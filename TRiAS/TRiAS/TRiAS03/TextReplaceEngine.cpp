// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 18:04:49
//
// @doc
// @module TextReplaceEngine.cpp | Implementation of the <c CTextReplaceEngine> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/ComBool.h>

#include <ClipBrd.hxx>
#include <TextReplacePrp.h>
#include <xtensnxx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "TRiASTrans.h"
#include "DataHelp.h"
#include "TextReplaceEngine.h"

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DMatchString, IID_DMatchString);
DefineSmartInterface2(DMatchString2, IID_DMatchString2);
DefineSmartInterface(MatchPlainText);					// WMatchPlainText
DefineSmartInterface(MatchRegExpr);						// WMatchRegExpr
DefineSmartInterface2(DSearchObjects, IID_DSearchObjects);
DefineSmartInterface(EnumObjectsByNumber);
DefineSmartInterface(ObjectProperty2);
DefineSmartInterface(ObjectProperty3);

//DefineSmartInterface(UndoRedoObjectFeature);

/////////////////////////////////////////////////////////////////////////////
// CTextReplaceEngine

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400

HRESULT CTextReplaceEngine::UpdateRegistry(BOOL fRegister)
{
#if _TRiAS_VER >= 0x0400
	return _Module.UpdateRegistryFromResource(IDR_TEXTREPLACEENGINE, fRegister);
#else
	return (0 != g_dwVer4) ? _Module.UpdateRegistryFromResource(IDR_TEXTREPLACEENGINE, fRegister) : S_OK;
#endif // _TRiAS_VER >= 0x0400
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction 
STDMETHODIMP CTextReplaceEngine::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CTextReplaceEngine::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klassen, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CTextReplaceEngineWorkerNoMatch :
		public output_iterator
	{
	public:
		CTextReplaceEngineWorkerNoMatch(
				OutEnumLONG &rOutIter, CTextReplaceEngine *pThis, IObjectProps *pIProps, 
				IObjectProperty *pPropSrc, DMatchString2 *pMatch, IObjectProperty *pPropDest) : 
			m_rOutIter(rOutIter), m_pThis(pThis), m_Match(pMatch), 
			m_ObjPropSrc(pPropSrc), m_ObjPropDest(pPropDest)
		{
			pIProps -> EnumObjectProps (m_EnumProps.ppi());
			_ASSERTE(m_EnumProps.IsValid());
		}
		~CTextReplaceEngineWorkerNoMatch() {}

	// diese Klasse wird als Output-Iterator verwendet (wird für jedes zu bearbeitende Objekt gerufen)
	    CTextReplaceEngineWorkerNoMatch& operator= (const LONG & lONr) throw(_com_error) 
		{ 
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);

		CComBSTR bstr;

			if (SUCCEEDED(m_pThis -> GenerateOutput (lONr, m_EnumProps, &bstr)) &&
				S_OK == m_pThis -> MatchAndReplaceString(lONr, m_Match, m_ObjPropSrc, bstr, m_ObjPropDest))
			{
				m_rOutIter = lONr;				// object should be added to the output collection
			}
			return *this; 
		}
		CTextReplaceEngineWorkerNoMatch& operator * (void) throw() { return *this; }
		CTextReplaceEngineWorkerNoMatch& operator++ (void)	throw() { return *this; }
		CTextReplaceEngineWorkerNoMatch operator++ (int) throw() { return *this; }

		CTextReplaceEngineWorkerNoMatch &operator= (const CTextReplaceEngineWorkerNoMatch &rhs)
		{
			if (&rhs != this) {
				m_pThis = rhs.m_pThis;
				m_rOutIter = rhs.m_rOutIter;
				m_Match = rhs.m_Match;
				m_EnumProps = rhs.m_EnumProps;
				m_ObjPropSrc = rhs.m_ObjPropSrc;
				m_ObjPropDest = rhs.m_ObjPropDest;
			}
			return *this;
		}

	protected:
		CTextReplaceEngine *m_pThis;
		OutEnumLONG m_rOutIter;
		WDMatchString2 m_Match;
		WEnumObjProps m_EnumProps;
		WObjectProperty m_ObjPropSrc;
		WObjectProperty2 m_ObjPropDest;
	};

// das Ganze nochmal aber mit nochmaligem Test
	class CTextReplaceEngineWorker 
	{
	public:
		CTextReplaceEngineWorker(
				OutEnumLONG &rOutIter, CTextReplaceEngine *pThis, IObjectProps *pIProps, 
				IObjectProperty *pPropSrc, DMatchString2 *pMatch, IObjectProperty *pPropDest) : 
			m_pThis(pThis), m_rOutIter(rOutIter), m_Match(pMatch), 
			m_ObjPropSrc(pPropSrc), m_ObjPropDest(pPropDest)
		{
			pIProps -> EnumObjectProps (m_EnumProps.ppi());
			_ASSERTE(m_EnumProps.IsValid());
		}
		~CTextReplaceEngineWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr) throw(_com_error)
		{
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);

		CComBSTR bstr;

			if (SUCCEEDED(m_pThis -> GenerateOutput (lONr, m_EnumProps, &bstr)) &&
				S_OK == m_pThis -> MatchAndReplaceString(lONr, m_Match, m_ObjPropSrc, bstr, m_ObjPropDest))
			{
				m_rOutIter++ = lONr;		// object is added to the output collections
			}
		}

	private:
		CTextReplaceEngine *m_pThis;
		OutEnumLONG &m_rOutIter;
		WDMatchString2 m_Match;
		WEnumObjProps m_EnumProps;
		WObjectProperty m_ObjPropSrc;
		WObjectProperty2 m_ObjPropDest;
	};
} // namespace

STDMETHODIMP CTextReplaceEngine::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// Undo/Redo level aufmachen
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID(IDS_UNDO_REPLACE, &RF), 64);
	TRiASTransaktion UndoLevel(resUndo);

	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

#if defined(_USE_CONFIRMREPLACE_DIALOG)
	// Dialog zum Nachfragen beim Nutzer
		if (NULL == m_pConfirm) {
		Window *pParent = (pWindow)DexxExtensionProc((WPARAM)DEX_QUERYACTIVEVIEWWINDOW, 0L);
		ResourceFile RF (g_pDLLName);

			_ASSERTE(NULL != pParent);
			ATLTRY(m_pConfirm = new CConfirmReplaceDlg(pParent, ResID(CConfirmReplaceDlg::IDD, &RF)));
			if (NULL != m_pConfirm) {
				m_pConfirm -> ChangePosition(m_ptDlgPos);
				m_pConfirm -> Show();
			}
		}
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)

	// QuellObjekteigenschaft und entsprechendes Match-Objekt bestimmen
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge
	WObjectProps Props;
	WObjectProperty ObjPropSrc, ObjPropDest;

		THROW_FAILED_HRESULT(GetMatchProperties(Props.ppi(), ObjPropSrc.ppi(), ObjPropDest.ppi()));

	// unter Umständen geht es schneller als durch direktes Durchgehen
	WEnumObjectsByNumber Enum2nd;
	WDMatchString2 Match;
	
		THROW_FAILED_HRESULT(GetMatchObject (Match.ppi()));

		if (!m_Status.m_fUseRegExpr && S_OK == TryToSearch(ObjPropSrc, m_Objects.Count(), Enum2nd.ppi())) {
		// Schnittmenge zwischen Eingabemenge und Recherchergebnis bilden
		OutEnumLONG outenum (static_cast<IEnum<LONG> *>(EnumOut));
		CTextReplaceEngineWorkerNoMatch iter_out (outenum, this, Props, ObjPropSrc, Match, ObjPropDest);
		WEnumLONG Objs2nd (Enum2nd);

			set_intersection(InEnumLONG(&m_Objects), InEnumLONG(),
							 InEnumLONG(static_cast<IEnum<LONG> *>(Objs2nd)), InEnumLONG(), 
							 iter_out);
		} 
		else {
		// alle Objekte in m_Objects auf Recherchekriterium prüfen und bei positivem Test ausgeben
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), 
					 CTextReplaceEngineWorker(iter_out, this, Props, ObjPropSrc, Match, ObjPropDest));
		}

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		DELETE_OBJ(m_pCfgDlg);
#if defined(_USE_CONFIRMREPLACE_DIALOG)
		if (NULL != m_pConfirm) {
			m_ptDlgPos = m_pConfirm -> GetPosition();
			delete m_pConfirm;
			m_pConfirm = NULL;
		}
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)

	// Transaktion ist nun gültig
		UndoLevel.End();

#if defined(_USE_CONFIRMREPLACE_DIALOG)
	} COM_CATCH_OP_NOASSERT_ON((delete m_pCfgDlg, delete m_pConfirm, m_pCfgDlg = NULL, m_pConfirm = NULL), E_ABORT);
#else
	} COM_CATCH_OP_NOASSERT_ON((delete m_pCfgDlg, m_pCfgDlg = NULL), E_ABORT);
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
	return S_OK;
}

namespace {
// Suchmode herausarbeiten
	SEARCHMODE GetSearchMode (CTextReplaceEngineDlg::CDlgStatus *pStatus)
	{
		_ASSERTE(!pStatus -> m_fUseRegExpr);	// in diesem Kontext darf keine RegExpr ausgewertet werden

	SEARCHMODE rgFlags = SEARCHMODE_NORMAL;

		if (pStatus -> m_fPartialMatch) {
			rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_PARTIALMATCH);
			if (pStatus -> m_fTestBOB)
				rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_PARTIALMATCHBOB);
		}
		if (pStatus -> m_fCapital)
			rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_NOMATCHCASE);

		return rgFlags;
	}
}

HRESULT CTextReplaceEngine::TryToSearch (
	IObjectProperty *pIOP, ULONG ulCnt, IEnumObjectsByNumber **ppIEnum)
{
	_ASSERTE(m_fIsInitialized);
	if (!IsInitialized()) return E_UNEXPECTED;

HRESULT hr = S_OK;

	COM_TRY {
	WDSearchObjects Search (pIOP);		// throws hr
	CComBSTR bstrMatch (m_Status.m_strFindWhat.c_str());
	SEARCHMODE rgFlags = GetSearchMode(&m_Status);


		THROW_FAILED_HRESULT(hr = Search -> ConsiderSearch(bstrMatch, rgFlags, ulCnt));
		if (S_OK == hr) 
			THROW_FAILED_HRESULT(Search -> SearchObjects(bstrMatch, rgFlags, ppIEnum));

	} COM_CATCH;
	return hr;		// ggf. implementiert aber nicht zu empfehlen
}

///////////////////////////////////////////////////////////////////////////////
// Generieren des entsprechenden Match-Objektes
HRESULT CTextReplaceEngine::GetMatchObject (DMatchString2 **ppIMatch)
{
	if (NULL == ppIMatch) return E_POINTER;

	_ASSERTE(IsInitialized());
	if (!IsInitialized()) return E_UNEXPECTED;

// je nach gewählten Optionen das richtige MatchObjekt generieren
WDMatchString2 Match;

	COM_TRY {
		if (m_Status.m_fUseRegExpr) {
		// mit RegularExpressions suchen
			_ASSERTE(!m_Status.m_fTestBOB);

			Match = WDMatchString2 (CLSID_MatchRegExprExakt);
			WMatchRegExpr(Match) -> put_FullMatch (CComBool(!m_Status.m_fPartialMatch));
		} 
		else {
		// Text vollständig wiederfinden (bzw. Textanfang)
			Match = WDMatchString2 (CLSID_MatchPlainTextExakt);

		WMatchPlainText MatchTxt(Match);

			MatchTxt -> put_ExistanceOnly (VARIANT_FALSE);
			MatchTxt -> put_FullMatch (CComBool(!m_Status.m_fPartialMatch));
			MatchTxt -> put_TestBOB (CComBool(m_Status.m_fTestBOB));
		}

	// zu suchenden Text setzen
	CComBSTR bstrMatch (m_Status.m_strFindWhat.c_str());

		THROW_FAILED_HRESULT(Match -> put_MatchText (bstrMatch));
		THROW_FAILED_HRESULT(Match -> put_MatchCase (CComBool(!m_Status.m_fCapital)));
		THROW_FAILED_HRESULT(Match -> put_NegateMatch (VARIANT_FALSE));

	} COM_CATCH;
	*ppIMatch = Match.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Abfragen der ausgewählten Objekteigenschaft
HRESULT CTextReplaceEngine::GetMatchProperties (
	IObjectProps **ppIProps, IObjectProperty **ppIOPSrc, IObjectProperty **ppIOPDest)
{
	if (NULL == ppIProps || NULL == ppIOPSrc || NULL == ppIOPDest) 
		return E_POINTER;

	*ppIProps = NULL;
	*ppIOPSrc = NULL;
	*ppIOPDest = NULL;
	
// Liste der Objekteigenschaften initialisieren
WObjectProps Props;
BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

	if (Props.IsValid()) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			if (FAILED(Props -> OnNewReferenceObject (0L))) 
				return E_FAIL;
			DEX_SetMustInitOPFs(FALSE);
		}
	}

WEnumObjProps EnumProps;

	RETURN_FAILED_HRESULT(Props -> EnumObjectProps (EnumProps.ppi()));
	RETURN_FAILED_HRESULT(EnumProps -> FindByName (m_Status.m_strObjPropSrc.c_str(), ppIOPSrc));
	RETURN_FAILED_HRESULT(EnumProps -> FindByName (m_Status.m_strObjPropDest.c_str(), ppIOPDest));
	*ppIProps = Props.detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Ergebniswert erzeugen
namespace {
// Wert einer vorgegebenen Objekteigenschaft an Zeichenkette anhängen
	int AppendObjectProperty (CComBSTR &rbstrDest, INT_PTR lONr, IEnumObjProps *pEnum, LPCSTR pcName)
	{
	LPCSTR pcBegin = pcName;

		while ('\0' != *pcName) {
		int c = *pcName++;

			if ('\\' == c && '}' == *pcName) {
				++pcName;	// zeigt jetzt auf erstes Zeichen nach "\}"
				break;
			}
		}

	// Namen der Objekteiegnschaft bilden
	os_string strObjProp (pcBegin, pcName-pcBegin-2);
	WObjectProperty Prop;
	char cbBuffer[_MAX_PATH];
	
		if (SUCCEEDED(pEnum -> FindByName (strObjProp.c_str(), Prop.ppi())) && 
			SUCCEEDED(Prop -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL))) 
		{
			rbstrDest.Append(cbBuffer);
		}
		return pcName-pcBegin;	// liefert Anzahl der zu überspringenden Zeichen
	}

// Inhalt der Zwischenablage an eine Zeichenkette anhängen
	bool AppendClipBoard (CComBSTR &rbstrDest)
	{
	CClipboard CB;
	char cbBuffer[_MAX_PATH];

		if (CB.GetItemSize(CClipboard::FmtText) > 0 && CB.Retrieve(cbBuffer, sizeof(cbBuffer))) {
			rbstrDest.Append(cbBuffer);
			return true;
		}
		return false;	// ClipBoard enthält keinen Text
	}
}

HRESULT CTextReplaceEngine::MatchAndReplaceString (
	INT_PTR lONr, DMatchString2 *pMatch, IObjectProperty *pPropSrc, 
	BSTR bstrToReplace, IObjectProperty2 *pPropDest) throw(_com_error)
{
char cbBuffer[_MAX_PATH];

	if (FAILED(pPropSrc -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL))) 
		return E_FAIL;

// Objekteigenschaft existiert
CComBSTR bstrSrc (cbBuffer);
CComBSTR bstrOut;
int iMatched = false;

	USES_CONVERSION;
	if (SUCCEEDED(pMatch -> MatchAndReplaceString (bstrSrc, bstrToReplace, &iMatched, &bstrOut)) && iMatched) {
#if defined(_USE_CONFIRMREPLACE_DIALOG)
	// ggf. beim Nutzer nachfragen
	CConfirmReplaceDlg::CONFIRMATION rgConfirm = CConfirmReplaceDlg::CONFIRMATION_Replace;

		if (NULL != m_pConfirm) {
		CComBSTR bstrNewValue;

			rgConfirm = m_pConfirm -> HandleNextObject(lONr, bstrSrc, bstrOut, &bstrNewValue);

		// neuer Wert eingegeben
		bool fNewValue = CConfirmReplaceDlg::CONFIRMATION_NewValue & rgConfirm;

			rgConfirm = CConfirmReplaceDlg::CONFIRMATION(rgConfirm & ~CConfirmReplaceDlg::CONFIRMATION_NewValue);
			if (fNewValue) {
				bstrOut = bstrNewValue;		// Nutzer hat neuen Wert eingegeben
			} 
			else if (CConfirmReplaceDlg::CONFIRMATION_ReplaceAll == rgConfirm) {
			// nicht weiter nachfragen
				m_ptDlgPos = m_pConfirm -> GetPosition();
				delete m_pConfirm;
				m_pConfirm = NULL;
			}
		}

	// Schreiben des Attributwertes ggf. mit Undo
		switch (rgConfirm) {
		case CConfirmReplaceDlg::CONFIRMATION_Replace:
		case CConfirmReplaceDlg::CONFIRMATION_ReplaceAll:
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
			{
			WObjectProperty3 Prop3;

				if (SUCCEEDED(pPropDest -> QueryInterface(Prop3.ppi())))
					return Prop3 -> SetWithUndo (lONr, OLE2A(bstrOut));
				
				return pPropDest -> Set(lONr, OLE2A(bstrOut));
			}
#if defined(_USE_CONFIRMREPLACE_DIALOG)
			break;

		case CConfirmReplaceDlg::CONFIRMATION_Cancel:
			_com_issue_error(E_ABORT);		// Operation abbrechen

		default:
			break;
		}
		// CConfirmReplaceDlg::CONFIRMATION_NextObject returns S_FALSE
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
	}
	return S_FALSE;
}

HRESULT CTextReplaceEngine::GenerateOutput (INT_PTR lONr, IEnumObjProps *pEnum, BSTR *pbstrOut)
{
	_ASSERTE(NULL != pEnum && NULL != pbstrOut);
	*pbstrOut = NULL;

	if (os_npos == m_Status.m_strReplaceWith.find_first_of('\\')) {
	// keine Spezialkommandos, also einfach kopieren der ReplaceWith-Zeichenkette
	CComBSTR bstrDest (m_Status.m_strReplaceWith.c_str());

		*pbstrOut = bstrDest.Detach();
	}
	else {
		USES_CONVERSION;
		COM_TRY {
		LPCSTR pcSrc = m_Status.m_strReplaceWith.c_str();
		CComBSTR bstrDest;

			while ('\0' != *pcSrc) {
			int c = *pcSrc++;

				if ('\\' == c) {
				// Sonderfeld soll eingefügt werden
				int cNext = *pcSrc++;
				
					switch (cNext) {
					case '{':	// Objekteigenschaft
						pcSrc += AppendObjectProperty (bstrDest, lONr, pEnum, pcSrc);
						break;

					case 'c':	// Zwischenablage
						AppendClipBoard (bstrDest);
						break;

					default:
						bstrDest.Append(A2OLE(pcSrc-2), 2);
						break;
					}
				} 
				else {
				// normaler Buchstabe --> in Ausgabe übernehmen
					bstrDest.Append(A2OLE(pcSrc-1), 1);
				}
			}
			*pbstrOut = bstrDest.Detach();
			
		} COM_CATCH;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTextReplaceEngine::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTextReplaceEngine::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

	m_Status.erase();
	COM_TRY {
		_ASSERTE(sizeof(int) == sizeof(long));
		
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fCapital));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fPartialMatch));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fTestBOB));
		THROW_FAILED_HRESULT(LoadLong(pStm, (long &)m_Status.m_fUseRegExpr));

		THROW_FAILED_HRESULT(CMatchLastComboBox::Load(pStm, m_Status.m_strFindWhat, m_Status.m_lstFindWhat));
		THROW_FAILED_HRESULT(CMatchLastComboBox::Load(pStm, m_Status.m_strReplaceWith, m_Status.m_lstReplaceWith));

		THROW_FAILED_HRESULT(CSelectObjectProperty::Load(pStm, m_Status.m_strObjPropSrc));
		THROW_FAILED_HRESULT(CSelectObjectProperty::Load(pStm, m_Status.m_strObjPropDest));

#if defined(_USE_CONFIRMREPLACE_DIALOG)
		THROW_FAILED_HRESULT(LoadLong(pStm, m_ptDlgPos.X()));
		THROW_FAILED_HRESULT(LoadLong(pStm, m_ptDlgPos.Y()));
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)

	} COM_CATCH;

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CTextReplaceEngine::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fCapital));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fPartialMatch));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fTestBOB));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_Status.m_fUseRegExpr));

		THROW_FAILED_HRESULT(CMatchLastComboBox::Save(pStm, m_Status.m_strFindWhat, m_Status.m_lstFindWhat));
		THROW_FAILED_HRESULT(CMatchLastComboBox::Save(pStm, m_Status.m_strReplaceWith, m_Status.m_lstReplaceWith));

		THROW_FAILED_HRESULT(CSelectObjectProperty::Save(pStm, m_Status.m_strObjPropSrc));
		THROW_FAILED_HRESULT(CSelectObjectProperty::Save(pStm, m_Status.m_strObjPropDest));

#if defined(_USE_CONFIRMREPLACE_DIALOG)
		THROW_FAILED_HRESULT(SaveLong(pStm, m_ptDlgPos.GetX()));
		THROW_FAILED_HRESULT(SaveLong(pStm, m_ptDlgPos.GetY()));
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTextReplaceEngine::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize  -> QuadPart += 4*sizeof(long) + 
#if defined(_USE_CONFIRMREPLACE_DIALOG)
		2*sizeof(CoOrd) +
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
		CMatchLastComboBox::GetSizeMax(m_Status.m_strFindWhat, m_Status.m_lstFindWhat) + 
		CMatchLastComboBox::GetSizeMax(m_Status.m_strReplaceWith, m_Status.m_lstReplaceWith) +
		CSelectObjectProperty::GetSizeMax (m_Status.m_strObjPropSrc) +
		CSelectObjectProperty::GetSizeMax (m_Status.m_strObjPropDest);
	return S_OK;
}

STDMETHODIMP CTextReplaceEngine::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

#if defined(_USE_CONFIRMREPLACE_DIALOG)
	m_ptDlgPos = Point(0, 0);
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CTextReplaceEngine::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CTextReplaceEngineDlg::CreateInstance(this, ResID(CTextReplaceEngineDlg::IDD, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 

		m_pCfgDlg -> InitWithData (m_Status);

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CTextReplaceEngine::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

// TextRecherche parametrisieren

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <statguid.h>
#include <ospace/std/algorithm>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "gentguid.h"
#include "GenTextDlg.h"
#include "SelObjPropDlg.h"

extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// 
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(EnumObjectsByNumber);

/////////////////////////////////////////////////////////////////////////////
// 
BOOL ReadTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPTSTR pText, int iLen);
BOOL WriteTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPCTSTR pText);

#pragma warning (disable: 4355)

CGenTextDlg::CGenTextDlg (CGenTextPropAct *pParent, ResID uiDlg, LPCSTR pcCaption)
	: CPropertyPage (uiDlg, pcCaption), 
	  m_SelObjProp (this, IDC_SELECT_OBJPROP),
	  m_sleObjProp (this, IDC_OBJPROPERTY),
	  m_rbFromObjProp (this, IDC_FROMOBJPROP),
	  m_rbDirectText (this, IDC_DIRECTINPUT),
	  m_cbDirectText (this, IDC_DIRECTTEXTLIST),
	  m_cbDependend (this, IDC_CREATEDEPENDEND),
	  m_rbDelete (this, IDC_DELETE),
	  m_rbReplace (this, IDC_REPLACE),
	  m_cbDynamic (this, IDC_DYNAMICLABEL),
	  m_cbRotate (this, IDC_ROTATEFORLINES),
	  m_cbDoNotMove (this, IDC_DONOTMOVE),
	  m_cbOnlyExistant (this, IDC_NOTEXISTANT),
	  m_ftDepOption (this, IDC_OPTIONSELECT),
	  m_cbDeleteTarget (this, IDC_DELETETARGETOBJECT),
	  m_pParent(pParent)
{
	m_dwFlags = 0L;
	m_fIsInitialized = false;
	m_pStatus = NULL;
}

#pragma warning (default: 4355)

CGenTextDlg::~CGenTextDlg (void)
{
}

CGenTextDlg *CGenTextDlg::CreateInstance (
	CGenTextPropAct *pParent, ResID uiDlg, LPCSTR pcCaption)
{
	COM_TRY {
	CGenTextDlg *pDlg = NULL;
	
		pDlg = new CGenTextDlg (pParent, uiDlg, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;

	} COM_CATCH_RETURN(NULL);
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CGenTextDlg::WindowInit (Event)
{
// Controls initialisieren
	m_rbFromObjProp.FInit();
	m_sleObjProp.FInit();
	m_SelObjProp.FInit();

	m_rbDirectText.FInit();
	m_cbDirectText.FInit();

	m_cbDependend.FInit();
	m_ftDepOption.FInit();
	m_rbDelete.FInit();
	m_rbReplace.FInit();

	m_cbDynamic.FInit();
	m_cbRotate.FInit();
	m_cbDoNotMove.FInit();
	m_cbOnlyExistant.FInit();
	m_cbDeleteTarget.FInit();

// Control voreinstellen
	m_rbFromObjProp.SetState (TRUE);
	m_rbDirectText.SetState (FALSE);

	m_cbDependend.SetChecked (FALSE);
	m_cbRotate.SetChecked (FALSE);
	m_cbDoNotMove.SetChecked (FALSE);
	m_cbOnlyExistant.SetChecked (FALSE);

#if _MSC_VER < 1100
// die folgenden beiden erst ab TRiASV3.0 aktiviert
	m_cbRotate.Hide();
//	m_cbDoNotMove.Hide();

// dynamisch geht nur in 'neueren' Datenbanken
	if (DEX_GetDBVersion() <= VERSION0500000A)
		m_cbDynamic.Hide();
#endif // _MSC_VER < 1100

// Bitmapbutton initialisieren
ResourceFile RF (g_pDLLName);

	if (m_SelObjProp.LoadBitmaps (ResID (IDB_ARROW_DOWN, &RF), 
				ResID (IDB_ARROW_DOWN_SEL, &RF), 
				ResID (IDB_ARROW_DOWN_FOCUS, &RF), 
				ResID (IDB_ARROW_DOWN_DISABLED, &RF)))
	{
		m_SelObjProp.SizeToContent(); 
	}

// Liste der Objekteigenschaften initialisieren
BOOL fMustReInit = DEX_GetObjectProps (m_Props.ppi());

	if (m_Props.IsValid()) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			m_Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			if (FAILED(m_Props -> OnNewReferenceObject (0L))) 
				return;
			DEX_SetMustInitOPFs(FALSE);
		}
	}

// Optionen initialisieren
	if (NULL != m_pStatus) {
		m_rbFromObjProp.SetState (m_pStatus -> m_fFromObjProp);
		m_rbDirectText.SetState (!m_pStatus -> m_fFromObjProp);

		m_cbDependend.SetChecked (m_pStatus -> m_fDependend);
		m_rbDelete.SetState (m_pStatus -> m_fDelete);
		m_rbReplace.SetState (!m_pStatus -> m_fDelete);
#if _MSC_VER > 1100
		m_cbRotate.SetChecked (m_pStatus -> m_fRotate);
#endif // _MSC_VER > 1100
		m_cbDoNotMove.SetChecked (m_pStatus -> m_fDoNotMove);
		m_cbDynamic.SetChecked (m_pStatus -> m_fDynamic);
		m_cbOnlyExistant.SetChecked (m_pStatus -> m_fOnlyExistant);
		m_cbDeleteTarget.SetChecked (m_pStatus -> m_fDeleteTarget);

	// Liste der letzten Direkteingaben initialisieren
	int iIndex = m_cbDirectText.AddString (m_pStatus -> m_strDirectText.c_str());

		if (iIndex >= 0) m_cbDirectText.ChangeCurrentIndex(iIndex);

		for (CDirectTextList::iterator it = m_pStatus -> m_lstDirectText.begin();
			 it != m_pStatus -> m_lstDirectText.end(); ++it)
		{
			if (!(*it == m_pStatus -> m_strDirectText))
				m_cbDirectText.AddString ((*it).c_str());
		}

	// Objekteigenschaft
		if (SUCCEEDED(RetrieveObjProp (m_pStatus -> m_strObjProp.c_str(), m_Props, m_ObjProp.ppi())))
			m_sleObjProp.SetText (m_pStatus -> m_strObjProp.c_str());
	}

	m_fIsInitialized = true;

	AdjustOK();
	AdjustControls(m_rbFromObjProp.GetState(), m_cbDependend.isChecked());
}


HRESULT CGenTextDlg::InitWithData (CGenTextDlg::CDlgStatus &rStatus)
{
	m_pStatus = &rStatus;		// Pointer auf StatusObjekt speichern
	return S_OK;
}

void CGenTextDlg::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_SELECT_OBJPROP:
	// Controls richten
		m_rbFromObjProp.SetState (TRUE);
		m_rbDirectText.SetState (FALSE);
		AdjustControls(TRUE, m_cbDependend.isChecked());
	
	// Dialog anzeigen
		ShowObjPropDlg();
		AdjustOK();
		break;

	case IDC_FROMOBJPROP:
		m_rbFromObjProp.SetState (TRUE);
		m_rbDirectText.SetState (FALSE);
		AdjustControls(m_rbFromObjProp.GetState(), m_cbDependend.isChecked());
		AdjustOK();
		break;

	case IDC_DIRECTINPUT:
		m_rbFromObjProp.SetState (FALSE);
		m_rbDirectText.SetState (TRUE);
		AdjustControls(m_rbFromObjProp.GetState(), m_cbDependend.isChecked());
		AdjustOK();
		break;

	case IDC_CREATEDEPENDEND:
	case IDC_DYNAMICLABEL:
		AdjustControls(m_rbFromObjProp.GetState(), m_cbDependend.isChecked());
		AdjustOK();
		break;
	}
}

int CGenTextDlg::OnSetActive (NotifyEvt e)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen 
void CGenTextDlg::OnCancel (NotifyEvt)
{
	return;		// hier evtl. Aufräumarbeiten durchführen
}

int CGenTextDlg::OnWizNext (NotifyEvt e)
{
	PrepareResult();
	return 0;
}

BOOL CGenTextDlg::OnWizFinish (NotifyEvt e)
{
	PrepareResult();
//#if _MSC_VER < 1100
//	return true;
//#else
	return false;		// FIXED: Bug in PropertyChoice (FakeMfc.Ext)	
//#endif _MSC_VER < 1100
}

void CGenTextDlg::EditChange (ControlEvt)
{
	AdjustOK();
}

void CGenTextDlg::ListBoxSel (ControlEvt)
{
	AdjustOK();
}

// aktuelle Auswahl aus Controls in interne Variablen übernehemen
void CGenTextDlg::PrepareResult (void)
{
	TX_ASSERT(NULL != m_pStatus);

	if (NULL == m_pStatus) return;

// Flags wegschreiben
	m_pStatus -> erase();

	m_pStatus -> m_fFromObjProp = m_rbFromObjProp.GetState();
	m_pStatus -> m_fDependend = m_cbDependend.isChecked();
	m_pStatus -> m_fDelete = m_rbDelete.GetState();
#if _MSC_VER > 1100
	m_pStatus -> m_fRotate = m_cbRotate.isChecked();
#else
	m_pStatus -> m_fRotate = false;
#endif // _MSC_VER > 1100
	m_pStatus -> m_fDoNotMove = m_cbDoNotMove.isChecked();
	m_pStatus -> m_fDynamic = m_cbDynamic.isChecked();
	m_pStatus -> m_fOnlyExistant = m_cbOnlyExistant.isChecked();
	m_pStatus -> m_fDeleteTarget = m_cbDeleteTarget.isChecked();

// SuchStrings wegschreiben
char cbBuffer[_MAX_PATH+1];
int iMax = m_cbDirectText.GetCount();

	for (int i = 0; i < iMax && i < MAXLASTITEMS; i++) {
		if (m_cbDirectText.GetString (cbBuffer, i, sizeof(cbBuffer)-1))
			m_pStatus -> m_lstDirectText.push_back(os_string(cbBuffer));
	}

	m_cbDirectText.GetText(cbBuffer, _MAX_PATH);
	m_pStatus -> m_strDirectText = cbBuffer;

// Objekteigenschaft wegschreiben
	m_sleObjProp.GetText (cbBuffer, _MAX_PATH);
	m_pStatus -> m_strObjProp = cbBuffer;
}

/////////////////////////////////////////////////////////////////////////////
// 
BOOL CGenTextDlg::ShowObjPropDlg (void)
{
// Objekteigenschaften lediglich einmal initialisieren
	TX_ASSERT(NULL != (IUnknown *)m_Props);
	if (!m_Props) return false;

ResourceFile RF (g_pDLLName);
CSelObjPropsDlg SelObjProps (this, RF, m_Props);
char cbBuffer[64];

	m_sleObjProp.GetText (cbBuffer, sizeof(cbBuffer)-1);
	m_ObjProp.Release();		// vorhergehende freigeben

	if (SelObjProps.FInit (cbBuffer)) {
	Point pt = m_sleObjProp.GetPosition();
	Dimension dim = SelObjProps.GetSize();

		pt.X() -= 1;
		pt.Y() -= dim.Height()+1;
		SelObjProps.ChangePosition (pt);
		
		SelObjProps.Show();
		if (SelObjProps.Result()) {
		string str;

			SelObjProps.GetSelectedObjProp (str);
			if (SUCCEEDED(RetrieveObjProp (str.c_str(), m_Props, m_ObjProp.ppi())))
			{
				m_sleObjProp.SetText (str.c_str());
				AdjustOK();
				return true;
			}
		}
	}
	return false;
}

// Finden einer bestimmten Objekteigenschaft
HRESULT CGenTextDlg::RetrieveObjProp (
	LPCSTR pcName, IObjectProps *pIProps, IObjectProperty **ppIOP)
{
WEnumObjProps EnumProps;
HRESULT hr = pIProps -> EnumObjectProps (EnumProps.ppi());

	if (FAILED(hr)) return hr;
	return EnumProps -> FindByName (pcName, ppIOP);
}

void CGenTextDlg::AdjustControls(BOOL fFromObjProp, BOOL fDependend)
{
	if (!m_fIsInitialized) return;

	if (fFromObjProp) {
		m_sleObjProp.Enable();
		m_SelObjProp.Enable();
		m_cbDirectText.Disable();
	} else {
		m_sleObjProp.Disable();
//		m_SelObjProp.Disable();
		m_cbDirectText.Enable();
	}

	if (fDependend) {
		m_ftDepOption.Enable();
		m_rbDelete.Enable();
		m_rbReplace.Enable();
		m_cbDeleteTarget.Disable();
#if _MSC_VER > 1100
		m_cbRotate.Enable();
#endif // _MSC_VER > 1100
	} else {
		m_ftDepOption.Disable();
		m_rbDelete.Disable();
		m_rbReplace.Disable();
		m_cbDeleteTarget.Enable();
#if _MSC_VER > 1100
		m_cbRotate.Disable();
#endif // _MSC_VER > 1100
	}

	if (fFromObjProp && fDependend) {
		m_cbDynamic.Enable();
		m_cbOnlyExistant.Enable();
	} else {
		m_cbDynamic.SetChecked(FALSE);
		m_cbDynamic.Disable();
		m_cbOnlyExistant.SetChecked(FALSE);
		m_cbOnlyExistant.Disable();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Buttons richten 
BOOL CGenTextDlg::AdjustOK (void)
{
	if (!m_fIsInitialized) return false;

// Knöpfe des Dialoges richten (Next, Previous, Finish)
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

// gültig, wenn eine der beiden Eingabevarianten vollständig ist
	if ((m_rbDirectText.GetState() && (-1 != m_cbDirectText.GetCurrentIndex() || 0 < m_cbDirectText.GetTextLen())) ||
		(m_rbFromObjProp.GetState() && 0 < m_sleObjProp.GetTextLen())) 
	{
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons (dwBttns);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Abfragen der ausgewählten Objekteigenschaft
HRESULT CGenTextDlg::GetSelectedProperty (IObjectProperty **ppIOP)
{
	if (NULL == ppIOP) return E_POINTER;
	if (!m_ObjProp) return E_UNEXPECTED;	// not initialized yet

WObjectProperty OProp (m_ObjProp);

	*ppIOP = OProp.detach();
	return S_OK;
}

HRESULT CGenTextDlg::ResetEnumLONG (void)
{
	m_Objects.Clear();
	return S_OK;
}

HRESULT CGenTextDlg::SetEnumLONG (IEnum<LONG> *pIEnumObjs)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	OutEnumIfLONG iter_out_if (&m_Objects);		// throws hr

		copy (InEnumLONG(pIEnumObjs), InEnumLONG(), iter_out_if);
	
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// STL worker classes
namespace {
	class CCreateTextBase :
		public unary_function<LONG, LONG>
	{
	protected:
		CGenTextDlg::CDlgStatus &m_rStatus;
		CPropertyActionExtUsage* m_pPAUse;	//JG Callback für ProgInd
		void Tick()
		{
			if (NULL != m_pPAUse)
				m_pPAUse -> Tick();
		}

		HRESULT FillObjectGeometrie (long lONr, OBJGEOMETRIE *pOG);
		void FreeObjGeometrie (OBJGEOMETRIE *pOG);
		BOOL EvalSchwerPunkt (OBJGEOMETRIE *pOG, POINT *pszPt);

		HRESULT GetPointAndIdent (long lONr, POINT *pszPt, LONG *plIdent);
		HRESULT CreateRelation (LONG lONr, LONG TxtONr);
		BOOL IsTextObject (LONG lONr);

		HRESULT CorrectPointCoords (long lIdent, POINT *ppt);
		SIZE GetDotsPerMM (HDC hDC = NULL);

	public:
		CCreateTextBase (CGenTextDlg::CDlgStatus &rStatus, /*JG*/CPropertyActionExtUsage* pPAUse = NULL)
			:  m_rStatus(rStatus)
		{
			m_pPAUse = pPAUse;
		}

		HRESULT CreateTextObject (LONG lONr, LPCSTR pcText, bool fDynamic, LONG lIdent, LONG *plONr, POINT *ppt = NULL);

		HRESULT CreateRelatedTextObject (LONG lONr, LPCSTR pcText, bool fDynamic, LONG lIdent, LONG *plTxtONr, POINT *ppt = NULL);
		HRESULT GetRelatedObject (LONG lONr, LONG *plRelONr);
		HRESULT DeleteRelatedTextObject (LONG lONr, LONG TxtONr, LONG *plIdent);
		HRESULT ModifyRelatedTextObject (LONG lONr, LONG *plTxtONr, LPCSTR pcText);
	};

// Text über festen Text (evtl. dynamisch) erzeugen
	class CCreateTextDirect :
		public CCreateTextBase
	{
	protected:
		os_string m_strText;

	public:
		CCreateTextDirect (CGenTextDlg::CDlgStatus &rStatus, os_string str, CPropertyActionExtUsage* pPAUse)
			:	CCreateTextBase(rStatus, pPAUse), 
				m_strText(str)
		{
		}

	// Text erzeugen
		LONG operator() (LONG lONr);
	};

// Text über Objekteigenschaft (statisch) erzeugen
	class CCreateTextFromObjProp :
		public CCreateTextDirect
	{
	private:
		WObjectProperty m_ObjProp;

	public:
		CCreateTextFromObjProp (IObjectProperty *pIObjProp, CGenTextDlg::CDlgStatus &rStatus, CPropertyActionExtUsage* pPAUse)
			:	CCreateTextDirect(rStatus, os_string(g_cbNil), pPAUse), 
				m_ObjProp(pIObjProp)
		{
		}

	// Text erzeugen
		LONG operator() (LONG lONr);
	};
}	// namespace

/////////////////////////////////////////////////////////////////////////////
// Hier werden die Texte erzeugt/gelöscht bzw. sonstwie behandelt
HRESULT CGenTextDlg::GetEnumLONG (IEnum<LONG> **ppIEnumObjs)
{
	if (NULL == ppIEnumObjs) return E_POINTER;

	*ppIEnumObjs = NULL;
	COM_TRY {
	// neuen Enumerator anlegen und füllen
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);
	OutEnumIfLONG iter_out_if ((IEnum<LONG> *)EnumOut);		// throws hr

	ULONG counter = m_Objects.Count();
	SetMaxTicks(counter);	// JG 980914

		TX_ASSERT(NULL != m_pStatus);
		if (m_pStatus -> m_fFromObjProp) {
		// Text über Objekteigenschaft generieren (statisch)
		WObjectProperty ObjProp;

			THROW_FAILED_HRESULT(GetSelectedProperty (ObjProp.ppi()));

			if (m_pStatus -> m_fDynamic) {
			// dynamische Textobjekte erzeugen
				if (m_pStatus -> m_fOnlyExistant) {
				// nur für existierende OProps erzeugen
					transform(InEnumLONG(&m_Objects), InEnumLONG(), iter_out_if, CCreateTextFromObjProp(ObjProp, *m_pStatus, this/*JG*/));
				} else {
				// alle Objekte (nicht nur für existierende OProps) erzeugen
					transform(InEnumLONG(&m_Objects), InEnumLONG(), iter_out_if, CCreateTextDirect(*m_pStatus, m_pStatus -> m_strObjProp, this/*JG*/));
				}
			} else {
			// alle Objekte der Eingabemenge durchgehen und Texte bilden
				transform(InEnumLONG(&m_Objects), InEnumLONG(), iter_out_if, CCreateTextFromObjProp(ObjProp, *m_pStatus, this/*JG*/));
			}
		} else {
		// Text aus Direkteingabe verwenden
			TX_ASSERT(!m_pStatus -> m_fDynamic);	// darf nicht dynamisch sein
		}
		*ppIEnumObjs = (IEnum<LONG> *)EnumOut.detach();		// übernimmt RefCnt

	} COM_CATCH;

	return S_FALSE;	// das wars, und es war der letzte
}

/////////////////////////////////////////////////////////////////////////////
// evtl. existierendes Textobjekt finden
// diese Funktion liefert die ObjektNummer des abhängigen (Text-)Objektes 
extern "C" 
BOOL CALLBACK FindLinkedObject (long lONr, long lRCode, short iRTyp, void *pData)
{
// angehängtes Textobjekt gefunden
	if (lRCode == -1L && iRTyp == RTBegleitO) {
		*(LONG *)pData = lONr;		// ObjektNummer merken
		return FALSE;				// Enumeration abbrechen
	}
	return TRUE;
}

HRESULT CCreateTextBase::GetRelatedObject (LONG lONr, LONG *plRelONr)
{
	if (NULL == plRelONr)
		return E_POINTER;

	TX_ASSERT(m_rStatus.m_fDependend);

ENUMRELATIONOBJS ERO;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = lONr;
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitO;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedObject;
	ERO.pData = plRelONr;

	*plRelONr = 0L;
	DEX_EnumRelationObjects (ERO);

	if (0L == *plRelONr) 	// kein abhängiges Objekt vorhanden
		return S_FALSE;
	return S_OK;
}

HRESULT CCreateTextBase::CreateRelatedTextObject (
	LONG lONr, LPCSTR pcText, bool fDynamic, LONG lIdent, LONG *plTxtONr, POINT *ppt)
{
// Text erzeugen
	RETURN_FAILED_HRESULT(CreateTextObject (lONr, pcText, fDynamic, lIdent, plTxtONr, ppt));
	return CreateRelation (lONr, *plTxtONr);	// Bezugsrelation zum neuen Textobjekt erzeugen
}

HRESULT CCreateTextBase::CreateTextObject (
	LONG lONr, LPCSTR pcText, bool fDynamic, LONG lIdent, LONG *plONr, POINT *ppt)
{
	if (NULL == plONr) return E_POINTER;

	*plONr = 0L;

TEXTGEOMETRIEEX TG;
POINT ptPos;
long lTargetIdent = 0L;

	if (0L == lIdent || NULL == ppt)
		RETURN_FAILED_HRESULT(GetPointAndIdent (lONr, &ptPos, &lTargetIdent));

	if (0 == lIdent)
		lIdent = lTargetIdent;
	if (NULL != ppt)
		ptPos = *ppt;

	INITSTRUCT(TG, TEXTGEOMETRIEEX);
	TG.lIdent = lIdent;
	TG.iObjTyp = fDynamic ? OGLabel : OGText;
	TG.iFlags = OGNewObject|OGAddToView;
	TG.lCnt = 1;
	TG.pdblX = &ptPos.x;
	TG.pdblY = &ptPos.y;
	TG.iKCnt = strlen(pcText);
	TG.pText = const_cast<char *>(pcText);
	TG.fIndObjProp = fDynamic ? TRUE : FALSE;
	DEX_ModObjGeometrie(TG);

	*plONr = TG.lONr;		// neu erzeugtes Objekt
	if (0 == TG.lONr)
		return E_FAIL;

// evtl. Unique Ident erzeugen und wegschreiben
char cbBuffer[64];
long lUIMCode = DEX_GetUniqueIdentMCode();

	TX_ASSERT(-1 != lUIMCode);
	if (!ReadTextMerkmal (TT_Objekt, TG.lONr, lUIMCode, cbBuffer, sizeof(cbBuffer))) {
		wsprintf (cbBuffer, TEXT("GENTEXT_%ld"), TG.lONr);
		WriteTextMerkmal (TT_Objekt, TG.lONr, lUIMCode, cbBuffer);
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Koordinate ermitteln, an der Text erzeugt werden soll
HRESULT CCreateTextBase::GetPointAndIdent (long lONr, POINT *pszPt, LONG *plIdent)
{
// 1. Geometrie entsprechend ObjektTyp besorgen
OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);
	RETURN_FAILED_HRESULT(FillObjectGeometrie (lONr, &OG));

HRESULT fResult = S_OK;

	switch (OG.iObjTyp) {
	case OGPunkt:
		pszPt -> x = ((long *)(OG.pdblX))[0];
		pszPt -> y = ((long *)(OG.pdblY))[0];
		if (!m_rStatus.m_fDoNotMove)
			CorrectPointCoords (OG.lIdent, pszPt);
		break;
		
	case OGLinie:
		{	// mittlere Koordinate benutzen
		long iMiddle = OG.lCnt / 2;
		
			pszPt -> x = ((long *)(OG.pdblX))[iMiddle];
			pszPt -> y = ((long *)(OG.pdblY))[iMiddle];
		}
		break;
		
	case OGFlaeche:
		if (!EvalSchwerPunkt (&OG, pszPt))
			fResult = E_UNEXPECTED;
		break;
		
	default:
		TX_ASSERT(FALSE);
		pszPt -> x = 0;
		pszPt -> y = 0;
		fResult = E_INVALIDARG;
		break;
	}
	FreeObjGeometrie (&OG);	// Speicher freigeben

	if (NULL != plIdent)
		*plIdent = OG.lIdent;
	return fResult;
}

// Objektgeometrie besorgen ---------------------------------------------------
HRESULT CCreateTextBase::FillObjectGeometrie (long lONr, OBJGEOMETRIE *pOG)
{
// Eigenschaften des Objektes anfordern
DWORD dwSize = pOG -> dwSize;

	pOG -> dwSize = sizeof (OBJSTATISTIK);
	pOG -> lONr = lONr;
	DEX_GetObjStatistik (*pOG);

// Geometrie dazuholen
	pOG -> dwSize = dwSize;

// Felder anfordern
	COM_TRY {
		pOG -> pdblX = new long [pOG -> lCnt];
		pOG -> pdblY = new long [pOG -> lCnt];
		if (NULL == pOG -> pdblX || NULL == pOG -> pdblY) {
			delete pOG -> pdblX;
			return E_OUTOFMEMORY;
		}
			
		if (pOG -> iKCnt > 0) {
			if (OGFlaeche == pOG -> iObjTyp) {
				pOG -> plCnt = new long [pOG -> iKCnt];
				if (NULL == pOG -> plCnt) 
					return E_OUTOFMEMORY;
			} else if (OGText == pOG -> iObjTyp || OGLabel == pOG -> iObjTyp) {
				((TEXTGEOMETRIE *)pOG) -> pText = new char [pOG -> iKCnt];
				if (NULL == ((TEXTGEOMETRIE *)pOG) -> pText)
					return E_OUTOFMEMORY;
			}
		}
	} COM_CATCH;

	DEX_GetObjGeometrie (*pOG);
	return S_OK;
}

// freigeben der OBJGEOMETRIE-Struktur ----------------------------------------
void CCreateTextBase::FreeObjGeometrie (OBJGEOMETRIE *pOG)
{
	if (NULL == pOG) return;

// Geometriefelder freigeben
	if (pOG -> pdblX) delete [] (long *)pOG -> pdblX;
	if (pOG -> pdblY) delete [] (long *)pOG -> pdblY;
	
// Kontur-/bzw. Textfeld freigeben
	if (pOG -> iKCnt > 0) {
		if (OGFlaeche == pOG -> iObjTyp) {
			if (pOG -> plCnt)
				delete [] pOG -> plCnt;
		} else if (OGText == pOG -> iObjTyp || OGLabel == pOG -> iObjTyp) {
			if (((TEXTGEOMETRIE *)pOG) -> pText)
				delete [] ((TEXTGEOMETRIE *)pOG) -> pText;
		}
	}
}

// Berechnen des Flächenschwerpunktes
BOOL CCreateTextBase::EvalSchwerPunkt (OBJGEOMETRIE *pOG, POINT *pszPt) 
{
// teste Parameter der Fläche
	if (pOG == NULL || pOG -> iObjTyp != OGFlaeche)
		return FALSE;
		
long lSize = pOG -> plCnt[0];		// Anzahl Stützpunkte (Außenkontur)
long *pX = (long *)pOG -> pdblX;
long *pY = (long *)pOG -> pdblY;

	if (lSize <= 3 || pX == NULL || pY == NULL) return FALSE;

	if (pX[0] != pX[lSize-1] || pY[0] != pY[lSize-1])
		return FALSE;		// Kontur nicht geschlossen
		
// kleinste X/Y-Koordinate bestimmen
long lIndex;
long lXMin = LONG_MAX;
long lYMin = LONG_MAX;

	for (lIndex = 0; lIndex < lSize; lIndex++) {
		if (pX[lIndex] < lXMin) lXMin = pX[lIndex];
		if (pY[lIndex] < lYMin) lYMin = pY[lIndex];
	}	

// Schwerpunkt berechnen
double Xs = 0.0, Ys = 0.0, Xsi, Ysi, Inh;	// Schwerpunkt-Koordinaten
double dblF = 0.0;

	for (lIndex = 0; lIndex < (lSize - 1); lIndex++) {	// für alle Punkte der Folge
	double X1 = double (pX[lIndex] - lXMin);	// laufende Koordinaten
	double Y1 = double (pY[lIndex] - lYMin);
	double X2 = double (pX[lIndex+1] - lXMin);
	double Y2 = double (pY[lIndex+1] - lYMin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {	   // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) /
				(3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 *Y2)) /
				(3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;
		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	      // Schwerpunkt
		Ys += Ysi * Inh;
		dblF += Inh;		      // Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (dblF == 0.0) return FALSE;
	
	pszPt -> x = long ((Xs / dblF) + lXMin + 0.5);
	pszPt -> y = long ((Ys / dblF) + lYMin + 0.5);
	return TRUE;	
}

/////////////////////////////////////////////////////////////////////////////
// Berechnet für Punktobjekte die Verschiebung des Textobjekts, 
// so daß sichtbarer Punkt nicht überdeckt wird.
HRESULT CCreateTextBase::CorrectPointCoords (long lIdent, POINT *ppt)
{
	TX_ASSERT (NULL != ppt);
	TX_ASSERT (0 != lIdent);

HANDLEVISINFO HandleVisInfo;
PVISINFO PVisInfo;         

	INITSTRUCT(HandleVisInfo, HANDLEVISINFO); 
	HandleVisInfo.m_lONr = 0;		// Target (ObjektNummer)
	HandleVisInfo.m_lIdent = lIdent;	// Identifikator
	HandleVisInfo.m_iVTyp = VTPunkt;	// VisInfoTyp
	HandleVisInfo.m_fFlags = 0;			// zu ändern bzw. geändert
	HandleVisInfo.m_pDesc = NULL;		// beschreibender Text
	HandleVisInfo.m_pView = NULL;		// evtl. SichtName (aktuelle Sicht: NULL)
	HandleVisInfo.m_pVI = (VISINFO *)&PVisInfo;		// generischer Pointer auf VisInfo
	HandleVisInfo.m_hWnd = NULL;		// als ParentWindow verwenden	
		
	if (!DEX_GetIdentVisInfo(HandleVisInfo)) 
		return false;    // hole Visualisierungsinfo mit Punktgröße

double dMassStabVerh = 0;           

	DEX_GetActiveScaling(dMassStabVerh);			// Verhältnis des jetzigen aktuellen Maßstab zum allg. Bezugsmaßstabes 

long lcx = ((long)PVisInfo.m_Size.cx) * 100;		// Punktgröße in 1/100 mm im allg. Bezugsmaßstab
long lcy = ((long)PVisInfo.m_Size.cy) * 100;		// in x- u. y-Richtung
SIZE PixelDimPerMM = GetDotsPerMM();				// berechnet Pixel pro mm                            
long lMassStabVerh = (long)(dMassStabVerh * 1000 + 0.5);	// zum Umwandeln der double in long "*" u. "/ 1000 "  ?

// wenn Punktobjekt sehr groß, führt cast zu 0!
	if (0 == lMassStabVerh) lMassStabVerh = 1;	// 1/100 mm
	
	lcx = lcx / lMassStabVerh;			// berechnet erst aktuellen- aus Bezugsmaßstab 
	lcy = lcy / lMassStabVerh;			// von derzeitiger  Visualisierung der Punktobjekte in mm 
		
// dann von mm nach Pixel (wieviel x Pixel auf z mm)
	lcx = lcx * (long)PixelDimPerMM.cx;                  
	lcy = lcy * (long)PixelDimPerMM.cy; 

// Koordinatentransformation von DB-Koord. nach Pixel:
COORDCONVERT CoordConv;       
POINT pt;
long Pkt[2];

	CoordConv.lpPt = &pt;
	CoordConv.lpPkt = Pkt;

// übergebe die Koordinaten in DB-Koord., bekomme Pixel	
	CoordConv.lpPt -> x = 0; 
	CoordConv.lpPt -> y = 0;			// POINT
	CoordConv.lpPkt[0] = ppt -> x;			// Punkt Feld long!! aus DB.-Koord.
	CoordConv.lpPkt[1] = ppt -> y;
	DEX_OCtoDCEx (CoordConv);
		
// Koordinatentransformation von Pixel nach DB-Koord.:
	CoordConv.lpPt -> x = (int)(CoordConv.lpPt -> x + (long)lcx/20);	
	CoordConv.lpPt -> y = (int)(CoordConv.lpPt -> y + (long)lcy/20);
        
	CoordConv.lpPkt[0] = 0;				// Punkt Feld long!!
	CoordConv.lpPkt[1] = 0;
	
	DEX_DCtoOCEx (CoordConv);     
		
	ppt -> x = CoordConv.lpPkt[0];
	ppt -> y = CoordConv.lpPkt[1];
	return S_OK;					                  
}

/////////////////////////////////////////////////////////////////////////////
// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster 
SIZE CCreateTextBase::GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
SIZE dimD;

	dimD.cx = 0;
	dimD.cy = 0;

	if (hDC != NULL) 
		hDCloc = hDC;
	else
		hDCloc = ::GetDC (::GetDesktopWindow());

	switch (GetMapMode (hDCloc)) 
	{
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			dimD.cx = HorzRes/HorzSize; 
			dimD.cy = VertRes/VertSize; 
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		dimD.cx = 100;
		dimD.cy = 100;
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		dimD.cx = 10;
		dimD.cy = 10;
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		dimD.cx = 40;
		dimD.cy = 40;
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		dimD.cx = 4;
		dimD.cy = 4;
		break;
		
	case MM_TWIPS:
		dimD.cx = 57;
		dimD.cy = 57;
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) 
		::ReleaseDC (::GetDesktopWindow(), hDCloc);

	return dimD;
}

HRESULT CCreateTextBase::CreateRelation (LONG lONr, LONG lTxtONr)
{
MODRELATION MR;

	INITSTRUCT (MR, MODRELATION);
	MR.lPONr = lONr;
	MR.lSONr = lTxtONr;
	MR.lRCode = -1L;		// Begleitrelation
	MR.iRTyp = RTBegleitO;
	return (EC_OKAY == DEX_ModifyRelation (MR)) ? S_OK : E_FAIL;
}

BOOL CCreateTextBase::IsTextObject (LONG lONr)
{
int iOTyp = DEX_GetObjectType(lONr);

	return (OGText == iOTyp || OGLabel == iOTyp) ? TRUE : FALSE;
}

HRESULT CCreateTextBase::DeleteRelatedTextObject (LONG lONr, LONG lTxtONr, LONG *plIdent)
{
	if (NULL != plIdent)
		*plIdent = DEX_GetObjIdent(lTxtONr);

// Relation auflösen
DELRELATION DR;	                            

	INITSTRUCT(DR, DELRELATION);
	DR.lPONr = lONr;		// PrimärObjekt
	DR.lSONr = lTxtONr;		// SekundärObjekt
	DR.lRCode = -1L;		// RelationsCode
	DR.iRTyp = RTBegleitO;		// RelationsTyp
    DEX_DeleteRelation(DR);

// Objekt löschen
	DEX_DeleteObjectEx(lTxtONr);
	return S_OK;
}

HRESULT CCreateTextBase::ModifyRelatedTextObject (LONG lONr, LONG *plTxtONr, LPCSTR pcText)
{
// 1. Geometrie entsprechend ObjektTyp besorgen
TEXTGEOMETRIEEX OG;

	INITSTRUCT(OG, TEXTGEOMETRIEEX);
	RETURN_FAILED_HRESULT(FillObjectGeometrie (*plTxtONr, (OBJGEOMETRIE *)&OG));

	COM_TRY {
		if (bool(m_rStatus.m_fDynamic) ^ bool(OG.fIndObjProp)) {
		// dynamic-Status hat sich geändert, also vollkommen neu erzeugen
		long lIdent = 0L;
		POINT pt;

			pt.x = *(long *)OG.pdblX;
			pt.y = *(long *)OG.pdblY;

			THROW_FAILED_HRESULT(DeleteRelatedTextObject(lONr, *plTxtONr, &lIdent));
			THROW_FAILED_HRESULT(CreateRelatedTextObject(lONr, pcText, m_rStatus.m_fDynamic, lIdent, plTxtONr, &pt));
		} else {
		// lediglich Text modifizieren
		PUTTEXTDATAEX PT;

			INITSTRUCT(PT, PUTTEXTDATAEX);
			PT.m_lONr = *plTxtONr;
			PT.m_pcText = pcText;
			PT.m_fIndObjProp = OG.fIndObjProp;
			DEX_PutTextObjectText(PT);
		}

	} COM_CATCH_OP(FreeObjGeometrie((OBJGEOMETRIE *)&OG));

	FreeObjGeometrie((OBJGEOMETRIE *)&OG);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Einen Text gemäß Parametern erzeugen und selbigen als Resultat liefern
LONG CCreateTextDirect::operator() (LONG lONr)
{
	Tick();				// PI weiterschalten
	if (IsTextObject(lONr))
		return 0L;		// Textobjekte übergehen

LONG lTxtONr = 0L;

	if (m_rStatus.m_fDependend) {
	// abhängigen Text behandeln
		if (S_OK == GetRelatedObject (lONr, &lTxtONr)) {
		// Text existiert bereits

			if (m_rStatus.m_fDelete) {
			// existierende Text löschen und neu erzeugen
			LONG lIdent = 0L;

				if (FAILED(DeleteRelatedTextObject (lONr, lTxtONr, &lIdent)))
					return 0L;
			// Text existiert nicht mehr
				if (FAILED(CreateRelatedTextObject (lONr, m_strText.c_str(), m_rStatus.m_fDynamic, lIdent, &lTxtONr)))
					return 0L;

			} else {
			// existierende Texte wiederverwenden
				if (FAILED(ModifyRelatedTextObject (lONr, &lTxtONr, m_strText.c_str())))
					return 0L;
			}

		} else {
		// Text existiert noch nicht
			if (FAILED(CreateRelatedTextObject (lONr, m_strText.c_str(), m_rStatus.m_fDynamic, 0L, &lTxtONr)))
				return 0L;
		}
	} else {
	// Text nicht abhängig erzeugen
		if (FAILED(CreateTextObject (lONr, m_strText.c_str(), false, 0L, &lTxtONr)))
			return 0L;

		if (m_rStatus.m_fDeleteTarget)	// BezugsObjekt löschen
			DEX_DeleteObjectEx(lONr);
	}
	return lTxtONr;
}

LONG CCreateTextFromObjProp::operator() (LONG lONr)
{
	// PI weiterschalten
	Tick();
	TX_ASSERT(m_ObjProp.IsValid());

	COM_TRY {
	char cbBuffer[_MAX_PATH];
	HRESULT hr = m_ObjProp -> Eval (lONr, cbBuffer, sizeof(cbBuffer), NULL);

		if (m_rStatus.m_fDynamic) {
			if (FAILED(hr) && m_rStatus.m_fOnlyExistant)
				return 0L;

			m_strText = m_rStatus.m_strObjProp;	// Name der Objekteigenschaft
		} else {
			if (FAILED(hr)) 
				return 0L;
			m_strText = cbBuffer;				// Text für dieses Objekt setzen
		}

	} COM_CATCH_RETURN(0L);

// den Rest erledigt die Basisklasse
	return CCreateTextDirect::operator()(lONr);
}


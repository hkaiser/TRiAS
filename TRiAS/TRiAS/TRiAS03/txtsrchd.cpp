// TextRecherche parametrisieren

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/ComBool.h>

#include <funcs03.h>
#include <xtsnguid.h>
#include <srchguid.h>
#include <statguid.h>
#include <ospace/std/algorithm>

#include <ipropseq.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <SelObjPropDlg.h>

#include "TxtSrchD.h"
#include "TextSearchEngine.h"

extern char g_pDLLName[_MAX_PATH];
const int WM_SHOWREGEXPRMENU = WM_USER+1234;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DMatchString, IID_DMatchString);
DefineSmartInterface(MatchPlainText);					// WMatchPlainText
DefineSmartInterface(MatchRegExpr);						// WMatchRegExpr
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(EnumObjectsByNumber);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineSmartInterface2(DSearchObjects, IID_DSearchObjects);

// MenuKommandos verteilen
#define ON_REGEXPR_ID(uiID,pText)				case (uiID): OnRegExprCommand(pText); break
#define ON_REGEXPR_ID_MOVE(uiID,pText,iMove)	case (uiID): OnRegExprCommand(pText,iMove); break

///////////////////////////////////////////////////////////////////////////////
// 
#pragma warning (disable: 4355)

CCfgTextSearch::CCfgTextSearch (CTextSearchEngine *pParent, ResID uiDlg, LPCSTR pcCaption)
			   : CPropertyPage (uiDlg, pcCaption), 
			     m_SelRegExpr (this, IDC_INSERT_REGEXPR),
				 m_SelObjProp (this, IDC_SELECT_OBJPROP),
				 m_cbCapital (this, IDC_CAPITAL),
				 m_cbPartialMatch (this, IDC_PARTIALMATCH),
				 m_cbFuzzyMatch (this, IDC_FUZZYMATCH),
				 m_cbUseRegExpr (this, IDC_USEREGEXPR),
				 m_cbTestBOB (this, IDC_BEGINOFTEXT),
				 m_cbExistsOnly (this, IDC_EXISTSONLY),
				 m_cbNegate (this, IDC_NEGATE),
				 m_cbFindWhat (this, IDC_FINDWHAT),
				 m_sleObjProp (this, IDC_OBJPROPERTY),
				 m_ftSearch (this, IDT_SEARCH),
			     m_pParent(pParent)
{
	m_hMenu = NULL;
	m_pEdit = NULL;
	m_dwFlags = 0L;
	m_fIsInitialized = false;

	m_pStatus = NULL;
}

#pragma warning (default: 4355)

CCfgTextSearch::~CCfgTextSearch (void)
{
	DELETE_OBJ(m_pEdit);
}

CCfgTextSearch *CCfgTextSearch::CreateInstance (
			CTextSearchEngine *pParent, ResID uiDlg, LPCSTR pcCaption)
{
	try {
	CCfgTextSearch *pDlg = NULL;
	
		TX_TRY(pDlg = new CCfgTextSearch (pParent, uiDlg, pcCaption));
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;

	} catch (_com_error &) {
		return NULL;
	}
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CCfgTextSearch::WindowInit (Event)
{
	m_cbCapital.FInit();
	m_cbPartialMatch.FInit();
	m_cbFuzzyMatch.FInit();
	m_cbUseRegExpr.FInit();
	m_cbTestBOB.FInit();
	m_cbExistsOnly.FInit();
	m_cbNegate.FInit();
	m_ftSearch.FInit();

	m_cbCapital.SetChecked(false);
	m_cbPartialMatch.SetChecked(false);
	m_cbFuzzyMatch.SetChecked(false);
	m_cbUseRegExpr.SetChecked(false);
	m_cbTestBOB.SetChecked(false);
	m_cbExistsOnly.SetChecked (false);
	m_cbNegate.SetChecked (false);

	m_cbFindWhat.FInit();
	m_pEdit = new CComboEditWnd (this, m_cbFindWhat);

	m_sleObjProp.FInit();
	m_SelRegExpr.FInit();
	m_SelObjProp.FInit();

	if (m_SelRegExpr.LoadBitmaps (IDB_ARROW_DOWN, IDB_ARROW_DOWN_SEL, IDB_ARROW_DOWN_FOCUS, IDB_ARROW_DOWN_DISABLED))
	{
		m_SelRegExpr.SizeToContent(); 
	}
	if (m_SelObjProp.LoadBitmaps (IDB_ARROW_DOWN, IDB_ARROW_DOWN_SEL, IDB_ARROW_DOWN_FOCUS, IDB_ARROW_DOWN_DISABLED))
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
		m_cbCapital.SetChecked(m_pStatus -> m_fCapital);
		m_cbPartialMatch.SetChecked(m_pStatus -> m_fPartialMatch);
		m_cbFuzzyMatch.SetChecked(m_pStatus -> m_fFuzzyMatch);
		m_cbUseRegExpr.SetChecked(m_pStatus -> m_fUseRegExpr);
		m_cbTestBOB.SetChecked(m_pStatus -> m_fTestBOB);
		m_cbExistsOnly.SetChecked(m_pStatus -> m_fExistsOnly);
		m_cbNegate.SetChecked (m_pStatus -> m_fNegate ? true : false);

	// Liste der letzten SuchPatterns initialisieren
		if (m_pStatus -> m_strFindWhat.size() > 0) {
		int iIndex = m_cbFindWhat.AddString (m_pStatus -> m_strFindWhat.c_str());

			if (iIndex >= 0) 
				m_cbFindWhat.ChangeCurrentIndex(iIndex);
		}

		for (CSearchList::iterator it = m_pStatus -> m_lstFindWhat.begin();
			 it != m_pStatus -> m_lstFindWhat.end(); ++it)
		{
			if (!(*it == m_pStatus -> m_strFindWhat))
				m_cbFindWhat.AddString ((*it).c_str());
		}

	// Objekteigenschaft
		if (SUCCEEDED(RetrieveObjProp (m_pStatus -> m_strObjProp.c_str(), m_Props, m_ObjProp.ppi())))
			m_sleObjProp.SetText (m_pStatus -> m_strObjProp.c_str());
	}

	m_fIsInitialized = true;

	AdjustOK();
	AdjustCheckBoxes(m_cbUseRegExpr.isChecked());
}


HRESULT CCfgTextSearch::InitWithData (CCfgTextSearch::CDlgStatus &rStatus)
{
// Pointer auf StatusObjekt speichern
	m_pStatus = &rStatus;
	return S_OK;
}

void CCfgTextSearch::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_INSERT_REGEXPR:
		if (!m_cbExistsOnly.isChecked()) {
		Event e;

			e.Msg() = WM_SHOWREGEXPRMENU;
			PostEvent (e);
		}
		break;

	case IDC_SELECT_OBJPROP:
		ShowObjPropDlg();
		AdjustOK();
		break;

	case IDC_EXISTSONLY:
	case IDC_USEREGEXPR:
	case IDC_FUZZYMATCH:
	case IDC_PARTIALMATCH:
		AdjustCheckBoxes(m_cbUseRegExpr.isChecked());
		AdjustOK();
		break;
	}
}

LRESULT CCfgTextSearch::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SHOWREGEXPRMENU:	// Menu für RegExpr anzeigen
		ShowRegExprMenu();
		break;
	}
	return CPropertyPage::Dispatch(e);
}

// MenuKommandos vom RegExprMenu auswerten
void CCfgTextSearch::MenuCommand (MenuCommandEvt e)
{
	BEGIN_COMMANDS(e.GetItemID()) 
		ON_REGEXPR_ID(ID_ANYCHAR, TEXT("."));
		ON_REGEXPR_ID_MOVE(ID_CHARINRANGE, TEXT("[]"), -1);
		ON_REGEXPR_ID_MOVE(ID_CHARNOTINRANGE, TEXT("[^]"), -1);
		ON_REGEXPR_ID(ID_BEGINOFTEXT, TEXT("\\`"));
		ON_REGEXPR_ID(ID_LINEEND, TEXT("\\'"));
		ON_REGEXPR_ID(ID_BEGINOFLINE, TEXT("^"));
		ON_REGEXPR_ID(ID_ENDOFLINE, TEXT("$"));
		ON_REGEXPR_ID(ID_OR, TEXT("\\|"));
		ON_REGEXPR_ID(ID_ZEROORMORE, TEXT("*"));
		ON_REGEXPR_ID(ID_ONEORMORE, TEXT("+"));
		ON_REGEXPR_ID(ID_ZEROORONE, TEXT("?"));
		ON_REGEXPR_ID(ID_WORDBEGIN, TEXT("\\<"));
		ON_REGEXPR_ID(ID_WORDEND, TEXT("\\>"));
		ON_REGEXPR_ID(ID_WITHINWORD, TEXT("\\B"));
		ON_REGEXPR_ID(ID_WORDBOUNDARY, TEXT("\\b"));
		ON_REGEXPR_ID_MOVE(ID_GROUPTOKENS, TEXT("\\(\\)"), -2);
	END_COMMANDS;
}

int CCfgTextSearch::OnSetActive (NotifyEvt e)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen 
void CCfgTextSearch::OnCancel (NotifyEvt)
{
	return;// hier evtl. Aufräumarbeiten durchführen
}

int CCfgTextSearch::OnWizNext (NotifyEvt e)
{
	DoUpdate();
	return 0;
}

BOOL CCfgTextSearch::OnWizFinish (NotifyEvt e)
{
	DoUpdate();
//#if _MSC_VER < 1100
//	return true;
//#else
	return false;		// FIXED: Bug in PropertyChoice (FakeMfc.Ext)	
//#endif _MSC_VER < 1100
}

void CCfgTextSearch::EditChange (ControlEvt)
{
	AdjustOK();
}

void CCfgTextSearch::ListBoxSel (ControlEvt)
{
	AdjustOK();
}

// aktuelle Auswahl aus Controls in interne Variablen übernehemen
void CCfgTextSearch::DoUpdate (void)
{
	TX_ASSERT(NULL != m_pStatus);

	if (NULL == m_pStatus) return;

// Flags wegschreiben
	m_pStatus -> m_fCapital = m_cbCapital.isChecked();
	m_pStatus -> m_fPartialMatch = m_cbPartialMatch.isChecked();
	m_pStatus -> m_fFuzzyMatch = m_cbFuzzyMatch.isChecked();
	m_pStatus -> m_fUseRegExpr = m_cbUseRegExpr.isChecked();
	m_pStatus -> m_fTestBOB = m_cbTestBOB.isChecked();
	m_pStatus -> m_fExistsOnly = m_cbExistsOnly.isChecked();
	m_pStatus -> m_fNegate = m_cbNegate.isChecked() ? true : false;

// SuchStrings wegschreiben
char cbBuffer[_MAX_PATH+1];
int iMax = m_cbFindWhat.GetCount();

	m_pStatus -> erase();
	for (int i = 0; i < iMax && i < MAXLASTITEMS; i++) {
		if (m_cbFindWhat.GetString (cbBuffer, i, sizeof(cbBuffer)-1))
			m_pStatus -> m_lstFindWhat.push_back(os_string(cbBuffer));
	}

	m_cbFindWhat.GetText(cbBuffer, _MAX_PATH);
	m_pStatus -> m_strFindWhat = cbBuffer;

// Objekteigenschaft wegschreiben
	m_sleObjProp.GetText (cbBuffer, _MAX_PATH);
	m_pStatus -> m_strObjProp = cbBuffer;

// ausgewählte Objekteigenschaft im Kontext ablegen
WPropertyActionSequence Seq;
WDataObject CtxDO;

	if (SUCCEEDED(m_pParent -> GetSite(IID_IPropertyActionSequence, Seq.ppv())) &&
		SUCCEEDED(Seq -> GetSequenceContext (CtxDO.ppi())))
	{
		SetObjectProperty(CtxDO, cbBuffer);
	}
}

///////////////////////////////////////////////////////////////////////////////
// MenuCommands
BOOL CCfgTextSearch::OnRegExprCommand (LPCSTR pcInsert, int iMove)
{
	AddToSearchString (pcInsert, iMove);
	AdjustOK();
	AdjustCheckBoxes();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member

BOOL CCfgTextSearch::ShowRegExprMenu (void)
{
// Menu generieren und anzeigen
ResourceFile RF (g_pDLLName);
Menu RegExprMenu (ResID(IDR_REGEXPR, &RF));
HWND hWnd = Handle (API_CLIENT_HWND);
Rectangle rc;

	GetWindowRect (m_SelRegExpr.Handle(API_WINDOW_HWND), (RECT *)&rc);	
	m_hMenu = GetSubMenu (RegExprMenu.Handle(API_MENU_HMENU), 0);		// SubMenu holen

// rechts unten positionieren
BOOL fResult = TrackPopupMenu (m_hMenu, TPM_RIGHTALIGN, rc.Right(), rc.Bottom(), 0, hWnd, NULL);
	
	m_hMenu = NULL;
	return fResult;
}

BOOL CCfgTextSearch::ShowObjPropDlg (void)
{
// Objekteigenschaften lediglich einmal initialisieren
	TX_ASSERT(NULL != (IUnknown *)m_Props);
	if (!m_Props) return false;

CSelObjPropsDlg SelObjProps (this, m_Props);
char cbBuffer[_MAX_PATH];

	m_sleObjProp.GetText (cbBuffer, sizeof(cbBuffer)-1);
	m_ObjProp.Release();		// vorhergehende freigeben

	if (SelObjProps.FInit (cbBuffer)) {
	Point pt = m_sleObjProp.GetPosition();
	Dimension dim = SelObjProps.GetSize();

		pt.X() -= 1;
		pt.Y() -= dim.Height()+1;
		SelObjProps.ChangePosition (pt);
		
		SelObjProps.Show((ShowState)(Normal | NoParentDisabling));
		if (SelObjProps.Result()) {
		os_string str ("");

			SelObjProps.GetSelectedObjProp (str);
			if (SUCCEEDED(RetrieveObjProp (str.c_str(), m_Props, m_ObjProp.ppi())))
			{
				m_sleObjProp.SetText (str.c_str());

			// Typ der Objekteigenschaft bestimmen, bei Zahlen bringt es keinen Sinn,
			// Groß-/Kleinschreibung zu unterscheiden
			DWORD dwType = PROPCAPS_NONE;
			
				if (SUCCEEDED(m_ObjProp -> GetPropInfo(NULL, 0, &dwType)) &&
					dwType & (PROPCAPS_OBJPROPTYPE_INTEGER|PROPCAPS_OBJPROPTYPE_DOUBLE)) 
				{
					m_cbCapital.SetChecked(false);
					m_cbCapital.Disable();
				} else 
					m_cbCapital.Enable();
				return true;
			}
		}
	}
	return false;
}

// Finden einer bestimmten Objekteigenschaft
HRESULT CCfgTextSearch::RetrieveObjProp (
	LPCSTR pcName, IObjectProps *pIProps, IObjectProperty **ppIOP)
{
WEnumObjProps EnumProps;
HRESULT hr = pIProps -> EnumObjectProps (EnumProps.ppi());

	if (FAILED(hr)) return hr;
	return EnumProps -> FindByName (pcName, ppIOP);
}

void CCfgTextSearch::AdjustCheckBoxes(BOOL fRegExpr)
{
	if (!m_fIsInitialized) return;

// wenn lediglich Existenz getestet werden soll, dann alles andere
// passisvieren
	if (m_cbExistsOnly.isChecked()) {
	// CheckBox's pasivieren
		m_cbCapital.SetChecked(false);
		m_cbPartialMatch.SetChecked(false);
		m_cbFuzzyMatch.SetChecked(false);
		m_cbUseRegExpr.SetChecked(false);
		m_cbTestBOB.SetChecked(false);
		m_cbCapital.Disable();
		m_cbPartialMatch.Disable();
		m_cbFuzzyMatch.Disable();
		m_cbUseRegExpr.Disable();
		m_cbTestBOB.Disable();

	// Auswahl passivieren
		m_cbFindWhat.Disable();
		m_ftSearch.Disable();
		return;
	}

// ansonsten wie gehabt
	m_cbFindWhat.Enable();
	m_ftSearch.Enable();

	if (fRegExpr) {
		m_cbFuzzyMatch.SetChecked(false);
		m_cbFuzzyMatch.Disable();
		m_cbUseRegExpr.Enable();
		m_cbUseRegExpr.SetChecked (true);
		m_cbPartialMatch.Enable();
		m_cbCapital.Enable();
		m_cbTestBOB.SetChecked(false);
		m_cbTestBOB.Disable();
	} 
	else if (m_cbFuzzyMatch.isChecked()) {
		m_cbUseRegExpr.SetChecked(false);
		m_cbUseRegExpr.Disable();
		m_cbPartialMatch.SetChecked(false);
		m_cbPartialMatch.Disable();
		m_cbTestBOB.SetChecked(false);
		m_cbTestBOB.Disable();
		m_cbCapital.SetChecked(false);
		m_cbCapital.Disable();
	} 
	else {
		m_cbCapital.Enable();
		m_cbFuzzyMatch.Enable();
		m_cbPartialMatch.Enable();
		if (m_cbPartialMatch.isChecked())
			m_cbTestBOB.Enable();
		else
			m_cbTestBOB.Disable();
		m_cbUseRegExpr.Enable();
		m_cbUseRegExpr.SetChecked (false);
	}
}

void CCfgTextSearch::AddToSearchString (LPCSTR pcAdd, int iMoveCursor)
{
Selection s = m_pEdit -> GetLastSelection();
int iLen = m_cbFindWhat.GetTextLen();

	try {
	int iAddLen = strlen(pcAdd);
	char *pBuffer = new char [iLen+iAddLen+1];

		m_cbFindWhat.GetText (pBuffer, iLen+1);
		pBuffer[iLen] = '\0';

	string str = pBuffer;

		delete pBuffer;
		if (iLen > 0)
			str.replace (s.Start(), s.End()-s.Start(), pcAdd);
		else 
			str = pcAdd;

	// Control während der Änderungen nicht zeichnen
	HWND hCtrl = m_cbFindWhat.Handle();

		SendMessage (hCtrl, WM_SETREDRAW, false, 0);
		m_cbFindWhat.SetFocus();
		m_cbFindWhat.SetText (str.c_str());
		s.Start() = s.End() = s.Start()+iAddLen+iMoveCursor;
		m_cbFindWhat.ChangeEditSelection (s);

	// jetzt alles mit einem mal zeichnen
		SendMessage (hCtrl, WM_SETREDRAW, true, 0);
		InvalidateRect (hCtrl, NULL, true);

	} catch (...) {
		;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Buttons richten 
BOOL CCfgTextSearch::AdjustOK (void)
{
	if (!m_fIsInitialized) return false;

// Knöpfe des Dialoges richten (Next, Previous, Finish)
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if ((-1 != m_cbFindWhat.GetCurrentIndex() || 0 < m_cbFindWhat.GetTextLen() || m_cbExistsOnly.isChecked()) && 
		0 < m_sleObjProp.GetTextLen()) 
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
// Generieren des entsprechenden Match-Objektes
HRESULT CCfgTextSearch::GetMatchObject (DMatchString **ppIMatch)
{
	if (NULL == ppIMatch) return E_POINTER;

	TX_ASSERT(m_fIsInitialized);
	TX_ASSERT(NULL != m_pStatus);

	if (NULL == m_pStatus) return E_UNEXPECTED;
	if (!m_fIsInitialized) return E_UNEXPECTED;

// je nach gewählten Optionen das richtige MatchObjekt generieren
WDMatchString Match;

	COM_TRY {
		if (m_pStatus -> m_fUseRegExpr) {
		// mit RegularExpressions suchen
			TX_ASSERT(!m_pStatus -> m_fExistsOnly);

			Match = WDMatchString (CLSID_MatchRegExprExakt);
			WMatchRegExpr(Match) -> put_FullMatch (CComBool(!m_pStatus -> m_fPartialMatch));
		} 
		else if (m_pStatus -> m_fFuzzyMatch) {
		// ungefähres Matching
			Match = WDMatchString (CLSID_MatchFuzzy);
		} 
		else {
		// Text vollständig wiederfinden (bzw. Textanfang)
			Match = WDMatchString (CLSID_MatchPlainTextExakt);

		WMatchPlainText MatchTxt(Match);

			MatchTxt -> put_ExistanceOnly (CComBool(m_pStatus -> m_fExistsOnly));
			MatchTxt -> put_FullMatch (CComBool(!m_pStatus -> m_fPartialMatch));
			MatchTxt -> put_TestBOB (CComBool(m_pStatus -> m_fTestBOB));
		}

	// zu suchenden Text setzen
	CComBSTR bstrMatch (m_pStatus -> m_strFindWhat.c_str());

		THROW_FAILED_HRESULT(Match -> put_MatchText (bstrMatch));
		THROW_FAILED_HRESULT(Match -> put_MatchCase (CComBool(!m_pStatus -> m_fCapital)));
		THROW_FAILED_HRESULT(Match -> put_NegateMatch (CComBool(m_pStatus -> m_fNegate)));

	} COM_CATCH;
	
	*ppIMatch = Match.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Abfragen der ausgewählten Objekteigenschaft
HRESULT CCfgTextSearch::GetMatchProperty (IObjectProperty **ppIOP)
{
	if (NULL == ppIOP) return E_POINTER;
	if (!m_ObjProp) return E_UNEXPECTED;	// not initialized yet

WObjectProperty OProp (m_ObjProp);

	*ppIOP = OProp.detach();
	return S_OK;
}

HRESULT CCfgTextSearch::ResetEnumLONG (void)
{
	m_Objects.Clear();
	return S_OK;
}

HRESULT CCfgTextSearch::SetEnumLONG (IEnum<LONG> *pIEnumObjs)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	try {
	OutEnumLONG iter_out (&m_Objects);		// throws hr

		copy (InEnumLONG(pIEnumObjs), InEnumLONG(), iter_out);
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} catch (...) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// hier passiert die eigentliche Recherche
const int SEARCH_BUFFERSIZE = 2048;

// PredikatKlasse, die die eigentliche Recherche im 'remove_copy_if' -
// Algorithmus durchführt
class CSearch 
{
private:
	WDMatchString m_Match;
	WObjectProperty m_ObjProp;
	char *m_pBuffer;
	bool m_fNotNegate;

public:
	CSearch (DMatchString *pIMatch, IObjectProperty *pIObjProp) : 
			m_Match(pIMatch), m_ObjProp(pIObjProp), m_fNotNegate(true)
	{ 
	CComBool fNegate;

		if (SUCCEEDED(m_Match -> get_NegateMatch (&fNegate)))
			m_fNotNegate = bool(!fNegate);
		ATLTRY(m_pBuffer = new char[SEARCH_BUFFERSIZE]); 
	} 
	~CSearch (void) { delete m_pBuffer; }

	BOOL operator() (LONG lONr)	throw(_com_error &) 	// zu untersuchendes Objekt
	{
		m_pBuffer[0] = '\0';	// für alle Fälle

	HRESULT hr = m_ObjProp -> Eval (lONr, m_pBuffer, SEARCH_BUFFERSIZE-1, NULL);

		if (hr == E_FAIL)			// Objekt unterstützt diese OE nicht
			return m_fNotNegate;	// gematched/nicht gematched hängt nur von NegateState ab

		THROW_FAILED_HRESULT(hr);	// sonstiger Fehler, nicht wieder rufen

	int iResult = 0;
	CComBSTR bstrMatch (m_pBuffer);
		
		m_Match -> MatchString (bstrMatch, &iResult);
		return iResult != 0 ? false : true;		// gematched oder auch nicht
	// false heißt gematched, true heißt nicht in Ausgabemenge übernehmen
	}
};

// JG 980916*/
// diese Klasse entspricht CSearch kann aber mit einem ProgressIndicator umgehen
// Die neue Klasse wird angelegt, um Seiteneffekte zu vermeiden
class CSearchExt:
	public CSearch,
	public CPropertyActionExtUsage
{
public:
	CSearchExt (DMatchString *pIMatch, 
				IObjectProperty *pIObjProp, 
				IProgressIndicatorUsage *pPa = NULL) : 
		CSearch(pIMatch, pIObjProp),
		CPropertyActionExtUsage(pPa)
	{
	}
	BOOL operator() (LONG lONr)	throw (_com_error &)
	{
		Tick();									// ProgInd handeln
		if (FAILED(GoOn()))
			_com_issue_error(E_ABORT);
		return CSearch::operator() (lONr);		// und eigentliche Action ausführen
	}
};

HRESULT CCfgTextSearch::GetEnumLONG (IEnum<LONG> **ppIEnumObjs)
{
	if (NULL == ppIEnumObjs) return E_POINTER;

	*ppIEnumObjs = NULL;
	COM_TRY {
	// neuen Enumerator anlegen und füllen
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);
	OutEnumLONG iter_out ((IEnum<LONG> *)EnumOut);		// throws hr
	WObjectProperty ObjProp;

		THROW_FAILED_HRESULT(GetMatchProperty (ObjProp.ppi()));

	// zuerst versuchen, die OP dazu zu überreden, selbst eine Objektmenge
	// zu erzeugen
		try {
		WEnumObjectsByNumber Enum2nd;

			THROW_FAILED_HRESULT(TryToSearch (ObjProp, m_Objects.Count(), Enum2nd.ppi()));

		// Schnittmenge zwischen Eingabemenge und Recherchergebnis bilden
		WEnumLONG Objs2nd (Enum2nd);		// throws hr

			try {
				set_intersection(InEnumLONG(&m_Objects), InEnumLONG(),
								 InEnumLONG((IEnum<LONG> *)Objs2nd), InEnumLONG(), 
								 iter_out);
			} catch (_com_error& hr) {
				return _COM_ERROR(hr);		// Fehler in set_intersection
			}

			*ppIEnumObjs = (IEnum<LONG> *)EnumOut.detach();		// übernimmt RefCnt

		// JG 980916 ProgInd handeln
			SetMaxTicks(1);
			TickToEnd();

			return S_OK;	// das wars, und es war der letzte

		} catch (_com_error&) {
			;		// erster Versuch einfach fehlgeschlagen
		}

	// alle Objekte in m_Objects auf Recherchekriterium prüfen und bei
	// positivem Test in iter_out ausgeben
		{
		WDMatchString Match;

			THROW_FAILED_HRESULT(GetMatchObject (Match.ppi()));

		// JG PI handlen
			SetMaxTicks(m_Objects.Count());

		// Suche initialisieren
			{
			// alle Objekte der Eingabemenge durchgehen und auf Match testen
				remove_copy_if(InEnumLONG(&m_Objects), InEnumLONG(), 
							   iter_out, CSearchExt(Match, ObjProp, this));	// JG erweiterten Comparator anlegen
			}
			*ppIEnumObjs = (IEnum<LONG> *)EnumOut.detach();		// übernimmt RefCnt
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT)
	
// explizit PrgIndicator auf 100%
	TickToEnd();
	return S_OK;	// das wars, und es war der letzte
}

static SEARCHMODE GetSearchMode (CCfgTextSearch::CDlgStatus *pStatus)
{
SEARCHMODE rgFlags = SEARCHMODE_NORMAL;

	if (pStatus -> m_fExistsOnly) {
		rgFlags = SEARCHMODE_ONLYEXISTANCE;
		if (pStatus -> m_fNegate)
			rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_NEGATERESULT);
		return rgFlags;
	}

	if (pStatus -> m_fUseRegExpr)
		rgFlags = SEARCHMODE_REGEXPR;
	else if (pStatus -> m_fFuzzyMatch) 
		rgFlags = SEARCHMODE_LIKE;

	if (pStatus -> m_fPartialMatch) {
		rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_PARTIALMATCH);
		if (pStatus -> m_fTestBOB)
			rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_PARTIALMATCHBOB);
	}
	if (pStatus -> m_fCapital)
		rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_NOMATCHCASE);

	if (pStatus -> m_fNegate)
		rgFlags = (SEARCHMODE)(rgFlags | SEARCHMODE_NEGATERESULT);

	return rgFlags;
}

HRESULT CCfgTextSearch::TryToSearch (
	IObjectProperty *pIOP, ULONG ulCnt, IEnumObjectsByNumber **ppIEnum)
{
	TX_ASSERT(NULL != m_pStatus);
	TX_ASSERT(m_fIsInitialized);

	if (!m_fIsInitialized) return E_UNEXPECTED;
	if (NULL == m_pStatus) return E_UNEXPECTED;

	try {
	WDSearchObjects Search (pIOP);		// throws hr
	CComBSTR bstrMatch (m_pStatus -> m_strFindWhat.c_str());
	SEARCHMODE rgFlags = GetSearchMode(m_pStatus);
	HRESULT hr = Search -> ConsiderSearch(bstrMatch, rgFlags, ulCnt);

		if (FAILED(hr)) _com_issue_error(hr);		// Fehler
		if (S_OK != hr) _com_issue_error(E_FAIL);	// implementiert aber nicht zu empfehlen

		THROW_FAILED_HRESULT(Search -> SearchObjects(bstrMatch, rgFlags, ppIEnum));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

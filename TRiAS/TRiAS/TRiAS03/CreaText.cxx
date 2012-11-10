// Dialog, welcher Objekteigenschaft etc. auswählt, um Texte zu erzeugen
// File: CREATEXT.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs02.h>
#include <funcs03.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>

#include <eieruhr.hxx>

#include "CreaText.hxx"
#include "TxtObPrp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CCreateTextObjectsDlg :: CCreateTextObjectsDlg (
		CCreateTextObjectsPropAct *pParent, ResID uiDlg, LPCSTR pcCaption)
	: CPropertyPage (uiDlg, pcCaption),
	  m_cbAddToView (this, IDC_ADDTOVIEW),
	  m_pbDefine (this, IDC_DEFINENEW),
	  m_dwFlags(0), m_pParent(pParent)
{
	m_pProps = NULL;	// TreeView

	m_fCreateDependend = false;
	m_fDeleteExistent = false;
	m_fDoNotMove = false;
}

#pragma warning (default: 4355)

CCreateTextObjectsDlg :: ~CCreateTextObjectsDlg (void)
{
	DELETE (m_pProps);
}

CCreateTextObjectsDlg *CCreateTextObjectsDlg :: CreateInstance (
		CCreateTextObjectsPropAct *pParent, ResID resID, LPCSTR pcCaption)
{
	try {
	CCreateTextObjectsDlg *pDlg = NULL;
	
		pDlg = new CCreateTextObjectsDlg (pParent, resID, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (bad_alloc) {
		return NULL;
	}
}

bool CCreateTextObjectsDlg :: FInit (void)
{
// IdentifikatorListBox füllen
	try {

		m_pProps = new CSelObjPropTree (this, IDC_OBJECTPROPS);
	
	} catch (bad_alloc) {
		return false;
	}
	return true;
}

void CCreateTextObjectsDlg :: SetFlags (DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CCreateTextObjectsDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
	if (NULL == m_pProps || 
		!m_pProps -> InitControl(OTPunkt|OTLinie|OTFlaeche|OTText, 
								  SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD,
								  NULL, CmpEntries, reinterpret_cast<DWORD>(m_pProps)))
	{
		return;
	}
	
	try {
		EnumObjs = WEnumObjectsByNumber(CLSID_EnumObjectsByNumber);

	} catch (_com_error&) {
		return;
	}
		
	m_cbCreateDependend.FInit();
	m_rbDeleteExistent.FInit();
	m_rbReplaceExistent.FInit();
	m_cbDoNotMove.FInit();

	m_cbCreateDependend.SetChecked (true);
	m_rbDeleteExistent.SetState (true);
	m_rbReplaceExistent.SetState (false);
	m_cbDoNotMove.SetChecked (true);

	AdjustOK();

// vorhergehende Einstellungen wieder einstellen
/*	if (0 != m_lResult) {
	int iIndex = SelectIdent (m_lResult);

		if (-1 != iIndex) {	// Focus setzen, ins Bild rollen
			m_pProps -> EnsureVisible (iIndex, false);
			m_pProps -> SelectItemFocus (iIndex);
		}
		m_cbAddToView.SetChecked (m_fAddToView);
	}
*/
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CCreateTextObjectsDlg :: OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = static_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustOK();
	}
}

int CCreateTextObjectsDlg :: OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CCreateTextObjectsDlg :: OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CCreateTextObjectsDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 	// Ergebnisse zwischenspeichern
		return 0;

	return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CCreateTextObjectsDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}

// HilfeRoutine ---------------------------------------------------------------
void CCreateTextObjectsDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

///////////////////////////////////////////////////////////////////////////////
// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CCreateTextObjectsDlg :: GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) return E_POINTER;
	if (!EnumObjs) return E_OUTOFMEMORY;

// IEnumLONG abfragen
	return EnumObjs -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppIEnum);
}

// Übergibt die zu verarbeitende Objektmenge ----------------------------------
HRESULT CCreateTextObjectsDlg :: SetEnumLONG (IEnumObjectsByNumber *pIEnum)
{
LONG lONr;
ResourceFile RF (g_pDLLName);
ResString resUndo (ResID(IDS_UNDOMODIDENTS, &RF), 128);

	DEX_BeginUndoLevel(resUndo.Addr());

	for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) {
	// do actions
	// ...
	// und zu lokalem Enumerator aller umklassifizieren Objekte hinzufügen
		EnumObjs -> AddItem (lONr);
	}

	DEX_EndUndoLevel();
	DEX_RefreshLegend();
	DEX_RepaintLegend();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CCreateTextObjectsDlg :: AdjustOK (bool fDisableNext)
{
DWORD dwBttns = 0;
int iCnt = m_pProps -> GetSelectedCount();

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (0 < iCnt && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CCreateTextObjectsDlg :: PrepareResult (void)
{
// Daten (Ident) aus Page lesen und speichern
	if (!GetSelectedIdent (m_lResult))
		return false;

	TX_ASSERT(IsValidIdent(m_lResult));

	m_fAddToView = m_cbAddToView.isChecked() ? true : false;

return true;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CCreateTextObjectsDlg :: GetSelectedIdent (long &rlIdent)
{
short iOTyp = 0;	// dummy

	if (m_pProps) 
		return m_pProps -> GetFirstIdent (rlIdent, iOTyp);
		
	return false;
}

int CCreateTextObjectsDlg :: GetItemCount (void)
{
	if (m_pProps) 
		return m_pProps -> GetItemCount();
		
	return 0;
}

int CCreateTextObjectsDlg :: SelectIdent (long lIdent, bool fSel)
{
	if (m_pProps) {
	int fResult = m_pProps -> SelectIdent (lIdent, 0, fSel);

		AdjustOK();
		return fResult;
	} else if (fSel)
		m_lResult = lIdent;		// lediglich vormerken
		
	return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CCreateTextObjectsDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}

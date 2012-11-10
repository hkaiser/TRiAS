// Auswahl der RechercheErgebnisse --------------------------------------------
// File: RECHRES.HXX

#include "triaspre.hxx"

#include <selidlst.hxx>
#include <registry.hxx>
#include <propname.hxx>
#include <SelObjPropDlg.h>

#include "triasres.h"
#include "strings.h"
#include "TRiASMode.h"

#include "rechres.h"
#include "rechres.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CRechResultDlg *CRechResultDlg::CreateInstance (
	pWindow pW, DatenBasisObjekt &rDBO, IObjectProps *pProps)
{
// CEierUhr Wait (pW);
CRechResultDlg *pDlg = new CRechResultDlg (pW, rDBO);

	if (pDlg == NULL || !pDlg -> FInit(pProps)) {
		DELETE_OBJ (pDlg);
		return NULL;
	}
	return pDlg;
}

#pragma warning(disable: 4355)

CRechResultDlg::CRechResultDlg (pWindow pW, DatenBasisObjekt &rDBO)
		: DialogWindow (pW, RECHRESULTDLG), m_rDBO(rDBO),
		  m_cbDataTips (this, IDC_SHOWDATATIP),
		  m_cbDataSource (this, IDC_DATASOURCE),
		  m_cbIdent (this, IDCB_RECHRES_IDENT),
		  m_cbObjTyp (this, IDCB_RECHRES_OBJTYP),
		  m_cbObjProp (this, IDC_OBJECTPROPERTY),
 		  m_pbOK (this, IDOK),
		  m_pbSelAll (this, IDB_RECHRES_SELALL),
		  m_rbObjTyp (this, IDR_RECHRES_OTYP),
		  m_rbIdent (this, IDR_RECHRES_IDENT),
		  m_rbOProp (this, IDR_RECHRES_OBJPROP),
		  m_SelObjProp (this, IDC_SELECT_OBJPROP),
		  m_sleObjProp (this, IDC_OBJPROPERTY),
		  m_pIdents (NULL)
{
	m_fHideFlags = 0;
	m_fSortFlags = 0;
	m_fHideDataTips = 0;

	m_cbIdent.SetChecked (true);
	m_cbObjTyp.SetChecked (true);
	m_cbObjProp.SetChecked (false);

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) 
		m_cbDataSource.SetChecked (true);
	else {
		m_cbDataSource.Disable();
		m_cbDataSource.Hide();
	}
	AdjustRadios (0);
}

#pragma warning(default: 4355)

CRechResultDlg::~CRechResultDlg (void)
{
	DELETE_OBJ (m_pIdents);
}

bool CRechResultDlg::FInit (IObjectProps *pProps)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListViewWindow (this, IDL_SHOWIDENTSLIST);
	if (m_pIdents == NULL) return false;

// Identifikatoren laden, Zuordnungsobjektklassen nicht anzeigen
DWORD dwMode = SELIDMODE_SINGLETYPE|SELIDMODE_NOQUERYDEFS;

	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) 
		dwMode |= SELIDMODE_SHOWCONNECTIONS;

	m_pIdents -> FInit();
	(*m_pIdents) -> InitControl (OTPunkt|OTLinie|OTFlaeche|OTText, dwMode, NULL, CmpEntries); 

// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = (*m_pIdents) -> GetExtendedStyle();

		(*m_pIdents) -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);
	}
#endif 

// Controls initialisieren
	if ((*m_pIdents) -> GetItemCount() > 0) 
		m_pbSelAll.Enable();		// Button SelectAll richten
	
// BmpButton fertig initialisieren
	if (m_SelObjProp.LoadBitmaps (IDB_ARROW_DOWN, IDB_ARROW_DOWN_SEL, IDB_ARROW_DOWN_FOCUS, IDB_ARROW_DOWN_DISABLED))
	{
		m_SelObjProp.SizeToContent(); 
	}

// Objekteigenschaften zwischenspeichern
	m_Props = pProps;
	if (NULL == pProps) {
		m_cbObjProp.SetChecked(false);
		m_cbObjProp.Disable();
		m_sleObjProp.Disable();
		m_SelObjProp.Disable();
	}

	m_cbDataTips.Disable();
	return true;
}

void CRechResultDlg::SetHideFlags (DWORD iHideFlags)
{
// Voreinstellungen einlesen
	m_fHideFlags = iHideFlags & ROHideFlags;
	m_fSortFlags = iHideFlags & ROSortFlags;
	m_fHideDataTips = iHideFlags & ROHideDataTips;

	m_cbIdent.SetChecked (!(iHideFlags & ROHideIdent));
	m_cbObjTyp.SetChecked (!(iHideFlags & ROHideObjTyp));
	m_cbDataSource.SetChecked (!(iHideFlags & ROHideDatasource));
	m_cbDataTips.SetChecked (m_fHideDataTips & ROHideDataTips ? FALSE : TRUE);

	AdjustRadios (m_fSortFlags);
}

// EventHandler ---------------------------------------------------------------
void CRechResultDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (true);
		break;
		
	case IDCANCEL:
		EndDlg (false);
		break;
		
	case IDCB_RECHRES_IDENT:
		m_fHideFlags &= ~ROHideIdent;
		if (!m_cbIdent.isChecked())
			m_fHideFlags |= ROHideIdent;
		break;

	case IDCB_RECHRES_OBJTYP:
		m_fHideFlags &= ~ROHideObjTyp;
		if (!m_cbObjTyp.isChecked())
			m_fHideFlags |= ROHideObjTyp;
		break;

	case IDC_DATASOURCE:
		m_fHideFlags &= ~ROHideDatasource;
		if (!m_cbDataSource.isChecked())
			m_fHideFlags |= ROHideDatasource;
		break;

	case IDC_SHOWDATATIP:
		m_fHideDataTips &= ~ROHideDataTips;
		if (!m_cbDataTips.isChecked())
			m_fHideDataTips |= ROHideDataTips;
		break;

	case IDB_RECHRES_SELALL:	// alle Klassen auswählen
		(*m_pIdents) -> ChangeSelectedAll(true);
		AdjustOK();
		break;

	case IDR_RECHRES_OTYP:
		m_fSortFlags = ROSortObjTyp;
		break;

	case IDR_RECHRES_IDENT:
		m_fSortFlags = ROSortIdent;
		break;

	case IDR_RECHRES_OBJPROP:
		m_fSortFlags = ROSortText;
		break;

	case IDC_OBJECTPROPERTY:
		if (!m_cbObjProp.isChecked()) {
			m_strActOProp = GetActOProp();
			m_sleObjProp.SetText (g_cbNil);
			m_cbDataTips.SetChecked(false);
			m_cbDataTips.Disable();
		} else if (m_strActOProp.size() > 0)
			SetActOProp (m_strActOProp.c_str());
		break;

	case IDC_SELECT_OBJPROP:
		ShowObjPropDlg();
		AdjustOK();
		break;
	}
}

// Ein Eintrag wurde aus der Liste gelöscht -----------------------------------
void CRechResultDlg::OnDeleteItem (NotifyEvt e)
{
NM_LISTVIEW *pNLV = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (0 == pNLV -> iSubItem)	// ItemData freigeben
		(*m_pIdents) -> OnDeleteItem (pNLV);
}

void CRechResultDlg::OnDeleteAllItems (NotifyEvt)
{
	(*m_pIdents) -> OnDeleteAllItems();
}

LRESULT CRechResultDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_NOTIFY:
		if (OnNotify((NotifyEvt &)e))
			return TRUE;
		break;

	default:
		break;
	}
	return DialogWindow::Dispatch(e);
}

BOOL CRechResultDlg::OnNotify (NotifyEvt e)
{
	if (IDL_SHOWIDENTSLIST != (uint)e.GetControlID())
		return FALSE;

	if (NM_CLICK == ((NMHDR *)e.LParam()) -> code)
		AdjustOK();
	return FALSE;	// trotzdem weiterleiten
}

// AbfrageRoutinen ------------------------------------------------------------
bool CRechResultDlg::GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetFirstIdent (rlIdent, riOTyp);
	return false;
}


bool CRechResultDlg::GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetNextIdent (rlIdent, riOTyp);
	return false;
}


bool CRechResultDlg::SelectIdents (long lIdent, short iOTyp)
{
	if (m_pIdents) {
		if (iOTyp & OTPunkt) 
			(*m_pIdents) -> SelectIdent (lIdent, OTPunkt, true);
		if (iOTyp & OTLinie) 
			(*m_pIdents) -> SelectIdent (lIdent, OTLinie, true);
		if (iOTyp & OTFlaeche) 
			(*m_pIdents) -> SelectIdent (lIdent, OTFlaeche, true);
		if (iOTyp & OTText) 
			(*m_pIdents) -> SelectIdent (lIdent, OTText, true);

		AdjustOK();
		return true;
	}
	return false;
}

// HilfsRoutinen --------------------------------------------------------------
void CRechResultDlg::AdjustOK (void)
{
	if (!m_pIdents || 0 == GetNoSelected())
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}

void CRechResultDlg::AdjustRadios (short iSort)
{
// erstmal alles rücksetzen
	m_rbObjTyp.SetState (false);
	m_rbIdent.SetState (false);
	m_rbOProp.SetState (false);
	
	if (!(iSort & ROSortFlags) || iSort & ROSortDatasource)
		iSort = RODefaultFlags;	// default ist nach OKS sortieren

	if (iSort & ROSortObjTyp) m_rbObjTyp.SetState (true);
	if (iSort & ROSortIdent) m_rbIdent.SetState (true);
	if (iSort & ROSortText) m_rbOProp.SetState (true);
}

string CRechResultDlg::GetActOProp (void)
{
char cbBuffer[_MAX_PATH+1];

	m_sleObjProp.GetText (cbBuffer, _MAX_PATH);
	return string(cbBuffer);
}

void CRechResultDlg::SetActOProp (LPCSTR pcName)
{
// Objekteigenschaft
	if (SUCCEEDED(RetrieveObjProp (pcName, m_Props, m_ObjProp.ppi()))) {
		m_sleObjProp.SetText (pcName);
		m_cbObjProp.SetChecked (true);
		m_cbDataTips.Enable();
		m_cbDataTips.SetChecked (m_fHideDataTips & ROHideDataTips ? FALSE : TRUE);
		m_strActOProp = pcName;
	}
}

BOOL CRechResultDlg::ShowObjPropDlg (void)
{
// Objekteigenschaften lediglich einmal initialisieren
	TX_ASSERT(m_Props.IsValid());
	if (!m_Props) return false;

CSelObjPropsDlg SelObjProps (this, m_Props);
char cbBuffer[64];

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
		string str;

			SelObjProps.GetSelectedObjProp (str);
			if (SUCCEEDED(RetrieveObjProp (str.c_str(), m_Props, m_ObjProp.ppi())))
			{
				m_sleObjProp.SetText (str.c_str());
				m_cbObjProp.SetChecked(true);
				m_cbDataTips.Enable();
				m_cbDataTips.SetChecked ((m_fHideDataTips & ROHideDataTips) ? FALSE : TRUE);
				AdjustOK();
				return true;
			}
			m_cbDataTips.SetChecked (false);
			m_cbDataTips.Disable();
		}
	}
	return false;
}

// Finden einer bestimmten Objekteigenschaft
HRESULT CRechResultDlg::RetrieveObjProp (
	LPCSTR pcName, IObjectProps *pIProps, IObjectProperty **ppIOP)
{
WEnumObjProps EnumProps;
HRESULT hr = pIProps -> EnumObjectProps (EnumProps.ppi());

	if (FAILED(hr)) return hr;
	return EnumProps -> FindByName (pcName, ppIOP);
}


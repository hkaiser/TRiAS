// Auswahl der RechercheErgebnisse --------------------------------------------
// File: RECHRES.HXX

#include "triaspre.hxx"

#include <selidlst.hxx>
#if defined(WIN32)
#include <registry.hxx>
#include <propname.hxx>
#endif // WIN32

#include "triasres.h"
#include "strings.h"

#include "rechres.h"
#include "rechres.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CRechResultDlg *CRechResultDlg :: CreateInstance (
	pWindow pW, DatenBasisObjekt &rDBO, LPENUMOBJPROPS pEnum)
{
// CEierUhr Wait (pW);
CRechResultDlg *pDlg = new CRechResultDlg (pW, rDBO);

	if (pDlg == NULL || !pDlg -> FInit(pEnum)) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}

#pragma warning(disable: 4355)

CRechResultDlg :: CRechResultDlg (pWindow pW, DatenBasisObjekt &rDBO)
		: DialogWindow (pW, RECHRESULTDLG), m_rDBO(rDBO),
		  m_cbObjNr (this, IDCB_RECHRES_OBJNR),
		  m_cbIdent (this, IDCB_RECHRES_IDENT),
		  m_cbObjTyp (this, IDCB_RECHRES_OBJTYP),
#if !defined(WIN32)
		  m_pbHelp (this, IDB_RECHRES_HELP),
#endif // WIN32
		  m_pbOK (this, IDOK),
		  m_pbSelAll (this, IDB_RECHRES_SELALL),
		  m_rbObjNr (this, IDR_RECHRES_ONR),
		  m_rbObjTyp (this, IDR_RECHRES_OTYP),
		  m_rbIdent (this, IDR_RECHRES_IDENT),
		  m_rbOProp (this, IDR_RECHRES_OBJPROP),
		  m_cbObjProps (this, IDC_RECHRES_OBJPROPS),
		  m_pIdents (NULL)
{
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32
	m_fHideFlags = 0;
	m_fSortFlags = 0;
	
	m_cbObjNr.SetChecked (true);
	m_cbIdent.SetChecked (true);
	m_cbObjTyp.SetChecked (true);

	AdjustRadios (0);
}

#pragma warning(default: 4355)

CRechResultDlg :: ~CRechResultDlg (void)
{
	DELETE (m_pIdents);
}

bool CRechResultDlg :: FInit (LPENUMOBJPROPS pIEnumOPs)
{
// IdentifikatorListBox füllen
	m_pIdents = CSelIdentList :: CreateInstance (this, IDL_SHOWIDENTSLIST);
	if (m_pIdents == NULL) return false;
	
short iCnt = m_pIdents -> GetCount();

// Button SelectAll richten
	if (iCnt) m_pbSelAll.Enable();
	
	if (NULL == pIEnumOPs) 
		m_cbObjProps.Disable();
	else {
	// Objekteigenschaften in ComboBox setzen
	LPOBJECTPROPERTY pIOP = NULL;

		for (pIEnumOPs -> Reset(); 
		     S_OK == pIEnumOPs -> Next(1, (LPUNKNOWN *)&pIOP, NULL); )
		{
		char cbBuffer[_MAX_PATH];

			pIOP -> GetPropInfo(cbBuffer, _MAX_PATH, NULL);
			pIOP -> Release();

#if defined(WIN32)
		CPropertyName Prop (cbBuffer);
		string strName = Prop.GetName();

			m_cbObjProps.AddString (strName.c_str());
#else
			m_cbObjProps.AddString (cbBuffer);
#endif
		}
		m_cbObjProps.ChangeCurrentIndex (0);
	}
	return true;
}

void CRechResultDlg::SetHideFlags (short iHideFlags)
{
// Voreinstellungen einlesen
	m_fHideFlags = iHideFlags & ROHideFlags;
	m_fSortFlags = iHideFlags & ROSortFlags;
	
	m_cbObjNr.SetChecked (!(iHideFlags & ROHideObjNr));
	m_cbIdent.SetChecked (!(iHideFlags & ROHideIdent));
	m_cbObjTyp.SetChecked (!(iHideFlags & ROHideObjTyp));

	AdjustRadios (m_fSortFlags);
}

// EventHandler ---------------------------------------------------------------
void CRechResultDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (true);
		break;
		
	case IDCANCEL:
		EndDlg (false);
		break;
		
	case IDB_RECHRES_HELP:
		break;

	case IDCB_RECHRES_OBJNR:
		m_fHideFlags &= ~ROHideObjNr;
		if (!m_cbObjNr.isChecked())
			m_fHideFlags |= ROHideObjNr;
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

	case IDB_RECHRES_SELALL:	// alle Klassen auswählen
		m_pIdents -> ChangeSelected (Range (0, m_pIdents -> GetCount() -1));
		AdjustOK();
		break;

	case IDR_RECHRES_ONR:
		m_fSortFlags = ROSortObjNr;
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
	}
}

// AbfrageRoutinen ------------------------------------------------------------
bool CRechResultDlg :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, riOTyp);
		
return false;
}


bool CRechResultDlg :: GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetNextIdent (rlIdent, riOTyp);
		
return false;
}


bool CRechResultDlg :: SelectIdents (long lIdent, short iOTyp)
{
	if (m_pIdents) {
		if (iOTyp & OTPunkt) 
			m_pIdents -> SelectIdent (lIdent, OTPunkt, true);
		if (iOTyp & OTLinie) 
			m_pIdents -> SelectIdent (lIdent, OTLinie, true);
		if (iOTyp & OTFlaeche) 
			m_pIdents -> SelectIdent (lIdent, OTFlaeche, true);
		if (iOTyp & OTText) 
			m_pIdents -> SelectIdent (lIdent, OTText, true);

		AdjustOK();
		return true;
	}
		
return false;
}

// HilfsRoutinen --------------------------------------------------------------
void CRechResultDlg :: AdjustOK (void)
{
	if (!m_pIdents || m_pIdents -> GetNoSelected() == 0)
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}

void CRechResultDlg :: AdjustRadios (short iSort)
{
// erstmal alles rücksetzen
	m_rbObjNr.SetState (false);
	m_rbObjTyp.SetState (false);
	m_rbIdent.SetState (false);
	m_rbOProp.SetState (false);
	
	if (!(iSort & ROSortFlags))
		iSort = ROSortObjNr;	// default ist nach ONr sortieren
	if (iSort & ROSortObjNr) m_rbObjNr.SetState (true);
	if (iSort & ROSortObjTyp) m_rbObjTyp.SetState (true);
	if (iSort & ROSortIdent) m_rbIdent.SetState (true);
	if (iSort & ROSortText) m_rbOProp.SetState (true);
}

string CRechResultDlg :: GetActOProp (void)
{
int iIndex = m_cbObjProps.GetCurrentIndex();
string str;

	if (0 <= iIndex) {
	char cbBuffer[64];

		m_cbObjProps.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
		str = cbBuffer;
	}
		
return str;
}

void CRechResultDlg :: SetActOProp (LPCSTR pName)
{
CPropertyName Prop (pName);
string strName = Prop.GetName();
int iIndex = m_cbObjProps.FindString (strName.c_str());

	m_cbObjProps.ChangeCurrentIndex (iIndex);
}


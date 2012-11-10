// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/13/1998 09:32:32 AM
//
// @doc
// @module EditObjProps.cpp | Description goes here

#include "triaspre.hxx"

#include <ospace/std/map>
#include <ospace/std/algorithm>

#include <PropName.hxx>

#include "triasres.h"
#include "extmain3.hxx"
#include "Strings.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "EditObjProps.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASOptionDlgCallback);	// WTRiASOptionDlgCallback
DefineSmartInterface(ObjectProps);			// WObjectProps
DefineSmartInterface(EnumObjProps);			// WEnumObjProps
DefineSmartInterface(Dispatch);
DefineSmartInterface(ObjectProperty2);
DefineSmartInterface(PropertyInfo2);

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften eines Objektes anzeigen/editieren
bool ObjektInfo::doShowOIAttribute (void) 
{
long lONr = GetActiveObj();

	TX_ASSERT(-1 != lONr);
	if ((DEX_GetObjectStatus (lONr) & OS_Temp)) 
		return false;		// kein selektiertes oder temporäres Objekt

VARIANT_BOOL fResult = VARIANT_FALSE;

	COM_TRY {
	WTRiASOptionDlg Dlg (CLSID_TRiASOptionDlg);
	CComObject<CEditObjProps> *pCB = NULL;

		THROW_FAILED_HRESULT(CComObject<CEditObjProps>::CreateInstance(&pCB));
		pCB -> SetLastName(m_rDBO.GetLastName());

		{
		WTRiASOptionDlgCallback CB(pCB);		// pending AddRef()
		CEditObjProps::CDlgWrapper Wrapper (pCB, this, Dlg, lONr);		// manage ConnPoint

			THROW_FAILED_HRESULT(Dlg -> put_Caption (CComBSTR (ResString (IDS_ATTRIBUTCAPTION, 64))));
			THROW_FAILED_HRESULT(Dlg -> put_HasApply (VARIANT_TRUE));
			THROW_FAILED_HRESULT(Dlg -> Show((INT_PTR)hWnd(), SHOWCOMMAND_Show, &fResult));

			Wrapper.SetCommit (fResult);		// evtl. Daten zurückschreiben

		// Speichern der zuletzt eingestellten Objekteigenschaft
			m_rDBO.SetLastName(pCB -> GetLastName());

		} // CB goes out of scope

	} COM_CATCH_RETURN(false);
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften in Gruppen sortiert im Dialog einhängen
namespace {
	#define IMG_TEXTPROP			3
	#define IMG_BOOLPROP			4
	#define IMG_DATUMPROP			20
	#define IMG_INTEGERPROP			21
	#define IMG_DOUBLEPROP			23
	#define IMG_TEXTPROP_DIS		24
	#define IMG_BOOLPROP_DIS		25
	#define IMG_DATUMPROP_DIS		26
	#define IMG_INTEGERPROP_DIS		27
	#define IMG_DOUBLEPROP_DIS		29

	#define IMG_TEXTPROP_RO			5
	#define IMG_BOOLPROP_RO			6
	#define IMG_DATUMPROP_RO		30
	#define IMG_INTEGERPROP_RO		31
	#define IMG_DOUBLEPROP_RO		32
	#define IMG_TEXTPROP_DIS_RO		33
	#define IMG_BOOLPROP_DIS_RO		34
	#define IMG_DATUMPROP_DIS_RO	35
	#define IMG_INTEGERPROP_DIS_RO	36
	#define IMG_DOUBLEPROP_DIS_RO	37

///////////////////////////////////////////////////////////////////////////////
// Index im ImageList aus Flags herausfinden
	inline int GetIntegerImage (bool fExists, bool fNotRO)
	{
		if (fExists)
			return fNotRO ? IMG_INTEGERPROP : IMG_INTEGERPROP_RO;
		else
			return fNotRO ? IMG_INTEGERPROP_DIS : IMG_INTEGERPROP_DIS_RO;
	}

	inline int GetDoubleImage (bool fExists, bool fNotRO)
	{
		if (fExists)
			return fNotRO ? IMG_DOUBLEPROP : IMG_DOUBLEPROP_RO;
		else
			return fNotRO ? IMG_DOUBLEPROP_DIS : IMG_DOUBLEPROP_DIS_RO;
	}

	inline int GetBoolImage (bool fExists, bool fNotRO)
	{
		if (fExists)
			return fNotRO ? IMG_BOOLPROP : IMG_BOOLPROP_RO;
		else
			return fNotRO ? IMG_BOOLPROP_DIS : IMG_BOOLPROP_DIS_RO;
	}

	inline int GetDatumImage (bool fExists, bool fNotRO)
	{
		if (fExists)
			return fNotRO ? IMG_DATUMPROP : IMG_DATUMPROP_RO;
		else
			return fNotRO ? IMG_DATUMPROP_DIS : IMG_DATUMPROP_DIS_RO;
	}

	inline int GetStringImage (bool fExists, bool fNotRO)
	{
		if (fExists)
			return fNotRO ? IMG_TEXTPROP : IMG_TEXTPROP_RO;
		else
			return fNotRO ? IMG_TEXTPROP_DIS : IMG_TEXTPROP_DIS_RO;
	}

	int GetImageIndex (DWORD dwFlags, bool fExists, bool fExpanded)
	{
		if (dwFlags & PROPCAPS_OBJPROPTYPE_INTEGER)
			return GetIntegerImage(fExists, dwFlags & PROPCAPS_NOTREADONLY);
		if (dwFlags & PROPCAPS_OBJPROPTYPE_DOUBLE)
			return GetDoubleImage(fExists, dwFlags & PROPCAPS_NOTREADONLY);
		if (dwFlags & PROPCAPS_OBJPROPTYPE_BOOL)
			return GetBoolImage(fExists, dwFlags & PROPCAPS_NOTREADONLY);
		if (dwFlags & PROPCAPS_OBJPROPTYPE_DATE)
			return GetDatumImage(fExists, dwFlags & PROPCAPS_NOTREADONLY);

		return GetStringImage(fExists, dwFlags & PROPCAPS_NOTREADONLY);
	}

	HRESULT RetrievePicture (DWORD dwFlags, BOOL fExists, BOOL fExpanded, CImageList &rilList, REFIID riid, LPVOID *ppIPict)
	{
	HICON hIcon = rilList.ExtractIcon (GetImageIndex(dwFlags, fExists, fExpanded));

		if (NULL == hIcon) return E_UNEXPECTED;

	PICTDESC pictDesc;

		pictDesc.cbSizeofstruct = sizeof(PICTDESC);
		pictDesc.picType = PICTYPE_ICON;
		pictDesc.icon.hicon = hIcon;
		return ::OleCreatePictureIndirect (&pictDesc, riid, TRUE, (LPVOID *)ppIPict);
	}
} // namespace

/////////////////////////////////////////////////////////////////////////////
// CEditObjProps

STDMETHODIMP CEditObjProps::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASOptionDlgCallback,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASOptionDlgCallback
STDMETHODIMP CEditObjProps::OnInitDialog(ITRiASOptionDlg *pIDlg)
{
CEierUhr Wait(GetParentWnd());

	RETURN_FAILED_HRESULT(pIDlg -> put_WordWrap (VARIANT_FALSE));
	RETURN_FAILED_HRESULT(pIDlg -> put_HasLines (VARIANT_TRUE));
	RETURN_FAILED_HRESULT(pIDlg -> put_HasButtons (VARIANT_TRUE));
	RETURN_FAILED_HRESULT(pIDlg -> put_MultiSelect (VARIANT_FALSE));
	RETURN_FAILED_HRESULT(pIDlg -> put_ContextHandle (m_lONr));
	return InsertItems(pIDlg);
}

STDMETHODIMP CEditObjProps::OnGetDispInfoChildren(ITRiASOptionDlg *pIDlg, ULONG ulItem, int *piChildren)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEditObjProps::OnGetDispInfoImage(ITRiASOptionDlg *pIDlg, ULONG ulItem, IDispatch **ppIPict)
{
	COM_TRY {
	WUnknown Unk;

		THROW_FAILED_HRESULT(pIDlg -> GetItemObject (ulItem, Unk.ppi()));

	DWORD dwFlags = 0L;
	WObjectProperty Prop;
	WPropertyInfo2 Info;

		if (SUCCEEDED(Unk -> QueryInterface(Info.ppi()))) {
		// ggf. spezielles Interface verwenden (falls vorhanden)
		INT_PTR hObjs = DEX_GetObjIdentEx(m_lONr);

			if (NULL == hObjs)
				return E_UNEXPECTED;

			THROW_FAILED_HRESULT(Info -> GetPropInfoEx (hObjs, NULL, 0, &dwFlags));
		}
		else if (SUCCEEDED(Unk -> QueryInterface(Prop.ppi()))) {
		// Standardinterface verwenden
			THROW_FAILED_HRESULT(Prop -> GetPropInfo (NULL, 0, &dwFlags));
		}
	
	CComVariant v;
	WTRiASLockFeatureEx Lock(Unk);
	BOOL fExists = (S_OK == Lock -> get_Feature (m_lONr, &v)) ? TRUE : FALSE;

		THROW_FAILED_HRESULT(RetrievePicture (dwFlags, fExists, FALSE, m_ilList, IID_IDispatch, (LPVOID *)ppIPict));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CEditObjProps::OnGetDispInfoExpandedImage(ITRiASOptionDlg *pIDlg, ULONG ulItem, IDispatch **ppIPict)
{
HRESULT hr = S_OK;

	COM_TRY {
	WUnknown Unk;

		THROW_FAILED_HRESULT(pIDlg -> GetItemObject (ulItem, Unk.ppi()));

	DWORD dwFlags = 0L;
	WObjectProperty Prop (Unk);

		THROW_FAILED_HRESULT(Prop -> GetPropInfo (NULL, 0, &dwFlags));

	CComVariant v;
	WTRiASLockFeatureEx Lock(Unk);
	BOOL fExists = (S_OK == Lock -> get_Feature (m_lONr, &v)) ? TRUE : FALSE;

		THROW_FAILED_HRESULT(RetrievePicture (dwFlags, fExists, TRUE, m_ilList, IID_IDispatch, (LPVOID *)ppIPict));

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CEditObjProps::OnGetDispInfoText(ITRiASOptionDlg *pIDlg, ULONG ulItem, BSTR *pbstrText)
{
	return E_NOTIMPL;
}

STDMETHODIMP CEditObjProps::OnQueryContextMenu(
	ITRiASOptionDlg *pIDlg, ULONG ulItem, INT_PTR hMenu, UINT uiFirst, UINT uiLast, UINT *puiLastID)
{
HRESULT hr = S_FALSE;

	TX_ASSERT(NULL != hMenu);
	COM_TRY {
	// Menu binden
	Menu menu (reinterpret_cast<HMENU>(hMenu), TRUE);	// autodetach hMenu
	bool fAddSeparator = false;

		if (::GetMenuItemCount (reinterpret_cast<HMENU>(hMenu)) > 0) 
			fAddSeparator = true;		// ZwischenSeparator einfügen

	// Typ des Items rauskriegen
	WUnknown Unk;

		THROW_FAILED_HRESULT(hr = pIDlg -> GetItemObject (ulItem, Unk.ppi()));
		m_Actions.clear();		// alles bisherige löschen
		if (S_OK == hr) {
		// wenn Item eine Objekteigenschaft repräsentiert
			if (fAddSeparator)
				menu.InsertSeparator((UINT)-1);

			menu.AppendItem (uiFirst, ResString(IDS_ADDOBJPROP, 64).Addr());
			menu.DisableItem(uiFirst);
			m_Actions.insert(CMapCmdAction::value_type(uiFirst++, (EDITOBJPROPACTION)AddObjProp));

		// testen, ob die Objekteigenschaft gelöscht werden darf
		CComVariant v;
		WTRiASLockFeatureEx Lock(Unk);
		WObjectProperty2 WriteObjProp;
		BOOL fExists = (S_OK == Lock -> get_Feature (m_lONr, &v)) ? TRUE : FALSE;

			menu.AppendItem (uiFirst, ResString(IDS_DELETEOBJPROP, 64).Addr());
			m_Actions.insert(CMapCmdAction::value_type(uiFirst, (EDITOBJPROPACTION)DeleteObjProp));
			if (!fExists || FAILED(Unk -> QueryInterface(WriteObjProp.ppi()))) 
				menu.DisableItem(uiFirst);	// nicht existent oder schreibgeschützt
			else
				SetMenuDefaultItem(reinterpret_cast<HMENU>(hMenu), uiFirst, FALSE);

		} else {
		// Item repräsentiert eine Ober/Zwischengruppe
		ULONG ulParent = 0;

			THROW_FAILED_HRESULT(pIDlg -> GetNextItem (ulItem, NEXTITEMMODE_PARENT, &ulParent));
			if (0 == ulParent) {
			// OberNode
			
			} else {
			// ZwischenNode

			}
		}
		if (NULL != puiLastID)
			*puiLastID = uiFirst;

	} COM_CATCH;
	return hr;
}

STDMETHODIMP CEditObjProps::OnGetCommandString(ITRiASOptionDlg *pIDlg, ULONG ulItem, UINT uiCmd, DWORD dwFlags, BSTR *pbstrDesc)
{
	return S_FALSE;
}

STDMETHODIMP CEditObjProps::OnInvokeCommand(ITRiASOptionDlg *pIDlg, ULONG ulItem, INT_PTR hWnd, UINT uiCmd)
{
CMapCmdAction::iterator it = m_Actions.find (uiCmd);
HRESULT hr = S_FALSE;

	if (it != m_Actions.end()) 
		hr = (this ->* (*it).second)(reinterpret_cast<HWND>(hWnd), pIDlg, ulItem);
	
	m_Actions.erase();
	return hr;
}

STDMETHODIMP CEditObjProps::OnOk (ITRiASOptionDlg *pIDlg)
{
	COM_TRY {
	ULONG hActItem = NULL;
	ULONG hChildItem = NULL;

		THROW_FAILED_HRESULT(pIDlg -> get_ActItem(&hActItem));
		THROW_FAILED_HRESULT(pIDlg -> GetChildItem(hActItem, &hChildItem));
		if (NULL == hChildItem) {
		os_string strFullName;

			if (SUCCEEDED(GetObjPropName (pIDlg, hActItem, strFullName)))
				SetLastName(strFullName.c_str());

		} else
			SetLastName("");

	} COM_CATCH;
	return S_OK;
}

HRESULT CEditObjProps::GetObjPropName(
	ITRiASOptionDlg *pIDlg, ULONG ulItem, os_string &rStrFull)
{
	USES_CONVERSION;
	COM_TRY {
	int iLoop = 0;
	CComBSTR bstr("");

		do {
		CComBSTR bstrT;
		
			THROW_FAILED_HRESULT(pIDlg -> GetItemName (ulItem, &bstrT));
			if (iLoop > 0) {
			CComBSTR bstrT1 (bstrT);

				bstrT1.Append(L"\\");
				bstrT1.AppendBSTR(bstr);
				bstr = bstrT1;
			} else
				bstr = bstrT;

		ULONG ulParent = 0;

			THROW_FAILED_HRESULT(pIDlg -> GetParentItem (ulItem, &ulParent));
			ulItem = ulParent;
			iLoop++;

		} while (NULL != ulItem);
		
	os_string strT ("OBJPROP_ROOT\\");

		strT += OLE2A(bstr);
		rStrFull = strT;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CEditObjProps::OnCancel (ITRiASOptionDlg *pIDlg)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Menubefehle abarbeiten
HRESULT CEditObjProps::AddObjProp (HWND hWnd, ITRiASOptionDlg *pIDlg, ULONG ulItem)
{
Window wnd(hWnd);
MessBox mb ("Menutest", "AddObjProp", &wnd);

	mb.Show();
	return S_OK;
}

HRESULT CEditObjProps::DeleteObjProp (HWND hWnd, ITRiASOptionDlg *pIDlg, ULONG ulItem)
{
	COM_TRY {
	// betroffenes Items rauskriegen
	WUnknown Unk;

		THROW_FAILED_HRESULT(pIDlg -> GetItemObject (ulItem, Unk.ppi()));

	WTRiASLockFeatureEx Lock(Unk);
	CComVariant vVal(DISP_E_PARAMNOTFOUND, VT_ERROR);

		THROW_FAILED_HRESULT(Lock -> put_Feature(m_lONr, vVal));		// Wert löschen
		THROW_FAILED_HRESULT(pIDlg -> RefreshItem (ulItem));			// Icon neu einlesen

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
HRESULT CEditObjProps::InsertItems(ITRiASOptionDlg *pIDlg)
{
// Liste der Objekteigenschaften initialisieren
WObjectProps Props;
BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

	if (!Props.IsValid()) 
		return E_UNEXPECTED;

// alle ObjProps für das Bezugsobjekt installieren
//	if (fMustReInit) 
	{
		Props -> OnNewReferenceObjects (-1L, 0L);	// alles bisherige löschen

// #HK001105: Paradigmenwechsel! Es werden jetzt Grundsätzlich alle Objekteigenschaften
// der zugehörigen Objektklasse eines Objektes geliefert, nicht mehr nur die am konkreten 
// Objekt existierenden 
//	INT_PTR hObjs = DEX_GetObjIdent(m_lONr);
//
//		RETURN_FAILED_HRESULT(Props -> OnNewReferenceObjects (hObjs, m_lONr));
		RETURN_FAILED_HRESULT(Props -> OnNewReferenceObject (m_lONr));
		DEX_SetMustInitOPFs(TRUE);
	}

// Objekteigenschaften in Gruppen sortiert im Baum einhängen
WEnumObjProps IEnum;
HRESULT hr = Props -> EnumObjectProps (IEnum.ppi());

	if (FAILED(hr)) return hr;

// Objekteigenschaften durchgehen
WObjectProperty IProp;
char cbPropInfo[_MAX_PATH];
ULONG hToSelect = NULL;
CItemMap Items;
CPropertyName LastName (GetLastName());

	for (IEnum -> Reset(); S_OK == IEnum -> Next (1, IProp.ppu(), NULL); /**/)
	{
	// vollständigen Namen geben lassen
	DWORD dwFlags = 0L;

		hr = IProp -> GetPropInfo (cbPropInfo, sizeof(cbPropInfo), &dwFlags);
		if (FAILED(hr) || dwFlags & PROPCAPS_INTERACTIVE)
			continue;		// keine interaktive ObjProps anzeigen

	// ParentItem der Property aus dem Baum besorgen
	CPropertyName PropName (cbPropInfo);
	CComBSTR bstrSubGroup (PropName.GetSubGroup().c_str());
	CComBSTR bstrName (PropName.GetName().c_str());
	ULONG hParent = CalcParentItem (pIDlg, CComBSTR(PropName.GetGroup().c_str()), Items);
	ULONG hNewItem = NULL;

		if (0 != bstrSubGroup.Length()) {
		ULONG hSubGroup = CalcSubGroupItem (pIDlg, hParent, bstrSubGroup);

			if (NULL != hSubGroup)
				pIDlg -> InsertItemObject (IProp, bstrName, hSubGroup, NULL, &hNewItem);
			else 
				pIDlg -> InsertItemObject (IProp, bstrName, hParent, NULL, &hNewItem);
		} else 
			pIDlg -> InsertItemObject (IProp, bstrName, hParent, NULL, &hNewItem);

	// neuen Eintrag in Liste aller Einträge ablegen
	os_string strFullName;

		PropName.GetFullName(strFullName);
		m_Entries.insert(CMapStringObject::value_type(strFullName, (IUnknown *)IProp));

		if (LastName == PropName) 
			hToSelect = hNewItem;
	}

// jetzt noch alle Items von ihrem Bezugsobjekt informieren
	hr = OnNewReferenceObject();
	if (SUCCEEDED(hr)) {
	// die zuletzt eingestellte Objekteigenschaft wieder einstellen
		if (NULL != hToSelect) 
			pIDlg -> SetFirstVisible (hToSelect);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Finden des ParentItems im Control, ansonsten TVI_ROOT liefern 
ULONG CEditObjProps::CalcParentItem (ITRiASOptionDlg *pIDlg, const CComBSTR &bstrGroup, CItemMap &rItems)
{
	TX_ASSERT(NULL != pIDlg);

ULONG hItem = 0L;
CItemMap::const_iterator it = rItems.find (bstrGroup);

	if (it == rItems.end()) {
	// erstes mal
		USES_CONVERSION;
		pIDlg -> InsertFolderItem (bstrGroup, 0L, &hItem);
		rItems.insert (make_pair (bstrGroup, hItem));
	} else
		hItem = (*it).second;

	return hItem;
}

///////////////////////////////////////////////////////////////////////////////
// Finden bzw. hinzufügen eines GruppenItems zu einem Parent 
ULONG CEditObjProps::CalcSubGroupItem (ITRiASOptionDlg *pIDlg, ULONG hParent, const CComBSTR &bstrSubGroup)
{
	TX_ASSERT(NULL != pIDlg);

ULONG hChild = 0L;

	pIDlg -> GetChildItem (hParent, &hChild);
	while (0L != hChild) {
	CComBSTR bstr;

		pIDlg -> GetItemName (hChild, CLEARED(&bstr));
		if (!wcscmp (bstr, bstrSubGroup)) 
			return hChild;		// SubGroup gibt es schon

		pIDlg -> GetNextItem (hChild, NEXTITEMMODE_NEXT, &hChild);
	}

// nichts gefunden, also neue SubGroup einfügen
ULONG hItem = 0L;

	pIDlg -> InsertFolderItem (bstrSubGroup, hParent, &hItem);
	return hItem;
}

///////////////////////////////////////////////////////////////////////////////
// MultiLineEdit, welches ReadOnly sein kann 
#include "editro.hxx"		// EditControl, welches RO/nicht RO sein kann

CEditCondRO :: CEditCondRO (pDialogWindow p, ResID r)
	     : ControlWindow (new MultiLineEdit (p, r))
{
	m_fRO = false;
}

CEditCondRO :: ~CEditCondRO (void)
{
	if (GetControl())
		delete (MultiLineEdit *)GetControl();
}

void CEditCondRO :: KeyDown (KeyEvt e)
{
	if (!m_fRO) {	// wenn nicht RO, dann bearbeiten
		Default ((Event &)e);
		return;
	}
	MessageBeep (MB_ICONHAND);
}

void CEditCondRO :: GetText (char *pBuff, uint uiLen)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> GetText (pBuff, uiLen);
}

void CEditCondRO :: SetText (const char *pcBuff)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> SetText (pcBuff);
}

void CEditCondRO :: SetTextLimit (uint nchars)
{
	if (GetControl())
        	((MultiLineEdit *)GetControl()) -> SetTextLimit (nchars);
}

int CEditCondRO :: GetTextLen (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> GetTextLen ();

return 0;
}

bool CEditCondRO :: isModified (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> isModified();

return false;
}

void CEditCondRO :: SetModified (bool fModified)
{
	if (GetControl() && !m_fRO)
        	((MultiLineEdit *)GetControl()) -> SetModified (fModified);
}

bool CEditCondRO :: FInit (void)
{
	if (GetControl())
	        return ((MultiLineEdit *)GetControl()) -> FInit();

return false;
}

#if defined(_FORCE_LEGACY_CODE)
// alle vorhandenen MerkmalsCodes dieser GeoDB lesen und zu ML ergänzen
ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &ML) 
{
ErrCode EC;
GeoDB &rDB = rDBO.DB();
DB_ADDR dba(rDB.DBDesc());
CActDB ActDB (rDB);	// DB aktivieren

	{
	// Fehler WC_NOTFOUND ignorieren
	ErrInstall EI (WC_NOTFOUND);
	PBD_MerkmalCreator MC (ML);

	// ersten MerkmalsCode suchen
		EC = (ErrCode)z_keyfirst (&dba, MK);
		if (EC != EC_OKAY) {
		// Fehler aufgetreten
			if (EC == WC_NOTFOUND) 
				return EC_OKAY;         // nichts gefunden: OK
			return EC;                      // sonstiger Fehler
		}

	// für alle weiteren Merkmale
		do {
		long MKode;
		CTable t(ML);

		// MKode aus Schlüsseldatei lesen
			EC = (ErrCode)z_keyread (rDB.DBDesc(), &MKode);
			if (EC != EC_OKAY) break;
			if (!t.Find (&MKode)) {
			// Textmerkmal in MerkmalsListe einfügen
			TextMerkmal *pMK = new TextMerkmal(
						&rDBO.PbdDB(), MKode, NULL
					);

				if (pMK) {
					if (!ML.isSystem() && pMK -> isSystem()) {
					// nicht einspeichern
						delete pMK;
					} else
						MC.InsertPtr (pMK);
				} else {
					db_error (EC_NOMEMORY, RC_FillMerkmale);
					return EC_NOMEMORY;
				}

			// wieder auf GeoDB umschalten
				EC = (ErrCode)z_keyfind (&dba, MK, &MKode);
				if (EC != EC_OKAY)
					break;	// snh
			}

		// nächsten Schlüssel suchen
			EC = (ErrCode)z_keynext (&dba, MK);
		} while (EC == EC_OKAY);
	} // Fehlerbearbeitung wieder einstellen
	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

// Baum optimieren
	if (EC == EC_OKAY) 
		ML.Optimize();

	return EC;
}
#endif // _FORCE_LEGACY_CODE


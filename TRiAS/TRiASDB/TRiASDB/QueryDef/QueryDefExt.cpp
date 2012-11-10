// @doc
// @module QueryDef.cpp | Implementation of the <c CQueryDefExtension> class

#include "stdafx.h"

#include "Strings.h"
#include "QueryDef.h"
#include "QueryDefExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectWithName);

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules QueryDef
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_QueryDefExt;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CQueryDefExtension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CQueryDefExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode) || !InitJumpTable())
		return FALSE;

// den aktuellen Namen von TRiAS lesen
CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.Open(key, REG_PRODUCT_KEY))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config"))) {
		DWORD dwCount = _countof(g_cbTRiAS);

			if (ERROR_SUCCESS != cfgkey.QueryValue (g_cbTRiAS, TEXT("TRiASName"), &dwCount))
				_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden
		}
	}

	COM_TRY {
	// ObjektklassenMap
		m_ObjsMap = WTRiASObjectHandleMap(CLSID_TRiASObjectsHandleMap);
		THROW_FAILED_HRESULT(WObjectWithName(m_ObjsMap) -> put_Name (CComBSTR(g_cbObjectsMap)));

	// ObjektMap
		m_ObjMap = WTRiASObjectHandleMap(CLSID_TRiASObjectHandleMap);
		THROW_FAILED_HRESULT(WObjectWithName(m_ObjMap) -> put_Name (CComBSTR(g_cbObjectMap)));
	} COM_CATCH_RETURN(FALSE);

// WindowsNotifikationen anfordern
	RegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken

// normale Notifikationen
	RegisterNotification (DEX_OBJECTCHANGED);

// MenuItem einhängen
	InstallMenuItem (IDM_DELETEFROMOBJCLASS, IDS_DELETEFROMOBJCLASS, IMIObjWnd, OR_OBJECT_MENU_POS);
	InstallMenuItem (IDM_MAKEOBJCLASS, IDS_MAKEOBJCLASS, IMIObjWnd, OR_OBJECT_MENU_POS);
	InstallMenuItem ((UINT)-1, 0, IMIObjWnd, OR_OBJECT_MENU_POS);	// MF_SEPARATOR
	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CQueryDefExtension::UnLoadExtension (void)
{
// WindowsNotifikationen abmelden
	UnRegisterNotification (__DexCmd, FALSE);		// alle DEX_... bei uns vorbeischicken
	FreeJumpTable();

// normale Notifikationen
	UnRegisterNotification (DEX_OBJECTCHANGED);

// MenuItem rauswerfen
	RemoveMenuItem ((UINT)-1, IMIObjWnd, OR_OBJECT_MENU_POS);			// MF_SEPARATOR
	RemoveMenuItem (IDM_MAKEOBJCLASS, IMIObjWnd, OR_OBJECT_MENU_POS);
	RemoveMenuItem (IDM_DELETEFROMOBJCLASS, IMIObjWnd, OR_OBJECT_MENU_POS);

	m_ObjsMap.Assign(NULL);
	m_ObjMap.Assign(NULL);

	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// Menubehandlung
bool CQueryDefExtension::FindMenuItem (HMENU hMenu, UINT uiID)
{
UINT uiCnt = GetMenuItemCount(hMenu);

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == GetMenuItemID (hMenu, uiLoop))
			return true;
	}

	return false;		// nichts gefunden
}

bool CQueryDefExtension::HasPseudoObjects (HWND hWnd)
{
CSelectedObjects Objs;

	if (!CollectSelectedObjects (hWnd, inserter(Objs, Objs.end())))
		return false;

	for (CSelectedObjects::iterator it = Objs.begin(); it != Objs.end(); ++it) {
		if (0 != DEX_GetNativeObject (*it))
			return true;
	}
	return false;		// no pseudoobjects
}

STDMETHODIMP_(BOOL) CQueryDefExtension::MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (NULL == hWnd || !FindMenuItem (hMenu, IDM_MAKEOBJCLASS))
		return FALSE;

short iObjCnt = 0;
bool fEnable = false;

	DEXOR_SelectedObjectsCount(hWnd, &iObjCnt);
	EnableMenuItem (hMenu, IDM_MAKEOBJCLASS+MenuOffset(), ((0 != iObjCnt) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
	
// Feststellen, ob wenigstens ein Objekt in einer Rechercheobjektklasse enthalten ist
	if (0 != iObjCnt) 
		fEnable = HasPseudoObjects (hWnd);

	EnableMenuItem (hMenu, IDM_DELETEFROMOBJCLASS+MenuOffset(), (fEnable ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
	return TRUE;
}

STDMETHODIMP_(BOOL) CQueryDefExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	if (NULL == hWnd) 
		return FALSE;		// nicht für uns

UINT uiRes = 0L;

	switch (uiMenuID) {
	case IDM_MAKEOBJCLASS:
		uiRes = IDS_MAKEOBJCLASS_LONG; 
		break;

	case IDM_DELETEFROMOBJCLASS:
		uiRes = IDS_DELETEFROMOBJCLASS_LONG; 
		break;

	default:
		break;
	}

	if (uiRes != 0L) {
	char cbString[_MAX_PATH];
	CString resMsg; 
	
		VERIFY(resMsg.LoadString(uiRes));
	
		strcpy (cbString, resMsg);
		strtok (cbString, "\n");
		DEX_SetMessageString (cbString);
		return TRUE;
	}
	return FALSE;
}

STDMETHODIMP_(BOOL) CQueryDefExtension::MenuCommand (UINT uiMenuID, HWND hWnd)
{
	_ASSERTE(NULL != hWnd);

	switch (uiMenuID) {
	case IDM_MAKEOBJCLASS:
		return SUCCEEDED(MakeObjectClass(hWnd)) ? TRUE : FALSE;

	case IDM_DELETEFROMOBJCLASS:
		return SUCCEEDED(DeleteFromClass(hWnd)) ? TRUE : FALSE;

	default:
		break;
	}
	return FALSE;
}

STDMETHODIMP_(LRESULT) CQueryDefExtension::Notification (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEX_OBJECTCHANGED:
		OnObjectChanged (lParam);
		break;
	}
	return FALSE;	// i.a. alles weiterleiten
}


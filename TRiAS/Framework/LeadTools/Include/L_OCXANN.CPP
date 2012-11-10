#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>

#include "L_OCXANN.H"


/////////////////////////////////////////////////////////////////////////////
// CAnnToolbar properties

CAnnToolbar::CAnnToolbar(const CAnnToolbar& dispatchSrc) : COleDispatchDriver() 
{
   ASSERT(this != &dispatchSrc);   // constructing from self?

   m_lpDispatch = dispatchSrc.m_lpDispatch;
   if (m_lpDispatch != NULL)
      m_lpDispatch->AddRef();
   m_bAutoRelease = TRUE;
}

BOOL CAnnToolbar::GetVisible()
{
   BOOL result;
   GetProperty(dispidVisible, VT_BOOL, (void*)&result);
   return result;
}

void CAnnToolbar::SetVisible(BOOL propVal)
{
   SetProperty(dispidVisible, VT_BOOL, propVal);
}

short CAnnToolbar::GetTool()
{
   short result;
   GetProperty(dispidTool, VT_I2, (void*)&result);
   return result;
}

void CAnnToolbar::SetTool(short propVal)
{
   SetProperty(dispidTool, VT_I2, propVal);
}

BOOL CAnnToolbar::GetAutoSetTool()
{
   BOOL result;
   GetProperty(dispidAutoSetTool, VT_BOOL, (void*)&result);
   return result;
}

void CAnnToolbar::SetAutoSetTool(BOOL propVal)
{
   SetProperty(dispidAutoSetTool, VT_BOOL, propVal);
}

short CAnnToolbar::GetButtonCount()
{
   short result;
   GetProperty(dispidButtonCount, VT_I2, (void*)&result);
   return result;
}

void CAnnToolbar::SetButtonCount(short propVal)
{
   SetProperty(dispidButtonCount, VT_I2, propVal);
}

short CAnnToolbar::GetButtonColumns()
{
   short result;
   GetProperty(dispidButtonColumns, VT_I2, (void*)&result);
   return result;
}

void CAnnToolbar::SetButtonColumns(short propVal)
{
   SetProperty(dispidButtonColumns, VT_I2, propVal);
}

short CAnnToolbar::GetButtonRows()
{
   short result;
   GetProperty(dispidButtonRows, VT_I2, (void*)&result);
   return result;
}

void CAnnToolbar::SetButtonRows(short propVal)
{
   SetProperty(dispidButtonRows, VT_I2, propVal);
}

long CAnnToolbar::GetHWnd()
{
   long result;
   GetProperty(dispidHWnd, VT_I4, (void*)&result);
   return result;
}

void CAnnToolbar::SetHWnd(long propVal)
{
   SetProperty(dispidHWnd, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CAnnToolbar operations

short CAnnToolbar::Create(float x, float y, short iAlign)
{
   short result;
   static BYTE parms[] =
      VTS_R4 VTS_R4 VTS_I2;
   InvokeHelper(dispidCreate, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
      x, y, iAlign);
   return result;
}

BOOL CAnnToolbar::GetButtonVisible(short nButton)
{
   BOOL result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonVisible, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
      nButton);
   return result;
}

void CAnnToolbar::SetButtonVisible(short nButton, BOOL bNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_BOOL;
   InvokeHelper(dispidButtonVisible, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       nButton, bNewValue);
}

short CAnnToolbar::GetButtonTool(short iButtonIndex)
{
   short result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonTool, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonTool(short iButtonIndex, short nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonTool, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, nNewValue);
}

short CAnnToolbar::GetButtonToolCount(short iButtonIndex)
{
   short result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonToolCount, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonToolCount(short iButtonIndex, short nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonToolCount, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, nNewValue);
}

short CAnnToolbar::GetButtonMenuTool(short iButtonIndex, short iToolIndex)
{
   short result;
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonMenuTool, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
      iButtonIndex, iToolIndex);
   return result;
}

void CAnnToolbar::SetButtonMenuTool(short iButtonIndex, short iToolIndex, short nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonMenuTool, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, iToolIndex, nNewValue);
}

short CAnnToolbar::GetButtonMenuTextID(short iButtonIndex, short iToolIndex)
{
   short result;
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonMenuTextID, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
      iButtonIndex, iToolIndex);
   return result;
}

void CAnnToolbar::SetButtonMenuTextID(short iButtonIndex, short iToolIndex, short nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonMenuTextID, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, iToolIndex, nNewValue);
}

CString CAnnToolbar::GetButtonMenuText(short iButtonIndex, short iToolIndex)
{
   CString result;
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonMenuText, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
      iButtonIndex, iToolIndex);
   return result;
}

void CAnnToolbar::SetButtonMenuText(short iButtonIndex, short iToolIndex, LPCTSTR lpszNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2 VTS_BSTR;
   InvokeHelper(dispidButtonMenuText, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, iToolIndex, lpszNewValue);
}

long CAnnToolbar::GetButtonBitmapDown(short iButtonIndex)
{
   long result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonBitmapDown, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonBitmapDown(short iButtonIndex, long nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I4;
   InvokeHelper(dispidButtonBitmapDown, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, nNewValue);
}

long CAnnToolbar::GetButtonBitmapUp(short iButtonIndex)
{
   long result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonBitmapUp, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonBitmapUp(short iButtonIndex, long nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I4;
   InvokeHelper(dispidButtonBitmapUp, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, nNewValue);
}

short CAnnToolbar::GetButtonToolTipTextID(short iButtonIndex)
{
   short result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonToolTipTextID, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonToolTipTextID(short iButtonIndex, short nNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_I2;
   InvokeHelper(dispidButtonToolTipTextID, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, nNewValue);
}

CString CAnnToolbar::GetButtonToolTipText(short iButtonIndex)
{
   CString result;
   static BYTE parms[] =
      VTS_I2;
   InvokeHelper(dispidButtonToolTipText, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
      iButtonIndex);
   return result;
}

void CAnnToolbar::SetButtonToolTipText(short iButtonIndex, LPCTSTR lpszNewValue)
{
   static BYTE parms[] =
      VTS_I2 VTS_BSTR;
   InvokeHelper(dispidButtonToolTipText, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
       iButtonIndex, lpszNewValue);
}

CAnnMenu::CAnnMenu(const CAnnMenu& dispatchSrc) : COleDispatchDriver() 
{
   ASSERT(this != &dispatchSrc);   // constructing from self?

   m_lpDispatch = dispatchSrc.m_lpDispatch;
   if (m_lpDispatch != NULL)
      m_lpDispatch->AddRef();
   m_bAutoRelease = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAnnMenu properties

short CAnnMenu::GetCount()
{
	short result;
	GetProperty(dispidCount, VT_I2, (void*)&result);
	return result;
}

void CAnnMenu::SetCount(short propVal)
{
	SetProperty(dispidCount, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CAnnMenu operations

CString CAnnMenu::GetItemString(short iIndex)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidItemString, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms,
		iIndex);
	return result;
}

void CAnnMenu::SetItemString(short iIndex, LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(dispidItemString, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iIndex, lpszNewValue);
}

long CAnnMenu::GetItemID(short iIndex)
{
	long result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidItemID, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		iIndex);
	return result;
}

void CAnnMenu::SetItemID(short iIndex, long nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4;
	InvokeHelper(dispidItemID, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iIndex, nNewValue);
}

short CAnnMenu::GetItemType(short iIndex)
{
	short result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidItemType, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms,
		iIndex);
	return result;
}

void CAnnMenu::SetItemType(short iIndex, short nNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(dispidItemType, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iIndex, nNewValue);
}

BOOL CAnnMenu::GetItemChecked(short iIndex)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidItemChecked, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		iIndex);
	return result;
}

void CAnnMenu::SetItemChecked(short iIndex, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(dispidItemChecked, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iIndex, bNewValue);
}

BOOL CAnnMenu::GetItemEnabled(short iIndex)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidItemEnabled, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		iIndex);
	return result;
}

void CAnnMenu::SetItemEnabled(short iIndex, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(dispidItemEnabled, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 iIndex, bNewValue);
}

short CAnnMenu::DeleteItem(short iIndex)
{
	short result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidDeleteItem, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		iIndex);
	return result;
}

short CAnnMenu::AddItem(LPCTSTR pszString, short iType, long nID, short iIndexBefore)
{
	short result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_I4 VTS_I2;
	InvokeHelper(dispidAddItem, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		pszString, iType, nID, iIndexBefore);
	return result;
}

CAnnMenu CAnnMenu::GetSubMenu(short iIndex)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(dispidGetSubMenu, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		iIndex);
	return CAnnMenu(pDispatch);
}

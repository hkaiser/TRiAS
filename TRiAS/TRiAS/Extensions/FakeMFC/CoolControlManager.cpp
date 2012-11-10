
/******************************************************************

$Archive: /MfcExt/Source/CoolControlManager.cpp $
$Workfile: CoolControlManager.cpp $
$Author: Bogdan Ledwig $
$Date: 99-02-19 23:13 $
$Revision: 12 $

*******************************************************************/

#include "StdAfx.h"     // You have to include at least <windows.h> and <commctrl.h>

#include "CoolControlManager.h"

#include <crtdbg.h>     // For _ASSERT and _RPT macros

////////////////////////////////////////////////////////////////////////
// CCMControl static members initialization

HWND CCoolControlsManager::CCMControl::m_hWndOld = NULL;


#define CCM_TIMER_VAL 100        // 100 ms timer period seems to be good enough...
#define MAX_CLASSNAME 64         // Length of buffer for retrieving the class name

CMapPtrToPtr CCoolControlsManager::m_ctrlMap = 10;
CMapPtrToPtr CCoolControlsManager::m_dlgMap = 10;
BOOL CCoolControlsManager::m_bEnabled = TRUE;

///////////////////////////////////////////////////////////////////////
// Here is the one and only CCoolControlsManager object
static CCoolControlsManager g_ctrlManager;

CCoolControlsManager& GetCtrlManager()
{
   return g_ctrlManager;
}

////////////////////////////////////////////////////////////////////////
// WH_CALLWNDPROCRET hook procedure

LRESULT CALLBACK CCM_CallWndProcRet( int nCode, WPARAM wParam, LPARAM lParam )
{     
   if ( nCode == HC_ACTION )
   {
      CWPRETSTRUCT* pwp = (CWPRETSTRUCT*)lParam;
      if ( g_ctrlManager.IsEnabled() )
      {
         if ( g_ctrlManager.m_bDialogOnly == TRUE )
         {
            if ( pwp->message == WM_INITDIALOG )
               g_ctrlManager.Install( pwp->hwnd );
         }
         else if ( pwp->message == WM_CREATE && g_ctrlManager.IsEnabled() )
         {
            // Get parent window handle
            HWND hWndParent = pwp->hwnd;            
            while ( GetWindowLong( hWndParent, GWL_STYLE ) & WS_CHILD )
               hWndParent = GetParent( hWndParent );

            TCHAR szBuf[MAX_CLASSNAME];
            GetClassName( hWndParent, szBuf, MAX_CLASSNAME );
            if ( !lstrcmp( szBuf, "#32770" ) )
            {
               if ( GetWindowLong( pwp->hwnd, GWL_STYLE ) & WS_CHILD )
                  g_ctrlManager.AddControl( pwp->hwnd );
            }
            else  // Add only toolbar controls
            {
               if ( GetWindowLong( pwp->hwnd, GWL_STYLE ) & WS_CHILD )
               {                  
                  GetClassName( pwp->hwnd, szBuf, MAX_CLASSNAME );
                  if ( !lstrcmp( szBuf, "ToolbarWindow32" ) )
                     g_ctrlManager.AddControl( pwp->hwnd );
                  else if ( !lstrcmp( szBuf, "ComboBox" ) )
                     g_ctrlManager.AddControl( pwp->hwnd );
               }
            }
         }         
      }
   }
   return CallNextHookEx( (HHOOK)g_ctrlManager.m_hkWndProc, nCode, wParam, lParam );
}

////////////////////////////////////////////////////////////////////////
// WH_CALLWNDPROC hook procedure

LRESULT CALLBACK CCM_CallWndProc( int nCode, WPARAM wParam, LPARAM lParam )
{     
   if ( nCode == HC_ACTION )
   {
      CWPSTRUCT* pwp = (CWPSTRUCT*)lParam;
      if ( g_ctrlManager.IsEnabled() )
      {
         if ( g_ctrlManager.m_bDialogOnly == TRUE )        
         {
            if ( pwp->message == WM_INITDIALOG )
               g_ctrlManager.Install( pwp->hwnd );
         }
         else if ( pwp->message == WM_CREATE && g_ctrlManager.IsEnabled() )
         {
            TCHAR szBuf[MAX_CLASSNAME];
            if ( GetWindowLong( pwp->hwnd, GWL_STYLE ) & WS_CHILD )
            {
               GetClassName( pwp->hwnd, szBuf, MAX_CLASSNAME );
               if ( lstrcmp( szBuf, "ScrollBar" ) ) // Don't add scrollbars
                  g_ctrlManager.AddControl( pwp->hwnd );
            }
         }
      }
   }
   return CallNextHookEx( (HHOOK)g_ctrlManager.m_hkWndProc, nCode, wParam, lParam );
}

// Install a hook for the current thread only
void CCoolControlsManager::InstallHook( BOOL bCallWndProcRet, BOOL bDialogOnly )
{
   _ASSERT( m_hkWndProc == NULL );

   m_bDialogOnly = bDialogOnly;

    m_hkWndProc = (HOOKPROC)SetWindowsHookEx( bCallWndProcRet ? WH_CALLWNDPROCRET : WH_CALLWNDPROC,
                                         (HOOKPROC) bCallWndProcRet ? CCM_CallWndProcRet : CCM_CallWndProc,
                                         NULL, /*hInstance*/
                                         GetCurrentThreadId() );   
#if defined(_VERBOSE_DUMP)
   _RPT0( _CRT_WARN, "CCoolControlsManager: WH_CALLWNDPROCRET hook installed\n" );
#endif // _VERBOSE_DUMP
}

// Install a global hook for all windows in the system.
// This function may be called only when is put in a DLL.
void CCoolControlsManager::InstallGlobalHook( HINSTANCE hInstance, BOOL bDialogOnly )
{
   _ASSERT( hInstance );      // hInstance must not be NULL!
   _ASSERT( m_hkWndProc == NULL );
   
   m_bDialogOnly = bDialogOnly;

   HOOKPROC hkProc = (HOOKPROC)GetProcAddress( hInstance, "CCM_CallWndProcRet" );

   m_hkWndProc = (HOOKPROC)SetWindowsHookEx( WH_CALLWNDPROCRET,
                                         (HOOKPROC)hkProc,
                                         hInstance,
                                         0 );   

#if defined(_VERBOSE_DUMP)
   _RPT0( _CRT_WARN, "CCoolControlsManager: WH_CALLWNDPROCRET global hook installed\n" );
#endif // _VERBOSE_DUMP
}

void CCoolControlsManager::UninstallHook()
{
   _ASSERT( m_hkWndProc != NULL );
   UnhookWindowsHookEx( (HHOOK)m_hkWndProc );
   m_hkWndProc = NULL;

#if defined(_VERBOSE_DUMP)
   _RPT0( _CRT_WARN, "CCoolControlsManager: Hook uninstalled\n" );
#endif // _VERBOSE_DUMP
   if ( m_uTimerID )
      KillTimer( NULL, m_uTimerID );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoolControlsManager::CCoolControlsManager()
{  
   m_hkWndProc = NULL;
   m_uTimerID = 0;
#if defined(_VERBOSE_DUMP)
   _RPT0( _CRT_WARN, "CCoolControlsManager::CCoolControlsManager()\n" );    
#endif // _VERBOSE_DUMP
}

CCoolControlsManager::~CCoolControlsManager()
{  
   if ( m_hkWndProc )
      UninstallHook();  

#if defined(_VERBOSE_DUMP)
   _RPT0( _CRT_WARN, "CCoolControlsManager::~CCoolControlsManager()\n" ); 
#endif // _VERBOSE_DUMP

   // If we have any elements in the map (normally impossible), unsubclass they and remove
   POSITION pos = m_ctrlMap.GetStartPosition();
   while ( pos )
   {
      HWND hWnd;
      CCMControl* pCtl;
      m_ctrlMap.GetNextAssoc( pos, (void*&)hWnd, (void*&)pCtl );

      pCtl->Unsubclass();
      m_ctrlMap.RemoveKey( hWnd );
      delete pCtl;
   }

   // Now do the same things for dialog map
   pos = m_dlgMap.GetStartPosition();
   while ( pos )
   {
      HWND hWnd;
      CCMDialog* pCtl;
      m_dlgMap.GetNextAssoc( pos, (void*&)hWnd, (void*&)pCtl );

      pCtl->Unsubclass();
      m_dlgMap.RemoveKey( hWnd );
      delete pCtl;
   }
}

void CCoolControlsManager::Install( HWND hWnd )
{
   CCMControl* pCtl;
   if ( m_dlgMap.Lookup( hWnd, (void*&)pCtl ) ) // Already in the dialog map
      return;

   // Iterate through all child windows
   HWND hCtrl = GetTopWindow( hWnd );

   while ( hCtrl )
   {
      if ( GetWindowLong( hCtrl, GWL_STYLE ) & WS_CHILD )
      {
         TCHAR szBuf[MAX_CLASSNAME];
         GetClassName( hCtrl, szBuf, MAX_CLASSNAME );
         if ( lstrcmpi( szBuf, _T( "#32770" ) ) ) // Never add child dialogs!
            AddControl( hCtrl );
      }
      hCtrl = GetNextWindow( hCtrl, GW_HWNDNEXT );
   }    

   AddDialog( hWnd ); // Add parent window so well

   // Now redraw all recently inserted controls   
   hCtrl = GetTopWindow( hWnd );
   while ( hCtrl ) 
   {
      if ( m_ctrlMap.Lookup( hCtrl, (void*&)pCtl ) )
         pCtl->DrawBorder();
      hCtrl = GetNextWindow( hCtrl, GW_HWNDNEXT );
   }    
}

void CCoolControlsManager::Uninstall( HWND hWnd )
{
   // Remove all window controls from the map
   // when the window is about to destroy
#if defined(_VERBOSE_DUMP)
   _RPT1( _CRT_WARN, "CCoolControlsManager: Uninstall, handle: %X\n", hWnd );
#endif // _VERBOSE_DUMP
   
   HWND hCtrl = GetTopWindow( hWnd );
   while ( hCtrl )
   {
      if ( GetWindowLong( hCtrl, GWL_STYLE ) & WS_CHILD )
         RemoveControl( hCtrl );
      hCtrl = GetNextWindow( hCtrl, GW_HWNDNEXT );
   }
}

// In lpszClass you can specify class name which will be used 
// instead of true class name (useful for non-standard controls 
// that are similar to the one of those we have supported)
BOOL CCoolControlsManager::AddControl( HWND hWnd, LPCTSTR lpszClass )
{  
   CCMControl* pCtl = NULL; 

   // Must not be NULL or already in the map
   if ( hWnd == NULL || m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) )
      return FALSE;   
   
   TCHAR szBuf[MAX_CLASSNAME];
   if ( lpszClass == NULL )
      GetClassName( hWnd, szBuf, MAX_CLASSNAME );
   else
      lstrcpy( szBuf, lpszClass );

   DWORD dwStyle = GetWindowLong( hWnd, GWL_STYLE );
   DWORD dwExStyle = GetWindowLong( hWnd, GWL_EXSTYLE );

   if ( !lstrcmpi( szBuf, _T( "Button" ) ) )
   {
      if ( ( dwStyle & BS_OWNERDRAW ) == BS_OWNERDRAW )         
         return FALSE;     // Do not subclass ownerdraw buttons
      else if ( ( dwStyle & BS_GROUPBOX ) == BS_GROUPBOX ||
           ( dwStyle & BS_FLAT ) == BS_FLAT ) 
         return FALSE;     // Skip all group boxes and flat buttons
      else if ( ( dwStyle & BS_AUTOCHECKBOX ) == BS_AUTOCHECKBOX ||
                ( dwStyle & BS_CHECKBOX ) == BS_CHECKBOX ||                
                ( dwStyle & BS_3STATE ) == BS_3STATE )
         pCtl = new CCMCheckBox;
      else if ( ( dwStyle & BS_AUTORADIOBUTTON ) == BS_AUTORADIOBUTTON || 
           ( dwStyle & BS_RADIOBUTTON ) == BS_RADIOBUTTON )
         pCtl = new CCMRadioButton;
      else
         pCtl = new CCMPushButton;     // If none of the above then it must be a pushbutton!
   }
   else if ( !lstrcmpi( szBuf, _T( "ComboBox" ) ) )
   {      
      // Special case for simple comboboxes
      if ( ( dwStyle & 0x03 ) == CBS_SIMPLE )
      {
         hWnd = GetTopWindow( hWnd );
         while ( hWnd )
         {
            AddControl( hWnd );
            hWnd = GetNextWindow( hWnd, GW_HWNDNEXT );
         }
         return FALSE;
      }   
      else
         pCtl = new CCMComboBox;
   }
   else if ( !lstrcmpi( szBuf, _T( "Edit" ) ) )
   {
      // Edit window in simple combobox
      GetClassName( GetParent( hWnd ), szBuf, MAX_CLASSNAME );
      if ( !lstrcmpi( szBuf, _T( "ComboBox" ) ) && 
            ( GetWindowLong( GetParent( hWnd ), GWL_STYLE ) & 0x03 ) == CBS_SIMPLE ) 
         pCtl = new CCMEditCombo;
      else
      {
         if ( dwExStyle & WS_EX_CLIENTEDGE )
            pCtl = new CCMEdit;
      }
     #if defined _DEBUG
       lstrcpy( szBuf, _T( "Edit" ) );
     #endif
   }
   else if ( !lstrcmpi( szBuf, _T( "ListBox" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysListView32" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
      {
         pCtl = new CCMControl;
         AddControl( GetTopWindow( hWnd ) );  // Don't forget to add the header control
      }
   }
   else if ( !lstrcmpi( szBuf, _T( "SHELLDLL_DefView" ) ) ) // In open/save common dialogs
   {
      AddControl( GetTopWindow( hWnd ) );  // Add child ListView control
      return FALSE;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysTreeView32" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysDateTimePick32" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
      {
         pCtl = new CCMDateTime;
         if ( dwStyle & DTS_UPDOWN )
            AddControl( GetTopWindow( hWnd ) );  // Add up-down control as well
      }
   }
   else if ( !lstrcmpi( szBuf, _T( "SysMonthCal32" ) ) )
      pCtl = new CCMControl;
   else if ( !lstrcmpi( szBuf, _T( "msctls_updown32" ) ) )
      pCtl = new CCMUpDown;
   else if ( !lstrcmpi( szBuf, _T( "ComboLBox" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "ScrollBar" ) ) )
   {
      if ( !( dwStyle & SBS_SIZEBOX ) && !( dwStyle & SBS_SIZEGRIP ) )
         pCtl = new CCMScrollBar;
   }
   else if ( !lstrcmpi( szBuf, _T( "ComboBoxEx32" ) ) )
   {
      AddControl( GetTopWindow( hWnd ) );
      return FALSE;
   }
   else if ( !lstrcmpi( szBuf, _T( "msctls_hotkey32" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysIPAddress32" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMIPAddress;
   }
   else if ( !lstrcmpi( szBuf, _T( "msctls_trackbar32" ) ) )
      pCtl = new CCMTrackbar;
   else if ( !lstrcmpi( szBuf, _T( "RichEdit" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "RichEdit20W" ) ) )
   {
      if ( dwExStyle & WS_EX_CLIENTEDGE )
         pCtl = new CCMControl;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysHeader32" ) ) )
   {
      if ( dwStyle & HDS_BUTTONS )         
         pCtl = new CCMHeaderCtrl;
      else
         return FALSE;
   }
   else if ( !lstrcmpi( szBuf, _T( "ToolbarWindow32" ) ) )
   {
      // Skip the flat toolbars
      if ( dwStyle & TBSTYLE_FLAT )
         return FALSE;
      HWND hCtrl = GetTopWindow( hWnd );  // Add additional toolbar controls
      while ( hCtrl )
      {
         AddControl( hCtrl );
         hCtrl = GetNextWindow( hCtrl, GW_HWNDNEXT );
      }      
      pCtl = new CCMToolbar;
   }
   else if ( !lstrcmpi( szBuf, _T( "SysTabControl32" ) ) )
   {
      AddControl( GetTopWindow( hWnd ) );  // Also add the up-down control
      return FALSE;
   }
   else  // Unknown control, do not process
      return FALSE;

   if ( pCtl )
   {
#if defined(_VERBOSE_DUMP)
      _RPT2( _CRT_WARN, "CCoolControlsManager::AddControl, handle: %X, type: %s\n", 
                 hWnd, szBuf );
#endif // _VERBOSE_DUMP

      // Perform window subclassing
      pCtl->Subclass( hWnd, CCM_ControlProc );

      // Add the control to the map         
      m_ctrlMap.SetAt( hWnd, pCtl );
      
      if ( m_uTimerID == 0 ) // If timer is not initialized yet
      {    
         m_uTimerID = SetTimer( NULL, 0, CCM_TIMER_VAL, CCM_TimerProc );
#if defined(_VERBOSE_DUMP)
         _RPT0( _CRT_WARN, "CControlManager: Timer created\n" );
#endif // _VERBOSE_DUMP
         _ASSERT( m_uTimerID );    // Failed to create the timer
      }
      return TRUE;
   }
   return FALSE;
}

BOOL CCoolControlsManager::RemoveControl( HWND hWnd )
{
   BOOL bResult = TRUE;   
   CCMControl* pCtl;
   if ( m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) == FALSE )
      bResult =  FALSE;   

  #if defined _DEBUG
   TCHAR szBuf[MAX_CLASSNAME];
   GetClassName( hWnd, szBuf, MAX_CLASSNAME );         
#if defined(_VERBOSE_DUMP)
   _RPT2( _CRT_WARN, "CCoolControlsManager::RemoveControl, handle: %X, class: %s, ", 
           hWnd, szBuf );
   _RPT0( _CRT_WARN, bResult ? "OK\n" : "fail\n" );
#endif // _VERBOSE_DUMP
  #endif

   if ( bResult == TRUE )
   {
      // Unsubclass window and next remove it from the map
      pCtl->Unsubclass();
      m_ctrlMap.RemoveKey( hWnd );
      delete pCtl;      // Destroy object

      if ( m_ctrlMap.IsEmpty() )
      {
         KillTimer( NULL, m_uTimerID );
#if defined(_VERBOSE_DUMP)
         _RPT0( _CRT_WARN, "CCoolControlsManager: Timer killed, map is empty\n" );
#endif // _VERBOSE_DUMP
         m_uTimerID = 0;
      }  
#if defined(_VERBOSE_DUMP)
      else
         _RPT1( _CRT_WARN, "CCoolControlsManager: map has %d items\n", m_ctrlMap.GetCount() );       
#endif // _VERBOSE_DUMP
   }
   return bResult;
}

void CCoolControlsManager::AddDialog( HWND hWnd )
{   
   if ( hWnd  )
   {
      CCMDialog* pCtl = new CCMDialog;
      pCtl->Subclass( hWnd, CCM_DialogProc );    // Perform window subclassing
      m_dlgMap.SetAt( hWnd, pCtl ); // Add the dialog to the map   
   }
}

void CCoolControlsManager::RemoveDialog( HWND hWnd )
{   
   CCMDialog* pCtl;
   if ( m_dlgMap.Lookup( hWnd, (void*&)pCtl ) == TRUE )   
   {
      // Unsubclass window and next remove it from the map
      pCtl->Unsubclass();
      m_dlgMap.RemoveKey( hWnd );
      delete pCtl;      // Destroy object
   }
}

static void CALLBACK CCM_TimerProc( HWND /*hwnd*/, UINT /*uMsg*/, 
                                    UINT /*idEvent*/, DWORD /*dwTime*/ )
{ 
   g_ctrlManager.TimerProc();
}

void CCoolControlsManager::TimerProc()
{
   // Do not process when the map is empty or the capture is set
   if ( m_ctrlMap.IsEmpty() || GetCapture() != NULL )
      return;

   POINT point;
   GetCursorPos( &point );
   HWND hWnd = WindowFromPoint( point );
   
   CCMControl* pCtl;
   // Lookup for a window in the map      
   if ( m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) == FALSE ) // Not found
   {
      // If window does not exist in the map, it can be
      // a child of the control (e.g. edit control in ComboBox
      // or header control in ListView). If so, get the parent window and
      // carry on
      hWnd = GetParent( hWnd );            
      // Not our window, so just reset previous control and exit
      if ( hWnd == NULL || m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) == FALSE )
      {            
         // Not our window, so just reset previous control and exit
         if ( m_ctrlMap.Lookup( CCMControl::m_hWndOld, (void*&)pCtl ) == TRUE )
         {            
            pCtl->SetState( dsHover, 0 );
            CCMControl::m_hWndOld = NULL;
         }
         return;
      }      
   }

   if ( pCtl->NeedRedraw( point ) ) // Window has been found and needs to be redraw!
   {
      // First, reset old control (if any)      
      CCMControl* pCtlOld;
      if ( m_ctrlMap.Lookup( CCMControl::m_hWndOld, (void*&)pCtlOld ) == TRUE )            
      {         
         pCtlOld->SetState( dsHover, 0 );
         CCMControl::m_hWndOld = NULL;
      }

      // Redraw control under the cursor            
      pCtl->SetState( 0, dsHover );
      CCMControl::m_hWndOld = hWnd;
   }
}

///////////////////////////////////////////////////////////////////////
// All messages from subclassed dialogs will come here

static LRESULT CALLBACK CCM_DialogProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{  
   // Try to find dialog in the dialog map    
   CCoolControlsManager::CCMDialog* pCtl;
   if ( g_ctrlManager.m_dlgMap.Lookup( hWnd, (void*&)pCtl ) == FALSE )
   {
      // This is not our dialog, so just apply default processing
      return DefWindowProc( hWnd, uMsg, wParam, lParam ); 
   }

   // Otherwise, let the dialog to process this message
   return pCtl->WindowProc( uMsg, wParam, lParam );
}

///////////////////////////////////////////////////////////////////////
// All messages from subclassed controls will come here

static LRESULT CALLBACK CCM_ControlProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{  
   CCoolControlsManager::CCMControl* pCtl;

   // Try to find window in the control map
   if ( g_ctrlManager.m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) == FALSE )
   {
      // This is not our window, so just apply default processing
      return DefWindowProc( hWnd, uMsg, wParam, lParam ); 
   }

   // Otherwise, let the control to process this message
   return pCtl->WindowProc( uMsg, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////////
// CCMControl and derived classes

CCoolControlsManager::CCMControl::CCMControl()
{
   m_hWnd = NULL;
   m_oldWndProc = NULL;
   m_nState = dsNormal;
   m_nOldState = dsNormal;
}

void CCoolControlsManager::CCMControl::PrepareDraw( HDC& hDC, RECT& rect )
{
   GetWindowRect( m_hWnd, &rect );         
   OffsetRect( &rect, -rect.left, -rect.top );
   hDC = GetWindowDC( m_hWnd );
}

void CCoolControlsManager::CCMControl::DrawBorder()
{  
   HDC hDC;
   RECT rect;
   PrepareDraw( hDC, rect );

   if ( GetWindowLong( m_hWnd, GWL_EXSTYLE ) & WS_EX_CLIENTEDGE )
   {
      RECT rc;
      GetWindowRect( m_hWnd, &rc );
      POINT point = { 0, 0 };
      ClientToScreen( m_hWnd, &point );
      if ( point.x == rc.left + 3 )
         InflateRect( &rect, -1, -1 );
   }

   if ( IsFocused() == TRUE )
      m_nState |= dsFocus;    
   else
      m_nState &= ~dsFocus;    

   // Single line control looks better when this style is added
   if ( ( rect.bottom - rect.top ) < 30 ) 
      m_nState |= dsAlternate;
   else
      m_nState &= ~dsAlternate;

   if ( ( m_nOldState & dsHover && m_nState & dsHover ) ||
        ( m_nOldState & dsFocus && m_nState & dsFocus ) )
      ; // If previous state is the same as current state, do nothing
   else
   {         
      // Perform control-specific drawing routines                  
#if defined(_VERBOSE_DUMP)
      _RPT2( _CRT_WARN, "CCoolControlsManager::DrawBorder, handle: %X state: %d\n", m_hWnd, m_nState );
#endif // _VERBOSE_DUMP
      DrawControl( hDC, rect );
   }

   // Update old state
   m_nOldState = m_nState;

   ReleaseDC( WindowFromDC( hDC ), hDC );
}

BOOL CCoolControlsManager::CCMControl::NeedRedraw( const POINT& /*point*/ )
{
   return m_hWnd != m_hWndOld ? TRUE : FALSE;
}

void CCoolControlsManager::CCMCore::Subclass( HWND hWnd, WNDPROC wndNewProc )
{
   _ASSERT( hWnd );      // Do you really want to subclass a window that has a NULL handle?
   m_hWnd = hWnd;   

   // Store address of the original window procedure
   m_oldWndProc = (WNDPROC)GetWindowLong( m_hWnd, GWL_WNDPROC );

   // And set the new one
   SetWindowLong( m_hWnd, GWL_WNDPROC, (LONG)wndNewProc );
}

void CCoolControlsManager::CCMCore::Unsubclass()
{
   SetWindowLong( m_hWnd, GWL_WNDPROC, (LONG)m_oldWndProc );
}

LRESULT CCoolControlsManager::CCMControl::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      // Generic messages
      case WM_KILLFOCUS:         
      case WM_SETFOCUS:
         DrawBorder();
         break;

      case WM_PAINT:
      case WM_NCPAINT:
      case WM_ENABLE:
         CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
         DrawBorder();
         return 0;

      case WM_NCDESTROY:
         // Unsubclass window and remove it from the map
         CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
         g_ctrlManager.RemoveControl( m_hWnd );
         return 0;
   }

   return CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
}

void CCoolControlsManager::CCMControl::DrawControl( HDC hDC, const RECT& rc )
{ 
   if ( m_nState & dsHoverMask )
   {
      Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                             COLOR_3DDKSHADOW, COLOR_3DLIGHT );
   }
   else
   {
      if ( IsWindowEnabled( m_hWnd ) == FALSE || m_nState & dsDisabled )
         Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                                COLOR_3DFACE, COLOR_3DFACE );
      else               
         Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                       m_nState & dsAlternate ? COLOR_3DHIGHLIGHT : COLOR_3DLIGHT, COLOR_3DLIGHT );
   }

   DrawScrollBars( hDC, rc );
}

void CCoolControlsManager::CCMControl::DrawScrollbarThumb( HDC hDC, const RECT& rc )
{
   if ( m_nState & dsHoverMask )
      Draw3dBorder( hDC, rc, COLOR_3DFACE, COLOR_3DDKSHADOW, 
                             COLOR_3DHIGHLIGHT, COLOR_3DSHADOW );
   else
      Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                             COLOR_3DFACE, COLOR_3DFACE );
}

void CCoolControlsManager::CCMControl::DrawScrollBars( HDC hDC, const RECT& rect )
{  
   const int nFrameSize  = GetSystemMetrics( SM_CXEDGE ); 
   const int nScrollSize = GetSystemMetrics( SM_CXHSCROLL );   

   RECT rc; 
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );  
   if ( dwStyle & WS_HSCROLL &&  dwStyle & WS_VSCROLL )
   {
      rc.left = rect.left + nFrameSize; rc.top = rect.bottom - nFrameSize - nScrollSize;
      rc.right = rect.right - nFrameSize - nScrollSize; rc.bottom = rect.bottom - nFrameSize;
      DrawScrollBar( hDC, rc, SB_HORZ );

      rc.left = rect.right - nFrameSize - nScrollSize; rc.top = rect.top + nFrameSize;
      rc.right = rect.right - nFrameSize; rc.bottom = rect.bottom - nFrameSize - nScrollSize;
      DrawScrollBar( hDC, rc, SB_VERT );
   }
   else if ( dwStyle & WS_VSCROLL )
   {
      rc.left = rect.right - nFrameSize - nScrollSize; rc.top = rect.top + nFrameSize;
      rc.right = rect.right - nFrameSize; rc.bottom = rect.bottom - nFrameSize;
      DrawScrollBar( hDC, rc, SB_VERT );
   }
   else if ( dwStyle & WS_HSCROLL )
   {
      rc.left = rect.left + nFrameSize; rc.top = rect.bottom - nFrameSize - nScrollSize;
      rc.right = rect.right - nFrameSize; rc.bottom = rect.bottom - nFrameSize;
      DrawScrollBar( hDC, rc, SB_HORZ );
   }
}

void CCoolControlsManager::CCMControl::DrawScrollBar( HDC hDC, const RECT& rect, 
                                                     int nType, BOOL bScrollbarCtrl )
{   
   int nScrollSize = GetSystemMetrics( SM_CXHSCROLL );

   // The minimal thumb size depends on the system version
   // For Windows 98 minimal thumb size is a half of scrollbar size 
   // and for Windows NT is always 8 pixels regardless of system metrics. 
   // I really don't know why.
   int nMinThumbSize;
   if ( GetVersion() & 0x80000000 ) // Windows 98 code
      nMinThumbSize = nScrollSize / 2;
   else                    
      nMinThumbSize = 8;
   
   // Calculate the arrow rectangles
   RECT rc1 = rect, rc2 = rect;   
   if ( nType == SB_HORZ )
   {
      if ( ( rect.right - rect.left ) < 2 * nScrollSize )
         nScrollSize = ( rect.right - rect.left ) / 2;

      rc1.right = rect.left + nScrollSize;
      rc2.left = rect.right - nScrollSize;
   }
   else // SB_VERT
   {
      if ( ( rect.bottom - rect.top ) < 2 * nScrollSize )
         nScrollSize = ( rect.bottom - rect.top ) / 2;

      rc1.bottom = rect.top + nScrollSize;      
      rc2.top = rect.bottom - nScrollSize;
   }   

   // Draw the scrollbar arrows
   DrawScrollbarThumb( hDC, rc1 );
   DrawScrollbarThumb( hDC, rc2 );

   // Disabled scrollbar never have a thumb
   if ( bScrollbarCtrl == TRUE && IsWindowEnabled( m_hWnd ) == FALSE )
      return;      
 
   SCROLLINFO si;
   si.cbSize = sizeof( SCROLLINFO );
   si.fMask = SIF_ALL;     
   GetScrollInfo( m_hWnd, bScrollbarCtrl ? SB_CTL : nType, &si );

   // Calculate the size and position of the thumb   
   int nRange = si.nMax - si.nMin + 1;      
   if ( nRange )
   {
      int nScrollArea = ( nType == SB_VERT ? ( rect.bottom - rect.top ) : ( rect.right - rect.left ) ) - 2 * nScrollSize;

      int nThumbSize; 
      if ( si.nPage == 0 ) // If nPage is not set then thumb has default size
         nThumbSize = GetSystemMetrics( SM_CXHTHUMB );
      else
         nThumbSize = max( MulDiv( si.nPage ,nScrollArea, nRange ), nMinThumbSize );

      if ( nThumbSize >= nScrollArea )
      {
         nThumbSize = nScrollArea;
         if ( bScrollbarCtrl == FALSE )
            return;
      }

      int nThumbPos;
      if ( UINT( nRange ) == si.nPage )
      {
         nThumbPos = 0;
         nThumbSize--;
      }
      else
         nThumbPos = MulDiv( si.nPos - si.nMin, nScrollArea - nThumbSize, nRange - si.nPage );

      if ( nType == SB_VERT )
      {
         rc1.top += nScrollSize + nThumbPos;
         rc1.bottom = rc1.top + nThumbSize;
      }
      else // SB_HORZ
      {
         rc1.left += nScrollSize + nThumbPos;
         rc1.right = rc1.left + nThumbSize;
      }

      if ( nThumbSize <= nScrollArea ) // Don't draw the thumb when it's larger than the scroll area
         DrawScrollbarThumb( hDC, rc1 );
   }   
}

BOOL CCoolControlsManager::CCMControl::IsFocused()
{ 
   return m_hWnd == GetFocus() ? TRUE : FALSE;
}

//////////////////////////////////////////////////////////////////////////////
// CCMEdit class

void CCoolControlsManager::CCMEdit::DrawControl( HDC hDC, const RECT& rc )
{
   RECT rect = rc;

   // Check if edit window has an associated up-down control.
   // If so draw a border around both controls
   HWND hWnd = GetNextWindow( m_hWnd, GW_HWNDNEXT );

   if ( hWnd ) 
   {
      TCHAR szBuf[MAX_CLASSNAME];
      // Retrieve window class name
      GetClassName( hWnd, szBuf, MAX_CLASSNAME );
      if ( lstrcmpi( szBuf, _T( "msctls_updown32" ) ) == 0 )   // Up-down is found
      {
         DWORD dwStyle = GetWindowLong( hWnd, GWL_STYLE );
         if ( ( dwStyle & UDS_ALIGNRIGHT || dwStyle & UDS_ALIGNLEFT ) &&
              SendMessage( hWnd, UDM_GETBUDDY, 0, 0L ) == (LONG)m_hWnd )
         {         
            RECT rc;
            GetWindowRect( hWnd, &rc );
            const int nEdge = GetSystemMetrics( SM_CXEDGE );
            if ( dwStyle & UDS_ALIGNRIGHT )
               rect.right += ( rc.right - rc.left ) - nEdge;
            else // UDS_ALIGNLEFT
               rect.left -= ( rc.right - rc.left ) - nEdge;

            HDC hDC = GetDC( hWnd );   // We must draw the lines onto spin control DC

            COLORREF clr = GetSysColor( m_nState & dsHoverMask ? COLOR_3DDKSHADOW : COLOR_3DHIGHLIGHT );
            if ( !IsWindowEnabled( m_hWnd ) )
               clr = GetSysColor( COLOR_3DFACE );
            FillSolidRect( hDC, 1, 1, rc.right - rc.left - nEdge - 1, 1, clr );
            if ( dwStyle & UDS_ALIGNLEFT )
               FillSolidRect( hDC, 1, 1, 1, rc.bottom - rc.top - nEdge - 1, clr );

            ReleaseDC( hWnd, hDC );
         }
      }
   }

   if ( GetWindowLong( m_hWnd, GWL_STYLE ) & ES_READONLY )
      m_nState |= dsDisabled;
   else
      m_nState &= ~dsDisabled;
   CCMControl::DrawControl( hDC, rect );
}

LRESULT CCoolControlsManager::CCMEdit::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      case WM_ENABLE:
         {
            CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
            DrawBorder();
            HWND hWnd = GetNextWindow( m_hWnd, GW_HWNDNEXT );
            if ( hWnd ) 
            {
               TCHAR szBuf[MAX_CLASSNAME];
               // Retrieve window class name
               GetClassName( hWnd, szBuf, MAX_CLASSNAME );
               if ( lstrcmpi( szBuf, _T( "msctls_updown32" ) ) == 0 &&   // Up-down is found
                  SendMessage( hWnd, UDM_GETBUDDY, 0, 0L ) == (LONG)m_hWnd )
                     PostMessage( hWnd, WM_PAINT, 0, 0L );  // Repaint up-down too
            }         
         }
         return 0;

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }
}

//////////////////////////////////////////////////////////////////////////////
// CCMComboBox class

void CCoolControlsManager::CCMComboBox::DrawControl( HDC hDC, const RECT& rect )
{
   // First, draw borders around the control   
   CCMControl::DrawControl( hDC, rect );

   // Now, we have to draw borders around the drop-down arrow
   RECT rc = rect;
   InflateRect( &rc, -2, -2 );
   rc.left = rc.right - GetSystemMetrics( SM_CXHSCROLL );
   
   if ( IsWindowEnabled( m_hWnd ) == TRUE )
   {
      if ( m_nState & dsHoverMask )
         Draw3dBorder( hDC, rc, COLOR_3DFACE, COLOR_3DDKSHADOW,
                                COLOR_3DHIGHLIGHT, COLOR_3DSHADOW );
      else
         Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                                COLOR_3DFACE, COLOR_3DFACE );
   }
   else
      Draw3dBorder( hDC, rc, COLOR_3DFACE, COLOR_3DFACE,
                             COLOR_3DFACE, COLOR_3DFACE );
}

BOOL CCoolControlsManager::CCMComboBox::IsFocused()
{ 
   // Special case for drop-down and simple ComboBoxes 
   // which contain child edit control and focus always 
   // goes to that edit window   
   if ( ( GetWindowLong( m_hWnd, GWL_STYLE ) & 0x03 ) == CBS_DROPDOWN )
   {
      HWND hWnd = GetTopWindow( m_hWnd );
      if ( hWnd && hWnd == GetFocus() )
         return TRUE;
   }

   return CCMControl::IsFocused();
}

LRESULT CCoolControlsManager::CCMComboBox::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      // Drop-down ComboBox receives neither WM_SETFOCUS nor WM_KILLFOCUS
      // Instead, it receives these next two messages
      case WM_LBUTTONUP:      // For kill focus
         if ( lParam == -1 )
            DrawBorder();
         break;

      case WM_COMMAND:
         if ( HIWORD( wParam ) == EN_SETFOCUS )
            DrawBorder();
         break;

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }

   return CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////////
// CCMDateTime class

void CCoolControlsManager::CCMDateTime::DrawControl( HDC hDC, const RECT& rc )
{
   if ( GetWindowLong( m_hWnd, GWL_STYLE ) & DTS_UPDOWN )
      CCMControl::DrawControl( hDC, rc );
   else
      CCMComboBox::DrawControl( hDC, rc );
}

//////////////////////////////////////////////////////////////////////////////
// CCMPushButton class

void CCoolControlsManager::CCMPushButton::DrawControl( HDC hDC, const RECT& rc )
{
   BOOL bDefault = FALSE;
   // Unfortunately BS_DEFPUSHBUTTON is defined as 0x00000001L,
   // and BS_OWNERDRAW as 0x0000000BL (see winuser.h) so we cannot
   // determine the default button for owner-draw controls
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE ) & BS_OWNERDRAW;

   if ( dwStyle != BS_OWNERDRAW )
   {
      if ( dwStyle == BS_DEFPUSHBUTTON && IsWindowEnabled( m_hWnd ) )
         bDefault = TRUE;
   }

   int nCheck = SendMessage( m_hWnd, BM_GETCHECK, 0, 0 );
   if ( m_nState & dsHoverMask )
   {
      if ( bDefault == TRUE )
      {
         Draw3dBorder( hDC, rc, COLOR_3DDKSHADOW, COLOR_3DDKSHADOW,
                                COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,
                                COLOR_3DLIGHT, COLOR_3DSHADOW );
      }
      else
      {
         if ( nCheck )
            Draw3dBorder( hDC, rc, COLOR_3DDKSHADOW, COLOR_3DHIGHLIGHT,
                                   COLOR_3DSHADOW, COLOR_3DLIGHT );
         else
            Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,
                                   COLOR_3DLIGHT, COLOR_3DSHADOW,
                                   COLOR_3DFACE, COLOR_3DFACE );
      }
   }
   else
   {
      if ( bDefault == TRUE )
      {
         Draw3dBorder( hDC, rc, COLOR_3DDKSHADOW, COLOR_3DDKSHADOW,
                                COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                                COLOR_3DFACE, COLOR_3DFACE );
      }
      else
      {
         if ( nCheck )
            Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                                   COLOR_3DFACE, COLOR_3DFACE );
         else
            Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                                   COLOR_3DFACE, COLOR_3DFACE,
                                   COLOR_3DFACE, COLOR_3DFACE );
      }
   }      
}

LRESULT CCoolControlsManager::CCMPushButton::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      // Button messages
      case BM_SETCHECK:
      case WM_SETTEXT:
         CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
         DrawBorder();
         return 0;

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }
}

//////////////////////////////////////////////////////////////////////////////
// CCMCheckBox class

void CCoolControlsManager::CCMCheckBox::DrawControl( HDC hDC, const RECT& rect )
{
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
   
   if ( dwStyle & BS_PUSHLIKE )
   {
      CCMPushButton::DrawControl( hDC, rect );
      return;
   }  

   RECT rc;
   
   // Checkmark square size, hard coded here because I couldn't find any
   // method to obtain this value from the system.
   // Maybe someone else knows how to do it? If so, please let me know!
   const int nCheckSize = 13;
   
   if ( ( dwStyle & BS_VCENTER ) == BS_VCENTER )
      rc.top = rect.top + ( ( rect.bottom - rect.top ) - nCheckSize ) / 2;
   else if ( dwStyle & BS_TOP )
      rc.top = rect.top + 1;
   else if ( dwStyle & BS_BOTTOM )
      rc.top = rect.bottom - nCheckSize - 2;
   else  // Default
      rc.top = rect.top + ( ( rect.bottom - rect.top ) - nCheckSize ) / 2;

   if ( dwStyle & BS_LEFTTEXT )
      rc.left = rect.right - nCheckSize;
   else
      rc.left = rect.left;

   rc.right = rc.left + nCheckSize;
   rc.bottom = rc.top + nCheckSize;

   if ( m_nState & dsHoverMask )
   {
      Draw3dBorder( hDC, rc, COLOR_3DDKSHADOW, COLOR_3DHIGHLIGHT,
                             COLOR_3DSHADOW, COLOR_3DFACE );
   }
   else
   {            
      if ( IsWindowEnabled( m_hWnd ) == TRUE ) 
      {
         int nState = SendMessage( m_hWnd, BM_GETCHECK, 0, 0L );
         Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                                nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW, 
                                nState == 2 ? COLOR_3DHIGHLIGHT : COLOR_WINDOW );
      }
      else
         Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                                COLOR_3DFACE, COLOR_3DFACE );
   }
}

//////////////////////////////////////////////////////////////////////////////
// CCMRadioButton class

void CCoolControlsManager::CCMRadioButton::DrawFrame( POINT* ptArr, int nColor, 
                                                     HDC hDC, int xOff, int yOff )
{
   for ( int i = 0; ; i++ )
   {
      if ( !ptArr[i].x && !ptArr[i].y )
         return;

      SetPixel( hDC, ptArr[i].x + xOff, ptArr[i].y + yOff, GetSysColor( nColor ) );
   }
}

void CCoolControlsManager::CCMRadioButton::DrawControl( HDC hDC, const RECT& rect )
{
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );

   if ( dwStyle & BS_PUSHLIKE )
   {
      CCMPushButton::DrawControl( hDC, rect );
      return;
   }  

   const int nRadioSize = 12;
   RECT rc;
   
   if ( ( dwStyle & BS_VCENTER ) == BS_VCENTER )
      rc.top = rect.top + ( ( rect.bottom - rect.top ) - nRadioSize - 1 ) / 2;
   else if ( dwStyle & BS_TOP )
      rc.top = rect.top + 1;
   else if ( dwStyle & BS_BOTTOM )
      rc.top = rect.bottom - nRadioSize - 3;
   else  // Default
      rc.top = rect.top + ( ( rect.bottom - rect.top ) - nRadioSize - 1 ) / 2;
   
   if ( dwStyle & BS_LEFTTEXT )
      rc.left = rect.right - nRadioSize;
   else
      rc.left = rect.left + 1;

   rc.right = rc.left + nRadioSize;
   rc.bottom = rc.top + nRadioSize;

   POINT pt1[] = { 
                  { 1,9 },{ 1,8 },
                  { 0,7 },{ 0,6 },{ 0,5 },{ 0,4 },
                  { 1,3 },{ 1,2 },
                  { 2,1 },{ 3,1 },
                  { 4,0 },{ 5,0 },{ 6,0 },{ 7,0 },
                  { 8,1 },{ 9,1 },
                  { 0,0 }
               };  
               
   POINT pt2[] = { 
                  { 2,8 },
                  { 1,7 },{ 1,6 },{ 1,5 },{ 1,4 },
                  { 2,3 },{ 2,2 },
                  { 3,2 },
                  { 4,1 },{ 5,1 },{ 6,1 },{ 7,1 },
                  { 8,2 },{ 9,2 },
                  { 0,0 }
               };  


   POINT pt3[] = { 
                  { 2,9 },{ 3,9 },
                  { 4,10 },{ 5,10 },{ 6,10 },{ 7,10 },
                  { 8,9 },{ 9,9 },
                  { 9,8 },
                  { 10,7 },{ 10,6 },{ 10,5 },{ 10,4 },
                  { 9,3 },
                  { 0,0 }
               };  

   POINT pt4[] = { 
                  { 2,10 },{ 3,10 },
                  { 4,11 },{ 5,11 },{ 6,11 },{ 7,11 },
                  { 8,10 },{ 9,10 },
                  { 10,9 },{ 10,8 },
                  { 11,7 },{ 11,6 },{ 11,5 },{ 11,4 },
                  { 10,3 },{ 10,2 },
                  { 0,0 }
               };  

   if ( m_nState & dsHoverMask )
   {
      DrawFrame( pt1, COLOR_3DSHADOW,
                      hDC, rc.left, rc.top );
      DrawFrame( pt2, COLOR_3DDKSHADOW,
                      hDC, rc.left, rc.top );
      DrawFrame( pt3, COLOR_3DFACE,
                      hDC, rc.left, rc.top );
      DrawFrame( pt4, COLOR_WINDOW,
                      hDC, rc.left, rc.top );
   }
   else
   {
      if ( IsWindowEnabled( m_hWnd ) == TRUE ) 
      {  
         DrawFrame( pt1, COLOR_3DSHADOW,
                         hDC, rc.left, rc.top );
         DrawFrame( pt2, COLOR_WINDOW,
                         hDC, rc.left, rc.top );
         DrawFrame( pt3, COLOR_3DFACE,
                         hDC, rc.left, rc.top );
         DrawFrame( pt4, COLOR_WINDOW,
                         hDC, rc.left, rc.top );                  
      }
      else
      {
         DrawFrame( pt1, COLOR_3DSHADOW,
                         hDC, rc.left, rc.top );
         DrawFrame( pt2, COLOR_3DFACE,
                         hDC, rc.left, rc.top );
         DrawFrame( pt3, COLOR_3DFACE,
                         hDC, rc.left, rc.top );
         DrawFrame( pt4, COLOR_3DHIGHLIGHT,
                         hDC, rc.left, rc.top );
      }
   }   
}

//////////////////////////////////////////////////////////////////////////////
// CCMUpDown class

void CCoolControlsManager::CCMUpDown::DrawButton( HDC hDC, const RECT& rc )
{
   // If associated edit control is disabled
   // draw up-down as disabled so well
   BOOL bEnabled = IsWindowEnabled( m_hWnd );
   HWND hWnd = (HWND)SendMessage( m_hWnd, UDM_GETBUDDY, 0, 0L );
   if ( hWnd )
      bEnabled = IsWindowEnabled( hWnd );

   if ( bEnabled && m_nState & dsHoverMask )
      Draw3dBorder( hDC, rc, COLOR_3DFACE, COLOR_3DDKSHADOW,
                             COLOR_3DHIGHLIGHT, COLOR_3DSHADOW );
   else
      Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                             COLOR_3DFACE, COLOR_3DFACE );
}

void CCoolControlsManager::CCMUpDown::DrawControl( HDC hDC, const RECT& rect )
{         
   RECT rc = rect;
   CCMControl* pCtl = NULL;
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
   HWND hWnd = (HWND)SendMessage( m_hWnd, UDM_GETBUDDY, 0, 0L );
   if ( hWnd && ( dwStyle & UDS_ALIGNRIGHT || dwStyle & UDS_ALIGNLEFT ) )
   {
      if ( dwStyle & UDS_ALIGNLEFT )
         rc.left += 2;
      else   // UDS_ALIGNRIGHT
         rc.right -= 2;
      rc.top += 2;
      rc.bottom -= 2;
                 
      if ( g_ctrlManager.m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) && 
           !( pCtl->GetState() & dsHoverMask ) )
      {
         COLORREF clr1 = GetSysColor( IsWindowEnabled( hWnd ) ? COLOR_3DHIGHLIGHT : COLOR_3DFACE );
         COLORREF clr2 = GetSysColor( IsWindowEnabled( hWnd ) ? COLOR_3DLIGHT : COLOR_3DFACE );

         FillSolidRect( hDC, rc.left, rc.top - 1,
                             rc.right, 1,
                             clr1 );
         FillSolidRect( hDC, rc.left, rc.bottom,
                             rc.right, 1,                                  
                             clr2 );

         if ( dwStyle & UDS_ALIGNLEFT )
            FillSolidRect( hDC, rc.left - 1, rc.top - 1,
                                1, rc.bottom,
                                clr1 );
         else
            FillSolidRect( hDC, rc.right, rc.top - 1,
                                1, rc.bottom,
                                clr2 );
      }
   }

   RECT r = rc;
   if ( dwStyle & UDS_HORZ )
   {
      r.right = r.left + ( rc.right - rc.left ) / 2;
      DrawButton( hDC, r );

      r.left = r.right + ( rc.right - rc.left ) % 2;
      r.right = rc.right;
      DrawButton( hDC, r );
   }
   else
   {
      r.bottom = r.top + ( rc.bottom - rc.top ) / 2;
      DrawButton( hDC, r );

      r.top = r.bottom + ( rc.bottom - rc.top ) % 2;
      r.bottom = rc.bottom;
      DrawButton( hDC, r );
   }

   if ( pCtl == NULL )  // Get parent (e.g. for datetime with up-down controls)
   {
      hWnd = GetParent( m_hWnd );
      g_ctrlManager.m_ctrlMap.Lookup( hWnd, (void*&)pCtl );
   }

   if ( pCtl && IsWindowEnabled( hWnd ) )   // Redraw parent or buddy if neccesary
   {
      if ( m_nState & dsHoverMask )
         pCtl->SetState( 0, dsHover );
      else
         pCtl->SetState( dsHover, 0 );
   }
}

//////////////////////////////////////////////////////////////////////////////
// CCMEditCombo class

void CCoolControlsManager::CCMEditCombo::PrepareDraw( HDC& hDC, RECT& rect )
{
   GetWindowRect( m_hWnd, &rect );
   InflateRect( &rect, 3, 3 );
   OffsetRect( &rect, -rect.left, -rect.top );
   // Draw onto that DC that is most suitable for given class   
   hDC = GetWindowDC( GetParent( m_hWnd ) );
}

//////////////////////////////////////////////////////////////////////////////
// CCMScrollBar class

void CCoolControlsManager::CCMScrollBar::DrawControl( HDC hDC, const RECT& rc )
{  
   DrawScrollBar( hDC, rc, 
             ( GetWindowLong( m_hWnd, GWL_STYLE ) & SBS_VERT ) ? SB_VERT : SB_HORZ,
             TRUE );
}

LRESULT CCoolControlsManager::CCMScrollBar::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      // Scrollbar messages
      case SBM_SETPOS:
         if ( !lParam )  // redraw flag
            break;

      case SBM_SETSCROLLINFO:      
         if ( !wParam )  // redraw flag
            break;

      case SBM_SETRANGEREDRAW:
         CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
         DrawBorder();
         return 0;

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }

   return CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////////
// CCMHeaderCtrl class

void CCoolControlsManager::CCMHeaderCtrl::DrawButton( HDC hDC, const RECT& rc, int nState )
{
   if ( nState & dsHoverMask )
      Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,
                             COLOR_3DLIGHT, COLOR_3DSHADOW );
   else
      Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                             COLOR_3DFACE, COLOR_3DFACE );      
}

void CCoolControlsManager::CCMHeaderCtrl::DrawControl( HDC hDC, const RECT& /*rc*/ )
{
   int nOldItem = m_nItem;
   m_nItem = -1;

   RECT rc;
   POINT point;
   GetCursorPos( &point );

   // This code fails if we will have standalone header control but such cases are rare...
   HWND hWnd = GetParent( m_hWnd ); 
   GetClientRect( GetParent( m_hWnd ), &rc );
   ScreenToClient( GetParent( m_hWnd ), &point );
   // Test if mouse pointer is within the client area of the list control
   BOOL bInView = PtInRect( &rc, point );    

   GetClientRect( m_hWnd, &rc );
   rc.right = 0;
   GetCursorPos( &point );
   ScreenToClient( m_hWnd, &point );
   hDC = GetDC( m_hWnd );
   
   int nState;
   int nCount = SendMessage( m_hWnd, HDM_GETITEMCOUNT, 0, 0L );   

// #HK990508: ADDED
int *piArray = (int *)alloca (nCount*sizeof(int));

   SendMessage (m_hWnd, HDM_GETORDERARRAY, nCount, LPARAM(piArray));
// #HK990508

   for ( int i = 0; i < nCount; i++ )
   {
      HDITEM hi;
      hi.mask = HDI_WIDTH;
      SendMessage( m_hWnd, HDM_GETITEM, piArray[i], (LPARAM)&hi );		// #HK990508: i --> piArray[i]
      rc.left = rc.right;
      rc.right = rc.left + hi.cxy;
      nState = 0;
      if ( bInView && PtInRect( &rc, point ) )							// #HK990508: & --> &&
      {
         nState = dsHover;
         m_nItem = i;
      }
      DrawButton( hDC, rc, nState );
   }

   int l = rc.right;
   GetClientRect( m_hWnd, &rc );
   rc.left = l;
   DrawButton( hDC, rc, 0 );

   // If header is a child of ListView, redraw the list so 
   // it will indicate proper state      
   CCMControl* pCtl;   
   if ( g_ctrlManager.m_ctrlMap.Lookup( hWnd, (void*&)pCtl ) )
   {
      if ( m_nItem >= 0 )
         pCtl->SetState( 0, dsHover );
      else if ( nOldItem >= 0 )
         pCtl->SetState( dsHover, 0 );
   }

   ReleaseDC( m_hWnd, hDC );
}

BOOL CCoolControlsManager::CCMHeaderCtrl::NeedRedraw( const POINT& point )
{
   RECT rc;
   GetClientRect( m_hWnd, &rc );
   rc.right = 0;

   POINT pt = point;
   ScreenToClient( m_hWnd, &pt );

   int nItem = -1;
   int nCount = SendMessage( m_hWnd, HDM_GETITEMCOUNT, 0, 0L );

// #HK990508: ADDED
int *piArray = (int *)alloca (nCount*sizeof(int));

   SendMessage (m_hWnd, HDM_GETORDERARRAY, nCount, LPARAM(piArray));
// #HK990508

   for ( int i = 0; i < nCount; i++ )
   {
      HDITEM hi;
      hi.mask = HDI_WIDTH;      
      SendMessage( m_hWnd, HDM_GETITEM, piArray[i], (LPARAM)&hi );		// #HK990508: i --> piArray[i]
      rc.left = rc.right;
      rc.right = rc.left + hi.cxy;
      if ( PtInRect( &rc, pt ) )
      {
         nItem = i;
         break;
      }
   }

   if ( m_hWnd != m_hWndOld || ( m_hWnd == m_hWndOld && m_nItem != nItem ) )
      return TRUE;
   return FALSE;
}

//////////////////////////////////////////////////////////////////////////////
// CCMTrackbar class

void CCoolControlsManager::CCMTrackbar::DrawThumb( HDC hDC, const RECT& rc )
{
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );

   if ( dwStyle & TBS_BOTH )
   {
      FillSolidRect( hDC, rc, GetSysColor( COLOR_3DFACE ) );
      if ( m_nState & dsHoverMask )
         Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,
                                COLOR_3DLIGHT, COLOR_3DSHADOW );
      else
         Draw3dBorder( hDC, rc, COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                                COLOR_3DFACE, COLOR_3DFACE );      
      return;
   }
   
   HPEN penHighlight = CreatePen( PS_SOLID, 1, GetSysColor( COLOR_3DHIGHLIGHT ) );
   HPEN penLight = CreatePen( PS_SOLID, 1, GetSysColor( m_nState & dsHoverMask ? COLOR_3DLIGHT : COLOR_3DFACE ) );
   HPEN penDkShadow = CreatePen( PS_SOLID, 1, GetSysColor( m_nState & dsHoverMask ? COLOR_3DDKSHADOW : COLOR_3DSHADOW ) );
   HPEN penShadow = CreatePen( PS_SOLID, 1, GetSysColor( m_nState & dsHoverMask ? COLOR_3DSHADOW : COLOR_3DFACE ) );

   int n;
   if ( dwStyle & TBS_VERT )
   {
      if ( dwStyle & TBS_LEFT )
      {    
         n = ( rc.bottom - rc.top ) / 2 + 1;

         FillSolidRect( hDC, rc, GetSysColor( COLOR_3DFACE ) );
      
         HPEN hOldPen = (HPEN)SelectObject( hDC, penHighlight );
         MoveToEx( hDC, rc.right - 2, rc.top, NULL );
         LineTo( hDC, rc.left + n - 1, rc.top );
         LineTo( hDC, rc.left, rc.top + n - 1 );         
         
         SelectObject( hDC, penDkShadow );
         LineTo( hDC, rc.left + n - 1, rc.bottom - 1 );
         LineTo( hDC, rc.right - 1, rc.bottom - 1 );
         LineTo( hDC, rc.right - 1, rc.top - 1 );

         SelectObject( hDC, penLight );
         MoveToEx( hDC, rc.right - 3, rc.top + 1, NULL );
         LineTo( hDC, rc.left + n - 1, rc.top + 1 );
         LineTo( hDC, rc.left + 1, rc.top + n - 1 );

         SelectObject( hDC, penShadow );         
         LineTo( hDC, rc.left + n - 1, rc.bottom - 2 );
         LineTo( hDC, rc.right - 2, rc.bottom - 2 );
         LineTo( hDC, rc.right - 2, rc.top );

         SelectObject( hDC, hOldPen );         
      }
      else // TBS_RIGHT
      {
         n = ( rc.bottom - rc.top ) / 2 + 1;

         FillSolidRect( hDC, rc, GetSysColor( COLOR_3DFACE ) );
      
         HPEN hOldPen = (HPEN)SelectObject( hDC, penHighlight );
         MoveToEx( hDC, rc.left, rc.bottom - 2, NULL );
         LineTo( hDC, rc.left, rc.top );
         LineTo( hDC, rc.right - n, rc.top );
         LineTo( hDC, rc.right - 1, rc.top + n - 1 );

         SelectObject( hDC, penDkShadow );          
         MoveToEx( hDC, rc.left, rc.bottom - 1, NULL );
         LineTo( hDC, rc.right - n, rc.bottom - 1 );
         LineTo( hDC, rc.right, rc.top + n - 2 );         

         SelectObject( hDC, penLight );
         MoveToEx( hDC, rc.left + 1, rc.bottom - 3, NULL );
         LineTo( hDC, rc.left + 1, rc.top + 1 );
         LineTo( hDC, rc.right - n, rc.top + 1 );
         LineTo( hDC, rc.right - 2, rc.top + n - 1 );

         SelectObject( hDC, penShadow );
         MoveToEx( hDC, rc.left + 1, rc.bottom - 2, NULL );
         LineTo( hDC, rc.right - n, rc.bottom - 2 );
         LineTo( hDC, rc.right - 1, rc.top + n - 2 );         

         SelectObject( hDC, hOldPen );
      }      
   }
   else
   {
      if ( dwStyle & TBS_TOP )
      {      
         n = ( rc.right - rc.left ) / 2 + 1;

         FillSolidRect( hDC, rc, GetSysColor( COLOR_3DFACE ) );
      
         HPEN hOldPen = (HPEN)SelectObject( hDC, penHighlight );
         MoveToEx( hDC, rc.left + n - 2, rc.top + 1, NULL );
         LineTo( hDC, rc.left, rc.top + n - 1 );
         LineTo( hDC, rc.left, rc.bottom - 1 );

         SelectObject( hDC, penDkShadow );          
         LineTo( hDC, rc.right - 1, rc.bottom - 1 );
         LineTo( hDC, rc.right - 1, rc.top + n - 1 );
         LineTo( hDC, rc.left + n - 2, rc.top - 1 );

         SelectObject( hDC, penLight );
         MoveToEx( hDC, rc.left + n - 2, rc.top + 2, NULL );
         LineTo( hDC, rc.left + 1, rc.top + n - 1 );
         LineTo( hDC, rc.left + 1, rc.bottom - 2 );
     
         SelectObject( hDC, penShadow );
         LineTo( hDC, rc.right - 2, rc.bottom - 2 );
         LineTo( hDC, rc.right - 2, rc.top + n - 1 );
         LineTo( hDC, rc.left + n - 2, rc.top );

         SelectObject( hDC, hOldPen );
      }
      else // TBS_BOTTOM
      {
         n = ( rc.right - rc.left ) / 2 + 1;

         FillSolidRect( hDC, rc, GetSysColor( COLOR_3DFACE ) );
               
         HPEN hOldPen = (HPEN)SelectObject( hDC, penHighlight );
         MoveToEx( hDC, rc.left + n - 2, rc.bottom - 2, NULL );
         LineTo( hDC, rc.left, rc.bottom - n );
         LineTo( hDC, rc.left, rc.top );
         LineTo( hDC, rc.right - 1, rc.top );

         SelectObject( hDC, penDkShadow );          
         LineTo( hDC, rc.right - 1, rc.bottom - n );
         LineTo( hDC, rc.left + n - 2, rc.bottom );

         SelectObject( hDC, penLight );
         MoveToEx( hDC, rc.left + n - 2, rc.bottom - 3, NULL );
         LineTo( hDC, rc.left + 1, rc.bottom - n );
         LineTo( hDC, rc.left + 1, rc.top + 1 );
         LineTo( hDC, rc.right - 2, rc.top + 1 );
     
         SelectObject( hDC, penShadow );
         LineTo( hDC, rc.right - 2, rc.bottom - n );
         LineTo( hDC, rc.left + n - 2, rc.bottom - 1 );

         SelectObject( hDC, hOldPen );
      }
   }

   DeleteObject( penHighlight );
   DeleteObject( penLight );
   DeleteObject( penDkShadow );
   DeleteObject( penShadow );
}

void CCoolControlsManager::CCMTrackbar::DrawControl( HDC hDC, const RECT& /*rect*/ )
{  
   hDC = GetDC( m_hWnd );
   DWORD dwStyle = GetWindowLong( m_hWnd, GWL_STYLE );
   
   RECT rc;   
   SendMessage( m_hWnd, TBM_GETCHANNELRECT, 0, (LPARAM)&rc );   

   // BUG!: Windows incorrectly calculates the channel rectangle for
   // sliders with TBS_VERT style, so we have to calculate the rectangle
   // in different manner. This bug appears on all Windows platforms!
   if ( dwStyle & TBS_VERT )
   {  
      int w = ( rc.right - rc.left );
      int h = ( rc.bottom - rc.top );
      rc.top = rc.left;
      rc.bottom = rc.left + w;

      RECT r;
      SendMessage( m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&r );         

      rc.left = r.left + ( ( r.right - r.left ) / 2 + 1 ) - h / 2;
      if ( dwStyle & TBS_LEFT )
         ;
      else if ( dwStyle & TBS_BOTH )
         rc.left -= 1;
      else
         rc.left -= 2;

      rc.right = rc.left + h;
   }

   // Draw the channel rect
   if ( m_nState & dsHoverMask )
      Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,                         
                             COLOR_3DDKSHADOW, COLOR_3DLIGHT );
   else
      Draw3dBorder( hDC, rc, COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,                         
                             COLOR_3DFACE, COLOR_3DFACE );
   
   // Draw the slider thumb
   if ( !( dwStyle & TBS_NOTHUMB ) )
   {
      SetRectEmpty( &rc );
      SendMessage( m_hWnd, TBM_GETTHUMBRECT, 0, (LPARAM)&rc );
      DrawThumb( hDC, rc );
   }

   ReleaseDC( m_hWnd, hDC );
}

//////////////////////////////////////////////////////////////////////////////
// CCMToolbar class

void CCoolControlsManager::CCMToolbar::DrawButton( HDC hDC, const RECT& rc, int nState )
{
   if ( nState & bsChecked )
   {
      if ( nState & bsHover )
         Draw3dBorder( hDC, rc,
                       COLOR_3DDKSHADOW, COLOR_3DHIGHLIGHT,
                       COLOR_3DSHADOW, COLOR_3DSHADOW );
      else
         Draw3dBorder( hDC, rc,
                       COLOR_3DSHADOW, COLOR_3DHIGHLIGHT,
                       COLOR_3DFACE, COLOR_3DFACE );
   }
   else
   {
      if ( nState & bsHover )
         Draw3dBorder( hDC, rc,
                       COLOR_3DHIGHLIGHT, COLOR_3DDKSHADOW,
                       COLOR_3DLIGHT, COLOR_3DSHADOW );
      else
         Draw3dBorder( hDC, rc,
                       COLOR_3DHIGHLIGHT, COLOR_3DSHADOW,
                       COLOR_3DFACE, COLOR_3DFACE );
   }
}

void CCoolControlsManager::CCMToolbar::DrawControl( HDC hDC, const RECT& /*rc*/ )
{
   if ( GetWindowLong( m_hWnd, GWL_STYLE ) & TBSTYLE_FLAT ) // Skip flat toolbars
      return;
      
   int nCount = SendMessage( m_hWnd, TB_BUTTONCOUNT, 0, 0L );

   hDC = GetDC( m_hWnd );  // We will draw toolbar buttons on the client DC

   POINT point;
   GetCursorPos( &point );
   ScreenToClient( m_hWnd, &point );
   
   m_nItem = -1;
   int nState = 0;
           
   for ( int i = 0; i < nCount; i++ )
   {     
      RECT rc;       
      TBBUTTON ti;
      SendMessage( m_hWnd, TB_GETBUTTON, i, (LPARAM)&ti );
      SendMessage( m_hWnd, TB_GETITEMRECT, i, (LPARAM)&rc );

      if ( !( ti.fsStyle & TBSTYLE_SEP ) )
      {                  
         nState = ( ti.fsState & TBSTATE_CHECKED ) ? bsChecked : bsNormal;
         if ( PtInRect( &rc, point ) == TRUE )
         {
            if ( ti.fsState & TBSTATE_ENABLED )
               nState |= bsHover;
            m_nItem = i;
         }         
         DrawButton( hDC, rc, nState );
      }
   }
      
   ReleaseDC( m_hWnd, hDC );
}

BOOL CCoolControlsManager::CCMToolbar::NeedRedraw( const POINT& point )
{
   int nCount = SendMessage( m_hWnd, TB_BUTTONCOUNT, 0, 0L );

   POINT pt = point;
   ScreenToClient( m_hWnd, &pt );
   int nItem = -1;                
   for ( int i = 0; i < nCount; i++ )
   {            
      TBBUTTON ti;      
      SendMessage( m_hWnd, TB_GETBUTTON, i, (LPARAM)&ti );

      if ( !( ti.fsStyle & TBSTYLE_SEP ) )
      {
         RECT rc;         
         SendMessage( m_hWnd, TB_GETITEMRECT, i, (LPARAM)&rc );
         if ( PtInRect( &rc, pt ) )
         {
            nItem = i;
            break;
         }
      }
   }

   if ( m_hWnd != m_hWndOld || ( m_hWnd == m_hWndOld && m_nItem != nItem ) )
      return TRUE;
   return FALSE;
}

LRESULT CCoolControlsManager::CCMToolbar::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {  
      case WM_PAINT:
      case WM_NCPAINT:
         m_nItem = -1;   // Redraw the whole toolbar unconditionally

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }
}

//////////////////////////////////////////////////////////////////////////////
// CCMIPAddress class

BOOL CCoolControlsManager::CCMIPAddress::IsFocused()
{
   HWND hWnd = GetTopWindow( m_hWnd );
   while ( hWnd )
   {
      if ( hWnd == GetFocus() )
         return TRUE;
      hWnd = GetNextWindow( hWnd, GW_HWNDNEXT );
   }

   return FALSE;
}

LRESULT CCoolControlsManager::CCMIPAddress::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      case WM_COMMAND:
         if ( HIWORD( wParam ) == EN_SETFOCUS || HIWORD( wParam ) == EN_KILLFOCUS )
            DrawBorder();
         break;

      default:
         return CCMControl::WindowProc( uMsg, wParam, lParam );
   }

   return CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
}

//////////////////////////////////////////////////////////////////////////////
// CCMDialog class

LRESULT CCoolControlsManager::CCMDialog::WindowProc( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {      
      case WM_PARENTNOTIFY:         
         if ( LOWORD( wParam ) == WM_CREATE )   // Add dynamically created controls to the map
            g_ctrlManager.AddControl( (HWND)lParam );
         break;

      case WM_NCDESTROY:
         // Unsubclass window and remove it from the map
         CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
         g_ctrlManager.RemoveDialog( m_hWnd );
         return 0;
   }

   return CallWindowProc( m_oldWndProc, m_hWnd, uMsg, wParam, lParam );
}

///////////////////////////////////////////////////////////////////////////////////
// Helper functions for drawing 3D frames (borrowed from CDC class)

void CCoolControlsManager::CCMControl::FillSolidRect( HDC hDC, int x, int y, int cx, int cy, COLORREF clr )
{
   SetBkColor( hDC, clr );
   RECT rect;
   SetRect( &rect, x, y, x + cx, y + cy );
   ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL );
}

void CCoolControlsManager::CCMControl::FillSolidRect( HDC hDC, const RECT& rect, COLORREF clr )
{
   SetBkColor( hDC, clr );
   ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL );
}

void CCoolControlsManager::CCMControl::Draw3dRect( HDC hDC, int x, int y, int cx, int cy,
                                                  COLORREF clrTopLeft, COLORREF clrBottomRight )
{
   FillSolidRect( hDC, x, y, cx - 1, 1, clrTopLeft );
   FillSolidRect( hDC, x, y, 1, cy - 1, clrTopLeft );
   FillSolidRect( hDC, x + cx, y, -1, cy, clrBottomRight );
   FillSolidRect( hDC, x, y + cy, cx, -1, clrBottomRight );
}

void CCoolControlsManager::CCMControl::Draw3dRect( HDC hDC, const RECT& rect,
                                                  COLORREF clrTopLeft, COLORREF clrBottomRight )
{
   Draw3dRect( hDC, rect.left, rect.top, rect.right - rect.left,
                    rect.bottom - rect.top, clrTopLeft, clrBottomRight );
}

void CCoolControlsManager::CCMControl::Draw3dBorder( HDC hDC, const RECT& rc, 
                                                    int nColor1, int nColor2,
                                                    int nColor3, int nColor4 )
{
   Draw3dRect( hDC, rc, GetSysColor( nColor1 ), GetSysColor( nColor2 ) );

   Draw3dRect( hDC, rc.left + 1, rc.top + 1, rc.right - rc.left - 2, rc.bottom - rc.top - 2, 
                        GetSysColor( nColor3 ), GetSysColor( nColor4 ) );
}

void CCoolControlsManager::CCMControl::Draw3dBorder( HDC hDC, const RECT& rc, 
                                                    int nColor1, int nColor2,
                                                    int nColor3, int nColor4,
                                                    int nColor5, int nColor6 )
{
   Draw3dRect( hDC, rc, GetSysColor( nColor1 ), GetSysColor( nColor2 ) );

   Draw3dRect( hDC, rc.left + 1, rc.top + 1, rc.right - rc.left - 2, rc.bottom - rc.top - 2, 
                        GetSysColor( nColor3 ), GetSysColor( nColor4 ) );
   Draw3dRect( hDC, rc.left + 2, rc.top + 2, rc.right - rc.left - 4, rc.bottom - rc.top - 4, 
                  GetSysColor( nColor5 ), GetSysColor( nColor6 ) );
}

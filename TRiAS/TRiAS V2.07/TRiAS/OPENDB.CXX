// OpenDBDialog in neuer Fassung ueber COMMDLG.DLL ----------------------------
// File: OPENDB.CXX

#include "triaspre.hxx"

#include <dlgs.h>

#include "opendb.h"
#include "opendb.hxx"           
#include "triasres.h"

extern HINSTANCE hInstance;
#if !defined(WIN32)
bool IsWin40 (void);
#endif

CDBDialog :: CDBDialog (bool fForceUser)
{
	m_pUser = NULL;
	m_pPasswd = NULL;
	m_fForceUser = fForceUser;

#if defined(WIN32)
	if (IsWin40()) 
		m_iFileOKMessage = 0;		// not used here
	else
#endif
	// Message registrieren
		m_iFileOKMessage = RegisterWindowMessage (FILEOKSTRING);
}

CDBDialog :: ~CDBDialog (void)
{
	DELETE (m_pUser);
	DELETE (m_pPasswd);  
}

// Konstruktor/Destruktor -----------------------------------------------------
COpenDBDlg :: COpenDBDlg (pWindow pW, LPCSTR pcTempl)
	    : COpenDialog (pW, (char *)pcTempl),
		  CDBDialog (true)
{
	m_fIsComFile = false;
		
#if defined(WIN32)
	if (IsWin40()) {
		AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDB40HookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(FILEOPEN40SUBDLG));
	} else
#endif
	{
	// SonderWünsche einstellen
		if (IsWinNT()) AddFlags (OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDBHookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(FILEOPENORD));
	}
	SetCustomData ((DWORD)(CDBBaseDialog *)this);
}


COpenDBDlg :: ~COpenDBDlg (void)
{
}


// Memberfunktionen -----------------------------------------------------------
char *CDBDialog :: GetUserName (char *pc, short iLen) const	// liefert UserNamen
{
	if (m_pUser == NULL) return NULL;
	
	if (pc == NULL) return m_pUser ? (m_pPasswd ? m_pUser : strlwr (m_pUser)) : NULL;

	strncpy (pc, m_pUser, iLen);
	pc[iLen-1] = '\0';

return m_pPasswd ? pc : strlwr (pc);
}
	
char *CDBDialog :: GetPassWord (char *pc, short iLen) const	// liefert Password
{
	if (m_pPasswd == NULL) return NULL;
	
	if (pc == NULL) return m_pPasswd;
	
	strncpy (pc, m_pPasswd, iLen);
	pc[iLen-1] = '\0';
	
return pc;
}


// Konstruktor/Destruktor -----------------------------------------------------
CNewDBDlg :: CNewDBDlg (pWindow pW, LPCSTR pcTempl)
	   : CSaveAsDialog (pW, (char *)pcTempl),
		 CDBDialog (false)
{
#if defined(WIN32)
	if (IsWin40()) {
		AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDB40HookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(FILEOPEN40SUBDLG));
	} else
#endif
	{
	// SonderWünsche einstellen
		if (IsWinNT()) AddFlags (OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDBHookFcn);
		SetTemplate (hInstance, MAKEINTRESOURCE(FILEOPENORD));
	}

	SetCaption (ResString (IDS_NEWDBCAPTION, 50).Addr());
	SetCustomData ((DWORD)(CDBBaseDialog *)this);
}


CNewDBDlg :: ~CNewDBDlg (void)
{
}

#if defined(WIN32)
CSaveAsDBDlg :: CSaveAsDBDlg (pWindow pW, bool fSaveAsCopy, LPCSTR pcTempl)
	   : CSaveAsDialog (pW, (char *)pcTempl),
		 CDBDialog (false)
{
	if (IsWin40()) {
		AddFlags (OFN_EXPLORER|OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDB40HookFcn);
	} else {
	// SonderWünsche einstellen
		if (IsWinNT()) AddFlags (OFN_LONGNAMES);
		SetHookFcn ((HOOKFCN)OpenDBHookFcn);
	}
	SetCaption (ResString (fSaveAsCopy ? 
					IDS_SAVEDBASCOPYCAPTION : 
					IDS_SAVEASDBCAPTION, 50));
	SetCustomData ((DWORD)(CDBBaseDialog *)this);
}


CSaveAsDBDlg :: ~CSaveAsDBDlg (void)
{
}
#endif


// HookFunktion ---------------------------------------------------------------
extern bool g_fCtl3dInit;

extern "C"
UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM lParam)
{
static CDBDialog *pDlg = NULL;

	switch (wMsg) {
	case WM_INITDIALOG:		// Pointer auf COpenDBDlg holen
		if (g_fCtl3dInit) 
			Ctl3dSubclassDlg (hDlg, CTL3D_ALL);
		pDlg = (CDBDialog *) (((OPENFILENAME *)lParam) -> lCustData);
		break;
		
	case WM_DESTROY:	// letzte Message an uns
		pDlg = NULL;		// AusgangsZustand wieder herstellen
		break;

	default:
		if (pDlg == NULL) break;
		if (wMsg == pDlg -> m_iFileOKMessage) {
		// OKButton ist gedrückt, nachsehen, ob NutzerName gegeben ist
		short iLen = (short)SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXTLENGTH, 0, 0L
				    ); 

			if (pDlg -> m_fForceUser && iLen == 0) {	
			// kein NutzerName gegeben, obwohl einer gefordert ist
				ErrorWindow (NULL, ResString (IDS_PARERROR,30),
						   ResString (IDS_NOUNAME, 120));

				SetFocus (GetDlgItem (hDlg, IDE_OPENDBUSERNAME));
				return TRUE;	// nicht weiterbearbeiten !
			} else if (iLen > 0) {
				DELETE (pDlg -> m_pUser);
				pDlg -> m_pUser = new char [iLen+2];
				if (pDlg -> m_pUser) {
					SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXT, iLen+1, 
						(LPARAM)pDlg -> m_pUser
					);
				}
			}
			
		// evtl. PassWord holen
			iLen = (short)SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD, 
						WM_GETTEXTLENGTH, 0, 0L
				      );
			if (iLen > 0) {
				DELETE (pDlg -> m_pPasswd);
				pDlg -> m_pPasswd = new char [iLen+2];
				if (pDlg -> m_pPasswd) {
					SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD,
						WM_GETTEXT, iLen+1, 
						(LPARAM)pDlg -> m_pPasswd
					);
				}
			}
		}
		break;
	}
			
return FALSE;	// erstmal alles weiterleiten
}

#if defined(WIN32)

// Diese Funktion wird nur unter 40 installiert und gerufen -------------------
extern "C" 
UINT EXPORTTRIAS APIENTRY OpenDB40HookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		{
		OFNOTIFY *pofn = (LPOFNOTIFY)lParam;
		CDBBaseDialog *pDlg = (CDBBaseDialog *) (pofn -> lpOFN -> lCustData);

			return pDlg -> HandleNotifications (hDlg, pofn);
		}

	default:		// no actions
		break;
	}
			
return FALSE;	// erstmal alles weiterleiten
}

// Notifikationen bearbeiten --------------------------------------------------
bool CDBBaseDialog :: HandleNotifications (HWND hDlg, LPOFNOTIFY pofn)
{
	switch (pofn->hdr.code) {
	case CDN_INITDONE:	// im Parent zentrieren
		{
		HWND hDlgP = ::GetParent(hDlg);
					
			CentreWindow (::GetParent (hDlgP), hDlgP);
		}
		return true;

	default:
		break;
	}

return false;
}

bool COpenDBDlg :: HandleNotifications (HWND hDlg, LPOFNOTIFY pofn)
{
	switch (pofn->hdr.code) {
	case CDN_INITDONE:	// im Parent zentrieren
		EnableWindow (GetDlgItem (hDlg, IDE_OPENDBUSERNAME), !IsComFile());
		break;

	case CDN_SELCHANGE:
		{	// Get the file specification from the common dialog.
		char szFile[_MAX_PATH+1];

			CommDlg_OpenSave_GetFilePath (GetParent(hDlg), szFile, sizeof(szFile));

		bool fFlag = (NOERROR == StgIsStorageFile (WideString(szFile))) ? true : false;

			SetComFile (fFlag);
			EnableWindow (GetDlgItem (hDlg, IDE_OPENDBUSERNAME), !fFlag);
		}
		return true;

	case CDN_FILEOK:		// user has pressed OK
		{
		// OKButton ist gedrückt, nachsehen, ob NutzerName gegeben ist
		short iLen = (short)SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXTLENGTH, 0, 0L
				    ); 

			if (iLen == 0 && !IsComFile()) {	
			// kein NutzerName gegeben, obwohl einer gefordert ist
				ErrorWindow (NULL, ResString (IDS_PARERROR,30),
						   ResString (IDS_NOUNAME, 120));

				SetFocus (GetDlgItem (hDlg, IDE_OPENDBUSERNAME));
				
				SetWindowLong (hDlg, DWL_MSGRESULT, true);
				return true;	// nicht weiterbearbeiten !
			} else if (iLen > 0) {
				DELETE (m_pUser);
				m_pUser = new char [iLen+2];
				if (m_pUser) {
					SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXT, iLen+1, 
						(LPARAM)m_pUser
					);
				}
			}
			
		// evtl. PassWord holen
			iLen = (short)SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD, 
						WM_GETTEXTLENGTH, 0, 0L
				      );
			if (iLen > 0) {
				DELETE (m_pPasswd);
				m_pPasswd = new char [iLen+2];
				if (m_pPasswd) {
					SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD,
						WM_GETTEXT, iLen+1, 
						(LPARAM)m_pPasswd
					);
				}
			}
		}
		return true;

	default:
		break;		// no other actions
	}

return CDBBaseDialog :: HandleNotifications (hDlg, pofn);
}

bool CNewDBDlg :: HandleNotifications (HWND hDlg, LPOFNOTIFY pofn)
{
	switch (pofn->hdr.code) {
/*	case CDN_SELCHANGE:
		{	// Get the file specification from the common dialog.
		char szFile[_MAX_PATH+1];

			CommDlg_OpenSave_GetFilePath (GetParent(hDlg), szFile, sizeof(szFile));

		bool fFlag = (NOERROR == StgIsStorageFile (WideString(szFile)) ? true : false;
		CDBDialog *pDlg = (CDBDialog *) (pofn -> lpOFN -> lCustData);

			pDlg -> SetComFile (fFlag);
			EnableWindow (GetDlgItem (hDlg, IDE_OPENDBUSERNAME), fFlag)
		}
		return true;
*/
/*	case CDN_TYPECHANGE:
		{
		OPENFILENAME *pOFN = (OPENFILENAME *)pofn -> lpOFN;

			pOFN -> nFilterIndex
		}
		return true;
*/
	case CDN_FILEOK:		// user has pressed OK
		{
		// OKButton ist gedrückt, nachsehen, ob NutzerName gegeben ist
		short iLen = (short)SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXTLENGTH, 0, 0L
				    ); 

			if (iLen > 0) {
				DELETE (m_pUser);
				m_pUser = new char [iLen+2];
				if (m_pUser) {
					SendDlgItemMessage (
						hDlg, 
						IDE_OPENDBUSERNAME, 
						WM_GETTEXT, iLen+1, 
						(LPARAM)m_pUser
					);
				}
			}
			
		// evtl. PassWord holen
			iLen = (short)SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD, 
						WM_GETTEXTLENGTH, 0, 0L
				      );
			if (iLen > 0) {
				DELETE (m_pPasswd);
				m_pPasswd = new char [iLen+2];
				if (m_pPasswd) {
					SendDlgItemMessage (
						hDlg, IDE_OPENDBPASSWD,
						WM_GETTEXT, iLen+1, 
						(LPARAM)m_pPasswd
					);
				}
			}
		}
		return true;

	default:
		break;		// no other actions
	}

return CDBBaseDialog :: HandleNotifications (hDlg, pofn);
}

#endif // WIN32




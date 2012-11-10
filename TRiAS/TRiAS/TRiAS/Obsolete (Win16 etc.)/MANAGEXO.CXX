// Klassendefinition für das Erweiterung-Lade/Entlade Dialogfenster -----------
// File: MANAGEXT.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <checklst.hxx>
#include "cextreg.hxx"
#include "managext.hxx"

extern bool g_fSystemAdm;

#if !defined(WIN32)
bool IsWin32s (void);
#endif

// Konstruktor/Destruktor -----------------------------------------------------
CManageExtDlg *CManageExtDlg :: CreateInstance (pWindow pW, ExtensionList &rEL)
{
CManageExtDlg *pDlg = new CManageExtDlg (pW, rEL);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}

return pDlg;
}

#pragma warning (disable: 4355)

CManageExtDlg :: CManageExtDlg (pWindow pW, ExtensionList &rEL)
	       : OwnerDrawDialogWindow (pW, MANAGEEXTENSIONS),
	         m_pbOK (this, IDOK),
		 m_pbCancel (this, IDCANCEL),
#if !defined(WIN32)
		 m_pbHelp (this, IDB_LOADHELP),
#endif // WIN32
		 m_pbInstall (this, IDB_INSTALL), 
		 m_pbRemove (this, IDB_REMOVE),
		 m_cbShowAll (this, IDC_SHOWALL),
		 m_rEL (rEL)
{
// Variablen initialisieren
	m_pExtName = NULL;
	m_pDLLName = NULL;
	m_pBuffer = NULL;

	m_pExtList = NULL;

	m_rgFlags = (EXTENSIONFLAG)0;

	m_fToLoad = false;
	m_fToUnload = false;
	m_fClickHasToggled = false;
	m_iCnt = 0;

	m_iCurrIndex = -1;

// Controls initialisieren
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32
	if (!g_fSystemAdm) {
		m_pbInstall.Hide();
		m_pbRemove.Hide();
		m_cbShowAll.Hide();
	}
}

#pragma warning (default: 4355)

CManageExtDlg :: ~CManageExtDlg (void)
{
	DELETE (m_pExtName);
	DELETE (m_pDLLName);
	DELETE (m_pBuffer);
	DELETE (m_pExtList);
}

bool CManageExtDlg :: FInit (void)
{
// internen Buffer anlegen
	m_pBuffer = new char [_MAX_PATH];
	if (m_pBuffer == NULL) return false;

// alle Erweiterungen in Liste aufnehemen
	if (!InitExtList())
		return false;

	m_pExtList -> ChangeCurrentIndex (-1);
	m_iCurrIndex = -1;
	m_pExtList -> SetFocus();
	m_pbRemove.Disable();

	m_cbShowAll.SetChecked (false);

return true;
}

bool CManageExtDlg :: InitExtList (bool fDelete)
{
// evtl. Liste löschen
	if (fDelete && m_pExtList) 
		m_pExtList -> Clear();

// Liste generieren 
	if (m_pExtList == NULL) {
		m_pExtList = new CCheckListBox (this, IDL_LOADLISTDLL);
		if (m_pExtList == NULL) return false;
	}

// Liste wieder hinzufügen
CTable r(m_rEL);
bool fShowAll = m_cbShowAll.isChecked();

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);
	Extension *pExt = (Extension *)l;

		if (l && l -> isGlobal() && (l -> isVisible() || fShowAll)) {
		int iIndex = m_pExtList -> AddItem (l -> ExtName().c_str());

			if (iIndex != LB_ERR) {
				m_pExtList -> SetItemChecked (iIndex, l -> isLoaded());
				if (l -> isLoaded())
					m_pExtList -> EnableItem (iIndex, l -> isUnLoadable());
				else
					m_pExtList -> EnableItem (iIndex, true);
			}
		}
	}

return true;
}

bool CManageExtDlg :: DrawEntireItem (DrawItemEvt e)
{
	return m_pExtList -> DrawItem (e);
}

bool CManageExtDlg :: DrawItemFocus (DrawItemEvt e)
{
	return m_pExtList -> FocusItem (e);
}

bool CManageExtDlg :: DrawItemSelect (DrawItemEvt e)
{
	return m_pExtList -> SelectItem (e);
}

bool CManageExtDlg :: DeleteItem (DeleteItemEvt e)
{
	return m_pExtList -> FreeItem (e.GetItemID());
}

void CManageExtDlg :: ButtonClick (ControlEvt e)
{
unsigned int uiID = e.GetControlID();

	switch (uiID) {
	case IDOK:
		EndDlg(1);
		break;

	case IDCANCEL:
		EndDlg(0);
		break;

	case IDB_INSTALL:
		{
		int iIndex = InstallExtension();

			m_pExtList -> ChangeCurrentIndex (iIndex);
			m_iCurrIndex = iIndex;
			m_pExtList -> SetFocus();
			if (iIndex >= 0 && m_pExtList -> IsItemEnabled (iIndex)) 
				m_pbRemove.Enable();
			else
				m_pbRemove.Disable();
		}
		break;

	case IDB_REMOVE:
		RemoveExtension (uiID);
		m_pbRemove.Disable();
		break;

	case IDB_LOADHELP:
		break;

	case IDC_SHOWALL:
		InitExtList (true);
		break;

	default:
		{
		int iIndex = m_pExtList -> GetItemIndex (uiID);

			if (iIndex >= 0 && GetNames (iIndex)) {
				if (toLoad())
					m_pExtList -> EnableItem (iIndex, isUnLoadable());
				else
					m_pExtList -> EnableItem (iIndex, true);

				m_pExtList -> ChangeCurrentIndex (iIndex);
				m_iCurrIndex = iIndex;
			}
		}
		break;
	}
}

void CManageExtDlg :: ListBoxSel (ControlEvt e)
{
int iIndex = m_pExtList -> GetCurrentIndex();

	m_fClickHasToggled = false;	// für alle Fälle

	if (m_pExtList -> IsItemEnabled()) {
		m_pbRemove.Enable();
		if (m_iCurrIndex == iIndex) {	// wenn nicht zum 1. mal, dann toggl'n
			m_pExtList -> ToggleItemChecked();
			m_fClickHasToggled = true;
		}
	} else
		m_pbRemove.Disable();

	m_iCurrIndex = iIndex;		// aktuelle Auswahl merken
}

void CManageExtDlg :: ListBoxClk (ControlEvt e)		// DoppelKlick
{
	if (m_pExtList -> IsItemEnabled()) {
		if (!m_fClickHasToggled)
		// wenn bei 1. Click nur Selection geändert wurde
			m_pExtList -> ToggleItemChecked();
		if (GetNames()) {
			if (toLoad())
				m_pExtList -> EnableItem (LB_ERR, isUnLoadable());
			else
				m_pExtList -> EnableItem (LB_ERR, true);
		}
	}
}

// ZugriffsFunktionen ---------------------------------------------------------
bool CManageExtDlg :: GetFirstExtName (void)
{
	return GetNames(m_iCnt = 0);
}

bool CManageExtDlg :: GetNextExtName (void)
{
	return GetNames(++m_iCnt);
}

bool CManageExtDlg :: GetNames (int iIndex)
{
// Bezeichner der DLL holen
	DELETE (m_pExtName);
	DELETE (m_pDLLName);

	if (!m_pExtList -> GetItem (m_pBuffer, _MAX_PATH, iIndex))
		return false;

	m_pExtName = StrDup (m_pBuffer, RC_LoadListSel);	// Bezeichner holen
	m_pDLLName = m_rEL.RetrieveDLLName (m_pExtName);	// Namen der DLL holen

	m_rgFlags = m_rEL.GetFlags(m_pDLLName);

HDEX hDexDummy;
bool fLoaded = m_rEL.isLoaded (m_pDLLName, hDexDummy);
bool fChecked = m_pExtList -> GetItemChecked (iIndex);

	m_fToLoad = !fLoaded && fChecked;
	m_fToUnload = fLoaded && !fChecked;
			
return true;
}

// Erweiterung dazuregistrieren oder aus dem System entfernen -----------------
bool CManageExtDlg :: RemoveExtension (unsigned int uiID)
{
int iIndex = m_pExtList -> GetItemIndex (uiID);

	if (!m_pExtList -> GetItem (m_pBuffer, _MAX_PATH, iIndex))
		return false;

LPSTR pDLL = m_rEL.RetrieveDLLName (m_pBuffer);
EXTENSIONFLAG rgFlags = m_rEL.GetFlags (pDLL);

	if (!(rgFlags & EF_Visible) || !(rgFlags & EF_UnLoadable)) {
	// eine nicht sichtbare Erweiterung soll gelöscht werden
	ResString resDelExtCap (IDS_DELETEEXTCAP, 64);
	ResString resDelExt (IDS_DELETEEXT, 256);
	MessBox mb (resDelExtCap, resDelExt, this);

		mb.SetType (YesNoButtons|QuestionMarkIcon);
		if (mb.Show() == NoReply) {
			DELETE(pDLL);
			return false;
		}
	}

LOADEXTENSIONEX LE;

	LE.m_pDesc = pDLL;
	LE.m_pName = m_pBuffer;
	LE.m_iMode = LEFullLoad;	// vollständig entladen
	LE.m_fGlobal = true;

bool iResult = DEX_ExternalUnLoadExtensionEx (LE);

	DELETE (pDLL);
	if (iResult) {
		CExtReg(string(m_pBuffer)).Unregister();	// aus RegDB rauswerfen
		InitExtList (true);
	}

return iResult;
}

int CManageExtDlg :: InstallExtension (void)
{
COpenDialog OpenDlg (this, (char *)ResString (IDS_EXTENSIONTEMPLATE, 100).Addr());

	OpenDlg.SetCaption (ResString (IDS_LOADEXTCAPTION, 64));
	OpenDlg.AddFlags (OFN_HIDEREADONLY|OFN_NOCHANGEDIR);

char cbFile[_MAX_PATH];
string strTmp;

	GetModuleFileName (GetModuleHandle (TRIAS_MODULENAME), cbFile, _MAX_PATH);
	strTmp = cbFile;
	
int iBackslash = strTmp.rfind(TEXT('\\'));	// abschließendes BackSlash wegnehmen

	if (iBackslash != NPOS)
		strTmp = strTmp.remove (iBackslash);

	OpenDlg.SetInitialDir (strTmp.c_str());		// auf EXE setzen
	OpenDlg.Show();
	if (!OpenDlg.Result()) return LB_ERR;

	OpenDlg.GetFileName (m_pBuffer, _MAX_PATH);

string strDLLName = _strupr(m_pBuffer);
char cbExt[_MAX_EXT];

	_splitpath (m_pBuffer, NULL, NULL, cbFile, cbExt);
	_makepath (m_pBuffer, TEXT(TEXT("")), TEXT(""), cbFile, cbExt);

char *pExtName = m_rEL.RetrieveExtName (m_pBuffer);

	if (pExtName != NULL) {
	int iIndex = m_pExtList -> FindString (pExtName);

		delete pExtName;	// bereits geladen
		return iIndex;
	}

	CExtReg (strDLLName).Register();	// in RegDB registrieren

	if (FindExtNameFromDLLName (this, strDLLName, strTmp, m_pBuffer)) {
	int iIndex = m_pExtList -> FindString (strTmp.c_str());

		if (iIndex >= 0) return iIndex;		// bereits installiert

	// Erweiterung installieren
	LOADEXTENSIONEX LE;

		LE.m_pDesc = (char *)strTmp.c_str();
		LE.m_pName = (char *)strDLLName.c_str();
		LE.m_iMode = LENoLoad;		// nur registrieren
		LE.m_fGlobal = true;
		DEX_ExternalLoadExtensionEx (LE);

		InitExtList (true);
		return m_pExtList -> FindString (strTmp.c_str());
	}

return LB_ERR;
}

// Finden des Kurzbezeichners einer Erweiterung über den gegebene Dateinamen
bool FindExtNameFromDLLName (pWindow pW, string &strDLLName, string &strExtName,
			     const char *pShortName)
{
	strExtName = TEXT("");

	if (IsWin32s()) return false;

HKEY hKey = NULL;
DWORD i = 0;
bool fFound = false;
char cbTriasKey[_MAX_PATH];
DWORD retCode = RegOpenKey (HKEY_CURRENT_USER, TEXT("Software\\uve\\TRiAS") TEXT("\\Extensions"), &hKey);

	if (retCode != ERROR_SUCCESS) return false;
	while (RegEnumKey (hKey, i++, cbTriasKey, _MAX_PATH) == ERROR_SUCCESS) {
	string strTriasKey = cbTriasKey;

		if (CompareDLLName (strTriasKey, strDLLName)) {
			strExtName = strTriasKey;
			fFound = true;
			break;
		}
	}

	RegCloseKey (hKey);   // Close the key handle.

	if (!fFound) {	
	// Bezeichner der Erweiterung abfragen
	CQueryExtensionNameDlg QueryDlg (pW, string(pShortName));

		QueryDlg.Show();
		if (QueryDlg.Result() == 0)
			return false;
		return QueryDlg.GetExtName (strExtName);
	}

return true;
}

bool CompareDLLName (string &strKey, string &strDLL)
{
char cbBuffer[_MAX_PATH];
LONG dwLen = _MAX_PATH;
string strExtKey = TEXT("Software\\uve\\TRiAS") TEXT("\\Extensions") TEXT("\\");

	strExtKey += strKey;		// vollständiger ErweiterungsSchlüssel

// Langen Bezeichner besorgen (für alle Fälle)
	if (RegQueryValue (HKEY_CURRENT_USER, strExtKey.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

string strLongName = cbBuffer;

// ClassID besorgen
	dwLen = _MAX_PATH;
	strExtKey += TEXT("\\") TEXT("CLSID");
	if (RegQueryValue (HKEY_CURRENT_USER, strExtKey.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

string strCLSID = TEXT("CLSID") TEXT("\\");

	dwLen = _MAX_PATH;
	strCLSID += cbBuffer;
	strCLSID += TEXT("\\InprocServer32");

	if (RegQueryValue (HKEY_CLASSES_ROOT, strCLSID.c_str(), cbBuffer, &dwLen) != ERROR_SUCCESS)
		return false;

	if (strDLL == cbBuffer) {	// wenn Pfad stimmt, haben wir's
		strKey = strLongName;
		return true;
	}

return false;
}


// Fenster, in dem Bezeichner einer zu installierenden Erweiterung abgefragt wird
#pragma warning (disable: 4355)

CQueryExtensionNameDlg :: CQueryExtensionNameDlg (pWindow pW, const string &strExtFile)
			: DialogWindow (pW, QUERYEXTENSIONNAME),
			  m_pbOK (this, IDOK),
			  m_sleExtName (this, IDE_EXTNAME),
			  m_ftQueryText (this, IDT_QUERYTEXT)
{
	m_pbOK.Disable();

char cbBuffer[_MAX_PATH];

	m_ftQueryText.GetText (cbBuffer, sizeof(cbBuffer));

string strTmp = cbBuffer;

	wsprintf (cbBuffer, strTmp.c_str(), strExtFile.c_str());
	m_ftQueryText.SetText (cbBuffer);
}

#pragma warning (default: 4355)

void CQueryExtensionNameDlg :: ButtonClick (ControlEvt e)
{
	switch (e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg (0);
		break;
	}
}

void CQueryExtensionNameDlg :: EditChange (ControlEvt)
{
	if (m_sleExtName.GetTextLen() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
}

bool CQueryExtensionNameDlg :: GetExtName (string &strExtName)
{
int iLen = m_sleExtName.GetTextLen();

	if (iLen <= 0) return false;

char cbBuffer[_MAX_PATH];

	m_sleExtName.GetText (cbBuffer, sizeof(cbBuffer));
	strExtName = cbBuffer;

return true;
}

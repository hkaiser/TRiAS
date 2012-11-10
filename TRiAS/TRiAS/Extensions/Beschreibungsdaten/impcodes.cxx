// Import von Beschreibungsinformationen --------------------------------------
// File: IMPCODES.CXX

#include "idntsdbp.hxx"

#include <windowsx.h>
#include <eieruhr.hxx>
#include <statguid.h>
#include <TRiASDB.h>

#include <ospace/file/path.h>

#include "identsdb.h"
#include "identsdb.hxx"
#include "identres.h"		// Resourcen
#include "strings.h"

#pragma warning (disable: 4251)		// string needs dll-interface

#include "yy_ansi.h"
#include "yy_stdio.h"
#include "yy_bool.h"
#include "yy_errgn.h"
#include "yy_inpfi.h"

#include "idntsdba.hxx"

#include "idntsdbl.hxx"		// lexer et al
#include "idntsdby.hxx"		// parser et al
#include "idntsdbm.hxx"		// Wrapper für alles zusammen

#include "impdialg.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(Dispatch);
DefineSmartInterface(TRiASObjects);

// HookFunktion, die AutoSubclassing ermöglicht -------------------------------
extern "C" 
UINT _XTENSN_EXPORT CALLBACK ImportPBDHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM lParam);

// Diese Funktion wird nur unter 40 installiert und gerufen -------------------
extern "C" 
UINT _XTENSN_EXPORT APIENTRY ImportPBD40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam);

bool DirectoryExists (string strDir)
{
HANDLE hFile = CreateFile (strDir.c_str(), GENERIC_READ,
	FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
	FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return false;
	CloseHandle (hFile);
	return true;
}

// Importieren einer der Listen -----------------------------------------------
bool CIdentsDBExtension::ImportCodes (void) 
{
char *pLocDir = new char [_MAX_PATH];
char *pPath = new char [_MAX_PATH];
char cDrive[_MAX_DRIVE];

#if _MSC_VER < 1100
	if (DEX_GetActiveProject (pLocDir) == NULL) {
#else
		HPROJECT hPr = DEX_GetDataSourceHandle();
	if (DEX_GetDataSourceName (hPr, pLocDir) == NULL) {
#endif
//	if (DEX_GetActiveProject (pLocDir) == NULL) {
		DELETE_OBJ(pLocDir);
		DELETE_OBJ(pPath);
		return false;
	}
	_splitpath (pLocDir, cDrive, pPath, NULL, NULL);

ResString subDir (ResID (IDS_IDENTSDBSUBDIR, &RF()), 20);
string strDir (pPath);

	strDir += subDir;
	_makepath (pLocDir, cDrive, strDir.c_str(), g_cbNil, g_cbNil);
	if (!DirectoryExists (pLocDir))
		_makepath (pLocDir, cDrive, pPath, g_cbNil, g_cbNil);

// abschließendes '\\' entfernen
char *cptr;

	if (*(cptr = &pLocDir[strlen(pLocDir)-1]) == '\\')
		*cptr = '\0';

// FileNamen abfragen
ResString resCaption (ResID (IDS_IMPORTDATA, &RF()), 64);
CImportPBDDlg SDlg (MWind(), ResString (ResID (IDS_OPENTEMPLATE, &RF()), 200));

	SDlg.SetInitialDir (pLocDir);
	SDlg.AddFlags (OFN_HIDEREADONLY);
	SDlg.SetCaption (resCaption);
	SDlg.SetCustomData ((DWORD)(void *)&SDlg);

	if (IsWin40()) {
		SDlg.AddFlags (OFN_LONGNAMES|OFN_EXPLORER|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_ALLOWMULTISELECT);
#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50()))
			SDlg.AddFlags (OFN_ENABLESIZING);
#endif // OFN_ENABLESIZING

		SDlg.SetHookFcn ((HOOKFCN)ImportPBD40HookFcn);
		SDlg.SetTemplate (g_hInstance, MAKEINTRESOURCE(IDD_IMPORTOPTIONS));
	} else
		SDlg.SetHookFcn ((HOOKFCN)ImportPBDHookFcn);

int fResult = SDlg.Show();

// Speicher freigeben
	DELETE_OBJ(pLocDir);
	DELETE_OBJ(pPath);
	if (!fResult) return false;

	MVWind() -> Update();		// erst neu zeichnen

bool fRet = false;

	{
	CEierUhr Wait (MVWind());

	// Statusfenster erzeugen
	LPPROGRESSINDICATOR pIStatus = NULL;
	HRESULT hr = m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator,
					IID_IProgressIndicator, (LPVOID *)&pIStatus);

		if (FAILED(hr)) 
			return false;	// ohne Statusfenster importieren ?
	
	int iLen = SDlg.GetFileNameLen();
	char *cbFName = new char[iLen+1];

		SDlg.GetFileName (cbFName, iLen);	// DBName

		DEX_BeginPBDTransaction();

	int iFilterIndex = SDlg.GetFilterIndex();

		if (1 != iFilterIndex) {
		os_path path(cbFName);

			if (!stricmp(path.extension().c_str(), g_cbTxi))
				iFilterIndex = 2;	// TXI importieren
			else if (!stricmp(path.extension().c_str(), g_cbTxm))
				iFilterIndex = 3;	// TXM importieren
			else
				iFilterIndex = 1;	// TXC annehmen
		}

		switch (iFilterIndex) {
		default:
		case 1:		// *.txc
			{
			// alle selektierten Daten importieren
			list<os_string> Names;
			bool fFirst = true;

				SDlg.GetFileNames (Names, cbFName, iLen);
				if (SDlg.ImportToAllDataSources()) {
					for (list<HPROJECT>::iterator itprj = SDlg.GetHandles().begin(); itprj != SDlg.GetHandles().end(); ++itprj) {
					// sämtliche Beschreibungen löschen, wenn verlangt
						if (SDlg.DeleteExisting())
							DeleteAllIdents(*itprj);

					// aus sämtlichen Datein importieren
						for (list<os_string>::iterator it = Names.begin(); it != Names.end(); ++it) {
							fRet = ImportFromXml ((*it).c_str(), pIStatus, *itprj, SDlg.KeepExisting(), SDlg.RejectUnused(), fFirst);
							if (!fRet) break;
						}

						if (!fRet) break;
						fFirst = false;
					}
				} else {
				// sämtliche Beschreibungen löschen, wenn verlangt
					if (SDlg.DeleteExisting())
						DeleteAllIdents(SDlg.GetHandle());

				// aus sämtlichen Datein importieren
					for (list<os_string>::iterator it = Names.begin(); it != Names.end(); ++it) {
						fRet = ImportFromXml ((*it).c_str(), pIStatus, SDlg.GetHandle(), SDlg.KeepExisting(), SDlg.RejectUnused(), fFirst);
						if (!fRet) break;
					}
				}					

				if (fRet) {
					DEX_EndPBDTransaction();
					DEXN_PBDIdentsChanged();
				} else
					DEX_BreakPBDTransaction();
			}
			break;

		case 2:		// *.txi
			{
				hr = InitializeImportStatus (pIStatus, cbFName);
				if (FAILED(hr)) {
					DELETE_OBJ(cbFName);
					pIStatus -> Release();
					return false;
				}

			CIdentsDBImportParser *pParser = CIdentsDBImportParser::CreateInstance (
								SDlg.KeepExisting(), SDlg.RejectUnused());

				if (NULL != pParser) {
					if (SDlg.DeleteExisting())
						DeleteAllIdents(SDlg.GetHandle());

					fRet = pParser -> ParseFile (cbFName, pIStatus, SDlg.GetHandle(),
						yy_psr_identsdb_obj::yy_psr_class_icodedesc_,
						yy_lex_identsdb_obj::yy_lex_class_icodedesc_);

					if (!fRet) {
						DEX_EndPBDTransaction();
						DEXN_PBDIdentsChanged();
					} else
						DEX_BreakPBDTransaction();
				}
				DELETE_OBJ(pParser);
			}
			break;

		case 3:		// *.txm
			{
				hr = InitializeImportStatus (pIStatus, cbFName);
				if (FAILED(hr)) {
					DELETE_OBJ(cbFName);
					pIStatus -> Release();
					return false;
				}

			CIdentsDBImportParser *pParser = CIdentsDBImportParser::CreateInstance (
								SDlg.KeepExisting(), SDlg.RejectUnused());

				if (NULL != pParser) {
					if (SDlg.DeleteExisting())
						DeleteAllMCodes(SDlg.GetHandle());

					fRet = pParser -> ParseFile (cbFName, pIStatus, SDlg.GetHandle(),
						yy_psr_identsdb_obj::yy_psr_class_mcodedesc_,
						yy_lex_identsdb_obj::yy_lex_class_mcodedesc_);

					if (!fRet) {
						DEX_EndPBDTransaction();
						DEXN_PBDMCodesChanged();
					} else
						DEX_BreakPBDTransaction();
				}
				DELETE_OBJ(pParser);
			}
			break;
		}
		DELETE_OBJ(cbFName);
		pIStatus -> Release();		// Fenster ausblenden
	} 
	return fRet;
}

static 
DWORD GetFileSize (LPCSTR pcFName)
{
HANDLE hFile = CreateFile (pcFName, GENERIC_READ, FILE_SHARE_READ, 0L, 
			   OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile) return 0L;

DWORD dwSize = GetFileSize (hFile, NULL);

	CloseHandle (hFile);
	return dwSize;
}


HRESULT CIdentsDBExtension::InitializeImportStatus (LPPROGRESSINDICATOR pIStatus, LPCSTR pcFName)
{
	return InitializeImportStatus (pIStatus, pcFName, GetFileSize(pcFName));
}

HRESULT CIdentsDBExtension::InitializeImportStatus (
	LPPROGRESSINDICATOR pIStatus, LPCSTR pcFName, ULONG ulCnt, bool fFirst)
{
	if (fFirst) {
	HWND hNewWnd = pIStatus -> InitNew (hWnd(), 0L);

		if (NULL == hNewWnd) 
			return E_FAIL;
	}

	RETURN_FAILED_HRESULT(pIStatus -> Restart (0L, ulCnt, PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW));

// diverse Text initialisieren
ResString resCaption (ResID (IDS_IMPORTDATA, &RF()), 64);
ResString resFile (ResID (IDS_IMPORTFILE, &RF()), 32);
ResString resStatus (ResID (IDS_IMPORTSTATUS, &RF()), 64);

	pIStatus -> ChangeText (PIFLAG_CAPTION, resCaption);
	pIStatus -> ChangeText (PIFLAG_FILE, resFile);
	pIStatus -> ChangeText (PIFLAG_FILENAME, pcFName);
	pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);
	return S_OK;
}

// ImportFenster --------------------------------------------------------------
static CImportPBDDlg *s_pDlg = NULL;

CImportPBDDlg::CImportPBDDlg (pWindow pW, LPCSTR pcTempl)
	: COpenDialog (pW, (char *)pcTempl)
{
	m_fDelete = true;
	m_hPr = NULL;
	m_iAllDS = CB_ERR;
	m_iOldDS = CB_ERR;
}

LRESULT CImportPBDDlg::OnWmInitDialog (HWND hDlg, HWND hDlgP)
{
	CentreWindow (::GetParent (hDlgP), hDlgP);

	m_fDelete = true;
	m_fKeep = false;
	m_fReject = false;
	m_fAllDataSources = true;

	if (IsWin40()) {
		SendDlgItemMessage (hDlg, IDC_DELETEEXISTING, BM_SETCHECK, true, 0);
		SendDlgItemMessage (hDlg, IDC_KEEPEXISTING, BM_SETCHECK, true, 0);
		EnableWindow (GetDlgItem (hDlg, IDC_KEEPEXISTING), false);
		SendDlgItemMessage (hDlg, IDC_REJECTUNUSED, BM_SETCHECK, false, 0);

		SendDlgItemMessage (hDlg, IDC_SELECTDATASOURCE, BM_SETCHECK, false, 0);
		EnableWindow (GetDlgItem (hDlg, IDC_DATASOURCES), false);

	// ComboBox mit Datenquellen füllen
		return FillDataSources (hDlg);
	}
	return TRUE;
}

LRESULT CImportPBDDlg::FillDataSources (HWND hDlg)
{
	USES_CONVERSION;
	COM_TRY {
		TX_ASSERT(NULL == m_hPr);
	
	HPROJECT hPr = DEX_GetDataSourceHandle();

	// alle Connections durchgehen und feststellen:
	// aktuelle Connection, ob beschreibbare Connection existiert
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

	WTRiASConnections Conns;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

	long m_lConnCnt = 0;

		m_listPrj.clear();
		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			VARIANT_BOOL fUpdatable = VARIANT_FALSE;

				THROW_FAILED_HRESULT(Conn -> get_Updatable (&fUpdatable));
				if (fUpdatable) {
				// geöffnet und beschreibbar
				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Conn -> get_Name (&bstrName));

				int iNew = SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_ADDSTRING, 0, (LPARAM)OLE2A(bstrName));

				// wenns die aktuelle ist, dann den Index speichern
				WTRiASDatabase DBase;
				INT_PTR lHandle = 0; 

					THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
					THROW_FAILED_HRESULT(DBase -> get_Handle (&lHandle));
					if (-1 != iNew)
						SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_SETITEMDATA, iNew, lHandle);		// ProjectHandle zuordnen
					if (hPr == reinterpret_cast<HPROJECT>(lHandle) || NULL == m_hPr) {
						SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_SETCURSEL, iNew, 0);
						m_hPr = hPr;
					}

					m_listPrj.push_back ((HPROJECT)lHandle);
					m_lConnCnt++;		// Zähler der beschreibbaren Connections
				}
			}
		}

	ResourceFile RF (g_pDLLName);
	ResString resAll(ResID(IDS_ALLDATASOURCES, &RF), 64);
	
		m_iAllDS = SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_ADDSTRING, 0, (LPARAM)resAll.Addr());
		if (CB_ERR != m_iAllDS) {
			m_iOldDS = SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_SETCURSEL, m_iAllDS, 0);
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

// WM_COMMAND geschickt, drückt Nutzer Knöpfchen? -----------------------------
LRESULT CImportPBDDlg::OnWmCommand (HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	if (!IsWin40()) return false;		// nur für neues Fenster

UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
HWND hCntrl = GET_WM_COMMAND_HWND (wParam, lParam);
UINT uiCmd = GET_WM_COMMAND_CMD (wParam, lParam);

	if (uiCmd == BN_CLICKED) {
	// Buttons
		switch (uiID) {
		case IDC_DELETEEXISTING:
			m_fDelete = SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false;
			EnableWindow (GetDlgItem (hDlg, IDC_KEEPEXISTING), !m_fDelete);
			return true;

		case IDC_KEEPEXISTING:
			m_fKeep = SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? false : true;
			return true;

		case IDC_REJECTUNUSED:
			m_fReject = SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? true : false;
			return true;

		case IDC_SELECTDATASOURCE:
			{
				m_fAllDataSources = SendDlgItemMessage (hDlg, uiID, BM_GETCHECK, 0, 0) ? false : true;
				if (m_fAllDataSources) {
				ResourceFile RF (g_pDLLName);
				ResString resAll(ResID(IDS_ALLDATASOURCES, &RF), 64);
				
					m_iAllDS = SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_ADDSTRING, 0, (LPARAM)resAll.Addr());
					if (CB_ERR != m_iAllDS) {
						m_iOldDS = SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_GETCURSEL, 0, 0);
						SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_SETCURSEL, m_iAllDS, 0);
					}
				} else {
					if (CB_ERR != m_iAllDS) {
						SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_DELETESTRING, m_iAllDS, 0);
						if (CB_ERR != m_iOldDS)
							SendDlgItemMessage (hDlg, IDC_DATASOURCES, CB_SETCURSEL, m_iOldDS, 0);
						m_iAllDS = CB_ERR;
						m_iOldDS = CB_ERR;
					}
				}
				EnableWindow (GetDlgItem (hDlg, IDC_DATASOURCES), !m_fAllDataSources);
			}
			return true;

		default:
			break;
		}
	} 
	else if (uiCmd == CBN_SELENDOK) {
	// ComboBox
		switch (uiID) {
		case IDC_DATASOURCES:
			{
			int iIndex = SendDlgItemMessage (hDlg, uiID, CB_GETCURSEL, 0, 0);

				if (-1 != iIndex)
					m_hPr = reinterpret_cast<HPROJECT>(SendDlgItemMessage (hDlg, uiID, CB_GETITEMDATA, iIndex, 0));
			}
			return true;

		default:
			break;
		}
	}
	return false;
}

LRESULT CImportPBDDlg::OnCdnTypeChange (HWND hDlg)
{
	if (!IsWin40()) return false;		// nur für neues Fenster

int iIndex = SendDlgItemMessage (GetParent(hDlg), cmb1, CB_GETCURSEL, 0, 0);

	EnableWindow (GetDlgItem (hDlg, IDC_REJECTUNUSED), iIndex != 2);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// DateiNamen einlesen
bool CImportPBDDlg::GetFileNames (list<os_string> &rNames, LPCSTR pcBuffer, int iCurrLen)
{
// einlesen der Dateinamen
LPSTR pTemp = NULL;

	ATLTRY(pTemp = new char [iCurrLen+2]);
	if (NULL == pTemp) return false;

	ZeroMemory (pTemp, iCurrLen+2);
	memcpy (pTemp, pcBuffer, iCurrLen+1);

// Analyse des Strings, evtl. zerlegen und generieren des ersten Namens
int i = 0;
LPSTR pT = pTemp;
int iCnt = 0;

	do {
	int iLen = strlen (pT) +1;

		pT += iLen;
		i += iLen;
		++iCnt;
	} while (i <= iCurrLen && '\0' != *pT);

	rNames.clear();		// alles bisherige vergessen
	if (iCnt > 1) {
	// Parsen der Eingabe und zerlegen in eine list<os_string>
	os_string strPath (pTemp);

		pT = pTemp;
	
		for (int i = 0; i < iCnt; i++) {
		int iLen = strlen (pT) +1;

			if (i > 0) {
			// vollständigen Dateinamen zusammenbauen
			os_string str (strPath);

				str += '\\';
				str += pT;
				ATLTRY(rNames.push_back (str.c_str()));
			}
			pT += iLen;
		} 

	} else {
		ATLTRY(rNames.push_back (pTemp));
	}
	
	DELETE_OBJ(pTemp);
	return true;
}

extern "C" 
UINT _XTENSN_EXPORT CALLBACK ImportPBDHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		s_pDlg = (CImportPBDDlg *) (((OPENFILENAME *)lParam) -> lCustData);
		return (UINT)s_pDlg -> OnWmInitDialog (hDlg, hDlg);


	case WM_COMMAND:
		return s_pDlg ? s_pDlg -> OnWmCommand (hDlg, wParam, lParam) : false;

	case WM_DESTROY:
		s_pDlg = NULL;
		break;

	default:		// no actions
		break;
	}
	return false;
}

#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDC_DELETEEXISTING,	IDH_IMPORTPBDDLG_DELETEXISTING,
	IDC_KEEPEXISTING,	IDH_IMPORTPBDDLG_KEEPEXISTING,
	IDC_REJECTUNUSED,	IDH_IMPORTPBDDLG_REJECTUNUSED,
	IDG_IMPORTOPTIONS,	IDH_IMPORTPBDDLG_IMPORTOPTIONS,
	0,			0,		// EndeKennung
};

extern "C" 
UINT _XTENSN_EXPORT APIENTRY ImportPBD40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wMsg) {
	case WM_NOTIFY:
		{
		LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

			switch (pofn->hdr.code) {
			case CDN_INITDONE:
				s_pDlg = (CImportPBDDlg *)(pofn -> lpOFN -> lCustData);
				return s_pDlg -> OnWmInitDialog (hDlg, ::GetParent(hDlg));

			case CDN_TYPECHANGE:
				return s_pDlg -> OnCdnTypeChange (hDlg);
			}
		} 
		break;

	case WM_COMMAND:
		return s_pDlg ? s_pDlg -> OnWmCommand (hDlg, wParam, lParam) : false;

	case WM_DESTROY:
		s_pDlg = NULL;
		break;

	case WM_HELP:
		{
		const HELPINFO *pHI = (const HELPINFO *)lParam;
		char cbHelpFile[_MAX_PATH];

			strcpy (cbHelpFile, g_cbHelpPath);
			strcat (cbHelpFile, DIALOG_HELP_FILE);

			WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
				 HELP_WM_HELP, (DWORD)s_dwHelp);
		}
		break;

	default:		// no actions
		break;
	}
	return false;	// erstmal alles weiterleiten
}


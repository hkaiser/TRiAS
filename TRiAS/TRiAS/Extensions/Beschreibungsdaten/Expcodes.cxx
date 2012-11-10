// Exportieren der Eintraege einer PBD ----------------------------------------
// File: EXPCODES.CXX

#include "idntsdbp.hxx"

#include <eieruhr.hxx>
#include <statguid.h>
#include <registrx.hxx>

#include "identres.h"		// Resourcen
#include "Strings.h"

#include "identsdb.h"
#include "defiderr.hxx"
#include "defabout.hxx"
#include "identsdb.hxx"

EXPORTMODE s_rgExportMode = EXPORTMODE_Normal;

// HookFunktion, die AutoSubclassing ermöglicht -------------------------------
extern "C" 
UINT _XTENSN_EXPORT CALLBACK ExportPBDHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM lParam);

#if !defined(WIN16)

// Diese Funktion wird nur unter 40 installiert und gerufen -------------------
extern "C" 
UINT _XTENSN_EXPORT APIENTRY ExportPBD40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam);

#endif

// entferenen aller evtl. Zeilenwechsel etc. ----------------------------------
char *RemoveNewLines (char *pText)
{
	if (NULL == pText) return (char *)g_cbNil;

char *pT = pText;

	while (*pT) {
		switch (*pT) {
		case '\r':
		case '\n':
			*pT = ' ';
			break;

		default:
			break;
		}
		++pT;
	}
	return pText;
}


// Export eines Identifikatoreintrages ----------------------------------------
typedef struct tagEXPORTDATA {
	int fh;
	LPUNKNOWN pIUnk;
	ULONG ulCnt;
} EXPORTDATA;

extern "C" 
BOOL _XTENSN_EXPORT PASCAL ExportIdentEntry (long Ident, BOOL, void *pData)
{
PBDDATA pbdData;
char KText[34];
char *pLText = new char [1025];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 1024;
	DEX_GetPBDData (pbdData);
	KText[32] = '\0';

char *pOutBuff = new char [1100];
EXPORTDATA *pED = (EXPORTDATA *)pData;

	RemoveNewLines (pbdData.pbdLText);

	if (pOutBuff) {
	char cbBuffer[MAX_OKS_LENX];
	HRESULT hr = ClassFromIdentX (Ident, cbBuffer);

		pOutBuff[0] = '\0';
		if (EXPORTMODE_Normal == (s_rgExportMode & EXPORTMODE_TXI)) {
			if (S_OK == hr) {
				if (pbdData.pbdLText) 
					wsprintf (EOS(pOutBuff), "\"%s\" /*%s*/%s\r\n", cbBuffer, pbdData.pbdKText, pbdData.pbdLText);
				else 
					wsprintf (EOS(pOutBuff), "\"%s\" /*%s*/\r\n", cbBuffer, pbdData.pbdKText);
			} else if (S_FALSE == hr) {
			const char *pT = (10 == DEX_GetIdBase()) ? g_cbNil : "0x";

				if (pbdData.pbdLText) 
					wsprintf (EOS(pOutBuff), "%s%s /*%s*/%s\r\n", pT, cbBuffer, pbdData.pbdKText, pbdData.pbdLText);
				else 
					wsprintf (EOS(pOutBuff), "%s%s /*%s*/\r\n", pT, cbBuffer, pbdData.pbdKText);
			}
		} else {
			if (s_rgExportMode & EXPORTMODE_IdentOnly)
				wsprintf (EOS(pOutBuff), "%08lx ", Ident);

			if (SUCCEEDED(hr) && s_rgExportMode & EXPORTMODE_OKSOnly)	// S_OK oder S_FALSE
				wsprintf (EOS(pOutBuff), "\"%s\" ", cbBuffer);
			else
				wsprintf (EOS(pOutBuff), "%08lx ", Ident);		// damit wenigstens was ausgegeben wird

			wsprintf (EOS(pOutBuff), "/*%s*/", pbdData.pbdKText);
			if (pbdData.pbdLText) 
				strcat (pOutBuff, pbdData.pbdLText);
			strcat (pOutBuff, "\r\n");
		}

		AnsiToOem (pOutBuff, pOutBuff);
		_lwrite (pED -> fh, pOutBuff, strlen(pOutBuff));
	}
	DELETE_OBJ(pLText);
	DELETE_OBJ(pOutBuff);

#if !defined(WIN16)
	if (pED -> pIUnk) {
		LPPROGRESSINDICATOR(pED -> pIUnk) -> SetPosition (++(pED -> ulCnt));
		if (LPPROGRESSINDICATOR(pED -> pIUnk) -> WasCanceled()) 
			return false;		// abbrechen
	}
#endif
		
	return true;	// weitermachen
}

// Export eines Merkmalseintrages ---------------------------------------------
//extern "C" 
//BOOL _XTENSN_EXPORT PASCAL ExportMCodeEntry (long MCode, BOOL, void *pData)
//{
//PBDMERKMAL pbdData;
//char KText[34];
//char *pLText = new char [1025];
//                                          
//	memset (&pbdData, '\0', sizeof(PBDMERKMAL));                                          
//
//	pbdData.dwSize = sizeof(PBDMERKMAL);
//	pbdData.pbdTyp = 'm';
//	pbdData.pbdCode = MCode;
//	pbdData.pbdKText = KText;
//	pbdData.pbdLText = pLText;
//	pbdData.pbdKTextLen = sizeof(KText) -1;
//	pbdData.pbdLTextLen = 1024;
//	
//	DEX_GetPBDData (pbdData);
//	KText[32] = '\0';
//
//// Systemmerkmale nicht ausgeben
//	if (pbdData.ipbdMTyp & PBDMERKMAL_SYSTEMFLAG)
//		return true;
//
//char *pOutBuff = new char [1100];                  
//EXPORTDATA *pED = (EXPORTDATA *)pData;
//
//	RemoveNewLines (pbdData.pbdLText);
//
//	if (pOutBuff) {
//	string strType = char(toupper(pbdData.ipbdMTyp & 0xff));
//
//		if (pbdData.ipbdMTyp & PBDMERKMAL_READONLY)
//			strType += 'R';		// readonly
//
//		if (DEX_GetMkBase() == 10) {
//			if (pbdData.pbdLText) {
//				wsprintf (pOutBuff, "%08ld %s 1 %d 0 /*%s*/%s\r\n", MCode, 
//					  strType.c_str(), pbdData.ipbdMLen,
//					  pbdData.pbdKText, pbdData.pbdLText);
//			} else {
//				wsprintf (pOutBuff, "%08ld %s 1 %d 0 /*%s*/\r\n", MCode, 
//					  strType.c_str(), pbdData.ipbdMLen,
//					  pbdData.pbdKText);
//			}
//		} else {
//			if (pbdData.pbdLText) {
//				wsprintf (pOutBuff, "0x%08lx %s 1 %d 0 /*%s*/%s\r\n", MCode, 
//					  strType.c_str(), pbdData.ipbdMLen,
//					  pbdData.pbdKText, pbdData.pbdLText);
//			} else {
//				wsprintf (pOutBuff, "0x%08lx %s 1 %d 0 /*%s*/\r\n", MCode, 
//					  strType.c_str(), pbdData.ipbdMLen,
//					  pbdData.pbdKText);
//			}
//		}
//		AnsiToOem (pOutBuff, pOutBuff);
//		_lwrite (pED -> fh, pOutBuff, strlen(pOutBuff));
//	}
//	DELETE_OBJ(pLText);
//	DELETE_OBJ(pOutBuff);
//
//#if !defined(WIN16)
//	if (pED -> pIUnk) {
//		LPPROGRESSINDICATOR(pED -> pIUnk) -> SetPosition (++(pED -> ulCnt));
//		if (LPPROGRESSINDICATOR(pED -> pIUnk) -> WasCanceled()) 
//			return false;		// abbrechen
//	}
//#endif
//	return true;	// weitermachen
//}

// Export eines Relationseintrages --------------------------------------------
//extern "C" 
//BOOL _XTENSN_EXPORT PASCAL ExportRCodeEntry (long lRCode, BOOL, void *pData)
//{
//PBDRELATION pbdData;
//char KText[34];
//char *pLText = new char [1025];
//                                          
//	memset (&pbdData, '\0', sizeof(PBDRELATION));                                          
//
//	pbdData.dwSize = sizeof(PBDRELATION);
//	pbdData.pbdTyp = 'r';
//	pbdData.pbdCode = lRCode;
//	pbdData.pbdKText = KText;
//	pbdData.pbdLText = pLText;
//	pbdData.pbdKTextLen = sizeof(KText) -1;
//	pbdData.pbdLTextLen = 1024;
//	
//	DEX_GetPBDData (pbdData);
//	KText[32] = '\0';
//
//char *pOutBuff = new char [1100];                  
//EXPORTDATA *pED = (EXPORTDATA *)pData;
//
//	RemoveNewLines (pbdData.pbdLText);
//
//	if (pOutBuff) {
//	char iTyp = toupper (pbdData.ipbdRTyp);
//
//		if (pbdData.pbdLText) {
//			wsprintf (pOutBuff, "%08ld %c /*%s*/%s\r\n", lRCode, 
//				  iTyp, pbdData.pbdKText, pbdData.pbdLText);
//		} else {
//			wsprintf (pOutBuff, "%08ld %c /*%s*/\r\n", lRCode, 
//				  iTyp, pbdData.pbdKText);
//		}
//
//		AnsiToOem (pOutBuff, pOutBuff);
//		_lwrite (pED -> fh, pOutBuff, strlen(pOutBuff));
//	}
//	DELETE_OBJ(pLText);
//	DELETE_OBJ(pOutBuff);
//
//#if !defined(WIN16)
//	if (pED -> pIUnk) {
//		LPPROGRESSINDICATOR(pED -> pIUnk) -> SetPosition (++(pED -> ulCnt));
//		if (LPPROGRESSINDICATOR(pED -> pIUnk) -> WasCanceled()) 
//			return false;		// abbrechen
//	}
//#endif
//		
//return true;	// weitermachen
//}

extern "C" HINSTANCE hInstance;
extern bool DirectoryExists (string strDir);

// Exportieren einer der Listen -----------------------------------------------
bool CIdentsDBExtension::ExportCodes (void) 
{
// ExportMode einlesen
	{
	CCurrentUser reg (KEY_READ, g_cbMyConfig);
	DWORD dwData = EXPORTMODE_Normal;

		reg.GetDWORD (g_cbExportMode, dwData);
		s_rgExportMode = (EXPORTMODE)dwData;
	} // Close Key

//
char *pLocDir = new char [_MAX_PATH];
char *pPath = new char [_MAX_PATH];
char cDrive[_MAX_DRIVE];

	if (DEX_GetActiveProject (pLocDir) == NULL) {
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
bool fAdmin = DEX_QueryMode() & QMSysAdmin;
ResString resTmpl (ResID(fAdmin ? IDS_SAVETEMPLATE_ADMIN : IDS_SAVETEMPLATE, &RF()), 200);
CSaveAsDialog SDlg (MWind(), (char *)resTmpl.Addr());

	SDlg.SetInitialDir (pLocDir);

#if !defined(WIN16)
	if (IsWin40()) {
		SDlg.AddFlags (OFN_LONGNAMES|OFN_EXPLORER|OFN_NOREADONLYRETURN|OFN_OVERWRITEPROMPT);
#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50()))
			SDlg.AddFlags (OFN_ENABLESIZING);
#endif // OFN_ENABLESIZING

		SDlg.SetHookFcn ((HOOKFCN)ExportPBD40HookFcn);
	} else
#endif
		SDlg.SetHookFcn ((HOOKFCN)ExportPBDHookFcn);

bool fRet = true;
ResString resCaption (ResID (IDS_EXPORTDATA, &RF()), 64);

	SDlg.SetCaption (resCaption);
	if (SDlg.Show()) {
	int iLen = SDlg.GetFileNameLen ();
	char *pFName = new char [iLen+1];

		if (pFName == NULL) return false;
		SDlg.GetFileName (pFName, iLen);	// DBName

		MVWind() -> Update();			// fertig zeichnen

	CEierUhr Wait (MVWind());

#if !defined(WIN16)
	// Statusfenster erzeugen
	LPPROGRESSINDICATOR pIStatus = NULL;
	HRESULT hr = m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator,
					IID_IProgressIndicator, (LPVOID *)&pIStatus);

		if (FAILED(hr)) return false;	// ohne Statusfenster importieren ?
		hr = InitializeExportStatus (pIStatus, SDlg.GetFilterIndex());
		if (FAILED(hr)) {
			pIStatus -> Release();
			return false;
		}
#else
	LPUNKNOWN pIStatus = NULL;
#endif // WIN16

		switch (SDlg.GetFilterIndex()) {
		default:	// eigenes Format
		case 1:		// *.txc
			fRet = ExportAsXml (pIStatus, pFName);
			break;

		case 2:		// *.txi
			fRet = ExportIdents (pIStatus, pFName);
			break;

//		case 3:		// *.txm
//			fRet = ExportMCodes (pIStatus, pFName); 
//			break;
//
//		case 3:		// *.txr
//			fRet = ExportRCodes (pIStatus, pFName); 
//			break;
//
			break;
		}
		DELETE_OBJ(pFName);

#if !defined(WIN16)
		pIStatus -> Release();		// Fenster freigeben
#endif // WIN16
	} else
		fRet = false;

// Speicher freigeben
	DELETE_OBJ(pLocDir);
	DELETE_OBJ(pPath);
	return fRet;
}


// Exportieren aller PBD-IdentifikatorEinträge -------------------------------
bool CIdentsDBExtension::ExportIdents (LPUNKNOWN pIUnk, char *pFName, const char *pExt) 
{
	return ExportCodeTemplate (pIUnk, pFName, pExt, 'i', (ENUMLONGKEYPROC)ExportIdentEntry);
}

//// Exportieren aller PBD-MerkmalsEinträge ------------------------------------
//bool CIdentsDBExtension::ExportMCodes (LPUNKNOWN pIUnk, char *pFName, const char *pExt) 
//{
//	return ExportCodeTemplate (pIUnk, pFName, pExt, 'm', (ENUMLONGKEYPROC)ExportMCodeEntry);
//}
//
// Exportieren aller PBD-RelationsEinträge ------------------------------------
//bool CIdentsDBExtension::ExportRCodes (LPUNKNOWN pIUnk, char *pFName, const char *pExt) 
//{
//	return ExportCodeTemplate (pIUnk, pFName, pExt, 'r', (ENUMLONGKEYPROC)ExportRCodeEntry);
//}

// exportieren einer Liste ----------------------------------------------------
bool CIdentsDBExtension::ExportCodeTemplate (LPUNKNOWN pIUnk, 
				char *pFName, const char *pExt, 
				short iTyp, ENUMLONGKEYPROC pFcn
			  )
{
// wenn Extension generiert werden soll, dann selbiges tun
	if (pExt != NULL) {
	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_PATH];
	char *pName = new char [_MAX_FNAME];
	
		_splitpath (pFName, pDrive, pPath, pName, NULL);
		_makepath (pFName, pDrive, pPath, pName, pExt);
		DELETE_OBJ(pDrive);	
		DELETE_OBJ(pPath);
		DELETE_OBJ(pName);
	}

// Datei bilden, wenn diese noch nicht existiert
int fh = _lcreat (pFName, 0);

	if (fh < 0) return false;

#if !defined(WIN16)
	if (pIUnk) LPPROGRESSINDICATOR(pIUnk) -> ChangeText (PIFLAG_FILENAME, pFName);
#endif

bool fRet;
ENUMLONGKEY ELK;
EXPORTDATA ED;

	ED.fh = fh;
	ED.pIUnk = pIUnk;
	ED.ulCnt = 0;

	ELK.eKey = iTyp;
	ELK.eFcn = (ENUMLONGKEYPROC)pFcn;
	ELK.ePtr = &ED;
	fRet = DEX_EnumPBDData (ELK);

// Datei wieder schließen
	_lclose (fh);		// Datei schließen

return fRet;
}

#if !defined(WIN16)

extern "C" 
BOOL _XTENSN_EXPORT PASCAL CountFcn (long Ident, BOOL, void *pData)
{
	(*(ULONG *)pData)++;	// nur zählen
	return true;
}

static bool CountPDBEntries (int iKey, ULONG *pulCnt)
{
ENUMLONGKEY ELK;

	ELK.eKey = iKey;
	ELK.eFcn = (ENUMLONGKEYPROC)CountFcn;
	ELK.ePtr = pulCnt;
	return DEX_EnumPBDData (ELK);
}

static ULONG CountEntries (int iType)
{
ULONG ulCnt = 0;

	switch (iType) {
	default:
	case 1:
		CountPDBEntries ('i', &ulCnt);
		break;

	case 2:
		CountPDBEntries ('i', &ulCnt);
		break;

//	case 3:
//		CountPDBEntries ('m', &ulCnt);
//		break;
	}
	return ulCnt;
}

HRESULT CIdentsDBExtension::InitializeExportStatus (LPPROGRESSINDICATOR pIStatus, int iType)
{
HWND hNewWnd = pIStatus -> InitNew (hWnd(), 0L);

	if (NULL == hNewWnd) return ResultFromScode (E_FAIL);

HRESULT hr = pIStatus -> Restart (0L, CountEntries (iType), PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
	if (FAILED(hr)) return hr;

// diverse Text initialisieren
ResString resCaption (ResID (IDS_EXPORTDATA, &RF()), 64);
ResString resFile (ResID (IDS_IMPORTFILE, &RF()), 32);
ResString resStatus (ResID (IDS_EXPORTSTATUS, &RF()), 64);

	pIStatus -> ChangeText (PIFLAG_CAPTION, resCaption);
	pIStatus -> ChangeText (PIFLAG_FILE, resFile);
	pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);
	return NOERROR;
}

#endif // WIN16

extern "C" 
UINT _XTENSN_EXPORT CALLBACK ExportPBDHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
#if !defined(WIN16)
	if (wMsg == WM_INITDIALOG) 
		CentreWindow (::GetParent(hDlg), hDlg);
#endif // WIN16
	
	return false;
}

#if !defined(WIN16)

extern "C" 
UINT _XTENSN_EXPORT APIENTRY ExportPBD40HookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NOTIFY == wMsg) {
	LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

		if (CDN_INITDONE == pofn->hdr.code) {
		HWND hDlgP = ::GetParent(hDlg);
					
			CentreWindow (::GetParent (hDlgP), hDlgP);
			return true;
		}
	}
	return false;	// erstmal alles weiterleiten
}

#endif // WIN16		

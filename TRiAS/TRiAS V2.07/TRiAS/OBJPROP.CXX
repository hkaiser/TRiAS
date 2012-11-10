// Auswahl von Objekteigenschaften (Dialogfenster) ----------------------------
// File: OBJPROP.CXX

#include "triaspre.hxx"

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>

#if defined(WIN32)
#include <registry.hxx>
#include <dirisole.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include "extmain3.hxx"
#endif // WIN32

#include <istatus.h>
#include <statguid.h>
#include <funcs03.h>

#include "strings.h"
#include "objprop.h"
#include "objprop.hxx"                                          

#include "triasres.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInstance;
#if !defined(WIN32)
extern bool IsWin40 (void);
#endif

#if !defined(HUGE)
#define HUGE __huge
#endif

//#define _DEBUG_HEAP
#if defined(_DEBUG_HEAP)
//debughilfe
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
		return false;

return true;
}
#else
#define HEAPCHECK()
#endif

// FunktionsPrototypen --------------------------------------------------------
char *TrimRightAndLeft (char *);
void ReplaceDel (char *pStr);
bool ReplaceDelimiter (char *pStr, char cDel, char cOldDel);
int RetrieveDelimiter (short iMode, char cDefault = '\t');

// spezielles strlen für HUGE-Strings -----------------------------------------
#if defined(WIN32)

inline size_t hstrlen (const char *pStr) { return strlen (pStr); }

#else

long hstrlen (const char *pStr)
{
char __huge *phStr = (char __huge *)pStr;
size_t iCnt = 0;

	while (*phStr++) 
		iCnt++;
	
return iCnt;
}

#endif // WIN32

extern "C" {

#if !defined(WIN32)
// HookFunktion für SaveAsDlg -------------------------------------------------
UINT EXPORTTRIAS CALLBACK ObjPropHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM);
#endif

// CallbackFunktion für Enumeration der ObjProps ------------------------------
typedef struct tagLOCENUMDATA {
	MultiSelListBox *pMSLB;
	ObjPropTree *pOPT;
	Extension *pExt;
} LOCENUMDATA;

_TRIAS_ENTRY bool EXPORTTRIAS WINAPI ObjPropFunc (const char *pFName, short iFuncID, bool, void *pData)
{
LOCENUMDATA *pLED = (LOCENUMDATA *)pData;
ObjectPropertyCreator OPCr (*pLED -> pOPT);
ObjectProperty *pOP = ContCreate (OPCr, ObjectPropertyExt)(pFName, iFuncID, pLED -> pExt);

	if (pOP) pLED -> pMSLB -> AddString (pFName);

HEAPCHECK(); return true;
}

// interne ObjPropFuncs (Prototypen) ------------------------------------------
char * WINAPI IntObjPropONr (long lONr, char *pBuffer, short iLen);
char * WINAPI IntObjPropIdent (long lONr, char *pBuffer, short iLen);
char * WINAPI IntObjPropObjTyp (long lONr, char *pBuffer, short iLen);
#if defined(WIN32)
char * WINAPI IntObjPropGUID (long lONr, char *pBuffer, short iLen);
char * WINAPI IntObjPropOKS (long lONr, char *pBuffer, short iLen);
#endif // WIN32

// Speicherverwaltung für Zwischenablage --------------------------------------
static char HUGE * WINAPI Alloc (long lCount);
static bool WINAPI Free (char HUGE *pB);
static char HUGE * WINAPI ReAlloc (char HUGE *pB, long lCount);


// Merkmale aus der PBD lesen -------------------------------------------------
bool EXPORTTRIAS WINAPI FillMCodesListBox (long lMCode, bool, void *pData)
{
PBDMERKMAL pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDMERKMAL));

	pbdData.dwSize = sizeof(PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText);
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'u';

	DEX_GetPBDData (pbdData);

char outBuff[80];

	if (10 == DEX_GetMkBase())
		wsprintf (outBuff, "%08ld:%s", lMCode, pbdData.pbdKText);
	else
		wsprintf (outBuff, "%08lx:%s", lMCode, pbdData.pbdKText);
		
	((ComboBox *)pData) -> AddString (outBuff);

HEAPCHECK(); return true;	// weitermachen
}

}	// extern "C"

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

#if defined(WIN32)
ObjectPropertyDlg :: ObjectPropertyDlg (pWindow pW, ExtensionList *pEL, 
					IEnum<LONG> *pEnumerator, LONG lRefONr)
		   : DialogWindow (pW, ResID (OBJPROPDLG)),
#else
ObjectPropertyDlg :: ObjectPropertyDlg (pWindow pW, ExtensionList *pEL, 
					LPENUMLONG pEnumerator, LONG lRefONr)
		   : DialogWindow (pW, ResID (OBJPROPDLG)),
		     m_HelpButton (this, IDB_OBJPROPHELP),
#endif // WIN32
		     m_OKButton (this, IDOK),
		     m_pbSortEntries (this, IDB_SORTENTRIES),
		     m_ClipButton (this, IDR_OBJPROPCLIPBOARD),
		     m_FileButton (this, IDR_OBJPROPFILE),
		     m_WindowButton (this, IDR_OBJPROPWINDOW),
		     m_MCodeButton (this, IDR_OBJPROPMCODE),
		     m_SelectFile (this, IDB_OBJPROPFILE),
		     m_FileName (this, IDE_OBJPROPFILE),
		     m_ObjProps (this, IDL_OBJPROP),
		     m_HeadLine (this, IDCB_OBJPROPHEADLINE),
		     m_Cumulation (this, IDCB_OBJPROPCUMULATE),
		     m_Count (this, IDCB_OBJPROPCOUNT),
		     m_MCodes (this, IDC_OBJPROPMCODES),
		     m_ObjPropData (this, IDCB_OBJPROPPROPS),
		     m_ftHelpText (this, IDT_HELPTEXT),
		     m_EL (*pEL),
		     m_pObjEnum (pEnumerator)
{
// Controls initialisieren
#if !defined(WIN32)
	m_HelpButton.Disable();
#endif // WIN32
	m_pbSortEntries.Disable();
	
	m_ClipButton.SetState (true);
	m_HeadLine.SetChecked (true);
	m_Cumulation.SetChecked (true);
	m_Count.SetChecked (true);
	m_ObjPropData.SetChecked (true);

	m_iFileType = 1;	// Default: *.OPR

	if (!IsWin40()) {
	ResString rsArial (IDS_ARIAL, 20);

		m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
		if (m_pFont) {
			m_pFont = m_ftHelpText.ChangeFont (m_pFont);
			m_fFontChanged = true;
		} else
			m_fFontChanged = false;
	} else
		m_fFontChanged = false;

// Daten initialisieren
	m_pObjPropTree = new ObjPropTreeStr();
	if (m_pObjPropTree == NULL) {
		db_error (EC_NOMEMORY, RC_ctObjPropDlg);
		HEAPCHECK(); return;
	}

// interne ObjPropFuncs initialisieren
	{
	ObjectPropertyCreator OPCr (*m_pObjPropTree);

		GenerateIntObjPropFunc (OPCr, ResString (IDS_OBJPROPONR, OBJPROPFUNCNAMELEN+1), 
					ResString (IDS_OBJPROPONRHELP, OBJPROPFUNCHELPLEN),
					(INTOBJPROPPROC)IntObjPropONr);
		GenerateIntObjPropFunc (OPCr, ResString (IDS_OBJPROPIDENT, OBJPROPFUNCNAMELEN+1), 
					ResString (IDS_OBJPROPIDENTHELP, OBJPROPFUNCHELPLEN),
					(INTOBJPROPPROC)IntObjPropIdent);
		GenerateIntObjPropFunc (OPCr, ResString (IDS_OBJPROPOBJTYP, OBJPROPFUNCNAMELEN+1), 
					ResString (IDS_OBJPROPTYPHELP, OBJPROPFUNCHELPLEN),
					(INTOBJPROPPROC)IntObjPropObjTyp);
#if defined(WIN32)
		GenerateIntObjPropFunc (OPCr, ResString (IDS_OBJPROPGUID, OBJPROPFUNCNAMELEN+1), 
					ResString (IDS_OBJPROPGUIDHELP, OBJPROPFUNCHELPLEN),
					(INTOBJPROPPROC)IntObjPropGUID);
		GenerateIntObjPropFunc (OPCr, ResString (IDS_OBJPROPOKS, OBJPROPFUNCNAMELEN+1), 
					ResString (IDS_OBJPROPOKSHELP, OBJPROPFUNCHELPLEN),
					(INTOBJPROPPROC)IntObjPropOKS);
#endif // WIN32

		GenerateIntObjPropFuncText (this, OPCr, 1);
		GenerateIntObjPropFuncText (this, OPCr, 2);
		GenerateIntObjPropFuncText (this, OPCr, 3);
		GenerateIntObjPropFuncText (this, OPCr, 4);
		GenerateMCodeIntObjPropFuncs (OPCr);
	}

// evtl. ReferenzObjekt besorgen, dazu einfach das erste zu bearbeitende Objekt
// verwenden
	if (0L == lRefONr && NULL != m_pObjEnum) {
		m_pObjEnum -> Reset(); 
		m_pObjEnum -> Next (1, &lRefONr, NULL);
	}

// ListBox füllen
ENUMOBJPROPDATA EOPD;
LOCENUMDATA LED;
CTable r (m_EL);

	LED.pMSLB = &m_ObjProps;
	LED.pOPT = m_pObjPropTree;
	EOPD.pFunc = (ENUMOBJPROPPROC)ObjPropFunc;
	EOPD.pPtr = &LED;

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l) {
			LED.pExt = l;
			l -> EnumObjPropFuncs (&EOPD, lRefONr);
		}
	}
	
// ComboBox füllen
	m_MCodes.Clear();	// erstmal alles löschen
	
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof(ENUMLONGKEY));
	ELK.eKey = 'm';
	ELK.eFcn = (ENUMLONGKEYPROC)FillMCodesListBox;
	ELK.ePtr = (void*)&m_MCodes;
	DEX_EnumPBDData (ELK);

	if (m_MCodes.GetCount() == 0 || DEX_GetROMode()) {
		m_MCodes.Disable();
		m_MCodeButton.Disable();
	}
	
// Zeichenkettenbuffer anlegen
	m_pBuff = new char [_MAX_PATH];
HEAPCHECK(); }

#pragma warning (default: 4355)

ObjectPropertyDlg :: ~ObjectPropertyDlg (void)
{
	DELETE (m_pObjPropTree);
	DELETE (m_pBuff);
	if (m_fFontChanged) {
		m_pFont = m_ftHelpText.ChangeFont (m_pFont);
		DELETE (m_pFont);
	}
HEAPCHECK(); }


bool ObjectPropertyDlg :: GenerateIntObjPropFunc (ObjectPropertyCreator &OPCr,
						  const char *pFName,
						  const char *pHText, 
						  INTOBJPROPPROC pFunc)
{
ObjectPropertyInt *pOPI = ContCreate (OPCr, ObjectPropertyInt)(pFName, pHText, pFunc);

	m_ObjProps.AddString (pFName);

HEAPCHECK(); return pOPI != NULL;
}


bool ObjectPropertyDlg :: GenerateIntObjPropFuncText (pWindow pW, ObjectPropertyCreator &OPCr, short iCnt)
{
ObjectProperty *pOPI = ContCreate (OPCr, CQueryFieldPropertyInt)(pW, iCnt);

	if (pOPI) m_ObjProps.AddString (pOPI -> pFName());

HEAPCHECK(); return pOPI != NULL;
}


void ObjectPropertyDlg :: ButtonClick (ControlEvt e)
{
unsigned int uiID = (uint)e.GetControlID();

	switch (uiID) {
	case IDB_OBJPROPHELP:
		break;

	case IDOK:
		{
		short iDest = OBJPROP_DESTCLIPBOARD;

			if (m_FileButton.GetState()) 
				iDest = OBJPROP_DESTFILE + m_iFileType -1;
			else if (m_MCodeButton.GetState()) {
			short iIndex = m_MCodes.GetCurrentIndex ();
			
				if (iIndex != -1) {
				char inBuff[65];
				long lMCode;
								
					m_MCodes.GetString (inBuff, iIndex, sizeof(inBuff)-1);
					lMCode = strtoul (inBuff, NULL, DEX_GetMkBase());
					if (lMCode != 0)
						EndDlg (GenerateObjProps (OBJPROP_DESTMCODE, lMCode));
				}
				break;
			}
				
			if (m_WindowButton.GetState()) 
				GenerateObjProps (OBJPROP_DESTWINDOW);
			else
				EndDlg (GenerateObjProps (iDest));
		}
		break;

	case IDCANCEL:
		EndDlg (0);
		break;

	case IDB_OBJPROPFILE:		// Dateiauswahl
		{
		CSaveAsDialog SFDlg (this, 
			(char *)ResString (IDS_OBJPROPFILETEMPLATE, 80).Addr());

#if !defined(WIN32)
			SFDlg.SetHookFcn ((HOOKFCN)ObjPropHookFcn);
#else
			if (IsWin40())
				SFDlg.AddFlags (OFN_EXPLORER);
			SFDlg.AddFlags (OFN_LONGNAMES);
#endif
			if (!SFDlg.Show()) break;

		int iLen = SFDlg.GetFileNameLen();
		char *pFileName = new char [iLen+1];

			if (pFileName) {
				SFDlg.GetFileName (pFileName, iLen);
				m_iFileType = SFDlg.GetFilterIndex();
				if (m_iFileType <= 0 || m_iFileType > 2)
					m_iFileType = 1;	// default: *.opr

				m_FileName.SetText (pFileName);
				m_FileButton.SetState (true);
				m_ClipButton.SetState (false);
				m_WindowButton.SetState (false);
				m_MCodeButton.SetState (false);
				m_OKButton.Enable();
				delete pFileName;
			}
		}
		break;

	case IDR_OBJPROPCLIPBOARD:
	case IDR_OBJPROPFILE:
	case IDR_OBJPROPWINDOW:
	case IDR_OBJPROPMCODE:
		{
			if (uiID == IDR_OBJPROPFILE)
				m_FileName.SetFocus();
			else if (uiID == IDR_OBJPROPMCODE)
				m_MCodes.SetFocus();
			AdjustControls ();
		}
		break;
		
	case IDB_SORTENTRIES:
		m_pObjPropTree = ResortObjProps (m_pObjPropTree);
		break;
	}
HEAPCHECK(); }

void ObjectPropertyDlg :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_OBJPROP:
		{
			if (m_pObjPropTree == NULL) return;

			m_pObjPropTree -> SetAll();

			for (short iIndex = 0; iIndex < (short)m_pObjPropTree -> Count(); iIndex++) {
			bool isSel = m_ObjProps.GetSelection (iIndex);
			char inBuff[OBJPROPFUNCNAMELEN+1];

				m_ObjProps.GetString (inBuff, iIndex, OBJPROPFUNCNAMELEN);
				m_pObjPropTree -> SetSelection (isSel, inBuff);
			}
			
			if (m_ObjProps.GetNoSelected() > 1)
				m_pbSortEntries.Enable();
			else	m_pbSortEntries.Disable();

		// HilfeText dieser Objprop anzeigen
			if (m_pBuff) {
			CTable t(*m_pObjPropTree);
			short iIndex = m_ObjProps.GetCaretIndex();
				
				if (iIndex == -1) break;
				
				m_ObjProps.GetString (m_pBuff, iIndex, _MAX_PATH);
				if (t.Find (m_pBuff)) {
				ObjectPropertyLock l(t);
				
					if (l) {
						l -> GetHelpText (m_pBuff, _MAX_PATH);
						m_ftHelpText.SetText (m_pBuff);
					}
				}
			}
		}
		break;
		
	case IDC_OBJPROPMCODES:
		m_FileButton.SetState (false);
		m_ClipButton.SetState (false);
		m_WindowButton.SetState (false);
		if (!DEX_GetROMode())
			m_MCodeButton.SetState (true);

		AdjustControls();
		break;
	}
HEAPCHECK(); }


void ObjectPropertyDlg :: AdjustControls (void)
{
// wenn keine Datei gegeben ist, aber generiert werden soll, dann OK passiv
	if ((m_FileButton.GetState() && m_FileName.GetTextLen() == 0) ||
	    (m_MCodeButton.GetState() && m_MCodes.GetCurrentIndex() == -1))
		m_OKButton.Disable();
	else
		m_OKButton.Enable();
				
	if (m_MCodeButton.GetState()) {
		m_HeadLine.Disable();
		m_Cumulation.Disable();
	} else {
		m_HeadLine.Enable();
		m_Cumulation.Enable();
	}
}


void ObjectPropertyDlg :: EditChange (ControlEvt e)
{
SingleLineEdit *pSLE = (SingleLineEdit *)e.GetControl();

	if (pSLE -> GetTextLen() > 0) {
		m_ClipButton.SetState (false);
		m_FileButton.SetState (true);
	}
HEAPCHECK(); }


extern "C" {

// Properties für ein Objekt zusammenstellen ----------------------------------
typedef struct tagENUMOBJECTPROPDATA {
	char __huge *pPropBuff;
	char __huge *pCurrPos;
	long lActSize;
	long lMaxSize;
	ObjPropTree *pOPT;
	bool fGetData;
	bool fCount;
	long lMCode;
	char cDelChar;
} ENUMOBJECTPROPDATA;

bool EXPORTTRIAS WINAPI GenerateObjectProperties (long lONr, bool, void *pData)
{
ENUMOBJECTPROPDATA *pEOPD = (ENUMOBJECTPROPDATA *)pData;

	if (pEOPD -> pOPT == NULL) return false;

// für alle selektierten Einträge
CTable t (*pEOPD -> pOPT);
bool fOPropsFound = false;	// mindestens eine OProp vorhanden

// wenn Anzahl der Items geschrieben werden soll
	if (pEOPD -> fGetData && pEOPD -> fCount) {
		if (pEOPD -> lMaxSize - pEOPD -> lActSize < 1056L) {
		char HUGE *pNew = ReAlloc (pEOPD -> pPropBuff, pEOPD -> lMaxSize);

			if (pNew == NULL) return false;
			if (pNew != pEOPD -> pPropBuff) {
				pEOPD -> pCurrPos = pNew + pEOPD -> lActSize;
				pEOPD -> pPropBuff = pNew;
			}
			pEOPD -> lMaxSize *= 2;
		}
		if (pEOPD -> pPropBuff) {
			ltoa (pEOPD -> pOPT -> SelCount(), pEOPD -> pCurrPos, 10);

		long lLen = hstrlen (pEOPD -> pCurrPos);
		
			pEOPD -> pCurrPos += lLen;
			pEOPD -> lActSize += lLen;
			if ('\0' != pEOPD -> cDelChar) {
				*(pEOPD -> pCurrPos)++ = pEOPD -> cDelChar;
			 	pEOPD -> lActSize++;
			}
		}
	}
	
// Properties besorgen
	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (!l || !l -> isSel()) continue;

		if (pEOPD -> lMaxSize - pEOPD -> lActSize < 1056L) {
		char HUGE *pNew = ReAlloc (pEOPD -> pPropBuff, pEOPD -> lMaxSize);

			if (pNew == NULL) return false;
			if (pNew != pEOPD -> pPropBuff) {
				pEOPD -> pCurrPos = pNew + pEOPD -> lActSize;
				pEOPD -> pPropBuff = pNew;
			}
			pEOPD -> lMaxSize *= 2;
		}
		if (pEOPD -> pPropBuff) {
			if (l -> InvokeFunc (lONr, pEOPD -> pCurrPos, 1024) != NULL)
				fOPropsFound = true;
			if (pEOPD -> fGetData) {
			long lLen = hstrlen (pEOPD -> pCurrPos);
			
				pEOPD -> pCurrPos += lLen;
				pEOPD -> lActSize += lLen;
				if ('\0' != pEOPD -> cDelChar) {
					*(pEOPD -> pCurrPos)++ = pEOPD -> cDelChar;
					pEOPD -> lActSize++;
				}
			} else
				*(pEOPD -> pCurrPos) = '\0';
		}
	}

// abschließendes CR/LF anfügen
	if (pEOPD -> fGetData) {
		if (*(pEOPD -> pCurrPos-1) == pEOPD -> cDelChar) {
			pEOPD -> pCurrPos--;
			pEOPD -> lActSize--;
		}

		if (pEOPD -> lMCode != -1L) {
			if (fOPropsFound) {
			// Delimiter setzen (auf ',', '/', ';', ':' oder '!')
				*(pEOPD -> pCurrPos) = '\0';	// Ende des Merkmales
				if ('\0' != pEOPD -> cDelChar)	// wenn Trennzeichen verwenden
					ReplaceDel (pEOPD -> pPropBuff);

			IUndoRedoObjectFeature *pIUndo = NULL;		// UndoRedo
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature, (LPVOID *)&pIUndo);

				if (SUCCEEDED(hr))
					hr = pIUndo -> Init (lONr, pEOPD -> lMCode, pEOPD -> pPropBuff, NULL); 

			// einzeln als Merkmal wegspeichern
			TARGETMERKMAL TM;
		
				INITSTRUCT(TM, TARGETMERKMAL);
				TM.lTarget = lONr;
				TM.lMCode = pEOPD -> lMCode;
				TM.imaxLen = (short)hstrlen (pEOPD -> pPropBuff);
				TM.pMText = pEOPD -> pPropBuff;
				TM.iTTyp = TT_Objekt;
				DEX_ModTextMerkmal (TM);

				if (S_OK == hr) 
					DEX_AddUndoRedo (pIUndo);
				if (pIUndo) pIUndo -> Release();
			}
		
			Free (pEOPD -> pPropBuff);
			pEOPD -> pPropBuff = Alloc (2048L);
			pEOPD -> lMaxSize = 2048L;
			pEOPD -> pCurrPos = pEOPD -> pPropBuff;
			pEOPD -> lActSize = 0;
		} else {
			*(pEOPD -> pCurrPos)++ = '\r';		// Trennzeichen Zeilenende
			*(pEOPD -> pCurrPos)++ = '\n';
			pEOPD -> lActSize += 2;
		}
	} else 
		*(pEOPD -> pCurrPos) = '\0';

HEAPCHECK(); return true;
}


// Generieren der MCodePropFuncs ----------------------------------------------
typedef struct tagENUMMCODESDATA {
	ObjectPropertyCreator *pOPCr;
	MultiSelListBox *pMSLB;
} ENUMMCODESDATA;


bool EXPORTTRIAS WINAPI EnumMCodes (long lMCode, DWORD, void *pData)
{
ENUMMCODESDATA *pEMD = (ENUMMCODESDATA *)pData;
ObjectProperty *pOP = ContCreate (*pEMD -> pOPCr, MCodeObjectPropertyInt)(lMCode);

	if (pOP) {
		pEMD -> pMSLB -> AddString (pOP -> pFName());
		HEAPCHECK(); return true;	// weitermachen
	}

HEAPCHECK(); return false;
}

}	// extern "C"


// Generieren der ObjektEigenschaften in einer Datei oder in der Zwischenablage
bool ObjectPropertyDlg :: GenerateObjProps (short iDest, long lMCode)
{
// wenn nichts selektiert wurde, dann einfach wieder raus
	if (m_ObjProps.GetNoSelected() == 0) return false;

// das kann eine Weile dauern
CEierUhr Wait (GetParent());

// evtl. Undo/Redo zuschalten
	if (iDest == OBJPROP_DESTMCODE) {
	ResString resUndoDesc (IDS_UNDOOBJPROPFEATURE, 64);

		DEX_BeginUndoLevel (resUndoDesc.Addr());
	}

// erstmal Objekte zählen, damit IProgressIndicator angezeigt werden kann
LPPROGRESSINDICATOR pIProgInd = NULL;

	ObjPropInitProgress (&pIProgInd);

// Ausgabe in ZeichenBuffer zusammenstellen
ENUMLONGKEY ELK;
ENUMOBJECTPROPDATA EOPD;

	EOPD.pPropBuff = Alloc (2048L);	// enthält dann alles
	EOPD.lMaxSize = 2048L;
	EOPD.lActSize = 0L;
	EOPD.pCurrPos = EOPD.pPropBuff;
	EOPD.pOPT = m_pObjPropTree;	// Baum der PropFuncs
	EOPD.fGetData = m_ObjPropData.isChecked();
	EOPD.lMCode = lMCode;
	EOPD.fCount = (m_Count.isChecked() && iDest == OBJPROP_DESTMCODE);
	EOPD.cDelChar = RetrieveDelimiter (iDest, '\t');

	if (iDest == OBJPROP_DESTFILE_CSV)
		EOPD.cDelChar = ',';	// Komma getrennt

// evtl. Überschrift generieren, Funktionen rücksetzen
CTable t(*m_pObjPropTree);

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (!l || !l -> isSel()) continue;
			
	// Funktionen Rücksetzen
		l -> InvokeFunc (OBJPROP_RESET, NULL, 0);
			
		if (EOPD.lMaxSize - EOPD.lActSize < OBJPROPFUNCNAMELEN+32) {
		char HUGE *pNew = ReAlloc (EOPD.pPropBuff, EOPD.lMaxSize);

			if (pNew == NULL) return false;
			if (pNew != EOPD.pPropBuff) {
				EOPD.pCurrPos = pNew + EOPD.lActSize;
				EOPD.pPropBuff = pNew;
			}
			EOPD.lMaxSize *= 2;
		}
			
	// FunktionsNamen anhängen (in Überschrift)
		if (iDest != OBJPROP_DESTMCODE && 
		    m_HeadLine.isChecked() && EOPD.pPropBuff) 
		{
			if (iDest == OBJPROP_DESTFILE_CSV)	// Komma getrennt: KopfZeile in '\"'
				wsprintf (EOPD.pCurrPos, "\"%s\"", l -> pFName());
			else
				strcpy (EOPD.pCurrPos, l -> pFName());

		long lLen = hstrlen (EOPD.pCurrPos);
		
			EOPD.pCurrPos += lLen;
			EOPD.lActSize += lLen;
			if ('\0' != EOPD.cDelChar) {
				*(EOPD.pCurrPos)++ = EOPD.cDelChar;
				EOPD.lActSize++;
			}
		}
	}

// abschließendes CR/LF anfügen
	if (iDest != OBJPROP_DESTMCODE && m_HeadLine.isChecked()) {
		if (*(EOPD.pCurrPos-1) == EOPD.cDelChar) {
			EOPD.pCurrPos--;
			EOPD.lActSize--;
		}
		*(EOPD.pCurrPos)++ = '\r';		// Trennzeichen Zeilenende
		*(EOPD.pCurrPos)++ = '\n';
		EOPD.lActSize += 2;
	} else
		*(EOPD.pCurrPos) = '\0';

// Daten generieren
	if (m_pObjEnum != NULL) {	// Enumerator gegeben
	long lONr = -1;
	ULONG ulCnt = 0;	// Zähler für ProgressIndikator

		for (m_pObjEnum -> Reset(); S_OK == m_pObjEnum -> Next (1, &lONr, NULL); ulCnt++) {
			GenerateObjectProperties (lONr, false, &EOPD);
			if (pIProgInd) {
				pIProgInd -> SetPosition(ulCnt);
				if (pIProgInd -> WasCanceled())
					break;
			}
		}
		if (pIProgInd) pIProgInd -> Release();

	} else {
	// alte Variante: ohne Enumerator
		ELK.eKey = (long)(void *)(GetParent() -> Handle (API_WINDOW_HWND));
		ELK.eFcn = (ENUMLONGKEYPROC)GenerateObjectProperties;
		ELK.ePtr = &EOPD;
		DEX_EnumSelectedObjects (ELK);
	}

	if (iDest == OBJPROP_DESTMCODE) 
		DEX_EndUndoLevel();

// evtl. Kumulation und Zähler ausgeben
	if (m_Cumulation.isChecked() || m_Count.isChecked()) {
	// zusätzliche Leerzeile dazwischensetzen
		*(EOPD.pCurrPos)++ = '\r';	// Trennzeichen Zeilenende
		*(EOPD.pCurrPos)++ = '\n';
		EOPD.lActSize += 2;
	}

	EOPD.fGetData = true;			// ggf. immer abfragen
	if (iDest != OBJPROP_DESTMCODE && m_Cumulation.isChecked())
		GenerateObjectProperties (OBJPROP_CUMULATION, false, &EOPD);
	if (iDest != OBJPROP_DESTMCODE && m_Count.isChecked())
		GenerateObjectProperties (OBJPROP_COUNT, false, &EOPD);

// Funktionen am Ende nochmal explizit rücksetzen
	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (!l || !l -> isSel()) 
			continue;
		l -> InvokeFunc (OBJPROP_RESET, NULL, 0);
	}

	if (EOPD.pCurrPos == EOPD.pPropBuff) {
		Free (EOPD.pPropBuff);
		HEAPCHECK(); return false;
	}

// Ergebnis verteilen
	switch (iDest) {
	case OBJPROP_DESTCLIPBOARD:		// in Zwischenablage ablegen
		if (EOPD.pPropBuff) {
		CClipboard DCB;

			DCB.Clear();
			DCB.Insert (EOPD.pPropBuff);
		}
		break;

	case OBJPROP_DESTWINDOW:
		if (EOPD.pPropBuff) {
		bool fToLargeText = false;
		
#if !defined(WIN32)
			if (USHRT_MAX <= EOPD.lActSize) {  
			ResString resCap (IDS_LISTOUTOFSPACECAP, 64);
			ResString resText (IDS_EDITOUTOFSPACE, 256);
			MessBox mb (resCap, resText, this);
			
				mb.SetType (ExclamationIcon | OkayButton);	
				mb.Show();
				fToLargeText = true;
			}
		
		ObjPropDestWindow OPDWDlg (this, EOPD.pPropBuff, fToLargeText);
#else
		ObjPropDestWindow OPDWDlg (this, EOPD.pPropBuff, m_HeadLine.isChecked());
#endif // WIN32			

			OPDWDlg.Show (Centre);
		}
		break;

	default:
		if (iDest >= OBJPROP_DESTFILE && iDest < OBJPROP_DESTFILE_LAST) 
		{	// als Datei ablegen
		int iLen = m_FileName.GetTextLen();

			if (iLen <= 0) {
				Free (EOPD.pPropBuff);
				HEAPCHECK(); return false;
			}
			
		char *pFileName = new char [iLen +2];

			if (pFileName == NULL) {
				db_error (EC_NOMEMORY, RC_GenerateObjProps);
				Free (EOPD.pPropBuff);
				HEAPCHECK(); return false;
			}

			m_FileName.GetText (pFileName, iLen+1);

		int fh = _lcreat (pFileName, 0);

			if (fh < 0) {
				db_error (EC_NOFILE, RC_GenerateObjProps);
				Free (EOPD.pPropBuff);
				HEAPCHECK(); return false;
			}

			_hwrite (fh, EOPD.pPropBuff, EOPD.lActSize);
			_lclose (fh);
		}
		break;
	}

// Speicher wieder freigeben
	Free (EOPD.pPropBuff);

HEAPCHECK(); return true;
}

static ULONG CountObjects (IEnum<LONG> *pObjEnum)
{
ULONG ulCnt = 0;	// counter
long lONr = 0;		// dummy

	for (pObjEnum -> Reset(); S_OK == pObjEnum -> Next (1, &lONr, NULL); ulCnt++) 
		{}

return ulCnt;
}

HRESULT ObjectPropertyDlg :: ObjPropInitProgress (LPPROGRESSINDICATOR *ppIProgInd)
{
	*ppIProgInd = NULL;

LPPROGRESSINDICATOR pIStatus = NULL;
HRESULT hr = PiCreateInstance (IID_IProgressIndicator, (LPVOID *)&pIStatus);

	if (FAILED(hr)) return hr;

HWND hNewWnd = pIStatus -> InitNew (Handle (API_WINDOW_HWND), 0L);

	if (NULL == hNewWnd) return ResultFromScode (E_FAIL);

	hr = pIStatus -> Restart (0L, (ULONG)CountObjects (m_pObjEnum), 
				  PIFLAG_CAPTION | PIFLAG_STATUS | PIFLAG_RESULT |
				  PIFLAG_TIME | PIFLAG_ADJUSTPERCENT);
	if (FAILED(hr)) {
		pIStatus -> Release();
		return hr;
	}

// diverse Texte initialisieren
ResString resCaption (IDS_OBJPROPCAP, 64);
ResString resStatus (IDS_OBJPROPSTATUS, 64);

	pIStatus -> ChangeText (PIFLAG_CAPTION, resCaption);
	pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, resStatus);

	*ppIProgInd = pIStatus;

return NOERROR;
}

bool ObjectPropertyDlg :: GenerateMCodeIntObjPropFuncs (ObjectPropertyCreator &OPCr)
{
ENUMMCODESDATA EMD;
ENUMNOKEYEX ENK;

	EMD.pOPCr = &OPCr;
	EMD.pMSLB = &m_ObjProps;
	
	ENK.eFcn = (ENUMNOKEYEXPROC)EnumMCodes;
	ENK.ePtr = &EMD;
	ENK.eData = DWORD('a');	// ObjektMerkmale ohne Systemmerkmale

HEAPCHECK(); return DEX_EnumMCodesEx (ENK);
}


// ----------------------------------------------------------------------------
// Installierte ObjPropFuncs --------------------------------------------------
// BasisKlasse
ObjectProperty :: ObjectProperty (const char *pFName)
{
	m_pFName = new char [strlen (pFName) +1];
	if (m_pFName != NULL) 
		strcpy (m_pFName, pFName);
	m_isSel = false;
	m_iOrd = 0;
HEAPCHECK(); }

ObjectProperty :: ObjectProperty (ObjectProperty &rOP, short iOrd)
{
	m_pFName = new char [strlen (rOP.m_pFName) +1];
	if (m_pFName != NULL) 
		strcpy (m_pFName, rOP.m_pFName);
	m_isSel = rOP.m_isSel;
	m_iOrd = iOrd;
HEAPCHECK(); }

ObjectProperty :: ~ObjectProperty (void)
{
	DELETE (m_pFName);
HEAPCHECK(); }

void *GetObjPropKeyStr (void *pObj)
{
	HEAPCHECK(); return ((ObjectProperty *)pObj) -> pFName();
}

void *GetObjPropKeyInt (void *pObj)
{
	HEAPCHECK(); return & ((ObjectProperty *)pObj) -> FOrd();
}


// ----------------------------------------------------------------------------
// externe ObjPropFuncs (in Erweiterungen gegebene) ---------------------------
ObjectPropertyExt :: ObjectPropertyExt (const char *pFName, short iFuncID, Extension *pExt)
		   : ObjectProperty (pFName),
		     m_Ext (*pExt)
{
	m_iFuncID = iFuncID;
HEAPCHECK(); }

ObjectPropertyExt :: ObjectPropertyExt (ObjectPropertyExt &rOPE, short iOrd)
		   : ObjectProperty (rOPE, iOrd),
		     m_Ext (rOPE.m_Ext)
{
	m_iFuncID = rOPE.m_iFuncID;
HEAPCHECK(); }

ObjectPropertyExt :: ~ObjectPropertyExt (void)
{
	// nothing to do else
HEAPCHECK(); }

ObjectProperty *ObjectPropertyExt :: Insert (ObjectPropertyCreator &rCr, short iOrd)
{
	HEAPCHECK(); return ContCreate (rCr, ObjectPropertyExt) (*this, iOrd);
}



char *ObjectPropertyExt :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
INVOKEOBJPROPDATAEX IOPD;

	INITSTRUCT(IOPD, INVOKEOBJPROPDATAEX);
	IOPD.iFuncID = m_iFuncID;
	IOPD.lONr = lONr;
	IOPD.iBuffLen = iLen;
	IOPD.pBuff = pBuffer;
	IOPD.pFName = pFName();
		
HEAPCHECK(); return TrimRightAndLeft (m_Ext.InvokePropFunc ((INVOKEOBJPROPDATA *)&IOPD));
}


char *ObjectPropertyExt :: GetHelpText (char *pBuffer, short iLen)
{
// hier von Erweiterung HelpText holen
GETHELPTEXTDATAEX GHTD;

	INITSTRUCT (GHTD, GETHELPTEXTDATAEX);
	GHTD.iFuncID = m_iFuncID;
	GHTD.iBuffLen = iLen;
	GHTD.pBuff = pBuffer;
	GHTD.pFName = pFName();

HEAPCHECK(); return m_Ext.GetHelpText ((GETHELPTEXTDATA *)&GHTD);
}

// ----------------------------------------------------------------------------
// interne ObjPropFuncs (in TRIAS vordefinierte) ------------------------------
ObjectPropertyInt :: ObjectPropertyInt (const char *pFName, 
				        const char *pHText, INTOBJPROPPROC pFunc)
		   : ObjectProperty (pFName)
{
	m_pFunc = pFunc;		// Pointer auf interne Funktion
	if (pHText) {
		m_pHText = new char [strlen (pHText)+1];
		if (m_pHText) strcpy (m_pHText, pHText);
	}
HEAPCHECK(); }

ObjectPropertyInt :: ObjectPropertyInt (ObjectPropertyInt &rOPI, short iOrd)
		   : ObjectProperty (rOPI, iOrd)
{
	m_pFunc = rOPI.m_pFunc;		// Pointer auf interne Funktion
	if (rOPI.m_pHText) {
		m_pHText = new char [strlen (rOPI.m_pHText)+1];
		if (m_pHText) strcpy (m_pHText, rOPI.m_pHText);
	}
HEAPCHECK(); }

ObjectProperty *ObjectPropertyInt :: Insert (ObjectPropertyCreator &rCr, short iOrd)
{
	HEAPCHECK(); return ContCreate (rCr, ObjectPropertyInt) (*this, iOrd);
}

ObjectPropertyInt :: ~ObjectPropertyInt (void)
{
	DELETE(m_pHText);
HEAPCHECK(); }

char *ObjectPropertyInt :: GetHelpText (char *pBuffer, short iLen)
{
	if (m_pHText && pBuffer) {
		strncpy (pBuffer, m_pHText, iLen);
		pBuffer[iLen-1] = '\0';
	}
	
HEAPCHECK(); return pBuffer;
}



extern "C" {

// HilfsVehikel ---------------------------------------------------------------
inline char * F (INTOBJPROPPROC pF, long lONr, char *pBuffer, short iLen)
{
	HEAPCHECK(); return ((INTOBJPROPCALLBACK)pF)(lONr, pBuffer, iLen);
}

}	// extern "C" 

char *ObjectPropertyInt :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (m_pFunc) 
		return TrimRightAndLeft (F(m_pFunc, lONr, pBuffer, iLen));

return NULL;
}


// ----------------------------------------------------------------------------
// Interne ObjPropFunc, die einen MerkmalsCode repräsentiert ------------------
const char *MCodeObjPropFuncName (long lMCode)
{
static char cbFuncName[OBJPROPFUNCNAMELEN+1];
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;
ErrCode RC; 

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbFuncName;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = OBJPROPFUNCNAMELEN+1;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY) {
	string strFmt = ResString (IDM_MCODEFORMAT, 32);

		if (10 == DEX_GetMkBase()) {
			strFmt += "%ld";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		} else {
			strFmt += "%lx";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		}
	}

HEAPCHECK(); return cbFuncName;
}


MCodeObjectPropertyInt :: MCodeObjectPropertyInt (long lMCode)
			: ObjectProperty (MCodeObjPropFuncName (lMCode))
{
	m_lMCode = lMCode;
HEAPCHECK(); }

MCodeObjectPropertyInt :: MCodeObjectPropertyInt (MCodeObjectPropertyInt &rMOPI, short iOrd)
			: ObjectProperty (rMOPI, iOrd)
{
	m_lMCode = rMOPI.m_lMCode;
HEAPCHECK(); }

ObjectProperty *MCodeObjectPropertyInt :: Insert (ObjectPropertyCreator &rCr, short iOrd)
{
	HEAPCHECK(); return ContCreate (rCr, MCodeObjectPropertyInt) (*this, iOrd);
}

MCodeObjectPropertyInt :: ~MCodeObjectPropertyInt (void)
{
HEAPCHECK(); }

char *MCodeObjectPropertyInt :: GetHelpText (char *pBuffer, short)
{
// Einlesen des FormatStrings als Resource
	wsprintf (pBuffer, 
		  ResString (IDS_OBJPROPMCODEHELP, OBJPROPFUNCHELPLEN), pFName());
		  	
HEAPCHECK(); return pBuffer;
}


char *MCodeObjectPropertyInt :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
static long lCnt = 0;
static long lCum = 0;

	if (lONr == OBJPROP_RESET) {
		lCnt = 0;		// Reset counter
		lCum = 0;	
		HEAPCHECK(); return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		return ltoa (lCum, pBuffer, 10);			
	} else if (lONr == OBJPROP_COUNT) {
		HEAPCHECK(); return ltoa (lCnt, pBuffer, 10);			
	} else if (lONr > 0 && pBuffer) {
	TARGETMERKMAL gm;

		memset (&gm, '\0', sizeof (TARGETMERKMAL));
		gm.dwSize = sizeof(TARGETMERKMAL);
		gm.lTarget = (LPARAM)lONr;		// ObjektNummer
		gm.lMCode = m_lMCode;			// MCode
		gm.imaxLen = iLen;
		gm.pMText = pBuffer;
		gm.iTTyp = TT_Objekt;
		if (DEX_GetTextMerkmal (gm)) {		// MWert besorgen
//			OemToAnsi (pBuffer, pBuffer);
			lCnt++;
			lCum += atol (pBuffer);
			HEAPCHECK(); return TrimRightAndLeft (pBuffer);
		}
	}

HEAPCHECK(); return NULL;
}


// Eingabe eines zusätzlichen Feldtextes --------------------------------------
char *MakeFullOPName (int iCnt)
{
static char cbName[OBJPROPFUNCNAMELEN+1];
ResString res (IDS_OBJPROPFTEXT, OBJPROPFUNCNAMELEN+1);

	strcpy (cbName, res);
	strcat (cbName, " ");
	itoa (iCnt, &cbName[strlen(cbName)], 10);
	
HEAPCHECK(); return cbName;
}

CQueryFieldPropertyInt :: CQueryFieldPropertyInt (pWindow pW, short iCnt)
			: ObjectProperty (MakeFullOPName (iCnt))
{
	m_pFText = new char [_MAX_PATH];
	m_fUseForAll = false;
	m_pW = pW;
	m_iCnt = iCnt;

	m_lCnt = 0;
	m_lCum = 0;
HEAPCHECK(); }

CQueryFieldPropertyInt :: CQueryFieldPropertyInt (CQueryFieldPropertyInt &rQFI, short iOrd)
			: ObjectProperty (rQFI, iOrd)
{
	if (rQFI.m_pFText) {
		m_pFText = new char [_MAX_PATH];
		if (m_pFText) strcpy (m_pFText, rQFI.m_pFText);
	} else
		m_pFText = NULL;
	m_fUseForAll = rQFI.m_fUseForAll;
	m_pW = rQFI.m_pW;
	m_iCnt = rQFI.m_iCnt;
	
	m_lCnt = 0;
	m_lCum = 0;
HEAPCHECK(); }

ObjectProperty *CQueryFieldPropertyInt :: Insert (ObjectPropertyCreator &rCr, short iOrd)
{
	HEAPCHECK(); return ContCreate (rCr, CQueryFieldPropertyInt) (*this, iOrd);
}

CQueryFieldPropertyInt :: ~CQueryFieldPropertyInt (void)
{
	DELETE (m_pFText);
HEAPCHECK(); }


char *CQueryFieldPropertyInt :: GetHelpText (char *pBuffer, short)
{
// Einlesen des FormatStrings als Resource
	strcpy (pBuffer, ResString (IDS_OBJPROPQFIELDHELP, OBJPROPFUNCHELPLEN));
		  	
HEAPCHECK(); return pBuffer;
}


char *CQueryFieldPropertyInt :: InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	if (lONr == OBJPROP_RESET) {
		m_lCnt = 0;		// Reset counter
		m_lCum = 0;
		m_fUseForAll = false;	
		HEAPCHECK(); return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		HEAPCHECK(); return ltoa (m_lCum, pBuffer, 10);
	} else if (lONr == OBJPROP_COUNT) {
		HEAPCHECK(); return ltoa (m_lCnt, pBuffer, 10);
	} else if (lONr > 0 && pBuffer) {
		if (m_fUseForAll) {	// Fenster ist bereits da gewesen
			strcpy (pBuffer, m_pFText);
			m_lCnt++;
			m_lCum += atol (pBuffer);
			HEAPCHECK(); return pBuffer;
		} else {
		// hier Fenster anzeigen und Text abfragen
		CQueryFieldDlg QFDlg (m_pW, m_iCnt);
		
			if (!QFDlg.FInit (lONr, true)) 
				return pBuffer;
			QFDlg.Show();
		
		bool fRet = QFDlg.Result();
			
			m_fUseForAll = QFDlg.UseForAll();
			QFDlg.GetFieldText (pBuffer, ULONG(iLen));
			if (m_fUseForAll)
				strcpy (m_pFText, pBuffer);	// ggf. merken
			m_lCnt++;
			m_lCum += atol (pBuffer);
			HEAPCHECK(); return fRet ? pBuffer : NULL;
		}	
	}

HEAPCHECK(); return NULL;
}


// ----------------------------------------------------------------------------
// Baum, der die installierten ObjPropFuncs enthält ---------------------------
ObjPropTree :: ObjPropTree (pGetKeyFcn pFGet, pKeyCmpFcn pFCmp)
	     : CTree (pFGet, pFCmp)
{
	// nothing else to do
HEAPCHECK(); }

ObjPropTree :: ~ObjPropTree (void)
{
	EveryDelete ();
HEAPCHECK(); }

void EXPORTTRIAS ObjPropTree :: UserDelete (void *pObj)
{
	((ObjectProperty *)pObj) -> /*ObjectProperty ::*/ ~ObjectProperty();
HEAPCHECK(); }

// Funktionen, die die Selektion einzelner oder aller Elemente richten --------
void ObjPropTree :: SetAll (bool fFlag)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (l) l -> SetSelection (fFlag);
	}
HEAPCHECK(); }


void ObjPropTree :: SetSelection (bool isSel, char *pFName)
{
CTable t(*this);

	if (t.Find (pFName)) {
	ObjectPropertyLock l(t);

		if (l) l -> SetSelection (isSel);
	}
HEAPCHECK(); }


long ObjPropTree :: SelCount (void)
{
CTable t(*this);
long lCnt = 0;

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (l && l -> isSel()) lCnt++;
	}

HEAPCHECK(); return lCnt;
}


ObjPropTreeStr :: ObjPropTreeStr (void)
		: ObjPropTree (GetObjPropKeyStr, StrCmp)
{
HEAPCHECK(); }

int ShortCmp (void *, void *);

ObjPropTreeInt :: ObjPropTreeInt (void)
		: ObjPropTree (GetObjPropKeyInt, ShortCmp)
{
HEAPCHECK(); }

// Interne ObjPropFuncs -------------------------------------------------------
extern "C" {

// ObjektNummer ---------------------------------------------------------------
char * EXPORTTRIAS WINAPI IntObjPropONr (long lONr, char *pBuffer, short)
{
static long lCnt = 0;

	if (lONr == OBJPROP_RESET) {
		lCnt = 0;			// Reset counter
		HEAPCHECK(); return NULL;
	}
	
// normale Funktionsabwicklung
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';		// no cumulation
		HEAPCHECK(); return pBuffer;
	} else if (lONr == OBJPROP_COUNT) {
		HEAPCHECK(); return ltoa (lCnt, pBuffer, 10);
	} else if (lONr > 0) {
		lCnt++;
		HEAPCHECK(); return ltoa (lONr, pBuffer, 10);
	}

HEAPCHECK(); return NULL;
}

#if defined(WIN32)
///////////////////////////////////////////////////////////////////////////////
// ObjectGUID
#define GUID_CCH	39

char * EXPORTTRIAS WINAPI IntObjPropGUID (long lONr, char *pBuffer, short)
{
static long lCnt = 0;

	if (lONr == OBJPROP_RESET) {
		lCnt = 0;			// Reset counter
		HEAPCHECK(); return NULL;
	}
	
// normale Funktionsabwicklung
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';		// no cumulation
		HEAPCHECK(); return pBuffer;
	} else if (lONr == OBJPROP_COUNT) {
		HEAPCHECK(); return ltoa (lCnt, pBuffer, 10);
	} else if (lONr > 0) {
	OBJECTGUID OUID;

		INITSTRUCT(OUID, OBJECTGUID);
		OUID.lONr = lONr;

		if (SUCCEEDED(DEX_GetObjectGuid (OUID))) {
		OLECHAR coleBuffer[GUID_CCH];
		HRESULT hr = StringFromGUID2 (OUID.guid, coleBuffer, GUID_CCH);

			if (FAILED(hr)) return NULL;

			USES_CONVERSION;
			strcpy (pBuffer, OLE2A(coleBuffer));

			lCnt++;
			return pBuffer;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// ObjektKlassenschlüssel
char * EXPORTTRIAS WINAPI IntObjPropOKS (long lONr, char *pBuffer, short)
{
static long lCnt = 0;

	if (lONr == OBJPROP_RESET) {
		lCnt = 0;			// Reset counter
		HEAPCHECK(); return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';		// no cumulation
		HEAPCHECK(); return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {
	// Zähler der Aufrufe seit dem letzten Reset
		HEAPCHECK(); return ltoa (lCnt, pBuffer, 10);
	} else if (lONr > 0) {
	long lIdent = DEX_GetObjIdent (lONr);

		lCnt++;
		ClassFromIdent (lIdent, pBuffer);
		return pBuffer;
	}

HEAPCHECK(); return NULL;
}
#endif // WIN32

// Identifikator --------------------------------------------------------------
char * EXPORTTRIAS WINAPI IntObjPropIdent (long lONr, char *pBuffer, short)
{
static long lCnt = 0;

	if (lONr == OBJPROP_RESET) {
		lCnt = 0;			// Reset counter
		HEAPCHECK(); return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_CUMULATION) {
		*pBuffer = '\0';		// no cumulation
		HEAPCHECK(); return pBuffer;	
	} else if (lONr == OBJPROP_COUNT) {
	// Zähler der Aufrufe seit dem letzten Reset
		HEAPCHECK(); return ltoa (lCnt, pBuffer, 10);
	} else if (lONr > 0) {
	long lIdent = DEX_GetObjIdent (lONr);

		lCnt++;
		if (10 == DEX_GetIdBase()) 
			ltoa (lIdent, pBuffer, 10);
		else
			wsprintf (pBuffer, "0x%lx", lIdent);
		return pBuffer;
	}

HEAPCHECK(); return NULL;
}


// Objekttyp ------------------------------------------------------------------
char * EXPORTTRIAS WINAPI IntObjPropObjTyp (long lONr, char *pBuffer, short)
{
static long lCntPunkt = 0L;
static long lCntKante = 0L;
static long lCntFlaeche = 0L;
static long lCntText = 0L;
static long lCntKO = 0L;
static long lCntUnknown = 0L;

	if (lONr == OBJPROP_RESET) {
		lCntPunkt = 0L;
		lCntKante = 0L;
		lCntFlaeche = 0L;
		lCntText = 0L;
		lCntKO = 0L;
		lCntUnknown = 0L;
		HEAPCHECK(); return NULL;
	}
	
	if (pBuffer == NULL) return NULL;
	
	if (lONr == OBJPROP_COUNT) {
	// GesamtObjektanzahl ausgeben
	ResString Format (IDS_OBJPROPCUMFORMAT, 64);

		wsprintf (pBuffer, (const char *)Format.Addr(),
				   lCntPunkt + lCntKante + lCntFlaeche + 
		      		   lCntText + lCntKO + lCntUnknown);
		HEAPCHECK(); return pBuffer;	
	} else if (lONr == OBJPROP_CUMULATION) {
	ResString Format (IDS_OBJPROPCNTFORMAT, 64);
	
	        wsprintf (pBuffer, (const char *)Format.Addr(),
	        		   lCntPunkt, lCntKante, lCntFlaeche,
	        		   lCntText, lCntKO);
	        HEAPCHECK(); return pBuffer;
	} else if (lONr > 0) {
	// eigentliche Arbeit
	short iObjTyp = DEX_GetObjectType (lONr);
	unsigned int iResID;

		switch (iObjTyp) {
		case OT_PUNKT:
			iResID = IDS_OBJPROPPUNKTOBJ;
			lCntPunkt++;
			break;
			
		case OT_KANTE:
			iResID = IDS_OBJPROPKANTENOBJ;
			lCntKante++;
			break;
			
		case OT_FLAECHE:
			iResID = IDS_OBJPROPFLAECHENOBJ;
			lCntFlaeche++;
			break;
			
		case OT_LABEL:
		case OT_TEXT:
			iResID = IDS_OBJPROPTEXTOBJ;
			lCntText++;
			break;
			
		case OT_KO:
			iResID = IDS_OBJPROPKOMPLEXOBJ;
			lCntKO++;
			break;
			
		case OT_KREIS:
			iResID = IDS_OBJPROPKREISOBJ;
			lCntFlaeche++;
			break;
			
		case OT_UNKNOWN:
		default:
			iResID = IDS_OBJPROPUNKNOWNOBJ;
			lCntUnknown++;
			break;
		}
		if (pBuffer) 
			strcpy (pBuffer, ResString (iResID, 64));
		HEAPCHECK(); return pBuffer;
	}

HEAPCHECK(); return NULL;
}

// ---------------------------------------------------------------------------
// Speicherverwaltung für Zwischenablage -------------------------------------
static char HUGE *WINAPI Alloc (long lCount)
{
HGLOBAL hG = GlobalAlloc (GHND, (DWORD)lCount);

	if (!hG) return NULL;
	
HEAPCHECK(); return (char HUGE *)GlobalLock (hG);
}

static bool WINAPI Free (char HUGE *pB)
{
#if !defined(WIN32)
HGLOBAL hG = (HGLOBAL)GlobalHandle (HIWORD (pB));
#else
HGLOBAL hG = (HGLOBAL)GlobalHandle (pB);
#endif

	if (!hG || GlobalUnlock (hG)) {
#if defined(WIN32) && defined(_DEBUG)
	DWORD dwErr = GetLastError();
#endif
		return false;
	}

HEAPCHECK(); return GlobalFree (hG) == NULL;
}

static char HUGE * WINAPI ReAlloc (char HUGE *pB, long lCount)
{
#if !defined(WIN32)
HGLOBAL hG = (HGLOBAL)GlobalHandle (HIWORD (pB));
#else
HGLOBAL hG = (HGLOBAL)GlobalHandle (pB);
#endif

	if (!hG || GlobalUnlock (hG)) {
#if defined(WIN32) && defined(_DEBUG)
	DWORD dwErr = GetLastError();
#endif
		return NULL;
	}
	if ((hG = GlobalReAlloc (hG, (DWORD)lCount*2, GMEM_MOVEABLE)) != 0) {
		HEAPCHECK(); return (char HUGE *)GlobalLock (hG);
	}

HEAPCHECK(); return NULL;
}

#if !defined(WIN32)
// HookFunktion für COMMDLG SaveAsDlg -----------------------------------------
UINT EXPORTTRIAS CALLBACK ObjPropHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
	if (wMsg == WM_INITDIALOG && Ctl3dEnabled()) 
		Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	// lediglich CTL3D aktivieren

return false;
}
#endif // WIN32

}	// extern "C"
		

// Fensterausgabe der Objekteigenschaften -------------------------------------
#pragma warning (disable: 4355)

#if defined(WIN32)
ObjPropDestWindow :: ObjPropDestWindow (pWindow pW, LPCSTR pcText, bool fHeadline)
		   : DialogWindow (pW, OBJPROPDESTWINDOW),
			 m_pbCopy (this, IDC_COPYTOCLIPBOARD),
		     m_Result (this, IDC_OBJPROPDESTWINDOW)
{
	if (NULL == pcText) {
		m_pbCopy.Disable();
		return;
	}

	m_pcText = pcText;		// nur für ClipBoard speichern

	if (!fHeadline)
		m_Result.SetStyle (LVS_NOCOLUMNHEADER);

#if defined(ListView_GetExtendedListViewStyle)
	m_Result.SetExtendedStyle (m_Result.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
#endif 
	InitListViewCtrl (pcText, fHeadline);

HEAPCHECK(); 
}

void ObjPropDestWindow :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDC_COPYTOCLIPBOARD:
		{
			TX_ASSERT(NULL != m_pcText);

		CClipboard DCB;

			DCB.Clear();
			DCB.Insert (m_pcText);
		}
		break;
	}

HEAPCHECK(); }

bool ObjPropDestWindow :: InitListViewCtrl (LPCSTR pcText, bool fHeadline)
{
// zeilenweise bearbeiten, jedes feld kommt in eine extra Spalte
CEierUhr Wait (GetParent());
const char *pcT = pcText;
const char *pcField = pcText;
int iColCnt = 0;
int iLineCnt = 0;

	while (*pcT) {
		switch (*pcT) {
		case '\r':
		case '\t':	// FeldEnde
			{
			string str (pcField, pcT - pcField);

				if (0 == iLineCnt) {	// erste Zeile
					if (fHeadline) 
						m_Result.InsertColumn (iColCnt, str.c_str(), LVCFMT_LEFT, 120, 0);
					else {
					ResString resColHdr (IDS_COLUMNHEADER, 32);
					char cbBuffer[64]; 

						wsprintf (cbBuffer, resColHdr.Addr(), iColCnt+1);
						m_Result.InsertColumn (iColCnt, cbBuffer, LVCFMT_LEFT, 120, 0);
						m_Result.InsertItem (0, str.c_str());
					}
				} else if (0 == iColCnt)	// neue Zeile
					m_Result.InsertItem (fHeadline ? iLineCnt-1 : iLineCnt, str.c_str());
				else {
				LV_ITEM lvi;

					memset (&lvi, 0, sizeof(LV_ITEM));
					lvi.mask = LVIF_TEXT;
					lvi.pszText = (char *)str.c_str();
					lvi.iItem = fHeadline ? iLineCnt-1 : iLineCnt;
					lvi.iSubItem = iColCnt;
					m_Result.SetItem (&lvi);
				}					
				++iColCnt;
				pcField = pcT+1;	// nächstes Feld
			}

			if ('\r' == *pcT) {	// ZeilenEnde
				++iLineCnt;
				iColCnt = 0;
				++pcT;		// '\n' überspringen
				++pcField;
			}
			break;

		default:
			break;
		}
		++pcT;
	}

return true;
}

#else // alte Variante

ObjPropDestWindow :: ObjPropDestWindow (pWindow pW, char *pText, bool fToLarge)
		   : DialogWindow (pW, OBJPROPDESTWINDOW),
		     m_Result (this, IDE_OBJPROPDESTWINDOW)
{
	if (pText) {
		if (fToLarge) 	// Textlänge begrenzen
			pText[(USHRT_MAX*15L)/16L] = '\0';
		m_Result.SetText (pText);
	}
HEAPCHECK(); }

void ObjPropDestWindow :: ButtonClick (ControlEvt)
{
	EndDlg (1);
HEAPCHECK(); }

#endif // WIN32

#pragma warning (default: 4355)

ObjPropDestWindow :: ~ObjPropDestWindow (void)
{
	// nothing to do
HEAPCHECK(); }

// Dialogfenster zum sortieren der ObjektPropFunktionen -----------------------
ObjPropTree *ObjectPropertyDlg :: ResortObjProps (ObjPropTree *pOPT)
{
// Dialogfenster anzeigen, welches alle selektierten OPF's enthält
CSortEntryDlg SEDlg (this, pOPT);

	if (!SEDlg.FInit()) { HEAPCHECK(); return pOPT; }
	SEDlg.Show();
	if (!SEDlg.Result()) { HEAPCHECK(); return pOPT; }

// neuen Baum erzeugen, alle OPF's in der gewünschten Reihenfolge umhängen
ObjPropTree *pnewOPT = new ObjPropTreeInt;
char *pcbFName = new char [_MAX_PATH];

	if (pnewOPT == NULL || pcbFName == NULL) {
		DELETE (pnewOPT);
		HEAPCHECK(); return pOPT;
	}

ObjectPropertyCreator OPCr (*pnewOPT);
short iCnt = SEDlg.OPList().GetCount();

	{
	CTable t(*pOPT);

		for (short iIndex = 0; iIndex < iCnt; iIndex++) {
			SEDlg.OPList().GetString (pcbFName, iIndex, _MAX_PATH);	
			if (t.Find (pcbFName)) {
			ObjectPropertyLock l(t);
			
				TX_ASSERT(NULL != (ObjectProperty *)l);
				if (!l) continue;

				l -> Insert (OPCr, iIndex);
			}
		}
	}	// CTable goes out of scope

	DELETE (pOPT);
	DELETE (pcbFName);

// alle Einträge als selektiert kennzeichnen
	pnewOPT -> SetAll (true);
		
HEAPCHECK(); return pnewOPT;
}


// Eigentliche DialogFunktionen -----------------------------------------------
#pragma warning (disable: 4355)

CSortEntryDlg :: CSortEntryDlg (pWindow pW, ObjPropTree *pOPT)
	       : DialogWindow (pW, ResID (SORTOBJPROPDLG)),
		 m_lbEntries (this, IDL_OBJPROPENTRIES),
		 m_rOPT (*pOPT)
{
HEAPCHECK(); }

#pragma warning (default: 4355)

bool CSortEntryDlg :: FInit (void)
{
	if (m_rOPT.Count() == 0) return false;
	
CTable t(m_rOPT);

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);
	
		if (!l || !l -> isSel()) continue;
		m_lbEntries.AddString (l -> pFName());
	}
	if (m_lbEntries.GetCount() > 0)
		m_lbEntries.ChangeCurrentIndex (0);
	else 
		return false;

HEAPCHECK(); return true;
}

CSortEntryDlg :: ~CSortEntryDlg (void)
{
	// nothing to do
HEAPCHECK(); }


void CSortEntryDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg(1);
		break;
		
	case IDCANCEL:
		EndDlg();
		break;
		
	case IDB_ENTRYUP:
		MoveEntry ();
		break;
		
	case IDB_ENTRYDOWN:
		MoveEntry (false);
		break;
	}
}


void CSortEntryDlg :: MoveEntry (bool fUp)
{
short iIndex = m_lbEntries.GetCurrentIndex();

	if (iIndex == -1) return;
	if (iIndex >= m_lbEntries.GetCount()-1 && fUp)
		return;		// geht nicht weiter hoch
	if (iIndex == 0 && !fUp)
		return;		// geht nicht weiter runter

char *pEntry = new char [_MAX_PATH];

	if (pEntry == NULL) return;
	
	m_lbEntries.GetString (pEntry, iIndex, _MAX_PATH);
	m_lbEntries.DelString (iIndex);
	iIndex = m_lbEntries.AddString (pEntry, fUp ? iIndex+1 : iIndex-1);
	m_lbEntries.ChangeCurrentIndex (iIndex);
	
	DELETE (pEntry);
HEAPCHECK(); }


// Rechts und Links alle Leerzeichen abschneiden ------------------------------
char *TrimRightAndLeft (char *pStr)
{
	if (pStr == NULL) return NULL;
	
char *pCurr = pStr;

// führende Spaces entfernen
	while (*pCurr) {
		if (!isascii (*pCurr) || !isspace (*pCurr))
			break;
		pCurr++;
	}

// String an den Anfang verschieben
	if (pCurr > pStr) {
	int iLen = (int)hstrlen (pCurr);

		memmove (pStr, pCurr, iLen);
		pStr[iLen] = '\0';
	}

// Abschließende Spaces entfernen
	pCurr = &pStr[hstrlen(pStr)-1];	// letztes Zeichen der Kette
	while (pCurr > pStr) {
		if (!isascii (*pCurr) || !isspace (*pCurr)) {
			*(pCurr+1) = '\0';
			break;
		}
		pCurr--;
	}
		
HEAPCHECK(); return pStr;
}

bool ReplaceDelimiter (char *pStr, char cDel, char cOldDel)
{
	if (pStr == NULL) return false;
	
// testen, ob der gewünschte Delimiter bereits im String ist
	if (strchr (pStr, cDel)) return false; 		// nicht ersetzt
	
// cDel als Delimiter verwenden
char *pDel = pStr;

	while ((pDel = strchr (pDel, cOldDel)) != NULL)
		*pDel = cDel;

HEAPCHECK(); return true;	
}


// Delimiter setzen (auf ',', '/', ';', ':' oder '!') -------------------------
void ReplaceDel (char *pStr)
{
	if (ReplaceDelimiter (pStr, ',', '\t')) { HEAPCHECK(); return; }
	if (ReplaceDelimiter (pStr, '/', '\t')) { HEAPCHECK(); return; }
	if (ReplaceDelimiter (pStr, ';', '\t')) { HEAPCHECK(); return; }
	if (ReplaceDelimiter (pStr, ':', '\t')) { HEAPCHECK(); return; }
	if (ReplaceDelimiter (pStr, '!', '\t')) { HEAPCHECK(); return; }
	
// nichts passendes gefunden, also alles beim alten lassen
HEAPCHECK(); }


// Fenster zur Eingabe eines Textes als Objekteigenschaft ---------------------
#pragma warning (disable: 4355)

CQueryFieldDlg :: CQueryFieldDlg (pWindow pW, short iCnt)
		: DialogWindow (pW, QUERYFIELDDLG),
		  m_sleFieldText (this, IDE_FIELDTEXT),
		  m_cbUseForAll (this, IDCB_USEFORALL)
{
	m_pInBuff = NULL;
	m_iCnt = iCnt;
HEAPCHECK(); }

#pragma warning (default: 4355)

bool CQueryFieldDlg :: FInit (long lONr, bool fUseForAll, LPCSTR pText)
{
// Buffer anlegen
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) return false;

// Caption modifizieren
char *pTemp = new char [_MAX_PATH];

	if (pTemp == NULL) return false; 

	if (GetCaption (m_pInBuff, _MAX_PATH) == NULL)
		ltoa (lONr, m_pInBuff, 10);
	else
		wsprintf (pTemp, m_pInBuff, m_iCnt, lONr);
	SetCaption (pTemp);
	DELETE (pTemp);

	m_cbUseForAll.SetChecked (fUseForAll);
	if (NULL != pText)
		m_sleFieldText.SetText (pText);

HEAPCHECK(); return true;
}

void CQueryFieldDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		m_sleFieldText.GetText (m_pInBuff, _MAX_PATH);
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg();
		break;
		
	case IDCB_USEFORALL:
		break;
	}
}


char *CQueryFieldDlg :: GetFieldText (char *pBuffer, ULONG)
{
	if (!pBuffer || !m_pInBuff) return NULL; 
	
HEAPCHECK(); return strcpy (pBuffer, m_pInBuff);
}

CQueryFieldDlg :: ~CQueryFieldDlg (void)
{
	DELETE (m_pInBuff);
HEAPCHECK(); }

// Funktion, welche aus der Registry das zu verwendende Trennzeichen liest ----
int RetrieveDelimiter (short iMode, char cDefault)
{
#if defined(WIN32)
	if (OBJPROP_DESTMCODE != iMode) return cDefault;

CCurrentUser regUser (g_cbRegConfig);
char cbBuffer[4];
DWORD dwLen = sizeof(cbBuffer)-1;

	if (regUser.GetSubSZ (g_cbDelFeature, cbBuffer, dwLen)) {
		if ('\\' == cbBuffer[0]) switch (cbBuffer[1]) {
		case 't':	cbBuffer[0] = '\t'; break;
		case 'r':	cbBuffer[0] = '\r'; break;
		case 'n':	cbBuffer[0] = '\n'; break;
		case 'b':	cbBuffer[0] = '\b'; break;
		case '\\':	cbBuffer[0] = '\\'; break;
		default:
		case '\0':	cbBuffer[0] = cDefault; break;
		}
		return cbBuffer[0];	// erster Buchstabe gilt
	}
#endif

return cDefault;
}

// Vergleichsfunktion für Shorts (CTree) --------------------------------------
int ShortCmp (void *pObj1, void *pObj2)
{
	return *(short *)pObj1 - *(short *)pObj2;
}


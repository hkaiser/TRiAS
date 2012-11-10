// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.06.99 22:52:21
//
// @doc
// @module Objprop.cxx | Ausgabe von Objekteigenschaften

#include "triaspre.hxx"

///////////////////////////////////////////////////////////////////////////////
// Vergleichsfunktion für Shorts (CTree) 
int ShortCmp (void *pObj1, void *pObj2)
{
	return *(short *)pObj1 - *(short *)pObj2;
}

#if defined(_FORCE_LEGACY_CODE)

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>

#if !defined(WIN16)
#include <registry.hxx>
#include <dirisole.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <PropName.hxx>
#include <ConfigObjectProperty.h>

#include "extmain3.hxx"
#endif // WIN16

#include <istatus.h>
#include <statguid.h>
#include <funcs03.h>

#include "strings.h"
#include "objprop.h"
#include "objprop.hxx"                                          

#include "triasres.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInstance;
#if defined(WIN16)
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

#if _TRiAS_VER >= 0x0300	// ????
#pragma warning(disable: 4273)
int __cdecl lstrcmp (void *p1, void *p2)
{
	return strcmp((char *)p1, (char *)p2); 
}
#pragma warning(default: 4273)
#endif // _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// FunktionsPrototypen 
char *TrimRightAndLeft (char *);
void ReplaceDel (char *pStr);
bool ReplaceDelimiter (char *pStr, char cDel, char cOldDel);
int RetrieveDelimiter (short iMode, char cDefault = '\t');

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProps);
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ConfigObjectProperty);

///////////////////////////////////////////////////////////////////////////////
// spezielles strlen für HUGE-Strings 
#if !defined(WIN16)
inline 
size_t hstrlen (const char *pStr) 
{ 
	return strlen (pStr); 
}
#else
long hstrlen (const char *pStr)
{
char __huge *phStr = (char __huge *)pStr;
size_t iCnt = 0;

	while (*phStr++) 
		iCnt++;
	return iCnt;
}
///////////////////////////////////////////////////////////////////////////////
// HookFunktion für SaveAsDlg 
extern "C"
UINT EXPORTTRIAS CALLBACK ObjPropHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
	if (wMsg == WM_INITDIALOG && Ctl3dEnabled()) 
		Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	// lediglich CTL3D aktivieren

return false;
}
#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// Speicherverwaltung für Zwischenablage 
static char HUGE * WINAPI Alloc (long lCount);
static bool WINAPI Free (char HUGE *pB);
static char HUGE * WINAPI ReAlloc (char HUGE *pB, long lCount);

///////////////////////////////////////////////////////////////////////////////
// Merkmale aus der PBD lesen 
extern "C"
BOOL EXPORTTRIAS WINAPI FillMCodesListBox (long lMCode, BOOL, void *pData)
{
	if (DEX_GetROModeFeature(lMCode))
		return TRUE;		// Objekteigenschaft ist schreibgeschützt, nicht anbieten

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
	if (!strncmp (pbdData.pbdKText, "__", 2))
		return TRUE;	// wirklich interne nicht mit anzeigen

char outBuff[80];

	if (10 == DEX_GetMkBase())
		wsprintf (outBuff, "%08ld:%s", lMCode, pbdData.pbdKText);
	else
		wsprintf (outBuff, "%08lx:%s", lMCode, pbdData.pbdKText);
		
	((ComboBox *)pData) -> AddString (outBuff);

HEAPCHECK(); return true;	// weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor 
#pragma warning (disable: 4355)

#if !defined(WIN16)
ObjectPropertyDlg::ObjectPropertyDlg (
	pWindow pW, ExtensionList *pEL, IEnum<LONG> *pEnumerator, LONG lRefONr)
		   : DialogWindow (pW, ResID (OBJPROPDLG)),
#else
ObjectPropertyDlg::ObjectPropertyDlg (
	pWindow pW, ExtensionList *pEL, LPENUMLONG pEnumerator, LONG lRefONr)
		   : DialogWindow (pW, ResID (OBJPROPDLG)),
		     m_HelpButton (this, IDB_OBJPROPHELP),
#endif // WIN16
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
			 m_pbConfigProp (this, IDB_CONFIGPROPERTY),
		     m_EL (*pEL),
		     m_pObjEnum (pEnumerator)
{
// Controls initialisieren
#if defined(WIN16)
	m_HelpButton.Disable();
#endif // WIN16
	m_pbSortEntries.Disable();
	m_pbConfigProp.Hide();

	m_ClipButton.SetState (true);
	m_HeadLine.SetChecked (true);
	m_Cumulation.SetChecked (true);
	m_Count.SetChecked (true);
	m_ObjPropData.SetChecked (true);

	m_iFileType = 1;	// Default: *.OPR

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin40()) {
	ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		m_pFont = new CVFont (Swiss, Dimension (0, -12), rsArial);
#else
		m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
		if (m_pFont) {
			m_pFont = m_ftHelpText.ChangeFont (m_pFont);
			m_fFontChanged = true;
		} else
			m_fFontChanged = false;
	} else
		m_fFontChanged = false;
#endif // defined(ENABLE_WIN32S_CODE)

// Daten initialisieren
// Zeichenkettenbuffer anlegen
	TX_TRY((m_pBuff = new char [_MAX_PATH], m_pObjPropTree = new ObjPropTreeStr()));
	if (NULL == m_pBuff || NULL == m_pObjPropTree) {
		DELETE_OBJ(m_pBuff);
		db_error (EC_NOMEMORY, RC_ctObjPropDlg);
		HEAPCHECK(); return;
	}

// evtl. ReferenzObjekt besorgen, dazu einfach das erste zu bearbeitende Objekt verwenden
	if (0L == lRefONr && NULL != m_pObjEnum) {
		m_pObjEnum -> Reset(); 
		m_pObjEnum -> Next (1, &lRefONr, NULL);
	}

// ObjPropFuncs initialisieren und Listbox füllen
	COM_TRY {
	ObjectPropertyCreator OPCr (*m_pObjPropTree);
	WObjectProps Props;
	BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

		if (Props.IsValid()) {
		// evtl. alle ObjProps installieren
			Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			THROW_FAILED_HRESULT(Props -> OnNewReferenceObject (lRefONr));
		}

	WEnumObjProps Enum;
	WObjectProperty Prop;

		THROW_FAILED_HRESULT(Props -> EnumObjectProps (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, Prop.ppu(), NULL); /**/) {
		ObjectProperty *pOP = ContCreate(OPCr, ObjectProperty) (Prop);

			if (NULL != pOP) 
				m_ObjProps.AddString (pOP -> pFName());
		}

	} COM_CATCH_NORETURN;


// ComboBox füllen
	m_MCodes.Clear();	// erstmal alles löschen
	
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof(ENUMLONGKEY));
	ELK.eKey = 'm';
	ELK.eFcn = (ENUMLONGKEYPROC)FillMCodesListBox;
	ELK.ePtr = (void*)&m_MCodes;
	DEX_EnumPBDData (ELK);

	if (0 == m_MCodes.GetCount()) {
		m_MCodes.Disable();
		m_MCodeButton.Disable();
	}

HEAPCHECK(); }

#pragma warning (default: 4355)

ObjectPropertyDlg::~ObjectPropertyDlg (void)
{
	DELETE_OBJ (m_pObjPropTree);
	DELETE_OBJ (m_pBuff);

#if defined(ENABLE_WIN32S_CODE)
	if (m_fFontChanged) {
		m_pFont = m_ftHelpText.ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
#endif // defined(ENABLE_WIN32S_CODE)
HEAPCHECK(); }

void ObjectPropertyDlg::ButtonClick (ControlEvt e)
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
		CSaveAsDialog SFDlg (this, (char *)ResString (IDS_OBJPROPFILETEMPLATE, 80).Addr());

#if defined(WIN16)
			SFDlg.SetHookFcn ((HOOKFCN)ObjPropHookFcn);
#else
			if (IsWin40()) {
				SFDlg.AddFlags (OFN_EXPLORER);
#if defined(OFN_ENABLESIZING)
				if (IsWin41() || (IsWinNT() && IsWin50())) {
					SFDlg.AddFlags (OFN_ENABLESIZING);
#if defined(OFN_DONTADDTORECENT)
					SFDlg.AddFlags(OFN_DONTADDTORECENT);
#endif // defined(OFN_DONTADDTORECENT)
				}
#endif // defined(OFN_ENABLESIZING)
			}
			SFDlg.AddFlags (OFN_LONGNAMES);
#endif
			if (!SFDlg.Show()) break;

		int iLen = SFDlg.GetFileNameLen();
		char cbFileName[_MAX_PATH];

			SFDlg.GetFileName (cbFileName, iLen);
			m_iFileType = SFDlg.GetFilterIndex();
			if (m_iFileType <= 0 || m_iFileType > 2)
				m_iFileType = 1;	// default: *.opr

			m_FileName.SetText (cbFileName);
			m_FileButton.SetState (true);
			m_ClipButton.SetState (false);
			m_WindowButton.SetState (false);
			m_MCodeButton.SetState (false);
			m_OKButton.Enable();
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

	case IDB_CONFIGPROPERTY:
		{
		// ObjProp konfigurieren
			if (m_pBuff) {
			CTable t(*m_pObjPropTree);
			short iIndex = m_ObjProps.GetCaretIndex();
				
				if (iIndex == -1) break;
				
				m_ObjProps.GetString (m_pBuff, iIndex, _MAX_PATH);
				if (t.Find (m_pBuff)) {
				ObjectPropertyLock l(t);
				
					if (l) {
						TX_ASSERT(l -> CanConfig());
						l -> ConfigProperty (this);
					}
				}
			}
		}
		break;
	}
HEAPCHECK(); }

void ObjectPropertyDlg::ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_OBJPROP:
		{
			if (m_pObjPropTree == NULL) return;

			m_pObjPropTree -> SetAll();

		char inBuff[OBJPROPFUNCNAMELEN+1];

			for (int iIndex = 0; iIndex < m_pObjPropTree -> Count(); iIndex++) {
			bool isSel = m_ObjProps.GetSelection (iIndex);

				m_ObjProps.GetString (inBuff, iIndex, OBJPROPFUNCNAMELEN);
				m_pObjPropTree -> SetSelection (isSel, inBuff);
			}
			
			if (m_ObjProps.GetNoSelected() > 1)
				m_pbSortEntries.Enable();
			else
				m_pbSortEntries.Disable();

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

					// evtl. Konfiguration ermöglichen
						if (l -> CanConfig())
							m_pbConfigProp.Show();
						else
							m_pbConfigProp.Hide();
					}
				}
			}

		}
		break;
		
	case IDC_OBJPROPMCODES:
		m_FileButton.SetState (false);
		m_ClipButton.SetState (false);
		m_WindowButton.SetState (false);
		m_MCodeButton.SetState (true);
		AdjustControls();
		break;
	}
HEAPCHECK(); }

void ObjectPropertyDlg::AdjustControls (void)
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


void ObjectPropertyDlg::EditChange (ControlEvt e)
{
SingleLineEdit *pSLE = (SingleLineEdit *)e.GetControl();

	if (pSLE -> GetTextLen() > 0) {
		m_ClipButton.SetState (false);
		m_FileButton.SetState (true);
	}
HEAPCHECK(); }

///////////////////////////////////////////////////////////////////////////////
// Properties für ein Objekt zusammenstellen 
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

extern "C" 
BOOL EXPORTTRIAS WINAPI GenerateObjectProperties (long lONr, BOOL, void *pData)
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

///////////////////////////////////////////////////////////////////////////////
// Generieren der ObjektEigenschaften in einer Datei oder in der Zwischenablage
bool ObjectPropertyDlg::GenerateObjProps (short iDest, long lMCode)
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
		
#if defined(WIN16)
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
#endif // WIN16			

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

static 
ULONG CountObjects (IEnum<LONG> *pObjEnum)
{
ULONG ulCnt = 0;	// counter
long lONr = 0;		// dummy

	for (pObjEnum -> Reset(); S_OK == pObjEnum -> Next (1, &lONr, NULL); ulCnt++) 
		;
	return ulCnt;
}

HRESULT ObjectPropertyDlg::ObjPropInitProgress (LPPROGRESSINDICATOR *ppIProgInd)
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
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Installierte ObjPropFuncs 
ObjectProperty::ObjectProperty (IObjectProperty *pIOP)
{
	TX_ASSERT(NULL != pIOP);
	m_ObjProp = pIOP;
	m_isSel = false;
	m_iOrd = 0;
HEAPCHECK(); }

ObjectProperty::ObjectProperty (ObjectProperty &rOP, short iOrd)
{
	m_ObjProp = rOP.m_ObjProp;
	m_strName = rOP.m_strName;
	m_isSel = rOP.m_isSel;
	m_iOrd = iOrd;
HEAPCHECK(); }

ObjectProperty::~ObjectProperty (void)
{
	m_ObjProp.Assign(NULL);
HEAPCHECK(); }

LPCSTR ObjectProperty::pFName() 
{
	if (0 == m_strName.size()) {
		TX_ASSERT(m_ObjProp.IsValid());
		m_strName = CPropertyName(m_ObjProp).GetName();
	}
	return m_strName.c_str();
}

ObjectProperty *ObjectProperty::Insert (ObjectPropertyCreator &rCr, short iOrd)
{
	HEAPCHECK(); return ContCreate (rCr, ObjectProperty) (*this, iOrd);
}

char *ObjectProperty::InvokeFunc (long lONr, char *pBuffer, short iLen)
{
	TX_ASSERT(m_ObjProp.IsValid());
	switch (lONr) {
	case OBJPROP_RESET:
		m_ObjProp -> Reset();
		break;

	case OBJPROP_CUMULATION:
		if (SUCCEEDED(m_ObjProp -> Cumulation (pBuffer, iLen, NULL)))
			return TrimRightAndLeft (pBuffer);
		break;

	case OBJPROP_COUNT:
		return ultoa (m_ObjProp -> Count(), pBuffer, 10);

	default:
		if (SUCCEEDED(m_ObjProp -> Eval (lONr, pBuffer, iLen, NULL)))
			return TrimRightAndLeft (pBuffer);
		break;
	}
	return NULL;
}

char *ObjectProperty::GetHelpText (char *pBuffer, short iLen)
{
	TX_ASSERT(m_ObjProp.IsValid());
	if (SUCCEEDED(m_ObjProp -> HelpInfo (pBuffer, iLen, NULL, NULL)))
		return pBuffer;
	return NULL;
}

bool ObjectProperty::CanConfig()
{
WConfigObjectProperty Cfg;

	return SUCCEEDED(m_ObjProp -> QueryInterface (Cfg.GetIID(), Cfg.ppv()));
}

HRESULT ObjectProperty::ConfigProperty (Window *pWindow)
{
	if (NULL == pWindow)
		return E_POINTER;

WConfigObjectProperty Cfg;

	if (SUCCEEDED(m_ObjProp -> QueryInterface (Cfg.GetIID(), Cfg.ppv()))) 
		return Cfg -> ConfigObjectProperty (pWindow -> Handle(API_WINDOW_HWND));

	return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
// Baum, der die installierten ObjPropFuncs enthält 
ObjPropTree::ObjPropTree (pGetKeyFcn pFGet, pKeyCmpFcn pFCmp)
	     : CTree (pFGet, pFCmp)
{
	// nothing else to do
HEAPCHECK(); }

ObjPropTree::~ObjPropTree (void)
{
	EveryDelete ();
HEAPCHECK(); }

void EXPORTTRIAS ObjPropTree::UserDelete (void *pObj)
{
	((ObjectProperty *)pObj) -> /*ObjectProperty ::*/ ~ObjectProperty();
HEAPCHECK(); }

// Funktionen, die die Selektion einzelner oder aller Elemente richten --------
void ObjPropTree::SetAll (bool fFlag)
{
CTable t (*this);

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (l) l -> SetSelection (fFlag);
	}
HEAPCHECK(); }

void ObjPropTree::SetSelection (bool isSel, char *pFName)
{
CTable t(*this);

	if (t.Find (pFName)) {
	ObjectPropertyLock l(t);

		if (l) l -> SetSelection (isSel);
	}
HEAPCHECK(); }

long ObjPropTree::SelCount (void)
{
CTable t(*this);
long lCnt = 0;

	for (t.First(); t.Valid(); t.Next()) {
	ObjectPropertyLock l(t);

		if (l && l -> isSel()) lCnt++;
	}

HEAPCHECK(); return lCnt;
}

void *GetObjPropKeyStr (void *pObj) { return (void *) ((ObjectProperty *)pObj) -> pFName(); }
void *GetObjPropKeyInt (void *pObj) { return & ((ObjectProperty *)pObj) -> FOrd(); }

ObjPropTreeInt::ObjPropTreeInt (void) : ObjPropTree (GetObjPropKeyInt, ShortCmp) {}
ObjPropTreeStr::ObjPropTreeStr (void) : ObjPropTree (GetObjPropKeyStr, StrCmp) {}

//////////////////////////////////////////////////////////////////////////////
// Speicherverwaltung für Zwischenablage 
static 
char HUGE *WINAPI Alloc (long lCount)
{
HGLOBAL hG = GlobalAlloc (GHND, (DWORD)lCount);

	if (!hG) return NULL;
	
HEAPCHECK(); return (char HUGE *)GlobalLock (hG);
}

static 
bool WINAPI Free (char HUGE *pB)
{
#if defined(WIN16)
HGLOBAL hG = (HGLOBAL)GlobalHandle (HIWORD (pB));
#else
HGLOBAL hG = (HGLOBAL)GlobalHandle (pB);
#endif

	if (!hG || GlobalUnlock (hG)) {
#if !defined(WIN16) && defined(_DEBUG)
	DWORD dwErr = GetLastError();
#endif
		return false;
	}

HEAPCHECK(); return GlobalFree (hG) == NULL;
}

static 
char HUGE * WINAPI ReAlloc (char HUGE *pB, long lCount)
{
#if defined(WIN16)
HGLOBAL hG = (HGLOBAL)GlobalHandle (HIWORD (pB));
#else
HGLOBAL hG = (HGLOBAL)GlobalHandle (pB);
#endif

	if (!hG || GlobalUnlock (hG)) {
#if !defined(WIN16) && defined(_DEBUG)
	DWORD dwErr = GetLastError();
#endif
		return NULL;
	}
	if ((hG = GlobalReAlloc (hG, (DWORD)lCount*2, GMEM_MOVEABLE|GMEM_ZEROINIT)) != 0) {
		HEAPCHECK(); return (char HUGE *)GlobalLock (hG);
	}

HEAPCHECK(); return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Fensterausgabe der Objekteigenschaften 
#pragma warning (disable: 4355)

#if !defined(WIN16)
ObjPropDestWindow::ObjPropDestWindow (pWindow pW, LPCSTR pcText, bool fHeadline)
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
	m_Result.SetExtendedStyle (m_Result.GetExtendedStyle() | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);
#endif 
	InitListViewCtrl (pcText, fHeadline);

HEAPCHECK(); 
}

void ObjPropDestWindow::ButtonClick (ControlEvt e)
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

bool ObjPropDestWindow::InitListViewCtrl (LPCSTR pcText, bool fHeadline)
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

ObjPropDestWindow::ObjPropDestWindow (pWindow pW, char *pText, bool fToLarge)
		   : DialogWindow (pW, OBJPROPDESTWINDOW),
		     m_Result (this, IDE_OBJPROPDESTWINDOW)
{
	if (pText) {
		if (fToLarge) 	// Textlänge begrenzen
			pText[(USHRT_MAX*15L)/16L] = '\0';
		m_Result.SetText (pText);
	}
HEAPCHECK(); }

void ObjPropDestWindow::ButtonClick (ControlEvt)
{
	EndDlg (1);
HEAPCHECK(); }

#endif // WIN16

#pragma warning (default: 4355)

ObjPropDestWindow::~ObjPropDestWindow (void)
{
	// nothing to do
HEAPCHECK(); }

// Dialogfenster zum sortieren der ObjektPropFunktionen -----------------------
ObjPropTree *ObjectPropertyDlg::ResortObjProps (ObjPropTree *pOPT)
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
		DELETE_OBJ (pnewOPT);
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

	DELETE_OBJ (pOPT);
	DELETE_OBJ (pcbFName);

// alle Einträge als selektiert kennzeichnen
	pnewOPT -> SetAll (true);
		
HEAPCHECK(); return pnewOPT;
}


// Eigentliche DialogFunktionen -----------------------------------------------
#pragma warning (disable: 4355)

CSortEntryDlg::CSortEntryDlg (pWindow pW, ObjPropTree *pOPT)
	       : DialogWindow (pW, ResID (SORTOBJPROPDLG)),
		 m_lbEntries (this, IDL_OBJPROPENTRIES),
		 m_pbUp (this, IDC_UP), m_pbDown (this, IDC_DOWN),
		 m_rOPT (*pOPT)
{
// OwnerDraw Knöpfe initialisieren
	if (m_pbUp.LoadBitmaps (IDB_UP, IDB_UP_SEL, IDB_UP_FOCUS, IDB_UP_DISABLED))
		m_pbUp.SizeToContent(); 
	if (m_pbDown.LoadBitmaps (IDB_DOWN, IDB_DOWN_SEL, IDB_DOWN_FOCUS, IDB_DOWN_DISABLED))
		m_pbDown.SizeToContent(); 

HEAPCHECK(); }

#pragma warning (default: 4355)

bool CSortEntryDlg::FInit (void)
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

CSortEntryDlg::~CSortEntryDlg (void)
{
	// nothing to do
HEAPCHECK(); }


void CSortEntryDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg(1);
		break;
		
	case IDCANCEL:
		EndDlg();
		break;
		
	case IDC_DOWN:
		MoveEntry ();
		break;
		
	case IDC_UP:
		MoveEntry (false);
		break;
	}
}

// Zeichenroutinen ------------------------------------------------------------
BOOL CSortEntryDlg::DrawEntireItem (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

BOOL CSortEntryDlg::DrawItemFocus (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

BOOL CSortEntryDlg::DrawItemSelect (DrawItemEvt e)
{
	return m_pbUp.DrawItem(e) || m_pbDown.DrawItem(e);
}

void CSortEntryDlg::MoveEntry (bool fUp)
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
	
	DELETE_OBJ (pEntry);
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

// Funktion, welche aus der Registry das zu verwendende Trennzeichen liest ----
int RetrieveDelimiter (short iMode, char cDefault)
{
#if !defined(WIN16)
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

#endif // defined(_FORCE_LEGACY_CODE)

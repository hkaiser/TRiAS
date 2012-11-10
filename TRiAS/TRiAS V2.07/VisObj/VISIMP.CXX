// Importieren einer VisAscdatei ----------------------------------------------
// File: VISIMP.CXX

#include "visobjp.hxx"

#include <stdio.h>
#include <ctype.h>
#if !defined(WIN32)
#include <ctl3d.h>
#include <commdlg.h>
#endif
	
// #include <protos.h>
#include <stddlg.hxx>

#include <hdrentrx.hxx>
#include <eieruhr.hxx>

#include <strdupx.hxx>

#include "visobj.h"
#include "visimp.h"
#include "resource.h"

#include "visobj.hxx"		// Klasse für diese Erweiterung
#include "visimp.hxx"
#include "vstatus.hxx"

#include "yy2stype.hxx"

#include "cimpview.hxx"		// Baum der Sichten
#include "cimpview.inl"

#include "uidobj.hxx"
#include "uidobj.inl"

// ImportOptionen -------------------------------------------------------------
bool g_fImpHSB = false;			// Eingabe als HSB interpretieren
bool g_fImpDefView = true;		// StandardSicht importieren
bool g_fImpObjVis = true;		// Objektvisualisierung importieren
bool g_fImpViewFeatures = true;		// Sichtmerkmale importieren
bool g_fImpLegInfo = false;		// LegendenInfo importieren
bool g_fImpExistendOnly = true;	// nur existierende Idents importieren

bool g_fDecIdent = true;		// IdentBase
long g_lUIMCode = 0;			// MerkmalsCode des Unique Idents

CStatus *g_pIS = NULL;			// ImportStatusFenster
CImpViewTree *g_pVT = NULL;		// Baum aller Sichten
CUIdentObjects *g_pUIObjs = NULL;	// Baum mit UIdents <--> (lONr's, iOType's)

extern FILE *yy2in;			// Eingabedatei

// Importieren der VisInfo aus einer VisASC-Datei -----------------------------
bool CVisObjExtension :: ImportVisInfo (void) 
{
// EingabeOptionen abfragen
CImportVisInfoDlg IVIDlg (MWind(), &RF());

	if (!IVIDlg.Init()) 	
		return false;	// Fehler bei der Initialisierung
	IVIDlg.Show (Centre);		// Dialogfenster anzeigen

return IVIDlg.Result();
}


extern "C" {

#if !defined(WIN32)
// HookFunktion für den OpenDialog --------------------------------------------
bool _XTENSN_EXPORT CALLBACK VisASCImportHookFcn (HWND hDlg, UINT wMsg, WPARAM, LPARAM)
{
	if (wMsg == WM_INITDIALOG && Ctl3dEnabled()) 
		Ctl3dSubclassDlg (hDlg, CTL3D_ALL);	// lediglich CTL3D aktivieren

return false;
}
#endif // WIN32

}	// extern "C"

// Dialogfenster zur Abfrage der ImportOptionen -------------------------------
#pragma warning (disable: 4355)

CImportVisInfoDlg :: CImportVisInfoDlg (pWindow pW, ResourceFile *pRF)
		   : DialogWindow (pW, ResID (IMPORTVISINFODLG, pRF)),
		     m_pbFName (this, IDB_IMPORTFILESELECT),
		     m_sleFName (this, IDE_IMPORTFILE),
		     m_pbOK (this, IDOK),
		     m_pbAllViews (this, IDB_SELECTALLIMPVIEWS),
		     m_mslbViews (this, IDL_IMPORTVIEWS),
		     m_rbAutoSelect (this, IDR_AUTOSELECT),
		     m_rbRGB (this, IDR_IMPORTRGB),
		     m_rbHSB (this, IDR_IMPORTHSB),
		     m_cbDefaultView (this, IDCB_IMPORTDEFAULTVIEW),
		     m_cbObjVisInfo (this, IDCB_IMPORTOBJVISINFO),
		     m_cbViewFeatures (this, IDCB_IMPORTVIEWFEATURES),
		     m_cbDeleteViews (this, IDCB_DELETEVIEWS),
		     m_cbLegInfo (this, IDCB_IMPORTLEGINFO),
#if defined(WIN32)
			 m_cbExistend (this, IDCB_IMPORTEXISTENTIDENTS),
#endif // WIN32
		     m_rRF (*pRF)
{
	m_pbOK.Disable();
	m_pbAllViews.Disable();
	m_mslbViews.Disable();
	m_cbDefaultView.Disable();
	
	m_rbAutoSelect.SetState (true);
	m_rbRGB.SetState (false);
	m_rbHSB.SetState (false);
	
	m_cbDefaultView.SetChecked (false);
	m_cbObjVisInfo.SetChecked (true);
	m_cbViewFeatures.SetChecked (true);
	m_cbLegInfo.SetChecked (true);
#if defined(WIN32)
	m_cbExistend.SetChecked (true);
#endif // WIN32

	m_cbDeleteViews.SetChecked (false);
	
	m_pBuff = NULL;
	m_pInBuff = NULL;
	
	m_pViews = NULL;	
}

#pragma warning (default: 4355)

bool CImportVisInfoDlg :: Init (void)
{
// temporäre Buffer anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) 
		return false;
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) 
		return false;

return true;
}


CImportVisInfoDlg :: ~CImportVisInfoDlg (void)
{
// Speicher freigeben	
	DELETE_OBJ (m_pBuff);
	DELETE_OBJ (m_pInBuff);
	DELETE_OBJ (m_pViews);
}


void _XTENSN_EXPORT CImportVisInfoDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		CEierUhr Wait (GetParent());
		
			EndDlg (ImportVisAsc ());
		}
		break;
		
	case IDCANCEL:
		EndDlg (false);
		break;
		
	case IDB_SELECTALLIMPVIEWS:
		{
		short iCnt = m_mslbViews.GetCount();
		
			if (iCnt > 0)
				m_mslbViews.ChangeSelected (Range (0, iCnt), true);
		}
		break;
		
	case IDB_IMPORTFILESELECT:
		{
		// EingabeDateiName auswählen
			if (SelectImportFileName()) {	// FName in m_pBuff
			// Datei analysieren, zählen der Identifikatoren
				DELETE_OBJ (m_pViews);
				m_mslbViews.Clear();
								
				m_pViews = AnalyzeVSCFile (m_pBuff);
				if (m_pViews == NULL) 
					break;

			// Listbox füllen
			CTable t(*m_pViews);
			ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);
			
				m_mslbViews.Enable();
				m_pbAllViews.Enable();

				m_cbDefaultView.Disable();
				for (t.First(); t.Valid(); t.Next()) {
				CImpViewLock l(t);
				
					if (!l) continue;
				
				// testen, ob StandardSicht
					if (strcmp (l -> GetViewName(), rsDefault)) 
						m_mslbViews.AddString (l -> GetViewName());
					else {
						m_cbDefaultView.Enable();
						m_cbDefaultView.SetChecked (true);
					}
				}							

			}
		}	
		break;
	}
}

void _XTENSN_EXPORT CImportVisInfoDlg :: EditChange (ControlEvt)
{
	if (m_sleFName.GetTextLen() > 0)
		m_pbOK.Enable();
	else
		m_pbOK.Disable();
}


// Eigentliche ImortRoutine, die VisASC-Datei interpretiert -------------------
bool CImportVisInfoDlg :: ImportVisAsc (void)
{
// Optionen setzen
	g_fImpHSB = m_rbHSB.GetState();
	g_fImpDefView = m_cbDefaultView.isChecked();
	g_fImpObjVis = m_cbObjVisInfo.isChecked();
	g_fImpViewFeatures = m_cbViewFeatures.isChecked();
	g_fImpLegInfo = m_cbLegInfo.isChecked();
#if defined(WIN32)
	g_fImpExistendOnly = m_cbExistend.isChecked();
#endif // WIN32
		
	g_fDecIdent = (DEX_GetIdBase() == 10);	
	g_lUIMCode = GetHeaderMCode (true, IDS_UNIQUEIDENT, 
						IDS_UNIQUEIDENTKTEXT, IDS_UNIQUEIDENTLTEXT);
	g_pVT = m_pViews;
		                                     	
// wenn gefordert, alle Sichten löschen
	if (m_cbDeleteViews.isChecked())
		DeleteOldViews();

// Identifikatoren zählen
short iIndex = m_mslbViews.GetFirstSelected();
short cnIdents = m_pViews -> CountIdents();
CImpView *pV = NULL;

	while (iIndex != -1) {
		m_mslbViews.GetString (m_pBuff, iIndex, _MAX_PATH);
		if (pV = m_pViews -> FFindItem (m_pBuff))
			pV -> Import() = true;
		iIndex = m_mslbViews.GetNextSelected();	// nächste Sicht
	}

// StandardSicht bei Bedarf abziehen
// ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);
// char *pDefault = (char *)rsDefault.Addr();

//	if (!g_fImpDefView && (pV = m_pViews -> FFindItem (pDefault)))
//		cnIdents -= pV -> IdCount();
	
// Datei eröffnen
	m_sleFName.GetText (m_pBuff, _MAX_PATH);
#if !defined(WIN32)
	AnsiToOem (m_pBuff, m_pBuff);
#endif // !WIN32

	yy2in = fopen (m_pBuff, "rt");
	if (yy2in == NULL) return false;

// evtl. aktive Sicht merken
	DEX_GetActiveSight (m_pInBuff);

bool fOldView = (*m_pInBuff != '\0');
	
// eigentliche ImportArbeit
	g_pIS = new CStatus (this, cnIdents, &m_rRF, g_fDecIdent ? 10 : 16);
	if (g_pIS) {
		g_pIS -> SetCaption (ResString (ResID (IDS_IMPORTCAPTION, &m_rRF), 30));
		g_pIS -> SetComment ((char *)ResString (ResID (IDS_IMPORTCOMMENT, &m_rRF), 50).Addr());
		g_pIS -> Show();
	}

bool iResult = InitYY2Parse();	// Datei einlesen

	fclose (yy2in);		// Datei schließen
	DELETE_OBJ (g_pIS);		// Fenster ausblenden

IStorage *pIStorage = NULL;

	if (DEX_GetProjectStorage(pIStorage))
		pIStorage -> Release();
	else
		DEX_FlushModifications();

	DEXN_ReReadIdents();		// alten Zustand löschen
	DEXN_ReReadSights (true);	// Sichten neu einlesen, (Standard aktivieren)
	if (fOldView) {		// alte Sicht wieder einstellen
		DEX_SelectNewSight (m_pInBuff);
//		((CVisObjExtension *)g_pTE) -> RebuildSight();
		DEX_RePaint();
	}
	
return !iResult;
}


// Abfrage des EingabeDateiNamens ---------------------------------------------
bool CImportVisInfoDlg :: SelectImportFileName (void)
{
char *pLocDir = new char [_MAX_PATH];
char *pPath = new char [_MAX_PATH];
char cDrive[_MAX_DRIVE];

	if (DEX_GetActiveProject (pLocDir) == NULL) {
		DELETE_OBJ (pLocDir);
		DELETE_OBJ (pPath);
		return false;
	}
	_splitpath (pLocDir, cDrive, pPath, NULL, NULL);
	_makepath (pLocDir, cDrive, pPath, NULL, NULL);
	DELETE_OBJ (pPath);

// abschließendes '\\' entfernen
char *cptr;

	if (*(cptr = &pLocDir[strlen(pLocDir)-1]) == '\\')
		*cptr = '\0';

// EingabeDateiNamen besorgen
COpenDialog ODlg (this, (char *)(const char *)ResString (
			ResID (IDS_VISASCTEMPLATE, &m_rRF), 50)
		  );

	ODlg.SetInitialDir (pLocDir);
	ODlg.SetCaption (ResString (ResID (IDS_OPENVISCAP, &m_rRF), 128));
#if !defined(WIN32)
	ODlg.SetHookFcn ((HOOKFCN)VisASCImportHookFcn);
#else
	if (IsWin40()) ODlg.AddFlags (OFN_LONGNAMES);
#endif
	ODlg.AddFlags (OFN_HIDEREADONLY|OFN_NOCHANGEDIR);

	if (!ODlg.Show()) {
		DELETE_OBJ (pLocDir);
		return false;
	}
	DELETE_OBJ (pLocDir);

// Eingegebenen DateiNamen lesen und im EditControl ablegen
	if (ODlg.Result()) {
		ODlg.GetFileName (m_pBuff, _MAX_PATH-1);
		m_sleFName.SetText (m_pBuff);
	}

return true;
}

string ViewNameCorrect (LPCSTR pcView)
{
	if (NULL == pcView) return string("");

string str (pcView);
size_t pos = str.find ("\\\"");

	while (NPOS != pos) {
		str.replace (pos, 2, '\"');
		pos = str.find ("\\\"", pos+1);
	}

	pos = str.rfind ('\"');
	str = str.substr (0, pos);
	return str;
}

// EingabeDatei analysieren und Identifikatoren zählen ------------------------
CImpViewTree *CImportVisInfoDlg :: AnalyzeVSCFile (char *pFName)
{
	if (pFName == NULL) return NULL;
#if !defined(WIN32)
	AnsiToOem (pFName, pFName);
#endif
	
FILE *pFile = fopen (pFName, "rt");
char *pTmp = NULL;

	if (pFile == NULL) return 0L;
	
CImpViewTree *pVT = new CImpViewTree;
CImpViewCreator CVCr (*pVT);
CImpView *pV = NULL;

	while ((pTmp = fgets (m_pInBuff, _MAX_PATH, pFile)) != NULL) {
	// erstes Zeichen suchen, daß kein Space ist
	char c = '\0';
	
		while (pTmp) {
			if (!isascii (*pTmp)) return 0L;
			if (!isspace (*pTmp)) break;
			pTmp++;
		}
		if ((c = *pTmp) == '\0') continue;	// nächste Zeile
					
	// SatzTyp feststellen
		switch (tolower (c)) {
		case 'l':	// LinienSatz ?
			if (tolower(*(pTmp+1)) == 'g')
				break;		// LegendenSatz
				
		// sonst duchfallen
		case 'a':	// Flächensatz
		case 'c':	// PunktSatz
		case 'x':	// TextSatz
			if (pV) (pV -> IdCount())++;
			break;	// nächste Zeile

		case 's':	// neue StartAnsicht
		case 'v':	// neue Sicht
			{
				pV = NULL;
				strtok (m_pInBuff, "\"\'");
				
			char *pView = strtok (NULL, "\0");

				if (pView) {
				string strView = ViewNameCorrect (pView);

					OemToAnsi (strView.c_str(), pView);
					pV = ContCreate (CVCr, CImpView)(pView);
				} else {	// StandardSicht
				ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);
				
					pV = ContCreate (CVCr, CImpView)((char *)rsDefault.Addr());
				}
			}
			break;
			
		default:
			if (isdigit (c) && pV) (pV -> IdCount())++;	// DefaultSatz
			break;			
		}
	}
	fclose (pFile);

	CVCr.Insert();			// letzte Sicht wegspeichern
	if (pVT -> Count() == 0) {	// wenn keine Sichten da sind
		DELETE_OBJ (pVT);
	}
	
return pVT;
}


// Löschen aller alten Sichten dieser Datenbasis ------------------------------
extern "C"
BOOL PASCAL _XTENSN_EXPORT FillViewTree (char *pView, BOOL, void *pData)
{
	((CImpViewTree *)pData) -> FAddItem (pView);
	return true;
}

bool CImportVisInfoDlg :: DeleteOldViews (void)
{
// 1. alle Sichten in einem Baum aufsammeln
CImpViewTree *pVT = new CImpViewTree;

	if (!pVT) return false;
	
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillViewTree;
	ENK.ePtr = (void *)pVT;

BOOL iResult = (BOOL)DEX_EnumSights (ENK);

	if (iResult) {	// 2. alle aufgesammelten Sichten löschen
	CTable t(*pVT);
	
		for (t.First(); t.Valid(); t.Next()) {
		CImpViewLock l(t);
		
			if (!l) continue;
			DEX_DeleteSight (l -> GetViewName());
		}
	}

// StandardSicht löschen
ResString rsDefault (ResID (IDS_DEFAULTVIEW, &m_rRF), 40);

	DEX_DeleteSight (rsDefault.Addr());

return iResult;
}


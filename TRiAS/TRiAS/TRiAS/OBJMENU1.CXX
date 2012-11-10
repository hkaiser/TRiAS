// Menuverarbeitungsroutinen fuer ObjektInfoDlgBox ----------------------------
// File: OBJMENU1.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

//#include "merkedit.hxx"
#include "newid.hxx"
#include "objowndr.hxx"
#include "tools.hxx"

#if defined(_FORCE_LEGACY_CODE)
#if !defined(WIN16)
#include "selectid.hxx"
#else
#include "selident.hxx"
#endif // WIN16
#endif // defined(_FORCE_LEGACY_CODE)

#include "triasres.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(OLD_TOOLBOX)
extern ToolWind *pToolBox;
#else
extern int g_iActTool;
#endif // OLD_TOOLBOX

extern ExtDirisWindow *CurrActDirisW;

// Bilden eines KomplexObjektes -----------------------------------------------
void ObjektInfo :: CreateKObject (void)
{
// Objektnummern der anderen selektierten Objekte holen
long lCnt = DEX_ActiveObjectsCount();

// für alle anderen selektierten Objekte KO-Bildung 
long *plObjs = new long [lCnt];

	lCnt = DEX_GetAllActiveObjects (plObjs);  // alle aktiven Objekte holen
	if (lCnt == 0L) {
		DELETE_OBJ (plObjs);
		return;
	}

// KomplexObjekt bilden
long Ident = 90000000L;
long RCode = 10000000L;
long newONr = GetActiveObj();

	for (long iCnt = 0; iCnt < lCnt; iCnt++) {
		DEX_MergeObjects (newONr, newONr, plObjs[iCnt], 
				  Ident, RCode, true)
		if (newONr == -1L)
			break;
	}

long Result;

	DEX_AddNewIdent (Result, Ident, 0, MODIDENT_TYP|ANI_AddToView)	// neuen Ident einhängen
	if (!Result)
		return;

// neuen Eintrag in der ListBox machen
	if (newONr != -1L) 
		RetrieveObjInfo (newONr);

// wieder aufräumen
	DELETE_OBJ (plObjs);
}


// Herauslöschen eines Objektes aus einem Komplexobjekt -----------------------
void ObjektInfo :: DeleteONFromKONr (void)
{
#if 0
// Objektnummern der anderen selektierten Objekte holen
long lCnt = DEX_ActiveObjectsCount();

// für alle anderen selektierten Objekte herauslöschen probieren 
long *plObjs = new long [lCnt];

	lCnt = DEX_GetAllActiveObjects (plObjs);  // alle aktiven Objekte holen
	if (lCnt == 0L) {
		DELETE_OBJ (plObjs);
		return;
	}

// Herauslöschen der Reihe nach
	for (long iCnt = 0; iCnt < lCnt; iCnt++) {
	long ONr = -1L;

		DEX_DeleteONFromKObject (ONr, newONr, plObjs[iCnt])
		if (ONr == 0)	// KObjekt existiert nicht mehr
			break;
		if (ONr != -1L && ONr != newONr) newONr = ONr;
	}

// letztes Objekt aus Komplexobjekt herausgelöst: KO in ListBox löschen
	if (ONr == 0) {
	// Objekt(e) aus ListBox entfernen und Markierung rücksetzen
	int oldIndex = pKurzInfo -> GetCaretIndex ();

		pKurzInfo -> DelItem (oldIndex);
		DeActivateObj();

		if (AssocTextObj != -1L) {
		long iTextIndex = FindObject (AssocTextObj);

			if (iTextIndex != -1) 
				pKurzInfo -> DelItem ((ushort)iTextIndex);
		}
	}

// wieder aufräumen
	DELETE_OBJ (plObjs);
#endif
}

#if defined(_FORCE_LEGACY_CODE)
extern "C"
bool EXPORTTRIAS WINAPI SelectIdentsLB (long lIdent, DWORD dwTypes, void *pData)
{
CSelectIdentDlg *pDlg = (CSelectIdentDlg *)pData;

	if (dwTypes & OTPunkt) 	 pDlg -> SelectIdent (lIdent, OTPunkt);
	if (dwTypes & OTLinie) 	 pDlg -> SelectIdent (lIdent, OTLinie);
	if (dwTypes & OTFlaeche) pDlg -> SelectIdent (lIdent, OTFlaeche);
	if (dwTypes & OTText)	 pDlg -> SelectIdent (lIdent, OTText);
	return true;
}

// RückrufFunktion, die Positionierung des fensters übernimmt -----------------
typedef struct tagDELINFODATA {
	DragRectangleObject *pDRO;
	bool iDelFlag;
} DELINFODATA;

extern "C" POINT WINAPI OICorrectPosition (pWindow pW, void *pData);

bool ObjektInfo::doComplementObjects (void)
{
// Dialog generieren
CSelectIdentDlg *pDlg = NULL;
ErrCode RC;

	{
	CEierUhr Wait  (this);		// kann 'ne Weile dauern
	
#if !defined(WIN16)
		pDlg = CSelectIdentDlg :: CreateInstance (this, 
						IDD_SELECTIDENTSDLG, IDL_IDENTSLIST);
#else
		pDlg = CSelectIdentDlg :: CreateInstance (this, 
						SELECTIDENTSDLG, IDL_IDENTSLIST);
#endif // WIN16
		if (pDlg == NULL) return false;
		
	// Einträge selektieren
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMLONGKEYPROC)SelectIdentsLB;
		ENK.ePtr = pDlg;
		DEXOR_EnumIdentsSelectedEx (Handle(API_WINDOW_HWND), ENK);
	}
	
// Dialog anzeigen und auswerten
	pDlg -> Show();
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait1 (this);
	ObjFeld Objs;
	long lIdent = -1L;
	short iOTyp = 0;
	
	// Alle Objekte der selktieren Einträge aufsammeln
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjects (Objs, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}

	// alle Objekte dieses Fensters wieder entfernen
	short maxIndex = m_pKurzInfo -> LocControl() -> GetCount();
	long lONr = -1L;
		
		for (short i = 0; i < maxIndex; i++) {
			lONr = (long)m_pKurzInfo -> GetItem (i);	// Eintrag holen
			Objs.DeleteObj (lONr);
		}
		
	// Dialogfenster generieren
		if (Objs.Count()) {
		DELINFODATA DID;
		DEXXCREATEOBJEKTINFO crOI;
		Rectangle rc = WindowRect();
		Point pt (rc.Left(), rc.Top());
		DragRectangleObject locDRO (pt, Dimension());
#if defined(OLD_TOOLBOX)
		short actTool = pToolBox ? pToolBox -> iActTool() : NUMARROW;
#else
		short actTool = g_iActTool;
#endif // OLD_TOOLBOX
		
			locDRO.Process (Point (pt.X() + 40, pt.Y() - 40));
		
			DID.pDRO = &locDRO;
			DID.iDelFlag = (actTool == NUMSCHERE);
			
			crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
			crOI.lpCaption = StrDupF (ResString (IDS_COMPLOBJINFO, 30));
			crOI.lcObjs = &Objs;
			crOI.pcMColor = new Color (RED);
			crOI.ppntPos = new Point (-1, -1);
			crOI.fcnPos = (OIPOSPROC)OICorrectPosition;
			crOI.pData = &DID;
		
			RC = DEXX_CreateObjektInfo (crOI) != NULL ? EC_OKAY : WC_RETURN;	// RechercheFenster generieren
		
			if (crOI.ppntPos) delete crOI.ppntPos;
			if (crOI.pcMColor) delete crOI.pcMColor;
			if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben
		}
	}
	DELETE_OBJ(pDlg);
	return RC == EC_OKAY;
}
#endif // defined(_FORCE_LEGACY_CODE)

#if defined(_FORCE_LEGACY_CODE)
bool IsLegalRegisteredVersion (Window *pW, UINT uiCaption);
#endif // defined(_FORCE_LEGACY_CODE)

// Alle selektierten Objekte exportieren --------------------------------------
bool ObjektInfo::doExportObjects (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsLegalRegisteredVersion(this, IDS_LICENCE_EXPORT))
		return false;

ObjFeld Objs;
short maxIndex = m_pKurzInfo -> LocControl() -> GetCount();
	
	{
	CEierUhr (this);
	ObjNummerCreator ONrCr (Objs);

		for (short i = 0; i < maxIndex; i++) {
		long lONr = (long)m_pKurzInfo -> GetItem (i);	// Eintrag holen
		bool isSel = m_pKurzInfo -> GetSelection (i);
							
			if (!isSel) continue;	// nur selektierte Objekte behandeln
			if (ContCreate (ONrCr, ObjNummer)(lONr) == NULL)
				return false;
		}
	}	// letztes Objekt einfügen
	
	return (m_rDBO.doExport (this, NULL, &Objs, GetParent(), true) == EC_OKAY);
#else
	_ASSERTE(FALSE);		// should not be called whatsoever
	return TRUE;
#endif // !defined(_FORCE_LEGACY_CODE)
}

// Vergleichsfunktion für sortieren entsprechend Kriterien --------------------
inline 
int CmpLongs (INT_PTR lONr1, INT_PTR lONr2)
{
register int iResult = 0;

	if (lONr1 > lONr2) iResult = 1;
	else if (lONr1 < lONr2) iResult = -1;

	return iResult;
}

extern "C" 
short EXPORTTRIAS WINAPI CompareObjs (INT_PTR lONr1, INT_PTR lONr2, DWORD dwData)
{
ObjektInfo *pDlg = (ObjektInfo *)dwData;	// zeigt auf ORFenster
short iSort = pDlg -> GetFlags() & ROSortFlags;

// wenn keine SortierInfo gegeben ist, dann auch nur ONrs vergleichen
	if (iSort == 0 || iSort & ROSortObjNr) 
		iSort = RODefaultFlags;

// Identifikatoren vergleichen
	if (iSort & ROSortIdent) {
	INT_PTR lIdent1 = DEX_GetObjIdentEx (lONr1);
	INT_PTR lIdent2 = DEX_GetObjIdentEx (lONr2);
	char cbBuffer1[MAX_OKS_LEN];
	char cbBuffer2[MAX_OKS_LEN];

	// bei Fehler Reihenfolge beibehalten
		if (FAILED(ClassFromIdent(lIdent1, cbBuffer1)))
			return -1;
		if (FAILED(ClassFromIdent(lIdent2, cbBuffer2)))
			return -1;

	short iCmp = strcmp (cbBuffer1, cbBuffer2);

	// bei gleichen Objektklassenschlüsseln, Identifikatoren vergleichen
		if (iCmp == 0) 
			return CmpLongs (lIdent1, lIdent2);
		return iCmp;
	}

// nach ObjektTyp sortieren	
	if (iSort & ROSortObjTyp) {
	short rgOTyp1 = DEX_GetObjectType (lONr1);
	short rgOTyp2 = DEX_GetObjectType (lONr2);
	
		return rgOTyp1 - rgOTyp2;
	}
	
// nach anzuzeigendem Text sortieren
CTable t(pDlg -> OITree());
char *pText1 = NULL;
char *pText2 = NULL;

	if (t.Find (&lONr1)) {
	ObjInfoItemLock l(t);
	
		if (l) pText1 = l -> PropText();
	}
	if (t.Find (&lONr2)) {
	ObjInfoItemLock l(t);
	
		if (l) pText2 = l -> PropText();
	}
	if (pText1 && pText2) {
	short iCmp = strcmp (pText1, pText2);

		if (iCmp) return iCmp;

	// wenn Texte gleich sind, Objektnummern vergleichen
	}
	return CmpLongs (lONr1, lONr2);		// ansonsten Objekte vergleichen
}


////////////////////////////////////////////////////////////////////////////
// Diverse Hilfsfunktionen
// File : DATAHELP.CXX
///////////////////////////////////////////////////////////////////////////

#include "kompp.hxx"
#include "kompaktr.h"

#include <shellapi.h>

#include <oleguid.h>
#include <dirisole.h>
// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>


#include <hdrentrx.hxx>
#include "kompdef.h"
#include <xtsnaux.hxx>
#include <igeometr.hxx>

#include "triasdec.h"
#include "triasdef.h"
#include "kompdll.hxx" 
#include "kompwin.hxx"
#include "komphead.hxx"
#include "kompgew.hxx"
#include "gewbaum.hxx"

#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "kpstatus.hxx"

#include "version.h"
#include "kompcls.hxx"
#include "kompias.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG && WIN32

/////////////////////////////////////////////////////////////////////////////
//	Liefern logische Werte für ObjectType ( OT_... zu OT...)
short LogObjectType ( long ONr ) 
{
short TstGiTyp = -1;

	short Status = DEX_GetObjectType (ONr);

//--------------Zuordnung----------------------------
	if ( Status == OGPunkt ) TstGiTyp = OTPunkt;
	if ( Status == OGLinie ) TstGiTyp = OTLinie;
	if ( Status == OGFlaeche ) TstGiTyp = OTFlaeche;
	if ( Status == OGText ) TstGiTyp = OTText;
	if ( Status == OGKO ) TstGiTyp = OTKO;
	if ( Status == OGSachObjekt ) TstGiTyp = OTSachObjekt;
	return TstGiTyp ;
}
/////////////////////////////////////////////////////////////////////////////
// ObjektContainer /////////////////////////////////////////////////////////
long *ObjectContainer ( long ONr, short iObjTyp )
{

long *pCont = new long[4];
	if ( pCont == NULL )
		return NULL;

long X,Y;

	if ( iObjTyp == OT_TEXT) {
		OBJGEOMETRIE OG;
		memset (&OG,'\0',sizeof(OBJGEOMETRIE));
 		OG.dwSize = sizeof(OBJGEOMETRIE);

		OG.lONr = ONr;
		OG.lCnt = 1;
		OG.pdblX = &X;
		OG.pdblY = &Y;
		OG.iFlags &= ~OGConverted;

		if (DEX_GetObjGeometrie (OG)) {
			*pCont = X;
			*(pCont+1) = X;
			*(pCont+2) = Y;
			*(pCont+3) = Y;
		}
	} else {
	// vorher Objektcontainer definieren-----------------------------------
		long CONT[4];
		DEX_GetObjContainer ( ONr, CONT[0]);
		*pCont = CONT[0];
		*(pCont+1) = CONT[1];
		*(pCont+2) = CONT[2];
		*(pCont+3) = CONT[3];

	}
	return pCont;

}
//////////////////////////////////////////////////////////////////////////////
// RechercheStatus abfragen -----------------------------------------------
bool isSelected (HWND hWnd, LONG lONr)
{
RECHOBJECT ro;

	INITSTRUCT (ro, RECHOBJECT);
	ro.lONr = lONr;
        DEXOR_QueryRechercheStatus (hWnd, ro);

	if (!(ro.iFlags & RSListed)) 
		return false;		// nicht in ORFenster

// RechercheStatusprüfen
	if (!(ro.iFlags & RSSelected))
		return false;		// nicht selektiert

return true;

}
//////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Konvertierung der Real-Koordinaten dX und dY in Datenbank-Koordinaten
void RealInDBKoord (double dX, double dY, KoOrd& PX, KoOrd& PY, CoordTransX* pCT)
{
// 1. Schritt: Umwandlung der Real-Koordinaten dX und dY in ASC-Format
	pCT -> InvTransform (&dX, &dY);

// 2. Schritt: Umwandlung des ASC-Format in DB-Koordinaten (unter Einbeziehung der Skalierung)
	pCT -> Scale (dX, dY, &PX, &PY);
} // RealInDBKoord
/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//////////////////       Original - Wolfgang //////////////////////
///////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Transformationsfaktor (Rückgabewert) berechnen, mit dessen Hilfe ein in Metern vorgegebener
// Eingabewert in x- bzw. y-Richtung multipliziert werden muß, um auf Datenbank-Verhältnisse zu
// kommen; die Berechnung wird für den Bereich durchgeführt, der in dem durch P1 und P2
// aufgespannten Container liegt
DoublePair UmrechnungsFaktor (Punkt& P1, Punkt& P2, CoordTransX* pCT)
{

KoOrd XMin, XMax, YMin, YMax;

#if _MSC_VER >= 1100
	KoOrd X1,X2,Y1,Y2;
	X1 = P1.GetX();
	X2 = P2.GetX();

	if (X1 < X2)
	{
		XMin =  X1;
		XMax = X2;
	}
	else
	{
		XMin = X2;
		XMax = X1;
	}

	Y1 = P1.GetY();
	Y2 = P2.GetY();

	if (Y1 < Y2)
	{
		YMin = Y1;
		YMax = Y2;
	}
	else
	{
		YMin = Y2;
		YMax = Y1;
	}

#else

	if (P1.X() < P2.X())
	{
		XMin = P1.X();
		XMax = P2.X();
	}
	else
	{
		XMin = P2.X();
		XMax = P1.X();
	}

	if (P1.Y() < P2.Y())
	{
		YMin = P1.Y();
		YMax = P2.Y();
	}
	else
	{
		YMin = P2.Y();
		YMax = P1.Y();
	}


#endif // _MSC_VER >= 1100
	
	double dXMin, dYMin, dXMax, dYMax;	// Real-Koordinaten

	pCT -> UnScale (XMin, YMin, &dXMin, &dYMin);	// DB-Koordinaten in ASC-Format transformieren
	pCT -> UnScale (XMax, YMax, &dXMax, &dYMax);	//  (incl. rausrechnen der internen Skalierung)

DoublePair DP1 (dXMin, dYMax);	// linker oberer Punkt des durch P1 und P2 aufgespannten Containers
double dBreite = 0;	// Containerbreite und
double dHoehe = 0;	// Containerhöhe in Meter
double dUFX, dUFY;	// Umrechnungsfaktor in x- bzw. y-Richtung

	if (dXMax > dXMin)
	{
	DoublePair DP2 (dXMax, dYMax);	// rechter oberer Punkt

		dBreite = pCT -> CoordTransDistance (&DP1, &DP2);
		if ( dBreite != 0.0)
			dUFX = ((double)XMax - XMin) / dBreite;
		else
			dUFX = 0.0;
	}

	if (dYMax > dYMin)
	{
	DoublePair DP3 (dXMin, dYMin);	// linker unterer Punkt

		dHoehe = pCT -> CoordTransDistance (&DP1, &DP3);
		if ( dHoehe != 0.0 )
			dUFY = ((double)YMax - YMin) / dHoehe;
		else
			dUFY = 0.0;
	}

	// mindestens 1 Containerseite = 0, dann den in dieser Richtung 100 m entfernt liegenden Punkt
	// ermitteln und mit dessen Hilfe die Umrechnungsfaktoren bestimmen
	if (dBreite == 0 || dHoehe == 0)
	{

	double cs = 0.0;

#if _MSC_VER >= 1100

	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	// COORDSCALING-Wert aus Datenbank-Header (1.0 für den Fall, daß Eintrag fehlt)
	cs = HeaderEntryX (ResString (ResID(IDS_COORDSCALING, &g_pTE->RF()), 17),m_hPr).EntryDouble(1.0);
#else
	// COORDSCALING-Wert aus Datenbank-Header (1.0 für den Fall, daß Eintrag fehlt)
	cs = HeaderEntryX (ResString (ResID(IDS_COORDSCALING, &g_pTE->RF()), 17)).EntryDouble(1.0);
#endif

	DoublePair DP4 (100.*cs, 100.*cs);	// Differenzwerte in x- bzw. y-Richtung
	DoublePair HP;  // Hilfspunkt, der in x- und y- Richtung 100 m entfernt liegt,
					// für Ermittlung der Umrechnungsfaktoren in unskalierten Koordinaten
	Punkt HPS;      // Hilfspunkt mit skalierten Koordinaten

		pCT -> CoordTransRectangle (&DP1, &DP4, &HP);			// Berechnung von HP


#if _MSC_VER < 1100

		RealInDBKoord (HP.X(), HP.Y(), HPS.X(), HPS.Y(), pCT);	// Skalierung von HP -> HPS
#else
//		KoOrd X = HPS.GetX();
//		KoOrd Y = HPS.GetY();

		KoOrd X;
		KoOrd Y;
		KoOrd& PX = X;
		KoOrd& PY = Y;

		RealInDBKoord (HP.X(), HP.Y(), PX, PY, pCT);	// Skalierung von HP -> HPS
		HPS.SetX (PX);
		HPS.SetY (PY);

#endif // _MSC_VER < 1100

		if (dBreite == 0)

#if _MSC_VER < 1100
			dUFX = ((double)HPS.X() - XMin) / 100.;
#else
			dUFX = ((double)HPS.GetX() - XMin) / 100.;
#endif // _MSC_VER < 1100

		if (dHoehe == 0)

#if _MSC_VER < 1100
			dUFY = ((double)HPS.Y() - YMax) / 100.;
#else
			dUFY = ((double)HPS.GetY() - YMax) / 100.;
#endif // _MSC_VER < 1100

	}

	return DoublePair (dUFX, dUFY);
} // UmrechnungsFaktor

//////////////////////////////////////////////////////////////////////////
//------------------- EXTERN - C --------------------------------------------
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT DeleteKompaktClass ( long Ident, Bool , void *pData)
  {


	char NewIdent[MAX_OKS_LENX+1];

#if _MSC_VER < 1100
	ClassFromIdentX ( Ident, NewIdent);
#else
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if ( hPr != m_hPr)
		return true;

	ClassFromIdentX ( hPr,Ident, NewIdent);
#endif
	
	long lOIdent =  (cSensibilitaetsStufe + 1) * 1000L;
	long lUIdent =  (cLeistungenUnterhaltung ) * 1000L;


	if ( strlen(NewIdent) != 4) {

/*------------ Korr. 15.3.98 : Leistungen bleiben
		if (strlen(NewIdent) != 6) {
			return true;
		} else {
			NewIdent[4] = '\0';
		}
-----------------------------------------------*/
		return true;
	}

	long RefIdent = atol(NewIdent+1);	
	
	if ( lOIdent > RefIdent && lUIdent < RefIdent)
		DEX_DeleteAllIdentObjects(Ident);
	return true;
  }

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheFlaechen (long Ident, DWORD Type , void *pData)
{
	long lIdent = (( OBJCLSRECHERCHE *)pData)->lIdent;
	MultiSelListBox *p = (( OBJCLSRECHERCHE *)pData)->pListBox;

#if _MSC_VER < 1100

	if ( Ident == lIdent)
		return true;
#else
	HPROJECT hPr1 = DEX_GetObjectsProject(Ident);
	HPROJECT hPr2 = DEX_GetObjectsProject(lIdent);
	if ( Ident == lIdent && hPr1 == hPr2)
		return true;
#endif

	PBDDATA pbdData;
	char KText[TEXTLEN+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

#if _MSC_VER < 1100
	DEX_GetPBDData (pbdData);
#else
	DEX_GetPBDDataEx (hPr1,pbdData);
#endif


char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&g_pTE->RF()),70));
	KText[TEXTLEN] = '\0';

	ulong ulIdent = (ulong) Ident;
	char NewIdent [MAX_OKS_LENX + 1];

#if _MSC_VER < 1100
	ClassFromIdentX ( ulIdent, NewIdent);

	wsprintf (outBuff, "%s:%s", NewIdent, KText);

	p -> AddString (outBuff);
#else
	ClassFromIdentX ( hPr1,ulIdent, NewIdent);
	wsprintf (outBuff, "%s:%s", NewIdent, KText);

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		char cbBuffer[_MAX_PATH];
			TX_ASSERT(NULL != hPr1);
			if (NULL != DEX_GetDataSourceShortName (hPr1, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
	}

	// Ident am jeweiligen Item speichern
	int iIndex = p -> AddString (outBuff);
	p -> SetItemData (iIndex, Ident);

#endif


	return TRUE;

}
//---------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FillIDListBox (long Ident, Bool , void *pData)
{


	ulong ulIdent = (ulong) Ident;
	char NewIdent [ MAX_OKS_LENX + 1];

#if _MSC_VER < 1200
	ClassFromIdentX ( ulIdent, NewIdent);
#else

	HPROJECT hPro = DEX_GetObjectsProject(ulIdent);

	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if ( hPr != hPro)
		return true;

	ClassFromIdentX ( hPro, ulIdent, NewIdent);
#endif


	PBDDATA pbdData;
	char KText[TEXTLEN+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	
	{

//	ErrInstall EI ( EC_INVADDR);
	ErrInstall EI ( WC_NOIDENT);

#if _MSC_VER < 1200
	if ( DEX_GetPBDData (pbdData) != EC_OKAY)
		return true;
#else
	if ( DEX_GetPBDDataEx (hPro,pbdData) != EC_OKAY)
		return true;
#endif


	char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&g_pTE->RF()),70));
	KText[TEXTLEN] = '\0';

	wsprintf (outBuff, "%s:%s", NewIdent, KText);

#if _MSC_VER < 1200
	((ListBox *)pData) -> AddString (outBuff);
#else
	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPro);
			if (NULL != DEX_GetDataSourceShortName (hPro, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
	}

	// Ident am jeweiligen Item speichern
	int iIndex = ((ListBox *)pData) -> AddString (outBuff);

	((ListBox *)pData) -> SetItemData (iIndex, Ident);
#endif // _MSC_VER < 1200


	}

	return TRUE;

}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FillOKSListBox (long Ident, Bool , void *pData)
{


	ulong ulIdent = (ulong) Ident;
	char NewIdent [ MAX_OKS_LENX + 1];

#if _MSC_VER < 1200
	ClassFromIdentX ( ulIdent, NewIdent);
#else

	HPROJECT hPro = DEX_GetObjectsProject(ulIdent);

	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if ( hPr != hPro)
		return true;

	ClassFromIdentX ( hPro, ulIdent, NewIdent);
#endif

	TR_OKSTree *pOKS = ( TR_OKSTree *) pData;

	CTable t (*pOKS);

	char *pNewID = new char [_MAX_PATH];
	if (pNewID)
		wsprintf(pNewID,"%s",NewIdent);
	else
		return true;

//	MessageBox (__hWndM ,pNewID,"Klasse",MB_OK);

	if (!t.Find(pNewID)) {
		TR_OKSCreator OCr (*pOKS);
		ContCreate (OCr,TR_OKS) (pNewID, ulIdent);
	} else {
		TR_OKSLock l(t);
		l->StoreSecondIdent(ulIdent);
//		MessageBox (__hWndM ,pNewID,"Doppelte Klasse",MB_OK);
	}

	DELETE_OBJ(pNewID);

	return TRUE;

}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FillFullIDListBox (long Ident, Bool , void *pData)
{


	ulong ulIdent = (ulong) Ident;
	char NewIdent [ MAX_OKS_LENX + 1];

#if _MSC_VER < 1200
	ClassFromIdentX ( ulIdent, NewIdent);
#else

	HPROJECT hPro = DEX_GetObjectsProject(ulIdent);

	ClassFromIdentX ( hPro, ulIdent, NewIdent);
#endif


	PBDDATA pbdData;
	char KText[TEXTLEN+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	
	{

//	ErrInstall EI ( EC_INVADDR);
	ErrInstall EI ( WC_NOIDENT);

#if _MSC_VER < 1200
	if ( DEX_GetPBDData (pbdData) != EC_OKAY)
		return true;
#else
	if ( DEX_GetPBDDataEx (hPro,pbdData) != EC_OKAY)
		return true;
#endif


	char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&g_pTE->RF()),70));
	KText[TEXTLEN] = '\0';

	wsprintf (outBuff, "%s:%s", NewIdent, KText);

#if _MSC_VER < 1200
	((ListBox *)pData) -> AddString (outBuff);
#else
	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		char cbBuffer[_MAX_PATH];

			TX_ASSERT(NULL != hPro);
			if (NULL != DEX_GetDataSourceShortName (hPro, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
	}

	// Ident am jeweiligen Item speichern
	int iIndex = ((ListBox *)pData) -> AddString (outBuff);

	((ListBox *)pData) -> SetItemData (iIndex, Ident);
#endif // _MSC_VER < 1200


	}

	return TRUE;

}
//---------------------------------------------------------------------

//---------------------------------------------------------------------
/*------------------
extern "C" BOOL PASCAL _XTENSN_EXPORT SucheMerkmalsKode (long Mkode, Bool , void *pData)
{
	MERKMALSDEFINITION *m = (MERKMALSDEFINITION *)pData;

PBDDATA pbdData;
char KText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = Mkode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	if ( strcmp (KText, m->pNummer) == 0 )
		m->lNummer = (ulong) Mkode;
	if ( strcmp (KText, m->pName) == 0 )
		m->lName = (ulong) Mkode;

	return TRUE;

}
----------------------------------*/
//---------------------------------------------------------------------------
//-----Idents pro GewCode-Merkmal--------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheKompaktKlassen ( long Ident, Bool , void *pData)
  {

	TR_OCLTree *pKPKL = (( GEWAESSERKLASSE *) pData)->pTRGew;
	ulong lIDCode = ((GEWAESSERKLASSE *)pData)->lGewCode;
	short iTyp = ((GEWAESSERKLASSE *)pData)->iTyp;


#if _MSC_VER >= 1100

	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();


// KK991129
	// Gewässer und Bauwerke nur in gleicher Datenquelle
	if ( iTyp != PM_HYDRAULIK && iTyp != PM_FLAECHEN) {
		if (m_hPr != hPr)
			return true;
	}
	
	if ( m_hPr != hPr ) {
		ResString StrH (ResID(IDS_HYDRAULIKCODE,&g_pTE->RF()),60);
		ResString StrF (ResID(IDS_FLAECHENCODE,&g_pTE->RF()),60);
		if ( iTyp == PM_FLAECHEN)
			lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrF.Addr());
		else
			lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrH.Addr());
	
	}

	if ( 0L == lIDCode)
		return true;

#endif

	CTable t ( *pKPKL);

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

	*pBuff = '\0';


#if _MSC_VER >= 1100


TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long)lIDCode;		// MerkmalsCode


	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( NULL == DEX_GetTextMerkmal ( tm )) {

#if _MSC_VER >= 1100

	// Abgleich für Bauwerke
		
		if ( iTyp == PM_BAUWERKE) {
			if (!StoreBauwIdentFeature (Ident,lIDCode)) {	// Hier : BW Code in OKS verglichen
				DELETE_OBJ (pBuff);
				return true;
			}
		} else {
			DELETE_OBJ (pBuff);
			return true;
		}
#else
		DELETE_OBJ (pBuff);
		return true;

#endif
	}
	}


	DELETE_OBJ (pBuff);
	if ( iTyp == PM_BAUWERKE) {
		long Number = 0L;

		ENUMLONGKEY ELK;
		memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
		ELK.eFcn = ( ENUMLONGKEYPROC) MindestensEinObjekt;
		ELK.eKey = Ident;
		ELK.ePtr = &Number;
		DEX_EnumIdentObjects(ELK);


// Prüfen , ob Ident wirklich belegt

		if ( Number == 0L) {
			
			tm.lTarget = Ident;		// ObjektKlasse
			char *pMText = new char [_MAX_PATH];
			if ( pMText ) {
				ResString Str (ResID(IDS_EREIGNISDATEN,&g_pTE->RF()),60);
				strcpy ( pMText, Str.Addr());
				tm.imaxLen = strlen (pMText);
				tm.pMText = pMText;		// Puffer
//				DELETE_OBJ(pMText);
			}
			tm.iTTyp = TT_Identifikator;
			tm.lMCode = (long)lIDCode;		// MerkmalsCode
			DEX_ModTextMerkmal ( tm );
			DELETE_OBJ(pMText);
			return true;
		}
	}

	if ( !t.Find ( &Ident )) {
		long MCode = 0L;
		TR_OCLCreator TRCr ( *pKPKL);
		ContCreate ( TRCr, TR_OCL) ( Ident, MCode,OC_ANLEGEN, NULL);

	}

	return true;
  }

////////////////////////////////////////////////////////////////////////
extern "C"  Bool PASCAL _XTENSN_EXPORT StoreBauwIdentFeature ( long Ident,ulong lIDCode) 
{

	char *pMText = new char [_MAX_PATH];
	if ( !pMText)
		return false;

	*pMText = '\0';
	strcat(pMText ,"16");

	char NewIdent[MAX_OKS_LENX+1];

#if _MSC_VER >= 1100

	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (m_hPr != hPr)
		return true;

	ClassFromIdentX ( hPr,Ident, NewIdent);


	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;


#else

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif


	long RefIdent = atol(NewIdent+1);	
	RefIdent = RefIdent/1000L;
	if ( (short)RefIdent != cBauwerkeIdent) 
		return false;

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Identifikator;

	tm.lMCode = (long) lIDCode;		// MerkmalsCode

	DEX_ModTextMerkmal ( tm );
	
	DELETE_OBJ ( pMText);
	return true;

}
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//-----Idents pro BauwCode-Merkmal fuer EinzelGewaesser --------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwEinzelKlassen ( long Ident, Bool , void *pData)
  {

	TR_OCLTree *pKPKL = (( GEWAESSERKLASSE *) pData)->pTRGew;
	ulong lIDCode = ((GEWAESSERKLASSE *)pData)->lGewCode;
	ulong lGewNrCode = ((GEWAESSERKLASSE *)pData)->lGewNrCode;
	char *pGewNr = ((GEWAESSERKLASSE *)pData)->pGewNr;

	if ( !pKPKL || !pGewNr || lIDCode == 0L || lGewNrCode == 0L)
		return false;

	CTable t ( *pKPKL);

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (m_hPr != hPr)
		return true;

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long)lIDCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		char NewIdent[MAX_OKS_LENX+1];

		ClassFromIdentX ( hPr,Ident, NewIdent);

		long RefIdent = atol(NewIdent+1);	
		RefIdent = RefIdent/1000L;
		if ( (short)RefIdent != cBauwerkeIdent) {
			DELETE_OBJ ( pBuff);
			return true;
		}
	}
	}

	DELETE_OBJ ( pBuff);


	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) SucheEinzelBauwerke;
	ELK.eKey = Ident;

	OBJEKTKLASSENTYP OT;
	OT.iTyp = OTLinie | OTPunkt;
	OT.lMCode = lGewNrCode;
	OT.pMWert = pGewNr;
	TR_OBJTree *pOBJ = new TR_OBJTree;
	OT.pOBJ = pOBJ;
	ELK.ePtr = &OT;

	DEX_EnumIdentObjects(ELK);


// Prüfen , ob Ident wirklich belegt
	if ( pOBJ->Count() == 0L) {
		DELETE_OBJ ( pOBJ);
		return true;
	}

	if ( !t.Find ( &Ident )) {
		long MCode = 0L;
		TR_OCLCreator TRCr ( *pKPKL);
		ContCreate ( TRCr, TR_OCL) ( Ident, MCode,OC_ANLEGEN, pOBJ);

	}

	return true;
  }
////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
//-----Idents pro BauwCode-Merkmal--------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwKlassen ( long Ident, Bool , void *pData)
  {

	TR_OCLTree *pKPKL = (( GEWAESSERKLASSE *) pData)->pTRGew;
	ulong lIDCode = ((GEWAESSERKLASSE *)pData)->lGewCode;

	CTable t ( *pKPKL);

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (m_hPr != hPr)
		return true;

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long)lIDCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ ( pBuff);
		return true;
	}
	}

	DELETE_OBJ ( pBuff);

	long Number = 0L;

	ENUMLONGKEY ELK;
	memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
	ELK.eFcn = ( ENUMLONGKEYPROC) MindestensEinObjekt;
	ELK.eKey = Ident;
	ELK.ePtr = &Number;
	DEX_EnumIdentObjects(ELK);


// Prüfen , ob Ident wirklich belegt
	if ( Number == 0L) {
		tm.lTarget = Ident;		// ObjektKlasse
		tm.imaxLen = NULL;
		tm.pMText = NULL;		// Puffer
		tm.iTTyp = TT_Identifikator;
		tm.lMCode = (long)lIDCode;		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );
		return true;
	}

	if ( !t.Find ( &Ident )) {
		long MCode = 0L;
		TR_OCLCreator TRCr ( *pKPKL);
		ContCreate ( TRCr, TR_OCL) ( Ident, MCode,OC_ANLEGEN, NULL);

	}

	return true;
  }
////////////////////////////////////////////////////////////////////////////
extern "C"  Bool PASCAL _XTENSN_EXPORT MindestensEinObjekt ( long lONr, Bool , void *pData)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( lONr == -1L || lONr == 0L)
		return true;

	if ( DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE || OS.iObjTyp == OT_PUNKT) {
			(* (long *)pData)++;
			return false;
		}
	}
	return true;

}
////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumeriereObjekte ( long lONr, Bool , void *pData)
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;
	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_FLAECHE || OS.iObjTyp == OT_KANTE || OS.iObjTyp == OT_PUNKT) 
			(* (long *)pData)++;
	}
	return TRUE;

}
//---------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////
extern "C"  Bool PASCAL _XTENSN_EXPORT ModifiziereObjekte ( long lONr, Bool , void *pData)
{

	ulong lMCodeV1 = ((MERKMALSWECHSEL *)pData)->lMCodeV1;
	ulong lMCodeV2 = ((MERKMALSWECHSEL *)pData)->lMCodeV2;
	ulong lMCodeZ1 = ((MERKMALSWECHSEL *)pData)->lMCodeZ1;
	ulong lMCodeZ2 = ((MERKMALSWECHSEL *)pData)->lMCodeZ2;

	if (!lMCodeV1 )
		return false;

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;
	if ( OS.lONr == -1L || OS.lONr == 0L || !DEX_GetObjStatistik (OS) ) 
		return TRUE;
		
	
	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)lMCodeV1;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm ))
		return true;
	}

	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)lMCodeZ1;		// MerkmalsCode
	if ( lMCodeZ1 ){
		DEX_ModTextMerkmal ( tm );

		tm.imaxLen = _MAX_PATH;
		tm.pMText =NULL;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)lMCodeV1;		// MerkmalsCode
		DEX_ModTextMerkmal ( tm );

	}
//-----------Next
	if (!lMCodeV2 || !lMCodeZ2)
			return true;

	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)lMCodeV2;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( DEX_GetTextMerkmal ( tm )) {

		tm.imaxLen = _MAX_PATH;
		tm.pMText =pBuff;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)lMCodeZ2;		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );

		tm.imaxLen = _MAX_PATH;
		tm.pMText =NULL;		// Puffer
		tm.iTTyp = TT_Objekt;
		tm.lMCode = (long)lMCodeV2;		// MerkmalsCode

		DEX_ModTextMerkmal ( tm );
	}

	}

	DELETE_OBJ ( pBuff);
	return TRUE;

}
//---------------------------------------------------------------------------
//-----Idents pro GewCode-Merkmal--------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheGewaesserKlassen ( long Ident, Bool , void *pData)
  {

	TR_OCLTree *pTRGew = (( GEWAESSERKLASSE *) pData)->pTRGew;
	ulong lIDCode = ((GEWAESSERKLASSE *)pData)->lGewCode;

	CTable t ( *pTRGew);

	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;


#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(Ident);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if (hPr != m_hPr)
		return true;

	TARGETMERKMALEX tm;
	memset (&tm, '\0', sizeof(TARGETMERKMALEX));
	
	tm.dwSize = sizeof(TARGETMERKMALEX);
	tm.pcView = KompaktDefaultVisInfo;

#else
	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
#endif

	tm.lTarget = Ident;		// ObjektKlasse
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Identifikator;
	tm.lMCode = (long)lIDCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm ))
		return true;
	}

	DELETE_OBJ ( pBuff);

	if ( !t.Find ( &Ident )) {
		long MCode = 0L;
		TR_OBJTree *pOBJ = new TR_OBJTree;
		if (!pOBJ)
			return true;

		OBJEKTKLASSENTYP OT;
		OT.iTyp = OTLinie;

		ENUMLONGKEY ELK;
		memset (&ELK,'\0',sizeof(ENUMLONGKEY) );
		ELK.eFcn = ( ENUMLONGKEYPROC) SucheGewaesserObjekt;
		ELK.eKey = Ident;
//		ELK.ePtr = pOBJ;
		OT.pOBJ = pOBJ;
		ELK.ePtr = &OT;
		DEX_EnumIdentObjects(ELK);

		if ( pOBJ->Count() == 0 ) {
			DELETE_OBJ ( pOBJ);
			return true;
		}

		TR_OCLCreator TRCr ( *pTRGew);
		ContCreate ( TRCr, TR_OCL) ( Ident, MCode,OC_DEFINIEREN, pOBJ);

	}

	return true;
  }


//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FindeTempObjekt ( long lONr, Bool , void *pData)
  {

	short Status = DEX_GetObjectType (lONr);

	if ( Status == OGText ) {
		if ( ((CKompiasExtension *)g_pTE)->ObjektIstGewaesser(lONr))
			return TRUE;
	}

	TR_OBJTree *pObj = (TR_OBJTree *)pData;

	
	CTable t(*pObj);

	if ( !t.Find ( &lONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
	}

	return TRUE;
		
  }
//---------------------------------------------------------------------------

//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT FindeEinzelObjekt ( long Object, Bool , void *pData)
  {
	long lMCode = ((MERKMALSRECHERCHE *)pData)->lMCode;
	long *pObj = ((MERKMALSRECHERCHE *)pData)->pObj;
	LPSTR pMWert = ((MERKMALSRECHERCHE *)pData)->pMWert;
	TR_OCLTree *pClass = ((MERKMALSRECHERCHE *)pData)->pClass;
	
	long lIdent = DEX_GetObjIdent(Object);
	CTable t (*pClass);

	if (!t.Find(&lIdent))
		return true;

	char * pPuffer = new char [_MAX_PATH];
	if ( !pPuffer)
		return true;
	*pPuffer = '\0';

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		// Puffer
	tm.iTTyp = TT_Objekt;
	DEX_GetTextMerkmal (tm);

	if ( *pPuffer == '\0') {
		DELETE_OBJ ( pPuffer);
		return true;
	}
	if ( strcmp (pMWert,pPuffer) == 0) {
		DELETE_OBJ ( pPuffer);
		*pObj = Object;
//		(*(MERKMALSRECHERCHE *)pData)->pObj = Object;
		return false;
	}
	DELETE_OBJ ( pPuffer);
	return true;

  }
//---------------------------------------------------------------------------
///////////////////// Gewaesser bearbeiten
//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT LoescheGewaesserObjekt ( long Object, Bool , void *pData)
  {

	short Status = DEX_GetObjectType (Object);

	if ( Status != OGLinie && Status != OGFlaeche)
		return true;

	long lMCode1 = ((MERKMALSDEFINITION *)pData)->lNummer;
	long lMCode2 = ((MERKMALSDEFINITION *)pData)->lName;
	long lMCode3 = ((MERKMALSDEFINITION *)pData)->lStartPunkt;

	long lCount = ((MERKMALSDEFINITION *)pData)->lCount;
	long lRefCount = ((MERKMALSDEFINITION *)pData)->lRefCount;
	CStatus *pStatus = ((MERKMALSDEFINITION *)pData)->pStatus;
	
    if ( pStatus->Break()) {

		MessageBox ( __hWndM ,
		 ResString (ResID(IDS_STOPCONTROL, &g_pTE->RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);

		return false;
	}
	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lMCode1;		// MerkmalsCode
	tm.imaxLen = NULL;
	tm.pMText = NULL;		
	tm.iTTyp = TT_Objekt;
	DEX_ModTextMerkmal (tm);

	tm.lMCode = (long)lMCode2;		// MerkmalsCode
	tm.imaxLen = NULL;
	tm.pMText = NULL;		
	tm.iTTyp = TT_Objekt;

	if ( lMCode2 != 0L)
		DEX_ModTextMerkmal (tm);

	tm.lMCode = (long)lMCode3;		// MerkmalsCode
	tm.imaxLen = NULL;
	tm.pMText = NULL;		
	tm.iTTyp = TT_Objekt;

	if (lMCode3 != 0L)
		DEX_ModTextMerkmal (tm);

	lRefCount++;
	if ( lCount == 0L && lRefCount > 100 )
		lRefCount = 1L;

	((MERKMALSDEFINITION *)pData)->lRefCount = lRefCount;

	if ( pStatus) 
		pStatus->SetValue(lRefCount, Object);

	return true;

  }
//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT DoppelnAttribut ( long Object, Bool , void *pData)
  {


	long lMCode1 = ((MERKMALSDEFINITION *)pData)->lNummer;	//GewNr


	
	char * pPuffer = new char [_MAX_PATH];
	if ( !pPuffer)
		return true;
	*pPuffer = '\0';


	long lIdent = DEX_GetObjIdent ( Object);

	ulong lSMCode = DEX_GetObjNameMCode(lIdent);

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lSMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		
	tm.iTTyp = TT_Objekt;

	if (!DEX_GetTextMerkmal(tm))
		return true;

	if ( *pPuffer == '\0') {
		DELETE_OBJ(pPuffer);
		return true;
	}

	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lMCode1;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		
	tm.iTTyp = TT_Objekt;

	if ( DEX_ModTextMerkmal(tm) != EC_OKAY)
		return true;

	DELETE_OBJ(pPuffer);

	return true;

  }
//---------------------------------------------------------------------------


//------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SetzeGewaesserObjekt ( long Object, Bool , void *pData)
  {


	short Status = DEX_GetObjectType (Object);

	if ( Status != OGLinie )
		return true;

	long lMCode1 = ((MERKMALSDEFINITION *)pData)->lNummer;


	long lCount = ((MERKMALSDEFINITION *)pData)->lCount;
	long lRefCount = ((MERKMALSDEFINITION *)pData)->lRefCount;
	CStatus *pStatus = ((MERKMALSDEFINITION *)pData)->pStatus;
	
    if ( pStatus->Break()) {

		MessageBox ( __hWndM ,
		 ResString (ResID(IDS_STOPCONTROL, &g_pTE->RF()),80),
		 ResString (ResID(IDS_CAPTIONKOMPAKT, &g_pTE->RF()),80),
		 MB_OK|MB_ICONEXCLAMATION);

		return false;
	}

	
	char * pPuffer = new char [_MAX_PATH];
	if ( !pPuffer)
		return true;
	*pPuffer = '\0';


	long lIdent = DEX_GetObjIdent ( Object);
	ulong lSMCode = DEX_GetObjNameMCode(lIdent);

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lSMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		
	tm.iTTyp = TT_Objekt;

	DEX_GetTextMerkmal(tm);

	tm.lTarget = Object;		// ObjektNummer
	tm.lMCode = (long)lMCode1;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pPuffer;		
	tm.iTTyp = TT_Objekt;

	if ( DEX_ModTextMerkmal(tm) != EC_OKAY)
		return true;

	lRefCount++;
	if ( lCount == 0L && lRefCount > 100 )
		lRefCount = 1L;

	((MERKMALSDEFINITION *)pData)->lRefCount = lRefCount;

	if ( pStatus) 
		pStatus->SetValue(lRefCount, Object);

	char *pLocProt = ((CKompiasExtension *)g_pTE)->KompaktProtokollPointer();
	if ( pLocProt ) {
		char *pT = new char [_MAX_PATH];
		if (pT) {
			*pT = '\0';
			wsprintf (pT,"+++ Zuordnung Quelle-Code %ld -> Ziel-Code %ld : Wert %s\n",lSMCode,lMCode1,pPuffer );
			KompaktProtokoll (pLocProt,pT);
			DELETE_OBJ(pT);
		}
	}

	DELETE_OBJ(pPuffer);

	return true;

  }
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheGewaesserObjekt ( long ONr, Bool , void *pData)
{

	TR_OBJTree *pObj = (( OBJEKTKLASSENTYP *) pData)->pOBJ;
	short iTyp = ((OBJEKTKLASSENTYP *)pData)->iTyp;
	short myTyp = LogObjectType(ONr);
	if (  ( myTyp & iTyp ) == 0 )
		return TRUE;


//	TR_OBJTree *pObj = (TR_OBJTree *)pData;
	
	CTable t(*pObj);

	if ( !t.Find ( &ONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
	}

	return TRUE;

}

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheEinzelGewaesserObjekt ( long ONr, Bool , void *pData)
{

	TR_OBJTree *pObj = (( OBJEKTKLASSENTYP *) pData)->pOBJ;
	short iTyp = ((OBJEKTKLASSENTYP *)pData)->iTyp;
	short myTyp = LogObjectType(ONr);
	if (  ( myTyp & iTyp ) == 0 )
		return TRUE;
	ulong ulMCode = ((OBJEKTKLASSENTYP *)pData)->lMCode;
	LPSTR pMWert = ((OBJEKTKLASSENTYP *)pData)->pMWert;


	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)ulMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm ))
		return true;
	}

	if ( strcmp(pBuff, pMWert) == 0 ) {
		CTable t(*pObj);

		if ( !t.Find ( &ONr) ) {
			TR_OBJCreator OCr ( *pObj);
			ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
		}
		DELETE_OBJ ( pBuff);
		return false;
	}
	DELETE_OBJ (pBuff);

	return true;

}

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheEinzelBauwerke ( long ONr, Bool , void *pData)
{

	TR_OBJTree *pObj = (( OBJEKTKLASSENTYP *) pData)->pOBJ;
	short iTyp = ((OBJEKTKLASSENTYP *)pData)->iTyp;
	short myTyp = LogObjectType(ONr);
	if (  ( myTyp & iTyp ) == 0 )
		return TRUE;
	ulong ulMCode = ((OBJEKTKLASSENTYP *)pData)->lMCode;
	LPSTR pMWert = ((OBJEKTKLASSENTYP *)pData)->pMWert;


	char *pBuff = new char [_MAX_PATH];
	if ( !pBuff)
		return true;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pBuff;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = (long)ulMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm ))
		return true;
	}

	if ( strcmp(pBuff, pMWert) == 0 ) {
		// Merkmal gefunden
		CTable t(*pObj);

		if ( !t.Find ( &ONr) ) {
			TR_OBJCreator OCr ( *pObj);
			ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
		}
	}
	DELETE_OBJ (pBuff);

	return true;

}

//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwObjekt ( long ONr, Bool , void *pData)
{

	TR_OBJTree *pObj = (( OBJEKTKLASSENTYP *) pData)->pOBJ;
	short iTyp = ((OBJEKTKLASSENTYP *)pData)->iTyp;
	short myTyp = LogObjectType(ONr);
	if (  ( myTyp & iTyp ) == 0 )
		return TRUE;


	CTable t(*pObj);

	if ( !t.Find ( &ONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
	}

	return TRUE;

}
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheBauwEinzelObjekt ( long ONr, Bool , void *pData)
{

	if ( -1L == ONr)
		return TRUE;
	
	TR_OBJTree *pObj = (( OBJEKTKLASSENTYP *) pData)->pOBJ;
	short iTyp = ((OBJEKTKLASSENTYP *)pData)->iTyp;
	short myTyp = LogObjectType(ONr);
	long lONr =  ((OBJEKTKLASSENTYP *)pData)->lONr;
	if (  ( myTyp & iTyp ) == 0 )
		return TRUE;
	if ( lONr != ONr)
		return TRUE;

	CTable t(*pObj);

	if ( !t.Find ( &ONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (ONr,NULL);
		return FALSE;
	}

	return TRUE;

}
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumBauwerke ( long lONr, Bool , void *pData)
{

	TR_OCLTree *pBauw = (( EREIGNISTYP *) pData)->pBauw;
	TR_OBJTree *pObj = (( EREIGNISTYP *) pData)->pObj;
	long lONF = ((EREIGNISTYP *)pData)->lONF;

	IExtendTopRel2 *pTop = (( EREIGNISTYP *) pData)->pTop;

	if ( !pTop || !pBauw || !pObj)
		return false;

	CTable e(*pBauw);
	long lIdent = DEX_GetObjIdent(lONr);

	if ( !e.Find ( &lIdent))
		return true;					// kein Bauwerk

	if ( pTop) {
		Relat Rel;
		HRESULT hr = pTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
		if (FAILED(hr)) {
			return true;
		}
		if ( Rel != REL_INN )
			return true;

	}

	CTable t(*pObj);

	if ( !t.Find ( &lONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
		return true;
	}

	return true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumTRiASObjekte ( long lONr, Bool , void *pData)
{

	TR_OCLTree *pClass = (( TOPOLOGIETYP *) pData)->pOutClass;
	long lONF = ((TOPOLOGIETYP *)pData)->lONF;

	IExtendTopRel2 *pTop = (( TOPOLOGIETYP *) pData)->pTop;

	if ( !pTop || !pClass)
		return false;

	long lIdent = DEX_GetObjIdent(lONr);

	if ( pTop) {
		Relat Rel;
		HRESULT hr = pTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
		if (FAILED(hr)) {
			return true;
		}
		if ( Rel != REL_INN && Rel != REL_INAUS)
			return true;

	}

	TR_OBJTree *pObj;

	CTable e(*pClass);

	if ( !e.Find ( &lIdent) ) {
		pObj = new TR_OBJTree;
		TR_OCLCreator OC ( *pClass);
		ContCreate ( OC, TR_OCL ) (lIdent,0L,true,pObj);
	} else {
		TR_OCLLock l(e);
		if ( l)
			pObj = l->OBJ();
	}

	CTable t(*pObj);

	if ( !t.Find ( &lONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
	}

	return true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumEinMuendung ( long lONr, Bool , void *pData)
{

	// Objekt muß Linie sein !!!
	OBJSTATISTIK OS;
	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  lONr;

	if ( OS.lONr > 0L && DEX_GetObjStatistik (OS)) {

			if ( OS.iObjTyp != OT_KANTE ) 
					return true;
	}



	TR_OCLTree *pBauw = (( EREIGNISTYP *) pData)->pBauw;	// Hier : Gewässer
	TR_OBJTree *pObj = (( EREIGNISTYP *) pData)->pObj;
	long lONF = ((EREIGNISTYP *)pData)->lONF;	// Hier : auszuschließendes Gewässer

	if ( lONr == lONF)
		return true;

	/*
	long lONF = ((EREIGNISTYP *)pData)->lONF;

	IExtendTopRel2 *pTop = (( EREIGNISTYP *) pData)->pTop;

	if ( !pTop || !pBauw || !pObj)
		return false;
	*/

	CTable e(*pBauw);
	long lIdent = DEX_GetObjIdent(lONr);

	if ( !e.Find ( &lIdent))
		return true;					// kein Gewässer

	/*
	if ( pTop) {
		Relat Rel;
		HRESULT hr = pTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
		if (FAILED(hr)) {
			return true;
		}
		if ( Rel != REL_INN && Rel != REL_INAUS)
			return true;

	}
	*/

	CTable t(*pObj);

	if ( !t.Find ( &lONr) ) {
		TR_OBJCreator OCr ( *pObj);
		ContCreate ( OCr, TR_OBJ ) (lONr,NULL);
		return true;
	}

	return true;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SelektierteObjekte ( long ONr, Bool , void *pData)
{
	(* ( long * ) pData)++;
	(* ((long *)pData + *(long *)pData )) = ONr;
	return true;
}
/////////////////////////////////////////////////////////////////////////////
bool LeistungenInKompakt ( LEISTUNGEN *p, KOMPAKTDATEN *q ) 
{

	if ( !p || !q )
		return false;

	if ( !p->pcGewaesserNr || *p->pcGewaesserNr == '\0')
		return false;

	memset (q, '\0', sizeof(KOMPAKTDATEN));
	q->dwSize = sizeof(KOMPAKTDATEN);

	q->iIdentNrHerkunft = p->iIdentNrHerkunft;
	q->iIdentNrZuordnung = p->iIdentNrZuordnung;
	q->iLinksRechtsMitte = p->iLinksRechtsMitte;
	q->pcGewaesserNr = p->pcGewaesserNr;

	if (p->pcLeistung)
		q->pcLeistung = p->pcLeistung;

	q->lMeterOffen = p->lMeterOffen;
	q->lBeginn = p->lBeginn;
	q->lEnde = p->lEnde;
	q->dKostetDM = p->dKostetDM;
	q->iRechnungsNr = p->iRechnungsNr;

	if (p->pcZuordnung )
		q->pcZuordnung = p->pcZuordnung;

 // Legende
	if (p->pcKurzText)
		q->pcKurzText = p->pcKurzText;
	if (p->pcLangText)
		q->pcLangText = p->pcLangText;
	if (p->pcComment)
		q->pcComment = p->pcComment;
// BauwerkeTeil
	q->pcBauwerksBezeichnung = NULL;
	q->lAnlageNr = 0L;
	q->lHoch = 0L;
	q->lRechts = 0L;
	q->lAnlageNr = 0L;
//----------------------------
	q->dBauwHoehe = 0.0;
	q->dWasserSpDiff = 0.0;
	q->pcBezeichner1 = NULL;
	q->pcBezeichner2 = NULL;

	return true;
}

/////////////////////////////////////////////////////////////////////////////
bool BauwerkeInKompakt ( BAUWERKE *p, KOMPAKTDATEN *q ) 
{
	if ( !p || !q )
		return false;

	if ( !p->pcGewaesserNr || *p->pcGewaesserNr == '\0')
		return false;

	memset (q, '\0', sizeof(KOMPAKTDATEN));
	q->dwSize = sizeof(KOMPAKTDATEN);
	q->iIdentNrHerkunft = cBauwerkeIdent;
	q->iIdentNrZuordnung = p->iIdentNrZuordnung;
	q->pcGewaesserNr = p->pcGewaesserNr;

	q->iLinksRechtsMitte = Leist_Mitte;

	if (p->pcBauwerksBezeichnung)
		q->pcBauwerksBezeichnung = p->pcBauwerksBezeichnung;

	q->lAnlageNr = p->lAnlageNr;
	q->lBeginn = p->lBeginn;
	q->lEnde = p->lEnde;
	q->lHoch = p->lHoch;
	q->lRechts = p->lRechts;
	q->lObjectIdent = p->lObjectIdent;	// BauwerkeIdent

//----------------------------
	q->dBauwHoehe = p->dBauwHoehe;
	q->dWasserSpDiff = p->dWasserSpDiff;
	if (p->pcBezeichner1)
		q->pcBezeichner1 = p->pcBezeichner1;
	if (p->pcBezeichner2)
		q->pcBezeichner2 = p->pcBezeichner2;

//----Leistungen - Rest
	q->pcLeistung = NULL;
	q->lMeterOffen = 0L;
	q->dKostetDM = 0.0;
	q->iRechnungsNr = 0;
	q-> pcZuordnung = NULL;
 // Legende
	q->pcKurzText = NULL;
	q->pcLangText = NULL;
	q->pcComment = NULL;

	return true;
}
///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------
char *StrDuplicat ( char *cptr ) 
{
char *newPtr = NULL;

	if (cptr != NULL && *cptr != NULL ) {
		newPtr = new char [strlen(cptr)+1];
		if (newPtr != NULL) 
			strcpy (newPtr, cptr);

	}

return newPtr;
}
/////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheTRiASKlassen (long Ident, DWORD Typ , void *pData)
{
	long lIdent = (( OBJCLSRECHERCHE *)pData)->lIdent;

	MultiSelListBox *p = (( OBJCLSRECHERCHE *)pData)->pListBox;


#if _MSC_VER < 1100

	if ( Ident == lIdent)
		return true;
#else
	HPROJECT hPr1 = DEX_GetObjectsProject(Ident);
	HPROJECT hPr2 = DEX_GetObjectsProject(lIdent);
	if ( Ident == lIdent && hPr1 == hPr2)
		return true;
#endif

	PBDDATA pbdData;
	char KText[TEXTLEN+1];
	KText[0] = '\0';
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

#if _MSC_VER < 1100
	DEX_GetPBDData (pbdData);
#else
	DEX_GetPBDDataEx (hPr1,pbdData);
#endif


	char outBuff[TEXTLEN+20];
	if ( KText[0] == NULL )
		strcat ( KText, ResString(ResID(IDS_KOMPNODEFIDENT,&g_pTE->RF()),70));
	KText[TEXTLEN] = '\0';

	ulong ulIdent = (ulong) Ident;
	char NewIdent [MAX_OKS_LENX + 1];


#if _MSC_VER < 1100
	ClassFromIdentX ( ulIdent, NewIdent);
#else
	ClassFromIdentX ( hPr1,ulIdent, NewIdent);
#endif

	char CTyp = ' ';

	if ( Typ & OTPunkt ) {
		CTyp = 'P';


#if _MSC_VER < 1100

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

		p -> AddString (outBuff);
#else

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];
			TX_ASSERT(NULL != hPr1);
			if (NULL != DEX_GetDataSourceShortName (hPr1, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
		}

	// Ident am jeweiligen Item speichern
		int iIndex = p -> AddString (outBuff);
		p -> SetItemData (iIndex, Ident);

#endif

	}

	if ( Typ & OTLinie ) {
		CTyp = 'L';

#if _MSC_VER < 1100

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

		p -> AddString (outBuff);
#else

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];
			TX_ASSERT(NULL != hPr1);
			if (NULL != DEX_GetDataSourceShortName (hPr1, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
		}

	// Ident am jeweiligen Item speichern
		int iIndex = p -> AddString (outBuff);
		p -> SetItemData (iIndex, Ident);

#endif

	}

	if ( Typ & OTFlaeche ) {
		CTyp = 'F';

#if _MSC_VER < 1100

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

		p -> AddString (outBuff);
#else

		wsprintf (outBuff, "%s:%c:%s", NewIdent, CTyp, KText);

	// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen in
	// Klammern hinten anhängen
		if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
			char cbBuffer[_MAX_PATH];
			TX_ASSERT(NULL != hPr1);
			if (NULL != DEX_GetDataSourceShortName (hPr1, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
		}

	// Ident am jeweiligen Item speichern
		int iIndex = p -> AddString (outBuff);
		p -> SetItemData (iIndex, Ident);

#endif

	}

	return true;

}
//-------------------------------------------------------------------------------
extern "C" Bool PASCAL _XTENSN_EXPORT SucheKompaktDaten ( HPROJECT hPr, Bool, void *pData)
{

	short iTyp = ((GEWAESSERKLASSE *)pData)->iTyp;
	ulong lIDCode = 0;

	ENUMNOKEYLONG ENL;
//	Bestimmen der Anzahl der Objektklassen
	ENL.eFcn = ( ENUMNOKEYLONGPROC) SucheKompaktKlassen;
	ENL.ePtr = pData;


	ResString StrH (ResID(IDS_HYDRAULIKCODE,&g_pTE->RF()),60);
	ResString StrF (ResID(IDS_FLAECHENCODE,&g_pTE->RF()),60);

	if ( iTyp == PM_FLAECHEN)
		lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrF.Addr());
	else
		lIDCode = DEX_GetMCodeFromFeatureNameEx(hPr,StrH.Addr());

	if ( lIDCode != 0) {

		((GEWAESSERKLASSE *)pData)->lGewCode = lIDCode;
		DEX_EnumClasses(hPr,ENL); 

	}

	return true;

}

///////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT SucheTRiASObjekte ( long lONr, Bool , void *pData)
{

	long lONF = (( TRIASKLASSE *)pData)->lONF;

	TR_IDMTree *pIDM = (( TRIASKLASSE *)pData)->pIDM;

	IExtendTopRel2 *pTop = ((TRIASKLASSE *)pData)->pTop;


	short iStatus = DEX_GetObjectType (lONr);
	short iStat;

	if ( OGText == iStatus)
		return true;

	if ( OGPunkt == iStatus)
		iStat = OTPunkt;

	if ( OGLinie == iStatus)
		iStat = OTLinie;

	if ( OGFlaeche == iStatus)
		iStat = OTFlaeche;

	long lIdent = DEX_GetObjIdent(lONr);

	CTable t(*pIDM);

	if ( !t.Find ( &lIdent) ) {
		TR_IDMCreator OCr ( *pIDM);
		ContCreate ( OCr, TR_IDM ) (lIdent,iStatus);
	} else {
//	Typ testen
		TR_IDMLock l(t);
		short iTyp = l->Typ();

		if ( (iTyp & iStat) == 0)	// Typ nicht gefragt
			return true;

		Relat Rel;
		HRESULT hr = pTop->TopoRelationObjObj_ONr ( lONF,lONr,&Rel);
		if (FAILED(hr)) 
			return true;

		if ( REL_INN != Rel && REL_INAUS != Rel ) 
			return true;

		l->StoreObject(lONr,Rel);
	}
	return true;

}
//--------------------------------------------------------
extern "C"  long PASCAL _XTENSN_EXPORT KompaktIdentifikator (char * pLocProt, short iHk, short iZuo )
{
	long lIdent = 0;

	char Ident[MAX_OKS_LENX + 1];
	ulong rIdent = (ulong)iHk * 1000 + (ulong)iZuo;

	char KomSign = KompaktIdentifikatorTabelle[iHk-1];

	wsprintf ( Ident,"%c%ld",KomSign,rIdent);

#if _MSC_VER < 1100
	HRESULT hr = IdentFromClassX ( Ident,&rIdent);
#else
	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	HRESULT hr = IdentFromClassX (hPr,Ident,&rIdent);
	if ( hr == S_FALSE)
		return 0;
#endif

	if (FAILED(hr)) {
		return 0;
	}

	lIdent = (long) rIdent;

//	if ( pLocProt ) {

//		wsprintf ( Ident,"%c%ld:\n",KomSign,rIdent);

//		KompaktProtokoll ( pLocProt,Ident);
//	}

	return lIdent;
}
//---------------------------------------------------------------------------
//--------------------------------------------------------
extern "C"  long PASCAL _XTENSN_EXPORT KompaktIdentifikatorEx (char * pLocProt, short iHk, short iZuo )
{
	long lIdent = 0;

	char Ident[MAX_OKS_LENX + 1];
	ulong rIdent = (ulong)iHk * 1000 + (ulong)iZuo;

	char KomSign = KompaktIdentifikatorTabelle[iHk-1];

	wsprintf ( Ident,"%c%ld",KomSign,rIdent);

#if _MSC_VER < 1100
	HRESULT hr = IdentFromClassX ( Ident,&rIdent);
#else
	HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	HRESULT hr = IdentFromClassX (hPr,Ident,&rIdent,true);
//	if (S_FALSE == hr) {
//		return 0;
//	}
#endif


	lIdent = (long) rIdent;


	return lIdent;
}
//---------------------------------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT  KompaktProtokoll (  char * pLocProt, char *pText )
{
	if (!pText || !pLocProt )
		return false;

	FILE *fascii = fopen (pLocProt, "a");

	if ( !fascii) {
		return false;
	}

	if ( fascii) {
		fprintf (fascii,pText);
		fclose (fascii);
	}

	return true;

}
//-----------------------------------------------------------------------------
extern "C" char * PASCAL _XTENSN_EXPORT ObjektKlassenSchluessel ( long lONr)
{

	if ( lONr == -1L || lONr == 0L)
		return NULL;

	ulong ulIdent = (ulong) DEX_GetObjIdent(lONr);
	char * pNewIdent = new char[ MAX_OKS_LENX + 1];
	if ( !pNewIdent)
		return NULL;

	*pNewIdent = '\0';

#if _MSC_VER < 1200
	ClassFromIdentX ( ulIdent, pNewIdent);
#else

	HPROJECT hPro = DEX_GetObjectsProject(ulIdent);

	ClassFromIdentX ( hPro, ulIdent, pNewIdent);
#endif

	return pNewIdent;
}

//------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" char * PASCAL _XTENSN_EXPORT GeometrieTyp ( long lONr)
{
	char *pGITyp = new char [20];

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( lONr == -1L || lONr == 0L)
		return NULL;

	*pGITyp = '\0';

	if ( DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp == OT_KANTE )
			strcat (pGITyp ,"Linienobjekt");
		if ( OS.iObjTyp == OT_PUNKT)
			strcat (pGITyp , "Punktobjekt");
		if ( OS.iObjTyp == OT_FLAECHE )
			strcat (pGITyp ,"Flächenobjekt");
		if ( OS.iObjTyp == OT_TEXT)
			strcat (pGITyp , "Textobjekt");
	}
	if ( *pGITyp == '\0')
		strcat ( pGITyp, "unbekannt");


	return pGITyp;
}
//-----------------------------------------------------------------------------
extern "C" char * PASCAL _XTENSN_EXPORT LinienAnfangsPunkt ( long lONr)
{
	char *pGITyp = new char [20];

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);
	OS.lONr =  lONr;

	if ( lONr == -1L || lONr == 0L)
		return NULL;

	*pGITyp = '\0';


	if ( DEX_GetObjStatistik (OS) ) {
		if ( OS.iObjTyp != OT_KANTE )
			return NULL;

	}


	OBJGEOMETRIE OG;
	double *pX = new double [OS.lCnt];
	double *pY = new double [OS.lCnt];
    
	if (pX == NULL || pY == NULL) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return NULL;
	}

	memset (&OG,'\0',sizeof(OBJGEOMETRIE));
	OG.dwSize = sizeof(OBJGEOMETRIE);
	OG.lONr = lONr;
	OG.lCnt = OS.lCnt;
	OG.pdblX = pX;
	OG.pdblY = pY;
	OG.iFlags = OGConverted;
	if (!DEX_GetObjGeometrie (OG)) {
		DELETE_OBJ (pX);
		DELETE_OBJ (pY);
		return NULL;
	}

	wsprintf ( pGITyp, "(%ld,%ld)",(long)*pX,(long)*pY);
	DELETE_OBJ (pX);
	DELETE_OBJ (pY);

	return pGITyp;
}

//------------------------------------------------------------------------------

extern "C" bool PASCAL _XTENSN_EXPORT SetzeBauwerkeIdent ( long lONr, long lObjectIdent)
{

	if ( lONr == -1L || lONr == 0L || lObjectIdent <= 0L)
		return false;

	char *pUniq = new char [_MAX_PATH];

	if ( !pUniq) 
		return false;

	*pUniq = '\0';

	wsprintf (pUniq,"BWIdent-%ld_%ld",lONr,lObjectIdent);

	long lIdent = DEX_GetObjIdent(lONr);

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.iTTyp = TT_Objekt;
	
	tm.lTarget = lONr;		// ObjektNummer
	tm.imaxLen = _MAX_PATH-1;
	tm.pMText =pUniq;		// Puffer

	#if _MSC_VER < 1100
		tm.lMCode = DEX_GetUniqueIdentMCode();		// MerkmalsCode
	#else
		HPROJECT hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
		tm.lMCode = DEX_GetUniqueIdentMCodeEx(hPr);		// MerkmalsCode
	#endif


	DEX_ModTextMerkmal ( tm );

	DELETE_OBJ(pUniq);

	return true;
}

//-----FlächenObjekte in Container enumerieren --------
extern "C"  Bool PASCAL _XTENSN_EXPORT EnumNachbarObjects ( long lONr, Bool , void *pData)
{
	TR_OBJTree *pObj = (TR_OBJTree *)pData;

	short Status = DEX_GetObjectType (lONr);

//--------------Zuordnung----------------------------
	if ( Status != OGFlaeche ) 
		return true;

#if _MSC_VER >= 1100
	long lIdent = DEX_GetObjIdent(lONr);

	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	HPROJECT m_hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();
	if ( hPr != m_hPr)
		return true;
#endif

	CTable t (*pObj);
	
	TR_OBJCreator OCr (*pObj);
	ContCreate (OCr,TR_OBJ) (lONr, NULL);

	return True;

}
//-------------------------------------------------------------------------------
extern "C"  Bool PASCAL _XTENSN_EXPORT LoescheTRiASObjekte ( long lONr, Bool , void *pData)
{

	long lMCode = (( MERKMALSDEFINITION *)pData)->lNummer;
	char *pGewNr = (( MERKMALSDEFINITION *)pData)->pNummer;
	char *pMText = new char [_MAX_PATH];
	if (!pMText)
		return true;

	// MerkmalsWert holen
	TARGETMERKMAL tm;
	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = lONr;		// Objekt
	tm.imaxLen = _MAX_PATH;
	tm.pMText =pMText;		// Puffer
	tm.iTTyp = TT_Objekt;
	tm.lMCode = lMCode;		// MerkmalsCode

	{
	ErrInstall EI (WC_BADMKTYP); // Warnung unterdrücken
	if ( !DEX_GetTextMerkmal ( tm )) {
		DELETE_OBJ(pMText);
		return true;
	}
	}

	if ( strcmp (pMText,pGewNr) == 0 )
		BOOL iFlag = DEX_DeleteObject(lONr);

	DELETE_OBJ(pMText);

	return true;

}

//--------------------------------------------------------------------------------
extern "C"  char * PASCAL _XTENSN_EXPORT BauwerkeName ( short iZuo)
{
	char *pLText = new char [_MAX_PATH];
	if (!pLText)
		return NULL;
	*pLText = '\0';

// --------------------Bauwerke -----------------------------------------

	if (iZuo == cBauwerkeSchoepfwerke)
		strcat ( pLText,  ResString (ResID(IDS_SCHOEPFWERKE,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeStauanlagen)
		strcat ( pLText,  ResString (ResID(IDS_STAUANLAGEN,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeRechte)
		strcat ( pLText,  ResString (ResID(IDS_RECHTE,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeKreuzungen)
		strcat ( pLText,  ResString (ResID(IDS_KREUZUNGEN,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeSohlbauwerke)
		strcat ( pLText,  ResString (ResID(IDS_SOHLBAUWERKE,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeSchaechte)
		strcat ( pLText,  ResString (ResID(IDS_SCHAECHTE,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeOekologie1)
		strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE1,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeRohrleitungen)
		strcat ( pLText,  ResString (ResID(IDS_ROHRLEITUNGEN,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeDurchlaesse)
		strcat ( pLText,  ResString (ResID(IDS_DURCHLAESSE,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeOekologie2)
		strcat ( pLText,  ResString (ResID(IDS_OEKOLOGIE2,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeBebauungLinks)
		strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGLINKS,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeBebauungRechts)
		strcat ( pLText,  ResString (ResID(IDS_BEBAUUNGRECHTS,&g_pTE->RF()),40));
	if (iZuo == cBauwerkeEinmuendung)
		strcat ( pLText,  ResString (ResID(IDS_EINMUENDUNG,&g_pTE->RF()),40));

	if (*pLText == '\0') {
		DELETE_OBJ(pLText);
		return NULL;
	}
	return pLText;
}

//--------------------------------------------------------------------------------

#if _MSC_VER >= 1100

void DefineFeatureSet ( PBDMERKMALEX * pData)
{


	HPROJECT _hPr = ((CKompiasExtension *)g_pTE)->AktuellesProjekt();

	HPROJECT hPr = DEX_GetObjectsProject(pData->lIdent);

// Test, ob OE bereits definiert
	long lRefCode = DEX_GetMCodeFromFeatureNameEx(hPr,pData->pbdKText);

	if ( hPr == _hPr && 0L != lRefCode && lRefCode == pData->pbdCode)
		return;
	if ( hPr != _hPr && 0L != lRefCode )
		return;

	if (lRefCode != 0L && lRefCode != pData->pbdCode) {
		if ( _hPr == hPr)
			((CKompiasExtension *)g_pTE)->ModifyObjFeature(lRefCode,pData->lIdent,pData->pbdKText);

		{
		ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (hPr,*pData) != EC_OKAY)
				return;
			else
				DEXN_PBDMCodeChanged (pData->pbdCode);
		}
		return;
	}

	if (0L == lRefCode ) {		// nicht in Datenquelle
		long lNewCode = pData->pbdCode;
		if ( _hPr != hPr ) {
			lNewCode = DEX_GetUniqueSysMCode();
		}

		if ( 0L == lNewCode)
			return;

		pData->pbdCode = lNewCode;

		{
		ErrInstall EI (WC_NOMERKMAL);
			if (DEX_ModPBDDataEx (hPr,*pData) != EC_OKAY)
				return;
			else
				DEXN_PBDMCodeChanged (pData->pbdCode);
		}

	}
	return;
}

#endif
//---------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//
// File : DATAHELP.CXX
//////////////////////////////////////////////////////////////////////////////

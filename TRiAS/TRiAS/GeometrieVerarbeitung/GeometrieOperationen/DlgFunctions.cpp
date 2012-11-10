// Definitionen: Funktionen, die in mehreren Dialogen benötigt werden
// File: DlgFunctions.cpp
// W. Mörtl


#include "ObjOperP.hxx"

#include "ObjOperR.h"		// Ressourcekonstante IDS_BEARB_OBJEKT in ProgressProxy.h

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
// externe Funktion
extern BOOL _OBJOPER_EXPORT FAR PASCAL CountSelectedObjects (long lONr, BOOL, void* lZaehl);



///////////////////////////////////////////////////////////////////////////////////////////////
#if _TRiAS_VER >= 0x0300
// Testen, ob sich unter den selektierten (markierten) Objekten AUSGENOMMEN das aktivierte
// (blinkende) Objekt aller geöffneten Recherchefenster Objekte aus schreibgeschützten
// Datenquellen bzw. Objektklassen befinden
BOOL _OBJOPER_EXPORT FAR PASCAL ReadOnlySelObjects (long lONr, BOOL, void* pROT)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (lONr == ((ROTest*)pROT)->lONrAO)
		return TRUE;

ulong ulIdent = DEX_GetObjIdent (lONr);

	if (DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt
	{
		((ROTest*)pROT)->bRO = true;
		return FALSE;	// der Rest des Testes kann großzügig erlassen werden
	}

	return TRUE;
}


// --------------------------------------------------------------------------------------------
// Testen, ob sich unter den selektierten (markierten) Objekten EINSCHLIEßLICH dem aktivierten
// (blinkenden) Objekt aller geöffneten Recherchefenster Objekt aus schreibgeschützten
// Datenquellen bzw. Objektklassen befinden; dann pvRO = true
BOOL _OBJOPER_EXPORT FAR PASCAL ReadOnlyAllObjects (long lONr, BOOL, void* pvRO)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ulong ulIdent = DEX_GetObjIdent (lONr);

	if (DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt
	{
		*(bool*)pvRO = true;
		return FALSE;	// der Rest des Testes kann großzügig erlassen werden
	}

	return TRUE;
}
#endif // _TRiAS_VER >= 0x0300




///////////////////////////////////////////////////////////////////////////////////////////////
// In der ModifyIdent-Page wurde nichts ausgewählt bzw. diese Seite ist gar nicht da, dann
// default-Identifikator für die Ergebnisobjekte vorgeben
HRESULT GetDefaultIdent (bool bKnowOC, IEnumLONG* pEnumIn, string sUnionName, ulong& ulIdent)
{
long lONr = 0;

	if (bKnowOC)
	{
		_ASSERTE (0 != pEnumIn);

		// Identifikator des 1. Objektes vorgeben
		pEnumIn->Reset();
		RETURN_FAILED_HRESULT (pEnumIn->Next (1, &lONr, NULL));
		ulIdent = DEX_GetObjIdentEx (lONr);
	}
	else
	{
		ulIdent = DEX_GetIdentFromClassName (sUnionName.c_str());
		if (0 == ulIdent)	// dieser Identifikator ist noch nicht in der PBD
		{
			ulIdent = DEX_GetUniqueICode();
			IdentNachtragen (ulIdent, sUnionName, false);
		}
	}

	return S_OK;

} // GetDefaultIdent


// --------------------------------------------------------------------------------------------
// default-Identifikator ulIdent den pEnumOut-Objekten zuordnen, da in einigen Routinen die
// Objekte nur mit dem Objektklassenschlüssel "Unbekannte Objektklasse" erzeugt und
// abgespeichert werden
HRESULT SetDefaultIdent (IEnumLONG* pEnumOut, ulong ulIdent, ulong& ulAnzNeuObj)
{
	ulAnzNeuObj = 0;	// für den Fehlerfall

	if (0 == ulIdent || (ulong)-1 == ulIdent)
		return S_FALSE;

	// bei Abbruch durch den Anwender gilt pEnumOut == NULL

	if (! pEnumOut)
		return E_POINTER;

ulong ulCnt = pEnumOut->Count();

	if (0 == ulCnt)
		return S_FALSE;

	ulAnzNeuObj = ulCnt;

long lONr = 0;
MODOBJIDENT MOI;	// Struktur für Modifikation des Identifikators

	INITSTRUCT (MOI, MODOBJIDENT);
	MOI.lNewIdent = ulIdent;

	for (pEnumOut->Reset(); S_OK == pEnumOut->Next (1, &lONr, NULL); ) 
	{
		_ASSERTE (lONr != 0);
		_ASSERTE (lONr != -1);

	short iOT = DEX_GetObjectType (lONr);

		if (OGLinie == iOT)
			MOI.iMode = MODIDENT_LINIE | MODIDENT_ADDTOVIEW;	// zur Sicht hinzufügen
		else if (OGFlaeche == iOT)
			MOI.iMode = MODIDENT_FLAECHE | MODIDENT_ADDTOVIEW;

		_ASSERTE (OGLinie == iOT || OGFlaeche == iOT);

		MOI.lONr = lONr;
		DEX_ModObjectIdentEx (MOI); 
	}

	return S_OK;

} // SetDefaultIdent


// --------------------------------------------------------------------------------------------
// Testen, ob die selektierten (markierten) Objekte ausgenommen das aktivierte (blinkende)
// Objekt aller geöffneten Recherchefenster den Read/Write-Modus besitzen
bool NoReadOnlySel (void)
{
#if _TRiAS_VER < 0x0300
	return true;
#else
ROTest ROT;

	ROT.lONrAO = ((ObjektOpExtension*)g_pTE)->ONrAO();
//	ROT.lONrAO = _lONrAO;
	ROT.bRO = false;

ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte
	
	ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) ReadOnlySelObjects;
	ELK.ePtr = (void*)&ROT;
	return DEX_EnumSelectedObjects (ELK);
#endif // _TRiAS_VER < 0x0300

	return true;

} // NoReadOnlySel


// --------------------------------------------------------------------------------------------
// Testen, ob die selektierten (markierten) Objekte aller geöffneten Recherchefenster den
// Read/Write-Modus besitzen
bool NoReadOnlyAll (void)
{
#if _TRiAS_VER < 0x0300
	return true;
#else
bool bRO = false;
ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte
	
	ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) ReadOnlyAllObjects;
	ELK.ePtr = (void*) &bRO;
	return DEX_EnumSelectedObjects (ELK);
#endif // _TRiAS_VER < 0x0300
}


// --------------------------------------------------------------------------------------------
// Ermittlung der Anzahl der selektierten Objekte in den geöffneten Recherchefenstern
// entsprechend ihrem Objekttyp
//   plNumber[0]: Anzahl der selektierten (markierten) Objekte (ausschließlich dem aktivierten,
//                d.h. blinkenden Objekt)
//   plNumber[1]: Anzahl der selektierten Flächen (einschl. der aktivierten Fläche)
//   plNumber[2]: Anzahl der selektierten Kanten (einschl. der aktivierten Kante)
//   plNumber[3]: Anzahl der selektierten Punkte (einschl. des aktivierten Punktes)
bool TypeCounter (long* plNumber)
{
	if (0 == plNumber)
	{
		_ASSERTE (0 != plNumber);

		return false;
	}

// Objektnummern aller selektierten, d.h. blau markierten Objekte bereitstellen und Anzahl
// der selektierten Objekte ermitteln
ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte

	plNumber[0] = 0;	// Anzahl der selektierten Objekte (s. SetsOperatDlg.h)
	plNumber[1] = 0;	// Flächen
	plNumber[2] = 0;	// Linien
	plNumber[3] = 0;	// Punkte
	ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) CountSelectedObjects;	// zu rufende Funktion
	ELK.ePtr = (void*) plNumber;						// durchgereichte Daten
	DEX_EnumSelectedObjects (ELK);

	return true;
}


// --------------------------------------------------------------------------------------------
// Ermittlung der Ausgangstoleranzen für die Linienvereinigung
bool GetStartTolerances (double& dFuzzy, double* pdDangle)
{
	dFuzzy = 0.0;		// für Fehlerfall

// Projekt-Container ermitteln
ObjRechteck oc;

	DEX_GetProjectCont (oc);
/*
// Ermittlung der jeweils größten Ausdehnung in x- bzw. y-Richtung der zu vereinigenden
// Linienobjekte (insofern ist ObjRechteck eigenlich nicht die richtige Klasse, da die größte
// Ausdehnung in x-Richtung von dem einen und die größte Ausdehnung in y-Richtung von einem
// anderen Objekt stammen kann; aber ObjRechteck ist mit seinen 4 KoOrd-Werten für die zu
// behandelnde Frage schön bequem)
ObjRechteck oc;

ENUMLONGKEY ELK;	// Enumeration aller selektierten Linienobjekte

	ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) GreatestObjectContainer;	// zu rufende Funktion
	ELK.ePtr = (void*) &oc;	// durchgereichte Daten
	DEX_EnumSelectedObjects (ELK);
*/		

// default-Wert für Fuzzy-Toleranz ermitteln
CoordTransX CTX;	
DoublePair dpMin, dpMax;

	if (! CTX.UnScale (oc.XMin(), oc.YMin(), &dpMin.X(), &dpMin.Y()))
		return false;
	if (! CTX.UnScale (oc.XMax(), oc.YMax(), &dpMax.X(), &dpMax.Y()))
		return false;

double dMinExtX, dMinExtY;

	if (! CTX.CoordTransDistanceEx (&dpMin, &dpMax, dMinExtX, dMinExtY))
		return false;
	
	// Toleranz als max ((Xmax - Xmin), (Ymax - Ymin)) / 10000 errechnen;
	// ist eine Containerseite jedoch kleiner als MinExt, dann Toleranz = LowFuzzy;
	// MinExt, LowFuzzy und FuzzyVal in opdeklar.hxx definiert
	if ((dMinExtX <= MinExt) || (dMinExtY <= MinExt))
		dFuzzy = dLowFuzzy;
	else
	{
		dFuzzy = max (dMinExtX, dMinExtY) / FuzzyVal;
		if (dFuzzy <= 0.) dFuzzy = dLowFuzzy;	// Minimlawert

		// auf 2 gültige Ziffern und höchstens 2 Kommastellen runden
		dFuzzy = fabs (dFuzzy);	// vorsichtshalber

	double k = 1.;

		while (dFuzzy >= k)
			k *= 10.;
		dFuzzy = floor (100./k * (dFuzzy + 0.005*k)) * k/100.;
	}

			
// default-Wert für Dangle-Toleranz ermitteln
	if (pdDangle)
	{
		*pdDangle = dFuzzy / 2.;

	double k = 1.;

		while (*pdDangle >= k)
			k *= 10.;
		*pdDangle = floor (100./k * (*pdDangle + 0.005*k)) * k/100.;
	}

	return true;

} // GetStartTolerances


// --------------------------------------------------------------------------------------------
// Sheet-Buttons einstellen
void AdjustSheetWizardBttns (CPropertyPage* pPP, DWORD dwFlags, bool bDisableNext)
{
	if (0 == pPP)
	{
		_ASSERTE (0 != pPP);
		return;
	}

DWORD dwBttns = 0;

	if (!(dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	// darf kein Child haben
	if (! bDisableNext)
	{
		if (dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	}
	else if (dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pPP->SetSheetWizardButtons (dwBttns);

} // AdjustSheetWizardBttns

// Funktionen für Arbeit mit Identifikator- und Merkmalsdatenbank
// File: DATBANK.CXX
// W. Mörtl


#include "GeometrP.hxx"

#include <iunredo.hxx>		// LPUNDOREDOPBDDATA
#include <undoguid.h>		// CLSID_UndoRedoObject
#include <errinstx.hxx>		// ErrInstall

#include "GeometrR.h"
#include "objgguid.h"
#include "FormatString.hxx"	// Format()
#include "datbank.hxx"
#include "opdeklar.hxx"		// DatKop


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif    

//////////////////////////////////////////////////////////////////////////////
// SmartIFs
DefineSmartInterface(InitObjektGeometrie);
DefineSmartInterface(ObjektGeometrie);
        
///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern "C" char pDLLName [_MAX_PATH];



///////////////////////////////////////////////////////////////////////////////////////////////
bool _GEOMETR_EXPORT CStringComp :: operator() (const string& slh, const string& srh) const
	{
	long lEndIndex = min (slh.length(), srh.length());

		for (long i = 0; i < lEndIndex; i++)
		{
			if (slh[i] < srh[i]) 
				return true;
			if (slh[i] > srh[i]) 
				return false;
		}

		return slh.length() < srh.length();
	}


///////////////////////////////////////////////////////////////////////////////////////////////
// alle Merkmalscodes eines Objektes (dessen Objektnummer in der Struktur ENUMLONGKEY ELK
// angegeben ist) bereitstellen
BOOL _GEOMETR_EXPORT FAR PASCAL AlleMerkmale (ulong ulMCode, BOOL, void* pvData)
{
	_ASSERTE (ulMCode != 0);
	_ASSERTE ((ulong)-1 != ulMCode);
	_ASSERTE (pvData != 0);

ulong ulIdent = DEX_GetObjIdent (((DatKop*)pvData)->lONr1);
HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

#if _TRiAS_VER < 0x0300
	if (ulMCode == DEX_GetOldUniqueIdentMCode() &&
		(MPObjectFeature | MPSystemFeatures) != ((DatKop*)pvData)->dwFeat)
#else
	if ((ulMCode == DEX_GetOldUniqueIdentMCodeEx (hPr) &&
		(MPObjectFeature | MPSystemFeatures) != ((DatKop*)pvData)->dwFeat) ||
		ulMCode == DEX_GetObjGuidMCode (ulIdent))	// "Eindeutige Objektkennung" nicht kopieren

#endif // _TRiAS_VER < 0x0300
		return true;	// Text des Merkmals "Eltern-UniqueIdents" nur kopieren, wenn alle
						// Merkmale übernommen werden sollen

	if (!((DatKop*)pvData)->bGeoErr &&
		ulMCode == GetHeaderMCode (false, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT, ulIdent))
		return true;	// Text des Merkmals "Geometriefehler" nicht kopieren

// #WM021210
//	if (!((DatKop*)pvData)->bClear &&
//		ulMCode == GetHeaderMCode (false, IDS_GEOCLEAR, IDS_GEOCLEARKT, IDS_GEOCLEARLT, ulIdent))
//		return true;	// Text des Merkmals "Bereinigter Geometriefehler" nicht kopieren

//	if (!((DatKop*)pvData)->bSect &&
//		ulMCode == GetHeaderMCode (false, IDS_INTERSECT, IDS_INTERSECTKT, IDS_INTERSECTLT, ulIdent))
//		return true;	// Text des Merkmals "Verschnitt" nicht kopieren

string sMText;		// Merkmalstext
string sMTextAn;	// Merkmalstext bei Anhängen
	
	if (((DatKop*)pvData)->bOverWrite)	// Merkmalstext überschreiben
		ReadFeatureText (((DatKop*)pvData)->lONr1, ulMCode, TT_Objekt, sMText);
	else								// Merkmalstext anhängen
	{		
		ReadFeatureText (((DatKop*)pvData)->lONr2, ulMCode, TT_Objekt, sMText);
		ReadFeatureText (((DatKop*)pvData)->lONr1, ulMCode, TT_Objekt, sMTextAn);
		sMText += sMTextAn;
	}

	// UniqueIdent (evtl.) ersetzen durch ((DatKop*)pvData)->sUISubst
#if _TRiAS_VER < 0x0300
	if (ulMCode == DEX_GetUniqueIdentMCode())
#else
	if (ulMCode == DEX_GetUniqueIdentMCodeEx (hPr))
#endif // _TRiAS_VER < 0x0300
	{
		if (((DatKop*)pvData)->sUISubst.length() > 0)
			sMText = ((DatKop*)pvData)->sUISubst;
		else if (0 == sMText.length())
		{
		ResourceFile RF (pDLLName);
		ResString UniqueIdent (ResID (IDS_UIDENT, &RF), 100);

			Format (sMText, (char*)UniqueIdent.Addr(), ((DatKop*)pvData)->lONr2);
		}
	}

	if (sMText.length() > 0)
		WriteFeatureText (((DatKop*)pvData)->lONr2, ulMCode, TT_Objekt, sMText);
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// ulMCode-Merkmal des lONr-Objektes lesen und in sMText zurückgeben
bool _GEOMETR_EXPORT ReadFeatureText (long lONr, ulong ulMCode, int iTTyp, string& sMText)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (ulMCode != 0);
	_ASSERTE ((ulong)-1 != ulMCode);

	if (0 == lONr || -1 == lONr || 0 == ulMCode|| (ulong)-1 == ulMCode)
		return false;
	
TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);	// setzt u.a. TM.imaxLen = 0 und TM.pMText = 0
	TM.lTarget = lONr;
	TM.lMCode = ulMCode;		// MerkmalsCode
	TM.iTTyp = iTTyp;			// MerkmalsTyp
	DEX_GetTextMerkmal (TM);	// liefert mit TM.imaxLen = 0 und TM.pMText = 0 die aktuelle
								// Textlänge TM.imaxLen
	if (TM.imaxLen > 0)			// ein ungenutztes Merkmal hat Textlänge = -1
	{
		TM.imaxLen++;	// wegen Fehler bei Hartmut
		TM.pMText = new char [TM.imaxLen];	// zu lesender Merkmalstext
		if (! TM.pMText)
		{
			DEX_Error (RC_datbank, EC_NOMEMORY);
			return false;
		}
		DEX_GetTextMerkmal (TM);	// Merkmalstext lesen
		sMText = TM.pMText;
		DELETE_VEC (TM.pMText);
	}
	else if (sMText.length() > 0)
		sMText[0] = '\0';

//	DELETE_VEC (TM.pMText);		s.o.

	return true;

} // ReadFeatureText


// --------------------------------------------------------------------------------------------
// sMText in ulMCode-Merkmal des lONr-Objektes schreiben; für sMText == "" wird der
// Merkmalstext gelöscht
bool _GEOMETR_EXPORT WriteFeatureText (long lONr, ulong ulMCode, int iTTyp, string sMText)
{
	_ASSERTE (ulMCode != 0);
	_ASSERTE ((ulong)-1 != ulMCode);

#if _TRiAS_VER >= 0x0300
HPROJECT hPr = DEX_GetObjectProject (lONr);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		DEX_Error (RC_datbank, WC_FEATURE_ISRO);
		return false;
	}
#endif // _TRiAS_VER >= 0x0300

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (0 == lONr || -1 == lONr || 0 == ulMCode || (ulong)-1 == ulMCode)
		return false;

TARGETMERKMAL TM;

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = (LPARAM)lONr;
	TM.lMCode = ulMCode;
	if ("" != sMText)	// Merkmalstext schreiben
	{
		if (sMText.length() <= SHRT_MAX - 3)
		{
			TM.imaxLen = sMText.length();
			TM.pMText = (char*)sMText.c_str();
		}
		else
		{
			_ASSERTE (sMText.length() <= SHRT_MAX - 3);

		// Anfang von sMText, wenn sMText zu lang ist
		string sAnfang = sMText.substr (0, SHRT_MAX-7) + " ...";

			TM.imaxLen = sAnfang.length();
			TM.pMText = (char*)sAnfang.c_str();
		}
	}
	else				// Merkmalstext löschen
	{
		TM.imaxLen = 0;
		TM.pMText = 0;
	}

	TM.iTTyp = iTTyp;

	if (EC_OKAY != DEX_ModTextMerkmal (TM))
		return false;
	return true;

} // WriteFeatureText


// --------------------------------------------------------------------------------------------
// Texte der Merkmalscodes des lONr1-GeoObjektes werden zum lONr2-GeoObjekt kopiert; die in
// sUISubst übergebene Zeichenkette ersetzt den bisherigen UniqueIdent des lONr1-Objektes;
// der Merkmalstext wird überschrieben/angehangen (bOverWrite == true/false);
// der Merkmalstext von "Geometriefehler" wird nicht/kopiert bei bGeoErr == false/true;
bool _GEOMETR_EXPORT MerkmaleKopieren (long lONr1, long lONr2, string sUISubst,
					  bool bOverWrite, DWORD dwFeat, bool bGeoErr/*, bool bClear, bool bSect*/)	// #WM021012
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

struct DatKop Dat;	// in opdeklar.hxx definiert

	Dat.lONr1 = lONr1;
	Dat.lONr2 = lONr2;
	Dat.sUISubst = sUISubst;
	Dat.bOverWrite = bOverWrite;
	Dat.bGeoErr = bGeoErr;
//	Dat.bClear = bClear;	#WM021201
//	Dat.bSect = bSect;		#WM021210
	Dat.dwFeat = dwFeat;

// alle Merkmalscodes des lONr1-Objektes bereitstellen
ENUMLONGKEYEX ELK;

	ELK.eKey = lONr1;
	ELK.eFcn = (ENUMLONGKEYEXPROC) AlleMerkmale;
	ELK.ePtr = (void*) &Dat;
	ELK.eData = dwFeat;

bool bRet = DEX_EnumObjektMerkmaleEx (ELK);	// Enumeration der Merkmalscodes eines Objektes

// wenn für überhaupt noch kein DB-Objekt der UniqueIdent belegt ist, wurde der neue
// UniqueIdent-Text sUISubst auch nicht an das neue lONr2-Objekt weggeschrieben (17.11.98)
string sMText;	// Merkmalstext

#if _TRiAS_VER < 0x0300
	ReadFeatureText (lONr2, DEX_GetUniqueIdentMCode(), TT_Objekt, sMText);
	if ("" == sMText && sUISubst.length() > 0)
		WriteFeatureText (lONr2, DEX_GetUniqueIdentMCode(), TT_Objekt, sUISubst);
#else
HPROJECT hPr = DEX_GetObjectProject (lONr2);

	ReadFeatureText (lONr2, DEX_GetUniqueIdentMCodeEx (hPr), TT_Objekt, sMText);
	if ("" == sMText && sUISubst.length() > 0)
		WriteFeatureText (lONr2, DEX_GetUniqueIdentMCodeEx (hPr), TT_Objekt, sUISubst);
#endif // _TRiAS_VER < 0x0300

	return bRet;

} // MerkmaleKopieren


// --------------------------------------------------------------------------------------------
// den in pIdentListe selektierten Objektklassenschlüssel ermitteln
ulong _GEOMETR_EXPORT IdentErmitteln (ComboBox* pIdentListe)
{
	_ASSERTE (pIdentListe != 0);

ulong ulIdent = 0;
int iIndex = pIdentListe->GetCurrentIndex();

	if (-1 != iIndex)	// ein Objektklassenschlüssel wurde selektiert
	{
#if _TRiAS_VER < 0x0300
	// NICHT mit "string" arbeiten, weil dies bei GetString(sInBuff.c_str(),...) zu Problemen
	// führen kann (sInBuff.c_str() allociert keinen Speicher, sondern stellt nur den Pointer
	// bereit, wodurch es zur Beschreibung eines nicht allocierten Speicherbereiches kommt)
	char pcInBuff [_MAX_PATH] = { '\0' };

		pIdentListe->GetString (pcInBuff, iIndex, sizeof(pcInBuff));
		IdentFromClassX (pcInBuff, &ulIdent);
#else
	// Ident ist am jeweiligen Item mitgespeichert
		ulIdent = pIdentListe->GetItemData (iIndex);

// ASSERTS ausgeblendet, da ggf. '<Neue Objektklasse...>' selektiert wurde
//		_ASSERTE (ulIdent != 0);
//		_ASSERTE ((ulong)-1 != ulIdent);
#endif // _TRiAS_VER < 0x0300
	}

	if (0 != ulIdent && (ulong)-1 != ulIdent)	// nur wenn wirklich neu, dann selektierten
		DEX_SetLastIdent (ulIdent);		//  Objektklassenschlüssel TRiAS-weit bekanntgeben

	return ulIdent;

} // IdentErmitteln


// --------------------------------------------------------------------------------------------
// PBD durch Identifikator ulIdent mit Kurztext sKText temporär (bTemp == true) oder permanent
// (bTemp == false) ergänzen;
// bei Rückgabe von false konnte der Nachtrag wegen fehlendem freiem dynamischen Speicher nicht
// erfolgen
bool _GEOMETR_EXPORT IdentNachtragen (ulong ulIdent, string sKText, bool bTemp)
{
#if _TRiAS_VER >= 0x0300
	if (!bTemp &&				// permanente Speicherung gewollt, aber
		DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt
	{
		DEX_Error (RC_datbank, WC_CLASS_ISRO);
		return false;
	}
#endif // _TRiAS_VER >= 0x0300

int iKTLen = sKText.length() + 1;
PBDDATA PD;

	INITSTRUCT (PD, PBDDATA);
	PD.pbdTyp = 'i';			// Typ: Identifikator
	PD.pbdCode = ulIdent;		// neuer Identifikator
	PD.pbdKText = new char [iKTLen];
	if (! PD.pbdKText)
	{
		DEX_Error (RC_datbank, EC_NOMEMORY);
		return false;
	}
	memset (PD.pbdKText, '\0', iKTLen);	// Initialisierung
	PD.pbdTemp = bTemp;					// temporärer (true) bzw. permanenter (false) Eintrag
	PD.pbdKTextLen = iKTLen;

// Abschalten einer evtl. Fehlermeldung beim nachfolgenden Test, ob Identifikator schon in PBD
// vorhanden ist
ErrInstall EI (WC_NOIDENT);

	// Test, ob Identifikator schon vorhanden; wenn return-Wert nicht EC_OKAY ist, dann ist
	// Identifikator noch nicht vorhanden
	if (EC_OKAY != DEX_GetPBDData (PD))
	{
		strcpy (PD.pbdKText, sKText.c_str());
		DEX_ModPBDData (PD);  // Identifikator in PBD eintragen
	}
	DELETE_VEC (PD.pbdKText);
	return true;

} // IdentNachtragen


// --------------------------------------------------------------------------------------------
// Identifikator ulIdent aus PBD entfernen
ErrCode _GEOMETR_EXPORT IdentLoeschen (ulong ulIdent)
{
PBDDATA PD;

	INITSTRUCT (PD, PBDDATA);
	PD.pbdTyp = 'i';			// Typ: Identifikator
	PD.pbdCode = ulIdent;		// zu löschender Identifikator

ErrCode EC = DEX_DelPBDData (PD);

	return EC;

} // IdentLoeschen

// --------------------------------------------------------------------------------------------
// Funktion, die im DBHeader nachsieht, ob dort der gesucht Eintrag bereits existiert; wenn
// nicht, dann diesen erzeugen. Der MerkmalsCode wird zurückgegeben.
// bGenerate	der Eintrag soll im Header erzeugt werden, wenn er noch nicht existiert (true)
// uiResKey		ResourceID des HeaderKey's
// uiResKT		ResourceID des KurzTextes für das neue Merkmal
// uiResLT		ResourceID des Langtextes für das neue Merkmal
#if _TRiAS_VER < 0x0300
ulong _GEOMETR_EXPORT GetHeaderMCode (bool bGenerate, uint uiResKey, uint uiResKT, uint uiResLT)
{
ResourceFile RF (pDLLName);
GEODBHDRENTRY hdrEntry;
ulong ulRet = (ulong)-1;

	INITSTRUCT (hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID (uiResKey, &RF), 17), 16);
	hdrEntry.lphdrText = new char [65];
	hdrEntry.hdrTextLen = 64;

	if (EC_OKAY == DEX_ReadGeoDBHdrEntry (hdrEntry))
	{
		// HeaderEintrag existiert
		ulRet = atol (hdrEntry.lphdrText);
		if (0L == ulRet) ulRet = (ulong)-1;
	}
	else if (bGenerate)
	{
	// bei Bedarf neu generieren
	ulong ulMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (0 != ulMCode && (ulong)-1 != ulMCode)
		{										// und wegschreiben
			ltoa (ulMCode, hdrEntry.lphdrText, 10);
			if (EC_OKAY == DEX_WriteGeoDBHdrEntry (hdrEntry))
				ulRet = ulMCode;
			// in Pbd eintragen
			SaveMCodeInPbd (ulMCode, uiResKT, uiResLT);
		} 
	}
	DELETE_OBJ (hdrEntry.lphdrText);

	return ulRet;

} // GetHeaderMCode
#else

ulong _GEOMETR_EXPORT GetHeaderMCode (bool bGenerate, uint uiResKey, uint uiResKT,
									  uint uiResLT, ulong ulIdent)
{
ResourceFile RF (pDLLName);
GEODBHDRENTRY hdrEntry;
ulong ulRet = (ulong)-1;
char cbBuffer[65];
HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	_ASSERTE (NULL != hPr);		// Projekt für diesen Ident muß existieren
	INITSTRUCT (hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (ResID (uiResKey, &RF), 17), 16);
	hdrEntry.lphdrText = cbBuffer;
	hdrEntry.hdrTextLen = sizeof(cbBuffer)-1;

// der Eintrag muß im Header der Datenquelle passieren
	if (EC_OKAY == DEX_ReadHeaderEntry (hPr, hdrEntry))
	{
		// HeaderEintrag existiert
		ulRet = atol (hdrEntry.lphdrText);

		if (0 != ulRet)
		{
		MAPMCODETOHANDLE M2H;
		long lHandle = 0L;

			INITSTRUCT(M2H, MAPMCODETOHANDLE);
			M2H.lMCode = ulRet;
			M2H.plHandle = (INT_PTR *)&lHandle;
			M2H.fCreate = true;
			if (! DEX_MapOrCreateMCodeToHandle (hPr, M2H))
				return (ulong)-1;
			
			_ASSERTE (lHandle != 0);

			ulRet = lHandle;		// zu verwendendes Handle
		}
	}
	else if (bGenerate)
	{
	// bei Bedarf neu generieren
//	ulong ulMCode = DEX_GetUniqueSysMCodeEx (hPr);	// neuen MCode besorgen
	ulong ulMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (0 != ulMCode && (ulong)-1 != ulMCode)
		{										// und wegschreiben
			ltoa (ulMCode, hdrEntry.lphdrText, 10);
			if (EC_OKAY == DEX_WriteHeaderEntry (hPr, hdrEntry))
				ulRet = ulMCode;
			// in Pbd eintragen
			SaveMCodeInPbd (ulIdent, ulMCode, uiResKT, uiResLT);
		} 
	}
	return ulRet;
} // GetHeaderMCode
#endif // _TRiAS_VER < 0x0300


// --------------------------------------------------------------------------------------------
// Merkmal ulMCode in PBD generieren
#if _TRiAS_VER < 0x0300
bool SaveMCodeInPbd (ulong ulMCode, uint uiRes1, uint uiRes2)
{
ResourceFile RF (pDLLName);
ResString KText (ResID (uiRes1, &RF), 33);
ResString LText (ResID (uiRes2, &RF), 128);
PBDMERKMAL PM;
bool iResult = true;

	INITSTRUCT (PM, PBDMERKMAL);
	PM.pbdTyp = 'm';
	PM.pbdCode = ulMCode;
	PM.pbdKText = (char*) KText.Addr();
	PM.pbdLText = (char*) LText.Addr();	
	PM.pbdKTextLen = strlen (KText);
	PM.pbdLTextLen = strlen (LText);
	PM.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG;
	PM.ipbdMLen = 256;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (PM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (ulMCode);
	}
	
	return iResult; 

} // SaveMCodeInPbd

#else

bool SaveMCodeInPbd (ulong ulIdent, ulong ulMCode, uint uiRes1, uint uiRes2)
{
HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		DEX_Error (RC_datbank, WC_FEATURE_ISRO);
		return false;
	}

ResourceFile RF (pDLLName);
ResString KText (ResID (uiRes1, &RF), 33);
ResString LText (ResID (uiRes2, &RF), 128);
PBDMERKMALEX PM;
bool iResult = true;

	INITSTRUCT (PM, PBDMERKMALEX);
	PM.pbdTyp = 'm';
	PM.pbdCode = ulMCode;
	PM.pbdKText = (char*) KText.Addr();
	PM.pbdLText = (char*) LText.Addr();	
	PM.pbdKTextLen = strlen (KText);
	PM.pbdLTextLen = strlen (LText);
	PM.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG;
	PM.ipbdMLen = 256;
	PM.lIdent = ulIdent;

	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (PM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (ulMCode);
	}

	return iResult;
	
} // SaveMCodeInPbd

#endif // _TRiAS_VER < 0x0300


// --------------------------------------------------------------------------------------------
// Testen, ob das lONr-Objekt einen schweren Geometriefehler besitzt, d.h. ob das Merkmal
// "Geometriefehler" die Teilzeichenkette "F..: " beinhaltet;
// in cCode kann angegeben werden, welches Zeichen (1 ... 9) auf der auf 'F' folgenden Position
// stehen soll; damit kann also gezielt gefragt werden, ob das Merkmal "Geometriefehler" die
// Teilzeichenkette "F1", "F2", ... beinhaltet; mit cCode == '*' (default) wird nach ALLEN
// Teilzeichenketten "F..: " gefragt;
// return-Werte sind:
//	S_OK			Merkmal "Geometriefehler" existiert und beinhaltet die Teilzeichenkette
//                  "F..: "
//	S_FALSE			Merkmal "Geometriefehler" existiert nicht, ist leer oder beinhaltet nicht
//                  die Teilzeichenkette "F..: " (möglich sind noch "W..: " und "B..: " für
//                  Warnungen bzw. bereinigte Geometriefehler)
//  E_INVALIDARG    Parameter cCode nicht im gültigen Bereich
//	E_OUTOFMEMORY	nicht genügend dynamischer Speicher beim Lesen des Merkmals
HRESULT _GEOMETR_EXPORT FehlerhaftesObjekt (IExtendGeoRein* pIGeoRein, long lONr, char cCode)
{
#if _TRiAS_VER >= 0x0300
ulong ulIdent = DEX_GetObjIdent (lONr);
//HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	if (pIGeoRein && DEX_GetROModeIdent (ulIdent)) {	
	// Objektklasse schreibgeschützt
	BOOL bSucc = FALSE;		// assume error

		if (S_OK == pIGeoRein->WholeAnalysis_ONr (lONr, &bSucc) && bSucc)
			return S_FALSE;

		return S_OK;
	}
#endif // _TRiAS_VER >= 0x0300


// der Normalfall: Datenquelle bzw. Objektklasse nicht schreibgeschützt
	if ('*' != cCode && (cCode < '1' || cCode > '9'))
		return E_INVALIDARG;	// unklarer Parameter

// MerkmalsCode für Merkmal "Geometriefehler" aus DBHeader holen
ulong ulMCode = GetHeaderMCode (false, IDS_GEOERROR, IDS_GEOERRORKT, IDS_GEOERRORLT, DEX_GetObjIdent(lONr));

	if (0 == ulMCode || (ulong)-1 == ulMCode)
		return S_FALSE;	// Merkmal "Geometriefehler" existiert überhaupt nicht

string sMText;		// Merkmalstext

	if (!ReadFeatureText (lONr, ulMCode, TT_Objekt, sMText))
		return E_OUTOFMEMORY;	// nicht genügend dynamischer Speicher

size_t pos1 = 0, pos2;
	
	for (;;)
	{
		pos2 = sMText.find ('F', pos1);
		if (NPOS == pos2) break;		// kein 'F' (mehr) gefunden

	// sMText enthält irgendwo ein 'F'
	bool bCode = false;	// auf der auf 'F' folgenden Position in sMText steht cCode (true)

		if ('*' == cCode)
			bCode = ('1' <= sMText[pos2+1] && sMText[pos2+1] <= '9');
		else if ('1' <= cCode && cCode <= '9')
			bCode = (cCode == sMText[pos2+1]);

		if (bCode)	// das auf 'F' folgende Zeichen ist cCode
		{
			// Folgt danach ": " ?
			if (':' == sMText[pos2+2] && ' ' == sMText[pos2+3])
				return S_OK;		//  Objekt hat einen schweren Geometriefehler

			// bzw. Ziffer und ": " ?
			else if ('0' <= sMText[pos2+2] && sMText[pos2+2] <= '9' &&
					 ':' == sMText[pos2+3] && ' ' == sMText[pos2+4])
				return S_OK;		// Objekt hat einen schweren Geometriefehler

			// bzw. Kleinbuchstabe und ": " ?
			else if ('a' <= sMText[pos2+2] && sMText[pos2+2] <= 'z' &&
					 ':' == sMText[pos2+3] && ' ' == sMText[pos2+4])
				return S_OK;		// Objekt hat einen schweren Geometriefehler
			
			// bzw. Ziffer, Kleinbuchstabe und ": " ?
			else if ('0' <= sMText[pos2+2] && sMText[pos2+2] <= '9' &&
					 'a' <= sMText[pos2+3] && sMText[pos2+3] <= 'z' &&
					 ':' == sMText[pos2+4] && ' ' == sMText[pos2+5])
				return S_OK;		// Objekt hat einen schweren Geometriefehler
		}

		pos1 = pos2 + 1;
	}

	return S_FALSE;	// Merkmal ist nicht belegt, d.h. Objekt ist fehlerfrei bzw. Merkmal
					// enthält nicht die Zeichenkette "F..: " für einen schweren Geometriefehler

} // FehlerhaftesObjekt


//////////////////////////////////////////////////////////////////////////////
// 
//	S_OK			Merkmal "Geometriefehler" existiert und beinhaltet die Teilzeichenkette
//                  "F..: "
//	S_FALSE			Merkmal "Geometriefehler" existiert nicht, ist leer oder beinhaltet nicht
//                  die Teilzeichenkette "F..: " (möglich sind noch "W..: " und "B..: " für
//                  Warnungen bzw. bereinigte Geometriefehler)
//  E_INVALIDARG    Parameter cCode nicht im gültigen Bereich etc.
//	E_OUTOFMEMORY	nicht genügend dynamischer Speicher beim Lesen des Merkmals
HRESULT _GEOMETR_EXPORT FehlerhaftesObjektKorrigieren(
	IExtendGeoRein* pIGeoRein, long lONr, CoordTransX *pCT, EObjekt **ppEO, 
	char cCode)
{
HRESULT hr = FehlerhaftesObjekt(pIGeoRein, lONr, cCode);

	if (S_FALSE != hr) {
	// Objekt hat Geometriefehler
	HOBJECTS ulIdent = DEX_GetObjIdent (lONr);

		if (DEX_GetROModeIdent (ulIdent)) {	
		// Objektklasse schreibgeschützt
			if (NULL == pIGeoRein)
				return E_INVALIDARG;

			COM_TRY	{
			WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	

				THROW_FAILED_HRESULT(wIObj->InitObjGeometry (lONr));

			WObjektGeometrie OG (wIObj);

				if (SUCCEEDED(pIGeoRein->ReducedGeometryCleaning(OG))) {
				// kein Geometriefehler mehr
					if (NULL != ppEO && !IObjGeometrieInEObj (OG, *ppEO, pCT)) {
					// Fehler beim erzeugen des EObjekt's
						DELETE_OBJ (*ppEO);
						hr = E_UNEXPECTED;
					}
					else {
					// Fehler behoben
						hr = S_FALSE;
					}
				}

			} COM_CATCH;
		}
	}
	return hr;
}

// --------------------------------------------------------------------------------------------
// UniqueIdents's der plParONr-"Eltern"-Objekte (Anzahl: lObjAnz) an das neu gebildete
// lONr-Objekt abspeichern
bool _GEOMETR_EXPORT ParentsUniqueIdents (long lONr, long* plParONr, long lObjAnz)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (plParONr != 0);
	_ASSERTE (lObjAnz > 0);

bool bRet = true;	// return-Wert dieser Routine
bool bTRet;			// return-Wert von ReadFeatureText() bzw. WriteFeatureText()
string sOldMCode, sMCode;
#if _TRiAS_VER < 0x0300
ulong ulOldMCode = DEX_GetOldUniqueIdentMCode();
ulong ulMCode = DEX_GetUniqueIdentMCode();

	_ASSERTE (ulMCode != 0);
	_ASSERTE ((ulong)-1 != ulMCode);
#else
HPROJECT hPr = DEX_GetObjectProject (lONr);
ulong ulOldMCode = DEX_GetOldUniqueIdentMCodeEx (hPr);	// MCode in der Zieldatenquelle
#endif // _TRiAS_VER < 0x0300

	_ASSERTE (ulOldMCode != 0);
	_ASSERTE ((ulong)-1 != ulOldMCode);
	
typedef set<string, CStringComp> StringSet;
StringSet setUIdent;

/* Die Einbeziehung aller Vorfahren wird vorerst nicht gewünscht; aber ich gehe davon aus, daß
   das noch einmal anders werden wird (22.10.98, 13:40:17 Uhr)
	if (ulOldMCode > 0)
	{
	size_t pos1, pos2;	// Positionen im String sMCode
	size_t len = sMTrenn.lengt();

		for (long j = 0; j < lObjAnz; j++)
		{
			_ASSERTE (plParONr[j] > 0);

			pos1 = 0;

			bTRet = ReadFeatureText (plParONr[j], ulOldMCode, TT_Objekt, sMCode);
			if (! bTRet) bRet = false;

			// sMCode noch zerlegen, wenn er sMTrenn enthält
			for (;;)
			{
//				pos2 = sMCode.find_first_of (sMTrenn, pos1);
				pos2 = sMCode.find (sMTrenn, pos1);
				if (NPOS == pos2)
					break;		// sMTrenn nicht mehr gefunden
				setUIdent.insert (sMCode.substr(pos1, pos2-pos1));
				pos1 = pos2 + len;
			}
			setUIdent.insert (sMCode.substr(pos1));
		}
	}
*/

#if _TRiAS_VER < 0x0300
	if (0 != ulMCode && (ulong)-1 != ulMCode)
		for (long j = 0; j < lObjAnz; j++)
		{
			_ASSERTE (plParONr[j] != 0);
			_ASSERTE (plParONr[j] != -1);

			bTRet = ReadFeatureText (plParONr[j], ulMCode, TT_Objekt, sMCode);
			if (! bTRet) bRet = false;
			setUIdent.insert (sMCode);
		}
#else
	for (long j = 0; j < lObjAnz; j++)
	{
		_ASSERTE (plParONr[j] != 0);
		_ASSERTE (plParONr[j] != -1);

	HPROJECT hPr = DEX_GetObjectProject (plParONr[j]);
	ulong ulMCode = DEX_GetUniqueIdentMCodeEx (hPr);	// MCode in der Ausgangsdatenquelle

		if (0 == ulMCode || (ulong)-1 == ulMCode)
		{
			_ASSERTE (0 != ulMCode);
			_ASSERTE ((ulong)-1 != ulMCode);

			continue;
		}

		bTRet = ReadFeatureText (plParONr[j], ulMCode, TT_Objekt, sMCode);
		if (! bTRet) bRet = false;
		setUIdent.insert (sMCode);
	}
#endif // _TRiAS_VER < 0x0300

	// neuen OldUniqueIdent zusammenbasteln
	for (StringSet::iterator it = setUIdent.begin(); it != setUIdent.end(); it++)
	{
		if (sOldMCode.length() > 0) 
			sOldMCode += sMTrenn;
		sOldMCode += (*it);
	}

	// sOldMCode kann leer sein, sMCode aller beteiligten Objekte leer ist
	if (sOldMCode.length() > 0)
	{
		bTRet = WriteFeatureText (lONr, ulOldMCode, TT_Objekt, sOldMCode);
		if (! bTRet) bRet = false;
	}

	return bRet;

} // ParentsUniqueIdents


// --------------------------------------------------------------------------------------------
// Kurztext für Code ulCode (IdentCode, MerkmalsCode, ReltCode) des Typs iType
// ('i' - Identifikator, 'm' - Merkmal, 'r' - Relation) ermitteln
bool _GEOMETR_EXPORT GetKurzText (ulong ulCode, short iType, string& sKText)
{
	sKText = "";	// für den Fehlerfall

PBDDATA PD;
char cbBuffer[64] = { '\0' };

	INITSTRUCT(PD, PBDDATA);		// Initialisierung
	PD.pbdTyp = iType;				// Typ: 'i' - Identifikator, 'm' - Merkmal, 'r' - Relation
	PD.pbdCode = ulCode;			// IdentCode, MerkmalsCode, RelatCode
	PD.pbdKText = cbBuffer;
	PD.pbdKTextLen = sizeof(cbBuffer);

ErrCode EC = DEX_GetPBDData (PD);

	if (EC_OKAY != EC)
		return false;

	sKText = PD.pbdKText;
	return true;
} // GetKurzText


// --------------------------------------------------------------------------------------------
// neues Merkmal in der PBD erzeugen (falls noch nicht vorhanden)
ErrCode _GEOMETR_EXPORT CreateFeatureInPBD (ulong ulMCode, string sMText, short iMaxLen,
											bool bSystemMerkmal, bool bReadOnly, ulong ulIdent)
{
	_ASSERTE (0 != ulMCode);
	_ASSERTE ((ulong)-1 != ulMCode);

#if _TRiAS_VER >= 0x0300
HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	if (DEX_GetROModeFeatureEx (hPr, ulMCode))	// Objekteigenschaft schreibgeschützt
	{
		DEX_Error (RC_datbank, WC_FEATURE_ISRO);
		return WC_FEATURE_ISRO;
	}
#endif // _TRiAS_VER >= 0x0300

	_ASSERTE (sMText.length() > 0);
	_ASSERTE (iMaxLen > 0);

// Abschalten einer evtl. Fehlermeldung beim nachfolgenden Test, ob Merkmal schon in PBD
// vorhanden ist
ErrInstall EI (WC_NOMERKMAL);


#if _TRiAS_VER < 0x0300
PBDMERKMAL PM;

	INITSTRUCT (PM, PBDMERKMAL);
#else
PBDMERKMALEX PM;

	INITSTRUCT (PM, PBDMERKMALEX);
	PM.lIdent = ulIdent;
#endif // _TRiAS_VER < 0x0300

	PM.pbdTyp = 'm';			// Merkmal
	PM.pbdCode = ulMCode;

ErrCode EC = DEX_GetPBDData (PM);

	if (EC == EC_OKAY && iMaxLen <= PM.ipbdMLen)	// wenn bereits vorhanden,
		return EC_OKAY;								// dann zurück

	if (EC != EC_OKAY)		// noch nicht vorhanden
	{
	short iLen = 0;

		while (((iLen = sMText.length()) > 0) && (' ' == sMText[iLen-1]))
			sMText.remove (iLen-1);	// Text ggf. trimmen

		// LangText setzen
		iLen = sMText.length();
		if (iLen > iLangTextLen)		// LangText ggf. begrenzen
			sMText.remove (iLangTextLen);
		PM.pbdLTextLen = iLen;
		PM.pbdLText = (char*)sMText.c_str();

		// KurzText setzen
		iLen = sMText.length();
		if (iLen > iKurzTextLen)		// KurzText ggf. begrenzen
			sMText.remove (iKurzTextLen);
		PM.pbdKTextLen = iLen;
		PM.pbdKText = (char*)sMText.c_str();
		PM.ipbdMTyp = 'a';				// Objekt-Merkmal
		if (bSystemMerkmal)
			PM.ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
		if (bReadOnly)
			PM.ipbdMTyp |= PBDMERKMAL_READONLY;
	}

	// diese Länge ggf. max. Länge des Merkmals vergrößern
	PM.ipbdMLen = iMaxLen;


// Undo-Objekt erzeugen (über OLE)
LPUNDOREDOPBDDATA pIUndo = NULL;

HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL, CLSCTX_INPROC_SERVER,
							   IID_IUndoRedoPBDData, (LPVOID*)&pIUndo);

	if (SUCCEEDED(hr))		// Initialisierung eines Undo-Objektes
		hr = pIUndo->InitModify ((const PBDDATA *)&PM, NULL);
	if (FAILED(hr)) 
	{
		pIUndo->Release();
		pIUndo = NULL;
	}

	EC = DEX_ModPBDData (PM);
	if (EC_OKAY == EC) 
	{
		if (pIUndo) 
			DEX_AddUndoRedo (pIUndo);
	}
	if (pIUndo) 
		pIUndo->Release();

	if (EC == EC_OKAY)
		DEXN_PBDMCodeChanged (ulMCode);

	return EC;

} // CreateFeatureInPBD

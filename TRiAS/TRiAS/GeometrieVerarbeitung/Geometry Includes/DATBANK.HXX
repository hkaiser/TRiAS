// Funktionen für Arbeit mit Identifikator- und Merkmalsdatenbank
// File: DATBANK.HXX
// W. Mörtl

#if !defined(_DATBANK_HXX)
#define _DATBANK_HXX




///////////////////////////////////////////////////////////////////////////////////////////////
// Komparatorklasse für Strings
class CStringComp 
{
public:
_GEOMETR_ENTRY bool operator() (const string& slh, const string& srh) const;
};



///////////////////////////////////////////////////////////////////////////////////////////////
// Merkmal eines Objektes lesen
_GEOMETR_ENTRY bool ReadFeatureText (long lONr, ulong ulMCode, int iTTyp, string& sMText);

// Merkmal eines Objektes schreiben
_GEOMETR_ENTRY bool WriteFeatureText (long lONr, ulong ulMCode, int iTTyp, string sMText);

// Texte der Merkmalscodes des lONr1-GeoObjektes zum lONr2-GeoObjekt kopieren
_GEOMETR_ENTRY bool MerkmaleKopieren (long lONr1, long lONr2, string sUISubst,
								bool bOverWrite = true, DWORD dwFeat = MPObjectFeature,
								bool bGeoErr = false/*, bool bClear = false, bool bSect = false*/);	// #WM021210

// den in IdentListe markierten Objektklassenschlüssel ermitteln
_GEOMETR_ENTRY ulong IdentErmitteln (ComboBox* pIdentListe);

// PBD durch Identifikator ergänzen
_GEOMETR_ENTRY bool IdentNachtragen (ulong ulIdent, string sKText, bool bTemp = false);

// Identifikator ulIdent aus PBD entfernen
_GEOMETR_ENTRY ErrCode IdentLoeschen (ulong ulIdent);

#if _TRiAS_VER < 0x0300
// Funktion, die Im DBHeader nachsieht, ob dort der gesucht Eintrag bereits existiert
// neue Funktion auf die 'alte' mappen
_GEOMETR_ENTRY ulong GetHeaderMCode (bool bGenerate, uint uiResKey, uint uiResKT,
									 uint uiResLT);

_GEOMETR_ENTRY inline ulong GetHeaderMCode (bool bGenerate, uint uiResKey, uint uiResKT,
											uint uiResLT, ulong /*lIdent*/)
{
	return GetHeaderMCode (bGenerate, uiResKey, uiResKT, uiResLT);
}

// Eintrag für ViewLegMCode in PBD generieren
bool SaveMCodeInPbd (ulong ulMCode, uint uiRes1, uint uiRes2);

#else
// Funktion, die Im DBHeader nachsieht, ob dort der gesucht Eintrag bereits existiert
_GEOMETR_ENTRY ulong GetHeaderMCode (bool bGenerate, uint uiResKey, uint uiResKT, uint uiResLT,
									 ulong ulIdent);
// Merkmal ulMCode in PBD generieren
bool SaveMCodeInPbd (ulong ulIdent, ulong ulMCode, uint uiRes1, uint uiRes2);

#endif // _TRiAS_VER < 0x0300

// Testen, ob lONr-Objekt einen Geometriefehler besitzt
_GEOMETR_ENTRY HRESULT FehlerhaftesObjekt (IExtendGeoRein* pIGeoRein, long lONr,
										   char cCode = '*');

// Testen, ob lONr-Objekt einen Geometriefehler besitzt. Bei schreibgeschützten
// Datenquellen, wird versucht den fehler zu beheben und ggf. das korrigierte
// EObjekt geliefert.
_GEOMETR_ENTRY HRESULT FehlerhaftesObjektKorrigieren(
	IExtendGeoRein* pIGeoRein, long lONr, 
	CoordTransX *pCT = NULL, EObjekt **ppEO = NULL, char cCode = '*');

// Rückgabe des Klartextes für den Resource-ID uiResID
//_GEOMETR_ENTRY const char* GetString (uint uiResID);

// UniqueIdents's der "Eltern"-Objekte an das neu gebildete Objekt abspeichern
_GEOMETR_ENTRY bool ParentsUniqueIdents (long lONr, long* plParONr, long lObjAnz);

// Kurztext für Code ulCode des Typs iType ermitteln
_GEOMETR_ENTRY bool GetKurzText (ulong ulCode, short iType, string& sKText);

// neues Merkmal in der PBD erzeugen
_GEOMETR_ENTRY ErrCode CreateFeatureInPBD (ulong ulMCode, string sMText, short iMaxLen,
									  bool bSystemMerkmal, bool bReadOnly, ulong ulIdent = -1);

#endif  // _DATBANK_HXX

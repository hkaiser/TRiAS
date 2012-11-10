// Headerdatei fnr das Erstellen des ArcInfo-Formats.
// File: TRIASARC.HXX                           Stand vom 7. Mai 1993

#if !defined(_TRIASARC_HXX)
#define _TRIASARC_HXX

// Alle Exportfunktionen fnr ein Datenformat mnssen in einer DLL zusammen-
// gefaßt sein, wobei die jeweiligen Ordinalzahlen der Funktionsaufrufe 
// fnr alle Export-DLL's identisch sein mnssen.
//
// Folgende Funktionen sind (zumindest als Entry) bereitzustellen:
//
// 1. Beginn eines DatenExports
//      ErrCode XXXExportBegin (char *lpFileName, OFSTRUCT &of, Bool Overwrite);
//                                                                      @10
// 2. Ausgabe einer Kommentarinformation im jeweiligen Format
//      ErrCode XXXExportComment (OFSTRUCT &of, const char *CommentString); @11
//
// 3. Ausgabe von Informationen, die am Anfang der Datei stehen mnssen
//      ErrCode XXXExportHeader (OFSTRUCT &of, const char *HeaderInfo); @12
//
// 5. Ausgabe von Informationen, die den Inhalt dieses Exports betreffen
//      ErrCode XXXExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);     
//                                                                      @13
//
// 4. Alles nber ein Objekt ausgeben
//      ErrCode _pascal __export XXXExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF,
//                                                 RSTRUCT *, char *);
//                                                                      @14
// 5. Abschließende Informationen ausgeben
//      ErrCode XXXExportTrailer (OFSTRUCT &of, const char *TrailerInfo); @15
//
// 6. Beenden des DatenExports
//      ErrCode XXXExportEnd (OFSTRUCT &of);                            @16
//
// 7. Liefert Die Eigenschaften des Exportfilters
//      short XXXExportCaps (ExportCapability);                         @17
//
// 8. _bergibt bei jedem Aufruf die Beschreibung eines Identifikators
//    (einer Schicht)
//      ErrCode XXXExportIdentDescription (IdentDescription &);         @18
//
// 9. _bergibt bei jedem Aufruf die Beschreibung eines Merkmales
//      ErrCode XXXExportMerkmalDescription (MerkmalDescription &);     @19
//
// 10. Abbruch des Exports durch den Benutzer
//      ErrCode _pascal __export XXXExportBreak (OFSTRUCT &);    @20

// Prototypen fnr TRIAS(R) - Exportfunktionen --------------------------
extern "C" {
	// Von der DLL TRIASARC exportierte Funktionen
	ErrCode EXPORTFLT PASCAL ArcInfoExportBegin (char *lpFileName, OFSTRUCT &of, OutMode, HWND);
	ErrCode EXPORTFLT PASCAL ArcInfoExportComment (OFSTRUCT &of, const char *lpCommentString);
	ErrCode EXPORTFLT PASCAL ArcInfoExportHeader (OFSTRUCT &of, const char *lpHeaderString);
	ErrCode EXPORTFLT PASCAL ArcInfoExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);
	ErrCode EXPORTFLT PASCAL ArcInfoExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *);
	ErrCode EXPORTFLT PASCAL ArcInfoExportTrailer (OFSTRUCT &of, const char *lpTrailerString);
	ErrCode EXPORTFLT PASCAL ArcInfoExportEnd (OFSTRUCT &of);
	ErrCode EXPORTFLT PASCAL ArcInfoExportIdentDescription (IdentDescription &);
	ErrCode EXPORTFLT PASCAL ArcInfoExportMerkmalDescription (MerkmalDescription &);
	short EXPORTFLT PASCAL ArcInfoExportCaps (ExportCapability);
	ErrCode EXPORTFLT PASCAL ArcInfoExportBreak (OFSTRUCT &);

}       // extern "C"

//struct MFELD;
ErrCode ExportBeforeFirstData (pchar pPath);

// KK000307 -----------------------------
	ErrCode ShortBeginn(void);
	ErrCode ShortEnd(void);
// KK000331
	ErrCode CreateTempDaten(char *);
//---------------------------------------

pchar CheckName (pchar pName, short MaxSize, Bool Konvert = False);

// Konstanten
const short FileNameSize        = 8;    // max. Länge eines Dateinamens
const short FieldNameSize       = 10;   // max. Länge eines Feldnamens    
const short MaxColumn           = 80;   // max. 80 Zeichen pro Merkmalszeile
const short ArcSize             = 500;  // max. 500 Stützpunkte pro Arc
const short KurzTextLen			= 32;	// max. Länge eines KurzTextes	

// Limitierung der Merkmalsanzahl bei der Ausgabe
// KK030129
const long ARC_LIMIT_FEATURES = 64;		// max. Anzahl von Objektmerkmalen


#endif // _TRIASARC_HXX

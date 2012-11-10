// Headerdatei für Export in CADdy-ASCII-Format
// File: CADDYASC.HXX				Stand vom 6. Dezember 1993

#if !defined(_CADDYASC_HXX)
#define _CADDYASC_HXX

// Alle Exportfunktionen für ein Datenformat müssen in einer DLL zusammen-
// gefaßt sein, wobei die jeweiligen Ordinalzahlen der Funktionsaufrufe 
// für alle Export-DLL's identisch sein müssen.
//
// Folgende Funktionen sind (zumindest als Entry) bereitzustellen:
//
// 1. Beginn eines DatenExports
// 	ErrCode XXXExportBegin (char *lpFileName, OFSTRUCT &of, Bool Overwrite);
//									@10
// 2. Ausgabe einer Kommentarinformation im jeweiligen Format
// 	ErrCode XXXExportComment (OFSTRUCT &of, const char *CommentString); @11
//
// 3. Ausgabe von Informationen, die am Anfang der Datei stehen müssen
// 	ErrCode XXXExportHeader (OFSTRUCT &of, const char *HeaderInfo);	@12
//
// 5. Ausgabe von Informationen, die den Inhalt dieses Exports betreffen
//	ErrCode XXXExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);	
//									@13
//
// 4. Alles über ein Objekt ausgeben
//	ErrCode EXPORTFLT PASCAL AcadDxfExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF,
//						   RSTRUCT *, char *);
//									@14
// 5. Abschließende Informationen ausgeben
// 	ErrCode XXXExportTrailer (OFSTRUCT &of, const char *TrailerInfo); @15
//
// 6. Beenden des DatenExports
// 	ErrCode XXXExportEnd (OFSTRUCT &of);				@16
//
// 7. Liefert Die Eigenschaften des Exportfilters
//	short XXXExportCaps (ExportCapability);				@17
//
// 8. Übergibt bei jedem Aufruf die Beschreibung eines Identifikators
//    (einer Schicht)
//	ErrCode XXXExportIdentDescription (IdentDescription &);		@18
//
// 9. Übergibt bei jedem Aufruf die Beschreibung eines Merkmales
//	ErrCode XXXExportMerkmalDescription (MerkmalDescription &);	@19
//
// 10. Abbruch des Exports durch den Benutzer
//	ErrCode EXPORTFLT PASCAL AcadDxfExportBreak (OFSTRUCT &);	@20

// Prototypen für TRIAS(R) - CADdy-ASCII-Exportfunktionen -------------------
extern "C" {
// Von der DLL CADdyASC	exportierte Funktionen
    ErrCode EXPORTFLT PASCAL CadAscExportBegin (char *lpFileName, OFSTRUCT &of,
						OutMode, HWND);
    ErrCode EXPORTFLT PASCAL CadAscExportComment (OFSTRUCT &of, char *lpCommentString);
    ErrCode EXPORTFLT PASCAL CadAscExportHeader (OFSTRUCT &of, char *lpHeaderString);
    ErrCode EXPORTFLT PASCAL CadAscExportDescription (OFSTRUCT &of,
			      			char *lpKeyInfo, char *lpDescInfo);
    ErrCode EXPORTFLT PASCAL CadAscExportData (OFSTRUCT &of, GSTRUCT &GS,
					       MFELD *MF, RSTRUCT *, char *);
    ErrCode EXPORTFLT PASCAL CadAscExportTrailer (OFSTRUCT &of,
						const char *lpTrailerString);
    ErrCode EXPORTFLT PASCAL CadAscExportEnd (OFSTRUCT &of);
    ErrCode EXPORTFLT PASCAL CadAscExportIdentDescription (IdentDescription &);
    ErrCode EXPORTFLT PASCAL CadAscExportMerkmalDescription (MerkmalDescription &);
    short EXPORTFLT PASCAL CadAscExportCaps (ExportCapability);
    ErrCode EXPORTFLT PASCAL CadAscExportBreak (OFSTRUCT &);

    LPSTR FAR PASCAL  DtoA (LPSTR String, LPSTR Format, double Wert);
    BOOL FAR PASCAL  OutputResourceTemplate (int fh, int ResID);
}	// extern "C"

//  Hilfs-Funktionen
    ErrCode ExportLine (int fh, const char *pText);
    ErrCode ExportBildMasse (int fh);
    ErrCode ExportVersion (int fh);
    ErrCode ExportPunkt (int fh, double X, double Y);

// Konstanten
const short KurzTextLen = 32;

#endif // _CADDYASC_HXX

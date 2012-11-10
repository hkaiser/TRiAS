// Headerdatei für Export der DIRIS-Merkmalsinformationen ---------------------
// File: DIRISMKL.HXX

#if !defined(_DIRISMKL_HXX)
#define _DIRISMKL_HXX

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
// 	ErrCode XXXExportComment (OFSTRUCT &of, const char *CommentString);	@11
//
// 3. Ausgabe von Informationen, die am Anfang der Datei stehen müssen
// 	ErrCode XXXExportHeader (OFSTRUCT &of, const char *HeaderInfo);	@12
//
// 5. Ausgabe von Informationen, die den Inhalt dieses Exports betreffen
//	ErrCode XXXExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);	
//									@13
//
// 4. Alles über ein Objekt ausgeben
// 	ErrCode XXXExportData (OFSTRUCT &of, GeoObjekt &GO, MerkmalsFeld *MF);
//									@14
// 5. Abschließende Informationen ausgeben
// 	ErrCode XXXExportTrailer (OFSTRUCT &of, const char *TrailerInfo);	@15
//
// 6. Beenden des DatenExports
// 	ErrCode XXXExportEnd (OFSTRUCT &of);				@16
//
// 7: Liefert Die Eigenschaften des Exportfilters
//	short XXXExportCaps (ExportCapability);				@17
//

// Prototypen für DIRIS- MerkmalsExportfunktionen -----------------------------
extern "C" {
// Von der DLL DIRISMKL.FLT exportierte ExportFunktionen
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportBegin (char *lpFileName, OFSTRUCT &of, OutMode, HWND);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportComment (OFSTRUCT &of, const char *lpCommentString);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportHeader (OFSTRUCT &of, const char *lpHeaderString);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportTrailer (OFSTRUCT &of, const char *lpTrailerString);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportEnd (OFSTRUCT &of);
_EXPFLT_ENTRY short EXPORTFLT PASCAL DirisMKLExportCaps (ExportCapability);
_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL DirisMKLExportBreak (OFSTRUCT &);
}

#endif // _DIRISMKL_HXX

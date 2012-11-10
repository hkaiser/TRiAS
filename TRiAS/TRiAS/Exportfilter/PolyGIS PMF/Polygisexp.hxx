// Headerdatei für Export in PolyGIS-PMF-Austauschformat ----------------------------
// File: ATLASEXP.HXX

#if !defined(_POLYGISEXP_HXX)
#define _POLYGISEXP_HXX

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
// 5. Abschlieáende Informationen ausgeben
// 	ErrCode XXXExportTrailer (OFSTRUCT &of, const char *TrailerInfo);	@15
//
// 6. Beenden des DatenExports
// 	ErrCode XXXExportEnd (OFSTRUCT &of);				@16
//
// 7: Liefert Die Eigenschaften des Exportfilters
//	short XXXExportCaps (ExportCapability);				@17
//

// Prototypen für ATLAS*GIS - ASCII-Exportfunktionen --------------------------
//XX	extern "C" {
//XX		// Von der DLL ATLASBNA exportierte ExportFunktionen
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportBegin (char *lpFileName, OFSTRUCT &of, OutMode, HWND);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportComment (OFSTRUCT &of, const char *lpCommentString);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportHeader (OFSTRUCT &of, const char *lpHeaderString);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportTrailer (OFSTRUCT &of, const char *lpTrailerString);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportEnd (OFSTRUCT &of);
//XX		_EXPFLT_ENTRY short EXPORTFLT PASCAL AtlasBnaExportCaps (ExportCapability);
//XX		_EXPFLT_ENTRY ErrCode EXPORTFLT PASCAL AtlasBnaExportBreak (OFSTRUCT &);
//XX	}

#endif // _POLYGISEXP_HXX

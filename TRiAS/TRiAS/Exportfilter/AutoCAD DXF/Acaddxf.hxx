// Headerdatei für Export in AutoCAD-DXF-Format
// File: ACADDXF.HXX				Stand vom 28.4.1994

#if !defined(_ACADDXF_HXX)
#define _ACADDXF_HXX

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
//	ErrCode _pascal __export  AcadDxfExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF,
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
// 8. übergibt bei jedem Aufruf die Beschreibung eines Identifikators
//    (einer Schicht)
//	ErrCode XXXExportIdentDescription (IdentDescription &);		@18
//
// 9. übergibt bei jedem Aufruf die Beschreibung eines Merkmales
//	ErrCode XXXExportMerkmalDescription (MerkmalDescription &);	@19
//
// 10. Abbruch des Exports durch den Benutzer
//	ErrCode _pascal __export  AcadDxfExportBreak (OFSTRUCT &);	@20

// Prototypen für TRIAS(R) - DXF-Exportfunktionen --------------------------
//XX extern "C" {
// 	Von der DLL ACADDXF exportierte Funktionen
//XX 	ErrCode EXPORTFLT PASCAL AcadDxfExportBegin (char *lpFileName, OFSTRUCT &of, OutMode, HWND);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportComment (OFSTRUCT &of, const char *lpCommentString);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportHeader (OFSTRUCT &of, const char *lpHeaderString);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportDescription (OFSTRUCT &of, const char *lpKeyInfo, const char *lpDescInfo);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *, char *);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportTrailer (OFSTRUCT &of, const char *lpTrailerString);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportEnd (OFSTRUCT &of);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportIdentDescription (IdentDescription &);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportMerkmalDescription (MerkmalDescription &);
//XX     short EXPORTFLT PASCAL AcadDxfExportCaps (ExportCapability);
//XX     ErrCode EXPORTFLT PASCAL AcadDxfExportBreak (OFSTRUCT &);

//  weitere  Hilfs-Funktionen
//XX	    LPSTR FAR PASCAL DtoA (LPSTR String, LPCSTR Format, double Wert);
/*XX*/	    LPSTR DtoA (LPSTR String, LPCTSTR Format, double Wert);
    pchar OutputResourceTemplate (int ResID, int FileHandle = NULL);
//XX }	// extern "C"

//  Enum für mögliche AutoCAD Entities
    enum AcadTyp { A_Punkt, A_Linie, A_PLinie, A_PLinieClosed, A_Text };

//  Funktions-Prototypen
    ErrCode ExportRecord (int fh, int GruppenKode, const char *GruppenWert);
    ErrCode ExportLine (int fh, const char *pText);
    ErrCode ExportAttribute (int fh, AcadTyp Typ, GSTRUCT &GS);
    ErrCode ExportGeometrie (int fh, GSTRUCT &GS, AcadTyp Typ, long FirstIndex=0);
    ErrCode ExportPunkt (int fh, int GKx, int GKy, double X, double Y);
    ErrCode ExportHeaderSection (int fh);
    ErrCode ExportLineTable (int fh);
    ErrCode ExportBlocksSection (int fh);
    ErrCode ExportLayerTable (int fh);
    ErrCode ExportExtension (int fh);
    ErrCode ExportVisInfoTemplate (int fh);
    ErrCode ExportTextHoehe (int fh, long ID);
    ErrCode ExportTextDrehWinkel (int fh, long ID);
    ErrCode ExportText (int fh, pchar pText);
    //XX	ErrCode ExportComment (OFSTRUCT &of, const pchar lpCommentString);
    //XX	ErrCode ExportHeader (OFSTRUCT &of, const pchar lpHeaderString);
    //XX	ErrCode ExportDescription (OFSTRUCT &of, const char *, const char *lpDescString);
    //XX	ErrCode ExportIdentDescription (IdentDescription &ID);
    //XX	ErrCode ExportTrailer (OFSTRUCT &of, const char *);
    //XX	ErrCode ExportData (OFSTRUCT &of, GSTRUCT &GS, MFELD *MF);
    ErrCode ExportBeforeFirstData (int FileHandle);
// KK000217
	ErrCode ShortBeginn(void);
	ErrCode ShortEnd(void);

    //XX	ErrCode ExportBegin (char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hParWnd);
    //XX	ErrCode ExportBreak (OFSTRUCT &of);
    //XX	ErrCode ExportEnd (void);
    ErrCode ExportMerkmalDescriptions (MerkmalDescription &MD);

	pchar CheckUmlaute (pchar pText);               // dt. Umlaute ersetzen

// globale Konstanten
const short KurzTextLen = 32;		// max. Zeichenanzahl für Kurztexte
const short LayerNameLength = 31;   // max. Länge eines Layer-Namen
const short MinLayerSize = 2;		// min. Größe eines Layer-Namens
const short ColOffset = 5;	    	// Spalten-Offset für
				    				// Merkmals-Datei (ersten 5 Stellen f. ID)
const short LineTypeSize = 20;	    // max. Größe eines Linientypfeldes

#endif // _ACADDXF_HXX

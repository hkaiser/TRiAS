// Fehler- und RoutinenCodes fuer C++ - IRISWIN
// File: ERRCODES.HXX

#ifndef _ERRCODES_HXX
#define _ERRCODES_HXX

// FehlerCodes
enum ErrCode {
	WC_DATASOURCE_ISRO = 2000,		// Datenquelle ist schreibgesch¸tzt
	WC_METADATA_ISRO = 2001,		// Beschreibungsdaten sind schreibgesch¸tzt
	WC_CLASS_ISRO = 2002,			// Objektklasse (Tabelle) ist schreibgesch¸tzt
	WC_FEATURE_ISRO = 2003,			// Objekteigenschaft ist schreibgesch¸tzt

	// Warnungen
	WC_NOALIASNAMESFOUND = 1809,    // keine dBASE-Aliasnamen gefunden
	WC_ALIASNAMETOLONG = 1808,      // Aliasname zu lang
	WC_UNKOWNTOKEN = 1807,          // unbekanntes Token
	WC_MERKMALERROR = 1806,         // Merkmal-Attribut-Fehler
	WC_UNKOBJECTTYP = 1805,         // unbekannter Objekttyp
	WC_UNKMERKMTYP  = 1804,         // unbekannter Merkmalstyp
	WC_TOMANYLAYERS = 1803,         // zu viele Ebenen
	WC_TEXTTRUNCATED = 1802,        // Text wurde auf maximale L‰nge angepaﬂt
	WC_SYMBOLNOTFOUND = 1801,       // Symbolname nicht gefunden
	WC_DOUBLEGROUP = 1800,          // DQLParser: Klassifikationsgruppe doppelt

	WC_NOVISINFOPUNKT = 1720,       // keine VisInfo gegeben
	WC_NOVISINFOLINIE = 1719,
	WC_NOVISINFOFLAECHE = 1718,
	WC_NOVISINFOTEXT = 1717,

	WC_NOASSOCOBJ = 1713,   // Kein BezugsObjekt f¸r TO
	WC_CANTCREATEKO = 1712, // Kann KO nicht generieren
	WC_BADRCODE = 1711,     // Komplexobjekt soll mit unterschiedlichen 
	WC_NOTEXTMK = 1710,     // Bezugsobjekt hat keinen Text f¸r Textobjekt 
	WC_NOKO = 1709,         // KO besitzt keine Komplexrelation
	WC_MULTIPLEREL = 1708,  // Komplexobjekt besitzt mehrere Komplexrelationen nach unten
	WC_TEXTOBJ = 1707,      // Objekt ist Textobjekt
	WC_NOTEXTOBJ = 1706,    // Objekt ist kein TextObjekt
	WC_BADCMDSTRING = 1705, // Unbekannte Kommandozeilenoption
	WC_RECHNOTFOUND = 1704, // Keine Objekte entspr. Komplexkriterien gefunden
	WC_MISSMATCH = 1703,    // DBaseMerkmalsCode nicht gegeben
	WC_EXISTS = 1702,       // Datei existiert bereits
	WC_NOLIBRARY = 1701,    // Treiber nicht auffindbar
	WC_NOTEXT = 1700,       // Suchtext nicht gefunden
	WC_NOVALFOUND = 1699,   // Wert existiert nicht
	WC_NOTAPPEND = 1200,    // Append wird durch DXF-Export nicht unterst¸tzt
	WC_NOMERKMAL = 1014,    // Merkmal in PBD nicht vorhanden
	WC_NORELATION = 1013,   // Relation in PBD nicht vorhanden
	WC_NOIDENT = 1012,      // Ident in PBD nicht vorhanden
	WC_BADCOORD = 750,      // inkorrekte Koordinaten
	WC_BADMKTYP = 730,      // Falscher Merkmalstyp
	WC_NOTFOUND = 701,      // Schl¸ssel nicht gefunden
	WC_NOFIT = 704,         // Objekt auﬂerhalb des Fensters
	WC_RETURN = 700,        // Kein Fehler, aber != EC_OKAY
	WC_FORTI = 215,
	WC_FORTR = 214,
	WC_NORIG = 212,         // Keine topologischen Relationen vorhanden
	WC_FORT = 211,          // Fortsetzung notwendig
	WC_NOEOK = 203,         // Objekt ist kein Elementarobjekt
	EC_CORRECTED = 2,       // war Fehler, aber behoben
	WC_WDHLG = 1,           // Wiederholung erforderlich
// Kein Fehler
	EC_OKAY = 0,            // Kein Fehler
// Fehler
	EC_NOON = -10,          // Objekt mit dieser Nummer existiert nicht
	EC_BADLINK = -118,      // Fehler in Verbindungsliste
	EC_BADZVGO = -522,      // Falscher Verweis in die VGO
	EC_BADZKFK = -528,      // Falscher Verweis in die KFK
	EC_INVDBNAME = -700,    // ung¸ltiger DBName
	EC_NOOPEN = -701,       // DB nicht erˆffnet
	EC_INVADDR = -702,      // Satz existiert nicht
	EC_ACTIVATE = -709,     // Fehler beim aktivieren einer DB
	EC_NOSPACE = -711,      // Datei kann nicht vergrˆﬂert werden
	EC_SYSERROR = -712,     // this should not happen
	EC_NOMEMORY = -715,     // Kein Speicherplatz
	EC_NOFILE = -716,       // Kann Datei nicht erˆffnen
	EC_NOREAD = -719,       // LeseFehler
	EC_BADLEN = -727,       // DBHeader: Textfeld zu klein
	EC_DELRECORD = -728,    // DBSatz ist gelˆscht
	EC_INVPBDNAME = -730,   // PBDName ung¸ltig

	EC_ENTSK = -912,        // falscher SrukturCode
	EC_NOIDENT = -1012,     // Ident nicht in pbd vorhanden

// Erweiterung: Geometrie-Editierung (Mˆ)
// -> -1501 schon belegt
	EC_PKTEKOLLI = -1502,           // Punkte kollinear
	EC_RADIUS0 = -1503,				// Radius = 0

// Erweiterung: Geometrie-Bereinigung (Mˆ)
	EC_GEOFEHLER = -1510,           // Geometriefehler
	EC_APPROXIMATION = -1511,       // Fehler bei Approximation
	EC_BREAKAPPROX = -1512,         // Approximation wurde abgebrochen

// Erweiterung: Objektoperationen (Mˆ)
	EC_NOHAUPTMENU = -1520,         // Fenster-Handle nicht vom Hauptmen¸
	EC_NOUNTERMENU = -1521,         // Fenster-Handle nicht von einem Untermen¸
	EC_NULLPOINTER = -1522,         // Pointer des GeoObjektes == NULL
	EC_LISTELEER = -1523,           // ClipListe leer
	EC_NOLOCK = -1524,				// Zugriff auf Element der ClipListe nicht mˆglich
	EC_NOGEOOBJEKT = -1525,         // angebotenes Objekt ist weder Punkt, Linie noch Fl‰che
	EC_ERRMENUITEMID = -1526,       // MenuItemID nicht im erwarteten Bereich
	EC_ERRRUECK = -1527,            // R¸ckgabewert fehlerhaft
	EC_ZUGROSS = -1528,				// Anforderung f¸r new zu groﬂ
	EC_NOGEOANTRIAS = -1529,        // keine ‹bergabe der Geometrie an TRIAS mˆglich
	EC_NOUNION = -1530,				// keine Fl‰chenvereinigung mˆglich
	EC_NOANFANG = -1531,            // kein Anfangspunkt f¸r Fl‰chenvereinigung gefunden
	EC_NOINHALT = -1532,            // Fl‰cheninhalt = 0 bei Fl‰chenvereinigung

// Erweiterung: Buffering (Mˆ)
	EC_NOBUFFER = -1550,            // Buffer l‰ﬂt sich nicht bilden

	EC_NODBNAME = -1700,    // DB-Name nicht definiert
	EC_ILLPARS = -1701,     // Illegale(r) Parameter
	EC_NOPBDNAME = -1702,   // PBD-Name nicht in GeoDB-Header gegeben
	EC_BADWINMODE = -1703,  // Windows nicht im Protected Mode
	EC_BADCPU = -1704,      // Nicht mindestens 80286
	EC_NOTIMER = -1705,     // Kein Timer mehr verf¸gbar
	EC_NOTADIB = -1706,     // Bild ist nicht im DIB-Format (device independent format)
	EC_PALETTEFAULT = -1707, // Palette kann nicht generiert werden
	EC_BITMAPFAULT = -1708, // DevDepBitmap kann nicht generiert werden
	EC_BADPERSONALINFO = -1709,     // PersonalInfo ver‰ndert
	EC_NOHELPFILE = -1710,  // HilfeDatei nicht auffindbar
	EC_DLLACTIVE = -1711,   // Import-Semaphore gesetzt (kann nicht zwei ImportAktionen gleichzeitig ausfÅhren)
	EC_NOSCRIPTFILE = -1712,        // Kein ScripFile gegeben
	EC_BADPARAM = -1713,    // invalid Parameter in DBaseExpression
	EC_NOMERKMAL = -1714,   // Referenz auf nichtexistierendes Objektmerkmal in DBaseExpr
	EC_NOEXPRSPACE = -1715, // ExpressionBuffer zu klein
	EC_NODLLFUNCTION = -1716,       // DLL-Funktion nicht gefunden
	EC_NOSCRIPTBUFFER = -1717,      // Kein ScriptBuffer gegeben
	EC_NOSCRIPTINCLIPBOARD = -1718, // kein Script im ClipBoard
	EC_NODEXMESSAGE = -1719,        // kann keine WindowMessage registrieren

// 	Erweiterungen
	EC_EXTINITFAILURE = -1720,      // Kann Extension nicht laden

// 	DQLParser
	EC_BadWindowSpec = -1800,       // falsche GeometrieSpezifikation
	EC_BadInSpec = -1801,           // falsche SichtSpezifikation
	EC_BadForSpec = -1802,          // falsche Objektauswahl

	EC_BadKoeffs = -1803,           // entartete Transformationsmatrix
	
	EC_NOSCHNITTPUNKT = -1100,      // Geraden haben keinen Schnittpunkt
	EC_NOSCHWERPUNKT = -1101,       // Fl‰chenschwerpunkt nicht bestimmbar
	EC_LOCKERROR = -1104,           // Fehler beim Verriegeln eines Objektes
	
//  ODBC-Fehler
	EC_UNKN_FIELD_TYPE = -1150,     // unbekannter Feldtyp  
	EC_UNKN_FIELD_NAME = -1151,     // unbekannter Feldname
	EC_NO_QUERY_POSSIBLE = -1152,   // F¸r diesen Feldtyp ist keine Anfrage mˆglich
	EC_NOTABLENAME = -1153,         // Name der Tabelle nicht gefunden
	EC_NODSN = -1154,               // Data-Source-Name nicht gefunden
        EC_NOOPENDSN = -1155,           // Kann DataSource nicht îffnen
        EC_NOTABLEUPDATE = -1156,       // Tabelle kann nicht geÑndert werden
        EC_NOTABLEAPPEND = -1157,       // an Tabelle kînnen keine DatensÑtze angeh. werden

// 	ACAD-DXF-Export
	EC_LAYER = -1200,				// kann Ebenen-Info nicht erzeugen
	EC_NOLINETABLE = -1201,         // kann Linientabelle nicht laden
	EC_NOVISINFOTEMPLATE = -1202,	// kann Visualisierungs-Template nicht laden
	EC_NOSYMBOL = -1203,            // Symbol nicht gefunden

// 	Arc/Info-Export
	EC_NORESOURCE = -1204,          // Resource nicht gefunden                      
	EC_USERBREAK = -1205,           // Nutzerabbruch
	EC_UNKNOWNOBJTYP = -1206,       // unbekannter Objekttyp
	EC_NOIDDESCRIPTION = -1207,     // keine ID-Beschreibungen

// 	dBase-Extension     
	EC_SYNTAX = -1208,              // Syntax-Fehler

//  Komplex-Recherche-Extension
	EC_RECHAKTIV = -1209,           // Recherche bereits aktiv
	EC_NOTEXTFORMAT = -1210,        // Daten nicht im Textformat
	EC_NODATA = -1211,              // keine Daten vorhanden
	EC_BadIdentSpec = -1212,        // ung¸ltiger Identifikator
	EC_BadFileSpec = -1213,         // ung¸ltige dBASE-Datei
	EC_BaddBaseExpr = -1214,        // ung¸ltiger dBASE-Ausdruck
	EC_BadKeySpec = -1215,          // ung¸ltige Schl¸ssel-Anbindung
	EC_BadOutDevice = -1216,        // unbekanntes Ausgabeger‰t
	EC_BadOutForm = -1217,          // unbekanntes Ausgabeform
	EC_BadOutStat = -1218,          // ung¸ltige Ausgabeanweisung
	EC_UncompleteScript = -1219,    // unvollst. Script
	EC_BadGroupSpec = -1220,        // ung¸ltige Gruppen-Spec.
	EC_BadNumericFormat = -1221,    // ung¸ltiges Numeric-Format
	EC_NODBASEFILE = -1222,         // keine dBASE-Datei
	EC_NODBASECONNECT = -1223,      // keine dBASE-Relation

// 	Arc/Info-Import
	EC_NOTEMPFILE = -1250,          // kann temp. Datei nicht îffnen
	EC_NOSCALE = -1251,             // Skalierung nicht berechenbar
	EC_NOWRITE = -1252,             // Fehler beim Schreiben in Datei
	
// 	KonsistenzTest
	EC_BadGeometrie = -1300,        // fehlerhafte ObjektGeometrie
	
// CodeBase-Fehler
	e4close  = -1410,
	e4create = -1411,
	e4length = -1412,
	e4length_set = -1413,
	e4lock	 = -1414,
	e4open	 = -1415,
	e4read	 = -1416,
	e4remove = -1417,
	e4rename = -1418,
	e4seek	 = -1419,
	e4unlock = -1420,
	e4write  = -1421,
// Database Specific Errors
	e4data = -1422,
	e4field_name= -1423,  // Invalid field name
	e4field_type= -1424,
	e4record_len= -1425,
// Index File Specific Errors
	e4entry = -1426, // Tag entry not located
	e4index = -1427,
	e4tag_name = -1428,
	e4unique   = -1429, // Key is not unique
// Expression Errors
	e4comma_expected =  -1430,
	e4complete  = -1431,
	e4data_name = -1432,
	e4num_parms =  -1433,
	e4overflow= -1434, // Overflow while evaluating expression
	e4right_missing =  -1435,
	e4type	  =  -1436,
	e4unrec_function =  -1437,
	e4unrec_operator =  -1438,
	e4unrec_value =  -1439,
	e4unterminated =  -1440,
// Critical Errors
	e4info	  = -1441, // Unexpeceted information in internal variable
	e4memory  = -1442, // Out of memory
	e4new	  = -1443, // Unexpected 'new' call
	e4parm	  = -1444, // Unexpected parameter
	e4result  = -1445, // Unexpected result
// Fataler Fehler
	e4fatal   = -1446, 
};

// Routinennummern
enum RoutCode {
	RC_ErrInstall = 8073,   // ::err_install
//      RC_InstallHandler = 8095,       // errorTree :: InstallHandler
	RC_ErrorFunc = 8096,            // err_func
	RC_OPEN = 8500,         // DatenBasis :: Open
	RC_CDatenBasis = 8501,  // DatenBasis :: DatenBasis
	RC_opDatenBasis = 8502, // DatenBasis :: operator =
	RC_DBOGetGI = 8503,     // DatenBasisObjekt :: GetGI
	RC_DBCont = 8504,       // DatenBasis :: DBCont
	RC_AddPunkt = 8505,     // Kante :: AddPunkt
	RC_AddKante = 8506,     // Masche :: AddKante
	RC_ctKante = 8507,      // Kante :: Kante
	RC_asKante = 8508,      // Kante :: operator =
	RC_AddPunkt_K = 8509,   // Masche :: AddPunkt
	RC_SetDBName = 8510,    // DBTemplate :: SetDBName
	RC_ctMasche = 8511,     // Masche :: Masche
	RC_opMasche = 8512,     // Masche :: operator =
	RC_ctHeaderEntry = 8513,// HeaderEntry :: HeaderEntry
	RC_opHeaderEntry = 8514,// HeaderEntry :: operator =
	RC_EditLBSel = 8515,    // EditHeaderDialog :: ListBoxSel
	RC_SaveEntry = 8516,    // EditHeaderDialog :: SaveEntry
	RC_ReadHdrEntry = 8517, // EditHeaderDialog :: ReadHeaderEntry
	RC_GIWindow = 8518,     // GeoDB :: GIWindow
	RC_ctToolWind = 8519,   // ToolBox :: ToolBox
	RC_ObjRecherche = 8520, // IrisWind :: ObjektRecherche
	RC_ctOwnerDrawPBW = 8521, // OwnerDrawPBWindow :: OwnerDrawPBWindow
	RC_ctToolBox = 8522,    // ToolBox :: ToolBox
	RC_Activate = 8523,     // DBTemplate :: Activate
	RC_InitPBD = 8524,      // PBD_DB :: InitPBD
	RC_IdGetLangText = 8525,// PBD_Ident :: GetLangText
	RC_ctTextMerkmal = 8526,// TextMerkmal :: TextMerkmal
	RC_opTextMerkmal = 8527,// TextMerkmal :: operator=
	RC_TMGetText = 8528,    // TextMerkmal :: GetMerkmalsText
	RC_opIntMerkmal = 8529, // IntMerkmal :: operator=
	RC_GetLangText = 8530,  // PBD_Data :: GetLangText
	RC_GetMWert = 8531,     // PBD_Merkmal :: GetMerkmalsWert
	RC_ctMListe = 8532,     // MerkmalsListe :: MerkmalsListe
	RC_InitIrisApp = 8533,  // IrisWind :: InitIrisApp
	RC_IdSelBClk = 8534,    // IdentSelektion :: ButtonClick
	RC_GetRigObj = 8535,    // GeoDB :: GetRigObj
	RC_ButtonResponse = 8536, // ObjektInfo :: ButtonResponse
	RC_RigInfo = 8537,      // GeoDB :: RigInfo
	RC_RelInfo = 8538,      // GeoDB :: RelInfo
	RC_Start = 8539,        // App :: Start
	RC_ctProFile = 8540,    // ProFile :: ProFile
	RC_ctIdentifikator = 8541, // Identifikator :: Identifikator
	RC_InitDIB = 8542,      // BildObjekt :: InitDIB
	RC_ctBildObjekt = 8543, // BildObjekt :: BildObjekt
	RC_ctBildWindow = 8544, // BildWindow :: BildWindow
	RC_TextRecherche = 8545, // TextRechercheDlg :: TextRecherche
	RC_FindText = 8546,     // GeoDB :: FindText
	RC_ctIrisWind = 8547,   // IrisWind :: IrisWind
	RC_ctDatenBasisObjekt = 8548,   // DatenBasisObjekt :: DatenBasisObjekt
	RC_ctPrntSel = 8549,    // PrinterSelektion :: PrinterSelektion
	RC_ctIrisPrinter = 8550,        // IrisPrinter :: IrisPrinter
	RC_FillMerkmale = 8551, // ListObjektInfoDialog :: FillMerkmale
	RC_ctSchrankSchnulli = 8552,    // SchrankSchnulli :: SchrankSchnulli
	RC_LOIDlgSaveEntry = 8553,      // ListObjektInfoDialog :: SaveEntry
	RC_MSaveInDB = 8554,            // TextMerkmal :: SaveInDB
	RC_IdGetPen = 8555,             // Identifikator :: GetPen
	RC_IdGetBrush = 8556,           // Identifikator :: GetBrush
	RC_ctExportDlg = 8557,          // ExportDlg :: ExportDlg
	RC_doExport = 8558,             // doExport
// SichtenBehandlung
	RC_ctSicht = 8559,              // Sicht :: Sicht
	RC_GetSightTargets = 8560,      // Sicht :: GetSightTargets
	RC_FindTarget = 8561,           // Sicht :: FindTarget
	RC_DelTarget = 8562,            // Sicht :: DelTarget
	RC_GetSightNames = 8563,        // DatenBasisObjekt :: GetSightNames
	RC_ctMainIrisWind = 8564,       // MainIrisWind :: MainIrisWind
	RC_MakeDBWindow = 8565,         // MainIrisWind :: MakeDBWindow
	RC_ctObjInfo = 8566,            // ObjInfo :: ObjInfo
	RC_DelSight = 8567,             // Sicht :: DelSight
	RC_CopyToClipBoard = 8568,      // IrisWind :: CopyToClipBoard
	RC_IrisMenuCmd = 8569,          // IrisWind :: MenuCommand
	RC_ReadDBaseCodes = 8570,       // Profile :: ReadDBaseCodes
	RC_IdFilter = 8571,             // GeoDB :: IdFilter
	RC_IdFilterSicht = 8572,        // GeoDB :: IdFilter
	RC_IdFilterNew = 8573,          // GeoDB :: IdFilterNew
	RC_ctRStatus = 8574,            // RStatus :: RStatus
	RC_ExpandParams = 8575,         // ExpandParams
	RC_RechResults = 8576,          // IrisWind :: ShowOIRechResults
	RC_InitScriptDlg = 8577,        // InitScriptDlg
	RC_PrintGraphics = 8578,        // irisWind :: PrintGraphics
	RC_ShowOIDBaseInfo = 8579,      // ObjInfo :: ShowOIDBaseInfo
	RC_SetContKante = 8580,         // Kante :: SetCont
	RC_SetContMasche = 8581,        // Masche :: SetCont

	RC_ReadText = 8582,             // GeoDB :: ReadText
	RC_IdGetFont = 8583,            // Identifikator :: GetFont 

	RC_EditTextObjekt = 8584,       // EditTextObjektDialog :: ButtonClick
	RC_WriteText = 8585,            // GeoDB :: WriteText
	RC_ChangeText = 8586,           // GeoText :: ChangeText

	RC_MatrixEvalKoeffs = 8587,             // EvalKoeffs

	RC_ctPriorityEntry = 8588,      // PriorityEntry :: PriorityEntry
	RC_ctPrioritySelDlg = 8589,     // PrioritySelDlg :: PrioritySelDlg
	RC_FillWithPriorities = 8590,   // FillWithPriorities
	RC_FillResPrioTree = 8591,      // FillResPrioTree

	RC_ctColorListBox = 8600,       // OwnerDrawColorListBox
	RC_ctStyleComboBox = 8601,      // OwnerDrawFillStyleBox
	RC_PrintUsage = 8602,           // PrintUsage
	RC_ParseCmdString = 8603,       // ParseCmdString

	RC_ChangeIdVisInfo = 8604,      // IrisWind :: ChangeIdVisInfo 
	RC_VisInfoDlgEnd = 8605,        // VisInfoDlg :: ButtonClick

	RC_GetPalette = 8606,           // SightPalette :: GetPalette 
	RC_AddNewColorsToPalette = 8607,        // AddNewColorsToPalette
	RC_ctOwnerDrawComboBox = 8608,  // OwnerDrawComboBox :. OwnerDrawComboBox

	RC_ctAusschnittsDlg = 8609,     // AusschnittsDlg :: AusschnittsDlg
	RC_EvalKoeffs = 8610,           // AusschnittsDlg :: EvalKoeffs

	RC_EDName = 8611,               // ProFile :: EDName
	RC_GetObjRgn = 8612,            // Sicht :: GetObjRgn
	RC_SetObjRgn = 8613,            // Sicht :: SetObjRgn

	RC_doRechercheBuffer = 8614,    // ExtDirisWindow :: doRechercheBuffer
	RC_LoadListSel = 8615,          // ExtListDLLDlg :: ListBoxSel
	RC_RetrieveDLLName = 8616,      // ExtensionList :: RetrieveDLLName
	RC_UnLoadListSel = 8617,        // ExtUnListDLLDlg :: ListBoxSel

	RC_ctOwnerDrawListBox = 8618,   // OwnerDrawListBox :: OwnerDrawListBox
	RC_RetrieveObjInfo = 8619,      // ObjektInfo :: RetrieveObjInfo
	RC_ctObjInfoItem = 8620,        // ObjInfoItem :: ObjInfoItem
	RC_GetHeadLine = 8621,          // PrintLayoutDlg :: GetHeadLine

	RC_RetrieveORCode = 8622,       // RetrieveORCode
	RC_ctKomplexObjekt = 8623,      // KomplexObjekt :: KomplexObjekt
	RC_ctKomplexObjektIterator = 8624,      // KomplexObjektIterator :: KomplexObjektIterator
	RC_GeoTextIndText = 8625,       // GeoTextInd :: Text

	RC_FlushDB = 8626,              // Trias01 : db_flush
	RC_AddObject = 8627,            // KomplexObjekt :: AddObject
	RC_CreateKObject = 8628,        // ObjektInfo :: CreateKObject
	RC_MergeKObjects = 8629,        // ObjektListe :: MergeKObjects

	RC_SavePBDIdent = 8630,         // PBD_Ident :: SaveInPBD
	RC_DeletePBDIdent = 8631,       // PBD_Ident :: DeleteInPBD     

	RC_EQueryClose = 8632,          // ExtDirisWindow :: QueryClose
	RC_ctIDItem = 8633,             // IDItem :: IDItem
	RC_ctDelIdentDlg = 8634,        // DelIdentDlg :: DelIdentDlg

	RC_BeginTrans = 8635,           // DBTemplate :: BeginTransaction
	RC_BreakTrans = 8636,           // DBTemplate :: BreakTransaction
	RC_RestoreDB = 8637,            // DBTemplate :: Restore

	RC_ctRelation = 8638,           // ctor DBaseRelation

// KoordinatenTransformation
	RC_CTFAspect = 8639,
	RC_CTFDistance = 8640,
	RC_CTFTrans = 8641,
	RC_CTFInvTrans = 8642,

	RC_ctCTF = 8643,                // CoordTrans :: CoordTrans
	RC_CTFLoad = 8644,
	RC_CTFUnLoad = 8645,
	RC_CTFToValue = 8646,
	RC_CTFToString = 8647,

	RC_SichtGetCont = 8648,         // Sicht :: GetCont
	RC_SichtSetCont = 8649,         // Sicht :: SetCont

	RC_CTFRectangle = 8650,

	RC_QueryObjGeometrie = 8651,
	RC_EditTextObj = 8652,          // IrisWind :: EditTextObjekt

	RC_RenameSight = 8653,          // Sicht :: Rename

	RC_FillOneIdent = 8654,

	RC_SichtPutMiText = 8655,       // Sicht :: PutMiText
	RC_SichtGetMiText = 8656,       // Sicht :: GetMiText
	RC_SichtDelMiText = 8664,       // Sicht :: DelMiText

	RC_GetVOMMI = 8657,
	RC_GeoDBOpen = 8658,            // GeoDB :: Open

	RC_HdrWriteBack = 8659,         // HeaderEntry :: WriteBack
	RC_SetEntryText = 8660,         // HeaderEntry :: SetEntryText

	RC_CreateObjektInfo = 8661,     // ExtDirisWindow :: CreateObjektInfo

	RC_PutGeoObj = 8662,            // DBO :: PutGeoObj
	RC_ctMenuItem = 8663,           // MenuItem :: MenuItem
// 8664 belegt

	RC_SavePBDMerkmal = 8664,       // PBD_Merkmal :: SaveInPBD
	RC_DeletePBDMerkmal = 8665,     // PBD_Merkmal :: DeleteInPBD

	RC_RetrieveExtName = 8666,      // ExtensionList :: RetrieveExtName
	RC_SetActiveSightName = 8667,   // DatenBasisObjekt :: SetActiveSightName
	RC_DelGI = 8668,                // GeoDB :: DelGI

	RC_InsertObjectGeometrie = 8669,        // ObjClipExtension
	RC_ctObjClip = 8670,                    // ctObjClipboardViewer
	RC_InsertObjectMerkmale = 8671,         // ObjClipExtension
	RC_UnloadLocalExtensions = 8672,        // ExtDirisWindow :: UnloadLocalExtensions
	RC_BildListe = 8673,                    // BackGrnd.Ext

	RC_ctObjPropDlg = 8674,                 // ObjPropDlg :: ObjPropDlg
	RC_GenerateObjProps = 8675,             // ObjPropDlg :: GenerateObjProps

	RC_UnLoadExtension = 8676,              // ExtDirisWindow :: UnLoadExtension

	RC_CIdTreeAddIdent = 8677,              // CIdTree :: AddIdent

	RC_BGetRel = 8678,                      // BGetRel
	RC_BFindRel = 8679,                     // BFindRel
	
	RC_SetAttributesPunkt = 8680,           // Punkt :: SetAttributes
	RC_SetAttributesLinie = 8681,           // Linie :: SetAttributes
	RC_SetAttributesFlaeche = 8682,         // Flaeche :: SetAttributes
	RC_SetAttributesText = 8683,            // Text :: SetAttributes

	RC_AppIdle = 8664,                      // App :: Idle
	
	RC_ctDBDict = 8665,                     // __ctor
	RC_ReadDBD = 8666,                      // KreideClientWindow :: ReadDBD
	RC_pKeyType = 8667,
	RC_pKeyFieldType = 8668,
	RC_pKeyFileName = 8669,
	RC_pTargetFileName = 8670,
	RC_pFileType = 8671,
	RC_pTreeKeyFileName  = 8672,
	RC_ExpandWithName = 8673,
	RC_CreateKeyFile = 8674,
	RC_CreateTreeKeyFile = 8675,
	RC_CreateGeoTreeFile = 8676,
	RC_pFileName = 8677,
	RC_CreateDictionary = 8678,
	RC_CreatePWDFile = 8679,
	RC_CreateNewGeoDB = 8680,
	
	RC_ImportDlgFillCBox = 8681,
	RC_ImportDlgReadDesc = 8682,
		
	RC_StringDup = 8683,
	
// ------------------

	RC_ctExport = 8700,             // Funktionen f¸r Export
	RC_ExportBegin = 8701,
	RC_ExportHeader = 8702,
	RC_ExportTrailer = 8703,
	RC_ExportComment = 8704,
	RC_ExportData = 8705,
	RC_ExportEnd = 8706,
	RC_ExportLine = 8707,
	RC_ExportDescription = 8708,
	RC_ExportIdentDescription = 8709,
	RC_ExportMerkmalDescription = 8710,
	RC_ExportBreak = 8711,
	RC_ExportDBContainer = 8712,

	RC_DxfImport = 8719,			// AutoCAD-Import
	RC_ACADDXF = 8720,              // ACAD-DXF-Export
	RC_CADDYASC = 8721,             // CADdy-ASCII-Export
	RC_TRIASARC = 8722,             // Arc/Info-Export

//      Komplex-Recherche
	RC_GetMiText = 8723,            // GetMiText ()
	RC_GetContKomplexr = 8724,      // KomplexrExtension :: GetContainer ()
	RC_IdFilterNewKomplexr = 8725,  // KomplexrExtension :: IdFilterNew ()
	RC_IdFilterKomplexr = 8726,     // KomplexrExtension :: IdFilter ()
	RC_KomplexrOutObjList = 8727,   // KomplexrExtension :: _OutObjectList ()
	RC_KomplExtMenuC = 8728,        // KomplexrExtension :: MenuCommand ()
	RC_KomplexrClassify = 8729,     // KomplexrExtension :: _Classify ()
	RC_ReadDBaseRelations = 8730,   // ProFile :: ReadDBaseRelations
	RC_ctDBaseRel = 8731,           // DBaseRel :: DBaseRel
	RC_ExpdBaseExpr = 8732,         // DBaseExtension :: _ExpanddBaseExpr

	RC_DQLParser = 8800,            // DQLyyparse
	RC_doRecherche = 8801,          // doRecherche
	RC_ReadScript = 8802,           // ReadScript
	RC_GetRStatus = 8803,           // IrisWind :: GetRStatus 
	RC_FilterCheck = 8804,          // DB_Filter :: Check
	RC_dorechercheBuffer = 8805,    // ExtDirisWindow :: dorechercheBuffer

// PBD_DataTempTree
        RC_ctPBD_Data = 8806,           // PBD_Data :: PBD_Data

// MerkInfo
	RC_ctTextMerkInfo = 8807,       // TextMerkInfo :: TextMerkInfo
	RC_ctLongMerkInfo = 8808,       // LongMerkInfo :: LongMerkInfo
	RC_ctDoubleMerkInfo = 8809,     // DoubleMerkInfo :: DoubleMerkInfo 
	RC_GetMerkInfo = 8810,          // GetMerkInfo

// DirisExtensionVerwaltung
	RC_ctExtDirisWindow = 8811,     // ExtDirisWindow :: ExtDirisWindow
	RC_LoadExtension = 8812,        // Extension :: Load
	RC_ctExtension = 8813,          // Extension :: Extension
	RC_LoadAllExtensions = 8814,    // ExtDirisWindow :: LoadAllExtensions

// Relationen
	RC_GetRelCode = 8815,           // GetRelationsCodes
	RC_GetCodes = 8816,             // GetCodes
	RC_GetRelation = 8817,          // GetRelation
	RC_BDelRel = 8818,              // BRelDelete

	RC_ctStringDup = 8819,          // StringDup :: StringDup
        RC_AddToTempTree = 8820,        // PBD_Data :: AddTotempTree
	RC_dBaseDispatch = 8821,        // dBaseDispatch :: dBaseDispatch
	
	RC_opplGeoKrs = 10000,          // GeoKreis :: operator+
	RC_opplGeoPkt = 10001,          // GeoPunkt :: operator+
	RC_opplGeoKante = 10002,        // GeoKante :: operator+
	RC_opplGeoFlaeche = 10003,      // GeoFlaeche :: operator+
	RC_cpyKrsObj = 10004,           // KreisObj :: KreisObj (KreisObj &)
	RC_asKrsObj = 10005,            // KreisObj :: operator =
	RC_SchwPktMasche = 10006,       // Masche :: Schwerpunkt

//  Komplex-Recherche-Extension
	RC_KomplSetScript = 10016,      // KomplexrExtesnion :: _SetScriptName
	RC_KomplexrAddIdent = 10017,    // KomplexrExtesnion :: AddIdent
	RC_KomplexrFilterIdents = 10018, // KomplexrExtesnion :: FilterIdents
	RC_ctEntryExpression = 10019,    // EntryExpression :: EntryExpression
	RC_EntryExprGetExpression = 10020,// EntryExpression :: GetExpression
	RC_EntryExprCheck = 10021,      // EntryExpression :: _CheckExpression
	RC_EntryExprFieldListe = 10022, // EntryExpression :: _FillFieldListe
	RC_EntryExprListSel = 10023,    // EntryExpression :: ListBoxSel
	RC_EntryExprFieldInfo = 10024,  // EntryExpression :: _OutputFieldInfo
	RC_EntryExprListClk = 10025,    // EntryExpression :: ListBoxClk
	RC_ScriptDlgGenScript = 10027,  // StandScriptDialog :: _GenerateScript
	RC_ScriptDlgReadExpr = 10028,   // StandScriptDialog :: _ReadExpression
	RC_SelectdBaseFiles = 10029,    // SelectdBaseFiles
	RC_ScriptDlgEntryExpr = 10030,  // StandScriptDialog :: _EntrydBaseExpression
	RC_EntrydBaseExpression = 10030,// EntrydBaseExpression
	RC_DBaseFilesAddDataI = 10031,  // DBaseFiles :: AddDataIndex
	RC_StScriptOutAlias = 10032,    // StandScriptDialog :: _OutputAliasNames
	RC_ctSelectAliasNames = 10033,  // SelectAliasNames :: SelectAliasNames
	RC_DBaseFilesSetMaster = 10034,  // DBaseFiles :: SetMaster 

//  Trias-Arc/Info-Import-FilTer
	RC_ArcTriasSelectCover = 10100, // ArcTriasExtension :: _SelectCover
	RC_ArcTriasMenuCmd = 10101,     // ArcTriasExtension :: MenuCommand
	RC_ArcTriasCheckCover = 10102,  // ArcTriasExtension :: _CheckCover
	RC_HeaderOutScale = 10103,      // Header :: OutScaleAndOffset
	RC_TextObjectAddText = 10104,   // TextObject :: AddText
	RC_ParamsSetCoverName = 10105,  // Params :: SetCoverName
	RC_ArcTriasExtInit = 10106,     // ArcTriasExtension :: InitExtension
	RC_PointEntriesAddEntry = 10107,// PointEntries :: AddEntry
	RC_PointEntriesOutGeo = 10108,  // PointEntries :: OutGeo
	RC_ctLineEntries = 10109,       // LineEntries :: LineEntries
	RC_LineEntriesAddPos = 10110,   // LineEntries :: AddPos
	RC_LineEntriesAddNrCnt = 10111, // LineEntries :: AddNrCnt
	RC_LineEntriesGetCnt = 10112,   // LineEntries :: GetCnt
	RC_LineEntriesOutGeo = 10113,   // LineEntries :: OutGeo
	RC_LineEntriesOutGeom = 10114,  // LineEntries :: OutGeometrie
	RC_PalEntriesAddPalV = 10115,   // PalEntries :: AddPalVektor
	RC_PalEntriesAddPalE = 10116,   // PalEntries :: AddPalEntry
	RC_LineEntriesDelDoppPkt = 10117,// LineEntries :: DeleteDoppPkt
	RC_ctMerkmal = 10118,            // Merkmal :: Merkmal
	RC_MerkmalAddMerkmal = 10119,    // Merkmal :: AddMerkmal
	RC_MBaumOutTXM = 10120,          // MerkmalsBaum :: OutTXM
	RC_MBaumOutMerkmale = 10121,     // MerkmalsBaum :: OutMerkmale
	RC_MBaumReset = 10122,           // MerkmalsBaum :: Reset
	RC_MBaumReadNRec = 10123,        // MerkmalsBaum :: ReadNextRekord
	RC_PalEntriesOutGeo = 10124,     // PalEntries :: OutGeo
	RC_ArcTriasLex = 10125,          // ArcTriasLex
	RC_ArcTriasYacc = 10126,         // RC_ArcTriasYacc
	RC_GetFulldBaseName = 10127,     // aus Kompatibilit‰tsgr¸nden  
	RC_MBaumStoreTableName = 10128,  // MerkmalsBaum :: StoreTablename
	RC_MBaumDeleteUnvalids = 10129,  // MerkmalsBaum :: DeleteUnvalids
	RC_ctCTextDatInfo = 10130,               // CTextDatInfo :: CTextDatInfo
	RC_CTextDatListSetKopp = 10131, // CTextDatInfoList :: SetKoppelfeld            
	RC_CTextDatListSetMaster = 10132,// CTextDatInfoList :: SetMaster
	RC_CTextDatListOutCon = 10133,   // CTextDatInfoList :: OutputConnectInfos
	RC_GetRelCFreeRel = 10134,		 // CFreeRel :: GetRelation
	RC_OnFreeRelCRelDialog = 10135,	 // CRelDialog :: OnFreeRelation
	RC_OnInitDialogCFreeRel = 10136, // CFreeRel :: OnInitDialog
	RC_QueryStoreCRelDlg = 10137,	 // CRelDialog :: QueryStore	
	
//  TRiAS/ARC I/O - komprimiertes Format
	RC_ArcTriasTransfer = 10138, // ArcTriasExtension :: cpl_error


//  ODBC
	RC_OpenCDataBaseEx = 10200,              // CDataBaseEx :: Open 
	RC_NotifydBaseExt = 10201,               // CDBaseExtension :: Notification
	RC_ReadCodesdBaseExt = 10202,    // CDBaseExtension :: ReaddBaseCodes
	RC_ExpandExprdBaseExt = 10203,   // CDBaseExtension :: ExpandDBaseExpression 
	RC_ctCColumnObj = 10204,                 // CColumnObj :: CColumnObj    
	RC_DoFieldExRecSet = 10205,              // CResSet :: DoFieldExchange
	RC_GetPathDBaseProFile = 10206,  // DBaseProFile :: GetPath
	RC_GetFullNameDBaseProFile = 10207, // DBaseProFile :: GetFullDBaseName
	RC_GetSQLTypeColObjArr = 10208,  // CColumnObjArray :: GetSQLType
	RC_BuildWhereKlColObjArr = 10209,       // CColumnObjArray :: BuildWhereKlausel 
	RC_AddColInfoColObjArr = 10210,         //      CColumnObjArray :: AddColInfo
	RC_ShowDBaseInfoCDBaseExt = 10211,      // CDBaseExtension :: ShowDBaseInfo
	RC_ctViewLongChar = 10212,                      // CViewLongVar :: CViewLongVar
	RC_GetDataBaseCDataBaseExTree = 10213, // CDataBaseExTree :: GetDataBase
	RC_RefreshCRecSet = 10214,              // CRecSet :: Refresh
	RC_ctCFeldInfo = 10215,                 // CFeldInfo :: CFeldInfo
	RC_InstPropFuncdBaseExt = 10216,        // CDBaseExtension :: InstallActPropertyFunctions
	RC_RetrieveFieldInfo = 10217,           // RetrieveFieldInfo
	RC_GetFieldInfoColumnObjArr = 10218,    // CColumnObjArray :: GetFieldInfo
	RC_CommonODBC = 10219,					// ODBC-Funktion
	RC_GetRecCntCRecSet = 10220,			// CRecSet :: GetRecordCount
	RC_ctShowFile = 10221,					// ShowFile :: ShowFile
	RC_DarstShowFile = 10222,				// ShowFile :: Darstellen
	RC_CreateRelMenu = 10223,				// ShowFile :: CreateRelMenu
	RC_ReadRelShowFile = 10224,				// ShowFile :: ReadRelations
	RC_ShowOdbcWin = 10225,					// OdbcDispatch :: ShowOdbcWindowField
	RC_ReadSlavesCRelDialog = 10226,		// CRelDialog :: ReadSlaves
	RC_ReadActSlavesCRelDialog = 10227,		// CRelDialog :: ReadActSlaves
	RC_OnStoreCRelDialog = 10228,			// CRelDialog :: OnStore
	RC_ctCRelDialog = 10229,     			// CRelDialog :: CRelDialog
	RC_OnInitDialogCRelDialog = 10230,		// CRelDialog :: OnInitDialog
	RC_GetSQLTypeCRelDialog = 10231,		// CRelDialog :: GetSQLType
	RC_ctCConnect = 10232,       			// CConnect :: CConnect
	RC_OnInitDlgCConect = 10233,			// CConnect :: OnInitDialog
	RC_ReadActConCConnect = 10234,			// CConnect :: ReadActConnection
	RC_WantWhereKlauselCConnect= 10235,		// CConnect :: WantWhereKlausel
	RC_GetDataSources = 10236,				// GetDataSources
	RC_CreateDataBaseCODBCInfos = 10237,	// CODBCInfos :: CreateDataBase
	RC_OutputColumnNamesCODBCInfos = 10238,	// CODBCInfos :: OutputColumnNames
	RC_OutputTableInfoCODBCInfos = 10239,	// CODBCInfos :: OutputTableInfo
	RC_OutputColumnInfoCODBCInfos = 10240,	// CODBCInfos :: OutputColumnInfo
	RC_OutputDataBaseInfoCODBCInfos = 10241,// CODBCInfos :: OutputDataBaseInfo
	RC_OutputTableNamesCODBCInfos = 10242,	// CODBCInfos :: OutputTableNames
	RC_GetSQLTypeCColumns = 10243,			// CColumns :: GetSQLType
	RC_ChangeDriverCConnect = 10244, 		// CConnect :: ChangeDriver
        RC_OdbcExtension = 10245,                       
	RC_StoreActConnCConnect = 10246,		// CConnect :: StoreActConnection	
	RC_StandardDSNCConnect = 10247,			// CConnect :: StandardDataSource
	RC_QueryStoreCConnect = 10248,			// CConnect :: QueryStore
	RC_ChangeSelectionCRelDialog = 10249,	// CRelDialog :: ChangeSelection
	RC_CCreateWhereKlDlg = 10250,			// CCreateWhereKlDlg
	RC_CTableInfo = 10251,					// CTabelInfo
	RC_CTableInfoTree = 10252,				// CTableInfoTree
	RC_CheckWhereKlausel = 10253,			// CheckWhereKlausel	
	RC_ctCFreeRel = 10254,					// CFreeRel :: CFreeRel
	RC_StoreActConnCFreeRel = 10255,		// CFreeRel :: StoreActConn
	RC_QueryStoreCFreeRel = 10256,			// CFreeRel :: QueryStore
        RC_ChangeDriverCFreeRel = 10257,        // CFreeRel :: ChangeDriver
        RC_OdbcExtLex = 10258,                  // yyinput        
	RC_InstPropFunction = 10259,        	// CODBCObjectProperties :: InstallActPropertyFunctions
	RC_GetFieldLenColObjArr = 10260,  		// CColumnObjArray :: GetFieldLen
        RC_MenuCommandCOdbcExtension = 10261,           // COdbcExtension :: MenuCommand
        RC_OdbcImport = 10262,                          // ODBC-Import
        RC_Profile = 10263,                             // Klasse Profile
	RC_SetFieldInfoColumnObjArr = 10264,	// CColumnObjArray :: SetFieldInfo	
    
//  dBASE-Ext
	RC_ctDBaseProFile = 10270,				// DBaseProFile :: DBaseProFile
	RC_InitCAliasFieldNameTree = 10271,		// CAliasFieldNameTree :: Init
	RC_InitCAliasFieldName = 10272,			// CAliasFieldNameTree :: Init
	RC_GetAliasNameCAliasFieldNameTree = 10273, // CAliasFieldNameTree :: GetAliasName

//	Maschenbildung
	RC_Maschenbildung = 10280,				// f¸r ganze Erweiterung Maschenbildung
	
// CodeBase user routines
	RC_ctDB_Filter = 10300,		// DB_Filter :: DB_Filter
	RC_CheckDB_Filter = 10301,	// DB_Filter :: Check
	RC_CheckTagDB_Filter = 10302,	// DB_Filter :: CheckTag
	RC_dBase = 10303,		// f¸r alle CodeBase-Routinen
	RC_crCBobj = 10304,		// CreateCodeBaseObj
	RC_ShowDBaseWin = 10305, 	// dBaseDispatch :: ShowDBaseWindowField

// Geometrie-DLL (Mˆ)
	RC_Position = 15001,			// Punkt :: Position
	RC_PunktAufKante = 15002,		// Punkt :: PunktAufKante
	RC_EnthaltenInPunkt = 15003,    // Punkt :: EnthaltenIn
	RC_ctPunktVec = 15004,          // PunktVec :: PunktVec
	
	RC_geo_obj3 = 15010,			// geo_obj3.cxx
	RC_AddKonturTeil = 15011,       // Kante :: AddKonturTeil
	RC_AddKantenStueck = 15012,		// Kante :: AddKantenStueck1, AddKantenStueck2
	RC_SubPunktKante = 15013,       // Kante :: SubPunkt
	RC_EpsAufbereitung0 = 15014,    // Kante :: EpsAufbereitung0
	RC_EpsAufbereitung1 = 15015,    // Kante :: EpsAufbereitung1
	RC_EpsAufbereitung2 = 15016,    // Kante :: EpsAufbereitung2
	RC_SpezAddPunkt1 = 15017,		// Kante :: SpezAddPunkt1
	RC_SpezAddPunkt2 = 15018,		// Kante :: SpezAddPunkt2
	RC_InneliegenderPunkt = 15019,  // Kante :: InneliegenderPunkt
	RC_EnthaltenInKante = 15020,    // Kante :: EnthaltenIn
	RC_KantenLage = 15021,			// Kante :: KantenLage
	RC_LinienVereinigung = 15022,   // Kante :: LinienVereinigung
	
	RC_geo_obj4 = 15030,			// geo_obj4.cxx
	RC_SubKante = 15031,            // Masche :: SubKante
	RC_SubPunktMasche = 15032,      // Masche :: SubPunkt
	RC_EnthaltenInMasche = 15033,   // Masche :: EnthaltenIn
	RC_FlaechenVereinigung = 15035,	// Masche :: FlaechenVereinigung
	RC_FlaechenAufbau = 15034,		// Masche :: FlaechenAufbau
	RC_AddInseln2 = 15035,			// Masche :: AddInseln2	


	RC_geotrias = 15040,			// geotrias.cxx
	RC_GeometrieAnTRIAS = 15041,    // GeometrieAnTRIAS
	RC_datbank = 15042,				// datbank.cxx
	
	RC_zeichnen = 15043,			// zeichnen.cxx

	RC_EpsGemeinsamePunkte = 15051, // Strecke :: EpsGemeinsamePunkte
	
	RC_mark_obj = 15060,			// mark_obj.cxx
	RC_EpsEinfIndex = 15061,		// EpsEinfIndex
	RC_AddMarkPunkt = 15062,        // AddMarkPunkt
	RC_EpsEinfMarkPunkt = 15063,    // EinfMarkPunkt
	RC_EpsMarkierungModify1 = 15064,// EpsMarkierungModify1
	RC_EpsMarkierungModify2 = 15065,// EpsMarkierungModify2
	RC_SpezMarkierungModify = 15066,// SpezMarkierungModify
	RC_KantenPosit = 15067,         // KantenPosit
	RC_KanteZerlegt = 15068,		// KanteZerlegt
	RC_FlaecheZerlegt = 15069,		// FlaecheZerlegt
	RC_ctMarkPunktVec = 15070,      // MarkPunktVec :: MarkPunktVec
	
	RC_clipping = 15080,			// clipping.cxx
	RC_ClippingGeoKante = 15081,    // GeoKante :: Clipping
	RC_ClippingGeoFlaeche = 15082,  // GeoFlaeche :: Clipping
	RC_TeilKanten1 = 15083,			// TeilKanten1
	RC_TeilKanten2 = 15084,			// TeilKanten2
	RC_TeilFlaechen1 = 15085,		// TeilFlaechen1
	RC_TeilFlaechen2 = 15086,		// TeilFlaechen2
	
	RC_bufferin = 15100,			// bufferin.cxx
	RC_BufferElement2 = 15101,		// BufferElement2
	RC_BufferElement3 = 15102,		// BufferElement3
	RC_BufferElement4 = 15103,		// BufferElement4
	RC_BufferElement5 = 15104,		// BufferElement5
	RC_BufferingGeoKante = 15105,   // GeoKante :: Buffering
	RC_BufferingGeoFlaeche = 15106, // GeoFlaeche :: Buffering
	
	RC_geomtest = 15120,			// geomtest.cxx
	RC_OrientDreh = 15121,          // Masche :: OrientDreh
	
	RC_gerrlist = 15131,			// gerlist.cxx
	RC_badpunkt = 15132,			// badpunkt.cxx
	RC_doppunkt = 15133,			// doppunkt.cxx
	RC_spitze = 15134,				// spitze.cxx
	RC_kollinea = 15135,			// kollinea.cxx
	RC_offen = 15136,				// offen.cxx
	RC_umlauf = 15137,				// umlauf.cxx
	RC_selbinzi = 15138,			// selbinzi.cxx
	RC_kontinzi = 15139,			// kontinzi.cxx
	RC_insel_ex = 15140,			// insel_ex.cxx
	RC_insel_in = 15141,			// insel_in.cxx
	RC_entartet = 15142,			// entartet.cxx
	RC_objgeom = 15143,				// objgeom.cxx

	RC_dateiwah = 15150,			// dateiwah.cxx
	
// Erweiterung: Geometrie-Editierung (Mˆ)
	RC_geoedit = 15300,				// geoedit.cxx
	RC_MenuCommandEdit = 15301,		// GeoEditExtension :: MenuCommand
	RC_idbSpeichernEdit = 15302,    // GeoEditExtension :: idb_Speichern
	RC_geomodif = 15303,			// geomodif.cxx
	RC_SaveStuetzpunkt = 15304,		// GeoEditExtension :: SaveStuetzpunkt
	RC_neu_ein = 15305,				// neu_ein.cxx
	RC_StandardWerteEdit = 15306,   // NeuEdWerte :: StandardWerte
	RC_dragline_edit = 15307,		// dragline.cxx
	RC_KreisParameter = 15308,		// Kreis
	RC_geomtree = 15309,			// geomtree.cxx
	RC_DeleteKEdit = 15310,			// GeometrieBaum :: DeleteK
	RC_WiederholungKEdit = 15311,	// GeometrieBaum :: WiederholungK
	
// Erweiterung: Geometrie-Bereinigung (Mˆ)
	RC_MenuCommandRein = 15351,			// GeoReinExtension :: MenuCommand
	RC_WindowsNotificationRein = 15352,	// GeoReinExtension :: WindowsNotification
	RC_PolygonApproximation = 15353,	// PolygonApproximation
	RC_georein = 15354,					// georein.cxx

// Erweiterung: Topologische Relationen (Mˆ)
	RC_toporel = 15400,				// toporel.cxx
	RC_MenuCommandTopo = 15401,		// TopoRelatExtension :: MenuCommand
	RC_Relationen = 15402,			// TopoRelatExtension :: Relationen
	RC_ErgebnisAnzeigenTopo = 15403,// TopoRelatExtension :: ErgebnisAnzeigen
	RC_numtree = 15404,				// numtree.cxx
	RC_MemberKTopo = 15405,			// ObjNrBaum :: MemberK
	
// Erweiterung: Objektoperationen (Mˆ)
	RC_objoper = 15450,				// objoper.cxx
	RC_MenuCommandOp = 15451,       // ObjektOpExtension :: MenuCommand
	RC_ObjektSchneiden = 15452,     // ObjektOpExtension :: ObjektSchneiden
	RC_ClipListeAnTRIAS = 15453,    // ObjektOpExtension :: ClipListeAnTRIAS
	RC_op_ein = 15454,				// op_ein.cxx
	RC_SetIdent2 = 15455,			// Parameter :: SetIdent2
	
// Erweiterung: Buffering (Mˆ)
	RC_buffer = 15500,				// buffer.cxx
	RC_MenuCommandBuffer = 15501,   // BufferExtension :: MenuCommand
	RC_PufferBilden = 15502,        // BufferExtension :: PufferBilden
	RC_PufferEinfaerben = 15503,    // BufferExtension :: PufferEinfaerben
	RC_buff_ein = 15504,			// buff_ein.cxx
	
// Erweiterung: Raster (Mˆ)
	RC_raster = 15550,				// raster.cxx
	RC_MenuCommandRaster = 15551,   // RasterExtension :: MenuCommand
        RC_rast_ein = 15552,                    // rast_ein.cxx
        RC_StandardWerteRaster = 15553, // Parameter :: StandardWerte
        RC_VoreinstellungRaster = 15554,// Parameter :: Voreinstellung

// Erweiterung: Abstandsmessung (Mˆ)
	RC_abstand = 15600,				// abstand.cxx
	RC_MenuCommandAbstand = 15601,  // AbstandExtension :: MenuCommand
	RC_abst_aus = 15602,			// abst_aus.cxx
	RC_dragline_abst = 15603,		// dragline.cxx
	RC_dateiwae = 15604,			// dateiwae.cxx
};

#if !defined(E_IGNORE)
#define E_IGNORE        ((int (*)(int, int, ...))0)
#define E_DEFAULT       ((int (*)(int, int ,...))1)
#endif

#endif // _ERRCODES_HXX

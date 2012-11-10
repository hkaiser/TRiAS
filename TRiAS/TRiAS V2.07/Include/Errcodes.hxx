// Fehler- und RoutinenCodes fuer C++ - IRISWIN
// File: ERRCODES.HXX

#ifndef _ERRCODES_HXX
#define _ERRCODES_HXX

#define FACILITY_ERRCODE	0x0423
#define HRESULT_FROM_ERRCODE(x)   (x ? ((HRESULT) (((x) & 0x0000FFFF) | (FACILITY_ERRCODE << 16) | 0x80000000)) : 0 )

// FehlerCodes
enum ErrCode {
// Warnungen
	WC_NOALIASNAMESFOUND = 1809,    // keine dBASE-Aliasnamen gefunden
	WC_ALIASNAMETOLONG = 1808,      // Aliasname zu lang
	WC_UNKOWNTOKEN = 1807,          // unbekanntes Token
	WC_MERKMALERROR = 1806, // Merkmal-Attribut-Fehler
	WC_UNKOBJECTTYP = 1805, // unbekannter Objekttyp
	WC_UNKMERKMTYP  = 1804, // unbekannter Merkmalstyp
	WC_TOMANYLAYERS = 1803,		// zu viele Ebenen
	WC_TEXTTRUNCATED = 1802,  	// Text wurde auf maximale Länge angepaßt
	WC_SYMBOLNOTFOUND = 1801, 	// Symbolname nicht gefunden
	WC_DOUBLEGROUP = 1800,		// DQLParser: Klassifikationsgruppe doppelt

	WC_NOVISINFOPUNKT = 1720,	// keine VisInfo gegeben
	WC_NOVISINFOLINIE = 1719,
	WC_NOVISINFOFLAECHE = 1718,
	WC_NOVISINFOTEXT = 1717,

	WC_NOASSOCOBJ = 1713,	// Kein BezugsObjekt für TO
	WC_CANTCREATEKO = 1712,	// Kann KO nicht generieren
	WC_BADRCODE = 1711,	// Komplexobjekt soll mit unterschiedlichen 
	WC_NOTEXTMK = 1710,	// Bezugsobjekt hat keinen Text für Textobjekt 
	WC_NOKO = 1709,		// KO besitzt keine Komplexrelation
	WC_MULTIPLEREL = 1708,	// Komplexobjekt besitzt mehrere Komplexrelationen nach unten
	WC_TEXTOBJ = 1707,	// Objekt ist Textobjekt
	WC_NOTEXTOBJ = 1706,	// Objekt ist kein TextObjekt
	WC_BADCMDSTRING = 1705,	// Unbekannte Kommandozeilenoption
	WC_RECHNOTFOUND = 1704,	// Keine Objekte entspr. Komplexkriterien gefunden
	WC_MISSMATCH = 1703,	// DBaseMerkmalsCode nicht gegeben
	WC_EXISTS = 1702,	// Datei existiert bereits
	WC_NOLIBRARY = 1701,	// Treiber nicht auffindbar
	WC_NOTEXT = 1700,	// Suchtext nicht gefunden
	WC_NOVALFOUND = 1699,	// Wert existiert nicht
	WC_NOTAPPEND = 1200,	// Append wird durch DXF-Export nicht unterstützt
	WC_NOMERKMAL = 1014,	// Merkmal in PBD nicht vorhanden
	WC_NORELATION = 1013,	// Relation in PBD nicht vorhanden
	WC_NOIDENT = 1012,	// Ident in PBD nicht vorhanden
	WC_BADCOORD = 750,	// inkorrekte Koordinaten
	WC_BADDBVERSION = 733,	// Datenbank ist zu neu für uns
	WC_MCODEEXISTS = 732,	// MCode ist bereits belegt
	WC_BADMKTYP = 730,	// Falscher Merkmalstyp
	WC_NOTFOUND = 701,	// Schlüssel nicht gefunden
	WC_NOFIT = 704,		// Objekt außerhalb des Fensters
	WC_DUPLICATE = 702,	// Schlüssel doppelt (bei unique keys)
	WC_RETURN = 700,	// Kein Fehler, aber != EC_OKAY
	WC_FORTI = 215,
	WC_FORTR = 214,
	WC_NORIG = 212,		// Keine topologischen Relationen vorhanden
	WC_FORT = 211,		// Fortsetzung notwendig
	WC_NOON = 208,
	WC_NOEOK = 203,		// Objekt ist kein Elementarobjekt
	EC_CORRECTED = 2,	// war Fehler, aber behoben
	WC_WDHLG = 1,		// Wiederholung erforderlich
// Kein Fehler
	EC_OKAY = 0,		// Kein Fehler
// Fehler
	EC_STATUSERROR = -9,	// ObjektStatus falsch
	EC_NOON = -10,		// Objekt mit dieser Nummer existiert nicht
	EC_BADLINK = -118,	// Fehler in Verbindungsliste
	EC_DUPLLINK = -150,	// doppelter Satz in Verbindungsliste
	EC_BADZVGO = -522,	// Falscher Verweis in die VGO
	EC_BADZKFK = -528,	// Falscher Verweis in die KFK
	EC_INVDBNAME = -700,	// ungültiger DBName
	EC_NOOPEN = -701,	// DB nicht eröffnet
	EC_INVADDR = -702,	// Satz existiert nicht
	EC_ACTIVATE = -709,	// Fehler beim aktivieren einer DB
	EC_SYSERROR = -712,	// this should not happen
	EC_NOSPACE = -711,	// Datei kann nicht vergrößert werden
	EC_NOMEMORY = -715,	// Kein Speicherplatz
	EC_NOFILE = -716,	// Kann Datei nicht eröffnen
	EC_NOREAD = -719,	// LeseFehler
	EC_BADLEN = -727,	// DBHeader: Textfeld zu klein
	EC_DELRECORD = -728,	// DBSatz ist gelöscht
	EC_INVPBDNAME = -730,	// PBDName ungültig
	EC_OPENRO = -731,	// DB RO eröffnen
	EC_STG_CLOSEERROR = -734,	// Fehler bei IStorage::Commit
	EC_STG_READERROR = -735,	// Fehler beim Read
	EC_STG_WRITEERROR = -736,	// Fehler beim Write
	EC_STG_SEEKERROR = -737,	// Fehler beim Seek
	EC_STG_FLUSHERROR = -738,	// Fehler bei IStream::Commit
	
	EC_ENTSK = -912,	// falscher SrukturCode
	EC_NOIDENT = -1012,	// Ident nicht in pbd vorhanden

	EC_NODBNAME = -1700,	// DB-Name nicht definiert
	EC_ILLPARS = -1701,	// Illegale(r) Parameter
	EC_NOPBDNAME = -1702,	// PBD-Name nicht in GeoDB-Header gegeben
	EC_BADWINMODE = -1703,	// Windows nicht im Protected Mode
	EC_BADCPU = -1704,	// Nicht mindestens 80286
	EC_NOTIMER = -1705,	// Kein Timer mehr verfügbar
	EC_NOTADIB = -1706,	// Bild ist nicht im DIB-Format (device independent format)
	EC_PALETTEFAULT = -1707, // Palette kann nicht generiert werden
	EC_BITMAPFAULT = -1708,	// DevDepBitmap kann nicht generiert werden
	EC_BADPERSONALINFO = -1709,	// PersonalInfo verändert
	EC_NOHELPFILE = -1710,	// HilfeDatei nicht auffindbar
	EC_DLLACTIVE = -1711,	// Import-Semaphore gesetzt (kann nicht zwei ImportAktionen gleichzeitig ausfhren)
	EC_NOSCRIPTFILE = -1712,	// Kein ScripFile gegeben
	EC_BADPARAM = -1713,	// invalid Parameter in DBaseExpression
	EC_NOMERKMAL = -1714,	// Referenz auf nichtexistierendes Objektmerkmal in DBaseExpr
	EC_NOEXPRSPACE = -1715,	// ExpressionBuffer zu klein
	EC_NODLLFUNCTION = -1716,	// DLL-Funktion nicht gefunden
	EC_NOSCRIPTBUFFER = -1717,	// Kein ScriptBuffer gegeben
	EC_NOSCRIPTINCLIPBOARD = -1718,	// kein Script im ClipBoard
	EC_NODEXMESSAGE = -1719,	// kann keine WindowMessage registrieren

// Erweiterungen
	EC_EXTINITFAILURE = -1720,	// Kann Extension nicht laden

// DQLParser
	EC_BadWindowSpec = -1800,	// falsche GeometrieSpezifikation
	EC_BadInSpec = -1801,		// falsche SichtSpezifikation
	EC_BadForSpec = -1802,		// falsche Objektauswahl

	EC_BadKoeffs = -1803,		// entartete Transformationsmatrix

	EC_NOSCHNITTPUNKT = -1100,	// Geraden haben keinen Schnittpunkt
	EC_NOSCHWERPUNKT = -1101,	// Flächenschwerpunkt nicht bestimmbar
	EC_FALSEEXPR = -1102,		// Invalid DBase-Expression
	EC_FILTCHECK = -1103,		// Fehler bei DBaseFilterung
	EC_LOCKERROR = -1104,           // Fehler beim Verriegeln eines Objektes

// CodeBase-Fehler
	e4close  = -1110,
	e4create = -1111,
	e4length = -1112,
	e4length_set = -1113,
	e4lock	 = -1114,
	e4open	 = -1115,
	e4read	 = -1116,
	e4remove = -1117,
	e4rename = -1118,
	e4seek	 = -1119,
	e4unlock = -1120,
	e4write  = -1121,
// Database Specific Errors
	e4data = -1122,
	e4field_name= -1123,  // Invalid field name
	e4field_type= -1124,
	e4record_len= -1125,
// Index File Specific Errors
	e4entry = -1126, // Tag entry not located
	e4index = -1127,
	e4tag_name = -1128,
	e4unique   = -1129, // Key is not unique
// Expression Errors
	e4comma_expected =  -1130,
	e4complete  = -1131,
	e4data_name = -1132,
	e4num_parms =  -1133,
	e4overflow= -1134, // Overflow while evaluating expression
	e4right_missing =  -1135,
	e4type	  =  -1136,
	e4unrec_function =  -1137,
	e4unrec_operator =  -1138,
	e4unrec_value =  -1139,
	e4unterminated =  -1140,
// Critical Errors
	e4info	  = -1141, // Unexpeceted information in internal variable
	e4memory  = -1142, // Out of memory
	e4new	  = -1143, // Unexpected 'new' call
	e4parm	  = -1144, // Unexpected parameter
	e4result  = -1145, // Unexpected result
// Fataler Fehler
	e4fatal   = -1146, 


// ACAD-DXF-ExportFilter
	EC_LAYER = -1200,
	EC_NOLINETABLE = -1201,
	EC_NOVISINFOTEMPLATE = -1202,
	EC_NOSYMBOL = -1203,		// Symbol nicht gefunden

// TRIAS-Arc/Info-ExportFilter
	EC_NORESOURCE = -1204,          // Resource nicht gefunden                      
	EC_USERBREAK = -1205,           // Nutzerabbruch
	EC_UNKNOWNOBJTYP = -1206,       // unbekannter Objekttyp
	EC_NOIDDESCRIPTION = -1207,     // keine ID-Beschreibungen

// dBase-Extension     
	EC_SYNTAX = -1208,              // Syntax-Fehler

//  Komplex-Recherche-Extension
	EC_RECHAKTIV = -1209,           // Recherche bereits aktiv
	EC_NOTEXTFORMAT = -1210,        // Daten nicht im Textformat
	EC_NODATA = -1211,              // keine Daten vorhanden
	EC_BadIdentSpec = -1212,        // ungültiger Identifikator
	EC_BadFileSpec = -1213,         // ungültige dBASE-Datei
	EC_BaddBaseExpr = -1214,        // ungültiger dBASE-Ausdruck
	EC_BadKeySpec = -1215,          // ungültige Schlüssel-Anbindung
	EC_BadOutDevice = -1216,        // unbekanntes Ausgabegerät
	EC_BadOutForm = -1217,          // unbekanntes Ausgabeform
	EC_BadOutStat = -1218,          // ungültige Ausgabeanweisung
	EC_UncompleteScript = -1219,    // unvollst. Script
	EC_BadGroupSpec = -1220,        // ungültige Gruppen-Spec.
	EC_BadNumericFormat = -1221,    // ungültiges Numeric-Format

// KonsistenzTest
	EC_BadGeometrie = -1300,	// fehlerhafte ObjektGeometrie
};

// Routinennummern
enum RoutCode {
	RC_ErrInstall = 8073,	// ::err_install
	RC_InstallHandler1 = 8095,	// errorTree :: InstallHandler
	RC_ErrorFunc = 8096,		// err_func
	RC_OPEN = 8500,		// DatenBasis :: Open
	RC_CDatenBasis = 8501,	// DatenBasis :: DatenBasis
	RC_opDatenBasis = 8502,	// DatenBasis :: operator =
	RC_DBOGetGI = 8503,	// DatenBasisObjekt :: GetGI
	RC_DBCont = 8504,	// DatenBasis :: DBCont
	RC_AddPunkt = 8505,	// Kante :: AddPunkt
	RC_AddKante = 8506,	// Masche :: AddKante
	RC_ctKante = 8507,	// Kante :: Kante
	RC_asKante = 8508,	// Kante :: operator =
	RC_AddPunkt_K = 8509,	// Masche :: AddPunkt
	RC_SetDBName = 8510,	// DBTemplate :: SetDBName
	RC_ctMasche = 8511,	// Masche :: Masche
	RC_opMasche = 8512,	// Masche :: operator =
	RC_ctHeaderEntry = 8513,// HeaderEntry :: HeaderEntry
	RC_opHeaderEntry = 8514,// HeaderEntry :: operator =
	RC_EditLBSel = 8515,	// EditHeaderDialog :: ListBoxSel
	RC_SaveEntry = 8516,	// EditHeaderDialog :: SaveEntry
	RC_ReadHdrEntry = 8517, // EditHeaderDialog :: ReadHeaderEntry
	RC_GIWindow = 8518,	// GeoDB :: GIWindow
	RC_ctToolWind = 8519,	// ToolBox :: ToolBox
	RC_ObjRecherche = 8520,	// IrisWind :: ObjektRecherche
	RC_ctOwnerDrawPBW = 8521, // OwnerDrawPBWindow :: OwnerDrawPBWindow
	RC_ctToolBox = 8522,	// ToolBox :: ToolBox
	RC_Activate = 8523,	// DBTemplate :: Activate
	RC_InitPBD = 8524,	// PBD_DB :: InitPBD
	RC_IdGetLangText = 8525,// PBD_Ident :: GetLangText
	RC_ctTextMerkmal = 8526,// TextMerkmal :: TextMerkmal
	RC_opTextMerkmal = 8527,// TextMerkmal :: operator=
	RC_TMGetText = 8528,	// TextMerkmal :: GetMerkmalsText
	RC_opIntMerkmal = 8529,	// IntMerkmal :: operator=
	RC_GetLangText = 8530,	// PBD_Data :: GetLangText
	RC_GetMWert = 8531,	// PBD_Merkmal :: GetMerkmalsWert
	RC_ctMListe = 8532,	// MerkmalsListe :: MerkmalsListe
	RC_InitIrisApp = 8533,	// IrisWind :: InitIrisApp
	RC_IdSelBClk = 8534,	// IdentSelektion :: ButtonClick
	RC_GetRigObj = 8535,	// GeoDB :: GetRigObj
	RC_ButtonResponse = 8536, // ObjektInfo :: ButtonResponse
	RC_RigInfo = 8537,	// GeoDB :: RigInfo
	RC_RelInfo = 8538,	// GeoDB :: RelInfo
	RC_Start = 8539,	// App :: Start
	RC_ctProFile = 8540,	// ProFile :: ProFile
	RC_ctIdentifikator = 8541, // Identifikator :: Identifikator
	RC_InitDIB = 8542,	// BildObjekt :: InitDIB
	RC_ctBildObjekt = 8543,	// BildObjekt :: BildObjekt
	RC_ctBildWindow = 8544,	// BildWindow :: BildWindow
	RC_TextRecherche = 8545, // TextRechercheDlg :: TextRecherche
	RC_FindText = 8546,	// GeoDB :: FindText
	RC_ctIrisWind = 8547,	// IrisWind :: IrisWind
	RC_ctDatenBasisObjekt = 8548,	// DatenBasisObjekt :: DatenBasisObjekt
	RC_ctPrntSel = 8549,	// PrinterSelektion :: PrinterSelektion
	RC_ctIrisPrinter = 8550,	// IrisPrinter :: IrisPrinter
	RC_FillMerkmale = 8551,	// ListObjektInfoDialog :: FillMerkmale
	RC_ctSchrankSchnulli = 8552,	// SchrankSchnulli :: SchrankSchnulli
	RC_LOIDlgSaveEntry = 8553,	// ListObjektInfoDialog :: SaveEntry
	RC_MSaveInDB = 8554,		// TextMerkmal :: SaveInDB
	RC_IdGetPen = 8555,		// Identifikator :: GetPen
	RC_IdGetBrush = 8556,		// Identifikator :: GetBrush
	RC_ctExportDlg = 8557,		// ExportDlg :: ExportDlg
	RC_doExport = 8558,		// doExport
// SichtenBehandlung
	RC_ctSicht = 8559,		// Sicht :: Sicht
	RC_GetSightTargets = 8560,	// Sicht :: GetSightTargets
	RC_FindTarget = 8561,		// Sicht :: FindTarget
	RC_DelTarget = 8562,		// Sicht :: DelTarget
	RC_GetSightNames = 8563,	// DatenBasisObjekt :: GetSightNames
	RC_ctMainIrisWind = 8564,	// MainIrisWind :: MainIrisWind
	RC_MakeDBWindow = 8565,		// MainIrisWind :: MakeDBWindow
	RC_ctObjInfo = 8566,		// ObjInfo :: ObjInfo
	RC_DelSight = 8567,		// Sicht :: DelSight
	RC_CopyToClipBoard = 8568,	// IrisWind :: CopyToClipBoard
	RC_IrisMenuCmd = 8569,		// IrisWind :: MenuCommand
	RC_ReadDBaseCodes = 8570,	// Profile :: ReadDBaseCodes
	RC_IdFilter = 8571,		// GeoDB :: IdFilter
	RC_IdFilterSicht = 8572,	// GeoDB :: IdFilter
	RC_IdFilterNew = 8573,		// GeoDB :: IdFilterNew
	RC_ctRStatus = 8574,		// RStatus :: RStatus
	RC_ExpandParams = 8575,		// ExpandParams
	RC_RechResults = 8576,		// IrisWind :: ShowOIRechResults
	RC_InitScriptDlg = 8577,	// InitScriptDlg
	RC_PrintGraphics = 8578,	// irisWind :: PrintGraphics
	RC_ShowOIDBaseInfo = 8579,	// ObjInfo :: ShowOIDBaseInfo
	RC_SetContKante = 8580,		// Kante :: SetCont
	RC_SetContMasche = 8581,	// Masche :: SetCont

	RC_ReadText = 8582,		// GeoDB :: ReadText
	RC_IdGetFont = 8583,		// Identifikator :: GetFont 

	RC_EditTextObjekt = 8584,	// EditTextObjektDialog :: ButtonClick
	RC_WriteText = 8585,		// GeoDB :: WriteText
	RC_ChangeText = 8586,		// GeoText :: ChangeText

	RC_MatrixEvalKoeffs = 8587,		// EvalKoeffs

	RC_ctPriorityEntry = 8588,	// PriorityEntry :: PriorityEntry
	RC_ctPrioritySelDlg = 8589,	// PrioritySelDlg :: PrioritySelDlg
	RC_FillWithPriorities = 8590,	// FillWithPriorities
	RC_FillResPrioTree = 8591,	// FillResPrioTree

	RC_VerifyIdent = 8592,		// VerifyIdent

	RC_ctColorListBox = 8600,	// OwnerDrawColorListBox
	RC_ctStyleComboBox = 8601,	// OwnerDrawFillStyleBox
	RC_PrintUsage = 8602,		// PrintUsage
	RC_ParseCmdString = 8603,	// ParseCmdString

	RC_ChangeIdVisInfo = 8604,	// IrisWind :: ChangeIdVisInfo 
	RC_VisInfoDlgEnd = 8605,	// VisInfoDlg :: ButtonClick

	RC_GetPalette = 8606,		// SightPalette :: GetPalette 
	RC_AddNewColorsToPalette = 8607,	// AddNewColorsToPalette
	RC_ctOwnerDrawComboBox = 8608,	// OwnerDrawComboBox :. OwnerDrawComboBox

	RC_ctAusschnittsDlg = 8609,	// AusschnittsDlg :: AusschnittsDlg
	RC_EvalKoeffs = 8610,		// AusschnittsDlg :: EvalKoeffs

	RC_EDName = 8611,		// ProFile :: EDName
	RC_GetObjRgn = 8612,		// Sicht :: GetObjRgn
	RC_SetObjRgn = 8613,		// Sicht :: SetObjRgn

	RC_doRechercheBuffer = 8614,	// ExtDirisWindow :: doRechercheBuffer
	RC_LoadListSel = 8615,		// ExtListDLLDlg :: ListBoxSel
	RC_RetrieveDLLName = 8616,	// ExtensionList :: RetrieveDLLName
	RC_UnLoadListSel = 8617,	// ExtUnListDLLDlg :: ListBoxSel

	RC_ctOwnerDrawListBox = 8618,	// OwnerDrawListBox :: OwnerDrawListBox
	RC_RetrieveObjInfo = 8619,	// ObjektInfo :: RetrieveObjInfo
	RC_ctObjInfoItem = 8620,	// ObjInfoItem :: ObjInfoItem
	RC_GetHeadLine = 8621,		// PrintLayoutDlg :: GetHeadLine

	RC_RetrieveORCode = 8622,	// RetrieveORCode
	RC_ctKomplexObjekt = 8623,	// KomplexObjekt :: KomplexObjekt
	RC_ctKomplexObjektIterator = 8624,	// KomplexObjektIterator :: KomplexObjektIterator
	RC_GeoTextIndText = 8625,	// GeoTextInd :: Text

	RC_FlushDB = 8626,		// Trias01 : db_flush
	RC_AddObject = 8627,		// KomplexObjekt :: AddObject
	RC_CreateKObject = 8628,	// ObjektInfo :: CreateKObject
	RC_MergeKObjects = 8629,	// ObjektListe :: MergeKObjects

	RC_SavePBDIdent = 8630,		// PBD_Ident :: SaveInPBD
	RC_DeletePBDIdent = 8631,	// PBD_Ident :: DeleteInPBD	

	RC_EQueryClose = 8632,		// ExtDirisWindow :: QueryClose
	RC_ctIDItem = 8633,		// IDItem :: IDItem
	RC_ctDelIdentDlg = 8634,	// DelIdentDlg :: DelIdentDlg

	RC_BeginTrans = 8635,		// DBTemplate :: BeginTransaction
	RC_BreakTrans = 8636,		// DBTemplate :: BreakTransaction
	RC_RestoreDB = 8637,		// DBTemplate :: Restore

	RC_ctRelation = 8638,		// ctor DBaseRelation

// KoordinatenTransformation
	RC_CTFAspect = 8639,
	RC_CTFDistance = 8640,
	RC_CTFTrans = 8641,
	RC_CTFInvTrans = 8642,

	RC_ctCTF = 8643,		// CoordTrans :: CoordTrans
	RC_CTFLoad = 8644,
	RC_CTFUnLoad = 8645,
	RC_CTFToValue = 8646,
	RC_CTFToString = 8647,

	RC_SichtGetCont = 8648,		// Sicht :: GetCont
	RC_SichtSetCont = 8649,		// Sicht :: SetCont

	RC_CTFRectangle = 8650,

	RC_QueryObjGeometrie = 8651,
	RC_EditTextObj = 8652,		// IrisWind :: EditTextObjekt

	RC_RenameSight = 8653,		// Sicht :: Rename

	RC_FillOneIdent = 8654,

	RC_SichtPutMiText = 8655,	// Sicht :: PutMiText
	RC_SichtGetMiText = 8656,	// Sicht :: GetMiText
	RC_SichtDelMiText = 8664,	// Sicht :: DelMiText

	RC_GetVOMMI = 8657,
	RC_GeoDBOpen = 8658,		// GeoDB :: Open

	RC_HdrWriteBack = 8659,		// HeaderEntry :: WriteBack
	RC_SetEntryText = 8660,		// HeaderEntry :: SetEntryText

	RC_CreateObjektInfo = 8661,	// ExtDirisWindow :: CreateObjektInfo

	RC_PutGeoObj = 8662,		// DBO :: PutGeoObj
	RC_ctMenuItem = 8663,		// MenuItem :: MenuItem
// 8664 belegt

	RC_SavePBDMerkmal = 8664,	// PBD_Merkmal :: SaveInPBD
	RC_DeletePBDMerkmal = 8665,	// PBD_Merkmal :: DeleteInPBD

	RC_RetrieveExtName = 8666,	// ExtensionList :: RetrieveExtName
	RC_SetActiveSightName = 8667,	// DatenBasisObjekt :: SetActiveSightName
	RC_DelGI = 8668,		// GeoDB :: DelGI

	RC_InsertObjectGeometrie = 8669,	// ObjClipExtension
	RC_ctObjClip = 8670,			// ctObjClipboardViewer
	RC_InsertObjectMerkmale = 8671,		// ObjClipExtension
	RC_UnloadLocalExtensions = 8672,	// ExtDirisWindow :: UnloadLocalExtensions
	RC_BildListe = 8673,			// BackGrnd.Ext

	RC_ctObjPropDlg = 8674,			// ObjPropDlg :: ObjPropDlg
	RC_GenerateObjProps = 8675,		// ObjPropDlg :: GenerateObjProps

	RC_UnLoadExtension = 8676,		// ExtDirisWindow :: UnLoadExtension

	RC_CIdTreeAddIdent = 8677,		// CIdTree :: AddIdent

	RC_BGetRel = 8678,			// BGetRel
	RC_BFindRel = 8679,			// BFindRel
	
	RC_SetAttributesPunkt = 8680,		// Punkt :: SetAttributes
	RC_SetAttributesLinie = 8681,		// Linie :: SetAttributes
	RC_SetAttributesFlaeche = 8682,		// Flaeche :: SetAttributes
	RC_SetAttributesText = 8683,		// Text :: SetAttributes

	RC_AppIdle = 8664,			// App :: Idle
	
	RC_ctDBDict = 8665,			// __ctor
	RC_ReadDBD = 8666,			// KreideClientWindow :: ReadDBD
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
	RC_DBOReScale = 8684,
	RC_DBOReReadIdents = 8685,

	RC_CreateDBEx = 8686,
	RC_CTFisMetric = 8687,
	RC_CTFNative = 8688,
	RC_CTFMetric = 8689,

	RC_OpenDB = 8690,
	RC_CloseDB = 8691,
						
// ------------------

	RC_ctExport = 8700,		// Funktionen für Export
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

	RC_ACADDXF = 8720,		// ACAD-DXF-Export
	RC_CADDYASC = 8721,		// CADdy-ASCII-Export
	RC_TRIASARC = 8722,             // Arc/Info-Export

//      Komplex-Recherche
	RC_GetMiText = 8723,            // GetMiText ()
	RC_GetContKomplexr = 8724,      // KomplexrExtension :: GetContainer ()
	RC_IdFilterNewKomplexr = 8725,  // KomplexrExtension :: IdFilterNew ()
	RC_IdFilterKomplexr = 8726,     // KomplexrExtension :: IdFilter ()
	RC_KomplexrOutObjList = 8727,   // KomplexrExtension :: _OutObjectList ()
	RC_KomplExtMenuC = 8728,        // KomplexrExtension :: MenuCommand ()
	RC_KomplexrClassify = 8729,     // KomplexrExtension :: _Classify ()

	RC_ReadDBaseRelations = 8730,	// ProFile :: ReadDBaseRelations
	RC_ctDBaseRel = 8731,		// DBaseRel :: DBaseRel
	RC_ExpdBaseExpr = 8732,         // DBaseExtension :: _ExpanddBaseExpr        

	RC_DQLParser = 8800,		// DQLyyparse
	RC_doRecherche = 8801,		// doRecherche
	RC_ReadScript = 8802,		// ReadScript
	RC_GetRStatus = 8803,		// IrisWind :: GetRStatus 
	RC_FilterCheck = 8804,		// DB_Filter :: Check
	RC_dorechercheBuffer = 8805,	// ExtDirisWindow :: dorechercheBuffer

	RC_opplGeoKrs = 10000,		// GeoKreis :: operator+
	RC_opplGeoPkt = 10001,		// GeoPunkt :: operator+
	RC_opplGeoKante = 10002, 	// GeoKante :: operator+
	RC_opplGeoFlaeche = 10003, 	// GeoFlaeche :: operator+
	RC_cpyKrsObj = 10004,
	RC_asKrsObj = 10005,
	RC_SchwPktMasche = 10006,	// Masche :: Schwerpunkt

// CodeBase user routines
	RC_ctDB_Filter = 10007,		// DB_Filter :: DB_Filter
	RC_CheckDB_Filter = 10008,	// DB_Filter :: Check
	RC_ctShowFile = 10009,		// ShowFile :: ShowFile
	RC_DarstShowFile = 10010,	// ShowFile :: Darstellen
	RC_dBase = 10011,		// fr alle CodeBase-Routinen
	RC_crCBobj = 10012,		// Create CodeBaseObj
	RC_CheckTagDB_Filter = 10013,	// DB_Filter :: CheckTag
	RC_ShowDBaseWin = 10014,	// ShowDBaseWindow
	RC_CreateRelMenu = 10015,	// ShowFile :: _CreateRelMenu

//  Komplex-Recherche-Extension
	RC_KomplSetScript = 10016,      // KomplexrExtesnion :: _SetScriptName
	RC_KomplexrAddIdent = 10017,    // KomplexrExtesnion :: AddIdent
	RC_KomplexrFilterIdents = 10018, // KomplexrExtesnion :: FilterIdents
	RC_ctEntryExpression = 10019,	 // EntryExpression :: EntryExpression
	RC_EntryExprGetExpression = 10020,// EntryExpression :: GetExpression
	RC_EntryExprCheck = 10021,	// EntryExpression :: _CheckExpression
	RC_EntryExprFieldListe = 10022, // EntryExpression :: _FillFieldListe
	RC_EntryExprListSel = 10023,	// EntryExpression :: ListBoxSel
	RC_EntryExprFieldInfo = 10024,	// EntryExpression :: _OutputFieldInfo
	RC_EntryExprListClk = 10025,	// EntryExpression :: ListBoxClk

// PBD_DataTempTree
	RC_AddToTempTree = 8820,	// PBD_Data :: AddTotempTree
	RC_ctPBD_Data = 8806,		// PBD_Data :: PBD_Data

// MerkInfo
	RC_ctTextMerkInfo = 8807,	// TextMerkInfo :: TextMerkInfo
	RC_ctLongMerkInfo = 8808,	// LongMerkInfo :: LongMerkInfo
	RC_ctDoubleMerkInfo = 8809,	// DoubleMerkInfo :: DoubleMerkInfo 
	RC_GetMerkInfo = 8810,		// GetMerkInfo

// DirisExtensionVerwaltung
	RC_ctExtDirisWindow = 8811,	// ExtDirisWindow :: ExtDirisWindow
	RC_LoadExtension = 8812,	// Extension :: Load
	RC_ctExtension = 8813,		// Extension :: Extension
	RC_LoadAllExtensions = 8814,	// ExtDirisWindow :: LoadAllExtensions

// Relationen
	RC_GetRelCode = 8815,		// GetRelationsCodes
	RC_GetCodes = 8816,		// GetCodes
	RC_GetRelation = 8817,		// GetRelation
	RC_BDelRel = 8818,		// BRelDelete

	RC_ctStringDup = 8819,		// StringDup :: StringDup
// --> 8820 belegt
// TRIAS06
	RC_dBaseDispatch = 8821,	// dBaseDispatch :: dBaseDispatch
};

#if !defined(E_IGNORE)
#define E_IGNORE	((int (*)(int, int, ...))0)
#define E_DEFAULT	((int (*)(int, int ,...))1)
#endif

#endif // _ERRCODES_HXX


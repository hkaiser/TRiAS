////////////////////////////////////////////////////////////////////////////////
// File:        peplus.h
//
// Authors:     Craig Chaplin
//
// Synopsis:    This file contains the class definitions for CCRPEngine and
//              CCRPEJob as well as any supporting classes and structures.
//
//              Note that the constants defined within this file correspond
//              directly with the #defines found in crpe.h.  Instead of the PE_
//              prefix, the class library uses the PEP_ prefix.
//
//              Note that the structures defined within this file correspond to
//              those present in crpe.h.  Instead of the PE prefix, the class
//              library uses the CRPE prefix.  The class library structures are
//              self initialising and also provide convenient constructors.
//
// History:     22/06/95 - CC - Created.
//              27/07/95 - CC - Added 4.0 Print Engine calls  
////////////////////////////////////////////////////////////////////////////////

#ifndef PEPLUS_H
#define PEPLUS_H

// structures MUST be byte aligned to match crpe.dll byte alignment

#pragma pack(1)

// error codes returned by CRPEngine::GetErrorCode() and CRPEJob::GetErrorCode()

const int PEP_ERR_NOERROR              = 0;
const int PEP_ERR_NOTENOUGHMEMORY      = 500;
const int PEP_ERR_INVALIDJOBNO         = 501;
const int PEP_ERR_INVALIDHANDLE        = 502;
const int PEP_ERR_STRINGTOOLONG        = 503;
const int PEP_ERR_NOSUCHREPORT         = 504;
const int PEP_ERR_NODESTINATION        = 505;
const int PEP_ERR_BADFILENUMBER        = 506;
const int PEP_ERR_BADFILENAME          = 507;
const int PEP_ERR_BADFIELDNUMBER       = 508;
const int PEP_ERR_BADFIELDNAME         = 509;
const int PEP_ERR_BADFORMULANAME       = 510;
const int PEP_ERR_BADSORTDIRECTION     = 511;
const int PEP_ERR_ENGINENOTOPEN        = 512;
const int PEP_ERR_INVALIDPRINTER       = 513;
const int PEP_ERR_PRINTFILEEXISTS      = 514;
const int PEP_ERR_BADFORMULATEXT       = 515;
const int PEP_ERR_BADGROUPSECTION      = 516;
const int PEP_ERR_ENGINEBUSY           = 517;
const int PEP_ERR_BADSECTION           = 518;
const int PEP_ERR_NOPRINTWINDOW        = 519;
const int PEP_ERR_JOBALREADYSTARTED    = 520;
const int PEP_ERR_BADSUMMARYFIELD      = 521;
const int PEP_ERR_NOTENOUGHSYSRES      = 522;
const int PEP_ERR_BADGROUPCONDITION    = 523;
const int PEP_ERR_JOBBUSY              = 524;
const int PEP_ERR_BADREPORTFILE        = 525;
const int PEP_ERR_NODEFAULTPRINTER     = 526;
const int PEP_ERR_SQLSERVERERROR       = 527;
const int PEP_ERR_BADLINENUMBER        = 528;
const int PEP_ERR_DISKFULL             = 529;
const int PEP_ERR_FILEERROR            = 530;
const int PEP_ERR_INCORRECTPASSWORD    = 531;
const int PEP_ERR_BADDATABASEDLL       = 532;
const int PEP_ERR_BADDATABASEFILE      = 533;
const int PEP_ERR_ERRORINDATABASEDLL   = 534;
const int PEP_ERR_DATABASESESSION      = 535;
const int PEP_ERR_DATABASELOGON        = 536;
const int PEP_ERR_DATABASELOCATION     = 537;
const int PEP_ERR_BADSTRUCTSIZE        = 538;
const int PEP_ERR_BADDATE              = 539;
const int PEP_ERR_BADEXPORTDLL         = 540;
const int PEP_ERR_ERRORINEXPORTDLL     = 541;
const int PEP_ERR_PREVATFIRSTPAGE      = 542;
const int PEP_ERR_NEXTATLASTPAGE       = 543;
const int PEP_ERR_CANNOTACCESSREPORT   = 544;
const int PEP_ERR_USERCANCELLED        = 545;
const int PEP_ERR_OLE2NOTLOADED        = 546;
const int PEP_ERR_BADCROSSTABGROUP     = 547;
const int PEP_ERR_NOCTSUMMARIZEDFIELD  = 548;
const int PEP_ERR_DESTINATIONNOTEXPORT = 549;
const int PEP_ERR_INVALIDPAGENUMBER    = 550;
const int PEP_ERR_BADLABELNUMBER       = 551;
const int PEP_ERR_NOTSTOREDPROCEDURE   = 552;
const int PEP_ERR_INVALIDPARAMETER     = 553;
const int PEP_ERR_GRAPHNOTFOUND        = 554;
const int PEP_ERR_INVALIDGRAPHTYPE     = 555;
const int PEP_ERR_INVALIDGRAPHDATA     = 556;
const int PEP_ERR_CANNOTMOVEGRAPH      = 557;
const int PEP_ERR_INVALIDGRAPHTEXT     = 558;
const int PEP_ERR_INVALIDGRAPHOPT      = 559;
const int PEP_ERR_NOTIMPLEMENTED       = 999;

// values to be used for CRPEngine::GetVersion() versionRequested parameter

const int PEP_GV_DLL    = 100;
const int PEP_GV_ENGINE = 200;

// values returned by CRPEJob::GetJobStatus()

const int PEP_JOBNOTSTARTED = 1;
const int PEP_JOBINPROGRESS = 2;
const int PEP_JOBCOMPLETED  = 3;
const int PEP_JOBFAILED     = 4;
const int PEP_JOBCANCELLED  = 5;

// values used to specify the sort direction for CRPEJob group condition
// attributes, record sort order field attributes, and group sort order
// field attributes

const int PEP_SF_DESCENDING = 0;
const int PEP_SF_ASCENDING  = 1;

// group section codes used by CRPEJob group condition attributes, report
// section attributes, and graphing attributes

const int PEP_ALLSECTIONS       = 0;
const int PEP_TITLESECTION      = 1000;
const int PEP_HEADERSECTION     = 2000;
const int PEP_GROUPHEADER       = 3000;  // plus group number
const int PEP_DETAILSECTION     = 4000;
const int PEP_GROUPFOOTER       = 5000;  // plus group number
const int PEP_GRANDTOTALSECTION = 6000;
const int PEP_FOOTERSECTION     = 7000;
const int PEP_SUMMARYSECTION    = 8000;

// group condition codes used by CRPEJob group condition attributes

const int PEP_GC_ANYCHANGE     = 0; // use for all field types except Date and Boolean

const int PEP_GC_DAILY         = 0; // use these constants for Date fields
const int PEP_GC_WEEKLY        = 1;
const int PEP_GC_BIWEEKLY      = 2;
const int PEP_GC_SEMIMONTHLY   = 3;
const int PEP_GC_MONTHLY       = 4;
const int PEP_GC_QUARTERLY     = 5;
const int PEP_GC_SEMIANNUALLY  = 6;
const int PEP_GC_ANNUALLY      = 7;

const int PEP_GC_TOYES         = 1; // use these constants for Boolean fields
const int PEP_GC_TONO          = 2;
const int PEP_GC_EVERYYES      = 3;
const int PEP_GC_EVERYNO       = 4;
const int PEP_GC_NEXTISYES     = 5;
const int PEP_GC_NEXTISNO      = 6;

const int PEP_GC_CONDITIONMASK = 0x00ff; // masks to get the condition and type
const int PEP_GC_TYPEMASK      = 0x0f00; // after calling CRPEJob::GetGroupCondition()
                                         
const int PEP_GC_TYPEOTHER     = 0x0000; // condition parameter
const int PEP_GC_TYPEDATE      = 0x0200;
const int PEP_GC_TYPEBOOLEAN   = 0x0400;

// values used by CRPEJob::ZoomPreviewWindow()
const int PEP_ZOOM_FULL_SIZE           = 0;
const int PEP_ZOOM_SIZE_FIT_ONE_SIDE   = 1;
const int PEP_ZOOM_SIZE_FIT_BOTH_SIDES = 2;

// values used in CRPEJob::SetLineHeight()
const int PEP_ALLLINES = -1;

// values used in CRPEJob::SetFont()
const int PEP_FIELDS    = 0x0001;
const int PEP_TEXT      = 0x0002;
const int PEP_UNCHANGED = -1;

// values used by CRPELogOnInfo structure
const int PEP_SERVERNAME_LEN   = 128;
const int PEP_DATABASENAME_LEN = 128;
const int PEP_USERID_LEN       = 128;
const int PEP_PASSWORD_LEN     = 128;

struct CRPELogOnInfo
{
    CRPELogOnInfo () : m_StructSize(sizeof(CRPELogOnInfo))
    {
        m_serverName[0] = m_databaseName[0] = m_userID[0] = m_password[0] = '\0';
    }

    CRPELogOnInfo (const char *serverName,
                   const char *databaseName,
                   const char *userID,
                   const char *password);

    // Initialize to sizeof(CRPELogOnInfo).
    WORD m_StructSize;

    // For any of the following values an empty string ("") means to use
    // the value already set in the report.  To override a value in the
    // report use a non-empty string (e.g. "Server A").  All strings are
    // null-terminated.
    //
    // For Netware SQL, pass the dictionary path name in ServerName and
    // data path name in DatabaseName.
    char m_serverName [PEP_SERVERNAME_LEN];
    char m_databaseName [PEP_DATABASENAME_LEN];
    char m_userID [PEP_USERID_LEN];

    // Password is undefined when getting information from report.
    char m_password [PEP_PASSWORD_LEN];
};


struct CRPEJobInfo
{
    CRPEJobInfo () : m_StructSize(sizeof(CRPEJobInfo)),
                     m_numRecordsRead(0),
                     m_numRecordsSelected(0),
                     m_numRecordsPrinted(0),
                     m_displayPageN(0),
                     m_latestPageN(0),
                     m_startPageN(0),
                     m_printEnded(FALSE)   // full report print completed?
    {}
    
    WORD m_StructSize;    // initialize to sizeof (CRPEJobInfo)

    DWORD m_numRecordsRead;
    DWORD m_numRecordsSelected;
    DWORD m_numRecordsPrinted;
    WORD  m_displayPageN;       // the page being displayed in window
    WORD  m_latestPageN;        // the page being generated
    WORD  m_startPageN;         // user opted, default to 1
    BOOL  m_printEnded;         // full report print completed?
};


// values used in CRPETableType structure
const int  PEP_DLL_NAME_LEN     = 64;
const int  PEP_FULL_NAME_LEN    = 256;
const WORD PEP_DT_STANDARD      = 1;
const WORD PEP_DT_SQL           = 2;

struct CRPETableType
{
    CRPETableType () : m_StructSize(sizeof(CRPETableType)),
                       m_dbType(PEP_DT_SQL)
    {
        m_dllName[0] = m_descriptiveName[0] = '\0';
    }
    
    // Initialize to sizeof(CRPETableType)
    WORD m_StructSize;

    // All strings are null-terminated.
    char m_dllName [PEP_DLL_NAME_LEN];
    char m_descriptiveName [PEP_FULL_NAME_LEN];

    WORD m_dbType;
};


// values used in CRPESessionInfo structure
const int PEP_SESS_USERID_LEN   = 128;
const int PEP_SESS_PASSWORD_LEN = 128;

struct CRPESessionInfo
{
    CRPESessionInfo () : m_StructSize(sizeof(CRPESessionInfo)),
                         m_sessionHandle(0)
    {
        m_userID[0] = m_password[0] = '\0';
    }

    CRPESessionInfo (const char *userID,
                     const char *password,
                     DWORD sessionHandle);

    // Initialize to sizeof(CRPESessionInfo)
    WORD m_StructSize;

    // All strings are null-terminated.
    char m_userID [PEP_SESS_USERID_LEN];

    // Password is undefined when getting information from report.
    char m_password [PEP_SESS_PASSWORD_LEN];

    // SessionHandle is undefined when getting information from report.
    // When setting information, if it is = 0 the UserID and Password
    // settings are used, otherwise the SessionHandle is used.
    DWORD m_sessionHandle;
};


// values used in CRPETableLocation structure
const int PEP_TABLE_LOCATION_LEN      = 256;

struct CRPETableLocation
{
    CRPETableLocation () : m_StructSize(sizeof(CRPETableLocation))
    {
        m_location[0] = '\0';
    }

    CRPETableLocation (const char *location);

    // Initialize to sizeof(CRPETableLocation)
    WORD m_StructSize;

    // String is null-terminated.
    char m_location [PEP_TABLE_LOCATION_LEN];
};


// values used in CRPEPrintOptions structures
const short PEP_UNCOLLATED       = 0;
const short PEP_COLLATED         = 1;
const short PEP_DEFAULTCOLLATION = 2;

struct CRPEPrintOptions
{
    CRPEPrintOptions () : m_StructSize(sizeof(CRPEPrintOptions)),
                          m_startPageN(0),
                          m_stopPageN(0),
                          m_nReportCopies(0),
                          m_collation(PEP_DEFAULTCOLLATION)
    {}

    CRPEPrintOptions (unsigned short startPageN,
                      unsigned short stopPageN,
                      unsigned short nReportCopies,
                      unsigned short collation
                     ) :
                      m_StructSize(sizeof(CRPEPrintOptions)),
                      m_startPageN(startPageN),
                      m_stopPageN(stopPageN),
                      m_nReportCopies(nReportCopies),
                      m_collation(collation)
    {}

    WORD m_StructSize;            // initialize to sizeof (PEPrintOptions)

    // page and copy numbers are 1-origin
    // use 0 to preserve the existing settings
    unsigned short m_startPageN,
                   m_stopPageN;

    unsigned short m_nReportCopies;
    unsigned short m_collation;
};

    
struct CRPEExportOptions
{
    CRPEExportOptions () : m_StructSize(sizeof(CRPEExportOptions)),
                           m_formatType(0),
                           m_formatOptions(NULL),
                           m_destinationType(0),
                           m_destinationOptions(NULL),
                           m_nFormatOptionsBytes(0),
                           m_nDestinationOptionsBytes(0)
    {
        m_formatDLLName[0] = m_destinationDLLName[0] = '\0';
    }

    CRPEExportOptions (const char *formatDLLName,
                       DWORD formatType,
                       void *formatOptions,
                       const char *destinationDLLName,
                       DWORD destinationType,
                       void *destinationOptions);

    WORD m_StructSize;               // initialize to sizeof(CRPEExportOptions)

    char m_formatDLLName [PEP_DLL_NAME_LEN];
    DWORD m_formatType;
    void *m_formatOptions;
    char m_destinationDLLName [PEP_DLL_NAME_LEN];
    DWORD m_destinationType;
    void *m_destinationOptions;
    WORD m_nFormatOptionsBytes;      // Set by 'GetExportOptions',
                                     // ignored by 'ExportTo'.
    WORD m_nDestinationOptionsBytes; // Set by 'GetExportOptions',
                                     // ignored by 'ExportTo'.
};


struct CRPESectionOptions
{
    CRPESectionOptions () : m_StructSize(sizeof(CRPESectionOptions)),
                            m_visible(0),
                            m_newPageBefore(0),
                            m_newPageAfter(0),
                            m_keepTogether(0),
                            m_suppressBlankLines(0),
                            m_resetPageNAfter(0),
                            m_printAtBottomOfPage(0)
    {}

    CRPESectionOptions (short visible,
                        short newPageBefore,
                        short newPageAfter,
                        short keepTogether,
                        short suppressBlankLines,
                        short resetPageNAfter,
                        short printAtBottomOfPage
                       ) :
                        m_StructSize(sizeof(CRPESectionOptions)),
                        m_visible(visible),
                        m_newPageBefore(newPageBefore),
                        m_newPageAfter(newPageAfter),
                        m_keepTogether(keepTogether),
                        m_suppressBlankLines(suppressBlankLines),
                        m_resetPageNAfter(resetPageNAfter),
                        m_printAtBottomOfPage(printAtBottomOfPage)
    {}

    WORD m_StructSize; // initialize to sizeof (CRPESectionOptions)

    short m_visible;              // BOOLEAN values, except use PEP_UNCHANGED
    short m_newPageBefore;        // to preserve the existing settings
    short m_newPageAfter;
    short m_keepTogether;
    short m_suppressBlankLines;
    short m_resetPageNAfter;
    short m_printAtBottomOfPage;
};


// Setting Graph/Chart info
// ------------------------
//
// Two parameters are passed to uniquely identify the graph:
//      - section code
//      - graph number in that section
//
// The section code includes whether it is a header or footer, and the
// graph number starts at 0, 1...  The graph number identifies the graph
// by its position in the section
//      - looking top down first,
//      - then left to right if they have the same top.

// Graph Types

const int PEP_SIDE_BY_SIDE_BAR_GRAPH          = 0;
const int PEP_STACKED_BAR_GRAPH               = 2;
const int PEP_PERCENT_BAR_GRAPH               = 3;
const int PEP_FAKED_3D_SIDE_BY_SIDE_BAR_GRAPH = 4;
const int PEP_FAKED_3D_STACKED_BAR_GRAPH      = 5;
const int PEP_FAKED_3D_PERCENT_BAR_GRAPH      = 6;
const int PEP_PIE_GRAPH                       = 40;
const int PEP_MULTIPLE_PIE_GRAPH              = 42;
const int PEP_PROPORTIONAL_MULTI_PIE_GRAPH    = 43;
const int PEP_LINE_GRAPH                      = 80;
const int PEP_AREA_GRAPH                      = 120;
const int PEP_THREED_BAR_GRAPH                = 160;
const int PEP_USER_DEFINED_GRAPH              = 500;
const int PEP_UNKNOWN_TYPE_GRAPH              = 1000;

// Graph Directions.
const int PEP_GRAPH_ROWS_ONLY         = 0;
const int PEP_GRAPH_COLS_ONLY         = 1;
const int PEP_GRAPH_MIXED_ROW_COL     = 2;
const int PEP_GRAPH_MIXED_COL_ROW     = 3;
const int PEP_GRAPH_UNKNOWN_DIRECTION = 20;

// Graph constant for rowGroupN, colGroupN, summarizedFieldN in PEGraphDataInfo
const int PEP_GRAPH_DATA_NULL_SELECTION = -1;

// Graph text max length
const int PEP_GRAPH_TEXT_LEN = 128;


struct CRPEGraphDataInfo
{
    CRPEGraphDataInfo () : m_StructSize(sizeof(CRPEGraphDataInfo)),
                           m_rowGroupN(0),
                           m_colGroupN(0),
                           m_summarizedFieldN(0),
                           m_graphDirection(PEP_GRAPH_COLS_ONLY)
    {}
    
    CRPEGraphDataInfo (short rowGroupN,
                       short colGroupN,
                       short summarizedFieldN,
                       short graphDirection
                      ) :
                       m_StructSize(sizeof(CRPEGraphDataInfo)),
                       m_rowGroupN(rowGroupN),
                       m_colGroupN(colGroupN),
                       m_summarizedFieldN(summarizedFieldN),
                       m_graphDirection(graphDirection)
    {}
                           
    WORD m_StructSize;        // initialize to sizeof (CRPEGraphDataInfo)

    short m_rowGroupN;        // group number in report
    short m_colGroupN;        // group number in report
    short m_summarizedFieldN; // summarized field number for the group
                              // where the graph stays.
    short m_graphDirection;   // For normal group/total report, the direction,
                              // is always GRAPH_COLS_ONLY.  For CrossTab
                              // report all four options will change the
                              // graph data.
};


struct CRPEGraphTextInfo
{
    CRPEGraphTextInfo () : m_StructSize(sizeof(CRPEGraphTextInfo))
    {
        m_graphTitle[0] = m_graphSubTitle[0]
                        = m_graphFootNote[0]
                        = m_graphGroupsTitle[0]
                        = m_graphSeriesTitle[0]
                        = m_graphXAxisTitle[0]
                        = m_graphYAxisTitle[0]
                        = m_graphZAxisTitle[0]
                        = '\0';
    }
        
    CRPEGraphTextInfo (const char *graphTitle,
                       const char *graphSubTitle,
                       const char *graphFootNote,
                       const char *graphGroupsTitle,
                       const char *graphSeriesTitle,
                       const char *graphXAxisTitle,
                       const char *graphYAxisTitle,
                       const char *graphZAxisTitle);
        
    WORD m_StructSize; // initialize to sizeof (CRPEGraphTextInfo)

    char m_graphTitle       [PEP_GRAPH_TEXT_LEN];
    char m_graphSubTitle    [PEP_GRAPH_TEXT_LEN];
    char m_graphFootNote    [PEP_GRAPH_TEXT_LEN];
    char m_graphGroupsTitle [PEP_GRAPH_TEXT_LEN];
    char m_graphSeriesTitle [PEP_GRAPH_TEXT_LEN];
    char m_graphXAxisTitle  [PEP_GRAPH_TEXT_LEN];
    char m_graphYAxisTitle  [PEP_GRAPH_TEXT_LEN];
    char m_graphZAxisTitle  [PEP_GRAPH_TEXT_LEN];
};


struct CRPEGraphOptions
{
    CRPEGraphOptions () : m_StructSize(sizeof(CRPEGraphOptions)),
                          m_graphMaxValue(0),
                          m_graphMinValue(0),
                          m_showDataValue(FALSE),
                          m_showGridLine(FALSE),
                          m_verticalBars(FALSE),
                          m_showLegend(FALSE)
    {
        m_fontFaceName[0] = '\0';
    }
    
    CRPEGraphOptions (double graphMaxValue,
                      double graphMinValue,
                      BOOL showDataValue,
                      BOOL showGridLine,
                      BOOL verticalBars,
                      BOOL showLegend,
                      const char *fontFaceName);
                      
    WORD m_StructSize;      // initialize to sizeof (PEGraphOptions)

    double m_graphMaxValue;
    double m_graphMinValue;

    BOOL m_showDataValue;   // Show data values on risers.
    BOOL m_showGridLine;
    BOOL m_verticalBars;
    BOOL m_showLegend;

    char m_fontFaceName[PEP_GRAPH_TEXT_LEN];
};

#pragma pack()

class CRPEJob : public CObject
{
    public:
        
    // constructors

        CRPEJob (short jobHandle);

    // destructor

        ~CRPEJob ();

    // operations

        BOOL Start ();  // start generating print job output

        void Close ();  // closes print job AND deletes CRPEJob object
        
        void Cancel (); // cancel print job output generation

        BOOL ShowNextPage ();           // show next page in preview window
        
        BOOL ShowFirstPage ();          // show first page in preview window

        BOOL ShowPreviousPage ();       // show previous page in preview window

        BOOL ShowLastPage ();           // show last page of preview window

        BOOL ShowPrintControls (BOOL showControls); // show controls in
                                                    // preview window

        BOOL ZoomPreviewWindow (short level); // set preview magnification

        BOOL NextWindowMagnification (); // step to the next preview window
                                         // magnification

        BOOL PrintWindow (); // print the preview window to printer

        BOOL ExportPrintWindow (BOOL toMail); // export the preview window

        void CloseWindow (); // close the preview window

        BOOL TestNthTableConnectivity (short tableN); // test to see if a valid
                                                      // connection exists to
                                                      // the specified table

    // attributes

        // report formula text attributes
        short GetNFormulas();

        BOOL GetNthFormula(short formulaN,
                           CString &formulaName,
                           CString &formulaText);

        BOOL GetFormula (const char *formulaName,
                         CString &formulaText);

        BOOL SetFormula (const char *formulaName,
                         const char *formulaText);

        BOOL CheckFormula(const char *formulaName);

        // record selection formula attributes
        BOOL GetSelectionFormula (CString &formulaText);

        BOOL SetSelectionFormula (const char *formulaText);

        BOOL CheckSelectionFormula ();

        // group selection formula attributes
        BOOL GetGroupSelectionFormula (CString &formulaText);

        BOOL SetGroupSelectionFormula (const char *formulaText);

        BOOL CheckGroupSelectionFormula();

        // group condition attributes
        short GetNGroups ();

        BOOL GetGroupCondition (short sectionCode,
                                CString &conditionField,
                                short *condition,
                                short *sortDirection);

        BOOL SetGroupCondition (short sectionCode,
                                const char *conditionField,
                                short condition,
                                short sortDirection);

        // record sort order field attributes
        short GetNSortFields ();

        BOOL GetNthSortField (short sortFieldN,
                              CString &field,
                              short *direction);

        BOOL SetNthSortField (short sortFieldN,
                              const char *field,
                              short direction);

        BOOL DeleteNthSortField (short sortFieldN);

        // group sort order field attributes
        short GetNGroupSortFields ();

        BOOL GetNthGroupSortField (short sortFieldN,
                                   CString &field,
                                   short *direction);
                                    
        BOOL SetNthGroupSortField (short sortFieldN,
                                   const char *field,
                                   short direction);

        BOOL DeleteNthGroupSortField (short sortFieldN);

        // database table attributes
        short GetNTables ();

        BOOL GetNthTableType (short tableN,
                              CRPETableType *tableType);

        BOOL GetNthTableSessionInfo (short tableN,
                                     CRPESessionInfo *sessionInfo);

        BOOL SetNthTableSessionInfo (short tableN,
                                     const CRPESessionInfo *sessionInfo,
                                     BOOL propagate);

        BOOL GetNthTableLocation (short tableN,
                                  CRPETableLocation *tableLocation);

        BOOL SetNthTableLocation (short tableN,
                                  const CRPETableLocation *tableLocation);

        BOOL GetNthTableLogonInfo (short tableN,
                                   CRPELogOnInfo *logonInfo);

        BOOL SetNthTableLogonInfo (short tableN,
                                   const CRPELogOnInfo *logonInfo,
                                   BOOL propagate);

        // SQL query attributes
        BOOL GetSQLQuery (CString &query);

        BOOL SetSQLQuery (const char *query);

        // SQL stored procedure attributes
        short GetNParams ();

        BOOL GetNthParam (short paramN,
                          CString &paramValue);

        BOOL SetNthParam (short paramN,
                          const char *paramValue);

        // report section attributes
        BOOL GetNDetailCopies(short *nCopies);
    
        BOOL SetNDetailCopies (short nCopies);

        BOOL GetMinimumSectionHeight (short sectionCode,
                                      short *height);
        
        BOOL SetMinimumSectionHeight (short sectionCode,
                                      short height);

        short GetNLinesInSection (short sectionCode);

        BOOL GetLineHeight (short sectionCode,
                            short lineN,
                            short *height,
                            short *ascent);

        BOOL SetLineHeight (short sectionCode,
                            short lineN,
                            short height,
                            short ascent);

        BOOL SetFont (short sectionCode,
                      short scopeCode,
                      const char *faceName,
                      short fontFamily,
                      short fontPitch,
                      short charSet,
                      short pointSize,
                      short isItalic,
                      short isUnderlined,
                      short isStruckOut,
                      short weight);

        BOOL GetSectionFormat (short sectionCode,
                               CRPESectionOptions *options);

        BOOL SetSectionFormat (short sectionCode,
                               const CRPESectionOptions *options);
        
        // graphing attributes
        BOOL GetGraphType (short sectionCode,
                           short graphN,
                           short *graphType);

        BOOL SetGraphType (short sectionCode,
                           short graphN,
                           short graphType);

        BOOL GetGraphData (short sectionCode,
                           short graphN,
                           CRPEGraphDataInfo *graphDataInfo);

        BOOL SetGraphData (short sectionCode,
                           short graphN,
                           CRPEGraphDataInfo *graphDataInfo);

        BOOL GetGraphText (short sectionCode,
                           short graphN,
                           CRPEGraphTextInfo *graphTextInfo);

        BOOL SetGraphText (short sectionCode,
                           short graphN,
                           CRPEGraphTextInfo *graphTextInfo);

        BOOL GetGraphOptions (short sectionCode,
                              short graphN,
                              CRPEGraphOptions *graphOptions);

        BOOL SetGraphOptions (short sectionCode,
                              short graphN,
                              CRPEGraphOptions *graphOptions);

        // report attributes
        BOOL GetReportTitle (CString &title);

        BOOL SetReportTitle (const char *title);

        BOOL GetPrintDate (short *year,
                           short *month,
                           short *day);
        
        BOOL SetPrintDate (short year,
                           short month,
                           short day);

        // report printer attributes
        BOOL GetSelectedPrinter (CString &driverName,
                                 CString &printerName,
                                 CString &portName,
                                 DEVMODE **mode);

        BOOL SelectPrinter (const char *driverName,
                            const char *printerName,
                            const char *portName,
                            const DEVMODE *mode = 0);

        BOOL GetPrintOptions (CRPEPrintOptions *options);

        BOOL SetPrintOptions (const CRPEPrintOptions *options);

        // output destination options
        BOOL OutputToPrinter (short nCopies = 1);

        BOOL OutputToWindow (const char *title,
                             int left,
                             int top,
                             int width,
                             int height,
                             int style,
                             CWnd *parentWindow);

        HWND GetWindowHandle ();

        BOOL PrintControlsShowing (BOOL *controlsShowing);

        BOOL GetExportOptions (CRPEExportOptions *options);

        BOOL ExportTo (const CRPEExportOptions *options);

        BOOL GetMargins (short *left,
                         short *right,
                         short *top,
                         short *bottom);

        BOOL SetMargins (short left,
                         short right,
                         short top,
                         short bottom);

        // job status attributes
        short GetJobStatus (CRPEJobInfo *jobStatus);

        BOOL IsJobFinished ();

        short GetErrorCode ();
        
        CString GetErrorText ();

        // misc. attributes
        short GetJobHandle ();

    // implementation
        #ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
        short m_jobHandle;
};


class CRPEngine : public CObject
{
    public:
        enum Status {engineOpen, engineClosed, engineMissing};

        static CRPEngine *GetEngine ();

        static Status GetEngineStatus ();

    // constructors

        CRPEngine (BOOL open = FALSE);

    // destructor

        ~CRPEngine ();

    // operations

        BOOL Open ();

        void Close ();

        CRPEJob *OpenJob (const char *reportFileName);

        BOOL LogOnServer (const char *dllName,
                          const CRPELogOnInfo *logOnInfo);

        BOOL LogOffServer (const char *dllName,
                           const CRPELogOnInfo *logOnInfo);

        BOOL LogOnSQLServerWithPrivateInfo(const char *dllName,
                                           void *privateInfo);

        short PrintReport (const char *reportFilePath,
                           BOOL toPrinter,
                           BOOL toWindow,
                           const char *title,
                           int left,
                           int top,
                           int width,
                           int height,
                           DWORD style,
                           CWnd *parentWindow);

    // attributes

        BOOL CanClose ();
        
        short GetVersion (short versionRequested);

        short GetErrorCode ();

        CString GetErrorText ();

        int GetNPrintJobs ();

    // implementation

        void AddJob (CRPEJob *job);

        void RemoveJob (CRPEJob *job);

        BOOL GetHandleString (HANDLE textHandle,
                              short textLength,
                              CString &string);

        #ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
        #endif

    protected:
                                    
        static CRPEngine *thePrintEngine;
        Status m_engineStatus;
        CObArray m_printJobs;
        int m_engineError;
};


#endif // PEPLUS_H

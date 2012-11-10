////////////////////////////////////////////////////////////////////////////////
// File:		peplus.cpp
//
// Authors:		Craig Chaplin
//
// Synopsis:	This file contains the class implementations for CRPEngine and
//				CRPEJob as well as any supporting classes and structures.
//
// History:  27/07/95 - CC - added GetNFormulas (4.0 only)
//                         - added GetNthFormula (4.0 only)  
//
////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "peplus.h"
#include "crpe.h"

CRPEngine *CRPEngine::thePrintEngine = NULL;

//////////////////////////////////////////////////////////////
// Supporting structures used by CRPEngine and CRPEJob classes
//////////////////////////////////////////////////////////////

CRPELogOnInfo::CRPELogOnInfo (const char *serverName,
							  const char *databaseName,
							  const char *userID,
							  const char *password
							 ) :
							  m_StructSize(sizeof(CRPELogOnInfo))
{
	lstrcpyn(m_serverName,serverName,sizeof(m_serverName) - 1);
	lstrcpyn(m_databaseName,databaseName,sizeof(m_databaseName) - 1);
	lstrcpyn(m_userID,userID,sizeof(m_userID) - 1);
	lstrcpyn(m_password,password,sizeof(m_password) - 1);
}


CRPESessionInfo::CRPESessionInfo (const char *userID,
								  const char *password,
								  DWORD sessionHandle
								 ) :
								  m_StructSize(sizeof(CRPESessionInfo)),
								  m_sessionHandle(sessionHandle)
{
	lstrcpyn(m_userID,userID,sizeof(m_userID) - 1);
	lstrcpyn(m_password,password,sizeof(m_password) - 1);
}


CRPETableLocation::CRPETableLocation (const char *location) :
									  m_StructSize(sizeof(CRPETableLocation))
{
	lstrcpyn(m_location,location,sizeof(m_location) - 1);
}


CRPEExportOptions::CRPEExportOptions (const char *formatDLLName,
									  DWORD formatType,
									  void *formatOptions,
									  const char *destinationDLLName,
									  DWORD destinationType,
									  void *destinationOptions
									 ) :
									  m_StructSize(sizeof(CRPEExportOptions)),
									  m_formatType(formatType),
									  m_formatOptions(formatOptions),
									  m_destinationType(destinationType),
									  m_destinationOptions(destinationOptions)
{
	lstrcpyn(m_formatDLLName,formatDLLName,sizeof(m_formatDLLName) - 1);
	lstrcpyn(m_destinationDLLName,destinationDLLName,sizeof(m_destinationDLLName) - 1);
}

                                      
CRPEGraphTextInfo::CRPEGraphTextInfo (const char *graphTitle,
                                      const char *graphSubTitle,
                                      const char *graphFootNote,
                                      const char *graphGroupsTitle,
                                      const char *graphSeriesTitle,
                                      const char *graphXAxisTitle,
                                      const char *graphYAxisTitle,
                                      const char *graphZAxisTitle
                                     ) :
                                      m_StructSize(sizeof(CRPEGraphTextInfo))
{
    lstrcpyn(m_graphTitle,graphTitle,sizeof(m_graphTitle) - 1);
    lstrcpyn(m_graphSubTitle,graphSubTitle,sizeof(m_graphSubTitle) - 1);
    lstrcpyn(m_graphFootNote,graphFootNote,sizeof(m_graphFootNote) - 1);
    lstrcpyn(m_graphGroupsTitle,graphGroupsTitle,sizeof(m_graphGroupsTitle) - 1);
    lstrcpyn(m_graphSeriesTitle,graphSeriesTitle,sizeof(m_graphSeriesTitle) - 1);
    lstrcpyn(m_graphXAxisTitle,graphXAxisTitle,sizeof(m_graphXAxisTitle) - 1);
    lstrcpyn(m_graphYAxisTitle,graphYAxisTitle,sizeof(m_graphYAxisTitle) - 1);
    lstrcpyn(m_graphZAxisTitle,graphZAxisTitle,sizeof(m_graphZAxisTitle) - 1);
}

                                      
CRPEGraphOptions::CRPEGraphOptions (double graphMaxValue,
                                    double graphMinValue,
                                    BOOL showDataValue,
                                    BOOL showGridLine,
                                    BOOL verticalBars,
                                    BOOL showLegend,
                                    const char *fontFaceName
                                    ) :
                                     m_StructSize(sizeof(CRPEGraphOptions)),
                                     m_graphMaxValue(graphMaxValue),
                                     m_graphMinValue(graphMinValue),
                                     m_showDataValue(showDataValue),
                                     m_showGridLine(showGridLine),
                                     m_verticalBars(verticalBars),
                                     m_showLegend(showLegend)
{
    lstrcpyn(m_fontFaceName,fontFaceName,sizeof(m_fontFaceName) - 1);
}


//////////////////
// CRPEngine Class
//////////////////

CRPEngine *CRPEngine::GetEngine(void)
{
	return CRPEngine::thePrintEngine;
}


CRPEngine::Status CRPEngine::GetEngineStatus(void)
{
	return(thePrintEngine != 0) ? thePrintEngine->m_engineStatus : engineMissing;
}


// constructors and destructor


CRPEngine::CRPEngine (BOOL open) : m_engineStatus(engineClosed),
								   m_engineError(0)
{
	ASSERT (thePrintEngine == NULL); // only one object of CRPEngine is allowed

	CRPEngine::thePrintEngine = this;

	if (open)
		Open();
}


CRPEngine::~CRPEngine()
{
	ASSERT (thePrintEngine == this); // only one object of CRPEngine allowed
	
	Close();
	CRPEngine::thePrintEngine = NULL;
}


// operations


BOOL CRPEngine::Open(void)
{
	m_engineError = 0;

	if (m_engineStatus == engineOpen)
		return TRUE;

	if (PEOpenEngine()) {
		m_engineStatus = engineOpen;
		return TRUE;
	}
	else {
		m_engineStatus = engineClosed;
		return FALSE;
	}
}


void CRPEngine::Close(void)
{
	m_engineError = 0;

	if (m_engineStatus == engineOpen) {

		while (m_printJobs.GetSize())
			((CRPEJob *)m_printJobs[0]) -> Close();

		PECloseEngine();
		m_engineStatus = engineClosed;
	}
}


CRPEJob *CRPEngine::OpenJob(const char *reportFileName)
{
	ASSERT (m_engineStatus == engineOpen); // engine must be open

	short jobHandle = 0;
	CRPEJob *newJob = NULL;

 	m_engineError = 0;

	if ((jobHandle = PEOpenPrintJob((char *)reportFileName)) == 0)
		return NULL;

	if ((newJob = new CRPEJob(jobHandle)) == NULL) {
		PEClosePrintJob(jobHandle);
		m_engineError = PEP_ERR_NOTENOUGHMEMORY;
		return NULL;
	}

	return newJob;
}


BOOL CRPEngine::LogOnServer(const char *dllName,const CRPELogOnInfo *logOnInfo)
{
	// ensure CRPELogOnInfo object is size CRPE expects
	ASSERT (sizeof(CRPELogOnInfo) == sizeof(PELogOnInfo));

	ASSERT (m_engineStatus == engineOpen); // engine must be open

 	m_engineError = 0;

	return (PELogOnServer((char *)dllName,(struct PELogOnInfo *) logOnInfo));
}


BOOL CRPEngine::LogOffServer(const char *dllName,
							 const CRPELogOnInfo *logOnInfo)
{										   
	// ensure CRPELogOnInfo object is size CRPE expects
	ASSERT (sizeof(CRPELogOnInfo) == sizeof(PELogOnInfo));

	ASSERT (m_engineStatus == engineOpen); // engine must be open

 	m_engineError = 0;

	return (PELogOffServer((char *)dllName,(struct PELogOnInfo *) logOnInfo));
}


BOOL CRPEngine::LogOnSQLServerWithPrivateInfo(const char *dllName,
                                              void *privateInfo)
{
    return PELogOnSQLServerWithPrivateInfo((char *)dllName,privateInfo);
}


short CRPEngine::PrintReport(const char *reportFilePath,
							 BOOL toPrinter,
							 BOOL toWindow,
							 const char *title,
							 int left,
							 int top,
							 int width,
							 int height,
							 DWORD style,
							 CWnd *parentWindow
							)
{
	ASSERT (m_engineStatus == engineOpen); // engine must be open

	m_engineError = 0;

	return PEPrintReport((char *)reportFilePath,
						 toPrinter,
						 toWindow,
						 (char *)title,
						 left,
						 top,
						 width,
						 height,
						 style,
						 parentWindow != 0 ? parentWindow->m_hWnd : 0);
}


// attributes
	

BOOL CRPEngine::CanClose()
{
    return (m_engineStatus != engineOpen) ? TRUE : PECanCloseEngine();
}


short CRPEngine::GetVersion(short versionRequested)
{
	ASSERT (m_engineStatus == engineOpen); // engine must be open

 	m_engineError = 0;

	return PEGetVersion(versionRequested);
}


short CRPEngine::GetErrorCode(void)
{
	return (m_engineError) ? m_engineError : PEGetErrorCode(0);
}


CString CRPEngine::GetErrorText(void)
{
	HANDLE textHandle;
	short textLength;
	CString errorText = "";

	if (!m_engineError)
		if (PEGetErrorText(0,&textHandle,&textLength))
			GetHandleString(textHandle,textLength,errorText);
	
	return errorText;
}


int CRPEngine::GetNPrintJobs()
{
    return m_printJobs.GetSize();
}


// implementation


void CRPEngine::AddJob(CRPEJob *job)
{
	m_printJobs.Add(job);
}


void CRPEngine::RemoveJob(CRPEJob *job)
{
	int numJobs = m_printJobs.GetSize();

	while (numJobs--)
		if (m_printJobs[numJobs] == job) {
			m_printJobs.RemoveAt(numJobs);
			break;
		}
}


BOOL CRPEngine::GetHandleString (HANDLE textHandle,
								 short textLength,
								 CString &string)
{
	BOOL result = FALSE;
	char *buffer = string.GetBufferSetLength(textLength);

	if (buffer) {
		result = PEGetHandleString(textHandle,buffer,textLength);
		string.ReleaseBuffer();
	}
	else
		m_engineError = PEP_ERR_NOTENOUGHMEMORY;

	return result;
}


// CRPEngine diagnostics


#ifdef _DEBUG
void CRPEngine::AssertValid() const
{
	CObject::AssertValid();
}


void CRPEngine::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG


////////////////
// CRPEJob Class
////////////////

// constructors & destructor

CRPEJob::CRPEJob(short jobHandle) : m_jobHandle(jobHandle)
{
 	// engine object must exist
	ASSERT (CRPEngine::GetEngine() != NULL);
	// engine must be open
	ASSERT (CRPEngine::GetEngineStatus() == CRPEngine::engineOpen);
	// job handle can't be 0
	ASSERT (jobHandle != 0);
	
	CRPEngine::GetEngine()->AddJob(this);
}


CRPEJob::~CRPEJob()
{
	ASSERT (CRPEngine::GetEngine() != NULL); // engine object must exist

	CRPEngine::GetEngine()->RemoveJob(this);
	PEClosePrintJob(m_jobHandle);
}


// operations


BOOL CRPEJob::Start()
{
	return PEStartPrintJob(m_jobHandle,TRUE);
}


void CRPEJob::Close()
{
	delete this;
}
	

void CRPEJob::Cancel()
{
	PECancelPrintJob(m_jobHandle);
}


BOOL CRPEJob::ShowNextPage(void)
{
	return PEShowNextPage(m_jobHandle);
}

		
BOOL CRPEJob::ShowFirstPage(void)
{
	return PEShowFirstPage(m_jobHandle);
}


BOOL CRPEJob::ShowPreviousPage(void)
{
	return PEShowPreviousPage(m_jobHandle);
}


BOOL CRPEJob::ShowLastPage(void)
{
	return PEShowLastPage(m_jobHandle);
}


BOOL CRPEJob::ShowPrintControls(BOOL showControls)
{
	return PEShowPrintControls(m_jobHandle,showControls);
}


BOOL CRPEJob::ZoomPreviewWindow(short level)
{
	return PEZoomPreviewWindow(m_jobHandle,level);
}


BOOL CRPEJob::NextWindowMagnification(void)
{
	return PENextPrintWindowMagnification(m_jobHandle);
}


BOOL CRPEJob::PrintWindow(void)
{
	return PEPrintWindow(m_jobHandle,TRUE);
}


BOOL CRPEJob::ExportPrintWindow(BOOL toMail)
{
	return PEExportPrintWindow(m_jobHandle,toMail,TRUE);
}

	
void CRPEJob::CloseWindow(void)
{
	PECloseWindow(m_jobHandle);
}


BOOL CRPEJob::TestNthTableConnectivity(short tableN)
{
	return PETestNthTableConnectivity(m_jobHandle,tableN);
}


// report fomula text attributes


short CRPEJob::GetNFormulas()
{
	return PEGetNFormulas(m_jobHandle);
}


BOOL CRPEJob::GetNthFormula(short formulaN,
							CString &formulaName,
						    CString &formulaText)
{
	HANDLE nameHandle;
	short nameLength;
	HANDLE textHandle;
	short textLength;

	BOOL result = FALSE;

	formulaName = "";
	formulaText = "";

	if (PEGetNthFormula(m_jobHandle,
	                    formulaN,
                        &nameHandle,
                        &nameLength,
                        &textHandle,
                        &textLength))
		if ((result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														      textLength,
														      formulaText)))
            result = CRPEngine::GetEngine()->GetHandleString(nameHandle,
                                                             nameLength,
                                                             formulaName);


	return result;
}


BOOL CRPEJob::GetFormula(const char *formulaName,
						 CString &formulaText)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	formulaText = "";

	if (PEGetFormula(m_jobHandle,
					 (char *)formulaName,
					 &textHandle,
					 &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 formulaText);

	return result;
}


BOOL CRPEJob::SetFormula(const char *formulaName,
						  const char *formulaText)
{
	return PESetFormula(m_jobHandle,(char *)formulaName,(char *)formulaText);
}


BOOL CRPEJob::CheckFormula(const char *formulaName)
{
    return PECheckFormula(m_jobHandle,(char *)formulaName);
}


// record selection formula attributes


BOOL CRPEJob::GetSelectionFormula(CString &formulaText)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	formulaText = "";

	if (PEGetSelectionFormula(m_jobHandle,
							  &textHandle,
							  &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 formulaText);

	return result;
}


BOOL CRPEJob::SetSelectionFormula(const char *formulaText)
{
	return PESetSelectionFormula(m_jobHandle,(char *)formulaText);
}


BOOL CRPEJob::CheckSelectionFormula ()
{
    return PECheckSelectionFormula(m_jobHandle);
}


// group selection formula attributes


BOOL CRPEJob::GetGroupSelectionFormula(CString &formulaText)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	formulaText = "";

	if (PEGetGroupSelectionFormula(m_jobHandle,
								   &textHandle,
								   &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 formulaText);

	return result;
}


BOOL CRPEJob::SetGroupSelectionFormula(const char *formulaText)
{
	return PESetGroupSelectionFormula(m_jobHandle,(char *)formulaText);
}


BOOL CRPEJob::CheckGroupSelectionFormula()
{
    return PECheckGroupSelectionFormula(m_jobHandle);
}


// group condition attributes


short CRPEJob::GetNGroups ()
{
    return PEGetNGroups(m_jobHandle);
}


BOOL CRPEJob::GetGroupCondition (short sectionCode,
                                 CString &conditionField,
                                 short *condition,
                                 short *sortDirection)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	conditionField = "";

	if (PEGetGroupCondition(m_jobHandle,
                            sectionCode,
                            &textHandle,
							&textLength,
                            condition,
                            sortDirection))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 conditionField);

	return result;
}


BOOL CRPEJob::SetGroupCondition(short sectionCode,
								 const char *conditionField,
								 short condition,
								 short sortDirection)
{
	return PESetGroupCondition(m_jobHandle,
							   sectionCode,
							   (char *)conditionField,
							   condition,
							   sortDirection);
}


// record sort order field attributes


short CRPEJob::GetNSortFields(void)
{
	return PEGetNSortFields(m_jobHandle);
}


BOOL CRPEJob::GetNthSortField(short sortFieldN,
							  CString &field,
							  short *direction)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	field = "";

	if (PEGetNthSortField(m_jobHandle,
						  sortFieldN,
						  &textHandle,
						  &textLength,
						  direction))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 field);

	return result;
}


BOOL CRPEJob::SetNthSortField(short sortFieldN,
							   const char *field,
							   short direction)
{
	return PESetNthSortField(m_jobHandle,sortFieldN,(char *)field,direction);
}


BOOL CRPEJob::DeleteNthSortField(short sortFieldN)
{
	return PEDeleteNthSortField(m_jobHandle,sortFieldN);
}


// group sort order field attributes


short CRPEJob::GetNGroupSortFields(void)
{
	return PEGetNGroupSortFields(m_jobHandle);
}


BOOL CRPEJob::GetNthGroupSortField(short sortFieldN,
									CString &field,
									short *direction)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	field = "";

	if (PEGetNthGroupSortField(m_jobHandle,
							   sortFieldN,
							   &textHandle,
							   &textLength,
							   direction))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 field);

	return result;
}

								   	
BOOL CRPEJob::SetNthGroupSortField(short sortFieldN,
									const char *field,
									short direction)
{
	return PESetNthGroupSortField(m_jobHandle,
								  sortFieldN,
								  (char *)field,
								  direction);
}


BOOL CRPEJob::DeleteNthGroupSortField(short sortFieldN)
{
	return PEDeleteNthGroupSortField(m_jobHandle,sortFieldN);
}


// database table attributes


short CRPEJob::GetNTables(void)
{
	return PEGetNTables(m_jobHandle);
}


BOOL CRPEJob::GetNthTableType(short tableN,
                              CRPETableType *tableType)
{
	return PEGetNthTableType(m_jobHandle,
							 tableN,
							 (struct PETableType *) tableType);
}


BOOL CRPEJob::GetNthTableSessionInfo(short tableN,
									 CRPESessionInfo *sessionInfo)
{
	return PEGetNthTableSessionInfo(m_jobHandle,
									tableN,
									(struct PESessionInfo *) sessionInfo);
}


BOOL CRPEJob::SetNthTableSessionInfo(short tableN,
									 const CRPESessionInfo *sessionInfo,
									 BOOL propagate)
{
	// ensure CRPESessionInfo object is size CRPE expects
	ASSERT (sizeof(CRPESessionInfo) == sizeof(PESessionInfo));

	return PESetNthTableSessionInfo(m_jobHandle,
									tableN,
									(struct PESessionInfo *) sessionInfo,
									propagate);
}


BOOL CRPEJob::GetNthTableLocation(short tableN,
								   CRPETableLocation *tableLocation)
{
	return PEGetNthTableLocation(m_jobHandle,
								 tableN,
								 (struct PETableLocation *) tableLocation);
}


BOOL CRPEJob::SetNthTableLocation(short tableN,
								  const CRPETableLocation *tableLocation)
{
	// ensure CRPETableLocation object is size CRPE expects
	ASSERT (sizeof(CRPETableLocation) == sizeof(PETableLocation));

	return PESetNthTableLocation(m_jobHandle,
								 tableN,
								 (struct PETableLocation *) tableLocation);
}


BOOL CRPEJob::GetNthTableLogonInfo(short tableN,
									CRPELogOnInfo *logonInfo)
{
	return PEGetNthTableLogOnInfo(m_jobHandle,
								  tableN,
								  (struct PELogOnInfo *) logonInfo);
}


BOOL CRPEJob::SetNthTableLogonInfo(short tableN,
									const CRPELogOnInfo *logonInfo,
									BOOL propagate)
{
	// ensure CRPELogOnInfo object is size CRPE expects
	ASSERT (sizeof(CRPELogOnInfo) == sizeof(PELogOnInfo));

	return PESetNthTableLogOnInfo(m_jobHandle,
								  tableN,
								  (struct PELogOnInfo *) logonInfo,
								  propagate);
}


// SQL query attributes


BOOL CRPEJob::GetSQLQuery(CString &query)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	query = "";

	if (PEGetSQLQuery(m_jobHandle,
					  &textHandle,
					  &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 query);

	return result;
}


BOOL CRPEJob::SetSQLQuery(const char *query)
{
	return PESetSQLQuery(m_jobHandle,(char *)query);
}


// SQL stored procedure attributes


short CRPEJob::GetNParams()
{
    return PEGetNParams(m_jobHandle);
}


BOOL CRPEJob::GetNthParam(short paramN,
                          CString &paramValue)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	paramValue = "";

	if (PEGetNthParam(m_jobHandle,
                      paramN,
					  &textHandle,
					  &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 paramValue);

	return result;
}


BOOL CRPEJob::SetNthParam(short paramN,
                          const char *paramValue)
{
    return PESetNthParam(m_jobHandle,paramN,(LPCSTR)paramValue);
}


// report section attributes


BOOL CRPEJob::GetNDetailCopies(short *nCopies)
{
    return PEGetNDetailCopies(m_jobHandle,nCopies);
}


BOOL CRPEJob::SetNDetailCopies(short nCopies)
{
	return PESetNDetailCopies(m_jobHandle,nCopies);
}


BOOL CRPEJob::GetMinimumSectionHeight(short sectionCode,
                                      short *height)
{
	return PEGetMinimumSectionHeight(m_jobHandle,
									 sectionCode,
									 height);
}


BOOL CRPEJob::SetMinimumSectionHeight(short sectionCode,
									  short height)
{
	return PESetMinimumSectionHeight(m_jobHandle,
									 sectionCode,
									 height);
}


short CRPEJob::GetNLinesInSection(short sectionCode)
{
    return PEGetNLinesInSection(m_jobHandle,sectionCode);
}


BOOL CRPEJob::GetLineHeight(short sectionCode,
                            short lineN,
                            short *height,
                            short *ascent)
{
    return PEGetLineHeight(m_jobHandle,
                           sectionCode,
                           lineN,
                           height,
                           ascent);
}


BOOL CRPEJob::SetLineHeight(short sectionCode,
							short lineN,
							short height,
							short ascent)
{
	return PESetLineHeight(m_jobHandle,
						   sectionCode,
						   lineN,
						   height,
						   ascent);
}


BOOL CRPEJob::SetFont(short sectionCode,
					   short scopeCode,
					   const char *faceName,
					   short fontFamily,
					   short fontPitch,
					   short charSet,
					   short pointSize,
					   short isItalic,
					   short isUnderlined,
					   short isStruckOut,
					   short weight)
{
	return PESetFont(m_jobHandle,
					 sectionCode,
					 scopeCode,
					 (char *)faceName,
					 fontFamily,
					 fontPitch,
					 charSet,
					 pointSize,
					 isItalic,
					 isUnderlined,
					 isStruckOut,
					 weight);
}


BOOL CRPEJob::GetSectionFormat (short sectionCode,
                                CRPESectionOptions *options)
{
    return PEGetSectionFormat(m_jobHandle,
                              sectionCode,
                              (struct PESectionOptions *)options);
}


BOOL CRPEJob::SetSectionFormat (short sectionCode,
                                const CRPESectionOptions *options)
{
	// ensure CRPESectionOptions is size CRPE expects
	ASSERT (sizeof(CRPESectionOptions) == sizeof(PESectionOptions));
    return PESetSectionFormat (m_jobHandle,
                               sectionCode,
                               (struct PESectionOptions *)options);
}


// graphing attributes


BOOL CRPEJob::GetGraphType (short sectionCode,
                            short graphN,
                            short *graphType)
{
    return PEGetGraphType(m_jobHandle,
                          sectionCode,
                          graphN,
                          graphType);
}


BOOL CRPEJob::SetGraphType (short sectionCode,
                            short graphN,
                            short graphType)
{
    return PESetGraphType (m_jobHandle,
                           sectionCode,
                           graphN,
                           &graphType);
}


BOOL CRPEJob::GetGraphData (short sectionCode,
                            short graphN,
                            CRPEGraphDataInfo *graphDataInfo)
{
	// ensure CRPEGraphDataInfo is size CRPE expects
	ASSERT (sizeof(CRPEGraphDataInfo) == sizeof(PEGraphDataInfo));

    return PEGetGraphData (m_jobHandle,
                           sectionCode,
                           graphN,
                           (struct PEGraphDataInfo *) graphDataInfo);
}


BOOL CRPEJob::SetGraphData (short sectionCode,
                            short graphN,
                            CRPEGraphDataInfo *graphDataInfo)
{
	// ensure CRPEGraphDataInfo is size CRPE expects
	ASSERT (sizeof(CRPEGraphDataInfo) == sizeof(PEGraphDataInfo));
    
    return PESetGraphData (m_jobHandle,
                           sectionCode,
                           graphN,
                           (struct PEGraphDataInfo *) graphDataInfo);
}


BOOL CRPEJob::GetGraphText (short sectionCode,
                            short graphN,
                            CRPEGraphTextInfo *graphTextInfo)
{
	// ensure CRPEGraphTextInfo is size CRPE expects
	ASSERT (sizeof(CRPEGraphTextInfo) == sizeof(PEGraphTextInfo));

    return PEGetGraphText (m_jobHandle,
                           sectionCode,
                           graphN,
                           (struct PEGraphTextInfo *) graphTextInfo);
}


BOOL CRPEJob::SetGraphText (short sectionCode,
                            short graphN,
                            CRPEGraphTextInfo *graphTextInfo)
{
	// ensure CRPEGraphTextInfo is size CRPE expects
	ASSERT (sizeof(CRPEGraphTextInfo) == sizeof(PEGraphTextInfo));

    return PESetGraphText (m_jobHandle,
                           sectionCode,
                           graphN,
                           (struct PEGraphTextInfo *) graphTextInfo);
}


BOOL CRPEJob::GetGraphOptions (short sectionCode,
                               short graphN,
                               CRPEGraphOptions *graphOptions)
{
	// ensure CRPEGraphOptions is size CRPE expects
	ASSERT (sizeof(CRPEGraphOptions) == sizeof(PEGraphOptions));

    return PEGetGraphOptions (m_jobHandle,
                              sectionCode,
                              graphN,
                              (struct PEGraphOptions *) graphOptions);
}


BOOL CRPEJob::SetGraphOptions (short sectionCode,
                               short graphN,
                               CRPEGraphOptions *graphOptions)
{
	// ensure CRPEGraphOptions is size CRPE expects
	ASSERT (sizeof(CRPEGraphOptions) == sizeof(PEGraphOptions));

    return PESetGraphOptions (m_jobHandle,
                              sectionCode,
                              graphN,
                              (struct PEGraphOptions *) graphOptions);
}


// report attributes


BOOL CRPEJob::GetReportTitle (CString &title)
{
	HANDLE textHandle;
	short textLength;
	BOOL result = FALSE;

	title = "";

	if (PEGetReportTitle(m_jobHandle,
						 &textHandle,
						 &textLength))
		result = CRPEngine::GetEngine()->GetHandleString(textHandle,
														 textLength,
														 title);

	return result;
}


BOOL CRPEJob::SetReportTitle(const char *title)
{
	return PESetReportTitle(m_jobHandle,(char *)title);
}


BOOL CRPEJob::GetPrintDate (short *year,
                            short *month,
                            short *day)
{
    return PEGetPrintDate(m_jobHandle,year,month,day);
}


BOOL CRPEJob::SetPrintDate(short year,
							short month,
							short day)
{
	return PESetPrintDate(m_jobHandle,year,month,day);
}


// output attributes


BOOL CRPEJob::GetSelectedPrinter (CString &driverName,
                                  CString &printerName,
                                  CString &portName,
                                  DEVMODE **mode)
{
	HANDLE driverHandle, printerHandle, portHandle;
	short driverLength, printerLength, portLength;
	BOOL result = FALSE;

	driverName = "";
    printerName = "";
    portName = "";

	if (PEGetSelectedPrinter(m_jobHandle,
                             &driverHandle,
                             &driverLength,
                             &printerHandle,
                             &printerLength,
                             &portHandle,
                             &portLength,
                             mode))
		if (CRPEngine::GetEngine()->GetHandleString(driverHandle,
												   driverLength,
												   driverName))
            if (CRPEngine::GetEngine()->GetHandleString(printerHandle,
                                                        printerLength,
                                                        printerName))
                result = CRPEngine::GetEngine()->GetHandleString(portHandle,
                                                                 portLength,
                                                                 portName);

	return result;
}


BOOL CRPEJob::SelectPrinter(const char *driverName,
							 const char *printerName,
							 const char *portName,
							 const DEVMODE *mode)
{
	return PESelectPrinter(m_jobHandle,
						   (char *)driverName,
						   (char *)printerName,
						   (char *)portName,
						   (DEVMODE *)mode);
}


BOOL CRPEJob::OutputToWindow(const char *title,
							  int left,
							  int top,
							  int width,
							  int height,
							  int style,
							  CWnd *parentWindow)
{
	return PEOutputToWindow(m_jobHandle,
							(char *)title,
							left,
							top,
							width,
							height,
							style,
						 	parentWindow != 0 ? parentWindow->m_hWnd : 0);
}


BOOL CRPEJob::OutputToPrinter(short nCopies)
{
    return PEOutputToPrinter(m_jobHandle,nCopies);
}


BOOL CRPEJob::GetPrintOptions(CRPEPrintOptions *options)
{
	return PEGetPrintOptions(m_jobHandle,
							 (struct PEPrintOptions *) options);
}


BOOL CRPEJob::SetPrintOptions(const CRPEPrintOptions *options)
{
	// ensure CRPEPrintOptions is size CRPE expects
	ASSERT (sizeof(CRPEPrintOptions) == sizeof(PEPrintOptions));

	return PESetPrintOptions(m_jobHandle,
							 (struct PEPrintOptions *) options);
}


BOOL CRPEJob::ExportTo(const CRPEExportOptions *options)
{
	// ensure CRPEExportOptions is size CRPE expects
	ASSERT (sizeof(CRPEExportOptions) == sizeof(PEExportOptions));

	return PEExportTo(m_jobHandle,
					  (struct PEExportOptions *) options);
}


BOOL CRPEJob::GetMargins(short *left,
                         short *right,
                         short *top,
                         short *bottom)
{
	return PEGetMargins(m_jobHandle,
						left,
						right,
						top,
						bottom);
}


BOOL CRPEJob::SetMargins(short left,
						 short right,
						 short top,
						 short bottom)
{
	return PESetMargins(m_jobHandle,
						left,
						right,
						top,
						bottom);
}


HWND CRPEJob::GetWindowHandle(void)
{
	return PEGetWindowHandle(m_jobHandle);
}


BOOL CRPEJob::GetExportOptions(CRPEExportOptions *options)
{
	return PEGetExportOptions(m_jobHandle,
							  (struct PEExportOptions *) options);
}


BOOL CRPEJob::PrintControlsShowing(BOOL *controlsShowing)
{
    return PEPrintControlsShowing(m_jobHandle,controlsShowing);
}


short CRPEJob::GetJobStatus(CRPEJobInfo *jobStatus)
{
	return PEGetJobStatus(m_jobHandle,(struct PEJobInfo *)jobStatus);
}


BOOL CRPEJob::IsJobFinished(void)
{
	return PEIsPrintJobFinished(m_jobHandle);
}


short CRPEJob::GetErrorCode(void)
{
	return PEGetErrorCode(m_jobHandle);
}


CString CRPEJob::GetErrorText(void)
{
	HANDLE textHandle;
	short textLength;
	CString errorText = "";

	if (PEGetErrorText(m_jobHandle,&textHandle,&textLength))
		CRPEngine::GetEngine()->GetHandleString(textHandle,
												textLength,
												errorText);
	
	return errorText;
}


// misc. attributes


short CRPEJob::GetJobHandle(void)
{
	return m_jobHandle;
}


// implementation


#ifdef _DEBUG
void CRPEJob::AssertValid() const
{
	CObject::AssertValid();
}


void CRPEJob::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

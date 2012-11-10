// TSPrinter.cpp : Implementierung von CTSPrinter
#include "stdafx.h"
#include "TSPrint.h"
#include "TSPrinter.h"

#include <winspool.h>

#define TS_ENVIRONMENT "Windows NT x86"
#define TS_MONITORNAME "Local Port"
#define TS_PORTNAME "TSDV:"
#define TS_PRINTERNAME "TeleSafe Drucker"
#define TS_PRINTERDRIVERNAME "TeleSafe Druckertreiber"


#define TSERRBASE 0xA0000000
	int iDocumentCounter;
	int iPageCounter;
	int iLineCounter;
	int iBlockCounter;
	long lByteCounter;
	bool tLandscape;

	HANDLE hPrinterDataFile;
    DWORD dwPrinterDataSize;
	LPBYTE pLineBuffer;
	DWORD cbLineBuffer;
	BYTE baBuffer[4096];

	BYTE bitmapbuf[6600][880];
	// maximalauflösung des Druckers wird mit 600 dpi angesetzt
	int iResolution;
	BYTE bLinesPerPixel;
	unsigned int uiBytesPerLine;
	unsigned int uiBytesPerBMPLine;

/////////////////////////////////////////////////////////////////////////////
// CTSPrinter

CTSPrinter :: CTSPrinter() {
	hPrinterDataFile = INVALID_HANDLE_VALUE;
	pLineBuffer = NULL;
	cbLineBuffer = 0;
}

CTSPrinter :: ~CTSPrinter() {
	if( INVALID_HANDLE_VALUE != hPrinterDataFile )
		CloseHandle( hPrinterDataFile );
}

STDMETHODIMP CTSPrinter::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITSPrinter
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CTSPrinter::AddTSMonitor(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	MONITOR_INFO_2 mi2;

	mi2.pName = TS_MONITORNAME;
	mi2.pEnvironment = TS_ENVIRONMENT;
	mi2.pDLLName = "tsdmon.dll";

	if( 0 == AddMonitor( NULL, 2, (LPBYTE)&mi2 ) )
		*pResult = GetLastError();
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::DeleteTSMonitor(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( 0 == DeleteMonitor( NULL, TS_ENVIRONMENT, TS_MONITORNAME ) )
		*pResult = GetLastError();
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::AddTSPort(long hWnd, long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( 0 == AddPort( NULL, (HWND)hWnd, TS_MONITORNAME ) )
		*pResult = GetLastError();
	else
		*pResult = 0;
	
	return S_OK;
}

STDMETHODIMP CTSPrinter::DeleteTSPort(long hWnd, long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	PORT_INFO_2 pi2[100];
	DWORD cbNeeded;
	DWORD cReturned;

	if( 0 == EnumPorts( NULL, 2, (unsigned char*)pi2, sizeof(pi2), &cbNeeded, &cReturned ) )
		*pResult = GetLastError();
	else
		*pResult = 0;


	if( 0 == DeletePort( NULL, (HWND)hWnd, TS_PORTNAME ) )
		*pResult = GetLastError();
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::AddTSPrinterDriver(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	DRIVER_INFO_3 dri3;
	dri3.cVersion = 4;
	dri3.pName = TS_PRINTERDRIVERNAME;
	dri3.pEnvironment = TS_ENVIRONMENT;
    dri3.pDriverPath = "RASDD.DLL";
	dri3.pDataFile = "tsdprn.dll";
	dri3.pConfigFile = "RASDDUI.DLL";
    dri3.pHelpFile = "RASDDUI.HLP";
	dri3.pDependentFiles = "tsdprn.dll\0RASDD.DLL\0RASDDUI.DLL\0RASDDUI.HLP\0";
	dri3.pMonitorName = TS_MONITORNAME;
    dri3.pDefaultDataType = "RAW"; 

	if( 0 == AddPrinterDriver( NULL, 3, (LPBYTE)&dri3 ) )
		*pResult = GetLastError();
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::DeleteTSPrinterDriver(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( 0 == DeletePrinterDriver( NULL, TS_ENVIRONMENT, TS_PRINTERDRIVERNAME/*, DPD_DELETE_UNUSED_FILES, 0 */) )
		*pResult = GetLastError();
	else
		*pResult = 0;


	return S_OK;
}

STDMETHODIMP CTSPrinter::AddTSPrinter(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	DEVMODE dm;
	memset( &dm, '\0', sizeof(dm) );
	strcpy((char*)dm.dmDeviceName,TS_PRINTERNAME);

	PRINTER_INFO_2 pri2;
	pri2.pServerName = NULL;
	pri2.pPrinterName = TS_PRINTERNAME; 
    pri2.pShareName = "";
	pri2.pPortName = "TSDV:";
	pri2.pDriverName = TS_PRINTERDRIVERNAME;
	pri2.pComment = "";
	pri2.pLocation = "";
	pri2.pDevMode = &dm; 
    pri2.pSepFile = "";
	pri2.pPrintProcessor = "winprint";
	pri2.pDatatype = "";
	pri2.pParameters = "";
	pri2.pSecurityDescriptor = NULL; 
    pri2.Attributes = 0;
	pri2.Priority = 1; 
    pri2.DefaultPriority = 0;
	pri2.StartTime = 0; 
    pri2.UntilTime = 0;
	pri2.Status = PRINTER_STATUS_OFFLINE;
	pri2.cJobs = 0; 
    pri2.AveragePPM = 0; 

	if( 0 == AddPrinter( NULL, 2, (LPBYTE)&pri2 ) )
		*pResult = GetLastError();
	else
		*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::DeleteTSPrinter(long * pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
 HANDLE hPrinter;
 DEVMODE dm;
 PRINTER_DEFAULTS pd;
	
	memset( &dm, '\0', sizeof(dm) );
	strcpy((char*)dm.dmDeviceName,TS_PRINTERNAME);

	pd.pDevMode = &dm; 
	pd.pDatatype = "RAW";
	pd.DesiredAccess = PRINTER_ALL_ACCESS;

	if( OpenPrinter(TS_PRINTERNAME, &hPrinter, &pd) ) {
		if( 0 == DeletePrinter( hPrinter ) )
			*pResult = GetLastError();
		else
			*pResult = 0;
	}
	else
		*pResult = GetLastError();

	return S_OK;
}

STDMETHODIMP CTSPrinter::TSFormatMessage(long lError, BSTR * strMessage, long * pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		lError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	CComBSTR bstrMessage( (char*)lpMsgBuf);
	LocalFree( lpMsgBuf );

	*strMessage = bstrMessage.Detach();
	*pResult = 0;

	return S_OK;
}

STDMETHODIMP CTSPrinter::LoadPrinterOutput(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	
	if( INVALID_HANDLE_VALUE != hPrinterDataFile )
		CloseHandle( hPrinterDataFile );

	hPrinterDataFile = CreateFile(OLE2A(strFileName), 
						   GENERIC_READ, 
						   0, 
						   0, 
						   OPEN_EXISTING, 
						   FILE_ATTRIBUTE_READONLY, 
						   0);

	if (hPrinterDataFile == INVALID_HANDLE_VALUE)
		*pResult = GetLastError();
	else {
		dwPrinterDataSize = GetFileSize(hPrinterDataFile, NULL);
		iDocumentCounter = 0;
		iPageCounter = 0;
		iBlockCounter = 0;
		lByteCounter = 0;
		*pResult = 0;
	}

	return S_OK;
}



void WriteDibHdr( HANDLE hFile )
{
 BITMAPFILEHEADER bmfh;
 BITMAPINFOHEADER bmi;
 DWORD dwBytes = 0;
 DWORD aRGBQ[2];
 DWORD cbWritten;
 BOOL    rc;

 WORD wHdrSize;

   // compute hdr and color table size
   wHdrSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (2*sizeof(RGBQUAD));

   // initialize BITMAPFILEHEADER
   bmfh.bfType = ('B'|('M'<<8));
   bmfh.bfSize =  sizeof(BITMAPFILEHEADER) + 
                  sizeof(BITMAPINFOHEADER) +
                  (2*sizeof(RGBQUAD)) + uiBytesPerBMPLine * iLineCounter;
//                  lpXPDV->dwTotalScanBytes ;
   bmfh.bfReserved1 =
   bmfh.bfReserved2 = 0;
   bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (2*sizeof(RGBQUAD));

   // initialize BITMAPINFOHEADER
   bmi.biSize          = sizeof(BITMAPINFOHEADER);
//   bmi.biWidth         = (lpXPDV->dwTotalScanBytes/lpXPDV->dwTotalScans) * 8;
//   bmi.biHeight        = lpXPDV->dwTotalScans;
   bmi.biWidth         = uiBytesPerBMPLine * 8;
   bmi.biHeight        = iLineCounter;
   bmi.biPlanes        = 
   bmi.biBitCount      = 1;  
   bmi.biCompression   = BI_RGB;  
   bmi.biSizeImage     =   
   bmi.biXPelsPerMeter =   
   bmi.biYPelsPerMeter =   
   bmi.biClrUsed       =   
   bmi.biClrImportant  = 0;  

   // set up DIB's color table
   aRGBQ[0] = (DWORD)0;              // black
   aRGBQ[1] = (DWORD)0xFFFFFF;       // white

   // write DIB header to disk file
//   _llseek(lpXPDV->hDIBFile, 0, 0);

   // write BITMAPFILEHEADER to DIB file
   rc = WriteFile(hFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER), &cbWritten, NULL);
   dwBytes += cbWritten;
//   wBytes += _lwrite(lpXPDV->hDIBFile, (LPSTR)&bmfh, sizeof(BITMAPFILEHEADER));

   // write BITMAPINFOHEADER to DIB file
   rc = WriteFile(hFile, (LPSTR)&bmi, sizeof(BITMAPINFOHEADER), &cbWritten, NULL);
   dwBytes += cbWritten;
//   wBytes += _lwrite(lpXPDV->hDIBFile, (LPSTR)&bmi, sizeof(BITMAPINFOHEADER));

   // write DIB's color table to DIB file
   rc = WriteFile(hFile, (LPSTR)aRGBQ, 2*sizeof(RGBQUAD), &cbWritten, NULL);
   dwBytes += cbWritten;
//   wBytes += _lwrite(lpXPDV->hDIBFile, (LPSTR)aRGBQ, 2*sizeof(RGBQUAD));

} //*** WriteDibHdr

BYTE* GetByte(void) {
	if( 0 == cbLineBuffer ) {
		if (!ReadFile(hPrinterDataFile, baBuffer, 4096, &cbLineBuffer, 0)) {
			return NULL;
		}
		else {
			iBlockCounter++;
			lByteCounter += cbLineBuffer;
			pLineBuffer = baBuffer;
		}
	}
	cbLineBuffer--;
	return pLineBuffer++;
}

STDMETHODIMP CTSPrinter::SavePage(BSTR strFileName, long *pResult)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	HRESULT hResult;
	HANDLE hFile;
	bool tPageSaved;
	LPBYTE pByte;
	LPBYTE pByteBuffer;
	DWORD cbByte;
	DWORD cbWritten;
	DWORD cbLineByte;

	char strMessage[256];

	tPageSaved = false;
	hResult = 0;
	cbLineByte = 0;

	pByteBuffer = GetByte();
	if( NULL == pByteBuffer )
		hResult = 0x1002;
	while(  false == tPageSaved && 0 == hResult ) {
		if( *pByteBuffer == 0x1B ) {
			pByteBuffer = GetByte();
			if( NULL == pByteBuffer )
				hResult = 0x1002;
			else {
				switch( *pByteBuffer ) {
				case 'A':	//PC_OCD_BEGINDOC
					iDocumentCounter++;
					iPageCounter = 0;
					break;
				case 'B':	// PC_OCD_BEGINPAGE
					memset(bitmapbuf,0,sizeof(bitmapbuf));
					iLineCounter = 0;
					memset(bitmapbuf[iLineCounter],0xFF,uiBytesPerBMPLine);
					break;
				case 'J':	//CM_OCD_YM_REL
					pByteBuffer = GetByte();
					if( NULL == pByteBuffer )
						hResult = 0x1002;
					else {
						cbByte = *pByteBuffer;
						if( cbByte != 6 )
							cbByte = cbByte;
						if( lByteCounter >= 57344 )
							cbByte = cbByte;
						while(cbByte != 0) {
							BYTE bx;
							bx = bLinesPerPixel;
							while( bx != 0 && cbByte != 0 ) {
								bx--;
								cbByte--;
							}
							iLineCounter++;
							memset(bitmapbuf[iLineCounter],0xFF,uiBytesPerBMPLine);
						}
					}
					break;
				case 'P':
					tLandscape = false;
					break;
				case 'L':
					tLandscape = true;
					break;
				case 0x0A:
				case 0x0C:
				case 0x0D:
				case 0x1B:
					break;
				case 'R':	//RESOLUTION
					pByteBuffer = GetByte();
					if( NULL == pByteBuffer )
						hResult = 0x1002;
					else {
						iResolution = (int)(*pByteBuffer) * 10;
						switch( iResolution ) {
						case 100:
							bLinesPerPixel = 6;
							if( tLandscape ) {
								uiBytesPerLine = 147;
								uiBytesPerBMPLine = 148;
							}
							else {
								uiBytesPerLine = 104;
								uiBytesPerBMPLine = 104;
							}
							break;
						case 200:
							bLinesPerPixel = 3;
							if( tLandscape ) {
								uiBytesPerLine = 293;
								uiBytesPerBMPLine = 296;
							}
							else {
								uiBytesPerLine = 207;
								uiBytesPerBMPLine = 208;
							}
							break;
						case 300:
							bLinesPerPixel = 2;
							if( tLandscape ) {
								uiBytesPerLine = 439;
								uiBytesPerBMPLine = 440;
							}
							else {
								uiBytesPerLine = 311;
								uiBytesPerBMPLine = 312;
							}
							break;
						case 600:
							bLinesPerPixel = 1;
							if( tLandscape ) {
								uiBytesPerLine = 877;
								uiBytesPerBMPLine = 880;
							}
							else {
								uiBytesPerLine = 621;
								uiBytesPerBMPLine = 624;
							}
							break;
						}
					}
					break;
				case 'Y':	// PC_OCD_ENDPAGE
					iPageCounter++;
					hFile = CreateFile( OLE2A(strFileName),
									   GENERIC_WRITE,
									   FILE_SHARE_READ | FILE_SHARE_WRITE,
									   NULL,
									   CREATE_ALWAYS,
									   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
									   NULL );
					if (hFile != INVALID_HANDLE_VALUE) {
						WriteDibHdr( hFile );
						for( iLineCounter--; 0 == hResult && iLineCounter>=0; iLineCounter-- ) {				
							if( !WriteFile(hFile, bitmapbuf[iLineCounter], uiBytesPerBMPLine, &cbWritten, NULL) )
								hResult = GetLastError();	
						}
						CloseHandle(hFile);
						tPageSaved = true;				
						hResult = 0;
						hFile = INVALID_HANDLE_VALUE;
					}
					else
						hResult = 0x1002;
					break;
				case 'Z':	// PC_OCD_ENDDOC
					hResult = 1;
					break;
				default:
					wsprintf( strMessage, "SavePage(%X)\n",*(pLineBuffer+1) );
					MessageBox(0, strMessage, "TSPrint", 0);
					hResult = 0x10FF;
				}
				if( !tPageSaved && 0 == hResult) {
					pByteBuffer = GetByte();
					if( NULL == pByteBuffer )
						hResult = 0x1002;
				}
			}
		}	
		else {
			pByte = bitmapbuf[iLineCounter];
			cbLineByte = uiBytesPerLine;
			do {
				*pByte = ~(*pByteBuffer);
				pByte++;
				cbLineByte--;
				pByteBuffer = GetByte();
				if( NULL == pByteBuffer ) {
					cbLineByte = 0;
					hResult = 0x1002;
				}
			} while( cbLineByte > 0 );
		}
	}

	*pResult = hResult;

	return S_OK;
}

STDMETHODIMP CTSPrinter::spezial1()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CoFreeUnusedLibraries();

	return S_OK;
}

//	CPrintHandler
//
//	Führt den Druck der Anlagen laut Liste aus

#include "StdAfx.h"
#include "Resource.h"
#include "PrintAnlage.h"

#include "PrintHandler.h"

static BOOL	g_bUserAbort;

/////////////////////////////////////////////////////////////////////////////
// Printing Dialog

class CPrintingDialog : public CDialog
{
public:
	//{{AFX_DATA(CPrintingDialog)
	enum { IDD = AFX_IDD_PRINTDLG };
	//}}AFX_DATA
	CPrintingDialog::CPrintingDialog( CWnd* pParent )
	{
		Create( CPrintingDialog::IDD, pParent );      // modeless !
		g_bUserAbort = FALSE;
	}
	virtual ~CPrintingDialog() { }

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};

BOOL CPrintingDialog::OnInitDialog()
{
//	SetWindowText( AfxGetAppName());
	SetWindowText( g_cbTRiAS );
	CenterWindow();
	return CDialog::OnInitDialog();
}

void CPrintingDialog::OnCancel()
{
	g_bUserAbort = TRUE;	// flag that user aborted print
	CDialog::OnCancel();
}


/////////////////////////////////////////////////////////////////////////////
//	Print Handler
CPrintHandler::CPrintHandler()
{
	m_pPA = NULL;
}

CPrintHandler::~CPrintHandler()
{
}

BOOL CALLBACK _GbmAbortProc( HDC, int )
{
	MSG	msg;
	while ( !g_bUserAbort && ::PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ))
	{
		if ( !AfxGetThread() -> PumpMessage())
			return FALSE;	// terminate if WM_QUIT received
	}
	return !g_bUserAbort;
}

void CPrintHandler::Print()
{
	// get default print info
	CPrintInfo printInfo;
	ASSERT( printInfo.m_pPD != NULL );	// must be set

	printInfo.SetMaxPage( m_pPrintListe -> GetSize());
	if ( m_pPrintListe -> GetSize() == 0 )	printInfo.SetMaxPage( 1 );

	if ( OnPreparePrinting( &printInfo ))
	{
		// hDC must be set (did you remember to call DoPreparePrinting?)
		ASSERT(printInfo.m_pPD -> m_pd.hDC != NULL);

		// gather file to print to if print-to-file selected
		CString		strOutput;
		CString		strDef( MAKEINTRESOURCE( AFX_IDS_PRINTDEFAULTEXT ));
		CString		strPrintDef( MAKEINTRESOURCE( AFX_IDS_PRINTDEFAULT ));
		CString		strFilter( MAKEINTRESOURCE( AFX_IDS_PRINTFILTER ));
		CString		strCaption( MAKEINTRESOURCE( AFX_IDS_PRINTCAPTION ));
		CFileDialog		*pDlg;

		if ( printInfo.m_pPD -> m_pd.Flags & PD_PRINTTOFILE )
		{
			// construct CFileDialog for browsing
			pDlg = new CFileDialog( FALSE, strDef, strPrintDef,
								OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
			pDlg -> m_ofn.lpstrTitle = strCaption;

			if ( pDlg -> DoModal() != IDOK )	return;

			// set output device to resulting path name
			strOutput = pDlg -> GetPathName();
			delete pDlg;
			pDlg = NULL;
		}

		// set up document info and start the document printing process
		CString		strTitle( MAKEINTRESOURCE( IDS_PRINTTITLE ));

		if ( strTitle.GetLength() > 31 )	strTitle.ReleaseBuffer( 31 );

		DOCINFO		docInfo;
		memset( &docInfo, 0, sizeof( DOCINFO ));
		docInfo.cbSize = sizeof( DOCINFO );
		docInfo.lpszDocName = strTitle;

		CString		strPortName;
		int			nFormatID;

		if ( strOutput.IsEmpty())
		{
			docInfo.lpszOutput = NULL;
			strPortName = printInfo.m_pPD -> GetPortName();
			nFormatID = AFX_IDS_PRINTONPORT;
		}
		else
		{
			docInfo.lpszOutput = strOutput;
			::GetFileTitle( strOutput, strPortName.GetBuffer( _MAX_PATH ), _MAX_PATH );
			nFormatID = AFX_IDS_PRINTTOFILE;
		}

		// setup the printing DC
		CDC		dcPrint;
		dcPrint.Attach( printInfo.m_pPD -> m_pd.hDC );  // attach printer dc
		dcPrint.m_bPrinting = TRUE;
		OnBeginPrinting( &dcPrint, &printInfo );
		dcPrint.SetAbortProc( _GbmAbortProc );

		// disable main window while printing & init printing status dialog
		AfxGetMainWnd() -> EnableWindow( FALSE );
		CPrintingDialog		dlgPrintStatus( AfxGetMainWnd());

		CString		strTemp;
		dlgPrintStatus.SetDlgItemText( AFX_IDC_PRINT_DOCNAME, strTitle );
		dlgPrintStatus.SetDlgItemText( AFX_IDC_PRINT_PRINTERNAME, printInfo.m_pPD -> GetDeviceName());
		AfxFormatString1( strTemp, nFormatID, strPortName );
		dlgPrintStatus.SetDlgItemText( AFX_IDC_PRINT_PORTNAME, strTemp );
		dlgPrintStatus.ShowWindow( SW_SHOW );
		dlgPrintStatus.UpdateWindow();

		// start document printing process
		if ( dcPrint.StartDoc( &docInfo ) == SP_ERROR )
		{
			// enable main window before proceeding
			AfxGetMainWnd() -> EnableWindow(TRUE);

			// cleanup and show error message
			OnEndPrinting( &dcPrint, &printInfo );
			dlgPrintStatus.DestroyWindow();
			dcPrint.Detach();		// will be cleaned up by CPrintInfo destructor
			AfxMessageBox( AFX_IDP_FAILED_TO_START_PRINT );
			return;
		}

		// Guarantee values are in the valid range
		UINT	nEndPage = printInfo.GetToPage();
		UINT	nStartPage = printInfo.GetFromPage();

		if ( nEndPage < printInfo.GetMinPage())		nEndPage = printInfo.GetMinPage();
		if ( nEndPage > printInfo.GetMaxPage())		nEndPage = printInfo.GetMaxPage();

		if ( nStartPage < printInfo.GetMinPage())	nStartPage = printInfo.GetMinPage();
		if ( nStartPage > printInfo.GetMaxPage())	nStartPage = printInfo.GetMaxPage();

		int	nStep = ( nEndPage >= nStartPage) ? 1 : -1;
		nEndPage = (nEndPage == 0xffff) ? 0xffff : nEndPage + nStep;

		VERIFY( strTemp.LoadString( AFX_IDS_PRINTPAGENUM ));

		// begin page printing loop
		BOOL	bError = FALSE;
		short	iLoop = 0;
		short	i;
		CString	strLastGS, strCurGS;

		for ( printInfo.m_nCurPage = nStartPage;
				printInfo.m_nCurPage != nEndPage;
				printInfo.m_nCurPage += nStep )
		{
			OnPrepareDC( &dcPrint, &printInfo );

			// check for end of print
			if ( !printInfo.m_bContinuePrinting )	break;

			i = printInfo.m_nCurPage - 1;
			strCurGS = m_pPrintListe -> GetAt( i );
			if ( !strCurGS.IsEmpty())
				strCurGS = strCurGS.Mid( 1 );

			ASSERT( printInfo.m_bContinuePrinting );
			if ( ++iLoop >= 50 )
			{
				if ( !( strCurGS == strLastGS ))
				{
					iLoop = 0;
					dcPrint.EndDoc();
					if ( printInfo.m_pPD -> m_pd.Flags & PD_PRINTTOFILE )
					{
						// construct CFileDialog for browsing
						pDlg = new CFileDialog( FALSE, strDef, strPrintDef,
											OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
						pDlg -> m_ofn.lpstrTitle = strCaption;

						if ( pDlg -> DoModal() != IDOK )	return;

						// set output device to resulting path name
						strOutput = pDlg -> GetPathName();
						delete pDlg;
						pDlg = NULL;

						if ( strOutput.IsEmpty())
						{
							docInfo.lpszOutput = NULL;
							strPortName = printInfo.m_pPD -> GetPortName();
							nFormatID = AFX_IDS_PRINTONPORT;
						}
						else
						{
							docInfo.lpszOutput = strOutput;
							::GetFileTitle( strOutput, strPortName.GetBuffer( _MAX_PATH ), _MAX_PATH );
							nFormatID = AFX_IDS_PRINTTOFILE;
						}
					}
				
					if ( dcPrint.StartDoc( &docInfo ) == SP_ERROR )
					{
						bError = TRUE;
						AfxMessageBox( AFX_IDP_FAILED_TO_START_PRINT );
						break;
					}
				}
			}
			strLastGS = strCurGS;

			// write current page
			TCHAR szBuf[80];
			wsprintf( szBuf, strTemp, printInfo.m_nCurPage );
			dlgPrintStatus.SetDlgItemText( AFX_IDC_PRINT_PAGENUM, szBuf );

			// set up drawing rect to entire page (in logical coordinates)
			printInfo.m_rectDraw.SetRect( 0, 0, dcPrint.GetDeviceCaps( HORZRES ),
												dcPrint.GetDeviceCaps( VERTRES ));
//			dcPrint.DPtoLP( &printInfo.m_rectDraw );

			// attempt to start the current page
			if ( dcPrint.StartPage() < 0 )
			{
				bError = TRUE;
				AfxMessageBox( IDS_ERROR_STARTPAGE );
				break;
			}

			// must call OnPrepareDC on newer versions of Windows because
			// StartPage now resets the device attributes.
			OnPrepareDC( &dcPrint, &printInfo );

			// page successfully started, so now render the page
			OnPrint( &dcPrint, &printInfo );
			if ( dcPrint.EndPage() < 0 || !_GbmAbortProc( dcPrint.m_hDC, 0 ))
			{
				bError = TRUE;
				AfxMessageBox( IDS_ERROR_ENDPAGE );
				break;
			}
		}

		// cleanup document printing process
		if (!bError)	dcPrint.EndDoc();
		else			dcPrint.AbortDoc();

		AfxGetMainWnd() -> EnableWindow();    // enable main window

		OnEndPrinting(&dcPrint, &printInfo);    // clean up after printing
		dlgPrintStatus.DestroyWindow();

		dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
	}
}	// Print

BOOL CPrintHandler::OnPreparePrinting( CPrintInfo* pInfo )
{
	ASSERT( pInfo != NULL );
	ASSERT( pInfo->m_pPD != NULL );

	// don't prompt the user if we're doing print preview, printing directly,
	// or printing via IPrint and have been instructed not to ask

	CWinApp*	pApp = AfxGetApp();
	if ( pInfo -> m_bPreview || pInfo -> m_bDirect ||
		( pInfo -> m_bDocObject && !( pInfo->m_dwFlags & PRINTFLAG_PROMPTUSER )))
	{
		if ( pInfo -> m_pPD -> m_pd.hDC == NULL )
		{
			// if no printer set then, get default printer DC and create DC without calling
			//   print dialog.
			if ( !pApp -> GetPrinterDeviceDefaults( &pInfo -> m_pPD -> m_pd ))
			{
				// bring up dialog to alert the user they need to install a printer.
				if ( !pInfo -> m_bDocObject || ( pInfo -> m_dwFlags & PRINTFLAG_MAYBOTHERUSER ))
					if ( pApp -> DoPrintDialog( pInfo -> m_pPD ) != IDOK )
						return FALSE;
			}

			if ( pInfo -> m_pPD -> m_pd.hDC == NULL )
			{
				// call CreatePrinterDC if DC was not created by above
				if ( pInfo -> m_pPD -> CreatePrinterDC() == NULL )
					return FALSE;
			}
		}

		// set up From and To page range from Min and Max
		pInfo -> m_pPD -> m_pd.nFromPage = (WORD)pInfo -> GetMinPage();
		pInfo -> m_pPD -> m_pd.nToPage = (WORD)pInfo -> GetMaxPage();
	}
	else
	{
		// otherwise, bring up the print dialog and allow user to change things

		// preset From-To range same as Min-Max range

		pInfo -> m_pPD -> m_pd.nFromPage = (WORD)pInfo -> GetMinPage();
		pInfo -> m_pPD -> m_pd.nToPage = (WORD)pInfo -> GetMaxPage();

		if ( pApp -> DoPrintDialog( pInfo -> m_pPD ) != IDOK )
			return FALSE;		// do not print
	}

	ASSERT( pInfo -> m_pPD != NULL );
	ASSERT( pInfo -> m_pPD -> m_pd.hDC != NULL );

	pInfo -> m_nNumPreviewPages = pApp -> m_nNumPreviewPages;
	VERIFY( pInfo -> m_strPageDesc.LoadString( AFX_IDS_PREVIEWPAGEDESC ));
	return TRUE;
}	// OnPreparePrinting

void CPrintHandler::OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	ASSERT( m_pPA == NULL );

	int				i;
	CString			text, ide;

	m_strEqIDE.Empty();
	if ( m_pPrintListe )
	{
		for ( i = 0; i < m_pPrintListe -> GetSize(); i++ )
		{
			text = m_pPrintListe -> GetAt( i );
			if ( !text.IsEmpty())
			{
				ide = text.Mid( 1 );
				if ( m_strEqIDE.IsEmpty())	m_strEqIDE = ide;
				else						m_strEqIDE = Identisch( ide, m_strEqIDE );
			}
		}
	}

	m_pPA = new CPrintAnlage1( "XX", 0L );
	m_pPA -> CreateStaticMembers( pDC, m_strEqIDE );

	if ( pInfo )
	{
		pInfo -> SetMaxPage( m_pPrintListe -> GetSize());
		pInfo -> m_strPageDesc.LoadString( IDS_PREV_PAGE_DESC );

		if ( m_pPrintListe -> GetSize() == 0 )	pInfo -> SetMaxPage( 1 );
	}
}

void CPrintHandler::OnEndPrinting( CDC* pDC, CPrintInfo* pInfo )
{
/*	Die Freigabe erfolgt erst beim beenden des Programmes
	m_pPA -> DeleteStaticMembers();
	delete m_pPA;
*/
	m_pPA = NULL;
}

void CPrintHandler::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(pDC);

//	if (m_nZoomState == ZOOM_OUT)
//		CView::OnPrepareDC(pDC, pInfo);
//	else if (m_pPageInfo[0].sizeScaleRatio.cx != 0)
//		CScrollView::OnPrepareDC(pDC, pInfo);

// CView::OnPrepareDC
	ASSERT_VALID(pDC);
	UNUSED(pDC);	// unused in release builds

	// Default to one page printing if doc length not known
	if (pInfo != NULL)
		pInfo -> m_bContinuePrinting =
			( pInfo -> GetMaxPage() != 0xffff || ( pInfo -> m_nCurPage == 1 ));
}

void CPrintHandler::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
	CPrintAnlage	*pPA;
	CxString		text, ide, enr;
	char			c;
	short			i = pInfo -> m_nCurPage - 1;
	BOOL			fehler = FALSE;

	ASSERT( m_pPrintListe );

	if ( i < m_pPrintListe -> GetSize())
	{
		pPA = NULL;
		text = m_pPrintListe -> GetAt( i );
		if ( !text.IsEmpty())
		{
			ide = text.Mid( 2 );
			c = text[0];
			ide.Teilen( enr, ide, ')' );
			text.Empty();

			switch ( c )
			{
			case '1':
				text = " Erfassungsblatt Seite 1";
				pPA = new CPrintAnlage1( ide, enr.Long());
				break;
			case '2':
				text = " Erfassungsblatt Seite 2";
				pPA = new CPrintAnlage2( ide, enr.Long());
				break;
			case '3':
				text = " Erfassungsblatt Seite 3";
				pPA = new CPrintAnlage3( ide, enr.Long());
				break;
			case '4':
				text = " Beitragsbescheid";
				pPA = new CPrintAnlage7( ide, enr.Long());
				pPA -> m_cKennung = '7';
				break;
			case '5':
				text = " InfoBrief Beitragsbescheid";
				pPA = new CPrintAnlage7( ide, enr.Long());
				pPA -> m_cKennung = '8';
				break;
			case '6':
				text = " Anlage Beitragsbescheid";
				pPA = new CPrintAnlage4( ide, enr.Long());
				break;
			case '7':
				text = " Bescheid Niederschlagswassergebühr";
				pPA = new CPrintAnlage7( ide, enr.Long());
				pPA -> m_cKennung = '9';
				break;
			case '8':
				text = " InfoBrief Gebührenbescheid";
				pPA = new CPrintAnlage7( ide, enr.Long());
				pPA -> m_cKennung = 'A';
				break;
			case '9':
				text = " Anlage Gebührenbescheid";
				pPA = new CPrintAnlage5( ide, enr.Long());
				break;
			case 'A':
				text = " Anlage - öffentliche Flächen -";
				pPA = new CPrintAnlage6( ide, enr.Long());
				break;
			case 'B':
				text = " Massstabsgerechte Lageskizze -";
				pPA = new CPrintAnlage8( ide, enr.Long());
				break;
			}
		}
		else
		{
			AfxMessageBox( IDS_ERROR_LISTEINTRAG );
			fehler = TRUE;
		}

		if ( pPA )
		{
			if ( NULL == pPA -> m_pNF_PG1 )		pPA -> CreateStaticMembers( pDC, m_strEqIDE );

			pPA -> Print( pDC );
			delete pPA;
		}
		else
			if ( !fehler )
				AfxMessageBox( IDS_ERROR_DRUCKSEITE );
	}
	else
	{
		AfxMessageBox( IDS_ERROR_PRINTLIST );
//		RenderGeoDB( pDC );
	}
}

CString CPrintHandler::Identisch( const char* ide1, const char* ide2 )
{
	ASSERT( AfxIsValidString( ide1 ));
	ASSERT( AfxIsValidString( ide2 ));

	CString		result;
	BOOL		fertig = FALSE;

	while ( !fertig )
	{
		fertig = (( *ide1 == '\0' ) || ( *ide2 == '\0' ));
		if ( !fertig )
		{
			if ( *ide1 == *ide2 )	result += *ide1;
			else					fertig = TRUE;
			ide1++;
			ide2++;
		}
	}

	return result;
}


void CPrintHandler::RenderGeoDB( CDC* pDC )
{
	BOOL	abbruch = FALSE;
	long	c[4];

	HENHMETAFILE	hMetaFile;
	CRect	rcDest, rcPict;
	CSize	size;
	CPoint	pt;
	CSize	sz;

	// get size of printer page (in pixels)
	int cxPage = pDC -> GetDeviceCaps(HORZRES);
	int cyPage = pDC -> GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC -> GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC -> GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

	rcDest.top    += 2;
	rcDest.bottom -= 2;
	rcDest.left   += 2;
	rcDest.right  -= 2;
	rcPict = rcDest;

	size.cx = rcDest.left;
	size.cy = rcDest.top;
	pDC -> LPtoHIMETRIC( &size );
	rcDest.left = size.cx;
	rcDest.top  = size.cy;
	size.cx = rcDest.right;
	size.cy = rcDest.bottom;
	pDC -> LPtoHIMETRIC( &size );
	rcDest.right  = size.cx;
	rcDest.bottom = size.cy;

	RECTL		cont;

	DEX_GetActiveSightContainer( c );

	if ( !abbruch )
	{
		cont.left   = c[0];
		cont.top    = c[3];
		cont.right  = c[1];
		cont.bottom = c[2];
	}

	if ( !abbruch )
	{
		RENDERGEODB		sRend;
		RECTL			rectl;
		HDC				hdcMetaFile;

		::SaveDC( pDC -> m_hDC );
		::SetMapMode( pDC -> m_hDC, MM_HIMETRIC );

		rectl.bottom = labs( rcDest.bottom - rcDest.top );
		rectl.top    = 0L;
		rectl.right  = labs( rcDest.right - rcDest.left );
		rectl.left   = 0L;
		rcPict.top    = rectl.top;
		rcPict.bottom = rectl.bottom;
		rcPict.left   = rectl.left;
		rcPict.right  = rectl.right;

		hdcMetaFile = CreateEnhMetaFile( pDC -> m_hDC, "C:\\TEMP\\Meta2.tmp", &rcPict, NULL );

		sRend.dwSize              = sizeof( RENDERGEODB );
		sRend.m_hDC               = hdcMetaFile;
		sRend.m_hTargetDC         = pDC -> m_hDC;

		sRend.m_rclFrame.left     = 0L;
		sRend.m_rclFrame.top      = rectl.bottom;
		sRend.m_rclFrame.right    = rectl.right;
		sRend.m_rclFrame.bottom   = 0L;
		sRend.m_rclClipBox        = sRend.m_rclFrame;

		sRend.m_rclGeoDB.left     = cont.left;
		sRend.m_rclGeoDB.top      = cont.top;
		sRend.m_rclGeoDB.right    = cont.right;
		sRend.m_rclGeoDB.bottom   = cont.bottom;

		::SetMapMode( hdcMetaFile, MM_HIMETRIC );
		::SetWindowOrgEx( hdcMetaFile, 0, (int)( sRend.m_rclFrame.top - sRend.m_rclFrame.bottom ), NULL );

		if ( hdcMetaFile )
		{
			DexExtensionProc((WPARAM)DEX_RENDERGEODB, (LPARAM)&sRend );
			hMetaFile = CloseEnhMetaFile( hdcMetaFile );
		}
		else
			AfxMessageBox( "Kein MetaFile verfügbar!" );

		::RestoreDC( pDC -> m_hDC, -1 );
	}

	if ( hMetaFile )
	{
		CRgn	rgn;
		CRect	DestRect;
		POINT	pt1, pt2;

		DestRect.bottom = - rcDest.bottom;
		DestRect.top    = - rcDest.top;
		DestRect.left   = rcDest.left;
		DestRect.right  = rcDest.right;
		pDC -> SetMapMode( MM_HIMETRIC );

		pt1.x = DestRect.left + 100;
		pt1.y = DestRect.top - 100;
		pt2.x = DestRect.right - 100;
		pt2.y = DestRect.bottom + 100;

		pDC -> IntersectClipRect( pt1.x, pt1.y, pt2.x, pt2.y );
		pDC -> PlayMetaFile( hMetaFile, &DestRect );

		DeleteEnhMetaFile( hMetaFile );
		hMetaFile = NULL;
	}
	else
		AfxMessageBox( "Kein MetaFile entstanden!" );
}

// AbfView.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp

#include "numedit.h"	// CErzNrEdit
#include "gaksete.h"	// CDaoRecordsetExt
#include "gakset.h"		// CErzSet
#include "AbfSet.h"		// CAbfSet
#include "documext.h"	// CDocumentExt
#include "abfdoc.h"		// CDocument
#include "abfpage.h"	// CAbfPage	
#include "branpage.h"	// CBranchPage
#include "TransPge.h"	// CTransPage
#include "EntPage.h"	// CEntPage
#include "BetrPage.h"	// CBetreiberPage
#include "abfsheet.h"	// CAbfSheet	
#include "childfrm.h"	// CChildFrame
#include "changenr.h"	// CChangeNummerDlg
#include "selset.h"		// CSelectSet
#include "abfArset.h"	// CAbfArtSet
#include "selnum.h"		// CSelectNumberDlg
#include "recview.h"	// CDaoRecordViewExt	
#include "AbfView.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	lokale Konstanten
// const short AbfPrintBufferSize = 2048;			// Puffergröße zum Drucken eines Formulars

// externe Variablen
extern CGakSet *g_pErzSet;

// externe Funktionen
void CALLBACK SetAbfallArt (LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// CAbfView
IMPLEMENT_DYNCREATE(CAbfView, CDaoRecordViewExt)

BEGIN_MESSAGE_MAP(CAbfView, CDaoRecordViewExt)
	//{{AFX_MSG_MAP(CAbfView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_GOTO_BOOKMARK, OnGotoBookmark)
	ON_UPDATE_COMMAND_UI(IDM_GOTO_BOOKMARK, OnUpdateGotoBookmark)
	ON_COMMAND(IDM_SET_BOOKMARK, OnSetBookmark)
	ON_COMMAND(IDM_NEW_REKORD, OnNewRekord)
	ON_UPDATE_COMMAND_UI(IDM_NEW_REKORD, OnUpdateNewRekord)
	ON_COMMAND(IDM_DELETE_REKORD, OnDeleteAbfallGruppe)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateNewRekord)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateNewRekord)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateNewRekord)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateNewRekord)	
	//}}AFX_MSG_MAP
// Record navigation enabled like AddNew
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfView diagnostics

#ifdef _DEBUG
void CAbfView::AssertValid() const
{
	CDaoRecordViewExt::AssertValid();
}

void CAbfView::Dump(CDumpContext& dc) const
{
	CDaoRecordViewExt::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAbfView database support
CDaoRecordset* CAbfView::OnGetRecordset()
{
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);
	return m_pSet;
}

void CAbfView::OnInitialUpdate()
{
	m_pSet = &GetDocument() -> m_AbfSet;
	CDaoRecordViewExt::OnInitialUpdate();
}

int CAbfView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDaoRecordViewExt::OnCreate (lpCreateStruct) == -1)
		return -1;
	
//	TODO: Add your specialized creation code here
	m_pSheet = new CAbfSheet (AFX_IDS_APP_TITLE, this);
	if (!m_pSheet->Create (this, WS_CHILD | WS_VISIBLE, 0))
	{
		DELETE_OBJ (m_pSheet);
		return -1;
	}

//	Fenster in AnfangsPosition bringen
	CRect rectClient;
	m_pSheet -> GetWindowRect (rectClient);
	m_pSheet -> SetWindowPos (NULL, 0, 0,
							  rectClient.Width(), rectClient.Height(),
							  SWP_NOZORDER | SWP_NOACTIVATE);
	return 0;
}

#ifdef _DEBUG
CAbfDoc* CAbfView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAbfDoc)));
	return (CAbfDoc*)m_pDocument;
}
#endif //_DEBUG
/*
void CAbfView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	return;
/*
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	try
	{
	//	Set prüfen
		ASSERT (m_pSet != NULL);
		ASSERT_VALID (m_pSet);
		CAbfSet *pSet = (CAbfSet *) m_pSet;
		ASSERT_VALID (pSet);

	//	Sheet prüfen
		ASSERT (m_pSheet != NULL);
		ASSERT_VALID (m_pSheet);
		CAbfSheet *pSheet = (CAbfSheet*) m_pSheet;
		ASSERT_VALID (pSheet);

	//	Formular erzeugen
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		CString strPage,
				strErstDat (m_pSet -> m_Erfassungsdatum.Format ((UINT) IDS_DATETIME_FORMAT)), 
			    strAendDat (m_pSet -> m_Aenderungsdatum.Format ((UINT) IDS_DATETIME_FORMAT));
		char *pPage = (char *) strPage.GetBuffer (AbfPrintBufferSize);
		strPage.Format (IDS_ABFALL_FORMULAR,pSet->m_Abfallnummer,pSheet->GetAbfallName(),
			pSheet->GetSonderAbfall(),pSheet->GetVorbehandlung(),pSheet->GetMengeT(),pSheet->GetMengeM(),
			pSet->m_Transporteurnummer,pSheet->GetTranspName(),pSheet->GetTranspStrasse(),pSheet->GetTranspOrt(),
			pSheet->GetTranspPlz(),pSet->m_Entsorgernummer,pSheet->GetEntsName(),pSheet->GetEntsStrasse(),
			pSheet->GetEntsOrt(),pSheet->GetEntsPlz(),pSheet->GetEntsArt(),pSheet->GetVerwertung(),
			pSet->m_EVN_Nummer,strErstDat,strAendDat,pApp->UserName());

		CDaoRecordViewExt :: Print (pDC, pInfo, strPage);
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}
*/
// virtuelles Suchen der zugeh. Abfallarten
BOOL CAbfView::SearchNummer (const char *pNummer, BOOL bOutErrMsg /*=TRUE*/)
{
	if (! HasRecords ())
		return TRUE;

	BOOL retval;
	if (retval = m_pSet -> SearchNummer(pNummer, bOutErrMsg))
	{
		//	Show results of seek operation
			UpdateData (FALSE);

		//	Überschrift akt.
			SetCaption ();

		//	Scroll-Status setzen
			SetScrollValues ();
	}

	//	akt. Satz sperren 
	return retval;
}


/*
void CAbfView::OnActivateView(BOOL bActivate, CView* pActView, CView* pDeactView) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (bActivate && g_pErzSet && !((CGakApp *) AfxGetApp ()) -> m_bResDlg &&
	   (m_pSet -> m_Nummer != g_pErzSet -> m_Nummer) && IsWindowVisible () && !m_bOnSearch)
	{
		CBoolSema Sema(m_bOnSearch);
		SearchNummer (g_pErzSet -> m_Nummer, TRUE);
	}
	CDaoRecordViewExt::OnActivateView(bActivate, pActView, pDeactView);
}
*/

BOOL CAbfView::CanGotoBookmark (void)
{
	return (HasRecords () && !m_strBookmark.IsEmpty ());
}

void CAbfView::OnUpdateGotoBookmark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanGotoBookmark ());				
}

void CAbfView::OnSetBookmark() 
{
	// TODO: Add your command handler code here
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());

	try
	{
		if (CanSetBookmark ())
			m_strBookmark = m_pSet -> m_Nummer;
		return;
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	m_strBookmark.Empty ();
}

void CAbfView::OnGotoBookmark() 
{
//	TODO: Add your command handler code here
//	Operation ausführbar ?
	if (CanGotoBookmark ())
		SearchNummer (m_strBookmark);
	else
#pragma message("JG")
		m_strBookmark.Empty();
}

void CAbfView::OnNewRekord() 
{
// JG hinzufügen eines neuen Rcords disablen
	return;

//	TODO: Add your command handler code here
	if (!CanAddNewRecord ())
		return;

//	prüfe interne Parameter
	ASSERT ((m_pSet != NULL) && m_pSet -> IsOpen ());

	try
	{
//		CBoolSema Sema(m_bOnSearch);
		BOOL bAddToList = FALSE;
		CString strNummer;

		if (g_pErzSet && !g_pErzSet -> m_Nummer.IsEmpty ())
			strNummer = g_pErzSet -> m_Nummer;
		else
		{
		//	neue Erzeugernummer durch Nutzer eingeben
			CChangeNummerDlg Dlg (m_pSet -> m_pDatabase, NULL, this, TRUE);
			if (Dlg.DoModal () != IDOK || Dlg.m_strNummer.IsEmpty ())
				return;
			strNummer = Dlg.m_strNummer;
		}

	//	zur Liste dazu nehmen ?
		bAddToList = strNummer == m_pSet -> m_Nummer;

		if (bAddToList)
		{			
		//	akt. Satz nur speichern
			if (!m_pSet -> CDaoRecordsetExt::LockReckord (Store, this))
				return;
		}
		else
		{
		//	alle Sätze der Abfallgruppe speichern und entriegeln
			if (!m_pSet -> LockReckord (FALSE, this))
				return;
		}

	//	Set öffnen
		CAbfArtSet Set (m_pSet -> m_pDatabase, ((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL());
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	//	neue Abfallart vom Nutzer eingeben
		CSelNumberDlg ArtDlg (this, &Set, ((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL(), IDS_ABFART_CAPTION);
		if (ArtDlg.DoModal () != IDOK || ArtDlg.m_strNumber.IsEmpty ())
			return;

	//	Set schließen
		if (Set.IsOpen ())
			Set.Close ();

	//	Datensatz für 'AddNew' vorbereiten

		CWaitCursor wc;
		if (!m_pSet -> PrepareAddNew (strNummer, SetAbfallArt, 
								     (LPARAM) (const char *) ArtDlg.m_strNumber))
			return;

		// JG nach neuanlegen den RS auffrischen
		SearchNummer();

		if (bAddToList)
			m_pSet -> SetBookmark (m_pSet->GetLastModifiedBookmark ());
		else
		{
			SetBookMarks ();			// alle Buchmarken setzen
		
		//	Scroll-Status neu setzen	// da Satz dazugekommen
			SetScrollValues ();	
		}

	//	Datensätze in Liste akt.
		CAbfSet *pSet = (CAbfSet *) m_pSet;
		if (!bAddToList)
			pSet->m_RecordInfoList.RemoveAll ();		// alte Liste löschen
		VERIFY (pSet->m_RecordInfoList.AddRecord (pSet->GetLastModifiedBookmark (), 
												  ArtDlg.m_strNumber, TRUE));

	//	Show results of add new operation
		UpdateData (FALSE);

	//	Überschrift akt.
		SetCaption ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CAbfView::OnUpdateNewRekord(CCmdUI* pCmdUI) 
{
	// JG anlegen über toolbar disablen
	pCmdUI -> Enable(false);

	// TODO: Add your command update UI handler code here
//	pCmdUI -> Enable (CanAddNewRecord () && m_pSheet &&
//					 (m_pSheet -> GetActiveIndex () == 0));			
}

//	AbfallGruppe löschen
void CAbfView::OnDeleteAbfallGruppe ()
{
	CString strDelText;
	AfxFormatString1 (strDelText, IDS_DELETE_ABFGR, 
					((CDaoRecordsetExt *) OnGetRecordset())->m_Nummer);
	if (IDYES == MessageBox (strDelText, AfxGetAppName(), MB_ICONQUESTION | MB_YESNO))
	{
		((CAbfSet *) OnGetRecordset ()) -> m_bDeleteAll = TRUE;		// alle Sätze der Liste löschen
//		CBoolSema Sema(m_bOnSearch);
		CDaoRecordViewExt::OnDeleteRekord(); 
	}
}

void CAbfView::DeleteAbfallGruppe()
{
	OnDeleteAbfallGruppe ();
}	

// Erzeugernummern aller Abfälle ändern
BOOL CAbfView::ChangeKey (BOOL bSelect /*FALSE*/)		
{
	return CDaoRecordViewExt::ChangeKey (TRUE);
}

void CAbfView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	Print (FALSE);	
}

void CAbfView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	Print (TRUE);	
}
/*
//	durchgereichte Daten beim Drucken            
//	CDruckInfo -----------------------------------------------------------
class  CDruckInfo 
{   
public:          
	int m_iTopTable;				//	y-Koordinate für Tabellenüberschrift
	int m_iOldRow;					//	alten Positionen im GRID
	int m_iOldCol;
	int m_iY;	                    //	x,y
	int m_iTextHoehe;				// 	Zeichenhoehe
	int m_iPrintPage;				//	Seitenummer
	int m_iPrintedPages;			//	max. Seitenzahl
	int m_iBilanzPage;              //	Bilanzseite
	int m_iYOffset;					//	Y-Koordinaten weiter auseinander
	int m_DruckPos[MaxTableEntries+iBilanzPageCnt]; //	Vektor speichert Druckpositionen der Spalten
	double m_dTableHeadFaktor;		//	Tabellenkopf-Faktor
	
	BOOL m_bOutput;					//	Ausgabeflag
	CString m_strBilanzNumber;		//	Bilanznummer (aus Erzeugerset)
	CDC *m_pDC;
	
	CDruckInfo (CDC *pDC);
	void CheckTableFaktor (const char *pText, int iWidth);
};                 

CDruckInfo :: CDruckInfo (CDC *pDC)
{                           
	m_dTableHeadFaktor = 1.0;
	m_iOldRow = m_iOldCol = 1;
	m_bOutput = FALSE;						//	nichts ausgeben
	m_iTopTable = m_iY = m_iTextHoehe = -1;		//	nicht init.
	m_iPrintPage = m_iBilanzPage = 1;
	m_iYOffset = m_iPrintedPages = 0;
	m_strBilanzNumber = "";
	ASSERT (NULL != pDC);
	m_pDC = pDC;  
	memset (m_DruckPos, 0, sizeof (m_DruckPos));
}                                   

void CDruckInfo :: CheckTableFaktor (const char *pText, int iWidth)
{                    
//	prüfe Parameter
	ASSERT (NULL != pText && AfxIsValidString (pText));
	ASSERT (iWidth > 0);   
	ASSERT (NULL != m_pDC);
	ASSERT (m_iTextHoehe > 0);
	
	CDruck Druck (m_pDC, m_iYOffset);
	VERIFY (NULL != Druck.ChangeFont ((int)(m_iTextHoehe*m_dTableHeadFaktor)));				
	           
	CSize szExt (m_pDC -> GetTextExtent (pText, strlen (pText)));
	while ((szExt.cx >= iWidth) && (m_dTableHeadFaktor > 0))
	{                          
		m_dTableHeadFaktor -= 0.05;		//	Zeichensatz in 0.05 Schritten kleiner
		VERIFY (NULL != Druck.ChangeFont ((int)(m_iTextHoehe*m_dTableHeadFaktor)));								
		szExt = m_pDC -> GetTextExtent (pText, strlen (pText));		
	}
}
                           
void CAbfView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable (m_pGrid && (m_pGrid -> GetNumProperty ("Rows") > iMinRowCnt));	
}

void CAbfView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable (m_pGrid && (m_pGrid -> GetNumProperty ("Rows") > iMinRowCnt));	
}

BOOL CAbfView::OnPreparePrinting(CPrintInfo* pInfo)
{
//	Prüfe Parameter
	ASSERT (pInfo != NULL);

// 	pInfo -> m_pPD -> m_pd.Flags |= PD_NOPAGENUMS;	//	keine Bereichsauswahl

	if (pInfo -> m_bPreview)				// bei Preview Operation
		pInfo -> m_nNumPreviewPages = 2;	// 2 Seiten bei Vorschau

	//if (!UpdateData (TRUE))
	//	return FALSE;						// lese Werte der akt. Page
	
	return DoPreparePrinting(pInfo);
}

void CAbfView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
//	aktuelle Texthöhe speichern
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);          
	ASSERT (NULL != m_pGrid);

	TEXTMETRIC tm;
	memset (&tm, 0, sizeof (tm));
	if (! pDC -> GetTextMetrics (&tm))
	{
		CGak16App *pApp = (CGak16App *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		pApp -> OutputMessage (IDS_CANNOT_PRINT);
	}
	
//	DruckInfo-Objekt erzeugen
	CDruckInfo *pDruckInfo = new CDruckInfo (pDC);	
	pDruckInfo -> m_iTextHoehe = tm.tmHeight;
	
//	Prepare-Fenster
	CPrepDruck *pPrepareDruck = new CPrepDruck (this);		
	VERIFY (pPrepareDruck -> Create (IDD_PREPARE_DRUCK, this));
	pPrepareDruck -> ShowWindow (SW_NORMAL);	
	
//	alten Grid-Positionen merken
	pDruckInfo -> m_iOldCol = (int)m_pGrid->GetNumProperty("Col");
	pDruckInfo -> m_iOldRow = (int)m_pGrid->GetNumProperty("Row");	
	m_bEventLockout = TRUE;	
	
//	Bilanznummer besorgen                                       
	CBilanzSet Set (((CGak16App *)AfxGetApp ()) -> GetDatabase ());
	ASSERT (!m_pSet -> m_NummerParam.IsEmpty ());
	AfxFormatString1 (Set.m_strFilter, IDS_WHER_NUMBER_FILTER, m_pSet -> m_NummerParam);
	Set.Open (CRecordset::forwardOnly,((CGak16App *)AfxGetApp ()) -> ErzeugerDefaultSQL (),
			  CRecordset::readOnly);
	if (!Set.IsEOF ())
		pDruckInfo -> m_strBilanzNumber = Set.m_Bilanznummer;		
	
//	Bereich über GetDiveceCaps lesen
	pInfo->m_rectDraw.SetRect(0, 0, pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES)); 
	
//	Koordinaten konvertieren
	pDC -> DPtoLP (pInfo -> m_rectDraw);
	
//	Y-Offset
	pDruckInfo->m_iYOffset = int(pDruckInfo->m_iTextHoehe/dYOffsetA);	//	Y-Koordinaten weiter auseinander 	
  	
//	CDruckInfo speichern
	ASSERT (NULL != pInfo);
	pInfo -> m_lpUserData = pDruckInfo;
	
//	alles dummy-Drucken und ggf. max. Seitenanzahl neu setzen
	OnPrint (pDC, pInfo);                                                    
	
	if (0 == pDruckInfo -> m_iPrintedPages)
		pInfo -> m_pPD -> m_pd.Flags |= PD_NOPAGENUMS;	//	keine Bereichsauswahl		
	{ 
		pInfo -> SetMinPage (1);
		pInfo -> SetMaxPage (pDruckInfo -> m_iPrintedPages);	
	}		
	
	pDruckInfo -> m_bOutput = TRUE;						//	jetzt alles ausgeben	
	pPrepareDruck -> DestroyWindow ();
}                                                          

void CAbfView::OnEndPrinting(CDC*, CPrintInfo* pInfo)
{
	ASSERT (NULL != pInfo);
	
	CDruckInfo *pDruckInfo = NULL;
	if (pInfo -> m_lpUserData)   
	{
		pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
		
	//	alten Grid-Positionen wieder einnehmen
		ASSERT (NULL != m_pGrid);
		m_pGrid->SetNumProperty("Col", pDruckInfo -> m_iOldCol);
		m_pGrid->SetNumProperty("Row", pDruckInfo -> m_iOldRow);
		m_bEventLockout = FALSE;	
	}		
	DELETE_OBJ (pDruckInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGak16View printing                                      
void CAbfView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
//	TODO: Add your specialized code here and/or call the base class
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	TRY
	{              
	//	Drucken erfolgt aus dem GRID: prüfe dortige Anzahl Datensätze
    	ASSERT (NULL != m_pGrid);                                    
    	int iRows = (int)m_pGrid -> GetNumProperty ("Rows") - 2;
    	if (iRows <= 0)
    		return;
    		    
		CWaitCursor wc;    		    
	//	lese CDruckInfos
		CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
		ASSERT (NULL != pDruckInfo);
		pDruckInfo->m_pDC = pDC;
		
	//	Zeichenbereich verkleinern
		pInfo -> m_rectDraw.left += iRandXY;
		pInfo -> m_rectDraw.right -= iRandXY;
		pInfo -> m_rectDraw.top += iRandXY;
		pInfo -> m_rectDraw.bottom -= iRandXY;
			
	//	akt. Zeichenposition speichern  
		pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;				
		
	//	speichere Druckpositionen der Spalten
		int iExtent = pInfo -> m_rectDraw.right - pInfo -> m_rectDraw.left;
		
	//	für Bilanzseite 1		
		for (int iPos = 0; iPos < iBilanzPageOne; iPos++)
		{   
			if (0 == iPos)
				pDruckInfo->m_DruckPos[iPos] = pInfo -> m_rectDraw.left;
			else                                                              
			{
				pDruckInfo->m_DruckPos[iPos] = MulDiv (ColumnInfoField[iPos-1].iDruckWidth, iExtent, 100) +
											   pDruckInfo->m_DruckPos[iPos-1];
											   
			//	prüfe Breite an Hand max. Textlänge
				pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-1].szMaxDruckText, 
												pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
			}											   
		}	                                   
		pDruckInfo->m_DruckPos[iPos] = pInfo -> m_rectDraw.right;//	iPos steht auf BlianzPageOne
		
	//	prüfe Breite an Hand max. Textlänge
		pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-1].szMaxDruckText, 
										pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
		
	//	für Bilanzseite 2        
		iPos++;
		pDruckInfo->m_DruckPos[iPos++] = pDruckInfo->m_DruckPos[0];				
		pDruckInfo->m_DruckPos[iPos++] = pDruckInfo->m_DruckPos[1];						
		
		int iMax = iBilanzPageOne+iBilanzPageTwo+2;
		for (;iPos < iMax-1; iPos++)
		{
			pDruckInfo->m_DruckPos[iPos] = MulDiv (ColumnInfoField[iPos-3].iDruckWidth, iExtent, 100) +
											   	   pDruckInfo->m_DruckPos[iPos-1];
		//	prüfe Breite an Hand max. Textlänge
			pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-3].szMaxDruckText, 
											pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
		}											   	   
		pDruckInfo->m_DruckPos[iMax-1] = pInfo -> m_rectDraw.right;
		
	//	prüfe Breite an Hand max. Textlänge:: iPos steht auf iMax - 1
		pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-3].szMaxDruckText, 
										pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);				
		
	//	Seite 3 keine Prüfung mehr auf min. Textbreite		    
	//	für Bilanzseite 3       
		iPos = iMax;
		pDruckInfo->m_DruckPos [iPos++] = pInfo -> m_rectDraw.left;				    
		pDruckInfo->m_DruckPos [iPos++] = pDruckInfo->m_DruckPos [1];				    
		pDruckInfo->m_DruckPos [iPos++] = int(1.3*pDruckInfo->m_DruckPos [2]);	//	zweite Feld etwas breiter			    
		pDruckInfo->m_DruckPos [iPos++] = pInfo -> m_rectDraw.right;				    				    
		
	//	Drucken der Angaben                  
	//	immer zuerst Modus bestimmen
		BOOL bOutput = pDruckInfo->m_bOutput;
		pDruckInfo->m_bOutput = FALSE;			//	diesen Modus nur aktiveren,
												//	wenn akt. Seite gedruckt werden soll	
		pDruckInfo -> m_iPrintPage = 0;			//	Anzahl Seiten berechnen/bzw. akt. Seite setzen
		CString strText;                        //	Hilfstext  
		
	//	für alle Bilanzseiten
		for (pDruckInfo->m_iBilanzPage = 1; pDruckInfo -> m_iBilanzPage<=iBilanzPageCnt; pDruckInfo->m_iBilanzPage++)
		{   
		//	prüfe, ob für Bilanzseite 3 Wert zu erwarten sind				
			if (3 == pDruckInfo->m_iBilanzPage)
			{        
				BOOL bHasVal = FALSE;		//	Standard sind keine Begründungen
					
			//	Spalte bleibt immer gleich
				m_pGrid -> SetNumProperty ("Col", iVerfahrenBegrCol);					
				for (int i = 1; !bHasVal && (i <= iRows); i++)
				{               
					m_pGrid -> SetNumProperty ("Row", i);					
					strText = m_pGrid -> GetStrProperty("Text");
					bHasVal = ((!strText.IsEmpty()) && (!(strText == EmptyMemo)));
				}
					        
			//	wenn keine Werte zu erwarten sind, alles beenden					        
				if (!bHasVal)
					break;																			
			}	
		
		//	aktuelle Zeichenposition ist am Anfang der Seite immer ganz oben
			pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;				
			
		//	Seitenzähler zunächst erhöhen				
			pDruckInfo -> m_iPrintPage++;			
			
		//	Ausgabeflag setzen        
			if (pDruckInfo->m_bOutput)	//	dieses Flag ist nur einmal für die Ausgabe der akt.
				return;					//	Seite gesetzt worden
			pDruckInfo -> m_bOutput = (bOutput && (pDruckInfo->m_iPrintPage == (int)pInfo->m_nCurPage)); 			
			
		//	Seitenkopf
			PrintPageHead (pInfo);
	                        
		//	Tabellenkopf
			PrintTableHead (pInfo);	
			    
		//	alle Zeilen der aktuellen Bilanzseite ausgeben			    
			for (int iGridIndex = 1; iGridIndex <= iRows; iGridIndex++)
			{                    
			//	bei Bilanzseite 3 extra Test auf gültigen Inhalt
				if (3 == pDruckInfo->m_iBilanzPage)
				{
					m_pGrid -> SetNumProperty ("Row", iGridIndex);																		
					m_pGrid -> SetNumProperty ("Col", iVerfahrenBegrCol);							
					strText = m_pGrid -> GetStrProperty("Text");
					if (strText.IsEmpty () || (strText == EmptyMemo))
						continue;		//	weiter mit der nächsten Zeile
				}
				
			//	wenn nicht genügend Platz für aktuelle Seite
				if (!PrintRow (iGridIndex, pInfo, pDruckInfo->m_bOutput))	
				{                                   
				//	Spaltenlinien drucken
					if (pDruckInfo -> m_bOutput)
						PrintTableLines (pInfo);
				
				//	Seitenzähler erhöhen
					pDruckInfo -> m_iPrintPage++;						
				
				//	Ausgabeflag setzen					        
					if (pDruckInfo->m_bOutput)	//	dieses Flag ist nur einmal für die Ausgabe der akt.
						return;					//	Seite gesetzt worden
					pDruckInfo -> m_bOutput = (bOutput && (pDruckInfo->m_iPrintPage == (int)pInfo->m_nCurPage));					
						
				//	Zeichenposition akt.						
					pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;										
					
				//	Seitenkopf
					PrintPageHead (pInfo);
	
				//	Tabellenkopf
					PrintTableHead (pInfo);
					                                                            
				//	jetzt die aktuelle Zeile noch einmal ausgeben					                                                            
					PrintRow (iGridIndex, pInfo, pDruckInfo->m_bOutput);		
				}					
			}	//	end_for:	alle Zeilen
			
		//	Spaltenlinien drucken
			if (pDruckInfo -> m_bOutput)
				PrintTableLines (pInfo);									    		
		}		//	end_for:	alle Bilanzseiten		
		
	//	ggf. max. Seitenzahl speichern			
		if (!bOutput)
			pDruckInfo -> m_iPrintedPages = pDruckInfo->m_iPrintPage;				
	}		
	CATCH (CResourceException, re)
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_CANNOT_PRINT);
	}		
	AND_CATCH (CUserException, re)
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_CANNOT_PRINT);
	}
	AND_CATCH (CMemoryException, me)      
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_NO_MEMORY);
	}   
	AND_CATCH (CDBException, db)
	{                           
		((CGak16App *) AfxGetApp ()) -> OutputMessage (db -> m_strError);
	}                
	AND_CATCH (CFileException, fe)
	{
		((CGak16App *) AfxGetApp ()) -> OutputFileError (fe -> m_cause);
	}
	END_CATCH	
}	
		                   
//	drucke Seitenkopf		                   
void CAbfView::PrintPageHead (CPrintInfo *pInfo)
{
	ASSERT (NULL != pInfo);

//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	ASSERT (NULL != pDruckInfo->m_pDC);
	
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);		
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dKopfFaktor18A), FW_BOLD));
	
	int iX = pInfo -> m_rectDraw.left + iRandXY;
	int iY = pDruckInfo -> m_iY + (pDruckInfo -> m_iTextHoehe / 2);

//	Texte ausgeben	
	CString strOut ("Betriebliche Abfallbilanz");
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength (), pDruckInfo->m_bOutput));
	
//	Zusatzfeld entsprechend Bilanz-Page ausgeben
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dKopfFaktor15A)));	
	strOut = "Abfalldatenerfassung - Seite ";
	switch (pDruckInfo -> m_iBilanzPage)    
	{
		case 1:
			strOut += "1";
		break;
		case 2:            
			strOut += "2";
		break;
		case 3:
			strOut = "Maßnahmen und Begründungen";
		break;
		default:
			ASSERT (FALSE);
	}
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength (), pDruckInfo->m_bOutput));
	
//	jetzt Bilanznummer			
	strOut = "Bilanz-Nr.: ";	
	VERIFY (Druck.ChangeFont (int(pDruckInfo->m_iTextHoehe*dInfoFaktor13A), FW_MEDIUM));			
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));
	int iLeft = iX;  //	Umrandungsposition speichern	        
	strOut = " " + pDruckInfo->m_strBilanzNumber + " ";
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, BilanzNummerLaenge+2, pDruckInfo->m_bOutput));	
	int iRight = iX; //	Umrandungsposition speichern	
	iX = pInfo -> m_rectDraw.right - iRandXY;							   
	char Buffer20 [20] = "";
	wsprintf (Buffer20, "Blatt-Nr.: %d/%d", pInfo->m_nCurPage, pDruckInfo->m_iPrintedPages);
	VERIFY (Druck.TextOut (iX, iY, Buffer20, TRUE, FALSE, strlen(Buffer20), pDruckInfo->m_bOutput));									   
	CSize szExt (Druck.GetTextExtent (Buffer20, 1));
	
//	BilanzNr. ggf. umranden
	if (pDruckInfo->m_bOutput) 
	{
		int iYOffset = (pDruckInfo->m_iTextHoehe / 5);
		Druck.DrawRectangle (iLeft, iY - iYOffset, iRight, iY + szExt.cy + iYOffset);			
	}		
	iY += szExt.cy + pDruckInfo->m_iYOffset;
	                                       
//	jetzt alles Einrahmen
	if (pDruckInfo->m_bOutput)
		Druck.DrawRectangle (pInfo->m_rectDraw.left, pDruckInfo -> m_iY, pInfo->m_rectDraw.right, iY);		                                       
		
//	zuletzt akt. Zeichenposition akt.	
	pDruckInfo -> m_iY = iY + pDruckInfo -> m_iTextHoehe;		                                                                                               
}    

//	drucke Tabellenkopf von Bilanzseite 1/2/3
void CAbfView::PrintTableHead (CPrintInfo *pInfo)
{
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	
//	Punkt 3 ist im Kopf für die Bilanzseiten 1 und 2 gleich
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);		
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dInfoFaktor13A), FW_MEDIUM));			
	
//	Zeichenpositionen lesen	
	int iX = pInfo -> m_rectDraw.left;
	int iY = pDruckInfo -> m_iY;
	                       
//	Punkt 3/4 ausgeben	                               
	CString strOut = (3 == pDruckInfo -> m_iBilanzPage) ? " 4 " : " 3 ";	
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));	
	CSize szExt (Druck.GetTextExtent (strOut, strOut.GetLength ()));
	
//	ggf. Punkt 3/4 umranden	
	if (pDruckInfo->m_bOutput)                                
		Druck.DrawRectangle (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY, 
							 iX, pDruckInfo -> m_iY + szExt.cy);		
	
	iY += int(pDruckInfo -> m_iTextHoehe / 2);
	if (3 == pDruckInfo -> m_iBilanzPage)
		strOut = "Begründung der Notwendigkeit zur Abfallbeseitigung, insbesondere Angaben zur";
	else
		strOut = "Übersicht zu Art, Menge und Verbleib der entsorgten Abfälle";
	iX += (3*iRandXY);				
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));										 						 
	
	if (3 == pDruckInfo -> m_iBilanzPage)
	{   
		iY -= int(pDruckInfo->m_iYOffset / 2);
		strOut = "mangelnden Verwertbarkeit";		
		VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));										 							
	}		

//	Rahmen für Punkt 3/4
	if (pDruckInfo->m_bOutput)
	{                                
		Druck.DrawRectangle (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY, 
							 pInfo -> m_rectDraw.right, iY);

	//	Tabellenspitzenkoordinate Y merken
		pDruckInfo->m_iTopTable = iY;									 
	}							 

//	Tabellenköpfe ausgeben: Zuerst Nummern
	iY += int(pDruckInfo -> m_iTextHoehe / 2);
	
//	jetzt ggf. Nummern ausgeben
	if (pDruckInfo->m_bOutput)
	{                                    
		if (1 == pDruckInfo -> m_iBilanzPage)
		{
			for (int iPos = 0; iPos < iBilanzPageOne; iPos++)
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos],
										 	 pDruckInfo -> m_DruckPos[iPos+1], iY,
										 	 ColumnInfoField[iPos].pDruckNumber));
		}	
		else
		{                                    
			if (2 == pDruckInfo -> m_iBilanzPage)
			{
				for (int iPos = iBilanzPageOne; iPos < iBilanzPageOne+iBilanzPageTwo-1; iPos++)
					VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos+2],
										 	 	 pDruckInfo -> m_DruckPos[iPos+3], iY,
										 	 	 ColumnInfoField[iPos].pDruckNumber));
			}										 	 	 	
			else
			{   
				int iPos = iBilanzPageOne+iBilanzPageTwo+2;
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.1"));								
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[++iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.2"));			
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[++iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.3"));
			}
		}	
	}										 	
		
	iY += szExt.cy + int(pDruckInfo -> m_iTextHoehe / 2);
	
//	Zeilenende ausgeben		
	if (pDruckInfo->m_bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo -> m_rectDraw.left, iY);							
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, iY));					
	}
						
//	jetzt Tabellenüberschriften
//	zuerst anderen Zeichensatz
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*
										    pDruckInfo->m_dTableHeadFaktor)));			
	szExt = Druck.GetTextExtent (" ", 1);		

//	zuerst die max. Y-Koordinate ermitteln
	int iSpace = int(szExt.cy / iSpaceVal);	//	Zwischenraum für x/y-Werte
	iY += iSpace;							//	diesen Platz zum vorigen Abschnitt
	           
	int iFirstRow = 0;
	int iMaxRow = 0;	           
	if (3 == pDruckInfo -> m_iBilanzPage) 		
	{
		iFirstRow = iBilanzPageOne+iBilanzPageTwo;
		iMaxRow = MaxTableEntries;
	}   
	else
	{   
		iFirstRow = 0;
		iMaxRow = iBilanzPageOne+iBilanzPageTwo;
	}
	
//	Clippingrechteck	    
	CRect rc (0, iY, 0, iY+szExt.cy);	    
	int iMaxY = 0;
	for (int i = iFirstRow; i < iMaxRow; i++)
	{   
		if (i < iBilanzPageOne)
		{
			rc.right = pDruckInfo->m_DruckPos[i+1];
			rc.left = pDruckInfo->m_DruckPos [i];	
		}			
		else   
		{
			if (i < (iBilanzPageOne+iBilanzPageTwo))
			{
				rc.right = pDruckInfo->m_DruckPos[i+2];
				rc.left = pDruckInfo->m_DruckPos[i+1];				
			}				
			else
			{
				rc.right = pDruckInfo->m_DruckPos[i+3];
				rc.left = pDruckInfo->m_DruckPos[i+2];					
			}				
		}   
		ASSERT (rc.Width () > 0);						
        
	//	y-Koordinate berechnen        
		rc.left += iSpace;
		rc.right -= iSpace;
		iMaxY = max (iMaxY, pDruckInfo->m_pDC->DrawText(TableCaptions[i].pCaption,-1,rc,DT_CALCRECT | uiTableFormat));
	}
	    
//	y-Koordinate  vergrößern	    
	iY += iMaxY;
		    
//	jetzt ggf. Überschriften ausgeben
	if (pDruckInfo->m_bOutput)
	{       
		rc.bottom = iY;
		
	//	FirstRow/MaxRow neu setzen
		if (1 == pDruckInfo->m_iBilanzPage)
		{
			iFirstRow = 0;
			iMaxRow = iBilanzPageOne;
		}		
		else
		{   
			if (2 == pDruckInfo->m_iBilanzPage)
			{
				iFirstRow = iBilanzPageOne;
				iMaxRow = iFirstRow + iBilanzPageTwo;
			}
			else
			{			
				iFirstRow = iBilanzPageOne + iBilanzPageTwo;
				iMaxRow = iFirstRow + iBilanzPageThree;
			}			
		}
		
		for (i = iFirstRow; i < iMaxRow; i++)
		{   
			if (i < iBilanzPageOne)
			{
				rc.right = pDruckInfo->m_DruckPos[i+1];
				rc.left = pDruckInfo->m_DruckPos [i];	
			}			
			else   
			{
				if (i < (iBilanzPageOne+iBilanzPageTwo))
				{
					rc.right = pDruckInfo->m_DruckPos[i+2];
					rc.left = pDruckInfo->m_DruckPos[i+1];				
				}				
				else
				{
					rc.right = pDruckInfo->m_DruckPos[i+3];
					rc.left = pDruckInfo->m_DruckPos[i+2];					
				}				
			}   
			ASSERT (rc.Width () > 0);						
        
		//	Text ausgeben
			rc.left += iSpace;
			rc.right -= iSpace;
			pDruckInfo->m_pDC->DrawText(TableCaptions[i].pCaption,-1,rc,uiTableFormat);
		}		
	}	
		
//	Zeilenende ausgeben 	
	iY += iSpace;	//	Zwischenraum zum vorigen Abschnitt	
	if (pDruckInfo -> m_bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo->m_rectDraw.left, iY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, iY));								
	}
	                            
//	Zeichenposition speichern	                            
	pDruckInfo -> m_iY = iY;	
}    

//	aktuelle Zeile berechnen bzw. ausgeben
//	BOOL, wenn Platz nicht mehr ausreicht
BOOL CAbfView :: PrintRow (int iGridIndex, CPrintInfo *pInfo, BOOL bOutput)	
{   
	ASSERT (iGridIndex > 0);
	ASSERT (NULL != m_pGrid);	
	ASSERT (iGridIndex < ((int)m_pGrid -> GetNumProperty ("Rows") - 1));
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);         
	ASSERT (NULL != pDruckInfo->m_pDC);
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo -> m_iYOffset);		
	VERIFY (Druck.ChangeFont (int(pDruckInfo -> m_iTextHoehe*pDruckInfo->m_dTableHeadFaktor),
							  FW_NORMAL, FaceName, 1));	//	kursiv

//	bestimme max. Y-Koordinate
	int iFirstRow = 0;
	int iMaxRow = 0;	           
	if (3 == pDruckInfo -> m_iBilanzPage) 		
	{
		iFirstRow = iBilanzPageOne+iBilanzPageTwo;
		iMaxRow = MaxTableEntries;
	}   
	else
	{   
	//	beide Bilanzseiten prüfen
		iFirstRow = 0;
		iMaxRow = iBilanzPageOne+iBilanzPageTwo;
	}	
	
//	lese akt. Zeichenposition
	int iY = pDruckInfo -> m_iY;
	CSize szExt (pDruckInfo->m_pDC->GetTextExtent (" ", 1));	
	int iSpace = szExt.cy / iSpaceVal;	//	Zwischenraum für x/y-Koordinaten
	iY += iSpace;
	
//	Clippingrechteck	    
	CRect rc (0, iY, 0, iY+szExt.cy);		
	
//	weitere Werte init.	
	int iMaxY = 0;         
	CString strText;
	
//	Zeile in GRID setzen
	m_pGrid -> SetNumProperty ("Row", iGridIndex);
	int iGridCol = 0;		
	for (int i = iFirstRow; i < iMaxRow; i++)
	{   
		if (i < iBilanzPageOne)
		{
			rc.right = pDruckInfo->m_DruckPos[i+1];
			rc.left = pDruckInfo->m_DruckPos [i];	
		}			
		else   
		{
			if (i < (iBilanzPageOne+iBilanzPageTwo))
			{
				rc.right = pDruckInfo->m_DruckPos[i+2];
				rc.left = pDruckInfo->m_DruckPos[i+1];				
			}				
			else
			{
				rc.right = pDruckInfo->m_DruckPos[i+3];
				rc.left = pDruckInfo->m_DruckPos[i+2];					
			}				
		}   
		ASSERT (rc.Width () > 0);						
        
	//	y-Koordinate berechnen        
		rc.left += iSpace;
		rc.right -= iSpace;         
		
	//	lese akt. Text aus GRID		
		m_pGrid -> SetNumProperty ("Col", TableCaptions[i].iGridCol);			
		strText = m_pGrid -> GetStrProperty("Text");
			
		iMaxY = max (iMaxY, Druck.DrawText(strText,strText.GetLength(),rc,
										   DT_CALCRECT|TableCaptions[i].iCenterMode));
	}               
	iY += (iMaxY + iSpace);
	
//	Kann diese Seite gedruckt werden ?
	if (iY > pInfo -> m_rectDraw.bottom)
		return FALSE;				//	dann zurück
	
//	Seite ggf. ausgeben	
	if (bOutput)
	{	
	//	Zeile ausgeben
		rc.bottom = iY - iSpace;	//	Zwischenraum wieder abziehen
		
	//	akt. Zeile/Spalte bestimmen		
		if (3 == pDruckInfo -> m_iBilanzPage) 		
		{
			iFirstRow = iBilanzPageOne+iBilanzPageTwo;
			iMaxRow = MaxTableEntries;
		}   
		else
		{   
			if (1 == pDruckInfo -> m_iBilanzPage) 		
			{
				iFirstRow = 0;
				iMaxRow = iBilanzPageOne;
			}
			else
			{   
				iFirstRow = iBilanzPageOne;
				iMaxRow = iFirstRow+iBilanzPageTwo;
			}
		}			
		
	//	alle Spalten ausgeben		
		for (int j = iFirstRow; j < iMaxRow; j++)
		{   
			if (j < iBilanzPageOne)
			{
				rc.right = pDruckInfo->m_DruckPos[j+1];
				rc.left = pDruckInfo->m_DruckPos [j];	
			}			
			else   
			{
				if (j < (iBilanzPageOne+iBilanzPageTwo))
				{
					rc.right = pDruckInfo->m_DruckPos[j+2];
					rc.left = pDruckInfo->m_DruckPos[j+1];				
				}				
				else
				{
					rc.right = pDruckInfo->m_DruckPos[j+3];
					rc.left = pDruckInfo->m_DruckPos[j+2];					
				}				
			}   
			ASSERT (rc.Width () > 0);						
        
		//	y-Koordinate berechnen        
			rc.left += iSpace;
			rc.right -= iSpace;         
		
		//	lese akt. Text aus GRID		
			m_pGrid -> SetNumProperty ("Col", TableCaptions[j].iGridCol);			
			strText = m_pGrid -> GetStrProperty("Text");
        
		//	Text ausgeben        
			Druck.DrawText(strText,strText.GetLength(),rc,TableCaptions[j].iCenterMode);
		}			
	}	//	Ende der Ausgabe
	
//	akt. Zeichenposition immer weiterführen
	pDruckInfo -> m_iY += (iMaxY + (2*iSpace));
	
//	akt. Zeile unterstreichen
	if (bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, pDruckInfo -> m_iY));				
	}		

	return TRUE;
}
                                 
//	Tabellenlinien ausgeben                                 
void CAbfView::PrintTableLines (CPrintInfo *pInfo)
{   
//	prüfe Parameter			                           
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	ASSERT (NULL != pDruckInfo -> m_pDC);
	ASSERT_VALID (pDruckInfo -> m_pDC);			               
	    
//	prüfe Ausgabemodus	    
	if (!pDruckInfo -> m_bOutput)
		return;
		
//	prüfe Parameter
	ASSERT (pDruckInfo -> m_iTopTable >= 0);
	ASSERT (pDruckInfo -> m_iTopTable < pDruckInfo -> m_iY);	
	
//	max. Koordinate steht in pDruckInfo -> m_iY;
//	äußerer Tabellenrahmen: für alle Bilanzen gleich
	int iTopY = pDruckInfo -> m_iTopTable;
	int iBottomY = pDruckInfo -> m_iY;
	
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);				
	Druck.DrawRectangle (pInfo -> m_rectDraw.left, iTopY, 
						 pInfo -> m_rectDraw.right, iBottomY);					

//	alle Spaltenrahmen zeichnen
	int iFirst = 0;
	int iLast = 0;	
//	für Bilanzseite
	if (1 == pDruckInfo -> m_iBilanzPage)
	{
		iFirst = 1;
		iLast = iBilanzPageOne;
	}			
	else
	{
		if (2 == pDruckInfo -> m_iBilanzPage)
		{
			iFirst = iBilanzPageOne+2;			        
			iLast = iBilanzPageOne+iBilanzPageTwo+1;			        
		}
		else
		{
			iFirst = iBilanzPageOne+iBilanzPageTwo+2;
			iLast = sizeof (pDruckInfo->m_DruckPos) / sizeof (int);
		}				
	}	
			                           
//	Linien zeichnen	
	for (int iX = pDruckInfo -> m_DruckPos [iFirst]; iFirst < iLast; iFirst++, 
		     iX = pDruckInfo -> m_DruckPos [iFirst])
	{
		pDruckInfo -> m_pDC -> MoveTo (iX, iTopY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (iX, iBottomY));				
	}			
}
*/
void CAbfView::Print (BOOL bToWindow)
{
	try
	{
		CString strReport;
		VERIFY (strReport.LoadString (IDS_ABF_TABLE_NAME));
		CDaoRecordViewExt::Print (strReport, bToWindow);
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}
}
/*
//	durchgereichte Daten beim Drucken            
//	CDruckInfo -----------------------------------------------------------
class  CDruckInfo 
{   
public:          
	int m_iTopTable;				//	y-Koordinate für Tabellenüberschrift
	int m_iOldRow;					//	alten Positionen im GRID
	int m_iOldCol;
	int m_iY;	                    //	x,y
	int m_iTextHoehe;				// 	Zeichenhoehe
	int m_iPrintPage;				//	Seitenummer
	int m_iPrintedPages;			//	max. Seitenzahl
	int m_iBilanzPage;              //	Bilanzseite
	int m_iYOffset;					//	Y-Koordinaten weiter auseinander
	int m_DruckPos[MaxTableEntries+iBilanzPageCnt]; //	Vektor speichert Druckpositionen der Spalten
	double m_dTableHeadFaktor;		//	Tabellenkopf-Faktor
	
	BOOL m_bOutput;					//	Ausgabeflag
	CString m_strBilanzNumber;		//	Bilanznummer (aus Erzeugerset)
	CDC *m_pDC;
	
	CDruckInfo (CDC *pDC);
	void CheckTableFaktor (const char *pText, int iWidth);
};                 

CDruckInfo :: CDruckInfo (CDC *pDC)
{                           
	m_dTableHeadFaktor = 1.0;
	m_iOldRow = m_iOldCol = 1;
	m_bOutput = FALSE;						//	nichts ausgeben
	m_iTopTable = m_iY = m_iTextHoehe = -1;		//	nicht init.
	m_iPrintPage = m_iBilanzPage = 1;
	m_iYOffset = m_iPrintedPages = 0;
	m_strBilanzNumber = "";
	ASSERT (NULL != pDC);
	m_pDC = pDC;  
	memset (m_DruckPos, 0, sizeof (m_DruckPos));
}                                   

void CDruckInfo :: CheckTableFaktor (const char *pText, int iWidth)
{                    
//	prüfe Parameter
	ASSERT (NULL != pText && AfxIsValidString (pText));
	ASSERT (iWidth > 0);   
	ASSERT (NULL != m_pDC);
	ASSERT (m_iTextHoehe > 0);
	
	CDruck Druck (m_pDC, m_iYOffset);
	VERIFY (NULL != Druck.ChangeFont ((int)(m_iTextHoehe*m_dTableHeadFaktor)));				
	           
	CSize szExt (m_pDC -> GetTextExtent (pText, strlen (pText)));
	while ((szExt.cx >= iWidth) && (m_dTableHeadFaktor > 0))
	{                          
		m_dTableHeadFaktor -= 0.05;		//	Zeichensatz in 0.05 Schritten kleiner
		VERIFY (NULL != Druck.ChangeFont ((int)(m_iTextHoehe*m_dTableHeadFaktor)));								
		szExt = m_pDC -> GetTextExtent (pText, strlen (pText));		
	}
}
                           
void CAbfView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable (m_pGrid && (m_pGrid -> GetNumProperty ("Rows") > iMinRowCnt));	
}

void CAbfView::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable (m_pGrid && (m_pGrid -> GetNumProperty ("Rows") > iMinRowCnt));	
}

BOOL CAbfView::OnPreparePrinting(CPrintInfo* pInfo)
{
//	Prüfe Parameter
	ASSERT (pInfo != NULL);

// 	pInfo -> m_pPD -> m_pd.Flags |= PD_NOPAGENUMS;	//	keine Bereichsauswahl

	if (pInfo -> m_bPreview)				// bei Preview Operation
		pInfo -> m_nNumPreviewPages = 2;	// 2 Seiten bei Vorschau

	//if (!UpdateData (TRUE))
	//	return FALSE;						// lese Werte der akt. Page
	
	return DoPreparePrinting(pInfo);
}

void CAbfView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
//	aktuelle Texthöhe speichern
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);          
	ASSERT (NULL != m_pGrid);

	TEXTMETRIC tm;
	memset (&tm, 0, sizeof (tm));
	if (! pDC -> GetTextMetrics (&tm))
	{
		CGak16App *pApp = (CGak16App *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		pApp -> OutputMessage (IDS_CANNOT_PRINT);
	}
	
//	DruckInfo-Objekt erzeugen
	CDruckInfo *pDruckInfo = new CDruckInfo (pDC);	
	pDruckInfo -> m_iTextHoehe = tm.tmHeight;
	
//	Prepare-Fenster
	CPrepDruck *pPrepareDruck = new CPrepDruck (this);		
	VERIFY (pPrepareDruck -> Create (IDD_PREPARE_DRUCK, this));
	pPrepareDruck -> ShowWindow (SW_NORMAL);	
	
//	alten Grid-Positionen merken
	pDruckInfo -> m_iOldCol = (int)m_pGrid->GetNumProperty("Col");
	pDruckInfo -> m_iOldRow = (int)m_pGrid->GetNumProperty("Row");	
	m_bEventLockout = TRUE;	
	
//	Bilanznummer besorgen                                       
	CBilanzSet Set (((CGak16App *)AfxGetApp ()) -> GetDatabase ());
	ASSERT (!m_pSet -> m_NummerParam.IsEmpty ());
	AfxFormatString1 (Set.m_strFilter, IDS_WHER_NUMBER_FILTER, m_pSet -> m_NummerParam);
	Set.Open (CRecordset::forwardOnly,((CGak16App *)AfxGetApp ()) -> ErzeugerDefaultSQL (),
			  CRecordset::readOnly);
	if (!Set.IsEOF ())
		pDruckInfo -> m_strBilanzNumber = Set.m_Bilanznummer;		
	
//	Bereich über GetDiveceCaps lesen
	pInfo->m_rectDraw.SetRect(0, 0, pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES)); 
	
//	Koordinaten konvertieren
	pDC -> DPtoLP (pInfo -> m_rectDraw);
	
//	Y-Offset
	pDruckInfo->m_iYOffset = int(pDruckInfo->m_iTextHoehe/dYOffsetA);	//	Y-Koordinaten weiter auseinander 	
  	
//	CDruckInfo speichern
	ASSERT (NULL != pInfo);
	pInfo -> m_lpUserData = pDruckInfo;
	
//	alles dummy-Drucken und ggf. max. Seitenanzahl neu setzen
	OnPrint (pDC, pInfo);                                                    
	
	if (0 == pDruckInfo -> m_iPrintedPages)
		pInfo -> m_pPD -> m_pd.Flags |= PD_NOPAGENUMS;	//	keine Bereichsauswahl		
	{ 
		pInfo -> SetMinPage (1);
		pInfo -> SetMaxPage (pDruckInfo -> m_iPrintedPages);	
	}		
	
	pDruckInfo -> m_bOutput = TRUE;						//	jetzt alles ausgeben	
	pPrepareDruck -> DestroyWindow ();
}                                                          

void CAbfView::OnEndPrinting(CDC*, CPrintInfo* pInfo)
{
	ASSERT (NULL != pInfo);
	
	CDruckInfo *pDruckInfo = NULL;
	if (pInfo -> m_lpUserData)   
	{
		pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
		
	//	alten Grid-Positionen wieder einnehmen
		ASSERT (NULL != m_pGrid);
		m_pGrid->SetNumProperty("Col", pDruckInfo -> m_iOldCol);
		m_pGrid->SetNumProperty("Row", pDruckInfo -> m_iOldRow);
		m_bEventLockout = FALSE;	
	}		
	DELETE_OBJ (pDruckInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGak16View printing                                      
void CAbfView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
//	TODO: Add your specialized code here and/or call the base class
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	TRY
	{              
	//	Drucken erfolgt aus dem GRID: prüfe dortige Anzahl Datensätze
    	ASSERT (NULL != m_pGrid);                                    
    	int iRows = (int)m_pGrid -> GetNumProperty ("Rows") - 2;
    	if (iRows <= 0)
    		return;
    		    
		CWaitCursor wc;    		    
	//	lese CDruckInfos
		CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
		ASSERT (NULL != pDruckInfo);
		pDruckInfo->m_pDC = pDC;
		
	//	Zeichenbereich verkleinern
		pInfo -> m_rectDraw.left += iRandXY;
		pInfo -> m_rectDraw.right -= iRandXY;
		pInfo -> m_rectDraw.top += iRandXY;
		pInfo -> m_rectDraw.bottom -= iRandXY;
			
	//	akt. Zeichenposition speichern  
		pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;				
		
	//	speichere Druckpositionen der Spalten
		int iExtent = pInfo -> m_rectDraw.right - pInfo -> m_rectDraw.left;
		
	//	für Bilanzseite 1		
		for (int iPos = 0; iPos < iBilanzPageOne; iPos++)
		{   
			if (0 == iPos)
				pDruckInfo->m_DruckPos[iPos] = pInfo -> m_rectDraw.left;
			else                                                              
			{
				pDruckInfo->m_DruckPos[iPos] = MulDiv (ColumnInfoField[iPos-1].iDruckWidth, iExtent, 100) +
											   pDruckInfo->m_DruckPos[iPos-1];
											   
			//	prüfe Breite an Hand max. Textlänge
				pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-1].szMaxDruckText, 
												pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
			}											   
		}	                                   
		pDruckInfo->m_DruckPos[iPos] = pInfo -> m_rectDraw.right;//	iPos steht auf BlianzPageOne
		
	//	prüfe Breite an Hand max. Textlänge
		pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-1].szMaxDruckText, 
										pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
		
	//	für Bilanzseite 2        
		iPos++;
		pDruckInfo->m_DruckPos[iPos++] = pDruckInfo->m_DruckPos[0];				
		pDruckInfo->m_DruckPos[iPos++] = pDruckInfo->m_DruckPos[1];						
		
		int iMax = iBilanzPageOne+iBilanzPageTwo+2;
		for (;iPos < iMax-1; iPos++)
		{
			pDruckInfo->m_DruckPos[iPos] = MulDiv (ColumnInfoField[iPos-3].iDruckWidth, iExtent, 100) +
											   	   pDruckInfo->m_DruckPos[iPos-1];
		//	prüfe Breite an Hand max. Textlänge
			pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-3].szMaxDruckText, 
											pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);
		}											   	   
		pDruckInfo->m_DruckPos[iMax-1] = pInfo -> m_rectDraw.right;
		
	//	prüfe Breite an Hand max. Textlänge:: iPos steht auf iMax - 1
		pDruckInfo -> CheckTableFaktor (ColumnInfoField[iPos-3].szMaxDruckText, 
										pDruckInfo->m_DruckPos[iPos]-pDruckInfo->m_DruckPos[iPos-1]);				
		
	//	Seite 3 keine Prüfung mehr auf min. Textbreite		    
	//	für Bilanzseite 3       
		iPos = iMax;
		pDruckInfo->m_DruckPos [iPos++] = pInfo -> m_rectDraw.left;				    
		pDruckInfo->m_DruckPos [iPos++] = pDruckInfo->m_DruckPos [1];				    
		pDruckInfo->m_DruckPos [iPos++] = int(1.3*pDruckInfo->m_DruckPos [2]);	//	zweite Feld etwas breiter			    
		pDruckInfo->m_DruckPos [iPos++] = pInfo -> m_rectDraw.right;				    				    
		
	//	Drucken der Angaben                  
	//	immer zuerst Modus bestimmen
		BOOL bOutput = pDruckInfo->m_bOutput;
		pDruckInfo->m_bOutput = FALSE;			//	diesen Modus nur aktiveren,
												//	wenn akt. Seite gedruckt werden soll	
		pDruckInfo -> m_iPrintPage = 0;			//	Anzahl Seiten berechnen/bzw. akt. Seite setzen
		CString strText;                        //	Hilfstext  
		
	//	für alle Bilanzseiten
		for (pDruckInfo->m_iBilanzPage = 1; pDruckInfo -> m_iBilanzPage<=iBilanzPageCnt; pDruckInfo->m_iBilanzPage++)
		{   
		//	prüfe, ob für Bilanzseite 3 Wert zu erwarten sind				
			if (3 == pDruckInfo->m_iBilanzPage)
			{        
				BOOL bHasVal = FALSE;		//	Standard sind keine Begründungen
					
			//	Spalte bleibt immer gleich
				m_pGrid -> SetNumProperty ("Col", iVerfahrenBegrCol);					
				for (int i = 1; !bHasVal && (i <= iRows); i++)
				{               
					m_pGrid -> SetNumProperty ("Row", i);					
					strText = m_pGrid -> GetStrProperty("Text");
					bHasVal = ((!strText.IsEmpty()) && (!(strText == EmptyMemo)));
				}
					        
			//	wenn keine Werte zu erwarten sind, alles beenden					        
				if (!bHasVal)
					break;																			
			}	
		
		//	aktuelle Zeichenposition ist am Anfang der Seite immer ganz oben
			pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;				
			
		//	Seitenzähler zunächst erhöhen				
			pDruckInfo -> m_iPrintPage++;			
			
		//	Ausgabeflag setzen        
			if (pDruckInfo->m_bOutput)	//	dieses Flag ist nur einmal für die Ausgabe der akt.
				return;					//	Seite gesetzt worden
			pDruckInfo -> m_bOutput = (bOutput && (pDruckInfo->m_iPrintPage == (int)pInfo->m_nCurPage)); 			
			
		//	Seitenkopf
			PrintPageHead (pInfo);
	                        
		//	Tabellenkopf
			PrintTableHead (pInfo);	
			    
		//	alle Zeilen der aktuellen Bilanzseite ausgeben			    
			for (int iGridIndex = 1; iGridIndex <= iRows; iGridIndex++)
			{                    
			//	bei Bilanzseite 3 extra Test auf gültigen Inhalt
				if (3 == pDruckInfo->m_iBilanzPage)
				{
					m_pGrid -> SetNumProperty ("Row", iGridIndex);																		
					m_pGrid -> SetNumProperty ("Col", iVerfahrenBegrCol);							
					strText = m_pGrid -> GetStrProperty("Text");
					if (strText.IsEmpty () || (strText == EmptyMemo))
						continue;		//	weiter mit der nächsten Zeile
				}
				
			//	wenn nicht genügend Platz für aktuelle Seite
				if (!PrintRow (iGridIndex, pInfo, pDruckInfo->m_bOutput))	
				{                                   
				//	Spaltenlinien drucken
					if (pDruckInfo -> m_bOutput)
						PrintTableLines (pInfo);
				
				//	Seitenzähler erhöhen
					pDruckInfo -> m_iPrintPage++;						
				
				//	Ausgabeflag setzen					        
					if (pDruckInfo->m_bOutput)	//	dieses Flag ist nur einmal für die Ausgabe der akt.
						return;					//	Seite gesetzt worden
					pDruckInfo -> m_bOutput = (bOutput && (pDruckInfo->m_iPrintPage == (int)pInfo->m_nCurPage));					
						
				//	Zeichenposition akt.						
					pDruckInfo -> m_iY = pInfo -> m_rectDraw.top;										
					
				//	Seitenkopf
					PrintPageHead (pInfo);
	
				//	Tabellenkopf
					PrintTableHead (pInfo);
					                                                            
				//	jetzt die aktuelle Zeile noch einmal ausgeben					                                                            
					PrintRow (iGridIndex, pInfo, pDruckInfo->m_bOutput);		
				}					
			}	//	end_for:	alle Zeilen
			
		//	Spaltenlinien drucken
			if (pDruckInfo -> m_bOutput)
				PrintTableLines (pInfo);									    		
		}		//	end_for:	alle Bilanzseiten		
		
	//	ggf. max. Seitenzahl speichern			
		if (!bOutput)
			pDruckInfo -> m_iPrintedPages = pDruckInfo->m_iPrintPage;				
	}		
	CATCH (CResourceException, re)
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_CANNOT_PRINT);
	}		
	AND_CATCH (CUserException, re)
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_CANNOT_PRINT);
	}
	AND_CATCH (CMemoryException, me)      
	{
		((CGak16App *) AfxGetApp ()) -> OutputMessage (IDS_NO_MEMORY);
	}   
	AND_CATCH (CDBException, db)
	{                           
		((CGak16App *) AfxGetApp ()) -> OutputMessage (db -> m_strError);
	}                
	AND_CATCH (CFileException, fe)
	{
		((CGak16App *) AfxGetApp ()) -> OutputFileError (fe -> m_cause);
	}
	END_CATCH	
}	
		                   
//	drucke Seitenkopf		                   
void CAbfView::PrintPageHead (CPrintInfo *pInfo)
{
	ASSERT (NULL != pInfo);

//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	ASSERT (NULL != pDruckInfo->m_pDC);
	
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);		
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dKopfFaktor18A), FW_BOLD));
	
	int iX = pInfo -> m_rectDraw.left + iRandXY;
	int iY = pDruckInfo -> m_iY + (pDruckInfo -> m_iTextHoehe / 2);

//	Texte ausgeben	
	CString strOut ("Betriebliche Abfallbilanz");
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength (), pDruckInfo->m_bOutput));
	
//	Zusatzfeld entsprechend Bilanz-Page ausgeben
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dKopfFaktor15A)));	
	strOut = "Abfalldatenerfassung - Seite ";
	switch (pDruckInfo -> m_iBilanzPage)    
	{
		case 1:
			strOut += "1";
		break;
		case 2:            
			strOut += "2";
		break;
		case 3:
			strOut = "Maßnahmen und Begründungen";
		break;
		default:
			ASSERT (FALSE);
	}
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength (), pDruckInfo->m_bOutput));
	
//	jetzt Bilanznummer			
	strOut = "Bilanz-Nr.: ";	
	VERIFY (Druck.ChangeFont (int(pDruckInfo->m_iTextHoehe*dInfoFaktor13A), FW_MEDIUM));			
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));
	int iLeft = iX;  //	Umrandungsposition speichern	        
	strOut = " " + pDruckInfo->m_strBilanzNumber + " ";
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, BilanzNummerLaenge+2, pDruckInfo->m_bOutput));	
	int iRight = iX; //	Umrandungsposition speichern	
	iX = pInfo -> m_rectDraw.right - iRandXY;							   
	char Buffer20 [20] = "";
	wsprintf (Buffer20, "Blatt-Nr.: %d/%d", pInfo->m_nCurPage, pDruckInfo->m_iPrintedPages);
	VERIFY (Druck.TextOut (iX, iY, Buffer20, TRUE, FALSE, strlen(Buffer20), pDruckInfo->m_bOutput));									   
	CSize szExt (Druck.GetTextExtent (Buffer20, 1));
	
//	BilanzNr. ggf. umranden
	if (pDruckInfo->m_bOutput) 
	{
		int iYOffset = (pDruckInfo->m_iTextHoehe / 5);
		Druck.DrawRectangle (iLeft, iY - iYOffset, iRight, iY + szExt.cy + iYOffset);			
	}		
	iY += szExt.cy + pDruckInfo->m_iYOffset;
	                                       
//	jetzt alles Einrahmen
	if (pDruckInfo->m_bOutput)
		Druck.DrawRectangle (pInfo->m_rectDraw.left, pDruckInfo -> m_iY, pInfo->m_rectDraw.right, iY);		                                       
		
//	zuletzt akt. Zeichenposition akt.	
	pDruckInfo -> m_iY = iY + pDruckInfo -> m_iTextHoehe;		                                                                                               
}    

//	drucke Tabellenkopf von Bilanzseite 1/2/3
void CAbfView::PrintTableHead (CPrintInfo *pInfo)
{
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	
//	Punkt 3 ist im Kopf für die Bilanzseiten 1 und 2 gleich
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);		
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*dInfoFaktor13A), FW_MEDIUM));			
	
//	Zeichenpositionen lesen	
	int iX = pInfo -> m_rectDraw.left;
	int iY = pDruckInfo -> m_iY;
	                       
//	Punkt 3/4 ausgeben	                               
	CString strOut = (3 == pDruckInfo -> m_iBilanzPage) ? " 4 " : " 3 ";	
	VERIFY (Druck.TextOut (iX, iY, strOut, TRUE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));	
	CSize szExt (Druck.GetTextExtent (strOut, strOut.GetLength ()));
	
//	ggf. Punkt 3/4 umranden	
	if (pDruckInfo->m_bOutput)                                
		Druck.DrawRectangle (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY, 
							 iX, pDruckInfo -> m_iY + szExt.cy);		
	
	iY += int(pDruckInfo -> m_iTextHoehe / 2);
	if (3 == pDruckInfo -> m_iBilanzPage)
		strOut = "Begründung der Notwendigkeit zur Abfallbeseitigung, insbesondere Angaben zur";
	else
		strOut = "Übersicht zu Art, Menge und Verbleib der entsorgten Abfälle";
	iX += (3*iRandXY);				
	VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));										 						 
	
	if (3 == pDruckInfo -> m_iBilanzPage)
	{   
		iY -= int(pDruckInfo->m_iYOffset / 2);
		strOut = "mangelnden Verwertbarkeit";		
		VERIFY (Druck.TextOut (iX, iY, strOut, FALSE, TRUE, strOut.GetLength(), pDruckInfo->m_bOutput));										 							
	}		

//	Rahmen für Punkt 3/4
	if (pDruckInfo->m_bOutput)
	{                                
		Druck.DrawRectangle (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY, 
							 pInfo -> m_rectDraw.right, iY);

	//	Tabellenspitzenkoordinate Y merken
		pDruckInfo->m_iTopTable = iY;									 
	}							 

//	Tabellenköpfe ausgeben: Zuerst Nummern
	iY += int(pDruckInfo -> m_iTextHoehe / 2);
	
//	jetzt ggf. Nummern ausgeben
	if (pDruckInfo->m_bOutput)
	{                                    
		if (1 == pDruckInfo -> m_iBilanzPage)
		{
			for (int iPos = 0; iPos < iBilanzPageOne; iPos++)
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos],
										 	 pDruckInfo -> m_DruckPos[iPos+1], iY,
										 	 ColumnInfoField[iPos].pDruckNumber));
		}	
		else
		{                                    
			if (2 == pDruckInfo -> m_iBilanzPage)
			{
				for (int iPos = iBilanzPageOne; iPos < iBilanzPageOne+iBilanzPageTwo-1; iPos++)
					VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos+2],
										 	 	 pDruckInfo -> m_DruckPos[iPos+3], iY,
										 	 	 ColumnInfoField[iPos].pDruckNumber));
			}										 	 	 	
			else
			{   
				int iPos = iBilanzPageOne+iBilanzPageTwo+2;
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.1"));								
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[++iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.2"));			
				VERIFY (Druck.TextOutCenter (pDruckInfo->m_DruckPos[++iPos],pDruckInfo->m_DruckPos[iPos+1], iY, "4.3"));
			}
		}	
	}										 	
		
	iY += szExt.cy + int(pDruckInfo -> m_iTextHoehe / 2);
	
//	Zeilenende ausgeben		
	if (pDruckInfo->m_bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo -> m_rectDraw.left, iY);							
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, iY));					
	}
						
//	jetzt Tabellenüberschriften
//	zuerst anderen Zeichensatz
	VERIFY (NULL != Druck.ChangeFont ((int)(pDruckInfo->m_iTextHoehe*
										    pDruckInfo->m_dTableHeadFaktor)));			
	szExt = Druck.GetTextExtent (" ", 1);		

//	zuerst die max. Y-Koordinate ermitteln
	int iSpace = int(szExt.cy / iSpaceVal);	//	Zwischenraum für x/y-Werte
	iY += iSpace;							//	diesen Platz zum vorigen Abschnitt
	           
	int iFirstRow = 0;
	int iMaxRow = 0;	           
	if (3 == pDruckInfo -> m_iBilanzPage) 		
	{
		iFirstRow = iBilanzPageOne+iBilanzPageTwo;
		iMaxRow = MaxTableEntries;
	}   
	else
	{   
		iFirstRow = 0;
		iMaxRow = iBilanzPageOne+iBilanzPageTwo;
	}
	
//	Clippingrechteck	    
	CRect rc (0, iY, 0, iY+szExt.cy);	    
	int iMaxY = 0;
	for (int i = iFirstRow; i < iMaxRow; i++)
	{   
		if (i < iBilanzPageOne)
		{
			rc.right = pDruckInfo->m_DruckPos[i+1];
			rc.left = pDruckInfo->m_DruckPos [i];	
		}			
		else   
		{
			if (i < (iBilanzPageOne+iBilanzPageTwo))
			{
				rc.right = pDruckInfo->m_DruckPos[i+2];
				rc.left = pDruckInfo->m_DruckPos[i+1];				
			}				
			else
			{
				rc.right = pDruckInfo->m_DruckPos[i+3];
				rc.left = pDruckInfo->m_DruckPos[i+2];					
			}				
		}   
		ASSERT (rc.Width () > 0);						
        
	//	y-Koordinate berechnen        
		rc.left += iSpace;
		rc.right -= iSpace;
		iMaxY = max (iMaxY, pDruckInfo->m_pDC->DrawText(TableCaptions[i].pCaption,-1,rc,DT_CALCRECT | uiTableFormat));
	}
	    
//	y-Koordinate  vergrößern	    
	iY += iMaxY;
		    
//	jetzt ggf. Überschriften ausgeben
	if (pDruckInfo->m_bOutput)
	{       
		rc.bottom = iY;
		
	//	FirstRow/MaxRow neu setzen
		if (1 == pDruckInfo->m_iBilanzPage)
		{
			iFirstRow = 0;
			iMaxRow = iBilanzPageOne;
		}		
		else
		{   
			if (2 == pDruckInfo->m_iBilanzPage)
			{
				iFirstRow = iBilanzPageOne;
				iMaxRow = iFirstRow + iBilanzPageTwo;
			}
			else
			{			
				iFirstRow = iBilanzPageOne + iBilanzPageTwo;
				iMaxRow = iFirstRow + iBilanzPageThree;
			}			
		}
		
		for (i = iFirstRow; i < iMaxRow; i++)
		{   
			if (i < iBilanzPageOne)
			{
				rc.right = pDruckInfo->m_DruckPos[i+1];
				rc.left = pDruckInfo->m_DruckPos [i];	
			}			
			else   
			{
				if (i < (iBilanzPageOne+iBilanzPageTwo))
				{
					rc.right = pDruckInfo->m_DruckPos[i+2];
					rc.left = pDruckInfo->m_DruckPos[i+1];				
				}				
				else
				{
					rc.right = pDruckInfo->m_DruckPos[i+3];
					rc.left = pDruckInfo->m_DruckPos[i+2];					
				}				
			}   
			ASSERT (rc.Width () > 0);						
        
		//	Text ausgeben
			rc.left += iSpace;
			rc.right -= iSpace;
			pDruckInfo->m_pDC->DrawText(TableCaptions[i].pCaption,-1,rc,uiTableFormat);
		}		
	}	
		
//	Zeilenende ausgeben 	
	iY += iSpace;	//	Zwischenraum zum vorigen Abschnitt	
	if (pDruckInfo -> m_bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo->m_rectDraw.left, iY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, iY));								
	}
	                            
//	Zeichenposition speichern	                            
	pDruckInfo -> m_iY = iY;	
}    

//	aktuelle Zeile berechnen bzw. ausgeben
//	BOOL, wenn Platz nicht mehr ausreicht
BOOL CAbfView :: PrintRow (int iGridIndex, CPrintInfo *pInfo, BOOL bOutput)	
{   
	ASSERT (iGridIndex > 0);
	ASSERT (NULL != m_pGrid);	
	ASSERT (iGridIndex < ((int)m_pGrid -> GetNumProperty ("Rows") - 1));
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);         
	ASSERT (NULL != pDruckInfo->m_pDC);
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo -> m_iYOffset);		
	VERIFY (Druck.ChangeFont (int(pDruckInfo -> m_iTextHoehe*pDruckInfo->m_dTableHeadFaktor),
							  FW_NORMAL, FaceName, 1));	//	kursiv

//	bestimme max. Y-Koordinate
	int iFirstRow = 0;
	int iMaxRow = 0;	           
	if (3 == pDruckInfo -> m_iBilanzPage) 		
	{
		iFirstRow = iBilanzPageOne+iBilanzPageTwo;
		iMaxRow = MaxTableEntries;
	}   
	else
	{   
	//	beide Bilanzseiten prüfen
		iFirstRow = 0;
		iMaxRow = iBilanzPageOne+iBilanzPageTwo;
	}	
	
//	lese akt. Zeichenposition
	int iY = pDruckInfo -> m_iY;
	CSize szExt (pDruckInfo->m_pDC->GetTextExtent (" ", 1));	
	int iSpace = szExt.cy / iSpaceVal;	//	Zwischenraum für x/y-Koordinaten
	iY += iSpace;
	
//	Clippingrechteck	    
	CRect rc (0, iY, 0, iY+szExt.cy);		
	
//	weitere Werte init.	
	int iMaxY = 0;         
	CString strText;
	
//	Zeile in GRID setzen
	m_pGrid -> SetNumProperty ("Row", iGridIndex);
	int iGridCol = 0;		
	for (int i = iFirstRow; i < iMaxRow; i++)
	{   
		if (i < iBilanzPageOne)
		{
			rc.right = pDruckInfo->m_DruckPos[i+1];
			rc.left = pDruckInfo->m_DruckPos [i];	
		}			
		else   
		{
			if (i < (iBilanzPageOne+iBilanzPageTwo))
			{
				rc.right = pDruckInfo->m_DruckPos[i+2];
				rc.left = pDruckInfo->m_DruckPos[i+1];				
			}				
			else
			{
				rc.right = pDruckInfo->m_DruckPos[i+3];
				rc.left = pDruckInfo->m_DruckPos[i+2];					
			}				
		}   
		ASSERT (rc.Width () > 0);						
        
	//	y-Koordinate berechnen        
		rc.left += iSpace;
		rc.right -= iSpace;         
		
	//	lese akt. Text aus GRID		
		m_pGrid -> SetNumProperty ("Col", TableCaptions[i].iGridCol);			
		strText = m_pGrid -> GetStrProperty("Text");
			
		iMaxY = max (iMaxY, Druck.DrawText(strText,strText.GetLength(),rc,
										   DT_CALCRECT|TableCaptions[i].iCenterMode));
	}               
	iY += (iMaxY + iSpace);
	
//	Kann diese Seite gedruckt werden ?
	if (iY > pInfo -> m_rectDraw.bottom)
		return FALSE;				//	dann zurück
	
//	Seite ggf. ausgeben	
	if (bOutput)
	{	
	//	Zeile ausgeben
		rc.bottom = iY - iSpace;	//	Zwischenraum wieder abziehen
		
	//	akt. Zeile/Spalte bestimmen		
		if (3 == pDruckInfo -> m_iBilanzPage) 		
		{
			iFirstRow = iBilanzPageOne+iBilanzPageTwo;
			iMaxRow = MaxTableEntries;
		}   
		else
		{   
			if (1 == pDruckInfo -> m_iBilanzPage) 		
			{
				iFirstRow = 0;
				iMaxRow = iBilanzPageOne;
			}
			else
			{   
				iFirstRow = iBilanzPageOne;
				iMaxRow = iFirstRow+iBilanzPageTwo;
			}
		}			
		
	//	alle Spalten ausgeben		
		for (int j = iFirstRow; j < iMaxRow; j++)
		{   
			if (j < iBilanzPageOne)
			{
				rc.right = pDruckInfo->m_DruckPos[j+1];
				rc.left = pDruckInfo->m_DruckPos [j];	
			}			
			else   
			{
				if (j < (iBilanzPageOne+iBilanzPageTwo))
				{
					rc.right = pDruckInfo->m_DruckPos[j+2];
					rc.left = pDruckInfo->m_DruckPos[j+1];				
				}				
				else
				{
					rc.right = pDruckInfo->m_DruckPos[j+3];
					rc.left = pDruckInfo->m_DruckPos[j+2];					
				}				
			}   
			ASSERT (rc.Width () > 0);						
        
		//	y-Koordinate berechnen        
			rc.left += iSpace;
			rc.right -= iSpace;         
		
		//	lese akt. Text aus GRID		
			m_pGrid -> SetNumProperty ("Col", TableCaptions[j].iGridCol);			
			strText = m_pGrid -> GetStrProperty("Text");
        
		//	Text ausgeben        
			Druck.DrawText(strText,strText.GetLength(),rc,TableCaptions[j].iCenterMode);
		}			
	}	//	Ende der Ausgabe
	
//	akt. Zeichenposition immer weiterführen
	pDruckInfo -> m_iY += (iMaxY + (2*iSpace));
	
//	akt. Zeile unterstreichen
	if (bOutput)
	{
		pDruckInfo -> m_pDC -> MoveTo (pInfo -> m_rectDraw.left, pDruckInfo -> m_iY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (pInfo -> m_rectDraw.right, pDruckInfo -> m_iY));				
	}		

	return TRUE;
}
                                 
//	Tabellenlinien ausgeben                                 
void CAbfView::PrintTableLines (CPrintInfo *pInfo)
{   
//	prüfe Parameter			                           
	ASSERT (NULL != pInfo);
	
//	lese CDruckInfos
	CDruckInfo *pDruckInfo = (CDruckInfo *) pInfo -> m_lpUserData;
	ASSERT (NULL != pDruckInfo);
	ASSERT (NULL != pDruckInfo -> m_pDC);
	ASSERT_VALID (pDruckInfo -> m_pDC);			               
	    
//	prüfe Ausgabemodus	    
	if (!pDruckInfo -> m_bOutput)
		return;
		
//	prüfe Parameter
	ASSERT (pDruckInfo -> m_iTopTable >= 0);
	ASSERT (pDruckInfo -> m_iTopTable < pDruckInfo -> m_iY);	
	
//	max. Koordinate steht in pDruckInfo -> m_iY;
//	äußerer Tabellenrahmen: für alle Bilanzen gleich
	int iTopY = pDruckInfo -> m_iTopTable;
	int iBottomY = pDruckInfo -> m_iY;
	
	CDruck Druck (pDruckInfo->m_pDC, pDruckInfo->m_iYOffset);				
	Druck.DrawRectangle (pInfo -> m_rectDraw.left, iTopY, 
						 pInfo -> m_rectDraw.right, iBottomY);					

//	alle Spaltenrahmen zeichnen
	int iFirst = 0;
	int iLast = 0;	
//	für Bilanzseite
	if (1 == pDruckInfo -> m_iBilanzPage)
	{
		iFirst = 1;
		iLast = iBilanzPageOne;
	}			
	else
	{
		if (2 == pDruckInfo -> m_iBilanzPage)
		{
			iFirst = iBilanzPageOne+2;			        
			iLast = iBilanzPageOne+iBilanzPageTwo+1;			        
		}
		else
		{
			iFirst = iBilanzPageOne+iBilanzPageTwo+2;
			iLast = sizeof (pDruckInfo->m_DruckPos) / sizeof (int);
		}				
	}	
			                           
//	Linien zeichnen	
	for (int iX = pDruckInfo -> m_DruckPos [iFirst]; iFirst < iLast; iFirst++, 
		     iX = pDruckInfo -> m_DruckPos [iFirst])
	{
		pDruckInfo -> m_pDC -> MoveTo (iX, iTopY);						
		VERIFY (pDruckInfo -> m_pDC -> LineTo (iX, iBottomY));				
	}			
}
*/
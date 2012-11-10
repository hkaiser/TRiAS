// RecView.cpp : implementation of the CDaoRecordViewExt class
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp

#include "numedit.h"	// CErzNrEdit
#include "gaksete.h"	// CDaoRecordsetExt
#include "changenr.h"	// CChangeKeyDialog
#include "childfrm.h"	// CChildFrame
#include "selnum.h"		// CSelectNumberDlg
#include "selset.h"		// CSelectSet

// Crystal-Reports-Header
#include "peplus.h"
#include "crpe.h"

#include "recView.h"	// zugeh. Header

// globale Var.
#include "gakset.h"
#include "abfset.h"

extern CGakSet * g_pErzSet;
extern CAbfSet * g_pAbfSet;

// Anzeige von Daten (JG981028)
#include "QueryRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CALLBACK SetBranchenNummer (LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt

IMPLEMENT_DYNCREATE(CDaoRecordViewExt, CDaoRecordView)

BEGIN_MESSAGE_MAP(CDaoRecordViewExt, CDaoRecordView)
	//{{AFX_MSG_MAP(CDaoRecordViewExt)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(IDM_CHANGE_KEY, OnUpdateChangeKey)
	ON_UPDATE_COMMAND_UI(IDM_DELETE_REKORD, OnUpdateDeleteRekord)
	ON_UPDATE_COMMAND_UI(IDM_GOTO_BOOKMARK, OnUpdateGotoBookmark)
	ON_UPDATE_COMMAND_UI(IDM_NEW_REKORD, OnUpdateNewRekord)
	ON_UPDATE_COMMAND_UI(IDM_SET_BOOKMARK, OnUpdateSetBookmark)
	ON_COMMAND(IDM_CHANGE_KEY, OnChangeKey)
	ON_COMMAND(IDM_DELETE_REKORD, OnDeleteRekord)
	ON_COMMAND(IDM_GOTO_BOOKMARK, OnGotoBookmark)
	ON_COMMAND(IDM_NEW_REKORD, OnNewRekord)
	ON_COMMAND(IDM_SET_BOOKMARK, OnSetBookmark)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_UPDATE_COMMAND_UI(IDM_LOOK_NR, OnUpdateLookNr)
	ON_COMMAND(IDM_AKTBILANZ, OnAktbilanz)
	ON_UPDATE_COMMAND_UI(IDM_AKTBILANZ, OnUpdateAktbilanz)
	ON_COMMAND(IDM_ABGLEICH_AKT, OnAbgleichAkt)
	ON_COMMAND(IDB_ABGLEICH, OnAbgleich)
	ON_COMMAND(IDM_ABGLEICH_AKTNEW, OnAbgleichAktnew)
	ON_UPDATE_COMMAND_UI(IDM_ABGLEICH_AKT, OnUpdateAbgleichAkt)
	ON_UPDATE_COMMAND_UI(IDM_ABGLEICH_AKTNEW, OnUpdateAbgleichAktnew)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(IDB_ABGLEICH, OnUpdateAbgleich)
	//}}AFX_MSG_MAP
	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CDaoRecordView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CDaoRecordView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CDaoRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt construction/destruction

CDaoRecordViewExt :: CDaoRecordViewExt()
				   : CDaoRecordView(CDaoRecordViewExt::IDD)
{
	m_pPrintJob = NULL;
	m_pSet = NULL;
	m_pSheet = NULL;
	//m_bOnSearch = FALSE;
//	m_iTextHoehe = 0;
}

CDaoRecordViewExt :: ~CDaoRecordViewExt ()
{
	if (m_pPrintJob)
		m_pPrintJob -> Close ();

	CGakApp * pApp = (CGakApp *) AfxGetApp();
	if (NULL != pApp)
		pApp->ReleaseView(this);
}

void CDaoRecordViewExt::OnInitialUpdate()
{
	CDaoRecordView::OnInitialUpdate();

	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);

//	Buchmarken setzen
	try
	{
		if (!m_pSet -> IsBOF () &&  !m_pSet -> IsEOF ())
		{
			COutputLockError le (m_pSet);
			m_pSet -> MoveLast ();
			m_varBookmarkLast = m_pSet -> GetBookmark ();
			m_pSet -> MoveFirst ();
			
		//	wenn 1. und letzter Satz identisch sind
			if (m_varBookmarkFirst == m_varBookmarkLast)
			{
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;		// kein Next
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;		// kein Last
			}

			m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;		// rückwärts nimmer !

			m_pSet -> LockReckord (TRUE);			// akt. Satz(Sätze) verriegel(n)
		}
		else
			m_varBookmarkLast.Clear ();
	}	
	catch (CException *e)
	{
		m_varBookmarkLast.Clear ();
		e -> Delete ();		// nur auffangen
	}

	Sync();
	UpdateData (FALSE);			// Dialoge akt.
}

void CDaoRecordViewExt::DoDataExchange(CDataExchange* pDX)
{
	CDaoRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDaoRecordViewExt)
	//}}AFX_DATA_MAP
	ASSERT (m_pSheet != NULL);
	ASSERT_VALID (m_pSheet);
	m_pSheet -> GetActivePage () -> UpdateData (pDX -> m_bSaveAndValidate);
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt printing
BOOL CDaoRecordViewExt::OnPreparePrinting(CPrintInfo* pInfo)
{
//	Prüfe Parameter
	ASSERT (pInfo != NULL);

//	Diese Angaben sind sowohl für Vorschau als auch Drucken gleich
	//pInfo -> SetMinPage (1);
	//pInfo -> SetMaxPage (1);
	pInfo -> m_pPD -> m_pd.Flags |= PD_NOPAGENUMS;	//	keine Bereichsauswahl

	if (pInfo -> m_bPreview)				// bei Preview Operation
		pInfo -> m_nNumPreviewPages = 1;	// nur eine Seite bei Vorschau

	UpdateData (TRUE);						// lese Werte der akt. Page

	return DoPreparePrinting(pInfo);
}

/*
void CDaoRecordViewExt::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
//	aktuelle Texthöhe speichern
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);

	TEXTMETRIC tm;
	memset (&tm, 0, sizeof (tm));
	if (! pDC -> GetTextMetrics (&tm))
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		pApp -> OutputMessage (IDS_CANNOT_PRINT);
		m_iTextHoehe = 0;
	}

	m_iTextHoehe = tm.tmHeight;
}
*/

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt diagnostics

#ifdef _DEBUG
void CDaoRecordViewExt::AssertValid() const
{
	CDaoRecordView::AssertValid();
}

void CDaoRecordViewExt::Dump(CDumpContext& dc) const
{
	CDaoRecordView::Dump(dc);
}

CDocument* CDaoRecordViewExt::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocument)));
	return m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt database support
CDaoRecordset* CDaoRecordViewExt::OnGetRecordset()
{
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);

	return m_pSet;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordViewExt message handlers
BOOL CDaoRecordViewExt::OnMove(UINT nIDMoveCommand) 
{
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);

	COutputLockError le (m_pSet);
	if (OnMoveExt (nIDMoveCommand))
	{
	//	Show results of move operation
		UpdateData (FALSE);

	//	Satz sperren 
		m_pSet -> LockReckord ();

	//	Überschrift akt.
		SetCaption ();
		
		return TRUE;
	}

	return FALSE;
}

//	erweiterte OnMove-Funktion: leicht modif. Orginalquelle
BOOL CDaoRecordViewExt::OnMoveExt(UINT nIDMoveCommand)
{
	ASSERT_VALID(this);
	ASSERT (m_pSet != NULL);

	if (!m_pSet -> LockReckord (FALSE, this))		// Satz entriegeln
		return FALSE;

	BOOL bBookmarkable = m_pSet->CanBookmark();
	BOOL bScrollable = m_pSet->CanScroll();

	switch (nIDMoveCommand)
	{
		case ID_RECORD_PREV:
			m_pSet->MovePrev();

			if (!m_pSet->IsBOF())
			{
				if (bBookmarkable)
					m_varBookmarkCurrent = m_pSet->GetBookmark();

				// Enable forward scrolling
				m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;

				if (bScrollable)
				{
					m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;

					if (IsOnFirstRecord())
						// Disable backward scrolling
						m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
					else
						m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
				}
				else
				{
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
				}


				break;
			}
			// Fall through to reset to first record

		case ID_RECORD_FIRST:
			m_pSet->MoveFirst();

			// backward scrolling never allowed after movefirst
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;

			if (m_pSet->IsEOF())
			{
				// Empty recordset, disable forward too
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
			}
			else
			{
				if (bBookmarkable)
				{
					m_varBookmarkCurrent = m_pSet->GetBookmark();
					m_varBookmarkFirst = m_varBookmarkCurrent;
				}

				// Enable forward scrolling
				m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;

				if (bScrollable)
					m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;
				else
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
			}

			break;

		case ID_RECORD_NEXT:
			m_pSet->MoveNext();

			if (!m_pSet->IsEOF())
			{
				if (bBookmarkable)
					m_varBookmarkCurrent = m_pSet->GetBookmark();

				if (IsOnLastRecord())
				{
					// Disable forward scrolling
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
				}
				else
				{
					m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;
					m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;
				}

				if (bScrollable)
					m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
				else
				{
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
				}

				break;
			}

			// Can't fall through to move last
			if (!bScrollable)
			{
				// At the end of forward only recordset
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
				break;
			}

			// Fall through to reset to last record

		case ID_RECORD_LAST:
			m_pSet->MoveLast();

			// forward scrolling never allowed after movelast
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;

			if (m_pSet->IsBOF())
			{
				// Empty recordset, disable backward too
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
			}
			else
			{
				if (bBookmarkable)
				{
					m_varBookmarkCurrent = m_pSet->GetBookmark();
					m_varBookmarkLast = m_varBookmarkCurrent;
				}

				// Enable backward scrolling
				if (bBookmarkable)
					m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
				else
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
			}

			break;

		default:
			// Unexpected case value
			ASSERT(FALSE);
	}

	// Show results of move operation
	// UpdateData(FALSE); // jetzt noch nicht !
	return TRUE;
}

void CDaoRecordViewExt::OnEditCopy() 
{
	// TODO: Add your command handler code here
	ASSERT (m_pSheet != NULL);
	CEdit *pWnd = (CEdit *) m_pSheet -> GetActivePage () -> GetFocus ();
	if (pWnd)
		pWnd -> Copy (); 
}

void CDaoRecordViewExt::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (HasRecords ());
}

void CDaoRecordViewExt::OnEditCut() 
{
	// TODO: Add your command handler code here
	ASSERT (m_pSheet != NULL);
	CEdit *pWnd = (CEdit *) m_pSheet -> GetActivePage () -> GetFocus ();
	if (pWnd)
		pWnd -> Cut (); 	
}

void CDaoRecordViewExt::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (HasRecords ());	
}

void CDaoRecordViewExt::OnEditPaste() 
{
	// TODO: Add your command handler code here
	ASSERT (m_pSheet != NULL);
	CEdit *pWnd = (CEdit *) m_pSheet -> GetActivePage () -> GetFocus ();
	if (pWnd)
		pWnd -> Paste (); 	
}

void CDaoRecordViewExt::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (HasRecords ());	
}

void CDaoRecordViewExt::OnEditUndo() 
{
	// TODO: Add your command handler code here
	ASSERT (m_pSheet != NULL);
	CEdit *pWnd = (CEdit *) m_pSheet -> GetActivePage () -> GetFocus ();
	if (pWnd && pWnd -> CanUndo ())
		pWnd -> Undo (); 	
}

void CDaoRecordViewExt::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (HasRecords ());	
}

void CDaoRecordViewExt::OnDestroy() 
{
//	ggf. Sperrmarke löschen
	ASSERT (m_pSet != NULL);
	if (!m_pSet -> LockReckord (FALSE, this))		// Satz ggf. entriegeln
		return;
		
	CDaoRecordView::OnDestroy();		// normales Ende !	
	
//	TODO: Add your message handler code here
}

//	Satz über seine Nummer suchen
BOOL CDaoRecordViewExt::SearchNummer (const char *pNummer, BOOL bOutErrMsg/*=TRUE*/)
{
	ASSERT (pNummer != NULL && AfxIsValidString (pNummer));

	BOOL bOk = FALSE;		// noch nichts getan

	try
	{
		if (! HasRecords ())
			return TRUE;

	//	Satz bereits geladen
		ASSERT (m_pSet != NULL);
		if (!*pNummer || (m_pSet -> m_Nummer == pNummer))
			return TRUE;

		CWaitCursor wc;
		COutputLockError le (m_pSet);
	//	akt. Satz entriegeln und speichern
		if (!m_pSet -> LockReckord (FALSE, this))		
			return FALSE;

	//	akt. Pos. merken
		COleVariant BookMark (m_pSet -> GetBookmark ());
		
	//	neue Nummer suchen
		COleVariant Var (pNummer, VT_BSTRT);
		if (m_pSet -> Seek ("=", &Var))
		{
		//  Synchronisation
			Sync();

		//	Show results of seek operation
			UpdateData (FALSE);

		//	Überschrift akt.
			SetCaption ();

			bOk = TRUE;
		}
		else
		{
			if (bOutErrMsg)
			{
				CGakApp *pApp = (CGakApp *) AfxGetApp ();
				ASSERT (pApp != NULL);
				CString strInfo;
				AfxFormatString1 (strInfo, IDS_ERZ_NOT_FOUND, pNummer);
				pApp -> OutputMessage (strInfo);	// Nachricht an Nutzer ausgeben					
			}
			m_pSet -> SetBookmark (BookMark);				// alten Satz einstell.
		}

	//	Scroll-Status setzen
		SetScrollValues ();

	//	akt. Satz sperren 
		return m_pSet -> LockReckord ();
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

	return bOk;
}

//	Buchmarke setzbar ?
BOOL CDaoRecordViewExt::CanSetBookmark (void)
{
	return HasRecords ();
}

//	Buchmarke setzen
void CDaoRecordViewExt::OnSetBookmark ()
{
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());

	try
	{
		if (CanSetBookmark ())
			m_varBookmark = m_pSet -> GetBookmark ();
		else
			m_varBookmark.Clear ();
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

//	kann Buchmarke angesprungen werden ?
BOOL CDaoRecordViewExt::CanGotoBookmark (void)
{
	return (HasRecords () && (m_varBookmark.vt != VT_EMPTY));
}

//	Buchmarke anspringen
void CDaoRecordViewExt::OnGotoBookmark ()
{
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());

	try
	{
	//	Operation ausführbar ?
		if (!CanGotoBookmark ())
		{
			m_varBookmark.Clear ();
			return;
		}

	//	akt. Satz entriegeln und speichern
		if (!m_pSet -> LockReckord (FALSE, this))		
			return;

	//	akt. Pos. merken
		CWaitCursor wc;
		COutputLockError le (m_pSet);
		COleVariant OldBookMark = m_pSet -> GetBookmark ();	

	//	Buchmarke einstellen
		try
		{
			m_pSet -> SetBookmark (m_varBookmark);	

		//	Scroll-Status setzen
			SetScrollValues ();	

		//	Show results of bookmark operation
			UpdateData (FALSE);	

		//	Überschrift akt.
			SetCaption ();
		}
		catch (CException *e)
		{
		//	Buchmarke löschen
			m_varBookmark.Clear ();

		//	Nachricht an Nutzer ausgeben
			CGakApp *pApp = (CGakApp *) AfxGetApp ();
			ASSERT (pApp != NULL);
			pApp -> OutputMessage (IDS_NO_DRECORD_FOUND);								

		//	alte Position einstellen
			m_pSet -> SetBookmark (OldBookMark);				

			e -> Delete ();
		}

	//	akt. Satz sperren 
		m_pSet -> LockReckord ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e1)
	{
		e1 -> ReportError ();
		e1 -> Delete ();
	}
}

//	akt. Satz löschbar
BOOL CDaoRecordViewExt::CanDeleteRecord (void)
{
	try
	{
		if (HasRecords () && 
			OnGetRecordset () -> CanUpdate ())					// Satz änderbar
			return TRUE;
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

	return FALSE;
}

//	aktuellen Satz löschen
void CDaoRecordViewExt::OnDeleteRekord ()
{
	ASSERT (m_pSet && m_pSet -> IsOpen ());
//	Transaktion bewirkt leeren des internen Puffers
	CDaoWorkspace *pWSpace = m_pSet -> m_pDatabase -> m_pWorkspace;
	ASSERT (pWSpace != NULL);

	try
	{
	//	Operation durchführbar ?
		if (!CanDeleteRecord ())			// Satz nicht löschbar ?
			return;

		CMutex mt;
		CWaitCursor wc;						// Sanduhr einschalten
//		CBoolSema Sema(m_bOnSearch);

	//	Transaktion beginnen
		pWSpace -> BeginTrans ();
		COutputLockError le (m_pSet);		// LockErrorMessage inst.

	//	akt. Satz löschen
		BOOL bLast = IsOnLastRecord ();		// wo stehen wir z.Z.
		BOOL bFirst = IsOnFirstRecord ();
		long lOldCnt = RecordCount ();

		m_pSet -> Delete ();				// wenn Satz nicht gelöscht werden konnte 
											// folgt Exception !
	//	jetzt auf den nächsten Satz gehen
		if (lOldCnt > 1)
		{
			if (bLast)				
			{			
				m_pSet -> MovePrev ();							// letzter Satz wurde gelöscht
				m_varBookmarkLast = m_pSet -> GetBookmark ();	// diese Buchmarke muß geändert werden
			}			
			else
				m_pSet -> MoveNext ();		

			m_varBookmarkCurrent = m_pSet -> GetBookmark ();	// akt. Buchmarke speichern

		//	ggf. Buchmarke First neu setzen
			if (bFirst)
				m_varBookmarkFirst = m_varBookmarkCurrent;	
		}
		else		// wenn letzte Datensatz gelöscht wurde
		{
			m_varBookmarkFirst.Clear ();		// alle Buchmarken sofort löschen
			m_varBookmarkLast.Clear ();
			m_varBookmarkCurrent.Clear ();			

		//	auch Scrollwerte setzen
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;

		}

		pWSpace -> CommitTrans ();			// Ende der Transaktion

	//	Satz ggf. verriegeln
		if (m_varBookmarkCurrent.vt != VT_EMPTY)
		{
		//	Scroll-Status setzen
			SetScrollValues ();

#ifdef _TRIAS_WITH_MENUBAR_
	
#endif //_TRIAS_WITH_MENUBAR_
			m_pSet -> LockReckord ();
		}
		else
			m_pSet -> LastRecordDeleted ();

	// Update RS
#pragma MSG("JG Seeken beim letzten RS")
		m_pSet->SearchNummer();

	//  Synchronisation 
		Sync();

	//	Show results of delete operation
		UpdateData (FALSE);

	//	Überschrift akt.
		SetCaption ();
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		pWSpace -> Rollback ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		pWSpace -> Rollback ();
	}
}

//	kann Schlüssel geändert werden ?
BOOL CDaoRecordViewExt::CanChangeKey (void)
{
	try
	{
		if (HasRecords () &&
			OnGetRecordset () -> CanUpdate ())					// Satz änderbar
			return TRUE;
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

	return FALSE;
}

//	Schlüssel ändern
void CDaoRecordViewExt::OnChangeKey ()
{
	if (!CanChangeKey ())
		return;

//	CBoolSema Sema(m_bOnSearch);
	ChangeKey ();
}

//	kann neuer Satz angehangen werden
BOOL CDaoRecordViewExt::CanAddNewRecord (void)
{
	if (OnGetRecordset () -> IsOpen ())
		return TRUE;

	return FALSE;	
}

void CDaoRecordViewExt::OnUpdateChangeKey(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanChangeKey ());
}

void CDaoRecordViewExt::OnUpdateDeleteRekord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanDeleteRecord ());
}

void CDaoRecordViewExt::OnUpdateGotoBookmark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanGotoBookmark ());		
}

void CDaoRecordViewExt::OnUpdateNewRekord(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanAddNewRecord ());		
}

void CDaoRecordViewExt::OnUpdateSetBookmark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI -> Enable (CanSetBookmark ());		
}

//	Scroll-Status setzen
void CDaoRecordViewExt::SetScrollValues (void)
{
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());

	try
	{
	//	wenn keine/oder nur 1 Datensatz im Set sind/ist
		if (RecordCount () <= 1)
		{
		//	nichts ist möglich			
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
			m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;

			if (m_pSet -> IsBOF () || m_pSet -> IsEOF ())	// keine Sätze im Set
			{
			//	alle Buchmarken löschen
				m_varBookmarkCurrent.Clear ();		
				m_varBookmarkFirst.Clear ();
				m_varBookmarkLast.Clear ();
			}
			else	// == 1
			{
			//	wenn außerhalb des Bereiches
				if (m_pSet -> IsBOF () || m_pSet -> IsEOF ())
					m_varBookmarkCurrent.Clear ();
				else
				{
				//	wir stehen genau auf dem einzig vorhandenen Satz
					m_varBookmarkCurrent = m_pSet -> GetBookmark ();
					m_varBookmarkFirst = m_varBookmarkCurrent;
					m_varBookmarkLast = m_varBookmarkCurrent;
				}
			}
			return;
		}

	//	wenn weder vor dem 1. noch nach dem letzten Satz
		if (!m_pSet -> IsBOF () && !m_pSet -> IsEOF ())
		{
		//	akt. Buchmarke speichern
			m_varBookmarkCurrent = m_pSet -> GetBookmark ();

		//	stehen wird auf dem 1. Satz ?
			if (m_varBookmarkCurrent == m_varBookmarkFirst)
			{
				m_varBookmarkFirst = m_varBookmarkCurrent; // Buchmarke speichern
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD; // kein zurück scrollen				
				m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;
				m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;						
			}
			else
			{
			//	stehen wird auf dem letzten Satz ?
				if (m_varBookmarkCurrent == m_varBookmarkLast)
				{
					m_varBookmarkLast = m_varBookmarkCurrent; // Buchmarke speichern
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
					m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
					m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
				}
				else
				//	wir befinden uns zwischen dem 1. und letzten Satz
				{	// alles ist möglich
					m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;
					m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;						
					m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
				}
			}
		}
		else
		{
		//	entweder vor dem 1. Satz oder hinter dem letzten Satz
			m_varBookmarkCurrent.Clear ();	// akt. Buchmarke in jedem Fall ungültig

		//	stehen wir vor dem 1. Satz ?
			if (m_pSet -> IsBOF ())
			{
				m_varBookmarkFirst.Clear ();				// Buchmarke löschen
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_BACKWARD;  // kein zurück scrollen						
				m_nStatus |= AFX_DAOVIEW_SCROLL_NEXT;
				m_nStatus |= AFX_DAOVIEW_SCROLL_LAST;						
			}						
			else											
			//	wir stehen hinter dem letzten Satz
			{
				m_varBookmarkLast.Clear ();					// Buchmarke löschen
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_NEXT;
				m_nStatus &= ~AFX_DAOVIEW_SCROLL_LAST;
				m_nStatus |= AFX_DAOVIEW_SCROLL_BACKWARD;
			}
		}
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

//	Erzeugernummer ändern
BOOL CDaoRecordViewExt::ChangeKey (BOOL bSelect /*FALSE*/)
{
	try
	{
		ASSERT ((m_pSet != NULL) && m_pSet -> IsOpen ());
		ASSERT_VALID (this);

		CChangeNummerDlg Dlg (m_pSet -> m_pDatabase, m_pSet -> m_Nummer, this, bSelect);
		if (Dlg.DoModal () != IDOK || Dlg.m_strNummer.IsEmpty ())
			return FALSE;

	//	Ist neue Nummer gleichen der alten ?
		if (m_pSet -> m_Nummer == Dlg.m_strNummer)
			return TRUE;

	//	akt. Satz entriegeln und speichern
		if (!m_pSet -> LockReckord (Store, this, Dlg.m_strNummer))		
			return FALSE;

	//	Überschrift akt.
		SetCaption ();

		return TRUE;
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

	return FALSE;
}

//	neuen Satz anhängen
void CDaoRecordViewExt::OnNewRekord ()
{
	if (!CanAddNewRecord ())
		return;

//	prüfe interne Parameter
	ASSERT ((m_pSet != NULL) && m_pSet -> IsOpen ());

	try
	{
//		CBoolSema Sema(m_bOnSearch);

	//	zuerst alten Datensatz entriegeln und speichern
		if (!m_pSet -> LockReckord (FALSE, this))
			return;

	//	neue Erzeugernummer durch Nutzer eingeben
		CChangeNummerDlg Dlg (m_pSet -> m_pDatabase);
		if (Dlg.DoModal () != IDOK || Dlg.m_strNummer.IsEmpty ())
			return;

	//	Branche durch Nutzer eingeben lassen
	//	Set öffnen
		CSelectSet Set (m_pSet -> m_pDatabase, ((CGakApp *)AfxGetApp ())->BranchenDefaultSQL());
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	//	neue Branchennummer vom Nutzer eingeben
		CSelNumberDlg BrDlg (this, &Set, ((CGakApp *)AfxGetApp ())->BranchenDefaultSQL(), IDS_BRANCHE_CAPTION);
		if (BrDlg.DoModal () != IDOK || BrDlg.m_strNumber.IsEmpty ())
			return;

	//	Set schließen
		if (Set.IsOpen ())
			Set.Close ();			

	//	Datensatz für 'AddNew' vorbereiten
		CWaitCursor wc;
		if (!m_pSet -> PrepareAddNew (Dlg.m_strNummer,SetBranchenNummer, 
								     (LPARAM)(const char *)BrDlg.m_strNumber))
			return;

	// JG Added for seeking new members
		m_pSet->SearchNummer();

		SetBookMarks ();			// auch anderen Buchmarken setzen

	//	Scroll-Status neu setzen	// da Satz dazugekommen
		SetScrollValues ();	

	//  Synchronisation der Ansichten
		Sync();

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

/*
BOOL CDaoRecordViewExt::Print(CDC* pDC, CPrintInfo* pInfo, const CString &strPage) 
{
//	TODO: Add your specialized code here and/or call the base class
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);
	ASSERT (!strPage.IsEmpty ());

	try
	{
	//	bilde Überschrift für Druck	
		COleDateTime OleDate (COleDateTime::GetCurrentTime());
		CString strDate (OleDate.Format ((UINT) IDS_DATETIME_FORMAT)), strCaption, strFrameCaption;

	//	lese Frame-Caption
		CFrameWnd* pFrame = GetParentFrame ();
		ASSERT (NULL != pFrame);
		ASSERT_VALID (pFrame);
		pFrame -> GetWindowText (strFrameCaption);

		AfxFormatString2 (strCaption, IDS_PAGE_HEADER, strFrameCaption, strDate);

	//	Header ausgeben
		if (!PrintPageHeader (pDC, pInfo, strCaption))
			return FALSE;

	//	Seite ausgeben
		int iy = pInfo -> m_rectDraw.top;			//	akt. y-Koordinate setzen
		CString strVal;								//	akt. Zeile	
		const char *pPage = strPage;				//  1. Zeichen der Seite
		char *pL = (char *) pPage;					//  letzte Zeichen der Zeile
		char *pF = (char *) pPage;					//	erste Zeichen der Zeile
		int iCnt = 0;								//	Anzahl Zeichen in akt. Zeile
		CString strLastText;						//	speichert letzten Textwert
		CSize Size;									//	letzte Textlänge
		while (pL && *pL)
		{
			if ((pL = strchr (pF, NeueZeile)))		// akt. Zeilenende suchen
			{
				iCnt = pL - pF;
				if (iCnt > 0)						// Text enthalten ?
				{
					strVal = strPage.Mid (pF - pPage, iCnt);

				//	letzte Zeile unterstreichen ?
					if (ZeileUnterStreichen == strVal [0])
					{
						if (strLastText.IsEmpty ())		// Formatfehler !
						{
							TRACE0 ("Fehler im Format des Erzeugerformulars !\n");
						}
						else
						{
						//	Zeile unterstreichen							
							Size = pDC -> GetTextExtent (strLastText);
							pDC -> MoveTo (0, iy);
							if (!pDC -> LineTo (Size.cx, iy))
								AfxThrowUserException ();					
							iy -= (m_iTextHoehe / 2);
						}
						strLastText.Empty ();		// letzter Text wird ungültig
					}
					else
					{
					//	"normale" Textausgabe
						if (! pDC -> TextOut (0, iy, strVal))
							AfxThrowUserException ();					
						strLastText = strVal;		// letzten Text speichern	
					}
				}							

			//	\nl
				iy += m_iTextHoehe;

			//	letzte Zeichen weiter setzen
				pL++;
				pF = pL;
			}
		}
		return TRUE;
	}
	catch (CUserException *ue)
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);

		pApp -> OutputMessage (IDS_CANNOT_PRINT);
		ue -> Delete ();
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

	return FALSE;
}
*/

//	Header für aktuelle Druckseite
/*
BOOL CDaoRecordViewExt::PrintPageHeader (CDC* pDC, CPrintInfo *pInfo, CString& strHeader)
{
//	prüfe Parameter
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);
	ASSERT (!strHeader.IsEmpty ());
	ASSERT (m_iTextHoehe > 0);

	try
	{		
	//	Text ausgeben
		if (!pDC -> TextOut (0, HeaderSpace, strHeader))
			AfxThrowUserException ();

	//	Text ganzseitig unterstreichen
		int iy = HeaderLineSpace + m_iTextHoehe;
		pDC -> MoveTo (0, iy);
		if (!pDC -> LineTo (pInfo -> m_rectDraw.right, iy))
			AfxThrowUserException ();

	//	restliche Zeichenfläche verleinern
		iy += HeaderSpace;
		pInfo -> m_rectDraw.top += iy;
		return TRUE;
	}
	catch (CUserException *ue)
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);

		pApp -> OutputMessage (IDS_CANNOT_PRINT);
		ue -> Delete ();
	}

	return FALSE;
}
*/

//	Caption des Frames setzen
void CDaoRecordViewExt::SetCaption ()
{
#pragma MSG("Überschrift aus Erzeugersatz")
	if (m_pSet -> IsValid())
		GetDocument () -> SetTitle (g_pErzSet->m_Nummer);
	else
		GetDocument () -> SetTitle (_T(""));
}	

//	hat zugeh. Set Records
BOOL CDaoRecordViewExt:: HasRecords (void)
{
	try
	{
		if (m_pSet && m_pSet -> IsOpen () &&
		   !m_pSet -> IsBOF () &&									// nicht vor dem 1. Satz
		   !m_pSet -> IsEOF () &&									// nicht hinter dem letzten Satz
		   (m_varBookmarkCurrent.vt != VT_EMPTY))	// und akt. Buchmarke gültig
		   return TRUE;
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

	return FALSE;
}

// ungef. Anzahl Datensätze lesen
long CDaoRecordViewExt:: RecordCount (void)
{
	if (!HasRecords ())		// wenn keine Sätze im Set
		return 0;

	if ((m_varBookmarkFirst.vt != VT_EMPTY) &&
		(m_varBookmarkLast.vt != VT_EMPTY) &&
	    (!(m_varBookmarkFirst == m_varBookmarkLast)))
		return 2;

	return 1;
}	

void CDaoRecordViewExt::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	ASSERT (NULL != pCmdUI);
	pCmdUI -> Enable (!HasRecords () || (m_pPrintJob && !m_pPrintJob -> IsJobFinished ()) ? FALSE : TRUE);	
}

void CDaoRecordViewExt::OnUpdateFilePrintPreview(CCmdUI* pCmdUI) 
{
	ASSERT (NULL != pCmdUI);
	pCmdUI -> Enable (!HasRecords () || (m_pPrintJob && !m_pPrintJob -> IsJobFinished ()) ? FALSE : TRUE);	
}

void CDaoRecordViewExt::OnUpdateLookNr(CCmdUI* pCmdUI) 
{
	pCmdUI -> Enable ((! ((CGakApp *) AfxGetApp ()) -> m_bResDlg) && HasRecords ());			
}

// alle Buchmarken neu setzen
void CDaoRecordViewExt::SetBookMarks (void)
{
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);

	m_pSet -> m_bOutputLockError = FALSE;		// LockInfo nicht ausgeben
	try
	{
		m_varBookmarkCurrent = m_pSet -> GetLastModifiedBookmark ();
		try 
		{
			m_pSet -> GetBookmark ();
		}
		catch (CException *ec)
		{
			ec -> Delete ();
			m_pSet -> SetBookmark (m_varBookmarkCurrent);
			m_varBookmarkFirst = m_varBookmarkLast = m_varBookmarkCurrent;	
			m_pSet -> m_bOutputLockError = TRUE;		// LockInfo wieder ausgeben
			return;
		}

		m_pSet -> MoveFirst ();
		m_varBookmarkFirst = m_pSet -> GetBookmark ();			
		m_pSet -> MoveLast ();
		m_varBookmarkLast = m_pSet -> GetBookmark ();			
		m_pSet -> SetBookmark (m_varBookmarkCurrent);
	}
	catch (CException *e)
	{
		e -> Delete ();		// nur auffangen
		m_varBookmarkFirst.Clear ();	
		m_varBookmarkLast.Clear ();
		m_varBookmarkCurrent.Clear ();			
	}

	m_pSet -> m_bOutputLockError = TRUE;		// LockInfo wieder ausgeben
}

CPropertySheet *CDaoRecordViewExt::GetSheet (void)
{
	ASSERT (NULL != m_pSheet);
	ASSERT_VALID (m_pSheet);

	return m_pSheet; 
}

void CDaoRecordViewExt::Print(CString &strReport, BOOL bToWindow)
{
	ASSERT (!strReport.IsEmpty ());

	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (NULL != pApp);
	ASSERT (NULL != m_pSet);
	ASSERT (m_pSet -> IsOpen ());

//	alten Job ggf. schließen
	if (m_pPrintJob)
		m_pPrintJob -> Close ();

//	akt. Satz speichern
	m_pSet -> LockReckord (Store, this);

	m_pPrintJob =  pApp -> Print (strReport, GetDocument () -> GetTitle (), m_pSet -> m_Nummer, bToWindow);
}


void CDaoRecordViewExt::OnAktbilanz() 
{
	// Zulässigkeitstest
	if (NULL == g_pErzSet)
		return;

	// nicht geöffneter RS
	if (!g_pErzSet->IsOpen())
		return;
	
	// leere RS
	if (g_pErzSet->IsBOF() && g_pErzSet->IsEOF())
		return;

	CDaoQueryDef Query(g_pErzSet->m_pDatabase);
	
	try 
	{
#pragma MSG("JG none global constant String(s)")

		// Querydef initialisieren
		Query.Open ("B_Abfallbilanz eines Erzeugers");

		// Parameter setzen	    prmErzeugernummer
		Query.SetParamValue(_T("prmErzeugernummer"), COleVariant(g_pErzSet->m_Nummer, VT_BSTRT));
		short bNurSonderAbf = false;
		//					   "prmNurSonderabfälle"	
		Query.SetParamValue(_T("prmNurSonderabfälle"), COleVariant(bNurSonderAbf, VT_I2));

		// RS initialiseren
		CDaoRecordset set(g_pErzSet->m_pDatabase);
		set.Open (&Query, dbOpenSnapshot);

		if (!set.IsBOF ())
		{
			CQueryResult ResDlg(NULL, &set, _T("B_Abfallbilanz eines Erzeugers"));
			ResDlg.DoModal ();
		}
		else
			AfxMessageBox("Keine Daten vorhanden", /*AfxGetAppName (),*/ MB_OK | MB_ICONINFORMATION);

		// MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONINFORMATION);
		set.Close ();

	}
	catch (CUserException *e)
	{
		e -> Delete ();		// hier Abbruch !
	}
	catch (CDaoException *e)
	{
		::DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	if (Query.IsOpen ())
		Query.Close ();
}

void CDaoRecordViewExt::Sync()
{
	// def. Impl. : no action
	// define your own Synchronisation
}
void CDaoRecordViewExt::OnAbgleichAkt() 
{
	if (NULL == g_pErzSet) 
		return;
	
	CGakApp* pApp = GetApp();
	if (NULL == pApp)
		return;

//	KK990714
	pApp->SetWindowStatus(FALSE);	// Erz+Abf-Fenster disable
	CGakSet *pErzSet = NULL;
	CAbfSet *pAbfSet = NULL;
	if ( g_pErzSet )
		pErzSet = g_pErzSet;

	if ( g_pAbfSet )
		pAbfSet = g_pAbfSet;
//--------------------KK990714

	CAbgleichParameter AbgleichParas(g_pErzSet->m_Nummer, "", pApp->GetAbfallTable(), pApp->GetErzTable(), true, true);

//	KK990714
	g_pAbfSet = NULL;
	g_pErzSet = NULL;
//----------------------
	GetApp()->DoAbgleich(TRUE, &AbgleichParas);

//	KK990714
	pApp->SetWindowStatus(TRUE);	// Erz+Abf-Fenster enable

	if ( pErzSet )
		g_pErzSet = pErzSet;

	if ( pAbfSet )
		g_pAbfSet = pAbfSet;
//--------------------KK990714

}

void CDaoRecordViewExt::OnAbgleich() 
{
	OnAbgleichAkt();
}

void CDaoRecordViewExt::OnAbgleichAktnew() 
{
	if (NULL == g_pErzSet) 
		return;

	CGakApp* pApp = GetApp();
	if (NULL == pApp)
		return;
//	KK990714
	pApp->SetWindowStatus(FALSE);	// Erz+Abf-Fenster disable
	CGakSet *pErzSet = NULL;
	CAbfSet *pAbfSet = NULL;
	if ( g_pErzSet )
		pErzSet = g_pErzSet;

	if ( g_pAbfSet )
		pAbfSet = g_pAbfSet;
//--------------------KK990714


	CAbgleichParameter AbgleichParas(g_pErzSet->m_Nummer, "", pApp->GetAbfallTable(), pApp->GetErzTable(), true, true);

//	KK990714
	g_pAbfSet = NULL;
	g_pErzSet = NULL;
//----------------------

	GetApp()->DoAbgleich(FALSE, &AbgleichParas);

//	KK990714
	pApp->SetWindowStatus(TRUE);	// Erz+Abf-Fenster enable

	if ( pErzSet )
		g_pErzSet = pErzSet;

	if ( pAbfSet )
		g_pAbfSet = pAbfSet;
//--------------------KK990714

}

void CDaoRecordViewExt::OnUpdateAbgleichAkt(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI)		// gültiger Parameter
		return;
	if ((NULL == g_pErzSet) || (!g_pErzSet->CanUpdate()))
		pCmdUI->Enable(false);
}

void CDaoRecordViewExt::OnUpdateAbgleichAktnew(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI)		// gültiger Parameter
		return;

	if ((NULL == g_pErzSet) || (!g_pErzSet->CanUpdate()))
		pCmdUI->Enable(false);
}

void CDaoRecordViewExt::OnUpdateAbgleich(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI)		// gültiger Parameter
		return;
	if ((NULL == g_pErzSet) || (!g_pErzSet->CanUpdate()))
		pCmdUI->Enable(false);
}


void CDaoRecordViewExt::OnUpdateAktbilanz(CCmdUI* pCmdUI) 
{
	if (NULL == pCmdUI)		// gültiger Parameter
		return;

	if ((NULL == g_pErzSet) /*|| (!g_pErzSet->CanUpdate())*/)
		pCmdUI->Enable(false);
}



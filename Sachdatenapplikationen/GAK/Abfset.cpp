// AbfSet.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGapApp 
#include "gaksete.h"		// CDaoRecordsetExt
#include "AbfSet.h"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Variablen
CAbfSet *g_pAbfSet = NULL;

#include "Gakset.h"
extern CGakSet * g_pErzSet;


bool CAbfSet::IsValid()
{
	// RS ungültig
	if (NULL == g_pAbfSet)
		return false;
	if (NULL == g_pErzSet)
		return false;

	// DS nicht synchron
	return (g_pAbfSet->m_Nummer == g_pErzSet->m_Nummer);
}



// CRecordInfo --------------------------------------------
CRecordInfo :: CRecordInfo (CString &strArt, /*CString& strEnts, */COleVariant varBookmark, 
							BOOL bFirst)
{
	m_strAbfArt = strArt;
	m_varBookMark = varBookmark;
	m_bFirst = bFirst;
}	

/*
CRecordInfo :: ~CRecordInfo ()
{
	TRACE1 ("Abfallart '%s' gelöscht.\n", m_strAbfArt);
}
*/

// CPtrListExt ---------------------------------------------
CPtrListExt :: ~CPtrListExt (void)
{
	RemoveAll ();
}

void CPtrListExt :: RemoveAll ()
{
	if (IsEmpty ())
		return;

	CRecordInfo *pInfo = NULL;
	POSITION pos = GetHeadPosition();
	while (pos != NULL)
	{
		pInfo = (CRecordInfo *) GetNext(pos);	// Destruktor wird ohne
		ASSERT (NULL != pInfo);					// cast nicht gerufen !
		DELETE_OBJ (pInfo);
	}

	CPtrList::RemoveAll ();
}

//	einzelnen Eintrag über seine Buchmarke löschen
BOOL CPtrListExt :: DeleteRecord (COleVariant &varBookmark)
{
	if ((VT_EMPTY == varBookmark.vt) || IsEmpty ())
		return FALSE;

	CRecordInfo *pInfo = NULL;
	POSITION pos = GetHeadPosition();
	POSITION DelPos;
	while (pos != NULL)
	{
		DelPos = pos;
		pInfo = (CRecordInfo *) GetNext(pos);	// Destruktor wird ohne
		ASSERT (NULL != pInfo);					// cast nicht gerufen !
		if (varBookmark == pInfo -> m_varBookMark)
		{
			DELETE_OBJ (pInfo);		// Objekt selbst löschen
			RemoveAt (DelPos);		// aus Liste
			return TRUE;
		}
	}

	return FALSE;
}

//	1. Satz über seine Buchmarke akt.
BOOL CPtrListExt :: SetFirstRecord (COleVariant varBookmark, const char *pAbfallArt/* = NULL*/)
{
	if ((VT_EMPTY == varBookmark.vt) || IsEmpty ())
		return FALSE;

	BOOL bFound = FALSE;
	POSITION pos = GetHeadPosition();
	CRecordInfo *pInfo = NULL;
	while (pos != NULL)
	{
		pInfo = (CRecordInfo *) GetNext(pos);
		ASSERT (NULL != pInfo);			
		if (!bFound && (varBookmark == pInfo -> m_varBookMark))
		{
			bFound = TRUE;
			pInfo -> m_bFirst = TRUE;
			
		//	ggf. Art ändern
			if (pAbfallArt && *pAbfallArt)
				pInfo -> m_strAbfArt = pAbfallArt;
		}
		else
			pInfo -> m_bFirst = FALSE;
	}

	return bFound;
}

BOOL CPtrListExt :: AddRecord (COleVariant varBookmark, const char *pAbfallArt, BOOL bFirst/* = TRUE*/)
{
	ASSERT (NULL != pAbfallArt && AfxIsValidString (pAbfallArt));
	ASSERT (*pAbfallArt);

	try
	{
		CString strArt (pAbfallArt);
		CRecordInfo *pInfo = new CRecordInfo (strArt, varBookmark);
		AddTail (pInfo);					

	//	ggf. als 1. Satz setzen
		if (bFirst)
			return SetFirstRecord (varBookmark);

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

/////////////////////////////////////////////////////////////////////////////
// CAbfSet
IMPLEMENT_DYNAMIC(CAbfSet, CDaoRecordsetExt)

CAbfSet :: CAbfSet(CDaoDatabase* pdb)
		 : CDaoRecordsetExt (IDS_ABFALL_INDEX,
						    ((CGakApp *) AfxGetApp ()) -> AbfallDefaultSQL (), pdb)
{
	//{{AFX_FIELD_INIT(CAbfSet)
	m_Abfallbezeichnung = _T("");
	m_Abfallnummer = _T("");
	m_Bemerkungen = _T("");
	m_Betreiberbemerkungen = _T("");
	m_Betreibernummer = _T("");
	m_Eigenentsorgung = FALSE;
	m_Entsorgerbemerkungen = _T("");
	m_Entsorgernummer = _T("");
	m_Entsorgungsfreistellung = FALSE;
	m_Entsorgungspartner = _T("");
	m_Entsorgungstelefax = _T("");
	m_Entsorgungstelefon = _T("");
	m_Entsorgungsverfahren = _T("");
	m_Freistellungsnummer = _T("");
	m_Menge_t = 0.0;
	m_Transporteurbemerkungen = _T("");
	m_Transporteurnummer = _T("");
	m_Verbringungscode = _T("");
	m_Vorbehandlung = _T("");
	m_Eigentransport = FALSE;
	m_EAKNummer = _T("");
	m_Nachweisnummer = _T("");
	m_Exportiert = _T("");
	//}}AFX_FIELD_INIT
	m_nFields += 23;
	m_nDefaultType = dbOpenTable;

	g_pAbfSet = this;
	m_bDeleteAll = TRUE;			// alle Sätze aus Liste löschen
}

CAbfSet :: ~CAbfSet ()
{
	g_pAbfSet = NULL;
}

void CAbfSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAbfSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Abfallbezeichnung]"), m_Abfallbezeichnung);
	DFX_Text(pFX, _T("[Abfallnummer]"), m_Abfallnummer);
	DFX_Text(pFX, _T("[Bemerkungen]"), m_Bemerkungen);
	DFX_Text(pFX, _T("[Betreiberbemerkungen]"), m_Betreiberbemerkungen);
	DFX_Text(pFX, _T("[Betreibernummer]"), m_Betreibernummer);
	DFX_Bool(pFX, _T("[Eigenentsorgung]"), m_Eigenentsorgung);
	DFX_Text(pFX, _T("[Entsorgerbemerkungen]"), m_Entsorgerbemerkungen);
	DFX_Text(pFX, _T("[Entsorgernummer]"), m_Entsorgernummer);
	DFX_Bool(pFX, _T("[Entsorgungsfreistellung]"), m_Entsorgungsfreistellung);
	DFX_Text(pFX, _T("[Entsorgungspartner]"), m_Entsorgungspartner);
	DFX_Text(pFX, _T("[Entsorgungstelefax]"), m_Entsorgungstelefax);
	DFX_Text(pFX, _T("[Entsorgungstelefon]"), m_Entsorgungstelefon);
	DFX_Text(pFX, _T("[Entsorgungsverfahren]"), m_Entsorgungsverfahren);
	DFX_Text(pFX, _T("[Freistellungsnummer]"), m_Freistellungsnummer);
	DFX_Double(pFX, _T("[Menge_t]"), m_Menge_t);
	DFX_Text(pFX, _T("[Transporteurbemerkungen]"), m_Transporteurbemerkungen);
	DFX_Text(pFX, _T("[Transporteurnummer]"), m_Transporteurnummer);
	DFX_Text(pFX, _T("[Verbringungscode]"), m_Verbringungscode);
	DFX_Text(pFX, _T("[Vorbehandlung]"), m_Vorbehandlung);
	DFX_Bool(pFX, _T("[Eigentransport]"), m_Eigentransport);
	DFX_Text(pFX, _T("[EAKNummer]"), m_EAKNummer);
	DFX_Text(pFX, _T("[Nachweisnummer]"), m_Nachweisnummer);
	DFX_Text(pFX, _T("[Exportiert]"), m_Exportiert);
	//}}AFX_FIELD_MAP

//	Basisklasse rufen
	CDaoRecordsetExt :: DoFieldExchange (pFX);
}

/////////////////////////////////////////////////////////////////////////////
// CAbfSet diagnostics
#ifdef _DEBUG
void CAbfSet::AssertValid() const
{
	CDaoRecordsetExt::AssertValid();
}

void CAbfSet::Dump(CDumpContext& dc) const
{
	CDaoRecordsetExt::Dump(dc);
}
#endif //_DEBUG

BOOL CAbfSet::CanUpdate(void)
{
	if (NULL == g_pErzSet) 
		return FALSE;
		
	return /*CDaoRecordsetExt::CanUpdate() &&*/ g_pErzSet->CanUpdate();
}

//	virtuelle Funktion
void CAbfSet::Move(long lRows)
{
	ASSERT_VALID(this);
	ASSERT(IsOpen());

	switch(lRows)
	{
		case AFX_DAO_NEXT:
			MoveExt(">", AFX_DAO_NEXT);
		break;
		case AFX_DAO_PREV:
			MoveExt ("<", AFX_DAO_PREV);
		break;
		case AFX_DAO_FIRST:
			 MoveExt ("=", AFX_DAO_FIRST);
		break;
		case AFX_DAO_LAST:
			MoveExt ("=", AFX_DAO_LAST);
		break;
	//	General case
		default:
	//	Call Move without getting Bookmark (using unitialized variant).
			CDaoRecordset :: Move (lRows);
	}
}

//	überlagerte MoveNext-Funktion
//	die Funktion geht davon aus, daß der Index "Nummer" gesetzt ist
BOOL CAbfSet::MoveExt (const char *pS, int iDir, const char *pErzNr /* = NULL */)
{
	ASSERT_VALID (this);
	ASSERT (IsOpen ());
	ASSERT (NULL != pS && AfxIsValidString (pS));
	ASSERT ((0 == strcmp (pS, ">")) || (0 == strcmp (pS, "<")) || (0 == strcmp (pS, "=")));
	ASSERT ((AFX_DAO_NEXT == iDir) || (AFX_DAO_PREV == iDir) ||
			(AFX_DAO_FIRST == iDir) || (AFX_DAO_LAST == iDir));

	COleVariant varOldErz;			// alter Erzeuger	
	BOOL bResOp = FALSE;			// noch nichts getan
	
	try
	{
		CMutex mt;					 // dieses Codestück thread sicher machen
		CWaitCursor wc;
		varOldErz = GetBookmark ();	 // Marke von altem Erzeuger

	//	zur nächsten Abfallgruppe	
		BOOL bFirstOp = FALSE;
		switch (iDir)
		{
			case AFX_DAO_NEXT:			
			case AFX_DAO_PREV:
			{
				// JG einfach den synchronen DS finden
				if (NULL == pErzNr && NULL != g_pErzSet)
					pErzNr = (g_pErzSet->m_Nummer);

				ASSERT ((NULL != pErzNr && *pErzNr) || !m_Nummer.IsEmpty ());
#pragma MSG("JG Clean up this")
// Das wäre die Version mit Abfrage
/*				// m_strFilter strFilter;
				m_strFilter = "[Nummer] = """;
				m_strFilter += 
				pErzNr && *pErzNr ? pErzNr : m_Nummer;
				m_strFilter += """";
				Requery();
*/
				COleVariant VarNr (pErzNr && *pErzNr ? pErzNr : m_Nummer, VT_BSTRT);
				bFirstOp = Seek (pS, &VarNr);
			}
			break;
			case AFX_DAO_FIRST:
			case AFX_DAO_LAST:
			{
				CDaoRecordset :: Move (iDir);
				if (AFX_DAO_FIRST == iDir)
					iDir = AFX_DAO_NEXT;
				else
					iDir = AFX_DAO_PREV;
				bFirstOp = TRUE;
			}
			break;
			default:
				ASSERT (FALSE);
		}

	//	1. Satz gefunden ?
		if (bFirstOp)			
		{
		//	Buchmarken sammeln	
			CRecordInfoList NewList;			// neue Liste anlegen
			CRecordInfo *pInfo = NULL;			// Zeiger int.
			CString strNummer (m_Nummer);
			do
			{
			//	Infos speichern
				CRecordInfo *pInfo = new CRecordInfo (m_Abfallnummer, GetBookmark ());
				NewList.AddTail (pInfo);					
				try
				{
					CDaoRecordset :: Move (iDir);
				}
				catch (CDaoException *e)
				{
					:: DisplayDaoException (e);
					e -> Delete ();
					break;
				}
				catch (CException *e)
				{
					e -> Delete ();
					break;
				}
			}					
			while ((m_Nummer == strNummer) && !IsEOF () && !IsBOF ());					

		//	ggf. Lockmeldung ausgeben
			OutputLockErrorMessage ();

		//	jetzt auf 1. Erzeuger gehen
			POSITION pos;
			if (AFX_DAO_NEXT == iDir)
				pInfo = NewList.GetHead ();				
			else
			{
			//	letzter Satz soll 1. werden					
				pos = NewList.FindIndex (NewList.GetCount () - 1);
				pInfo = NewList.GetAt (pos);
			}

			ASSERT (NULL != pInfo);
			SetBookmark (pInfo -> m_varBookMark);
			pInfo -> m_bFirst = TRUE;

		//	jetzt Liste umkopieren
			m_RecordInfoList.RemoveAll ();			// alte Liste zuvor löschen
			pos = NewList.GetHeadPosition ();
			while (NULL != pos)
				m_RecordInfoList.AddTail (NewList.GetNext (pos));					
			NewList.CPtrList::RemoveAll ();
			bResOp = TRUE;	
			// JG
#pragma MSG("m_bValid accessing function")
//			m_bValid = TRUE;
			// alles OK		
		}	// Seek failed
		else
		{
			// hier wird zu dem alten Satz gegangen
			SetBookmark (varOldErz);				// es wurde kein weiterer Erzeuger gefunden
		}
	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS(CDaoException)))
			::DisplayDaoException ((CDaoException*) e);
		else
			e -> ReportError ();
		if (varOldErz.vt != VT_EMPTY)
			SetBookmark (varOldErz);
		throw;										// Exception weiterleiten
	}
	
	return bResOp;		// Operationflag setzen							
}

// alle zum Erzeuger gehörenden Abfälle locken
int CAbfSet::LockReckord (BOOL bLock, CWnd *pWnd, const char *pNummer)
{
	int iRes = LockFailed;						// noch nichts getan
	COleVariant varOldPos;
	try 
	{
		CMutex mt;
		if (!m_bCanUpDate)					// war durch anderen Nutzer
			return NothingToLock;			// gesperrt

		if (m_RecordInfoList.IsEmpty ())
			return Locked;
		
		ASSERT (IsOpen ());

		CWaitCursor wc;	
	//	ak. Satz immer zuerst behandeln
		iRes = CDaoRecordsetExt :: LockReckord (bLock, pWnd, pNummer);
		if ((LockFailed == iRes) ||					// wenn Fehler beim Locken oder
			(bLock && (NothingToLock == iRes)))		// durch anderen Nutzer gesperrt
			return iRes;

		varOldPos = GetBookmark ();		// alte Pos. speichern
		CRecordInfo *pInfo = NULL;

	//	jetzt durch alle Sätze bewegen
		POSITION pos = m_RecordInfoList.GetHeadPosition ();
		while (NULL != pos)
		{
			pInfo = m_RecordInfoList.GetNext (pos);
			ASSERT (NULL != pInfo);
			if (pInfo -> m_varBookMark == varOldPos)	// diesen Satz nicht noch mal
				continue;

			SetBookmark (pInfo -> m_varBookMark);		// akt. Satz setzen
			iRes = CDaoRecordsetExt :: LockReckord (bLock, NULL, pNummer);
			if ((LockFailed == iRes) ||				// wenn Fehler beim Locken oder
				(bLock && (NothingToLock == iRes)))	// durch anderen Nutzer gesperrt
			break;
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
	if (varOldPos.vt != VT_EMPTY)
		SetBookmark (varOldPos);		// wieder auf alte Position
	 
	return iRes;	
}

//	1 oder alle Sätze der Liste löschen
//	Sätze sind gelockt !
void CAbfSet::Delete()
{
	ASSERT_VALID (this);
	ASSERT (IsOpen ());

//	wenn nur akt. Satz löschen
	if (!m_bDeleteAll)		
	{		
		CDaoRecordset::Delete ();
		return;
	}
	
	CString strOldNummer (m_Nummer);
	CRecordInfo *pInfo = NULL;
	POSITION pos = m_RecordInfoList.GetHeadPosition();
	while (pos != NULL)
	{
		pInfo = (CRecordInfo *) m_RecordInfoList.GetNext(pos);
		ASSERT (NULL != pInfo);					
		SetBookmark (pInfo -> m_varBookMark);	// auf Satz positionieren
		CDaoRecordset::Delete();				// Satz löschen
	}

	m_RecordInfoList.RemoveAll ();				// Liste wird geleert
	m_Nummer = strOldNummer;					// für Seek notwendig
}

BOOL CAbfSet::PrepareAddNew (const char *pNummer, PFPREPARE pf/*= NULL*/, LPARAM lp/*= 0*/)
{
	BOOL retval = CDaoRecordsetExt::PrepareAddNew (pNummer, pf, lp);	
	return retval;
}

BOOL CAbfSet::SearchNummer (const char *pNummer, BOOL bOutErrMsg /*=TRUE*/)
{
	// wenn der Erzset noch leer ist ist alles getan
	if (NULL == g_pErzSet)
		return TRUE;

//  JG den default Parameter handeln
	if (NULL == pNummer)
		pNummer = (g_pErzSet->m_Nummer);

	ASSERT (pNummer != NULL && AfxIsValidString (pNummer));
	BOOL bOk = FALSE;		// noch nichts getan

	try
	{

	//	Satz bereits geladen ?
//	das will ich ja gerade provozieren
//		if (!*pNummer || (m_Nummer == pNummer))
//			return TRUE;

		CMutex mt;
		CWaitCursor wc;
		COutputLockError le (this);

	//	akt. Satz entriegeln und speichern
		if (!LockReckord (FALSE))
			return FALSE;

	//	akt. Pos. merken
		COleVariant BookMark = GetBookmark ();

		bOutErrMsg = false;

	//	neue Nummer suchen
		if (MoveExt ("=", AFX_DAO_NEXT, pNummer))
		{
			bOk = TRUE;
		}
		else
		{
			if (bOutErrMsg)
			{
				CGakApp *pApp = (CGakApp *) AfxGetApp ();
				ASSERT (pApp != NULL);
				CString strInfo;
				AfxFormatString1 (strInfo, IDS_ABF_NOT_FOUND, pNummer);
				pApp -> OutputMessage (strInfo);	// Nachricht an Nutzer ausgeben
			}
			SetBookmark (BookMark);					// alten Satz einstell.
		}

	//	akt. Satz sperren 
		return LockReckord();
	}
	catch (CException *e)
	{
		// e -> ReportError ();		// bereits ausgegeben 
		e -> Delete ();
	}

	return bOk;
}

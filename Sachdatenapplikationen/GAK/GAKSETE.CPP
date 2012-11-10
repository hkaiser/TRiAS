// gakSete.cpp : implementation of the CDaoRecordsetExt class
//

#include "stdafx.h"
#include "gak.h"
#include "gakSete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "GakSet.h"
#include "AbfSet.h"
extern CGakSet * g_pErzSet;
extern CAbfSet * g_pAbfSet;

//	Kontstanten
const int iSystFieldCnt = 4;			// 4 Systemfelder ex.

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetExt implementation

IMPLEMENT_DYNAMIC(CDaoRecordsetExt, CDaoRecordset)

CDaoRecordsetExt::CDaoRecordsetExt(UINT uiPrimKey, const char *pDefaultSQL, CDaoDatabase* pdb)
				 :CDaoRecordset(pdb)
{
	ASSERT (pDefaultSQL != NULL && AfxIsValidString (pDefaultSQL));

	//{{AFX_FIELD_INIT(CDaoRecordsetExt)
	m_Nummer = _T("");
	m_user = _T("");
	m_ro = FALSE;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenTable;		// Typ festlegen
	m_pTableDef = NULL;					// Table-Def.

	m_bCanUpDate = FALSE;				// Satz nicht editierbar

	m_strDefaultSQL = pDefaultSQL;
	m_uiPrimKey = uiPrimKey;

	m_bOutputLockError = TRUE;			// Satz gelockt Meldung ausgeben

#pragma MSG("m_bValid accessing function")
//	m_bValid = FALSE;
}

CString CDaoRecordsetExt::GetDefaultDBName()
{	
//	lese default-DB-Namen
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	return pApp -> DatabaseName ();
}

void CDaoRecordsetExt::OutputLockErrorMessage (void)
{
//  JG no Locking message 
//	return;

	if (m_bOutputLockError && !m_bCanUpDate && !m_user.IsEmpty () && (m_ro != 0))
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (NULL != pApp);
		ASSERT_VALID (pApp);

		CString strInfo;
		AfxFormatString1 (strInfo, IDS_REC_USED, m_user);
		pApp -> OutputMessage (strInfo);
	}

	else
		// Page Locking
		if (GetEditMode() == dbEditInProgress)
		{
			CGakApp *pApp = (CGakApp *) AfxGetApp ();
			ASSERT (NULL != pApp);
			ASSERT_VALID (pApp);

			CString strInfo = ("Datenbankseite ist gesperrt");
//			AfxFormatString1 (strInfo, IDS_REC_USED, m_user);
			pApp -> OutputMessage (strInfo);
		}
}	

void CDaoRecordsetExt::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoRecordsetExt)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	DFX_DateTime(pFX, _T("[Erfassungsdatum]"), m_Erfassungsdatum);
	DFX_DateTime(pFX, _T("[Aenderungsdatum]"), m_Aenderungsdatum);
	DFX_Text(pFX, _T("[user]"), m_user);
	DFX_Bool(pFX, _T("[ro]"), m_ro);
	//}}AFX_FIELD_MAP

//	Satz-Sperr-Flag bilden
	if (pFX -> m_nOperation == CDaoFieldExchange :: DFX_Operation :: Fixup)
	{
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (NULL != pApp);
		ASSERT_VALID (pApp);

	//	Satz gesperrt ?
		m_bCanUpDate = TRUE;		
		if (m_ro)									// ja
		{
		//	durch anderen Nutzer ?
			if ((!m_user.IsEmpty ()) &&				// gültiger UserName ?
				 (m_user != pApp -> UserName ()) &&
				 (0 != strcmpi (pApp -> UserName (), "GAK")))
			{
				m_bCanUpDate = FALSE;				// durch anderen Nutzer

			//	ggf. Nutzer Informieren
				OutputLockErrorMessage ();
			}
		}
	}
}

CString CDaoRecordsetExt::GetDefaultSQL()
{
	return m_strDefaultSQL;
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetExt diagnostics

#ifdef _DEBUG
void CDaoRecordsetExt::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoRecordsetExt::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
	dc << "Erzeugernummer = " << m_Nummer;
	dc << "Nutzername = " << m_user;
	dc << "read/only = " << m_ro;
}
#endif //_DEBUG

BOOL CDaoRecordsetExt::CanUpdate(void)
{ 
	return m_bCanUpDate;
}


CDaoRecordsetExt::~CDaoRecordsetExt (void)
{
	if (IsOpen ())
		Close ();	
	
	if (m_pTableDef)
	{
		if (m_pTableDef -> IsOpen ())
			m_pTableDef -> Close ();
		DELETE_OBJ (m_pTableDef);
	}
}

//	überlagere Open-Funktion
void CDaoRecordsetExt :: Open (int nOpenType /*= AFX_DAO_USE_DEFAULT_TYPE*/, 
							   LPCTSTR /*lpszSQL = NULL*/, 
							   int nOptions /* = 0*/)
{
	try
	{
		AllocDatabase ();								// Database erzeugen

		CString strIndex;
		if (!strIndex.LoadString (m_uiPrimKey))
			AfxThrowResourceException ();

		m_pTableDef = new CDaoTableDef (m_pDatabase);
		m_pTableDef -> Open (GetDefaultSQL());

		m_bOutputLockError = FALSE;						// Meldung Satz gelockt nicht ausgeben
		CDaoRecordset :: Open (m_pTableDef);			// Set Öffnen
		SetCurrentIndex (strIndex);						// Index setzen
		SetLockingMode(false);							// optimistic locking
		m_bOutputLockError = TRUE;
		// LockReckord (TRUE);								// akt. Satz verriegeln
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		throw me;
	}
	catch (CDaoException *de)
	{
		//	de -> ReportError (); Fehlermeldung nicht doppelt ausgeben
		throw de;
	}
	catch (CResourceException *re)
	{
		re -> ReportError ();
		throw re;
	}

	// JG ist der Zugriff zulässig?
	#pragma MSG("m_bValid accessing function")
//	m_bValid = !(IsEOF() && IsBOF());
}
	
//	aktuellen Satz verriegeln/entriegeln
int CDaoRecordsetExt::LockReckord (int iLock, CWnd *pWnd, const char *pNummer)
{
	CDaoWorkspace *pWSpace = m_pDatabase -> m_pWorkspace;
	try
	{
		CMutex mt;
		if (!CanUpdate()	/*m_bCanUpDate*/	)					// war durch anderen Nutzer
			return NothingToLock;			// gesperrt

	//	Transaktion bewirkt leeren des internen Puffers
		ASSERT (pWSpace != NULL);
		SetLockingMode(false);							// optimistic locking
		pWSpace -> BeginTrans ();

//	KK990713
		AllocCache();	// MarkForEdit-LockedReckord benötigt Cache ( CMapPtrToPtr)

	//	ggf. Änderungsstatus bestimmen
		BOOL bDirty = FALSE;
		if ((FALSE == iLock) || (Store == iLock))
		{
			if (pWnd)
				pWnd -> UpdateData ();			// akt. Dialog-Infos lesen

		//	ggf. Erzeugernummer ändern
			if (pNummer && *pNummer && (m_Nummer != pNummer))
			{
				bDirty = TRUE;
				m_Nummer = pNummer;
			}

			if (!bDirty)
			{
				MarkForEdit();
				bDirty = FieldsChanged ();
			}
		}		

		Edit();
		switch (iLock)
		{
			case TRUE:								// Satz verriegeln
			{
				m_ro = TRUE;
				CGakApp *pApp = (CGakApp *) AfxGetApp ();
				ASSERT (pApp != NULL);
				m_user = pApp -> UserName ();		// Nutzernamen setzen
			}
			break;
			case FALSE:								// Satz entriegeln
				m_ro = FALSE;
			case Store:								// Satz speichern
			{
				SetFieldDirty (NULL, TRUE);			// alle Felder wurden geändert

			//  ggf. Änderungsdatum akt.
				if (bDirty)
					m_Aenderungsdatum = COleDateTime::GetCurrentTime();
			}
			break;
			default:
				ASSERT (FALSE);
		}
		Update();						
		pWSpace -> CommitTrans ();		// Daten in DB speichern

	//	ggf. Cache-Puffer anlegen
		if (TRUE == iLock)
		{
		//	Save fields for restore/dirty checking later
			AllocCache();
			StoreFields();
			SetFieldDirty (NULL, FALSE);
		}			

		return Locked;
	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS(CDaoException)))
			::DisplayDaoException ((CDaoException *) e);
		else
			e -> ReportError ();
		e -> Delete ();
		pWSpace -> Rollback ();

		m_bCanUpDate = FALSE;			// diesen Satz nicht mehr ändern !
		if (pWnd && pWnd -> IsWindowVisible ())
			pWnd -> UpdateData ();	
	}

	return LockFailed;		
}

//	überlagerte AddNew-Funktion
BOOL CDaoRecordsetExt :: PrepareAddNew (const char *pNummer, 
										PFPREPARE pFunction/* = NULL*/, LPARAM lParam/* = 0*/)
{
//	prüfe Parameter
	ASSERT (pNummer != NULL && AfxIsValidString (pNummer));
	if (!*pNummer)
		return FALSE;

	ASSERT (IsOpen ());

	CDaoWorkspace *pWSpace = m_pDatabase -> m_pWorkspace;
	ASSERT (pWSpace != NULL);
	try
	{
		pWSpace -> BeginTrans ();		
		CDaoRecordset :: AddNew ();				// Basis-Funktion rufen
		m_Erfassungsdatum = COleDateTime::GetCurrentTime(); // Erfassungsdatum 
		m_Nummer = pNummer;						// ErzNummer speichern
		m_ro = TRUE;							// eigene Sperrung setzen
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		m_user = pApp -> UserName ();			// Nutzernamen setzen

	//	ggf. nutzerspezifische Init. machen
		if (pFunction && lParam)
			pFunction (lParam);

		Update();
		pWSpace -> CommitTrans ();				// Daten in DB speichern
		m_bCanUpDate = TRUE;					// kann geändert werden

		return TRUE;
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

	return FALSE;
}	

//	überlagerte Delete-Funktion
void CDaoRecordsetExt :: Delete ()
{
	ASSERT (IsOpen ());

	try
	{
		CDaoRecordset :: Delete ();
		if (IsBOF () || IsEOF ())		// keine Sätze im Set !!
			m_bCanUpDate = FALSE;
	}
	catch (CException *e)
	{
		throw e;
	}
}	

//	Hier nur die Zeichen "[]" filtern
void CDaoRecordsetExt::SetFieldValue(LPCTSTR szName, const COleVariant& varValue)
{
	CString strName (szName);
	int iFirst = strName.Find ('['); 
	int iLast = strName.Find (']');
	if ((++iFirst > 0) && (iLast > 1))
		strName = strName.Mid (iFirst, iLast - iFirst);	
	
	CDaoRecordset::SetFieldValue (strName, varValue);
}

//	Info, das letzte Datensatz gelöscht wurde
void CDaoRecordsetExt :: LastRecordDeleted (void)
{
	m_bCanUpDate = FALSE;
	m_Nummer.Empty ();
}

//	wurde der Inhalt eines der Felder geändert (ohne Systemfelder)
BOOL CDaoRecordsetExt :: FieldsChanged (void)
{
	BOOL bDirty = FALSE;
	int nIndex = 0;
	int nIndexEnd = m_nFields - 1 - iSystFieldCnt;

	while (nIndex <= nIndexEnd && !bDirty)
		bDirty = IsFieldStatusDirty (nIndex++);
	
	return bDirty;
}

BOOL CDaoRecordsetExt::SearchNummer(const char *, BOOL )
{
	return TRUE;
}

bool CDaoRecordsetExt::IsValid()
{
	return true ;
	// RS ungültig
	if (NULL == g_pAbfSet)
		return false;
	if (NULL == g_pErzSet)
		return false;

	// DS nicht synchron
	return (g_pAbfSet->m_Nummer == g_pErzSet->m_Nummer);
}


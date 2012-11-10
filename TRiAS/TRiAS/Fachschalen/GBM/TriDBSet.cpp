// TriDBSet.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "TriDBSet.h"
#include "SetOI.h"
#include "SetSI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// _DEBUG,WIN32,_WINDOWS,__XT,__MFC__,__DEXPROCS,_WINDLL,_AFXDLL,_MBCS,EBWIN32,_SECDLL
// NDEBUG,WIN32,_WINDOWS,__XT,__MFC__,__DEXPROCS,_WINDLL,_AFXDLL,_MBCS,EBWIN32,_SECDLL

extern CStrasseSet* g_pSetStrasse;
extern COrteSet* g_pSetOrte;
extern int g_iMessageStatus;


/////////////////////////////////////////////////////////////////////////////
// CTriDBSet

IMPLEMENT_DYNAMIC(CTriDBSet, CRecordset)

CTriDBSet::CTriDBSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTriDBSet)
	m_NFPG1_IDE = _T("");
	m_TRIDB_NR = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_bInitialisiert = FALSE;
}


CString CTriDBSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CTriDBSet::GetDefaultSQL()
{
	return _T("[TRIDB]");
}

void CTriDBSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTriDBSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFPG1_IDE]"), m_NFPG1_IDE);
	RFX_Text(pFX, _T("[TRIDB_NR]"), m_TRIDB_NR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTriDBSet diagnostics

#ifdef _DEBUG
void CTriDBSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTriDBSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CTriDBSet::InitListen( BOOL overwrite )
{
	CSetOrtIndex	*pSOI;
	CSetStrIndex	*pSSI;
	CString			text, key, message;
	BOOL			bOpened = FALSE;
	BOOL			result = TRUE;

	if ( !m_bInitialisiert )
	{
		m_bInitialisiert = TRUE;

		if ( g_iMessageStatus >= 3 )
		{
			message = "Lesen OrtIndex";
			DEX_SetMessageString((const char*)message );
		}

		pSOI = new CSetOrtIndex( m_pDatabase );
		if ( pSOI )
		{
			m_mapOrte.RemoveAll();

			pSOI -> Open();
			while ( !pSOI -> IsEOF())
			{
				key = pSOI -> m_SCHL;
				text = pSOI -> m_LISTE;
				if ( !key.IsEmpty() && !text.IsEmpty())	m_mapOrte.SetAt( key, text );
				pSOI -> MoveNext();
			}
			pSOI -> Close();
			delete pSOI;
			pSOI = NULL;
		}

		if ( g_iMessageStatus >= 3 )
		{
			message = "Lesen StrIndex";
			DEX_SetMessageString((const char*)message );
		}

		pSSI = new CSetStrIndex( m_pDatabase );
		if ( pSSI )
		{
			m_mapStrassen.RemoveAll();

			pSSI -> Open();
			while ( !pSSI -> IsEOF())
			{
				key = pSSI -> m_SCHL;
				text = pSSI -> m_LISTE;
				if ( !key.IsEmpty() && !text.IsEmpty())	m_mapStrassen.SetAt( key, text );
				pSSI -> MoveNext();
			}
			pSSI -> Close();
			delete pSSI;
			pSSI = NULL;
		}

		if ( g_iMessageStatus >= 3 )
		{
			message = "Lesen TriDB";
			DEX_SetMessageString((const char*)message );
		}

		if ( !IsOpen())
		{
			Open();
			bOpened = TRUE;
		}
		else
			Requery();

		while ( !IsEOF())
		{
			key = m_NFPG1_IDE.Left( 5 );
			if ( m_mapStrassen.Lookup( key, text ))
			{
				if ( g_iMessageStatus >= 3 )
				{
					message  = "Lesen IDE + Strasse: ";
					message += key;
					message += " ==> ";
					message += text;
					DEX_SetMessageString((const char*)message );
				}

				if ( text.Find( ';' ) >= 0 )
					m_mapIDE.SetAt( m_NFPG1_IDE, m_TRIDB_NR );
			}
			MoveNext();
		}

		if ( bOpened )
			Close();
	}

	if ( g_iMessageStatus >= 3 )
	{
		message = "RewriteIndex";
		DEX_SetMessageString((const char*)message );
	}

	if (( m_mapStrassen.GetCount() == 0 ) || ( m_mapOrte.GetCount() == 0 ))
		RewriteIndex();

	message.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)message );

	return result;
}

void CTriDBSet::RegisterGS( const char* ide, const char* nr )
{
	CString		strIDE, strNr;
	CString		key, text;
	BOOL		setzen;
	ASSERT( AfxIsValidString( ide ));
	ASSERT( AfxIsValidString( nr ));

	strIDE = ide;
	strNr = nr;
	ASSERT( !strIDE.IsEmpty());
	ASSERT( !strNr.IsEmpty());
	if (( strIDE.GetLength() < 2 ) ||
		( strNr.IsEmpty()))
		return;

	strNr.TrimLeft();	strNr.TrimRight();
	while ( strNr.GetLength() < 3 )
	{
		text = strNr;
		strNr = "0";
		strNr += text;
	}
	if ( strIDE.GetLength() >= 5 )
	{
		key = strIDE.Left( 5 );
		setzen = FALSE;
		if ( !m_mapStrassen.Lookup( key, text ))
		{
			setzen = TRUE;
			text = strNr;
		}
		if ( text.Find( strNr ) < 0 )
		{
			text += ";";
			text += strNr;
			setzen = TRUE;
		}
		if ( setzen )
			m_mapStrassen.SetAt( key, text );
	}
	if ( strIDE.GetLength() >= 2 )
	{
		key = strIDE.Left( 2 );
		setzen = FALSE;
		if ( !m_mapOrte.Lookup( key, text ))
		{
			setzen = TRUE;
			text = strNr;
		}
		if ( text.Find( strNr ) < 0 )
		{
			text += ";";
			text += strNr;
			setzen = TRUE;
		}
		if ( setzen )
			m_mapOrte.SetAt( key, text );
	}
}

BOOL CTriDBSet::GetProjekte( const char* ide, CString& nr )
{
	BOOL	result = FALSE;
	CString	strIDE;
	CString	key, text;

	ASSERT( AfxIsValidString( ide ));
	strIDE = ide;

	nr.Empty();
	if ( strIDE.GetLength() < 2 )	return result;
	if ( strIDE.GetLength() == 10 )
	{
		if ( m_mapIDE.Lookup( strIDE, text ))
		{
			result = TRUE;
			nr = text;
			return result;
		}
	}

	if ( strIDE.GetLength() >= 5 )
	{
		key = strIDE.Left( 5 );
		if ( m_mapStrassen.Lookup( key, text ))
		{
			result = TRUE;
			nr = text;
		}
		return result;
	}

	key = strIDE.Left( 2 );
	if ( m_mapOrte.Lookup( key, text ))
	{
		result = TRUE;
		nr = text;
	}
	return result;
}

short CTriDBSet::FindOISY( short iTriDBNr )
{
	short		result = -1;
	CString		key, liste, nr, rest;
	POSITION	pos;

	for ( pos = m_mapOrte.GetStartPosition(); pos != NULL; )
	{
		m_mapOrte.GetNextAssoc( pos, key, liste );
		rest = liste;
		while ( rest.GetLength() > 0 )
		{
			nr = rest.Left( 3 );
			if ( rest.GetLength() > 4 )	rest = rest.Mid( 4 );
			else						rest.Empty();
			if ( atoi( nr ) == iTriDBNr )
			{
				result = String2OISY( key );
				break;
			}
		}
	}
	if ( g_iMessageStatus >= 4 )
	{
		if ( result >= 0 )	AfxMessageBox( "OISY gefunden!" );
		else				AfxMessageBox( "OISY nicht gefunden!" );
	}

	return result;
}

BOOL CTriDBSet::RewriteIndex()
{
	CSetOrtIndex	*pSOI;
	CSetStrIndex	*pSSI;
	POSITION		pos;
	CString		text1, text, key;
	BOOL		result = TRUE;
	short		i;

	if ( !IsOpen())		Open();
	result = IsOpen();

	if ( result )
	{
//		AfxGetMainWnd() -> BeginWaitCursor();

		if ( g_iMessageStatus >= 1 )
			DEX_SetMessageString( "Einlesen der Grundstücke" );
		text1 = "Lese Grundstück: ";

		m_mapOrte.RemoveAll();
		m_mapStrassen.RemoveAll();
		MoveFirst();
		i = 0;
		while ( !IsEOF())
		{
			if ( g_iMessageStatus >= 3 )
				if ( i++ == 10 )
			{
				text = text1;
				text += m_NFPG1_IDE;
				DEX_SetMessageString((const char*)text );
				i = 0;
			}
			RegisterGS( m_NFPG1_IDE, m_TRIDB_NR );
			MoveNext();
		}
		Close();
		DEX_SetMessageString( NULL );
//		AfxGetMainWnd() -> EndWaitCursor();
		m_bInitialisiert = TRUE;

		pSOI = new CSetOrtIndex( m_pDatabase );
		if ( pSOI )
		{
			pSOI -> Open();
			while ( !pSOI -> IsEOF())
			{
				pSOI -> Delete();
				pSOI -> MoveNext();
			}
			for ( pos = m_mapOrte.GetStartPosition(); pos != NULL; )
			{
				m_mapOrte.GetNextAssoc( pos, key, text );
				if ( !key.IsEmpty() && !text.IsEmpty())
				{
					pSOI -> AddNew();
					pSOI -> m_SCHL = key;
					pSOI -> m_LISTE = text;
					pSOI -> Update();
				}
			}
			pSOI -> Close();
			delete pSOI;
			pSOI = NULL;
		}

		pSSI = new CSetStrIndex( m_pDatabase );
		if ( pSSI )
		{
			pSSI -> Open();
			while ( !pSSI -> IsEOF())
			{
				pSSI -> Delete();
				pSSI -> MoveNext();
			}
			for ( pos = m_mapStrassen.GetStartPosition(); pos != NULL; )
			{
				m_mapStrassen.GetNextAssoc( pos, key, text );
				if ( !key.IsEmpty() && !text.IsEmpty())
				{
					pSSI -> AddNew();
					pSSI -> m_SCHL = key;
					pSSI -> m_LISTE = text;
					pSSI -> Update();
				}
			}
			pSSI -> Close();
			delete pSSI;
			pSSI = NULL;
		}
	}

	return result;
}

BOOL CTriDBSet::Ortslage( const char* ide, CString& ort, CString& str )
{
	BOOL	result = FALSE;
	CString	strIDE, key;

	ASSERT( AfxIsValidString( ide ));
	strIDE = ide;

	ort.Empty();
	str.Empty();
	if ( strIDE.GetLength() < 2 )	return result;
	if ( strIDE.GetLength() >= 5 )
	{
		key = strIDE.Left( 5 );
		str = g_pSetStrasse -> Strasse( key );
		if ( !str.IsEmpty())	result = TRUE;
	}

	if ( strIDE.GetLength() >= 2 )
	{
		key = strIDE.Left( 2 );
		ort = g_pSetOrte -> Ort( key );
		if ( result )
			if ( !ort.IsEmpty())	result = TRUE;
			else					result = FALSE;
	}
	return result;
}

int CTriDBSet::GetProjectNr( const char* ide )
{
	int			result = 0;
	BOOL		bOpened = FALSE;
	CxString	text, filter, old;

	if ( GetProjekte( ide, text ))
	{
		if ( text.Find( ';' ) < 0 )
			result = text.Short();
		else
		{
			filter = "( NFPG1_IDE = '";
			filter += ide;
			filter += "')";
			old = m_strFilter;
			m_strFilter = filter;
			bOpened = !IsOpen();
			if ( bOpened )	Open();
			else			Requery();

			if ( !IsEOF())
			{
				text = m_TRIDB_NR;
				result = text.Short();
			}

			m_strFilter = old;
			if ( bOpened )	Close();
			else			Requery();
		}
	}

	return result;
}

BOOL CTriDBSet::ModIDE( const char* alt, const char* neu, int tridbnr )
{
	CxString	text, init, oldFilter;
	BOOL		result = FALSE;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( alt ));
	ASSERT( AfxIsValidString( neu ));
	init = neu;
	if ( init.GetLength() > 2 )
		init = init.Left( 2 );

	InitListen( FALSE );

	oldFilter = m_strFilter;
	m_strFilter = "( NFPG1_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	if ( IsEOF())
	{
		init = "";
		init.AppendF( tridbnr, -1 );
		AddNew();
		m_NFPG1_IDE = neu;
		m_TRIDB_NR = init;
		Update();
	}
	else
		while ( !IsEOF())
		{
			Edit();
			m_NFPG1_IDE = neu;
			Update();

			MoveNext();
		}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

	m_bInitialisiert = FALSE;
	InitListen( TRUE );

	return TRUE;
}

void CTriDBSet::AddIDE( const char* ide, int v )
{
	CString		text, init, oldFilter;
	BOOL		result = FALSE;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( ide ));

	if ( opened = !IsOpen())	Open();
	else						Requery();

	AddNew();
	m_NFPG1_IDE = ide;
	m_TRIDB_NR  = v;
	Update();

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

	m_bInitialisiert = FALSE;
	InitListen( TRUE );
}

// VerzSet.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "VerzSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CVerzSet

IMPLEMENT_DYNAMIC(CVerzSet, CRecordset)

CVerzSet::CVerzSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerzSet)
	m_TRIDB_NR = _T("");
	m_TRIDB_VZ = _T("");
	m_TRIDB_BZ = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CVerzSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CVerzSet::GetDefaultSQL()
{
	return _T("[VERZ]");
}

void CVerzSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CVerzSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TRIDB_NR]"), m_TRIDB_NR);
	RFX_Text(pFX, _T("[TRIDB_VZ]"), m_TRIDB_VZ);
	RFX_Text(pFX, _T("[TRIDB_BZ]"), m_TRIDB_BZ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerzSet diagnostics

#ifdef _DEBUG
void CVerzSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerzSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

short CVerzSet::IstProjektIntegriert( const char *name )
{
	short		result = -1;
	BOOL		opened = FALSE;
	CString		test;
	CxString	nr;

	ASSERT( AfxIsValidString( name ));
	test = name;
	ASSERT( test.GetLength() > 0 );
	test.MakeUpper();

	if ( !IsOpen())
	{
		Open();
		opened = TRUE;
	}
	else
		Requery();

	MoveFirst();
	while ( !IsEOF() && ( result < 0 ))
	{
		m_TRIDB_VZ.MakeUpper();
		nr = m_TRIDB_NR;
		if ( m_TRIDB_VZ == test )	result = (short)nr.Short();
		else						MoveNext();
	}

	if ( opened )	Close();

	if ( g_iMessageStatus >= 4 )
	{
		CString	msg;

		msg = "IstProjekt '";
		msg += test;
		msg += "' integriert: ";
		if ( result >= 0 )	msg += "Ja";
		else				msg += "Nein";

		AfxMessageBox( msg );
	}

	return result;
}

BOOL CVerzSet::InitListen( BOOL )
{
	BOOL		opened = FALSE;
	CxString	nr;

	if ( !IsOpen())
	{
		Open();
		opened = TRUE;
	}
	else
		Requery();

	m_arrVerz.RemoveAll();
	MoveFirst();
	while ( !IsEOF())
	{
		m_TRIDB_VZ.MakeUpper();
		nr = m_TRIDB_NR;
		m_arrVerz.SetAtGrow( nr.Short(), m_TRIDB_VZ );
		MoveNext();
	}

	if ( opened )	Close();

	return TRUE;
}

CString CVerzSet::GetProjectName( int id )
{
	CString	result;

	if (( id >= 0 ) && ( id < m_arrVerz.GetSize()))
		result = m_arrVerz[id];

	return result;
}

int CVerzSet::RegisterProjekt( const char* name, const char* pfad )
{
	int			result = 0;
	int			nr, maxnr;
	BOOL		opened = FALSE;
	CxString	text;

	ASSERT( AfxIsValidString( name ));
	ASSERT( AfxIsValidString( pfad ));

	if ( !IsOpen())
	{
		Open();
		opened = TRUE;
	}
	else
		Requery();

	nr = maxnr = 0;
	MoveFirst();
	while ( !IsEOF())
	{
		m_TRIDB_VZ.MakeUpper();
		text = m_TRIDB_NR;
		nr = text.Short();
		if ( nr > maxnr )	maxnr = nr;
		MoveNext();
	}
	maxnr++;
	text.Empty();
	text.AppendF( maxnr, -1 );
	AddNew();
	m_TRIDB_BZ = name;
	m_TRIDB_VZ = pfad;
	m_TRIDB_NR = text;
	Update();

	if ( opened )	Close();
	else			Requery();

	result = maxnr;
	return result;
}

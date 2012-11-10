// nf_pg3.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"

#include "CulcuDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern CSetNF_PG1* g_pNF_PG1;
extern CSetNF_PG2H* g_pNF_PG2H;
extern CSetNF_PG2D* g_pNF_PG2D;
extern CSetNF_PG1GB* g_pNF_PG1GB;

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG3

IMPLEMENT_DYNAMIC(CSetNF_PG3, CRecordset)

CSetNF_PG3::CSetNF_PG3(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG3)
	m_NFP3_IDE = _T("");
	m_NFP3_AWE = 0;
	m_NFP3_AEW = 0;
	m_NFP3_GW = 0;
	m_NFP3_MOB = _T("");
	m_NFP3_SAM = _T("");
	m_NFP3_SAG = 0;
	m_NFP3_SAT = _T("");
	m_NFP3_KK = _T("");
	m_NFP3_KKG = 0;
	m_NFP3_KKT = _T("");
	m_NFP3_KKV = _T("");
	m_NFP3_KKK = _T("");
	m_NFP3_FV = 0;
	m_NFP3_BEM = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_strSort = "NFP3_IDE";
}

CSetNF_PG3::~CSetNF_PG3()
{
	if ( IsOpen())		Close();
}

BOOL CSetNF_PG3::Open( UINT nOpenType, LPCTSTR lpszSQL, DWORD dwOptions )
{
	BOOL	result = FALSE;

	m_strSort = "NFP3_IDE";
	try {

		result = CRecordset::Open( nOpenType, lpszSQL, dwOptions );

	} catch ( CDBException *e ) {

		AfxMessageBox( e -> m_strError );

	} catch ( CMemoryException *e) {

		AfxMessageBox( g_cbMemoryException );
		e -> Delete();

	} catch (...) {

		AfxMessageBox( g_cbUnhandeledException );
	}

	return result;
}

CString CSetNF_PG3::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG3::GetDefaultSQL()
{
	return _T("[NF_PG3]");
}

void CSetNF_PG3::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG3)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "NFP3_IDE", m_NFP3_IDE);
	RFX_Double(pFX, "NFP3_AWE", m_NFP3_AWE);
	RFX_Double(pFX, "NFP3_AEW", m_NFP3_AEW);
	RFX_Double(pFX, "NFP3_GW", m_NFP3_GW);
	RFX_Text(pFX, "NFP3_MOB", m_NFP3_MOB);
	RFX_Text(pFX, "NFP3_SAM", m_NFP3_SAM);
	RFX_Double(pFX, "NFP3_SAG", m_NFP3_SAG);
	RFX_Text(pFX, "NFP3_SAT", m_NFP3_SAT);
	RFX_Text(pFX, "NFP3_KK", m_NFP3_KK);
	RFX_Double(pFX, "NFP3_KKG", m_NFP3_KKG);
	RFX_Text(pFX, "NFP3_KKT", m_NFP3_KKT);
	RFX_Text(pFX, "NFP3_KKV", m_NFP3_KKV);
	RFX_Text(pFX, "NFP3_KKK", m_NFP3_KKK);
	RFX_Double(pFX, "NFP3_FV", m_NFP3_FV);
	RFX_Text(pFX, "NFP3_BEM", m_NFP3_BEM);
	//}}AFX_FIELD_MAP
}

void CSetNF_PG3::InitListen( const char* id )
{
	CString		filter, ide;

	if ( AfxIsValidString( id ))
	{
		ide = id;
		if ( ide.GetLength() > 3 )
			ide = ide.Left( 3 );
		if ( !ide.IsEmpty())
		{
			filter  = "(NFP3_IDE = '";
			filter += ide;
			filter += "')";
		}
		if ( !( filter == m_strFilter ))
			m_strFilter = filter;
	}

	if ( !IsOpen())		Open();
	else				Requery();

	m_mapMOB.RemoveAll();
	while ( !IsEOF())
	{
		if ( !m_NFP3_IDE.IsEmpty())
			if ( TestYES( m_NFP3_MOB ))
				m_mapMOB.SetAt( m_NFP3_IDE, (void*)1 );
		MoveNext();
	}
}	// InitListen

BOOL CSetNF_PG3::IstMOB( const char* id )
{
	BOOL	result = FALSE;
	void	*ptr = NULL;

	if ( AfxIsValidString( id ))
		if ( *id == '\0' )
		result = m_mapMOB.Lookup( id, ptr );

//	result = ( ptr == (void*)1 );
	return result;
}	// IstMOB

CDetailSatz *CSetNF_PG3::FindIDE( const char* id )
{
	CDetailSatz	*result;

	result = new CDetailSatz;
	if ( result )
	{
		result -> IDE().Empty();
		if ( Find( id ))
		{
			result -> IDE()    = m_NFP3_IDE;
//			result -> AWE()    = m_NFP3_AWE;		
//			if ( !IsFieldNull( &m_NFP3_AWE ))	result -> AWE() = m_NFP3_AWE;
			if ( IsDoubleOK( m_NFP3_AWE ))		result -> AWE() = m_NFP3_AWE;
			else								result -> AWE() = 0;
//			result -> AEW()    = m_NFP3_AEW;
//			if ( !IsFieldNull( &m_NFP3_AEW ))	result -> AEW() = m_NFP3_AEW;
			if ( IsDoubleOK( m_NFP3_AEW ))		result -> AEW() = m_NFP3_AEW;
			else								result -> AEW() = 0;
//			result -> GW()     = m_NFP3_GW;
//			if ( !IsFieldNull( &m_NFP3_GW ))	result -> GW() = m_NFP3_GW;
			if ( IsDoubleOK( m_NFP3_GW ))		result -> GW() = m_NFP3_GW;
			else								result -> GW() = 0;
			result -> MOB()    = TestYES( m_NFP3_MOB );
			result -> SAM()    = TestYES( m_NFP3_SAM );
//			result -> SAG()    = m_NFP3_SAG;
//			if ( !IsFieldNull( &m_NFP3_SAG ))	result -> SAG() = m_NFP3_SAG;
			if ( IsDoubleOK( m_NFP3_SAG ))		result -> SAG() = m_NFP3_SAG;
			else								result -> SAG() = 0;
			result -> SAT()    = TestYES( m_NFP3_SAT );
			result -> KK()     = TestYES( m_NFP3_KK );
//			result -> KKG()    = m_NFP3_KKG;
//			if ( !IsFieldNull( &m_NFP3_KKG ))	result -> KKG() = m_NFP3_KKG;
			if ( IsDoubleOK( m_NFP3_KKG ))		result -> KKG() = m_NFP3_KKG;
			else								result -> KKG() = 0;
			result -> KKT()    = TestYES( m_NFP3_KKT );
			result -> KKV()    = TestYES( m_NFP3_KKV );
			result -> KKK()    = TestYES( m_NFP3_KKK );
//			result -> FV()     = m_NFP3_FV;
//			if ( !IsFieldNull( &m_NFP3_FV ))	result -> FV() = m_NFP3_FV;
			if ( IsDoubleOK( m_NFP3_FV ))		result -> FV() = m_NFP3_FV;
			else								result -> FV() = 0;
			result -> Bem()    = m_NFP3_BEM;
			result -> FE()     = ( m_NFP3_FV == 1 );
			result -> FZ()     = ( m_NFP3_FV == 2 );
			result -> FZE()    = ( m_NFP3_FV == 3 );

//			result -> Sonst()  = m_strSonst;
		}
		else
		{
			result -> AWE() = 0;
			result -> AEW() = 0;
			result -> GW()  = 0;
			result -> MOB() = FALSE;
			result -> SAM() = FALSE;
			result -> SAG() = 0;
			result -> SAT() = FALSE;
			result -> KK()  = FALSE;
			result -> KKG() = 0;
			result -> KKT() = FALSE;
			result -> KKV() = FALSE;
			result -> KKK() = FALSE;
			result -> FV()  = 0;
		}
	}
	return result;
}	// FindIDE

BOOL CSetNF_PG3::Find( const char *id )
{
	BOOL	result = FALSE;

	ASSERT( id );
	ASSERT( AfxIsValidString( id ));
	ASSERT( *id != '\0' );

	if ( m_NFP3_IDE == id )
		return TRUE;

	BOOL		bOpened = FALSE;
	CString		oldFilter;

	oldFilter = m_strFilter;
	m_strFilter = "( NFP3_IDE = '";
	m_strFilter += id;
	m_strFilter += "' )";

	TRY
	{
		if ( IsOpen())	Requery();
		else
		{
			bOpened = TRUE;
			Open();
		}

		if ( m_NFP3_IDE == id )
			result = TRUE;

		m_strFilter = oldFilter;
		if ( bOpened )	Close();
		else			Requery();
	}
	CATCH (CMemoryException, m)
	{
		AfxMessageBox( IDS_NOMEMORY );
		return FALSE;
	}
	AND_CATCH (CFileException, f)
	{
		AfxMessageBox( IDS_FILEERROR );
		return FALSE;
	}
	AND_CATCH (CDaoException, d)
	{
		for ( short i = 0; i < d -> GetErrorCount(); i++ )
		{
			d -> GetErrorInfo( i );
			AfxMessageBox( d -> m_pErrorInfo -> m_strDescription );
		}
		return FALSE;
	}
	END_CATCH

	if ( result )
	{
		if ( !IsDoubleOK( m_NFP3_AWE ))		m_NFP3_AWE = 0;
		if ( !IsDoubleOK( m_NFP3_AEW ))		m_NFP3_AEW = 0;
		if ( !IsDoubleOK( m_NFP3_GW ))		m_NFP3_GW  = 0;
		if ( !IsDoubleOK( m_NFP3_SAG ))		m_NFP3_SAG = 0;
		if ( !IsDoubleOK( m_NFP3_KKG ))		m_NFP3_KKG = 0;
		if ( !IsDoubleOK( m_NFP3_FV ))		m_NFP3_FV  = 0;
	}
/*
	if ( !IsEOF() || !IsBOF())
	{
		if (( m_NFP3_IDE == id ) && !(IsEOF() || IsBOF()))
			result = TRUE;
		else
		{
			MoveFirst();
//			while ( !IsEOF() && ( m_NFP3_IDE != id ))
			while ( !IsEOF() && ( m_NFP3_IDE < id ))	// Setzt Index voraus!!!
				MoveNext();
			if ( m_NFP3_IDE == id )		result = TRUE;
	}	}
*/
	return result;
}	// Find

BOOL CSetNF_PG3::IDE( const char *w )
{	return SetSaveText( m_NFP3_IDE, w, 10 ); }

BOOL CSetNF_PG3::AWE( double w )
{	return SetSaveDoublePositive( m_NFP3_AWE, w, 10000. ); }

BOOL CSetNF_PG3::AEW( double w )
{	return SetSaveDoublePositive( m_NFP3_AEW, w, 100000. ); }

BOOL CSetNF_PG3::GW( double w )
{	return SetSaveDoublePositive( m_NFP3_GW, w, 10000000. ); }

BOOL CSetNF_PG3::MOB( BOOL w )
{
	if ( w )	m_NFP3_MOB = "Y";
	else		m_NFP3_MOB = "N";
	return FALSE;
}	// MOB

BOOL CSetNF_PG3::SAM( BOOL w )
{
	if ( w )	m_NFP3_SAM = "Y";
	else		m_NFP3_SAM = "N";
	return FALSE;
}	// SAM

BOOL CSetNF_PG3::SAG( double w )
{	return SetSaveDoublePositive( m_NFP3_SAG, w, 100000. ); }

BOOL CSetNF_PG3::SAT( BOOL w )
{
	if ( w )	m_NFP3_SAT = "Y";
	else		m_NFP3_SAT = "N";
	return FALSE;
}	// SAT

BOOL CSetNF_PG3::KK( BOOL w )
{
	if ( w )	m_NFP3_KK = "Y";
	else		m_NFP3_KK = "N";
	return FALSE;
}	// KK

BOOL CSetNF_PG3::KKG( double w )
{	return SetSaveDoublePositive( m_NFP3_KKG, w, 100000. ); }

BOOL CSetNF_PG3::KKT( BOOL w )
{
	if ( w )	m_NFP3_KKT = "Y";
	else		m_NFP3_KKT = "N";
	return FALSE;
}	// KKT

BOOL CSetNF_PG3::KKV( BOOL w )
{
	if ( w )	m_NFP3_KKV = "Y";
	else		m_NFP3_KKV = "N";
	return FALSE;
}	// KKV

BOOL CSetNF_PG3::KKK( BOOL w )
{
	if ( w )	m_NFP3_KKK = "Y";
	else		m_NFP3_KKK = "N";
	return FALSE;
}	// KKK

BOOL CSetNF_PG3::BEM( const char *w )
{
	ASSERT( w );
	ASSERT( AfxIsValidString( w ));
	m_NFP3_BEM = w;
	return FALSE;
}

// Liefert FALSE, wenn der Wert nicht korrigiert werden musste
BOOL CSetNF_PG3::SetSaveText( CString &z, const char *w, short len )
{
	BOOL		result = FALSE;
	CxString	text = w;

	text.AllTrimm();
	if ( text.GetLength() > len )
	{
		result = TRUE;
		text = text.Left( len );
	}
	z = text;

	return result;
}	// SetSaveText

// Liefert FALSE, wenn der Wert nicht korrigiert werden musste
BOOL CSetNF_PG3::SetSaveDoublePositive( double &z, double w, double max )
{
	BOOL	result = FALSE;
	double	t = w;

	if (( t > max ) || ( t < 0 ))
	{
		result = TRUE;
		if ( t > max )	t = max - 1;
		if ( t < 0 )	t = 0;
	}
	z = t;

	return result;
}	// SetSaveDoublePositive




CDetailSatz::CDetailSatz()
{
	m_NFP3_AWE = 0;
	m_NFP3_AEW = 0;
	m_NFP3_GW  = 0;
	m_NFP3_MOB = FALSE;
	m_NFP3_SAM = FALSE;
	m_NFP3_SAG = 0;
	m_NFP3_SAT = FALSE;
	m_NFP3_KK  = FALSE;
	m_NFP3_KKG = 0;
	m_NFP3_KKT = FALSE;
	m_NFP3_KKV = FALSE;
	m_NFP3_KKK = FALSE;
	m_NFP3_FV  = 0;
	m_NFP3_FE  = FALSE;
	m_NFP3_FZ  = FALSE;
	m_NFP3_FZE = FALSE;
}	// CDetailSatz

CDetailSatz& CDetailSatz::operator = ( CDetailSatz& qDS )
{
	IDE()    = qDS.IDE();
	AWE()    = qDS.AWE();
	AEW()    = qDS.AEW();
	GW()     = qDS.GW();
	MOB()    = qDS.MOB();
	SAM()    = qDS.SAM();
	SAG()    = qDS.SAG();
	SAT()    = qDS.SAT();
	KK()     = qDS.KK();
	KKG()    = qDS.KKG();
	KKT()    = qDS.KKT();
	KKV()    = qDS.KKV();
	KKK()    = qDS.KKK();
	FV()     = qDS.FV();
	Bem()    = qDS.Bem();
	FE()     = qDS.FE();
	FZ()     = qDS.FZ();
	FZE()    = qDS.FZE();
	Sonst()  = qDS.Sonst();
	return *this;
}	// operator =

void CSetNF_PG3::RewriteIDE( const char* ide, CDetailSatz* pDS )
{
	BOOL		bOpened = FALSE;
	CString		oldFilter;

	oldFilter = m_strFilter;
	m_strFilter = "( NFP3_IDE = '";
	m_strFilter += ide;
	m_strFilter += "' )";

	TRY
	{
		if ( IsOpen())	Requery();
		else
		{
			bOpened = TRUE;
			Open();
		}

		if ( IsEOF())		AddNew();
		else				Edit();

		m_NFP3_AEW = pDS -> AEW();
		m_NFP3_AWE = pDS -> AWE();
		m_NFP3_BEM = pDS -> Bem();
		m_NFP3_FV  = pDS -> FV();
		m_NFP3_GW  = pDS -> GW();
		m_NFP3_IDE = ide;
		m_NFP3_KK  = ( pDS -> KK() ? "Y" : "N" );
		m_NFP3_KKG = pDS -> KKG();
		m_NFP3_KKK = ( pDS -> KKK() ? "Y" : "N" );
		m_NFP3_KKT = ( pDS -> KKT() ? "Y" : "N" );
		m_NFP3_KKV = ( pDS -> KKV() ? "Y" : "N" );
		m_NFP3_MOB = ( pDS -> MOB() ? "Y" : "N" );
		m_NFP3_SAG = pDS -> SAG();
		m_NFP3_SAM = ( pDS -> SAM() ? "Y" : "N" );
		m_NFP3_SAT = ( pDS -> SAT() ? "Y" : "N" );
		if ( pDS -> FE())		m_NFP3_FV = 1;
		else if ( pDS -> FZ())	m_NFP3_FV = 2;
		else if ( pDS -> FZE())	m_NFP3_FV = 3;
		else					m_NFP3_FV = 2;

		Update();
		m_strFilter = oldFilter;
		if ( bOpened )	Close();
		else			Requery();
	}
	CATCH (CMemoryException, m)
	{
		AfxMessageBox( IDS_NOMEMORY );
		return;
	}
	AND_CATCH (CFileException, f)
	{
		AfxMessageBox( IDS_FILEERROR );
		return;
	}
	AND_CATCH (CDaoException, d)
	{
		for ( short i = 0; i < d -> GetErrorCount(); i++ )
		{
			d -> GetErrorInfo( i );
			AfxMessageBox( d -> m_pErrorInfo -> m_strDescription );
		}
		return;
	}
	END_CATCH
}


///////////////////////////////////////////////////////////////////////
//	CCalculator
void CCalculator::StartDialog()
{
	HINSTANCE	hLibrary;
	CString		dllname;
	CxString	text;
	BER_AGG_PROC	procAGG;
	BER_BDM_PROC	procBDM;
	BER_BFL_PROC	procBFL;
	BER_BSA_PROC	procBSA;
	BER_GEF_PROC	procGEF;
	BER_VOLP_PROC	procVOLP;
	BER_VOLT_PROC	procVOLT;

	ASSERT( !m_strIDE.IsEmpty());

	dllname = "GbmTriB.DLL";
	text = dllname;
	if ( !text.FileExist())
	{
		text  = "Kann die Datei '";
		text += dllname;
		text += "' nicht finden!";
		AfxMessageBox( text );
	}
	if (( hLibrary = LoadLibrary( dllname )) < (HINSTANCE)HINSTANCE_ERROR )
	{
		const char* lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);

		// Display the string.
		::MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

		// Free the buffer.
		LocalFree((void*)lpMsgBuf );
 
		text  = "Kann die Datei '";
		text += dllname;
		text += "' nicht laden!";
		AfxMessageBox( text );
		return;
	}

	procAGG  =  (BER_AGG_PROC)::GetProcAddress( hLibrary, "BER_AGG" );
	procBDM  =  (BER_BDM_PROC)::GetProcAddress( hLibrary, "BER_BDM" );
	procBFL  =  (BER_BFL_PROC)::GetProcAddress( hLibrary, "BER_BFL" );
	procBSA  =  (BER_BSA_PROC)::GetProcAddress( hLibrary, "BER_BSA" );
	procGEF  =  (BER_GEF_PROC)::GetProcAddress( hLibrary, "BER_GEF" );
	procVOLP = (BER_VOLP_PROC)::GetProcAddress( hLibrary, "BER_VOLP" );
	procVOLT = (BER_VOLT_PROC)::GetProcAddress( hLibrary, "BER_VOLT" );
	if (( procAGG == NULL ) || ( procBDM == NULL ) || ( procBFL == NULL ) ||
		( procBSA == NULL ) || ( procGEF == NULL ) || ( procVOLP == NULL ) ||
		( procVOLT == NULL ))
	{
		const char* lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);

		// Display the string.
		::MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

		// Free the buffer.
		LocalFree((void*)lpMsgBuf );
		FreeLibrary( hLibrary );
		return;
	}

	CBasisSatz	*pS = NULL;
	CDetailSatz	*pDS = NULL;
	CPG2DArray	arrPG2D, arrPG2H;
	CPG1GBArray	arrPG1GB;
	CCulcuDlg	dlg;

	pS = g_pNF_PG1 -> FindIDE( m_strIDE );
	pDS = m_pNF_PG3 -> FindIDE( m_strIDE );
	g_pNF_PG2D -> InitArray( m_strIDE, &arrPG2D );
	g_pNF_PG2H -> InitArray( m_strIDE, &arrPG2H );
	g_pNF_PG1GB -> InitArray( m_strIDE, &arrPG1GB );

	CxString	zeile;
//	double		temp;

	if ( pS != NULL )
	{
		float	UE_KAT, UE_GEF, UE_GEFS, UE_AGGS, WOHNEIN, UE_GEBF;
		float	UE_AGG, VOLLGE, UE_BAR, UE_BFL, UNB_VOLL, UMGE_VOLG;
		int		UE_TIEF, UE_FST;

		UE_KAT    = pS -> KAT();
		UE_GEFS   = pS -> GEFS();
		UE_FST    = ( pS -> Flurstk().IsEmpty() ? 0 : 1 );
		UE_GEBF   = arrPG1GB.GFL();

		UE_GEF    = pS -> GEF() = (*procGEF)( UE_KAT, UE_GEFS, UE_FST, UE_GEBF );

		UE_AGGS   = pS -> AGGS();
		WOHNEIN   = pDS -> AWE();
		UE_TIEF   = ( pS -> TIEF() ? 0 : 1 );

		UE_AGG    = pS -> AGG() = (*procAGG)( UE_KAT, UE_GEF, UE_GEFS, UE_AGGS, WOHNEIN, UE_TIEF, UE_GEBF );

		VOLLGE    = arrPG1GB.VOL();
		UNB_VOLL  = pS -> GFZ() + pS -> BMZ() + pS -> VGZ() + pS -> GUZ();
		UMGE_VOLG = pS -> VOLU();

		UE_BFL    = pS -> BFL() = (*procBFL)( UE_AGG, VOLLGE, UE_GEBF, UNB_VOLL, UMGE_VOLG );

		UE_BAR    = pS -> BAR();

		pS -> BDM()             = (*procBDM)( UE_AGG, VOLLGE, UE_BAR, UE_BFL, UNB_VOLL, UMGE_VOLG );
		
		pS -> VOLLIE2()         = (*procVOLP)( VOLLGE, UNB_VOLL, UMGE_VOLG );

		pS -> VOLLIE3()         = (*procVOLT)( VOLLGE );

		float	bsa  = (*procBSA)( UE_BAR );

		zeile.Empty();	zeile.AppendFormated( UE_KAT, -1, 2, 2 );
		dlg.m_strText1 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_GEFS, -1, 2, 2 );
		dlg.m_strText2 = zeile;
		zeile.Empty();	zeile.AppendF( UE_FST, -1 );
		dlg.m_strText3 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_GEBF, -1, 2, 2 );
		dlg.m_strText4 = zeile;

		zeile.Empty();	zeile.AppendFormated( UE_GEF, -1, 2, 2 );
		dlg.m_strText5 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_AGGS, -1, 2, 2 );
		dlg.m_strText6 = zeile;
		zeile.Empty();	zeile.AppendFormated( WOHNEIN, -1, 2, 2 );
		dlg.m_strText7 = zeile;
		zeile.Empty();	zeile.AppendF( UE_TIEF, -1 );
		dlg.m_strText8 = zeile;

		zeile.Empty();	zeile.AppendFormated( VOLLGE, -1, 2, 2 );
		dlg.m_strText9 = zeile;
		zeile.Empty();	zeile.AppendFormated( UNB_VOLL, -1, 2, 2 );
		dlg.m_strText10 = zeile;
		zeile.Empty();	zeile.AppendFormated( UMGE_VOLG, -1, 2, 2 );
		dlg.m_strText11 = zeile;

		zeile.Empty();	zeile.AppendFormated( UE_BAR, -1, 2, 2 );
		dlg.m_strtext12 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_BFL, -1, 2, 2 );
		dlg.m_strText13 = zeile;

//BER_AGG ( float UE_KAT, float UE_GEF, float UE_GEFS, float UE_AGGS, float WOHNEIN, int UE_TIEF, float UE_GEBF );
//BER_BDM ( float UE_AGG, float VOLLGE, float UE_BAR, float UE_BFL, float UNB_VOLL, float UMGE_VOLG );
//BER_BFL ( float UE_AGG, float VOLLGE, float UE_GEBF, float UNB_VOLL, float UMGE_VOLG );
//BER_GEF ( float UE_KAT, float UE_GEFS, int UE_FST, float UE_GEBF );
//BER_VOLP( float VOLLGE, float UNB_VOLL, float UMGE_VOLG );
//BER_VOLT( float VOLLGE );
//BER_BSA ( float UE_BAR );

		zeile.Empty();	zeile.AppendFormated( UE_GEF, -1, 2, 2 );
		dlg.m_strText24 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_AGG, -1, 2, 2 );
		dlg.m_strText20 = zeile;
		zeile.Empty();	zeile.AppendFormated( UE_BFL, -1, 2, 2 );
		dlg.m_strText22 = zeile;
		zeile.Empty();	zeile.AppendFormated( pS -> BDM(), -1, 2, 2 );
		dlg.m_strText21 = zeile;
		zeile.Empty();	zeile.AppendFormated( pS -> VOLLIE2(), -1, 2, 2 );
		dlg.m_strText25 = zeile;
		zeile.Empty();	zeile.AppendFormated( pS -> VOLLIE3(), -1, 2, 2 );
		dlg.m_strText26 = zeile;
		zeile.Empty();	zeile.AppendFormated( bsa, -1, 2, 2 );
		dlg.m_strText23 = zeile;

		if ( IDOK == dlg.DoModal())
			g_pNF_PG1 -> RewriteIDE( pS );
	}

	FreeLibrary( hLibrary );
}	// StartDialog

void CCalculator::Calculate()
{
	HINSTANCE		hLibrary;
	CString			dllname;
	CxString		text;
	BER_AGG_PROC	procAGG;
	BER_BDM_PROC	procBDM;
	BER_BFL_PROC	procBFL;
	BER_BSA_PROC	procBSA;
	BER_GEF_PROC	procGEF;
	BER_VOLP_PROC	procVOLP;
	BER_VOLT_PROC	procVOLT;

	ASSERT( m_arrIDE.GetSize() > 0 );

	dllname = "GbmTriB.DLL";
	text = dllname;
	if ( !text.FileExist())
	{
		text  = "Kann die Datei '";
		text += dllname;
		text += "' nicht finden!";
		AfxMessageBox( text );
	}
	if (( hLibrary = LoadLibrary( dllname )) < (HINSTANCE)HINSTANCE_ERROR )
	{
		const char* lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);

		// Display the string.
		::MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

		// Free the buffer.
		LocalFree((void*)lpMsgBuf );
 
		text  = "Kann die Datei '";
		text += dllname;
		text += "' nicht laden!";
		AfxMessageBox( text );
		return;
	}

	procAGG  =  (BER_AGG_PROC)::GetProcAddress( hLibrary, "BER_AGG" );
	procBDM  =  (BER_BDM_PROC)::GetProcAddress( hLibrary, "BER_BDM" );
	procBFL  =  (BER_BFL_PROC)::GetProcAddress( hLibrary, "BER_BFL" );
	procBSA  =  (BER_BSA_PROC)::GetProcAddress( hLibrary, "BER_BSA" );
	procGEF  =  (BER_GEF_PROC)::GetProcAddress( hLibrary, "BER_GEF" );
	procVOLP = (BER_VOLP_PROC)::GetProcAddress( hLibrary, "BER_VOLP" );
	procVOLT = (BER_VOLT_PROC)::GetProcAddress( hLibrary, "BER_VOLT" );
	if (( procAGG == NULL ) || ( procBDM == NULL ) || ( procBFL == NULL ) ||
		( procBSA == NULL ) || ( procGEF == NULL ) || ( procVOLP == NULL ) ||
		( procVOLT == NULL ))
	{
		const char* lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);

		// Display the string.
		::MessageBox( NULL, lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );

		// Free the buffer.
		LocalFree((void*)lpMsgBuf );
		FreeLibrary( hLibrary );
		return;
	}

	CBasisSatz	*pS = NULL;
	CDetailSatz	*pDS = NULL;
	CPG2DArray	arrPG2D, arrPG2H;
	CPG1GBArray	arrPG1GB;
	short		i;

	for ( i = 0; i < m_arrIDE.GetSize(); i++ )
	{
		m_strIDE = m_arrIDE[i];
		pS = g_pNF_PG1 -> FindIDE( m_strIDE );
		pDS = m_pNF_PG3 -> FindIDE( m_strIDE );
		g_pNF_PG2D -> InitArray( m_strIDE, &arrPG2D );
		g_pNF_PG2H -> InitArray( m_strIDE, &arrPG2H );
		g_pNF_PG1GB -> InitArray( m_strIDE, &arrPG1GB );

		if ( pS != NULL )
		{
			float	UE_KAT, UE_GEF, UE_GEFS, UE_AGGS, WOHNEIN, UE_GEBF;
			float	UE_AGG, VOLLGE, UE_BAR, UE_BFL, UNB_VOLL, UMGE_VOLG;
			int		UE_TIEF, UE_FST;

			UE_KAT    = pS -> KAT();
			UE_GEFS   = pS -> GEFS();
			UE_FST    = ( pS -> Flurstk().IsEmpty() ? 0 : 1 );
			UE_GEBF   = arrPG1GB.GFL();

			UE_GEF    = pS -> GEF() = (*procGEF)( UE_KAT, UE_GEFS, UE_FST, UE_GEBF );

			UE_AGGS   = pS -> AGGS();
			WOHNEIN   = pDS -> AWE();
			UE_TIEF   = ( pS -> TIEF() ? 0 : 1 );

			UE_AGG    = pS -> AGG() = (*procAGG)( UE_KAT, UE_GEF, UE_GEFS, UE_AGGS, WOHNEIN, UE_TIEF, UE_GEBF );

			VOLLGE    = arrPG1GB.VOL();
			UNB_VOLL  = pS -> GFZ() + pS -> BMZ() + pS -> VGZ() + pS -> GUZ();
			UMGE_VOLG = pS -> VOLU();

			UE_BFL    = pS -> BFL() = (*procBFL)( UE_AGG, VOLLGE, UE_GEBF, UNB_VOLL, UMGE_VOLG );

			UE_BAR    = pS -> BAR();

			pS -> BDM()             = (*procBDM)( UE_AGG, VOLLGE, UE_BAR, UE_BFL, UNB_VOLL, UMGE_VOLG );

			pS -> VOLLIE2()         = (*procVOLP)( VOLLGE, UNB_VOLL, UMGE_VOLG );

			pS -> VOLLIE3()         = (*procVOLT)( VOLLGE );

			float	bsa  = (*procBSA)( UE_BAR );

//BER_AGG ( float UE_KAT, float UE_GEF, float UE_GEFS, float UE_AGGS, float WOHNEIN, int UE_TIEF, float UE_GEBF );
//BER_BDM ( float UE_AGG, float VOLLGE, float UE_BAR, float UE_BFL, float UNB_VOLL, float UMGE_VOLG );
//BER_BFL ( float UE_AGG, float VOLLGE, float UE_GEBF, float UNB_VOLL, float UMGE_VOLG );
//BER_GEF ( float UE_KAT, float UE_GEFS, int UE_FST, float UE_GEBF );
//BER_VOLP( float VOLLGE, float UNB_VOLL, float UMGE_VOLG );
//BER_VOLT( float VOLLGE );
//BER_BSA ( float UE_BAR );
			g_pNF_PG1 -> RewriteIDE( pS );
		}
	}

	FreeLibrary( hLibrary );
}	// Calculate

void CSetNF_PG3::TestPrintIDE( CStringArray* array )
{
	CStringArray	temp;
	CString			filter, oldFilter;
	CString			oldSort;
	CString			ide;
	BOOL			bOpened = FALSE;
	int				i;

	if ( array -> GetSize() == 0 )		return;

	ide = array -> GetAt( 0 );
//	filter = "(Left( NFP3_IDE, 2 ) = '";
//	filter += ide.Left( 2 );
//	filter += "') AND ";
//	filter += "(NFP3_MOB = 'Y')";

//	filter = "(NFP3_MOB = 'Y')";

	filter = "( NFP3_IDE Like '";
	filter += ide.Left( 2 );
	filter += "%') AND ";
	filter += "(NFP3_MOB = 'Y')";

	oldFilter = m_strFilter;
	oldSort = m_strSort;
	m_strFilter = filter;
	m_strSort = "NFP3_IDE";
	if ( !IsOpen())
	{
		Open();
		bOpened = TRUE;
	}
	else
		Requery();

	for ( i = 0; i < array -> GetSize(); i++ )
	{
		ide = array -> GetAt( i );
		if ( Find( ide ))
			temp.Add( ide );
	}

	m_strFilter = oldFilter;
	m_strSort = oldSort;
	if ( bOpened )	Close();
	else			Requery();

	array -> RemoveAll();
	for ( i = 0; i < temp.GetSize(); i++ )
		array -> Add( temp[i]);
}

BOOL CSetNF_PG3::ModIDE( const char* alt, const char* neu )
{
	CString		text, init, oldFilter;
	BOOL		result = FALSE;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( alt ));
	ASSERT( AfxIsValidString( neu ));
	init = neu;
	if ( init.GetLength() > 2 )
		init = init.Left( 2 );

	InitListen( init );

	oldFilter = m_strFilter;
	m_strFilter = "( NFP3_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP3_IDE = neu;
		Update();

		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

//	m_bInitialisiert = FALSE;
	InitListen( init );

	return TRUE;
}

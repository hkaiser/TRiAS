// NF_PG1.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase* g_pDatabase;
extern CSetNF_PG4* g_pNF_PG4;
extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1

IMPLEMENT_DYNAMIC(CSetNF_PG1, CRecordset)

CSetNF_PG1::CSetNF_PG1(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG1)
	m_NFP1_PRO = _T("");
	m_NFP1_IDE = _T("");
	m_NFP1_ORT = _T("");
	m_NFP1_FLU = _T("");
	m_NFP1_KAT = 0.0;
	m_NFP1_FST = _T("");
	m_NFP1_GFZ = 0.0;
	m_NFP1_BMZ = 0.0;
	m_NFP1_VGZ = 0.0;
	m_NFP1_GUZ = 0.0;
	m_NFP1_TIEF = _T("");
	m_NFP1_GEF = 0.0;
	m_NFP1_AGG = 0.0;
	m_NFP1_BFL = 0.0;
	m_NFP1_AST = _T("");
	m_NFP1_STC = _T("");
	m_NFP1_BAR = 0.0;
	m_NFP1_TIEB = 0.0;
	m_NFP1_BDM = 0.0;
	m_NFP1_KASS = _T("");
	m_NFP1_AGGS = 0.0;
	m_NFP1_GEFS = 0.0;
	m_NFP1_FLGG = 0.0;
	m_B_GEDR = _T("");
	m_B_GE_D = _T("");
	m_B_GE_Z = _T("");
	m_NA_B_PLAN = _T("");
	m_NFP1_VOLU = 0.0;
	m_VOLLIE2 = 0.0;
	m_VOLLIE3 = 0.0;
	m_NFP1_ANNWL = _T("");
	m_RW_DM_JA = 0.0;
	m_RW_DM_QA = 0.0;
	m_RW_FL_GE = 0.0;
	m_RW_FL_RU = 0.0;
	m_NFP1_NEIG = _T("");
	m_nFields = 37;
	//}}AFX_FIELD_INIT
//	m_nDefaultType = dynaset;
	m_nDefaultType = snapshot;
	m_bInitialisiert = FALSE;
	m_strSort = "NFP1_IDE";
}


CString CSetNF_PG1::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG1::GetDefaultSQL()
{
	return _T("[NF_PG1]");
}

void CSetNF_PG1::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG1)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP1_PRO]"), m_NFP1_PRO);
	RFX_Text(pFX, _T("[NFP1_IDE]"), m_NFP1_IDE);
	RFX_Text(pFX, _T("[NFP1_ORT]"), m_NFP1_ORT);
	RFX_Text(pFX, _T("[NFP1_FLU]"), m_NFP1_FLU);
	RFX_Double(pFX, _T("[NFP1_KAT]"), m_NFP1_KAT);
	RFX_Text(pFX, _T("[NFP1_FST]"), m_NFP1_FST);
	RFX_Double(pFX, _T("[NFP1_GFZ]"), m_NFP1_GFZ);
	RFX_Double(pFX, _T("[NFP1_BMZ]"), m_NFP1_BMZ);
	RFX_Double(pFX, _T("[NFP1_VGZ]"), m_NFP1_VGZ);
	RFX_Double(pFX, _T("[NFP1_GUZ]"), m_NFP1_GUZ);
	RFX_Text(pFX, _T("[NFP1_TIEF]"), m_NFP1_TIEF);
	RFX_Double(pFX, _T("[NFP1_GEF]"), m_NFP1_GEF);
	RFX_Double(pFX, _T("[NFP1_AGG]"), m_NFP1_AGG);
	RFX_Double(pFX, _T("[NFP1_BFL]"), m_NFP1_BFL);
	RFX_Text(pFX, _T("[NFP1_AST]"), m_NFP1_AST);
	RFX_Text(pFX, _T("[NFP1_STC]"), m_NFP1_STC);
	RFX_Double(pFX, _T("[NFP1_BAR]"), m_NFP1_BAR);
	RFX_Date(pFX, _T("[NFP1_ANDAT]"), m_NFP1_ANDAT);
	RFX_Double(pFX, _T("[NFP1_TIEB]"), m_NFP1_TIEB);
	RFX_Double(pFX, _T("[NFP1_BDM]"), m_NFP1_BDM);
	RFX_Text(pFX, _T("[NFP1_KASS]"), m_NFP1_KASS);
	RFX_Double(pFX, _T("[NFP1_AGGS]"), m_NFP1_AGGS);
	RFX_Double(pFX, _T("[NFP1_GEFS]"), m_NFP1_GEFS);
	RFX_Double(pFX, _T("[NFP1_FLGG]"), m_NFP1_FLGG);
	RFX_Text(pFX, _T("[B_GEDR]"), m_B_GEDR);
	RFX_Text(pFX, _T("[B_GE_D]"), m_B_GE_D);
	RFX_Text(pFX, _T("[B_GE_Z]"), m_B_GE_Z);
	RFX_Text(pFX, _T("[NA_B_PLAN]"), m_NA_B_PLAN);
	RFX_Double(pFX, _T("[NFP1_VOLU]"), m_NFP1_VOLU);
	RFX_Double(pFX, _T("[VOLLIE2]"), m_VOLLIE2);
	RFX_Double(pFX, _T("[VOLLIE3]"), m_VOLLIE3);
	RFX_Text(pFX, _T("[NFP1_ANNWL]"), m_NFP1_ANNWL);
	RFX_Double(pFX, _T("[RW_DM_JA]"), m_RW_DM_JA);
	RFX_Double(pFX, _T("[RW_DM_QA]"), m_RW_DM_QA);
	RFX_Double(pFX, _T("[RW_FL_GE]"), m_RW_FL_GE);
	RFX_Double(pFX, _T("[RW_FL_RU]"), m_RW_FL_RU);
	RFX_Text(pFX, _T("[NFP1_NEIG]"), m_NFP1_NEIG);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1 diagnostics

#ifdef _DEBUG
void CSetNF_PG1::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_PG1::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

//#define SET_SAVE_DATA( x, y )	if ( IsFieldNull( &y ))	x = 0;	else x = y;
#define SET_SAVE_DATA( x, y )	if ( !IsDoubleOK( y ))	x = 0;	else x = y;

void CSetNF_PG1::Refresh()
{
	if ( IsOpen())	Close();
	Open();
	m_bInitialisiert = FALSE;
}

void CSetNF_PG1::UpdateListen( CStringArray* array )
{
	ASSERT( AfxIsValidAddress( array, sizeof( CStringArray )));

	if ( array -> GetSize() * 2 > m_arrBasis.GetSize())
	{
		InitListen( array -> GetAt( 0 ));
		return;
	}

	CString		strIDE;
	int			i;

	for ( i = 0; i < array -> GetSize(); i++ )
	{
		strIDE = array -> GetAt( i );

	}
}

void CSetNF_PG1::InitListen( const char* id )
{
	CBasisSatz*	pS;
	BOOL		bFertig;
	CString		kenn, ide;
	CString		flur, stck, tief;
	CString		text;
	short		len;

	ASSERT( AfxIsValidString( id ));
	if ( !AfxIsValidString( id ))	return;
	ide = id;
	ide.TrimLeft();
	ide.TrimRight();
	len = ide.GetLength();
	if ( len < 2 )	return;
	if ( len > 2 )
	{
		len = 2;
		ide = ide.Left( len );
	}

	if ( !( ide == m_strLastInitID ))
		m_bInitialisiert = FALSE;

	if ( m_bInitialisiert )		return;

	m_strLastInitID = ide;

	AfxGetMainWnd() -> BeginWaitCursor();

	if ( g_pNF_PG4 == NULL )	g_pNF_PG4 = new CSetNF_PG4( g_pDatabase );
	ASSERT( g_pNF_PG4 );

	if ( !IsOpen())		Open();
	else				Requery();

	bFertig = FALSE;
	while ( !IsEOF() && !bFertig )
	{
		kenn = m_NFP1_IDE.Left( len );
		if ( kenn == ide )		bFertig = TRUE;
		else					MoveNext();
	}

	bFertig = FALSE;
	m_arrBasis.Clear();
	while ( !IsEOF() && !bFertig )
	{
		if ( g_iMessageStatus >= 3 )
		{
			text  = "Initialisieren NF_PG1: ";
			text += m_NFP1_IDE;
			DEX_SetMessageString((const char*)text );
		}

		pS = m_arrBasis.Add( m_NFP1_IDE );
		if ( pS )
			if ( pS -> Gueltig())
		{
			flur = m_NFP1_FLU;
			stck = m_NFP1_FST;
			tief = m_NFP1_TIEF;
			flur.TrimLeft();
			flur.TrimRight();
			stck.TrimLeft();
			stck.TrimRight();
			tief.MakeUpper();

			if ( g_pNF_PG4 -> Find( m_NFP1_IDE ))
			{
				pS -> Besitzer()  = g_pNF_PG4 -> m_NFP4_ENA;	// m_NFP1_ENA;
				pS -> Ort()	      = g_pNF_PG4 -> m_NFP4_EOR;	// m_NFP1_EOR;
				pS -> PLZ()       = g_pNF_PG4 -> m_NFP4_EPL;	// m_NFP1_EPL;
				pS -> Strasse()	  = g_pNF_PG4 -> m_NFP4_EAN;	// m_NFP1_EAN;
				pS -> Hausnr()    = "";
			}
			else
			{
				pS -> Besitzer()  = "";
				pS -> Ort()	      = "";
				pS -> PLZ()       = "";
				pS -> Strasse()	  = "";
				pS -> Hausnr()    = "";
			}
			pS -> Flur()      = flur;
			pS -> Flurstk()   = stck;
//			pS -> GSFlaeche() = m_NFP1_KAT;		// Fläche lt. Kataster
//			if ( IsFieldNull( &m_NFP1_KAT ))	pS -> GSFlaeche() = 0;
//			else								pS -> GSFlaeche() = m_NFP1_KAT;
			SET_SAVE_DATA( pS -> GSFlaeche(), m_NFP1_KAT );
//			pS -> BFlaeche()  = m_NFP1_BFL;		// Beitragsfläche
//			if ( IsFieldNull( &m_NFP1_BFL ))	pS -> BFlaeche() = 0;
//			else								pS -> BFlaeche() = m_NFP1_BFL;
			SET_SAVE_DATA( pS -> BFlaeche(), m_NFP1_BFL );
//			pS -> Beitrag()   = m_NFP1_BDM;		// Beitrag in DM (??)
//			if ( IsFieldNull( &m_NFP1_BDM ))	pS -> Beitrag() = 0;
//			else								pS -> Beitrag() = m_NFP1_BDM;
			SET_SAVE_DATA( pS -> Beitrag(), m_NFP1_BDM );

//			pS -> BAR()       = int( m_NFP1_BAR );
			SET_SAVE_DATA( pS -> BAR(), m_NFP1_BAR );
//			pS -> GFZ()       = m_NFP1_GFZ;
			SET_SAVE_DATA( pS -> GFZ(), m_NFP1_GFZ );
//			pS -> BMZ()       = m_NFP1_BMZ;
			SET_SAVE_DATA( pS -> BMZ(), m_NFP1_BMZ );
//			pS -> VGZ()       = m_NFP1_VGZ;
			SET_SAVE_DATA( pS -> VGZ(), m_NFP1_VGZ );
//			pS -> GUZ()       = m_NFP1_GUZ;
			SET_SAVE_DATA( pS -> GUZ(), m_NFP1_GUZ );
//			pS -> KAT()       = m_NFP1_KAT;
			SET_SAVE_DATA( pS -> KAT(), m_NFP1_KAT );
			pS -> AnDatGueltig() = !IsFieldNull( &m_NFP1_ANDAT );
			pS -> ANDAT()     = m_NFP1_ANDAT;
			pS -> AnNWL()     = m_NFP1_ANNWL;
			pS -> AnNWL().MakeLower();
//			pS -> GEF()       = m_NFP1_GEF;
			SET_SAVE_DATA( pS -> GEF(), m_NFP1_GEF );
//			pS -> GEFS()      = m_NFP1_GEFS;
			SET_SAVE_DATA( pS -> GEFS(), m_NFP1_GEFS );
//			pS -> AGG()       = m_NFP1_AGG;
			SET_SAVE_DATA( pS -> AGG(), m_NFP1_AGG );
//			pS -> AGGS()      = m_NFP1_AGGS;
			SET_SAVE_DATA( pS -> AGGS(), m_NFP1_AGGS );
//			pS -> BFL()       = m_NFP1_BFL;
			SET_SAVE_DATA( pS -> BFL(), m_NFP1_BFL );
			pS -> TIEF()      = ( tief == "N" );

//			pS -> TIEB()      = m_NFP1_TIEB;
			SET_SAVE_DATA( pS -> TIEB(), m_NFP1_TIEB );
//			pS -> VOLU()      = m_NFP1_VOLU;
//			if ( IsFieldNull( &m_NFP1_VOLU ))	pS -> VOLU() = 0;
//			else								pS -> VOLU() = m_NFP1_VOLU;
			SET_SAVE_DATA( pS -> VOLU(), m_NFP1_VOLU );
			pS -> NA_B_PLAN() = m_NA_B_PLAN;
			pS -> KASS()      = m_NFP1_KASS;
//			pS -> VOLLIE2()   = m_VOLLIE2;
//			if ( IsFieldNull( &m_VOLLIE2 ))		pS -> VOLLIE2() = 0;
//			else								pS -> VOLLIE2() = m_VOLLIE2;
			SET_SAVE_DATA( pS -> VOLLIE2(), m_VOLLIE2 );
//			pS -> VOLLIE3()   = m_VOLLIE3;
//			if ( IsFieldNull( &m_VOLLIE3 ))		pS -> VOLLIE3() = 0;
//			else								pS -> VOLLIE3() = m_VOLLIE3;
			SET_SAVE_DATA( pS -> VOLLIE3(), m_VOLLIE3 );
//			pS -> BDM()       = m_NFP1_BDM;
			SET_SAVE_DATA( pS -> BDM(), m_NFP1_BDM );
//			m_B_GEDR;
			pS -> m_bBBGedr   = TestYES( m_B_GEDR );	// || ( m_B_GEDR == "R" ))
			pS -> m_bGBGedr   = TestYES( m_B_GEDR );	// || ( m_B_GEDR == "R" ))
//			m_B_GE_D;
//			m_B_GE_Z;
			SET_SAVE_DATA( pS -> RW_DM_QA(), m_RW_DM_QA );
			SET_SAVE_DATA( pS -> RW_DM_JA(), m_RW_DM_JA );
			SET_SAVE_DATA( pS -> RW_FL_RU(), m_RW_FL_RU );
			SET_SAVE_DATA( pS -> RW_FL_GE(), m_RW_FL_GE );
			pS -> NEIG() = m_NFP1_NEIG;

			if ( m_strProjekt.IsEmpty())	m_strProjekt = m_NFP1_PRO;
		}
		MoveNext();
		kenn = m_NFP1_IDE.Left( len );
		if ( !( kenn == ide ))		bFertig = TRUE;
	}
	Close();
	if ( g_iMessageStatus >= 3 )
	{
		text  = "Initialisieren NF_PG1 abgeschlossen.";
		DEX_SetMessageString((const char*)text );
	}

	m_bInitialisiert = TRUE;
	AfxGetMainWnd() -> EndWaitCursor();
}

short CSetNF_PG1::GetSize()
{
	return m_arrBasis.GetSize();
}

CBasisSatz* CSetNF_PG1::FindIDE( const char* ide )
{
	return m_arrBasis.Find( ide );
}

void CSetNF_PG1::Add2Array( const char* muster, CStringArray* pArray )
{
	CBasisSatz	*pS;
	CString		ident, txt;
	short		i, len;

	ASSERT( AfxIsValidString( muster ));
	if ( !AfxIsValidString( muster ))	return;
	txt = muster;
	if ( txt.GetLength() < 2 )		return;
	len = txt.GetLength();

	for ( i = 0; i < m_arrBasis.GetSize(); i++ )
	{
		pS = (CBasisSatz*)m_arrBasis[i];
		ident = pS -> IDE();
		if ( ident.Left( len ) == txt )
		{
			pArray -> Add( ident );
		}
	}
}	// Add2Array

void CSetNF_PG1::Add2ArrayByEigner( const char* name, CStringArray* pArray )
{
	CBasisSatz	*pS;
	CString		ident, txt;
	short		i, len;

	ASSERT( AfxIsValidString( name ));
	if ( !AfxIsValidString( name ))	return;
	txt = name;
	if ( txt.GetLength() < 2 )		return;
	len = txt.GetLength();

	for ( i = 0; i < m_arrBasis.GetSize(); i++ )
	{
		pS = (CBasisSatz*)m_arrBasis[i];
		ident = pS -> Besitzer();
		if ( ident.Left( len ) == txt )
		{
			pArray -> Add( pS -> IDE());
		}
	}
}

void CSetNF_PG1::Add2ArrayByFlur( const char* flur, const char* stck, CStringArray* pArray )
{
	CBasisSatz	*pS;
	CString		id1, id2, txt, tyt;
	short		i, len1, len2;

	ASSERT( AfxIsValidString( flur ));
	ASSERT( AfxIsValidString( stck ));
	if ( !AfxIsValidString( flur ))	return;
	if ( !AfxIsValidString( stck ))	return;
	txt = flur;
	tyt = stck;
	len1 = txt.GetLength();
	len2 = tyt.GetLength();
	if (( len1 + len2 ) < 1 )	return;

	for ( i = 0; i < m_arrBasis.GetSize(); i++ )
	{
		pS = (CBasisSatz*)m_arrBasis[i];
		id1 = pS -> Flur();
		id2 = pS -> Flurstk();

		if ( len2 == 0 )
		{
			if ( id1.Left( len1 ) == txt )
				pArray -> Add( pS -> IDE());
		}
		else if ( len1 == 0 )
		{
			if ( id2.Left( len2 ) == tyt )
				pArray -> Add( pS -> IDE());
		}
		else
		{
			if (( id1.Left( len1 ) == txt ) &&
				( id2.Left( len2 ) == tyt ))
				pArray -> Add( pS -> IDE());
		}
	}
}

void CSetNF_PG1::CopyGS( const char* quelle, const char* neu )
{
	CBasisSatz	*pQ;
	CBasisSatz	*pN;

	ASSERT( AfxIsValidString( quelle ));
	ASSERT( AfxIsValidString( neu ));

	pQ = FindIDE( quelle );

	if ( NULL != pQ )
	{
		pN = m_arrBasis.Add( neu );
		if ( NULL == pN )
		{
			AfxMessageBox( IDS_NOMEMORY );
			return;
		}

		pN -> PLZ()        = pQ -> PLZ();
		pN -> Ort()        = pQ -> Ort();
		pN -> Strasse()    = pQ -> Strasse();
		pN -> Hausnr()     = pQ -> Hausnr();
		pN -> Flur()       = pQ -> Flur();
		pN -> Flurstk()    = pQ -> Flurstk();
		pN -> Besitzer()   = pQ -> Besitzer();
		pN -> GSFlaeche()  = pQ -> GSFlaeche();
		pN -> BFlaeche()   = pQ -> BFlaeche();
		pN -> Beitrag()    = pQ -> Beitrag();
		pN -> BAR()        = pQ -> BAR();
		pN -> GFZ()        = pQ -> GFZ();
		pN -> BMZ()        = pQ -> BMZ();
		pN -> VGZ()        = pQ -> VGZ();
		pN -> GUZ()        = pQ -> GUZ();
		pN -> ANDAT()      = pQ -> ANDAT();
		pN -> AnNWL()      = pQ -> AnNWL();
		pN -> KAT()        = pQ -> KAT();
		pN -> TIEF()       = pQ -> TIEF();
		pN -> TIEB()       = pQ -> TIEB();
		pN -> GEF()        = pQ -> GEF();
		pN -> GEFS()       = pQ -> GEFS();
		pN -> AGG()        = pQ -> AGG();
		pN -> AGGS()       = pQ -> AGGS();
		pN -> BFL()        = pQ -> BFL();
		pN -> VOLU()       = pQ -> VOLU();
		pN -> NA_B_PLAN()  = pQ -> NA_B_PLAN();
		pN -> KASS()       = pQ -> KASS();
		pN -> VOLLIE2()    = pQ -> VOLLIE2();
		pN -> VOLLIE3()    = pQ -> VOLLIE3();
		pN -> BDM()        = pQ -> BDM();
		pN -> RW_DM_QA()   = pQ -> RW_DM_QA();
		pN -> RW_DM_JA()   = pQ -> RW_DM_JA();
		pN -> RW_FL_RU()   = pQ -> RW_FL_RU();
		pN -> RW_FL_GE()   = pQ -> RW_FL_GE();
		pN -> NEIG()       = pQ -> NEIG();
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CBasisSatz

CBasisSatz::CBasisSatz( const char* ide )
{
	CString		text;

	m_bGueltig = FALSE;
	if ( AfxIsValidString( ide ))
	{
		text = ide;
		if ( text.GetLength() == 10 )
			m_bGueltig = TRUE;
	}
	if ( m_bGueltig )
		m_strIDE = text;

	m_rKAT       = 0;
	m_dBFlaeche  = 0;
	m_dBeitrag   = 0;

	m_dVOL     = 0;
	m_dGFL     = 0;
	m_dVOLU    = 0;
	m_dTIEB    = 0;
	m_rBFL     = 0;
	m_rAGG     = 0;
	m_rAGGS    = 0;
	m_rGEF     = 0;
	m_rGEFS    = 0;
	m_dBAR     = 0;
	m_rGFZ     = 0;
	m_rBMZ     = 0;
	m_rVGZ     = 0;
	m_rGUZ     = 0;
	m_rKAT     = 0;
	m_dVOLLIE2 = 0;
	m_dVOLLIE3 = 0;
	m_dBDM     = 0;
	m_dRW_DM_QA = 0;
	m_dRW_DM_JA = 0;
	m_dRW_FL_RU = 0;
	m_dRW_FL_GE = 0;

	m_bAnDatGueltig = FALSE;
	m_bTIEF         = FALSE;

	m_bBBGedr  = FALSE;
	m_bGBGedr  = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//	CBasisArray
CBasisArray::CBasisArray()
{
}

CBasisArray::~CBasisArray()
{
	Clear();
}

void CBasisArray::Clear()
{
	CBasisSatz*	pS;

	m_mapIndex.RemoveAll();
	for ( short i = 0; i < GetSize(); i++ )
	{
		pS = (CBasisSatz*)GetAt( i );
		if ( pS )	delete pS;
	}
	RemoveAll();
}	// Clear

CBasisSatz* CBasisArray::Add( const char* ide )
{
	CBasisSatz*	pS = NULL;
	CString		kenn;

	ASSERT( AfxIsValidString( ide ));
	if ( !AfxIsValidString( ide ))	return pS;
	kenn = ide;

	pS = new CBasisSatz( kenn );
	if ( pS )
	{
		if ( pS -> Gueltig())
		{
			CPtrArray::Add((void*)pS );
			m_mapIndex.SetAt( kenn, pS );
		}
		else
		{
			delete pS;
			pS = NULL;
		}
	}

	return pS;
}	// Add

void CBasisArray::Add( CBasisSatz* pS )
{
	ASSERT( pS );
	ASSERT( pS -> Gueltig());
	CPtrArray::Add((void*)pS );
	m_mapIndex.SetAt( pS -> IDE(), pS );
}

CBasisSatz* CBasisArray::Find( const char* ide )
{
//	CBasisSatz	*pS;
	CBasisSatz	*result = NULL;
	void		*ptr;
	CString		kenn;

	ASSERT( AfxIsValidString( ide ));
	if ( !AfxIsValidString( ide ))	return result;
	kenn = ide;

	if ( m_mapIndex.Lookup( kenn, ptr ))
		result = (CBasisSatz*)ptr;
/*
	for ( short i = 0; i < GetSize(); i++ )
	{
		pS = (CBasisSatz*)GetAt( i );
		if ( pS -> IDE() == kenn )
		{
			result = pS;
			break;
		}
	}
*/
	return result;
}	// Find


CString CBasisSatz::AnDatum()
{
	CString		result;
	CxString	buf;

	if ( AnDatGueltig())	buf.AppendF( m_strANDAT, 10 );
	else					buf = "unbekannt";
	result = buf;
	return result;
}

void CSetNF_PG1::RewriteIDE( CBasisSatz* pS )
{
	ASSERT( pS );

	CBasisSatz	*pO = FindIDE( pS -> IDE());

	if ( pO != pS )		m_arrBasis.Add( pS );
	WriteBack( pS );
}

void CSetNF_PG1::WriteBack( CBasisSatz* pS )
{
	BOOL		bOpened = FALSE;
	CString		oldFilter;
	CxString	datum, zeit;
	CTime		time;

	oldFilter = m_strFilter;
	m_strFilter = "( NFP1_IDE = '";
	m_strFilter += pS -> IDE();
	m_strFilter += "' )";

	time = CTime::GetCurrentTime();
	datum.AppendF( time, 18 );	// Datum yyyy-mm-dd HH:MM:SS
	zeit.AppendF( time, 4 );	// Zeit HH:MM
	zeit += ":00";
	TRY
	{
		if ( IsOpen())
			Requery();
		else
		{
			bOpened = TRUE;
			Open();
		}

		if ( IsEOF())		AddNew();
		else				Edit();

//		m_LFDNR;
		m_NFP1_PRO   = m_strProjekt;
		m_NFP1_IDE   = pS -> IDE();
//		m_NFP1_ENA   = pS -> Besitzer();
//		m_NFP1_EAN   = pS -> Strasse();
//		m_NFP1_EPL   = pS -> PLZ();
//		m_NFP1_EOR   = pS -> Ort();
//		m_NFP1_ORT;
		m_NFP1_FLU   = pS -> Flur();
		m_NFP1_KAT   = pS -> KAT();
		m_NFP1_FST   = pS -> Flurstk();
		m_NFP1_GFZ   = pS -> GFZ();
		m_NFP1_BMZ   = pS -> BMZ();
		m_NFP1_VGZ   = pS -> VGZ();
		m_NFP1_GUZ   = pS -> GUZ();
		m_NFP1_TIEF  = ( pS -> TIEF() ? "N" : "Y" );
		m_NFP1_GEF   = pS -> GEF();
		m_NFP1_GEFS  = pS -> GEFS();
		m_NFP1_AGG   = pS -> AGG();
		m_NFP1_AGGS  = pS -> AGGS();
		m_NFP1_BFL   = pS -> BFL();	//	pS -> BFlaeche()  = m_NFP1_BFL;
		m_NFP1_BAR   = pS -> BAR();
		m_NFP1_ANDAT = pS -> ANDAT();
		m_NFP1_ANNWL = pS -> AnNWL();
		m_NFP1_TIEB  = pS -> TIEB();
		m_NFP1_BDM   = pS -> Beitrag();
		m_NFP1_VOLU  = pS -> VOLU();
		m_NA_B_PLAN  = pS -> NA_B_PLAN();
		m_NFP1_KASS  = pS -> KASS();
		m_VOLLIE2    = pS -> VOLLIE2();		// *
		m_VOLLIE3    = pS -> VOLLIE3();		// *
		m_NFP1_BDM   = pS -> BDM();			// *
		m_RW_DM_QA   = pS -> RW_DM_QA();
		m_RW_DM_JA   = pS -> RW_DM_JA();
		m_RW_FL_RU   = pS -> RW_FL_RU();
		m_RW_FL_GE   = pS -> RW_FL_GE();
		m_NFP1_NEIG  = pS -> NEIG();
//		m_B_GEDR;
//		m_B_GE_D;
//		m_B_GE_Z;
//		if ( !IsFieldNull( &m_B_GEDR ))		// Schon gesetzte Flags nicht überschreiben!
		if ( !( m_B_GEDR == "Y" ) && !( m_B_GEDR == "N" ))		// Schon gesetzte Flags nicht überschreiben!
		{
			if (( pS -> m_bBBGedr ) && !TestYES( m_B_GEDR ))
			{
				m_B_GEDR = "Y";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
			if (( !pS -> m_bBBGedr ) && TestYES( m_B_GEDR ))
			{
				m_B_GEDR = "N";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
		}
		else
		{
			if ( pS -> m_bBBGedr )
			{
				m_B_GEDR = "Y";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
			else
			{
				m_B_GEDR = "N";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
		}
/*		if ( !( m_B_GEDR == "Y" ) && !( m_B_GEDR == "N" ))		// Schon gesetzte Flags nicht überschreiben!
		{
			if (( pS -> m_bGBGedr ) && !TestYES( m_B_GEDR ))
			{
				m_B_GEDR = "Y";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
			if (( !pS -> m_bGBGedr ) && TestYES( m_B_GEDR ))
			{
				m_B_GEDR = "N";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
		}
		else
		{
			if ( pS -> m_bGBGedr )
			{
				m_B_GEDR = "Y";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
			else
			{
				m_B_GEDR = "N";
				m_B_GE_D = datum;
				m_B_GE_Z = zeit;
			}
		}
*/
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
	AND_CATCH (CDBException, d)
	{
		AfxMessageBox( "DB - Fehler!" );
		AfxMessageBox( d -> m_strError );
	}
	END_CATCH
}

double& CBasisSatz::TIEB()
{	return m_dTIEB;
}

double& CBasisSatz::VOLU()
{	return m_dVOLU;
}

CString& CBasisSatz::NA_B_PLAN()
{	return m_strNA_B_PLAN;
}

void CSetNF_PG1::ResetIDE( const char* ide )
{
	CString		text, init, oldFilter;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( ide ));
	init = ide;
	if ( init.GetLength() > 2 )
		init = init.Left( 2 );

	InitListen( init );

	oldFilter = m_strFilter;
	m_strFilter = "( NFP1_IDE = '";
	m_strFilter += ide;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP1_GEF  = 0;
		m_NFP1_AGG  = 0;
		m_NFP1_BFL  = 0;
		m_NFP1_BDM  = 0;
		m_NFP1_AGGS = 0;
		m_NFP1_GEFS = 0;
		m_NFP1_FLGG = 0;
		m_NFP1_TIEB = 0;
		Update();

		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

	m_bInitialisiert = FALSE;
	InitListen( init );
}

void CSetNF_PG1::TestPrintBB( CStringArray* array )
{
	CStringArray	temp;
	CBasisSatz*		pBS;
	CString			ide;
	int				i;

	for ( i = 0; i < array -> GetSize(); i++ )
	{
		ide = array -> GetAt( i );
		pBS = FindIDE( ide );
		if ( pBS )
			if ( !pBS -> m_bBBGedr )
				temp.Add( ide );
	}
	array -> RemoveAll();
	for ( i = 0; i < temp.GetSize(); i++ )
		array -> Add( temp[i]);
}

void CSetNF_PG1::TestPrintGB( CStringArray* array )
{
	CStringArray	temp;
	CBasisSatz*		pBS;
	CString			ide;
	int				i;

	for ( i = 0; i < array -> GetSize(); i++ )
	{
		ide = array -> GetAt( i );
		pBS = FindIDE( ide );
		if ( pBS )
			if ( !pBS -> m_bGBGedr )
				temp.Add( ide );
	}
	array -> RemoveAll();
	for ( i = 0; i < temp.GetSize(); i++ )
		array -> Add( temp[i]);
}

BOOL CSetNF_PG1::ModIDE( const char* alt, const char* neu )
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
	if ( FindIDE( neu ) != NULL )
	{
		text = "Die Identifikationsnummer '";
		text += neu;
		text += "' wird bereits verwendet! Änderung nicht gespeichert!";
		AfxMessageBox( text );
		return result;
	}

	oldFilter = m_strFilter;
	m_strFilter = "( NFP1_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP1_IDE = neu;
		Update();

		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

	m_bInitialisiert = FALSE;
	InitListen( init );

	return TRUE;
}

long CSetNF_PG1::GetCount()
{
	long	result = 0L;
	SDWORD	n;

	SQLRETURN	status;
	HSTMT		hSTMT = NULL;
	CString		request, text;

	if ( SQL_SUCCESS != ::SQLAllocStmt( m_pDatabase -> m_hdbc, &hSTMT ))
	{
		text = "Fehler in NF_PG1::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	request = "SELECT Count(*) FROM NF_PG1";
	status = ::SQLExecDirect( hSTMT, (UCHAR FAR *)(const char*)request, request.GetLength());
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG1::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	status = ::SQLBindCol( hSTMT, 1, SQL_C_LONG, &result, sizeof(long), &n );
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG1::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	status = ::SQLFetch( hSTMT );
	if ( status == SQL_NO_DATA_FOUND )
	{
		result = 0L;
	}
	else if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG1::GetCount()";
		AfxMessageBox( text );
	}

cleanup:
	if ( hSTMT )
	{
		status = ::SQLFreeStmt( hSTMT, SQL_CLOSE );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG1::GetCount()\nSQLFreeStmt( hSTMT, SQL_CLOSE ) fehlgeschlagen!";
			AfxMessageBox( text );
		}

		status = ::SQLFreeStmt( hSTMT, SQL_DROP );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG1::GetCount()\nSQLFreeStmt( hSTMT, SQL_DROP ) fehlgeschlagen!";
			AfxMessageBox( text );
		}
		hSTMT = NULL;
	}

	return result;
}

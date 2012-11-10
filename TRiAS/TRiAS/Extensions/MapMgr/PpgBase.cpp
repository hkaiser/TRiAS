#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#undef CPropertyPage
#define CPropertyPage CPropertyPage

/////////////////////////////////////////////////////////////////////////////
// CPpgBase property page

IMPLEMENT_DYNAMIC(CPpgBase, CPropertyPage)

CPpgBase::CPpgBase(UINT nID)
	: CPropertyPage(nID)
	, m_IDD( nID )
{
	//{{AFX_DATA_INIT(CPpgBase)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpgBase::~CPpgBase() {
}

void CPpgBase::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpgBase)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPpgBase, CPropertyPage)
	//{{AFX_MSG_MAP(CPpgBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpgBase message handlers

BOOL CPpgBase::OnInitDialog()  {
	m_pParent = (CMapImportDlg*) GetParent();
	ASSERT_KINDOF( CMapImportDlg, m_pParent );
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CPpgBase::OnWizardBack()  {
//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	UINT	nID = m_pParent->m_pageWay.back();
	m_pParent->m_pageWay.pop_back();
	return nID;
}

LRESULT CPpgBase::OnWizardNext()  {
//	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	UINT	nNextStep = m_pParent->m_nNextStep;
//	TRACE( _T("CPpgBase::OnWizardNext: %ld\n"), nNextStep );
	if( -1 != nNextStep )
		m_pParent->m_pageWay.push_back(m_IDD);

	m_pParent->m_nNextStep = -1;

	return nNextStep;
}

LRESULT CPpgBase::OnWizardNext(UINT nID)  {
	CPpgBase::OnWizardNext();

	return nID;
}

BOOL CPpgBase::OnSetActive()  {
//	AFX_MANAGE_STATE(AfxGetModuleState());
	UpdateData(FALSE);
	UpdateControls();
	return CPropertyPage::OnSetActive();
}

BOOL CPpgBase::OnKillActive()  {
//	AFX_MANAGE_STATE(AfxGetModuleState());
	UpdateData();
	return CPropertyPage::OnKillActive();
}

BOOL CPpgBase::OnWizardFinish()  {
	AFX_MANAGE_STATE(AfxGetModuleState());
	return /*m_pParent->Finish() && */CPropertyPage::OnWizardFinish();
}

#include <stdlib.h>
#include <math.h>

static void setDMSMask( CMaskEdit& rCtl ) {
	rCtl.SetMask( _T("99°59'59,999\"") );
	rCtl.SetPromptChar( _T("0") );
}
static void setDMSValue( CMaskEdit& rCtl, const double &val ) {
	double d, m, s, v, rest;
	v = val;
	v = modf( v, &d ); v *= 60;
	v = modf( v, &m ); v *= 60;
	v = modf( v, &s ); v *= 1000;
	v = modf( v, &rest );
	if( rest < 1 ) rest *= 1000;
	else if( rest < 10 ) rest *= 100;
	else if( rest < 100 ) rest *= 10;
	CString	S;
	S.Format( _T("%02d°%02d'%02d,%03d\""), (short) d, (short) m, (short) s, (short) rest );
	rCtl.SetText( _T(','), S );
}
static void getDMSValue( double &val, CMaskEdit &rCtl ) {
	CString	S;
	S = rCtl.GetText( _T(',') );
	if( S.Find( _T(',') ) )
		S.SetAt( S.Find( _T(',') ), _T('.') );
	double v, vv, d, m, s, rest;
	v = atof( S );
	v = modf( v, &vv ); rest = v * 1000; v = vv / 100;
	v = modf( v, &vv ); s = v * 100; v = vv / 100;
	v = modf( v, &vv ); m = v * 100; v = vv / 100;
	v = modf( v, &vv ); d = v * 100; v = vv / 100;
	rest = floor( rest + 0.5 );
	d = floor( d + 0.5 );
	m = floor( m + 0.5 );
	s = floor( s + 0.5 );
	val = d + ( m / 60 ) + ( ( s + ( rest / 1000 ) ) / 3600 );
}

static void setGKMask( CMaskEdit& rCtl ) {
	rCtl.SetMask( _T("6-999.999,999") );
	rCtl.SetPromptChar( _T("0") );
}
static void setGKValue( CMaskEdit& rCtl, const double &val ) {
	double	v, vv, v1, v2, v3, rest;
	v = val;
	v = modf( v, &vv ); rest = v * 1000; v = vv / 1000;
	v = modf( v, &vv ); v3 = v * 1000; v = vv / 1000;
	v = modf( v, &vv ); v2 = v * 1000; v = vv / 1000;
	v = modf( v, &vv ); v1 = v * 1000; v = vv / 1000;
	rest = floor( rest + 0.5 );
	v3 = floor( v3 + 0.5 );
	v2 = floor( v2 + 0.5 );
	v1 = floor( v1 + 0.5 );
	if( rest < 1 ) rest *= 1000;
	else if( rest < 10 ) rest *= 100;
	else if( rest < 100 ) rest *= 10;
	CString	S;
	S.Format( _T("%1d-%03d.%03d,%03d"), (short) v1, (short) v2, (short) v3, (short) rest );
	rCtl.SetText( _T(','), S );
}
static void getGKValue( double &val, CMaskEdit &rCtl ) {
	CString	S;
	S = rCtl.GetText( _T(',') );
	if( S.Find( _T(',') ) )
		S.SetAt( S.Find( _T(',') ), _T('.') );
	val = atof( S );
}

bool	CPpgBase::MEInitMask( CMaskEdit& rCtl ) {
//	_ASSERTE( m_pParent->m_pCS );
//	TRIASCSTYPE	t;
//	m_pParent->m_pCS->get_CoordSystemType( &t );
//	if( tcsCS_Geographic == t ) {
		setDMSMask( rCtl );
//	} else if( tcsCS_Projected == t ) {
//		setGKMask( rCtl );
//	} else {
//		_ASSERTE( !_T("Unknown Coordsystem") );
//	}
	return true;
}

bool	CPpgBase::MESetValue( CMaskEdit& rCtl, const double& val ) {
//	_ASSERTE( m_pParent->m_pCS );
//	TRIASCSTYPE	t;
//	m_pParent->m_pCS->get_CoordSystemType( &t );
//	if( tcsCS_Geographic == t ) {
		setDMSValue( rCtl, val );
//	} else if( tcsCS_Projected == t ) {
//		setGKValue( rCtl, val );
//	} else {
//		_ASSERTE( !_T("Unknown Coordsystem") );
//	}
	return true;
}

bool	CPpgBase::MEGetValue( double& val, CMaskEdit& rCtl ) {
//	_ASSERTE( m_pParent->m_pCS );
//	TRIASCSTYPE	t;
//	m_pParent->m_pCS->get_CoordSystemType( &t );
//	if( tcsCS_Geographic == t ) {
		getDMSValue( val, rCtl );
//	} else if( tcsCS_Projected == t ) {
//		getGKValue( val, rCtl );
//	} else {
//		_ASSERTE( !_T("Unknown Coordsystem") );
//	}
	return true;
}

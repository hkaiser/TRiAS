// QueryPar.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "numedit.h"	// CRealEdit
#include "ErzPar.h"		// CErzeugerParam
#include "resultp.h"	// CResultParam
#include "branchep.h"	// CBrancheParam
#include "gebietp.h"	// CGebietParam
#include "AbfallP.h"	// CAbfallParam

#include "QueryPar.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globale Konstanten
QueryParameter QueryParameterField [] = 
{
//	ValueType, PageType, Name
	{ "prmErzeugernummer",		dbText,		ErzeugerPage},
	{ "prmBranchennummer",		dbText,		BranchenPage},			
	{ "prmAlleBranchen",		dbBoolean,	BranchenPage},			
	{ "prmGemeindekennzahl",	dbText,		GebietsPage},
	{ "prmKreis",				dbText,		GebietsPage},			
	{ "prmAlleGemeinden",		dbBoolean,	GebietsPage},
	{ "prmAlleKreise",			dbBoolean,	GebietsPage},
	{ "prmNurSonderabfälle",	dbBoolean,	AbfallPage},
	{ "prmMengenschwelle",		dbSingle,	AbfallPage},
	{ "prmAbfallart",			dbText,		AbfallPage},
	{ "prmAlleAbfallarten",		dbBoolean,	AbfallPage},
	{ NULL, 0, NoPage }
};

/////////////////////////////////////////////////////////////////////////////
// CEnterQueryParam dialog
CEnterQueryParam::CEnterQueryParam(CWnd* pParent /*=NULL*/)
	: CDialog(CEnterQueryParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEnterQueryParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CEnterQueryParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterQueryParam)
	DDX_Control(pDX, IDS_TYPE, m_stType);
	DDX_Control(pDX, IDS_INFOTEXT, m_stInfoText);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDE_PARAM, m_edParam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterQueryParam, CDialog)
	//{{AFX_MSG_MAP(CEnterQueryParam)
	ON_EN_CHANGE(IDE_PARAM, OnChangeParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterQueryParam message handlers

BOOL CEnterQueryParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	m_btOk.EnableWindow (FALSE);
	CString strInfo;
	AfxFormatString1 (strInfo, IDS_QUERY_PARAM_INFO, m_varParamInfo.m_strName);	
	m_stInfoText.SetWindowText (strInfo);

//	vordefinierten Wert setzen
	CString strVal;
	GetQueryParamValue (m_varParamInfo, strVal); 
	m_edParam.SetWindowText (strVal);

//	Datentyp ausgeben
	CString strTypeName (GetFieldType (m_varParamInfo.m_nType));
	if (strTypeName.IsEmpty ())
	{
	//	Info an Nutzer ausgeben
		CString strError;
		AfxFormatString1 (strError, IDS_UNKNOWN_DATA_TYPE, m_varParamInfo.m_strName);
		MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONSTOP); 
		AfxThrowUserException ();
	}

//	ggf. Hilfstext anhängen
	CString strType, strHelp;
	switch (m_varParamInfo.m_nType)
	{
		case dbBoolean:
			VERIFY (strHelp.LoadString (IDS_BOOL_VALUES));
		break;
		case dbDate:
			VERIFY (strHelp.LoadString (IDS_DATE_VALUES));
		break;
	}
	
//	Extension anhängen
	if (!strHelp.IsEmpty ())
		strTypeName += " " + strHelp;			

	AfxFormatString1 (strType, IDS_TYPE_PARAM, strTypeName);
	m_stType.SetWindowText (strType);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEnterQueryParam::OnChangeParam() 
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (m_edParam.LineLength () > 0);	
}

void CEnterQueryParam::OnOK() 
{
	// TODO: Add extra validation here
	try
	{
		CString strValue;
		m_edParam.GetWindowText (strValue);
		VERIFY (WriteQueryParamValue (m_varParamInfo, strValue));
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return;
	}
	
	CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
// CQueryParams

IMPLEMENT_DYNAMIC(CQueryParams, CPropertySheet)
/*
CQueryParams::CQueryParams(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}
*/

CQueryParams::CQueryParams(CDaoQueryDef *pQueryDef, CWnd* pParentWnd,
						   LPCTSTR pszCaption, UINT iSelectPage)
						   
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	ASSERT (NULL != pQueryDef && pQueryDef -> IsOpen ());
	
//	Wizzard config.
	int iCnt = pQueryDef -> GetParameterCount();
	ASSERT (iCnt > 0);

	CDaoParameterInfo Info;
	int iPageCnt = NoPage;		//	Zähler für bereits hinzugefügte Seiten
	int iActPage = NoPage;		//	akt. Seite
	QueryParameter *pFieldInfo = NULL;
	for (int iIndex = 0; iIndex < iCnt; iIndex++)
	{
	//	lese Parameterwert
		pQueryDef->GetParameterInfo (iIndex, Info, AFX_DAO_SECONDARY_INFO);

	//	suche Namen des Parameters in Liste
		iActPage = NoPage;		
		for (pFieldInfo = QueryParameterField; pFieldInfo->pName && *pFieldInfo->pName; pFieldInfo++)
		{
		//	Name un Typ müssen stimmen
			if ((0 == Info.m_strName.CompareNoCase (pFieldInfo->pName)) &&
				(Info.m_nType == pFieldInfo -> iValType))
			{
				iActPage = pFieldInfo -> tpPage;
				break;
			}				
		}

	//	wenn ein gültiger Parameter, wurde zugeh. Seite schon hinzugefügt
		if ((iActPage != NoPage) && (iPageCnt & iActPage))
			continue;		//	weiter mit dem nächsten Parameter

	//	Seiten aktivieren
		switch (iActPage)
		{
			case ErzeugerPage:
			{
				m_pgErzeugerParam.m_pQueryDef = pQueryDef;
				AddPage (&m_pgErzeugerParam);
			}
			break;
			case BranchenPage:
			{
				m_pgBranchenParam.m_pQueryDef = pQueryDef;
				AddPage (&m_pgBranchenParam);
			}
			break;
			{
			case GebietsPage:
				m_pgGebietParam.m_pQueryDef = pQueryDef;
				AddPage (&m_pgGebietParam);
			}
			break;
			case AbfallPage:
			{
				m_pgAbfallParam.m_pQueryDef = pQueryDef;
				AddPage (&m_pgAbfallParam);
			}
			break;
			default:
			{
				CEnterQueryParam Dlg (this);
				Dlg.m_varParamInfo = Info;
				if (IDOK != Dlg.DoModal ())
					AfxThrowUserException ();				
				pQueryDef->SetParamValue(Info.m_strName, Dlg.m_varParamInfo.m_varValue);
			}
		}	//	end_switch

	//	Seite ggf. speichern
		if (iActPage != NoPage)
			iPageCnt |= iActPage;
	}

//	die Ergebnisseite immer hinzunehmen
	m_pgResultParam.m_pQueryDef = pQueryDef;
	AddPage (&m_pgResultParam);
}

CQueryParams::~CQueryParams()
{
}

BEGIN_MESSAGE_MAP(CQueryParams, CPropertySheet)
	//{{AFX_MSG_MAP(CQueryParams)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryParams message handlers

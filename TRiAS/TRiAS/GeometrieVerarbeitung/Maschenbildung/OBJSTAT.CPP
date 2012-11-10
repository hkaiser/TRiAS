// objstat.cpp : implementation file
//

#include "pheader.h"		//	prec. Header
#include "resource.h"		//	Ressourcen

//	STL-Header
#include <ospace/com/smartif.h>			

//	TRIAS-Header
#include <xtensnx.h>		// DEX_GetObjectType ()
#include <IGeometr.hxx>		// IObjektGeometrie

//	GUID-Header
#include <eonrguid.h>		
#include <triashelper.h>
#include <objgguid.h>		// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie

//	Projekt-Header
// #include "tools.hpp"		// HasGeoError () 
#include "geoobjs.hpp"		// IsClear ()
#include "objstat.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// extern void TestIMaschen (IEnumObjectsByNumber *);

/////////////////////////////////////////////////////////////////////////////
// CObjStatDlg property page

IMPLEMENT_DYNCREATE(CObjStatDlg, CPropertyPage)

CObjStatDlg::CObjStatDlg() : CPropertyPage(CObjStatDlg::IDD)
{
	//{{AFX_DATA_INIT(CObjStatDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lGeoErrCnt = m_lTexteCnt = m_lPointCnt = m_lLineCnt = m_lAreaCnt = 0L;
	m_pIEnumObjs = NULL;		// Eingabestrom
	m_dwFlags = 0;				// Dialog-Flags
}

CObjStatDlg::~CObjStatDlg()
{
	if (m_pIEnumObjs)
	{
		m_pIEnumObjs -> Release ();
		m_pIEnumObjs = NULL;
	}
}

void CObjStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CObjStatDlg)
	DDX_Control(pDX, IDT_TEXTCNT, m_stTexteCnt);
	DDX_Control(pDX, IDT_SUMME, m_stSumCnt);
	DDX_Control(pDX, IDT_PKTCNT, m_stPointCnt);
	DDX_Control(pDX, IDT_LINCNT, m_stLineCnt);
	DDX_Control(pDX, IDT_GEO_ERROR, m_stGeoErrCnt);
	DDX_Control(pDX, IDT_FLCNT, m_stAreaCnt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CObjStatDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CObjStatDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CObjStatDlg message handlers

BOOL CObjStatDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	if (!m_pIEnumObjs)
		VERIFY (S_OK == CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
										  IID_IEnumObjectsByNumber, (LPVOID *)&m_pIEnumObjs));

	char Buffer [20] = "";
	m_stAreaCnt.SetWindowText (ltoa (m_lAreaCnt, Buffer, 10));
	m_stLineCnt.SetWindowText (ltoa (m_lLineCnt, Buffer, 10));
	m_stPointCnt.SetWindowText (ltoa (m_lPointCnt, Buffer, 10));
	m_stTexteCnt.SetWindowText (ltoa (m_lTexteCnt, Buffer, 10));
	m_stGeoErrCnt.SetWindowText (ltoa (m_lGeoErrCnt, Buffer, 10));
	m_stSumCnt.SetWindowText (ltoa (m_lAreaCnt+m_lLineCnt+m_lPointCnt+m_lTexteCnt+m_lGeoErrCnt, 
									Buffer, 10));

//	TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CObjStatDlg * CObjStatDlg::CreateInstance ()
{
	CObjStatDlg *pDlg = NULL;

	try
	{
		pDlg = new CObjStatDlg ();
	}
	catch (CMemoryException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return NULL;
	}

	return pDlg;
}

BOOL CObjStatDlg::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetButtons ();
	
	return CPropertyPage::OnSetActive();
}

void CObjStatDlg::SetButtons (void)
{
	CPropertySheet *pSheet = GetPropertySheet();
	if (NULL == pSheet)
		return;

	DWORD dwBttns = 0;
	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_FINISH;
	else
		dwBttns |= PSWIZB_NEXT;
	
	pSheet -> SetWizardButtons (dwBttns);
}

// liest Objektmenge
HRESULT CObjStatDlg::GetEnumLONG (IEnumObjectsByNumber **ppIEnum)
{
	if (NULL == ppIEnum) 
		return E_POINTER;
	if (NULL == m_pIEnumObjs) 
		return E_OUTOFMEMORY;

//	IEnumObjectsByNumber abfragen
	return m_pIEnumObjs -> QueryInterface (IID_IEnumObjectsByNumber, (LPVOID *)ppIEnum);
}

// übergibt Objektmenge
HRESULT CObjStatDlg::SetEnumLONG (IEnumObjectsByNumber *pIEnum)
{
//	prüfe Parameter
	if (NULL == pIEnum)
		return E_POINTER;
		
	if (!m_pIEnumObjs)
		VERIFY (S_OK == CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
										  IID_IEnumObjectsByNumber, (LPVOID *)&m_pIEnumObjs));
	
	try
	{
		long lONr = 0;

	//	alle fehlerfreien Kanten speichern
		HRESULT hrt = NO_ERROR;
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) 
		{
			ASSERT (lONr > 0);
			
			switch (DEX_GetObjectType (lONr))
			{
				case OGFlaeche:
					m_lAreaCnt++;
				break;
				case OGLinie:
					m_lLineCnt++;
				break;
				case OGText:
					m_lTexteCnt++;
				break;
				case OGPunkt:
					m_lPointCnt++;
				break;
				default:
					ASSERT (FALSE);
				break;
			}
			
			// if (HasGeoError (lONr))
			CGeometrieObject GO (lONr);
			hrt = GO.m_wIObjGeo -> IsClear ();
			if (S_FALSE == hrt)
				m_lGeoErrCnt++; 
				
		//	Objekt-Nummer im Ausgabe-Strom speichern
			m_pIEnumObjs -> AddItem (lONr);
		}

		// TestIMaschen (m_pIEnumObjs);
	}
	catch (_com_error& hr)
	{
		DEX_Error (RC_Maschenbildung, EC_SYSERROR);
		return _COM_ERROR (hr);
	}
	catch (CMemoryException *me)
	{
		DEX_Error (RC_Maschenbildung, EC_NOMEMORY);		
		me -> Delete ();
		return E_OUTOFMEMORY; 	
	}
	
	return NOERROR;
}

// Verparam.cpp : implementation file
//
#include "pheader.h"			//	vorübersetzter Header
#include "resource.h"			//	Resource-Konstanten

//	STL-Header
#include <ospace/com/smartif.h>			
#include <ospace/com/iterenum.h>
#include <ospace/std/list>		// list

//	GUID-Header
#include <xtsnguid.h>
#include <objgguid.h>			//	CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include "verguid.h"			//	zugeh. GUID-Header
#include <triashelper.h>
#include <initguid.h>
#include <operguid.h>			//	CLSID_GeometrieOperationen

//	TRIAS-Header
#include <hpp/propactb.hpp>			//	Basisklasse		// fje
#include <ienumobj.hxx>			//	IEnumLONG

//	Projekt-Header
#include <IGeometr.hxx>			//	IExtendObjOper
#include "verschnt.hpp"			//	CVerschnittPropAct
#define _NO_PARAM_DIAOLOG
#include "paramdlg.hpp"			//	CParameters
#include "objkante.hpp"			//	CObjektKante
#include "Verparam.hpp"			//	zugeh. Header
#include "tools.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface (ExtendObjOper);
DefineSmartInterface (ProgressIndicator2);
DefineSmartInterface (ConnectionPoint);
DefineSmartInterface (ConnectionPointContainer);
DefineSmartInterface (EnumLONG);

//	externe Funktionen
extern double GetNewDeltaPos (int iDelta, double OldFuzzy);

/////////////////////////////////////////////////////////////////////////////
// CVerschnittPage property page
IMPLEMENT_DYNCREATE(CVerschnittPage, CPropertyPage)

CVerschnittPage::CVerschnittPage() : CPropertyPage(CVerschnittPage::IDD)
{
	//{{AFX_DATA_INIT(CVerschnittPage)
	//}}AFX_DATA_INIT
	m_pAction = NULL;
	m_dwFlags = 0;
	m_bDeleteLines = FALSE;
	m_bMarkLines = FALSE;

	m_Params.Init (m_dFuzzy, &m_dDangleLen);	//	Nutzer-Fuzzy und DangleLänge berechnen lassen
}

void CVerschnittPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVerschnittPage)
	DDX_Control(pDX, IDC_MARK_OBJECTS, m_btMarkObjects);
	DDX_Control(pDX, IDB_DELETE_LINES, m_btDeleteLines);
	DDX_Control(pDX, IDE_DANGLE_LEN, m_edDangleLen);
	DDX_Control(pDX, IDT_DESCRIPTION, m_stDescription);
	DDX_Control(pDX, IDE_FUZZY, m_edFuzzy);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVerschnittPage, CPropertyPage)
	//{{AFX_MSG_MAP(CVerschnittPage)
	ON_NOTIFY(UDN_DELTAPOS, IDB_FUZZY, OnDeltaposFuzzy)
	ON_EN_CHANGE(IDE_FUZZY, OnChangeFuzzy)
	ON_EN_SETFOCUS(IDE_FUZZY, OnSetfocusFuzzy)
	ON_EN_CHANGE(IDE_DANGLE_LEN, OnChangeDangleLen)
	ON_EN_SETFOCUS(IDE_DANGLE_LEN, OnSetfocusDangleLen)
	ON_NOTIFY(UDN_DELTAPOS, IDB_DANGLE_LEN, OnDeltaposDangleLen)
	ON_BN_CLICKED(IDB_DELETE_LINES, OnDeleteLines)
	ON_BN_CLICKED(IDC_MARK_OBJECTS, OnMarkObjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVerschnittPage message handlers

BOOL CVerschnittPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetButtons ();
	
	return CPropertyPage::OnSetActive();
}

BOOL CVerschnittPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	char Buffer [50] = "";
	DtoA (m_dFuzzy, Buffer);
	m_edFuzzy.SetWindowText (Buffer);

	DtoA (m_dDangleLen, Buffer);
	m_edDangleLen.SetWindowText (Buffer);

	m_btDeleteLines.SetCheck (m_bDeleteLines);
	m_btMarkObjects.SetCheck (m_bMarkLines);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Fuzzy-Toleranze setzen
void CVerschnittPage::SelectFuzzy (double dFuzzy)
{
	ASSERT (dFuzzy >= 0.0);

	m_dFuzzy = dFuzzy;
	if (m_hWnd && IsWindowVisible ())
	{
		char Buffer [50] = "";
		DtoA (m_dFuzzy, Buffer);
		m_edFuzzy.SetWindowText (Buffer);
	}
}

//	DangleLänge setzen
void CVerschnittPage::SelectDangleLen (double dDangleLen)
{
	ASSERT (dDangleLen >= 0.0);

	m_dDangleLen = dDangleLen;
	if (m_hWnd && IsWindowVisible ())
	{
		char Buffer [50] = "";
		DtoA (m_dDangleLen, Buffer);
		m_edDangleLen.SetWindowText (Buffer);
	}
}

void CVerschnittPage::SetButtons (void)
{
	CPropertySheet *pSheet = GetPropertySheet();
	if (NULL == pSheet)
		return;

	DWORD dwBttns = 0;
	int iCnt = (m_dFuzzy >= 0.0) && (m_dDangleLen >= 0.0);

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (0 < iCnt /*&& !bDisableNext*/) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons (dwBttns);
}

// liest Objektmenge
HRESULT CVerschnittPage::GetEnumLONG (WEnumObjectsByNumber &WEnum)
{
//	prüfe Listeneinträge
	if (m_OutNrListe.empty ())
		return S_OK;

//	ansonsten immer 1. Element zurück
	WEnum = m_OutNrListe.front ();
	m_OutNrListe.pop_front ();	//	dieses Objekt löschen

	return m_OutNrListe.empty () ? S_OK : S_FALSE;
}

// Page erzeugen
CVerschnittPage *CVerschnittPage::CreateInstance (CVerschnittPropAct *pAction)		
{
	ASSERT (NULL != pAction);

	CVerschnittPage *pDlg = NULL;

	try
	{
		pDlg = new CVerschnittPage ();
	}
	catch (CMemoryException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return NULL;
	}
	pDlg -> m_pAction = pAction;

	return pDlg;
}

// übergibt Objektmenge und führt Verschnitt aus
HRESULT CVerschnittPage::SetEnumLONG (IEnumObjectsByNumber *pIEnum)
{
	if (!pIEnum)
		return E_POINTER;
	
	HRESULT hr = NOERROR;
	DWORD dwCookie = 0;
	WConnectionPoint CP;
	
	try
	{
		long lONr = 0;
		long lCnt = 0;
		long lFirstONr = 0;
		
	//	alle Punkte, Linien, Flächen speichern
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) 
		{
			ASSERT (lONr > 0);
			
			switch (DEX_GetObjectType (lONr))
			{
				case OGLinie:
				case OGPunkt:
				case OGFlaeche:
				{
					lCnt++;
					if (1 == lCnt)
						lFirstONr = lONr;		// 1. Obj-Nummer merken
				}
				break;
			}
		}

	//	wenigstens 1 Objekt in Liste ? (evtl. mit Selbstinzidenz)
		if (lCnt < 1)
			return NOERROR;

	//	Geometrie des 1. Objektes lesen
		CObjektKante Kante (lFirstONr);				
		long *pX = NULL;
		long *pY = NULL;
		Kante.GetGeometrie (&pX, &pY);
		ASSERT (NULL != pX);
		ASSERT (NULL != pY);
		
	//	Toleranzen berechnen
		m_Params.CalculateTolerances (pX [0], pY [0], m_dFuzzy, &m_dDangleLen);

		ASSERT (NULL != g_pTE);
		ASSERT (NULL != g_pTE -> m_pXtnSite);

	//	Indicator init.
		WProgressIndicator2 PI (CLSID_ProgressIndicator);
	
	//	Indicator init.: Parent setzen
		HWND hWnd = NULL;
		hr = PI -> InitNew ((LONG)(m_hWnd ? m_hWnd : g_pTE -> MWind () -> m_hWnd), 0L, (LONG *)&hWnd);
		if (FAILED(hr)) 
			_com_issue_error (hr);
			
	//	Interface von Wolfgang besorgen
		WExtendObjOper wObjOper;
		hr = g_pTE -> m_pXtnSite -> GetXtension (CLSID_GeometrieOperationen, 
												 IID_IExtendObjOper, wObjOper.ppv ());
		if (FAILED(hr))
			_com_issue_error (hr);

	//	Connectionpoint init.
		try
		{
			WConnectionPointContainer CPC (wObjOper);		//	throw hr
			hr = CPC -> FindConnectionPoint (IID_IProgressIndicator2, CP.ppi ());
			if (FAILED(hr))
				_com_issue_error (hr);
			hr = CP -> Advise (PI, &dwCookie);
			if (FAILED(hr))
				_com_issue_error (hr);
		}
		catch (_com_error&)
		{
		//	nur auffangen
		}			

	//	Objekte verschneiden 
		WEnumLONG wInput = pIEnum;		
		WEnumLONG wEnumOutObjs;
		WEnumLONG wEnumDelObjs;
		hr = wObjOper -> Splitting (wInput, m_Params.GetXFuzzy (), m_Params.GetYFuzzy (),
								 m_Params.GetDangleLen (), wEnumOutObjs.ppi(),
								 (m_bDeleteLines || m_bMarkLines) ? wEnumDelObjs.ppi() : NULL);
		if (FAILED(hr))
			_com_issue_error (hr);

	//	Elemente speichern
		if (wEnumOutObjs->Count () > 0)
		{
			WEnumObjectsByNumber WEnumObjs = wEnumOutObjs;
			m_OutNrListe.push_back (WEnumObjs);
		}
		
	//	Ursprungsobjekte ggf. löschen
		if ((S_OK == hr) && (m_bDeleteLines || m_bMarkLines))
		{
			PIFLAGS Flags = (PIFLAGS) (PIFLAGS_STATUS | PIFLAGS_TIME | PIFLAGS_ADJUSTPERCENT |
									   PIFLAGS_INIT_SHOWWINDOW);

		//	min, max neu setzen
			ULONG ulCnt = wEnumDelObjs -> Count ();
			HRESULT hr = PI -> Restart (1L, ulCnt, Flags);
			if (FAILED(hr)) 
				_com_issue_error (hr);

		//	Indicator neu init.: Caption setzen			
			CString strText;
			VERIFY (strText.LoadString (m_bDeleteLines ? IDS_CAPTION_DEL_VERSCHN : IDS_CAPTION_MARK_OBJECTS));
			COleVariant varText (strText);
			hr = PI -> ChangeText (PIFLAGS_CAPTION, (BSTR) varText.pbVal);
			if (FAILED(hr)) 
				_com_issue_error (hr);

		//	Adjust-Text setzen
			VERIFY (strText.LoadString (IDS_STATUS_STAND));
			varText = strText;
			hr = PI -> ChangeText (PIFLAGS_ADJUSTPERCENT, (BSTR) varText.pbVal);
			if (FAILED(hr)) 
				_com_issue_error (hr);

		//	löschen/markieren der Objekte
		//	MerkmalsCode besorgen
			CString strMark;
			VERIFY(strMark.LoadString (IDS_MARK_OBJECT_LINK));

			int iPercent = 0;
			for (wEnumDelObjs -> Reset(); S_OK == wEnumDelObjs -> Next (1, &lONr, NULL); /**/) 
			{
			//	Nutzerabbruch ?
				hr = PI -> IsCanceled ();			
				if (FAILED(hr)) 
					_com_issue_error (hr);
				if (S_OK == hr)	
					break;

			//	nächste Position				
				hr = PI -> IncrementPosition (&iPercent);
				if (FAILED(hr)) 
					_com_issue_error (hr);

			//	Objekt löschen					
				ASSERT (lONr > 0);						//	Objektnummer ok ?
				if (m_bMarkLines) {
					ULONG ulMCode = GetMerkmalsKode(lONr, IDS_MARKOBJECT_HDR, IDS_MARKOBJECT_PBD, TRUE);
					ASSERT (0 != ulMCode);
					ASSERT ((ULONG)-1 != ulMCode);
					if (0 == ulMCode || (ULONG)-1 == ulMCode)
						continue;
					VERIFY (EC_OKAY == OutputMerkmal (lONr, ulMCode, strMark));
				} else
				//	Objekt löschen
					VERIFY (DEX_DeleteObjectEx (lONr));		//	undo berücksichtigen
			}
		}
	}
	catch (_com_error& hre)
	{
		DEX_Error (RC_Maschenbildung, EC_SYSERROR);
		hr = _COM_ERROR (hre);
	}
	catch (CMemoryException *me)
	{
		DEX_Error (RC_Maschenbildung, EC_NOMEMORY);		
		me -> Delete ();
		hr = E_OUTOFMEMORY; 	
	}

//	Interface freigeben
	if (dwCookie > 0)
		CP -> Unadvise (dwCookie);			
		
	return hr;
}

//	Beschreibungstext ausgeben
void CVerschnittPage :: OutputDescription (UINT uiResID)
{
	CString strText;
	VERIFY (strText.LoadString (uiResID));
	m_stDescription.SetWindowText (strText);
}

void CVerschnittPage::OnSetfocusFuzzy() 
{
	// TODO: Add your control notification handler code here
	OutputDescription (IDS_FANG_BEREICH_VER);	
}

void CVerschnittPage::OnSetfocusDangleLen() 
{
	// TODO: Add your control notification handler code here
	OutputDescription (IDS_DANGLE_DESCR);	
}

void CVerschnittPage::OnChangeDangleLen() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edDangleLen.GetWindowText (strText);
	m_dDangleLen = atof (strText);
	SetButtons ();

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);	
}

void CVerschnittPage::OnChangeFuzzy() 
{
// TODO: Add your control notification handler code here
	CString strText;
	m_edFuzzy.GetWindowText (strText);
	m_dFuzzy = atof (strText);
	SetButtons ();

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

void CVerschnittPage::OnDeltaposDangleLen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

//	akt. Wert lesen
	CString strActVal;
	m_edDangleLen.GetWindowText (strActVal);
	m_dDangleLen = atof (strActVal);

//	neuen Wert berechnen
	m_dDangleLen = GetNewDeltaPos (pNMUpDown -> iDelta, m_dDangleLen);

//	neuen Wert setzen
	char Buffer [50] = "";
	DtoA (m_dDangleLen, Buffer);
	m_edDangleLen.SetWindowText (Buffer);

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);	

	*pResult = 0;
}

void CVerschnittPage::OnDeltaposFuzzy(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

//	akt. Wert bestimmen
	CString strActVal;
	m_edFuzzy.GetWindowText (strActVal);
	m_dFuzzy = atof (strActVal);

//	neuen Wert berechnen
	m_dFuzzy = GetNewDeltaPos (pNMUpDown -> iDelta, m_dFuzzy);

//	neuen Wert setzen
	char Buffer [50] = "";
	DtoA (m_dFuzzy, Buffer);
	m_edFuzzy.SetWindowText (Buffer);

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);	

	*pResult = 0;
}

void CVerschnittPage::OnDeleteLines() 
{
	// TODO: Add your control notification handler code here
	m_bDeleteLines = m_btDeleteLines.GetCheck ();
	OutputDescription (m_bDeleteLines ? IDS_DELETE_VER_OBJS : IDS_DELETE_LINES_NOT);

	if (m_bDeleteLines)
		m_btMarkObjects.SetCheck (FALSE);
	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);		
}

void CVerschnittPage::SelectDeleteOldLines (BOOL bFlag)
{
	m_bDeleteLines = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btDeleteLines.SetCheck (m_bDeleteLines);
}

void CVerschnittPage::SelectMarkOldLines (BOOL bFlag)
{
	m_bMarkLines = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btMarkObjects.SetCheck (m_bMarkLines);
}

void CVerschnittPage::OnMarkObjects() 
{
	// TODO: Add your control notification handler code here
	m_bMarkLines = m_btMarkObjects.GetCheck();
	OutputDescription (m_bMarkLines ? IDS_MARK_OBJECTS_LIN : IDS_MARK_OBJECTS_NOT_LIN);

	if (m_bMarkLines)
		m_btDeleteLines.SetCheck (FALSE);

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

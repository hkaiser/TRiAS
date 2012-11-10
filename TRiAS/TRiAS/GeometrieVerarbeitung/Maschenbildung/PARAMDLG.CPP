// ParamDialog.cpp : implementation file
//
#include "pheader.h"			// vorübersetzter Header
#include "resource.h"			// Resource-Konstanten

#include <xtensnn.h>

//	STL-Header
#include <ospace/std/list>		// list
#include <ospace/std/map>		// map
#include <ospace/com/smartif.h>			

//	TRiAS-Header
#include <dblpair.hxx>			// DoublePair
#include <ctfxmfc.h>			// CCoordTransX
#include <IGeometr.hxx>			// IObjektGeometrie

//	allg. Header
#include <float.h>				// DBL_MIN, DBL_MAX
#include <math.h>				// sqrt ()

//	GUID-Header
#include <objgguid.h>			// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <xtsnguid.h>
#include <triashelper.h>
#include "linaguid.h"
#include "linvguid.h"

//	Projekt-Header
#include "linver.hpp"			// CLinVerExtension	

#include <hpp/progrsst.hpp>		// CProgressIndicator

#include <hpp/propactb.hpp>		// Basisklasse		// fje
#include "linvprp.hpp"			// CLinVerPropAct

#include "objkante.hpp"			// CObjektKante
#include "ParamDlg.hpp"			// zugeh. Header
#include "maschbil.hpp"			// CMaschenBildung
#include "tools.hpp"

#include <limits.h>				// für ULONG_MAX

#if _MSC_VER >= 1100
#include <new>
using std::bad_alloc;
#endif // _MSC_VER >= 1100

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
//	Konstanten
const double MinExt = 100;			// minimale Ausdehnung des Projektes in X/Y-Richtung
const double LowFuzzy = 0.0;		// Fuzzy für obige Ausdehnung
const int FuzzyVal = 10000;			// zur Berechnung der Fuzzy-Toleranz



///////////////////////////////////////////////////////////////////////////////////////////////
//	globale Funktionen
double GetNewDeltaPos (int iDelta, double dFuzzy)
{
	double dDelta = 0;
	if (dFuzzy < 0)
		dFuzzy = 0.0;

//	Schrittweite bestimmen
	if (iDelta < 0) 
	{
		if (dFuzzy >= 100.0)
			dDelta = 100.0;
		else if (dFuzzy >= 10.0)
			dDelta = 10.0;
		else if (dFuzzy >= 1.0)
			dDelta = 1.0;
		else if (dFuzzy >= 0.1)
			dDelta = 0.1;
		else if (dFuzzy >= 0.01)
			dDelta = 0.01;
		else
			dDelta = 0.01;
	} 
	else 
	{
		if (dFuzzy > 100.0)
			dDelta = -100.0;
		else if (dFuzzy > 10.0)
			dDelta = -10.0;
		else if (dFuzzy > 1.0)
			dDelta = -1.0;
		else if (dFuzzy > 0.1)
			dDelta = -0.1;
		else if (dFuzzy > 0.01)
			dDelta = -0.01;
		else
			dDelta = -0.01;
	} 		

//	Wert muß größer als 0 sein
	if (dFuzzy + dDelta <= 0.0) 
		dFuzzy = 0.0;
	else
		dFuzzy += dDelta;

	return dFuzzy;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//	CParameters
CParameters :: CParameters (void)
{
	m_ulOldUnIdent = m_ulNewUnIdent = (ULONG)-1;	// ungültige Werte
	m_ulDangleLen = m_ulXFuzzy = m_ulYFuzzy = 0;	// Test auf gleiche Koordinate
}


// --------------------------------------------------------------------------------------------
void CParameters :: ReadNewUnIdent (void)
{
//	hole von TRIAS Merkmalskode für neuen UniqueIdent
// holen wird später erledigt, wenn MCode benötigt wird (#HK980907)
//	CString strMText;
//	VERIFY (strMText.LoadString (IDS_VEREINIGTE_IDENTS));
//	m_ulNewUnIdent = DEX_GetMCodeFromFeatureNameCI ((char *)(const char *)strMText);
//	if (m_ulNewUnIdent <= 0)						// wenn noch nicht vergeben
//		m_ulNewUnIdent = DEX_GetUniqueSysMCode();	// neuen Merkmalskode von TRiAS holen
//
//	prüfe diesen Kode	
//	ASSERT (0 != m_ulNewUnIdent);
//	ASSERT ((ULONG)-1 != m_ulNewUnIdent);
}


// --------------------------------------------------------------------------------------------
//	interne Werte init.
BOOL CParameters :: Init (void)
{
// nach CMaschenBildung::CreateMaschen() bzw. CMaschenBildung::CreateLines() verlegt, da hPr
// hier noch nicht bekannt
	return TRUE;
}


// --------------------------------------------------------------------------------------------
BOOL CParameters :: Init (double &dFuzzy, double *pdDangleLen /* = NULL*/)
{
	Init ();

//	lese (GeoDB)-Projekt-Container
CObjContainer oc;

	DEX_GetProjectCont (oc);
		
//	bestimme Fuzzy-Toleranz
CCoordTransX transf;	
DoublePair dpMin, dpMax;

	VERIFY (transf.UnScale (oc.XMin (), oc.YMin (), &dpMin.X (), &dpMin.Y ()));
	VERIFY (transf.UnScale (oc.XMax (), oc.YMax (), &dpMax.X (), &dpMax.Y ()));

//	max ((Xmax - Xmin), (Ymax - Ymin)) / 10000
//	liegt Container zwischen 1 und 100 --> 0.002
double dMinExtX, dMinExtY;

	VERIFY (transf.CoordTransDistanceEx (&dpMin, &dpMax, dMinExtX, dMinExtY));
	
	if ((dMinExtX <= MinExt) || (dMinExtY <= MinExt))
		dFuzzy = LowFuzzy;
	else
		dFuzzy = max (dMinExtX, dMinExtY) / FuzzyVal;

	dFuzzy = fabs (dFuzzy);	// vorsichtshalber

	if (pdDangleLen)
		*pdDangleLen = dFuzzy / 2.0;

// dFuzzy und pdDangleLen auf 2 gültige Ziffern und höchstens 2 Kommastellen runden
double k = 1.;

	while (dFuzzy >= k)
		k *= 10.;
	dFuzzy = floor (100./k * (dFuzzy + 0.005*k)) * k/100.;
			
	if (pdDangleLen)
	{
		k = 1.;
		while (*pdDangleLen >= k)
			k *= 10.;
		*pdDangleLen = floor (100./k * (*pdDangleLen + 0.005*k)) * k/100.;
	}
			
	return TRUE;
}


// --------------------------------------------------------------------------------------------
//	Toleranzen in Datenbankeinheiten berechnen
//	Koordinate eines bel. Objektes
HRESULT CParameters::CalculateTolerances (CObjektKante &Kante, double dFuzzy,
										  double *pDangleLen /*NULL*/)
{
	long lCnt = 0;
	long *pX = NULL;
	long *pY = NULL;

	Kante.GetGeometrie (&pX, &pY, &lCnt);
	ASSERT (NULL != pX);
	ASSERT (NULL != pY);
	ASSERT (lCnt > 0);

	return CalculateTolerances (pX [0], pY [0], dFuzzy, pDangleLen);
}


// --------------------------------------------------------------------------------------------
HRESULT CParameters::CalculateTolerances (long lX, long lY, double dFuzzy,
										  double *pDangleLen /*NULL*/)
{

//	berechne Fuzzy-Toleranzen
	CCoordTransX transf;
	DoublePair dpKoord, dpInFuzzy (dFuzzy, dFuzzy), dpOutFuzzy;

//	Skalierung von DB-Koordinaten entfernen
	VERIFY (transf.UnScale (lX, lY, &dpKoord.X (), &dpKoord.Y ()));		

//	Berechne um Fuzzy-Tolerance entfernten Punkt
	VERIFY (transf.CoordTransRectangle (&dpKoord, &dpInFuzzy, &dpOutFuzzy));

//	Skalierung wieder hinzufügen
	KoOrd lNewKoordX, lNewKoordY;
	VERIFY (transf.Scale (dpOutFuzzy.X (), dpOutFuzzy.Y (), &lNewKoordX, &lNewKoordY));

	m_ulXFuzzy = abs (lNewKoordX - lX);
	m_ulYFuzzy = abs (lNewKoordY - lY);

	if (pDangleLen)
	{
	//	ggf. Dangle-Länge berechnen
//		DoublePair dpInDangle (*pDangleLen, *pDangleLen), dpOutDangle;
		DoublePair dpInDangle (sqrt(2.)/2.*(*pDangleLen), sqrt(2.)/2.*(*pDangleLen)), dpOutDangle;	// 05.10.99

	//	berechne um Dangle-Länge entfernten Punkt
		VERIFY (transf.CoordTransRectangle (&dpKoord, &dpInDangle, &dpOutDangle));

	//	Skalierung wieder hinzufügen
		VERIFY (transf.Scale (dpOutDangle.X (), dpOutDangle.Y (), &lNewKoordX, &lNewKoordY));
	
//		m_ulDangleLen = (ULONG) sqrt (double(((lNewKoordX-lX)*(lNewKoordX-lX))+
//											 ((lNewKoordY-lY)*(lNewKoordY-lY))));
	// #AK990811 ... verhindern wir mal lieber 'nen Überlauf...
		double	dLen = sqrt ((double)(lNewKoordX-lX) * (double)(lNewKoordX-lX) +
							 (double)(lNewKoordY-lY) * (double)(lNewKoordY-lY));

		_ASSERTE (dLen + 0.5 < (double)ULONG_MAX);

		m_ulDangleLen = (ULONG) (dLen + 0.5);
	}

	return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// CParamDialog property page
IMPLEMENT_DYNCREATE(CParamDialog, CPropertyPage)

CParamDialog::CParamDialog() : CPropertyPage(CParamDialog::IDD)
{
	//{{AFX_DATA_INIT(CParamDialog)
	//}}AFX_DATA_INIT
	m_pAction = NULL;
	m_dwFlags = 0;				// Dialog-Flags

	m_Params.Init (m_dFuzzy);	// Nutzer-Fuzzy berechnen lassen
	m_bDeleteLines = FALSE;
	m_bMarkObjects = FALSE;		// #HK971217
	m_bOutputMerkmal = m_bUnionMaschen = m_bUnionLines = TRUE;
}

CParamDialog::~CParamDialog()
{
}

void CParamDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParamDialog)
	DDX_Control(pDX, IDC_MARK_OBJECTS, m_btMarkObjects);
	DDX_Control(pDX, IDB_OUTPUT_MERKMAL, m_btOutputMerkmal);
	DDX_Control(pDX, IDT_DESCRIPTION, m_stDescription);
	DDX_Control(pDX, IDB_MASCHEN_UNION, m_btUnionMaschen);
	DDX_Control(pDX, IDB_LINES_UNION, m_btUnionLines);
	DDX_Control(pDX, IDB_DELETE_LINES, m_btDeleteLines);
	DDX_Control(pDX, IDE_FUZZY, m_edFuzzy);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CParamDialog, CPropertyPage)
	//{{AFX_MSG_MAP(CParamDialog)
	ON_EN_CHANGE(IDE_FUZZY, OnChangeFuzzy)
	ON_BN_CLICKED(IDB_DELETE_LINES, OnDeleteLines)
	ON_BN_CLICKED(IDB_LINES_UNION, OnLinesUnion)
	ON_BN_CLICKED(IDB_MASCHEN_UNION, OnMaschenUnion)
	ON_EN_SETFOCUS(IDE_FUZZY, OnSetfocusFuzzy)
	ON_NOTIFY(UDN_DELTAPOS, IDB_FUZZY, OnDeltaposFuzzy)
	ON_BN_CLICKED(IDB_OUTPUT_MERKMAL, OnOutputMerkmal)
	ON_BN_CLICKED(IDC_MARK_OBJECTS, OnMarkObjects)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CParamDialog message handlers
void CParamDialog::OnChangeFuzzy() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edFuzzy.GetWindowText (strText);
	m_dFuzzy = atof (strText);
	SetButtons ();

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

BOOL CParamDialog::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	char Buffer [50] = "";
	DtoA (m_dFuzzy, Buffer);
	m_edFuzzy.SetWindowText (Buffer);

//	Buttons setzen
	m_btUnionLines.SetCheck (m_bUnionLines);
	m_btDeleteLines.SetCheck (m_bDeleteLines);
	m_btUnionMaschen.SetCheck (m_bUnionMaschen);
	m_btOutputMerkmal.SetCheck (m_bOutputMerkmal);
	m_btMarkObjects.SetCheck (m_bMarkObjects);		// #HK971217

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParamDialog::SetButtons (void /*BOOL bDisableNext*/)
{
	CPropertySheet *pSheet = GetPropertySheet();
	if (NULL == pSheet)
		return;

	DWORD dwBttns = 0;
	int iCnt = m_dFuzzy >= 0.0 /*&& m_dDangle >= 0.0*/ && (m_bUnionMaschen || m_bUnionLines) ? 1 : 0;

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

BOOL CParamDialog::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetButtons ();
	
	return CPropertyPage::OnSetActive();
}

// Page erzeugen
CParamDialog *CParamDialog::CreateInstance (CLinVerPropAct *pAction)		
{
	ASSERT (NULL != pAction);

	CParamDialog *pDlg = NULL;

	try
	{
		pDlg = new CParamDialog ();
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

// Festlegen der Datenquelle in der alles gespeichert werden soll
HRESULT CParamDialog::SetDataSource (HPROJECT hPr)
{
	m_Params.m_hPr = hPr;
	return S_OK;
}

// übergibt Objektmenge
HRESULT CParamDialog::SetEnumLONG (IEnumObjectsByNumber *pIEnum)
{
	if (!pIEnum)
		return E_POINTER;
	
	BOOL bUserBreak = FALSE;
	try
	{
		long lONr = 0;
		m_ObjektListe.clear ();		//	alle Elemente der Liste löschen
		
	//	alle fehlerfreien Kanten speichern
		HRESULT hrt = NO_ERROR;
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/) 
		{
			ASSERT (lONr > 0);
			
			if (OGLinie != DEX_GetObjectType (lONr)) // ||		// wenn keine Linie
				 // HasGeoError (lONr))							// oder Geofehler
				continue;										// dann nächstes Objekt

		//	neues Objekt erzeugen und in Liste aufnehmen
			CObjektKante OK (lONr);
			hrt = OK.m_wIObjGeo -> IsClear ();
			if (S_OK == hrt)
				m_ObjektListe.push_back (OK);
		}

	//	wenigstens 1 Objekt in Liste ?
		if (m_ObjektListe.size () < 1)
			return NOERROR;

	//	Toleranzen berechnen
		m_Params.CalculateTolerances (m_ObjektListe.front (), m_dFuzzy);

	//	Maschenbildung
		CObjektKante Predikat;

	//	Ausgabeobjekt erzeugen
		WEnumObjectsByNumber WEnumObjs (CLSID_EnumObjectsByNumber);

	//	Ausgabeobjekt übergeben
		CMaschenBildung Maschen (m_ObjektListe, WEnumObjs, m_Params, Predikat);
		CProgressIndicator Indicator (m_hWnd);

	//	ggf. Maschen erzeugen
		if (m_bUnionMaschen) {
			ASSERT(NULL != m_Params.m_hPr);		// Datenquelle muß festgelegt sein
			if (SUCCEEDED(Maschen.CreateMaschen (m_Params.m_hPr, &Indicator, m_bOutputMerkmal))) // #WM991014
			{
			//	Ursprungslinien löschen
				if (m_bDeleteLines)
				{
					ASSERT(!m_bMarkObjects);

					CString strCaption;
					VERIFY (strCaption.LoadString (IDS_CAPTION_DELETE_MASCH));
					if (!DeleteLinesInTrias (&Indicator, strCaption))
						return NOERROR;
				}

			// #HK971217
			// Ursprungslinien kennzeichnen
				if (m_bMarkObjects) 
				{
					ASSERT(!m_bDeleteLines);

					CString strCaption;
					VERIFY (strCaption.LoadString (IDS_CAPTION_MARK_OBJECTS));
					if (!MarkObjectsInTrias (&Indicator, strCaption))
						return NOERROR;
				}

			//	benutzte Linien in Liste löschen
				DeleteLinesInListe ();
			}
			else
				bUserBreak = TRUE;
		}
				
	//	ggf. restlichen Linien vereinigen
		if (!bUserBreak && m_bUnionLines && !m_ObjektListe.empty ())
		{
			ASSERT (NULL != m_Params.m_hPr);
			ASSERT (reinterpret_cast<HPROJECT>(0xcdcdcdcd) != m_Params.m_hPr);

//			if (Maschen.CreateLines (m_Params.m_hPr, &Indicator, m_bOutputMerkmal))
//			if (S_OK == Maschen.CreateLines (m_Params.m_hPr, &Indicator, m_bOutputMerkmal))
			if (SUCCEEDED (Maschen.CreateLines (m_Params.m_hPr, &Indicator, m_bOutputMerkmal)))	// #WM991014
			{
			//	Ursprungslinien löschen
				if (m_bDeleteLines)
				{
					ASSERT(!m_bMarkObjects);

					CString strCaption;
					VERIFY (strCaption.LoadString (IDS_CAPTION_DELETE_LINES));
					DeleteLinesInTrias (&Indicator, strCaption);
				}

			// #HK971217
			// Ursprungslinien kennzeichnen
				if (m_bMarkObjects) 
				{
					ASSERT(!m_bDeleteLines);

					CString strCaption;
					VERIFY (strCaption.LoadString (IDS_CAPTION_MARK_OBJECTS));
					MarkObjectsInTrias (&Indicator, strCaption);
				}
			}
			else
				bUserBreak = TRUE;
		}

	//	ggf. Ausgabeobjekt speichern
	//	lese Anzahl gespeicherter Objektnummern
		ULONG ulCnt = 0;
		hrt = WEnumObjs->GetCount (&ulCnt);
		if (FAILED (hrt))
			_com_issue_error (hrt);

		if (0 != ulCnt)
			m_OutNrListe.push_back (WEnumObjs);
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
	catch (bad_alloc *be)
	{
		be = NULL;
		DEX_Error (RC_Maschenbildung, EC_NOMEMORY);		
		return E_OUTOFMEMORY; 	
	}
	
	return bUserBreak ? E_ABORT : NOERROR;
}

void CParamDialog::OnDeleteLines() 
{
	// TODO: Add your control notification handler code here
	m_bDeleteLines = m_btDeleteLines.GetCheck ();
	OutputDescription (m_bDeleteLines ? IDS_DELETE_LINES : IDS_DELETE_LINES_NOT);

	if (m_bDeleteLines)			// #HK971217
		m_btMarkObjects.SetCheck (FALSE);

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

// #HK971217
void CParamDialog::OnMarkObjects() 
{
	m_bMarkObjects = m_btMarkObjects.GetCheck();
	OutputDescription (m_bMarkObjects ? IDS_MARK_OBJECTS : IDS_MARK_OBJECTS_NOT);

	if (m_bMarkObjects)
		m_btDeleteLines.SetCheck (FALSE);

	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

void CParamDialog::OnLinesUnion() 
{
	// TODO: Add your control notification handler code here
	m_bUnionLines = m_btUnionLines.GetCheck ();	
	OutputDescription (m_bUnionLines ? IDS_UNION_LINES : IDS_UNION_LINES_NOT);
	SetButtons ();
	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

void CParamDialog :: DeleteLinesInListe (void)
{
//	prüfe Parameter
	if (m_ObjektListe.empty ())
		return;

//	Kante aus Liste löschen
	CObjektKantenList_tit Iter;
	for (Iter = m_ObjektListe.begin(); Iter != m_ObjektListe.end();)
	{
	//	Objekt löschen
		if ((*Iter).m_sBuildCnt > 0)				// wenn wenigstens einmal benutzt
			m_ObjektListe.erase (Iter++);			
		else
		{
			(*Iter).m_bIsInUnion = FALSE;			// wird nicht benutzt
			Iter++;					
		}
	}
}

//	benutzte Kanten in TRiAS löschen
BOOL CParamDialog :: DeleteLinesInTrias (CProgressIndicator *pIndicator, CString &strCaption)
{
	ASSERT (NULL != pIndicator);

//	prüfe Parameter
	if (m_ObjektListe.empty ())
		return TRUE;

//	Indicator init.
	pIndicator->InitStatusDialog (m_ObjektListe.size (), strCaption);
	long lPos = 1;

	CObjektKantenList_tit Iter;
	for (Iter = m_ObjektListe.begin(); Iter != m_ObjektListe.end(); Iter++, lPos++)
	{
	//	Progress-Indicator akt.
		pIndicator->SetupStatus (lPos);
		if (pIndicator->WasCanceled ())
			return FALSE;

	//	Objekt löschen
		if ((*Iter).m_sBuildCnt > 0)				// wenn wenigstens einmal benutzt
			VERIFY ((*Iter).DeleteGeometrie ());
	}

	return TRUE;
}

//	benutzte Kanten in TRiAS kennzeichnen
BOOL CParamDialog :: MarkObjectsInTrias (CProgressIndicator *pIndicator, CString &strCaption)
{
	ASSERT (NULL != pIndicator);

//	prüfe Parameter
	if (m_ObjektListe.empty ())
		return TRUE;

//	Indicator init.
	pIndicator->InitStatusDialog (m_ObjektListe.size (), strCaption);
	long lPos = 1;


	CObjektKantenList_tit Iter;
	for (Iter = m_ObjektListe.begin(); Iter != m_ObjektListe.end(); Iter++, lPos++)
	{
	//	Progress-Indicator akt.
		pIndicator->SetupStatus (lPos);
		if (pIndicator->WasCanceled ())
			return FALSE;

	//	Objekt kennzeichnen
		if ((*Iter).m_sBuildCnt > 0) {				// wenn wenigstens einmal benutzt
		// MerkmalsCode besorgen
		ULONG ulMCode = GetMerkmalsKode((*Iter).GetObjNummer(), IDS_MARKOBJECT_HDR,
										IDS_MARKOBJECT_PBD, TRUE);

			ASSERT (0 != ulMCode);
			ASSERT ((ULONG)-1 != ulMCode);
			if (0 == ulMCode || (ULONG)-1 == ulMCode) continue;		
			VERIFY ((*Iter).MarkObject(ulMCode)); 
		}
	}

	return TRUE;
}

void CParamDialog::OnMaschenUnion() 
{
	// TODO: Add your control notification handler code here
	m_bUnionMaschen = m_btUnionMaschen.GetCheck ();	
	OutputDescription (m_bUnionMaschen ? IDS_UNION_MASCHEN : IDS_UNION_MASCHEN_NOT);
	SetButtons ();
	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

//	Beschreibungstext ausgeben
void CParamDialog :: OutputDescription (UINT uiResID)
{
	CString strText;
	VERIFY (strText.LoadString (uiResID));
	m_stDescription.SetWindowText (strText);
}

void CParamDialog::OnSetfocusFuzzy() 
{
	// TODO: Add your control notification handler code here
	OutputDescription (IDS_FANG_BEREICH);
}

void CParamDialog::OnDeltaposFuzzy(NMHDR* pNMHDR, LRESULT* pResult) 
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
		
	*pResult = 0;
}

//	Parameter setzen
void CParamDialog::SelectFuzzy (double dFuzzy)
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

void CParamDialog::SelectUnionMaschen (BOOL bFlag)
{
	m_bUnionMaschen = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btUnionMaschen.SetCheck (m_bUnionMaschen);
}

void CParamDialog::SelectUnionLines (BOOL bFlag)
{
	m_bUnionLines = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btUnionLines.SetCheck (m_bUnionLines);
}

void CParamDialog::SelectDeleteOldLines (BOOL bFlag)
{
	m_bDeleteLines = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btDeleteLines.SetCheck (m_bDeleteLines);
}

void CParamDialog::SelectOutputMerkmal (BOOL bFlag)
{
	m_bOutputMerkmal = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btOutputMerkmal.SetCheck (m_bOutputMerkmal);
}

void CParamDialog::OnOutputMerkmal() 
{
	// TODO: Add your control notification handler code here
	m_bOutputMerkmal = m_btOutputMerkmal.GetCheck ();	
	OutputDescription (m_bOutputMerkmal ? IDS_OUTPUT_MERKMAL : IDS_OUTPUT_MERKMAL_NOT);
	ASSERT (NULL != m_pAction);
	m_pAction -> SetDirty (TRUE);
}

// #HK971217
void CParamDialog::SelectMarkObjects (BOOL bFlag)
{
	m_bMarkObjects = bFlag;
	if (m_hWnd && IsWindowVisible ())
		m_btMarkObjects.SetCheck (m_bMarkObjects);
}

// liest Objektmenge
HRESULT CParamDialog::GetEnumLONG (WEnumObjectsByNumber &WEnum)
{
	// nachfolgenden Zeilen ergänzt, weil sonst WEnum == 0x00 bleibt, wenn m_OutNrListe leer ist (#WM990625)
	try
	{
	WEnumObjectsByNumber wEnumObjs (CLSID_EnumObjectsByNumber);

		WEnum = wEnumObjs;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}	

//	prüfe Listeneinträge
	if (m_OutNrListe.empty ())
		return S_OK;

//	ansonsten immer 1. Element zurück
	WEnum = m_OutNrListe.front ();
	m_OutNrListe.pop_front ();	//	dieses Objekt löschen

	return m_OutNrListe.empty () ? S_OK : S_FALSE;
}

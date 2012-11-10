// importpa.cpp : implementation file
//
// Erarbeitet: J.Benkenstein					Stand vom 30.11.1995

#include "pheader.h"
#include "odbcext.hr"		// Resourcen

#include <hpp/getodbci.hpp>		// CODBCInfos
#include "database.hpp"		// CDataBaseExt
#include <hpp/objinfo.hpp>		// ObjektMerkmalInfo

#include "importpa.hpp"		// zugeh. Header		

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifndef WIN32
//	globale Variablen
CPropertySheetExt *g_pSheet = NULL;
#endif

// CImportParams ------------------------------------------------------------------------------------
CImportParams :: CImportParams (void)
{
	m_pulObjektKlassen = NULL;
	CleanUp ();
}

CImportParams :: ~ CImportParams (void)
{
	CleanUp ();
}

//	Info für Import vollständig ?
BOOL CImportParams :: InfoComplete (void)
{
	if (m_strDataSource.IsEmpty () || m_strTableName.IsEmpty () || m_strDefinition.IsEmpty () ||
		m_strKoppelFeld.IsEmpty () || m_strHochWert.IsEmpty () || m_strRechtsWert.IsEmpty () ||
 	   (m_ulObjektMKode == 0)	|| (m_pulObjektKlassen == NULL) || (*m_pulObjektKlassen == 0))
		return FALSE;
	else
		return TRUE;					
}

//	alle Infos löschen
void CImportParams :: CleanUp (void)
{
	m_tDsn = NoDataSource;
	m_COdbcInfos.DeleteAll ();	
	m_strDataSource.Empty ();
	m_strTableName.Empty ();
	m_strKoppelFeld.Empty ();
	m_strRechtsWert.Empty ();
	m_strHochWert.Empty ();
	m_strFilter.Empty ();
	m_strDefinition.Empty ();
	m_ulObjektMKode = 0;
	DELETE_VEC (m_pulObjektKlassen);		 	

	m_ulNotImported = m_ulPointCnt = m_ulObjektMKode = 0;
	m_ulUnIdMKode = ulUnIdMKode;

	m_sKoppelIndex = m_sRechtsWertIndex = m_sHochWertIndex = -1;

	m_bAction = TRUE;								// TRIAS abgleichen		
	m_bDelNotExist = m_bAddNotExist = FALSE;		// nicht existierende ignorieren

	m_lImpCnt = m_lErrImpCnt = m_lDelCnt = m_lDoppTableCnt =            
	m_lNewCnt = m_lDoppTriasCnt = 0;
}

#ifndef WIN32

CPropertySheetExt::CPropertySheetExt (UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
				  : CPropertySheet (nIDCaption, pParentWnd, iSelectPage)
{                   
	m_hWndEsc = NULL;
	m_iActPage = 0;		// --> Definition-Page wird geladen
	g_pSheet = this;
}	                                

CPropertySheetExt::~CPropertySheetExt ()
{           
	g_pSheet = NULL;
}

void CPropertySheetExt :: SetWizardButtons (int iMode)
{       
	if (m_btNext.m_hWnd)
	{
		if (iMode & PSWIZB_NEXT)
			m_btNext.EnableWindow (TRUE); 
		else			
			m_btNext.EnableWindow (FALSE);
	}
	
	if (m_btBack.m_hWnd)
	{			
	if (iMode & PSWIZB_BACK)
		m_btBack.EnableWindow (TRUE); 			
	else
		m_btBack.EnableWindow (FALSE);						
	}		
}	        

void CPropertySheetExt :: SetFinishText (const char *pText)
{
	ASSERT (pText != NULL && AfxIsValidString (pText));
	m_btNext.SetWindowText (pText);
	if (m_hWndEsc)		// "Abbrechen"-Button disabeln 
		:: ShowWindow (m_hWndEsc, SW_HIDE);	
}

#endif		// WIN16


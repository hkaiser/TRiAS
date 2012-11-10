// feldinfo.cpp : implementation file
//

#include "pheader.h"		// vorübersetzter Header

extern "C" 
{
    #include <xtension.h>   // TRIAS-Messages
    #include <xtensnx.h>
    #include "odbcext.hr"	// Resource-Konstanten
}    

#include <columnst.hpp>		// CColumnStatus
#include <hpp/collist.hpp>		// CColumnObjArray

#include "feldinfo.hpp"		// zugeh. Header

//	Konstanten
const short sTabConst = 4;				// aus CommonView
const short sTabOffset = 3;                                                      
const short sTypeLen = 5;				// 5 Zeichen für Länge eines Feldes
const char strTab [] = "\t";

BEGIN_MESSAGE_MAP(CFeldInfo, CDialog)
	//{{AFX_MSG_MAP(CFeldInfo)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDL_FIELDINFO, OnSelchangeFeldList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFeldInfo dialog
CFeldInfo :: CFeldInfo (CWnd* pParent, CColumnObjArray *pCA)
		   : CDialog (CFeldInfo :: IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeldInfo)
		// NOTE: the ClassWizard will add member initialization here
	m_bResult = FALSE;			// noch nichts getan		
	m_pCA = NULL;
	//}}AFX_DATA_INIT                                      
	
//	prüfe Parameter
	if (!pParent || !pCA || !pCA -> Count ())
	{
		DEX_Error (RC_ctCFeldInfo, EC_ILLPARS);
		return;
	}	         
	
	m_pCA = pCA;				// Zeiger speichern
	      
	m_bResult = TRUE;			// alles OK
}

void CFeldInfo :: DoDataExchange(CDataExchange* pDX)
{
	CDialog :: DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeldInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDL_FIELDINFO, m_lbFieldInfo);		
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFeldInfo message handlers
void CFeldInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_lbFieldInfo.m_hWnd && m_lbFieldInfo.IsWindowVisible ())      	
		m_lbFieldInfo.MoveWindow (0, 0, cx, cy);	
}

BOOL CFeldInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	if (m_bResult == FALSE)
		return FALSE;
		
	m_bResult = FALSE;		// Flag rücksetzen		
	
//	Listbox einstellen
	int TabArray [2];
	WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
	short sHelp = (m_pCA -> m_sMaxNameLen + sTabOffset) * sTabConst;         
	TabArray [0] = sHelp;		
	TabArray [1] = ((m_pCA -> m_sMaxTypeNameLen + sTabOffset) * sTabConst) + sHelp;
	m_lbFieldInfo.SetTabStops (2, (LPINT) TabArray);
	sHelp = (m_pCA -> m_sMaxNameLen + m_pCA -> m_sMaxTypeNameLen + sTypeLen) + 
			(sTabOffset * 2);	    
	m_lbFieldInfo.SetHorizontalExtent (wUnits * sHelp);		
	
//	für alle Felder Informationen ausgeben	
	CString strInfo;
	CRing ri (*m_pCA);                 
	char Buffer [15] = "";
	int nResult = 0;
	CString strMemo;
	CString strVariabel;
	
	TRY
	{   
		strMemo.LoadString (IDS_MEMO);
		strVariabel.LoadString (IDS_VARIABEL);
	
		for (ri.First (); ri.Valid (); ri.Next ())
		{
			CColumnObjLock pCO (ri);
			if (! pCO)
			{
				DEX_Error (RC_ctCFeldInfo, EC_LOCKERROR);
				return FALSE;
			}          
		
			strInfo = pCO -> ColName ();
			strInfo += strTab;		      
			strInfo += pCO -> SQLTypeName ();
			strInfo += strTab;		
			if (strMemo.CompareNoCase (pCO -> SQLTypeName ()) == 0)
				strInfo += strVariabel;
			else								
				strInfo += ltoa (pCO -> FieldLen (), Buffer, 10);
		
			nResult = m_lbFieldInfo.AddString (strInfo);
			if (nResult == LB_ERR || nResult == LB_ERRSPACE)
			{       
				DEX_Error (RC_ctCFeldInfo, EC_NOMEMORY);
				return FALSE;                   
			}
		}	// end for                            
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_ctCFeldInfo, EC_NOMEMORY);        
		return FALSE;
	}
	END_CATCH
	
//	Caption ändern		
	m_lbFieldInfo.SetCurSel (0);		
                        
	return m_bResult = ChangeCaption (m_lbFieldInfo.GetCurSel ());	
}

afx_msg void CFeldInfo :: OnSelchangeFeldList (void)
{              
	if (m_lbFieldInfo.GetCurSel () < 0)
		return;
	ChangeCaption (m_lbFieldInfo.GetCurSel ());
}	
 
BOOL CFeldInfo :: ChangeCaption (int iSel)
{                 
	if (iSel < 0)
		return FALSE;
	
	TRY
	{	                        
		char Buffer [20] = "";
		CString strCaption;						
		m_lbFieldInfo.GetText (iSel, strCaption);
		strCaption = strCaption.Left (strCaption.Find (strTab));				
		strCaption += ": ";
		strCaption += itoa (iSel + 1, Buffer, 10);
		strCaption += "/";				          
		strCaption += itoa (m_lbFieldInfo.GetCount (), Buffer, 10);
		SetWindowText (strCaption);         // Caption ausgeben
	}
	CATCH (CMemoryException, cme)
	{        
		DEX_Error (RC_ctCFeldInfo, EC_NOMEMORY);		            
		return FALSE;	            
	}
	END_CATCH		
	
	return TRUE;
}

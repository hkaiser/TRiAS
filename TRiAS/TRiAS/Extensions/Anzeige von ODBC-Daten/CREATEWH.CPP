/*
Mit Hilfe dieses Dilaogs kann die WHERE-Klausel einer SQL-SELECT-Anweisung als
Kombination aus TRIAS-Merkmalen und Feldnamen einer Tabelle erzeugt werden.

Erarbeitet: J. Benkenstein 				Stand vom 28.10.1994
*/

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten

#include <sqlext.h>			// SQLGetInfo ()
#include <hpp/getodbci.hpp>
#include "database.hpp"		// CDataBaseEx                                                              
#include <hpp/waitcur.hpp>		// CWaitCursor
#include <hpp/helptext.hpp>		// CHelpText
#include <hpp/columnst.hpp>		// CColumns
#include <hpp/chklausl.hpp>		// CheckWhereKlausel ()
#include <hpp/objinfo.hpp>		// KurzTextLen

#include "tablinfo.hpp"		// CTableInfoTree
#include <hpp/createwh.hpp>		// zugeh. Header
#include <errinstx.hxx> // ErrInstall

// extern Variablen 
extern int g_sMkBase;			// Zahlenbasis

// 	lokale Variablen
static int sMaxStrLen = 0;	// zur Einstellung des Srcoll-Bereiches in ListBoxen

//	Operator-Beschreibungs-Feld
static uint OperatorDescArray [MaxOperators];
static uint FunctionDescArray [MaxFunctions];


//	lokale Funktionen
// 
// 	ListBox mit allen Merkmalen der PBD füllen
BOOL __export FAR PASCAL FillMerkmalsList (long lMerkmal, DWORD dw, void *pData)
{   
// KK000413 :
//	Umstellen der alten Funktion ( Lesen in PBD DEX_EnumMCodesEx )
//	in DEX_EnumObjektMerkmaleClassEx ( MK pro ID)	
ObjMerkmalInfo *pInfo = (ObjMerkmalInfo *) pData;

	if ('m' != pInfo -> m_lType)
		return TRUE;
	if (0 == pInfo -> m_lIdent)
		return TRUE;

	if (dw & MPSystemFeatures)
		return TRUE;

ErrInstall E1 (WC_NOMERKMAL);
ErrCode EC;
char KText[KurzTextLen] = "";
PBDMERKMALEX pbdData;  
         
	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = (short) pInfo -> m_lType;
	pbdData.pbdCode = lMerkmal;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = KurzTextLen - 1;
	pbdData.lIdent = pInfo -> m_lIdent;
	HPROJECT hPr = DEX_GetObjectsProject(pInfo -> m_lIdent);
	EC = DEX_GetPBDDataEx (hPr, pbdData);

	if (EC != EC_OKAY) // Nur definierte OE !!
		return TRUE;

	// Merkmal
	ASSERT('m' == pbdData.pbdTyp);
	if (pbdData.ipbdMTyp != 'a')					// nur ObjectFeature
		return TRUE;	// KK000411

	if (0 == strncmp (pbdData.pbdKText, "__", 2))	// HK - intern : alle OE mit __ raus
		return TRUE;	// KK000411


   	char outBuff [sizeof (KText) + 20];
  
// KK000427
long lMOCode = DEX_MapHandleToMCode(lMerkmal);

//	Scroll-Variable setzen		           
	sMaxStrLen = max (sMaxStrLen, lstrlen (outBuff));		

//	if (pInfo -> m_pCComboBox) {
//		int iIndex = pInfo -> m_pCComboBox -> AddString (outBuff);
//		return (CB_ERR != iIndex) ? TRUE : FALSE;
//	}

	if (pInfo -> m_pCListBox) {
	int iIndex = pInfo -> m_pCListBox -> AddString (pbdData.pbdKText);

		if (CB_ERR != iIndex) {
			pInfo -> m_pCListBox -> SetItemData(iIndex, lMOCode);
			return TRUE;
		}
	}

	ASSERT(/*NULL != pInfo -> m_pCComboBox || */NULL != pInfo -> m_pCListBox);
	return FALSE;	
}
	

/////////////////////////////////////////////////////////////////////////////
// CCreateWhereKlDlg dialog

__export CCreateWhereKlDlg :: CCreateWhereKlDlg(CWnd* pParent, CDataBaseExt *pDataBase,
					 		  CString &strKlausel, ulong nActObjIdent,CString &strTableNames)
				   			: CDialog(CCreateWhereKlDlg :: IDD, pParent),
				   	 		  m_strKlausel (strKlausel),
				   	 		  m_nActObjIdent(nActObjIdent),
				   	 		  m_strTableNames (strTableNames),
				   	 		  m_TableTree (pDataBase)
{
	//{{AFX_DATA_INIT(CCreateWhereKlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT                       
	
	sMaxStrLen = 0;
	m_bParse = FALSE;  

   
	if (! (m_pDataBase = pDataBase) || strTableNames.IsEmpty () ||
		(m_TableTree.Result () != EC_OKAY))
		m_ErrCode = EC_ILLPARS;
	else		
		m_ErrCode = EC_OKAY;
}

void CCreateWhereKlDlg :: DoDataExchange(CDataExchange* pDX)
{
	CDialog :: DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateWhereKlDlg)
	DDX_Control(pDX, IDL_TABLE_FIELDS, m_lbFields);
	DDX_Control(pDX, IDL_SCALE_FUNCTIONS, m_lbFunctions);
	DDX_Control(pDX, IDL_OPERATORS, m_lbOperators);
	DDX_Control(pDX, IDL_OBJ_MERKMALE, m_lbMerkmale);
	DDX_Control(pDX, IDE_WHERE, m_edKlausel);
	DDX_Control(pDX, IDT_WHERE_DESCR, m_stDescription);
	DDX_Control(pDX, IDOK, m_btBeenden);
	DDX_Control(pDX, IDB_CHECK_WHERE, m_btCheckKlausel);
	DDX_Control(pDX, IDB_AS_TEXT, m_btAsText);
	DDX_Control(pDX, IDB_AS_DATE, m_btAsDate);	
	DDX_Control(pDX, IDB_AS_NUM, m_btAsNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateWhereKlDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateWhereKlDlg)
	ON_EN_CHANGE(IDE_WHERE, OnChangeKlausel)
	ON_BN_CLICKED(IDB_CHECK_WHERE, OnCheckKlausel)
	ON_LBN_SELCHANGE(IDL_OBJ_MERKMALE, OnSelchangeMerkmale)
	ON_LBN_DBLCLK(IDL_OBJ_MERKMALE, OnDblclkMerkmale)
	ON_LBN_DBLCLK(IDL_OPERATORS, OnDblclkOperators)
	ON_LBN_SELCHANGE(IDL_OPERATORS, OnSelchangeOperators)
	ON_LBN_SELCHANGE(IDL_SCALE_FUNCTIONS, OnSelchangeFunctions)
	ON_LBN_DBLCLK(IDL_SCALE_FUNCTIONS, OnDblclkFunctions)
	ON_LBN_DBLCLK(IDL_TABLE_FIELDS, OnDblclkFields)
	ON_LBN_SELCHANGE(IDL_TABLE_FIELDS, OnSelchangeFields)
	ON_BN_CLICKED(IDB_AS_TEXT, OnAsText)
	ON_BN_CLICKED(IDB_AS_DATE, OnAsDate)	
	ON_BN_CLICKED(IDB_AS_NUM, OnAsNum)
	ON_EN_SETFOCUS(IDE_WHERE, OnSetfocusKlausel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCreateWhereKlDlg message handlers

// Dialog init.
BOOL CCreateWhereKlDlg :: OnInitDialog (void)
{
	CDialog :: OnInitDialog();
	
//	prüfe interne Parameter
	if (m_ErrCode != EC_OKAY)
		EndDialog (IDABORT);	
		
//	SandUhr einschalten
	CWaitCursor wc;		
	
//	Arial-Zeichensatz für Beschreibungsfeld einstellen	
	m_stDescription.InitFont ();
	
//	voreingestellte Klausel ausgeben             
	m_edKlausel.LimitText (KlauselSize);
	if (! m_strKlausel.IsEmpty ())	
	{
		m_edKlausel.SetWindowText (m_strKlausel);
		if (m_strKlausel.Find ('\'') >= 0)
			m_btAsText.SetCheck (1);			
		else
		{
			if (m_strKlausel.Find ('#') >= 0)
				m_btAsDate.SetCheck (1);				
			else				
				m_btAsNum.SetCheck (1);				
		}
	}		
	
// KK000413
//	Merkmalskodes lesen      
	
	m_lbMerkmale.ResetContent();
	ObjMerkmalInfo oi;
	oi.m_lIdent = m_nActObjIdent;
	oi.m_lType = 'm';
	oi.m_pCListBox = &m_lbMerkmale;

	ENUMLONGKEYEX ELK;
	ErrInstall EI (WC_NOMERKMAL);
	ELK.eFcn = (ENUMLONGKEYEXPROC)FillMerkmalsList;
	ELK.ePtr =  (void*) &oi;
	ELK.eKey = m_nActObjIdent;
	ELK.eData = DWORD('a');

	if (!DEX_EnumObjektMerkmaleClassEx(ELK)) {
		m_ErrCode = EC_SYSERROR;
		EndDialog (IDABORT);	
		return FALSE;
	}

//	Srcoll-Bereich für MerkmalsListBox setzen
	WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
	if (sMaxStrLen > 0)
		m_lbMerkmale.SetHorizontalExtent (wUnits * sMaxStrLen);		
		
//	Init. Operator-, Function- und Feldnamen-ListBox
	if (!ReadOperators (wUnits) || !ReadFunctions (wUnits) ||
		(m_TableTree.CreateTables (m_strTableNames) != EC_OKAY) ||	// Tabellen erzeugen
		(m_TableTree.OutputRechercheFields (m_lbFields, sMaxStrLen) != EC_OKAY))		
	{                   
		m_ErrCode = EC_SYSERROR;
		EndDialog (IDABORT);	
		return FALSE;
	}		            

//	Funktionen
	if (m_lbFunctions.GetCount () > 0)
		m_lbFunctions.EnableWindow (TRUE);
	else
		m_lbFunctions.EnableWindow (FALSE);			
	                        
//	Horizontal-Extent setzen	                        
	m_lbFields.SetHorizontalExtent (wUnits * sMaxStrLen);			
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//	Klausel wurde geändert
void CCreateWhereKlDlg :: OnChangeKlausel (void)
{                             
	BOOL bEnable = m_edKlausel.LineLength () > 0;
	m_btCheckKlausel.EnableWindow (bEnable);	
	m_btBeenden.EnableWindow (bEnable);
}
    
//	Klausel-Eingabe-Feld erhielt Steuerung    
void CCreateWhereKlDlg :: OnSetfocusKlausel (void)
{                        
	static BOOL bFirstTime = TRUE;
	
	if (bFirstTime)
	{
		bFirstTime = FALSE;
		m_edKlausel.SetSel (m_strKlausel.GetLength (), 
							m_strKlausel.GetLength ()); 
	}		

//	Beschreibungstext ausgeben
	if (m_bParse)
		m_bParse = FALSE;		// Flag rücksetzen
	else		
		m_stDescription.Output (IDS_INPUT_KLAUSEL);			
}

// 	Merkmal als Textwert benutzen
void CCreateWhereKlDlg :: OnAsText (void)
{                                       
//	nur Beschreibungs-Text ausgeben
	m_stDescription.Output (IDS_TEXT_VALUE);
}

// 	Merkmal als Datum benutzen
void CCreateWhereKlDlg :: OnAsDate (void)
{                                       
//	nur Beschreibungs-Text ausgeben
	m_stDescription.Output (IDS_DATE_VALUE);
}

// 	Merkmal als Ziffer benutzen
void CCreateWhereKlDlg :: OnAsNum (void)
{                                       
//	nur Beschreibungs-Text ausgeben
	m_stDescription.Output (IDS_NUM_VALUE);
}

void CCreateWhereKlDlg :: OnSelchangeMerkmale (void)
{
int iCurSel = m_lbMerkmale.GetCurSel();

	if (iCurSel < 0)
		return;

//	Beschreibung ausgeben	
CString strInfo; 

	m_lbMerkmale.GetText (iCurSel, strInfo);	
	
//	Merkmalskode lesen	
	if (! strInfo.IsEmpty ())
		m_stDescription.OutputDescription (m_lbMerkmale.GetItemData(iCurSel), 'm', IDS_SELMERKMAL);    // Info ausgeben
}	                            

//	neues Merkmal wurde gewählt
void CCreateWhereKlDlg :: OnDblclkMerkmale (void)
{       
	int iCurSel = m_lbMerkmale.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY	{
	CString strSel, strSep;
	
	//	wenn Text-Merkmal gefordert
		if (m_btAsText.GetCheck ())
			strSep = TextMerkmalStr;
		else {
			if (m_btAsDate.GetCheck ())
				strSep = DateMerkmalStr;				
		}			
		strSel = strSep;				// ggf. Separator 
		strSel += MerkmalBeginStr; 		// "{"
		
	//	Merkmal lesen
	CString strMerkmal;

		m_lbMerkmale.GetText (iCurSel, strMerkmal);

	//	Wert komplettieren
		strSel += strMerkmal;				
		strSel += MerkmalEndStr;			// "}"
        strSel += strSep;					// ggf. Separator 
				
		m_edKlausel.ReplaceSel (strSel);    // Wert im Editfeld einfügen
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}		
	END_CATCH
}
      
//	neuer Operator wurde gewählt      
void CCreateWhereKlDlg :: OnDblclkOperators (void)
{
	int iCurSel = m_lbOperators.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY	{
	CString strSel;
		
	//	Operator lesen
		CString strOperator;
		m_lbOperators.GetText (iCurSel, strOperator);
		                                           
	//	Wert komplettieren
		strSel = " ";
		strSel += strOperator;
		strSel += " ";

		m_edKlausel.ReplaceSel (strSel);    // Wert im Editfeld einfügen
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}		
	END_CATCH
}
    
//	neuer Operator wurde selektiert    
void CCreateWhereKlDlg :: OnSelchangeOperators (void)
{
	short sActSel = m_lbOperators.GetCurSel ();		
	if ((sActSel >= 0) && (sActSel < MaxOperators))		// wenn Index gültig
	{                          
		uint uResID = OperatorDescArray [sActSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
	}
}

//	neue skalare Funktion wurde selektiert
void CCreateWhereKlDlg :: OnSelchangeFunctions (void)
{
	short sActSel = m_lbFunctions.GetCurSel ();		
	if ((sActSel >= 0) && (sActSel < MaxFunctions))		// wenn Index gültig
	{                          
		uint uResID = FunctionDescArray [sActSel];
		if (uResID)
			m_stDescription.Output (uResID);			// Beschreibung ausgeben
	}	
}

//	neue skalare Funktion wurde gewählt
void CCreateWhereKlDlg :: OnDblclkFunctions (void)
{
	int iCurSel = m_lbFunctions.GetCurSel ();
	if (iCurSel < 0)
		return;

	TRY	{   
	CString strFunction, strFormat, strValue;		
	
		m_lbFunctions.GetText (iCurSel, strFunction);
		strFormat.LoadString (IDS_SCALE_FCN_FORMAT);
		char *pBuffer = strValue.GetBuffer (strFormat.GetLength () + 
											strFunction.GetLength () + 10);
		wsprintf (pBuffer, strFormat, (const char *) strFunction);
		m_edKlausel.ReplaceSel (pBuffer);	
	}
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
	}	
	END_CATCH
}

// 	neues Feld wurde gewählt
void CCreateWhereKlDlg :: OnDblclkFields (void)
{
	int iCurSel = m_lbFields.GetCurSel ();
	if (iCurSel < 0)
		return;

	CString strField, strFeldName;
	m_lbFields.GetText (iCurSel, strField);
	AfxFormatString1 (strFeldName, IDS_FIELDNAME_FORMAT, strField);
	m_edKlausel.ReplaceSel (strFeldName);		
}
    
//	neues Feld wurde gewählt    
void CCreateWhereKlDlg :: OnSelchangeFields (void)
{
	int iCurSel = m_lbFields.GetCurSel ();
	if (iCurSel < 0)
		return;

	CString strSel, strFullName;
	m_lbFields.GetText (iCurSel, strSel);
	                           
	TRY
	{	                           
	//	Tabellen-Name ggf. ergänzen
		if (strSel.Find (TableSQLSep) == -1)
		{
			strFullName = m_strTableNames;
			strFullName += TableSQLSepStr;					
		}
	
		strFullName += strSel;
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
		return; 
	}	
	END_CATCH	
	
	m_TableTree.OutputDescription (m_stDescription, strFullName);
}
                          
//	Dialog beenden                          
void CCreateWhereKlDlg :: OnOK (void)
{
	if (! CheckKlausel ())
	{
    	m_btCheckKlausel.EnableWindow (FALSE);
		m_btBeenden.EnableWindow (FALSE);		
		return;	  
	}		
		
	m_ErrCode = EC_OKAY;
	m_edKlausel.GetWindowText (m_strKlausel);
			
	CDialog :: OnOK();
}

//	Eingegebene Klausel prüfen:
void CCreateWhereKlDlg :: OnCheckKlausel (void)
{
	m_btCheckKlausel.EnableWindow (FALSE);
	if (! CheckKlausel ())                      
		m_btBeenden.EnableWindow (FALSE);		
}

//	Init. OperatorListBox und Feld                
BOOL CCreateWhereKlDlg :: ReadOperators (WORD wUnits)
{       
	int sMaxLen = 0;		// max. ZK-Länge setzen

	TRY
	{          
	//	Operatorfeld init.      
		memset (&OperatorDescArray, 0, sizeof (OperatorDescArray) /
									   sizeof (uint));			
									   
		uint uActResID = IDS_AND_OP;
		CString strActOp;
		for (short sIndex = 0; sIndex < MaxOperators; sIndex++, uActResID += 2)
		{   
		//	akt. String laden
			if (strActOp.LoadString (uActResID) &&			// String aus Resource laden
				(m_lbOperators.AddString (strActOp) >= 0))	// String in ListBox
				OperatorDescArray [sIndex] = uActResID + 1;	// ResID speichern							
			else
			{                
				DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);				
				return FALSE;
			}     
			sMaxLen = max (sMaxLen, strActOp.GetLength ()); 				
		}
	}
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
		return FALSE;
	}                                   
	END_CATCH	
	
//	Horizontal-Extent setzen
//	if (sMaxLen > 0)
//		m_lbOperators.SetHorizontalExtent (wUnits * sMaxLen);				

	return TRUE;
}
                                        
// Init. FunctionListBox und Feld                                        
BOOL CCreateWhereKlDlg :: ReadFunctions (WORD wUnits)
{         
	sMaxStrLen = 0;         // max. Länge einer ZK setzen

	TRY
	{          
	//	Functionfeld init.      
		memset (&FunctionDescArray, 0, sizeof (FunctionDescArray) /
									   sizeof (uint));
									   
	//	lese String-Funktionen-Flag
		UDWORD	fFuncs = 0;            
		RETCODE nRetCode;		
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_STRING_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
	//	prüfe Ret-Kode									  
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			return FALSE;
		}						
		    
	//	gebe zugeh. String-Funktionen in ListBox aus und speichere 
	//	deren Beschreibungs-ResID
		uint uIndex = 0;				// Beschreibungs-Array-Index init.
		GetScaleFunction (uIndex, IDS_STRING_ACII, SQL_FN_STR_ASCII, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_CHAR, SQL_FN_STR_CHAR, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_CONCAT, SQL_FN_STR_CONCAT, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_INSERT, SQL_FN_STR_INSERT, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_LCASE, SQL_FN_STR_LCASE, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_LEFT, SQL_FN_STR_LEFT, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_LENGTH, SQL_FN_STR_LENGTH, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_LOCATE, SQL_FN_STR_LOCATE, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_LTRIM, SQL_FN_STR_LTRIM, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_REPEAT, SQL_FN_STR_REPEAT, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_REPLACE, SQL_FN_STR_REPLACE, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_RIGHT, SQL_FN_STR_RIGHT, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_RTRIM, SQL_FN_STR_RTRIM, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_SUBSTRING, SQL_FN_STR_SUBSTRING, fFuncs);
		GetScaleFunction (uIndex, IDS_STRING_UCASE, SQL_FN_STR_UCASE, fFuncs);				
		
	//	lese Konvertierungs-Funktionen 
		fFuncs = 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_CONVERT_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
	//	prüfe Ret-Kode									  
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			return FALSE;
		}								
		GetScaleFunction (uIndex, IDS_CVT_CONVERT, SQL_FN_CVT_CONVERT, fFuncs);
		
	//	lese numerische Funktionen
		fFuncs = 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_NUMERIC_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			return FALSE;
		}													   
		GetScaleFunction (uIndex, IDS_NUM_ABS, SQL_FN_NUM_ABS, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_ACOS, SQL_FN_NUM_ACOS, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_ASIN, SQL_FN_NUM_ASIN, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_ATAN, SQL_FN_NUM_ATAN, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_ATAN2, SQL_FN_NUM_ATAN2, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_CEILING, SQL_FN_NUM_CEILING, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_COS, SQL_FN_NUM_COS, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_COT, SQL_FN_NUM_COT, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_EXP, SQL_FN_NUM_EXP, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_FLOOR, SQL_FN_NUM_FLOOR, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_LOG, SQL_FN_NUM_LOG, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_MOD, SQL_FN_NUM_MOD, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_PI, SQL_FN_NUM_PI, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_RAND, SQL_FN_NUM_RAND, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_SIGN, SQL_FN_NUM_SIGN, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_SIN, SQL_FN_NUM_SIN, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_SQRT, SQL_FN_NUM_SQRT, fFuncs);
		GetScaleFunction (uIndex, IDS_NUM_TAN, SQL_FN_NUM_TAN, fFuncs);				
		
	//	lese Datums-Funktionen
		fFuncs = 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_TIMEDATE_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			return FALSE;
		}													   				
		GetScaleFunction (uIndex, IDS_TD_NOW, SQL_FN_TD_NOW, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_CURDATE, SQL_FN_TD_CURDATE, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_DAYOFMONTH, SQL_FN_TD_DAYOFMONTH, fFuncs);		
		GetScaleFunction (uIndex, IDS_TD_DAYOFWEEK, SQL_FN_TD_DAYOFWEEK, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_DAYOFYEAR, SQL_FN_TD_DAYOFYEAR, fFuncs);		
		GetScaleFunction (uIndex, IDS_TD_MONTH, SQL_FN_TD_MONTH, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_QUARTER, SQL_FN_TD_QUARTER, fFuncs);		
		GetScaleFunction (uIndex, IDS_TD_WEEK, SQL_FN_TD_WEEK, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_YEAR, SQL_FN_TD_YEAR, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_CURTIME, SQL_FN_TD_CURTIME, fFuncs);		
		GetScaleFunction (uIndex, IDS_TD_HOUR, SQL_FN_TD_HOUR, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_MINUTE, SQL_FN_TD_MINUTE, fFuncs);
		GetScaleFunction (uIndex, IDS_TD_SECOND, SQL_FN_TD_SECOND, fFuncs);					
	}									   	                   
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_CCreateWhereKlDlg, EC_NOMEMORY);
		return FALSE;
	}                                   
	END_CATCH	
	
//	Horizontal-Extent setzen
//	if (sMaxStrLen > 0)
//		m_lbFunctions.SetHorizontalExtent (wUnits * sMaxStrLen);				

	return TRUE;
}

//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
void CCreateWhereKlDlg :: GetScaleFunction (uint &uIndex, uint uResID,
											UDWORD uwCheckFlag, UDWORD fFlag)
{
	if (uwCheckFlag & fFlag)
	{                            
		CString strText;
		TRY 
		{
			if (strText.LoadString (uResID)	&&
				(m_lbFunctions.AddString (strText) >= 0))
			{ 		
				FunctionDescArray [uIndex] = ++uResID;							
				uIndex++;    
				sMaxStrLen = max (sMaxStrLen, strText.GetLength ());
			}			
			else
			{ 
				DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			}				
		}
		CATCH (CMemoryException, me)
		{        
			THROW_LAST ();		// diese Exception zum nächsten Handler
		}
		END_CATCH			
	}
}	 	
     
//	aktuelle Klausel prüfen     
BOOL CCreateWhereKlDlg :: CheckKlausel (void)
{                       
	m_bParse = TRUE;

	CString strKlausel, strError;
	m_edKlausel.GetWindowText (strKlausel);
	short sErrorPos = -1;
	
	BOOL bRet = :: CheckWhereKlausel (m_pDataBase, m_strTableNames, strKlausel, 
									  strError, sErrorPos);
		
	if (!strError.IsEmpty ())
		m_stDescription.SetWindowText (strError);					
			
	if (sErrorPos != -1)
		m_edKlausel.SetSel (sErrorPos, sErrorPos);
			
//	Fehlermeldung ggf. ausgeben									  
	if (bRet == FALSE)          
	{
		m_edKlausel.SetFocus ();
		:: MessageBeep (MB_ICONHAND);			
	}		
	
	return bRet;
}   

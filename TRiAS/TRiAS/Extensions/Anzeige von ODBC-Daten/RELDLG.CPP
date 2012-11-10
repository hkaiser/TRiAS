// reldlg.cpp : implementation file
//

// überabritet 990506 
// folgende Member wurden eliminiert
// m_CAddSlaveList
// m_btAddRel, m_btRemRel
// Code für verschiedene Listen wurde eliminiert

#include "pheader.h"			// vorübersetzter Header
#include "odbcext.hr"    		// Resource-Konstanten

#include <xtsnaux.hxx>			// WideString

#include <hpp/waitcur.hpp>			// CWaitCursor
#include <hpp/relation.hpp>     	// DBaseRel
#include <hpp/getodbci.hpp>
#include "profile.hpp"			// DBaseProfile
#include "database.hpp"			// CDataBaseEx
#include <hpp/columnst.hpp>			// CColumns
#include <hpp/odbcerr.hpp>          // OdbcError 
#include <hpp/helptext.hpp>			// CHelpText                                
#include <hpp/strdup.hxx>			// StringDup
#include <hpp/getodbci.hpp>			// ODBC-Infos lesen
#include <tabdlgs.hpp>			// CTabbedDialogs

#include "UserDlg.h"			// CUserDlg
#include "FileDlg.h"			// CFileDlg
#include "freereld.hpp"			// CFreeRel

#include "reldlg.hpp"			// zugeh. Header

#include "myhelper.h"

// Konstanten
const short MinParCnt = 3;		// wenigstens 3 Parameter für ODBC-Anbindung	
const char Separator = ',';	    // Parameter-Separator                          

BEGIN_MESSAGE_MAP(CRelDialog, CDialog)
	//{{AFX_MSG_MAP(CRelDialog)
	ON_BN_CLICKED(IDB_FREEREL, OnFreeRelation)	
//	ON_COMMAND (IDB_ADDREL, OnDelSlave)
//	ON_COMMAND (IDB_REMREL, OnAddSlave)	
	ON_COMMAND (IDB_DELREL, OnDelete)
//	ON_LBN_SELCHANGE(IDL_ADDSLAVE, OnSelWeitere)   
	ON_LBN_SELCHANGE(IDL_DELETESLAVE, OnSelVorhandene)   	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelDialog dialog
CRelDialog :: CRelDialog(CWnd* pParent, CString &strMaster, CString &strKoppelFeld, HPROJECT hPr)
		    : CDialog(CRelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelDialog)
	m_ecResult = EC_OKAY;
	m_sMaxStrLen = 0;	
	m_sType = -1;			// unbekanter Typ
	//}}AFX_DATA_INIT
	
	TRY
	{	
		m_strMaster = strMaster;
		// m_strMaster.MakeUpper ();
		m_strKoppelFeld = strKoppelFeld;
		// m_strKoppelFeld.MakeUpper ();
		m_hProject = hPr;		
	}
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_ctCRelDialog, m_ecResult = EC_NOMEMORY);
	}
	END_CATCH  				
}

void CRelDialog :: DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelDialog)      	
	DDX_Control(pDX, IDL_ADDSLAVE, m_CAddSlaveList);	
	DDX_Control(pDX, IDL_DELETESLAVE, m_CDelSlaveList);
	DDX_Control(pDX, IDB_FREEREL, m_CFreeRelButton);		
	DDX_Control(pDX, IDB_DELREL, m_DelButton);
	DDX_Control(pDX, IDOK, m_CStoreButton);	
	//}}AFX_DATA_MAP
}

// Dialog "füllen"
BOOL CRelDialog :: OnInitDialog (void)
{
	CWaitCursor wc;		// Sanduhr einschalten

	CDialog :: OnInitDialog ();
	
	TRY
	{	
		CString strCaption;
		AfxFormatString2 (strCaption, IDS_RELCAPTION, m_strMaster, m_strKoppelFeld);
		SetWindowText (strCaption);
	}
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_OnInitDialogCRelDialog, m_ecResult = EC_NOMEMORY);
		return FALSE;
	}
	END_CATCH  				

	m_sType = GetSQLType (m_strMaster, m_strKoppelFeld);
	if (m_sType == -1)		// unbekannter Typ
		return FALSE;
	
	if ((ReadSlaves () != EC_OKAY) || 
	  	(ReadActSlaves () != EC_OKAY))
		return FALSE;       

//	Horizontalen Scrollbalken für beide ListBoxen setzen
	WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
	m_CDelSlaveList.SetHorizontalExtent (wUnits * m_sMaxStrLen);	
//	m_CAddSlaveList.SetHorizontalExtent (wUnits * m_sMaxStrLen);
	
//	jetzt kein speichern der Anbindung ermöglichen	
	m_CStoreButton.EnableWindow (FALSE);	
	
//	OwnerDraw-Button laden
/*	if (! m_btAddRel.AutoLoad (IDB_ADDREL, this) ||
		! m_btRemRel.AutoLoad (IDB_REMREL, this))
		return FALSE;	
		
	m_btAddRel.EnableWindow (FALSE);	// da keine Relation selektiert
	m_btRemRel.EnableWindow (FALSE);		
*/	
	return TRUE;
}
	              
// Slave-Daten-Pool füllen
ErrCode CRelDialog :: ReadSlaves (void)
{                 
	// JG alle ini Dateien aller Projekte lesen
//	list<HPROJECT> ProjectList;	// hier werden die zu durchforstenden Projekte gespeichert

	//JG hier Schleife über alle DQ's
//	if (FAILED(EnumAllProjects(ProjectList)))
//		return WC_RETURN;

	// und jetzt gehts los
//	for (list<HPROJECT>::iterator it = ProjectList.begin();it!= ProjectList.end();it++)
//	{
//		HPROJECT actProject = (*it);

		HPROJECT actProject = m_hProject;
		TRY	
		{                   
		//	Ini-Dateinamen lesen	
			Profile ProFile(actProject);				    
                        
		//	Puffer init.                        
			const short BufferSize = 1024;
			CString strBuffer;
			char *pBuffer = strBuffer.GetBuffer (BufferSize);
			*pBuffer = '\0';
			
		//	alle gültigen Strings lesen		
			CString Section;
			VERIFY(Section.LoadString (IDS_ODBC_SECTION));
			if (!GetPrivateProfileString (Section, NULL, "", pBuffer, 
				BufferSize, ProFile.GetProFileName ()))
			{
				VERIFY(Section.LoadString (IDS_ODBC_SECTION_OLD));
				if (!GetPrivateProfileString (Section, NULL, "", pBuffer, 
					BufferSize, ProFile.GetProFileName ()))
				{
					return EC_ILLPARS; // und tschüß
				}
			}

			ulong lIdent = 0;		// akt. ID
			long *pMKs = NULL;
			char **ppMStrs = NULL;
			short sCnt = 0;			// Anzahl der zum Eintrag gelesenen Werte
			CString strSlave;		// aktueller Slave-String
			CString strActMaster = m_strMaster;	// aktuelle Master-Connection
			strActMaster += RelatSep;
			strActMaster += m_strKoppelFeld;    
			CString strActSlave, strActKoppelFeld;
			short sActType = -1;		// aktueller SQL-Typ: unbekannt
			
		//	alle Anbindungen mit wenigstens 3 Parametern in AddSlaveListe ausgeben			
			for (char *pBuff = pBuffer; *pBuff; pBuff += lstrlen (pBuff) + 1)
			{                
			//	aktuellen ID bestimmen                                         
				if (FAILED(IdentFromClassX (actProject, pBuff + 2, &lIdent, FALSE)) || (InvalidIdent(lIdent)))
					lIdent = (ulong) -1L;		// Standard lesen
					
				sCnt = ProFile.ReadOdbcCodes (&pMKs, &ppMStrs, (long) lIdent);
				if ((sCnt >= MinParCnt)										// wenigstens 3 Parameter 
					&& (pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0])	// AliasName OK
					&& (pMKs [1] == -1) && (ppMStrs [1] != NULL) && (*ppMStrs [1]))	// FeldName OK	
				{                       
				//	Verbindung zusammenbauen
					strSlave = ppMStrs [0];	
					strSlave += RelatSep;
					strSlave += ppMStrs [1];
					// strSlave.MakeUpper ();		// alles in Großbuchstaben
					if ((strActMaster != strSlave) &&                         	// verschieden dem ges. Master
						(m_CDelSlaveList.FindString (-1, strSlave) == LB_ERR))  // und nicht in akt. Liste
					{   
					
					//	Typ-Kompatibilität prüfen           
						strActSlave = ppMStrs [0]; 
						strActKoppelFeld = ppMStrs [1];
						sActType = GetSQLType (strActSlave, strActKoppelFeld);
						if (SQLTypesCompatible (m_sType, sActType))
						{
							if (m_CDelSlaveList.AddString (strSlave) >= 0)				// speichern		
								m_sMaxStrLen = max (strSlave.GetLength (), m_sMaxStrLen);	// max. Länge setzen
							else
							{                                                                 
								DEX_Error (RC_ReadSlavesCRelDialog, m_ecResult = EC_NOMEMORY);	
							}
						}	// hier keine Meldung, nur (typkompatible) 1						
					}		// bereits gespeichert !				
				}			// keine vollst. Anbindung vorh.		
				
			//	MKodes und MStr-Speicher freigeben
				for (short i = 0; i < sCnt; i++)
					DELETE_VEC (ppMStrs [i]);
				DELETE_VEC (ppMStrs);
				DELETE_VEC (pMKs);

			}	// end_for
		}		
		CATCH (CMemoryException, cme)
		{
			DEX_Error (RC_ReadSlavesCRelDialog, m_ecResult = EC_NOMEMORY);
		}	  
		END_CATCH       
//	}
	
	return m_ecResult;		
}	

// Die zum aktuellen Master gehörenden Slaves lesen
ErrCode CRelDialog ::  ReadActSlaves (void)
{
	TRY
	{                       
	//	Slave-Anbindungen lesen
		Profile ProFile(m_hProject);
		DBaseRel MasterRel (m_strMaster, m_strKoppelFeld);                   
		DBaseRel **ppDR = NULL;		
		short sCnt = ProFile.ReadOdbcRelations (MasterRel, &ppDR);
		if (sCnt == 0)
			return EC_OKAY;   
         
	//	alle Relationen ausgeben         
		m_CDelSlaveList.ResetContent ();	// alten Einträge löschen
		CString strRel;
		short sActType = -1;				// akt. SQL-Type: unbekannt
		for (short i = 0; i < sCnt; i++)
		{            
		//	String zusammenbauen           
			strRel = ppDR [i] -> GetDBName ();
			strRel += RelatSep;
			strRel += ppDR [i] -> GetFieldName ();	            
			
		// 	wenn Eintrag bereits geprüft, weiter
			if (m_CDelSlaveList.FindString (-1, strRel) == LB_ERR)
			{
			
			// 	Typ-Kompatibilität prüfen
				sActType = GetSQLType (ppDR [i] -> GetDBName (), ppDR [i] -> GetFieldName ());
				if (! SQLTypesCompatible (m_sType, sActType))
					continue;		// weiter
			}				
			                                    
		//	Relation ans akt. Ende der DelSlaveListBox ausgeben			                                    
			if (m_CDelSlaveList.AddString (strRel) >= 0)
				m_sMaxStrLen = max (strRel.GetLength (), m_sMaxStrLen);	// max. Länge setzen
			else
			{
				DEX_Error (RC_ReadActSlavesCRelDialog, m_ecResult = EC_SYSERROR);
			}
			
		}			
		
	//	Relationsfelder freigeben
		for (short j = 0; j < sCnt; j++)
			DELETE_OBJ (ppDR [j]);
		DELETE_VEC (ppDR);								
	}
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_ReadActSlavesCRelDialog, m_ecResult = EC_NOMEMORY);		     
		return EC_NOMEMORY;		     	
	}
	END_CATCH		             
	
//	StoreMasterButton ggf. aktivieren
	if (m_CDelSlaveList.GetCount () > 0)
		m_CStoreButton.EnableWindow ();
		
	return EC_OKAY;		
}

// aktuellen Master-Anbindungen speichern                                     
void CRelDialog :: StoreRel (void) 
{              

//	kein Speichern erforderlich/notwendig      
//	JG warum nicht, alle Relationen wurden gelöscht, also müssen wir schreiben 
//	if (m_CDelSlaveList.GetCount () == 0)
//		return;
        
	TRY
	{                                       
	//	aktuellen Master-Connection zusammenbauen
		CString strMaster = m_strMaster;	
		strMaster += RelatSep;
		strMaster += m_strKoppelFeld;
		
		CString strActSlave;	// aktueller Slave
		CString strSlave;		// alle Slaves speichern
		short sCnt = m_CDelSlaveList.GetCount ();
		// JG wenn keine Relation mehr existiert, dann leeren Eintrag generieren (sollte den alten Eintrag löschen) 
		if (sCnt != 0)
		{
			char Buffer [10] = "";
			strSlave = itoa (sCnt, Buffer, 10);
			strSlave += ",";
		}
		for (short i = 0; i < sCnt; i++)
		{
			m_CDelSlaveList.GetText (i, strActSlave);
			strSlave += strActSlave;
			if (i < (sCnt - 1))
				strSlave += ",";
		}
		CString Section;
		Section.LoadString (IDS_ODBC_RELATION);
		Profile Profile(m_hProject);
		WritePrivateProfileString (Section, strMaster, strSlave, Profile.GetProFileName ());
	}    
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_OnStoreCRelDialog, m_ecResult = EC_NOMEMORY);		     
		return;		     	
	}
	END_CATCH		                                         
}                                  

//	lese SQL-Type zur gegebenen Connection
short CRelDialog :: GetSQLType (const char *pMaster, const char *pKoppelFeld)
{   
	short sType = -1;			// unbekannter Typ

	Profile ProFile(m_hProject);

	StringDup strTableName (ProFile.GetTableName (pMaster), TRUE);
	if (! strTableName) 
	{               
		DEX_Error (RC_GetSQLTypeCRelDialog, m_ecResult = EC_NOTABLENAME);
		return -1;
	}                                               

	CDataBaseEx *pCDataBase = NULL;
	CColumns *pCColumns = NULL;        
	TRY 
	{                                                        
		pCDataBase = new CDataBaseEx ();
		// 
#pragma MSG("hier muß noch das Projekt bestimmt werden")
		if (!pCDataBase -> OpenAlias (pMaster, m_hProject))
		{
			DELETE_OBJ (pCColumns);
			return -1;
		}
		pCColumns = new CColumns ((CDatabase *) pCDataBase);  
		
	//	Tabellen-Namen speichern				
		pCColumns -> m_strTableNameParam = strTableName;        
		if (pCColumns -> Open ()) 
		{   
		//	FeldInfo lesen		
			while (! pCColumns -> IsEOF())
			{   
				if (strcmpi (pKoppelFeld, pCColumns -> m_strColumnName) == 0)
				{
					sType = pCColumns -> m_nDataType;		// Typ speichern und raus
					break;
				}	
				
			// 	lese nächste Feld-Info       
				pCColumns -> MoveNext();                      
			}			
		}			
	}	 
	CATCH (CMemoryException, e)	
	{   
		DEX_Error (RC_GetSQLTypeCRelDialog, m_ecResult = EC_NOMEMORY);               
	}                
	AND_CATCH (CDBException, dbe)   
	{            
		m_ecResult = EC_SYSERROR;       
		OdbcError oe (dbe);
		oe.Show (RC_GetSQLTypeCRelDialog);                 
	}
	END_CATCH                                               
	
//	Speicher freigeben	                    
	DELETE_OBJ (pCColumns);         // Spalten-Info-Objekt
	DELETE_OBJ (pCDataBase);		// Data-Source-Objekt
	
	return sType;
}

//	selektierten Einträge innerhalb der ListBoxen austauschen	
void CRelDialog :: ChangeSelection (CListBox &lbSrc, CListBox &lbDest)
{   
//	Anzahl der selektierten Einträge lesen
	int iCnt = lbSrc.GetSelCount ();
	if (iCnt <= 0)
		return;     
		
//	Inidizes der selektierten Einträge lesen
	int *pIndexArray = NULL;
	TRY
	{                 
		pIndexArray = new int [iCnt];
		if (lbSrc.GetSelItems (iCnt, pIndexArray) != iCnt)	// lese Indizes
		{
			DELETE_VEC (pIndexArray);
			return;
		}	    
	}		
	CATCH (CMemoryException, me)
	{          
		DEX_Error (RC_ChangeSelectionCRelDialog, EC_NOMEMORY);                 
		return;
	}
	END_CATCH		
		
//	Einträge kopieren 
	CString strBuffer;
	int i;
	for (i = 0; i < iCnt; i++)
	{
		lbSrc.GetText (pIndexArray [i], strBuffer);
		lbDest.AddString (strBuffer);	
	}				
        
//	Einträge in Source-ListBox löschen
	for (i = iCnt - 1; i >= 0; i--)
		lbSrc.DeleteString (pIndexArray [i]);
		
	DELETE_VEC (pIndexArray);		// Speicher freigeben		
}

//	Event-Handler --------------------------------------------------------------------
//     
//	weitere Relationen selektiert
afx_msg void CRelDialog :: OnSelWeitere (void)
{                                
//	m_btRemRel.EnableWindow (m_CAddSlaveList.GetCount () > 0 ? TRUE : FALSE);
}   

// 	vorhandene Relationen selektiert
afx_msg void CRelDialog :: OnSelVorhandene (void)
{                                
//	m_btAddRel.EnableWindow (m_CDelSlaveList.GetCount () > 0 ? TRUE : FALSE);    
	m_CStoreButton.EnableWindow (m_CDelSlaveList.GetCount () > 0 ? TRUE : FALSE);
	m_DelButton.EnableWindow(m_CDelSlaveList.GetCount () > 0 ? TRUE : FALSE);
}   

//	neue Slave-Anbindung zum aktuellen Master 	              
afx_msg void CRelDialog :: OnAddSlave (void)
{                            
//	ChangeSelection (m_CAddSlaveList, m_CDelSlaveList);
	m_CStoreButton.EnableWindow (m_CDelSlaveList.GetCount () > 0 ? TRUE : FALSE);
//	m_btRemRel.EnableWindow (FALSE);	
}
 
// aktuelle Slave-Anbindung vom Master entfernen 
afx_msg void CRelDialog :: OnDelSlave (void)
{   
//	ChangeSelection (m_CDelSlaveList, m_CAddSlaveList);                          
//	m_btAddRel.EnableWindow (FALSE);    
}
// JG löschen von so'n paar Elementen
afx_msg void CRelDialog :: OnDelete (void)
{   
//	ChangeSelection (m_CDelSlaveList, m_CAddSlaveList);                          
//	m_btAddRel.EnableWindow (FALSE);    
	ChangeSelection (m_CDelSlaveList, m_CAddSlaveList);		// ReUsable ?????? 
	m_DelButton.EnableWindow(m_CDelSlaveList.GetCount () > 0 ? TRUE : FALSE);
}

// aktuellen Master-Anbindungen speichern                                     
afx_msg void CRelDialog :: OnOK (void) 
{   
	StoreRel ();                
	EndDialog (IDOK);		// Dialog beenden	
}
    
// freie Relation erzeugen
afx_msg void CRelDialog :: OnFreeRelation (void) 
{
	CFreeRelDialog dlg (this, m_strMaster, m_strKoppelFeld, m_sType, m_hProject);         
	if (dlg.Result () && dlg.DoModal () == IDOK)
	{	
	//	Relation ausgeben
		TRY
		{
			CString strSlave;
			CString strKoppelField;
			if (dlg.GetRelation (strSlave, strKoppelField) == False)
				return;
			strSlave += RelatSep;
			strSlave += strKoppelField;						
			// strSlave.MakeUpper ();
			if (m_CDelSlaveList.FindString (1, strSlave) == LB_ERR /*&&                         	// verschieden dem ges. Master
				m_CAddSlaveList.FindString (-1, strSlave) == LB_ERR*/)  // und nicht in akt. Liste
			{
				m_CDelSlaveList.AddString (strSlave);				// speichern		
				
			//	Scrollrange evtl. neu setzen								
				if (strSlave.GetLength () > m_sMaxStrLen)
				{
					m_sMaxStrLen = strSlave.GetLength ();
					WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
					m_CDelSlaveList.SetHorizontalExtent (wUnits * m_sMaxStrLen);					
				}
			}
	    }
		CATCH (CMemoryException, me)
		{		                         
			DEX_Error (RC_OnFreeRelCRelDialog, EC_NOMEMORY);		
		}
		END_CATCH			
	}		
}



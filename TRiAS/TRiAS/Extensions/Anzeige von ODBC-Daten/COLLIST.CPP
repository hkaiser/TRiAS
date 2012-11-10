/*
File: COLLIST.CPP
- speichere  Spalten-Infos einer ODBC-Tabelle in einem Container.

Erarbeitet: J.Benkenstein					Stand vom 13. Mai 1994
*/
                                                 
#include "pheader.h"		// vorübersetzte Header                                                 
#include "odbcext.hr"		// Ressourcen	
                                       
#include <hpp/columnst.hpp>		// CColumns       
#include <hpp/collist.hpp>		// zugehör. Header 
#include <hpp/odbcerr.hpp>      // OdbcError 

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstanten
const short cMaxIntLength = 15;			// max. Darstellungs-Längen
const short cMaxFloatLength = 25;
const short cMaxTimeLen = 8;      		// hh:mm:ss
const short cMaxDateLen = 10;			// yyyy-mm-dd
const short cMaxTimeStampLen = 19;		// yyyy-mm-dd hh:mm:ss
const char fKoordFormat [] = "%.5f";	// Formate der Datentypen		
const char dKoordFormat [] = "%.5lf";	

// externe Funktionen
char *DtoA (double Wert, char *String, const char *Format = NULL); 
int yylexr (char *pFirstChar);

// CColumnObj --------------------------------------------------------------------
CColumnObj :: CColumnObj (CColumns &OneCol, short sIndex)
{               
	m_pValue = NULL;
	m_bResult = TRUE;
	m_sRFXType = OneCol.m_nRFXType;			// RFX-Daten-Typ
	m_sSQLType = OneCol.m_nDataType;		// SQL-Daten-Typ
	m_sRadix = OneCol.m_nRadix;				// Radix für Konvertierung
	m_sShowLen = 0;							// Darstellungs-Länge rücksetzen
	m_lFieldLen = OneCol.m_lLength;			// Länge speichern
	m_sIndex = sIndex;						// Index im ArrayContainer
	
	TRY	
	{           
		m_strSQLTypeName = OneCol.m_strTypeName;
		m_strColName = OneCol.m_strColumnName;
		AfxFormatString1 (m_strBracketsColName, IDS_FIELDNAME_FORMAT, m_strColName);
		switch (m_sRFXType)
		{              
			case AFX_RFX_TEXT:                  
			{
				m_pValue = new CString;      
				m_sShowLen = (short) OneCol.m_lLength;
			}				
			break;								
			case AFX_RFX_INT:           
			{
				m_pValue = new int; 	
				m_sShowLen = cMaxIntLength;				
			}				
			break;
			case AFX_RFX_LONG:
			{
				m_pValue = new long; 	
				m_sShowLen = cMaxIntLength;				
			}	
			break;
			case AFX_RFX_SINGLE:
			{
				m_pValue = new float; 	
				m_sShowLen = cMaxFloatLength;				
			}				
			break;
			case AFX_RFX_DOUBLE:                            
			{
				m_pValue = new double; 	                    
				m_sShowLen = cMaxFloatLength;				
			}				
			break;						
			case AFX_RFX_BYTE:            	
			{
				m_pValue = new BYTE;
				m_sShowLen = 1;				
			}	
			break;				 	                 
			case AFX_RFX_BOOL:            	
			{
				m_pValue = new BOOL; 	
				m_sShowLen = 1;				
			}				
			break;
			case AFX_RFX_DATE:
			{
				m_pValue = new CTime; 	
				switch (m_sSQLType)
				{
					case SQL_DATE:  
						m_sShowLen = cMaxDateLen;										
					break;
					case SQL_TIME:              
						m_sShowLen = cMaxTimeLen;				
					break;
					case SQL_TIMESTAMP:         
						m_sShowLen = cMaxTimeStampLen;				
					break;					
				}
			}				
			break;
			case AFX_RFX_BINARY:
			{
				m_pValue = new CByteArray; 	
				m_sShowLen = m_strSQLTypeName.GetLength () + 1;		// für "*"
			}				
			break;						                 			                        						                 			                        
			case AFX_RFX_LONGBINARY:
			{
				m_pValue = new CLongBinary;                                   
				m_sShowLen = m_strSQLTypeName.GetLength () + 1;		// für "*"
			}				
			break;
			default:
			{
				m_bResult = FALSE;			
				DEX_Error (RC_ctCColumnObj, EC_UNKN_FIELD_TYPE);
			}				
			break;				
		}
	}
	CATCH (CMemoryException, cme)
	{
		m_bResult = FALSE;           
		DEX_Error (RC_ctCColumnObj, EC_NOMEMORY);
	}
	END_CATCH		
}	

CColumnObj :: ~CColumnObj (void)
{
	switch (m_sRFXType)
	{              
		case AFX_RFX_TEXT:                  
			delete (CString *) m_pValue;
		break;								
		case AFX_RFX_INT:
			delete (int*) m_pValue; 	
		break;
		case AFX_RFX_LONG:
			delete (long*) m_pValue;
		break;
		case AFX_RFX_SINGLE:
			delete (float*) m_pValue; 	
		break;
		case AFX_RFX_DOUBLE:
			delete (double*) m_pValue; 
		break;						
		case AFX_RFX_BYTE:            	
			delete (BYTE*) m_pValue; 
		break;				 	                 
		case AFX_RFX_BOOL:            	
			delete (BOOL*) m_pValue;  	
		break;
		case AFX_RFX_DATE:
			delete (CTime*) m_pValue; 
		break;
		case AFX_RFX_BINARY:
			delete (CByteArray*) m_pValue; 	
		break;						                 			                        						                 			                        
		case AFX_RFX_LONGBINARY:
			delete (CLongBinary*) m_pValue; 
		break;
		default:
			// do nothing
		break;			
	}               
	
	m_pValue = NULL;		// Zeiger wird ungültig	
}
                                                           
// CColumnObjArray ---------------------------------------------------------------
CColumnObjArray :: CColumnObjArray (int iSize)
			    : CArrayContainer (iSize)		// für 30 Feldinfos init. (default)
{
	m_sMaxTypeNameLen = m_sMaxNameLen = m_sMaxShowLen = 0;
	m_sActIndex = 0;
}			    
                                     
CColumnObjArray :: ~ CColumnObjArray (void)
{
	EveryDelete ();
}

void __export CColumnObjArray :: UserDelete (void *pObj)
{
	((CColumnObj *) pObj) -> ~CColumnObj ();
}

// neue Spalten-Info speichern
BOOL CColumnObjArray :: AddColInfo (CColumns &OneCol)
{                      
CColumnObj *pCO = NULL;
CColumnObjCreator cr (*this);

	TRY
	{
		pCO = :: ContCreate (cr, CColumnObj) (OneCol, m_sActIndex++);
	}
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_AddColInfoColObjArr,  EC_NOMEMORY);
		return FALSE;			
	}	             
	END_CATCH
	             
//	max. Längen aktualisieren	             
	m_sMaxNameLen = max (m_sMaxNameLen, pCO -> ColName ().GetLength ()); 	 
	m_sMaxShowLen = max (m_sMaxShowLen, pCO -> ShowLen ()); 	
	m_sMaxTypeNameLen = max (m_sMaxTypeNameLen, pCO -> SQLTypeName ().GetLength ());
				
	return pCO -> Result ();
}
                                                                
// lese SQL-Typ über geg. Feldnamen
// Tree ist hier leider nicht möglich: Konflikt im RFX	                                                                
// bei Fehler -1	
short CColumnObjArray :: GetSQLType (char *pFieldName)
{
//	prüfe Parameter
	if (!pFieldName || !*pFieldName)
		return -1;
		
//	suche im Container
	CRing ri (*this);
	for (ri.First (); ri.Valid (); ri.Next ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_GetSQLTypeColObjArr, EC_LOCKERROR);			
			return -1;
		}                       
		if (strcmpi (pFieldName, pCO -> ColName ()) == 0)
			return pCO -> SQLType ();
	}
	
	DEX_Error (RC_GetSQLTypeColObjArr, EC_UNKN_FIELD_NAME); 	
	return -1;			
}

// lese SQL-Typ über geg. Feldindex
// bei Fehler -1	
short CColumnObjArray :: GetSQLType (short sIndex)
{
//	prüfe Parameter
	ASSERT (sIndex >= 0 && sIndex < (short) Count ());

	CRing ri (*this);
	if (ri.Goto ((ulong) sIndex) && ri.Valid ())
	{
		CColumnObjLock pCO (ri);
		if (pCO)
			return pCO -> SQLType ();
		else
			DEX_Error (RC_GetSQLTypeColObjArr, EC_LOCKERROR);			
	}

	return -1;
}

// lese SQL-Länge über geg. Feldindex
// bei Fehler 0	
long CColumnObjArray :: GetFieldLen (short sIndex)
{
	ASSERT (sIndex >= 0 && sIndex < (short) Count ());

	CRing ri (*this);
	if (ri.Goto ((ulong) sIndex) && ri.Valid ())
	{
		CColumnObjLock pCO (ri);
		if (pCO)
			return pCO -> FieldLen ();
		else
			DEX_Error (RC_GetFieldLenColObjArr, EC_LOCKERROR);			
	}

	return 0;
}
	
// lese SQL-Länge über geg. Feldnamen
// bei Fehler 0	
long CColumnObjArray :: GetFieldLen (char *pFieldName)
{
//	prüfe Parameter
	if (!pFieldName || !*pFieldName)
		return 0;
		
//	suche im Container
	CRing ri (*this);
	for (ri.First (); ri.Valid (); ri.Next ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_GetFieldLenColObjArr, EC_LOCKERROR);			
			return 0;
		}                       
		if (strcmpi (pFieldName, pCO -> ColName ()) == 0)
			return pCO -> FieldLen ();
	}
	
	DEX_Error (RC_GetFieldLenColObjArr, EC_UNKN_FIELD_NAME); 	
	return 0;			
}

CString ExpandApostrophs(CString strValue)
{
CString str;

	for (int i = 0; i < strValue.GetLength(); ++i)
	{
		if ('\'' == strValue.GetAt(i))
			str += '\'';
		str += strValue.GetAt(i);
	}	
	return str;
}

//	WHERE-Klausel für SELECT-Anweisung erzeugen                    
BOOL CColumnObjArray :: BuildWhereKlausel (CString &strWhere, char *pFieldName, 
								    	   char *pFieldValue, BOOL bOutErr)
{								    
//	prüfe Parameter
	if (!pFieldName || Count () == 0)
	{
		if (bOutErr)
		{
			DEX_Error (RC_BuildWhereKlColObjArr, EC_ILLPARS);
		}
		return FALSE;
	}	
	
	if (!*pFieldName)
		return FALSE;	

	TRY
	{

		if ( pFieldValue != NULL && lstrlen (pFieldValue) > 0 )
			AfxFormatString1 (strWhere, IDS_FIELDNAME_FORMAT, pFieldName);
		else	// Spezial-Fall: vollst. Klausel bereits im Feldnamen enth.	
		{
			strWhere = pFieldName;
			return TRUE;			 
		}
	
	//	ensprechend dem Feld-Typ eine Klausel erzeugen
		strWhere += "=";
	                      
	//	lese Typinfo		
		short sSQLType = GetSQLType (pFieldName);
		switch (sSQLType) {
		// keine Anfrage für diese Typen möglich oder sinnvoll !          
		case SQL_BIT:
		case SQL_TINYINT:
		case SQL_BINARY:
		case SQL_VARBINARY:
		case SQL_LONGVARCHAR:
		case SQL_LONGVARBINARY:
			{                                                 
				if (bOutErr)
				{
					DEX_Error (RC_BuildWhereKlColObjArr, EC_NO_QUERY_POSSIBLE);
				}
				return FALSE;
			}
			break;

		case SQL_SMALLINT:
		case SQL_INTEGER: 		
		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:				// von TRiAS nur numer. Typen zulassen
			{
			short sTriasType = yylexr (pFieldValue);
			
				if (sTriasType == SQL_DOUBLE || sTriasType == SQL_INTEGER)	
					strWhere += pFieldValue;		
				else
					return FALSE;				
			}
			break;

		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:		// hier strenge Typprüfung notwendig !
			{
				if (yylexr (pFieldValue) == sSQLType) {
					strWhere += "#";
					strWhere += pFieldValue;
					strWhere += "#";			
				}
				else
					return FALSE;
			}
			break;

		case SQL_DECIMAL:   // ODBC default xfer type
		case SQL_NUMERIC:   // ODBC default xfer type
		case SQL_BIGINT: 	// ODBC default xfer type
		case SQL_CHAR:
		case SQL_VARCHAR:	//	der TRiAS-Wert wird jetzt immer als Text interpretiert 
			{
			//	hier Längen prüfen
				if (lstrlen (pFieldValue) > GetFieldLen (pFieldName))
					return FALSE;						
				strWhere += "\'";
				strWhere += ExpandApostrophs(pFieldValue);
				strWhere += "\'";			
			}
			break;

		//	für alle unbekannten		
		default:
			{	// Fehlermeldung bereits ausgegeben
				return FALSE;			
			}				
			break;				
		}
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_BuildWhereKlColObjArr, EC_NOMEMORY);		
		return FALSE;
	}		
	END_CATCH
	
	return TRUE;
}

// Feldnamen- und typ in Liste ausgeben
BOOL CColumnObjArray :: FillColumnList (CColumns &ColStatus) 
{               	
// 	Lese alle Infos über alle Felder
	TRY
	{
		for (ColStatus.MoveFirst (); ! ColStatus.IsEOF(); ColStatus.MoveNext())
		{                                                                 
		// 	Feld-Info speichern
			if (! AddColInfo (ColStatus))
				return FALSE;
		}
	}
	CATCH (CDBException, dbe)
	{                 
		OdbcError oe (dbe);
		oe.Show (); 			       
		return FALSE;
	}			
	END_CATCH

	return TRUE;
}

//	lese, soweit möglich, den Inhalt des angegebenen Feldes als Zeichenkette	     
BOOL CColumnObjArray :: GetFieldInfo (CRecordset *pRS, CString &strOutput, 
									  const char *pFieldName)
{
//	prüfe Parameter
	ASSERT (pFieldName != NULL && AfxIsValidString (pFieldName));

//	prüfe Parameter
	if (!pRS)
	{
		DEX_Error (RC_GetFieldInfoColumnObjArr, EC_ILLPARS);
		return FALSE;
	}		                                

	if (pRS -> IsOpen () == FALSE)        
	{
		DEX_Error (RC_GetFieldInfoColumnObjArr, EC_SYSERROR);
		return FALSE;
	}		                                
	
//	suche Objekt im Container
	CRing ri (*this);
	short sFeldIndex = 1;
	for (ri.First (); ri.Valid (); ri.Next (), sFeldIndex++)
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_GetFieldInfoColumnObjArr, EC_LOCKERROR);			
			return FALSE;
		}                       
		if (strcmpi (pFieldName, pCO -> ColName ()) == 0)
			return GetFieldInfo (sFeldIndex, strOutput, pCO, pRS);
	}       			
	
	return FALSE;			
}

//	lese, soweit möglich, den Inhalt des angegebenen Feldes als Zeichenkette	     
BOOL CColumnObjArray :: GetFieldInfo (CRecordset *pRS, CString &strOutput, short sIndex)
{
//	prüfe Parameter
	ASSERT (sIndex >= 0 && sIndex < (short) Count ());
	ASSERT (pRS != NULL);

	CRing ri (*this);
	if (ri.Goto ((ulong) sIndex) && ri.Valid ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_GetFieldInfoColumnObjArr, EC_LOCKERROR);			
			return FALSE;
		}
		return GetFieldInfo (sIndex+1, strOutput, pCO, pRS);
	}

	return FALSE;
}

//	lese Feldinformation
BOOL CColumnObjArray :: GetFieldInfo (short sFeldIndex, CString &strOutput, CColumnObj *pCO,
									  CRecordset *pRS)
{
//	prüfe Parameter
	ASSERT (sFeldIndex > 0);
	ASSERT (pCO != NULL && pRS != NULL);

	TRY 
	{	
		char Buffer [40] = "";
		strOutput.Empty ();		// Ausgabe-String leeren

#if (_MFC_VER >= 0x0420)	// #HK960812: ???
		if ((pRS -> GetFieldStatus(sFeldIndex-1) & AFX_SQL_FIELD_FLAG_NULL) == 0)
		// if (!pRS -> IsFieldStatusNull (sFeldIndex-1))
#else
		if (! pRS -> IsFieldFlagNull (sFeldIndex, 
									  CFieldExchange :: outputColumn))
#endif // _MFC_VER
		{					
			switch (pCO -> RFXType ())
			{              
				case AFX_RFX_TEXT:                      
					strOutput +=  *((CString *) pCO -> Value ());
				break;                                                  
				case AFX_RFX_INT:
					strOutput += itoa (*((int *) pCO -> Value ()), Buffer, pCO -> Radix ());
				break;
				case AFX_RFX_LONG:                                              
					strOutput += ltoa (*((long *) pCO -> Value ()), Buffer, pCO -> Radix ());
				break;
				case AFX_RFX_SINGLE:    
					strOutput += DtoA (*((float *) pCO -> Value ()), Buffer, fKoordFormat); 
				break;
				case AFX_RFX_DOUBLE:
					strOutput += DtoA (*((double *) pCO -> Value ()), Buffer, dKoordFormat);                           
				break;                                          
				case AFX_RFX_BYTE:                                             
					strOutput += itoa (*((BYTE *) pCO -> Value ()), Buffer, 10);
				break;                                                   
				case AFX_RFX_BOOL:            
					strOutput += *((BOOL *) pCO -> Value ()) ? "1" : "0";   
				break;
				case AFX_RFX_DATE:                 
				{               
					CTime *pTime = (CTime *) pCO -> Value ();
					if (pCO -> SQLType () == SQL_DATE ||      // "normales" Datum
						pCO -> SQLType () == SQL_TIMESTAMP)   // oder Zeitstempel
					{   
						strOutput += itoa (pTime -> GetYear (), Buffer, 10);                                                                                                                                               
						strOutput += "-";
						strOutput += itoa (pTime -> GetMonth (), Buffer, 10);
						strOutput += "-";
						strOutput += itoa (pTime -> GetDay (), Buffer, 10);
					}                                               
								
					if (pCO -> SQLType () == SQL_TIME ||       // Zeit
						pCO -> SQLType () == SQL_TIMESTAMP)    // oder Zeitstempel                                                                     
					{
						if (pCO -> SQLType () == SQL_TIMESTAMP)
							strOutput += " ";                                       // als Separator                                                        
						strOutput += itoa (pTime -> GetHour (), Buffer, 10);
						strOutput += ".";
						strOutput += itoa (pTime -> GetMinute (), Buffer, 10);
						strOutput += ".";
						strOutput += itoa (pTime -> GetSecond (), Buffer, 10);                                                                                          
					}
				}                                                                                   
				break;
				case AFX_RFX_BINARY:
				case AFX_RFX_LONGBINARY:               
				break;
				default:
				{                       
					DEX_Error (RC_GetFieldInfoColumnObjArr, EC_UNKN_FIELD_TYPE);
				}                                       
				break;                          
			}       // end_switch
		}			// keine Info vorhanden					
	}
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_GetFieldInfoColumnObjArr, EC_NOMEMORY);
	}	
	END_CATCH			

	return strOutput.IsEmpty () ? FALSE : TRUE;
}

//	Index lesen
short CColumnObjArray :: GetIndex (const char *pFieldName)
{
//	prüfe Parameter
	ASSERT (pFieldName != NULL && AfxIsValidString (pFieldName));

//	suche Objekt im Container
	CRing ri (*this);
	for (ri.First (); ri.Valid (); ri.Next ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_GetFieldInfoColumnObjArr, EC_LOCKERROR);			
			return -1;
		}                       
		if (strcmpi (pFieldName, pCO -> ColName ()) == 0)
			return pCO -> Index ();
	}       			

	DEX_Error (RC_ctCColumnObj, EC_UNKN_FIELD_NAME);

	return -1;
}

//	lese Feldnamen über geg. Index
//	bei Fehler NULL
const char *CColumnObjArray :: GetFeldName (short sIndex)
{
//	prüfe Parameter
	ASSERT (sIndex >= 0 && sIndex < (short) Count ());

	CRing ri (*this);
	if (ri.Goto ((ulong) sIndex) && ri.Valid ())
	{
		CColumnObjLock pCO (ri);
		if (pCO)
			return pCO -> ColName ();
		else
			DEX_Error (RC_GetSQLTypeColObjArr, EC_LOCKERROR);			
	}

	return NULL;
}

//	schreibe, soweit möglich, den Inhalt der angegebenen Zeichenkette ins Feld	     
SetInfoResult CColumnObjArray :: SetFieldInfo (const char *pValue, short sIndex)
{
//	prüfe Parameter
	ASSERT (sIndex >= 0 && sIndex < (short) Count ());
	ASSERT (pValue != NULL && AfxIsValidString (pValue));

	CRing ri (*this);
	if (ri.Goto ((ulong) sIndex) && ri.Valid ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_SetFieldInfoColumnObjArr, EC_LOCKERROR);			
			return OkSet;
		}
		return SetFieldInfo (pValue, pCO);
	}

	return NotSet;
}

//	schreibe, soweit möglich, den Inhalt der angegebenen Zeichenkette ins Feld	     
SetInfoResult CColumnObjArray :: SetFieldInfo (const char *pValue, const char *pFieldName)
{
//	prüfe Parameter
	ASSERT (pValue != NULL && AfxIsValidString (pValue));
	ASSERT (pFieldName != NULL && AfxIsValidString (pFieldName));

	CRing ri (*this);
	for (ri.First (); ri.Valid (); ri.Next ())
	{
		CColumnObjLock pCO (ri);
		if (pCO == NULL)
		{
			DEX_Error (RC_SetFieldInfoColumnObjArr, EC_LOCKERROR);			
			return NotSet;
		}                       
		if (strcmpi (pFieldName, pCO -> ColName ()) == 0)
			return SetFieldInfo (pValue, pCO);
	}

	return NotSet;
}

//	schreibe Feldinformation
SetInfoResult CColumnObjArray :: SetFieldInfo (const char *pVal, CColumnObj *pCO)
{
//	prüfe Parameter
	ASSERT (pCO != NULL);
	ASSERT (pVal != NULL && AfxIsValidString (pVal));

	short sRet = OkSet;

	TRY 
	{	
		switch (pCO -> RFXType ())
		{              
			case AFX_RFX_TEXT:                      
			{
				CString strT (pVal);
				if (strT.GetLength () > pCO -> FieldLen ())
				{
					sRet = InfoTruncated;
					strT = strT.Left ((int)pCO -> FieldLen ());
				}
				*((CString *) pCO -> Value ()) = strT;
			}
			break;                                                  
			case AFX_RFX_INT:
				*((int *) pCO -> Value ()) = atoi (pVal);
			break;
			case AFX_RFX_LONG:                                              
				*((long *) pCO -> Value ()) = atol (pVal);
			break;
			case AFX_RFX_SINGLE:    
				*((float *) pCO -> Value ()) = (float) atof (pVal);
			break;
			case AFX_RFX_DOUBLE:
				*((double *) pCO -> Value ()) = atof (pVal);
			break;                                          
			case AFX_RFX_BYTE:     
				*((BYTE *) pCO -> Value ()) = atoi (pVal);				
			break;                                                   
			case AFX_RFX_BOOL:            
				*((BOOL *) pCO -> Value ()) = atoi (pVal) > 0 ? 1 : 0;
			break;
			case AFX_RFX_DATE:                 
			{   
				uint iYear, iMonth, iDay, iHour, iMin, iSec;				
				iYear = iMonth = iDay = iHour = iMin = iSec = 0;
				char *pE = NULL;
				if (pCO -> SQLType () == SQL_DATE ||      // "normales" Datum
					pCO -> SQLType () == SQL_TIMESTAMP)   // oder Zeitstempel
				{   
				//	Format: "1990-10-8"
					iYear = (uint)strtoul (pVal,&pE, 10);
					if (pE && *++pE)
					{
						iMonth = (uint)strtoul (pE, &pE, 10);
						if (pE && *++pE)
							iDay = (uint)strtoul (pE, &pE, 10);
					}
				}                                               
								
				if (pCO -> SQLType () == SQL_TIME ||       // Zeit
					pCO -> SQLType () == SQL_TIMESTAMP)    // oder Zeitstempel                                                                     
				{
				//	Format: "1990-10-8 12:05:23"
					if (pE && *++pE)
					{
						iHour = (uint)strtoul (pE, &pE, 10);
						if (pE && *++pE)
						{
							iMin = (uint)strtoul (pE, &pE, 10);
							if (pE && *++pE)
								iSec = (uint)strtoul (pE, NULL, 10);
						}
					}						
				}

			//	Datum/Zeit speichern
				*((CTime *) pCO -> Value ()) = CTime (iYear, iMonth, iDay, 
													  iHour, iMin, iSec);					
			}                                                                                   
			break;
			case AFX_RFX_BINARY:
			case AFX_RFX_LONGBINARY:               
			break;
			default:
			{                       
				DEX_Error (RC_SetFieldInfoColumnObjArr, EC_UNKN_FIELD_TYPE);
				return NotSet;
			}                                       
			break;                          
		}       // end_switch
	}
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_SetFieldInfoColumnObjArr, EC_NOMEMORY);
		return NotSet;
	}	
	END_CATCH			

	return (SetInfoResult) sRet;
}


/*
FILE: ODBCERR.CPP
- Anzeigen einer durch ODBC erzeugten Fehlermeldung.

Erarbeitet: J. Benkenstein		Stand vom 14. September 1994
*/

#include "pheader.h"        // vorübersetzte Header                                      
#include "odbcext.hr"		// Resource-Defines                                      

#include <xtsnpropatl.h>	// CObjectProperties
#include <xtsnimp.hxx>      // ImportInterface
#include <sql.h>			// SQL_INVALID_HANDLE
#include "odbcguid.h"		
#include "odbcext.hpp"		// COdbcExtension
#include <hpp/odbcerr.hpp>		// zugeh. Header

// externe Variablen
extern COdbcExtension *g_pCOdbcExtension;

// OdbcError -------------------------------------------------------------------------
OdbcError :: OdbcError (CDBException *dbe)
{   
	m_sRetCode = dbe ? dbe -> m_nRetCode : 0;	      
	
	TRY
	{	      
		m_strErrText = dbe ? dbe -> m_strError : ""; 		        
		if (m_strErrText.IsEmpty ())
			m_strErrText.LoadString (IDS_UNKNOWN_ERROR);
	}		
	CATCH (CMemoryException, cme)
	{
	}				                  	
	END_CATCH
}                         

void OdbcError :: Show (short RoutCode)
{    
/*
	if (m_sRetCode > AFX_SQL_ERROR &&  	// wenn für diesen Fehlerkode 
		m_sRetCode < AFX_SQL_ERROR_MAX)	// eine Meldung existiert
	{	// durch MFC generierter Fehler	
		// m_sRetCode = m_sRetCode - AFX_SQL_ERROR + AFX_IDP_SQL_FIRST;
		TRY
		{
			CString strError, strCaption;
			strError.LoadString (m_sRetCode);
			strCaption.LoadString (IDS_ODBCERROR);
			:: MessageBox (g_pCOdbcExtension -> hWnd (), m_strError, 
						   strCaption, MB_OK | MB_ICONSTOP);
		}
		CATCH (CMemoryException, cme)
		{
		}				                  	
		END_CATCH
		return;
	}			
*/

//	Dieser Fehler weist auf "Ungereimtheiten" im Programm hin	    
	if (m_sRetCode == SQL_INVALID_HANDLE)
	{
		DEX_Error (RoutCode, EC_SYSERROR);
		return;
	}		
                               
//	"echter" ODBC-Error
	TRY 
	{
		if (NULL != g_pCOdbcExtension)
			g_pCOdbcExtension->Show(m_strErrText);
	}   
	CATCH (CMemoryException, cme)
	{
	}				                  	
	END_CATCH
}	

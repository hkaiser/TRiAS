/*
FILE: ODBCERR.HPP
- Anzeigen einer durch ODBC erzeugten Fehlermeldung.

Erarbeitet: J. Benkenstein				Stand vom 24. März 1994
*/

                 
#ifndef _ODBCERR_HPP                 
#define _ODBCERR_HPP                

class OdbcError
{
protected:   
	short m_sRetCode;
	CString m_strErrText;
public:                        
	OdbcError (CDBException *);
	~ OdbcError (void) {}
	
	void Show (short RoutCode = RC_CommonODBC);	
};

#endif // _ODBCERR_HPP                 


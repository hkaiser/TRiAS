/*
Datei: DAOTOOLS.CPP

Das Modul beinhaltet allgmeine Funktionen zur Arbeit mit den DAO-Klassen.

Erarbeitet: J. Benkenstein			Stand vom 26.7.1996
*/

#include "stdafx.h"		// prec. Header
#include "gak.h"		// Ressourcen	
#include "daotools.h"	// zugeh. Header

//	gebe Abfragetyp als Text zurück
CString GetQueryType (short sType)
{
	CString strType;
	switch (sType)
	{
		case dbQSelect:
			VERIFY (strType.LoadString (IDS_QUERY_SELECTION));
		break;
		case dbQAction:
			VERIFY (strType.LoadString (IDS_QUERY_ACTION));
		break;
		case dbQCrosstab:
			VERIFY (strType.LoadString (IDS_QUERY_CROSSTAB));
		break;
		case dbQDelete:
			VERIFY (strType.LoadString (IDS_QUERY_DELETE));
		break;
		case dbQUpdate:
			VERIFY (strType.LoadString (IDS_QUERY_UPDATE));
		break;
		case dbQAppend:
			VERIFY (strType.LoadString (IDS_QUERY_APPEND));
		break;
		case dbQMakeTable:
			VERIFY (strType.LoadString (IDS_QUERY_MAKE_TABLE));
		break;
		case dbQDDL:
			VERIFY (strType.LoadString (IDS_QUERY_DDL));
		break;
		case dbQSPTBulk:
		case dbQSQLPassThrough:
			VERIFY (strType.LoadString (IDS_QUERY_PASS_THR));
		break;
		case dbQSetOperation:
			VERIFY (strType.LoadString (IDS_QUERY_UNION));
		break;
		default:
			ASSERT (FALSE);
	}

	return strType;
}

//	gebe DaoFeldTyp als Text zurück
CString GetFieldType (short sType)
{
	CString strTypeName;
	switch (sType)
	{
		case dbBoolean:				
			VERIFY (strTypeName.LoadString (IDS_BOOLEAN));
		break;						
		case dbByte:
			VERIFY (strTypeName.LoadString (IDS_BYTE));
		break;
		case dbInteger:
			VERIFY (strTypeName.LoadString (IDS_INTEGER));
		break;
		case dbLong:
			VERIFY (strTypeName.LoadString (IDS_LONG_INTEGER));
		break;
		case dbCurrency:
			VERIFY (strTypeName.LoadString (IDS_WAEHRUNG));
		break;
		case dbSingle:
			VERIFY (strTypeName.LoadString (IDS_SINGLE));
		break;
		case dbDouble:
			VERIFY (strTypeName.LoadString (IDS_DOUBLE));
		break;
		case dbDate:
			VERIFY (strTypeName.LoadString (IDS_DATUM));
		break;
		case dbText:
			VERIFY (strTypeName.LoadString (IDS_TEXT));
		break;
		case dbMemo:
			VERIFY (strTypeName.LoadString (IDS_MEMO));
		break;				
		case dbLongBinary:		
			VERIFY (strTypeName.LoadString (IDS_LONG_BINARY));
		break;
		case dbGUID:
			VERIFY (strTypeName.LoadString (IDS_GUID));
		break;
		default:
			ASSERT (FALSE);
	}

	return strTypeName;
}

//	Fehler-Behandlung realisieren
void DisplayDaoException(CDaoException* e)
{
	ASSERT (NULL != e);
	ASSERT (e -> IsKindOf (RUNTIME_CLASS(CDaoException)));

	CString strMsg;
	if (e->m_pErrorInfo!=NULL)
	{
		CString strCaption;
		strCaption.Format(_T("Datenbankfehler %ld"), e->m_pErrorInfo->m_lErrorCode);
		strMsg.Format(
			_T("\"%s\"\n\n")
			_T("Hilfe zum Fehler aufrufen ?"),
			(LPCTSTR)e->m_pErrorInfo->m_strDescription);

		if (::MessageBox(GetDesktopWindow(), strMsg, strCaption, 
						 MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			CString strHelpFile;
			VERIFY (strHelpFile.LoadString (IDS_ERROR_HELP_FILE_NAME));
			::WinHelp(GetDesktopWindow(),
					  // e->m_pErrorInfo->m_strHelpFile,
					  strHelpFile,
					  HELP_CONTEXT,
					  e->m_pErrorInfo->m_lHelpContext);
		}
	}
	else
	{
		strMsg.Format(
			_T("Fehler: CDaoException\n\n")
			_T("SCODE_CODE		=%d\n")	
			_T("SCODE_FACILITY	=%d\n")	
			_T("SCODE_SEVERITY	=%d\n")	
			_T("ResultFromScode	=%d\n"),
			SCODE_CODE		(e->m_scode),
			SCODE_FACILITY	(e->m_scode),
			SCODE_SEVERITY	(e->m_scode),
			ResultFromScode (e->m_scode));
		::MessageBox(GetDesktopWindow(), strMsg, AfxGetAppName (), 
					  MB_OK|MB_ICONINFORMATION);
	}
}

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	lese Parameterwert einer Abfrage in einen CString
void GetQueryParamValue (const CDaoParameterInfo &Info, CString &strValue)
{
	COleVariant vars (Info.m_varValue);
	char Empty [] = "";
	char *pVal = NULL;
	if ((VT_EMPTY == vars.vt) || (VT_NULL == vars.vt) || (VT_UNKNOWN == vars.vt))
		pVal = Empty;
	else
	{
		if (VT_BSTR == vars.vt)
			pVal = (char *) vars.pbVal;
		else
		{
			vars.ChangeType (VT_BSTR);		// in Zeichenkette umwandeln
			pVal = AnsiStringNew ((LPCWSTR) vars.pbVal);
		}				
	}	

	strValue = pVal;
}

//	schreibe Parameterwert (CString) in Parameterinfo
BOOL WriteQueryParamValue (CDaoParameterInfo &Info, const CString &strValue)
{
	COleVariant vars ((const char *)strValue, VT_BSTR), vard;
	switch (Info.m_nType)
	{
		case dbBoolean:
			vard.ChangeType (VT_BOOL, vars);
		break;
		case dbByte:
			vard.ChangeType (VT_I2, vars);
		break;
		case dbInteger:
			vard.ChangeType (VT_I4, vars);
		break;
		case dbLong:
			vard.ChangeType (VT_I4, vars);
		break;
		case dbCurrency:
			vard.ChangeType (VT_CY, vars);
		break;
		case dbSingle:
			vard.ChangeType (VT_R4, vars);
		break;
		case dbDouble:
			vard.ChangeType (VT_R8, vars);
		break;
		case dbDate:
			vard.ChangeType (VT_DATE, vars);
		break;
		case dbMemo:		// Typ bleibt
		case dbText:
			vard = COleVariant ((const char *)strValue, VT_BSTRT);
		break;
		default:
		{
			((CGakApp *) AfxGetApp ()) -> OutputMessage (IDS_UNKNOWN_QUERY_PARAM);
			return FALSE;
		}
	}
		
	Info.m_varValue = vard;
	return TRUE;
}

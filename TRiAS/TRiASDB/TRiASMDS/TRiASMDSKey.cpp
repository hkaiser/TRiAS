#include "stdafx.h"
#include "TRiASMDSImpl.h"
#include "TRiASMDSKey.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
//
static const TCHAR cbOKS[] = 
	TEXT("\\[\\([[:xdigit:]]+\\)\\]" "\\|"							// [OKS]
		 "\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]].*\\)" "\\|"	// OKS:irgend was
		 "\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)"						// [OKS]irgend was
		);

static const TCHAR* pOKS[] = {
	_T( "\\([[:xdigit:]]+\\)" ),									// OKS
	_T( "\\[\\([[:xdigit:]]+\\)\\]" ),								// [OKS]
	_T( "\\(\\([[:xdigit:]]+\\)[[:punct:][:blank:]].*\\)" ),		// OKS:irgend was
	_T( "\\[\\([[:xdigit:]]+\\)\\]\\(.*\\)" ),						// [OKS]irgend was
};

CTRiASMDSKey::CTRiASMDSKey() 
{
	pattern(cbOKS);
	m_rexOKS_0.pattern(pOKS[0]);
	m_rexOKS_1.pattern(pOKS[1]);
	m_rexOKS_2.pattern(pOKS[2]);
	m_rexOKS_3.pattern(pOKS[3]);
}

STDMETHODIMP CTRiASMDSKey::SplitOKS(
		/*[in]*/ BSTR strPossibleOKS,
		/*[in,optional,defaultvalue(NULL)]*/ BSTR* pbstrAppendix,
		/*[out,retval]*/ BSTR* pbstrOKS
	)
{
	CHECKINPOINTER(pbstrOKS);
	USES_CONVERSION;
	COM_TRY {
	// Eingabezeichenkette analysieren
	os_string strToTest (OLE2A(strPossibleOKS));
	int iMatched = match(strToTest);

		if (iMatched <= 0) {
			MAKE_ERROR(KEY_E_NOOBJECTKEY);
		}

	String strOKS(L"");
	String strApp(L"");

		if (group(4).size() > 0) {
		// dritter Fall gefunden ('[hexdigits]...')
			_ASSERTE(group(5).size() > 0);
			strOKS = os_string(group(4)).c_str();
			strApp = os_string(group(5)).c_str();
		} 
		else if (group(1).size() > 0) {
		// ersten Fall gefunden ('[hexdigits]')
			strOKS = os_string(group(1)).c_str();
		} 
		else if (group(3).size() > 0) {
		// zweiten Fall gefunden ('hexdigits:...')
			strOKS = os_string(group(3)).c_str();
		} 
		else {
			MAKE_ERROR(KEY_E_NOOBJECTKEY);
		}
		if (0 == strOKS.Length()) {
			MAKE_ERROR(KEY_E_NOOBJECTKEY);
		}

	// Resultat liefern, wenn gewünscht
		if (NULL != pbstrAppendix) 
			*pbstrAppendix = strApp.Detach();

		*pbstrOKS = strOKS.UCase().Detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASMDSKey::FormatOKS(
		/*[in]*/ VARIANT vOKS,
		/*[in,optional,defaultvalue(NULL)]*/ BSTR strShortname,
		/*[out,retval]*/ BSTR* pStrFormattedOKS
	)
{
	CHECKINPOINTER(pStrFormattedOKS);
	USES_CONVERSION;
	COM_TRY {
	CComBSTR strOKS;

		if (V_ISINTEGER(&vOKS)) {
		CComVariant	v(vOKS);
		TCHAR _buf[64];
		
			WIN_ERROR_NOTSUCCESS(v.ChangeType(VT_I4), MDS_E_COERCE);
			wsprintf (_buf, _T("%lx"), V_I4(&v));
			strOKS = _buf;
		} 
		else {
			ERROR_EXPR_FALSE(V_ISBSTR(&vOKS), E_INVALIDARG);
		
		os_string strToTest (OLE2A(V_BSTR(&vOKS)));
			
			if (m_rexOKS_0.match(strToTest) > 0)
				strOKS = os_string(m_rexOKS_0.group(1)).c_str();
			else if( m_rexOKS_1.match(strToTest)) 
				strOKS = os_string(m_rexOKS_1.group(1)).c_str();
			else {
				MAKE_ERROR( KEY_E_NOHEXDIGITS );
			}
		}
		ERROR_EXPR_TRUE(0 == strOKS.Length(), E_INVALIDARG);

	CComBSTR strNewOKS(L"[");

		strNewOKS.AppendBSTR(strOKS);
		strNewOKS.Append(L"]");

		if (strShortname && *strShortname) 
			strNewOKS.Append(strShortname);

		*pStrFormattedOKS = strNewOKS.Detach();

	} COM_CATCH;
	return S_OK;
}

// TSCryptSvr.h : Deklaration von CTSCryptSvr

#ifndef __TSCRYPTSVR_H_
#define __TSCRYPTSVR_H_

#include "resource.h"       // Hauptsymbole

#define TSERRBASE 0xA0000000

/////////////////////////////////////////////////////////////////////////////
// CTSCryptSvr
class ATL_NO_VTABLE CTSCryptSvr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTSCryptSvr, &CLSID_TSCryptSvr>,
	public IDispatchImpl<ITSCryptSvr, &IID_ITSCryptSvr, &LIBID_TSCRYPTLib>
{
public:
	CTSCryptSvr();

DECLARE_REGISTRY_RESOURCEID(IDR_TSCRYPTSVR)

BEGIN_COM_MAP(CTSCryptSvr)
	COM_INTERFACE_ENTRY(ITSCryptSvr)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ITSCryptSvr
public:
	STDMETHOD(GetOwnerEmailAddress)(/*[in]*/long hCertificate, /*[out]*/BSTR* strOwnerEmailAddress, /*[out,retval]*/long* pResult);
	STDMETHOD(AddUserBySignerInfoFile)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(LoadSignerInfo)(/*[in]*/long hUser, /*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(SaveSignerInfo)(/*[in]*/long hUser, /*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(ValidateSignature)(/*[in]*/long hUser, /*[out,retval]*/long* pResult);
	STDMETHOD(GetUserCertificate)(/*[in]*/long hUser, /*[out]*/long* hCertificate, /*[out,retval]*/long* pResult);
	STDMETHOD(GetUser)(/*[in]*/long index, /*[out]*/long* hUser, /*[out,retval]*/long* pResult);
	STDMETHOD(GetSignerCount)(/*[out]*/long* lSignerCount, /*[out,retval]*/long* pResult);
	STDMETHOD(GetUserCount)(/*[out]*/long* lUserCount, /*[out,retval]*/long* pResult);
	STDMETHOD(AddUser)(/*[in]*/long pCertificate, /*[out,retval]*/long* pResult);
	STDMETHOD(SetEncryptionType)(/*[in]*/long lType, /*[out,retval]*/long* pResult);
	STDMETHOD(SaveContent)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(SaveDocument)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(IsOwnCertificate)(/*[in]*/long hCerificate, /*[out,retval]*/long* pResult);
	STDMETHOD(GetNotBefore)(/*[in]*/long pCertificate, /*[out]*/BSTR* strNotBefore, /*[out,retval]*/long* pResult);
	STDMETHOD(GetNotAfter)(/*[in]*/long pCertificate, /*[out]*/BSTR* strNotAfter, /*[out,retval]*/long* pResult);
	STDMETHOD(SetLabel)(/*[in]*/long pCertificate, /*[in]*/BSTR strLabel, /*[out,retval]*/long* pResult);
	STDMETHOD(GetLabel)(/*[in]*/long pCertificate, /*[out]*/BSTR* strLabel, /*[out,retval]*/long* pResult);
	STDMETHOD(ExportCertificate)(/*[in]*/BSTR strFileName, /*[in]*/long pCertificate, /*[out,retval]*/long* pResult);
	STDMETHOD(ImportCertificates)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetIssuerCommonName)(/*[in]*/long pCertificate, /*[out]*/BSTR* strIssuerCommonName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetErrorDescription)(/*[in]*/long lErrorCode, /*[out]*/BSTR* strErrorDescription, /*[out,retval]*/long* pResult);
	STDMETHOD(GetOwnerCommonName)(/*[in]*/long pCertificate, /*[out]*/BSTR* strOwnerCommonName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetNextCertificate)(/*[out]*/long* pCertificate, /*[out,retval]*/long* pResult);
	STDMETHOD(GetFirstCertificate)(/*[out]*/long* pCertificate, /*[out,retval]*/long* pResult);
	STDMETHOD(LoadContent)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(LoadDocument)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetDocument)(/*[out]*/VARIANT* pvDocument, /*[out,retval]*/long* pResult);
	STDMETHOD(GetContent)(/*[out]*/VARIANT* pvContent, /*[out,retval]*/long* pResult);
	STDMETHOD(SetSignature)(/*[in]*/ VARIANT* pvSignature, /*[out,retval]*/ long* pResult);
	STDMETHOD(GetSignature)(/*[out]*/ VARIANT* pvSignature, /*[out,retval]*/ long* pResult);
	STDMETHOD(Sign_CS)(/*[out,retval]*/long* pResult);
	STDMETHOD(GetSCardIssuerCommonName_CS)(/*[out]*/BSTR* strIssuerCommonName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetSCardOwnerCommonName_CS)(/*[out]*/BSTR* strOwnerCommonName, /*[out,retval]*/long* pResult);
	STDMETHOD(GetSCardLabel_CS)(/*[out]*/BSTR* strLabel, /*[out,retval]*/long* pResult);
	STDMETHOD(Close)(/*[out,retval]*/long* pResult);
	STDMETHOD(Open)(/*[out,retval]*/long* pResult);
	STDMETHOD(SetPassword)(/*[in]*/BSTR strPassword, /*[out,retval]*/long* pResult);
	STDMETHOD(SetDatabase)(/*[in]*/BSTR strFileName, /*[out,retval]*/long* pResult);
//	STDMETHOD(Initialize_CS)(/*[out,retval]*/long* pResult);
	STDMETHOD(EncryptFile)(/*[in]*/ long hWnd, /*[in]*/ BSTR strFileName, /*[out]*/ BSTR* strCryptedFileName, /*[out,retval]*/ long* pResult);
	STDMETHOD(VerifyFile)(/*[in]*/ long hWnd, /*[in]*/ BSTR strFilName, /*[in]*/ BSTR strSigFileName, /*[out,retval]*/ long *pResult);
	STDMETHOD(get_AlgID_Sign)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_AlgID_Sign)(/*[in]*/ long newVal);
	STDMETHOD(Logoff)(/*[in]*/ long hWnd, /*[out,retval]*/long* pResult);
	STDMETHOD(Logon)(/*[in]*/ long hWnd, /*[out,retval]*/ long* pResult);
	STDMETHOD(SignFile)(/*[in]*/ long hWnd, /*[in]*/ BSTR strFileName, /*[out]*/ BSTR* strSigFileName, /*[out,retval]*/ long* pResult);
	STDMETHOD(GetPassword)(/*[in]*/ long hWnd, /*[out,retval]*/ long* pResult);
};

#endif //__TSCRYPTSVR_H_

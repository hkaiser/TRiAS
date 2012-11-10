#if !defined(_WIZARD_STDIMPL_H_8D00FD20_F032_11d2_9942_00AA002A873B)
#define _WIZARD_STDIMPL_H_8D00FD20_F032_11d2_9942_00AA002A873B

DefineSmartInterface(Wizard)
DefineSmartInterface(WizardCallback)
DefineSmartInterface(WizardSupportSite)

#include "com/ErrorMacros2.h"
#include "Pragmas.h"

#pragma HDR_ON()

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

////////////////////////////////////////////////////////////////////////////////
// @doc TEMPLATE WIZARD CWizardSupportIml

struct WIZARD_PPGDESCR_ENTRY {
	const CLSID*	pclsidPropPage;
	UINT			nIDDocStr;
	UINT			nIDHelpFile;
	DWORD			dwHelpContext;
};

#define BEGIN_WIZARD_PPGDESCR_MAP(theClass) \
	static WIZARD_PPGDESCR_ENTRY* GetPpgDescrMap() { \
		static WIZARD_PPGDESCR_ENTRY pPpgDescrMap[] = {

#define WIZARD_PPGDESCR_ENTRY(clsid,nIDDocStr,nIDHelpFile,dwHelpContext) \
			{&clsid,nIDDocStr,nIDHelpFile,dwHelpContext},

#define END_WIZARD_PPGDESCR_MAP() \
			{ NULL, 0, 0, 0 } \
		}; \
		return pPpgDescrMap; \
	}

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CWizardSupportImpl
	: public IDispatchImpl<IWizardSupportSite, &IID_IWizardSupportSite>
	, public CErrSupport<T, &IID_IWizardSupportSite>
{
protected:
	class CSALock {			// simple Class to safe lock a SAFEARRY
		SAFEARRAY	*m_pArray;
		bool		m_bDestroy;
	public:
		CSALock(SAFEARRAY *pArray, bool bDestroy=true) : m_pArray(pArray) , m_bDestroy(bDestroy) {::SafeArrayLock(m_pArray);}
		~CSALock() { ::SafeArrayUnlock(m_pArray); if(m_bDestroy) ::SafeArrayDestroy(m_pArray); }
	};
	IDispatch	*m_pRefOfWizard;
	typedef	CWizardSupportImpl<T,pCLSID> CWizardSupportImpl_t;
public:
	BEGIN_COM_MAP(CWizardSupportImpl)
		COM_INTERFACE_ENTRY(IWizardSupportSite)
	END_COM_MAP()
// IWizardSupport
	STDMETHOD(putref_Wizard)(/*[in]*/ IDispatch * pWizard) {
		m_pRefOfWizard = pWizard;
		return S_OK;
	}
	STDMETHOD(DescribePageMore)(/*[in]*/ BSTR strPpgCLSID, /*[out,retval]*/ SAFEARRAY** pPageInfo ) {
		COM_TRY {
			CLSID	clsid;
			::CLSIDFromString( strPpgCLSID, &clsid );
			WIZARD_PPGDESCR_ENTRY	*lpEntries = T::GetPpgDescrMap();
			long	nEntries = 0;
			for( ; lpEntries->pclsidPropPage; ++lpEntries ) {
				if( InlineIsEqualGUID( *lpEntries->pclsidPropPage, clsid ) )
					break;
			}
			if( !lpEntries->pclsidPropPage )
				return E_FAIL;		// no extended Propertypage Description found
			SAFEARRAYBOUND	bnds[1];
			bnds[0].lLbound = 0;
			bnds[0].cElements = 4;
			long	idx[1];
			SAFEARRAY	*pArray = ::SafeArrayCreate( VT_VARIANT, 1, bnds );
			CSALock( pArray, false );
			CComBSTR	strDocString;
			CComBSTR	strHelpFile;
			VARIANT		vTitle; ::VariantInit(&vTitle);
			VARIANT		vDocString; ::VariantInit(&vDocString);
			VARIANT		vHelpFile; ::VariantInit(&vHelpFile);
			CComVariant	vHelpContext; ::VariantInit(&vHelpContext);

			strDocString.LoadString(lpEntries->nIDDocStr);
			strHelpFile.LoadString(lpEntries->nIDHelpFile);
			ERROR_EXPR_FALSE( strDocString && strDocString.Length() && strHelpFile && strHelpFile.Length(), E_FAIL );
			CComVariant(strHelpFile).Detach(&vHelpFile);
			CComVariant(strDocString).Detach(&vDocString);
			CComVariant((long)lpEntries->dwHelpContext).Detach(&vHelpContext);
			idx[0] = 0;
			ERROR_FAILED_HRESULT( ::SafeArrayPutElement( pArray, &idx[0], &vTitle ), E_FAIL );
			++idx[0];
			ERROR_FAILED_HRESULT( ::SafeArrayPutElement( pArray, &idx[0], &vDocString ), E_FAIL );
			++idx[0];
			ERROR_FAILED_HRESULT( ::SafeArrayPutElement( pArray, &idx[0], &vHelpFile ), E_FAIL );
			++idx[0];
			ERROR_FAILED_HRESULT( ::SafeArrayPutElement( pArray, &idx[0], &vHelpContext ), E_FAIL );
			*pPageInfo = pArray;
		} COM_CATCH;
		return S_OK;
	}
	STDMETHOD(SpecifyNextPage)(/*[in]*/ BSTR strCLSIDOfCurrPage, /*[out]*/ BSTR* pbstrCLSIDOfNextPage ) {
		return E_NOTIMPL;
	}
	STDMETHOD(SpecifyNextObject)(/*[in]*/ BSTR strCLSIDOfCurrObject, /*[in]*/ BSTR strCLSIDOfCurrPage, /*[out]*/ BSTR* pbstrCLSIDOfNextObject ) {
		return E_NOTIMPL;
	}
};

////////////////////////////////////////////////////////////////////////////////
// Standardimplementierung für ein Wizard-Objekt

template<class T, const IID *pCLSID, const IID *pIID, class ThreadModel>
class ATL_NO_VTABLE CWizardObjectImpl
	: public CComObjectRootEx<ThreadModel>
	, public CComCoClass<T, pCLSID>
	, public ISpecifyPropertyPagesImpl<T>
	, public IConnectionPointContainerImpl<T>
	, public CErrSupport<T, pIID>
	, public CWizardSupportImpl<T, pCLSID>
{
public:
	typedef CWizardObjectImpl<T, pCLSID, pIID, ThreadModel> CWizardObjectImpl_t;
	typedef CErrSupport<T, pIID> errsupport_t;
	BEGIN_COM_MAP(CWizardObjectImpl)
		COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_CHAIN(errsupport_t)
		COM_INTERFACE_ENTRY_CHAIN(CWizardSupportImpl_t)
	END_COM_MAP()
};

#undef THIS_FILE

#pragma HDR_OFF()

#endif // !_WIZARD_STDIMPL_H_8D00FD20_F032_11d2_9942_00AA002A873B

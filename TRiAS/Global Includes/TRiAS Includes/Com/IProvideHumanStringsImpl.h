#if !defined(_HUMANSTRINGS_H_3484DF41_2F3D_11d3_998F_0060085FC1CE)
#define _HUMANSTRINGS_H_3484DF41_2F3D_11d3_998F_0060085FC1CE

#include "Pragmas.h"
#pragma HDR_ON()

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

#import "tlb/UICtrl.tlb" \
	raw_interfaces_only	\
	no_implementation	\
	no_namespace		\
	named_guids

struct HNT_STRINGDESCRIPTOR {
	enum tagHUMANSTRINGTYPE	hnType;
	UINT			hnResID;
};

#define BEGIN_HNTSTRING_MAP(theClass) \
	static HNT_STRINGDESCRIPTOR* GetHNTDescriptorMap() { \
		static HNT_STRINGDESCRIPTOR hntDescriptors[] = {

#define	HNTSTRING_ENTRY(hnt,resID) \
	{hnt, resID},

#define END_HNTSTRING_MAP() \
	{ HNT_UNDEFINED, 0 } \
		}; \
		return hntDescriptors; \
	}

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CProvideHumanStringsImpl
	: public IDispatchImpl<IProvideHumanStrings, &IID_IProvideHumanStrings>
{
public:
	typedef CProvideHumanStringsImpl<T,pCLSID> CProvideHumanStringsImpl_t;

	BEGIN_COM_MAP(CProvideHumanStringsImpl)
		COM_INTERFACE_ENTRY(IProvideHumanStrings)
	END_COM_MAP()
	
	STDMETHOD(get_String)( enum tagHUMANSTRINGTYPE type, ULONG locale, BSTR* pbstrName ) {
		if( NULL == pbstrName )
			return E_POINTER;
		const HNT_STRINGDESCRIPTOR* pDescr = T::GetHNTDescriptorMap();
		for( ; HNT_UNDEFINED != pDescr->hnType; ++pDescr ) {
			if( type != pDescr->hnType )
				continue;
			CComBSTR	strName;
			bool bRes = strName.LoadString( pDescr->hnResID );
			_ASSERTE( true == bRes );
			if( false == bRes )
				return E_FAIL;
			*pbstrName = strName.Detach( );
			return S_OK;
		}
		return E_FAIL;
	}
};


#undef THIS_FILE
#pragma HDR_OFF()

#endif //_HUMANSTRINGS_H_3484DF41_2F3D_11d3_998F_0060085FC1CE

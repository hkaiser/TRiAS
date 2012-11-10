#if !defined(__GeoMediaObjects__4E096670_CE15_11d1_8F28_0060085FC1CE)
#define __GeoMediaObjects__4E096670_CE15_11d1_8F28_0060085FC1CE

#include <comdef.h>

struct __declspec(uuid("3bd80880-7126-11cf-8357-08003601e5f9"))
_IGCollection : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        short * Count ) = 0;
    virtual HRESULT __stdcall _NewEnum (
        IUnknown * * Enum ) = 0;
};


struct __declspec(uuid("05f57eb0-720b-11cf-8357-08003601e5f9"))
_IGDynaCollection : _IGCollection
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall Append (
        IDispatch * Object ) = 0;
    virtual HRESULT __stdcall Delete (
        BSTR Name ) = 0;
};

struct __declspec(uuid("a374538b-e404-11cf-99af-08003601e42c"))
_DGMStyleBase : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_StyleClass (
        short * pStyleClass ) = 0;
    virtual HRESULT __stdcall Copy (
        IDispatch * * pNewStyle ) = 0;
};

//#include "GMObjects/GMConstants.h"

#if !defined(__BUILD_HEADERS__F1946A90_CE1B_11d1_8F28_0060085FC1CE)
	#if defined(_DEBUG)
			#pragma comment( lib, "GMObjectsD.lib" )
	#elif defined(_RDEBUG)
			#pragma comment( lib, "GMObjectsR.lib" )
	#elif defined(NDEBUG)
			#pragma comment( lib, "GMObjects.lib" )
	#endif
	#include "GMObjects/PClient.tlh"
	#include "GMObjects/PCSS.tlh"
	#include "GMObjects/PView.tlh"
	#include "GMObjects/Mapview.tlh"
	#include "GMObjects/PBasic.tlh"
	#include "GMObjects/PService.tlh"
	#include "GMObjects/GeoMedia.tlh"
	#include "GMObjects/PDBPipe.tlh"
	#include "GMObjects/DefCoordSystem.tlh"
#endif //__BUILD_HEADERS__F1946A90_CE1B_11d1_8F28_0060085FC1CE

#endif // __GeoMediaObjects__4E096670_CE15_11d1_8F28_0060085FC1CE

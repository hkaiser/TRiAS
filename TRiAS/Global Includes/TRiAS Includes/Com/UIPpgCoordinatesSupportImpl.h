#if !defined(_WIZARD_COORDPPG_IMPL_H_8D00FD22_F032_11d2_9942_00AA002A873B)
#define _WIZARD_COORDPPG_IMPL_H_8D00FD22_F032_11d2_9942_00AA002A873B

#import "tlb/UICtrl.tlb" \
	raw_interfaces_only	\
	no_implementation	\
	no_namespace		\
	named_guids

DefineSmartInterface(Dispatch)

#include "com/ErrorMacros2.h"
#include "Pragmas.h"
#pragma HDR_ON()

#ifdef _DEBUG
#undef THIS_FILE
#define	THIS_FILE	(__FILE__)
#endif

template<class T, const IID *pCLSID>
class ATL_NO_VTABLE CUIPpgCoordinatesSupportImpl
	: public IDispatchImpl<IUIPpgCoordinatesSupport, &IID_IUIPpgCoordinatesSupport>
	, public CErrSupport<T, &IID_IUIPpgCoordinatesSupport>
{
	long		m_lCoordinatesPerRow;
protected:
	struct CSAWrap {
		SAFEARRAYBOUND	m_b[1];
		SAFEARRAY		*m_a;
		CSAWrap(VARTYPE vt, UINT nElems) : m_a(NULL) { 
			m_b[0].lLbound = 0;
			m_b[0].cElements = nElems;
			m_a = ::SafeArrayCreate( vt, 1, m_b );
		};
		~CSAWrap() {
			::SafeArrayDestroy(m_a);
		}
		HRESULT	CopyIn( SAFEARRAY* pSrc ) {
			long	lBound;
			long	uBound;
			RETURN_FAILED_HRESULT( ::SafeArrayGetLBound( pSrc, 1, &lBound ) );
			RETURN_FAILED_HRESULT( ::SafeArrayGetUBound( pSrc, 1, &uBound ) );
			m_b[0].cElements = uBound - lBound;
			RETURN_FAILED_HRESULT( ::SafeArrayRedim( m_a, m_b ) );
			RETURN_FAILED_HRESULT( ::SafeArrayCopy( m_a, &pSrc ) );
			return S_OK;
		}
		HRESULT CopyOut( SAFEARRAY** ppSA ) {
			RETURN_FAILED_HRESULT( ::SafeArrayCopy( *ppSA, &m_a ) );
			return S_OK;
		}
	};
	CSAWrap		m_arrCoordinateNames;
	CSAWrap		m_arrCoordinateNamesEditable;
	CSAWrap		m_arrColumnHeaders0;
	CSAWrap		m_arrColumnHeaders1;
	CSAWrap		m_arrCoordinates0;
	CSAWrap		m_arrCoordinates1;
	CSAWrap		m_arrMaskProviders0;
	CSAWrap		m_arrMaskProviders1;
	CSAWrap		m_arrCoordEditable0;
	CSAWrap		m_arrCoordEditable1;

	typedef CUIPpgCoordinatesSupportImpl<T,pCLSID> CUIPpgCoordinatesSupportImpl_t;
public:
	CUIPpgCoordinatesSupportImpl()
		: m_lCoordinatesPerRow(1)
		, m_arrCoordinateNames( VT_BSTR, 1 )
		, m_arrCoordinateNamesEditable( VT_BOOL, 1 )
		, m_arrColumnHeaders0( VT_BSTR, 3 )
		, m_arrColumnHeaders1( VT_BSTR, 3 )
		, m_arrCoordinates0( VT_R8, 1 )
		, m_arrCoordinates1( VT_R8, 1 )
		, m_arrMaskProviders0( VT_DISPATCH, 1 )
		, m_arrMaskProviders1( VT_DISPATCH, 1 )
		, m_arrCoordEditable0( VT_BOOL, 1 )
		, m_arrCoordEditable1( VT_BOOL, 1 )
	{}

	BEGIN_COM_MAP(CUIPpgCoordinatesSupportImpl)
		COM_INTERFACE_ENTRY(IUIPpgCoordinatesSupport)
	END_COM_MAP()

	STDMETHOD(get_CoordinatesPerRow)( long* pVal) {
		CHECKOUTPOINTER(pVal);
		*pVal = m_lCoordinatesPerRow;
		return S_OK;
	}
	STDMETHOD(put_CoordinatesPerRow)( long val) {
		if( val > 2 || val < 0 )
			return E_UNEXPECTED;
		m_lCoordinatesPerRow = val;
		return S_OK;
	}
    STDMETHOD(get_CoordinateNames)( SAFEARRAY * * pVal ) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			return m_arrCoordinateNames.CopyOut( pVal );
		} COM_CATCH;
	}
    STDMETHOD(put_CoordinateNames)( SAFEARRAY * pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			return m_arrCoordinateNames.CopyIn( pVal );
		} COM_CATCH;
		return S_OK;
	}
    STDMETHOD(get_CoordinateNamesEditable)( SAFEARRAY** pVal ) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			return m_arrCoordinateNamesEditable.CopyOut( pVal );
		} COM_CATCH;
	}
    STDMETHOD(put_CoordinateNamesEditable)( SAFEARRAY* pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			return m_arrCoordinateNamesEditable.CopyIn( pVal );
		} COM_CATCH;
	}

    STDMETHOD(get_Coordinates)(long lColumn, SAFEARRAY** pVal ) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrCoordinates0.CopyOut(pVal);
			} else if( 1 == lColumn ) {
				return m_arrCoordinates1.CopyOut(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(put_Coordinates)(long lColumn, SAFEARRAY * pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrCoordinates0.CopyIn(pVal);
			} else if( 1 == lColumn ) {
				return m_arrCoordinates1.CopyIn(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(get_ColumnHeaders)( long lColumn, SAFEARRAY * * pVal ) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrColumnHeaders0.CopyOut(pVal);
			} else if( 1 == lColumn ) {
				return m_arrColumnHeaders1.CopyOut(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(put_ColumnHeaders)( long lColumn, SAFEARRAY * pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrColumnHeaders0.CopyIn(pVal);
			} else if( 1 == lColumn ) {
				return m_arrColumnHeaders1.CopyIn(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(get_MaskProviders)( long lColumn, SAFEARRAY** pVal ) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrMaskProviders0.CopyOut(pVal);
			} else if( 1 == lColumn ) {
				return m_arrMaskProviders1.CopyOut(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(put_MaskProviders)(long lColumn, SAFEARRAY* pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrMaskProviders0.CopyIn(pVal);
			} else if( 1 == lColumn ) {
				return m_arrMaskProviders1.CopyIn(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(get_CoordinatesEditable)( long lColumn, SAFEARRAY** pVal) {
		CHECKOUTPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrCoordEditable0.CopyOut(pVal);
			} else if( 1 == lColumn ) {
				return m_arrCoordEditable1.CopyOut(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
    STDMETHOD(put_CoordinatesEditable)( long lColumn, SAFEARRAY* pVal ) {
		CHECKINPOINTER(pVal);
		COM_TRY {
			if( 0 == lColumn ) {
				return m_arrCoordEditable0.CopyIn(pVal);
			} else if( 1 == lColumn ) {
				return m_arrCoordEditable1.CopyIn(pVal);
			} else {
				return E_UNEXPECTED;
			}
		} COM_CATCH;
	}
};

#undef THIS_FILE
#pragma HDR_OFF()

#endif // !_WIZARD_COORDPPG_IMPL_H_8D00FD22_F032_11d2_9942_00AA002A873B

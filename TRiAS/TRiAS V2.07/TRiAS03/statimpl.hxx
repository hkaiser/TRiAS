// InterfaceImplementation IProgessIndicator ----------------------------------
// File: STATIMPL.HXX

#if !defined(_STATIMPL_HXX)
#define _STATIMPL_HXX

#include <istatus.h>		// Interfacedeklarationen
#include "TRiASHelper.h"

class CProgressIndicator : 
	public IProgressIndicator,
	public CComDualImpl<IProgressIndicator2, &IID_IProgressIndicator2, &LIBID_TRiASHelperLib,
		TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_IProgressIndicator2>,
	public CComObjectRoot,
	public CComCoClass<CProgressIndicator, &CLSID_ProgressIndicator>
{
private:
	class Window *m_pParent;
	class CStatusDlg *m_pDlg;
	HWND m_hWnd;
	bool m_fInitialized;

public:
		CProgressIndicator (void);
		~CProgressIndicator (void);

	BEGIN_COM_MAP(CProgressIndicator)
		COM_INTERFACE_ENTRY(IProgressIndicator2)
		COM_INTERFACE_ENTRY(IProgressIndicator)
		COM_INTERFACE_ENTRY2(IDispatch, IProgressIndicator2)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CProgressIndicator)
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROGRESSINDICATOR_RGS)

// *** IProgressIndicator methods ***
	STDMETHOD_(HWND, InitNew)(THIS_ HWND hWnd, DWORD dwReserved);
	STDMETHOD(Restart)(THIS_ ULONG uiMinPos, ULONG ulMaxPos, DWORD dwFlags);
	STDMETHOD(ChangeText)(THIS_ DWORD dwWhichText, LPCSTR pcNewText);
	STDMETHOD(RetrieveText)(THIS_ DWORD dwWichText, LPSTR cbText, ULONG uiLen);

	STDMETHOD_(int, SetPosition)(THIS_ ULONG uiNewPos);
	STDMETHOD_(BOOL, WasCanceled)(THIS);

// *** IProgressIndicator2 methods ***
// #if _MSC_VER >= 1100
	STDMETHOD(InitNew)(THIS_ LONG hWndParent, DWORD dwReserved, LONG *pHWND);
// #else	
//	STDMETHOD(InitNew)(THIS_ HWND hWndParent, DWORD dwReserved, HWND *pHWND);
// #endif // _MSC_VER >= 1100
	STDMETHOD(Restart)(THIS_ ULONG uiMinPos, ULONG ulMaxPos, PIFLAGS rgFlags);
    STDMETHOD(ChangeText)(THIS_ PIFLAGS dwWhichText, BSTR bstrNewText);
    STDMETHOD(RetrieveText)(THIS_ PIFLAGS dwWhichText, BSTR *pbstrOutText);
	STDMETHOD(SetPosition)(THIS_ ULONG ulNewPos, INT *piPercent);
    STDMETHOD(IncrementPosition)(THIS_ INT *piPercent);
    STDMETHOD(IsCanceled)(THIS);

	STDMETHOD(get_Flags)(THIS_ PIFLAGS *prgFlags);
	STDMETHOD(put_Flags)(THIS_ PIFLAGS rgFlags);
	STDMETHOD(RetrieveRange)(THIS_ ULONG *pulMinPos, ULONG *pulMaxPos);
};

#endif // _STATIMPL_HXX

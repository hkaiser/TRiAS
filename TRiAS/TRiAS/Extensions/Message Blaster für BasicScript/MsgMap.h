// Datenstruktur, die eine Konkrete message einer Basic-Routibne zuordnet
// File: MSGMAP.H

#if !defined(_MSGMAP_H)
#define _MSGMAP_H

#include "resource.h"

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(ConnectionPointContainer);

///////////////////////////////////////////////////////////////////////////////
// eigentliche MessageMap
typedef map<UINT, os_string, less<UINT> > CMsgMap;

class CMessageMap :
	public ITRiASSysNotificationSink,
//	public ISupportErrorInfo,
	public CComDualImpl<IMessageMap, &IID_IMessageMap, &LIBID_MsgBlastLib>,
	public CComObjectRoot,
	public CComCoClass<CMessageMap, &CLSID_MessageMap>
{
public:
		CMessageMap() { m_fEnabled = false; }
		~CMessageMap() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CMessageMap)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
		COM_INTERFACE_ENTRY(IMessageMap)
		COM_INTERFACE_ENTRY2(IDispatch, IMessageMap)
	END_COM_MAP()
	
	DECLARE_NOT_AGGREGATABLE(CMessageMap)
	DECLARE_REGISTRY_RESOURCEID(IDR_MESSAGEMAP_RGS)

// *** ITRiASSysNotificationSink specific functions ***
	STDMETHOD(WindowsMessage) (THIS_ long hWnd, long uiMsg, long wParam, long lParam);

// *** IMessageMap methods
public:
	STDMETHOD(get_ToCall)(/*[in]*/ LONG Msg, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ToCall)(/*[in]*/ LONG Msg, /*[in]*/ BSTR newVal);
	STDMETHOD(get_HasMsg)(/*[in]*/ LONG Msg, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Enabled)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Enabled)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(AddMessage)(/*[in]*/ LONG Msg, /*[in]*/ BSTR ToCall, /*[out, retval]*/VARIANT_BOOL *pVal);
	STDMETHOD(RemoveMessage)(/*[in]*/ LONG Msg, /*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(RemoveAll)();

protected:
	HRESULT DisConnectFromServer (void);
	HRESULT SetXtsnSite (ITriasXtensionSite *pSite);

	HRESULT BlastMessage (os_string strToCall, WPARAM wParam, LPARAM lParam);

private:
	bool m_fEnabled;
	
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookieSys;

	WExtendBScript m_Sink;		// hier soll's hin

	CMsgMap m_Msg;
};

#endif // _MSGMAP_H

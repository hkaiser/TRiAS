#ifndef _SCRINFO_H
#define _SCRINFO_H

class CStreamInfo :
	public CComObjectRoot,
	public CComCoClass<CStreamInfo,&CLSID_StreamInfo>,
	public IPersistStream,
	public IStreamInfo
{
protected:
	ULONG       m_cRef;      // Interface reference count
	LPUNKNOWN 	m_pIUnk;
	UINT		m_uiManID;
private:
	bool m_fIsDirty;
	map<os_string, DWORD, less<os_string> > map_StreamInfo;
	typedef map<os_string, DWORD, less<os_string> > StreamMap;

	int StreamMapCount(void);

public:
	BEGIN_COM_MAP(CStreamInfo)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IStreamInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CStreamInfo)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_STREAMINFO_REG)

	   	CStreamInfo(void);
   		virtual ~CStreamInfo(void);

	static HRESULT CreateInstance(IStreamInfo **pp)
		{ return _CreatorClass::CreateInstance(NULL, IID_IStreamInfo, (LPVOID *)pp); }

	// IPersistStream
	STDMETHOD(GetClassID)(LPCLSID);
    STDMETHOD(IsDirty)(void);
    STDMETHOD(Load)(LPSTREAM);
    STDMETHOD(Save)(LPSTREAM, BOOL);
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR *);

	//IStreamInfo
    STDMETHOD(Get)(BSTR bstr, DWORD*);
    STDMETHOD(Set)(BSTR bstr, DWORD);
    STDMETHOD(Rename)(BSTR bstr, BSTR bstrNew);
	STDMETHOD_(UINT,Count)(void);
	STDMETHOD_(UINT,GetManID)(void); 
	STDMETHOD_(void,SetManID)(UINT ui);
};

#endif // _SCRINFO_H


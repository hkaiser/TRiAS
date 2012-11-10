#ifndef _ENUMEX_H
#define _ENUMEX_H

class CEnumObjects : 
	public IEnumUnknownExtended
{
public:
	CEnumObjects ();
	virtual ~CEnumObjects ();

protected:
	ULONG m_cRef;
	LONG m_lDelayDel;

	list<WUnknown> m_listUnknowns;
	typedef list<WUnknown> TYPEUnknownList;

	TYPEUnknownList::iterator m_itcur;

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (void);
	STDMETHOD_(ULONG, Release) (void);

// *** IEnumUnknown methods
	STDMETHOD(Next)(ULONG celt, IUnknown ** rgelt, ULONG * pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(IEnumUnknown ** ppenum);

// *** IEnumUnknownExtended methods
	STDMETHOD(Delete)(BSTR bstr);
	STDMETHOD(Add)(LPUNKNOWN lpUnk);
	STDMETHOD(Find)(BSTR bstr, LPUNKNOWN * lplpUnk);
	STDMETHOD_(UINT, Count) (void);

	HRESULT DelayedDelete(void);
	HRESULT HandsOffStorage();
};

#endif //_ENUMEX_H
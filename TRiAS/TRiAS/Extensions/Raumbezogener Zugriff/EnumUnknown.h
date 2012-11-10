// Header für CEnumUnknown
#include "raumguid.h"

DefineEnumerator(WUnknown);


class MyEnumWUnknown: 
    public NEnumWUnknown
{
public:
    HRESULT Add(LPDISPATCH pIDisp);
};

class CEnumUnknown:
    public IEnumUnknown,
    public CComObjectRoot
{
public:
    STDMETHOD(Next)(ULONG celt, IUnknown ** rgelt, ULONG * pceltFetched);
    STDMETHOD(Skip)(ULONG celt);
    STDMETHOD(Reset)(void);
    STDMETHOD(Clone)(IEnumUnknown ** ppenum);

    BEGIN_COM_MAP(CEnumUnknown)
	    COM_INTERFACE_ENTRY(IEnumUnknown)
    END_COM_MAP()

    HRESULT Add(IDispatch* pIDisp);
    MyEnumWUnknown myEnum;
};
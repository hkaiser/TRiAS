// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CObjDispatch wrapper class

class CObjDispatch : public COleDispatchDriver
{
public:
	CObjDispatch() {}		// Calls COleDispatchDriver default constructor
	CObjDispatch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CObjDispatch(const CObjDispatch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'QueryInterface' not emitted because of invalid return type or parameter type
	unsigned long AddRef();
	unsigned long Release();
	// method 'GetTypeInfoCount' not emitted because of invalid return type or parameter type
	// method 'GetTypeInfo' not emitted because of invalid return type or parameter type
	// method 'GetIDsOfNames' not emitted because of invalid return type or parameter type
	// method 'Invoke' not emitted because of invalid return type or parameter type
#ifdef _DEBUG
    void put_xmin(const VARIANT& min);
	void put_xmax(const VARIANT& max);
	void get_xmin(VARIANT* pmin);
	void get_xmax(VARIANT* pmax);
#endif
    void get_value(DISPID id,VARIANT* pmin);
};

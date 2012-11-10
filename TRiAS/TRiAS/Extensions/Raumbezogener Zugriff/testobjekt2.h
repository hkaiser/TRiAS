// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CTestObjekt2 wrapper class

class CTestObjekt2 : public COleDispatchDriver
{
public:
	CTestObjekt2() {}		// Calls COleDispatchDriver default constructor
	CTestObjekt2(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTestObjekt2(const CTestObjekt2& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

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
	void put_xmin(const VARIANT& min);
	void put_xmax(const VARIANT& max);
	void get_xmin(VARIANT* pmin);
	void get_xmax(VARIANT* pmax);
};

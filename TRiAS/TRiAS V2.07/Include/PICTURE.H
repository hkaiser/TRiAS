// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Picture wrapper class

class CPicture 
	: public COleDispatchDriver
{
public:
	CPicture() {}		// Calls COleDispatchDriver default constructor
	CPicture(LPDISPATCH pDispatch, bool fAutoRelease) 
		: COleDispatchDriver(pDispatch, fAutoRelease) {}
	CPicture(const CPicture& dispatchSrc) 
		: COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetHandle();
	long GetHPal();
	void SetHPal(long);
	short GetType();
	long GetWidth();
	long GetHeight();

// Operations
public:
	// method 'Render' not emitted because of invalid return type or parameter type
};

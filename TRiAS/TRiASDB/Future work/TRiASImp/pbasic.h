// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// CGMPoint wrapper class


class CGMPoint : public COleDispatchDriver
{
public:
	CGMPoint() {}		// Calls COleDispatchDriver default constructor
	CGMPoint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMPoint(const CGMPoint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	double GetX();
	void SetX(double newValue);
	double GetY();
	void SetY(double newValue);
	double GetZ();
	void SetZ(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CGMPoints wrapper class

class CGMPoints : public COleDispatchDriver
{
public:
	CGMPoints() {}		// Calls COleDispatchDriver default constructor
	CGMPoints(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMPoints(const CGMPoints& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	void Add(LPDISPATCH Point, const VARIANT& index);
	void Remove(const VARIANT& index);
};


/////////////////////////////////////////////////////////////////////////////
// CGMPointGeometry wrapper class

class CGMPointGeometry : public COleDispatchDriver
{
public:
	CGMPointGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMPointGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMPointGeometry(const CGMPointGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetOrigin();
	void SetRefOrigin(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CGMLineGeometry wrapper class

class CGMLineGeometry : public COleDispatchDriver
{
public:
	CGMLineGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMLineGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMLineGeometry(const CGMLineGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetStart();
	void SetRefStart(LPDISPATCH newValue);
	LPDISPATCH GetEnd();
	void SetRefEnd(LPDISPATCH newValue);
};
/////////////////////////////////////////////////////////////////////////////
// CGMPolylineGeometry wrapper class

class CGMPolylineGeometry : public COleDispatchDriver
{
public:
	CGMPolylineGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMPolylineGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMPolylineGeometry(const CGMPolylineGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetPoints();
};
/////////////////////////////////////////////////////////////////////////////
// CGMPolygonGeometry wrapper class

class CGMPolygonGeometry : public COleDispatchDriver
{
public:
	CGMPolygonGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMPolygonGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMPolygonGeometry(const CGMPolygonGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetPoints();
};
/////////////////////////////////////////////////////////////////////////////
// CGMBoundaryGeometry wrapper class

class CGMBoundaryGeometry : public COleDispatchDriver
{
public:
	CGMBoundaryGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMBoundaryGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMBoundaryGeometry(const CGMBoundaryGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetExterior();
	void SetRefExterior(LPDISPATCH newValue);
	LPDISPATCH GetHoles();
};
/////////////////////////////////////////////////////////////////////////////
// CGMGeometryCollection wrapper class

class CGMGeometryCollection : public COleDispatchDriver
{
public:
	CGMGeometryCollection() {}		// Calls COleDispatchDriver default constructor
	CGMGeometryCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMGeometryCollection(const CGMGeometryCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	LPDISPATCH Item(const VARIANT& index);
	void Add(LPDISPATCH geometry, const VARIANT& index);
	void Remove(const VARIANT& index);
};
/////////////////////////////////////////////////////////////////////////////
// CGMTextPointGeometry wrapper class

class CGMTextPointGeometry : public COleDispatchDriver
{
public:
	CGMTextPointGeometry() {}		// Calls COleDispatchDriver default constructor
	CGMTextPointGeometry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CGMTextPointGeometry(const CGMTextPointGeometry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetOrigin();
	void SetRefOrigin(LPDISPATCH newValue);
	double GetRotation();
	void SetRotation(double newValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	CString GetRichText();
	void SetRichText(LPCTSTR lpszNewValue);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	short GetFormat();
	void GetNormalUnitVector(double* ui, double* uj, double* uk);
	void SetNormalUnitVector(double ui, double uj, double uk);
};

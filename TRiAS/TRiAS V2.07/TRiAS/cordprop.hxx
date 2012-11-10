// Einstellen der Koordinatensystemeigenschaften dieses Projektes -------------
// File: CORDPROP.HXX

#if !defined(_CORDPROP_HXX)
#define _CORDPROP_HXX

///////////////////////////////////////////////////////////////////////////////
// verwendete Interfaces
DefineSmartInterface(Storage);
DefineSmartInterface(DataObject);

class CCoordProperties : public CPropertySheetExt {
protected:
	HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO);

public:
		CCoordProperties (pWindow pWnd);
		~CCoordProperties (void) {}

	HRESULT LoadPages (void);
};

#endif // _CORDPROP_HXX


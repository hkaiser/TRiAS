// ColorLookUp.h : Declaration of the CColorLookUp

#include "DoubleColor.h"       // main symbols

#if !defined(_COLORLOOKUP_H)
#define _COLORLOOKUP_H

///////////////////////////////////////////////////////////////////////////////
// Benötigte SmartIF's
DefineSmartInterface(DoubleColor);

/////////////////////////////////////////////////////////////////////////////
// Colors

class CColorLookUp : 
	public CComDualImpl<IColorLookUp, &IID_IColorLookUp, &LIBID_ColorLookUp>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CColorLookUp, &CLSID_ColorLookUp>
{
public:
	CColorLookUp() { m_iSteps = 0; }

	BEGIN_COM_MAP(CColorLookUp)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IColorLookUp)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CColorLookUp) 
	DECLARE_REGISTRY_RESOURCEID(IDR_COLORLOOKUP_RGS)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IColorLookUp
	STDMETHOD(Init) (THIS_ int iCnt, IDoubleColor *pIColor1, 
		IDoubleColor *pIColor2, VARIANT vColor3);
	STDMETHOD(get_Color) (THIS_ int iIndex, IDoubleColor **ppIColor);

protected:
	HRESULT InitColors2 (void);
	HRESULT InitColors3 (void);

private:
	WDoubleColor m_StartColor;
	WDoubleColor m_MiddleColor;
	WDoubleColor m_EndColor;
	int m_iSteps;

	typedef vector<WDoubleColor> Colors;
	Colors m_Colors;
};

#endif // _COLORLOOKUP_H

// DoubleColor.h: Declaration of Color, consisting of double values

#if !defined(_DOUBLECOLOR_H)
#define _DOUBLECOLOR_H

/////////////////////////////////////////////////////////////////////////////
// DoubleColor

class CDoubleColor :
	public CComDualImpl<IDoubleColor, &IID_IDoubleColor, &LIBID_ColorLookUp>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CDoubleColor, &CLSID_DoubleColor>
{
public:
	CDoubleColor (void) {}
	HRESULT FinalConstruct (void);

	BEGIN_COM_MAP(CDoubleColor)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IDoubleColor)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CDoubleColor) 
	DECLARE_REGISTRY_RESOURCEID(IDR_DOUBLECOLOR_RGS)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

///////////////////////////////////////////////////////////////////////////////
// IDoubleColor methods
	STDMETHOD(get_RGB) (THIS_ long *plRGB);
	STDMETHOD(put_RGB) (THIS_ long lRGB);

	STDMETHOD(get_Red) (THIS_ double *pdRed);
	STDMETHOD(put_Red) (THIS_ double dRed);
	STDMETHOD(get_Green) (THIS_ double *pdGreen);
	STDMETHOD(put_Green) (THIS_ double dGreen);
	STDMETHOD(get_Blue) (THIS_ double *pdBlue);
	STDMETHOD(put_Blue) (THIS_ double dBlue);
	STDMETHOD(get_Hue) (THIS_ double *pdHue);
	STDMETHOD(put_Hue) (THIS_ double dHue);
	STDMETHOD(get_Saturation) (THIS_ double *pdSat);
	STDMETHOD(put_Saturation) (THIS_ double dSat);
	STDMETHOD(get_Brightness) (THIS_ double *pdBright);
	STDMETHOD(put_Brightness) (THIS_ double dBright);

	STDMETHOD(get_Complement) (THIS_ IDoubleColor **ppIColor);
	STDMETHOD(get_Saturated) (THIS_ IDoubleColor **ppIColor);
	STDMETHOD(get_Grayed) (THIS_ IDoubleColor **ppIColor);
	STDMETHOD(get_Pure) (THIS_ IDoubleColor **ppIColor);

	STDMETHOD(InitRGB) (THIS_ double dRed, double dGreen, double dBlue);
	STDMETHOD(InitHSB) (THIS_ double dHue, double dSat, double dBright);
	STDMETHOD(RetrieveRGB) (THIS_ double *pdRed, double *pdGreen, double *pdBlue);
	STDMETHOD(RetrieveHSB) (THIS_ double *pdHue, double *pdSat, double *pdBright);

private:
// primary attributes
	double m_dRed;
	double m_dGreen;
	double m_dBlue;

// secondary attributes
	double m_dHue;
	double m_dSat;
	double m_dBright;
};

#endif // _DOUBLECOLOR_H

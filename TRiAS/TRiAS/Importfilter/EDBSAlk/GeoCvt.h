// ArcConversion.h : Declaration of the CArcConversion

#ifndef __GEOCVT_H_
#define __GEOCVT_H_


/////////////////////////////////////////////////////////////////////////////
// CArcConversion
class CArcConversion
{
public:
	CArcConversion();

	get_Anisotropy(/*[out, retval]*/ double *pVal);
	put_Anisotropy(/*[in]*/ double newVal);
	get_Precision(/*[out, retval]*/ double *pVal);
	put_Precision(/*[in]*/ double newVal);
	Convert1(/*[in]*/ double StartX, /*[in]*/ double StartY,/*[in]*/ double OriginX,/*[in]*/ double OriginY,/*[in]*/ double EndX,/*[in]*/ double EndY, /*[in, out]*/ SAFEARRAY **PolyLineArc);
private:
	double m_dAnisotropy;
	double m_dPrecision;
};

void ConvertArc1(/*[in]*/ double StartX, /*[in]*/ double StartY,/*[in]*/ double OriginX,/*[in]*/ double OriginY,/*[in]*/ double EndX,/*[in]*/ double EndY, /*[in, out]*/ SAFEARRAY **PolyLineArc);

#endif //__GEOCVT_H_

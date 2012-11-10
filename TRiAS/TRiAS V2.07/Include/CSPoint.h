// @doc
// @module CSPoint.h | Wrapper für _DGMPoint

#if !defined(_CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_)
#define _CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// TypeLibs
// type libraries
/*#import "PBasic.tlb" \
	raw_interfaces_only \
	no_namespace \
	named_guids \
	raw_native_types \
	rename("Point", "GMPoint")
*/
///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(_DGMPoint, IID__DGMPoint);	// W_DGMPoint

class CCSPoint 
{
private:
	W_DGMPoint m_pt;

public:
	CCSPoint (double dX, double dY, double dZ = 0.0)
		: m_pt (CLSID_TRiASCSPoint)
	{
	double Coords[3] = { dX, dY, dZ };

		m_pt -> SetPoint(Coords);
	}
	~CCSPoint () {}

// Zugriffsoperatoren
	_DGMPoint *operator &() { return m_pt; }
	const _DGMPoint *operator &() const { return m_pt; }
	_DGMPoint *operator ->() const { return m_pt; }
	operator _DGMPoint *() { return m_pt; }
};

#endif // !defined(_CSPOINT_H__5EA16685_5F37_11D1_B9E5_080036D63803__INCLUDED_)

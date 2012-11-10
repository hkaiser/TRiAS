// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 19.10.2001 09:13:47 
//
// @doc
// @module CoordSystems.h | Declaration of the <c CCoordSystems> class

#if !defined(_COORDSYSTEMS_H__AC51A9F1_644B_473E_8736_EEF777B71A9F__INCLUDED_)
#define _COORDSYSTEMS_H__AC51A9F1_644B_473E_8736_EEF777B71A9F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/SafeArray.h>

#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids


///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASCSTransform);
DefineSmartInterface(TRiASCS);

///////////////////////////////////////////////////////////////////////////////
// Wrapper hält gesamtes Koordinatensystemhandling
class CCoordSystems
{
public:
	CCoordSystems() 
	{
	}
	~CCoordSystems()
	{
		if (m_CTF.IsValid())
			m_CTF -> ShutDown();
	}

	bool IsValid() { return m_CSIn.IsValid() && m_CSOut.IsValid() && m_CTF.IsValid(); }

	HRESULT LoadCSIn (LPCSTR pcTcfIn)
	{
		m_CSIn.Assign(NULL);
		if (NULL == pcTcfIn)
			return E_POINTER;

		RETURN_FAILED_HRESULT(EnsureCTF());
		RETURN_FAILED_HRESULT(m_CSIn.CreateInstance(CLSID_TRIASCS));
		RETURN_FAILED_HRESULT(m_CSIn -> LoadFromFile(CComBSTR(pcTcfIn)))
		RETURN_FAILED_HRESULT(m_CSIn -> get_GUID(&m_bstrGuid))
		RETURN_FAILED_HRESULT(m_CTF -> AddInputCS(m_CSIn));
		return S_OK;
	}

	HRESULT LoadCSOut (LPCSTR pcTcfOut)
	{
		_ASSERTE(m_CSIn.IsValid());		// muß zuerst initailisiert werden

		m_CSOut.Assign(NULL);
		if (NULL == pcTcfOut)
			return E_POINTER;

		RETURN_FAILED_HRESULT(EnsureCTF());
		RETURN_FAILED_HRESULT(m_CSOut.CreateInstance(CLSID_TRIASCS));

		RETURN_FAILED_HRESULT(m_CSOut -> LoadFromFile(CComBSTR(pcTcfOut)))
		RETURN_FAILED_HRESULT(m_CTF -> putref_OutputCS(m_CSOut));
		RETURN_FAILED_HRESULT(m_CSOut -> Recompute());
		return S_OK;
	}

	HRESULT Transform (long lCount, double *pX, double *pY)
	{
	// Daten bereitstellen
	CSafeArray saIn (VT_R8, 3*lCount);

		{
		CSafeArrayLock<CSCOORD> lockCoords (saIn);
		CSCOORD *pCoord = lockCoords;

			_ASSERTE(lCount == lockCoords.Size()/(sizeof(CSCOORD)/sizeof(double)));
			for (long i = 0; i < lCount; ++i, ++pCoord) {
				pCoord->X = pX[i];
				pCoord->Y = pY[i];
				pCoord->Z = 0;
			}
		}

	// Koordinaten transformieren
	VARIANT vIn;
	CComVariant vOut;

		V_VT(&vIn) = VT_R8|VT_ARRAY;
		V_ARRAY(&vIn) = saIn;
		RETURN_FAILED_HRESULT(m_CTF -> Transform(m_bstrGuid, vIn, &vOut));

	// Koordinaten zurückkopieren
	CSafeArray saOut (VT_R8);

		if (!saOut.Attach(V_ARRAY(&vOut), true))
			return E_UNEXPECTED;

		{
		CSafeArrayLock<CSCOORD> lockCoords (saOut);
		CSCOORD *pCoord = lockCoords;

			_ASSERTE(lCount == lockCoords.Size()/(sizeof(CSCOORD)/sizeof(double)));
			for (long i = 0; i < lCount; ++i, ++pCoord) {
				pX[i] = pCoord->X;
				pY[i] = pCoord->Y;
			}
		}
		return S_OK;
	}

protected:
	HRESULT EnsureCTF()
	{
		if (m_CTF.IsValid())
			return S_FALSE;
		return m_CTF.CreateInstance(CLSID_TRiASCSTransform);
	}

private:
	WTRiASCSTransform m_CTF;
	CComBSTR m_bstrGuid;
	WTRiASCS m_CSIn;
	WTRiASCS m_CSOut;
};

extern CCoordSystems g_CoordSys;

#endif // !defined(_COORDSYSTEMS_H__AC51A9F1_644B_473E_8736_EEF777B71A9F__INCLUDED_)

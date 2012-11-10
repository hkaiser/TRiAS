// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 12:22:20 PM
//
// @doc 
// @module GeometryBlob.h | Geometrie eines Objektes GeoMedia-like aufbereiten

#if !defined(_GEOMETRYBLOB_H__3D5F0813_036D_11D2_8651_00600875138A__INCLUDED_)
#define _GEOMETRYBLOB_H__3D5F0813_036D_11D2_8651_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma warning (disable: 4192)	// automatically excluding 'IMoniker' while importing type library

/////////////////////////////////////////////////////////////////////////////
// Includes
#if defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)
#include <GMObjects/GMObjects.h>
#endif // defined(_USE_GEOMEDIA_GEOMETRY_TYPELIBS)

#import <tlb/tdbgeo.tlb>			\
	no_namespace					\
	raw_native_types				\
	raw_interfaces_only				\
	named_guids						\
	no_implementation				\
	exclude("IPersist", "IPersistMemory")

#include <CSSPoint.h>
#include <ScaleHeader.h>

namespace trias_geometryblob {

/////////////////////////////////////////////////////////////////////////////
// Klasse, die aus einem Geometriefeld ein Geometrie-Blob in einem SAFEARRAY macht
class _TRIAS01_ENTRY CMakeBlobs
{
public:
// Zugriffsfunktionen
	typedef HRESULT (CMakeBlobs::* GETBLOBSIZEPROC)(/*[in]*/unsigned long lCnt, /*[in]*/ void *pData, /*[out]*/unsigned long *plSize);
	typedef HRESULT (CMakeBlobs::* MAKEBLOBPROC)(/*[in]*/unsigned long ulCnt, /*[in]*/double_i itx, /*[in]*/double_i ity, /*[in]*/CSPointBase *pNormal, /*[in]*/ void *pData, /*[in,out]*/BYTE *pBlob);
	typedef HRESULT (CMakeBlobs::* MAKEVERTICESPROC)(/*[in]*/BYTE *pBlob, /*[in]*/double_v &rX, /*[in]*/double_v &rY, /*[in]*/ void *pData);

	typedef struct tagMAKEBLOBDATA {
		const CLSID *pClsId;
		GETBLOBSIZEPROC GetBlobSize;
		MAKEBLOBPROC MakeBlob;
		MAKEVERTICESPROC MakeVertices;
	} MAKEBLOBDATA;

	typedef struct tagTEXTBLOBDATA {
		double dRotation;
		long lFlags;
		string strText;
	} TEXTBLOBDATA;

public:
	CMakeBlobs(CScaleHeader &rHdr) : m_rHdr(rHdr) {}
	~CMakeBlobs() {}

	MAKEBLOBDATA *GetMakeBlobData() 
	{
		static MAKEBLOBDATA s_cbMakeBlobs[] = {
			{ &CLSID_TRiASCSPointGeometry, GetPointGeometrySize, MakePointGeometryBlob, MakePointVertices },
			{ &CLSID_TRiASCSPolylineGeometry, GetPolylineGeometrySize, MakePolylineGeometryBlob, MakePolylineVertices },
			{ &CLSID_TRiASCSPolygonGeometry, GetPolygonGeometrySize, MakePolygonGeometryBlob, MakePolygonVertices },
			{ &CLSID_TRiASCSTextPointGeometry, GetTextGeometrySize, MakeTextGeometryBlob, MakeTextVertices },
			{ NULL, NULL, NULL, NULL },
		};
		return s_cbMakeBlobs;
	}

// GETBLOBSIZEPROC
	HRESULT GetPointGeometrySize (unsigned long lCnt, void *pData, unsigned long *plSize);
	HRESULT GetPolylineGeometrySize (unsigned long lCnt, void *pData, unsigned long *plSize);
	HRESULT GetPolygonGeometrySize (unsigned long lCnt, void *pData, unsigned long *plSize);
	HRESULT GetTextGeometrySize (unsigned long lCnt, void *pData, unsigned long *plSize);

// MAKEBLOBPROC
	HRESULT MakePointGeometryBlob (unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob);
	HRESULT MakePolylineGeometryBlob (unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob);
	HRESULT MakePolygonGeometryBlob (unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob);
	HRESULT MakeTextGeometryBlob (unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob);

// MAKEVERTICESPROC
	HRESULT MakePointVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData);
	HRESULT MakePolylineVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData);
	HRESULT MakePolygonVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData);
	HRESULT MakeTextVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData);

public:
	HRESULT GetBlobSize (REFCLSID rClsId, unsigned long lCnt, void *pData, unsigned long *plSize);
	HRESULT MakeBlob (REFCLSID rClsId, unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob);

	HRESULT MakeVertices (REFCLSID rClsId, BYTE *pBlob, double_v &rX, double_v &rY, void *pData);

private:
	CScaleHeader &m_rHdr;
};

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
_TRIAS01_ENTRY HRESULT CreateSABlobFromVertices (CScaleHeader &rHdr, double_v &rX, double_v &rY, CSPointBase *pNormal, void *pData, REFCLSID rClsId, SAFEARRAY **pSA);
_TRIAS01_ENTRY HRESULT CreateBlobFromVertices (CScaleHeader &rHdr, unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, REFCLSID rClsId, void **pBlob, unsigned long *plSize);
_TRIAS01_ENTRY HRESULT CreateSABlobBoundaryFromArray (unsigned long lCnt, void **ppData, unsigned long *pSizes, SAFEARRAY **pSA);

_TRIAS01_ENTRY HRESULT CreateVerticesFromSABlob (SAFEARRAY *pSA, CScaleHeader &rHdr, double_v &rX, double_v &rY, void *pData, REFCLSID rClsId);
_TRIAS01_ENTRY HRESULT CreateVerticesFromBlob (BYTE *pBlob, CScaleHeader &rHdr, double_v &rX, double_v &rY, void *pData, REFCLSID rClsId);
_TRIAS01_ENTRY HRESULT CreateArrayFromSABlobBoundary (SAFEARRAY *pSA, vector<BYTE *> &rBlobs, vector<unsigned long> &rSizes);

_TRIAS01_ENTRY BOOL BlobHasBoundaryGeometry (SAFEARRAY *pSA);

} // namespace trias_geometryblob

#endif // !defined(_GEOMETRYBLOB_H__3D5F0813_036D_11D2_8651_00600875138A__INCLUDED_)

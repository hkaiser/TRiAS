// $Header: /TRiAS/TRiAS/TRiAS01/GeometryBlob.cpp 1     15.06.98 22:23 Hartmut Kaiser $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/14/1998 12:22:14 PM
//
// @doc
// @module GeometryBlob.cpp | Geometrie eines Objektes GeoMedia-like aufbereiten

#include "trias01p.hxx"

#include <Array.h>

#include <NativeObject.h>
#include <GeometryBlob.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

namespace trias_geometryblob {

/////////////////////////////////////////////////////////////////////////////
// globale Instanz für GeometryBlob-Konvertierungen
HRESULT CMakeBlobs::GetBlobSize (REFCLSID rClsId, unsigned long lCnt, void *pData, unsigned long *plSize)
{
MAKEBLOBDATA *pMBD = GetMakeBlobData();

	while (NULL != pMBD -> pClsId) {
		if (InlineIsEqualGUID(rClsId, *(pMBD -> pClsId))) 
			return (this ->* (pMBD -> GetBlobSize))(lCnt, pData, plSize);
		pMBD++;
	}
	return E_FAIL;
}

HRESULT CMakeBlobs::MakeBlob (
	REFCLSID rClsId, unsigned long lCnt, double_i itx, double_i ity, 
	CSPointBase *pNormal, void *pData, BYTE *pBlob)
{
MAKEBLOBDATA *pMBD = GetMakeBlobData();

	while (NULL != pMBD -> pClsId) {
		if (InlineIsEqualGUID(rClsId, *(pMBD -> pClsId))) 
			return (this ->* (pMBD -> MakeBlob))(lCnt, itx, ity, pNormal, pData, pBlob);
		pMBD++;
	}
	return E_FAIL;
}

HRESULT CMakeBlobs::MakeVertices (
	REFCLSID rClsId, BYTE *pBlob, double_v &rX, double_v &rY, void *pData)
{
MAKEBLOBDATA *pMBD = GetMakeBlobData();

	while (NULL != pMBD -> pClsId) {
		if (InlineIsEqualGUID(rClsId, *(pMBD -> pClsId))) 
			return (this ->* (pMBD -> MakeVertices))(pBlob, rX, rY, pData);
		pMBD++;
	}
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////
// GETBLOBSIZEPROC
HRESULT CMakeBlobs::GetPointGeometrySize (unsigned long, void *, unsigned long *plSize)
{
	if (NULL == plSize)
		return E_POINTER;
	*plSize = sizeof(CLSID) + sizeof(CSPointBase);		// ein WerteTripel
	return S_OK;
}

HRESULT CMakeBlobs::GetPolylineGeometrySize (unsigned long lCnt, void * /*pData*/, unsigned long *plSize)
{
	if (NULL == plSize)
		return E_POINTER;
	*plSize = sizeof(CLSID) + sizeof(long) + lCnt*sizeof(CSPointBase);
	return S_OK;
}

HRESULT CMakeBlobs::GetPolygonGeometrySize (unsigned long lCnt, void * /*pData*/, unsigned long *plSize)
{
	if (NULL == plSize)
		return E_POINTER;
	*plSize = sizeof(CLSID) + sizeof(long) + lCnt*sizeof(CSPointBase);
	return S_OK;
}

HRESULT CMakeBlobs::GetTextGeometrySize (unsigned long /*lCnt*/, void *pData, unsigned long *plSize)
{
	if (NULL == plSize)
		return E_POINTER;

TEXTBLOBDATA *pTBD = reinterpret_cast<TEXTBLOBDATA *>(pData);

	TX_ASSERT(NULL != pTBD);	// kein Text kann vorkommen (beim Neuerzeugen)
	*plSize = sizeof(CLSID) + 2*sizeof(CSPointBase) + sizeof(double) + 2*sizeof(long) + (pTBD -> strText.size()+1)*sizeof(wchar_t);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// MAKEBLOBPROC
template<class T>
inline void AssignAndAdvance (BYTE *& p, T x)
{
	memcpy (p, (void *)&x, sizeof(T));
	p += sizeof(T); 
}
inline void AssignAndAdvance (BYTE *& p, void *px, unsigned int iSize)
{
	memcpy (p, px, iSize);
	p += iSize; 
}

HRESULT CMakeBlobs::MakePointGeometryBlob (
	unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *, void *pData, BYTE *pBlob)
{
#if defined(_DEBUG)
BYTE *pBlobOrigin = pBlob;
unsigned long ulSize = 0;

	TX_ASSERT(1 == ulCnt);
	GetPointGeometrySize (ulCnt, pData, &ulSize);	//lint !e534
	TX_ASSERT(TIsValidAddress(pBlob, ulSize, true));
#endif // _DEBUG

	AssignAndAdvance(pBlob, CLSID_TRiASCSPointGeometry);
//	AssignAndAdvance(pBlob, *pPts);
	RETURN_FAILED_HRESULT(m_rHdr.UnScale (*itx, *ity, *(CSPointBase *)pBlob));

#if defined(_DEBUG)
	pBlob += sizeof(CSPointBase);
	TX_ASSERT(pBlob-pBlobOrigin == ulSize);
#endif // _DEBUG
	return S_OK;
}

HRESULT CMakeBlobs::MakePolylineGeometryBlob (
	unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *, void *pData, BYTE *pBlob)
{
#if defined(_DEBUG)
BYTE *pBlobOrigin = pBlob;
unsigned long ulSize = 0;

	GetPolylineGeometrySize (ulCnt, pData, &ulSize);	//lint !e534
	TX_ASSERT(TIsValidAddress(pBlob, ulSize, true));
#endif // _DEBUG
	
	AssignAndAdvance(pBlob, CLSID_TRiASCSPolylineGeometry);
	AssignAndAdvance(pBlob, ulCnt);
	for (unsigned long i = 0; i < ulCnt; i++) 
	{
//		AssignAndAdvance(pBlob, pPts[i]);
		RETURN_FAILED_HRESULT(m_rHdr.UnScale (*itx, *ity, *(CSPointBase *)pBlob));
		++itx; ++ity;
		pBlob += sizeof(CSPointBase);
	}
		
	TX_ASSERT(pBlob-pBlobOrigin == ulSize);
	return S_OK;
}

HRESULT CMakeBlobs::MakePolygonGeometryBlob (
	unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *, void *pData, BYTE *pBlob)
{
#if defined(_DEBUG)
BYTE *pBlobOrigin = pBlob;
unsigned long ulSize = 0;

	GetPolygonGeometrySize (ulCnt, pData, &ulSize);	//lint !e534
	TX_ASSERT(TIsValidAddress(pBlob, ulSize, true));
#endif // _DEBUG

	AssignAndAdvance(pBlob, CLSID_TRiASCSPolygonGeometry);
	AssignAndAdvance(pBlob, ulCnt);
	for (unsigned long i = 0; i < ulCnt; i++) 
	{
//		AssignAndAdvance(pBlob, pPts[i]);
		RETURN_FAILED_HRESULT(m_rHdr.UnScale (*itx, *ity, *(CSPointBase *)pBlob));
		++itx; ++ity;
		pBlob += sizeof(CSPointBase);
	}

	TX_ASSERT(pBlob-pBlobOrigin == ulSize);
	return S_OK;
}

HRESULT CMakeBlobs::MakeTextGeometryBlob (
	unsigned long ulCnt, double_i itx, double_i ity, CSPointBase *pNormal, void *pData, BYTE *pBlob)
{
#if defined(_DEBUG)
BYTE *pBlobOrigin = pBlob;
unsigned long ulSize = 0;

	TX_ASSERT(1 == ulCnt);
	GetTextGeometrySize (ulCnt, pData, &ulSize);
	TX_ASSERT(TIsValidAddress(pBlob, ulSize, true));
#endif // _DEBUG
TEXTBLOBDATA *pTBD = (TEXTBLOBDATA *)pData;
size_t uiTextSize = (pTBD -> strText.size() + 1) * sizeof(wchar_t);

	USES_CONVERSION;
	AssignAndAdvance(pBlob, CLSID_TRiASCSTextPointGeometry);
//	AssignAndAdvance(pBlob, *pPts);
	RETURN_FAILED_HRESULT(m_rHdr.UnScale (*itx, *ity, *(CSPointBase *)pBlob));
	pBlob += sizeof(CSPointBase);
	AssignAndAdvance(pBlob, pTBD -> dRotation);
	AssignAndAdvance(pBlob, *pNormal);
	AssignAndAdvance(pBlob, pTBD -> lFlags);
	AssignAndAdvance(pBlob, uiTextSize);
	AssignAndAdvance(pBlob, A2OLE(pTBD -> strText.c_str()), uiTextSize);

	TX_ASSERT(pBlob-pBlobOrigin == ulSize);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// MAKEVERTICESPROC
template<class T>
inline void RetrieveAndAdvance (T &rx, BYTE *& p)
{
	memcpy ((void *)&rx, p, sizeof(T));
	p += sizeof(T); 
}

inline void RetrieveAndAdvance (void *px, BYTE *& p, unsigned int iSize)
{
	memcpy (px, p, iSize);
	p += iSize; 
}

HRESULT CMakeBlobs::MakePointVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData)
{
	pBlob += sizeof(GUID);										// GUID übergehen
	return m_rHdr.Scale (*(CSPointBase *)pBlob, &rX, &rY);		// Koordinaten lesen
}

HRESULT CMakeBlobs::MakePolylineVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData)
{
	pBlob += sizeof(GUID);					// GUID übergehen

unsigned long lCnt = 0;

	RetrieveAndAdvance(lCnt, pBlob);
	for (unsigned long i = 0; i < lCnt; i++) 
	{
		RETURN_FAILED_HRESULT(m_rHdr.Scale (*(CSPointBase *)pBlob, &rX, &rY));	// Koordinaten lesen
		pBlob += sizeof(CSPointBase);
	}
	return S_OK;
}

HRESULT CMakeBlobs::MakePolygonVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData)
{
	pBlob += sizeof(GUID);					// GUID übergehen

unsigned long lCnt = 0;

	RetrieveAndAdvance(lCnt, pBlob);
	for (unsigned long i = 0; i < lCnt; i++) 
	{
		RETURN_FAILED_HRESULT(m_rHdr.Scale (*(CSPointBase *)pBlob, &rX, &rY));	// Koordinaten lesen
		pBlob += sizeof(CSPointBase);
	}
	return S_OK;
}

HRESULT CMakeBlobs::MakeTextVertices (BYTE *pBlob, double_v &rX, double_v &rY, void *pData)
{
	USES_CONVERSION;

TEXTBLOBDATA *pTBD = (TEXTBLOBDATA *)pData;

	pBlob += sizeof(GUID);						// GUID übergehen

	RETURN_FAILED_HRESULT(m_rHdr.Scale (*(CSPointBase *)pBlob, &rX, &rY));	// Koordinate lesen
	pBlob += sizeof(CSPointBase);

	RetrieveAndAdvance(pTBD -> dRotation, pBlob);
	pBlob += sizeof(CSPointBase);					// Normale übergehen
	RetrieveAndAdvance(pTBD -> lFlags, pBlob);

// Text einlesen
ULONG uiTextSize = 0;
LPOLESTR pText = NULL;

	RetrieveAndAdvance(uiTextSize, pBlob);
	ATLTRY(pText = new OLECHAR[uiTextSize]);
	if (NULL == pText) return E_OUTOFMEMORY;

	RetrieveAndAdvance(pText, pBlob, uiTextSize);
	pTBD -> strText = OLE2A(pText);
	DELETE_OBJ(pText);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Erzeugen eines VT_UI1-SAFEARRAY aus einem Koordinatenfeld
HRESULT CreateSABlobFromVertices (
	CScaleHeader &rHdr, double_v &rX, double_v &rY, 
	CSPointBase *pNormal, void *pData, REFCLSID rClsId, SAFEARRAY **pSA)
{
	if (NULL == pSA)
		return E_POINTER;

	COM_TRY {
	// resultierende Größe feststellen
	unsigned long ulSize = 0;
	CMakeBlobs MakeBlobs (rHdr);

		TX_ASSERT(rX.size() == rY.size());
		THROW_FAILED_HRESULT(MakeBlobs.GetBlobSize (rClsId, rX.size(), pData, &ulSize));

	// SAFEARRAY anlegen und Daten übernehmen
	CSafeArray sa (VT_UI1, ulSize);

		if (!sa) _com_issue_error(E_OUTOFMEMORY);
		{
		CSafeArrayLock<BYTE> lock (sa);

			THROW_FAILED_HRESULT(MakeBlobs.MakeBlob (rClsId, rX.size(), rX.begin(), rY.begin(), pNormal, pData, lock));
		} // lock goes out of scope

		*pSA = sa.Detach();		// Ergebnis liefern

	} COM_CATCH;
	return S_OK;
}

// Erzeugen eines BYTE-Blobs aus einem Koordinatenfeld
HRESULT CreateBlobFromVertices (
	CScaleHeader &rHdr, unsigned long ulCnt, double_i itx, double_i ity, 
	CSPointBase *pNormal, void *pData, REFCLSID rClsId, void **ppBlob, unsigned long *plSize)
{
	if (NULL == ppBlob || NULL == plSize)
		return E_POINTER;

BYTE *pNewData = NULL;

	COM_TRY {
	// resultierende Größe feststellen
	unsigned long ulSize = 0;
	CMakeBlobs MakeBlobs (rHdr);

		THROW_FAILED_HRESULT(MakeBlobs.GetBlobSize (rClsId, ulCnt, pData, &ulSize));

	// SAFEARRAY anlegen und Daten übernehmen
		pNewData = (BYTE *)::CoTaskMemAlloc (ulSize);
		if (NULL == pNewData) _com_issue_error(E_OUTOFMEMORY);

		THROW_FAILED_HRESULT(MakeBlobs.MakeBlob (rClsId, ulCnt, itx, ity, pNormal, pData, pNewData));

	// Ergebnisse liefern
		*ppBlob = pNewData;
		*plSize = ulSize;

	} COM_CATCH_OP(::CoTaskMemFree(pNewData));
	return S_OK;
}

// Erzeugen einer BoundaryGeometry aus einem Feld von Koordinatenfeldern
HRESULT CreateSABlobBoundaryFromArray (
	unsigned long lCnt, void **ppData, unsigned long *pSizes, SAFEARRAY **pSA)
{
	COM_TRY {
	// GesamtGröße feststellen: Boundary  ExteriorSize   Exterior    HolesSize
	unsigned long ulSize = sizeof(GUID) + sizeof(long) + pSizes[0] + sizeof(long);
	//						    GeomColl       numItems
	unsigned long ulHolesSize = sizeof(GUID) + sizeof(long);

		for (unsigned long i = 1; i < lCnt; i++) 
		//				   ItemSize       Item
			ulHolesSize += sizeof(long) + pSizes[i];

	// SAFEARRAY anlegen und Daten übernehmen
	CSafeArray sa (VT_UI1, ulSize+ulHolesSize);

		if (!sa) _com_issue_error(E_OUTOFMEMORY);
		{
		CSafeArrayLock<BYTE> lock (sa);
		BYTE *pBlob = lock;
		unsigned long iFirst = 0;

		// Exterior erzeugen
			AssignAndAdvance(pBlob, CLSID_TRiASCSBoundaryGeometry);
			AssignAndAdvance(pBlob, pSizes[0]);
			AssignAndAdvance(pBlob, ppData[0], pSizes[0]);

			AssignAndAdvance(pBlob, ulHolesSize);
			AssignAndAdvance(pBlob, CLSID_TRiASCSGeometryCollection);
			AssignAndAdvance(pBlob, lCnt-1);

			for (unsigned long j = 1; j < lCnt; j++) {
				AssignAndAdvance(pBlob, pSizes[j]);
				AssignAndAdvance(pBlob, ppData[j], pSizes[j]);
				TX_ASSERT(pBlob - lock <= ulSize+ulHolesSize);
			}

		// abschließende Tests
			TX_ASSERT(pBlob - lock == ulSize+ulHolesSize);
		} // lock goes out of scope

		*pSA = sa.Detach();		// Ergebnis liefern

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer Stützpunktliste aus einem SafeArray
HRESULT CreateVerticesFromSABlob (
	SAFEARRAY *pSA, CScaleHeader &rHdr, double_v &rX, double_v &rY, void *pData, REFCLSID rClsId)
{
	COM_TRY {
	CSafeArray sa (VT_UI1);

		if (!sa.Attach (pSA, true))
			return E_UNEXPECTED;

		{
		CSafeArrayLock<BYTE> lock (sa);
		CMakeBlobs MakeBlobs (rHdr);

			THROW_FAILED_HRESULT(MakeBlobs.MakeVertices (rClsId, lock, rX, rY, pData));
		} // lock goes out of scope

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Erzeugen einer Stützpunktfolge aus einem Blob
HRESULT CreateVerticesFromBlob (
	BYTE *pBlob, CScaleHeader &rHdr, double_v &rX, double_v &rY, void *pData, REFCLSID rClsId)
{
CMakeBlobs MakeBlobs (rHdr);

	return MakeBlobs.MakeVertices (rClsId, pBlob, rX, rY, pData);
}

/////////////////////////////////////////////////////////////////////////////
// Erzeugen einzelner Blobs aus einer Kantenfolge 
HRESULT CreateArrayFromSABlobBoundary (SAFEARRAY *pSA, vector<BYTE *> &rBlobs, ulong_v &rSizes)
{
	COM_TRY {
	// SAFEARRAY anlegen und Daten übernehmen
	CSafeArray sa (VT_UI1);

		if (!sa.Attach (pSA, true))
			_com_issue_error(E_UNEXPECTED);

		{
		CSafeArrayLock<BYTE> lock (sa);
		BYTE *pBlob = lock;

		// GUID übergehen
			TX_ASSERT(InlineIsEqualGUID (*(GUID *)pBlob, CLSID_TRiASCSBoundaryGeometry));
			pBlob += sizeof(GUID);				// GUID übergehen

		// Exterior einlesen
		unsigned long ulSize = 0;

			RetrieveAndAdvance(ulSize, pBlob);
			rSizes.push_back(ulSize);			// Größe des BLOB's speichern

		BYTE *pData = (BYTE *)::CoTaskMemAlloc (ulSize);

			if (NULL == pData) _com_issue_error(E_OUTOFMEMORY);
			RetrieveAndAdvance(pData, pBlob, ulSize);
			rBlobs.push_back (pData);

		// Löcher behandeln
		unsigned long ulHolesSize = 0;

			RetrieveAndAdvance(ulHolesSize, pBlob);

		// GUID übergehen
			TX_ASSERT(InlineIsEqualGUID (*(GUID *)pBlob, CLSID_TRiASCSGeometryCollection));
			pBlob += sizeof(GUID);

#if defined(_DEBUG)
		long ulHolesSizeDeb = 0;
#endif // _DEBUG
		long lCnt = 0;		// Anzahl der Löcher

			RetrieveAndAdvance(lCnt, pBlob);
			for (unsigned long j = 0; j < lCnt; j++) {
			unsigned long ulHole = 0;

				RetrieveAndAdvance(ulHole, pBlob);
				rSizes.push_back(ulHole);

				pData = (BYTE *)::CoTaskMemAlloc (ulHole);
				if (NULL == pData) _com_issue_error(E_OUTOFMEMORY);

				RetrieveAndAdvance(pData, pBlob, ulHole);
				rBlobs.push_back (pData);

#if defined(_DEBUG)
				ulHolesSizeDeb += ulHole;
				ulHolesSizeDeb += sizeof(unsigned long);
				TX_ASSERT(pBlob - lock <= ulSize+ulHolesSize+sizeof(GUID)+2*sizeof(unsigned long));
#endif // _DEBUG
			}

		// abschließende Tests
			TX_ASSERT(pBlob - lock == ulSize+ulHolesSize+sizeof(GUID)+2*sizeof(unsigned long));
			TX_ASSERT(ulHolesSizeDeb+sizeof(GUID)+sizeof(long) == ulHolesSize);
		} // lock goes out of scope

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Feststellen, obs eine Boundaraygeometrie ist
BOOL BlobHasBoundaryGeometry (SAFEARRAY *pSA)
{
// SAFEARRAY anlegen und Daten übernehmen
CSafeArray sa (VT_UI1);

	if (!sa.Attach (pSA, true))
		return FALSE;

CSafeArrayLock<GUID> lock (sa);

	return InlineIsEqualGUID(CLSID_TRiASCSBoundaryGeometry, *(GUID *)lock);
}

} // namespace trias_geometryblob;

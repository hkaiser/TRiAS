/*
Datei: GEOOBJS.CPP

Realisiert die Verwaltung der typspezifischen Objektgeometrien.
*/

#include "pheader.h"			// vorübersetzte Header
#include "resource.h"			// Ressource-Konstanten

//	GUID-Header
#include <xtsnguid.h>
#include <triashelper.h>
#include <objgguid.h>			// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <initguid.h>

//	TRiAS-Header
#include <IGeometr.hxx>			// IObjektGeometrie
#include <ospace/com/iterenum.h>

//	STL-Header
#include <ospace/com/smartif.h>			

#include "geoobjs.hpp"			//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface (InitObjektGeometrie);
//	CGeometrieObject ----------------------------------------------
// Interface und Abmaße Erzeugen --> kein try/catch
CGeometrieObject::CGeometrieObject (long lObjNr)	
{
	ASSERT (lObjNr > 0);
	m_bIsDoppelt = FALSE;

//	Objekt im Speicher erzeugen
	WInitObjektGeometrie Init (CLSID_ObjektGeometrie, CLSCTX_INPROC_SERVER, NULL); // throw hr

//	Geometrie init. (alles 0 setzen)
	HRESULT hr = Init -> InitObjGeometry (lObjNr);
	if (FAILED(hr))
		_com_issue_error (hr);

//	eigentliche Interface besorgen
	m_wIObjGeo = Init;	// throw hr
}

//	default Konstruktor
CGeometrieObject::CGeometrieObject ()	
{
	m_bIsDoppelt = FALSE;
}

//	Copy-Konstruktor
CGeometrieObject::CGeometrieObject (const CGeometrieObject &OK)	
{
	m_bIsDoppelt = OK.m_bIsDoppelt;
	((CGeometrieObject &)OK).GetInterface (m_wIObjGeo.ppi ());
}

BOOL CGeometrieObject :: operator = (const CGeometrieObject &OK) 
{
	m_bIsDoppelt = OK.m_bIsDoppelt;
	return (NOERROR == ((CGeometrieObject &)OK).GetInterface (m_wIObjGeo.ppi ()));
}

HRESULT CGeometrieObject :: GetInterface (IObjektGeometrie **ppIOG) 
{
	if (NULL == ppIOG)
		return E_POINTER;

	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 
	
	*ppIOG = m_wIObjGeo;
	if (NULL != *ppIOG)
		(*ppIOG) -> AddRef ();
	else
		return E_UNEXPECTED;

	return NOERROR;
}

/*
BOOL CGeometrieObject :: operator == (const CGeometrieObject &OK) const 
{
	WObjektGeometrie IOG;
	long lONr1 = -1;
	long lONr2 = -1;

	HRESULT hr = ((CGeometrieObject &)OK).GetInterface (IOG.ppi());
	if (FAILED(hr))
		throw hr;
	ASSERT (NULL != IOG);

	hr = IOG -> GetONr (&lONr1);
	if (FAILED(hr))
		throw hr;
	
	m_wIObjGeo -> GetONr (&lONr2);
	
	return lONr1 == lONr2;
}
*/

//	lese Objektnummer
long CGeometrieObject :: GetObjNummer (void)
{
//	prüfe interne Parameter
	ASSERT (NULL != (IObjektGeometrie *)m_wIObjGeo); 
	
	long lObjNr = 0;
	HRESULT hr = m_wIObjGeo -> GetONr (&lObjNr);
	if (FAILED(hr))
		_com_issue_error (hr);

	return lObjNr;
}

// CCompareObjects --------------------------------------------------------------
CCompareObjects :: CCompareObjects (IEnumObjectsByNumber *pIEnum)
{
	ASSERT (NULL != pIEnum);
	m_pIEnumObjs = pIEnum;

	m_lpCnt = m_pX = m_pY = NULL;
	m_lCnt = 0;
	m_sKCnt = 0;
	m_bIsFlaeche = FALSE;

}

// lese Geometrie
void CCompareObjects :: GetGeometrie (CGeometrieObject &Object, long **ppX, long **ppY, long *lpCnt, 
									  short *spKCnt, long **lppCnt)
{
//	prüfe Parameter
	ASSERT (NULL != (IObjektGeometrie *)Object.m_wIObjGeo); 
	ASSERT ((NULL != ppX) && (NULL != ppY) && (NULL != lpCnt));

//	Stützpunktanzahl lesen
	HRESULT hr = Object.m_wIObjGeo -> GetCnt (lpCnt);
	if (FAILED(hr))
		_com_issue_error (hr);
	
//	Konturanzahl lesen
	if (NULL != spKCnt)
	{
		hr = Object.m_wIObjGeo -> GetKCnt (spKCnt);
		if (FAILED(hr))
			_com_issue_error (hr);
	}
	
//	Zeiger auf Geometrie holen
	hr = Object.m_wIObjGeo -> GetX ((VOID **)ppX);
	if (FAILED(hr))
		_com_issue_error (hr);
	
	hr = Object.m_wIObjGeo -> GetY ((VOID **)ppY);
	if (FAILED(hr))
		_com_issue_error (hr);

//	ggf. Konturfeld holen
	if (NULL != lppCnt)
	{
		hr = Object.m_wIObjGeo -> GetLPCnt (lppCnt);
		if (FAILED(hr))
			_com_issue_error (hr);
	}
}

// lese zu vergleichende Geometrie
void CCompareObjects :: Init (CGeometrieObject &Object, BOOL bIsFlaeche)
{
	GetGeometrie (Object, &m_pX, &m_pY, &m_lCnt, bIsFlaeche ? &m_sKCnt : NULL,
				  bIsFlaeche ? &m_lpCnt : NULL);
	ASSERT ((m_lCnt > 0) && (NULL != m_pX) && (NULL != m_pY));
	
	m_bIsFlaeche = bIsFlaeche;

	if (!bIsFlaeche)
	{
		m_sKCnt = 0;
		m_lpCnt = NULL;
	}	
}

// Vergleich der Objekte
void CCompareObjects :: operator ()(CGeometrieObject &Object)
{
//	nur Vergleich mit noch nicht geprüften durchführen
	if (Object.m_bIsDoppelt)
		return;

	long *pX = NULL;
	long *pY = NULL;
	long *lpCnt = NULL;
	long lCnt = 0;
	short sKCnt = 0;

//	lese Geometrie des neuen Objektes
	GetGeometrie (Object, &pX, &pY, &lCnt, m_bIsFlaeche ? &sKCnt : NULL,
				  m_bIsFlaeche ? &lpCnt : NULL);
	ASSERT ((lCnt > 0) && (NULL != pX) && (NULL != pY)) ;

//	prüfe Parameter des alten
	ASSERT ((m_lCnt > 0) && (NULL != m_pX) && (NULL != m_pY)) ;

//	führe Vergleich durch
	if (lCnt != m_lCnt)
		return;

//	vergleiche Stützpunktfolgen
	if (0 != memcmp (pX, m_pX, sizeof (long) * m_lCnt))
		return;

	if (0 != memcmp (pY, m_pY, sizeof (long) * m_lCnt))
		return;

//	bei Flächen noch diesen Vergleich
	if (m_bIsFlaeche)
	{
		ASSERT ((sKCnt > 0) && (m_sKCnt > 0));
		if (sKCnt != m_sKCnt)
			return;

		ASSERT ((NULL != m_lpCnt) && (NULL != lpCnt));
		if (0 != memcmp (lpCnt, m_lpCnt, sizeof (long) * m_sKCnt))
			return;
	}

//	speichere Objektnummer im Ausgabestrom
	ASSERT (NULL != m_pIEnumObjs);
	m_pIEnumObjs -> AddItem (Object.GetObjNummer ());
	Object.m_bIsDoppelt = TRUE;
}

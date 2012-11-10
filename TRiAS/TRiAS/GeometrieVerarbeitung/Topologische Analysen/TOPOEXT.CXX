// Definition des Interface für die Erweiterung "Topologische Relationen"
// File: TopoExt.cxx


#include "TopoRelP.hxx"

#include "ObjGExt.hxx"		// CreateInterfaceOG()
#include "GeoTrias.hxx"		// EFlaecheErzeugen()

#include "TopoRel.hxx"		// TopoRelatExtension


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// --------------------------------------------------------------------------------------------
// IExtendTopRel2-Methoden
// Topologische TRiAS-Relation zwischen dem lONr1-Bezugsobjekt und einem weiteren lONr2-Objekt
STDMETHODIMP_(HRESULT) TopoRelatExtension :: TopoRelationObjObj_ONr (LONG lONr1, LONG lONr2,
																	 Relat* prTR)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

ErrInstall EI (WC_MESSAGE_TOPO);	// keine Anzeige der Fehlermeldung WC_MESSAGE_TOPO

	return m_pTRF->RelationObjObj_ONr (lONr1, lONr2, prTR);
}


// --------------------------------------------------------------------------------------------
// Topologische TRiAS-Relation zwischen dem Bezugsobjekt pIOG1 und einem weiteren Objekt pIOG2
STDMETHODIMP_(HRESULT) TopoRelatExtension :: TopoRelationObjObj_Geom (IObjektGeometrie* pIOG1,
														  IObjektGeometrie* pIOG2, Relat* prTR)
{
	_ASSERTE (pIOG1 != 0);
	_ASSERTE (pIOG2 != 0);

ErrInstall EI (WC_MESSAGE_TOPO);	// keine Anzeige der Fehlermeldung WC_MESSAGE_TOPO

	return m_pTRF->RelationObjObj_Geom (pIOG1, pIOG2, prTR);
}


// --------------------------------------------------------------------------------------------
// Rückgabe aller Objekte, die zu dem lONr-Bezugsobjekt eine in relTR vorgegebene Relation
// besitzen
STDMETHODIMP_(HRESULT) TopoRelatExtension :: GetObjectsObj_ONr (LONG lONr, Relat relTR,
															    IEnumLONG** ppEnumOut)
{
	if (NULL == ppEnumOut)
		return E_POINTER;

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ErrInstall EI (WC_MESSAGE_TOPO);	// keine Anzeige der Fehlermeldung WC_MESSAGE_TOPO

	return m_pTRF->RelatObjekte_ONr (lONr, relTR, ppEnumOut);
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(HRESULT) TopoRelatExtension :: GetObjectsObj_Geom (IObjektGeometrie* pIOG,
															Relat relTR, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Rückgabe eines Punktes, der garantiert innerhalb des lONr-Objekt liegt
STDMETHODIMP_(HRESULT) TopoRelatExtension :: GetPointInsideArea_ONr (LONG lONr, double* pdInX,
																	 double* pdInY)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

	if (OT_FLAECHE != DEX_GetObjectType (lONr))
		return E_UNEXPECTED;

WObjektGeometrie wObj;

	THROW_FAILED_HRESULT (CreateInterfaceOG (wObj.ppi(), lONr));

	return GetPointInsideArea_Geom (wObj, pdInX, pdInY);
}


// --------------------------------------------------------------------------------------------
// Rückgabe eines Punktes, der garantiert innerhalb des pIOG-Objekt liegt
STDMETHODIMP_(HRESULT) TopoRelatExtension :: GetPointInsideArea_Geom (IObjektGeometrie* pIOG,
																  double* pdInX, double* pdInY)
{
	_ASSERTE (0 != pIOG);

short iOT;

	pIOG->GetObjTyp (&iOT);
	if (OT_FLAECHE != iOT)
		return E_UNEXPECTED;

short iKCnt;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pIOG->GetKCnt (&iKCnt);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetLPCnt (&plCnt);

EFlaeche* pFl = EFlaecheErzeugen (iKCnt, plXK, plYK, plCnt);

	if (pFl->InneliegenderPunkt (*pdInX, *pdInY))
		return S_OK;
	return E_FAIL;
}


// --------------------------------------------------------------------------------------------
// Topologische TRiAS- und OGC-Relationen zwischen dem lONr1-Bezugsobjekt und einem weiteren
// lONr2-Objekt
STDMETHODIMP_(HRESULT) TopoRelatExtension :: TopoRelationObjObj2_ONr (LONG lONr1, LONG lONr2,
																	  UINT* puiTR)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

ErrInstall EI (WC_MESSAGE_TOPO);	// keine Anzeige der Fehlermeldung WC_MESSAGE_TOPO

	return m_pTRF->RelationObjObj2_ONr (lONr1, lONr2, puiTR);
}


// --------------------------------------------------------------------------------------------
// Topologische TRiAS- und OGC-Relationen zwischen dem Bezugsobjekt pIOG1 und einem weiteren
// Objekt pIOG2
STDMETHODIMP_(HRESULT) TopoRelatExtension :: TopoRelationObjObj2_Geom (IObjektGeometrie* pIOG1,
														  IObjektGeometrie* pIOG2, UINT* puiTR)
{
	_ASSERTE (pIOG1 != 0);
	_ASSERTE (pIOG2 != 0);

ErrInstall EI (WC_MESSAGE_TOPO);	// keine Anzeige der Fehlermeldung WC_MESSAGE_TOPO

	return m_pTRF->RelationObjObj2_Geom (pIOG1, pIOG2, puiTR);
}

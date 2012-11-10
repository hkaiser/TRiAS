// Lesen der Geometrie eines DB-Objektes --------------------------------------
// File: DBOGETGI.CXX

#include "triaspre.hxx"

#include <Ciid.h>
#include <konsobj.hxx>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <VisInfo.h>
#include <Array.h>			// CSafeArray
#include <NativeView.h>		// CNativeView
#include <Palette.hxx>
#include <funcs03.h>

#include <CSRectGeom.h>
#include <CSTextPointGeom.h>

#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>

#include <dbmsg.hmc>
//#include <TDBGeo_i.c>		// TDBGeo-Guid's
#include <Helper.h>
//#include <Helper_i.c>

#include "TRiASUtil.h"

EXTERN_C const IID IID_IRawVisInfo = {0x4BAB20A3,0xA922,0x11D1,{0x85,0x88,0x00,0x60,0x08,0x75,0x13,0x8A}};
EXTERN_C const CLSID CLSID_DefaultVisInfo = {0x289BE0C4,0x92F6,0x11D1,{0xBA,0x03,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const CLSID CLSID_PointVisInfo = {0x0796385D,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
EXTERN_C const CLSID CLSID_LineVisInfo = {0x0796385F,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
EXTERN_C const CLSID CLSID_AreaVisInfo = {0x07963861,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
EXTERN_C const CLSID CLSID_TextVisInfo = {0x07963863,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
EXTERN_C const CLSID CLSID_CookieHelper = {0xBED66F3A,0x7351,0x11D2,{0x9E,0xF1,0x00,0x60,0x08,0x44,0x78,0x00}};

#include "Strings.h"
#include "drw_obj1.hxx"
#include "schrift.hxx"
#include "relobj.hxx"
#include "minitpbd.hxx"
#include "ExtMain3.hxx"

#include "triasres.h"

extern HPALETTE hPalette;				// derzeit aktive Palette des IrisWind
#if defined(_USE_LEGACY_CODE)
extern DWORD g_dwMenu;					// Menu selbst behandeln
#endif // defined(_USE_LEGACY_CODE)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
using namespace trias_nativeview;
OBJECTTYPE VisTypeToOBJECTTYPE (CNativeView::VisType rgType);
VISINFOTYPE VisTypeToVISINFOTYPE (CNativeView::VisType rgType);
CNativeView::VisType OBJECTTYPEToVisType (OBJECTTYPE rgType);
DWORD OBJECTTYPEToBits (OBJECTTYPE rgType);

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASRelations);	// WTRiASRelations
DefineSmartInterface(TRiASViews);		// WTRiASViews
DefineSmartInterface(TRiASView);		// WTRiASView
DefineSmartInterface(TRiASViewItems);	// WTRiASViewItems
DefineSmartInterface(TRiASViewItem);	// WTRiASViewItem 
DefineSmartInterface(EnumVARIANT);		// WEnumVARIANT
DefineSmartInterface(RawVisInfo);		// WRawVisInfo
DefineSmartInterface2(DVisInfo, IID_DVisInfo);		// WDVisInfo
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASFeature);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(Dispatch);
DefineSmartInterface2(_DGMTextPointGeometry, IID__DGMTextPointGeometry);		// W_DGMTextPointGeometry
DefineSmartInterface(TRiASObjectsCollection);
DefineSmartInterface(TRiASCSGeometryProperties);
DefineSmartInterface2(_DGMGeometryCollection, IID__DGMGeometryCollection);
DefineSmartInterface(TRiASObjectsOperations);
DefineSmartInterface(TRiASSearchObjects);
DefineSmartInterface(CookieHelper);

///////////////////////////////////////////////////////////////////////////////
// DatenBasisObjekt::GetGI liest die Geometrie eines DB-Objektes und
// übergibt dem rufenden Programm einen Pointer auf ein 
// DrawObject (PunktObjekt, KantenObjekt, MaschenObjekt oder SchriftObjekt). 
// Bei KomplexObjekten wird die ObjektListe gelesen.
HRESULT DatenBasisObjekt::GetGI (
	long ObjNr, LPCSTR pcGeomName, ExtShapeObjectDCreator &DOC, ExtShapeObject **ppDO, 
	ObjContainer *pOC, INT_PTR lIdent) 
{
	*ppDO = NULL;

GeoObjekt *pDBO = NULL;
HRESULT hr = GetGI (ObjNr, pcGeomName, &pDBO, pOC, lIdent);

	if (S_OK != hr) {
		DELETE_OBJ (pDBO);
		*ppDO = NULL;
		return hr;
	}

// DrawObject bilden
	COM_TRY {
		switch (pDBO -> isA ()) {
		case OT_PUNKT:
//			*ppDO = ContCreate (DOC, PunktObjekt) ((GeoPunkt &)(*(GeoPunkt *)pDBO));
			*ppDO = DOC.ItemCreate ((GeoPunkt &)(*(GeoPunkt *)pDBO), (PunktObjekt *)NULL);
			break;

		case OT_KANTE:
//			*ppDO = ContCreate (DOC, KantenObjekt) ((GeoKante &)(*(GeoKante *)pDBO));
			*ppDO = DOC.ItemCreate ((GeoKante &)(*(GeoKante *)pDBO), (KantenObjekt *)NULL);
			break;

		case OT_FLAECHE:
//			*ppDO = ContCreate (DOC, MaschenObjekt) ((GeoFlaeche &)(*(GeoFlaeche *)pDBO));
			*ppDO = DOC.ItemCreate ((GeoFlaeche &)(*(GeoFlaeche *)pDBO), (MaschenObjekt *)NULL);
			break;

		case OT_LABEL:
		case OT_TEXT:
//			*ppDO = ContCreate (DOC, SchriftObjekt) ((BasicGeoText &)(*(BasicGeoText *)pDBO));
			*ppDO = DOC.ItemCreate ((BasicGeoText &)(*(BasicGeoText *)pDBO), (SchriftObjekt *)NULL);
			break;

		case OT_KREIS:
			break;

		case OT_KO:
#if defined(_USE_KOMPLEX_OBJECTS)
//			*ppDO = ContCreate (DOC, RelationsObjekt) ((KomplexObjekt &)(*(KomplexObjekt *)pDBO));
			*ppDO = DOC.ItemCreate ((KomplexObjekt &)(*(KomplexObjekt *)pDBO), (RelationsObjekt *)NULL);
			if (*ppDO != NULL) // alle Objekte des KomplexObjektes einlesen
				THROW_FAILED_HRESULT(KOGetGI (*(KomplexObjekt *)pDBO, DOC));
#endif // defined(_USE_KOMPLEX_OBJECTS)
			break;

		case OT_UNKNOWN:
		default:
			break;          // do nothing
		}
	} COM_CATCH;
	return (NULL != *ppDO) ? S_OK : E_OUTOFMEMORY;
}

OBJECTTYPE OBJECTTYPEFromGEOMETRYTYPE (GEOMETRYTYPE rgType)
{
	switch (rgType) {
	case GEOMETRYTYPE_Point:
	case GEOMETRYTYPE_OrientedPoint:
		return OBJECTTYPE_Point;
	case GEOMETRYTYPE_Line:
		return OBJECTTYPE_Line;
	case GEOMETRYTYPE_Area:
	case GEOMETRYTYPE_Boundary:
		return OBJECTTYPE_Area;
	case GEOMETRYTYPE_Text:
		return OBJECTTYPE_Text;
	default:
		break;
	}
	return OBJECTTYPE_Unknown;
}

HRESULT DatenBasisObjekt::GetGI (
	long lONr, LPCSTR pcGeomName, GeoObjekt **ppGO, ObjContainer *pOC, INT_PTR lIdent)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetGI(lONr, ppGO, pOC);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	HRESULT hr = E_FAIL;

		USES_CONVERSION;
		COM_TRY {
		// Objekt besorgen
		WTRiASObject Obj;			// gesuchtes Objekt
		WTRiASObjects Objs;			// zugehörige Objektklasse		
		HOBJECTS hObjs;
		HPROJECT hPr = NULL;		// zugehöriges Datenbank-Handle

			THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));
			THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
			THROW_FAILED_HRESULT(GetObjectsFromMap ((INT_PTR)hObjs, Objs));

			THROW_FAILED_HRESULT(Obj -> get_DatabaseHandle ((INT_PTR *)&hPr));

		// Feature von zugehöriger Objektklasse geben lassen
		WTRiASFeature Feat;
		CComVariant vGeomName ((NULL != pcGeomName) ? A2OLE(pcGeomName) : g_cbDefaultGeometry);

			THROW_FAILED_HRESULT(Objs -> get_GeometryFeature (vGeomName, VARIANT_FALSE, CComBSTR(g_cbNil), Feat.ppi()));

		// jetzt eigentliches (Geometrie-)Merkmal abfragen
		CComVariant vVal;
		CSafeArray sa (VT_VARIANT, 3);		// enthält 2 Parameter

			{
			CSafeArrayLock<VARIANT> lock(sa);
	
			// der erste optionale Parameter enthält bei der Rückkehr den CS-Guid
				V_VT(&lock[EVALEXPARAM_CoordSysGuid]) = VT_ERROR;
				V_ERROR(&lock[EVALEXPARAM_CoordSysGuid]) = DISP_E_PARAMNOTFOUND;

			// der zweite optionale Parameter enthält evtl. Suchfenster
				if (NULL != pOC) {
#if defined(_KOORD_ISDOUBLE)
				CCSRectangleGeometry rect (pOC -> XMin(), pOC -> YMin(), pOC -> XMax(), pOC -> YMax(), 1);
#else
				double dXMin, dYMin, dXMax, dYMax;

					pCT() -> UnScale (pOC -> XMin(), pOC -> YMin(), &dXMin, &dYMin);
					pCT() -> UnScale (pOC -> XMax(), pOC -> YMax(), &dXMax, &dYMax);

				CCSRectangleGeometry rect (dXMin, dYMin, dXMax-dXMin, dYMax-dYMin);
#endif // _KOORD_ISDOUBLE
				WDispatch dispRect (rect);

					V_VT(&lock[EVALEXPARAM_Window]) = VT_DISPATCH;
					V_DISPATCH(&lock[EVALEXPARAM_Window]) = dispRect.detach();
				} else {
					V_VT(&lock[EVALEXPARAM_Window]) = VT_ERROR;
					V_ERROR(&lock[EVALEXPARAM_Window]) = DISP_E_PARAMNOTFOUND;
				}

			// dritter optionaler Parameter enthält bei Rückkehr evtl. Objektcontainer
				V_VT(&lock[EVALEXPARAM_Envelope]) = VT_ERROR;
				V_ERROR(&lock[EVALEXPARAM_Envelope]) = DISP_E_PARAMNOTFOUND;
			}

		// eigentlicher Aufruf
		SAFEARRAY *psa = sa;
		
			hr = Feat -> EvalEx (Obj, &psa, &vVal);
			if (S_OK != hr) {
				if (SUCCEEDED(hr))		// TRIASDB_S_OBJECTDOESNOTFIT
					return hr;
				THROW_FAILED_HRESULT(hr);
			}
			if (V_VT(&vVal) != (VT_ARRAY|VT_UI1) && V_VT(&vVal) != VT_DISPATCH)
				_com_issue_error(E_UNEXPECTED);		// falsches Datenformat

		// jetzt aus Blob/GeometrieObjekt (_DGMGeometry) und ObjektContainer GeoObjekt erzeugen
		__Interface<ITRiASSimpleRectangle> cont;

			{
			CSafeArrayLock<VARIANT> lock(sa);
			CComVariant vCont;

				if (SUCCEEDED(vCont.ChangeType (VT_DISPATCH, &lock[EVALEXPARAM_Envelope]))) 
					cont = V_DISPATCH(&vCont);
			} 
			THROW_FAILED_HRESULT(hr = GenerateGeoObjekt (DB(hPr), lONr, (0 == lIdent) ? (INT_PTR)hObjs : (INT_PTR)lIdent, vVal, cont, ppGO));

		// dem Objekt für alle Fälle seinen Typ reinreichen
			if (NULL != *ppGO)
				Obj -> put_Type (OBJECTTYPEFromGEOMETRYTYPE((*ppGO) -> GType()));	// keinen fehler auswerden

		} COM_CATCH;
		return hr;
	}
}

namespace {
inline
	HRESULT EnsureEnvelope (IDispatch *pDisp, __Interface<ITRiASSimpleRectangle> &rCont)
	{
		if (!rCont) 
			THROW_FAILED_HRESULT(WTRiASCSGeometryProperties(pDisp) -> get_Envelope(rCont.ppi()));
		return S_OK;
	}
} // namespace

HRESULT DatenBasisObjekt::GenerateGeoObjekt (
	GeoDB &rDB, INT_PTR lONr, INT_PTR lIdent, VARIANT &rvBlobOrObj, 
	_DGMRectangleGeometry *pCont, GeoObjekt **ppGO)
{
HRESULT hr = S_OK;

	COM_TRY {
	// evtl. GeometryObject generieren
	WDispatch disp;
	CComVariant vData;
	GEOMETRYTYPE rgType = GEOMETRYTYPE_Unknown;

		if (SUCCEEDED(vData.ChangeType (VT_DISPATCH, &rvBlobOrObj))) {
		// Objekt ist bereits erzeugt
			disp = V_DISPATCH(&vData);
			THROW_FAILED_HRESULT(hr = RetrieveType (disp, &rgType));
		} else {
		// Objekt eben selbst instantiieren
			TX_ASSERT((VT_ARRAY|VT_UI1) == V_VT(&rvBlobOrObj));
			THROW_FAILED_HRESULT(hr = StorageToGeometry (rvBlobOrObj, &rgType, disp.ppi()));
		}

	// evtl. Container des Objektes berechnen
	__Interface<ITRiASSimpleRectangle> Cont (pCont);

	// DrawObject bilden
		switch (rgType) {
		case GEOMETRYTYPE_Point:
		case GEOMETRYTYPE_OrientedPoint:
			*ppGO = new GeoPunkt(rDB, lONr, lIdent, Punkt(disp));
			break;

		case GEOMETRYTYPE_Line:
			EnsureEnvelope (disp, Cont);		// throws hr
			*ppGO = new GeoKante(rDB, lONr, lIdent, Kante(disp, Cont));
			break;

		case GEOMETRYTYPE_Area:
			EnsureEnvelope (disp, Cont);		// throws hr
			*ppGO = new GeoFlaeche(rDB, lONr, lIdent, Masche(disp, Cont));
			break;

		case GEOMETRYTYPE_Boundary:
			EnsureEnvelope (disp, Cont);		// throws hr
			*ppGO = new GeoFlaeche(rDB, lONr, lIdent, Masche(disp, Cont, true));
			break;

		case GEOMETRYTYPE_Text:
			{
			CCSTextPointGeometry text (disp);
			CComBSTR bstrText;

				USES_CONVERSION;
				text.get_Text (CLEARED(&bstrText));		// Fehler evtl. ignorieren

			LPCSTR pcText = OLE2A(bstrText);
			size_t iLen = strlen(g_cbIndText);

				if (strncmp (pcText, g_cbIndText, iLen))	// "@@" ?
					*ppGO = new GeoText(rDB, lONr, lIdent, Punkt(disp), (LPSTR)pcText);
				else
					*ppGO = new GeoTextIndOP(rDB, lONr, lIdent, Punkt(disp), (LPSTR)pcText+iLen);
			}
			break;

#pragma TODO("Komplexobjekte aus TRiASDB-basierter Datenbank lesen!")
//		case OT_KO:
//			*ppDO = ContCreate (DOC, RelationsObjekt) ((KomplexObjekt &)(*(KomplexObjekt *)pDBO));
//			if (*ppDO != NULL) // alle Objekte des KomplexObjektes einlesen
//				THROW_FAILED_HRESULT(KOGetGI (*(KomplexObjekt *)pDBO, DOC));
//			break;

		case GEOMETRYTYPE_Collection:
			{
			// erstes Element der Collection rekursiv erzeugen
			W_DGMGeometryCollection Coll (disp);
			long lCnt = 0;

				THROW_FAILED_HRESULT(Coll -> get_Count (&lCnt));
				TX_ASSERT(1 <= lCnt);

			WDispatch element;
			
				THROW_FAILED_HRESULT(Coll -> Item (CComVariant(1), element.ppi()));
				THROW_FAILED_HRESULT(hr = GenerateGeoObjekt (rDB, lONr, lIdent, CComVariant(element), pCont, ppGO));

				if (1 < lCnt) {
#pragma TODO("Nachdenken, was mit GeometryCollection-Objekten weiter zu tun ist!")
//					TX_ASSERT(1 < lCnt);
//					hr = S_FALSE;
					;
				}
			}
			break;

		case GEOMETRYTYPE_Unknown:
		default:
			hr = S_FALSE;
			break;          // do nothing
		}
	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Geometrie schreiben
ObjTyp OBJECTTYPEToObjTyp (OBJECTTYPE rgType)
{
ObjTyp rgResult = OT_UNKNOWN;

	if (rgType & OBJECTTYPE_Point) 
		rgResult = OT_PUNKT;
	if (rgType & OBJECTTYPE_Line)
		rgResult = OT_KANTE;
	if (rgType & OBJECTTYPE_Area)
		rgResult = OT_FLAECHE;
	if (rgType & OBJECTTYPE_Text)
		rgResult = OT_TEXT;
	if (rgType & OBJECTTYPE_Complex)
		rgResult = OT_KO;

	return rgResult;
}

HRESULT DatenBasisObjekt::PutGI (GeoObjekt *pGO, bool fNewOType)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().PutGI(pGO);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Objekt besorgen
		WTRiASObject Obj;			// gesuchtes Objekt
		WTRiASObjects Objs;			// zugehörige Objektklasse		
		HOBJECTS hObjs = NULL;

			THROW_FAILED_HRESULT(GetObjectFromMap (pGO -> GetONr(), Obj));
			THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
			THROW_FAILED_HRESULT(GetObjectsFromMap ((INT_PTR)hObjs, Objs));

		OBJECTTYPE rgType = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(Obj -> get_Type (&rgType));

		// Feature von zugehöriger Objektklasse geben lassen
		WTRiASFeature Feat;

			THROW_FAILED_HRESULT(Objs -> get_GeometryFeature (CComVariant(g_cbDefaultGeometry), VARIANT_FALSE, CComBSTR(g_cbNil), Feat.ppi()));

		VARIANT_BOOL fUpdatable = VARIANT_TRUE;

			THROW_FAILED_HRESULT(Feat -> get_Updatable (&fUpdatable));
			if (!fUpdatable) {
				SetLastError (HRESULT_FROM_ERRCODE(WC_FEATURE_ISRO));
				return HRESULT_FROM_ERRCODE(WC_FEATURE_ISRO);
			}

		// Geometrie besorgen und in Blob konvertieren
		WDispatch Geom (pGO -> GetGeometry());

			if (!Geom.IsValid()) _com_issue_error(E_INVALIDARG);		// Objekttyp falsch

		// Geometrie wegschreiben
		CComVariant vVal (Geom);

//			THROW_FAILED_HRESULT(GeometryToStorage(pGO -> GType(), Geom, &vVal));
//			TX_ASSERT(V_VT(&vVal) == (VT_ARRAY|VT_UI1));
		
			THROW_FAILED_HRESULT(Feat -> Update (Obj, vVal));

		// wenn der Objekttyp bisher nicht bekannt war, dann den Objektzähler im Identifikator richten
			if (OBJECTTYPE_Unknown == rgType) {
				THROW_FAILED_HRESULT(Obj -> get_Type (&rgType));
				Idents().IncrementObjectCount (pGO -> Id(), OBJECTTYPEToObjTyp(rgType), pGO -> ObjNr());
			}

		} COM_CATCH;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert GeoObjekt zu einer vorgegeben ON 
GeoObjekt *DatenBasisObjekt::GetGeoObj (INT_PTR lONr, INT_PTR lIdent) 
{
	TX_ASSERT(IsValidONr(lONr));

CONrTable t(Shapes().ObjNumTree()); // Navigator für alle Objekte
GeoObjekt *pGO = NULL;

	if (t.Find (&lONr)) {
	ExtShapeObjectONrLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		
		pGO = l -> operator GeoObjekt *();
		
		switch (pGO -> isA()) {
		case OT_PUNKT:   return new GeoPunkt (*(GeoPunkt*)pGO);
		case OT_KANTE:   return new GeoKante (*(GeoKante*)pGO);
		case OT_FLAECHE: return new GeoFlaeche (*(GeoFlaeche*)pGO);
		case OT_LABEL:
		case OT_TEXT:
			{
			TextObjTyp ToTyp = ((BasicGeoText *)pGO) -> isText();

				if (TOT_TEXT == ToTyp)
					return new GeoText (*(GeoText *)pGO);
#if defined(_USE_LEGACY_CODE)
				else if (TOT_TEXTIND == ToTyp)
					return new GeoTextInd (*(GeoTextInd *)pGO);
#endif // defined(_USE_LEGACY_CODE)
				else {
					TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
					return new GeoTextIndOP (*(GeoTextIndOP *)pGO);
				}
			}

		case OT_KREIS:	return new GeoKreis (*(GeoKreis *)pGO);
		case OT_KO:		
#if defined(_USE_KOMPLEX_OBJECTS)
			return new KomplexObjekt (*(KomplexObjekt *)pGO);
#endif // defined(_USE_KOMPLEX_OBJECTS)
		case OT_UNKNOWN:
		default:
			TX_ASSERT(false);
			return NULL;
		}
	} else 
		GetGI (lONr, NULL, &pGO, NULL, lIdent);

	return pGO;
}

// liefert Container zu einer vorgegeben ObjektNummer -------------------------
bool DatenBasisObjekt::GetObjContainer (INT_PTR lONr, ObjContainer &OC, 
	IUnknown *pICS) 
{
CONrTable t(Shapes().ObjNumTree()); // Navigator für alle Objekte
bool fLoaded = false;
GeoObjekt *pGO = NULL;

	if (!t.Find (&lONr)) {		// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	HRESULT hr = GetGI (lONr, NULL, &pGO);

		if (S_OK != hr || pGO == NULL)
			return false;

		fLoaded = true;
	} 
	else {
	ExtShapeObjectONrLock l(t);	// Objekt ist geladen

		if (!l) return false;
		
		pGO = l -> operator GeoObjekt *();
		if ((pGO -> isA() == OT_TEXT || pGO -> isA() == OT_LABEL) && l -> isVisible()) {
		// Texte sofort behandeln, wenn sie angezeigt sind
		Rectangle rcR = l -> BoundingBox();

			OC = rcR;
			if (NULL != pICS) 
				return ConvertObjContainer(OC, pICS);
			return true;
		}
	}
	
// ObjektContainer bestimmen
	switch (pGO -> isA()) {
	case OT_PUNKT:   
	case OT_KANTE:   
	case OT_FLAECHE: 
	case OT_TEXT:		// #HK960116
	case OT_LABEL:		// #HK980602
	case OT_KO:
	case OT_KREIS:
		{
		bool fResult = pGO->GetObjContainer (OC);

			if (fLoaded) 
				DELETE_OBJ (pGO);
			if (NULL != pICS) 
				return ConvertObjContainer(OC, pICS);
			return fResult;
		}

	default:
//	case OT_TEXT:		// #HK960116
	case OT_UNKNOWN:
		break;
	}

// evtl. aufräumen
	if (fLoaded) 
		DELETE_OBJ (pGO);
	return false;
}

// Einlesen der Geometrien aller Objekte des Komplexobjektes ------------------
// (insbesondere der Objekte, die nicht zur aktuellen Sicht gehören)
HRESULT DatenBasisObjekt::KOGetGI (KomplexObjekt &KO, ExtShapeObjectDCreator &DOC)
{
#if defined(_USE_KOMPLEX_OBJECTS)
ObjektListeIterator KOI (KO.OL()); 
CTable t (Idents().IdentTree());
long ONr = KOI.FirstONr();
ExtShapeObject *pESO;

	while (ONr != -1L) {
	long Ident = RetrieveIdent (ONr);	// Ident besorgen

		if (t.Find (&Ident)) {
		CIdentifikatorLock l(t);

			if (l && !(l -> toPaint() & l -> GetOTypes())) {
			// wenn Ident normalerweise nicht geladen werden soll

				RETURN_FAILED_HRESULT(GetGI (ONr, NULL, DOC, &pESO, NULL, Ident));
			}
		}
		ONr = KOI.NextONr();	// nächstes Objekt holen
	}
#endif // defined(_USE_KOMPLEX_OBJECTS)
	return S_OK;
}

// Liefern einiger Objekteigenschaften über die Schnittstelle -----------------
bool DatenBasisObjekt::QueryObjStatistik (HPROJECT hPr, OBJSTATISTIK *pSt)
{
	if (HACTCONNECTION != hPr && !IsValidConnection(hPr))
		return false;

CONrTable t (Shapes().ObjNumTree());
GeoObjekt *pGO = NULL;
bool iLoaded = false;
GeoDB &rDB = DB (GetObjectDBHandle (pSt -> lONr, hPr));

	if (!t.Find (&pSt -> lONr)) {	// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	HRESULT hr = GetGI (pSt -> lONr, NULL, &pGO, NULL, pSt -> lIdent);

		if (S_OK != hr)
			return false;
		if (pGO == NULL) 
			return false;

//		_ASSERT(0 == pSt -> lIdent || pSt -> lIdent == pGO -> Id());
		pSt -> lIdent = pGO -> Id();
		iLoaded = true;
	} else {	// Objekt suchen
	// Objekt ist derzeit geladen
	ExtShapeObjectONrLock l(t);

		if (!l) return false;

//		_ASSERT(0 == pSt -> lIdent || pSt -> lIdent == l -> Id());
		pSt -> lIdent = l -> Id();	// Identifikator
//		pGO = l -> operator GeoObjekt *();
		pGO = *l;
	}

	pSt -> lCnt = 0;
	pSt -> iKCnt = 0;

	switch (pSt -> iObjTyp = pGO -> isA()) {
	case OT_PUNKT:
	// nur eine Koordinate
		pSt -> lCnt = 1;
		break;

	case OT_LABEL:
	case OT_TEXT:
	// nur eine Koordinate
		pSt -> lCnt = 1;
		pSt -> iKCnt = strlen (((BasicGeoText *)pGO) -> TextBase()) +1;
		break;

	case OT_KANTE:
	// Anzahl der Stützpunkte
		pSt -> lCnt = ((GeoKante *)pGO) -> ASP();
		break;

	case OT_FLAECHE:
	// Anzahl der Konturen
		pSt -> iKCnt = ((GeoFlaeche *)pGO) -> KantenAnz();
	// Gesamtanzahl der Stützpunkte
		pSt -> lCnt = ((GeoFlaeche *)pGO) -> ASP();
		break;

	case OT_KREIS:
		pSt -> lCnt = 2;
		break;

	case OT_KO:
	// Anzahl der Teilobjekte liefern
#if defined(_USE_KOMPLEX_OBJECTS)
		pSt -> lCnt = (long)((KomplexObjekt *)pGO) -> OL().Count();
#else
		pSt -> lCnt = 1;
#endif // defined(_USE_KOMPLEX_OBJECTS)
		break;

	case OT_UNKNOWN:
	default:
		if (iLoaded) DELETE_OBJ (pGO);
	        return false;
	}

// Aufräumarbeiten
	if (iLoaded) DELETE_OBJ (pGO);
	return true;
}

// Geometrie über Schnittstelle liefern ---------------------------------------
bool DatenBasisObjekt::QueryObjGeometrie (HPROJECT hPr, OBJGEOMETRIE *pGS, IUnknown *pICS)
{
	if (NULL == pCT() || (HACTCONNECTION != hPr && !IsValidConnection(hPr)))
		return false;

CONrTable t (Shapes().ObjNumTree());
GeoDB &rDB = DB (GetObjectDBHandle (pGS -> lONr, hPr));

	if (!t.Find (&pGS -> lONr)) {	// Objekt suchen
	// nicht gefunden, Objekt ist offensichtlich nicht geladen
	GeoObjekt *pGO;
	HRESULT hr = GetGI (pGS -> lONr, NULL, &pGO, NULL, pGS -> lIdent);		// pGS -> lIdent darf NULL sein

		if (S_OK != hr)	return false;

	bool fRC = RetrieveGeometrie (pGO, pGS, pCT(), pICS);

		if ((pGS -> dwSize == sizeof(TEXTGEOMETRIE) || pGS -> dwSize == sizeof(TEXTGEOMETRIEEX)) && 
			(pGS -> iObjTyp == OT_TEXT || pGS -> iObjTyp == OT_LABEL))
		{
		// Text mit kopieren
		char *pDest = ((TEXTGEOMETRIE *)pGS) -> pText;
		int iLen = strlen(((BasicGeoText *)pGO) -> TextBase());
		int iToCopy = min(pGS -> iKCnt-1, iLen);
			
			if (iLen > 0 && pDest) {
				strncpy (pDest, ((BasicGeoText *)pGO) -> TextBase(), iToCopy);
				pDest[iToCopy] = '\0';
			}
			if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
				((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp = (pGS -> iObjTyp == OT_LABEL) ? TRUE : FALSE;
		}
		DELETE_OBJ (pGO);
		return fRC;
	} 
	else {
	// Objekt ist derzeit geladen
	ExtShapeObjectONrLock l(t);

		if (l) {
		GeoObjekt *pGO = l -> operator GeoObjekt *();
		bool iResult = RetrieveGeometrie (pGO, pGS, pCT(), pICS);
		
			if ((pGS -> dwSize == sizeof(TEXTGEOMETRIE) || pGS -> dwSize == sizeof(TEXTGEOMETRIEEX)) && 
				(pGS -> iObjTyp == OT_TEXT || pGS -> iObjTyp == OT_LABEL))
			{
			// Text mit kopieren
			char *pDest = ((TEXTGEOMETRIE *)pGS) -> pText;
			int iLen = strlen(((BasicGeoText *)pGO) -> TextBase());
			int iToCopy = min(pGS -> iKCnt-1, iLen);
			
				if (iLen > 0 && pDest) {
					strncpy (pDest, ((BasicGeoText *)pGO) -> TextBase(), iToCopy);
					pDest[iToCopy] = '\0';
				}
				if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
					((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp = (pGS -> iObjTyp == OT_LABEL) ? TRUE : FALSE;
			}
			return iResult;
		}
	}
	return false;
}

bool ConvertCoords (KoOrd *, KoOrd *, OBJGEOMETRIE *, CoordTrans *, IUnknown *pICS, bool = true);
bool CopyCoords (KoOrd *, KoOrd *, OBJGEOMETRIE *, CoordTrans *);

bool DatenBasisObjekt::RetrieveGeometrie (
	GeoObjekt *pGO, OBJGEOMETRIE *pGS, CoordTrans *pCT, IUnknown *pICS)
{
bool iRC = false;
KoOrd *x = NULL, *y = NULL;
long *KCnt = NULL;

	pGS -> lIdent = pGO -> Id();
	pGS -> lONr = pGO -> ObjNr();

	if (!pGO -> RetrievePureGeometrie (&x, &y, &KCnt)) {
	// Speicher wieder freigeben
		DELETE_OBJ(x);
		DELETE_OBJ(y);
		DELETE_OBJ(KCnt);
		return false;
	}

	if ((pGS -> iObjTyp = pGO -> isA()) == OT_FLAECHE) {
		for (long i = 0; i < pGS -> iKCnt; i++)
			pGS -> plCnt[i] = KCnt[i];
	}

// Geometrie konvertieren
	if (pGS -> iFlags & OGConverted)	// konvertierte doubleKoordinaten 
		iRC = ConvertCoords (x, y, pGS, pCT, pICS);
	else								// !konvertierte longKoordinaten
		iRC = CopyCoords (x, y, pGS, pCT);

// Speicher wieder freigeben
	DELETE_OBJ(x);
	DELETE_OBJ(y);
	DELETE_OBJ(KCnt);
	return iRC;
}

// Konvertieren eines Koordinatenfeldes ---------------------------------------
#if !defined(WIN16)
inline 
bool ConvertRCToOCEx (CoordTrans *pCT, double dX, double dY, KoOrd &rlX, 
	KoOrd &rlY, LPVOID pData, IUnknown *pICS = NULL, bool fScale = false)
{
	if (!pCT -> InvTransformEx (&dX, &dY, pData, pICS)) 
		return false;

#if defined(_KOORD_ISDOUBLE)
	if (fScale) 
		return pCT -> Scale (dX, dY, &rlX, &rlY);

	rlX = dX;
	rlY = dY;
	return true;
#else
	return pCT -> Scale (dX, dY, &rlX, &rlY);
#endif // _KOORD_ISDOUBLE
}

inline 
bool ConvertOCToRCEx (CoordTrans *pCT, KoOrd lX, KoOrd lY, double &rdX, 
	double &rdY, LPVOID pData, IUnknown *pICS = NULL, bool fUnScale = false)
{
#if !defined(_KOORD_ISDOUBLE)
	if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
		return false;
#else
	if (fUnScale) {
		if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
			return false;
	} else {
		rdX = lX;
		rdY = lY;
	}
#endif // _KOORD_ISDOUBLE
	return pCT -> TransformEx (&rdX, &rdY, pData, pICS);
}
#endif // !WIN16

inline 
bool ConvertRCToOC (CoordTrans *pCT, double dX, double dY, KoOrd &rlX, 
	KoOrd &rlY, bool fScale = false)
{
	if (!pCT -> InvTransform (&dX, &dY)) 
		return false;

#if defined(_KOORD_ISDOUBLE)
	if (fScale) 
		return pCT -> Scale (dX, dY, &rlX, &rlY);

	rlX = dX;
	rlY = dY;
	return true;
#else
	return pCT -> Scale (dX, dY, &rlX, &rlY);
#endif // _KOORD_ISDOUBLE
}

inline 
bool ConvertOCToRC (CoordTrans *pCT, KoOrd lX, KoOrd lY, double &rdX, 
	double &rdY, bool fUnScale = false)
{
#if !defined(_KOORD_ISDOUBLE)
	if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
		return false;
#else
	if (fUnScale) {
		if (!pCT -> UnScale (lX, lY, &rdX, &rdY))
			return false;
	} else {
		rdX = lX;
		rdY = lY;
	}
#endif // _KOORD_ISDOUBLE
	return pCT -> Transform (&rdX, &rdY);
}

bool ConvertCoords (KoOrd *x, KoOrd *y, OBJGEOMETRIE *pGS, CoordTrans *pCT, 
	IUnknown *pICS, bool iFlag)
{
// jede Koordinate konvertieren
	TX_ASSERT(pGS -> lCnt > 0);

LPVOID pData = NULL;
bool fResult = true;

	if (iFlag) {
#if defined(_KOORD_ISDOUBLE)
		*(double *)(pGS -> pdblX) = x[0];
		*(double *)(pGS -> pdblY) = y[0];
#else
		if (!pCT -> UnScale (x[0], y[0], (double *)(pGS -> pdblX), (double *)(pGS -> pdblY)))
			return false;
#endif // _KOORD_ISDOUBLE

		pCT -> GetTransformParam (*(double *)(pGS -> pdblX), *(double *)(pGS -> pdblY), &pData);
		if (!pCT -> TransformEx ((double *)(pGS -> pdblX), (double *)(pGS -> pdblY), pData, pICS)) 
		{
//			if (NULL != pData) CoTaskMemFree (pData);
			pCT -> FreeTransformParam (pData);
			return false;
		}

		for (long i = 1; i < pGS -> lCnt; i++) {
			if (!ConvertOCToRCEx (pCT, x[i], y[i], ((double *)(pGS -> pdblX))[i], 
				((double *)(pGS -> pdblY))[i], pData, pICS)) 
			{
				fResult = false;
				break;
			}
		}
		pCT -> FreeTransformParam (pData);
	} 
	else {
		pCT -> GetInvTransformParam (*(double *)(pGS -> pdblX), *(double *)(pGS -> pdblY), &pData);
		for (long i = 0; i < pGS -> lCnt; i++) {
			if (!ConvertRCToOCEx (pCT, ((double *)(pGS -> pdblX))[i], ((double *)(pGS -> pdblY))[i], 
				x[i], y[i], pData, pICS))
			{
				fResult = false;
				break;
			}
		}
		pCT -> FreeInvTransformParam (pData);
	}
//	if (NULL != pData) CoTaskMemFree (pData);
	return fResult;
}

bool CopyCoords (KoOrd *x, KoOrd *y, OBJGEOMETRIE *pGS, CoordTrans *pCT)
{
#if defined(_KOORD_ISDOUBLE)
// hier ist die einzige Stelle, wo Koordinaten aus 'internen' double Koordinaten
// in 'externe ' long Koordinaten umgesetzt werden
KoOrd X, Y;

	for (long i = 0; i < pGS -> lCnt; i++) {
		if (!pCT -> Scale (x[i], y[i], &X, &Y))
			return false;
		((long *)(pGS -> pdblX))[i] = ToCoOrd(X);
		((long *)(pGS -> pdblY))[i] = ToCoOrd(Y);
	}
#else
// Koordinaten lediglich umkopieren
	for (long i = 0; i < pGS -> lCnt; i++) {
		((KoOrd *)(pGS -> pdblX))[i] = x[i];
		((KoOrd *)(pGS -> pdblY))[i] = y[i];
	}
#endif // _KOORD_ISDOUBLE

	return true;
}

bool DatenBasisObjekt::ConvertObjContainer (ObjContainer &rOC, IUnknown *pICS)
{
CoordTrans *pCTF = pCT();
ObjContainer OC;
KoOrd dX, dY;

#if defined(_KOORD_ISDOUBLE)
	dX = rOC.XMin();
	dY = rOC.YMin();
#else
	if (!pCTF -> UnScale (rOC.XMin(), rOC.YMin(), dX, dY))
		return false;
#endif // _KOORD_ISDOUBLE
void *pData = NULL;

	pCTF -> GetTransformParam (dX, dY, &pData);
	if (!pCTF -> TransformEx (&dX, &dY, pData, pICS)) {
		pCTF -> FreeTransformParam (pData);
		return false;
	}
	OC.SetXMin(dX);
	OC.SetYMin(dY);
	 
	if (!::ConvertOCToRCEx (pCTF, rOC.XMax(), rOC.YMax(), dX, dY, pData, pICS)) {
		pCTF -> FreeTransformParam (pData);
		return false;
	}
	pCTF -> FreeTransformParam (pData);

	OC.SetXMax(dX);
	OC.SetYMax(dY);

	rOC = OC;
	return true;
}

#if !defined(WIN16)
//////////////////////////////////////////////////////////////////////////////
// Koordinatentransformationen
bool DatenBasisObjekt::ConvertRCToOC (double dX, double dY, KoOrd &rlX, 
	KoOrd &rlY, bool fScale)
{
	return ::ConvertRCToOC (pCT(), dX, dY, rlX, rlY, fScale);
}

bool DatenBasisObjekt::ConvertOCToRC (KoOrd lX, KoOrd lY, double &rdX, 
	double &rdY, bool fUnScale)
{
	return ::ConvertOCToRC (pCT(), lX, lY, rdX, rdY, fUnScale);
}

bool DatenBasisObjekt::ConvertRCToOCEx (double dX, double dY, KoOrd &rlX, 
	KoOrd &rlY, LPVOID pData, IUnknown *pICS, bool fScale)
{
	return ::ConvertRCToOCEx (pCT(), dX, dY, rlX, rlY, pData, pICS, fScale);
}

bool DatenBasisObjekt::ConvertOCToRCEx (KoOrd lX, KoOrd lY, double &rdX, 
	double &rdY, LPVOID pData, IUnknown *pICS, bool fUnScale)
{
	return ::ConvertOCToRCEx (pCT(), lX, lY, rdX, rdY, pData, pICS, fUnScale);
}
#endif // !WIN16

#if defined(_FORCE_LEGACY_CODE)
bool DatenBasisObjekt::DeleteObjekt (long lONr, bool fUndo)
{
// wenn ein Textobjekt dranhängt, dann dieses ebenfalls löschen
CActDB ActDB (DB());	// DB aktivieren
bool fDelAssoc = false;
bool fDelObj = !DEXN_DeletingObject (lONr);
short iObjStatus = DEX_GetObjectStatus (lONr);
long lIdent = RetrieveIdent(lONr);
long lAssocId = 0L;
HPROJECT hDB = DB().DBDesc();
ObjTyp rgOTyp = Shapes().RetrieveObjTyp (DB(), lONr);
long AssocTextObj = 0L;

	TX_ASSERT(OT_UNKNOWN != rgOTyp);
#if !defined(_DEBUG)
	if (OT_UNKNOWN == rgOTyp) return false;		// Objekt ist bereits gelöscht
#endif // !_DEBUG

	if (iObjStatus == -1 || !(iObjStatus & OS_Temp)) {
	// Objekte bearbeiten wenn nicht geladen oder nicht temporär
		AssocTextObj = AssociatedTextObjekt (lONr);

	// eigentliches löschen
		if (AssocTextObj != -1) {
			fDelAssoc = true;
			if (DEXN_DeletingObject (AssocTextObj))
				fDelAssoc = false;
		}

	// GeoDB für alle Fälle als modifiziert markieren
		DB().SetDirty (true);

	// jetzt allen sagen, daß es wirklich gelöscht wird
		if (fDelObj)
			DEXN_ObjectToDelete(lONr);

	// wenn nur eines der Objekte gelöscht werden soll, dann Relation lösen
		if ((fDelObj || fDelAssoc) && AssocTextObj != -1L) {
			if ((ErrCode)DelRelation (hDB, lONr, AssocTextObj, 0, BRELA) != EC_OKAY)
				return false;

			if (fUndo) {
			LPUNDOREDODELETEOBJECTRELATION pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteObjectRelation,
							 (LPVOID *)&pIUndo);

				if (SUCCEEDED(hr) && S_OK == pIUndo -> Init (lONr, AssocTextObj, -1, BRELA)) 
				{
					DEX_AddUndoRedo (pIUndo);
				}
				if (pIUndo) pIUndo -> Release();
			}
		}

	// Objekt löschen
		if (fDelObj) {
			if (fUndo) {
				DeleteFeatures (lONr);	// Merkmale mit Undo/Redo löschen
				DeleteRelations (lONr);	// Relationen mit Undo/Redo löschen
			}
			if (((ErrCode)del (hDB, lONr) != EC_OKAY)) 
				return false;
			DecrementObjectCount();		// ein Objekt weniger
		}

	// vormals abhängiges Textobjekt löschen
		if (fDelAssoc) {
			lAssocId = RetrieveIdent (AssocTextObj);
			DEXN_ObjectToDelete(AssocTextObj);
			if (fUndo) {
				DeleteFeatures (AssocTextObj);	// Merkmale mit Undo/Redo löschen
				DeleteRelations (AssocTextObj);	// Relationen mit Undo/Redo löschen
			}
			if (((ErrCode)del (hDB, AssocTextObj) != EC_OKAY))
				return false;
			DecrementObjectCount();		// ein Objekt weniger
		}
	}

// Objekt(e) aus ObjektBaum und IdentBaum löschen
CTable t (Shapes().ObjIdTree());
bool fResult = false;
GeoDB &rDB = DB(lIdent);

	if (fDelObj) {
		Shapes().DeleteObjekt (lONr);					// keinen Fehler auswerten
		
		if (0 == Idents().DecrementObjectCount (DB(), lIdent, rgOTyp, lONr)) {	// war's der letzte mit diesem Ident (im Speicher)
		short iOTypes = 0;

			if (!Idents().FindId (rDB, lIdent, NULL, &iOTypes) || 
				0 == (iOTypes & OTypToBits(rgOTyp)))
			{
				Idents().DeleteIdent (lIdent, OTypToVTyp(rgOTyp));
			}
		}
		DEXN_ObjectDeleted (lONr);
		fResult = true;
	}

	if (fDelAssoc && -1L != AssocTextObj) {
		Shapes().DeleteObjekt (AssocTextObj);
		
		if (0 == Idents().DecrementObjectCount (DB(), lIdent, OT_TEXT, AssocTextObj)) 
		{
		short iOTypes = 0;

			if (!Idents().FindId (rDB, lAssocId, NULL, &iOTypes) || 
				0 == (iOTypes & TPText))
			{
				Idents().DeleteIdent (lAssocId, VT_Text);
			}
		}
		DEXN_ObjectDeleted (lAssocObj);
		fResult = true;
	}
	return true;
}
#else
bool DatenBasisObjekt::DeleteObjekt (INT_PTR lONr, bool fUndo)
{
// wenn ein Textobjekt dranhängt, dann dieses ebenfalls löschen
bool fDelObj = !DEXN_DeletingObject (lONr);
bool fDelAssoc = false;
long lIdent = RetrieveIdent(lONr, true);
long lAssocId = 0L;
long lAssocTextObj = 0L;

HPROJECT hDB = GetObjectDBHandle(lONr);
GeoDB &rDB = DB(hDB);
ObjTyp rgOTyp = Shapes().RetrieveObjTyp (rDB, lONr);
short iObjStatus = DEX_GetObjectStatus (lONr);
HRESULT hr = S_OK;

	TX_ASSERT(OT_UNKNOWN != rgOTyp);
#if !defined(_DEBUG)
	if (OT_UNKNOWN == rgOTyp) {
		SetLastError (E_UNEXPECTED);
		return false;		// Objekt ist bereits gelöscht
	}
#endif // !_DEBUG

	if (iObjStatus == -1 || !(iObjStatus & OS_Temp)) {
	// Objekte bearbeiten wenn nicht geladen oder nicht temporär
		lAssocTextObj = AssociatedTextObjekt (lONr);

	// eigentliches löschen
		if (-1L != lAssocTextObj) {
			fDelAssoc = true;
			if (DEXN_DeletingObject (lAssocTextObj))
				fDelAssoc = false;
		}

	// jetzt allen sagen, daß es wirklich gelöscht wird
		if (fDelObj)
			DEXN_ObjectToDelete(lONr);

	// wenn nur eines der Objekte gelöscht werden soll, dann Relation lösen
		if ((fDelObj || fDelAssoc) && (-1L != lAssocTextObj)) {
		DELRELATIONEX DR;

			INITSTRUCT(DR, DELRELATIONEX);
			DR.lPONr = lONr;
			DR.lSONr = lAssocTextObj;
			DR.lRCode = 0;
			DR.iRTyp = RTBegleitO;
			DR.fUndo = fUndo;
			if (EC_OKAY != DEX_DeleteRelation(DR)) {
				SetLastError (E_UNEXPECTED);
				return false;
			}
		}

	// Objekt löschen
		if (fDelObj) {
			if (fUndo) {
				DeleteFeatures (lONr);	// Merkmale mit Undo/Redo löschen
				DeleteRelations (lONr);	// Relationen mit Undo/Redo löschen
			}

			if (FAILED(hr = rDB.DeleteObject (lONr))) {
				SetLastError (hr);
				return false;
			}
			DecrementObjectCount();		// ein Objekt weniger
		}

	// vormals abhängiges Textobjekt löschen
		if (fDelAssoc) {
			DEX_DeleteObjectEx (lAssocTextObj);		// Undo sauber verschachteln

//			lAssocId = RetrieveIdent (lAssocTextObj, true);
//			DEXN_ObjectToDelete(lAssocTextObj);
//			if (fUndo) {
//				DeleteFeatures (lAssocTextObj);	// Merkmale mit Undo/Redo löschen
//				DeleteRelations (lAssocTextObj);	// Relationen mit Undo/Redo löschen
//			}
//			if (FAILED(hr = rDB.DeleteObject (lAssocTextObj))) {
//				SetLastError (hr);
//				return false;
//			}
//			DecrementObjectCount();		// ein Objekt weniger
		}
	}

// Objekt(e) aus ObjektBaum und IdentBaum löschen
CIdentTable t (Shapes().ObjIdTree());
bool fResult = false;

	if (fDelObj) {
		Shapes().DeleteObjekt (lONr);					// keinen Fehler auswerten
		if (0 == Idents().DecrementObjectCount (lIdent, rgOTyp, lONr)) {	// war's der letzte mit diesem Ident (im Speicher)
		short iOTypes = 0;

			if (!Idents().FindId (lIdent, NULL, &iOTypes) || 0 == (iOTypes & OTypToBits(rgOTyp)))
				Idents().DeleteIdent (lIdent, OTypToVTyp(rgOTyp));
		}
		DEXN_ObjectDeleted (lONr);
		fResult = true;
		SetLastError (S_OK);
	}

// jetzt auch Infos zu abhängigem Objekt nachziehen
//	if (fDelAssoc) {
//		TX_ASSERT(0L != lAssocTextObj);
//		Shapes().DeleteObjekt (lAssocTextObj);
//		if (0 == Idents().DecrementObjectCount (lAssocId, OT_TEXT, lAssocTextObj)) {
//		short iOTypes = 0;
//
//			if (!Idents().FindId (lAssocId, NULL, &iOTypes) || 0 == (iOTypes & TPText))
//				Idents().DeleteIdent (lAssocId, VT_Text);
//		}
//		DEXN_ObjectDeleted (lAssocTextObj);
//		fResult = true;
//		SetLastError (S_OK);
//	}
	return fResult;
}
#endif // _FORCE_LEGACY_CODE

// Feststellen des Objekttyps eines Objektes ----------------------------------
ObjTyp DatenBasisObjekt::RetrieveObjTyp (long lONr)
{
	TX_ASSERT(IsValidONr(lONr));
	return Shapes().RetrieveObjTyp (DB (GetObjectDBHandle(lONr)), lONr);
}

// Temporäres Einfügen eines Objektes in den Objektbaum -----------------------
long DatenBasisObjekt::PutGeoObj (GeoObjekt *pGO, short iFlags)
{
// DrawObject bilden
ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pESO = NULL;
short iTemp = 0;

	if (iFlags & OGTempObject) iTemp |= ANI_Temp;
	if (iFlags & OGAddToView) iTemp |= ANI_AddToView;

	switch (pGO -> isA()) {
	case OT_PUNKT:
		AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_PUNKT);	
//		pESO = ContCreate (DOC, PunktObjekt) (*(GeoPunkt *)pGO);
		pESO = DOC.ItemCreate (*(GeoPunkt *)pGO, (PunktObjekt *)NULL);
		break;

	case OT_KANTE:
		AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_LINIE);	
		pESO = DOC.ItemCreate (*(GeoKante *)pGO, (KantenObjekt *)NULL);
		break;

	case OT_FLAECHE:
		AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_FLAECHE);	
		pESO = DOC.ItemCreate (*(GeoFlaeche *)pGO, (MaschenObjekt *)NULL);
		break;

	case OT_LABEL:
	case OT_TEXT:
		{
		TextObjTyp ToTyp = ((BasicGeoText *)pGO) -> isText();

			AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_TEXT);	
			if (TOT_TEXT == ToTyp)
				pESO = DOC.ItemCreate (*(GeoText *)pGO, (SchriftObjekt *)NULL);
#if defined(_FORCE_LEGACY_CODE)
			else if (TOT_TEXTIND == ToTyp)
				pESO = DOC.ItemCreate (*(GeoTextInd *)pGO, (SchriftObjekt *)NULL);
#endif // defined(_USE_LEGACY_CODE)
			else {
				TX_ASSERT(TOT_TEXTINDOBJPROP == ToTyp);
				pESO = DOC.ItemCreate (*(GeoTextIndOP *)pGO, (SchriftObjekt *)NULL);
			}
		}
		break;

	case OT_KREIS:
		AddNewIdent (pGO -> Id(), hPalette, iTemp, MODIDENT_FLAECHE);	
		pESO = DOC.ItemCreate (*(GeoKreis *)pGO, (KreisObjekt *)NULL);
		break;

	case OT_KO:
	case OT_UNKNOWN:
	default:
		TX_ASSERT(false);
		break;          // do nothing
	}

	if (pESO == NULL) {
		db_error (EC_NOMEMORY, RC_PutGeoObj);
		return -1L;
	}

// Objekt ist temporär
	if (iTemp & ANI_Temp) pESO -> Status() = OS_Temp;

// Einfügen und evtl. Baum Optimieren
	Shapes().CondOptimize (Shapes().TimedInsert(DOC, pGO -> isA()));
	Idents().IncrementObjectCount (pGO -> Id(), pGO -> isA(), pGO -> ObjNr());
	return pGO -> ObjNr();
}

///////////////////////////////////////////////////////////////////////////////
// Neuen Objektsatz erzeugen (noch ohne Geometrie)
OBJECTTYPE ObjTypToOBJECTTYPE (ObjTyp rgType)
{
	switch (rgType) {
	case OT_PUNKT:
		return OBJECTTYPE_Point;

	case OT_KANTE:
		return OBJECTTYPE_Line;

	case OT_FLAECHE:
	case OT_KREIS:
		return OBJECTTYPE_Area;

	case OT_TEXT:
	case OT_LABEL:
		return OBJECTTYPE_Text;

	default:
	case OT_UNKNOWN:
		break;
	}
	return OBJECTTYPE_Unknown;
}

INT_PTR DatenBasisObjekt::CreateObjTemplate (INT_PTR lIdent, int iObjTyp)
{
INT_PTR lONr = -1L;

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Objekt erzeugen
	WTRiASObject Obj;			// neue zu erzeugendes Objekt 
	WTRiASObjects Objs;			// zugehörige Objektklasse		
	CComBSTR bstrNil(g_cbNil);
	OBJECTTYPE rgType = ObjTypToOBJECTTYPE((ObjTyp)iObjTyp);

		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));
		THROW_FAILED_HRESULT(Objs -> Add(bstrNil, bstrNil, rgType, Obj.ppi()));
		TX_ASSERT(Obj.IsValid());

//		if (iObjTyp >= 0)		// Objekttyp ist gegeben
//		{
//			THROW_FAILED_HRESULT(Obj -> put_Type(rgType));
//		}
		THROW_FAILED_HRESULT(Obj -> get_Handle (&lONr));	// Objektnummer liefern

	} COM_CATCH_RETURN(-1L);
	return lONr;
}

///////////////////////////////////////////////////////////////////////////////
// Einspeichern eines Objektes aus übergebenen Feldern 
bool DatenBasisObjekt::ModObjGeometrie (HPROJECT hPr, OBJGEOMETRIE *pGS, IUnknown *pICS)
{
	if (HACTCONNECTION != hPr && !IsValidConnection(hPr)) {
		SetLastError (E_INVALIDARG);
		return false;
	}

GeoObjekt *pGO = NULL;	// Daten konvertieren
bool fRc = true;

// Identifikator richten
	if (0L == pGS -> lIdent || -1L == pGS -> lIdent) {
		if (pGS -> lONr > 0)		// ObjektNummer bekannt
			pGS -> lIdent = RetrieveIdent (pGS -> lONr, true);
		else {			// Ident und ObjektNummer sind unbekannt
			if (DB(hPr).GetROMode()) {
				SetLastError (HRESULT_FROM_ERRCODE(WC_DATASOURCE_ISRO));
				return false;
			}
			pGS -> lIdent = DEX_GetUnknownIdentEx(hPr);
		}
	}
	if (0L == pGS -> lIdent || -1L == pGS -> lIdent) {
		SetLastError (E_INVALIDARG);
		return false;
	}

HPROJECT hPrLoc = NULL;

	if (0 != pGS -> lONr && -1 != pGS -> lONr)
		hPrLoc = GetObjectDBHandle (pGS -> lONr, hPr);
	if (NULL == hPrLoc)
		hPrLoc = GetIdentDBHandle (pGS -> lIdent, hPr);
	TX_ASSERT(HACTCONNECTION != hPrLoc);		// Handle muß an dieser Stelle bekannt sein

GeoDB &rDB = DB (hPrLoc);

	if (rDB.GetROMode()) {
		SetLastError (HRESULT_FROM_ERRCODE(WC_DATASOURCE_ISRO));
		return false;
	}
	if (DEX_GetROModeIdent (pGS -> lIdent)) {
		SetLastError (HRESULT_FROM_ERRCODE(WC_CLASS_ISRO));
		return false;
	}

// wenn lediglich Template erzeugt werden soll
	if (pGS -> dwSize == sizeof(OBJCREATE)) {
		if (!(pGS -> iFlags & OGTempObject)) {
			if (pGS -> lIdent == 0L) {
				pGS -> lIdent = DEX_GetUnknownIdentEx(hPr);
				if (0L == pGS -> lIdent) 
					return false;
			}
			if (pGS -> lONr > 0) {
			// bestehendes Objekt löschen und wiederverwenden
				if (!DeleteObjekt (pGS -> lONr)) 
					return false;
			}
#if defined(_FORCE_LEGACY_CODE)
			if (!IsTRiASDBBased()) {
				pGS -> lONr = rDB.CreateObjTemplate (pGS -> lIdent, pGS -> iObjTyp);
			} else
#endif // _USE_LEGACY_CODE
			{
				TX_ASSERT(IsTRiASDBBased());
				pGS -> lONr = CreateObjTemplate (pGS -> lIdent, pGS -> iObjTyp);
			}
			if (pGS -> lONr == -1L) return false;
		
		// neues Objekt im Speicher erzeugen/Ident registrieren
			if (!AddNewIdent (pGS -> lIdent, hPalette, 0, MODIDENT_TYP))
				return false;

			IncrementObjectCount();		// ein Objekt mehr
#if defined(_FORCE_LEGACY_CODE)
			rDB.SetDirty();
#endif // _USE_LEGACY_CODE
			SetLastError (S_OK);
			return true;
		} else {
			SetLastError (S_OK);
			return true;	// so tun als ob's ok wäre
		}
	}

//
// 1. Schritt: Geometrie des neuen Objektes besorgen
//
	if (pGS -> iFlags & OGIgnoreGeometry) {
		SetLastError (S_FALSE);
		return false;		// jemand war vor uns da
	}

	if (!(pGS -> iFlags & OGModObject)) {
#if defined(_FORCE_LEGACY_CODE)
		if (!IsTRiASDBBased()) {
			pGS -> lONr = -1L;	// ObjektNummer muß neu vergeben werden
		} else
#endif // _USE_LEGACY_CODE
		{
			TX_ASSERT(IsTRiASDBBased());
			pGS -> lONr = CreateObjTemplate (pGS -> lIdent, pGS -> iObjTyp);
		}
	}

	if (pGS -> iFlags & OGOverlay) {
	// wenn ObjektGeometrie von einem anderen Objekt übernommen werden soll
	CONrTable t (Shapes().ObjNumTree());
	COPYGEOMETRIE *pCG = (COPYGEOMETRIE *)pGS;

		if (!t.Find (&pCG -> lTargetONr)) {	// Objekt suchen
		// nicht gefunden, Objekt ist offensichtlich nicht geladen
		HRESULT hr = GetGI (pCG -> lTargetONr, NULL, &pGO);

			if (S_OK != hr)
				return false;
		} else 
		// Objekt ist derzeit geladen
			pGO = GetGeoObj (pCG -> lTargetONr);

	} else {
	// wenn ObjektGeometrie gegeben ist
		if (pGS -> iFlags & OGConverted) {	// konvertierte doubleKoordinaten 
			if (NULL == pCT()) {
				SetLastError (E_UNEXPECTED);
				return false;
			}

		KoOrd *x = NULL, *y = NULL;

			TX_TRY((x = new KoOrd [pGS -> lCnt], y = new KoOrd [pGS -> lCnt]));
			if (NULL == x || NULL == y) {
				SetLastError (E_OUTOFMEMORY);
				DELETE_OBJ (x);
				return false;
			}

		// GeoObjekt bilden
			fRc = ConvertCoords (x, y, pGS, pCT(), pICS, false);
			if (fRc) pGO = MakeGIObject (pGS, x, y);

		// Speicher wieder freigeben
			DELETE_OBJ(x);
			DELETE_OBJ(y);
		} else 				// !konvertierte longKoordinaten
			pGO = MakeGI (pGS, (long *)pGS -> pdblX, (long *)pGS -> pdblY);
	}
	if (NULL == pGO) 
		return false;

//
// 2. Schritt: Objekt in die GeoDB wegschreiben 
// 	       (wenn nicht TempObjekt gefordert ist)
	if (pGS -> iFlags & OGTempObject) 
	// ObjektNummer generieren
		 pGO -> ObjNr() = rDB.GetUniqueTempONr();
	else {
	// Geometrie testen, ob Koordinaten innerhalb DBCont liegen
		if (!(pGS -> iFlags & OGForceGeometry) && !rDB.VerifyGI (pGO)) 
		{
			SetLastError (E_INVALIDARG);
		    DELETE_OBJ(pGO);
		    return false;
		}

	// neue Geometrie schreiben
#if defined(_FORCE_LEGACY_CODE)
		if (!IsTRiASDBBased() && pGS -> iFlags & OGOverlay) {
		// Geometrie in der DB überlagern
		COPYGEOMETRIE *pCG = (COPYGEOMETRIE *)pGS;

			rDB.SetDirty();
			pGO -> ObjNr() = pGS -> lONr;
			if (rDB.OverlayGI (pCG -> lTargetONr, pGO) != EC_OKAY) {
				DELETE_OBJ (pGO);
				return false;
			}
		} else 
#endif // _USE_LEGACY_CODE
		{
		// bisherige Geometrie rauslöschen, wenn modifiziert werden soll
			if (pGS	-> iFlags & OGModObject) {
			// bei allen nachfragen, ob geändert werden soll
				if (DEXN_ChangingObject (pGS -> lONr))
					return false;		// jemand hat was dagegen

#if defined(_FORCE_LEGACY_CODE)
			// Geometrie löchen
				if (!IsTRiASDBBased() && EC_OKAY != rDB.DelGI (pGO -> ObjNr())) {
					DELETE_OBJ (pGO);
					return false;
				}
#endif // defined(_FORCE_LEGACY_CODE)
			}
			else {
				if (DEXN_AddingObject(hPrLoc))
					return false;	// jemand hat was dagegen
				DEXN_ObjectToAdd(hPrLoc);
			}

		// Objekt/Geometrie neu speichern
			if (PutGI (pGO) != EC_OKAY) {
				DELETE_OBJ (pGO);
				return false;
			}
		}
	}

//
// Schritt 3: GeoObjekt im Speicher aufbauen
//
	if ((pGS -> iFlags & (OGModObject|OGOverlay)) && (pGO -> ObjNr() != -1L))
	// bisheriges Objekt löschen
		Shapes().DeleteObjekt (pGO -> ObjNr());
	else
		IncrementObjectCount();		// ein Objekt mehr

// neues Objekt im Speicher erzeugen
	if (!(pGS -> iFlags & OGNoMemoryObject)) {
		if (-1 == PutGeoObj (pGO, pGS -> iFlags)) {
			DELETE_OBJ (pGO);
			return false;
		}
		pGS -> lONr = pGO -> ObjNr();	// neue ObjektNummer
	} 
	else {
	// Ident muß angelegt werden
		if (!AddNewIdent (pGS -> lIdent, hPalette, 0, OTypToBits((ObjTyp)pGS -> iObjTyp)))	
			return false;

		pGS -> lONr = pGO -> ObjNr();	// neue ObjektNummer
		DELETE_OBJ (pGO);
	}
	if (!(pGS -> iFlags & OGModObject))
		DEXN_ObjectAdded(pGS -> lONr);

	DEXN_ObjectChanged (pGS -> lONr);
	SetLastError (S_OK);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt sicher aus dem Speicher entladen, Objektklasse entsprechend kennzeichnen
BOOL DatenBasisObjekt::UnloadObject	(INT_PTR hObj)
{
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());
INT_PTR lIdent = RetrieveIdent (hObj);		// Objektklasse bestimmen

// zuerst wirklich aus Speicher rauswerfen
BOOL fHasChanged = FALSE;		

	for (tabObj.FindFirst (&lIdent); tabObj.Valid(); ) {
	// Objekte in dieser Objektklasse wiederfinden
	long lONr = 0;

		{	// Objektnummer holen
		ExtShapeObjectIdentLock l(tabObj);

			if (!l) break;	// Fehler
			if (l -> Id() != lIdent) 
				break;	// fertig mit diesem ID
			if (hObj == l -> ObjNr())	// Objekt rauslöschen
				lONr = hObj;
		}

	// löschen, erst nur Baum, dann Baum mit Objekt
		if (lONr != 0 && tabONr.Find (&lONr)) {
			tabONr.Delete();
			tabObj.Delete();
	
			fHasChanged = TRUE;
			break;
		} else
			tabObj.Next();
	}

// jetzt Objektklasse kennzeichnen
	if (fHasChanged) {
	CTable t(Idents().IdentTree());

		if (t.Find (&lIdent)) {
		CIdentifikatorLock l(t);

			if (l) {
//				l -> MayUnload(lONr);
			CIdentObjects *pObjs = l -> DetachObjList();	// Objektliste neu einlesen

				DELETE_OBJ(pObjs);
				l -> NotAllLoaded();		// nicht mehr alle Objekte sind geladen
				ResetLoadedRects();			// nichts ist mehr so, wie es war
			}
		}
	}
	return fHasChanged;
}

///////////////////////////////////////////////////////////////////////////////
//
inline double sqr (long x) { return (double(x)*double(x)); }

// DatenBasisObjekt::MakeGI bildet DB-Objekte und übergibt einen
// Pointer auf ein GeoObjekt (GeoPunkt, GeoKante oder GeoMasche)
GeoObjekt *DatenBasisObjekt::MakeGI (OBJGEOMETRIE *pGS, long *x, long *y) 
{
// hier ist die einzige Stelle, wo 'externe' long-Koordinaten in 'interne' double 
// Koordinaten konvertiert werden müssen
KoOrd *pdX = NULL;
KoOrd *pdY = NULL;

	COM_TRY {
	// Speicher anfordern
	long lCnt = pGS -> lCnt;

		pdX = new KoOrd[lCnt];
		pdY = new KoOrd[lCnt];

	// Koordinaten DeSkalieren
		for (long i = 0; i < lCnt; i++) {
			if (!pCT() -> UnScale (x[i], y[i], &pdX[i], &pdY[i]))
				return NULL;
		}

	} COM_CATCH_RETURN(NULL);

// Objekt erzeugen
	return MakeGIObject (pGS, pdX, pdY);
}

GeoObjekt *DatenBasisObjekt::MakeGIObject (OBJGEOMETRIE *pGS, KoOrd *x, KoOrd *y) 
{
// Geometrie anfordern
GeoObjekt *pGO = NULL;           // Anfangswert

// zu Zeit nur Elementarobjekte 
	COM_TRY {
		switch (pGS -> iObjTyp) {
		case OT_PUNKT:         // PunktObjekt
			pGO = new GeoPunkt (DB(), pGS -> lONr, pGS -> lIdent, Punkt (x[0], y[0]));
			break;

		case OT_KANTE:         // KantenObjekt
			pGO = new GeoKante (DB(), pGS -> lONr, pGS -> lIdent, Kante(pGS -> lCnt, x, y));
			break;

		case OT_FLAECHE:         // Flächenobjekt
			{
				for (short i = 0; i < pGS -> iKCnt; i++) {
				long lUsedLen = pGS -> plCnt[i];
		
					if (NULL == pGO) 
					// erste Geometrieportion       
						pGO = new GeoFlaeche (DB(), pGS -> lONr, pGS -> lIdent, Masche(lUsedLen, x, y, false));
					else
						((GeoFlaeche *)(pGO)) -> AddKante (lUsedLen, x, y);
		
					x += lUsedLen;		// auf nächste Kontur stellen
					y += lUsedLen;
				}
			}
			break;

		case OT_KREIS:
			{
			long lRadius = (long)sqrt (sqr(x[0]-x[1])+sqr(y[0]-y[1]));
			Punkt Pt (x[0], y[0]);

				pGO = new GeoKreis (DB(), pGS -> lONr, pGS -> lIdent, Pt, lRadius);
			}
			break;

		case OT_LABEL:
		case OT_TEXT:		// TextObjekt
			{
			CCSTextPointGeometry text(x[0], y[0]);
			CComBSTR bstrText ((OT_LABEL == pGS -> iObjTyp) ? g_cbIndText : g_cbNil);

				bstrText += ((TEXTGEOMETRIE *)pGS) -> pText;
				text.put_Text (bstrText);

			BOOL fIndObjProp = (OT_LABEL == pGS -> iObjTyp) ? TRUE : FALSE;

				if (pGS -> dwSize == sizeof(TEXTGEOMETRIEEX))
					fIndObjProp = ((TEXTGEOMETRIEEX *)pGS) -> fIndObjProp;

				if (!fIndObjProp) {
					pGO = new GeoText (DB(), pGS -> lONr, pGS -> lIdent, Punkt(text), ((TEXTGEOMETRIE *)pGS) -> pText);
				} else {
					pGO = new GeoTextIndOP (DB(), pGS -> lONr, pGS -> lIdent, Punkt(text));
				}
			}
			break;

		default:
			pGO = NULL;
			break;
		}
	} COM_CATCH_OP_RETURN(delete(pGO), NULL);
	return pGO;		// im Fehlerfall NULL
}

bool DatenBasisObjekt::GetTextObjektText (HPROJECT hPr, GETTEXTDATA *pGTD)
{
GeoObjekt *pGO = GetGeoObj (pGTD -> m_lONr);

	if (pGO == NULL || (pGO -> isA() != OT_TEXT && pGO -> isA() != OT_LABEL)) {
		DELETE_OBJ (pGO);
		return false;
	}
	
char *pText = ((BasicGeoText *)pGO) -> TextBase();

	TX_ASSERT(TIsValidString(pText));
	if (pText && pGTD -> m_pText) {
		strncpy (pGTD -> m_pText, pText, pGTD -> m_iLen);
		pGTD -> m_pText[pGTD -> m_iLen-1] = '\0';
		pGTD -> m_iLen = strlen (pGTD -> m_pText);
	} else 
		pGTD -> m_iLen = 0;
		
	delete pGO;
	return true;
}

bool DatenBasisObjekt::PutTextObjektText (HPROJECT hPr, PUTTEXTDATA *pPTD)
{
bool fResult = false;

#if defined(_FORCE_LEGACY_CODE)
	if (IsTRiASDBBased()) {
	// erstmal in der GeoDB ändern
	BOOL fIndObjProp = FALSE;

		if (sizeof(PUTTEXTDATAEX) == pPTD -> dwSize)
			fIndObjProp = ((PUTTEXTDATAEX *)lParam) -> m_fIndObjProp;	// Labelobjekt

		if (EC_OKAY == DB().WriteText (pPTD -> m_lONr, (char *)pPTD -> m_pcText, fIndObjProp))
			return ChangeTextObjectText (pPTD -> m_lONr, (char *)pPTD -> m_pcText);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	GeoObjekt *pGO = GetGeoObj (pPTD -> m_lONr);

		if (pGO == NULL || (pGO -> isA() != OT_TEXT && pGO -> isA() != OT_LABEL)) {
			DELETE_OBJ (pGO);
			return false;
		}
		
		COM_TRY {
		CCSTextPointGeometry text (pGO -> GetGeometry());		// throws hr

			TX_ASSERT(text.IsValid());

			if (SUCCEEDED(text.put_Text (CComBSTR(pPTD -> m_pcText))) && SUCCEEDED(PutGI (pGO)))
			{
				fResult = ChangeTextObjectText (pPTD -> m_lONr, (char *)pPTD -> m_pcText);
			}
			DELETE_OBJ(pGO);

		} COM_CATCH_OP_RETURN(delete pGO, false);
	}
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung von SichtContainern 
ErrCode DatenBasisObjekt::SetSichtCont (ObjContainer &OC, LPCSTR pcView)
{
// Container als Merkmal an aktueller Sicht wegschreiben
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return WC_RETURN;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return EC_OKAY;

	// Eintrag in Header und Pbd generieren
		MainInitPbd (DB(), IDS_HDRSICHTCONTAINER, true);

	// MCode aus Header holen
	HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
	long lMCode = HE.EntryLong (-1L);

		if (lMCode == -1L) return WC_NOTFOUND;	// Fehler

	CActDB ActDB (DB());		// #ActDB
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), cbBuffer);
	ErrCode RC;

		wsprintf (cbBuffer, "0,%ld,%ld,%ld,%ld", OC.XMin(), OC.YMin(), OC.XMax(), OC.YMax());
		RC = S.PutMiText (lMCode, cbBuffer);
		return RC;
	
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (NULL == pCT())
			return EC_FAIL;

		try {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// Property setzen, evtl. neu erzeugen, vorher Coords konvertieren
#if defined(_KOORD_ISDOUBLE)
		// Koordinaten im Basis-KoordSystem des Projektes ablegen
		CCSRectangleGeometry Rect (OC.XMin(), OC.YMin(), OC.XMax(), OC.YMax(), 1);
#else
		double dX, dY, dWidth, dHeight;
		LPVOID pData = NULL;

			if (!pCT() -> UnScale (OC.XMin(), , &dX, &dY))
				return EC_FAIL;

			pCT() -> GetTransformParam (dX, dY, &pData);
			::ConvertOCToRCEx (pCT(), OC.XMin(), OC.YMin(), dX, dY, pData);
			::ConvertOCToRCEx (pCT(), OC.XMax(), OC.YMax(), dWidth, dHeight, pData);
			pCT() -> FreeTransformParam (pData);

		CCSRectangleGeometry Rect (dX, dY, dWidth-dX, dHeight-dY);
#endif // _KOORD_ISDOUBLE

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;
		WDispatch dispRect (Rect);

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			THROW_FAILED_HRESULT(SetPropertyResID (Props, ResID(IDS_HDRSICHTCONTAINER), (IDispatch *)dispRect, true));

		} catch (_com_error &) {
			return EC_FAIL;
		}
	}
	return EC_OKAY;
}


ErrCode DatenBasisObjekt::DelSichtCont (LPCSTR pcView)
{
// Container als Merkmal an aktueller Sicht löschen
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return WC_RETURN;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return EC_OKAY;

	// Eintrag in Header und Pbd generieren
		MainInitPbd (DB(), IDS_HDRSICHTCONTAINER, true);

	// MCode aus Header holen
	HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
	long lMCode = HE.EntryLong (-1L);

		if (lMCode == -1L) return WC_NOTFOUND;	// Fehler

	CActDB ActDB (DB());		// #ActDB
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), cbBuffer);

		return S.DelMiText (lMCode);	// Merkmal in Sicht löschen
	
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen, gesuchte löschen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			THROW_FAILED_HRESULT(DelProperty (Props, ResID(IDS_HDRSICHTCONTAINER)));

		} catch (_com_error &) {
			return EC_FAIL;
		}
	}
	return EC_OKAY;
}


ErrCode DatenBasisObjekt::GetSichtCont (ObjContainer *pOC, LPCSTR pcView)
{
// Container als Merkmal aus aktueller Sicht lesen
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return WC_RETURN;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return WC_RETURN;

	// Eintrag in Header und Pbd generieren
		MainInitPbd (DB(), IDS_HDRSICHTCONTAINER, true);

	// MCode aus Header holen
	HeaderEntry HE (DB(), IDS_HDRSICHTCONTAINER);
	long lMCode = HE.EntryLong (-1L);

		if (lMCode == -1L) return WC_NOTFOUND;	// Fehler

	CActDB ActDB (DB());		// #ActDB
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), cbBuffer);
	LPSTR pBuffer = NULL;
	ErrCode RC;

		RC = S.GetMiText (lMCode, &pBuffer);
		if (NULL == pOC || EC_OKAY != RC) {
			DELETE_OBJ (pBuffer);
			return RC;	// Fehler oder nur testen, ob Merkmal existiert
		}

	// ObjContainer neu aufbauen
	char *cptr;

		strtok (pBuffer, ",");		// erste Zahl überspringen
		cptr = strtok (NULL, ",");
		if (cptr) pOC -> SetXMin(atol (cptr));
		else {
			DELETE_OBJ (pBuffer);
			return WC_RETURN;
		}

		cptr = strtok (NULL, ",");
		if (cptr) pOC -> SetYMin(atol (cptr));
		else {
			DELETE_OBJ (pBuffer);
			return WC_RETURN;
		}

		cptr = strtok (NULL, ",");
		if (cptr) pOC -> SetXMax(atol (cptr));
		else {
			DELETE_OBJ (pBuffer);
			return WC_RETURN;
		}

		cptr = strtok (NULL, ",");
		if (cptr) pOC -> SetYMax(atol (cptr));
		else {
			DELETE_OBJ (pBuffer);
			return WC_RETURN;
		}
		DELETE_OBJ (pBuffer);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (NULL == pCT())
			return EC_FAIL;

		try {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

		// Property lesen, dann Coords konvertieren
		WDispatch dispRect (GetPropertyResID (Props, ResID(IDS_HDRSICHTCONTAINER), (IDispatch *)NULL), false);
		CCSRectangleGeometry Rect (dispRect);

			if (!Rect) return EC_FAIL;		// Container exitiert nicht

//			Rect -> Release();		// GetProperty liefert mit AddRef ab
			if (NULL == pOC)
				return EC_OKAY;		// lediglich testen, ob Container existiert

#if defined(_KOORD_ISDOUBLE)
		// Koordinaten liegen im Basis-KoordSystem des Projektes vor
		double dXMin, dYMin, dXMax, dYMax;
		
			THROW_FAILED_HRESULT(Rect.get_XMin(&dXMin));
			THROW_FAILED_HRESULT(Rect.get_YMin(&dYMin));
			THROW_FAILED_HRESULT(Rect.get_XMax(&dXMax));
			THROW_FAILED_HRESULT(Rect.get_YMax(&dYMax));
			pOC -> SetXMin(dXMin);
			pOC -> SetYMin(dYMin);
			pOC -> SetXMax(dXMax);
			pOC -> SetYMax(dYMax);
#else
		double dX, dY, dWidth, dHeight;
		
			THROW_FAILED_HRESULT(Rect.get_X(&dX));
			THROW_FAILED_HRESULT(Rect.get_Y(&dY));
			THROW_FAILED_HRESULT(Rect -> get_Width(&dWidth));
			THROW_FAILED_HRESULT(Rect -> get_Height(&dHeight));

		LPVOID pData = NULL;
		KoOrd x, y;

			if (!pCT() -> Scale (dX, dY, &x, &y))
				return EC_FAIL;

			pCT() -> GetInvTransformParam (x, y, &pData);
			::ConvertRCToOCEx (pCT(), dX, dY, x, y, pData);
			pOC -> SetXMin(x);
			pOC -> SetYMin(y);

			::ConvertRCToOCEx (pCT(), dX+dWidth, dY+dHeight, x, y, pData);
			pOC -> SetXMax(x);
			pOC -> SetYMax(y);

			pCT() -> FreeInvTransformParam (pData);
#endif // _KOORD_ISDOUBLE

		} catch (_com_error &) {
			return EC_FAIL;
		}
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Textobjekte anzeigen/nicht anzeigen
HRESULT DatenBasisObjekt::SetShowTexts (bool fShowTexts, LPCSTR pcView)
{
// Flag als Merkmal an aktueller Sicht wegschreiben
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return WC_RETURN;		// keine aktive Sicht
		pcView = cbBuffer;
	}

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Ansicht besorgen
	WTRiASView View;

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

	// Property setzen, evtl. neu erzeugen
	WTRiASProperties Props;
	CComBool fShow (fShowTexts);

		THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
		THROW_FAILED_HRESULT(SetProperty (Props, g_cbShowTextsInView, VARIANT_BOOL(fShow), true));

	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::GetShowTexts (bool &rfShowTexts, LPCSTR pcView)
{
// Flag als Merkmal an aktueller Sicht wegschreiben
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return WC_RETURN;		// keine aktive Sicht
		pcView = cbBuffer;
	}

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Ansicht besorgen
	WTRiASView View;
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));		// Property lesen
	
	CComBool fShow (GetProperty (Props, g_cbShowTextsInView, VARIANT_TRUE));

		rfShowTexts = fShow;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recherche nach Textmerkmal, Enumeration der gefundenen Objekte 
namespace {
	HRESULT GetSearchCommand(int iMode, BSTR *pbstrCommand)
	{
	CComBSTR bstrCommand;
	
		switch (iMode & SMActionFlag) {
		default:
			TX_ASSERT(FALSE);
		//
		// hier durchfallen ...
		case SMExactMatch:
			bstrCommand = SEARCHCOMMAND_MatchComplete;
			break;

		case SMSubstringMatch:
			bstrCommand = SEARCHCOMMAND_MatchComplete;
			bstrCommand += g_cbSemiColon;
			bstrCommand += SEARCHOPTION_PartialMatch;
			bstrCommand += g_cbHasOption;
			break;

		case SMSubStringStartMatch:
			bstrCommand = SEARCHCOMMAND_MatchComplete;
			bstrCommand += g_cbSemiColon;
			bstrCommand += SEARCHOPTION_PartialMatchBOB;
			bstrCommand += g_cbHasOption;
			break;

		case SMInexactMatch:
			bstrCommand = SEARCHCOMMAND_MatchLike;
			break;

		case SMRegularExpression:
			bstrCommand = SEARCHCOMMAND_MatchRegExpr;
			break;

		case SMSubRegularExpression:
			bstrCommand = SEARCHCOMMAND_MatchRegExpr;
			bstrCommand += g_cbSemiColon;
			bstrCommand += SEARCHOPTION_PartialMatch;
			bstrCommand += g_cbHasOption;
			break;

		case SMExistanceOnly:
			bstrCommand = SEARCHCOMMAND_ExistanceOnly;
			break;
		}

		if (iMode & SMIgnoreCase) {
			bstrCommand += g_cbSemiColon;
			bstrCommand += SEARCHOPTION_IgnoreCase;
			bstrCommand += g_cbHasOption;
		}
		if (iMode & SMNegateResult) {
			bstrCommand += g_cbSemiColon;
			bstrCommand += SEARCHOPTION_NegateResult;
			bstrCommand += g_cbHasOption;
		}

		*pbstrCommand = bstrCommand.Detach();
		return S_OK;
	}
} // namespace

bool DatenBasisObjekt::EnumRechTextMerkmal (ENUMRECHTEXTMERKMAL *pERTM)
{
// als erstes Textrecherche selbst durchführen
ObjFeld Objekte;					// Feld welches ObjektNummern aufnehmen soll
char *pText = pERTM -> pMWert;		// zu suchender Text (evtl. NULL --> ExistanceOnly)

	if (NULL == pText && 0 == (pERTM -> iMode & SMActionFlag)) 
		pERTM -> iMode = SMExistanceOnly;		// alter code verwendet das !

	if (SMExistanceOnly == (pERTM -> iMode & SMActionFlag) && NULL != pText) {	// NULL-Text vortäuschen
		pText = NULL;
//		pERTM -> iMode = SMExactMatch | (pERTM -> iMode & SMActViewOnly);
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ErrCode RC = DB().FindText (pERTM -> lMCode, pERTM -> iMode & SMActionFlag, pText, Objekte);

		if (RC == WC_NOTFOUND) return true;	// nichts gefunden
		if (RC != EC_OKAY) return false;	// Fehler

		if (pERTM -> iMode & SMActViewOnly) {
		// nach Identifikatoren (über aktuelle Sicht) filtern
			if (DB().IdFilter (Objekte, Idents()) != EC_OKAY)
				return false;
		} else if (pERTM -> pView != NULL) {
		// nach Identifikatoren (über gegebebene Sicht) filtern
			if (DB().IdFilter (Objekte, pERTM -> pView) != EC_OKAY)
				return false;
		}
	} else 
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Rechercheparameter zusammenbauen
	CSafeArray sa (VT_VARIANT, 2);

		{
		CSafeArrayLock<VARIANT> lock (sa);
		CComVariant v(pText);

			v.Detach(&lock[0]);
			lock[1] = CComVariant(pERTM -> lMCode);		// MerkmalsCode übergeben
		}

	// alle geöffneten DatenBanken nacheinander arbeiten lassen
	bool fFilteredColl = (pERTM -> dwSize == sizeof(ENUMRECHTEXTMERKMALEX)) ? 
		((ENUMRECHTEXTMERKMALEX *)pERTM) -> fFilteredColl : false;
	bool fFilterView = (pERTM -> iMode & SMActViewOnly) ? true : false;
	CComBSTR bstrCommand;

		if (FAILED(GetSearchCommand(pERTM -> iMode, CLEARED(&bstrCommand))) ||
			FAILED(SearchObjects (bstrCommand, CComBSTR("Test"), sa, Objekte, 
				fFilteredColl, fFilterView, pERTM -> pView, pERTM -> lMCode)))
		{
			return false;
		}

	// ggf. Flag zurückschreiben
		if (pERTM -> dwSize == sizeof(ENUMRECHTEXTMERKMALEX))
			((ENUMRECHTEXTMERKMALEX *)pERTM) -> fFilteredColl = fFilteredColl;
	}

// gefundene Objekte enumerieren
	return Objekte.Enumerate ((BOOL (*)(long, BOOL, void *))pERTM -> eFcn, pERTM -> pData);
}

HRESULT CopyHandlesToResult (ITRiASObjects *pIObjs, ObjFeld &rObjs)
{
	COM_TRY {
	ObjNummerCreator ONC (rObjs);              // Creator
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(pIObjs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

		WTRiASObject Obj (V_DISPATCH(&v));
		INT_PTR hObj = NULL;

			THROW_FAILED_HRESULT(Obj -> get_Handle (&hObj));
			rObjs.NewObj (ONC, hObj);
		}

	} COM_CATCH;
	return S_OK;
}

// Erzeugen und initialisieren eines neuen TRiASObjects- Objektes
namespace {
	HRESULT MakeNewObjects (
		IDispatch *pIParent, BSTR bstrName, REFCLSID rClsId, 
		OBJECTSCOLLECTIONTYPE rgType, ITRiASObjects **ppIObjs) throw(_com_error)
	{
	WTRiASObjectsOperations ObjOper (CLSID_TRiASObjectsOperations);		// throws hr

		return ObjOper -> MakeNewObjects(pIParent, bstrName, CComBSTR(CIID(rClsId).ProgID().c_str()), rgType, ppIObjs);
	}
} // namespace

HRESULT DatenBasisObjekt::SearchObjectsDataSource (GeoDB *pDB, BSTR bstrCommand, 
	ITRiASObjectsCollection *pIObjsColl, bool fFilterView, bool &rfFilteredColl, 
	SAFEARRAY *pParams, ITRiASObjects *pIObjsRes)
{
	TX_ASSERT(!fFilterView || NULL != pIObjsColl);		// bei Suche über Ansicht muß ObjsColl gegeben sein

HRESULT hr = pDB -> SearchObjects (bstrCommand, pIObjsRes, pParams);
WTRiASSearchObjects SearchObjs;

	if (S_OK != hr) {
		if (!rfFilteredColl && 
				(TRIASDB_S_SEARCH_NOT_SUPPORTED == hr || 
				 TRIASDB_S_SEARCH_NOT_RECOMMENDED == hr ||
				 E_NOTIMPL == hr)
			) 
		{
		// DataBase unterstützt diese Recherche nicht, Objektklassen einzeln durchgehen
			rfFilteredColl = true;
			if (fFilterView && NULL != pIObjsColl && 
				SUCCEEDED(pIObjsColl -> QueryInterface(SearchObjs.ppi()))) 
			{
				TX_ASSERT(SearchObjs.IsValid());
				if (S_OK == SearchObjs -> ConsiderSearch (bstrCommand, pParams))
				{
					hr = SearchObjs -> SearchObjects (bstrCommand, pIObjsRes, pParams);
				}
			}
			else {
				hr = pDB -> SearchObjectsSeparate (bstrCommand, pIObjsRes, pParams);		// Objektklassenweise vorgehen
			}
		} 
		if (S_OK != hr)
			return hr;		// Fehler oder nichts gefunden
	} 
	else if (fFilterView && NULL != pIObjsColl &&
			 SUCCEEDED(pIObjsColl -> QueryInterface(SearchObjs.ppi()))) 
	{
	// ok, über Ansicht filtern
		TX_ASSERT(SearchObjs.IsValid());
		RETURN_FAILED_HRESULT(SearchObjs -> ConstraintObjects (pIObjsRes));
	} 
	return S_OK;
}

HRESULT DatenBasisObjekt::SearchObjects (
	BSTR bstrCommand, BSTR bstrOutName, SAFEARRAY *pParams, ObjFeld &rObjs, 
	bool &rfFilteredColl, bool fFilterView, LPCSTR pcView, INT_PTR lMCode)
{
CRing r (*m_pGeoDBs);
WTRiASFeature Prop;
WTRiASObjectsCollection ObjsColl;

	if (fFilterView) {
	// über Ansicht recherieren
	string strView;
	
		if (!GetViewName (pcView, strView)) return false;
	
	// Objektklassen der Ansicht besorgen			
	WTRiASView View;

		RETURN_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(strView.c_str()), VARIANT_FALSE, View.ppi()));
		RETURN_FAILED_HRESULT(View -> get_ObjectsDefs (ObjsColl.ppi()));
	}

// Resultatsmenge
WTRiASObjects Objs;		

	RETURN_FAILED_HRESULT(MakeNewObjects (m_Prj, bstrOutName, CLSID_TRiASObjects, OBJECTSCOLLECTIONTYPE_Temporary, Objs.ppi()));
	if (0 == lMCode) {
	// eigentliche Recherche (über alle geöffneten Datenbanken)
		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened()) {
			// Recherche durchführen
				if (S_OK != SearchObjectsDataSource (l, bstrCommand, ObjsColl, 
					fFilterView, rfFilteredColl, pParams, Objs))
				{
					continue;	// Fehler oder nichts gefunden
				}
			}
		}
	} else {
	// Recherche genau über eine Datenquelle (aus der Feature stammt)
	HPROJECT hPr = GetFeatureDBHandle (lMCode);
	GeoDB &rDB = m_pGeoDBs -> DB(hPr);

		if (rDB.isOpened()) {
		// Recherche nur für diese eine durchführen
		HRESULT hr = SearchObjectsDataSource (&rDB, bstrCommand, ObjsColl, fFilterView, 
			rfFilteredColl, pParams, Objs);

			if (S_OK != hr)
				return hr;				// Fehler oder nichts gefunden
		} 
		else {
			return E_UNEXPECTED;		// can happen, while Legend is to be opened
		}
	}

// Ergebnis in Feld ablegen
	RETURN_FAILED_HRESULT(CopyHandlesToResult (Objs, rObjs));
	return S_OK;
}

// Recherche nach Geometrie (Rechteck), Enumeration der gefundenen Objekte ----
bool DatenBasisObjekt::EnumRechGeometrie (ENUMRECHGEOMETRIE *pERG)
{
// als erstes Geometrierecherche selbst durchführen
CActDB ActDB (DB());
ObjFeld Objekte;	// Feld für ObjektNummern
HRESULT hr = S_OK;
LPCSTR pcView = NULL;

// nach Identifikatoren (über gegebene Sicht) filtern
	if (sizeof(ENUMRECHGEOMETRIEEX) == pERG -> dwSize) {
	ENUMRECHGEOMETRIEEX *pERGEx = (ENUMRECHGEOMETRIEEX *)pERG;

		if (NULL != pERGEx -> m_pView)
			pcView = pERGEx -> m_pView;
		else
			pERG -> iMode |= ERGActSight;		// über aktuelle Sicht filtern
	}

	if (NULL == pCT()) return false;

// Container berechnen und recherche durchführen
	if (pERG -> iMode & ERGConverted) {

	KoOrd x1, y1, x2, y2;
	double *pC = (double *)pERG -> lCont;

	LPVOID pData = NULL;

		pCT() -> GetInvTransformParam (pC[0], pC[2], &pData);
		::ConvertRCToOCEx (pCT(), pC[0], pC[2], x1, y1, pData);
		::ConvertRCToOCEx (pCT(), pC[1], pC[3], x2, y2, pData);
//		if (NULL != pData) CoTaskMemFree (pData);
		pCT() -> FreeInvTransformParam (pData);

	ObjContainer OC (x1, x2, y1, y2);

		hr = GIWindow (OC, Objekte, pERG -> iMode & ERGExact, pERG -> iMode & ERGActSight, pcView);
	} else {
	double dXMin, dXMax, dYMin, dYMax;
	long *plCont = (long *)pERG -> lCont;

		pCT() -> UnScale (plCont[0], plCont[2], &dXMin, &dYMin);
		pCT() -> UnScale (plCont[1], plCont[3], &dXMax, &dYMax);

	ObjContainer OC (dXMin, dXMax, dYMin, dYMax);

		hr = GIWindow (OC, Objekte, pERG -> iMode & ERGExact, pERG -> iMode & ERGActSight, pcView);
	}
	if (FAILED(hr)) return false;

// gefundene Objekte enumerieren
	return Objekte.Enumerate (pERG -> eFcn, pERG -> pData);
}

///////////////////////////////////////////////////////////////////////////////
// GeometrieRecherchefunktionalitäten
BOOL DatenBasisObjekt::GetViewName (LPCSTR pcView, string &rStr)
{
	if (NULL != pcView)
		rStr = pcView;
	else {
	char cbBuffer[64];

		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)))
			return FALSE;
		rStr = cbBuffer;
	}
	return TRUE;
}
	
HRESULT DatenBasisObjekt::GIWindow (
	ObjContainer &rOC, ObjFeld &rObjs, BOOL fExact, BOOL fFilterView, LPCSTR pcView)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ErrCode EC = DB().GIWindow (rOC, rObjs, fExact);

		if (EC_OKAY == EC && fFilterView) {
			if (NULL == pcView) 
				EC = DB().IdFilter (rObjs, Idents());	// über aktueller Ansicht filtern
			else
				EC = DB().IdFilter (rObjs, (LPSTR)pcView);		// über bestimmter Ansicht filtern
		}
		if (EC_OKAY != EC)
			return HRESULT_FROM_ERRCODE(EC);

	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Rechercheparameter zusammenbauen
	CSafeArray sa (VT_VARIANT, 3);

		{
		CSafeArrayLock<VARIANT> lock (sa);
		CComVariant v1((_DGMRectangleGeometry *)rOC);
		CComVariant v2(g_cbDefaultGeometry);

			v1.Detach(&lock[0]);
			v2.Detach(&lock[1]);
			lock[2] = CComVariant(bool(fExact));
		}

	CComBSTR bstrCommand(SEARCHCOMMAND_IntersectsWindow);
	bool fFilteredColl = false;

		if (FAILED(SearchObjects (bstrCommand, CComBSTR("Test"), sa, rObjs, 
			fFilteredColl, fFilterView, pcView)))
		{
			return S_FALSE;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// SichtBeschreibungsinfo behandeln 
char *DatenBasisObjekt::QueryViewDesc (VIEWDESC *pVD)
{
NAMEDVIEWPROPERTY NVP;
ResString resCap (IDS_CAPTIONMCODE, 17);

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = pVD -> m_pView;
	NVP.pcName = resCap.Addr();
	NVP.pBuffer = pVD -> m_pDesc;
	NVP.iLen = pVD -> m_iLen;

HRESULT hr = DEX_GetNamedViewProperty(NVP);

	if (SUCCEEDED(hr)) {
		pVD -> m_iLen = NVP.iLen;
		return pVD -> m_pDesc;
	}
	pVD -> m_iLen = 0;
	return NULL;	// nichts vorhanden
}

char *DatenBasisObjekt::SetViewDesc (VIEWDESC *pVD)
{
NAMEDVIEWPROPERTY NVP;
ResString resCap (IDS_CAPTIONMCODE, 17);
ResString resKText (IDS_CAPTIONMCODEKTEXT, 33);
ResString resLText (IDS_CAPTIONMCODELTEXT, _MAX_PATH);

	INITSTRUCT(NVP, NAMEDVIEWPROPERTY);
	NVP.pcView = pVD -> m_pView;
	NVP.pcName = resCap;
	NVP.pBuffer = pVD -> m_pDesc;
	NVP.iLen = (NULL != pVD -> m_pDesc) ? strlen(pVD -> m_pDesc) : 0;
	NVP.pcShort = resKText;
	NVP.pcDesc = resLText;

HRESULT hr = DEX_SetNamedViewProperty(NVP);

	if (SUCCEEDED(hr)) 
		return pVD -> m_pDesc;

	return NULL;
}

#if defined(_FORCE_LEGACY_CODE)	
// Eintrag für Ident in PBD generieren ----------------------------------------
static bool SaveICodeInPbd (long lIdent, uint uiResKT, uint uiResLT)
{
// PBDEintrag zusammenstellen
ResString rsKText (uiResKT, 32);
ResString rsLText (uiResLT, 64);
PBDDATA TM;
bool iResult = true;

	INITSTRUCT (TM, PBDDATA);
	TM.pbdTyp = 'i';
	TM.pbdCode = lIdent;
	TM.pbdKText = (char *)rsKText.Addr();
	TM.pbdLText = (char *)rsLText.Addr();	
	TM.pbdKTextLen = strlen (rsKText);
	TM.pbdLTextLen = strlen (rsLText);

	{
	ErrInstall EI (WC_NOIDENT);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDIdentChanged (lIdent);
	}
	
return iResult; 
}

long GetHeaderICode (bool fGenerate, uint resID, uint uiResKT, uint uiResLT)
{
GEODBHDRENTRY hdrEntry;
long result = 0L;

	INITSTRUCT (hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = new char [64 +1];
	hdrEntry.hdrTextLen = 64;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
	} else if (fGenerate) {
	// bei Bedarf neu generieren
	long lIdent = DEX_GetUniqueICode();	// neuen MCode besorgen
	
		if (lIdent != -1) {		// und wegschreiben
			ltoa (lIdent, hdrEntry.lphdrText, 10);
			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY)
				result = lIdent;
		// in Pbd eintragen
			SaveICodeInPbd (lIdent, uiResKT, uiResLT);
		}
	}
	DELETE_OBJ (hdrEntry.lphdrText);
	return result;
}
#endif // defined(_FORCE_LEGACY_CODE)	

// Liefert den Ident für ein nicht klassifiziertes/nicht klassifizierbares Objekt 
ULONG DatenBasisObjekt::QueryUnknownIdent (HPROJECT hPr)
{
#if defined(_FORCE_LEGACY_CODE)	
CActDB ActDB (DB());

	return GetHeaderICode (true, IDS_HDRUNKNOWNIDENT, 
			       , IDS_LTUNKNOWNIDENT);
#else
IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = g_cbUnknownOKS;
	IFC.fCreateNew = true;

HRESULT hr = DEX_GetIdentFromClassEx(hPr, IFC);

	if (SUCCEEDED(hr)) {
		if (S_FALSE == hr) {
		// Objekt wiederfinden und Beschreibungsdaten und ggf. definieren
			USES_CONVERSION;
			COM_TRY {
			WTRiASObjects Objs;

				THROW_FAILED_HRESULT(GetObjectsFromMap (IFC.ulIdent, Objs));
				THROW_FAILED_HRESULT(Objs -> put_Name (A2OLE(ResString (IDS_KTUNKNOWNIDENT, 64))));
				THROW_FAILED_HRESULT(Objs -> put_Description (A2OLE(ResString (IDS_LTUNKNOWNIDENT, 128))));

			} COM_CATCH_RETURN(IFC.ulIdent);
		}
		return IFC.ulIdent;	
	}
	return -1L;
#endif // defined(_FORCE_LEGACY_CODE)	
}

///////////////////////////////////////////////////////////////////////////////
// Liefert ONr zu gegebenem Objektnamen 
typedef set<INT_PTR> CMCodesForQuery;
typedef struct tagFINDOBJFROMOBJNAME {
	long m_lONr;
	char *m_pMWert;
	CMCodesForQuery *m_psetMCodes;
} FINDOBJFROMOBJNAME;

extern "C" 
BOOL WINAPI EXPORTTRIAS FindObjNameForIdent (long lONr, BOOL, void *pData)
{
	*(long *)pData = lONr;
	return FALSE;		// nur das erste Objekt interessiert
}

extern "C" 
BOOL WINAPI EXPORTTRIAS EnumIdentForObjName (long lIdent, BOOL, void *pData)
{
FINDOBJFROMOBJNAME *pFindObj = (FINDOBJFROMOBJNAME *)pData;
INT_PTR lMCode = DEX_GetObjNameMCode (lIdent);

	if (NULL != lMCode)
		pFindObj -> m_psetMCodes -> insert(lMCode);		// MCode speichern
	return TRUE;
}

extern "C" 
BOOL WINAPI EXPORTTRIAS EnumIdentForUIdent (long lIdent, BOOL, void *pData)
{
FINDOBJFROMOBJNAME *pFindObj = (FINDOBJFROMOBJNAME *)pData;
INT_PTR lMCode = DEX_GetUniqueIdentMCodeEx (DEX_GetObjectsProject(lIdent));

	if (NULL != lMCode)
		pFindObj -> m_psetMCodes -> insert(lMCode);		// MCode speichern
	return TRUE;
}

namespace {
	long FindObjFromNameAndMCodes (char *pObjName, CMCodesForQuery &rsetMCodes)
	{
	long lONr = -1;

		for (CMCodesForQuery::iterator it = rsetMCodes.begin(); 
			 it != rsetMCodes.end(); 
			 ++it) 
		{
		ENUMRECHTEXTMERKMALEX ERTM;

			INITSTRUCT (ERTM, ENUMRECHTEXTMERKMALEX);
			ERTM.lMCode = *it;
			ERTM.pMWert = pObjName;
			ERTM.iMode = SMExactMatch;
			ERTM.eFcn = (RECHTEXTMERKMALCALLBACK)FindObjNameForIdent;
			ERTM.pData = &lONr;

			if (DEX_EnumRechTextMerkmal(ERTM) && (-1 != lONr || ERTM.fFilteredColl))
				return lONr;		// Objekt gefunden
		}
		return -1;
	}
}

long DatenBasisObjekt::FindObjFromName (char *pObjName)
{
// alle Identifikatoren Enumerieren, da der MCode identspezifisch ist
ENUMNOKEYLONG ENK;
FINDOBJFROMOBJNAME FOBJ;
CMCodesForQuery setMCodes;

	FOBJ.m_lONr = -1L;
	FOBJ.m_pMWert = pObjName;
	FOBJ.m_psetMCodes = &setMCodes;
		
	ENK.eFcn = (ENUMNOKEYLONGPROC)EnumIdentForObjName;
	ENK.ePtr = &FOBJ;
	DEX_EnumIdents (ENK);	// alle MCodes sammeln

// jetzt für alle gefundenen MCodes recherchieren
	FOBJ.m_lONr = FindObjFromNameAndMCodes (pObjName, setMCodes);

	if (-1L == FOBJ.m_lONr) {
	// unter Objektnamen nichts gefunden, das ganze für UniqueIdent wiederholen
		setMCodes.clear();

		ENK.eFcn = (ENUMNOKEYLONGPROC)EnumIdentForUIdent;
		ENK.ePtr = &FOBJ;
		DEX_EnumIdents (ENK);	// sämtliche MCodes sammeln

	// eigentliche Recherche
		FOBJ.m_lONr = FindObjFromNameAndMCodes (pObjName, setMCodes);
	}
	return FOBJ.m_lONr;
}


// RückrufFunktion für EnumIdentViewsEx ---------------------------------------
// extern VisType OTypToVTyp (ObjTyp iOTyp);
extern "C" 
inline bool locF (ENUMLONGKEYEXPROC pF, char *pView, DWORD dwData, void *pPtr)
{
	return ((bool (CALLBACK *)(char *, DWORD, void *))pF)(pView, dwData, pPtr);
}

#if defined(_FORCE_LEGACY_CODE)
typedef struct tagENUMVIEWSDATA {
	ENUMLONGKEYEX *pELK;
	GeoDB *pDB;
} ENUMVIEWSDATA;

extern "C" 
static bool HandleView (Sicht &rS, char *pName, ENUMLONGKEYEX *pELK, short iVTyp)
{
	if (EC_OKAY == rS.GetIDfromSight (pELK -> eKey, NULL, iVTyp)) 
	{
	// eigentliche EnumerationsFunktion rufen
		if (!locF(pELK -> eFcn, pName, pELK -> eData, pELK -> ePtr))
			return false;		// abgebrochen
	}
	return true;
}

extern "C" 
BOOL PASCAL CALLBACK EnumViewForIdent (char *pView, BOOL, void *pData)
{
ENUMVIEWSDATA *pEVD = ((ENUMVIEWSDATA *)pData);
ENUMLONGKEYEX *pELK = pEVD -> pELK;
ErrInstall EI (WC_NOTFOUND);
Sicht S (*(pEVD -> pDB), pView);
char cbName[64];

	OemToAnsi (S.Name(), cbName);

// ACHTUNG: jede Ansicht nur einmal enumerieren ! (#HK971111)
	if (pELK -> eData & OTPunkt) {
		if (!HandleView (S, cbName, pELK, VT_Punkt))
			return false;
		return true;
	}
	if (pELK -> eData & OTLinie) {
		if (!HandleView (S, cbName, pELK, VT_Linie)) 
			return false;
		return true;
	}
	if (pELK -> eData & OTFlaeche) {
		if (!HandleView (S, cbName, pELK, VT_Flaeche)) 
			return false;
		return true;
	}
	if ((pELK -> eData & OTText) && !HandleView (S, cbName, pELK, VT_Text)) 
		return false;

	return true; 	// weiter machen
}
#endif // _FORCE_LEGACY_CODE

typedef struct tagENUMVIEWSDATAPRJ {
	ENUMLONGKEYEX *pELK;
	WTRiASProject m_Prj;
	DatenBasisObjekt *m_pDBO;
} ENUMVIEWSDATAPRJ;

static bool HandleViewPrj (
	DatenBasisObjekt *pDBO, ITRiASView *pIView, char *pName, 
	ENUMLONGKEYEX *pELK, OBJECTTYPE rgVTyp, bool &rfReturn)
{
WTRiASObjects Objs;

	THROW_FAILED_HRESULT(pDBO -> GetObjectsFromMap (pELK -> eKey, Objs));

// ViewItem wiederfinden
WTRiASViewItem ViewItem;
OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

	if (SUCCEEDED(pIView -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi())) &&
		SUCCEEDED(ViewItem -> get_Types (&rgTypes)) &&
		rgTypes & rgVTyp)
	{
	// eigentliche EnumerationsFunktion rufen
		rfReturn = locF(pELK -> eFcn, pName, pELK -> eData, pELK -> ePtr) ? true : false;
		return true;	// enumeriert
	}
	return false;		// nicht enumeriert
}

extern "C" 
BOOL PASCAL CALLBACK EnumViewForIdentPrj (char *pView, BOOL, void *pData)
{
ENUMVIEWSDATAPRJ *pEVD = ((ENUMVIEWSDATAPRJ *)pData);
ENUMLONGKEYEX *pELK = pEVD -> pELK;
WTRiASView View;

	if (FAILED(pEVD -> m_Prj -> get_View (CComBSTR(pView), VARIANT_FALSE, View.ppi()))) {
		TX_ASSERT(false);		// Ansicht wurde nicht wiedergefunden
		return false;	// snh
	}

// ACHTUNG: jede Ansicht nur einmal enumerieren ! (#HK971111), korrigiert: #HK000317
bool fReturn = false;

	if (pELK -> eData & OTPunkt) {
		if (HandleViewPrj (pEVD -> m_pDBO, View, pView, pELK, OBJECTTYPE_Point, fReturn))
			return fReturn;
	}
	if (pELK -> eData & OTLinie) {
		if (HandleViewPrj (pEVD -> m_pDBO, View, pView, pELK, OBJECTTYPE_Line, fReturn)) 
			return fReturn;
	}
	if (pELK -> eData & OTFlaeche) {
		if (HandleViewPrj (pEVD -> m_pDBO, View, pView, pELK, OBJECTTYPE_Area, fReturn)) 
			return fReturn;
	}
	if (pELK -> eData & OTText) {
		if (HandleViewPrj (pEVD -> m_pDBO, View, pView, pELK, OBJECTTYPE_Text, fReturn)) 
			return fReturn;
	}
	return true; 	// weiter machen
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller Sichten, zu dem der gegebene Ident gehört 
bool DatenBasisObjekt::EnumIdentViewsEx (ENUMLONGKEYEX *pELK)
{
ENUMNOKEY ENK;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ENUMVIEWSDATA EVD;

		EVD.pELK = pELK;
		EVD.pDB = &DB();
		
		ENK.eFcn = (ENUMNOKEYPROC)EnumViewForIdent;
		ENK.ePtr = &EVD;
		return DEX_EnumSights (ENK) ? true : false;
	
	} else	
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	ENUMVIEWSDATAPRJ EVD;

		EVD.pELK = pELK;
		EVD.m_Prj = m_Prj;
		EVD.m_pDBO = this;
		
		ENK.eFcn = (ENUMNOKEYPROC)EnumViewForIdentPrj;
		ENK.ePtr = &EVD;
		return DEX_EnumSights (ENK) ? true : false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Identifikator besorgen 
LONG DatenBasisObjekt::RetrieveIdent (LONG lONr, bool fForceNative) 
{
	TX_ASSERT(IsValidONr(lONr));

CONrTable t(Shapes().ObjNumTree());	// Navigator Objektliste

	if (!fForceNative && t.Find (&lONr)) {		// Objekt gefunden
	ExtShapeObjectONrLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);
		
		return l -> Id();
	} else {
	// Objekt nicht geladen, ist nicht in aktueller Sicht
	INT_PTR lIdent = 0L;

#if defined(_FORCE_LEGACY_CODE)
		if (!IsTRiASDBBased()) {
		CActDB ActDB (DB());

		// in GeoDB nachsehen
			if (EC_OKAY == FindID (DB().DBDesc(), lONr, &lIdent))
				return lIdent;
		} else 
#endif // defined(_FORCE_LEGACY_CODE)
		{
			TX_ASSERT(IsTRiASDBBased());
			COM_TRY {
			WTRiASObject Obj;

				THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj))
				THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle (&lIdent));

			} COM_CATCH_RETURN(0L);
			return lIdent;
		}
	}
	return 0L;
}

///////////////////////////////////////////////////////////////////////////////
// Alle Idents einer Ansicht enumerieren

// Enumeration aller Identifikatoren einer Sicht 
extern "C" inline BOOL EnumIdentsCallback (
	BOOL (*pFcn)(long, BOOL, void *), long lKey, BOOL fNotLast, void *pData)
{
	return ((ENUMLONGKEYCALLBACK) pFcn)(lKey, fNotLast, pData);
}

/////////////////////////////////////////////////////////////////////////////
// lokale Daten

namespace {
// Feld aller bekannten Objekttypen 
	const OBJECTTYPE g_rgObjTypes[] = {
		{ OBJECTTYPE_Point, },
		{ OBJECTTYPE_Line, },
		{ OBJECTTYPE_Area, },
		{ OBJECTTYPE_Text, },
		{ OBJECTTYPE_Complex, },
		{ OBJECTTYPE_Unknown, },
	};
}

HRESULT DatenBasisObjekt::EnumViewIdents (LPCSTR pcView, ENUMLONGKEYPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
	Sicht locSicht (DB(), pcView);
	
		return (LRESULT)locSicht.EnumIdents (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Elemente dieser Ansicht besorgen
		WTRiASViewItems ViewItems;

			THROW_FAILED_HRESULT(View -> get_ViewItems (ViewItems.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;
		set<INT_PTR, less<INT_PTR> > setHandles;

			THROW_FAILED_HRESULT(ViewItems -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
			{
				TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

			WTRiASViewItem Item (V_DISPATCH(&v));

			// alle bekannten Objekttypen durchgehen
				for (const OBJECTTYPE *pEntry = g_rgObjTypes;
					 OBJECTTYPE_Unknown != *pEntry;
					 pEntry++)
				{
				WTRiASObjects Objs;

					if (SUCCEEDED(Item -> get_Objects (*pEntry, Objs.ppi())))
					{
					INT_PTR lHandle = NULL;

						if (FAILED(Objs -> get_Handle (&lHandle)) || NULL == lHandle)
							continue;

					set<INT_PTR, less<INT_PTR> >::iterator it = setHandles.find (lHandle);

						if (it == setHandles.end()) {
							setHandles.insert (lHandle);
							if (!EnumIdentsCallback (pFcn, lHandle, TRUE, pData))
								return S_FALSE;
						}
					}
				}
			}

		} COM_CATCH;
		return S_OK;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Alle Idents einer Ansicht enumerieren (mit Objekttypen)

// Enumeration aller Identifikatoren einer Sicht unter Angabe der vorhandenen 
// Objekttypen
extern "C" inline BOOL EnumIdentsExCallback (
	BOOL (*pFcn)(long, DWORD, void *), long lKey, DWORD dwData, void *pData)
{
	return ((ENUMLONGKEYEXCALLBACK) pFcn)(lKey, dwData, pData);
}

HRESULT DatenBasisObjekt::EnumViewIdentsEx (LPCSTR pcView, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
	Sicht locSicht (DB(), pcView);
	
		return (LRESULT)locSicht.EnumIdentsEx (pFcn, pData, (short)dwData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Elemente dieser Ansicht besorgen
		WTRiASViewItems ViewItems;

			THROW_FAILED_HRESULT(View -> get_ViewItems (ViewItems.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(ViewItems -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
			{
				TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

			WTRiASViewItem Item (V_DISPATCH(&v));

			// alle bekannten Objekttypen durchgehen
				for (const OBJECTTYPE *pEntry = g_rgObjTypes;
					 OBJECTTYPE_Unknown != *pEntry;
					 pEntry++)
				{
				WTRiASObjects Objs;

					if (SUCCEEDED(Item -> get_Objects (*pEntry, Objs.ppi())))
					{
					INT_PTR lHandle = NULL;
					OBJECTTYPE dwTypes = OBJECTTYPE_Unknown;

						if (FAILED(Objs -> get_Handle (&lHandle)) || NULL == lHandle)
							continue;		// Fehler
						if (FAILED(Objs -> get_Types (&dwTypes)) || !(dwTypes & dwData))
							continue;		// Fehler oder nicht passende Objekttypen

					// nur den betreffenden Objekttyp liefern (je Objekttyp einmal rufen)
						if (!EnumIdentsExCallback (pFcn, lHandle, dwTypes & OBJECTTYPEToBits(*pEntry), pData))
							return S_FALSE;
					}
				}
			}

		} COM_CATCH;
		return S_OK;
	}
}

///////////////////////////////////////////////////////////////////////////////
// neue Ansicht erzeugen, bereits existierende Ansicht evtl. löschen
int DatenBasisObjekt::CreateView (LPCSTR pcView)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);

		if (EC_OKAY == S.CreateView()) {
		// neue Ansicht ins Menu einhängen
		ExtDirisWindow *pFrame = GetViewWindow() -> GetFrame();

			TX_ASSERT(NULL != pFrame);
			if (AddItemToSightMenu (pFrame, pFrame -> MainMenu(), pcView) && !(g_dwMenu & HANDLEMENU_MainMenu))
				DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));

		// Die Welt von diesem Ereignis in Kenntnis setzen
		VIEWCREATED VC;

			INITSTRUCT (VC, VIEWCREATED);
			VC.m_pTarget = g_cbNil;
			VC.m_pNewName = (char *)pcView;
			DEXN_SightCreated(VC);

			return CVCreated;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASViews Views;
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_Views (Views.ppi()));

		// festellen, ob Ansicht bereits existiert
			if (SUCCEEDED(Views -> Item (CComVariant(pcView), View.ppi())))
				Views -> Remove (CComVariant(pcView));		// existierende Ansicht erstmal entfernen

		// neue Ansicht erzeugen
			THROW_FAILED_HRESULT(Views -> Add (CComBSTR(pcView), View.ppi()));

		// Notifikation ist bereits in CallBack-von Views.Add erfolgt
			return CVCreated;

		} COM_CATCH_RETURN(CVError);
	}
	return CVError;
}

///////////////////////////////////////////////////////////////////////////////
// Neue Ansicht erzeugen, evtl existierende wiederverwenden
int DatenBasisObjekt::CreateViewOpt (LPCSTR pcView)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);
	ErrCode RC = S.CreateView(false);

		if (RC == WC_EXISTS) return CVExists;
		if (RC == EC_OKAY) {
		// neue Ansicht ins Menu einhängen
		ExtDirisWindow *pFrame = GetViewWindow() -> GetFrame();

			TX_ASSERT(NULL != pFrame);
			if (AddItemToSightMenu (pFrame, pFrame -> MainMenu(), pcView) && !(g_dwMenu & HANDLEMENU_MainMenu))
				DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));

		// Die Welt von diesem Ereignis in Kenntnis setzen
		VIEWCREATED VC;

			INITSTRUCT (VC, VIEWCREATED);
			VC.m_pTarget = g_cbNil;
			VC.m_pNewName = (char *)pcView;
			DEXN_SightCreated(VC);

			return CVCreated;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// evtl. Ansicht besorgen
		WTRiASViews Views;
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_Views (Views.ppi()));

		// festellen, ob Ansicht bereits existiert
			if (SUCCEEDED(Views -> Item (CComVariant(pcView), View.ppi())))
				return CVExists;

		// neue Ansicht erzeugen
			THROW_FAILED_HRESULT(Views -> Add (CComBSTR(pcView), View.ppi()));

		// Notifikation ist bereits in CallBack-von Views.Add erfolgt
			return (CVCreated);

		} catch (_com_error &) {
			return LRESULT(CVError);
		}
	}
	return CVError;
}

///////////////////////////////////////////////////////////////////////////////
// Ansicht löschen
bool DatenBasisObjekt::DeleteView (LPCSTR pcView, bool fDelAttribs)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);

		return (EC_OKAY == S.DelSight(fDelAttribs)) ? true : false;
	
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// Ansicht besorgen
		WTRiASViews Views;
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_Views (Views.ppi()));

		// festellen, ob Ansicht existiert
			if (SUCCEEDED(Views -> Item (CComVariant(pcView), View.ppi())))
				Views -> Remove (CComVariant(pcView));		// existierende Ansicht entfernen
			
			return true;

		} catch (_com_error &) {
			return false;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Identifikator/Objekttyp aus Ansicht entfernen
// iOTypes gibt die zu entfernenden Objekttypen an
// iDefTypes gibt an welche Objekttypen nur dann zu entfernen sind, wenn diese
// eine defaultvis besitzen
bool DatenBasisObjekt::RemoveIdentFromView (
	LPCSTR pcView, LONG lIdent, int iOTypes, int iDefTypes)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pcView);
	bool fResult = S.SatzNr() > 0;		// Sicht existiert
	ErrCode RC = EC_OKAY;

		if (fResult && iOTypes & OTPunkt) {
			RC = S.DelIDfromSight (lIdent, VTPunkt);
			fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
		}
		if (fResult && iOTypes & OTLinie) {
			RC = S.DelIDfromSight (lIdent, VTLinie);
			fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
		}
		if (fResult && iOTypes & OTFlaeche) {
			RC = S.DelIDfromSight (lIdent, VTFlaeche);
			fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
		}
		if (fResult && iOTypes & OTText) {
			RC = S.DelIDfromSight (lIdent, VTText);
			fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
		}
		return fResult;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// Ansicht besorgen
		WTRiASView View;
		WTRiASViewItem ViewItem;
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// zuständiges ViewItem besorgen
			if (FAILED(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi())))
				return false;		// ViewItem eben nicht enthalten

		OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
		OBJECTTYPE rgDefTypes = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(ViewItem -> get_Types (&rgTypes));
			THROW_FAILED_HRESULT(ViewItem -> get_DefaultTypes (&rgDefTypes));

		bool fModified = false;

			if (iOTypes & OTPunkt) {
				if ((rgDefTypes & OBJECTTYPE_Point) || !(iDefTypes & OTPunkt)) {
					rgTypes = (OBJECTTYPE)(rgTypes & ~OBJECTTYPE_Point);
					fModified = true;
				}
			}
			if (iOTypes & OTLinie) {
				if ((rgDefTypes & OBJECTTYPE_Line) || !(iDefTypes & OTLinie)) {
					rgTypes = (OBJECTTYPE)(rgTypes & ~OBJECTTYPE_Line);
					fModified = true;
				}
			}
			if (iOTypes & OTFlaeche) {
				if ((rgDefTypes & OBJECTTYPE_Area) || !(iDefTypes & OTFlaeche)) {
					rgTypes = (OBJECTTYPE)(rgTypes & ~OBJECTTYPE_Area);
					fModified = true;
				}
			}
			if (iOTypes & OTText) {
				if ((rgDefTypes & OBJECTTYPE_Text)|| !(iDefTypes & OTText)) {
					rgTypes = (OBJECTTYPE)(rgTypes & ~OBJECTTYPE_Text);
					fModified = true;
				}
			}
			return fModified ? SUCCEEDED(ViewItem -> put_Types (rgTypes)) : true;

		} catch (_com_error &e) {
			e;
			TX_ASSERT(SUCCEEDED(_COM_ERROR(e)));
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Ansicht umbenennen
bool DatenBasisObjekt::RenameView (LPCSTR pcView, LPCSTR pcNewName)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pcView);

		return (S.SatzNr() > 0 && EC_OKAY == S.Rename(pcNewName)) ? true : false;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle notwendigen Änderungen erfolgen in der Notifikation
			THROW_FAILED_HRESULT(View -> put_Name (CComBSTR(pcNewName)));

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob Ident/OTyp zur Ansicht gehören
bool DatenBasisObjekt::ViewHasIdent (LPCSTR pcView, long lIdent, int iOTypes)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pcView);
	bool fResult = S.SatzNr() > 0;		// Sicht existiert

		if (!fResult) return false;
		
	ErrCode RC = EC_OKAY;

		fResult = false;	
		if (iOTypes & OTPunkt) {
			RC = S.GetIDfromSight (lIdent, NULL, VTPunkt);
			fResult = (RC == EC_OKAY);
		}
		if (!fResult && iOTypes & OTLinie) {
			RC = S.GetIDfromSight (lIdent, NULL, VTLinie);
			fResult = (RC == EC_OKAY);
		}
		if (!fResult && iOTypes & OTFlaeche) {
			RC = S.GetIDfromSight (lIdent, NULL, VTFlaeche);
			fResult = (RC == EC_OKAY);
		}
		if (!fResult && iOTypes & OTText) {
			RC = S.GetIDfromSight (lIdent, NULL, VTText);
			fResult = (RC == EC_OKAY);
		}
		return fResult;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;
		WTRiASViewItem ViewItem;
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// zuständiges ViewItem besorgen
			if (SUCCEEDED(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi()))) {
			OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
			bool fResult = false;

				THROW_FAILED_HRESULT(ViewItem -> get_Types (&rgTypes));
				if (iOTypes & OTPunkt) 
					fResult = rgTypes & OBJECTTYPE_Point ? true : false;
				if (!fResult && iOTypes & OTLinie) 
					fResult = rgTypes & OBJECTTYPE_Line ? true : false;
				if (!fResult && iOTypes & OTFlaeche) 
					fResult = rgTypes & OBJECTTYPE_Area ? true : false;
				if (!fResult && iOTypes & OTText) 
					fResult = rgTypes & OBJECTTYPE_Text ? true : false;

				return fResult;
			}

		} COM_CATCH_RETURN(false);
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Objekttypen einer Objektklasse in einer Ansicht festellen
HRESULT DatenBasisObjekt::GetDefaultObjectTypes (INT_PTR lIdent, OBJECTTYPE *prgType)
{
ResString resDefView (IDS_DEFAULTVISINFO, 40);

	return GetObjectTypes (resDefView, lIdent, prgType);
}

///////////////////////////////////////////////////////////////////////////////
// Objekttypen einer Objektklasse in einer Ansicht festellen
HRESULT DatenBasisObjekt::GetObjectTypes (LPCSTR pcView, INT_PTR lIdent, OBJECTTYPE *prgType)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}

// Ansicht besorgen
WTRiASView View;
WTRiASViewItem ViewItem;
WTRiASObjects Objs;

	if (SUCCEEDED(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()))) {
	// nur, wenn Ansicht auch existiert
		RETURN_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

	// zuständiges ViewItem besorgen
		if (SUCCEEDED(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi()))) {
		OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
		bool fResult = false;

			return ViewItem -> get_Types (prgType);
		} 
	} 
	return S_FALSE;		// Ansicht oder ViewItem in dieser Anscicht nicht gefunden
}

///////////////////////////////////////////////////////////////////////////////
// Identifikator zu einer Ansicht hinzufügen
bool DatenBasisObjekt::AddIdentToView (LPCSTR pcView, long lIdent, int iOTypes)
{
char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return false;		// keine aktive Sicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pcView);
	bool fResult = S.SatzNr() > 0;		// Sicht existiert

		if (!fResult) return false;		// Ansicht existiert nicht

	ErrCode RC = EC_OKAY;

		if (iOTypes & OTPunkt) {
			RC = S.AddIDtoSight (lIdent, NULL, VTPunkt);
			fResult = (RC == EC_OKAY);
		}
		if (fResult && iOTypes & OTLinie) {
			RC = S.AddIDtoSight (lIdent, NULL, VTLinie);;
			fResult = (RC == EC_OKAY);
		}
		if (fResult && iOTypes & OTFlaeche) {
			RC = S.AddIDtoSight (lIdent, NULL, VTFlaeche);
			fResult = (RC == EC_OKAY);
		}
		if (fResult && iOTypes & OTText) {
			RC = S.AddIDtoSight (lIdent, NULL, VTText);
			fResult = (RC == EC_OKAY);
		}
		return fResult;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;
		WTRiASViewItem ViewItem;
		WTRiASObjects Objs;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_TRUE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// zuständiges ViewItem besorgen
			THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_TRUE, CComBSTR(g_cbTRiASViewItem), ViewItem.ppi()));

		OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;
		OBJECTTYPE rgNewType = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(ViewItem -> get_Types (&rgTypes));
			if (iOTypes & OTPunkt) {
				rgTypes = (OBJECTTYPE)(rgTypes | OBJECTTYPE_Point);
				rgNewType = (OBJECTTYPE)(rgNewType | OBJECTTYPE_Point);
			}
			if (iOTypes & OTLinie) {
				rgTypes = (OBJECTTYPE)(rgTypes | OBJECTTYPE_Line);
				rgNewType = (OBJECTTYPE)(rgNewType | OBJECTTYPE_Line);
			}
			if (iOTypes & OTFlaeche) {
				rgTypes = (OBJECTTYPE)(rgTypes | OBJECTTYPE_Area);
				rgNewType = (OBJECTTYPE)(rgNewType | OBJECTTYPE_Area);
			}
			if (iOTypes & OTText) {
				rgTypes = (OBJECTTYPE)(rgTypes | OBJECTTYPE_Text);
				rgNewType = (OBJECTTYPE)(rgNewType | OBJECTTYPE_Text);
			}

			THROW_FAILED_HRESULT(ViewItem -> put_Types (rgTypes));
			return SUCCEEDED(ViewItem -> put_Objects (rgNewType, Objs));

		} COM_CATCH_RETURN(false);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Festellen, ob eine Ansicht zu diesem Projekt gehört
bool DatenBasisObjekt::ProjectHasView (LPCSTR pcView)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrInstall EI (WC_NOTFOUND);
	Sicht S (DB(), pcView);

		return LRESULT(S.SatzNr() > 0);		// Sicht existiert
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen
	WTRiASView View;

		return SUCCEEDED(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
	}
}

// Liefert alle IdentHandles, und die zugehörigen _VisualisierungsTypen_ (!!)
// die in der gegebenen Ansicht sind
bool DatenBasisObjekt::GetViewIdents (LPCSTR pcView, long **ppIDs, short &rNumIDs, short **ppTypes)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	Sicht locSight (DB(), pcView);

		return (EC_OKAY == locSight.GetSightIDs (ppIDs, rNumIDs, ppTypes)) ? true : false;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// ViewItems
		WTRiASViewItems Items;
		LONG lCnt = 0;

			THROW_FAILED_HRESULT(View -> get_ViewItems (Items.ppi()));
			THROW_FAILED_HRESULT(Items -> get_ItemCount (&lCnt));

			TX_TRY(*ppIDs = new long[lCnt]);
			if (NULL == *ppIDs)
				return false;

			if (NULL != ppTypes) {
				TX_TRY(*ppTypes = new short[lCnt]);
				if (NULL == ppTypes)
					return false;
			}

		WUnknown Unk;

			THROW_FAILED_HRESULT(Items -> _NewEnum (Unk.ppi()));

		WEnumVARIANT Enum (Unk);
		CComVariant v;
		long j = 0;

			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&v), NULL); /**/)
			{
				TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

			// alle bekannten Objekttypen durchgehen
			WTRiASViewItem Item (V_DISPATCH(&v));

				for (const OBJECTTYPE *pEntry = g_rgObjTypes;
					 OBJECTTYPE_Unknown != *pEntry;
					 pEntry++)
				{
				WTRiASObjects Objs;

					if (SUCCEEDED(Item -> get_Objects (*pEntry, Objs.ppi())))
					{
					INT_PTR lHandle = NULL;

						if (FAILED(Objs -> get_Handle (&lHandle)) || NULL == lHandle)
							continue;		// Fehler

						TX_ASSERT(j < lCnt);
						(*ppIDs)[j] = lHandle;

					// Anhand der Objekttypen entscheiden, ob Objekte wirklich existieren
					OBJECTTYPE dwTypes = OBJECTTYPE_Unknown;
					short iTypes = 0;

						if (SUCCEEDED(Objs -> get_Types (&dwTypes)))
							iTypes = OBJECTTYPEToVisType((OBJECTTYPE)(dwTypes & *pEntry));
						else
							iTypes = CNativeView::VT_Default;

						if (NULL != ppTypes) 
							(*ppTypes)[j] = iTypes;		// evtl. Objekttyp(en) liefern
					
					// nächster Entry, wenn Objekte dieses Types wirklich existieren
						if (CNativeView::VT_Default != iTypes)
							j++;
					}
				}
			}
			rNumIDs = (short)j;

		} COM_CATCH_RETURN(false);
	}
	return true;
}

size_t GetVisInfoObjectSize (CNativeView::VisType rgType)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return sizeof(PVisInfo);

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return sizeof(LVisInfo);

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return sizeof(FVisInfo);

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return sizeof(TVisInfo);

	default:
	case CNativeView::VT_Default:
		return sizeof(VisInfo);
	}
}

HRESULT CreateVisInfoObject (CNativeView::VisType rgType, VisInfo **ppVis)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		TX_TRY(*ppVis = new PVisInfo);
		break;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		TX_TRY(*ppVis = new LVisInfo);
		break;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		TX_TRY(*ppVis = new FVisInfo);
		break;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		TX_TRY(*ppVis = new TVisInfo);
		break;

	case CNativeView::VT_Default:
		TX_TRY(*ppVis = new VisInfo);
		break;

	default:
		return E_INVALIDARG;
	}
	return (NULL != *ppVis) ? S_OK : E_OUTOFMEMORY;
}

// Konvertieren eines DVisInfo-Objektes in ein VisInfo-Objekt
HRESULT RetrieveVisInfoObject (CNativeView::VisType rgVTyp, DVisInfo *pIVis, 
	VisInfo **ppVI)
{
	try {
	WRawVisInfo Raw (pIVis);
	CComBSTR data;

		THROW_FAILED_HRESULT(Raw -> RetrieveRawData (VisTypeToVISINFOTYPE(rgVTyp), &data));

	SAFEARRAY *psa = NULL;

		THROW_FAILED_HRESULT(VectorFromBstr (data, &psa));

	CSafeArray sa (VT_UI1, psa);
	CSafeArrayLock<unsigned char> lock (sa);

		THROW_FAILED_HRESULT(CreateVisInfoObject(rgVTyp, ppVI));

		TX_ASSERT(GetVisInfoObjectSize(rgVTyp)-sizeof(void *) == lock.Size());
		memcpy ((unsigned char *)(*ppVI) + sizeof(void *), lock, lock.Size());	// ugly hack

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

REFCLSID GetVisInfoCLSID (CNativeView::VisType rgVTyp)
{
	switch (rgVTyp) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return CLSID_PointVisInfo;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return CLSID_LineVisInfo;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return CLSID_AreaVisInfo;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return CLSID_TextVisInfo;

	default:
	case CNativeView::VT_Default:
		return CLSID_DefaultVisInfo;
	}
}

// Konvertieren eines VisInfo-Objektes in ein DVisInfo-Objekt
HRESULT SetVisInfoObject (CNativeView::VisType rgVTyp, VisInfo *pVI, DVisInfo **ppIVis)
{
	try {
	size_t iSize = GetVisInfoObjectSize(rgVTyp)-sizeof(void *);			// sizeof(obj) - sizeof(vtable *)
	CSafeArray sa (VT_UI1, iSize);

		{
		CSafeArrayLock<unsigned char> lock (sa);

			TX_ASSERT(iSize == lock.Size());
			memcpy (lock, ((unsigned char *)pVI) + sizeof(void *), lock.Size());
		}

	CComBSTR data;
	WRawVisInfo Raw (GetVisInfoCLSID(rgVTyp));

		THROW_FAILED_HRESULT(BstrFromVector (sa, &data));
		THROW_FAILED_HRESULT(Raw -> SetRawData (VisTypeToVISINFOTYPE(rgVTyp), data))

	WDVisInfo Vis (Raw);

		*ppIVis = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

bool DatenBasisObjekt::RetrieveVisInfo (
	LPCSTR pcView, long lIdent, short iVTyp, VISINFO &rVI, bool *pfDef)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ErrInstall EI (WC_NOTFOUND);
	Sicht locSicht (DB(), pcView);
			
		return locSicht.RetrieveVisInfo (lIdent, iVTyp, rVI);
	} else
#endif // _FORCE_LEGACY_CODE
	{
	VisInfo *pVI = NULL;

		if (RetrieveVisInfo (pcView, lIdent, iVTyp, &pVI, pfDef)) {
			TX_ASSERT(NULL != pVI);
			pVI -> CopyTo (rVI);
			delete pVI;
			return true;
		}
		return false;
	}
}

bool DatenBasisObjekt::RetrieveVisInfo (
	LPCSTR pcView, long lIdent, short iVTyp, VisInfo **ppVI, bool *piDef)
{
	TX_ASSERT(IsTRiASDBBased());

VisInfo *pVI = NULL;

	try {
	// Ansicht besorgen
	WTRiASView View;
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

	// ViewItem wiederfinden
	WTRiASViewItem ViewItem;
	WDVisInfo Vis;
	OBJECTTYPE rgObjType = VisTypeToOBJECTTYPE((CNativeView::VisType)iVTyp);

		THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi()));
		if (SUCCEEDED(ViewItem -> get_VisInfo (rgObjType, Vis.ppi()))) {
			if (NULL != piDef) {
			// Info besorgen, ob Eintrag defaultvisinfo enthält
			OBJECTTYPE rgDefTypes = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(ViewItem -> get_DefaultTypes (&rgDefTypes));
				*piDef = (rgDefTypes & rgObjType) ? true : false;
			}
			if (NULL == ppVI)
				return true;		// lediglich testen, ob VisInfo existiert
			THROW_FAILED_HRESULT(RetrieveVisInfoObject ((CNativeView::VisType)iVTyp, Vis, ppVI));
		} else
			return false;

	} catch (_com_error &) {
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Alle VisInfos für einen Ident einer Ansicht
ErrCode DatenBasisObjekt::SaveVI (LPCSTR pcView, CIdentifikator &rId)
{
	if (DEX_GetROModeEx(HACTPROJECT)) 
		return EC_OKAY;

char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return EC_FAIL;		// keine aktive Sicht
		pcView = cbBuffer;
	}

long lIdent = rId.Id();
VisInfo *pVI = rId.GetVisInfo(VT_Punkt);
ErrCode RC = EC_OKAY;

	if (NULL != pVI) {
		RC = SaveVI(pVI, pcView, lIdent, VT_Punkt);
		delete pVI;
		if (EC_OKAY != RC)
			return RC;
	}

	pVI = rId.GetVisInfo(VT_Linie);
	if (NULL != pVI) {
		RC = SaveVI(pVI, pcView, lIdent, VT_Linie);
		delete pVI;
		if (EC_OKAY != RC)
			return RC;
	}

	pVI = rId.GetVisInfo(VT_Flaeche);
	if (NULL != pVI) {
		RC = SaveVI(pVI, pcView, lIdent, VT_Flaeche);
		delete pVI;
		if (EC_OKAY != RC)
			return RC;
	}

	pVI = rId.GetVisInfo(VT_Text);
	if (NULL != pVI) {
		RC = SaveVI(pVI, pcView, lIdent, VT_Text);
		delete pVI;
		if (EC_OKAY != RC)
			return RC;
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Eine VisInfo für einen Ident in einer Ansicht 
ErrCode DatenBasisObjekt::SaveVI (
	VisInfo *pVI, LPCSTR pcView, long lIdent, VisType iVTyp, int fBits, bool fTemp)
{
	if (NULL == pVI)
		return EC_NOMEMORY;

// fBits sind nur gesetzt, wenn VisTyp gleich VT_Default ist
	TX_ASSERT(-1 == fBits || CNativeView::VT_Default == iVTyp);
	TX_ASSERT(iVTyp == pVI -> isA());

	if (DEX_GetROModeEx(HACTPROJECT)) 
		return EC_OKAY;

char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return EC_FAIL;		// keine aktive Sicht
		pcView = cbBuffer;
	}
	if (*pcView == '\0' || fTemp)		// temporärer Ident
		return EC_OKAY;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ErrCode RC = EC_OKAY;
	Sicht S (DB(), pcView);	// aktuelle/geforderte Sicht

		DBASSERT (S.AddIDtoSight (lIdent, pVI, fBits));

	// in StandardSicht abspeichern, wenn dort dieser ID 
	// nicht vertreten ist
	ResString rsDefault (IDS_DEFAULTVISINFO, 41);

		if (NULL == pcView || strcmp (rsDefault, pcView)) {
		ErrInstall EI (WC_NOTFOUND);

			if (GetDefaultIDVisInfo (DB(), lIdent, NULL, iVTyp) == WC_NOTFOUND) 
				DBASSERT (AddIDtoDefaultSight (DB(), lIdent, pVI));
		}                                               
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		try {
		// Ansicht besorgen/erzeugen
		WTRiASView View;
		WTRiASObjects Objs;
		WTRiASViewItem ViewItem;
		
			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_TRUE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

		// zuständiges ViewItem besorgen/erzeugen
			THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_TRUE, CComBSTR(g_cbTRiASViewItem), ViewItem.ppi()));
			if (-1 != fBits) {
			// lediglich Sichtzugehörigkeit definieren
				THROW_FAILED_HRESULT(ViewItem -> put_Types (OBJECTTYPE(fBits)));
			} 
			else {
			WDVisInfo Vis;
			OBJECTTYPE rgType = VisTypeToOBJECTTYPE((CNativeView::VisType)iVTyp);

				THROW_FAILED_HRESULT(SetVisInfoObject ((CNativeView::VisType)iVTyp, pVI, Vis.ppi()));
				THROW_FAILED_HRESULT(ViewItem -> put_VisInfo (rgType, Vis));
				THROW_FAILED_HRESULT(ViewItem -> put_Objects (rgType, Objs));
			}

		// in StandardSicht abspeichern, wenn dort dieser ID nicht vertreten ist
		ResString rsDefault (IDS_DEFAULTVISINFO, 41);

			if (NULL == pcView || strcmp (rsDefault, pcView)) {
				if (!RetrieveVisInfo (rsDefault, lIdent, iVTyp)) 	// ebenfalls in DefaultSicht speichern
					SaveVI (pVI, rsDefault, lIdent, iVTyp, fBits, fTemp);	// evtl. Fehler ignorieren
			}                                               

		} catch (_com_error &) {
			return EC_FAIL;
		}
	}
	return EC_OKAY;
}

// piDef: die ObjTypen, die zwar vertreten aber nicht definiert sind
// piGot: die wirklich definierten ObjTypen
bool DatenBasisObjekt::GetCompleteVisInfo (
	LPCSTR pcView, long lIdent, VisInfo **ppVI, int iOTypes, 
	HPALETTE hPal, int *piGot, int *piDef)
{
	if (NULL != piGot) *piGot = 0;		// Resultate initialisieren
	if (NULL != piDef) *piDef = 0;

	if (iOTypes & TPPunkt) {
	bool fDefault = false;

		if (RetrieveVisInfo (pcView, lIdent, VT_Punkt, &ppVI[0], &fDefault)) {
			if (NULL != piDef && fDefault)
				*piDef |= TPPunkt;
			if (NULL != piGot)
				*piGot |= TPPunkt;
			if (NULL != hPal) ExpandPalette (hPal, ppVI[0]);
		}
	}
	if (iOTypes & TPLinie) {
	bool fDefault = false;

		if (RetrieveVisInfo (pcView, lIdent, VT_Linie, &ppVI[1], &fDefault)) {
			if (NULL != piDef && fDefault)
				*piDef |= TPLinie;
			if (NULL != piGot)
				*piGot |= TPLinie;
			if (NULL != hPal) ExpandPalette (hPal, ppVI[1]);
		}
	}
	if (iOTypes & TPFlaeche) {
	bool fDefault = false;

		if (RetrieveVisInfo (pcView, lIdent, VT_Flaeche, &ppVI[2], &fDefault)) {
			if (NULL != piDef && fDefault)
				*piDef |= TPFlaeche;
			if (NULL != piGot)
				*piGot |= TPFlaeche;
			if (NULL != hPal) ExpandPalette (hPal, ppVI[2]);
		}
	}
	if (iOTypes & TPText) {
	bool fDefault = false;

		if (RetrieveVisInfo (pcView, lIdent, VT_Text, &ppVI[3], &fDefault)) {
			if (NULL != piDef && fDefault)
				*piDef |= TPText;
			if (NULL != piGot)
				*piGot |= TPText;
			if (NULL != hPal) ExpandPalette (hPal, ppVI[3]);
		}
	}
	return true;
}

bool DatenBasisObjekt::SetCompleteVisInfo (
	LPCSTR pcView, long lIdent, VisInfo **ppVI, int iOTypes)
{
	if (ppVI[0] != NULL && iOTypes & TPPunkt) 
	{
		if (EC_OKAY != SaveVI (ppVI[0], pcView, lIdent, VT_Punkt)) 
			return false;
	}
	if (ppVI[1] != NULL && iOTypes & TPLinie) 
	{
		if (EC_OKAY != SaveVI (ppVI[1], pcView, lIdent, VT_Linie)) 
			return false;
	}
	if (ppVI[2] != NULL && iOTypes & TPFlaeche)
	{
		if (EC_OKAY != SaveVI (ppVI[2], pcView, lIdent, VT_Flaeche)) 
			return false;
	}
	if (ppVI[3] != NULL && iOTypes & TPText)
	{
		if (EC_OKAY != SaveVI (ppVI[3], pcView, lIdent, VT_Text)) 
			return false;
	}
	return true;
}

bool DatenBasisObjekt::GetCompleteDefaultVisInfo (
	long lIdent, VisInfo **ppVI, int iOTypes, 
	HPALETTE hPal, int *piGot, int *piDef)
{
// nur die VisInfo nachladen, die noch nicht vorhanden ist
	if (iOTypes & TPPunkt && NULL != ppVI[0])	iOTypes &= ~TPPunkt;
	if (iOTypes & TPLinie && NULL != ppVI[1])	iOTypes &= ~TPLinie;
	if (iOTypes & TPFlaeche && NULL != ppVI[2])	iOTypes &= ~TPFlaeche;
	if (iOTypes & TPText && NULL != ppVI[3])	iOTypes &= ~TPText;

ResString rsDefault (IDS_DEFAULTVISINFO, 41);

	return GetCompleteVisInfo (rsDefault, lIdent, ppVI, iOTypes, hPal, piGot, piDef);
}

bool DatenBasisObjekt::SetCompleteDefaultVisInfo (
	long lIdent, VisInfo **ppVI, int iOTypes)
{
ResString rsDefault (IDS_DEFAULTVISINFO, 41);

	return SetCompleteVisInfo (rsDefault, lIdent, ppVI, iOTypes);
}

///////////////////////////////////////////////////////////////////////////////
// Palette einer Ansicht erzeugen
HPALETTE DatenBasisObjekt::GetViewPalette (
	LPCSTR pcView, long *pIDs, short iNumIDs, short *pTypes)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);	// aktuelle/geforderte Sicht

		return S.GetPalette();
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	SightPalette SP;

		{
		CmpColorCreator CCC(SP);
		CTable t(SP);

			if (NULL == pIDs) {
				TX_ASSERT(0 == iNumIDs && NULL == pTypes);

			long *Targets = NULL;
			short *iTypes = NULL;
			short numTargets = 0;

			// Farben aller Identifikatoren holen
				GetViewIdents (pcView, &Targets, numTargets, &iTypes);
				for (int i = 0; i < numTargets; i++) {
				VisInfo *pVI = NULL;

					RetrieveVisInfo (pcView, Targets[i], iTypes[i], &pVI);	// VisInfo holen
					SP.AddToSightPalette (t, CCC, pVI);
					DELETE_OBJ (pVI);
				}
				DELETE_OBJ (Targets);
				DELETE_OBJ (iTypes);
			}	// letzte Farbe in Baum einfügen
			else {
			// die Infos über die Ansicht liegen bereits vor 
				TX_ASSERT(0 != iNumIDs && NULL != pTypes);

			// Farben aller Identifikatoren holen
				for (int i = 0; i < iNumIDs; i++) {
				VisInfo *pVI = NULL;

					RetrieveVisInfo (pcView, pIDs[i], pTypes[i], &pVI);	// VisInfo holen
					SP.AddToSightPalette (t, CCC, pVI);
					DELETE_OBJ (pVI);
				}
			}
		}	// Creator goes out of scope

		return SP.GetPalette();	// Palette generieren
	}
}

#if defined(_FORCE_LEGACY_CODE)
ErrCode DatenBasisObjekt::SetViewAttribs (
	LPCSTR pcView, long lMerkmale, long lRelationen)
{
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);	// aktuelle/geforderte Sicht

		return S.SetAttribs (lMerkmale, lRelationen);	
	}
	return EC_OKAY;
}

ErrCode DatenBasisObjekt::GetViewAttribs (
	LPCSTR pcView, long *plMerkmale, long *plRelationen)
{
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	Sicht S (DB(), pcView);	// aktuelle/geforderte Sicht

		return S.GetAttribs (plMerkmale, plRelationen);	
	}
	return EC_OKAY;
}

#endif // _USE_LEGACY_CODE

HRESULT CopyProperties (ITRiASProperties *pISrcProps, ITRiASProperties *pIDestProps)
{
WEnumVARIANT Enum;
CComVariant v;

	RETURN_FAILED_HRESULT(pISrcProps -> _NewEnum (Enum.ppu()));
	for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
		TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

	WTRiASProperty Prop (V_DISPATCH(&v));
	WTRiASProperty NewProp;
	CComBSTR bstrName;

		RETURN_FAILED_HRESULT(Prop -> get_Name (CLEARED(&bstrName)))
		RETURN_FAILED_HRESULT(pIDestProps -> Add (CComVariant(bstrName), NewProp.ppi()));

	CComVariant vVal;
	PROPERTY_TYPE rgType = PROPERTY_TYPE_Normal;

		if (SUCCEEDED(Prop -> GetValueAndType (&vVal, &rgType))) 
		{
			RETURN_FAILED_HRESULT(NewProp -> SetValueAndType (vVal, rgType));
		}

	CComBSTR bstrDesc;

		if (SUCCEEDED(Prop -> get_Description (CLEARED(&bstrDesc)))) 
		{
			RETURN_FAILED_HRESULT(NewProp -> put_Description (bstrDesc));
		}
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::SetViewAttribs (
	LPCSTR pcViewSrc, LPCSTR pcViewDest, ITRiASProperties *pIProps, ITRiASRelations *pIRels)
{
#if defined(_FORCE_LEGACY_CODE)
	if (IsTRiASDBBased()) 
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen
	WTRiASView ViewDest, ViewSrc;

		if (FAILED(m_Prj -> get_View (CComBSTR(pcViewDest), VARIANT_FALSE, ViewDest.ppi())))
			return S_FALSE;
		if (FAILED(m_Prj -> get_View (CComBSTR(pcViewSrc), VARIANT_FALSE, ViewSrc.ppi())))
			return S_FALSE;

	// Properties kopieren
		if (NULL != pIProps) {
		WTRiASProperties Props;

			RETURN_IMPL_AND_FAILED(WTRiASPropertyBase(ViewDest) -> get_Properties (Props.ppi()));
			RETURN_FAILED_HRESULT(CopyProperties (pIProps, Props));
		}

	// Properties der einzelnen ViewItems mit kopieren
	WTRiASViewItems ViewItemsDest, ViewItemsSrc;

		RETURN_FAILED_HRESULT(ViewDest -> get_ViewItems (ViewItemsDest.ppi()));
		RETURN_FAILED_HRESULT(ViewSrc -> get_ViewItems (ViewItemsSrc.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		RETURN_FAILED_HRESULT(ViewItemsSrc -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			TX_ASSERT(SUCCEEDED(v.ChangeType (VT_DISPATCH)));

		WTRiASViewItem ViewItemSrc (V_DISPATCH(&v));
		WTRiASViewItem ViewItemDest;
		
			if (FAILED(ViewItemsDest -> Item (v, ViewItemDest.ppi()))) 
				continue;		// existiert nicht in der Zielansicht, also weiter

		WTRiASProperties PropsSrc, PropsDest;
		
			RETURN_FAILED_HRESULT(WTRiASPropertyBase(ViewItemSrc) -> get_Properties (PropsSrc.ppi()));
			RETURN_FAILED_HRESULT(WTRiASPropertyBase(ViewItemDest) -> get_Properties (PropsDest.ppi()));
			CopyProperties (PropsSrc, PropsDest);
		}
		
	// Relationen umhängen
		if (NULL != pIRels) 
			RETURN_IMPL_AND_FAILED(ViewDest -> put_Relations (pIRels));
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::GetViewAttribs (
	LPCSTR pcView, ITRiASProperties **ppIProps, ITRiASRelations **ppIRels)
{
#if defined(_FORCE_LEGACY_CODE)
	if (IsTRiASDBBased()) 
#endif // _USE_LEGACY_CODE
	{
	// Ansicht besorgen
	WTRiASView View;

		TX_ASSERT(IsTRiASDBBased());
		if (SUCCEEDED(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()))) {
			RETURN_IMPL_AND_FAILED(WTRiASPropertyBase(View) -> get_Properties (ppIProps));
			RETURN_IMPL_AND_FAILED(View -> get_Relations (ppIRels));
		}
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::MoveViewAttribs (LPCSTR pcViewDest, LPCSTR pcViewSrc)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	ErrCode RC = EC_OKAY;
	Sicht S (DB(), pcViewDest);	// aktuelle/geforderte Sicht
	Sicht Src (DB(), pcViewSrc);

		return EC_OKAY == S.MoveAttribs (&Src) ? S_OK : E_FAIL;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	WTRiASProperties Props;
	WTRiASRelations Rels;

		if (SUCCEEDED(GetViewAttribs(pcViewSrc, Props.ppi(), Rels.ppi())))
			RETURN_FAILED_HRESULT(SetViewAttribs(pcViewSrc, pcViewDest, Props, Rels));
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::WriteBackVisInfos()
{
char cbBuffer[SIGHTMENUITEM+1];

	GetActiveSightName(cbBuffer, sizeof(cbBuffer));

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	ErrCode EC = Idents().WriteBack (DB(), cbBuffer);

		return (EC_OKAY == EC) ? S_OK : HRESULT_FROM_ERRCODE(EC);
	} else
#endif // #if defined(_FORCE_LEGACY_CODE)
	{
		TX_ASSERT(IsTRiASDBBased());

	CTable t(Idents().IdentTree());

		for (t.First(); t.Valid(); t.Next()) {
		CIdentifikatorLock l(t);

			if (!l) continue;
			if (l -> isModified()) {
				THROW_FAILED_HRESULT(WriteBackVisInfo (l, cbBuffer, VT_Punkt));
				THROW_FAILED_HRESULT(WriteBackVisInfo (l, cbBuffer, VT_Linie));
				THROW_FAILED_HRESULT(WriteBackVisInfo (l, cbBuffer, VT_Flaeche));
				THROW_FAILED_HRESULT(WriteBackVisInfo (l, cbBuffer, VT_Text));
				l -> UnModified();	// nicht mehr modifiziert
			}
		}
	}
	return S_OK;
}

namespace {
	inline Color ConvertPalette (Color &rC, HPALETTE hPal)
	{
		if (hPal && 0 != rC.Reserved()) {
			::GetPaletteEntries (hPal, rC.Red(), 1, (PALETTEENTRY *)&rC);
			rC.Reserved() = 0;
		}
		return rC;
	}
}

HRESULT DatenBasisObjekt::WriteBackVisInfo (CIdentifikator *pId, LPCSTR pcView, VisType iVTyp)
{
	TX_ASSERT(IsTRiASDBBased());
	TX_ASSERT(NULL != pId);

	if (!pId -> hasVI (iVTyp))
		return S_FALSE;		// dieser Objekttyp ist in der aktuellen Ansicht nicht vertreten

VisInfo *pVI = (VisInfo *)pId -> VI (iVTyp).Copy();
VisType ilocVTyp = pVI -> isA();

// Fläche oder Punkt: MainColor konvertieren
	ConvertPalette (pVI -> PrimColor(), pId -> hPal());

// wenn Ident Punkt, 2. Farbe konvertieren
	if (ilocVTyp == VT_Punkt) 
		ConvertPalette (((PVisInfo *)pVI) -> SecColor(), pId -> hPal());

// wenn Ident Fläche, FüllFarbe konvertieren
	if (ilocVTyp == VT_Flaeche)
		ConvertPalette (((FVisInfo *)pVI) -> SecColor(), pId -> hPal());

ErrCode RC = SaveVI (pVI, pcView, pId -> Id(), iVTyp, -1, pId -> isTemp());

	DELETE_OBJ(pVI);
	return (EC_OKAY == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
}

///////////////////////////////////////////////////////////////////////////////
// Liefert evtl. Namen der Ursprungsdatenquelle der Ansicht 
HRESULT DatenBasisObjekt::GetRelatedDataSourceName (RELATEDDATASOURCENAME *pRDSN)
{
HRESULT hr = S_FALSE;		// default: not found anything

	TX_ASSERT(IsTRiASDBBased());
	USES_CONVERSION;
	COM_TRY {
	// Ansicht besorgen
	WTRiASView View;
	CComBSTR bstrDSName;

		if (FAILED(m_Prj -> get_View (CComBSTR(pRDSN -> pcTargetName), VARIANT_FALSE, View.ppi())))
			return S_FALSE;

		hr = View -> get_RelatedDataSourceName (&bstrDSName);
		if (SUCCEEDED(hr)) {
		size_t iToCopy = min(pRDSN -> iLen-1, bstrDSName.Length());

			strncpy (pRDSN -> pDataSourceName, OLE2A(bstrDSName), iToCopy);
			pRDSN -> pDataSourceName[iToCopy] = '\0';
			pRDSN -> iLen = iToCopy;
		}

	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Liefern Unique- Identifikator, MerkmalsCode und RelationsCode 
long DatenBasisObjekt::GetUniqueICode (HPROJECT hPr, BOOL fSystem)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetUniqueICode (fSystem);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
	
	INT_PTR lIdent = NULL;

		COM_TRY {
		WCookieHelper Helper (CLSID_CookieHelper);
		INT_PTR lCookieHolder = 0L;

			THROW_FAILED_HRESULT(Helper -> GetCookieHolder (CComBSTR(g_cbObjectsMap), &lCookieHolder));
			THROW_FAILED_HRESULT(Helper -> GetNextCookie (lCookieHolder, &lIdent));

		} COM_CATCH_RETURN(-1);

// neuen Ident immer vom Projekt geben lassen	
//		if (HACTPROJECT != hPr) {
//			if (fSystem)
//				lIdent = GetUniqueLong (IDS_HDRUNIQUEICODE, FIRSTUNIQUEICODEX);
//
//			lIdent = GetUniqueLong (IDS_HDRUNIQUEICODE, FIRSTUNIQUEICODEX);
//		
//		} else 
//			lIdent = DB(hPr).GetUniqueICode (fSystem);

		if (0 == lIdent || -1 == lIdent)
			return 0L;

#if _TRiAS_VER >= 0x0500
	// ab TRiAS5 liefert DEX_GetUniqueSysICode lediglich den nächsten freien Wert
	// ohne diesen auch als Objektklasse zu definieren
		if (fSystem)
			return lIdent;
#endif _TRiAS_VER >= 0x0500

		if (NULL == hPr)
			hPr = DEX_GetDataSourceHandle();

	IDENTFROMCLASS IFC;
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, "[%lx]", lIdent);	// Unique Ident als OKS verwenden
		INITSTRUCT(IFC, IDENTFROMCLASS);
		IFC.pcClass = cbBuffer;
		IFC.fCreateNew = true;

	HRESULT hr = DEX_GetIdentFromClassEx (hPr, IFC);

		if (SUCCEEDED(hr)) 
			return IFC.ulIdent;	

		return -1L;
	}
}

long DatenBasisObjekt::GetUniqueMCode (HPROJECT hPr, BOOL fSystem)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetUniqueMCode (fSystem);
	} else
#endif // _FORCE_LEGACY_CODE
	{
	INT_PTR lCookie = 0L;

		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
			if (HACTPROJECT == hPr) {
			WCookieHelper Helper (CLSID_CookieHelper);
			INT_PTR lCookieHolder = 0L;

				THROW_FAILED_HRESULT(Helper -> GetCookieHolder (CComBSTR(g_cbFeatureMap), &lCookieHolder));
				THROW_FAILED_HRESULT(Helper -> GetNextCookie (lCookieHolder, &lCookie));
				return lCookie;

//				if (fSystem) 
//					return GetUniqueLong (IDS_HDRUNIQUESYSMCODE, FIRSTUNIQUESYSMCODE_PRJ);
//
//				return GetUniqueLong (IDS_HDRUNIQUEMCODE, FIRSTUNIQUEMCODE_PRJ);
			} else {
				return DB(hPr).GetUniqueMCode (fSystem);
			}
		} COM_CATCH_RETURN(-1L);
		return lCookie;
	}
}

long DatenBasisObjekt::GetUniqueRCode (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetUniqueRCode();
	} else
#endif // _FORCE_LEGACY_CODE
	{
	INT_PTR lCookie = 0L;

		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WCookieHelper Helper (CLSID_CookieHelper);
		INT_PTR lCookieHolder = 0L;

			THROW_FAILED_HRESULT(Helper -> GetCookieHolder (CComBSTR(g_cbRelationMap), &lCookieHolder));
			THROW_FAILED_HRESULT(Helper -> GetNextCookie (lCookieHolder, &lCookie));
			return lCookie;

		} COM_CATCH_RETURN(-1);
		return lCookie;
//		return GetUniqueLong (IDS_HDRUNIQUERCODE, FIRSTUNIQUERCODE);
	}
}

long DatenBasisObjekt::GetUniqueTempONr (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().GetUniqueTempONr();
	} else
#endif // _FORCE_LEGACY_CODE
	{
	INT_PTR lCookie = 0L;

		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WCookieHelper Helper (CLSID_CookieHelper);
		INT_PTR lCookieHolder = 0L;

			THROW_FAILED_HRESULT(Helper -> GetCookieHolder (CComBSTR(g_cbObjectMap), &lCookieHolder));
			THROW_FAILED_HRESULT(Helper -> GetNextCookie (lCookieHolder, &lCookie));
			return lCookie;

		} COM_CATCH_RETURN(-1);
		return lCookie;
//		return GetUniqueLong (IDS_HDRUNIQUETEMPON, FIRSTUNIQUETEMPON);
	}
}

#if defined(_FORCE_LEGACY_CODE)
long DatenBasisObjekt::GetUniqueLong (unsigned int resID, long lFirstCode)
{
	TX_ASSERT(IsTRiASDBBased());

GEODBHDRENTRYEX HE;
ResString resStr (resID, 17);
char cbBuffer[HDRENTRYTEXTLEN+1];
unsigned long lEntry = (unsigned long)lFirstCode;	// Entry existiert noch nicht

	INITSTRUCT (HE, GEODBHDRENTRYEX);
	strncpy (HE.hdrKey, resStr.Addr(), HDRKEYLENGTH);
	HE.lphdrText = cbBuffer;
	HE.hdrTextLen = HDRENTRYTEXTLEN;
	if (EC_OKAY == DEX_ReadGeoDBHdrEntry(HE)) 
		lEntry = strtoul(HE.lphdrText, NULL, 10);

// Eintrag wegschreiben
	_ltoa (lEntry +1, cbBuffer, 10);

	HE.lphdrText = cbBuffer;
	HE.hdrTextLen = strlen (cbBuffer);
	HE.dwFlags = HEADER_SYSTEMRO;
	if (EC_OKAY != DEX_WriteGeoDBHdrEntry(HE))
		lEntry = -1L;

	return lEntry;		// Unique Wert liefern
} 
#endif // defined(_FORCE_LEGACY_CODE)

HPROJECT DatenBasisObjekt::GetIdentParentHandle (INT_PTR lIdent, BOOL fMayFail)
{
HPROJECT hPr = NULL;

	COM_TRY {
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));
		THROW_FAILED_HRESULT(GetDatabaseOrProjectHandle (Objs, &hPr));

	} COM_CATCH_EX(e) {
		e;	// UNUSED(e)
		if (!fMayFail) {
			COM_TRACECOMERROR(e);
			COM_ASSERT_EX(e);
		}
		return HACTCONNECTION;
	}
	return hPr;
}

HPROJECT DatenBasisObjekt::GetIdentDBHandle (INT_PTR lIdent, HPROJECT hPr)
{
//	TX_ASSERT(HACTPROJECT != hPr);	// muß GeoDBHandle sein
	if (HACTCONNECTION != hPr) return hPr;
	if (NULL == lIdent) return NULL;

	return GetIdentParentHandle (lIdent);
}

HPROJECT DatenBasisObjekt::GetObjectDBHandle (INT_PTR lONr, HPROJECT hPr)
{
	TX_ASSERT(HACTPROJECT != hPr);	// muß GeoDBHandle sein
	if (HACTCONNECTION != hPr) return hPr;
	if (NULL == lONr || -1 == lONr) 
		return NULL;

HPROJECT hParentPr = NULL;

	COM_TRY {
	WTRiASObject Obj;

		THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj))
		THROW_FAILED_HRESULT(GetDatabaseHandle (Obj, &hParentPr));

	} COM_CATCH_RETURN(NULL);
	return hParentPr;
}

HPROJECT DatenBasisObjekt::GetFeatureDBHandle (INT_PTR lMCode, HPROJECT hPr)
{
	TX_ASSERT(HACTPROJECT != hPr);	// muß GeoDBHandle sein
	if (HACTCONNECTION != hPr) return hPr;
	if (NULL == lMCode || -1 == lMCode) 
		return NULL;

HPROJECT hParentPr = NULL;

	COM_TRY {
	WTRiASFeature Feat;

		if (SUCCEEDED((GetFeatureFromMap (lMCode, Feat)))) {
		// MCode ist bereits einer Datenquelle zugeordnet
			THROW_FAILED_HRESULT(GetDatabaseHandle (Feat, &hParentPr));
		}

	} COM_CATCH_RETURN(NULL);
	return hParentPr;
}

HPROJECT DatenBasisObjekt::GetObjectProject (ITRiASObject *pIObj)
{
	if (NULL == pIObj) 
		return NULL;

HPROJECT hParentPr = NULL;

	if (FAILED(GetDatabaseHandle (pIObj, &hParentPr)))
		return NULL;
	return hParentPr;
}

///////////////////////////////////////////////////////////////////////////////
// Neue Objektklasse hinzufügen/Visualisierung übernehmen
bool DatenBasisObjekt::AddNewIdent (
	long lNewIdent, HPALETTE hPalette, short iFlags, short iVTyp, long lTargetId)
{
	SetLastError(S_OK);

CTable tID (Idents().IdentTree());
short oldDrawType = DT_Normal;
bool oldLoadInfo = false;
bool oldTempInfo = false;
bool fAllLoaded = false;
bool fTempFlag = iFlags & ANI_Temp;
VisInfo *newpVI[4];

// wenn BezugsIdent nicht gegeben ist, dann neuen Ident verwenden
	if (lTargetId == -1L) 
		lTargetId = lNewIdent;

	memset (newpVI, '\0', 4 * sizeof(VisInfo *));

// Id im IdTree suchen
short iToPaint = iVTyp;
short iOTypes = iVTyp;
bool fMovedAway = false;
//short fSearchAble = iVTyp;
long lPCnt = 0, lLCnt = 0, lFCnt = 0, lTCnt = 0, lKCnt = 0;
CIdentObjects *pObjs = NULL;
long lObjNameCode = 0;

	if (tID.Find (&lTargetId)) {		// Id gibt es schon: löschen
	CIdentifikatorLock l(tID);

		TX_ASSERT(NULL != (CIdentifikator *)l);

	CIdentifikator *pId = (CIdentifikator *)l;

		oldDrawType = pId -> DType();	// DrawType merken
		oldLoadInfo = pId -> loaded();
		oldTempInfo = pId -> isTemp();

		if (lTargetId == lNewIdent) {
			iOTypes = pId -> GetOTypes() | iVTyp;
			iToPaint = pId -> toPaint() | iVTyp;
		} else {
			iOTypes = pId -> GetOTypes() & iVTyp;
			iToPaint = pId -> toPaint() & iVTyp;
		}
		fAllLoaded = pId -> AreAllLoaded();
		fMovedAway = pId ->  MovedAway();
//		fSearchAble = pId -> GetSearchAble();
					
	// alter Ident ist nicht mehr vollständig
		if (fTempFlag) {
			pId -> MovedAway (true);
			if (lNewIdent == lTargetId)
				fMovedAway = true;
		}

		lPCnt = pId -> GetPointCount();
		lLCnt = pId -> GetLineCount();
		lFCnt = pId -> GetAreaCount();
		lTCnt = pId -> GetTextCount();
		lKCnt = pId -> GetComplexCount();
		pObjs = pId -> DetachObjList();

		lObjNameCode = pId -> GetObjNameFeatureCode();
	}
	
// VisInfo von neuem Ident holen, wenn dieser bekannt ist, ansonsten in
// Sicht nachsehen
char cbView[MAXVIEWNAMESIZE+1];
short iExistOTypes = 0;
short fSpec = 0;

	DEX_GetActiveSight (cbView);	// aktuellen Sichtnamen holen
	if (tID.Find (&lNewIdent)) {
	CIdentifikatorLock l(tID);

		if (l) fSpec = l -> GetCompleteVisInfo ((VisInfo **)newpVI, iToPaint, &iExistOTypes);
	} 
	if (iToPaint != (iExistOTypes & iToPaint) && cbView[0] != '\0') 
		GetCompleteVisInfo (cbView, lNewIdent, (VisInfo **)newpVI, iToPaint);

// wenn immer noch nichts ist, dann in DefaultSicht nachsehen	
	GetCompleteDefaultVisInfo (lNewIdent, (VisInfo **)newpVI, iToPaint|iVTyp);
	fSpec |= MakeCompleteNewVisInfo ((VisInfo **)newpVI, iToPaint|iVTyp, true); // <<-- true für CreateObject ?? (#hk950603)

// bei Bedarf Ident zur aktuellen Sicht hinzufügen
	if ('\0' != cbView[0] && iFlags & ANI_AddToView) {
	// neue VisInfo wegschreiben
	ErrCode EC = EC_OKAY;

		if (fSpec == TPAll && NULL != newpVI[0]) {	// nur DefaultInfo schreiben
			EC = AddIdentToView (cbView, lNewIdent, TPAll) ? EC_OKAY : EC_FAIL;
		} else {		// nur nicht DefaultSätze schreiben
			if (!(fSpec & TPPunkt) && newpVI[0]) 
				EC = SaveVI (newpVI[0], cbView, lNewIdent, VT_Punkt);
			if (!(fSpec & TPLinie) && EC == EC_OKAY && newpVI[1]) 
				EC = SaveVI (newpVI[1], cbView, lNewIdent, VT_Linie);
			if (!(fSpec & TPFlaeche) && EC == EC_OKAY && newpVI[2]) 
				EC = SaveVI (newpVI[2], cbView, lNewIdent, VT_Flaeche);
			if (!(fSpec & TPText) && EC == EC_OKAY && newpVI[3]) 
				EC = SaveVI (newpVI[3], cbView, lNewIdent, VT_Text);

		// Ident/Typ ohne VisInfo wegschreiben bzw. DefaultSatz löschen
			if (EC == EC_OKAY) {
				if (fSpec != 0)
					AddIdentToView (cbView, lNewIdent, fSpec);
				else
					RemoveIdentFromView (cbView, lNewIdent, TPAll, TPAll);
			}
		}
	}
	Idents().DeleteIdent (lNewIdent);		// Ident löschen

// Identifikatoreintrag in Baum generieren
	if (Idents().AddIdent (*this, lNewIdent, newpVI, fSpec, hPalette) && tID.Find (&lNewIdent)) {
	CIdentifikatorLock l (tID);

		TX_ASSERT(NULL != (CIdentifikator *)l);

	CIdentifikator *pId = (CIdentifikator *)l;

	// LoadStatus von altem Identifikator übernehmen
		if (!(iFlags & ANI_UnloadComplete) && (oldLoadInfo || fTempFlag))
			pId -> Load();
		else
			pId -> UnLoad();
		if (!(iFlags & ANI_Unload) && (fAllLoaded || fTempFlag))
			pId -> AllLoaded();
		else
			pId -> NotAllLoaded();
		
	// wenn der alte oder der neue Ident temp ist, dann muß es 
	// der neue auf jeden Fall auch sein
		if (oldTempInfo || fTempFlag)
			pId -> Temp();
		else
			pId -> Perm();
		
		pId -> DType() = oldDrawType;
		pId -> SetSpecial (fSpec|pId -> GetSpecial());
		pId -> SetOTypes (iOTypes|pId -> GetOTypes());
//		pId -> SetSearchAble (fSearchAble);
		if (fTempFlag && lNewIdent == lTargetId)
			pId -> MovedAway (fMovedAway);

	// ggf. Objektzähler korrigieren
		if (iFlags & ANI_CountObjects) {
			if (iVTyp & MODIDENT_PUNKT)
				++lPCnt;
			if (iVTyp & MODIDENT_LINIE)
				++lLCnt;
			if (iVTyp & MODIDENT_FLAECHE)
				++lFCnt;
			if (iVTyp & MODIDENT_TEXT)
				++lTCnt;
		}
		pId -> InitPointCount (lPCnt);
		pId -> InitLineCount (lLCnt);
		pId -> InitAreaCount (lFCnt);
		pId -> InitTextCount (lTCnt);
		pId -> InitComplexCount (lKCnt);

		pId -> SetObjNameFeatureCode (lObjNameCode);

		if (iFlags & ANI_Unload|ANI_UnloadComplete) {
		// neuzeichnen garantieren
			ResetLoadedRects();		// nichts ist mehr so, wie es war
		} else {
		// bei Unload* Objektliste neu erzeugen
			TX_VERIFY (NULL == pId -> AttachObjList (pObjs));
			pObjs = NULL;
		}
	}
	DELETE_OBJ(pObjs);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt doppeln
bool DatenBasisObjekt::CloneObject(HPROJECT hPr, CLONEOBJECT *pCloneObj)
{
	_ASSERTE(HACTPROJECT != hPr);

// Zieldatenquelle sicherstellen
	if (HACTCONNECTION == hPr) {
		if (0 != pCloneObj -> lNewIdent)
			hPr = GetIdentDBHandle (pCloneObj -> lNewIdent, hPr);
		else
			hPr = GetObjectDBHandle(pCloneObj -> lONrToCopy);
	}
	_ASSERTE(HACTCONNECTION != hPr);

	return SUCCEEDED(::CloneObject (hPr, pCloneObj -> lONrToCopy, 
		pCloneObj -> lNewIdent, &pCloneObj -> lNewONr));
}


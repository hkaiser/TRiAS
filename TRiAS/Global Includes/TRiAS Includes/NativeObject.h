///////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeObject.h | Declaration of the <c CNativeObject> class

#if !defined(_NATIVEOBJECT_H__6A40D9C3_B054_11D1_859E_00600875138A__INCLUDED_)
#define _NATIVEOBJECT_H__6A40D9C3_B054_11D1_859E_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <risdb.h>
#include <xtension.h>

#include <ospace/std/vector>

typedef vector<double> double_v;
typedef vector<double>::iterator double_i;

typedef vector<unsigned long> ulong_v;
typedef vector<unsigned long>::iterator ulong_i;

namespace trias_nativeobject {

#if !defined(OUREL)
// Makros für RelationsTypen --------------------------------------------------
#define UREL	0x01				// Relation von Unten
#define OREL	0x02				// Relation von Oben (ist KomplexObjekt)
#define OUREL	(OREL|UREL)			// beides

#define GREL	0x04				// gleichrangige Relation existiert

#define BRELA	0x08				// hat BegleitObjekt
#define BRELP	0x10				// ist BegleitObjekt
#define BRELAP	(BRELA|BRELP)		// beides

#define HREL(x) ((x)&GREL)			// Zugriffsfunktionen
#define VREL(x) ((x)&OUREL)
#define VRELO(x) ((x)&OREL)
#define VRELU(x) ((x)&UREL)
#define KREL(x) ((x)&(OUREL|GREL))	// Komplexrelationen
#define BREL(x) ((x)&BRELAP)		// Begleitrelationen
#endif // OUREL

#if !defined(OTPunkt)
#define OTPunkt			0x01
#define OTLinie			0x02
#define OTFlaeche		0x04
#define OTText			0x08
#define OTAll			(OTPunkt|OTLinie|OTFlaeche|OTText)
#define OTKO			0x10
#define OTSachObjekt	0x20	// zusätzliches Flag (BLOB - Flag)
#endif // !defined(OTPunkt)

///////////////////////////////////////////////////////////////////////////////
// StatusBits im ObjektSatz 
#define SB_TEXTOBJ		0x01
#define SB_TEXTOBJIND	0x02
#define SB_SACHOBJ		0x04

///////////////////////////////////////////////////////////////////////////////
// Bits, die Typ der MerkmalsVerbindung charakterisiert 
#define OBL_MERKMAL		0x0L
#define IDL_MERKMAL		0x40000000L
#define SICHT_MERKMAL	0x80000000L

///////////////////////////////////////////////////////////////////////////////
// Anordnung eines Containers in einem double[4] Feld
#define XMIN_IDX		0
#define XMAX_IDX		1
#define YMIN_IDX		2
#define YMAX_IDX		3

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf Objekt-Daten in TRiAS-Datenbank (ReadOnly)

class _TRIAS01_ENTRY CNativeObject
{
private:
	HPROJECT m_hPr;			// Projekt-Handle
	long m_lONr;			// TargetObjekt
	bool m_fIsValid;		// gültiger ObjektSatz

protected:
	HRESULT GetKantenCont (long lFirst, double *plCont);
	HRESULT GetMaschenCont (long lFirst, double *plCont);
	HRESULT GetKante (long lFirst, BOOL fLast, double_v &rX, double_v &rY, double *plCont);

	HRESULT GetVOMMI (long *plFirst, long lMCode);

// Punktgeometrien speichern
	HRESULT PutPointGeometry (LPCSTR pcName, double dX, double dY);

// LinienGeometrien
	static inline void UpdateContainer (struct kcont *pCont, long x, long y);
	static inline long Winkel (long x1, long y1, long x2, long y2);

	HRESULT PutKante (double *pX, double *pY, long lCnt, long *pKNr, struct kcont *pCont);
	HRESULT PutKnoten (double x, double y, long zKPL, long *pKAL);
	HRESULT ChainKnoten (long lKPL, long lKante);
	HRESULT PutPoints (double *pX, double *pY, long iNum, long *pKAL, struct kcont *pCont);
	HRESULT PutPoint (double x, double y, long *pSPL);
	HRESULT LinkKante (long lKante, long *povol);

	HRESULT DeleteKante (long lKante);
	HRESULT DeletePoints (long lPunkt);
	HRESULT DeleteNode (long Node, long Kante);

// FlächenGeometrien
	HRESULT PutMasche (double *pX, double *pY, unsigned long *pK, unsigned long iKCnt, long *pzvoma);
	HRESULT LinkMasche (long lMasche);
	HRESULT LinkKanteM (long lMasche, long lKFM);

	HRESULT DeleteKanteArea (long lKante, long lFNo);

// Geometrierecherche
static HRESULT QtSearch (HPROJECT hPr, LPCSTR pcName, double *pdWindow, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData);
static HRESULT HtSearch (HPROJECT hPr, LPCSTR pcName, double *pdWindow, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData, BOOL fExact);

// RelationsRoutinen
	HRESULT EstablishRelation (INT_PTR lOSek, INT_PTR lRCode, int rgRelTyp, long *plRelSatz);
	HRESULT ChainRelation (INT_PTR lONr, INT_PTR lRelSatz, int rgRelTyp);
	HRESULT MaskRelation (INT_PTR lONr, int rgRelTyp, bool fFlag);
	HRESULT PutBegleitRelation (INT_PTR lOSek);

	HRESULT FindRelation (INT_PTR lONr2, INT_PTR lRelCode, int rgRelTyp, long *plWert = NULL);
	HRESULT FindRelationsSatz (long lBegin, long *plWert, long lRelCode, long lONr2);
	HRESULT DeleteVORSatz (long lONr, int rgRelTyp, long lRelSatz);
	HRESULT EnumRelationTypesForCode (long lStart, HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData);

static HRESULT TestOBL (HPROJECT hPr, INT_PTR lONr, int rgRMaske);
static HRESULT DeleteBegleitRelation (HPROJECT hPr, INT_PTR lOPrim, INT_PTR lOSek);

// Enumeration aller Relationen, um diese zu löschen
	struct CDeleteRelationsCallBack
	{
		HPROJECT m_hPr;
		INT_PTR m_lONr;
		INT_PTR m_lRCode;
#if defined(_DEBUG)
		int m_iRelType;
#endif // _DEBUG
	};
	static HRESULT CALLBACK DeleteRelations (INT_PTR lRCode, int iRelType, UINT_PTR dwData);
	static HRESULT CALLBACK DeleteRelatedObjectsRelations (INT_PTR lONr, int iRelType, UINT_PTR dwData);

	HRESULT ApplyConnectFilterPoint(LPCSTR pcName, CONNECTFILTEREX *pFilter);
	HRESULT ApplyConnectFilterLine(LPCSTR pcName, CONNECTFILTEREX *pFilter);
	HRESULT ApplyConnectFilterArea(LPCSTR pcName, CONNECTFILTEREX *pFilter);

public:
	CNativeObject(HPROJECT hPr, long lONr = 0L, bool fSupressPossibleError = true);
	~CNativeObject() {}

	HRESULT GetObjectType (DWORD *pdwType);

// Objekt erzeugen/schreiben /Ident und Geometrie)
	HRESULT PutGeometry (long lIdent, DWORD rgType, LPCSTR pcName, SAFEARRAY *pGeom);

	HRESULT PutPointObject (long lIdent, LPCSTR pcName, double_v &rX, double_v &rY);
	HRESULT PutLineObject (long lIdent, LPCSTR pcName, double_v &rX, double_v &rY);
	HRESULT PutAreaObject (long lIdent, LPCSTR pcName, double_v &rX, double_v &rY, ulong_v &rKnt);
	HRESULT PutTextObject (long lIdent, LPCSTR pcName, double_v &rX, double_v &rY, LPCSTR pcText);
	HRESULT CreateObjectTemplate (long lIdent);

// Geometrien löschen
	HRESULT DeleteGeometry (LPCSTR pcName);
	HRESULT DeletePointGeometry (LPCSTR pcName);
	HRESULT DeleteLineGeometry (LPCSTR pcName);
	HRESULT DeleteAreaGeometry (LPCSTR pcName);

// liefern Geometrie direkt
	HRESULT GetPointGeometry (LPCSTR pcName, double_v &rX, double_v &rY, double *plWindow = NULL, double *plCont = NULL);
	HRESULT GetLineGeometry (LPCSTR pcName, double_v &rX, double_v &rY, double *plWindow = NULL, double *plCont = NULL);
	HRESULT GetAreaGeometry (LPCSTR pcName, double_v &rX, double_v &rY, ulong_v &rKnt, double *plWindow = NULL, double *plCont = NULL);
	HRESULT GetTextGeometryAndText (LPCSTR pcName, double_v &rX, double_v &rY, double &rdAngle, os_string &rStr, double *plWindow = NULL, double *plCont = NULL);

// liefert Geometrie als OGC WKT (well-known text)
	HRESULT GetGeometryWKT (LPCSTR pcName, BSTR *pbstrWKT, double *plWindow = NULL, double *plCont = NULL);

// liefert Geometrie als VT_ARRAY|VT_DOUBLE
	HRESULT GetGeometry (LPCSTR pcName, SAFEARRAY **pvGeom, double *pdWindow = NULL, double *pdCont = NULL);
	HRESULT GetGeometryGuid (LPCSTR pcName, _GUID *pGuid);
	HRESULT GetContainer (LPCSTR pcName, double *plCont);

	HRESULT GetTextObjektText (long lMCode, os_string &rStr);
	HRESULT PutTextObjektText (long lMCode, LPCSTR pcText);
	HRESULT GetTextObjektText (long lMCode, BSTR *pbstrVal);
	HRESULT PutTextObjektText (long lMCode, BSTR bstrVal);
	HRESULT DeleteTextObjectText (long lMCode);

	HRESULT GetTextMerkmal (long lMCode, os_string &rStr);
	HRESULT PutTextMerkmal (long lMCode, LPCSTR pcNewText, BOOL fTextMCode = FALSE);
	HRESULT GetTextMerkmal (long lMCode, BSTR *pbstrVal);
	HRESULT PutTextMerkmal (long lMCode, BSTR bstrVal, BOOL fTextMCode = FALSE);
	HRESULT DeleteTextMerkmal (long lMCode, BOOL fTextMCode = FALSE);
	HRESULT EnumRelatedMCodes (HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);
static HRESULT FindTextMerkmal (HPROJECT hPr, long lMCode, LPCSTR pcPattern, int iMode, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData);

	HRESULT GetObjectGUID (struct _GUID *pGuid);
	HRESULT SetObjectGUID (const _GUID &rGuid);
static HRESULT FindObjectFromGUID (HPROJECT hPr, const _GUID &rGuid, INT_PTR *plONr);

	HRESULT GetCreationDate (DATE *pdCreate);
	HRESULT GetModificationDate (DATE *pdCreate);

	HRESULT CreateObjTemplate (long lIdent, INT_PTR *plONr = NULL);

	HRESULT GetIdent (INT_PTR *plIdent);
	HRESULT PutIdent (long lIdent, long *plOldIdent = NULL);
	HRESULT DeleteIdent (long *plOldIdent = NULL);
	HRESULT VerifyIdent (long lIdent, long lIdRec, DWORD rgOTyp);
	HRESULT ModifyIdent (long lIdent, long *plOldIdent = NULL);

	HRESULT Delete (BOOL fDelRelated);		// Objekt vollständig löschen

// Relationen verwalten
	HRESULT PutRelation (INT_PTR lOSek, INT_PTR lRelCode, int rgRelTyp);

	HRESULT DeleteAllRelations();
	HRESULT DeleteRelation (INT_PTR lOSek, INT_PTR lRelCode, int rgRelTyp);
	
	HRESULT EnumRelationCodes (HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData, int iMaske = OUREL|GREL|BRELAP);
	HRESULT EnumBegleitRelationCode (HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData);
	HRESULT EnumRelatedObjects (INT_PTR lRCode, HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData);
	HRESULT EnumBegleitObject (HRESULT (CALLBACK *pFcn)(INT_PTR, int, UINT_PTR), UINT_PTR dwData);

	INT_PTR AssociatedObject();

	HRESULT ApplyConnectFilter(LPCSTR pcName, CONNECTFILTEREX *pFilter);

// Geometrierecherche
static HRESULT EnumObjectsInWindow (HPROJECT hPr, LPCSTR pcName, double *pdWindow, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData, BOOL fExact = FALSE);

// general purpose functions
	BOOL operator! () { return m_fIsValid ? FALSE : TRUE; }
	operator BOOL () { return m_fIsValid ? TRUE : FALSE; }
};

///////////////////////////////////////////////////////////////////////////////
// Bewegungsrichtung, wenn man bei 3 gegebenen Punkten P1(x1,y1), P2(x2,y2) und P3(x3,y3) vom
// ersten, zum zweiten und dann zum dritten geht; return-Werte sind
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn P2 zwischen P1 und P3 liegt bzw.
//    bei P1 == P2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn P1 zwischen P3 und P2 liegt
//  0 bei Kollinearität, wenn P3 zwischen P1 und P2 liegt bzw.
//    bei P1 == P3, P2 == P3, P1 == P2 == P3
inline
int TurnDirection (double x1, double y1, double x2, double y2, double x3, double y3)
{
double dx1 = x2 - x1;
double dy1 = y2 - y1;
double dx2 = x3 - x1;
double dy2 = y3 - y1;

	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;
} // TurnDirection


///////////////////////////////////////////////////////////////////////////////
// 2 Strecken (x11,y11)-(x21,y21) und (x12,y12)-(x22,y22) haben wenigstens einen Punkt
// gemeinsam; dann Rückgabe von true, sonst false
inline
bool Intersection (double x11, double y11, double x21, double y21, double x12, double y12,
				   double x22, double y22)
{
	return ((TurnDirection (x11, y11, x21, y21, x12, y12) *
			 TurnDirection (x11, y11, x21, y21, x22, y22)) <= 0) &&
			((TurnDirection (x12, y12, x22, y22, x11, y11) *
			  TurnDirection (x12, y12, x22, y22, x21, y21)) <= 0);
}

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT PunktLage (double dXp, double dYp, double *x, double *y, long lCnt, 
	bool &rbInner);
HRESULT PunktLage (double x, double y, CONNECTFILTEREX *pFilter, bool& bInner);
bool Intersection (double x11, double y11, double x21, double y21, double x12, 
	double y12, double x22, double y22);

} // namespace trias_nativeobject

/////////////////////////////////////////////////////////////////////////////
// benötige globale Funktionen
_TRIAS01_ENTRY HRESULT CreateLink (HPROJECT hPr, long lFileNo, long *plBegin, long Wert);
_TRIAS01_ENTRY HRESULT DeleteLink (HPROJECT hPr, long lFileNo, long *plBegin, long Wert);
_TRIAS01_ENTRY HRESULT TestDBLink (HPROJECT hPr, long lFileNo, long lFirst, long lValue);

_TRIAS01_ENTRY HRESULT CreateLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink);
_TRIAS01_ENTRY HRESULT DeleteLinkVIO (HPROJECT hPr, long *pBegin, long lWert, long lIdent, LINKTYPE rgLink);
_TRIAS01_ENTRY HRESULT TestDBLinkVIO (HPROJECT hPr, long lFirst, long lValue, long lIdent, LINKTYPE rgLink, LINKTYPE *prgLink);

_TRIAS01_ENTRY HRESULT CreateChainEnd (HPROJECT hPr, long lFileNo, long *pBegin, long Wert);

#endif // !defined(_NATIVEOBJECT_H__6A40D9C3_B054_11D1_859E_00600875138A__INCLUDED_)

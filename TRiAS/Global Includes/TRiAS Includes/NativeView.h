///////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeView.h | Declaration of <CNativeView> class

#if !defined(_NATIVEVIEW_H__D87E62C3_92A7_11D1_BA02_080036D63803__INCLUDED_)
#define _NATIVEVIEW_H__D87E62C3_92A7_11D1_BA02_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <risdb.h>
#include <VisInfo.h>

#if !defined(TPPunkt)
#define TPUnknown	0x00

#define TPPunkt		OTPunkt
#define TPLinie		OTLinie
#define TPFlaeche	OTFlaeche
#define TPText		OTText
#define TPAll		(OTPunkt|OTLinie|OTFlaeche|OTText)

#define TPKO		OTKO
#define TPSO		OTSachObjekt
#endif

#include <defattr.h>

struct attribs;		// forward decl

namespace trias_nativeview {

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf Ansicht-Daten in TRiAS-Datenbank (ReadOnly)
class CNativeView 
{
private:
	HPROJECT m_hPr;			// Projekt-Handle
	os_string m_strName;	// Name der Ansicht
	LONG m_lRecNo;			// zugehörige Satznummer
	LONG m_lClipObj;		// ClippingObject

	HRESULT GetDefaultViewEntry (attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId);
	HRESULT GetPointViewEntry (attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault = FALSE);
	HRESULT GetLineViewEntry (attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault = FALSE);
	HRESULT GetAreaViewEntry (attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault = FALSE);
	HRESULT GetTextViewEntry (attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault = FALSE);

public:
	enum VisType {		// VisualisierungsTyp
		VT_DontCare = -1,

		VT_Punkt = 0,			// PunktVisInfo
		VT_Linie = 1,			// LinienVisInfo
		VT_Flaeche = 2,			// FlaechenVisInfo
		VT_Default = 3, 
		VT_Text = 4,			// TextVisInfo

		VT_PunktDef = 0x0100,	// PunktVisInfo, Voreinstellung
		VT_LinieDef = 0x0101,	// LinienVisInfo, Voreinstellung 
		VT_FlaecheDef = 0x0102, // FlaechenVisInfo, Voreinstellung
		VT_TextDef = 0x0104, 	// TextVisInfo, Voreinstellung

		VT_MaskDef = 0x0100,	// Maske
	};

	_TRIAS01_ENTRY CNativeView (HPROJECT hPr, LPCSTR pcName);
	_TRIAS01_ENTRY ~CNativeView() {}

	_TRIAS01_ENTRY static HRESULT EnumViews (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(LPCSTR, DWORD), DWORD dwData);
	_TRIAS01_ENTRY HRESULT EnumEntries (HRESULT (CALLBACK *pFcn)(LONG, VisType, DWORD), DWORD dwData);			// holt alle IDs dieser Sicht
	_TRIAS01_ENTRY HRESULT GetViewEntry (LONG Ident, VisType rgType = VT_Default, DVisInfo **ppVI = NULL, const CLSID *pClsId = NULL);	// Liest VisInfo aus Sicht
	_TRIAS01_ENTRY HRESULT GetObjRgn (LONG *plClipObj);

	_TRIAS01_ENTRY HRESULT GetTextMerkmal (INT_PTR lMCode, os_string &rStr);
	_TRIAS01_ENTRY HRESULT PutTextMerkmal (INT_PTR lMCode, LPCSTR pcNewText);
	_TRIAS01_ENTRY HRESULT DeleteTextMerkmal (INT_PTR lMCode);
};

#define MAXVIEWNAMELEN	40		// max. Länge eines AnsichtNamens

///////////////////////////////////////////////////////////////////////////////
// Besonderheiten in der GeoDB bei FlächenVisInfos
const int BMBkConture = 0x0001;			// Kontur wie Hintergrund
const int BMOpaque = 0x8000;			// Opaque bei Flächen

///////////////////////////////////////////////////////////////////////////////
// VisualisierungsInfo für SchriftObjekte 
const short TV_Italic = 0x01;			// FontEigenschaften
const short TV_Underlined = 0x02;
const short TV_StrikedThru = 0x04;
const short TV_FixedPitch = 0x08;
const short TV_Bold = 0x10;
const short TV_Light = 0x20;
const short TV_BKMode = 0x40;
const short TV_Frame = 0x80;

const short TV_LeftAlign = 0x0000;		// default: linksbündig
const short TV_CentreAlign = 0x0100;	// zentrieren
const short TV_RightAlign = 0x0200;		// rechtsbündig
const short TV_Justified = 0x0400;		// Blocksatz
const short TV_AlignStyle = 0x0700;		// alle Bits (Maske)
const short TV_RoundFrame = 0x0800;		// Runde Ecken (nur mit TV_Frame)

} // namespace trias_nativeview

#endif // !defined(_NATIVEVIEW_H__D87E62C3_92A7_11D1_BA02_080036D63803__INCLUDED_)

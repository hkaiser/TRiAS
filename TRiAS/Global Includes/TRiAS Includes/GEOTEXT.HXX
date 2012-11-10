///////////////////////////////////////////////////////////////////////////
// @doc 
// @module GEOTEXT.HXX | Klassendefinition für TextObjekte

#if !defined(_GEOTEXT_HXX__64E947B3_F98D_11D1_8639_00600875138A__INCLUDED_)
#define _GEOTEXT_HXX__64E947B3_F98D_11D1_8639_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _DEBUG
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif

#include <CSTextPointGeom.h>

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);		// WObjectProperty

/////////////////////////////////////////////////////////////////////////////
// Textobjektklassen
class BasicGeoText : 
	public GeoPunkt 
{
protected:
	char *_ShowedText;

	void SetText (char *);

public:
		BasicGeoText (GeoDB &rDB, long ONr, long Id = 0) 
			: GeoPunkt (rDB, ONr, Id), _ShowedText(NULL) 
		{ 
			COM_TRY {
			CCSTextPointGeometry text;

				m_pt = (_DGMPointGeometry *)text;
			} COM_CATCH_NORETURN;
		}
		BasicGeoText (GeoDB &rDB, long ONr, long Id, const Punkt &Pt) 
			: GeoPunkt (rDB, ONr, Id, Pt), _ShowedText(NULL) 
		{ 
		__Interface<_DGMTextPointGeometry> text;

			if (!m_pt.IsValid() || FAILED(m_pt -> QueryInterface(text.ppi()))) {
			// nur dann neu erzeugen, wenn das Objekt noch kein Rechteck ist
				COM_TRY {
				CCSTextPointGeometry text(Pt.GetX(), Pt.GetY());

					m_pt = (_DGMPointGeometry *)text;
				} COM_CATCH_NORETURN;
			}
		}
		BasicGeoText (BasicGeoText &rBGT) :
			GeoPunkt (rBGT.DB(), rBGT.ObjNr(), rBGT.Id(), Punkt(rBGT)), 
			_ShowedText(NULL)  
		{ 
		}

// virtuelle Funktionen
_TRIAS02_ENTRY long RetrievePureGeometrie (KoOrd **ppX, KoOrd **ppY, long **pKCnt = NULL);
_TRIAS02_ENTRY GEOMETRYTYPE GType();

virtual char *Text (void) const = 0;
virtual TextObjTyp isText (void) = 0;	// liefert TextTyp
_TRIAS02_ENTRY virtual char *TextBase() const;	// liefert Grundlage, auf der Text 'berechnet' wird

_TRIAS02_ENTRY Dimension EXPORT02 Size (void);	// liefert Zeilen und Spalten
_TRIAS02_ENTRY virtual char * EXPORT02 ChangeText (char *);	// neuen Text einfügen

_TRIAS02_ENTRY ObjTyp isA (void);

		~BasicGeoText (void) { DELETE_OBJ(_ShowedText);}
};

class GeoText : 
	public BasicGeoText 
{
public:
// Konstruktoren/Destruktoren
	_TRIAS02_ENTRY EXPORT02 GeoText (GeoDB &rDB, long ONr, long Id = 0, char *Text = NULL);
	_TRIAS02_ENTRY EXPORT02 GeoText (GeoDB &rDB, long ONr, long Id, const Punkt &Pt, char *Text = NULL);
	_TRIAS02_ENTRY EXPORT02 GeoText (GeoText &GT);

	char * Text (void) const { return _ShowedText; }

	~GeoText (void) {}

// virtuelle Funktionen
_TRIAS02_ENTRY TextObjTyp isText (void);
};

#if defined(_USE_LEGACY_CODE)
class GeoTextInd : 
	public BasicGeoText 
{
protected:
	long _MCode;	// MerkmalsCode im Bezugsobjekt
	long _AssocONr;	// zugehöriges Bezugsobjekt

public:
// Konstruktoren/Destruktoren
	_TRIAS02_ENTRY 	GeoTextInd (GeoDB &rDB, long ONr, long Id = 0, long MCode = -1L);
	_TRIAS02_ENTRY GeoTextInd (GeoDB &rDB, long ONr, long Id, const Punkt &Pt, long MCode = -1L);
	_TRIAS02_ENTRY EXPORT02 GeoTextInd (GeoTextInd &GTI);

_TRIAS02_ENTRY char * Text (void) const;

	~GeoTextInd (void) {}

// virtuelle Funktionen
_TRIAS02_ENTRY TextObjTyp isText (void);

inline	long FAssocObj (void) { return _AssocONr; }
inline	long FMCode (void) { return _MCode; }
};
#endif // defined(_USE_LEGACY_CODE)

class GeoTextIndOP : 
	public GeoText 
{
protected:
	long _AssocONr;				// zugehöriges Bezugsobjekt
	WObjectProperty m_ObjProp;
	os_string m_strText;

public:
// Konstruktoren/Destruktoren
	_TRIAS02_ENTRY GeoTextIndOP (GeoDB &rDB, long lONr, long Id = 0, char *Text = NULL);
	_TRIAS02_ENTRY GeoTextIndOP (GeoDB &rDB, long lONr, long Id, const Punkt &Pt, char *Text = NULL);
	_TRIAS02_ENTRY EXPORT02 GeoTextIndOP (GeoTextIndOP &GTI);

_TRIAS02_ENTRY char *Text (void) const;
_TRIAS02_ENTRY char *TextBase() const;	// liefert Grundlage, auf der Text 'berechnet' wird

	_TRIAS02_ENTRY ~GeoTextIndOP (void) {}

// virtuelle Funktionen
_TRIAS02_ENTRY ObjTyp isA (void);
_TRIAS02_ENTRY TextObjTyp isText (void);
_TRIAS02_ENTRY char * EXPORT02 ChangeText (char *);	// neuen Text einfügen, tut hier nichts

inline long FAssocObj (void) { return _AssocONr; }
};

#endif // !defined(_GEOTEXT_HXX__64E947B3_F98D_11D1_8639_00600875138A__INCLUDED_)

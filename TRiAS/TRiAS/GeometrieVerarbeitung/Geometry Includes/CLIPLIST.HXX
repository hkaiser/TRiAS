// Liste der beim Clipping erzeugten Teilobjekte
// File: CLIPLIST.HXX
// W. Mörtl


#ifndef _CLIPLIST_HXX
#define _CLIPLIST_HXX


class GeoObjekt;	// für DeclareLock (s. u.)

class _GEOMETR_ENTRY ClipListe : public CListContainer 
{
protected:
	void UserDelete (void* pObj);	// virt. Funkt. in Container-Klasse

public:
// Konstruktor/Destruktor
	ClipListe (void);
	~ClipListe (void);
};


	// das nachfolgende Makro 'DeclareLock' generiert zwei zusätzliche Klassen:
	// GeoObjektCreator - für das Neueintragen eines Teilobjektes in die Liste
	// GeoObjektLock    - für den typsicheren Zugriff auf ein Element der Liste
	DeclareLock (ClipListe, GeoObjekt);

#endif  // _CLIPLIST_HXX

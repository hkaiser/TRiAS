// HeaderDatei (Template), die verwendet werden kann, um gezielt einzelne
// Klassen nicht mit zu kompilieren
// Klassen, die gebraucht werden mÅssen hier herauskommentiert werden.
// Die jeweilige Klassenhierarchie ist durch einrÅcken gekennzeichnet.
// File: TEMPLATE.H

#if !defined(_TEMPLATE_H)
#define _TEMPLATE_H

// GeometrieObjekte
#define NOOBJCONTAINER
#define	NOKOORDINATENPAAR
#define		NOPUNKT
#define		NOAUSDEHNUNG
#define	NOKANTE
#define	NOMASCHE
#define	NOGEOOBJEKT
#define		NOGEOPUNKT
#define		NOGEOKANTE
#define		NOGEOFLAECHE

// Zeichenbare Objekte
#define	NOTRANSFORMATION
#define		NODRAGRECTANGLEOBJEKT
#define		NOEXTSHAPEOBJECT
#define			NOPUNKTOBJEKT
#define			NOKANTENOBJEKT
#define			NOMASCHENOBJEKT
#define			NODATENBASISOBJEKT
#define			NOGITTEROBJEKT
#define	NOEXTBITMAPOBJECT

// DatenBasis
#define NODBTEMPLATE
#define		NOGEODB
#define		NOPBDDB

// PBD - Objekte
#define NOPBDDATA
#define		NOPBDIDENT
#define		NOPBDRELATION
#define		NOPBDMERKMAL
#define			NOTEXTMERKMAL
#define			NOINTMERKMAL
#define			NOFLOATMERKMAL
#define			NODOUBLEMERKMAL

// ProfileObjekte
#define	NOPROFILE

#endif // _TEMPLATE_H

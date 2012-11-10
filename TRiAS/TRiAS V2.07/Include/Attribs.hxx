// Prototypen und Funktionsbeschreibung der Zugriffsfunktionen für die 
// Visualisierungsinformationen in der GeoDB
// File: ATTRIBS.HXX

#if !defined(_ATTRIBS_HXX)
#define _ATTRIBS_HXX

#include <visinfo.hxx>

#if !defined(NOSICHT)

#define SIGHTNAMESIZE   	40      	// max. Länge eines Sichtbezeichners

class ObjContainer;

enum TType { IDTyp, ONTyp, };   // Typ der Sichtverwaltung

class Sicht {
private:
	char _SichtName[SIGHTNAMESIZE+1];       // Bezeichner der Sicht
	char *_NutzerName;      	// NutzerName
	short _SatzNr;          	// SatzNummer des Sicht-Satzes
	long _ClippObj;			// ObjNummer von ClippingObjekt
	class GeoDB &m_rDB;		// DatenBank

private:
// Funktionen, die Zugriff auf SichtKomponenten erlauben
_TRIAS02_ENTRY ErrCode EXPORT02 NewTarget (TType TT, long Target, VisInfo *VI, short fSpec = -1);
_TRIAS02_ENTRY ErrCode EXPORT02 FindTarget (TType TT, long Target, VisInfo **VI, short iTyp = -1);
_TRIAS02_ENTRY ErrCode EXPORT02 DelTarget (TType TT, long Target, short iType = -1);

_TRIAS02_ENTRY ErrCode EXPORT02 DelAttribSet (long frstTarget);

_TRIAS02_ENTRY ErrCode EXPORT02 GetSightTargets (TType TT, long **ppTs, short &numTs, short **ppTypes = NULL);

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 Sicht (GeoDB &rDB, const char *SichtName, 
				const char *Nutzer = NULL);

// Memberfunktionen
inline	bool isValid (void) { return _SatzNr != 0; }
inline	char *Name (void) { return _SichtName; }
inline	long SatzNr (void) { return _SatzNr; }
inline	GeoDB &DB (void) const { return m_rDB; }

// Identifikatorbehandlung
inline	ErrCode GetSightIDs (long **ppIDs, short &numIDs, short **ppTypes = NULL)       // holt alle IDs dieser Sicht
		{ return GetSightTargets (IDTyp, ppIDs, numIDs, ppTypes); }

inline	ErrCode AddIDtoSight (long Ident, VisInfo *VI = NULL, short fSpec = -1)   // Schreibt ID zu Sicht
		{ return NewTarget (IDTyp, Ident, VI, fSpec); }
inline	ErrCode DelIDfromSight (long Ident, short iTyp = -1)	// Löscht ID aus Sicht
		{ return DelTarget (IDTyp, Ident, iTyp); }
inline	ErrCode GetIDfromSight (long Ident, VisInfo **VI = NULL, short iTyp = -1) // Liest VisInfo aus Sicht
		{ return FindTarget (IDTyp, Ident, VI, iTyp); }
_TRIAS02_ENTRY short EXPORT02 GetTypes (long lIdent, short fAll = true);

// liefert die Standardwerte für diesen Identifikator
_TRIAS02_ENTRY friend ErrCode EXPORT02 GetDefaultTargetVisInfo (GeoDB &rDB, TType TT, long Ident, VisInfo **VI = NULL, short iTyp = -1);
friend inline	ErrCode GetDefaultIDVisInfo (GeoDB &rDB, long Ident, VisInfo **VI = NULL, short iTyp = -1)
		{ return GetDefaultTargetVisInfo (rDB, IDTyp, Ident, VI, iTyp); }
_TRIAS02_ENTRY friend short EXPORT02 GetDefaultTypes (GeoDB &rDB, long lIDent, short fAll = true);

// schreibt in StandardSicht
_TRIAS02_ENTRY friend ErrCode EXPORT02 AddTargettoDefaultSight (GeoDB &rDB, TType TT, long Ident, VisInfo *pVI = NULL);
friend inline	ErrCode AddIDtoDefaultSight (GeoDB &rDB, long Ident, VisInfo *pVI = NULL)
		{ return AddTargettoDefaultSight (rDB, IDTyp, Ident, pVI); }

// EinzelObjektbehandlung
inline	ErrCode GetSightONs (long **ppONs, short &numONs, short **ppTypes = NULL)       // holt alle Objektnummern dieser Sicht
		{ return GetSightTargets (ONTyp, ppONs, numONs, ppTypes); }

inline	ErrCode AddONtoSight (long ON, VisInfo *VI = NULL, short fSpec = -1)      // Schreibt ON zu Sicht
		{ return NewTarget (ONTyp, ON, VI, fSpec); }
inline	ErrCode DelONfromSight (long ON, short iTyp = -1)	// löscht ON aus Sicht
		{ return DelTarget (ONTyp, ON, iTyp); }
inline	ErrCode GetONfromSight (long ON, VisInfo **VI = NULL, short iTyp = -1)	// Liest VisInfo dieses Objektes
		{ return FindTarget (ONTyp, ON, VI, iTyp); }

// liefert die Standardwerte für dieses Objekt
friend inline	ErrCode GetDefaultONVisInfo (GeoDB &rDB, long ON, VisInfo **VI = NULL)
		{ return GetDefaultTargetVisInfo (rDB, ONTyp, ON, VI); }
friend inline	ErrCode AddONtoDefaultSight (GeoDB &rDB, long Ident, VisInfo *pVI = NULL)
		{ return AddTargettoDefaultSight (rDB, ONTyp, Ident, pVI); }

_TRIAS02_ENTRY ErrCode EXPORT02 DelSight (bool fDelAttribs = true);	// gesamte Sicht löschen
_TRIAS02_ENTRY ErrCode EXPORT02 Rename (const char *pNewName);		// Umbenennen
_TRIAS02_ENTRY ErrCode EXPORT02 CreateView (bool fRemoveOld = false);	// leer erzeugen 

#if defined(MSWIND)
_TRIAS02_ENTRY HPALETTE EXPORT02 GetPalette (void);	// liefert Palette dieser Sicht

// Funktionen, die alle VisInfo's zu einem IDent behandeln
_TRIAS02_ENTRY short EXPORT02 GetCompleteVisInfo (long lIdent, HPALETTE hPal, VisInfo ** ppVI, short iBits, short *piGot = NULL);
_TRIAS02_ENTRY ErrCode EXPORT02 SetCompleteVisInfo (long lIdent, VisInfo **ppVI, short iBits);
_TRIAS02_ENTRY bool EXPORT02 ReadVisInfoFromSight (long lIdent, HPALETTE hPal, VisInfo *& pVI, VisType iVTyp);

_TRIAS02_ENTRY friend ErrCode EXPORT02 GetCompleteDefaultVisInfo (GeoDB &rDB, long lIdent, HPALETTE hPal, VisInfo **ppVI, short iBits, short *piGot = NULL);
_TRIAS02_ENTRY friend ErrCode EXPORT02 SetCompleteDefaultVisInfo (GeoDB &rDB, long lIdent, VisInfo **ppVI, short iBits = TPAll);
_TRIAS02_ENTRY friend ErrCode EXPORT02 ReadVisInfoFromDefaultSight (GeoDB &rDB, long lIdent, HPALETTE hPal, VisInfo *& pVI, VisType iVTyp);
#endif

_TRIAS02_ENTRY long EXPORT02 GetObjRgn (void);		// liefert Objekt für ClippingRgn
_TRIAS02_ENTRY long EXPORT02 SetObjRgn (long);		// setzt neues ClippObj

_TRIAS02_ENTRY bool EXPORT02 GetCont (ObjContainer &);	// setzen/ lesen des SichtContainers
_TRIAS02_ENTRY bool EXPORT02 SetCont (ObjContainer &);

_TRIAS02_ENTRY ErrCode EXPORT02 PutMiText (long lMCode, char *pText);
_TRIAS02_ENTRY ErrCode EXPORT02 GetMiText (long lMCode, char **pBuff);
_TRIAS02_ENTRY ErrCode EXPORT02 DelMiText (long lMCode);

_TRIAS02_ENTRY ErrCode EXPORT02 MoveAttribs (Sicht *pS);
_TRIAS02_ENTRY ErrCode EXPORT02 GetAttribs (long *, long *);
_TRIAS02_ENTRY ErrCode EXPORT02 SetAttribs (long, long);

#if defined(MSWIND)
_TRIAS02_ENTRY bool EXPORT02 EnumIdents (bool (*Fcn)(long, bool, void *), void *);
_TRIAS02_ENTRY bool EXPORT02 EnumIdentsEx (bool (*Fcn)(long, DWORD, void *), void *, short iOTypes);
_TRIAS02_ENTRY bool EXPORT02 EnumObjects (bool (*Fcn)(long, bool, void *), void *);
_TRIAS02_ENTRY bool EXPORT02 RetrieveVisInfo (long lIdent, short iVTyp, VISINFO &rVI);
#endif
// Destruktor
	_TRIAS02_ENTRY EXPORT02 ~Sicht (void);
};
#endif // NOSICHT

#endif // _ATTRIBS_HXX

// Klasse, die aktuellen Zustand des Hauptprogrammes beschreibt ---------------
// File: RSTATUS.HXX

#if !defined(_RSTATUS_HXX)
#define _RSTATUS_HXX

#if !defined(NORSTATUS)

enum RSToDo { RSUnknown, RSClassify, RSObjList, };
enum RMode { RMUnknown, RMFile, RMBuffer, RMClipboard, };

class RStatus {
public:
// Konstruktor
		RStatus (
			long SelON, 		// selektiertes Objekt
			GeoDB &DB,		// aktuelle DB
			PBD_DB &pbdDB,		// aktuelle PBD
			char *Path,		// PBD-SuchPfad
			ObjContainer *pRc = NULL	// selektiertes Fenster
		);

	ObjContainer *_pRc;	// aktuell selektiertes Gebiet
	long _SelON;		// aktuell selektiertes Objekt
	char * _DBPath;		// Pfad, wo DbaseDateien stehen
	GeoDB &_DB;		// GeometrieDatenbasis
	PBD_DB &_PbdDB;		// Produktbeschreibungsdatenbasis
	ObjFeld *_pOF;		// hier wird das ObjFeld (Ergebnis der 
				// Recherche) abgelegt.
	RSToDo _toDo;		// was soll mit dem gefundenen gemacht werden

		~RStatus (void);
};
#endif

// Diverse Funktionsdeklarationen ---------------------------------------------
ErrCode doRecherche (App *, HANDLE, const char *, RStatus &, RMode);
ErrCode doFileRecherche (pWindow, App *, HANDLE, const char *, RStatus &);
char *RechercheParamDlg(void);

#endif	// _RSTATUS_HXX

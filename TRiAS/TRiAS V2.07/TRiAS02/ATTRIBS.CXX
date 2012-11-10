// Memberfunktionen fuer die Klassen Sicht und VisType
// File: ATTRIBS.CXX

#include "trias02p.hxx"

#include "konsobj.hxx"

#if defined(_DEBUG)
extern "C" short g_iKonsFlags;
#endif // _DEBUG

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

_TRIAS02_ENTRY 
bool EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);

// Memberfunktionen der Klasse Sicht ------------------------------------------
// Konstruktor
Sicht :: Sicht (GeoDB &rDB, const char *SichtName, const char *NutzerName)
       : m_rDB (rDB)
{
// Memberwerte setzen
	_ClippObj = -1L;

// Bezeichnung der Sicht kopieren 
	if (SichtName != NULL) {
		memset (_SichtName, '\0', SIGHTNAMESIZE+1);
		strncpy (_SichtName, SichtName, SIGHTNAMESIZE);

	// ein gutes Programm sollte tolerant sein
		if (strlen(_SichtName) == 0) 
			strcpy (_SichtName, "???");

#if defined(MSWIND)
	// Zeichensatzkonvertierung
		AnsiToOem (_SichtName, _SichtName);
#endif
	} else
		*_SichtName = '\0';

// Bezeichnung des NutzerNamens kopieren (für Zugriffsrechte)
	if (NutzerName != NULL) {
		_NutzerName = new char [strlen (NutzerName) +1];
		if (_NutzerName == NULL) {
			db_error (EC_NOMEMORY, RC_ctSicht);
			return;
		}
	} else
		_NutzerName = NULL;

// FestStellen, ob Sicht bereits existiert
DB_ADDR dba (DB().DBDesc());			// gesuchte DatenBankadresse

	dba.file_no = SICHT;
	{
	ErrInstall EI (WC_NOTFOUND);

		if (z_keyfind (&dba, SICHTNAME, _SichtName) == EC_OKAY)
			_SatzNr = (short)dba.rec_no;    // gesuchter Satz
		else	
			_SatzNr = 0;                    // existiert nicht
	}
}

// Destruktor 
Sicht :: ~Sicht (void) 
{
	DELETE (_NutzerName);
}

// SichtSatz sicher generieren ------------------------------------------------
ErrCode Sicht :: CreateView (bool fRemoveOld)
{
DB_ADDR dbaSICHT (DB().DBDesc());       // DatenBankaddresse
sicht locSicht;         // SichtSatz
ErrCode RC;

	dbaSICHT.file_no = SICHT;
	if (_SatzNr != 0) {
		if (fRemoveOld) {	// Sicht existiert bereits
			if (DEXN_SightToDelete (_SichtName))
				return WC_RETURN;	// jemand hat was dagegen
			DelSight (true);		// Sicht löschen
			DEXN_SightDeleted (_SichtName);	// Vollzug melden
		} else
			return WC_RETURN;
	}

	if (_SatzNr == 0) {     // Sicht existiert nicht 
	// neuen SichtEintrag anlegen
		DB().SetDirty();

		memset (&locSicht, '\0', sizeof(locSicht));
		strncpy (locSicht.sichtname, _SichtName, SIGHTNAMESIZE);
		locSicht.objrgn = _ClippObj;
		__New (dbaSICHT, locSicht);
		_SatzNr = (short)dbaSICHT.rec_no;
		return EC_OKAY;		// neu angelegt
	} 

return WC_EXISTS;
}

// Eigentliche Memberfunktionen -----------------------------------------------
ErrCode Sicht :: GetSightTargets (TType OType, long **ppTs, short &numTs, 
				  short **ppTypes) 
{
sicht locSicht;         // lokale DatenStruktur (SichtSatz)
DB_ADDR dba (DB().DBDesc());            // DatenBankadresse
ErrCode RC;             // FehlerCode

// SichtSatz einlesen
	if (_SatzNr == 0) {     // Sicht existiert nicht 
		*ppTs = NULL;
		if (ppTypes) *ppTypes = NULL;
		numTs = 0;
		return (ErrCode)db_error (WC_NOTFOUND, RC_GetSightTargets);
	}
	dba.file_no = SICHT;
	dba.rec_no = _SatzNr;
	__Read (dba, locSicht);

// Anzahl der Sätze im Set merken
short nSet = 0;         // erste Satznummer im Set

	if (OType == IDTyp) {           // gesucht: IDSet
		numTs = locSicht.idnum;         // Anzahl der Targets
		nSet = locSicht.idset;          // erster IDSatz
	} else if (OType == ONTyp) {     // gesucht: ONSet
		numTs = locSicht.onnum;         // Anzahl der Targets
		nSet = locSicht.onset;          // erster ONSatz
	} else
		numTs = 0;

// Speicher für IDFeld anfordern
	if (numTs == 0) {
		*ppTs = NULL;           // keine IDs im Set
		if (ppTypes) *ppTypes = NULL;
		return EC_OKAY;
	}
	*ppTs = new long [numTs];
	if (*ppTs == NULL)              
		return (ErrCode)db_error (EC_NOMEMORY, RC_GetSightTargets);

	if (ppTypes) {
		*ppTypes = new short [numTs];
		if (*ppTypes == NULL)              
			return (ErrCode)db_error (EC_NOMEMORY, RC_GetSightTargets);
	}

// Identifikatoren einlesen
attribs Attr;

	dba.file_no = ATTRIBS; // Dateinummer
	for (register short i = 0; i < numTs; i++) {
		if ((dba.rec_no = nSet) == 0) { // SatzNummer
			numTs = i;      // Set zu Ende, Anzahl korrigieren
			break;
		}
		__Read (dba, Attr);
		(*ppTs)[i] = Attr.attTarget;		// TargetNummer
		if (ppTypes) 
			(*ppTypes)[i] = Attr.attFlag;	// Typ kopieren
		nSet = Attr.attSet;			// nächster Satz
	}

return EC_OKAY;
}

// ----------------------------------------------------------------------------
static bool BitsInVisType (VisType iVTyp, short iBits)
{
	switch (iVTyp) {
	case VT_Punkt:		return iBits & TPPunkt;
	case VT_Linie:		return iBits & TPLinie;
	case VT_Flaeche:	return iBits & TPFlaeche;
	case VT_Text:		return iBits & TPText;
	case VT_Default:
	default:
		break;
	}

return false;
}


static short VisTypeToBits (VisType iVTyp, short iDefFlags)
{
	switch (iVTyp) {
	case VT_Punkt:		return TPPunkt;
	case VT_Linie:		return TPLinie;
	case VT_Flaeche:	return TPFlaeche;
	case VT_Text:		return TPText;
	case VT_Default:	return iDefFlags;
	default:
		break;
	}

return 0;
}


// Hilfsfunktionen für Sichtverwaltung ----------------------------------------
// FindTarget findet den Eintrag für einen Identifikator (OType == IDTyp) oder
// ein Objekt (OType == ONTyp) und liefert in VI die entsprechenden Attribute
// (sofern VI != NULL). Wenn VI == NULL ist, dann testet FindTarget lediglich
// ob ein Eintrag vorhanden ist (--> RückkehrCode).
//
// iType gibt den gesuchten VisTyp an (Punkt, Linie, Fläche etc.). Ist iType
// nicht gegeben (iType == -1), dann wird der erste gefundene verwendet.
//
// Wird ein bestimmter Satztyp nicht gefunden, dann wird im zugehörigen 
// DefaultSatz nachgesehen, ob dieser Typ überhaupt zur Sicht gehört. Wenn ja
// dann wird eine StandardVisualiserung generiert und WC_RETURN geliefert.
//
ErrCode Sicht :: FindTarget (TType OType, long Target, VisInfo **VI, 
			     short iType) 
{
// SichtSatz einlesen
DB_ADDR dba (DB().DBDesc());
ErrCode RC;
sicht locSicht;

	if (_SatzNr == 0) {     // Sicht existiert nicht 
		if (VI)	*VI = NULL;		// Id ist nicht vertreten
		return (ErrCode)db_error (WC_NOTFOUND, RC_FindTarget);
	}
	dba.file_no = SICHT;
	dba.rec_no = _SatzNr;
	__Read (dba, locSicht);

// ersten Satz im Set merken
short nSet = 0;         // erste Satznummer im Set

	if (OType == IDTyp)             // gesucht: IDSet
		nSet = locSicht.idset;          // erster IDSatz
	else if (OType == ONTyp)        // gesucht: ONSet
		nSet = locSicht.onset;          // erster ONSatz

// TargetSatz im Set suchen
attribs Attr;
bool fGenerateDefault = false;

	memset (&Attr, '\0', sizeof(Attr));	// NullSetzen
	dba.file_no = ATTRIBS;                  // Dateinummer
	do {
		if ((dba.rec_no = nSet) == 0 ||         // SatzNummer
		    ((unsigned long)Attr.attTarget > (unsigned long)Target)) {
			if (VI) *VI = NULL;		// nichts gefunden
			return (ErrCode)db_error (WC_NOTFOUND, RC_FindTarget);
		}
		__Read (dba, Attr);
		nSet = Attr.attSet;

	// suchen bis Target und Typ (wenn gegeben) übereinstimmen
		if (Attr.attTarget != Target) 
			continue;	// noch nicht gefunden

		if (iType != -1) {
			if (Attr.attFlag == iType) 
				break;	// gefunden
			else if (Attr.attFlag == VT_Default) {
				if (!BitsInVisType ((VisType)iType, Attr.attDefVis)) {
				// nicht in Sicht vertreten
					if (VI) *VI = NULL;
					return (ErrCode)db_error (WC_NOTFOUND, RC_FindTarget);
				}
				fGenerateDefault = true;
				break;	// dieser Satz existiert nicht
			}
		} else
			break;	// ersten Satz nehmen
	} while (true);

// wenn VI gegeben ist, dann Informationen kopieren (neues Objekt generieren)
	if (!fGenerateDefault && VI != NULL) {       // VisInfo kopieren

		switch (Attr.attFlag) {	// HIBYTE enthält zusätzliche Flags ab V5.00.00.011
		case VT_Punkt:		// Punktobjekt
			{
			Dimension dim (((pattribs &)Attr).sizex, ((pattribs &)Attr).sizey);
			Color SecC = DEF_SECCOLOR;

				if (DB().GetDBVersion() >= VERSION0500000B)
					SecC = (Color &)((pattribs &)Attr).pscolor;

				*VI = new PVisInfo (Attr.attStyle,
						 Attr.attPrio, *(Color *)(&Attr.attPColor),
						 dim, Attr.attName, ((pattribs &)Attr).prot,
						 SecC
					  );
			}
			break;

		case VT_Linie:		// Linien-(Kanten-)Objekt
			*VI = new LVisInfo (Attr.attStyle,
					Attr.attPrio, (Color &)Attr.attPColor,
					((lattribs &)Attr).width,
					Attr.attName
				  );
			break;

		case VT_Flaeche:		// Flächenobjekt
			*VI = new FVisInfo (Attr.attStyle,
					Attr.attPrio, (Color &)Attr.attPColor,
					(Color &)((fattribs &)Attr).bcolor
#if !defined(OLDVISINFO)
					, Attr.attAttrEx
#endif // !OLDVISINFO
					, Attr.attName
				  );
			break;

		case VT_Text:		// SchriftObjekt
			*VI = new TVisInfo (Attr.attStyle,
					Attr.attPrio, (Color &)Attr.attPColor,
					Dimension (((tattribs &)Attr).tsizex,
						   ((tattribs &)Attr).tsizey),
					((tattribs &)Attr).ttype & 0xff
#if !defined(OLDVISINFO)
						| (Attr.attAttrEx << 8) & ~0xff
#endif // !OLDVISINFO
					, ((tattribs &)Attr).trot * 20,
					Attr.attName
				  );
			break;

		case VT_Default:	// DefaultWerte, keine Objektspezifik
			*VI = new VisInfo (Attr.attStyle, 
					Attr.attPrio, (Color &)Attr.attPColor,
					Attr.attName);
			break;

		default:
			break;
		}
	} else if (fGenerateDefault) {
		if (VI) *VI = NULL;
		return WC_RETURN;
	}

return EC_OKAY;
}

// NewTarget legt einen neuen Identifikatoreintrag (OType == IDTyp) oder
// Objekteintrag (OType == ONTyp) an, wobei eine neue Sicht generiert wird, 
// wenn dieser Eintrag der erste ist. In dem Fall, wenn der gewünschte Satz
// bereits existiert, wird lediglich die AttributInformation aktualisiert
// (VI != NULL). Wird der Satz neu erzeugt, und VI == NULL, dann werden 
// Standardwerte als Attributwerte eingetragen.
//
// Ein wegzuschreibender DefaultSatz dient im allgemeinen lediglich der 
// Definition einer Sichtzugehörigkeit (fSpec enthält ide entsprechenden Bits).
// Dieser wird grundsätzlich hinter die Sätze gleichen Idents aber mit 
// definiertem SytzTyp platziert.
//
ErrCode Sicht :: NewTarget (TType OType, long Target, VisInfo *VI, short fSpec) 
{
// SichtSatz einlesen
DB_ADDR dbaSICHT (DB().DBDesc());       // DatenBankaddresse
sicht locSicht;         // SichtSatz
ErrCode RC;

	dbaSICHT.file_no = SICHT;
	if (_SatzNr == 0) {     // Sicht existiert nicht 
	// neuen SichtEintrag anlegen
		DB().SetDirty();

		memset (&locSicht, '\0', sizeof(locSicht));
		strncpy (locSicht.sichtname, _SichtName, SIGHTNAMESIZE);
		locSicht.objrgn = _ClippObj;
		__New (dbaSICHT, locSicht);
		_SatzNr = (short)dbaSICHT.rec_no;
	} else {
		dbaSICHT.rec_no = _SatzNr;
		__Read (dbaSICHT, locSicht);
	}

// ersten Satz im Set merken
short nSet = 0;         // erste Satznummer im Set
short nSetPrev;         // vorhergehender Satz

	if (OType == IDTyp)             // gesucht: IDSet
		nSet = locSicht.idset;          // erster IDSatz
	else if (OType == ONTyp)        // gesucht: ONSet
		nSet = locSicht.onset;          // erster ONSatz

// TargetSatz im Set suchen
attribs Attr;
DB_ADDR dbaATT (DB().DBDesc());
short iTyp = VI ? VI -> isA() : VT_Default;		// Typ der VisInfo
bool fInsert = false;	// Einfügen bei DefaultSatz

	dbaATT.file_no = ATTRIBS;               // Dateinummer
	dbaATT.rec_no = 0;                      // Anfangswert
	memset (&Attr, '\0', sizeof(Attr));
	nSetPrev = 0;				// kein vorheriger Satz

// SetKette durchsuchen, bis SatzNummer/SatzTyp gefunden
	do {
		if ((dbaATT.rec_no = nSet) == 0)        // SatzNummer
			break;          // nicht gefunden
	// Satz einlesen
		__Read (dbaATT, Attr);

	// richtige Stelle gefunden ?
		if ((unsigned long)Attr.attTarget > (unsigned long)Target)
			break;		// vorbei gerauscht (nicht gefunden)

		if (Attr.attTarget == Target) {
		// Satz für diesen ID existiert bereits

			if (iTyp == VT_Default) {
				if (Attr.attFlag == VT_Default) {
					break;	// Ident+Typ existiert bereits
				} else {
					nSetPrev = (short)dbaATT.rec_no;
					nSet = Attr.attSet;	// nächster Satz
					continue;		// dahinter einfügen
				}
			} else {
			// objektspezifische VisInfo gegeben
				if (Attr.attFlag == VT_Default) {
				// diesen Typ aus DefaultSatz löschen
					Attr.attDefVis &= ~VisTypeToBits ((VisType)iTyp, 0);
					if (Attr.attDefVis != 0) {
					// DefaultSatz noch notwendig
						DB().SetDirty();
						__Write (dbaATT, Attr);
						fInsert = true;
					}
					break;		// DefaultSatz ersetzen
				} else if (Attr.attFlag == iTyp) {
					break;		// Ident+Typ existiert bereits
				}
			}
		}

		nSetPrev = (short)dbaATT.rec_no;
		nSet = Attr.attSet;         // nächster Satz
	} while (true);

// Stelle im Set gefunden, wo Satz hingehört
	if (VI != NULL) {       // VisInfo gegeben
	// neue AttributInfos (allgemeine Attribute) setzen
		Attr.attPrio = VI -> Priority();
		Attr.attStyle = VI -> Style();
		strncpy (Attr.attName, VI -> VisName(), VISNAMESIZE);
		*(Color *)(&Attr.attPColor) = VI -> PrimColor();

	// objektspezifische Attribute setzen         
		switch (Attr.attFlag = VI -> isA()) {
		case VT_Punkt:       // VisInfo für Punkt
			{
			Dimension dim = ((PVisInfo *)VI) -> Size();

				((pattribs &)Attr).sizex = short(dim.Width());
				((pattribs &)Attr).sizey = short(dim.Height());
				((pattribs &)Attr).prot = short(((PVisInfo *)VI) -> Rotation());
				(Color &)((pattribs &)Attr).pscolor = ((PVisInfo *)VI) -> SecColor();
			}
			break;

		case VT_Linie:	// VisInfo für Linie (Kante)
			((lattribs &)Attr).width = ((LVisInfo *)VI) -> Width();
			break;

		case VT_Flaeche:	// VisInfo für Fläche
			{
			FVisInfo *pFVI = (FVisInfo *)VI;
			
#if !defined(OLDVISINFO)
				Attr.attStyle = pFVI -> OldStyle();
				Attr.attAttrEx = (char)pFVI -> AttrEx();
#endif // !OLDVISINFO
				(Color &)((fattribs *)&Attr) -> bcolor = pFVI -> SecColor();
			}
			break;

		case VT_Text:	// VisInfo für Text
			{
			TVisInfo *pTVI = (TVisInfo *)VI;
			Dimension dim = pTVI -> Size();
			
				((tattribs &)Attr).tsizex = char(dim.Width());
				((tattribs &)Attr).tsizey = char(dim.Height());
				((tattribs &)Attr).ttype = (unsigned char)pTVI -> Type();
				((tattribs &)Attr).trot = pTVI -> Rotation() / 20;
#if !defined(OLDVISINFO)
				Attr.attAttrEx = (char)pTVI -> AttrEx();
#endif // !OLDVISINFO
			}
			break;

		case VT_Default:	// keine Objektspezifik
			if (fSpec != -1)
				Attr.attDefVis = fSpec;	// nur Sichtzugehörigkeit
			break;
		}
	} else {        // keine VisInfo gegeben
	// Standardwerte verwenden
		Attr.attFlag = VT_Default;	// ohne Objektspezifik
		Attr.attPrio = DEF_PRIORITY;
		Attr.attStyle = 0;
		Attr.attPColor = 0;
		if (fSpec != -1)
			Attr.attDefVis = fSpec;	// nur Sichtzugehörigkeit
		Attr.attName[0] = '\0';
	}

// entweder alten Satz neu beschreiben oder Satz neu anlegen
	DB().SetDirty();

	if (nSet != 0 && Attr.attTarget == Target && !fInsert) {
	// Satz existiert bereits, wieder wegschreiben
		__Write (dbaATT, Attr);
	} else {
	// neuen Satz anlegen
		Attr.attTarget = Target;	// Ident merken
		Attr.attSet = nSet;         	// nächster Satz
		__New (dbaATT, Attr);
	// Satz im Set einordnen               
		if (nSetPrev == 0) {
		// erster Satz im Set - Kopfsatz korrigieren
			if (OType == IDTyp)
				locSicht.idset = (short)dbaATT.rec_no;
			else
				locSicht.onset = (short)dbaATT.rec_no;
		} else {
		// Satz an die richtige Stelle im Set einhängen
		short tRec = (short)dbaATT.rec_no;

			dbaATT.rec_no = nSetPrev;
			__Read (dbaATT, Attr);
			Attr.attSet = tRec;
			__Write (dbaATT, Attr);
		}
	// Zähler für Set im Kopfsatz aktualisieren
		if (OType == IDTyp)             
			locSicht.idnum++;
		else if (OType == ONTyp)
			locSicht.onnum++;
		__Write (dbaSICHT, locSicht);
	}

return EC_OKAY;         // alles ok, fertig und raus
}


// DelTarget löscht einen Identifikatoreintrag (OType == IDTyp) oder Objekt-
// eintrag (OType == ONTyp) aus der SetKette. wird der letzte Eintrag aus 
// einer Sicht gelöscht, so wird auch diese gelöscht.
ErrCode Sicht :: DelTarget (TType OType, long Target, short iType) 
{
// SichtSatz einlesen
DB_ADDR dbaSICHT (DB().DBDesc());       // DatenBankaddresse
sicht locSicht;         // SichtSatz
ErrCode RC;		// FehlerKode

	if (_SatzNr == 0)       // Sicht existiert nicht 
		return (ErrCode)db_error (WC_NOTFOUND, RC_DelTarget);
	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	__Read (dbaSICHT, locSicht);

// Anzahl der Sätze im Set merken
short nSet = 0;         // erste Satznummer im Set
short nSetPrev;         // vorhergehender Satz

	if (OType == IDTyp)             // gesucht: IDSet
		nSet = locSicht.idset;          // erster IDSatz
	else if (OType == ONTyp)        // gesucht: ONSet
		nSet = locSicht.onset;          // erster ONSatz

// TargetSatz im Set suchen
attribs Attr;
DB_ADDR dbaATT (DB().DBDesc());

	dbaATT.file_no = ATTRIBS;               // Dateinummer
	dbaATT.rec_no = 0;                      // Anfangswert
	memset (&Attr, '\0', sizeof(Attr));	// NullSetzen
	do {
	// SetKette durchsuchen, bis SatzNummer gefunden
		nSetPrev = (short)dbaATT.rec_no;
		if ((dbaATT.rec_no = nSet) == 0 ||      // SatzNummer
		    ((unsigned long)Attr.attTarget > (unsigned long)Target))
			return (ErrCode)db_error (WC_NOTFOUND, RC_DelTarget);
	// Satz einlesen
		__Read (dbaATT, Attr);
		nSet = Attr.attSet;         // nächster Satz
	} while (Attr.attTarget != Target || 
		 (iType != -1 ? Attr.attFlag != iType : false));   // bis Target gefunden

// Satz gefunden, herauslöschen
	DB().SetDirty();

	__Dispose (dbaATT);
	if (nSetPrev == 0) {
	// erster Satz in Set soll gelöscht werden
		if (OType == IDTyp)             locSicht.idset = nSet;
		else if (OType == ONTyp)        locSicht.onset = nSet;
		__Write (dbaSICHT, locSicht);
	} else {
	// mittendrin oder letzter Satz in der SetKette
		dbaATT.rec_no = nSetPrev;
		__Read (dbaATT, Attr);
		Attr.attSet = nSet;         // Zeiger umhängen
		__Write (dbaATT, Attr);
	}

// Zähler im SichtSatz korrigieren
	if (OType == IDTyp)             locSicht.idnum--;
	else if (OType == ONTyp)        locSicht.onnum--;

// SichtSatz wegschreiben, wenn er noch gebraucht wird, ansonsten herauslöschen
	if (locSicht.idnum != 0 || locSicht.onnum != 0) {
	// Satz mit korrigiertem Zähler wegschreiben            
		__Write (dbaSICHT, locSicht);
	} else
	// Satz freigeben
		__Dispose (dbaSICHT);

return EC_OKAY;         // alles ok, fertig und raus
}


// Gesamte Sicht löschen ------------------------------------------------------
ErrCode Sicht :: DelSight (int fDelAttribs) 
{
// Sichtsatz einlesen
DB_ADDR dbaSICHT (DB().DBDesc());	// DatenBankAdresse
sicht locSicht;		// DatenSatz
ErrCode RC;		// FehlerKode

// SichtKopfsatz einlesen
	if (_SatzNr == 0) 	// Sicht existiert nicht
		return (ErrCode)db_error (WC_NOTFOUND, RC_DelSight);

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	__Read (dbaSICHT, locSicht);

	DB().SetDirty();

// evtl. Sichtmerkmale löschen
	if (fDelAttribs && DB().GetDBVersion() >= VERSION05000008) {
		while ((RC = (ErrCode)delmi (DB().DBDesc(), -1L, _SatzNr, SICHT)) == EC_OKAY)
			;
		if (RC != WC_RETURN && RC != WC_NOTFOUND) 
			return RC;	// Fehler
	}	

// WC_NOTFOUND ist eigentlich ein Fehler, als workaround für einen noch nicht 
// gefundenen Bug wird dieser FehlerCode an dieser Stelle jedoch zugelassen,
// damit im Zweifelsfalle die Sicht wirklich gelöscht wird. Es bleiben höchsten 
// ein paar Merkmalsleichen in der GeoDB zurück.

// Identifikatorsätze löschen
	if (locSicht.idset != 0) 
		DBASSERT (DelAttribSet (locSicht.idset));
// ObjektSätze löschen
	if (locSicht.onset != 0) 
		DBASSERT (DelAttribSet (locSicht.onset));

// Sichtkopfsatz selbst löschen
	__Dispose (dbaSICHT);

	_SatzNr = 0;		// Sicht existiert nicht mehr
	_ClippObj = -1;

return EC_OKAY;
}

// Alle Sätze dieses Sets löschen ---------------------------------------------
// der Zähler des Kopfsatzes wird dabei nicht korrigiert
ErrCode Sicht :: DelAttribSet (long TargetNr) 
{
DB_ADDR dbaATT (DB().DBDesc());		// DatenBankadresse
ErrCode RC;				// FehlerKode
attribs Attr;
long nSet = TargetNr;			// jeweils nächster Satz

	DB().SetDirty();

	dbaATT.file_no = ATTRIBS;
	nSet = TargetNr;
	do {
	// Satz einlesen
		dbaATT.rec_no = nSet;
		__Read (dbaATT, Attr);
		nSet = Attr.attSet;
	// Satz freigeben
		__Dispose (dbaATT);
	} while (nSet != 0);

return EC_OKAY;
}


#if defined(MSWIND)

// Liefert die Standardwerte für ein Target -----------------------------------
ErrCode GetDefaultTargetVisInfo (GeoDB &rDB, TType TT, long Ident, VisInfo **VI, short iTyp) 
{
Sicht DefSight (rDB, ResString (IDS_DEFAULTVISINFO, 40));

	return DefSight.FindTarget (TT, Ident, VI, iTyp);
}

ErrCode AddTargettoDefaultSight (GeoDB &rDB, TType TT, long Ident, VisInfo *pVI) 
{
Sicht DefSight (rDB, ResString (IDS_DEFAULTVISINFO, 40));

	return DefSight.NewTarget (TT, Ident, pVI);
}
#endif

// Liefert ObjektNummer, an der diese Ansicht geclippt werden soll ------------
long Sicht :: GetObjRgn (void) 
{
// nur wenn Version neuer als 006 ist
	if (DB().GetDBVersion() <= VERSION05000005) return -1L;

// SichtKopfSatz einlesen
sicht locSicht;
DB_ADDR dbaSICHT (DB().DBDesc());

	if (_SatzNr == 0) {		// Sicht existiert nicht 
		db_error (WC_NOTFOUND, RC_GetObjRgn);
		return -1L;
	}
	if (_ClippObj != -1L)
		return _ClippObj;

// noch nicht gelesen
	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	if ((ErrCode)z_readrec (&dbaSICHT, &locSicht) != EC_OKAY)
		return -1L;
	_ClippObj = locSicht.objrgn;		// liefert ObjektNummer

return _ClippObj;
}

// Einstellen der ObjektNummer, an dem geclippt werden soll -------------------
long Sicht :: SetObjRgn (long newCObj)
{
// nur wenn Version neuer als 006 ist
	if (DB().GetDBVersion() <= VERSION05000005) return -1L;

// SichtKopfSatz einlesen
sicht locSicht;
DB_ADDR dbaSICHT (DB().DBDesc());
ErrCode RC;

	if (_SatzNr == 0) {		// Sicht existiert nicht 
		db_error (WC_NOTFOUND, RC_SetObjRgn);
		return -1L;
	}

// noch nicht gelesen
	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	__Read (dbaSICHT, locSicht);

	DB().SetDirty();

long oldCObj = locSicht.objrgn;		// alte ClipObjNr

	locSicht.objrgn = newCObj;
	__Write (dbaSICHT, locSicht);
	_ClippObj = newCObj;

return oldCObj;
}


// Umbennen einer Sicht -------------------------------------------------------
ErrCode Sicht :: Rename (const char *pNewName)
{
// SichtKopf lesen
sicht locSicht;
DB_ADDR dbaSICHT (DB().DBDesc());
ErrCode RC;

	if (_SatzNr == 0) 		// Sicht existiert nicht 
		return (ErrCode)db_error (WC_NOTFOUND, RC_RenameSight);

// noch nicht gelesen
	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	__Read (dbaSICHT, locSicht);

// alten Satz rauslöschen
	DB().SetDirty();
	__Dispose (dbaSICHT);

// neuen Namen reinschreiben
	strncpy (_SichtName, pNewName, SIGHTNAMESIZE);
	memset (locSicht.sichtname, '\0', SIGHTNAMESIZE);
	strncpy (locSicht.sichtname, pNewName, SIGHTNAMESIZE);

// neuen Satz generieren
	__New (dbaSICHT, locSicht);
	_SatzNr = (short)dbaSICHT.rec_no;

return EC_OKAY;
}

// Übernehmen der Merkmale/Relationen einer gegebenen Sicht -------------------
ErrCode Sicht :: MoveAttribs (Sicht *pS)
{
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

ErrCode RC;
DB_ADDR dbaSICHTsrc (DB().DBDesc());
DB_ADDR dbaSICHTdest (DB().DBDesc());
sicht SICHTSatzSrc;
sicht SICHTSatzDest;

	if (_SatzNr == -1 || pS -> _SatzNr == -1) return EC_OKAY;

	dbaSICHTsrc.file_no = dbaSICHTdest.file_no = SICHT;
	dbaSICHTsrc.rec_no = pS -> _SatzNr;
	dbaSICHTdest.rec_no = _SatzNr;

	__Read (dbaSICHTsrc, SICHTSatzSrc);
	__Read (dbaSICHTdest, SICHTSatzDest);

	SICHTSatzDest.zmerkm = SICHTSatzSrc.zmerkm;
	SICHTSatzDest.zrelat = SICHTSatzSrc.zrelat;

	SICHTSatzSrc.zmerkm = 0;
	SICHTSatzSrc.zrelat = 0;

	DB().SetDirty();
	__Write (dbaSICHTsrc, SICHTSatzSrc);
	__Write (dbaSICHTdest, SICHTSatzDest);

return EC_OKAY;
}

ErrCode Sicht :: GetAttribs (long *pMerkm, long *pRel)
{
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

ErrCode RC;
DB_ADDR dbaSICHT (DB().DBDesc());
sicht SICHTSatz;

	if (_SatzNr == -1) return EC_OKAY;

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;

	__Read (dbaSICHT, SICHTSatz);

	*pMerkm = SICHTSatz.zmerkm;
	*pRel = SICHTSatz.zrelat;

	SICHTSatz.zmerkm = 0;		// doppeltes löschen vermeiden
	SICHTSatz.zrelat = 0;

	DB().SetDirty();
	__Write (dbaSICHT, SICHTSatz);

return EC_OKAY;
}

ErrCode Sicht :: SetAttribs (long lMerkm, long lRel)
{
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

ErrCode RC;
DB_ADDR dbaSICHT (DB().DBDesc());
sicht SICHTSatz;

	if (_SatzNr == -1) return EC_OKAY;

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;

	__Read (dbaSICHT, SICHTSatz);

	SICHTSatz.zmerkm = lMerkm;
	SICHTSatz.zrelat = lRel;

	DB().SetDirty();
	__Write (dbaSICHT, SICHTSatz);

return EC_OKAY;
}


#if defined(MSWIND)
// Enumeration der Identifikatoren und er EinzelObjekte einer Sicht -----------
extern "C" {
inline bool EnumIdentsCallback (bool (*pFcn)(long, bool, void *), 
				long lKey, bool fNotLast, void *pData)
{
	return ((ENUMLONGKEYCALLBACK) pFcn)(lKey, fNotLast, pData);
}

inline bool EnumIdentsExCallback (bool (*pFcn)(long, DWORD, void *), 
				long lKey, DWORD dwData, void *pData)
{
	return ((ENUMLONGKEYEXCALLBACK) pFcn)(lKey, dwData, pData);
}

inline bool EnumObjectsCallback (bool (*pFcn)(long, bool, void *),
				 long Key, int iTyp, void *pData)
{
	return ((ENUMLONGKEYCALLBACK) pFcn)(Key, iTyp, pData);
}

}


bool Sicht :: EnumIdents (bool (*pFcn)(long, bool, void *), void *pData)
{
long *Idents = NULL;
short *iTypes = NULL;
short iNumIDs;
ErrInstall EI (WC_NOTFOUND);	// kein Fehler, wenn Sicht nicht existiert

// einlesen aller Idents dieser Sicht
	if (GetSightIDs (&Idents, iNumIDs, &iTypes) != EC_OKAY) {
		DELETE (Idents);
		DELETE (iTypes);
		return false;
	}

// rufen der gegebenen Funktion für jeden der Identifikatoren
bool fRet = true;

	for (int i = 0; i < iNumIDs; i++) {
		if (FindLong (Idents, iNumIDs, Idents[i]) != i)
			continue;	// war schon

		if ((fRet = EnumIdentsCallback (pFcn, Idents[i], i < iNumIDs -1, pData)) == false) 
			break;
	}

	DELETE (Idents);
	DELETE (iTypes);

return fRet;
}

bool Sicht :: EnumIdentsEx (bool (*pFcn)(long, DWORD, void *), void *pData, short iOTypes)
{
long *Idents = NULL;
short *iTypes = NULL;
short iNumIDs;
ErrInstall EI (WC_NOTFOUND);	// kein Fehler, wenn Sicht nicht existiert

// einlesen aller Idents dieser Sicht
	if (GetSightIDs (&Idents, iNumIDs, &iTypes) != EC_OKAY) {
		DELETE (Idents);
		DELETE (iTypes);
		return false;
	}

// rufen der gegebenen Funktion für jeden der Identifikatoren
bool fRet = true;

	for (int i = 0; i < iNumIDs; i++) {
	short iVTyp = VisTypeToBits ((VisType)iTypes[i], 0);
	
		if (!(iOTypes & iVTyp)) 
			continue;	// wird nicht gebraucht

		if ((fRet = EnumIdentsExCallback (pFcn, Idents[i], (DWORD)iVTyp, pData)) == false) 
			break;
	}

	DELETE (Idents);
	DELETE (iTypes);

return fRet;
}

bool Sicht :: EnumObjects (bool (*pFcn)(long, bool, void *), void *pData)
{
long *Objs = NULL;
short *iTypes = NULL;
short iNumObjs;
ErrInstall EI (WC_NOTFOUND);	// kein Fehler, wenn Sicht nicht existiert

// einlesen aller Einzelobjekte dieser Sicht
	if (GetSightONs (&Objs, iNumObjs, &iTypes) != EC_OKAY) {
		DELETE (Objs);
		DELETE (iTypes);
		return false;
	}

// rufen der gegebenen Funktion für jedes der Einzelobjekte
	for (int i = 0; i < iNumObjs; i++) {
		if (EnumObjectsCallback (pFcn, Objs[i], iTypes[i], pData) == false) {
			DELETE (Objs);
			DELETE (iTypes);
			return false;
		}
	}

	DELETE (Objs);
	DELETE (iTypes);

return true;
}

#endif // MSWIND


// Liefert aktuell eingestellten SichtContainer -------------------------------
bool Sicht :: GetCont (ObjContainer &) 
{
#if 0
// nur wenn Version mindestens 007 ist
	if (GetDBVersion() <= VERSION05000006) return false;

	if (_SatzNr == 0) {		// Sicht existiert nicht 
		db_error (WC_NOTFOUND, RC_SichtGetCont);
		return -1L;
	}

// SichtKopfSatz einlesen
sicht locSicht;
DB_ADDR dbaSICHT (DB().DBDesc());

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = _SatzNr;
	if ((ErrCode)z_readrec (&dbaSICHT, &locSicht) != EC_OKAY)
		return -1L;

// wenn Container nicht gegeben ist, dann false liefern
	if (locSicht.rxmin == 0 && locSicht.rxmax == 0 &&
	    locSicht.rymin == 0 && locSicht.rymax == 0)
		return false;

	OC.XMin() = locSicht.rxmin;
	OC.XMax() = locSicht.rxmax;
	OC.YMin() = locSicht.rymin;
	OC.YMax() = locSicht.rymax;
#endif
return true;	// alles in Butter
}

// EInstellen der ObjektNummer, an dem geclippt werden soll -------------------
bool Sicht :: SetCont (ObjContainer &)
{
#if 0
// nur wenn Version mindestens 007 ist
	if (GetDBVersion() <= VERSION05000006) return false;

	if (_SatzNr == 0) {		// Sicht existiert nicht 
		db_error (WC_NOTFOUND, RC_SichtSetCont);
		return -1L;
	}

// noch nicht gelesen
sicht locSicht;
DB_ADDR dbaSICHT (DB().DBDesc());
ErrCode RC;

	dbaSICHT.file_no = SICHT;	// SichtKopfSatz einlesen
	dbaSICHT.rec_no = _SatzNr;
	Read (dbaSICHT, locSicht);

// neuen SichtContainer setzen
	locSicht.rxmin = OC.XMin();
	locSicht.rxmax = OC.XMax();
	locSicht.rymin = OC.YMin();
	locSicht.rymax = OC.YMax();
	Write (dbaSICHT, locSicht);
#endif
return true;
}

// MerkmalsInfo an Sichtschreiben/lesen ---------------------------------------
ErrCode Sicht :: PutMiText (long lMCode, char *pText)
{
// nur wenn Version neuer als 006 ist
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

ErrCode RC;

	if (_SatzNr == 0) {     // Sicht existiert nicht 
	// neuen SichtEintrag anlegen
	struct sicht locSicht;
	DB_ADDR dbaSICHT (DB().DBDesc());

		dbaSICHT.file_no = SICHT;
		memset (&locSicht, '\0', sizeof(locSicht));
		strncpy (locSicht.sichtname, _SichtName, SIGHTNAMESIZE);
		locSicht.objrgn = -1;
		
		DB().SetDirty();
		__New (dbaSICHT, locSicht);
		_SatzNr = (short)dbaSICHT.rec_no;
	}

	DB().SetDirty();
	if ((RC = (ErrCode)delmi (DB().DBDesc(), lMCode, _SatzNr, SICHT)) != EC_OKAY && RC != WC_NOTFOUND)
		return RC;
	RC = (ErrCode):: PutMiText (DB().DBDesc(), lMCode, _SatzNr, SICHT, pText, FALSE);

// Merkmals-Integrität testen
#if defined(_DEBUG)
string strName = _SichtName;

	OemToAnsi (strName.c_str(), (LPSTR)strName.c_str());	// _SichtName ist bereits konvertiert
	TX_ASSERT(EC_OKAY == TestSichtMerkmal (DB(), strName.c_str(), lMCode, g_iKonsFlags));
#endif // _DEBUG

return RC;
}

ErrCode Sicht :: GetMiText (long lMCode, char **pText)
{
// nur wenn Version neuer als 006 ist
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

	if (_SatzNr > 0) 
		return (ErrCode):: GetMiText (DB().DBDesc(), lMCode, _SatzNr, SICHT, pText);
	else
		return (ErrCode)db_error (WC_NOTFOUND, RC_SichtGetMiText);
}

ErrCode Sicht :: DelMiText (long lMCode)
{
// nur wenn Version neuer als 006 ist
	if (DB().GetDBVersion() < VERSION05000008) return EC_OKAY;

	if (_SatzNr > 0) {
		DB().SetDirty();
		return (ErrCode):: delmi (DB().DBDesc(), lMCode, _SatzNr, SICHT);
	} else
		return (ErrCode)db_error (WC_NOTFOUND, RC_SichtDelMiText);
}

#if defined (MSWIND)

// return: die ObjTypen, die zwar vertreten aber nicht definiert sind
// piGot: die wirklich definierten ObjTypen
short Sicht :: GetCompleteVisInfo (long lIdent, HPALETTE hPal, 
				   VisInfo ** ppVI, short iBits, short *piGot)
{
ErrInstall EI (WC_NOTFOUND);
short fRet = 0;

	if (NULL != piGot) *piGot = 0;		// Resultat initialisieren

	if (iBits & TPPunkt) {
		if (ReadVisInfoFromSight (lIdent, hPal, ppVI[0], VT_Punkt)) {
			if (NULL == ppVI[0])
				fRet |= TPPunkt;
			if (NULL != piGot)
				*piGot |= TPPunkt;
		}
	}
	if (iBits & TPLinie) {
		if (ReadVisInfoFromSight (lIdent, hPal, ppVI[1], VT_Linie)) {
			if (NULL == ppVI[1])
				fRet |= TPLinie;
			if (NULL != piGot)
				*piGot |= TPLinie;
		}
	}
	if (iBits & TPFlaeche) {
		if (ReadVisInfoFromSight (lIdent, hPal, ppVI[2], VT_Flaeche)) {
			if (NULL == ppVI[2])
				fRet |= TPFlaeche;
			if (NULL != piGot)
				*piGot |= TPFlaeche;
		}
	}
	if (iBits & TPText) {
		if (ReadVisInfoFromSight (lIdent, hPal, ppVI[3], VT_Text)) {
			if (NULL == ppVI[3])
				fRet |= TPText;
			if (NULL != piGot)
				*piGot |= TPText;
		}
	}

return fRet;
}

                                       
// Einlesen einer gesuchten VisInfo aus einer Sicht ---------------------------
bool Sicht :: ReadVisInfoFromSight (long lIdent, HPALETTE hPal, 
				    VisInfo *& pVI, VisType iVTyp)
{
ErrCode RC;

	if ((RC = GetIDfromSight (lIdent, &pVI, iVTyp)) != EC_OKAY) {
		if (RC != WC_NOTFOUND && RC != WC_RETURN) 
			return false;
	} 
	if (hPal != 0 && pVI != NULL)	// Palette evtl. erweitern
		ExpandPalette (hPal, pVI);

return RC == WC_RETURN ? true : false;
}


ErrCode GetCompleteDefaultVisInfo (GeoDB &rDB, long lIdent, HPALETTE hPal, 
				   VisInfo **ppVI, short iBits, short *piGot)
{
ErrCode RC = EC_OKAY;
ErrInstall EI (WC_NOTFOUND);

	if (NULL != piGot) *piGot = 0;

	if (ppVI[0] == NULL && iBits & TPPunkt) {
		RC = ReadVisInfoFromDefaultSight (rDB, lIdent, hPal, ppVI[0], VT_Punkt);
		if (RC != EC_OKAY && RC != WC_RETURN) return RC;
		if (NULL != piGot) *piGot = TPPunkt;
	}
	if (ppVI[1] == NULL && iBits & TPLinie) {
		RC = ReadVisInfoFromDefaultSight (rDB, lIdent, hPal, ppVI[1], VT_Linie);
		if (RC != EC_OKAY && RC != WC_RETURN) return RC;
		if (NULL != piGot) *piGot = TPLinie;
	}
	if (ppVI[2] == NULL && iBits & TPFlaeche) {
		RC = ReadVisInfoFromDefaultSight (rDB, lIdent, hPal, ppVI[2], VT_Flaeche);
		if (RC != EC_OKAY && RC != WC_RETURN) return RC;
		if (NULL != piGot) *piGot = TPFlaeche;
	}
	if (ppVI[3] == NULL && iBits & TPText) {
		RC = ReadVisInfoFromDefaultSight (rDB, lIdent, hPal, ppVI[3], VT_Text);
		if (RC != EC_OKAY && RC != WC_RETURN) return RC;
		if (NULL != piGot) *piGot = TPText;
	}
	
return EC_OKAY;
}

ErrCode ReadVisInfoFromDefaultSight (GeoDB &rDB, long lIdent, HPALETTE hPal, 
				     VisInfo *& pVI, VisType iVTyp)
{
ErrCode RC;

	if ((RC = GetDefaultIDVisInfo (rDB, lIdent, &pVI, iVTyp)) != EC_OKAY) {
		if (RC != WC_NOTFOUND) 
			return RC;
	} else if (hPal != 0)		// Palette evtl. erweitern
		ExpandPalette (hPal, pVI);

return EC_OKAY;
}

// vorhandene VisInfo im Defaultsicht wegschreiben ----------------------------
ErrCode SetCompleteDefaultVisInfo (GeoDB &rDB, long lIdent, VisInfo **ppVI, short iBits)
{
ErrCode RC = EC_OKAY;
ErrInstall EI (WC_NOTFOUND);

	if (ppVI[0] != NULL && iBits & TPPunkt) 
		DBASSERT (AddIDtoDefaultSight (rDB, lIdent, ppVI[0]));
	if (ppVI[1] != NULL && iBits & TPLinie) 
		DBASSERT (AddIDtoDefaultSight (rDB, lIdent, ppVI[1]));
	if (ppVI[2] != NULL && iBits & TPFlaeche)
		DBASSERT (AddIDtoDefaultSight (rDB, lIdent, ppVI[2]));
	if (ppVI[3] != NULL && iBits & TPText)
		DBASSERT (AddIDtoDefaultSight (rDB, lIdent, ppVI[3]));

return EC_OKAY;
}

ErrCode Sicht :: SetCompleteVisInfo (long lIdent, VisInfo **ppVI, short iBits)
{
ErrCode RC = EC_OKAY;
ErrInstall EI (WC_NOTFOUND);

	if (ppVI[0] != NULL && iBits & TPPunkt) 
		DBASSERT (AddIDtoSight (lIdent, ppVI[0]));
	if (ppVI[1] != NULL && iBits & TPLinie) 
		DBASSERT (AddIDtoSight (lIdent, ppVI[1]));
	if (ppVI[2] != NULL && iBits & TPFlaeche)
		DBASSERT (AddIDtoSight (lIdent, ppVI[2]));
	if (ppVI[3] != NULL && iBits & TPText)
		DBASSERT (AddIDtoSight (lIdent, ppVI[3]));

return EC_OKAY;
}

// Diese Funktion besorgt aus der DefaultSicht alle vorhandenen Typen zu einem
// Identifikator
short GetDefaultTypes (GeoDB &rDB, long lIdent, short fAll)
{
Sicht DefSight (rDB, ResString (IDS_DEFAULTVISINFO, 40));

	return DefSight.GetTypes (lIdent, fAll);
}
#endif

short Sicht :: GetTypes (long lIdent, short fAll)
{
// SichtSatz einlesen
DB_ADDR dba (DB().DBDesc());
sicht locSicht;

	if (_SatzNr == 0) {		// Sicht existiert nicht 
		db_error (WC_NOTFOUND, RC_FindTarget);
		return 0;
	}
	dba.file_no = SICHT;
	dba.rec_no = _SatzNr;
	if (z_readrec (&dba, &locSicht) != EC_OKAY) return 0;

// ersten Satz im Set merken
short nSet = locSicht.idset;          // erster IDSatz

// TargetSatz im Set suchen
attribs Attr;
short fTypes = 0;

	memset (&Attr, '\0', sizeof(Attr));	// NullSetzen
	dba.file_no = ATTRIBS;                  // Dateinummer
	do {
		if ((dba.rec_no = nSet) == 0 || 
		    ((unsigned long)Attr.attTarget > (unsigned long)lIdent)) 
			break;		// fertig

		if (z_readrec (&dba, &Attr) != EC_OKAY) return fTypes;
		nSet = Attr.attSet;

	// suchen bis Target übereinstimmt
		if (Attr.attTarget == lIdent) {
			if (fAll) 
				fTypes |= VisTypeToBits ((VisType)Attr.attFlag, Attr.attDefVis);
			else if ((VisType)Attr.attFlag == VT_Default)
				fTypes |= Attr.attDefVis;
		}
	} while (true);

return fTypes;
}


// Liefert eine VisInfo für einen der Idents dieser Sicht ---------------------
bool Sicht :: RetrieveVisInfo (long lIdent, short iVTyp, VISINFO &rVI)
{
VisInfo *pVI = NULL;

	if (GetIDfromSight (lIdent, &pVI, iVTyp) != EC_OKAY)
		return false; 
	
	if (pVI == NULL) return false;

	pVI -> CopyTo (rVI);
	delete pVI;

	if (iVTyp == VT_Default) {	// sonstige Typen lesen
		TX_ASSERT(TIsValidAddress(&rVI, sizeof(DVISINFO), true));
		((DVISINFO &)rVI).m_iDefTypes = GetTypes (lIdent, false);
	}
	
return true;
}

///////////////////////////////////////////////////////////////////////////////
// Helper für VisInfo
_TRIAS02_ENTRY VisInfo *MakeNewVI (VisType iVTyp) 
{
VisInfo *pNewVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pNewVI = new CDefaultPVisInfo();
		break;

	case VT_Linie:
		pNewVI = new CDefaultLVisInfo();
		break;

	case VT_Flaeche:
		pNewVI = new CDefaultFVisInfo();
		break;

	case VT_Text:
		pNewVI = new CDefaultTVisInfo();
		break;

	case VT_Default:
		pNewVI = new CDefaultVisInfo();
		break;
	}

return pNewVI;
}

// Funktion, die DefaultVisInfo typgerecht generiert --------------------------
_TRIAS02_ENTRY 
short MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, bool fSpecial)
{
// wenn alle gebraucht werden, aber keiner da ist, dann EINEN DefaultSatz 
// generieren
short fRet = 0;

	if (iBits == TPAll && fSpecial &&
	    ppVI[0] == NULL && ppVI[1] == NULL &&
	    ppVI[2] == NULL && ppVI[3] == NULL)
	{
		ppVI[0] = MakeNewVI (VT_Default);
		return TPAll;		// ACHTUNG: SonderFall
	} 
	if (ppVI[0] == NULL && iBits & TPPunkt) {
		ppVI[0] = MakeNewVI (VT_Punkt);
		fRet |= TPPunkt;
	}
	if (ppVI[1] == NULL && iBits & TPLinie) {
		ppVI[1] = MakeNewVI (VT_Linie);
		fRet |= TPLinie;
	}
	if (ppVI[2] == NULL && iBits & TPFlaeche) {
		ppVI[2] = MakeNewVI (VT_Flaeche);
		fRet |= TPFlaeche;
	}
	if (ppVI[3] == NULL && iBits & TPText) {
		ppVI[3] = MakeNewVI (VT_Text);
		fRet |= TPText;
	}

return fRet;	// normaler Verlauf
}


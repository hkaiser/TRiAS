// Memberfunktionen für Nomenklaturanzeige ------------------------------------
// File: NOMENKL.CXX

#include "triaspre.hxx"

#include "nomenkl.hxx"
#include "schrank.hxx"

extern Bool Nomen10CFlag, Nomen25CFlag, Nomen50CFlag;   // einer der Modi ist aktiv 
extern pWindow CurrActW;
extern SchrankSchnulli *pSchrank;
extern Bool SchrankCFlag;

extern NomenklaturDlg *pNomenkl;

// MenuSelectBearbeitungen ----------------------------------------------------
void IrisWind :: MenuSelectNomen10 (void) 
{
        if (Nomen10CFlag) {             // Anzeige ganz ausschalten
                if (pNomenkl) {
                        pNomenkl -> Hide();
                        delete pNomenkl;
                        pNomenkl = NULL;
                        if (pSchrank) {
                                pSchrank -> Hide();
                                delete pSchrank;
                                pSchrank = NULL;
                                SchrankCFlag = FALSE;
                        }
                }
        } else if (Nomen25CFlag || Nomen50CFlag) {      // Mode Wechseln
                Nomen25CFlag = Nomen50CFlag = FALSE;
                pNomenkl -> SetMode(M10000);
        } else {
                if (!pNomenkl)
                        pNomenkl = new NomenklaturDlg (this, M10000, DBO().pCT());
                pNomenkl -> Show();     // neu anzeigen
                SetFocus();
                ValidateWindow();       // kein RePaint()
        }
        Nomen10CFlag = !Nomen10CFlag;
}

void IrisWind :: MenuSelectNomen25 (void) 
{
        if (Nomen25CFlag) {             // Anzeige ganz ausschalten
                if (pNomenkl) {
                        pNomenkl -> Hide();
                        delete pNomenkl;
                        pNomenkl = NULL;
                        if (pSchrank) {
                                pSchrank -> Hide();
                                delete pSchrank;
                                pSchrank = NULL;
                                SchrankCFlag = FALSE;
                        }
                }
        } else if (Nomen10CFlag || Nomen50CFlag) {      // Mode Wechseln
                Nomen10CFlag = Nomen50CFlag = FALSE;
                pNomenkl -> SetMode(M25000);
        } else {
                if (!pNomenkl)
                        pNomenkl = new NomenklaturDlg (this, M25000, DBO().pCT());
                pNomenkl -> Show();     // neu anzeigen
                SetFocus();
                ValidateWindow();       // kein RePaint()
        }
        Nomen25CFlag = !Nomen25CFlag;
}

void IrisWind :: MenuSelectNomen50 (void) 
{
        if (Nomen50CFlag) {             // Anzeige ganz ausschalten
                if (pNomenkl) {
                        pNomenkl -> Hide();
                        delete pNomenkl;
                        pNomenkl = NULL;
                        if (pSchrank) {
                                pSchrank -> Hide();
                                delete pSchrank;
                                pSchrank = NULL;
                                SchrankCFlag = FALSE;
                        }
                }
        } else if (Nomen10CFlag || Nomen25CFlag) {      // Mode Wechseln
                Nomen10CFlag = Nomen25CFlag = FALSE;
                pNomenkl -> SetMode(M50000);
        } else {
                if (!pNomenkl)
                        pNomenkl = new NomenklaturDlg (this, M50000, DBO().pCT());
                pNomenkl -> Show();     // neu anzeigen
                SetFocus();
                ValidateWindow();       // kein RePaint()
        }
        Nomen50CFlag = !Nomen50CFlag;
}


// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

NomenklaturDlg :: NomenklaturDlg (pWindow pW, Masstab M, CoordTrans *pCT)
                : ModeLessDialog (pW, ResID (NOMENKLATUR)),
                  Nomenklatur (this, ResID (IDT_NOMENKLATUR)),
                  NomenklaturTyp (this, ResID (IDT_NOMENTYP)),
                  _pCT (pCT)
{
// Fenster in linke untere Ecke Positionieren
        ChangePosition (Point (0, 54));
        _M = M_INVALID;         // initialisieren, damit SetMode klappt
        SetMode (M);            // Maástab und Text setzen
}

#pragma warning (default: 4355)

// Anzeige der aktuellen Koordinaten
void NomenklaturDlg :: SetCoords (Point &inPt) 
{
// Koordinaten in DB-Koordinaten umsetzen
Punkt Pt = DCtoOC (inPt);       // Device --> Objekt

// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
double XOut, YOut;

        pCT() -> UnScale (Pt, &XOut, &YOut);

// temporäre Zeichenkette
char OutBuff[20], InBuff[20];

// Nomenklatur berechnen und anzeigen
        GetNomenklatur (YOut, XOut, OutBuff, _M);
        Nomenklatur.GetText (InBuff, 20);
        if (strcmp (InBuff, OutBuff)) {
        // nur neue (veränderte) Nomenklatur ausgeben
                Nomenklatur.SetText (OutBuff);
                if (pSchrank) 
                        pSchrank -> SetFach (OutBuff);
        }
}

// Abfrage, ob Fenster geschlossen werden soll
Bool NomenklaturDlg :: QueryClose (Event) 
{
        Nomen25CFlag = FALSE;
        Nomen50CFlag = FALSE;
        Nomen10CFlag = FALSE;

return TRUE;            // auf jeden Fall raus
}

// neuen Mode einstellen
void NomenklaturDlg :: SetMode (Masstab newMode) {

        if (newMode != _M) {
                _M = newMode;
                switch (_M) {
                case M25000:
                        NomenklaturTyp.SetText (ResString (IDS_25000, 20));
                        break;

                case M50000:
                        NomenklaturTyp.SetText (ResString (IDS_50000, 20));
                        break;

                case M10000:
                        NomenklaturTyp.SetText (ResString (IDS_10000, 20));
                        break;

                case M_INVALID:
                        break;
                }
        }
}


char *NomenklaturDlg :: GetNomenklatur (double gh, double gr, char *nom, Masstab M) {
double          b, l;
int             nl100, nb100, n100, nl50, nb50, n50, nl25, nb25, n25, nl10, nb10, n10;
char            mn, mill;
/* Einlesen breite,l„nge, bzw. irc = gaugeo(...)  */

        if (gaugeo (&gh, &gr, &b, &l) < 0) {
                strcpy (nom, ResString (IDS_KOORDERR, 30));
                return nom;
        }
/* b = gh; l = gr; */
        b /= 3600.0;
        l /= 3600.0;
        if (b < 48.0 || b > 56.0 || l < 6.0 || l > 18.0) {
                strcpy (nom, ResString (IDS_NOKARTE, 30));
                return nom;
        }
        if (b >= 52.0) {
                mn = 'N';
                b = 12.- (b - 52.0) * 3.;
        } else {
                mn = 'M';
                b = 12.- (b - 48.0) * 3.;
        }
        if (l >= 12.0) {
                mill = '3';
                l = (l - 12.0) * 2.;
        } else {
                mill = '2';
                l = (l - 6.0) * 2.;
	}

	nl100 = (l < 12.0) ? (int)l : 11;
	nb100 = (b < 12.0) ? (int)b : 11;
	n100 = nb100 * 12 + nl100 + 1;  /* 1 <= n100 <= 144 */
	b = (b - nb100) * 8;
	l = (l - nl100) * 8;

	nb50 = (int)((b + 4) / 8);
	b = b - nb50 * 4;
	nl50 = (int)((l + 4) / 8);
	l = l - nl50 * 4;
	n50 = 2 * nb50 + nl50;
	nb25 = (int)((b + 2) / 4);
	b = b - nb25 * 2;
	nl25 = (int)((l + 2) / 4);
	l = l - nl25 * 2;
	n25 = 2 * nb25 + nl25;
	nb10 = (int)((b + 1) / 2);
//      b = b - nb10;
	nl10 = (int)((l + 1) / 2);
//      l = l - nl10;
	n10 = 2 * nb10 + nl10 + 1;

	wsprintf (nom, ResString (IDS_NOMENKL, 30).Addr(), mn, mill, n100, 'A' + n50, 'a' + n25, n10);
	switch (M) {
	case M25000:    nom[12] = '\0'; break;
	case M50000:    nom[10] = '\0'; break;
	case M10000:    // nicht ver„ndern
	case M_INVALID: // Fehler ignorieren
	default:        break;
	}

return nom;
}

// Eventhandler für FocusChangeEvt --------------------------------------------
void NomenklaturDlg :: FocusChange (FocusChangeEvt /* e */) {}
#if 0
	if (!e.gotFocus()) {	// hat Focus abgegeben
		CurrActW -> SetFocus();
//		((IrisWind *)CurrActW) -> ValidateWindow();
	}
}
#endif


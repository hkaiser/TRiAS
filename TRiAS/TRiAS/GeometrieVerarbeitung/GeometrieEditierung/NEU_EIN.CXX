// Eingaben bei Neuerfassung
// File: NEU_EIN.CXX
// W. Mörtl


#include "geoeditp.hxx"

#include "kreis.hxx"	// Vollkreis, Kreisbogen

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



// externe Variable
extern ResourceFile* pRF;





// ------------------------------------------------------------------------------------------------
// Konstruktor
#if defined (MSCC8)
#pragma warning (disable: 4355)	// Ausschalten von uninteressanten Warnungen
#endif
NeuEditDlg :: NeuEditDlg (pWindow pW, IdentList& IL, EObjekt* pEO, char* pcObjName, Punkt* pZuZiePkt)
	  		: DialogWindow (pW, ResID (IDD_NEUERFASSUNG, pRF)),
			 m_IdentListe (this, IDL_IDENTIFIKATOR),
			 _ObjName (this, IDE_OBJNAME),
			 _XKoord (this, IDE_XKOORD),
			 _YKoord (this, IDE_YKOORD),
			 _Rahmen (this, IDG_SPEICHERFORM),
			 _Temporaer (this, IDR_TEMPORAER),
			 _Permanent (this, IDR_PERMANENT),
			 _OKButton (this, IDOK),
			 _FortsetzButton (this, IDB_FORTSETZEN),
			 _ZuZiehButton (this, IDB_ZUZIEHEN),
			 _LoeschButton (this, IDB_LOESCHEN),
			 _InselButton (this, IDB_INSEL),
			 _KreisButton (this, IDB_KREIS),
		     _IL (IL)
{
	TX_ASSERT (pEO != NULL);
	TX_ASSERT (pcObjName != NULL);

// Standardwerte einstellen
	_pEO = pEO;
	_pcObjName = pcObjName;
	_pW = pW;
	m_pZuZiePkt = pZuZiePkt;
	StandardWerte ();
	DialogBoxCaption ();

	if ((DEX_QueryMode() & QMSysAdmin) == 0)
	{
		_Rahmen.Hide();		// verstecken
		_Temporaer.Hide();
		_Permanent.Hide();
	}
}
#if defined (MSCC8)
#pragma warning (default: 4355)
#endif



// ------------------------------------------------------------------------------------------------
// Destruktor
NeuEditDlg :: ~NeuEditDlg (void)
{
}



// ------------------------------------------------------------------------------------------------
// Reaktion auf Button-Click
void _GEOEDIT_EXPORT NeuEditDlg :: ButtonClick (ControlEvt e)
{
	if (_Temporaer.GetState())	// Speicherform ermitteln
		_sfSForm = SFORM_TEMP;
	else
		_sfSForm = SFORM_PERM;
	Focus ();	// 1. Eingabestelle bei Objektname
	OKB ();		// OK-Button einstellen
	
	switch ((uint) e.GetControlID())
	{
		case IDCANCEL:			// Editierung verwerfen
			idb_cancel ();
			EndDlg (VERWERFEN);
			break;

		case IDOK:              // Objekt abspeichern und bei Fläche vorher zuziehen
			idb_ok ();
			EndDlg (BEENDEN);			
			break;

		case IDB_FORTSETZEN:	// aktuelle Editierung fortsetzen
			idb_fortsetzen ();
			EndDlg (FORTSETZEN);
			break;
			
		case IDB_ZUZIEHEN:		// bei Editierung eines Linienobjektes dieses zuziehen
			idb_zuziehen ();
			break;

		case IDB_LOESCHEN:		// Löschen des zuletzt editierten Stützpunktes
			idb_loeschen ();
			break;

		case IDB_INSEL:			// bei Fläche mit den folgenden Punkten eine Insel aufbauen
			idb_insel ();
			EndDlg (INSEL);
			break;

		case IDB_KREIS:			// aus 3 Stützpunkten einen Kreis bzw. Kreisbogen konstruieren
			idb_kreis ();
			break;

		default:
			TX_ASSERT (false);
			break;
	}
} // ButtonClick


// ------------------------------------------------------------------------------------------------
// DoppelClick auf ListBox für Identifikator-Auswahl
void _GEOEDIT_EXPORT NeuEditDlg :: ListBoxClk (ControlEvt)
{
	m_ulIdent = IdentErmitteln ();  // ausgewählten Identifikator ermitteln
	Focus ();	// 1. Eingabestelle bei Objektname
	OKB ();	// OK-Button einstellen
} // ListBoxClk


// ------------------------------------------------------------------------------------------------
// Click auf ListBox für Identifikator-Auswahl
void _GEOEDIT_EXPORT NeuEditDlg :: ListBoxSel (ControlEvt)
{
	m_ulIdent = IdentErmitteln ();  // ausgewählten Identifikator ermitteln
	Focus ();	// 1. Eingabestelle bei Objektname
	OKB ();		// OK-Button einstellen
} // ListBoxSel


// ------------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in eines der Editierfelder
void _GEOEDIT_EXPORT NeuEditDlg :: EditChange (ControlEvt e)
{
	switch ((uint) e.GetControlID ())
	{
		case IDE_OBJNAME:
			if (_ObjName.GetTextLen() > 0)
				_ObjName.GetText (_pcObjName, maxTextLaenge+1);
			break;

		case IDE_XKOORD:
		case IDE_YKOORD:
			if (! _bIntern)		// dieser Zweig wurde nicht durch programm-interne Modifikation der
								//   Editierfelder XKoord bzw. YKoord erreicht
				_bPtKorr = true;	// sondern: Koordinaten wurden extern durch Anwender verändert
			break;

		default:
			TX_ASSERT (false);
			break;
	}
	
	OKB ();	// OK-Button einstellen
} // EditChange


// ------------------------------------------------------------------------------------------------
// Einstellung von Standardwerten
void NeuEditDlg :: StandardWerte (void)
{
// Variablen initialisieren
	m_pCT = new CoordTransX ();
	if (m_pCT == NULL) return;

CEierUhr Wait (_pW);

// ListBox mit Identifikatoren füllen
CTable t (_IL);
char pcOutBuff [64];

	for (t.First(); t.Valid(); t.Next())
	{
	IdentListEntryLock l(t);                                        
	
		if (!l) continue;
		ClassFromIdentX (l -> Ident(), pcOutBuff);
		strcat (pcOutBuff, ":");
		strcat (pcOutBuff, l -> KText());
		m_IdentListe.AddString (pcOutBuff);
	}
		
short iIndex;	// Index des zuletzt verwendeten Identifikators in der Identifikatorliste
    
	m_ulIdent = DEX_GetLastIdent ();	// den zuletzt verwendeten Identifikator geben lassen
	if (m_ulIdent != -1L)
	{
		ClassFromIdentX (m_ulIdent, pcOutBuff);
		iIndex = m_IdentListe.FindString (pcOutBuff);
		m_IdentListe.ChangeCurrentIndex (iIndex);	// den zuletzt selektierten Identifikator wieder selektieren
	}
	else	// bisher noch kein Identifikator selektiert
	{
		m_IdentListe.ChangeCurrentIndex (0);	// den ersten Identifikator  selektieren
		m_ulIdent = IdentErmitteln ();
	}

// Koordinaten des letzten editierten Punktes im Editierfeld anzeigen
KoOrd lRW, lHW;	// Rechts- und Hochwert (im KoOrd-Format) des zuletzt editierten Punktes

	switch (_pEO -> isA())
	{
		case OT_PUNKT:
			lRW = ((Punkt*)_pEO) -> X();
			lHW = ((Punkt*)_pEO) -> Y();
			break;
			
		case OT_KANTE:
		{
		long lSPAnz = ((Kante*)_pEO) -> ASP ();	// Anzahl der bis jetzt editierten Punkte
		
			lRW = ((Kante*)_pEO) -> SP(lSPAnz-1).X();
			lHW = ((Kante*)_pEO) -> SP(lSPAnz-1).Y();
		}
			break;
			
		case OT_FLAECHE:
		{
		short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen 
		long lSPA = ((Masche*)_pEO) -> KA(iKA-1).ASP ();	// Anzahl der Stützpunkte der letzten Kontur
		
			lRW = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-1).X();
			lHW = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-1).Y();
		}
			break;
					
		default:	// weder Punkt, Linie bzw. Fläche, was dann ?
			TX_ASSERT (false);
			return;
	}
	
	KoordDBToText (Punkt(lRW, lHW));	// stellt auch _bIntern = false
// StellenAnzahl() wird später wieder eingeführt, bedarf noch einer Klärung !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	StellenAnzahl (_XLen, _YLen);	// Anzahl der Vorkomma-Stellen von _XKoord und _YKoord ermitteln

// Zugriffsmode des Projektes ermitteln
short iZM = DEX_GetROMode();	// Abfrage des Zugriffsmodes auf das aktuelle Projekt
								// Schreibschutz (1), volle Schreibrechte (0) bzw. Fehlerfall (-1)

// RadioButton initialisieren
	if (iZM == -1)				// Datenbank nicht geöffnet
	{
		DEX_Error (RC_neu_ein, EC_NOOPEN);
	}
	else
	{
		if (iZM == 0)				// Datenbank nicht schreibgeschützt (R/W-Modus)
		{
			_Permanent.Enable();
			_Permanent.SetState (true);
			_sfSForm = SFORM_PERM;	// Speicherform: permanent
		}
		else if (iZM == 1)			// Datenbank schreibgeschützt (R/O-Modus)
		{
			_Permanent.Disable();
			_Temporaer.SetState (true);
			_sfSForm = SFORM_TEMP;	// Speicherform: temporär
		}
	}

short iKA = 0;	// Kantenanzahl bei Editierung einer Fläche

	if (_pEO->isA() == OT_FLAECHE)
		iKA = ((Masche*)_pEO) -> KantenAnz();
		
bool bHW0 = (_pEO->isA() == OT_FLAECHE && ((Masche*)_pEO) -> KA(iKA-1).ASP() >= 3);
		
// ZuZiehen-bzw. Kreis-Button nur freigeben bei Editierung einer Kante bzw. Fläche und
// wenn wenigstens schon 3 Stützpunkte von dieser Kante bzw. von der aktuell erfaßten
// Außen- bzw. Innenkontur erfaßt wurden
	if ((_pEO->isA() == OT_KANTE && ((Kante*)_pEO) -> ASP() >= 3) || bHW0)
	{
		_ZuZiehButton.Enable();
		_KreisButton.Enable();
	}
	else
	{
		_ZuZiehButton.Disable();
		_KreisButton.Disable();
	}

	// Ausnahme: Wenn m_pZuZiePkt != NULL, dann liegt Linienverlängerung vor; in diesem Fall
	// wird der _ZuZiehButton immer aktivieren
	if (m_pZuZiePkt)
		_ZuZiehButton.Enable();

// Löschen-Button nur bei Linien- und Flächeobjekt freigeben, wenn wenigstens 2 Punkte
// editiert wurden; Punktobjekt bzw. erster Punkt eines Linien- oder Flächenobjektes mit
// Abbrechen-Button eliminieren
bool bHW = ((_pEO->isA() == OT_PUNKT) ||
			(_pEO->isA() == OT_KANTE && ((Kante*)_pEO) -> ASP() == 1) ||
			(_pEO->isA() == OT_FLAECHE && ((Masche*)_pEO) -> ASP() == 1));
			
	if (bHW)
		_LoeschButton.Disable();
	else
		_LoeschButton.Enable();
	                                                            
// Insel-Button nur freigeben, wenn eine Fläche editiert wird und von der aktuell erfaßten
// Außen- bzw. Innenkontur wenigstens schon 3 Stützpunkte erfaßt wurden; dann bHW0 == true
	if (bHW0)
		_InselButton.Enable();
	else		
		_InselButton.Disable();
	
// OK-Button einstellen
	OKB ();
		
// für Punktobjekt ist der Fortsetzen-Button nicht sinnvoll		
	if (_pEO->isA() != OT_PUNKT) 
		_FortsetzButton.Enable();
	else
		_FortsetzButton.Disable();
	
// NumEdit initialiseren
	_XKoord.SetNumEditMode (NumEditX :: NEM_NoTest);
	_YKoord.SetNumEditMode (NumEditX :: NEM_NoTest);
	
// weitere Member initialisieren
	_bPtKorr = false;	// in _XKoord bzw. _YKoord wurden durch Anwender noch keine Änderungen vorgenommen	
	
// 1. Eingabestelle soll bei _ObjName sein, wenn permanente Abspeicherung gewählt wurde
	Focus ();
} // StandardWerte


// ------------------------------------------------------------------------------------------------
// den in m_IdentListe markierten Identifikator ermitteln
long NeuEditDlg :: IdentErmitteln (void)
{
ulong ulIdent = 0;
short iIndex = m_IdentListe.GetCurrentIndex ();

	if (-1 != iIndex)	// ein Identifikator wurde selektiert
	{
	char pcInBuff [64];

		m_IdentListe.GetString (pcInBuff, iIndex, sizeof(pcInBuff));
		IdentFromClassX (pcInBuff, &ulIdent);
	}
	if (0 != ulIdent)				// nur wenn wirklich neu, dann
		DEX_SetLastIdent (ulIdent);	// selektierten Identifikator TRiAS-weit bekanntgeben

	return ulIdent;
} // IdentErmitteln


// ------------------------------------------------------------------------------------------------
// Koordinaten-Konvertierung Text -> DB-Koordinaten
void NeuEditDlg :: KoordTextToDB (Punkt& ResultPkt)
{
// TEXTL ist in geokonst.hxx definiert
char pcBufferX [TEXTL];	// Konvertierungspuffer für x-
char pcBufferY [TEXTL];	//  bzw. y-Koordinate

	if (m_pCT)
	{
	double dRW, dHW;

		_XKoord.GetText (pcBufferX, TEXTL);
		_YKoord.GetText (pcBufferY, TEXTL);
	    if (m_pCT -> CoordTransToValueEx (pcBufferX, pcBufferY, dRW, dHW) == false)
			return;

		// Umwandlung der Real- in DB-Koordinaten (unter Berücksichtigung der internen Skalierung)
		RealInDBKoord (dRW, dHW, ResultPkt.X(), ResultPkt.Y(), m_pCT);
	}
	else
	{
		_XKoord.GetText (pcBufferX, 64);
		ResultPkt.X() = atol (pcBufferX);
		_YKoord.GetText (pcBufferY, 64);
		ResultPkt.Y() = atol (pcBufferY);
	}
} // KoordTextToDB


// ------------------------------------------------------------------------------------------------
// Koordinaten-Konvertierung Datenbank -> Text
void NeuEditDlg :: KoordDBToText (Punkt& Pt)
{
char pcBuffer [TEXTL];	// Konvertierungspuffer

	if (m_pCT)
	{
	double XOut, YOut;

		DBKoordInReal (Pt, XOut, YOut, m_pCT);

		// Umwandlung in Text für Anzeige im dblnumedit-Fenster
		m_pCT -> CoordTransToStringEx (XOut, YOut, true, pcBuffer, sizeof(pcBuffer));	// Rechtswert
		_bIntern = true;	// _XKoord und _YKoord werden intern modifiziert
		_XKoord.SetText (pcBuffer);
		m_pCT -> CoordTransToStringEx (XOut, YOut, false, pcBuffer, sizeof(pcBuffer));	// Hochwert
		_YKoord.SetText (pcBuffer);
	}
	else
	{
		_XKoord.SetText (ltoa (Pt.X(), pcBuffer, 10));
		_YKoord.SetText (ltoa (Pt.Y(), pcBuffer, 10));
	}

	_bIntern = false;
} // KoordDBToText


// ------------------------------------------------------------------------------------------------
// Anzahl der Vorkomma-Stellen von _XKoord und _YKoord bestimmen
void NeuEditDlg :: StellenAnzahl (short& iXL, short& iYL)
{
char pcBuffer [TEXTL];	// Konvertierungspuffer

	_XKoord.GetText (pcBuffer, TEXTL);

// Was wird mit Koordinaten in der Form 12°34'56" ????

char* pT = strchr (pcBuffer, '.');	
	
	iXL = strlen (pcBuffer);	// für den Fall, daß Koordinate keinen Dezimalpunkt enthält
	if (pT) iXL = pT - pcBuffer;

	_YKoord.GetText (pcBuffer, TEXTL);
	pT = strchr (pcBuffer, '.');
	iYL = strlen (pcBuffer);
	if (NULL != pT) iYL = pT - pcBuffer;
} // StellenAnzahl


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Abbruch-Button
// das bisher editierte Objekt wird auf dem Bildschirm gelöscht, es wird nichts abgespeichert;
// das EObjekt selbst wird in geoedit.cxx gelöscht
void NeuEditDlg :: idb_cancel (void)
{
	switch (_pEO -> isA())
	{
		case OT_PUNKT:
			break;
			
		case OT_KANTE:
			KanteNeuZeichnen ((Kante*)_pEO, _pW);
			break;
	
		case OT_FLAECHE:
		{
		short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen
		
			for (short i = iKA-1; i >= 0; i--)
				KanteNeuZeichnen (&((Masche*)_pEO)->KA(i), _pW);	// Löschen aller Konturen
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
} // idb_cancel


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des OK-Button
// Flächenobjekte bzw. dessen letzte editierte Insel automatisch zuziehen;
// die eigentliche Abspeicherung erfolgt in geoedit.cxx
void NeuEditDlg :: idb_ok (void)
{
	if (_bPtKorr)	// durch Anwender wurde _XKoord bzw. _YKoord verändert
		PunktKorrigieren ();
				
	// letzte Kontur einer Fläche zuziehen, wenn sie noch offen ist
	if (_pEO -> isA() == OT_FLAECHE)
		FlaecheZuziehen ((Masche*) _pEO);
	                                   
	// Objektname als char-String bereitstellen
	if (_ObjName.GetTextLen() > 0)
		_ObjName.GetText (_pcObjName, maxTextLaenge+1);
}


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Fortsetzen-Button
void NeuEditDlg :: idb_fortsetzen (void)
{
	if (_bPtKorr)	// durch Anwender wurde _XKoord bzw. _YKoord verändert
		PunktKorrigieren ();
				
	// Objektname als char-String bereitstellen
	if (_ObjName.GetTextLen() > 0)
		_ObjName.GetText (_pcObjName, maxTextLaenge+1);
}


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Zuziehen-Button
// Linien- bzw. Flächenobjekt wird zugezogen, d.h. der Anfangspunkt wird als Endpunkt
// hinzugefügt; Button wird erst aktiviert, wenn aktuelle Stützpunktanzahl >= 3 ist;
// Ausnahme: Wenn m_pZuZiePkt != NULL, dann liegt Linienverlängerung vor, in diesem Fall
// wird der _ZuZiehButton immer aktiviert
void NeuEditDlg :: idb_zuziehen (void)
{
Punkt AP;	// Anfangspunkt des Linien- bzw. Flächenobjektes

	if (_bPtKorr)	// durch Anwender wurde _XKoord bzw. _YKoord verändert
		PunktKorrigieren ();
				
	// Linienobjekt zuziehen
	if (_pEO -> isA() == OT_KANTE)
	{
	long lSPAnz = ((Kante*)_pEO) -> ASP ();	// Anzahl der bisher editierten Stützpunkte
	Punkt EP = ((Kante*)_pEO) -> SP(lSPAnz-1);	// zuletzt manuell editierter Stützpunkt

		if (NULL == m_pZuZiePkt)	// echte Neueditierung
		{
			AP.X() = ((Kante*)_pEO) -> SP(0).X();
			AP.Y() = ((Kante*)_pEO) -> SP(0).Y();
		}
		else						// Linienverlängerung
		{
			AP.X() = m_pZuZiePkt -> X();
			AP.Y() = m_pZuZiePkt -> Y();
		}
		((Kante*)_pEO) -> AddPunkt (&AP.X(), &AP.Y(), 1, -1);
	
		DrawLine (AP, EP, false, _pW);	// Linienobjekt auf Bildschirm zuziehen
	}

	// letzte Kontur einer Fläche zuziehen, wenn sie noch offen ist
	if (_pEO -> isA() == OT_FLAECHE)
	{
	short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen 
	
		AP = ((Masche*)_pEO) -> KA(iKA-1).SP(0);	// Anfangspunkt der letzten Kontur
		FlaecheZuziehen ((Masche*) _pEO);
	}
	                                   
	KoordDBToText (AP);	// Koordinaten des Anfangs-/Endpunktes anzeigen 
	
	// nach dem Zuziehen sind der Zuziehen- und der Fortsetzen-Button nicht mehr sinnvoll		
	_ZuZiehButton.Disable();
	_FortsetzButton.Disable();
} // idb_zuziehen


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Löschen-Button
// Löschen des zuletzt editierten Stützpunktes (kann mehrfach hintereinander ausgeführt werden);
// bei einem Punktobjekt bzw. wenn bei einem Linien- bzw. Flächenobjekt nur (noch) ein Stützpunkt
// vorhanden ist, wird der Löschen-Button deaktiviert; soll auch dieser Stützpunkt gelöscht werden,
// ist der Abbrechen-Button zu verwenden, der gleichzeitig das gesamte Objekt löscht
void NeuEditDlg :: idb_loeschen (void)
{
long lSPA;		// Anzahl der bisher editierten Stützpunkte eines Linienobjektes bzw. der
				// letzten Kontur eines Flächenobjektes
Punkt EP1, EP2;	// die beiden zuletzt manuell editierten Stützpunkte
short iKA = 0;	// Anzahl der bis jetzt editierten Konturen (nur für Flächenobjekt sinnvoll)
bool bInDel = false;	// letzter Punkt einer Innenkontur (und damit die gesamte Innenkontur) 
					// gelöscht (true), sonst false


	switch (_pEO -> isA())
	{
		case OT_PUNKT:

			TX_ASSERT (_pEO -> isA() != OT_PUNKT);

			return;		// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			
		case OT_KANTE:
		{
			lSPA = ((Kante*)_pEO) -> ASP ();

			if (lSPA <= 1)
			{
				TX_ASSERT (lSPA > 1);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
				
			// die letzte Strecke wird auf dem Bildschirm gelöscht
			EP2 = ((Kante*)_pEO) -> SP(lSPA-1);	// der letzte und
			EP1 = ((Kante*)_pEO) -> SP(lSPA-2);	//   der vorletzte manuell editierte Stützpunkt
			KoordDBToText (EP1);	// Koordinaten des vorletzten Punktes anzeigen
			((Kante*)_pEO) -> SubPunkt (1, lSPA-1);
		}
			break;
	
		case OT_FLAECHE:
		{
		long lSPAnz = ((Masche*)_pEO) -> ASP ();	// Gesamtanzahl der bisher editierten Stützpunkte
		
			iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen 
			lSPA = ((Masche*)_pEO) -> KA(iKA-1).ASP ();	// Anzahl der Stützpunkte der letzten Kontur
		
			if (lSPAnz <= 1 || lSPA == 0)
			{
				TX_ASSERT (lSPAnz > 1 && lSPA > 0);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
				
			// die letzte (von möglicherweise noch mehreren) Strecke der letzten Kontur wird auf dem
			// Bildschirm gelöscht
			if (lSPA >= 2)
			{
				EP2 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-1);	// der letzte und
				EP1 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-2);	//   der vorletzte manuell editierte
				KoordDBToText (EP1);	// Koordinaten des vorletzten Punktes anzeigen
				((Masche*)_pEO) -> SubPunkt (1, lSPA-1, iKA);
			}
			else	// es wird der letzte Stützpunkt einer Innenkontur gelöscht
			{
				((Masche*)_pEO) -> SubPunkt (1, lSPA-1, iKA);
				iKA--;
				EP2 = ((Masche*)_pEO) -> KA(iKA-1).SP(0);	// Anfangs-/Endpunktes der vorhergehenden Kontur
				KoordDBToText (EP2);
				bInDel = true;	// letzter Punkt einer Innenkontur (und damit gesamte Innenkontur) gelöscht
			}
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
			
	if (lSPA >= 2)		
		DrawLine (EP1, EP2, false, _pW);	// Strecke zwischen EP1 und EP2 auf Bildschirm löschen
			
	// Löschen-Button nur bei Linien- und Flächeobjekt freigeben, wenn wenigstens 2 Punkte
	// editiert wurden; Punktobjekt, ersten Punkt eines Linienobjektes bzw. ersten Punkt der
	// Außenkontur eines Flächenobjektes mit Abbrechen-Button eliminieren
bool bHW = ((_pEO->isA() == OT_PUNKT) ||
			(_pEO->isA() == OT_KANTE && ((Kante*)_pEO) -> ASP() == 1) ||
			(_pEO->isA() == OT_FLAECHE && ((Masche*)_pEO) -> ASP() == 1));
			
	if (bHW)
		_LoeschButton.Disable();
	else
		_LoeschButton.Enable();

bool bHW0 = (_pEO->isA() == OT_FLAECHE && ((Masche*)_pEO) -> KA(iKA-1).ASP() >= 3);
		
	// nach dem Löschen sind der Fortsetzen-Button und der ZuZiehen-Button wieder sinnvoll
	//(können durch Zuziehen-Button deaktiviert worden sein)		
	_FortsetzButton.Enable();
	if ((_pEO->isA() == OT_KANTE && ((Kante*)_pEO) -> ASP() >= 3) || bHW0)
	{
		_ZuZiehButton.Enable();
		_KreisButton.Enable();
	}
	else
	{
		_ZuZiehButton.Disable();
		_KreisButton.Disable();
	}

	if (m_pZuZiePkt)	// Ausnahme: Linienverlängerung
		_ZuZiehButton.Enable();
	
	if (bHW0)
		_InselButton.Enable();
	else		
		_InselButton.Disable();
		
	// Spezialfall: letzter Punkt einer Innenkontur (und damit gesamte Innenkontur) gelöscht
	if (bInDel)
	{		
		_FortsetzButton.Disable();
		_ZuZiehButton.Disable();
		_InselButton.Enable();
	}
} // idb_loeschen


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Insel-Button
// die aktuell editierte Kontur wird zugezogen und die Konturanzahl inkrementiert
void NeuEditDlg :: idb_insel (void)
{
	if (_bPtKorr)	// durch Anwender wurde _XKoord bzw. _YKoord verändert
		PunktKorrigieren ();

	if (_pEO -> isA() != OT_FLAECHE)
	{
		TX_ASSERT (_pEO -> isA() == OT_FLAECHE);
		return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
	}
		
	// letzte Kontur einer Fläche zuziehen, wenn sie noch offen ist
	FlaecheZuziehen ((Masche*) _pEO);
	                                   
	// Objektname als char-String bereitstellen
	if (_ObjName.GetTextLen() > 0)
		_ObjName.GetText (_pcObjName, maxTextLaenge+1);
}


// ------------------------------------------------------------------------------------------------
// Reaktion bei Betätigung des Kreis-Button
void NeuEditDlg :: idb_kreis (void)
{
	if (_bPtKorr)	// durch Anwender wurde _XKoord bzw. _YKoord verändert
		PunktKorrigieren ();
				
long lSPA;		// Anzahl der bisher editierten Stützpunkte eines Linienobjektes bzw. der
				// letzten Kontur eines Flächenobjektes
Punkt EP1, EP2, EP3;	// die 3 letzten manuell editierten Stützpunkte
short iKA;	// Anzahl der bis jetzt editierten Konturen (nur bei Flächenobjekt)

	switch (_pEO -> isA())
	{
		case OT_PUNKT:

			TX_ASSERT (_pEO -> isA() != OT_PUNKT);

			return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			
		case OT_KANTE:
		{
			lSPA = ((Kante*)_pEO) -> ASP ();

			if (lSPA <= 2)
			{
				TX_ASSERT (lSPA > 2);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
				
			EP1 = ((Kante*)_pEO) -> SP(lSPA-1);	// der letzte,
			EP2 = ((Kante*)_pEO) -> SP(lSPA-2);	//   der vorletzte und
			EP3 = ((Kante*)_pEO) -> SP(lSPA-3);	//   der vorvorletzte manuell editierte Stützpunkt
			
			// bei einer Linie, die aus genau 3 Punkten besteht und die in einen Vollkreis
			// umgewandelt werden soll, gibt es Probleme, wenn diese 3 Punkte zuerst gelöscht werden
			// (weil dann ja gar nichts mehr da wäre) und danach erst die neuen Punkte hinzugefügt werden;
			// da ich aber die Routine Masche -> SubPunkt nicht ändern will, werden in diesem Fall
			// erst die Kreispunkte hinzugefügt und danach die 3 Erzeuger-Punkte gelöscht
			if (lSPA > 3)	// Kreisbogen und kein Vollkreis						  
				((Kante*)_pEO) -> SubPunkt (3, lSPA-3);	// die 3 letzten Punkte löschen
		}		
			break;

		case OT_FLAECHE:
		{
		long lSPAnz = ((Masche*)_pEO) -> ASP ();	// Gesamtanzahl der bisher editierten Stützpunkte
		
			iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen 
			lSPA = ((Masche*)_pEO) -> KA(iKA-1).ASP ();	// Anzahl der Stützpunkte der letzten Kontur
		
			if (lSPAnz <= 2)
			{
				TX_ASSERT (lSPAnz > 2);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
			
			EP1 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-1);	// der letzte
			EP2 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-2);	//   der vorletzte und
			EP3 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-3);	//   der vorvorletzte manuell editierte
			  
			if (lSPA > 3)	// Kreisbogen und kein Vollkreis (s. OT_KANTE)						  
				((Masche*)_pEO) -> SubPunkt (3, lSPA-3, iKA);	// die 3 letzten Punkte löschen
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
        
	DrawLine (EP3, EP2, false, _pW);	// Linie zwischen EP3 und EP2 bzw.
	DrawLine (EP2, EP1, false, _pW);	//   zwischen EP2 und EP1 auf Bildschirm löschen
	
	if (lSPA == 3)	// genau 3 Stützpunkte editiert -> Vollkreis
	{
		Vollkreis (_pEO, EP3, EP2, EP1, _pW);
		if (_pEO -> isA() == OT_KANTE)			// Vollkreis bei Linie
			((Kante*)_pEO) -> SubPunkt (3, 0);			// die 3 ersten Punkte löschen
		if (_pEO -> isA() == OT_FLAECHE)		// Vollkreis bei Fläche
			((Masche*)_pEO) -> SubPunkt (3, 0, iKA);	// die 3 ersten Punkte löschen
		_ZuZiehButton.Disable();
		_KreisButton.Disable();
		_FortsetzButton.Disable();
	}
	else			// schon mehr als 3 Stützpunkte editiert -> Kreisbogen
		Kreisbogen (_pEO, EP3, EP2, EP1, _pW);
} // idb_kreis


// ------------------------------------------------------------------------------------------------
// Flächenobjekt zuziehen, wenn noch offen
void NeuEditDlg :: FlaecheZuziehen (Masche* pF)
{
	TX_ASSERT (pF != NULL);

	if (! pF) return;

short iKA = pF -> KantenAnz ();			// Anzahl der bis jetzt editierten Konturen 
long lSPA = pF -> KA(iKA-1).ASP ();		// Anzahl der Stützpunkte der letzten Kontur
Punkt AP = pF -> KA(iKA-1).SP(0);		// Anfangspunkt und
Punkt EP = pF -> KA(iKA-1).SP(lSPA-1);	// zuletzt editierter Stützpunkt der letzten Kontur
	
	if (lSPA <= 2 ||	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
		AP == EP)		// Kontur ist schon zugezogen
	{
		TX_ASSERT (lSPA > 2);
		return;
	}
		
	pF -> AddPunkt (&AP.X(), &AP.Y(), 1, -1, -1);	// zuziehen
	DrawLine (AP, EP, false, _pW);	// Flächenobjekt bzw. dessen letzte Insel auf Bildschirm zuziehen
} // FlaecheZuziehen


// ------------------------------------------------------------------------------------------------
// OK-Button einstellen; diesen Button nur freigeben, wenn
// - entsprechend des Objekttypes schon genügend Stützpunkte editiert wurden,
// - ein Identifikator vergeben wurde,
// - bei permanenter Abspeicherung (_sfSForm == SFORM_PERM) ein Objektname eingegeben wurde und
// - die Editierfelder für die Koordinaten die richtigen Vorkommastellen haben;
// bHW ist Hilfswert für Test, ob die Anzahl der schon editierten Stützpunkte es erlauben, den
// OK-Button freizugegeben; dann bHW == true	                            
void NeuEditDlg :: OKB (void)
{
short iKA = 0;	// Kantenanzahl bei Editierung einer Fläche

	if (_pEO->isA() == OT_FLAECHE)
		iKA = ((Masche*)_pEO) -> KantenAnz();
		
bool bHW = ((_pEO->isA() == OT_PUNKT) ||
			(_pEO->isA() == OT_KANTE && ((Kante*)_pEO) -> ASP() >= 2) ||
			(_pEO->isA() == OT_FLAECHE && ((Masche*)_pEO) -> KA(iKA-1).ASP() >= 3));
			
//short iXKS, iYKS;	// Anzahl der Vorkommastellen von _XKoord und _YKoord

//	StellenAnzahl (iXKS, iYKS);

	if (bHW && (m_ulIdent != -1L && m_ulIdent != 0) &&	
	    (_sfSForm == SFORM_TEMP ||
		(_sfSForm == SFORM_PERM && _ObjName.GetTextLen() > 0))/* &&
		_XLen == iXKS && _YLen == iYKS*/)
		_OKButton.Enable();
	else
		_OKButton.Disable();
} // OKB


// ------------------------------------------------------------------------------------------------
// 1. Eingabestelle soll bei _ObjName sein, wenn permanente Abspeicherung gewählt wurde
void NeuEditDlg :: Focus (void)
{
	if (_sfSForm == SFORM_TEMP)	// temporär
		_ObjName.Disable();	// kein Objektname angebbar
	else						// permanent
	{				                      
		_ObjName.Enable();
		_ObjName.SetText (_pcObjName);	// evtl. schon vorhandenen Objektnamen im Editierfeld anzeigen
		
	int iTL = _ObjName.GetTextLen();

		// aus der Textlänge die aktuelle Cursorposition (d.h. beide Parameter des Selection-
		// Objektes sind gleich) für SetFocus durch ChangeSelection aufbauen,
		_ObjName.ChangeSelection (Selection (iTL, iTL));
		_ObjName.SetFocus();
	}
} // Focus


// ------------------------------------------------------------------------------------------------
// letzten Punkt des aktuell editierten Objektes aufgrund von Eingaben des Anwenders modifizieren
void NeuEditDlg :: PunktKorrigieren (void)
{
Punkt NewPkt;	// neuer Punkt in DB-Koordinaten
					
	KoordTextToDB (NewPkt);	// DB-Koordinaten aus DoubleNumEdit rekonstruieren

long lSPA;		// Anzahl der bisher editierten Stützpunkte eines Linienobjektes bzw. der
				// letzten Kontur eines Flächenobjektes
Punkt EP1, EP2;	// die beiden (wenn schon vorhanden) zuletzt manuell editierten Stützpunkte


	switch (_pEO -> isA())
	{
		case OT_PUNKT:
			((Punkt*)_pEO) -> X() = NewPkt.X();	// Punktkoordinaten modifizieren
			((Punkt*)_pEO) -> Y() = NewPkt.Y();
			break;
			
		case OT_KANTE:
		{
			lSPA = ((Kante*)_pEO) -> ASP ();

			if (lSPA == 0)
			{
				TX_ASSERT (lSPA > 0);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
				
			// das Linienobjekt hat mindestens schon 2 Stützpunkte, so daß noch eine Linie auf dem
			// Bildschirm korrigiert werden muß
			if (lSPA >= 2)
			{
				EP1 = ((Kante*)_pEO) -> SP(lSPA-1);	// der letzte und
				EP2 = ((Kante*)_pEO) -> SP(lSPA-2);	//   der vorletzte manuell editierte Stützpunkt
				DrawLine (EP2, EP1, false, _pW);	// Linie auf Bildschirm löschen
				DrawLine (EP2, NewPkt, false, _pW);	// Linie neu zeichnen
			}
				
			// wenn gleich der 1. Punkt korrigiert wird, würde es, wenn zuerst die Routine
			// SubPunkt() ausgeführt werden würde, zu einem Fehler kommen, weil dadurch die
			// gesamte Linie gelöscht werden müßte; deshalb zuerst Routine AddPunkt()
			((Kante*)_pEO) -> AddPunkt (&NewPkt.X(), &NewPkt.Y(), 1, -1);	// Punkt neu aufnehmen
			((Kante*)_pEO) -> SubPunkt (1, lSPA-1);		//  und alten löschen
		}
			break;
	
		case OT_FLAECHE:
		{
		long lSPAnz = ((Masche*)_pEO) -> ASP ();	// Gesamtanzahl der bisher editierten Stützpunkte
		short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen 
		
			lSPA = ((Masche*)_pEO) -> KA(iKA-1).ASP ();	// Anzahl der Stützpunkte der letzten Kontur
		
			if (lSPAnz == 0)
			{
				TX_ASSERT (lSPAnz > 0);
				return;	// dieser Zweig dürfte eigentlich gar nicht erreicht werden
			}
			
			// letzte Kontur hat mindestens schon 2 Stützpunkte, so daß noch eine Linie auf dem
			// Bildschirm korrigiert werden muß
			if (lSPA >= 2)		
			{
				EP1 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-1);	// der letzte und
				EP2 = ((Masche*)_pEO) -> KA(iKA-1).SP(lSPA-2);	//  der vorletzte manuell editierte
				DrawLine (EP2, EP1, false, _pW);	// Linie zwischen EP1 und EP2 auf Bildschirm löschen
				DrawLine (EP2, NewPkt, false, _pW);	// Linie neu zeichnen
			}
			
			// wenn gleich der 1. Punkt einer Außenkontur korrigiert wird, würde es, wenn zuerst die
			// Routine SubPunkt ausgeführt werden würde, zu einem Fehler kommen, weil dadurch die gesamte
			// Kontur gelöscht werden müßte; deshalb zuerst Routine AddPunkt
			((Masche*)_pEO) -> AddPunkt (&NewPkt.X(), &NewPkt.Y(), 1, -1, -1);
			((Masche*)_pEO) -> SubPunkt (1, lSPA-1, iKA);	// Korr170895
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
} // PunktKorrigieren	


// ------------------------------------------------------------------------------------------------
// Überschrift der DialogBox durch Objekttyp ergänzen
void NeuEditDlg :: DialogBoxCaption (void)
{
char pcBuffer [TEXTL];

	GetCaption (pcBuffer, TEXTL);

char zz [] = ": ";	// Trennzeichen für Abtrennung eines evtl. schon eingetragenen Objekttyps
size_t len = strcspn (pcBuffer, zz);

	GetCaption (pcBuffer, len+1);
	strcat (pcBuffer, ": ");
	switch (_pEO -> isA())
	{
		case OT_PUNKT:
			strcat (pcBuffer, ResString (ResID (IDS_PUNKTOBJ, pRF), 40));
			break;
		case OT_KANTE:
			strcat (pcBuffer, ResString (ResID (IDS_LINIENOBJ, pRF), 40));
			break;
		case OT_FLAECHE:
		{
		short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen
		
			strcat (pcBuffer, ResString (ResID (IDS_FLAECHENOBJ, pRF), 40));
			if (iKA == 1)
				strcat (pcBuffer, ResString (ResID (IDS_AUSSENKON, pRF), 40));
			if (iKA > 1)
			{
			ResString Format (ResID (IDS_KONTURCNT, pRF), 40);
			char pcBuff [TEXTL];
			
				wsprintf (pcBuff, Format.Addr (), iKA-1);
				strcat (pcBuffer, pcBuff);
			}
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
	SetCaption (pcBuffer);
} // DialogBoxCaption

// Funktionen für Geometriefehler "entartetes Objekt"
// File: ENTARTET.CXX
// W. Mörtl

#include "GeoReinP.hxx"

#include <hdrentrx.hxx>		// HeaderEntryX

#include "entartet.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



// --------------------------------------------------------------------------------------------
Entartung :: Entartung (EObjekt& GO, int iKaNr)
		   : GeoFehler (GO)
{
	_iKaNr = iKaNr;

	if (OT_KANTE == GO.isA())
		_EPkt = ((EKante&)GO).SP(0);
	else
	{
		_ASSERTE (GO.isA() == OT_FLAECHE);
		_EPkt = ((EFlaeche&)GO).KA(_iKaNr).SP(0);
	}

	m_OTAlt = _GO.isA();
	if (OT_FLAECHE == m_OTAlt)
		m_iKCntAlt = ((EFlaeche&)GO).KantenAnz();
}


// --------------------------------------------------------------------------------------------
// CopyKonstruktor
Entartung :: Entartung (Entartung& EA)
		   : GeoFehler (EA._GO, EA._isCorrected)
{
	_iKaNr = EA._iKaNr;
	_EPkt = EA._EPkt;
	m_OTAlt = EA.m_OTAlt;
	if (OT_FLAECHE == m_OTAlt)
		m_iKCntAlt = EA.m_iKCntAlt;
	m_OTNeu = EA.m_OTNeu;
}


// --------------------------------------------------------------------------------------------
Entartung :: ~Entartung (void)
{
}
   
   
// --------------------------------------------------------------------------------------------
// Liefert true, wenn Eintrag in Fehlerliste möglich, sonst false
bool Entartung :: AddGeoFehler (GeoFehlerListe& GFL)
{
GeoFehlerCreator GFC (GFL);

	if (ContCreate (GFC, Entartung) (*this) != NULL)   // hier wird der CopyKonstruktor gerufen
		return true;
	DEX_Error (RC_entartet, EC_NOMEMORY);
	return false;
}


// --------------------------------------------------------------------------------------------
// Beschreibung des bereinigten bzw. unbereinigten Geometriefehlers als Merkmalstext in
// sAnalyseText eintragen; nur für Linien- bzw. Flächenobjekte; bereinigte Entartungen bei
// Innenkonturen (durch Löschen dieser Kontur) werden ausnahmsweise auch angezeigt
void Entartung :: AnalysePuffern (string& sAnalyseText, CoordTransX* pCT)
{
	_ASSERTE (m_OTAlt != OT_PUNKT);	// pCT kann NULL sein

	if (m_OTAlt == OT_PUNKT)	// Test ist für Punktobjekt nicht sinnvoll
		return;

string sBuffer;

	if (_isCorrected)
	{
	ResString resFTyp (ResID (IDS_TYPFLAECHE, pRF), 30);
	ResString resLTyp (ResID (IDS_TYPLINIE, pRF), 30);
	ResString resPTyp (ResID (IDS_TYPPUNKT, pRF), 30);
	string sTypAlt, sTypNeu;

		if (OT_FLAECHE == m_OTAlt) sTypAlt = resFTyp.Addr();
		else sTypAlt = resLTyp.Addr();	// m_OTAlt == OT_KANTE

		if (OT_KANTE == m_OTNeu)
			sTypNeu = resLTyp.Addr();
		else
			sTypNeu = resPTyp.Addr();	// m_OTNeu == OT_PUNKT

		if (pCT)
		{
		ResString resText (ResID (IDS_ENTARTUNGBER11, pRF), 80);

			if (OT_FLAECHE == m_OTAlt &&					// von einem Flächenobjekte
				m_iKCntAlt > ((EFlaeche&)_GO).KantenAnz())	// wurde eine Innenkontur gelöscht
				resText = ResString (ResID (IDS_ENTARTUNGBER21, pRF), 80);

		double XOut, YOut;	// Real-Koordinaten des ersten Stützpunktes

			// Konvertierung der Datenbank- in Real-Koordinaten
			DBKoordInReal (_EPkt, XOut, YOut, pCT);

			Format (sBuffer, (char*)resText.Addr(), DtoL(XOut), DtoL(YOut), sTypAlt.c_str(),
					sTypNeu.c_str());
		}
		else
		{
		ResString resText (ResID (IDS_ENTARTUNGBER12, pRF), 80);

			if (OT_FLAECHE == m_OTAlt &&					// von einem Flächenobjekte
				m_iKCntAlt > ((EFlaeche&)_GO).KantenAnz())	// wurde eine Innenkontur gelöscht
				resText = ResString (ResID (IDS_ENTARTUNGBER22, pRF), 80);

			Format (sBuffer, (char*)resText.Addr(), sTypAlt.c_str(), sTypNeu.c_str());
		}

		sAnalyseText += sBuffer;
	}

	else
	{
		if (m_OTAlt == OT_FLAECHE &&	// Fläche hat überhaupt keine Konturen mehr
			((EFlaeche&)_GO).KantenAnz() == 0)
		{
			_EPkt.X() = 0;				//  dann erster Punkt = Nullpunkt
			_EPkt.Y() = 0;
		}

	ResString resText1 (ResID (IDS_ENTARTUNG1, pRF), 30);

		if (pCT)
		{
		double XOut, YOut;	// Real-Koordinaten des ersten Stützpunktes

			// Konvertierung der Datenbank- in Real-Koordinaten
			DBKoordInReal (_EPkt, XOut, YOut, pCT);

			if (OT_KANTE == _GO.isA())
				Format (sBuffer, "%s (%ld,%ld)", (char*)resText1.Addr(), DtoL(XOut),
						DtoL(YOut));

			else				// Fläche
			{
				_ASSERTE (_GO.isA() == OT_FLAECHE);

			long lRest = ((EFlaeche&)_GO).KA(_iKaNr).ASP();	// Stützpunktanzahl der Kontur

				if (_iKaNr == 0)	// Außenkontur
				{
				ResString resText2 (ResID (IDS_ENTARTUNG2, pRF), 80);

					Format (sBuffer, (char*)resText2.Addr(), lRest, DtoL(XOut), DtoL(YOut));
				}
				else				// Innenkontur
				{
				ResString resText3 (ResID (IDS_ENTARTUNG3, pRF), 80);

					Format (sBuffer, (char*)resText3.Addr(), lRest, DtoL(XOut), DtoL(YOut));
				}
			}

			sAnalyseText += sBuffer;
		}
		else
			sAnalyseText += resText1.Addr();
	}

	sAnalyseText += "\r\n";

} // AnalysePuffern


// --------------------------------------------------------------------------------------------
// Bereinigung bei Entartungs-Fehlern erfolgt bei Kanten und Flächen ohne Inseln durch
// Typ-Umwandlung und bei Innenkonturen durch Löschen, wenn in den projektbezogenen Einträgen
// des DB-Headers das Bit 4 des Schlüssels "GeoRein" auf 1 gesetzt ist;
// fehlt der Schlüssel "GeoRein", wird der gleiche Test in der Registrier-Datenbank
// durchgeführt;
// fehlt dort der Schlüssel auch bzw. ist Bit 4 = 1, werden Entartungs-Fehler bereinigt, sonst
// nicht
void Entartung :: ErrorCorrection (void)
{
// mit Schlüssel "GeoRein" in den projektbezogenen Einträgen des DB-Headers testen, ob eine
// Entartung bereinigt werden soll (Bit 4 = 1) oder nicht (Bit 4 = 0)
ResString ErrClean (ResID (IDS_ERRCLEAN, pRF), 30);	
HeaderEntryX HE (ErrClean);
DWORD dwWert;	// Wert des Schlüssels "GeoRein"

	if (HE.Status() != HE_INVALID)	// Schlüssels "GeoRein" existiert im DB-Header
	{
	string sInPuffer;	// Konvertierungspuffer für Wert des Schlüssels "GeoRein"

		sInPuffer = HE.EntryText();
		dwWert = atol (sInPuffer.c_str());
	}

	else
	{
		// falls in den projektbezogenen Einträgen Schlüssel "GeoRein" nicht existiert, dann
		// den gleichen Test in der Registry
		dwWert = 0x00;	// default-Wert für den Fall, daß Schlüssel "GeoRein" gar nicht existiert

	CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathRein);

		cuExtConfig.GetDWORD (ErrClean.Addr(), dwWert);
	}

	_isCorrected = false;
	m_OTNeu = _GO.isA();

	if ((dwWert & 0x10) == 0x00)
		return;		// es ist keine Korrektur gewünscht

	if (OT_KANTE != m_OTAlt && OT_FLAECHE != m_OTAlt)
		return;		// es wird keine Korrektur vorgenommen

	if (m_OTAlt == OT_KANTE)	// Linienobjekt
	{
		m_OTNeu = OT_PUNKT;		// Kante wird in Punktobjekt umgewandelt
		_isCorrected = true;
	}
	else						// Flächenobjekt
	{
	EFlaeche* pFl = (EFlaeche*)&_GO;

		if (1 == pFl->KantenAnz())	// Fläche ohne Innenkonturen
		{
			if (pFl->ASP() > 1)
				m_OTNeu = OT_KANTE;	// Außenkontur der Fläche wird in Linienobjekt umgewandelt
			else
				m_OTNeu = OT_PUNKT;	// Außenkontur der Fläche wird in Punktobjekt umgewandelt
			_isCorrected = true;
		}
		else						// Fläche mit Innenkonturen
		{
			if (_iKaNr > 0 &&				// Entartung einer Innenkontur
				pFl->KA(_iKaNr).ASP() <= 2)	// mit höchstens 2 Punkten
			{
				pFl->SubKante (1, _iKaNr);	// diese Innenkontur ersatzlos löschen
				_isCorrected = true;
			}
		}
	}

} // ErrorCorrection

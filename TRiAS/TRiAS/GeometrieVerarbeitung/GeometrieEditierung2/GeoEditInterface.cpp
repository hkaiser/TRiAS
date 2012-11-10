// Definitionen: Interface für die Erweiterung "Geometrie-Editierung"
// File: GeoEditInterface.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "GeometrR.h"	// IDS_WINKELKORR, ...

#include "GeoEdit.h"



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// alle Objekt der vorgegebenen Objektklasse einsammeln, die schon rechtwinklig gemacht
// wurden
BOOL _GEOEDIT_EXPORT FAR PASCAL GetRectObjects (long lONr, DWORD, void* pvDat)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

HRESULT hr = ((CGeoEditExtension*)g_pTE)->RectangularObject (lONr);

	if (E_FAIL == hr)	// Merkmal "MaxWinkelKorrektur" existiert überhaupt nicht
		return false;

	if (S_OK == hr)		// Merkmal existiert und ist belegt, d.h. Objekt wurde schon
		((IEnum<LONG>*)pvDat)->AddItem (lONr);	// rechtwinklig gemacht
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Ermittlung des Startindex lStartInd entsprechend dem vorgegebenen RefLine-Modus
HRESULT CGeoEditExtension::GetStartIndex (long lONr, RefLine rfLine, IEnumLONG* pEnumIn,
										  long& lStartInd)
{
WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

	try
	{
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

		THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

		wObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

KoOrd* plXK; KoOrd* plYK;
long* plCnt;	// Anzahl der Stützpunkte in den Konturen

	wObj->GetX ((void**)&plXK);
	wObj->GetY ((void**)&plYK);
	wObj->GetLPCnt (&plCnt);

	switch (rfLine)
	{
		case EDIT_RECTANGULAR:	// gemeinsame Strecke zu Objekten der lONr-Objektklasse, die
								// schon rechtwinklig gemacht wurden
			if (S_OK != CommonLineWithRectObject (lONr, plXK, plYK, plCnt[0], lStartInd))
				LongestLine (plXK, plYK, plCnt[0], lStartInd);
			break;

		case EDIT_COMMON:		// gemeinsame Strecke zu Objekten vorgebbarer Objektklassen
			if (pEnumIn &&		// besagte Objektklassen sind tatsächlich vorgegeben
				S_OK == CommonLine (lONr, plXK, plYK, plCnt[0], pEnumIn, lStartInd))
				break;

		case EDIT_LONGEST:		// die längste Strecke
			LongestLine (plXK, plYK, plCnt[0], lStartInd);
			break;

		case EDIT_SOUTHERN:		// die südlichste Strecke
			SouthernmostLine (plXK, plYK, plCnt[0], lStartInd);
			break;
	}

	return S_OK;

} // GetStartIndex


// --------------------------------------------------------------------------------------------
// Ermittlung des Startindex lStartInd aus einer (evtl.) gemeinsamen Strecke mit einem schon
// rechtwinklig gemachten Objekt, das aus zur gleichen Objektklasse wie das lONr-Objekt gehört;
// gibt es kein solches Objekt, dann ist der return-Wert "S_FALSE", lStartInd ist in
// diesem Fall unbestimmt
HRESULT CGeoEditExtension::CommonLineWithRectObject (long lONr, KoOrd* plXK, KoOrd* plYK,
													 long lCnt0, long& lStartInd)
{
KoOrd x0, y0, x1, y1;	// Anfangs- und Endkoordinaten des längsten Konturabschnitts

	try	{
	// Objektnummern aller Objekte der Objektklasse des lONr-Objektes bereitstellen
	WEnumLONG wEnumIn (CLSID_EnumObjectsByNumber);	// throws_com_error
	ENUMLONGKEY ELK;

		ELK.eKey = DEX_GetObjIdentEx (lONr);
		ELK.eFcn = (ENUMLONGKEYPROC) GetRectObjects;
		ELK.ePtr = wEnumIn;
		DEX_EnumIdentObjects (ELK);

		if (0 == wEnumIn->Count())	// kein Objekt gefunden, das schon rechtwinklig gemacht
			return S_FALSE;			// wurde

	ulong ulIdent = 0;				// Identifikator für die Ergebnisobjekte (wird hier nicht
									// weiter benötigt)
	DWORD dwLageAusw = LAUSS;			// nur die wEnumIn-Flächen für Vergleich heranziehen, die
									// außerhalb der lONr-Fläche liegen
	SpForm sfSForm = SFORM_TEMP;	// temporäre Abspeicherung 
	WEnumLONG wComCont (CLSID_EnumObjectsByNumber);	// Objektnummern der gemeinsamen
													// Konturabschnitte

		if (! m_wObjOper.IsValid())	// (wenn noch nicht, dann) IExtendObjOper-Interface für
		{							//  CommonContour_ONr() zuschalten
		WUnknown wObjOper;

			ObjOperInterface (wObjOper.ppi());
			m_wObjOper = wObjOper;
		}

		if (m_wObjOper.IsValid())
			m_wObjOper->CommonContour_ONr (lONr, ulIdent, wEnumIn, dwLageAusw, sfSForm,
										   wComCont.ppi());
		else
			_ASSERTE (false);

		if (0 == wComCont->Count())	// keines der schon rechtwinklig gemachten Objekte hat
			return S_FALSE;			// einen gemeinsamen Konturabschnitt mit dem lONr-Objekt

		// wenn es mindestens 1 gemeinsamen Konturabschnitt gibt, dann die längste Strecke
		// bestimmen
		THROW_FAILED_HRESULT (GiveLongestLine (wComCont, x0, y0, x1, y1));
		VisualCommonContour (wComCont);
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return StartIndex (plXK, plYK, lCnt0, x0, y0, x1, y1, lStartInd);

} // CommonLineWithRectObject


// --------------------------------------------------------------------------------------------
// Ermittlung des Startindex lStartInd aus einer (evtl.) gemeinsamen Strecke mit einem
// pEnumIn-Objekt; gibt es kein solches Objekt, dann ist der return-Wert "S_FALSE", lStartInd
// ist in diesem Fall unbestimmt
HRESULT CGeoEditExtension::CommonLine (long lONr, KoOrd* plXK, KoOrd* plYK, long lCnt0,
									   IEnumLONG* pEnumIn, long& lStartInd)
{
	if (NULL == pEnumIn) return S_FALSE;

KoOrd x0, y0, x1, y1;	// Anfangs- und Endkoordinaten des längsten Konturabschnitts

	try
	{
	ulong ulIdent = 0;				// Identifikator für die Ergebnisobjekte (wird hier nicht
									// weiter benötigt)
	DWORD dwLageAusw = LINAU;		// nur die pEnumIn-Flächen für Vergleich heranziehen, die
									// sowohl innerhalb als auch außerhalb der lONr-Fläche
									// liegen
	SpForm sfSForm = SFORM_TEMP;	// temporäre Abspeicherung 
	WEnumLONG wComCont (CLSID_EnumObjectsByNumber);	// Objektnummern der gemeinsamen
													// Konturabschnitte

		if (! m_wObjOper.IsValid())	// (wenn noch nicht, dann) IExtendObjOper-Interface für
		{							//  CommonContour_ONr() zuschalten
		WUnknown wObjOper;

			ObjOperInterface (wObjOper.ppi());
			m_wObjOper = wObjOper;
		}

		if (m_wObjOper.IsValid())
			m_wObjOper->CommonContour_ONr (lONr, ulIdent, pEnumIn, dwLageAusw, sfSForm,
										   wComCont.ppi());
		else
			_ASSERTE (false);

		if (0 == wComCont->Count())	// keines der pEnumIn-Objekt hat einen gemeinsamen
			return S_FALSE;			// Konturabschnitt mit dem lONr-Objekt

		// wenn es mindestens 1 gemeinsamen Konturabschnitt gibt, dann die längste Strecke
		// bestimmen
		THROW_FAILED_HRESULT (GiveLongestLine (wComCont, x0, y0, x1, y1));
		VisualCommonContour (wComCont);
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return StartIndex (plXK, plYK, lCnt0, x0, y0, x1, y1, lStartInd);

}  // CommonLine


// --------------------------------------------------------------------------------------------
// Ermittlung des Startindex lStartInd aus der längsten Strecke der Außenkontur
void CGeoEditExtension::LongestLine (KoOrd* plXK, KoOrd* plYK, long lCnt0, long& lStartInd)
{
	lStartInd = -1;			// für den undenkbaren Fehlerfall

double dMaxStrecke = -1;	// Startwert für Länge der längsten Strecke

	for (long j = 0; j < lCnt0-1; j++)
	{
	double dLaenge = AbstandPktPktE (plXK[j], plYK[j], plXK[j+1], plYK[j+1]);

		if (dLaenge > dMaxStrecke)
		{
			dMaxStrecke = dLaenge;
			lStartInd = j;
		}
	}

	_ASSERTE (lStartInd >= 0);

} // LongestLine


// --------------------------------------------------------------------------------------------
// Ermittlung des Startindex lStartInd aus der "südlichsten" Strecke;
// diese wird folgendermaßen definiert:
// Suche nach den Stützpunkten mit dem kleinsten Hochwert; unter den jeweils beidseitig
// abgehenden Strecken wird diejenige mit der kleinsten (absoluten) Steigung gesucht und wenn
// es davon mehrere gleiche geben sollte, die mit der größten Länge
void CGeoEditExtension::SouthernmostLine (KoOrd* plXK, KoOrd* plYK, long lCnt0,
										  long& lStartInd)
{
	lStartInd = -1;				// für den undenkbaren Fehlerfall

KoOrd lMinHW = MAXKOORD;		// Startwert für den kleinsten Hochwert
double dMinAnstieg = DBL_MAX;	// Startwert für den kleinsten (absoluten) Anstieg
double dMaxStrecke = -1;		// Startwert für Länge der längsten Strecke
double dAnst0, dAnst1;			// Anstiege der beiden Strecken die "links" bzw. "rechts" vom
								// j-ten Stützpunkt abgehen
long jv;						// jv = "j - 1"

	for (long j = 0; j < lCnt0-1; j++)
	{
		if (plYK[j] > lMinHW) continue;		// es gibt südlichere Stützpunkte

		(j > 0) ? (jv = j - 1) : (jv = lCnt0 - 2);
		if (plXK[j] != plXK[jv])
			dAnst0 = fabs ((double)(plYK[j] - plYK[jv]) / (plXK[j] - plXK[jv]));
		else
			dAnst0 = DBL_MAX;

		if (plXK[j+1] != plXK[j])
			dAnst1 = fabs ((double)(plYK[j+1] - plYK[j]) / (plXK[j+1] - plXK[j]));
		else
			dAnst1 = DBL_MAX;

		if (plYK[j] < lMinHW)
		{
			lMinHW = plYK[j];
			dMinAnstieg = dAnst0;
			dMaxStrecke = AbstandPktPktE (plXK[jv], plYK[jv], plXK[j], plYK[j]);
			lStartInd = jv;
		}
		else		// gleicher kleinster Hochwert
		{
			if (dAnst0 < dMinAnstieg)
			{
				dMinAnstieg = dAnst0;
				dMaxStrecke = AbstandPktPktE (plXK[jv], plYK[jv], plXK[j], plYK[j]);
				lStartInd = jv;
			}
			else
			{
				if (dAnst0 == dMinAnstieg)	// gleicher kleinster Anstieg
				{
				double dLaenge = AbstandPktPktE (plXK[jv], plYK[jv], plXK[j], plYK[j]);

					if (dLaenge > dMaxStrecke)
					{
						dMaxStrecke = dLaenge;
						lStartInd = jv;
					}
				}
			}
		}

		if (dAnst1 < dMinAnstieg)
		{
			dMinAnstieg = dAnst1;
			dMaxStrecke = AbstandPktPktE (plXK[j], plYK[j], plXK[j+1], plYK[j+1]);
			lStartInd = j;
		}
		else
		{
			if (dAnst1 == dMinAnstieg)		// gleicher kleinster Anstieg
			{
			double dLaenge = AbstandPktPktE (plXK[j], plYK[j], plXK[j+1], plYK[j+1]);

				if (dLaenge > dMaxStrecke)
				{
					dMaxStrecke = dLaenge;
					lStartInd = j;
				}
			}
		}
	}

	_ASSERTE (lStartInd >= 0);

} // SouthernmostLine


// --------------------------------------------------------------------------------------------
// die längste gemeinsame pComCont-Konturstrecke feststellen und Anfangs- sowie Endpunkt
// (x0,y0) bzw. (x1,y1) zurückgeben
HRESULT CGeoEditExtension::GiveLongestLine (IEnumLONG* pComCont, KoOrd& x0, KoOrd& y0,
											KoOrd& x1, KoOrd& y1)
{
	_ASSERTE (pComCont != NULL);

WObjektGeometrie wObj;		// ObjektGeometrie und
long lONr, lCnt;			// Parameter des lONr-Objektes
KoOrd* plXK; KoOrd* plYK;
long lMaxLength = -1;		// Startwert für maximale Länge

	try
	{
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

		for (pComCont->Reset(); S_OK == pComCont->Next (1, &lONr, NULL); )
		{
			_ASSERTE (lONr != 0);
			_ASSERTE (lONr != -1);

			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

			wObj = wIObj;
			wObj->GetCnt (&lCnt);
			wObj->GetX ((void**)&plXK);
			wObj->GetY ((void**)&plYK);

			for (long j = 0; j < lCnt-1; j++)
			{
			long lLength = DtoL (AbstandPktPktE (plXK[j], plYK[j], plXK[j+1], plYK[j+1]));

				if (lLength > lMaxLength)
				{
					lMaxLength = lLength;
					x0 = plXK[j];
					y0 = plYK[j];
					x1 = plXK[j+1];
					y1 = plYK[j+1];
				}
			} // for
		} // for
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;

} // GiveLongestLine


// --------------------------------------------------------------------------------------------
// Visualisierung der temporär erzeugten gemeinsamen Konturabschnitte
HRESULT CGeoEditExtension::VisualCommonContour (IEnumLONG* pComCont)
{
	_ASSERTE (pComCont != NULL);

	pComCont->Reset();

long lONr = 0;	// Objektnummer des 1. gemeinsamen Konturabschnitts
HRESULT hr = pComCont->Next (1, &lONr, NULL);

//	if (FAILED (hr)) return hr;
	if (S_OK != hr) return hr;		// 05.03.99

HANDLEVISINFO HVI;
LVISINFO LVIC;		// für gemeinsamen Konturabschnitt

	INITSTRUCT (HVI, HANDLEVISINFO);
	memset (&LVIC, '\0', sizeof (LVISINFO));
	HVI.m_lIdent = DEX_GetObjIdentEx (lONr);	// Identifikator und
	HVI.m_iVTyp = VTLinie;					// VisInfoTyp eines gemeinsamen Konturabschnitts
	HVI.m_pVI = &LVIC.m_VI;					// generischer Pointer auf VisInfo

	LVIC.m_Width = 0;				// Linienbreite
	LVIC.m_VI.m_Priority = 0;		// Zeichenpriorität
	LVIC.m_VI.m_C = RGB (0, 0, 0);	// Primärfarbe "schwarz"

	DEX_ModIdentVisInfo (HVI);

	return S_OK;

} // VisualCommonContour


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "Objektoperationen" herstellen
HRESULT CGeoEditExtension::ObjOperInterface (IUnknown** ppIObjOper)
{
HRESULT hr = S_OK;
WExtendObjOper wObjOper;	// Interface für Ankopplung von ObjOper.ext

	if (m_pXtnSite)
	{
		hr = m_pXtnSite->GetXtension (CLSID_GeometrieOperationen, IID_IExtendObjOper,
									  (LPVOID*)wObjOper.ppi());

		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
		*ppIObjOper = wObjOper.detach();
	}
	else hr = E_UNEXPECTED;

	if (FAILED (hr) ||	// Fehler, z.B. ObjOper.ext nicht verfügbar
		! m_pXtnSite)
	{
	ResString resText (ResID (IDS_NOOBJOPER, pRF), 250);
	ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
		
		MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return hr;
	}

	return hr;

} // ObjOperInterface   


// --------------------------------------------------------------------------------------------
// Testen, ob das Merkmal "MaxWinkelKorrektur" überhaupt existiert und wenn ja, ob es für das
// lONr-Objekt einen Eintrag besitzt;
// return-Werte sind:
//	S_OK			Merkmal "MaxWinkelKorrektur" existiert und hat einen Eintrag
//	S_FALSE			Merkmal "MaxWinkelKorrektur" existiert aber ist leer
//	E_FAIL			Merkmal "MaxWinkelKorrektur" existiert nicht
//	E_OUTOFMEMORY	nicht genügend dynamischer Speicher beim Lesen des Merkmals
HRESULT CGeoEditExtension::RectangularObject (long lONr)
{
// MerkmalsCode für Merkmal "MaxWinkelKorrektur" aus DBHeader holen
ulong ulMCode = GetHeaderMCode (false, IDS_WINKELKORR, IDS_WINKELKORRKT, IDS_WINKELKORRLT,
								DEX_GetObjIdent(lONr));

	if (0 == ulMCode || (ulong)-1 == ulMCode)
		return E_FAIL;			// Merkmal "MaxWinkelKorrektur" existiert überhaupt nicht

string sMText;	// Merkmalstext

	if (!ReadFeatureText (lONr, ulMCode, TT_Objekt, sMText))
		return E_OUTOFMEMORY;	// nicht genügend dynamischer Speicher

	if (sMText.length() > 0)	// Merkmal ist belegt, d.h. Objekt wurde schon rechtwinklig
		return S_OK;			//  gemacht

	return S_FALSE;				// Merkmal ist nicht belegt, d.h. Objekt wurde noch nicht
								// rechtwinklig gemacht
} // RectangularObject


// --------------------------------------------------------------------------------------------
// (x0,y0) und (x1,y1) sind die Koordinaten des Anfangs- und Endpunktes eines linienförmigen
// Objektes, das auf der Außenkontur des (plXK,plYK)-Objektes liegt; daraus lStartInd ermitteln
HRESULT CGeoEditExtension::StartIndex (KoOrd* plXK, KoOrd* plYK, long lCnt0, KoOrd x0,
									   KoOrd y0, KoOrd x1, KoOrd y1, long& lStartInd)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);

long j, jv, jn;		// jv = "j - 1"; jn = "j + 1"

	for (j = 0; j < lCnt0; j++)
		if (plXK[j] == x0 && plYK[j] == y0)
			break;

	if (j == lCnt0) return E_UNEXPECTED;	// (x0,y0) nicht auf (plXK,plYK)-Kontur

	(j < lCnt0 - 2) ? (jn = j + 1) : (jn = 0);
	if (plXK[jn] == x1 && plYK[jn] == y1)
		lStartInd = j;
	else
	{
		(j > 0) ? (jv = j - 1) : (jv = lCnt0 - 2);
		if (plXK[jv] == x1 && plYK[jv] == y1)
			lStartInd = jv;
		else return E_UNEXPECTED;	// (x1,y1) nicht auf (plXK,plYK)-Kontur
	}
	
	return S_OK;

} // StartIndex



///////////////////////////////////////////////////////////////////////////////////////////////
// IExtendGeoEdit-Methoden
// --------------------------------------------------------------------------------------------
// das lONr-Objekt rechtwinklig machen
//   [in] rfLine     Modus für Bestimmung der Bezugsstrecke
//   [in] dEps90     Epsilon für die Winkel nahe" 90° bzw. "nahe" 270°
//   [in] dEps180    Epsilon für die Winkel nahe" 180°
//   [in] dEpsCom    Epsilon für  die Stützpunktgleichheit mit den angrenzenden Objekten
//   [in] pEnumIn    ObjNummern der Objekte, die auf eine gemeinsame Strecke getestet werden
//                   sollen
//   [out] ppEnumOut ObjNummern der Objekte, die verändert wurden
STDMETHODIMP_ (HRESULT) CGeoEditExtension::MakeRectangular_ONr (long lONr, RefLine rfLine,
												 double dEps90, double dEps180, double dEpsCom,
												 IEnumLONG* pEnumIn, IEnumLONG** ppEnumOut)
{
long lStartInd;		// Startindex

	GetStartIndex (lONr, rfLine, pEnumIn, lStartInd);

	try
	{
		// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
		if (m_wEditOper.IsValid())
		{
			m_wEditOper->SetEditExtensionSite (NULL);
			m_wEditOper.Assign(NULL);
		}

	WEditOperation wEditOper (CLSID_ObjectModify);	// throws_com_error

		THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
		m_wEditOper = wEditOper;

	int iKInd = 0;	// Bezugsstrecke ist bei externem Aufruf immer Teil der Außenkontur

	WModifyOperation wModOper (CLSID_MakeRectangular);		// throws_com_error

	// die anschließende Befehlszeile ersetzt die 3 nachfolgend herauskommentierten Zeilen;
	// die aktuelle EditierOperation m_wEditOper (u.z. ObjectModify) wird durch QueryInterface
	// nach dem Interface-ID von IModifyClassSite gefragt, der in pISite bereitgestellt wird;
	// IModifyClassSite ist das Interface, das die CObjectModify-Klasse für die
	// ModifyOperation's (u.a. MakeRectangular) bereitstellt, d.h. das Interface, über das z.B.
	// MakeRectangular die CObjectModify-Klasse rufen kann
	WModifyClassSite pISite (m_wEditOper);

		// nächste Zeile ist für CreateInterfaceTO() notwendig
		THROW_FAILED_HRESULT (wModOper->SetModifyClassSite(this, pISite));
		THROW_FAILED_HRESULT (wModOper->Rectangularity (lONr, iKInd, lStartInd, dEps90,
							  dEps180, dEpsCom, (IEnumObjectsByNumber**)ppEnumOut));

		// ModifyOperation "Rechtwinkligkeit" wieder abmelden
		if (wModOper.IsValid())
		{
			wModOper->SetModifyClassSite (NULL, NULL);
			wModOper.Assign (NULL);
		}

		// EditOperation "ObjektModifizierung" wieder abmelden
		if (m_wEditOper.IsValid())
		{
			m_wEditOper->SetEditExtensionSite (NULL);
			m_wEditOper.Assign(NULL);
		}
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}
	
	return S_OK;

} // MakeRectangular_ONr

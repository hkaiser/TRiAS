// Interface-Funktionen für Erweiterungs-DLL "Objektoperationen mit GeoObjekten"
// File: ObjOperI.cxx
// W. Mörtl


#include "ObjOperP.hxx"

#include <resstrg.h>    // IDS_UIFORMAT

#include "ObjOperR.h"	// Ressourcekonstanten für diese Erweiterung (IDS_BOXTEXT3, ...)

#include "geotrias.hxx"	// EFlaecheErzeugen()
#include "strecke.hxx"	// Strecke

#include "ObjOper.hxx"	// Klasse für diese Erweiterung


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;

    

// --------------------------------------------------------------------------------------------
// lONr-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn übergeben werden; die
// Objektnummern der Ergebnis-Objekte werden in ppEnumOut zurückgegeben
HRESULT ObjektOpExtension::SchnittObjObjekte_ONr (HPROJECT hPr, long lONr,
									  IEnumLONG* pEnumTarget, ulong ulLageAusw, SpForm sfSForm,
									  bool bFortAnz, IEnumLONG** ppEnumNew)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	// schneidendes Objekt initialisieren
	_lONrAO = lONr;		// Objektnummer des schneidenden Objektes ermitteln
	if (!AktiviertesObjekt())
		return E_FAIL;

	// weitere Member initialisieren
	_ulLageAusw = ulLageAusw;	// Bitmuster für Auswahl bei Schnittoperationen
	_sfSForm = sfSForm;			// Speicherform

// Objektnummern der zu schneidenden Objekte aus pEnumTarget auslesen und in m_plOrigObjNr
// bereitstellen
HRESULT hrRet = GetObjNummern (pEnumTarget);

	if (S_OK != hrRet) return hrRet;

//bool bFortAnz = false;	// keine Fortschrittsanzeige

	if (OT_PUNKT != _iOT && 
		S_OK == SchnittAusfuehren (hPr, bFortAnz, ppEnumNew) && *ppEnumNew)
			return S_OK;

	if (OT_PUNKT == _iOT)
	{
	WObjektGeometrie wObj;

		try
		{
		WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (_lONrAO));
			wObj = wIObj;
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}

		if (S_OK == PointCutsLines (wObj, true, ppEnumNew) &&  *ppEnumNew)
			return S_OK;
	}

	return E_FAIL;

} // SchnittObjObjekte_ONr


// --------------------------------------------------------------------------------------------
// pIOG-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn übergeben werden;
// die Objektnummern der Ergebnis-Objekte werden in ppEnumOut zurückgegeben
HRESULT ObjektOpExtension::SchnittObjObjekte_Geom (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
						ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	_ASSERTE (pIOG != NULL);

	_sfSForm = sfSForm;		// Speicherform

// Objektnummern der zu schneidenden Objekte aus pEnumIn auslesen und in m_plOrigObjNr
// bereitstellen
HRESULT hrRet = GetObjNummern (pEnumIn);

	if (S_OK != hrRet) return hrRet;

// Vector für neu erzeugte Teilobjekte
	m_veNewObjs.clear();	// Vector erst einmal löschen

short iOT;

	pIOG->GetObjTyp (&iOT);

	switch (iOT)
	{
		case OT_PUNKT:		// "Messer" ist ein Punktobjekt 
			hrRet = PointCutsLines (pIOG, false, ppEnumOut);
			break;

		case OT_KANTE:		// "Messer" ist ein Linienobjekt 
			hrRet = E_NOTIMPL;
			break;

		case OT_FLAECHE:	// "Messer" ist ein Flächenobjekt 
			hrRet = E_NOTIMPL;
			break;

		default:
			_ASSERTE (iOT == OT_PUNKT || iOT == OT_KANTE || iOT == OT_FLAECHE);
			hrRet = E_UNEXPECTED;
	}


// Übergabe der neu gebildeten Teilobjekte an ppEnumOut
	try
	{
	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);
	long lNewObjs = m_veNewObjs.size();

		if (lNewObjs > 0)	// mindestens 1 Teilobjekt erzeugt
		{
			// Übertragen der Objektnummern der erzeugten Teilobjekte aus m_veNewObjs in wOutput
			for (long i = 0; i < lNewObjs; i++)
				((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_veNewObjs[i]);

			_bMenLoeNeu = true;	// Menüpunkt für Löschen der neuen Teilobjekte aktivieren
		}

		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		hrRet = _COM_ERROR (e);
	}

// wird noch beim Löschen der ursprünglichen Objekt in ObjekteLoeschen() benötigt (15.04.99)
//	DELETE_VEC (m_plOrigObjNr);	// wurde in GetObjNummern() angelegt

	return hrRet;

} // SchnittObjObjekte_Geom


// --------------------------------------------------------------------------------------------
// pIOG-Punkt schneidet die m_plOrigObjNr-Objekte und gibt die Ergebnisse in ppEnumOut zurück
HRESULT ObjektOpExtension::PointCutsLines (IObjektGeometrie* pIOG, bool bOrigPt,
										   IEnumLONG** ppEnumOut)
{
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

KoOrd lTX =	plXK[0];
KoOrd lTY =	plYK[0];

HRESULT hrRet = S_OK;
WObjektGeometrie wObj;

	try
	{
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

		for (long i = 0; i < _lAnzOrigObj; i++)
		{
			_ASSERTE (m_plOrigObjNr[i] != 0);
			_ASSERTE (m_plOrigObjNr[i] != -1);

			if (OT_KANTE != DEX_GetObjectType (m_plOrigObjNr[i]))
				continue;	// Punkt kann nur Kanten schneiden

			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (m_plOrigObjNr[i]));

			wObj = wIObj;

			hrRet = PointCutOneLine (lTX, lTY, bOrigPt, wObj, m_plOrigObjNr[i]);
		}

	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		for (long l = 0; l < _lAnzNeuObj; l++)
			((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_plNeuObjNr[l]);

		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		hrRet = _COM_ERROR (e);
	}	

	return hrRet;

} // PointCutsLines


// --------------------------------------------------------------------------------------------
// Punkt (lTX,lTY) zerlegt (evtl.) das pIOG-Linienobjekt (mit Objektnummer lONr)
// (lONr steckt zwar auch in pIOG drin, ist also hier ad libidum, ist aber bei Aufruf von
// PointCutOneLine() als separate Variable vorhanden und wird deshalb mit als Parameter
// übergeben)
// für bOrigPt == true wird der unveränderte Originalpunkt (lTX,lTY) genommen, für
// bOrigPt == false wird der nächste, auf dem pIOG-Linienobjekt liegende Punkt verwendet
HRESULT ObjektOpExtension::PointCutOneLine (KoOrd lTX, KoOrd lTY, bool bOrigPt,
											IObjektGeometrie* pIOG, long lONr)
{
HRESULT hrRet = S_OK;

long lCnt;		// Parameter des pIOG-Linienobjektes
KoOrd* plXK; KoOrd* plYK;
ulong ulIdent;

	pIOG->GetCnt (&lCnt);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetIdent (&ulIdent);

// den Punkt TPkt ermitteln, der sich ergibt, wenn Punkt (lTX,lTY) auf das pIOG-Linienobjekt
// gezogen wird
long lPInd = -1;		// Index des pIOG-Stützpunktes, dem TPkt am nächsten liegt
long lSInd = -1;		// Index der pIOG-Strecke, dem TPkt am nächsten liegt
EPunkt TPkt = NearestPointToObject (EPunkt(lTX,lTY), pIOG, 0, lCnt-1, false, &lPInd, &lSInd);

	if (0 == lPInd || lPInd == lCnt-1)
	{
		_ASSERTE (0 != lPInd);			// Routine dürfte eigentlich
		_ASSERTE (lCnt-1 != lPInd);	// gar nicht hierher kommen

	ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

		MessageBox (__hWndM, "Das Linienobjekt kann an dieser Stelle nicht geteilt werden.",
		resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return S_FALSE;
	}

	if (bOrigPt && (TPkt.X() != lTX || TPkt.Y() != lTY))
		return S_FALSE;		// der Punkt (lTX,lTY) liegt nicht auf dem pIOG-Linienobjekt


// lONr-Linienobjekt kann geteilt werden
GeoKante* pTKt = 0;	// eine neu erzeugte Teillinie

	if (-1 != lPInd)	// Teilung an einem schon vorhandenen Stützpunkt
	{
		if (lPInd >= 0 && lPInd < lCnt)
		{
			pTKt = new GeoKante (lONr, ulIdent, plXK, plYK, lPInd+1);
			if (! pTKt)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}

			pTKt->AddClipObjekt (_CL1);
			DELETE_OBJ (pTKt);

			pTKt = new GeoKante (lONr, ulIdent);
			if (! pTKt)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}

			pTKt->AddPunkt (plXK, plYK, lCnt, lPInd, lCnt-1, -1);
			pTKt->AddClipObjekt (_CL1);
			DELETE_OBJ (pTKt);
		}
		else
		{
			_ASSERTE (lPInd >= 0 && lPInd < lCnt);

			hrRet = E_UNEXPECTED;
		}
	}

	else if (-1 != lSInd)	// Teilung innerhalb einer Strecke
	{
		if (lSInd >= 0 && lSInd < lCnt-1)
		{
			pTKt = new GeoKante (lONr, ulIdent, plXK, plYK, lSInd+1);
			if (! pTKt)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}

			pTKt->AddPunkt (&TPkt.X(), &TPkt.Y(), 1, -1);
			pTKt->AddClipObjekt (_CL1);
			DELETE_OBJ (pTKt);

			pTKt = new GeoKante (lONr, ulIdent);
			if (! pTKt)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}

			pTKt->AddPunkt (&TPkt.X(), &TPkt.Y(), 1, -1);
			pTKt->AddPunkt (plXK, plYK, lCnt, lSInd+1, lCnt-1, -1);
			pTKt->AddClipObjekt (_CL1);
			DELETE_OBJ (pTKt);
		}
		else
		{
			_ASSERTE (lSInd >= 0 && lSInd < lCnt-1);

			hrRet = E_UNEXPECTED;
		}
	}
	else
	{
		_ASSERTE (lPInd != -1 || lSInd != -1);

		hrRet = E_UNEXPECTED;
	}

	ObjNrSpeichern (lONr);		// Objektnummer des Originalobjektes retten

	// Teilobjekte aus _CL1 in TRiAS abspeichern und m_veNewObjs füllen
	RETURN_FAILED_HRESULT (NewObjectsToTRiAS (_CL1));

OBJECTSPLITTED OS;	// Struktur für die Mitteilung der Objektnummern ...

	INITSTRUCT (OS, OBJECTSPLITTED);
	OS.m_lONrOrig = lONr;									// ... des Ursprungsobjektes
	OS.m_lONrNew1 = m_veNewObjs.at(m_veNewObjs.size()-2);	// und des 1. bzw.
	OS.m_lONrNew2 = m_veNewObjs.at(m_veNewObjs.size()-1);	// des 2. neuen Objektes
	DEXN_ObjectSplitted (OS);			// Mitteilung, daß neue Objekte erzeugt wurden

	return hrRet;

} // PointCutOneLine


// --------------------------------------------------------------------------------------------
// pIOG-Kante schneidet das lONr-Objekt;
// die Objektnummern der Ergebnis-Objekte werden in ppEnumOut zurückgegeben
HRESULT ObjektOpExtension::SchnittKanteObj_Geom (HPROJECT hPr, IObjektGeometrie* pIOG,
											   long lONr, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	_ASSERTE (pIOG != NULL);

//OBJECTSPLITTED OS;	// Struktur für die Mitteilung der Objektnummern (31.12.98)

//	INITSTRUCT (OS, OBJECTSPLITTED);	// Ursprungsobjektes (sowie später - im Erfolgsfall -
//	OS.m_lONrOrig = lONr;				//  der beiden neuen Objekte)

// schneidende Kante initialisieren
long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	DELETE_OBJ (_pBO);		// vorsichtshalber löschen
	_pBO = new EKante (plXK, plYK, lSPAnz);
	if (! _pBO)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}
	_iOT = OT_KANTE;
	_lONrAO = 0;		// definiert setzen, weil damit getestet wird
	_lSPA = lSPAnz;		// Gesamtstützpunktanzahl der schneidenden Kante

	// weitere Member initialisieren
	_sfSForm = SFORM_PERM;	// Speicherform: permanent
	_lAnzOrigObj = 1;		// Anzahl der Objekte, die geschnitten werden sollen

	DELETE_VEC (m_plOrigObjNr);	// Feld für Objektnummer des zu schneidenden Objektes
	m_plOrigObjNr = new long [_lAnzOrigObj];
	if (! m_plOrigObjNr)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}
	m_plOrigObjNr [0] = lONr;
	m_lOrigInd = 0;				// Laufindex von m_plOrigObjNr

	if (S_OK == SchnittAusfuehren (hPr, bFortAnz, ppEnumOut) && *ppEnumOut)
		return S_OK;
	return E_FAIL;

} // SchnittKanteObj_Geom


// --------------------------------------------------------------------------------------------
// Hilfsroutine für SchnittObjObjekte_ONr() und SchnittKanteObj_Geom()
HRESULT ObjektOpExtension::SchnittAusfuehren (HPROJECT hPr, bool bFortAnz,
											  IEnumLONG** ppEnumOut)
{
	*ppEnumOut = NULL;	// Fehlerfall

	m_pW = MWind();		// MWind() liefert pWindow-Zeiger auf HauptFenster

	// Fenster für prozentuale Anzeige und Abbruch
	if (bFortAnz)
	{
		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error

			THROW_FAILED_HRESULT (InitProgressIndicator (PI, ResID (IDS_SCHNITT_CAPTION, pRF),
										   ResID (IDS_STATUS_STAND, pRF), _lAnzOrigObj*_lSPA));
			THROW_FAILED_HRESULT (RegisterPI (PI));
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}
	}

HRESULT hrRet = S_OK;	// return-Wert dieser Routine

	// Teilobjekte erzeugen
	for (int i = 0; i < _lAnzOrigObj; i++)
		if (_lONrAO != m_plOrigObjNr[i] &&	// kein Schnitt mit sich selbst (20.05.99)
			!ObjektSchneiden (m_plOrigObjNr[i]))
			hrRet = E_FAIL;

	try
	{
		THROW_FAILED_HRESULT (UnRegisterPI());

	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		_ASSERTE (wOutput.IsValid());

		// Member dieser Erweiterung für Abspeicherung in TRiAS definiert setzen
		_lAnzNeuObj = _CL1.Count();		// Anzahl der Teilobjekte in ClipListe _CL1

		if (_lAnzNeuObj > 0)	// mindestens 1 Teilfäche erzeugt
		{
			DELETE_VEC (m_plNeuObjNr);	// Feld der Objektnummern der neuen Teilobjekte löschen
			m_plNeuObjNr = new long [_lAnzNeuObj]; // Feld für diese neuen Objektnummern anlegen
			if (! m_plNeuObjNr)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}
			m_lNeuInd = 0;		// Laufindex für m_plNeuObjNr

			// Teilobjekte aus _CL1 in TRiAS abspeichern und m_plNeuObjNr füllen
			if (!ClipListeAnTRIAS (hPr, _CL1))
				hrRet = E_FAIL;		// 19.06.98

			// wenn in ClipListeAnTRIAS() Objekte nicht an TRiAS übergeben werden können, wird
			// _lAnzNeuObj entsprechend reduziert; deshalb die nachfolgende Abfrage noch einmal
			if (_lAnzNeuObj > 0)
			{
				// Übertragen der Objektnummern der erzeugten Teilobjekte aus m_plNeuObjNr in wOutput
				for (long i = 0; i < _lAnzNeuObj; i++)
					((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_plNeuObjNr[i]);

				_bMenLoeNeu = true;     // Menüpunkt für Löschen der neuen Teilobjekte aktivieren

			OBJECTSPLITTED OS;	// Struktur für die Mitteilung der Objektnummern ...

				INITSTRUCT (OS, OBJECTSPLITTED);		// ... des Ursprungsobjektes
				OS.m_lONrOrig = m_plOrigObjNr[0];
				OS.m_lONrNew1 = m_plNeuObjNr[0];		// sowie des 1. bzw.
				if (_lAnzNeuObj > 1)
					OS.m_lONrNew2 = m_plNeuObjNr[1];	//  des 2. neuen Objektes
				DEXN_ObjectSplitted (OS);			// Mitteilung, daß neue Objekte erzeugt wurden
			}
		}

		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

// Das Zeichnen erfolgt IMMER durch die ModifyPage (20.0.99).
//	if (_lAnzNeuObj > 0)
//		MakeNewObjectsVisible();	// Bereich, in dem die neuen Objekte liegen, zeichnen

	return hrRet;

} // SchnittAusfuehren


// --------------------------------------------------------------------------------------------
// Durchschnitt der Flächen, deren Objektnummern in pEnumIn übergeben werden; weitere Parameter
// sind
// - ulIdent:  Identifikator für die Ergebnisflächen
// - sfSForm:  Speicherform (permanent, temporär)
// - bFortAnz: Fortschrittsanzeige wird eingeblendet (true) bzw. ist nicht sichtbar (false)
// in ppEnumOut werden die Objektnummern der Ergebnisflächen zurückgegeben
HRESULT ObjektOpExtension::DurchschnittsFlaeche (HPROJECT hPr, IEnumLONG* pEnumIn,
												 ulong ulIdent, bool bCopyFeat, SpForm sfSForm,
												 bool bFortAnz, IEnumLONG** ppEnumOut)
{
long lSumme;	// Summe der Stützpunktanzahl der Außenkonturen

	if (GemeinsameRoutine1 (pEnumIn, sfSForm, bFortAnz, lSumme) == false)
		return E_FAIL;

	m_OpMode = DURCHSCHNITT;
	bCopyFeat ? (m_bCopyFeat = true) : (m_bCopyFeat = false);

	if (bFortAnz)	// mit Fortschrittsanzeige
	{
		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error

			THROW_FAILED_HRESULT (InitProgressIndicator (PI, ResID (IDS_DURCHSCHNITT_CAPTION, pRF),
														ResID(IDS_STATUS_STAND, pRF), lSumme));
			THROW_FAILED_HRESULT (RegisterPI (PI));
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}
	}

	
// schrittweise Flächendurchschnitt bilden
bool bOK = true;	// Durchschnitt wurde zu Ende geführt

	for (int i = 0; i < _lAnzOrigObj; i++)
	{
	int iOT = DEX_GetObjectType (m_plOrigObjNr[i]);

		_ASSERTE (iOT == OT_FLAECHE);

		if (iOT != OT_FLAECHE ||
			!EinzObjDurchschnitt (m_plOrigObjNr[i]))
		{
			 bOK = false;	// Abbruch der Durchschnittsbildung
			 break;
		}
	}

	if (FAILED(UnRegisterPI())) return false;

	
// in _CL1 wurden immer die letzten Ergebnisse der schrittweise durchgeführten
// Durchschnittsoperation abgelegt; enthält _CL1 höchstens einen Eintrag, wurde kein
// Durchschnitt durchgeführt und es wird false zurückgegeben, ansonsten sind alle Einträge zu
// löschen, der letzte natürlich erst, nachdem das Objekt an TRiAS übergeben wurde
CRing ri1 (_CL1);			// Navigator für ListContainer ClipListe _CL1
HRESULT hrRet = E_ABORT;	// Durchschnitt mußte abgebrochen werden bzw. wurde durch Anwender
							// abgebrochen

	if (bOK)     // Durchschnitt wurde vollständig mit allen Flächen durchgeführt
	{
		IdentModify (ulIdent);		// alle Objekte aus _CL1 mit ulIdent versehen
		hrRet = GemeinsameRoutine2 (hPr, ppEnumOut);	// alle Objekte aus _CL1 an TRiAS
	}

	_CL1.EveryDelete();		// ClipListe löschen

	if (FAILED (hrRet))		// Durchschnitt war nicht vollständig möglich
	{
		_bMenLoeOrig = false;

	// anstelle des Fehlercodes "WC_MESSAGE_OPER" wird die Routine ErrHandler() gerufen
	// (siehe DEX_ErrInstall())
		ResString resText (ResID (IDS_BOXTEXT3, pRF), 200);
	ErrCode rcDummy;

		DEX_SetError (rcDummy, 0, WC_MESSAGE_OPER, (void*)resText.Addr());
		return hrRet;
	}

	return S_OK;

} // DurchschnittsFlaeche


// --------------------------------------------------------------------------------------------
// Vereinigung der Flächen, deren Objektnummern in pEnumIn übergeben werden; weitere Parameter
// sind
// - ulIdent:  Identifikator für die Ergebnisflächen
// - sfSForm:  Speicherform (permanent, temporär)
// - bFortAnz: Fortschrittsanzeige wird eingeblendet (true) bzw. ist nicht sichtbar (false)
// in ppEnumOut werden die Objektnummern der Ergebnisflächen zurückgegeben
HRESULT ObjektOpExtension::VereinigungsFlaeche (IEnumLONG* pEnumIn, ulong ulIdent,
										  SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	_ASSERTE(NULL != pEnumIn && NULL != ppEnumOut);

	if (NULL == ppEnumOut) return E_POINTER;
	*ppEnumOut = NULL;
	if (NULL == pEnumIn || 0 == ulIdent) return E_INVALIDARG;

// bei mehr als 2 Objekten die modifizierte BlinkelRoutine arbeiten lassen
// (selbige ruft jedoch auch diese Routine hier, aber immer mit genau 2 Objekten)
	if (pEnumIn -> Count() > 2) {
	// KurzText besorgen
	HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
	string sOCName;
	WEnumLONG wOrigEnum;	// Originalobjekte, die zu den neuen Objekten beigetragen haben

		if (!GetKurzText (ulIdent, 'i', sOCName))
			sOCName = sUnionName;

		RETURN_FAILED_HRESULT (BeginAction (hPr, sOCName, NULL));
		RETURN_FAILED_HRESULT (DoAction (hPr, pEnumIn));
		RETURN_FAILED_HRESULT (EndAction (hPr, wOrigEnum.ppi(), ppEnumOut));
		return S_OK;
	}

// bei 2 Objekten alles beim Alten lassen (#HK000424)
	_ASSERTE (pEnumIn != NULL);	// ulIdent == 0 ist möglich

long lSumme;	// Summe der Stützpunktanzahl der Außenkonturen

	if (GemeinsameRoutine1 (pEnumIn, sfSForm, bFortAnz, lSumme) == false)
		return E_FAIL;

	m_OpMode = VEREINIGUNG;

	if (bFortAnz)	// mit Fortschrittsanzeige
	{
		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error

			THROW_FAILED_HRESULT (InitProgressIndicator (PI,
				  ResID (IDS_VEREINIGUNG_CAPTION, pRF), ResID(IDS_STATUS_STAND, pRF), lSumme));
			THROW_FAILED_HRESULT (RegisterPI (PI));
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}
	}

	_pVFl = NULL;	// Vereinigungsfläche

	// schrittweise Flächenvereinigung bilden
	for (int i = 0; i < _lAnzOrigObj; i++)
	{
		if (OT_FLAECHE != DEX_GetObjectType (m_plOrigObjNr[i]))
			continue;
		EinzFlaeVereinigen (m_plOrigObjNr[i]);
	}

	if (FAILED(UnRegisterPI())) return false;

HRESULT hrRet = S_OK;

	if (m_bUnion &&		// 28.10.98
		_pVFl)			// Vereinigung war möglich, d.h. Vereinigungsobjekt in _CL1 eintragen
	{
	CRing ri1 (_CL1);	// Navigator für ListContainer ClipListe _CL1

		_ASSERTE (0 != ulIdent);
		_ASSERTE ((ulong)-1 != ulIdent);

	GeoFlaeche* pGF = new GeoFlaeche (0, ulIdent, *_pVFl);
		
		if (! pGF)
		{
			DEX_Error (RC_objoperi, EC_NOMEMORY);
			DELETE_OBJ (_pVFl);
			return E_OUTOFMEMORY;
		}

		pGF->AddClipObjekt(_CL1);
		DELETE_OBJ (pGF);

	HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!

		hrRet = GemeinsameRoutine2 (hPr, ppEnumOut);
		ri1.First();
		ri1.Delete();
	}
	else	// 28.10.98
	{
		if (! m_bUnion) hrRet = E_FAIL;
		if (! _pVFl) hrRet = S_FALSE;
	}

	// DELETE auch für den Fall notwendig, daß keine Vereinigung möglich war, weil z.B. unter
	// den pEnumIn-Eingangsobjekten nur 1 Fläche enthalten war (16.12.98)
	DELETE_OBJ (_pVFl);
						
	return hrRet;
} // VereinigungsFlaeche


// --------------------------------------------------------------------------------------------
// gemeinsame Routine für DurchschnittsFlaeche() und VereinigungsFlaeche()
bool ObjektOpExtension::GemeinsameRoutine1 (IEnumLONG* pEnumIn, SpForm sfSForm, bool bFortAnz,
											long& lSumme)
{
	m_pW = MWind();		// MWind() liefert pWindow-Zeiger auf HauptFenster
	_sfSForm = sfSForm;	// Speicherform

// Objektnummern der Objekte, mit denen eine Objektoperation durchgeführt werden soll, aus
// pEnumIn auslesen
HRESULT hrRet = GetObjNummern (pEnumIn);

	if (hrRet != S_OK)
		return false;

	if (bFortAnz)	// mit Fortschrittsanzeige
	{
		// Startwert für prozentuale Anzeige aus Summe der Stützpunktanzahlen der Außenkontur
		// ermitteln, dabei kann die Stützpunktanzahl des 1. Objektes unberücksichtigt bleiben,
		// da es nicht separat behandelt wird, sondern gleich mit dem 2. Objekt verarbeitet wird
		lSumme = 0;	// Summe der Stützpunktanzahl der Außenkonturen

		for (long i = 1; i < _lAnzOrigObj; i++)
			lSumme += StuetzpunkteAussen (m_plOrigObjNr[i]);
	}
	return true;
} // GemeinsameRoutine1


// --------------------------------------------------------------------------------------------
// gemeinsame Routine für DurchschnittsFlaeche() und VereinigungsFlaeche()
HRESULT ObjektOpExtension::GemeinsameRoutine2 (HPROJECT hPr, IEnumLONG** ppEnumOut)
{
	try
	{
	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		_ASSERTE (wOutput.IsValid());

		// Member dieser Erweiterung für Abspeicherung in TRiAS definiert setzen
		_lAnzNeuObj = _CL1.Count();		// Anzahl der neuen Flächen in ClipListe _CL1

		if (_lAnzNeuObj > 0)	// mindestens 1 neue Fläche erzeugt
		{
			DELETE_VEC (m_plNeuObjNr);	// Feld der Objektnummern der neuen Flächen löschen
			m_plNeuObjNr = new long [_lAnzNeuObj];	// Feld für diese neuen Objektnummern anlegen
			if (! m_plNeuObjNr)
			{
				DEX_Error (RC_objoperi, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}
			m_lNeuInd = 0;   						// Laufindex für m_plNeuObjNr

			// Teilobjekte aus _CL1 in TRiAS abspeichern und m_plNeuObjNr füllen
			ClipListeAnTRIAS (hPr, _CL1);

			// Übertragen der Objektnummern der erzeugten Teilobjekte aus m_plNeuObjNr in wOutput
			for (int i = 0; i < _lAnzNeuObj; i++)
				((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_plNeuObjNr[i]);

			_bMenLoeNeu = true;     // Menüpunkt für Löschen der neuen Teilobjekte aktivieren
		}

		// Objektnummern der erzeugten Teilobjekte nach ppEnumOut weiterreichen
		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;

} // GemeinsameRoutine2


// --------------------------------------------------------------------------------------------
// Exklusiv-Oder der lONr-Fläche (Bezugsobjekt) mit allen Flächen, deren Objektnummern in
// pEnumIn übergeben werden
HRESULT ObjektOpExtension::ExklusivFlaeche_ONr (long lONr, IEnumLONG* pEnumIn,
										  SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	// Bezugsobjekt initialisieren
	_lONrAO = lONr;						// Objektnummer des Bezugsobjektes
	if (!AktiviertesObjekt())	// Bezugsobjekt erzeugen
		return E_FAIL;

	if (OT_FLAECHE != _iOT)		// Exklusiv-Oder nur mit einer Fläche möglich
		return E_INVALIDARG;

	// weitere Member initialisieren
	_sfSForm = sfSForm;		// Speicherform
	m_OpMode = SUBTRAKTION;

	// Bezugsfläche in Zwischenspeicher _CL2
	GeoFlaeche (_lONrAO, _ulIdent, *(EFlaeche*)_pBO).AddClipObjekt (_CL2);

// Objektnummern der Objekte für Exklusiv-Oder aus pEnumIn auslesen
HRESULT hrRet = GetObjNummern (pEnumIn, true);

	if (hrRet != S_OK)
		return hrRet;

	if (S_OK == ExklOderAusfuehren (bFortAnz, ppEnumOut) && *ppEnumOut)
		return S_OK;
	return E_FAIL;

} // ExklusivFlaeche_ONr


// --------------------------------------------------------------------------------------------
// Hilfsroutine für ExklusivFlaeche_ONr()
HRESULT ObjektOpExtension::ExklOderAusfuehren (bool bFortAnz, IEnumLONG** ppEnumOut)
{
	*ppEnumOut = NULL;	// Fehlerfall

	m_pW = MWind();		// MWind() liefert pWindow-Zeiger auf HauptFenster

	if (bFortAnz)	// Fenster für prozentuale Anzeige und Abbruch
	{
	// lStartW ist Startwert für prozentuale Anzeige; von _lAnzOrigObj wird 1 subtrahiert, da
	// in _lAnzOrigObj auch die aktivierte (blinkende) Fläche mitgezählt wurde
	long lStartW = (_lAnzOrigObj-1)*_lSPA + StuetzpunktAnzahl2();

		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error

			THROW_FAILED_HRESULT (InitProgressIndicator (PI,
				ResID (IDS_EXKLUSIVODER_CAPTION, pRF), ResID(IDS_STATUS_STAND, pRF), lStartW));
			THROW_FAILED_HRESULT (RegisterPI (PI));
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}
	}

HRESULT hrRet = S_OK;	// return-Wert dieser Routine

	// Exklusiv-Oder ausführen (_lAnzOrigObj-1, weil ein Platz für die Objektnummer des
	// Bezugsobjektes reserviert wurde)
	for (int i = 0; i < _lAnzOrigObj-1; i++)
		if (!ObjektExklOder (m_plOrigObjNr[i]))	// oder EinzObjExklOder
			hrRet = E_FAIL;

	// wenn aus der aktivierten (blinkenden) Fläche mindestens eine Ergebnisfläche gebildet
	// wurde, dann auch die Nummer der aktivierten Fläche abspeichern
	if (_CL2.Count() > 0)
		ObjNrSpeichern (_lONrAO);
		
HRESULT hr = UnRegisterPI();

	if (FAILED(hr)) return hr;

bool bRet1 = true, bRet2 = true;	// return-Werte von ClipListeAnTRIAS()
long lAnzCL1 = _CL1.Count();		// Anzahl der Objekte in ClipListe _CL1
long lAnzCL2 = _CL2.Count();		//  bzw. _CL2

	// Member dieser Erweiterung für Abspeicherung in TRiAS definiert setzen
	_lAnzNeuObj = lAnzCL1 + lAnzCL2;	// Gesamtanzahl der neuen Objekte

	if (_lAnzNeuObj > 0)	// mindestens 1 Objekt erzeugt
	{
		DELETE_VEC (m_plNeuObjNr);		// Feld der Objektnummern der neuen Objekte löschen
		m_plNeuObjNr = new long [_lAnzNeuObj];	// Feld für diese neuen Objektnummern anlegen
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoperi, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
		m_lNeuInd = 0;   						// Laufindex für m_plNeuObjNr

		// Objekte aus _CL1 bzw. _CL2 in TRiAS abspeichern und m_plNeuObjNr füllen
	HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!

		if (lAnzCL1 > 0)
			bRet1 = ClipListeAnTRIAS (hPr, _CL1);
		if (lAnzCL2 > 0)
			bRet2 = ClipListeAnTRIAS (hPr, _CL2);

		_bMenLoeNeu = true;     // Menüpunkt für Löschen der neuen Objekte aktivieren
	}

	try
	{
	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		_ASSERTE (wOutput.IsValid());

		// Übertragen der Objektnummern der erzeugten Objekte aus m_plNeuObjNr in wOutput
		for (i = 0; i < _lAnzNeuObj; i++)
			((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_plNeuObjNr[i]);

		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	MakeNewObjectsVisible();	// Bereich, in dem die neuen Objekte liegen, zeichnen

	if (SUCCEEDED(hrRet) && bRet1 && bRet2) return S_OK;
	return E_FAIL;

} // ExklOderAusfuehren


// --------------------------------------------------------------------------------------------
//
HRESULT ObjektOpExtension::ExklusivFlaeche_Geom (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
										  SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// gemeinsame Konturabschnitte (Kanten) der lONr-Fläche mit allen pEnumIn-Flächen;
// die Auswertung erfolgt für ulLageAusw
//  LINN	wenn pEnumIn-Fläche innerhalb,
//  LAUSS	wenn pEnumIn-Fläche außerhalb bzw.
//  LINAU	wenn pEnumIn-Fläche sowohl innerhalb als auch außerhalb
// der lONr-Fläche liegt
// ulIdent ist der Identifikator für die Ergebnisobjekte
HRESULT ObjektOpExtension::GemeinsameKontur_ONr (long lONr, ulong ulIdent, IEnumLONG* pEnumIn,
						ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	if (NULL == pEnumIn || 0 == pEnumIn->Count())	// keine pEnumIn-Flächen
		return E_UNEXPECTED;

	m_pW = MWind();		// MWind() liefert pWindow-Zeiger auf HauptFenster
	m_OpMode = GEMKONTUR;
	_sfSForm = sfSForm;	// Speicherform (10.02.98)

CEierUhr Wait (MVWind());

// Parameter der Bezugsfläche ermitteln
IObjektGeometrie* pIOG = NULL;
HRESULT hr = CreateInterfaceOG (&pIOG, lONr);

	if (FAILED(hr)) return hr;

KoOrd* plXK; KoOrd* plYK;
short iKCnt;	// Größe des Konturfeldes
long* plCnt;	// Anzahl der Stützpunkte in den Konturen

	pIOG->GetObjTyp (&_iOT);
	if (_iOT != OT_FLAECHE)
	{
		pIOG->Release();
		return E_UNEXPECTED;	// keine Fläche
	}

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetKCnt (&iKCnt);
	pIOG->GetLPCnt (&plCnt);

	_pBO = EFlaecheErzeugen (iKCnt, plXK, plYK, plCnt);
	if (! _pBO)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		DELETE_OBJ (_pBO);		// vorsichtshalber
		pIOG->Release();
		return E_OUTOFMEMORY;
	}

GeoFlaeche* pBFl = new GeoFlaeche (lONr, 0, *(EFlaeche*)_pBO); // Bezugsfläche

	if (! pBFl)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		DELETE_OBJ (_pBO);
		pIOG->Release();
		return E_OUTOFMEMORY;
	}


// Objektnummern der anderen Flächenobjekte aus pEnumIn auslesen
HRESULT hrRet = GetObjNummern (pEnumIn);

	if (hrRet != S_OK)
		return hrRet;

	if (bFortAnz)	// mit Fortschrittsanzeige
	{
	long lSumme = 0;

		for (long i = 1; i < _lAnzOrigObj; i++)
			lSumme += StuetzpunkteAussen (m_plOrigObjNr[i]);

		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error

			THROW_FAILED_HRESULT (InitProgressIndicator (PI, ResID (IDS_GEMKONTUR_CAPTION, pRF),
														ResID(IDS_STATUS_STAND, pRF), lSumme));
			THROW_FAILED_HRESULT (RegisterPI (PI));
		}
		catch (_com_error& e)
		{
			return _COM_ERROR (e);
		}
	}

bool bAbbr = false;	// Operation wurde (durch Anwender) nicht/abgebrochen (false/true)
// das definierte Setzen von bAbbr auf "false" ist notwendig, da KonturGemeinsamkeiten() ohne
// Beeinflussung von bAbbr durchlaufen werden kann (09.02.98)

	for (long i = 0; i < _lAnzOrigObj; i++)
	{
		if (m_plOrigObjNr[i] == lONr)
			continue;		// kein Test mit "sich selbst" (10.02.98)

	// Parameter der anderen Flächenobjekte ermitteln
	IObjektGeometrie* pIOG2 = NULL;
	HRESULT hr = CreateInterfaceOG (&pIOG2, m_plOrigObjNr[i]);

		if (FAILED(hr)) return hr;

	short iOT2;
	KoOrd* plXK2; KoOrd* plYK2;
	short iKCnt2;	// Größe des Konturfeldes
	long* plCnt2;	// Anzahl der Stützpunkte in den Konturen

		pIOG2->GetObjTyp (&iOT2);
		if (iOT2 != OT_FLAECHE)
		{
			pIOG2->Release();
			return E_UNEXPECTED;	// keine Fläche
		}

		pIOG2->GetX ((void**)&plXK2);
		pIOG2->GetY ((void**)&plYK2);
		pIOG2->GetKCnt (&iKCnt2);
		pIOG2->GetLPCnt (&plCnt2);

	EFlaeche* pFl2 = EFlaecheErzeugen (iKCnt2, plXK2, plYK2, plCnt2);

		if (! pFl2)
		{
			DEX_Error (RC_objoperi, EC_NOMEMORY);
			pIOG2->Release();
			return E_OUTOFMEMORY;
		}

		pBFl->KonturGemeinsamkeiten (pFl2, ulLageAusw, _CL1, bAbbr,
									 (BaseProgressStatus*)GetPIProxy());
		DELETE_OBJ (pFl2);
		pIOG2->Release();

		if (bAbbr)
		{
			hrRet = E_FAIL;
			break;
		}
	}

	DELETE_OBJ (_pBO);
	pIOG->Release();


// in _CL1 wurden die gemeinsamen Konturabschnitte abgelegt
CRing ri1 (_CL1);  // Navigator für ListContainer ClipListe _CL1

//	if (0 == ulIdent)		// kein Identifikator übergeben
//		ulIdent = DEX_GetUnknownIdentEx (DEX_GetObjectProject(lONr));

	IdentModify (ulIdent);	// alle Objekte aus _CL1 mit ulIdent versehen

HPROJECT hPr = 0;	// hier ist sicher noch Handlungsbedarf !!!

	hrRet = GemeinsameRoutine2 (hPr, ppEnumOut);	// alle Objekte aus _CL1 an TRiAS

	_CL1.EveryDelete();		// ClipListe löschen
	
	return hrRet;

} // GemeinsameKontur_ONr


// --------------------------------------------------------------------------------------------
// gemeinsame Konturabschnitte (Kanten) der lONr-Fläche mit allen pEnumIn-Flächen
HRESULT ObjektOpExtension::GemeinsameKontur_Geom (IObjektGeometrie* pIOG, ulong ulIdent,
										  IEnumLONG* pEnumIn, ulong ulLageAusw, SpForm sfSForm,
										  bool bFortAnz, IEnumLONG** ppEnumOut)
{
	return E_NOTIMPL;
} // GemeinsameKontur_Geom


// --------------------------------------------------------------------------------------------
// Vereinigung von Linienobjekten (auch für externen Aufruf);
// pEnumIn:   Objektnummern der zu vereinigenden Linien
// ppEnumOut: Objektnummern der vereinigten Linien bzw. der Linien, die nicht vereinigt werden
//            konnten
HRESULT ObjektOpExtension::LinienZusammenfassung (IEnumLONG* pEnumIn, ulong ulIdent,
											 double dFill, bool bAsArea, IEnumLONG** ppEnumOut)
{
	_ASSERTE (pEnumIn != NULL);
	_ASSERTE (ulIdent != 0);
	_ASSERTE ((ulong)-1 != ulIdent);

HRESULT hr = S_OK;

	try
	{
	// nicht genutzter ProgressIndicator
	VARIANT varPI;
	
		VariantInit (&varPI);

	// Objektnummern der zu vereinigenden Linien
	WEnumObjectsByNumber wInput;

	// Objektnummern der Ergebnisobjekte, d.h. der vereinigten Linien
	WEnumObjectsByNumber wOutput;

	// Objektnummern der Originalobjekte, die zu einer Vereinigung beigetragen haben
	VARIANT varUsed;

		VariantInit (&varUsed);

		// Objektnummern der zu vereinigenden Linien aus IEnumLONG* pEnumIn nach 
		// WEnumObjectsByNumber wInput weiterreichen
		wInput = pEnumIn;

#if _TRiAS_VER < 0x0300

	WExtLinienVerfolgung LinVer (CLSID_ExtLinienVerfolgung);
	
		hr = LinVer->LinesUnion (
					wInput,			// zu vereinigende Objekte
					dFill,			// Toleranz (in Meter)
					true,			// Merkmale der Originalobjekte werden vererbt
					bAsArea,		// vereinigte Linien möglichst in Flächen umwandeln (true)
					varPI,			// kein ProgressIndicator
					&varUsed,		// Objektnummern der zur Vereinigung beigetragenen Linien
					wOutput.ppi());	// vereinigte Linien
#else

	WExtLinienVerfolgungEx LinVer (CLSID_ExtLinienVerfolgung);
	HPROJECT hPr = DEX_GetObjectsProject (ulIdent);
	
		hr = LinVer->LinesUnion (
					reinterpret_cast<INT_PTR>(hPr),
					wInput,			// zu vereinigende Objekte
					dFill,			// Toleranz (in Meter)
					true,			// Merkmale der Originalobjekte werden vererbt
					bAsArea,		// vereinigte Linien möglichst in Flächen umwandeln (true)
					varPI,			// kein ProgressIndicator
					&varUsed,		// Objektnummern der zur Vereinigung beigetragenen Linien
					wOutput.ppi());	// vereinigte Linien

#endif // _TRiAS_VER < 0x0300

		if (FAILED(hr)) _com_issue_error (hr);

		_bNeuZeigen = false;	// keine Recherchefenster
		_bOrigZeigen = false;	//  für Ergebnisanzeige

	// Test, ob überhaupt eine Vereinigung erfolgt ist
	ulong ulCnt = 0;

		if (!wOutput.IsValid() || FAILED(wOutput->GetCount (&ulCnt)))
			ulCnt = 0;

		if (0 == ulCnt)		// keine vereinigten Linien gebildet
		{
		// Objektnummern aller ursprünglichen Linien aus wInput an ppEnumOut zurückgeben
		WEnumLONG wOut (wInput);	// mit implizitem QueryInterface

		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
			*ppEnumOut = wOut.detach();

			return S_FALSE;
		}

		// den vereinigten Linien nur noch den Identifikator ulIdent zuweisen
		IdentAndRechWindows (wOutput, NULL, ulIdent, true);

	// Objektnummern der Ergebnisobjekte für evtl. Löschen über Menüpunkt von wOutput nach
	// m_plNeuObjNr
	long lONr = 0;

		_lAnzNeuObj = ulCnt;

		DELETE_VEC (m_plNeuObjNr);
		m_plNeuObjNr = new long[_lAnzNeuObj];
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoperi, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
		m_lNeuInd = 0;   // Laufindex für m_plNeuObjNr

		for (wOutput->Reset(); S_OK == wOutput->Next (1, &lONr, NULL); )
		{
			m_plNeuObjNr[m_lNeuInd] = lONr;
			m_lNeuInd++;
		}

		// die Objektnummern der evtl. ungenutzten Linien zu wOutput hinzufügen
		hr = VariantChangeType (&varUsed, &varUsed, 0, VT_UNKNOWN);
		if ((S_OK == hr) && (varUsed.punkVal != NULL))	
		{
		WEnumObjectsByNumber wUsed (varUsed.punkVal);
		long lONrIn = 0, lONrUse = 0;

			for (pEnumIn->Reset(); S_OK == pEnumIn->Next (1, &lONrIn, NULL); )
			{
			bool bBreak = false;	// innere for-Schleife nicht abgebrochen

				for (wUsed->Reset(); S_OK == wUsed->Next (1, &lONrUse, NULL); )
					if (lONrIn == lONrUse)
					{
						bBreak = true;
						break;		// innere for-Schleife
					}

				if (bBreak) continue;	// äußere for-Schleife
				wOutput->AddItem (lONrIn);	// Objektnummer eines ungenutzten Objektes
			}
		}


	// Objektnummern der vereinigten und ungenutzten Linien aus WEnumObjectsByNumber wOutput
	// nach IEnumLONG** ppEnumOut weiterreichen
	WEnumLONG wOut (wOutput);	// mit implizitem QueryInterface

		*ppEnumOut = wOut.detach();
	}

	catch (_com_error& e)
	{
		// Anbindung an Erweiterung "maschbld.ext" ist nicht gelungen
		if (HRESULT_FROM_WIN32(ERROR_DLL_NOT_FOUND) == _COM_ERROR(e))
		{
		ResString resText (ResID (IDS_NOMASCHBLD, pRF), 250);
		ErrCode rcDummy;

			DEX_SetError (rcDummy, 0, WC_MESSAGE_OPER, (void*)resText.Addr());
		}

		hr = _COM_ERROR(e);
	}

	return hr;

} // LinienZusammenfassung


// --------------------------------------------------------------------------------------------
// 2 Linienobjekte werden (möglichst) zu einem gemeinsamen Linienobjekt vereinigt;
// evtl. Lücke wird ausgefüllt, wenn sie <= dFill ist; ist die Ergebnislinie geschlossen, wird
// sie für bAsArea = true in ein Flächenobjekte umgewandelt
HRESULT ObjektOpExtension::LinienZusammenfassung (IObjektGeometrie* pIOGIn1,
										IObjektGeometrie* pIOGIn2, double dFill, bool bAsArea,
										ulong ulIdent, IObjektGeometrie** ppIOGOut)
{
	_ASSERTE (pIOGIn1 != NULL);
	_ASSERTE (pIOGIn2 != NULL);
	_ASSERTE (ppIOGOut != NULL);

	if (!pIOGIn1 || !pIOGIn2 || !ppIOGOut)
		return E_POINTER; 

// Objekttypen der beiden Objekte ermitteln
short iOT1, iOT2;

	pIOGIn1->GetObjTyp (&iOT1);
	pIOGIn2->GetObjTyp (&iOT2);
	if (iOT1 != OT_KANTE || iOT2 != OT_KANTE)
		return E_INVALIDARG;	// nicht beides Linien

	return E_NOTIMPL;

} // LinienZusammenfassung


// --------------------------------------------------------------------------------------------
// Objektnummern aus pEnumIn auslesen und in m_plOrigObjNr bereitstellen; für bBObj = true wird
// noch ein Platz für die Objektnumer des Bezugsobjektes reserviert
HRESULT ObjektOpExtension::GetObjNummern (IEnumLONG* pEnumIn, bool bBObj)
{
	_ASSERTE (pEnumIn != NULL);

	_lAnzOrigObj = pEnumIn->Count();	// Anzahl der Objekte
	if (bBObj) _lAnzOrigObj++;

	DELETE_VEC (m_plOrigObjNr);
	m_plOrigObjNr = new long [_lAnzOrigObj];
	if (! m_plOrigObjNr)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}
		
	pEnumIn->Reset();

HRESULT hrRet = pEnumIn->Next (_lAnzOrigObj, m_plOrigObjNr, NULL);

	_ASSERTE (hrRet == S_OK);

	m_lOrigInd = 0;		// Laufindex von m_plOrigObjNr

	return hrRet;
} // GetObjNummern


// --------------------------------------------------------------------------------------------
// Splitten aller Objekte, deren Objektnummern in pEnumIn übergeben werden; die Objektnummern
// der neu erzeugten Teilobjekte bzw. der Originalobjekte, die nicht gesplittet werden müssen,
// werden in ppEnumOutAtom, die Objektnummern der gesplitteten Originalobjekte in ppEnumOutMod
// zurückgegeben; lFuzzyX bzw. lFuzzyY sind die Toleranzen in x- bzw. y-Richtung innerhalb
// derer noch eine Gemeinsamkeit angenommen wird; Teilobjekte, deren Länge kleiner/gleich
// lDangle ist, werden gar nicht erst erzeugt;
// return-Werte sind:
//   S_OK           fehlerfreies Splitting
//   S_FALSE        es wurden keine Objekte übergeben
//   E_OUTOFMEMORY	unzureichender dynamischer Speicher
//   E_POINTER      Pointer-Parameter von Splitting() sind NULL
//   E_NOINTERFACE  Anbindung an Interface nicht gelungen
//   E_FAIL         SubRoutinen von Splitting() haben "false" zurückgegeben
HRESULT ObjektOpExtension::SplittingBase (HPROJECT hPr, IEnumLONG* pEnumIn, 
	KoOrd lFuzzyX, KoOrd lFuzzyY, KoOrd lDangle, IEnumLONG** ppEnumOutAtom, 
	IEnumLONG** ppEnumOutMod, IEnumLONG** ppEnumOutNotTouched)
{
	_ASSERTE (pEnumIn != NULL);
	_ASSERTE (ppEnumOutAtom != NULL);	// ppEnumOutMod kann NULL sein

	if (NULL == pEnumIn || NULL == ppEnumOutAtom)
		return E_POINTER;

	if (0 == pEnumIn->Count())
		return S_FALSE;	// es wurden keine Objekte übergeben

// Objektnummern der zu splittenden Objekte aus pEnumIn auslesen
HRESULT hrRet = GetObjNummern (pEnumIn);

	if (hrRet != S_OK)
		return hrRet;

	m_lOrigInd = _lAnzOrigObj;	// wird z. B. bei CopyFeatures() benötigt
	m_OpMode = SPLITTING;

	// zu allen SplittingObjekten MarkLine-Objekte anlegen
	BuildMarkLine();

// ppEnumOutAtom für die Rückgabe der Objektnummern der erzeugten Teilobjekte bzw. der
// Originalobjekte, die nicht gesplittet werden müssen, definieren
HRESULT hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
							   IID_IEnumLONG, (LPVOID *)ppEnumOutAtom);

	if (hr != S_OK) return hr;

// Liste für die Objektnummern der Originalobjekte, die gesplittet wurden
	if (ppEnumOutMod)
	{
		hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
							   IID_IEnumLONG, (LPVOID*)ppEnumOutMod);
		if (hr != S_OK) return hr;
	}

// Liste für die Objektnummern der Originalobjekte, die nicht gesplittet wurden
	if (ppEnumOutNotTouched)
	{
		hr = CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
							   IID_IEnumLONG, (LPVOID *)ppEnumOutNotTouched);
		if (hr != S_OK) return hr;
	}

//	min, max setzen
PIFLAGS rgFlags = (PIFLAGS)(PIFLAGS_STATUS |			// Anzeige der Statuszeile, 
							PIFLAGS_TIME |				//  der verbleibenden Zeit und
							PIFLAGS_ADJUSTPERCENT |		//  des Prozentwertes
							PIFLAGS_INIT_SHOWWINDOW);	// erst dann Anzeige, wenn etwas zu
														//  sehen ist
	hr = GetPIProxy()->Restart (1, _lAnzOrigObj, rgFlags);
	if (FAILED(hr)) return hr;


//	Caption setzen			
ResString resTitel (ResID (IDS_VERSCHNITT_CAPTION, pRF), 100);
CComBSTR bstrTitel (resTitel.Addr());	// char* in Bi-String konvertieren

	hr = GetPIProxy()->ChangeText (PIFLAGS_CAPTION, bstrTitel);
	if (FAILED(hr)) return hr;
			
//	Adjust-Text setzen
ResString resAdjust (ResID (IDS_STATUS_STAND, pRF), 100);
CComBSTR bstrAdjust (resAdjust.Addr());

	hr = GetPIProxy()->ChangeText (PIFLAGS_ADJUSTPERCENT, bstrAdjust);
	if (FAILED(hr)) return hr;

	
	// Abarbeitung jedes SplittingObjektes mit allen anderen Objekten
	for (long j = 0; j < _lAnzOrigObj; j++)
	{
		hr = GetPIProxy()->IncrementPosition (NULL);	// Progress-Indicator aktualisieren
		if (FAILED(hr)) return hr;

		hr = GetPIProxy()->IsCanceled();	// Abbruch?
		if (FAILED(hr)) return hr;
		if (S_OK == hr) return S_FALSE;		// Abbruch durch den Anwender

	int iOT1 = DEX_GetObjectType (m_plOrigObjNr[j]);

		if (iOT1 != OT_KANTE && iOT1 != OT_FLAECHE)
			continue;	// es werden nur Linien und Flächen berücksichtigt

	HRESULT hr = Verschnitt (hPr, m_plOrigObjNr[j], m_plOrigObjNr, _lAnzOrigObj, 
		lFuzzyX, lFuzzyY, lDangle, ppEnumOutAtom, ppEnumOutMod, ppEnumOutNotTouched);

		if (hr != S_OK) return hr;
	} // for j

	return SetMembers (*ppEnumOutMod, *ppEnumOutAtom);

} // SplittingBase


// --------------------------------------------------------------------------------------------
// zu allen SplittingObjekten MarkLine-Objekte anlegen
bool BuildMarkLine (void)
{
	return true;
} // BuildMarkLine


// --------------------------------------------------------------------------------------------
// lOrigObjNr1-Objekt mit allen anderen Objekten verschneiden
HRESULT Verschnitt (HPROJECT hPr, long lOrigObjNr1, long* plOrigObjNr, long lAnzOrigObj,
	KoOrd lFuzzyX, KoOrd lFuzzyY, KoOrd lDangle, IEnumLONG** ppEnumOutAtom, 
	IEnumLONG** ppEnumOutMod, IEnumLONG** ppEnumOutNotTouched)
{
	_ASSERTE (plOrigObjNr != NULL);

IObjektGeometrie* pSpObj1 = NULL;
HRESULT hr = CreateInterfaceOG (&pSpObj1, lOrigObjNr1);

	if (FAILED(hr)) return hr;

short iOT1;					// Objekttyp,
long lSize1;				//  Länge,
short iKCnt1 = 0;			//  Anzahl der Konturen (bei Linienobjekt = 0) und
KoOrd* plXK1; KoOrd* plYK1;	//  Koordinaten des pSpObj1-SplittingObjektes
KoOrd lXmin1, lXmax1, lYmin1, lYmax1;	// Koordinaten des pSpObj1-Containers

	pSpObj1->GetObjTyp (&iOT1);
	pSpObj1->GetX ((void**)&plXK1);
	pSpObj1->GetY ((void**)&plYK1);
	pSpObj1->GetCont (&lXmin1, &lXmax1, &lYmin1, &lYmax1);

ObjRechteck OC1 (lXmin1, lXmax1, lYmin1, lYmax1);	// Objektcontainer des pSpObj1-Objektes
int iKInd;	// Index der Flächenkontur, aus der pML gebildet wird (für Kante gilt -1)
bool bClosed;	// pML geschlossen (true) oder offen (false)

	if (OT_KANTE == iOT1)
	{
		pSpObj1->GetCnt (&lSize1);
		iKInd = -1;
		bClosed = false;
		if (plXK1[0] == plXK1[lSize1-1] && plYK1[0] == plYK1[lSize1-1])
			bClosed = true;
	}
	else	// bei Flächenobjekt nur Außenkontur berücksichtigen
	{
	long* plCnt;	// Anzahl der Stützpunkte in den Konturen

		pSpObj1->GetLPCnt (&plCnt);
		lSize1 = plCnt[0];	// Anzahl der Stützpunkte der Außenkontur
		pSpObj1->GetKCnt (&iKCnt1);
		iKInd = 0;
		bClosed = true;
	}

// (erweiterte) Stützpunktfolge des pSpObj1-SplittingObjektes
MarkLine* pML = new MarkLine (lSize1, iKInd, bClosed);

	if (!pML || !pML->Vektor())
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		DELETE_OBJ (pML);
		pSpObj1->Release();
		return E_OUTOFMEMORY;
	}

	// 1. Markierung der markierten pML-Punkte wird standardmäßig auf "NORMAL" gesetzt
	for (long i = 0; i < lSize1; i++)
	{
		pML->SetX (i, plXK1[i]);
		pML->SetY (i, plYK1[i]);
	}

KoOrd lXmin2, lXmax2, lYmin2, lYmax2;	// Koordinaten des pSpObj2-Containers
bool bCommon = false;	// pSpObj1 besitzt nach der Routine VektorErweiterung() Stützpunkte
						//  mit der Markierung GEMEINSAM (true) oder nicht (false)

	// Abarbeitung aller anderen Objekte
	for (long jj = 0; jj < lAnzOrigObj; jj++)
	{
	int iOT2 = DEX_GetObjectType (plOrigObjNr[jj]);

		if (iOT2 != OT_KANTE && iOT2 != OT_FLAECHE)
			continue;

		if (lOrigObjNr1 == plOrigObjNr[jj] &&
			S_OK != FehlerhaftesObjekt (NULL, lOrigObjNr1))
			continue;	// kein Splitting mit "sich selbst", wenn Objekt fehlerfrei

	IObjektGeometrie* pSpObj2 = NULL;
	HRESULT hr = CreateInterfaceOG (&pSpObj2, plOrigObjNr[jj]);

		if (FAILED(hr))
		{
			DELETE_OBJ (pML);
			pSpObj1->Release();
			return hr;
		}

		pSpObj2->GetCont (&lXmin2, &lXmax2, &lYmin2, &lYmax2);

	ObjRechteck OC2 (lXmin2, lXmax2, lYmin2, lYmax2);	// Objektcontainer des pSpObj2-Objektes

		if (OC1.EpsDurchschnitt (OC2, lFuzzyX, lFuzzyY))
			VektorErweiterung (plXK1, plYK1, lSize1, pML, pSpObj2, lFuzzyX, lFuzzyY,
							   lOrigObjNr1 == plOrigObjNr[jj], bCommon);

		pSpObj2->Release();

	} // for jj

	pSpObj1->Release();

	if (bCommon)	// das pSpObj1-Objekt hat Stützpunkte mit speziellen Markierungen
	{
	bool bRet = TeilobjekteBilden (hPr, pML, lOrigObjNr1, lDangle, *ppEnumOutAtom);

		// Objektnummer des gesplitteten Originalobjektes zurückgeben
		if (ppEnumOutMod && bRet)
			((IEnum<LONG>*)*ppEnumOutMod)->AddItem (lOrigObjNr1);

/*	nachfolgende if-Anweisung wurde deaktiviert, 
	weil sonst beim Löschen der neu erzeugten Objekte auch diese mit gelöscht würden;
	die andere Konsequenz ist mir natürlich auch klar: für eine nachfolgende Flächenvereinigung
	müßten erst die Objekte gelöscht werden, die gesplittet wurden, damit jetzt nur noch die
	Atom-Objekte (die Splittergebnisse und diejenigen, die sich mit keinem anderen Objekt
	berühren) übrig bleiben (06.10.99)
		// Objektnummern auch der Originalobjekte in ppEnumOutAtom übernehmen, die nicht
		// gesplittet werden müssen
		if (! bRet)
			((IEnum<LONG>*)*ppEnumOutAtom)->AddItem (lOrigObjNr1);
*/
		if (!bRet && NULL != ppEnumOutNotTouched)
			((IEnum<LONG>*)*ppEnumOutNotTouched)->AddItem (lOrigObjNr1);
	}

/*	nachfolgender else-Zweig wurde deaktiviert, s.o.
	// Objektnummern auch der Originalobjekte in ppEnumOutAtom übernehmen, die sich mit keinem
	// anderen Objekt berühren
	else
		((IEnum<LONG>*)*ppEnumOutAtom)->AddItem (lOrigObjNr1);
*/
	else if(NULL != ppEnumOutNotTouched)
		((IEnum<LONG>*)*ppEnumOutNotTouched)->AddItem (lOrigObjNr1);

	DELETE_OBJ (pML);
	return S_OK;

} // Verschnitt


// --------------------------------------------------------------------------------------------
// Erweiterung des aus (plX1, plY1, lSize1) gebildeten pML-Vektors durch evtl. mit pSpObj2
// gemeinsame Punkte; bSelf == true heißt, daß ein Objekt mit "sich selbst" verglichen wird;
// enthält pML am Ende der Routine mindestens einen Stützpunkt mit der Markierung GEMEINSAM,
// wird in bCommon true zurückgegeben
void VektorErweiterung (KoOrd* plX1, KoOrd* plY1, long lSize1, MarkLine*& pML,
						IObjektGeometrie* pSpObj2, KoOrd lFuzzyX, KoOrd lFuzzyY, bool bSelf,
						bool& bCommon)
{
	_ASSERTE (plX1 != NULL);
	_ASSERTE (plY1 != NULL);
	_ASSERTE (pML != NULL);
	_ASSERTE (pSpObj2 != NULL);

short iOT2;				// Parameter des pSpObj2-Objektes
long lSize2;
short iKCnt2 = 0;		//  Anzahl der Konturen (bei Linienobjekt = 0)
KoOrd* plX2; KoOrd* plY2;

	pSpObj2->GetObjTyp (&iOT2);

	if (OT_KANTE == iOT2)
		pSpObj2->GetCnt (&lSize2);
	else	// bei Flächenobjekt nur Außenkontur berücksichtigen
	{
	long* plCnt;	// Anzahl der Stützpunkte in den Konturen

		pSpObj2->GetLPCnt (&plCnt);
		lSize2 = plCnt[0];	// Anzahl der Stützpunkte der Außenkontur
		pSpObj2->GetKCnt (&iKCnt2);
	}
	
	pSpObj2->GetX ((void**)&plX2);
	pSpObj2->GetY ((void**)&plY2);

EPunkt Pj0;
EPunkt Pj1 (plX1[0], plY1[0]);	// pSpObj1->SP(0)

long jj;				// Index für pSpObj2-Strecken
SchnittErg Fo = KEINE;	// Schnittergebnis zweier Strecken
DoublePair ZPA, ZPE;	// evtl. gemeinsame Punkte beider Strecken
EPunkt Pjj0;				// pSpObj2->SP(jj)

	// Test von jeder pSpObj1-Strecke mit jeder pSpObj2-Strecke
	for (long j = 0; j < lSize1-1; j++)		// pSpObj1-Strecken
	{
		Pj0.X() = Pj1.X();		// pSpObj1->SP(j)
		Pj0.Y() = Pj1.Y();
		Pj1.X() = plX1[j+1];	// pSpObj1->SP(j+1)
		Pj1.Y() = plY1[j+1];

	Strecke sj (Pj0, Pj1);
	ObjRechteck SC1 = BuildRectangle (Pj0, Pj1);

		bSelf ? (jj = j + 2) : (jj = 0);

	EPunkt Pjj1 (plX2[jj], plY2[jj]);	// pSpObj2->SP(jj)
	SchnittErg FoV = KEINE;		// Fo für jj-1

		for (; jj < lSize2-1; jj++)	// pSpObj2-Strecken
		{
			// bei Test mit "sich selbst" von geschlossenene Objekten dürfen die 1. und letzte
			// Strecke nicht miteinander getestet werden, da sie sich ja gerade eben berühren
			if (bSelf && pML->IsClosed() && 0 == j && jj == lSize1-2)
			{
				FoV = KEINE;
				continue;
			}

			Pjj0.X() = Pjj1.X();		// pSpObj2->SP(jj)
			Pjj0.Y() = Pjj1.Y();
			Pjj1.X() = plX2[jj+1];		// pSpObj2->SP(jj+1)
			Pjj1.Y() = plY2[jj+1];

		// Test, ob die Container der beiden zu vergleichenden Strecken untereinander
		// durchschnittsleer sind
		ObjRechteck SC2 = BuildRectangle (Pjj0, Pjj1);

			if (! SC1.EpsDurchschnitt (SC2, lFuzzyX, lFuzzyY))
			{
				FoV = KEINE;
				continue;	// die Container beider Strecken sind durchschnittsleer
			}

			Fo = sj.EpsGemeinsamePunkte (Pjj0, Pjj1, ZPA, ZPE, lFuzzyX, lFuzzyY);
	
			if (KEINE == Fo || UEBERLAPP == Fo)
			{
				FoV = Fo;
				continue;	// für jj-for-Schleife
			}
			else
			{
				if (RAND == Fo)
				{
				double dx0 = ZPA.X() - Pjj0.X();
				double dy0 = ZPA.Y() - Pjj0.Y();
				double dx1 = ZPA.X() - Pjj1.X();
				double dy1 = ZPA.Y() - Pjj1.Y();
				double dFuzzy = lFuzzyX*lFuzzyX + lFuzzyY*lFuzzyY;

					// durch diese Bedingung werden RAND-Punkte, die gleichzeitig innerhalb
					// eines UEBERLAPP-Bereiches liegen, ausgeschlossen
					if ((jj == 0 || FoV != RAND) &&
						(jj > 0 || dx0*dx0+dy0*dy0 > dFuzzy) &&
						(jj < lSize2-2 || dx1*dx1+dy1*dy1 > dFuzzy))
					{
						FoV = Fo;
						continue;	// für jj-for-Schleife
					}
				}
			}
			
			// Bei ECHT == Fo || INNEN == Fo wird ZPA immer bearbeitet.
			FoV = Fo;

			// Zwischen 2 Stützpunkten des ursprünglichen Objektes können mehrere zusätzliche
			// Punkte liegen. Deshalb wird der Index k von pML ermittelt, vor dem der
			// zusätzliche Punkt ZPA eingefügt werden soll.
			bCommon = true;	// pML hat mindestens einen Stützpunkt mit Markierung GEMEINSAM

		long k = EinfIndex (plX1, plY1, j, pML, ZPA);

			_ASSERTE (k >= 0);

			EinfMarkPunkt (pML, ZPA, k);

			// bei Test mit "sich selbst" ist der gemeinsame Punkt außer bei der
			// j-Position auch bei der jj-Position einzufügen
			if (bSelf)
			{
				k = EinfIndex (plX1, plY1, jj, pML, ZPA);
				_ASSERTE (k >= 0);
				EinfMarkPunkt (pML, ZPA, k);
			}

		} // for jj
	} // for j

} // VektorErweiterung


// --------------------------------------------------------------------------------------------
// Zwischen 2 Stützpunkten j und j+1 des Vektors pXK,pYK können bei Schnitt mit einer anderen
// Linie mehrere zusätzliche Punkte liegen. Es ist der Index (return-Wert) des aus dem Vektor
// pXK,pYK gebildeten MarkLine-Vektors pML zu ermitteln, bei dem ein zusätzlicher Punkt ZP
// eingefügt werden soll.
long EinfIndex (KoOrd* pXK, KoOrd* pYK, long j, MarkLine* pML, DoublePair ZP)
{
	_ASSERTE (pXK != NULL);
	_ASSERTE (pYK != NULL);
	_ASSERTE (pML != NULL);
	_ASSERTE (j >= 0);

	if (!pXK || !pYK || !pML)
		return -2;		// ein unerlaubter Index
		
long lVekL = pML->ADP();

// zuerst ka mit pML->x(ka) == pXK[j] && pML->y(ka) == pYK[j] sowie ke mit
// pML->x(ke) == pXK[j+1] && pML->y(ke) == pYK[j+1] suchen
long ka = j - 1;

	do
		ka++;          
	while ((pML->x(ka) != pXK[j] || pML->y(ka) != pYK[j]) &&
		   ka < lVekL);

long ke = ka;	// 10.06.98

	do
		ke++;          
	while ((pML->x(ke) != pXK[j+1] || pML->y(ke) != pYK[j+1]) &&
		   ke < lVekL);

// Danach muß getestet werden, in welchem Teilabschnitt pML[k'],pML[k'+1] der ursprünglichen
// Strecke pK[j],pK[j+1] die Einfügung erfolgen muß, d.h. auf welcher Teilstrecke
// pML[k'],pML[k'+1] der Punkt ZP liegt (mit ka <= k' und k' <= ke).
double dMinAbst = 1.0E308;
long k = ka;
long ks = k + 1;	// k' (return-Wert)

	do
	{
	double dAbst;

		if (AbstandPktStrecke (ZP, pML->DP(k), pML->DP(k+1), dAbst) &&
			dAbst < dMinAbst)
		{
			dMinAbst = dAbst;
			ks = k + 1;
		}
		k++;
	}
	while ((pML->x(k) != pXK[j+1] || pML->y(k) != pYK[j+1]) &&
		   dMinAbst > 0. &&		// 10.06.98
//		   k < lVekL);
		   k < ke);	// wie konnte das so lange gut gehen ???? unbegreiflich !!! (10.06.98)

	_ASSERTE (ks <= ke);

	return ks;

} // EinfIndex


// --------------------------------------------------------------------------------------------
// Punkt DP in Vektor pML vor Vektorindex 0 <= lIndex < Vektorlänge mit der Markierung
// GEMEINSAM einfügen; existiert schon ein koordinatengleicher Punkt, wird
// nur die Markierung des schon vorhandenen Punktes modifiziert;
bool EinfMarkPunkt (MarkLine*& pML, DoublePair DP, long lIndex)
{
	_ASSERTE (pML != NULL);

	if (! pML) return false;

	_ASSERTE (lIndex >= 0);
	
long lVekL = pML->ADP();

	_ASSERTE (lIndex < lVekL);

	if (lIndex < 0 || lIndex >= lVekL) // unerlaubter Index
	{
		DEX_Error (RC_objoperi, EC_ILLPARS);
		return false;
	}

bool b1 = (DP.X() != pML->x(lIndex) || DP.Y() != pML->y(lIndex));
bool b2 = (0 == lIndex || DP.X() != pML->x(lIndex-1) || DP.Y() != pML->y(lIndex-1));

	// DP wird nur eingefügt, wenn kein koordinatengleicher Punkt existiert
	if (b1 && b2)
	{
		AddMarkPunkt (pML, lIndex, DP, GEMEINSAM);
		return true;
	}
	
	// DP nicht einfügen (Koordinatengleichheit), nur Markierung modifizieren
	else
	{
	long lInd;	// Index, bei dem die Modifizierung (evtl.) vorgenommen wird

		b1 ? (lInd = lIndex-1) : (lInd = lIndex);

		pML->ModMark1 (lInd, GEMEINSAM);

		// bei geschlossener Kante die Markierungen von Anfangs- und Endpunkt ggf. in
		// Übereinstimmung bringen
		if (pML->IsClosed() &&	// geschlossene Kante
			(0 == lInd || lInd == lVekL-1))
		{
			pML->ModMark1 (lVekL-1, GEMEINSAM);	// eine der beiden Zeilen ist umsonst,
			pML->ModMark1 (0, GEMEINSAM);		//  aber so spare ich mir eine Abfrage
		}
	}

   	return true;

} // EinfMarkPunkt


// --------------------------------------------------------------------------------------------
// pML an den Punkten mit der Markierung "GEMEINSAM" zerlegen; werden dabei 
// neue Teilobjekte nach TRiAS abgespeichert, wird true zurückgegeben, sonst false
bool TeilobjekteBilden (HPROJECT hPr, MarkLine* pML, long lAltObjNr, long lDangle,
						IEnumLONG* pEnumOut)
{
	_ASSERTE (pML != NULL);
	_ASSERTE (lAltObjNr != 0);
	_ASSERTE (lAltObjNr != -1);
	_ASSERTE (pEnumOut != NULL);

	if (!pML || !pEnumOut) return false;

long lVekL = pML->ADP();

	if (lVekL < 2) return false;

long i = 0;				// Index für pML-Punkte
bool bIsClosed = pML->IsClosed();

	// pML ist geschlossen, dann 1. Punkt mit Markierung "GEMEINSAM" suchen
	if (bIsClosed)
		while (pML->GetMk1(i) != GEMEINSAM)
		{
			i++;
			_ASSERTE (i < lVekL);
		}

bool bRet = false;	// return-Wert dieser Routine
long lAInd = i;		// Anfangsindex für den Teil der Linie, der aus pML übernommen wird
long lNeuONr;		// Objektnummer eines neuen Teilobjektes

	// Aufbau der Teilobjekte
	// lCounter zählt die abgearbeiteten pML-Punkte
	for (long lCounter = 0; lCounter < lVekL-1; lCounter++)
	{
		if (i < lVekL-1) i++;
		else i = 1;

	// wenn aktueller Punkt pML[i] die Markierung "GEMEINSAM" besitzt
	// und mindestens 2 Punkte vorhanden sind, dann Teilobjekt erzeugen
	Mar1 Mark = pML->GetMk1(i);

		if (GEMEINSAM == Mark && 
			lAInd != i &&		// es sind mindestens 2 Punkte für Teilobjekt vorhanden
			! (bIsClosed && ((lAInd == lVekL-1 && 0 == i) || (0 == lAInd && i == lVekL-1))))
		{
			if (i-lAInd+1 == lVekL ||		// Teilobjekt == Originalobjekt
				(bIsClosed && (lAInd == i)))
				return false;		//  hier braucht nichts Neues erzeugt zu werden

			if (NeuesTeilobjekt (hPr, pML, lAInd, i, lDangle, lAltObjNr, lNeuONr))
			{
				((IEnum<LONG>*)pEnumOut)->AddItem (lNeuONr);
				bRet = true;
			}

			lAInd = i;	// Anfangsindex für den nächsten Teilobjekt
		}
	}

	// evtl. noch Rest von pML verarbeiten
	if (lAInd != i &&	// es sind mindestens noch 2 Punkte vorhanden
		! (bIsClosed && ((lAInd == lVekL-1 && 0 == i) || (0 == lAInd && i == lVekL-1))))
	{
		if (i-lAInd+1 == lVekL ||		// Teilobjekt == Originalobjekt
			(bIsClosed && (lAInd == i)))
			return bRet;		//  hier braucht nichts Neues erzeugt zu werden

		if (NeuesTeilobjekt (hPr, pML, lAInd, i, lDangle, lAltObjNr, lNeuONr))
		{
			((IEnum<LONG>*)pEnumOut)->AddItem (lNeuONr);
			bRet = true;
		}
	}

	return bRet;

} // TeilobjekteBilden


// --------------------------------------------------------------------------------------------
// Testen der Länge des neu zu bildenden Objektes; ist die Länge kleiner/gleich lDangle,
// wird true zurückgegeben, sonst false
bool DangleObject (MarkLine* pML, long lAInd, long lEInd, long lDangle)
{
	_ASSERTE (pML != NULL);
	_ASSERTE (lAInd != lEInd);

long lVekL = pML->ADP();
long i = lAInd;
long i1;		// der auf i folgende Index
double dLaenge = 0.;

	do
	{
		if (i < lVekL-1) i1 = i + 1;
		else i1 = 1;

	double dx = pML->x(i) - pML->x(i1);
	double dy = pML->y(i) - pML->y(i1);

		dLaenge += sqrt(dx*dx + dy*dy);
		if (dLaenge > lDangle) return false;

		i = i1;
	}
	while (i < lEInd);

	return true;

} // DangleObject


// --------------------------------------------------------------------------------------------
// ein neues Teilobjekt erzeugen und nach TRiAS speichern (Rückgabe von true); wird Teilobjekt
// nicht erzeugt, weil es kürzer als lDangle ist oder der dynamische Speicher unzureichend ist,
// wird false zurückgegeben
bool NeuesTeilobjekt (HPROJECT hPr, MarkLine* pML, long lAInd, long lEInd, long lDangle,
					  long lAltObjNr, long& lNeuONr)
{
	_ASSERTE (pML != NULL);
	_ASSERTE (lAInd != lEInd);

long lVekL = pML->ADP();

	// Test auf lDangle-Länge nur beim 1. und letzten Teilstück von Linienobjekten
	if (!pML->IsClosed() && (0 == lAInd || lEInd == lVekL-1) &&	// 09.02.98
		DangleObject (pML, lAInd, lEInd, lDangle))
		return false;

	_ASSERTE (lAltObjNr != 0);
	_ASSERTE (lAltObjNr != -1);

IObjektGeometrie* pIOG = NULL;	// zu bildendes Teilobjekt

	// Anfang eines Teilobjektes
	if (FAILED(CreateInterfaceOG (&pIOG, DtoL(pML->x(lAInd)), DtoL(pML->y(lAInd)), OT_KANTE)))
		return false;

long lRestLen;		// Anzahl der noch an pIOG anzuhängenden Punkte

	if (lAInd < lEInd)
		lRestLen = lEInd - lAInd;
	else
	{
		_ASSERTE (pML->IsClosed() == true);

		lRestLen = lVekL - lAInd + lEInd - 1;
	}

KoOrd* plXK = new KoOrd [lRestLen];
KoOrd* plYK = new KoOrd [lRestLen];

	if (!plXK || !plYK)
	{
		DEX_Error (RC_objoperi, EC_NOMEMORY);
		DELETE_VEC (plXK);
		pIOG->Release();
		return false;
	}

long j = 0;			// Laufindex für die zu füllenden Vektoren plXK bzw. plYK
long k = lAInd + 1;	// Laufindex für den auszulesenden  Vektor pML

	do
	{
		plXK [j] = DtoL (pML->x(k));
		plYK [j] = DtoL (pML->y(k));

		j++;
		if (k < lVekL-1) k++;
		else k = 1;
	}
	while (j < lRestLen);

	pIOG->AddPunkt (plXK, plYK, lRestLen, -1, -1);	// pML-Teilobjekt an pIOG anhängen
	DELETE_VEC (plXK);
	DELETE_VEC (plYK);

bool bRet = TeilobjektSpeichern (hPr, pIOG, lAltObjNr, lNeuONr);

	pIOG->Release();

	return bRet;

} // NeuesTeilobjekt


// --------------------------------------------------------------------------------------------
// neu gebildetes Teilobjekt nach TRiAS speichern; gelingt Speicherung, wird true zurück
// gegeben, sonst false
bool TeilobjektSpeichern (HPROJECT hPr, IObjektGeometrie* pIOG, long lAltObjNr, long& lNeuONr)
{
	_ASSERTE (pIOG != NULL);
	_ASSERTE (lAltObjNr != 0);
	_ASSERTE (lAltObjNr != -1);

	// OGNewObject:     permanentes Objekt in Datenbank aufnehmen
//	// OGIgnoreIdent:	Identifikator ignorieren
//	pIOG->SetFlags (OGNewObject | OGIgnoreIdent);	// 06.10.99
	pIOG->SetFlags (OGNewObject);

ulong ulIdent = DEX_GetObjIdent (lAltObjNr);

	// ist für die Speicherung eines Objektes die Zieldatenquelle vorgegeben (hPr != 0),
	// sollte der Identifikator 0 sein (unbekannte Objektklasse), weil sonst vorrangig die
	// Zieldatenquelle durch DEX_GetObjectsProject(ulIdent) aus dem Identifikator ermittelt
	// wird
	if (0 != hPr && 0 != ulIdent && hPr != DEX_GetObjectsProject (ulIdent))
		pIOG->SetIdent (0L);

	if (0 == hPr)
	{
		_ASSERTE (0 != ulIdent);
		_ASSERTE ((ulong)-1 != ulIdent);

		pIOG->SetIdent (ulIdent);
		hPr = DEX_GetObjectsProject (ulIdent);
	}

short rgFlags = 0;

	pIOG->GetFlags(&rgFlags);
	pIOG->SetFlags(OGForceGeometry | rgFlags);	// falls es das erste Objekt dieser DQ ist

#if _TRiAS_VER < 0x0300
HRESULT hr = pIOG->GeometrieAnTRiAS (true, NULL);
#else
//INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectProject (lAltObjNr));
HRESULT hr = pIOG->GeometrieAnTRiASEx (reinterpret_cast<INT_PTR>(hPr), true, NULL);
#endif // _TRiAS_VER < 0x0300

	// wenn Objekt in DB eingespeichert wurde, dann Merkmale des lAltObjNr-Ursprungsobjektes
	// an das neu erzeugte lNeuONr-Objekt kopieren (dabei UniqueIdent modifizieren)
	if (S_OK == hr)
	{
		pIOG->GetONr (&lNeuONr);

	// UniqueIdent ersetzen durch "OPER_ ..."
/*
	string sUIText;
	ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sUIText, (char*)resText.Addr(), lNeuONr);
		MerkmaleKopieren (lAltObjNr, lNeuONr, sUIText);
*/
		((ObjektOpExtension*)g_pTE)->CopyFeatures (lAltObjNr, lNeuONr);
	}
	else
	{
		// Fehlerliste anlegen
		return false;
	}

	return true;

} // TeilobjektSpeichern


// --------------------------------------------------------------------------------------------
// Verschieben (eines Teilabschnittes) des lONr-Objektes;
// der kürzeste senkrechte Abstand des Bezugsspunktes (lXB,lYB) zu den Strecken des
// lONr-Objektes liefert Weite der Verschiebung; aus der Lage des Bezugsspunktes zum
// lONr-Objekt ergibt sich außerdem die Richtung der Verschiebung; die Strecke des
// lONr-Objektes, zu der der Bezugsspunkt den kleinsten Abstand hat, ist die Bezugsstrecke; sie
// wird senkrecht zum Lot vom Bezugsspunkt auf diese Strecke verschoben; alle anderen Strecken
// werden nachgezogen
//   lXB, lYB: Koordinaten des Bezugsspunktes
//   lXA, lYA: Koordinaten des Anfangspunktes
//   lXE, lYE: Koordinaten des Endpunktes
//             liegen der Anfangs-bzw. Endpunkt nicht exakt auf dem lONr-Objekt, wird der
//             jeweils nächstgelegene Punkt bestimmt (der auch zwischen 2 lONr-Stützpunkten
//             liegen kann); default: 1. bzw. letzter lONr-Stützpunkt
//   bVerlA:   Verlängerung der verschobenen Linie über den (lXA,lYA)-Punkt bzw.
//   bVerlE:   (lXE,lYE)-Punkt hinaus (true); default: true
//   lEps:     ist der Abstand eines neu hinzugefügten Anfangspunktes vom 1. Stützpunkt (mit
//             Maximumnorm) kleiner als lEps, wird er nicht hinzugefügt; ebenso Endpunkt und
//             letzter Stützpunkt
//   lXMin, lYMin, lXMax, lYMax: Koordinaten des Containers, bis zu dessen Rand die
//             Verlängerung bei bVerlA = true bzw. bVerlE = true erfolgen soll
HRESULT ObjektOpExtension::LinienVerschiebung_ONr (long lONr, KoOrd lXB, KoOrd lYB,
			  KoOrd lXA, KoOrd lYA, KoOrd lXE, KoOrd lYE, MoveDir MD, bool bVerlA, bool bVerlE,
			  KoOrd lEps, KoOrd lXMin, KoOrd lYMin, KoOrd lXMax, KoOrd lYMax, long* plONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (lXB > 0);
	_ASSERTE (lYB > 0);

	if (0 == lONr || -1 == lONr) return E_UNEXPECTED;

WObjektGeometrie wObj;		// ObjektGeometrie des lONr-Objektes

	try
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

	// ... initialisieren
		THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

		wObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

long lIndA;			// Index für kleinsten Abstand von Anfangspunkt (lXA,lYA) bzw.
long lIndE;			//  von Endpunkt (lXE,lYE) zu den Strecken des wObj-Objektes
BOOL bPA;			// Anfangs (lXA,lYA) bzw.
BOOL bPE;			//  Endpunkt (lXE,lYE) ist/ist nicht mit einem Stützpunkt identisch
					//  (true/false)
short iOT;
KoOrd* plXK; KoOrd* plYK;
long* plK;
long lFirstInd = 0;	// wenn wObj eine Linie ist: erster Index der Linie
					// wenn wObj eine Fläche ist: erster Index der Kontur, zu der lIndA gehört
long lAnz;			// wenn wObj eine Linie ist: Gesamtstützpunktanzhl
					// wenn wObj eine Fläche ist: Stützpunktanzahl der Kontur, zu der lIndA
					// gehört

	wObj->GetObjTyp (&iOT);

	_ASSERTE (iOT == OT_KANTE || iOT == OT_FLAECHE);

	wObj->GetCnt (&lAnz);
	wObj->GetX ((void**)&plXK);
	wObj->GetY ((void**)&plYK);
	if (OT_FLAECHE == iOT)
		wObj->GetLPCnt (&plK);

	// wenn Anfangspunkt (lXA,lYA) vorgegeben ist aber nicht auf wObj liegt, dann den
	// nächstgelegen Punkt auf wObj suchen (dabei wird sich i.d.R. ein Punkt zwischen 2
	// Stützpunkten ergeben)
	if (lXA > 0 && lYA > 0)		// Anfangspunkt vorgegeben
		wObj->GetPointOnObject (&lXA, &lYA, &lIndA, &bPA);
	else						// kein Anfangspunkt vorgegeben
	{
		lIndA = 0;
		bPA = true;
		lXA = plXK [0];
		lYA = plYK [0];
	}

	if (lXE > 0 && lYE > 0)		// Endpunkt vorgegeben
		wObj->GetPointOnObject (&lXE, &lYE, &lIndE, &bPE);
	else						// kein Endpunkt vorgegeben
	{
		if (OT_KANTE == iOT)
			lIndE = lAnz - 1;		// höchster Stützpunktindex der Kante
		else
			lIndE = plK[0] - 1;		// höchster Stützpunktindex der Außenkontur

		bPE = true;		// Endpunkt (lXE,lYE) ist der letzten Stützpunkt der Kante bzw. der
						// Außenkontur
		lXE = plXK [lIndE];
		lYE = plYK [lIndE];
	}

	_ASSERTE (lIndA != lIndE);


	// den Nachbarindex lNextInd (vorhergehenden bzw. nachfolgenden) von lIndA ermitteln; wenn
	// wObj eine Fläche ist, ist noch ein Vortest erforderlich
	if (OT_FLAECHE == iOT)
	{
	// testen, zu welcher wObj-Kontur der Punkt mit dem Index lIndA gehört
	short iKInd;	// Index der Kontur, zu der der Anfangsindex lIndA gehört
	long lIndex;	// für Routine IndexTest(); wird hier nicht ausgewertet
	IndPos IP;		// für Routine IndexTest(); wird hier nicht ausgewertet

		wObj->IndexTest (lIndA, &iKInd, &lIndex, &IP);
		lAnz = plK[iKInd];
		for (int i = 0; i < iKInd; i++) 
			lFirstInd += plK[i]; 
	}

long lNextInd;		// bei MD == MOVEDIR_UP:   der auf lIndA folgende Index
					// bei MD == MOVEDIR_DOWN: der lIndA vorangehende Index

	if (MOVEDIR_UP == MD)
	{
		if (lIndA < lAnz-1) lNextInd = lIndA + 1;
		else
		{
			_ASSERTE (iOT == OT_FLAECHE);
			lNextInd = lFirstInd + 1;
		}
	}
	else
	{		
		if (lIndA > lFirstInd) lNextInd = lIndA - 1;
		else
		{
			_ASSERTE (iOT == OT_FLAECHE);
			lNextInd = lFirstInd + lAnz - 2;
		}
	}


// zu verschiebende Kante aus den wObj-Stützpunkten aufbauen
WObjektGeometrie wMoveObj;	// ObjektGeometrie der zu verschiebenden Kante
					
	try
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

	// ... initialisieren
		// Abstand zwischen Anfangspunkt (lXA,lYA) und dem 1. zu übernehmenden Stützpunkt
		// (plXK[lNextInd],plYK[lNextInd]) ist > lEps, dann mit (lXA,lYA) beginnen sonst mit
		// (plXK[lIndA],plYK[lIndA]) bzw. (plXK[lNextInd],plYK[lNextInd])
		if (! bPA &&
			(labs (lXA-plXK[lNextInd]) > lEps || labs (lYA-plYK[lNextInd]) > lEps))
			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lXA, lYA, OT_KANTE))
		else
		{
			if (bPA)
				THROW_FAILED_HRESULT (wIObj->InitObjGeometry (plXK[lIndA], plYK[lIndA], OT_KANTE))
			else
			{
				THROW_FAILED_HRESULT (wIObj->InitObjGeometry (plXK[lNextInd], plYK[lNextInd], OT_KANTE));
				if (MOVEDIR_UP == MD)
				{
					if (lNextInd < lAnz-1) lNextInd++;
					else
					{
						_ASSERTE (iOT == OT_FLAECHE);
						lNextInd = lFirstInd + 1;
					}
				}
				else
				{
					if (lNextInd > lFirstInd) lNextInd--;
					else
					{
						_ASSERTE (iOT == OT_FLAECHE);
						lNextInd = lFirstInd + lAnz - 2;
					}
				}
			}
		}

		wMoveObj = wIObj;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	wMoveObj->AddKantenTeil (wObj, lNextInd, lIndE, MD);

	// Abstand zwischen Endpunkt (lXE,lYE) und dem letzten Stützpunkt > lEps, dann (lXE,lYE)
	// noch hinzunehmen
	if (labs (lXE-plXK [lIndE]) > lEps || labs (lYE-plYK [lIndE]) > lEps)
		wMoveObj->AddPunkt (lXE, lYE, -1, -1);


long lCntM;	// Stützpunktanzahl von wMoveObj
KoOrd* plXM; KoOrd* plYM;

	wMoveObj->GetCnt (&lCntM);
	wMoveObj->GetX ((void**)&plXM);
	wMoveObj->GetY ((void**)&plYM);


// Lotpunkt LP des Bezugspunktes BPkt (lXB,lYB) auf wMoveObj bestimmen; daraus ergibt sich der
// Abstand für die Verschiebung 
EPunkt BPkt (lXB, lYB);	// Bezugspunkt
KoOrd lMinAbst = LONG_MAX;	// kleinster Abstand von BPkt zu den Strecken des wMoveObj-Objektes
KoOrd lAbst;	// Abstand von Strecke Str (in for-Schleife)
EPunkt LPkt;		// Lotpunkt von BPkt auf die wMoveObj-Strecken mit lMinAbst
EPunkt LP;		// Lotpunkt von BPkt auf eine wMoveObj-Strecke

	for (long i = 0; i < lCntM-1; i++)
	{
	EPunkt P1 (plXM[i], plYM[i]);
	EPunkt P2 (plXM[i+1], plYM[i+1]);
	Strecke Str (P1, P2);

		if (Str.LotPktStrecke (BPkt, lAbst, LP) &&	// lAbst gilt echt für die Strecke Str (nicht
			lAbst < lMinAbst)						//  für deren Trägergerade)
		{
			lMinAbst = lAbst;
			LPkt = LP;
		}

		if (0 == lMinAbst)	// BPkt liegt auf der Strecke Str, d.h. Routine wird beendet
			return E_INVALIDARG;	// keine Verschiebung möglich
	}

	// Lotpunkt ließ sich auf keine der wMoveObj-Strecken fällen, deshalb Lotpunkt auf die
	// Trägergeraden der 1. bzw. letzten Strecke ermitteln
	if (LONG_MAX == lMinAbst)
	{
	EPunkt P1 (plXM[0], plYM[0]);
	EPunkt P2 (plXM[1], plYM[1]);
	Strecke Str (P1, P2);

		// Lot auf die Trägergerade der 1. wMoveObj-Strecke
		Str.LotPktStrecke (BPkt, lAbst, LP);
		if (0 == lAbst)
			return E_INVALIDARG;	// keine Verschiebung möglich

		if (lAbst < lMinAbst)
		{
			lMinAbst = lAbst;
			LPkt = LP;
		}

		Str.AP().X() = plXM[lCntM-2];
		Str.AP().Y() = plYM[lCntM-2];
		Str.EP().X() = plXM[lCntM-1];
		Str.EP().Y() = plYM[lCntM-1];

		// Lot auf die Trägergerade der letzten wMoveObj-Strecke
		Str.LotPktStrecke (BPkt, lAbst, LP);
		if (0 == lAbst)
			return E_INVALIDARG;	// keine Verschiebung möglich

		if (lAbst < lMinAbst)
		{
			lMinAbst = lAbst;
			LPkt = LP;
		}
	}

	_ASSERTE (lMinAbst < LONG_MAX);


// Verschiebung bzgl. des Bezugspunktes
KoOrd xv = lXB - LPkt.X();
KoOrd yv = lYB - LPkt.Y();

	for (i = 0; i < lCntM; i++)
	{
	KoOrd x = plXM[i] + xv;
	KoOrd y = plYM[i] + yv;

		wMoveObj->ModPunkt (x, y, i);
	}

// zu verschiebendes Objekt evtl. noch am Anfang und/oder Ende verlängern
	if (bVerlA)
		LineElongation (wMoveObj, true, lXMin, lYMin, lXMax, lYMax);

	if (bVerlE)
		LineElongation (wMoveObj, false, lXMin, lYMin, lXMax, lYMax);

ulong ulIdent;

	wObj->GetIdent (&ulIdent);
	wMoveObj->SetIdent (ulIdent);
	// OGNewObject:     permanentes Objekt in Datenbank aufnehmen
	// OGForceGeoError: Objekt wird bei Geometriefehler von GEOREIN abgewiesen
	// OGForceGeometry: auch außerhalb des aktuellen Projekt-Containers speichern
	//                  (aus Rundungsgründen)
	wMoveObj->SetFlags (OGNewObject | OGForceGeoError | OGForceGeometry);

#if _TRiAS_VER < 0x0300
HRESULT hr = wMoveObj->GeometrieAnTRiAS (true, NULL);
#else
INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));
HRESULT hr = wMoveObj->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300

	// wenn Objekt in DB eingespeichert wurde, dann Objektname und UniqueIdent vergeben
	if (S_OK == hr)
	{
		wMoveObj->GetONr (plONr);

	string sONText, sUIText;	// Merkmalstexte für Objektname bzw. UniqueIdent
	ResString resShLine (ResID (IDS_SHIFTEDLINE, pRF), 100);

		Format (sONText, (char*)resShLine.Addr(), lONr);
		WriteFeatureText (*plONr, DEX_GetObjNameMCode (ulIdent), TT_Objekt, sONText);

	ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sUIText, (char*)resText.Addr(), *plONr);
#if _TRiAS_VER < 0x0300
		WriteFeatureText (*plONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIText);
#else
		WriteFeatureText (*plONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(*plONr)),
						  TT_Objekt, sUIText);
#endif // _TRiAS_VER < 0x0300
	}

	return S_OK;

} // LinienVerschiebung_ONr


// --------------------------------------------------------------------------------------------
// Verlängerung des linienförmigen pIOG-Objektes am Anfang (bAnf = true) bzw. am Ende
// (bAnf = false) bis zum Rand des vorgegebenen Rechteckes (lXMin, YMin, lXMax, lYMax)
bool ObjektOpExtension::LineElongation (IObjektGeometrie* pIOG, bool bAnf, KoOrd lXMin,
										KoOrd lYMin, KoOrd lXMax, KoOrd lYMax)
{
	_ASSERTE (pIOG != NULL);

ObjRechteck PC;	// Projekt-Container

	DEX_GetProjectCont (PC);

	if (0 == lXMin || lXMin < PC.XMin())
		lXMin = PC.XMin();
	if (0 == lYMin || lYMin < PC.YMin())
		lYMin = PC.YMin();
	if (0 == lXMax || lXMax > PC.XMax())
		lXMax = PC.XMax();
	if (0 == lYMax || lYMax > PC.YMax())
		lYMax = PC.YMax();

long lCnt;				// Stützpunktanzahl von pIOG
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lCnt);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

KoOrd x2, y2;	// Koordinaten des 1. bzw. letzten pIOG-Punktes
KoOrd x1, y1;	// Koordinaten des 2. bzw. vorletzten pIOG-Punktes
double a, b, c;	// Parameter für allgemeine Gleichung ax+by+c=0 der Trägergeraden
long lMInd;		// Index des zu modifizierenden Stützpunktes bei Verlängerung

// Verlängerung am Anfang
	if (bAnf)
	{
		lMInd = 0;
		x2 = plXK[lMInd];
		y2 = plYK[lMInd];

	long i = lMInd + 1;

		do
		{
			x1 = plXK[i];
			y1 = plYK[i];
			a = y2 - y1;
			b = x1 - x2;
			i++;
		}
		while ((0 == a && 0 == b) && i < lCnt);

		_ASSERTE (i < lCnt);

		if (i == lCnt)
			return false;

		c = -y1*b - x1*a;
	}

// Verlängerung am Ende
	else
	{
		lMInd = lCnt - 1;
		x2 = plXK[lMInd];
		y2 = plYK[lMInd];

	long i = lMInd - 1;

		do
		{
			x1 = plXK[i];
			y1 = plYK[i];
			a = y2 - y1;
			b = x1 - x2;
			i--;
		}
		while ((0 == a && 0 == b) && i >= 0);

		_ASSERTE (i >= 0);

		if (i < 0)
			return false;

		c = -y1*b - x1*a;
	}


	// schneidet die Trägergerade ax+by+c=0 eine der senkrechten Containerseiten?
	if (b != 0)		// Trägergerade nicht senkrecht
	{
		// schneidet die Trägergerade ax+by+c=0 die linke Containerseite?
		if (lXMin < x2 && x2 < x1)
		{
		KoOrd y = DtoL ((-a*lXMin - c) / b);

			if (lYMin <= y && y <= lYMax)	// ja
			{
				pIOG->ModPunkt (lXMin, y, lMInd);
				return true;
			}
		}

		// schneidet die Trägergerade die rechte Containerseite?
		if (lXMax > x2 && x2 > x1)
		{
		KoOrd y = DtoL ((-a*lXMax - c) / b);

			if (lYMin <= y && y <= lYMax)	// ja
			{
				pIOG->ModPunkt (lXMax, y, lMInd);
				return true;
			}
		}
	}
	else		// Trägergerade senkrecht, d.h. Schnitt mit linker bzw. rechter
				// Containerseite nicht möglich
	{
		if (x1 < lXMin || x1 > lXMax)	// Trägergerade außerhalb des Containers
			return false;	// E_INVALIDARG
	}

	// schneidet die Trägergerade ax+by+c=0 eine der waagerechten Containerseiten?
	if (a != 0)		// Trägergerade nicht waagerecht
	{
		// schneidet die Trägergerade ax+by+c=0 die obere Containerseite?
		if (lYMax > y2 && y2 > y1)
		{
		KoOrd x = DtoL ((-b*lYMax - c) / a);

			if (lXMin <= x && x <= lXMax)	// ja
			{
				pIOG->ModPunkt (x, lYMax, lMInd);
				return true;
			}
		}

		// schneidet die Trägergerade die untere Containerseite?
		if (lYMin < y2 && y2 < y1)
		{
		KoOrd x = DtoL ((-b*lYMin - c) / a);

			if (lXMin <= x && x <= lXMax)	// ja
			{
				pIOG->ModPunkt (x, lYMin, lMInd);
				return true;
			}
		}
	}
	else		// Trägergerade senkrecht, d.h. Schnitt mit oberer bzw. unterer
				// Containerseite nicht möglich
	{
		if (y1 < lYMin || y1 > lYMax)	// Trägergerade außerhalb des Containers
			return false;	// E_INVALIDARG
	}

	return true;

} // LineElongation
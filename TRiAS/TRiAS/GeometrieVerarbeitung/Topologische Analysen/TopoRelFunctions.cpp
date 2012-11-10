// Funktionalität für Topologische Relationen
// File: TopoRelFunctions.cpp
// W. Mörtl


#include "TopoRelP.hxx"

#include "FormatString.hxx"		// Format()

#include "SmartInterfaces.h"	// WExtendGeoRein
#include "DatBank.hxx"			// FehlerhaftesObjekt()
#include "GeoTrias.hxx"			// EObjektErzeugen()

#include "TopoRel.hxx"			// TopoRelatExtension
#include "TopoRelFunctions.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// Relation des lONr-Objektes bezüglich des Bezugsobjektes
BOOL CALLBACK GetObjRelat (long lONr, BOOL, void*)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);
	_ASSERTE (NULL != g_pTE);

	return ((TopoRelatExtension*)g_pTE)->GetRelFunctions()->GetObjectRelation (lONr);
}


//---------------------------------------------------------------------------------------------
// Anzahl der Objekte des Identifikators ulIdent ermitteln
BOOL CALLBACK CountObjectsOfAClass (ulong ulIdent, BOOL, void* pvAnz)
{
	_ASSERTE (0 != ulIdent);
	_ASSERTE ((ulong)-1 != ulIdent);

// Anzahl der Objekte des Identifikators ulIdent ohne Berücksichtigung der Objekttypen ermitteln
IDENTOBJECTCOUNT IOC;

	INITSTRUCT (IOC, IDENTOBJECTCOUNT);
	IOC.ulIdent = ulIdent;
	IOC.iOTypes = OTPunkt | OTLinie | OTFlaeche | OTText;	// alle Objekttypen
	*(long*)pvAnz += DEX_GetIdentObjectCount (IOC);

	return true;
}


//---------------------------------------------------------------------------------------------
// Zählen von Objekten außer dem Bezugsbjekt und Rückgabe in pvAnz
BOOL CALLBACK CountObjects (long lONr, BOOL, void* pvAnz)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);
	_ASSERTE (NULL != g_pTE);

long lRefONr = ((TopoRelatExtension*)g_pTE)->GetRelFunctions()->GetRefONr();

	if (lRefONr != lONr)
		(*(long*)pvAnz)++;

	return true;
}


//---------------------------------------------------------------------------------------------
// Test, ob lONr-Objekt schon in einer der Objektnummern-Bäume enthalten ist
BOOL CALLBACK IsObjNumberInTree (long lONr, DWORD, void*)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);
	_ASSERTE (NULL != g_pTE);

	return ((TopoRelatExtension*)g_pTE)->GetRelFunctions()->IsObjectInTree (lONr);
}


//---------------------------------------------------------------------------------------------
// Objektnummern aller Objekte des Identifikators ulIdent bereitstellen
BOOL CALLBACK GetObjNumbersOfAClass (ulong ulIdent, BOOL, void*)
{
	_ASSERTE (0 != ulIdent);
	_ASSERTE ((ulong)-1 != ulIdent);

ENUMLONGKEYEX ELK;

	ELK.eKey = ulIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC) IsObjNumberInTree;
	ELK.eData = OTPunkt | OTLinie | OTFlaeche | OTText;	// alle Objekttypen
	return DEX_EnumIdentObjectsEx (ELK);
}



///////////////////////////////////////////////////////////////////////////////////////////////
TopoRelFunc::TopoRelFunc (void)
{
	// Member initialisieren
	m_ulSelRelat = WITH;	// ausgewählte Relation: innerhalb (default-Wert)
	m_bSepaWin = true;		// Analyseergebnisse in getrennten Recherchefenstern anzeigen (default-Wert)
	m_pRefObj = NULL;		// aktuelles Bezugsobjekt
	m_lRefONr = -1;			// Objektnummer des aktuellen Bezugsobjektes
	m_bGeoRein = false;		// Ankopplung von GeoRein.ext über Interface noch nicht erfolgt
}


// --------------------------------------------------------------------------------------------
TopoRelFunc::~TopoRelFunc (void)
{
	DELETE_OBJ (m_pRefObj);
	
    // Interface's wieder freigeben
    m_wGeoRein.Assign (0);
}





///////////////////////////////////////////////////////////////////////////////////////////////
// Funktionen

// --------------------------------------------------------------------------------------------
// Vorarbeiten für die topologische Analyse
HRESULT TopoRelFunc::PrepareAnalysis (InEnumLONG RefObject, TOPORELRESULT caRelationInfo,
									  MULTIREFRESULT caMultiRefInfo, bool bFirstRelObj)
{
long lRefONr = *RefObject;	// Objektnummer des Referenzobjektes

	SetRefONr (lRefONr);

	GeoReinInterface();

	if (S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lRefONr)) {
	ResourceFile RF (g_pDLLName);
	string sText;
	ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
	ResString resText (ResID (IDS_GEOFEHL1, &RF), 200);

		Format (sText, (char*)resText.Addr(), lRefONr);
		MessageBox (__hWndM, sText.c_str(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return S_FALSE;
	}
		
	if (! BuildReferenceObject())
		return S_FALSE;

	m_ulSelRelat = caRelationInfo.ulSelRelat;
	m_bSepaWin = caRelationInfo.bSepaWin;
	m_iReferenceType = caMultiRefInfo.iReferenceType;
	m_lLimitCnt = caMultiRefInfo.lLimitCnt;

	m_bFirstRelObj = bFirstRelObj;

	return S_OK;

} // PrepareAnalysis


// -----------------------------------------------------------------------------------------------
// Bezugsobjekt aufbauen
bool TopoRelFunc :: BuildReferenceObject (void)
{
	if (EObjektErzeugen (m_lRefONr, m_pRefObj, &m_CTX))
	{     
		m_iRefOT = m_pRefObj->isA();	// Objekttyp

		if (OT_PUNKT == m_iRefOT)
			m_RefOC = ((EPunkt*)m_pRefObj)->GetCont();
		else if (OT_KANTE == m_iRefOT)
			m_RefOC = ((EKante*)m_pRefObj)->GetCont();
		else if (OT_FLAECHE == m_iRefOT)
			m_RefOC = ((EFlaeche*)m_pRefObj)->GetCont();
		else
		{
			_ASSERTE (OT_PUNKT == m_iRefOT || OT_KANTE == m_iRefOT || OT_FLAECHE == m_iRefOT);
			return false;
		}

		return true;
	}

	return false;

} // BuildReferenceObject


// --------------------------------------------------------------------------------------------
// Relation des lONr-Objektes bezüglich des Bezugsobjektes bestimmen
bool TopoRelFunc :: GetObjectRelation (long lONr)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

	if (lONr == m_lRefONr)	// kein Test mit "sich selbst"
		return true;

int iOT = DEX_GetObjectType (lONr);

// "Außerhalb"-Schnelltest
long lCO[4];	// Container-Koordinaten des aktuellen lONr-Objektes

	DEX_GetObjContainer (lONr, lCO);
	if (lCO[1] < m_RefOC.XMin() || lCO[0] > m_RefOC.XMax() ||
		lCO[3] < m_RefOC.YMin() || lCO[2] > m_RefOC.YMax())
	{
		m_OGCRelat = DISJOINT;
		StoreObjectNumber (lONr);
		return true;
	}


EObjekt* pEO = NULL;	// zu testendes Objekt

	// Test auf Geometriefehler
	if (m_bFirstRelObj && (OT_KANTE == iOT || OT_FLAECHE == iOT)) {
	// auf Geometriefehler prüfen
		GeoReinInterface();
 		if (S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr, &m_CTX, &pEO)) {
		// für Objekte, die nicht vollständig außerhalb des Containers des 
		// Bezugsobjektes liegen ist die Ermittlung der topologischen 
		// Relation nicht möglich
			StoreObjectNumber (lONr);
			return true;	// durch "true" wird Abarbeitung nach Fehlermeldung nicht abgebrochen
		}
	}

	if (NULL == pEO && !EObjektErzeugen (lONr, pEO, &m_CTX)) {
	// Fehler beim erzeugen des EObjekt's
		DELETE_OBJ (pEO);
		return false;
	}
		
Posit posLage;	// Relation des zu testenden Objektes; wird an dieser Stelle nicht ausgewertet,
				// da das Ergebnis im Member m_OGCRelat abgelegt und von dort durch die
				// Routine StoreObjectNumber() ausgewertet wird

	Relations (pEO, posLage);
	DELETE_OBJ (pEO);
	
	StoreObjectNumber (lONr);
	
	return true;

} // GetObjectRelation


// --------------------------------------------------------------------------------------------
// Relationen des Elementarobjektes pEO (Objekttyp iOT) bez. des Bezugsobjektes m_pRefObj
// bestimmen und in Parameter posLage zurückgeben
void TopoRelFunc :: Relations (EObjekt* pEO, Posit& posLage)
{
	_ASSERTE (NULL != pEO);

	if (! pEO)
	{
		DEX_Error (RC_Relationen, EC_ILLPARS);
		return;
	}

ObjTyp iOT = pEO->isA();	// Objekttyp des zu testenden Objektes

	if (IsOutside (pEO, iOT, posLage))
		return;
	
	switch (m_iRefOT)
	{
		case OT_PUNKT:		// Bezugsobjekt ist Punkt
			switch (iOT)
			{
				case OT_PUNKT:
					if (*(EPunkt*)m_pRefObj == *(EPunkt*)pEO)
						posLage = GLEICH;
					else posLage = AUSSERH;
					break;
			
				case OT_KANTE:
					// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: Wie
					// liegt die pEO-Kante bez. des m_pRefObj-Punktes? Dafür habe ich aber keine
					// Routine.
					posLage = ((EPunkt*)m_pRefObj)->PunktAufKante ((EKante*)pEO);
					if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
						posLage = UMSCHLB;	// Ergebnis von PunktAufKante() modifiziert werden
					else if (KONTUR == posLage)
						posLage = AUSSERHB;
					break;

				case OT_FLAECHE:
					// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: Wie
					// liegt die pEO-Fläche bez. des m_pRefObj-Punktes? Dafür habe ich aber keine
					// Routine.
					posLage = ((EPunkt*)m_pRefObj)->EnthaltenIn ((EFlaeche*)pEO);
					if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
						posLage = UMSCHL;	// Ergebnis von EnthaltenIn() modifiziert werden
					else if (KONTUR == posLage)
						posLage = AUSSERHB;
					break;
			}

			TRiAStoOGCRelations (pEO, posLage);
			break;
			

		case OT_KANTE:		// Bezugsobjekt ist Kante
			switch (iOT)
			{
				case OT_PUNKT:
					posLage = ((EPunkt*)pEO)->PunktAufKante ((EKante*)m_pRefObj);
					TRiAStoOGCRelations (pEO, posLage);
					break;
			
				case OT_KANTE:
				{
					m_OGCRelat = ((EKante*)pEO)->LinesLocation ((EKante*)m_pRefObj);
					posLage = OGCtoTRiASRelations (m_OGCRelat);
					break;
				}

				case OT_FLAECHE:
					// eigentlich müßte nachfolgend die umgekehrte Frage gestellt werden: Wie
					// liegt die pEO-Fläche bez. der m_pRefObj-Kante? Dafür habe ich aber keine
					// Routine.
					posLage = ((EKante*)m_pRefObj)->EnthaltenIn ((EFlaeche*)pEO);
					if (INNERH == posLage)	// weil ich besagte Routine nicht habe, muß das
						posLage = UMSCHL;	// Ergebnis von EnthaltenIn() modifiziert werden
					else if (INNERHB == posLage)
						posLage = UMSCHLB;
					else if (KONTUR == posLage)
						posLage = AUSSERHB;
					else if (UMSCHL == posLage)
						posLage = AUSSERH;
					else if (UMSCHLB == posLage)
						posLage = AUSSERHB;
					TRiAStoOGCRelations (pEO, posLage);
					break;
			}
			break;
			

		case OT_FLAECHE:	// Bezugsobjekt ist Fläche
			switch (iOT)
			{
				case OT_PUNKT:
					posLage = ((EPunkt*)pEO)->EnthaltenIn ((EFlaeche*)m_pRefObj);
					break;
			
				case OT_KANTE:
					posLage = ((EKante*)pEO)->EnthaltenIn ((EFlaeche*)m_pRefObj);
					break;

				case OT_FLAECHE:
					posLage = ((EFlaeche*)pEO)->EnthaltenIn ((EFlaeche*)m_pRefObj);
					break;
			}

			TRiAStoOGCRelations (pEO, posLage);
			break;

		default:
			_ASSERTE (false);
			posLage = UNKLAR;
			break;
	}
	
	// die Fälle "auf der Kontur liegend" bzw. "völlig identisch" werden nachfolgend nicht
	// gesondert ausgewertet
	if (KONTUR == posLage || GLEICH == posLage)
		posLage = INNERHB;
	
} // Relations


// --------------------------------------------------------------------------------------------
// Test ob das pEO-Objekt ganz sicher außerhalb des Bezugsobjektes liegt mittels Vergleich der 
// Objekt-Container
bool TopoRelFunc :: IsOutside (EObjekt* pEO, ObjTyp iOT, Posit& posLage)
{
ObjRechteck OC;	// Container des zu testenden Objektes

	if (OT_PUNKT == iOT)
		OC = ((EPunkt*)pEO)->GetCont();
	else if (OT_KANTE == iOT)
		OC = ((EKante*)pEO)->GetCont();
	else if (OT_FLAECHE == iOT)
		OC = ((EFlaeche*)pEO)->GetCont();
	else
	{
		_ASSERTE (OT_PUNKT == iOT || OT_KANTE == iOT || OT_FLAECHE == iOT);
		return false;
	}

	if (! m_RefOC.Durchschnitt(OC))
	{
		posLage = AUSSERH;
		m_OGCRelat = DISJOINT;
		return true;
	}

	return false;
} // IsOutside


// --------------------------------------------------------------------------------------------
// Konvertierung der TRiAS-Relationen in die OGC-Relationen
void TopoRelFunc :: TRiAStoOGCRelations (EObjekt* pEO, Posit posLage)
{
	if (AUSSERH == posLage)	
	{
		m_OGCRelat = DISJOINT;
		return;
	}

	if (AUSSERHB == posLage || KONTUR == posLage)
	{
		m_OGCRelat = TOUCH;
		return;
	}

	if (UMSCHL == posLage || UMSCHLB == posLage)
	{
		m_OGCRelat = CONTAIN;
		return;
	}

	if (INNERH == posLage)
	{
		m_OGCRelat = WITHIN;
		return;
	}

	if (GLEICH == posLage)
	{
		m_OGCRelat = EQUAL;
		return;
	}

	_ASSERTE (NULL != pEO);

	if (! pEO)
	{
		DEX_Error (RC_Relationen, EC_ILLPARS);
		return;
	}
	
ObjTyp iOT = pEO->isA();	// Objekttyp des zu testenden Objektes

	switch (m_iRefOT)
	{
		case OT_PUNKT:		// Bezugsobjekt ist Punkt
			switch (iOT)
			{
				case OT_PUNKT:
					m_OGCRelat = UNCLEAR;
					break;

				case OT_KANTE:
					_ASSERTE (AUSSERH == posLage || AUSSERHB == posLage || UMSCHLB == posLage);
					m_OGCRelat = UNCLEAR;
					break;

				case OT_FLAECHE:
					_ASSERTE (AUSSERH == posLage || AUSSERHB == posLage || UMSCHL == posLage);
					m_OGCRelat = UNCLEAR;
					break;
			}
			break;

			
		case OT_KANTE:		// Bezugsobjekt ist Kante
			switch (iOT)
			{
				case OT_PUNKT:
					m_OGCRelat = UNCLEAR;
					break;
			
				case OT_KANTE:
					// dieser Programmzweig dürfte gar nicht erreicht werden, da bei der
					// Kombination Kante/Kante zuerst mit LinesLocation() die OGC-Relation
					// ermittelt wird und daraus mit OGCtoTRiASRelations() die TRiAS-Relation
					_ASSERTE (false);
					break;

				case OT_FLAECHE:
					if (INNAUSS == posLage)
						m_OGCRelat = ENTER;
					else
					{
						_ASSERTE (INNAUSS == posLage);
						m_OGCRelat = UNCLEAR;
					}
					break;
			}
			break;
			

		case OT_FLAECHE:	// Bezugsobjekt ist Fläche
			switch (iOT)
			{
				case OT_PUNKT:
					m_OGCRelat = UNCLEAR;
					break;
			
				case OT_KANTE:
					if (INNERHB == posLage)
						m_OGCRelat = WITHIN;
					else if (INNAUSS == posLage)
						m_OGCRelat = ENTER;
					else
					{
						_ASSERTE (INNERHB == posLage || INNAUSS == posLage);
						m_OGCRelat = UNCLEAR;
					}
					break;

				case OT_FLAECHE:
					if (INNERHB == posLage)
						m_OGCRelat = WITHIN;
					else if (INNAUSS == posLage)
						m_OGCRelat = OVERLAP;
					else
					{
						_ASSERTE (INNAUSS == posLage || INNERHB == posLage);
						m_OGCRelat = UNCLEAR;
					}
					break;
			}
			break;

		default:
			_ASSERTE (false);
			m_OGCRelat = UNCLEAR;
			break;
	}

} // TRiAStoOGCRelations


// --------------------------------------------------------------------------------------------
// Konvertierung der OGC-Relationen in die TRiAS-Relationen
Posit TopoRelFunc :: OGCtoTRiASRelations (OGCPosit ogsLage)
{
	if (DISJOINT == ogsLage)
		return AUSSERH;

	if (WITHIN == ogsLage)
		return INNERH;

	if (EQUAL == ogsLage)
		return GLEICH;

	if (CONTAIN == ogsLage)
		return UMSCHL;

	if (TOUCH == ogsLage)
		return AUSSERHB;

	if (ENTER == ogsLage || OVERLAP == ogsLage)
		return INNAUSS;

	_ASSERTE (false);
	return UNKLAR;

} // OGCtoTRiASRelations


// --------------------------------------------------------------------------------------------
// Objektnummern entsprechend der ermittelten Relation in die dafür vorgesehenen Bäume
// eintragen; die "außerhalb" liegenden Objekte werden in Routine IsObjectInTree() behandelt
void TopoRelFunc :: StoreObjectNumber (long lONr)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

	switch (m_OGCRelat)
	{
		case WITHIN:
			// Eigentlich wäre es sinnvoller, InsertK() auch bei m_bSepaWin == true (und nicht
			// nur bei m_bSepaWin == false) davon abhängig zu machen, ob die Auswahl entsprechend
			// m_ulSelRelat überhaupt gewünscht wird. Da aber die Routine IsObjectInTree()
			// testet, ob das lONr-Objekt schon in einem der Bäume vorhanden sein müsste, wird
			// InsertK() bei m_bSepaWin == true immer ausgeführt.
			m_ONrWithin.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&		// nur das gemeinsame Recherchefenster
				(m_ulSelRelat & WITH))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case CONTAIN:
			m_ONrContain.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & CONT))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case OVERLAP:
			m_ONrOverlap.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & OVER))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case ENTER:
			m_ONrEnter.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & ENTE))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case TOUCH:
			m_ONrTouch.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & TOUC))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case EQUAL:
			m_ONrEqual.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & EQUA))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case DISJOINT:
			m_ONrDisjoint.InsertK (lONr, m_lRefObjCount);
			if (! m_bSepaWin &&
				(m_ulSelRelat & DISJ))
				m_ONrRelat.InsertK (lONr, m_lRefObjCount);
			break;

		case UNCLEAR:
			m_ONrUnclear.InsertK (lONr, m_lRefObjCount);
			break;
	}
} // StoreObjectNumber


// --------------------------------------------------------------------------------------------
// Testen der Zusatz-Info's bei mehreren Bezugsobjekten; bei Erfüllung, Rückgabe von true
bool TopoRelFunc :: IsMultiRefCondition (long lFrequencyCnt)
{
	switch (m_iReferenceType)
	{
		case All:
			if (lFrequencyCnt == m_lRefObjCount)
				return true;
			break;

		case Least:
			if (lFrequencyCnt >= m_lLimitCnt)
				return true;
			break;

		case Most:
			if (lFrequencyCnt <= m_lLimitCnt)
				return true;
			break;

		case Exact:
			if (lFrequencyCnt == m_lLimitCnt)
				return true;
	}

	return false;

} // IsMultiRefCondition


// --------------------------------------------------------------------------------------------
// Übertragen der Objektnummern aus dem ONrTree-Baum nach pOutput
void TopoRelFunc :: TransferResults (int iRel, ObjNrBaum& ONrTree, IEnumLONG* pOutput)
{
	if (m_ulSelRelat & iRel && ONrTree.Count() > 0)
	{
	ObjNrBaumTable t (ONrTree);

		for (t.First(); t.Valid(); t.Next())
		{
		ObjNrKnotenLock kl (t);

			if (kl && IsMultiRefCondition (kl->GetCounter()))
				((IEnum<LONG>*)pOutput)->AddItem (kl->GetONr());
		}
	}
} // TransferResults


// --------------------------------------------------------------------------------------------
// Testen, ob unter den Bedingungen mehrerer Bezugsobjekte Daten aus dem ONrTree-Baum
// auszugeben sind
bool TopoRelFunc :: IsTreeContentValid (int iRel, ObjNrBaum& ONrTree)
{
	if (m_ulSelRelat & iRel && ONrTree.Count() > 0)
	{
	ObjNrBaumTable t (ONrTree);

		for (t.First(); t.Valid(); t.Next())
		{
		ObjNrKnotenLock kl (t);

			if (kl && IsMultiRefCondition (kl->GetCounter()))
				return true;
		}
	}
	
	return false;

} // IsTreeContentValid


// --------------------------------------------------------------------------------------------
// Anzahl der Ausgabeströme ermitteln
void TopoRelFunc :: CountPackets (long& lPacket)
{
	lPacket = 0;

	if (m_bSepaWin)
	{

		if (IsTreeContentValid (WITH, m_ONrWithin))
			lPacket++;
		if (IsTreeContentValid (EQUA, m_ONrEqual))
			lPacket++;
		if (IsTreeContentValid (OVER, m_ONrOverlap))
			lPacket++;
		if (IsTreeContentValid (ENTE, m_ONrEnter))
			lPacket++;
		if (IsTreeContentValid (CONT, m_ONrContain))
			lPacket++;
		if (IsTreeContentValid (DISJ, m_ONrDisjoint))
			lPacket++;
		if (IsTreeContentValid (TOUC, m_ONrTouch))
			lPacket++;
	}
	else if (IsTreeContentValid (0xFF, m_ONrRelat))
		lPacket = 1;

	if (IsTreeContentValid (0xFF, m_ONrUnclear))
	{
	ResourceFile RF (g_pDLLName);
    ResString resText (ResID (IDS_WITHGEOMETRYERRORS, &RF), 250);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, &RF), 50);
	
		if (IDYES == MessageBox (__hWndM, resText.Addr(), resCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
			lPacket++;
		else
			m_ONrUnclear.EveryDelete();
	}

}  // CountPackets


// --------------------------------------------------------------------------------------------
// Ausgabestrom zusammenstellen
void TopoRelFunc :: BuildOutputObjects (IEnumLONG* pEnumOut, CComBSTR& bstrCapt,
										CComBSTR& bstrColor, OGCPosit& rgPosition)
{
ResourceFile RF (g_pDLLName);
	
	bstrCapt = ResString (ResID (IDS_LONGCLASSNAME, &RF), 40);	// Fensterüberschrift
	bstrColor = cDefaultColor;									// Farbe
	rgPosition = UNCLEAR;										// topologische Relation


	if (m_bSepaWin)
	{
		if ((m_ulSelRelat & WITH) && m_ONrWithin.Count())
		{
			TransferResults (WITH, m_ONrWithin, pEnumOut);
			m_ONrWithin.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSWITHIN, &RF), 40);
			bstrColor = cWithinColor;
			rgPosition = WITHIN;
		}
		else if ((m_ulSelRelat & CONT) && m_ONrContain.Count())
		{
			TransferResults (CONT, m_ONrContain, pEnumOut);
			m_ONrContain.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSCONTAIN, &RF), 40);
			bstrColor = cContainColor;
			rgPosition = CONTAIN;
		}
		else if ((m_ulSelRelat & OVER) && m_ONrOverlap.Count())
		{
			TransferResults (OVER, m_ONrOverlap, pEnumOut);
			m_ONrOverlap.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSOVERLAP, &RF), 40);
			bstrColor = cOverlapColor;
			rgPosition = OVERLAP;
		}
		else if ((m_ulSelRelat & ENTE) && m_ONrEnter.Count())
		{
			TransferResults (ENTE, m_ONrEnter, pEnumOut);
			m_ONrEnter.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSENTER, &RF), 40);
			bstrColor = cEnterColor;
			rgPosition = ENTER;
		}
		else if ((m_ulSelRelat & TOUC) && m_ONrTouch.Count())
		{
			TransferResults (TOUC, m_ONrTouch, pEnumOut);
			m_ONrTouch.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSTOUCH, &RF), 40);
			bstrColor = cTouchColor;
			rgPosition = TOUCH;
		}
		else if ((m_ulSelRelat & EQUA) && m_ONrEqual.Count())
		{
			TransferResults (EQUA, m_ONrEqual, pEnumOut);
			m_ONrEqual.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSEQUAL, &RF), 40);
			bstrColor = cEqualColor;
			rgPosition = EQUAL;
		}
		else if ((m_ulSelRelat & DISJ) && m_ONrDisjoint.Count())
		{
			TransferResults (DISJ, m_ONrDisjoint, pEnumOut);
			m_ONrDisjoint.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSDISJOINT, &RF), 40);
			bstrColor = cDisjointColor;
			rgPosition = DISJOINT;
		}
		else if (m_ONrUnclear.Count())
		{
			TransferResults (0xFF, m_ONrUnclear, pEnumOut);
			m_ONrUnclear.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSUNCLEAR, &RF), 40);
			bstrColor = cUnclearColor;
			rgPosition = UNCLEAR;
		}
	}


	// nur ein Sammelfenster
	else
	{
		if (m_ONrRelat.Count())
		{
			TransferResults (0xFF, m_ONrRelat, pEnumOut);
			m_ONrRelat.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJRELAT, &RF), 40);
			bstrColor = cUniversalColor;
		}
		else if (m_ONrUnclear.Count())
		{
			TransferResults (0xFF, m_ONrUnclear, pEnumOut);
			m_ONrUnclear.EveryDelete();
			bstrCapt = ResString (ResID (IDS_OBJSUNCLEAR, &RF), 40);
			bstrColor = cUnclearColor;
			rgPosition = UNCLEAR;
		}
	}
} // BuildOutputObjects


// --------------------------------------------------------------------------------------------
// Mitteilung, wenn die topologische Analyse für mindestens eine ausgewählte Relation keine
// Ergebnisobjekte liefert
CComBSTR TopoRelFunc :: MessageNoObjects (void)
{
ResourceFile RF (g_pDLLName);
string strMessageNoObjects = "";

	if (m_bSepaWin)
	{
		if ((m_ulSelRelat & DISJ) &&
			(0 == m_ONrDisjoint.Count() || !IsTreeContentValid (DISJ, m_ONrDisjoint)))
			strMessageNoObjects += ResString (ResID (IDS_NODISJOINT, &RF), 100);

		if ((m_ulSelRelat & EQUA) &&
			(0 == m_ONrEqual.Count() || !IsTreeContentValid (EQUA, m_ONrEqual)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOEQUAL, &RF), 100);
		}

		if ((m_ulSelRelat & TOUC) &&
			(0 == m_ONrTouch.Count() ||!IsTreeContentValid (TOUC, m_ONrTouch)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOTOUCH, &RF), 100);
		}

		if ((m_ulSelRelat & ENTE) &&
			(0 == m_ONrEnter.Count() || !IsTreeContentValid (ENTE, m_ONrEnter)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOENTER, &RF), 100);
		}

		if ((m_ulSelRelat & OVER) &&
			(0 == m_ONrOverlap.Count() || !IsTreeContentValid (OVER, m_ONrOverlap)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOOVERLAP, &RF), 100);
		}
	
		if ((m_ulSelRelat & CONT) &&
			(0 == m_ONrContain.Count() || !IsTreeContentValid (CONT, m_ONrContain)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOCONTAIN, &RF), 100);
		}
	
		if ((m_ulSelRelat & WITH) &&
			(0 == m_ONrWithin.Count() || !IsTreeContentValid (WITH, m_ONrWithin)))
		{
			if (strMessageNoObjects != "") strMessageNoObjects += "\n\n";
			strMessageNoObjects += ResString (ResID (IDS_NOWITHIN, &RF), 100);
		}
	}

	else
		if (0 == m_ONrRelat.Count() || !IsTreeContentValid (0xFF, m_ONrRelat))
			strMessageNoObjects = ResString (ResID (IDS_NORELAT, &RF), 100);

	return (CComBSTR)strMessageNoObjects.c_str();
		
} // MessageNoObjects


// --------------------------------------------------------------------------------------------
// Bearbeiten der gesamten Sicht
bool TopoRelFunc :: ProcessCompleteView (ulong ulSelRelat)
{
long lCRO[4];	// Container-Koordinaten des Bezugsobjektes

	DEX_GetObjContainer (m_lRefONr, lCRO);

CEierUhr Wait (g_pTE->MVWind());
	
// Objektnummern der Objekte aus der aktuellen Sicht (ERGActSight) in Routine GetObjRelat()
// bereitstellen, deren Container mit dem Container des Bezugsobjektes "etwas" gemeinsam haben
ENUMRECHGEOMETRIE ERG;	// Struktur für Geometrierecherche

	INITSTRUCT (ERG, ENUMRECHGEOMETRIE);
	ERG.lCont = lCRO;					// SuchBereich (umschließendes Rechteck des Bezugsobjektes)
	ERG.iMode = ERGActSight;			// SuchMode (nur aktuelle Sicht auswerten)
	ERG.eFcn = (RECHGEOMETRIEPROC) GetObjRelat;	// gerufene Funktion

bool bOK = DEX_EnumRechGeometrie (ERG);	// bei Abbbruch durch den Anwender: false
	
	// Nummern der Objekte, die bei der soeben durchgeführten Enumeration nicht erfaßt wurden
	// (also vollständig außerhalb des Bezugsobjektes liegen) noch in den m_ONrDisjoint- bzw.
	// m_ONrRelat-Baum eintragen
	if (bOK && ulSelRelat & DISJ)
		OutsideObjects();

	return true;

} // ProcessCompleteView


// --------------------------------------------------------------------------------------------
// Nummern der Objekte, die bei der Geometrierecherche nicht erfaßt wurden (also vollständig
// außerhalb des Bezugsobjektes liegen) noch in den m_ONrDisjoint- bzw. m_ONrRelat- Baum eintragen
bool TopoRelFunc :: OutsideObjects (void)
{
// alle Objektklassen der aktuellen Sicht bereitstellen
char cSichtName[MAXVIEWNAMESIZE+1] = { '\0' };     // Name der Sicht (NICHT mit "string")
ENUMTEXTKEY ETK;	// Struktur für Enumeration mit einem char*-Key (hier: Name der aktuellen
					// Sicht)
	ETK.eKey = DEX_GetActiveSight (cSichtName);  // Suchschlüssel (Name der aktuellen Sicht)
	ETK.eFcn = (ENUMTEXTKEYPROC) GetObjNumbersOfAClass;
	return DEX_EnumSightIdents (ETK);

} // OutsideObjects


// --------------------------------------------------------------------------------------------
// Testen, ob lONr-Objekt schon im m_ONrWithin-, m_ONrContain-, m_ONrOverlap-, m_ONrEnter-,
// m_ONrTouch-, m_ONrEqual- bzw. im m_ONrUnclear-Baum enthalten ist; wenn nein, dann Eintrag
// in den m_ONrDisjoint- bzw. m_ONrRelat-Baum 
bool TopoRelFunc :: IsObjectInTree (long lONr)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

	if (lONr == m_lRefONr)	// kein Test mit "sich selbst"
		return true;

	if (m_bFirstRelObj)	{
	int iOT = DEX_GetObjectType (lONr);

		if (OT_KANTE == iOT || OT_FLAECHE == iOT) {
			GeoReinInterface();
			if (S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr))
			{
				// Objekte mit Geometriefehler in den m_ONrUnclear-Baum
				if (!m_ONrUnclear.MemberK (lONr))
					m_ONrUnclear.InsertK (lONr, m_lRefObjCount);

				return true;
			}
		}
	}
	
bool bWithin = false;	// Objektnummer lONr ist nicht im Baum m_ONrWithin
bool bContain = false;	//  nicht im Baum m_ONrContain
bool bOverlap = false;	//  nicht im Baum m_ONrOverlap
bool bEnter = false;	//  nicht im Baum m_ONrEnter
bool bTouch = false;	//  nicht im Baum m_ONrTouch
bool bEqual = false;	//  nicht im Baum m_ONrEqual
bool bDisjoint = false;	//  nicht im Baum m_ONrDisjoint
bool bUnclear = false;	//  nicht im Baum m_ONrUnclear

	bWithin = m_ONrWithin.MemberK (lONr);
	if (! bWithin)
	{
		bContain = m_ONrContain.MemberK (lONr);
		if (! bContain)
		{
			bOverlap = m_ONrOverlap.MemberK (lONr);
			if (! bOverlap)
			{
				bEnter = m_ONrEnter.MemberK (lONr);
				if (! bEnter)
				{
					bTouch = m_ONrTouch.MemberK (lONr);
					if (! bTouch)
					{
						bEqual = m_ONrEqual.MemberK (lONr);
						if (! bEqual)
						{
							bDisjoint = m_ONrDisjoint.MemberK (lONr);
							if (! bDisjoint)
								bUnclear = m_ONrUnclear.MemberK (lONr);
						}
					}
				}
			}
		}
	}

	// lONr ist weder im m_ONrWithin-, m_ONrOverlap-, m_ONrOverlap-, m_ONrEnter-, m_ONrTouch-,
	// m_ONrEqual-, m_ONrDisjoint- noch im m_ONrUnclear-Baum enthalten
	if (!bWithin && !bContain && !bOverlap && !bEnter && !bTouch && !bEqual && !bDisjoint &&
		!bUnclear)
	{
		if (m_bSepaWin)
			m_ONrDisjoint.InsertK (lONr, m_lRefObjCount);	//  dann in Baum m_ONrDisjoint
		else
			m_ONrRelat.InsertK (lONr, m_lRefObjCount);		//   oder in Baum m_ONrRelat eintragen
	}

	return true;

} // IsObjectInTree


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "GeometrieBereinigung" herstellen, wenn noch m_bGeoRein == false
HRESULT TopoRelFunc :: GeoReinInterface (void)
{
    if (m_bGeoRein) return S_FALSE;

HRESULT hrRet;

    if (g_pTE && g_pTE->m_pXtnSite)
    	hrRet = g_pTE->m_pXtnSite->GetXtension (CLSID_GeometrieBereinigung, IID_IExtendGeoRein,
    											(LPVOID*)&m_wGeoRein);
    else hrRet = E_UNEXPECTED;

    if (FAILED (hrRet) ||	// Fehler, z.B. GeoRein.ext nicht verfügbar
    	! g_pTE || ! g_pTE->m_pXtnSite)
    {
	ResourceFile RF (g_pDLLName);
    ResString resText (ResID (IDS_NOGEOREIN, &RF), 250);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, &RF), 50);
    	
    	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
    	return hrRet;
    }

    m_bGeoRein = true;
    return S_OK;

} // GeoReinInterface   



///////////////////////////////////////////////////////////////////////////////////////////////
// Funktionen für das Interface von TopoRelatExtension

// ------------------------------------------------------------------------------------------------
// Topologische Relation zwischen dem lONr1-Bezugsobjekt und einem weiteren lONr2-Objekt
HRESULT TopoRelFunc :: RelationObjObj_ONr (long lONr1, long lONr2, Relat* prTR)
{
	_ASSERTE (0 != lONr1);
	_ASSERTE (-1 != lONr1);
	_ASSERTE (0 != lONr2);
	_ASSERTE (-1 != lONr2);

	m_OGCRelat = UNCLEAR;	// für den Fehlerfall

ResourceFile RF (g_pDLLName);
ResString resText (ResID (IDS_GEOFEHL2, &RF), 200);
string sErrText;
ErrCode rcDummy;

	GeoReinInterface();
	if (S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr1))
	{
		Format (sErrText, (char*)resText.Addr(), lONr1);
		DEX_SetError (rcDummy, 0, WC_MESSAGE_TOPO, (void*)sErrText.c_str());
		*prTR = REL_UNKLAR;
		return S_FALSE;
	}

	if (S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr2))
	{
		Format (sErrText, (char*)resText.Addr(), lONr2);
		DEX_SetError (rcDummy, 0, WC_MESSAGE_TOPO, (void*)sErrText.c_str());
		*prTR = REL_UNKLAR;
		return S_FALSE;
	}

	m_bSepaWin = true;	// Analyseergebnisse in getrennten Recherchefenstern anzeigen
	m_lRefONr = lONr1;	// Objektnummer des lONr1-Bezugsobjektes

Posit posLage;			// Relation des zu testenden lONr2-Objektes
EObjekt* pEO = NULL;	// zu testendes lONr2-Objekt

	DELETE_OBJ (m_pRefObj);
	if (! BuildReferenceObject())	// lONr1-Bezugsobjekt als m_pRefObj erzeugen
	{
		*prTR = REL_UNKLAR;		// nicht genügend dynamischer Speicher
		return E_OUTOFMEMORY;
	}

	if (! EObjektErzeugen (lONr2, pEO, &m_CTX))	// zu testendes lONr2-Objekt als pEO erzeugen
	{
		DELETE_OBJ (pEO);
		*prTR = REL_UNKLAR;
		return E_OUTOFMEMORY;
	}
		
	Relations (pEO, posLage);

	DELETE_OBJ (pEO);

	switch (posLage)
	{
		case INNERH:
		case INNERHB:
			*prTR = REL_INN;	// vollständig innerhalb
			return S_OK;

		case AUSSERH:
		case AUSSERHB:
			*prTR = REL_AUSS;	// vollständig außerhalb
			return S_OK;

		case INNAUSS:
		case UMSCHL:
		case UMSCHLB:
			*prTR = REL_INAUS;	// sonstige
			return S_OK;
	}

	*prTR = REL_UNKLAR;
	return E_UNEXPECTED;

} // RelationObjObj_ONr


// --------------------------------------------------------------------------------------------
// Topologische Relation zwischen dem pIOG1-Bezugsobjekt und einem weiteren pIOG2-Objekt
HRESULT TopoRelFunc :: RelationObjObj_Geom (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
											 Relat* prTR)
{
	_ASSERTE (NULL != pIOG1);
	_ASSERTE (NULL != pIOG2);

	m_OGCRelat = UNCLEAR;	// für den Fehlerfall

ResourceFile RF (g_pDLLName);
ResString resText (ResID (IDS_GEOFEHL2, &RF), 200);
string sErrText1, sErrText2;
ErrCode rcDummy;
BOOL bSucc;		// Parameter von WholeAnalysis_Geom()

long lONr1 = -1, lONr2 = -1;	// pIOG1 bzw. pIOG2 können einfach nur Geometrien sein, d. h.
							// keine echten DB-Objekte, müssen also keine Objektnummern haben

	pIOG1->GetONr (&lONr1);
	pIOG2->GetONr (&lONr2);

	if (lONr1 <= 0 || lONr2 <= 0)
    	GeoReinInterface();		// (wenn noch nicht, dann) GeoReinInterface für
								// WholeAnalysis_Geom() zuschalten

	// Test auf Fehlerhaftigkeit für Objekte, die nicht in der DB enthalten sind
    if (m_wGeoRein.IsValid())
    {
		if (lONr1 <= 0 &&
    		S_OK != m_wGeoRein->WholeAnalysis_Geom (pIOG1, &bSucc))
			Format (sErrText1, (char*)resText.Addr(), lONr1);

		if (lONr2 <= 0 &&
    		S_OK != m_wGeoRein->WholeAnalysis_Geom (pIOG2, &bSucc))
			Format (sErrText2, (char*)resText.Addr(), lONr2);
	}

	// Test auf Fehlerhaftigkeit für DB-Objekte
	GeoReinInterface();
	if (0 != lONr1 && -1 != lONr1 &&
		S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr1))
		Format (sErrText1, (char*)resText.Addr(), lONr1);

	if (0 != lONr2 && -1 != lONr2 &&
		S_FALSE != FehlerhaftesObjektKorrigieren(m_wGeoRein, lONr2))
		Format (sErrText2, (char*)resText.Addr(), lONr2);

	if ("" != sErrText1 || "" != sErrText2)
	{
		if ("" != sErrText1)
			DEX_SetError (rcDummy, 0, WC_MESSAGE_TOPO, (void*)sErrText1.c_str());
		if ("" != sErrText2)
			DEX_SetError (rcDummy, 0, WC_MESSAGE_TOPO, (void*)sErrText2.c_str());
		*prTR = REL_UNKLAR;
		return S_FALSE;
	}

	m_bSepaWin = true;	// Analyseergebnisse in getrennten Recherchefenstern anzeigen

Posit posLage;			// Relation des zu testenden pIOG2-Objektes
EObjekt* pEO = NULL;	// zu testendes pIOG2-Objekt

	DELETE_OBJ (m_pRefObj);
	if (! IObjGeometrieInEObj (pIOG1, m_pRefObj, &m_CTX) ||	// pIOG1-Bezugsobjekt als m_pRefObj erzeugen
		! IObjGeometrieInEObj (pIOG2, pEO, &m_CTX))		// zu testendes pIOG2-Objekt als pEO erzeugen
	{
		DELETE_OBJ (pEO);
		*prTR = REL_UNKLAR;	// nicht genügend dynamischer Speicher
		return E_OUTOFMEMORY;
	}
		
	Relations (pEO, posLage);

	DELETE_OBJ (pEO);

	switch (posLage)
	{
		case INNERH:
		case INNERHB:
			*prTR = REL_INN;	// vollständig innerhalb
			return S_OK;

		case AUSSERH:
		case AUSSERHB:
			*prTR = REL_AUSS;	// vollständig außerhalb
			return S_OK;

		case INNAUSS:
		case UMSCHL:
		case UMSCHLB:
			*prTR = REL_INAUS;	// sonstige
			return S_OK;
	}

	*prTR = REL_UNKLAR;
	return E_UNEXPECTED;

} // RelationObjObj_Geom


// --------------------------------------------------------------------------------------------
// Topologische TRiAS- und OGC-Relationen zwischen dem lONr1-Bezugsobjekt und einem weiteren
// lONr2-Objekt
HRESULT TopoRelFunc :: RelationObjObj2_ONr (LONG lONr1, LONG lONr2, UINT* puiTR)
{
Relat rTR = REL_UNKLAR;	// TRiAS-Relation
HRESULT hRet = RelationObjObj_ONr (lONr1, lONr2, &rTR);

	switch (m_OGCRelat)
	{
		case WITHIN:
			*puiTR = rTR | REL_WITHIN;
			break;

		case CONTAIN:
			*puiTR = rTR | REL_CONTAIN;
			break;

		case OVERLAP:
			*puiTR = rTR | REL_OVERLAP;
			break;

		case ENTER:
			*puiTR = rTR | REL_ENTER;
			break;

		case TOUCH:
			*puiTR = rTR | REL_TOUCH;
			break;

		case EQUAL:
			*puiTR = rTR | REL_EQUAL;
			break;

		case DISJOINT:
			*puiTR = rTR | REL_DISJOINT;
			break;

		case INTERSECT:
			*puiTR = rTR | REL_INTERSECT;
			break;

		default:
			_ASSERTE (false);
			*puiTR = rTR | REL_UNCLEAR;
			hRet = E_UNEXPECTED;
	}

	return hRet;
	
} // RelationObjObj2_ONr


// --------------------------------------------------------------------------------------------
// Topologische TRiAS- und OGC-Relationen zwischen dem Bezugsobjekt pIOG1 und einem weiteren
// Objekt pIOG2
HRESULT TopoRelFunc :: RelationObjObj2_Geom (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
											  UINT* puiTR)
{
Relat rTR = REL_UNKLAR;	// TRiAS-Relation
HRESULT hRet = RelationObjObj_Geom (pIOG1, pIOG2, &rTR);

	switch (m_OGCRelat)
	{
		case WITHIN:
			*puiTR = rTR | REL_WITHIN;
			break;

		case CONTAIN:
			*puiTR = rTR | REL_CONTAIN;
			break;

		case OVERLAP:
			*puiTR = rTR | REL_OVERLAP;
			break;

		case ENTER:
			*puiTR = rTR | REL_ENTER;
			break;

		case TOUCH:
			*puiTR = rTR | REL_TOUCH;
			break;

		case EQUAL:
			*puiTR = rTR | REL_EQUAL;
			break;

		case DISJOINT:
			*puiTR = rTR | REL_DISJOINT;
			break;

		case INTERSECT:
			*puiTR = rTR | REL_INTERSECT;
			break;

		default:
			_ASSERTE (false);
			*puiTR = rTR | REL_UNCLEAR;
			hRet = E_UNEXPECTED;
	}

	return hRet;

} // RelationObjObj2_Geom


// --------------------------------------------------------------------------------------------
// Rückgabe aller Objekte, die zu dem lONr-Bezugsobjekt eine in relTR vorgegebene Relation
// besitzen
HRESULT TopoRelFunc :: RelatObjekte_ONr (long lONr, Relat relTR, IEnumLONG** ppEnumOut)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

	m_bSepaWin = true;	// Analyseergebnisse in getrennten Recherchefenstern anzeigen
	m_lRefONr = lONr;	// Objektnummer des Bezugsobjektes

	DELETE_OBJ (m_pRefObj);
	if (! BuildReferenceObject())	// lONr-Bezugsobjekt als m_pRefObj erzeugen
		return E_OUTOFMEMORY;

	m_ulSelRelat = 0x00;
	if (REL_INN == relTR)
		m_ulSelRelat |= WITH | EQUA;
	else if (REL_INAUS == relTR)
		m_ulSelRelat |= OVER | ENTE | CONT;
	else if (REL_AUSS == relTR)
		m_ulSelRelat |= DISJ | TOUC;
	else if (0x00 != relTR >> 8) m_ulSelRelat = (relTR & 0xff00) >> 8;	// #HK000422: ADDED '>> 8'

	ProcessCompleteView (m_ulSelRelat);


	COM_TRY
	{
	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		_ASSERTE (wOutput.IsValid());

		// Übertragen der Objektnummern der Ergebnisobjekte nach wOutput
		TransferResults (WITH, m_ONrWithin, wOutput);
		TransferResults (EQUA, m_ONrEqual, wOutput);
		TransferResults (OVER, m_ONrOverlap, wOutput);
		TransferResults (ENTE, m_ONrEnter, wOutput);
		TransferResults (CONT, m_ONrContain, wOutput);
		TransferResults (DISJ, m_ONrDisjoint, wOutput);
		TransferResults (TOUC, m_ONrTouch, wOutput);

		*ppEnumOut = wOutput.detach();
	}
	COM_CATCH;

	return S_OK;

} // RelatObjekte_ONr

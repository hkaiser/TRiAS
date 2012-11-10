// Methoden für Klassen GeometrieKnoten und GeometrieBaum
// File: GEOMTREE.CXX
// H. Kaiser, W. Mörtl


#include "geoeditp.hxx"


#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




// ===================================================================================================
// Methoden für Klasse GeometrieKnoten
// ---------------------------------------------------------------------------------------------------
// friend-Funktionen
// bekommt als Parameter den Pointer auf ein im Baum "GeometrieBaum" hängendes Objekt und liefert
// den Pointer auf die Objektnummer (den Schlüssel)
void* _GEOEDIT_EXPORT GeometrieGetKey (void* pObj)
{
	return & ((GeometrieKnoten*) pObj) -> GetONr();
} // GeometrieGetKey


// ---------------------------------------------------------------------------------------------------
// GeometrieKnoten werden in GeometrieBaum nach aufsteigenden Objektnummern sortiert;
// Die beiden Pointer-Parameter werden durch GeometrieGetKey erzeugt, der erste zeigt auf einen
// mittels Create neu einzufügenden Knoten bzw. einen mittels Find() zu suchenden Knoten, der zweite
// auf den schon im Baum vorhandenen Knoten, beginnend bei der Wurzel
int _GEOEDIT_EXPORT GeometrieCompare (void* pKey1, void* pKey2)
{
	TX_ASSERT (pKey1 != NULL);
	TX_ASSERT (pKey2 != NULL);

	if (!pKey1 || !pKey2)
		return -2;		// Fehlerfall

long lONr1 = *(long*) pKey1;
long lONr2 = *(long*) pKey2;

	TX_ASSERT (lONr1 > 0);
	TX_ASSERT (lONr2 > 0);

	if (lONr1 <= 0 || lONr2 <= 0)
		return -2;		// Fehlerfall

	if (lONr1 < lONr2)	// Vergleich zweier Objektnummern
		return -1;
	if (lONr1 > lONr2)
		return 1;

	return 0;		// zwei gleiche Objektnummern können bei Find() auftreten
} // GeometrieCompare


// ---------------------------------------------------------------------------------------------------
// Konstruktor
GeometrieKnoten :: GeometrieKnoten (void)
{
	m_pIOG = NULL;
	m_lONr = 0;
	m_iAnz = 1;
}


// ---------------------------------------------------------------------------------------------------
// Destruktor
GeometrieKnoten :: ~GeometrieKnoten (void)
{
	if (m_pIOG)
	{
		// das hier zugehörige AddRef() wird gebildet in
		// GeometrieKnoten::CreateInstance (lONr) aus GeometrieBaum::InsertK (long lONr)
		// FInit (lONr) aus GeometrieKnoten::CreateInstance (long lONr)
		// CreateInterfaceOG (m_pIOG, lONr) aus GeometrieKnoten::FInit (long lONr)
		// CoCreateInstance (CLSID_ObjektGeometrie, NULL, CLSCTX_INPROC_SERVER, IID_IInitObjektGeometrie,
		//    (LPVOID*) &pInitOG) aus CreateInterfaceOG (IObjektGeometrie** pIOG, long lONr)
		// CreateAnObject (punkOuter, riid, ppvObj) aus ObjektGeometrieCF::CreateInstance (LPUNKNOWN punkOuter,
		//    REFIID riid, LPVOID *ppvObj)
		// ObjektGeometrie::CreateInstance (punkOuter, ObjectDestroyed) aus CreateAnObject (LPUNKNOWN punkOuter,
		//    REFIID riid, LPVOID FAR *ppvObj)
		// AddRef() aus ObjektGeometrie::CreateInstance (LPUNKNOWN pIUnk, DESTROYNOTIFYPROC* pFcn)
		m_pIOG -> Release ();
		m_pIOG = NULL;
	}
}


// ---------------------------------------------------------------------------------------------------
// GeometrieKnoten zweistufig anlegen
GeometrieKnoten* GeometrieKnoten :: CreateInstance (long lONr)
{
	TX_ASSERT (lONr > 0);

GeometrieKnoten* pGK = new GeometrieKnoten ();

	if (pGK == NULL || !pGK -> FInit (lONr))
		DELETE (pGK);

	return pGK;
}


// ---------------------------------------------------------------------------------------------------
// Initialisierung eines GeometrieKnoten einschl. Geometrie von TRiAS lesen
bool GeometrieKnoten :: FInit (long lONr)
{
	if (FAILED(CreateInterfaceOG (&m_pIOG, lONr)))
		return false;

	m_lONr = lONr;
	return true;
}


// ---------------------------------------------------------------------------------------------------
// Rückgabe des Members IObjektGeometrie* m_pIOG
HRESULT GeometrieKnoten :: GetIOG (IObjektGeometrie** ppIOG)
{
	if (m_pIOG)
	{
		m_pIOG -> AddRef();	// ein weiterer Zugriff auf m_pIOG durch nachfolgende Pointerkopie
		*ppIOG = m_pIOG;
		return S_OK;
	}
	*ppIOG = NULL;	
	return E_POINTER;
} // GetIOG




// ===================================================================================================
// Methoden für Klasse GeometrieBaum
// ---------------------------------------------------------------------------------------------------
// Ruf eines korrekten Destruktors, wenn ein Objekt freigegeben werden soll
void _GEOEDIT_EXPORT GeometrieBaum :: UserDelete (void* pObj)
{
	TX_ASSERT (pObj != NULL);

	((GeometrieKnoten*)pObj) -> ~GeometrieKnoten();
} // UserDelete


// ---------------------------------------------------------------------------------------------------
// Knoten in GeometrieBaum einfügen
bool GeometrieBaum :: InsertK (long lONr)
{
	TX_ASSERT (lONr > 0);

	if (WiederholungK (lONr))	// wenn lONr-Objekt schon im Baum, wird nur m_iAnz inkrementiert
		return false;

GeometrieKnoten* pGK = GeometrieKnoten :: CreateInstance (lONr);
GeometrieKnotenOptCreator KC (*this);	// bisher: GeometrieKnotenCreator

	if (pGK == NULL || !KC.InsertPtr (pGK))
	{
		DELETE (pGK);	// 15.4.97
		return false;
	}
	return true;
} // InsertK


// ---------------------------------------------------------------------------------------------------
// Knoten in GeometrieBaum löschen, wenn das betreffende Objekt deselektiert wurde;
// da das Objekt in mehreren Recherchefenstern selektiert gewesen sein kann, darf es erst dann
// wirklich gelöscht werden, wenn es zum letzten Mal deselektiert wurde
bool GeometrieBaum :: DeleteK (long lONr)
{
	TX_ASSERT (lONr > 0);

bool toDelete = false;
CTable tab (*this);

	if (tab.Find (&lONr))
	{
	GeometrieKnotenLock kl (tab);

		if (kl)
		{
			kl -> DecAnz ();		// m_iAnz dekrementieren
			if (0 == kl->GetAnz())	// Objekt war nur noch einmal in einem der Recherchefenster
				toDelete = true;	//  selektiert, deshalb kann es wirklich gelöscht werden
		}
		else
    		DEX_Error (RC_DeleteKEdit, EC_SYSERROR);
	}

	if (toDelete)
	{
		tab.Delete ();
		return true;	// Knoten gelöscht
	}

	return false;	// Knoten nicht gefunden und damit nicht gelöscht bzw. Knoten noch nicht gelöscht,
					// da Objekt immer noch in mindestens einem weiteren Recherchefenster selektiert ist
} // DeleteK


// ---------------------------------------------------------------------------------------------------
// Objektgeometrie des lONr-Objektes ist schon Element des GeometrieBaumes (true) und
// Inkrementierung von m_iAnz, sonst false
bool GeometrieBaum :: WiederholungK (long lONr)
{
	TX_ASSERT (lONr > 0);

CTable tab (*this);

	if (tab.Find (&lONr))
	{
	GeometrieKnotenLock kl (tab);

		if (kl)
		{
			kl -> IncAnz ();
			return true;
		}
		else
			DEX_Error (RC_WiederholungKEdit, EC_SYSERROR);
	}

	return false;
} // WiederholungK

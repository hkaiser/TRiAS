// Klassen für Abspeicherung von Objektgeometrien in einem Baum
// File: GEOMTREE.HXX
// H. Kaiser, W. Mörtl


#ifndef _GEOMTREE_HXX
#define _GEOMTREE_HXX


#if !defined(NOGEOMETRIEBAUM)
class GeometrieKnoten
{
friend void* GeometrieGetKey (void*);		// liefert den Schlüssel des Knotens
friend int GeometrieCompare (void*, void*);	// vergleicht zwei Schlüssel

private:
	IObjektGeometrie* m_pIOG;
	long m_lONr;		// Objektnummer von m_pIOG (Schlüssel für GeometrieBaum)
	short m_iAnz;		// Anzahl, wie oft dieses Objekt in möglicherweise mehreren
						//  Recherchfenstern selektiert ist

protected:
		GeometrieKnoten (void);

	bool FInit (long lONr);

public:
		~GeometrieKnoten (void);

static GeometrieKnoten* CreateInstance (long lONr);

//	operator IObjektGeometrie *() { return m_pIOG; }

	HRESULT GetIOG (IObjektGeometrie** ppIOG);
	long& GetONr (void) { return m_lONr; }
	short GetAnz (void) const { return m_iAnz; }
	void IncAnz (void) { m_iAnz++; }		// m_iAnz inkrementieren
	void DecAnz (void) { m_iAnz--; }		// m_iAnz dekrementieren
	void SetAnz (short iAnz = 0) { m_iAnz = iAnz; }	// m_iAnz setzen

//	bool WriteBack (...);
//	bool MarkObject (...);
};
#endif // NOGEOMETRIEKNOTEN

                                              
                                              
#if !defined(NOGEOMETRIEBAUM)
class GeometrieBaum : public COptTree
{
protected:
	void UserDelete (void* pObj);
	
public:
		GeometrieBaum (LONG lDelta = 1)
			: COptTree (GeometrieGetKey, GeometrieCompare, CFDefault, lDelta) {}
		~GeometrieBaum (void) { EveryDelete(); }

	bool InsertK (long lONr);
	bool DeleteK (long lONr);
	bool WiederholungK (long lONr);
};


	// generiert zwei Klassen:
	// GeometrieKnotenCreator    für Neueintrag eines GeometrieKnoten in GeometrieBaum
	// GeometrieKnotenLock       für typsicheren Zugriff auf einen Knoten
	DeclareOptLock (GeometrieBaum, GeometrieKnoten);

#endif // NOGEOMETRIEBAUM

#endif // _GEOMTREE_HXX

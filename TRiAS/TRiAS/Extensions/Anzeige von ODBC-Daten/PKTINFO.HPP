/*
DATEI: PKTINFO.HPP

Der Container verwaltet Objekt-Informationen von vorgegebenen Objektklassen.

  Erarbeitet: J. Benkenstein					Stand vom: 17.1.1996
*/

#ifndef _PUNKT_INFO_HPP
#define _PUNKT_INFO_HPP

enum ObjektState { NotModified = 0, IsModified = 1, IsDeleted = 2 };

class CPunktInfo
{
public:
	double m_dX, m_dY;			// Koordinaten
	long m_lObjNr;				// Objekt-Nummer	
	CString m_strMerkmal;		// Merkmalswert
	BOOL m_sIsModified;			// wurde modifiziert 

//	Konstruktor/Destruktor
	CPunktInfo (long lObjNr, const char *pMerkmal, double XKoord, double YKoord,
				short sIsModified);
	~CPunktInfo (void) {}

//	globale Zugriffsfunktionen
	friend void *GetPunktInfo (void *pObj);
};

class CPunktInfoTree : public CTree
{
private:
	BOOL m_bDelDopp;				// doppelte löschen ?

protected:
	void UserDelete (void *pObj);
	
	BOOL StoreObjektInfo (long lObjNr, double X, double Y, const char *pMerkmal,
						  short sIsMod = NotModified);

	//	Fehlermeldung ausgeben
	void OutputError (uint uiResID, long lObjNr,
					 
					  long X, long Y, const char *pMerkmal);

public:
//	Konstruktor/Destruktor
	CPunktInfoTree (BOOL bDeleteDoppelte);
	~CPunktInfoTree (void);

//	weitere Member
//	speichern der für die angegebenen Objektklassen zugeh. CPunktInfo
	BOOL GetPunktInfos (ulong *pObjektKlassen, ulong ulMerkmalsKode);

		//	nicht referenzierte Objekte löschen
	BOOL DeleteNotRefObj (CProgressCtrl &stProgress, CStatic &stInfo,
						  void (*pWasInterrupted) (void));

		// SatzInfo speichern
	BOOL StoreRecordInfo (long lObjNr, const char *pMerkmal,	
						  double dX, double dY, short sMod);

//	friend-Funktionen
	friend BOOL PASCAL EnumObjektMerkmale (long lObjNr, DWORD dwData, void *pData);
};
DeclareLock (CPunktInfoTree, CPunktInfo);

#endif	// _PUNKT_INFO_HPP

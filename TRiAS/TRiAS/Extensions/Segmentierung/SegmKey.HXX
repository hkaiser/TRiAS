// Klassendefinitionen fuer Knoten-Baum ------------------------------------------
// File: SEGMKEY.HXX

#if !defined(_SEGMKEY_HXX)
#define _SEGMKEY_HXX

///////////////////////////////////////////////////////////////////////////////
#include <containr.hxx>
// KnotenKlasse
class CSegKnoten 
{
private:
	string m_strKeyText;
	string m_strGuid;
	long m_lONr;


public:
// Konstruktor/Destruktor
	CSegKnoten (const char *pKeyText);
	~CSegKnoten();


// ZugriffsFunktionen für Knoten-Baum
	friend void _XTENSN_EXPORT *GetKnoten (void *pObj);
//	friend int _XTENSN_EXPORT CmpKnoten (void *pObj1, void *pObj2);

	char const *KeyText() { return m_strKeyText.c_str(); }

	// 
	void SetObject ( long lONr ) { m_lONr = lONr; }
	long &GetObject (void) { return m_lONr; }

};

class CSegKnotenTree : 
	public CTree 
{
protected:
	void _XTENSN_EXPORT UserDelete (void *pObj);

public:
// Konstruktor/Destruktor 
	CSegKnotenTree (void);
	~CSegKnotenTree (void);

};
DeclareLock (CSegKnotenTree, CSegKnoten);		// notwendige Klassendefinitionen

#endif // _SEGMKEY_HXX

/*
File: LAYERS.HPP
realiert die Verwaltung der zu importierenden Layernamen

erarbeitet : J. Benkenstein                 Stand vom 28.11.1996
*/

#ifndef _LAYERS_HPP
#define _LAYERS_HPP

//  Die Klasse speichert alle Informationen zu einem Layer
class CLayer
{
private:
// 	Attribute
    char *m_pLayerName;

public:
//  Konstruktor/Destruktor
	CLayer (void);
    ~ CLayer (void);

// 	weitere Member
	Bool Init (char *pLayerName);
    char *LayerName (void) { return m_pLayerName; }

//  friend Funktionen
    friend void* GetLayerName (void *pObj);            // Get-Key-Funktion
	friend int CompareLayerNames (void *pObj1, void *pObj2);
};


//  Die Klasse verwaltet die Layerbeschreibungen
class ResourceFile;
class CLayerBaum : public CTree 
{
protected:
#ifdef WIN32
	void UserDelete (void *pObj);
#else
	void __export UserDelete (void *pObj);
#endif

public:
//  Konstruktor/Destruktor
    CLayerBaum (void);
    ~ CLayerBaum (void);				// Tabelleninhalt löschen

// 	weitere Member
	Bool Init (ResourceFile *pRF, char *pEbenen); // lese alle gültigen Layernamen aus Registry

	Bool IsValid (char *pLayerName);	// gültiger Layername
};
DeclareLock (CLayerBaum, CLayer);

#endif // __LAYERS_HPP


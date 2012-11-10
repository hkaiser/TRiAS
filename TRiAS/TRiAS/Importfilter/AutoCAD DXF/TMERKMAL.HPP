/*
File: TMERKMAL.HPP
realiert die Verwaltung einer Textmerkmals-Liste.

erarbeitet : J. Benkenstein				 Stand vom 28.08.1995
*/

#ifndef _TMERKMAL_HPP
#define _TMERKMAL_HPP

#ifndef NO_TEXT_MERKMAL
// Textmerkmal im DIRIS-ASCII-Format
class TextMerkmal 
{
private:
	char *m_pMValue;		// Wert/Inhalt des Merkmals
	char *m_pMName;			// Name des Merkmals

public:
// 	Konstruktor/Destruktor
	TextMerkmal (void) { m_pMValue = m_pMName = NULL; }
	~ TextMerkmal (void);

// 	weitere Member
	Bool Init (char *pMName, char *pMValue);
	char *GetValue (void) { return m_pMValue; }
	char *GetName (void)  { return m_pMName; }
};
#endif // NO_TEXT_MERKMAL

#ifndef NO_TEXT_MERKMALS_LISTE
// TextMerkmalsListe verwaltet TextMerkmale in einer Liste
class TextMerkmalsListe : public CListContainer
{
protected:
#ifdef WIN32
	void UserDelete (void *pObj);
#else
	void __export UserDelete (void *pObj);	
#endif

public:
// 	Konstruktor/Destruktor
	TextMerkmalsListe   (void);
	~TextMerkmalsListe (void);

// 	weitere Member
//	Merkmal speichern
	Bool AddMerkmal (char *pMName, char *pMValue, Bool bOemToAnsii = True); 

//	operatoren
	Bool operator = (TextMerkmalsListe&);
	Bool operator += (TextMerkmalsListe&);
};
DeclareLock (TextMerkmalsListe, TextMerkmal);
#endif // NO_TEXT_MERKMALS_LISTE

#endif // _TMERKMAL_HPP

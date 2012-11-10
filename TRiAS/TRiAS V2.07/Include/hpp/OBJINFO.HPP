/*
        Die Klasse beinhaltet Infos für TRiAS-Enum-Funtkionen.

        Erarbeitet: J. Benkenstein                      Stand vom: 30.11.95
*/

#ifndef _OBJ_INFO_HPP
#define _OBJ_INFO_HPP

#ifdef WIN32
class CListCtrl;
#endif

// Konstanten
const short KurzTextLen = 80;            		// Länge des KurzTextes für Objektklasse/Merkmal
const short LangTextLen = 256;                  // Länge des Langtextes  -- " --
const short maxLangTextShowLen = 40;			// max. Darstellungslänge eines LangTextes
const ulong ulUnIdMKode = 51200000;				// MerkmalsKode für unique Ident			

//	CObjektInfo -------------------------------------------
class CObjektInfo
{
public:
	ulong m_ulKode;							// Identifikator/Merkmalskode
	CString m_strDescr;

	CObjektInfo (void) { m_ulKode = 0; }
	~CObjektInfo (void) {}

	BOOL InfoComplete (void) { return (m_ulKode > 0) && (!m_strDescr.IsEmpty ()); } 
};

//	Parameter-Halter für DEX_Enum-Funktionen
class ObjMerkmalInfo                        
{
public:
	long m_lType;
	CComboBox *m_pCComboBox;
    CListBox *m_pCListBox;
#ifdef WIN32
	CListCtrl *m_pCListCtrl;
	int m_iIndex, 					// akt. Index in Listcontrol
	m_iMaxFirstLen, m_iMaxSecLen;	// max. Zeichenanzahl für 1. und 2. Spalte
#endif
	ObjMerkmalInfo (void) { Reset (); }
	void Reset (void) 	  { m_lType = 'i'; m_pCComboBox = NULL; m_pCListBox = NULL; 
#ifdef WIN32	
						    m_pCListCtrl = NULL; m_iIndex = m_iMaxFirstLen = m_iMaxSecLen = 0;
#endif
						  }
};

//	KurzText zu einem Id oder Merkmal lesen
char* __export GetKurzText (ulong ulKode, short sType,
						    char *pBuffer, short sBufferSize);

BOOL __export FAR PASCAL FillObjMerkmalList (ulong Ident, BOOL, void* pData);
#ifdef WIN32
BOOL __export FAR PASCAL FillObjMerkmalListView (ulong Ident, BOOL, void* pData);
#endif

#endif _OBJ_INFO_HPP


/*
File: BLOCK.HPP
realiert die Verwaltung von Bl�cken.

erarbeitet : J. Benkenstein		Stand vom 24. April 1998
*/

#ifndef _BLOCK_HPP
#define _BLOCK_HPP

//	CBlock --------------------------------------------------------------------
class DGeoObj;
class TextMerkmalsListe;
class CDGeoObjListe;
class CBlock
{
//	Attribute
private:
	char	*m_pBlockName;		//	Name des Blocks
	double	m_dXBasis,			//	Basispunkt	
			m_dYBasis;
			
//	Liste der einzuf�genden Objekte
	CDGeoObjListe *m_pObjectListe;	

public:
//	Konstruktor/Destruktor
	CBlock ();
	~CBlock ();

	Bool Init (char *pBlockname, double dXBasis, double dYBasis);

//	weitere Member
//	Lese/Schreibfunktionen
	char *BlockName ()  { return m_pBlockName; }
	double & XBasis ()	{ return m_dXBasis; }
	double & YBasis ()	{ return m_dYBasis; }
	
//	neues DGeoObjekt in Liste aufnehmen
	Bool AddObject (DGeoObj *&pObject);

//	Block-Geometrie und �bergebenen Merkmale an TRiAS ausgeben
	Bool Output (long lIdent,						//	Identifikator
				 TextMerkmalsListe *pListe,			//	Merkmalsliste
				 double XInsert, double YInsert,	//	Einf�gepunkt
				 double XMasstab, double dYMasstab,	//	Ma�stab
				 double dDrehWinkel,				//	Winkel
				 double dXOffset, double dYOffset,	//	zus�tz. Verschiebung
				 CDGeoObjListe *pDListe = NULL);		//	Objekte an akt. Liste anh�ngen

//	lese GeoObjectList
	CDGeoObjListe * GetDGeoObjListe () { return m_pObjectListe;	}
	
//  friend Funktionen
    friend void* GetBlockName (void *pObj);            // Get-Key-Funktion
};

//	Tree, der Bl�cke �ber ihren Namen speichert
class CSymbolObject;
class CBlockTree : public CTree
{
private:
	char *m_pActBlockName;
	
	void UserDelete (void *pObj);

public:
//	Konstruktor/Destruktor
	CBlockTree ();
	~CBlockTree ();

//	Neuen Block in Baum anlegen: Blockname wird als aktueller gespeichert
	Bool CreateBlock (char *pBlockname, double dXBasis, double dYBasis);

//	neues DGeoObjekt in Liste aufnehmen: als Objekt zum akt. Block hinzuf�gen
	Bool AddObject (DGeoObj *&pObject);

//	Block ausgeben
	Bool Output (CSymbolObject *pSymbol,		//	ist hier Parameterspeicher
				 CDGeoObjListe *pListe = NULL);	//	Objekte an Liste anh�ngen
};
DeclareLock (CBlockTree, CBlock);

#endif //	_BLOCK_HPP

/*
File: BLOCK.CPP
realiert die Verwaltung von Blöcken.

erarbeitet : J. Benkenstein		Stand vom 24. April 1998
*/

#include "pheader.hpp"			//	prec. Header
#include <new>					//	bad_alloc
#include <assert.h>				//	assert ()	
#include "dxfimp.h"				//	Ressource-Konstanten

#include "tools.hpp"		  	// TRIAS-Ausgabe	
#include "punktli.hpp"	  	  	// PunktListe
#include "tmerkmal.hpp"	  	  	// zugeh. TextMerkmalsListe
#include "merkmal.hpp"		  	// MerkmalsBaum	
#include "bogen.hpp"		  	// GetBogenparam ()	
#include "optparam.hpp" 		// OptParam
#include "dgeo_obj.hpp"	 	  	// DGeoObj

#include "block.hpp"			//	zugeh. Header

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//	globale Variablen
CBlockTree *g_pBlockTree = NULL;

//	externe Funktionen
extern void yyerror (short);
char *DtoA (double Val, char *pBuffer, char *pFormat = NULL);

//	externe Variablen
extern Params OptParams;

//	globale Funktionen -------------------------------------------------------
void* GetBlockName (void *pObj) 
{
	return ((CBlock *) pObj) -> BlockName ();
}

//	CBlock --------------------------------------------------------------------
CBlock :: CBlock ()
{
	m_pBlockName = NULL;
	m_dXBasis = m_dYBasis = 0;
	m_pObjectListe = NULL;
}

CBlock :: ~CBlock ()
{
	DELETE_VEC (m_pBlockName);
	DELETE_OBJ (m_pObjectListe);
}

//	Block init.
Bool CBlock :: Init (char *pBlockName, double dXBasis, double dYBasis)
{
	try
	{
	//	prüfe Parameter
		assert (pBlockName && *pBlockName);
		if (!pBlockName || !*pBlockName)
		{
			yyerror (IDS_PARAM_ERROR);
			return False;
		}

	//	Blocknamen speichern
		m_pBlockName = new char [strlen (pBlockName) + 1];
		strcpy (m_pBlockName, pBlockName);

	//	Einfügepunkt speichert
		m_dXBasis = dXBasis;
		m_dYBasis = dYBasis;

	//	Objektliste anlegen
		m_pObjectListe = new CDGeoObjListe;

		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;	
}

//	neues DGeoObjekt in Liste aufnehmen
Bool CBlock :: AddObject (DGeoObj *&pObj)
{
//	prüfe Parameter
	assert (pObj && m_pObjectListe);
	if (!pObj || !m_pObjectListe)
	{
		yyerror (IDS_PARAM_ERROR);
		return False;
	}

	return m_pObjectListe->AddObject (pObj);
}

//	Block-Geometrie und übergebenen Merkmale an TRiAS ausgeben
Bool CBlock::Output (long lIdent,							//	Identifikator
					 TextMerkmalsListe *pListe,				//	Merkmalsliste
					 double dXInsert, double dYInsert,		//	Einfügepunkt
					 double dXMasstab, double dYMasstab,	//	Maßstab
					 double dDrehWinkel,					//	Drehwinkel
					 double dXOffset, double dYOffset,		//	zusätz. Verschiebung
					 CDGeoObjListe *pGeoListe)				//	Objekte an akt. Liste anhängen
{
//	prüfe Parameter
	assert ((lIdent != 0) && pListe && (pListe->Count() > 0));	//	wenigstens Blockname
	assert (m_pObjectListe);
	if ((lIdent == 0) || (!pListe) || (pListe->Count () < 1) || (!m_pObjectListe))
	{
		yyerror (IDS_PARAM_ERROR);
		return False;
	}
	
//	hat dieser Block Geometrien ?
	if (m_pObjectListe->Count () < 1)
		return True;						//	weiter parsen

//	soll der Block zerlegt werden ?
	if (!OptParams.m_bImpBlocks)
	{
	//	erstelle Punkt-Symbol für den gesamten Block
		DGeoObj Punkt;
		if (!Punkt.Init (DGT_Punkt, lIdent, pListe) ||		//	Init.
			!Punkt.AddPunkt (dXInsert - m_dXBasis + dXOffset,
							 dYInsert - m_dYBasis + dYOffset))//	Punkt hinzufügen
			return False;

	//	ggf. Drehwinkel ausgeben
		Punkt.SetWinkel (dDrehWinkel);
		
	//	Punkt ausgeben oder speichern (bzw. zuvor kopieren
		if (pGeoListe)
			return pGeoListe->AddObject (Punkt);
		else
			return Punkt.Output ();
	}

//	Block soll zerlegt ausgegeben werden: alle graphischen Elemente ausgeben
	CRing r (*m_pObjectListe);	
	for (r.First (); r.Valid (); r.Next ())
	{
		CDGeoObjPtrLock pDGeoObjPtr (r);
		if (!pDGeoObjPtr)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	lese Zeiger auf das DGeoObjekt
		DGeoObj *pObj = pDGeoObjPtr -> GetDGeoObj ();
		if (!pObj)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	Objekt an TRiAS ausgeben
		if (pObj -> OutputExt (lIdent, pListe, 
							   m_dXBasis,			//	Blockbasispunkt,
							   m_dYBasis,
							   dXInsert, dYInsert,	//	akt. Einfügepunkt
							   dXMasstab, dYMasstab, 
							   dDrehWinkel,
							   dXOffset, dYOffset,
							   pGeoListe) == 0)
			return False;
	}

	return True;
}

// CBlockTree -----------------------------------------------------------------
CBlockTree :: CBlockTree ()
			: CTree (GetBlockName)
{
	m_pActBlockName = NULL;
	g_pBlockTree = this;
}

CBlockTree :: ~CBlockTree ()
{
	EveryDelete ();

	DELETE_VEC (m_pActBlockName);

	g_pBlockTree = NULL;
}

void CBlockTree :: UserDelete (void *pObj)
{
	((CBlock *) pObj) -> ~ CBlock ();
}

//	Neuen Block in Baum anlegen
Bool CBlockTree :: CreateBlock (char *pBlockName, double dXBasis, double dYBasis)
{
	try
	{
	//	akt. Block wird ungültig
		DELETE_VEC (m_pActBlockName);

	//	prüfe Blocknamen
		if (!pBlockName || !*pBlockName)
			return True;

	//	wurde der Block bereits gespeichert ?
		CTable Tb (*this);
		if (Tb.Find (pBlockName))
		{
			assert (False);		//	das sollte eigentlich nicht passieren
			return True;
		}

	//	Block speichern
		CBlockCreator BC (*this);
		CBlock *pBlock = ContCreate (BC, CBlock);
		Bool bRet = pBlock && pBlock -> Init (pBlockName, dXBasis, dYBasis);

	//	akt. Blocknamen merken
		if (bRet)
		{
			m_pActBlockName = new char [strlen (pBlockName) + 1];
			strcpy (m_pActBlockName, pBlockName);
		}

		return bRet;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}

//	Block ausgeben
Bool CBlockTree::Output (CSymbolObject *pSymbol, CDGeoObjListe *pGeoListe)					//	Objekte an akt
{
//	prüfe Parameter
	assert (NULL != pSymbol);
	if (!pSymbol)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}		

//	prüfe Blocknamen
	char *pBlockName = (char *)pSymbol->GetBlockName();
	if (!pBlockName || !*pBlockName)
	{
		assert (False);					//	sollte auch nicht passieren
		return True;					//	weiter parsen
	}

//	Block suchen und ausgeben
	CTable Tb (*this);
	if (!Tb.Find (pBlockName))
	{
		assert (False);					//	sollte eigentlich nicht passieren
		return True;					//	weiter parsen
	}
	else
	{
	//	Objekt gültig ?
		if (!Tb.Valid ())
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	Objekt locken
		CBlockLock pBlock (Tb);		
		if (!pBlock)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}

	//	diesen Block entsprechend Zeilen und Spalten ausgeben
	//	Parameter init.
		int iRows = pSymbol->Zeilen ();
		int iCols = pSymbol->Spalten ();
		
	//	Parameter prüfen
		assert ((iRows >= 1) && (iCols >= 1) && pSymbol->GetMerkmalsListe ()); 
		if ((iRows < 1) || (iCols < 1) || !pSymbol->GetMerkmalsListe ())
		{
			yyerror (IDS_PARAM_ERROR);
			return True;		//	weiter parsen
		}

	//	Blöcke ausgeben
		double dYOffset = 0;
		for (int i = 0; i < iRows; i++, dYOffset += pSymbol->ZeilenAbstand ())
		{
			double dXOffset = 0;
			for (int j = 0; j < iCols; j++, dXOffset += pSymbol->SpaltenAbstand ())
			{
			//	Block ausgeben
				if (!pBlock -> Output (pSymbol->GetIdent (),		
									   pSymbol->GetMerkmalsListe (),
									   pSymbol->XInsert (), pSymbol->YInsert (),
									   pSymbol->XMasstab (), pSymbol->YMasstab (),
									   pSymbol->GetWinkel (), 
									   dXOffset, dYOffset,
									   pGeoListe))
					return False;
			}
		}
	}
	
	return TRUE;
}

//	neues DGeoObjekt in Liste aufnehmen: als Objekt zum akt. Block (Namen) hinzufügen
//	Symbole werden zerlegt
Bool CBlockTree::AddObject (DGeoObj *&pObject)
{
	try
	{
	//	prüfe Parameter
		assert (pObject && m_pActBlockName && *m_pActBlockName);
		if (!pObject || !m_pActBlockName || !*m_pActBlockName)
		{
			yyerror (IDS_PARAM_ERROR);
			return True; //	weiter parsen
		}

	//	Block suchen
		CTable Tb (*this);
		if (!Tb.Find (m_pActBlockName))
		{
			assert (False);		//	das sollte eigentlich nicht passieren
			return True;
		}

	//	Objekt locken
		CBlockLock pBlock (Tb);		
		if (!pBlock)
		{
			yyerror (IDS_SYSERROR);
			return False;
		}
		
	//	Symbol wird an dieser Stelle zerlegt
		if (DGT_Symbol == pObject -> isA ())
			return Output ((CSymbolObject *)pObject, pBlock->GetDGeoObjListe ());
		else
			return pBlock->AddObject (pObject);
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}



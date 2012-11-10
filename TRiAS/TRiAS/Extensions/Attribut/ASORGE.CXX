//---------------ASORGE.CXX---------------------------------

#include "attribp.hxx"


#include <triastlb_i.c>
#include <triastlb.h>

#include <oleguid.h>
#include <dirisole.h>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

#include <shellapi.h>
#include <igeometr.hxx>

#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>

#include <igeometr.hxx>

#include "version.h"

#include "attribut.h" 
#include "about.h"
#include "define.h"

#include "about.hxx"
#include "idkey.hxx"    
#include "objkey.hxx"
#include "clstree.hxx"
#include "stohwnd.hxx"
#include "attinfo.hxx"
#include "erben.hxx"
#include "bilden.hxx"
#include "auswahl.hxx" 
#include "txtedit.hxx"
#include "mwerte.hxx"
#include "attribut.hxx"
//------Sorge ----------
//------------Jedem Merkmalswert Objekte zuordnen
short AttributExtension :: MerkmalVergleich ( void ) 
{
	short Number = 0;

	if ( !m_pOBJ)
		return 0;
	if ( !m_pMKM )
		return 0;
	ulong Count = m_pOBJ->Count();
	if ( Count == 0 )
		return 0;
	if ( m_pMVergl )
		DELETE ( m_pMVergl);

	m_pMVergl = new VClassTree;

	if ( ! m_pMVergl) 
		return 0;

	short iRange = 0;

 
	CEierUhr Wait( MWind());

	CTable t (*m_pOBJ);
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if (!l->ObjFlag())
			continue;
		BildeMerkmalBaum (ONr);
		iRange++;

	}
	if ( m_pMVergl) {
		char *pBuff = new char [_MAX_PATH];
		if ( !pBuff ) 
			return 0;
		if ( m_pMVergl->Count() ) {
			long lCount = (long) m_pMVergl->Count();
			wsprintf (pBuff, " %ld Klassen ", lCount);
			
			MessageBox ( 0 ,
			 pBuff, 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);
			Number = (short) m_pMVergl->Count();
		}
		DELETE ( pBuff);

	}

	return Number;
}
//--------------------------------------------------------------------------
void AttributExtension :: BildeMerkmalBaum (long ONr )
{
	if ( !m_pMKM)
		return;

	CTable t(*m_pMKM);
	char *pBuff1 = new char [_MAX_PATH];
	if ( !pBuff1 ) 
		return;

	t.First();
	IDMLock l(t);
	long lMCode = l->Ident();

	// MerkmalsWert holen
	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;

	tm.lMCode = lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pBuff1;		// Puffer

	if ( !DEX_GetTextMerkmal (tm) ) {
		DELETE ( pBuff1);
		return;
	}

//------Baum suchen------------------------------------

	if ( !pBuff1 || *pBuff1 == '\0' ) {
		DELETE ( pBuff1);
		return;
	}
	

	if ( !LadeMerkmalBaum ( pBuff1))
		return;


	CTable d(*m_pMVergl);

	if ( d.Find ( pBuff1) ) {
		VClassLock e(d);
		OBJTree *pObj = e->Obj();
		if (!pObj) {
			pObj = new OBJTree;
			if ( !pObj) {
				DELETE ( pBuff1);
				return;
			}
			e->StoreObjTree ( pObj);
		}

		CTable f(*pObj);
		if ( !f.Find ( &ONr)) {
			OBJECTTYP ObjStr;
			ObjStr.lIdent = DEX_GetObjIdent ( ONr );
			OBJCreator OBJCr ( *pObj );
			ContCreate ( OBJCr, OBJ ) ( ONr, &ObjStr);
		}
	}

	DELETE ( pBuff1);

	return;
}
//------------------------------------------------------------------------
	
bool AttributExtension :: LadeMerkmalBaum ( char *pMerkmal )
{
	if ( !m_pMVergl)
		return false;
	if ( !pMerkmal || *pMerkmal == '\0')
		return false;

	CTable d(*m_pMVergl);

	if ( !d.Find (pMerkmal)) {
		VClassCreator CLSCr ( *m_pMVergl );
		ContCreate ( CLSCr, VClass ) ( pMerkmal);
	}
	return true;
}

//---------------ASORGE.CXX---------------------------------

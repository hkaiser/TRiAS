//---------------OSORGE.CXX---------------------------------

#include "attribp.hxx"

#include <shellapi.h>

#include <igeometr.hxx>

// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>
#include <clipbrd.hxx>

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

void AttributExtension :: SorgesAblage ( void ) 
{

	if ( !m_pOBJ)
		return;

	ulong Count = m_pOBJ->Count();
	if ( Count == 0 )
		return;

	OBJTree *pTP = new OBJTree;
	if (!pTP)
		return;

	char *pBuff1 = new char [_MAX_PATH];
	char *pName = new char [_MAX_PATH];
	char *pKey = new char [_MAX_PATH];

	if ( !pBuff1 || !pName || !pKey) {
		DELETE ( pBuff1);
		DELETE ( pName);
		DELETE ( pKey);
		return;
	}

	CEierUhr Wait( MWind());

	CTable t (*m_pOBJ);
	short flag = true;
	for ( t.First(); t.Valid(); t.Next() ) {
		OBJLock l(t);
		long ONr = l->Object();	
		if ( flag ) {
			Nomenklatur( ONr,pBuff1);
			KreisName ( ONr, pKey, pName);
			flag = false;
		}

		BildeTPBaum (ONr,pTP);

	}
	DruckBild(pTP,pBuff1,pKey,pName);
	DELETE (pTP);
	DELETE ( pBuff1);
	DELETE ( pName);
	DELETE ( pKey);
	return;
}
//--------------------------------------------------------------------------
void AttributExtension :: BildeTPBaum ( long ONr , OBJTree *pTP)
{
	if ( !pTP)
		return;
	char *pBuff1 = new char [_MAX_PATH];
	if ( !pBuff1 ) 
		return;

	// MerkmalsWert holen
	long lMCode = 51400000;	// TP-Nr
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
	*(pBuff1+4) = '\0';
	long MCode = atol ( pBuff1);	// TP-Nummer

	lMCode = 51300000;	// KreisNr

	tm.lMCode = lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	*pBuff1 = '\0';
	if ( !DEX_GetTextMerkmal (tm) ) {
		DELETE ( pBuff1);
		return;
	}
	long Ident = atol ( pBuff1);

	CTable f(*pTP);
	if ( !f.Find ( &MCode)) {
		OBJECTTYP ObjStr;
		ObjStr.lIdent = Ident;	// KreisNummer
		ObjStr.lMCode = ONr;	// TRiAS - ONr
		OBJCreator OBJCr ( *pTP );
		ContCreate ( OBJCr, OBJ ) ( MCode, &ObjStr);
	}
	
	DELETE ( pBuff1);
	return;
}
//------------------------------------------------------------------------
//--------------------------------------------------------------------------
void AttributExtension :: DruckBild ( OBJTree *pTP, char *pNom, char *pKey, char *pName )
{
	if ( !pTP)
		return;


	short TPNumber = 0;
	short MaxTP = ( short ) TPZEILEN;

	char * pBuf = new char [ 2*MaxTP *_MAX_PATH ];
	if ( pBuf == NULL )
		return;

	CEierUhr Wait( MWind());

	{	//	ClipBoard

		CClipboard CLP;

		*pBuf = '\0';
		short Pos = 0;

		TPNumber = AusgabeClip ( Pos, pBuf, pTP, pNom, pKey, pName );

/*------------Laut Ausssage Sorge nicht notwendig - ErsatzPunkte ( > 50)

//-------------Anzahl der TP > MaxTP ????
		if ( TPNumber != (short) pTP->Count()) {
			
			MessageBox ( 0 ,
			 "2. Liste notwendig !!!", 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);	
			Pos = Pos + MaxTP;
//			strcat ( pBuf, "\n\n");
			short TPNum = AusgabeClip ( Pos, pBuf, pTP, pNom, pKey, pName );
			TPNumber = TPNumber + TPNum;
		}

		if ( TPNumber != (short) pTP->Count()) {

			MessageBox ( 0 ,
			 "Objekte noch nicht bearbeitet !!! ", 
			 "Merkmalsanalyse", 
			 MB_OK|MB_ICONEXCLAMATION);	
		}
----------------------------------------------------------------*/

		strcat ( pBuf, "\r");
		CLP.Insert ( pBuf );

	}

	DELETE ( pBuf);
	return;
}
//------------------------------------------------------------------------
short AttributExtension :: AusgabeClip ( short Pos, char *pBuf, OBJTree *pTP, char *pNom, char *pKey, char *pName )
{
	if ( !pBuf || !pTP || !pNom || !pName || !pKey)
		return 0;

short TPNumber = 0;

//------------KopfBeschreibung---------------------------	

	strcat ( pBuf, pName);
	strcat ( pBuf, "\n");
	strcat ( pBuf, pKey);
	strcat ( pBuf, "\n");

	strcat ( pBuf, pNom);
	strcat ( pBuf, "-A\t");
	strcat ( pBuf, pNom);
	strcat ( pBuf, "-B\t");
	strcat ( pBuf, pNom);
	strcat ( pBuf, "-C\t");
	strcat ( pBuf, pNom);
	strcat ( pBuf, "-D\n");

	CTable t ( *pTP);
	long S[4];
	S[0] = 1000;
	S[1] = 2000;
	S[2] = 3000;
	S[3] = 4000;
	char FKey[20];

	long Key = 0;
	long MaxTP = (long) TPZEILEN;

	for ( long i = 1; i < MaxTP+1; i++ ) {
		for ( long j = 0; j < 4; j++) {
			Key = S[j] + i + Pos;
			if ( t.Find ( &Key)) {
				OBJLock l(t);
				l->SetFlag();
				wsprintf ( FKey,"%ld",Key);
				strcat ( pBuf,FKey);
				strcat ( pBuf, "\t");		
				TPNumber++;
			} else {
				strcat ( pBuf, "\t");		
			}
			Key = Key + 100;
			if ( t.Find ( &Key)) {
				OBJLock l(t);
				l->SetFlag();
				wsprintf ( FKey,"%ld",Key);
				strcat ( pBuf,FKey);
				strcat ( pBuf, "\t");		
				TPNumber++;
			} else {
				strcat ( pBuf, "\t");		
			}
			Key = Key + 100;
			if ( t.Find ( &Key)) {
				OBJLock l(t);
				l->SetFlag();
				wsprintf ( FKey,"%ld",Key);
				strcat ( pBuf,FKey);
				strcat ( pBuf, "\t");		
				TPNumber++;
			} else {
				strcat ( pBuf, "\t");		
			}
			Key = Key + 100;
			if ( t.Find ( &Key)) {
				OBJLock l(t);
				l->SetFlag();
				wsprintf ( FKey,"%ld",Key);
				strcat ( pBuf,FKey);
				strcat ( pBuf, "\t");		
				TPNumber++;
			} else {
				strcat ( pBuf, "\t");		
			}
			Key = Key + 100;
			if ( t.Find ( &Key)) {
				OBJLock l(t);
				l->SetFlag();
				wsprintf ( FKey,"%ld",Key);
				strcat ( pBuf,FKey);
				strcat ( pBuf, "\t");		
				TPNumber++;
			} else {
				strcat ( pBuf, "\t");		
			}
		}
		char *ptr = strrchr ( pBuf, '\t');
		if ( ptr)
			*ptr = '\n';
	}
	return TPNumber;
}
//--------------------------------------------------------------------------
void AttributExtension :: Nomenklatur ( long ONr, char *pN)
{
	if ( !pN)
		return;
	*pN = '\0';

	char *pBuff1 = new char [_MAX_PATH];
	if ( !pBuff1 ) 
		return;


	// MerkmalsWert holen
	long lMCode = 51600000;	// DBF-Datei

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
	if ( strcmp ( pBuff1, "et310742") == 0 )
		strcpy ( pN, "N-32-107");
	if ( strcmp ( pBuff1, "et310842") == 0 )
		strcpy ( pN, "N-32-108");
	if ( strcmp ( pBuff1, "et312042") == 0 )
		strcpy ( pN, "N-32-120");

	if ( strcmp ( pBuff1, "et408542") == 0 )
		strcpy ( pN, "N-33-85");
	if ( strcmp ( pBuff1, "et408742") == 0 )
		strcpy ( pN, "N-33-87");
	if ( strcmp ( pBuff1, "et408842") == 0 )
		strcpy ( pN, "N-33-88");
	if ( strcmp ( pBuff1, "et408942") == 0 )
		strcpy ( pN, "N-33-89");

	if ( strcmp ( pBuff1, "et409742") == 0 )
		strcpy ( pN, "N-33-97");
	if ( strcmp ( pBuff1, "et409842") == 0 )
		strcpy ( pN, "N-33-98");
	if ( strcmp ( pBuff1, "et409942") == 0 )
		strcpy ( pN, "N-33-99");

	if ( strcmp ( pBuff1, "et410042") == 0 )
		strcpy ( pN, "N-33-100");
	if ( strcmp ( pBuff1, "et410142") == 0 )
		strcpy ( pN, "N-33-101");
	if ( strcmp ( pBuff1, "et410942") == 0 )
		strcpy ( pN, "N-33-109");
	if ( strcmp ( pBuff1, "et411042") == 0 )
		strcpy ( pN, "N-33-110");
	if ( strcmp ( pBuff1, "et411142") == 0 )
		strcpy ( pN, "N-33-111");
	if ( strcmp ( pBuff1, "et411242") == 0 )
		strcpy ( pN, "N-33-112");
	if ( strcmp ( pBuff1, "et411342") == 0 )
		strcpy ( pN, "N-33-113");

	if ( strcmp ( pBuff1, "et412142") == 0 )
		strcpy ( pN, "N-33-121");
	if ( strcmp ( pBuff1, "et412242") == 0 )
		strcpy ( pN, "N-33-122");
	if ( strcmp ( pBuff1, "et412342") == 0 )
		strcpy ( pN, "N-33-123");
	if ( strcmp ( pBuff1, "et412442") == 0 )
		strcpy ( pN, "N-33-124");
	if ( strcmp ( pBuff1, "et412542") == 0 )
		strcpy ( pN, "N-33-125");
	if ( strcmp ( pBuff1, "et412642") == 0 )
		strcpy ( pN, "N-33-126");

	if ( strcmp ( pBuff1, "et413342") == 0 )
		strcpy ( pN, "N-33-133");
	if ( strcmp ( pBuff1, "et413442") == 0 )
		strcpy ( pN, "N-33-134");
	if ( strcmp ( pBuff1, "et413542") == 0 )
		strcpy ( pN, "N-33-135");
	if ( strcmp ( pBuff1, "et413642") == 0 )
		strcpy ( pN, "N-33-136");
	if ( strcmp ( pBuff1, "et413742") == 0 )
		strcpy ( pN, "N-33-137");
	if ( strcmp ( pBuff1, "et413842") == 0 )
		strcpy ( pN, "N-33-138");

	if ( strcmp ( pBuff1, "et200242") == 0 )
		strcpy ( pN, "M-33-2");
	if ( strcmp ( pBuff1, "et200342") == 0 )
		strcpy ( pN, "M-33-3");
	if ( strcmp ( pBuff1, "et200442") == 0 )
		strcpy ( pN, "M-33-4");
	if ( strcmp ( pBuff1, "et200542") == 0 )
		strcpy ( pN, "M-33-5");
	if ( strcmp ( pBuff1, "et200642") == 0 )
		strcpy ( pN, "M-33-6");

	if ( strcmp ( pBuff1, "et201442") == 0 )
		strcpy ( pN, "M-33-14");
	if ( strcmp ( pBuff1, "et201542") == 0 )
		strcpy ( pN, "M-33-15");
	if ( strcmp ( pBuff1, "et201642") == 0 )
		strcpy ( pN, "M-33-16");
	if ( strcmp ( pBuff1, "et201742") == 0 )
		strcpy ( pN, "M-33-17");
	if ( strcmp ( pBuff1, "et201842") == 0 )
		strcpy ( pN, "M-33-18");
		
    DELETE ( pBuff1);
	return; 
}
//---------------------------------------------------------
//--------------------------------------------------------------------------
void AttributExtension :: KreisName ( long ONr, char * pK, char *pName)
{
	if ( !pName || !pK)
		return;
	*pName = '\0';
	*pK = '\0';

	// MerkmalsWert holen
	long lMCode = 51300000;	// KreisSchl.

	TARGETMERKMAL tm;

	tm.dwSize = sizeof(TARGETMERKMAL);
	tm.lTarget = ONr;		// ObjektNummer
	tm.iTTyp = TT_Objekt;

	tm.lMCode = lMCode;		// MerkmalsCode
	tm.imaxLen = _MAX_PATH;
	tm.pMText = pK;		// Puffer

	if ( !DEX_GetTextMerkmal (tm) ) {
		return;
	}

	if ( strcmp ( pK , "12051") == 0 )
		strcpy ( pName, "BrandenBurg an der Havel");
	if ( strcmp ( pK , "12052") == 0 )
		strcpy ( pName, "Cottbus");
	if ( strcmp ( pK , "12053") == 0 )
		strcpy ( pName, "Frankfurt/Oder");
	if ( strcmp ( pK , "12054") == 0 )
		strcpy ( pName, "Potsdam");

	if ( strcmp ( pK , "12060") == 0 )
		strcpy ( pName, "Barnim");
	if ( strcmp ( pK , "12061") == 0 )
		strcpy ( pName, "Dahme-Spreewald");
	if ( strcmp ( pK , "12062") == 0 )
		strcpy ( pName, "Elbe-Elster");
	if ( strcmp ( pK , "12063") == 0 )
		strcpy ( pName, "Havelland");
	if ( strcmp ( pK , "12064") == 0 )
		strcpy ( pName, "M‰rkisch-Oderland");
	if ( strcmp ( pK , "12065") == 0 )
		strcpy ( pName, "Oberhavel");
	if ( strcmp ( pK , "12066") == 0 )
		strcpy ( pName, "Oberspreewald-Lausitz");
	if ( strcmp ( pK , "12067") == 0 )
		strcpy ( pName, "Oder-Spree");
	if ( strcmp ( pK , "12068") == 0 )
		strcpy ( pName, "Ostprignitz-Ruppin");
	if ( strcmp ( pK , "12069") == 0 )
		strcpy ( pName, "Potsdam-Mittelmark");
	if ( strcmp ( pK , "12070") == 0 )
		strcpy ( pName, "Prignitz");
	if ( strcmp ( pK , "12071") == 0 )
		strcpy ( pName, "Spree-Neiﬂe");
	if ( strcmp ( pK , "12072") == 0 )
		strcpy ( pName, "Teltow-Fl‰ming");
	if ( strcmp ( pK , "12073") == 0 )
		strcpy ( pName, "Uckermark");

	return;
}
//---------------------------------------------------------
//---------------OSORGE.CXX---------------------------------

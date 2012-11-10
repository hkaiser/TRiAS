/*
Datei: TOOLS.CXX
Die beinhaltet allgemeine Funktionen zur Arbeit innerhalb der Komplexrecherche.

Erarbeitet:  J. Benkenstein						 Stand vom: 15.07.1993
*/

#include "pheader.h"

extern "C" {
	#include "komplexr.hr"	   // Resourcen-Defines
}

#include "tools.htp"			// Selektion der CommonView-Klassen
#include <commonvu.hxx>
#include <dbtools.hxx>			// GeteditName ()
#include "tools.hxx"			// zugeh. Header

//  externe Variablen
extern ResourceFile *pRF;

//  Text-Merkmal eines Objektes lesen
ErrCode GetMiText (long MKode, long ObjNr, char* &pBuffer, short BufferLen) {
//  Text-Puffer anlegen
	if (! (pBuffer = new char [BufferLen])) {
		DEX_Error (RC_GetMiText, EC_NOMEMORY);
		return EC_NOMEMORY;
	}

//  Merkmals-Feld anlegen
	TARGETMERKMAL Merkmal;

//  Merkmals-Feld init.
	memset (&Merkmal, 0, sizeof (TARGETMERKMAL));
	Merkmal.dwSize = sizeof (TARGETMERKMAL);
	Merkmal.lTarget = ObjNr;
	Merkmal.lMCode = MKode;
	Merkmal.imaxLen = BufferLen;
	Merkmal.pMText = pBuffer;
	Merkmal.iTTyp = TT_Objekt;

//  Merkmalswert von TRIAS lesen
	pBuffer = DEX_GetTextMerkmal (Merkmal);
	ErrCode EC = pBuffer ? EC_OKAY : WC_NOVALFOUND;
	if (EC == WC_NOVALFOUND)
		DELETE_VEC (pBuffer);

	return EC;
}


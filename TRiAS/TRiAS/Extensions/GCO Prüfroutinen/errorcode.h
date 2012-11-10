// $Header: $
// @module errorobject.h

#if !defined(_ERRORCODE_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_)
#define _ERRORCODE_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_


#include "resource.h"

//GCO-Struktur
//xx_x_xx_xxx_xxx_xxxxx_xxx
const short GCS_LENGTH = 25;

const short GCS_US[6] = { 2,4,7,11,15,21 };	// Position i-1

//xxx_xxx_xxxxx_xxx_...	verkürzt
const short GCS_USP[4] = {3,7,13,17};	// Position i-1


//--------------------------------------------------------------------------

//Fehlerarten beim GCS-Test
// Werte von ErrorMode 
#define GCS_NOTHING			0x01		//kein GCS-Code
#define GCS_SYNTAX 			0x02		//GCS-Syntax ( _...) falsch
#define GCS_DUPLICATE		0x04		//Doppelte/Mehrfache GCO-Nummer
#define GCS_OTHER			0x08		//GCS-Code in anderen Feld

#define GCS_DATA			0x0F

#define GCS_STREETCODEPOS	16		//Position Straßenschlüssel im GCS-Code 
#define GCS_PARTCODEPOS		12		//Position Ortsteil im GCS-Code 



#define GI_DUPLICATE		0x100		//Mehrfache Geometrie
#define GI_MULTI			0x200		//Überlappung
#define GI_DIFFERENT		0x400		//GI teilweise identisch

// SABIS  _ Fehler ab 0x1000

//Klassifikation der Prüfroutinen
#define PRF_CODE		1
#define PRF_DOPPELCODE	2
#define PRF_GEOMETRIE	3

//-------------------------------------------------------------------------
#define LINE_NOTCONTROL				0x01		//noch nichtreferenzierte Strassen
#define LINE_CTRLFEATURE			0x02		//noch alte Attribute belegt
#define LINE_CTRLINTERN				0x04		//noch interne Strassen

//-------------------------------------------------------------------------

// Merkmale eines Objektes enumerieren
typedef struct ObjFeat {
	DWORD dwSize;
	long lONr;
	long lMCode;
	int iTyp;
	const char *pCode;
} ObjFeat;

//-------------------------------------------------------------------------

//-------------------------------------------------------------------------



#endif // !defined(_ERRORCODE_H__E2054A33_4327_11D2_9EBE_006008447800__INCLUDED_)

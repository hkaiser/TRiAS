/*
Datei: HEADER.CXX

Das Modul beinhaltet eine Klasse zum Lesen/Schreiben des Headers
einer TRIAS-Datenbank.

erarbeitet : J. Benkenstein                              Stand vom 11. Mai 1995
*/
                      
#include "pheader.h"
                      
// #HK960812
	#include <resstrg.h>            	// TRIAS-Resourcen
	#include <math.h>					// fabs ()
	#include <xtensnn.h>

#include <hdrentrx.hxx>                 // HeaderEntryX

#define NOOPTPARAM
#include "optparam.hxx"                 // Params
#include "tools.hxx"                    // CreateMerkmal ()
#include "header.hxx"                   // zugeh. Header-File

// KK990906
#include <KoOrd.h>						// Maximale Koordinatengröße

//  Konstanten
const double CheckKonst = 10.0;
const ulong UniqueIdent = 51200000;			// Merkmalskode für unique Ident
const ulong TextObjMKode = 99999100;		// Merkmalskode für Textwert
const short UnIDLen = MaxFileSize + 20;		// max. Länge des zugeh. Merkmalstextes
const short TextObjLen = 100;				// max. Länge des zugeh. Merkmalstextes
const double MaxKoord = 1.0E+07;			// größte Koordinate
char HeaderDoubleFormat [] = "%10.10lf";    // voreingestelltes double-Format

//  externe Variablen
extern Params *pParams;

/*
//  globale Funktionen
pchar DtoA (double Val, pchar pBuffer) {
	gcvt (Val, 15, (char *) pBuffer);
	if (pBuffer [lstrlen (pBuffer) - 1] == '.')
		lstrcat (pBuffer, "0");
	return pBuffer;
}
*/

// Header ---------------------------------------------------------------------
// Ausgabe des Skalierungs-Vektors und des Offsets
Bool Header :: OutScaleAndOffset (double *pKoord) {
//  nur Ausgabe, wenn noch keine Enträge vorh.
	ResString HVar (ResID (IDS_KOEFF11), 20);

#if _TRiAS_VER >= 0x0300
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HeaderEntryX HD (HVar,hPr);
#else
	HeaderEntryX HD (HVar);
#endif
	if (HD.Status () != HE_INVALID)
		return True;

	double XMin = (*pKoord + pParams -> XOffset) * pParams -> Scaling;
	double YMin = (*++pKoord + pParams -> YOffset) * pParams -> Scaling;
	double XMax = (*++pKoord + pParams -> XOffset) * pParams -> Scaling;
	double YMax = (*++pKoord + pParams -> YOffset) * pParams -> Scaling;

	if ((XMax == XMin) || (YMax == YMin) || (XMax == YMax && XMin == YMin)) {
		DEX_Error (RC_HeaderOutScale, EC_NOSCALE);
		return False;
	}
	else 
	{
		XMin = Check (XMin, FALSE);		// Koordinaten runden
		YMin = Check (YMin, FALSE);
		XMax = Check (XMax, TRUE);
		YMax = Check (YMax, TRUE);

		// double dMaxKoord = max (abs (XMax), abs (YMax));
		//double Scale = fabs (MaxKoord / (XMax - XMin));
		//double ScaleY = fabs (MaxKoord / (YMax - YMin));
		//if (Scale > ScaleY)
		//	Scale = ScaleY;

// KK991006
		double dMaxKoord = (double) MAXKOORD;
		double Scale = max ( XMax,YMax);

		double dMulti = 1.0;
		double dScale = Scale;
		while ( dMaxKoord >= dScale ) {
			dMulti = dMulti*CheckKonst;
			dScale = Scale * dMulti;
		}

		Scale = dMulti / CheckKonst;


		Scale = 1 / Scale;                				// inverse Matrix !

		char Buffer [50] = "";

	//  Skalierung ausgeben
#if _TRiAS_VER >= 0x0300
		HeaderEntryX HD11 (HVar,hPr);  		// Koeff11
#else
		HeaderEntryX HD11 (HVar);  		// Koeff11
#endif
		HD11.SetEntryText (DtoA (Scale, Buffer, HeaderDoubleFormat));
		if (HD11.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF12), 20);     // Koeff12

#if _TRiAS_VER >= 0x0300
		HeaderEntryX HD12 (HVar,hPr);
#else
		HeaderEntryX HD12 (HVar);
#endif

		HD12.SetEntryText ("0.0");
		if (HD12.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF21), 20);     // Koeff21

#if _TRiAS_VER >= 0x0300
		HeaderEntryX HD21 (HVar,hPr);
#else
		HeaderEntryX HD21 (HVar);
#endif
		HD21.SetEntryText ("0.0");
		if (HD21.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF22), 20);     // Koeff22

#if _TRiAS_VER >= 0x0300
		HeaderEntryX HD22 (HVar,hPr);
#else
		HeaderEntryX HD22 (HVar);
#endif
		HD22.SetEntryText (Buffer);
		if (HD22.WriteBack () != EC_OKAY)
			return False;

	//  Offset ausgeben
		HVar = ResString (ResID (IDS_OFFSETX), 20);     // XMin


#if _TRiAS_VER >= 0x0300
		HeaderEntryX OX (HVar,hPr);
#else
		HeaderEntryX OX (HVar);
#endif

		OX.SetEntryText (DtoA (XMin, Buffer, HeaderDoubleFormat));
		if (OX.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_OFFSETY), 20);   	// YMin

#if _TRiAS_VER >= 0x0300
		HeaderEntryX OY (HVar,hPr);
#else
		HeaderEntryX OY (HVar);
#endif

		OY.SetEntryText (DtoA (YMin, Buffer, HeaderDoubleFormat));
		if (OY.WriteBack () != EC_OKAY)
			return False;

//		Änderung im Projekt nachziehen !

		short iFlag = True;

#if _TRiAS_VER >= 0x0300

		HVar = ResString (ResID (IDS_KOEFF11), 20);
		HeaderEntryX HD (HVar);

		if (HD.Status () == HE_INVALID) {

			HeaderEntryX HD11 (HVar);  		// Koeff11
			HD11.SetEntryText (DtoA (Scale, Buffer, HeaderDoubleFormat));
			if (HD11.WriteBack () != EC_OKAY)
				iFlag = False;

			HVar = ResString (ResID (IDS_KOEFF12), 20);     // Koeff12

			HeaderEntryX HD12 (HVar);

			HD12.SetEntryText ("0.0");
			if (HD12.WriteBack () != EC_OKAY)
				iFlag = False;

			HVar = ResString (ResID (IDS_KOEFF21), 20);     // Koeff21

			HeaderEntryX HD21 (HVar);
			HD21.SetEntryText ("0.0");
			if (HD21.WriteBack () != EC_OKAY)
				iFlag = False;

			HVar = ResString (ResID (IDS_KOEFF22), 20);     // Koeff22

			HeaderEntryX HD22 (HVar);
			HD22.SetEntryText (Buffer);
			if (HD22.WriteBack () != EC_OKAY)
				iFlag = False;

		//  Offset ausgeben
			HVar = ResString (ResID (IDS_OFFSETX), 20);     // XMin


			HeaderEntryX OX (HVar);

			OX.SetEntryText (DtoA (XMin, Buffer, HeaderDoubleFormat));
			if (OX.WriteBack () != EC_OKAY)
				iFlag = False;

			HVar = ResString (ResID (IDS_OFFSETY), 20);   	// YMin

			HeaderEntryX OY (HVar);

			OY.SetEntryText (DtoA (YMin, Buffer, HeaderDoubleFormat));
			if (OY.WriteBack () != EC_OKAY)
				iFlag = False;
		}
#endif

	//  hier noch TRIAS benachrichtigen, daß Scaling sich geändert hat
		DEXN_ReReadHeader ();
		DEXN_ReScale();
		return iFlag;
	}
}

Bool Header :: _GetMerkmalsKode (ulong &MK, char *pText) {
	HeaderEntryX HD (pText);
	if (HD.Status () != HE_INVALID)
	{
		MK = HD.EntryLong ();
		return True;
	}		

//  sonst neuen Eintrag erzeugen und speichern
	char Buffer [20] = "";
	ultoa (MK, Buffer, DEX_GetMkBase ());
	HD.SetEntryText (Buffer);
	if (HD.WriteBack () != EC_OKAY)  // Wert speichern
		return False;

	return True;
}

//  unique Ident lesen/erzeugen
//Bool Header :: GetUniqueIdent (ulong &MK) {
Bool Header :: GetUniqueIdent (ulong &MK, ulong ID) {


	ResString Text (ResID (IDS_UNIQUEIDENT), 30);
	MK = UniqueIdent;
// KK990927
	if ( 0 == ID)
		return True;

	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) &&
	   (CreateMerkmal (MK, (pchar) Text.Addr () , UnIDLen, ID) == EC_OKAY))
		return True;
	else		
		return False;
}

//Bool Header :: GetTextObjMKode (ulong &MK) {
Bool Header :: GetTextObjMKode (ulong &MK, ulong ID) {
	ResString Text (ResID (IDS_TEXTOBJMCODE), 30);
	MK = TextObjMKode;

// KK990927
	if ( 0 == ID)
		return True;

	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen, ID) == EC_OKAY))
		return True;
	else
		return False;		
}

//	Koordinaten runden
double Header :: Check (double dVal, BOOL bDirect)
{
	double dOldVal = dVal;		// alten Wert speichern
	
//	Exponent ber.	
	int iCnt = 0;
	dVal = fabs (dVal);
	while (floor (dVal) != 0.0)
	{
		dVal /= CheckKonst;
		iCnt++;
	}

	dVal = pow (CheckKonst, --iCnt);				// neuer Wert
	int iVal = (int)(double)(dOldVal / dVal);	// ganz. Teil

//	ggf. ganz. Teil ink.
	if ((dOldVal > 0) && bDirect)
		iVal++;
	else
	{
		if ((dOldVal < 0) && !bDirect)
			iVal--;
	}
	
	return (dVal * iVal);
}

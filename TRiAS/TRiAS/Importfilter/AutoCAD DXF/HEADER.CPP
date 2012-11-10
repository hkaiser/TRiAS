+/*
Datei: HEADER.CPP

Das Modul beinhaltet eine Klasse zum Lesen/Schreiben des Headers
einer TRIAS-Datenbank.

erarbeitet : J. Benkenstein        				Stand vom 21. August 1994
*/
                      
#include "pheader.hpp"

// #HK960812
	#include <resstrg.h>            	// TRIAS-Resourcen
	#include <math.h>					// fabs ()
	#include <xtensnn.h>				// DEXN_Rescale ()

// KK000125
#include <float.h>						// DBL_MAX

#include "dxfimp.h"

#include <hdrentrx.hxx>                 // HeaderEntryX
#include "optparam.hpp"                 // Params
#include "tools.hpp"                    // CreateMerkmal ()
#include "header.hpp"                   // zugeh. Header-File

// KK991006
#include "helptext.hpp"					// CHelpText
#include "numedit.hpp"					// Numedit
#include "realedit.hpp"          		// RealEdit
#include <KoOrd.h>						// Maximale Koordinatengröße
#include "optprdlg.hpp"					// OptParamsDlg
extern Params OptParams;				// globales Parameter-Halter-Objekt
// KK991006

//  Konstanten
const double CheckKonst = 10.0;			 // Koord-Container runden
const short UnIDLen = MaxFileSize + 20;  // max. Länge des zugeh. Merkmalstextes
const short TextObjLen = 100;            // max. Länge des zugeh. Merkmalstextes
//const double MaxKoord = 1.0E+07;         // größte Koordinate

char HeaderDoubleFormat [] = "%10.10lf";    // voreingestelltes double-Format
//const double ScaleFaktor = 0.30;			// Abmaße um 30% vergrößern

//	externe Variablen
extern double XMin;			// EXTMIN/EXTMAX
extern double YMin;
extern double XMax;
extern double YMax;

// KK000125	externe Variablen
extern double XLMin;		//LIMMIN/LIMMAX
extern double YLMin;
extern double XLMax;
extern double YLMax;

// externe Funktionen
char *DtoA (double Wert, char *String, char *Format = NULL); 
void yyerror (short);

// Header ---------------------------------------------------------------------
// Ausgabe des Offsets
Bool Header :: GetScaleAndOffset (void) {
// KK991007
//	Parameter-Dialog
	if ( !OptParams.m_bOffset) {
		double dMinX = OptParams.XOffset;
		double dMinY = OptParams.YOffset;

//		OptParams.XOffset = Check(XMin,False);
//		OptParams.YOffset = Check(YMin,False);

// KK000125
// Falls EXTMIN + EXTMAX nicht vorhanden , zu LIMMIN,LIMMAX wechseln!
		if ( XMin == DBL_MAX && YMin == DBL_MAX ) {
			XMin = XLMin;
			XMax = XLMax;
			YMin = YLMin;
			YMax = YLMax;
		}

		OptParams.XOffset = XMin;
		OptParams.YOffset = YMin;

		OptParamsDlg OP (g_pTE -> MWind (), & g_pTE -> RF (), &OptParams);
		if (OP.OpFlag ())
			OP.Show ();

		OptParams.XOffset = dMinX;
		OptParams.YOffset = dMinY;

		return OP.Result();
	
	} else {

		ResString HVar (ResID (IDS_OFFSETX), 20);     // XMin

	#if _MSC_VER >= 1100
		HPROJECT hPr = DEX_GetDataSourceHandle();
		HeaderEntryX HD_X (HVar,hPr);
	#else
		HeaderEntryX HD_X (HVar);
	#endif

		if (HD_X.Status () != HE_INVALID) {			// Header in Datenquelle vorhanden

			ResString HVar (ResID (IDS_OFFSETY), 20);

		#if _MSC_VER >= 1100
			HeaderEntryX HD_Y (HVar,hPr);
		#else
			HeaderEntryX HD_Y (HVar);
		#endif

		//  X/Y-Offset der Datenquelle
			double dHeadX = atof (HD_X.EntryText ());
			double dHeadY = atof (HD_Y.EntryText ());

			if (dHeadX > XMin || dHeadY > YMin) 
				return False;
		}
	}

// KK991007

	return True;
}
// Header ---------------------------------------------------------------------
// Ausgabe des Skalierungs-Vektors und des Offsets
Bool Header :: OutScaleAndOffset (void) {

//  nur Ausgabe, wenn noch keine Enträge vorh.
	ResString HVar (ResID (IDS_KOEFF11), 20);

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HeaderEntryX HD (HVar,hPr);
#else
	HeaderEntryX HD (HVar);
#endif

	if (HD.Status () != HE_INVALID)			// Header in Datenquelle vorhanden
		return True;

	if ((XMax == XMin) || (YMax == YMin)) 
	{
		// DEX_Error (RC_HeaderOutScale, EC_NOSCALE);
		yyerror (IDS_BILDM_ERR);
		return False;
	}
	else 
	{

	// Erst einmal bei einstelligem Runden belassen ! Später Koord.Systeme unterscheiden
		XMin = Check (XMin, FALSE);		// Koordinaten runden
		YMin = Check (YMin, FALSE);
		XMax = Check (XMax, TRUE);
		YMax = Check (YMax, TRUE);

		//double Scale = fabs (MaxKoord / (XMax - XMin));
		//double ScaleY = fabs (MaxKoord / (YMax - YMin));
		//double dMaxKoord = max (abs (XMax), abs (YMax));

	//	double Scale = fabs (MaxKoord / (XMax - XMin));
	//	double ScaleY = fabs (MaxKoord / (YMax - YMin));
	//	Scale = min (Scale, ScaleY);
	//	Scale = 1 / Scale;  		// inverse Matrix !

// KK991006
		double dMaxKoord = (double) MAXKOORD;

		//double Scale = fabs (dMaxKoord / (XMax - XMin));
		//double ScaleY = fabs (dMaxKoord / (YMax - YMin));
		
		//Scale = min (Scale, ScaleY);
		double Scale = max ( XMax,YMax);

		double dMulti = 1.0;
		double dScale = Scale;
		while ( dMaxKoord >= dScale ) {
			dMulti = dMulti*CheckKonst;
			dScale = Scale * dMulti;
		}

		Scale = dMulti / CheckKonst;
		
		Scale = 1 / Scale;  		// inverse Matrix !

		
	//  Skalierung ausgeben
		char Buffer [50] = "";

	// Header Datenquelle füllen
#if _MSC_VER >= 1100
		HeaderEntryX HD11 (HVar,hPr);                      	// Koeff11
#else
		HeaderEntryX HD11 (HVar);                      	// Koeff11
#endif

		HD11.SetEntryText (DtoA (Scale, Buffer, HeaderDoubleFormat));
		if (HD11.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF12), 20);     // Koeff12

#if _MSC_VER >= 1100
		HeaderEntryX HD12 (HVar,hPr);
#else
		HeaderEntryX HD12 (HVar);                      	// Koeff12
#endif

		HD12.SetEntryText ("0.0");
		if (HD12.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF21), 20);     // Koeff21

#if _MSC_VER >= 1100
		HeaderEntryX HD21 (HVar,hPr);
#else
		HeaderEntryX HD21 (HVar);
#endif

		HD21.SetEntryText ("0.0");
		if (HD21.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_KOEFF22), 20);     // Koeff22

#if _MSC_VER >= 1100
		HeaderEntryX HD22 (HVar,hPr);
#else
		HeaderEntryX HD22 (HVar);
#endif

		HD22.SetEntryText (Buffer);
		if (HD22.WriteBack () != EC_OKAY)
			return False;

	//  Offset ausgeben
		HVar = ResString (ResID (IDS_OFFSETX), 20);     // XMin

#if _MSC_VER >= 1100
		HeaderEntryX OX (HVar,hPr);
#else
		HeaderEntryX OX (HVar);
#endif

		OX.SetEntryText (DtoA (XMin, Buffer, HeaderDoubleFormat));
		if (OX.WriteBack () != EC_OKAY)
			return False;

		HVar = ResString (ResID (IDS_OFFSETY), 20);   	// YMin

#if _MSC_VER >= 1100
		HeaderEntryX OY (HVar,hPr);
#else
		HeaderEntryX OY (HVar);
#endif

		OY.SetEntryText (DtoA (YMin, Buffer, HeaderDoubleFormat));
		if (OY.WriteBack () != EC_OKAY)
			return False;

//		Änderung im Projekt nachziehen !
		short iFlag = true;

#if _MSC_VER >= 1100

		HVar = ResString (ResID (IDS_KOEFF11), 20);
		HeaderEntryX HD (HVar);


		if (HD.Status () == HE_INVALID) {		// Projektheader nicht vorhanden

			HeaderEntryX HD11 (HVar);                      	// Koeff11

			HD11.SetEntryText (DtoA (Scale, Buffer, HeaderDoubleFormat));
			if (HD11.WriteBack () != EC_OKAY)
				iFlag = false;

			HVar = ResString (ResID (IDS_KOEFF12), 20);     // Koeff12

			HeaderEntryX HD12 (HVar);                      	// Koeff12

			HD12.SetEntryText ("0.0");
			if (HD12.WriteBack () != EC_OKAY)
				iFlag = false;

			HVar = ResString (ResID (IDS_KOEFF21), 20);     // Koeff21

			HeaderEntryX HD21 (HVar);


			HD21.SetEntryText ("0.0");
			if (HD21.WriteBack () != EC_OKAY)
				iFlag = false;

			HVar = ResString (ResID (IDS_KOEFF22), 20);     // Koeff22

			HeaderEntryX HD22 (HVar);


			HD22.SetEntryText (Buffer);
			if (HD22.WriteBack () != EC_OKAY)
				iFlag = false;

	//  Offset ausgeben
			HVar = ResString (ResID (IDS_OFFSETX), 20);     // XMin

			HeaderEntryX OX (HVar);


			OX.SetEntryText (DtoA (XMin, Buffer, HeaderDoubleFormat));
			if (OX.WriteBack () != EC_OKAY)
				iFlag = false;

			HVar = ResString (ResID (IDS_OFFSETY), 20);   	// YMin

			HeaderEntryX OY (HVar);


			OY.SetEntryText (DtoA (YMin, Buffer, HeaderDoubleFormat));
			if (OY.WriteBack () != EC_OKAY)
				iFlag = false;
			
		}
#endif


	//  hier noch TRIAS benachrichtigen, daß Scaling sich geändert hat
		DEXN_ReReadHeader ();
		DEXN_ReScale();
		return iFlag;
	}
}

Bool Header :: _GetMerkmalsKode (ulong &MK, char *pText) 
{

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HeaderEntryX HD (pText,hPr);
#else
	HeaderEntryX HD (pText);
#endif

	if (HD.Status () != HE_INVALID)
	{
		MK = HD.EntryLong ();

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
		long lMKode = MK;
		MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif
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

Bool Header :: MatrixExists (void)
{
	ResString HVar (ResID (IDS_KOEFF11), 20);

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HeaderEntryX HD (HVar,hPr);
#else
	HeaderEntryX HD (HVar);
#endif

	if (HD.Status () != HE_INVALID)
		return True;
	else
		return False;
}

//  unique Ident lesen/erzeugen
// KK990927
//Bool Header :: GetUniqueIdent (ulong &MK) 
Bool Header :: GetUniqueIdent (ulong &MK,ulong ID) 
{

// KK 990927 - Blödsinn KK000608
/*-----
#if _MSC_VER >= 1100
	if ((MK == 0) || (MK == -1)) {
		if ( 0 == ID)
			HPROJECT hPr = DEX_GetDataSourceHandle();
		else
			HPROJECT hPr = DEX_GetObjectsProject(ID);

		MK = DEX_GetUniqueIdentMCodeEx (hPr);
	}

// KK000608 -----------------------------------
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------

#else
	if ((MK == 0) || (MK == -1)) {
		MK = DEX_GetUniqueIdentMCode ();
	}
#endif
-------------------------------------------------------------*/

	if ( 0L == ID)
		return True;

	if ((MK == 0) || (MK == -1))
	{
		ResString Text (ResID (IDS_UNIQUEIDENT), 30);
		MK = UniqueIdent;

#if _MSC_VER >= 1100
		HPROJECT hPr = DEX_GetObjectsProject(ID);

// KK000608 -----------------------------------
		long lMKode = MK;
		MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif

		if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) &&
//	   	(CreateMerkmal (MK, (pchar) Text.Addr () , UnIDLen) == EC_OKAY))
	   	(CreateMerkmal (MK, (pchar) Text.Addr () , UnIDLen, ID) == EC_OKAY))
			return True;
		else		
			return False;
	}
	else
		return True;
}

// KK990927
//Bool Header :: GetTextObjMKode (ulong &MK) 
Bool Header :: GetTextObjMKode (ulong &MK,ulong ID) 
{

	if ( 0L == ID)
		return True;

	ResString Text (ResID (IDS_TEXTOBJMCODE), 30);
	if ((MK == 0) || (MK == -1)) 
		MK = TextObjMKode;

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif


	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
//	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen) == EC_OKAY))
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen,ID) == EC_OKAY))
		return True;
	else
		return False;		
}

// KK990927
//Bool Header :: GetTextObjWinkel (ulong &MK) 
Bool Header :: GetTextObjWinkel (ulong &MK,ulong ID) 
{

	if ( 0L == ID)
		return True;

	ResString Text (ResID (IDS_TEXTOBJWINKEL, &g_pTE -> RF()), 30);
	if ((MK == 0) || (MK == -1)) 
		MK = DEX_GetUniqueSysMCode();

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif

	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
//	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen) == EC_OKAY))
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen, ID) == EC_OKAY))
		return True;
	else
		return False;		
}

// KK990927
//Bool Header :: GetTextObjHoehe (ulong &MK) 
Bool Header :: GetTextObjHoehe (ulong &MK,ulong ID) 
{

	if ( 0L == ID)
		return True;

	ResString Text (ResID (IDS_TEXTOBJHOEHE, &g_pTE -> RF()), 30);
	if ((MK == 0) || (MK == -1)) 
		MK = DEX_GetUniqueSysMCode();

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif


	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
//	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen) == EC_OKAY))
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen, ID) == EC_OKAY))
		return True;
	else
		return False;		
}

// KK990927
//Bool Header :: GetSymObjWinkel (ulong &MK) 
Bool Header :: GetSymObjWinkel (ulong &MK,ulong ID) 
{

	if ( 0L == ID)
		return True;

	ResString Text (ResID (IDS_SYMBOLOBJWINKEL, &g_pTE -> RF()), 30);
	if ((MK == 0) || (MK == -1)) 
		MK = DEX_GetUniqueSysMCode();

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif


	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
//	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen) == EC_OKAY))
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen, ID) == EC_OKAY))
		return True;
	else
		return False;		
}

// KK990927
//Bool Header :: GetComment (ulong &MK) 
Bool Header :: GetComment (ulong &MK,ulong ID) 
{

	if ( 0L == ID)
		return True;

	ResString Text (ResID (IDS_COMMENTKODE, &g_pTE -> RF()), 30);
	if ((MK == 0) || (MK == -1)) 
		MK = DEX_GetUniqueSysMCode();

// KK000608 -----------------------------------
#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetObjectsProject(ID);
	long lMKode = MK;
	MK = DEX_MapMCodeToHandle(hPr,lMKode);
// --------------------------------------------
#endif


	if (_GetMerkmalsKode (MK, (char *) Text.Addr ()) && 
//	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen) == EC_OKAY))
	   (CreateMerkmal (MK, (pchar) Text.Addr (), TextObjLen, ID) == EC_OKAY))
		return True;
	else
		return False;		
}

Bool Header::SetTextFlag (void)
{

	ResString Text (ResID (IDS_POSTEXTATBASELINE, &g_pTE -> RF()), 30);

#if _MSC_VER >= 1100
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HeaderEntryX PosTxt (Text,hPr);
#else
	HeaderEntryX PosTxt (Text);
#endif

	if (PosTxt.Status () != HE_INVALID)
		return True;

	PosTxt.SetEntryText ("1");
	if (PosTxt.WriteBack() != EC_OKAY)
		return false;
return true;
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
//--------------------------------------------------------------------------


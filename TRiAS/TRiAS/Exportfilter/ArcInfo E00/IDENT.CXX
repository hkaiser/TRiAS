/*
File: IDENT.CXX
realiert die Verwaltung eines Identifikator-Beschreibungs-Baumes
für den Arc/Info-Filter.

erarbeitet : J. Benkenstein				 Begonnen am 4. Mai 1993
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

extern "C" {
	#include <io.h>		 	// setmode ()
	#include <fcntl.h>	  	// O_TEXT
	#include <xtensnxx.h>   	// DEXX_MAINWINDOW
}

#include <attribs.hxx>		// VisInfo ...
#include <impexp.hxx>		// IdentDescription
#include <ristypes.hxx>		// OT_PUNKT, OT_KANTE, OT_FLAECHE, OT_TEXT
#include <strdup.hxx>		// StringDup ()

//XX #include "triasarc.hr"		// Resource-IDs
#include "triasarc.hxx"		// FileNameSize, CheckName ()
#include "section.hxx"		// Section u.a.
#include "info.hxx"			// PatTable 
#include "cover.hxx"		// Cover, TexteCover u.a.
#include "numedit.hxx"		// NumEdit
#include "helptext.hxx"		// CHelpText
#include "expparam.hxx"		// Export-Parameter bestimmen
#include "ident.hxx"		// zugeh. Header-File

//	Konstanten
const short StandartHoehe = 10;

//  externe Variablen 
extern Bool FourCoverages;	// Ausgabe in 4 Coverages-Flag ?	
extern ResourceFile *pRF;
extern "C" {
extern HWND __hWndM;
extern UINT __DexxCmd;
}

//  globale Funktionen -------------------------------------------------------
//  - ggf. DOS-String erzeugen
//  - Konvertierung in Großbuchstaben
//  - deutsche Umlaute und "ß" ersetzen
//  - Zeiger auf neuen Namen liefern (muß über delete freigegeben werden)
//  - 1. Zeichen muß Buchstabe sein
//  - abschließende "_" löschen
pchar CheckName (pchar pName, short MaxSize, Bool Konvert) {
//  Parameter prüfen
	if (!pName || !*pName)
		return NULL;

//  ggf. DOS-String erzeugen
	if (Konvert)
		AnsiToOem (pName, pName);

//  Puffer für Dateinamen anfordern
	pchar pOldName = new char [MaxSize + 1];
	if (!pOldName)
		return NULL;
	lstrcpyn (pOldName, pName, min (MaxSize, lstrlen (pName))+1);
	strupr (pOldName);

//  Zielpuffer anfordern, Platz für Umlautekonvertierung
	pchar pNewName = new char [(2 * MaxSize) + 1];
	if (!pNewName) {
		DELETE_VEC (pOldName);
		return NULL;
	}
	*pNewName = '\0';

//  Zeiger merken
	pchar pNewNameSave = pNewName;
	pchar pOldNameSave = pOldName;

//  Ist das 1. Zeichen eine Ziffer ?
	if (*pOldName < 'A' || *pOldName > 'Z') {
		*pNewName++ = 'A';
		pOldName++;
	}

//  deutsche Umlaute und "ß" ersetzen
	while (*pOldName) {
		if ((*pOldName >= '0' && *pOldName <= '9') ||
			(*pOldName >= 'A' && *pOldName <= 'Z')) {
			*pNewName++ = *pOldName++;
			continue;
		}
		switch (*pOldName) {
			case 'á':
				*pNewName++ = 'S';
				*pNewName = 'S';
			break;
			case '„':
			case 'Ž':
				*pNewName++ = 'A';
				*pNewName = 'E';
			break;
			case '':
			case 'š':
				*pNewName++ = 'U';
				*pNewName = 'E';
			break;
			case '”':
			case '™':
				*pNewName++ = 'O';
				*pNewName = 'E';
			break;
			default:
				*pNewName = '_';
		}
		pNewName++;
		pOldName++;
	}   // end while

	*pNewName = '\0';		   // akt. Ende setzen
	*(pNewNameSave + MaxSize) = '\0';	// max. Länge nicht übers.
	DELETE_VEC (pOldNameSave);		 // alten Puffer löschen

//  abschließende "_" löschen
	pOldName = pNewNameSave + lstrlen (pNewNameSave);
	while (--pOldName > pNewNameSave && *pOldName == '_')
		   *pOldName = '\0';

	return pNewNameSave;		   // mit neuem Namen zurück
}

// GetKey-Funktion für erw. ID-Baum
void* GetExtID (void *pObj)
{
	return & (((ExtIdentDescription *) pObj) -> ID ());
}

// KeyCompare-Funktion für ID-Baum
int CompareExtIDs (void *pObj1, void *pObj2)
{
	long ID1 = *((long *) pObj1);
	long ID2 = *((long *) pObj2);

	if (ID1 == ID2)
		return 0;
	else
		if (ID1 > ID2)
			return 1;
		else
			return -1;
}

//  ExtIdentDescription -----------------------------------------------------
//  Filenamen bilden und speichern, _RC wird gesetzt
ExtIdentDescription :: ExtIdentDescription (IdentDescription &IDD)
					 : IdentDescription (IDD) {
	_pCover = NULL;
	_pFileName = NULL;

//  internen Typ erzeugen
	VisInfo *pVI = &IDD.VisInfoObj ();
/*
	if (!pVI) {
		_RC = WC_UNKOBJECTTYP;
		return;
	}
*/
	if (pVI)
	{
		switch (pVI -> isA ()) 
		{
			case VT_Punkt :
				_Typ = 'P';
			break;
			case VT_Linie :
				_Typ = 'L';
			break;
			case VT_Flaeche :
				_Typ = 'F';
			break;
			case VT_Text :
				_Typ = 'T';
			break;
			case VT_Default:
			default: 
			{
				_Typ = 'U';				 // unbekannt
				_RC = WC_UNKOBJECTTYP;
				return;
			}
		}
	}
	else
		_Typ = 'U';

	_pFileName = CheckName (KurzText (), FileNameSize);
	_pKurzText = CheckName (KurzText (), KurzTextLen);
	_RC = _pFileName && _pKurzText ? EC_OKAY : EC_NOMEMORY;
}

//  angeforderten Speicher freigeben
ExtIdentDescription :: ~ExtIdentDescription (void) {
	DELETE_OBJ (_pCover);
	DELETE_VEC (_pFileName);           
	DELETE_VEC (_pKurzText);
}

//  Cover hat Daten ?
Bool ExtIdentDescription :: hasData (void) {
	return _pCover -> hasData ();
}

//  Cover löschen
ErrCode ExtIdentDescription :: DeleteFile (void) {
	if (!_pCover)
		return EC_LOCKERROR;
	return _pCover -> DeleteCover ();
}

//  eigentlichen Daten ausgeben
ErrCode ExtIdentDescription :: OutputData (GSTRUCT &GS, MFELD *pMF) {
	return _pCover -> OutputData (GS, pMF);
}

//  Coverages-Initialisierung
ErrCode ExtIdentDescription :: OutputFirstData (void) {
	return _pCover -> OutputFirstData ();
}

//  abschl. Infos in Coverages ausgeben
ErrCode ExtIdentDescription :: OutputLastData (void) {
//	return _pCover -> OutputLastData ();
	ErrCode EC = _pCover -> OutputLastData ();
	if ( EC == EC_OKAY)
		return _pCover -> TransferTempDaten ();
	else
		return EC;

}

//  ImportMakro-Zeile ausgeben
ErrCode ExtIdentDescription :: OutputImportMakro (int fh) {
	return _pCover -> OutputImportMakro (fh);
}

//  zugehörige Arc/Info-Cover erzeugen
ErrCode ExtIdentDescription :: CreateCover (pchar pPath) {
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char NewPath [_MAX_PATH] = "";
	_splitpath (pPath, Drive, Dir, NULL, NULL);
	_makepath (NewPath, Drive, Dir, _pFileName, NULL);

//  Arc/Info-Cover erzeugen
	VisInfo *pVI = &VisInfoObj ();
	if (!pVI)
		return (_RC = WC_UNKOBJECTTYP);

	switch (pVI -> isA ()) {
		case VT_Punkt :
			_pCover = new PointCover (NewPath);
		break;
		case VT_Linie :
			_pCover = new ArcCover (NewPath);
		break;
		case VT_Flaeche :
			_pCover = new PolyCover (NewPath);
		break;
		case VT_Text :
			_pCover = new TexteCover (NewPath);
		break;
		case VT_Default:
		default:
			return (_RC = WC_UNKOBJECTTYP);
	}

	if (!_pCover)   // wenn kein Speicher mehr vorhanden
		return (_RC = EC_NOMEMORY);

	return (_RC = EC_OKAY);
}

//  lesen des Covernamens, _RC setzen
pchar ExtIdentDescription :: GetCoverName (void) {
	pchar pFileName = StrDup (_pFileName, RC_TRIASARC);
	_RC = pFileName ? EC_OKAY : EC_NOMEMORY;
	return pFileName;
}

//  Covernamen neu setzen, _RC setzen
pchar ExtIdentDescription :: SetCoverName (pchar pNewCoverName) {
	DELETE_VEC (_pFileName);
	_RC = (_pFileName = StrDup (pNewCoverName, RC_TRIASARC)) ? EC_OKAY :
		  EC_NOMEMORY;
	return _pFileName;
}

// ExtIdentDescriptionTree --------------------------------------------------
// ID-Beschreibungs-Baum anlegen
ExtIdentDescriptionTree :: ExtIdentDescriptionTree (void)
						 : CTree (GetExtID, CompareExtIDs) {
	_pPolyCover = NULL;
	_pArcCover = NULL;
	_pTexteCover = NULL;
	_pPointCover = NULL;						 
}

void EXPORTFLT ExtIdentDescriptionTree :: UserDelete (void *pObj) {
	((ExtIdentDescription *) pObj) -> ~ExtIdentDescription ();
}

ExtIdentDescriptionTree :: ~ ExtIdentDescriptionTree (void) {
	DELETE_OBJ (_pPolyCover);	
	DELETE_OBJ (_pArcCover);	
	DELETE_OBJ (_pTexteCover);	
	DELETE_OBJ (_pPointCover);	
	
	EveryDelete ();
}

// neue ID-Beschr. in Baum
ErrCode ExtIdentDescriptionTree :: AddIDD (IdentDescription &IDD) {
	CTable Tb (*this);
	VisInfo *pViNew = &IDD.VisInfoObj ();
	VisInfo *pViOld = NULL;
	for (Tb.FindFirst (&IDD.ID ()); Tb.Valid (); Tb.FindNext (&IDD.ID ())) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return EC_LOCKERROR;
		
		pViOld = &pIDD -> VisInfoObj ();

	//	beide ObjInfos fehlen
		if (!pViOld && !pViNew)
			return EC_OKAY;	
		
	//	beide vorhanden und gleich ?
		if (pViNew && pViOld && (pViNew -> isA () == pViOld -> isA()))
			return EC_OKAY;
	}

//  neuen Eintrag erzeugen
	ExtIdentDescriptionCreator IDD_Cr (*this);
//XX	ExtIdentDescription *pEID = Create (IDD_Cr, ExtIdentDescription) (IDD);
/*XX*/	ExtIdentDescription *pEID = ContCreate (IDD_Cr, ExtIdentDescription) (IDD);
	if (pEID)   
		return pEID -> Result ();
	else
		return EC_NOMEMORY;
}

//  eigentlichen Daten ausgeben
ErrCode ExtIdentDescriptionTree :: OutputData (GSTRUCT &GS, MFELD *pMF) {
	Bool Found = False;
	CTable Tb (*this);
	VisInfo *pVI = NULL;
	short sTyp;
	for (Tb.FindFirst (&GS.Id); Tb.Valid (); Tb.FindNext (&GS.Id)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return EC_LOCKERROR;

		pVI = &pIDD -> VisInfoObj ();
		if (pVI)
			sTyp = pVI -> isA ();
		switch (GS.Typ) {
			case OT_KANTE:         
				if ((pVI && sTyp == VT_Linie) || !pVI)
				{
					if (FourCoverages)
						return _pArcCover -> OutputData (GS, pMF, pIDD -> IdentKurzText ());
					Found = True;
				}										
			break;
			case OT_PUNKT:
				if ((pVI && sTyp == VT_Punkt) || !pVI)
				{
					if (FourCoverages)
						return _pPointCover -> OutputData (GS, pMF, pIDD -> IdentKurzText ());
					Found = True;
				}					
			break;
			case OT_FLAECHE:
				if ((pVI && sTyp == VT_Flaeche) || !pVI)
				{
					if (FourCoverages)
						return _pPolyCover -> OutputData (GS, pMF, pIDD -> IdentKurzText ());
					Found = True;
				}					
			break;
			case OT_TEXT:
				if ((pVI && sTyp == VT_Text) || !pVI)
				{
					if (FourCoverages)
						return _pTexteCover -> OutputData (GS, pMF);
					Found = True;
				}					
			break;
			default:
			break;
		}

	//  wenn ID gefunden
		if (Found)
			return pIDD -> OutputData (GS, pMF);	// Daten ausgeben
	}

	return EC_SYSERROR;
}

//  Coverages-Initialisierung
ErrCode ExtIdentDescriptionTree :: OutputFirstData (pchar pPath) {
	ErrCode EC = EC_OKAY;
	
//	wenn nur Ausgabe in 4 Coverages	
	if (FourCoverages)
	{             
		char Drive   [_MAX_DRIVE]   = "";
		char Dir	 [_MAX_DIR]		= "";
		char FName   [_MAX_FNAME]   = "";
		char pNewPath[_MAX_PATH]	= "";

	//	Namen für Flächencover bilden		
		_splitpath (pPath, Drive, Dir, FName, NULL);
		pchar pFileName = CheckName (FName, FileNameSize);		
		if ((lstrlen (pFileName) + 2) <= FileNameSize)
			lstrcat (pFileName, "_f");
		else
			lstrcpy ((pFileName + FileNameSize - 2), "_f");
		_makepath (pNewPath, Drive, Dir, pFileName, NULL);
					
	//	FlächenCover erzeugen			
		_pPolyCover = new PolyCover (pNewPath);
		if (!_pPolyCover || ((EC = _pPolyCover -> Result ()) != EC_OKAY))
		{
			DELETE_VEC (pFileName);
			return EC;			
		}
		
		if ((EC = _pPolyCover -> OutputFirstData ()) != EC_OKAY)
		{                   
			DELETE_VEC (pFileName);
			return EC;		
		}			
							
	//	Namen für LinienCover bilden
		lstrcpy (pFileName + lstrlen (pFileName) - 2, "_l");								
		_makepath (pNewPath, Drive, Dir, pFileName, NULL);		
		
	//	LinienCover erzeugen
		_pArcCover = new ArcCover (pNewPath);
		if (!_pArcCover || ((EC = _pArcCover -> Result ()) != EC_OKAY))
		{
			DELETE_VEC (pFileName);
			return EC;			
		}
		
		if ((EC = _pArcCover -> OutputFirstData ()) != EC_OKAY)
		{                   
			DELETE_VEC (pFileName);
			return EC;		
		}							
		
	//	Namen für PunktCover bilden
		lstrcpy (pFileName + lstrlen (pFileName) - 2, "_p");								
		_makepath (pNewPath, Drive, Dir, pFileName, NULL);		
		
	//	PunkteCover erzeugen
		_pPointCover = new PointCover (pNewPath);
		if (!_pPointCover || ((EC = _pPointCover -> Result ()) != EC_OKAY))
		{
			DELETE_VEC (pFileName);
			return EC;			
		}
		
		if ((EC = _pPointCover -> OutputFirstData ()) != EC_OKAY)
		{                   
			DELETE_VEC (pFileName);
			return EC;		
		}	

	//	Namen für TexteCover bilden
		lstrcpy (pFileName + lstrlen (pFileName) - 2, "_t");								
		_makepath (pNewPath, Drive, Dir, pFileName, NULL);		
		
	//	TexteCover erzeugen
		_pTexteCover = new TexteCover (pNewPath);
		if (!_pTexteCover || ((EC = _pTexteCover -> Result ()) != EC_OKAY))
		{
			DELETE_VEC (pFileName);
			return EC;			
		}
		
		if ((EC = _pTexteCover -> OutputFirstData ()) != EC_OKAY)
		{                   
			DELETE_VEC (pFileName);
			return EC;		
		}							
		
		DELETE_VEC (pFileName);		
		return EC;
	}
	
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) 
	{
		ExtIdentDescriptionLock pIDD (Tb);
		if (pIDD) 
		{
			if ((EC = pIDD -> CreateCover (pPath)) != EC_OKAY)
				return EC;
			if ((EC = pIDD -> OutputFirstData ()) != EC_OKAY)
				return EC;
		} 
		else
			return EC_SYSERROR;
	}

	return EC_OKAY;
}

//  abschl. Infos in Coverages ausgeben
ErrCode ExtIdentDescriptionTree :: OutputLastData (void) {
	ErrCode EC = EC_OKAY; 
	
	if (FourCoverages)
	{                           
		if (_pPolyCover -> hasData ())
		{
			if ((EC = _pPolyCover -> OutputLastData ()) != EC_OKAY)
				return EC;		
// KK000404
			_pPolyCover -> TransferTempDaten ();

		}
		else
			_pPolyCover -> DeleteCover ();						
						
		if (_pArcCover -> hasData ())
		{				
			if ((EC = _pArcCover -> OutputLastData ()) != EC_OKAY)
					return EC;		
// KK000404
			_pArcCover -> TransferTempDaten ();
		}
		else
			_pArcCover -> DeleteCover ();
			
		if (_pPointCover -> hasData ())
		{								
			if ((EC = _pPointCover -> OutputLastData ()) != EC_OKAY)
					return EC;		
// KK000404
			_pPointCover -> TransferTempDaten ();
		}
		else
			_pPointCover -> DeleteCover ();
			
		if (_pTexteCover -> hasData ())
		{								
			if ((EC = _pTexteCover -> OutputLastData ()) != EC_OKAY)
					return EC;		
// KK000404
			_pTexteCover -> TransferTempDaten ();
		}
		else
			_pTexteCover -> DeleteCover ();
			
		return EC;													
	}				
	
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (pIDD) {
			if (! pIDD -> hasData ()) {	 // wenn keine Datem im Cover sind
				pIDD -> DeleteFile ();	 // alle Coverages löschen
				continue;				   // und weiter
			}
			if ((EC = pIDD -> OutputLastData ()) != EC_OKAY)
				return EC;


		} else
			return EC_SYSERROR;
	}

	return EC_OKAY;
}

// Import-Makro ausgeben
ErrCode ExtIdentDescriptionTree :: OutputImportMakro (int fh) {
	ErrCode EC = EC_OKAY;
	
	if (FourCoverages)
	{
		if (_pPolyCover -> hasData ())
			if ((EC = _pPolyCover -> OutputImportMakro (fh)) != EC_OKAY)
				return EC;		
		
		if (_pArcCover -> hasData ())
			if ((EC = _pArcCover -> OutputImportMakro (fh)) != EC_OKAY)
				return EC;						
				
		if (_pPointCover -> hasData ())
			if ((EC = _pPointCover -> OutputImportMakro (fh)) != EC_OKAY)
				return EC;							

		if (_pTexteCover -> hasData ())
			if ((EC = _pTexteCover -> OutputImportMakro (fh)) != EC_OKAY)
				return EC;							
		
		return EC;
	}

	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (pIDD) {
			if (! pIDD -> hasData ()) {	 	// wenn keine Daten im Cover sind
				continue;				   	// weiter
			}
			if ((EC = pIDD -> OutputImportMakro (fh)) != EC_OKAY)
				return EC;
		} else
			return EC_SYSERROR;
	}

	return EC_OKAY;
}

//  Cover- und Merkmalsnamen im Dialog prüfen
ErrCode ExtIdentDescriptionTree :: CheckCoverNameDialog (BOOL bEnable) {
//  Elternfenster bestimmen
	Window *pParent = (Window *) SendMessage (__hWndM, __DexxCmd,
											   DEXX_MAINWINDOW, 0L);
	if (!pParent)
		return EC_NODEXMESSAGE;
		
//	Dialog zur zum Einstellen der Export-Parameter	           
	ExportParamDialog EPD (pParent, bEnable);
	if (EPD.OpFlag () == EC_OKAY)
		EPD.Show ();
	
	return EPD.OpFlag ();
}

//  Alle Dateien löschen
ErrCode ExtIdentDescriptionTree :: DeleteAllFiles (void) {
	if (FourCoverages)
	{             
		_pPolyCover -> DeleteCover ();
		_pArcCover -> DeleteCover ();
		_pTexteCover -> DeleteCover ();
		_pPointCover -> DeleteCover ();
		              
		return EC_OKAY;
	}
	
	ErrCode EC = EC_OKAY;
	
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (pIDD) {
			if ((EC = pIDD -> DeleteFile ()) != EC_OKAY)
				return EC;
		} else
			return EC_SYSERROR;
	}

	return EC_OKAY;
}

//  True, wenn noch ein weiteres Objekt den gesuchten Namen
//  enthält, sonst False
Bool ExtIdentDescriptionTree :: OtherCoverName  (long Id, pchar pSearchName,
												 char Typ) {
//  prüfe Parameter
	if (!pSearchName || !*pSearchName)
		return False;

	pchar pCoverName = "";
	CTable Tb (*this);
	for (Tb.First (); Tb.Valid (); Tb.Next ()) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (! pIDD)
			return False;			   // interner Fehler

			// nicht für übergebenes Objekt
		if (pIDD -> ID () != Id || pIDD -> IntTyp () != Typ) {
				pCoverName = pIDD -> GetCoverName ();
				if (lstrcmp (pCoverName, pSearchName) == 0) {
					DELETE_VEC (pCoverName);
					return True;
				}
			DELETE_VEC (pCoverName);
		}
	}

	return False;
}

//  Covernamen lesen, der im Fehlerfall NULL ist
//  und über delete freizugeben ist
pchar ExtIdentDescriptionTree :: GetCoverName (long ID, char Typ) {
	CTable Tb (*this);
	for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pID (Tb);
		if (!pID)
			return NULL;
		if (pID -> IntTyp () == Typ)
			return pID -> GetCoverName ();	 // mit Namen zurück
	}

	return NULL;
}

//  Neuen Covernamen speichern
ErrCode ExtIdentDescriptionTree :: SetCoverName (long ID, pchar pNewName,
												 char Typ) {
	CTable Tb (*this);
	for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pID (Tb);
		if (!pID)
			return EC_LOCKERROR;
		if (pID -> IntTyp () == Typ)
			return pID -> SetCoverName (pNewName) ? EC_OKAY : EC_NOMEMORY;
	}

	return EC_SYSERROR;
}

// zu einem Text-Objekt über seinen ID die Höhe lesen
ErrCode ExtIdentDescriptionTree :: FindTextHoehe (long ID, double &Hoehe) {
	Hoehe = 0.0;
	CTable Tb (*this);
	VisInfo *pVI = NULL;
	for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return EC_LOCKERROR;
		pVI = &pIDD -> VisInfoObj ();
		if (pVI && (pVI -> isA () == VT_Text)) {
			Hoehe = abs (((TVisInfo &) (pIDD -> VisInfoObj ())).Size ().Height());
			return EC_OKAY;
		}
	}

	//return EC_SYSERROR;
	Hoehe = StandartHoehe;
	return EC_OKAY;
}

// zu einem Text-Objekt über seinen ID den Drehwinkel bestimmen
ErrCode ExtIdentDescriptionTree :: FindTextDrehWinkel (long ID, double &Wi) {
	Wi = 0.0;
	CTable Tb (*this);
	VisInfo *pVI = NULL;
	for (Tb.FindFirst (&ID); Tb.Valid (); Tb.FindNext (&ID)) {
		ExtIdentDescriptionLock pIDD (Tb);
		if (!pIDD)
			return EC_LOCKERROR;
		pVI = &pIDD -> VisInfoObj ();
		if (pVI && pVI -> isA () == VT_Text) {
			Wi = ((TVisInfo &) (pIDD -> VisInfoObj ())).Rotation ();
			return EC_OKAY;
		}
	}

	//return EC_SYSERROR;
	Wi = 0;
	return EC_OKAY;
}


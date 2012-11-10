/*
File: OPTPARAM.CXX
Das Modul dient zur Eingabe und Verwaltung optionaler Parameter.

Erarbeitet: J. Benkenstein                                         Stand vom 11. Mai 1995
*/

#include "pheader.h"

#include "numedit.hxx"           	// NumEdit
#include "realedit.hxx"          	// RealEdit
#include "arctrias.hr"                   // Resourcen-Defines
#include "helptext.hxx"				// CHelpText
#include "optparam.hxx"          	// zugeh. Header

//  externe Variablen
extern Params *pParams;

//  Prototypen
char *DtoA (double Val, char *pBuffer, char *pFormat = NULL);

// Params ------------------------------------------------------------------
Params :: Params (void) {
	m_bAllCover = FALSE;				// bei mehreren Dateien alle versch. ID
	DebugOutput = FALSE;				// keine Debug-Ausgaben
	pCoverName = NULL;                	// "kurzer" CoverName (DOS-Name)
	XOffset = YOffset = 0.0;        	// Koordinaten-Verschiebung
	Scaling = 1.0;                    	// Skalierungs-Faktor
	UserID = True;                  	// Arc/Info-User-ID konv.
	CrUnID = True;                    	// unique -Ident erzeugen
	ID = 0;								// für Cover vergebener ID
	UnID = 0;                          	// unique Ident-MK
	TextMK = 0;                        	// TextMerkmalskode
	bAnsiiText = ImpTexte = ImpTabellen = True;	// Texte und sonstige Tabellen immer importieren
									    // Ansii-Text erzeugen
	sIdCode = 16;
	sMCode = 16;

// KK000328
	IsCompressed = False;				// Datei unkomprimiert

	Reset ();
	ResetCounter ();
}

Params :: ~ Params (void) {
	DELETE_VEC (pCoverName);
}

//	// alle Zähler zurücksetzen
void Params :: ResetCounter (void)					
{
	NotImported = SubImported = TableCnt = TextCnt = LineCnt = PointCnt = AreaCnt = BugCnt = 0;
}

// irgendwelche Objekt imp. ?
Bool Params :: HasImported (void)
{
	ulong ulAll = NotImported+SubImported+TableCnt+TextCnt+LineCnt+PointCnt+AreaCnt+BugCnt;
	return ulAll > 0 ? TRUE : FALSE;
}

// alle Werte auf Standardwerte setzen
void Params :: Reset (void) {
	DoublePrec = AatFields = AatExist = PalExist = False;
// KK000317
// Parameter EinzelCover (P,L,F,T) überprüfen
//	ImpFlaechen = ImpLinien = ImpPunkte = ImpTexte = False;

// KK000328
	IsCompressed = False;				// Datei unkomprimiert

	LineNr = MaxLineNr = 0;
	DELETE_VEC (pCoverName);
}

//  neuen Covernamen setzen
Bool Params :: SetCoverName (pchar pNewCoverName) {
    DELETE_VEC (pCoverName);    // alten Namen löschen

	char FileName [_MAX_FNAME] = "";
	_splitpath (pNewCoverName, NULL, NULL, FileName, NULL);
	if (lstrlen (FileName) > MaxFileSize)
		*(FileName + MaxFileSize) = '\0';

	pCoverName = new char [lstrlen (FileName) + 1];
	if (! pCoverName) {
		DEX_Error (RC_ParamsSetCoverName, EC_NOMEMORY);
		return False;
	}
	lstrcpy (pCoverName, FileName);

	return True;
}

#pragma warning (disable:4355)

// OptionalParams ----------------------------------------------------------
OptParams :: OptParams (pWindow pParent, ResourceFile *pRF, BOOL bMultFiles)
	: DialogWindow (pParent, ResID (IDD_OPTPARAMS, pRF)),
	_ID (this, ResID (IDE_IDENT, pRF), pParams -> sIdCode),
	_XOffset (this, ResID (IDE_XOFFSET, pRF)),
	_YOffset (this, ResID (IDE_YOFFSET, pRF)),
	_Scaling (this, ResID (IDE_SCALING, pRF)),
	_UserID (this, ResID (IDB_USERID, pRF)),
	_UnID (this, ResID (IDB_CTREATUNIDENT, pRF)), 
	_AllCover (this, ResID (IDB_FOR_ALL_COVER, pRF)),
	_ImpFlaechen (this, ResID (IDB_AREAS, pRF)),
	_ImpLinien (this, ResID (IDB_LINES, pRF)),
	_ImpPunkte (this, ResID (IDB_POINTS, pRF)),
	_ImpTexte (this, ResID (IDB_TEXTE, pRF)),
	_ImpTabellen (this, ResID (IDB_TABLES, pRF)),
	_Description (this, ResID (IDT_DESCRIPTION, pRF), pRF)
//	_AllImport (this, ResID (IDB_IMPORT_ALLE, pRF))
{       
//	Flag speichern
	m_bMultFiles = bMultFiles;

//	Beschreibungsfeld init.       
	_OpFlag = _Description.FInit ();
	if (!_OpFlag)
		return; 

	_pRF = pRF;

//  Ident-Feld init.
	char Buffer [50] = "";
	_ID.SetTextLimit (10);

//	gültiger ID
	if (pParams -> ID == 0)
		pParams -> ID = (ulong) DEX_GetUniqueICode (); // Unique Ident von TRIAS

//	Objektklassenschlüssel besorgen
#ifdef WIN32
	HRESULT hr = ClassFromIdentX (pParams -> ID, Buffer, sizeof (Buffer) - 1); 
	if (FAILED (hr))
		DEX_Error (RC_ParamsSetCoverName, WC_NOIDENT);
#else
	if (pParams -> sIdCode == 10)                                      
		ultoa (pParams -> ID, Buffer, 10);
	else 
		wsprintf (Buffer, "%lx", pParams -> ID);
#endif
		
	_ID.SetText (Buffer);		

//	weiteren Felder init.
	_XOffset.SetText (DtoA (pParams -> XOffset, Buffer));
	_YOffset.SetText (DtoA (pParams -> YOffset, Buffer));
	_Scaling.SetText (DtoA (pParams -> Scaling, Buffer));
	_UnID.SetChecked (pParams -> CrUnID);
	_UserID.SetChecked (pParams -> UserID);

	_ImpTexte.SetChecked (bMultFiles ? 1: pParams -> ImpTexte);
	_ImpTabellen.SetChecked (bMultFiles ? 1 : pParams -> ImpTabellen);
	if (bMultFiles)		// explizit aktivieren
	{
		_ImpLinien.SetChecked (1);					
		_ImpFlaechen.SetChecked (1);
		_ImpPunkte.SetChecked (1);
//		_ImpLinien.Disable ();					
//		_ImpFlaechen.Disable ();
//		_ImpPunkte.Disable ();
		_AllCover.Enable ();
		_AllCover.SetChecked (pParams -> m_bAllCover);
	}
	else
	{
		_AllCover.SetChecked (0);			// nur eine Objektklasse notw.
		_AllCover.Disable ();

	//	Linien-Flag einstellen	              
		if (! pParams -> AatExist)			// keine AAT vorhanden
			_ImpLinien.Disable ();			// ausschalten
		else
		{
			_ImpLinien.Enable ();			// einschalten	
			if (pParams -> PalExist)		// Pal ist vorhanden
				// nur dann setzen, wenn an den ARCS noch weitere Nutzer-Infos hängen
				_ImpLinien.SetChecked (pParams -> AatFields); 		
			else
				_ImpLinien.SetChecked (True);	// keine Flächen --> immer importieren
		} 
	
		if (pParams -> PalExist)			// Flächen vorhanden
		{                           
			_ImpFlaechen.Enable ();
			_ImpFlaechen.SetChecked (True);	
			_ImpPunkte.Disable ();          // dann bitte keine Punkte
		}		
		else								// und umgekehrt			
		{                          
			_ImpFlaechen.Disable ();
			_ImpPunkte.Enable ();		
			_ImpPunkte.SetChecked (True);		
		}		
	}			// nur eine Datei
		
//  Caption bilden
	if (!bMultFiles && pParams -> pCoverName)
	{
		ResString Caption (ResID (IDS_OPTCAPTION, pRF), 40);
		wsprintf (Buffer, Caption, pParams -> pCoverName);
		SetCaption (Buffer);
	}
	
//	Beschreibungstext setzen                
	_Description.SetHelpText (IDS_OBJEKTKLASSE);	
}                     

#pragma warning (default:4355)

void __export OptParams :: ButtonClick (ControlEvt CE) {
	uint ID = 0;
	CheckBox *pBox = (CheckBox *) CE.GetControl ();
	
	switch ((uint) CE.GetControlID ()) {
		case IDB_PARHELP:
			return;
		case IDCANCEL:
			EndDlg (False);
			return;			
		case IDOK: 
			if (_CheckAllParams ())  // wenn alle Parameter OK
				EndDlg (True);
			return;
		case IDB_USERID:
			ID = pBox -> isChecked () ? IDS_IMPORTUSERID : IDS_IMPORTNOUSERID;
			break;         
		case IDB_CTREATUNIDENT:        
			ID = pBox -> isChecked () ? IDS_CREATEUID : IDS_CREATENOUID;
			break;                         
		case IDB_AREAS:
			ID = pBox -> isChecked () ? IDS_IMPORTAREA : IDS_IMPORTNOAREA;
			break;        
		case IDB_LINES:
			ID = pBox -> isChecked () ? IDS_IMPORTLINES : IDS_IMPORTNOLINES;		
			break;         
		case IDB_POINTS:               
			ID = pBox -> isChecked () ? IDS_IMPORTPOINTS : IDS_IMPORTNOPOINTS;
			break;         
		case IDB_TEXTE:                
			ID = pBox -> isChecked () ? IDS_IMPORTTEXTE : IDS_IMPORTNOTEXTE;
			break;       
		case IDB_TABLES:               
			ID = pBox -> isChecked () ? IDS_IMPORTTABLES : IDS_IMPORTNOTABLES;
			break;
		case IDB_FOR_ALL_COVER:
			ID = pBox -> isChecked () ? IDS_FOR_ALL_COVER : IDS_FOR_NOTALL_COVER;
			break;
//		case IDB_IMPORT_ALLE:
//		{
//			if (pBox -> isChecked ())
//			{
//				ID = IDS_IMPORT_ALL;
//				_ImpFlaechen.Enable ();
//				_ImpFlaechen.SetChecked (True);
//				_ImpLinien.Enable ();
//				_ImpLinien.SetChecked (True);
//				_ImpPunkte.Enable ();
//				_ImpPunkte.SetChecked (True);
//				_ImpTexte.Enable ();
//				_ImpTexte.SetChecked (True);
//				_ImpTabellen.Enable ();
//				_ImpTabellen.SetChecked (True);
//			}
//			else
//				ID = IDS_IMPORT_SELECTED;
//		}
//		break;
		default:
			return;
	}       
	        
	if (ID)
		_Description.SetHelpText (ID);					
}

//  alle Parameter prüfen
Bool OptParams :: _CheckAllParams (void) 
{            
//	prüfe Art der zu importierenden Feature class
	if (!m_bMultFiles && !_ImpFlaechen.isChecked () && !_ImpLinien.isChecked () &&
		!_ImpTexte.isChecked () && !_ImpPunkte.isChecked () && !_ImpTabellen.isChecked ())
		return False; 	

	const short MaxLen = 30;
	char Buffer [MaxLen] = "";

//  Ident                          
#if _TRiAS_VER > 0x0200

#if _TRiAS_VER < 0x0300
	HRESULT hr = IdentFromClassX (_ID.GetText (Buffer, MaxLen), &pParams -> ID, FALSE);
#else
	HPROJECT hPr = DEX_GetDataSourceHandle();
	HRESULT hr = IdentFromClassX (hPr, _ID.GetText (Buffer, MaxLen), &pParams -> ID, FALSE);
#endif

	if (FAILED (hr))
	{
		DEX_Error (RC_ParamsSetCoverName, WC_NOIDENT);
		return FALSE;
	}
#else
	if ((pParams -> ID = strtoul (_ID.GetText (Buffer, MaxLen), NULL, 
	     					      pParams -> sIdCode)) == 0)
		return False;
#endif

//  Skalierung
	if ((pParams -> Scaling = atof (_Scaling.GetText (Buffer, MaxLen))) == 0.0)
		return False;

//  X/Y-Offset
	pParams -> XOffset = atof (_XOffset.GetText (Buffer, MaxLen));
	pParams -> YOffset = atof (_YOffset.GetText (Buffer, MaxLen));

	pParams -> UserID = _UserID.isChecked (); // konvertiere User-ID
	pParams -> CrUnID = _UnID.isChecked ();   // erzeuge Unique Ident       

	if (m_bMultFiles)
		pParams -> m_bAllCover = _AllCover.isChecked ();

	//else		
	//{
		pParams -> ImpFlaechen = _ImpFlaechen.isChecked (); // speichere Import-Status
		pParams -> ImpLinien = _ImpLinien.isChecked (); 	//	
		pParams -> ImpPunkte = _ImpPunkte.isChecked (); 	//		
	//}
	pParams -> ImpTexte = _ImpTexte.isChecked (); 		//	
	pParams -> ImpTabellen = _ImpTabellen.isChecked (); //			

	return True;
}
                         
void __export OptParams :: EditFocusChg (EditFocusChgEvt e)
{                                    
	if (! e.gotFocus ())		// Focus geht verloren
		return;
		
	uint ID = 0;		
	
	switch ((uint) e.GetControlID ())	
	{
		case IDE_IDENT:                     
			ID = IDS_OBJEKTKLASSE;
		break;
		case IDE_XOFFSET:
			ID = IDS_KOORDTRX;
		break;		
		case IDE_YOFFSET:
			ID = IDS_KOORDTRY;
		break;
		case IDE_SCALING:
			ID = IDS_KOORDSKAL;
		break;		
		default:
		return;
	}       
	
	if (ID)
		_Description.SetHelpText (ID);
} 	
                         

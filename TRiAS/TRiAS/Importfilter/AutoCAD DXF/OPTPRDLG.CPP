/*
File: OPTPRDLG.CPP
Das Module realisiert die Eingabe optionaler Parameter-Eingabe im Dialog.

Erarbeitet: J.Benkenstein                       Stand vom 01.09.1994
*/

#include "pheader.hpp"				// vorübersetzter Header

#include "numedit.hpp"				// Numedit
#include "realedit.hpp"          	// RealEdit
#include "helptext.hpp"				// CHelpText
#include "optprdlg.hpp"				// zugeh. Header

// KK991007
#include <hdrentrx.hxx>                 // HeaderEntryX
#include <resstrg.h>            	// TRIAS-Resourcen



//	externe Funktionen
char *DtoA (double Val, char *pBuffer, char *pFormat = NULL);

#pragma warning (disable:4355)
// OptionalParams ----------------------------------------------------------
OptParamsDlg :: OptParamsDlg (pWindow pParent, ResourceFile *pRF, Params *pOP)
: DialogWindow (pParent, ResID (IDD_OPTPARAMS, pRF)),
_XOffset (this, ResID (IDE_XOFFSET, pRF)),
_YOffset (this, ResID (IDE_YOFFSET, pRF)),
_CloseLines (this, ResID (IDB_CLOSE_LINES, pRF)),
m_ImpTextHoehe (this, ResID (IDB_HOEHE_IMP, pRF)),
m_ImpTextDrehWi (this, ResID (IDB_WINKEL_IMP, pRF)),
m_ImpSymDrehWi (this, ResID (IDB_IMP_SYM_DREHWI, pRF)),
m_ImpComment (this, ResID (IDB_IMPORT_COMMENT, pRF)),
m_ImpBlocks (this, ResID (IDB_IMPORT_BLOCKS, pRF)),
m_ImpSystemBlocks (this, ResID (IDB_IMPORT_SYSTEM_BLOCKS)),
m_edEbenen (this, ResID (IDE_LAYERS, pRF)),
// KK991007
m_NoShow (this, ResID (IDB_SHOWOFFSET, pRF)),
_OffsetXText (this, ResID (IDC_OFFSETX, pRF)),
_OffsetYText (this, ResID (IDC_OFFSETY, pRF)),
OKButton (this,IDOK),
// KK991007
_Description (this, ResID (IDT_DESCRIPTION, pRF), pRF)
{       
//	Beschreibungsfeld init.       
	_OpFlag = _Description.FInit () && pOP && pRF ? True : False;
	if (!_OpFlag)
	{
		DEX_Error (RC_DxfImport, EC_SYSERROR);
		return; 
	}

//	Argumente speichern
	_pRF = pRF;
	_pParams = pOP;

//  weitere Felder init.
	char Buffer [50] = "";
	
	_XOffset.SetText (DtoA (_pParams -> XOffset, Buffer));
	
	_YOffset.SetText (DtoA (_pParams -> YOffset, Buffer));

// KK991007
	OKButton.Enable();
	if ( pOP->FileName() ) {
		_XOffset.Disable();
		_YOffset.Disable();
	}

	_CloseLines.SetChecked (_pParams -> bCloseLine);
	m_ImpTextHoehe.SetChecked (_pParams -> m_bImpTextHoehe);
	m_ImpTextDrehWi.SetChecked (_pParams -> m_bImpTextDrehWi);
	m_ImpSymDrehWi.SetChecked (_pParams -> m_bImpSymDrehWi);
	m_ImpComment.SetChecked (_pParams -> m_bImpComment);
	m_ImpBlocks.SetChecked (_pParams -> m_bImpBlocks);
	m_ImpSystemBlocks.SetChecked (_pParams -> m_bImpSystemBlocks);

// KK991007
	m_NoShow.SetChecked (_pParams -> m_bOffset);

	m_edEbenen.SetText (_pParams -> m_pEbenen ? _pParams -> m_pEbenen : "");

	_Description.SetHelpText (IDS_XOFFSET);

// KK991007
	if ( pOP->FileName() ) {

		char *strCap = new char [_MAX_PATH];
		if ( strCap ) {
			ResString Cap (ResID (IDS_TEXTCAPTION, pRF),50);

			wsprintf (strCap,Cap.Addr(),pOP->FileName());
			SetCaption (strCap);
			ResString OX (ResID (IDS_TEXTOFFSETX, pRF),50);
			ResString OY (ResID (IDS_TEXTOFFSETY, pRF),50);
			_OffsetXText.SetText(OX.Addr());
			_OffsetYText.SetText(OY.Addr());
			_Description.SetText ("");
//  nur Ausgabe, wenn noch keine Enträge vorh.
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
				ResString DBT (ResID (IDS_TEXTQUELLE, pRF),100);
		#else
				HeaderEntryX HD_Y (HVar);
				ResString DBT (ResID (IDS_TEXTDBQUELLE, pRF),100);
		#endif


				wsprintf ( strCap ,DBT.Addr(),HD_X.EntryText(),HD_Y.EntryText());

				double dQ = 1.0;

// KK000607 - geodätisch - Grad beachten !!!
		#if _MSC_VER >= 1100
				ResString HD (ResID (IDS_HEADERDEGREE, pRF), 50);
				ResString HDegr (ResID (IDS_DEGREE, pRF), 50);
				HeaderEntryX HD_Degree (HD,hPr);
				if (HD_Degree.Status () != HE_INVALID) {			// Header in Datenquelle vorhanden
					if ( 0 == strcmp (HD_Degree.EntryText(),HDegr.Addr()))
						dQ = 3600.0;
				}
		#endif
//----------------------------------------------------------------

			//  X/Y-Offset der Datenquelle
				double dMinX = atof (HD_X.EntryText ());
				double dMinY = atof (HD_Y.EntryText ());
// KK000607
				dMinY = dMinY / dQ;

				if (dMinX > _pParams -> XOffset || dMinY > _pParams -> YOffset) {
					ResString TW (ResID (IDS_TEXTWIDER, pRF),50);
					strcat ( strCap,TW.Addr());
					OKButton.Disable();
				}

				_Description.SetText (strCap);

			}
			
			DELETE_OBJ (strCap);

		} else {
			SetCaption (pOP->FileName());
		}
		
	}

}                     
#pragma warning (default:4355)

void __export OptParamsDlg :: ButtonClick (ControlEvt CE) {
	uint ID = 0;
	CheckBox *pBox = (CheckBox *) CE.GetControl ();
	
	switch ((uint) CE.GetControlID ()) {
		// case IDB_PARHELP:
		// return;
		case IDCANCEL:
			EndDlg (False);
		return;			
		case IDOK: 
			if (_CheckAllParams ())  // wenn alle Parameter OK
				EndDlg (True);
		return;
		case IDB_CLOSE_LINES:
			ID = pBox -> isChecked () ? IDS_CLOSE_LINES : IDS_NOT_CLOSE_LINES;
		break;         
		case IDB_HOEHE_IMP:
			ID = pBox -> isChecked () ? IDS_HOEHE_IMP : IDS_NOT_HOEHE_IMP;
		break;			
		case IDB_WINKEL_IMP:
			ID = pBox -> isChecked () ? IDS_WINKEL_IMP : IDS_NOT_WINKEL_IMP;
		break;
		case IDB_IMP_SYM_DREHWI:
			ID = pBox -> isChecked () ? IDS_SWINKEL_IMP : IDS_NOT_SWINKEL_IMP;
		break;
		case IDB_IMPORT_COMMENT:
			ID = pBox -> isChecked () ? IDS_COMMENT_IMP : IDS_NOT_COMMENT_IMP;
		break;
		case IDB_IMPORT_BLOCKS:
		{
			ID = pBox -> isChecked () ? IDS_BLOCKS_IMP : IDS_NOT_BLOCKS_IMP;
			if (pBox -> isChecked ())
				m_ImpSystemBlocks.Enable ();
			else
			{
				m_ImpSystemBlocks.Disable ();
				m_ImpSystemBlocks.SetChecked (FALSE);
			}
		}
		break;
		case IDB_IMPORT_SYSTEM_BLOCKS: 
			ID = pBox -> isChecked () ? IDS_SYSTEM_BLOCKS_IMP : IDS_NOT_SYSTEM_BLOCKS_IMP;
		break;
	// KK991007
		case IDB_SHOWOFFSET:

		break;

		default:
			return;
	}       
	        
	if (ID)
		_Description.SetHelpText (ID);					
}

//  alle Parameter prüfen
Bool OptParamsDlg :: _CheckAllParams (void) 
{            
	const short MaxLen = 30;
	char Buffer [MaxLen] = "";

//  X/Y-Offset
	_pParams -> XOffset = atof (_XOffset.GetText (Buffer, MaxLen));
	_pParams -> YOffset = atof (_YOffset.GetText (Buffer, MaxLen));
	_pParams -> bCloseLine = _CloseLines.isChecked (); // konvertiere Linien-Flag
	_pParams -> m_bImpTextHoehe = m_ImpTextHoehe.isChecked ();
	_pParams -> m_bImpTextDrehWi = m_ImpTextDrehWi.isChecked ();
	_pParams -> m_bImpSymDrehWi = m_ImpSymDrehWi.isChecked ();
	_pParams -> m_bImpComment = m_ImpComment.isChecked ();
	_pParams -> m_bImpBlocks = m_ImpBlocks.isChecked ();
	_pParams -> m_bImpSystemBlocks = m_ImpSystemBlocks.isChecked ();	
	_pParams -> m_bOffset = m_NoShow.isChecked ();	

//	Ebenen lesen
	if (m_edEbenen.isModified ())
	{
	//	alten Text löschen
		DELETE_VEC (_pParams -> m_pEbenen);
		UINT uiSize = m_edEbenen.GetTextLen()+1;
		_pParams -> m_pEbenen = new char [uiSize];
		if (!_pParams -> m_pEbenen)
		{
			DEX_Error (RC_DxfImport, EC_NOMEMORY);
			return False;
		}
		m_edEbenen.GetText (_pParams -> m_pEbenen, uiSize);
	}

	return True;
}

void __export OptParamsDlg :: EditFocusChg (EditFocusChgEvt e)	
{                                    
	if (! e.gotFocus ())		// Focus geht verloren
		return;
		
	uint ID = 0;		
	
	switch ((uint) e.GetControlID ())	
	{
		case IDE_XOFFSET:
			ID = IDS_XOFFSET;
		break;		
		case IDE_YOFFSET:
			ID = IDS_YOFFSET;
		break;
		case IDE_LAYERS:
			ID = IDS_LAYERSEL_DESCR;
		break;
		default:
		return;
	}       
	
	if (ID)
		_Description.SetHelpText (ID);
} 	
                         

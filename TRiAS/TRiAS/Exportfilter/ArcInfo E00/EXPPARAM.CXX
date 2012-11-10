/*
File: EXPPARAM.CXX
Bezugsmaßstab über einen Dialog einlesen.

erarbeitet : J. Benkenstein				 Begonnen am 21. August 1994
*/

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

//XX #include "triasarc.hr"		   	// Resource-IDs
#include "nameedit.hxx"			// NameEdit
#include "numedit.hxx"		  	// NumEdit
#include "covname.hxx"			// CoverNameDialog
#include "merkname.hxx"			// MerkmalNameDialog
#include "helptext.hxx"			// CHelpText
#include "expparam.hxx"		  	// zugeh. Header-File

// KK000330
#include "e00compr.h"			// Komprimierung

//  externe Variablen
extern ResourceFile *pRF;
extern double Masstab;		  	// Bezugs-Maßstab
extern Bool TextExist;		  	// Text-Objekte existieren
extern Bool PolyExist;		  	// Flächen-Objekte existieren
extern Bool FourCoverages;		// Konvertierungsart 
// KK000330
extern int nComprLevel;			// Komprimierungsart

extern Bool Insel;				// Inseln exportieren
                    
#pragma warning (disable:4355)
                    
// ExpParamMasstab -------------------------------------------------------------
ExportParamDialog :: ExportParamDialog (pWindow pParent, BOOL bEnable)
: DialogWindow (pParent, ResID (IDD_PARAMS, pRF)),
_MasstabEdit (this, ResID (IDE_BEZUGSM, pRF)),
_CreateLables (this, ResID (IDB_CREATELABELS, pRF)),
_CoverNames (this, ResID (IDB_COVERNAMES, pRF)),
_MerkmalNames (this, ResID (IDB_MERKMNAMES, pRF)),
_ManyCoverages (this, ResID (IDB_MANYCOVERS, pRF)),	
_Description (this, ResID (IDT_DESCRIPTION, pRF), pRF),
_MasstabText (this, ResID (IDT_MASSTABTEXT, pRF)),
_Insel (this, ResID (IDB_INSEL, pRF)),

// KK000329
_ComprNone (this, ResID (IDC_COMPRNONE)),
_ComprPartial (this, ResID (IDC_COMPRPARTIAL)),
_ComprFull (this, ResID (IDC_COMPRFULL)),

_FourCoverages (this, ResID (IDB_FOURCOVER))

{
//  prüfe Parameter
	if (!pRF || ! _Description.FInit ()) 
	{                        
		EndDlg (_OpFlag = EC_SYSERROR);
		return;
	}   
	
	_OpFlag = EC_OKAY;
	    
//	Buzugsmaßstab-Feld init.	    
	if (TextExist)
	{			    
		if (Masstab) 
		{
			char Buffer [20] = "";
			ltoa ((long) Masstab, Buffer, 10);
			_MasstabEdit.SetText (Buffer);
		}
	}
	else
	{
		_MasstabEdit.Hide ();						
		_MasstabText.Hide ();
	}			
		                   
//	Label-Flag init.					// wenn Flächen vorhanden
    if (PolyExist)
	{
    	_CreateLables.SetChecked (True);
		_Insel.SetChecked (True);
	}
	else
	{
		_CreateLables.Disable ();		    	
		_Insel.Disable ();
	}
				          
//	Konvertierungsart setzen: immer pro ID ein Cover
	if (FourCoverages)
	{
		_ManyCoverages.Hide ();	
		_FourCoverages.SetState (TRUE);
	}
	else
		_ManyCoverages.SetState (TRUE);
		
	_Description.SetHelpText (IDS_MANY_COVER);			// zugeh. Beschreibungstext

	if (bEnable)
		_MerkmalNames.Enable ();
	else
		_MerkmalNames.Disable ();	

// KK000329
	_ComprNone.SetState(TRUE);

}                           

#pragma warning (default:4355)

//  Ein PushBotton wurde betätigt.
void EXPORTFLT ExportParamDialog :: ButtonClick (ControlEvt CE) 
{               
	switch ((uint) CE.GetControlID ()) 
	{
		case IDB_PARAMHELP:
			return;       					// noch kein Text definiert
		break;			  
		case IDCANCEL:
			EndDlg (_OpFlag = EC_USERBREAK);
		break;              
		case IDB_CREATELABELS:
		{                         
			if (_CreateLables.isChecked ())
				_Description.SetHelpText (IDS_CREATE_LABELS);
			else
				_Description.SetHelpText (IDS_CREATE_NO_LABELS);		
		}       
		break;
		case IDB_INSEL:
		{
			if (_Insel.isChecked ())
				_Description.SetHelpText (IDS_INSEL);
			else
				_Description.SetHelpText (IDS_NOT_INSEL);
		}
		break;
		case IDB_FOURCOVER: 
		{                            
			_Description.SetHelpText (IDS_FOUR_COVER);					
			_CoverNames.Disable ();			// der Dateien-Namens-Dialog ist nicht notwendig	
			// SetOkButton ();
		}			
		break;			
		case IDB_MANYCOVERS:                                               
		{			
			_Description.SetHelpText (IDS_MANY_COVER);					
			_CoverNames.Enable ();			// Dialog möglich
			// SetOkButton ();
		}			
		break;
		case IDB_COVERNAMES:
		{
			CoverNameDialog CVD (this);
			if ((_OpFlag = (ErrCode) CVD.Result ()) != EC_OKAY)
				EndDlg (_OpFlag);	  

			CVD.Show ();
			if ((_OpFlag = (ErrCode) CVD.Result ()) != EC_OKAY)
				EndDlg (_OpFlag);	  
			// SetOkButton ();
		}
		break;
		case IDB_MERKMNAMES:
		{
			MerkmalNameDialog MND (this);
			if ((_OpFlag = (ErrCode) MND.Result ()) != EC_OKAY)
				EndDlg (_OpFlag);	  			
			MND.Show ();          
			if ((_OpFlag = (ErrCode) MND.Result ()) != EC_OKAY)
				EndDlg (_OpFlag);	  
			// SetOkButton ();
		}			
		break; 

// KK000329
//--------------------------------------------------------------------------
		case IDC_COMPRNONE :
		{
			_ComprNone.SetState(TRUE);
			_ComprPartial.SetState(FALSE);
			_ComprFull.SetState(FALSE);
			_Description.SetHelpText (IDS_COMPR_NONE);
			nComprLevel = E00_COMPR_NONE;
		}
		break;

		case IDC_COMPRPARTIAL :
		{
			_ComprPartial.SetState(TRUE);
			_ComprNone.SetState(FALSE);
			_ComprFull.SetState(FALSE);
			_Description.SetHelpText (IDS_COMPR_PARTIAL);
			nComprLevel = E00_COMPR_PARTIAL;

		}
		break;

		case IDC_COMPRFULL :
		{
			_ComprFull.SetState(TRUE);
			_ComprPartial.SetState(FALSE);
			_ComprNone.SetState(FALSE);
			_Description.SetHelpText (IDS_COMPR_FULL);
			nComprLevel = E00_COMPR_FULL;

		}
		break;
//----------------------------------------------------------------------------

		case IDOK: 
		{   
			FourCoverages = !_ManyCoverages.GetState ();
		
		//	die Merkmalsnamen immer prüfen			
			MerkmalNameDialog MND (this);
			if (!MND.CheckAllNames (FALSE))						// sind Namen eindeutig
			{
				if ((MND.CreateUniqueNames () != EC_OKAY) ||	// bitte eindeutige erz.
					!MND.CheckAllNames (FALSE))					// und nochmals prüfen
				{
					OutputWarnung (IDS_MERKM_NOT_CHECKED);
					break;    
				}
			}

		//	die Covernamen ggf. prüfen
			if (!FourCoverages)
			{
				CoverNameDialog CVD (this);
				if (!CVD.CheckAllNames (FALSE))						// alle Dateinamen eindeutig
				{
					if ((CVD.UniqueCoverNames () != EC_OKAY) ||		// eindeutige erz.
						!CVD.CheckAllNames (FALSE))					// nochmals prüfen
					{
						OutputWarnung (IDS_COVER_NOT_CHECKED);
						break;
					}
				}
			}

			PolyExist = _CreateLables.isChecked ();				
			Insel = _Insel.isChecked ();
			
			if (TextExist)
			{						
				char Buffer [20] = "";
				_MasstabEdit.GetText (Buffer, sizeof (Buffer));
				Masstab = atol (Buffer);
				if (Masstab)
					EndDlg (_OpFlag = EC_OKAY);
				else
					OutputWarnung (IDS_NOMASSTAB);								
			}					
			else
				EndDlg (_OpFlag = EC_OKAY);
		}
		break;
		default:
			return;
	}
}

void ExportParamDialog :: OutputWarnung (uint uiResId) 
{
	ResString Caption (ResID (IDS_WARNUNG, pRF), 20);
	ResString Text (ResID (uiResId, pRF), 128);
	MessBox MB (Caption.Addr (), Text.Addr (), this);
	MB.SetType (OkayButton | ExclamationIcon);
	MB.Show ();
}

void EXPORTFLT ExportParamDialog :: EditFocusChg (EditFocusChgEvt e)
{
	if ((((uint) e.GetControlID ()) == IDE_BEZUGSM) && e.gotFocus ())
		_Description.SetHelpText (IDS_BEZUGS_MASSTAB);					
} 

Bool ExportParamDialog :: QueryClose (Event)
{               
	_OpFlag = EC_USERBREAK;
	return True;
}

/*
void ExportParamDialog :: SetOkButton (void)
{
	if ((_ManyCoverages.GetState () && m_bMerkmaleChecked && m_bCoverChecked) ||
		(!_ManyCoverages.GetState () && m_bMerkmaleChecked))
		m_btOk.Enable ();
	else
		m_btOk.Disable ();
}
*/
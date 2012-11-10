// Bearbeiten eines MerkmalsWertes --------------------------------------------
// File: OBJMDLG.CXX

#include "objclipp.hxx"

#include "objcldlg.h"
#include "objmdlg.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

ObjMerkmalDlg :: ObjMerkmalDlg (pWindow pW, ResourceFile *pRF, 
				char *pMText, char *pKText)
	        : DialogWindow (pW, ResID (OBJMERKMALDLG, pRF)),
		  MWert (this, IDE_OBJMERKMAL)
{
// DialogFenster initialisieren
	SetCaption (pKText);
	MWert.SetText (pMText);
}

#pragma warning (default: 4355)

ObjMerkmalDlg :: ~ObjMerkmalDlg (void)
{
	// nothing to do
}

void _XTENSN_EXPORT ObjMerkmalDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (MWert.isModified()) 
			EndDlg (1);
		else
			EndDlg (0);
		break;

	case IDCANCEL:
		EndDlg (0);
		break;
	}
}

char *ObjMerkmalDlg :: GetNewText (char *pBuffer, short iMaxLen)
{
	MWert.GetText (pBuffer, iMaxLen);

return pBuffer;
}

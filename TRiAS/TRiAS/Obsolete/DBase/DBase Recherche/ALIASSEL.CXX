/*
File: ALIASSEL.CXX

Das Modul dient zu Auswahl der projektspezifischen Alias-Namen.

Erarbeitet: J. Benkenstein				  Stand vom: 13.11.95
*/

#include "pheader.h"

extern "C" {
	#include "komplexr.hr"		   	// ResourceKonstanten
}

#include "aliassel.htp"
#include <commonvu.hxx>
#include <containr.hxx>
#include <dbliste.hxx>			  	// DataIndexTree
#include "aliassel.hxx"			 	// zugeh. Header

//  Konstanten
const short ProfBufferSize = 1024;  // Profile-Buffer
const short AliasSize = 10;		 	// max. Größe eines Aliasnamens
const char Sep [] = ":";			// Separator

#pragma warning (disable:4355)
// SelectAliasNames --------------------------------------------------------
SelectAliasNames :: SelectAliasNames (pWindow pParent, ResourceFile *pRF,
							CodeBase *pCodeBase, DBaseFiles *pData)
: DialogWindow (pParent, ResID (IDD_ALIASSELECT, pRF)),
_List (this, ResID (IDL_ALIASSELECT, pRF)),
_OK (this, ResID (IDB_OKALIASSELECT, pRF)) {
	_OpFlag = False;

//  prüfe Parameter
	if (!pCodeBase || !pData) {
		DEX_Error (RC_ctSelectAliasNames, EC_SYSERROR);
	}
	if (pCodeBase -> error () != r4success)	 // prüfe CodeBase
		return;

	_pCodeBase = pCodeBase;		 // Zeiger speichern
	_pDataTree = pData;

//  Speicher anlegen
	pchar pBuffer = new char [ProfBufferSize];
	if (!pBuffer)
		return;

//  alle Schlüssel aus Alias-Section lesen
	ulong Len = 0;
	ResString Section (ResID (IDS_ALIASSECTION, pRF), 25);

//  Projektnamen lesen
	char Project  [_MAX_PATH] = "";
	char Drive	[_MAX_DRIVE] = "";
	char Dir	  [_MAX_DIR] = "";
	char FileName [_MAX_FNAME] = "";
	DEX_GetActiveProject (Project);
	_splitpath (Project, Drive, Dir, FileName, NULL);
	ResString Ext (ResID (IDS_INIEXTENSION, pRF), _MAX_EXT);
	_makepath (Project, Drive, Dir, FileName, Ext.Addr ());


	Len = GetPrivateProfileString (Section.Addr (), NULL, "", pBuffer,
								   ProfBufferSize, Project);
	if (!Len) {
		DEX_Error (RC_ctSelectAliasNames, WC_NOALIASNAMESFOUND);
		DELETE_VEC (pBuffer);
		return;
	}

//  zu den gefundenen Schlüssel die zugeh. Enträge lesen und ausgeben
	pchar pNewLine = NULL;
	ulong ActLen = 0;
	for (pchar pActKey = pBuffer; pActKey < pBuffer + Len;
		 pActKey += lstrlen (pActKey) + 1) {
		ActLen = GetPrivateProfileString (Section.Addr (), pActKey, "",
										  FileName, _MAX_FNAME, Project);
		if (ActLen) {
			pNewLine = new char [lstrlen (pActKey) + ActLen + 2];
			if (!pNewLine) {
				DEX_Error (RC_ctSelectAliasNames, EC_NOMEMORY);
				break;
			}
			lstrcpy (pNewLine, pActKey);
			lstrcat (pNewLine, Sep);
			lstrcat (pNewLine, FileName);
			if (_List.AddString (strupr (pNewLine)) == -1) {
				DEX_Error (RC_ctSelectAliasNames, EC_SYSERROR);
				break;
			}
		}
		DELETE_VEC (pNewLine);
	}

	DELETE_VEC (pNewLine);
	DELETE_VEC (pBuffer);

	_OpFlag = True;
}							 

#pragma warning (default:4355)

void __export SelectAliasNames :: ListBoxSel (ControlEvt) {
	if (_List.GetNoSelected () > 0)
		_OK.Enable ();
	else
		_OK.Disable ();
}

void __export SelectAliasNames :: ButtonClick (ControlEvt e) {
	switch ((uint) e.GetControlID ()) {
		case IDB_OKALIASSELECT: {
			char AliasName [_MAX_PATH] = "";
			pchar pSep = NULL;
			for (short Index = _List.GetFirstSelected (); Index >= 0;
				Index = _List.GetNextSelected ()) {

			//  akt. String lesen
				_List.GetString (AliasName, Index, sizeof (AliasName) - 1);

			//  Aliasnamen auslesen
				AliasName [AliasSize] = '\0';
				pSep = strstr (AliasName, Sep);
				*pSep = '\0';
				if (! _pDataTree -> AddDataIndex (_pCodeBase, AliasName))
					break;
			}
			EndDlg (True);
		}
		break;
		case IDB_ABBRALIASSELECT:
			EndDlg (False);
		break;
		case IDB_HELPALIASSELECT:
		break;
	}
}

// Memberfunktionen fuer MetaFileSupport unter CommonVU -----------------------
// File: METAFILE.CXX

extern "C" {
	#include <windows.h>
	#include <string.h>
	#include <protos.h>
}

#include <commonvu.hxx>
#include <drawobj.hxx>

#include <errcodes.hxx>

#include "metafile.hxx"


MetaFile :: MetaFile (char *Name) 
	  : Window ()
{
// Handles initialisieren
	_hMF = 0;
	_hMetaDC = 0;

// Namen merken
	_Name = new char [strlen (Name)+1];
	if (_Name == NULL) {
		db_error (EC_NOMEMORY, RC_ctMetaFile);
		return;
	}
	strcpy (_Name, Name);
}

MetaFile :: ~MetaFile (void) 
{
	if (_hMF) DeleteMetaFile (_hMF);
	if (_Name != NULL) {
		delete _Name;
		_Name = NULL;
	}
}

// Generieren des MetaFiles ---------------------------------------------------
void MetaFile :: Generate (void) {
MetaFileExposeEvt e;

// MetaFile anlegen
	_hMetaDC = CreateMetaFile (_Name);
	_hMF = 0;

// den Nutzer auffordern endlich sein Zeug zu zeichnen
	MetaFileExpose (e);

// MetaFile schlieáen und Handle merken
	_hMF = CloseMetaFile (_hMetaDC);
	_hMetaDC = 0;
}


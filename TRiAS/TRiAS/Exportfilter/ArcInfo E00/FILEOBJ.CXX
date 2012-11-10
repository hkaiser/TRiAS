/*
Datei: FILEOBJ.cxx
Die Klasse FileObj ist in erster Linie als scoping class eines FileHandles
entworfen worden.

Erarbeitet: J. Benkenstein						  Stand vom: 20.12.1993
*/

#include "stdafx.h"               
#include "fileobj.hxx"		  // zugeh. Header

//  FileObj ----------------------------------------------------------------
// Datei im geg. Modus öffnen
FileObj :: FileObj (OFSTRUCT *pof, uint OpenMode) {
		_delete = False;
		_pof = pof;
		_fh = OpenFile (_pof -> szPathName, _pof, OpenMode);
}

FileObj :: FileObj (pchar pFileName, uint OpenMode) {
		_pof = NULL;
		_fh = -1;

		if (_pof = new OFSTRUCT) {
				_fh = OpenFile (pFileName, _pof, OpenMode);
				_delete = True;
		} else
				_delete = False;
}

//  Datei schließen
FileObj :: ~ FileObj (void) {
		if (_fh > 0)
				_lclose (_fh);

		if (_delete)
				DELETE_OBJ (_pof);
}

//  Datei löschen
void FileObj :: Delete (void) {
		if (_fh > 0) {
				remove (_pof -> szPathName);
				_fh = -1;
		}
}

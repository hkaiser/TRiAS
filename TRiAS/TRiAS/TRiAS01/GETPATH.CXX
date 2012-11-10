/* Bibliotheksroutine                                           */
/* Herausloesen des Pfadnamens                                  */
/* File: GETPATH.C              last update: 25. Mai 1989       */

#include "trias01p.hxx"

char * FUNCTYPE getpath (register char *cbPath, char *name, int)
{
char *cbDrive = NULL;
char *cbTPath = NULL;

	if(cbPath == NULL) 
		cbPath = new char [_MAX_PATH];
	cbDrive = new char [_MAX_DRIVE];
	cbTPath = new char [_MAX_PATH];

        if(cbPath && cbTPath && cbDrive ) {
		_splitpath (name, cbDrive, cbTPath, NULL, NULL);
		_makepath (cbPath, cbDrive, cbTPath, "", "");
	} else {
		if (cbPath) delete cbPath;
	}
	if (cbTPath) delete cbTPath;
	if (cbDrive) delete cbDrive;
	
return cbPath;
}

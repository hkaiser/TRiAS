/*
Datei: FILEOBJ.hxx
Die Klasse FileObj ist in erster Linie als scoping class eines FileHandles
entworfen worden.

Erarbeitet: J. Benkenstein              Stand vom: 20.12.1993
*/

#ifndef _FILEOBJ_HXX
#define _FILEOBJ_HXX

class FileObj {
private:
//  Attribute
    OFSTRUCT *_pof;
    int _fh;
    Bool _delete;

public:
//  Konstruktor/Destruktor
    FileObj (OFSTRUCT *pof, uint OpenMode);     // Datei im geg. Modus öffnen
    FileObj (pchar pFileName, uint OpenMode);
    ~ FileObj (void);

//  weitere Member
    void Delete (void);     // Datei löschen
    int FileHandle (void) { return _fh; }
    OFSTRUCT &FileStructur (void) { return *_pof; }

//  operatoren
    Bool operator ! (void) { return _fh <= 0; }
};

#endif  //   _FILEOBJ_HXX

/*
Datei: TOOLS.HXX
Die beinhaltet allgemeine Funktionen zur Arbeit innerhalb der Komplexrecherche.

Erarbeitet:  J. Benkenstein			    Stand vom: 15.07.1993
*/

#ifndef _TOOLS_HXX
#define _TOOLS_HXX

//  Text-Merkmal eines Objektes lesen
ErrCode GetMiText (long MKode, long ObjNr, char* &pBuffer, short BufferLen = 100);

#endif	    // _TOOLS_HXX

/*
Datei: DQLEXPRT.HXX

Die Datei listet alle von der Komplexrecherche-Extension exportierten
Funktionen.

Erabeitet: J. Benkenstein                       Stand vom 1. Novmber 1993
*/

#ifndef _DQLEXPRT_HXX
#define _DQLEXPRT_HXX

#if defined(__cplusplus)
extern "C"
{
#endif

//      - pScriptName = vollst. Name der Scriptdatei
//      - Parse = FALSE --> Recherche durchfheren
//      - Parse = TRUE  --> Script nur "kontrollieren"
BOOL FAR PASCAL doFileRechercheCall (char *pScriptName, BOOL Parse = FALSE);

#if defined(__cplusplus)
}
#endif

#endif  // _DQLEXPRT_HXX

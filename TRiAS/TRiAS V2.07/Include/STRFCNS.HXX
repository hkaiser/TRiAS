// Prototypen fuer StringManipulationsFunktionen ------------------------------
// File: STRFCNS.HXX

#if !defined(_STRFCNS_HXX)
#define _STRFCNS_HXX

_TRIAS01_ENTRY char *ShortenPath (char *pName, short iMaxLen);
_TRIAS01_ENTRY char *ExpandWithName (char *pName, const char *pFullPath, bool iFullPath = FALSE);

#endif // _STRFCNS_HXX

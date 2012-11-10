// Memberfunktionen fuer YACC-StackElemente -----------------------------------
// File: DBASEKEY.CXX
// Stand vom 22.12.1992

#include "pheader.h"

#include "dbasekey.htp"	 // Klassen-Selektion
#include <commonvu.hxx>
#include <dbasekey.hxx>

#include "tools.hxx"		// GetMiText ()


/*
// ----------------------------------------------------------------------------
// Eine Routine, die das erste Vorkommen eines Schlüssels in Bäumen findet,
// in denen Schlüssel nicht eindeutig sind
CKeyNode *CKeyNode :: FindFirst (void *key) const {
CKeyNode *locNode = Find(key);

		while (locNode) {
		CKeyNode *oldNode = locNode;

				locNode = locNode -> Prev();
				if (!locNode || locNode -> Compare (key) != 0)
				// erster entsprechender Eintrag in Container gefunden
						return oldNode;		 
		}
		return 0;
}

// Das Gegenstück dazu für den Navigator
Bool CTable :: FindFirst (void *key) {

		m_pCurrentNode = ((CKeyContainer &)GetContainer()) . DataStructure ();
		if (m_pCurrentNode)
				m_pCurrentNode = ((CKeyNode *)m_pCurrentNode) -> FindFirst (key);

return m_pCurrentNode != 0;
}
*/

// Konstruktoren --------------------------------------------------------------
DBaseKey :: DBaseKey (DBaseKeyType DBK, long Code, Bool bOnlyExpr) 
{
		_bOnlyExpr = bOnlyExpr;
		_DBKType = DBK;
		_DBaseKeyLong = Code;
		_DBaseKeyString = NULL;
}

DBaseKey :: DBaseKey (DBaseKeyType DBK, char *lpName, Bool bOnlyExpr) 
{
		_bOnlyExpr = bOnlyExpr;
		_DBKType = DBK;
		_DBaseKeyString = new char [lstrlen (lpName) +1];
		if (_DBaseKeyString)
				lstrcpy (_DBaseKeyString, lpName);
}

DBaseKey :: DBaseKey (DBaseKey &DBK) 
{
		_bOnlyExpr = DBK._bOnlyExpr;
		_DBKType = DBK._DBKType;
		_DBaseKeyLong = DBK._DBaseKeyLong;
		if (DBK._DBaseKeyString) {
				_DBaseKeyString = new char [lstrlen (DBK._DBaseKeyString) +1];
				if (_DBaseKeyString) 
						lstrcpy (_DBaseKeyString, DBK._DBaseKeyString);
		} else
				_DBaseKeyString = NULL;
}

DBaseKey :: ~DBaseKey (void) 
{
		DELETE_VEC (_DBaseKeyString);
}

GeoDBKey :: GeoDBKey (GeoDBKeyType GDK, long Code) {

		_GDKType = GDK;
		_GeoDBKeyLong = Code;
}

GeoDBKey :: GeoDBKey (GeoDBKey &GDBK) {

		_GDKType = GDBK._GDKType;
		_GeoDBKeyLong = GDBK._GeoDBKeyLong;
}

KeyFilter :: KeyFilter (GeoDBKey *pGDBK, DBaseKey *pDBK, Bool iUnique) {

		_isUnique = iUnique;
		_pGDBK = new GeoDBKey (*pGDBK);
		_pDBK = new DBaseKey (*pDBK);
}

KeyFilter :: KeyFilter (DBaseKey *pDBK, Bool iUnique) {
		_isUnique = iUnique;
		_pGDBK = NULL;
		_pDBK = new DBaseKey (*pDBK);
}


KeyFilter :: ~KeyFilter (void) {

		DELETE_OBJ (_pGDBK);
		DELETE_OBJ (_pDBK);
}

char *KeyFilter :: FieldValue (long ONr, int NumMCodes, long *MCodes, char **MStrs) {
//		prüfe Parameter
		if (_pGDBK == NULL)
				return NULL;
		
long lParNum = _pGDBK -> GeoDBKeyLong();
char *MerkmalsWert;

		switch (_pGDBK -> isA()) {
		case DBKCode:		   // MerkmalsCode enthält KeyWert
				return GetMiText (lParNum, ONr, MerkmalsWert) == EC_OKAY ? MerkmalsWert : NULL;

		case DBKParameter:	  // Parameter zeigt auf MCode, der KeyWert
								// enthält
				if (lParNum <= 0 || lParNum > NumMCodes) return NULL;
				if (MCodes[lParNum-1] >= 0) {
				// aus MerkmalsCode holen
						return GetMiText (MCodes[lParNum-1], ONr, MerkmalsWert) == EC_OKAY ? MerkmalsWert : NULL;

				} else if (MStrs[lParNum-1] != NULL) {
				// KeyWert ist in *.INI bereits direkt gegeben
				char *cptr = new char [lstrlen(MStrs[lParNum-1]) +1];

						if (cptr) lstrcpy (cptr, MStrs[lParNum-1]);
						return cptr;
				} else
						return NULL;
				break;

		case DBKUnknown:
		default:
				return NULL;
		}
}

char *KeyFilter :: FieldName (long ONr, int NumMCodes, long *MCodes, char **MStrs) {
// prüfe Parameter
   if (_pDBK == NULL)
				return NULL;		

long lParNum = _pDBK -> DBaseKeyLong();
char *lpParName = _pDBK -> DBaseKeyName();
char *MerkmalsText;

		switch (_pDBK -> isA()) {
		case DBCode:			// MerkmalsCode enthält FeldNamen
				return GetMiText (lParNum, ONr, MerkmalsText) == EC_OKAY ? MerkmalsText : NULL;

		case DBParameter:	   // Parameter zeigt auf MCode, der FeldNamen
								// enthält
				if (lParNum <= 0 || lParNum > NumMCodes) return NULL;
				if (MCodes[lParNum-1] >= 0) {
				// aus MerkmalsCode holen
						return GetMiText (MCodes[lParNum-1], ONr, MerkmalsText) == EC_OKAY ? MerkmalsText : NULL;
				} else if (MStrs[lParNum-1] != NULL) {
				// FeldName ist in *.INI bereits direkt gegeben
				char *cptr = new char [lstrlen(MStrs[lParNum-1]) +1];

						if (cptr) lstrcpy (cptr, MStrs[lParNum-1]);
						return cptr;
				} else
						return NULL;

		case DBField:
		case DBTag:
				{
				// FeldName/DBaseTag ist unmittelbar gegeben
				char *cptr = new char [lstrlen (lpParName) +1];

						if (cptr) lstrcpy (cptr, lpParName);
						return cptr;
				}
				break;

		case DBUnknown:
		default:
				return NULL;
		}
}


Bool KeyFilter :: hasTag (long ONr, int NumMCodes, long *MCodes, char **MStrs) {
//		prüfe Parameter
		if (_pDBK == NULL)
				return False;

long lParNum = _pDBK -> DBaseKeyLong();
char *lpParName = _pDBK -> DBaseKeyName();
Bool Result = FALSE;
char *MerkmalsText;

		switch (_pDBK -> isA()) {
		case DBTag:
				Result = TRUE;
				break;

		case DBCode:
				if (GetMiText (lParNum, ONr, MerkmalsText) == EC_OKAY) {
						Result = DetectTag (MerkmalsText);
						DELETE_VEC (MerkmalsText);
				}
				break;

		case DBParameter:
				if (lParNum <= 0 || lParNum > NumMCodes) return NULL;
				if (MCodes[lParNum-1] >= 0) {
				// aus MerkmalsCode holen
						if (GetMiText (MCodes[lParNum-1], ONr, MerkmalsText) == EC_OKAY) {
								Result = DetectTag (MerkmalsText);
								DELETE_VEC (MerkmalsText);
						}
				} else 
				// FeldName ist bereits direkt gegeben
						Result = DetectTag (MStrs[lParNum-1]);
				break;

		case DBField:
		// FeldName/DBaseTag ist unmittelbar gegeben
				{
				char *cptr = new char [lstrlen(lpParName) +1];

						if (cptr) {
								lstrcpy (cptr, lpParName);
								Result = DetectTag (cptr);
								DELETE_VEC (cptr);
						} else
								Result = FALSE;
				}
				break;

		case DBUnknown:
		default:
				break;
		}

return Result;
}

char *KeyFilter :: TagName (long ONr, int NumMCodes, long *MCodes, char **MStrs) {
char *cptr = FieldName (ONr, NumMCodes, MCodes, MStrs);

		if (DetectTag (cptr, TRUE)) 
				return cptr;

		DELETE_VEC (cptr);

return NULL;
}

char *KeyFilter :: KeyValue (long ONr, int NumMCodes, long *MCodes, char **MStrs) {

		return FieldValue (ONr, NumMCodes, MCodes, MStrs);
}

// StrringTermKlasse zur Verwaltung von MasterTerm und SlaveTerm --------------
StringTerm :: StringTerm (char *pS1, char *pS2) 
{
		_pStr1 = new char [lstrlen(pS1)+1];
		if (_pStr1) 
				lstrcpy (_pStr1, pS1);
		_pStr2 = new char [lstrlen(pS2)+1];
		if (_pStr2) 
				lstrcpy (_pStr2, pS2);
}

StringTerm :: ~StringTerm (void) 
{
		DELETE_VEC (_pStr1);
		DELETE_VEC (_pStr2);
}

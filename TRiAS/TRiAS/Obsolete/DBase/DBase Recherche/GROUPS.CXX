// Memberfunktionen fuer GruppenListe -----------------------------------------
// File: GROUPS.CXX

#include "pheader.h"

#include <containr.hxx>
#include "groups.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
Group :: Group (char *lpName, long lId) {

		if (lpName) {
				_lpGroupName = new char [lstrlen(lpName) +1];
				if (_lpGroupName)
						lstrcpy (_lpGroupName, lpName);
		} else
				_lpGroupName = NULL;
		_lGroupIdent = lId;
}

Group :: ~Group (void) {
		DELETE_VEC (_lpGroupName);
}


// Vergleichsfunktion zweier GruppenEinträge ----------------------------------
int CompareGroups (void *pObj1, void *pObj2) {
Group *pG1 = (Group *)pObj1;
Group *pG2 = (Group *)pObj2;

long lIdCmp = (pG1 -> _lGroupIdent) - (pG2 -> _lGroupIdent);

		if (lIdCmp < 0) return -1L;
		if (lIdCmp == 0) return 0;
		return 1;
}

// EinSpeichern eines neuen GrouppenEintrages ---------------------------------
Bool Groups :: AddGroup (char *lpName, long lId) {
GroupCreator GC (*this);

		return Create (GC, Group) (lpName, lId) != NULL;
}

// Überprüfen, ob eine Gruppe bereits existiert
Bool Groups :: hasGroup (char *lpName, long lId) {
Group locG (lpName, lId);
CTable t(*this);

		if (lpName) {
				for (t.FindFirst (&locG); t.Valid(); t.FindNext (&locG)) {
				GroupLock l(t);

						if (!l) continue;
						if (l -> _lpGroupName) {
								if (!lstrcmp (l -> _lpGroupName, lpName))
										return TRUE;
						}
				}
		} else
				return t.FindFirst (&locG);

return FALSE;
}

void __export Groups :: UserDelete (void *pObj)
{ 
		((Group *)pObj) -> ~Group (); 
}

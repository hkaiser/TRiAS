// Abfragen und Setzen des SchluesselsuchContextes (KEYCONTEXT) ---------------
// File: SWITCHKC.C

#include "trias01p.hxx"

#include <switchkc.h>
#include "syncdb.hxx"

// Abfragen des aktuellen Schlüsselkontextes ----------------------------------
extern "C" void FUNCTYPE EXPORT01 GetKeyContext (KEYCONTEXT *pKC) 
{
	SYNC_DBACCESS_EX (g_pDbMutex);

	pKC -> ikcWorkingFile = working_file;
	pKC -> ikcFindField = find_field;
	memcpy (pKC -> pkcParent, parent, MAXLEVEL*sizeof(PAGE_NO));
	memcpy (pKC -> pkcSlots, slots, MAXLEVEL*sizeof(short));
	pKC -> ikcLevel = lvl;
}

// Setzen des Schlüsselkontextes ----------------------------------------------
extern "C" void FUNCTYPE EXPORT01 SetKeyContext (KEYCONTEXT *pKC) 
{
	SYNC_DBACCESS_EX (g_pDbMutex);

	working_file = pKC -> ikcWorkingFile;
	find_field = pKC -> ikcFindField;
	memcpy (parent, pKC -> pkcParent, MAXLEVEL*sizeof(PAGE_NO));
	memcpy (slots, pKC -> pkcSlots, MAXLEVEL*sizeof(short));
	lvl = pKC -> ikcLevel;
}



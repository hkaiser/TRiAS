// Relationen zwischen DBaseDateien werden in einer RelationsListe abgespeichert
// File: RELATION.CXX

#if defined (CLIPPER) || defined (MDX) || defined (NDX)
// OK
#else
	#error --- you must define CLIPPER, NDX or MDX
#endif

#include <d4all.h>
#ifdef WIN32
#include <bool.h>
#endif
#include <cxxtypes.hxx>

extern "C" {
	#include <string.h>	 	// strupr ()
	#include <protos.h>	 	// für DELETE ()
#ifndef WIN32	
	#include <storage.h>	// LPSTORAGE
#endif	
	#include <xtension.h>   // für DEX_Error ()
	#include <xtensnx.h>
}

#include "relation.htp"
#include <commonvu.hxx>
#include <containr.hxx>
#include <errcodes.hxx>

#include <objfeld.hxx>
#include <dbliste.hxx>

#include <dbasekey.hxx>
#include <relation.hxx>

// Konstruktor/Destruktor -----------------------------------------------------
__export Relation :: Relation (DBaseFiles &DBFs, MasterTerm *pMT, SlaveTerm *pST)
		  : _DBFs (DBFs)
{
	if (! (_pMaster = new char [lstrlen (pMT -> MasterDBName ()) + 1])) {
		DEX_Error (RC_ctRelation, EC_NOMEMORY);
		return;
	}
	lstrcpy (_pMaster, pMT -> MasterDBName ());
	strupr (_pMaster);

	if (! (_pMField = new char [lstrlen (pMT -> MasterField()) + 1])) {
		DEX_Error (RC_ctRelation, EC_NOMEMORY);
		return;
	}
	lstrcpy (_pMField, pMT -> MasterField());

	if (! (_pSlave = new char [lstrlen (pST -> SlaveDBName()) + 1])) {
		DEX_Error (RC_ctRelation, EC_NOMEMORY);
		return;
	}
	lstrcpy (_pSlave, pST -> SlaveDBName());
	strupr (_pSlave);

//  evtl. "<>" löschen
	DetectTag (pST -> SlaveTag(), True);

	if (! (_pSTag = new char [lstrlen (pST -> SlaveTag()) + 1])) {
		DEX_Error (RC_ctRelation, EC_NOMEMORY);
		return;
	}
	lstrcpy (_pSTag, pST -> SlaveTag());
}

__export Relation :: ~Relation (void) 
{
	DELETE_VEC (_pMaster);
	DELETE_VEC (_pSlave);
	DELETE_VEC (_pMField);
	DELETE_VEC (_pSTag);
}

Bool Relation :: Seek (CodeBase *pCB) {
//  1. Finden der DBaseDateien in der DBaseDateiListe
	CTable t1(_DBFs);
	CTable t2(_DBFs);

	if (!t1.Find (_pSlave))
		return False;
	if (!t2.Find (_pMaster))
		return False;

	DataIndexLock l1(t1);
	DataIndexLock l2(t2);

	if (!l1 || !l2)
		return False;

//  2. Selektieren des zu verwendenden Tag's
#ifdef MDX
	if (l1 -> select (_pSTag) != r4success)
		return False;
#else
#if defined (CLIPPER) || defined (NDX)
	if (!pCB)
		return False;
	Index NewIndex (l1, _pSTag);
	if (pCB -> error () != r4success)
		return False;
	l1 -> select (&NewIndex);
#endif
#endif
	Field *pMasterF = l2 -> field(_pMField);

//  3. Positionieren des Slaves
	if (l1 -> seek (*pMasterF) != r4success)
		return False;

	return True;
}

__export RelationList :: RelationList (void) 
			  : CListContainer ()
{
		// nothing to do
}

__export RelationList :: ~RelationList (void)
{
	EveryDelete();
}

void __export RelationList :: UserDelete (void *pObj) 
{
	((Relation *)pObj) -> ~Relation ();
}

Bool __export DetectTag (char *cptr, Bool toMove) 
{
		if (cptr && *cptr == '<') {
		char *tmp = strchr (cptr, '>');

				if (tmp) {
						*tmp = '\0';
						if (toMove) {
								memmove (cptr, cptr+1, lstrlen (cptr+1));
								*(tmp-1) = '\0';
						}
				} else if (toMove)
						memmove (cptr, cptr+1, lstrlen(cptr+1));

				return TRUE;
		}

return FALSE;						   
}

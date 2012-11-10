// Memberdefinition für speziellen Baum (DelTree) -----------------------------
// File: DELTREE.CXX

#include "contpre.hxx"
#include <deltree.hxx>

// Konstruktor
_DLLENTRY DelTree :: DelTree (pGetKeyFcn keyfcn, pKeyCmpFcn cmpfcn, CONTFLAG fContFlags) 
		   : CTree (keyfcn, cmpfcn, CONTFLAG(CFSyncThreads|fContFlags))
{
	// nothing to do
}

// Destruktor
_DLLENTRY DelTree :: ~DelTree (void) 
{
	// nothing to do
}

#if 0 // ======================================================================
// Delete für IdTree1, gibt Speicherplatz für Objekt nicht frei
Bool _DLLENTRY DelTree :: Delete (CNode *node) 
{
	if (CContainer :: WODelete (node)) {
	CBinaryNode * bnode = (CBinaryNode *) node;

		if (!bnode -> Left())
			bnode -> Parent() -> Graft (bnode, bnode -> Right());
		else if (!bnode -> Right())
			bnode -> Parent() -> Graft (bnode, bnode -> Left());
		else {
		CBinaryNode * righty = bnode -> Left() -> RightMost();

			if (righty != bnode -> Left()) {
				righty -> Parent() -> SetRight (righty -> Left());
				if (righty -> Left())
					righty -> Left() -> SetParent (righty -> Parent());

				righty -> SetLeft (bnode -> Left());
				bnode -> Left() -> SetParent (righty);
			}

			righty -> SetRight (bnode -> Right());
			bnode -> Right() -> SetParent (righty);

			bnode -> Parent() -> Graft (bnode, righty);
		}
		delete bnode;
		return TRUE;
	} else
		return FALSE;
}
#endif // =====================================================================

void _DLLENTRY DelTree :: UserDelete (void *) {}


// Routinen für UniqueTree -- Ein Baum, der nur eindeutige Schlüssel erlaubt
// Konstruktor
_DLLENTRY UniqueTree :: UniqueTree (pGetKeyFcn keyfcn, pKeyCmpFcn cmpfcn, CONTFLAG fContFlags)
		      : CTree (keyfcn, cmpfcn, CONTFLAG(CFUniqueKey|fContFlags))
{
	// nothing to do
}

// Destruktor
_DLLENTRY UniqueTree :: ~UniqueTree (void) 
{
	// nothing to do
}

#if 0 //=======================================================================
// Spezielle EinfügeRoutine, die eindeutige Schlüssel gewährleistet -----------
Bool _DLLENTRY UniqueTree :: Insert (FSHandle h, void *pobj)
{
	if (Count()) {
	void *key = (*m_pGetKeyFcn)(pobj);

		for (CBinaryNode *look = m_pRoot -> Left(); look; ) {
		int cmp = look -> Compare (key);

			if (cmp == 0) {			// doppelter Key
				return FALSE;
			} else if (cmp > 0) {		// key > this
				if (look -> Right())
					look = look -> Right();
				else {
					look -> SetRight (new CBinaryNode (h, *this, look));
					break;
				}
			} else if (cmp < 0) {		// key < this
				if (look -> Left())
					look = look -> Left();
				else {
					look -> SetLeft (new CBinaryNode (h, *this, look));
					break;
				}
			}
		}
	} else
		m_pRoot -> SetLeft (new CBinaryNode (h, *this, m_pRoot));

return CKeyContainer :: Insert (h, pobj);	// updates the Count (), etc...
}


#if !defined(NOWODELETE)
// Das Löschen der Bäume erfordert ein spezielles Delete, welches das
// Objekt selbst nicht löscht
Bool _DLLENTRY CContainer :: WODelete (CNode *node) 
{
	if (node -> Locked ()) return FALSE;

	// Notify all the navigators.
	for (int i = 0; i < MAX_NAVIGATORS; i++)
		if (m_grNavs[i])
			m_grNavs[i] -> DeleteNotify (node);

	node -> SetHandle (0);
	--m_ulCount;

return TRUE;
}
#endif

#endif //======================================================================

// Relationen zwischen DBaseDateien werden in einer RelationsListe abgespeichert
// File: RELATION.HXX

#if !defined(_RELATION_HXX)
#define _RELATION_HXX

Bool DetectTag (char *cptr, Bool toMove);

class MasterTerm;
class SlaveTerm;
class DBaseFiles;
class CodeBase;

class Relation {
	DBaseFiles &_DBFs;      // Liste aller DBaseDateien
	char *_pSlave;          // Name der SlaveDB
	char *_pMaster;         // Name der MasterDB
	char *_pMField;         // Name des MasterFeldes
	char *_pSTag;           // Name des SlaveTags

public:
		Relation (DBaseFiles &DBFs, MasterTerm *pMT, SlaveTerm *pST);
		~Relation (void);

	Bool Seek (CodeBase *pCB);
};

class RelationList : public ListContainer {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		RelationList ();
		~RelationList (void);
};
DeclareLock (RelationList, Relation);

#endif // _RELATION_HXX

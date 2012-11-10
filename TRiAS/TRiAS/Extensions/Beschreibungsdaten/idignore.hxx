// Liste aller im weiteren zu ignorierenden Identifikatoren
// File: IDIGNORE.HXX

#if !defined(_IDIGNORE_HXX)
#define _IDIGNORE_HXX

class IgnoreId {
private:
	long _Id;

public:
		IgnoreId (long Id) { _Id = Id; }
		~IgnoreId (void) {}

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};

class IdIgnoreList : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		IdIgnoreList (void);
		~IdIgnoreList (void);

	bool Add (long Ident);
	bool Find (long Ident);
};
DeclareLock (IdIgnoreList, IgnoreId);

#endif 	// IDIGNORE_HXX

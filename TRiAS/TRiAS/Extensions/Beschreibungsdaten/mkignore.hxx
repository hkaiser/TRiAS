// Liste aller im weiteren zu ignorierenden Merkmale
// File: MKIGNORE.HXX

#if !defined(_MKIGNORE_HXX)
#define _MKIGNORE_HXX

class IgnoreMCode {
private:
	long _MCode;

public:
		IgnoreMCode (long MCode) { _MCode = MCode; }
		~IgnoreMCode (void) {}

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};

class MCodeIgnoreList : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		MCodeIgnoreList (void);
		~MCodeIgnoreList (void);

	bool Add (long MCode);
	bool Find (long MCode);
};
DeclareLock (MCodeIgnoreList, IgnoreMCode);

#endif 	// MKIGNORE_HXX

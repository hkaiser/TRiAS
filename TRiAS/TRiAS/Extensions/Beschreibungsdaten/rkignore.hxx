// Liste aller im weiteren zu ignorierenden RelationsCodes -------------------
// File: RKIGNORE.HXX

#if !defined(_RKIGNORE_HXX)
#define _RKIGNORE_HXX

class IgnoreRC {
private:
	long m_lRCode;

public:
		IgnoreRC (long lRCode) { m_lRCode = lRCode; }
		~IgnoreRC (void) {}

friend void *GetLongKey (void *pObj);
friend int CmpLongKey (void *pObj1, void *pObj2);
};

class RCodeIgnoreList : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		RCodeIgnoreList (void);
		~RCodeIgnoreList (void);

	bool Add (long lRCode);
	bool Find (long lRCode);
};
DeclareLock (RCodeIgnoreList, IgnoreRC);

#endif 	// _RKIGNORE_HXX

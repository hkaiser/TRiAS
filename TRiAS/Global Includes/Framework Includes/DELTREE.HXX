// Baum (Container), der spezielles Delete hat --------------------------------
// File: DELTREE.HXX

#if !defined(_DELTREE_HXX)
#define _DELTREE_HXX

class _CTR_ENTRY32 DelTree : public CTree {
protected:
	void UserDelete (void *pObj);
#if 0 // durch m_fContFlags überflüssig geworden (#HK940605)
	bool Delete (CNode *node);
#endif

public:
// Konstruktor
		DelTree (pGetKeyFcn keyfcn, pKeyCmpFcn cmpfcn = StrCmp, 
			 CONTFLAG fContFlags = CFNoSpecial);
// Destruktor
		~DelTree (void);
};

class _CTR_ENTRY32 UniqueTree : public CTree {
protected:
	void UserDelete (void *pObj) = 0;
#if 0 // durch m_fContFlags überflüssig geworden (#HK940605)
	bool Insert (FSHandle, void *);
#endif

public:
		UniqueTree (pGetKeyFcn keyfcn, pKeyCmpFcn cmpfcn = StrCmp, 
			    CONTFLAG fContFlags = CONTFLAG(CFDefault|CFUniqueKey));
		~UniqueTree (void);
};

#endif // _DELTREE_HXX

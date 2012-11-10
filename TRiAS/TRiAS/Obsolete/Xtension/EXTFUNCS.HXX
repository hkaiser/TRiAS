// Verwaltung von Funktionen, die von anderen Erweiterungen exportiert sind
// File: EXTFUNCS.HXX

#if !defined(_EXTFUNCS_HXX)
#define _EXTFUNCS_HXX

class ExtFuncProc : public DLLBind {
private:
	char *_pName;

public:
		ExtFuncProc (const char *pName);
		~ExtFuncProc (void);

friend void *GetDLLName (void *pObj);
};

class ExtFuncProcTree : public Tree {
protected:
	void UserDelete (void *pObj);

public:
		ExtFuncProcTree (void) : Tree (GetDLLName, StrCmp) {}
		~ExtFuncProcTree (void) { EveryDelete(); }
};
DeclareLock (ExtFuncProcTree, ExtFuncProc);


#endif // _EXTFUNCS

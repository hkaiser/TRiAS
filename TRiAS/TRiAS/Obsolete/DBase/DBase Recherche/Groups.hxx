// Klassendeklaration fuer die Klassifikationsgruppen -------------------------
// File: GROUPS.HXX


#if !defined(_GROUPS_HXX)
#define _GROUPS_HXX

class Group {
private:
	char *_lpGroupName;
	long _lGroupIdent;

public:
// Konstruktor/Destruktor
		Group (char *, long);
		~Group (void);

friend void *GetGroupKey (void *pObj) { return pObj; }
friend int CompareGroups (void *, void *);
friend class Groups;
};

class Groups : public CTree {
protected:

	void UserDelete (void *pObj);

public:
// Konstruktor
		Groups (void) : CTree (GetGroupKey, CompareGroups) {}
		~Groups (void) { EveryDelete (); }

// sonstige Member
	Bool AddGroup (char *, long);
	Bool hasGroup (char *, long);
};
DeclareLock (Groups, Group);


#endif // _GROUPS_HXX

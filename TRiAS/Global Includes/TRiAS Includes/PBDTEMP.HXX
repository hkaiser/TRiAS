// Temporaerer Baum fuer temp. PBD-Items --------------------------------------
// File: PBDTEMP.HXX

#if !defined(_PBDTEMP_HXX)
#define _PBDTEMP_HXX

class _TRIAS02_ENTRY PBDTempTree : public CTree {
protected:
	void UserDelete (void *pObj) 
	{
        	((PBD_Data *)pObj) -> /*PBD_Data :: */~PBD_Data ();
	}

public:
// Konstruktor/Destruktor
		PBDTempTree (void);
		~PBDTempTree (void);
};
DeclareLock (PBDTempTree, PBD_Data);

#endif // _PBDTEMP_HXX


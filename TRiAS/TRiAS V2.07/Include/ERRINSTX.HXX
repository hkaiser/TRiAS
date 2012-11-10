// Klasse, die FehlerBehandlung als ScopingClass verwaltet --------------------
// Version für TRIAS(R)-Erweiterungen
// File: ERRINSTX.HXX

#if !defined(_ERRINST_HXX)
#define _ERRINST_HXX

typedef int (*ERRHANDLER)(int,int,...);

class ErrInstall {
public:
	enum ErrHandling {
		EIgnore = 0,
		EDefault = 1,
	};

private:
	ERRHANDLER _oldEH;      // alte Methode
	ErrCode _RC;

public:
		ErrInstall (ErrCode RC, ErrHandling EH = EIgnore)
			{ ErrCode rc; DEX_ErrInstall (rc, _RC = RC, (ERRHANDLER)(void *)(DWORD)EH, &_oldEH); }
		ErrInstall (ErrCode RC, ERRHANDLER EH)
			{ ErrCode rc; DEX_ErrInstall (rc, _RC = RC, EH, &_oldEH); }
		ErrInstall (ErrCode RC, ERRHANDLER EH, DWORD pData)
			{ ErrCode rc; DEX_ExtErrInstall (rc, _RC = RC, EH, &_oldEH, pData); }
		~ErrInstall (void) 
			{ ErrCode rc; DEX_ErrInstall (rc, _RC, _oldEH, NULL); }
};

#endif // _ERRINST_HXX


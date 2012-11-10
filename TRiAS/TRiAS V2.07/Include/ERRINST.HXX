// Klasse, die FehlerBehandlung als ScopingClass verwaltet --------------------
// File: ERRINST.HXX

#if !defined(_ERRINST_HXX)
#define _ERRINST_HXX

typedef int ERRHANDLERFUNC (int, int, ...);
typedef int (*ERRHANDLERPROC)(int,int,...);

class ErrInstall {
public:
	enum ErrHandling {
		EIgnore = 0,
		EDefault = 1,
	};

private:
	ERRHANDLERPROC _oldEH;	// alte Methode
	ErrCode _RC;

public:
		ErrInstall (ErrCode RC, ErrHandling EH = EIgnore)
			{ err_install (_RC = RC, (ERRHANDLERPROC)(void *)(DWORD)EH, &_oldEH); }
		ErrInstall (ErrCode RC, ERRHANDLERPROC EH)
			{ err_install (_RC = RC, EH, &_oldEH); }
		ErrInstall (ErrCode RC, ERRHANDLERPROC EH, void *pData)
			{ ExtErrInstall (_RC = RC, EH, &_oldEH, pData); }
		~ErrInstall (void) 
			{ err_install (_RC, _oldEH, 0); }
};

#endif // _ERRINST_HXX


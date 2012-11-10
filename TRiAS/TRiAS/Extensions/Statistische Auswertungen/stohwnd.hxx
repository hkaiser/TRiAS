// Klassendefinitionen fÅr SHWND-Baum-----------------------------------------
// File : STOHWND.HXX

#if !defined (_STOHWND_HXX)
#define _STOHWND_HXX

class SHWND  {

private:
	HWND _Shwnd;

public:
// Konstruktor/Destruktor
		SHWND (HWND Shwnd);
		~SHWND (void);


// ZugriffsFunktionen fÅr Baum
friend void _XTENSN_EXPORT *GetHwnd (void *pWnd);
friend int _XTENSN_EXPORT CmpHwnds (void *pWnd1, void *pWnd2);


// ZugriffsFunktionen auf Element HWND
	HWND &Shwnd (void) { return _Shwnd; }


};

class SHWNDTree : public CTree {
protected:
	void _XTENSN_EXPORT UserDelete (void *pWnd);

public:
// Konstruktor/Destruktor 
		SHWNDTree (void);
		~SHWNDTree (void);
};
DeclareLock (SHWNDTree, SHWND);		// notwendige Klassendefinitionen

#endif // _STOHWND_HXX

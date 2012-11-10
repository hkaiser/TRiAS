#ifndef _CLIPBRD_HXX

#include "clipdef.h"

// #define _DLLENTRY

class DummyWindow : public TopAppWindow {
public :
            DummyWindow (void) {};
};

class CClipBoardLock {
	BOOL	locked;

public:
		CClipBoardLock (HWND hwd);
		~CClipBoardLock (void);

	BOOL Locked (void) { return locked; }
};


class MemoryDC {
private:
	HDC	hmemoryDC;

public:	
		MemoryDC (HDC hDC) ;
		~MemoryDC (void);

	HDC Handle() { return hmemoryDC; }
};

class DisplayDC {
private:
	HDC	hDC;
	HWND	hwnd;

public:
		DisplayDC (HWND hwd ) ;
		~DisplayDC (void);

	HDC Handle() { return hDC ; }
};

 
class CClipBoard_Imp
{
	DummyWindow     dummy;

public:

		CClipBoard_Imp (void);

	void	Clear (void);
	void	Insert (const char *txt);
	void	Insert (const pBitmap );
	long	GetItemSize (int);
	BOOL	Retrieve (char *, int len);
	BOOL	Retrieve (pBitmap);

		~CClipBoard_Imp (void);
};

#endif



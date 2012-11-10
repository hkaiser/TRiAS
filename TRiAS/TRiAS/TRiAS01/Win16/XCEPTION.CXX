// Abfangen von SystemInterrupts um alles sicher auf die Platte zu kriegen
// File: XCEPTION.CXX

#include "trias01p.hxx"

#if !defined(WIN32)

#include <toolhelp.h>

#include "resource.h"
	
extern "C" void NEAR PASCAL EXCEPTIONHANDLER (void);
extern "C" void FAR PASCAL ShutdownInterruptHandler (void);

/* undocumented function */ 
extern "C" extern int FAR PASCAL SysErrorBox(LPSTR msg, LPSTR title,
				  WORD lButton, WORD mButton, WORD rButton);

#include <freestor.hxx>

extern "C" {

#define _FP_SEG(fp) (*((unsigned __far *)&(fp)+1))
#define _FP_OFF(fp) (*((unsigned __far *)&(fp)))
#define _MK_FP(s,o) ((void __far *)(((DWORD)(void __far*)(s)<<16)|(o)))

#define HMODULE_FROM_HTASK(hTask)	(HMODULE)(*((WORD __far *)_MK_FP(hTask,0x1e)))
#define GetCurrentModule() 		HMODULE_FROM_HTASK(GetCurrentTask())

#define SEB_OK      1
#define SEB_CANCEL  2
#define SEB_YES     3
#define SEB_NO      4
#define SEB_RETRY   5
#define SEB_ABORT   6
#define SEB_IGNORE  7

#define SEB_DEFAULT 0x8000

// Hier an dieser Stelle wird ein Behandlung eines GP's vorgeschlagen ---------
char cbSEBCaption[_MAX_PATH +1] = { '\0' };
char cbSEBText[_MAX_PATH +1] = { '\0' };
extern HINSTANCE g_hInstance;

typedef int (PASCAL * SYSERRORBOXPROC) (char *, char *, WORD, WORD, WORD);

static void DoExceptionHandling (int wNumber);

char *g_pTempStack = NULL;	// Zeiger auf einen temporären Stack
char *g_pTempStackEnd;		// Offset zum Ende des TempStacks

WORD old_ss;            	// Sichern von SS:SP am Beginn
WORD old_sp;

WORD new_ss;
WORD new_sp;

HMODULE g_hTrias = NULL;

void near CExceptionHandler (
		WORD wES, WORD wDS,
		WORD wDI, WORD wSI,
		WORD wBP, WORD wSP,
		WORD wBX, WORD wDX,
		WORD wCX, WORD wAX,
		WORD wOldBP, 
		WORD wRetIP, WORD wResCS,
		WORD wRealAX,
		WORD wNumber,
		WORD wHandle,
		WORD wIP, WORD wCS, WORD wFlags)
{
static WORD s_fInHandler = false;

	if (wNumber == 1 || wNumber == 3 || wNumber == 256)
		return;
		
	if (s_fInHandler) return;
	s_fInHandler = true;
	
// Stack umschalten
	new_ss = _FP_SEG(g_pTempStackEnd);
	new_sp = _FP_OFF(g_pTempStackEnd);
	
	__asm 	mov 	old_ss, ss
	__asm	mov 	old_sp, sp
	__asm	mov	ax, new_ss
	__asm	mov	ss, ax
	__asm	mov	sp, new_sp

	if (g_hTrias == GetCurrentModule())
		DoExceptionHandling (wNumber);		// unser GP

// Stack zurückschalten		
	__asm 	mov	ss, old_ss
	__asm	mov	sp, old_sp
	s_fInHandler = false;
	
return;
}

static void DoExceptionHandling (int wNumber)
{
// FlushDB rufen
	db_flush (FLUSH_ALLDATA);
	db_pzflush (FLUSH_ALLDATA);

HINSTANCE hModule = (HINSTANCE)GetModuleHandle((LPSTR) "USER");
SYSERRORBOXPROC SysErrorBox = (SYSERRORBOXPROC)GetProcAddress (hModule, (LPSTR) (DWORD) 320);

	SysErrorBox (cbSEBText, cbSEBCaption, 0, SEB_OK | SEB_DEFAULT, 0);
}


// Initialisierung/DeInitialisierung der ExceptionHandlerRoutine --------------
#define TEMPSTACK_SIZE  4096

bool __export PASCAL SetupInterruptHandler (void)
{
	g_hTrias = GetModuleHandle ((LPSTR)"TRIAS");

	g_pTempStack = new char [TEMPSTACK_SIZE];
	if (!g_pTempStack) return false;
    
	g_pTempStackEnd = ((g_pTempStack + TEMPSTACK_SIZE) - 2);

// Stringresourcen laden
	LoadString (g_hInstance, IDS_FATALEXITCAPTION, cbSEBCaption, _MAX_PATH);
	LoadString (g_hInstance, IDS_FATALEXIT, cbSEBText, _MAX_PATH);
    
return InterruptRegister (NULL, (FARPROC)EXCEPTIONHANDLER);
}

void __export PASCAL ShutdownInterruptHandler (void)
{
	InterruptUnRegister (NULL);
	if (g_pTempStack) {	// nicht doppelt freigeben
		delete g_pTempStack;
		g_pTempStack = NULL;
	}
}

}	// extern "C" 

#endif // !WIN32

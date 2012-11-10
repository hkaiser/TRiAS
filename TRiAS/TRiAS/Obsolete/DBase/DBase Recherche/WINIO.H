/*
WINIO.H
Stdio (e.g. printf) functionality for Windows - definition
Dave Maxey - 1991
*/

#ifdef __cplusplus
extern "C" {
#endif
/* ==== STDIO.H for Windows ==== */
#include <stdarg.h>
#include <stdio.h>

#ifndef WIN32
#undef putchar
#define putchar fputchar
#undef getchar
#define getchar fgetchar

int FAR __cdecl puts (const char FAR *);
int FAR __cdecl fputchar (int);
int FAR __cdecl fgetchar (void);
#endif

/* ==== Extensions ==== */

/* winio_init() must be called before any of the above listed
functions to init the i/o window. Similar arguments to WinMain(), but
we drop the cmdline pointer but add a bufsize parameter (unsigned) -
0 means default (8k). */
int winio_init(HANDLE, HANDLE, int, unsigned);

/* Makes the window inactive, and allows the user to view and play with
it until double- clicking on the system menu to close it. NEVER RETURNS. */
void winio_end(void);

/* closes the window immediately and frees up buffers */
void winio_close(void);

/* to override default title of "Console I/O" */
void winio_settitle(BYTE *);

/* May be SYSTEM_FIXED_FONT (default), ANSI_FIXED_FONT, or OEM_FIXED_FONT */
BOOL winio_setfont(WORD);

/* To turn automatic updating of window off and on */
BOOL winio_setpaint(BOOL);

/* clear out the contents of the buffer and start over fresh */
void winio_clear(void);

/* should be used to release cpu in spells between I/O calls. A
WM_QUIT message received by it will exit the application. If that is
a problem, use the winio_onclose function below */
void winio_yield(void);

/* Returns the underlying Windows window handle to WINIO window */
HWND winio_hwnd(void);

/* ==== User definable exit routine ==== */

typedef void (* DESTROY_FUNC)(void);

/* Optional notification function; without it, there is no way for your
application to know if the user has double-clicked the system menu box */
void winio_onclose(DESTROY_FUNC);

/* ==== Utility function built on message box ==== */

BOOL winio_warn(BOOL, const BYTE *, ...);
#ifdef __cplusplus
}
#endif

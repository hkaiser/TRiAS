/*
WMHANDLR.H
Event (WM_ message) handlers - interface
Dave Maxey and Andrew Schulman - 1991

wmhandler_init MUST be called before a window is opened.

wmhandler_get returns current handler for an event.

wmhandler_set also returns current handler, and then makes
supplied handler current for the message type.
*/

#ifdef __cplusplus
extern "C" {
#endif
typedef long (*WMHANDLER)(HWND, unsigned, WORD, LONG);

long FAR PASCAL _export WinioWndProc(HWND, WORD, WORD, LONG);
void wmhandler_init(void);
WMHANDLER wmhandler_get(unsigned);
WMHANDLER wmhandler_set(unsigned, WMHANDLER);
#ifdef __cplusplus
}
#endif


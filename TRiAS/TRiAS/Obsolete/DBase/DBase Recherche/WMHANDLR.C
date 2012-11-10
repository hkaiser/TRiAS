/*
WMHANDLR.C
Event (WM_ message) handlers - implementation
Dave Maxey and Andrew Schulman - 1991
*/

#include <windows.h>
#include "wmhandlr.h"

long            defwmhandler(HWND, unsigned, WORD, LONG);

WMHANDLER       wmhandler[WM_USER];

/* -----------------------------------------------------------------------  */
/* This is our event processor. It is the dispatcher for the handlers set   */
/* using SetHandler. An Application plugs this function into its            */
/* window, sets handlers for messages, and WndProc handles the rest.        */
/* This window procecedure should never need to be changed!                 */
/* -----------------------------------------------------------------------  */
long FAR PASCAL _export WinioWndProc(HWND hWnd, WORD message, 
    WORD wParam, LONG lParam)
    {
    if (message < WM_USER)
        return (*wmhandler[message])(hWnd, message, wParam, lParam);
    else
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

/* ---------------------------------------------------------------- */
/* Routines to get and set the message handlers. Setting to NULL    */
/* uninstalls a handler, by setting the handler to the default      */
/* which calls Windows own DefWndProc.                              */
/* ---------------------------------------------------------------- */
WMHANDLER wmhandler_get(unsigned message)
    {
    return (message < WM_USER) ? wmhandler[message] : 0;
    }

WMHANDLER wmhandler_set(unsigned message, WMHANDLER f)
    {
    WMHANDLER oldf;
    if (message < WM_USER)
        {
        oldf = wmhandler[message];
        wmhandler[message] = f ? f : defwmhandler;
        return (oldf ? oldf : defwmhandler);
        }
    else
        return 0;
    }

/* ----------------------------------------------------------------------- */
/* This is a default handler so that an application chain on to a previous */
/* handler from their current one without having to worry what was there   */
/* before. All this default handler does is to call DefWindowProc.         */
/* ----------------------------------------------------------------------- */
long defwmhandler(HWND hwnd, unsigned message, WORD wParam, LONG lParam)
    {   
    return DefWindowProc(hwnd, message, wParam, lParam);
    }

/* -------------------------------------------------------------------  */
/* MUST BE CALLED BEFORE THE APPLICATION WINDOW IS CREATED -            */
/* Just inits the array of handlers to the default..                    */
/* -------------------------------------------------------------------  */
void wmhandler_init(void)
    {
    WMHANDLER *pwm;
    int i;
    for (i=0, pwm=wmhandler; i < WM_USER; i++, pwm++) 
        *pwm = defwmhandler;
    }

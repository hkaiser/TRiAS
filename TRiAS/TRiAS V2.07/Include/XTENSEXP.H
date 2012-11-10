// Funktionen, die von diversen Erweiterungen exportiert werden ---------------
// File: XTENSEXP.H

#if !defined(_XTENSEXP_H)
#define _XTENSEXP_H

#if defined(__cplusplus)
extern "C" {
#endif

// BILDER.EXT -----------------------------------------------------------------
typedef BOOL FAR (PASCAL *SHOWIMAGEPROC)(char *, char *);
typedef BOOL FAR (PASCAL *HIDEIMAGEPROC)(void);

BOOL FAR PASCAL ShowImage (char *pImage, char *);
BOOL FAR PASCAL HideImage (void);


// CNTRPROJ.EXT --------------------------------------------------------------
typedef BOOL FAR (PASCAL *SWITCHTOPROJECTPROC)(char *, char *, char *, short);
typedef BOOL FAR (PASCAL *RETURNTOPREVIOUSPROJECT)(void);

BOOL FAR PASCAL SwitchToProject (char *pDBKey, char *pUser, char *pView, short);
BOOL FAR PASCAL ReturnToPreviousProject (void);

#if defined(__cplusplus)
}
#endif

#endif // _XTENSEXP_H

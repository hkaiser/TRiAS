// Trick, der Limitierung von VC++ 2.1 umgeht, 
// welches DS_CONTEXTHELP nicht kennt
// File: DLGTRICK.H

#if !defined(_DLGTRICK_H)
#define _DLGTRICK_H

#undef DS_MODALFRAME
#define DS_MODALFRAME	0x2080L

#undef WS_CHILD
#define WS_CHILD	0x40000400L

#endif // _DLGTRICK_H

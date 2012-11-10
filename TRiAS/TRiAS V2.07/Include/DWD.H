/* Struktur eines Passworteintrages im DB-Passwortfile          */
/* File: DWD.H                  last update: 5. Oktober 1989    */

#ifndef _DWD_H
#define _DWD_H
 
#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

struct dbpasswd {
        char *dw_name;
        char *dw_passwd;
        int dw_uid;
        unsigned long dw_access;
        unsigned long dw_rw;
        char *dw_comment;
};

#if !defined(FUNCTYPE)
#if defined(DLL)
#define FUNCTYPE _pascal
#else
#define FUNCTYPE _cdecl
#endif
#endif

void FUNCTYPE setdwent (char *dwdfile);
void FUNCTYPE enddwent (void);
struct dbpasswd *FUNCTYPE getdwent (void);
struct dbpasswd *FUNCTYPE getdwnam (char *name, char *dbname); 
struct dbpasswd *FUNCTYPE getdwuid (int uid, char *dbname);

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _DWD_H

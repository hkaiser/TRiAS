/* Versionskennzeichnung der DB-Software                        */
/* File: DBVERSIO       @(#)dbversio.msk        2.5     4/10/90 */ 

#ifndef _DBVERSION_H
#define _DBVERSION_H

#ifndef NOCOPYRIGHT
static char Date[] = "#@D";
static char Version[] = "V@A.@B";
static char Copyright[] = "Copyright(C) 1991 - 2001, TRiAS Potsdam";
static char Release[] = ".@C";
 
#define D_LEN sizeof(Date)
#define V_LEN sizeof(Version)
#define C_LEN sizeof(Copyright)
#define R_LEN sizeof(Release)
#endif
 
#endif // _DBVERSION_H

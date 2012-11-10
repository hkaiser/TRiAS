/* Versionskennzeichnung der DB-Software                        */
/* File: DBVERSIO               @(#)dbversio.msk        2.5     4/10/90 */ 

#ifndef _DBVERSION_H
#define _DBVERSION_H

//short FUNCTYPE mycrypt (unsigned char *, int);

#ifndef NOCOPYRIGHT
static char Date[] = "#KK970615";
static char Version[] = "V1.01";
static char Copyright[] = "Copyright (C) 1992 - 1997 uve GmbH FEZ Potsdam";
static char Release[] = ".014";
 
#define D_LEN sizeof(Date)
#define V_LEN sizeof(Version)
#define C_LEN sizeof(Copyright)
#define R_LEN sizeof(Release)
#endif
 
#define COPYRIGHT_CRC 0x0001 
#define COPYRIGHT_LEN 80

#endif // _DBVERSION_H

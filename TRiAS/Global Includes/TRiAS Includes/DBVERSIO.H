/* Versionskennzeichnung der DB-Software                        */
/* File: DBVERSIO               @(#)dbversio.msk        2.5     4/10/90 */ 

#ifndef _DBVERSION_H
#define _DBVERSION_H

#if defined(__cplusplus)
extern "C" {
#endif

// short FUNCTYPE mycrypt ();

#ifndef NOCOPYRIGHT
//static char Date[] = "#HK920727";
//static char Version[] = "V5.00";
//static char Copyright[] = "Copyright (C) Fernerkundungszentrum uve Potsdam GmbH";
//static char Release[] = ".003";
static char Date[] = "#HK010703";
static char Version[] = "V6.00";
static char Copyright[] = "Copyright© TRiAS Potsdam";
static char Release[] = ".003";
 
#define D_LEN sizeof(Date)
#define V_LEN sizeof(Version)
#define C_LEN sizeof(Copyright)
#define R_LEN sizeof(Release)
#endif
 
#define COPYRIGHT_CRC 0x49de 
#define COPYRIGHT_LEN 80

#if defined(__cplusplus)
}
#endif

#endif // _DBVERSION_H

/* Versionskennzeichnung der DB-Software                        	*/
/* File: DBVERSIO               @(#)dbversio.msk        2.5     4/10/90 */ 

#ifndef _DBVERSION_H
#define _DBVERSION_H

#ifndef NOCOPYRIGHT
static char Date[] = "#HK000126";
static char Version[] = "V2.00";
static char Copyright[] = "Copyright(C) 1991 - 2000, TRiAS GmbH Potsdam";
static char Release[] = ".004";
 
#define D_LEN sizeof(Date)
#define V_LEN sizeof(Version)
#define C_LEN sizeof(Copyright)
#define R_LEN sizeof(Release)
#endif
 
#endif // _DBVERSION_H

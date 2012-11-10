/* Fehlerkodedefinitionen fuer ASC-Parser			*/
/* File: ASCERRS.H						*/

#if !defined(_ASCERRS_H)
#define _ASCERRS_H

typedef struct err_par {
	int iLineNumber;
	char *pString;
	char *pFile;
} ERROR_PARAMETER;

/* Routinennummern */
#define ASCPARSER	8350
#define ASCSCANNER	8351

/* Fehlerkodes */
#define EOKAY	0

#define EBADRC	-760
#define EPKTID	-761
#define ELINID	-762
#define EFLID	-763
#define EBREL	-764
#define EKOORD	-765
#define ESYNTX	-766
#define ENOHD	-768
#define EGCNT	-769
#define EMCNT	-770
#define EBADKO  -771
#define EFKID	-772

#define ENOEND	760

void yyerror (char *);
int __cdecl esyntx (int errcode, int routine, ...);

#endif // _ASCERRS_H

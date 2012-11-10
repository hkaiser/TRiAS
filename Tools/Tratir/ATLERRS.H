/* Fehlerkodedefinitionen fuer ATL-Parser                       */
/* File: ATLERRS.H                                              */

#if !defined(_ATLERRS_H)
#define _ATLERRS_H

typedef struct err_par {
	int line_number;
	char *string;
} ERROR_PARAMETER;

/* Fehlerkodes */
#define EOKAY   0

#define EBADRC  -760
#define EPKTID  -761
#define ELINID  -762
#define EFLID   -763
#define EBREL   -764
#define EKOORD  -765
#define ESYNTX  -766
#define ENOHD   -768
#define EGCNT   -769
#define EMCNT   -770

#define ENOEND  760

#endif // _ATLERRS_H

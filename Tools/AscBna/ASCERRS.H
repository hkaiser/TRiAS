/* Fehlerkodedefinitionen fuer ASC-Parser			*/
/* File: ASCERRS.H						*/

/* ASCPARSER: %W%	%E%
 */

typedef struct err_par {
	int line_number;
	char *string;
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
int cdecl db_error (int, int, ...);

typedef union {
    char *string;
    shpid_t pgno;
    int number;
    float flt;
} YYSTYPE;
#define	ID	258
#define	STRCONST	259
#define	INTCONST	260
#define	IOPARAM	261
#define	FLOATCONST	262
#define	CREATE	263
#define	INSERT	264
#define	OPEN	265
#define	CLOSE	266
#define	QUIT	267
#define	SELECT	268
#define	DELETE	269
#define	NL	270
#define	ERROR	271
#define	CHECK	272
#define	SPLIT	273
#define	HELP	274
#define	DUMP	275
#define	ONLY	276
#define	SET	277
#define	STRUCT	278
#define	WRITE	279
#define	ECHO_TOKEN	280
#define	EVALSPLIT	281
#define	EVALPENALTY	282
#define	LOADFILE	283
#define	PREDINFO	284
#define	CREATEANL	285
#define	OPENANL	286
#define	CLOSEANL	287
#define	WKLDSTATS	288
#define	SPLITSTATS	289
#define	PENALTYSTATS	290
#define	ANLINFO	291


extern YYSTYPE yylval;

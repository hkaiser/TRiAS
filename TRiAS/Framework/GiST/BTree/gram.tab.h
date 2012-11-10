#ifndef BISON_GRAM_TAB_H
# define BISON_GRAM_TAB_H

#ifndef YYSTYPE
typedef union {
    BTkey *key;
    char *string;
    BToper oper;
    GiSTpredicate *pred;
    int number;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	ID	257
# define	STRCONST	258
# define	INTCONST	259
# define	CREATE	260
# define	INSERT	261
# define	DROP	262
# define	OPEN	263
# define	CLOSE	264
# define	QUIT	265
# define	SELECT	266
# define	DELETE	267
# define	WHERE	268
# define	FROM	269
# define	NL	270
# define	ERROR	271
# define	AND	272
# define	OR	273
# define	DEBUG	274
# define	HELP	275
# define	DUMP	276
# define	opLE	277
# define	opGE	278
# define	opNE	279
# define	NOT	280


extern YYSTYPE yylval;

#endif /* not BISON_GRAM_TAB_H */

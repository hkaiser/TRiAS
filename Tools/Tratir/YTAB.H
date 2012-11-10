
typedef union  {
	struct tagSTRINGTOKEN strtok;
	struct tagNUMBERTOKEN numtok;
	struct tagFLOATTOKEN flttok;
} YYSTYPE;
extern YYSTYPE yylval;
#define T_STRING 257
#define T_STERN 258
#define T_LBDA 259
#define T_PHI 260
#define T_INT 261
#define T_FLOAT 262

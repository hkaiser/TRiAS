
typedef union  {
	STRING_TOKEN strtok;
	NUMBER_TOKEN numtok;
	FLOAT_TOKEN flttok;
} YYSTYPE;
extern YYSTYPE yylval;
#define T_STRING 257
#define T_MISTRING 258
#define T_INTEGER 259
#define T_PSATZ 260
#define T_LSATZ 261
#define T_FSATZ 262
#define T_DSATZ 263
#define T_GSATZ 264
#define T_MSATZ 265
#define T_RSATZ 266
#define T_TSATZ 267
#define T_WSATZ 268
#define T_ESATZ 269
#define T_IDENT 270
#define T_BSATZ 271
#define T_ISATZ 272
#define T_CSATZ 273
#define T_VSATZ 274
#define T_HRELSATZ 275
#define T_KRELSATZ 276
#define T_BRELSATZ 277
#define T_KOSATZ 278
#define T_HEXINTEGER 279
#define T_KSATZ 280
#define T_HSATZ 281
#define T_OFFSET 282
#define T_SCALE 283
#define T_ENTRY 284
#define T_PBDNAME 285
#define T_ENTRYROSYS 286
#define T_ENTRYRO 287
#define T_ENTRYSYS 288
#define T_FLOAT 289

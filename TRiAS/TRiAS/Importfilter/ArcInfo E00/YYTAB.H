
typedef union  {
	struct {
		double real1;
		double real2;
		char *p_real_str;
	} real_struct;
	struct {
		long int1;
		long int2;
		long int3;
		char *str_ptr1;
	} int_struct;
	long integer;
	char *str_ptr;
	double real;                            
} YYSTYPE;
extern YYSTYPE yylval;
#define REAL 257
#define INT 258
#define TEXTVAL 259
#define USER_ID_FIELD 260
#define QSTRING 261
#define USER_FIELD_PARAMS 262
#define PAT_FILE_NAME 263
#define AAT_FILE_NAME 264
#define TIC_FILE_NAME 265
#define BND_FILE_NAME 266
#define OTHER_FILE_NAME 267
#define COVER_BEGIN 268
#define COVER_ENDE 269
#define IFO_BEGIN 270
#define IFO_ENDE 271
#define ARC 272
#define CNT 273
#define TXT 274
#define PAL 275
#define LAB 276
#define TOL 277
#define ID_FIELD 278
#define LENGTH 279
#define FIRST_NODE 280
#define LAST_NODE 281
#define LEFT_POLY 282
#define RIGHT_POLY 283
#define XMIN 284
#define YMIN 285
#define XMAX 286
#define YMAX 287
#define ID_TIC 288
#define XTIC 289
#define YTIC 290
#define AREA 291
#define PERIMETER 292
#define EOL 293
#define COMMAND 294
#define PATH 295
#define COMMAND_ENDE 296
#define SIN_BEGIN 297
#define SIN_ENDE 298
#define LOG_BEGIN 299
#define LOG_ENDE 300
#define TX_BEGIN 301
#define LX_ERROR 302

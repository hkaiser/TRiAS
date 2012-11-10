
typedef union  {
	struct {
		double real1;
		double real2;
		double real3;
	} real_struct; 
	short integer;
	char *str_ptr;
	double real;				
} YYSTYPE;
extern YYSTYPE yylval;
#define FLAG0 257
#define FLAG1 258
#define VERTEX_COUNT 259
#define KOORD 260
#define KOORD_X 261
#define KOORD_Y 262
#define KOORD_Z 263
#define FLOAT 264
#define FLOAT1 265
#define FLOAT2 266
#define FLOAT4 267
#define FLOAT5 268
#define WINKEL0 269
#define WINKEL1 270
#define TEXT0 271
#define LAYER_NAME 272
#define NAME 273
#define WINKEL 274
#define TEXT_HOEHE 275
#define ANFANG 276
#define SECTION 277
#define END_SECT 278
#define END_OF_FILE 279
#define ENTITIES 280
#define HEADER 281
#define BLOCKS 282
#define TABLES 283
#define VERSION 284
#define EXT_MIN 285
#define EXT_MAX 286
#define LAST_EDIT 287
#define LEX_ERROR 288
#define LINE 289
#define POLY_LINE 290
#define VERTEX 291
#define SEQEND 292
#define CIRCLE 293
#define ARC 294
#define TEXT_ELEM 295
#define POINT 296
#define INSERT 297
#define TRACE_ELEM 298
#define SOLID 299
#define SHAPE 300
#define ATTRIB 301
#define LIM_MIN 302
#define LIM_MAX 303
#define BLOCK 304
#define ENDBLK 305
#define LWPOLY_LINE 306

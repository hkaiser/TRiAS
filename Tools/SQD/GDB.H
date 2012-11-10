// globale Variablen ----------------------------------------------------------
extern int yylineno;

// Funktionsprototypen --------------------------------------------------------
void yyerror (const char *);
void yyunput (int);
void r_error (char *, int);
void r_abort (char *);
int yylex (void);
int yyparse (void);
int InitYYParse (void);

int ascii_open (int);

#define YYMAXDEPTH	150
#define PointerSize	40

#if defined(__cplusplus)
// Inlinefunktionen
extern double XMin, XMax, YMin, YMax;
inline void SetXCont (double X) { if (X < XMin) XMin = X; if (X > XMax) XMax = X; }
inline void SetYCont (double Y) { if (Y < YMin) YMin = Y; if (Y > YMax) YMax = Y; }
//	if (YMin < 0) {fprintf (stderr, "\nZeile %ld: YMin = %lf\n", yylineno, YMin); abort();} }
#endif


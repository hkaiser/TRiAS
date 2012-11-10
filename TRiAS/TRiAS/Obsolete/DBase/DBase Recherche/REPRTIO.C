/* Eingabe und Ausgaberoutinen fuer Reportgenerator             */
/* File: REPRTIO.C                                              */

#include "pheader.h"
// #include <windows.h>
#include <time.h>
#include <memory.h>

// #include "winio.h"
#include "dql.h"

/* Variablendefinitionen */
SYS_VAR system_var[] = {        /* Systemvariablen */
        {       "pagenum", 1    },      /* aktuelle Seitennummer */
        {       "linenum", 0    },      /* aktuelle Zeile auf Seite */
        {       "tuplenum", 0   },      /* aktuelle Datensatznummer */
        {       "colnum", 0     },      /* aktuelle Spaltennummer */
        {       NULL, 0 },
};

/* Systemkonstantenberechnungsfunktionen */
short Year (void), Month (void), Day (void), W_day (void);
short Y_day (void), Hour (void), Minute (void), Second (void);

SYS_CONST system_const[] = {  /* Systemkonstanten */
        {       "year", Year            },
        {       "month", Month          },
        {       "day", Day              },
        {       "m_day", Day            },
        {       "w_day", W_day          },
        {       "y_day", Y_day          },
        {       "hour", Hour            },
        {       "minute", Minute        },
        {       "second", Second        },
        {       NULL, NULL              }
};

VARIABLE var_table[MAXVARS];    /* Variablentabelle */

/* Variablen fuer Seiten- und Zeilenformatierung */
int Lines = 64;         /* Anzahl der Druckzeilen einer Seite */
int AllLines = 69;      /* physische Laenge einer Seite */
int Columns = MAXSTRING; /* Anzahl der Spalten einer Zeile */
int NewPage = 2;        /* naechste Seitennummer */

int StartRPage = 1;      /* erste auszugebende Seite */
int EndRPage = MAXPOS;   /* letzte auszugebende Seite */
int StartRTuple = 1;     /* erster auzugebender Datensatz */
int EndRTuple = MAXPOS;  /* letzter auszugebender Datensatz */

int allow_tuple = TRUE; /* Tuplenummer liegt in erlaubtem Bereich */
int was_allowed = TRUE; /* Tuplenummer war einmal im erlaubten Bereich */

int m1val = 3;  /* Zeilen bis einschliesslich Headerzeile */
int m2val = 2;  /* Freizeilen nach Headerzeile */
int m3val = 2;  /* Freizeilen nach letzter Textzeile */
int m4val = 3;  /* unteres Feld einschliesslich Fussnote */

char Header[MAXSTRING+1]; /* Headerzeile */
char Footer[MAXSTRING+1]; /* Fussnote */

char LineBegin[MAXSTRING];      /* Text am Zeilenbeginn */
char LineEnd[MAXSTRING];        /* Text am Zeilenende */
char OutLine[MAXSTRING+1];      /* eigentliche Informationszeile */

char *form_line;        /* Zeile, die gerade formatiert wird */

SUBROUTINE subroutines[MAXSUBR];        /* Unterprogramme */
SUBROUTINE head;                        /* Kopfzeile */
SUBROUTINE foot;                        /* Fusszeile */

/* ------------------------------------------------------------------------ */

/* Ausgabefunktionen */

static int pagefeed = FALSE;    /* Flag zeigt an, dass Zeichen auf Seite ist */

void out_string (char *cptr) {

        while (*cptr && ActCol <= MAXSTRING) {
                pagefeed = TRUE;
                form_line[ActCol++] = *cptr++;
        }
}

int new_page (void) {

        if (!pagefeed) return TRUE;          /* Seite ist noch leer */
        pagefeed = FALSE;
        if (ActLine <= 0) put_head ();
        if (skip (Lines-ActLine) == EOF) {       /* Seite voll machen */
                r_abort ("Schreibfehler auf Ausgabedatei");
		return FALSE;
	}
        ActLine = Lines;
        put_foot ();

return TRUE;
}

#undef min
#define min(x,y) (((x)>(y))?(y):(x))

static int p_flag = TRUE;       /* Druckerlaubnisflag */

int new_line (short num) {          /* num Zeilen weiterschalten */

/* Seite soll nicht gedruckt werden */
        if (!allow_tuple || ActPage < StartRPage || ActPage > EndRPage)
                p_flag = FALSE;
        else
                p_flag = TRUE;

/* Ausgabe der gesamten Zeile */
        if (p_flag && LineBegin != NULL) 
		puts (LineBegin);
        OutLine[Columns] = '\0';                /* Zeilenende markieren */
        if (p_flag) 
		puts (OutLine);       /* eigentliche Information */
        if (p_flag && LineEnd != NULL) 
		puts (LineEnd);

        if (p_flag) 
		putchar ('\n');  /* naechste Zeile */

        ActCol = 0;                     /* Zeile loeschen */
        memset (OutLine, ' ', MAXSTRING);

        if (skip (min (num -1, Lines-ActLine)) == EOF) {
                r_abort ("Schreibfehler auf Ausgabedatei");
		return FALSE;
	}
        ActLine += num;

return TRUE;
}

/* Ausgabe von Leerzeilen */
int skip (int num) {
/* Seite soll nicht gedruckt werden */
        if (!allow_tuple || ActPage < StartRPage || ActPage > EndRPage)
                p_flag = FALSE;
        else
                p_flag = TRUE;

        while (num-- > 0)
                if (p_flag && putchar ('\n') == EOF) 
			return (EOF);

return TRUE;
}

/* Kopfzeile ausgeben */
int put_head (void) {
/* Seite soll nicht gedruckt werden */
        if (!allow_tuple || ActPage < StartRPage || ActPage > EndRPage)
                p_flag = FALSE;
        else
                p_flag = TRUE;

        skip (m1val -1);        /* Seitenbeginn */
        if (p_flag && Header != NULL) {
                Header[Columns] = '\0';
                puts (Header);
                if (putchar ('\n') == EOF) {
                        r_abort ("Schreibfehler auf Ausgabedatei");
			return FALSE;
		}
        } else if (p_flag && putchar ('\n') == EOF) {
        	r_abort ("Schreibfehler auf Ausgabedatei");
		return FALSE;
	}

        skip (m2val);           /* Platz bis zum Text */
        ActLine = m1val + m2val +1;

return TRUE;
}

/* Fussnote ausgeben */
int put_foot (void) {
register int reset_allow = FALSE;

/* Seite soll nicht gedruckt werden */
        if (!allow_tuple || ActPage < StartRPage || ActPage > EndRPage)
                p_flag = FALSE;
        else
                p_flag = TRUE;
        if (was_allowed && !allow_tuple) {
        /* Tuples sind gedruckt, nun noch Seite zuende drucken */
                allow_tuple = TRUE;
                reset_allow = TRUE;
        }
        skip (m3val);           /* Platz nach Text */
        if (p_flag && Footer != NULL) {
                Footer[Columns] = '\0';
                puts (Footer);
                if (putchar ('\n') == EOF) {
                        r_abort ("Schreibfehler auf Ausgabedatei");
			return FALSE;
		}
        } else if (p_flag && putchar ('\n') == EOF) {
		r_abort ("Schreibfehler auf Ausgabedatei");
		return FALSE;
	}

        skip (m4val -1);        /* bis Seitenende */
        ActLine = 0;
        if (reset_allow) {
                was_allowed = FALSE;
                allow_tuple = FALSE;
        }
        if (p_flag) {
        /* Seitennummerierung weiterzaehlen */
                ActPage = NewPage;
                NewPage++;
        }

return TRUE;
}

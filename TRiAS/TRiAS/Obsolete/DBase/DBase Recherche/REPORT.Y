%{
/* Reportgenerator                                              */
/* File: REPORT.Y                                               */

static char SccsId[] = "uve FEZ: %W%  %E%";

#if defined(__cplusplus)
extern "C" {
#endif
	#include <stdio.h>
	#include <time.h>
	#include <string.h>
	#include <malloc.h>

	#include "report.h"
#if defined(__cplusplus)
}

#undef NULL
#define NULL 0

#endif

/* Monatsnamen */
static char *month[] = { "Jan", "Feb", "Mar", "Apr", "Mai", "Jun",
                         "Jul", "Aug", "Sep", "Okt", "Nov", "Dez" };

static VARIABLE *p;     /* Pointer auf aktuelle Eingabevariable */

long for_all_seek = 0;  /* Position von FOR_ALL */
int for_all_flag = FALSE;       /* Schleifenflag */
int for_all_line = 0;           /* Zeilennummer des Schleifenanfangs */

int ignoreflag = FALSE;         /* Flag fuer IF/ELSE */

int declaration = FALSE;        /* Deklarationssektion */

static int last_foot;
static int OutCols = 0;

%}

%union {
        STRING_TOKEN strtok;
        NUMBER_TOKEN numtok;
        REAL_TOKEN realtok;
}

%start report

%token <numtok> REPORT LINES COLUMNS ALL FROM TO BIG PAGE TUPLE
%token <numtok> FOR_ONE FOR_ALL HEAD TAIL FORMAT NUMBER TUPLES
%token <numtok> VARI VARF VARS LASTI VALUEI NEXTI LASTF VALUEF NEXTF
%token <numtok> LASTS VALUES NEXTS NEW LINE COL BATCH PROC CALL
%token <numtok> SYSTEM_VAR SYSTEM_CONST INT REAL PRINT DECLARATION
%token <numtok> LINEBEGIN LINEEND IF ELSE

%token <strtok> IDENT STRING TERMINAL DATE TIME SPACE

%token <realtok> REAL_NUMBER

%token <numtok> '{' '}' ';' '+' '-' '(' ')' '*' '/' '%'

%type <numtok>  control_spec control_stmt format int_num
%type <numtok>  assignment integer input_integer
%type <numtok>  closing_brace int_e proc_call proc_begin
%type <numtok>  head_spec tail_spec procedure_declaration
%type <numtok>  condition boolean_stmt

%type <strtok>  output_cmds output_cmd string formatted input_string
%type <realtok> e input_real 

%right EQU

%left OROR
%left ANDAND
%left UNOT
%left LT GT NE LE GE EQ

%left '+' '-'
%left '*' '/' '%'
%left UMINUS
%%

/* Reportdefinitionssprache */
report:         report_spec report_stmts closing_brace
        ;

/* Festlegen des Namens der Generierten Tabelle */
report_spec:    REPORT IDENT '{'
        |       REPORT IDENT error
                {
                        r_error ("Fragwuerdige Reportspezifikation", $2.strline);
                }
        ;

/* Anweisungen der Reportdefinitionssprache */
report_stmts:   report_stmt
        |       report_stmt report_stmts
        ;

closing_brace:  '}'
        |       error
                {
                        yyerrok;
                        r_error ("Fehlende schlieszende '}'", yylineno);
                }
        ;

report_stmt:    format_section
        |       tuple_section
        |       declaration_section
        |       tail_spec       /* nur fuer internen Gebrauch */
        ;

/* Prozedurdeklarationen */
declaration_section:    declaration_begin declarations closing_brace
                {       declaration = FALSE;    }
        ;

declaration_begin:      DECLARATION '{'
                {       declaration = TRUE;     }
        |       DECLARATION error
                {
                        yyerrok;
                        r_error ("Fragwuerdige Deklarationssektion", $<numtok>2.numline);
                }
        ;

declarations:   declaration
        |       declaration declarations
        ;

declaration:    head_spec
        |       tail_spec
        |       procedure_declaration
        ;

/* Prozedurdeklaration- bzw. Aufruf */
procedure_declaration:  proc_begin control_spec closing_brace
                {
                register SUBROUTINE *sr_p;

                        if (!declaration) {
                                yylineno = (sr_p = &subroutines[$2.value])->ret_line;
                                yyseek (sr_p->ret_seek);        /* Return */
                        }
                }
        ;

proc_begin:     PROC integer '{'
                {
                        if (declaration) {
                        register SUBROUTINE *sr_p;

                                if ($2.value < 0 || $2.value >= MAXSUBR) {
                                        r_error ("Nicht erlaubte Prozedurnummer", $2.numline);
                                        break;
                                }
                                sr_p = &subroutines[$2.value];
                                sr_p->seek = yytell (0);
                                sr_p->line = yylineno;
                                yyignore;
                        }
                        $$.value = $2.value;
                }
        |       PROC error
                {
                        yyerrok;
                        r_error ("Fragwuerdige Prozedurdeklaration", $<numtok>2.numline);
                }
        ;

/* Vorgeben des Seitenformates */
format_section: format_begin format_stmts closing_brace
        ;

format_begin:   FORMAT '{'
        |       FORMAT error closing_brace
        ;

format_stmts:   format_stmt
        |       format_stmt format_stmts
        ;

format_stmt:    LINES EQU int_num ';'
                {
                        Lines = $3.value;
                }
        |       ALL LINES EQU int_num ';'
                {
                        AllLines = $4.value;
                }
        |       COLUMNS EQU int_num ';'
                {
                register int cols = $3.value;

                        if (cols > MAXSTRING) Columns = MAXSTRING;
                        else Columns = cols;
                }
        |       FROM PAGE int_num ';'
                {
                        StartPage = $3.value;
                }
        |       TO PAGE int_num ';'
                {
                        EndPage = $3.value;
                }
        |       FROM TUPLE int_num ';'
                {
                        StartTuple = $3.value;
                }
        |       TO TUPLE int_num ';'
                {
                        EndTuple = $3.value;
                }
        |       LINEBEGIN '{'
                {
                        form_line = LineBegin;
                        memset (LineBegin, '\0', MAXSTRING);
                }
                                output_cmds closing_brace
                                {
                                        form_line = OutLine;
                                }
        |       LINEEND '{'
                {
                        form_line = LineEnd;
                        memset (LineEnd, '\0', MAXSTRING);
                }
                                output_cmds closing_brace
                                {
                                        form_line = OutLine;
                                }
        |       error ';'
                {
                        yyerrok;
                        r_error ("Fragwuerdige Formatangabe", $2.numline);
                }
        ;

/* Vorgeben des Seitenkopfes */
head_spec:      head_begin output_cmds closing_brace
                {
                        if (!declaration) {
                                if (!put_head ()) YYABORT;
                                form_line = OutLine;    /* normale Zeile */
                                ActCol = OutCols;
                                yylineno = head.ret_line;
                                yyseek (head.ret_seek);
                        }
                }
        ;

head_begin:     HEAD '{'
                {
                        if (declaration) {
                                head.seek = yytell (0);
                                head.line = yylineno;
                                yyignore;
                        } else {
                                form_line = Header;     /* Headerzeile formatieren */
                                OutCols = ActCol;
                                ActCol = 0;
                                memset (Header, ' ', MAXSTRING);
                        }
                }
        |       HEAD error
                {
                        Header[0] = '\0';       /* keine Kopfzeile */
                        form_line = OutLine;
                        yyerrok;
                        r_error ("Fragwuerdige Kopfzeilendeklaration", $<numtok>2.numline);
                }
        ;

/* Vorgeben des Seitenfussbereiches */
tail_spec:      tail_begin output_cmds closing_brace
                {
                        if (!declaration) {
                                if (!put_foot ()) YYABORT;
                                form_line = OutLine;    /* normale Zeile */
                                ActCol = OutCols;
                                yylineno = foot.ret_line;
                                yyseek (foot.ret_seek);
                        }
                }
        ;

tail_begin:     TAIL '{'
                {
                        if (declaration) {
                                foot.seek = yytell (0);
                                foot.line = yylineno;
                                yyignore;
                        } else {
                                form_line = Footer;
                                OutCols = ActCol;
                                ActCol = 0;
                                memset (Footer, ' ', MAXSTRING);
                        }
                }
        |       TAIL error
                {
                        Footer[0] = '\0';
                        form_line = OutLine;
                        yyerrok;
                        r_error ("Fragwuerdige Fussnotendeklaration", $<numtok>2.numline);
                }
        ;

tuple_section:  tuple_begin tuple_body closing_brace
                {
                        if (ActLine > 0) {
                                skip (Lines - ActLine);
                                call (&foot);
                                last_foot = TRUE;
                        }
                        else last_foot = FALSE;
                }
        ;

tuple_begin:    TUPLES '{'
                {
                        form_line = OutLine;            /* normale Zeile */
                        memset (OutLine, ' ', MAXSTRING);
                        if (ActLine <= 0 || ActLine > Lines) {
                        /* Ausgabe der Kopfzeile */
                                call (&head);
                        }
                }
        |       TUPLES error
                {
                        r_error ("Fragwuerdige Datenverarbeitungssektion", $1.numline);
                }
        ;

/* Festlegen der Verarbeitungsschritte fuer die Datensaetze */
tuple_body:     tuple_stmt
        |       tuple_stmt tuple_body
        ;

tuple_stmt:     forall forall_body closing_brace
                {
                        if (for_all_flag) {
                        /* zurueckpositionieren */
                                yyseek (for_all_seek);
                                yylineno = for_all_line;
                        }
                }
        |       control_stmt
        ;

/* Verarbeitung aller Datensaetze */
forall:         FOR_ALL '{'
                {
                        if (for_all_flag == FALSE) {
                        /* nur beim ersten mal */
                                for_all_seek = yytell(0);       /* aktuelle Pos. merken */
                                for_all_line = yylineno;
                                for_all_flag = TRUE;            /* Schleife aktivieren */
                                act_no = lexin (act_in);        /* Lesen erstes Tupel */
                                if (act_no) ActTuple++;
                                next_no = lexin (next_in);      /* lesen naechstes Tupel */
                                last_in = NULL; last_no = 0;
                                /* Feststellen, ob Tuplenummer im erlaubten Bereich */
                                if (ActTuple >= StartTuple && ActTuple <= EndTuple) 
                                        was_allowed =
                                        allow_tuple = TRUE;
                                else
                                        allow_tuple = FALSE;
                        }
                }
        |       FOR_ALL error
                {
                        r_error ("Fragwuerdige Tupelverarbeitung.", $1.numline);
                }
        ;

forall_body:    forone_spec
        |       forone_spec
                {
                        if (for_all_flag == FALSE) yyignore;
                }
                                control_spec
        |       control_spec forone_spec
        |       control_spec forone_spec
                {
                        if (for_all_flag == FALSE) yyignore;
                }
                                        control_spec
        ;

/* Verarbeitung eines Datensatzes */
forone_spec:    forone control_spec closing_brace
                {
                /* naechsten Datensatz einlesen */
                        last_in = act_in; last_no = act_no;
                        act_in = next_in; act_no = next_no;
                        next_no = lexin (next_in = input_tab[in_cnt]);
                        if (next_no == 0) {
                                next_in = NULL;
                                next_no = 0;
                        }
                        if (act_no == 0)
                        /* letzter Datensatz */
                                for_all_flag = FALSE;   /* Beenden */
                        else
                                ActTuple++;
                        if (++in_cnt >= 3) in_cnt = 0;
                        /* Feststellen, ob Tuplenummer im erlaubten Bereich */
                        if (ActTuple >= StartTuple && ActTuple <= EndTuple)
                                was_allowed =
                                allow_tuple = TRUE;
                        else
                                allow_tuple = FALSE;
                }
        ;

forone:         FOR_ONE '{'
        |       FOR_ONE error
                {
                        r_error ("Fragwuerdige Tupelverarbeitung.", $1.numline);
                }
        ;

/* allgemeine Steueranweisungen */
control_spec:   '{' control_spec closing_brace
        |       control_stmt
        |       control_stmt control_spec
        ;

control_stmt:   format
        |       assignment
        |       condition
        |       proc_call
        |       head_spec       /* nur fuer internen Gebrauch */
        |       tail_spec       /*           - " -            */
        |       procedure_declaration   /*   - " -            */
        ;

condition:      if_condition
                {       if (ignoreflag == TRUE) ignoreflag = FALSE;     }
        |       if_condition else_condition
                {       if (ignoreflag == TRUE) ignoreflag = FALSE;     }
        ;

if_condition:   if_begin control_spec closing_brace
        ;

else_condition: else_begin control_spec closing_brace
        ;

if_begin:       IF '(' boolean_stmt ')' '{'
                {
                        if (!$3.value) {
                                ignoreflag = TRUE;
                                yyignore;
                        }
                }
        ;

else_begin:     ELSE '{'
                {
                        if (ignoreflag == TRUE)
                                ignoreflag = FALSE;
                        else {
                                ignoreflag = TRUE;
                                yyignore;
                        }
                }
        ;

boolean_stmt:   '(' boolean_stmt ')'
                {       $$.value = $2.value;                    }
        |       boolean_stmt OROR boolean_stmt
                {       $$.value = ($1.value || $3.value);      }
        |       boolean_stmt ANDAND boolean_stmt
                {       $$.value = ($1.value && $3.value);      }
        |       UNOT boolean_stmt
                {       $$.value = !($2.value);                 }
        |       integer EQ integer
                {       $$.value = ($1.value == $3.value);      }
        |       integer NE integer
                {       $$.value = ($1.value != $3.value);      }
        |       integer LE integer
                {       $$.value = ($1.value <= $3.value);      }
        |       integer GE integer
                {       $$.value = ($1.value >= $3.value);      }
        |       integer GT integer
                {       $$.value = ($1.value > $3.value);       }
        |       integer LT integer
                {       $$.value = ($1.value < $3.value);       }
        |       e EQ e
                {       $$.value = ($1.value == $3.value);      }
        |       e NE e
                {       $$.value = ($1.value != $3.value);      }
        |       e LE e
                {       $$.value = ($1.value <= $3.value);      }
        |       e GE e
                {       $$.value = ($1.value >= $3.value);      }
        |       e GT e
                {       $$.value = ($1.value > $3.value);       }
        |       e LT e
                {       $$.value = ($1.value < $3.value);       }
        ;

/* Prozeduraufruf */
proc_call:      CALL PROC integer ';'
                {
                register SUBROUTINE *sr_p;

                        if ($2.value < 0 || $2.value >= MAXSUBR) {
                                r_error ("Nicht erlaubte Prozedurnummer", $2.numline);
                                break;
                        }
                        sr_p = &subroutines[$2.value];
                        if (call (sr_p)) {      /* Abarbeiten */
                                r_error ("Nicht deklarierte Prozedur", $2.numline);
                                break;
                        }
                        $$.value = $2.value;
                }
        ;

/* Zuweisungsoperator */
assignment:     VARF NUMBER EQU e ';'
                {
                register VARIABLE *var_p;

                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if ((var_p = &var_table[$2.value])->ptr == NULL) {
                                if ((var_p->ptr = calloc (1, sizeof(double))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'f') {
                                if ((var_p->ptr = realloc (var_p->ptr, sizeof(double))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        *(double *)(var_p->ptr) = $4.value;
                        var_p->type = 'f';
                }
        |       VARI NUMBER EQU int_e ';'
                {
                register VARIABLE *var_p;

                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if ((var_p = &var_table[$2.value])->ptr == NULL) {
                                if ((var_p->ptr = calloc (1, sizeof(int))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'i') {
                                if ((var_p->ptr = realloc (var_p->ptr, sizeof(int))) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        *(int *)(var_p->ptr) = $4.value;
                        var_p->type = 'i';
                }
        |       VARS NUMBER EQU string ';'
                {
                register VARIABLE *var_p;

                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if ((var_p = &var_table[$2.value])->ptr == NULL) {
                                if ((var_p->ptr = calloc (1, MAXSTRING+1)) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        } else if (var_p->type != 'i') {
                                if ((var_p->ptr = realloc (var_p->ptr, MAXSTRING+1)) == NULL) {
                                        r_abort ("Kein Speicherplatz.");
					YYABORT;
				}
                        }
                        strncpy (var_p->ptr, $4.str, MAXSTRING);
                        var_p->type = 's';
                }
        |       SYSTEM_VAR EQU e ';'
                {
                        system_var[$1.index].var_wert = (int)$3.value;
                }
        ;

/* Expression (reine Doublearithmetik) */
e:              '(' e ')'
                {       $$.value = $2.value;    }
        |       e '+' e
                {       $$.value = $1.value + $3.value; }
        |       e '-' e
                {       $$.value = $1.value - $3.value; }
        |       e '*' e
                {       $$.value = $1.value * $3.value; }
        |       e '/' e
                {       $$.value = $1.value / $3.value; }
        |       '-' e   %prec UMINUS
                {       $$.value = - $2.value;          }
        |       VARF NUMBER
                {
                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if (var_table[$2.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", $1.numline);
                                $$.value = 0;
                        } else if (var_table[$2.value].type != 'f')
                                r_error ("Variable ist kein Real.", $1.numline);
                        else
                                $$.value = *(double *)var_table[$2.value].ptr;
                }
        |       input_real
                {       $$.value = $1.value;    }
        |       '(' REAL ')' integer
                {       $$.value = (double)$4.value;    }
        |       REAL_NUMBER
        |       string
                {
                        r_error ("String in arithmetischem Ausdruck", $1.strline);
                }
        ;


/* Integer - Expression (reine Integerarithmetik) */
int_e:          '(' int_e ')'
                {       $$.value = $2.value;    }
        |       int_e '+' int_e
                {       $$.value = $1.value + $3.value; }
        |       int_e '-' int_e
                {       $$.value = $1.value - $3.value; }
        |       int_e '*' int_e
                {       $$.value = $1.value * $3.value; }
        |       int_e '/' int_e
                {       $$.value = $1.value / $3.value; }
        |       int_e '%' int_e
                {       $$.value = $1.value % $3.value; }
        |       '-' int_e   %prec UMINUS
                {       $$.value = - $2.value;          }
        |       integer
        |       string
                {
                        r_error ("String in arithmetischem Ausdruck", $1.strline);
                }
        ;


/* Anweisungen zur dynamischen Seitenformatierung */
format:         NEW PAGE ';'            /* neue Seite anfangen */
                {
                        if (!new_page ()) YYABORT;
                }
        |       NEW LINE int_num ';'    /* int_num Zeilen weiter */
                {
                /* Ausgabe der Kopf- und Fusszeile */
                        if (ActLine > Lines) {
                                call (&head);
                                call (&foot);
                        }
                        if (!new_line ((short)$3.value)) YYABORT;
                }
        |       string BATCH int_num ';'/* String int_num breit stapeln */
                {
                        r_error ("BATCH noch nicht verfuegbar", $2.numline);
                }
        |       output_cmd              /* Ausgabekommandos */
                {
                        out_string ($1.str);
                }
        ;

output_cmds:    output_cmd              /* ein Ausgabekommando */
                {
                        out_string ($1.str);
                }
        |       output_cmd
                /* jedes Ausgabekommando einzeln bearbeiten */
                {
                        out_string ($1.str);
                }
                                output_cmds
        ;

output_cmd:     string int_num ';'      /* String int_num mal ausgeben */
                {
                register int i = $2.value, len = 0;

                        $$.str[0] = '\0';
                        while (i-- > 0 && len < MAXSTRING) {
                                len = strlen ($$.str);
                                strncat ($$.str, $1.str, MAXSTRING-len);
                        }
                }
        |       COL EQU integer ';'         /* Spalte int_num */
                {
                register int cols = $3.value;

                        if (cols > Columns) cols = Columns;
                        ActCol = cols;
                        $$.str[0] = '\0';
                }
        |       PRINT formatted integer ';' /* Integer formatiert drucken */
                {
                        sprintf ($$.str, $2.str, $<numtok>3.value);
                }
        |       PRINT formatted e ';'   /* Real formatiert drucken */
                {
                        sprintf ($$.str, $2.str, $<realtok>3.value);
                }
        |       PRINT formatted string ';'   /* Zeichenkette drucken */
                {
                        sprintf ($$.str, $2.str, $<strtok>3.str);
                }
        |       DATE ';'                /* Datum: dd.mm.yy */
                {
                long clock;
                register struct tm *tm;

                        time (&clock);
                        tm = localtime (&clock);
                        sprintf ($$.str, "%02d-%3.3s-%02d", tm->tm_mday,
                                        month[tm->tm_mon], tm->tm_year);
                }
        |       TIME ';'                /* Zeit:  hh.mm.ss */
                {
                long clock;
                register struct tm *tm;

                        time (&clock);
                        tm = localtime (&clock);
                        sprintf ($$.str, "%2d.%02d.%02d", tm->tm_hour,
                                        tm->tm_min, tm->tm_sec);
                }
        |       SYSTEM_VAR ';'
                {
system_variable:
                        sprintf ($$.str, "%d", $1.value);
                }
        |       SYSTEM_CONST ';'
                {
                        goto system_variable;
                }
        |       ';'
                {
                        $$.str[0] = '\0';       /* NOP */
                }
        ;

/* Ausgabeformat */
formatted:      STRING                  /* Konstantes Format */
        |       VARS NUMBER              /* Variables Format */
                {
                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if (var_table[$2.value].type != 's')
                                r_error ("Variable ist kein String.", $1.numline);
                        else
                                strcpy ($$.str, var_table[$2.value].ptr);
                }
        ;


/* Eingabedaten */
input_integer:  LASTI integer    /* Element integer des vorherigen Satzes */
                {
                        p = last_in;
input_int:
                        if (p != NULL) {
                                $<numtok>$.value = *(int *)p[$2.value].ptr;
                                $<numtok>$.numline = 'i';
                        } else memset (&$$, '\0', sizeof($$));
                }
        |       VALUEI integer
                {
                        p = act_in;
                        goto input_int;
                }
        |       NEXTI integer
                {
                        p = next_in;
                        goto input_int;
                }
        ;

input_real:     LASTF integer    /* Element integer des vorherigen Satzes */
                {
                        p = last_in;
input_real:
			if (p != NULL) {
                                $<realtok>$.value = *(double *)p[$2.value].ptr;
                                $<realtok>$.numline = 'f';
                        } else memset (&$$, '\0', sizeof($$));
                }
        |       VALUEF integer
                {
                        p = act_in;
                        goto input_real;
                }
        |       NEXTF integer
                {
                        p = next_in;
                        goto input_real;
                }
        ;

input_string:   LASTS integer    /* Element integer des vorherigen Satzes */
                {
                        p = last_in;
input_string:
                        if (p != NULL) {
                                strcpy ($<strtok>$.str, p[$2.value].ptr);
                                $<strtok>$.strline = 's';
                        } else memset (&$$, '\0', sizeof($$));
                }
        |       VALUES integer
                {
                        p = act_in;
                        goto input_string;
                }
        |       NEXTS integer
                {
                        p = next_in;
                        goto input_string;
                }
        ;

/* (System-)Konstante oder (System-)Variable */
int_num:        /* nothing */
                {       $<numtok>$.value = 1;   }       /* Defaultwert 1 */
        |       integer
        ;

integer:        NUMBER
        |       VARI NUMBER
                {
                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if (var_table[$2.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", $1.numline);
                                $<numtok>$.value = 0;
                        } else if (var_table[$2.value].type != 'i')
                                r_error ("Variable ist kein Integer.", $1.numline);
                        else
                                $<numtok>$.value = *(int *)var_table[$2.value].ptr;
                }
        |       input_integer
                {
                        $<numtok>$.value = $1.value;
                }
        |       '(' INT ')' VARF NUMBER
                {
                        if ($5.value < 0 || $5.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $4.numline);
                                break;
                        }
                        if (var_table[$5.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", $4.numline);
                                $<numtok>$.value = 0;
                        } else if (var_table[$5.value].type != 'f')
                                r_error ("Variable ist kein Real.", $4.numline);
                        else
                                $<numtok>$.value = (int)(*(double *)var_table[$5.value].ptr);
                }
        |       '(' INT ')' input_real
                {
                        $<numtok>$.value = (int)$4.value;
                }
        |       SYSTEM_VAR
        |       SYSTEM_CONST
        ;

/* allgemeine Zeichenkette */
string:         STRING                  /* Stringkonstante */
        |       TERMINAL STRING         /* Eingabestring anfordern */
                {
                register FILE *tty;

                        if ((tty = fopen ("/dev/tty", "w+")) == NULL)
                                r_error ("kann Terminal nicht eroeffnen",
                                                                $1.strline);
                        fputs ($2.str, tty);
                        fputs ("> ", tty);
                        $$.str[0] = '\0';
                        fgets ($$.str, sizeof($$.str)-1, tty);
                }
        |       SPACE                   /* Leerzeichen */
                {
                        strcpy ($$.str, " ");
                }
        |       input_string
        |       VARS NUMBER
                {
                        if ($2.value < 0 || $2.value >= MAXVARS) {
                                r_error ("Nicht existierende Variable", $1.numline);
                                break;
                        }
                        if (var_table[$2.value].ptr == NULL) {
                                r_error ("Variable nicht definiert", $1.numline);
                                $<strtok>$.str[0] = '\0';
                        } else if (var_table[$2.value].type != 's')
                                r_error ("Variable ist kein String.", $1.numline);
                        else
                                strncpy ($<strtok>$.str, var_table[$2.value].ptr, MAXSTRING);
                }
        |       '(' STRING ')' NUMBER
                {
number_cnvrt:
                        sprintf ($$.str, "%d", $1.value);
                }
        |       '(' STRING ')' SYSTEM_VAR
                {
                        goto number_cnvrt;
                }
        |       '(' STRING ')' SYSTEM_CONST
                {
                        goto number_cnvrt;
                }
        ;

%%

/* Anspringen einer YACC-Unterprogramm-Aktion */
int call (register SUBROUTINE *subr) {

        if (subr->seek != 0L) {
                subr->ret_seek = yytell (-1);
                subr->ret_line = yylineno;
                yylineno = subr->line;
                yyseek (subr->seek);
                return (FALSE);
        }
        else return (TRUE);
}

void _FAR_ * _FAR_ _cdecl calloc (size_t num, size_t size) {
HANDLE hMem;

	hMem = GlobalAlloc (GHND, num*size);
	if (hMem == 0)
		return NULL;

return GlobalLock (hMem);
}

void _FAR_ _cdecl free (void _FAR_ *ptr) {

	GlobalFree ((HANDLE)GlobalHandle (HIWORD (ptr)));
}

void _FAR_ * _FAR_ _cdecl realloc (void _FAR_ *ptr, size_t newsize) {
HANDLE hMem = (HANDLE)GlobalHandle ((HIWORD)ptr);

	GlobalUnlock (hMem);
	GlobalFree (hMem);
	hMem = GlobalReAlloc (hMem, newsize, GHND);
	if (hMem == 0)
		return NULL;

return GlobalLock (hMem);
}

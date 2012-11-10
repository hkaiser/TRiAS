%{       

#include "pheader.h"

#include "yytab.h"      					// Yacc-Defines

#define NOOPTPARAM
#include "optparam.hxx"     				// Params -> LineNr

// Konstanten
const short FieldLenPos = 16;				// Position der Feldlänge in der akt. Zeile
const short FieldTypePos = 34;				// Position des Feldtyps in der akt. Zeile	
const short FieldLenSize = 4;           	// Array-Längen der o.g. Werte
const short FieldTypeSize = 3;			
const short FieldCountPos = 38;				// max. Feldanzahl
const short FieldCountLen = 4;				// max. Länge dieses Feldes
const short RecCountPos = 47;				// max. Anzahl Datensätze
const short Max = 127;
const double dBeginText = -1.0000000E-02;	// Text folgt

//  Variablen
char LexBuffer [128] = "";
long FirstPos, SecPos;
          			
//  externe Variablen
extern Params *pParams;
extern Bool TellArcs;           			// Arc-Positionen nicht speichern ?
extern int Error;                       	// Lex-Fehler-Flag
extern Bool bReadText;						// lese Text-Flag

//  Prototypen
char *ReadNextLine (char *, short MaxCh);   // nächste Zeile lesen
void ConvertName (char *pBuffer = LexBuffer); 	// Namen konvertieren
Bool ReadFileParams (void);					// Dateiparameter lesen
Bool ReadFieldParams (void);				// Feldparameter lesen
void yytell (void);
void IncCounter (long ObjNr = 0);
int yylex ();
void OutKonvMess (DGeoTyp);
%}
/* globale expression */
command         ([a-zA-Z]+)
drive           ([a-zA-Z]":")
dir             ([a-zA-Z0-9\/\-\_]+)
ext             (\.[a-zA-Z0-9]+)
path1           ({drive}?{dir}{ext})
path2           ({drive}?{dir})
filename        ([A-Za-z][A-Za-z0-9\-\_\+]*)
pat_filename    ({filename}".PAT")
aat_filename    ({filename}".AAT")
tic_filename    ({filename}".TIC")
bnd_filename    ({filename}".BND")
oth_filename    ({filename}"."[A-Z0-9]+)
field_name      ([A-Za-z0-9\+\_\-]*)
id_field        ({filename}"#")
uid_field       ({filename}"-ID")
sign            [+-]
dezimal         [0-9]
integer         ({sign}?{dezimal}+)
integer_textval ({integer}.)
real            ({integer}"."{dezimal}+)
realexp         ({real}"E"{integer})
textbegin		(\"|\')			
nl              \n

%start DATA
%start INFO
%start SIN
%start LOG

%%
[ \t]+                  ;
{nl}                    { IncCounter (); }

<DATA>^"ARC  "[2|3]$    { return ARC; }
<DATA>^"CNT  "[2|3]$    { return CNT; }
<DATA>^"LAB  "[2|3]$    { return LAB; }
<DATA>^"PAL  "[2|3]$    { return PAL; }
<DATA>^"TXT  "[2|3]$    { bReadText = True; 
						  OutKonvMess (DGT_Text);	
						  return TXT; }
<DATA>^"TOL  "[2|3]$    { return TOL; }

<DATA>^"        -1         0         0         0         0         0         0"$ { return EOL; }

<INFO>^"EOI"$           { BEGIN DATA; return IFO_ENDE; }
<INFO>^{pat_filename}   { return ReadFileParams () ? PAT_FILE_NAME : LX_ERROR; }
<INFO>^{aat_filename}   { return ReadFileParams () ? AAT_FILE_NAME : LX_ERROR; }
<INFO>^"AREA"           { return AREA; }
<INFO>^"PERIMETER"      { return PERIMETER; }
<INFO>^"FNODE#"         { return FIRST_NODE; }
<INFO>^"TNODE#"         { return LAST_NODE; }
<INFO>^"LPOLY#"         { return LEFT_POLY; }
<INFO>^"RPOLY#"         { return RIGHT_POLY; }
<INFO>^"LENGTH"         { return LENGTH; }
<INFO>^"XMIN"           { return XMIN; }
<INFO>^"YMIN"           { return YMIN; }
<INFO>^"XMAX"           { return XMAX; }
<INFO>^"YMAX"           { return YMAX; }
<INFO>^"XTIC"           { return XTIC; }
<INFO>^"YTIC"           { return YTIC; }
<INFO>^"IDTIC"          { return ID_TIC; }
<INFO>^{bnd_filename}   { return ReadFileParams () ? BND_FILE_NAME : LX_ERROR; }
<INFO>^{tic_filename}   { return ReadFileParams () ? TIC_FILE_NAME : LX_ERROR; }
<INFO>^{oth_filename}   { return ReadFileParams () ? OTHER_FILE_NAME : LX_ERROR; }
<INFO>^{id_field}       { return ID_FIELD; }
<INFO>^{uid_field}      { ConvertName (LexBuffer); 
						  yylval.str_ptr = LexBuffer;
						  return USER_ID_FIELD; }
<INFO>^{field_name}     { return ReadFieldParams () ? USER_FIELD_PARAMS : LX_ERROR; }

^"EXP  0"               { BEGIN DATA;
				          bReadText = False;
						  return COVER_BEGIN; }
^"EOS"$                 { return COVER_ENDE; }
^"IFO  "[2|3]$          { BEGIN INFO;
						  return IFO_BEGIN; }
<DATA>^"TX"[0-9]"  "[2|3]$  { bReadText = True; 
							  OutKonvMess (DGT_Text);	
							  return TX_BEGIN; }

<INFO>{integer_textval}$    { yylval.integer = atol (yytext);
						  	  return INT; }
						  	  
^{textbegin}            { register int scope_char = yytext[0];
                          register int inchar;
                          register char *cptr = LexBuffer;

						  while ((inchar = input()) != scope_char)
                          		*cptr++ = inchar;
                          *cptr = '\0';
							                    
						  yylval.str_ptr = LexBuffer;
						  return QSTRING;
						}						  							  

{integer}               { yylval.integer = atol (yytext);
						  	  return INT; }

{real} |
{realexp}               {   double dVal = atof (yytext);
							if (bReadText && dVal == dBeginText)
							{                                   
						  		ReadNextLine (LexBuffer, Max);	// bis Zeilenende
						  		if (Error)
									return LX_ERROR;   
									
								ReadNextLine (LexBuffer, Max);  // akt. Text lesen
						  		if (Error)
									return LX_ERROR;   									
						  		yylval.str_ptr = LexBuffer;
						  		return TEXTVAL; 								
							}
							else
							{
								yylval.real = atof (yytext);
						  	   	return REAL; 
						  	}
						}						  	

^"SIN  "[2|3]$       	{ BEGIN SIN; return SIN_BEGIN; }
<SIN>^"EOX"$            { return SIN_ENDE; }
^"LOG  "[2|3]$          { BEGIN LOG; return LOG_BEGIN; }
<LOG>^"EOL"$            { return LOG_ENDE; }
<LOG>{command}          { return COMMAND; }
<LOG>^"~"$              { return COMMAND_ENDE; }
<LOG>{path1}|{path2}    { return PATH; }
.                       { LexBuffer [0] = yytext [0];
						  ReadNextLine (LexBuffer + 1, Max - 1);
						  if (Error)
							return LX_ERROR;
						  yylval.str_ptr = LexBuffer;
						  return TEXTVAL; 
						}
%%

//  aktuelle Dateiposition speichern
void yytell (void) 
{
    if (TellArcs == True) 
    {
		SecPos = FirstPos;
		FirstPos = ftell (yyin);
    }
}

// int yywrap (void) {
//    fclose (yyin);
//    return OpenInput (ActFileName, ++FileCnt);  // nächste e00-Datei öffnen
//    return 1;       // immer beenden
// }

// in internen Puffer lesen
char *ReadNextLine (char *Buffer, short MaxCnt) 
{
    short i = 0;
    short ch = '\0';

    while (!Error && i < MaxCnt) 
    {
		ch = (short) input ();
		if (ch != '\n') 
		{
			Buffer [i] = (char) ch;
			i++;
		} 
		else
	    	break;
    }
    Buffer [i] = '\0';  /* Textende setzen */

/*  wenn Puffer zu klein, lese bis zum nä.'\n' */
    if (ch != '\n') 
    {
		DEX_Error (RC_ArcTriasLex, EC_SYSERROR);
		while (!Error && input () != '\n');
    }
    pParams -> LineNr++;

    return Buffer;
}

//  Namen konvertieren: "-" durch "_" ersetzen
void ConvertName (char *pBuffer) 
{
    memcpy (pBuffer, yytext, min (strlen (yytext) + 1, Max));
    char *pB = pBuffer;
    while (*pB && *pB != ' ')
    {
    	if (*pB == '-')
    		*pB = '_';
		pB++;
	}		
    *pB = '\0';
}
                     
// 	Feldnamen, Typ u.a. Parameter lesen
Bool ReadFieldParams (void)
{
	ConvertName (LexBuffer);					// Feldnamen konvertieren
	yylval.int_struct.str_ptr1 = LexBuffer;
   	short NameLen = strlen (LexBuffer);
   	
//	Rest der akt. Zeile lesen   	
	char Line [Max] = "";
   	ReadNextLine (Line, Max - 1);
	if (Error)
		return False;
		
//	Info-Flag lesen
	char *pB = Line + strlen (Line) - 1;			
	while (pB != Line && *pB != ' ')
		pB--;
	
//	Fehlertest		
	if (pB == Line)
	{               
		DEX_Error (RC_ArcTriasLex, EC_SYNTAX);
		return False;
	}		         
	yylval.int_struct.int3 = atol (pB);	
								
//	FeldTyp und Länge lesen   	
	if (strlen (Line) <= (FieldTypePos + FieldTypeSize + 1 - NameLen))
	{                
		DEX_Error (RC_ArcTriasLex, EC_SYNTAX);
		return False;
	}
	                    
//	setze Endekennungen
	Line [FieldLenPos + FieldLenSize - NameLen] = '\0';
	Line [FieldTypePos + FieldTypeSize - NameLen] = '\0';		                    
	yylval.int_struct.int1 = atol (&Line [FieldLenPos - NameLen]);
	yylval.int_struct.int2 = atol (&Line [FieldTypePos - NameLen]);	   	
							
	return True;							
}

//	Dateiparameter lesen          
Bool ReadFileParams (void)
{
	ConvertName (LexBuffer);				// Filenamen konvertieren
	yylval.int_struct.str_ptr1 = LexBuffer;
   	short NameLen = strlen (LexBuffer);
   	
//	Rest der akt. Zeile lesen   	
	char Line [Max] = "";
   	ReadNextLine (Line, Max - 1);
	if (Error)
		return False;
		
//	Anzahl Felder und Anzahl Datensätze lesen   	
	if (strlen (Line) <= (RecCountPos + 2 - NameLen))
	{                
		DEX_Error (RC_ArcTriasLex, EC_SYNTAX);
		return False;
	}
	                    
//	setze Endekennungen
	Line [FieldCountPos + FieldCountLen - NameLen] = '\0';
	yylval.int_struct.int2 = atol (&Line [FieldCountPos - NameLen]);
	yylval.int_struct.int1 = atol (&Line [RecCountPos - NameLen]);	   	
	
	return True;
}

// Lex init
void yyinit_lex (void)
{
	yy_init = 1;
}


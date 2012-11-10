/* $Header: $
 * Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
 * Created: 08.09.99 10:58:11
 *
 * @doc
 * @module sql.l | TRiASQL Lexer definition
 */

%{

#include <stdio.h>
#include <string.h>
#include <io.h>
#include <iostream.h>
#include "yyacc.h"
#include "ParseTree.h"
int yyleng;
CString m_strGlobalError;

#define    YYBUFF_SIZE	  4096
YY_BUFFER_STATE yybuff;

#define YY_SKIP_YYWRAP
#define yywrap() (1)

#define YY_NEVER_INTERACTIVE
						
extern char *input_string;

#define YY_NO_UNPUT
#undef YY_INPUT
#define YY_INPUT(buf,result,maxsize) \
		   result = strlen(input_string); \
		   if (result > maxsize) result = maxsize; \
		   strncpy(buf, input_string, maxsize); \
		   input_string += result;

%}

__dot			[.]
__identifier	([a-zA-Z_][a-zA-Z0-9_]*)
__number_value	([0-9]+)
__float_value	([0-9]*\.[0-9]+)
__string_value	(\'(([^\'])|(\\.))*\')
_create 		[cC][rR][eE][aA][tT][eE]
_select 		[sS][eE][lL][eE][cC][tT]
_from			[fF][rR][oO][mM]
_and			[aA][nN][dD]
_or 			[oO][rR]
_max			[mM][aA][xX]
_min			[mM][iI][nN]
_avg			[aA][vV][gG]
_count			[cC][oO][uU][nN][tT]
_sum			[sS][uU][mM]
_where			[wW][hH][eE][rR][eE]
_order			[oO][rR][dD][eE][rR]
_group			[gG][rR][oO][uU][pP]
_by 			[bB][yY]
_asc			[aA][sS][cC]
_desc			[dD][eE][sS][cC]
_table			[tT][aA][bB][lL][eE]
__smallint		[sS][mM][aA][lL][lL][iI][nN][tT]
__integer		[iI][nN][tT][eE][gG][eE][rR]
__char			[cC][hH][aA][rR]
__float 		[fF][lL][oO][aA][tT]
__delete		[dD][eE][lL][eE][tT][eE]
__update		[uU][pP][dD][aA][tT][eE]
__set			[sS][eE][tT]
__insert		[iI][nN][sS][eE][rR][tT]
__into			[iI][nN][tT][oO]
__values		[vV][aA][lL][uU][eE][sS]
__is			[iI][sS]
__not			[nN][oO][tT]
__null			[nN][uU][lL][lL]
__as			[aA][sS]
__all			[aA][lL][lL]
__distinct		[dD][iI][sS][tT][iI][nN][cC][tT]
__having		[hH][aA][vV][iI][nN][gG]
__abs			[aA][bB][sS]
__round 		[rR][oO][uU][nN][dD]
__getdate		[gG][eE][tT][dD][aA][tT][eE]
__like			[lL][iI][kK][eE]
__drop			[dD][rR][oO][pP]

%%
		 
{__like}			return LIKE;
{__drop}			return DROP;
{__getdate} 		return GETDATE;
{__round}			return ROUND;
{__abs} 			return ABS;
{__having}			return HAVING;
{__null}			return SQL_NULL;
{__all} 			return ALL;
{__distinct}		return DISTINCT;
{__as}				return AS;
{__not} 			return NOT; 
{__is}				return IS; 
{_and}				return AND; 
{__values}			return VALUES; 
{__delete}			return SQL_DELETE; 
{__update}			return UPDATE; 
{__insert}			return INSERT; 
{__into}			return INTO; 
{__set} 			return SET; 
{_where}			return WHERE; 
{_order}			return ORDER; 
{_group}			return GROUP; 
{_by}				return BY; 
{_asc}				return ASC; 
{_desc} 			return DESC;	 
{_or}				return OR; 
{__dot} 			return DOT; 
{_select}			return SELECT ;
{_create}			return CREATE ;
{_from} 			return FROM ; 
{_max}				return MAX ; 
{_min}				return MIN ; 
{_avg}				return AVG ; 
{_count}			return COUNT ; 
{_sum}				return SUM ; 
{_table}			return TABLE ; 
{__smallint}		return SMALLINT_DATATYPE;
{__integer} 		return INTEGER_DATATYPE;
{__char}			return CHAR_DATATYPE;
{__float}			return FLOAT_DATATYPE;
{__number_value}	{ m_pTree->AddToken( NUMBER_VALUE, YYText()); return NUMBER_VALUE; };
{__float_value} 	{ m_pTree->AddToken( FLOAT_VALUE, YYText()); return FLOAT_VALUE; };
{__string_value}	{ m_pTree->AddToken( STRING_VALUE, YYText()); return STRING_VALUE; };
"(" 				return LEFTPAREN;
")" 				return RIGHTPAREN;
"*" 				return STAR;
"+" 				return PLUS; 
"-" 				return MINUS;
"/" 				return DIVIDE;
,					return COMMA; 
"=" 				return EQUALS;
"<>"				return NOT_EQUALS;
">" 				return MORE;
"<" 				return LESS;
">="				return MORE_EQUALS;
"<="				return LESS_EQUALS;
[ ] 				{}
\t					{}
\n					{}
{__identifier}		{ m_pTree->AddToken(IDENTIFIER, YYText());	   return IDENTIFIER; }

%%

void __cdecl yyerror( char *s)
{
	m_strGlobalError = s;
	printf( "%s\n",s );
}


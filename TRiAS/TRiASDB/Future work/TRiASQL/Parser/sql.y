// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.09.99 10:57:29
//
// @doc
// @module sql.y | TRiASQL Parser definition

%{			   

#include <stdio.h>
#include "stdafx.h"
#include "flexlexer.h"
#include "ParseTree.h"
#include <malloc.h>

#define YYSTYPE CSQLNode *

extern "C++" int  yylex(void);

#define YYERROR_VERBOSE
#define YYDEBUG 1

%}

%pure_parser

%token IDENTIFIER
%token LEFTPAREN RIGHTPAREN COMMA 
%token STRING_VALUE FLOAT_VALUE NUMBER_VALUE DATE_VALUE
%token SQL_NULL
%token FROM AS 
%token WHERE EQUALS DOT 
%token LESS MORE LESS_EQUALS MORE_EQUALS IS
%token NOT_EQUALS
%token SELECT STAR COUNT DISTINCT AVG MAX MIN SUM
%token ORDER BY ASC DESC ALL DISTINCT GROUP HAVING
%token SQL_DELETE UPDATE SET INSERT INTO VALUES
%token DROP CREATE TABLE CHAR_DATATYPE SMALLINT_DATATYPE INTEGER_DATATYPE FLOAT_DATATYPE SMALLINT_DATATYPE
%left ABS ROUND GETDATE
%left MINUS PLUS LIKE
%left STAR DIVIDE
%left AND OR
%left EQUALS 
%left NOT 

%%

Command:  SQL_Statement
	{
		$$ = $1;
		pState->SetFirst (	$$);
	}
	| DDL_Statement
	{
		$$ = $1;
		pState->SetFirst (	$$);
	}
	;

SQL_Statement:	SELECT AllDistinct SelectElementList FROM IdentList 
			WhereClause GroupByClause HavingClause OrderClause
	{
		$$ = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject ($2, "Distinct");
		pState->AddNameForObject ($3, "SelectClause");
		pState->AddNameForObject ($5, "FromClause");
		pState->AddNameForObject ($6, "WhereClause");
		pState->AddNameForObject ($7, "GroupByClause");
		pState->AddNameForObject ($8, "HavingClause");
		pState->AddNameForObject ($9, "OrderClause");
	} 
	| SELECT AllDistinct STAR FROM IdentList WhereClause GroupByClause HavingClause OrderClause
	{
		$$ = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject ($2, "Distinct");
		$3 = pState->MakeNode (NodeType_Star, "*");
		pState->AddNameForObject ($3, "SelectClause");
		pState->AddNameForObject ($5, "FromClause");
		pState->AddNameForObject ($6, "WhereClause");
		pState->AddNameForObject ($7, "GroupByClause");
		pState->AddNameForObject ($8, "HavingClause");
		pState->AddNameForObject ($9, "OrderClause");
	} 
	| SQL_DELETE FROM Identifier WhereClause
	{
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($4, "WhereClause");
		$$ = pState->MakeNode (NodeType_Delete, "Delete");
	} 
	| UPDATE Identifier SET UpdateList WhereClause
	{
		pState->AddNameForObject ($2, "NameIdent");
		pState->AddNameForObject ($4, "UpdateList");
		pState->AddNameForObject ($5, "WhereClause");
		$$ = pState->MakeNode (NodeType_Update, "Update");
	} 
	| INSERT INTO Identifier InsertColSpec VALUES LEFTPAREN InsertValueList RIGHTPAREN
	{
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($4, "InsertColSpec");
		pState->AddNameForObject ($7, "InsertValueList");
		$$ = pState->MakeNode (NodeType_Insert, "Insert");
	} 
	;

DDL_Statement: CREATE TABLE Identifier LEFTPAREN ColDataTypeList RIGHTPAREN
	{
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($5, "ColDataTypeList");
		$$ = pState->MakeNode (NodeType_CreateTable, "create table");
	}
	| DROP TABLE Identifier 
	{
		pState->AddNameForObject ($3, "NameIdent");
		$$ = pState->MakeNode (NodeType_DropTable, "drop table");
	}
	;
 
AllDistinct:
	{
		$$ = NULL;
	}
	| ALL
	{
		$$ = NULL;
	}
	| DISTINCT
	{
		$$ = pState->MakeNode (NodeType_Distinct, "Distinct");
	}
	;

SelectElementList: SelectExpressionAsName
	{
		$$ = $1;
	}
	| SelectElementList COMMA SelectExpressionAsName
	{
		$1->AddLast ($3);
		$$ = $1;
	}
	;	

SelectExpressionAsName: SelectExpression
	{
		$$ = $1;
	}
	| SelectExpression AS Identifier
	{
		$$ = pState->MakeNode (NodeType_AsName, "As name");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	;

InsertColSpec:	LEFTPAREN ColList RIGHTPAREN
	{
		$$ = $2;
	} 
	| 
	{
		$$ =NULL;
	}
	;

ColList: ColName
	{
		$$ = $1;
	}
	| ColList COMMA ColName
	{
					$1->AddLast ($3);
					$$ = $1;
	}
	;	



InsertValueList:  ConstantExpression
	{ 
		$$=$1;
	}
	| InsertValueList COMMA ConstantExpression
	{
		$1->AddLast ($3);
		$$ = $1;
	}
	;



WhereClause: /* Empty */
	{
		//$$ = pState->MakeNode(NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| WHERE WhereConditions
	{
		//$$ = pState->MakeNode (NodeType_WhereCondition, "Where");
		//$$->m_pLeftChild = $2;
		$$ = $2;
	}
	;

ConstantExpression: Value
	{
		$$ = $1;
	}
	| ConstantExpression PLUS ConstantExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression MINUS ConstantExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression DIVIDE ConstantExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression STAR ConstantExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN ConstantExpression RIGHTPAREN
	{
		$$ = $2;
	}
	;

UpdateList: UpdateValue
	{
		$$ = $1;		
	}
		| UpdateList COMMA UpdateValue
	{
		$1->AddLast ($3);
		$$ = $1;
	}
	;

UpdateValue: ColName EQUALS ValueOrColNameExpression
	{
		$$ = pState->MakeNode(NodeType_UpdateValue, "UpdateValue");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	;

WhereConditions:		WherePredicate
	{
		$$ = $1;		
	}
	| WhereConditions OR WhereConditions
	{
		$$ = pState->MakeNode (NodeType_Or, "Or");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| WhereConditions AND WhereConditions
	{
		$$ = pState->MakeNode (NodeType_And, "And");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	|	NOT WhereConditions 
	{
		$$ = pState->MakeNode (NodeType_Not, "Not");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = NULL;
	}
	|	LEFTPAREN WhereConditions RIGHTPAREN
	{
		$$ = $2;
	}
	;

WherePredicate: ValueOrColNameExpression EQUALS ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_Equals, "Equals");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression NOT_EQUALS ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_NotEquals, "NotEquals");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression LESS ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_Less, "Less");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MORE ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_More, "More");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression LESS_EQUALS ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_LessEquals, "LESS_EQUALS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MORE_EQUALS ValueOrColNameExpression
	{
		$$ = pState->MakeNode (NodeType_MoreEquals, "MORE_EQUALS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	|	ColName IS NOT SQL_NULL
	{
		$$ = pState->MakeNode (NodeType_IsNot, " IS NOT");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	}
	|	ColName IS SQL_NULL
	{
		$$ = pState->MakeNode (NodeType_Is, " IS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	}
	|	ColName LIKE String
	{
		$$ = pState->MakeNode (NodeType_Like, "LIKE");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	;

ColName: Identifier DOT Identifier
	{ 
		$$ = pState->MakeNode(NodeType_Dot, "dot");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| Identifier							   
	{ 
		$$ = pState->MakeNode(NodeType_Dot, "dot");
		$$->m_pLeftChild = NULL;
		$$->m_pRightChild = $1;
	}
	;
 
IdentList: Identifier
	{
		$$ = pState->MakeNode(NodeType_Identifier, "id");
	}
	| IdentList COMMA Identifier
	{
		$1->AddLast ($3);
		$$ = $1;
	}
	;

Identifier: IDENTIFIER
	{ 
		$$ = pState->MakeNode(NodeType_Identifier, "id");
	}
	;

SelectExpression: SelectExpressionItem
	{
		$$ = $1;
	}
	| SelectExpression PLUS SelectExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression MINUS SelectExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression DIVIDE SelectExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression STAR SelectExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN SelectExpression RIGHTPAREN
	{
		$$ = $2;
	}
	;

SelectExpressionItem: ValueOrColName
	{
		$$ = $1;
	}
	| Aggregate
	{
		$$ = $1;
	}
	| Function
	{
		$$ = $1;
	}
	;

ValueOrColName: Value
	{
		$$ = $1;
	}			 
	| ColName
	{
		$$ = $1;
	}
	;

ValueOrColNameExpression: ValueOrColName
	{
		$$ = $1;
	}
	| Function
	{
		$$ = $1;
	}
	| ValueOrColNameExpression PLUS ValueOrColNameExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MINUS ValueOrColNameExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression DIVIDE ValueOrColNameExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression STAR ValueOrColNameExpression
	{
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = $2;
	};

/* Group by */
GroupByClause:
	{
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| GROUP BY ColName
	{
	
		$$ = $3;
	}
	;

HavingClause: /* Empty */
	{
		$$ = NULL;
	}
	| HAVING WhereConditions
	{
		$$ = $2;
	}
	; 

OrderClause:
	{
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| ORDER BY OrderColList
	{
		$$ = $3;
	}
	;

OrderColList: OrderCol
	{
		$$ = $1;
	}
	| OrderColList COMMA OrderCol
	{
		$1->AddLast ($3);
		$$ = $1;
	}
	;

OrderCol: ColName
	{
		$$ = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		$$->m_pLeftChild = $1;
	}
	| ColName ASC
	{
		$$ = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		$$->m_pLeftChild = $1;
	}
	| ColName DESC
	{
		$$ = pState->MakeNode (NodeType_OrderDESC, "OrderDESC");
		$$->m_pLeftChild = $1;
	}
	;

Value: LiteralValue
	{
		 $$=$1;
	}
	;

//ValueOrNull: Value
//	{ 
//		$$=$1;
//	}
//	| SQL_NULL
//	{ 
//		$$ = pState->MakeNode(NodeType_Null, "NULL");
//	}
//	;

Function: MathFunction
	{
		$$=$1;
	}
	| DateFunction
	{
		$$=$1;
	}
	;

MathFunction: ABS LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		$$->m_pLeftChild = $3;	
	}
	|	ROUND LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		$$->m_pLeftChild = $3;	
	}
	;

DateFunction:	GETDATE LEFTPAREN RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_FunctionGetDate, "GETDATE");
	}
	;

Aggregate:		  SUM LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateSum, "SUM");
		$$->m_pLeftChild = $3;
	}
	| AVG	LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateAvg, "AVG SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| MAX	LEFTPAREN ValueOrColNameExpression	RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateMax, "MAX SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| MIN	LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateMin, "MIN SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| COUNT   LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateCount, "COUNT COLNAME");
		$$->m_pLeftChild = $3;
	}
	| COUNT   LEFTPAREN STAR  RIGHTPAREN
	{
		$$ = pState->MakeNode (NodeType_AggregateCount, "COUNT *");
		$$->m_pLeftChild = pState->MakeNode (NodeType_Star, "*");;
	}
	;



ColDataTypeList: Identifier DataType
	{
		$1->m_pLeftChild = $2;
		$$=$1;
	}
	|	ColDataTypeList COMMA Identifier DataType
	{
		$3->m_pLeftChild = $4;
		$1->AddLast ($3);
		$$ = $1;
	}
	;

DataType: CHAR_DATATYPE LEFTPAREN Number RIGHTPAREN 		
	{
		$$ = pState->MakeNode(NodeType_CharDataType, "character_typ");
		$$->m_pLeftChild = $3;
	}
	| INTEGER_DATATYPE
	{
		$$ = pState->MakeNode(NodeType_IntegerDataType, "interger_typ");
	}
	| FLOAT_DATATYPE			   
	{
		$$ = pState->MakeNode(NodeType_FloatDataType, "float_typ");
	}
	| SMALLINT_DATATYPE
	{
		$$ = pState->MakeNode (NodeType_SmallIntDataType, "smallint_type");
	}
	;

LiteralValue:	Number { $$ = $1; }
	| Float { $$ = $1; }
	| String { $$ = $1; }
	;

Number: 	NUMBER_VALUE
	{
		$$ = pState->MakeNode(NodeType_Integer_Value, "Number");
	}
	;

Float:		FLOAT_VALUE
	{
		$$ = pState->MakeNode(NodeType_Float_Value, "Float");
	}
	;
String: 	STRING_VALUE
	{
		$$ = pState->MakeNode(NodeType_String_Value, "String");
	}
	;

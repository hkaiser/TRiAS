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
%token DROP CREATE TABLE 
%token CHAR_DATATYPE SMALLINT_DATATYPE INTEGER_DATATYPE FLOAT_DATATYPE TEXT_DATATYPE
%token TOP PERCENT

%token ASTEXT ASBINARY DIMENSION GEOMETRYTYPE SRID ISEMPTY

%left ABS ROUND GETDATE
%left MINUS PLUS LIKE
%left STAR DIVIDE
%left AND OR
%left EQUALS 
%left NOT 

%%

Command:  SQL_Statement
	{
	// Command:  SQL_Statement
		$$ = $1;
		pState->SetFirst (	$$);
	}
	| DDL_Statement
	{
	// Command:  DDL_Statement
		$$ = $1;
		pState->SetFirst (	$$);
	}
	;

SQL_Statement:	SELECT AllDistinct TopRows SelectElementList FROM IdentList 
			WhereClause GroupByClause HavingClause OrderClause
	{
	//	SQL_Statement:	SELECT AllDistinct TopRows SelectElementList FROM IdentList 
	//				WhereClause GroupByClause HavingClause OrderClause
		$$ = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject ($2, "Distinct");
		pState->AddNameForObject ($3, "TopRows");
		pState->AddNameForObject ($4, "SelectClause");
		pState->AddNameForObject ($6, "FromClause");
		pState->AddNameForObject ($7, "WhereClause");
		pState->AddNameForObject ($8, "GroupByClause");
		pState->AddNameForObject ($9, "HavingClause");
		pState->AddNameForObject ($10, "OrderClause");
	} 
	| SELECT AllDistinct TopRows STAR FROM IdentList WhereClause GroupByClause HavingClause OrderClause
	{
	//	SQL_Statement:	SELECT AllDistinct TopRows STAR FROM IdentList WhereClause 
	//				GroupByClause HavingClause OrderClause
		$$ = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject ($2, "Distinct");
		pState->AddNameForObject ($3, "TopRows");
		$4 = pState->MakeNode (NodeType_Star, "*");
		pState->AddNameForObject ($4, "SelectClause");
		pState->AddNameForObject ($6, "FromClause");
		pState->AddNameForObject ($7, "WhereClause");
		pState->AddNameForObject ($8, "GroupByClause");
		pState->AddNameForObject ($9, "HavingClause");
		pState->AddNameForObject ($10, "OrderClause");
	} 
	| SQL_DELETE FROM Identifier WhereClause
	{
	//	SQL_Statement:	SQL_DELETE FROM Identifier WhereClause
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($4, "WhereClause");
		$$ = pState->MakeNode (NodeType_Delete, "Delete");
	} 
	| UPDATE Identifier SET UpdateList WhereClause
	{
	//	SQL_Statement:	UPDATE Identifier SET UpdateList WhereClause
		pState->AddNameForObject ($2, "NameIdent");
		pState->AddNameForObject ($4, "UpdateList");
		pState->AddNameForObject ($5, "WhereClause");
		$$ = pState->MakeNode (NodeType_Update, "Update");
	} 
	| INSERT INTO Identifier InsertColSpec VALUES LEFTPAREN InsertValueList RIGHTPAREN
	{
	//	SQL_Statement:	INSERT INTO Identifier InsertColSpec VALUES LEFTPAREN InsertValueList RIGHTPAREN
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($4, "InsertColSpec");
		pState->AddNameForObject ($7, "InsertValueList");
		$$ = pState->MakeNode (NodeType_Insert, "Insert");
	} 
	| Identifier
	{
	//	SQL_Statement:	Identifier
	// ein einfacher Tabellenname ist äquivalent zu 'select * from tabelle'
		$$ = pState->MakeNode (NodeType_Select, "Select");
		pState->AddNameForObject (pState->MakeNode (NodeType_Star, "*"), "SelectClause");
		pState->AddNameForObject ($1, "FromClause");
	}
	;

DDL_Statement: CREATE TABLE Identifier LEFTPAREN ColDataTypeList RIGHTPAREN
	{
	//	DDL_Statement: CREATE TABLE Identifier LEFTPAREN ColDataTypeList RIGHTPAREN
		pState->AddNameForObject ($3, "NameIdent");
		pState->AddNameForObject ($5, "ColDataTypeList");
		$$ = pState->MakeNode (NodeType_CreateTable, "create table");
	}
	| DROP TABLE Identifier 
	{
	//	DDL_Statement: DROP TABLE Identifier
		pState->AddNameForObject ($3, "NameIdent");
		$$ = pState->MakeNode (NodeType_DropTable, "drop table");
	}
	;
 
AllDistinct:
	{
	//	AllDistinct:
		$$ = NULL;
	}
	| ALL
	{
	//  AllDistinct:	ALL
		$$ = NULL;
	}
	| DISTINCT
	{
	//	AllDistinct:	DISTINCT
		$$ = pState->MakeNode (NodeType_Distinct, "Distinct");
	}
	;

TopRows:
	{
	// TopRows:
		$$ = NULL;
	}
	| TOP Number
	{
	// TopRows: TOP Number
		$$ = pState->MakeNode (NodeType_TopRows, "TopRows");
		$$->m_pLeftChild = $2;
	}
	| TOP Number PERCENT
	{
	// TopRows: TOP Number PERCENT
		$$ = pState->MakeNode (NodeType_TopRowsPercent, "TopRows");
		$$->m_pLeftChild = $2;
	}
	;

SelectElementList: SelectExpressionAsName
	{
	//	SelectElementList: SelectExpressionAsName
		$$ = $1;
	}
	| SelectElementList COMMA SelectExpressionAsName
	{
	//	SelectElementList: SelectElementList COMMA SelectExpressionAsName
		$1->AddLast ($3);
		$$ = $1;
	}
	;	

SelectExpressionAsName: SelectExpression
	{
	//	SelectExpressionAsName: SelectExpression
		$$ = $1;
	}
	| SelectExpression AS Identifier
	{
	//	SelectExpressionAsName: SelectExpression AS Identifier
		$$ = pState->MakeNode (NodeType_AsName, "As name");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression Identifier
	{
	//	SelectExpressionAsName: SelectExpression Identifier
		$$ = pState->MakeNode (NodeType_AsName, "As name");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $2;
	}
	;

InsertColSpec:	LEFTPAREN ColList RIGHTPAREN
	{
	//	InsertColSpec:	LEFTPAREN ColList RIGHTPAREN
		$$ = $2;
	} 
	| 
	{
	// InsertColSpec:
		$$ = NULL;
	}
	;

ColList: ColName
	{
	//	ColList: ColName
		$$ = $1;
	}
	| ColList COMMA ColName
	{
	//	ColList: ColList COMMA ColName
		$1->AddLast ($3);
		$$ = $1;
	}
	;	

InsertValueList:  ConstantExpression
	{ 
	// InsertValueList:  ConstantExpression
		$$=$1;
	}
	| InsertValueList COMMA ConstantExpression
	{
	// InsertValueList:  InsertValueList COMMA ConstantExpression
		$1->AddLast ($3);
		$$ = $1;
	}
	;

WhereClause: /* Empty */
	{
	//	WhereClause: /* Empty */
		//$$ = pState->MakeNode(NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| WHERE WhereConditions
	{
	// WhereClause: WHERE WhereConditions
		//$$ = pState->MakeNode (NodeType_WhereCondition, "Where");
		//$$->m_pLeftChild = $2;
		$$ = $2;
	}
	;

ConstantExpression: Value
	{
	// ConstantExpression: Value
		$$ = $1;
	}
	| ConstantExpression PLUS ConstantExpression
	{
	// ConstantExpression: ConstantExpression PLUS ConstantExpression
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression MINUS ConstantExpression
	{
	// ConstantExpression: ConstantExpression MINUS ConstantExpression
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression DIVIDE ConstantExpression
	{
	// ConstantExpression: ConstantExpression DIVIDE ConstantExpression
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ConstantExpression STAR ConstantExpression
	{
	// ConstantExpression: ConstantExpression STAR ConstantExpression
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN ConstantExpression RIGHTPAREN
	{
	// ConstantExpression: LEFTPAREN ConstantExpression RIGHTPAREN
		$$ = $2;
	}
	;

UpdateList: UpdateValue
	{
	//	UpdateList: UpdateValue
		$$ = $1;		
	}
	| UpdateList COMMA UpdateValue
	{
	//	UpdateList: UpdateList COMMA UpdateValue
		$1->AddLast ($3);
		$$ = $1;
	}
	;

UpdateValue: ColName EQUALS ValueOrColNameExpression
	{
	//	UpdateValue: ColName EQUALS ValueOrColNameExpression
		$$ = pState->MakeNode(NodeType_UpdateValue, "UpdateValue");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	;

WhereConditions: WherePredicate
	{
	//	WhereConditions: WherePredicate
		$$ = $1;		
	}
	| WhereConditions OR WhereConditions
	{
	//	WhereConditions: WhereConditions OR WhereConditions
		$$ = pState->MakeNode (NodeType_Or, "Or");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| WhereConditions AND WhereConditions
	{
	//	WhereConditions: WhereConditions OR WhereConditions
		$$ = pState->MakeNode (NodeType_And, "And");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	|	NOT WhereConditions 
	{
	//	WhereConditions: NOT WhereConditions 
		$$ = pState->MakeNode (NodeType_Not, "Not");
		$$->m_pLeftChild = $2;
		$$->m_pRightChild = NULL;
	}
	|	LEFTPAREN WhereConditions RIGHTPAREN
	{
	//	WhereConditions: LEFTPAREN WhereConditions RIGHTPAREN
		$$ = $2;
	}
	;

WherePredicate: ValueOrColNameExpression EQUALS ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression EQUALS ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_Equals, "Equals");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression NOT_EQUALS ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression NOT_EQUALS ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_NotEquals, "NotEquals");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression LESS ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression LESS ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_Less, "Less");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MORE ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression MORE ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_More, "More");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression LESS_EQUALS ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression LESS_EQUALS ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_LessEquals, "LESS_EQUALS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MORE_EQUALS ValueOrColNameExpression
	{
	//	WherePredicate: ValueOrColNameExpression MORE_EQUALS ValueOrColNameExpression
		$$ = pState->MakeNode (NodeType_MoreEquals, "MORE_EQUALS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ColName IS NOT SQL_NULL
	{
	//	WherePredicate:  ColName IS NOT SQL_NULL
		$$ = pState->MakeNode (NodeType_IsNot, " IS NOT");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	}
	| ColName IS SQL_NULL
	{
	//	WherePredicate: ColName IS SQL_NULL
		$$ = pState->MakeNode (NodeType_Is, " IS");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = pState->MakeNode (NodeType_Null, "NULL");
	}
	| ColName LIKE String
	{
	//	WherePredicate: ColName LIKE String
		$$ = pState->MakeNode (NodeType_Like, "LIKE");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	;

ColName: Identifier DOT Identifier
	{ 
	//	ColName: Identifier DOT Identifier
		$$ = pState->MakeNode(NodeType_Dot, "dot");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| Identifier DOT STAR
	{
	//	ColName: Identifier DOT STAR
	// #HK010514: Tabelle.* ist als SpaltenId erlaubt
		$$ = pState->MakeNode(NodeType_Dot, "dot");
		$$->m_pLeftChild = $1;
		$3 = pState->MakeNode (NodeType_Star, "*");
		$$->m_pRightChild = $3;
	}
	| Identifier							   
	{ 
	//	ColName: Identifier
		$$ = pState->MakeNode(NodeType_Dot, "dot");
		$$->m_pLeftChild = NULL;
		$$->m_pRightChild = $1;
	}
	;
 
IdentList: IdentifierWithAlias
	{
	//	IdentList: IdentifierWithAlias
		$$ = $1;	// pState->MakeNode(NodeType_Identifier, "id");
	}
	| IdentList COMMA IdentifierWithAlias
	{
	//	IdentList: IdentList COMMA IdentifierWithAlias
		$1->AddLast ($3);
		$$ = $1;
	}
	;

IdentifierWithAlias:	Identifier
	{
	// IdentifierWithAlias:	Identifier
		$$ = $1;
	}
	| Identifier AS Identifier
	{
	// IdentifierWithAlias:	Identifier AS Identifier
		$1->m_pLeftChild = NULL;
		$1->m_pRightChild = $3;
		$$ = $1;
	}
	| Identifier Identifier
	{
	// IdentifierWithAlias:	Identifier Identifier
		$1->m_pLeftChild = NULL;
		$1->m_pRightChild = $2;
		$$ = $1;
	}
	;
	
Identifier: IDENTIFIER
	{ 
	//	Identifier: IDENTIFIER
		$$ = pState->MakeNode(NodeType_Identifier, "id");
	}
	;

SelectExpression: SelectExpressionItem
	{
	//	SelectExpression: SelectExpressionItem
		$$ = $1;
	}
	| SelectExpression PLUS SelectExpression
	{
	//	SelectExpression: SelectExpression PLUS SelectExpression
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression MINUS SelectExpression
	{
	//	SelectExpression: SelectExpression MINUS SelectExpression
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression DIVIDE SelectExpression
	{
	//	SelectExpression: SelectExpression DIVIDE SelectExpression
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| SelectExpression STAR SelectExpression
	{
	//	SelectExpression: SelectExpression STAR SelectExpression
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN SelectExpression RIGHTPAREN
	{
	//	SelectExpression: SelectExpression RIGHTPAREN
		$$ = $2;
	}
	;

SelectExpressionItem: ValueOrColName
	{
	// SelectExpressionItem: ValueOrColName
		$$ = $1;
	}
	| Aggregate
	{
	// SelectExpressionItem: Aggregate
		$$ = $1;
	}
	| Function
	{
	// SelectExpressionItem: Function
		$$ = $1;
	}
	;

ValueOrColName: Value
	{
	// ValueOrColName: Value
		$$ = $1;
	}			 
	| ColName
	{
	// ValueOrColName: ColName
		$$ = $1;
	}
	;

ValueOrColNameExpression: ValueOrColName
	{
	// ValueOrColNameExpression: ValueOrColName
		$$ = $1;
	}
	| Function
	{
	// ValueOrColNameExpression: Function
		$$ = $1;
	}
	| ValueOrColNameExpression PLUS ValueOrColNameExpression
	{
	// ValueOrColNameExpression: ValueOrColNameExpression PLUS ValueOrColNameExpression
		$$ = pState->MakeNode(NodeType_ExpressionAdd, "+");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression MINUS ValueOrColNameExpression
	{
	// ValueOrColNameExpression: ValueOrColNameExpression MINUS ValueOrColNameExpression
		$$ = pState->MakeNode(NodeType_ExpressionMinus, "-");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression DIVIDE ValueOrColNameExpression
	{
	// ValueOrColNameExpression: ValueOrColNameExpression DIVIDE ValueOrColNameExpression
		$$ = pState->MakeNode(NodeType_ExpressionDivide, "/");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| ValueOrColNameExpression STAR ValueOrColNameExpression
	{
	// ValueOrColNameExpression: ValueOrColNameExpression STAR ValueOrColNameExpression
		$$ = pState->MakeNode(NodeType_ExpressionMultiply, "*");
		$$->m_pLeftChild = $1;
		$$->m_pRightChild = $3;
	}
	| LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// ValueOrColNameExpression: ValueOrColNameExpression RIGHTPAREN
		$$ = $2;
	};

/* Group by */
GroupByClause: /* Empty */
	{
	// GroupByClause: /* Empty */
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| GROUP BY ColName
	{
	// GroupByClause: GROUP BY ColName
		$$ = $3;
	}
	;

HavingClause: /* Empty */
	{
	// HavingClause: /* Empty */
		$$ = NULL;
	}
	| HAVING WhereConditions
	{
	// HavingClause: HAVING WhereConditions
		$$ = $2;
	}
	; 

OrderClause: /* Empty */
	{
	// OrderClause: /* Empty */
		//$$ = pState->MakeNode (NodeType_Empty, "Empty");
		$$ = NULL;
	}
	| ORDER BY OrderColList
	{
	// OrderClause: ORDER BY OrderColList
		$$ = $3;
	}
	;

OrderColList: OrderCol
	{
	// OrderColList: OrderCol
		$$ = $1;
	}
	| OrderColList COMMA OrderCol
	{
	// OrderColList: OrderColList COMMA OrderCol
		$1->AddLast ($3);
		$$ = $1;
	}
	;

OrderCol: ColName
	{
	// OrderCol: ColName
		$$ = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		$$->m_pLeftChild = $1;
	}
	| ColName ASC
	{
	// OrderCol: ColName ASC
		$$ = pState->MakeNode (NodeType_OrderASC, "OrderASC");
		$$->m_pLeftChild = $1;
	}
	| ColName DESC
	{
	// OrderCol: ColName DESC
		$$ = pState->MakeNode (NodeType_OrderDESC, "OrderDESC");
		$$->m_pLeftChild = $1;
	}
	;

Value: LiteralValue
	{
	// Value: LiteralValue
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
	// Function: MathFunction
		$$ = $1;
	}
	| DateFunction
	{
	// Function: DateFunction
		$$ = $1;
	}
	| GeometryFunction
	{
	// GeometryFunction
		$$ = $1;
	}
	;

MathFunction: ABS LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// MathFunction: ABS LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		$$->m_pLeftChild = $3;	
	}
	|	ROUND LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// MathFunction: ROUND LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_FunctionAbs, "ABS");
		$$->m_pLeftChild = $3;	
	}
	;

DateFunction:	GETDATE LEFTPAREN RIGHTPAREN
	{
	// DateFunction:	GETDATE LEFTPAREN RIGHTPAREN
		$$ = pState->MakeNode (NodeType_FunctionGetDate, "GETDATE");
	}
	;

GeometryFunction:
		ASTEXT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// ASTEXT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionAsText, "ASTEXT");
		$$->m_pLeftChild = $3;
	}
	|	ASBINARY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// ASBINARY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionAsBinary, "ASBINARY");
		$$->m_pLeftChild = $3;
	}
	|	DIMENSION LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// DIMENSION LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionDimension, "DIMENSION");
		$$->m_pLeftChild = $3;
	}
	|	GEOMETRYTYPE LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// GEOMETRYTYPE LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionGeometryType, "GEOMETRYTYPE");
		$$->m_pLeftChild = $3;
	}
	|	SRID LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// SRID LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionSRID, "SRID");
		$$->m_pLeftChild = $3;
	}
	|	ISEMPTY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// ISEMPTY LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_GeometryFunctionIsEmpty, "ISEMPTY");
		$$->m_pLeftChild = $3;
	}
	;

Aggregate: SUM LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// Aggregate: SUM LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateSum, "SUM");
		$$->m_pLeftChild = $3;
	}
	| AVG LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// Aggregate: AVG LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateAvg, "AVG SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| MAX LEFTPAREN ValueOrColNameExpression	RIGHTPAREN
	{
	// Aggregate: MAX LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateMax, "MAX SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| MIN LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// Aggregate: MIN LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateMin, "MIN SUBEXPR");
		$$->m_pLeftChild = $3;
	}
	| COUNT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
	{
	// Aggregate: COUNT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateCount, "COUNT COLNAME");
		$$->m_pLeftChild = $3;
	}
	| COUNT LEFTPAREN STAR  RIGHTPAREN
	{
	// Aggregate: COUNT LEFTPAREN ValueOrColNameExpression RIGHTPAREN
		$$ = pState->MakeNode (NodeType_AggregateCount, "COUNT *");
		$$->m_pLeftChild = pState->MakeNode (NodeType_Star, "*");;
	}
	;

ColDataTypeList: Identifier DataType
	{
	// ColDataTypeList: Identifier DataType
		$1->m_pLeftChild = $2;
		$$=$1;
	}
	|	ColDataTypeList COMMA Identifier DataType
	{
	// ColDataTypeList: ColDataTypeList COMMA Identifier DataType
		$3->m_pLeftChild = $4;
		$1->AddLast ($3);
		$$ = $1;
	}
	;

DataType: CHAR_DATATYPE LEFTPAREN Number RIGHTPAREN 		
	{
	// DataType: CHAR_DATATYPE LEFTPAREN Number RIGHTPAREN 		
		$$ = pState->MakeNode(NodeType_CharDataType, "character_typ");
		$$->m_pLeftChild = $3;
	}
	| INTEGER_DATATYPE
	{
	// DataType: INTEGER_DATATYPE	
		$$ = pState->MakeNode(NodeType_IntegerDataType, "integer_typ");
	}
	| FLOAT_DATATYPE			   
	{
	// DataType: FLOAT_DATATYPE	
		$$ = pState->MakeNode(NodeType_FloatDataType, "float_typ");
	}
	| SMALLINT_DATATYPE
	{
	// DataType: SMALLINT_DATATYPE	
		$$ = pState->MakeNode (NodeType_IntegerDataType, "integer_typ");
	}
	| TEXT_DATATYPE
	{
	// DataType: TEXT_DATATYPE	
		$$ = pState->MakeNode (NodeType_SmallIntDataType, "text_type");
	}
	;

LiteralValue:	Number 
	{ 
	// LiteralValue:	Number 
		$$ = $1; 
	}
	| Float 
	{ 
	// LiteralValue:	Float 
		$$ = $1; 
	}
	| String 
	{ 
	// LiteralValue:	String 
		$$ = $1; 
	}
	;

Number: NUMBER_VALUE
	{
	// Number: NUMBER_VALUE
		$$ = pState->MakeNode(NodeType_Integer_Value, "Number");
	}
	;

Float: FLOAT_VALUE
	{
	// Float: FLOAT_VALUE
		$$ = pState->MakeNode(NodeType_Float_Value, "Float");
	}
	;

String: STRING_VALUE
	{
	// String: STRING_VALUE
		$$ = pState->MakeNode(NodeType_String_Value, "String");
	}
	;

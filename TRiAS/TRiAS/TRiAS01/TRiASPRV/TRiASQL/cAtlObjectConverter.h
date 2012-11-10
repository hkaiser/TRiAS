/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: cAtlObjectConverter.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// cAtlObjectConverter.h: interface for the cAtlObjectConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CATLOBJECTCONVERTER_H__6E28FF47_272F_11D3_857F_00104B8CC00A__INCLUDED_)
#define AFX_CATLOBJECTCONVERTER_H__6E28FF47_272F_11D3_857F_00104B8CC00A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cTableIdentList;
class cTableIdent;
class CSQLNode;
class cColumnIdent;
class cColumnIdentList;
class cOrderByObjList;
class cOrderByObj;
class cGenericStack;
class cGenericStackList;
class cLiteralValue;
class cUpdateItemList;
class cUpdateItem;
class cCreateTableItem;
class cCreateTableItemList;

class cAtlObjectConverter  
{
public:
	cAtlObjectConverter();
	virtual ~cAtlObjectConverter();
	
	static bool NodeToUpdateItemList( CSQLNode *pNode, cUpdateItemList *pTableIdentList );
	static bool NodeToUpdateItem( CSQLNode *pNode, cUpdateItem *pIdentifier );
	static bool NodeToTableIdentifierList( CSQLNode *pNode, cTableIdentList *pTableIdentList );
	static bool NodeToTableIdentifier( CSQLNode *pNode, cTableIdent *pIdentifier );
	static bool NodeToColumnIdentifier( CSQLNode *pNode, cColumnIdent *pIdentifier );
	static bool NodeToColumnIdentifierList( CSQLNode *pNode, cColumnIdentList *pList );
	static bool NodeToOrderByList( CSQLNode *pNode, cOrderByObjList *pList );
	static bool NodeToOrderByObj( CSQLNode *pNode, cOrderByObj *pObj );
	static bool NodeToExpressionStack( CSQLNode * pNode, cGenericStack *pStack );
	static bool NodeToExpressionStackList( CSQLNode * pNode, cGenericStackList *pStackList );
	static bool RecurseExpression( CSQLNode *pNode, cGenericStack *pStack );
	static bool NodeToLiteralValue( CSQLNode * pNode, cLiteralValue *pLiteralValue );
	static bool NodeToCreateTableItemList( CSQLNode * pNode, cCreateTableItemList *pList );
	static bool NodeToCreateTableItem( CSQLNode * pNode, cCreateTableItem *pItem );
};

#endif // !defined(AFX_CATLOBJECTCONVERTER_H__6E28FF47_272F_11D3_857F_00104B8CC00A__INCLUDED_)

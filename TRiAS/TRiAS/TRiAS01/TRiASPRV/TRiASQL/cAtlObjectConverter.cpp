/*  Product: Small Parser

  Copyright(C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http:// www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: cAtlObjectConverter.cpp $ 
* 
* *****************  Version 3  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 8:47p
* Updated in $/Products/SmallParser
* Fixing headers so all code is in CPP - files
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
* Updated in $/Products/SmallParser
*/

// cAtlObjectConverter.cpp: implementation of the cAtlObjectConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <LocaleHelpers.h>

#include "cAtlObjectConverter.h"
#include "parser\ParseTree.h"
#include "TableIdentList.h"
#include "ColumnIdentList.h"
#include "OrderByList.h"
#include "GenericStackList.h"
#include "LiteralValue.h"
#include "AggregateFunction.h"
#include "NullExpression.h"
#include "SelectStarExpression.h"
#include "AritOperator.h"
#include "CompareOperator.h"
#include "BoolOperator.h"
#include "MathFunction.h"
#include "GeometryFunction.h"
#include "DateFunction.h"
#include "UpdateItemList.h"
#include "CreateTableItemList.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cAtlObjectConverter::cAtlObjectConverter()
{
}

cAtlObjectConverter::~cAtlObjectConverter()
{
}

bool cAtlObjectConverter::RecurseExpression(CSQLNode *pNode, cGenericStack *pStack)
{
	// What can it be?
	bool fRecurse = true;
	if (!pNode)
		return true;
	
CComVariant vAdd;
	
	switch (pNode->m_NodeType) {
	case NodeType_Dot:
		{
			CComObject<cColumnIdent> *pIdent;
			CComObject<cColumnIdent>::CreateInstance(&pIdent);
			NodeToColumnIdentifier(pNode, pIdent);
			vAdd = pIdent;
			fRecurse = false;
		}
		break;

	case NodeType_Identifier: // Assume literal value
		{
			CComObject<cLiteralValue> *pIdent;
			CComObject<cLiteralValue>::CreateInstance(&pIdent);
			NodeToLiteralValue(pNode, pIdent);
			vAdd = pIdent;
			fRecurse = false;
		}
		break;

	case NodeType_Null:
		{
			CComObject<cNullExpression> *pIdent;
			CComObject<cNullExpression>::CreateInstance(&pIdent);
			vAdd = pIdent;
			fRecurse = false;
		}
		break;

	case NodeType_Star:
		{
			CComObject<cSelectStarExpression> *pIdent;
			CComObject<cSelectStarExpression>::CreateInstance(&pIdent);
			vAdd = pIdent;
			fRecurse = false;
		}
		break;

	case NodeType_ExpressionAdd:
		{
			CComObject<cAritOperator> *pIdent;
			CComObject<cAritOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetAritOperator(ARIT_OPERATOR_PLUS);
		}
		break;

	case NodeType_ExpressionMinus:
		{
			CComObject<cAritOperator> *pIdent;
			CComObject<cAritOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetAritOperator(ARIT_OPERATOR_MINUS);
		}
		break;

	case NodeType_ExpressionDivide:
		{
			CComObject<cAritOperator> *pIdent;
			CComObject<cAritOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetAritOperator(ARIT_OPERATOR_DIVIDE);
		}
		break;

	case NodeType_ExpressionMultiply:
		{
			CComObject<cAritOperator> *pIdent;
			CComObject<cAritOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetAritOperator(ARIT_OPERATOR_MULTIPLY);
		}
		break;

	case NodeType_Not:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_NOT);
		}
		break;

	case NodeType_Is:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_IS);
		}
		break;

	case NodeType_IsNot:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_ISNOT);
		}
		break;

	case NodeType_Like:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_LIKE);
		}
		break;

	case NodeType_NotEquals:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_NOT_EQUALS);
		}
		break;

	case NodeType_Equals:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_EQUALS);
		}
		break;

	case NodeType_And:
		{
			CComObject<cBoolOperator> *pIdent;
			CComObject<cBoolOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetBoolOperator(BOOL_OPERATOR_AND);
		}
		break;

	case NodeType_Or:
		{
			CComObject<cBoolOperator> *pIdent;
			CComObject<cBoolOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetBoolOperator(BOOL_OPERATOR_OR);
		}
		break;

	case NodeType_MoreEquals:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_MOREEQUALS);
		}
		break;

	case NodeType_LessEquals:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_LESSEQUALS);
		}
		break;

	case NodeType_More:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_MORE);
		}
		break;

	case NodeType_Less:
		{
			CComObject<cCompareOperator> *pIdent;
			CComObject<cCompareOperator>::CreateInstance(&pIdent);
			vAdd = pIdent;
			pIdent->SetCompareOperator(COMPARE_OPERATOR_LESS);
		}
		break;

	case NodeType_AggregateCount:
		{
			CComObject<cAggregateFunction> *pIdent;
			CComObject<cAggregateFunction>::CreateInstance(&pIdent);
			pIdent->SetAggregateFunction(AGGREGATE_FUNCTION_COUNT);
			vAdd = pIdent;
		}
		break;

	case NodeType_AggregateAvg:
		{
			CComObject<cAggregateFunction> *pIdent;
			CComObject<cAggregateFunction>::CreateInstance(&pIdent);
			pIdent->SetAggregateFunction(AGGREGATE_FUNCTION_AVG);
			vAdd = pIdent;
		}
		break;

	case NodeType_AggregateMax:
		{
			CComObject<cAggregateFunction> *pIdent;
			CComObject<cAggregateFunction>::CreateInstance(&pIdent);
			pIdent->SetAggregateFunction(AGGREGATE_FUNCTION_MAX);
			vAdd = pIdent;
		}
		break;

	case NodeType_AggregateMin:
		{
			CComObject<cAggregateFunction> *pIdent;
			CComObject<cAggregateFunction>::CreateInstance(&pIdent);
			pIdent->SetAggregateFunction(AGGREGATE_FUNCTION_MIN);
			vAdd = pIdent;
		}
		break;

	case NodeType_AggregateSum:
		{
			CComObject<cAggregateFunction> *pIdent;
			CComObject<cAggregateFunction>::CreateInstance(&pIdent);
			pIdent->SetAggregateFunction(AGGREGATE_FUNCTION_SUM);
			vAdd = pIdent;
		}
		break;

	case NodeType_FunctionAbs:
		{
			CComObject<cMathFunction> *pIdent;
			CComObject<cMathFunction>::CreateInstance(&pIdent);
			pIdent->SetMathFunction(MATH_FUNCTION_ABS);
			vAdd = pIdent;
		}
		break;

	case NodeType_FunctionGetDate:
		{
			CComObject<cDateFunction> *pIdent;
			CComObject<cDateFunction>::CreateInstance(&pIdent);
			pIdent->SetDateFunction(DATE_FUNCTION_GETDATE);
			vAdd = pIdent;
		}
		break;
		
	case NodeType_GeometryFunctionAsText:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_ASTEXT);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_GeometryFunctionAsBinary:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_ASBINARY);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_GeometryFunctionDimension:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_DIMENSION);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_GeometryFunctionGeometryType:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_GEOMETRYTYPE);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_GeometryFunctionSRID:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_SRID);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_GeometryFunctionIsEmpty:
		{
		CComObject<CGeometryFunction> *pGeomFunc = NULL;

			CComObject<CGeometryFunction>::CreateInstance(&pGeomFunc);
			pGeomFunc->SetGeomFunction(GEOMETRY_FUNCTION_ISEMPTY);
			vAdd = pGeomFunc;
		}
		break;

	case NodeType_Integer_Value:
	case NodeType_Float_Value:
	case NodeType_String_Value:
		{
			CComObject<cLiteralValue> *pIdent;
			CComObject<cLiteralValue>::CreateInstance(&pIdent);
			NodeToLiteralValue(pNode, pIdent);
			vAdd = pIdent;
			fRecurse = false;
		}
		break;
	}
	if (fRecurse)
	{
		if (pNode->m_pLeftChild)
			RecurseExpression(pNode->m_pLeftChild, pStack);
		if (pNode->m_pRightChild)
			RecurseExpression(pNode->m_pRightChild, pStack);
	}
	pStack->AddItem(vAdd); 
	return true;
}


bool cAtlObjectConverter::NodeToExpressionStack(CSQLNode *pNode, cGenericStack *pStack)
{
	// Now recurse the tree...
	
	if (pNode && pNode->m_NodeType == NodeType_AsName)
	{
		pStack->SetAsName(pNode->m_pRightChild->m_pSQLToken->GetAsString());	
		pNode = pNode->m_pLeftChild;
	}
	return RecurseExpression(pNode, pStack);
}



bool cAtlObjectConverter::NodeToExpressionStackList(CSQLNode *pNode, cGenericStackList *pStackList)
{
	while (pNode)
	{
		CComObject<cGenericStack> *pStack;
		CComObject<cGenericStack>::CreateInstance(&pStack);
		//		pStack->AddRef();
		
		if (cAtlObjectConverter::NodeToExpressionStack(pNode, pStack) == false)
		{
			return false;
		}
		pStackList->AddItem(pStack);
		pNode = pNode->m_pNext;
	}
	
	return true;
}



bool cAtlObjectConverter::NodeToCreateTableItemList(CSQLNode * pNode, cCreateTableItemList *pList)
{
	while (pNode)
	{
		CComObject<cCreateTableItem> *pObj;
		CComObject<cCreateTableItem>::CreateInstance(&pObj);
		cAtlObjectConverter::NodeToCreateTableItem(pNode, pObj);
		
		//		pObj->AddRef();
		
		pList->AddItem(pObj);
		pNode = pNode->m_pNext;
	}
	return true;
}

bool cAtlObjectConverter::NodeToCreateTableItem(CSQLNode * pNode, cCreateTableItem *pItem)
{
	CSQLNode *pDataTypeNode = pNode->m_pLeftChild;
	int nFieldLen;
	PARSER_DATATYPE DataType;
	
	
	switch (pDataTypeNode->m_NodeType)
	{
		case NodeType_CharDataType:
			nFieldLen = atoi(pDataTypeNode->m_pLeftChild->m_pSQLToken->GetAsString());
			DataType = PARSER_DATATYPE_STRING;
			break;
			
		case NodeType_IntegerDataType:
			nFieldLen = sizeof(long);
			DataType = PARSER_DATATYPE_INTEGER;
			break;
			
		case NodeType_FloatDataType:
			nFieldLen = sizeof(double);
			DataType = PARSER_DATATYPE_FLOAT;
			break;
			
		case NodeType_TextDataType:
			nFieldLen = LONG_MAX;
			DataType = PARSER_DATATYPE_STRING;
			break;
			
			//		case NodeType_SmallIntDataType:
			//			nFieldLen = sizeof(int);
			//			DataType = SQLObjectsGlobal::TABLE_DATATYPE_SMALLINT;
			//			break;
	}
	
	pItem->m_strColumnName = pNode->m_pSQLToken->GetAsString();
	pItem->m_DataType = DataType;
	pItem->m_nDataLength = nFieldLen;
	return true;
}



bool cAtlObjectConverter::NodeToColumnIdentifier(CSQLNode *pNode, cColumnIdent *pObj)
{
	_ASSERTE(pNode);
	
	switch (pNode->m_NodeType)
	{
		case NodeType_Identifier:
			pObj->SetColumnName(pNode->m_pSQLToken->GetAsString());
			break;
			
		case NodeType_Dot:
			{
				if (NodeType_Star == pNode->m_pRightChild->m_NodeType)
					pObj->SetColumnName("*");
				else
					pObj->SetColumnName(pNode->m_pRightChild->m_pSQLToken->GetAsString());
				
				if (pNode->m_pLeftChild)
					pObj->SetTableName(pNode->m_pLeftChild->m_pSQLToken->GetAsString());
				else
					pObj->SetTableName("");
			}
			break;
			
		case NodeType_Star:
			pObj->SetColumnName("*");
			
		default:
			_ASSERTE(FALSE);
			return false;
	}
	return true;
}	



bool cAtlObjectConverter::NodeToColumnIdentifierList(CSQLNode* pNode, cColumnIdentList *pList)
{
	while (pNode)
	{
		CComObject<cColumnIdent> *pObj;
		CComObject<cColumnIdent>::CreateInstance(&pObj);
		//		pObj->AddRef();
		NodeToColumnIdentifier(pNode, pObj);
		// CComVariant v = pIdentifier;
		pList->AddItem(pObj);
		pNode = pNode->m_pNext;
	}
	return true;
}	



bool cAtlObjectConverter::NodeToUpdateItemList(CSQLNode *pNode, cUpdateItemList *pList)
{
	while (pNode)
	{
		CComObject<cUpdateItem> *pIdentifier;
		CComObject<cUpdateItem>::CreateInstance(&pIdentifier);
		//		pIdentifier->AddRef();
		
		NodeToUpdateItem(pNode,  pIdentifier);
		pList->AddItem(pIdentifier);
		pNode = pNode->m_pNext;
	}
	return true;
}

bool cAtlObjectConverter::NodeToUpdateItem(CSQLNode *pNode, cUpdateItem *pUpdateItem)
{
	cAtlObjectConverter::NodeToColumnIdentifier(pNode->m_pLeftChild, pUpdateItem->m_pColumnIdent);
	cAtlObjectConverter::NodeToExpressionStack(pNode->m_pRightChild, pUpdateItem->m_pExpressionStack);
	return true;
}


bool cAtlObjectConverter::NodeToOrderByList(CSQLNode *pNode, cOrderByObjList *pList)
{
	while (pNode)
	{
		CComObject<cOrderByObj> *pIdentifier;
		CComObject<cOrderByObj>::CreateInstance(&pIdentifier);
		//		pIdentifier->AddRef();
		
		NodeToOrderByObj(pNode,  pIdentifier);
		pList->AddItem(pIdentifier);
		pNode = pNode->m_pNext;
	}
	return true;
}

bool cAtlObjectConverter::NodeToOrderByObj(CSQLNode *pNode, cOrderByObj *pNewObj)
{
	_ASSERTE((pNode->m_NodeType == NodeType_OrderDESC) || (pNode->m_NodeType == NodeType_OrderASC));
	
	if (pNode->m_NodeType == NodeType_OrderDESC)
		pNewObj->SetAsc(false);
	else
		pNewObj->SetAsc(true);	
	
	cAtlObjectConverter::NodeToColumnIdentifier(pNode->m_pLeftChild, pNewObj->m_pColumnIdent);
	return true;
}

bool cAtlObjectConverter::NodeToTableIdentifier(CSQLNode *pNode, cTableIdent *pIdentifier)
{
	pIdentifier->SetName(pNode->m_pSQLToken->GetAsString());
	if (NULL != pNode -> m_pRightChild)
		pIdentifier->SetAlias(pNode -> m_pRightChild -> m_pSQLToken -> GetAsString());
	return true;
}	

bool cAtlObjectConverter::NodeToLiteralValue(CSQLNode * pNode, cLiteralValue *pLiteralValue)
{
	_ASSERTE(pNode);	
	_ASSERTE(pNode->m_pSQLToken);	
	
	pLiteralValue->SetData(pNode->m_pSQLToken->GetAsString());
	switch (pNode->m_NodeType) {
	case NodeType_Integer_Value:
		pLiteralValue->SetData(pNode->m_pSQLToken->GetAsString());
		pLiteralValue->SetDataType(PARSER_DATATYPE_INTEGER);
		break;

	case NodeType_Float_Value:	// 'C' locale in aktuelles locale konvertieren
		{
		int iConverted = 0;
		double dValue = 0.0;
		
			{	// englisches locale
			CSetLocale locale("C");

				iConverted = sscanf(pNode->m_pSQLToken->GetAsString(), "%lf", &dValue);
			}
			if (1 == iConverted) {
			char cbBuffer[_MAX_PATH];
			CSetLocale locale;

				sprintf (cbBuffer, "%lf", dValue);
				pLiteralValue->SetData(cbBuffer);
			} else
				pLiteralValue->SetData(pNode->m_pSQLToken->GetAsString());

			pLiteralValue->SetDataType(PARSER_DATATYPE_FLOAT);
		}
		break;

	case NodeType_String_Value:
		pLiteralValue->SetData(pNode->m_pSQLToken->GetAsString());
		pLiteralValue->SetDataType(PARSER_DATATYPE_STRING);
		break;
		
	default:
		_ASSERTE(FALSE);
		break;
	}
	return true;
}

bool cAtlObjectConverter::NodeToTableIdentifierList(CSQLNode *pNode, cTableIdentList *pTableIdentList)
{
	while (pNode)
	{
		CComObject<cTableIdent> *pIdentifier;
		CComObject<cTableIdent>::CreateInstance(&pIdentifier);

		switch (pNode->m_NodeType) {
		case NodeType_Identifier:
			NodeToTableIdentifier(pNode,  pIdentifier);
			pTableIdentList->AddItem(pIdentifier);
			break;
			
		default:
			_ASSERTE(FALSE);
			return false;
		}
		pNode = pNode->m_pNext;
	}
	return true;
}

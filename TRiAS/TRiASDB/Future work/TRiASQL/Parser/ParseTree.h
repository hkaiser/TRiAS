/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ParseTree.h $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 8:48p
 * Updated in $/Products/SmallParser/Parser
 * Fixing headers
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:25p
 * Updated in $/Products/SmallParser/Parser
*/

#ifndef __CParseTree_H
#define __CParseTree_H

#include "flexlexer.h"

//Node types
typedef enum
{
	NodeType_Integer_Value = 1,
	NodeType_Float_Value,
	NodeType_String_Value,
	NodeType_Identifier,

	NodeType_CreateTable,
	NodeType_DropTable,

	NodeType_Dot,
	NodeType_Insert,
	NodeType_Null,
	NodeType_Delete,
	NodeType_AsName,
	NodeType_Not,
	NodeType_Equals,
	NodeType_NotEquals,
	NodeType_And,
	NodeType_Or,
	NodeType_MoreEquals,
	NodeType_LessEquals,
	NodeType_More,
	NodeType_Less,
	NodeType_Is,
	NodeType_IsNot,
	NodeType_Like,
	NodeType_Star,
	NodeType_Select,
	NodeType_Distinct,
	NodeType_Update,
	NodeType_UpdateValue,

	NodeType_OrderDESC,
	NodeType_OrderASC,

	NodeType_CharDataType,
	NodeType_IntegerDataType,
	NodeType_FloatDataType,
	NodeType_SmallIntDataType,

	NodeType_ExpressionAdd,
	NodeType_ExpressionMinus,
	NodeType_ExpressionDivide,
	NodeType_ExpressionMultiply,

	NodeType_AggregateCount,
	NodeType_AggregateAvg,
	NodeType_AggregateMax,
	NodeType_AggregateMin,
	NodeType_AggregateSum,

	NodeType_FunctionAbs,
	NodeType_FunctionGetDate,

	NodeType_Undefined
} NODETYPE;






class CSQLToken : public CObject
{
public:
    CSQLToken( int nType, const TCHAR *szText )
        {
        m_nType = nType;
		m_strText = szText;
        }

	~CSQLToken()
		{
		}

	int GetType();
	
	inline CString GetAsString()
		{
		return m_strText;
		}
	
	inline long GetAsLong()
		{
		return atol( m_strText );
		}
	
	inline double GetAsDouble()
		{
		return atof( m_strText );
		}

protected:
    int m_nType;
    CString m_strText;
};



class CSQLNode : public CObject
{
public:
	CSQLNode()
		{
        m_pSQLToken = NULL;
        m_NodeType = NodeType_Undefined;
        m_pNext = NULL;
        m_pLeftChild = NULL;
		m_pRightChild = NULL;
		m_strText = "";
		}

	void AddLast( CSQLNode *pNewNode )
		{
		if ( m_pNext )
			m_pNext->AddLast( pNewNode );
		else
			m_pNext = pNewNode;
		}

    CSQLToken *m_pSQLToken; //Corresponding SQL-token, valid only if identifier or value
    CSQLNode *m_pNext;
    CSQLNode *m_pLeftChild;
	CSQLNode *m_pRightChild;
    NODETYPE m_NodeType;
	CString m_strText;						 
};


typedef CMapStringToObjectPtrTempl<CSQLNode *> CSQLNodeMap;
typedef CObArrayTempl<CSQLNode *> CSQLNodeArray;
typedef CObArrayTempl<CSQLToken *> CSQLTokenArray;


class CParseTree : public CObject
{
public:
	CParseTree()
		{
		Clear();
		}

	~CParseTree();

	void Clear();

	inline void SetFirst( CSQLNode *pNode )
		{
		m_pFirst = pNode;
		}
	
	inline CSQLNode *GetFirst()
		{
		return m_pFirst;
		}

	inline void SetError( const char *szError )
		{
		m_strError = szError;
		}

	inline CString GetError()
		{
		return m_strError;
		}

	int ParseSQL( CString strSQL );
	CSQLNode *MakeNode( NODETYPE NodeType, const TCHAR *szText );
	void AddToken( int NodeType, const TCHAR *strText );
	
	inline void AddNameForObject( CSQLNode *pObject, const TCHAR *strText )
		{
		m_NameMap.SetAt( strText, pObject );
		}

	CSQLNode* GetObjectNameForName( const TCHAR *strText )
		{
		CSQLNode *pRet = NULL;
		pRet = m_NameMap.Lookup( strText);
		return pRet;
		}


protected:	
	CSQLNodeArray m_NodeArray;
	CSQLTokenArray m_TokenArray;
	CSQLToken *m_pCurrentToken;
	CSQLNodeMap m_NameMap;
	CSQLNode *m_pFirst;
	CString m_strError;
};


#endif

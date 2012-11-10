/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: ParseTree.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/14/99    Time: 4:26p
 * Updated in $/Products/SmallParser/Parser
 * Fixed double deletion error
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:25p
 * Updated in $/Products/SmallParser/Parser
*/

#include "stdafx.h"
#include "ParseTree.h"

#ifdef _DEBUG
#include "..\shalloc.h"
#define new DEBUG_NEW
#endif



int yyparse( CParseTree *pTree, yyFlexLexer *pLexer );


CParseTree::~CParseTree()
{
	Clear();
}

void CParseTree::Clear()
{
	m_pFirst = NULL;
	
	m_NameMap.RemoveAll();

	for ( int i = 0; i < m_TokenArray.GetSize(); i++ )
		delete m_TokenArray.GetAt( i );
	m_TokenArray.RemoveAll();
	
	for ( i = 0; i < m_NodeArray.GetSize(); i++ )
		delete m_NodeArray.GetAt( i );
	m_NodeArray.RemoveAll();



	m_strError.Empty();
}



void CParseTree::AddToken( int NodeType, const TCHAR *strText )
{
//	m_pCurrentToken = ( CSQLToken *) new char[1234];
	m_pCurrentToken = new CSQLToken( NodeType, strText ) ;
	m_TokenArray.AddTail( m_pCurrentToken );
}


int CParseTree::ParseSQL( CString strSQL )
{
	yyFlexLexer Lexer;
	Clear();
	Lexer.SetInputString( this, (char *)(const char *)strSQL );
	return yyparse( this, &Lexer );
}



CSQLNode *CParseTree::MakeNode( NODETYPE NodeType, const TCHAR *szText )
{
CSQLNode *pNode = new CSQLNode;
pNode->m_strText = szText;
pNode->m_NodeType = NodeType;

m_NodeArray.Add( pNode );
switch( NodeType )
    {
    case NodeType_String_Value :
		//m_pCurrentToken->m_strText = 		
    case NodeType_Integer_Value :
    case NodeType_Float_Value :
    case NodeType_Identifier :
		//
		if ( NodeType == NodeType_Identifier  )
			{
			int j;
			j = 0;
			}
        pNode->m_pSQLToken =  m_pCurrentToken;
    default : 
        break;
    }
return pNode;
}

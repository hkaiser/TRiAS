/*  Product: Small Parser

  Copyright(C) 1999  Systementor AB, Stefan Holmberg
  Email - stefan.holmberg@systementor.se
  Web:   - http:// www.systementor.se
  
	///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: Parser.cpp $ 
* 
* *****************  Version 5  *****************
* User: Stefan Holmberg Date: 7/14/99    Time: 4:26p
* Updated in $/Products/SmallParser
* 
* *****************  Version 4  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 9:13p
* Updated in $/Products/SmallParser
* Changed Parser interface not to return IDispatch but real interface
* pointers
* 
* *****************  Version 3  *****************
* User: Stefan Holmberg Date: 7/13/99    Time: 6:45p
* Updated in $/Products/SmallParser
* 
* *****************  Version 2  *****************
* User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
* Updated in $/Products/SmallParser
*/

// Parser.cpp : Implementation of cParser

#include "stdafx.h"
#include "Parser.h"
#include "shalloc.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// cParser

#ifdef _DEBUG
CAllocationGuarder Guarder(__FILE__, __LINE__);
#endif

cParser::cParser()
{
	m_pSelectStmt = NULL;
	m_pUpdateStmt = NULL;
	m_pInsertStmt = NULL;
	m_pDeleteStmt = NULL;
	m_pCreateTableStmt = NULL;
	m_pDropStmt = NULL;
	m_STATEMENTTYPE = STATEMENT_TYPE_UNKNOWN;
}


cParser::~cParser()
{
	Clear();
}

void cParser::Clear()
{
	m_Tree.Clear();
	RELEASE(m_pSelectStmt);
	RELEASE(m_pUpdateStmt);
	RELEASE(m_pInsertStmt);
	RELEASE(m_pDeleteStmt);
	RELEASE(m_pCreateTableStmt);
	RELEASE(m_pDropStmt);
	m_STATEMENTTYPE = STATEMENT_TYPE_UNKNOWN;
}

STDMETHODIMP cParser::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IParser
	};
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i], riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP cParser::ParseSQL(BSTR bstrSQL)
{
ObjectLock l(this);

	Clear();
	if (m_Tree.ParseSQL(bstrSQL) != 0)
		return OleDBError(DB_E_ERRORSINCOMMAND, m_Tree.GetError());
	
	MAKE_OLEDB_ERROR(CreateStmt());
	return S_OK;
}

STDMETHODIMP cParser::get_SelectStmt(ISelectStmt **pVal)
{
ObjectLock l(this);

	if (m_pSelectStmt)
		m_pSelectStmt->AddRef();
	*pVal =  m_pSelectStmt;
	return S_OK;
}

STDMETHODIMP cParser::get_UpdateStmt(IUpdateStmt **pVal)
{
ObjectLock l(this);

	if (m_pUpdateStmt)
		m_pUpdateStmt->AddRef();
	*pVal =  m_pUpdateStmt;
	return S_OK;
}

STDMETHODIMP cParser::get_InsertStmt(IInsertStmt **pVal)
{
ObjectLock l(this);

	if (m_pInsertStmt)
		m_pInsertStmt->AddRef();
	*pVal =  m_pInsertStmt;
	return S_OK;
}


HRESULT cParser::CreateStmt()
{
	CSQLNode *pNode = m_Tree.GetFirst();
	_ASSERTE(pNode);
	
	switch (pNode->m_NodeType) {
	case NodeType_Select:
		RETURN_ERROR(CComObject<cSelectStmt>::CreateInstance(&m_pSelectStmt));
		m_pSelectStmt->AddRef();
		m_pSelectStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_SELECT;
		break;

	case NodeType_Update:
		RETURN_ERROR(CComObject<cUpdateStmt>::CreateInstance(&m_pUpdateStmt));
		m_pUpdateStmt->AddRef();
		m_pUpdateStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_UPDATE;
		break;

	case NodeType_Insert:
		RETURN_ERROR(CComObject<cInsertStmt>::CreateInstance(&m_pInsertStmt));
		m_pInsertStmt->AddRef();
		m_pInsertStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_INSERT;
		break;

	case NodeType_Delete:
		RETURN_ERROR(CComObject<cDeleteStmt>::CreateInstance(&m_pDeleteStmt));
		m_pDeleteStmt->AddRef();
		m_pDeleteStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_DELETE;
		break;

	case NodeType_DropTable:
		RETURN_ERROR(CComObject<cDropStmt>::CreateInstance(&m_pDropStmt));
		m_pDropStmt->AddRef();
		m_pDropStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_DROPTABLE;
		break;

	case NodeType_CreateTable:
		RETURN_ERROR(CComObject<cCreateTableStmt>::CreateInstance(&m_pCreateTableStmt));
		m_pCreateTableStmt->AddRef();
		m_pCreateTableStmt->InitializeFromParseTree(&m_Tree);
		m_STATEMENTTYPE = STATEMENT_TYPE_CREATETABLE;
		break;
	}
	return S_OK;
}



STDMETHODIMP cParser::get_StatementType(STATEMENT_TYPE *pVal)
{
ObjectLock l(this);

	*pVal = m_STATEMENTTYPE;
	return S_OK;
}

STDMETHODIMP cParser::get_DeleteStmt(IDeleteStmt **pVal)
{
ObjectLock l(this);

	if (m_pDeleteStmt)
		m_pDeleteStmt->AddRef();
	*pVal =  m_pDeleteStmt;
	return S_OK;
}

STDMETHODIMP cParser::get_CreateTableStmt(ICreateTableStmt **pVal)
{
ObjectLock l(this);

	if (m_pCreateTableStmt)
		m_pCreateTableStmt->AddRef();
	*pVal =  m_pCreateTableStmt;
	return S_OK;
}

STDMETHODIMP cParser::get_DropTableStmt(IDropStmt **pVal)
{
ObjectLock l(this);

	if (m_pDropStmt)
		m_pDropStmt->AddRef();
	*pVal =  m_pDropStmt;
	return S_OK;
}

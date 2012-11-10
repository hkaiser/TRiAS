/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: SelectStmt.h $ 
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:24p
 * Updated in $/Products/SmallParser
*/

// SelectStmt.h : Declaration of the cSelectStmt

#ifndef __SELECTSTMT_H_
#define __SELECTSTMT_H_

#include "resource.h"       // main symbols
#include "TableIdentList.h"       // main symbols
#include "ColumnIdentList.h"       // main symbols
#include "OrderByList.h"       // main symbols
#include "GenericStack.h"       // main symbols
#include "GenericStackList.h"       // main symbols
#include "Parser\ParseTree.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// cSelectStmt
class ATL_NO_VTABLE cSelectStmt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<cSelectStmt, &CLSID_SelectStmt>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISelectStmt, &IID_ISelectStmt, &LIBID_TRiASQL>
{
public:
	cSelectStmt();
	~cSelectStmt();
	void Clear();

	void InitializeFromParseTree( CParseTree *pTree );

	CComObject<cTableIdentList>			*m_pTableIdentList;
	CComObject<cOrderByObjList>			*m_pOrderByObjList;
	CComObject<cGenericStack>			*m_pWhereExpressionStack;
	CComObject<cColumnIdentList>		*m_pGroupByList;
	CComObject<cGenericStackList>		*m_pSelectExpressionStackList;
	CComObject<cGenericStack>			*m_pHavingExpressionStack;
protected:
	bool m_fDistinct;

public:

//	DECLARE_REGISTRY_RESOURCEID(IDR_SELECTSTMT)
	DECLARE_NO_REGISTRY()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(cSelectStmt)
		COM_INTERFACE_ENTRY(ISelectStmt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISelectStmt
public:
	STDMETHOD(get_GroupByObjList)(/*[out, retval]*/ IColumnIdentList* *pVal);
	STDMETHOD(get_HavingExpressionStack)(/*[out, retval]*/ IGenericStack* *pVal);
	STDMETHOD(get_SelectExpressionList)(/*[out, retval]*/ IGenericStackList* *pVal);
	STDMETHOD(get_WhereExpressionStack)(/*[out, retval]*/ IGenericStack* *pVal);
	STDMETHOD(get_OrderByObjList)(/*[out, retval]*/ IOrderByObjList* *pVal);
	STDMETHOD(get_TableIdentList)(/*[out, retval]*/ ITableIdentList **pVal);
	STDMETHOD(get_Distinct)(/*[out, retval]*/ BOOL *pVal);
};



#endif //__SELECTSTMT_H_

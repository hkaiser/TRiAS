/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Sep 08 10:13:26 1999
 */
/* Compiler settings for D:\TRiASDev.MVC\TRiASQL\TRiASQL.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TRiASQL_h__
#define __TRiASQL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IExpressionItem_FWD_DEFINED__
#define __IExpressionItem_FWD_DEFINED__
typedef interface IExpressionItem IExpressionItem;
#endif 	/* __IExpressionItem_FWD_DEFINED__ */


#ifndef __IGenericColl_FWD_DEFINED__
#define __IGenericColl_FWD_DEFINED__
typedef interface IGenericColl IGenericColl;
#endif 	/* __IGenericColl_FWD_DEFINED__ */


#ifndef __IGenericStack_FWD_DEFINED__
#define __IGenericStack_FWD_DEFINED__
typedef interface IGenericStack IGenericStack;
#endif 	/* __IGenericStack_FWD_DEFINED__ */


#ifndef __IGenericStackList_FWD_DEFINED__
#define __IGenericStackList_FWD_DEFINED__
typedef interface IGenericStackList IGenericStackList;
#endif 	/* __IGenericStackList_FWD_DEFINED__ */


#ifndef __ITableIdent_FWD_DEFINED__
#define __ITableIdent_FWD_DEFINED__
typedef interface ITableIdent ITableIdent;
#endif 	/* __ITableIdent_FWD_DEFINED__ */


#ifndef __ITableIdentList_FWD_DEFINED__
#define __ITableIdentList_FWD_DEFINED__
typedef interface ITableIdentList ITableIdentList;
#endif 	/* __ITableIdentList_FWD_DEFINED__ */


#ifndef __IColumnIdent_FWD_DEFINED__
#define __IColumnIdent_FWD_DEFINED__
typedef interface IColumnIdent IColumnIdent;
#endif 	/* __IColumnIdent_FWD_DEFINED__ */


#ifndef __IColumnIdentList_FWD_DEFINED__
#define __IColumnIdentList_FWD_DEFINED__
typedef interface IColumnIdentList IColumnIdentList;
#endif 	/* __IColumnIdentList_FWD_DEFINED__ */


#ifndef __IOrderByObj_FWD_DEFINED__
#define __IOrderByObj_FWD_DEFINED__
typedef interface IOrderByObj IOrderByObj;
#endif 	/* __IOrderByObj_FWD_DEFINED__ */


#ifndef __IOrderByObjList_FWD_DEFINED__
#define __IOrderByObjList_FWD_DEFINED__
typedef interface IOrderByObjList IOrderByObjList;
#endif 	/* __IOrderByObjList_FWD_DEFINED__ */


#ifndef __ICreateTableItem_FWD_DEFINED__
#define __ICreateTableItem_FWD_DEFINED__
typedef interface ICreateTableItem ICreateTableItem;
#endif 	/* __ICreateTableItem_FWD_DEFINED__ */


#ifndef __ICreateTableItemList_FWD_DEFINED__
#define __ICreateTableItemList_FWD_DEFINED__
typedef interface ICreateTableItemList ICreateTableItemList;
#endif 	/* __ICreateTableItemList_FWD_DEFINED__ */


#ifndef __ISelectStmt_FWD_DEFINED__
#define __ISelectStmt_FWD_DEFINED__
typedef interface ISelectStmt ISelectStmt;
#endif 	/* __ISelectStmt_FWD_DEFINED__ */


#ifndef __IUpdateItem_FWD_DEFINED__
#define __IUpdateItem_FWD_DEFINED__
typedef interface IUpdateItem IUpdateItem;
#endif 	/* __IUpdateItem_FWD_DEFINED__ */


#ifndef __IUpdateItemList_FWD_DEFINED__
#define __IUpdateItemList_FWD_DEFINED__
typedef interface IUpdateItemList IUpdateItemList;
#endif 	/* __IUpdateItemList_FWD_DEFINED__ */


#ifndef __IUpdateStmt_FWD_DEFINED__
#define __IUpdateStmt_FWD_DEFINED__
typedef interface IUpdateStmt IUpdateStmt;
#endif 	/* __IUpdateStmt_FWD_DEFINED__ */


#ifndef __ILiteralValue_FWD_DEFINED__
#define __ILiteralValue_FWD_DEFINED__
typedef interface ILiteralValue ILiteralValue;
#endif 	/* __ILiteralValue_FWD_DEFINED__ */


#ifndef __IAggregateFunction_FWD_DEFINED__
#define __IAggregateFunction_FWD_DEFINED__
typedef interface IAggregateFunction IAggregateFunction;
#endif 	/* __IAggregateFunction_FWD_DEFINED__ */


#ifndef __INullExpression_FWD_DEFINED__
#define __INullExpression_FWD_DEFINED__
typedef interface INullExpression INullExpression;
#endif 	/* __INullExpression_FWD_DEFINED__ */


#ifndef __ISelectStarExpression_FWD_DEFINED__
#define __ISelectStarExpression_FWD_DEFINED__
typedef interface ISelectStarExpression ISelectStarExpression;
#endif 	/* __ISelectStarExpression_FWD_DEFINED__ */


#ifndef __IAritOperator_FWD_DEFINED__
#define __IAritOperator_FWD_DEFINED__
typedef interface IAritOperator IAritOperator;
#endif 	/* __IAritOperator_FWD_DEFINED__ */


#ifndef __ICompareOperator_FWD_DEFINED__
#define __ICompareOperator_FWD_DEFINED__
typedef interface ICompareOperator ICompareOperator;
#endif 	/* __ICompareOperator_FWD_DEFINED__ */


#ifndef __IBoolOperator_FWD_DEFINED__
#define __IBoolOperator_FWD_DEFINED__
typedef interface IBoolOperator IBoolOperator;
#endif 	/* __IBoolOperator_FWD_DEFINED__ */


#ifndef __IMathFunction_FWD_DEFINED__
#define __IMathFunction_FWD_DEFINED__
typedef interface IMathFunction IMathFunction;
#endif 	/* __IMathFunction_FWD_DEFINED__ */


#ifndef __IDateFunction_FWD_DEFINED__
#define __IDateFunction_FWD_DEFINED__
typedef interface IDateFunction IDateFunction;
#endif 	/* __IDateFunction_FWD_DEFINED__ */


#ifndef __IInsertStmt_FWD_DEFINED__
#define __IInsertStmt_FWD_DEFINED__
typedef interface IInsertStmt IInsertStmt;
#endif 	/* __IInsertStmt_FWD_DEFINED__ */


#ifndef __IDeleteStmt_FWD_DEFINED__
#define __IDeleteStmt_FWD_DEFINED__
typedef interface IDeleteStmt IDeleteStmt;
#endif 	/* __IDeleteStmt_FWD_DEFINED__ */


#ifndef __ICreateTableStmt_FWD_DEFINED__
#define __ICreateTableStmt_FWD_DEFINED__
typedef interface ICreateTableStmt ICreateTableStmt;
#endif 	/* __ICreateTableStmt_FWD_DEFINED__ */


#ifndef __IDropStmt_FWD_DEFINED__
#define __IDropStmt_FWD_DEFINED__
typedef interface IDropStmt IDropStmt;
#endif 	/* __IDropStmt_FWD_DEFINED__ */


#ifndef __IParser_FWD_DEFINED__
#define __IParser_FWD_DEFINED__
typedef interface IParser IParser;
#endif 	/* __IParser_FWD_DEFINED__ */


#ifndef __Parser_FWD_DEFINED__
#define __Parser_FWD_DEFINED__

#ifdef __cplusplus
typedef class Parser Parser;
#else
typedef struct Parser Parser;
#endif /* __cplusplus */

#endif 	/* __Parser_FWD_DEFINED__ */


#ifndef __SelectStmt_FWD_DEFINED__
#define __SelectStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class SelectStmt SelectStmt;
#else
typedef struct SelectStmt SelectStmt;
#endif /* __cplusplus */

#endif 	/* __SelectStmt_FWD_DEFINED__ */


#ifndef __TableIdent_FWD_DEFINED__
#define __TableIdent_FWD_DEFINED__

#ifdef __cplusplus
typedef class TableIdent TableIdent;
#else
typedef struct TableIdent TableIdent;
#endif /* __cplusplus */

#endif 	/* __TableIdent_FWD_DEFINED__ */


#ifndef __TableIdentList_FWD_DEFINED__
#define __TableIdentList_FWD_DEFINED__

#ifdef __cplusplus
typedef class TableIdentList TableIdentList;
#else
typedef struct TableIdentList TableIdentList;
#endif /* __cplusplus */

#endif 	/* __TableIdentList_FWD_DEFINED__ */


#ifndef __ColumnIdent_FWD_DEFINED__
#define __ColumnIdent_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColumnIdent ColumnIdent;
#else
typedef struct ColumnIdent ColumnIdent;
#endif /* __cplusplus */

#endif 	/* __ColumnIdent_FWD_DEFINED__ */


#ifndef __ColumnIdentList_FWD_DEFINED__
#define __ColumnIdentList_FWD_DEFINED__

#ifdef __cplusplus
typedef class ColumnIdentList ColumnIdentList;
#else
typedef struct ColumnIdentList ColumnIdentList;
#endif /* __cplusplus */

#endif 	/* __ColumnIdentList_FWD_DEFINED__ */


#ifndef __OrderByObj_FWD_DEFINED__
#define __OrderByObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class OrderByObj OrderByObj;
#else
typedef struct OrderByObj OrderByObj;
#endif /* __cplusplus */

#endif 	/* __OrderByObj_FWD_DEFINED__ */


#ifndef __OrderByObjList_FWD_DEFINED__
#define __OrderByObjList_FWD_DEFINED__

#ifdef __cplusplus
typedef class OrderByObjList OrderByObjList;
#else
typedef struct OrderByObjList OrderByObjList;
#endif /* __cplusplus */

#endif 	/* __OrderByObjList_FWD_DEFINED__ */


#ifndef __UpdateStmt_FWD_DEFINED__
#define __UpdateStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class UpdateStmt UpdateStmt;
#else
typedef struct UpdateStmt UpdateStmt;
#endif /* __cplusplus */

#endif 	/* __UpdateStmt_FWD_DEFINED__ */


#ifndef __UpdateItem_FWD_DEFINED__
#define __UpdateItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class UpdateItem UpdateItem;
#else
typedef struct UpdateItem UpdateItem;
#endif /* __cplusplus */

#endif 	/* __UpdateItem_FWD_DEFINED__ */


#ifndef __UpdateItemList_FWD_DEFINED__
#define __UpdateItemList_FWD_DEFINED__

#ifdef __cplusplus
typedef class UpdateItemList UpdateItemList;
#else
typedef struct UpdateItemList UpdateItemList;
#endif /* __cplusplus */

#endif 	/* __UpdateItemList_FWD_DEFINED__ */


#ifndef __GenericColl_FWD_DEFINED__
#define __GenericColl_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericColl GenericColl;
#else
typedef struct GenericColl GenericColl;
#endif /* __cplusplus */

#endif 	/* __GenericColl_FWD_DEFINED__ */


#ifndef __GenericStack_FWD_DEFINED__
#define __GenericStack_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericStack GenericStack;
#else
typedef struct GenericStack GenericStack;
#endif /* __cplusplus */

#endif 	/* __GenericStack_FWD_DEFINED__ */


#ifndef __GenericStackList_FWD_DEFINED__
#define __GenericStackList_FWD_DEFINED__

#ifdef __cplusplus
typedef class GenericStackList GenericStackList;
#else
typedef struct GenericStackList GenericStackList;
#endif /* __cplusplus */

#endif 	/* __GenericStackList_FWD_DEFINED__ */


#ifndef __LiteralValue_FWD_DEFINED__
#define __LiteralValue_FWD_DEFINED__

#ifdef __cplusplus
typedef class LiteralValue LiteralValue;
#else
typedef struct LiteralValue LiteralValue;
#endif /* __cplusplus */

#endif 	/* __LiteralValue_FWD_DEFINED__ */


#ifndef __AggregateFunction_FWD_DEFINED__
#define __AggregateFunction_FWD_DEFINED__

#ifdef __cplusplus
typedef class AggregateFunction AggregateFunction;
#else
typedef struct AggregateFunction AggregateFunction;
#endif /* __cplusplus */

#endif 	/* __AggregateFunction_FWD_DEFINED__ */


#ifndef __NullExpression_FWD_DEFINED__
#define __NullExpression_FWD_DEFINED__

#ifdef __cplusplus
typedef class NullExpression NullExpression;
#else
typedef struct NullExpression NullExpression;
#endif /* __cplusplus */

#endif 	/* __NullExpression_FWD_DEFINED__ */


#ifndef __SelectStarExpression_FWD_DEFINED__
#define __SelectStarExpression_FWD_DEFINED__

#ifdef __cplusplus
typedef class SelectStarExpression SelectStarExpression;
#else
typedef struct SelectStarExpression SelectStarExpression;
#endif /* __cplusplus */

#endif 	/* __SelectStarExpression_FWD_DEFINED__ */


#ifndef __AritOperator_FWD_DEFINED__
#define __AritOperator_FWD_DEFINED__

#ifdef __cplusplus
typedef class AritOperator AritOperator;
#else
typedef struct AritOperator AritOperator;
#endif /* __cplusplus */

#endif 	/* __AritOperator_FWD_DEFINED__ */


#ifndef __CompareOperator_FWD_DEFINED__
#define __CompareOperator_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompareOperator CompareOperator;
#else
typedef struct CompareOperator CompareOperator;
#endif /* __cplusplus */

#endif 	/* __CompareOperator_FWD_DEFINED__ */


#ifndef __BoolOperator_FWD_DEFINED__
#define __BoolOperator_FWD_DEFINED__

#ifdef __cplusplus
typedef class BoolOperator BoolOperator;
#else
typedef struct BoolOperator BoolOperator;
#endif /* __cplusplus */

#endif 	/* __BoolOperator_FWD_DEFINED__ */


#ifndef __MathFunction_FWD_DEFINED__
#define __MathFunction_FWD_DEFINED__

#ifdef __cplusplus
typedef class MathFunction MathFunction;
#else
typedef struct MathFunction MathFunction;
#endif /* __cplusplus */

#endif 	/* __MathFunction_FWD_DEFINED__ */


#ifndef __DateFunction_FWD_DEFINED__
#define __DateFunction_FWD_DEFINED__

#ifdef __cplusplus
typedef class DateFunction DateFunction;
#else
typedef struct DateFunction DateFunction;
#endif /* __cplusplus */

#endif 	/* __DateFunction_FWD_DEFINED__ */


#ifndef __InsertStmt_FWD_DEFINED__
#define __InsertStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class InsertStmt InsertStmt;
#else
typedef struct InsertStmt InsertStmt;
#endif /* __cplusplus */

#endif 	/* __InsertStmt_FWD_DEFINED__ */


#ifndef __DeleteStmt_FWD_DEFINED__
#define __DeleteStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class DeleteStmt DeleteStmt;
#else
typedef struct DeleteStmt DeleteStmt;
#endif /* __cplusplus */

#endif 	/* __DeleteStmt_FWD_DEFINED__ */


#ifndef __CreateTableStmt_FWD_DEFINED__
#define __CreateTableStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class CreateTableStmt CreateTableStmt;
#else
typedef struct CreateTableStmt CreateTableStmt;
#endif /* __cplusplus */

#endif 	/* __CreateTableStmt_FWD_DEFINED__ */


#ifndef __CreateTableItem_FWD_DEFINED__
#define __CreateTableItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class CreateTableItem CreateTableItem;
#else
typedef struct CreateTableItem CreateTableItem;
#endif /* __cplusplus */

#endif 	/* __CreateTableItem_FWD_DEFINED__ */


#ifndef __CreateTableItemList_FWD_DEFINED__
#define __CreateTableItemList_FWD_DEFINED__

#ifdef __cplusplus
typedef class CreateTableItemList CreateTableItemList;
#else
typedef struct CreateTableItemList CreateTableItemList;
#endif /* __cplusplus */

#endif 	/* __CreateTableItemList_FWD_DEFINED__ */


#ifndef __DropStmt_FWD_DEFINED__
#define __DropStmt_FWD_DEFINED__

#ifdef __cplusplus
typedef class DropStmt DropStmt;
#else
typedef struct DropStmt DropStmt;
#endif /* __cplusplus */

#endif 	/* __DropStmt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_TRiASQL_0000 */
/* [local] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0001
    {	STATEMENT_TYPE_UNKNOWN	= 0,
	STATEMENT_TYPE_UPDATE	= STATEMENT_TYPE_UNKNOWN + 1,
	STATEMENT_TYPE_SELECT	= STATEMENT_TYPE_UPDATE + 1,
	STATEMENT_TYPE_INSERT	= STATEMENT_TYPE_SELECT + 1,
	STATEMENT_TYPE_DELETE	= STATEMENT_TYPE_INSERT + 1,
	STATEMENT_TYPE_CREATETABLE	= STATEMENT_TYPE_DELETE + 1,
	STATEMENT_TYPE_DROPTABLE	= STATEMENT_TYPE_CREATETABLE + 1
    }	STATEMENT_TYPE;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0002
    {	EXPRESSIONITEM_TYPE_AGGREGATEFUNCTION	= 0,
	EXPRESSIONITEM_TYPE_SELECTSTAR	= EXPRESSIONITEM_TYPE_AGGREGATEFUNCTION + 1,
	EXPRESSIONITEM_TYPE_COLUMNIDENT	= EXPRESSIONITEM_TYPE_SELECTSTAR + 1,
	EXPRESSIONITEM_TYPE_ARITOPERATOR	= EXPRESSIONITEM_TYPE_COLUMNIDENT + 1,
	EXPRESSIONITEM_TYPE_BOOLOPERATOR	= EXPRESSIONITEM_TYPE_ARITOPERATOR + 1,
	EXPRESSIONITEM_TYPE_COMPAREOPERATOR	= EXPRESSIONITEM_TYPE_BOOLOPERATOR + 1,
	EXPRESSIONITEM_TYPE_DATEFUNCTION	= EXPRESSIONITEM_TYPE_COMPAREOPERATOR + 1,
	EXPRESSIONITEM_TYPE_LITERALVALUE	= EXPRESSIONITEM_TYPE_DATEFUNCTION + 1,
	EXPRESSIONITEM_TYPE_MATHFUNCTION	= EXPRESSIONITEM_TYPE_LITERALVALUE + 1,
	EXPRESSIONITEM_TYPE_NULLEXPRESSION	= EXPRESSIONITEM_TYPE_MATHFUNCTION + 1
    }	EXPRESSIONITEM_TYPE;

typedef /* [public][public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0003
    {	PARSER_DATATYPE_INTEGER	= 0,
	PARSER_DATATYPE_STRING	= PARSER_DATATYPE_INTEGER + 1,
	PARSER_DATATYPE_FLOAT	= PARSER_DATATYPE_STRING + 1
    }	PARSER_DATATYPE;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0004
    {	AGGREGATE_FUNCTION_SUM	= 0,
	AGGREGATE_FUNCTION_COUNT	= AGGREGATE_FUNCTION_SUM + 1,
	AGGREGATE_FUNCTION_MIN	= AGGREGATE_FUNCTION_COUNT + 1,
	AGGREGATE_FUNCTION_MAX	= AGGREGATE_FUNCTION_MIN + 1,
	AGGREGATE_FUNCTION_AVG	= AGGREGATE_FUNCTION_MAX + 1
    }	AGGREGATE_FUNCTION;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0005
    {	ARIT_OPERATOR_PLUS	= 0,
	ARIT_OPERATOR_MINUS	= ARIT_OPERATOR_PLUS + 1,
	ARIT_OPERATOR_DIVIDE	= ARIT_OPERATOR_MINUS + 1,
	ARIT_OPERATOR_MULTIPLY	= ARIT_OPERATOR_DIVIDE + 1
    }	ARIT_OPERATOR;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0006
    {	MATH_FUNCTION_ABS	= 0
    }	MATH_FUNCTION;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0007
    {	BOOL_OPERATOR_AND	= 0,
	BOOL_OPERATOR_OR	= BOOL_OPERATOR_AND + 1
    }	BOOL_OPERATOR;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0008
    {	DATE_FUNCTION_GETDATE	= 0
    }	DATE_FUNCTION;

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_TRiASQL_0000_0009
    {	COMPARE_OPERATOR_EQUALS	= 0,
	COMPARE_OPERATOR_NOT_EQUALS	= COMPARE_OPERATOR_EQUALS + 1,
	COMPARE_OPERATOR_MORE	= COMPARE_OPERATOR_NOT_EQUALS + 1,
	COMPARE_OPERATOR_LESS	= COMPARE_OPERATOR_MORE + 1,
	COMPARE_OPERATOR_MOREEQUALS	= COMPARE_OPERATOR_LESS + 1,
	COMPARE_OPERATOR_LESSEQUALS	= COMPARE_OPERATOR_MOREEQUALS + 1,
	COMPARE_OPERATOR_IS	= COMPARE_OPERATOR_LESSEQUALS + 1,
	COMPARE_OPERATOR_ISNOT	= COMPARE_OPERATOR_IS + 1,
	COMPARE_OPERATOR_NOT	= COMPARE_OPERATOR_ISNOT + 1,
	COMPARE_OPERATOR_LIKE	= COMPARE_OPERATOR_NOT + 1
    }	COMPARE_OPERATOR;



extern RPC_IF_HANDLE __MIDL_itf_TRiASQL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TRiASQL_0000_v0_0_s_ifspec;

#ifndef __IExpressionItem_INTERFACE_DEFINED__
#define __IExpressionItem_INTERFACE_DEFINED__

/* interface IExpressionItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IExpressionItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE771-EC1D-4680-9A37-B5CD0BF0C1BC")
    IExpressionItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AsString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ItemType( 
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IExpressionItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IExpressionItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IExpressionItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IExpressionItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IExpressionItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IExpressionItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IExpressionItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IExpressionItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IExpressionItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IExpressionItem __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        END_INTERFACE
    } IExpressionItemVtbl;

    interface IExpressionItem
    {
        CONST_VTBL struct IExpressionItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IExpressionItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IExpressionItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IExpressionItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IExpressionItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IExpressionItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IExpressionItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IExpressionItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IExpressionItem_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IExpressionItem_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExpressionItem_get_AsString_Proxy( 
    IExpressionItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IExpressionItem_get_AsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IExpressionItem_get_ItemType_Proxy( 
    IExpressionItem __RPC_FAR * This,
    /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);


void __RPC_STUB IExpressionItem_get_ItemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IExpressionItem_INTERFACE_DEFINED__ */


#ifndef __IGenericColl_INTERFACE_DEFINED__
#define __IGenericColl_INTERFACE_DEFINED__

/* interface IGenericColl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGenericColl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE772-EC1D-4680-9A37-B5CD0BF0C1BC")
    IGenericColl : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGenericCollVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGenericColl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGenericColl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGenericColl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGenericColl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGenericColl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGenericColl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGenericColl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IGenericColl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IGenericColl __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IGenericColl __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IGenericCollVtbl;

    interface IGenericColl
    {
        CONST_VTBL struct IGenericCollVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericColl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGenericColl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGenericColl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGenericColl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGenericColl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGenericColl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGenericColl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGenericColl_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IGenericColl_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IGenericColl_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericColl_get_Count_Proxy( 
    IGenericColl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IGenericColl_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericColl_get__NewEnum_Proxy( 
    IGenericColl __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IGenericColl_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericColl_get_Item_Proxy( 
    IGenericColl __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IGenericColl_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGenericColl_INTERFACE_DEFINED__ */


#ifndef __IGenericStack_INTERFACE_DEFINED__
#define __IGenericStack_INTERFACE_DEFINED__

/* interface IGenericStack */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGenericStack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE773-EC1D-4680-9A37-B5CD0BF0C1BC")
    IGenericStack : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Push( 
            VARIANT vObject) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pop( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Peek( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvObj) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AsName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGenericStackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGenericStack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGenericStack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGenericStack __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGenericStack __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGenericStack __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGenericStack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGenericStack __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IGenericStack __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Push )( 
            IGenericStack __RPC_FAR * This,
            VARIANT vObject);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pop )( 
            IGenericStack __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Peek )( 
            IGenericStack __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvObj);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsName )( 
            IGenericStack __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IGenericStack __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IGenericStack __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IGenericStackVtbl;

    interface IGenericStack
    {
        CONST_VTBL struct IGenericStackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericStack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGenericStack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGenericStack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGenericStack_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGenericStack_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGenericStack_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGenericStack_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGenericStack_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IGenericStack_Push(This,vObject)	\
    (This)->lpVtbl -> Push(This,vObject)

#define IGenericStack_Pop(This,pvObj)	\
    (This)->lpVtbl -> Pop(This,pvObj)

#define IGenericStack_Peek(This,pvObj)	\
    (This)->lpVtbl -> Peek(This,pvObj)

#define IGenericStack_get_AsName(This,pVal)	\
    (This)->lpVtbl -> get_AsName(This,pVal)

#define IGenericStack_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IGenericStack_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStack_get_Count_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IGenericStack_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStack_Push_Proxy( 
    IGenericStack __RPC_FAR * This,
    VARIANT vObject);


void __RPC_STUB IGenericStack_Push_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStack_Pop_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvObj);


void __RPC_STUB IGenericStack_Pop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IGenericStack_Peek_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvObj);


void __RPC_STUB IGenericStack_Peek_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStack_get_AsName_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IGenericStack_get_AsName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStack_get__NewEnum_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IGenericStack_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStack_get_Item_Proxy( 
    IGenericStack __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IGenericStack_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGenericStack_INTERFACE_DEFINED__ */


#ifndef __IGenericStackList_INTERFACE_DEFINED__
#define __IGenericStackList_INTERFACE_DEFINED__

/* interface IGenericStackList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IGenericStackList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE774-EC1D-4680-9A37-B5CD0BF0C1BC")
    IGenericStackList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGenericStackListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGenericStackList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGenericStackList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGenericStackList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IGenericStackList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IGenericStackList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IGenericStackList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IGenericStackList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IGenericStackList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IGenericStackList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IGenericStackList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IGenericStackListVtbl;

    interface IGenericStackList
    {
        CONST_VTBL struct IGenericStackListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGenericStackList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGenericStackList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGenericStackList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGenericStackList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IGenericStackList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IGenericStackList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IGenericStackList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IGenericStackList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IGenericStackList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IGenericStackList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStackList_get_Count_Proxy( 
    IGenericStackList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IGenericStackList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStackList_get__NewEnum_Proxy( 
    IGenericStackList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IGenericStackList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IGenericStackList_get_Item_Proxy( 
    IGenericStackList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IGenericStackList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGenericStackList_INTERFACE_DEFINED__ */


#ifndef __ITableIdent_INTERFACE_DEFINED__
#define __ITableIdent_INTERFACE_DEFINED__

/* interface ITableIdent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITableIdent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE775-EC1D-4680-9A37-B5CD0BF0C1BC")
    ITableIdent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITableIdentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITableIdent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITableIdent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITableIdent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITableIdent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITableIdent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITableIdent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITableIdent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITableIdent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } ITableIdentVtbl;

    interface ITableIdent
    {
        CONST_VTBL struct ITableIdentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITableIdent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITableIdent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITableIdent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITableIdent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITableIdent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITableIdent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITableIdent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITableIdent_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITableIdent_get_Name_Proxy( 
    ITableIdent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITableIdent_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITableIdent_INTERFACE_DEFINED__ */


#ifndef __ITableIdentList_INTERFACE_DEFINED__
#define __ITableIdentList_INTERFACE_DEFINED__

/* interface ITableIdentList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITableIdentList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE776-EC1D-4680-9A37-B5CD0BF0C1BC")
    ITableIdentList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITableIdentListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITableIdentList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITableIdentList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITableIdentList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITableIdentList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITableIdentList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITableIdentList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITableIdentList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITableIdentList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ITableIdentList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITableIdentList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } ITableIdentListVtbl;

    interface ITableIdentList
    {
        CONST_VTBL struct ITableIdentListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITableIdentList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITableIdentList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITableIdentList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITableIdentList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITableIdentList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITableIdentList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITableIdentList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITableIdentList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITableIdentList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ITableIdentList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITableIdentList_get_Count_Proxy( 
    ITableIdentList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITableIdentList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITableIdentList_get__NewEnum_Proxy( 
    ITableIdentList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB ITableIdentList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITableIdentList_get_Item_Proxy( 
    ITableIdentList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB ITableIdentList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITableIdentList_INTERFACE_DEFINED__ */


#ifndef __IColumnIdent_INTERFACE_DEFINED__
#define __IColumnIdent_INTERFACE_DEFINED__

/* interface IColumnIdent */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IColumnIdent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE777-EC1D-4680-9A37-B5CD0BF0C1BC")
    IColumnIdent : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColumnIdentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColumnIdent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColumnIdent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColumnIdent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IColumnIdent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IColumnIdent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IColumnIdent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IColumnIdent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IColumnIdent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IColumnIdent __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableName )( 
            IColumnIdent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnName )( 
            IColumnIdent __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IColumnIdentVtbl;

    interface IColumnIdent
    {
        CONST_VTBL struct IColumnIdentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnIdent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColumnIdent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColumnIdent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColumnIdent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IColumnIdent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IColumnIdent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IColumnIdent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IColumnIdent_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IColumnIdent_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IColumnIdent_get_TableName(This,pVal)	\
    (This)->lpVtbl -> get_TableName(This,pVal)

#define IColumnIdent_get_ColumnName(This,pVal)	\
    (This)->lpVtbl -> get_ColumnName(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColumnIdent_get_TableName_Proxy( 
    IColumnIdent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IColumnIdent_get_TableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColumnIdent_get_ColumnName_Proxy( 
    IColumnIdent __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IColumnIdent_get_ColumnName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColumnIdent_INTERFACE_DEFINED__ */


#ifndef __IColumnIdentList_INTERFACE_DEFINED__
#define __IColumnIdentList_INTERFACE_DEFINED__

/* interface IColumnIdentList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IColumnIdentList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE778-EC1D-4680-9A37-B5CD0BF0C1BC")
    IColumnIdentList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IColumnIdentListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IColumnIdentList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IColumnIdentList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IColumnIdentList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IColumnIdentList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IColumnIdentList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IColumnIdentList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IColumnIdentList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IColumnIdentList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IColumnIdentList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IColumnIdentList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IColumnIdentListVtbl;

    interface IColumnIdentList
    {
        CONST_VTBL struct IColumnIdentListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IColumnIdentList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IColumnIdentList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IColumnIdentList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IColumnIdentList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IColumnIdentList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IColumnIdentList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IColumnIdentList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IColumnIdentList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IColumnIdentList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IColumnIdentList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColumnIdentList_get_Count_Proxy( 
    IColumnIdentList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IColumnIdentList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColumnIdentList_get__NewEnum_Proxy( 
    IColumnIdentList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IColumnIdentList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IColumnIdentList_get_Item_Proxy( 
    IColumnIdentList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IColumnIdentList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IColumnIdentList_INTERFACE_DEFINED__ */


#ifndef __IOrderByObj_INTERFACE_DEFINED__
#define __IOrderByObj_INTERFACE_DEFINED__

/* interface IOrderByObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IOrderByObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE779-EC1D-4680-9A37-B5CD0BF0C1BC")
    IOrderByObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Asc( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnIdent( 
            /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOrderByObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOrderByObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOrderByObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOrderByObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IOrderByObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IOrderByObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IOrderByObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IOrderByObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Asc )( 
            IOrderByObj __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnIdent )( 
            IOrderByObj __RPC_FAR * This,
            /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IOrderByObjVtbl;

    interface IOrderByObj
    {
        CONST_VTBL struct IOrderByObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOrderByObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOrderByObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOrderByObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOrderByObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IOrderByObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IOrderByObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IOrderByObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IOrderByObj_get_Asc(This,pVal)	\
    (This)->lpVtbl -> get_Asc(This,pVal)

#define IOrderByObj_get_ColumnIdent(This,pVal)	\
    (This)->lpVtbl -> get_ColumnIdent(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOrderByObj_get_Asc_Proxy( 
    IOrderByObj __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IOrderByObj_get_Asc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOrderByObj_get_ColumnIdent_Proxy( 
    IOrderByObj __RPC_FAR * This,
    /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IOrderByObj_get_ColumnIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOrderByObj_INTERFACE_DEFINED__ */


#ifndef __IOrderByObjList_INTERFACE_DEFINED__
#define __IOrderByObjList_INTERFACE_DEFINED__

/* interface IOrderByObjList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IOrderByObjList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77A-EC1D-4680-9A37-B5CD0BF0C1BC")
    IOrderByObjList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOrderByObjListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOrderByObjList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOrderByObjList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOrderByObjList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IOrderByObjList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IOrderByObjList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IOrderByObjList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IOrderByObjList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IOrderByObjList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IOrderByObjList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IOrderByObjList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IOrderByObjListVtbl;

    interface IOrderByObjList
    {
        CONST_VTBL struct IOrderByObjListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOrderByObjList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOrderByObjList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOrderByObjList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOrderByObjList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IOrderByObjList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IOrderByObjList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IOrderByObjList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IOrderByObjList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IOrderByObjList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IOrderByObjList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOrderByObjList_get_Count_Proxy( 
    IOrderByObjList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IOrderByObjList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOrderByObjList_get__NewEnum_Proxy( 
    IOrderByObjList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IOrderByObjList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IOrderByObjList_get_Item_Proxy( 
    IOrderByObjList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IOrderByObjList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOrderByObjList_INTERFACE_DEFINED__ */


#ifndef __ICreateTableItem_INTERFACE_DEFINED__
#define __ICreateTableItem_INTERFACE_DEFINED__

/* interface ICreateTableItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICreateTableItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77B-EC1D-4680-9A37-B5CD0BF0C1BC")
    ICreateTableItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataLength( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataType( 
            /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateTableItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICreateTableItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICreateTableItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICreateTableItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICreateTableItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICreateTableItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICreateTableItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICreateTableItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DataLength )( 
            ICreateTableItem __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColName )( 
            ICreateTableItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DataType )( 
            ICreateTableItem __RPC_FAR * This,
            /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal);
        
        END_INTERFACE
    } ICreateTableItemVtbl;

    interface ICreateTableItem
    {
        CONST_VTBL struct ICreateTableItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateTableItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateTableItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateTableItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateTableItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICreateTableItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICreateTableItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICreateTableItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICreateTableItem_get_DataLength(This,pVal)	\
    (This)->lpVtbl -> get_DataLength(This,pVal)

#define ICreateTableItem_get_ColName(This,pVal)	\
    (This)->lpVtbl -> get_ColName(This,pVal)

#define ICreateTableItem_get_DataType(This,pVal)	\
    (This)->lpVtbl -> get_DataType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItem_get_DataLength_Proxy( 
    ICreateTableItem __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ICreateTableItem_get_DataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItem_get_ColName_Proxy( 
    ICreateTableItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ICreateTableItem_get_ColName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItem_get_DataType_Proxy( 
    ICreateTableItem __RPC_FAR * This,
    /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal);


void __RPC_STUB ICreateTableItem_get_DataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICreateTableItem_INTERFACE_DEFINED__ */


#ifndef __ICreateTableItemList_INTERFACE_DEFINED__
#define __ICreateTableItemList_INTERFACE_DEFINED__

/* interface ICreateTableItemList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICreateTableItemList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77C-EC1D-4680-9A37-B5CD0BF0C1BC")
    ICreateTableItemList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateTableItemListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICreateTableItemList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICreateTableItemList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ICreateTableItemList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } ICreateTableItemListVtbl;

    interface ICreateTableItemList
    {
        CONST_VTBL struct ICreateTableItemListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateTableItemList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateTableItemList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateTableItemList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateTableItemList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICreateTableItemList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICreateTableItemList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICreateTableItemList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICreateTableItemList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ICreateTableItemList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ICreateTableItemList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItemList_get_Count_Proxy( 
    ICreateTableItemList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ICreateTableItemList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItemList_get__NewEnum_Proxy( 
    ICreateTableItemList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB ICreateTableItemList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableItemList_get_Item_Proxy( 
    ICreateTableItemList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB ICreateTableItemList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICreateTableItemList_INTERFACE_DEFINED__ */


#ifndef __ISelectStmt_INTERFACE_DEFINED__
#define __ISelectStmt_INTERFACE_DEFINED__

/* interface ISelectStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISelectStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77D-EC1D-4680-9A37-B5CD0BF0C1BC")
    ISelectStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Distinct( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdentList( 
            /* [retval][out] */ ITableIdentList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrderByObjList( 
            /* [retval][out] */ IOrderByObjList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhereExpressionStack( 
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectExpressionList( 
            /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HavingExpressionStack( 
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupByObjList( 
            /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISelectStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISelectStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISelectStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISelectStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISelectStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISelectStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISelectStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISelectStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Distinct )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdentList )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdentList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OrderByObjList )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ IOrderByObjList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhereExpressionStack )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectExpressionList )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HavingExpressionStack )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GroupByObjList )( 
            ISelectStmt __RPC_FAR * This,
            /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } ISelectStmtVtbl;

    interface ISelectStmt
    {
        CONST_VTBL struct ISelectStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISelectStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISelectStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISelectStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISelectStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISelectStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISelectStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISelectStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISelectStmt_get_Distinct(This,pVal)	\
    (This)->lpVtbl -> get_Distinct(This,pVal)

#define ISelectStmt_get_TableIdentList(This,pVal)	\
    (This)->lpVtbl -> get_TableIdentList(This,pVal)

#define ISelectStmt_get_OrderByObjList(This,pVal)	\
    (This)->lpVtbl -> get_OrderByObjList(This,pVal)

#define ISelectStmt_get_WhereExpressionStack(This,pVal)	\
    (This)->lpVtbl -> get_WhereExpressionStack(This,pVal)

#define ISelectStmt_get_SelectExpressionList(This,pVal)	\
    (This)->lpVtbl -> get_SelectExpressionList(This,pVal)

#define ISelectStmt_get_HavingExpressionStack(This,pVal)	\
    (This)->lpVtbl -> get_HavingExpressionStack(This,pVal)

#define ISelectStmt_get_GroupByObjList(This,pVal)	\
    (This)->lpVtbl -> get_GroupByObjList(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_Distinct_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_Distinct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_TableIdentList_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdentList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_TableIdentList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_OrderByObjList_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ IOrderByObjList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_OrderByObjList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_WhereExpressionStack_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_WhereExpressionStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_SelectExpressionList_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_SelectExpressionList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_HavingExpressionStack_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_HavingExpressionStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISelectStmt_get_GroupByObjList_Proxy( 
    ISelectStmt __RPC_FAR * This,
    /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ISelectStmt_get_GroupByObjList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISelectStmt_INTERFACE_DEFINED__ */


#ifndef __IUpdateItem_INTERFACE_DEFINED__
#define __IUpdateItem_INTERFACE_DEFINED__

/* interface IUpdateItem */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUpdateItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77E-EC1D-4680-9A37-B5CD0BF0C1BC")
    IUpdateItem : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnIdent( 
            /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpressionStack( 
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUpdateItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUpdateItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUpdateItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUpdateItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUpdateItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUpdateItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUpdateItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUpdateItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnIdent )( 
            IUpdateItem __RPC_FAR * This,
            /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpressionStack )( 
            IUpdateItem __RPC_FAR * This,
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IUpdateItemVtbl;

    interface IUpdateItem
    {
        CONST_VTBL struct IUpdateItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUpdateItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUpdateItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUpdateItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUpdateItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUpdateItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUpdateItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUpdateItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUpdateItem_get_ColumnIdent(This,pVal)	\
    (This)->lpVtbl -> get_ColumnIdent(This,pVal)

#define IUpdateItem_get_ExpressionStack(This,pVal)	\
    (This)->lpVtbl -> get_ExpressionStack(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateItem_get_ColumnIdent_Proxy( 
    IUpdateItem __RPC_FAR * This,
    /* [retval][out] */ IColumnIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IUpdateItem_get_ColumnIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateItem_get_ExpressionStack_Proxy( 
    IUpdateItem __RPC_FAR * This,
    /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IUpdateItem_get_ExpressionStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUpdateItem_INTERFACE_DEFINED__ */


#ifndef __IUpdateItemList_INTERFACE_DEFINED__
#define __IUpdateItemList_INTERFACE_DEFINED__

/* interface IUpdateItemList */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUpdateItemList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE77F-EC1D-4680-9A37-B5CD0BF0C1BC")
    IUpdateItemList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUpdateItemListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUpdateItemList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUpdateItemList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUpdateItemList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUpdateItemList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUpdateItemList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUpdateItemList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUpdateItemList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IUpdateItemList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IUpdateItemList __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IUpdateItemList __RPC_FAR * This,
            /* [in] */ long varIndex,
            /* [retval][out] */ VARIANT __RPC_FAR *ppBook);
        
        END_INTERFACE
    } IUpdateItemListVtbl;

    interface IUpdateItemList
    {
        CONST_VTBL struct IUpdateItemListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUpdateItemList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUpdateItemList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUpdateItemList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUpdateItemList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUpdateItemList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUpdateItemList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUpdateItemList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUpdateItemList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IUpdateItemList_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IUpdateItemList_get_Item(This,varIndex,ppBook)	\
    (This)->lpVtbl -> get_Item(This,varIndex,ppBook)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateItemList_get_Count_Proxy( 
    IUpdateItemList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IUpdateItemList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateItemList_get__NewEnum_Proxy( 
    IUpdateItemList __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IUpdateItemList_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateItemList_get_Item_Proxy( 
    IUpdateItemList __RPC_FAR * This,
    /* [in] */ long varIndex,
    /* [retval][out] */ VARIANT __RPC_FAR *ppBook);


void __RPC_STUB IUpdateItemList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUpdateItemList_INTERFACE_DEFINED__ */


#ifndef __IUpdateStmt_INTERFACE_DEFINED__
#define __IUpdateStmt_INTERFACE_DEFINED__

/* interface IUpdateStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUpdateStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE780-EC1D-4680-9A37-B5CD0BF0C1BC")
    IUpdateStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdent( 
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpdateItemList( 
            /* [retval][out] */ IUpdateItemList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhereExpressionStack( 
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUpdateStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUpdateStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUpdateStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUpdateStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUpdateStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUpdateStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUpdateStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUpdateStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdent )( 
            IUpdateStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpdateItemList )( 
            IUpdateStmt __RPC_FAR * This,
            /* [retval][out] */ IUpdateItemList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhereExpressionStack )( 
            IUpdateStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IUpdateStmtVtbl;

    interface IUpdateStmt
    {
        CONST_VTBL struct IUpdateStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUpdateStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUpdateStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUpdateStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUpdateStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUpdateStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUpdateStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUpdateStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUpdateStmt_get_TableIdent(This,pVal)	\
    (This)->lpVtbl -> get_TableIdent(This,pVal)

#define IUpdateStmt_get_UpdateItemList(This,pVal)	\
    (This)->lpVtbl -> get_UpdateItemList(This,pVal)

#define IUpdateStmt_get_WhereExpressionStack(This,pVal)	\
    (This)->lpVtbl -> get_WhereExpressionStack(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateStmt_get_TableIdent_Proxy( 
    IUpdateStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IUpdateStmt_get_TableIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateStmt_get_UpdateItemList_Proxy( 
    IUpdateStmt __RPC_FAR * This,
    /* [retval][out] */ IUpdateItemList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IUpdateStmt_get_UpdateItemList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUpdateStmt_get_WhereExpressionStack_Proxy( 
    IUpdateStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IUpdateStmt_get_WhereExpressionStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUpdateStmt_INTERFACE_DEFINED__ */


#ifndef __ILiteralValue_INTERFACE_DEFINED__
#define __ILiteralValue_INTERFACE_DEFINED__

/* interface ILiteralValue */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ILiteralValue;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE781-EC1D-4680-9A37-B5CD0BF0C1BC")
    ILiteralValue : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataType( 
            /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILiteralValueVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILiteralValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILiteralValue __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILiteralValue __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ILiteralValue __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ILiteralValue __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ILiteralValue __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ILiteralValue __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            ILiteralValue __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            ILiteralValue __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DataType )( 
            ILiteralValue __RPC_FAR * This,
            /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal);
        
        END_INTERFACE
    } ILiteralValueVtbl;

    interface ILiteralValue
    {
        CONST_VTBL struct ILiteralValueVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILiteralValue_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILiteralValue_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILiteralValue_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILiteralValue_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ILiteralValue_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ILiteralValue_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ILiteralValue_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ILiteralValue_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define ILiteralValue_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define ILiteralValue_get_DataType(This,pVal)	\
    (This)->lpVtbl -> get_DataType(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ILiteralValue_get_DataType_Proxy( 
    ILiteralValue __RPC_FAR * This,
    /* [retval][out] */ PARSER_DATATYPE __RPC_FAR *pVal);


void __RPC_STUB ILiteralValue_get_DataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILiteralValue_INTERFACE_DEFINED__ */


#ifndef __IAggregateFunction_INTERFACE_DEFINED__
#define __IAggregateFunction_INTERFACE_DEFINED__

/* interface IAggregateFunction */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAggregateFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE782-EC1D-4680-9A37-B5CD0BF0C1BC")
    IAggregateFunction : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AggregateFunction( 
            /* [retval][out] */ AGGREGATE_FUNCTION __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAggregateFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAggregateFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAggregateFunction __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAggregateFunction __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAggregateFunction __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAggregateFunction __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAggregateFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAggregateFunction __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IAggregateFunction __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IAggregateFunction __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AggregateFunction )( 
            IAggregateFunction __RPC_FAR * This,
            /* [retval][out] */ AGGREGATE_FUNCTION __RPC_FAR *pVal);
        
        END_INTERFACE
    } IAggregateFunctionVtbl;

    interface IAggregateFunction
    {
        CONST_VTBL struct IAggregateFunctionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAggregateFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAggregateFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAggregateFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAggregateFunction_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAggregateFunction_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAggregateFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAggregateFunction_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAggregateFunction_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IAggregateFunction_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IAggregateFunction_get_AggregateFunction(This,pVal)	\
    (This)->lpVtbl -> get_AggregateFunction(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAggregateFunction_get_AggregateFunction_Proxy( 
    IAggregateFunction __RPC_FAR * This,
    /* [retval][out] */ AGGREGATE_FUNCTION __RPC_FAR *pVal);


void __RPC_STUB IAggregateFunction_get_AggregateFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAggregateFunction_INTERFACE_DEFINED__ */


#ifndef __INullExpression_INTERFACE_DEFINED__
#define __INullExpression_INTERFACE_DEFINED__

/* interface INullExpression */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INullExpression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE783-EC1D-4680-9A37-B5CD0BF0C1BC")
    INullExpression : public IExpressionItem
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct INullExpressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INullExpression __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INullExpression __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INullExpression __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INullExpression __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INullExpression __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INullExpression __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INullExpression __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            INullExpression __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            INullExpression __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        END_INTERFACE
    } INullExpressionVtbl;

    interface INullExpression
    {
        CONST_VTBL struct INullExpressionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INullExpression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INullExpression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INullExpression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INullExpression_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INullExpression_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INullExpression_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INullExpression_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INullExpression_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define INullExpression_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INullExpression_INTERFACE_DEFINED__ */


#ifndef __ISelectStarExpression_INTERFACE_DEFINED__
#define __ISelectStarExpression_INTERFACE_DEFINED__

/* interface ISelectStarExpression */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISelectStarExpression;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE784-EC1D-4680-9A37-B5CD0BF0C1BC")
    ISelectStarExpression : public IExpressionItem
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISelectStarExpressionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISelectStarExpression __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISelectStarExpression __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            ISelectStarExpression __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        END_INTERFACE
    } ISelectStarExpressionVtbl;

    interface ISelectStarExpression
    {
        CONST_VTBL struct ISelectStarExpressionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISelectStarExpression_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISelectStarExpression_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISelectStarExpression_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISelectStarExpression_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISelectStarExpression_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISelectStarExpression_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISelectStarExpression_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISelectStarExpression_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define ISelectStarExpression_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISelectStarExpression_INTERFACE_DEFINED__ */


#ifndef __IAritOperator_INTERFACE_DEFINED__
#define __IAritOperator_INTERFACE_DEFINED__

/* interface IAritOperator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAritOperator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE785-EC1D-4680-9A37-B5CD0BF0C1BC")
    IAritOperator : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AritOperator( 
            /* [retval][out] */ ARIT_OPERATOR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAritOperatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAritOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAritOperator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAritOperator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAritOperator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAritOperator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAritOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAritOperator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IAritOperator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IAritOperator __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AritOperator )( 
            IAritOperator __RPC_FAR * This,
            /* [retval][out] */ ARIT_OPERATOR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IAritOperatorVtbl;

    interface IAritOperator
    {
        CONST_VTBL struct IAritOperatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAritOperator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAritOperator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAritOperator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAritOperator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAritOperator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAritOperator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAritOperator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAritOperator_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IAritOperator_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IAritOperator_get_AritOperator(This,pVal)	\
    (This)->lpVtbl -> get_AritOperator(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAritOperator_get_AritOperator_Proxy( 
    IAritOperator __RPC_FAR * This,
    /* [retval][out] */ ARIT_OPERATOR __RPC_FAR *pVal);


void __RPC_STUB IAritOperator_get_AritOperator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAritOperator_INTERFACE_DEFINED__ */


#ifndef __ICompareOperator_INTERFACE_DEFINED__
#define __ICompareOperator_INTERFACE_DEFINED__

/* interface ICompareOperator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICompareOperator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE786-EC1D-4680-9A37-B5CD0BF0C1BC")
    ICompareOperator : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CompareOperator( 
            /* [retval][out] */ COMPARE_OPERATOR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICompareOperatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICompareOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICompareOperator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICompareOperator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICompareOperator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICompareOperator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICompareOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICompareOperator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            ICompareOperator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            ICompareOperator __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CompareOperator )( 
            ICompareOperator __RPC_FAR * This,
            /* [retval][out] */ COMPARE_OPERATOR __RPC_FAR *pVal);
        
        END_INTERFACE
    } ICompareOperatorVtbl;

    interface ICompareOperator
    {
        CONST_VTBL struct ICompareOperatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICompareOperator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICompareOperator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICompareOperator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICompareOperator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICompareOperator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICompareOperator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICompareOperator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICompareOperator_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define ICompareOperator_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define ICompareOperator_get_CompareOperator(This,pVal)	\
    (This)->lpVtbl -> get_CompareOperator(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICompareOperator_get_CompareOperator_Proxy( 
    ICompareOperator __RPC_FAR * This,
    /* [retval][out] */ COMPARE_OPERATOR __RPC_FAR *pVal);


void __RPC_STUB ICompareOperator_get_CompareOperator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICompareOperator_INTERFACE_DEFINED__ */


#ifndef __IBoolOperator_INTERFACE_DEFINED__
#define __IBoolOperator_INTERFACE_DEFINED__

/* interface IBoolOperator */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IBoolOperator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE787-EC1D-4680-9A37-B5CD0BF0C1BC")
    IBoolOperator : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BoolOperator( 
            /* [retval][out] */ BOOL_OPERATOR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBoolOperatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBoolOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBoolOperator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBoolOperator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBoolOperator __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBoolOperator __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBoolOperator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBoolOperator __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IBoolOperator __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IBoolOperator __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BoolOperator )( 
            IBoolOperator __RPC_FAR * This,
            /* [retval][out] */ BOOL_OPERATOR __RPC_FAR *pVal);
        
        END_INTERFACE
    } IBoolOperatorVtbl;

    interface IBoolOperator
    {
        CONST_VTBL struct IBoolOperatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBoolOperator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBoolOperator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBoolOperator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBoolOperator_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBoolOperator_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBoolOperator_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBoolOperator_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBoolOperator_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IBoolOperator_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IBoolOperator_get_BoolOperator(This,pVal)	\
    (This)->lpVtbl -> get_BoolOperator(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IBoolOperator_get_BoolOperator_Proxy( 
    IBoolOperator __RPC_FAR * This,
    /* [retval][out] */ BOOL_OPERATOR __RPC_FAR *pVal);


void __RPC_STUB IBoolOperator_get_BoolOperator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBoolOperator_INTERFACE_DEFINED__ */


#ifndef __IMathFunction_INTERFACE_DEFINED__
#define __IMathFunction_INTERFACE_DEFINED__

/* interface IMathFunction */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMathFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE788-EC1D-4680-9A37-B5CD0BF0C1BC")
    IMathFunction : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MathFunction( 
            /* [retval][out] */ MATH_FUNCTION __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMathFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMathFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMathFunction __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMathFunction __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMathFunction __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMathFunction __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMathFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMathFunction __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IMathFunction __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IMathFunction __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MathFunction )( 
            IMathFunction __RPC_FAR * This,
            /* [retval][out] */ MATH_FUNCTION __RPC_FAR *pVal);
        
        END_INTERFACE
    } IMathFunctionVtbl;

    interface IMathFunction
    {
        CONST_VTBL struct IMathFunctionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMathFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMathFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMathFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMathFunction_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMathFunction_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMathFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMathFunction_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMathFunction_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IMathFunction_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IMathFunction_get_MathFunction(This,pVal)	\
    (This)->lpVtbl -> get_MathFunction(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMathFunction_get_MathFunction_Proxy( 
    IMathFunction __RPC_FAR * This,
    /* [retval][out] */ MATH_FUNCTION __RPC_FAR *pVal);


void __RPC_STUB IMathFunction_get_MathFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMathFunction_INTERFACE_DEFINED__ */


#ifndef __IDateFunction_INTERFACE_DEFINED__
#define __IDateFunction_INTERFACE_DEFINED__

/* interface IDateFunction */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDateFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE789-EC1D-4680-9A37-B5CD0BF0C1BC")
    IDateFunction : public IExpressionItem
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DateFunction( 
            /* [retval][out] */ DATE_FUNCTION __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDateFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDateFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDateFunction __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDateFunction __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDateFunction __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDateFunction __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDateFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDateFunction __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            IDateFunction __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ItemType )( 
            IDateFunction __RPC_FAR * This,
            /* [retval][out] */ EXPRESSIONITEM_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DateFunction )( 
            IDateFunction __RPC_FAR * This,
            /* [retval][out] */ DATE_FUNCTION __RPC_FAR *pVal);
        
        END_INTERFACE
    } IDateFunctionVtbl;

    interface IDateFunction
    {
        CONST_VTBL struct IDateFunctionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDateFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDateFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDateFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDateFunction_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDateFunction_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDateFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDateFunction_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDateFunction_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define IDateFunction_get_ItemType(This,pVal)	\
    (This)->lpVtbl -> get_ItemType(This,pVal)


#define IDateFunction_get_DateFunction(This,pVal)	\
    (This)->lpVtbl -> get_DateFunction(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDateFunction_get_DateFunction_Proxy( 
    IDateFunction __RPC_FAR * This,
    /* [retval][out] */ DATE_FUNCTION __RPC_FAR *pVal);


void __RPC_STUB IDateFunction_get_DateFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDateFunction_INTERFACE_DEFINED__ */


#ifndef __IInsertStmt_INTERFACE_DEFINED__
#define __IInsertStmt_INTERFACE_DEFINED__

/* interface IInsertStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IInsertStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE78A-EC1D-4680-9A37-B5CD0BF0C1BC")
    IInsertStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdent( 
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ColumnIdentList( 
            /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InsertExpressionList( 
            /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInsertStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInsertStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInsertStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInsertStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IInsertStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IInsertStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IInsertStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IInsertStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdent )( 
            IInsertStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ColumnIdentList )( 
            IInsertStmt __RPC_FAR * This,
            /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InsertExpressionList )( 
            IInsertStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IInsertStmtVtbl;

    interface IInsertStmt
    {
        CONST_VTBL struct IInsertStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInsertStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInsertStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInsertStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInsertStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IInsertStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IInsertStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IInsertStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IInsertStmt_get_TableIdent(This,pVal)	\
    (This)->lpVtbl -> get_TableIdent(This,pVal)

#define IInsertStmt_get_ColumnIdentList(This,pVal)	\
    (This)->lpVtbl -> get_ColumnIdentList(This,pVal)

#define IInsertStmt_get_InsertExpressionList(This,pVal)	\
    (This)->lpVtbl -> get_InsertExpressionList(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInsertStmt_get_TableIdent_Proxy( 
    IInsertStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IInsertStmt_get_TableIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInsertStmt_get_ColumnIdentList_Proxy( 
    IInsertStmt __RPC_FAR * This,
    /* [retval][out] */ IColumnIdentList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IInsertStmt_get_ColumnIdentList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IInsertStmt_get_InsertExpressionList_Proxy( 
    IInsertStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStackList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IInsertStmt_get_InsertExpressionList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IInsertStmt_INTERFACE_DEFINED__ */


#ifndef __IDeleteStmt_INTERFACE_DEFINED__
#define __IDeleteStmt_INTERFACE_DEFINED__

/* interface IDeleteStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDeleteStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE78B-EC1D-4680-9A37-B5CD0BF0C1BC")
    IDeleteStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdent( 
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WhereExpressionStack( 
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDeleteStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDeleteStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDeleteStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDeleteStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDeleteStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDeleteStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDeleteStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDeleteStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdent )( 
            IDeleteStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WhereExpressionStack )( 
            IDeleteStmt __RPC_FAR * This,
            /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IDeleteStmtVtbl;

    interface IDeleteStmt
    {
        CONST_VTBL struct IDeleteStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDeleteStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDeleteStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDeleteStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDeleteStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDeleteStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDeleteStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDeleteStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDeleteStmt_get_TableIdent(This,pVal)	\
    (This)->lpVtbl -> get_TableIdent(This,pVal)

#define IDeleteStmt_get_WhereExpressionStack(This,pVal)	\
    (This)->lpVtbl -> get_WhereExpressionStack(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDeleteStmt_get_TableIdent_Proxy( 
    IDeleteStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IDeleteStmt_get_TableIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDeleteStmt_get_WhereExpressionStack_Proxy( 
    IDeleteStmt __RPC_FAR * This,
    /* [retval][out] */ IGenericStack __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IDeleteStmt_get_WhereExpressionStack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDeleteStmt_INTERFACE_DEFINED__ */


#ifndef __ICreateTableStmt_INTERFACE_DEFINED__
#define __ICreateTableStmt_INTERFACE_DEFINED__

/* interface ICreateTableStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICreateTableStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE78C-EC1D-4680-9A37-B5CD0BF0C1BC")
    ICreateTableStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdent( 
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateTableItemList( 
            /* [retval][out] */ ICreateTableItemList __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICreateTableStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICreateTableStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICreateTableStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdent )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateTableItemList )( 
            ICreateTableStmt __RPC_FAR * This,
            /* [retval][out] */ ICreateTableItemList __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } ICreateTableStmtVtbl;

    interface ICreateTableStmt
    {
        CONST_VTBL struct ICreateTableStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateTableStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICreateTableStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICreateTableStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICreateTableStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICreateTableStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICreateTableStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICreateTableStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICreateTableStmt_get_TableIdent(This,pVal)	\
    (This)->lpVtbl -> get_TableIdent(This,pVal)

#define ICreateTableStmt_get_CreateTableItemList(This,pVal)	\
    (This)->lpVtbl -> get_CreateTableItemList(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableStmt_get_TableIdent_Proxy( 
    ICreateTableStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ICreateTableStmt_get_TableIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ICreateTableStmt_get_CreateTableItemList_Proxy( 
    ICreateTableStmt __RPC_FAR * This,
    /* [retval][out] */ ICreateTableItemList __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ICreateTableStmt_get_CreateTableItemList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICreateTableStmt_INTERFACE_DEFINED__ */


#ifndef __IDropStmt_INTERFACE_DEFINED__
#define __IDropStmt_INTERFACE_DEFINED__

/* interface IDropStmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDropStmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE78D-EC1D-4680-9A37-B5CD0BF0C1BC")
    IDropStmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TableIdent( 
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDropStmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDropStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDropStmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDropStmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDropStmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDropStmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDropStmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDropStmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TableIdent )( 
            IDropStmt __RPC_FAR * This,
            /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IDropStmtVtbl;

    interface IDropStmt
    {
        CONST_VTBL struct IDropStmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDropStmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDropStmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDropStmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDropStmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDropStmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDropStmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDropStmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDropStmt_get_TableIdent(This,pVal)	\
    (This)->lpVtbl -> get_TableIdent(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDropStmt_get_TableIdent_Proxy( 
    IDropStmt __RPC_FAR * This,
    /* [retval][out] */ ITableIdent __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IDropStmt_get_TableIdent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDropStmt_INTERFACE_DEFINED__ */


#ifndef __IParser_INTERFACE_DEFINED__
#define __IParser_INTERFACE_DEFINED__

/* interface IParser */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IParser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62ECE78E-EC1D-4680-9A37-B5CD0BF0C1BC")
    IParser : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ParseSQL( 
            /* [in] */ BSTR bstrSQL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectStmt( 
            /* [retval][out] */ ISelectStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UpdateStmt( 
            /* [retval][out] */ IUpdateStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StatementType( 
            /* [retval][out] */ STATEMENT_TYPE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InsertStmt( 
            /* [retval][out] */ IInsertStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeleteStmt( 
            /* [retval][out] */ IDeleteStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateTableStmt( 
            /* [retval][out] */ ICreateTableStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DropTableStmt( 
            /* [retval][out] */ IDropStmt __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IParser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IParser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IParser __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IParser __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IParser __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IParser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IParser __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseSQL )( 
            IParser __RPC_FAR * This,
            /* [in] */ BSTR bstrSQL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ ISelectStmt __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UpdateStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ IUpdateStmt __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatementType )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ STATEMENT_TYPE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InsertStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ IInsertStmt __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ IDeleteStmt __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateTableStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ ICreateTableStmt __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DropTableStmt )( 
            IParser __RPC_FAR * This,
            /* [retval][out] */ IDropStmt __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IParserVtbl;

    interface IParser
    {
        CONST_VTBL struct IParserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IParser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IParser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IParser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IParser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IParser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IParser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IParser_ParseSQL(This,bstrSQL)	\
    (This)->lpVtbl -> ParseSQL(This,bstrSQL)

#define IParser_get_SelectStmt(This,pVal)	\
    (This)->lpVtbl -> get_SelectStmt(This,pVal)

#define IParser_get_UpdateStmt(This,pVal)	\
    (This)->lpVtbl -> get_UpdateStmt(This,pVal)

#define IParser_get_StatementType(This,pVal)	\
    (This)->lpVtbl -> get_StatementType(This,pVal)

#define IParser_get_InsertStmt(This,pVal)	\
    (This)->lpVtbl -> get_InsertStmt(This,pVal)

#define IParser_get_DeleteStmt(This,pVal)	\
    (This)->lpVtbl -> get_DeleteStmt(This,pVal)

#define IParser_get_CreateTableStmt(This,pVal)	\
    (This)->lpVtbl -> get_CreateTableStmt(This,pVal)

#define IParser_get_DropTableStmt(This,pVal)	\
    (This)->lpVtbl -> get_DropTableStmt(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IParser_ParseSQL_Proxy( 
    IParser __RPC_FAR * This,
    /* [in] */ BSTR bstrSQL);


void __RPC_STUB IParser_ParseSQL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_SelectStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ ISelectStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_SelectStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_UpdateStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ IUpdateStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_UpdateStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_StatementType_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ STATEMENT_TYPE __RPC_FAR *pVal);


void __RPC_STUB IParser_get_StatementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_InsertStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ IInsertStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_InsertStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_DeleteStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ IDeleteStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_DeleteStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_CreateTableStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ ICreateTableStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_CreateTableStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IParser_get_DropTableStmt_Proxy( 
    IParser __RPC_FAR * This,
    /* [retval][out] */ IDropStmt __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IParser_get_DropTableStmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IParser_INTERFACE_DEFINED__ */



#ifndef __TRiASQL_LIBRARY_DEFINED__
#define __TRiASQL_LIBRARY_DEFINED__

/* library TRiASQL */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TRiASQL;

EXTERN_C const CLSID CLSID_Parser;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE790-EC1D-4680-9A37-B5CD0BF0C1BC")
Parser;
#endif

EXTERN_C const CLSID CLSID_SelectStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE791-EC1D-4680-9A37-B5CD0BF0C1BC")
SelectStmt;
#endif

EXTERN_C const CLSID CLSID_TableIdent;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE792-EC1D-4680-9A37-B5CD0BF0C1BC")
TableIdent;
#endif

EXTERN_C const CLSID CLSID_TableIdentList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE793-EC1D-4680-9A37-B5CD0BF0C1BC")
TableIdentList;
#endif

EXTERN_C const CLSID CLSID_ColumnIdent;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE794-EC1D-4680-9A37-B5CD0BF0C1BC")
ColumnIdent;
#endif

EXTERN_C const CLSID CLSID_ColumnIdentList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE795-EC1D-4680-9A37-B5CD0BF0C1BC")
ColumnIdentList;
#endif

EXTERN_C const CLSID CLSID_OrderByObj;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE796-EC1D-4680-9A37-B5CD0BF0C1BC")
OrderByObj;
#endif

EXTERN_C const CLSID CLSID_OrderByObjList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE797-EC1D-4680-9A37-B5CD0BF0C1BC")
OrderByObjList;
#endif

EXTERN_C const CLSID CLSID_UpdateStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE798-EC1D-4680-9A37-B5CD0BF0C1BC")
UpdateStmt;
#endif

EXTERN_C const CLSID CLSID_UpdateItem;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79A-EC1D-4680-9A37-B5CD0BF0C1BC")
UpdateItem;
#endif

EXTERN_C const CLSID CLSID_UpdateItemList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79B-EC1D-4680-9A37-B5CD0BF0C1BC")
UpdateItemList;
#endif

EXTERN_C const CLSID CLSID_GenericColl;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79C-EC1D-4680-9A37-B5CD0BF0C1BC")
GenericColl;
#endif

EXTERN_C const CLSID CLSID_GenericStack;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79D-EC1D-4680-9A37-B5CD0BF0C1BC")
GenericStack;
#endif

EXTERN_C const CLSID CLSID_GenericStackList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79E-EC1D-4680-9A37-B5CD0BF0C1BC")
GenericStackList;
#endif

EXTERN_C const CLSID CLSID_LiteralValue;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE79F-EC1D-4680-9A37-B5CD0BF0C1BC")
LiteralValue;
#endif

EXTERN_C const CLSID CLSID_AggregateFunction;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A0-EC1D-4680-9A37-B5CD0BF0C1BC")
AggregateFunction;
#endif

EXTERN_C const CLSID CLSID_NullExpression;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A1-EC1D-4680-9A37-B5CD0BF0C1BC")
NullExpression;
#endif

EXTERN_C const CLSID CLSID_SelectStarExpression;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A2-EC1D-4680-9A37-B5CD0BF0C1BC")
SelectStarExpression;
#endif

EXTERN_C const CLSID CLSID_AritOperator;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A3-EC1D-4680-9A37-B5CD0BF0C1BC")
AritOperator;
#endif

EXTERN_C const CLSID CLSID_CompareOperator;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A4-EC1D-4680-9A37-B5CD0BF0C1BC")
CompareOperator;
#endif

EXTERN_C const CLSID CLSID_BoolOperator;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A5-EC1D-4680-9A37-B5CD0BF0C1BC")
BoolOperator;
#endif

EXTERN_C const CLSID CLSID_MathFunction;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A6-EC1D-4680-9A37-B5CD0BF0C1BC")
MathFunction;
#endif

EXTERN_C const CLSID CLSID_DateFunction;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A7-EC1D-4680-9A37-B5CD0BF0C1BC")
DateFunction;
#endif

EXTERN_C const CLSID CLSID_InsertStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A8-EC1D-4680-9A37-B5CD0BF0C1BC")
InsertStmt;
#endif

EXTERN_C const CLSID CLSID_DeleteStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7A9-EC1D-4680-9A37-B5CD0BF0C1BC")
DeleteStmt;
#endif

EXTERN_C const CLSID CLSID_CreateTableStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7AA-EC1D-4680-9A37-B5CD0BF0C1BC")
CreateTableStmt;
#endif

EXTERN_C const CLSID CLSID_CreateTableItem;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7AB-EC1D-4680-9A37-B5CD0BF0C1BC")
CreateTableItem;
#endif

EXTERN_C const CLSID CLSID_CreateTableItemList;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7AC-EC1D-4680-9A37-B5CD0BF0C1BC")
CreateTableItemList;
#endif

EXTERN_C const CLSID CLSID_DropStmt;

#ifdef __cplusplus

class DECLSPEC_UUID("62ECE7AD-EC1D-4680-9A37-B5CD0BF0C1BC")
DropStmt;
#endif
#endif /* __TRiASQL_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

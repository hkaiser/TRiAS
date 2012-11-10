/*  Product: Small Parser

    Copyright (C) 1999  Systementor AB, Stefan Holmberg
    Email - stefan.holmberg@systementor.se
    Web:   - http://www.systementor.se

///////////////////////////////////////////////////////////////////////////////
*/

/* * $History: TRiASQL.cpp $ 
 * 
 * *****************  Version 3  *****************
 * User: Stefan Holmberg Date: 7/13/99    Time: 6:45p
 * Updated in $/Products/SmallParser
 * 
 * *****************  Version 2  *****************
 * User: Stefan Holmberg Date: 7/11/99    Time: 12:23p
 * Updated in $/Products/SmallParser
*/

// TRiASQL.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f SmallParserps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "TRiASQL.h"				 

#include "TRiASQL_i.c"
#include "Parser.h"

#ifdef _DEBUG
#include "shalloc.h"
#define new DEBUG_NEW
#endif


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Parser, cParser)
//OBJECT_ENTRY(CLSID_SelectStmt, cSelectStmt)
//OBJECT_ENTRY(CLSID_TableIdent, cTableIdent)
//OBJECT_ENTRY(CLSID_TableIdentList, cTableIdentList)
//OBJECT_ENTRY(CLSID_ColumnIdent, cColumnIdent)
//OBJECT_ENTRY(CLSID_ColumnIdentList, cColumnIdentList)
//OBJECT_ENTRY(CLSID_OrderByObj, cOrderByObj)
//OBJECT_ENTRY(CLSID_GroupByObjList, cGroupByObjList)
//OBJECT_ENTRY(CLSID_OrderByObjList, cOrderByList)
//OBJECT_ENTRY(CLSID_UpdateStmt, cUpdateStmt)
//OBJECT_ENTRY(CLSID_UpdateItem, cUpdateItem)
//OBJECT_ENTRY(CLSID_UpdateItemList, cUpdateItemList)
//OBJECT_ENTRY(CLSID_GenericColl, cGenericColl)
//OBJECT_ENTRY(CLSID_GenericStack, cGenericStack)
//OBJECT_ENTRY(CLSID_GenericStackList, cGenericStackList)
//OBJECT_ENTRY(CLSID_LiteralValue, cLiteralValue)
//OBJECT_ENTRY(CLSID_AggregateFunction, cAggregateFunction)
//OBJECT_ENTRY(CLSID_NullExpression, cNullExpression)
//OBJECT_ENTRY(CLSID_SelectStarExpression, cSelectStarExpression)
//OBJECT_ENTRY(CLSID_AritOperator, cAritOperator)
//OBJECT_ENTRY(CLSID_CompareOperator, cCompareOperator)
//OBJECT_ENTRY(CLSID_BoolOperator, cBoolOperator)
//OBJECT_ENTRY(CLSID_MathFunction, cMathFunction)
//OBJECT_ENTRY(CLSID_DateFunction, cDateFunction)
//OBJECT_ENTRY(CLSID_InsertStmt, cInsertStmt)
//OBJECT_ENTRY(CLSID_DeleteStmt, cDeleteStmt)
//OBJECT_ENTRY(CLSID_CreateTableStmt, cCreateTableStmt)
//OBJECT_ENTRY(CLSID_CreateTableItem, cCreateTableItem)
//OBJECT_ENTRY(CLSID_CreateTableItemList, cCreateTableItemList)
//OBJECT_ENTRY(CLSID_DropStmt, cDropStmt)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_TRiASQL);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


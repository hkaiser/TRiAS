// BScript-Erweiterung (DaoLayer) ---------------------------------------------
// File: DAOEXTF.CPP

#include "stdafx.h"

#include <eb.h>
#include "resource.h"

#include <initguid.h>
#undef _DBDAOID_H_
#include <dbdaoid.h>		// guid's

#include "WinVersn.h"
#include "Daoextf.h"
#include "jumptab.h"
#include "strcvrt.h"
#include "ebargs.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DefineSmartDAOInterface(IF) \
	typedef __Interface<IF,__CIID<&IID_I##IF>,CComPtr<IF> > W##IF;

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(EnumVARIANT);
DefineSmartDAOInterface(DAOWorkspace);

///////////////////////////////////////////////////////////////////////////////
// globale Instanz der DBEngine
CdbDBEngine *g_pDBEngine = NULL;
CdbDBEngine *DBEngine (bool fNewIfFirst = true);

///////////////////////////////////////////////////////////////////////////////
// HelperFunctions 
///////////////////////////////////////////////////////////////////////////////
void HandleDAOError (ebHTHREAD hThread, LONG lError);
void HandleBscriptError (ebHTHREAD hThread, LONG iError);

///////////////////////////////////////////////////////////////////////////////
// Make Ole-VARIANT from ebVARIANT --------------------------------------------
COleVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg,
						 bool fUseUnicode = true)
{
COleVariant vResult;

	if (iArg > iNumArgs) 
		return COleVariant ((LONG)DISP_E_PARAMNOTFOUND, VT_ERROR);
	
ebVARIANT v;

	ebGetVariantEx (lpArgs, iArg, &v);

	VariantInit (&vResult);
	switch (v.Type) {
	case TYP_BOOLEAN:	// VT_BOOL
	case TYP_INTEGER:	// VT_I2
	case TYP_LONG:		// VT_I4
	case TYP_SINGLE:	// VT_R4
	case TYP_DOUBLE:	// VT_R8
	case TYP_CURRENCY:	// VT_CY
	case TYP_DATE:		// VT_DATE
	case TYP_NULL:		// VT_NULL
		vResult = COleVariant ((VARIANT &)v);
		break;
		
	case TYP_ERROR:		// VT_ERROR
		if (ebHIWORD(v.u.l) & 0x0002) 
			vResult = COleVariant ((LONG)DISP_E_PARAMNOTFOUND, VT_ERROR); // parameter was skipped
		else
			vResult = COleVariant ((VARIANT &)v);
		break;
		
	case TYP_STRING:	// VT_BSTR
		{
		ebHSUB hStr = v.u.h;
		LPTSTR pT = ebLockString (hThread, hStr);
		
			if (pT) {
				vResult = COleVariant (pT, fUseUnicode ? VT_BSTR : VT_BSTRT);
				ebUnlockString (hThread, hStr);
			}
		}
		break;
		
	case TYP_OLEOBJECT:	// VT_DISPATCH
		{
			V_VT (&vResult) = VT_DISPATCH;
			V_DISPATCH(&vResult) = ebGetDispatch (hThread, v.u.o);
		}
		break;

	default:
		break;
	}

return vResult;
}

// Make ebVARIANT from Ole-VARIANT --------------------------------------------
ebVARIANT MakeebVARIANT (ebHTHREAD hThread, VARIANT &v, bool fUseUnicode = true)
{
ebVARIANT vResult;

	switch (V_VT(&v)) {
	case VT_BOOL:		// TYP_BOOLEAN
	case VT_I2:		// TYP_INTEGER
	case VT_I4:		// TYP_LONG
	case VT_R4:		// TYP_SINGLE
	case VT_R8:		// TYP_DOUBLE
	case VT_CY:		// TYP_CURRENCY
	case VT_DATE:	// TYP_DATE
	case VT_NULL:	// TYP_NULL
		vResult = (ebVARIANT &)v;
		break;
		
	case VT_ERROR:		// TYP_ERROR
		if (V_ERROR(&v) == DISP_E_PARAMNOTFOUND) {
			vResult.Type = TYP_ERROR;
			vResult.u.l = 0x00020000;	// parameter was skipped
		} else
			vResult = (ebVARIANT &)v;
		break;
		
	case VT_BSTR:		// TYP_STRING
		vResult.Type = TYP_STRING;
		vResult.u.h = ebCreateString (hThread, fUseUnicode ? AnsiString(V_BSTR(&v)) : V_BSTRT(&v));
		break;
		
	case VT_BSTRT:		// TYP_STRING
		vResult.Type = TYP_STRING;
		vResult.u.h = ebCreateString (hThread, fUseUnicode ? AnsiString(V_BSTR(&v)) : V_BSTRT(&v));
		break;
		
	case VT_DISPATCH:	// TYP_OLEOBJECT
		vResult.Type = TYP_OLEOBJECT;
		vResult.u.o = ebCreateOleId (hThread, V_DISPATCH(&v));
		break;

	default:
		vResult.Type = TYP_ERROR;
		vResult.u.l = 0x00020000;	// parameter was skipped
		break;
	}

return vResult;
}

///////////////////////////////////////////////////////////////////////////////
// CallBackFunktionen

// ----------------------------------------------------------------------------
// Dao_not_supported
// ----------------------------------------------------------------------------
void Dao_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	throw TRIASERR_DAONOTSUPPORTED;
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// DaoObject_refcnt
// ----------------------------------------------------------------------------
void DaoObject_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
	// error message ?
		ebSetObject (lpArgs, RETURNVAL, NULL);
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		if (0 == GetDaoObject (lpArgs) -> Release())
			{ break; }		// Debug purposes
		break;
	}
}

// ----------------------------------------------------------------------------
// DBEngine_refcnt
// ----------------------------------------------------------------------------
void DBEngine_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
	// error message ?
		ebSetObject (lpArgs, RETURNVAL, reinterpret_cast<DWORD>(DBEngine()));
		break;
		
	case OBJECT_REFINC:
		DBEngine() -> GetInterface() -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		if (0 == DBEngine() -> GetInterface() -> Release())
			{}		// Fehlermeldung: DBEngine soll gelöscht werden
		break;
	}
}

// -------------------------------------------------------------------------------
// TableDef_refcnt
// -------------------------------------------------------------------------------
void TableDef_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbTableDef TableDef;

				TableDef.SetInterface (CLSID_CDAOTableDef, dbIID_IDAOTableDef);
				SetDaoObject (lpArgs, TableDef);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// QueryDef_refcnt
// -------------------------------------------------------------------------------
void QueryDef_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbQueryDef QueryDef;

				QueryDef.SetInterface (CLSID_CDAOQueryDef, dbIID_IDAOQueryDef);
				SetDaoObject (lpArgs, QueryDef);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// Field_refcnt
// -------------------------------------------------------------------------------
void Field_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbField Field;

				Field.SetInterface (CLSID_CDAOField, dbIID_IDAOField);
				SetDaoObject (lpArgs, Field);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// Index_refcnt
// -------------------------------------------------------------------------------
void Index_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbIndex Index;

				Index.SetInterface (CLSID_CDAOIndex, dbIID_IDAOIndex);
				SetDaoObject (lpArgs, Index);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// User_refcnt
// -------------------------------------------------------------------------------
void User_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbUser User;

				User.SetInterface (CLSID_CDAOUser, dbIID_IDAOUser);
				SetDaoObject (lpArgs, User);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// Group_refcnt
// -------------------------------------------------------------------------------
void Group_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbGroup Group;

				Group.SetInterface (CLSID_CDAOGroup, dbIID_IDAOGroup);
				SetDaoObject (lpArgs, Group);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

// -------------------------------------------------------------------------------
// Relation_refcnt
// -------------------------------------------------------------------------------
void Relation_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			TRY {
			CdbRelation Relation;

				Relation.SetInterface (CLSID_CDAORelation, dbIID_IDAORelation);
				SetDaoObject (lpArgs, Relation);
			} CATCH_ALL (e) {
				ebSetObject (lpArgs, RETURNVAL, 0L);
			} END_CATCH_ALL
		}
		break;
		
	case OBJECT_REFINC:
		GetDaoObject (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetDaoObject (lpArgs) -> Release();
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// DaoObject_Name_propget
// ----------------------------------------------------------------------------
void DaoObject_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbObject DaoObj (GetDaoObject (lpArgs), true);

	SetString (hThread, lpArgs, (&DaoObj) -> GetName());
}

// ----------------------------------------------------------------------------
// DaoObject_Name_propset
// ----------------------------------------------------------------------------
void DaoObject_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbObject DaoObj (GetDaoObject (lpArgs), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	(&DaoObj) -> SetName (str);
}

// ----------------------------------------------------------------------------
// DaoObject_Properties_propget
// ----------------------------------------------------------------------------
void DaoObject_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbObject DaoObj (GetDaoObject (lpArgs), true);

	SetDaoObject (lpArgs, (&DaoObj) -> Properties);
}

// ----------------------------------------------------------------------------
// Field_Properties_propget
// ----------------------------------------------------------------------------
void Field_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField DaoObj (GetDaoObject (lpArgs, (DAOField *)NULL), true);

	SetDaoObject (lpArgs, (&DaoObj) -> Properties);
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// DaoCollection_Count_propget
// ----------------------------------------------------------------------------
void DaoCollection_Count_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbStaticCollection Coll;
	
	Coll.SetInterface (GetDaoObject (lpArgs), true);
	ebSetLong (lpArgs, RETURNVAL, Coll.GetCount());
}

// ----------------------------------------------------------------------------
// DaoCollection_Append_command
// ----------------------------------------------------------------------------
void DaoDynCollection_Append_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDynamicCollection Coll; 
CdbObject DaoObj (GetDaoObject (lpArgs, OBJARG1), true);

	Coll.SetInterface (GetDaoObject (lpArgs), true);
	Coll.ObAppend (DaoObj);
}

// ----------------------------------------------------------------------------
// DaoCollection_Delete_command
// ----------------------------------------------------------------------------
void DaoDynCollection_Delete_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDynamicCollection Coll;
CStrArg str (hThread, lpArgs, OBJARG1);

	Coll.SetInterface (GetDaoObject (lpArgs), true);
	Coll.Delete (str);
}

// ----------------------------------------------------------------------------
// DaoCollection_Refresh_command
// ----------------------------------------------------------------------------
void DaoCollection_Refresh_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbStaticCollection Coll;

	Coll.SetInterface (GetDaoObject (lpArgs), true);
	Coll.Refresh();
}

// ----------------------------------------------------------------------------
// DaoCollection_Item_function
// ----------------------------------------------------------------------------
void DaoCollection_Item_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
COleVariant vArg = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1);

// Argument ist entweder LONG (lIndex) ...
LONG lError = 0;

	TRY {
		vArg.ChangeType (VT_I4);		// raises COleException
		
	CdbStaticCollection Coll;
	
		Coll.SetInterface (GetDaoObject (lpArgs), true);
		SetDaoObject (lpArgs, Coll.ObItem (V_I4(&vArg)));
		return;		// ok, Item gefunden
	} CATCH (COleException, e) {
		if (DISP_E_TYPEMISMATCH != COleException::Process (e)) 
			lError = TRIASERR_DAOGENERICERROR;
	} CATCH_ALL (e) {
		;
	} END_CATCH_ALL
	
	if (0 != lError) {
		HandleBscriptError (hThread, lError);
		ASSERT(false);		// kehrt nicht zurück
	}

// ... oder ZeichenKette (Name)
	TRY {
		vArg.ChangeType (VT_BSTR);

	CdbStaticCollection Coll;
	
		Coll.SetInterface (GetDaoObject (lpArgs), true);
		SetDaoObject (lpArgs, Coll.ObItem (AnsiString(V_BSTR(&vArg))));
	} CATCH (COleException, e) {
		if (DISP_E_TYPEMISMATCH == COleException::Process (e))
			lError = TRIASERR_DAOINVALIDPARAM;		// falscher ParameterTyp
		else 
			lError = TRIASERR_DAOGENERICERROR;		// unbekannter Fehler
	} CATCH_ALL(e) {
		;
	} END_CATCH_ALL

	if (0 != lError) {
		HandleBscriptError (hThread, lError);
		ASSERT(false);		// kehrt nicht zurück
	}
}

// ----------------------------------------------------------------------------
// DaoDynCollection_Item_function
// ----------------------------------------------------------------------------
void DaoDynCollection_Item_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
COleVariant vArg = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1);

// Argument ist entweder LONG (lIndex) ...
LONG lError = 0L;

	TRY {
		vArg.ChangeType (VT_I4);		// raises COleException
		
	CdbDynamicCollection Coll;

		Coll.SetInterface (GetDaoObject (lpArgs), true);
		SetDaoObject (lpArgs, Coll.ObItem (V_I4(&vArg)));
		return;		// ok, Item gefunden
	} CATCH (COleException, e) {
		if (DISP_E_TYPEMISMATCH != COleException::Process (e)) 
 			lError = TRIASERR_DAOGENERICERROR;
	} CATCH_ALL(e) {
		;
	} END_CATCH_ALL

	if (0 != lError) {
		HandleBscriptError (hThread, lError);
		ASSERT(false);		// kehrt nicht zurück
	}

// ... oder ZeichenKette (Name)
	TRY {
		vArg.ChangeType (VT_BSTR);

	CdbDynamicCollection Coll;
	
		Coll.SetInterface (GetDaoObject (lpArgs), true);
		SetDaoObject (lpArgs, Coll.ObItem (AnsiString(V_BSTR(&vArg))));
	} CATCH (COleException, e) {
		if (DISP_E_TYPEMISMATCH == COleException::Process (e))
 			lError = TRIASERR_DAOINVALIDPARAM;
		else 
 			lError = TRIASERR_DAOGENERICERROR;
	} CATCH_ALL(e) {
		;
	} END_CATCH_ALL

	if (0 != lError) {
		HandleBscriptError (hThread, lError);
		ASSERT(false);		// kehrt nicht zurück
	}
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// DBEngine_DefaultUser_propset
// ----------------------------------------------------------------------------
void DBEngine_DefaultUser_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str (hThread, lpArgs, OBJARG1);

	DBEngine() -> SetDefaultUser (str);
}

// ----------------------------------------------------------------------------
// DBEngine_DefaultPassword_propset
// ----------------------------------------------------------------------------
void DBEngine_DefaultPassword_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str (hThread, lpArgs, OBJARG1);

	DBEngine() -> SetDefaultPassword (str);
}

// ----------------------------------------------------------------------------
// DBEngine_IniPath_propget
// ----------------------------------------------------------------------------
void DBEngine_IniPath_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	SetString (hThread, lpArgs, DBEngine() -> GetIniPath());
}

// ----------------------------------------------------------------------------
// DBEngine_IniPath_propset
// ----------------------------------------------------------------------------
void DBEngine_IniPath_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> SetIniPath (CStrArg (hThread, lpArgs, OBJARG1));
}

// ----------------------------------------------------------------------------
// DBEngine_LoginTimeout_propget
// ----------------------------------------------------------------------------
void DBEngine_LoginTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ebSetInt (lpArgs, 0, DBEngine() -> GetLoginTimeout());
}

// ----------------------------------------------------------------------------
// DBEngine_LoginTimeout_propset
// ----------------------------------------------------------------------------
void DBEngine_LoginTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> SetLoginTimeout (ebGetInt (lpArgs, OBJARG1));
}

// ----------------------------------------------------------------------------
// DBEngine_SystemDB_propget
// ----------------------------------------------------------------------------
void DBEngine_SystemDB_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	SetString (hThread, lpArgs, DBEngine() -> GetSystemDB());
}

// ----------------------------------------------------------------------------
// DBEngine_SystemDB_propset
// ----------------------------------------------------------------------------
void DBEngine_SystemDB_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str (hThread, lpArgs, OBJARG1);

	DBEngine() -> SetSystemDB (str);
}

// ----------------------------------------------------------------------------
// DBEngine_Version_propget
// ----------------------------------------------------------------------------
void DBEngine_Version_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	SetString (hThread, lpArgs, DBEngine() -> GetVersion());
}

// ----------------------------------------------------------------------------
// DBEngine_CompactDatabase_command
// ----------------------------------------------------------------------------
void DBEngine_CompactDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2);
CStrArg str3 (hThread, lpArgs, OBJARG3, iNumArgs);
long lArg4 = LongArg (lpArgs, OBJARG4, -1L, iNumArgs);
CStrArg str5 (hThread, lpArgs, OBJARG5, iNumArgs);

	DBEngine() -> CompactDatabase (str1, str2, str3, lArg4, str5);
}

// ----------------------------------------------------------------------------
// DBEngine_CreateWorkspace_function
// ----------------------------------------------------------------------------
void DBEngine_CreateWorkspace_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2);
CStrArg str3 (hThread, lpArgs, OBJARG3);

	SetDaoObject (lpArgs, DBEngine() -> CreateWorkspace (str1, str2, str3));
}

// ----------------------------------------------------------------------------
// DBEngine_Idle_command
// ----------------------------------------------------------------------------
void DBEngine_Idle_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
long lArg = LongArg (lpArgs, OBJARG1, -1L, iNumArgs);

	DBEngine() -> Idle (lArg);
}

// ----------------------------------------------------------------------------
// DBEngine_RegisterDatabase_command
// ----------------------------------------------------------------------------
void DBEngine_RegisterDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2);
CStrArg str4 (hThread, lpArgs, OBJARG4);

	DBEngine() -> RegisterDatabase (str1, str2, GetBool (lpArgs, OBJARG3), str4);
}

// ----------------------------------------------------------------------------
// DBEngine_RepairDatabase_command
// ----------------------------------------------------------------------------
void DBEngine_RepairDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str (hThread, lpArgs, OBJARG1);

	DBEngine() -> RepairDatabase (str);
}

// ----------------------------------------------------------------------------
// DBEngine_Errors_function
// ----------------------------------------------------------------------------
void DBEngine_Errors_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	SetDaoObject (lpArgs, DBEngine() -> Errors);
}

// ----------------------------------------------------------------------------
// DBEngine_Workspaces_function
// ----------------------------------------------------------------------------
void DBEngine_Workspaces_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();
	SetDaoObject (lpArgs, DBEngine() -> Workspaces);
}

// -------------------------------------------------------------------------------
// Workspace_IsolateODBCTrans_propget
// -------------------------------------------------------------------------------
void Workspace_IsolateODBCTrans_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetBool (lpArgs, wrk.GetIsolateODBCTrans());
}

// -------------------------------------------------------------------------------
// Workspace_IsolateODBCTrans_propset
// -------------------------------------------------------------------------------
void Workspace_IsolateODBCTrans_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	wrk.SetIsolateODBCTrans (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Workspace_UserName_propget
// -------------------------------------------------------------------------------
void Workspace_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetString (hThread, lpArgs, wrk.GetUserName());
}

// -------------------------------------------------------------------------------
// Workspace_UserName_propset
// -------------------------------------------------------------------------------
void Workspace_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CStrArg str (hThread, lpArgs, OBJARG1);
// not implemented in DBDAO
//CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
//	wrk.SetUserName (str);
DAOWorkspace * p = GetDaoObject(lpArgs, (DAOWorkspace *)NULL);

	DAOMFC_CALL(p->put__30_UserName(STB(str)));
}

// -------------------------------------------------------------------------------
// Workspace_BeginTrans_command
// -------------------------------------------------------------------------------
void Workspace_BeginTrans_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	wrk.BeginTrans();
}

// -------------------------------------------------------------------------------
// Workspace_CommitTrans_command
// -------------------------------------------------------------------------------
void Workspace_CommitTrans_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	wrk.CommitTrans();
}

// -------------------------------------------------------------------------------
// Workspace_RollBack_command
// -------------------------------------------------------------------------------
void Workspace_RollBack_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	wrk.Rollback();
}

// -------------------------------------------------------------------------------
// Workspace_Close_command
// -------------------------------------------------------------------------------
void Workspace_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	wrk.Close();
}

// -------------------------------------------------------------------------------
// Workspace_CreateDatabase_function
// -------------------------------------------------------------------------------
void Workspace_CreateDatabase_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2);
int iArg3 = IntArg (lpArgs, OBJARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateDatabase (str1, str2, iArg3));
}

// -------------------------------------------------------------------------------
// Workspace_CreateGroup_function
// -------------------------------------------------------------------------------
void Workspace_CreateGroup_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateGroup (str1, str2));
}

// -------------------------------------------------------------------------------
// Workspace_CreateUser_function
// -------------------------------------------------------------------------------
void Workspace_CreateUser_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);
CStrArg str3 (hThread, lpArgs, OBJARG3, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateUser (str1, str2, str3));
}

// -------------------------------------------------------------------------------
// Workspace_OpenDatabase_function
// -------------------------------------------------------------------------------
void Workspace_OpenDatabase_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
ebBOOL fArg2 = BoolArg (lpArgs, OBJARG2, ebFALSE, iNumArgs);
ebBOOL fArg3 = BoolArg (lpArgs, OBJARG3, ebFALSE, iNumArgs);
CStrArg str4 (hThread, lpArgs, OBJARG4, iNumArgs);

	SetDaoObject (lpArgs, wrk.OpenDatabase (str1, fArg2, fArg3, str4));
}

// -------------------------------------------------------------------------------
// Workspace_Databases_propget
// -------------------------------------------------------------------------------
void Workspace_Databases_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetDaoObject (lpArgs, wrk.Databases);
}

// -------------------------------------------------------------------------------
// Workspace_Groups_propget
// -------------------------------------------------------------------------------
void Workspace_Groups_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetDaoObject (lpArgs, wrk.Groups);
}

// -------------------------------------------------------------------------------
// Workspace_Users_propget
// -------------------------------------------------------------------------------
void Workspace_Users_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace wrk (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetDaoObject (lpArgs, wrk.Users);
}

// -------------------------------------------------------------------------------
// Error_Description_propget
// -------------------------------------------------------------------------------
void Error_Description_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbError err (GetDaoObject(lpArgs, (DAOError *)NULL), true);

	SetString (hThread, lpArgs, err.GetDescription());
}

// -------------------------------------------------------------------------------
// Error_HelpContext_propget
// -------------------------------------------------------------------------------
void Error_HelpContext_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbError err (GetDaoObject(lpArgs, (DAOError *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, err.GetHelpContext());
}

// -------------------------------------------------------------------------------
// Error_HelpFile_propget
// -------------------------------------------------------------------------------
void Error_HelpFile_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbError err (GetDaoObject(lpArgs, (DAOError *)NULL), true);

	SetString (hThread, lpArgs, err.GetHelpFile());
}

// -------------------------------------------------------------------------------
// Error_Number_propget
// -------------------------------------------------------------------------------
void Error_Number_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbError err (GetDaoObject(lpArgs, (DAOError *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, err.GetNumber());
}

// -------------------------------------------------------------------------------
// Error_Source_propget
// -------------------------------------------------------------------------------
void Error_Source_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbError err (GetDaoObject(lpArgs, (DAOError *)NULL), true);

	SetString (hThread, lpArgs, err.GetSource());
}

// -------------------------------------------------------------------------------
// Database_CollatingOrder_propget
// -------------------------------------------------------------------------------
void Database_CollatingOrder_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, db.GetCollatingOrder());
}

// -------------------------------------------------------------------------------
// Database_Connect_propget
// -------------------------------------------------------------------------------
void Database_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetString (hThread, lpArgs, db.GetConnect());
}

// -------------------------------------------------------------------------------
// Database_QueryTimeout_propget
// -------------------------------------------------------------------------------
void Database_QueryTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, db.GetQueryTimeout());
}

// -------------------------------------------------------------------------------
// Database_QueryTimeout_propset
// -------------------------------------------------------------------------------
void Database_QueryTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	db.SetQueryTimeout (ebGetInt (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Database_RecordsAffected_propget
// -------------------------------------------------------------------------------
void Database_RecordsAffected_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, db.GetRecordsAffected());
}

// -------------------------------------------------------------------------------
// Database_Transactions_propget
// -------------------------------------------------------------------------------
void Database_Transactions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetBool (lpArgs, db.GetTransactions());
}

// -------------------------------------------------------------------------------
// Database_Updatable_propget
// -------------------------------------------------------------------------------
void Database_Updatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetBool (lpArgs, db.GetUpdatable());
}

// -------------------------------------------------------------------------------
// Database_Version_propget
// -------------------------------------------------------------------------------
void Database_Version_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetString (hThread, lpArgs, db.GetVersion());
}

// -------------------------------------------------------------------------------
// Database_Close_command
// -------------------------------------------------------------------------------
void Database_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	db.Close();
}

// -------------------------------------------------------------------------------
// Database_CreateProperty_function
// -------------------------------------------------------------------------------
void Database_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
COleVariant vArg3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3);
ebBOOL fArg4 = BoolArg (lpArgs, OBJARG4, ebFALSE, iNumArgs);

	SetDaoObject (lpArgs, db.CreateProperty (str1, iArg2, &vArg3, fArg4));
}

// -------------------------------------------------------------------------------
// Database_CreateQueryDef_function
// -------------------------------------------------------------------------------
void Database_CreateQueryDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);

	SetDaoObject (lpArgs, db.CreateQueryDef (str1, str2));
}

// -------------------------------------------------------------------------------
// Database_CreateRelation_function
// -------------------------------------------------------------------------------
void Database_CreateRelation_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);
CStrArg str3 (hThread, lpArgs, OBJARG3, iNumArgs);
long lArg4 = LongArg (lpArgs, OBJARG4, -1L, iNumArgs);

	SetDaoObject (lpArgs, db.CreateRelation (str1, str2, str3, lArg4));
}

// -------------------------------------------------------------------------------
// Database_CreateTableDef_function
// -------------------------------------------------------------------------------
void Database_CreateTableDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
long lArg2 = LongArg (lpArgs, OBJARG2, -1L, iNumArgs);
CStrArg str3 (hThread, lpArgs, OBJARG3, iNumArgs);
CStrArg str4 (hThread, lpArgs, OBJARG4, iNumArgs);

	SetDaoObject (lpArgs, db.CreateTableDef (str1, lArg2, str3, str4));
}

// -------------------------------------------------------------------------------
// Database_Execute_command
// -------------------------------------------------------------------------------
void Database_Execute_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
long lArg2 = LongArg (lpArgs, OBJARG2, -1L, iNumArgs);

	db.Execute (str1, lArg2);
}

// -------------------------------------------------------------------------------
// Database_OpenRecordSet_function
// -------------------------------------------------------------------------------
void Database_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
int iArg3 = IntArg (lpArgs, OBJARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, db.OpenRecordset (str1, iArg2, iArg3));
}

// -------------------------------------------------------------------------------
// Database_TableDefs_propget
// -------------------------------------------------------------------------------
void Database_TableDefs_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, db.TableDefs);
}

// -------------------------------------------------------------------------------
// Database_Containers_propget
// -------------------------------------------------------------------------------
void Database_Containers_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, db.Containers);
}

// -------------------------------------------------------------------------------
// Database_QueryDefs_propget
// -------------------------------------------------------------------------------
void Database_QueryDefs_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, db.QueryDefs);
}

// -------------------------------------------------------------------------------
// Database_RecordSet_propget
// -------------------------------------------------------------------------------
void Database_RecordSet_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, db.Recordsets);
}

// -------------------------------------------------------------------------------
// Database_Relations_propget
// -------------------------------------------------------------------------------
void Database_Relations_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase db (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, db.Relations);
}

// -------------------------------------------------------------------------------
// TableDef_Attributes_propget
// -------------------------------------------------------------------------------
void TableDef_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, tab.GetAttributes());
}

// -------------------------------------------------------------------------------
// TableDef_Attributes_propset
// -------------------------------------------------------------------------------
void TableDef_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	tab.SetAttributes (ebGetLong (lpArgs, OBJARG1));
}

// ----------------------------------------------------------------------------
// TableDef_Properties_propget
// ----------------------------------------------------------------------------
void TableDef_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef DaoObj (GetDaoObject (lpArgs, (DAOTableDef *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// -------------------------------------------------------------------------------
// TableDef_Name_propget
// -------------------------------------------------------------------------------
void TableDef_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef Table (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetString (hThread, lpArgs, Table.GetName());
}

// -------------------------------------------------------------------------------
// TableDef_Name_propset
// -------------------------------------------------------------------------------
void TableDef_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef Table (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	Table.SetName (str);
}

// -------------------------------------------------------------------------------
// TableDef_Connect_propget
// -------------------------------------------------------------------------------
void TableDef_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetString (hThread, lpArgs, tab.GetConnect());
}

// -------------------------------------------------------------------------------
// TableDef_Connect_propset
// -------------------------------------------------------------------------------
void TableDef_Connect_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);

	tab.SetConnect (str1);
}

// -------------------------------------------------------------------------------
// TableDef_DateCreated_propget
// -------------------------------------------------------------------------------
void TableDef_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
COleVariant vOle = tab.GetDateCreated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// TableDef_LastUpdated_propget
// -------------------------------------------------------------------------------
void TableDef_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
COleVariant vOle = tab.GetLastUpdated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// TableDef_RecordCount_propget
// -------------------------------------------------------------------------------
void TableDef_RecordCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, tab.GetRecordCount());
}

// -------------------------------------------------------------------------------
// TableDef_SourceTableName_propget
// -------------------------------------------------------------------------------
void TableDef_SourceTableName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetString (hThread, lpArgs, tab.GetSourceTableName());
}

// -------------------------------------------------------------------------------
// TableDef_SourceTableName_propset
// -------------------------------------------------------------------------------
void TableDef_SourceTableName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef Table (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	Table.SetSourceTableName (str);
}

// -------------------------------------------------------------------------------
// TableDef_Updateable_propget
// -------------------------------------------------------------------------------
void TableDef_Updateable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetBool (lpArgs, tab.GetUpdatable());
}

// -------------------------------------------------------------------------------
// TableDef_ValidationRule_propget
// -------------------------------------------------------------------------------
void TableDef_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetString (hThread, lpArgs, tab.GetValidationRule());
}

// -------------------------------------------------------------------------------
// TableDef_ValidationRule_propset
// -------------------------------------------------------------------------------
void TableDef_ValidationRule_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);

	tab.SetValidationRule (str1);
}

// -------------------------------------------------------------------------------
// TableDef_ValidationText_propget
// -------------------------------------------------------------------------------
void TableDef_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetString (hThread, lpArgs, tab.GetValidationText());
}

// -------------------------------------------------------------------------------
// TableDef_ValidationText_propset
// -------------------------------------------------------------------------------
void TableDef_ValidationText_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);

	tab.SetValidationText (str1);
}

// -------------------------------------------------------------------------------
// TableDef_CreateField_function
// -------------------------------------------------------------------------------
void TableDef_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
int iArg3 = IntArg (lpArgs, OBJARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, tab.CreateField (str1, iArg2, iArg3));
}

// -------------------------------------------------------------------------------
// TableDef_CreateIndex_function
// -------------------------------------------------------------------------------
void TableDef_CreateIndex_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);

	SetDaoObject (lpArgs, tab.CreateIndex (str1));
}

// -------------------------------------------------------------------------------
// TableDef_CreateProperty_function
// -------------------------------------------------------------------------------
void TableDef_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
COleVariant vArg3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3);
ebBOOL fArg4 = BoolArg (lpArgs, OBJARG4, ebFALSE, iNumArgs);

	SetDaoObject (lpArgs, tab.CreateProperty (str1, iArg2, &vArg3, fArg4));
}

// -------------------------------------------------------------------------------
// TableDef_OpenRecordSet_function
// -------------------------------------------------------------------------------
void TableDef_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);
long lArg1 = IntArg (lpArgs, OBJARG1, -1L, iNumArgs);
long lArg2 = IntArg (lpArgs, OBJARG2, -1L, iNumArgs);

	SetDaoObject (lpArgs, tab.OpenRecordset (lArg1, lArg2));
}

// -------------------------------------------------------------------------------
// TableDef_RefreshLink_command
// -------------------------------------------------------------------------------
void TableDef_RefreshLink_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	tab.RefreshLink();
}

// -------------------------------------------------------------------------------
// TableDef_Fields_propget
// -------------------------------------------------------------------------------
void TableDef_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetDaoObject (lpArgs, tab.Fields);
}

// -------------------------------------------------------------------------------
// TableDef_Indexes_propget
// -------------------------------------------------------------------------------
void TableDef_Indexes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbTableDef tab (GetDaoObject(lpArgs, (DAOTableDef *)NULL), true);

	SetDaoObject (lpArgs, tab.Indexes);
}

// -------------------------------------------------------------------------------
// Field_AllowZeroLength_propget
// -------------------------------------------------------------------------------
void Field_AllowZeroLength_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetBool (lpArgs, fld.GetAllowZeroLength());
}

// -------------------------------------------------------------------------------
// Field_AllowZeroLength_propset
// -------------------------------------------------------------------------------
void Field_AllowZeroLength_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetAllowZeroLength (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_Attributes_propget
// -------------------------------------------------------------------------------
void Field_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, fld.GetAttributes());
}

// -------------------------------------------------------------------------------
// Field_Attributes_propset
// -------------------------------------------------------------------------------
void Field_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetAttributes (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_CollatingOrder_propget
// -------------------------------------------------------------------------------
void Field_CollatingOrder_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, fld.GetCollatingOrder());
}

// -------------------------------------------------------------------------------
// Field_DataUpdatable_propget
// -------------------------------------------------------------------------------
void Field_DataUpdatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetBool (lpArgs, fld.GetDataUpdatable());
}

// -------------------------------------------------------------------------------
// Field_DefaultValue_propget
// -------------------------------------------------------------------------------
void Field_DefaultValue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetDefaultValue());
}

// -------------------------------------------------------------------------------
// Field_DefaultValue_propset
// -------------------------------------------------------------------------------
void Field_DefaultValue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	fld.SetDefaultValue (str);
}

// -------------------------------------------------------------------------------
// Field_ForeignName_propget
// -------------------------------------------------------------------------------
void Field_ForeignName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetForeignName());
}

// -------------------------------------------------------------------------------
// Field_ForeignName_propset
// -------------------------------------------------------------------------------
void Field_ForeignName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	fld.SetForeignName (str);
}

// -------------------------------------------------------------------------------
// Field_OrdinalPosition_propget
// -------------------------------------------------------------------------------
void Field_OrdinalPosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, fld.GetOrdinalPosition());
}

// -------------------------------------------------------------------------------
// Field_OrdinalPosition_propset
// -------------------------------------------------------------------------------
void Field_OrdinalPosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetOrdinalPosition (ebGetInt (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_Required_propget
// -------------------------------------------------------------------------------
void Field_Required_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetBool (lpArgs, fld.GetRequired());
}

// -------------------------------------------------------------------------------
// Field_Required_propset
// -------------------------------------------------------------------------------
void Field_Required_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetRequired (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_Size_propget
// -------------------------------------------------------------------------------
void Field_Size_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, fld.GetSize());
}

// -------------------------------------------------------------------------------
// Field_Size_propset
// -------------------------------------------------------------------------------
void Field_Size_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetSize (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_SourceField_propget
// -------------------------------------------------------------------------------
void Field_SourceField_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetSourceField());
}

// -------------------------------------------------------------------------------
// Field_SourceTable_propget
// -------------------------------------------------------------------------------
void Field_SourceTable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetSourceTable());
}

// -------------------------------------------------------------------------------
// Field_Type_propget
// -------------------------------------------------------------------------------
void Field_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, fld.GetType());
}

// -------------------------------------------------------------------------------
// Field_Type_propset
// -------------------------------------------------------------------------------
void Field_Type_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetType (ebGetInt (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_ValidateOnSet_propget
// -------------------------------------------------------------------------------
void Field_ValidateOnSet_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetBool (lpArgs, fld.GetValidateOnSet());
}

// -------------------------------------------------------------------------------
// Field_ValidateOnSet_propset
// -------------------------------------------------------------------------------
void Field_ValidateOnSet_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	fld.SetValidateOnSet (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Field_ValidationRule_propget
// -------------------------------------------------------------------------------
void Field_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetValidationRule());
}

// -------------------------------------------------------------------------------
// Field_ValidationRule_propset
// -------------------------------------------------------------------------------
void Field_ValidationRule_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	fld.SetValidationRule (str);
}

// -------------------------------------------------------------------------------
// Field_ValidationText_propget
// -------------------------------------------------------------------------------
void Field_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetValidationText());
}

// -------------------------------------------------------------------------------
// Field_ValidationText_propset
// -------------------------------------------------------------------------------
void Field_ValidationText_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	fld.SetValidationText (str);
}

// -------------------------------------------------------------------------------
// Field_Value_propget
// -------------------------------------------------------------------------------
void Field_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
COleVariant vOle = fld.GetValue();

ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle, false);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Field_Value_propset
// -------------------------------------------------------------------------------
void Field_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
COleVariant v = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1, false);

	fld.SetValue (&v);
}

// -------------------------------------------------------------------------------
// Field_Name_propget
// -------------------------------------------------------------------------------
void Field_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	SetString (hThread, lpArgs, fld.GetName());
}

// -------------------------------------------------------------------------------
// Field_Name_propset
// -------------------------------------------------------------------------------
void Field_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	fld.SetName (str);
}

// -------------------------------------------------------------------------------
// Field_AppendChunk_command
// -------------------------------------------------------------------------------
void Field_AppendChunk_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
COleVariant v = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1);

	fld.AppendChunk (&v);
}

// -------------------------------------------------------------------------------
// Field_CreateProperty_function
// -------------------------------------------------------------------------------
void Field_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
COleVariant vArg3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3);
ebBOOL fArg4 = BoolArg (lpArgs, OBJARG4, ebFALSE, iNumArgs);

	SetDaoObject (lpArgs, fld.CreateProperty (str1, iArg2, &vArg3, fArg4));
}

// -------------------------------------------------------------------------------
// Field_FieldSize_function
// -------------------------------------------------------------------------------
void Field_FieldSize_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, fld.FieldSize());
}

// -------------------------------------------------------------------------------
// Field_GetChunk_function
// -------------------------------------------------------------------------------
void Field_GetChunk_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbField fld (GetDaoObject(lpArgs, (DAOField *)NULL), true);
COleVariant vOle = fld.GetChunk (ebGetLong (lpArgs, OBJARG1), ebGetLong (lpArgs, OBJARG2));
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);
	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Index_Clustered_propget
// -------------------------------------------------------------------------------
void Index_Clustered_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetClustered());
}

// -------------------------------------------------------------------------------
// Index_Clustered_propset
// -------------------------------------------------------------------------------
void Index_Clustered_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	idx.SetClustered (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Index_DistinctCount_propget
// -------------------------------------------------------------------------------
void Index_DistinctCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetDistinctCount());
}

// -------------------------------------------------------------------------------
// Index_Foreign_propget
// -------------------------------------------------------------------------------
void Index_Foreign_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetForeign());
}

// -------------------------------------------------------------------------------
// Index_IgnoreNulls_propget
// -------------------------------------------------------------------------------
void Index_IgnoreNulls_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetIgnoreNulls());
}

// -------------------------------------------------------------------------------
// Index_IgnoreNulls_propset
// -------------------------------------------------------------------------------
void Index_IgnoreNulls_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	idx.SetIgnoreNulls (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Index_Primary_propget
// -------------------------------------------------------------------------------
void Index_Primary_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetPrimary());
}

// -------------------------------------------------------------------------------
// Index_Primary_propset
// -------------------------------------------------------------------------------
void Index_Primary_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	idx.SetPrimary (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Index_Required_propget
// -------------------------------------------------------------------------------
void Index_Required_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetRequired());
}

// -------------------------------------------------------------------------------
// Index_Required_propset
// -------------------------------------------------------------------------------
void Index_Required_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	idx.SetRequired (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Index_Unique_propget
// -------------------------------------------------------------------------------
void Index_Unique_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetBool (lpArgs, idx.GetUnique());
}

// -------------------------------------------------------------------------------
// Index_Unique_propset
// -------------------------------------------------------------------------------
void Index_Unique_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	idx.SetUnique (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Index_CreateField_function
// -------------------------------------------------------------------------------
void Index_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
int iArg3 = IntArg (lpArgs, OBJARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, idx.CreateField (str1, iArg2, iArg3));
}

// -------------------------------------------------------------------------------
// Index_CreateProperty_function
// -------------------------------------------------------------------------------
void Index_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
COleVariant vArg3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3);
ebBOOL fArg4 = BoolArg (lpArgs, OBJARG4, ebFALSE, iNumArgs);

	SetDaoObject (lpArgs, idx.CreateProperty (str1, iArg2, &vArg3, fArg4));
}

// -------------------------------------------------------------------------------
// Index_Fields_propget
// -------------------------------------------------------------------------------
void Index_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex idx (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetDaoObject (lpArgs, idx.Fields);
}

// -------------------------------------------------------------------------------
// Container_Inherit_propget
// -------------------------------------------------------------------------------
void Container_Inherit_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	SetBool (lpArgs, cont.GetInherit());
}

// -------------------------------------------------------------------------------
// Container_Inherit_propset
// -------------------------------------------------------------------------------
void Container_Inherit_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	cont.SetInherit (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Container_Owner_propget
// -------------------------------------------------------------------------------
void Container_Owner_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	SetString (hThread, lpArgs, cont.GetOwner());
}

// -------------------------------------------------------------------------------
// Container_Owner_propset
// -------------------------------------------------------------------------------
void Container_Owner_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	cont.SetOwner (str);
}

// -------------------------------------------------------------------------------
// Container_Permissions_propget
// -------------------------------------------------------------------------------
void Container_Permissions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, cont.GetPermissions());
}

// -------------------------------------------------------------------------------
// Container_Permissions_propset
// -------------------------------------------------------------------------------
void Container_Permissions_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	cont.SetPermissions (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Container_UserName_propget
// -------------------------------------------------------------------------------
void Container_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	SetString (hThread, lpArgs, cont.GetUserName());
}

// -------------------------------------------------------------------------------
// Container_UserName_propset
// -------------------------------------------------------------------------------
void Container_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	cont.SetUserName (str);
}

// -------------------------------------------------------------------------------
// Container_Documents_propget
// -------------------------------------------------------------------------------
void Container_Documents_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer cont (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	SetDaoObject (lpArgs, cont.Documents);
}

// -------------------------------------------------------------------------------
// Document_Container_propset
// -------------------------------------------------------------------------------
void Document_Container_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	SetString (hThread, lpArgs, doc.GetContainer());
}

// -------------------------------------------------------------------------------
// Document_Owner_propget
// -------------------------------------------------------------------------------
void Document_Owner_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	SetString (hThread, lpArgs, doc.GetOwner());
}

// -------------------------------------------------------------------------------
// Document_Owner_propset
// -------------------------------------------------------------------------------
void Document_Owner_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	doc.SetOwner (str);
}

// -------------------------------------------------------------------------------
// Document_Permissions_propget
// -------------------------------------------------------------------------------
void Document_Permissions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, doc.GetPermissions());
}

// -------------------------------------------------------------------------------
// Document_Permissions_propset
// -------------------------------------------------------------------------------
void Document_Permissions_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	doc.SetPermissions (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Document_DateCreated_propget
// -------------------------------------------------------------------------------
void Document_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);
COleVariant vOle = doc.GetDateCreated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Document_LastUpdated_propget
// -------------------------------------------------------------------------------
void Document_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);
COleVariant vOle = doc.GetLastUpdated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Document_UserName_propget
// -------------------------------------------------------------------------------
void Document_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	SetString (hThread, lpArgs, doc.GetUserName());
}

// -------------------------------------------------------------------------------
// Document_UserName_propset
// -------------------------------------------------------------------------------
void Document_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument doc (GetDaoObject(lpArgs, (DAODocument *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	doc.SetUserName (str);
}

// -------------------------------------------------------------------------------
// QueryDef_Connect_propget
// -------------------------------------------------------------------------------
void QueryDef_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetString (hThread, lpArgs, qdef.GetConnect());
}

// -------------------------------------------------------------------------------
// QueryDef_Connect_propset
// -------------------------------------------------------------------------------
void QueryDef_Connect_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	qdef.SetConnect (str);
}

// -------------------------------------------------------------------------------
// QueryDef_DateCreated_propget
// -------------------------------------------------------------------------------
void QueryDef_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
COleVariant vOle = qdef.GetDateCreated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// QueryDef_LastUpdated_propget
// -------------------------------------------------------------------------------
void QueryDef_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
COleVariant vOle = qdef.GetLastUpdated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// QueryDef_Type_propget
// -------------------------------------------------------------------------------
void QueryDef_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, qdef.GetType());
}

// -------------------------------------------------------------------------------
// QueryDef_ODBCTimeout_propget
// -------------------------------------------------------------------------------
void QueryDef_ODBCTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, qdef.GetODBCTimeout());
}

// -------------------------------------------------------------------------------
// QueryDef_ODBCTimeout_propset
// -------------------------------------------------------------------------------
void QueryDef_ODBCTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	qdef.SetODBCTimeout (ebGetInt (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// QueryDef_RecordsAffected_propget
// -------------------------------------------------------------------------------
void QueryDef_RecordsAffected_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetBool (lpArgs, qdef.GetRecordsAffected());
}

// -------------------------------------------------------------------------------
// QueryDef_ReturnsRecords_propget
// -------------------------------------------------------------------------------
void QueryDef_ReturnsRecords_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetBool (lpArgs, qdef.GetReturnsRecords());
}

// -------------------------------------------------------------------------------
// QueryDef_ReturnsRecords_propset
// -------------------------------------------------------------------------------
void QueryDef_ReturnsRecords_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	qdef.SetReturnsRecords (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// QueryDef_SQL_propget
// -------------------------------------------------------------------------------
void QueryDef_SQL_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetString (hThread, lpArgs, qdef.GetSQL());
}

// -------------------------------------------------------------------------------
// QueryDef_SQL_propset
// -------------------------------------------------------------------------------
void QueryDef_SQL_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	qdef.SetSQL (str);
}

// -------------------------------------------------------------------------------
// QueryDef_Updateable_propget
// -------------------------------------------------------------------------------
void QueryDef_Updateable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetBool (lpArgs, qdef.GetUpdatable());
}

// -------------------------------------------------------------------------------
// QueryDef_CreateProperty_function
// -------------------------------------------------------------------------------
void QueryDef_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
COleVariant vArg3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3);
ebBOOL fArg4 = BoolArg (lpArgs, OBJARG4, ebFALSE, iNumArgs);

	SetDaoObject (lpArgs, qdef.CreateProperty (str1, iArg2, &vArg3, fArg4));
}

// -------------------------------------------------------------------------------
// QueryDef_Execute_command
// -------------------------------------------------------------------------------
void QueryDef_Execute_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
int iArg = IntArg (lpArgs, OBJARG1, -1, iNumArgs);

	qdef.Execute (iArg);
}

// -------------------------------------------------------------------------------
// QueryDef_OpenRecordSet_function
// -------------------------------------------------------------------------------
void QueryDef_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
int iArg1 = IntArg (lpArgs, OBJARG1, -1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);

	SetDaoObject (lpArgs, qdef.OpenRecordset (iArg1, iArg2));
}

// -------------------------------------------------------------------------------
// QueryDef_Fields_propget
// -------------------------------------------------------------------------------
void QueryDef_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetDaoObject (lpArgs, qdef.Fields);
}

// -------------------------------------------------------------------------------
// QueryDef_Parameters_propget
// -------------------------------------------------------------------------------
void QueryDef_Parameters_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetDaoObject (lpArgs, qdef.Parameters);
}

// -------------------------------------------------------------------------------
// RecordSet_AbsolutePosition_propget
// -------------------------------------------------------------------------------
void RecordSet_AbsolutePosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, rset.GetAbsolutePosition());
}

// -------------------------------------------------------------------------------
// RecordSet_AbsolutePosition_propset
// -------------------------------------------------------------------------------
void RecordSet_AbsolutePosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.SetAbsolutePosition (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// RecordSet_BOF_propget
// -------------------------------------------------------------------------------
void RecordSet_BOF_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetBOF());
}

// -------------------------------------------------------------------------------
// RecordSet_Bookmark_propget
// -------------------------------------------------------------------------------
void RecordSet_Bookmark_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_Bookmark_propset
// -------------------------------------------------------------------------------
void RecordSet_Bookmark_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_Bookmarkable_propget
// -------------------------------------------------------------------------------
void RecordSet_Bookmarkable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetBookmarkable());
}

// -------------------------------------------------------------------------------
// RecordSet_CacheSize_propget
// -------------------------------------------------------------------------------
void RecordSet_CacheSize_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, rset.GetCacheSize());
}

// -------------------------------------------------------------------------------
// RecordSet_CacheSize_propset
// -------------------------------------------------------------------------------
void RecordSet_CacheSize_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.SetCacheSize (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// RecordSet_CacheStart_propget
// -------------------------------------------------------------------------------
void RecordSet_CacheStart_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_CacheStart_propset
// -------------------------------------------------------------------------------
void RecordSet_CacheStart_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_DateCreated_propget
// -------------------------------------------------------------------------------
void RecordSet_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
COleVariant vOle = rset.GetDateCreated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// RecordSet_EditMode_propget
// -------------------------------------------------------------------------------
void RecordSet_EditMode_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, rset.GetEditMode());
}

// -------------------------------------------------------------------------------
// RecordSet_EOF_propget
// -------------------------------------------------------------------------------
void RecordSet_EOF_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetEOF());
}

// -------------------------------------------------------------------------------
// RecordSet_Filter_propget
// -------------------------------------------------------------------------------
void RecordSet_Filter_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, rset.GetFilter());
}

// -------------------------------------------------------------------------------
// RecordSet_Filter_propset
// -------------------------------------------------------------------------------
void RecordSet_Filter_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

CStrArg str (hThread, lpArgs, OBJARG1);

	rset.SetFilter (str);
}

// -------------------------------------------------------------------------------
// RecordSet_Index_propget
// -------------------------------------------------------------------------------
void RecordSet_Index_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, rset.GetIndex());
}

// -------------------------------------------------------------------------------
// RecordSet_Index_propset
// -------------------------------------------------------------------------------
void RecordSet_Index_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.SetIndex (str);
}

// -------------------------------------------------------------------------------
// RecordSet_LastModified_propget
// -------------------------------------------------------------------------------
void RecordSet_LastModified_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_LastUpdated_propget
// -------------------------------------------------------------------------------
void RecordSet_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
COleVariant vOle = rset.GetLastUpdated();
ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// RecordSet_LockEdits_propget
// -------------------------------------------------------------------------------
void RecordSet_LockEdits_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetLockEdits());
}

// -------------------------------------------------------------------------------
// RecordSet_LockEdits_propset
// -------------------------------------------------------------------------------
void RecordSet_LockEdits_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.SetLockEdits (GetBool (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// RecordSet_NoMatch_propget
// -------------------------------------------------------------------------------
void RecordSet_NoMatch_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetNoMatch());
}

// -------------------------------------------------------------------------------
// RecordSet_PercentPosition_propget
// -------------------------------------------------------------------------------
void RecordSet_PercentPosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetSingle (lpArgs, RETURNVAL, rset.GetPercentPosition());
}

// -------------------------------------------------------------------------------
// RecordSet_PercentPosition_propset
// -------------------------------------------------------------------------------
void RecordSet_PercentPosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.SetPercentPosition (ebGetSingle (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// RecordSet_RecordCount_propget
// -------------------------------------------------------------------------------
void RecordSet_RecordCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, rset.GetRecordCount());
}

// -------------------------------------------------------------------------------
// RecordSet_Restartable_propget
// -------------------------------------------------------------------------------
void RecordSet_Restartable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetRestartable());
}

// -------------------------------------------------------------------------------
// RecordSet_Sort_propget
// -------------------------------------------------------------------------------
void RecordSet_Sort_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, rset.GetSort());
}

// -------------------------------------------------------------------------------
// RecordSet_Sort_propset
// -------------------------------------------------------------------------------
void RecordSet_Sort_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.SetSort (str);
}

// -------------------------------------------------------------------------------
// RecordSet_Transactions_propget
// -------------------------------------------------------------------------------
void RecordSet_Transactions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetTransactions());
}

// -------------------------------------------------------------------------------
// RecordSet_Type_propget
// -------------------------------------------------------------------------------
void RecordSet_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, rset.GetType());
}

// -------------------------------------------------------------------------------
// RecordSet_Updatable_propget
// -------------------------------------------------------------------------------
void RecordSet_Updatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetBool (lpArgs, rset.GetUpdatable());
}

// -------------------------------------------------------------------------------
// RecordSet_ValidationRule_propget
// -------------------------------------------------------------------------------
void RecordSet_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, rset.GetValidationRule());
}

// -------------------------------------------------------------------------------
// RecordSet_ValidationText_propget
// -------------------------------------------------------------------------------
void RecordSet_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, rset.GetValidationText());
}

// -------------------------------------------------------------------------------
// RecordSet_AddNew_command
// -------------------------------------------------------------------------------
void RecordSet_AddNew_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.AddNew();
}

// -------------------------------------------------------------------------------
// RecordSet_CancelUpdate_command
// -------------------------------------------------------------------------------
void RecordSet_CancelUpdate_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.CancelUpdate();
}

// -------------------------------------------------------------------------------
// RecordSet_Clone_function
// -------------------------------------------------------------------------------
void RecordSet_Clone_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetDaoObject (lpArgs, rset.Clone());
}

// -------------------------------------------------------------------------------
// RecordSet_Close_command
// -------------------------------------------------------------------------------
void RecordSet_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.Close();
}

// -------------------------------------------------------------------------------
// RecordSet_CopyQueryDef_function
// -------------------------------------------------------------------------------
void RecordSet_CopyQueryDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetDaoObject (lpArgs, rset.CopyQueryDef());
}

// -------------------------------------------------------------------------------
// RecordSet_Delete_command
// -------------------------------------------------------------------------------
void RecordSet_Delete_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.Delete();
}

// -------------------------------------------------------------------------------
// RecordSet_Edit_command
// -------------------------------------------------------------------------------
void RecordSet_Edit_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.Edit();
}

// -------------------------------------------------------------------------------
// RecordSet_FillCache_command
// -------------------------------------------------------------------------------
void RecordSet_FillCache_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_FindFirst_command
// -------------------------------------------------------------------------------
void RecordSet_FindFirst_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.FindFirst (str);
}

// -------------------------------------------------------------------------------
// RecordSet_FindLast_command
// -------------------------------------------------------------------------------
void RecordSet_FindLast_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.FindLast (str);
}

// -------------------------------------------------------------------------------
// RecordSet_FindNext_command
// -------------------------------------------------------------------------------
void RecordSet_FindNext_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.FindNext (str);
}

// -------------------------------------------------------------------------------
// RecordSet_FindPrevious_command
// -------------------------------------------------------------------------------
void RecordSet_FindPrevious_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rset.FindPrevious (str);
}

// -------------------------------------------------------------------------------
// RecordSet_GetRows_function
// -------------------------------------------------------------------------------
void RecordSet_GetRows_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_Move_command
// -------------------------------------------------------------------------------
void RecordSet_Move_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	Dao_not_supported (hThread, iNumArgs, lpArgs);
}

// -------------------------------------------------------------------------------
// RecordSet_MoveFirst_command
// -------------------------------------------------------------------------------
void RecordSet_MoveFirst_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.MoveFirst();
}

// -------------------------------------------------------------------------------
// RecordSet_MoveLast_command
// -------------------------------------------------------------------------------
void RecordSet_MoveLast_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.MoveLast();
}

// -------------------------------------------------------------------------------
// RecordSet_MoveNext_command
// -------------------------------------------------------------------------------
void RecordSet_MoveNext_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.MoveNext();
}

// -------------------------------------------------------------------------------
// RecordSet_MovePrevious_command
// -------------------------------------------------------------------------------
void RecordSet_MovePrevious_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.MovePrevious();
}

// -------------------------------------------------------------------------------
// RecordSet_OpenRecordSet_function
// -------------------------------------------------------------------------------
void RecordSet_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
int iArg1 = IntArg (lpArgs, OBJARG1, -1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);

	SetDaoObject (lpArgs, rset.OpenRecordset (iArg1, iArg2));
}

// -------------------------------------------------------------------------------
// RecordSet_Requery_command
// -------------------------------------------------------------------------------
void RecordSet_Requery_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CdbQueryDef qdef (GetDaoObject(lpArgs, (DAOQueryDef *)NULL, OBJARG1), true);

	rset.Requery (&qdef);
}

// -------------------------------------------------------------------------------
// RecordSet_Seek_command
// -------------------------------------------------------------------------------
void RecordSet_Seek_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);
COleVariant v1 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG2, false);
COleVariant v2 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3, false);
COleVariant v3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG4, false);
COleVariant v4 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG5, false);
COleVariant v5 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG6, false);
COleVariant v6 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG7, false);
COleVariant v7 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG8, false);
COleVariant v8 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG9, false);
COleVariant v9 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG10, false);
COleVariant v10 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG11, false);
COleVariant v11 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG12, false);
COleVariant v12 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG13, false);
COleVariant v13 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG14, false);

	rset.Seek (str, iNumArgs-2, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
}

// -------------------------------------------------------------------------------
// RecordSet_Seek_command
// -------------------------------------------------------------------------------
void RecordSet_Seek3Keys_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);
COleVariant v1 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG2, false);
COleVariant v2 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG3, false);
COleVariant v3 = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG4, false);

	rset.Seek (str, iNumArgs-2, v1, v2, v3);
}

// -------------------------------------------------------------------------------
// RecordSet_Update_command
// -------------------------------------------------------------------------------
void RecordSet_Update_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	rset.Update();
}

// -------------------------------------------------------------------------------
// RecordSet_Fields_propget
// -------------------------------------------------------------------------------
void RecordSet_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset rset (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetDaoObject (lpArgs, rset.Fields);
}

// -------------------------------------------------------------------------------
// Parameter_Type_propget
// -------------------------------------------------------------------------------
void Parameter_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter par (GetDaoObject(lpArgs, (DAOParameter *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, par.GetType());
}

// -------------------------------------------------------------------------------
// Parameter_Value_propget
// -------------------------------------------------------------------------------
void Parameter_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter par (GetDaoObject(lpArgs, (DAOParameter *)NULL), true);
COleVariant vOle = par.GetValue();

ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Parameter_Value_propset
// -------------------------------------------------------------------------------
void Parameter_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter par (GetDaoObject(lpArgs, (DAOParameter *)NULL), true);
COleVariant v = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1);

	par.SetValue (&v);
}

// -------------------------------------------------------------------------------
// Property_Type_propget
// -------------------------------------------------------------------------------
void Property_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbProperty prop (GetDaoObject(lpArgs, (DAOProperty *)NULL), true);

	ebSetInt (lpArgs, RETURNVAL, prop.GetType());
}

// -------------------------------------------------------------------------------
// Property_Type_propset
// -------------------------------------------------------------------------------
void Property_Type_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbProperty prop (GetDaoObject(lpArgs, (DAOProperty *)NULL), true);

	prop.SetType (ebGetInt (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Property_Value_propget
// -------------------------------------------------------------------------------
void Property_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbProperty prop (GetDaoObject(lpArgs, (DAOProperty *)NULL), true);
COleVariant vOle = prop.GetValue();

ebVARIANT v;

	ebGetVariantEx (lpArgs, 0, &v);
	ebFreeVariant (hThread, &v);

	v = MakeebVARIANT (hThread, vOle);
	ebSetVariant (lpArgs, 0, &v);
}

// -------------------------------------------------------------------------------
// Property_Value_propset
// -------------------------------------------------------------------------------
void Property_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbProperty prop (GetDaoObject(lpArgs, (DAOProperty *)NULL), true);
COleVariant v = MakeVARIANT (hThread, iNumArgs, lpArgs, OBJARG1);

	prop.SetValue (&v);
}

// -------------------------------------------------------------------------------
// Property_Inherited_propget
// -------------------------------------------------------------------------------
void Property_Inherited_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbProperty prop (GetDaoObject(lpArgs, (DAOProperty *)NULL), true);

	SetBool (lpArgs, prop.GetInherited());
}

// -------------------------------------------------------------------------------
// Relation_Attributes_propget
// -------------------------------------------------------------------------------
void Relation_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	ebSetLong (lpArgs, RETURNVAL, rel.GetAttributes());
}

// -------------------------------------------------------------------------------
// Relation_Attributes_propset
// -------------------------------------------------------------------------------
void Relation_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	rel.SetAttributes (ebGetLong (lpArgs, OBJARG1));
}

// -------------------------------------------------------------------------------
// Relation_ForeignTable_propget
// -------------------------------------------------------------------------------
void Relation_ForeignTable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	SetString (hThread, lpArgs, rel.GetForeignTable());
}

// -------------------------------------------------------------------------------
// Relation_ForeignTable_propset
// -------------------------------------------------------------------------------
void Relation_ForeignTable_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rel.SetForeignTable (str);
}

// -------------------------------------------------------------------------------
// Relation_Table_propget
// -------------------------------------------------------------------------------
void Relation_Table_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	SetString (hThread, lpArgs, rel.GetTable());
}

// -------------------------------------------------------------------------------
// Relation_Table_propset
// -------------------------------------------------------------------------------
void Relation_Table_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	rel.SetTable (str);
}

// -------------------------------------------------------------------------------
// Relation_CreateField_function
// -------------------------------------------------------------------------------
void Relation_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
int iArg2 = IntArg (lpArgs, OBJARG2, -1, iNumArgs);
int iArg3 = IntArg (lpArgs, OBJARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, rel.CreateField (str1, iArg2, iArg3));
}

// -------------------------------------------------------------------------------
// Relation_Fields_propget
// -------------------------------------------------------------------------------
void Relation_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation rel (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	SetDaoObject (lpArgs, rel.Fields);
}

// -------------------------------------------------------------------------------
// Group_PID_propset
// -------------------------------------------------------------------------------
void Group_PID_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup grp (GetDaoObject(lpArgs, (DAOGroup *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	grp.SetPID (str);
}

// -------------------------------------------------------------------------------
// Group_CreateUser_function
// -------------------------------------------------------------------------------
void Group_CreateUser_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup grp (GetDaoObject(lpArgs, (DAOGroup *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);
CStrArg str3 (hThread, lpArgs, OBJARG3, iNumArgs);

	SetDaoObject (lpArgs, grp.CreateUser (str1, str2, str3));
}

// -------------------------------------------------------------------------------
// Group_Users_propget
// -------------------------------------------------------------------------------
void Group_Users_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup grp (GetDaoObject(lpArgs, (DAOGroup *)NULL), true);

	SetDaoObject (lpArgs, grp.Users);
}

// -------------------------------------------------------------------------------
// User_PID_propset
// -------------------------------------------------------------------------------
void User_PID_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser user (GetDaoObject(lpArgs, (DAOUser *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	user.SetPID (str);
}

// -------------------------------------------------------------------------------
// User_Password_propset
// -------------------------------------------------------------------------------
void User_Password_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser user (GetDaoObject(lpArgs, (DAOUser *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	user.SetPassword (str);
}

// -------------------------------------------------------------------------------
// User_CreateGroup_function
// -------------------------------------------------------------------------------
void User_CreateGroup_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser user (GetDaoObject(lpArgs, (DAOUser *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, OBJARG2, iNumArgs);

	SetDaoObject (lpArgs, user.CreateGroup (str1, str2));
}

// -------------------------------------------------------------------------------
// User_NewPassword_command
// -------------------------------------------------------------------------------
void User_NewPassword_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser user (GetDaoObject(lpArgs, (DAOUser *)NULL), true);
CStrArg str1 (hThread, lpArgs, OBJARG1);
CStrArg str2 (hThread, lpArgs, OBJARG2);

	user.NewPassword (str1, str2);
}

// -------------------------------------------------------------------------------
// User_Groups_propget
// -------------------------------------------------------------------------------
void User_Groups_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser user (GetDaoObject(lpArgs, (DAOUser *)NULL), true);

	SetDaoObject (lpArgs, user.Groups);
}

///////////////////////////////////////////////////////////////////////////////
// Methods for Workspaces(0) - the default workspace
// -------------------------------------------------------------------------------
// BeginTrans_protocmd
// -------------------------------------------------------------------------------
void BeginTrans_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];

	wrk.BeginTrans();
}

// -------------------------------------------------------------------------------
// CommitTrans_protocmd
// -------------------------------------------------------------------------------
void CommitTrans_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];

	wrk.CommitTrans();
}

// -------------------------------------------------------------------------------
// RollBack_protocmd
// -------------------------------------------------------------------------------
void RollBack_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];

	wrk.Rollback();
}

// -------------------------------------------------------------------------------
// CreateDatabase_protofunc
// -------------------------------------------------------------------------------
void CreateDatabase_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];
CStrArg str1 (hThread, lpArgs, CMDARG1);
CStrArg str2 (hThread, lpArgs, CMDARG2);
int iArg3 = IntArg (lpArgs, CMDARG3, -1, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateDatabase (str1, str2, iArg3));
}

// -------------------------------------------------------------------------------
// CreateGroup_protofunc
// -------------------------------------------------------------------------------
void CreateGroup_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];
CStrArg str1 (hThread, lpArgs, CMDARG1);
CStrArg str2 (hThread, lpArgs, CMDARG2, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateGroup (str1, str2));
}

// -------------------------------------------------------------------------------
// CreateUser_protofunc
// -------------------------------------------------------------------------------
void CreateUser_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];
CStrArg str1 (hThread, lpArgs, CMDARG1, iNumArgs);
CStrArg str2 (hThread, lpArgs, CMDARG2, iNumArgs);
CStrArg str3 (hThread, lpArgs, CMDARG3, iNumArgs);

	SetDaoObject (lpArgs, wrk.CreateUser (str1, str2, str3));
}

// -------------------------------------------------------------------------------
// OpenDatabase_protofunc
// -------------------------------------------------------------------------------
void OpenDatabase_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	DBEngine() -> Workspaces.GetDelayedInterface();

CdbWorkspace wrk = DBEngine() -> Workspaces[0L];
CStrArg str1 (hThread, lpArgs, CMDARG1);
ebBOOL fArg2 = BoolArg (lpArgs, CMDARG2, ebFALSE, iNumArgs);
ebBOOL fArg3 = BoolArg (lpArgs, CMDARG3, ebFALSE, iNumArgs);
CStrArg str4 (hThread, lpArgs, CMDARG4, iNumArgs);

	SetDaoObject (lpArgs, wrk.OpenDatabase (str1, fArg2, fArg3, str4));
}

// -------------------------------------------------------------------------------
// Workspace_Name_propget
// -------------------------------------------------------------------------------
void Workspace_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace DaoObjekt (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Workspace_Name_propset
// -------------------------------------------------------------------------------
void Workspace_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace DaoObjekt (GetDaoObject(lpArgs, (DAOWorkspace *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Database_Name_propget
// -------------------------------------------------------------------------------
void Database_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase DaoObjekt (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Database_Name_propset
// -------------------------------------------------------------------------------
void Database_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase DaoObjekt (GetDaoObject(lpArgs, (DAODatabase *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// QueryDef_Name_propget
// -------------------------------------------------------------------------------
void QueryDef_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef DaoObjekt (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// QueryDef_Name_propset
// -------------------------------------------------------------------------------
void QueryDef_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef DaoObjekt (GetDaoObject(lpArgs, (DAOQueryDef *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Parameter_Name_propget
// -------------------------------------------------------------------------------
void Parameter_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter DaoObjekt (GetDaoObject(lpArgs, (DAOParameter *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Parameter_Name_propset
// -------------------------------------------------------------------------------
void Parameter_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter DaoObjekt (GetDaoObject(lpArgs, (DAOParameter *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Recordset_Name_propget
// -------------------------------------------------------------------------------
void RecordSet_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset DaoObjekt (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Recordset_Name_propset
// -------------------------------------------------------------------------------
void RecordSet_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset DaoObjekt (GetDaoObject(lpArgs, (DAORecordset *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Index_Name_propget
// -------------------------------------------------------------------------------
void Index_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex DaoObjekt (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Index_Name_propset
// -------------------------------------------------------------------------------
void Index_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex DaoObjekt (GetDaoObject(lpArgs, (DAOIndex *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Relation_Name_propget
// -------------------------------------------------------------------------------
void Relation_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation DaoObjekt (GetDaoObject(lpArgs, (DAORelation *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Relation_Name_propset
// -------------------------------------------------------------------------------
void Relation_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation DaoObjekt (GetDaoObject(lpArgs, (DAORelation *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Container_Name_propget
// -------------------------------------------------------------------------------
void Container_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer DaoObjekt (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Container_Name_propset
// -------------------------------------------------------------------------------
void Container_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer DaoObjekt (GetDaoObject(lpArgs, (DAOContainer *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Document_Name_propget
// -------------------------------------------------------------------------------
void Document_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument DaoObjekt (GetDaoObject(lpArgs, (DAODocument *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Document_Name_propset
// -------------------------------------------------------------------------------
void Document_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument DaoObjekt (GetDaoObject(lpArgs, (DAODocument *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// User_Name_propget
// -------------------------------------------------------------------------------
void User_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser DaoObjekt (GetDaoObject(lpArgs, (DAOUser *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// User_Name_propset
// -------------------------------------------------------------------------------
void User_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser DaoObjekt (GetDaoObject(lpArgs, (DAOUser *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// -------------------------------------------------------------------------------
// Group_Name_propget
// -------------------------------------------------------------------------------
void Group_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup DaoObjekt (GetDaoObject(lpArgs, (DAOGroup *)NULL), true);

	SetString (hThread, lpArgs, DaoObjekt.GetName());
}

// -------------------------------------------------------------------------------
// Group_Name_propset
// -------------------------------------------------------------------------------
void Group_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup DaoObjekt (GetDaoObject(lpArgs, (DAOGroup *)NULL), true);
CStrArg str (hThread, lpArgs, OBJARG1);

	DaoObjekt.SetName (str);
}

// ----------------------------------------------------------------------------
// DBEngine_Properties_propget
// ----------------------------------------------------------------------------
void DBEngine_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDBEngine DaoObj (GetDaoObject (lpArgs, (DAODBEngine *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Workspace_Properties_propget
// ----------------------------------------------------------------------------
void Workspace_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbWorkspace DaoObj (GetDaoObject (lpArgs, (DAOWorkspace *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Database_Properties_propget
// ----------------------------------------------------------------------------
void Database_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDatabase DaoObj (GetDaoObject (lpArgs, (DAODatabase *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// QueryDef_Properties_propget
// ----------------------------------------------------------------------------
void QueryDef_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbQueryDef DaoObj (GetDaoObject (lpArgs, (DAOQueryDef *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Parameter_Properties_propget
// ----------------------------------------------------------------------------
void Parameter_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbParameter DaoObj (GetDaoObject (lpArgs, (DAOParameter *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Recordset_Properties_propget
// ----------------------------------------------------------------------------
void RecordSet_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRecordset DaoObj (GetDaoObject (lpArgs, (DAORecordset *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Index_Properties_propget
// ----------------------------------------------------------------------------
void Index_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbIndex DaoObj (GetDaoObject (lpArgs, (DAOIndex *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Relation_Properties_propget
// ----------------------------------------------------------------------------
void Relation_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbRelation DaoObj (GetDaoObject (lpArgs, (DAORelation *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Container_Properties_propget
// ----------------------------------------------------------------------------
void Container_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbContainer DaoObj (GetDaoObject (lpArgs, (DAOContainer *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Document_Properties_propget
// ----------------------------------------------------------------------------
void Document_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbDocument DaoObj (GetDaoObject (lpArgs, (DAODocument *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// User_Properties_propget
// ----------------------------------------------------------------------------
void User_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbUser DaoObj (GetDaoObject (lpArgs, (DAOUser *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

// ----------------------------------------------------------------------------
// Group_Properties_propget
// ----------------------------------------------------------------------------
void Group_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CdbGroup DaoObj (GetDaoObject (lpArgs, (DAOGroup *)NULL), true);

	SetDaoObject (lpArgs, DaoObj.Properties);
}

///////////////////////////////////////////////////////////////////////////////
// For...Each support

template<typename InterfaceT>
void GenericNewEnum(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
WUnknown Unk;
HRESULT hr = ((InterfaceT *)ebGetObject(lpArgs, OBJTARGET)) -> _NewEnum(Unk.ppi());

	ebSetObject (lpArgs, RETURNVAL, NULL);
	if (SUCCEEDED(hr)) {
		COM_TRY {
		WEnumVARIANT Enum (Unk);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)Enum.detach());
		} 
		COM_CATCH_NORETURN_OP(
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		);
	}
}

template<typename InterfaceT, IID const *piid>
void GenericNextItem(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CComVariant v;
__Interface<InterfaceT, __CIID<piid> > Item;
HRESULT hr = ((IEnumVARIANT *)ebGetObject(lpArgs, OBJTARGET)) -> Next(1, &v, NULL); 

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		if (FAILED(v.ChangeType(VT_DISPATCH)))
			return;

		if (SUCCEEDED(V_DISPATCH(&v) -> QueryInterface (Item.GetIID(), Item.ppv())))
			ebSetObject(lpArgs, RETURNVAL, (ebDWORD)Item.detach());
	}
}

// ----------------------------------------------------------------------------
// WorkSpaces_NewEnum_propget
// ----------------------------------------------------------------------------
void WorkSpaces_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOWorkspaces>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// WorkSpace_Next_propget
// ----------------------------------------------------------------------------
void WorkSpace_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOWorkspace, &IID_IDAOWorkspace>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Errors_NewEnum_propget
// ----------------------------------------------------------------------------
void Errors_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOErrors>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Error_Next_propget
// ----------------------------------------------------------------------------
void Error_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOError, &IID_IDAOError>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Databases_NewEnum_propget
// ----------------------------------------------------------------------------
void Databases_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAODatabases>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Database_Next_propget
// ----------------------------------------------------------------------------
void Database_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAODatabase, &IID_IDAODatabase>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// TableDefs_NewEnum_propget
// ----------------------------------------------------------------------------
void TableDefs_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOTableDefs>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// TableDef_Next_propget
// ----------------------------------------------------------------------------
void TableDef_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOTableDef, &IID_IDAOTableDef>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Fields_NewEnum_propget
// ----------------------------------------------------------------------------
void Fields_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOFields>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Field_Next_propget
// ----------------------------------------------------------------------------
void Field_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOField, &IID_IDAOField>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Indexes_NewEnum_propget
// ----------------------------------------------------------------------------
void Indexes_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOIndexes>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Index_Next_propget
// ----------------------------------------------------------------------------
void Index_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOIndex, &IID_IDAOIndex>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Containers_NewEnum_propget
// ----------------------------------------------------------------------------
void Containers_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOContainers>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Container_Next_propget
// ----------------------------------------------------------------------------
void Container_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOContainer, &IID_IDAOContainer>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Documents_NewEnum_propget
// ----------------------------------------------------------------------------
void Documents_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAODocuments>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Document_Next_propget
// ----------------------------------------------------------------------------
void Document_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAODocument, &IID_IDAODocument>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// QueryDefs_NewEnum_propget
// ----------------------------------------------------------------------------
void QueryDefs_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOQueryDefs>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// QueryDef_Next_propget
// ----------------------------------------------------------------------------
void QueryDef_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOQueryDef, &IID_IDAOQueryDef>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// RecordSets_NewEnum_propget
// ----------------------------------------------------------------------------
void RecordSets_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAORecordsets>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// RecordSet_Next_propget
// ----------------------------------------------------------------------------
void RecordSet_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAORecordset, &IID_IDAORecordset>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Parameters_NewEnum_propget
// ----------------------------------------------------------------------------
void Parameters_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOParameters>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Parameter_Next_propget
// ----------------------------------------------------------------------------
void Parameter_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOParameter, &IID_IDAOParameter>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Properties_NewEnum_propget
// ----------------------------------------------------------------------------
void Properties_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOProperties>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Property_Next_propget
// ----------------------------------------------------------------------------
void Property_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOProperty, &IID_IDAOProperty>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Relations_NewEnum_propget
// ----------------------------------------------------------------------------
void Relations_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAORelations>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Relation_Next_propget
// ----------------------------------------------------------------------------
void Relation_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAORelation, &IID_IDAORelation>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Groups_NewEnum_propget
// ----------------------------------------------------------------------------
void Groups_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOGroups>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Group_Next_propget
// ----------------------------------------------------------------------------
void Group_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOGroup, &IID_IDAOGroup>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// Users_NewEnum_propget
// ----------------------------------------------------------------------------
void Users_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNewEnum<DAOUsers>(hThread, iNumArgs, lpArgs);
}

// ----------------------------------------------------------------------------
// User_Next_propget
// ----------------------------------------------------------------------------
void User_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	GenericNextItem<DAOUser, &IID_IDAOUser>(hThread, iNumArgs, lpArgs);
}

///////////////////////////////////////////////////////////////////////////////
// Fehlerbehandlung
void HandleDAOError (ebHTHREAD hThread, LONG lError)
{
CdbDBEngine *pDAO = DBEngine (false);
CString stError = TEXT("");
int iFirstErr = 0;

	if (NULL != pDAO) {
		if (0 == lError) {
		int cError = DBEngine() -> Errors.GetCount();

			for (long iError = 0; iError < cError; iError++) {
			CdbError rError = DBEngine() -> Errors[iError];

				if (0 == iError)
					iFirstErr = rError.GetNumber();
				stError += rError.GetDescription();
				stError += TEXT("\n");
			}
		} else {
			TRY {
				stError.LoadString ((UINT)lError);
			} CATCH (CMemoryException, e) {
				stError = "Out of memory.";
			} END_CATCH
			iFirstErr = lError;
		}
	} else {	// Initialisierungsfehler der DAO-Engine
		TRY {
			iFirstErr = IDS_DAOINITERROR;
			stError.LoadString (IDS_DAOINITERROR);
		} CATCH (CMemoryException, e) {
			stError = "Out of memory.";
		} END_CATCH
	}

	if (stError.IsEmpty()) {
		iFirstErr = TRIASERR_DAOGENERICERROR;
		TRY {
			stError.LoadString (TRIASERR_DAOGENERICERROR);
		} CATCH (CMemoryException, e) {
			stError = "Out of memory.";
		} END_CATCH
	}

// Fehler in Form einer MsgBox melden oder 'On Error' rufen
	ebRuntimeError (hThread, false, iFirstErr, stError);

	ASSERT(false);		// darf nicht hierhin zurückkehren
}

void HandleBscriptError (ebHTHREAD hThread, LONG lError)
{
	throw lError;
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// This routine is the entry point used by the EBRUN.DLL module to execute 
// an external routine.
//
// parameters:	hThread		pointer to reserved structure
//			wCmdNum		ID of the extension routine as it appears in the
//						prototype table
//			iNumArgs	number of OBJARGs passed to this routine
//			lpArgs		pointer to an array of pointers to the OBJARGs
//
// returns:		nothing
// ----------------------------------------------------------------------------
extern "C" 
__declspec(dllexport) void ebCALLBACK RuntimeCallback (ebHTHREAD hThread, WORD wCmdNum, int iNumArgs, ebARGS lpArgs)
{
bool fError = false;
LONG lError = 0L;

	try {
	// call the extension routine via the jump table
		if (wCmdNum >= g_iExtFcnsOffset && wCmdNum < g_iExtFcnsLast)
			(*g_pExtFcns[wCmdNum - g_iExtFcnsOffset])(hThread, iNumArgs, lpArgs);
		else 
			Dao_not_supported (hThread, iNumArgs, lpArgs);
	} catch (CdbException) {
	// Fehlerbehandlung rufen
		fError = true;
	} catch (int lThrownError) {
		lError = lThrownError;
		fError = true;
	} catch(...) {
		lError = TRIASERR_DAOGENERICERROR;
		fError = true;
	}

	if (fError)	{
		HandleDAOError (hThread, lError);
		// ... kehrt nicht zurück
	}
}


// --------------------------------------------------------------------------
// Init - this routine is called when the DLL is loaded. If this routine
// returns FALSE, then the extension will not be loaded. 
//
// parameters:	none
//
// returns:		true		success initializing
//			false		unable to initialize
// --------------------------------------------------------------------------
extern "C" 
__declspec(dllexport) bool ebCALLBACK Init (ebHINSTANCE hInst)
{
// DAO funktioniert nicht unter Win32s
	CalcVersion();
	if (IsWin32s())	return false;

// globale Variablen initialisieren
	g_pDBEngine = NULL;

// Sprungverteiler anlegen
	g_pExtFcns = InitJumpTable (g_iExtFcnsOffset, g_iExtFcnsLast);
	if (NULL == g_pExtFcns)
		return false;

return true;
}

// --------------------------------------------------------------------------
// This function is called immediately before the extension DLL is removed
// from memory. It can perform any cleanup that the DLL may need to perform.
// --------------------------------------------------------------------------
extern "C" 
__declspec(dllexport) void ebCALLBACK Term (ebHINSTANCE hInst)
{
	if (g_pDBEngine) {
		delete g_pDBEngine;
		g_pDBEngine = NULL;
	}

	FreeJumpTable (g_pExtFcns);
}

CdbDBEngine *DBEngine (bool fNewIfFirst)
{
// Globale DBEngine anlegen
	if (NULL != g_pDBEngine) 
		return g_pDBEngine;

	if (!fNewIfFirst)	// nicht neu anlegen (für Fehlerbehandlung)
		return NULL;
				
	g_pDBEngine = new CdbDBEngine();

return g_pDBEngine;
}


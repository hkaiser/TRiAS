// BScript-Erweiterung (DaoLayer) ---------------------------------------------
// File: DAOEXTF.CPP

#if !defined(_DAOEXTF_H)
#define _DAOEXTF_H

///////////////////////////////////////////////////////////////////////////////
// Position der Argumente im Parameterfeld
const int RETURNVAL	= 0;	// Rückkehrwert

const int OBJTARGET	= 1;	// ObjektRoutinen
const int OBJARG1	= 2;
const int OBJARG2	= 3;
const int OBJARG3	= 4;
const int OBJARG4	= 5;
const int OBJARG5	= 6;
const int OBJARG6	= 7;
const int OBJARG7	= 8;
const int OBJARG8	= 9;
const int OBJARG9	= 10;
const int OBJARG10	= 11;
const int OBJARG11	= 12;
const int OBJARG12	= 13;
const int OBJARG13	= 14;
const int OBJARG14	= 15;

const int CMDARG1	= 1;	// globale Routinen
const int CMDARG2	= 2;
const int CMDARG3	= 3;
const int CMDARG4	= 4;
const int CMDARG5	= 5;

///////////////////////////////////////////////////////////////////////////////
// FunktionsPrototypen
void Dao_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DaoObject_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DaoObject_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoObject_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoObject_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DaoCollection_Count_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoCollection_Refresh_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoCollection_Item_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DaoDynCollection_Append_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoDynCollection_Delete_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DaoDynCollection_Item_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void DBEngine_DefaultUser_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_DefaultPassword_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_IniPath_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_IniPath_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_LoginTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_LoginTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_SystemDB_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_SystemDB_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_Version_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_CompactDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_CreateWorkspace_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_Idle_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_RegisterDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_RepairDatabase_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_Errors_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_Workspaces_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void DBEngine_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Workspace_IsolateODBCTrans_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_IsolateODBCTrans_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_BeginTrans_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_CommitTrans_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_RollBack_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_CreateDatabase_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_CreateGroup_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_CreateUser_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_OpenDatabase_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Databases_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Groups_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Users_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Workspace_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Error_Description_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_HelpContext_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_HelpFile_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_Number_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_Source_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Database_CollatingOrder_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_QueryTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_QueryTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_RecordsAffected_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Transactions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Updatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Version_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_CreateQueryDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_CreateRelation_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_CreateTableDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Execute_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_TableDefs_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Containers_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_QueryDefs_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_RecordSet_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Relations_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void TableDef_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Connect_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_RecordCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_SourceTableName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_SourceTableName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Updateable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_ValidationRule_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_ValidationText_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_CreateIndex_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_RefreshLink_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Indexes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Field_AllowZeroLength_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_AllowZeroLength_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_CollatingOrder_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_DataUpdatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_DefaultValue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_DefaultValue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ForeignName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ForeignName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_OrdinalPosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_OrdinalPosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Required_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Required_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Size_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Size_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_SourceField_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_SourceTable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Type_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidateOnSet_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidateOnSet_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidationRule_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_ValidationText_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_AppendChunk_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_FieldSize_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_GetChunk_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Index_Clustered_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Clustered_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_DistinctCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Foreign_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_IgnoreNulls_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_IgnoreNulls_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Primary_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Primary_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Required_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Required_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Unique_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Unique_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Container_Inherit_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Inherit_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Owner_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Owner_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Permissions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Permissions_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Documents_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Document_Container_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Owner_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Owner_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Permissions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Permissions_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_UserName_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_UserName_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void QueryDef_Connect_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Connect_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_ODBCTimeout_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_ODBCTimeout_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_RecordsAffected_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_ReturnsRecords_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_ReturnsRecords_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_SQL_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_SQL_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Updateable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_CreateProperty_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Execute_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Parameters_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void RecordSet_AbsolutePosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_AbsolutePosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_BOF_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Bookmark_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Bookmark_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Bookmarkable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CacheSize_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CacheSize_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CacheStart_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CacheStart_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_DateCreated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_EditMode_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_EOF_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Filter_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Filter_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Index_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Index_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_LastModified_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_LastUpdated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_LockEdits_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_LockEdits_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_NoMatch_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_PercentPosition_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_PercentPosition_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_RecordCount_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Restartable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Sort_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Sort_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Transactions_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Updatable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_ValidationRule_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_ValidationText_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_AddNew_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CancelUpdate_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Clone_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Close_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_CopyQueryDef_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Delete_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Edit_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_FillCache_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_FindFirst_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_FindLast_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_FindNext_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_FindPrevious_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_GetRows_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Move_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_MoveFirst_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_MoveLast_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_MoveNext_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_MovePrevious_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_OpenRecordSet_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Requery_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Seek_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Seek3Keys_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Update_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Parameter_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Property_Type_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Type_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Value_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Value_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Inherited_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Relation_Attributes_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Attributes_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_ForeignTable_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_ForeignTable_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Table_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Table_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_CreateField_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Fields_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void Group_PID_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_CreateUser_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Users_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

void User_PID_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Password_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_CreateGroup_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_NewPassword_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Groups_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Name_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Name_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Properties_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// Methods for Workspaces(0) - the default workspace
void BeginTrans_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CommitTrans_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RollBack_protocmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CreateDatabase_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CreateGroup_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void CreateUser_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void OpenDatabase_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

///////////////////////////////////////////////////////////////////////////////
// For...Each
void WorkSpaces_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void WorkSpace_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Errors_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Error_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Databases_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Database_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDefs_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void TableDef_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Fields_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Field_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Indexes_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Index_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Containers_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Container_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Documents_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Document_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDefs_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void QueryDef_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSets_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void RecordSet_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameters_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Parameter_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Properties_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Property_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relations_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Relation_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Groups_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Group_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void Users_NewEnum_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);
void User_Next_propget(ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs);

#endif // _BSCREXTF_H

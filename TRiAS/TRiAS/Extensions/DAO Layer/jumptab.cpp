// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JUMPTAB.CPP
// LastID = 358

#include "stdafx.h"

#include <limits.h>
#include <eb.h>

#include "Daoextf.h"
#include "jumptab.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (statisch/compilergeneriert)
static STATICEXTPROC s_StaticExtFcns[] = {
// reference counting routines
	{ DaoObject_refcnt, 1 },
	{ DBEngine_refcnt, 2 },
	{ TableDef_refcnt, 3 },
	{ QueryDef_refcnt, 4 },
	{ Field_refcnt, 5 },
	{ Index_refcnt, 6 },
	{ User_refcnt, 7 },
	{ Group_refcnt, 8 },
	{ Relation_refcnt, 9 },

// .DaoObject routines
	{ DaoObject_Name_propget, 10 },
	{ DaoObject_Name_propset, 11 },
	{ DaoObject_Properties_propget, 12 },

// .DaoCollection routines
	{ DaoCollection_Count_propget, 13 },
	{ DaoDynCollection_Append_command, 14 },
	{ DaoDynCollection_Delete_command, 15 },
	{ DaoCollection_Refresh_command, 16 },
	{ DaoCollection_Item_function, 33 },
	{ DaoDynCollection_Item_function, 285 },

// DBEngine routines
	{ DBEngine_DefaultUser_propset, 17 },
	{ DBEngine_DefaultPassword_propset, 18 },
	{ DBEngine_IniPath_propget, 19 },
	{ DBEngine_IniPath_propset, 20 },
	{ DBEngine_LoginTimeout_propget, 21 },
	{ DBEngine_LoginTimeout_propset, 22 },
	{ DBEngine_SystemDB_propget, 23 },
	{ DBEngine_SystemDB_propset, 24 },
	{ DBEngine_Version_propget, 25 },
	{ DBEngine_CompactDatabase_command, 26 },
	{ DBEngine_CreateWorkspace_function, 27 },
	{ DBEngine_Idle_command, 28 },
	{ DBEngine_RegisterDatabase_command, 29 },
	{ DBEngine_RepairDatabase_command, 30 },
	{ DBEngine_Errors_function, 31 },
	{ DBEngine_Workspaces_function, 32 },
	{ DBEngine_Properties_propget, 327 },
	
// Workspace routines
	{ Workspace_IsolateODBCTrans_propget, 34 },
	{ Workspace_IsolateODBCTrans_propset, 35 },
	{ Workspace_UserName_propget, 36 },
	{ Workspace_UserName_propset, 37 },
	{ Workspace_BeginTrans_command, 38 },
	{ Workspace_CommitTrans_command, 39 },
	{ Workspace_RollBack_command, 40 },
	{ Workspace_Close_command, 41 },
	{ Workspace_CreateDatabase_function, 42 },
	{ Workspace_CreateGroup_function, 43 },
	{ Workspace_CreateUser_function, 44 },
	{ Workspace_OpenDatabase_function, 45 },
	{ Workspace_Databases_propget, 46 },
	{ Workspace_Groups_propget, 47 },
	{ Workspace_Users_propget, 49 },
	{ Workspace_Name_propget, 294 },
	{ Workspace_Name_propset, 295 },	
	{ Workspace_Properties_propget, 296},

// Error routines
	{ Error_Description_propget, 50 },
	{ Error_HelpContext_propget, 51 },
	{ Error_HelpFile_propget, 52 },
	{ Error_Number_propget, 53 },
	{ Error_Source_propget, 54 },

// Database routines
	{ Database_CollatingOrder_propget, 60 },
	{ Database_Connect_propget, 61 },
	{ Database_QueryTimeout_propget, 63 },
	{ Database_QueryTimeout_propset, 64 },
	{ Database_RecordsAffected_propget, 65 },
	{ Database_Transactions_propget, 66 },
	{ Database_Updatable_propget, 67 },
	{ Database_Version_propget, 70 },
	{ Database_Close_command, 71 },
	{ Database_CreateProperty_function, 72 },
	{ Database_CreateQueryDef_function, 73 },
	{ Database_CreateRelation_function, 74 },
	{ Database_CreateTableDef_function, 75 },
	{ Database_Execute_command, 76 },
	{ Database_OpenRecordSet_function, 78 },
	{ Database_TableDefs_propget, 55 },
	{ Database_Containers_propget, 56 },
	{ Database_QueryDefs_propget, 57 },
	{ Database_RecordSet_propget, 58 },
	{ Database_Relations_propget, 59 },
	{ Database_Name_propget, 297 },
	{ Database_Name_propset, 298 },	
	{ Database_Properties_propget, 299},

// TableDef routines
	{ TableDef_Attributes_propget, 79 },
	{ TableDef_Attributes_propset, 80 },
	{ TableDef_Connect_propget, 81 },
	{ TableDef_Connect_propset, 82 },
	{ TableDef_DateCreated_propget, 84 },
	{ TableDef_LastUpdated_propget, 85 },
	{ TableDef_RecordCount_propget, 86 },
	{ TableDef_SourceTableName_propget, 87 },
	{ TableDef_SourceTableName_propset, 291 },
	{ TableDef_Updateable_propget, 88 },
	{ TableDef_ValidationRule_propget, 89 },
	{ TableDef_ValidationRule_propset, 90 },
	{ TableDef_ValidationText_propget, 91 },
	{ TableDef_ValidationText_propset, 92 },
	{ TableDef_CreateField_function, 93 },
	{ TableDef_CreateIndex_function, 94 },
	{ TableDef_CreateProperty_function, 95 },
	{ TableDef_OpenRecordSet_function, 96 },
	{ TableDef_RefreshLink_command, 97 },
	{ TableDef_Fields_propget, 98 },
	{ TableDef_Indexes_propget, 99 },
	{ TableDef_Name_propget, 293 },
	{ TableDef_Name_propset, 290 },	
	{ TableDef_Properties_propget, 292 },

// Field routines
	{ Field_AllowZeroLength_propget, 101 },
	{ Field_AllowZeroLength_propset, 102 },
	{ Field_Attributes_propget, 103 },
	{ Field_Attributes_propset, 104 },
	{ Field_CollatingOrder_propget, 105 },
	{ Field_DataUpdatable_propget, 106 },
	{ Field_DefaultValue_propget, 107 },
	{ Field_DefaultValue_propset, 108 },
	{ Field_ForeignName_propget, 109 },
	{ Field_ForeignName_propset, 110 },
	{ Field_OrdinalPosition_propget, 111 },
	{ Field_OrdinalPosition_propset, 112 },
	{ Field_Required_propget, 113 },
	{ Field_Required_propset, 114 },
	{ Field_Size_propget, 115 },
	{ Field_Size_propset, 287 },
	{ Field_SourceField_propget, 116 },
	{ Field_SourceTable_propget, 117 },
	{ Field_Type_propget, 118 },
	{ Field_Type_propset, 119 },
	{ Field_ValidateOnSet_propget, 120 },
	{ Field_ValidateOnSet_propset, 121 },
	{ Field_ValidationRule_propget, 122 },
	{ Field_ValidationRule_propset, 123 },
	{ Field_ValidationText_propget, 124 },
	{ Field_ValidationText_propset, 125 },
	{ Field_Value_propget, 126 },
	{ Field_Value_propset, 127 },
	{ Field_AppendChunk_command, 128 },
	{ Field_CreateProperty_function, 129 },
	{ Field_FieldSize_function, 130 },
	{ Field_GetChunk_function, 131 },
 	{ Field_Properties_propget, 286 },
	{ Field_Name_propget, 288 },
	{ Field_Name_propset, 289 },

// Index routines
	{ Index_Clustered_propget, 133 },
	{ Index_Clustered_propset, 134 },
	{ Index_DistinctCount_propget, 135 },
	{ Index_Foreign_propget, 136 },
	{ Index_IgnoreNulls_propget, 137 },
	{ Index_IgnoreNulls_propset, 138 },
	{ Index_Primary_propget, 139 },
	{ Index_Primary_propset, 140 },
	{ Index_Required_propget, 141 },
	{ Index_Required_propset, 142 },
	{ Index_Unique_propget, 143 },
	{ Index_Unique_propset, 144 },
	{ Index_CreateField_function, 145 },
	{ Index_CreateProperty_function, 146 },
	{ Index_Fields_propget, 147 },
	{ Index_Name_propget, 309 },
	{ Index_Name_propset, 310 },	
	{ Index_Properties_propget, 311 },

// Container routines
	{ Container_Inherit_propget, 150 },
	{ Container_Inherit_propset, 151 },
	{ Container_Owner_propget, 152 },
	{ Container_Owner_propset, 153 },
	{ Container_Permissions_propget, 154 },
	{ Container_Permissions_propset, 155 },
	{ Container_UserName_propget, 156 },
	{ Container_UserName_propset, 157 },
	{ Container_Documents_propget, 158 },
	{ Container_Name_propget, 315 },
	{ Container_Name_propset, 316 },	
	{ Container_Properties_propget, 317 },

// Document routines
	{ Document_Container_propget, 160 },
	{ Document_Owner_propget, 161 },
	{ Document_Owner_propset, 162 },
	{ Document_Permissions_propget, 163 },
	{ Document_Permissions_propset, 164 },
	{ Document_DateCreated_propget, 165 },
	{ Document_LastUpdated_propget, 166 },
	{ Document_UserName_propget, 167 },
	{ Document_UserName_propset, 168 },
	{ Document_Name_propget, 318 },
	{ Document_Name_propset, 319 },	
	{ Document_Properties_propget, 320 },

// QueryDef routines
	{ QueryDef_Connect_propget, 170 },
	{ QueryDef_Connect_propset, 171 },
	{ QueryDef_DateCreated_propget, 172 },
	{ QueryDef_LastUpdated_propget, 173 },
	{ QueryDef_Type_propget, 174 },
	{ QueryDef_ODBCTimeout_propget, 178 },
	{ QueryDef_ODBCTimeout_propset, 179 },
	{ QueryDef_RecordsAffected_propget, 180 },
	{ QueryDef_ReturnsRecords_propget, 181 },
	{ QueryDef_ReturnsRecords_propset, 182 },
	{ QueryDef_SQL_propget, 183 },
	{ QueryDef_SQL_propset, 184 },
	{ QueryDef_Updateable_propget, 185 },
	{ QueryDef_CreateProperty_function, 186 },
	{ QueryDef_Execute_command, 187 },
	{ QueryDef_OpenRecordSet_function, 188 },
	{ QueryDef_Fields_propget, 189 },
	{ QueryDef_Parameters_propget, 190 },
	{ QueryDef_Name_propget, 300 },
	{ QueryDef_Name_propset, 301 },	
	{ QueryDef_Properties_propget, 302 },

// RecordeSet routines
	{ RecordSet_AbsolutePosition_propget, 192 },
	{ RecordSet_AbsolutePosition_propset, 193 },
	{ RecordSet_BOF_propget, 194 },
	{ RecordSet_Bookmark_propget, 195 },
	{ RecordSet_Bookmark_propset, 196 },
	{ RecordSet_Bookmarkable_propget, 197 },
	{ RecordSet_CacheSize_propget, 198 },
	{ RecordSet_CacheSize_propset, 199 },
	{ RecordSet_CacheStart_propget, 200 },
	{ RecordSet_CacheStart_propset, 201 },
	{ RecordSet_DateCreated_propget, 202 },
	{ RecordSet_EditMode_propget, 203 },
	{ RecordSet_EOF_propget, 204 },
	{ RecordSet_Filter_propget, 205 },
	{ RecordSet_Filter_propset, 206 },
	{ RecordSet_Index_propget, 207 },
	{ RecordSet_Index_propset, 208 },
	{ RecordSet_LastModified_propget, 209 },
	{ RecordSet_LastUpdated_propget, 210 },
	{ RecordSet_LockEdits_propget, 211 },
	{ RecordSet_LockEdits_propset, 212 },
	{ RecordSet_NoMatch_propget, 213 },
	{ RecordSet_PercentPosition_propget, 214 },
	{ RecordSet_PercentPosition_propset, 215 },
	{ RecordSet_RecordCount_propget, 216 },
	{ RecordSet_Restartable_propget, 217 },
	{ RecordSet_Sort_propget, 218 },
	{ RecordSet_Sort_propset, 219 },
	{ RecordSet_Transactions_propget, 220 },
	{ RecordSet_Type_propget, 221 },
	{ RecordSet_Updatable_propget, 223 },
	{ RecordSet_ValidationRule_propget, 224 },
	{ RecordSet_ValidationText_propget, 226 },
	{ RecordSet_AddNew_command, 228 },
	{ RecordSet_CancelUpdate_command, 229 },
	{ RecordSet_Clone_function, 230 },
	{ RecordSet_Close_command, 231 },
	{ RecordSet_CopyQueryDef_function, 232 },
	{ RecordSet_Delete_command, 233 },
	{ RecordSet_Edit_command, 234 },
	{ RecordSet_FillCache_command, 235 },
	{ RecordSet_FindFirst_command, 236 },
	{ RecordSet_FindLast_command, 237 },
	{ RecordSet_FindNext_command, 238 },
	{ RecordSet_FindPrevious_command, 239 },
	{ RecordSet_GetRows_function, 240 },
	{ RecordSet_Move_command, 241 },
	{ RecordSet_MoveFirst_command, 242 },
	{ RecordSet_MoveLast_command, 243 },
	{ RecordSet_MoveNext_command, 244 },
	{ RecordSet_MovePrevious_command, 245 },
	{ RecordSet_OpenRecordSet_function, 246 },
	{ RecordSet_Requery_command, 247 },
	{ RecordSet_Seek_command, 248 },
	{ RecordSet_Seek3Keys_command, 328 },
	{ RecordSet_Update_command, 249 },
	{ RecordSet_Fields_propget, 250 },
	{ RecordSet_Name_propget, 306 },
	{ RecordSet_Name_propset, 307 },	
	{ RecordSet_Properties_propget, 308 },

// Parameter routines
	{ Parameter_Type_propget, 252 },
	{ Parameter_Value_propget, 254 },
	{ Parameter_Value_propset, 255 },
	{ Parameter_Name_propget, 303 },
	{ Parameter_Name_propset, 304 },	
	{ Parameter_Properties_propget, 305 },

// Property routines
	{ Property_Type_propget, 256 },
	{ Property_Type_propset, 257 },
	{ Property_Value_propget, 258 },
	{ Property_Value_propset, 259 },
	{ Property_Inherited_propget, 260 },

// Relation routines
	{ Relation_Attributes_propget, 261 },
	{ Relation_Attributes_propset, 262 },
	{ Relation_ForeignTable_propget, 263 },
	{ Relation_ForeignTable_propset, 264 },
	{ Relation_Table_propget, 265 },
	{ Relation_Table_propset, 266 },
	{ Relation_CreateField_function, 267 },
	{ Relation_Fields_propget, 268 },
	{ Relation_Name_propget, 312 },
	{ Relation_Name_propset, 313 },	
	{ Relation_Properties_propget, 314 },

// Group routines
	{ Group_PID_propset, 269 },
	{ Group_CreateUser_function, 270 },
	{ Group_Users_propget, 271 },
	{ Group_Name_propget, 324 },
	{ Group_Name_propset, 325 },	
	{ Group_Properties_propget, 326 },

// User routines
	{ User_PID_propset, 272 },
	{ User_Password_propset, 273 },
	{ User_CreateGroup_function, 274 },
	{ User_NewPassword_command, 275 },
	{ User_Groups_propget, 276 },
	{ User_Name_propget, 321 },
	{ User_Name_propset, 322 },	
	{ User_Properties_propget, 323 },

// Methods for Workspaces(0) - the default workspace
	{ BeginTrans_protocmd, 277 },
	{ CommitTrans_protocmd, 278 },
	{ RollBack_protocmd, 279 },
	{ CreateDatabase_protofunc, 281 },
	{ CreateGroup_protofunc, 282 },
	{ CreateUser_protofunc, 283 },
	{ OpenDatabase_protofunc, 284 },

// For...Each methods for collections
	{ WorkSpaces_NewEnum_propget, 329 },
	{ WorkSpace_Next_propget, 330 },
	{ Errors_NewEnum_propget, 331 },
	{ Error_Next_propget, 332 },
	{ Databases_NewEnum_propget, 333 },
	{ Database_Next_propget, 334 },
	{ TableDefs_NewEnum_propget, 335 },
	{ TableDef_Next_propget, 336 },
	{ Fields_NewEnum_propget, 337 },
	{ Field_Next_propget, 338 },
	{ Indexes_NewEnum_propget, 339 },
	{ Index_Next_propget, 340  },
	{ Containers_NewEnum_propget, 341 },
	{ Container_Next_propget, 342 },
	{ Documents_NewEnum_propget, 343 },
	{ Document_Next_propget, 344 },
	{ QueryDefs_NewEnum_propget, 345 },
	{ QueryDef_Next_propget, 346 },
	{ RecordSets_NewEnum_propget, 347 },
	{ RecordSet_Next_propget, 348 },
	{ Parameters_NewEnum_propget, 349 },
	{ Parameter_Next_propget, 350 },
	{ Properties_NewEnum_propget, 351 },
	{ Property_Next_propget, 352 },
	{ Relations_NewEnum_propget, 353 },
	{ Relation_Next_propget, 354 },
	{ Groups_NewEnum_propget, 355 },
	{ Group_Next_propget, 356 },
	{ Users_NewEnum_propget, 357 },
	{ User_Next_propget, 358 },
};
#define NUMEXTPROCS (sizeof(s_StaticExtFcns)/sizeof(s_StaticExtFcns[0]))

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (dynamisch/laufzeitgeneriert)
ebEXTPROC *g_pExtFcns = NULL;
int g_iExtFcnsOffset = 0;		// Offset zum ersten Eintrag
int g_iExtFcnsLast = 0;			// erster nicht belegter FuncID

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung der SprungverteilerTabelle
inline int imin (int i1, int i2) { return (i1 < i2) ? i1 : i2; }
inline int imax (int i1, int i2) { return (i1 > i2) ? i1 : i2; }

ebEXTPROC *InitJumpTable (int &riMin, int &riMax)
{
	ASSERT(0 < NUMEXTPROCS);	// mindestens eine Funktion muß existieren

// kleinsten und größten Index finden
int iMin = INT_MAX;
int iMax = 0;
STATICEXTPROC *pTab = s_StaticExtFcns;

	for (int i = 0; i < NUMEXTPROCS; i++, pTab++) {
		iMin = imin (iMin, pTab -> m_iFcnNum);
		iMax = imax (iMax, pTab -> m_iFcnNum);
	}
	ASSERT(iMin != INT_MAX);
	ASSERT(iMax >= iMin);

// dynamische Sprungverteilertabelle anlegen
int iSize = iMax - iMin + 1;
ebEXTPROC *pFuncTab = new ebEXTPROC [iSize];

	if (NULL == pFuncTab) return NULL;

	riMin = iMin;
	riMax = iMax + 1;

// Sprungverteilertabelle initialisieren
ebEXTPROC *pFcn = pFuncTab;
int j = 0;

	for (j = 0; j < iSize; j++, pFcn++) 
		*pFcn = Dao_not_supported;

	pTab = s_StaticExtFcns;
	for (j = 0; j < NUMEXTPROCS; j++, pTab++) {
	// FunktionsID im Rahmen des erwarteten Bereiches
		ASSERT(pTab -> m_iFcnNum >= iMin && pTab -> m_iFcnNum <= iMax);

	// dieser Eintrag darf noch nicht belegt sein	
		ASSERT(pFuncTab[pTab -> m_iFcnNum-iMin] == Dao_not_supported);
		
		pFuncTab[pTab -> m_iFcnNum-iMin] = pTab -> m_pExtFcn;		// Funktion setzen
	}

return pFuncTab;
}

void FreeJumpTable (ebEXTPROC *&rpExtFcns)
{
	if (NULL != rpExtFcns) {
		delete[] rpExtFcns;
		rpExtFcns = NULL;
	}
}


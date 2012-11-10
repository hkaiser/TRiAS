// BScript-Erweiterung (DaoLayer) ---------------------------------------------
// File: DAOEXTP.RC

#include <eb.h>
                                                         
//
// Registration Data Block - this contains information used by Basic to
// manage this extension.
//
EXTENSIONINFO RCDATA LOADONCALL DISCARDABLE
BEGIN
	1			// 'true' if this DLL needs to stay resident
	"DAO-Layer V@A.@B\0"
END


//
// Prototype table - this table describes all the extensions defined by
// this extension module.
//
BUILTINS RCDATA LOADONCALL DISCARDABLE
BEGIN
// ObjektDefinitionen
	OBJECT_BEGIN
	///////////////////////////////////////////////////////////////////////////
	// base DAO object
		".DaoObject\0", 1, "\0"
		// Properties
		OBJECT_PROPGET, "Name\0",				10, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				11, 1, 1, TYP_STRING

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Properties\0", 12, TYP_APPOBJECT, "Properties\0", 0, 0
#else
		OBJECT_PROPGET, "Properties\0",			12, TYP_APPOBJECT, "Properties\0", 0, 0
#endif
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// base DAO collection
		".DaoCollection\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Count\0",				13, TYP_LONG, 0, 0

		// Methods
		OBJECT_COMMAND, "Refresh\0",			16, 0, 0
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, ".DaoObject\0", 1, 1, TYP_VARIANT
		OBJECT_ENDDEF

	// base DAO DynCollection
		".DaoDynCollection\0", 1, ".DaoCollection\0"
		// Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, ".DaoObject\0"
		OBJECT_COMMAND, "Delete\0",				15, 1, 1, TYP_STRING
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// predefined DBEngineObject
		".DaoEngine\0", 2, ".DaoObject\0"
	
		// Properties
		OBJECT_PROPSET, "DefaultUser\0",		17, 1, 1, TYP_STRING
		OBJECT_PROPSET, "DefaultPassword\0",	18, 1, 1, TYP_STRING
		OBJECT_PROPGET, "IniPath\0",			19, TYP_STRING, 0, 0
		OBJECT_PROPSET, "IniPath\0",			20, 1, 1, TYP_STRING
		OBJECT_PROPGET, "LoginTimeout\0",		21, TYP_STRING, 0, 0
		OBJECT_PROPSET, "LoginTimeout\0",		22, 1, 1, TYP_STRING
		OBJECT_PROPGET, "SystemDB\0",			23, TYP_STRING, 0, 0
		OBJECT_PROPSET, "SystemDB\0",			24, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Version\0",			25, TYP_STRING, 0, 0

		// Methods
		OBJECT_COMMAND, "CompactDatabase\0",	26, 2, 5, TYP_STRING, TYP_STRING, TYP_STRING, TYP_LONG, TYP_STRING
		OBJECT_FUNCTION, "CreateWorkspace\0",	27, TYP_APPOBJECT, "Workspace\0", 3, 3, TYP_STRING, TYP_STRING, TYP_STRING
		OBJECT_COMMAND, "Idle\0",				28, 0, 1, TYP_LONG
		OBJECT_COMMAND, "RegisterDatabase\0",	29, 4, 4, TYP_STRING, TYP_STRING, TYP_BOOLEAN, TYP_STRING
		OBJECT_COMMAND, "RepairDatabase\0",		30, 1, 1, TYP_STRING

		// Collections
		OBJECT_PROPGET, "Errors\0",				31, TYP_APPOBJECT, "Errors\0", 0, 0
		OBJECT_PROPGET, "Properties\0",			327, TYP_APPOBJECT, "Properties\0", 0, 0
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Workspaces\0",	32, TYP_APPOBJECT, "Workspaces\0", 0, 0
#else
		OBJECT_PROPGET, "Workspaces\0",			32, TYP_APPOBJECT, "Workspaces\0", 0, 0
#endif
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Workspaces collection
		"Workspaces\0", 1, ".DaoDynCollection\0"
		// Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Workspace\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Workspace\0", 1, 1, TYP_VARIANT
		OBJECT_FUNCTION, "Item\0",				285, TYP_APPOBJECT, "Workspace\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 329, TYP_APPOBJECT, "WorkSpaces\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 330, TYP_APPOBJECT, "WorkSpace\0", 0, 0
		OBJECT_ENDDEF

	// Workspace object
		"Workspace\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "IsolateODBCTrans\0",	34, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "IsolateODBCTrans\0",	35, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "UserName\0",			36, TYP_STRING, 0, 0
		OBJECT_PROPSET, "UserName\0",			37, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				294, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				295, 1, 1, TYP_STRING

		// Methods
		OBJECT_COMMAND, "BeginTrans\0",			38, 0, 0
		OBJECT_COMMAND, "CommitTrans\0",		39, 0, 0
		OBJECT_COMMAND, "RollBack\0",			40, 0, 0
		OBJECT_COMMAND, "Close\0",				41, 0, 0

		OBJECT_FUNCTION, "CreateDatabase\0",	42, TYP_APPOBJECT, "Database\0", 2, 3, TYP_STRING, TYP_STRING, TYP_INTEGER
		OBJECT_FUNCTION, "CreateGroup\0",		43, TYP_APPOBJECT, "Group\0", 1, 2, TYP_STRING, TYP_STRING
		OBJECT_FUNCTION, "CreateUser\0",		44, TYP_APPOBJECT, "User\0", 0, 3, TYP_STRING, TYP_STRING, TYP_STRING
		OBJECT_FUNCTION, "OpenDatabase\0",		45, TYP_APPOBJECT, "Database\0", 1, 4, TYP_STRING, TYP_BOOLEAN, TYP_BOOLEAN, TYP_STRING

		// Collections
		OBJECT_PROPGET, "Properties\0",			296, TYP_APPOBJECT, "Properties\0", 0, 0
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Databases\0", 46, TYP_APPOBJECT, "Databases\0", 0, 0
#else
		OBJECT_PROPGET, "Databases\0",			46, TYP_APPOBJECT, "Databases\0", 0, 0
#endif
		OBJECT_PROPGET, "Groups\0",				47, TYP_APPOBJECT, "Groups\0", 0, 0
		OBJECT_PROPGET, "Users\0",				49, TYP_APPOBJECT, "Users\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Errors Collection
		"Errors\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "Error\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 331, TYP_APPOBJECT, "Errors\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 332, TYP_APPOBJECT, "Error\0", 0, 0
		OBJECT_ENDDEF

	// Error object
		"Error\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Description\0",		50, TYP_STRING, 0, 0
		OBJECT_PROPGET, "HelpContext\0",		51, TYP_LONG, 0, 0
		OBJECT_PROPGET, "HelpFile\0",			52, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Number\0",				53, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Source\0",				54, TYP_STRING, 0, 0

		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Databases Collection
		"Databases\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "Database\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 333, TYP_APPOBJECT, "Databases\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 334, TYP_APPOBJECT, "Database\0", 0, 0
		OBJECT_ENDDEF

	// Database object
		"Database\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "CollatingOrder\0",		60, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Connect\0",			61, TYP_STRING, 0, 0
		OBJECT_PROPGET, "QueryTimeout\0",		63, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "QueryTimeout\0",		64, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "RecordsAffected\0",	65, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Transactions\0",		66, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Updatable\0",			67, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Version\0",			70, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name\0",				297, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				298, 1, 1, TYP_STRING

		// Methods
		OBJECT_COMMAND, "Close\0",				71, 0, 0
		OBJECT_FUNCTION, "CreateProperty\0",	72, TYP_APPOBJECT, "Property\0", 0, 4, TYP_STRING, TYP_INTEGER, TYP_VARIANT, TYP_BOOLEAN
		OBJECT_FUNCTION, "CreateQueryDef\0",	73, TYP_APPOBJECT, "QueryDef\0", 0, 2, TYP_STRING, TYP_STRING
		OBJECT_FUNCTION, "CreateRelation\0",	74, TYP_APPOBJECT, "Relation\0", 0, 4, TYP_STRING, TYP_STRING, TYP_STRING, TYP_LONG
		OBJECT_FUNCTION, "CreateTableDef\0",	75, TYP_APPOBJECT, "TableDef\0", 0, 4, TYP_STRING, TYP_LONG, TYP_STRING, TYP_STRING
		OBJECT_COMMAND, "Execute\0",			76, 1, 2, TYP_STRING, TYP_LONG
		OBJECT_FUNCTION, "OpenRecordSet\0",		78, TYP_APPOBJECT, "RecordSet\0", 1, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "TableDefs\0", 55, TYP_APPOBJECT, "TableDefs\0", 0, 0
#else
		OBJECT_PROPGET, "TableDefs\0",			55, TYP_APPOBJECT, "TableDefs\0", 0, 0
#endif
		OBJECT_PROPGET, "Containers\0",			56, TYP_APPOBJECT, "Containers\0", 0, 0
		OBJECT_PROPGET, "QueryDefs\0",			57, TYP_APPOBJECT, "QueryDefs\0", 0, 0
		OBJECT_PROPGET, "Recordsets\0",			58, TYP_APPOBJECT, "Recordsets\0", 0, 0
		OBJECT_PROPGET, "Relations\0",			59, TYP_APPOBJECT, "Relations\0", 0, 0
		OBJECT_PROPGET, "Properties\0",			299, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// TableDefs Collection
		"TableDefs\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "TableDef\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "TableDef\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 335, TYP_APPOBJECT, "TableDefs\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 336, TYP_APPOBJECT, "TableDef\0", 0, 0
		OBJECT_ENDDEF

	// TableDef object
		"TableDef\0", 3, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Attributes\0",			79, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Attributes\0",			80, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Connect\0",			81, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Connect\0",			82, 1, 1, TYP_STRING
		OBJECT_PROPGET, "DateCreated\0",		84, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "LastUpdated\0",		85, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "RecordCount\0",		86, TYP_LONG, 0, 0
		OBJECT_PROPGET, "SourceTableName\0",	87, TYP_STRING, 0, 0
		OBJECT_PROPSET, "SourceTableName\0",	291, 1, 1, TYP_STRING 
		OBJECT_PROPGET, "Updateable\0",			88, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "ValidationRule\0",		89, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ValidationRule\0",		90, 1, 1, TYP_STRING
		OBJECT_PROPGET, "ValidationText\0",		91, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ValidationText\0",		92, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				293, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				290, 1, 1, TYP_STRING

		// Methods
		OBJECT_FUNCTION, "CreateField\0",		93, TYP_APPOBJECT, "Field\0", 0, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER
		OBJECT_FUNCTION, "CreateIndex\0",		94, TYP_APPOBJECT, "Index\0", 0, 1, TYP_STRING
		OBJECT_FUNCTION, "CreateProperty\0",	95, TYP_APPOBJECT, "Property\0", 0, 4, TYP_STRING, TYP_STRING, TYP_STRING, TYP_LONG
		OBJECT_FUNCTION, "OpenRecordSet\0",		96, TYP_APPOBJECT, "RecordSet\0", 0, 2, TYP_INTEGER, TYP_INTEGER
		OBJECT_COMMAND, "RefreshLink\0",		97, 0, 0

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Fields\0", 98, TYP_APPOBJECT, "Fields\0", 0, 0
#else
		OBJECT_PROPGET, "Fields\0",				98, TYP_APPOBJECT, "Fields\0", 0, 0
#endif
		OBJECT_PROPGET, "Indexes\0",			99, TYP_APPOBJECT, "Indexes\0", 0, 0
		OBJECT_PROPGET, "Properties\0",			292, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Fields Collection
		"Fields\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Field\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Field\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 337, TYP_APPOBJECT, "Fields\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 338, TYP_APPOBJECT, "Field\0", 0, 0
		OBJECT_ENDDEF

	// Field object
		"Field\0", 5, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "AllowZeroLength\0",	101, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "AllowZeroLength\0",	102, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Attributes\0",			103, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Attributes\0",			104, 1, 1, TYP_LONG
		OBJECT_PROPGET, "CollatingOrder\0",		105, TYP_LONG, 0, 0
		OBJECT_PROPGET, "DataUpdatable\0",		106, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "DefaultValue\0",		107, TYP_STRING, 0, 0
		OBJECT_PROPSET, "DefaultValue\0",		108, 1, 1, TYP_STRING
		OBJECT_PROPGET, "ForeignName\0",		109, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ForeignName\0",		110, 1, 1, TYP_STRING
		OBJECT_PROPGET, "OrdinalPosition\0",	111, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "OrdinalPosition\0",	112, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Required\0",			113, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Required\0",			114, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Size\0",				115, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Size\0",				287, 1, 1, TYP_LONG
		OBJECT_PROPGET, "SourceField\0",		116, TYP_STRING, 0, 0
		OBJECT_PROPGET, "SourceTable\0",		117, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Type\0",				118, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Type\0",				119, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "ValidateOnSet\0",		120, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "ValidateOnSet\0",		121, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "ValidationRule\0",		122, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ValidationRule\0",		123, 1, 1, TYP_STRING
		OBJECT_PROPGET, "ValidationText\0",		124, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ValidationText\0",		125, 1, 1, TYP_STRING
		OBJECT_PROPGET|OBJECT_DEFAULT, "Value\0", 126, TYP_VARIANT, 0, 0
		OBJECT_PROPSET|OBJECT_DEFAULT, "Value\0", 127, 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Name\0",				288, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				289, 1, 1, TYP_STRING
		
		// Methods
		OBJECT_COMMAND, "AppendChunk\0",		128, 1, 1, TYP_VARIANT
		OBJECT_FUNCTION, "CreateProperty\0",	129, TYP_APPOBJECT, "Property\0", 0, 4, TYP_STRING, TYP_INTEGER, TYP_VARIANT, TYP_BOOLEAN
		OBJECT_FUNCTION, "FieldSize\0",			130, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "GetChunk\0",			131, TYP_VARIANT, 2, 2, TYP_LONG, TYP_LONG

		// Collections
		OBJECT_PROPGET, "Properties\0",			286, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Indexes Collection
		"Indexes\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Index\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Index\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 339, TYP_APPOBJECT, "Indexes\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 340, TYP_APPOBJECT, "Index\0", 0, 0
		OBJECT_ENDDEF

	// Index object
		"Index\0", 6, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Clustered\0",			133, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Clustered\0",			134, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "DistinctCount\0",		135, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Foreign\0",			136, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "IgnoreNulls\0",		137, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "IgnoreNulls\0",		138, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Primary\0",			139, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Primary\0",			140, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Required\0",			141, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Required\0",			142, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Unique\0",				143, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Unique\0",				144, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Name\0",				309, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				310, 1, 1, TYP_STRING

		// Methods
		OBJECT_FUNCTION, "CreateField\0",		145, TYP_APPOBJECT, "Field\0", 0, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER
		OBJECT_FUNCTION, "CreateProperty\0",	146, TYP_APPOBJECT, "Property\0", 0, 4, TYP_STRING, TYP_STRING, TYP_STRING, TYP_LONG

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Fields\0", 147, TYP_APPOBJECT, "Fields\0", 0, 0
#else
		OBJECT_PROPGET, "Fields\0",				147, TYP_APPOBJECT, "Fields\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			311, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Containers Collection
		"Containers\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "Container\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 341, TYP_APPOBJECT, "Containers\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 342, TYP_APPOBJECT, "Container\0", 0, 0
		OBJECT_ENDDEF

	// Container object
		"Container\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Inherit\0",			150, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Inherit\0",			151, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Owner\0",				152, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Owner\0",				153, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Permissions\0",		154, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Permissions\0",		155, 1, 1, TYP_LONG
		OBJECT_PROPGET, "UserName\0",			156, TYP_STRING, 0, 0
		OBJECT_PROPSET, "UserName\0",			157, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				315, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				316, 1, 1, TYP_STRING

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Documents\0", 158, TYP_APPOBJECT, "Documents\0", 0, 0
#else
		OBJECT_PROPGET, "Documents\0",			158, TYP_APPOBJECT, "Documents\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			317, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Documents Collection
		"Documents\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "Document\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 343, TYP_APPOBJECT, "Documents\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 344, TYP_APPOBJECT, "Document\0", 0, 0
		OBJECT_ENDDEF

	// Document object
		"Document\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Container\0",			160, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Owner\0",				161, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Owner\0",				162, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Permissions\0",		163, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Permissions\0",		164, 1, 1, TYP_LONG
		OBJECT_PROPGET, "DateCreated\0",		165, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "LastUpdated\0",		166, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "UserName\0",			167, TYP_STRING, 0, 0
		OBJECT_PROPSET, "UserName\0",			168, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				318, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				319, 1, 1, TYP_STRING

	//	Collections
		OBJECT_PROPGET, "Properties\0",	320, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// QueryDefs Collection
		"QueryDefs\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "QueryDef\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "QueryDef\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 345, TYP_APPOBJECT, "QueryDefs\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 346, TYP_APPOBJECT, "QueryDef\0", 0, 0
		OBJECT_ENDDEF

	// QueryDef object
		"QueryDef\0", 4, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Connect\0",			170, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Connect\0",			171, 1, 1, TYP_STRING
		OBJECT_PROPGET, "DateCreated\0",		172, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "LastUpdated\0",		173, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "Type\0",				174, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "ODBCTimeout\0",		178, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "ODBCTimeout\0",		179, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "RecordsAffected\0",	180, TYP_LONG, 0, 0
		OBJECT_PROPGET, "ReturnsRecords\0",		181, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "ReturnsRecords\0",		182, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "SQL\0",				183, TYP_STRING, 0, 0
		OBJECT_PROPSET, "SQL\0",				184, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Updatable\0",			185, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Name\0",				300, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				301, 1, 1, TYP_STRING

	//	Methods
		OBJECT_FUNCTION, "CreateProperty\0",	186, TYP_APPOBJECT, "Property\0", 0, 4, TYP_STRING, TYP_STRING, TYP_STRING, TYP_LONG
		OBJECT_COMMAND, "Execute\0",			187, 0, 1, TYP_INTEGER
		OBJECT_FUNCTION, "OpenRecordSet\0",		188, TYP_APPOBJECT, "RecordSet\0", 1, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER

		// Collections
		OBJECT_PROPGET, "Fields\0",				189, TYP_APPOBJECT, "Fields\0", 0, 0
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Parameters\0", 190, TYP_APPOBJECT, "Indexes\0", 0, 0
#else
		OBJECT_PROPGET, "Parameters\0",			190, TYP_APPOBJECT, "Indexes\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			302, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// RecordSets Collection
		"Recordsets\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "RecordSet\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 347, TYP_APPOBJECT, "RecordSets\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 348, TYP_APPOBJECT, "RecordSet\0", 0, 0
		OBJECT_ENDDEF

	// RecordSet object
		"Recordset\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "AbsolutePosition\0",	192, TYP_LONG, 0, 0
		OBJECT_PROPSET, "AbsolutePosition\0",	193, 1, 1, TYP_LONG
		OBJECT_PROPGET, "BOF\0",				194, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Bookmark\0",			195, TYP_VARIANT, 0, 0
		OBJECT_PROPSET, "Bookmark\0",			196, 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Bookmarkable\0",		197, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "CacheSize\0",			198, TYP_LONG, 0, 0
		OBJECT_PROPSET, "CacheSize\0",			199, 1, 1, TYP_LONG
		OBJECT_PROPGET, "CacheStart\0",			200, TYP_LONG, 0, 0
		OBJECT_PROPSET, "CacheStart\0",			201, 1, 1, TYP_LONG
		OBJECT_PROPGET, "DateCreated\0",		202, TYP_VARIANT, 0, 0	// Time/Date
		OBJECT_PROPGET, "EditMode\0",			203, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "EOF\0",				204, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Filter\0",				205, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Filter\0",				206, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Index\0",				207, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Index\0",				208, 1, 1, TYP_STRING
		OBJECT_PROPGET, "LastModified\0",		209, TYP_VARIANT, 0, 0	// Bookmark
		OBJECT_PROPGET, "LastUpdated\0",		210, TYP_VARIANT, 0, 0	// Date/Time
		OBJECT_PROPGET, "LockEdits\0",			211, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "LockEdits\0",			212, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "NoMatch\0",			213, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "PercentPosition\0",	214, TYP_SINGLE, 0, 0
		OBJECT_PROPSET, "PercentPosition\0",	215, 1, 1, TYP_SINGLE
		OBJECT_PROPGET, "RecordCount\0",		216, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Restartable\0",		217, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Sort\0",				218, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Sort\0",				219, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Transactions\0",		220, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "Type\0",				221, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "Updatable\0",			223, TYP_BOOLEAN, 0, 0
		OBJECT_PROPGET, "ValidationRule\0",		224, TYP_STRING, 0, 0
		OBJECT_PROPGET, "ValidationText\0",		226, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name\0",				306, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				307, 1, 1, TYP_STRING
		
	// Methods
		OBJECT_COMMAND, "AddNew\0",				228, 0, 0
		OBJECT_COMMAND, "CancelUpdate\0",		229, 0, 0
		OBJECT_FUNCTION, "Clone\0",				230, TYP_APPOBJECT, "RecordSet\0", 0, 0
		OBJECT_COMMAND, "Close\0",				231, 0, 0
		OBJECT_FUNCTION, "CopyQueryDef\0",		232, TYP_APPOBJECT, "QueryDef\0", 0, 0
		OBJECT_COMMAND, "Delete\0",				233, 0, 0
		OBJECT_COMMAND, "Edit\0",				234, 0, 0
		OBJECT_COMMAND, "FillCache\0",			235, 0, 2, TYP_INTEGER, TYP_STRING
		OBJECT_COMMAND, "FindFirst\0",			236, 1, 1, TYP_STRING
		OBJECT_COMMAND, "FindLast\0",			237, 1, 1, TYP_STRING
		OBJECT_COMMAND, "FindNext\0",			238, 1, 1, TYP_STRING
		OBJECT_COMMAND, "FindPrevious\0",		239, 1, 1, TYP_STRING
		OBJECT_FUNCTION, "GetRows\0",			240, TYP_VARIANT, 1, 1, TYP_LONG
		OBJECT_COMMAND, "Move\0",				241, 1, 2, TYP_LONG, TYP_STRING
		OBJECT_COMMAND, "MoveFirst\0",			242, 0, 0
		OBJECT_COMMAND, "MoveLast\0",			243, 0, 0
		OBJECT_COMMAND, "MoveNext\0",			244, 0, 0
		OBJECT_COMMAND, "MovePrevious\0",		245, 0, 0
		OBJECT_FUNCTION, "OpenRecordSet\0",		246, TYP_APPOBJECT, "RecordSet\0", 0, 2, TYP_INTEGER, TYP_INTEGER
		OBJECT_COMMAND, "Requery\0",			247, 0, 1, TYP_APPOBJECT, "QueryDef\0"
		OBJECT_COMMAND, "Seek\0",				248, 5, 14, TYP_STRING, 
						TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT,
						TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, 
						TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "Seek\0",				328, 2, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "Update\0",				249, 0, 0

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Fields\0", 250, TYP_APPOBJECT, "Fields\0", 0, 0
#else
		OBJECT_PROPGET, "Fields\0",				250, TYP_APPOBJECT, "Fields\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			308, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Parameters Collection
		"Parameters\0", 1, ".DaoCollection\0"
		// standard Methods
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 33, TYP_APPOBJECT, "Parameter\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 349, TYP_APPOBJECT, "Parameters\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 350, TYP_APPOBJECT, "Parameter\0", 0, 0
		OBJECT_ENDDEF

	// Parameter object
		"Parameter\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Type\0",				252, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "Name\0",				303, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				304, 1, 1, TYP_STRING
		OBJECT_PROPGET|OBJECT_DEFAULT, "Value\0", 254, TYP_VARIANT, 0, 0
		OBJECT_PROPSET|OBJECT_DEFAULT, "Value\0", 255, 1, 1, TYP_VARIANT

	//	Collection
		OBJECT_PROPGET, "Properties\0",			305, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Properties collection
		"Properties\0", 1, ".DaoDynCollection\0"
		// Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Property\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Property\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 351, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 352, TYP_APPOBJECT, "Property\0", 0, 0
		OBJECT_ENDDEF

	// Property object
		"Property\0", 1, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Type\0",				256, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Type\0",				257, 1, 1, TYP_INTEGER
		OBJECT_PROPGET|OBJECT_DEFAULT, "Value\0", 258, TYP_VARIANT, 0, 0
		OBJECT_PROPSET|OBJECT_DEFAULT, "Value\0", 259, 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Inherited\0",			260, TYP_BOOLEAN, 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Relations Collection
		"Relations\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Relation\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Relation\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 353, TYP_APPOBJECT, "Relations\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 354, TYP_APPOBJECT, "Relation\0", 0, 0
		OBJECT_ENDDEF

	// Relation object
		"Relation\0", 9, ".DaoObject\0"
		// Properties
		OBJECT_PROPGET, "Attributes\0",			261, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Attributes\0",			262, 1, 1, TYP_LONG
		OBJECT_PROPGET, "ForeignTable\0",		263, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ForeignTable\0",		264, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Table\0",				265, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Table\0",				266, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				312, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				313, 1, 1, TYP_STRING

		// Methods
		OBJECT_FUNCTION, "CreateField\0",		267, TYP_APPOBJECT, "Field\0", 0, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Fields\0", 268, TYP_APPOBJECT, "Fields\0", 0, 0
#else
		OBJECT_PROPGET, "Fields\0",				268, TYP_APPOBJECT, "Fields\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			314, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Groups Collection
		"Groups\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "Group\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "Group\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 355, TYP_APPOBJECT, "Groups\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 356, TYP_APPOBJECT, "Group\0", 0, 0
		OBJECT_ENDDEF

	// Group object
		"Group\0", 8, ".DaoObject\0"
		// Properties
		OBJECT_PROPSET, "PID\0",				269, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				324, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				325, 1, 1, TYP_STRING

		// Methods
		OBJECT_FUNCTION, "CreateUser\0",		270, TYP_APPOBJECT, "User\0", 0, 3, TYP_STRING, TYP_STRING, TYP_STRING

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Users\0", 271, TYP_APPOBJECT, "Users\0", 0, 0
#else
		OBJECT_PROPGET, "Users\0",				271, TYP_APPOBJECT, "Users\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			326, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Users Collection
		"Users\0", 1, ".DaoDynCollection\0"
		// standard Methods
		OBJECT_COMMAND, "Append\0",				14, 1, 1, TYP_APPOBJECT, "User\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 285, TYP_APPOBJECT, "User\0", 1, 1, TYP_VARIANT

		// For...Each methods
		OBJECT_PROPGET, ".NewEnum\0", 357, TYP_APPOBJECT, "Users\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 358, TYP_APPOBJECT, "User\0", 0, 0
		OBJECT_ENDDEF

	// User object
		"User\0", 7, ".DaoObject\0"
		// Properties
		OBJECT_PROPSET, "PID\0",				272, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Password\0",			273, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0",				321, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0",				322, 1, 1, TYP_STRING

		// Methods
		OBJECT_FUNCTION, "CreateGroup\0",		274, TYP_APPOBJECT, "Group\0", 0, 2, TYP_STRING, TYP_STRING
		OBJECT_COMMAND, "NewPassword\0",		275, 2, 2, TYP_STRING, TYP_STRING

		// Collections
#ifdef _USE_DEFAULT_PROPERTYGET
		OBJECT_PROPGET|OBJECT_DEFAULT, "Groups\0", 276, TYP_APPOBJECT, "Groups\0", 0, 0
#else
		OBJECT_PROPGET, "Groups\0",				276, TYP_APPOBJECT, "Groups\0", 0, 0
#endif
		OBJECT_PROPGET, "Properties\0",			323, TYP_APPOBJECT, "Properties\0", 0, 0
		OBJECT_ENDDEF

	OBJECT_END

// globale Funktionen
	PROTO_BEGIN
	// Methods for Workspaces(0)
		PROTO_CMD, "BeginTrans\0",				277, 0, 0
		PROTO_CMD, "CommitTrans\0",				278, 0, 0
		PROTO_CMD, "RollBack\0",				279, 0, 0

		PROTO_FUNC, "CreateDatabase\0",			281, TYP_APPOBJECT, "Database\0", 2, 3, TYP_STRING, TYP_STRING, TYP_INTEGER
		PROTO_FUNC, "CreateGroup\0",			282, TYP_APPOBJECT, "Group\0", 1, 2, TYP_STRING, TYP_STRING
		PROTO_FUNC, "CreateUser\0",				283, TYP_APPOBJECT, "User\0", 0, 3, TYP_STRING, TYP_STRING, TYP_STRING
		PROTO_FUNC, "OpenDatabase\0",			284, TYP_APPOBJECT, "Database\0", 1, 4, TYP_STRING, TYP_BOOLEAN, TYP_BOOLEAN, TYP_STRING
	PROTO_END

// LAST USED ID: 358

// Konstantendefinitionen
	CONST_BEGIN
	// vordefiniertes DBEngine-Objekt
		TYP_APPOBJECT, "DBEngine\0", ".DaoEngine\0", 1L

	// Locale string constants
		TYP_STRING, "dbLangArabic\0", ";LANGID=0x0401;CP=1256;COUNTRY=0\0"
		TYP_STRING, "dbLangCzech\0", ";LANGID=0x0405;CP=1250;COUNTRY=0\0"
		TYP_STRING, "dbLangDutch\0", ";LANGID=0x0413;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangGeneral\0", ";LANGID=0x0409;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangGreek\0", ";LANGID=0x0408;CP=1253;COUNTRY=0\0"
		TYP_STRING, "dbLangHebrew\0", ";LANGID=0x040D;CP=1255;COUNTRY=0\0"
		TYP_STRING, "dbLangHungarian\0", ";LANGID=0x040E;CP=1250;COUNTRY=0\0"
		TYP_STRING, "dbLangIcelandic\0", ";LANGID=0x040F;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangNordic\0", ";LANGID=0x041D;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangNorwDan\0", ";LANGID=0x0414;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangPolish\0", ";LANGID=0x0415;CP=1250;COUNTRY=0\0"
		TYP_STRING, "dbLangCyrillic\0", ";LANGID=0x0419;CP=1251;COUNTRY=0\0"
		TYP_STRING, "dbLangSpanish\0", ";LANGID=0x040A;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangSwedFin\0", ";LANGID=0x040B;CP=1252;COUNTRY=0\0"
		TYP_STRING, "dbLangTurkish\0", ";LANGID=0x041F;CP=1254;COUNTRY=0\0"
		TYP_STRING, "dbLangJapanese\0", ";LANGID=0x0411;CP=932;COUNTRY=0\0"
		TYP_STRING, "dbLangChineseSimplified\0", ";LANGID=0x0804;CP=936;COUNTRY=0\0"
		TYP_STRING, "dbLangChineseTraditional\0", ";LANGID=0x0404;CP=950;COUNTRY=0\0"
		TYP_STRING, "dbLangKorean\0", ";LANGID=0x040C;CP=494;COUNTRY=0\0"
		TYP_STRING, "dbLangThai\0", ";LANGID=0x101E;CP=874;COUNTRY=0\0"

	// Collating Order
		TYP_LONG, "dbSortNeutral\0", 1024L
		TYP_LONG, "dbSortArabic\0", 1025L
		TYP_LONG, "dbSortCyrillic\0", 1049L
		TYP_LONG, "dbSortCzech\0", 1029L
		TYP_LONG, "dbSortDutch\0", 1043L
		TYP_LONG, "dbSortGeneral\0", 1033L
		TYP_LONG, "dbSortGreek\0", 1032L
		TYP_LONG, "dbSortHebrew\0", 1037L
		TYP_LONG, "dbSortHungarian\0", 1038L
		TYP_LONG, "dbSortIcelandic\0", 1039L
		TYP_LONG, "dbSortNorwdan\0", 1030L
		TYP_LONG, "dbSortPDXIntl\0", 1033L
		TYP_LONG, "dbSortPDXNor\0", 1030L
		TYP_LONG, "dbSortPDXSwe\0", 1053L
		TYP_LONG, "dbSortPolish\0", 1045L
		TYP_LONG, "dbSortSpanish\0", 1034L
		TYP_LONG, "dbSortSwedFin\0", 1053L
		TYP_LONG, "dbSortTurkish\0", 1055L
		TYP_LONG, "dbSortJapanese\0", 1041L
		TYP_LONG, "dbSortChineseSimplified\0", 2052L
		TYP_LONG, "dbSortChineseTraditional\0", 1028L
		TYP_LONG, "dbSortKorean\0", 1036L
		TYP_LONG, "dbSortThai\0", 4126L
		TYP_LONG, "dbSortUndefined\0", -1L

	// Options for CreateDatabase (options)
		TYP_INTEGER, "dbVersion10\0", 1
		TYP_INTEGER, "dbEncrypt\0", 2
		TYP_INTEGER, "dbDecrypt\0", 4
		TYP_INTEGER, "dbVersion11\0", 8
		TYP_INTEGER, "dbVersion20\0", 16
		TYP_INTEGER, "dbVersion30\0", 32
	
	// Options for CreateRelation
		TYP_LONG, "dbRelationUnique\0", 1L
		TYP_LONG, "dbRelationDontEnforce\0", 2L
		TYP_LONG, "dbRelationInherited\0", 4L
		TYP_LONG, "dbRelationUpdateCascade\0", 256L
		TYP_LONG, "dbRelationDeleteCascade\0", 4096L
		TYP_LONG, "dbRelationLeft\0", 16777216L
		TYP_LONG, "dbRelationRight\0", 33554432L

	// Options for CreateTableDef/TableDef-Attributes
		TYP_LONG, "dbAttachExclusive\0", 65536L
		TYP_LONG, "dbAttachSavePWD\0", 131072L
		TYP_LONG, "dbSystemObject\0", -2147483646L
		TYP_LONG, "dbAttachedTable\0", 1073741824L
		TYP_LONG, "dbAttachedODBC\0", 536870912L
		TYP_LONG, "dbHiddenObject\0", 1L

	// Options for Execute/OpenRecordSet
		TYP_INTEGER, "dbDenyWrite\0", 1
		TYP_INTEGER, "dbDenyRead\0", 2
		TYP_INTEGER, "dbReadOnly\0", 4
		TYP_INTEGER, "dbAppendOnly\0", 8
		TYP_INTEGER, "dbInconsistent\0", 16
		TYP_INTEGER, "dbConsistent\0", 32
		TYP_INTEGER, "dbSQLPassThrough\0", 64
		TYP_INTEGER, "dbFailOnError\0", 128
		TYP_INTEGER, "dbForwardOnly\0", 256
		TYP_INTEGER, "dbSeeChanges\0", 512

	// Option für MakeReplica
		TYP_LONG, "dbRepMakeReadOnly\0", 2L

	// Types für OpenRecordset
		TYP_INTEGER, "dbOpenTable\0", 1
		TYP_INTEGER, "dbOpenDynaset\0", 2
		TYP_INTEGER, "dbOpenSnapshot\0", 4

	// Fieldtypes
		TYP_INTEGER, "dbBoolean\0", 1
		TYP_INTEGER, "dbByte\0", 2
		TYP_INTEGER, "dbInteger\0", 3
		TYP_INTEGER, "dbLong\0", 4
		TYP_INTEGER, "dbCurrency\0", 5
		TYP_INTEGER, "dbSingle\0", 6
		TYP_INTEGER, "dbDouble\0", 7
		TYP_INTEGER, "dbDate\0", 8
		TYP_INTEGER, "dbText\0", 10
		TYP_INTEGER, "dbLongBinary\0", 11
		TYP_INTEGER, "dbMemo\0", 12
		TYP_INTEGER, "dbGUID\0", 15

	// Field-Attributes
		TYP_LONG, "dbFixedField\0", 1L
		TYP_LONG, "dbVariableField\0", 2L
		TYP_LONG, "dbAutoIncrField\0", 16L
		TYP_LONG, "dbUpdatableField\0", 32L
		TYP_LONG, "dbSystemField\0", 8192L

	// SecurityFlags
		TYP_LONG, "dbSecNoAccess\0", 0L
		TYP_LONG, "dbSecFullAccess\0", 1048575L
		TYP_LONG, "dbSecDelete\0", 65536L
		TYP_LONG, "dbSecReadSec\0", 131072L
		TYP_LONG, "dbSecWriteSec\0", 262144L
		TYP_LONG, "dbSecWriteOwner\0", 524288L
		TYP_LONG, "dbSecDBCreate\0", 1L
		TYP_LONG, "dbSecDBOpen\0", 2L
		TYP_LONG, "dbSecDBExclusive\0", 4L
		TYP_LONG, "dbSecDBAdmin\0", 8L
		TYP_LONG, "dbSecCreate\0", 1L
		TYP_LONG, "dbSecReadDef\0", 4L
		TYP_LONG, "dbSecWriteDef\0", 65548L
		TYP_LONG, "dbSecRetrieveData\0", 20L
		TYP_LONG, "dbSecInsertData\0", 32L
		TYP_LONG, "dbSecReplaceData\0", 64L
		TYP_LONG, "dbSecDeleteData\0", 128L

	// EditMode
		TYP_INTEGER, "dbEditNone\0", 0
		TYP_INTEGER, "dbEditInProgress\0", 1
		TYP_INTEGER, "dbEditAdd\0", 2

	CONST_END

	TABLE_END
END

%{
/* Datenbasis-Struktur-Definitionssprachprozessor               */
/* File: DDSP.Y                                                 */

#if defined(sccs)
static char SccsId[] = "%W%	%E%";
#endif

#include "StdAfx.h"

#include "ddspprot.h"		// Prototypen
 
ID_INFO *id_list, *currid;
int var_size;                   /* Anzahl der Basistypvariablen im field */
int type_size;                  /* Variablengroesse */
char var_str[80];               /* aktuelle Variablendeklaration */
char db_name[_MAX_PATH];          /* Datenbasisname */
int  multidim = 0;              /* multi-dimensional array flag */

char dbd_ext[4];				/* Erweiterung für DictionaryDatei */
 
extern int line;				/* aktuelle Eingabezeile */
 
#ifdef BACKUP
extern short backup_flag;
#endif

long DBVersion = 0L; 			/* VersionsNummer */
long PageSize = 1024L;			/* PageGröße */

%}
 
%start schema
 
%union {
	STRTOK tstr;
	NUMTOK tnum;
}
 
%token <tnum> T_CONTAINS T_DATA T_DATABASE
%token <tnum> T_DOUBLE T_FILE T_FLOAT T_DB_ADDR T_CHAR T_INT T_LONG
%token <tnum> T_BACKUP T_TO T_ENABLE T_DISABLE
%token <tnum> T_UNIQUE T_ONLY T_KEY T_AND T_BTREE T_HTREE T_QTREE T_CTREE
%token <tnum> T_RECORD T_SHORT T_STRUCT T_NUMBER T_UNION T_VERSION
%token <tstr> T_IDENT T_STRING T_EXTENSION
 
%token <tnum> '{' '}' ';' ','
 
%type <tstr> file_id var var_name
%type <tnum> basic_type size size_specs key_field geotree
%type <tnum> grouped_field_spec 

%%
 
schema:         db_spec dds_stmts closing_brace
        ;
 
closing_brace:
		'}'
	|	'}' ';'
        {
			dderror("';' ist nach '}' nicht erforderlich", $2.numline);
        }
	|	error
		{
			yyerrok;
			dderror("Fehlende schlieszende '}'",line);
		}
	;
 
db_spec:
		T_DATABASE T_IDENT '{'
        {
			strcpy (db_name, $2.str);
			open_files ();
			PageSize = PAGESIZE;
			strcpy (dbd_ext, "stb");
			dbd_ext[3] = '\0';
        }
	|	T_DATABASE T_IDENT '[' T_NUMBER ']' '{'
		{
			strcpy (db_name, $2.str);
			open_files();
			PageSize = $4.num;
			strcpy (dbd_ext, "stb");
			dbd_ext[3] = '\0';
		}
	|	T_DATABASE T_IDENT T_EXTENSION T_IDENT'{'
		{
			strcpy (db_name, $2.str);
			open_files ();
			PageSize = PAGESIZE;
			strncpy (dbd_ext, $4.str, 3);
			dbd_ext[3] = '\0';
		}
	|	T_DATABASE T_IDENT '[' T_NUMBER ']' T_EXTENSION T_IDENT '{'
		{
			strcpy (db_name, $2.str);
			open_files();
			PageSize = $4.num;
			strncpy (dbd_ext, $7.str, 3);
			dbd_ext[3] = '\0';
		}
	|	T_DATABASE T_IDENT error
		{
			yyerrok;
			dderror ("Fehlende oeffnende '{'", $2.strline);
			strcpy (db_name, $2.str);
			open_files();
		}
	;
 
id_list:
		T_IDENT
		{
			id_list = (ID_INFO *)calloc (1, sizeof (ID_INFO));
			if (id_list == NULL)
				abort ("Kein Speicherplatz");
			strcpy (id_list->id_name, $1.str);
			id_list->next_id = NULL;
			currid = id_list;
		}
	|	id_list ',' T_IDENT
		{
			currid->next_id = (ID_INFO *)calloc (1, sizeof (ID_INFO));
			if ((currid = currid->next_id) == NULL)
				abort ("Kein Speicherplatz");
			strcpy (currid->id_name, $3.str);
			currid->next_id = NULL;
		}
	|	error ';'
		{
			dderror ("Name ist kein Identifier", $2.numline);
			unput (';');
		}
	;
 
dds_stmts:	
		dds_stmt
	|	dds_stmts dds_stmt
	;
 
dds_stmt:
		version_spec
	|	file_spec
	|	record_spec
	|	error ';'
		{
			dderror ("Fragwürdiger dds Operator", $2.numline);
		}
	;
 
file_spec:
		data_file_spec          /* Datenfile */
	|	btree_file_spec         /* BTree Keyfile */
	|	geotree_file_spec       /* GeoTree Keyfile */
	|	backup_file_spec        /* Backupfile */
	;
 
data_file_spec: T_DATA T_FILE file_id T_CONTAINS id_list ';'
        {
			add_file ($3.str, 'd', id_list);
        }
	|	T_DATA T_FILE error ';'
		{
			dderror ("Fragwürdige Dateideklaration", $2.numline);
		}
	;
 
btree_file_spec: btree T_KEY T_FILE file_id T_CONTAINS id_list ';'
		{
			add_file ($4.str, 'k', id_list);
		}
	|       btree T_KEY T_FILE error ';'
		{
			dderror ("Fragwürdige Btree Keydateideklaration", $2.numline);
		}
	;
 
btree:	/* nothing */
	|	T_BTREE
	;
 
geotree_file_spec: 
		geotree T_KEY T_FILE file_id T_AND file_id T_CONTAINS id_list ';'
		{
			add_file ($4.str, $1.num, id_list);
			add_file ($6.str, 'K', id_list);
		}
	|	geotree T_KEY T_FILE error ';'
		{
			dderror ("Fragwürdige GeoTree Keydateideklaration", $2.numline);
		}
	;
 
geotree:        T_QTREE         /* QuadTree (2D) */
                { $$.num = 'q'; }
        |       T_HTREE         /* HexTree (2D-Container) */
                { $$.num = 'h'; }
        |       T_CTREE         /* CubicTree (3D-Container) */
                { $$.num = 'c'; }
        ;
 
backup_file_spec:       T_ENABLE T_BACKUP T_TO T_FILE file_id ';'
                {
#ifdef BACKUP
                        add_file ($5.str, 'b', NULL);
#else
                        dderror ("Backup nicht generiert", $2.numline);
#endif
                }
        |       T_DISABLE T_BACKUP ';'
                {
#ifdef BACKUP
                        backup_flag = -1;
#else
                        dderror ("Backup nicht generiert", $2.numline);
#endif
                }
        |       T_ENABLE T_BACKUP error ';'
                {
#ifdef BACKUP
                        dderror ("Fragwürdige Backup-Dateideklaration", $2.numline);
#else
                        dderror ("Backup nicht generiert", $2.numline);
#endif
                }
        ;

version_spec:	T_VERSION T_NUMBER '.' T_NUMBER '.' T_NUMBER '.' T_NUMBER ';'
		{
		// VersionsNummer (optional)
			DBVersion = ((long)$2.num << 24) + ((long)$4.num << 16) +
				    ($6.num <<  8) +  $8.num;
		}
	|	T_VERSION error ';'
		{
			dderror ("Fragwürdige Versionsnummer", $1.numline);
		}
	;
 
key_field:      T_UNIQUE T_ONLY T_KEY
                { $$.num = 'U'; }
        |       T_UNIQUE T_KEY
                { $$.num = 'u'; }
        |       T_ONLY T_KEY
                { $$.num = 'D'; }
        |       T_KEY
                { $$.num = 'd'; }
        |       /* nothing */
                { $$.num = 'n'; }
        ;
 
file_id:        T_IDENT
        |       T_STRING
        ;
 
record_spec:    rec_id field_defs closing_brace
                {
                        close_record ();
                }
        |       T_RECORD error closing_brace
                {
                        dderror ("Fragwürdige Recorddeklaration", $1.numline);
                }
        ;
 
rec_id:
		T_RECORD T_IDENT '{'
        {
			add_record ($2.str);
        }
	;
 
field_defs:
		field_spec
	|	field_defs field_spec
	;
 
field_spec:
		key_field basic_type var ';'
		{
			strcat(var_str, ";");
			if ($2.num == 'c' && multidim )
				$2.num = 'C';
			add_field ($3.str, $2.num, type_size*var_size, $1.num, var_str);
		}
	|       grouped_field_spec '{' field_defs '}' T_IDENT size_specs ';'
		{
			if (multidim == 2)
				dderror ("Struktur-/Unionfelder mit mehreren Dimensionen nicht erlaubt", $2.numline);
			close_struct ($1.num, $5.str, $6.num);
		}
	|       error ';'
		{
			dderror ("Fragwürdige Felddeklaration",$2.numline);
		}
	;
		
grouped_field_spec:
		key_field T_STRUCT
		{
			add_field ("struct", 'g', 0, $1.num, "struct {");
			$$.num = $1.num;
		}
	|       key_field T_UNION
		{
			add_field ("union", 'G', 0, $1.num, "union {");
			$$.num = $1.num;
		}
	;
 
basic_type:
		T_INT
		{
			strcpy(var_str,"int ");
			$$.num = 'i';
			type_size = INT_SIZE; 
		}
	|       T_SHORT 
		{
			strcpy(var_str,"short ");
			$$.num = 's';
			type_size = SHORT_SIZE; 
		}
	|       T_LONG 
		{
			strcpy(var_str,"long ");
			$$.num = 'l';
			type_size = LONG_SIZE; 
		}
	|       T_FLOAT
		{
			strcpy(var_str,"float ");
			$$.num = 'f';
			type_size = FLOAT_SIZE; 
		}
	|       T_DOUBLE
		{
			strcpy(var_str,"double ");
			$$.num = 'F';
			type_size = DOUBLE_SIZE; 
		}
	|       T_CHAR
		{
			strcpy(var_str,"char ");
			$$.num = 'c';
			type_size = CHAR_SIZE; 
		}
	|       T_DB_ADDR
		{
			strcpy(var_str,"DB_ADDR ");
			$$.num = 'd';
			type_size = DB_ADDR_SIZE; 
		}
	|       T_IDENT
		{
			dderror("Fragwürdiger Datentyp", $1.strline);
		}
	;
		
var:    var_name size_specs
		{
			strcpy($$.str, $1.str);
			var_size = $2.num;
		}
	;
 
var_name:       T_IDENT
		{
			strcat(var_str,$1.str);
			strcpy($$.str, $1.str);
		}
	;
 
size_specs:
		/* nothing */
		{
			multidim = 0;
			$$.num = 1;
		}
	|       size
		{
			multidim = 1;
			$$.num = $1.num;
		}
	|       size_specs size
		{
			multidim = 2;
			$$.num = $1.num * $2.num;
		}
	;
 
size:
		'[' T_NUMBER ']'
		{
			strcat(var_str, "[");
			strcat(var_str, itos($2.num));
			strcat(var_str, "]");
			$$.num = $2.num;
		}
	|       '[' T_IDENT ']'
		{
			dderror("Fragwürdige Feldgrößendeklaration", $2.strline);
			var_str[0] = '\0';
			$$.num = 2;
		}
	;

%%

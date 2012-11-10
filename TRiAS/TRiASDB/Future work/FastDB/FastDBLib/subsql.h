//-< SUBSQL.H >------------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Interactive data manipulation language (subset of SQL)
//-------------------------------------------------------------------*--------*

#ifndef __SUBSQL_H__
#define __SUBSQL_H__

enum SubSqlTokens { 
    tkn_array = tkn_last_token, 
    tkn_autoincrement,
    tkn_backup,
    tkn_bool,
    tkn_commit,
    tkn_compactify,
    tkn_create,
    tkn_delete,
    tkn_describe,
    tkn_drop,
    tkn_exit,
    tkn_hash,
    tkn_help,
    tkn_index,
    tkn_int1,
    tkn_int2,
    tkn_int4,
    tkn_int8,
    tkn_of,
    tkn_on,
    tkn_open,
    tkn_real4, 
    tkn_real8, 
    tkn_reference,
    tkn_rollback,
    tkn_server,
    tkn_set,
    tkn_stop,
    tkn_semi,
    tkn_show,
    tkn_to, 
    tkn_update,
    tkn_values
};
	
    

class dbList { 
  public:
    enum NodeType { 
	nInteger,
	nBool,
	nReal,
	nString,
	nTuple,
	nAutoinc,
	nIdentifier
    };

    dbList* next;
    int     type;
    union { 
	bool  bval;
	db_int8  ival;
	real8 fval;
	char* sval;
	struct { 
	    int     nComponents;
	    dbList* components;
	} aggregate;
    };

    ~dbList() { 
	if (type == nTuple) {
	    delete aggregate.components;
	} else if (type == nString || type == nIdentifier) {
	    delete[] sval;
	}
    }

    dbList(int type) { 
	this->type = type;
	next = NULL; 
    }
};


struct tableField { 
    char* name;
    char* refTableName;
    int   type;
    
    tableField() { name = refTableName = NULL; }
    ~tableField() { delete[] name; delete[] refTableName; }
};

class dbUpdateElement { 
  public:
    dbUpdateElement*   next;
    dbFieldDescriptor* field;
    dbExprNode*        value;
    char*              strValue;

    dbUpdateElement() { 
	next = NULL;
	strValue = NULL;
    }
    ~dbUpdateElement() { 
	delete[] strValue;
    }
};

class dbSubSql : public dbDatabase { 
  private:
    int   pos;
    int   line;
    int   tknPos;
    char* buf;
    int   buflen;
    FILE* in;
    bool  opened;
    db_int8  ival;
    real8 fval;
    char* name;

    static char* prompt;

    dbTableDescriptor* droppedTables;
    dbTableDescriptor* existedTables;

    dbQuery query;

    void handleError(dbErrorClass error, char const* msg = NULL,  int arg = 0);

    void error(char const* msg);

    int  get();
    void unget(int ch);
    int  scan();
    bool parse();

    bool expect(char* expected, int token);
    
    void recovery();

    bool isValidOid(oid_t oid);

    static void dumpRecord(byte* record, dbFieldDescriptor* first);
    static int calculateRecordSize(dbList* list, int offs,
				   dbFieldDescriptor* first);
    int  initializeRecordFields(dbList* node, byte* dst, int offs, 
				      dbFieldDescriptor* first);
    bool insertRecord(dbList* list, dbTableDescriptor* desc);
    bool readCondition();
    int  readExpression();
    int  readValues(dbList** chain);
    bool updateFields(dbAnyCursor* cursor, dbUpdateElement* elems);
    bool createTable();
    int  parseType();
    int  updateRecords(dbTableDescriptor* desc, dbList *fields, dbList *values, dbAnyCursor &cursor, byte *buf);
    dbFieldDescriptor* readFieldName();
  public:
    void run(int argc, char* argv[]);
    
    dbSubSql();
    virtual~dbSubSql();
};   


#endif

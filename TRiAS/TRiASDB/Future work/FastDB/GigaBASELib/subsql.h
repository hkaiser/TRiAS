//-< SUBSQL.H >------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Interactive data manipulation language (subset of SQL)
//-------------------------------------------------------------------*--------*

#ifndef __SUBSQL_H__
#define __SUBSQL_H__

enum SubSqlTokens { 
     tkn_all = tkn_last_token,
    tkn_array, 
    tkn_backup,
    tkn_bool,
    tkn_commit,
    tkn_create,
    tkn_delete,
    tkn_drop,
    tkn_error,
    tkn_exit,
    tkn_hash,
    tkn_help,
    tkn_index,
    tkn_insert, 
    tkn_int1,
    tkn_int2,
    tkn_int4,
    tkn_int8,
    tkn_into,
    tkn_of,
    tkn_on,
    tkn_open,
    tkn_real4, 
    tkn_real8, 
    tkn_reference,
    tkn_restore,
    tkn_rollback,
    tkn_select,
    tkn_server,
    tkn_stop,
    tkn_semi,
    tkn_show,
    tkn_to, 
    tkn_table,
    tkn_values
};
	
struct tableField { 
    char* name;
    char* refTableName;
    int   type;
    
    tableField() { name = refTableName = NULL; }
    ~tableField() { delete[] name; delete[] refTableName; }
};
 

class dbList { 
  public:
    enum NodeType { 
	nInteger,
	nBool,
	nReal,
	nString,
	nTuple
    };

    dbList* next;
    int     type;
    union { 
	bool  bval;
	int8  ival;
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
	} else if (type == nString) {
	    delete[] sval;
	}
    }

    dbList(int type) { 
	this->type = type;
	next = NULL; 
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
    int8  ival;
    real8 fval;
    char* name;
    dbTableDescriptor* metatable;

    static char* prompt;

    dbTableDescriptor* droppedTables;

    dbQuery query;

    void handleError(dbErrorClass error, char const* msg = NULL,  int arg = 0);

    void error(char const* msg);

    int  get();
    void unget(int ch);
    int  scan();
    bool parse();

    bool expect(char* expected, int token);
    
    void recovery();

    static void dumpRecord(byte* record, dbFieldDescriptor* first);
    static int calculateRecordSize(dbList* list, int offs,
				   dbFieldDescriptor* first);
    static int initializeRecordFields(dbList* node, byte* dst, int offs, 
				      dbFieldDescriptor* first);
    bool insertRecord(dbList* list, dbTableDescriptor* desc);
    bool readCondition();
    int  readValues(dbList** chain);
    bool createTable();
    int  parseType();

    dbFieldDescriptor* readFieldName();
  public:
    void run(int argc, char* argv[]);
    
    dbSubSql();
    virtual~dbSubSql();
};   


#endif

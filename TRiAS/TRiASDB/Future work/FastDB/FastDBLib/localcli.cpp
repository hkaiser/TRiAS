//-< LOCALCLI.CPP >--------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Jun-2002  K.A. Knizhnik  * / [] \ *
//                          Last update: 20-Jun-2002  K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Implementation of local C interface to database
//-------------------------------------------------------------------*--------*

#define INSIDE_FASTDB

#include "localcli.h"
#include "ttree.h"
#include "hashtab.h"
#include "symtab.h"
#include <ctype.h>

dbCLI dbCLI::instance;

int cli_open(char const* server_url,
	     int         max_connect_attempts,
	     int         reconnect_timeout_sec)
{
    return cli_bad_address;
}

int cli_create(char const* databaseName,
	       char const* filePath,
	       unsigned    transactionCommitDelay, 
	       int         openAttr, 
	       size_t      initDatabaseSize)
{
    return dbCLI::instance.create_session(databaseName, filePath, transactionCommitDelay, openAttr, initDatabaseSize);
}

int dbCLI::create_session(char const* databaseName, 
			  char const* filePath,
			  unsigned    transactionCommitDelay, 
			  int         openAttr, 
			  size_t      initDatabaseSize)
{
    dbCriticalSection cs(sessionMutex);
    dbDatabase* db = NULL; 
    session_desc* s;
    for (s = active_session_list; s != NULL; s = s->next) { 
	if (strcmp(s->name, databaseName) == 0) { 
	    db = s->db;
	    db->accessCount += 1;
	    break;
	}
    }
    if (db == NULL) { 
	db = new dbDatabase((openAttr & cli_open_readonly) 
			    ? dbDatabase::dbReadOnly : dbDatabase::dbAllAccess,
			    initDatabaseSize);	 
	if (!db->open(databaseName, filePath, 0, transactionCommitDelay)) { 
	    return cli_database_not_found;
	}
	dbTable* table = (dbTable*)db->getRow(dbMetaTableId);
	dbTableDescriptor* metatable = new dbTableDescriptor(table);
	db->linkTable(metatable, dbMetaTableId);
	oid_t tableId = table->firstRow;
	while (tableId != 0) {
	    table = (dbTable*)db->getRow(tableId);
	    dbTableDescriptor* desc;
	    for (desc = db->tables; desc != NULL && desc->tableId != tableId; desc = desc->nextDbTable);
	    if (desc == NULL) { 
		desc = new dbTableDescriptor(table);
		db->linkTable(desc, tableId);
		desc->setFlags();
	    }
	    tableId = table->next;
	}
	if (!db->completeDescriptorsInitialization()) {
	    return cli_table_not_found;
	}
	db->accessCount = 1;
    }
    s = sessions.allocate();
    s->name = new char[strlen(databaseName) + 1];
    strcpy(s->name, databaseName);
    s->db = db;
    s->stmts = NULL;
    s->next = active_session_list;
    s->existed_tables = db->tables;
    s->dropped_tables = NULL;
    active_session_list = s;
    return s->id;
}


int cli_close(int session)
{
    return dbCLI::instance.close(session);
}

int dbCLI::close(int session)
{
    dbCriticalSection cs(sessionMutex);
    statement_desc *stmt, *next;
    session_desc* s = sessions.get(session);
    if (s == NULL) {
	return cli_bad_descriptor;
    }    
    for (stmt = s->stmts; stmt != NULL; stmt = next) {
	next = stmt->next;
	free_statement(stmt);
    }
    if (--s->db->accessCount == 0) { 
	dbTableDescriptor *desc, *next_desc;
	for (desc = s->db->tables; desc != NULL; desc = next_desc) {
	    next_desc = desc->nextDbTable;
	    if (!desc->isStatic) { 
		delete desc;
	    }
	}
	s->db->tables = NULL;
	s->db->close();
	delete s->db;
    }
    while (s->dropped_tables != NULL) {
	dbTableDescriptor* next = s->dropped_tables->nextDbTable;
	delete s->dropped_tables;
	s->dropped_tables = next;
    }
    session_desc** spp;
    for (spp = &active_session_list; *spp != s; spp = &(*spp)->next);
    *spp = s->next;
    delete[] s->name;
    sessions.free(s);

    return cli_ok;
}

int cli_statement(int session, char const* sql)
{
    return dbCLI::instance.create_statement(session, sql);
}

int dbCLI::create_statement(int session, char const* sql)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    statement_desc* stmt = statements.allocate();
    stmt->sql = new char[strlen(sql)+1];
    strcpy(stmt->sql, sql);
    stmt->columns = NULL;
    stmt->params = NULL;
    stmt->session = s;
    stmt->for_update = 0;
    stmt->first_fetch = true;
    stmt->prepared = false;
    stmt->n_params = 0;
    stmt->n_columns = 0;
    stmt->n_autoincremented_columns = 0;
    stmt->oid = 0;
    stmt->next = s->stmts;
    stmt->updated = false;
    stmt->table = NULL;
    s->stmts = stmt;
    char const* p = sql;
    parameter_binding** last = &stmt->params;
    while (*p != '\0') {
	if (*p == '\'') {
	    do {
		do {
		    p += 1;
		} while (*p != '\0' && *p != '\'');
		if (*p == '\0') {
		    *last = NULL;
		    free_statement(stmt);
		    return cli_bad_statement;
		}
	    } while (*++p == '\'');
	} else if (*p == '%') {
	    stmt->n_params += 1;
	    char const* q = p++;
	    while (isalnum(*p)) p += 1;
	    if (*p == '%') {
		*last = NULL;
		free_statement(stmt);
		return cli_bad_statement;
	    }
	    parameter_binding* pb = parameter_allocator.allocate();
	    int len = p - q;
	    pb->name = new char[len+1];
	    memcpy(pb->name, q, len);
	    pb->name[len] = '\0';
	    *last = pb;
	    last = &pb->next;
	    pb->var_ptr = NULL;
	} else {
	    p += 1;
	}
    }
    *last = NULL;
    return stmt->id;
}

int cli_parameter(int           statement,
		  char const* param_name,
		  int           var_type,
		  void*         var_ptr)
{
    return dbCLI::instance.bind_parameter(statement, param_name, var_type, var_ptr);
}


int dbCLI::bind_parameter(int           statement,
			  char const* param_name,
			  int           var_type,
			  void*         var_ptr)
{
    if ((unsigned)var_type >= cli_array_of_oid) {
	return cli_unsupported_type;
    }
    statement_desc* s = statements.get(statement);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    s->prepared = false;
    for (parameter_binding* pb = s->params; pb != NULL; pb = pb->next) {
	if (strcmp(pb->name, param_name) == 0) {
	    pb->var_ptr  = var_ptr;
	    pb->var_type = var_type;
	    return cli_ok;
	}
    }
    return cli_parameter_not_found;
}

int cli_column(int           statement,
	       char const* column_name,
	       int           var_type,
	       int*          var_len,
	       void*         var_ptr)
{
    return dbCLI::instance.bind_column(statement, column_name, var_type, var_len, var_ptr);
}

int dbCLI::bind_column(int           statement,
		       char const* column_name,
		       int           var_type,
		       int*          var_len,
		       void*         var_ptr)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    if ((unsigned)var_type >= cli_unknown) { 
	return cli_unsupported_type;
    }
    s->prepared = false;
    if (var_type == cli_autoincrement) {
	s->n_autoincremented_columns += 1;
    }
    column_binding* cb = column_allocator.allocate();
    cb->name = new char[strlen(column_name) + 1];
    cb->next = s->columns;
    s->columns = cb;
    s->n_columns += 1;
    strcpy(cb->name, column_name);
    cb->var_type = var_type;
    cb->var_len = var_len;
    cb->var_ptr = var_ptr;
    cb->set_fnc = NULL;
    cb->get_fnc = NULL;
    return cli_ok;
}

int cli_array_column(int            statement,
		     char const*  column_name,
		     int            var_type,
		     void*          var_ptr,
		     cli_column_set set,
		     cli_column_get get)
{
    return cli_array_column_ex(statement, column_name, var_type, var_ptr, 
			       (cli_column_set_ex)set, (cli_column_get_ex)get);
}

int cli_array_column_ex(int               statement,
			char const*     column_name,
			int               var_type,
			void*             var_ptr,
			cli_column_set_ex set,
			cli_column_get_ex get)
{
    return dbCLI::instance.bind_array_column(statement, column_name, var_type, var_ptr, set, get);
}


int dbCLI::bind_array_column(int               statement,
			     char const*     column_name,
			     int               var_type,
			     void*             var_ptr,
			     cli_column_set_ex set,
			     cli_column_get_ex get)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    if (var_type < cli_asciiz || var_type > cli_array_of_string) {
	return cli_unsupported_type;
    }
    s->prepared = false;
    column_binding* cb = new column_binding;
    cb->name = new char[strlen(column_name) + 1];
    cb->next = s->columns;
    s->columns = cb;
    s->n_columns += 1;
    strcpy(cb->name, column_name);
    cb->var_type = var_type;
    cb->var_len = NULL;
    cb->var_ptr = var_ptr;
    cb->set_fnc = set;
    cb->get_fnc = get;
    return cli_ok;
}

int dbCLI::match_columns(char const* table_name, statement_desc* stmt)
{    
    stmt->table = stmt->session->db->findTable(table_name);
    if (stmt->table == NULL) {
	return cli_table_not_found;
    }
    for (column_binding* cb = stmt->columns; cb != NULL; cb = cb->next) { 
	cb->field = stmt->table->find(cb->name);
	if (cb->field == NULL) { 
	    printf("cb->name='%s'\n", cb->name);
	    return cli_column_not_found;
	}
    }
    return cli_ok;
}

int cli_fetch(int statement, int for_update)
{
    return dbCLI::instance.fetch(statement, for_update);
}

int dbCLI::fetch(int statement, int for_update)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    stmt->for_update = for_update;
    stmt->oid = 0;
    if (!stmt->prepared) {
	int tkn;
	sql_scanner scanner(stmt->sql);
	if (scanner.get() != tkn_select) {
	    return cli_bad_statement;
	}
	if ((tkn = scanner.get()) == tkn_all) {
	    tkn = scanner.get();
	}
	if (tkn == tkn_from && scanner.get() == tkn_ident) {
	    int rc = match_columns(scanner.identifier(), stmt);
	    if (rc != cli_ok) { 
		return rc;
	    }
	} else { 
	    return cli_bad_statement;
	}
	char* p = scanner.current_position(), *q = p;
	parameter_binding* pb = stmt->params;
	stmt->query.reset();
	while (*p != '\0') {
	    if (*p == '\'') {
		do {
		    do {
			p += 1;
		    } while (*p != '\0' && *p != '\'');
		    if (*p == '\0') {
			return cli_bad_statement;
		    }
		} while (*++p == '\'');
	    } else if (*p == '%') {
		if (p != q) { 
		    *p = '\0';
		    stmt->query.append(dbQueryElement::qExpression, q);		    
		}
		if (pb->var_ptr == NULL) { 
		    return cli_unbound_parameter;
		}
		switch(pb->var_type) {
		  case cli_oid:
		    stmt->query.append(dbQueryElement::qVarReference, pb->var_ptr);
		    break;
		  case cli_bool:
		    stmt->query.append(dbQueryElement::qVarBool, pb->var_ptr);
		    break;
		  case cli_int1:
		    stmt->query.append(dbQueryElement::qVarInt1, pb->var_ptr);
		    break;
		  case cli_int2:
		    stmt->query.append(dbQueryElement::qVarInt2, pb->var_ptr);
		    break;
		  case cli_int4:
		    stmt->query.append(dbQueryElement::qVarInt4, pb->var_ptr);
		    break;
		  case cli_int8:
		    stmt->query.append(dbQueryElement::qVarInt8, pb->var_ptr);
		    break;
		  case cli_real4:
		    stmt->query.append(dbQueryElement::qVarReal4, pb->var_ptr);
		    break;
		  case cli_real8:
		    stmt->query.append(dbQueryElement::qVarReal8, pb->var_ptr);
		    break;
		  case cli_asciiz:
		    stmt->query.append(dbQueryElement::qVarString, pb->var_ptr);
		    break;
		  case cli_pasciiz:
		    stmt->query.append(dbQueryElement::qVarStringPtr, pb->var_ptr);
		    break;
		  case cli_array_of_oid:
		    stmt->query.append(dbQueryElement::qVarArrayOfRef, pb->var_ptr);
		    break;
		  default:
		    return cli_unsupported_type;
		    
		}
		while (isalnum(*++p));
		q = p;
		pb = pb->next;
	    } else {
		p += 1;
	    }
	}
	if (p != q) { 
	    stmt->query.append(dbQueryElement::qExpression, q);
	}
	stmt->prepared = true;
    }
    stmt->cursor.setTable(stmt->table);
    stmt->cursor.reset();
    return stmt->cursor.select(stmt->query, for_update ? dbCursorForUpdate : dbCursorViewOnly);
}


int dbCLI::fetch_columns(statement_desc* stmt)
{
    stmt->first_fetch = false;
    if (stmt->cursor.isEmpty()) {
	return cli_not_found;
    }
    stmt->updated = false;
    char* data = (char*)stmt->session->db->getRow(stmt->cursor.currId);
    for (column_binding* cb = stmt->columns; cb != NULL; cb = cb->next) {
	char* src = data + cb->field->dbsOffs;
	char* dst = (char*)cb->var_ptr;
	switch (cb->field->type) {
	  case dbField::tpBool:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(bool*)src;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = *(bool*)src ? 1 : 0;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = *(bool*)src ? 1 : 0;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = *(bool*)src ? 1 : 0;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(bool*)src ? 1 : 0;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(bool*)src ? 1 : 0;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(bool*)src ? 1 : 0;
		continue;
	    }
	    break;	    
	  case dbField::tpInt1:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(int1*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = *(int1*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = *(int1*)src;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = *(int1*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(int1*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(int1*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(int1*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt2:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(int2*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = (int1)*(int2*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = *(int2*)src;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = *(int2*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(int2*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(int2*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(int2*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt4:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(int4*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = (cli_int1_t)*(int4*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = (cli_int2_t)*(int4*)src;
		continue;
	      case cli_int4:
	      case cli_autoincrement:
		*(cli_int4_t*)dst = *(int4*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(int4*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(int4*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(int4*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt8:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(db_int8*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = (cli_int1_t)*(db_int8*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = (cli_int2_t)*(db_int8*)src;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = (cli_int4_t)*(db_int8*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(db_int8*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(db_int8*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(db_int8*)src;
		continue;
	    }
	    break;
	  case dbField::tpReal4:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(real4*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = (cli_int1_t)*(real4*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = (cli_int2_t)*(real4*)src;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = (cli_int4_t)*(real4*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = (db_int8)*(real4*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = *(real4*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(real4*)src;
		continue;
	    }
	    break;
	  case dbField::tpReal8:
	    switch (cb->var_type) {
	      case cli_bool:
		*(cli_bool_t*)dst = *(real8*)src != 0;
		continue;
	      case cli_int1:
		*(cli_int1_t*)dst = (cli_int1_t)*(real8*)src;
		continue;
	      case cli_int2:
		*(cli_int2_t*)dst = (cli_int2_t)*(real8*)src;
		continue;
	      case cli_int4:
		*(cli_int4_t*)dst = (cli_int4_t)*(real8*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = (db_int8)*(real8*)src;
		continue;
	      case cli_real4:
		*(cli_real4_t*)dst = (real4)*(real8*)src;
		continue;
	      case cli_real8:
		*(cli_real8_t*)dst = *(real8*)src;
		continue;
	    }
	    break;
	  case dbField::tpReference:
	    if (cb->var_type == cli_oid) { 
		*(cli_oid_t*)dst = *(oid_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpString:
	    if (cb->var_type == cli_asciiz || cb->var_type == cli_pasciiz) { 
		if (cb->var_type == cli_pasciiz) { 
		    dst = *(char**)dst;
		}
		dbVarying* v = (dbVarying*)src;
		int size = v->size;
		if (cb->set_fnc != NULL) {
		    dst = (char*)cb->set_fnc(cli_array_of_string, dst, size, 
					     cb->name, stmt->id);
		    memcpy(dst, data + v->offs, size);
		} else { 
		    int n = size;
		    if (cb->var_len != NULL) {
			if (n > *cb->var_len) {
			    n = *cb->var_len;
			}
			*cb->var_len = size;
		    }
		    memcpy(dst, data + v->offs, n);
		}
		continue;
	    }
	    break;
	  case dbField::tpArray:
	    if (cb->var_type >= cli_array_of_oid && cb->var_type <= cli_array_of_string) 
	    { 
		dbVarying* v = (dbVarying*)src;
		int n = v->size;
		src = data + v->offs;
		if (cb->set_fnc != NULL) {
		    dst = (char*)cb->set_fnc(cb->var_type, dst, n, 
					     cb->name, stmt->id);
		} else { 
		    int size = n;
		    if (cb->var_len != NULL) {
			if (n > *cb->var_len) {
			    n = *cb->var_len;
			}
			*cb->var_len = size;
		    }
		}
		switch (cb->field->components->type) {
		  case dbField::tpBool:
		    if (cb->var_type == cli_array_of_bool) { 
			cli_bool_t* dst_elem = (cli_bool_t*)dst;
		        bool*       src_elem = (bool*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpInt1:
		    if (cb->var_type == cli_array_of_int1) { 
			cli_int1_t* dst_elem = (cli_int1_t*)dst;
		        int1*       src_elem = (int1*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpInt2:
		    if (cb->var_type == cli_array_of_int2) { 
			cli_int2_t* dst_elem = (cli_int2_t*)dst;
		        int2*       src_elem = (int2*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpInt4:
		    if (cb->var_type == cli_array_of_int4) { 
			cli_int4_t* dst_elem = (cli_int4_t*)dst;
		        int4*       src_elem = (int4*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpInt8:
		    if (cb->var_type == cli_array_of_int8) { 
			cli_int8_t* dst_elem = (cli_int8_t*)dst;
		        db_int8*       src_elem = (db_int8*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpReal4:
		    if (cb->var_type == cli_array_of_real4) { 
			cli_real4_t* dst_elem = (cli_real4_t*)dst;
		        real4*       src_elem = (real4*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpReal8:
		    if (cb->var_type == cli_array_of_real8) { 
			cli_real8_t* dst_elem = (cli_real8_t*)dst;
		        real8*       src_elem = (real8*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpReference:
		    if (cb->var_type == cli_array_of_oid) { 
			cli_oid_t* dst_elem = (cli_oid_t*)dst;
		        oid_t*     src_elem = (oid_t*)src;
			while (--n >= 0) *dst_elem++ = *src_elem++;
			continue;
		    }
		    break;
		  case dbField::tpString:
		    if (cb->var_type == cli_array_of_string) { 
			char** dst_elem = (char**)dst;
		        dbVarying* src_elem = (dbVarying*)src;
			while (--n >= 0) { 
			    *dst_elem++ = (char*)((char*)src_elem + src_elem->offs);
			    src_elem += 1;
			}
			continue;
		    }		    
		}
	    }
	}
	return cli_unsupported_type;
    }
    return cli_ok;
}


int dbCLI::store_columns(char* data, statement_desc* stmt)
{
    for (column_binding* cb = stmt->columns; cb != NULL; cb = cb->next) 
    {
	char* dst = data + cb->field->appOffs;
	char* src = (char*)cb->var_ptr;
	switch (cb->field->type) {
	  case dbField::tpBool:
	    switch (cb->var_type) {
	      case cli_bool:
		*(bool*)dst = *(cli_bool_t*)src;
		continue;
	      case cli_int1:
		*(bool*)dst = *(cli_int1_t*)src != 0;
		continue;
	      case cli_int2:
		*(bool*)dst = *(cli_int2_t*)src != 0;
		continue;
	      case cli_int4:
		*(bool*)dst = *(cli_int4_t*)src != 0;
		continue;
	      case cli_int8:
		*(bool*)dst = *(db_int8*)src != 0;
		continue;
	      case cli_real4:
		*(bool*)dst = *(cli_real4_t*)src != 0;
		continue;
	      case cli_real8:
		*(bool*)dst = *(cli_real8_t*)src != 0;
		continue;
	    }
	    break;	    
	  case dbField::tpInt1:
	    switch (cb->var_type) {
	      case cli_bool:
		*(int1*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(int1*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(int1*)dst = (int1)*(cli_int2_t*)src;
		continue;
	      case cli_int4:
		*(int1*)dst = (int1)*(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(int1*)dst = (int1)*(db_int8*)src;
		continue;
	      case cli_real4:
		*(int1*)dst = (int1)*(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(int1*)dst = (int1)*(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt2:
	    switch (cb->var_type) {
	      case cli_bool:
		*(int2*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(int2*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(int2*)dst = *(cli_int2_t*)src;
		continue;
	      case cli_int4:
		*(int2*)dst = (int2)*(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(int2*)dst = (int2)*(db_int8*)src;
		continue;
	      case cli_real4:
		*(int2*)dst = (int2)*(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(int2*)dst = (int2)*(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt4:
	    switch (cb->var_type) {
	      case cli_bool:
		*(int4*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(int4*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(int4*)dst = *(cli_int2_t*)src;
		continue;
	      case cli_autoincrement:
#ifdef AUTOINCREMENT_SUPPORT
		*(int4*)dst = fd->defTable->autoincrementCount;
#endif
		continue;
	      case cli_int4:
		*(int4*)dst = *(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(int4*)dst = (int4)*(db_int8*)src;
		continue;
	      case cli_real4:
		*(int4*)dst = (int4)*(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(int4*)dst = (int4)*(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpInt8:
	    switch (cb->var_type) {
	      case cli_bool:
		*(db_int8*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(db_int8*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(db_int8*)dst = *(cli_int2_t*)src;
		continue;
	      case cli_int4:
		*(db_int8*)dst = *(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(db_int8*)dst = *(db_int8*)src;
		continue;
	      case cli_real4:
		*(db_int8*)dst = (db_int8)*(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(db_int8*)dst = (db_int8)*(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpReal4:
	    switch (cb->var_type) {
	      case cli_bool:
		*(real4*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(real4*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(real4*)dst = *(cli_int2_t*)src;
		continue;
	      case cli_int4:
		*(real4*)dst = *(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(real4*)dst = *(db_int8*)src;
		continue;
	      case cli_real4:
		*(real4*)dst = *(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(real4*)dst = (real4)*(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpReal8:
	    switch (cb->var_type) {
	      case cli_bool:
		*(real8*)dst = *(cli_bool_t*)src ? 1 : 0;
		continue;
	      case cli_int1:
		*(real8*)dst = *(cli_int1_t*)src;
		continue;
	      case cli_int2:
		*(real8*)dst = *(cli_int2_t*)src;
		continue;
	      case cli_int4:
		*(real8*)dst = *(cli_int4_t*)src;
		continue;
	      case cli_int8:
		*(real8*)dst = *(db_int8*)src;
		continue;
	      case cli_real4:
		*(real8*)dst = *(cli_real4_t*)src;
		continue;
	      case cli_real8:
		*(real8*)dst = *(cli_real8_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpReference:
	    if (cb->var_type == cli_oid) { 
		*(oid_t*)dst = *(cli_oid_t*)src;
		continue;
	    }
	    break;
	  case dbField::tpString:
	    if (cb->var_type == cli_pasciiz) { 
		*(char**)dst = *(char**)src;
		continue;
	    } else if (cb->var_type == cli_asciiz) { 
		if (cb->get_fnc != NULL) {
		    int len;
		    src = (char*)cb->get_fnc(cb->var_type, src, &len, 
					     cb->name, stmt->id);
		}
		*(char**)dst = src;
		continue;
	    }
	    break;
	  case dbField::tpArray:
	    if (cb->var_type >= cli_array_of_oid && cb->var_type <= cli_array_of_string) 
	    { 
		int size = 0;
		if (cb->set_fnc != NULL) {
		    src = (char*)cb->get_fnc(cb->var_type, src, &size, 
					     cb->name, stmt->id);
		} else { 
		    if (cb->var_len != NULL) {
			size = *cb->var_len; 
		    } else { 
			return cli_incompatible_type;
		    }
		}
		if (cb->var_type == cli_array_of_string) { 
		    if (cb->field->components->type != dbField::tpString) { 
			return cli_incompatible_type;
		    }
		} else if ((size_t)sizeof_type[cb->var_type - cli_array_of_oid] != cb->field->components->appSize) {
		    return cli_incompatible_type;
		}
		dbAnyArray::arrayAllocator((dbAnyArray*)dst, src, size);
		continue;
	    }
	}
	return cli_unsupported_type;
    }
    return cli_ok;
}



int cli_insert(int statement, cli_oid_t* oid)
{
    return dbCLI::instance.insert(statement, oid);
}

int dbCLI::insert(int statement, cli_oid_t* oid)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	sql_scanner scanner(stmt->sql);
	if (scanner.get() != tkn_insert
	    || scanner.get() != tkn_into
	    || scanner.get() != tkn_ident)
	{
	    return cli_bad_statement;
	}
	int rc = match_columns(scanner.identifier(), stmt);
	if (rc != cli_ok) {
	    return rc;
	}
	stmt->prepared = true;
    }
    dbSmallBuffer buf(stmt->table->appSize);    
    char* obj = buf.base();
    memset(obj, 0, stmt->table->appSize);  
    dbFieldDescriptor *first = stmt->table->columns, *fd = first;
    do { 
	if (fd->appType == dbField::tpString) { 
	    *(char**)(obj + fd->appOffs) = "";
	}
    } while ((fd = fd->next) != first);
    
    int rc = store_columns(buf.base(), stmt);
    if (rc != cli_ok) { 
	return rc;
    }

    dbAnyReference ref;
    stmt->session->db->insertRecord(stmt->table, &ref, buf.base());
    stmt->oid = ref.getOid();
    if (oid != NULL) { 
	*oid = ref.getOid();
    }
    if (stmt->n_autoincremented_columns > 0) { 
	for (column_binding* cb = stmt->columns; cb != NULL; cb = cb->next) {
	    if (cb->var_type == cli_autoincrement) { 
		*(cli_int4_t*)cb->var_ptr = ref.getOid();
	    }
	}
    }
    return cli_ok;
}

int cli_update(int statement)
{
    return dbCLI::instance.update(statement);
}

int dbCLI::update(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	return cli_not_fetched;
    }
    if (!stmt->for_update) {
	return cli_not_update_mode;
    }
    if (stmt->updated) { 
	return cli_already_updated;
    }
    if (stmt->cursor.isEmpty()) { 
	return cli_not_found;
    }
    dbSmallBuffer buf(stmt->table->appSize); 
    char* record = buf.base();
    memset(record, 0, stmt->table->appSize);
    stmt->cursor.setRecord((byte*)record);
    stmt->cursor.fetch();
    
    int rc = store_columns(buf.base(), stmt);
    if (rc != cli_ok) { 
	return rc;
    }
    stmt->cursor.update();
    stmt->updated = true;
    return cli_ok;
}

int cli_get_first(int statement)
{
    return dbCLI::instance.get_first(statement);
}

int dbCLI::get_first(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	return cli_not_fetched;
    }
    if (!stmt->cursor.gotoFirst()) { 
	return cli_not_found;
    }
    return fetch_columns(stmt);
}

int cli_get_last(int statement)
{
    return dbCLI::instance.get_last(statement);
}

int dbCLI::get_last(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	return cli_not_fetched;
    }
    if (!stmt->cursor.gotoLast()) { 
	return cli_not_found;
    }
    return fetch_columns(stmt);
}

int cli_get_next(int statement)
{
    return dbCLI::instance.get_next(statement);
}

int dbCLI::get_next(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	return cli_not_fetched;
    }
    if (!((stmt->first_fetch && stmt->cursor.gotoFirst()) ||
	  (!stmt->first_fetch && stmt->cursor.gotoNext())))
    {
	return cli_not_found;
    }
    return fetch_columns(stmt);
}

int cli_get_prev(int statement)
{
    return dbCLI::instance.get_prev(statement);
}

int dbCLI::get_prev(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    if (!stmt->prepared) { 
	return cli_not_fetched;
    }
    if (!((stmt->first_fetch && stmt->cursor.gotoLast()) ||
	  (!stmt->first_fetch && stmt->cursor.gotoPrev())))
    {
	return cli_not_found;
    }
    return fetch_columns(stmt);
}

cli_oid_t cli_get_oid(int statement)
{
    return dbCLI::instance.get_inserted_oid(statement);
}

int dbCLI::get_inserted_oid(int statement)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) {
	return 0;
    }
    return s->oid;
}


int cli_free(int statement)
{
    return dbCLI::instance.free_statement(statement);
}

int dbCLI::free_statement(int statement)
{
    statement_desc* stmt = statements.get(statement);
    if (stmt == NULL) {
	return cli_bad_descriptor;
    }
    return free_statement(stmt);
}

int dbCLI::free_statement(statement_desc* stmt)
{
    statement_desc *sp, **spp = &stmt->session->stmts;
    while ((sp = *spp) != stmt) {
	if (sp == NULL) {
	    return cli_bad_descriptor;
	}
	spp = &sp->next;
    }
    *spp = stmt->next;
    delete[] stmt->sql;
    column_binding *cb, *next_cb;
    for (cb = stmt->columns; cb != NULL; cb = next_cb) {
	next_cb = cb->next;
	delete[] cb->name;
	column_allocator.free(cb);
    }
    parameter_binding *pb, *next_pb;
    for (pb = stmt->params; pb != NULL; pb = next_pb) {
	next_pb = pb->next;
	delete[] pb->name;
	parameter_allocator.free(pb);
    }
    statements.free(stmt);
    return cli_ok;
}


int cli_commit(int session)
{
    return dbCLI::instance.commit(session);
}

int dbCLI::commit(int session)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    while (s->dropped_tables != NULL) {
	dbTableDescriptor* next = s->dropped_tables->nextDbTable;
	delete s->dropped_tables;
	s->dropped_tables = next;
    }
    s->db->commit();
    s->existed_tables = s->db->tables;
    return cli_ok;
}

int cli_precommit(int session)
{
    return dbCLI::instance.precommit(session);
}

int dbCLI::precommit(int session)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    s->db->precommit();
    return cli_ok;
}

int cli_abort(int session)
{
    return dbCLI::instance.abort(session);
}

int dbCLI::abort(int session)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) {
	return cli_bad_descriptor;
    }
    dbDatabase* db = s->db;
    while (s->dropped_tables != NULL) {
	dbTableDescriptor* next = s->dropped_tables->nextDbTable;
	db->linkTable(s->dropped_tables, s->dropped_tables->tableId);
	s->dropped_tables = next;
    }
    s->db->rollback();
    while (db->tables != s->existed_tables) { 
	dbTableDescriptor* table = db->tables;
	db->unlinkTable(table);
	delete table;
    }
    return cli_ok;
}


int cli_remove(int statement)
{
    return dbCLI::instance.remove(statement);
}

int dbCLI::remove(int statement)
{
    statement_desc* stmt = statements.get(statement);    
    if (stmt == NULL || !stmt->prepared) {
	return cli_bad_descriptor;
    }
    if (!stmt->for_update) {
	return cli_not_update_mode;
    }
    if (stmt->cursor.isEmpty()) { 
	return cli_not_found;
    }
    stmt->cursor.removeAllSelected();
    return cli_ok;
}

int cli_describe(int session, char const* table, cli_field_descriptor** fields)
{
    return dbCLI::instance.describe(session, table, fields);
}

int dbCLI::describe(int session, char const* table, cli_field_descriptor** fields)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	
    dbDatabase* db = s->db;
    dbTableDescriptor* desc = db->findTableByName(table);
    if (desc == NULL) {
	return cli_table_not_found;
    } else { 
	int nColumns = desc->nColumns;
	cli_field_descriptor* fp = 
	    (cli_field_descriptor*)malloc(nColumns*sizeof(cli_field_descriptor));
	dbFieldDescriptor* fd = desc->columns; 
	*fields = fp;
	for (int i = 0; i < nColumns; i++, fp++) { 
	    fp->type = (cli_var_type)map_type(fd);
	    fp->name = fd->name;	    
	    fp->refTableName = fd->refTableName;
	    fp->inverseRefFieldName = fd->inverseRefName;
	    fp->flags = 0;
	    if (fd->tTree != 0) { 
		fp->flags |= cli_indexed;
	    }
	    if (fd->hashTable != 0) { 
		fp->flags |= cli_hashed;
	    }
	    fd = fd->next;
	}
	return nColumns;
    }
}


int cli_show_tables(int session, cli_table_descriptor** tables)
{
    return dbCLI::instance.show_tables(session, tables);
}

int dbCLI::show_tables(int session, cli_table_descriptor** tables)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	
    dbTableDescriptor* desc;
    int nTables = 0;
    for (desc = s->db->tables; desc != NULL; desc = desc->nextDbTable) {
	if (strcmp(desc->name, "Metatable")) {
	    nTables += 1;
	}
    }    
    if (nTables != 0) { 
	cli_table_descriptor* td = (cli_table_descriptor*)malloc(nTables*sizeof(cli_table_descriptor));
	*tables = td;
	for (desc = s->db->tables; desc == NULL; desc = desc->nextDbTable) {
	    if (strcmp(desc->name, "Metatable")) {
		td->name = desc->name;
		td += 1;
	    }
	}
    } else { 
	*tables = NULL;
    }
    return nTables;
}


#define MAX_QUERY_INDETIFIER_LENGTH 256

int sql_scanner::get()
{
    char buf[MAX_QUERY_INDETIFIER_LENGTH];
    int i = 0, ch;

    do {
	ch = *p++;
	if (ch == '\0') {
	    return tkn_eof;
	}
    } while (ch > 0 && ch <= 32);

    if (ch == '*') {
	return tkn_all;
    } else if ((ch >= '0' && ch <= '9') || ch == '+' || ch == '-') {	
	int const_type = tkn_iconst;
	while (true) {
	    ch = *p++;
	    if (ch == '.' || ch == 'e' || ch == 'E') { 
		const_type = tkn_fconst;
	    } else if (!((ch >= '0' && ch <= '9') || ch == '+' || ch == '-')) { 
		break;
	    }
	}
	return const_type;
    } else if (isalnum(ch) || ch == '$' || ch == '_') {
	do {
	    buf[i++] = ch;
	    if (i == MAX_QUERY_INDETIFIER_LENGTH) {
		// Identifier too long
		return tkn_error;
	    }
	    ch = *p++;
	} while (ch != EOF && (isalnum(ch) || ch == '$' || ch == '_'));
	p -= 1;
	buf[i] = '\0';
	ident = buf;
	return dbSymbolTable::add(ident, tkn_ident);
    } else {
	// Invalid symbol
	return tkn_error;
    }
}


int cli_create_table(int session, char const* tableName, int nColumns, 
		     cli_field_descriptor* columns)
{
    return dbCLI::instance.create_table(session, tableName, nColumns, columns);
}


int dbCLI::create_table(int session, char const* tableName, int nColumns, 
			cli_field_descriptor* columns)
{
    int i;
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	    
    dbDatabase* db = s->db;
    db->modified = true;
    if (db->findTableByName(tableName) != NULL) {
	return cli_table_already_exists;
    }
    int nFields = nColumns;
    int varyingLength = strlen(tableName) + 1;
    for (i = 0; i < nColumns; i++) { 
	int type = columns[i].type;
	varyingLength += strlen(columns[i].name) + 3;
	if (type == cli_oid || type == cli_array_of_oid) { 
	    varyingLength += strlen(columns[i].refTableName);
	    if (columns[i].inverseRefFieldName != NULL) { 
		varyingLength += strlen(columns[i].inverseRefFieldName);
	    }
	}
	switch (type) {        
	  case cli_oid:
	  case cli_bool:
	  case cli_int1:
	  case cli_int2:
	  case cli_int4:
	  case cli_autoincrement:
	  case cli_int8:
	  case cli_real4:
	  case cli_real8:
	  case cli_asciiz:
	  case cli_pasciiz:
	    break;
	  case cli_array_of_oid:
	  case cli_array_of_bool:
	  case cli_array_of_int1:
	  case cli_array_of_int2:
	  case cli_array_of_int4:
	  case cli_array_of_int8:
	  case cli_array_of_real4:
	  case cli_array_of_real8:
	  case cli_array_of_string:
	    varyingLength += strlen(columns[i].name) + 2 + 3;
	    nFields += 1;
	    break;
	  case cli_unknown:
	    return cli_unsupported_type;
	}
    }
    db->beginTransaction(true);
    oid_t oid = db->allocateRow(dbMetaTableId, 
				sizeof(dbTable) + sizeof(dbField)*nFields + varyingLength);
    dbTable* table = (dbTable*)db->putRow(oid);
    int offs = sizeof(dbTable) + sizeof(dbField)*nFields;
    table->name.offs = offs;
    table->name.size = strlen(tableName)+1;
    strcpy((char*)table + offs, tableName);
    offs += table->name.size;
    size_t size = sizeof(dbRecord);
    table->fields.offs = sizeof(dbTable);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    offs -= sizeof(dbTable);

    for (i = 0; i < nColumns; i++, field += 1, offs -= sizeof(dbField)) {
	field->name.offs = offs;
	field->name.size = strlen(columns[i].name) + 1;
	strcpy((char*)field + offs, columns[i].name);
	offs += field->name.size;	
	field->tableName.offs = offs;
	int type = columns[i].type;
	
	if (type == cli_oid || type == cli_array_of_oid) {
	    field->tableName.size = strlen(columns[i].refTableName) + 1;
	    strcpy((char*)field + offs, columns[i].refTableName);
	    offs += field->tableName.size;
	    field->inverse.offs = offs;
	    if (columns[i].inverseRefFieldName != NULL) { 
		field->inverse.size = strlen(columns[i].inverseRefFieldName) + 1;
		strcpy((char*)field + offs, columns[i].inverseRefFieldName);
		offs += field->inverse.size;
	    } else { 
		field->inverse.size = 1;
		*((char*)field + offs) = '\0';
		offs += 1;
	    }
	} else { 
	    field->tableName.size = 1;
	    *((char*)field + offs) = '\0';
	    offs += 1;
	}
	field->tTree = field->hashTable = 0;
 
	switch (type) {        
	  case cli_oid:
	    field->type = dbField::tpReference;
	    field->size = sizeof(oid_t);
	    break;
	  case cli_bool:
	    field->type = dbField::tpBool;
	    field->size = sizeof(bool);
	    break;
	  case cli_int1:
	    field->type = dbField::tpInt1;
	    field->size = sizeof(int1);
	    break;
	  case cli_int2:
	    field->type = dbField::tpInt2;
	    field->size = sizeof(int2);
	    break;
	  case cli_int4:
	  case cli_autoincrement:
	    field->type = dbField::tpInt4;
	    field->size = sizeof(int4);
	    break;
	  case cli_int8:
	    field->type = dbField::tpInt8;
	    field->size = sizeof(db_int8);
	    break;
	  case cli_real4:
	    field->type = dbField::tpReal4;
	    field->size = sizeof(real4);
	    break;
	  case cli_real8:
	    field->type = dbField::tpReal8;
	    field->size = sizeof(real8);
	    break;
	  case cli_asciiz:
	  case cli_pasciiz:
	    field->type = dbField::tpString;
	    field->size = sizeof(dbVarying);
	    field->offset = DOALIGN(size, sizeof(int4));
	    size = field->offset + sizeof(dbVarying);
	    if (columns[i].flags & cli_hashed) {
		field->hashTable = dbHashTable::allocate(db); 
	    }
	    if (columns[i].flags & cli_indexed) {
		field->tTree = dbTtree::allocate(db); 
	    }
	    continue;
	  case cli_array_of_oid:
	  case cli_array_of_bool:
	  case cli_array_of_int1:
	  case cli_array_of_int2:
	  case cli_array_of_int4:
	  case cli_array_of_int8:
	  case cli_array_of_real4:
	  case cli_array_of_real8:
	  case cli_array_of_string:
	    field->type = dbField::tpArray;
	    field->size = sizeof(dbVarying);
	    field->offset = DOALIGN(size, sizeof(int4));
	    size = field->offset + sizeof(dbVarying);
	    field += 1;
	    offs -= sizeof(dbField);
	    field->name.offs = offs;
	    field->name.size = strlen(columns[i].name) + 3;
	    sprintf((char*)field + offs, "%s[]", columns[i].name);
	    offs += field->name.size;	
	    field->tableName.offs = offs;
	    field->tableName.size = 1;
	    *((char*)field + offs) = '\0';
	    offs += 1;
	    field->inverse.offs = offs;
	    field->inverse.size = 1;
	    *((char*)field + offs) = '\0';
	    offs += 1;
	    field->offset = 0;
	    switch (type) { 
	      case cli_array_of_oid:
		field->type = dbField::tpReference;
		field->size = sizeof(oid_t);
		break;
	      case cli_array_of_bool:
		field->type = dbField::tpBool;
		field->size = sizeof(bool);
		break;
	      case cli_array_of_int1:
		field->type = dbField::tpInt1;
		field->size = sizeof(int1);
		break;
	      case cli_array_of_int2:
		field->type = dbField::tpInt2;
		field->size = sizeof(int2);
		break;
	      case cli_array_of_int4:
		field->type = dbField::tpInt4;
		field->size = sizeof(int4);
		break;
	      case cli_array_of_int8:
		field->type = dbField::tpInt8;
		field->size = sizeof(db_int8);
		break;
	      case cli_array_of_real4:
		field->type = dbField::tpReal4;
		field->size = sizeof(real4);
		break;
	      case cli_array_of_real8:
		field->type = dbField::tpReal8;
		field->size = sizeof(real8);
		break;
	      case cli_array_of_string:
		field->type = dbField::tpString;
		field->size = sizeof(dbVarying);
		break;
	    }
	    continue;
	} 
	if (columns[i].flags & cli_hashed) {
	    field->hashTable = dbHashTable::allocate(db); 
	}
	if (columns[i].flags & cli_indexed) {
	    field->tTree = dbTtree::allocate(db); 
	}
	field->offset = DOALIGN(size, field->size);
	size = field->offset + sizeof(dbVarying);
    }
    table->fields.size = nFields;
    table->fixedSize = size;
    table->nRows = 0;
    table->nColumns = nColumns;
    table->firstRow = 0;
    table->lastRow = 0;
    
    db->linkTable(new dbTableDescriptor(table), oid);
    if (!db->completeDescriptorsInitialization()) {
	return cli_table_not_found;
    }
    return cli_ok;
}


int cli_drop_table(int session, char const* tableName)
{
    return dbCLI::instance.drop_table(session, tableName);
}


int dbCLI::drop_table(int session, char const* tableName)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	    
    dbDatabase* db = s->db;
    dbTableDescriptor* desc = db->findTableByName(tableName);
    if (desc == NULL) {
	return cli_table_not_found;
    }
    db->dropTable(desc);
    if (desc == s->existed_tables) { 
	s->existed_tables = desc->nextDbTable;
    }
    db->unlinkTable(desc);
    desc->nextDbTable = s->dropped_tables;
    s->dropped_tables = desc;
    return cli_ok;
}

int cli_alter_index(int session, char const* tableName, char const* fieldName, int newFlags)
{
    return dbCLI::instance.alter_index(session, tableName, fieldName, newFlags);
}

int dbCLI::alter_index(int session, char const* tableName, char const* fieldName, int newFlags)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	    
    dbDatabase* db = s->db;
    dbTableDescriptor* desc = db->findTableByName(tableName);
    if (desc == NULL) {
	return cli_table_not_found;
    }
    dbFieldDescriptor* fd = desc->find(fieldName);
    if (fd == NULL) { 
	return cli_column_not_found;
    }
    if (fd->tTree != 0 && (newFlags & cli_indexed) == 0) { 
	db->dropIndex(fd);
    } 
    if (fd->hashTable != 0 && (newFlags & cli_hashed) == 0) { 
	db->dropHashTable(fd);
    } 
    if (fd->tTree == 0 && (newFlags & cli_indexed) != 0) {
	db->createIndex(fd);
    }
    if (fd->hashTable == 0 && (newFlags & cli_hashed) != 0) {
	db->createHashTable(fd);
    }
    return cli_ok;
}







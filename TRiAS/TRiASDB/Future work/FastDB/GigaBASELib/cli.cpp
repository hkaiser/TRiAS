//-< CLI.CPP >-------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     13-Jan-2000  K.A. Knizhnik  * / [] \ *
//                          Last update: 13-Jan-2000  K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Call level interface client part implementation
//-------------------------------------------------------------------*--------*

#include <ctype.h>
#include "stdtp.h"
#include "sockio.h"
#include "sync.h"
#include "cli.h"
#include "cliproto.h"

struct parameter_binding { 
    parameter_binding* next;
    char* name;
    int   var_type;
    int   var_len;
    void* var_ptr;

    ~parameter_binding() { 
	delete[] name;
    }
};

struct column_binding { 
    column_binding* next;
    char* name;
    int   var_type;
    int*  var_len;
    void* var_ptr;
    void* arr_ptr;
    int   arr_len;
    cli_column_get get_fnc;   
    cli_column_set set_fnc;   

    ~column_binding() { 
	delete[] name;
    }
};

struct session_desc;

struct statement_desc {
    int                id;
    statement_desc*    next;
    char*              stmt;
    column_binding*    columns;
    parameter_binding* params;
    session_desc*      session;
    bool               for_update;
    bool               prepared;   
    cli_oid_t          oid;
    int                stmt_len;
    int                n_params;
    int                n_columns;
    int                columns_len;

    void free() { 
	delete[] stmt;
	column_binding *cb, *next_cb;
	for (cb = columns; cb != NULL; cb = next_cb) { 
	    next_cb = cb->next;
	    delete cb;
	}
	parameter_binding *pb, *next_pb;
	for (pb = params; pb != NULL; pb = next_pb) { 
	    next_pb = pb->next;
	    delete pb;
	}
    }
    statement_desc(int id, statement_desc* next) { 
	this->id = id;
	this->next = next;
    }
};    

struct session_desc { 
    int             id;
    session_desc*   next;    
    socket_t*       sock;
    statement_desc* stmts;
    
    session_desc(int id, session_desc* next) { 
	this->id = id;
	this->next = next;
    }
};

template<class T>
class descriptor_table { 
  protected: 
    T**         table;
    T*          free_desc;
    int         descriptor_table_size;
    dbMutex     mutex;
    
  public:
    descriptor_table() { 
	int i;
	descriptor_table_size = 16;
	table = new T*[descriptor_table_size];
	T* next = NULL;
	for (i = 0; i < descriptor_table_size; i++) { 
	    table[i] = next = new T(i, next);
	}
	free_desc = next;
    }

    T* get(int desc) {
	dbCriticalSection cs(mutex);
	return (desc >= descriptor_table_size) ? (T*)0 : table[desc];
    }

    T* allocate() { 
	dbCriticalSection cs(mutex);
	if (free_desc == NULL) {
	    int i, n;
	    T** desc = new T*[descriptor_table_size * 2];
	    memcpy(desc, table, descriptor_table_size*sizeof(T*));
	    delete[] table;
	    table = desc;	    
	    T* next = NULL;
	    for (i = descriptor_table_size, n = i*2; i < n; i++) { 
		table[i] = next = new T(i, next);
	    }
	    free_desc = next;
	    descriptor_table_size = n;
	}
	T* desc = free_desc;
	free_desc = desc->next;
	return desc;
    }

    void free(T* desc) { 
	dbCriticalSection cs(mutex);
	desc->next = free_desc;
	free_desc = desc;
    }
};

static descriptor_table<session_desc>   sessions;
static descriptor_table<statement_desc> statements;

int cli_open(char const* server_url, 
	     int         max_connect_attempts,
	     int         reconnect_timeout_sec)
{
    socket_t* sock = socket_t::connect(server_url, 
				       socket_t::sock_any_domain,
				       max_connect_attempts,
				       reconnect_timeout_sec);
    if (!sock->is_ok()) { 
	delete sock;
	return cli_connection_refused;
    }
    session_desc* session = sessions.allocate();
    session->sock = sock;
    session->stmts = NULL;
    return session->id;
}


int cli_close(int session)
{
    statement_desc *stmt, *next;
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    cli_request req;
    req.length = sizeof(req);
    req.cmd = cli_cmd_close_session;
    req.pack();
    int result = cli_ok;
    if (!s->sock->write(&req, sizeof req)) { 
	result = cli_network_error;
    }
    for (stmt = s->stmts; stmt != NULL; stmt = next) {  
	next = stmt->next;
	stmt->free();
	statements.free(stmt);
    }
    sessions.free(s);
    return result;
}

int cli_statement(int session, char const* stmt_str)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    statement_desc* stmt = statements.allocate();
    stmt->stmt = new char[strlen(stmt_str)+1];
    stmt->columns = NULL;
    stmt->params = NULL;
    stmt->session = s;
    stmt->for_update = 0;
    stmt->prepared = false;
    stmt->n_params = 0;
    stmt->n_columns = 0;
    stmt->columns_len = 0;
    stmt->oid = 0;
    stmt->next = s->stmts;
    s->stmts = stmt;
    char const* p = stmt_str;
    char* dst = stmt->stmt;
    parameter_binding** last = &stmt->params;
    while (*p != '\0') { 
	if (*p == '\'') { 
	    do { 
		do { 
		    *dst++ = *p++;
		} while (*p != '\0' && *p != '\'');
		*dst++ = *p;
		if (*p == '\0') { 
		    *last = NULL;
		    stmt->free();
		    statements.free(stmt);
		    return cli_bad_statement;
		}
	    } while (*++p == '\'');
	} else if (*p == '%') { 
	    stmt->n_params += 1;
	    char const* q = p++;
	    while (isalnum((unsigned char)*p)) p += 1;
	    if (*p == '%') { 
		*last = NULL;
		stmt->free();
		statements.free(stmt);
		return cli_bad_statement;
	    }
	    parameter_binding* pb = new parameter_binding;
	    int len = p - q;
	    pb->name = new char[len+1];
	    memcpy(pb->name, q, len);
	    pb->name[len] = '\0';
	    *last = pb;
	    last = &pb->next;
	    pb->var_ptr = NULL;
	    *dst++ = '\0';
	} else { 
	    *dst++ = *p++;
	}
    }
    if (dst == stmt->stmt || *(dst-1) != '\0') { 
	*dst++ = '\0';
    }
    stmt->stmt_len = dst - stmt->stmt;
    *last = NULL;
    return stmt->id;
}

int cli_parameter(int         statement,
		  char const* param_name, 
		  int         var_type,
		  void*       var_ptr)
{
    if ((unsigned)var_type > cli_pasciiz) { 
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

int cli_column(int         statement,
	       char const* column_name, 
	       int         var_type, 
	       int*        var_len, 
	       void*       var_ptr)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    s->prepared = false;
    column_binding* cb = new column_binding;
    int len = strlen(column_name) + 1;
    cb->name = new char[len];
    s->columns_len += len;
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
		     char const*    column_name, 
		     int            var_type,
		     void*          var_ptr,
		     cli_column_set set,
		     cli_column_get get)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    if (var_type < cli_asciiz || var_type > cli_array_of_real8) { 
	return cli_unsupported_type;
    }
    s->prepared = false;
    column_binding* cb = new column_binding;
    int len = strlen(column_name) + 1;
    cb->name = new char[len];
    s->columns_len += len;
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
   
int cli_fetch(int statement, int for_update)
{
    parameter_binding* pb;
    column_binding*    cb;
    statement_desc* stmt = statements.get(statement);
    char *p, *s;

    if (stmt == NULL) { 
	return cli_bad_descriptor;
    }
    stmt->for_update = for_update;
    int msg_size = sizeof(cli_request) + 1;
    for (pb = stmt->params; pb != NULL; pb = pb->next) { 
	if (pb->var_ptr == NULL) { 
	    return cli_unbound_parameter;
	}
	if (pb->var_type == cli_asciiz) { 
	    msg_size += strlen((char*)pb->var_ptr) + 1;
	} else if (pb->var_type == cli_pasciiz) { 
	    msg_size += strlen(*(char**)pb->var_ptr) + 1;
	} else { 
	    msg_size += sizeof_type[pb->var_type];
	}
    }
    stmt->oid = 0;
    if (!stmt->prepared) { 
	msg_size += 4 + stmt->stmt_len + stmt->n_params;
	msg_size += stmt->columns_len + stmt->n_columns;
    }
    dbSmallBuffer buf(msg_size);
    p = buf;
    cli_request* req = (cli_request*)p;
    req->length  = msg_size;
    req->cmd     = stmt->prepared 
	? cli_cmd_execute : cli_cmd_prepare_and_execute;
    req->stmt_id = statement;
    req->pack();
    p += sizeof(cli_request);

    if (!stmt->prepared) { 
	*p++ = stmt->n_params;
	*p++ = stmt->n_columns;
	p = pack2(p, stmt->stmt_len + stmt->n_params);
	pb = stmt->params;
	char* end = p + stmt->stmt_len + stmt->n_params;
	char* src = stmt->stmt;
	while (p < end) { 
	    while ((*p++ = *src++) != '\0');
	    if (pb != NULL) { 
		*p++ = pb->var_type == cli_pasciiz ? cli_asciiz : pb->var_type;
		pb = pb->next;
	    }
	}
	for (cb = stmt->columns; cb != NULL; cb = cb->next) { 
	    *p++ = cb->var_type;
	    s = cb->name;
	    while ((*p++ = *s++) != '\0');
	}
    }	
    *p++ = for_update;
    for (pb = stmt->params; pb != NULL; pb = pb->next) { 
	switch (pb->var_type) { 
	  case cli_asciiz:
	    s = (char*)pb->var_ptr;
	    while ((*p++ = *s++) != '\0');
	    continue;
	  case cli_pasciiz:
	    s = *(char**)pb->var_ptr;
	    while ((*p++ = *s++) != '\0');
	    continue;
	  default:
	    switch (sizeof_type[pb->var_type]) { 
	      case 1:
		*p++ = *(char*)pb->var_ptr;
		continue;
	      case 2:
		p = pack2(p, *(int2*)pb->var_ptr);
		continue;
	      case 4:
		p = pack4(p, *(int4*)pb->var_ptr);
		continue;
	      case 8:
		p = pack8(p, *(int8*)pb->var_ptr);
		continue;
	    }
	}
    }
    assert(msg_size == p - buf);
    if (!stmt->session->sock->write(buf, msg_size)) { 
	return cli_network_error;
    }
    int4 response;
    if (!stmt->session->sock->read(&response, sizeof response)) { 
	return cli_network_error;
    }
    unpack4(response);
    if (response >= 0) { 
	stmt->prepared = true;
    }
    return response;
}

static int cli_send_columns(int statement, int cmd)
{
    statement_desc* s = statements.get(statement);
    column_binding* cb;
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    long msg_size = sizeof(cli_request);
    if (cmd == cli_cmd_update) { 
	if (!s->prepared) { 
	    return cli_not_fetched;
	}
	if (s->oid == 0) { 
	    return cli_not_found;
	}
	if (!s->for_update) { 
	    return cli_not_update_mode;
	}
    } else { 
	if (!s->prepared) { 
	    cmd = cli_cmd_prepare_and_insert;
	    msg_size += 1 + s->stmt_len + s->n_columns + s->columns_len;
	}
    }
    for (cb = s->columns; cb != NULL; cb = cb->next) { 
	if (cb->get_fnc != NULL) { 
	    cb->arr_ptr = cb->get_fnc(cb->var_type, cb->var_ptr, &cb->arr_len);
	    int len = cb->arr_len;
	    if (cb->var_type >= cli_array_of_oid) { 
		len *= sizeof_type[cb->var_type - cli_array_of_oid];
	    }
	    msg_size += 4 + len;
	} else { 
	    if (cb->var_type == cli_asciiz) { 
		msg_size += 4 + strlen((char*)cb->var_ptr) + 1;
	    } else if (cb->var_type == cli_pasciiz) { 
		msg_size += 4 + strlen(*(char**)cb->var_ptr) + 1;
	    } else if (cb->var_type >= cli_array_of_oid) { 
		msg_size += 4 + 
		    *cb->var_len * sizeof_type[cb->var_type-cli_array_of_oid];
	    } else { 
		msg_size += sizeof_type[cb->var_type];
	    }
	}
    }
    dbSmallBuffer buf(msg_size);
    char* p = buf;
    cli_request* req = (cli_request*)p;
    req->length  = msg_size;
    req->cmd     = cmd;
    req->stmt_id = statement;
    req->pack();
    p += sizeof(cli_request);
    if (cmd == cli_cmd_prepare_and_insert) { 
	char* cmd = s->stmt;
	while ((*p++ = *cmd++) != '\0');
	*p++ = s->n_columns;
	for (cb = s->columns; cb != NULL; cb = cb->next) { 
	    char* src = cb->name;
	    *p++ = cb->var_type;
	    while ((*p++ = *src++) != '\0');
	}	
    }
    for (cb = s->columns; cb != NULL; cb = cb->next) { 
	int n;
	char* src;
	if (cb->get_fnc != NULL) { 
	    src = (char*)cb->arr_ptr;
	    n = cb->arr_len;
	} else { 
	    src = (char*)cb->var_ptr;
	    if (cb->var_type >= cli_array_of_oid) { 
		n = *cb->var_len;	
	    }
	}
	if (cb->var_type >= cli_array_of_oid) { 
	    p = pack4(p, n);
	    switch (sizeof_type[cb->var_type-cli_array_of_oid]) { 
	      case 2:
		while (--n >= 0) { 
		    p = pack2(p, src);
		    src += 2;
		}
		break;
	      case 4:
		while (--n >= 0) { 
		    p = pack4(p, src);
		    src += 4;
		}
		break;
	      case 8:
		while (--n >= 0) { 
		    p = pack8(p, src);
		    src += 8;
		}
		break;
	      default:
		memcpy(p, src, n);
		p += n;
	    }
	} else if (cb->var_type == cli_asciiz) { 		
	    p = pack4(p, strlen(src)+1);
	    while ((*p++ = *src++) != 0);
	} else if (cb->var_type == cli_pasciiz) { 
	    src = *(char**)src;
	    p = pack4(p, strlen(src)+1);
	    while ((*p++ = *src++) != 0);
	} else { 
	    switch (sizeof_type[cb->var_type]) { 
	      case 2:
		p = pack2(p, src);
		break;
	      case 4:
		p = pack4(p, src);
		break;
	      case 8:
		p = pack8(p, src);
		break;
	      default:
		*p++ = *src;
	    }
	}
    }
    assert(p - buf == msg_size);
    if (!s->session->sock->write(buf, msg_size)) { 
	return cli_network_error;
    }
    return cli_ok;
}

int cli_insert(int statement, cli_oid_t* oid)
{
    int rc = cli_send_columns(statement, cli_cmd_insert);
    if (rc == cli_ok) { 
	char buf[sizeof(cli_oid_t) + 4];
	statement_desc* s = statements.get(statement);
	if (!s->session->sock->read(buf, sizeof buf)) { 
	    rc = cli_network_error;
	} else { 
	    rc = unpack4(buf);
	    s->prepared = true;
	    s->oid = unpack_oid(buf + 4);
	    if (oid != NULL) { 
		*oid = s->oid;
	    }
	}
    }
    return rc;
}

int cli_update(int statement)
{
    int rc = cli_send_columns(statement, cli_cmd_update);
    if (rc == cli_ok) { 
	int4 response;
	statement_desc* s = statements.get(statement);
	if (!s->session->sock->read(&response, sizeof response)) { 
	    rc = cli_network_error;
	} else { 
	    unpack4(response);
	    rc = response;
	}
    }
    return rc;      
}

static int cli_get(int statement, int cmd)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    if (!s->prepared) { 
	return cli_not_fetched;
    }
    cli_request req;
    req.length  = sizeof(cli_request);
    req.cmd     = cmd;
    req.stmt_id = statement;
    req.pack();
    if (!s->session->sock->write(&req, sizeof req)) { 
	return cli_network_error;
    }   
    int4 response;
    if (!s->session->sock->read(&response, sizeof response)) { 
	return cli_network_error;
    }
    unpack4(response);
    if (response <= 0) { 
	return response;
    }
    dbSmallBuffer buf(response-4);
    if (!s->session->sock->read(buf, response-4)) { 
	return cli_network_error;
    }
    char* p = buf;
    s->oid = unpack_oid(p);
    if (s->oid == 0) { 
	return cli_not_found;
    }
    p += sizeof(cli_oid_t);
    for (column_binding* cb = s->columns; cb != NULL; cb = cb->next) { 
	if (cb->set_fnc != NULL) { 
	    int len = unpack4(p);
	    p += 4;
	    char* dst = (char*)cb->set_fnc(cb->var_type, cb->var_ptr, len);
	    if (cb->var_type >= cli_array_of_oid) { 
		switch (sizeof_type[cb->var_type-cli_array_of_oid]) { 
		  case 2:		    
		    while (--len >= 0) { 
			p = unpack2(dst, p);
			dst += 2;
		    }
		    break;
		  case 4:
		    while (--len >= 0) { 
			p = unpack4(dst, p);
			dst += 4;
		    }
		    break;
		  case 8:
		    while (--len >= 0) { 
			p = unpack8(dst, p);
			dst += 8;
		    }
		    break;
		  default:
		    memcpy(dst, p, len);
		    p += len;
		}
	    } else { 
		memcpy(dst, p, len);
		p += len;
	    }
	} else { 
	    if (cb->var_type >= cli_asciiz) { 
		int len = unpack4(p);
		p += 4;
		char* dst = (char*)cb->var_ptr;
		char* src = p;
		int n = len;
		if (cb->var_len != NULL) { 
		    if (n > *cb->var_len) { 
			n = *cb->var_len;
		    }
		    *cb->var_len = n;
		}
		if (cb->var_type >= cli_array_of_oid) { 
		    switch (sizeof_type[cb->var_type-cli_array_of_oid]) { 
		      case 2:		    
			while (--n >= 0) { 
			    src = unpack2(dst, src);
			    dst += 2;
			}
			p += len*2;
			break;
		      case 4:
			while (--n >= 0) { 
			    src = unpack4(dst, src);
			    dst += 4;
			}
			p += len*4;
			break;
		      case 8:
			while (--n >= 0) { 
			    src = unpack8(dst, src);
			    dst += 8;
			}
			p += len*8;
			break;
		      default:
			memcpy(dst, p, n);
			p += len;
		    }
		} else { 
		    if (cb->var_type == cli_pasciiz) { 
			dst = *(char**)dst;
		    }
		    memcpy(dst, p, n);
		    p += len;
		}
	    } else { 
		switch (sizeof_type[cb->var_type]) { 
		  case 2:
		    p = unpack2((char*)cb->var_ptr, p);
		    break;
		  case 4:
		    p = unpack4((char*)cb->var_ptr, p);
		    break;
		  case 8:
		    p = unpack8((char*)cb->var_ptr, p);
		    break;
		  default:
		    *(char*)cb->var_ptr = *p++;
		}
	    }
	}
    }
    return cli_ok;
}

int cli_get_first(int statement)
{
    return cli_get(statement, cli_cmd_get_first);
}

int cli_get_last(int statement)
{
    return cli_get(statement, cli_cmd_get_last);
}

int cli_get_next(int statement)
{
    return cli_get(statement, cli_cmd_get_next);
}

int cli_get_prev(int statement)
{
    return cli_get(statement, cli_cmd_get_prev);
}

cli_oid_t cli_get_oid(int statement)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) { 
	return 0;
    }
    return s->oid;
}


static int cli_send_command(int session, int statement, int cmd)
{
    session_desc* s = sessions.get(session);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	
    cli_request req;
    req.length  = sizeof(cli_request);
    req.cmd     = cmd;
    req.stmt_id = statement;
    req.pack();
    if (!s->sock->write(&req, sizeof req)) { 
	return cli_network_error;
    }
    int4 response;
    if (!s->sock->read(&response, sizeof response)) { 
	return cli_network_error;
    }
    unpack4(response);
    return response;
}

int cli_free(int statement)
{
    statement_desc* stmt = statements.get(statement);
    session_desc* s = stmt->session;
    if (s == NULL) { 
	return cli_bad_descriptor;
    }	
    statement_desc *sp, **spp = &s->stmts; 
    while ((sp = *spp) != stmt) { 
	if (sp == NULL) { 
	    return cli_bad_descriptor;
	}
	spp = &sp->next;
    }
    *spp = stmt->next;
    stmt->free();
    statements.free(stmt);
    cli_request req;
    req.length  = sizeof(cli_request);
    req.cmd     = cli_cmd_free_statement;
    req.stmt_id = statement;
    req.pack();
    if (!s->sock->write(&req, sizeof req)) { 
	return cli_network_error;
    }
    return cli_ok;
}
    

int cli_commit(int session)
{
    return cli_send_command(session, 0, cli_cmd_commit);
}

int cli_abort(int session)
{
    return cli_send_command(session, 0, cli_cmd_abort);
}

int cli_remove(int statement)
{
    statement_desc* s = statements.get(statement);
    if (s == NULL) { 
	return cli_bad_descriptor;
    }
    if (s->oid == 0) { 
	return cli_not_found;
    }
    if (!s->for_update) { 
	return cli_not_update_mode;
    }
    return cli_send_command(s->session->id, s->id, cli_cmd_remove);
}





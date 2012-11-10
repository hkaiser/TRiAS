//-< SUBSQL.CPP >----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Interactive data manipulation language (subset of SQL)
//-------------------------------------------------------------------*--------*

#include <stdio.h>
#include <ctype.h>
#include "gigabase.h"
#include "compiler.h"
#include "subsql.h"
#include "symtab.h"
#include "hashtab.h"
#include "btree.h"
#include "server.h"

char* dbSubSql::prompt = ">> ";
const int initBufSize = 4096;

dbSubSql::dbSubSql()
{
    static struct { 
	char* name;
	int   tag;
    } keywords[] = { 
	{"array",   tkn_array},
	{"backup",  tkn_backup},	
	{"bool",    tkn_bool},
	{"commit",  tkn_commit},
	{"create",  tkn_create},
	{"delete",  tkn_delete},
	{"drop",    tkn_drop},
	{"exit",    tkn_exit},
	{"hash",    tkn_hash},
	{"help",    tkn_help},
	{"index",   tkn_index},
	{"insert",  tkn_insert},
	{"int1",    tkn_int1},
	{"int2",    tkn_int2},
	{"int4",    tkn_int4},
	{"int8",    tkn_int8},
	{"into",    tkn_into},
	{"of",      tkn_of},
	{"on",      tkn_on},
	{"open",    tkn_open},
	{"reference",tkn_reference},
	{"real4",   tkn_real4},
	{"real8",   tkn_real8},
	{"restore", tkn_restore},
	{"rollback",tkn_rollback},
	{"select",  tkn_select},
	{"server",  tkn_server},
	{"stop",    tkn_stop},
	{"show",    tkn_show},
	{"to",      tkn_to},
	{"table",   tkn_table},
	{"values",  tkn_values}
    };
    for (unsigned i = 0; i < items(keywords); i++) { 
	dbSymbolTable::add(keywords[i].name, keywords[i].tag, false);    
    }
    buflen = initBufSize;
    buf = new char[buflen];
    droppedTables = NULL;
    opened = false;
}

dbSubSql::~dbSubSql() { delete[] buf; }


inline int dbSubSql::get() 
{
    int ch = getc(in);
    if (ch == '\n') { 
	pos = 0;
	line += 1;
    } else if (ch == '\t') {
	pos = DOALIGN(pos + 1, 8);
    } else {  
	pos += 1;
    }
    return ch;
}

inline void dbSubSql::unget(int ch) { 
    if (ch != EOF) { 
	if (ch != '\n') { 
	    pos -= 1;
	} else { 
	    line -= 1;
	}
	ungetc(ch, in); 
    }
}

void dbSubSql::error(char const* msg)
{
#ifdef THROW_EXCEPTION_ON_ERROR
    try { 
	handleError(QueryError, msg, tknPos > 0 ? tknPos - 1 : 0);
    } catch(dbException) {}
#else
    dbDatabaseThreadContext* ctx = threadContext.get();
    ctx->interactive = true;
    if (setjmp(ctx->unwind) == 0) { 
	handleError(QueryError, msg, tknPos > 0 ? tknPos - 1 : 0);
    }
#endif
}


int dbSubSql::scan() 
{
    int i, ch, digits;
    
  nextToken:
    do { 
	if ((ch = get()) == EOF) { 
	    return tkn_eof;
	}
    } while (isspace(ch));
    
    tknPos = pos;
    switch (ch) { 
      case '*':
	return tkn_all;
      case '(':
	return tkn_lpar;
      case ')':
	return tkn_rpar;
      case ',':
	return tkn_comma;
      case '.':
	return tkn_dot;
      case ';':
	return tkn_semi;
      case '\'':
	i = 0; 
	while (true) { 
	    ch = get();
	    if (ch == '\'') { 
		if ((ch = get()) != '\'') { 
		    unget(ch);
		    break;
		}
	    } else if (ch == '\n' || ch == EOF) { 
		unget(ch);
		error("New line within character constant");
		return tkn_error;
	    }
	    if (i+1 == buflen) { 
		char* newbuf = new char[buflen*2];
		memcpy(newbuf, buf, buflen);
		delete[] buf;
		buf = newbuf;
		buflen *= 2;
	    }
	    buf[i++] = ch;
	}
	buf[i] = '\0';
	return tkn_sconst;
      case '-':
	if ((ch = get()) == '-') { 
	    // ANSI comments
	    while ((ch = get()) != EOF && ch != '\n');
	    goto nextToken;
	}
	unget(ch);
	ch = '-';
	// no break
      case '0': case '1': case '2': case '3': case '4': 
      case '5': case '6': case '7': case '8': case '9':
      case '+':
	i = 0;
	do { 
	    buf[i++] = ch;
	    if (i == buflen) { 
	        error("Numeric constant too long");
		return tkn_error;
	    }
	    ch = get();
	} while (ch != EOF 
		 && (isdigit(ch) || ch == '+' || ch == '-' || ch == 'e' || 
		     ch == 'E' || ch == '.'));
	unget(ch);
	buf[i] = '\0';
	if (sscanf(buf, INT8_FORMAT "%n", &ival, &digits) != 1) { 
	    error("Bad integer constant");
	    return tkn_error;
	}
	if (digits != i) { 
	    if (sscanf(buf, "%lf%n", &fval, &digits) != 1 || digits != i) {
		error("Bad float constant");
		return tkn_error;
	    }
	    return tkn_fconst;
	} 
	return tkn_iconst;

      default:
	if (isalpha(ch) || ch == '$' || ch == '_') { 
	    i = 0;
	    do { 
		buf[i++] = ch;
		if (i == buflen) { 
		    error("Identifier too long");
		    return tkn_error;
		}
		ch = get();
	    } while (ch != EOF && (isalnum(ch) || ch == '$' || ch == '_'));
	    unget(ch);
	    buf[i] = '\0';
	    name = buf;
	    return dbSymbolTable::add(name, tkn_ident);
	} else { 
	    error("Invalid symbol");
	    return tkn_error;
	}
    }
}


bool dbSubSql::expect(char* expected, int token)
{
    int tkn = scan();
    if (tkn != token) { 
	if (tkn != tkn_error) { 
	    char buf[256];
	    sprintf(buf, "Token '%s' expected", expected);
	    error(buf);
	}
	return false;
    }
    return true;
}
	    

bool dbSubSql::createTable()
{
    int tkn;
    if (!expect("table name", tkn_ident) || !expect("(", tkn_lpar)) { 
	return false;
    }
    char* name = this->name;
    int varyingLength = strlen(name)+1;

    static const struct { 
	int size;
	int alignment;
    } typeDesc[] = { 
	{ sizeof(bool), sizeof(bool) }, 
	{ sizeof(int1), sizeof(int1) }, 
	{ sizeof(int2), sizeof(int2) }, 
	{ sizeof(int4), sizeof(int4) }, 
	{ sizeof(int8), sizeof(int8) }, 
	{ sizeof(real4), sizeof(real4) }, 
	{ sizeof(real8), sizeof(real8) }, 
	{ sizeof(dbVarying), 4 }, 
	{ sizeof(oid_t), sizeof(oid_t) }, 
	{ sizeof(dbVarying), 4 }
    };

    const int maxFields = 256;
    tableField fields[maxFields];
    int nFields = 0;
    int nColumns = 0;
    tkn = tkn_comma;
    while (tkn == tkn_comma) { 
	if (nFields+1 == maxFields) { 
	    error("Too many fields");
	    break;
	}
	if (!expect("field name", tkn_ident)) { 
	    break;
	}
	int nameLen = strlen(buf)+1;
	fields[nFields].name = new char[nameLen];
	strcpy(fields[nFields].name, buf);
	varyingLength += nameLen + 2;
	int type = parseType();
	fields[nFields++].type = type;
	if (type == dbField::tpUnknown) { 
	    break;
	}
	nColumns += 1;
	if (type == dbField::tpArray) {
	    if (nFields+1 == maxFields) { 
		error("Too many fields");
		break;
	    }
	    fields[nFields].name = new char[nameLen+2];
	    sprintf(fields[nFields].name, "%s[]", fields[nFields-1].name);
	    varyingLength += nameLen+2+2;
	    type = parseType();
	    if (type == dbField::tpUnknown) { 
		break;
	    }
	    if (type == dbField::tpArray) { 
		error("Arrays of arrays are not supported by CLI");
		break;
	    }
	    fields[nFields++].type = type;
	} else if (type == dbField::tpReference) { 
	    int len =  strlen(buf);
	    fields[nFields-1].refTableName = new char[len + 1];
	    strcpy(fields[nFields-1].refTableName, buf);	    
	    varyingLength += len;
	}
	tkn = scan(); 
    }
    if (tkn == tkn_rpar) { 
	beginTransaction(true);
	modified = true;
	if (findTable(name) != NULL) { 
	    error("Table already exists");
	    return false;
	}
	oid_t oid = allocateRow(dbMetaTableId, 
				sizeof(dbTable) + sizeof(dbField)*nFields 
				+ varyingLength, metatable);
	dbPutTie tie;
	dbTable* table = (dbTable*)putRow(tie, oid);    
	int offs = sizeof(dbTable) + sizeof(dbField)*nFields;
	table->name.offs = offs;
	table->name.size = strlen(name)+1;
	strcpy((char*)table + offs, name);
	offs += table->name.size;
	size_t size = sizeof(dbRecord);
	table->fields.offs = sizeof(dbTable);
	dbField* field = (dbField*)((char*)table + table->fields.offs);
	offs -= sizeof(dbTable);
	bool arrayComponent = false;

	for (int i = 0; i < nFields; i++) { 
	    field->name.offs = offs;
	    field->name.size = strlen(fields[i].name) + 1;
	    strcpy((char*)field + offs, fields[i].name);
	    offs += field->name.size;
	    
	    field->tableName.offs = offs;
	    if (fields[i].refTableName) { 
		field->tableName.size = strlen(fields[i].refTableName);
		strcpy((char*)field + offs, fields[i].refTableName);
		offs += field->tableName.size;
	    } else { 
		field->tableName.size = 1;
		*((char*)field + offs++) = '\0';
	    }
	    
	    field->inverse.offs = offs;
	    field->inverse.size = 1;
	    *((char*)field + offs++) = '\0';
	    
	    field->type = fields[i].type;
	    field->size = typeDesc[fields[i].type].size;
	    if (!arrayComponent) { 
		size = DOALIGN(size, typeDesc[fields[i].type].alignment);
		field->offset = size;
		size += field->size;
	    } else { 
		field->offset = 0;
	    }
	    field->hashTable = 0;
	    field->bTree = 0;
	    arrayComponent = field->type == dbField::tpArray; 
	    field += 1;
	    offs -= sizeof(dbField);
	}
	table->fields.size = nFields;
	table->fixedSize = size;
	table->nRows = 0;
	table->nColumns = nColumns;
	table->firstRow = 0;
	table->lastRow = 0;

	linkTable(new dbTableDescriptor(table), oid);
	if (!completeDescriptorsInitialization()) { 
	    error("Reference to undefined table");
	}
    }
    return tkn == tkn_rpar;
}

int dbSubSql::parseType()
{
    switch (scan()) { 
      case tkn_bool:
	return dbField::tpBool;
      case tkn_int1:
	return dbField::tpInt1;
      case tkn_int2:
	return dbField::tpInt2;
      case tkn_int4:
	return dbField::tpInt4;
      case tkn_int8:
	return dbField::tpInt8;
      case tkn_real4:
	return dbField::tpReal4;
      case tkn_real8:
	return dbField::tpReal8;
      case tkn_array:
	return expect("of", tkn_of) ? dbField::tpArray : dbField::tpUnknown;
      case tkn_string:
	return dbField::tpString;
      case tkn_reference:
	return 
	    expect("to", tkn_to) && expect("referenced table name", tkn_ident) 
	    ? dbField::tpReference : dbField::tpUnknown;
      default:
	error("Field type expected");
    }
    return dbField::tpUnknown;
}


bool dbSubSql::readCondition()
{
    int i, ch;
    for (i = 0; (ch = get()) != ';' && ch !=  EOF; i++) { 
	if (i+1 == buflen) { 
	    char* newbuf = new char[buflen*2];
	    memcpy(newbuf, buf, buflen);
	    delete[] buf;
	    buf = newbuf;
	    buflen *= 2;
	}
	buf[i] = ch;
    }
    buf[i] = '\0';
    if (ch != ';') { 
	error("unexpected end of input");
	return false;
    } 
    return true;
}


void dbSubSql::dumpRecord(byte* base, dbFieldDescriptor* first)
{
    int i, n;
    byte* elem;
    dbFieldDescriptor* fd = first;
    do { 
	if (fd != first) { 
	    printf(", ");
	}
	switch (fd->type) { 
	  case dbField::tpBool:
	    printf("%s", *(bool*)(base + fd->dbsOffs) 
		   ? "true" : "false");
	    continue;
	  case dbField::tpInt1:
	    printf("%d", *(int1*)(base + fd->dbsOffs)); 
	    continue;	    
	  case dbField::tpInt2:
	    printf("%d", *(int2*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpInt4:
	    printf("%d", *(int4*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpInt8:
	    printf(INT8_FORMAT,	*(int8*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpReal4:
	    printf("%f", *(real4*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpReal8:
	    printf("%f", *(real8*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpString:
	    printf("'%s'", (char*)base+((dbVarying*)(base+fd->dbsOffs))->offs);
	    continue;
	  case dbField::tpReference:
	    printf("#%x", *(oid_t*)(base + fd->dbsOffs)); 
	    continue;
	  case dbField::tpRawBinary:
	    n = fd->dbsSize;
	    elem = base + fd->dbsOffs;
	    printf("(");
	    for (i = 0; i < n; i++) { 
		if (i != 0) { 
		    printf(", ");
		}
		printf("%02x", *elem++);
	    }
	    printf(")");
	    continue;
	  case dbField::tpArray:
	    n = ((dbVarying*)(base + fd->dbsOffs))->size;
	    elem = base + ((dbVarying*)(base + fd->dbsOffs))->offs;
	    printf("(");
	    for (i = 0; i < n; i++) { 
		if (i != 0) { 
		    printf(", ");
		}
		dumpRecord(elem, fd->components);
		elem += fd->components->dbsSize;
	    }
	    printf(")");
	    continue;
	  case dbField::tpStructure:
	    printf("(");
	    dumpRecord(base, fd->components);
	    printf(")");
	}
    } while ((fd = fd->next) != first);
}

int dbSubSql::calculateRecordSize(dbList* node, int offs, 
				  dbFieldDescriptor* first)
{
    dbFieldDescriptor* fd = first;
    do { 
	if (node == NULL) { 
	    return -1;
	}
	if (fd->type == dbField::tpArray) { 
	    if (node->type != dbList::nTuple) { 
		return -1;
	    }
	    int nElems = node->aggregate.nComponents;
	    offs = DOALIGN(offs, fd->components->alignment) 
		 + nElems*fd->components->dbsSize;
	    if (fd->attr & dbFieldDescriptor::HasArrayComponents) {
		dbList* component = node->aggregate.components;
		while (--nElems >= 0) { 
		    int d = calculateRecordSize(component,offs,fd->components);
		    if (d < 0) return d;
		    offs = d;
		    component = component->next;
		}
	    } 
	} else if (fd->type == dbField::tpString) { 
	    if (node->type != dbList::nString) { 
		return -1;
	    }
	    offs += strlen(node->sval) + 1;
	} else if (fd->type == dbField::tpRawBinary) { 
	    if (node->type != dbList::nTuple) { 
		return -1;
	    }
	    int nElems = node->aggregate.nComponents;
	    dbList* component = node->aggregate.components;
	    if (size_t(nElems) > fd->dbsSize) { 
		return -1;
	    }
	    while (--nElems >= 0) { 
		if (component->type != dbList::nInteger
		    || (component->ival & ~0xFF) != 0) 
		{ 
		    return -1;
		}
		component = component->next;
	    }
	} else { 
	    if (!((node->type == dbList::nBool && fd->type == dbField::tpBool)
		  || (node->type == dbList::nInteger 
		      && (fd->type == dbField::tpInt1
			  || fd->type == dbField::tpInt2
			  || fd->type == dbField::tpInt4
			  || fd->type == dbField::tpInt8
			  || fd->type == dbField::tpReference))
		  || (node->type == dbList::nReal 
		      && (fd->type == dbField::tpReal4
			  || fd->type == dbField::tpReal8))
		  || (node->type == dbList::nTuple 
		      && fd->type == dbField::tpStructure)))
	    {
		return -1;
	    }
	    if (fd->attr & dbFieldDescriptor::HasArrayComponents) {
		int d = calculateRecordSize(node->aggregate.components,
					    offs, fd->components);
		if (d < 0) return d;
		offs = d;
	    }
	}
	node = node->next;
    } while ((fd = fd->next) != first);
    return offs;    
}

int dbSubSql::initializeRecordFields(dbList* node, byte* dst, int offs, 
				     dbFieldDescriptor* first)
{
    dbFieldDescriptor* fd = first;
    dbList* component;
    byte* elem;
    int len, elemOffs, elemSize;

    do { 
	switch (fd->type) { 
	  case dbField::tpBool:
	    *(bool*)(dst+fd->dbsOffs) = node->bval;
	    break;
	  case dbField::tpInt1:
	    *(int1*)(dst+fd->dbsOffs) = (int1)node->ival;
	    break;
	  case dbField::tpInt2:
	    *(int2*)(dst+fd->dbsOffs) = (int2)node->ival;
	    break;
	  case dbField::tpInt4:
	    *(int4*)(dst+fd->dbsOffs) = (int4)node->ival;
	    break;
	  case dbField::tpInt8:
	    *(int8*)(dst+fd->dbsOffs) = node->ival;
	    break;
	  case dbField::tpReal4:
	    *(real4*)(dst+fd->dbsOffs) = (real4)node->fval;
	    break;
	  case dbField::tpReal8:
	    *(real8*)(dst+fd->dbsOffs) = node->fval;
	    break;
	  case dbField::tpReference:
	    *(oid_t*)(dst+fd->dbsOffs) = 0;
	    break;
	  case dbField::tpString:
	    ((dbVarying*)(dst+fd->dbsOffs))->offs = offs;
	    len = strlen(node->sval) + 1;
	    ((dbVarying*)(dst+fd->dbsOffs))->size = len;
	    memcpy(dst + offs, node->sval, len);
	    offs += len;
	    break;
	  case dbField::tpRawBinary:
	    len = node->aggregate.nComponents;
	    component = node->aggregate.components;
	    elem = dst + fd->dbsOffs;
	    while (--len >= 0) { 
		*elem++ = (byte)component->ival;
		component = component->next;
	    }
	    break;
	  case dbField::tpArray:
	    len = node->aggregate.nComponents;
	    elem = (byte*)DOALIGN(long(dst) + offs, fd->components->alignment);
	    offs = elem - dst;
	    ((dbVarying*)(dst+fd->dbsOffs))->offs = offs;
	    ((dbVarying*)(dst+fd->dbsOffs))->size = len;
	    elemSize = fd->components->dbsSize;  
	    elemOffs = len*elemSize;
	    offs += elemOffs;
	    component = node->aggregate.components;
	    while (--len >= 0) { 
		elemOffs = initializeRecordFields(component, elem, elemOffs, 
						  fd->components);
		elemOffs -= elemSize;
		elem += elemSize;
		component = component->next;
	    }
	    offs += elemOffs;
	    break;
	  case dbField::tpStructure:
	    offs = initializeRecordFields(node->aggregate.components, 
					  dst, offs, fd->components);
	}
	node = node->next;
    } while ((fd = fd->next) != first);

    return offs;
}


bool dbSubSql::insertRecord(dbList* list, dbTableDescriptor* desc)
{
    int size = calculateRecordSize(list, desc->fixedSize, desc->columns);
    if (size < 0) { 
	error("Incompatible types in insert statement");
	return false;
    }
    oid_t oid = allocateRow(desc->tableId, size, desc);
    dbPutTie tie;
    byte* dst = (byte*)putRow(tie, oid);    
    initializeRecordFields(list, dst, desc->fixedSize, desc->columns);

    int nRows = desc->nRows;
    dbFieldDescriptor* fd;
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField){
	dbHashTable::insert(this, fd->hashTable, oid, fd->type, fd->dbsOffs, 
			    nRows);
    }
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbBtree::insert(this, fd->bTree, oid, fd->dbsOffs);
    }    
    return true;
}

int dbSubSql::readValues(dbList** chain)
{
    int i, n = 0;
    int tkn;
    dbList* node;

    while (true) { 
	switch (scan()) { 
	  case tkn_lpar:
	    node = new dbList(dbList::nTuple);
	    node->aggregate.components = NULL;
	    i = readValues(&node->aggregate.components);
	    if (i < 0) { 
		return -1;
	    }
	    node->aggregate.nComponents = i;
	    break;
	  case tkn_rpar:
	    return -n; // valid only in case of empty list
	  case tkn_iconst:
	    node = new dbList(dbList::nInteger);
	    node->ival = ival;
	    break;
	  case tkn_true:
	    node = new dbList(dbList::nBool);
	    node->bval = true;
	    break;
	  case tkn_false:
	    node = new dbList(dbList::nBool);
	    node->bval = false;
	    break;	    
	  case tkn_fconst:
	    node = new dbList(dbList::nReal);
	    node->fval = fval;
	    break;
	  case tkn_sconst:
	    node = new dbList(dbList::nString);
	    node->sval = new char[strlen(buf)+1];
	    strcpy(node->sval, buf);
	    break;
	  case tkn_error:
	    return -1;
	  default:
	    error("Syntax error in insert list");
	    return -1;
	}
	*chain = node;
	chain = &node->next;
	n += 1;
	if ((tkn = scan()) == tkn_rpar) { 
	    return n;
	}
	if (tkn != tkn_comma) {   
	    error("',' expected");
	    return -1;
	}
    }
}


dbFieldDescriptor* dbSubSql::readFieldName()
{
    int tkn;

    if (expect("table name", tkn_ident)) { 
	dbTableDescriptor* desc;
	dbFieldDescriptor* fd;
	if ((desc = findTable(name)) == NULL) { 
	    error("No such table in database");
	    return NULL;
	}	
	if (expect(".", tkn_dot) && expect("field name", tkn_ident)) { 
	    if ((fd = desc->find(name)) == NULL) { 
		error("No such field in the table");
		return NULL;
	    } else if (fd->type == dbField::tpArray) { 	
		error("Array components can not be indexed");
		return NULL;
	    }
	} else { 
	    return NULL;
	}
	while ((tkn = scan()) != tkn_semi) { 
	    if (tkn != tkn_dot) { 
		error("'.' expected");
		return NULL;
	    }	
	    if (expect("field name", tkn_ident)) { 
		if ((fd = fd->find(name)) == NULL) { 
		    error("No such field in the table");
		    return NULL;
		} else if (fd->type == dbField::tpArray) { 	
		    error("Array components can not be indexed");
		    return NULL;
		}	
	    } else { 
		return NULL;
	    }
	}
	if (fd->type == dbField::tpReference) { 
	    error("References can not be indexed");
	    return NULL;
	} 	
	if (fd->type == dbField::tpStructure) { 
	    error("Structures can not be indexed");
	    return NULL;
	} 
	return fd;
    }
    return NULL;
}



bool dbSubSql::parse() 
{
    dbTableDescriptor* desc;
    dbFieldDescriptor* fd;
    int tkn;
    bool outputOid;

    line = 1;
    pos = 0;

    while (true) { 
	if (in == stdin) { 
	    printf(prompt);
	    tkn = scan();
	    pos += strlen(prompt);
	} else { 
	    tkn = scan();
	}	    

	switch (tkn) { 
	  case tkn_select:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    outputOid = true;
	    if ((tkn = scan()) == tkn_all) { 
		outputOid = false;
		tkn = scan();
	    } 
	    if (tkn != tkn_from) { 
		error("'from' keyword expected");
		continue;
	    }
	    if (scan() != tkn_ident) { 
		error("Table name expected");
		continue;
	    }
	    if ((desc = findTable(name)) != NULL) {     
		dbAnyCursor cursor(*desc, dbCursorViewOnly, NULL);
		query.pos = pos;
		dbDatabaseThreadContext* ctx = threadContext.get();
		ctx->interactive = true;
		if (setjmp(ctx->unwind) == 0) { 
		    if (readCondition()) { 
			query = buf;
			select(&cursor, query);
			if (!query.compiled()) { 
			    dbExprNode::cleanup();
			    continue;
			}		 
		    } else { 
			continue;
		    }
		    if (cursor.gotoFirst()) { 
			dbGetTie tie;
			dbFieldDescriptor* fd = desc->columns; 
			do { 
			    printf("%s ", fd->name);
			} while ((fd = fd->next) != desc->columns);
			if (outputOid) { 
			    printf("\n#%x: (", cursor.currId);
			} else { 
			    printf("\n(");
			}
			dumpRecord((byte*)getRow(tie, cursor.currId), 
				   cursor.table.columns);
			printf(")");
			while (cursor.gotoNext()) { 
			    if (outputOid) { 
				printf(",\n#%x: (", cursor.currId);
			    } else { 
				printf(",\n(");
			    }
			    dumpRecord((byte*)getRow(tie, cursor.currId),
				       cursor.table.columns);
			    printf(")");
			}
			printf("\n\t%d records selected\n", 
			       cursor.getNumberOfRecords());
		    } else { 
			fprintf(stderr, "No records selected\n");
		    }
		}
		if (!modified) { 
		    commit(); // release locks
		}
	    } else { 
		error("No such table in database");
	    }
	    continue;
		
	  case tkn_open:
	    if (expect("database file name", tkn_sconst)) { 
		if (opened) { 
		    close();
		    while (droppedTables != NULL) { 
			dbTableDescriptor* next = droppedTables->nextDbTable;
			droppedTables->drop(); 
			droppedTables = next;
		    }
		    opened = false;
		    dbTableDescriptor::cleanup();
		}
		if (!open(buf)) { 
		    fprintf(stderr, "Database not opened\n");
		} else { 
		    dbGetTie tie;
		    opened = true;
		    dbTable* table = (dbTable*)getRow(tie, dbMetaTableId);
		    metatable = new dbTableDescriptor(table);
		    linkTable(metatable, dbMetaTableId);
		    oid_t tableId = table->firstRow;
		    while (tableId != 0) {
			table = (dbTable*)getRow(tie, tableId);
			linkTable(new dbTableDescriptor(table), tableId);
			tableId = table->next;
		    }
		    if (!completeDescriptorsInitialization()) {
			error("Reference to undefined table");
		    }
		}
	    }
	    continue;
		    
	  case tkn_drop:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    switch (scan()) { 
	      case tkn_table:
		if (expect("table name", tkn_ident)) { 
		    desc = findTable(name);
		    if (desc == NULL) { 
			error("No such table in database");
		    } else { 
			dropTable(desc);
			unlinkTable(desc);
			desc->nextDbTable = droppedTables;
			droppedTables = desc;
		    }
		}
		continue;
	      case tkn_hash:
		fd = readFieldName();
		if (fd != NULL) { 
		    if (fd->hashTable == 0) { 
			error("This field is not hashed");
		    } else { 
			dropHashTable(fd);
		    }
		}
		continue;
	      case tkn_index:
		fd = readFieldName();
		if (fd != NULL) { 
		    if (fd->bTree == 0) { 
			error("There is no index for this field");
		    } else { 
			dropIndex(fd);
		    }
		}
		continue;
	      default:
		error("Expecting 'table', 'hash' or 'index' keyword");
	    }
	    continue;

	  case tkn_backup:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    if (expect("backup file name", tkn_sconst)) { 
		if (!backup(buf)) { 
		    printf("Backup failed\n");
		} else { 
		    while (droppedTables != NULL) { 
			dbTableDescriptor* next = droppedTables->nextDbTable;
			droppedTables->drop(); 
			droppedTables = next;
		    }
		    commit();
		}
	    }
	    continue;

	  case tkn_restore:
	    if (opened) { 
		error("Can not restore online database");
		continue;
	    }
	    if (expect("backup file name", tkn_sconst)) { 
		char bckName[initBufSize];
		strcpy(bckName, buf);
		if (expect("database file name", tkn_sconst)) { 
		    if (!restore(bckName, buf)) { 
			printf("Restore failed\n");
		    }
		} 
	    }
	    continue;
	    
	    
	  case tkn_create:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    switch (scan()) { 
	      case tkn_hash:
		if (!expect("on", tkn_on)) { 
		    continue;
		}
		fd = readFieldName();
		if (fd != NULL) { 
		    if (fd->hashTable != 0) { 
			error("This field is already hashed");
		    } else { 
			createHashTable(fd);
		    }
		}
		continue;
	      case tkn_index:
		if (!expect("on", tkn_on)) { 
		    continue;
		}
		fd = readFieldName();
		if (fd != NULL) { 
		    if (fd->bTree != 0) { 
			error("Index already exists");
		    } else { 
			createIndex(fd);
		    }
		}
		continue;

		      case tkn_table:
		createTable();
		continue;

	      default:
		error("Expecting 'table', 'hash' or 'index' keyword");
	    }
	    continue;

	  case tkn_insert:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    if (expect("into", tkn_into) && expect("table name", tkn_ident)) {
		if ((desc = findTable(name)) == NULL) { 
		    error("No such table in database");
		    continue;
		}
		if (!expect("values", tkn_values)) { 
		    continue;
		}
		beginTransaction(true);
		modified = true;
		while (expect("(", tkn_lpar)) { 
		    dbList* list = NULL;
		    int n = readValues(&list);
		    if (n <= 0 || !insertRecord(list, desc)) { 
			if (n == 0) { 
			    error("Empty fields list");
			}
			tkn = tkn_semi; // just avoid extra error messages
		    } else { 
			tkn = scan();
		    }
		    while (list != NULL) { 
			dbList* tail = list->next;
			delete list;
			list = tail;
		    }
		    if (tkn == tkn_semi) { 
			break;
		    } else if (tkn != tkn_comma) { 
			error("';' or ',' expected");
		    }
		}
	    }
	    continue;

	  case tkn_delete:
	    if (!opened) { 
		error("Database not opened");
		continue;
	    }
	    if (expect("from", tkn_from) && expect("table name", tkn_ident)) {
		if ((desc = findTable(name)) == NULL) { 
		    error("No such table in database");
		} else { 
		    deleteTable(desc);
		}
	    }
	    continue;

	  case tkn_commit:
	    if (!opened) { 
		error("Database not opened");
	    } else { 
		while (droppedTables != NULL) { 
		    dbTableDescriptor* next = droppedTables->nextDbTable;
		    droppedTables->drop(); 
		    droppedTables = next;
		}
		commit();
	    }
	    continue;

	  case tkn_rollback:
	    if (!opened) { 
		error("Database not opened");
	    } else { 
		while (droppedTables != NULL) { 
		    dbTableDescriptor* next = droppedTables->nextDbTable;
		    linkTable(droppedTables, droppedTables->tableId); 
		    droppedTables = next;
		}
		rollback();
	    } 
	    continue;

	  case tkn_show:
	    if (!opened) { 
		error("Database not opened");
	    } else { 
		printf("Database file size: " INT8_FORMAT " Kb\n"
		       "Object index size : " INT8_FORMAT " handles\n"
		       "Used part of index: " INT8_FORMAT " handles\n",
		       int8(header->root[1-header->curr].size / 1024),
		       int8(header->root[1-header->curr].indexSize), 
		       int8(header->root[1-header->curr].indexUsed));
	    } 
	    continue;
		       
	  case tkn_help:
	    fprintf(stderr, "SubSQL commands:\n\n\
open 'database-file-name' ';'\n\
select ('*') from <table-name> where <condition> ';'\n\
delete from <table-name>\n\
drop table <table-name>\n\
drop index <table-name> {'.' <field-name>} ';'\n\
create index on <table-name> {'.' <field-name>} ';'\n\
drop hash <table-name> {'.' <field-name>};\n\
create hash on <table-name> {'.' <field-name>}field> ';'\n\
insert into <table-name> values '(' <value>{',' <value>} ')' ';'\n\
backup 'backup-file-name'\n\
restore 'backup-file-name' 'database-file-name'\n\
start server URL number-of-threads\n\
stop server URL\n\
commit\n\
rollback\n\
show\n\
exit\n\
help\n\n");
	    continue;
	  case tkn_start:
	    commit(); // allow server therads to process
	    if (expect("server", tkn_server) 
		&& expect("server URL", tkn_sconst))
	    {
		dbServer* server = dbServer::find(buf);
		if (server == NULL) { 
		    char* serverURL = new char[strlen(buf)+1];
		    strcpy(serverURL, buf);
		    if (expect("number of threads", tkn_iconst)) { 
			server = new dbServer(this, serverURL, (int)ival);
			printf("Server started for URL %s\n", serverURL);
		    }
		    delete[] serverURL;
		}
		if (server != NULL) { 
		    server->start();
		}
	    }
	    continue;
	  case tkn_stop:
	    if (expect("server", tkn_server) 
		&& expect("server URL", tkn_sconst))
	    {
		dbServer* server = dbServer::find(buf);
		if (server != NULL) { 
		    server->stop();
		    printf("Server stopped for URL %s\n", buf);
		} else { 
		    fprintf(stderr, "No server was started for URL %s\n", buf);
		}
	    }
	    continue;
	  case tkn_semi:
	    putchar('\n');
	    // no break
	  case tkn_error:
	    continue;
	  case tkn_exit:
	    return false;
	  case tkn_eof:
	    return true;
	  default:
	    error("Unexpected token");
	}
    }
}

	    
void dbSubSql::handleError(dbErrorClass error, char const* msg, int arg)
{
#ifdef THROW_EXCEPTION_ON_ERROR
    throw dbException(error, msg, arg);
#else
    dbDatabaseThreadContext* ctx = threadContext.get();
    if (ctx->interactive) { 
	const int screenWidth = 80;
	int col;
	switch (error) { 
	  case QueryError:
	    col = arg % screenWidth;
	    if (in == stdin) { 
		while (--col >= 0) putc('-', stderr);
		fprintf(stderr, "^\n%s\n", msg);
	    } else { 
		fprintf(stderr, "%s at line %d position %d\n", msg, line, arg);
	    }
	    break;
	  case ArithmeticError:
	    fprintf(stderr, "%s\n", msg);
	    break;
	  case IndexOutOfRangeError:
	    fprintf(stderr, "Index %d is out of range\n", arg);
	    break;
	  case NullReferenceError:
	    fprintf(stderr, "Null object reference is accessed\n");
	    break;
	  default:
	    dbDatabase::handleError(error, msg, arg);
	}
	//
	// Recovery
	//
	if (in == stdin) { 
	    int ch;
	    while ((ch = get()) != '\n' && ch != EOF); 
	} else { 
	    fseek(in, 0, SEEK_END);
	}
    }
    longjmp(ctx->unwind, error);
#endif
}

void dbSubSql::run(int argc, char* argv[])
{
    for (int i = 1; i < argc; i++) { 
        in = fopen(argv[i], "r");
	if (in == NULL) { 
	    fprintf(stderr, "Failed to open '%s' file\n", argv[i]);
	} else { 
	    if (!parse()) { 
		if (opened) { 
		    close();
		}
		return;
	    }
	}
    }
    in = stdin;
    parse();
    if (opened) { 
	close();
    }
}

int main(int argc, char* argv[]) 
{
    printf("SubSQL interactive utility for GigaBASE\n"
	   "Type 'help' for more information\n");
    dbSubSql db;
    db.run(argc, argv);
    return 0;
}
    

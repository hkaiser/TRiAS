//-< QUERY.CPP >-----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Constructing and hashing database query statements
//-------------------------------------------------------------------*--------*

#include "gigabase.h"
#include "symtab.h"
#include "compiler.h"

dbMutex&        dbQueryElement::mutex = *new dbMutex;
dbQueryElement* dbQueryElement::freeChain;

dbQueryExpression& dbQueryExpression::operator = (dbComponent const& comp) 
{ 
    first = NULL; 
    last = &first;
    add(dbQueryElement::qExpression, comp.structure);
    if (comp.field != NULL) { 
	add(dbQueryElement::qExpression, ".");
	add(dbQueryElement::qExpression, comp.field);
    }
    operand = false;
    return *this;
}

dbQueryExpression& dbQueryExpression::operator=(dbQueryExpression const& expr)
{ 
    first = new dbQueryElement(dbQueryElement::qExpression, "(");
    first->next = expr.first;
    last = expr.last;
    *last = new dbQueryElement(dbQueryElement::qExpression, ")");
    last = &(*last)->next;
    operand = false;
    return *this;
}
 
dbQuery& dbQuery::add(dbQueryExpression const& expr) 
{ 
    append(dbQueryElement::qExpression, "(");
    *nextElement = expr.first;
    nextElement = expr.last;
    append(dbQueryElement::qExpression, ")");
    operand = false;
    return *this;
}



dbQuery& dbQuery::reset() 
{ 
    dbCriticalSection cs(dbQueryElement::mutex);
    *nextElement = dbQueryElement::freeChain;
    dbQueryElement::freeChain = elements;
    elements = NULL;
    nextElement = &elements;
    operand = false;
    dbCompiledQuery::destroy();
    return *this;
}

void dbCompiledQuery::destroy()
{
    if (tree != NULL) {
	dbCriticalSection cs(dbExprNode::mutex);
	delete tree;
	for (dbOrderByNode *op = order, *nop; op != NULL; op = nop) {
	    nop = op->next;
	    delete op;
	}
	for (dbFollowByNode *fp = follow, *nfp; fp != NULL; fp = nfp) {
	    nfp = fp->next;
	    delete fp;
	}
	tree = NULL;
    }
    startFrom = StartFromAny;
    follow = NULL;
    order = NULL;
    table = NULL;
}

int dbUserFunction::getParameterType()
{
    static byte argType[] = {  
	tpInteger,
	tpReal,
	tpString,
	tpInteger,
	tpReal,
	tpString,
	tpInteger,
	tpReal,
	tpString,
	tpInteger,
	tpReal,
	tpString
    };
    return argType[type];
}

dbUserFunction* dbUserFunction::list;


void dbUserFunction::bind(char* fname, void* f, funcType ftype) 
{ 
    name = fname;
    dbSymbolTable::add(name, tkn_ident, false);
    next = list;
    list = this;
    fptr = f;
    type = ftype;
}

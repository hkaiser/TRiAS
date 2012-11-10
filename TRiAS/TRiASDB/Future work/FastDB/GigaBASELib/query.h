//-< QUERY.H >-------------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Constructing and hashing database query statements
//-------------------------------------------------------------------*--------*

#ifndef __QUERY_H__
#define __QUERY_H__

class dbQueryElement { 
    friend class dbQuery;
    friend class dbCompiler;
    friend class dbQueryExpression;
  public:
    enum ElementType { 
	qExpression, // part of SQL expression
	qVarBool,
	qVarInt1,
	qVarInt2,
	qVarInt4,
	qVarInt8,
	qVarReal4,
	qVarReal8,
	qVarString,
	qVarStringPtr,
	qVarReference,
	qVarArrayOfRef,	
	qVarArrayOfRefPtr	
    };
    
    void* operator new (size_t size) { 
	dbCriticalSection cs(mutex);
	dbQueryElement* elem = freeChain;
	if (elem != NULL) { 
	    freeChain = elem->next;
	    return elem;
	} else { 
	    return new byte[size];
	}
    }

    dbQueryElement(ElementType t, void const* p, 
		   dbTableDescriptor* table = NULL) 
    {
	type = t;
	ptr  = p; 	
	ref  = table;
	next = NULL;
    } 
  private:
    dbQueryElement*    next;
    void const*        ptr;
    ElementType        type;
    dbTableDescriptor* ref;

    static dbMutex&    mutex;
    static dbQueryElement* freeChain;

};
    
#ifndef DB_QUERY_SEP
#define DB_QUERY_SEP ,
#endif
// Bugs in Microsoft Visual C++ makes it impossible to use operator, when
// exception throw statement is used or MFC headers are included.  
// Just use operator+ instead. 
// #define DB_QUERY_SEP +

#define DB_QUERY_OPR operator DB_QUERY_SEP
    
class dbComponent { 
  public:
    char const* structure;
    char const* field; 

    dbComponent(char const* s, char const* f=NULL) : structure(s), field(f) {}
};

class dbQueryExpression { 
    friend class dbQuery;
    dbQueryElement*  first;
    dbQueryElement** last;
    bool             operand;

    dbQueryExpression& add(dbQueryElement::ElementType type, void const* ptr) {
	last = &(*last = new dbQueryElement(type, ptr))->next;
	operand = (type == dbQueryElement::qExpression);
	return *this;
    }
	
  public:
    dbQueryExpression& operator = (char const* ptr) { 
	first = NULL, last = &first;
	return add(dbQueryElement::qExpression, ptr);
    }
    dbQueryExpression& operator = (dbComponent const& comp);

    dbQueryExpression& operator = (dbQueryExpression const& expr);

    dbQueryExpression& DB_QUERY_OPR(int1& ptr) { 
        return add(dbQueryElement::qVarInt1, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(int2& ptr) { 
        return add(dbQueryElement::qVarInt2, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(int4& ptr) { 
        return add(dbQueryElement::qVarInt4, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(int8& ptr) { 
        return add(dbQueryElement::qVarInt8, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(real4& ptr) { 
        return add(dbQueryElement::qVarReal4, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(real8& ptr) { 
        return add(dbQueryElement::qVarReal8, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(bool& ptr) { 
        return add(dbQueryElement::qVarBool, &ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(char const* ptr) { 
        return add(operand ? dbQueryElement::qVarString 
		   : dbQueryElement::qExpression, ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(char const** ptr) { 
        return add(dbQueryElement::qVarStringPtr, ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(char** ptr) { 
        return add(dbQueryElement::qVarStringPtr, ptr);
    }
    dbQueryExpression& DB_QUERY_OPR(dbQueryExpression const& expr) { 
	*last = new dbQueryElement(dbQueryElement::qExpression, "(");
	(*last)->next = expr.first;
	last = expr.last;
	*last = new dbQueryElement(dbQueryElement::qExpression, ")");
	last = &(*last)->next;
	operand = false;
	return *this;
    }
    dbQueryExpression& DB_QUERY_OPR(dbComponent const& comp) { 
	add(dbQueryElement::qExpression, comp.structure);
	if (comp.field != NULL) { 
	    add(dbQueryElement::qExpression, ".");
	    add(dbQueryElement::qExpression, comp.field);
	}
	operand = false;
	return *this;
    }
};

class dbOrderByNode;
class dbFollowByNode;

class dbCompiledQuery { 
  public:
    dbExprNode*        tree;
    dbOrderByNode*     order;
    dbFollowByNode*    follow;
    dbTableDescriptor* table;
    
    enum IteratorInit { 
	StartFromAny,
	StartFromFirst,
	StartFromLast,
	StartFromRef, 
	StartFromArray,
	StartFromArrayPtr
    };
    IteratorInit       startFrom;
    void const*        root;

    void destroy();

    bool compiled() { return tree != NULL; }

    dbCompiledQuery() { 
	tree = NULL;
	order = NULL;
	follow = NULL;
	table = NULL;
	startFrom = StartFromAny;
    }
};


class dbQuery : public dbCompiledQuery { 
    friend class dbCompiler;
    friend class dbDatabase;
  private:
    dbMutex            mutex;
    dbQueryElement*    elements;
    dbQueryElement**   nextElement;
    bool               operand;

    //
    // Prohibite query copying
    //
    dbQuery(dbQuery const&) {} 
    dbQuery& operator =(dbQuery const&) { return *this; }

  public:
    int                pos; // position of condition in statement

    dbQuery& append(dbQueryElement::ElementType type, void const* ptr,
		    dbTableDescriptor* table = NULL) 
    { 
	nextElement = &(*nextElement=new dbQueryElement(type,ptr,table))->next;
	operand = (type == dbQueryElement::qExpression);
	return *this;
    }

    dbQuery& reset();

    //
    // Redefined operator = and , make it possible to specify query in the
    // following way:
    //         int x, y;
    //         dbDataTime dt;
    //         dbQuery q; 
    //         dbCursor<record> cursor;
    //         q = "x=",x,"and y=",y,"and",dt == "date";
    //         for (x = 0; x < max_x; x++) { 
    //             for (y = 0; y < max_y; y++) { 
    //                 cursor.select(q);
    //                 ...
    //             }
    //         }

    dbQuery& add(dbQueryExpression const& expr); 

    dbQuery& and(char const* str) { 
	if (elements != NULL) { 
	    append(dbQueryElement::qExpression, "and");
	}
	return append(dbQueryElement::qExpression, str);
    }

    dbQuery& or(char const* str) { 
	if (elements != NULL) { 
	    append(dbQueryElement::qExpression, "or");
	}
	return append(dbQueryElement::qExpression, str);
    }

    dbQuery& add(char const* str) { 
	return append(operand ? dbQueryElement::qVarString 
		      : dbQueryElement::qExpression, str);
    }
    dbQuery& add(char const** str) { 
	return append(dbQueryElement::qVarStringPtr, str);
    }
    dbQuery& add(char** str) { 
	return append(dbQueryElement::qVarStringPtr, str);
    }
    dbQuery& add(int1& value) { 
	return append(dbQueryElement::qVarInt1, &value);
    }
    dbQuery& add (int2& value) { 
	return append(dbQueryElement::qVarInt2, &value);
    }
    dbQuery& add (int4& value) { 
	return append(dbQueryElement::qVarInt4, &value);
    }
    dbQuery& add (int8& value) { 
	return append(dbQueryElement::qVarInt8, &value);
    }
    dbQuery& add (real4& value) { 
	return append(dbQueryElement::qVarReal4, &value);
    }
    dbQuery& add(real8& value) { 
	return append(dbQueryElement::qVarReal8, &value);
    }
    dbQuery& add(bool& value) { 
	return append(dbQueryElement::qVarBool, &value);
    }

    dbQuery& DB_QUERY_OPR(char const*  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(char const** value) { return add(value); }
    dbQuery& DB_QUERY_OPR(char** value) { return add(value); }
    dbQuery& DB_QUERY_OPR(int1&  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(int2&  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(int4&  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(int8&  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(real4& value) { return add(value); }
    dbQuery& DB_QUERY_OPR(real8& value) { return add(value); }
    dbQuery& DB_QUERY_OPR(bool&  value) { return add(value); }
    dbQuery& DB_QUERY_OPR(dbQueryExpression const& expr) { return add(expr); }

    dbQuery& operator = (const char* str) { 
	return reset().append(dbQueryElement::qExpression, str);
    }
    dbQuery& operator = (dbQueryExpression const& expr) { 
	return reset().add(expr);
    }

    dbQuery() { 
	elements = NULL;
	nextElement = &elements;
	operand = false;
	pos = 0;
    } 
    dbQuery(char const* str) { 
	elements = new dbQueryElement(dbQueryElement::qExpression, str);
	nextElement = &elements->next;
	operand = true;
	pos = 0;
    } 
    ~dbQuery() { 
	reset();
    }
};

template<class T>
inline dbQuery& DB_QUERY_OPR(dbQuery& query, dbReference<T> const& value) { 
    return query.append(dbQueryElement::qVarReference, &value, 
			&T::dbDescriptor);
}

template<class T>
inline dbQuery& DB_QUERY_OPR(dbQuery& query, 
			     dbArray< dbReference<T> > const& value) 
{ 
    return query.append(dbQueryElement::qVarArrayOfRef, &value, 
			&T::dbDescriptor);
}

template<class T>
inline dbQuery& DB_QUERY_OPR(dbQuery& query, 
			     dbArray< dbReference<T> >const* const& value) 
{ 
    return query.append(dbQueryElement::qVarArrayOfRefPtr, &value, 
			&T::dbDescriptor);
}

#define USER_FUNC(f) static dbUserFunction f##_descriptor(&f, #f)

class dbUserFunction { 
    friend class dbDatabase;
    friend class dbCompiler;

    void* fptr;
    char* name;
    
    dbUserFunction* next;
    static dbUserFunction* list;

    enum funcType {
	fInt2Bool,
	fReal2Bool,
	fStr2Bool,
	fInt2Int,
	fReal2Int,
	fStr2Int,
	fInt2Real,
	fReal2Real,
	fStr2Real,
	fInt2Str,
	fReal2Str,
	fStr2Str
    };
    int type;

    void bind(char* name, void* f, funcType ftype);

  public:

    static dbUserFunction* find(char const* name) { 
	for (dbUserFunction* func = list; func != NULL; func = func->next) { 
	    if (name == func->name) { 
		return func;
	    }
	}
	return NULL;
    }
    
    int getParameterType();

    dbUserFunction(bool (*f)(int8), char* name) { 
	bind(name, (void*)f, fInt2Bool); 
    }
    dbUserFunction(bool (*f)(real8), char* name) { 
	bind(name, (void*)f, fReal2Bool); 
    }
    dbUserFunction(bool (*f)(char const*), char* name) { 
	bind(name, (void*)f, fStr2Bool); 
    }
    dbUserFunction(int8 (*f)(int8), char* name) { 
	bind(name, (void*)f, fInt2Int); 
    }
    dbUserFunction(int8 (*f)(real8), char* name) { 
	bind(name, (void*)f, fReal2Int); 
    }
    dbUserFunction(int8 (*f)(char const*), char* name) { 
	bind(name, (void*)f, fStr2Int); 
    }
    dbUserFunction(real8 (*f)(int8), char* name) { 
	bind(name, (void*)f, fInt2Real); 
    }
    dbUserFunction(real8 (*f)(real8), char* name) { 
	bind(name, (void*)f, fReal2Real); 
    }
    dbUserFunction(real8 (*f)(char const*), char* name) { 
	bind(name, (void*)f, fStr2Real); 
    }
    dbUserFunction(char* (*f)(int8), char* name) { 
	bind(name, (void*)f, fInt2Str); 
    }
    dbUserFunction(char* (*f)(real8), char* name) { 
	bind(name, (void*)f, fReal2Str); 
    }
    dbUserFunction(char* (*f)(char const*), char* name) { 
	bind(name, (void*)f, fStr2Str); 
    }
};

#endif


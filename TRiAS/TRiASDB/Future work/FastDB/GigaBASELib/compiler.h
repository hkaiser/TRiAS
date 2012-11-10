//-<  COMPILE.H >----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 17-Jan-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Conditional expresion compiler
//-------------------------------------------------------------------*--------*

#ifndef __COMPILER_H__
#define __COMPILER_H__

#include <setjmp.h>

#if defined(__osf__) || defined(__FreeBSD__)
#define longjmp(b,s) _longjmp(b,s) // do not restore signal context
#define setjmp(b)  _setjmp(b)
#endif

#define DEBUG_NONE  0
#define DEBUG_CHECK 1
#define DEBUG_TRACE 2

#if DEBUG == DEBUG_TRACE
#define TRACE_MSG(x)  dbTrace x
#else
#define TRACE_MSG(x)
#endif

extern void dbTrace(char* message, ...);

enum dbvmCodes { 
#define DBVM(cop, type, n_operands, commutative) cop,
#include "compiler.d"
dbvmLastCode
};

#define IS_CONSTANT(c) \
(unsigned(c) - dbvmLoadVarBool <= dbvmLoadStringConstant - dbvmLoadVarBool)

enum nodeType { 
    tpInteger,
    tpBoolean,
    tpReal,
    tpString,
    tpReference,
    tpArray,
    tpFreeVar,  // index of EXISTS clause 
    tpList,     // list of expressions
    tpVoid
};

enum tokens { 
    tkn_ident,
    tkn_lpar,
    tkn_rpar,
    tkn_lbr,
    tkn_rbr,
    tkn_dot,
    tkn_comma,
    tkn_power,
    tkn_iconst,
    tkn_sconst,
    tkn_fconst,
    tkn_add,
    tkn_sub,
    tkn_mul,
    tkn_div,
    tkn_and,
    tkn_or,
    tkn_not,
    tkn_null,
    tkn_neg,
    tkn_eq,
    tkn_ne,
    tkn_gt,
    tkn_ge,
    tkn_lt,
    tkn_le,
    tkn_between,
    tkn_escape,
    tkn_exists,
    tkn_like,
    tkn_in,
    tkn_length,
    tkn_lower,
    tkn_upper,
    tkn_abs,
    tkn_is,
    tkn_integer,
    tkn_real,
    tkn_string,
    tkn_first,
    tkn_last,
    tkn_current,
    tkn_var,
    tkn_col,
    tkn_true,
    tkn_false,
    tkn_where, 
    tkn_follow,
    tkn_start,
    tkn_from,
    tkn_order,
    tkn_by,
    tkn_asc,
    tkn_desc, 
    tkn_eof,
    tkn_last_token
};    

struct dbStrLiteral { 
    char* str;
    int   len;
};


class dbUserFunction;

class dbExprNode { 
    friend class dbExprNodeSegment;
  public:
    nat1 cop;
    nat1 type;
    nat2 offs;

    static const nat1  nodeTypes[];
    static const nat1  nodeOperands[];
    static const nat1  commutativeOperator[];
    static dbExprNode* freeNodeList;
    static dbMutex&    mutex;

    static dbExprNodeSegment* segmentList;

    union { 
        dbExprNode*  operand[3];
        dbExprNode*  next;
	oid_t        oid;
	int8         ivalue;
	real8        fvalue;
	dbStrLiteral svalue;
	void const*  var;

	struct { 
	    dbExprNode*         base;  // the same as operand[0]
	    dbFieldDescriptor*  field;
	} ref;

	struct { 
	    dbExprNode*         arg;   // the same as operand[0]
	    void*               fptr;
	} func;
    };

    dbExprNode(dbExprNode* node);

    dbExprNode(int cop, dbExprNode* left = NULL, dbExprNode* right = NULL, 
	       dbExprNode* right2 = NULL)
    {
	this->cop = cop;
	type = nodeTypes[cop];
	operand[0] = left;
	operand[1] = right;
	operand[2] = right2;
    }
    dbExprNode(int cop, dbExprNode* expr1, dbExprNode* expr2, int offs) { 
	this->cop = cop;
	this->offs = offs;
	type = nodeTypes[cop];
	operand[0] = expr1;
	operand[1] = expr2;
    }
    dbExprNode(int cop, dbExprNode* expr, int offs) { 
	this->cop = cop;
	this->offs = offs;
	type = nodeTypes[cop];
	operand[0] = expr;
    }
    dbExprNode(int cop, dbFieldDescriptor* field, dbExprNode* base = NULL) 
    {
	this->cop = cop;
	this->offs = field->dbsOffs;
	type = nodeTypes[cop];
	ref.field = field;
	ref.base = base;
    }
    dbExprNode(int cop, int8 ivalue) { 
 	this->cop = cop;
	this->ivalue = ivalue;
	type = tpInteger;
    }
    dbExprNode(int cop, real8 fvalue) { 
 	this->cop = cop;
	this->fvalue = fvalue;
	type = tpReal;
    }
    dbExprNode(int cop, dbStrLiteral& svalue) { 
 	this->cop = cop;
	this->svalue = svalue;
	type = tpString;
    }
    dbExprNode(int cop, void const* var) { 
 	this->cop = cop;
	this->var = var;
	type = nodeTypes[cop];
    }
    dbExprNode(int cop, dbExprNode* expr, void* fptr) { 
 	this->cop = cop;
	func.arg = expr;
	func.fptr = fptr;
	type = nodeTypes[cop];
    }
    ~dbExprNode();

    void* operator new(size_t size);

    void operator delete(void* ptr) { 
	if (ptr != NULL) { 
	    dbExprNode* node = (dbExprNode*)ptr;
	    node->next = freeNodeList;
	    freeNodeList = node;
	}
    }

    static void cleanup();
};


class dbExprNodeSegment { 
  public:
    enum { allocationQuantum = 1024};
    char               buf[sizeof(dbExprNode)*allocationQuantum];
    dbExprNodeSegment* next;
};


class dbBinding { 
  public:
    dbBinding*  next;
    char const* name;
    bool        used;
    int         index;
};

class dbOrderByNode { 
  public:
    dbOrderByNode*     next;
    dbFieldDescriptor* field;
    bool               ascent;  // true for ascent order, false for descent 
};

class dbFollowByNode { 
  public:
    dbFollowByNode*    next;
    dbFieldDescriptor* field;
};

class dbCompiler { 
    friend class dbQuery;
    friend class dbQueryElement;
  public:
    enum { 
	maxStrLen    = 4096,
	maxFreeVars  = 4
    };

    dbTableDescriptor* table;
    dbQueryElement*    queryElement;
    int                currPos;
    int                firstPos;
    int                offsetWithinStatement;
    int                bvalue;
    int8               ivalue;
    real8              fvalue;
    dbStrLiteral       svalue;
    int                lex;
    char*              name;
    dbBinding*         bindings;
    int                nFreeVars;
    int                varType;
    void const*        varPtr;
    dbTableDescriptor* varRefTable;

    jmp_buf            abortCompilation;
    static bool        initialized;

    int         compare(dbExprNode* expr, dbExprNode* list);

    int         scan();
    void        error(const char* msg, int pos = -1);
    dbExprNode* conjunction();    
    dbExprNode* disjunction();
    dbExprNode* comparison();    
    dbExprNode* addition();    
    dbExprNode* multiplication();    
    dbExprNode* power();
    dbExprNode* term();
    dbExprNode* field(dbExprNode* expr, dbTableDescriptor* refTable,
		      dbFieldDescriptor* fd);

    bool        compile(dbTableDescriptor* table, dbQuery& query);
    void        compileOrderByPart(dbQuery& query);
    void        compileStartFollowPart(dbQuery& query);

    dbCompiler();
};

class dbDatabaseThreadContext { 
  public:
    int readAccess;
    int writeAccess;
    int concurrentId;
    dbL2List cursors; 
    
    dbCompiler compiler;
    
    bool     interactive;
    jmp_buf  unwind;

    dbDatabaseThreadContext() { 
	concurrentId = 0;
	readAccess = false;
	writeAccess = false;
	interactive = false;
    }
};

class dbSynthesizedAttribute { 
  public:
    union { 
	byte* base;
	int   bvalue;
	int8  ivalue;
	real8 fvalue;
	oid_t oid;
	
	struct { 
	    char* base;
	    int   size;
	} array;
    };
    enum ObjectStorageClass {
	osSelf,     // self object field
	osStack,    // object allocate on stack
	osDynamic,  // object allocated by operstor new
	osPage      // reference to page in page pool
    };
    ObjectStorageClass osClass;    
    union { 
	int sp; 
	struct {
	    byte*                   addr;
	    dbSynthesizedAttribute* next;
	} loc;
    } os;
};

class dbInheritedAttribute { 
  public:
    byte*              record;
    oid_t              oid;
    dbTableDescriptor* table;
    dbDatabase*        db;

    enum { 
	internalStackSize = 64*1024
    };


    dbSynthesizedAttribute* dynChain;
    size_t sp;

    struct IteratorContext { 
	int     index;
	int     sp;
	dbSynthesizedAttribute* dynChain; 
	jmp_buf unwind;
    } iterator[dbCompiler::maxFreeVars];

    byte   stack[internalStackSize];
    
    void cleanup() { 
	dbSynthesizedAttribute* attr;
	for (attr = dynChain; attr != NULL; attr = attr->os.loc.next) { 
	    free(*dynChain);
	}
    }
	
    void unwind(int i) { 
	IteratorContext* ctx = &iterator[i];
	sp = ctx->sp;
	while (dynChain != ctx->dynChain) {
	    free(*dynChain);
	    dynChain = dynChain->os.loc.next;
	}	
	longjmp(ctx->unwind, 1);
    }

    void makeDynamic(dbSynthesizedAttribute& attr, void* p) {
	attr.osClass = dbSynthesizedAttribute::osDynamic;
	attr.os.loc.addr = (byte*)p;		
	attr.os.loc.next = dynChain;
	dynChain = &attr;
    }
    void allocateString(dbSynthesizedAttribute& attr, int len) {
	if (sp + len > sizeof(stack)) {
	    attr.array.base = new char[len];
	    attr.array.size = len;
	    makeDynamic(attr, attr.array.base);
	} else { 
	    attr.osClass = dbSynthesizedAttribute::osStack;
	    attr.array.base = (char*)stack + sp;
	    attr.array.size = len;
	    attr.os.sp = sp;
	    sp += len;
	}
    }
    void allocateString(dbSynthesizedAttribute& attr, char* str, size_t len) {
	allocateString(attr, len);
	memcpy(attr.array.base, str, len);
    }
    void allocateString(dbSynthesizedAttribute& attr, char* str) {
	allocateString(attr, str, strlen(str) + 1);
    }

    void free(dbSynthesizedAttribute& attr) { 
	switch (attr.osClass) { 
	  case dbSynthesizedAttribute::osStack:
	    sp = attr.os.sp;
	    break;
	  case dbSynthesizedAttribute::osPage:
	    db->pool.unfix(attr.os.loc.addr);
	    dynChain = dynChain->os.loc.next;
	    break;
	  case dbSynthesizedAttribute::osDynamic:
	    delete[] attr.os.loc.addr;	
	    dynChain = dynChain->os.loc.next;
	    break;
	  default:
	    break;
	}
    }
    
    void load(dbSynthesizedAttribute& sattr) { 
	offs_t pos = db->getPos(sattr.oid) & ~dbFlagsMask;
	int offs = (int)pos & (dbPageSize-1);
	byte* page = db->pool.get(pos - offs);
	dbRecord* rec = (dbRecord*)(page + offs);
	size_t size = rec->size;
	if (offs + size > dbPageSize) { 
	    byte* dst;
	    int start = DOALIGN(sp, 8);
	    if (start + size > sizeof(stack)) { 
		dst = new byte[size];
		makeDynamic(sattr, dst);
	    } else { 
		sattr.osClass = dbSynthesizedAttribute::osStack;
		sattr.os.sp = sp;
		dst = stack + start;
		sp = start + size;
	    }
	    sattr.base = dst;
	    memcpy(dst, rec, dbPageSize - offs);
	    db->pool.unfix(page);
	    size -= dbPageSize - offs;
	    pos += dbPageSize - offs;
	    dst += dbPageSize - offs;
	    while (size > dbPageSize) { 
		page = db->pool.get(pos);
		memcpy(dst, page, dbPageSize);
		db->pool.unfix(page);
		dst += dbPageSize;
		size -= dbPageSize;
		pos += dbPageSize;
	    }
	    page = db->pool.get(pos);
	    memcpy(dst, page, size);
	    db->pool.unfix(page);
	} else { 
	    sattr.base = (byte*)rec;    
	    sattr.osClass = dbSynthesizedAttribute::osPage;
	    sattr.os.loc.addr = page;	    
	    sattr.os.loc.next = dynChain;
	    dynChain = &sattr;
	}
    }

    dbInheritedAttribute() { 
	dynChain = NULL;
	sp = 0;
    }

    ~dbInheritedAttribute() { 
	cleanup(); 
    }
};

#endif

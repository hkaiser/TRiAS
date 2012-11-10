//-< DATABASE.CPP >--------------------------------------------------*--------*
// FastDB                    Version 1.0         (c) 1999  GARRET    *     ?  *
// (Main Memory Database Management System)                          *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 14-Jan-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Database memory management, query execution, scheme evaluation
//-------------------------------------------------------------------*--------*


#include <ctype.h>
#include <math.h>
#include "fastdb.h"
#include "compiler.h"
#include "hashtab.h"
#include "ttree.h"
#include "symtab.h"

dbNullReference null;

char const* const dbMetaTableName = "Metatable";
 
unsigned dbDatabase::dbParallelScanThreshold = 1000;

size_t dbDatabase::internalObjectSize[] = {
    0,
    dbPageSize,
    sizeof(dbTtree),
    sizeof(dbTtreeNode),
    sizeof(dbHashTable),
    sizeof(dbHashTableItem)
};

inline void convertIntToString(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr)
{
    char buf[32];
    sattr.array.size = sprintf(buf, INT8_FORMAT, sattr.ivalue) + 1;
    sattr.array.base = dbStringValue::create(buf, iattr);
}

inline void convertRealToString(dbInheritedAttribute&   iattr,
				dbSynthesizedAttribute& sattr)
{
    char buf[32];
    sattr.array.size = sprintf(buf, "%f", sattr.fvalue) + 1;
    sattr.array.base = dbStringValue::create(buf, iattr);
}

inline void concatenateStrings(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr,
			       dbSynthesizedAttribute& sattr2)
{
    char* str = 
	dbStringValue::create(sattr.array.size + sattr.array.size - 1, iattr);
    memcpy(str, sattr.array.base, sattr.array.size-1);
    memcpy(str + sattr.array.size - 1, sattr2.array.base, sattr2.array.size);
    sattr.array.base = str;
    sattr.array.size += sattr2.array.size-1;
}

inline int compareStringsForEquality(dbSynthesizedAttribute& sattr1,
				     dbSynthesizedAttribute& sattr2)
{
#ifdef IGNORE_CASE
    return stricmp(sattr1.array.base, sattr2.array.base);
#else
    return strcmp(sattr1.array.base, sattr2.array.base);
#endif
}

inline int compareStrings(dbSynthesizedAttribute& sattr1,
			  dbSynthesizedAttribute& sattr2)
{
#ifdef USE_LOCALTE_SETTINGS
#ifdef IGNORE_CASE
    return stricoll(sattr1.array.base, sattr2.array.base);
#else
    return strcoll(sattr1.array.base, sattr2.array.base);
#endif
#else
#ifdef IGNORE_CASE
    return stricmp(sattr1.array.base, sattr2.array.base);
#else
    return strcmp(sattr1.array.base, sattr2.array.base);
#endif
#endif
}

#ifdef IGNORE_CASE
#define GET_CHAR(c) toupper((byte)(c))
#else
#define GET_CHAR(c) (c)
#endif

inline bool matchStrings(dbSynthesizedAttribute& sattr1,
			 dbSynthesizedAttribute& sattr2,
			 char escapeChar)
{
    char *str = sattr1.array.base;
    char *pattern = sattr2.array.base;
    char *wildcard = NULL; 
    char *strpos = NULL;
    while (true) { 
	int ch = GET_CHAR(*str);
	if (*pattern == dbMatchAnySubstring) { 
	    wildcard = ++pattern;
	    strpos = str;
	} else if (ch == '\0') { 
	    return (*pattern == '\0');
	} else if (*pattern == escapeChar && GET_CHAR(pattern[1]) == ch) { 
	    str += 1;
	    pattern += 2;
	} else if (*pattern != escapeChar
		   && (ch == GET_CHAR(*pattern)
		       || *pattern == dbMatchAnyOneChar))
        { 
	    str += 1;
	    pattern += 1;
	} else if (wildcard) { 
	    str = ++strpos;
	    pattern = wildcard;
	} else { 
	    return false;
	}
    }
}

inline bool matchStrings(dbSynthesizedAttribute& sattr1,
			 dbSynthesizedAttribute& sattr2)
{
    char *str = sattr1.array.base;
    char *pattern = sattr2.array.base;
    char *wildcard = NULL; 
    char *strpos = NULL;
    while (true) { 
	int ch = GET_CHAR(*str);
	if (*pattern == dbMatchAnySubstring) { 
	    wildcard = ++pattern;
	    strpos = str;
	} else if (ch == '\0') { 
	    return (*pattern == '\0');
	} else if (ch == GET_CHAR(*pattern) || *pattern == dbMatchAnyOneChar) {
	    str += 1;
	    pattern += 1;
	} else if (wildcard) { 
	    str = ++strpos;
	    pattern = wildcard;
	} else { 
	    return false;
	}
    }
}


inline void lowercaseString(dbInheritedAttribute&   iattr,
			    dbSynthesizedAttribute& sattr) 
{ 
    char *dst = dbStringValue::create(sattr.array.size, iattr);
    char *src = sattr.array.base;
    sattr.array.base = dst;
    while ((*dst++ = tolower(byte(*src++))) != '\0');
}    

inline void uppercaseString(dbInheritedAttribute&   iattr,
			    dbSynthesizedAttribute& sattr) 
{ 
    char *dst = dbStringValue::create(sattr.array.size, iattr);
    char *src = sattr.array.base;
    sattr.array.base = dst;
    while ((*dst++ = toupper(byte(*src++))) != '\0');
}    

inline void copyString(dbInheritedAttribute&   iattr,
		       dbSynthesizedAttribute& sattr, char* str) 
{ 
    sattr.array.base = dbStringValue::create(str, iattr);
    sattr.array.size = strlen(str) + 1;
    delete[] str;
}    

inline void searchArrayOfBool(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    bool *p = (bool*)sattr2.array.base;
    int   n = sattr2.array.size;
    bool  v = (bool)sattr.bvalue;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    return;
	}
    }
    sattr.bvalue = false;
}

inline void searchArrayOfInt1(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int1 *p = (int1*)sattr2.array.base;
    int   n = sattr2.array.size;
    int1  v = (int1)sattr.ivalue;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    return;
	}
    }
    sattr.bvalue = false;
}

inline void searchArrayOfInt2(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int2 *p = (int2*)sattr2.array.base;
    int   n = sattr2.array.size;
    int2  v = (int2)sattr.ivalue;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    return;
	}
    }
    sattr.bvalue = false;
}

inline void searchArrayOfInt4(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int4 *p = (int4*)sattr2.array.base;
    int   n = sattr2.array.size;
    int4  v = (int4)sattr.ivalue;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    return;
	}
    }
    sattr.bvalue = false;
}

inline void searchArrayOfInt8(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int8 *p = (int8*)sattr2.array.base;
    int   n = sattr2.array.size;
    int8  v = sattr.ivalue;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    return;
	}
	p += 1;
    }
    sattr.bvalue = false;
}

inline void searchArrayOfReal4(dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    real4* p = (real4*)sattr2.array.base;
    int    n = sattr2.array.size;
    real4  v = (real4)sattr.fvalue;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    return;
	}
    }
    sattr.bvalue = false;
}

inline void searchArrayOfReal8(dbSynthesizedAttribute& sattr, 
			       dbSynthesizedAttribute& sattr2)
{
    real8 *p = (real8*)sattr2.array.base;
    int    n = sattr2.array.size;
    real8  v = sattr.fvalue;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    return;
	}
	p += 1;
    }
    sattr.bvalue = false;
}

inline void searchArrayOfReference(dbSynthesizedAttribute& sattr, 
				   dbSynthesizedAttribute& sattr2)
{
    oid_t *p = (oid_t*)sattr2.array.base;
    int    n = sattr2.array.size;
    oid_t  v = sattr.oid;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    return;
	}
	p += 1;
    }
    sattr.bvalue = false;
}

inline void searchArrayOfString(dbSynthesizedAttribute& sattr, 
				dbSynthesizedAttribute& sattr2)
{
    dbVarying *p = (dbVarying*)sattr2.array.base;
    int        n = sattr2.array.size;
    char*      str = sattr.array.base;
    char*      base = (char*)sattr2.base; 
    while (--n >= 0) { 
	if (strcmp(base + p->offs, str) == 0) { 
	    sattr.bvalue = true;
	    return;
	}
	p += 1;
    }
    sattr.bvalue = false;
}

inline void searchInString(dbSynthesizedAttribute& sattr, 
			   dbSynthesizedAttribute& sattr2)
{
    if (sattr.array.size > sattr2.array.size) { 
	sattr.bvalue = false;
    } else if (sattr2.array.size > dbBMsearchThreshold) { 
	int len = sattr.array.size - 2;
	int n = sattr2.array.size - 1;
	int i, j, k;
	int shift[256];
	byte* pattern = (byte*)sattr.array.base;
	byte* str = (byte*)sattr2.array.base;
	for (i = 0; i < (int)items(shift); i++) { 
	    shift[i] = len+1;
	}
 	for (i = 0; i < len; i++) { 
	    shift[pattern[i]] = len-i;
	}
	for (i = len; i < n; i += shift[str[i]]) { 
	    j = len;
	    k = i;
	    while (pattern[j] == str[k]) { 
		k -= 1;
		if (--j < 0) { 
		    sattr.bvalue = true;
		    return;
		}
	    }
	}
	sattr.bvalue = false;
    } else { 
	sattr.bvalue = strstr(sattr2.array.base, sattr.array.base) != NULL;
    }
}

inline int8 powerIntInt(int8 x, int8 y) 
{
    int8 res = 1;

    if (y < 0) {
	x = 1/x;
	y = -y;
    }
    while (y != 0) {
	if (y & 1) { 
	    res *= x;
	}
	x *= x;
	y >>= 1;
    }
    return res;    
}

inline real8 powerRealInt(real8 x, int8 y) 
{
    real8 res = 1.0;

    if (y < 0) {
	x = 1/x;
	y = -y;
    }
    while (y != 0) {
	if (y & 1) { 
	    res *= x;
	}
	x *= x;
	y >>= 1;
    }
    return res;    
}



bool dbDatabase::evaluate(dbExprNode* expr, oid_t oid, dbTable* table)
{
    dbInheritedAttribute iattr;
    dbSynthesizedAttribute sattr;
    iattr.db = this;
    iattr.oid = oid;
    iattr.table = table;
    iattr.record = (byte*)getRow(oid);    
    execute(expr, iattr, sattr);
    return sattr.bvalue != 0;
}


void _fastcall dbDatabase::execute(dbExprNode*             expr, 
				   dbInheritedAttribute&   iattr, 
				   dbSynthesizedAttribute& sattr)
{
    dbSynthesizedAttribute sattr2, sattr3;

    switch (expr->cop) {
      case dbvmVoid:
	sattr.bvalue = true; // empty condition
	return;
      case dbvmCurrent:
	sattr.oid = iattr.oid;
	return;
      case dbvmFirst:
	sattr.oid = iattr.table->firstRow;
	return;
      case dbvmLast:
	sattr.oid = iattr.table->lastRow;
	return;
      case dbvmLoadBool:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = *(bool*)(sattr.base+expr->offs);
	return;
      case dbvmLoadInt1:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int1*)(sattr.base+expr->offs);
	return;
      case dbvmLoadInt2:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int2*)(sattr.base+expr->offs);
	return;
      case dbvmLoadInt4:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int4*)(sattr.base+expr->offs);
	return;
      case dbvmLoadInt8:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int8*)(sattr.base+expr->offs);
	return;
      case dbvmLoadReal4:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = *(real4*)(sattr.base+expr->offs);
	return;
      case dbvmLoadReal8:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = *(real8*)(sattr.base+expr->offs);
	return;
      case dbvmLoadReference:
	execute(expr->operand[0], iattr, sattr);
	sattr.oid = *(oid_t*)(sattr.base+expr->offs);
	return;
      case dbvmLoadArray:
      case dbvmLoadString:
	execute(expr->operand[0], iattr, sattr2);
	sattr.array.base = (char*)sattr2.base 
	    + ((dbVarying*)(sattr2.base + expr->offs))->offs;
	sattr.array.size = ((dbVarying*)(sattr2.base + expr->offs))->size;
	return;

      case dbvmLoadSelfBool:
	sattr.bvalue = *(bool*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfInt1:
	sattr.ivalue = *(int1*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfInt2:
	sattr.ivalue = *(int2*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfInt4:
	sattr.ivalue = *(int4*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfInt8:
	sattr.ivalue = *(int8*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfReal4:
	sattr.fvalue = *(real4*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfReal8:
	sattr.fvalue = *(real8*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfReference:
	sattr.oid = *(oid_t*)(iattr.record+expr->offs);
	return;
      case dbvmLoadSelfArray:
      case dbvmLoadSelfString:
	sattr.array.base = (char*)iattr.record + 
	    ((dbVarying*)(iattr.record + expr->offs))->offs;
	sattr.array.size = ((dbVarying*)(iattr.record + expr->offs))->size;
	return;

      case dbvmInvokeMethodBool:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.bvalue);
	sattr.bvalue = *(bool*)&sattr.bvalue;
	return;
      case dbvmInvokeMethodInt1:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int1*)&sattr.ivalue;
	return;
      case dbvmInvokeMethodInt2:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int2*)&sattr.ivalue;
	return;
      case dbvmInvokeMethodInt4:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int4*)&sattr.ivalue;
	return;
      case dbvmInvokeMethodInt8:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	return;
      case dbvmInvokeMethodReal4:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.fvalue); 
	sattr.fvalue = *(real4*)&sattr.fvalue;
	return;
      case dbvmInvokeMethodReal8:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.fvalue);
	return;
      case dbvmInvokeMethodReference:
	execute(expr->ref.base, iattr, sattr);
        expr->ref.field->method->invoke(sattr.base, &sattr.oid);
	return;
      case dbvmInvokeMethodString:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr2.array.base);
	sattr.array.size = strlen(sattr2.array.base) + 1;
	sattr.array.base = dbStringValue::create(sattr2.array.base, iattr);
	delete[] sattr2.array.base;
	return;

      case dbvmInvokeSelfMethodBool:
	expr->ref.field->method->invoke(iattr.record, &sattr.bvalue);
	sattr.bvalue = *(bool*)&sattr.bvalue;
	return;
      case dbvmInvokeSelfMethodInt1:
	expr->ref.field->method->invoke(iattr.record, &sattr.ivalue);
	sattr.ivalue = *(int1*)&sattr.ivalue;
	return;
      case dbvmInvokeSelfMethodInt2:
	expr->ref.field->method->invoke(iattr.record, &sattr.ivalue);
	sattr.ivalue = *(int2*)&sattr.ivalue;
	return;
      case dbvmInvokeSelfMethodInt4:
	expr->ref.field->method->invoke(iattr.record, &sattr.ivalue);
	sattr.ivalue = *(int4*)&sattr.ivalue;
	return;
      case dbvmInvokeSelfMethodInt8:
	expr->ref.field->method->invoke(iattr.record, &sattr.ivalue);
	return;
      case dbvmInvokeSelfMethodReal4:
	expr->ref.field->method->invoke(iattr.record, &sattr.fvalue); 
	sattr.fvalue = *(real4*)&sattr.fvalue;
	return;
      case dbvmInvokeSelfMethodReal8:
	expr->ref.field->method->invoke(iattr.record, &sattr.fvalue);
	return;
      case dbvmInvokeSelfMethodReference:
	expr->ref.field->method->invoke(iattr.record, &sattr.oid);
	return;
      case dbvmInvokeSelfMethodString:
	expr->ref.field->method->invoke(iattr.record, &sattr2.array.base);
	sattr.array.size = strlen(sattr2.array.base) + 1;
	sattr.array.base = dbStringValue::create(sattr2.array.base, iattr);
	delete[] sattr2.array.base;
	return;

      case dbvmLength:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = sattr.array.size;
	return;
      case dbvmStringLength:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = sattr.array.size - 1;
	return;

      case dbvmGetAt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if ((nat8)sattr2.ivalue >= (nat8)sattr.array.size) { 
	    if (expr->operand[1]->cop == dbvmVariable) { 
		longjmp(iattr.iterator[expr->operand[1]->offs].unwind, 1);
	    }
	    iattr.removeTemporaries();
	    iattr.db->handleError(IndexOutOfRangeError, NULL, 
				  int(sattr2.ivalue));
	}
	sattr.base = (byte*)sattr.array.base + int(sattr2.ivalue)*expr->offs;
	return;
      case dbvmCharAt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if ((nat8)sattr2.ivalue >= (nat8)(sattr.array.size-1)) { 
	    if (expr->operand[1]->cop == dbvmVariable) { 
		longjmp(iattr.iterator[expr->operand[1]->offs].unwind, 1);
	    }
	    iattr.removeTemporaries();
	    iattr.db->handleError(IndexOutOfRangeError, NULL, 
				  int(sattr2.ivalue));
	}
	sattr.ivalue = (byte)sattr.array.base[int(sattr2.ivalue)];
	return;

      case dbvmExists:
	iattr.iterator[expr->offs].index = 0;
	if (setjmp(iattr.iterator[expr->offs].unwind) == 0) { 
	    do { 
		execute(expr->operand[0], iattr, sattr);
		iattr.iterator[expr->offs].index += 1;
	    } while (!sattr.bvalue);
	} else {
	    sattr.bvalue = false;
	}
	return;

      case dbvmVariable:
	sattr.ivalue = iattr.iterator[expr->offs].index;
	return;

      case dbvmLoadVarBool:
	sattr.bvalue = *(bool*)expr->var;
	return;
      case dbvmLoadVarInt1:
	sattr.ivalue = *(int1*)expr->var;
	return;
      case dbvmLoadVarInt2:
	sattr.ivalue = *(int2*)expr->var;
	return;
      case dbvmLoadVarInt4:
	sattr.ivalue = *(int4*)expr->var;
	return;
      case dbvmLoadVarInt8:
	sattr.ivalue = *(int8*)expr->var;
	return;
      case dbvmLoadVarReal4:
	sattr.fvalue = *(real4*)expr->var;
	return;
      case dbvmLoadVarReal8:
	sattr.fvalue = *(real8*)expr->var;
	return;
      case dbvmLoadVarReference:
	sattr.oid = *(oid_t*)expr->var;
	return;
      case dbvmLoadVarString:
	sattr.array.base = (char*)expr->var;
	sattr.array.size = strlen((char*)sattr.array.base) + 1;
	return;
      case dbvmLoadVarStringPtr:
	sattr.array.base = *(char**)expr->var;
	sattr.array.size = strlen((char*)sattr.array.base) + 1;
	return;
      case dbvmLoadVarArray:
	sattr.array.base = (char*)((dbAnyArray*)expr->var)->base();
	sattr.array.size = ((dbAnyArray*)expr->var)->length();
	return;

      case dbvmLoadTrue:
	sattr.bvalue = true;
	return;
      case dbvmLoadFalse:
	sattr.bvalue = false;
	return;
      case dbvmLoadNull:
	sattr.oid = 0;
	return;
      case dbvmLoadIntConstant:
	sattr.ivalue = expr->ivalue;
	return;
      case dbvmLoadRealConstant:
	sattr.fvalue = expr->fvalue;
	return;
      case dbvmLoadStringConstant:
	sattr.array.base = expr->svalue.str;
	sattr.array.size = expr->svalue.len;
	return;
    
      case dbvmOrBool:
	execute(expr->operand[0], iattr, sattr);
	if (sattr.bvalue == 0) { 
	    execute(expr->operand[1], iattr, sattr);
	}
	return;
      case dbvmAndBool:
	execute(expr->operand[0], iattr, sattr);
	if (sattr.bvalue != 0) { 
	    execute(expr->operand[1], iattr, sattr);
	}
	return;
      case dbvmNotBool:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = !sattr.bvalue; 
	return;

      case dbvmIsNull:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = sattr.oid == 0;
	return;

      case dbvmNegInt:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = -sattr.ivalue;
	return;
      case dbvmAddInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.ivalue += sattr2.ivalue;
	return;
      case dbvmSubInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.ivalue -= sattr2.ivalue;
	return;
      case dbvmMulInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.ivalue *= sattr2.ivalue;
	return;
      case dbvmDivInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr2.ivalue == 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, "Division by zero");
	} else { 
	    sattr.ivalue /= sattr2.ivalue;
	}
	return;
      case dbvmAndInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.ivalue &= sattr2.ivalue;
	return;
      case dbvmOrInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.ivalue |= sattr2.ivalue;
	return;
      case dbvmNotInt:
	execute(expr->operand[0], iattr, sattr);
        sattr.ivalue = ~sattr.ivalue;
	return;
      case dbvmAbsInt:
	execute(expr->operand[0], iattr, sattr);
	if (sattr.ivalue < 0) { 
	    sattr.ivalue = -sattr.ivalue;
	}
	return;
      case dbvmPowerInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr.ivalue == 2) { 
	    sattr.ivalue = sattr2.ivalue < 64 
		? (nat8)1 << (int)sattr2.ivalue : 0;
	} else if (sattr.ivalue == 0 && sattr2.ivalue < 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, 
				  "Raise zero to negative power");	    
	} else { 
	    sattr.ivalue = powerIntInt(sattr.ivalue, sattr2.ivalue);
	}
	return;

	
      case dbvmEqInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue == sattr2.ivalue;
	return;
      case dbvmNeInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue != sattr2.ivalue;
	return;
      case dbvmGtInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue > sattr2.ivalue;
	return;
      case dbvmGeInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue >= sattr2.ivalue;
	return;
      case dbvmLtInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue < sattr2.ivalue;
	return;
      case dbvmLeInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.ivalue <= sattr2.ivalue;
	return;
      case dbvmBetweenInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr.ivalue < sattr2.ivalue) { 
	    sattr.bvalue = false;
	} else { 
	    execute(expr->operand[2], iattr, sattr2);
	    sattr.bvalue = sattr.ivalue <= sattr2.ivalue;
	}
	return;

      case dbvmNegReal:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = -sattr.fvalue;
	return;
      case dbvmAddReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.fvalue += sattr2.fvalue;
	return;
      case dbvmSubReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.fvalue -= sattr2.fvalue;
	return;
      case dbvmMulReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.fvalue *= sattr2.fvalue;
	return;
      case dbvmDivReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr2.fvalue == 0.0) {
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, "Division by zero");
	} else {
	    sattr.fvalue /= sattr2.fvalue;
	}
	return;
      case dbvmAbsReal:
	execute(expr->operand[0], iattr, sattr);
	if (sattr.fvalue < 0) { 
	    sattr.fvalue = -sattr.fvalue;
	}
	return;
      case dbvmPowerReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr.fvalue < 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, 
				  "Power operator returns complex result");
	} else if (sattr.fvalue == 0.0 && sattr2.fvalue < 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, 
				  "Raise zero to negative power");	    
	} else { 
	    sattr.fvalue = pow(sattr.fvalue, sattr2.fvalue);
	}
	return;
      case dbvmPowerRealInt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr.fvalue == 0.0 && sattr2.ivalue < 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(ArithmeticError, 
				  "Raise zero to negative power");	    
	} else { 
	    sattr.fvalue = powerRealInt(sattr.fvalue, sattr2.ivalue);
	}
	return;

      case dbvmEqReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue == sattr2.fvalue;
	return;
      case dbvmNeReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue != sattr2.fvalue;
	return;
      case dbvmGtReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue > sattr2.fvalue;
	return;
      case dbvmGeReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue >= sattr2.fvalue;
	return;
      case dbvmLtReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue < sattr2.fvalue;
	return;
      case dbvmLeReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.fvalue <= sattr2.fvalue;
	return;
      case dbvmBetweenReal:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (sattr.fvalue < sattr2.fvalue) { 
	    sattr.bvalue = false;
	} else { 
	    execute(expr->operand[2], iattr, sattr2);
	    sattr.bvalue = sattr.fvalue <= sattr2.fvalue;
	}
	return;

      case dbvmIntToReal:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = (real8)sattr.ivalue;
	return;
      case dbvmRealToInt:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = (int8)sattr.fvalue;
	return;

      case dbvmIntToString:
	execute(expr->operand[0], iattr, sattr);
	convertIntToString(iattr, sattr);
	return;
      case dbvmRealToString:
	execute(expr->operand[0], iattr, sattr);
	convertRealToString(iattr, sattr);
	return;
      case dbvmStringConcat:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	concatenateStrings(iattr, sattr, sattr2);
	return;
      case dbvmUpperString:
	execute(expr->operand[0], iattr, sattr);
	uppercaseString(iattr, sattr);
	return;
      case dbvmLowerString:
	execute(expr->operand[0], iattr, sattr);
	lowercaseString(iattr, sattr);
	return;

      case dbvmEqString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) == 0;
	return;
      case dbvmNeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) != 0;
	return;
      case dbvmGtString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) > 0;
	return;
      case dbvmGeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) >= 0;
	return;
      case dbvmLtString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) < 0;
	return;
      case dbvmLeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(sattr, sattr2) <= 0;
	return;
      case dbvmLikeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = matchStrings(sattr, sattr2);
	return;
      case dbvmLikeEscapeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	execute(expr->operand[2], iattr, sattr3);
	sattr.bvalue = matchStrings(sattr, sattr2, *sattr3.array.base);
	return;
      case dbvmBetweenString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if (compareStrings(sattr, sattr2) < 0) { 
	    sattr.bvalue = false;
	} else { 
	    execute(expr->operand[2], iattr, sattr2);
	    sattr.bvalue = compareStrings(sattr, sattr2) <= 0;
	}
	return;

      case dbvmEqBool:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.bvalue == sattr2.bvalue;
	return;
      case dbvmNeBool:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.bvalue != sattr2.bvalue;
	return;

      case dbvmEqReference:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.oid == sattr2.oid;
	return;
      case dbvmNeReference:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = sattr.oid != sattr2.oid;
	return;

      case dbvmDeref:
	execute(expr->operand[0], iattr, sattr);
	if (sattr.oid == 0) { 
	    iattr.removeTemporaries();
	    iattr.db->handleError(NullReferenceError);
	}
	assert(!(iattr.db->currIndex[sattr.oid] 
		 & (dbInternalObjectMarker|dbFreeHandleMarker)));
	sattr.base = iattr.db->baseAddr + iattr.db->currIndex[sattr.oid];
	return;

      case dbvmFuncInt2Bool:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = (*(bool(*)(int8))expr->func.fptr)(sattr.ivalue);
	return;
      case dbvmFuncReal2Bool:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = (*(bool(*)(real8))expr->func.fptr)(sattr.fvalue);
	return;
      case dbvmFuncStr2Bool:
	execute(expr->operand[0], iattr, sattr);
	sattr.bvalue = 
	    (*(bool(*)(char const*))expr->func.fptr)(sattr.array.base);
	return;
      case dbvmFuncInt2Int:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = (*(int8(*)(int8))expr->func.fptr)(sattr.ivalue);
	return;
      case dbvmFuncReal2Int:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = (*(int8(*)(real8))expr->func.fptr)(sattr.fvalue);
	return;
      case dbvmFuncStr2Int:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = 
	    (*(int8(*)(char const*))expr->func.fptr)(sattr.array.base);
	return;
      case dbvmFuncInt2Real:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = (*(real8(*)(int8))expr->func.fptr)(sattr.ivalue);
	return;
      case dbvmFuncReal2Real:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = (*(real8(*)(real8))expr->func.fptr)(sattr.fvalue);
	return;
      case dbvmFuncStr2Real:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = 
	    (*(real8(*)(char const*))expr->func.fptr)(sattr.array.base);
	return;
      case dbvmFuncInt2Str:
	execute(expr->operand[0], iattr, sattr);
	copyString(iattr, sattr, 
		   (*(char*(*)(int8))expr->func.fptr)(sattr.ivalue));
	return;
      case dbvmFuncReal2Str:
	execute(expr->operand[0], iattr, sattr);
	copyString(iattr, sattr, 
		   (*(char*(*)(real8))expr->func.fptr)(sattr.fvalue));
	return;
      case dbvmFuncStr2Str:
	execute(expr->operand[0], iattr, sattr);
	copyString(iattr, sattr, 
		  (*(char*(*)(char const*))expr->func.fptr)(sattr.array.base));
	return;

      case dbvmInArrayBool:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfBool(sattr, sattr2);
	return;
      case dbvmInArrayInt1:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt1(sattr, sattr2);
	return;
      case dbvmInArrayInt2:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt2(sattr, sattr2);
	return;
      case dbvmInArrayInt4:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt4(sattr, sattr2);
	return;
      case dbvmInArrayInt8:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt8(sattr, sattr2);
	return;
      case dbvmInArrayReal4:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReal4(sattr, sattr2);
	return;
      case dbvmInArrayReal8:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReal8(sattr, sattr2);
	return;
      case dbvmInArrayString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfString(sattr, sattr2);
	return;
      case dbvmInArrayReference:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReference(sattr, sattr2);
	return;
      case dbvmInString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchInString(sattr, sattr2);
	return;

      default:
	assert(false);
    }
}


void dbDatabase::handleError(dbErrorClass error, char const* msg, int arg)
{
#ifdef THROW_EXCEPTION_ON_ERROR
    if (error != NoError) {
	throw dbException(error, msg, arg);
    }
#else
    char buf[256];
    switch (error) { 
      case QueryError:
	fprintf(stderr, "%s in position %d\n", msg, arg);
	return;
      case ArithmeticError:
	fprintf(stderr, "%s\n", msg);
	break;
      case IndexOutOfRangeError:
	fprintf(stderr, "Index %d is out of range\n", arg);
	break;
      case DatabaseOpenError:
	fprintf(stderr, "%s\n", msg);
	return;
      case FileError:
	fprintf(stderr, "%s: %s\n", msg, 
		dbFile::errorText(arg, buf, sizeof(buf)));
	break;
      case OutOfMemoryError:
	fprintf(stderr,"Not enough memory: failed to allocate %d bytes\n",arg);
	break;
      case NullReferenceError:
	fprintf(stderr, "Null object reference is accessed\n");
	break;
      case Deadlock:
	fprintf(stderr, "%s\n", msg);
	break;
      default:
	return;
    }	
    abort();
#endif
}

void dbDatabase::initializeMetaTable()
{
    static struct { 
	char const* name;
	int         type;
	int         size;
	int         offs;
    } metaTableFields[] = { 
	{ "name", dbField::tpString, sizeof(dbVarying), 
	  offsetof(dbTable, name)},
	{ "fields", dbField::tpArray, sizeof(dbVarying), 
	  offsetof(dbTable, fields)},
	{ "fields[]", dbField::tpStructure, sizeof(dbField), 0},
	{ "fields[].name", dbField::tpString, sizeof(dbVarying), 
	  offsetof(dbField, name)},
	{ "fields[].tableName",dbField::tpString,sizeof(dbVarying), 
	  offsetof(dbField, tableName)},
	{ "fields[].inverse", dbField::tpString, sizeof(dbVarying), 
	  offsetof(dbField, inverse)},
	{ "fields[].type", dbField::tpInt4, 4, offsetof(dbField, type)},
	{ "fields[].offset", dbField::tpInt4, 4, offsetof(dbField, offset)},
	{ "fields[].size", dbField::tpInt4, 4, offsetof(dbField, size)},
	{ "fields[].hashTable", dbField::tpReference, sizeof(oid_t), 
	  offsetof(dbField, hashTable)},
	{ "fields[].tTree", dbField::tpReference, sizeof(oid_t), 
	  offsetof(dbField, tTree)},
	{ "fixedSize", dbField::tpInt4, 4, offsetof(dbTable, fixedSize)},
	{ "nRows", dbField::tpInt4, 4, offsetof(dbTable, nRows)},
	{ "nColumns", dbField::tpInt4, 4, offsetof(dbTable, nColumns)}
    };

    unsigned i;
    size_t varyingSize = strlen(dbMetaTableName)+1;
    for (i = 0; i < items(metaTableFields); i++) { 
	varyingSize += strlen(metaTableFields[i].name) + 3;
	
    }
    offs_t metaTableOffs = allocate(sizeof(dbTable)
				    + sizeof(dbField)*items(metaTableFields)
				    + varyingSize);
    index[0][dbMetaTableId] = metaTableOffs;
    dbTable* table = (dbTable*)(baseAddr + metaTableOffs);
    table->size = sizeof(dbTable) + sizeof(dbField)*items(metaTableFields)
	        + varyingSize;
    table->next = table->prev = 0;
    int offs = sizeof(dbTable) + sizeof(dbField)*items(metaTableFields);
    table->name.offs = offs;
    table->name.size = strlen(dbMetaTableName)+1;
    strcpy((char*)table + offs, dbMetaTableName);
    offs += table->name.size;
    table->fields.offs = sizeof(dbTable);
    table->fields.size = items(metaTableFields);
    table->fixedSize = sizeof(dbTable);
    table->nRows = 0;
    table->nColumns = 5;
    table->firstRow = 0;
    table->lastRow = 0;

    dbField* field = (dbField*)((char*)table + table->fields.offs);
    offs -= sizeof(dbTable);
    for (i = 0; i < items(metaTableFields); i++) { 
	field->name.offs = offs;
	field->name.size = strlen(metaTableFields[i].name) + 1;
	strcpy((char*)field + offs, metaTableFields[i].name);
	offs += field->name.size;

	field->tableName.offs = offs;
	field->tableName.size = 1;
        *((char*)field + offs++) = '\0';
	
	field->inverse.offs = offs;
	field->inverse.size = 1;
	*((char*)field + offs++) = '\0';
	
	field->type = metaTableFields[i].type;
	field->size = metaTableFields[i].size;
	field->offset = metaTableFields[i].offs;
	field->hashTable = 0;
	field->tTree = 0;
	field += 1;
	offs -= sizeof(dbField);
    }
}

bool dbDatabase::open(char const* dbName, char const* fiName, unsigned waitLockTimeout)
{
    dbWaitLockTimeout = waitLockTimeout;
    delete[] databaseName;
    delete[] fileName;
    opened = false;
    databaseNameLen = strlen(dbName);
    char* name = new char[databaseNameLen+16];
    sprintf(name, "%s.in", dbName);
    databaseName = name;
    if (fiName == NULL) { 
	fileName = new char[databaseNameLen + 5];
	sprintf(fileName, "%s.fdb", dbName);
    } else { 
	fileName = new char[strlen(fiName)+1];
	strcpy(fileName, fiName);
    }

    dbInitializationMutex::initializationStatus status;
    status = initMutex.initialize(name);
    if (status == dbInitializationMutex::InitializationError) { 
	handleError(DatabaseOpenError, 
		    "Failed to start database initialization");
	return false;
    }
    sprintf(name, "%s.dm", dbName);
    if (!shm.open(name)) { 
	handleError(DatabaseOpenError, "Failed to open database monitor");
	return false;
    }
    monitor = shm.get();
    sprintf(name, "%s.ws", dbName);
    if (!writeSem.open(name)) { 
	handleError(DatabaseOpenError, 
		    "Failed to initialize database writers semaphore");
	return false;
    }
    sprintf(name, "%s.rs", dbName);
    if (!readSem.open(name)) { 
	handleError(DatabaseOpenError, 
		    "Failed to initialize database readers semaphore");
	return false;
    }
    sprintf(name, "%s.us", dbName);
    if (!upgradeSem.open(name)) { 
	handleError(DatabaseOpenError, 
		    "Failed to initialize database upgrade semaphore");
	return false;
    }
    sprintf(name, "%s.bce", dbName);
    if (!backupCompletedEvent.open(name)) { 
	handleError(DatabaseOpenError, 
		    "Failed to initialize database backup completed event");
	return false;
    }    
    allocatedSize = 0;
    size_t indexSize = initIndexSize < dbFirstUserId 
	? size_t(dbFirstUserId) : initIndexSize;
    indexSize = DOALIGN(indexSize, dbHandlesPerPage);
	    
    size_t fileSize = initSize ? initSize : dbDefaultInitDatabaseSize;
    fileSize = DOALIGN(fileSize, dbBitmapSegmentSize);

    if (fileSize < indexSize*sizeof(offs_t)*4) {
	fileSize = indexSize*sizeof(offs_t)*4;
    }

    for (int i = dbBitmapId + dbBitmapPages; --i >= 0;) { 
	bitmapPageAvailableSpace[i] = INT_MAX;
    }
    currBitmapPage = dbBitmapId;
    currBitmapOffs = 0;
    inAllocator = 0;
    tables = NULL;
    modified = false;
    concurrentTransId = 1;
    attach();

    if (status == dbInitializationMutex::NotYetInitialized) { 
	sprintf(name, "%s.cs", dbName);
	if (!cs.create(name, &monitor->sem)) { 
	    handleError(DatabaseOpenError,
			"Failed to initialize database monitor");
	    return false;
	}
	readSem.reset();
	writeSem.reset();
	upgradeSem.reset();
	monitor->nReaders = 0;
	monitor->nWriters = 0;
	monitor->nWaitReaders = 0;
	monitor->nWaitWriters = 0;
	monitor->waitForUpgrade = false;
	monitor->version = version = 1;
	monitor->users = 0;
	monitor->backupInProgress = 0;
	monitor->lastDeadlockRecoveryTime = 0;
	memset(monitor->dirtyPagesMap, 0, dbDirtyPageBitmapSize);
    
	sprintf(databaseName, "%s.%d", dbName, version);
	if (file.open(fileName, databaseName, 
		      accessType == dbReadOnly, fileSize) != dbFile::ok)
	{
	    handleError(DatabaseOpenError, "Failed to create database file");
	    return false;
	}
	baseAddr = (byte*)file.getAddr();
	fileSize = file.getSize();
	header = (dbHeader*)baseAddr;

	if ((unsigned)header->curr > 1) { 
	    handleError(DatabaseOpenError, "Database file was corrupted: "
			"invalid root index");
	    return false;
	}
	if (!header->initialized) {
	    if (accessType == dbReadOnly) { 
		handleError(DatabaseOpenError, "Can not open uninitialized "
			    "file in read only moode");
		return false;
	    }
	    header->curr = 0;
	    header->size = fileSize;
	    size_t used = dbPageSize;
	    header->root[0].index = used;
	    header->root[0].indexSize = indexSize;
	    header->root[0].indexUsed = dbFirstUserId;
	    header->root[0].freeList = 0;
	    used += indexSize*sizeof(offs_t);
	    header->root[1].index = used;
	    header->root[1].indexSize = indexSize;
	    header->root[1].indexUsed = dbFirstUserId;
	    header->root[1].freeList = 0;
	    used += indexSize*sizeof(offs_t);

	    header->root[0].shadowIndex = header->root[1].index;
	    header->root[1].shadowIndex = header->root[0].index;
	    header->root[0].shadowIndexSize = indexSize;
	    header->root[1].shadowIndexSize = indexSize;
	    
	    index[0] = (offs_t*)(baseAddr + header->root[0].index);
	    index[1] = (offs_t*)(baseAddr + header->root[1].index);
	    index[0][dbInvalidId] = dbFreeHandleMarker;

	    size_t bitmapPages = 
		(used + dbPageSize*(dbAllocationQuantum*8-1) - 1)
		/ (dbPageSize*(dbAllocationQuantum*8-1));
	    memset(baseAddr+used, 0xFF, (used + bitmapPages*dbPageSize)
		                        / (dbAllocationQuantum*8));
	    size_t i;
	    for (i = 0; i < bitmapPages; i++) { 
		index[0][dbBitmapId + i] = used + dbPageObjectMarker;
		used += dbPageSize;
	    }
	    while (i < dbBitmapPages) { 
		index[0][dbBitmapId+i] = dbFreeHandleMarker;
		i += 1;
	    }
	    currIndex = index[0];
	    currIndexSize = dbFirstUserId;
	    committedIndexSize = 0;
	    initializeMetaTable();
	    header->dirty = true;
	    memcpy(index[1], index[0], currIndexSize*sizeof(offs_t));
	    file.markAsDirty(0, used);
	    file.flush();
	    header->initialized = true;
	    file.markAsDirty(0, sizeof(dbHeader));
	    file.flush();
	} else {
	    if (header->dirty) { 
		TRACE_MSG(("Database was not normally closed: "
			   "start recovery\n"));
		if (accessType == dbReadOnly) { 
		    handleError(DatabaseOpenError,
				"Can not open dirty file in read only moode");
		    return false;
		}
		recovery();
		TRACE_MSG(("Recovery completed\n"));
	    } else { 
		if (file.getSize() != header->size) { 
		    handleError(DatabaseOpenError, "Database file was "
				"corrupted: file size in header differs "
				"from actual file size");
		    return false;
		}
	    }	    
	}
	if (!loadScheme(true)) { 
	    return false;
	}
	initMutex.done();
    } else { 
	sprintf(name, "%s.cs", dbName);
	if (!cs.open(name, &monitor->sem)) { 
	    handleError(DatabaseOpenError, "Failed to open shared semaphore");
	    return false;
	}
	version = 0;
	if (!loadScheme(false)) { 
	    return false;
	}
    }
    monitor->users += 1;
    opened = true;
    return true;
}

void dbDatabase::recovery()
{
    int curr = header->curr;
    header->size = file.getSize();
    header->root[1-curr].indexUsed = header->root[curr].indexUsed; 
    header->root[1-curr].freeList = header->root[curr].freeList; 
    header->root[1-curr].index = header->root[curr].shadowIndex;
    header->root[1-curr].indexSize = 
	header->root[curr].shadowIndexSize;
    header->root[1-curr].shadowIndex = header->root[curr].index;
    header->root[1-curr].shadowIndexSize = 
	header->root[curr].indexSize;
    
    offs_t* dst = (offs_t*)(baseAddr+header->root[1-curr].index);
    offs_t* src = (offs_t*)(baseAddr+header->root[curr].index);
    currIndex = dst;
    for (int n = header->root[curr].indexUsed; --n >= 0;) { 
	if (*dst != *src) { 
	    *dst = *src;
	}
	dst += 1;
	src += 1;
    }
    //
    // Restore consistency of table rows l2-list 
    //
    dbTable* table = (dbTable*)getRow(dbMetaTableId);
    oid_t lastId = table->lastRow;
    if (lastId != 0) { 
	dbRecord* record = getRow(lastId);
	if (record->next != 0) { 
	    record->next = 0;
	}
    }
    oid_t tableId = table->firstRow;
    while (tableId != 0) { 
	table = (dbTable*)getRow(tableId);
	lastId = table->lastRow;
	if (lastId != 0) { 
	    dbRecord* record = getRow(lastId);
	    if (record->next != 0) { 
		record->next = 0;
	    }
	}
	tableId = table->next;
    }
    memset(monitor->dirtyPagesMap, 0, dbDirtyPageBitmapSize);
}

void dbDatabase::setConcurrency(unsigned nThreads)
{
    if (nThreads == 0) { // autodetect number of processors
	nThreads = dbThread::numberOfProcessors();
    } 
    if (nThreads > dbMaxParallelSearchThreads) { 
	nThreads = dbMaxParallelSearchThreads;
    }
    parThreads = nThreads;
}


bool dbDatabase::loadScheme(bool alter) 
{
    if (!beginTransaction(accessType != dbReadOnly)) { 
	return false;
    }

    dbTableDescriptor *desc, *next;
    dbTable* metaTable = (dbTable*)getRow(dbMetaTableId);
    oid_t first = metaTable->firstRow;
    oid_t last = metaTable->lastRow;
    int nTables = metaTable->nRows;
    oid_t tableId = first;

    for (desc = dbTableDescriptor::chain; desc != NULL; desc = next) {
	next = desc->next;
	if (desc->db != NULL && desc->db != DETACHED_TABLE && desc->db != this) { 
	    continue;
	}
	if (desc->db == DETACHED_TABLE) {
	    desc = desc->clone();
	}
	dbFieldDescriptor* fd;
	for (fd = desc->firstField; fd != NULL; fd = fd->nextField) {
	    fd->tTree = 0;
	    fd->hashTable = 0;
	    fd->attr &= ~dbFieldDescriptor::Updated;
	}

	int n = nTables;
	while (--n >= 0) {
	    dbTable* table = (dbTable*)getRow(tableId);
	    oid_t next = table->next;
	    if (strcmp(desc->name, (char*)table + table->name.offs) == 0) {
		if (!desc->equal(table)) { 
		    if (!alter) { 
			handleError(DatabaseOpenError, "Incompatible class"
				    " definition in application");
			return false;
		    }
		    modified = true;
		    if (table->nRows == 0) { 
			TRACE_MSG(("Replace definition of table '%s'\n", 
				   desc->name));
			updateTableDescriptor(desc, tableId);
		    } else { 
			reformatTable(tableId, desc);
		    } 
		} else { 
		    linkTable(desc, tableId);
		}
		desc->setFlags();
		break;
	    }
	    if (tableId == last) {
		tableId = first;
	    } else { 
		tableId = next;
	    }
	}
	if (n < 0) { // no match found
	    if (accessType == dbReadOnly) { 
		handleError(DatabaseOpenError, "New table definition can not "
			    "be added to read only database");
		return false;
	    } else {     
		TRACE_MSG(("Create new table '%s' in database\n", desc->name));
		addNewTable(desc);
		modified = true;
	    }
	}
	if (accessType != dbReadOnly) { 
	    if (!addIndices(alter, desc)) { 
		handleError(DatabaseOpenError, "Failed to alter indices with"
			    " active applications");
		rollback();
		return false;
	    }
	}
    }	
    for (desc = tables; desc != NULL; desc = desc->nextDbTable) {
	if (desc->cloneOf != NULL) {
	    for (dbFieldDescriptor *fd = desc->firstField; fd != NULL; fd = fd->nextField)
	    {
		if (fd->refTable != NULL) {
		    fd->refTable = lookupTable(fd->refTable);
		}
	    }
	}
	desc->checkRelationship();
    }
    commit();
    return true;
} 


void dbDatabase::reformatTable(oid_t tableId, dbTableDescriptor* desc)
{
    dbTable* table = (dbTable*)putRow(tableId);

    if (desc->match(table)) { 
	TRACE_MSG(("New version of table '%s' is compatible with old one\n", 
		   desc->name));
	updateTableDescriptor(desc, tableId);
    } else { 
	TRACE_MSG(("Reformat table '%s'\n", desc->name));
	oid_t oid = table->firstRow;
	updateTableDescriptor(desc, tableId);
	while (oid != 0) { 
	    dbRecord* record = getRow(oid);
	    size_t size = 
		desc->columns->calculateNewRecordSize((byte*)record, 
						     desc->fixedSize);
	    offs_t offs = currIndex[oid];
	    record = putRow(oid, size);
	    byte* dst = (byte*)record;
	    byte* src = baseAddr + offs;
	    desc->columns->convertRecord(dst, src, desc->fixedSize);
	    oid = record->next;
	}
    }
}
 
void dbDatabase::deleteTable(dbTableDescriptor* desc)
{
    beginTransaction(true);
    modified = true;
    dbTable* table = (dbTable*)putRow(desc->tableId);
    oid_t rowId = table->firstRow;
    table->firstRow = table->lastRow = 0;
    table->nRows = 0;
	
    while (rowId != 0) {
	dbRecord* record = getRow(rowId);
	oid_t nextId = record->next;
	size_t size = record->size;
	
	removeInverseReferences(desc, rowId);

	if (rowId < committedIndexSize && index[0][rowId] == index[1][rowId]) {
	    cloneBitmap(currIndex[rowId], size);
	} else { 
	    free(currIndex[rowId], size);
	}
	freeId(rowId);
	rowId = nextId;
    }
    dbFieldDescriptor* fd;
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) { 
	dbHashTable::purge(this, fd->hashTable);
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbTtree::purge(this, fd->tTree);
    } 
} 

void dbDatabase::dropHashTable(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbHashTable::drop(this, fd->hashTable);
    fd->hashTable = 0;
    fd->indexType &= ~HASHED;

    dbFieldDescriptor** fpp = &fd->defTable->hashedFields;
    while (*fpp != fd) { 
	fpp = &(*fpp)->nextHashedField;
    }
    *fpp = fd->nextHashedField;

    dbTable* table = (dbTable*)putRow(fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].hashTable = 0;
}

void dbDatabase::dropIndex(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbTtree::drop(this, fd->tTree);
    fd->tTree = 0;
    fd->indexType &= ~INDEXED;

    dbFieldDescriptor** fpp = &fd->defTable->indexedFields;
    while (*fpp != fd) { 
	fpp = &(*fpp)->nextIndexedField;
    }
    *fpp = fd->nextIndexedField;

    dbTable* table = (dbTable*)putRow(fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].tTree = 0;
}

void dbDatabase::createHashTable(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbTable* table = (dbTable*)getRow(fd->defTable->tableId);
    int nRows = table->nRows;
    fd->hashTable = dbHashTable::allocate(this, 2*nRows);
    fd->attr &= ~dbFieldDescriptor::Updated;
    fd->nextHashedField = fd->defTable->hashedFields;
    fd->defTable->hashedFields = fd;
    fd->indexType |= HASHED;
    table = (dbTable*)putRow(fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].hashTable = fd->hashTable;

    for (oid_t oid = table->firstRow; oid != 0; oid = getRow(oid)->next) {
	dbHashTable::insert(this, fd->hashTable, oid, fd->type, fd->dbsOffs,
			    nRows);
    }
}


void dbDatabase::createIndex(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    fd->tTree = dbTtree::allocate(this); 
    fd->attr &= ~dbFieldDescriptor::Updated;
    fd->nextIndexedField = fd->defTable->indexedFields;
    fd->defTable->indexedFields = fd;
    fd->indexType |= INDEXED;
    dbTable* table = (dbTable*)putRow(fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].tTree = fd->tTree;
    
    for (oid_t oid = table->firstRow; oid != 0; oid = getRow(oid)->next) {
	dbTtree::insert(this, fd->tTree, oid, fd->type, fd->dbsOffs);
    }
}

void dbDatabase::dropTable(dbTableDescriptor* desc)
{
    deleteTable(desc);
    freeRow(dbMetaTableId, desc->tableId);

    dbFieldDescriptor* fd;
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) { 
	dbHashTable::drop(this, fd->hashTable);
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbTtree::drop(this, fd->tTree);
    } 
}


bool dbDatabase::addIndices(bool alter, dbTableDescriptor* desc)
{
    dbFieldDescriptor* fd;
    oid_t tableId = desc->tableId;
    dbTable* table = (dbTable*)getRow(tableId);
    int nRows = table->nRows;
    oid_t firstId = table->firstRow;
    int nNewIndices = 0;
    int nDelIndices = 0;
    for (fd = desc->firstField; fd != NULL; fd = fd->nextField) { 
	if ((fd->indexType & HASHED) && fd->type != dbField::tpStructure) { 
	    if (fd->hashTable == 0) { 
		if (!alter && tableId < committedIndexSize
		    && index[0][tableId] == index[1][tableId])
		{
		    // If there are some other active applications which 
		    // can use this table, then they will not know
		    // about newly created index, which leads to inconsistency
		    return false;
		}
		fd->hashTable = dbHashTable::allocate(this, nRows);
		nNewIndices += 1;
		TRACE_MSG(("Create hash table for field '%s'\n", fd->name));
	    }
	} else if (fd->hashTable != 0) { 
	    if (alter) { 
		TRACE_MSG(("Remove hash table for field '%s'\n", fd->name));
		nDelIndices += 1;
		fd->hashTable = 0;
	    } else { 
		return false;
	    }
	}
	if ((fd->indexType & INDEXED) && fd->type != dbField::tpStructure) { 
	    if (fd->tTree == 0) { 
		if (!alter && tableId < committedIndexSize
		    && index[0][tableId] == index[1][tableId])
		{
		    return false;
		}
		fd->tTree = dbTtree::allocate(this);
		nNewIndices += 1;
		TRACE_MSG(("Create index for field '%s'\n", fd->name));
	    }
	} else if (fd->tTree != 0) { 
	    if (alter) { 
		nDelIndices += 1;
		TRACE_MSG(("Remove index for field '%s'\n", fd->name));
		fd->tTree = 0;
	    } else { 
		return false;
	    }
	}
    }
    if (nNewIndices > 0) { 
	modified = true;
	for (oid_t rowId = firstId; rowId != 0; rowId = getRow(rowId)->next) {
	    for (fd = desc->hashedFields; fd != NULL; fd=fd->nextHashedField) {
		if (fd->hashTable >= committedIndexSize 
		    || index[0][fd->hashTable] != index[1][fd->hashTable]) 
		{ 
		    dbHashTable::insert(this, fd->hashTable, rowId, 
					fd->type, fd->dbsOffs, 2*nRows);
		}
	    }
	    for (fd=desc->indexedFields; fd != NULL; fd=fd->nextIndexedField) {
		if (fd->tTree >= committedIndexSize 
		    || index[0][fd->tTree] != index[1][fd->tTree]) 
		{ 
		    dbTtree::insert(this, fd->tTree, rowId, 
				    fd->type, fd->dbsOffs);
		}
	    }
	} 
    }
    if (nNewIndices + nDelIndices != 0) { 
	table = (dbTable*)putRow(tableId);
	offs_t fieldOffs = currIndex[tableId] + table->fields.offs;
	for (fd = desc->firstField; fd != NULL; fd = fd->nextField) { 
	    dbField* field = (dbField*)(baseAddr + fieldOffs);    
	    if (field->hashTable != fd->hashTable) { 
		if (field->hashTable != 0) { 
		    assert(fd->hashTable == 0);
		    modified = true;
		    dbHashTable::drop(this, field->hashTable);
		    field = (dbField*)(baseAddr + fieldOffs);
		}
		field->hashTable = fd->hashTable;
	    }
	    if (field->tTree != fd->tTree) { 
		if (field->tTree != 0) { 
		    assert(fd->tTree == 0);
		    modified = true;
		    dbTtree::drop(this, field->tTree);
		    field = (dbField*)(baseAddr + fieldOffs);
		}
		field->tTree = fd->tTree;
	    }
	    fieldOffs += sizeof(dbField);
	}
    }
    return true;
}

 
void dbDatabase::updateTableDescriptor(dbTableDescriptor* desc, oid_t tableId)
{
    size_t newSize = sizeof(dbTable) + desc->nFields*sizeof(dbField)
	+ desc->totalNamesLength();
    linkTable(desc, tableId);

    dbTable* table = (dbTable*)getRow(tableId);
    int   nRows = table->nRows;
    oid_t first = table->firstRow;
    oid_t last = table->lastRow;

    int nFields = table->fields.size;
    offs_t fieldOffs = currIndex[tableId] + table->fields.offs;

    while (--nFields >= 0) { 
	dbField* field = (dbField*)(baseAddr + fieldOffs);
	fieldOffs += sizeof(dbField);

	oid_t hashTableId = field->hashTable;
	oid_t tTreeId = field->tTree;
	if (hashTableId != 0) { 
	    dbHashTable::drop(this, hashTableId);
	} 
	if (tTreeId != 0) { 
	    dbTtree::drop(this, tTreeId);
	}
    } 

    table = (dbTable*)putRow(tableId, newSize);
    desc->storeInDatabase(table);
    table->firstRow = first;
    table->lastRow = last;
    table->nRows = nRows;
}

oid_t dbDatabase::addNewTable(dbTableDescriptor* desc)
{
    oid_t tableId = allocateRow(dbMetaTableId, 
				sizeof(dbTable) + desc->nFields*sizeof(dbField)
				+ desc->totalNamesLength());
    linkTable(desc, tableId);
    desc->storeInDatabase((dbTable*)getRow(tableId));
    return tableId;
}

void dbDatabase::close()
{
    detach();
    delete[] databaseName;
    delete[] fileName;
    databaseName = NULL;
    fileName = NULL;
    opened = false;
    monitor->users -= 1;
    if (header->dirty) { 
	file.flush();
	header->dirty = false;
	file.markAsDirty(0, sizeof(dbHeader));
    }
     dbTableDescriptor *desc, *next;
     for (desc = tables; desc != NULL; desc = next) {
	 next = desc->nextDbTable;
	 desc->tableId = 0;
	 if (desc->cloneOf != NULL) {
	     delete desc;
	 } else if (!desc->fixedDatabase) {
	     desc->db = NULL;
	 }
    }

    file.close();
    if (initMutex.close()) { 
	cs.erase();
	shm.erase();
	readSem.erase();
	writeSem.erase();
	upgradeSem.erase();
	backupCompletedEvent.erase();
	initMutex.erase();
    } else { 
	cs.close();
	shm.close();
	readSem.close();
	writeSem.close();
	upgradeSem.close();
	backupCompletedEvent.close();
    }
}

dbTableDescriptor* dbDatabase::lookupTable(dbTableDescriptor* origDesc)
{
    for (dbTableDescriptor* desc = tables; desc != NULL; desc = desc->nextDbTable) 
    {
	if (desc->cloneOf == origDesc) {
	    return desc;
	}
    }
    return NULL;
}


void dbDatabase::attach() 
{
    if (threadContext.get() == NULL) { 
	threadContext.set(new dbDatabaseThreadContext);
    }
}

void dbDatabase::detach() 
{
    commit();
    dbDatabaseThreadContext* ctx = threadContext.get();
    delete ctx;
    threadContext.set(NULL);
}

bool dbDatabase::existsInverseReference(dbExprNode* expr, int nExistsClauses)
{
    while (true) { 
	switch (expr->cop) { 
	  case dbvmLoadSelfReference:
	  case dbvmLoadSelfArray:
	    return expr->ref.field->inverseRef != NULL;
	  case dbvmLoadReference:
	    if (expr->ref.field->attr & dbFieldDescriptor::ComponentOfArray) { 
		expr = expr->ref.base;
		continue;
	    }
	    // no break
	  case dbvmLoadArray:
	    if (expr->ref.field->inverseRef == NULL) { 
		return false;
	    }
	    expr = expr->ref.base;
	    continue; 
	  case dbvmGetAt:
	    if (expr->operand[1]->cop != dbvmVariable 
		|| expr->operand[1]->offs != --nExistsClauses) 
	    {
		return false;
	    }
	    expr = expr->operand[0];
	    continue;
	  case dbvmDeref:
	    expr = expr->operand[0];
	    continue;	    
	  default:
	    return false;
	}
    }
}

bool dbDatabase::followInverseReference(dbExprNode* expr, dbExprNode* andExpr, 
					dbAnyCursor* cursor, oid_t iref)
{
    while (expr->cop == dbvmGetAt || expr->cop == dbvmDeref ||
	   (expr->cop == dbvmLoadReference 
	    && (expr->ref.field->attr & dbFieldDescriptor::ComponentOfArray))) 
    { 
	expr = expr->operand[0]; 	
    } 
    dbTable* table = (dbTable*)getRow(cursor->table->tableId);
    dbFieldDescriptor* fd = expr->ref.field->inverseRef;
    if (fd->type == dbField::tpArray) { 
	byte* rec = (byte*)getRow(iref);
	dbVarying* arr = (dbVarying*)(rec + fd->dbsOffs);
	oid_t* refs = (oid_t*)(rec + arr->offs);
	if (expr->cop >= dbvmLoadSelfReference) {
	    for (int n = arr->size; --n >= 0;) { 
		oid_t oid = *refs++;
		if (oid != 0) { 
		    if (andExpr == NULL || evaluate(andExpr, oid, table)) { 
			if (!cursor->add(oid)) { 
			    return false;
			}
		    }
		}
	    }
	} else { 
	    for (int n = arr->size; --n >= 0;) { 
		oid_t oid = *refs++;
		if (oid != 0) { 
		    if (!followInverseReference(expr->ref.base, andExpr,
						cursor, oid))
		    {
			return false;
		    }
		}
	    }
	}
    } else { 
	assert(fd->type == dbField::tpReference);
	oid_t oid = *(oid_t*)((byte*)getRow(iref) + fd->dbsOffs);
	if (oid != 0) { 
	    if (expr->cop >= dbvmLoadSelfReference) {
		if (andExpr == NULL || evaluate(andExpr, oid, table)) { 
		    if (!cursor->add(oid)) { 
			return false;
		    }
		}
	    } else { 
		if (!followInverseReference(expr->ref.base, andExpr, 
					    cursor, oid)) 
		{
		    return false;
		}
	    }
	}
    }
    return true;
}
    

bool dbDatabase::isIndexApplicable(dbAnyCursor* cursor, 
				   dbExprNode* expr, dbExprNode* andExpr,
				   dbFieldDescriptor* &indexedField)
{
    int nExistsClauses = 0;
    while (expr->cop == dbvmExists) { 
	expr = expr->operand[0];
	nExistsClauses += 1;
    }
    int cmpCop = expr->cop;

    if (dbExprNode::nodeOperands[cmpCop] < 2) { 
	return false;
    }
    unsigned loadCop = expr->operand[0]->cop;

    if (loadCop - dbvmLoadSelfBool > dbvmLoadSelfReference - dbvmLoadSelfBool
	&& loadCop - dbvmLoadBool > dbvmLoadReference - dbvmLoadBool)
    {
	return false;
    }
    dbFieldDescriptor* field = expr->operand[0]->ref.field;
    if (field->hashTable == 0 && field->tTree == 0) { 
	return false;
    }
    if (loadCop >= dbvmLoadSelfBool) { 
	if (isIndexApplicable(cursor, expr, andExpr)) { 
	    indexedField = field;
	    return true;
	}
    } 
    else if (existsInverseReference(expr->operand[0]->ref.base, nExistsClauses))
    { 
	dbAnyCursor tmpCursor(*field->defTable, dbCursorViewOnly, NULL);
	if (isIndexApplicable(&tmpCursor, expr, NULL)) { 
	    expr = expr->operand[0]->ref.base;
	    indexedField = field;
	    cursor->checkForDuplicates();
	    if (andExpr != NULL) { 
		andExpr = andExpr->operand[1];
	    }
	    for (dbSelection::segment* curr = tmpCursor.selection.first; 
		 curr != NULL; 
		 curr = curr->next)
	    { 
		for (int i = 0, n = curr->nRows; i < n; i++) { 
		    if (!followInverseReference(expr, andExpr,  
						cursor, curr->rows[i]))
		    {
			return true;
		    }
		} 
	    }
	    return true;
	}
    } else if (expr->operand[0]->ref.base->cop == dbvmDeref) { 
	dbExprNode* ref = expr->operand[0]->ref.base->operand[0];
	if (ref->cop == dbvmLoadSelfReference) { 
	    dbFieldDescriptor* refField = ref->ref.field;
	    if (refField->hashTable == 0 && refField->tTree == 0) { 
		return false;
	    }
	    assert(refField->type == dbField::tpReference);
	    dbAnyCursor tmpCursor(*refField->defTable, dbCursorViewOnly, NULL);
	    if (isIndexApplicable(&tmpCursor, expr, NULL)) { 
		oid_t oid;
		indexedField = refField;
		dbSearchContext sc;
		sc.db = this;
		sc.type = dbField::tpReference;
		sc.offs = refField->dbsOffs;
		sc.cursor = cursor;
		sc.condition = andExpr ? andExpr->operand[1] : (dbExprNode*)0;
		sc.firstKey = sc.lastKey = (char*)&oid;
		sc.firstKeyInclusion = sc.lastKeyInclusion = true;
		for (dbSelection::segment* curr = tmpCursor.selection.first; 
		     curr != NULL; 
		     curr = curr->next)
		{ 
		    for (int i = 0, n = curr->nRows; i < n; i++) { 
			oid = curr->rows[i];
			sc.probes = 0;
			if (refField->hashTable != 0) { 
			    dbHashTable::find(this, refField->hashTable, sc);
			    TRACE_MSG(("Hash table search for field %s.%s: %d probes\n", 
				       refField->defTable->name, refField->longName, sc.probes)); 
			} else { 
			    dbTtree::find(this, refField->tTree, sc);
			    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
				       refField->defTable->name, refField->longName, sc.probes)); 
			}
		    }
		}
		return true;
	    }
	}
    }
    return false;
}

inline char* findWildcard(char* pattern, char* escape) 
{
    if (escape == NULL) { 
	while (*pattern != dbMatchAnyOneChar &&
	       *pattern != dbMatchAnySubstring)
	{
	    if (*pattern++ == '\0') { 
		return NULL;
	    }
	}
    } else { 
	char esc = *escape;
	while (*pattern != dbMatchAnyOneChar &&
	       *pattern != dbMatchAnySubstring &&
	       *pattern != esc)
	{
	    if (*pattern++ == '\0') { 
		return NULL;
	    }
	}
    }
    return pattern;
}
	

bool dbDatabase::isIndexApplicable(dbAnyCursor* cursor, 
				   dbExprNode* expr, dbExprNode* andExpr)
{
    int n = dbExprNode::nodeOperands[expr->cop];
    dbFieldDescriptor* field = expr->operand[0]->ref.field;
    dbSearchContext sc;

    union { 
	bool  b;
	int1  i1;
	int2  i2;
	int4  i4;
	int8  i8;
	real4 f4;
	real8 f8;
	oid_t oid;
	char* s;
    } literal[2];

    bool strop = false;
    char* s;
    literal[0].i8 = 0;
    literal[1].i8 = 0;

    for (int i = 0; i < n-1; i++) { 
	bool  bval = false;
	int8  ival = 0;
	real8 fval = 0;
	oid_t oid = 0;
	char* sval = NULL;
	dbExprNode* opd = expr->operand[i+1];
	switch (opd->cop) {  
	  case dbvmLoadVarBool:
	    bval = *(bool*)opd->var;
	    break;
	  case dbvmLoadVarInt1:
	    ival = *(int1*)opd->var;
	    break;
	  case dbvmLoadVarInt2:
	    ival = *(int2*)opd->var;
	    break;
	  case dbvmLoadVarInt4:
	    ival = *(int4*)opd->var;
	    break;
	  case dbvmLoadVarInt8:
	    ival = *(int8*)opd->var;
	    break;
	  case dbvmLoadVarReference:
	    oid = *(oid_t*)opd->var;
	    break;
	  case dbvmLoadVarReal4:
	    fval = *(real4*)opd->var;
	    break;
	  case dbvmLoadVarReal8:
	    fval = *(real8*)opd->var;
	    break;
	  case dbvmLoadVarString:
	    sval = (char*)opd->var;
	    strop = true;
	    break;
	  case dbvmLoadVarStringPtr:
	    sval = *(char**)opd->var;
	    strop = true;
	    break;
	  case dbvmLoadTrue:
	    bval = true;
	    break;
	  case dbvmLoadFalse:
	    bval = false;
	    break;
	  case dbvmLoadIntConstant:
	    ival = opd->ivalue;
	    break;
	  case dbvmLoadRealConstant:
	    fval = opd->fvalue;
	    break;
	  case dbvmLoadStringConstant:
	    sval = (char*)opd->svalue.str;
	    strop = true;
	    break;
	  default:
	    return false;
	} 
	switch (field->type) { 
	  case dbField::tpBool:
	    literal[i].b = bval;
	    break;
	  case dbField::tpInt1:
	    literal[i].i1 = (int1)ival;
	    break;
	  case dbField::tpInt2:
	    literal[i].i2 = (int2)ival;
	    break;
	  case dbField::tpInt4:
	    literal[i].i4 = (int4)ival;
	    break;
	  case dbField::tpInt8:
	    literal[i].i8 = ival;
	    break;
	  case dbField::tpReference:
	    literal[i].oid = oid;
	    break;
	  case dbField::tpReal4:
 	    literal[i].f4 = (real4)fval;
	    break;
	  case dbField::tpReal8:
	    literal[i].f8 = fval;
	    break;
	  case dbField::tpString:
	    literal[i].s = sval;
	    break;
	  default:
	    assert(false);
	}
    }
    sc.db = this;
    sc.type = field->type;
    sc.offs = field->dbsOffs;
    sc.cursor = cursor;
    sc.condition = andExpr ? andExpr->operand[1] : (dbExprNode*)0;
    sc.probes = 0;

    switch (expr->cop) { 
      case dbvmEqReference:
      case dbvmEqInt:
      case dbvmEqReal:
      case dbvmEqString:
	sc.firstKey = sc.lastKey = 
	    strop ? literal[0].s : (char*)&literal[0];
	sc.firstKeyInclusion = sc.lastKeyInclusion = true;
	if (field->hashTable != 0) { 
	    dbHashTable::find(this, field->hashTable, sc);
	    TRACE_MSG(("Hash table search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	} else { 
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	}
	return true;
      case dbvmGtInt:
      case dbvmGtReal:
      case dbvmGtString:
	if (field->tTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKey = NULL;
	    sc.firstKeyInclusion = false;
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmGeInt:
      case dbvmGeReal:
      case dbvmGeString:
	if (field->tTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKey = NULL;
	    sc.firstKeyInclusion = true;
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLtInt:
      case dbvmLtReal:
      case dbvmLtString:
	if (field->tTree != 0) {
	    sc.firstKey = NULL;
	    sc.lastKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKeyInclusion = false;
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLeInt:
      case dbvmLeReal:
      case dbvmLeString:
	if (field->tTree != 0) {
	    sc.firstKey = NULL;
	    sc.lastKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKeyInclusion = true;
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmBetweenInt:
      case dbvmBetweenReal:
      case dbvmBetweenString:
	if (field->hashTable != 0 &&
	    ((strop && strcmp(literal[0].s, literal[1].s) == 0)
	     || (!strop && literal[0].i8 == literal[1].i8)))
	{
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    dbHashTable::find(this, field->hashTable, sc);
	    TRACE_MSG(("Hash table search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} else if (field->tTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.firstKeyInclusion = true;
	    sc.lastKey = strop ? literal[1].s : (char*)&literal[1];
	    sc.lastKeyInclusion = true;
	    dbTtree::find(this, field->tTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLikeString:
      case dbvmLikeEscapeString:
	if ((s = findWildcard(literal[0].s, literal[1].s)) == NULL 
	    || ((s[1] == '\0' || s != literal[0].s) && field->tTree != 0))
	{
	    if (s == NULL) { 
		sc.firstKey = sc.lastKey = literal[0].s;
		sc.firstKeyInclusion = sc.lastKeyInclusion = true;
		if (field->hashTable != 0) { 
		    dbHashTable::find(this, field->hashTable, sc);
		    TRACE_MSG(("Hash table search for field %s.%s: "
			       "%d probes\n", field->defTable->name, 
			       field->longName, sc.probes));
		} else { 
		    dbTtree::find(this, field->tTree, sc);
		    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
			       field->defTable->name, field->longName, 
			       sc.probes));
		}
	    } else { 		
		int len = s - literal[0].s;
		if (len == 0) { 
		    if (*s != dbMatchAnySubstring) { 
			return false;
		    }
		    sc.firstKey = NULL;
		    sc.lastKey = NULL;
		    dbTtree::find(this, field->tTree, sc);
		    TRACE_MSG(("Use index for ordering records by field "
			       "%s.%s\n", field->defTable->name, 
			       field->longName)); 
		} else { 	    
		    sc.firstKey = new char[len+1];
		    memcpy(sc.firstKey, literal[0].s, len);
		    sc.firstKey[len] = '\0';
		    sc.firstKeyInclusion = true;
		    sc.lastKey = new char[len+4];
		    memcpy(sc.lastKey, literal[0].s, len);
		    if ((byte)sc.lastKey[len-1] != 0xFF) { 
			sc.lastKey[len-1] += 1;
			sc.lastKey[len] = '\0';
			sc.lastKeyInclusion = false;
		    } else { 
			sc.lastKey[len] = (char)0xFF;
			sc.lastKey[len+1] = (char)0xFF;
			sc.lastKey[len+2] = (char)0xFF;
			sc.lastKey[len+3] = '\0';
			sc.lastKeyInclusion = true;
		    }
		    if (s[0] != dbMatchAnySubstring || s[1] != '\0') { 
			// Records selected by index do not necessarily
			// match the pattern, so include pattern matching in
			// condition expression
			if (andExpr == NULL) { 
			    if (expr->operand[0]->cop != dbvmLoadSelfString) { 
				dbExprNode load(dbvmLoadSelfString, 
						expr->operand[0]->ref.field);
				dbExprNode like(expr->cop, &load, 
						expr->operand[1],
						expr->operand[2]);
				sc.condition = &like;
				dbTtree::find(this, field->tTree, sc);
				like.cop = dbvmVoid;// do not destruct operands
			    } else { 
				sc.condition = expr;
				dbTtree::find(this, field->tTree, sc);
			    }
			} else { 
			    sc.condition = andExpr;
			    dbTtree::find(this, field->tTree, sc);
			}
		    } else { 
			dbTtree::find(this, field->tTree, sc);
		    }
		    TRACE_MSG(("Index search for prefix in LIKE expression "
			       "for field %s.%s: %d probes\n", 
			       field->defTable->name, field->longName, 
			       sc.probes));
		    delete[] sc.firstKey;
		    delete[] sc.lastKey;
		}
	    } 	
	    return true;
	}
    }
    return false;
}


struct SearchThreadArgument { 
    dbParallelQueryContext* ctx;
    int                     id;
};
			     

static void thread_proc parallelSearch(void* arg) 
{
    SearchThreadArgument* sa = (SearchThreadArgument*)arg;
    sa->ctx->search(sa->id);
}


void dbDatabase::traverse(dbAnyCursor* cursor, dbQuery& query) 
{
    const int defaultStackSize = 1024;
    oid_t buf[defaultStackSize];
    oid_t *stack = buf;
    int   stackSize = defaultStackSize;
    int   sp = 0, len;
    dbAnyArray* arr;
    oid_t oid, *refs;
    dbTable* table = (dbTable*)getRow(cursor->table->tableId);

    void* root = (void*)query.root;
    switch (query.startFrom) { 
      case dbCompiledQuery::StartFromFirst:
	oid = table->firstRow;
	if (oid != 0) { 
	    stack[sp++] = oid;
	}
	break;
      case dbCompiledQuery::StartFromLast:
	oid = table->lastRow;
	if (oid != 0) { 
	    stack[sp++] = oid;
	}
	break;
      case dbCompiledQuery::StartFromRef:
	oid = *(oid_t*)root;
	if (oid != 0) { 
	    stack[sp++] = oid;
	}
	break;
      case dbCompiledQuery::StartFromArrayPtr:
	root = *(dbAnyArray**)root;
	// no break
      case dbCompiledQuery::StartFromArray:
	arr = (dbAnyArray*)root;
	len = arr->length();
	if (len > stackSize) {
	    stackSize = len;
	    stack = new oid_t[stackSize];
	}
	refs = (oid_t*)arr->base();
	while (--len >= 0) { 
	    oid = refs[len];
	    if (oid != 0) { 
		stack[sp++] = oid;
	    }
	}
	break;
      default:
	assert(false);
    }
    cursor->checkForDuplicates();
    dbExprNode* condition = query.tree;
    dbFollowByNode* follow = query.follow;

    while (sp != 0) { 
	oid_t curr = stack[--sp];
	if (condition->cop == dbvmVoid || evaluate(condition, curr, table)) {
	    if (!cursor->add(curr)) { 
		break;
	    }
	} else { 
	    cursor->mark(curr);
	}
	byte* record = (byte*)getRow(curr);
	for (dbFollowByNode* fp = follow; fp != NULL; fp = fp->next) { 
	    dbFieldDescriptor* fd = fp->field;
	    if (fd->type == dbField::tpArray) { 
		dbVarying* vp = (dbVarying*)(record + fd->dbsOffs);
		len = vp->size;
		if (sp + len > stackSize) { 
		    int newSize = len > stackSize ? len*2 : stackSize*2;
		    oid_t* newStack = new oid_t[newSize];
		    memcpy(newStack, stack, stackSize*sizeof(oid_t));
		    stackSize = newSize;
		    if (stack != buf) { 
			delete[] stack;
		    }
		    stack = newStack;
		}
		refs = (oid_t*)(record + vp->offs);
		while (--len >= 0) { 
		    oid = refs[len];
		    if (oid != 0 && !cursor->isMarked(oid)) { 
			stack[sp++] = oid;
		    }
		}
	    } else { 
		assert(fd->type == dbField::tpReference);
		if (sp == stackSize) { 
		    int newSize = stackSize*2;
		    oid_t* newStack = new oid_t[newSize];
		    memcpy(newStack, stack, stackSize*sizeof(oid_t));
		    stackSize = newSize;
		    if (stack != buf) { 
			delete[] stack;
		    }
		    stack = newStack;
		}
		oid = *(oid_t*)(record + fd->dbsOffs);
		if (oid != 0 && !cursor->isMarked(oid)) { 
		    stack[sp++] = oid;
		}
	    }
	}
    }
    if (stack != buf) { 
	delete[] stack;
    }
    if (query.order != NULL) { 
	cursor->selection.sort(this, query.order);
    }
}


void dbDatabase::select(dbAnyCursor* cursor, dbQuery& query) 
{    
    assert(opened);
    dbDatabaseThreadContext* ctx = threadContext.get();
    dbFieldDescriptor* indexedField = NULL;
    assert(ctx != NULL);
    { 
	dbCriticalSection cs(query.mutex);  
	query.mutexLocked = true; 
	if (!query.compiled() || cursor->table != query.table) { 
	    if (!ctx->compiler.compile(cursor->table, query)) { 
		query.mutexLocked = false;
		return;
	    }
	}
	query.mutexLocked = false;
    }
    beginTransaction(cursor->type == dbCursorForUpdate);

    if (query.startFrom != dbCompiledQuery::StartFromAny) { 
	ctx->cursors.link(cursor);
        traverse(cursor, query);
	return;
    }

    dbExprNode* condition = query.tree;
    if (condition->cop == dbvmVoid && query.order == NULL) { 
	// Empty select condition: select all records in the table
	select(cursor);
	return;
    } 
    if (condition->cop == dbvmEqReference) { 
	if (condition->operand[0]->cop == dbvmCurrent
	    && condition->operand[1]->cop == dbvmLoadVarReference)
	{
	    cursor->setCurrent(*(dbAnyReference*)condition->operand[1]->var);
	    return;
	} 
	if (condition->operand[1]->cop == dbvmCurrent
	    && condition->operand[0]->cop == dbvmLoadVarReference)
	{
	    cursor->setCurrent(*(dbAnyReference*)condition->operand[0]->var);
	    return;
	}
    }
    ctx->cursors.link(cursor);

    if (condition->cop == dbvmAndBool) { 
	if (isIndexApplicable(cursor, condition->operand[0], 
			      condition, indexedField)) 
	{ 
	    if (query.order != NULL) { 
		if (indexedField->defTable != query.table
		    || query.order->next != NULL 
		    || query.order->field != indexedField)
		{ 
		    cursor->selection.sort(this, query.order);
		} else if (!query.order->ascent) { 
		    cursor->selection.reverse();
		}
	    }
	    return;
	}
    } else { 
	if (condition->cop == dbvmOrBool) { 
	    cursor->checkForDuplicates();
	}
	while (condition->cop == dbvmOrBool 
	       && !cursor->isLimitReached()
	       && isIndexApplicable(cursor, condition->operand[0], NULL, 
				    indexedField))
	{
	    condition = condition->operand[1];
	}
	if (!cursor->isLimitReached()
	    && isIndexApplicable(cursor, condition, NULL, indexedField)) 
	{ 
	    if (query.order != NULL) {
		if (indexedField->defTable != query.table
		    || condition != query.tree
		    || query.order->next != NULL 
		    || query.order->field != indexedField)
		{ 
		    cursor->selection.sort(this, query.order);
		} else if (!query.order->ascent) { 
		    cursor->selection.reverse();		
		}
	    }
	    return;
	}
    }
    if (query.order != NULL && query.order->next == NULL 
	&& query.order->field->tTree != 0) 
    { 
	dbFieldDescriptor* field = query.order->field;
	TRACE_MSG(("Use index for ordering records by field %s.%s\n", 
		   query.table->name, field->longName)); 
	if (condition->cop == dbvmVoid) { 
	    if (query.order->ascent) { 
		dbTtree::traverseForward(this, field->tTree, cursor); 
	    } else { 
		dbTtree::traverseBackward(this, field->tTree, cursor);
	    }
	} else { 
	    if (query.order->ascent) { 
		dbTtree::traverseForward(this,field->tTree,cursor,condition); 
	    } else { 
		dbTtree::traverseBackward(this,field->tTree,cursor,condition);
	    }
	}
	return;
    }

    dbTable* table = (dbTable*)getRow(cursor->table->tableId);
    int n = parThreads-1;
    if (cursor->getNumberOfRecords() == 0
	&& n > 0 && table->nRows >= dbParallelScanThreshold 
	&& cursor->limit >= dbDefaultSelectionLimit)
    {
	dbThread thread[dbMaxParallelSearchThreads];
	SearchThreadArgument sa[dbMaxParallelSearchThreads];
	dbParallelQueryContext par(this, table, &query);
	int i;
	for (i = 0; i < n; i++) { 
	    sa[i].id = i;
	    sa[i].ctx = &par;
	    thread[i].create(parallelSearch, &sa[i]);
	}
	par.search(i);
	for (i = 0; i < n; i++) { 
	    thread[i].join();
	}
	if (query.order != NULL) { 
	    dbRecord* rec[dbMaxParallelSearchThreads];
	    for (i = 0; i <= n; i++) { 
		if (par.selection[i].first != NULL) { 
		    rec[i] = getRow(par.selection[i].first->rows[0]);
		} else { 
		    rec[i] = NULL;
		}
	    }
	    while (true) { 
	        int min = -1;
		for (i = 0; i <= n; i++) { 
		    if (rec[i] != NULL 
			&& (min < 0 || dbSelection::compare(rec[i], rec[min], 
							    query.order) < 0))
		    {
			min = i;
		    }
		}
		if (min < 0) { 
		    return;
		}
		oid_t oid = 
		    par.selection[min].first->rows[par.selection[min].pos];
		cursor->selection.add(oid);
		par.selection[min].pos += 1;
		if (par.selection[min].pos == par.selection[min].first->nRows){
		    par.selection[min].pos = 0;
		    dbSelection::segment* next=par.selection[min].first->next;
		    delete par.selection[min].first;
		    if ((par.selection[min].first = next) == NULL) { 
			rec[min] = NULL;
			continue;
		    }
		}
		oid = par.selection[min].first->rows[par.selection[min].pos];
		rec[min] = getRow(oid);
	    }
	} else { 
	    for (i = 0; i <= n; i++) { 
		if (par.selection[i].first != NULL) { 
		    par.selection[i].first->prev = cursor->selection.last;
		    if (cursor->selection.last == NULL) { 
			cursor->selection.first = par.selection[i].first;
		    } else { 
			cursor->selection.last->next = par.selection[i].first;
		    }
		    cursor->selection.last = par.selection[i].last;
		    cursor->selection.nRows += par.selection[i].nRows;	
		}
	    }
	}		
    } else { 
	oid_t oid = table->firstRow;
	if (!cursor->isLimitReached()) { 
	    while (oid != 0) { 
		if (evaluate(condition, oid, table)) { 
		    if (!cursor->add(oid)) { 
			break;
		    }
		}
		oid = getRow(oid)->next;
	    }
	}
	if (query.order != NULL) { 
	    cursor->selection.sort(this, query.order);
	}
    }
}

void dbDatabase::select(dbAnyCursor* cursor) 
{
    assert(opened);
    beginTransaction(cursor->type == dbCursorForUpdate);
    dbTable* table = (dbTable*)getRow(cursor->table->tableId);
    cursor->firstId = table->firstRow;
    cursor->lastId = table->lastRow;
    cursor->selection.nRows = table->nRows;
    cursor->allRecords = true;
    threadContext.get()->cursors.link(cursor);
}


void dbDatabase::remove(dbTableDescriptor* desc, oid_t delId) 
{
    modified = true;

    removeInverseReferences(desc, delId);

    dbFieldDescriptor* fd;
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField){
	dbHashTable::remove(this, fd->hashTable, delId, fd->type, fd->dbsOffs);
    }
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbTtree::remove(this, fd->tTree, delId, fd->type, fd->dbsOffs);
    }

    freeRow(desc->tableId, delId);
}


dbRecord* dbDatabase::putRow(oid_t oid, size_t newSize) 
{  
    offs_t offs = currIndex[oid];
    if (oid < committedIndexSize && index[0][oid] == index[1][oid]) { 
	size_t pageNo = oid/dbHandlesPerPage;
	monitor->dirtyPagesMap[pageNo >> 5] |= 1 << (pageNo & 31);
	cloneBitmap(offs, getRow(oid)->size);
	currIndex[oid] = allocate(newSize);
    } else { 
	size_t oldSize = getRow(oid)->size;
	if (oldSize != newSize) {
	    currIndex[oid] = allocate(newSize);
	    cloneBitmap(offs, oldSize);
	    free(offs, oldSize);
	}
    }
    dbRecord* record = (dbRecord*)(baseAddr + currIndex[oid]);
    record->next = ((dbRecord*)(baseAddr + offs))->next;
    record->prev = ((dbRecord*)(baseAddr + offs))->prev;
    record->size = newSize;
    return record;
}

oid_t dbDatabase::allocateRow(oid_t tableId, size_t size) 
{ 
    oid_t oid = allocateId();
    currIndex[oid] = allocate(size);
    dbTable* table = (dbTable*)putRow(tableId);
    dbRecord* record = getRow(oid);
    record->size = size;
    record->next = 0;
    record->prev = table->lastRow;
    if (table->lastRow != 0) { 
	//
	// Optimisation hack: avoid cloning of the last record. 
	// Possible inconsistency in L2-list will be eliminated by recovery
	// procedure.
	//
	getRow(table->lastRow)->next = oid;
	file.markAsDirty(currIndex[table->lastRow], sizeof(dbRecord));
    } else { 
	table->firstRow = oid;
    }
    table->lastRow = oid;
    table->nRows += 1;
    return oid;
}

void dbDatabase::freeRow(oid_t tableId, oid_t oid)
{
    dbTable* table = (dbTable*)putRow(tableId);
    dbRecord* del = getRow(oid);
    size_t size = del->size;
    oid_t next = del->next;
    oid_t prev = del->prev;
    table->nRows -= 1;
    if (prev == 0) {
	table->firstRow = next;
    }
    if (next == 0) {
	table->lastRow = prev;
    }
    if (prev != 0) {
	putRow(prev)->next = next;
    }
    if (next != 0) {
	putRow(next)->prev = prev;
    }
    if (oid < committedIndexSize && index[0][oid] == index[1][oid]) { 
	cloneBitmap(currIndex[oid], size);
    } else { 
	free(currIndex[oid], size);
    }
    freeId(oid);
}

void dbDatabase::freeObject(oid_t oid) 
{ 
    int marker = currIndex[oid] & dbInternalObjectMarker;
    if (oid < committedIndexSize && index[0][oid] == index[1][oid]) { 
	cloneBitmap(currIndex[oid] - marker, internalObjectSize[marker]);
    } else { 
	free(currIndex[oid] - marker, internalObjectSize[marker]);
    } 
    freeId(oid);
}
 

void dbDatabase::update(oid_t oid, dbTableDescriptor* desc, void const* record)
{
    size_t size = 
	desc->columns->calculateRecordSize((byte*)record, desc->fixedSize);

    byte* src = (byte*)record;
    desc->columns->markUpdatedFields((byte*)getRow(oid), src);
    updatedRecordId = oid;

    dbFieldDescriptor* fd;
    for (fd = desc->inverseFields; fd != NULL; fd = fd->nextInverseField) { 
	if (fd->type == dbField::tpArray) { 
	    dbAnyArray* arr = (dbAnyArray*)(src + fd->appOffs);
	    int n = arr->length();
	    oid_t* newrefs = (oid_t*)arr->base();

	    byte* old = (byte*)getRow(oid);
	    int m = ((dbVarying*)(old + fd->dbsOffs))->size;
	    int offs = ((dbVarying*)(old + fd->dbsOffs))->offs;
	    int i, j, k;
	    old += offs;

	    for (i = j = 0; i < m; i++) {
		oid_t oldref = *((oid_t*)old + i); 
		if (oldref != 0) { 
		    for (k = j; j < n && newrefs[j] != oldref; j++);
		    if (j == n) { 
			for (j = k--; k >= 0 && newrefs[k] != oldref; k--);
			if (k < 0) { 
			    removeInverseReference(fd, oid, oldref);
			    old = (byte*)getRow(oid) + offs;
			}
		    } else { 
			j += 1;
		    }
		}
	    }
	    for (i = j = 0; i < n; i++) { 
		if (newrefs[i] != 0) { 
		    for(k=j; j < m && newrefs[i] != *((oid_t*)old+j); j++);
		    if (j == m) { 
			for (j=k--; k >= 0 && newrefs[i] != *((oid_t*)old+k); k--);
			if (k < 0) { 
			    insertInverseReference(fd, oid, newrefs[i]);
			    old = (byte*)getRow(oid) + offs;
			}
		    } else { 
			j += 1;
		    }
		}
	    }
	} else { 
	    oid_t newref = *(oid_t*)(src + fd->appOffs);
	    byte* old = (byte*)getRow(oid);
	    oid_t oldref = *(oid_t*)(old + fd->dbsOffs); 
	    if (newref != oldref) {
		if (oldref != 0) { 
		    removeInverseReference(fd, oid, oldref);
		}
		if (newref != 0) { 
		    insertInverseReference(fd, oid, newref);
		}
	    }
	}
    }		

    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbHashTable::remove(this,fd->hashTable,oid,fd->type,fd->dbsOffs);
	}
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbTtree::remove(this, fd->tTree, oid, fd->type, fd->dbsOffs);
	}
    }

    byte* old = (byte*)getRow(oid);    
    byte* dst = (byte*)putRow(oid, size);    
    if (dst == old) { 
	dbSmallBuffer buf(size);
	byte* temp = (byte*)buf.base();
	desc->columns->storeRecordFields(temp, src, desc->fixedSize);
	memcpy(dst+sizeof(dbRecord), buf+sizeof(dbRecord), 
	       size-sizeof(dbRecord));
    } else { 
	desc->columns->storeRecordFields(dst, src, desc->fixedSize);
    }
    modified = true;

    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbHashTable::insert(this,fd->hashTable,oid,fd->type,fd->dbsOffs,0);
	}
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbTtree::insert(this, fd->tTree, oid, fd->type, fd->dbsOffs);
	    fd->attr &= ~dbFieldDescriptor::Updated;
	}
    }
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	fd->attr &= ~dbFieldDescriptor::Updated;	
    }
}


void dbDatabase::insertRecord(dbTableDescriptor* desc, dbAnyReference* ref, 
			      void const* record) 
{ 
    assert(opened);
    beginTransaction(true);
    modified = true;
    size_t size = 
	desc->columns->calculateRecordSize((byte*)record, desc->fixedSize);

    oid_t oid = allocateRow(desc->tableId, size);
    byte* src = (byte*)record;
    byte* dst = (byte*)getRow(oid);    
    desc->columns->storeRecordFields(dst, src, desc->fixedSize);
    ref->oid = oid;

    int nRows = ((dbTable*)getRow(desc->tableId))->nRows;
    dbFieldDescriptor* fd;
    for (fd = desc->inverseFields; fd != NULL; fd = fd->nextInverseField) { 
	if (fd->type == dbField::tpArray) { 
	    dbAnyArray* arr = (dbAnyArray*)(src + fd->appOffs);
	    int n = arr->length();
	    oid_t* refs = (oid_t*)arr->base();
	    while (--n >= 0) { 
		if (refs[n] != 0) {
		    insertInverseReference(fd, oid, refs[n]);
		}
	    }
	} else { 
	    oid_t ref = *(oid_t*)(src + fd->appOffs);
	    if (ref != 0) { 
		insertInverseReference(fd, oid, ref);
	    }
	}
    }		
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	dbHashTable::insert(this, fd->hashTable, oid, fd->type, fd->dbsOffs, 
			    nRows);
    }
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbTtree::insert(this, fd->tTree, oid, fd->type, fd->dbsOffs);
    }
}


inline void dbDatabase::extend(offs_t size)
{
    size_t oldSize = header->size;

    if (size > oldSize) { 
	if (oldSize*2 > size) { 
	    size = oldSize*2;
	} 
	TRACE_MSG(("Extend database file from %ld to %ld bytes\n",
		   header->size, size));
	header->size = size;
	sprintf(databaseName + databaseNameLen, ".%d", ++monitor->version);
	int status = file.setSize(databaseName, size);
	if (status != dbFile::ok) { 
	    handleError(FileError, "Failed to extend file", status);
	}
	file.markAsDirty(oldSize, size - oldSize);
	byte* addr = (byte*)file.getAddr();
	long shift = addr - baseAddr;
	if (shift != 0) { 
	    dbDatabaseThreadContext* ctx = threadContext.get();
	    assert(ctx != NULL);
	    size_t base = (size_t)baseAddr; 
	    for (dbL2List* cursor = ctx->cursors.next; 
		 cursor != &ctx->cursors;
		 cursor = cursor->next)
	    {
		((dbAnyCursor*)cursor)->adjustReferences(base, oldSize, shift);
	    }
	    baseAddr = addr;
	    index[0] = (offs_t*)((char*)index[0] + shift);
	    index[1] = (offs_t*)((char*)index[1] + shift);
	    currIndex = (offs_t*)((char*)currIndex + shift);
	    header = (dbHeader*)addr;
	}
    }
}

offs_t dbDatabase::allocate(size_t size, oid_t oid)
{
    static byte const firstHoleSize [] = {
	8,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
	5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
    };
    static byte const lastHoleSize [] = {
        8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
    static byte const maxHoleSize [] = {
	8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	5,4,3,3,2,2,2,2,3,2,2,2,2,2,2,2,4,3,2,2,2,2,2,2,3,2,2,2,2,2,2,2,
	6,5,4,4,3,3,3,3,3,2,2,2,2,2,2,2,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,
	5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,
	7,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,4,3,2,2,2,2,2,2,3,2,2,2,2,2,2,2,
	5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,
	6,5,4,4,3,3,3,3,3,2,2,2,2,2,2,2,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,1,
	5,4,3,3,2,2,2,2,3,2,1,1,2,1,1,1,4,3,2,2,2,1,1,1,3,2,1,1,2,1,1,0
    };
    static byte const maxHoleOffset [] = {
	0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,0,1,5,5,5,5,5,5,0,5,5,5,5,5,5,5,
        0,1,2,2,0,3,3,3,0,1,6,6,0,6,6,6,0,1,2,2,0,6,6,6,0,1,6,6,0,6,6,6,
        0,1,2,2,3,3,3,3,0,1,4,4,0,4,4,4,0,1,2,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,2,2,0,3,3,3,0,1,0,2,0,1,0,4,0,1,2,2,0,1,0,3,0,1,0,2,0,1,0,7,
	0,1,2,2,3,3,3,3,0,4,4,4,4,4,4,4,0,1,2,2,0,5,5,5,0,1,5,5,0,5,5,5,
	0,1,2,2,0,3,3,3,0,1,0,2,0,1,0,4,0,1,2,2,0,1,0,3,0,1,0,2,0,1,0,6,
	0,1,2,2,3,3,3,3,0,1,4,4,0,4,4,4,0,1,2,2,0,1,0,3,0,1,0,2,0,1,0,5,
	0,1,2,2,0,3,3,3,0,1,0,2,0,1,0,4,0,1,2,2,0,1,0,3,0,1,0,2,0,1,0,0
    };

    size = DOALIGN(size, dbAllocationQuantum);
    int objBitSize = size >> dbAllocationQuantumBits;
    offs_t pos;    
    int firstPage = currBitmapPage;
    int lastPage = dbBitmapId + dbBitmapPages;
    int freePage = 0;
    int holeBeforeFreePage = 0;
    int i, holeBitSize = 0;
    register int alignment = size & (dbPageSize-1);
    register size_t offs = currBitmapOffs;
    const size_t inc = dbPageSize/dbAllocationQuantum/8;
    const int pageBits = dbPageSize*8;

    allocatedSize += size;
    inAllocator += 1;
    if (alignment == 0) { 
	offs = DOALIGN(offs, inc);
    }
	
    while (true) { 
	for (i=firstPage; i<lastPage && currIndex[i]!=dbFreeHandleMarker; i++){
	    int spaceNeeded = objBitSize - holeBitSize < pageBits 
		? objBitSize - holeBitSize : pageBits;
	    if (bitmapPageAvailableSpace[i] <= spaceNeeded) {
		holeBitSize = 0;
		offs = 0;
		continue;
	    }
	    register byte* begin = get(i);
	    while (offs < dbPageSize) { 
		int mask = begin[offs]; 
		if (holeBitSize + firstHoleSize[mask] >= objBitSize) { 
		    currBitmapPage = i;
		    currBitmapOffs = offs + 1;
		    pos = ((offs_t(i-dbBitmapId)*dbPageSize + offs)*8 
			   - holeBitSize) << dbAllocationQuantumBits;
		    extend(pos + size);
		    if (oid != 0) { 
			offs_t prev = currIndex[oid];
			memcpy(baseAddr+pos, 
			       baseAddr+(prev&~dbInternalObjectMarker), size);
			currIndex[oid] = (prev & dbInternalObjectMarker) + pos;
		    }
		    begin = put(i);
		    if (currBitmapOffs == offs+1) { 
			currBitmapOffs = offs;
		    }
		    begin[offs] |= (1 << (objBitSize - holeBitSize)) - 1; 
		    if (holeBitSize != 0) { 
			if (size_t(holeBitSize) > offs*8) { 
			    memset(begin, 0xFF, offs);
			    holeBitSize -= offs*8;
			    begin = put(--i);
			    offs = dbPageSize;
			}
			while (holeBitSize > pageBits) { 
			    memset(begin, 0xFF, dbPageSize);
			    holeBitSize -= pageBits;
			    bitmapPageAvailableSpace[i] = 0;
			    begin = put(--i);
			    offs = dbPageSize;
			}
			while ((holeBitSize -= 8) > 0) { 
			    begin[--offs] = 0xFF; 
			}
			begin[offs-1] |= ~((1 << -holeBitSize) - 1);
		    }
		    inAllocator -= 1;
		    file.markAsDirty(pos, size);
		    return pos;
		} else if (maxHoleSize[mask] >= objBitSize) { 
		    int holeBitOffset = maxHoleOffset[mask];
		    currBitmapPage = i;
		    currBitmapOffs = offs + 1;
		    pos = ((offs_t(i-dbBitmapId)*dbPageSize + offs)*8 + 
			   holeBitOffset) << dbAllocationQuantumBits;
		    extend(pos + size);
		    if (oid != 0) { 
			offs_t prev = currIndex[oid];
			memcpy(baseAddr+pos, 
			       baseAddr+(prev&~dbInternalObjectMarker), size);
			currIndex[oid] = (prev & dbInternalObjectMarker) + pos;
		    }
		    begin = put(i);
		    begin[offs] |= ((1 << objBitSize) - 1) << holeBitOffset;
		    if (currBitmapOffs == offs+1) { 
			currBitmapOffs = offs;
		    }
		    inAllocator -= 1;
		    file.markAsDirty(pos, size);
		    return pos;
		}
		if (lastHoleSize[mask] == 8) { 
		    holeBitSize += 8;
		    offs += 1;
		} else { 
		    if (alignment == 0) { 
			holeBitSize = 0;
			offs = (offs + inc) & ~(inc-1);
		    } else { 
			holeBitSize = lastHoleSize[mask];
			offs += 1;
		    }
		}
	    }
	    if (offs == 0 && holeBitSize == 0 
		&& spaceNeeded < bitmapPageAvailableSpace[i]) 
	    { 
		bitmapPageAvailableSpace[i] = spaceNeeded;
	    }
	    offs = 0;
	}
	if (firstPage == dbBitmapId || inAllocator > 1) { 
	    if (freePage > i) { 
		i = freePage;
		holeBitSize = holeBeforeFreePage;
	    }
	    if (i == lastPage) { 
		handleError(OutOfMemoryError, NULL, size);
	    }
	    assert(currIndex[i] == dbFreeHandleMarker);

	    size_t extension = (size > extensionQuantum) 
		             ? size : extensionQuantum;
	    int morePages = 
		(extension + dbPageSize*(dbAllocationQuantum*8-1) - 1)
		/ (dbPageSize*(dbAllocationQuantum*8-1));

	    if (size_t(i + morePages) > dbBitmapId + dbBitmapPages) { 
		morePages =  
		    (size + dbPageSize*(dbAllocationQuantum*8-1) - 1)
		    / (dbPageSize*(dbAllocationQuantum*8-1));
		if (size_t(i + morePages) > dbBitmapId + dbBitmapPages) { 
		    handleError(OutOfMemoryError, NULL, size);
		}
	    }
	    objBitSize -= holeBitSize;
	    int skip = DOALIGN(objBitSize, dbPageSize/dbAllocationQuantum);
	    pos = ((i-dbBitmapId) << (dbPageBits+dbAllocationQuantumBits+3)) 
		+ (skip << dbAllocationQuantumBits);
	    extend(pos + morePages*dbPageSize);
	    file.markAsDirty(pos, morePages*dbPageSize);
	    memset(baseAddr + pos, 0, morePages*dbPageSize);
	    memset(baseAddr + pos, 0xFF, objBitSize>>3);
	    *(baseAddr + pos + (objBitSize>>3)) = (1 << (objBitSize&7))-1;
	    memset(baseAddr + pos + (skip>>3), 0xFF, 
		   morePages*(dbPageSize/dbAllocationQuantum/8));

	    int j = i;
	    while (--morePages >= 0) { 
		monitor->dirtyPagesMap[oid_t(j)/dbHandlesPerPage/32] 
		    |= 1 << int(j/dbHandlesPerPage & 31);
		currIndex[j++] = pos + dbPageObjectMarker;
		pos += dbPageSize;
	    }
	    j = i + objBitSize / pageBits; 
	    currBitmapPage = j;
	    currBitmapOffs = 0;
	    while (--j >= i) { 
		bitmapPageAvailableSpace[j] = 0;
	    }
	    
	    pos = (offs_t(i-dbBitmapId)*dbPageSize*8 - holeBitSize)
		<< dbAllocationQuantumBits;
	    if (oid != 0) { 
		offs_t prev = currIndex[oid];
		memcpy(baseAddr + pos, 
		       baseAddr + (prev & ~dbInternalObjectMarker), size);
		currIndex[oid] = (prev & dbInternalObjectMarker) + pos;
	    }

	    if (holeBitSize != 0) { 
		while (holeBitSize > pageBits) { 
		    holeBitSize -= pageBits;
		    memset(put(--i), 0xFF, dbPageSize);
		    bitmapPageAvailableSpace[i] = 0;
		}
		byte* cur = (byte*)put(--i) + dbPageSize;
		while ((holeBitSize -= 8) > 0) { 
		    *--cur = 0xFF; 
		}
		*(cur-1) |= ~((1 << -holeBitSize) - 1);
	    }
	    inAllocator -= 1;
	    file.markAsDirty(pos, size);
	    return pos;
	} 
	freePage = i;
	holeBeforeFreePage = holeBitSize;
	holeBitSize = 0;
	firstPage = dbBitmapId;
	lastPage = currBitmapPage;
	offs = 0;
    }
} 

void dbDatabase::free(offs_t pos, size_t size)
{
    assert(pos != 0 && (pos & (dbAllocationQuantum-1)) == 0);
    size_t quantNo = pos / dbAllocationQuantum;
    int    objBitSize = (size+dbAllocationQuantum-1) / dbAllocationQuantum;
    oid_t  pageId = dbBitmapId + quantNo / (dbPageSize*8);
    size_t offs = quantNo % (dbPageSize*8) / 8;
    byte*  p = put(pageId) + offs;
    int    bitOffs = quantNo & 7;

    allocatedSize -= objBitSize*dbAllocationQuantum;

    if (pageId == currBitmapPage && offs < currBitmapOffs) { 
	currBitmapOffs = offs;
    }

    bitmapPageAvailableSpace[pageId] = INT_MAX;
 
    if (objBitSize > 8 - bitOffs) { 
	objBitSize -= 8 - bitOffs;
	*p++ &= (1 << bitOffs) - 1;
	offs += 1;
	while (objBitSize + offs*8 > dbPageSize*8) { 
	    memset(p, 0, dbPageSize - offs);
	    p = put(++pageId);
	    bitmapPageAvailableSpace[pageId] = INT_MAX;
	    objBitSize -= (dbPageSize - offs)*8;
	    offs = 0;
	}
	while ((objBitSize -= 8) > 0) { 
	    *p++ = 0;
	}
	*p &= ~((1 << (objBitSize + 8)) - 1);
    } else { 
	*p &= ~(((1 << objBitSize) - 1) << bitOffs); 
    }
}

void dbDatabase::cloneBitmap(offs_t pos, size_t size)
{
    size_t quantNo = pos / dbAllocationQuantum;
    int    objBitSize = (size+dbAllocationQuantum-1) / dbAllocationQuantum;
    oid_t  pageId = dbBitmapId + quantNo / (dbPageSize*8);
    size_t offs = quantNo % (dbPageSize*8) / 8;
    int    bitOffs = quantNo & 7;

    put(pageId); 
    if (objBitSize > 8 - bitOffs) { 
	objBitSize -= 8 - bitOffs;
	offs += 1;
	while (objBitSize + offs*8 > dbPageSize*8) { 
	    put(++pageId);
	    objBitSize -= (dbPageSize - offs)*8;
	    offs = 0;
	}
    }
}


oid_t dbDatabase::allocateId(int n) 
{
    oid_t oid;
    int curr = 1-header->curr;
    if (n == 1) { 
	if ((oid = header->root[curr].freeList) != 0) { 
	    header->root[curr].freeList = 
		(oid_t)(currIndex[oid] - dbFreeHandleMarker);
	    unsigned i = oid / dbHandlesPerPage;
	    monitor->dirtyPagesMap[i >> 5] |= 1 << (i & 31);
	    return oid;
	}
    }
    if (currIndexSize + n > header->root[curr].indexSize) {
	size_t oldIndexSize = header->root[curr].indexSize;
	size_t newIndexSize = oldIndexSize * 2;
	while (newIndexSize < oldIndexSize + n) { 
	    newIndexSize = newIndexSize*2;
	}
	TRACE_MSG(("Extend index size from %ld to %ld\n", 
		   oldIndexSize, newIndexSize));
	offs_t newIndex = allocate(newIndexSize*sizeof(offs_t));
	memcpy(baseAddr + newIndex, currIndex, currIndexSize*sizeof(offs_t));
	currIndex = index[curr] = (offs_t*)(baseAddr + newIndex);
	free(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	header->root[curr].index = newIndex;
	header->root[curr].indexSize = newIndexSize;
	file.markAsDirty(newIndex, currIndexSize*sizeof(offs_t));
    }
    oid = currIndexSize;
    header->root[curr].indexUsed = currIndexSize += n;
    return oid;
}
	    
void dbDatabase::freeId(oid_t oid, int n) 
{
    oid_t freeList = header->root[1-header->curr].freeList;
    while (--n >= 0) {
	unsigned i = oid / dbHandlesPerPage;
	monitor->dirtyPagesMap[i >> 5] |= 1 << (i & 31);
	currIndex[oid] = freeList + dbFreeHandleMarker;
	freeList = oid++;
    }
    header->root[1-header->curr].freeList = freeList;
}
    
bool dbDatabase::beginTransaction(bool modify)
{
    dbDatabaseThreadContext* ctx = threadContext.get();
    if (modify) { 
	assert(accessType != dbReadOnly);
	if (!ctx->writeAccess) { 
	    cs.enter();
	    if (ctx->readAccess) { 
		assert(monitor->nWriters == 0);
		if (monitor->nReaders != 1) {
		    if (monitor->waitForUpgrade) { 
			handleError(Deadlock, "Deadlock is caused by upgrading shared locks to exclusive");
		    }
		    monitor->waitForUpgrade = true;
		    monitor->nWaitWriters += 1;
		    cs.leave();
		    
		    while (!upgradeSem.wait(dbWaitLockTimeout)
			   || !(monitor->nWriters == 1 && monitor->nReaders == 0)) 
		    { 
			// There are no writers, so some reader was died
			cs.enter();
			unsigned currTime = dbSystem::getCurrentTimeMsec();
			if (currTime - monitor->lastDeadlockRecoveryTime
			    >= dbWaitLockTimeout)
			{
			    // Ok, let's try to "remove" this reader
			    monitor->lastDeadlockRecoveryTime = currTime;
			    if (--monitor->nReaders == 1) { 
				// Looks like we are recovered
				monitor->nWriters = 1;
				monitor->nReaders = 0;
				monitor->nWaitWriters -= 1;
				monitor->waitForUpgrade = false;
				cs.leave();
				break;
			    }
			}
			cs.leave();
		    }
		} else { 
		    monitor->nWriters = 1;		    
		    monitor->nReaders = 0;
		    cs.leave();
		} 
	    } else { 
		if (monitor->nWriters != 0 || monitor->nReaders != 0) { 
		    monitor->nWaitWriters += 1;
		    cs.leave();
		    while (!writeSem.wait(dbWaitLockTimeout)
			   || !(monitor->nWriters == 1 && monitor->nReaders == 0))
		    { 
			cs.enter();
			unsigned currTime = dbSystem::getCurrentTimeMsec();
			if (currTime - monitor->lastDeadlockRecoveryTime
			    >= dbWaitLockTimeout)
			{
			    monitor->lastDeadlockRecoveryTime = currTime;
			    if (monitor->nWriters != 0) { 
				// writer was died
				recovery();
				monitor->nWriters = 1;
				monitor->nWaitWriters -= 1;
				cs.leave();
				break;
			    } else { 
				// some reader was died
				// Ok, let's try to "remove" this reader
				if (--monitor->nReaders == 0) { 
				    // Looks like we are recovered
				    monitor->nWriters = 1;
				    monitor->nWaitWriters -= 1;
				    cs.leave();
				    break;
				} 
			    }
			}
			cs.leave();
		    }
		} else { 
		    monitor->nWriters = 1;
		    cs.leave();
		}
	    }
	    ctx->writeAccess = true;
	} 
    } else { 
	if (!ctx->readAccess && !ctx->writeAccess) { 
	    cs.enter();
	    if (monitor->nWriters + monitor->nWaitWriters != 0) {
		monitor->nWaitReaders += 1;
		cs.leave();
		while (!readSem.wait(dbWaitLockTimeout)
		       || !(monitor->nWriters == 0 && monitor->nReaders > 0))
		{ 
		    cs.enter();
		    unsigned currTime = dbSystem::getCurrentTimeMsec();
		    if (currTime - monitor->lastDeadlockRecoveryTime
			>= dbWaitLockTimeout)
		    {
			monitor->lastDeadlockRecoveryTime = currTime;
			if (monitor->nWriters != 0) { 
			    // writer was died
			    recovery();
			    monitor->nWriters = 0;
			} else {
			    // some potential writer was died
			    monitor->nWaitWriters -= 1;
			}
			monitor->nReaders += 1;
			monitor->nWaitReaders -= 1;
			cs.leave();
			break;
		    }
		    cs.leave();
		}
	    } else { 
		monitor->nReaders += 1;
		cs.leave();
	    }
	    ctx->readAccess = true;
	}
    }
    if (version != monitor->version) {
	sprintf(databaseName+databaseNameLen, ".%d", monitor->version);
	if (version == 0) { 
	    if (file.open(fileName, databaseName, accessType == dbReadOnly, 0)
		!= dbFile::ok) 
	    {
		handleError(DatabaseOpenError, "Failed to open database file");
		endTransaction(); // release locks
		return false;
	    }
	} else { 
	    int status = file.setSize(databaseName, header->size);
	    if (status != dbFile::ok) { 
		handleError(FileError,"Failed to reopen database file",status);
		endTransaction(); // release locks
		return false;
	    }
	}
	version = monitor->version;
	baseAddr = (byte*)file.getAddr();
	header = (dbHeader*)baseAddr;
	assert(file.getSize() == header->size);
    }
    index[0] = (offs_t*)(baseAddr + header->root[0].index);
    index[1] = (offs_t*)(baseAddr + header->root[1].index);
    currIndex = index[1-header->curr];
    currIndexSize = header->root[1-header->curr].indexUsed;
    committedIndexSize = header->root[header->curr].indexUsed;
    if (modify) { 
	header->dirty = true;
    }
    return true;
}

void dbDatabase::precommit() 
{
    dbDatabaseThreadContext* ctx = threadContext.get();     
    if (ctx != NULL && (ctx->writeAccess || ctx->readAccess)) { 
	ctx->concurrentId = concurrentTransId; 
	endTransaction();
    }
}


void dbDatabase::commit() 
{
    dbDatabaseThreadContext* ctx = threadContext.get();     
    if (ctx == NULL) { 
	return;
    }
    if (modified && (ctx->writeAccess || ctx->concurrentId == concurrentTransId))
    {
	if (!ctx->writeAccess) {
	    beginTransaction(true);
	}
	int curr = header->curr;
	int4 *map = monitor->dirtyPagesMap;
	size_t oldIndexSize = header->root[curr].indexSize;
	size_t newIndexSize = header->root[1-curr].indexSize;
	if (newIndexSize > oldIndexSize) { 
	    offs_t newIndex = allocate(newIndexSize*sizeof(offs_t));
	    header->root[1-curr].shadowIndex = newIndex;
	    header->root[1-curr].shadowIndexSize = newIndexSize;
	    cloneBitmap(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	    free(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	}   
	size_t nPages = committedIndexSize / dbHandlesPerPage;
	offs_t* srcIndex = currIndex; 
	offs_t* dstIndex = index[curr]; 	    
	for (size_t i = 0; i < nPages; i++) { 
	    if (map[i >> 5] & (1 << (i & 31))) { 
		file.markAsDirty(header->root[1-curr].index + i*dbPageSize, dbPageSize);
		for (size_t j = 0; j < dbHandlesPerPage; j++) {
		    offs_t offs = dstIndex[j];
		    if (srcIndex[j] != offs) { 
			if (!(offs & dbFreeHandleMarker)) {
			    size_t marker = offs & dbInternalObjectMarker;
			    if (marker != 0) { 
				free(offs-marker, internalObjectSize[marker]);
			    } else { 
				free(offs, ((dbRecord*)(baseAddr+offs))->size);
			    }
			}
		    }
		}
	    }
	    dstIndex += dbHandlesPerPage;
	    srcIndex += dbHandlesPerPage;
	}
	file.markAsDirty(header->root[1-curr].index + nPages*dbPageSize, 
			 (currIndexSize - nPages*dbHandlesPerPage)*sizeof(offs_t));
	offs_t* end = index[curr] + committedIndexSize;
	while (dstIndex < end) { 
	    offs_t offs = *dstIndex;
	    if (*srcIndex != offs) { 
		if (!(offs & dbFreeHandleMarker)) {
		    size_t marker = offs & dbInternalObjectMarker;
		    if (marker != 0) { 
			free(offs-marker, internalObjectSize[marker]);
		    } else { 
			free(offs, ((dbRecord*)(baseAddr+offs))->size);
		    }
		}
	    }
	    dstIndex += 1;
	    srcIndex += 1;
	}
	file.markAsDirty(0, sizeof(dbHeader));
	file.flush();

	cs.enter();
	while (monitor->backupInProgress) { 
	    cs.leave();
	    backupCompletedEvent.wait();
	    cs.enter();
	}
	header->curr = curr ^= 1;
	cs.leave();

	file.markAsDirty(0, sizeof(dbHeader));
	file.flush();

	file.markAsDirty(0, sizeof(dbHeader));
	header->root[1-curr].indexUsed = currIndexSize; 
	header->root[1-curr].freeList  = header->root[curr].freeList; 

	if (newIndexSize != oldIndexSize) {
	    header->root[1-curr].index=header->root[curr].shadowIndex;
	    header->root[1-curr].indexSize=header->root[curr].shadowIndexSize;
	    header->root[1-curr].shadowIndex=header->root[curr].index;
	    header->root[1-curr].shadowIndexSize=header->root[curr].indexSize;
	    file.markAsDirty(header->root[1-curr].index, currIndexSize*sizeof(offs_t));
	    memcpy(baseAddr + header->root[1-curr].index, currIndex, 
		   currIndexSize*sizeof(offs_t));
	    memset(map, 0, 4*((currIndexSize+dbHandlesPerPage*32-1)
		   / (dbHandlesPerPage*32)));
	} else { 
	    byte* srcIndex = (byte*)currIndex; 
	    byte* dstIndex = (byte*)index[1-curr]; 
	    
	    for (size_t i = 0; i < nPages; i++) { 
		if (map[i >> 5] & (1 << (i & 31))) { 
		    map[i >> 5] -= (1 << (i & 31));
		    memcpy(dstIndex, srcIndex, dbPageSize);
		    file.markAsDirty(header->root[1-curr].index + i*dbPageSize, dbPageSize);
		}
		srcIndex += dbPageSize;
		dstIndex += dbPageSize;
	    }
	    if (currIndexSize > nPages*dbHandlesPerPage) {
		memcpy(dstIndex, srcIndex,  		       
		       sizeof(offs_t)*(currIndexSize-nPages*dbHandlesPerPage));
		file.markAsDirty(header->root[1-curr].index + nPages*dbPageSize, 
				 sizeof(offs_t)*(currIndexSize-nPages*dbHandlesPerPage));
		memset(map + (nPages>>5), 0, 
		       ((currIndexSize + dbHandlesPerPage*32 - 1)
			/ (dbHandlesPerPage*32) - (nPages>>5))*4);
	    }
	}
	modified = false;
	concurrentTransId += 1;
    }
    if (ctx->writeAccess || ctx->readAccess) { 
	endTransaction();
    }
}

void dbDatabase::rollback() 
{
    dbDatabaseThreadContext* ctx = threadContext.get();
    if (modified && (ctx->writeAccess || ctx->concurrentId == concurrentTransId))
    { 
	if (!ctx->writeAccess) {
	    beginTransaction(true);
	}
	int curr = header->curr;
	byte* dstIndex = (byte*)currIndex; 
	byte* srcIndex = (byte*)index[curr]; 
 
	size_t nPages = 
	    (committedIndexSize + dbHandlesPerPage - 1) / dbHandlesPerPage;
	int4 *map = monitor->dirtyPagesMap;
	for (size_t i = 0; i < nPages; i++) { 
	    if (map[i >> 5] & (1 << (i & 31))) { 
		memcpy(dstIndex, srcIndex, dbPageSize);
		file.markAsDirty(header->root[1-curr].index + i*dbPageSize, dbPageSize);
	    }
	    srcIndex += dbPageSize;
	    dstIndex += dbPageSize;
	}
	memset(map, 0,
	       size_t((currIndexSize+dbHandlesPerPage*32-1) / (dbHandlesPerPage*32))*4);
	header->root[1-curr].indexSize = header->root[curr].indexSize;
	header->root[1-curr].indexUsed = committedIndexSize;
	header->root[1-curr].freeList  = header->root[curr].freeList; 
	file.markAsDirty(0, sizeof(dbHeader));
	modified = false;
	concurrentTransId += 1;
    } 
    if (monitor->users != 0) { // if not abandon	
	endTransaction();
    }
}

void dbDatabase::endTransaction() 
{
    dbDatabaseThreadContext* ctx = threadContext.get();
    assert(ctx != NULL);
    while (!ctx->cursors.isEmpty()) { 
	((dbAnyCursor*)ctx->cursors.next)->reset();
    }
    if (ctx->writeAccess) { 
	cs.enter();
	monitor->nWriters -= 1;
	assert(monitor->nWriters == 0 && !monitor->waitForUpgrade);
	if (monitor->nWaitWriters != 0) { 
	    monitor->nWaitWriters -= 1;
	    monitor->nWriters = 1;
	    writeSem.signal();
	} else if (monitor->nWaitReaders != 0) { 
	    monitor->nReaders = monitor->nWaitReaders;
	    monitor->nWaitReaders = 0;
	    readSem.signal(monitor->nReaders);
	}
	cs.leave();
    } else if (ctx->readAccess) { 
	cs.enter();
	monitor->nReaders -= 1;
	if (monitor->nReaders == 1 && monitor->waitForUpgrade) { 
	    assert(monitor->nWriters == 0);
	    monitor->waitForUpgrade = false;
	    monitor->nWaitWriters -= 1;
	    monitor->nWriters = 1;
	    monitor->nReaders = 0;
	    upgradeSem.signal();
	} else if (monitor->nReaders == 0) { 
	    if (monitor->nWaitWriters != 0) { 
		assert(monitor->nWriters == 0 && !monitor->waitForUpgrade);
		monitor->nWaitWriters -= 1;
		monitor->nWriters = 1;
		writeSem.signal();
	    }
	} 
	cs.leave();
    }
    ctx->writeAccess = false;
    ctx->readAccess = false;
}


void dbDatabase::linkTable(dbTableDescriptor* table, oid_t tableId)
{
    assert(((void)"Table can be used only in one database", 
	    table->tableId == 0));
    table->db = this;
    table->nextDbTable = tables;
    table->tableId = tableId;
    tables = table;
}

void dbDatabase::unlinkTable(dbTableDescriptor* table)
{
    dbTableDescriptor** tpp;
    for (tpp = &tables; *tpp != table; tpp = &(*tpp)->nextDbTable);
    *tpp = table->nextDbTable;
    table->tableId = 0;
    if (!table->fixedDatabase) { 
	table->db = NULL;
    }
}

dbTableDescriptor* dbDatabase::findTable(char const* name)
{
    for (dbTableDescriptor* desc=tables; desc != NULL; desc=desc->nextDbTable)
    { 
	if (desc->name == name) { 
	    return desc;
	}
    }
    return NULL;
}
    
void dbDatabase::insertInverseReference(dbFieldDescriptor* fd, oid_t inverseId,
					oid_t targetId)
{
    byte buf[1024];
    if (inverseId == targetId) { 
	return;
    }
    fd = fd->inverseRef;
    if (fd->type == dbField::tpArray) { 
	dbTableDescriptor* desc = fd->defTable;
	dbRecord* rec = getRow(targetId);
	dbVarying* arr = (dbVarying*)((byte*)rec + fd->dbsOffs);
	size_t arrSize = arr->size;
	size_t arrOffs = arr->offs;
	offs_t oldOffs = currIndex[targetId];
	size_t newSize = desc->fixedSize;
	int lastOffs = 
	    desc->columns->sizeWithoutOneField(fd, (byte*)rec, newSize);
	int newArrOffs = DOALIGN(newSize, sizeof(oid_t));
	size_t oldSize = rec->size;
	newSize = newArrOffs + (arrSize + 1)*sizeof(oid_t);
	if (newSize > oldSize) { 
	    newSize = newArrOffs + (arrSize+1)*sizeof(oid_t)*2;
	} else { 
	    newSize = oldSize;
	}

	byte* dst = (byte*)putRow(targetId, newSize);
	byte* src = baseAddr + oldOffs;
	byte* tmp = NULL;

	if (dst == src) { 
	    if (arr->offs == newArrOffs && newArrOffs > lastOffs) { 
		*((oid_t*)((byte*)rec + newArrOffs) + arrSize) = inverseId;
		arr->size += 1;
		return;
	    }
	    if (oldSize > sizeof(buf)) { 
                src = tmp = new byte[oldSize];
	    } else { 
		src = buf;
	    }
	    memcpy(src, rec, oldSize);
	}
	desc->columns->copyRecordExceptOneField(fd, dst, src, desc->fixedSize);
	
	arr = (dbVarying*)(dst + fd->dbsOffs);
	arr->size = arrSize + 1;
	arr->offs = newArrOffs;
	memcpy(dst + newArrOffs, src + arrOffs, arrSize*sizeof(oid_t));
	*((oid_t*)(dst + newArrOffs) + arrSize) = inverseId;
	if (tmp != NULL) { 
	    delete[] tmp;
	}
    } else { 
	*(oid_t*)((byte*)putRow(targetId) + fd->dbsOffs) = inverseId;
    }
}


void dbDatabase::removeInverseReferences(dbTableDescriptor* desc, oid_t oid)
{
    dbFieldDescriptor* fd;
    if (desc->inverseFields != NULL) { 
    }
    for (fd = desc->inverseFields; fd != NULL; fd = fd->nextInverseField) { 
	if (fd->type == dbField::tpArray) { 
	    dbVarying* arr = (dbVarying*)((byte*)getRow(oid) + fd->dbsOffs);
	    int n = arr->size;
	    int offs = arr->offs + n*sizeof(oid_t);
	    while (--n >= 0) { 
		offs -= sizeof(oid_t);
		oid_t ref = *(oid_t*)((byte*)getRow(oid) + offs);
		if (ref != 0) {
		    currIndex[oid] |= dbFreeHandleMarker;
		    removeInverseReference(fd, oid, ref);
		    currIndex[oid] &= ~dbFreeHandleMarker;
		}
	    }
	} else { 
	    oid_t ref = *(oid_t*)((byte*)getRow(oid) + fd->dbsOffs);
	    if (ref != 0) { 
		currIndex[oid] |= dbFreeHandleMarker;
		removeInverseReference(fd, oid, ref);
		currIndex[oid] &= ~dbFreeHandleMarker;
	    }
	}
    }
}


void dbDatabase::removeInverseReference(dbFieldDescriptor* fd, 
					oid_t inverseId,
					oid_t targetId)
{
    if (inverseId == targetId || targetId == updatedRecordId ||
	(currIndex[targetId] & dbFreeHandleMarker) != 0) 
    { 
	return;
    }
    byte* rec = (byte*)putRow(targetId);
    if ((fd->indexType & DB_FIELD_CASCADE_DELETE)
	&& ((fd->inverseRef->type != dbField::tpArray) ||
	    ((dbVarying*)(rec + fd->inverseRef->dbsOffs))->size <= 1)) 
    { 
	remove(fd->inverseRef->defTable, targetId);
	return;
    } 

    fd = fd->inverseRef;
    if (fd->type == dbField::tpArray) { 
	dbVarying* arr = (dbVarying*)(rec + fd->dbsOffs);
	oid_t* p = (oid_t*)(rec + arr->offs);
	for (int n = arr->size, i = n; --i >= 0;) { 
	    if (p[i] == inverseId) { 
		while (++i < n) { 
		    p[i-1] = p[i];
		}
		arr->size -= 1;
		break;
	    }
	}
    } else { 
	if (*(oid_t*)(rec + fd->dbsOffs) == inverseId) { 
	    *(oid_t*)(rec + fd->dbsOffs) = 0;
	}
    }
}

bool dbDatabase::completeDescriptorsInitialization()
{
    dbTableDescriptor* desc; 
    bool result = true;
    for (desc = tables; desc != NULL; desc = desc->nextDbTable) { 
	dbFieldDescriptor* fd;
	for (fd = desc->firstField; fd != NULL; fd = fd->nextField) { 
	    if (fd->refTableName != NULL) { 
		fd->refTable = findTable(fd->refTableName);
		if (fd->refTable == NULL) { 
		    result = false;
		}
	    }
	}
	desc->checkRelationship();
    }
    return result;
}


bool dbDatabase::backup(char const* file)
{
    dbFile f;
    if (f.create(file) != dbFile::ok) {
	return false;
    }  
    backupCompletedEvent.reset(); 
    cs.enter();
    if (monitor->backupInProgress) { 
	return false; // no two concurrent backups are possible
    }
    monitor->backupInProgress = true;
    cs.leave();
    size_t writtenBytes;
    bool result = f.write(baseAddr, writtenBytes, header->size) == dbFile::ok 
	&& writtenBytes == header->size;
    monitor->backupInProgress = false;
    backupCompletedEvent.signal(); 
    f.close();
    return result;
}

dbDatabase::dbDatabase(dbAccessType type, size_t dbInitSize, 
		       size_t dbExtensionQuantum, size_t dbInitIndexSize,
		       int nThreads
#ifdef NO_PTHREADS
		       , bool
#endif
) : accessType(type), 
  initSize(dbInitSize), 
  extensionQuantum(dbExtensionQuantum),
  initIndexSize(dbInitIndexSize)
{
    bitmapPageAvailableSpace = new int[dbBitmapId + dbBitmapPages];
    setConcurrency(nThreads);
    tables = NULL;
    databaseName = NULL;
    fileName = NULL;
    opened = false;
}      

dbDatabase::~dbDatabase() 
{
    delete[] bitmapPageAvailableSpace;
    delete[] databaseName;
    delete[] fileName;
}

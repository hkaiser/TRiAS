//-< DATABASE.CPP >--------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 14-Jan-99    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Database memory management, query execution, scheme evaluation
//-------------------------------------------------------------------*--------*

#include <ctype.h>
#include <math.h>
#include "gigabase.h"
#include "compiler.h"
#include "hashtab.h"
#include "btree.h"
#include "symtab.h"

dbNullReference null;

char const* const dbMetaTableName = "Metatable";
 
unsigned dbDatabase::dbParallelScanThreshold = 1000;

inline void convertIntToString(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr)
{
    char buf[32];
    iattr.allocateString(sattr, buf, 
			 sprintf(buf, INT8_FORMAT, sattr.ivalue) + 1);
}

inline void convertRealToString(dbInheritedAttribute&   iattr,
				dbSynthesizedAttribute& sattr)
{
    char buf[32];
    iattr.allocateString(sattr, buf, 
			 sprintf(buf, "%f", sattr.fvalue) + 1);
}

static void concatenateStrings(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr,
			       dbSynthesizedAttribute& sattr2)
{
    int len = sattr.array.size + sattr2.array.size - 1;
    if (iattr.sp + len > sizeof(iattr.stack)) { 
	byte* s = new byte[len];
	memcpy(s, sattr.array.base, sattr.array.size - 1);
	memcpy(s + sattr.array.size - 1, sattr2.array.base, sattr2.array.size);
	iattr.free(sattr2);
	iattr.free(sattr);
	iattr.makeDynamic(sattr, s);
    } else { 
	if (sattr2.osClass == dbSynthesizedAttribute::osStack) { 
	    iattr.sp = sattr2.os.sp;
	}
	if (sattr.osClass == dbSynthesizedAttribute::osStack) { 
	    assert(int(iattr.sp) == sattr.os.sp + sattr.array.size);
	    memcpy(iattr.stack + iattr.sp - 1, sattr2.array.base, 
		   sattr2.array.size);
	    iattr.sp += sattr2.array.size-1;
	    if (sattr2.osClass != dbSynthesizedAttribute::osStack) { 
		iattr.free(sattr2);
	    }
	} else { 
	    if (sattr2.osClass == dbSynthesizedAttribute::osStack) { 
		assert(sattr2.array.base == (char*)iattr.stack + iattr.sp);
		memmove(sattr2.array.base + sattr.array.size - 1, 
			sattr2.array.base, sattr2.array.size);
		memcpy(sattr2.array.base,sattr.array.base,sattr.array.size-1);
	    } else { 
		memcpy(iattr.stack + iattr.sp, sattr.array.base, 
		       sattr.array.size - 1);
		memcpy(iattr.stack + iattr.sp + sattr.array.size - 1, 
		       sattr2.array.base, sattr2.array.size);
		iattr.free(sattr2);
	    }
	    iattr.free(sattr);
	    sattr.osClass = dbSynthesizedAttribute::osStack;
	    sattr.os.sp = iattr.sp;
	    iattr.sp += len;
	}
    } 
}

inline int compareStringsForEquality(dbInheritedAttribute&   iattr,
				     dbSynthesizedAttribute& sattr1,
				     dbSynthesizedAttribute& sattr2)
{
    int result = strcmp(sattr1.array.base, sattr2.array.base);
    iattr.free(sattr2);
    iattr.free(sattr1);
    return result;
}

inline int compareStrings(dbInheritedAttribute&   iattr,
			  dbSynthesizedAttribute& sattr1,
			  dbSynthesizedAttribute& sattr2)
{
#ifdef USE_LOCALTE_SETTINGS
    int result = strcoll(sattr1.array.base, sattr2.array.base);
#else
    int result = strcmp(sattr1.array.base, sattr2.array.base);
#endif
    iattr.free(sattr2);
    iattr.free(sattr1);
    return result;
}


inline bool matchStrings(dbInheritedAttribute&   iattr,
			 dbSynthesizedAttribute& sattr1,
			 dbSynthesizedAttribute& sattr2,
			 char escapeChar)
{
    char *str = sattr1.array.base;
    char *pattern = sattr2.array.base;
    char *wildcard = NULL; 
    char *strpos = NULL;
    bool value;
    while (true) { 
	if (*pattern == dbMatchAnySubstring) { 
	    wildcard = ++pattern;
	    strpos = str;
	} else if (*str == '\0') { 
	    value = (*pattern == '\0');
	    break;
	} else if (*pattern == escapeChar && pattern[1] == *str) { 
	    str += 1;
	    pattern += 2;
	} else if (*pattern != escapeChar
		   && (*str == *pattern || *pattern == dbMatchAnyOneChar))
        { 
	    str += 1;
	    pattern += 1;
	} else if (wildcard) { 
	    str = ++strpos;
	    pattern = wildcard;
	} else { 
	    value = false;
	    break;
	}
    }
    iattr.free(sattr2);
    iattr.free(sattr1);
    return value;
}

inline bool matchStrings(dbInheritedAttribute&   iattr,
			 dbSynthesizedAttribute& sattr1,
			 dbSynthesizedAttribute& sattr2)
{
    char *str = sattr1.array.base;
    char *pattern = sattr2.array.base;
    char *wildcard = NULL; 
    char *strpos = NULL;
    bool value;
    while (true) { 
	if (*pattern == dbMatchAnySubstring) { 
	    wildcard = ++pattern;
	    strpos = str;
	} else if (*str == '\0') { 
	    value = (*pattern == '\0');
	    break;
	} else if (*str == *pattern || *pattern == dbMatchAnyOneChar) { 
	    str += 1;
	    pattern += 1;
	} else if (wildcard) { 
	    str = ++strpos;
	    pattern = wildcard;
	} else { 
	    value = false;
	    break;
	}
    }
    iattr.free(sattr2);
    iattr.free(sattr1);
    return value;
}


inline void lowercaseString(dbInheritedAttribute&   iattr,
			    dbSynthesizedAttribute& sattr) 
{ 
    char *src = sattr.array.base;
    if (sattr.osClass == dbSynthesizedAttribute::osStack ||
	sattr.osClass == dbSynthesizedAttribute::osDynamic) 
    { 
	char *dst = src;
	while ((*dst++ = tolower(byte(*src++))) != '\0');
    } else { 	
	char* dst;
	if (iattr.sp + sattr.array.size > sizeof(iattr.stack)) { 
	    dst = new char[sattr.array.size];
	    sattr.array.base = dst;
	    while ((*dst++ = tolower(byte(*src++))) != '\0');
	    iattr.free(sattr);		
	    iattr.makeDynamic(sattr, (byte*)sattr.array.base);
	} else { 
	    dst = (char*)iattr.stack + iattr.sp;
	    sattr.array.base = dst;
	    while ((*dst++ = tolower(byte(*src++))) != '\0');
	    iattr.free(sattr);		
	    sattr.osClass = dbSynthesizedAttribute::osStack;
	    sattr.os.sp = iattr.sp;
	    iattr.sp += sattr.array.size;
	}
    }
}    

inline void uppercaseString(dbInheritedAttribute&   iattr,
			    dbSynthesizedAttribute& sattr) 
{ 
    char *src = sattr.array.base;
    if (sattr.osClass == dbSynthesizedAttribute::osStack ||
	sattr.osClass == dbSynthesizedAttribute::osDynamic) 
    { 
	char *dst = src;
	while ((*dst++ = toupper(byte(*src++))) != '\0');
    } else { 	
	char* dst;
	if (iattr.sp + sattr.array.size > sizeof(iattr.stack)) { 
	    dst = new char[sattr.array.size];
	    sattr.array.base = dst;
	    while ((*dst++ = toupper(byte(*src++))) != '\0');
	    iattr.free(sattr);		
	    iattr.makeDynamic(sattr, (byte*)sattr.array.base);
	} else { 
	    dst = (char*)iattr.stack + iattr.sp;
	    sattr.array.base = dst;
	    while ((*dst++ = toupper(byte(*src++))) != '\0');
	    iattr.free(sattr);		
	    sattr.osClass = dbSynthesizedAttribute::osStack;
	    sattr.os.sp = iattr.sp;
	    iattr.sp += sattr.array.size;
	}
    }
}    

inline void copyString(dbInheritedAttribute&   iattr,
		       dbSynthesizedAttribute& sattr, char* str) 
{ 
    iattr.allocateString(sattr, str);
}    

inline void searchArrayOfBool(dbInheritedAttribute&   iattr,
			      dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    bool *p = (bool*)sattr2.array.base;
    int   n = sattr2.array.size;
    bool  v = (bool)sattr.bvalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    break;
	}
    }
    iattr.free(sattr2);
}

inline void searchArrayOfInt1(dbInheritedAttribute&   iattr,
			      dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int1 *p = (int1*)sattr2.array.base;
    int   n = sattr2.array.size;
    int1  v = (int1)sattr.ivalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    break;
	}
    }
    iattr.free(sattr2);
}

inline void searchArrayOfInt2(dbInheritedAttribute&   iattr,
			      dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int2 *p = (int2*)sattr2.array.base;
    int   n = sattr2.array.size;
    int2  v = (int2)sattr.ivalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    break;
	}
    }
    iattr.free(sattr2);
}

inline void searchArrayOfInt4(dbInheritedAttribute&   iattr,
			      dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int4 *p = (int4*)sattr2.array.base;
    int   n = sattr2.array.size;
    int4  v = (int4)sattr.ivalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    break;
	}
    }
    iattr.free(sattr2);
}

inline void searchArrayOfInt8(dbInheritedAttribute&   iattr,
			      dbSynthesizedAttribute& sattr, 
			      dbSynthesizedAttribute& sattr2)
{
    int8 *p = (int8*)sattr2.array.base;
    int   n = sattr2.array.size;
    int8  v = sattr.ivalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    break;
	}
	p += 1;
    }
    iattr.free(sattr2);
}

inline void searchArrayOfReal4(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr, 
			       dbSynthesizedAttribute& sattr2)
{
    real4* p = (real4*)sattr2.array.base;
    int    n = sattr2.array.size;
    real4  v = (real4)sattr.fvalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p++) { 
	    sattr.bvalue = true;
	    break;
	}
    }
    iattr.free(sattr2);
}

inline void searchArrayOfReal8(dbInheritedAttribute&   iattr,
			       dbSynthesizedAttribute& sattr, 
			       dbSynthesizedAttribute& sattr2)
{
    real8 *p = (real8*)sattr2.array.base;
    int    n = sattr2.array.size;
    real8  v = sattr.fvalue;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    break;
	}
	p += 1;
    }
    iattr.free(sattr2);
}

inline void searchArrayOfReference(dbInheritedAttribute&   iattr,
				   dbSynthesizedAttribute& sattr, 
				   dbSynthesizedAttribute& sattr2)
{
    oid_t *p = (oid_t*)sattr2.array.base;
    int    n = sattr2.array.size;
    oid_t  v = sattr.oid;
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (v == *p) { 
	    sattr.bvalue = true;
	    break;
	}
	p += 1;
    }
    iattr.free(sattr2);
}

inline void searchArrayOfString(dbInheritedAttribute&   iattr,
				dbSynthesizedAttribute& sattr, 
				dbSynthesizedAttribute& sattr2)
{
    dbVarying *p = (dbVarying*)sattr2.array.base;
    int        n = sattr2.array.size;
    char*      str = sattr.array.base;
    char*      base = (char*)sattr2.base; 
    sattr.bvalue = false;
    while (--n >= 0) { 
	if (strcmp(base + p->offs, str) == 0) { 
	    sattr.bvalue = true;
	    break;
	}
	p += 1;
    }
    iattr.free(sattr2);
    iattr.free(sattr);
}

inline void searchInString(dbInheritedAttribute&   iattr,
			   dbSynthesizedAttribute& sattr, 
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
		    iattr.free(sattr2);
		    iattr.free(sattr);
		    return;
		}
	    }
	}
	sattr.bvalue = false;
    } else { 
	sattr.bvalue = strstr(sattr2.array.base, sattr.array.base) != NULL;
    }
    iattr.free(sattr2);
    iattr.free(sattr);
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



bool dbDatabase::evaluate(dbExprNode* expr, oid_t oid, 
			  dbTableDescriptor* table)
{
    dbInheritedAttribute iattr;
    dbSynthesizedAttribute sattr1;
    dbSynthesizedAttribute sattr2;
    iattr.db = this;
    iattr.oid = oid;
    iattr.table = table;
    sattr1.oid = oid;
    iattr.load(sattr1);
    iattr.record = sattr1.base;
    execute(expr, iattr, sattr2);
    iattr.free(sattr1);
    return sattr2.bvalue != 0;
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
	iattr.free(sattr);
	return;
      case dbvmLoadInt1:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int1*)(sattr.base+expr->offs);	
	iattr.free(sattr);
	return;
      case dbvmLoadInt2:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int2*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadInt4:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int4*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadInt8:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = *(int8*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadReal4:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = *(real4*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadReal8:
	execute(expr->operand[0], iattr, sattr);
	sattr.fvalue = *(real8*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadReference:
	execute(expr->operand[0], iattr, sattr);
	sattr.oid = *(oid_t*)(sattr.base+expr->offs);
	iattr.free(sattr);
	return;
      case dbvmLoadArray:
      case dbvmLoadString:
	execute(expr->operand[0], iattr, sattr);
	sattr2.array.base = (char*)sattr.base 
	    + ((dbVarying*)(sattr.base + expr->offs))->offs;
	sattr2.array.size = ((dbVarying*)(sattr.base + expr->offs))->size;
	sattr.array.base = sattr2.array.base;
	sattr.array.size = sattr2.array.size;
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
	sattr.osClass = dbSynthesizedAttribute::osSelf;
	return;

      case dbvmInvokeMethodBool:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.bvalue);
	sattr.bvalue = *(bool*)&sattr.bvalue;
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodInt1:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int1*)&sattr.ivalue;
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodInt2:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int2*)&sattr.ivalue;
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodInt4:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	sattr.ivalue = *(int4*)&sattr.ivalue;
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodInt8:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.ivalue);
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodReal4:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.fvalue); 
	sattr.fvalue = *(real4*)&sattr.fvalue;
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodReal8:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.fvalue);
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodReference:
	execute(expr->ref.base, iattr, sattr);
        expr->ref.field->method->invoke(sattr.base, &sattr.oid);
	iattr.free(sattr);
	return;
      case dbvmInvokeMethodString:
	execute(expr->ref.base, iattr, sattr);
	expr->ref.field->method->invoke(sattr.base, &sattr.array.base);
	iattr.free(sattr);
	sattr.array.size = strlen(sattr.array.base) + 1;
	iattr.makeDynamic(sattr, sattr.array.base); 
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
	expr->ref.field->method->invoke(iattr.record, &sattr.array.base);
	sattr.array.size = strlen(sattr.array.base) + 1;
	iattr.makeDynamic(sattr, sattr.array.base); 
	return;

      case dbvmLength:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = sattr.array.size;
	iattr.free(sattr);
	return;
      case dbvmStringLength:
	execute(expr->operand[0], iattr, sattr);
	sattr.ivalue = sattr.array.size - 1;
	iattr.free(sattr);
	return;

      case dbvmGetAt:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	if ((nat8)sattr2.ivalue >= (nat8)sattr.array.size) { 
	    if (expr->operand[1]->cop == dbvmVariable) { 
		iattr.unwind(expr->operand[1]->offs);
	    }
	    iattr.cleanup();
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
		iattr.unwind(expr->operand[1]->offs);
	    }
	    iattr.cleanup();
	    iattr.db->handleError(IndexOutOfRangeError, NULL, 
				  int(sattr2.ivalue));
	}
	sattr.ivalue = (byte)sattr.array.base[int(sattr2.ivalue)];
	iattr.free(sattr);
	return;

      case dbvmExists:
	iattr.iterator[expr->offs].index = 0;
	iattr.iterator[expr->offs].sp = iattr.sp;
	iattr.iterator[expr->offs].dynChain = iattr.dynChain;
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
	sattr.osClass = dbSynthesizedAttribute::osSelf;
	return;
      case dbvmLoadVarStringPtr:
	sattr.array.base = *(char**)expr->var;
	sattr.array.size = strlen((char*)sattr.array.base) + 1;
	sattr.osClass = dbSynthesizedAttribute::osSelf;
	return;
      case dbvmLoadVarArray:
	sattr.array.base = (char*)((dbAnyArray*)expr->var)->base();
	sattr.array.size = ((dbAnyArray*)expr->var)->length();
	sattr.osClass = dbSynthesizedAttribute::osSelf;
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
	sattr.osClass = dbSynthesizedAttribute::osSelf;
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
	    iattr.cleanup();
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
	    iattr.cleanup();
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
	    iattr.cleanup();
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
	    iattr.cleanup();
	    iattr.db->handleError(ArithmeticError, 
				  "Power operator returns complex result");
	} else if (sattr.fvalue == 0.0 && sattr2.fvalue < 0) { 
	    iattr.cleanup();
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
	    iattr.cleanup();
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
	sattr.bvalue = compareStringsForEquality(iattr, sattr, sattr2) == 0;
	return;
      case dbvmNeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStringsForEquality(iattr, sattr, sattr2) != 0;
	return;
      case dbvmGtString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(iattr, sattr, sattr2) > 0;
	return;
      case dbvmGeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(iattr, sattr, sattr2) >= 0;
	return;
      case dbvmLtString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(iattr, sattr, sattr2) < 0;
	return;
      case dbvmLeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = compareStrings(iattr, sattr, sattr2) <= 0;
	return;
      case dbvmLikeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	sattr.bvalue = matchStrings(iattr, sattr, sattr2);
	return;
      case dbvmLikeEscapeString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	execute(expr->operand[2], iattr, sattr3);
	sattr.bvalue = matchStrings(iattr, sattr, sattr2, *sattr3.array.base);
	return;
      case dbvmBetweenString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
#ifdef USE_LOCALE_SETTINGS
	if (strcoll(sattr.array.base, sattr2.array.base) < 0) { 
	    sattr.bvalue = false;
	} else { 
	    iattr.free(sattr2);
	    execute(expr->operand[2], iattr, sattr2);
	    sattr.bvalue = strcoll(sattr.array.base, sattr2.array.base) <= 0;
	}
#else
	if (strcmp(sattr.array.base, sattr2.array.base) < 0) { 
	    sattr.bvalue = false;
	} else { 
	    iattr.free(sattr2);
	    execute(expr->operand[2], iattr, sattr2);
	    sattr.bvalue = strcmp(sattr.array.base, sattr2.array.base) <= 0;
	}
#endif
	iattr.free(sattr2);
	iattr.free(sattr);
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
	    iattr.cleanup();
	    iattr.db->handleError(NullReferenceError);
	}
	iattr.load(sattr);
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
	iattr.free(sattr);
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
	iattr.free(sattr);
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
	iattr.free(sattr);
	return;
      case dbvmFuncInt2Str:
	execute(expr->operand[0], iattr, sattr);
	sattr.array.base =
	    (*(char*(*)(int8))expr->func.fptr)(sattr.ivalue);
	sattr.array.size = strlen(sattr.array.base) + 1;
	iattr.makeDynamic(sattr, sattr.array.base);
	return;
      case dbvmFuncReal2Str:
	execute(expr->operand[0], iattr, sattr);
	sattr.array.base =
	    (*(char*(*)(real8))expr->func.fptr)(sattr.fvalue);
	sattr.array.size = strlen(sattr.array.base) + 1;
	iattr.makeDynamic(sattr, sattr.array.base);
	return;
      case dbvmFuncStr2Str:
	execute(expr->operand[0], iattr, sattr);
	sattr.array.base = 
	    (*(char*(*)(char const*))expr->func.fptr)(sattr.array.base);
	sattr.array.size = strlen(sattr.array.base) + 1;
	iattr.free(sattr);
	iattr.makeDynamic(sattr, sattr.array.base);
	return;

      case dbvmInArrayBool:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfBool(iattr, sattr, sattr2);	
	return;
      case dbvmInArrayInt1:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt1(iattr, sattr, sattr2);
	return;
      case dbvmInArrayInt2:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt2(iattr, sattr, sattr2);
	return;
      case dbvmInArrayInt4:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt4(iattr, sattr, sattr2);
	return;
      case dbvmInArrayInt8:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfInt8(iattr, sattr, sattr2);
	return;
      case dbvmInArrayReal4:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReal4(iattr, sattr, sattr2);
	return;
      case dbvmInArrayReal8:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReal8(iattr, sattr, sattr2);
	return;
      case dbvmInArrayString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfString(iattr, sattr, sattr2);
	return;
      case dbvmInArrayReference:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchArrayOfReference(iattr, sattr, sattr2);
	return;
      case dbvmInString:
	execute(expr->operand[0], iattr, sattr);
	execute(expr->operand[1], iattr, sattr2);
	searchInString(iattr, sattr, sattr2);
	return;

      default:
	assert(false);
    }
}


void dbDatabase::handleError(dbErrorClass error, char const* msg, int arg)
{
#ifdef THROW_EXCEPTION_ON_ERROR
    throw dbException(error, msg, arg);
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
	fprintf(stderr, "Deadlock is caused by upgrading "
		"shared locks to exclusive");
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
	{ "fields[].bTree", dbField::tpReference, sizeof(oid_t), 
	  offsetof(dbField, bTree)},
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
    setPos(dbMetaTableId, metaTableOffs);
    dbTable* table = (dbTable*)pool.put(metaTableOffs);
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
	field->bTree = 0;
	field += 1;
	offs -= sizeof(dbField);
    }
    pool.unfix(table);
}

bool dbDatabase::open(char const* name)
{
    int rc;
    opened = false;
    writeSem.open();
    readSem.open();
    upgradeSem.open();

    size_t indexSize = initIndexSize < dbFirstUserId 
	? size_t(dbFirstUserId) : initIndexSize;
    indexSize = DOALIGN(indexSize, dbHandlesPerPage);
	    
    memset(dirtyPagesMap, 0, dbDirtyPageBitmapSize+4);
    
    for (int i = dbBitmapId + dbBitmapPages; --i >= 0;) { 
	bitmapPageAvailableSpace[i] = INT_MAX;
    }
    currRBitmapPage = currPBitmapPage = dbBitmapId;
    currRBitmapOffs = currPBitmapOffs = 0;
    inAllocator = 0;
    tables = NULL;
    modified = false;
    concurrentTransId = 1;
    attach();

    monitor.nReaders = 0;
    monitor.nWriters = 0;
    monitor.nWaitReaders = 0;
    monitor.nWaitWriters = 0;
    monitor.waitForUpgrade = false;
    
    int openAttr = (accessType == dbReadOnly) ? dbFile::read_only : 0;
    if (*name == '@') { 
	FILE* f = fopen(name+1, "r");
	if (f == NULL) { 
	    handleError(DatabaseOpenError, 
			"Failed to open database configuration file");
	    return false;
	}
	dbMultiFile::dbSegment segment[dbMaxFileSegments];
	const int maxFileNameLen = 1024;
	char fileName[maxFileNameLen];
	int i, n;
	int8 size;
	for (i=0; (n=fscanf(f, "%s" INT8_FORMAT, fileName, &size)) >= 1; i++) {
	    if (i == dbMaxFileSegments) { 
		while (--i >= 0) delete[] segment[i].name;
		fclose(f);
		handleError(DatabaseOpenError, "Too much segments");
		return false;
	    }
	    if (n == 1) { 
		if (i > 0 && segment[i-1].size == 0) { 
		    while (--i >= 0) delete[] segment[i].name;
		    fclose(f);
		    handleError(DatabaseOpenError, 
				"Segment size was not specified");
		    return false;
		}
		size = 0;
	    } else if (size == 0) { 
		while (--i >= 0) delete[] segment[i].name;
		fclose(f);
		handleError(DatabaseOpenError, "Invalid segment size");
		return false;
	    }
	    segment[i].size = offs_t(size);
	    segment[i].name = new char[strlen(fileName) + 1];
	    strcpy(segment[i].name, fileName);
	}
	fclose(f);
	if (i == 0) { 
	    fclose(f);
	    handleError(DatabaseOpenError, 
			"File should have at least one segment");
	    return false;
	}
	    
	dbMultiFile* mfile = new dbMultiFile;
	rc = mfile->open(i, segment, openAttr);
	while (--i >= 0) delete[] segment[i].name;
	if (rc != dbFile::ok) { 
	    delete mfile;
	    handleError(DatabaseOpenError, "Failed to create database file");
	    return false;
	}
	file = mfile;
    } else {
	file = new dbFile;
	if (file->open(name, openAttr) != dbFile::ok) { 
	    delete file;
	    handleError(DatabaseOpenError, "Failed to create database file");
	    return false;
	}
    }
    memset(header, 0, sizeof(dbHeader));
    rc = file->read(0, header, dbPageSize);
    if (rc != dbFile::ok && rc != dbFile::eof) { 
	delete file;
	handleError(DatabaseOpenError, "Failed to read file header");
	return false;
    }	

    if ((unsigned)header->curr > 1) { 
	delete file;
	handleError(DatabaseOpenError, 
		    "Database file was corrupted: invalid root index");
	return false;
    }
    if (!header->initialized) {
	if (accessType == dbReadOnly) { 
	    delete file;
	    handleError(DatabaseOpenError, "Can not open uninitialized "
			"file in read only moode");
	    return false;
	}
	header->curr = 0;
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
	
	size_t bitmapPages = 
	    (used + dbPageSize*(dbAllocationQuantum*8-1) - 1)
	    / (dbPageSize*(dbAllocationQuantum*8-1));
	size_t bitmapSize = bitmapPages*dbPageSize;
	size_t usedBitmapSize = (used + bitmapSize) / (dbAllocationQuantum*8);
	byte* bitmap = (byte*)dbFile::allocateBuffer(bitmapSize);
	memset(bitmap, 0xFF, usedBitmapSize);
	memset(bitmap + usedBitmapSize, 0, bitmapSize - usedBitmapSize);
	rc = file->write(used, bitmap, bitmapSize);
	dbFile::deallocateBuffer(bitmap);
	if (rc != dbFile::ok) { 
	    delete file;
	    handleError(DatabaseOpenError, "Failed to write to the file");
	    return false;
	}	
	size_t bitmapIndexSize = 
	    DOALIGN((dbBitmapId + dbBitmapPages)*sizeof(offs_t), dbPageSize);
	offs_t* index = (offs_t*)dbFile::allocateBuffer(bitmapIndexSize);
	index[dbInvalidId] = dbFreeHandleFlag;
	size_t i;
	for (i = 0; i < bitmapPages; i++) { 
	    index[dbBitmapId + i] = used | dbPageObjectFlag | dbModifiedFlag;
	    used += dbPageSize;
	}
	header->root[0].bitmapEnd = dbBitmapId + i;
	header->root[1].bitmapEnd = dbBitmapId + i;
	while (i < dbBitmapPages) { 
	    index[dbBitmapId+i] = dbFreeHandleFlag;
	    i += 1;
	}
	rc = file->write(header->root[1].index, index, bitmapIndexSize);
	dbFile::deallocateBuffer(index);
	if (rc != dbFile::ok) { 
	    delete file;
	    handleError(DatabaseOpenError, "Failed to write indx to the file");
	    return false;
	}		
	header->root[0].size = used;
	header->root[1].size = used;
	committedIndexSize = 0;
	currIndexSize = dbFirstUserId;
	if (!pool.open(file, used)) { 
	    handleError(DatabaseOpenError, "Failed to allocate page pool");	    
	}
	initializeMetaTable();
	offs_t indexPage = header->root[1].index;
	offs_t lastIndexPage = 
	    indexPage + header->root[1].bitmapEnd*sizeof(offs_t);
	while (indexPage < lastIndexPage) { 
	    offs_t* p = (offs_t*)pool.put(indexPage);
	    for (i = 0; i < dbHandlesPerPage; i++) { 
		p[i] &= ~dbModifiedFlag;
	    }
	    pool.unfix(p);
	    indexPage += dbPageSize;
	}
	pool.copy(header->root[0].index, header->root[1].index,
		  currIndexSize*sizeof(offs_t));
	header->dirty = true;
	header->root[0].size = header->root[1].size;
	if (file->write(0, header, dbPageSize) != dbFile::ok) { 
	    pool.close();
	    delete file;
	    handleError(DatabaseOpenError, "Failed to write to the file");
	    return false;
	}	
	pool.flush();
	header->initialized = true;
	if (file->write(0, header, dbPageSize) != dbFile::ok ||
	    file->flush() != dbFile::ok) 
	{ 
	    pool.close();
	    delete file;
	    handleError(DatabaseOpenError, 
			"Failed to complete file initialization");
	    return false;
	}	
    } else {
	int curr = header->curr;
	if (header->root[curr].indexSize != header->root[curr].shadowIndexSize)
	{
	    delete file;
	    handleError(DatabaseOpenError, 
			"Header of database file is corrupted");
	    return false;
	}		
	    
	if (rc != dbFile::ok) { 
	    delete file;
	    handleError(DatabaseOpenError, "Failed to read object index");
	    return false;
	}		
	pool.open(file, header->root[curr].size);
	if (header->dirty) { 
	    TRACE_MSG(("Database was not normally closed: start recovery\n"));
	    if (accessType == dbReadOnly) { 
		delete file;
		handleError(DatabaseOpenError,
			    "Can not open dirty file in read only moode");
		return false;
	    }
	    header->root[1-curr].size = header->root[curr].size;
	    header->root[1-curr].indexUsed = header->root[curr].indexUsed; 
	    header->root[1-curr].freeList = header->root[curr].freeList; 
	    header->root[1-curr].index = header->root[curr].shadowIndex;
	    header->root[1-curr].indexSize = 
		header->root[curr].shadowIndexSize;
	    header->root[1-curr].shadowIndex = header->root[curr].index;
	    header->root[1-curr].shadowIndexSize = 
		header->root[curr].indexSize;
	    header->root[1-curr].bitmapEnd = header->root[curr].bitmapEnd;
	    
	    pool.copy(header->root[1-curr].index, header->root[curr].index, 
		      DOALIGN(header->root[curr].indexUsed*sizeof(offs_t), 
			      dbPageSize));
	    restoreTablesConsistency();
	    TRACE_MSG(("Recovery completed\n"));
	} 
    }
    if (!loadScheme()) { 
	pool.close();
	delete file;
	return false;
    }
    opened = true;
    return true;
}


void dbDatabase::restoreTablesConsistency()
{
    //
    // Restore consistency of table rows l2-list 
    //
    dbTable* table = (dbTable*)get(dbMetaTableId);
    oid_t lastId = table->lastRow;
    oid_t tableId = table->firstRow;
    pool.unfix(table);
    if (lastId != 0) { 
	dbRecord* record = (dbRecord*)get(lastId);
	if (record->next != 0) { 
	    pool.modify(record);
	    record->next = 0;
	}
	pool.unfix(record);
    }
    while (tableId != 0) { 
	table = (dbTable*)get(tableId);
	lastId = table->lastRow;
	tableId = table->next;
	pool.unfix(table);
	if (lastId != 0) { 
	    dbRecord* record = (dbRecord*)get(lastId);
	    if (record->next != 0) { 
		pool.modify(record);
		record->next = 0;
	    }
	    pool.unfix(record);
	}
    }
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


bool dbDatabase::loadScheme() 
{
    beginTransaction(accessType != dbReadOnly);
    dbTableDescriptor* desc;
    dbGetTie tie;
    dbTable* metaTable = (dbTable*)get(dbMetaTableId);
    oid_t first = metaTable->firstRow;
    int nTables = metaTable->nRows;
    oid_t tableId = first;
    pool.unfix(metaTable);

    for (desc = dbTableDescriptor::chain; desc != NULL; desc = desc->next) {
	if (desc->db != NULL && desc->db != this) { 
	    continue;
	}
	dbFieldDescriptor* fd;
	for (fd = desc->firstField; fd != NULL; fd = fd->nextField) {
	    fd->bTree = 0;
	    fd->hashTable = 0;
	    fd->attr &= ~dbFieldDescriptor::Updated;
	}
	desc->nRows = 0;
	desc->firstRow = 0;
	desc->lastRow = 0;

	int n = nTables;
	while (--n >= 0) {
	    if (tableId == 0) { 
		tableId = first;	    
	    }
	    dbTable* table = (dbTable*)getRow(tie, tableId);
	    oid_t next = table->next;
	    if (strcmp(desc->name, (char*)table + table->name.offs) == 0) {
		if (!desc->equal(table)) { 
		    modified = true;
		    if (table->nRows == 0) { 
			TRACE_MSG(("Replace definition of table '%s'\n", 
				   desc->name));
			dbGetTie tie;
			dbTable* table = (dbTable*)getRow(tie, tableId);
			updateTableDescriptor(desc, tableId, table);
		    } else { 
			reformatTable(tableId, desc);
		    } 
		} else { 
		    linkTable(desc, tableId);
		}
		break;
	    }
	    tableId = next;
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
	    addIndices(desc);
	}
	desc->checkRelationship();
    }	
    commit();
    return true;
} 


void dbDatabase::reformatTable(oid_t tableId, dbTableDescriptor* desc)
{
    dbGetTie tie;
    dbTable* table = (dbTable*)getRow(tie, tableId);

    if (desc->match(table)) { 
	TRACE_MSG(("New version of table '%s' is compatible with old one\n", 
		   desc->name));
	updateTableDescriptor(desc, tableId, table);
    } else { 
	TRACE_MSG(("Reformat table '%s'\n", desc->name));
	oid_t oid = table->firstRow;
	updateTableDescriptor(desc, tableId, table);
	while (oid != 0) { 
	    dbGetTie getTie;
	    dbPutTie putTie;
	    byte* src = (byte*)getRow(getTie, oid);
	    size_t size = 
		desc->columns->calculateNewRecordSize(src, desc->fixedSize);
	    dbRecord* record = putRow(putTie, oid, size);
	    byte* dst = (byte*)record;
	    desc->columns->convertRecord(dst, src, desc->fixedSize);
	    oid = record->next;
	}
    }
}
 
void dbDatabase::deleteTable(dbTableDescriptor* desc)
{
    beginTransaction(true);
    modified = true;
    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, desc->tableId);
    oid_t rowId = table->firstRow;
    desc->firstRow = desc->lastRow = table->firstRow = table->lastRow = 0;
    desc->nRows = table->nRows = 0;
	
    while (rowId != 0) {
	dbRecord rec;
	getHeader(rec, rowId);

	removeInverseReferences(desc, rowId);
	offs_t pos = getPos(rowId);
	if (pos & dbModifiedFlag) {
	    free(pos & ~dbFlagsMask, rec.size);
	} else { 
	    cloneBitmap(pos, rec.size);
	}
	freeId(rowId);
	rowId = rec.next;
    }
    dbFieldDescriptor* fd;
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) { 
	dbHashTable::purge(this, fd->hashTable);
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	dbBtree::purge(this, fd->bTree);
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

    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].hashTable = 0;
}

void dbDatabase::dropIndex(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbBtree::drop(this, fd->bTree);
    fd->bTree = 0;
    fd->indexType &= ~INDEXED;

    dbFieldDescriptor** fpp = &fd->defTable->indexedFields;
    while (*fpp != fd) { 
	fpp = &(*fpp)->nextIndexedField;
    }
    *fpp = fd->nextIndexedField;

    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, fd->defTable->tableId);
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].bTree = 0;
}

void dbDatabase::createHashTable(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, fd->defTable->tableId);
    int nRows = table->nRows;
    fd->hashTable = dbHashTable::allocate(this, 2*nRows);
    fd->attr &= ~dbFieldDescriptor::Updated;
    fd->nextHashedField = fd->defTable->hashedFields;
    fd->defTable->hashedFields = fd;
    fd->indexType |= HASHED;
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].hashTable = fd->hashTable;

    oid_t oid = table->firstRow; 
    while (oid != 0) { 
	dbRecord rec;
	dbHashTable::insert(this, fd->hashTable, oid, fd->type, fd->dbsOffs,
			    nRows);
	getHeader(rec, oid);
	oid = rec.next;
    }
}


void dbDatabase::createIndex(dbFieldDescriptor* fd)
{
    beginTransaction(true);
    modified = true;
    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, fd->defTable->tableId);
    fd->bTree = dbBtree::allocate(this, fd->type, 
				  (fd->indexType & CASE_INSENSITIVE) != 0); 
    fd->attr &= ~dbFieldDescriptor::Updated;
    fd->nextIndexedField = fd->defTable->indexedFields;
    fd->defTable->indexedFields = fd;
    fd->indexType |= INDEXED;
    dbField* field = (dbField*)((char*)table + table->fields.offs);
    field[fd->fieldNo].bTree = fd->bTree;
    
    oid_t oid = table->firstRow; 
    while (oid != 0) {
	dbRecord rec;
	dbBtree::insert(this, fd->bTree, oid, fd->dbsOffs);
	getHeader(rec, oid);
	oid = rec.next;
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
	dbBtree::drop(this, fd->bTree);
    } 
}


void dbDatabase::addIndices(dbTableDescriptor* desc)
{
    dbFieldDescriptor* fd;
    oid_t tableId = desc->tableId;
    int nRows = desc->nRows;
    oid_t firstId = desc->firstRow;
    int nNewIndices = 0;
    int nDelIndices = 0;
    for (fd = desc->firstField; fd != NULL; fd = fd->nextField) { 
	if ((fd->indexType & HASHED) && fd->type != dbField::tpStructure) { 
	    if (fd->hashTable == 0) { 
		fd->hashTable = dbHashTable::allocate(this, nRows);
		nNewIndices += 1;
		TRACE_MSG(("Create hash table for field '%s'\n", fd->name));
	    }
	} else if (fd->hashTable != 0) { 
	    TRACE_MSG(("Remove hash table for field '%s'\n", fd->name));
	    nDelIndices += 1;
	    fd->hashTable = 0;
	}
	if ((fd->indexType & INDEXED) && fd->type != dbField::tpStructure) { 
	    if (fd->bTree == 0) { 
		fd->bTree = 
		    dbBtree::allocate(this, fd->type, 
				      (fd->indexType & CASE_INSENSITIVE) != 0);
		nNewIndices += 1;
		TRACE_MSG(("Create index for field '%s'\n", fd->name));
	    }
	} else if (fd->bTree != 0) { 
	    nDelIndices += 1;
	    TRACE_MSG(("Remove index for field '%s'\n", fd->name));
	    fd->bTree = 0;
	}
    }
    if (nNewIndices > 0) { 
	dbRecord rec;
	modified = true;
	for (oid_t rowId = firstId; rowId != 0; rowId = rec.next) {
	    for (fd = desc->hashedFields; fd != NULL; fd=fd->nextHashedField) {
		if (getPos(fd->hashTable) & dbModifiedFlag) { 
		    dbHashTable::insert(this, fd->hashTable, rowId, 
					fd->type, fd->dbsOffs, 2*nRows);
		}
	    }
	    for (fd=desc->indexedFields; fd != NULL; fd=fd->nextIndexedField) {
		if (getPos(fd->bTree) & dbModifiedFlag) { 
		    dbBtree::insert(this, fd->bTree, rowId, fd->dbsOffs);
		}
	    }
	    getHeader(rec, rowId);
	} 
    }
    if (nNewIndices + nDelIndices != 0) { 
	dbPutTie tie;
	dbTable* table = (dbTable*)putRow(tie, tableId);
	dbField* field = (dbField*)((byte*)table + table->fields.offs);    
	for (fd = desc->firstField; fd != NULL; fd = fd->nextField) { 
	    if (field->hashTable != fd->hashTable) { 
		if (field->hashTable != 0) { 
		    assert(fd->hashTable == 0);
		    modified = true;
		    dbHashTable::drop(this, field->hashTable);
		}
		field->hashTable = fd->hashTable;
	    }
	    if (field->bTree != fd->bTree) { 
		if (field->bTree != 0) { 
		    assert(fd->bTree == 0);
		    modified = true;
		    dbBtree::drop(this, field->bTree);
		}
		field->bTree = fd->bTree;
	    }
	    field += 1;
	}
    }
}

 
void dbDatabase::updateTableDescriptor(dbTableDescriptor* desc, 
				       oid_t tableId, dbTable* table)
{
    dbFieldDescriptor* fd;
    size_t newSize = sizeof(dbTable) + desc->nFields*sizeof(dbField)
	+ desc->totalNamesLength();
    linkTable(desc, tableId);
    
    int nFields = table->fields.size;

    dbField* field = (dbField*)((byte*)table + table->fields.offs);

    while (--nFields >= 0) { 
	oid_t hashTableId = field->hashTable;
	oid_t bTreeId = field->bTree;
	if (hashTableId != 0) { 
	    for (fd = desc->hashedFields; 
		 fd != NULL && fd->hashTable != hashTableId;
		 fd = fd->nextHashedField);
	    if (fd == NULL) { 
		dbHashTable::drop(this, hashTableId);
	    }
	} 
	if (bTreeId != 0) { 
	    for (fd = desc->indexedFields; 
		 fd != NULL && fd->bTree != bTreeId;
		 fd = fd->nextIndexedField);
	    if (fd == NULL) { 
		dbBtree::drop(this, bTreeId);
	    }
	}
	field += 1;
    } 

    dbPutTie tie;
    desc->storeInDatabase((dbTable*)putRow(tie, tableId, newSize));

}

oid_t dbDatabase::addNewTable(dbTableDescriptor* desc)
{
    oid_t tableId = allocateRow(dbMetaTableId, 
				sizeof(dbTable) + desc->nFields*sizeof(dbField)
				+ desc->totalNamesLength());
    linkTable(desc, tableId);
    dbPutTie tie;
    desc->storeInDatabase((dbTable*)putRow(tie, tableId));
    return tableId;
}



void dbDatabase::close()
{
    detach();
    opened = false;
    if (header->dirty) { 
	int rc = file->write(0, header, dbPageSize);
	if (rc != dbFile::ok) { 
	    handleError(FileError, "Failed to write header to the disk", rc);
	}
	pool.flush();
	header->dirty = false;
	rc = file->write(0, header, dbPageSize);
	if (rc != dbFile::ok) { 
	    handleError(FileError, "Failed to write header to the disk", rc);
	}
    }
    for (dbTableDescriptor* desc=tables; desc != NULL; desc=desc->nextDbTable){
	desc->tableId = 0;
	if (!desc->fixedDatabase) { 
	    desc->db = NULL;
	}
    }
    pool.close();
    delete file;
    readSem.close();
    writeSem.close();
    upgradeSem.close();
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
    dbGetTie tie;
    while (expr->cop == dbvmGetAt || expr->cop == dbvmDeref ||
	   (expr->cop == dbvmLoadReference 
	    && (expr->ref.field->attr & dbFieldDescriptor::ComponentOfArray))) 
    { 
	expr = expr->operand[0]; 	
    } 
    dbTableDescriptor* table = &cursor->table;
    dbFieldDescriptor* fd = expr->ref.field->inverseRef;
    if (fd->type == dbField::tpArray) { 
	byte* rec = (byte*)getRow(tie, iref);
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
	oid_t oid = *(oid_t*)((byte*)getRow(tie, iref) + fd->dbsOffs);
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

    if (loadCop - dbvmLoadSelfBool > dbvmLoadSelfString - dbvmLoadSelfBool
	&& loadCop - dbvmLoadBool > dbvmLoadString - dbvmLoadBool)
    {
	return false;
    }
    dbFieldDescriptor* field = expr->operand[0]->ref.field;
    if (field->hashTable == 0 && field->bTree == 0) { 
	return false;
    }
    if (loadCop >= dbvmLoadSelfBool) { 
	if (isIndexApplicable(cursor, expr, andExpr)) { 
	    indexedField = field;
	    return true;
	}
    } 
    else if (existsInverseReference(expr->operand[0]->ref.base,nExistsClauses))
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
    sc.offs = field->dbsOffs;
    sc.cursor = cursor;
    sc.condition = andExpr ? andExpr->operand[1] : (dbExprNode*)0;
    sc.probes = 0;

    switch (expr->cop) { 
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
	    dbBtree::find(this, field->bTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	}
	return true;
      case dbvmGtInt:
      case dbvmGtReal:
      case dbvmGtString:
	if (field->bTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKey = NULL;
	    sc.firstKeyInclusion = false;
	    dbBtree::find(this, field->bTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmGeInt:
      case dbvmGeReal:
      case dbvmGeString:
	if (field->bTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKey = NULL;
	    sc.firstKeyInclusion = true;
	    dbBtree::find(this, field->bTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLtInt:
      case dbvmLtReal:
      case dbvmLtString:
	if (field->bTree != 0) {
	    sc.firstKey = NULL;
	    sc.lastKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKeyInclusion = false;
	    dbBtree::find(this, field->bTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLeInt:
      case dbvmLeReal:
      case dbvmLeString:
	if (field->bTree != 0) {
	    sc.firstKey = NULL;
	    sc.lastKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.lastKeyInclusion = true;
	    dbBtree::find(this, field->bTree, sc);
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
	} else if (field->bTree != 0) {
	    sc.firstKey = strop ? literal[0].s : (char*)&literal[0];
	    sc.firstKeyInclusion = true;
	    sc.lastKey = strop ? literal[1].s : (char*)&literal[1];
	    sc.lastKeyInclusion = true;
	    dbBtree::find(this, field->bTree, sc);
	    TRACE_MSG(("Index search for field %s.%s: %d probes\n", 
		       field->defTable->name, field->longName, sc.probes)); 
	    return true;
	} 
	return false;
      case dbvmLikeString:
      case dbvmLikeEscapeString:
	if ((s = findWildcard(literal[0].s, literal[1].s)) == NULL 
	    || ((s[1] == '\0' || s != literal[0].s) && field->bTree != 0))
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
		    dbBtree::find(this, field->bTree, sc);
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
		    dbBtree::find(this, field->bTree, sc);
		    TRACE_MSG(("Use index for ordering records "
			       "by field %s.%s\n", field->defTable->name, 
			       field->longName)); 
		} else { 	    
		    char* firstKey = new char[len+1];
		    sc.firstKey = firstKey;
		    memcpy(firstKey, literal[0].s, len);
		    firstKey[len] = '\0';
		    sc.firstKeyInclusion = true;
		    char* lastKey = new char[len+4];
		    sc.lastKey = lastKey;
		    memcpy(lastKey, literal[0].s, len);
		    if ((byte)lastKey[len-1] != 0xFF) { 
			lastKey[len-1] += 1;
			lastKey[len] = '\0';
			sc.lastKeyInclusion = false;
		    } else { 
			lastKey[len] = (char)0xFF;
			lastKey[len+1] = (char)0xFF;
			lastKey[len+2] = (char)0xFF;
			lastKey[len+3] = '\0';
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
				dbBtree::find(this, field->bTree, sc);
				like.cop = dbvmVoid;// do not destruct operands
			    } else { 
				sc.condition = expr;
				dbBtree::find(this, field->bTree, sc);
			    }
			} else { 
			    sc.condition = andExpr;
			    dbBtree::find(this, field->bTree, sc);
			}
		    } else { 
			dbBtree::find(this, field->bTree, sc);
		    }
		    TRACE_MSG(("Index search for prefix in LIKE expression "
			       "for field %s.%s: %d probes\n", 
			       field->defTable->name, field->longName, 
			       sc.probes));
		    delete[] firstKey;
		    delete[] lastKey;
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
    dbTableDescriptor* table = &cursor->table;

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
    dbGetTie tie;

    while (sp != 0) { 
	oid_t curr = stack[--sp];
	if (condition->cop == dbvmVoid || evaluate(condition, curr, table)) {
	    if (!cursor->add(curr)) { 
		break;
	    }
	} else { 
	    cursor->mark(curr);
	}
	byte* record = (byte*)getRow(tie, curr);
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
	if (!query.compiled() || &cursor->table != query.table) { 
	    if (!ctx->compiler.compile(&cursor->table, query)) { 
		return;
	    }
	}
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
    ctx->cursors.link(cursor);

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
	&& query.order->field->bTree != 0) 
    { 
	dbFieldDescriptor* field = query.order->field;
	TRACE_MSG(("Use index for ordering records by field %s.%s\n", 
		   query.table->name, field->longName)); 
	if (condition->cop == dbvmVoid) { 
	    if (query.order->ascent) { 
		dbBtree::traverseForward(this, field->bTree, cursor); 
	    } else { 
		dbBtree::traverseBackward(this, field->bTree, cursor);
	    }
	} else { 
	    if (query.order->ascent) { 
		dbBtree::traverseForward(this,field->bTree,cursor,condition); 
	    } else { 
		dbBtree::traverseBackward(this,field->bTree,cursor,condition);
	    }
	}
	return;
    }

    dbTableDescriptor* table = &cursor->table;
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
	    dbGetTie  tie[dbMaxParallelSearchThreads];
	    for (i = 0; i <= n; i++) { 
		if (par.selection[i].first != NULL) { 
		    rec[i] = getRow(tie[i], par.selection[i].first->rows[0]);
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
		rec[min] = getRow(tie[min], oid);
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
		dbRecord rec;
		if (evaluate(condition, oid, table)) { 
		    if (!cursor->add(oid)) { 
			break;
		    }
		}
		getHeader(rec, oid);
		oid = rec.next;
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
    cursor->firstId = cursor->table.firstRow;
    cursor->lastId = cursor->table.lastRow;
    cursor->selection.nRows = cursor->table.nRows;
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
	dbBtree::remove(this, fd->bTree, delId, fd->dbsOffs);
    }
    freeRow(desc->tableId, delId, desc);
}

dbRecord* dbDatabase::putRow(dbPutTie& tie, oid_t oid) { 
    offs_t pos = getPos(oid);
    int offs = (int)pos & (dbPageSize-1);
    byte* p = pool.get(pos - offs);
    dbRecord* rec = (dbRecord*)(p + (offs & ~dbFlagsMask));
    if (!(offs & dbModifiedFlag)) { 
	dirtyPagesMap[size_t(oid/dbHandlesPerPage/32)] 
	    |= 1 << int(oid/dbHandlesPerPage & 31);
	cloneBitmap(pos & ~dbFlagsMask, rec->size);
	allocate(rec->size, oid);
	pos = getPos(oid);
    }
    tie.set(pool, pos & ~dbFlagsMask, rec->size);
    pool.unfix(p);
    return (dbRecord*)tie.get(); 
}

byte* dbDatabase::put(dbPutTie& tie, oid_t oid) { 
    offs_t pos = getPos(oid);
    if (!(pos & dbModifiedFlag)) { 
	dirtyPagesMap[size_t(oid/dbHandlesPerPage/32)] 
	    |= 1 << int(oid/dbHandlesPerPage & 31);
	allocate(dbPageSize, oid);
	cloneBitmap(pos & ~dbFlagsMask, dbPageSize);
	pos = getPos(oid);
    }
    tie.set(pool, pos & ~dbFlagsMask, dbPageSize);
    return tie.get(); 
}


dbRecord* dbDatabase::putRow(dbPutTie& tie, oid_t oid, size_t newSize) 
{  
    offs_t pos = getPos(oid);
    int offs = (int)pos & (dbPageSize-1);
    byte* p = pool.get(pos - offs);
    dbRecord* rec = (dbRecord*)(p + (offs & ~dbFlagsMask));
    if (!(offs & dbModifiedFlag)) { 
	dirtyPagesMap[size_t(oid/dbHandlesPerPage/32)] 
	    |= 1 << int(oid/dbHandlesPerPage & 31);
	cloneBitmap(pos, rec->size);
	pos = allocate(newSize);
	setPos(oid, pos | dbModifiedFlag);
    } else { 
	if (rec->size != newSize) {
	    offs_t newPos = allocate(newSize);
	    cloneBitmap(pos & ~dbFlagsMask, rec->size);
	    free(pos & ~dbFlagsMask, rec->size);
	    pos = newPos;
	    setPos(oid, pos | dbModifiedFlag);
	}
    }
    tie.set(pool, pos & ~dbFlagsMask, newSize);
    dbRecord* record = (dbRecord*)tie.get();
    record->next = rec->next;
    record->prev = rec->prev;
    record->size = newSize;
    pool.unfix(p);
    return record;
}

oid_t dbDatabase::allocateRow(oid_t tableId, size_t size, 
			      dbTableDescriptor* desc) 
{ 
    dbPutTie rTie, tTie;
    oid_t oid = allocateId();
    offs_t pos = allocate(size); 
    setPos(oid, pos | dbModifiedFlag);
    dbTable* table = (dbTable*)putRow(tTie, tableId);
    rTie.set(pool, pos, size);
    dbRecord* record = (dbRecord*)rTie.get();
    record->size = size;
    record->next = 0;
    record->prev = table->lastRow;
    if (table->lastRow != 0) { 
	//
	// Optimisation hack: avoid cloning of the last record. 
	// Possible inconsistency in L2-list will be eliminated by recovery
	// procedure.
	//
	dbRecord* rec = (dbRecord*)put(table->lastRow);
	rec->next = oid;
	pool.unfix(rec);
    } else { 
	table->firstRow = oid;
	if (desc != NULL) { 
	    desc->firstRow = oid;
	}
    }
    table->lastRow = oid;
    table->nRows += 1;
    if (desc != NULL) { 
	desc->lastRow = oid;
	desc->nRows += 1;
	assert(table->nRows == desc->nRows);
    }
    return oid;
}


void dbDatabase::freeRow(oid_t tableId, oid_t oid, dbTableDescriptor* desc)
{
    dbPutTie tie;
    dbTable* table = (dbTable*)putRow(tie, tableId);
    dbRecord rec;
    getHeader(rec, oid);
    table->nRows -= 1;
    if (rec.prev == 0) {
	table->firstRow = rec.next;
    } else { 
	dbPutTie tie;
	putRow(tie, rec.prev)->next = rec.next;
    }
    if (rec.next == 0) {
	table->lastRow = rec.prev;
    } else { 
	dbPutTie tie;
	putRow(tie, rec.next)->prev = rec.prev;
    }
    offs_t pos = getPos(oid);
    if (pos & dbModifiedFlag) { 
	free(pos & ~dbFlagsMask, rec.size);
    } else { 
	cloneBitmap(pos, rec.size);
    }
    if (desc != NULL) { 
	desc->nRows = table->nRows;
	desc->firstRow = table->firstRow;
	desc->lastRow = table->lastRow;
    }
    freeId(oid);
}

void dbDatabase::freePage(oid_t oid) 
{ 
    offs_t pos = getPos(oid);
    if (pos & dbModifiedFlag) { 
	free(pos & ~dbFlagsMask, dbPageSize);
    } else { 
	cloneBitmap(pos & ~dbFlagsMask, dbPageSize);
    } 
    freeId(oid);
}
 

void dbDatabase::update(oid_t oid, dbTableDescriptor* desc, void const* record)
{
    size_t size = 
	desc->columns->calculateRecordSize((byte*)record, desc->fixedSize);

    byte* src = (byte*)record;
    dbGetTie getTie;
    byte* old = (byte*)getRow(getTie, oid);
    desc->columns->markUpdatedFields(old, src);

    dbFieldDescriptor* fd;
    updatedRecordId = oid;
    for (fd = desc->inverseFields; fd != NULL; fd = fd->nextInverseField) { 
	if (fd->type == dbField::tpArray) { 
	    dbAnyArray* arr = (dbAnyArray*)(src + fd->appOffs);
	    int n = arr->length();
	    oid_t* newrefs = (oid_t*)arr->base();

	    int m = ((dbVarying*)(old + fd->dbsOffs))->size;
	    int offs =  ((dbVarying*)(old + fd->dbsOffs))->offs;
	    int i, j, k;

	    if (fd->indexType & DB_FIELD_CASCADE_DELETE) { 
		for (i = 0, k = 0; i < m; i++) { 
		    oid_t oldref = *(oid_t*)(old + offs); 
		    offs += sizeof(oid_t);
		    for (j = i; j < n && newrefs[j] != oldref; j++);
		    if (j >= n) { 
			j = i < n ? i : n; 
			while (--j >= 0 && newrefs[j] != oldref);
			if (j < 0) {
			    k += 1;
			    removeInverseReference(fd, oid, oldref);
			}
		    }
		} 
		if (n != m - k) { 
		    oid_t* oldrefs = (oid_t*)(old + offs) - m;
		    for (i = 0; i < n; i++) { 
			for (j = 0; j < m && newrefs[i] != oldrefs[j]; j++);
			if (j == m) { 
			    insertInverseReference(fd, oid, newrefs[i]);
			}
		    }
		}
	    } else { 
		k = n < m ? n : m;
		for (i = 0; i < k; i++) {
		    oid_t oldref = *(oid_t*)(old + offs); 
		    offs += sizeof(oid_t);
		    if (newrefs[i] != oldref) {
			if (oldref != 0) { 
			    removeInverseReference(fd, oid, oldref);
			}
			if (newrefs[i] != 0) { 
			    insertInverseReference(fd, oid, newrefs[i]);
			}
		    }
		}
		while (i < m) { 
		    oid_t oldref = *(oid_t*)(old + offs); 
		    offs += sizeof(oid_t);
		    if (oldref != 0) { 
			removeInverseReference(fd, oid, oldref);
		    }
		    i += 1;
		} 
		while (i < n) { 
		    if (newrefs[i] != 0) { 
			insertInverseReference(fd, oid, newrefs[i]);
		    }
		    i += 1;
		}
	    }
	} else { 
	    oid_t newref = *(oid_t*)(src + fd->appOffs);
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
    updatedRecordId = 0;

    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbHashTable::remove(this,fd->hashTable,oid,fd->type,fd->dbsOffs);
	}
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbBtree::remove(this, fd->bTree, oid, fd->dbsOffs);
	}
    }

    {
	dbPutTie putTie;
	byte* dst = (byte*)putRow(putTie, oid, size);    
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
    }

    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbHashTable::insert(this,fd->hashTable,oid,fd->type,fd->dbsOffs,0);
	}
    } 
    for (fd = desc->indexedFields; fd != NULL; fd = fd->nextIndexedField) { 
	if (fd->attr & dbFieldDescriptor::Updated) { 
	    dbBtree::insert(this, fd->bTree, oid, fd->dbsOffs);
	    fd->attr &= ~dbFieldDescriptor::Updated;
	}
    }
    for (fd = desc->hashedFields; fd != NULL; fd = fd->nextHashedField) {
	fd->attr &= ~dbFieldDescriptor::Updated;	
    }
}


void dbDatabase::insert(dbTableDescriptor* desc, dbAnyReference* ref, 
			void const* record) 
{ 
    assert(opened);
    beginTransaction(true);
    modified = true;
    byte* src = (byte*)record;
    size_t size = desc->columns->calculateRecordSize(src, desc->fixedSize);

    oid_t oid = allocateRow(desc->tableId, size, desc);
    ref->oid = oid;
    {
	dbPutTie tie;
	byte* dst = (byte*)putRow(tie, oid);    
        desc->columns->storeRecordFields(dst, src, desc->fixedSize);
    }

    int nRows = desc->nRows;
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
	dbBtree::insert(this, fd->bTree, oid, fd->dbsOffs);
    }
}


inline void dbDatabase::extend(offs_t size)
{
    if (size > header->root[1-header->curr].size) { 
	header->root[1-header->curr].size = size;
    }
}

offs_t dbDatabase::used() { 
    oid_t lastPage = header->root[1-header->curr].bitmapEnd;
    int setbits = 0;
    for (oid_t page = dbBitmapId; page < lastPage; page++) { 
	byte* p = get(page);
	for (size_t i = 0; i < dbPageSize; i++) { 
	    byte mask = p[i];
	    while (mask != 0) { 
		if (mask & 1) { 
		    setbits += 1;
		}
		mask >>= 1;
	    }
	}
	pool.unfix(p);
    }
    return setbits*dbAllocationQuantum;
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
    int holeBeforeFreePage = 0;
    int holeBitSize = 0;
    register int alignment = size & (dbPageSize-1);
    register size_t offs;
    const int pageBits = dbPageSize*8;
    oid_t firstPage;
    oid_t lastPage = header->root[1-header->curr].bitmapEnd;
    dbPutTie tie;
    oid_t i, freePage = 0;
    const size_t inc = dbPageSize/dbAllocationQuantum/8;

    inAllocator += 1;
    if (alignment == 0) { 
	firstPage = currPBitmapPage;
	offs = DOALIGN(currPBitmapOffs, inc);
    } else { 
	firstPage = currRBitmapPage;
	offs = currRBitmapOffs;
    }
	
    while (true) { 
	if (alignment == 0) { 
	    // allocate page object 
	    for (i = firstPage; i < lastPage; i++){
		int spaceNeeded = objBitSize - holeBitSize < pageBits 
		    ? objBitSize - holeBitSize : pageBits;
		if (bitmapPageAvailableSpace[i] <= spaceNeeded) {
		    holeBitSize = 0;
		    offs = 0;
		    continue;
		}
		register byte* begin = get(i);
		size_t startOffs = offs;	
		while (offs < dbPageSize) { 
		    if (begin[offs++] != 0) { 
			offs = DOALIGN(offs, inc);
			holeBitSize = 0;
		    } else if ((holeBitSize += 8) == objBitSize) { 
			currPBitmapPage = i;
			currPBitmapOffs = offs;
			pos = ((offs_t(i-dbBitmapId)*dbPageSize + offs)*8 
			       - holeBitSize) << dbAllocationQuantumBits;
			extend(pos + size);
			if (oid != 0) { 
			    offs_t prev = getPos(oid);
			    int marker = (int)prev & dbFlagsMask;
			    pool.copy(pos, prev - marker, size);
			    setPos(oid, pos | marker | dbModifiedFlag);
			}
			pool.unfix(begin);
			begin = put(tie, i);
			size_t holeBytes = holeBitSize >> 3;
			if (holeBytes > offs) { 
			    memset(begin, 0xFF, offs);
			    holeBytes -= offs;
			    begin = put(tie, --i);
			    offs = dbPageSize;
			}
			while (holeBytes > dbPageSize) { 
			    memset(begin, 0xFF, dbPageSize);
			    holeBytes -= dbPageSize;
			    bitmapPageAvailableSpace[i] = 0;
			    begin = put(tie, --i);
			}
			memset(&begin[offs-holeBytes], 0xFF, holeBytes);
			inAllocator -= 1;
			return pos;
		    }
		}
		if (startOffs == 0 && holeBitSize == 0
		    && spaceNeeded < bitmapPageAvailableSpace[i]) 
		{ 
		    bitmapPageAvailableSpace[i] = spaceNeeded;
		}
		offs = 0;
		pool.unfix(begin);
	    }
	} else { 
	    for (i = firstPage; i < lastPage; i++){
		int spaceNeeded = objBitSize - holeBitSize < pageBits 
		    ? objBitSize - holeBitSize : pageBits;
		if (bitmapPageAvailableSpace[i] <= spaceNeeded) {
		    holeBitSize = 0;
		    offs = 0;
		    continue;
		}
		register byte* begin = get(i);
		size_t startOffs = offs;
		while (offs < dbPageSize) { 
		    int mask = begin[offs]; 
		    if (holeBitSize + firstHoleSize[mask] >= objBitSize) { 
			currRBitmapPage = i;
			currRBitmapOffs = offs;
			if (i > currPBitmapPage ||
			    (i == currPBitmapPage && offs >= currPBitmapOffs))
			{
			    currPBitmapPage = i;
			    currPBitmapOffs = offs + 1; 
			}
			pos = ((offs_t(i-dbBitmapId)*dbPageSize + offs)*8 
			       - holeBitSize) << dbAllocationQuantumBits;
			extend(pos + size);
			if (oid != 0) { 
			    offs_t prev = getPos(oid);
			    int marker = (int)prev & dbFlagsMask;
			    pool.copy(pos, prev - marker, size);
			    setPos(oid, pos | marker | dbModifiedFlag);
			}
			pool.unfix(begin);
			begin = put(tie, i);
			begin[offs] |= (1 << (objBitSize - holeBitSize)) - 1; 
			if (holeBitSize != 0) { 
			    if (size_t(holeBitSize) > offs*8) { 
				memset(begin, 0xFF, offs);
				holeBitSize -= offs*8;
				begin = put(tie, --i);
				offs = dbPageSize;
			    }
			    while (holeBitSize > pageBits) { 
				memset(begin, 0xFF, dbPageSize);
				holeBitSize -= pageBits;
				bitmapPageAvailableSpace[i] = 0;
				begin = put(tie, --i);
			    }
			    while ((holeBitSize -= 8) > 0) { 
				begin[--offs] = 0xFF; 
			    }
			    begin[offs-1] |= ~((1 << -holeBitSize) - 1);
			}
			inAllocator -= 1;
			return pos;
		    } else if (maxHoleSize[mask] >= objBitSize) { 
			int holeBitOffset = maxHoleOffset[mask];
			currRBitmapPage = i;
			currRBitmapOffs = offs;
			if (i > currPBitmapPage ||
			    (i == currPBitmapPage && offs >= currPBitmapOffs))
			{
			    currPBitmapPage = i;
			    currPBitmapOffs = offs + 1; 
			}
			pos = ((offs_t(i-dbBitmapId)*dbPageSize + offs)*8 + 
			       holeBitOffset) << dbAllocationQuantumBits;
			extend(pos + size);
			if (oid != 0) { 
			    offs_t prev = getPos(oid);
			    int marker = (int)prev & dbFlagsMask;
			    pool.copy(pos, prev - marker, size);
			    setPos(oid, pos | marker | dbModifiedFlag);
			}
			pool.unfix(begin);
			begin = put(tie, i);
			begin[offs] |= ((1<<objBitSize) - 1) << holeBitOffset;
			inAllocator -= 1;
			return pos;
		    }
		    offs += 1;
		    if (lastHoleSize[mask] == 8) { 
			holeBitSize += 8;
		    } else { 
			holeBitSize = lastHoleSize[mask];
		    }
		}
		if (startOffs == 0 && holeBitSize == 0
		    && spaceNeeded < bitmapPageAvailableSpace[i]) 
		{
		    bitmapPageAvailableSpace[i] = spaceNeeded;
		}
		offs = 0;
		pool.unfix(begin);
	    }
	}
	if (firstPage == dbBitmapId || inAllocator > 1) { 
	    if (freePage > i) { 
		i = freePage;
		holeBitSize = holeBeforeFreePage;
	    }
	    if (i ==  dbBitmapId + dbBitmapPages) { 
		handleError(OutOfMemoryError, NULL, size);
	    }
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
	    pos = (offs_t(i-dbBitmapId) 
		   << (dbPageBits+dbAllocationQuantumBits+3)) 
		  + (skip << dbAllocationQuantumBits);
	    extend(pos + morePages*dbPageSize);
	    size_t len = objBitSize >> 3;
	    offs_t adr = pos;
	    byte* p;
	    while (len >= dbPageSize) { 
		p = pool.put(adr);
		memset(p, 0xFF, dbPageSize);
		pool.unfix(p);
		adr += dbPageSize;
		len -= dbPageSize;
	    }
	    p = pool.put(adr);
	    memset(p, 0xFF, len);
	    p[len] = (1 << (objBitSize&7))-1;
	    pool.unfix(p);
	    adr = pos + (skip>>3);
	    len = morePages * (dbPageSize/dbAllocationQuantum/8);
	    while (true) { 
		int off = (int)adr & (dbPageSize-1);
		p = pool.put(adr - off);
		if (dbPageSize - off >= len) { 
		    memset(p + off, 0xFF, len);
		    pool.unfix(p);
		    break;
		} else { 
		    memset(p + off, 0xFF, dbPageSize - off);
		    pool.unfix(p);
		    adr += dbPageSize - off;
		    len -= dbPageSize - off;
		}
	    }
	    oid_t j = i;
	    while (--morePages >= 0) { 
		dirtyPagesMap[size_t(j/dbHandlesPerPage/32)] 
		    |= 1 << int(j/dbHandlesPerPage & 31);
		setPos(j++, pos | dbPageObjectFlag | dbModifiedFlag);
		pos += dbPageSize;
	    }
	    header->root[1-header->curr].bitmapEnd = j;
	    j = i + objBitSize / pageBits; 
	    currPBitmapPage = j;
	    currPBitmapOffs = 0;
	    if (alignment != 0) { 
		currRBitmapPage = j;
		currRBitmapOffs = 0;
	    }
	    while (j > i) { 
		bitmapPageAvailableSpace[size_t(--j)] = 0;
	    }
	    
	    pos = (offs_t(i-dbBitmapId)*dbPageSize*8 - holeBitSize)
		<< dbAllocationQuantumBits;
	    if (oid != 0) { 
		offs_t prev = getPos(oid);
		int marker = (int)prev & dbFlagsMask;
		pool.copy(pos, prev - marker, size);
		setPos(oid, pos | marker | dbModifiedFlag);
	    }

	    if (holeBitSize != 0) { 
		while (holeBitSize > pageBits) { 
		    holeBitSize -= pageBits;
		    byte* p = put(tie, --i);
		    memset(p, 0xFF, dbPageSize);
		    bitmapPageAvailableSpace[i] = 0;
		}
		byte* cur = (byte*)put(tie, --i) + dbPageSize;
		while ((holeBitSize -= 8) > 0) { 
		    *--cur = 0xFF; 
		}
		*(cur-1) |= ~((1 << -holeBitSize) - 1);
	    }
	    inAllocator -= 1;
	    return pos;
	} 
	freePage = i;
	holeBeforeFreePage = holeBitSize;
	holeBitSize = 0;
	lastPage = firstPage;
	firstPage = dbBitmapId;
	offs = 0;
    }
} 

void dbDatabase::free(offs_t pos, size_t size)
{
    assert(pos != 0 && (pos & (dbAllocationQuantum-1)) == 0);
    dbPutTie tie;
    offs_t quantNo = pos / dbAllocationQuantum;
    int    objBitSize = (size+dbAllocationQuantum-1) / dbAllocationQuantum;
    oid_t  pageId = dbBitmapId + oid_t(quantNo / (dbPageSize*8));
    size_t offs = (size_t(quantNo) & (dbPageSize*8-1)) >> 3;
    byte*  p = put(tie, pageId) + offs;
    int    bitOffs = int(quantNo) & 7;

    if (pageId == currRBitmapPage && offs < currRBitmapOffs) { 
	currRBitmapOffs = offs;
    }

    bitmapPageAvailableSpace[pageId] = INT_MAX;
 
    if (objBitSize > 8 - bitOffs) { 
	objBitSize -= 8 - bitOffs;
	*p++ &= (1 << bitOffs) - 1;
	offs += 1;
	while (objBitSize + offs*8 > dbPageSize*8) { 
	    memset(p, 0, dbPageSize - offs);
	    p = put(tie, ++pageId);
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
    offs_t quantNo = pos / dbAllocationQuantum;
    int    objBitSize = (size+dbAllocationQuantum-1) / dbAllocationQuantum;
    oid_t  pageId = dbBitmapId + oid_t(quantNo / (dbPageSize*8));
    size_t offs = (size_t(quantNo) & (dbPageSize*8-1)) >> 3;
    int    bitOffs = int(quantNo) & 7;
    oid_t  oid = pageId;
    pos = getPos(oid);
    if (!(pos & dbModifiedFlag)) { 
	dirtyPagesMap[size_t(oid / dbHandlesPerPage / 32)] 
	    |= 1 << (int(oid / dbHandlesPerPage) & 31);
	allocate(dbPageSize, oid);
	cloneBitmap(pos & ~dbFlagsMask, dbPageSize);
    }

    if (objBitSize > 8 - bitOffs) { 
	objBitSize -= 8 - bitOffs;
	offs += 1;
	while (objBitSize + offs*8 > dbPageSize*8) { 
	    oid = ++pageId;
	    pos = getPos(oid);
	    if (!(pos & dbModifiedFlag)) { 
		dirtyPagesMap[size_t(oid / dbHandlesPerPage / 32)] 
		    |= 1 << (int(oid / dbHandlesPerPage) & 31);
		allocate(dbPageSize, oid);
		cloneBitmap(pos & ~dbFlagsMask, dbPageSize);
	    }
	    objBitSize -= (dbPageSize - offs)*8;
	    offs = 0;
	}
    }
}


oid_t dbDatabase::allocateId() 
{
    oid_t oid;
    int curr = 1-header->curr;
    if ((oid = header->root[curr].freeList) != 0) { 
	header->root[curr].freeList = oid_t(getPos(oid) >> dbFlagsBits);
	dirtyPagesMap[size_t(oid / dbHandlesPerPage / 32)] 
	    |= 1 << (int(oid / dbHandlesPerPage) & 31);
	return oid;
    }
    if (currIndexSize + 1 > header->root[curr].indexSize) {
	size_t oldIndexSize = header->root[curr].indexSize;
	size_t newIndexSize = oldIndexSize * 2;
	while (newIndexSize < oldIndexSize + 1) { 
	    newIndexSize = newIndexSize*2;
	}
	TRACE_MSG(("Extend index size from %ld to %ld\n", 
		   oldIndexSize, newIndexSize));
	offs_t newIndex = allocate(newIndexSize * sizeof(offs_t));
	pool.copy(newIndex, header->root[curr].index, 
		  currIndexSize*sizeof(offs_t));
	free(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	header->root[curr].index = newIndex;
	header->root[curr].indexSize = newIndexSize;
    }
    oid = currIndexSize;
    header->root[curr].indexUsed = ++currIndexSize;
    return oid;
}
	    
void dbDatabase::freeId(oid_t oid) 
{
    dirtyPagesMap[size_t(oid / dbHandlesPerPage / 32)] 
	|= 1 << (int(oid / dbHandlesPerPage) & 31);
    setPos(oid, (offs_t(header->root[1-header->curr].freeList) << dbFlagsBits)
	   | dbFreeHandleFlag);
    header->root[1-header->curr].freeList = oid;
}
    

void dbDatabase::beginTransaction(bool modify)
{
    dbDatabaseThreadContext* ctx = threadContext.get();
    if (modify) { 
	assert(accessType != dbReadOnly);
	if (!ctx->writeAccess) { 
	    mutex.lock();
	    if (ctx->readAccess) { 
		assert(monitor.nWriters == 0);
		if (monitor.nReaders != 1) {
		    if (monitor.waitForUpgrade) { 
			handleError(Deadlock);
		    }
		    monitor.waitForUpgrade = true;
		    monitor.nWaitWriters += 1;
		    upgradeSem.wait(mutex);
		    assert(monitor.nWriters == 1 && monitor.nReaders == 0);
		} else { 
		    monitor.nWriters = 1;		    
		    monitor.nReaders = 0;
		} 
		mutex.unlock();
	    } else { 
		if (monitor.nWriters != 0 || monitor.nReaders != 0) { 
		    monitor.nWaitWriters += 1;
		    writeSem.wait(mutex);
		    assert(monitor.nWriters == 1 && monitor.nReaders == 0);
		} else { 
		    monitor.nWriters = 1;
		}
		mutex.unlock();
	    }
	    ctx->writeAccess = true;
	} 
    } else { 
	if (!ctx->readAccess && !ctx->writeAccess) { 
	    mutex.lock();
	    if (monitor.nWriters + monitor.nWaitWriters != 0) {
		monitor.nWaitReaders += 1;
		readSem.wait(mutex);
		assert(monitor.nWriters == 0 && monitor.nReaders > 0);
	    } else { 
		monitor.nReaders += 1;
	    }
	    mutex.unlock();
	    ctx->readAccess = true;
	}
    }
    currIndexSize = header->root[1-header->curr].indexUsed;
    committedIndexSize = header->root[header->curr].indexUsed;
    assert(currIndexSize >= committedIndexSize);
    if (modify) { 
	header->dirty = true;
    }
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
    int rc;
    dbDatabaseThreadContext* ctx = threadContext.get();     
    if (ctx == NULL) { 
	return;
    }
    if (modified && (ctx->writeAccess || ctx->concurrentId == concurrentTransId))
    {
	if (!ctx->writeAccess) {
	    beginTransaction(true);
	}
	int n, curr = header->curr;
	oid_t i;
	int4* map = dirtyPagesMap;
	size_t oldIndexSize = header->root[curr].indexSize;
	size_t newIndexSize = header->root[1-curr].indexSize;
	size_t nPages = committedIndexSize / dbHandlesPerPage;
	if (newIndexSize > oldIndexSize) { 
	    offs_t newIndex = allocate(newIndexSize*sizeof(offs_t));
	    header->root[1-curr].shadowIndex = newIndex;
	    header->root[1-curr].shadowIndexSize = newIndexSize;
	    cloneBitmap(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	    free(header->root[curr].index, oldIndexSize*sizeof(offs_t));
	}
	for (i = 0; i < nPages; i++) { 
	    if (map[size_t(i >> 5)] & (1 << int(i & 31))) { 
		offs_t* srcIndex = 
		    (offs_t*)pool.get(header->root[1-curr].index+i*dbPageSize);
		offs_t* dstIndex = 
		    (offs_t*)pool.get(header->root[curr].index+i*dbPageSize);
		for (size_t j = 0; j < dbHandlesPerPage; j++) {
		    offs_t pos = dstIndex[j];
		    if (srcIndex[j] != pos) { 
			if (!(pos & dbFreeHandleFlag)) {
			    if (pos & dbPageObjectFlag) {  
				free(pos & ~dbFlagsMask, dbPageSize);
			    } else { 
				int offs = (int)pos & (dbPageSize-1);
				dbRecord* rec = (dbRecord*)
				    (pool.get(pos-offs)+(offs & ~dbFlagsMask));
				free(pos, rec->size);
				pool.unfix(rec);
			    }
			}
		    }
		}
		pool.unfix(srcIndex);
		pool.unfix(dstIndex);
	    }
	}
	if ((committedIndexSize % dbHandlesPerPage) != 0 
	    && (map[size_t(i >> 5)] & (1 << int(i & 31)))) 
	{ 
	    offs_t* srcIndex = 
		(offs_t*)pool.get(header->root[1-curr].index + i*dbPageSize);
	    offs_t* dstIndex = 
		(offs_t*)pool.get(header->root[curr].index + i*dbPageSize);
	    n = committedIndexSize % dbHandlesPerPage;
	    do { 
		offs_t pos = *dstIndex;
		if (*srcIndex != pos) { 
		    if (!(pos & dbFreeHandleFlag)) {
			if (pos & dbPageObjectFlag) { 
			    free(pos & ~dbFlagsMask, dbPageSize);
			} else { 
			    int offs = (int)pos & (dbPageSize-1);
			    dbRecord* rec = (dbRecord*)
				(pool.get(pos-offs) + (offs & ~dbFlagsMask));
			    free(pos, rec->size);
			    pool.unfix(rec);
			}
		    }
		}
		dstIndex += 1;
		srcIndex += 1;
	    } while (--n != 0);

	    pool.unfix(srcIndex);
	    pool.unfix(dstIndex);
	}
	for (i = 0; i <= nPages; i++) { 
	    if (map[size_t(i >> 5)] & (1 << int(i & 31))) { 
		offs_t* p = 
		    (offs_t*)pool.put(header->root[1-curr].index+i*dbPageSize);
		for (size_t j = 0; j < dbHandlesPerPage; j++) {
		    p[j] &= ~dbModifiedFlag;
		}
		pool.unfix(p);
	    }
	}
	if (currIndexSize > committedIndexSize) { 
	    offs_t page = (header->root[1-curr].index 
		+ committedIndexSize*sizeof(offs_t)) & ~((offs_t)dbPageSize-1);
	    offs_t end = (header->root[1-curr].index + dbPageSize - 1
		+ currIndexSize*sizeof(offs_t)) & ~((offs_t)dbPageSize-1);
	    while (page < end) { 
		offs_t* p = (offs_t*)pool.put(page);
		for (size_t h = 0; h < dbHandlesPerPage; h++) { 
		    p[h] &= ~dbModifiedFlag;
		}
		pool.unfix(p);
		page += dbPageSize;
	    }
	}
	if ((rc = file->write(0, header, dbPageSize)) != dbFile::ok) { 
	    handleError(FileError, "Failed to write header", rc);
	}
	pool.flush();
	header->curr = curr ^= 1;
	if ((rc = file->write(0, header, dbPageSize)) != dbFile::ok ||
	    (rc = file->flush()) != dbFile::ok)
	{
	    handleError(FileError, "Failed to flush changes to the disk", rc);
	}

	header->root[1-curr].size = header->root[curr].size;
	header->root[1-curr].indexUsed = currIndexSize; 
	header->root[1-curr].freeList  = header->root[curr].freeList; 
	header->root[1-curr].bitmapEnd = header->root[curr].bitmapEnd; 

	if (newIndexSize != oldIndexSize) {
	    header->root[1-curr].index=header->root[curr].shadowIndex;
	    header->root[1-curr].indexSize=header->root[curr].shadowIndexSize;
	    header->root[1-curr].shadowIndex=header->root[curr].index;
	    header->root[1-curr].shadowIndexSize=header->root[curr].indexSize;
	    pool.copy(header->root[1-curr].index, header->root[curr].index,
		      currIndexSize*sizeof(offs_t));
	    memset(map, 0, 4*((currIndexSize+dbHandlesPerPage*32-1)
		   / (dbHandlesPerPage*32)));
	} else { 
	    for (i = 0; i < nPages; i++) { 
		if (map[size_t(i >> 5)] & (1 << int(i & 31))) { 
		    map[size_t(i >> 5)] -= (1 << int(i & 31));
		    pool.copy(header->root[1-curr].index + i*dbPageSize,
			      header->root[curr].index + i*dbPageSize,
			      dbPageSize);
		}
	    }
	    if (currIndexSize > i*dbHandlesPerPage &&
		((map[size_t(i >> 5)] & (1 << int(i & 31))) != 0
		 || currIndexSize != committedIndexSize))
	    {
		pool.copy(header->root[1-curr].index + i*dbPageSize,
			  header->root[curr].index + i*dbPageSize,
			  size_t(sizeof(offs_t)*currIndexSize - i*dbPageSize));
		memset(map + size_t(i>>5), 0, 
		       size_t(((currIndexSize + dbHandlesPerPage*32 - 1)
			       / (dbHandlesPerPage*32) - (i>>5))*4));
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
	size_t nPages = 
	    (committedIndexSize + dbHandlesPerPage - 1) / dbHandlesPerPage;
	int4 *map = dirtyPagesMap;
	for (oid_t i = 0; i < nPages; i++) { 
	    if (map[size_t(i >> 5)] & (1 << int(i & 31))) { 
		pool.copy(header->root[1-curr].index + i*dbPageSize,
			  header->root[curr].index + i*dbPageSize,
			  dbPageSize);
	    }
	}
	memset(map, 0,
	       size_t((currIndexSize+dbHandlesPerPage*32-1) / (dbHandlesPerPage*32))*4);
	header->root[1-curr].indexSize = header->root[curr].indexSize;
	header->root[1-curr].indexUsed = committedIndexSize;
	header->root[1-curr].freeList  = header->root[curr].freeList; 
	header->root[1-curr].bitmapEnd = header->root[curr].bitmapEnd; 
	header->root[1-curr].size = header->root[curr].size;
	modified = false;
	concurrentTransId += 1;

	restoreTablesConsistency();
	for (dbTableDescriptor* desc = dbTableDescriptor::chain; 
	     desc != NULL; 
	     desc = desc->next)         
	{
	    if (desc->db != NULL && desc->db != this) { 
		continue;
	    }
	    dbTable* table = (dbTable*)get(desc->tableId);
	    desc->firstRow = table->firstRow;
	    desc->lastRow = table->lastRow;
	    desc->nRows = table->nRows;
	    pool.unfix(table);
	}
    } 
    endTransaction();
}

void dbDatabase::endTransaction() 
{
    dbDatabaseThreadContext* ctx = threadContext.get();
    assert(ctx != NULL);
    while (!ctx->cursors.isEmpty()) { 
	((dbAnyCursor*)ctx->cursors.next)->reset();
    }
    if (ctx->writeAccess) { 
	mutex.lock();
	monitor.nWriters -= 1;
	assert(monitor.nWriters == 0 && !monitor.waitForUpgrade);
	if (monitor.nWaitWriters != 0) { 
	    monitor.nWaitWriters -= 1;
	    monitor.nWriters = 1;
	    writeSem.signal();
	} else if (monitor.nWaitReaders != 0) { 
	    monitor.nReaders = monitor.nWaitReaders;
	    monitor.nWaitReaders = 0;
	    readSem.signal(monitor.nReaders);
	}
	mutex.unlock();
    } else if (ctx->readAccess) { 
	mutex.lock();
	monitor.nReaders -= 1;
	if (monitor.nReaders == 1 && monitor.waitForUpgrade) { 
	    assert(monitor.nWriters == 0);
	    monitor.waitForUpgrade = false;
	    monitor.nWaitWriters -= 1;
	    monitor.nWriters = 1;
	    monitor.nReaders = 0;
	    upgradeSem.signal();
	} else if (monitor.nReaders == 0) { 
	    if (monitor.nWaitWriters != 0) { 
		assert(monitor.nWriters == 0 && !monitor.waitForUpgrade);
		monitor.nWaitWriters -= 1;
		monitor.nWriters = 1;
		writeSem.signal();
	    } else { 
		assert(monitor.nWaitReaders == 0);
	    }
	} 
	mutex.unlock();
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
    dbPutTie putTie;
    byte buf[1024];
    if (inverseId == targetId) { 
	return;
    }
    fd = fd->inverseRef;
    if (fd->type == dbField::tpArray) { 
	dbTableDescriptor* desc = fd->defTable;
	dbGetTie getTie;
	dbRecord* rec = getRow(getTie, targetId);
	dbVarying* arr = (dbVarying*)((byte*)rec + fd->dbsOffs);
	size_t arrSize = arr->size;
	size_t arrOffs = arr->offs;
	size_t newSize = desc->fixedSize;
	int lastOffs = 
	    desc->columns->sizeWithoutOneField(fd, (byte*)rec, newSize);
	int newArrOffs = DOALIGN(newSize, sizeof(oid_t));
	size_t oldSize = rec->size;
	newSize = newArrOffs + (arrSize +  1)*sizeof(oid_t);
	if (newSize > oldSize) { 
	    newSize = newArrOffs + (arrSize+1)*sizeof(oid_t)*2;
	} else { 
	    newSize = oldSize;
	}

	byte* dst = (byte*)putRow(putTie, targetId, newSize);
	byte* src = (byte*)rec;
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
	*(oid_t*)((byte*)putRow(putTie, targetId) + fd->dbsOffs) = inverseId;
    }
}


void dbDatabase::removeInverseReferences(dbTableDescriptor* desc, oid_t oid)
{
    dbFieldDescriptor* fd;
    dbGetTie tie;
    offs_t pos = getPos(oid);
    assert(!(pos & (dbFreeHandleFlag|dbPageObjectFlag)));
    tie.set(pool, pos & ~dbFlagsMask);
    byte* rec = (byte*)tie.get();
    if (desc->inverseFields != NULL) { 
	setPos(oid, pos | dbFreeHandleFlag);
    }
    for (fd = desc->inverseFields; fd != NULL; fd = fd->nextInverseField) { 
	if (fd->type == dbField::tpArray) { 
	    dbVarying* arr = (dbVarying*)(rec + fd->dbsOffs);
	    int n = arr->size;
	    int offs = arr->offs + n*sizeof(oid_t);
	    while (--n >= 0) { 
		offs -= sizeof(oid_t);
		oid_t ref = *(oid_t*)(rec + offs);
		if (ref != 0) {
		    removeInverseReference(fd, oid, ref);
		}
	    }
	} else { 
	    oid_t ref = *(oid_t*)(rec + fd->dbsOffs);
	    if (ref != 0) { 
		removeInverseReference(fd, oid, ref);
	    }
	}
    }
    if (desc->inverseFields != NULL) { 
	setPos(oid, pos);
    }
}


void dbDatabase::removeInverseReference(dbFieldDescriptor* fd, 
					oid_t inverseId,
					oid_t targetId)
{
    if (inverseId == targetId || targetId == updatedRecordId ||
	(getPos(targetId) & dbFreeHandleFlag) != 0) 
    { 
	return;
    }
    dbPutTie tie;
    byte* rec = (byte*)putRow(tie, targetId);

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


bool dbDatabase::restore(char const* backupFileName,
			 char const* databaseFileName)
{
    dbFile bck;
    dbFile dbf;
    int rc;
    assert(!opened);
    if (bck.open(backupFileName, dbFile::sequential|dbFile::read_only) 
	!= dbFile::ok) 
    {
	TRACE_MSG(("Failed to open backup file\n"));
	return false;
    }
    void* buf = dbFile::allocateBuffer(dbPageSize);
    if (*databaseFileName == '@') { 
	FILE* f = fopen(databaseFileName+1, "r");
	if (f == NULL) { 
	    TRACE_MSG(("Failed to open database configuration file\n"));
	    dbFile::deallocateBuffer(buf);
	    return false;
	}
	const int maxFileNameLen = 1024;
	char fileName[maxFileNameLen];
	int i, n;
	int8 size = 0;
	for (i=0; (n=fscanf(f, "%s" INT8_FORMAT, fileName, &size)) >= 1; i++) {
	    if ((rc = dbf.open(fileName, dbFile::truncate|dbFile::sequential))
		!= dbFile::ok) 
	    { 
		TRACE_MSG(("Failed to open database segment %d '%s': %d\n",
			   i, fileName, rc));
		dbFile::deallocateBuffer(buf);
		return false;
	    }
	    if (n == 2) { 
		while (size != 0) { 
		    if ((rc = bck.read(buf, dbPageSize)) != dbFile::ok) { 
			TRACE_MSG(("Failed to read page from backup: %d\n", 
				   rc));
			dbFile::deallocateBuffer(buf);
			return false;
		    }
		    if ((rc = dbf.write(buf, dbPageSize)) != dbFile::ok) { 
			TRACE_MSG(("Failed to write restored page: %d\n", rc));
			dbFile::deallocateBuffer(buf);
			return false;
		    }
		    size -= 1;
		}
	    } else { 
		while ((rc = bck.read(buf, dbPageSize)) == dbFile::ok) {
		    if ((rc = dbf.write(buf, dbPageSize)) != dbFile::ok) { 
			TRACE_MSG(("Failed to write restored page: %d\n", rc));
			dbFile::deallocateBuffer(buf);
			return false;
		    }
		}
		if (rc != dbFile::eof) { 
		    TRACE_MSG(("Failed to read page from backup: %d\n", rc));
		    dbFile::deallocateBuffer(buf);
		    return false;
		}
	    }
	    dbf.close();
	    size = 0;
	}
	fclose(f);
    } else {
	if ((rc = dbf.open(databaseFileName, 
			   dbFile::sequential|dbFile::sequential))
	    != dbFile::ok) 
	{ 
	    TRACE_MSG(("Failed to open database file '%s': %d\n",
		       databaseFileName, rc));
	    dbFile::deallocateBuffer(buf);
	    return false;
	}
	while ((rc = bck.read(buf, dbPageSize)) == dbFile::ok) {
	    if ((rc = dbf.write(buf, dbPageSize)) != dbFile::ok) { 
		TRACE_MSG(("Failed to write restored page: %d\n", rc));
		dbFile::deallocateBuffer(buf);
		return false;
	    }
	}
	if (rc != dbFile::eof) { 
	    TRACE_MSG(("Failed to read page from backup: %d\n", rc));
	    dbFile::deallocateBuffer(buf);
	    return false;
	}
    }
    bck.close();
    dbFile::deallocateBuffer(buf);
    return true;
}

bool dbDatabase::backup(char const* fileName)
{
    assert(opened);
    dbFile f;
    if (f.open(fileName, dbFile::sequential|dbFile::truncate) != dbFile::ok) {
	return false;
    }  
    beginTransaction(false);
    offs_t eof = header->root[header->curr].size;
    int rc = f.write(header, dbPageSize);
    for (offs_t pos = dbPageSize; rc == dbFile::ok && pos < eof;) { 
	byte* p = pool.get(pos);
	rc = f.write(p, dbPageSize);
	pool.unfix(p);
	pos += dbPageSize;
    }
    f.close();
    return rc == dbFile::ok;
}


dbDatabase::dbDatabase(dbAccessType type, size_t poolSize, 
		       size_t dbExtensionQuantum, size_t dbInitIndexSize,
		       int nThreads)
: accessType(type), 
  extensionQuantum(dbExtensionQuantum),
  initIndexSize(dbInitIndexSize),
  pool(this, poolSize)
{
    dirtyPagesMap = new int4[dbDirtyPageBitmapSize/4+1];
    bitmapPageAvailableSpace = new int[dbBitmapId + dbBitmapPages];
    setConcurrency(nThreads);
    tables = NULL;
    opened = false;
    header = (dbHeader*)dbFile::allocateBuffer(dbPageSize);
    updatedRecordId = 0;
}      

dbDatabase::~dbDatabase() 
{
    delete[] dirtyPagesMap;
    delete[] bitmapPageAvailableSpace;
    dbFile::deallocateBuffer(header);
}



//-< SYMTAB.CPP >----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 20-Nov-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Symbol table implementation
//-------------------------------------------------------------------*--------*

#include "stdtp.h"
#include "sync.h"
#include "symtab.h"

const size_t hashTableSize = 1009;
dbSymbolTable::HashTableItem* dbSymbolTable::hashTable[hashTableSize];

int dbSymbolTable::add(char* &str, int tag, bool allocate) {
    static dbMutex mutex;
    dbCriticalSection cs(mutex);
    unsigned hash = 0;
    byte* p = (byte*)str;
    while (*p != 0) { 
	hash = hash*31 + *p++;
    }
    int index = hash % hashTableSize;
    HashTableItem *ip;
    for (ip = hashTable[index]; ip != NULL; ip = ip->next) { 
	if (ip->hash == hash && strcmp(ip->str, str) == 0) { 
	    str = ip->str;
	    return ip->tag;
	}
    }
    ip = new HashTableItem;
    if (allocate) { 
	str = strdup(str);
    }
    ip->str = str;
    ip->hash = hash;
    ip->tag = tag;
    ip->next = hashTable[index];
    hashTable[index] = ip;
    return tag;
}


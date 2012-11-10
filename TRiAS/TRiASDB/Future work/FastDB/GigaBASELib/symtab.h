//-< SYMTAB.H >----------------------------------------------------*--------*
// GigaBASE                  Version 1.0         (c) 1999  GARRET    *     ?  *
// (Post Relational Database Management System)                      *   /\|  *
//                                                                   *  /  \  *
//                          Created:     20-Nov-98    K.A. Knizhnik  * / [] \ *
//                          Last update: 10-Dec-98    K.A. Knizhnik  * GARRET *
//-------------------------------------------------------------------*--------*
// Symbol table interface
//-------------------------------------------------------------------*--------*

#ifndef __SYMTAB_H__
#define __SYMTAB_H__

class dbSymbolTable { 
    struct HashTableItem { 
	HashTableItem* next;
	char*          str;
	unsigned       hash;
	int            tag;
    };
    static HashTableItem* hashTable[]; 
   
  public:    
    static int add(char* &str, int tag,  bool allocate = true);
};

#endif


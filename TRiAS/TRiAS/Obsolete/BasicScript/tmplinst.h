#ifndef _TMPLINST_H
#define _TMPLINST_H

#include <ospace/header.h>

HRESULT CreateObject(CLSID *pClID, LPVOID *ppv);

os_bstream &operator<< (os_bstream &str, CLSID &rClsID);
os_bstream &operator>> (os_bstream &str, CLSID &rClsID);

void os_write (os_bstream& stream, const WListElement &) ;
void os_write (os_bstream& stream, const WAnpassen &) ;
void os_write (os_bstream& stream, const WCommand &) ;
void os_write (os_bstream& stream, const WSave &) ;
void os_write (os_bstream& stream, const WPersistBStream &) ;
void os_write (os_bstream& stream, const WScriptContainer &) ;
void os_write (os_bstream& stream, const WProcess &) ;

void os_read (os_bstream& stream, WListElement &);
void os_read (os_bstream& stream, WAnpassen &) ;
void os_read (os_bstream& stream, WCommand &) ;
void os_read (os_bstream& stream, WSave &) ;
void os_read (os_bstream& stream, WPersistBStream &) ;
void os_read (os_bstream& stream, WScriptContainer &) ;
void os_read (os_bstream& stream, WProcess &) ;

void os_write (os_bstream& stream, const MyEnum& Enum) ;
void os_read (os_bstream& stream, MyEnum& Enum) ;
	
void os_write (os_bstream& stream, const NEnumWListElement& Enum) ;
void os_read (os_bstream& stream, NEnumWListElement& Enum) ;

void os_write (os_bstream& stream, const WEnumWListElement&) ;
void os_read (os_bstream& stream, WEnumWListElement&) ;

#endif //  _TMPLINST_H

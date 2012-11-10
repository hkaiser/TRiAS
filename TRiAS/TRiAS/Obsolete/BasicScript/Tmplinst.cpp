#include <bscriptp.hxx>

#include <ospace/source.h>
#include <ospace/uss/std/list.h>
#include <ospace/uss/std/map.h>

#include <ipropseq.hxx>

#include "macrguid.h"

#include "imacorg.h"
#include "imacro.h"

#include "myenum.h"
#include "tmplinst.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Streamoperatoren für ClassID
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *** LETZTE FREIE ID's = 130 - 139 ***

os_bstream &operator<< (os_bstream &str, CLSID &rClsID)
{
    str << rClsID.Data1 << (unsigned long)rClsID.Data2 << (unsigned long)rClsID.Data3;
	for (int i = 0; i < sizeof(rClsID.Data4); i++)
		str << (unsigned long)rClsID.Data4[i];

return str;
}

os_bstream &operator>> (os_bstream &str, CLSID &rClsID)
{
unsigned long data2 = 0;
unsigned long data3 = 0;
unsigned long data4 = 0;

    str >> rClsID.Data1 >> data2 >> data3;
	for (int i = 0; i < sizeof(rClsID.Data4); i++) {
		str >> data4; 
		rClsID.Data4[i] = (unsigned char)data4;
	}

	rClsID.Data2 = (unsigned short)data2;
	rClsID.Data3 = (unsigned short)data3;

return str;
}

// Liste der Menueinträge speicherfähig machen
const int os_list_start_id = os_user_start_id + 100;
OS_STREAMABLE_0( (list<WListElement>*), os_list_start_id +1);

// Map der Macrobefehle speicherfähig machen
const int os_map_start_id = os_user_start_id + 140;
OS_STREAMABLE_0( (map< UINT,WCommand,less<UINT> > *), os_map_start_id +1);

const int os_commands_id = os_user_start_id + 128;
OS_STREAMABLE_0( (WCommands*), os_commands_id);

void os_write (os_bstream& stream, const WCommands &) {}
void os_read (os_bstream& stream, WCommands &) {}

// WPeristStream für Streaming instanzieren
const int os_persiststream_id = os_user_start_id + 127;
OS_STREAMABLE_0( (WPersistStream *), os_persiststream_id);

void os_write (os_bstream& stream, const WPersistStream &) {}
void os_read (os_bstream& stream, WPersistStream &) {}

// WAnpassen für Streaming instanzieren
const int os_anpassen_id = os_user_start_id + 122;
OS_STREAMABLE_0( (WAnpassen *), os_anpassen_id);

void os_write (os_bstream& stream, const WAnpassen &) {}
void os_read (os_bstream& stream, WAnpassen &) {}

// WAnalyse für Streaming instanzieren
const int os_analyse_id = os_user_start_id + 129;
OS_STREAMABLE_0( (WAnalyse *), os_analyse_id);

void os_write (os_bstream& stream, const WAnalyse &) {}
void os_read (os_bstream& stream, WAnalyse &) {}

// WSave für Streaming instanzieren
const int os_save_id = os_user_start_id + 121;
OS_STREAMABLE_0( (WSave *), os_save_id);

void os_write (os_bstream& stream, const WSave &) {}
void os_read (os_bstream& stream, WSave &) {}

// WPersistBStream für Streaming instanzieren
const int os_persist_id = os_user_start_id + 115;
OS_STREAMABLE_0( (WPersistBStream *), os_persist_id);

void os_write (os_bstream& stream, const WPersistBStream &) {}
void os_read (os_bstream& stream, WPersistBStream &) {}

// WScriptContainer für Streaming instanzieren
const int os_scriptcontainer_id = os_user_start_id + 113;
OS_STREAMABLE_0( (WScriptContainer *), os_scriptcontainer_id);

void os_write (os_bstream& stream, const WScriptContainer &) {}
void os_read (os_bstream& stream, WScriptContainer &) {}

// WProcess für Streaming instanzieren
const int os_process_id = os_user_start_id + 114;
OS_STREAMABLE_0( (WProcess *), os_process_id);

void os_write (os_bstream& stream, const WProcess &) {}
void os_read (os_bstream& stream, WProcess &) {}

// WListelement für Streaming instanzieren
const int os_listelement_id = os_user_start_id + 116;
OS_STREAMABLE_0( (WListElement *), os_listelement_id);

void os_write (os_bstream& stream, const WListElement & Int)
{
	try {
	WPersistBStream IPBS (Int);		// throws hr
	CLSID clsID;

		IPBS -> GetClassID (&clsID);
		stream << clsID;

		IPBS -> Save (&stream);
	
	} catch (HRESULT) {
		;
	}
}


void os_read (os_bstream& stream, WListElement & Int) 
{
	try {
	CLSID clsID;

		stream >> clsID;

		THROW_FAILED_HRESULT(CreateObject(&clsID, Int.ppv()));

	WPersistBStream IPBS(Int);		// throws hr

		IPBS -> Load (&stream);
	} catch (HRESULT) {
		;
	}
}

// WCommand für Streaming instanzieren
const int os_command_id = os_user_start_id + 126;
OS_STREAMABLE_0( (WCommand *), os_command_id);

void os_write (os_bstream& stream, const WCommand & Int)
{
	try {
	WPersistBStream IPBS (Int);
	CLSID clsID;

		IPBS -> GetClassID (&clsID);
		stream << clsID;

		IPBS -> Save (&stream);

	} catch (HRESULT) {
		;
	}
}

void os_read (os_bstream& stream, WCommand & Int) 
{
	try {
	CLSID clsID;

		stream >> clsID;
		THROW_FAILED_HRESULT(CreateObject(&clsID, Int.ppv()));

	WPersistBStream IPBS (Int);		// throws hr

		IPBS -> Load (&stream);

	} catch (HRESULT) {
		;
	}
}

// WEnumWListElement für Streaming instanzieren
const int os_enumlist_id = os_user_start_id + 117;
OS_STREAMABLE_0( (WEnumWListElement *), os_enumlist_id);

void os_write (os_bstream& stream, const WEnumWListElement&) {}
void os_read (os_bstream& stream, WEnumWListElement&) {}

// NEnumWListElementt für Streaming instanzieren
// NEnumWListElement == 
// __Enumerator<WListElement,CIID_EnumWListElement,list<WListElement> >
const int os_enum_id = os_user_start_id + 111;
OS_STREAMABLE_0( (NEnumWListElement*), os_enum_id);

void os_write (os_bstream& stream, const NEnumWListElement& Enum) 
{
	stream << Enum.m_data;
}
void os_read (os_bstream& stream, NEnumWListElement& Enum) 
{
	stream >> Enum.m_data;
}	

// Myenum für Streaming instanzieren, kein TEMPLATE 
const int os_myenum_id = os_user_start_id + 112;
OS_NO_FACTORY_STREAMABLE_1( (MyEnum*), os_myenum_id, (NEnumWListElement*) );

void os_write (os_bstream& stream, const MyEnum& Enum) 
{
	os_write(stream, (const NEnumWListElement&) Enum);
}

void os_read (os_bstream& stream, MyEnum& Enum) 
{
	os_read(stream, (NEnumWListElement&) Enum);
}	

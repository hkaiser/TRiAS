// Testbeispiel für die Iterator-Templates ------------------------------------
// File ITERTMPL.CXX

#include <windows.h>
#include <iostream.h>

#define OS_NO_STREAM_SUPPORT
#include <set.h>
#include <list.h>
#include <iterenum.h>

#include <initguid.h>
#include <eonrguid.h>

#pragma warning (disable: 4114)

///////////////////////////////////////////////////////////////////////////////
// Die folgenden Definitionen erfordern, daß der GUID des zu erzeugenden 
// Enumerators definiert und verfügbar ist (in diesem Fall IID_IEnumLONG).
//
DefineEnumerator(LONG);				// definiert NEnumLONG
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

DefineSmartEnumerator(LONG);		// definiert WEnumLONG (Wrapper für IEnum<LONG>)

///////////////////////////////////////////////////////////////////////////////
// Ausgeben aller Elemente eines gegebenen Iterators unter Benutzung eines
// InputIterators, der den Enumerator an die Erfordernisse der STL-Algorithmen
// anpaßt.
//
void OutputAllElements (IEnum<LONG> *pEnum)
{
ostream_iterator<LONG> out(cout, " ");

	copy (InEnumLONG(pEnum), InEnumLONG(), out);
	cout << endl << flush;
}

void main (void)
{
NEnumLONG EnumLongs;

	EnumLongs.AddItem (6);
	EnumLongs.AddItem (2);
	EnumLongs.AddItem (3);
	EnumLongs.AddItem (1);

// Elemente des Enumerators nach cout kopieren
	OutputAllElements (&EnumLongs);

// Zusätzliche Elemente aus Feld lesen und zum Enumerator hinzufügen.
// Das geschieht mit Hilfe eines OutputIterators, der Ausgaben von
// STL-Algortithmen direkt in Enumeratoren speichert.
	{
	OutEnumLONG out_iter (&EnumLongs);
	LONG values[] = { 12, 14, 15, 7, 9, };

		copy (values, &values[sizeof(values)/sizeof(long)], out_iter);
	}

// Elemente des Enumerators nach cout kopieren
	OutputAllElements (&EnumLongs);
}

#if !defined(OS_NO_STREAM_SUPPORT)

///////////////////////////////////////////////////////////////////////////////
// StreamSupport
const int nenum_id = 1000;
const int iterface_id = 1001;

OS_STREAMABLE_0((NEnumLONG *), nenum_id);
OS_STREAMABLE_0((WEnumLONG *), iterface_id);

void os_write (os_bstream &, const NEnumLONG &) {}
void os_read (os_bstream &, NEnumLONG &) {}
void os_write (os_bstream &, const WEnumLONG &) {}
void os_read (os_bstream &, WEnumLONG &) {}

#endif // OS_POLY_FUNCTION

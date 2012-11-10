// Diverse Hilfsfunktionen für den Umgang mit unserem CDataObject -------------
// File: DATAHELP.CXX

#include "bscriptp.hxx"
#include "bscript.h"

#include <eonrguid.h>
#include <oprpguid.h>

#include "macrguid.h"
#include "imacorg.h"

#include "datahelp.h"

#define OS_NO_STREAM_SUPPORT

DefineSmartInterface(Stream);

// Funktionen für EnumLONG ////////////////////////////////////////////////////

// Serialisieren/DeSerialisieren eines IUnknowns 
// in diesem Falle ein IDataObject
HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown *pIUnk,// IEnum *, 
										   IStream **ppIStream)
{
	ASSERT(pIUnk);
	ASSERT(ppIStream);

	*ppIStream = NULL;

// neuen Stream anlegen, kreiert eine neuen Memoryblock der Größe NULL
// wird selbstständig wieder freigegen (true)
WStream IStream;
HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());	

	if (FAILED(hr)) return hr;
	try 
	{
	WPersistStream IPersStr (pIUnk);	// throws hr

	// den Enumerator wegschreiben
		THROW_FAILED_HRESULT(OleSaveToStream (IPersStr, IStream));

	// wieder zurück positionieren
	LARGE_INTEGER li;

		LISet32 (li, 0L);
		THROW_FAILED_HRESULT(IStream -> Seek (li, STREAM_SEEK_SET, NULL));

		*ppIStream = IStream.detach();
	}
	catch (_com_error &e)
	{
		if (*ppIStream) (*ppIStream) -> Release();
		*ppIStream = NULL;
		return _COM_ERROR(e);
	}
	return NOERROR;
}

// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' --
HRESULT CreateEnumLONGFromStream (IStream *pIStream, IEnum<LONG> **ppEnumOut)
{
	ASSERT(NULL != pIStream);
	ASSERT(NULL != ppEnumOut);

	*ppEnumOut = NULL;
	return OleLoadFromStream (pIStream, IID_IEnumLONG, (LPVOID *)ppEnumOut));  
}


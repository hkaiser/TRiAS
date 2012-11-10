// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <crtdbg.h>

#import "..\CvrtGuid.tlb" \
	raw_interfaces_only raw_native_types no_namespace named_guids

class CInitCom
{
public:
	CInitCom() { CoInitialize(NULL); }
	~CInitCom() { CoUninitialize(); }
};

CInitCom g_InitCom;

int main(int argc, char* argv[])
{
	IConvertGuidPtr CvrtGuid;
	CvrtGuid.CreateInstance(CLSID_ConvertGuid);

	for (int i = 0; i < 100; ++i) {
	GUID Guid, Guid2;
	BSTR bstrGuid, bstrGuid32;
	wchar_t wBuffer[80];
		
		CoCreateGuid(&Guid);
		StringFromGUID2(Guid, wBuffer, sizeof(wBuffer));
		CvrtGuid->GuidToGuid32String(bstr_t(wBuffer), &bstrGuid32);
		CvrtGuid->Guid32StringToGuid(bstrGuid32, &bstrGuid);
		IIDFromString(bstrGuid, &Guid2);

		_ASSERTE(IsEqualGUID(Guid, Guid2));

		SysFreeString(bstrGuid);
		SysFreeString(bstrGuid32);
	}
	return 0;
}

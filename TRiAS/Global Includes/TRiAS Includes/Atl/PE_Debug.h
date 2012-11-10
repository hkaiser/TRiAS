///////////////////////////////////////////////////////////////////////////
// @doc 
// @module PE_Debug.h | Description goes here

#if !defined(_CPEDebug_H__5425EF24_D5D6_11D1_85EF_00600875138A__INCLUDED_)
#define _CPEDebug_H__5425EF24_D5D6_11D1_85EF_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// modified: #HK980417
// original comment:

// PE_Debug.H
// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net

class CPEDebug {
public:
	CPEDebug();
	~CPEDebug();

	void ClearReport();
	void DumpDebugInfo (
		const BYTE* caller, HINSTANCE hInstance, LPSTR pcFile, int iLen, 
		LPSTR pcFunction, int iLenFunc, int *piLineNo);

private:
// Report data
	enum { MAX_MODULENAME_LEN = 512, };
	char latestModule[MAX_MODULENAME_LEN];

// File mapping data
	HANDLE hFile;
	HANDLE hFileMapping;
	PIMAGE_DOS_HEADER fileBase;

// Pointers to debug information
	PIMAGE_NT_HEADERS NT_Header;
	PIMAGE_COFF_SYMBOLS_HEADER COFFDebugInfo;
	PIMAGE_SYMBOL COFFSymbolTable;
	int COFFSymbolCount;
	const char* stringTable;
	
	void ClearFileCache();
	void ClearDebugPtrs();
	void MapFileInMemory(const char* module);
	void FindDebugInfo();
	PIMAGE_COFF_SYMBOLS_HEADER GetDebugHeader();
	PIMAGE_SECTION_HEADER SectionHeaderFromName(const char* name);
	const char* GetSymbolName(PIMAGE_SYMBOL sym);

	void DumpSymbolInfo (DWORD relativeAddress, LPSTR pcFile, int iLen, LPSTR pcFunction, int iLenFunc);
	void DumpLineNumber (DWORD relativeAddress, int *piLineNo);
};

#endif // !defined(_CPEDebug_H__5425EF24_D5D6_11D1_85EF_00600875138A__INCLUDED_)

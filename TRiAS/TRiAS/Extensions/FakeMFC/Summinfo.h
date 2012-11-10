// summinfo.h : interface of the CSummInfo classes
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#if !defined(_MAC)

#include "propset.h"

extern const OLECHAR szSummInfo[];

DEFINE_GUID (FMTID_SummaryInformation, 0xF29F85E0, 0x4FF9, 0x1068, 0xAB, 0x91, 0x08, 0x00, 0x2B, 0x27, 0xB3, 0xD9) ;

// #define PID_DICTIONARY	0X00000000
// #define PID_CODEPAGE	0X00000001
#define PID_TITLE		0X00000002
#define PID_SUBJECT		0X00000003
#define PID_AUTHOR		0X00000004
#define PID_KEYWORDS	0X00000005
#define PID_COMMENTS	0X00000006
#define PID_TEMPLATE	0X00000007
#define PID_LASTAUTHOR	0X00000008
#define PID_REVNUMBER	0X00000009
#define PID_EDITTIME	0X0000000A
#define PID_LASTPRINTED	0X0000000B
#define PID_CREATE_DTM	0X0000000C
#define PID_LASTSAVE_DTM	0X0000000D
#define PID_PAGECOUNT	0X0000000E
#define PID_WORDCOUNT	0X0000000F
#define PID_CHARCOUNT	0X00000010
#define PID_THUMBNAIL	0X00000011
#define PID_APPNAME		0X00000012
// #define PID_SECURITY	0X00000013
#define cPID_STANDARD	(PID_SECURITY+1-2)

class CSummInfo {
public:
	CSummInfo();

	bool SetTitle(LPCTSTR szTitle);
	CString GetTitle();
	bool SetSubject(LPCTSTR szSubject);
	CString GetSubject();
	bool SetAuthor(LPCTSTR szAuthor);
	CString GetAuthor();
	bool SetKeywords(LPCTSTR szKeywords);
	CString GetKeywords();
	bool SetComments(LPCTSTR szComments);
	CString GetComments();
	bool SetTemplate(LPCTSTR szTemplate);
	CString GetTemplate();
	bool SetLastAuthor(LPCTSTR szLastAuthor);
	CString GetLastAuthor();
	bool IncrRevNum();
	CString GetRevNum();
	void StartEditTimeCount();
	bool AddCountToEditTime();
	CString GetEditTime();
	bool RecordPrintDate();
	CString GetLastPrintDate();
	bool RecordCreateDate();
	CString GetCreateDate();
	bool RecordSaveDate();
	CString GetLastSaveDate();
	bool SetNumPages(ULONG nPages);
	CString GetNumPages();
	bool SetNumWords(ULONG nWords);
	CString GetNumWords();
	ULONG GetNumWordsNum();
	bool SetNumChars(ULONG nChars);
	CString GetNumChars();
	ULONG GetNumCharsNum();
	bool SetAppname(LPCTSTR szAppname);
	CString GetAppname();
	bool SetSecurity(ULONG nLevel);
	CString GetSecurity();
	ULONG GetSecurityNum();
	HRESULT WriteToStorage(LPSTORAGE lpRootStg);
	HRESULT ReadFromStorage(LPSTORAGE lpRootStg);

protected:
	CPropertySet m_propSet;
	CPropertySection* m_pSection;
	__int64 startEdit;
};

#endif // !defined(_MAC)

// MakeName.h: interface for the CMakeName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKENAME_H__93A86B95_546C_11D1_96FC_00A024D6F582__INCLUDED_)
#define AFX_MAKENAME_H__93A86B95_546C_11D1_96FC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMakeName  
{
private:
	string m_strRoot;
	int m_iMax;
	int m_iCurr;
	int m_iFirst;
	char m_iAppendChar;

public:
	void Reset();
	bool GetNextName(string &rStr);

	CMakeName(LPCSTR pcRoot, int iFirst, int iMax, char cAppend);
	virtual ~CMakeName();
};

#endif // !defined(AFX_MAKENAME_H__93A86B95_546C_11D1_96FC_00A024D6F582__INCLUDED_)

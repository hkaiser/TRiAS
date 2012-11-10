// MakeName.cpp: implementation of the CMakeName class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include <ospace/file/path.h>

#include "MakeName.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMakeName::CMakeName(LPCSTR pcRoot, int iFirst, int iMax, char cAppend)
	: m_strRoot(pcRoot), m_iMax(iFirst+iMax), m_iFirst(iFirst), m_iAppendChar(cAppend)
{
	Reset();
}

CMakeName::~CMakeName()
{

}

bool CMakeName::GetNextName(string &rStr)
{
	if (m_iCurr >= m_iMax)
		return false;

os_path path (m_strRoot.c_str());
char cbBuffer[256];
os_string base (path.base());

	ltoa (m_iCurr++, cbBuffer, 10);
	if (m_iAppendChar != '\0') {
	string str (base.substr(0, base.size()-1));

		str += cbBuffer;
		str += base.substr(base.size()-1, os_npos);
		path.base(str);
	} else 
		path.base(os_string(base + cbBuffer));

	rStr = path.filename();
	return true;
}

void CMakeName::Reset()
{
	m_iCurr = m_iFirst;
}

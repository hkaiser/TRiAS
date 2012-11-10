// fieldinf.hpp : header file
//

#ifndef _FIELDINF_HPP
#define _FIELDINF_HPP

enum SortType { SortName = 1, SortType = 2, SortLen = 4, SortAsc = 8, SortDesc = 16, NotSorted = 32};

int __export CALLBACK CompareFelderFunction (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

//	Speichert Info für Feldinfos
class CFeldInf
{
public:
	CString m_strName;
	CString m_strType;
	long m_lLen;

	CFeldInf (const char *pName, const char *pType, long lLen);
	~ CFeldInf (void) {}
};

class CFeldInfExt : public CFeldInf
{
public:
        long m_lExtData;

        CFeldInfExt (const char *pName, const char *pType, long lLen,
                     long lExtData);
        ~ CFeldInfExt (void) {}                               
};


#endif          // CFieldInf


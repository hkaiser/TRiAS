// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.01.2003 16:35:30 
//
// @doc
// @module DumpHelperScope.h | Declaration of the <c CDumpHelperScope> class

#if !defined(_DUMPHELPERSCOPE_H__DB7BF445_0843_4A39_896A_719262B42F64__INCLUDED_)
#define _DUMPHELPERSCOPE_H__DB7BF445_0843_4A39_896A_719262B42F64__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(USE_DLIB) && defined(USE_DLIB_SCOPE)

///////////////////////////////////////////////////////////////////////////////
// 
class CDumpScope1
{
public:
	CDumpScope1(const char *pfname, int iLine, int iLevel, 
		char const *pfmt1, char const *pexp1)
	:	m_strFName(pfname), m_iLine(iLine), m_iLevel(iLevel), 
		m_strFmt1(pfmt1), m_strExp1(pexp1)
	{
		os_string fmt ("i: ");
		fmt += m_strFmt1;
		D_OUTF1_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str());
	}

	~CDumpScope1()
	{
		os_string fmt ("o: ");
		fmt += m_strFmt1;
		D_OUTF1_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str());
	}

private:
	int m_iLine;
	os_string m_strFName;
	int m_iLevel;
	os_string m_strFmt1;
	os_string m_strExp1;
};

///////////////////////////////////////////////////////////////////////////////
// 
class CDumpScope2
{
public:
	CDumpScope2(const char *pfname, int iLine, int iLevel, 
		char const *pfmt1, char const *pexp1,
		char const *pfmt2, char const *pexp2)
	:	m_strFName(pfname), m_iLine(iLine), m_iLevel(iLevel), 
		m_strFmt1(pfmt1), m_strExp1(pexp1), 
		m_strFmt2(pfmt2), m_strExp2(pexp2)
	{
		os_string fmt ("i: ");
		fmt += m_strFmt1;
		D_OUTF2_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str(), 
			m_strFmt2.c_str(), m_strExp2.c_str());
	}

	~CDumpScope2()
	{
		os_string fmt ("o: ");
		fmt += m_strFmt1;
		D_OUTF2_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str(), 
			m_strFmt2.c_str(), m_strExp2.c_str());
	}

private:
	int m_iLine;
	os_string m_strFName;
	int m_iLevel;
	os_string m_strFmt1;
	os_string m_strExp1;
	os_string m_strFmt2;
	os_string m_strExp2;
};

///////////////////////////////////////////////////////////////////////////////
// 
class CDumpScope3
{
public:
	CDumpScope3(const char *pfname, int iLine, int iLevel, 
		char const *pfmt1, char const *pexp1,
		char const *pfmt2, char const *pexp2,
		char const *pfmt3, char const *pexp3)
	:	m_strFName(pfname), m_iLine(iLine), m_iLevel(iLevel), 
		m_strFmt1(pfmt1), m_strExp1(pexp1), 
		m_strFmt2(pfmt2), m_strExp2(pexp2),
		m_strFmt3(pfmt3), m_strExp3(pexp3)
	{
		os_string fmt ("i: ");
		fmt += m_strFmt1;
		D_OUTF3_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str(), 
			m_strFmt2.c_str(), m_strExp2.c_str(),
			m_strFmt3.c_str(), m_strExp3.c_str());
	}

	~CDumpScope3()
	{
		os_string fmt ("o: ");
		fmt += m_strFmt1;
		D_OUTF3_EX(m_strFName.c_str(), m_iLine, m_iLevel, 
			fmt.c_str(), m_strExp1.c_str(), 
			m_strFmt2.c_str(), m_strExp2.c_str(),
			m_strFmt3.c_str(), m_strExp3.c_str());
	}

private:
	int m_iLine;
	os_string m_strFName;
	int m_iLevel;
	os_string m_strFmt1;
	os_string m_strExp1;
	os_string m_strFmt2;
	os_string m_strExp2;
	os_string m_strFmt3;
	os_string m_strExp3;
};

///////////////////////////////////////////////////////////////////////////////
// Makrodefinitionen
#define D_SCOPE_OUTF1(level,fmt,exp) \
	CDumpScope1 __Scope1(__FILE__, __LINE__, level, fmt, exp); \
	/**/

#define D_SCOPE_OUTF2(level,fmt1,exp1,fmt2,exp2) \
	CDumpScope2 __Scope2(__FILE__, __LINE__, level, fmt1, exp1, fmt2, exp2); \
	/**/

#define D_SCOPE_OUTF3(level,fmt1,exp1,fmt2,exp2,fmt3,exp3) \
	CDumpScope3 __Scope3(__FILE__, __LINE__, level, fmt1, exp1, fmt2, exp2, fmt3, exp3); \
	/**/

#define D_SCOPE_OUTF	D_SCOPE_OUTF1

#endif // defined(USE_DLIB_SCOPE) && defined(USE_DLIB)

///////////////////////////////////////////////////////////////////////////////
// Fallback definitions
#if !defined(D_SCOPE_OUTF1)
#define D_SCOPE_OUTF	D_OUTF
#define D_SCOPE_OUTF1	D_OUTF1
#define D_SCOPE_OUTF2	D_OUTF2
#define D_SCOPE_OUTF3	D_OUTF3
#endif // !define d(D_SCOPE_OUTF1)

#endif // !defined(_DUMPHELPERSCOPE_H__DB7BF445_0843_4A39_896A_719262B42F64__INCLUDED_)

// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 3.12.2002 11:18:23
//
// @doc
// @module CopyErrorList.h | Declaration of the <c CCopyErrorList> class

#if !defined(_COPYERRORLIST_H__FC3DA878_C836_4B8C_B7B3_1179E6BF282C__INCLUDED_)
#define _COPYERRORLIST_H__FC3DA878_C836_4B8C_B7B3_1179E6BF282C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include <ospace/std/string>

///////////////////////////////////////////////////////////////////////////////
//  Ein aufgetretener Fehler
class CCopyError
{
public:
    CCopyError(long lError, long lDlkName, char const *pcFile)
    :   m_lError(lError), m_lDlkName(lDlkName), m_strFile(pcFile) 
    {}
    ~CCopyError() {}
    
    char const *GetFileName() const { return m_strFile.c_str(); }
    long GetErrorCode() const { return m_lError; }
    long GetDlkName() const { return m_lDlkName; }
    
private:
    long m_lError;
    long m_lDlkName;
    std::string m_strFile;
};

///////////////////////////////////////////////////////////////////////////////
//  Liste der Fehler, die beim Kopieren aufgetreten sind
class CCopyErrorList
{
    typedef std::map<long, CCopyError> CErrorMap;
    
public:
    CCopyErrorList(void);
    ~CCopyErrorList(void);
    
    long AddErrorEntry(long lError, long lDlkName, char const *pcFile);
    void RemoveErrorEntry(long lIdx);
    CCopyError GetErrorEntry(long lIdx) const;
    
	void Lock() const { m_critsec.Lock(); }
	void Unlock() const { m_critsec.Unlock(); }

private:
    CErrorMap m_mapErrors;
    long m_lKeyIdx;
	mutable CComMultiThreadModel::AutoCriticalSection m_critsec;
};

///////////////////////////////////////////////////////////////////////////////
//  
class CCopyErrorListLock
{
public:
	CCopyErrorListLock(CCopyErrorList const &rp) :
	    m_rp(rp)
	{
		rp.Lock();
	}

	~CCopyErrorListLock()
	{
		m_rp.Unlock();
	}
	
private:
	CCopyErrorList const &m_rp;
};

#endif // !defined(_COPYERRORLIST_H__FC3DA878_C836_4B8C_B7B3_1179E6BF282C__INCLUDED_)

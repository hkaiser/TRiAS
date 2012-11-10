// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 3.12.2002 11:18:30
//
// @doc
// @module CopyErrorList.cpp | Implementation of the <c CCopyErrorList> class

#include "StdAfx.h"
#include "CopyErrorList.h"

CCopyErrorList::CCopyErrorList(void) : 
    m_lKeyIdx(1)
{
}

CCopyErrorList::~CCopyErrorList(void)
{
}

///////////////////////////////////////////////////////////////////////////////
//  
long CCopyErrorList::AddErrorEntry(long lError, long lDlkName, char const *pcFile)
{
CCopyErrorListLock lock(*this);

    m_mapErrors.insert(
        CErrorMap::value_type(++m_lKeyIdx, CCopyError(lError, lDlkName, pcFile))
    );
    return m_lKeyIdx;
}

void CCopyErrorList::RemoveErrorEntry(long lIdx)
{
CCopyErrorListLock lock(*this);
CErrorMap::iterator it = m_mapErrors.find(lIdx);

    if (it != m_mapErrors.end())
        m_mapErrors.erase(it);
}

CCopyError CCopyErrorList::GetErrorEntry(long lIdx) const
{
CCopyErrorListLock lock(*this);
CErrorMap::const_iterator it = m_mapErrors.find(lIdx);

    if (it == m_mapErrors.end())
        _com_issue_error(E_UNEXPECTED);

    return (*it).second;
}



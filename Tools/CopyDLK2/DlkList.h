// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.11.2002 10:3:24
//
// @doc
// @module DlkList.h | Declaration of the <c CDlkList> class

#if !defined(_DLKLIST_H__FB443F37_A5DB_477C_9DAF_BE2ADCCC2D9A__INCLUDED_)
#define _DLKLIST_H__FB443F37_A5DB_477C_9DAF_BE2ADCCC2D9A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/set>

///////////////////////////////////////////////////////////////////////////////
//  
class CDlkList :
    public std::set<long>
{
    typedef std::set<long> CDlksToCopy;
    
public:
    CDlkList(void);
    ~CDlkList(void);
    
    BOOL LoadFromFile (char const *pcFileName);
    
    bool IsLoaded() { return m_fIsLoaded; }
        
private:
    bool m_fIsLoaded; 
};

#endif // !defined(_DLKLIST_H__FB443F37_A5DB_477C_9DAF_BE2ADCCC2D9A__INCLUDED_)

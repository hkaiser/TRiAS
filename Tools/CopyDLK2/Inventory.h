// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 26.11.2002 20:46:45
//
// @doc
// @module Inventory.h | Declaration of the <c CInventory> class

#if !defined(_INVENTORY_H__0F2F7A6B_4D86_4150_9913_EE4215D68DE5__INCLUDED_)
#define _INVENTORY_H__0F2F7A6B_4D86_4150_9913_EE4215D68DE5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
//  
class CMapInventory :
    public std::map<long, long>
{
    typedef std::map<long, long> CInventory;
    
public:
    CMapInventory();
    ~CMapInventory();
    
    BOOL LoadFromFile(char const *pcFileName);
    bool IsLoaded() { return m_fIsLoaded; }
        
private:
    bool m_fIsLoaded; 
};

#endif // !defined(_INVENTORY_H__0F2F7A6B_4D86_4150_9913_EE4215D68DE5__INCLUDED_)

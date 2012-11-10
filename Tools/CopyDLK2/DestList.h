// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 10.12.2002 16:40:44
//
// @doc
// @module DestList.h | Declaration of the <c CDestList> class

#if !defined(_DESTLIST_H__BCFD9AF8_73FE_4C86_8295_505AB5321694__INCLUDED_)
#define _DESTLIST_H__BCFD9AF8_73FE_4C86_8295_505AB5321694__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>

///////////////////////////////////////////////////////////////////////////////
//  Dateitypen
#define FILETYPE_UNKNOWN    0x00
#define FILETYPE_TIF        0x01
#define FILETYPE_X          0x02
#define FILETYPE_TFW        0x04
#define FILETYPE_ALL        0x07

///////////////////////////////////////////////////////////////////////////////
//  
class CDestList :
    public std::map<long, DWORD>
{
    typedef std::map<long, DWORD> CDestListMap;

public:
    CDestList(void);
    ~CDestList(void);

    BOOL LoadFromDir (char const *pcDirName);
    long GetFileTypes() const 
    { 
        if (IsLoaded())
            return m_lFileType; 
        return FILETYPE_ALL;
    }

    bool IsLoaded() const { return m_fIsLoaded; }
    void Reset() { this->clear(); m_fIsLoaded = false; m_lFileType = 0; }
    
protected:
    BOOL LoadFromDirPattern(CDestListMap &rmapDest, long &rlFileTypes, 
        char const *pcPath, char const *pcPattern, long lFileType);
    
private:
    DWORD m_lFileType;
    bool m_fIsLoaded;
};

#endif // !defined(_DESTLIST_H__BCFD9AF8_73FE_4C86_8295_505AB5321694__INCLUDED_)

// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 10.12.2002 16:40:49
//
// @doc
// @module DestList.cpp | Implementation of the <c CDestList> class

#include "StdAfx.h"

#include <ospace/file/path.h>

#include "boost/directory.h"
#include "DestList.h"

CDestList::CDestList(void) :
    m_lFileType(0), m_fIsLoaded(false)
{
}

CDestList::~CDestList(void)
{
}

///////////////////////////////////////////////////////////////////////////////
//  
BOOL CDestList::LoadFromDirPattern(CDestListMap &rmapDest, long &rlFileTypes, 
    char const *pcPath, char const *pcPattern, long lFileType)
{
    using namespace boost::filesystem;

ospace::file::os_path filepath(pcPath);
dir_it end;

	for (dir_it it (std::string(filepath).c_str(), pcPattern); it != end; ++it) {
		if (get<is_directory>(it))
			continue;

    ospace::file::os_path name = *it;
    long lDlkName = strtoul(name.base().c_str(), NULL, 10);
    std::map<long, DWORD>::iterator cit = rmapDest.find(lDlkName);
    
        if (cit != rmapDest.end()) 
            (*cit).second |= lFileType;
        else 
            rmapDest.insert(value_type(lDlkName, lFileType));

        rlFileTypes |= lFileType;
    }
    return TRUE;
}

BOOL CDestList::LoadFromDir (char const *pcDirName)
{
    if (NULL == pcDirName || '\0' == *pcDirName)
        return FALSE;

    COM_TRY {
    CDestListMap mapDest;
    long lFileTypes = 0;
    
        if (!LoadFromDirPattern(mapDest, lFileTypes, pcDirName, "*.tif", FILETYPE_TIF))
            return FALSE;
        if (!LoadFromDirPattern(mapDest, lFileTypes, pcDirName, "*.x", FILETYPE_X))
            return FALSE;
        if (!LoadFromDirPattern(mapDest, lFileTypes, pcDirName, "*.tfw", FILETYPE_TFW))
            return FALSE;
        
        std::swap(mapDest, *this);
        m_lFileType = lFileTypes;
        m_fIsLoaded = true;
        
    } COM_CATCH_OP_RETURN((this->clear(), m_fIsLoaded = false), FALSE);
    return TRUE;
}



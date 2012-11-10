// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 26.11.2002 20:47:07
//
// @doc
// @module Inventory.cpp | Implementation of the <c CInventory> class

#include "StdAfx.h"

#include <fstream>

#include "inventory.h"

CMapInventory::CMapInventory(void) :
    m_fIsLoaded(false)
{
}

CMapInventory::~CMapInventory(void)
{
}
    
namespace {
    inline
    long GetCdNum (long lCdName)
    {
    long lNumber = lCdName - (lCdName/100)*100;
    
        _ASSERTE(lNumber != 0);
        return lNumber;
    }
}

///////////////////////////////////////////////////////////////////////////////
//  
BOOL CMapInventory::LoadFromFile(char const *pcFileName)
{
    if (NULL == pcFileName || '\0' == *pcFileName)
        return FALSE;

    COM_TRY {
    // neue Datei einlesen
    CInventory Entries;
    std::ifstream infile(pcFileName);
    
        if (infile.is_open()) {
            while (!infile.eof()) {
            std::string strLeft, strBottom, strCdNomenklatur;

                infile >> strLeft;
                infile >> strBottom;
                infile >> strCdNomenklatur;
            
            // zusätzlicher Test
                if (0 == strLeft.size() || 0 == strBottom.size() || 0 == strCdNomenklatur.size())
                    break;  // EOF reached
                    
            // in Liste einfügen
            long lLeft = atol(strLeft.c_str());
            long lBottom = atol(strBottom.c_str());
            long lDlkName = (lLeft/1000)*10000 + lBottom/1000;
            CInventory::iterator it = Entries.find(lDlkName);
            long lCdNomenklatur = atol(strCdNomenklatur.c_str());
            
                if (it == Entries.end()) {
                // erstes Vorkommen
                std::pair<CInventory::iterator, bool> p = Entries.insert(
                    CInventory::value_type(lDlkName, lCdNomenklatur));
                    
                    if (!p.second) {
                        this->clear();
                        return FALSE;
                    }
                }
                else {
                    if (GetCdNum(lCdNomenklatur) > GetCdNum((*it).second)) {
                    // Eintrag austauschen
                        (*it).second = lCdNomenklatur;
                    }
                }
            }
        
        // erfolgreich eingelesen
            std::swap (Entries, *this);
            m_fIsLoaded = true;
        }
        else {
            this->clear();
            return FALSE;
        }
        
    } COM_CATCH_OP_RETURN((this->clear(), m_fIsLoaded = false), FALSE);
    return TRUE;
}


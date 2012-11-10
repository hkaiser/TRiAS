// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.11.2002 10:3:29
//
// @doc
// @module DlkList.cpp | Implementation of the <c CDlkList> class

#include "StdAfx.h"

#include <fstream>

#include "dlklist.h"

CDlkList::CDlkList(void) :
    m_fIsLoaded(false)
{
}

CDlkList::~CDlkList(void)
{
}

///////////////////////////////////////////////////////////////////////////////
//  
BOOL CDlkList::LoadFromFile(char const *pcFileName)
{
    if (NULL == pcFileName || '\0' == *pcFileName)
        return FALSE;
        
    COM_TRY {
    // neue Datei einlesen
    CDlksToCopy Dlks;
    std::ifstream infile;
    
        infile.open(pcFileName);
        if (infile.is_open()) {
            while (!infile.eof()) {
            std::string line;
                
                infile >> line;

            // zusätzlicher EOF test
                if (0 == line.size())
                    break;
                    
            // in Liste einfügen
            long lNomenklatur = atol(line.c_str());
            CDlksToCopy::const_iterator cit = Dlks.find(lNomenklatur);
            
                if (cit == Dlks.end()) {
                std::pair<CDlksToCopy::iterator, bool> p = Dlks.insert(lNomenklatur);
                    
                    if (!p.second) {
                        this->clear();
                        return FALSE;
                    }
                }
            }
        
        // erfolgreich eingelesen
            std::swap (Dlks, *this);
            m_fIsLoaded = true;
        }
        else {
            this->clear();
            return FALSE;
        }
        
    } COM_CATCH_OP_RETURN((this->clear(), m_fIsLoaded = false), FALSE);
    return TRUE;
}



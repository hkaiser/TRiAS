// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.11.1999 11:26:39 
//
// @doc
// @module AttachNumber.h | Declaration of the <c CAttachNumber> class

#if !defined(_ATTACHNUMBER_H__9A77E1A7_83EA_402C_9E8E_F9BC02E87108__INCLUDED_)
#define _ATTACHNUMBER_H__9A77E1A7_83EA_402C_9E8E_F9BC02E87108__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/string/regexp.h>

class CAttachNumber
	: public os_regexp
{
public:
	CAttachNumber() : m_iCurrNumber(0), m_iStartAt(0) { pattern(".*(\\([[:digit:]]+\\))\\'"); }

	bool HasNumbering (LPCSTR pToTest)
	{
		try {
		// Eingabezeichenkette analysieren
		os_string strToTest (pToTest);
		int iMatched = match(strToTest);

			if (iMatched <= 0) 
				return false; 

			if (group(1).size() > 0) {
				m_iCurrNumber = atol (group(1).to_string().c_str());
				m_iStartAt = group(1).position() -2;	// " (" wieder wegschneiden
			} 
		} catch (...) {
			m_iCurrNumber = 0;
			m_iStartAt = 0;
		}
		return m_iCurrNumber != 0 ? true : false;
	}
	int GetCurrentNumber()
	{
		return m_iCurrNumber;
	}
	CString CorrectNumbering (LPCSTR pKey)
	{
		if (m_iCurrNumber == 0) {
			_ASSERTE(m_iCurrNumber != 0);
			return CString(pKey);
		}

	os_string strKey (pKey);
	char cbCnt[32];

		strKey = strKey.substr(0, m_iStartAt) + " (";
		strKey += _ltoa (m_iCurrNumber+1, cbCnt, 10);
		strKey += ')';
		return CString(strKey.c_str());
	}

private:
	int m_iCurrNumber;
	int m_iStartAt;
};

#endif // !defined(_ATTACHNUMBER_H__9A77E1A7_83EA_402C_9E8E_F9BC02E87108__INCLUDED_)

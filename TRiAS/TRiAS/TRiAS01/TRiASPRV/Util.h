// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.05.2001 12:48:29 
//
// @doc
// @module Util.h | Declaration of the <c CUtil> class

#if !defined(_UTIL_H__9307FF74_9A5B_49F4_90B4_E297E30C3A04__INCLUDED_)
#define _UTIL_H__9307FF74_9A5B_49F4_90B4_E297E30C3A04__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <math.h>
#include <time.h>

///////////////////////////////////////////////////////////////////////////////
// diverse Macros
#define _countof(x) (sizeof(x)/sizeof(x[0]))
#define DELETE_OBJ(p) if(!(p)) {} else { delete (p); (p) = NULL; }

///////////////////////////////////////////////////////////////////////////////
// Helper, um reine [out] Parameter sauber zu halten
inline BSTR *CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr) {
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT *CLEARED (CComVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();			//lint !e534, !e613
	return pv;
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
inline
bool StatementHasType (IParser *pIParser, STATEMENT_TYPE rgExpectedType)
{
STATEMENT_TYPE rgType = STATEMENT_TYPE_UNKNOWN;

	if (SUCCEEDED(pIParser -> get_StatementType(&rgType)))
		return rgType == rgExpectedType;
	return false;		// irgend ein Fehler
}

inline
bool ExpressionHasType (IExpressionItem *pIItem, EXPRESSIONITEM_TYPE rgExpectedType)
{
EXPRESSIONITEM_TYPE rgType = EXPRESSIONITEM_TYPE_UNKNOWN;

	if (SUCCEEDED(pIItem -> get_ItemType (&rgType)))
		return rgType == rgExpectedType;
	return false;		// irgend ein Fehler
}

inline
int CmpQuotedNames (LPCOLESTR pcName1, LPCOLESTR pcName2)
{
	if (L'[' == *pcName2 || L'`' == *pcName2)
		return wcsncmp (pcName1, pcName2+1, wcslen(pcName2)-2);
	return wcscmp (pcName1, pcName2);
}

inline 
CComBSTR RemoveQuotes(LPCOLESTR pcoleStr)
{
CComBSTR bstr;

	if (NULL != pcoleStr) {
		if (L'[' == *pcoleStr || L'`' == *pcoleStr) 
			bstr = CComBSTR(wcslen(pcoleStr)-2, pcoleStr+1);
		else
			bstr = pcoleStr;
	}
	return bstr;
}

///////////////////////////////////////////////////////////////////////////////
// DATE in einzelne Komponenten zerlegen
#define MIN_DATE			(-657434L)
#define MAX_DATE			2958465L
#define HALF_SECOND			(1.0/172800.0)

inline 
bool TmFromOleDate(DATE dtSrc, struct tm& tmDest)
{
static int rgMonthDays[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

// The legal range does not actually span year 0 to 9999.
	if (dtSrc > MAX_DATE || dtSrc < MIN_DATE) // about year 100 to about 9999
		return false;

long nDays;             // Number of days since Dec. 30, 1899
long nDaysAbsolute;     // Number of days since 1/1/0
long nSecsInDay;        // Time in seconds since midnight
long nMinutesInDay;     // Minutes in day

long n400Years;         // Number of 400 year increments since 1/1/0
long n400Century;       // Century within 400 year block (0,1,2 or 3)
long n4Years;           // Number of 4 year increments since 1/1/0
long n4Day;             // Day within 4 year block
						//  (0 is 1/1/yr1, 1460 is 12/31/yr4)
long n4Yr;              // Year within 4 year block (0,1,2 or 3)
bool bLeap4 = true;     // TRUE if 4 year block includes leap year

double dblDate = dtSrc; // tempory serial date

// If a valid date, then this conversion should not overflow
	nDays = (long)dblDate;

// Round to the second
	dblDate += ((dtSrc > 0.0) ? HALF_SECOND : -HALF_SECOND);

	nDaysAbsolute = (long)dblDate + 693959L; // Add days from 1/1/0 to 12/30/1899

	dblDate = fabs(dblDate);
	nSecsInDay = (long)((dblDate - floor(dblDate)) * 86400.);

// Calculate the day of week (sun=1, mon=2...)
//   -1 because 1/1/0 is Sat.  +1 because we want 1-based
	tmDest.tm_wday = (int)((nDaysAbsolute - 1) % 7L) + 1;

// Leap years every 4 yrs except centuries not multiples of 400.
	n400Years = (long)(nDaysAbsolute / 146097L);

// Set nDaysAbsolute to day within 400-year block
	nDaysAbsolute %= 146097L;

// -1 because first century has extra day
	n400Century = (long)((nDaysAbsolute - 1) / 36524L);

// Non-leap century
	if (n400Century != 0) {
	// Set nDaysAbsolute to day within century
		nDaysAbsolute = (nDaysAbsolute - 1) % 36524L;

	// +1 because 1st 4 year increment has 1460 days
		n4Years = (long)((nDaysAbsolute + 1) / 1461L);

		if (n4Years != 0)
			n4Day = (long)((nDaysAbsolute + 1) % 1461L);
		else {
			bLeap4 = false;
			n4Day = (long)nDaysAbsolute;
		}
	}
	else {
	// Leap century - not special case!
		n4Years = (long)(nDaysAbsolute / 1461L);
		n4Day = (long)(nDaysAbsolute % 1461L);
	}

	if (bLeap4) {
	// -1 because first year has 366 days
		n4Yr = (n4Day - 1) / 365;

		if (n4Yr != 0)
			n4Day = (n4Day - 1) % 365;
	}
	else {
		n4Yr = n4Day / 365;
		n4Day %= 365;
	}

// n4Day is now 0-based day of year. Save 1-based day of year, year number
	tmDest.tm_yday = (int)n4Day + 1;
	tmDest.tm_year = n400Years * 400 + n400Century * 100 + n4Years * 4 + n4Yr;

// Handle leap year: before, on, and after Feb. 29.
	if (n4Yr == 0 && bLeap4) {
	// Leap Year
		if (n4Day == 59) {
			/* Feb. 29 */
			tmDest.tm_mon = 2;
			tmDest.tm_mday = 29;
			goto DoTime;
		}

	// Pretend it's not a leap year for month/day comp.
		if (n4Day >= 60)
			--n4Day;
	}

// Make n4DaY a 1-based day of non-leap year and compute
//  month/day for everything but Feb. 29.
	++n4Day;

// Month number always >= n/32, so save some loop time */
	for (tmDest.tm_mon = (n4Day >> 5) + 1;
		n4Day > rgMonthDays[tmDest.tm_mon]; tmDest.tm_mon++);

	tmDest.tm_mday = (int)(n4Day - rgMonthDays[tmDest.tm_mon-1]);

DoTime:
	if (nSecsInDay == 0)
		tmDest.tm_hour = tmDest.tm_min = tmDest.tm_sec = 0;
	else {
		tmDest.tm_sec = (int)nSecsInDay % 60L;
		nMinutesInDay = nSecsInDay / 60L;
		tmDest.tm_min = (int)nMinutesInDay % 60;
		tmDest.tm_hour = (int)nMinutesInDay / 60;
	}

	return true;
}

inline
DBDATE DbDateFromDate (DATE dDate)
{
struct tm tm;
DBDATE db;

	TmFromOleDate(dDate, tm);
	db.year = tm.tm_year;
	db.month = tm.tm_mon;
	db.day = tm.tm_mday;
	return db;
}

#endif // !defined(_UTIL_H__9307FF74_9A5B_49F4_90B4_E297E30C3A04__INCLUDED_)

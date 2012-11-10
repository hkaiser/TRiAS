// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 05.07.2001 17:47:06 
//
// @doc
// @module DateTime.cpp | Definition of the <c CDateTime> class

#include "trias01p.hxx"

#include <time.h>
#include <DateTime.h>

/////////////////////////////////////////////////////////////////////////////
// COleDateTime class HELPER definitions
namespace {

// Verifies will fail if the needed buffer size is too large
#define MIN_DATE                (-657434L)  // about year 100
#define MAX_DATE                2958465L    // about year 9999

// Half a second, expressed in days
const double HALF_SECOND = 1.0/172800.0;

// One-based array of days in year at month start
const int MonthDays[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

// COleDateTime class HELPERS - implementation
	inline 
	bool OleDateFromTm(WORD wYear, WORD wMonth, WORD wDay,	WORD wHour, WORD wMinute, WORD wSecond, DATE& dtDest)
	{
	// Validate year and month (ignore day of week and milliseconds)
		if (wYear > 9999 || wMonth < 1 || wMonth > 12)
			return false;

	//  Check for leap year and set the number of days in the month
	BOOL bLeapYear = ((wYear & 3) == 0) && ((wYear % 100) != 0 || (wYear % 400) == 0);
	int nDaysInMonth = MonthDays[wMonth] - MonthDays[wMonth-1] + ((bLeapYear && wDay == 29 && wMonth == 2) ? 1 : 0);

	// Finish validating the date
		if (wDay < 1 || wDay > nDaysInMonth || wHour > 23 || wMinute > 59 || wSecond > 59)
			return false;

	// Cache the date in days and time in fractional days
	double dblTime;

	// It is a valid date; make Jan 1, 1AD be 1
	long nDate = wYear*365L + wYear/4 - wYear/100 + wYear/400 + MonthDays[wMonth-1] + wDay;

	//  If leap year and it's before March, subtract 1:
		if (wMonth <= 2 && bLeapYear)
			--nDate;

	//  Offset so that 12/30/1899 is 0
		nDate -= 693959L;

		dblTime = (((long)wHour * 3600L) +  // hrs in seconds
			((long)wMinute * 60L) +			// mins in seconds
			((long)wSecond)) / 86400.;

		dtDest = (double) nDate + ((nDate >= 0) ? dblTime : -dblTime);
		return true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Liefert aktuelle Systemzeit als DBTYPE_DATE
_TRIAS01_ENTRY double GetCurrentTimeAsDATE()
{
// Convert time_t to struct tm
time_t timeSrc = ::time(NULL);
tm *ptm = localtime(&timeSrc);
double dResult = 0;

	_ASSERTE(NULL != ptm);

	if (OleDateFromTm((WORD)(ptm->tm_year + 1900), (WORD)(ptm->tm_mon + 1), (WORD)ptm->tm_mday,
		(WORD)ptm->tm_hour, (WORD)ptm->tm_min, (WORD)ptm->tm_sec, dResult))
	{
		return dResult;
	}
	return 0;
}


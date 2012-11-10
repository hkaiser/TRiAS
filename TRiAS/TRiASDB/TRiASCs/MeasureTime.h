// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.11.2000 12:39:38 
//
// @doc
// @module MeasureTime.h | Declaration of the <c CMeasureTime> class

#if !defined(_MEASURETIME_H__63EDBF75_016F_457B_B22C_0C08176EE44B__INCLUDED_)
#define _MEASURETIME_H__63EDBF75_016F_457B_B22C_0C08176EE44B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CMeasureTime
{
public:
	CMeasureTime() 
	{
		QueryPerformanceCounter(&m_timeStartTime);
		QueryPerformanceFrequency(&m_timeFrequency);
	}
	double GetElapsedTime()
	{
	LARGE_INTEGER timeTime;

		QueryPerformanceCounter(&timeTime);
		return 1000. * double(timeTime.QuadPart - m_timeStartTime.QuadPart)/double(m_timeFrequency.QuadPart);
	}

private:
	LARGE_INTEGER m_timeStartTime;
	LARGE_INTEGER m_timeFrequency;
};

#endif // !defined(_MEASURETIME_H__63EDBF75_016F_457B_B22C_0C08176EE44B__INCLUDED_)

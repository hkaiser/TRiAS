// TITLE:
// High-Resolution Counter Class.
//
// VERSION:
// 1.0
//
// AUTHOR:
// Created by J.M.McGuiness, CompuServe ID [Jason_McGuiness].
//
// DESCRIPTION:
// This file declares a class the wraps the Pentium-specific time stamp counter.
// This counter has a resolution in terms of PCLKS (processor clocks) so it can
// be used for direct instruction timings.
//
// VERSION HISTORY:
// 26/3/96 Creation of version 1.0
//
// LEGALITIES:
// Copyright © 1996 by J.M.McGuiness, all rights reserved.
//
// This file must not be distributed without the author's prior
// consent.
//
/////////////////////////////////////////////////////////////////////////////

#include "contpre.hxx"
#include <time.h>
#include <math.h>

#include "p5ticker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

P5_Ticker::P5_Ticker(void)
{
//	Has_RDTSC=Check_Has_RDTSC();
	count.QuadPart=0;
}

P5_Ticker &P5_Ticker::operator=(const P5_Ticker &ts)
{
//	Has_RDTSC=ts.Has_RDTSC;
	count.QuadPart=ts.count.QuadPart;
	return (*this);
}

P5_Ticker &P5_Ticker::operator=(const ULARGE_INTEGER &ts)
{
//	Has_RDTSC=Check_Has_RDTSC();
	count.QuadPart=ts.QuadPart;
	return (*this);
}

#pragma optimize("",off)
P5_Ticker &P5_Ticker::Get_Time(void)
{
	if (Has_RDTSC)
	{
	volatile ULARGE_INTEGER ts;

		if (IsWinNT()) {
			QueryPerformanceCounter ((LARGE_INTEGER *)&ts);
		} else {
			_asm
			{
				cli							; privileged instruction !
				xor eax,eax
				push ecx
				push edx
				_emit 0x0f					; cpuid - serialise the processor
				_emit 0xa2
				pop edx
				pop ecx
				_emit 0x0f					; rdtsc
				_emit 0x31
				mov ts.HighPart,edx
				mov ts.LowPart,eax
				sti							; privileged instruction !
			}
		}
//		TX_TRACE1("Time stamp counter value: quad=%lu.\n",ts.QuadPart);
		count.QuadPart=ts.QuadPart;
	}
	else
	{
		count.QuadPart=0;
	}
	return (*this);
}
#pragma optimize("",on)

// The following function will work out the processor clock frequency to a
// specified accuracy determined by the target average deviation required.
// Note that the worst average deviation of the result is less than 5MHz for
// a mean frequency of 90MHz. So basically the target average deviation is
// supplied only if you want a more accurate result, it won't let you get a
// worse one. (Units are Hz.)
//
// (The average deviation is a better and more robust measure than it's cousin
// the standard deviation of a quantity. The item determined by each is
// essentially similar. See "Numerical Recipies", W.Press et al for more
// details.)
//
// This function will run for a maximum of 20 seconds before giving up on
// trying to improve the average deviation, with the average deviation
// actually achieved replacing the supplied target value. Use "max_loops" to
// change this. To improve the value the function converges to increase
// "interval" (which is in units of ms, default value=1000ms).

#pragma optimize("",off)
double P5_Ticker::Get_Frequency(double &target_ave_dev,const unsigned long interval,const unsigned int max_loops) const
{
// CEierUhr wait;
register ULARGE_INTEGER goal,period,current;
register unsigned int ctr=0;
double curr_freq,ave_freq;	// In Hz.
double ave_dev,tmp=0;
P5_Ticker s,f;

	if (!QueryPerformanceFrequency((LARGE_INTEGER *)&period))
	{
		throw no_performance_counter;
	}
	period.QuadPart*=interval;
	period.QuadPart/=1000;

	// Start of tight timed loop.
	QueryPerformanceCounter((LARGE_INTEGER *)&goal);
	goal.QuadPart+=period.QuadPart;
	s.Get_Time();
	do
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&current);
	} while(current.QuadPart<goal.QuadPart);
	f.Get_Time();
	// End of tight timed loop.

	ave_freq=1000*(double)((LONGLONG)(f-s).To_Ticks().QuadPart)/interval;
	do
	{
		// Start of tight timed loop.
		QueryPerformanceCounter((LARGE_INTEGER *)&goal);
		goal.QuadPart+=period.QuadPart;
		s.Get_Time();
		do
		{
			QueryPerformanceCounter((LARGE_INTEGER *)&current);
		} while(current.QuadPart<goal.QuadPart);
		f.Get_Time();
		// End of tight timed loop.

		// Average of the old frequency plus the new.
		curr_freq=1000*(double)((LONGLONG)(f-s).To_Ticks().QuadPart)/interval;
		ave_freq=(curr_freq+ave_freq)/2;

		// Work out the current average deviation of the frequency.
		tmp+=fabs(curr_freq-ave_freq);
		ave_dev=tmp/++ctr;
	} while (ave_dev>target_ave_dev && ctr<max_loops);
	target_ave_dev=ave_dev;
	TX_TRACE2("Estimated the processor clock frequency =%gHz, dev.=±%gHz.\n",ave_freq,ave_dev);
	return ave_freq;
}
#pragma optimize("",on)

#pragma optimize("",off)
BOOL P5_Ticker::Check_Has_RDTSC(void) const
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	if (sys_info.dwProcessorType==PROCESSOR_INTEL_PENTIUM)
	{
		try
		{
			_asm
			{
				_emit 0x0f				; rdtsc	
				_emit 0x31
			}
		}
		catch (...)	// Check to see if the opcode is defined.
		{
			TX_TRACE0("RDTSC instruction NOT present.\n");
			return FALSE;
		}
		// Check to see if the instruction ticks accesses something that changes.
		volatile ULARGE_INTEGER ts1,ts2;
		_asm
		{
			xor eax,eax
			_emit 0x0f					; cpuid
			_emit 0xa2
			_emit 0x0f					; rdtsc
			_emit 0x31
			mov ts1.HighPart,edx
			mov ts1.LowPart,eax
			xor eax,eax
			_emit 0x0f					; cpuid
			_emit 0xa2
			_emit 0x0f					; rdtsc
			_emit 0x31
			mov ts2.HighPart,edx
			mov ts2.LowPart,eax
		}
		// If we return true then there's a very good chance it's a real RDTSC instruction!
		if (ts2.HighPart==ts1.HighPart)
		{
			if (ts2.LowPart>ts1.LowPart)
			{
				TX_TRACE0("RDTSC instruction probably present.\n");
				return TRUE;
			}
			else
			{
				TX_TRACE0("RDTSC instruction NOT present.\n");
				return FALSE;
			}
		}
		else if (ts2.HighPart>ts1.HighPart)
		{
			TX_TRACE0("RDTSC instruction probably present.\n");
			return TRUE;
		}
		else
		{
			TX_TRACE0("RDTSC instruction NOT present.\n");
			return FALSE;
		}
	}
	else
	{
		TX_TRACE0("RDTSC instruction NOT present.\n");
		return FALSE;
	}
}

#pragma optimize("",on)


///////////////////////////////////////////////////////////////////////////////
// static variable
BOOL P5_Ticker::Has_RDTSC = P5_Ticker().Check_Has_RDTSC();

///////////////////////////////////////////////////////////////////////////////

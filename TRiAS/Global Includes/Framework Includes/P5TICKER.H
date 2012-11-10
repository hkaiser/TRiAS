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

typedef enum {
	no_performance_counter = 0,
} P5_Ticker_Errors_Type;

class _CTR_ENTRY32 P5_Ticker 
{
public:
	P5_Ticker(void);

inline P5_Ticker (const P5_Ticker &);
inline ~P5_Ticker (void) {};

	P5_Ticker &operator= (const P5_Ticker &);
	P5_Ticker &operator= (const ULARGE_INTEGER &);

inline P5_Ticker operator+ (const P5_Ticker &) const;
inline P5_Ticker operator- (const P5_Ticker &) const;
inline ULARGE_INTEGER To_Ticks (void) const { return count; }

	P5_Ticker &Get_Time (void);
	double Get_Frequency (double &, const unsigned long = 1000, 
						  const unsigned int = 20) const;

inline BOOL P5_Ticker_Available(void) const { return Has_RDTSC; }

private:
static BOOL Has_RDTSC;

	ULARGE_INTEGER count;	// unsigned 64-bit integer. (MFC data type.)

	BOOL Check_Has_RDTSC(void) const;
};

///////////////////////////////////////////////////////////////////////////////

inline P5_Ticker::P5_Ticker(const P5_Ticker &ts)
{
	count.QuadPart = ts.count.QuadPart;
}

inline P5_Ticker P5_Ticker::operator+ (const P5_Ticker &ts1) const
{
P5_Ticker ts;

	ts.count.QuadPart = count.QuadPart + ts1.count.QuadPart;
	return (ts);
}

inline P5_Ticker P5_Ticker::operator- (const P5_Ticker &ts1) const
{
P5_Ticker ts;

	ts.count.QuadPart = count.QuadPart - ts1.count.QuadPart;
	return (ts);
}


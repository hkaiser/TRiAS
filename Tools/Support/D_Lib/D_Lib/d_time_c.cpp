//
// *D_Lib* Copyright 1996-1999  Anatoly Kardash, anatoly-k@geocities.com
//
// Permission to use, copy, modify, and distribute, this software
// and its documentation for any purpose is hereby granted without
// fee, provided that the above copyright notice appear in all copies
// and that both that copyright notice and this permission notice
// appear in supporting documentation, and that the name of the
// copyright holders be used in advertising or publicity pertaining
// to distribution of the software with specific, written prior
// permission, and that no fee is charged for further distribution
// of this software, or any modifications thereof. The copyright
// holder make no representations about the suitability of this
// software for any purpose. It is provided "as is" without express
// or implied warranty.
//
// THE COPYRIGHT HOLDER DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
// SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR
// ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA, PROFITS, QPA OR GPA,
// WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
// ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//

#include <stdio.h>
#include <math.h>
#ifndef USE_GETTIMEOFDAY	/* { */
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#ifdef NO_FTIME_PROTO	/* { */
extern "C" int ftime(struct timeb *tp);
#endif			/* } NO_FTIME_PROTO */
#else				/* }{ USE_GETTIMEOFDAY */
#include <sys/time.h>
#endif				/* } USE_GETTIMEOFDAY */

#include <d_time_c.h>

void D_Time_c::Set()
{
#ifndef USE_GETTIMEOFDAY	/* { */

#ifdef _MSC_VER /* {  MSVC++ supports standard "stuct timeb" and
		   "ftime()" in a strange way */
    	struct _timeb tp; 
	_ftime( &tp);    
#else		/* }{ _MSC_VER */

    	struct timeb tp; 
	ftime( &tp);    

#endif		/* } _MSC_VER */

    	_sec = tp.time;
    	_usec = tp.millitm;

#else				/* }{ USE_GETTIMEOFDAY */

	struct timeval tv;
	gettimeofday( &tv, 0);
	_sec = tv.tv_sec;
	_usec = tv.tv_usec;

#endif				/* } USE_GETTIMEOFDAY */
} 

void D_Time_c::Set( long sec, long usec)
{
	_sec = sec;
	if( sec < 0)
		_usec = -usec;
	else
		_usec = usec;
}

D_Time_c& D_Time_c::operator =( const D_Time_c& time)
{
    	_sec = time._sec;
    	_usec = time._usec;
    	return( *this);
}

ostream& operator <<( ostream& os, const D_Time_c& t)
{
	char res[32];	// 32 - enough?
	sprintf( res, "%d.%03d", t.GetSec(), t.GetUsec());
	os << res << flush;
	return( os);
}

int operator ==( const D_Time_c& t1, const D_Time_c& t2)
{
	if( (t1._sec  == t2._sec) &&
            (t1._usec == t2._usec))
        	return( 1);
    	else
		return( 0);	
}

int operator !=( const D_Time_c& t1, const D_Time_c& t2)
{
	if( (t1._sec  != t2._sec) ||
            (t1._usec != t2._usec))
        	return( 1);
    	else
		return( 0);	
}


#ifndef __D_TIME_C_H__	/* { */
#define __D_TIME_C_H__

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

#include <iostream.h>

class D_Time_c
{

public:

	D_Time_c()
		{ Set(); } 
	D_Time_c( long sec, long usec = 0)
		{ Set( sec, usec); }
	D_Time_c( const D_Time_c& time)
		: _sec( time._sec),
		  _usec( time._usec)
		{}
	virtual ~D_Time_c()
		{}

	D_Time_c& operator =( const D_Time_c&);

	void Set();
	void Set( long sec, long usec = 0);

	long GetSec() const
		{ return( _sec); }
	long GetUsec () const
		{ return( _usec); }

friend int operator ==( const D_Time_c& t1, const D_Time_c& t2);
friend int operator !=( const D_Time_c& t1, const D_Time_c& t2);

friend ostream& operator <<( ostream&, const D_Time_c&);

private:

	long _sec;
	long _usec;   	// not short due to long is more standard and
			// therefore more suitable for e.g. Versant

};

#endif	/* } __D_TIME_C_H__ */

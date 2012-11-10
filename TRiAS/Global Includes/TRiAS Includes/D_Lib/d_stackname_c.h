#ifndef __D_STACKNAME_C_H__	/* { */
#define __D_STACKNAME_C_H__

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

#include <d_lib/d_lib_dll.h>

class DLIB_EXPORTED D_StackName_c
{
public:
	D_StackName_c( const char* stack_name);
	~D_StackName_c();

	const char* StackName()
	{ return( _stack_name); }

private:

	const char* _stack_name;

	D_StackName_c() {}
	D_StackName_c( const D_StackName_c&) {}
	D_StackName_c& operator =( const D_StackName_c&)
	{ return( *this); }

};


#endif	/* } __D_STACKNAME_C_H__ */

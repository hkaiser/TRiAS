#ifndef __D_SUPPORT_C_H__	/* { */
#define __D_SUPPORT_C_H__

/*
 * *D_Lib* Copyright 1996-1999  Anatoly Kardash, anatoly-k@geocities.com
 *
 * Permission to use, copy, modify, and distribute, this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that the above copyright notice appear in all copies
 * and that both that copyright notice and this permission notice
 * appear in supporting documentation, and that the name of the
 * copyright holders be used in advertising or publicity pertaining
 * to distribution of the software with specific, written prior
 * permission, and that no fee is charged for further distribution
 * of this software, or any modifications thereof. The copyright
 * holder make no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express
 * or implied warranty.
 *
 * THE COPYRIGHT HOLDER DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA, PROFITS, QPA OR GPA,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include <sys/types.h>
#include <limits.h>
#include <stdarg.h>

#ifdef __cplusplus	/* { */
#include <iostream.h>
#endif	/* } __cplusplus */

#include <d_lib/d_lib_dll.h>

#ifdef __cplusplus	/* { */

class DLIB_EXPORTED D_SupportAux_c
{
public:
	inline static ostream& D_Stream();
private:
	// this class is not for instantiation, so ...
	D_SupportAux_c() {}
	D_SupportAux_c( const D_SupportAux_c&) {}
	D_SupportAux_c& operator =( const D_SupportAux_c&)
	{ return( *this); }

friend class D_Support_c;	// to avoid warning of GNU C++
};


class DLIB_EXPORTED D_Support_c
{
public:
	enum Scope
	{
		D_ANY_SCOPE,	// for searching
		D_FILE_SCOPE,
		D_CLASS_SCOPE,
		D_STACK_SCOPE
	};

	static int DoPrintFor( const char* file,
			const char* class_name,
			unsigned int level);
	static int SetDoPrintFor( Scope scope,
			const char* mask,
			int level,
			int flag = 1);

	static int DoSelfTestFor( const char* file,
			const char* class_name,
			int level);
	static int SetDoSelfTestFor( const char* mask,
			Scope scope,
			int level,
			int flag = 1);

	static const char* Prefix( const char* fname,
			unsigned long line,
			const char* class_name,
			int level = -1);	// -1 --> all
	static int SetPrefix( const char* mask,
			Scope scope,
			int level,
			const char* format,
			int weight = INT_MIN);
		// - format is any string with possible elements:
		// <%FILE>, <%LINE>, <%CLASS>, <%LEVEL>,
		// <%PID>, <%TID>,
		// <%YEAR>, <%MONTH>, <%DAY>,
		// <%HOUR>, <%MIN>, <%SEC>, <%MSEC>
		// - don't use the "weight" arg - leave it default

	static void SetFileNameStrip( unsigned int level);

	static void SetRefreshInterval( const time_t interval);

	static ostream& D_Stream();

	static void Dump( ostream& to_where =
				D_SupportAux_c::D_Stream());
		// dumps the current settings

	static void Enter();
	static void Leave();

private:
	// this class is not for instantiation, so ...
	D_Support_c() {}
	D_Support_c( D_Support_c&) {}
	D_Support_c& operator =( D_Support_c&) { return( *this); }

	// functions parsing the config file
	static int SetDoPrintFor( const char* param, int weight);
	// param is:
	// "print@{file|class|stack}@[area]@[level]@{on|off|yes|no|0|1}"
	static int SetDoSelfTestFor( const char* param, int weight);
	// param is:
	// "selftest@{file|class|stack}@[area]@[level]@{on|off|yes|no|0|1}"
	static int SetPrefix( const char* param, int weight);
	// param is:
	// "prefix@{file|class|stack}@[area]@[level]@format"
	static int SetFileNameStrip( const char* param);
	// param is "fstrip@#"
	static int SetRefreshInterval( const char* param);
	// param is "refresh@#"
	static int SetD_Stream( const char* param);
	// param is "to_stream@{out|err}" or "to_file@filename"
	static int Dump( const char* param);
	// param is "dump"

friend void D_UpdateMaskInfos();	// sorry, another external name

};

DLIB_EXPORTED
ostream& D_SupportAux_c::D_Stream()
{
	return( D_Support_c::D_Stream());
}

extern "C"
{
#else	/* }{ __cplusplus */

/* These are functions wrapping the C++ methods and, therefore,
 * allowing to use D_Lib in C-programs.
 */

DLIB_EXPORTED
void D_C_Support_Enter();
DLIB_EXPORTED
void D_C_Support_Leave();

DLIB_EXPORTED
const char* D_C_Support_Prefix( const char* fname,
			unsigned long line,
			const char* class_name,
			int level);	/* -1 --> all */

DLIB_EXPORTED
int D_C_Support_DoPrintFor( const char* file,
			const char* class_name,
			unsigned int level);
DLIB_EXPORTED
int D_C_Support_DoSelfTestFor( const char* file,
			const char* class_name,
			int level);

#endif	/* } __cplusplus */

DLIB_EXPORTED
const char* D_C_Support_Sprintf( const char* fmt, ...);
DLIB_EXPORTED
void D_C_Support_Fprintf( int stream_flag, int format_flag,
		const char* prefix,
		const char* exp1, const char* str1,
		const char* exp2, const char* str2,
		const char* exp3, const char* str3,
		const char* exp4, const char* str4,
		const char* exp5, const char* str5);

#ifdef __cplusplus	/* { */

}	// extern "C"
#endif	/* } __cplusplus */

#endif	/* } __D_SUPPORT_C_H__ */

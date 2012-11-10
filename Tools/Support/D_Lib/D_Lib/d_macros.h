#ifndef __D_MACROS_H__	/* { */
#define __D_MACROS_H__

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

#ifdef __cplusplus	/* { */
#include <iostream.h>	// to support ostream and cerr
#endif	/* } __cplusplus */

#ifdef USE_DLIB					/* { */

#include <d_lib/d_support_c.h>

#ifdef __cplusplus	/* { */
#include <d_lib/d_stackname_c.h>
#endif	/* } __cplusplus */

#ifdef INSIDE_D_LIBRARY	/* { */

// some defines to avoid recursive calls from inside the
// debug library (inside the library everything is working
// always and prints to cerr)

#define D_SUPPORT_PREFIX(file,line,clnm)	\
					file << "(" << line << "): "
#define D_SUPPORT_PREFIX_LEVEL(file,line,clnm,level)	\
					file << "(" << line << "): "
#define D_SUPPORT_DOPRINT(file,clnm,level)  		(1)
#define D_SUPPORT_DOSELFTEST(file,clnm,level)	(1)
#define D_SUPPORT_STREAM()			cerr
#define D_SUPPORT_ENTER				/* nothing */
#define D_SUPPORT_LEAVE				/* nothing */

#else				/* }{ INSIDE_D_LIBRARY */

/* The defines commonly used in macros */

#ifdef __cplusplus	/* { */

#define D_SUPPORT_PREFIX(file,line,clnm)	\
			D_Support_c::Prefix(file,line,clnm)
#define D_SUPPORT_PREFIX_LEVEL(file,line,clnm,level)	\
			D_Support_c::Prefix(file,line,clnm,level)
#define D_SUPPORT_DOPRINT(file,clnm,level) \
			D_Support_c::DoPrintFor(file,clnm,level)
#define D_SUPPORT_DOSELFTEST(file,clnm,level) \
			D_Support_c::DoSelfTestFor(file,clnm,level)
#define D_SUPPORT_STREAM()	D_Support_c::D_Stream()
#define D_SUPPORT_ENTER		D_Support_c::Enter()
#define D_SUPPORT_LEAVE		D_Support_c::Leave()

#else	/* } __cplusplus */

/* C support functions */
#define D_SUPPORT_PREFIX(file,line,clnm)	\
			D_C_Support_Prefix(file,line,clnm,-1)
#define D_SUPPORT_PREFIX_LEVEL(file,line,clnm,level)	\
			D_C_Support_Prefix(file,line,clnm,level)
#define D_SUPPORT_DOPRINT(file,clnm,level) \
			D_C_Support_DoPrintFor(file,clnm,level)
#define D_SUPPORT_DOSELFTEST(file,clnm,level) \
			D_C_Support_DoSelfTestFor(file,clnm,level)
#define D_SUPPORT_ENTER		D_C_Support_Enter()
#define D_SUPPORT_LEAVE		D_C_Support_Leave()

#endif	/* } __cplusplus */

#endif				/* } INSIDE_D_LIBRARY */

#define D_SUPPORT_FPRINTF1(stream,format,prefix, \
		exp1,str1) \
			D_C_Support_Fprintf(stream,format,prefix, \
					exp1,str1, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0)
#define D_SUPPORT_FPRINTF2(stream,format,prefix, \
		exp1,str1, \
		exp2,str2) \
			D_C_Support_Fprintf(stream,format,prefix, \
					exp1,str1, \
					exp2,str2, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0)
#define D_SUPPORT_FPRINTF3(stream,format,prefix, \
		exp1,str1, \
		exp2,str2, \
		exp3,str3) \
			D_C_Support_Fprintf(stream,format,prefix, \
					exp1,str1, \
					exp2,str2, \
					exp3,str3, \
					(char*)0,(char*)0, \
					(char*)0,(char*)0)
#define D_SUPPORT_FPRINTF4(stream,format,prefix, \
		exp1,str1, \
		exp2,str2, \
		exp3,str3, \
		exp4,str4) \
			D_C_Support_Fprintf(stream,format,prefix, \
					exp1,str1, \
					exp2,str2, \
					exp3,str3, \
					exp4,str4, \
					(char*)0,(char*)0)
#define D_SUPPORT_FPRINTF5(stream,format,prefix, \
		exp1,str1, \
		exp2,str2, \
		exp3,str3, \
		exp4,str4, \
		exp5,str5) \
			D_C_Support_Fprintf(stream,format,prefix, \
					exp1,str1, \
					exp2,str2, \
					exp3,str3, \
					exp4,str4, \
					exp5,str5)
#define D_SUPPORT_SPRINTF(fmt,arg) \
			D_C_Support_Sprintf(fmt,arg)

#endif						/* } USE_DLIB */

/*
 * D_ macro may be used from both C++ and C
 */

/*-------------------------------------------------------------------
 * --- D_() macro ---
 *-------------------------------------------------------------------
 * The D_() macro allows to hide pieces of code from the production
 * version, i.e. the code inside will not be compiled at all. The macro
 * can be used for any source code not containing the ',' (comma)
 * characters.
 * E.g.:
 *
 * D_( cout << "This long message will be printed from the debug\n" <<
 * 	"version but will not be included even in binary code of\n" <<
 * 	"the production version\n"; )
 *
 * Please note:
 * 1. The line:
 *	D_( int a = 0, b = 1; printf( "a=%d,b=%d", a, b); )
 *    will NOT work due to ',' between declarations while:
 *	int a = 0, b = 1; D_( printf( "a=%d,b=%d", a, b); )
 *    will work fine.
 * 2. This macro is not syncronized, i.e. if it is used from, for
 *    example, different threads - the execution may be mixed.
 */

#ifdef USE_DLIB					/* { */
#define D_(token_list)		token_list
#else						/* }{ USE_DLIB */
#define D_(token_list)		/* nothing */
#endif						/* } USE_DLIB */

#ifdef __cplusplus	/* { */

//////////////////////////////////////////////////////////////////////
// D_P, D_S, D_PRINT and D_OUT families of macros are for C++ only! //
//////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
// --- D_P() macro family ---
//-------------------------------------------------------------------
// The D_P() macros just print (unconditionally) the argument
// expression(s) and the result of its/their evaluation. The result
// is sent to "ostream& cerr", so if the argument is a class then
// the appropriate operator should be defined. The macros is mostly
// useful when a programmer wants temporarily insert some debug print
// into the program (if he/she left them in the code then the output
// will ialways be generated for debug version and never for
// non-debug one). Please note again the same problem with commas.
// Another possible problem is: if the macros are used in a code that
// may be executed during initialization of static instances then this
// may happen before initialization of the "cerr" - guess what will
// you get :-(.
// E.g.:
//
// int a=5, b =6; D_P( a + b)
// D_P2( a + b, a - b)
//
// will print to the standard error:
//
// junk.cpp(15): a + b = [11]
// junk.cpp(16): a + b = [11], a - b = [-1]
//

#ifdef USE_DLIB					/* { */
#define D_P1(exp) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< #exp << " = [" << ::flush << (exp) << "]\n" \
		<< ::flush; D_SUPPORT_LEAVE; }
#define D_P2(exp1,exp2) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< #exp1 << " = [" << ::flush << (exp1) << "], " \
		<< #exp2 << " = [" << ::flush << (exp2) << "]\n" \
		<< ::flush; D_SUPPORT_LEAVE; }
#define D_P3(exp1,exp2,exp3) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< #exp1 << " = [" << ::flush << (exp1) << "], " \
		<< #exp2 << " = [" << ::flush << (exp2) << "], " \
		<< #exp3 << " = [" << ::flush << (exp3) << "]\n" \
		<< ::flush; D_SUPPORT_LEAVE; }
#define D_P4(exp1,exp2,exp3,exp4) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< #exp1 << " = [" << ::flush << (exp1) << "], " \
		<< #exp2 << " = [" << ::flush << (exp2) << "], " \
		<< #exp3 << " = [" << ::flush << (exp3) << "], " \
		<< #exp4 << " = [" << ::flush << (exp4) << "]\n" \
		<< ::flush; D_SUPPORT_LEAVE; }
#define D_P5(exp1,exp2,exp3,exp4,exp5) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< #exp1 << " = [" << ::flush << (exp1) << "], " \
		<< #exp2 << " = [" << ::flush << (exp2) << "], " \
		<< #exp3 << " = [" << ::flush << (exp3) << "], " \
		<< #exp4 << " = [" << ::flush << (exp4) << "], " \
		<< #exp5 << " = [" << ::flush << (exp5) << "]\n" \
		<< ::flush; D_SUPPORT_LEAVE; }
#define D_P				D_P1
#else						/* }{ USE_DLIB */
#define D_P1(exp)   			/* nothing */
#define D_P2(exp1,exp2)			/* nothing */
#define D_P3(exp1,exp2,exp3)		/* nothing */
#define D_P4(exp1,exp2,exp3,exp4)	/* nothing */
#define D_P5(exp1,exp2,exp3,exp4,exp5)	/* nothing */
#define D_P				D_P1
#endif						/* } USE_DLIB */

//-------------------------------------------------------------------
// --- D_S() macro family ---
//-------------------------------------------------------------------
// The D_S() macros are simplified form of the D_P() ones.
// These macros do the same work but print the result of the
// argument(s) evaluation only without (unlike the D_P()) the
// argument itself. The main purpose of these macros is temporary
// printing of some message(s) to standard error stream. All the
// problems of the D_P() macros remain for the D_S().
// E.g.:
//
// D_S( "I'm here!")
// int a = 5, b = 6;
// D_S2( "I'm here too:", a + b)
//
// will print to the standard error:
//
// junk.cpp(45): I'm here!
// junk.cpp(47): I'm here too: 11
//

#ifdef USE_DLIB					/* { */
#define D_S1(exp) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< (exp) << "\n" << ::flush; D_SUPPORT_LEAVE; }
#define D_S2(exp1,exp2) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< (exp1) << " " << ::flush \
		<< (exp2) << "\n" << ::flush; D_SUPPORT_LEAVE; }
#define D_S3(exp1,exp2,exp3) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< (exp1) << " " << ::flush \
		<< (exp2) << " " << ::flush \
		<< (exp3) << "\n" << ::flush; D_SUPPORT_LEAVE; }
#define D_S4(exp1,exp2,exp3,exp4) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< (exp1) << " " << ::flush \
		<< (exp2) << " " << ::flush \
		<< (exp3) << " " << ::flush \
		<< (exp4) << "\n" << ::flush; D_SUPPORT_LEAVE; }
#define D_S5(exp1,exp2,exp3,exp4,exp5) \
	{ D_SUPPORT_ENTER ; \
	cerr << D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()) << ::flush \
		<< (exp1) << " " << ::flush \
		<< (exp2) << " " << ::flush \
		<< (exp3) << " " << ::flush \
		<< (exp4) << " " << ::flush \
		<< (exp5) << "\n" << ::flush; D_SUPPORT_LEAVE; }
#define D_S				D_S1
#else						/* }{ USE_DLIB */
#define D_S1(exp)   			/* nothing */
#define D_S2(exp1,exp2)		/* nothing */
#define D_S3(exp1,exp2,exp3)		/* nothing */
#define D_S4(exp1,exp2,exp3,exp4)	/* nothing */
#define D_S5(exp1,exp2,exp3,exp4,exp5)	/* nothing */
#define D_S				D_S1
#endif						/* } USE_DLIB */

//-------------------------------------------------------------------
// --- D_PRINT() macro family ---
//-------------------------------------------------------------------
// The D_PRINT() macros are more general form of the D_P() macros
// and accepts also levelling argument. Also the macros support all
// the features of the debug library (run-time turning on/off,
// redirection, etc.) So the macro is predestinated to be remained
// in the source code "forever".
// E.g.:
//
// int a=5, b =6; D_PRINT( 2, a + b)
// D_PRINT2( 1, a + b, a - b)
//
// will print to the current debug output (if debug printing is
// turned on for both levels 1 and 2):
//
// junk.cpp(15): a + b = [11]
// junk.cpp(16): a + b = [11], a - b = [-1]
//
// and will print if debug printing is turned on for levels 2 only:
//
// junk.cpp(15): a + b = [11]
//

#ifdef USE_DLIB					/* { */
#define D_PRINT1(level,exp) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush \
			<< #exp << " = [" << ::flush << (exp) \
			<< "]\n" << ::flush; } \
	D_SUPPORT_LEAVE; }
#define D_PRINT2(level,exp1,exp2) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush \
			<< #exp1 << " = [" << ::flush << (exp1) << "] " \
			<< #exp2 << " = [" << ::flush << (exp2) << "]\n" \
			<< ::flush; } \
	D_SUPPORT_LEAVE; }
#define D_PRINT3(level,exp1,exp2,exp3) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush \
			<< #exp1 << " = [" << ::flush << (exp1) << "] " \
			<< #exp2 << " = [" << ::flush << (exp2) << "]\n" \
			<< #exp3 << " = [" << ::flush << (exp3) << "]\n" \
			<< ::flush; } \
	D_SUPPORT_LEAVE; }
#define D_PRINT4(level,exp1,exp2,exp3,exp4) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush \
			<< #exp1 << " = [" << ::flush << (exp1) << "] " \
			<< #exp2 << " = [" << ::flush << (exp2) << "]\n" \
			<< #exp3 << " = [" << ::flush << (exp3) << "]\n" \
			<< #exp4 << " = [" << ::flush << (exp4) << "]\n" \
			<< ::flush; } \
	D_SUPPORT_LEAVE; }
#define D_PRINT5(level,exp1,exp2,exp3,exp4,exp5) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush \
			<< #exp1 << " = [" << ::flush << (exp1) << "] " \
			<< #exp2 << " = [" << ::flush << (exp2) << "]\n" \
			<< #exp3 << " = [" << ::flush << (exp3) << "]\n" \
			<< #exp4 << " = [" << ::flush << (exp4) << "]\n" \
			<< #exp5 << " = [" << ::flush << (exp5) << "]\n" \
			<< ::flush; } \
	D_SUPPORT_LEAVE; }
#define D_PRINT			D_PRINT1
#else						/* }{ USE_DLIB */
#define D_PRINT1(level,exp)			/* nothing */
#define D_PRINT2(level,exp1,exp2)		/* nothing */
#define D_PRINT3(level,exp1,exp2,exp3)		/* nothing */
#define D_PRINT4(level,exp1,exp2,exp3,exp4)	/* nothing */
#define D_PRINT5(level,exp1,exp2,exp3,exp4,exp5) /* nothing */
#define D_PRINT				D_PRINT1
#endif						/* } USE_DLIB */

//-------------------------------------------------------------------
// --- D_OUT(level) macro ---
//-------------------------------------------------------------------
// The D_OUT() macro may be used like a standard "cout" and "cerr"
// streams but supports all the features of the debug library. Please
// note that the code following the macro remains in result of any
// compilation and take space of the "CODE" section althought may be
// not executed if compiled without USE_DLIB flag defined.
// E.g.:
//
// D_OUT(1) << "a + b = [" << a + b << "] - I'm here!\n" << D_END;
//
// will print to the current debug output (if debug printing is
// turned on for the level 1, of course):
//
// bar.cpp(321): a + b = [11] - I'm here!
//

#ifdef USE_DLIB					/* { */
#define D_OUT(level) \
	{ D_SUPPORT_ENTER; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		{ D_SUPPORT_STREAM() << D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, D_Lib_D_GetD_LibClassName(), level) << ::flush
#define D_END \
		::flush; } \
	D_SUPPORT_LEAVE; }
#else						/* }{ USE_DLIB */
#define D_OUT(level)		{if(1){} else cerr
#define D_END			::flush;}
#endif						/* } USE_DLIB */

#endif	/* } __cplusplus */

/*********************************************************************
 * D_PF, D_SF, D_PRINTF and D_OUTF families of macros are for both
 * C and C++.
 ********************************************************************/

/*-------------------------------------------------------------------
 * --- D_PF() macro family ---
 *-------------------------------------------------------------------
 * The D_PF() macros just print (unconditionally) the result of its
 * argument evaluation according to specified format. The result
 * is sent to the stderr stream. The macros is mostly
 * useful when a programmer wants temporarily insert some debug print
 * into the program (if he/she left them in the code then the output
 * will always be generated for debug version and never for
 * non-debug one). Please note again the same problem with commas
 * as in macros D_ and D_P.
 * E.g.:
 *
 * int a=5, b =6; D_PF( "%04d", a + b)
 * D_PF2( "%d%%", a + b, "%d", a - b)
 *
 * will print to the standard error:
 *
 * junk.cpp(15): a + b = [0011]
 * junk.cpp(16): a + b = [11%], a - b = [-1]
 */

#ifdef USE_DLIB					/* { */
#define D_PF1(fmt,exp) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF1( 0, 1, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		#exp, D_SUPPORT_SPRINTF( fmt, (exp))); \
		D_SUPPORT_LEAVE; }
#define D_PF2(fmt1,exp1,fmt2,exp2) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF2( 0, 1, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2))); \
		D_SUPPORT_LEAVE; }
#define D_PF3(fmt1,exp1,fmt2,exp2,fmt3,exp3) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF3( 0, 1, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3))); \
		D_SUPPORT_LEAVE; }
#define D_PF4(fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF4( 0, 1, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3)), \
		#exp4, D_SUPPORT_SPRINTF( fmt4, (exp4))); \
		D_SUPPORT_LEAVE; }
#define D_PF5(fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4,fmt5,exp5) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF5( 0, 1, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3)), \
		#exp4, D_SUPPORT_SPRINTF( fmt4, (exp4)), \
		#exp5, D_SUPPORT_SPRINTF( fmt5, (exp5))); \
		D_SUPPORT_LEAVE; }
#define D_PF				D_PF1
#else						/* }{ USE_DLIB */
#define D_PF1(exp)   			/* nothing */
#define D_PF2(exp1,exp2)		/* nothing */
#define D_PF3(exp1,exp2,exp3)		/* nothing */
#define D_PF4(exp1,exp2,exp3,exp4)	/* nothing */
#define D_PF5(exp1,exp2,exp3,exp4,exp5)	/* nothing */
#define D_PF				D_PF1
#endif						/* } USE_DLIB */

/*-------------------------------------------------------------------
 * --- D_SF() macro family ---
 *-------------------------------------------------------------------
 * The D_SF() macros are simplified form of the D_PF() ones.
 * These macros do the same work but print the result of the
 * argument(s) evaluation only without (unlike the D_PF()) the
 * argument itself. The main purpose of these macros is temporary
 * printing of some message(s) to standard error stream. All the
 * problems of the D_PF() macros remain for the D_SF().
 * E.g.:
 *
 * D_SF( "%s", "I'm here!")
 * int a = 5, b = 6;
 * D_SF2( "I'm here too: x%02X", a + b)
 *
 * will print to the standard error:
 *
 * junk.cpp(45): I'm here!
 * junk.cpp(47): I'm here too: x0B
 */

#ifdef USE_DLIB					/* { */
#define D_SF1(fmt,exp) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF1( 0, 0, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		"", D_SUPPORT_SPRINTF( fmt, (exp))); \
		D_SUPPORT_LEAVE; }
#define D_SF2(fmt1,exp1,fmt2,exp2) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF2( 0, 0, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		"", D_SUPPORT_SPRINTF( fmt2, (exp2))); \
		D_SUPPORT_LEAVE; }
#define D_SF3(fmt1,exp1,fmt2,exp2,fmt3,exp3) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF3( 0, 0, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		"", D_SUPPORT_SPRINTF( fmt3, (exp3))); \
		D_SUPPORT_LEAVE; }
#define D_SF4(fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF4( 0, 0, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		"", D_SUPPORT_SPRINTF( fmt3, (exp3)), \
		"", D_SUPPORT_SPRINTF( fmt4, (exp4))); \
		D_SUPPORT_LEAVE; }
#define D_SF5(fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4,fmt5,exp5) \
	{ D_SUPPORT_ENTER ; \
	D_SUPPORT_FPRINTF5( 0, 0, \
		D_SUPPORT_PREFIX( __FILE__, __LINE__, D_Lib_D_GetD_LibClassName()), \
		"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
		"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
		"", D_SUPPORT_SPRINTF( fmt3, (exp3)), \
		"", D_SUPPORT_SPRINTF( fmt4, (exp4)), \
		"", D_SUPPORT_SPRINTF( fmt5, (exp5))); \
		D_SUPPORT_LEAVE; }
#define D_SF				D_SF1
#else						/* }{ USE_DLIB */
#define D_SF1(exp)   			/* nothing */
#define D_SF2(exp1,exp2)		/* nothing */
#define D_SF3(exp1,exp2,exp3)		/* nothing */
#define D_SF4(exp1,exp2,exp3,exp4)	/* nothing */
#define D_SF5(exp1,exp2,exp3,exp4,exp5)	/* nothing */
#define D_SF				D_SF1
#endif						/* } USE_DLIB */

/*-------------------------------------------------------------------
 * --- D_PRINTF(() macro family ---
 *-------------------------------------------------------------------
 * The D_PRINTF() macros are more general form of the D_PF() macros
 * and accepts also levelling argument. Also the macros support all
 * the features of the debug library (run-time turning on/off,
 * redirection, etc.) So the macro is predestinated to be remained
 * in the source code "forever".
 * E.g.:
 *
 * int a=5, b =6; D_PRINTF( 2, "%04d", a + b)
 * D_PRINTF2( 1, "%d%%", a + b, "%d" a - b)
 *
 * will print to the current debug output (if debug printing is
 * turned on for both levels 1 and 2):
 *
 * junk.cpp(15): a + b = [0011]
 * junk.cpp(16): a + b = [11%], a - b = [-1]
 *
 * and will print if debug printing is turned on for levels 2 only:
 *
 * junk.cpp(15): a + b = [0011]
 */

#ifdef USE_DLIB					/* { */
#define D_PRINTF1(level,fmt,exp) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF1( 1, 1, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			#exp, D_SUPPORT_SPRINTF( fmt, (exp))); \
	D_SUPPORT_LEAVE; }
#define D_PRINTF2(level,fmt1,exp1,fmt2,exp2) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF2( 1, 1, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2))); \
	D_SUPPORT_LEAVE; }
#define D_PRINTF3(level,fmt1,exp1,fmt2,exp2,fmt3,exp3) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF3( 1, 1, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3))); \
	D_SUPPORT_LEAVE; }
#define D_PRINTF4(level,fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF4( 1, 1, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3)), \
			#exp4, D_SUPPORT_SPRINTF( fmt4, (exp4))); \
	D_SUPPORT_LEAVE; }
#define D_PRINTF5(level,fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4,fmt5,exp5) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF5( 1, 1, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			#exp1, D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			#exp2, D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			#exp3, D_SUPPORT_SPRINTF( fmt3, (exp3)), \
			#exp4, D_SUPPORT_SPRINTF( fmt4, (exp4)), \
			#exp5, D_SUPPORT_SPRINTF( fmt5, (exp5))); \
	D_SUPPORT_LEAVE; }
#define D_PRINTF			D_PRINTF1
#else						/* }{ USE_DLIB */
#define D_PRINTF1(level,exp)			/* nothing */
#define D_PRINTF2(level,exp1,exp2)		/* nothing */
#define D_PRINTF3(level,exp1,exp2,exp3)		/* nothing */
#define D_PRINTF4(level,exp1,exp2,exp3,exp4)	/* nothing */
#define D_PRINTF5(level,exp1,exp2,exp3,exp4,exp5) /* nothing */
#define D_PRINTF			D_PRINTF1
#endif						/* } USE_DLIB */

/*-------------------------------------------------------------------
 * --- D_OUTF() macro family ---
 *-------------------------------------------------------------------
 * The D_OUTF() macros are simplified form of the D_PRINTF() ones.
 * These macros do the same work but print the result of the
 * argument(s) evaluation only without (unlike the D_PRINTF()) the
 * argument itself. The advantage of these macros is that freely
 * formatted output may be done using all the facilities of D_Lib.
 * E.g.:
 *
 * D_OUTF( 2, "%s", "I'm here!")
 * int a = 5, b = 6;
 * D_OUTF2( 1, "I'm here too: x%02X", a + b)
 *
 * will print to the current debug output (if debug printing is
 * turned on for both levels 1 and 2):
 *
 * junk.cpp(45): I'm here!
 * junk.cpp(47): I'm here too: x0B
 *
 * and will print if debug printing is turned on for levels 2 only:
 *
 * junk.cpp(45): I'm here!
 */

#ifdef USE_DLIB					/* { */
#define D_OUTF1(level,fmt,exp) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF1( 1, 0, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			"", D_SUPPORT_SPRINTF( fmt, (exp))); \
	D_SUPPORT_LEAVE; }
#define D_OUTF2(level,fmt1,exp1,fmt2,exp2) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF2( 1, 0, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			"", D_SUPPORT_SPRINTF( fmt2, (exp2))); \
	D_SUPPORT_LEAVE; }
#define D_OUTF3(level,fmt1,exp1,fmt2,exp2,fmt3,exp3) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF3( 1, 0, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			"", D_SUPPORT_SPRINTF( fmt3, (exp3))); \
	D_SUPPORT_LEAVE; }
#define D_OUTF4(level,fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF4( 1, 0, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			"", D_SUPPORT_SPRINTF( fmt3, (exp3)), \
			"", D_SUPPORT_SPRINTF( fmt4, (exp4))); \
	D_SUPPORT_LEAVE; }
#define D_OUTF5(level,fmt1,exp1,fmt2,exp2,fmt3,exp3,fmt4,exp4,fmt5,exp5) \
	{ D_SUPPORT_ENTER ; \
	if( D_SUPPORT_DOPRINT( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else \
		D_SUPPORT_FPRINTF5( 1, 0, D_SUPPORT_PREFIX_LEVEL( \
				__FILE__, __LINE__, \
				D_Lib_D_GetD_LibClassName(), level), \
			"", D_SUPPORT_SPRINTF( fmt1, (exp1)), \
			"", D_SUPPORT_SPRINTF( fmt2, (exp2)), \
			"", D_SUPPORT_SPRINTF( fmt3, (exp3)), \
			"", D_SUPPORT_SPRINTF( fmt4, (exp4)), \
			"", D_SUPPORT_SPRINTF( fmt5, (exp5))); \
	D_SUPPORT_LEAVE; }
#define D_OUTF			D_OUTF1
#else						/* }{ USE_DLIB */
#define D_OUTF1(level,exp)			/* nothing */
#define D_OUTF2(level,exp1,exp2)		/* nothing */
#define D_OUTF3(level,exp1,exp2,exp3)		/* nothing */
#define D_OUTF4(level,exp1,exp2,exp3,exp4)	/* nothing */
#define D_OUTF5(level,exp1,exp2,exp3,exp4,exp5) /* nothing */
#define D_OUTF			D_OUTF1
#endif						/* } USE_DLIB */

/*
 * D_SELFTEST macro may be used from both C++ and C
 */

/*-------------------------------------------------------------------
 * --- D_SELFTEST(level) macro ---
 *-------------------------------------------------------------------
 * The D_SELFTEST() macro is a "prefix" for a code that performs
 * self-testing actions and may be turned on/off by the level.
 * Please note that like the D_OUT() macro all the code will remain
 * even when compiled without USE_DLIB flag although will not be
 * executed.
 * E.g.:
 *
 * int a[10];
 * init_a_array( a, 10);
 * D_SELFTEST(1) {
 * 	for( int i = 0; i < 10; i ++)
 * 		if( a[i] != i)
 * 			cerr << "Internal error: " <<
 * 				"illegal array initialization" << endl;
 * }
 *
 * will execute the written code if is compiled with USE_DLIB flag and
 * the self-testing for level 1 is turned on.
 */

#ifdef USE_DLIB					/* { */
#define D_SELFTEST(level) \
	if( D_SUPPORT_DOSELFTEST( __FILE__, D_Lib_D_GetD_LibClassName(), level) == 0) \
		{ /* do nothing */  } \
	else
#else						/* }{ USE_DLIB */
#define D_SELFTEST(level)		if(1){} else
#endif						/* } USE_DLIB */

#ifdef __cplusplus	/* { */

////////////////////////////////////////////////////////////////
// D_CLASS macro is for C++ only!                             //
// (Anyway we need the D_Lib_D_GetD_LibClassName() in C also) //
////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
// --- D_CLASS() macro ---
//-------------------------------------------------------------------
// The D_CLASS() macro is a class name definition that must be
// included in the class declaration if user wants to have facility
// to turn on/off printing/selftesting using the class name as well
// as file names.
// Please note that when the code is compiled without USE_DLIB flag
// then this macro is expanded to nothing, so it does not impact the
// result of compilation.
// E.g.:
//
// class My_c
// {
// D_CLASS( My_c)
// public:
// 	void my_method()
// 	{
// 		D_OUT(1) << "in my_method()\n" << D_END;
// 		// do something
// 	}
// };
//
// will allow to turn the printing on by the following line in the
// D_Lib config file:
// print:class:My_c:1:on
// (or, of course, by calling the appropriate method of the
// D_Support_c).
//

#ifdef USE_DLIB					/* { */

// These macro and function make available in any scope call of
// the D_Lib_D_GetD_LibClassName() function:
// if the function is called from inside of a class method then it
// returns the class name, otherwise NULL pointer showing that
// this point is out of any class scope.
// Requirement: the class definition must contain macro D_CLASS().

#define D_CLASS(class_name) \
	private: \
		static const char* D_Lib_D_GetD_LibClassName() \
			{ return( #class_name); }

#else						/* }[ USE_DLIB */

#define D_CLASS(class_name)   			private:

#endif						/* } USE_DLIB */

#endif	/* } __cplusplus */

#ifdef USE_DLIB					/* { */

static
#ifdef __cplusplus	/* { */
inline
#endif	/* } __cplusplus */
const char* D_Lib_D_GetD_LibClassName()
{
	return( 0);
}

#endif						/* } USE_DLIB */

#ifdef __cplusplus	/* { */

////////////////////////////////////////////////////////////////
// D_STACK macro is for C++ only!                             //
////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------
// --- D_STACK() macro ---
//-------------------------------------------------------------------
// The D_STACK() macro is a stack "name" definition that must be
// included in the place from which the stack scope is interested
// (if user wants to have facility to turn on/off printing/selftesting
// using the stack name as well as file and class names). When the
// real stack scope disappeares (e.g.. by leaving the function)
// the D_STACK() macro's domain is also left. So this macro allows
// to manipulate with printing/etc. in the current function and
// in all functions that are called from it.
// Please note that when the code is compiled without USE_DLIB flag
// then this macro is expanded to nothing, so it does not impact the
// result of compilation.
// E.g.:
//
// static void my_lovely_proc( int a)
// {
// 	D_OUT(3) << "my_lovely_proc() a = [" << a << "]\n" << D_END;
// }
//
// void my_lovely_func()
// {
// D_STACK( my_lovely_func)
//
// 	D_OUT(1) << "my_lovely_func()\n" << D_END;
// 	for( int a = 15; a >=0; a--)
//		my_lovely_proc( a);
// }
//
// will allow to turn the printing on by the following line in the
// D_Lib config file:
// print:stack:my_lovely_func:1:on
// (or, of course, by calling the appropriate method of the
// D_Support_c).
//

#ifdef USE_DLIB					/* { */

#define D_STACK_CONCAT(arg1,arg2)		arg1##arg2
#define D_STACK_INSTANCE_NAME(line) \
			D_STACK_CONCAT( D_Lib_D_SNameObject, line)
#define D_STACK(stack_name) \
	D_StackName_c D_STACK_INSTANCE_NAME( __LINE__)( #stack_name);

#else						/* }[ USE_DLIB */

#define D_STACK(stack_name)   			/* nothing */

#endif						/* } USE_DLIB */

#endif	/* } __cplusplus */

#endif	/* } __D_MACROS_H__ */

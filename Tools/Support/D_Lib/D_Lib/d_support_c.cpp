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

#define INSIDE_D_LIBRARY	// to avoid recursive calls 
#define INSIDE_DLIB_SOURCES	// for proper DLL declarations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

#ifdef _WIN32	/* { WinNT, non-portable! */

#include <io.h>		// for _open()
#include <process.h>	// for getpid()
#include <windows.h>	// for multithreading support

#include <ospace/stlex/dbgstream.h>

// WinNT's file names are not "fully" case-sensitive, so...
#define FILE_NAMES_CASE_UNSENSITIVE

#else	/* }{ _WIN32 */

#include <unistd.h>	// for access(), getpid(), etc.

#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
#include <pthread.h>	// at least for Sun/Solaris2 and SGI/IRIX5
#endif	/* } NO_POSIX_THREADS_SUPPORT */

#endif	/* } _WIN32 */

#include <iostream.h>
#include <fstream.h>

#include <d_macros.h>
#include <d_support_c.h>
#include <d_stackname_c.h>
#include <d_time_c.h>
#include <d_list_c.h>
#include <d_levelinfo_c.h>
#include <d_maskinfo_c.h>

#ifdef FILENAME_MAX	/* { */
#if FILENAME_MAX >= 1024
#define D_FNAME_MAX	FILENAME_MAX
#else
#define D_FNAME_MAX	2048
#endif
#else			/* }{ FILENAME_MAX */
#define D_FNAME_MAX	2048
#endif			/* } FILENAME_MAX */

// Please note:
//
// The internal classes:
//
//	D_SupportInit_c
//	D_StackInfo_c
//
// are not surrounded by "#ifdef USE_DLIB/#endif" to have the same
// set of classes independently on which compilation of this lib
// was used.

// = { ================ Multithreading support ====================

#ifdef USE_DLIB					/* { */

#if defined( _WIN32) && defined( _MT)	/* { */

inline static long get_current_thread_id()
{
	long tid = (long)GetCurrentThreadId();
	return( tid);
}

static CRITICAL_SECTION d_crit_section;
static int d_crit_section_inited = 0;

inline static void init_critical_section()
{
	if( d_crit_section_inited)
		return;
	d_crit_section_inited = 1;
	InitializeCriticalSection( &d_crit_section);
}

inline static void delete_critical_section()
{
	if( !d_crit_section_inited)
		return;
	d_crit_section_inited = 0;
	DeleteCriticalSection( &d_crit_section);
}

inline static void enter_critical_section()
{
	init_critical_section();
	EnterCriticalSection( &d_crit_section);
}

inline static void leave_critical_section()
{
	LeaveCriticalSection( &d_crit_section);
}

#else	/* }{ _WIN32 && _MT */

// NOTE: non-POSIX threading is not supported

inline static long get_current_thread_id()
{
#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
	long tid = (long)pthread_self();
	return( tid);
#else	/* }{ NO_POSIX_THREADS_SUPPORT */
	// non-POSIX threading is not supported
	return( -1);
#endif	/* } NO_POSIX_THREADS_SUPPORT */
}

#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
// Hopefully this will be executed before creation of
// any thread (that may be done by some user in another
// static instance initialization).
static pthread_mutex_t d_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t locked_thread = (pthread_t)INT_MAX;
static int locked_count = 0;
#endif	/* } NO_POSIX_THREADS_SUPPORT */

inline static void init_critical_section()
{
	// nothing for non-Win32 platforms
}

inline static void delete_critical_section()
{
	// nothing for non-Win32 platforms
}

inline static void enter_critical_section()
{
#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
	//cerr << "===== [" << get_current_thread_id() <<
	//		"] - before lock()\n" << flush;
	pthread_t cur_thread = pthread_self();
	if( pthread_equal( locked_thread, cur_thread))
	{
		locked_count ++ ;
		return;
	}
	pthread_mutex_lock( &d_mutex);
	locked_thread = cur_thread;
	locked_count ++ ;
	//cerr << "===== [" << get_current_thread_id() <<
	//		"] - after lock()\n" << flush;
#endif	/* } NO_POSIX_THREADS_SUPPORT */
}

inline static void leave_critical_section()
{
#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
	//cerr << "===== [" << get_current_thread_id() <<
	//		"] - before unlock()\n" << flush;
	locked_count -- ;
	if( locked_count > 0)
		return;
	locked_thread = (pthread_t)INT_MAX;
	pthread_mutex_unlock( &d_mutex);
	//cerr << "===== [" << get_current_thread_id() <<
	//		"] - after unlock()\n" << flush;
#endif	/* } NO_POSIX_THREADS_SUPPORT */
}

#endif	/* } _WIN32 && _MT */

#else						/* }{ USE_DLIB */

// for non-USE_DLIB version the 2 funcs are required from the
// "local" class D_SupportInit_c

inline static void init_critical_section()
{
	// empty for non-USE_DLIB version
}

inline static void delete_critical_section()
{
	// empty for non-USE_DLIB version
}

#endif						/* } USE_DLIB */

class D_SupportInit_c
{
public:
	D_SupportInit_c()
		{
			init_critical_section();
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
			set_regerror_func( D_RegError);
#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
		}
	~D_SupportInit_c()
		{ delete_critical_section(); }
};
static D_SupportInit_c a_static_instance;

// = } ============ Enf of multithreading support =================

#ifdef USE_DLIB					/* { */

// keywords for config-file
static const char* stdstream_kw = "to_stream@";
static const char* filename_kw = "to_file@";
static const char* newfilename_kw = "to_new_file@";
static const char* print_kw = "print@";
static const char* selftest_kw = "selftest@";
static const char* fstrip_kw = "fstrip@";
static const char* refresh_kw = "refresh@";
static const char* prefix_kw = "prefix@";
static const char* dump_kw = "dump";

// weight for "manually" set parameters:
static int man_weight = 0;
// weights for external params (i.e. from file) are from INT_MIN+1 to...
// weights for internal params (i.e. from code) are from 1 to...
// (INT_MIN can not be used, it plays one of the roles:
// - sign that other weight must be used;
// - value for default params, i.e. the minimal weight)

// keywords to be substituted in the prefix/filename
static const char* pid_kw = "<%PID>";		// prefix/fname
static const char* tid_kw = "<%TID>";		// prefix
static const char* year_kw = "<%YEAR>";		// prefix/fname
static const char* month_kw = "<%MONTH>";	// prefix/fname
static const char* day_kw = "<%DAY>";		// prefix/fname
static const char* hour_kw = "<%HOUR>";		// prefix/fname
static const char* min_kw = "<%MIN>";		// prefix/fname
static const char* sec_kw = "<%SEC>";		// prefix/fname
static const char* msec_kw = "<%MSEC>";		// prefix
static const char* file_kw = "<%FILE>";		// prefix
static const char* line_kw = "<%LINE>";		// prefix
static const char* class_kw = "<%CLASS>";	// prefix
static const char* level_kw = "<%LEVEL>";	// prefix

#endif						/* } USE_DLIB */

#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
const D_RegExpImpl_c*	D_RegExpImpl_c::_current = 0;
#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

class D_StackInfo_c
{
public:

	D_StackInfo_c( D_StackName_c* stack_name)
		: _stack_name( stack_name),
		  _counter( 1)
	{}

	const char* StackName() const
	{ return( _stack_name->StackName()); }
	unsigned int Counter() const
	{ return( _counter); }

	void IncCounter()
	{ _counter ++ ; }
	void DecCounter()
	{ _counter -- ; }

private:

	D_StackName_c	*_stack_name;
	unsigned int	_counter;

	D_StackInfo_c() {}
	D_StackInfo_c( const D_StackInfo_c&) {}
	D_StackInfo_c& operator =( const D_StackInfo_c&)
	{ return( *this); }

};

#ifdef USE_DLIB					/* { */

// This function says if D_Lib will print something by itself
// (the directive "dump" will work always)
static inline int to_work_silently()
{
	static int was_here = 0;
	static int silently = 0;

	if( !was_here)
	{
		// The presense of the DLIB_SILENCE env.var. says
		// that D_Lib will not print anything by itself
		char* d_silence_env = getenv( "TRiASDMP_SILENCE");
		if( d_silence_env)
			silently = 1;
		was_here = 1;
	}
	return( silently);
}


static inline ostream* get_d_stream();

#if defined( _WIN32) && defined( _MT)	/* { */
// In MSWin the handler for threads must be initialized
// before creation of the threads

static DWORD InitTlsIndex()
{
	DWORD TlsIndex = TlsAlloc();
	if( TlsIndex == TLS_OUT_OF_INDEXES)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: TlsAlloc() "
				"failed - thread safe support "
				"disabled\n" << flush;
	}
	return( TlsIndex);
}

static DWORD d_lib_TlsIndex = InitTlsIndex();

#else	/* }{ _WIN32 && _MT */

#ifndef NO_POSIX_THREADS_SUPPORT	/* { */
static void delete_si( void* data)
{
	D_VoidList_c* stack_infos = (D_VoidList_c*)data;
	if( stack_infos)
		delete stack_infos;
}
#endif	/* } NO_POSIX_THREADS_SUPPORT */

#endif	/* } _WIN32 && _MT */

static D_VoidList_c* get_d_lib_stack_infos()
{
#if defined( _WIN32) && defined( _MT)	/* { */

	if( d_lib_TlsIndex != TLS_OUT_OF_INDEXES)
	{
		LPVOID ptr = TlsGetValue( d_lib_TlsIndex);
		if( ptr)
			return( (D_VoidList_c*)ptr);
		// Well, this is a memory leak... So what? :-)
		ptr = (LPVOID)new D_VoidList_c;
		if( TlsSetValue( d_lib_TlsIndex, ptr) == 0)
		{
			if( !to_work_silently())
				*get_d_stream() << "TRiASDMP: "
					"TlsSetValue() failed"
					" - thread safe support "
					"disabled\n" << flush;
			TlsFree( d_lib_TlsIndex);
			d_lib_TlsIndex = TLS_OUT_OF_INDEXES;
		}
		else if( ( ptr = TlsGetValue( d_lib_TlsIndex)) == 0)
		{
			if( !to_work_silently())
				*get_d_stream() << "TRiASDMP: "
					"TlsGetValue() failed"
					" - thread safe support "
					"disabled\n" << flush;
			TlsFree( d_lib_TlsIndex);
			d_lib_TlsIndex = TLS_OUT_OF_INDEXES;
		}
		else
			return( (D_VoidList_c*)ptr);
	}
	
	static D_VoidList_c* si = 0;
	if( si == 0)
		si = new D_VoidList_c;
	return( si);


#else	/* }{ _WIN32 && _MT */

#ifndef NO_POSIX_THREADS_SUPPORT	/* { */

	static int thread_key_created = 0;
	static pthread_mutex_t	mutex_for_si;
	static pthread_key_t	key_for_si;

	if( !thread_key_created)
	{
		pthread_mutex_lock( &mutex_for_si);
		// retest after lock
		if( !thread_key_created)
		{
			thread_key_created ++ ;
			pthread_key_create( &key_for_si, delete_si);
		}
		pthread_mutex_unlock( &mutex_for_si);
	}
	void* ptr = pthread_getspecific( key_for_si);
	if( ptr)
		return( (D_VoidList_c*)ptr);
	ptr = (void*)new D_VoidList_c;
	pthread_setspecific( key_for_si, ptr);
	ptr = pthread_getspecific( key_for_si);
	return( (D_VoidList_c*)ptr);

#else	/* }{ NO_POSIX_THREADS_SUPPORT */

	static D_VoidList_c* ptr = 0;
	// Yes, this is a memory leak... But so it works for statics!
	if( ptr == 0)
		ptr = new D_VoidList_c;
	return( ptr);

#endif	/* } NO_POSIX_THREADS_SUPPORT */
#endif	/* } _WIN32 && _MT */
}

// ---- to use instead cout/cerr that may be not ready yet

// some compilers (e.g. SGI) reject inlining if func has static
// vars, so...
static ofstream* d_cerr = 0;
static inline ostream* get_cerr()
{
	// Yes, this is a memory leak... But so it works for statics!
	if( d_cerr == 0)
	{
		d_cerr = new ofstream;
		d_cerr->attach( fileno( stderr));
	}
	return( d_cerr);
}

// some compilers (e.g. SGI) reject inlining if func has static
// vars, so...
static ofstream* d_cout = 0;
static inline ostream* get_cout()
{
	// Yes, this is a memory leak... But so it works for statics!
	if( d_cout == 0)
	{
		d_cout = new ofstream;
		d_cout->attach( fileno( stdout));
	}
	return( d_cout);
}

#if defined(_WIN32)
// #HK990305: BEGIN
static odbgstream* d_cdbg = 0;
static inline ostream* get_cdbg()
{
	// Yes, this is a memory leak... But so it works for statics!
	if( d_cdbg == 0)
	{
		d_cdbg = new odbgstream;
	}
	return( d_cdbg);
}
// #HK990305: END
#endif // _WIN32

static inline int is_there_stderr()
{
#ifdef _WIN32	/* { WinNT, non-portable! */

	PIMAGE_DOS_HEADER dos_hd = (PIMAGE_DOS_HEADER)
					GetModuleHandle( NULL);
	PIMAGE_NT_HEADERS nt_hd = (PIMAGE_NT_HEADERS)(
			(DWORD)dos_hd + (DWORD)dos_hd->e_lfanew);
	if( dos_hd->e_magic != IMAGE_DOS_SIGNATURE ||
	    nt_hd->Signature != IMAGE_NT_SIGNATURE)
		return( 0);

	DWORD ss = nt_hd->OptionalHeader.Subsystem;
	if( ss == IMAGE_SUBSYSTEM_WINDOWS_CUI ||
	    ss == IMAGE_SUBSYSTEM_OS2_CUI ||
	    ss == IMAGE_SUBSYSTEM_POSIX_CUI)
		return( 1);

	return( 0);

#else	/* }{ _WIN32 */
	return( 1);
#endif	/* }{ _WIN32 */
}

// a forward prototype - not to change the structure
static int set_d_file( const char* fname, int reporting, int new_file = 0);

static ostream* d_stream = 0;
static inline ostream* get_d_stream()
{
	// for the first time (i.e. by default):
	// - if this is MSWindows (NT/95/...) application where
	//   standard output/error are not defined: to file
	//   "dlib.out"
	// - otherwise: to stderr
	if( d_stream == 0)
	{
		if( is_there_stderr())
			d_stream = get_cerr();
		else
			set_d_file( "TRiASDMP.log", 0);
	}
	return( d_stream);
}

static ofstream* d_ofstream = 0;
static int was_ofstream = 0;
static D_String_c* d_fname = 0;

static unsigned int d_fname_stripping_level = 3;
		// i.e. by default "/dir1/dir2/dir3/fname.ext" -->
		//			".../dir2/dir3/fname.ext"

static char* canonize_fname( const char* fname)
{
#ifdef FILE_NAMES_CASE_UNSENSITIVE	/* { */

	static char can_fname[ D_FNAME_MAX * 3]; // enough for mask?
	int i = 0;
	for( ; fname[i] != '\0'; i ++)
		can_fname[i] = toupper( fname[i]);
	can_fname[i] = '\0';
	return( can_fname);

#else	/* }{ FILE_NAMES_CASE_UNSENSITIVE */

	return( (char*)fname);

#endif	/* } FILE_NAMES_CASE_UNSENSITIVE */
}

static char* canonize_quotedname( const char* qname)
{
	if( qname[0] != '"')
		return( (char*)qname);
	static char can_qname[2048];	// enough for class/stack name?
	int i = 1;
	for( ; qname[i] != '\0' && qname[i] != '"'; i ++)
		can_qname[i] = qname[i];
	can_qname[i] = '\0';
	return( can_qname);
}

static inline D_MaskInfo_c* get_default_mask()
// the accepted default: nothing to do if not asked
{
	D_MaskInfo_c* default_mask = new D_MaskInfo_c(
		".*", D_Support_c::D_FILE_SCOPE, INT_MIN, -1, (long)0);
	     // all areas, scope <file>, minimal weight, all levels, off
			// i.e. by default nobody does smth.
	return( default_mask);
}

static const char* default_prefix_format =
	"<%PID>:<%FILE>(<%LINE>):";
	// e.g. "123:.../aaa/bbb.cpp(567):"
static inline D_MaskInfo_c* get_default_prefix()
{
	//default_prefix = new D_MaskInfo_c(
	D_MaskInfo_c* default_prefix = new D_MaskInfo_c(
		".*", D_Support_c::D_FILE_SCOPE, INT_MIN, -1,
	  // all areas, scope <file>, minimal weight, all levels
				(char*)default_prefix_format);
	return( default_prefix);
}

enum ForPrintOrSelfTest
{
	FOR_PRINT,
	FOR_SELFTEST
};

static void delete_mask_info( void* mi, void* )
{
	D_MaskInfo_c* minfo = (D_MaskInfo_c*)mi;
	delete minfo;
}

static D_VoidList_c* get_mask_infos_long( ForPrintOrSelfTest which)
{
	static D_VoidList_c* print_mask_infos = 0;
	static D_VoidList_c* selftest_mask_infos = 0;
	// Yes, this is a memory leak... But so it works for statics!
	if( print_mask_infos == 0)
	{
		print_mask_infos =
			new D_VoidList_c( delete_mask_info);
		selftest_mask_infos =
			new D_VoidList_c( delete_mask_info);
	}
	switch( which)
	{
		case FOR_PRINT:
			return( print_mask_infos);
		case FOR_SELFTEST:
			return( selftest_mask_infos);
		default:
			// should not be, but...
			// no exceptions, etc. - we are in the debug lib!
			if( !to_work_silently())
				*get_d_stream() <<
					"TRiASDMP: internal error\n" <<
					flush;
			return( 0);
	}
}

static D_VoidList_c* get_mask_infos_string()
{
	static D_VoidList_c* mask_infos = 0;
	// Yes, this is a memory leak... But so it works for statics!
	if( mask_infos == 0)
		mask_infos = new D_VoidList_c( delete_mask_info);
	return( mask_infos);
}

static time_t refresh_interval = 5;

static inline int need_update( const char* d_cfg_fname)
{
	static int was_here = 0;
	static struct stat buf;
	static time_t last_check = 0;
	static time_t last_read = 0;

	// for testing only!
	//static int counter = 0;
	//counter ++ ;
	//if( counter == 5)
	//{
	//	counter = 0;
	//	return( 1);
	//}

	time_t cur_check = time( 0);
	if( cur_check - last_check < refresh_interval)
		return( 0);
	last_check = cur_check;
	if( stat( d_cfg_fname, &buf) != 0)	// if no file
	{					// then once only
		if( was_here)
			return( 0);
		was_here = 1;
		return( 1);
	}
	was_here = 1;

	if( buf.st_mtime != last_read)
	{
		last_read = buf.st_mtime;
		return( 1);
	}
	return( 0);
}

static void strip_spaces( char* str)
{
	char* s = str;
	while( *s != '\0' && !isgraph( *s))
		s ++;
	if( *s == '\0')
	{
		str[0] = '\0';
		return;
	}
	char *d;
	if( s != str)
	{
		for( d = str; *s != '\0' ; d++, s ++)
			*d = *s;
		*d = '\0';
	}
	else
		d = str + strlen( str);
	d --;
	while( d >= str && !isgraph( *d))
		d --;
	*( d + 1) = '\0';
}

static char* get_d_cfg_fname()
{
	char* d_cfg_env = getenv( "TRiASDMP_CONFIG");
	if( d_cfg_env)
		return( d_cfg_env);
	return( "TRiASDMP.cfg");
}

void D_UpdateMaskInfos()
{
	static const char* d_cfg_fname = 0;
	if( d_cfg_fname == 0)
		d_cfg_fname = get_d_cfg_fname();

	if( !need_update( d_cfg_fname))
		return;

	// ---- to clear our lists and to set defaults
	//
	// (The following 3 insert()s are memory leaks... These are
	// the default settings of D_Lib and hopefully not too much
	// leaked memory.)

	// print infos
	get_mask_infos_long( FOR_PRINT)->clear();
	get_mask_infos_long( FOR_PRINT)->insert( get_default_mask());

	// selftest infos
	get_mask_infos_long( FOR_SELFTEST)->clear();
	get_mask_infos_long( FOR_SELFTEST)->insert( get_default_mask());

	// prefix infos
	get_mask_infos_string()->clear();
	get_mask_infos_string()->insert( get_default_prefix());

	// does the config file exist?
	if( access( d_cfg_fname, 0) == -1)
		return;

	// try to read it
	FILE* fp = fopen( d_cfg_fname, "r");
	if( fp == NULL)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: failed to open "
				"file " << d_cfg_fname << "\n" << flush;
		return;
	}
	if( !to_work_silently())
		*get_d_stream() << "TRiASDMP: reading configuration "
			"from " << d_cfg_fname << "...\n" << flush;
	char buf[1024];
	int weight = INT_MIN;
	while( fgets( buf, sizeof( buf) - 1, fp))
	{
		weight ++ ;	// i.e. starts from INT_MIN+1
		strip_spaces( buf);
		if( buf[0] == '#')	// comment
			continue;
		if( buf[0] == '\0')	// empty
			continue;
		if( D_Support_c::SetFileNameStrip( buf) ||
		    D_Support_c::SetD_Stream( buf) ||
		    D_Support_c::SetDoPrintFor( buf, weight) ||
		    D_Support_c::SetDoSelfTestFor( buf, weight) ||
		    D_Support_c::SetPrefix( buf, weight) ||
		    D_Support_c::SetRefreshInterval( buf) ||
		    D_Support_c::Dump( buf))
			continue;
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: configuration "
				"file " << d_cfg_fname << " contains "
				"illegal line [" << buf << "]\n" <<
				flush;
	}
	fclose( fp);
}

static char* get_brief_fname( const char* full_fname)
{
	static char res[ D_FNAME_MAX + 1];
	char* s = strrchr( full_fname, '/');
#ifdef _WIN32	/* { WinNT, non-portable! */
	if( s == 0)
		s = strrchr( full_fname, '\\'); 
#endif	/* } _WIN32 */
	if( s == 0)
		strcpy( res, full_fname);
	else
		strcpy( res, s + 1);
	s = strchr( res, '.');
	if( s != 0)
		*s = '\0';
	return( res);
}

static int find_mask_info( void* mi, void* data)
{
	D_MaskInfo_c* minfo = (D_MaskInfo_c*)mi;
	const char* mask = (const char*)data;
	if( minfo->CompareMask( mask))
		return( 1);
	return( 0);
}

static void print_about_change_something( const char* what,
		D_Support_c::Scope scope,
		const char* mask, int level, int flag)
{
	if( to_work_silently())
		return;

	*get_d_stream() << "TRiASDMP: " << what << " for " << flush;
	switch( scope)
	{
		case D_Support_c::D_FILE_SCOPE:
			*get_d_stream() << "files" << flush;
			break;
		case D_Support_c::D_CLASS_SCOPE:
			*get_d_stream() << "classes" << flush;
			break;
		case D_Support_c::D_STACK_SCOPE:
			*get_d_stream() << "stacks" << flush;
			break;
		default:
			*get_d_stream() << "<unknown scope>" << flush;
			break;
	}
	*get_d_stream() << " [" <<
		mask << "] and level [" << flush;
	if( level == -1)
		*get_d_stream() << "all" << flush;
	else
		*get_d_stream() << level << flush;
	*get_d_stream() << "] is turned " << flush;
	if( flag)
		*get_d_stream() << "on" << flush;
	else
		*get_d_stream() << "off" << flush;
	*get_d_stream() << "\n" << flush;
}

static void print_about_change_prefix( D_Support_c::Scope scope,
		const char* mask,
		int level, const char* format)
{
	if( to_work_silently())
		return;

	*get_d_stream() << "TRiASDMP: prefix for " << flush;
	switch( scope)
	{
		case D_Support_c::D_FILE_SCOPE:
			*get_d_stream() << "files" << flush;
			break;
		case D_Support_c::D_CLASS_SCOPE:
			*get_d_stream() << "classes" << flush;
			break;
		case D_Support_c::D_STACK_SCOPE:
			*get_d_stream() << "stacks" << flush;
			break;
		default:
			*get_d_stream() << "<unknown scope>" << flush;
			break;
	}
	*get_d_stream() << " [" <<
		mask << "] and level [" << flush;
	if( level == -1)
		*get_d_stream() << "all" << flush;
	else
		*get_d_stream() << level << flush;
	*get_d_stream() << "] is changed to [" <<
		format << "]\n" << flush;
}

static void* get_info_from_info_collections(
		D_VoidList_c* infos,
		const char* fname, const char* class_name,
		unsigned int level, int* found)
{
	static const int all_lvl = -1;
	char* fkey = 0;
	char* ckey = 0;
	D_VoidList_c* stack_infos = get_d_lib_stack_infos();
	size_t s_entries = stack_infos->entries();
	int cur_weight = INT_MIN;
	void* res = 0;

	*found = 0;
	size_t m_entries = infos->entries();
	// Please note: we pass through all the elements due to
	// the same mask are stored in the same elements of
	// the list not in order of their specification,
	// the order is specified by "weight" - see comments
	// at the beginning of the source.
	for( size_t i = 0; i < m_entries; i ++)
	{
		D_MaskInfo_c* mi = (D_MaskInfo_c*)infos->at( i);
		D_VoidList_c& levels = mi->GetLevelInfos();

		//if( class_name)
		//	D_P3( fname, class_name, mi)
		//else
		//	D_P2( fname, mi);
		size_t l_entries = levels.entries();
		for( size_t j = 0; j < l_entries; j ++)
		{
			D_LevelInfo_c* li =
				(D_LevelInfo_c*)levels.at( j);
			if( li->_no != (const int)level &&
			    li->_no != all_lvl)
				continue;
			if( li->_weight < cur_weight)
				continue;

			if( li->_scope == D_Support_c::D_FILE_SCOPE)
			{
				if( fkey == 0)
				  fkey = canonize_fname(
					get_brief_fname( fname));
				if( mi->Compare( fkey))
				{
					res = li->_info;
					cur_weight = li->_weight;
					*found = 1;
				}
			}

			if( class_name != 0 &&
			    li->_scope == D_Support_c::D_CLASS_SCOPE)
			{
				if( ckey == 0)
				  ckey = canonize_quotedname(
							class_name);
				if( mi->Compare( ckey))
				{
					res = li->_info;
					cur_weight = li->_weight;
					*found = 1;
				}
			}

			if( s_entries != 0 &&
			    li->_scope == D_Support_c::D_STACK_SCOPE)
			{
				D_VoidList_c* stack_infos =
					get_d_lib_stack_infos();
				for( size_t l = 0; l < s_entries; l ++)
				{
					D_StackInfo_c* si =
						(D_StackInfo_c*)
						   stack_infos->at( l);
					char* skey =
					  canonize_quotedname(
						si->StackName());
					if( mi->Compare( skey))
					{
						res = li->_info;
						cur_weight =
							li->_weight;
						*found = 1;
						break;
					}
				}
			}

		}
	}

	//D_P2( *found, res);
	return( res);
}

static int do_something_for( ForPrintOrSelfTest which,
		const char* fname, const char* class_name,
		unsigned int level)
{
	int found = 0;
	int flag = (int)get_info_from_info_collections(
			get_mask_infos_long( which),
			fname, class_name, level, &found);
	if( !found)
	{
		if( !to_work_silently())
		{
			*get_d_stream() << "TRiASDMP: could not find "
				"flag for: file [" << fname << "]" <<
				flush;
			if( class_name)
				*get_d_stream() << ", class [" <<
					class_name << "]" << flush;
			*get_d_stream() << ", level [" << level <<
				"] - assumed value 1\n" << flush;
		}
		flag = 1;
	}
	return( flag);
}

static int set_do_something_for( ForPrintOrSelfTest which,
		const char* mask, D_Support_c::Scope scope,
		int weight, int level, int flag)
{
	static const char* what_for_print =
					"debug printing";
	static const char* what_for_selftest =
					"selftest code execution";
	const char* what = what_for_print;
	if( which != FOR_PRINT)
		what = what_for_selftest;

	const char* msk = 0;
	if( scope == D_Support_c::D_FILE_SCOPE)
		msk = canonize_fname( mask);
	else
		msk = mask;
	size_t index = get_mask_infos_long( which)->index(
				find_mask_info, (void*)msk);
	if( index == NO_SUCH_ELEMENT)
	{
		D_MaskInfo_c* mi = new D_MaskInfo_c(
				msk, scope, weight, level, flag);
		if( mi->GetRegExpStatus() != D_RegExp_c::OK)
		{
			delete mi;
			return( 0);
		}
		get_mask_infos_long( which)->insert( mi);
		print_about_change_something( what,
				scope, msk, level, flag);
		return( 1);
	}
	D_MaskInfo_c* minfo =
		(D_MaskInfo_c*)get_mask_infos_long( which)->at( index);
	minfo->SetLevelInfo( scope, weight, level, flag);
	print_about_change_something( what, scope, msk, level, flag);
	return( 1);
}

static inline int get_level_value( const char* level,
		const char* kw, const char* param)
{
	int lvl = atoi( level);
	if( lvl < 0 ||
	  ( lvl == 0 && *level != '0'))
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: illegal format of "
				"the " << kw << " directive: [" <<
				param << "] (level " << "[" << level <<
				"])\n" << flush;
		return( INT_MIN);
	}
	return( lvl);
}

static int get_param_elements( const char* param,
		const char* kw, unsigned int kw_len,
		D_Support_c::Scope& scope,
		char*& arg_beg,
		char*& new_param,
		char*& area,
		int& lvl1, int& lvl2,
		char*& val)
{
	// does the param begin with the keyword?
	if( strncmp( param, kw, kw_len) != 0)
		return( 0);
	arg_beg = (char*)( param + kw_len);

	// well, let's extract the scope ({file|class|stack})
	static const char* file_scope = "file@";
	static unsigned int file_scope_len = 0;
	if( file_scope_len == 0)
		file_scope_len = strlen( file_scope);
	static const char* class_scope = "class@";
	static unsigned int class_scope_len = 0;
	if( class_scope_len == 0)
		class_scope_len = strlen( class_scope);
	static const char* stack_scope = "stack@";
	static unsigned int stack_scope_len = 0;
	if( stack_scope_len == 0)
		stack_scope_len = strlen( stack_scope);
	if( strncmp( arg_beg, file_scope, file_scope_len) == 0)
	{
		scope = D_Support_c::D_FILE_SCOPE;
		arg_beg += file_scope_len;
	}
	else if( strncmp( arg_beg, class_scope, class_scope_len) == 0)
	{
		scope = D_Support_c::D_CLASS_SCOPE;
		arg_beg += class_scope_len;
	}
	else if( strncmp( arg_beg, stack_scope, stack_scope_len) == 0)
	{
		scope = D_Support_c::D_STACK_SCOPE;
		arg_beg += stack_scope_len;
	}
	else 
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: illegal format of"
				"the " << kw << " directive: [" <<
				arg_beg << "] - scope must be "
				"{file|class|stack}\n" << flush;
		return( 0);
	}

	// now arg_beg ponts to "[area]@[level]@val"
	new_param = new char[ strlen( arg_beg) + 1];
	if( new_param == 0)
	{
		// no exceptions, etc. - we are in the debug lib!
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: operator new "
				"failed\n" << flush;
		return( 0);
	}
	strcpy( new_param, arg_beg);

	// new_param is "[area]@[level]@val"

	char* s = strchr( new_param, '@');
	if( s == 0)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: illegal format of "
				"the " << kw << " directive: [" <<
				arg_beg << "]\n" << flush;
		delete[] new_param;
		return( 0);
	}

	static const char* default_area = ".*";
	char* s1 = strchr( s + 1, '@');
	char* level;
	*s = '\0';
	if( s1 == 0)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: illegal format of "
				"the " << kw << " directive: [" <<
				arg_beg << "]\n" << flush;
		delete[] new_param;
		return( 0);
	}
	else if( s == new_param)	// format "@level@val"
	{
		area = (char*)default_area;
		level = s + 1;
		*s1 = '\0';
		val = s1 + 1;
	}
	else				// format "area@level@val"
	{
		area = new_param;
		level = s + 1;
		*s1 = '\0';
		val = s1 + 1;
	}

	if( strlen( level) == 0)	// format "area@@val"
		lvl1 = lvl2 = -1;
	else if( strcmp( level, "all") == 0)
		lvl1 = lvl2 = -1;
	else
	{
		s = strchr( level + 1, '-');
		if( s == 0)
		{
			lvl1 = lvl2 =
				get_level_value( level, kw, arg_beg);
			if( lvl1 == INT_MIN)
			{
				delete[] new_param;
				return( 0);
			}
		}
		else
		{
			lvl1 = get_level_value( level, kw, arg_beg);
			if( lvl1 == INT_MIN)
			{
				delete[] new_param;
				return( 0);
			}
			lvl2 = get_level_value( s + 1, kw, arg_beg);
			if( lvl2 == INT_MIN)
			{
				delete[] new_param;
				return( 0);
			}
		}
	}
	return( 1);
}

static int set_do_something_for( ForPrintOrSelfTest which,
		const char* param,
		const char* kw, unsigned int kw_len,
		int weight)
{
	D_Support_c::Scope scope;
	char* arg_beg;
	char* new_param;
	char* area;
	int lvl1, lvl2;
	char* val;

	if( get_param_elements( param, kw, kw_len,
			scope, arg_beg, new_param, area,
			lvl1, lvl2, val) == 0)
		return( 0);

	int flag;
	if( strcmp( val, "on") == 0 ||
	    strcmp( val, "yes") == 0 ||
	    strcmp( val, "1") == 0)
		flag = 1;
	else if( strcmp( val, "off") == 0 ||
	    strcmp( val, "no") == 0 ||
	    strcmp( val, "0") == 0)
		flag = 0;
	else
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: illegal format of "
				"the " << kw << " directive: [" <<
				arg_beg << "] (flag [" << val <<
				"])\n" << flush;
		delete[] new_param;
		return( 0);
	}

	for( int lvl = lvl1; lvl <= lvl2; lvl ++)
	{
		int r = set_do_something_for( which,
				area, scope, weight, lvl, flag);
		if( r == 0)
		{
			if( !to_work_silently())
				*get_d_stream() << "TRiASDMP: illegal "
					"format of the " << kw <<
					" directive: [" << arg_beg <<
					"] (illegal regular "
					"expression)\n" << flush;
			delete[] new_param;
			return( 0);
		}
	}
	delete[] new_param;
	return( 1);
}

static inline int set_prefix( const char* param,
		const char* kw, unsigned int kw_len, int weight)
{
	D_Support_c::Scope scope;
	char* arg_beg;
	char* new_param;
	char* area;
	int lvl1, lvl2;
	char* val;

	if( get_param_elements( param, kw, kw_len,
			scope, arg_beg, new_param, area,
			lvl1, lvl2, val) == 0)
		return( 0);

	for( int lvl = lvl1; lvl <= lvl2; lvl ++)
	{
		int r = D_Support_c::SetPrefix(
				area, scope, lvl, val, weight);
		if( r == 0)
		{
			if( !to_work_silently())
				*get_d_stream() << "TRiASDMP: illegal "
					"format of the " << kw <<
					" directive: [" << arg_beg <<
					"] (illegal regular "
					"expression)\n" << flush;
			delete[] new_param;
			return( 0);
		}
	}
	delete[] new_param;
	return( 1);
}

static int extract_positive_number( const char* what, const char* param,
		const char* kw, unsigned int kw_len)
{
	if( strncmp( param, kw, kw_len) != 0)
		return( -1);

	const char* num = param + kw_len;
	int val = atoi( num);
	if( val < 0 ||
	  ( val == 0 && *num != '0'))
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: trial to " <<
				what << " to illegal value [" <<
				num << "]\n" << flush;
		return( -1);
	}
	return( val);
}

#endif						/* } USE_DLIB */

int D_Support_c::DoPrintFor( const char* file,
		const char* class_name, unsigned int level)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	int flag = do_something_for( FOR_PRINT,
			file, class_name, level);
	leave_critical_section();
	return( flag);
#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::DoSelfTestFor( const char* file,
		const char* class_name, int level)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	D_UpdateMaskInfos();
	int flag = do_something_for( FOR_SELFTEST,
			file, class_name, level);
	leave_critical_section();
	return( flag);
#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::SetDoPrintFor( Scope scope,
		const char* mask, int level, int flag)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	man_weight ++ ;
	int res = set_do_something_for( FOR_PRINT,
			mask, scope, man_weight, level, flag);
	leave_critical_section();
	return( res);
#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::SetDoSelfTestFor( const char* mask,
		D_Support_c::Scope scope, int level, int flag)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	man_weight ++ ;
	int res = set_do_something_for( FOR_SELFTEST,
			mask, scope, man_weight, level, flag);
	leave_critical_section();
	return( res);
#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::SetDoPrintFor( const char* param, int weight)
{
#ifdef USE_DLIB					/* { */

// The param must have format:
// "print@{file|class|stack}@[area]@[level]@{on|off|yes|no|0|1}"

	enter_critical_section();
	static unsigned int print_kw_len = 0;
	if( print_kw_len == 0)
		print_kw_len = strlen( print_kw);
	int res = set_do_something_for( FOR_PRINT,
			param, print_kw, print_kw_len, weight);
	leave_critical_section();
	return( res);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::SetDoSelfTestFor( const char* param, int weight)
{
#ifdef USE_DLIB					/* { */

// The param must have format:
// "selftest@{file|class|stack}@[area]@[level]@{on|off|yes|no|0|1}"

	enter_critical_section();
	static unsigned int selftest_kw_len = 0;
	if( selftest_kw_len == 0)
		selftest_kw_len = strlen( selftest_kw);
	int res = set_do_something_for( FOR_SELFTEST,
			param, selftest_kw, selftest_kw_len, weight);
	leave_critical_section();
	return( res);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

void D_Support_c::SetFileNameStrip( unsigned int new_lvl)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	if( !to_work_silently())
		*get_d_stream() << "TRiASDMP: file name strip level " <<
			"changed to " << new_lvl << "\n" << flush;
	d_fname_stripping_level = new_lvl;
	leave_critical_section();
#endif						/* } USE_DLIB */
}

int D_Support_c::SetFileNameStrip( const char* param)
{
#ifdef USE_DLIB					/* { */

// The param must have format
//	"fstrip@#" (# must be positive)

	enter_critical_section();
	static unsigned int fstrip_kw_len = 0;
	if( fstrip_kw_len == 0)
		fstrip_kw_len = strlen( fstrip_kw);

	int new_lvl = extract_positive_number(
			"change file name stripping level",
			param, fstrip_kw, fstrip_kw_len);
	if( new_lvl == -1)
	{
		leave_critical_section();
		return( 0);
	}
	SetFileNameStrip( (unsigned int)new_lvl);
	leave_critical_section();
	return( 1);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

void D_Support_c::SetRefreshInterval( const time_t interval)
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	if( !to_work_silently())
		*get_d_stream() << "TRiASDMP: refresh interval " <<
			"changed to " << interval << "\n" << flush;
	refresh_interval = interval;
	leave_critical_section();
#endif						/* } USE_DLIB */
}

int D_Support_c::SetRefreshInterval( const char* param)
{
#ifdef USE_DLIB					/* { */

// The param must have format
//	"refresh@#" (# must be positive)

	enter_critical_section();
	static unsigned int refresh_kw_len = 0;
	if( refresh_kw_len == 0)
		refresh_kw_len = strlen( refresh_kw);

	int new_int = extract_positive_number(
			"change refresh interval",
			param, refresh_kw, refresh_kw_len);
	if( new_int == -1)
	{
		leave_critical_section();
		return( 0);
	}
	SetRefreshInterval( (unsigned int)new_int);
	leave_critical_section();
	return( 1);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

#ifdef USE_DLIB					/* { */

inline static const char* get_pid_as_string()
{
	static char res[32];
	sprintf( res, "%d", (int)getpid());
	return( res);
}

inline static const char* get_tid_as_string()
{
	static char res[32];
	long tid = get_current_thread_id();
	if( tid == -1)
		strcpy( res, "<no thread>");
	else
		sprintf( res, "%d", tid);
	return( res);
}

static const char* get_fname_as_string( const char* fname)
{

// Suppose the fname is d:/dir1/dir2/dir3/dir4/file.ext.
// 1. If d_fname_stripping_level == 0 then
//    everything is returned as is, i.e.
//	d:/dir1/dir2/dir3/dir4/file.ext
// 2. If d_fname_stripping_level == 1 then
//    file name (w/o path) is returned, i.e.
//	file.ext
// 3. If d_fname_stripping_level > 1 then
//    the file name is truncated up the last d_fname_stripping_level
//    parts, i.e. if d_fname_stripping_level==3 (default value) then
//    we'll return
// 	.../dir3/dir4/file.ext
//

	static char res[ D_FNAME_MAX + 1];

	// firstly all '\\' -> '/'
	strcpy( res, fname);
	int i = 0;
	for( ; res[i] != '\0'; i ++)
		if( res[i] == '\\')
			res[i] = '/';

	if( d_fname_stripping_level == 0)
		return( res);

	// instead of strlen
	int len = i;

	unsigned int slashes = 0;
	for( i = len - 1; i >= 0; i --)
		if( res[i] == '/')
		{
			slashes ++ ;
			if( slashes == d_fname_stripping_level)
				break;
		}

	if( slashes < d_fname_stripping_level)
		return( res);

	int beg = 0;
	if( d_fname_stripping_level > 1)
	{
		// substitution line is "...", so if there is less then
		// 3 characters left then - nothing to do
		if( i <= 3)
			return( res);

		// well, now the res[i] is the first slash we want
		res[0] = '.';
		res[1] = '.';
		res[2] = '.';
		res[3] = '/';

		beg += 4;
	}
	i ++;	// 1st char after the '/'
	////for( int j = beg; res[i] != '\0'; j ++. i ++) !!! MS!!!
	int j = beg;
	for( ; res[i] != '\0'; j ++, i ++)
		res[j] = res[i];
	res[j] = '\0';
	return( res);
}

inline static const char* get_fline_as_string( unsigned long line)
{
	static char res[32];
	sprintf( res, "%d", line);
	return( res);
}

inline static const char* get_class_as_string( const char* cname)
{
	static const char* no_cname = "<no class name>";
	if( cname != 0)
		return( cname);
	else
		return( no_cname);
}

inline static const char* get_level_as_string( int level)
{
	static char res[32];
	if( level == -1)
		strcpy( res, "<no level>");
	else
		sprintf( res, "%d", level);
	return( res);
}

inline static const char* get_millisecs_as_string( D_Time_c* time)
{
	static char res[32];
	sprintf( res, "%03d", time->GetUsec());
	return( res);
}

inline static const char* get_secs_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%02d", time->tm_sec);
	return( res);
}

inline static const char* get_mins_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%02d", time->tm_min);
	return( res);
}

inline static const char* get_hour_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%02d", time->tm_hour);
	return( res);
}

inline static const char* get_day_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%02d", time->tm_mday);
	return( res);
}

inline static const char* get_month_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%02d", time->tm_mon + 1); // +1 - see localtime()
						 // manual pages
	return( res);
}

inline static const char* get_year_as_string( struct tm* time)
{
	static char res[32];
	sprintf( res, "%04d", time->tm_year + 1900);	// this field
					// contains "year since 1900"
	return( res);
}

//static void to_stop_here()
//{
//	static here = 0;
//	here ++ ;
//}

inline static void replace_string_element( D_String_c* format,
		const char* kw,
		const char* str)
{
	//to_stop_here();	// for internal debug
	size_t where = format->index( kw);
	if( where == NO_SUCH_ELEMENT)
		return;
	unsigned int len = strlen( kw);
	format->replace( where, len, str);
}

#endif						/* } USE_DLIB */

const char* D_Support_c::Prefix( const char* fname,
			unsigned long line,
			const char* class_name,
			int level)
// "class_name" == 0 for calls from outside of a class's methods
// "level" for not leveled macros == -1 (i.e. all - see the header),
// therefore at least default prefix (set for ".*" and -1) must fit it.
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();

	//if( class_name)
	//	D_P2( fname, class_name)
	//else
	//	D_P( fname);

	D_Time_c cur_time;
	time_t aclock = (time_t)cur_time.GetSec();
	struct tm* tm_time = localtime( &aclock);

	const char* pid_str = get_pid_as_string();
	const char* tid_str = get_tid_as_string();
	const char* year_str = get_year_as_string( tm_time);
	const char* month_str = get_month_as_string( tm_time);
	const char* day_str = get_day_as_string( tm_time);
	const char* hour_str = get_hour_as_string( tm_time);
	const char* min_str = get_mins_as_string( tm_time);
	const char* sec_str = get_secs_as_string( tm_time);
	const char* msec_str = get_millisecs_as_string( &cur_time);
	const char* file_str = get_fname_as_string( fname);
	const char* line_str = get_fline_as_string( line);
	const char* class_str = get_class_as_string( class_name);
	const char* level_str = get_level_as_string( level);

	int found = 0;
	char* format = (char*)get_info_from_info_collections(
			get_mask_infos_string(),
			fname, class_name, (unsigned int)level, &found);

	if( !found)
	{
		if( !to_work_silently())
		{
			*get_d_stream() << "TRiASDMP: could not find " <<
				"format for: file [" << fname << "]" <<
				flush;
			if( class_name)
				*get_d_stream() << ", class [" <<
					class_name << "]" << flush;
			*get_d_stream() << ", level [" << level <<
				"] - assumed default format\n" << flush;
		}
		format = (char*)default_prefix_format;
	}

	static D_String_c* prefix = 0;
	// Yes, this is a memory leak... But so it works for statics!
	if( prefix == 0)
		prefix = new D_String_c;
	*prefix = format;

	replace_string_element( prefix, pid_kw, pid_str);
	replace_string_element( prefix, tid_kw, tid_str);
	replace_string_element( prefix, year_kw, year_str);
	replace_string_element( prefix, month_kw, month_str);
	replace_string_element( prefix, day_kw, day_str);
	replace_string_element( prefix, hour_kw, hour_str);
	replace_string_element( prefix, min_kw, min_str);
	replace_string_element( prefix, sec_kw, sec_str);
	replace_string_element( prefix, msec_kw, msec_str);
	replace_string_element( prefix, file_kw, file_str);
	replace_string_element( prefix, line_kw, line_str);
	replace_string_element( prefix, class_kw, class_str);
	replace_string_element( prefix, level_kw, level_str);
	// if prefix has the last char != space, then to add it
	size_t l = prefix->length();
	if( l > 0)
		if( (*prefix)[ l - 1] != ' ')
			(*prefix) += " ";

	const char* ret = prefix->data();
	leave_critical_section();
	return( ret);

#else						/* }{ USE_DLIB */

	static char res[ D_FNAME_MAX + 32];	// enough for line no?
	sprintf( res, "%s(%d):", fname, line);
	return( res);

#endif						/* } USE_DLIB */
}

int D_Support_c::SetPrefix( const char* mask,
		D_Support_c::Scope scope,
		int level,
		const char* format,
		int weight)
{
#ifdef USE_DLIB					/* { */

	enter_critical_section();
	const char* msk = 0;
	if( weight == INT_MIN)
	{
		man_weight ++ ;
		weight = man_weight;
	}
	if( scope == D_Support_c::D_FILE_SCOPE)
		msk = canonize_fname( mask);
	else
		msk = mask;
	size_t index = get_mask_infos_string()->index(
				find_mask_info, (void*)msk);
	if( index == NO_SUCH_ELEMENT)
	{
		D_MaskInfo_c* mi = new D_MaskInfo_c( msk, scope, weight,
				level, (char*)format);
		if( mi->GetRegExpStatus() != D_RegExp_c::OK)
		{
			delete mi;
			leave_critical_section();
			return( 0);
		}
		get_mask_infos_string()->insert( mi);
		print_about_change_prefix( scope, msk, level, format);
		leave_critical_section();
		return( 1);
	}
	D_MaskInfo_c* minfo =
		(D_MaskInfo_c*)get_mask_infos_string()->at( index);
	minfo->SetLevelInfo( scope, weight, level, (char*)format);
	print_about_change_prefix( scope, msk, level, format);
	leave_critical_section();
	return( 1);
#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

int D_Support_c::SetPrefix( const char* param, int weight)
{
#ifdef USE_DLIB					/* { */

// The param must have format "prefix@scope@[area]@[level]@format"

	enter_critical_section();
	static unsigned int prefix_kw_len = 0;
	if( prefix_kw_len == 0)
		prefix_kw_len = strlen( prefix_kw);
	int res = set_prefix( param, prefix_kw, prefix_kw_len, weight);
	leave_critical_section();
	return( res);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

ostream& D_Support_c::D_Stream()
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	ostream* ret = get_d_stream();
	leave_critical_section();
	return( *ret);
#else						/* }{ USE_DLIB */
	return( cerr);
#endif						/* } USE_DLIB */
}


#ifdef USE_DLIB					/* { */

static inline ostream& operator <<( ostream& s, D_Support_c::Scope sc)
{
	switch( sc)
	{
		case D_Support_c::D_FILE_SCOPE:
			s << "file@";
			break;
		case D_Support_c::D_CLASS_SCOPE:
			s << "class@";
			break;
		case D_Support_c::D_STACK_SCOPE:
			s << "stack@";
			break;
		default:
			s << "<unknown scope>@";
			break;
	}
	return( s);
}

static void dump_for( ForPrintOrSelfTest which, const char* kw,
		ostream& str)
{
	size_t m_entries = get_mask_infos_long( which)->entries();
	for( size_t i = 0; i < m_entries; i ++)
	{
		D_MaskInfo_c* mi = (D_MaskInfo_c*)get_mask_infos_long(
						    which)->at( i);
		D_VoidList_c& levels = mi->GetLevelInfos();
		static const int all_lvl = -1;
		size_t l_entries = levels.entries();
		for( size_t j = 0; j < l_entries; j ++)
		{
			D_LevelNumberInfo_c* li = (D_LevelNumberInfo_c*)
							levels.at( j);
			str << kw << flush;
			str << li->_scope << flush;
			str << mi->GetMaskStr() << "@" << flush;
			if( li->_no == all_lvl)
				str << "all" << flush;
			else
				str << li->_no << flush;
			str << "@" << li->GetInfo() << "\n" << flush;
		}
	}
}

static void dump_mask_infos( const char* kw, ostream& str)
{
	size_t m_entries = get_mask_infos_string()->entries();
	for( size_t i = 0; i < m_entries; i ++)
	{
		D_MaskInfo_c* mi =
			(D_MaskInfo_c*)get_mask_infos_string()->at( i);
		D_VoidList_c& levels = mi->GetLevelInfos();
		static const int all_lvl = -1;
		size_t l_entries = levels.entries();
		for( size_t j = 0; j < l_entries; j ++)
		{
			D_LevelStringInfo_c* li =
				(D_LevelStringInfo_c*)levels.at( j);
			str << kw << flush;
			str << li->_scope << flush;
			str << mi->GetMaskStr() << "@" << flush;
			if( li->_no == all_lvl)
				str << "all" << flush;
			else
				str << li->_no << flush;
			str << "@" << li->GetInfo() << "\n" << flush;
		}
	}
}

#endif						/* } USE_DLIB */

void D_Support_c::Dump( ostream& str)
{
#ifdef USE_DLIB					/* { */
	str << "# --- Dump of TRiASDMP settings ---\n" << flush;
	str << refresh_kw << refresh_interval << "\n" << flush;
	str << fstrip_kw << d_fname_stripping_level << "\n" << flush;
	if( was_ofstream)
		str << filename_kw << *d_fname << "\n" << flush;
	else
	{
		if( *get_d_stream() == *get_cerr())
			str << stdstream_kw << "err\n" << flush;
		else if( *get_d_stream() == *get_cout())
			str << stdstream_kw << "out\n" << flush;
#if defined(_WIN32)
// #HK990305: BEGIN
		else if( *get_d_stream() == *get_cdbg())
			str << stdstream_kw << "dbg\n" << flush;
// #HK990305: END
#endif // defined(WIN32)
		else
			str << "#" << stdstream_kw << "<unknown>\n" <<
				flush;
	}
	dump_for( FOR_PRINT, print_kw, str);
	dump_for( FOR_SELFTEST, selftest_kw, str);
	dump_mask_infos( prefix_kw, str);
	str << "# --- End of dump ---\n" << flush;
#endif						/* } USE_DLIB */
}

int D_Support_c::Dump( const char* param)
{
#ifdef USE_DLIB					/* { */

// The param must have format
//	"dump"

	enter_critical_section();
	static unsigned int dump_kw_len = 0;
	if( dump_kw_len == 0)
		dump_kw_len = strlen( dump_kw);

	if( strcmp( param, dump_kw) != 0)
	{
		leave_critical_section();
		return( 0);
	}
	Dump();
	leave_critical_section();
	return( 1);

#else						/* }{ USE_DLIB */
	return( 1);
#endif						/* } USE_DLIB */
}

#ifdef USE_DLIB					/* { */

static void close_ofstream()
{
	if( was_ofstream)
		d_ofstream->close();
	was_ofstream = 0;
}

static void set_d_stream_for( ostream& str, char* name)
{
	if( *get_d_stream() == str)	// already was
		return;
	if( !to_work_silently())
		*get_d_stream() << "TRiASDMP: output is switched to std" <<
			name << "\n" << flush;
	close_ofstream();
	d_stream = &str;
}

static int set_d_stream( const char* stream)
{
	if( strcmp( stream, "out") == 0)
	{
		set_d_stream_for( *get_cout(), "out");
		return( 1);
	}
	if( strcmp( stream, "err") == 0)
	{
		set_d_stream_for( *get_cerr(), "err");
		return( 1);
	}
#if defined(_WIN32)
// #HK990305
	if( strcmp( stream, "dbg") == 0)
	{
		set_d_stream_for( *get_cdbg(), "dbg");
		return( 1);
	}
// #HK990305
#endif // defined(WIN32)

	if( !to_work_silently())
		*get_d_stream() << "TRiASDMP: trial to switch output "
			"to illegal stream [" << stream << "]\n" <<
			flush;
	return( 0);
}

static int set_d_file( const char* fn, int reporting, int new_file)
{
	static D_String_c* fname = 0;
	// Yes, this is a memory leak... But so it works for statics!
	if( fname == 0)
		fname = new D_String_c;
	*fname = fn;

	D_Time_c cur_time;
	time_t aclock = (time_t)cur_time.GetSec();
	struct tm* tm_time = localtime( &aclock);

	const char* pid_str = get_pid_as_string();
	const char* year_str = get_year_as_string( tm_time);
	const char* month_str = get_month_as_string( tm_time);
	const char* day_str = get_day_as_string( tm_time);
	const char* hour_str = get_hour_as_string( tm_time);
	const char* min_str = get_mins_as_string( tm_time);
	const char* sec_str = get_secs_as_string( tm_time);

	replace_string_element( fname, pid_kw, pid_str);
	replace_string_element( fname, year_kw, year_str);
	replace_string_element( fname, month_kw, month_str);
	replace_string_element( fname, day_kw, day_str);
	replace_string_element( fname, hour_kw, hour_str);
	replace_string_element( fname, min_kw, min_str);
	replace_string_element( fname, sec_kw, sec_str);
	const char* fn_to_open = fname->data();

	if( new_file)
		unlink( fn_to_open);

	// Shit! The MSVC4.0's ofstream contains not working funcs:
	// setbuf(), is_open(), more?
	// So, we have to use the good old open() C func :-(
	//	int fd = _open( fn_to_open, _O_WRONLY | _O_CREAT,
	//				_S_IREAD | _S_IWRITE);
	//	if( fd == -1)
	//	{
	//		if( !to_work_silently())
	//			*get_d_stream() << "D_Lib: trial to "
	//				"switch output to illegal "
	//				"file [" << fname << "]\n" <<
	//				flush;
	//		return( 0);
	//	}
	//
	// ... [time passes...]
	//
	// Alas! in MSVC4.2 any form of attachment of file descriptor
	// to ofstream does not work! But now we have open()/close()
	// working, so let's use them.

	if( reporting)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: output is switched "
				"to file " << fn_to_open << "\n" <<
				flush;
	}
	close_ofstream();
	// Yes, this is a memory leak... But so it works for statics!
	if( d_ofstream == 0)
		d_ofstream = new ofstream;
	d_ofstream->open( fn_to_open, ios::app | ios::in);
	d_stream = d_ofstream;
	was_ofstream = 1;
	if( reporting)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: output is switched "
				"to file " << fn_to_open << "\n" <<
				flush;
	}
	// this is how to obtain file descriptor:
	// int fd = d_ofstream->rdbuf()->fd();
	// it may be useful if there will be a problem with
	// syncronizing of output from different processes
	if( d_fname == 0)
		d_fname = new D_String_c;
	*d_fname = fn_to_open;
	return( 1);
}

#endif						/* } USE_DLIB */

int D_Support_c::SetD_Stream( const char* param)
{
#ifdef USE_DLIB					/* { */

// The param must begin from "to_stream@" or "to_file@", otherwise
// the param will be ignored silently (this is useful for parsing
// of a control line - if it is in known format then it is used
// and the 1 is returned, else it is ignored and the 0 is returned).

	enter_critical_section();
	static unsigned int stdstream_kw_len = 0;
	if( stdstream_kw_len == 0)
		stdstream_kw_len = strlen( stdstream_kw);
	static unsigned int filename_kw_len = 0;
	if( filename_kw_len == 0)
		filename_kw_len = strlen( filename_kw);
	static unsigned int newfilename_kw_len = 0;
	if( newfilename_kw_len == 0)
		newfilename_kw_len = strlen( newfilename_kw);

	int res;

	if( strncmp( param, stdstream_kw, stdstream_kw_len) == 0)
	{
		res = set_d_stream( param + stdstream_kw_len);
		leave_critical_section();
		return( res);
	}

	if( strncmp( param, filename_kw, filename_kw_len) == 0)
	{
		res = set_d_file( param + filename_kw_len, 1);
		leave_critical_section();
		return( res);
	}

	if( strncmp( param, newfilename_kw, newfilename_kw_len) == 0)
	{
		res = set_d_file( param + newfilename_kw_len, 1, 1); // last 1 - to new file
		leave_critical_section();
		return( res);
	}

	leave_critical_section();
	return( 0);

#else						/* }{ USE_DLIB */

	return( 1);

#endif						/* } USE_DLIB */
}

void D_Support_c::Enter()
{
#ifdef USE_DLIB					/* { */
	enter_critical_section();
	D_UpdateMaskInfos();
#endif						/* } USE_DLIB */
}

void D_Support_c::Leave()
{
#ifdef USE_DLIB					/* { */
	leave_critical_section();
#endif						/* } USE_DLIB */
}

#ifdef USE_DLIB					/* { */

static int find_stack_info( void* si, void* data)
{
	D_StackInfo_c* sinfo = (D_StackInfo_c*)si;
	const char* sname = (const char*)data;
	if( strcmp( sinfo->StackName(), sname) == 0)
		return( 1);
	return( 0);
}

#endif						/* } USE_DLIB */

D_StackName_c::D_StackName_c( const char* stack_name)
	: _stack_name( 0)
{
#ifdef USE_DLIB					/* { */
//	D_Support_c::Enter();
	// D_OUT(1) << "ctr for [" << _stack_name << "]\n" << D_END;
	_stack_name = stack_name;
	D_VoidList_c* stack_infos = get_d_lib_stack_infos();
	size_t index = stack_infos->index( find_stack_info,
			(void*)_stack_name);
	if( index == NO_SUCH_ELEMENT)
	{
		stack_infos->insert( new D_StackInfo_c( this));
	}
	else
	{
		D_StackInfo_c* sinfo =
			(D_StackInfo_c*)stack_infos->at( index);
		sinfo->IncCounter();
	}
//	D_Support_c::Leave();
#endif						/* } USE_DLIB */
}

D_StackName_c::~D_StackName_c()
{
#ifdef USE_DLIB					/* { */
//	D_Support_c::Enter();
	// D_OUT(1) << "dtr for [" << _stack_name << "]\n" << D_END;
	D_VoidList_c* stack_infos = get_d_lib_stack_infos();
	size_t index = stack_infos->index( find_stack_info,
			(void*)_stack_name);
	if( index == NO_SUCH_ELEMENT)
	{
		if( !to_work_silently())
			*get_d_stream() << "TRiASDMP: could not find " <<
				"stack information for leaving stack "
				"[" << _stack_name << "] - internal "
				"error\n" << flush;
//		D_Support_c::Leave();
		return;
	}
	D_StackInfo_c* sinfo = (D_StackInfo_c*)stack_infos->at( index);
	sinfo->DecCounter();
	if( index != 0)	// i.e. not the last element
	{
//		D_Support_c::Leave();
		return;
	}
	if( sinfo->Counter() > 0)	// i.e. not the last recursion
	{
//		D_Support_c::Leave();
		return;
	}
	// removing of top elements
	while( 1)
	{
		stack_infos->remove();
		// D_OUT(1) << "delete for [" << sinfo->StackName() <<
		// 	"]\n" << D_END;
		delete sinfo;
		if( stack_infos->entries() == 0)
			break;
		sinfo = (D_StackInfo_c*)stack_infos->at( 0);
		if( sinfo->Counter() > 0)
			break;
	}
//	D_Support_c::Leave();
#endif						/* } USE_DLIB */
}

#ifdef USE_DLIB					/* { */

// Functiond used from C sources

extern "C"
DLIB_EXPORTED
void D_C_Support_Enter()
{
	D_Support_c::Enter();
}

extern "C"
DLIB_EXPORTED
void D_C_Support_Leave()
{
	D_Support_c::Leave();
}

extern "C"
DLIB_EXPORTED
const char* D_C_Support_Prefix( const char* fname,
			unsigned long line,
			const char* class_name,
			int level)
{
	return( D_Support_c::Prefix( fname, line, class_name, level));
}

extern "C"
DLIB_EXPORTED
int D_C_Support_DoPrintFor( const char* file,
			const char* class_name,
			int level)
{
	return( D_Support_c::DoPrintFor( file, class_name, level));
}

extern "C"
DLIB_EXPORTED
int D_C_Support_DoSelfTestFor( const char* file,
			const char* class_name,
			int level)
{
	return( D_Support_c::DoSelfTestFor( file, class_name, level));
}

extern "C"
DLIB_EXPORTED
const char* D_C_Support_Sprintf( const char* fmt, ...)
{
	static char buf[4096];
	char* s;
	va_list args;
	va_start( args, fmt);
	vsprintf( buf, fmt, args);
	va_end( args);
	s = new char[ strlen( buf) + 1];
	strcpy( s, buf);
	return( s);
}

extern "C"
DLIB_EXPORTED
void D_C_Support_Fprintf( int stream_flag, int format_flag,
		const char* prefix,
		const char* exp1, const char* str1,
		const char* exp2, const char* str2,
		const char* exp3, const char* str3,
		const char* exp4, const char* str4,
		const char* exp5, const char* str5)
{
	ostream* stream;
	if( stream_flag)
		stream = get_d_stream();
	else
		stream = get_cerr();

	*stream << prefix << flush;
	if( format_flag)
		*stream << exp1 << " = [" << flush;
	*stream << str1 << flush;
	if( format_flag)
		*stream << "]" << flush;
	delete[] (char*)str1;
	if( exp2)
	{
		if( format_flag)
			*stream << ", " << exp2 << " = [" << flush;
		*stream << str2 << flush;
		if( format_flag)
			*stream << "]" << flush;
		delete[] (char*)str2;
	}
	if( exp3)
	{
		if( format_flag)
			*stream << ", " << exp3 << " = [" << flush;
		*stream << str3 << flush;
		if( format_flag)
			*stream << "]" << flush;
		delete[] (char*)str3;
	}
	if( exp4)
	{
		if( format_flag)
			*stream << ", " << exp4 << " = [" << flush;
		*stream << str4 << flush;
		if( format_flag)
			*stream << "]" << flush;
		delete[] (char*)str4;
	}
	if( exp5)
	{
		if( format_flag)
			*stream << ", " << exp5 << " = [" << flush;
		*stream << str5 << flush;
		if( format_flag)
			*stream << "]" << flush;
		delete[] (char*)str5;
	}
	*stream << "\n" << flush;
}

#endif						/* } USE_DLIB */


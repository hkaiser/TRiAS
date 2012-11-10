#if defined(__STL_OSPACE5__)
	#pragma warning (disable: 4304)
	#pragma warning (disable: 4114)
	#pragma warning (disable: 4786)
	#if defined(_DEBUG)
			#pragma comment( lib, "OSpace5D.lib" )
	#elif defined(_RDEBUG)
			#pragma comment( lib, "OSpace5R.lib" )
	#elif defined(NDEBUG)
			#pragma comment( lib, "OSpace5R.lib" )
	#endif
#elif defined(__STL_OSPACE4__)
	#pragma warning (disable: 4304)
	#pragma warning (disable: 4114)
	#pragma warning (disable: 4786)
	#if defined(_DEBUG)
			#pragma comment( lib, "OSpace2D.lib" )
	#elif defined(_RDEBUG)
			#pragma comment( lib, "OSpace2R.lib" )
	#elif defined(NDEBUG)
			#pragma comment( lib, "OSpace2R.lib" )
	#endif
#endif

#if defined(__STL_OSPACE5__) || defined(__STL_OSPACE4__)
	#define OS_ALTERNATIVE_STRING_NAMES
	#define OS_MULTI_THREADED
	#define OS_NO_STREAM_SUPPORT
	#define OS_NO_ALLOCATORS
	#define OS_WIN_95
	#define OS_STL_ASSERT
	#define OS_NO_WSTRING
	#define OS_NO_NAMESPACE

	#if defined(__STL_OSPACE4__)
		#define bool int
	#endif
	#include <ospace/stl/algo.h>
	#include <ospace/stl/map.h>
	#include <ospace/stl/vector.h>
	#include <ospace/stl/list.h>
	#include <ospace/stl/deque.h>
	#include <ospace/stl/set.h>
	#include <ospace/std/string>
	#if defined(__STL_OSPACE4__)
		#undef bool
	#endif

	namespace ospace { namespace std { namespace rel_ops {} } }
	using namespace ospace::std;
	using namespace ospace::std::rel_ops;

#elif defined(__STL_HP__)
	#define __PLACEMENT_NEW_INLINE
	#include <bool.h>
	#include <algo.h>
	#include <map.h>
	#include <vector.h>
	#include <list.h>
	#include <deque.h>
	#include <set.h>
#else
#error "keine STL-Bibliothek definiert"
#endif

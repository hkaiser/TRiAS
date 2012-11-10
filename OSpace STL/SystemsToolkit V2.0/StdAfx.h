// Precompiled Header for Ospace2.Dll
// File: StdAfx.h

#include <ospace/config.h>

#if !defined(OS_NO_NAMESPACE)
namespace ospace { namespace std {} }
using namespace ::ospace::std;
#elif defined(OS_OPS_NAMESPACE)
namespace ospace { namespace std { namespace rel_ops {} } }
using namespace ::ospace::std::rel_ops;
#endif // OS_NO_NAMESPACE



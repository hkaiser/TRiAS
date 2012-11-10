// Systems<ToolKit> DLL support
// Copyright (c) 1996 by ObjectSpace, Inc.  All rights reserved.
// Email: sales@objectspace.com, ccs.support@objectspace.com
// Last Modified: $Date: 1996/11/20 22:21:11 $

#include <ospace/std/iostream>
#include <windows.h>
#include <ospace/config.h>
#include <ospace/string/src/regex.h>

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_helper_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_helper_toolkit();

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_io_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_io_toolkit();

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_streaming_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_streaming_toolkit();

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_thread_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_thread_toolkit();

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_file_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_file_toolkit();

OS_VCC_PUBLIC void OS_BCC_PUBLIC os_init_time_toolkit();
OS_VCC_PUBLIC void OS_BCC_PUBLIC os_exit_time_toolkit();

BOOL WINAPI
#ifdef __BORLANDC__
  DllEntryPoint( HANDLE handle, ULONG reason, LPVOID reserved )
#else
  DllMain( HANDLE handle, ULONG reason, LPVOID reserved )
#endif
  {
  switch ( reason )
    {
    case DLL_PROCESS_ATTACH:
      os_init_thread_toolkit();
      os_init_helper_toolkit();
      os_init_io_toolkit();
      os_init_file_toolkit();
      os_init_streaming_toolkit();
	  os_init_time_toolkit();

	// default Regeln für RegExpr matching festlegen
	  re_set_syntax (RE_INTERVALS|RE_CHAR_CLASSES|RE_HAT_LISTS_NOT_NEWLINE);
      break;

    case DLL_PROCESS_DETACH:
	  os_exit_time_toolkit();
      os_exit_streaming_toolkit();
      os_exit_file_toolkit();
      os_exit_io_toolkit();
      os_exit_helper_toolkit();
      os_exit_thread_toolkit();
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;

    default:
//      cout << "unknown";
      break;
    }

  return TRUE;
  }

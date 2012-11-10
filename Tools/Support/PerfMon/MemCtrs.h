// $Header: $
// Copyright® 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 03:22:04 PM
//
// @doc
// @module MemCtrs.h | SharedMemory Messagestrings
//
#if !defined(_MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_
//
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
//
// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif
//
//
//     Perfutil messages
//
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: UTIL_LOG_OPEN
//
// MessageText:
//
//  An extensible counter has opened the Event Log for MEMCTRS.DLL
//
#define UTIL_LOG_OPEN                    ((DWORD)0x4000076CL)

//
//
// MessageId: UTIL_CLOSING_LOG
//
// MessageText:
//
//  An extensible counter has closed the Event Log for MEMCTRS.DLL
//
#define UTIL_CLOSING_LOG                 ((DWORD)0x400007CFL)

//
//
// MessageId: PERFMON_OPEN_FILE_MAPPING_ERROR
//
// MessageText:
//
//  Unable to open mapped file containing Application Memory performance data.
//
#define PERFMON_OPEN_FILE_MAPPING_ERROR  ((DWORD)0xC00007D0L)

//
//
// MessageId: PERFMON_UNABLE_MAP_VIEW_OF_FILE
//
// MessageText:
//
//  Unable to map to shared memory file containing Application Memory performance data.
//
#define PERFMON_UNABLE_MAP_VIEW_OF_FILE  ((DWORD)0xC00007D1L)

//
//
// MessageId: PERFMON_UNABLE_OPEN_DRIVER_KEY
//
// MessageText:
//
//  Unable open "Performance" key of Applicationa Memory Performace Driver in registy. Status code is returned in data.
//
#define PERFMON_UNABLE_OPEN_DRIVER_KEY   ((DWORD)0xC00007D2L)

//
//
// MessageId: PERFMON_UNABLE_READ_FIRST_COUNTER
//
// MessageText:
//
//  Unable to read the "First Counter" value under the AppMem\Performance Key. Status codes returned in data.
//
#define PERFMON_UNABLE_READ_FIRST_COUNTER ((DWORD)0xC00007D3L)

//
//
// MessageId: PERFMON_UNABLE_READ_FIRST_HELP
//
// MessageText:
//
//  Unable to read the "First Help" value under the AppMem\Performance Key. Status codes returned in data.
//
#define PERFMON_UNABLE_READ_FIRST_HELP   ((DWORD)0xC00007D4L)

//
//
// MessageId: PERFMON_WRONG_STARTMODE
//
// MessageText:
//
//  Die Routine IPerfContext::Start wurde mit einem für diesen Kontext falschen Wert als STARTMODE gerufen.
//
#define PERFMON_WRONG_STARTMODE          ((DWORD)0xC00007D5L)

//
#endif // !defined(_MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_)

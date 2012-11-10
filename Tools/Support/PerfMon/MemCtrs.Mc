;// $Header: $
;// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
;// Created: 12/26/1998 03:22:04 PM
;//
;// @doc
;// @module MemCtrs.h | SharedMemory Messagestrings
;//
;#if !defined(_MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_)
;#define _MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_
;//
;#if _MSC_VER >= 1000
;#pragma once
;#endif // _MSC_VER >= 1000
;//
;// Header include diagnostics
;#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
;#pragma message(__TIME__": include " __FILE__ )
;#endif
;//

LanguageNames = (
	German=0x407:MSG00407
	English=0x409:MSG00409
)

MessageIdTypedef=DWORD

;//
;//     Perfutil messages
;//
MessageId=1900
Severity=Informational
Facility=Application
SymbolicName=UTIL_LOG_OPEN
Language=German
An extensible counter has opened the Event Log for MEMCTRS.DLL
.
Language=English
An extensible counter has opened the Event Log for MEMCTRS.DLL
.
;//
MessageId=1999
Severity=Informational
Facility=Application
SymbolicName=UTIL_CLOSING_LOG
Language=German
An extensible counter has closed the Event Log for MEMCTRS.DLL
.
Language=English
An extensible counter has closed the Event Log for MEMCTRS.DLL
.
;//
MessageId=2000
Severity=Error
Facility=Application
SymbolicName=PERFMON_OPEN_FILE_MAPPING_ERROR
Language=German
Unable to open mapped file containing Application Memory performance data.
.
Language=English
Unable to open mapped file containing Application Memory performance data.
.
;//
MessageId=+1
Severity=Error
Facility=Application
SymbolicName=PERFMON_UNABLE_MAP_VIEW_OF_FILE
Language=German
Unable to map to shared memory file containing Application Memory performance data.
.
Language=English
Unable to map to shared memory file containing Application Memory performance data.
.
;//
MessageId=+1
Severity=Error
Facility=Application
SymbolicName=PERFMON_UNABLE_OPEN_DRIVER_KEY
Language=German
Unable open "Performance" key of Applicationa Memory Performace Driver in registy. Status code is returned in data.
.
Language=English
Unable open "Performance" key of Applicationa Memory Performace Driver in registy. Status code is returned in data.
.
;//
MessageId=+1
Severity=Error
Facility=Application
SymbolicName=PERFMON_UNABLE_READ_FIRST_COUNTER
Language=German
Unable to read the "First Counter" value under the AppMem\Performance Key. Status codes returned in data.
.
Language=English
Unable to read the "First Counter" value under the AppMem\Performance Key. Status codes returned in data.
.
;//
MessageId=+1
Severity=Error
Facility=Application
SymbolicName=PERFMON_UNABLE_READ_FIRST_HELP
Language=German
Unable to read the "First Help" value under the AppMem\Performance Key. Status codes returned in data.
.
Language=English
Unable to read the "First Help" value under the AppMem\Performance Key. Status codes returned in data.
.
;//
MessageId=+1
Severity=Error
Facility=Application
SymbolicName=PERFMON_WRONG_STARTMODE
Language=German
Die Routine IPerfContext::Start wurde mit einem für diesen Kontext falschen Wert als STARTMODE gerufen.
.
Language=English
The IPerfContext::Start - method was called with the wrong STARTMODE-context.
.
;//
;#endif // !defined(_MEMCTRS_H__4674526C_9CBA_11D2_9F09_006008447800__INCLUDED_)

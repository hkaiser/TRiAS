// PE_Debug.CPP

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#include "StdAfx.h"

#include "PE_Debug.h"
#include "DumpBuffer.h"



// Add an offset to a pointer and cast to a given type; may be
// implemented as a template function but Visual C++ has some problems.
#define BasedPtr( type, ptr, ofs ) (type)( (DWORD)(ptr) + (DWORD)(ofs) )


PE_Debug :: PE_Debug()
  {
  // Init file mapping cache
  hFileMapping = 0 ;
  hFile = INVALID_HANDLE_VALUE ;
  fileBase = 0 ;
  ClearDebugPtrs() ;
  ClearReport() ;
  }


PE_Debug :: ~PE_Debug()
  {
  ClearFileCache() ;
  }


void PE_Debug :: ClearReport()
  {
  latestModule[ 0 ] = 0 ;
  latestFile[ 0 ] = 0 ;
  }


void PE_Debug :: ClearDebugPtrs()
  {
  NT_Header = NULL ;
  COFFDebugInfo = NULL ;
  COFFSymbolTable = NULL ;
  COFFSymbolCount = 0 ;
  stringTable = NULL ;
  }


void PE_Debug :: ClearFileCache()
  {
  if( fileBase )
    {
    UnmapViewOfFile( fileBase ) ;
    fileBase = 0 ;
    }
  if( hFileMapping != 0 )
    {
    CloseHandle( hFileMapping ) ;
    hFileMapping = 0 ;
    }
  if( hFile != INVALID_HANDLE_VALUE )
    {
    CloseHandle( hFile ) ;
    hFile = INVALID_HANDLE_VALUE ;
    }
  }


void PE_Debug :: DumpLineNumber( DumpBuffer& dumpBuffer, DWORD relativeAddress )
  {
  PIMAGE_LINENUMBER line = BasedPtr( PIMAGE_LINENUMBER, COFFDebugInfo,
                                     COFFDebugInfo->LvaToFirstLinenumber ) ;
  DWORD lineCount = COFFDebugInfo->NumberOfLinenumbers ;
  const DWORD none = (DWORD)-1 ;
  DWORD maxAddr = 0 ;
  DWORD lineNum = none ;
  for( DWORD i=0; i < lineCount; i++ )
    {
    if( line->Linenumber != 0 )  // A regular line number
      {
      // look for line with bigger address <= relativeAddress
      if( line->Type.VirtualAddress <= relativeAddress &&
          line->Type.VirtualAddress > maxAddr )
        {
        maxAddr = line->Type.VirtualAddress ;
        lineNum = line->Linenumber ;
        }
      }
    line++ ;
    }
  if( lineNum != none )
    dumpBuffer.Printf( "  line: %d\r\n", lineNum ) ;
  else
    dumpBuffer.Printf( "  line: <unknown>\r\n" ) ;
  }


const char* PE_Debug :: GetSymbolName( PIMAGE_SYMBOL sym )
  {
  const int NAME_MAX_LEN = 64 ;
  static char buf[ NAME_MAX_LEN ] ;
  if( sym->N.Name.Short != 0 )
    {
    strncpy( buf, (const char*)sym->N.ShortName, 8 ) ;
    buf[ 8 ] = 0 ;
    }
  else
    {
    strncpy( buf, stringTable + sym->N.Name.Long, NAME_MAX_LEN ) ;
    buf[ NAME_MAX_LEN - 1 ] = 0 ;
    }
  return( buf ) ;
  }

#if defined(_USE_BSCKIT)

#include "hungary.h"		// ??
#include "bscapi.h"

LPCSTR demangle (LPCSTR pcModule, LPCSTR pcFunction)
{
Bsc *pBsc = NULL;

	if (Bsc::open (pcModule, &pBsc))
		return pBsc -> formatDname (pcFunction);
	else
		return pcFunction;
}
#endif // _USE_BSCKIT

void PE_Debug :: DumpSymbolInfo( DumpBuffer& dumpBuffer, DWORD relativeAddress, LPCSTR pcModule )
  {
  // Variables to keep track of function symbols
  PIMAGE_SYMBOL currentSym = COFFSymbolTable ;
  PIMAGE_SYMBOL fnSymbol = NULL ;
  DWORD maxFnAddress = 0 ;
  // Variables to keep track of file symbols
  PIMAGE_SYMBOL fileSymbol = NULL ;
  PIMAGE_SYMBOL latestFileSymbol = NULL ;
  for( int i = 0; i < COFFSymbolCount; i++ )
    {
    // Look for .text section where relativeAddress belongs to.
    // Keep track of the filename the .text section belongs to.
    if( currentSym->StorageClass == IMAGE_SYM_CLASS_FILE )
      latestFileSymbol = currentSym ;
    // Borland uses "CODE" instead of the standard ".text" entry
    // Microsoft uses sections that only _begin_ with .text
    const char* symName = GetSymbolName( currentSym ) ;
    if( strnicmp( symName, ".text", 5 ) == 0 || 
        strcmpi( symName, "CODE" ) == 0 )
      if( currentSym->Value <= relativeAddress )
        {
        PIMAGE_AUX_SYMBOL auxSym = (PIMAGE_AUX_SYMBOL)(currentSym + 1) ;
        if( currentSym->Value + auxSym->Section.Length >= relativeAddress )
          fileSymbol = latestFileSymbol ;
        }
    // Look for the function with biggest address <= relativeAddress
    BOOL isFunction = ISFCN( currentSym->Type ) ; // Type == 0x20, See WINNT.H
    if( isFunction && 
        ( currentSym->StorageClass == IMAGE_SYM_CLASS_EXTERNAL ||
          currentSym->StorageClass == IMAGE_SYM_CLASS_STATIC ) )
      {
      if( currentSym->Value <= relativeAddress &&
          currentSym->Value > maxFnAddress )
        {
        maxFnAddress = currentSym->Value ;
        fnSymbol = currentSym ;
        }
      }
    // Advance counters, skip aux symbols
    i += currentSym->NumberOfAuxSymbols ;
    currentSym += currentSym->NumberOfAuxSymbols ;
    currentSym++ ;
    }
  // dump symbolic info if found
  if( fileSymbol )
    {
    const char* auxSym = (const char*)(fileSymbol + 1) ;
    if( strcmpi( latestFile, auxSym ) )
      {
      strcpy( latestFile, auxSym ) ;
      dumpBuffer.Printf( "  file: %s\r\n", auxSym ) ;    
      }
    }
  else
    {
    latestFile[ 0 ] = 0 ;
    dumpBuffer.Printf( "  file: unknown\r\n" ) ;    
    }
  if( fnSymbol )
#if defined(_USE_BSCKIT)
    dumpBuffer.Printf( "    function: %s", demangle (GetSymbolName (fnSymbol), pcModule) ) ;
#else
    dumpBuffer.Printf( "    function: %s", GetSymbolName( fnSymbol ) ) ;
#endif // _USE_BSCKIT
  else
    dumpBuffer.Printf( "    function: <unknown>" ) ;
  }


PIMAGE_SECTION_HEADER PE_Debug :: SectionHeaderFromName( const char* name )
  {
  PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION( NT_Header ) ;
  for( unsigned i = 0; i < NT_Header->FileHeader.NumberOfSections; i++ )
    {
    if( strnicmp( (const char*)section->Name, name, IMAGE_SIZEOF_SHORT_NAME ) == 0 )
      return( section ) ;
    else
      section++ ;
    }
  return 0;
  }


PIMAGE_COFF_SYMBOLS_HEADER PE_Debug :: GetDebugHeader()
  {
  // Some files have a wrong entry in the COFF header, so
  // first check if the debug info exists at all
  if( NT_Header->FileHeader.PointerToSymbolTable == 0 )
    return( 0 ) ;
  DWORD debugDirRVA = NT_Header->OptionalHeader.
                      DataDirectory[ IMAGE_DIRECTORY_ENTRY_DEBUG ].
                      VirtualAddress;
  if( debugDirRVA == 0 )
    return( 0 ) ;

  // The following values must be calculated differently for MS/Borland files
  PIMAGE_DEBUG_DIRECTORY debugDir ;
  DWORD size ;

  // Borland files have the debug directory at the beginning of a .debug section
  PIMAGE_SECTION_HEADER debugHeader = SectionHeaderFromName( ".debug" ) ;
  if( debugHeader && debugHeader->VirtualAddress == debugDirRVA )
    {
    debugDir = (PIMAGE_DEBUG_DIRECTORY)(debugHeader->PointerToRawData + (DWORD)fileBase) ;
    size = NT_Header->OptionalHeader.
           DataDirectory[ IMAGE_DIRECTORY_ENTRY_DEBUG ].Size *
           sizeof( IMAGE_DEBUG_DIRECTORY ) ;
    }
  else
  // Microsoft debug directory is in the .rdata section
    {
    debugHeader = SectionHeaderFromName( ".rdata" ) ;
    if( debugHeader == 0 )
      return( 0 ) ;
    size = NT_Header->OptionalHeader.
           DataDirectory[ IMAGE_DIRECTORY_ENTRY_DEBUG ].Size ;
    DWORD offsetInto_rdata = debugDirRVA - debugHeader->VirtualAddress ;
    debugDir = BasedPtr( PIMAGE_DEBUG_DIRECTORY, fileBase,
                         debugHeader->PointerToRawData + offsetInto_rdata ) ;
    }

  // look for COFF debug info
  DWORD debugFormats = size / sizeof( IMAGE_DEBUG_DIRECTORY ) ;
  for( DWORD i = 0; i < debugFormats; i++ )
    {
    if( debugDir->Type == IMAGE_DEBUG_TYPE_COFF )
      return( (PIMAGE_COFF_SYMBOLS_HEADER)((DWORD)fileBase + debugDir->PointerToRawData) ) ;
    else
      debugDir++ ;
    }
  return( NULL ) ;
  }


void PE_Debug :: FindDebugInfo()
  {
  ClearDebugPtrs() ;
  // Put everything into a try/catch in case the file has wrong fields
  try
    {
    // Verify that fileBase is a valid pointer to a DOS header
    if( fileBase->e_magic == IMAGE_DOS_SIGNATURE )
      {
      // Get a pointer to the PE header
      NT_Header = BasedPtr( PIMAGE_NT_HEADERS, fileBase, fileBase->e_lfanew ) ;
      // Verify that NT_Header is a valid pointer to a NT header
      if( NT_Header->Signature == IMAGE_NT_SIGNATURE )
        {
        // Get a pointer to the debug header if any
        COFFDebugInfo = GetDebugHeader() ;
        // Get a pointer to the symbol table and retrieve the number of symbols
        if( NT_Header->FileHeader.PointerToSymbolTable )
          COFFSymbolTable = 
            BasedPtr( PIMAGE_SYMBOL, fileBase, NT_Header->FileHeader.PointerToSymbolTable ) ;
        COFFSymbolCount = NT_Header->FileHeader.NumberOfSymbols ;
        // The string table starts right after the symbol table
        stringTable = (const char*)(COFFSymbolTable + COFFSymbolCount) ; 
        }
      }
    }
  catch( ... )
    {
    // Header wrong, do nothing
    }
  }


void PE_Debug :: MapFileInMemory( const char* module )
  {
  ClearFileCache() ;
  hFile = CreateFile( module, GENERIC_READ, FILE_SHARE_READ, NULL,
                             OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 ) ;
  if( hFile != INVALID_HANDLE_VALUE )
    {
    hFileMapping = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, 0, NULL ) ;
    if( hFileMapping != 0 )
      fileBase = (PIMAGE_DOS_HEADER)MapViewOfFile( hFileMapping, FILE_MAP_READ, 0, 0, 0 ) ;
    }
  // NB: open files/mapping are closed later in ClearFileCache
  }


void PE_Debug :: DumpDebugInfo( DumpBuffer& dumpBuffer, const BYTE* caller, HINSTANCE hInstance )
  {
  // Avoid to open, map and looking for debug header/symbol table
  // by caching the latest and comparing the actual module with
  // the latest one.
  static char module[ MAX_MODULENAME_LEN ] ;
  GetModuleFileName( hInstance, module, MAX_MODULENAME_LEN ) ;
  if( strcmpi( latestModule, module ) )  // New module
    {
    strcpy( latestModule, module ) ;
    dumpBuffer.Printf( "Module: %s\r\n", module ) ;
    MapFileInMemory( module ) ;
    FindDebugInfo() ;
    }

  if( fileBase )
    {
    // Put everything into a try/catch in case the file has wrong fields
    try
      {
      DWORD relativeAddress = caller - (BYTE*)hInstance ;
      // Dump symbolic information and line number if available
      if( COFFSymbolCount != 0 && COFFSymbolTable != NULL )
        {
        DumpSymbolInfo( dumpBuffer, relativeAddress, module ) ;
        if( COFFDebugInfo )
          DumpLineNumber( dumpBuffer, relativeAddress ) ;
        }
      else
        {
        dumpBuffer.Printf( "  no debug information (COFF)\r\n" ) ;
        dumpBuffer.Printf( "    address: %08X\r\n", caller ) ;
        }
      }
    catch( ... )
      {
      // Header wrong, do nothing
      }
    }
  else
    {
    dumpBuffer.Printf( "  module not accessible\r\n" ) ;
    dumpBuffer.Printf( "    address: %08X\r\n", caller ) ;
    }
  }

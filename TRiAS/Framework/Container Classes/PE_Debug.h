// PE_Debug.H

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#ifndef PE_DEBUG_


#define PE_DEBUG_


class DumpBuffer ;


class PE_Debug
  {
  public :
    PE_Debug() ;
    ~PE_Debug() ;
    void ClearReport() ;
    void DumpDebugInfo( DumpBuffer& dumpBuffer, const BYTE* caller, HINSTANCE hInstance ) ;
    void Display() ;
  private :
    // Report data
    enum { MAX_MODULENAME_LEN = 512, MAX_FILENAME_LEN = 256 } ;
    char latestModule[ MAX_MODULENAME_LEN ] ;
    char latestFile[ MAX_FILENAME_LEN ] ;
    // File mapping data
    HANDLE hFile ;
    HANDLE hFileMapping ;
    PIMAGE_DOS_HEADER fileBase ;
    // Pointers to debug information
    PIMAGE_NT_HEADERS NT_Header ;
    PIMAGE_COFF_SYMBOLS_HEADER COFFDebugInfo ;
    PIMAGE_SYMBOL COFFSymbolTable ;
    int COFFSymbolCount ;
    const char* stringTable ;

    void ClearFileCache() ;
    void ClearDebugPtrs() ;
    void MapFileInMemory( const char* module ) ;
    void FindDebugInfo() ;
    void DumpSymbolInfo( DumpBuffer& dumpBuffer, DWORD relativeAddress, LPCSTR pcModule ) ;
    void DumpLineNumber( DumpBuffer& dumpBuffer, DWORD relativeAddress ) ;
    PIMAGE_COFF_SYMBOLS_HEADER GetDebugHeader() ;
    PIMAGE_SECTION_HEADER SectionHeaderFromName( const char* name ) ;
    const char* GetSymbolName( PIMAGE_SYMBOL sym ) ;
  } ;


#endif  // #ifndef PE_DEBUG_


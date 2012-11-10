// DumpBuffer.H

// Author: Dr. Carlo Pescio
// Eptacom Consulting
// Via Bernardo Forte 2-3
// 17100 Savona - ITALY
// Fax +39-19-854761
// email pescio@programmers.net


#ifndef DUMP_BUFFER_


#define DUMP_BUFFER_


class DumpBuffer
{
public :
    DumpBuffer();
    void Clear();
    void Printf (const char* format, ...);
    void StaticPrintf (const char* format, ...);
    void SetWindowText (HWND hWnd) const;
    void StaticSetWindowText (HWND hWnd) const;

private:
    enum { BUFFER_SIZE = 32000, STATIC_BUFFER_SIZE = 512 } ;
    char buffer[BUFFER_SIZE];
	char static_buffer[STATIC_BUFFER_SIZE];
    char *current;
	char *static_current;
};

void DumpCallsStack (DumpBuffer& dumpBuffer);

#endif // #ifndef DUMP_BUFFER_

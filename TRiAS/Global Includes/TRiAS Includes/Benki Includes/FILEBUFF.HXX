/*
Datei: FILEBUFF.HXX

Erarbeitet: J. Benkenstein                                      Stand vom 8.9.94
*/

#ifndef _FILEBUFF_HXX 
#define _FILEBUFF_HXX 

const short FileBufferSize = 1024 * 16;    // Datei-Puffer-Größe

class CFileBuffer
{                 
public:
	char *m_pBuffer;
	uint m_uSize;
	
	CFileBuffer (void) { m_pBuffer = NULL; m_uSize = 0; }
	~CFileBuffer (void) { if (m_pBuffer) delete [] m_pBuffer; }
	
	char* CreateBuffer (short Size = FileBufferSize) {  m_uSize = Size;
			    return m_pBuffer = new char [Size]; }
	char* Addr (void) { return m_pBuffer; }
	uint GetSize (void) { return m_uSize; }
};

#endif          // _FILEBUFF_HXX

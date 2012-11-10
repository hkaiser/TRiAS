#include	"stdafx.h"
#include	"metafile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	new	DEBUG_NEW

const int MemChunkSize = 8 * 1024;
const int RecChunkSize = 256;

CMetaMemory::CMetaMemory() {
	m_pMemory = NULL;
	m_pRecords = NULL;
	m_dwMemSize = 0;
	m_dwMemRemain = 0;
	m_dwMemLast = 0;

	m_dwRecSize = 0;
	m_dwRecRemain = 0;
	m_dwRecLast = 0;
}

CMetaMemory::~CMetaMemory() {
	if( NULL != m_pMemory )
		delete[] m_pMemory;
	if( NULL != m_pRecords )
		delete[] m_pRecords;
}

void CMetaMemory::Push( METARECORD FAR* pRecord ) {
	DWORD	dwTmp;
	while( m_dwMemRemain < pRecord->rdSize * sizeof(WORD) ) {
		dwTmp = ( m_dwMemSize / MemChunkSize ) * MemChunkSize + MemChunkSize;
		HPBYTE	pNewMem = new BYTE[dwTmp];
		memset( pNewMem, 0x00, dwTmp );
		if( NULL != m_pMemory ) {
			memcpy( pNewMem, m_pMemory, m_dwMemSize - m_dwMemRemain );
			delete[] m_pMemory;
		}
		m_dwMemRemain += MemChunkSize;
		m_dwMemSize = dwTmp;
		m_pMemory = pNewMem;
	}
	if( m_dwRecRemain < 2 ) {
		dwTmp = ( m_dwRecSize / RecChunkSize ) * RecChunkSize + RecChunkSize;
		LPMETARECORD *pNewMem = new LPMETARECORD[dwTmp];
		memset( pNewMem, 0x00, dwTmp * sizeof(HPBYTE) );
		if( NULL != m_pRecords ) {
			memcpy( pNewMem, m_pRecords, m_dwRecSize * sizeof(HPBYTE) );
			delete[] m_pRecords;
		}
		m_dwRecRemain += RecChunkSize;
		m_dwRecSize = dwTmp;
		m_pRecords = pNewMem;
	}
	dwTmp = pRecord->rdSize * sizeof(WORD);
	m_pRecords[m_dwRecLast] = (LPMETARECORD) &m_pMemory[m_dwMemLast];
	memcpy( &m_pMemory[m_dwMemLast], pRecord, dwTmp );
	m_dwMemLast += dwTmp;
	m_dwMemRemain -= dwTmp;
	m_dwRecLast++;
}

void CMetaMemory::Reset() {
	m_dwMemRemain = m_dwMemSize;
	m_dwRecRemain = m_dwRecSize;
	m_dwMemLast = 0;
	m_dwRecLast = 0;
}

CMetaMemory& CMetaMemory::operator+=( const CMetaMemory& m ) {
	LPMETARECORD lpMR;
	for( DWORD i = 0; i < m.m_dwRecLast; i++ ) {
		lpMR = m.m_pRecords[i];
		Push(lpMR);
	}
	return *this;
}

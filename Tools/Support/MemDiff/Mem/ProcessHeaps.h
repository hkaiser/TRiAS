//==================================================
// MemDiff - Matt Pietrek 1999
// Microsoft Systems Journal, December 1999
// FILE: ProcessHeaps.h
//==================================================
#if !defined(AFX_PROCESSHEAPS_H__9C1EA1C2_1037_41FF_B60F_2FB75FDD45FC__INCLUDED_)
#define AFX_PROCESSHEAPS_H__9C1EA1C2_1037_41FF_B60F_2FB75FDD45FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProcessHeaps  
{
	// structure to hold info about each heap
	struct CProcessHeapInfo
	{
		PVOID	m_pStart;
		PVOID	m_pEnd;
	};

	unsigned			m_nHeaps;
	HANDLE				m_aHeaps[ 256 ];
	CProcessHeapInfo	m_aHeapInfo[ 256 ];

public:
	bool IsAddressInHeaps( PVOID pAddr );
	CProcessHeaps();
	virtual ~CProcessHeaps(){}

};

#endif // !defined(AFX_PROCESSHEAPS_H__9C1EA1C2_1037_41FF_B60F_2FB75FDD45FC__INCLUDED_)



#include "stdafx.h"
 

#include "del.hpp"

// Klasse löscht Pointer
//--------------------------------------------------------------

DelPointer :: DelPointer()
{
}

void DelPointer :: Del(long* pX, long* pY, long* pK)
{
	m_pY = pY;  
	m_pX = pX;
	m_pK = pK;
	
	if (m_pY)
		delete m_pY;
	if (m_pX)
		delete m_pX;
	if (m_pK)
		delete m_pK;
}


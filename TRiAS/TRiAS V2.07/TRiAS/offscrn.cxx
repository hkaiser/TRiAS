// OffScreenBuffer, über welchen gezeichnet wird ------------------------------
// File: OFFSCRN.CXX

#include "triaspre.hxx"

#include "offscrn.hxx"

///////////////////////////////////////////////////////////////////////////////
// FensterObjekt --------------------------------------------------------------
// Konstruktor/Destruktor/Initialisierung 
COffScreenBuffer::
COffScreenDC::COffScreenDC (HDC hDC, Rectangle &rc)
	: CDCWindow (hDC, rc, hDC)
{
	// nothing else to do
}

COffScreenBuffer::
COffScreenDC::~COffScreenDC (void)
{
	// nothing else to do
}

bool COffScreenBuffer::
COffScreenDC::DCExpose (CDCExposeEvt)
{
	// intensionally left free
}

///////////////////////////////////////////////////////////////////////////////
// DrawObject -----------------------------------------------------------------
// Konstruktor/Destruktor/Initialisierung 
COffScreenBuffer::COffScreenBuffer (void)
{
	m_hBmp = NULL;
	m_pDCWnd = NULL;
}

COffScreenBuffer::~COffScreenBuffer (void)
{
	if (NULL != m_hBmp)	{
		m_hBmp = ::SelectObject (m_hDC, m_hBmp);
		::DeleteObject (m_hBmp);
	}
	DELETE(m_pDCWnd);
}


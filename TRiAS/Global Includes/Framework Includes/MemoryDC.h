///////////////////////////////////////////////////////////////////////////
// @doc 
// @module MemoryDC.h | FlickerFree drawing for CommonVu-Windows

#if !defined(_MEMORYDC_H__894418F4_DB91_11D1_85FE_00600875138A__INCLUDED_)
#define _MEMORYDC_H__894418F4_DB91_11D1_85FE_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// minimaler Zeitabstand zwischen zweimal Zeichnen
extern DWORD g_dwTicksBetweenPaints;

/////////////////////////////////////////////////////////////////////////////
// 
class CMemoryDC 
{
private:
	Window *m_pW;
	HDC m_hDC;
	HDC m_hMemDC;
	HBITMAP m_hOldBitmap;
	HBITMAP m_hBitmap;
	Rectangle m_rect;
	bool m_fEnable;
	bool m_fDeleteBmp;
	DWORD m_dwTicks;

public:
	CMemoryDC (Window *pW, BOOL fEnable, HBITMAP *phBmp) :
		m_pW(pW), m_hOldBitmap(NULL), m_hBitmap(NULL), m_fEnable(false), m_fDeleteBmp(false)
	{
		if (!fEnable) return;		// nothing else to do

		_ASSERTE(NULL != m_pW);

	// aktuelle DC's zwischenspeichern
		m_hDC = (HDC)m_pW -> Handle (API_WINDOW_HDC);

	// MemDC's erzeugen/konfigurieren
		m_hMemDC = ::CreateCompatibleDC(m_hDC);
		if (NULL == m_hMemDC) return;

		::GetClientRect (m_pW -> Handle (API_WINDOW_HWND), (RECT *)&m_rect);
		if (NULL != phBmp && NULL != *phBmp)
			m_hBitmap = *phBmp;
		else 
			m_hBitmap = ::CreateCompatibleBitmap (m_hDC, m_rect.Width(), -m_rect.Height()+1);

		if (NULL != m_hBitmap) {
		// neue DC's einstellen, aber nur, wenn der Speicher gereicht hat 
			m_hOldBitmap = (HBITMAP)::SelectObject(m_hMemDC, m_hBitmap);
			m_pW -> SetHandle (API_WINDOW_HDC, m_hMemDC);

			m_dwTicks = ::GetTickCount();
			m_fEnable = true;

			if (NULL != phBmp) {
				if (NULL == *phBmp) 
					*phBmp = m_hBitmap;
			} else
				m_fDeleteBmp = true;

		} else
			::DeleteDC (m_hMemDC);
	}

	BOOL Draw (BOOL fForce)
	{
		if (!m_fEnable) return FALSE;		// nothing else to do
	
	DWORD dwTicks = ::GetTickCount();
	BOOL fResult = FALSE;

		if (fForce || dwTicks-m_dwTicks >= g_dwTicksBetweenPaints) {
		// die minimale Zeit zwischen zweimal Zeichnen ist um 
		HPALETTE hOldPalette = NULL;
		extern HPALETTE hPalette;

			if (NULL != hPalette) {
			// Palette einstellen       
				hOldPalette = ::SelectPalette (m_hDC, hPalette, FALSE);
				::RealizePalette (m_hDC);
			}
			fResult = ::BitBlt (m_hDC, m_rect.Left(), m_rect.Top(), m_rect.Width(), -m_rect.Height()+1,
								m_hMemDC, m_rect.Left(), m_rect.Top(), SRCCOPY);

			if (NULL != hPalette)
				::SelectPalette (m_hDC, hOldPalette, FALSE);
			m_dwTicks = dwTicks;
		}
		return fResult;
	}

	~CMemoryDC()
	{
		if (!m_fEnable) return;			// nothing else to do

	// alte DC's wieder einstellen
		m_pW -> SetHandle (API_WINDOW_HDC, m_hDC);

	// Bitmaps freigeben
		_ASSERTE(NULL != m_hBitmap);
		_ASSERTE(NULL != m_hMemDC);
		::SelectObject (m_hMemDC, m_hOldBitmap);
		if (m_fDeleteBmp) {
			::DeleteObject(m_hBitmap);
			m_hBitmap = NULL; 
		}
		::DeleteDC(m_hMemDC);
	}

	bool operator! () { return !IsValid(); }
	bool IsValid() { return m_fEnable; }
};

#endif // !defined(_MEMORYDC_H__894418F4_DB91_11D1_85FE_00600875138A__INCLUDED_)

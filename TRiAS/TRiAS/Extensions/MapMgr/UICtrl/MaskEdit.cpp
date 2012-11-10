#include "stdafx.h"
#include "UICtrl.h"
#include "MaskEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CMaskEdit

STDMETHODIMP CMaskEdit::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr[] =  {
		&IID_IMaskEdit,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++) {
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CMaskEdit::OnDraw(ATL_DRAWINFO& di) {
	if( m_ctlEdit.m_hWnd ) {
		HFONT hOldFont = NULL;
		if (m_pFont) {
			CComPtr<IFont> pFont;
			m_pFont->QueryInterface(IID_IFont, (void**)&pFont);
			HFONT hfont;
			pFont->get_hFont(&hfont);
			m_ctlEdit.SetFont( hfont );
		}
	}
	RefreshDisplay();
	return S_OK;
}

HRESULT CMaskEdit::FinalConstruct() {
	FONTDESC	f;
	memset( &f, 0, sizeof(f) );
	f.cbSizeofstruct = sizeof(f);
    f.lpstrName = L"MS Sans Serif";
    f.cySize.Lo = 8;
    f.sWeight = FW_NORMAL;
    f.sCharset = DEFAULT_CHARSET;
    f.fItalic = false;
    f.fUnderline = false;
    f.fStrikethrough = false;
	IFontDisp*	u;
	HRESULT hr = OleCreateFontIndirect( &f, IID_IFontDisp, (void**) &u );
	if( S_OK == hr ) {
		m_pFont = CComPtr<IFontDisp>(u);
		u->Release();
	}
	put_Mask( CComBSTR( _T("6-999.999,999") ) );
	put_Text( _T(','), CComBSTR( _T("4-603.619,703") ) );
//	CComBSTR	s;
//	get_Text( _T(','), &s );
	return S_OK;
}
HRESULT CMaskEdit::FinalRelease() {
	return S_OK;
}

STDMETHODIMP CMaskEdit::get_Mask(BSTR * pVal) {
	_ASSERTE(m_nMaskLen <= _countof(m_strMask) );
	TCHAR	s[MAX_MASK_LEN];
	LPCTSTR	pC;
	UINT	nChar;
	UINT	c;
	for( nChar = 0, pC = m_strMask; *pC && nChar < m_nMaskLen; pC++, nChar++ ) {
		c = ( 256 + *pC ) % 256;
		s[nChar] = isMaskLiteral(c) ? c : m_chCodeTable[c];
	}
	s[nChar] = _T('\0');
	USES_CONVERSION;
	*pVal = ::SysAllocString( A2W(s) );
	return S_OK;
}

STDMETHODIMP CMaskEdit::put_Mask(BSTR newVal) {
	USES_CONVERSION;
	LPCTSTR	p = W2A( newVal );
	ParseMaskString( p );
	BuildDisplayString();
	RefreshDisplay();
	::SysFreeString( newVal );
	return S_OK;
}

STDMETHODIMP CMaskEdit::get_PromptChar(BSTR * pVal) {
	TCHAR	tc[2];
	LPCTSTR	p = tc;
	tc[0] = m_chPrompt;
	tc[1] = _T('\0');
	USES_CONVERSION;
	*pVal = ::SysAllocString( A2W(p) );
	return S_OK;
}

STDMETHODIMP CMaskEdit::put_PromptChar(BSTR newVal) {
	USES_CONVERSION;
	LPCTSTR	p = W2A(newVal);
	m_chPrompt = *p;
	BuildDisplayString();
	::SysFreeString( newVal );
	return S_OK;
}

STDMETHODIMP CMaskEdit::get_EscapeChar(BSTR * pVal) {
	TCHAR	tc[2];
	tc[0] = m_chEscape;
	tc[1] = _T('\0');
	USES_CONVERSION;
	*pVal = ::SysAllocString( A2W(tc) );
	return S_OK;
}

STDMETHODIMP CMaskEdit::get_Text(short DelimterCharacter, BSTR * pVal) {
	TCHAR	szText[MAX_MASK_LEN];
	UINT	nChar;
	UINT	nDstChar;
	for( nChar = 0, nDstChar = 0; nChar < m_nMaskLen; nChar++ ) {
		if( isMaskChar( nChar ) || m_strDisplay[nChar] == (TCHAR) DelimterCharacter )
			szText[nDstChar++] = m_strDisplay[nChar];
	}
	szText[nDstChar] = _T('\0');
	USES_CONVERSION;
	*pVal = ::SysAllocString( A2W(szText) );
	return S_OK;
}

STDMETHODIMP CMaskEdit::put_Text(short DelimterCharacter, BSTR newVal) {
	USES_CONVERSION;
	LPCTSTR	lpszText = W2A(newVal);
	PullChar( 0, m_nMaskLen );
	for( UINT nChar = 0; nChar < m_nMaskLen; nChar++ ) {
		if( isMaskChar( nChar ) )
			PushChar( nChar, lpszText[nChar] );
	}
	::SysFreeString( newVal );
	return S_OK;
}

LRESULT CMaskEdit::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	TCHAR	ch = wParam;
	if( !m_bReadOnly ) {
		UINT	nStartPos;
		UINT	nEndPos;
		GetSel( nStartPos, nEndPos );
	
		if(IsCharValid(nStartPos, ch))	  {		 
			if(nStartPos != nEndPos)		// multi-select
				PullChar(nStartPos, nEndPos);
			PushChar(nStartPos, ch);
			RefreshDisplay();
			UINT nNewPos = SetCursorPos(nStartPos, 1);
			Fire_TextChange();
			if( nNewPos == nStartPos )
				Fire_AdvanceFocusNext();
		}
		else {
			MessageBeep(MB_ICONEXCLAMATION);
		}
	}
	return 0;
}

LRESULT CMaskEdit::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	int		virtKey = (int) wParam;
	long	nKeyData = lParam;
	UINT	nStartPos;
	UINT	nEndPos;
	bool	bShift = 0 != (::GetKeyState(VK_SHIFT) & 0x8000);

	int	nRet = 0;
	GetSel( nStartPos, nEndPos );

	switch(virtKey) {
	case VK_BACK: {
		}
		break;
	case VK_DELETE: {
			if( nStartPos == nEndPos ) {
				PullChar( nStartPos, nStartPos + 1 );
			} else {				
				PullChar( nStartPos, nEndPos );
			}
			RefreshDisplay();
			SetCursorPos(nStartPos, 0 );
		}
		break;
	case VK_LEFT: {
			UINT nNewPos = SetCursorPos(nStartPos, -1, bShift ? nEndPos : -1);
			if( nNewPos == nStartPos )
				Fire_AdvanceFocusPrevious();
		}
		break;
	case VK_RIGHT: {
			UINT nNewPos = SetCursorPos(nStartPos, 1, bShift ? nStartPos : -1);
			if( nNewPos == nStartPos )
				Fire_AdvanceFocusNext();
		}
		break;
	case VK_END: {
			UINT nPos = GetPrevDataPos(m_nMaskLen - 1);
			SetCursorPos(nPos, 1 );
		}
		break;
	case VK_HOME: {
			UINT nPos = GetNextDataPos(0);
			SetCursorPos( nPos, -1 );
		}
		break;
	case VK_INSERT: {
//			m_bInsertMode = !m_bInsertMode;
		}
		break;
	default :
		bHandled = false;
	}
	return nRet;
}

UINT CMaskEdit::SetCursorPos( UINT nOldPos, int nDirection, int startSel ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nOldPos <= m_nMaskLen && nOldPos >= 0);
	_ASSERTE(nDirection == 0 || nDirection == 1 || nDirection == -1 );

	UINT nNewPos = nOldPos;					//new position for cursor
	int nPosHolder = 0;						//position holder
	
	if(0 == m_nMaskLen)	
		return 0;
	if( 0 == nDirection ) {
		startSel = nNewPos;
	} else if( 1 == nDirection ) {
		nNewPos = GetNextDataPos(nOldPos);
		if( -1 == startSel ) {
			startSel = nNewPos;
		} 
	} else if( -1 == nDirection ) {
		nNewPos = GetPrevDataPos(nOldPos);
		if( -1 == startSel ) {
			startSel = nNewPos;
		} 
	}
	_ASSERTE( nNewPos >= 0 && nNewPos <= m_nMaskLen );
	SetSel( startSel, nNewPos );
	return nNewPos;
}

UINT CMaskEdit::GetNextDataPos( UINT nOldPos ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nOldPos <= m_nMaskLen && nOldPos >= 0);

	UINT nNewPos = nOldPos;						//new position for cursor
	if(0 == m_nMaskLen)	
		return 0;
	if( !isMaskLiteral( m_strMask[nNewPos] ) && nNewPos != m_nMaskLen )
		nNewPos++;
	while( isMaskLiteral( m_strMask[nNewPos] ) && nNewPos != m_nMaskLen ) {
		nNewPos++;
	}
	if( nNewPos == m_nMaskLen )
		nNewPos = nOldPos;
	return nNewPos;
}

UINT CMaskEdit::GetPrevDataPos( UINT nOldPos ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nOldPos <= m_nMaskLen && nOldPos >= 0);

	int nNewPos = nOldPos;						//new position for cursor
	if(0 == m_nMaskLen)
		return 0;
	if( nNewPos > 0 && !isMaskLiteral( m_strMask[nNewPos] ) )
		nNewPos--;
	for( ;; ) {
		if( 0 == nNewPos || !isMaskLiteral( m_strMask[nNewPos] ) )
			break;
		nNewPos--;
	}
	if( isMaskLiteral( m_strMask[nNewPos]  ) && 0 == nNewPos ) {
		nNewPos = nOldPos;
	}
	return nNewPos;
}

void CMaskEdit::PullChar( UINT nFromPos, UINT nToPos, bool bSetUndoBuffer ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nFromPos <= m_nMaskLen && nFromPos >= 0);
	_ASSERTE(nToPos <= m_nMaskLen && nToPos >= 0);
	TCHAR	ch;

	if( nFromPos == nToPos )
		return;
	UINT	nDstPos, nSrcPos;
	for( nSrcPos = nToPos, nDstPos = nFromPos; nDstPos < m_nMaskLen; nDstPos++ ) {
		if( !isMaskChar( nDstPos ) ) {
			continue;
		}
		for( ; nSrcPos < m_nMaskLen && !isMaskChar( nSrcPos ); nSrcPos++ ) {
			;
		}
		if( nSrcPos >= m_nMaskLen ) {
			ch = m_chPrompt;
		} else if( !IsCharValid( nDstPos, m_strDisplay[nSrcPos] ) ) {
			ch = m_chPrompt;
		} else {
			ch = m_strDisplay[nSrcPos];
		}
		m_strDisplay[nDstPos] = ch;
		nSrcPos++;
	}
}

void CMaskEdit::PushChar( UINT nStartPos, TCHAR ch, bool bRefreshDisplay ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nStartPos <= m_nMaskLen && nStartPos >= 0 );

	if(m_bInsertMode) {
		UINT	nDstPos = m_nMaskLen - 1;
		UINT	nSrcPos = 0;
		TCHAR	c;
		for( ; nDstPos > nStartPos; nDstPos-- ) {
			if( !isMaskChar( nDstPos ) )
				continue;
			for( nSrcPos = nDstPos - 1; !isMaskChar( nSrcPos ); nSrcPos-- ) {
				;
			}
			if( IsCharValid( nDstPos, m_strDisplay[nSrcPos] ) ) {
				c = m_strDisplay[nSrcPos];
			} else {
				c = m_chPrompt;
			}
			m_strDisplay[nDstPos] = c;
		}
	}
	m_strDisplay[nStartPos] = ch;
}

/*
UINT CMaskEdit::GetRepaintPos(UINT iIndex) {
	HDC		hdc = NULL;
	UINT	nRetPos = 0;
	
	//because edit controls don't keep their current font in the HDC,
	//we need to get it and select it into the HDC before doing the
	//calculations
	HFONT hCurFont = (HFONT)SendMessage(WM_GETFONT, 0, 0);
	
	hdc = ::GetDC(m_hWnd);											
	
	if(hdc != NULL) {
		HFONT hOldFont = (HFONT)::SelectObject(hdc, hCurFont);
		SIZE	szFont;
		GetTextExtentPoint( hdc, m_strDisplay, iIndex, &szFont );
		nRetPos = szFont.cx;
		SelectObject(hdc, hOldFont);
		::ReleaseDC(m_hWnd, hdc);
	}
	return nRetPos;
}
*/

void CMaskEdit::BuildDisplayString() {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	LPCTSTR	pC;
	UINT	n;
	for( n = 0, pC = m_strMask; *pC && n < m_nMaskLen; pC++, n++) {
		m_strDisplay[n] = isMaskLiteral(*pC) ? *pC : m_chPrompt;
	}
	m_strDisplay[n] = _T('\0');
}

////////////////////////////////////////////////////////////////////
// Codetabelle: Zeichen zwischen 0x20 (Space) und 0xff initialisieren
// und dann alle Zeichen die als Codes verwendet werden (szCodes)
// mit einem Wert kleiner als 0x20 belegen; dieser Wert gibt dann im
// unteren Teil der Tabelle das eigentliche Codezeichen an.

static TCHAR szCodes[] = _T("0123456789ANLUX+");

HRESULT CMaskEdit::InitCodetable( ) {
	for( int i = 0; i < _countof(m_chCodeTable); i++ )
		m_chCodeTable[i] = i;
	TCHAR	*pC = szCodes;
	for( i = 0; *pC; pC++, i++ ) {
		m_chCodeTable[*pC] = i;
		m_chCodeTable[i] = *pC;
	}
	return S_OK;
}
//°59°59'59"
HRESULT CMaskEdit::ParseMaskString(LPCTSTR lpszMask ) {
	HRESULT	hr = E_FAIL;
	try {
		bool bEscapeChar = false;
		TCHAR	strMask[MAX_MASK_LEN];
		memset( strMask, 0, sizeof(strMask) );
		LPCTSTR	pC;
		UINT	c;
		for( m_nMaskLen = 0, pC = lpszMask; *pC && m_nMaskLen < MAX_MASK_LEN - 1; pC++ ) {
			c = ( 256 + *pC ) % 256;
			if( c < 0x20 )
				break;
			if( bEscapeChar ) {
				strMask[m_nMaskLen] = c;
				bEscapeChar = false;
			} else if(c == (UINT) m_chEscape) {
				bEscapeChar = true;
				continue;
			} else {
				strMask[m_nMaskLen] = m_chCodeTable[c];
			}
			m_nMaskLen++;
		}
		strMask[m_nMaskLen] = _T('\0');
		memcpy( m_strMask, strMask, m_nMaskLen * sizeof(TCHAR) );
		hr = S_OK;
	} catch(...) {
		hr = E_OUTOFMEMORY;
	}
	return hr;
}

////////////////////////////////////////////////////////////////////
// *Wäre* es korrekt, das Zeichen ch an der Stelle nPos in den
// aktuelle String einzufügen?

bool CMaskEdit::IsCharValid(UINT nPos, TCHAR& ch ) {
	_ASSERTE(m_nMaskLen < _countof(m_strMask) );
	_ASSERTE(nPos <= m_nMaskLen && nPos >= 0);

	bool bRet = false;
	int iSpread = (_T('a') - _T('A'));
	
	_ASSERTE(ch != _T('\0'));
	if(ch == _T('\0')) {
		return false;
	}

	if( nPos >= m_nMaskLen )
		return false;

	TCHAR chMask = m_strMask[nPos];

	if( isMaskLiteral(chMask) )
		return false;

	chMask = m_chCodeTable[chMask];
	if( _T('0') <= chMask && _T('9') >= chMask ) {	// numerical in range
		bRet = (ch <= chMask && ch >= _T('0') );
		return bRet;
	}

	bRet = false;
	switch( chMask ) {
	case _T('A'): {	//alphas only
			bRet = ((ch >= _T('a') && ch <= _T('z')) || (ch >= _T('A') && ch <= _T('Z')));
		}
		break;
	case _T('N'): {	//alpanumerics only
			bRet = (
				(ch >= _T('a') && ch <= _T('z')) 
				 || (ch >= _T('A') && ch <= _T('Z'))
				 || (ch >= _T('0') && ch <= _T('9'))
				 );
		}
		break;
	case _T('L'): {	//force lower case
			if((ch >= _T('a') && ch <= _T('z')) || (ch >= _T('A') && ch <= _T('Z'))) {
				if(ch >= _T('A') && ch <= _T('Z'))
					ch += iSpread;
				bRet = TRUE;
			}
		}
		break;
	case _T('U'): {	//force upper case
			if((ch >= _T('a') && ch <= _T('z')) || (ch >= _T('A') && ch <= _T('Z'))) {
				if(ch >= _T('a') && ch <= _T('z'))
					ch -= iSpread;
				bRet = TRUE;
			}
		}
		break;
	case _T('X'): {	//any ASCII character
			bRet = ( ch >= 0x20 && ch <= 0xff );
		}
		break;
	case _T('+'): { // +/- sign
			bRet = ( ch == _T('+') || ch == _T('-') );
		}
		break;
	}
	return bRet;
}


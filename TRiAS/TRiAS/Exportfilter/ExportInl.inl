#if !defined(__XT) || !defined(__DEXPROCS) 
#error "you must compile with __XT and __DEXPROCS defined"
#endif

#if defined(_DEX_INLINE)

#pragma HDR_ON()

#if defined(_DEBUG)
extern "C" LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l) {
#else
_DEX_INLINE LRESULT DexExtensionProc (WPARAM w, LPARAM l) {
#endif
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}

#if defined(_DEBUG)
_DEX_INLINE extern "C" LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l) {
#else
_DEX_INLINE LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l) {
#endif
	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}

_DEX_INLINE HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen) {
	CLASSFROMIDENT CFI;
	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdent(CFI);
}

//XX	_DEX_INLINE HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew) {
//XX		if (NULL == pulIdent) return E_POINTER;
//XX		IDENTFROMCLASS IFC;
//XX		INITSTRUCT(IFC, IDENTFROMCLASS);
//XX		IFC.pcClass = pcClass;
//XX		IFC.fCreateNew = fCreateNew;
//XX		HRESULT hr = DEX_GetIdentFromClass(IFC);
//XX		if (SUCCEEDED(hr)) 
//XX			*pulIdent = IFC.ulIdent;
//XX		return hr;
//XX	}

_DEX_INLINE HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen) {
	CLASSFROMIDENT CFI;
	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdentEx(hPr, CFI);
}

_DEX_INLINE HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew) {
	if (NULL == pulIdent) return E_POINTER;

	IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

	HRESULT hr = DEX_GetIdentFromClassEx(hPr, IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}

#pragma HDR_OFF()

#endif	// _DEX_INLINE

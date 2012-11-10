#pragma HDR_ON()

#include <xtension.h>
#include <xtensnx.h>

HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen);
HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew);
HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen);
HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew);

#ifdef	_ENABLE_INLINES
#if !defined(_DEX_INLINE)
#define	_DEX_INLINE	inline
#endif
#include "ExportInl.inl"
#endif

#pragma HDR_OFF()

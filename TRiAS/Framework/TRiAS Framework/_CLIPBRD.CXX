
#include "tfrmpre.hxx"

#include "clipdef.h"
#include "clip_im.hxx"
#include "Clipbrd.hxx"

#if !defined(WIN32)
#define _DLLENTRY	__export
#endif

_DLLENTRY CClipboard :: CClipboard (void)
{
	cb_imp = new CClipBoard_Imp();    
}

_DLLENTRY CClipboard :: ~CClipboard (void)
{
	delete	cb_imp;
}

void _DLLENTRY  CClipboard :: Clear (void)
{
	cb_imp->Clear();
}

long _DLLENTRY CClipboard :: GetItemSize (Format fmt)
{
	return cb_imp-> GetItemSize(fmt);
}

void _DLLENTRY CClipboard :: Insert (const char *txt)
{
	cb_imp->Insert(txt);
}


void _DLLENTRY CClipboard :: Insert (const pBitmap bitmap)
{
	cb_imp->Insert(bitmap);
}

BOOL _DLLENTRY CClipboard ::Retrieve (char * txt, int len)
{
	return cb_imp->Retrieve (txt, len);
}

BOOL _DLLENTRY CClipboard :: Retrieve (pBitmap bitmap) 
{                
	return cb_imp->Retrieve (bitmap);
}

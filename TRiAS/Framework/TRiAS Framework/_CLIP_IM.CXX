#include "tfrmpre.hxx"

#include "Clip_im.hxx"
#include "Clipbrd.hxx"

#include <string.h>

CClipBoard_Imp :: CClipBoard_Imp (void)
{
}

CClipBoard_Imp :: ~CClipBoard_Imp (void)
{
}

void CClipBoard_Imp :: Clear (void)
{
CClipBoardLock cl(dummy.Handle());

	if (cl.Locked())
		EmptyClipboard ();
}

long CClipBoard_Imp :: GetItemSize (int fmt)
{
HGLOBAL hDexClipData;
long size = 0, len=0;
BITMAP bm; 
int fmtcheck;
char *DexClipText = NULL ;

        switch (fmt) {
        case (int)CClipboard::FmtText:
                            fmtcheck = CF_TEXT;
                            break;
        case (int)CClipboard::FmtBitmap:
                            fmtcheck = CF_BITMAP;
                            break;
        default:
                            return size ;
        }
        
        if (!IsClipboardFormatAvailable ( fmtcheck))
                  return size;

CClipBoardLock cl(dummy.Handle()) ;

        if (!cl.Locked())
                  return size ;

        switch (fmt) {
        case (int)CClipboard::FmtText:
                 hDexClipData = GetClipboardData (CF_TEXT);
                 DexClipText = (char *)GlobalLock(hDexClipData);
            
                 size = strlen (DexClipText) ;
                 GlobalUnlock ( hDexClipData );
                 break ;

        case (int)CClipboard::FmtBitmap:
		{
                DisplayDC displayDC(dummy.Handle()) ;

                     	if (displayDC.Handle()) {
			MemoryDC memoryDC (displayDC.Handle());

                        	if (memoryDC.Handle()) {
                            		hDexClipData = GetClipboardData (CF_BITMAP) ;
                            		SelectObject ( memoryDC.Handle(), hDexClipData );
                            		GetObject (hDexClipData, sizeof (BITMAP), (char *) &bm) ;

	        	            	size = ((( bm.bmWidth * bm.bmBitsPixel + 15 ) >> 4 ) * 2	// # words per row
				                 * bm.bmHeight )				// by # rows
				                 * bm.bmPlanes;	// by # planes
				}
			}
                }
                break;

	default:
		break ;
        }

return size ;
}

void CClipBoard_Imp :: Insert (const char * txt)
{
        unsigned long len = strlen ( txt ) ;
        char * str ;
        HGLOBAL hGlobalMemory = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT, len + 1);

        if( !(hGlobalMemory) )
        	return ;

CClipBoardLock cl(dummy.Handle()) ;

        if (!cl.Locked() || !(str = (char *)GlobalLock (hGlobalMemory)))
        {
            GlobalFree (hGlobalMemory);
            return ;
        }

        strcpy (str, txt);
        GlobalUnlock (hGlobalMemory) ;
        SetClipboardData (CF_TEXT, hGlobalMemory);
}


void CClipBoard_Imp :: Insert (const pBitmap bitmap)
{
        HBITMAP hBitmap;
    	BITMAP bm;
        CClipBoardLock cl(dummy.Handle()) ;

        if ( !cl.Locked())
        	return;

DisplayDC displayDC (dummy.Handle()) ;

        if (displayDC.Handle()) {
        MemoryDC src(displayDC.Handle()) ;

        	if (src.Handle()) {
                	SelectObject (src.Handle(), CV_RunTime::Bitmap_hBitmap(bitmap)) ;
                	GetObject (CV_RunTime::Bitmap_hBitmap(bitmap), sizeof (BITMAP), (char *) &bm) ;
	            	if (hBitmap = CreateBitmapIndirect(&bm)) {
			MemoryDC dest(displayDC.Handle()) ;

				if (dest.Handle()) {
					SelectObject (dest.Handle(), hBitmap);
					BitBlt (dest.Handle(), 0, 0,
						bm.bmWidth, bm.bmHeight,
						src.Handle(), 0, 0,SRCCOPY);
					SetClipboardData (CF_BITMAP, hBitmap) ;
				}
			}
		}
        }
}

Bool CClipBoard_Imp :: Retrieve (char * txt, int len)
{
        HGLOBAL hDexClipData ;
        char * DexClipText = NULL ;
        CClipBoardLock cl(dummy.Handle()) ;

        if ( !cl.Locked() || !(hDexClipData = (HGLOBAL)GetClipboardData (CF_TEXT)))
            return FALSE ;

        DexClipText = (char *)GlobalLock( hDexClipData );

        if ( len == -1 )
            len = strlen (DexClipText) ;

		strncpy(txt, DexClipText, len);
        txt[len] = NULL;

        GlobalUnlock ( hDexClipData );

        return TRUE ;
}

Bool CClipBoard_Imp ::Retrieve ( pBitmap bitmap) 
{                

        HBITMAP hDexClipData = 0;
        HBITMAP hBitmap;
    	BITMAP bm;
        CClipBoardLock cl(dummy.Handle()) ;

        if ( !cl.Locked()   || !(hDexClipData = (HBITMAP)GetClipboardData (CF_BITMAP)))
            return FALSE ;

        DisplayDC displayDC(dummy.Handle()) ;

        if (!displayDC.Handle() )
            return FALSE ;

        MemoryDC src(displayDC.Handle()), dest(displayDC.Handle()) ;

        if ( !src.Handle() || !dest.Handle() ) 
            return FALSE ;

        SelectObject (src.Handle(), hDexClipData) ;
        GetObject (hDexClipData, sizeof (BITMAP), (char *) &bm) ;
        if (!(hBitmap = CreateBitmapIndirect(&bm)))
            return FALSE;

        SelectObject (dest.Handle(), hBitmap) ;
        BitBlt (dest.Handle(),0,0,bm.bmWidth, bm.bmHeight,
                src.Handle(),0,0,SRCCOPY) ;

        DeleteObject (CV_RunTime::Bitmap_hBitmap(bitmap));

        CV_RunTime::Bitmap_hBitmap(bitmap) = hBitmap ;
        CV_RunTime::Bitmap_DeviceDependency(bitmap) = TRUE;

return TRUE;
}

CClipBoardLock :: CClipBoardLock (HWND hwnd)
{
      locked = OpenClipboard (hwnd);
}

CClipBoardLock :: ~CClipBoardLock (void)
{
    	if (locked)
		CloseClipboard () ;
}

MemoryDC :: MemoryDC (HDC hDC)
{
	hmemoryDC =  CreateCompatibleDC (hDC);
}

MemoryDC :: ~MemoryDC (void)
{
    if ( hmemoryDC )
        DeleteDC(hmemoryDC);
}

DisplayDC :: DisplayDC (HWND handle)
{
    if ( handle )
    {
        hwnd = handle ;
        hDC = GetDC( hwnd);
    }
}

DisplayDC :: ~DisplayDC ()
{
    if ( hDC )
        ReleaseDC(hwnd, hDC);
}

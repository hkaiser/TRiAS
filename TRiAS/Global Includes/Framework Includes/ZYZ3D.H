/** zyz3d.h                                                             **/

#ifndef _ZYZ3D_H_
#define _ZYZ3D_H_

/* misc. control flag defines */
#define DRAW3D_IN           0x0001
#define DRAW3D_OUT          0x0002

#define DRAW3D_TOPLINE      0x0004
#define DRAW3D_BOTTOMLINE   0x0008
#define DRAW3D_LEFTLINE     0x0010
#define DRAW3D_RIGHTLINE    0x0020


/* public function prototypes */
void FAR PASCAL Draw3DFaceFrame(HDC, LPRECT, WORD);
void FAR PASCAL Draw3DRect(HDC, LPRECT, WORD, WORD);
#if defined(WIN32)
void WINAPI Draw3DLine(HDC hdc, UINT x, UINT y, UINT nLen,
                               UINT wShadowWidth, UINT wFlags);
#else
void FAR PASCAL Draw3DLine(HDC, WORD, WORD, WORD, WORD, WORD);
#endif

#endif



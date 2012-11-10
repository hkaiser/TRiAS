/** zyzgauge.h                                                           **/

#ifndef _ZYZGAUGE_H_
#define _ZYZGAUGE_H_

#if defined(__cplusplus)
extern "C" {
#endif


/* gas gauge graph control messages--class "zYzGauge" */
#define ZYZG_SETRANGE       (WM_USER + 0)
#define ZYZG_GETRANGE       (WM_USER + 1)
#define ZYZG_SETPOSITION    (WM_USER + 2)
#define ZYZG_GETPOSITION    (WM_USER + 3)
#define ZYZG_SETORIENTATION (WM_USER + 4)
#define ZYZG_GETORIENTATION (WM_USER + 5)
#define ZYZG_SETFGCOLOR     (WM_USER + 6)
#define ZYZG_GETFGCOLOR     (WM_USER + 7)
#define ZYZG_SETBKCOLOR     (WM_USER + 8)
#define ZYZG_GETBKCOLOR     (WM_USER + 9)
#define ZYZG_SETWIDTH3D     (WM_USER + 10)
#define ZYZG_GETWIDTH3D     (WM_USER + 11)
#define ZYZG_SETBEZELFACE   (WM_USER + 12)
#define ZYZG_GETBEZELFACE   (WM_USER + 13)
#define ZYZG_SETDELTAPOS    (WM_USER + 14)

/* orientations for ZYZG_WW_ORIENTATION */
#define ZYZG_ORIENT_LEFTTORIGHT     0
#define ZYZG_ORIENT_RIGHTTOLEFT     1
#define ZYZG_ORIENT_BOTTOMTOTOP     2
#define ZYZG_ORIENT_TOPTOBOTTOM     3


/* gauge styles */
#define ZYZGS_3D        0x8000L     /* control will be 3D       */
#define ZYZGS_RIGHT	0x0001L	    // rechtsbündiges Control
#define ZYZGS_CENTER	0x0002L	    // zentrierter Text
#define ZYZGS_LEFT	0x0000L	    // linksbündiger Text

// maximale TextTemplateLänge -------------------------------------------------
#define ZYZG_GAUGETEXTLEN	64

/* public function prototypes */
_TF_ENTRY32 unsigned int WINAPI GaugeBoxInit (HINSTANCE hInstance);

#if defined(__cplusplus)
}
#endif

#endif

/** EOF: zyzgauge.h **/
                                                             

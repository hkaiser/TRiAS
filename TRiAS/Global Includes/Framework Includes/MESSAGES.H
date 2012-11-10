
#ifndef MESSAGES_H
#define MESSAGES_H	1

#define WM_NULL		    0x0000
#define WM_CREATE	    0x0001
#define WM_DESTROY	    0x0002
#define WM_MOVE		    0x0003
#define WM_SIZE		    0x0005
#define WM_ACTIVATE	    0x0006
#define WM_SETFOCUS	    0x0007
#define WM_KILLFOCUS	    0x0008
#define WM_SETVISIBLE	    0x0009
#define WM_ENABLE	    0x000A
#define WM_SETREDRAW	    0x000B
#define WM_SETTEXT	    0x000C
#define WM_GETTEXT	    0x000D
#define WM_GETTEXTLENGTH    0x000E
#define WM_PAINT	    0x000F
#define WM_CLOSE	    0x0010
#define WM_QUERYENDSESSION  0x0011
#define WM_QUIT		    0x0012
#define WM_QUERYOPEN	    0x0013
#define WM_ERASEBKGND	    0x0014
#define WM_SYSCOLORCHANGE   0x0015
#define WM_ENDSESSION	    0x0016
#define WM_SHOWWINDOW	    0x0018
#define WM_CTLCOLOR	    0x0019
//#define WM_WININICHANGE	    0x001A
#define WM_DEVMODECHANGE    0x001B
#define WM_ACTIVATEAPP	    0x001C
#define WM_FONTCHANGE	    0x001D
#define WM_TIMECHANGE	    0x001E
#define WM_CANCELMODE	    0x001F
#define WM_SETCURSOR	    0x0020
#define WM_MOUSEACTIVATE    0x0021
#define WM_CHILDACTIVATE    0x0022
#define WM_QUEUESYNC        0x0023
#define WM_GETMINMAXINFO    0x0024
#define WM_PAINTICON	    0x0026
#define WM_ICONERASEBKGND   0x0027
#define WM_NEXTDLGCTL	    0x0028
#define WM_SPOOLERSTATUS    0x002A
#define WM_DRAWITEM         0x002B
#define WM_MEASUREITEM      0x002C
#define WM_DELETEITEM       0x002D
#define WM_VKEYTOITEM       0x002E
#define WM_CHARTOITEM       0x002F
#define WM_SETFONT          0x0030
#define WM_GETFONT	    0x0031


#define WM_QUERYDRAGICON    0x0037

#define WM_COMPAREITEM	    0x0039
#define WM_COMPACTING       0x0041

#define WM_NCCREATE	    0x0081
#define WM_NCDESTROY	    0x0082
#define WM_NCCALCSIZE	    0x0083
#define WM_NCHITTEST	    0x0084
#define WM_NCPAINT	    0x0085
#define WM_NCACTIVATE	    0x0086
#define WM_GETDLGCODE	    0x0087
#define WM_NCMOUSEMOVE	    0x00A0
#define WM_NCLBUTTONDOWN    0x00A1
#define WM_NCLBUTTONUP	    0x00A2
#define WM_NCLBUTTONDBLCLK  0x00A3
#define WM_NCRBUTTONDOWN    0x00A4
#define WM_NCRBUTTONUP	    0x00A5
#define WM_NCRBUTTONDBLCLK  0x00A6
#define WM_NCMBUTTONDOWN    0x00A7
#define WM_NCMBUTTONUP	    0x00A8
#define WM_NCMBUTTONDBLCLK  0x00A9

#define WM_KEYFIRST	    0x0100
#define WM_KEYDOWN	    0x0100
#define WM_KEYUP	    0x0101
#define WM_CHAR		    0x0102
#define WM_DEADCHAR	    0x0103
#define WM_SYSKEYDOWN	    0x0104
#define WM_SYSKEYUP	    0x0105
#define WM_SYSCHAR	    0x0106
#define WM_SYSDEADCHAR	    0x0107
#define WM_KEYLAST	    0x0108

#define WM_INITDIALOG	    0x0110
#define WM_COMMAND	    0x0111
#define WM_SYSCOMMAND	    0x0112
#define WM_TIMER	    0x0113
#define WM_HSCROLL	    0x0114
#define WM_VSCROLL	    0x0115
#define WM_INITMENU	    0x0116
#define WM_INITMENUPOPUP    0x0117
#define WM_MENUSELECT	    0x011F
#define WM_MENUCHAR	    0x0120
#define WM_ENTERIDLE	    0x0121


#define WM_MOUSEFIRST	    0x0200
#define WM_MOUSEMOVE	    0x0200
#define WM_LBUTTONDOWN	    0x0201
#define WM_LBUTTONUP	    0x0202
#define WM_LBUTTONDBLCLK    0x0203
#define WM_RBUTTONDOWN	    0x0204
#define WM_RBUTTONUP	    0x0205
#define WM_RBUTTONDBLCLK    0x0206
#define WM_MBUTTONDOWN	    0x0207
#define WM_MBUTTONUP	    0x0208
#define WM_MBUTTONDBLCLK    0x0209
//#define WM_MOUSELAST	    0x0209

#define WM_PARENTNOTIFY     0x0210
#define WM_MDICREATE	    0x0220
#define WM_MDIDESTROY	    0x0221
#define WM_MDIACTIVATE	    0x0222
#define WM_MDIRESTORE	    0x0223
#define WM_MDINEXT	    0x0224
#define WM_MDIMAXIMIZE	    0x0225
#define WM_MDITILE	    0x0226
#define WM_MDICASCADE	    0x0227
#define WM_MDIICONARRANGE   0x0228
#define WM_MDIGETACTIVE     0x0229
#define WM_MDISETMENU	    0x0230


#define WM_CUT		    0x0300
#define WM_COPY		    0x0301
#define WM_PASTE	    0x0302
#define WM_CLEAR	    0x0303
#define WM_UNDO		    0x0304
#define WM_RENDERFORMAT	    0x0305
#define WM_RENDERALLFORMATS 0x0306
#define WM_DESTROYCLIPBOARD 0x0307
#define WM_DRAWCLIPBOARD    0x0308
#define WM_PAINTCLIPBOARD   0x0309
#define WM_VSCROLLCLIPBOARD 0x030A
#define WM_SIZECLIPBOARD    0x030B
#define WM_ASKCBFORMATNAME  0x030C
#define WM_CHANGECBCHAIN    0x030D
#define WM_HSCROLLCLIPBOARD 0x030E
#define WM_QUERYNEWPALETTE  0x030F
#define WM_PALETTEISCHANGING 0x0310
#define WM_PALETTECHANGED   0x0311

#define WM_DDE_FIRST	    0x03E0
//#define WM_DDE_INITIATE     0x3E0
//#define WM_DDE_TERMINATE    0x3E1
//#define WM_DDE_ADVISE	    0x3E2
//#define WM_DDE_UNADVISE     0x3E3
//#define WM_DDE_ACK	    	0x3E4
//#define WM_DDE_DATA	    	0X3E5
//#define WM_DDE_REQUEST	    0x3E6
//#define WM_DDE_POKE	    	0x3E7
//#define WM_DDE_EXECUTE	    0x3E8
#define WM_DDE_LAST	    (WM_DDE_FIRST+8)


#define WM_USER		    0x0400

#define DM_GETDEFID	    (WM_USER+0)
#define DM_SETDEFID	    (WM_USER+1)
#define DC_HASDEFID	    0x534B

//#define EM_GETSEL	   (WM_USER+0)
//#define EM_SETSEL	   (WM_USER+1)
//#define EM_GETRECT	   (WM_USER+2)
//#define EM_SETRECT	   (WM_USER+3)
//#define EM_SETRECTNP	   (WM_USER+4)
#if !defined(WIN32)
#define EM_SCROLL	   (WM_USER+5)
#endif
//#define EM_LINESCROLL	   (WM_USER+6)
//#define EM_GETMODIFY	   (WM_USER+8)
//#define EM_SETMODIFY	   (WM_USER+9)
//#define EM_GETLINECOUNT    (WM_USER+10)
//#define EM_LINEINDEX	   (WM_USER+11)
//#define EM_SETHANDLE	   (WM_USER+12)
//#define EM_GETHANDLE	   (WM_USER+13)
//#define EM_GETTHUMB	   (WM_USER+14)
//#define EM_LINELENGTH	   (WM_USER+17)
//#define EM_REPLACESEL	   (WM_USER+18)
#define EM_SETFONT	   (WM_USER+19)
//#define EM_GETLINE	   (WM_USER+20)
//#define EM_LIMITTEXT	   (WM_USER+21)
//#define EM_CANUNDO	   (WM_USER+22)
//#define EM_UNDO 	   (WM_USER+23)
//#define EM_FMTLINES	   (WM_USER+24)
//#define EM_LINEFROMCHAR    (WM_USER+25)
#define EM_SETWORDBREAK    (WM_USER+26)
//#define EM_SETTABSTOPS	   (WM_USER+27)
//#define EM_SETPASSWORDCHAR (WM_USER+28)
//#define EM_EMPTYUNDOBUFFER (WM_USER+29)
//#define EM_MSGMAX          (WM_USER+30)

//#define LB_ADDSTRING	       (WM_USER+1)
//#define LB_INSERTSTRING        (WM_USER+2)
//#define LB_DELETESTRING        (WM_USER+3)
//#define LB_RESETCONTENT        (WM_USER+5)
//#define LB_SETSEL	       (WM_USER+6)
//#define LB_SETCURSEL	       (WM_USER+7)
//#define LB_GETSEL	       (WM_USER+8)
//#define LB_GETCURSEL	       (WM_USER+9)
//#define LB_GETTEXT	       (WM_USER+10)
//#define LB_GETTEXTLEN	       (WM_USER+11)
//#define LB_GETCOUNT	       (WM_USER+12)
//#define LB_SELECTSTRING        (WM_USER+13)
//#define LB_DIR		       (WM_USER+14)
//#define LB_GETTOPINDEX	       (WM_USER+15)
//#define LB_FINDSTRING	       (WM_USER+16)
//#define LB_GETSELCOUNT	       (WM_USER+17)
//#define LB_GETSELITEMS	       (WM_USER+18)
//#define LB_SETTABSTOPS         (WM_USER+19)
//#define LB_GETHORIZONTALEXTENT (WM_USER+20)
//#define LB_SETHORIZONTALEXTENT (WM_USER+21)
//#define LB_SETCOLUMNWIDTH      (WM_USER+22)
//#define LB_SETTOPINDEX	       (WM_USER+24)
//#define LB_GETITEMRECT	       (WM_USER+25)
//#define LB_GETITEMDATA         (WM_USER+26)
//#define LB_SETITEMDATA         (WM_USER+27)
//#define LB_SELITEMRANGE        (WM_USER+28)
//#define LB_MSGMAX	       (WM_USER+33)

//#define CB_GETEDITSEL	         (WM_USER+0)
//#define CB_LIMITTEXT	         (WM_USER+1)
//#define CB_SETEDITSEL	         (WM_USER+2)
//#define CB_ADDSTRING	         (WM_USER+3)
//#define CB_DELETESTRING	         (WM_USER+4)
//#define CB_DIR                   (WM_USER+5)
//#define CB_GETCOUNT	         (WM_USER+6)
//#define CB_GETCURSEL	         (WM_USER+7)
//#define CB_GETLBTEXT	         (WM_USER+8)
//#define CB_GETLBTEXTLEN	         (WM_USER+9)
//#define CB_INSERTSTRING          (WM_USER+10)
//#define CB_RESETCONTENT	         (WM_USER+11)
//#define CB_FINDSTRING	         (WM_USER+12)
//#define CB_SELECTSTRING	         (WM_USER+13)
//#define CB_SETCURSEL	         (WM_USER+14)
//#define CB_SHOWDROPDOWN          (WM_USER+15)
//#define CB_GETITEMDATA           (WM_USER+16)
//#define CB_SETITEMDATA           (WM_USER+17)
//#define CB_GETDROPPEDCONTROLRECT (WM_USER+18)
//#define CB_GETDROPPEDSTATE       (WM_USER+23)
//#define CB_MSGMAX                (WM_USER+32)

#define WM_CVHELP 				 0xBFFF
#endif

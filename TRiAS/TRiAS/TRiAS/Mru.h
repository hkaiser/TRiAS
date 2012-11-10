//*************************************************************
//  File name: mru.h
//
//  Description:
//
//      Header for MRU support
//
//  Development Team:
//
//      Gilles Vollant (100144.2636@compuserve.com) 
//
//*************************************************************

#if !defined(_MRU_H)
#define _MRU_H

#define NBMRUMENUSHOW   4       // Default number of MRU showed in the menu File
#define NBMRUMENU       9       // Default number of MRU stored
#define IDMRU           8000    // Default First ID of MRU
#ifdef  OFS_MAXPATHNAME
#define MAXSIZEMRUITEM  OFS_MAXPATHNAME
#else
#define MAXSIZEMRUITEM  _MAX_PATH     // Default max size of an entry
#endif

typedef struct tagMRUMENU {
	WORD wNbItemFill;
	WORD wNbLruShow;
	WORD wNbLruMenu;
	WORD wMaxSizeLruItem;
	WORD wIdMru;
	LPSTR lpMRU;
	bool *lpfRO;
	bool fEmpty;
} MRUMENU;

typedef MRUMENU FAR * LPMRUMENU;

#ifdef __cplusplus
LPMRUMENU       CreateMruMenu  (WORD wNbLruShowInit = NBMRUMENUSHOW,
                                WORD wNbLruMenuInit = NBMRUMENU,
                                WORD wMaxSizeLruItemInit = MAXSIZEMRUITEM,
                                WORD wIdMruInit = IDMRU);
#else
LPMRUMENU       CreateMruMenu  (WORD wNbLruShowInit,
                                WORD wNbLruMenuInit,
                                WORD wMaxSizeLruItemInit,
                                WORD wIdMruInit);
#endif

LPMRUMENU       CreateMruMenuDefault();
void            DeleteMruMenu  (LPMRUMENU lpMruMenu);  

void            SetNbLruShow   (LPMRUMENU lpMruMenu,WORD wNbLruShowInit);
BOOL            SetMenuItem    (LPMRUMENU lpMruMenu,WORD wItem,LPCSTR lpItem, BOOL fRO);
BOOL            GetMenuItem    (LPMRUMENU lpMruMenu,WORD wItem,
                                BOOL fIDMBased,string &rStr, BOOL &rfRO);
BOOL            DelMenuItem    (LPMRUMENU lpMruMenu,WORD wItem,BOOL fIDMBased);
void            AddNewItem     (LPMRUMENU lpMruMenu,LPCSTR lpItem, BOOL);
void            PlaceMenuMRUItem(LPMRUMENU lpMruMenu,HMENU hMenu,UINT uiItem);
void			RemoveMenuMRUItem (LPMRUMENU lpMruMenu, HMENU hMenu);

BOOL            SaveMruInIni   (LPMRUMENU lpMruMenu,LPCSTR lpszSection,LPCSTR lpszFile);
BOOL            LoadMruInIni   (LPMRUMENU lpMruMenu,LPCSTR lpszSection,LPCSTR lpszFile);

#if !defined(WIN16)
BOOL            SaveMruInReg   (LPMRUMENU lpMruMenu,LPCSTR lpszKey);
BOOL            LoadMruInReg   (LPMRUMENU lpMruMenu,LPCSTR lpszKey);
#endif


//////////////////////////////////////////////////////////////

#endif // _MRU_H

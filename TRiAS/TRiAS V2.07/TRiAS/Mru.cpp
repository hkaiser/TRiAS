//*************************************************************
//  File name: mru.c
//
//  Description:
//
//      Routines for MRU support
//
//  Development Team:
//
//      Gilles Vollant (100144.2636@compuserve.com) 
//
//*************************************************************

#include "triaspre.hxx"
#include "triasres.h"
#include "mru.h"

// CreateMruMenu  : MRUMENU constructor
// wNbLruShowInit : nb of item showed in menu
// wNbLruMenuInit : nb of item stored in memory
// wMaxSizeLruItemInit : size max. of filename


//*************************************************************
//
//  CreateMruMenu()
//
//  Purpose:
//
//              Allocate and Initialize an MRU and return a pointer on it
//
//
//  Parameters:
//
//      WORD wNbLruShowInit -      Maximum number of item displayed on menu
//      WORD wNbLruMenuInit -      Maximum number of item stored in memory
//      WORD wMaxSizeLruItemInit - Maximum size of an item (ie size of pathname)
//      WORD wIdMruInit -          ID of the first item in the menu (default:IDMRU)
//
//
//  Return: (LPMRUMENU)
//
//      Pointer on a MRUMENU structure, used by other function
//
//
//  Comments:
//      wNbLruShowInit <= wNbLruMenuInit
//
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************

LPMRUMENU CreateMruMenu (WORD wNbLruShowInit,
            WORD wNbLruMenuInit,WORD wMaxSizeLruItemInit,WORD wIdMruInit)
{
LPMRUMENU lpMruMenu = new MRUMENU;

	lpMruMenu->wNbItemFill = 0;                   
	lpMruMenu->wNbLruMenu = wNbLruMenuInit;             
	lpMruMenu->wNbLruShow = wNbLruShowInit;
	lpMruMenu->wIdMru = wIdMruInit;
	lpMruMenu->wMaxSizeLruItem = wMaxSizeLruItemInit;
	lpMruMenu->lpMRU = new char [lpMruMenu->wNbLruMenu*(UINT)lpMruMenu->wMaxSizeLruItem];
	if (lpMruMenu->lpMRU == NULL) {
		delete lpMruMenu;
		lpMruMenu =  NULL;
		return NULL;
	}

// RO-Flags
	lpMruMenu->lpfRO = new bool [lpMruMenu->wNbLruMenu];
	if (NULL == lpMruMenu->lpfRO) {
		delete lpMruMenu;
		lpMruMenu =  NULL;
	}
	lpMruMenu->fEmpty = true;		// noch nicht eingelesen

return lpMruMenu;
}

//*************************************************************
//
//  CreateMruMenuDefault()
//
//  Purpose:
//
//              Allocate and Initialize an MRU and return a pointer on it
//              Use default parameter
//
//
//  Parameters:
//
//
//  Return: (LPMRUMENU)
//
//      Pointer on a MRUMENU structure, used by other function
//
//
//  Comments:
//
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************

LPMRUMENU CreateMruMenuDefault()
{
	return CreateMruMenu (NBMRUMENUSHOW,NBMRUMENU,MAXSIZEMRUITEM,IDMRU);
}


//*************************************************************
//
//  DeleteMruMenu()
//
//  Purpose:
//              Destructor :
//              Clean and free a MRUMENU structure
//
//  Parameters:
//
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU, allocated
//             by CreateMruMenu() or CreateMruMenuDefault()
//
//
//  Return: void
//
//
//  Comments:
//
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
void DeleteMruMenu(LPMRUMENU lpMruMenu)
{
	if (lpMruMenu == NULL) return;
	
// RO-Flags
	if (lpMruMenu->lpfRO) 
		delete lpMruMenu->lpfRO;

	if (lpMruMenu->lpMRU)
		delete lpMruMenu->lpMRU;
	if (lpMruMenu)
		delete lpMruMenu;
}

//*************************************************************
//
//  SetNbLruShow()
//
//  Purpose:
//              Change the maximum number of item displayed on menu
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      WORD wNbLruShowInit -      Maximum number of item displayed on menu
//
//
//  Return: void
//
//
//  Comments:
//
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
void SetNbLruShow (LPMRUMENU lpMruMenu,WORD wNbLruShowInit)
{
	lpMruMenu->wNbLruShow = min(wNbLruShowInit,lpMruMenu->wNbLruMenu);
}

//*************************************************************
//
//  SetMenuItem()
//
//  Purpose:
//              Set the filename of an item 
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      WORD wItem -               Number of Item to set, zero based
//      LPSTR lpItem -             String, contain the filename of the item
//
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      used when load .INI or reg database
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool SetMenuItem (LPMRUMENU lpMruMenu, WORD wItem, LPSTR lpItem, bool fRO)
{                                      
	if (wItem >= NBMRUMENU) 
		return false;
	strncpy((lpMruMenu->lpMRU) + 
		((lpMruMenu->wMaxSizeLruItem) * (UINT)wItem),
		lpItem, lpMruMenu->wMaxSizeLruItem-1);
	lpMruMenu->lpfRO[wItem] = fRO;

	lpMruMenu->wNbItemFill = (int)max((int)lpMruMenu->wNbItemFill,(int)wItem+1);

return true;
}

//*************************************************************
//
//  GetMenuItem()
//
//  Purpose:
//              Get the filename of an item 
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      WORD wItem -               Number of Item to set, zero based
//      bool fIDMBased -           true :  wItem is based on ID menu item
//                                 false : wItem is zero-based
//      LPSTR lpItem -             String where the filename of the item will be
//                                   stored by GetMenuItem()
//      UINT  uiSize -             Size of the lpItem buffer
//
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      Used for saving in .INI or reg database, or when user select
//        an MRU in File menu
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool GetMenuItem (LPMRUMENU lpMruMenu, WORD wItem, bool fIDMBased, string &rStr, bool &rfRO)
{
	if (fIDMBased) 
		wItem -= (lpMruMenu->wIdMru + 1);

	if (wItem >= lpMruMenu->wNbItemFill) 
		return false;

	rStr = (char *)((lpMruMenu->lpMRU) + ((lpMruMenu->wMaxSizeLruItem) * (UINT)(wItem)));
	rfRO = lpMruMenu->lpfRO[wItem];

return true;
}

//*************************************************************
//
//  AddNewItem()
//
//  Purpose:
//              Add an item at the begin of the list
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      LPSTR lpItem -             String contain the filename to add
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      Used when used open a file (using File Open common
//        dialog, Drag and drop or MRU)
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
inline WORD tmin (WORD p1, WORD p2)
{
	return p1 < p2 ? p1 : p2;
}

void AddNewItem (LPMRUMENU lpMruMenu, LPCSTR lpItem, bool fRO)
{
WORD i, j;

	for (i = 0; i < lpMruMenu->wNbItemFill; i++) {
		if (strcmpi(lpItem, (lpMruMenu->lpMRU) + 
		    ((lpMruMenu->wMaxSizeLruItem) * (UINT)i)) == 0)
		{         
        // Shift the other items
			for (j = i; j > 0; j--) {
				strcpy ((lpMruMenu->lpMRU) + (lpMruMenu->wMaxSizeLruItem * (UINT)j),
						(lpMruMenu->lpMRU) + (lpMruMenu->wMaxSizeLruItem * (UINT)(j-1)));
				lpMruMenu->lpfRO[j] = lpMruMenu->lpfRO[j-1];
			}
			strncpy(lpMruMenu->lpMRU, lpItem, lpMruMenu->wMaxSizeLruItem-1);
			lpMruMenu->lpfRO[0] = fRO;
			return;
		}
	}

	lpMruMenu->wNbItemFill = tmin(lpMruMenu->wNbItemFill+1,lpMruMenu->wNbLruMenu);

	for (i = lpMruMenu->wNbItemFill-1; i > 0; i--) {
		strcpy (lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem * (UINT)i),
			lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem * (UINT)(i-1)));
		lpMruMenu->lpfRO[i] = lpMruMenu->lpfRO[i-1];
	}
	strncpy(lpMruMenu->lpMRU,lpItem,lpMruMenu->wMaxSizeLruItem-1);  
	lpMruMenu->lpfRO[0] = fRO;
}

//*************************************************************
//
//  DelMenuItem()
//
//  Purpose:
//              Delete an item
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      WORD wItem -               Number of Item to set, zero based
//      bool fIDMBased -           true :  wItem is based on ID menu item
//                                 false : wItem is zero-based
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      Used when used open a file, using MRU, and when an error
//         occured (by example, when file was deleted)
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool DelMenuItem(LPMRUMENU lpMruMenu,WORD wItem,bool fIDMBased)
{ 
WORD i;

	if (fIDMBased) 
		wItem -= (lpMruMenu->wIdMru + 1);
	if (lpMruMenu->wNbItemFill <= wItem) 
		return false;

	lpMruMenu->wNbItemFill--;
	for (i = wItem; i < lpMruMenu->wNbItemFill; i++) {
		strcpy (lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem * (UINT)i),
			lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem * (UINT)(i+1)));
		lpMruMenu->lpfRO[i] = lpMruMenu->lpfRO[i+1];
	}
	*(lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem * (UINT)i)) = '\0';

return true;
}
                           
//*************************************************************
//
//  PlaceMenuMRUItem()
//
//  Purpose:
//              Add MRU at the end of a menu
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      HMENU hMenu -              Handle of menu where MRU must be added
//      UINT uiItem -              Item of menu entry where MRU must be added
//
//  Return: void
//
//
//  Comments:
//      Used MRU is modified, for refresh the File menu
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
void PlaceMenuMRUItem (LPMRUMENU lpMruMenu, HMENU hMenu, UINT uiItem)
{
int  i;   
WORD wNbShow;

	if (hMenu == NULL) return;

// "Liste ..." entfernen
	RemoveMenu (hMenu, lpMruMenu->wIdMru-1, MF_BYCOMMAND);

// remove old MRU in menu
	for (i = 0; i <= (int)(lpMruMenu->wNbLruMenu); i++)
		RemoveMenu (hMenu, i+lpMruMenu->wIdMru, MF_BYCOMMAND);

// If they are item, insert a separator before the files
	InsertMenu (hMenu,uiItem,MF_SEPARATOR,lpMruMenu->wIdMru,NULL);
  
	if (lpMruMenu->wNbItemFill == 0) {
	ResString resMRU (IDS_EMPTYMRU, 32);

		InsertMenu (hMenu, lpMruMenu->wIdMru, MF_STRING|MF_GRAYED, 
				    lpMruMenu->wIdMru-1, resMRU);
	} else {
		wNbShow = min(lpMruMenu->wNbItemFill,lpMruMenu->wNbLruShow);
		for (i = (int)wNbShow-1; i >= 0; i--) {
		LPSTR lpTxt = new char [lpMruMenu->wMaxSizeLruItem + 20];
			
			if (lpTxt) {
				wsprintf (lpTxt,"&%lu %s",
							(DWORD)(i+1), 
							lpMruMenu->lpMRU + (lpMruMenu->wMaxSizeLruItem*(UINT)i));
				InsertMenu (hMenu,(((WORD)i) != (wNbShow-1)) ? (lpMruMenu->wIdMru+i+2) : lpMruMenu->wIdMru,
						MF_STRING, lpMruMenu->wIdMru+i+1,lpTxt);   
				delete lpTxt;
			}
		}
	}
}




//*************************************************************
//
//  SaveMruInIni()
//
//  Purpose:
//              Save MRU in a private .INI
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      LPSTR lpszSection  -       Points to a null-terminated string containing
//                                      the name of the section 
//      LPSTR lpszFile -           Points to a null-terminated string that names 
//                                      the initialization file. 
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      See WritePrivateProfileString API for more info on lpszSection and lpszFile
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool SaveMruInIni(LPMRUMENU lpMruMenu, LPCSTR lpszSection, LPCSTR lpszFile)
{
	for (WORD i = 0; i < lpMruMenu->wNbLruMenu; i++) {
	char szEntry[16];                         

		wsprintf (szEntry,"File%lu", (DWORD)i+1);

	string str;
	bool fRO = false;

		if (GetMenuItem(lpMruMenu,i,false,str,fRO)) {
			str += fRO ? ",1" : ",0";
			WritePrivateProfileString(lpszSection,szEntry,str.c_str(),lpszFile);
		} else
			WritePrivateProfileString(lpszSection,szEntry,NULL,lpszFile);
	}

	WritePrivateProfileString(NULL,NULL,NULL,lpszFile); // flush cache 

	lpMruMenu -> fEmpty = true;		// nicht mehr dirty

return true;
}


//*************************************************************
//
//  LoadMruInIni()
//
//  Purpose:
//              Load MRU from a private .INI
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      LPSTR lpszSection  -       Points to a null-terminated string containing
//                                      the name of the section 
//      LPSTR lpszFile -           Points to a null-terminated string that names 
//                                      the initialization file. 
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      See GetPrivateProfileString API for more info on lpszSection and lpszFile
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool LoadMruInIni(LPMRUMENU lpMruMenu,LPCSTR lpszSection,LPCSTR lpszFile)
{
	if (!lpMruMenu -> fEmpty) return true;	// nur einmal einlesen

LPSTR lpTxt;

	lpTxt = new char [lpMruMenu->wMaxSizeLruItem + 20];
	if (lpTxt == NULL) return false;

	for (WORD i = 0; i< lpMruMenu->wNbLruMenu; i++) {
	char szEntry[16];
      
		wsprintf(szEntry, "File%lu", (DWORD)i+1);
		GetPrivateProfileString(lpszSection,szEntry,"",lpTxt,
				lpMruMenu->wMaxSizeLruItem + 10,lpszFile);
		if (*lpTxt == '\0')
			break;

	char *pT = strchr (lpTxt, ',');

		if (pT) *pT = '\0';		// fRO abkoppeln

	bool fRO = pT ? ('0' == *(pT+1) ? false : true) : false;

		SetMenuItem (lpMruMenu, i, lpTxt, fRO);
	}
	delete lpTxt;

	lpMruMenu -> fEmpty = false;

return true;
}

#ifdef WIN32

//*************************************************************
//
//  SaveMruInReg()
//
//  Purpose:
//              Save MRU in the registry
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      LPSTR lpszKey  -           Points to a null-terminated string 
//                                      specifying  the name of a key that 
//                                      this function opens or creates.
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      Win32 function designed for Windows NT and Windows 95
//      See RegCreateKeyEx API for more info on lpszKey
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool SaveMruInReg (LPMRUMENU lpMruMenu, LPCSTR lpszKey)
{
HKEY hCurKey;
DWORD dwDisp;

	RegCreateKeyEx (HKEY_CURRENT_USER, lpszKey, 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
			NULL, &hCurKey, &dwDisp);

	for (WORD i = 0; i < lpMruMenu->wNbLruMenu; i++) {
	char szEntry[16];
	bool fRO;
	string str;

		wsprintf(szEntry, "File%lu", (DWORD)i+1);
		if (!GetMenuItem(lpMruMenu,i,false,str,fRO) || 0 == str.length()) {
			RegDeleteValue (hCurKey, szEntry);
//			break;
		} else {
			str += fRO ? ",1" : ",0";
			RegSetValueEx (hCurKey, szEntry, 0, REG_SZ, (const BYTE *)str.c_str(), str.length());
		}
	}
	RegCloseKey(hCurKey);

	lpMruMenu -> fEmpty = true;		// nicht mehr dirty
	
return true;
}

//*************************************************************
//
//  LoadMruInReg()
//
//  Purpose:
//              Load MRU from the registry
//
//  Parameters:
//      LPMRUMENU lpMruMenu -      pointer on MRUMENU
//      LPSTR lpszKey  -           Points to a null-terminated string 
//                                      specifying  the name of a key that 
//                                      this function opens or creates.
//
//  Return: (bool)
//      true  - Function run successfully
//      false - Function don't run successfully
//
//
//  Comments:
//      Win32 function designed for Windows NT and Windows 95
//      See RegOpenKeyEx API for more info on lpszKey
//
//  History:    Date       Author       Comment
//              09/24/94   G. Vollant   Created
//
//*************************************************************
bool LoadMruInReg(LPMRUMENU lpMruMenu,LPCSTR lpszKey)
{
	if (!lpMruMenu -> fEmpty) return true;	// nur einmal einlesen

LPSTR lpTxt;
WORD i;
HKEY hCurKey;
DWORD dwType;

	lpTxt = new char [lpMruMenu->wMaxSizeLruItem + 20];
	if (lpTxt == NULL) return false;

	RegOpenKeyEx (HKEY_CURRENT_USER, lpszKey, 0, KEY_READ, &hCurKey);

	for (i = 0; i < lpMruMenu->wNbLruMenu; i++) {
	char szEntry[16];
	DWORD dwSizeBuf;  

		wsprintf(szEntry, "File%lu", (DWORD)i+1);
		*lpTxt = '\0';
		dwSizeBuf = lpMruMenu->wMaxSizeLruItem + 10;
		RegQueryValueEx (hCurKey, szEntry, NULL, &dwType, (LPBYTE)lpTxt, &dwSizeBuf);
		*(lpTxt+dwSizeBuf) = '\0';
		if (*lpTxt == '\0')
			break;

	char *pT = strchr (lpTxt, ',');

		if (pT) *pT = '\0';

	bool fRO = pT ? ('0' == *(pT+1) ? false : true) : false;

		SetMenuItem(lpMruMenu,i,lpTxt, fRO);
	}
	RegCloseKey(hCurKey);
	delete lpTxt;

	lpMruMenu -> fEmpty = false;

return true;
}

#endif

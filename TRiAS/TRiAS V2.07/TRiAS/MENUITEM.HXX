// Liste der von Erweiterungen geladenen MenuItems ----------------------------
// File: MENUITEM.HXX

#if !defined(_MENUITEM_HXX)
#define _MENUITEM_HXX

// dieser Baum enthält alle Menuerweiterungen der ORFenster
class MenuItem {
public:
	char *_pMenuText;	// anzuzeigender MenuText
	HDEX _hDex;		// zuständige Erweiterung
	short _iMenuID;		// MenuItem (Key)
	short _iPopup;		// Nummer des PopupMenu 

		MenuItem (char *pText, HDEX hDex, short ID, short iNum);
		~MenuItem (void);
};

class MenuItemList : public CListContainer {
protected:
	void UserDelete (void *pObj);

public:
		MenuItemList (void);
		~MenuItemList (void);

	bool RemoveMenuItem (short);
};
DeclareLock (MenuItemList, MenuItem);

#endif // _MENUITEM_HXX

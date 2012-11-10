// SetMenuBitmaps 
// versorgt ein Menu mit den zugehörigen Bitmaps

#include "Pheader.h"
#include "MenuBitmapper.h"
#include "odbcext.h"

CBitmap bmpUndo;
CBitmap bmpRedo;
CBitmap bmpCopy;
CBitmap bmpCut;
CBitmap bmpClear;
CBitmap bmpPaste;
CBitmap bmpSortAsc;
CBitmap bmpSortDesc;

class CFlag
{
protected:
	bool bFlag;
public:
	CFlag(){ Reset();};
	void Set(){bFlag = true;};
	void Reset(){bFlag = false;};
	bool IsSet(){return bFlag;};
};

void InitBitmaps()
{
	static CFlag flag;
	if (flag.IsSet())
		return;

	VERIFY(bmpUndo.LoadBitmap(IDB_UNDO));
	VERIFY(bmpRedo.LoadBitmap(IDB_REDO));
	VERIFY(bmpCopy.LoadBitmap(IDB_COPY));
	VERIFY(bmpCut.LoadBitmap(IDB_CUT));
	VERIFY(bmpClear.LoadBitmap(IDB_CLEAR));
	VERIFY(bmpPaste.LoadBitmap(IDB_PASTE));
	VERIFY(bmpSortAsc.LoadBitmap(IDB_SORTASC));
	VERIFY(bmpSortDesc.LoadBitmap(IDB_SORTDESC));

	flag.Set();
}


void SetMenuBitmaps(CMenu* pMenu)
{
	ASSERT(pMenu);
	if (NULL == pMenu)
		return;

	InitBitmaps();	

	UINT count = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < count; i++)
	{
		CBitmap* pBmp = NULL;

		switch (pMenu->GetMenuItemID(i))
		{
			case ID_EDIT_COPY	:	pBmp = &bmpCopy;
							break;	
			case ID_EDIT_UNDO	:	pBmp = &bmpUndo;
							break;	
			case ID_EDIT_REDO	:	pBmp = &bmpRedo;
							break;	
			case ID_EDIT_CUT	:	pBmp = &bmpCut;
							break;	
			case ID_EDIT_PASTE	:	pBmp = &bmpPaste;
							break;	
			case ID_EDIT_CLEAR	:	pBmp = &bmpClear;
							break;	
			case IDD_ASC		:	pBmp = &bmpSortAsc;
							break;	
			case IDD_DESC		:	pBmp = &bmpSortDesc;
							break;	
		}

		// kein relevanter CommandID
		if (NULL == pBmp)
			continue;
		
		VERIFY(pMenu->SetMenuItemBitmaps(i, MF_BYPOSITION | MF_OWNERDRAW,
					pBmp, pBmp));
	}
}
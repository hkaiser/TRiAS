#include "bscriptp.hxx"
#include "bscript.h"

#include "macrguid.h"                  
#include "imacorg.h"
#include "imacro.h"

#include "custdlg.h"

#include <ospace/std/string>
#include <ospace/source.h>

#include "myenum.h"

#include "listitem.h"
#include "commsi.h"
#include "procimp.h"
#include "analimp.h"
#include "anpasimp.h"
#include "saveimp.h"

#include "macroorg.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANPASSENINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpIAnpassen* CImpIAnpassen :: Create(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)
{
	if (pUnkOuter == NULL)
		return NULL;

	CImpIAnpassen* pIAnpassen = new CImpIAnpassen(pUnkOuter, pMacroOrg);
	if (NULL == pIAnpassen)	return NULL;		

	HRESULT hr = pIAnpassen -> FInit(); 
	if (FAILED(hr)) {
		delete pIAnpassen;
		return NULL;
	}

return  pIAnpassen;
}
		
CImpIAnpassen :: CImpIAnpassen(	LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg)// = 10110
{
	m_cRef=0;

	m_pUnkOuter = pUnkOuter;
	m_pMacroOrg = pMacroOrg;
	
	m_uiNewID = GetOffset()+10;
}

CImpIAnpassen :: ~CImpIAnpassen()
{                
}                                                     

HRESULT CImpIAnpassen :: FInit()
{
return NOERROR;	
}                                         

LPIMPICOMMANDS CImpIAnpassen :: GetCommands(void)
{
return m_pMacroOrg -> GetCommands();
}

UINT CImpIAnpassen :: GetOffset(void) 
{ 
return m_pMacroOrg -> GetOffset();
}

bool CImpIAnpassen :: CutAcc (char *pc, CString &str)
{
short i=0;
char pc2[MAXSTRLENGTH];

	while(*pc != '\0' && *pc != '\t') {	
		if(*pc != '&') { pc2[i] = *pc ; i++; }
		pc++;		
	}

	pc2[i] = '\0';
	str = pc2;

return true;
}

HRESULT CImpIAnpassen :: AddString (CTreeCtrl *pTCtrl, 
									LPSTR pc, 
									UINT uiID,
									HTREEITEM hParentTreeItem,
									HTREEITEM *phTreeItem)
{
TV_INSERTSTRUCT InsertStruct;
	InsertStruct.hParent = hParentTreeItem;
	InsertStruct.hInsertAfter = TVI_LAST;	

TV_ITEM   item;
	item.mask = TVIF_TEXT ;

CString str = pc;
	CutAcc(pc, str);

	item.pszText = (char *)(LPCTSTR)str;
	item.cchTextMax = str.GetLength();

	InsertStruct.item = item;

*phTreeItem = NULL;
	*phTreeItem = pTCtrl -> InsertItem (&InsertStruct);
	if (*phTreeItem == NULL) return ResultFromScode(E_FAIL);

ITEMDATA *pID = new ITEMDATA;
	pID -> flags = CUSTFLAGS_INIT;
	pID -> strMacroText = " ";
	pID -> uiID = uiID;
	if ( ! pTCtrl -> SetItemData(*phTreeItem, (DWORD)pID) )
		return ResultFromScode(E_FAIL);

return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
HRESULT CImpIAnpassen :: GetListItems(IEnum<WListElement> *pIEnum,
									  CTreeCtrl *pTCtrl,
									  HTREEITEM hTreeItem)
{
	ASSERT (pIEnum);

HRESULT hr = NOERROR;
		
	do {
	
	IListElement *pILE;	
	char  c[MAXSTRLENGTH];
	UINT uiID = 0;
		hr = GetNextListElement (&pILE, pIEnum, c, uiID);  
		if (FAILED(hr)) return hr;
		if (GetScode(hr) == S_FALSE) continue;

		HTREEITEM hNewTreeItem;	
		HRESULT hr = AddString (pTCtrl, c, uiID, hTreeItem , &hNewTreeItem); 
			if (FAILED(hr)) return hr;
  
		if(uiID >= MIN_DROPDOWNID) {

		IEnum<WListElement> *pIEnum_Down = NULL;
			hr = pILE -> GetEnum(&pIEnum_Down);
			if (FAILED(hr)) return hr; 

			hr = GetListItems(pIEnum_Down, pTCtrl, hNewTreeItem);
			pIEnum_Down -> Release();
			if (FAILED(hr)) return hr;
		}
  
	} while (GetScode(hr) == S_OK);

return NOERROR;
}


HRESULT CImpIAnpassen :: Fill(	LPCTSTR pcMacroName, 
								const CString& strNewMenuEntry,
								UINT uiID, 
								IListElement *pILstEl_ListItem_Up,
								IListElement *pILE_After,
								bool fMacro)
{
LPIMPICOMMANDS pICs = GetCommands();
	if (NULL == pICs) return ResultFromScode(E_FAIL);

LPCTSTR pcEntry = strNewMenuEntry;
HRESULT hr2 = pICs -> InsertCommand (pcMacroName, uiID, fMacro);
	if (SUCCEEDED(hr2)) {
	
		hr2 = pICs -> InsertMenuItem(pcEntry, uiID, pILstEl_ListItem_Up, pILE_After);
		pICs -> Release();
		if (FAILED(hr2)) return hr2;
	} 
	else {
		pICs -> Release();
		return hr2;
	}

return NOERROR;
}

HRESULT CImpIAnpassen :: SetNewItemInLists (
							UINT uiOldID,
							UINT uiCmpID,
							UINT &uiNewID,
							short i,
							const CString& strNewMenuEntry,
							const CString& strNew,
							IListElement *pILstEl_ListItem_Up,
							IListElement *pILE_After,
							bool fMacro)
{
	if (uiCmpID != uiOldID) return ResultFromScode(S_FALSE);

LPCTSTR pc = strNew;
HRESULT hr = Fill(	pc, strNewMenuEntry, m_uiNewID, 
					pILstEl_ListItem_Up, pILE_After, fMacro);

	if (FAILED(hr)) return hr;
	
HMENU hMenu = NULL;
	pILstEl_ListItem_Up -> GetMenu(&hMenu);

	hr = InsertMenu(hMenu, 
					(pILE_After>0) ? i:i+1, 
					MF_BYPOSITION, m_uiNewID, 
					strNewMenuEntry);					
	if (FAILED(hr)) return hr;
	
	uiNewID = m_uiNewID; 
	m_uiNewID++;

return ResultFromScode(S_OK);
}

void  CImpIAnpassen :: IDTest (IListElement **ppILE, 
								UINT uiPreID,
								UINT uiSucID,
								UINT &uiID)
{								
	if (uiSucID > 0) uiID = uiSucID;
	else if (uiPreID > 0)	{
		uiID = uiPreID;
		// kein Nachfolger, an das Ende der Liste setzen 
		*ppILE = NULL;
	}
	else ASSERT(uiPreID);
}

/////////////////////////////////////////////////////////////////////////////
// für NewMenu()
HRESULT CImpIAnpassen :: SetNewItemInLists (	IEnum<WListElement> *pIEnum,
												UINT uiPreID, 
												UINT uiSucID, 
												UINT &uiNewID,
												const CString& strNew,
												const CString& strNewMenuEntry,
												IListElement *pILstEl_ListItem_Up,
												bool fMacro)
{
	ASSERT (pIEnum);

HRESULT hr = NOERROR;
short i = 0;
		
	do {
	
	IListElement *pILE;	
	char  cOld[MAXSTRLENGTH];
	UINT uiOldID = 0;
		hr = GetNextListElement (&pILE, pIEnum, cOld, uiOldID);  
		if (FAILED(hr)) return hr;
		if (GetScode(hr) == S_FALSE) continue;

	HRESULT hr2 = SetNewItemInLists (	uiOldID, 
										(uiSucID > 0) ? uiSucID : uiPreID, 
										uiNewID,
										i,  
										strNewMenuEntry, strNew,
										pILstEl_ListItem_Up, 
										(uiSucID > 0) ? pILE : NULL, 
										fMacro);
		if (FAILED(hr2) || GetScode(hr2) == S_OK) return hr2;

		if(uiOldID >= MIN_DROPDOWNID) {
			
		IEnum<WListElement> * pIEnum_Down = NULL;
		HRESULT hr1 = pILE -> GetEnum(&pIEnum_Down);
			if (FAILED(hr1)) return hr1; 

			hr1 = SetNewItemInLists (	pIEnum_Down, uiPreID, uiSucID, uiNewID,
										strNew, strNewMenuEntry, pILE, fMacro);
			pIEnum_Down -> Release();			
			if (FAILED(hr1) || GetScode(hr1) == S_OK) return hr1;
		}

		i++;

	} while (GetScode(hr) == S_OK);

return hr;
}


HRESULT CImpIAnpassen :: SetNewMenuEntry(	UINT uiID,
											UINT uiCmpID,
											const CString& strNew,
											IListElement *pILE,
											IListElement *pILstEl_ListItem_Up )
{
	if (uiCmpID != uiID) return ResultFromScode(S_FALSE);
	
HMENU hMenu = NULL;
	pILstEl_ListItem_Up -> GetMenu(&hMenu);
	if ( ! ::ModifyMenu(hMenu, uiID, MF_BYCOMMAND | MF_STRING, uiID, strNew) )
		return ResultFromScode(E_FAIL); 

LPCSTR pcStr = strNew;
	pILE -> Insert (pcStr, uiID);

return ResultFromScode(S_OK);
}

HRESULT CImpIAnpassen :: SetNewMenuEntry(	IEnum<WListElement> *pIEnum,
											UINT uiID, 
											const CString& strNew,
											IListElement *pILstEl_ListItem_Up)
{
	ASSERT (pIEnum);
	ASSERT (uiID);
	ASSERT (!strNew.IsEmpty());

HRESULT hr = NOERROR;
		
	do {
	
	IListElement *pILE;	
	char  c[MAXSTRLENGTH];
	UINT uiCmpID = 0;
		hr = GetNextListElement (&pILE, pIEnum, c, uiCmpID);  
		if (FAILED(hr)) return hr;
		if (GetScode(hr) == S_FALSE) continue;

// nach OLD suchen und NEW dafür setzen
	HRESULT hr2 = SetNewMenuEntry(	uiID, uiCmpID, strNew, 
									pILE, pILstEl_ListItem_Up);
		if (FAILED(hr2) || GetScode(hr2) == S_OK) return hr2;
			
		if(uiCmpID >= MIN_DROPDOWNID) {
			
		IEnum<WListElement> * pIEnum_Down = NULL;
		HRESULT hr1 = pILE -> GetEnum(&pIEnum_Down);
			if (FAILED(hr1)) return hr1; 

			hr1 = SetNewMenuEntry (	pIEnum_Down, uiID, strNew, pILE);
			pIEnum_Down -> Release();			
			if (FAILED(hr1) || GetScode(hr1) == S_OK) return hr1;			
		}
	} while (GetScode(hr) == S_OK);

return hr;
}

HRESULT CImpIAnpassen :: InsertMenu(	HMENU hMenu, 
									UINT uiPosition, UINT uiFlags, UINT uiID, 
									LPCTSTR pccNewItem)
{

	if ( ! ::InsertMenu (hMenu, uiPosition, uiFlags, uiID, pccNewItem) )
		return ResultFromScode(E_FAIL);
return NOERROR;
}

HRESULT CImpIAnpassen :: GetEnum(IEnum<WListElement> **ppIEnum)
{
LPIMPICOMMANDS pICs = GetCommands();
	if (NULL == pICs) return ResultFromScode (E_FAIL);

HRESULT hr = pICs -> GetEnum(ppIEnum);
	pICs -> Release();

return hr;
}

HRESULT CImpIAnpassen :: DeleteItem(UINT uiID,
									UINT uiIDDel,
									IListElement *pILE_Up,
									IListElement *pILE)
{
	if(uiID != uiIDDel) return ResultFromScode(S_FALSE);

LPIMPICOMMANDS pICs = GetCommands();
	if (NULL == pICs) return ResultFromScode (E_FAIL);

HRESULT hr = pICs -> DeleteItem(uiID, pILE_Up, pILE);
	pICs -> Release();
	if (FAILED(hr)) return hr;

return ResultFromScode(S_OK);
}

HRESULT CImpIAnpassen :: DeleteItem(IEnum<WListElement> *pIEnum, 
									UINT uiIDDel,
									IListElement *pILE_Up)
{
	ASSERT (pIEnum);

HRESULT hr = NOERROR;
		
	do {
	
	IListElement *pILE;	
	char  c[MAXSTRLENGTH];
	UINT uiID = 0;
		hr = GetNextListElement (&pILE, pIEnum, c, uiID);  
		if (FAILED(hr)) return hr;
		if (GetScode(hr) == S_FALSE) continue;

	HRESULT hr1 = DeleteItem(uiID, uiIDDel, pILE_Up, pILE);
		if(FAILED(hr1) || GetScode(hr1) == S_OK) return hr1;

		if(uiID >= MIN_DROPDOWNID) {

		IEnum<WListElement> * pIEnum_Down = NULL;
		HRESULT hr2 = pILE -> GetEnum(&pIEnum_Down);
			if (FAILED(hr)) return hr; 

			hr2 = DeleteItem (pIEnum_Down, uiIDDel, pILE);
			pIEnum_Down -> Release();
			if (FAILED(hr2) || GetScode(hr2) == S_OK) return hr2;
		}
  
	} while (GetScode(hr) == S_OK);

return hr;
}

/////////////////////////////////////////////////////////////////////////////////////
// *** IAnpassen methods

STDMETHODIMP CImpIAnpassen :: DeleteItem (UINT uiID)
{					
IEnum<WListElement> *pIEnum = NULL;	
HRESULT hr = GetEnum(&pIEnum);	
	if (FAILED(hr)) return hr;
	
	hr = DeleteItem(pIEnum, uiID, NULL);
	pIEnum -> Release();

return hr;
}
 
STDMETHODIMP CImpIAnpassen :: SetNewMenuEntry(UINT uiID, 
											  LPCSTR pNewMenuEntry)
{
IEnum<WListElement> *pIEnum = NULL;	
HRESULT hr = GetEnum(&pIEnum);	
	if (FAILED(hr)) return hr;

CString strNewMenuEntry = pNewMenuEntry;
	hr = SetNewMenuEntry (pIEnum, uiID, strNewMenuEntry, NULL);
	pIEnum -> Release();
	
return hr;
}

STDMETHODIMP CImpIAnpassen :: ReadMenu(CWnd *pTC)
{
IEnum<WListElement> *pIEnum = NULL;	
HRESULT hr = GetEnum(&pIEnum);	
	if (FAILED(hr)) return hr;
	
	hr = GetListItems (pIEnum, (CTreeCtrl *)pTC, NULL);
	pIEnum -> Release();

return hr;
}


STDMETHODIMP CImpIAnpassen :: SetNewMenu(UINT uiPreID, 
										 UINT uiSucID,
										 UINT &uiNewID,
										 LPCSTR pNew,
										 LPCSTR pNewMenuEntry,
										 bool fMacro)
{
IEnum<WListElement> *pIEnum = NULL;	
HRESULT hr = GetEnum(&pIEnum);	
	if (FAILED(hr)) return hr;

CString strNew = pNew;
CString strNewMenuEntry = pNewMenuEntry;
	hr = SetNewItemInLists (pIEnum, uiPreID, uiSucID, uiNewID, 
							strNew, strNewMenuEntry, NULL, fMacro);
	pIEnum -> Release();

return hr;
}

STDMETHODIMP CImpIAnpassen :: GetDescription (	LPSTR pc, UINT uiLen, 
												UINT ui, bool &fMacro)
{
LPIMPICOMMANDS pICs = GetCommands();
	if (NULL == pICs) return ResultFromScode(E_FAIL);

HRESULT hr  = pICs -> GetDescription (pc, uiLen, ui, fMacro);
	pICs -> Release();

return hr; 
}

STDMETHODIMP_(void) CImpIAnpassen :: GetNewMacroID (UINT *puiID) 
{ 
	ASSERT(puiID);
	ASSERT(m_uiNewID);
	*puiID = m_uiNewID; 
}
STDMETHODIMP_(void) CImpIAnpassen :: SetNewMacroID (UINT uiID) 
{ 
	ASSERT(uiID);
	m_uiNewID = uiID; 
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CImpIAnpassen :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}


STDMETHODIMP_(ULONG) CImpIAnpassen :: AddRef (void)
{
    ++m_cRef;
return m_pUnkOuter -> AddRef ();
}


STDMETHODIMP_(ULONG) CImpIAnpassen :: Release (void)
{                               
    --m_cRef;
return m_pUnkOuter -> Release ();
}


HRESULT GetNextListElement (IListElement **ppILE, 
							IEnum<WListElement> *pIEnum,
							LPSTR c, UINT &uiID)  
{
WListElement ILE;
HRESULT hr = pIEnum -> Next (1, &ILE, 0);	
	if (FAILED(hr) || GetScode(hr) == S_FALSE) return hr;

	hr = ILE -> Get (c, MAXSTRLENGTH, &uiID);
	if (FAILED(hr)) return hr; 

	*ppILE = ILE;

return hr;
}



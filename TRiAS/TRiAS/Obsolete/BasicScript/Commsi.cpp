#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <ospace/stream.h>
#include <fstream.h>
#include <ospace/std/string>
#include <ospace/source.h>
#include <ospace/com/olestrea.h>
#include <ospace/uss/std/map.h>

#include "xtsnguid.h"                  

#include <ixtnext.hxx>

#include "macrguid.h"                  

#include "imacro.h"
#include "imacorg.h"

#include "menuver.h" // Konstante zum sicheren Abspeichern der Menüstruktur

#include "myenum.h"
#include "tmplinst.h"

#include "commimp.h"
#include "myenum.h"
#include "listitem.h"
#include "commsi.h"

#pragma warning (disable: 4355)

const UINT ISLOADED	= 1;
const UINT NOTLOADED	= 0;

char g_str[_MAX_PATH+1];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMANDS-INTERFACE-IMPL.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CImpICommands* CImpICommands :: Create(LPUNKNOWN pUnkOuter, IScriptContainer *pISC)
{
	CImpICommands* pICommands = new CImpICommands(pUnkOuter, pISC);
	if (NULL == pICommands)	return NULL;		

	HRESULT hr = pICommands -> FInit(); 
	if (FAILED(hr)) {
		delete pICommands;
		return NULL;
	}

	pICommands -> AddRef();

return  pICommands;
}
		
CImpICommands :: CImpICommands(LPUNKNOWN pUnkOuter, IScriptContainer *pISC)
				: m_ListItem(), m_PersStream(this)
{
	ASSERT(pISC);

	m_cRef=0;

	m_pUnkOuter = pUnkOuter;
	m_pIScriptContainer	= pISC;
	pISC -> AddRef();

	m_uiTrashID = MIN_SEPARATORID;
	m_uiDropDownID = MIN_DROPDOWNID;

	m_iState = NOTLOADED;
}

CImpICommands :: ~CImpICommands()
{         
	m_pIScriptContainer	-> Release();
}                                                     

HRESULT CImpICommands :: FInit()
{
return NOERROR;	
}                                         

HRESULT CImpICommands :: in(os_bstream &stream)
{
	m_ListItem.ClearItem(NULL);
	m_mapCommand.erase(m_mapCommand.begin(), m_mapCommand.end());

	try {
	WAnpassen IA(m_pUnkOuter);	// throws hr
	UINT uiVer = 0, ui = 0;

		stream >> uiVer;
		
		switch (uiVer) {
		case uiMenuStructureVersion:
			stream >> m_ListItem >> m_mapCommand >> ui;
			IA -> SetNewMacroID(ui);
			break;
		default:
			return ResultFromScode(E_FAIL);
			break;
		}
		m_iState = ISLOADED;
	} catch (HRESULT hr) {
		return hr;
	}

	return S_OK;
}

HRESULT CImpICommands :: out(os_bstream &stream)
{
	try {
	WAnpassen IA(m_pUnkOuter);		// throws hr

		stream << uiMenuStructureVersion;
	
	UINT ui = 0;

		IA -> GetNewMacroID(&ui);
		stream << m_ListItem << m_mapCommand << ui;
			
		m_iState = NOTLOADED;
	
	} catch (HRESULT hr) {
		return hr;
	}

	return S_OK;
}

HRESULT CImpICommands :: file_out(LPCSTR pcName)
{
fstream file(pcName, ios::out | ios::trunc | ios::binary);
os_bstream stream(os_adapter_for(file));

return out(stream);
}

HRESULT CImpICommands :: file_in (LPCSTR pcName)
{	
	if(m_iState == ISLOADED) return NOERROR;

fstream file(pcName, ios::in | ios::binary | ios::nocreate);
	if(file.fail()) return ResultFromScode(S_FALSE);

os_bstream stream(os_adapter_for(file));

return in(stream);
}

HRESULT CImpICommands :: storage_out(LPSTREAM pIStream)
{
olestream OLE_Stream (pIStream);
	if(OLE_Stream.fail()) return ResultFromScode(S_FALSE);

os_bstream stream(os_adapter_for(OLE_Stream));

return out(stream);
}
HRESULT CImpICommands :: storage_in(LPSTREAM pIStream)
{
	if(m_iState == ISLOADED) return NOERROR;

olestream OLE_Stream (pIStream);
	if(OLE_Stream.fail()) return ResultFromScode(S_FALSE);

os_bstream stream(os_adapter_for(OLE_Stream));
	
return in(stream);
}

HRESULT CImpICommands :: SaveFile()
{
char Buffer[_MAX_PATH];	
	if (NULL == DEX_GetActiveProject (Buffer)) return ResultFromScode(E_FAIL);

char Name[MAXSTRLENGTH];
HRESULT hr = MakeFileName(Buffer, Name, "men");
	if(FAILED(hr)) return hr;
	
return file_out(Name);
}

HRESULT CImpICommands :: LoadFile()
{
// Menuitems nur laden, wenn Projekt geöffnet
char Buffer[_MAX_PATH];	
	if (NULL == DEX_GetActiveProject (Buffer)) return ResultFromScode(E_FAIL);

char Name[MAXSTRLENGTH];
HRESULT hr = MakeFileName(Buffer, Name, "men");
	if(FAILED(hr)) return hr;

// lädt Liste und Map vom File
return file_in (Name);
}

HRESULT CImpICommands::GetEnum(IEnum<WListElement> ** ppIEn)
{
	try {
	WListElement ILE(&m_ListItem);
	
		THROW_FAILED_HRESULT(ILE -> GetEnum(ppIEn));

	} catch (HRESULT hr) {
		return hr;
	}

	return S_OK;
}

HRESULT CImpICommands::InsertMenu(HMENU hMenu, IListElement *pILE)
{
	ASSERT(hMenu);
	
	if(NULL == pILE) pILE = &m_ListItem;

HRESULT hr = NOERROR;
WORD wItem = 0;

// Enumerator dieses ListElements geben lassen	
IEnum <WListElement> *pIEnumerator = NULL;
	hr = pILE -> GetEnum(&pIEnumerator);
	if (FAILED(hr)) return hr;	

	while (GetScode(hr) != S_FALSE) {
		
	UINT uiID = 0;
	char c[MAXSTRLENGTH];
	
	IListElement *pIListEl = NULL;
		hr = GetNextListElement (&pIListEl, pIEnumerator, c, uiID);
		if (FAILED(hr) || GetScode(hr) == S_FALSE) continue; // zur unbedingten Freigabe vom Eumerator

// neues Popup-Menü erzeugen
		if (uiID >=	MIN_DROPDOWNID) {
		
			pIListEl -> SetMenu(GetSubMenu(hMenu, wItem));
		
// für eventuell anderen Menüeintrag c				
			if ( ! ::ModifyMenu(hMenu, wItem, MF_BYPOSITION|MF_POPUP|MF_STRING, 
								(UINT)GetSubMenu(hMenu, wItem), c) )
				continue; 
			
			hr = InsertMenu(GetSubMenu(hMenu, wItem), pIListEl);
			if (FAILED(hr)) continue;
			
		} else if (uiID < MIN_SEPARATORID) {
// Sonstige Menüpunkte einhänge
		UINT uiid = ::GetMenuItemID(hMenu, wItem);
			if (uiID != uiid) {
				if ( ! ::InsertMenu(hMenu, wItem, MF_BYPOSITION|MF_STRING, uiID, c) )
					continue; 
			}
			else
// für eventuell anderen Menüeintrag c				
				if ( ! ::ModifyMenu(hMenu, uiID, MF_STRING, uiID, c) )
					continue; 
		}

		wItem ++;
	}

	pIEnumerator -> Release();

return NOERROR;
}


HRESULT CImpICommands :: InsertCommand(
	LPCSTR pMacroName, UINT uiMenuID, bool fMacro)
{
	ASSERT(NULL != pMacroName);
	ASSERT(uiMenuID>0 && uiMenuID<MIN_SEPARATORID);

CString str = pMacroName; 
CImpIMenu *pMenu = CImpIMenu :: Create (str, fMacro);

	if (NULL == pMenu) return ResultFromScode (E_OUTOFMEMORY);

	try {
	WCommand IC(pMenu);		// throws hr

		m_mapCommand[uiMenuID] = IC;

	} catch (HRESULT hr) {
		pMenu -> Release();
		return hr;
	} 

	pMenu -> Release();
	return S_OK;
}

HRESULT CImpICommands :: InsertMenuItem(LPCSTR cMenuEntry, 
										UINT uiID,
										IListElement **ppILE_ListItem,
										IListElement *pILE_ListItem_Up)
{
	if (NULL == pILE_ListItem_Up) return ResultFromScode (E_FAIL);

CListItem *pListItem = NULL;

	TRY {
		pListItem = new CListItem;
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;

	try {
	WListElement ILE(pListItem);	// throws hr

		THROW_FAILED_HRESULT(ILE -> Insert(cMenuEntry, uiID));
		THROW_FAILED_HRESULT(pILE_ListItem_Up -> Insert(ILE, NULL));

		*ppILE_ListItem = ILE.detach();
	
	} catch (HRESULT hr) {
		pListItem -> Release();
		return hr;
	}

	pListItem -> Release();
	return NOERROR;
}

HRESULT CImpICommands :: InsertMenuItem(
	LPCSTR cMenuEntry, UINT uiMenuID, 
	IListElement *pILstEl_ListItem_Up, IListElement *pILE_After)
{
// IDItem erzeugen
CIDItem *pIDItem = NULL;

	TRY {
		pIDItem = new CIDItem;
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;

	try {
	// Füllt ID_Elemente in Liste eines übergeordneten ListenElements 
	// vor Element "After"
	WListElement ILE (pIDItem);		// throw hr

		THROW_FAILED_HRESULT(ILE -> Insert(cMenuEntry, uiMenuID));
		THROW_FAILED_HRESULT(pILstEl_ListItem_Up -> Insert(ILE, pILE_After));
	
	} catch (HRESULT hr) {
		pIDItem -> Release();
		return hr;
	}
	
	pIDItem -> Release();
	return S_OK;
}

HRESULT CImpICommands :: InsertMenuItem(
	LPCSTR cMenuEntry, UINT uiMenuID, IListElement *pILstEl_ListItem_Up)
{
CIDItem *pIDItem = NULL;

	TRY {
		pIDItem = new CIDItem;
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;

	try {
	// Füllt ID_Elemente in Liste eines übergeordneten ListenElements
	// ILstEl ist eigentlich ein  Pointer auf IListElement
	WListElement ILstEl (pIDItem);		// throw hr
		
		THROW_FAILED_HRESULT(ILstEl -> Insert(cMenuEntry, uiMenuID));
		THROW_FAILED_HRESULT(pILstEl_ListItem_Up -> Insert(ILstEl, NULL));
	
	} catch (HRESULT hr) {
		pIDItem -> Release();
		return hr;
	}

	pIDItem -> Release();
	return S_OK;
}

HRESULT CImpICommands::GetMenuStructure (
	HMENU hMenu, IListElement *pILE_ListItem_Up) // übergeordnete Liste
{
	ASSERT (NULL != hMenu);		// Menuhandle gültig ?
	if (NULL == hMenu) return E_FAIL;

char cMenuEntry [_MAX_PATH+1];
HRESULT hr = NOERROR;
IListElement *pILE_LstI = NULL;
WORD nCount = (WORD)GetMenuItemCount (hMenu);
	
	for (WORD wItem = 0; wItem < nCount; wItem++) {
	UINT uiMenuID = GetMenuItemID (hMenu, wItem);

		GetMenuString (hMenu, wItem, cMenuEntry, _MAX_PATH, MF_BYPOSITION);
		if (uiMenuID == -1) {		// Popup-Menü
		// Listenelement mit Unterliste aus ID_Elementen 
			hr = InsertMenuItem((LPCSTR)cMenuEntry, m_uiDropDownID, &pILE_LstI, 
								pILE_ListItem_Up);
			m_uiDropDownID++;
			if (FAILED (hr)) return hr;

			pILE_LstI -> SetMenu(GetSubMenu (hMenu, wItem));

		//  erneuter rekursiver Aufruf , übergeordnete Liste übergeben: 
			hr = GetMenuStructure (GetSubMenu (hMenu, wItem), pILE_LstI);
			if (FAILED(hr)) return hr;
		}
		else if (uiMenuID == 0 || strlen(cMenuEntry) == 0) {
			strncpy(cMenuEntry, "======(TRENNLINIE)======", 25);// Separator
		// Es wird der Menüstring und der MenuID dem Listenelement übergeben und
		// ID_Element in Liste gefüllt 
		// auch Separatoren in Liste der ID_Elemente
			hr = InsertMenuItem((LPCSTR)cMenuEntry, m_uiTrashID, pILE_ListItem_Up);
			if (FAILED(hr)) return hr;	
			m_uiTrashID++;
		}
		else {
	// keine Separatoren in Map füllen		
			hr = InsertCommand((LPCSTR)cMenuEntry, uiMenuID, false);
			if (FAILED(hr)) return hr;
			hr = InsertMenuItem((LPCSTR)cMenuEntry, uiMenuID, pILE_ListItem_Up);
			if (FAILED(hr)) return hr;	
		}
	}

return NOERROR;
}

HRESULT CImpICommands :: GetDescription (	LPSTR pc, UINT iLen, 
												UINT ui, bool &fMacro)
{
ICommand * pIC = GetCommand(ui);
	if (NULL == pIC) {
		fMacro = false;
		return ResultFromScode(S_FALSE);
	}

HRESULT hr = pIC  -> GetDescription(pc, iLen, fMacro);
	pIC -> Release();

return hr;
}

HRESULT CImpICommands :: DeleteItem (UINT uiID,
										  IListElement *pILstEl_Up,
										  IListElement *pILE)
{
	ASSERT(pILstEl_Up);
	ASSERT(pILE);

	if (0 == m_mapCommand.erase(uiID))
		return ResultFromScode(E_FAIL);

HRESULT hr = pILstEl_Up -> ClearItem(pILE);
	if (FAILED(hr)) return hr;

HMENU hMenu = NULL;
	hr = pILstEl_Up -> GetMenu(&hMenu);
	if (FAILED(hr)) return hr;

	if ( ! DeleteMenu(hMenu, uiID, MF_BYCOMMAND) )
		return ResultFromScode(E_FAIL);

return NOERROR;
}

HRESULT CImpICommands :: GetMenuItems(HMENU hMenu)
{
	try {
	WListElement ILE(&m_ListItem);		// throws hr

		THROW_FAILED_HRESULT(ILE -> Insert("Verwalter", m_uiDropDownID++));
		THROW_FAILED_HRESULT(GetMenuStructure (hMenu, ILE));
	
	} catch (HRESULT hr) {
		return hr;
	}

	return S_OK;
}

ICommand * CImpICommands :: GetCommand (UINT uiID)
{
LPCOMMAND pIC = m_mapCommand[uiID];
	if(NULL == pIC) return NULL;
	pIC -> AddRef();
return pIC; 
}

HRESULT CImpICommands :: FireEvent (UINT uiID)
{
LPCOMMAND pIC = GetCommand(uiID);
	if (NULL == pIC) return ResultFromScode(E_FAIL);

HRESULT hr = pIC -> FireEvent(uiID); 
	pIC -> Release();

return hr;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CImpICommands :: QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if ( IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_ICommands))
		*ppv = this;
	if ( IsEqualIID (riid, IID_IPersistStream))
		*ppv = &m_PersStream;

	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	
return ResultFromScode(E_NOINTERFACE);
}

STDMETHODIMP_(ULONG) CImpICommands :: AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CImpICommands :: Release (void)
{                               
	if(--m_cRef == 0){
		delete this;
     	return 0;
    }
    	
return m_cRef;
}

//
// *** IPersistStream methods 
//
// von aussen nicht sichtbar und abfragbar

CImpICommands::XPersistStream::XPersistStream(CImpICommands *pICom)
{
	m_cRef = 0;
	m_fIsDirty = false;

	m_pICommands = pICom;
}

CImpICommands::XPersistStream::~XPersistStream(void)
{
}

STDMETHODIMP CImpICommands::XPersistStream::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
return m_pICommands->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CImpICommands::XPersistStream::AddRef(void)
{
    ++m_cRef;
return m_pICommands->AddRef();
}

STDMETHODIMP_(ULONG) CImpICommands::XPersistStream::Release(void)
{
    --m_cRef;
return m_pICommands->Release();
}

STDMETHODIMP CImpICommands::XPersistStream::GetClassID(LPCLSID pClsID)
{
return NOERROR;
}

STDMETHODIMP CImpICommands::XPersistStream::IsDirty(void)
{
// wenn noch nicht gespeichert
	if (true == m_fIsDirty)
		return ResultFromScode(S_OK);	
// schon gespeichert
return ResultFromScode(S_FALSE);
}

STDMETHODIMP CImpICommands::XPersistStream::Load(LPSTREAM pIStream)
{                      
	if (NULL == pIStream) 
		return ResultFromScode(STG_E_INVALIDPOINTER);

HRESULT hr = m_pICommands -> storage_in (pIStream);
	if (FAILED(hr)) return hr;	

	m_fIsDirty = false;
	
return NOERROR;
}

STDMETHODIMP CImpICommands::XPersistStream::Save(LPSTREAM pIStream, 
											BOOL fClearDirty )
{                     
	if (NULL == pIStream)
		return ResultFromScode(E_POINTER);
	// bei Speichern dirty = false	

HRESULT hr = m_pICommands -> storage_out (pIStream);
	if (FAILED(hr)) return hr;	

// Speichern abgeschlossen
	if (fClearDirty) 
// bleibt trotz Speichern dirty, da in einem anderen STREAM als geöffneten gespeichert wurde
		m_fIsDirty = false;     
	else
		m_fIsDirty = true;	
	
//	pIStream -> Commit(STGC_DEFAULT);
		        
return NOERROR;
}

STDMETHODIMP CImpICommands::XPersistStream::GetSizeMax(ULARGE_INTEGER FAR
												  * pcbSize)
{
return NOERROR;
}

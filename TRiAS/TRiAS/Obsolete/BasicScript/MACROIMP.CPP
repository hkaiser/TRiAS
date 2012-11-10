
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <ospace/source.h>

#include "macrguid.h"                  

#include "imacro.h"
#include "imacorg.h"

#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

HRESULT TestclsID (LPSTORAGE pIStorage, const CLSID &clsIDTest)
{
CLSID clsID;
HRESULT hr = ReadClassStg (pIStorage, &clsID);
	if (FAILED(hr)) return hr;
		
	if (!IsEqualCLSID (clsID, clsIDTest)) {
		if (clsID == CLSID_NULL)	// Absturz beim letzten mal
			hr = WriteClassStg (pIStorage, clsIDTest);
		else
			hr = ResultFromScode(E_FAIL);
	}
return hr;
}

HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt)
{
	ASSERT(pPathName);
	ASSERT(pNameToUse);
	ASSERT(pcFileExt);

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pFName = new char [_MAX_FNAME];

	if (pDrive == NULL || pPath == NULL || pFName == NULL) {
		if (pDrive) delete (pDrive);
		if (pPath) delete (pPath);
		if (pFName) delete (pFName);    
		return ResultFromScode (E_OUTOFMEMORY);
	}
	
	// DateiNamen splitten
	_splitpath (pPathName, pDrive, pPath, pFName, NULL);
	// auszugebender Name
	_makepath (pNameToUse, pDrive, pPath, pFName, pcFileExt);

	// Speicher freigeben
	delete (pDrive);
	delete (pPath);
	delete (pFName);               
		                        
return NOERROR;		
}

HRESULT MakePathName(LPCSTR pPathName, LPSTR pNameToUse)
{
	ASSERT(pPathName);
	ASSERT(pNameToUse);

char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];

	if (pDrive == NULL || pPath == NULL) {
		if (pDrive) delete (pDrive);
		if (pPath) delete (pPath);
		return ResultFromScode (E_OUTOFMEMORY);
	}
	
	// DateiNamen splitten
	_splitpath (pPathName, pDrive, pPath, NULL, NULL);
	// auszugebender Name
	_makepath (pNameToUse, pDrive, pPath, NULL, NULL);

	// Speicher freigeben
	delete (pDrive);
	delete (pPath);
		                        
return NOERROR;		
}

HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						bool &fNew, bool fDirect, CLSID clsID)
{       
LPSTORAGE pIStorage;
HRESULT hr;                                                     

DWORD dw = 0;

DWORD dwMode =	STGM_READWRITE | 
				STGM_SHARE_EXCLUSIVE ;	

	if (fDirect) dwMode = dwMode | STGM_DIRECT;
	else dwMode = dwMode | STGM_TRANSACTED;

	if (NULL == pIRootStorage) 	                   
		return ResultFromScode(STG_E_INVALIDPOINTER);

	USES_CONVERSION;
	hr = pIRootStorage -> OpenStorage (	A2OLE(strStorName), 
										NULL, dwMode, NULL,
										0, &pIStorage);
	if (FAILED(hr)) {
		if (STG_E_FILENOTFOUND == GetScode(hr)) {
			hr = pIRootStorage -> CreateStorage (	A2OLE(strStorName), 
													dwMode, 0, 0, &pIStorage);
			if (SUCCEEDED(hr)) {
				hr = WriteClassStg (pIStorage, clsID);
				fNew = true;
			}
			else {
				*ppISubStorage = NULL;
				return hr;
			}
		}
		else {
			*ppISubStorage = NULL;
			return hr;
		}
	}
						
	hr = TestclsID (pIStorage, clsID);
	if (FAILED(hr)) { pIStorage -> Release(); return hr; }
	
	*ppISubStorage = pIStorage;
	
return NOERROR;
} 

HRESULT MakeRootStorage(LPSTORAGE *ppIStorage, LPCSTR pPathName)
{           
HRESULT hr = NOERROR;

DWORD dwMode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE | 
				STGM_TRANSACTED ;

char *pNameToUse = new char [_MAX_PATH];

LPSTORAGE pIStorage = *ppIStorage;
	
	if (NULL == pNameToUse || NULL == pPathName)
		return ResultFromScode(E_FAIL);
	
	// alte ProjektStruktur, eigenes DocFile erzeugen/öffnen  
	// erstellt Pfadnamen
	hr = MakeFileName (pPathName, pNameToUse, "str");
	if (FAILED(hr))			
		return hr;
		
// Funktionen machen Addref(), Release() im Destruktor (Memberpointer Rootstorage)
	USES_CONVERSION;
	hr = StgOpenStorage (A2OLE(pNameToUse), NULL, dwMode, 0, 0, &pIStorage);
	if (FAILED(hr)) {
		if (GetScode(hr) == STG_E_FILENOTFOUND) {
		// neu anlegen
			dwMode |= STGM_CREATE;

			hr = StgCreateDocfile (A2OLE(pNameToUse), dwMode, 0, &pIStorage);
			delete (pNameToUse);
			if (FAILED(hr)) return hr;
				
			// GUID reinschreiben (Kontrollmöglichkeit)
			hr = WriteClassStg (pIStorage, CLSID_ScriptContainer);				
			if (FAILED(hr)) {
				pIStorage -> Release();
				return hr;
		    }
		}
		else {
		    delete (pNameToUse);
		    return hr;
		}
	} else delete (pNameToUse);

	hr = TestclsID (pIStorage, CLSID_ScriptContainer);
	if (FAILED(hr)) { pIStorage -> Release(); return hr; }

	*ppIStorage = pIStorage;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACROSCRIPTINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CIMacroScriptImp* CIMacroScriptImp :: Create(LPUNKNOWN pUnkOuter, CMacroScripts* pMacroScripts)
{
	if (pUnkOuter == NULL)
		return NULL;

	CIMacroScriptImp* pIMacroScripts = new CIMacroScriptImp(pUnkOuter, pMacroScripts);
	if ( NULL == pIMacroScripts || !pIMacroScripts -> FInit() )
		return NULL;		

return  pIMacroScripts;
}
		
CIMacroScriptImp :: CIMacroScriptImp(LPUNKNOWN pUnkOuter, CMacroScripts* pMacroScripts)
{
	m_cRef=0;

	m_pUnkOuter = pUnkOuter;

	m_pMacro = NULL;
	m_pMacroScripts = pMacroScripts;
	
	m_pIRootStorage = NULL;
	
	m_fNotCommit =	false;
	m_fNew =		false;
	
	m_pIStream = NULL;

return;
}

CIMacroScriptImp :: ~CIMacroScriptImp()
{                
DWORD dw = 0;
// nur bei altem Projekt
	if (m_pIRootStorage) dw = m_pIRootStorage -> Release();
	ASSERT(dw==0);
	m_pIRootStorage = NULL;
	
	if (m_pIStream) dw = m_pIStream -> Release();  
	ASSERT(dw==0);
	m_pIStream = NULL;
}                                                     

HRESULT CIMacroScriptImp :: DestroyStorage()
{

CEnumMacroScripts *pEn = NULL;
HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr;	
	
CObArray *pA = pEn -> GetArray ();	
	pEn -> Release();

    if (0 != ULONG(pA -> GetSize())) return hr; 

	USES_CONVERSION;

LPSTORAGE pIStorage = NULL;
	
	if (NULL == DEX_GetProjectStorage (pIStorage)) {
		if (m_pIRootStorage) {
			hr = m_pIRootStorage -> DestroyElement(A2OLE("MacroScripts"));
			if (FAILED(hr) && GetScode(hr) != STG_E_FILENOTFOUND) return hr;

			hr = m_pIRootStorage -> Commit(STGC_DEFAULT);
			if (FAILED(hr)) return hr;
		}
	}
	else {
		hr = m_pMacroScripts -> GetIPersistStorage() -> HandsOffStorage();
		if (FAILED(hr)) { pIStorage -> Release(); return hr; }

		hr = pIStorage -> DestroyElement(A2OLE("MacroScripts"));
		pIStorage -> Release();
	}

return hr;
}

bool CIMacroScriptImp :: FInit()
{
return true;	
}                                         

//////////////////////////////////////////////////////////////////////////
// *** MacroScripts specific functions ***

////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CIMacroScriptImp :: GetebInst(CebInstance **ppInst) 
{
	*ppInst = NULL;
	*ppInst = m_pMacroScripts -> GetebInst();
	if (NULL == *ppInst) return ResultFromScode(E_FAIL);

return NOERROR;
}

STDMETHODIMP CIMacroScriptImp :: GetEnumScripts (IEnumScripts **ppenum)
{
CEnumMacroScripts *pEn = NULL;
HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr; 		

	hr = pEn -> Clone (ppenum);
	pEn -> Release();

return hr;
}


STDMETHODIMP CIMacroScriptImp :: DelScript (LPCSTR pcName)
{                             
	ASSERT(pcName);

CMacro *pM = NULL;		
CString strMacroName = pcName;
CEnumMacroScripts *pEn = NULL;

HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr; 		

// alten schon geöffneten Stream schliessen,
// Objekte aus dem Enumerator loeschen
bool fNew = false;
	hr = pEn -> DelItem (strMacroName, &fNew);
	if (FAILED(hr)) {
		pEn -> Release(); return hr;
	}
	
bool fNotCommit = false;

	//  für COMMIT(), wenigstens einen mit Commit() finden	
	while (S_OK == pEn -> Next (1, &pM, NULL) && fNotCommit == false) {
			fNotCommit = pM -> GetIMacros() -> GetNotCommit();
			if (fNotCommit) break;
	}

	pEn -> Release();

// bei neuem Macro UND kein anderer gespeicherter vorhanden, Commit() nicht nötig
// Commit wurde gesetzt, als der jetzt zu löschende gespeichert wurde

	if (fNew == true && fNotCommit == false) 
		m_fNotCommit = false;			
	else {
		// Löschen beendet, aber noch COMMIT()
		DEX_SetDirtyGeoDB(1);
		m_fNotCommit = true;
	}

LPSTORAGE pIStorage;
	hr = m_pMacroScripts -> GetIPersistStorage() -> GetStorage(&pIStorage);
	if (FAILED(hr)) return hr;	

// Stream vom Storage loeschen, wenn vorhanden
	USES_CONVERSION;
	hr = pIStorage -> DestroyElement (A2OLE(strMacroName));
	pIStorage -> Release();
	if (FAILED(hr) && GetScode(hr) != STG_E_FILENOTFOUND)
		return hr;

return NOERROR;
}

DWORD CIMacroScriptImp :: GetScriptInfo (ebFILEHEADER *pHead)
{
	if(pHead == NULL) return 0;

DWORD dwFlags = 0;

	if(pHead -> dwScriptSz > 0)
		dwFlags |= CC_SCRIPT;

	if(pHead -> dwCodeSz > 0)
		dwFlags |= CC_CODE;

return dwFlags;
}

STDMETHODIMP CIMacroScriptImp :: GetScriptInfo (LPCSTR pcName, 
												DWORD *pdwInfo) 
{
	ASSERT(pcName);

CMacro *pM = NULL;		
CEnumMacroScripts *pEn = NULL;

HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr; 		
		
// pMakro -> AddRef(), wenn aufindbar !!!
	hr = pEn -> FindByName (pcName, &pM);
	pEn -> Release();
	
	if (FAILED(hr) || S_FALSE == GetScode(hr)) 	return hr;

LPSTREAM pIStream = NULL;
	
	if(m_pIStream) {
		m_pIStream -> Release(); m_pIStream = NULL;
	}

CString str = pcName;
								// ADDREF()
	hr = OpenOrCreateStream(str, &m_pIStream);
	if(FAILED(hr)) {
		pM -> Release(); return hr;
	}

ebFILEHEADER Head;
	hr = pM -> GetIPersistStream() -> LoadHeader (m_pIStream, &Head);
	pM -> Release();			// kein Header
	if (FAILED(hr)) return hr; 

// Header, aber kein Code
	*pdwInfo = GetScriptInfo (&Head);

return hr;
} 

STDMETHODIMP CIMacroScriptImp :: CreateScript (LPCSTR pcName)
{
return ResultFromScode(E_NOTIMPL);
}

HRESULT CIMacroScriptImp :: OpenOrCreateStream(const CString & strMacroName, LPSTREAM *ppIStream)
{
LPSTORAGE pISubStorage = NULL;

HRESULT	hr = m_pMacroScripts -> GetIPersistStorage() -> GetStorage (&pISubStorage);
	if (FAILED(hr)) return hr;

DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 
// vorhandenen Stream öffnen
	USES_CONVERSION;
	hr = pISubStorage -> OpenStream (A2OLE(strMacroName), 0, dwMode, 0, ppIStream);
	if (FAILED(hr)) {
		hr = pISubStorage -> CreateStream (A2OLE(strMacroName), dwMode, 0, 0, ppIStream);
	}

	pISubStorage -> Release();

return hr;
}

STDMETHODIMP CIMacroScriptImp :: GetScript (LPCSTR pcName, LPSTR *ppcMacroText,
											ebHCODE *phCode)
{                        
	ASSERT(pcName);

CString	strMacroName = pcName;
CMacro *pM = NULL;		
CEnumMacroScripts *pEn = NULL;
		
// immer Stream öffnen und aufheben bis neues Script geoeffnet wird
	if (m_pIStream) 
		m_pIStream -> Release(); m_pIStream = NULL;
	
HRESULT hr = OpenOrCreateStream(strMacroName, &m_pIStream);
	if (FAILED(hr)) return hr; 
		
	hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr; 		

// pMakro -> AddRef(), wenn aufindbar !!!
	hr = pEn -> FindByName (strMacroName, &pM);
	pEn -> Release();
	if (FAILED(hr)) { 
		if (pM) pM -> Release(); return hr;
	}

	*ppcMacroText = NULL;

	if (S_FALSE == GetScode(hr)) {

// pMakro -> AddRef(), kein passendes Objekt gefunden, Schaffen des Objektes 
		
		pM = CMacro :: Create (NULL);
		if (NULL == pM) {
			if (m_pIStream) m_pIStream; m_pIStream = NULL; return ResultFromScode(E_FAIL);
		}

		pM -> GetIMacros() -> SetName(strMacroName);
// neues Macro für späteres Commit() kennzeichnen
		pM -> GetIMacros() -> SetNew(true);

// Script in Liste füllen, pMakro->AddRef(),   
		hr = m_pMacroScripts -> AddScript (strMacroName, pM);
		pM -> Release();
		if (FAILED(hr)) {
			if (m_pIStream) m_pIStream; m_pIStream = NULL; return hr;
		}

		return ResultFromScode (S_FALSE);
	
	} else {

// Makro schon vorhanden und geöffnet bei pPersistStorage -> Load()			
// liest eigentliche Daten aus PersistStream-Objekt
		hr = GetData (ppcMacroText, phCode, pM);
// von FindByName() 
		pM -> Release();

// ppcMacroText, phCode draussen freigeben
		if (FAILED(hr)) {
			if (m_pIStream) m_pIStream; m_pIStream = NULL; return hr;
		}
	}                           
	
return ResultFromScode (S_OK);
}

HRESULT CIMacroScriptImp :: GetData (LPSTR *ppcMacroText, ebHCODE *phCode, CMacro *pM)
{
		// Standardinterfacefunktion: Lesen des Scripts	
HRESULT	hr = pM -> GetIPersistStream() -> Load (m_pIStream);
	if (FAILED(hr)) return hr; 
		
	hr = pM -> GetIPersistStream() -> GetScriptText(ppcMacroText);     
	if(FAILED(hr)) return hr; 

	// Code geben lassen 			
	hr = pM -> GetIPersistStream() -> GetCode(phCode);
	if (FAILED(hr)) return hr;

return hr;
}

HRESULT CIMacroScriptImp :: SetData (LPSTR pText, ebHCODE hCode, 
									DWORD dwSaveFlag, CMacro *pM)
{
	ASSERT(pText);
	ASSERT(pM);
	ASSERT(m_pIStream);

// Setzen aller Informationen zum erfolgreichen Speichern als Member von Inerface-PersistStream
HRESULT hr = pM -> GetIPersistStream() -> SetCode (hCode);
	if(FAILED(hr)) return hr;
	
	pM -> SetCompiled(dwSaveFlag);

// Text immer setzen  
	hr = pM -> GetIPersistStream() -> SetScriptText (pText);
	if (FAILED (hr)) return hr;             

// Schreiben des Textes, physisches Abspeichern erst bei Commit()
// Stream muss geoeffnet sein (Low-Memory-Situation ?)
	hr = pM -> GetIPersistStream() -> Save (m_pIStream, false);	
	if (FAILED(hr)) return hr;

// zur nochmaligen Überprüfung für Commit() bei DelScript()
	pM -> GetIMacros() -> SetNotCommit(true);

return hr;
}

STDMETHODIMP CIMacroScriptImp :: SetScript (LPCSTR pcName, 
											LPSTR pText, ebHCODE hCode, 
											DWORD dwSaveFlag) 
{
	ASSERT(pcName);

CString strMacroName = pcName;
CMacro *pM = NULL;
CEnumMacroScripts *pEn = NULL;
HRESULT hr = m_pMacroScripts -> GetEnum (&pEn);
	if (FAILED(hr)) return hr;
	
// ist Makro schon in Liste ?   pM -> AddRef()
	hr = pEn -> FindByName (strMacroName, &pM);		
	pEn -> Release();// kein passendes Objekt gefunden	        						
	if (FAILED(hr) || S_FALSE == GetScode(hr)) 	return hr;
	
	hr = SetData (pText, hCode, dwSaveFlag, pM);
//	 von FindByName()	
	pM -> Release();			           
// Commit() ?
	m_fNotCommit = true;
return hr;
}


STDMETHODIMP_(HRESULT) CIMacroScriptImp :: NewSubStorage(LPSTORAGE pIRootStorage, 
														LPSTORAGE *ppISubStorage)
{
//
// *** Für CopyTo() !!!
//
	ASSERT(pIRootStorage);

CString s; 
	TRY {
		if (0 == s.LoadString(IDS_STORAGE_NAME_MACROSCRIPTS))
			return false;
	}
	CATCH ( CMemoryException, e ) {	
		AfxMessageBox (IDS_NOMEMORY);
	}
	END_CATCH

LPSTORAGE pIStorage = NULL;
	HRESULT hr = MakeSubStorage(pIRootStorage, ppISubStorage, s, m_fNew, true, CLSID_ScriptContainer);

return hr;
}

STDMETHODIMP_(HRESULT) CIMacroScriptImp :: InitStorages (LPSTORAGE pIRootStorage, LPCSTR pPath )
{
	if(m_pIRootStorage) return NOERROR;

HRESULT hr = NOERROR;     
LPSTORAGE pISubStorage = NULL;

// liefert m_pIRootStorage und pISubStorage 
//  mit internem AddRef()
//Schaut nach Wurzel der Storagestruktur:

	hr = FInitStorages(pPath, pIRootStorage, &pISubStorage);
	if (FAILED(hr)) return hr;
        
IPersistStorage *pIPersistStorage = m_pMacroScripts -> GetIPersistStorage();
	if(pIPersistStorage) hr = pIPersistStorage -> Load(pISubStorage);
	if (FAILED(hr)) return hr;   	
	if (GetScode(hr) == S_FALSE) hr = pIPersistStorage -> InitNew(pISubStorage);

	pISubStorage -> Release();

return hr;	
}

STDMETHODIMP_(HRESULT) CIMacroScriptImp :: Commit (DWORD grfCommitFlags, bool fAsk) 
{                       
HRESULT hr = NOERROR;

// ist voher etwas verändert worden ?, dann Commit()
	if (m_fNotCommit) {
	
		if ( AskSaveChanges() == IDYES || fAsk == false ) {
			
		LPSTORAGE  pISubStorage = NULL;		
			hr = m_pMacroScripts -> GetIPersistStorage() -> GetStorage(&pISubStorage);
			if (FAILED(hr)) return hr;
			// Storage vorher in ProjectClose zerstoert
			if(pISubStorage == NULL) return ResultFromScode(S_FALSE);
			
			hr = pISubStorage -> Commit(grfCommitFlags);
			pISubStorage -> Release();
			if (FAILED(hr)) return hr;								
			
			m_fNotCommit = false;
		}
	// bei altem Projekt Storage für weitere Nutzung behalten
		if (m_pIRootStorage) {
	// eventuell Substorage löschen, wenn kein Stream vorhanden
			hr = m_pIRootStorage -> Commit(grfCommitFlags);
			if (FAILED(hr)) return hr;
			m_fNotCommit = false;
		}
	}

	DestroyStorage();

return hr;
}

int CIMacroScriptImp :: AskSaveChanges ()
{
// nur bei alten Projekten noch einmal fragen
	if (m_pIRootStorage == NULL)
		return true;

CString strSp;
	strSp.LoadString (IDS_MACROSAVE);

return AfxMessageBox (strSp, MB_YESNOCANCEL);
}


STDMETHODIMP_(HRESULT) CIMacroScriptImp :: IsDirty (void) 
{ 
	if (m_fNotCommit) ResultFromScode (S_OK);
return ResultFromScode (S_FALSE);
}

STDMETHODIMP_(HRESULT) CIMacroScriptImp :: SetNotCommit (bool fNotCommit) 
{
	m_fNotCommit = fNotCommit;
return NOERROR;
}

// lädt Root und eigenes Substorage
HRESULT CIMacroScriptImp :: FInitStorages(LPCSTR pPathName, 
										  LPSTORAGE pIRootStorage,
										  LPSTORAGE *ppISubStorage)
{	
HRESULT hr = NOERROR;	
	if (NULL == pIRootStorage) {
	// wird pIRootStorage -> Addref durchgeführt
		hr = MakeRootStorage(&m_pIRootStorage, pPathName); 
		if (FAILED(hr)) return hr;
	}

DWORD dw = 0;
CString s; 
	TRY {
		if (0 == s.LoadString(IDS_STORAGE_NAME_MACROSCRIPTS)) {
			if(m_pIRootStorage) m_pIRootStorage -> Release();
			return ResultFromScode(E_FAIL);
		}
	}
	CATCH ( CMemoryException, e ) {	
		if(m_pIRootStorage) m_pIRootStorage -> Release();
		AfxMessageBox (IDS_NOMEMORY);
		return ResultFromScode(E_FAIL);
	}
	END_CATCH
	
	hr = MakeSubStorage(pIRootStorage ? pIRootStorage : m_pIRootStorage, ppISubStorage, s, m_fNew, false/*direkt*/, CLSID_ScriptContainer); 
	if (FAILED(hr) && GetScode(hr) != STG_E_ACCESSDENIED) if(m_pIRootStorage) m_pIRootStorage -> Release();


return hr;
}                     

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CIMacroScriptImp :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}


STDMETHODIMP_(ULONG) CIMacroScriptImp :: AddRef (void)
{
    ++m_cRef;
return m_pUnkOuter -> AddRef ();
}


STDMETHODIMP_(ULONG) CIMacroScriptImp :: Release (void)
{                               
    --m_cRef;
return m_pUnkOuter -> Release ();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MACROSINTERFACEIMP.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CIMacrosImp* CIMacrosImp :: Create(LPUNKNOWN pUnkOuter, CMacro *pMacro)
{                           
	if (pUnkOuter == NULL)
		return NULL;
		
	CIMacrosImp* pIMacro = new CIMacrosImp (pUnkOuter, pMacro);
	if ( NULL == pIMacro )
		return NULL;		

return  pIMacro;
}
		
CIMacrosImp :: CIMacrosImp(LPUNKNOWN pUnkOuter, CMacro *pMacro)
{	                    
   	m_cRef=0;                                             
    	
	m_pMacro = pMacro;      	
	m_pUnkOuter = pUnkOuter;	

	m_fNew = false;
	m_fNotCommit = false;	
}

CIMacrosImp :: ~CIMacrosImp()
{                     
}                                                     

bool CIMacrosImp :: FInit()
{                             
return TRUE;
}

// *** Macros specific functions ***
HRESULT CIMacrosImp :: SetNew (bool fNew)
{
	if (m_fNew == true)
		return ResultFromScode (E_FAIL);

	m_fNew = fNew;

return NOERROR;
}

bool CIMacrosImp :: GetNew (void)
{
return m_fNew;
}


HRESULT CIMacrosImp :: SetNotCommit (bool fNotCommit)
{
	m_fNotCommit = fNotCommit;

return NOERROR;
}

bool CIMacrosImp :: GetNotCommit (void)
{
return m_fNotCommit;
}

STDMETHODIMP CIMacrosImp :: GetName (LPSTR pScName, ULONG ulSize)
{
	if (ulSize < (ULONG)m_strName.GetLength() || pScName == NULL)
		return ResultFromScode(E_FAIL);

	strcpy (pScName, m_strName);
int iLen = m_strName.GetLength();
	pScName[iLen+1] = '\0';					   
	
return NOERROR;
}


STDMETHODIMP CIMacrosImp :: SetName (LPCSTR pScName)
{              
	if (NULL == pScName)
		return ResultFromScode(E_FAIL);

	if (m_strName.GetLength() != 0)
		m_strName.Empty();

	m_strName = pScName;
return NOERROR;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CIMacrosImp :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
return m_pUnkOuter -> QueryInterface (riid, ppvObj);
}


STDMETHODIMP_(ULONG) CIMacrosImp :: AddRef (void)
{
	++m_cRef;
return m_pUnkOuter -> AddRef ();
}

STDMETHODIMP_(ULONG) CIMacrosImp :: Release (void)
{                                                 
	--m_cRef;
return m_pUnkOuter ->  Release();
}




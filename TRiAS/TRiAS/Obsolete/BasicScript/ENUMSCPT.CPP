// Enumerator der ObjektProperties einer Erweiterung --------------------------
// File ENUMPROP.CXX

#include "bscriptp.hxx"

#include "macrguid.h"

#include "imacro.h"
#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


// Der eigentliche Enumerator der ObjektProperties ----------------------------
CEnumMacroScripts :: CEnumMacroScripts (void)
                       : m_ObArray()
{
	m_dwRefCnt = 0L;
	Reset();
}

CEnumMacroScripts :: ~CEnumMacroScripts (void)
{
	ReleaseStreams();
}

void CEnumMacroScripts :: ReleaseStreams()
{
// Liste aus Objekten wieder freigeben
ULONG ul = 0;
	while (ul < ULONG(m_ObArray.GetSize())) {
	CMacroHelper *pObj = (CMacroHelper *)m_ObArray.GetAt (m_ObArray.GetSize()-1);	   
// Freigabe erst der LPUNKNOWN's und dann der Objekte an sich	    
		if (pObj != NULL) {
			m_ObArray.RemoveAt (m_ObArray.GetSize()-1);
			delete pObj;
			pObj = NULL;
		}
	}
}

CEnumMacroScripts *CEnumMacroScripts :: CreateInstance (CEnumMacroScripts *penum)
// penum wird bei CLONE() zum Kopieren des derzeitigen Zustandes übergeben
{
CEnumMacroScripts *pEnum = new CEnumMacroScripts();
	if (NULL == pEnum)
		return NULL;

	if (!pEnum -> FInit (penum)) {
		delete (pEnum);
		pEnum = NULL;
		return NULL;
	}
	pEnum -> AddRef();

return pEnum;
}

bool CEnumMacroScripts :: FInit (CEnumMacroScripts *pEnum)
{                        
// Kopieren, wenn CLONE()
	if (NULL != pEnum /* alter Enumerator */) {
	CObArray *pArray = pEnum -> GetArray();                  
	int iCnt = pArray -> GetSize(); 
	int i = 0;      
	CString strName;
	char *pc = strName.GetBuffer(MAXSTRLENGTH);
	CMacroHelper *pObj;
		TRY {		
			for (i=0; i<iCnt ; i++) {						
				pObj = pEnum -> GetAt (i); 
				CMacro *pM = pObj -> GetMacro();
				AddScript (*pObj, pM);
			}
		} 
		CATCH (CMemoryException, e) {
			return false;
		}
		END_CATCH
		SetCurr (pEnum -> GetCurr());
	}
	
return TRUE;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CEnumMacroScripts :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IUnknown || riid == IID_IEnumScripts)
		*ppvObj = this;
	else
		return ResultFromScode (E_NOINTERFACE);

	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CEnumMacroScripts :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CEnumMacroScripts :: Release (void)
{
	if (--m_dwRefCnt == 0) {
		delete this;	// freigeben
		return 0L;
	}

return m_dwRefCnt;
}

// *** IEnumUnknown methods ---------------------------------------------------
STDMETHODIMP CEnumMacroScripts :: Next (ULONG celt, LPUNKNOWN *ppUnk, ULONG *ppeltFetched)
{
//                       Anzahl zu liefernder Werte | hierhin liefern | wirklich gelieferte
DWORD cONrReturn = 0L;
ULONG ulCnt = ULONG(m_ObArray.GetSize()); 
LPUNKNOWN pUnk = *ppUnk;
CMacro * pM = NULL;

	if (ppeltFetched) *ppeltFetched = 0L;
	
	if (NULL == ppUnk || ulCnt <= m_ulCurr) 
		return ResultFromScode(S_FALSE);

	while (ulCnt > m_ulCurr && 0 < celt) {
	CMacroHelper *pObj;
	
		VERIFY( pObj = (CMacroHelper *)m_ObArray.GetAt ( (int)m_ulCurr ) );

		pM = pObj -> GetMacro();
		pM -> AddRef();
		
		pUnk = (LPUNKNOWN) pM;
		
		*ppUnk = pUnk;	         
		ppUnk++;		

	// weiterzählen
		m_ulCurr++;
		celt--;
		cONrReturn++;
	}
	
	if (ppeltFetched) 
		*ppeltFetched = (cONrReturn - celt);	// gelieferte Werte
	
	         
return S_OK;
}

HRESULT CEnumMacroScripts :: Next (ULONG celt, CMacro **ppM, ULONG *ppeltFetched)
{
//                       Anzahl zu liefernder Werte | hierhin liefern | wirklich gelieferte
DWORD cONrReturn = 0L;
ULONG ulCnt = ULONG(m_ObArray.GetSize()); 
CMacro * pM = *ppM;

	if (ppeltFetched) *ppeltFetched = 0L;
	
	if (NULL == ppM || ulCnt <= m_ulCurr) 
		return ResultFromScode(S_FALSE);

	while (ulCnt > m_ulCurr && 0 < celt) {
	CMacroHelper *pObj;
	
		VERIFY( pObj = (CMacroHelper *)m_ObArray.GetAt ( (int)m_ulCurr ) );

		pM = pObj -> GetMacro();
		pM -> AddRef();
		
		*ppM = pM;	         
		ppM++;		

	// weiterzählen
		m_ulCurr++;
		celt--;
		cONrReturn++;
	}
	
	if (ppeltFetched) 
		*ppeltFetched = (cONrReturn - celt);	// gelieferte Werte
	
	         
return S_OK;
}

STDMETHODIMP CEnumMacroScripts :: Skip (ULONG dwSkip)
{               
// Überspringen dwSkip Elemente                    
	if (m_ObArray.GetSize() > (int) (m_ulCurr + dwSkip)) {
		m_ulCurr += dwSkip;
		return NOERROR;
	}

return ResultFromScode(S_FALSE);
}

STDMETHODIMP CEnumMacroScripts :: Reset (void)
{             
	m_ulCurr = 0;
	
return NOERROR;
}

STDMETHODIMP CEnumMacroScripts :: Clone (IEnumScripts **ppenum)
{                                                                      
	*ppenum = NULL;		// für alle Fälle

//  neuen Enumerator bilden
CEnumMacroScripts *pEnum = CEnumMacroScripts :: CreateInstance (this);

	if (pEnum == NULL) return ResultFromScode (E_OUTOFMEMORY);

	*ppenum = pEnum;
		
return NOERROR;
}

STDMETHODIMP CEnumMacroScripts :: FindByName (LPCSTR pName, LPUNKNOWN *ppUnk)
{                     
	ASSERT (pName);
	
CMacroHelper *pObj = NULL;
LPUNKNOWN pUnk = *ppUnk;

	if (! m_MapScript.Lookup( pName, (CObject*&) pObj))
		return ResultFromScode(S_FALSE);

	ASSERT (pObj);
	if (NULL == pObj) return ResultFromScode(E_FAIL);

	CMacro *pM = pObj -> GetMacro(); 
        
        pUnk = (LPUNKNOWN) pM;
        
	pUnk -> AddRef(); 
	
	*ppUnk = pUnk;
	
return ResultFromScode(S_OK);
}

HRESULT CEnumMacroScripts :: FindByName (LPCSTR pName, CMacro ** ppM)
{                     
	ASSERT (pName);
	
CMacroHelper *pObj = NULL;
CMacro * pM = NULL;

	if (! m_MapScript.Lookup( pName, (CObject*&) pObj))
		return ResultFromScode(S_FALSE);

	ASSERT (pObj);
	if (NULL == pObj) return ResultFromScode(E_FAIL);

	pM =  pObj -> GetMacro(); 

	if (pM == NULL)
		return ResultFromScode(E_FAIL);
				
	pM -> AddRef(); 
	
	*ppM = pM;
	
return ResultFromScode(S_OK);
}


HRESULT CEnumMacroScripts :: GetNextString (int i, CString *pstrNext)
{
int iCnt = m_ObArray.GetSize(); 

	if (iCnt <= i) 
		return ResultFromScode(E_FAIL);

	CMacroHelper *pObj = NULL;
	
	VERIFY( pObj = (CMacroHelper *)m_ObArray.GetAt (i) );
	if (NULL == pObj) return ResultFromScode(E_FAIL);
	
	*pstrNext = *pObj;  

return NOERROR;
}

HRESULT CEnumMacroScripts :: AddScript (CMacroHelper *pObj)
{        
	TRY {
		m_ObArray.Add (pObj);	
// AddRef()
// Freigabe siehe in ~()
		m_MapScript.SetAt (*pObj, pObj);
	}
	CATCH (CMemoryException, e) {
		return ResultFromScode(E_OUTOFMEMORY);
	}
	END_CATCH
		
return NOERROR;
}
        
HRESULT CEnumMacroScripts :: AddScript (LPCSTR pcName, CMacro *pM)
{       
	if (NULL == pcName || NULL == pM) 
		return ResultFromScode(E_FAIL);

// pM -> AddRef()
CMacroHelper *pObj = new CMacroHelper (pcName, pM);	
	if (pObj == NULL) 
		return ResultFromScode(E_FAIL);

HRESULT hr = AddScript (pObj);
	if (FAILED(hr)) {
		delete pObj;
		pObj = NULL;
		return hr;
	}
	
return NOERROR;
}

HRESULT CEnumMacroScripts :: DelItem (CString strName, bool *pfNew)
{              
// Objekt suchen
CMacroHelper *pObj = NULL;
	if (0 == m_MapScript.Lookup (strName, (CObject*&) pObj))
		return ResultFromScode(S_FALSE);
// Objekt aus Liste löschen	
	if ( ! m_MapScript.RemoveKey (strName) )
		return ResultFromScode(E_FAIL);

// Objekt aus Array löschen                             
CString strNext;
HRESULT hr = NOERROR;             
int i = 0;
bool fFound = false;

	while (fFound == false && GetScode(hr) == S_OK) {
		hr = GetNextString (i, &strNext);
		if (strNext == strName) {
			m_ObArray.RemoveAt(i); 
			fFound = true;
		}
		i++;
	}       
	if (fFound == false)	
		return ResultFromScode(E_FAIL);

// Objekt an sich löschen
	if (pObj) {
		*pfNew = pObj -> GetMacro() -> GetIMacros() ->	GetNew();
		delete pObj;
		pObj = NULL;
	}                       
	else return ResultFromScode(E_FAIL);
	
return hr;
}
        

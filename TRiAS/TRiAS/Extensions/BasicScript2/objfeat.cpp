// File: ONBJFEAT.CPP

#include "bscriptp.hxx"
#include "bscript.h"

#include <new>
#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>

#include <iobjman.h>

#include "macrguid.h"
#include "iscrprop.h"

extern CComModule _Module;

#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "macro.h"
#include "objfeat.h"
#include "BSParam.h"

#define OS_NO_STREAM_SUPPORT

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#if defined(WIN32)
#define __huge
#endif // WIN32

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

typedef enum tagRunFlag
{
	CUMULATION,
	RESET,
	EVAL
} RunFlag;

///////////////////////////////////////////////////////////////////////////////
// Smartinterfacedefinitionen 
DefineSmartInterface(ObjectManagement);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(GetTRiASApplication);
DefineSmartInterface(Dispatch);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ScriptProperty);
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);	// W_DGeoObject
DefineSmartInterface2(_DDocument, IID_DDocument);	// W_DDocument
DefineSmartInterface2(_DApplication, IID_DApplication);

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern SummitModul g_SummitModuls[];
#include "eb.h"
//////////////////////////////////////////////////////////////////////////////////////////////
// CALLBACK Funktionsdeklarationen 
extern "C" 
extern "C" 
void ebCALLBACK _XTENSN_EXPORT OnObjFeatRuntimeError (	long lParam, ebLPCSTR lpMsg, ebDWORD dwErrNum, ebWORD wLinNr, ebWORD wCharPos, 
												ebLPCSTR lpSource, ebLPCSTR lpHelpFile, ebDWORD dwHelpContext);
extern "C" 
ebHSCRIPT ebCALLBACK _XTENSN_EXPORT RequestorProc (ebHTHREAD hThread, ebLPCTSTR pcMacroName, long lParam);

///////////////////////////////////////////////////////////////////////////////
// algemeine globale Funktionen
HRESULT RunThread(ebHTHREAD hThread, ebHSCRIPT hScript);
BOOL	LoadString(CString & str, int IDS);
CString GetPathName (LPCSTR pcPath);
HRESULT SetHomeDir(CebInstance *pInst, LPCSTR lpcstr);
HRESULT GetValueVariant (CebThread &rThread, ebVARIANT var, LPVOID *lplpVoid, ebWORD wType);
HRESULT SetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT GetReturnParams (CebThread & rThread, BSPARAM *pBSParams, LPVOID *lplpExtVariant, ebWORD wExtVariantType);
HRESULT GetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);
HRESULT ResetApplicationObjects (CebThread & rThread, BSPARAM *pBSParams, int iCountPar);

//////////////////////////////////////////////////////////////////////////////
//	Methods: Base CObjectFeatureScript2

CObjectFeatureScript2::CObjectFeatureScript2() 
{
	m_dwID = 0; // INSTALL /UNINSTALL
	m_pRelScripts = NULL;
	m_pScript = NULL;
	m_ulAccessCount = 0;
	m_pSuspendDeb = NULL;
}
CObjectFeatureScript2::~CObjectFeatureScript2()
{
	ASSERT(NULL == m_pRelScripts);
	ASSERT(NULL == m_pSuspendDeb);
	if (m_pScript) delete m_pScript; m_pScript = NULL;
}

//////////////////////////////////////////////////////////////////////////////
//	Methods: IPersist
STDMETHODIMP CObjectFeatureScript :: GetClassID(LPCLSID pClsID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	*pClsID = CLSID_CreateObjectFeatureScript;
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////////
//	Methods: IPersist
STDMETHODIMP CObjectFeatureFileScript :: GetClassID(LPCLSID pClsID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	*pClsID = CLSID_CreateObjectFeatureFileScript;
	return S_OK;
}

STDMETHODIMP CObjectFeatureScript2 :: SetName(LPCSTR lpcstr) 
{ 
	m_strScriptName = lpcstr; 
	return S_OK; 
} 
STDMETHODIMP CObjectFeatureScript2 :: GetName(LPSTR lpstr, UINT ui)  
{	
	if (ui < m_strScriptName.GetLength() || m_strScriptName.IsEmpty())
		return E_FAIL;
	strcpy(lpstr, m_strScriptName);
	return S_OK;
} 

///////////////////////////////////////////////////////////////////////////////////////
// *** IObjectProperty ***
STDMETHODIMP CObjectFeatureScript2::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	HRESULT hr = S_OK;

	if (NULL != pBuffer)
		hr = GetName(pBuffer, wLen);

	if (NULL != pdwFlags) {
		if (FAILED(RunPropertyFlags (pdwFlags)))
			*pdwFlags = PROPCAPS_RESTRICTED|PROPCAPS_OBJPROPTYPE_STRING|PROPCAPS_GENERATED;
	}
	return hr;
}

STDMETHODIMP_(ULONG) CObjectFeatureScript2::Count(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ULONG ulCount = 0;
	HRESULT hr = RunCount (&ulCount);
	if (SUCCEEDED(hr))
		return ulCount;
	return 	m_ulAccessCount;
}

STDMETHODIMP CObjectFeatureScript2::HelpInfo (LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return RunGetDescription (pBuffer, ulLen);
}

STDMETHODIMP CObjectFeatureScript2::Reset(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

// *** BasicScript-Umsetzung ***
	HRESULT hr = RunReset();
	if (SUCCEEDED(hr))
		// ZugriffsCount für Count zählen
		m_ulAccessCount ++;
	return hr;
}
STDMETHODIMP CObjectFeatureScript2::Uninstall()
{
// *** BasicScript-Umsetzung ***
	return  RunUninstall();
}
STDMETHODIMP CObjectFeatureScript2::Install()
{
// *** BasicScript-Umsetzung ***
	return RunInstall();
}

STDMETHODIMP CObjectFeatureScript2::Eval(LONG lONr, LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten)
{			
	AFX_MANAGE_STATE(AfxGetAppModuleState());
// *** BasicScript-Umsetzung ***
	return RunEvaluation(lONr, pFeatureName, ulLen, pulWritten);
}

STDMETHODIMP CObjectFeatureScript2::Cumulation(LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
// *** BasicScript-Umsetzung ***
	return RunCumulation(pFeatureName, ulLen, pulWritten);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Runningfunktionen für Scriptabarbeitung
HRESULT  CObjectFeatureScript2::RunEvaluation(LONG lONr, LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten)
{
	ASSERT(0 < ulLen);
	ASSERT(NULL != pFeatureName);
	ASSERT(0 != lONr);

HRESULT hr = S_OK;
BSPARAM BSParams;
LPVOID lpVoid = NULL;
ebVARIANT vString;

	if (pulWritten) *pulWritten = 0;

	try	{
	W_DGeoObject IObj;

		{// Dokument geben lassen
		W_DDocument IDoc;		
		
			THROW_FAILED_HRESULT(GetDocument (IDoc.ppi()));

		// Objekt geben lassen
			THROW_FAILED_HRESULT(ConvertLongToObject (lONr, IDoc, IObj.ppi()));
		}

	// Anlegen der Parameterwerte
		BSParams.pTypes = new ebPARAM[2];
		BSParams.pValues = new LPVOID[2];

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_VARIANT ;//| TYP_MODSPARM
		BSParams.pTypes -> szExtType[0] = '\0';
		BSParams.pValues[0] = (LPVOID)&vString;
	
	// erster Param: Objekt, für das Featurewert berechnet werden soll
		(BSParams.pTypes + 1) -> wType = TYP_APPOBJECT;
		strcpy ((BSParams.pTypes + 1) -> szExtType, "GeoObject");
	
	ebDWORD dw = (ebDWORD)(_DGeoObject *)IObj;
	
		BSParams.pValues[1] = (LPVOID)&dw;	// Adresse des Object-Pointers übergeben
	
	// EntryString laden
	CString strEntryName;
	
		if (!::LoadString(strEntryName, IDS_EVAL)) 
			_com_issue_error(E_OUTOFMEMORY);
	
	// eigentliche Ausführung
		THROW_FAILED_HRESULT(Run (strEntryName, &BSParams, 1, &lpVoid, TYP_STRING)); // Params

		hr = S_FALSE;	// erstmal false setzen			
		if (lpVoid)
		{
			if (ulLen > strlen((LPSTR)lpVoid))
			{
				strcpy(pFeatureName, (LPSTR)lpVoid); 		
				if (pulWritten) *pulWritten = strlen((LPSTR)lpVoid);
			}
			hr = S_OK;
		}
	}
	catch (bad_alloc)
	{
		hr = E_OUTOFMEMORY; 
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}	

	if (lpVoid) CoTaskMemFree(lpVoid);
	if (BSParams.pTypes) delete BSParams.pTypes; BSParams.pTypes = NULL;
	if (BSParams.pValues) delete BSParams.pValues; BSParams.pValues = NULL;

	return hr;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Runningfunktionen für Scriptabarbeitung
HRESULT CObjectFeatureScript2::RunGetDescription (LPSTR pBuffer, ULONG ulLen)
{
	ASSERT(0 < ulLen);
	ASSERT(NULL != pBuffer);

HRESULT hr = S_OK;
BSPARAM BSParams;
LPVOID lpVoid = NULL;
ebVARIANT vString;

	try	{
	// Function Description() As Variant
	ebPARAM Pars[1];		// Anlegen der Parameterwerte
	LPVOID ParValues[1];

		BSParams.pTypes = Pars;
		BSParams.pValues = ParValues;

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_VARIANT;
		BSParams.pTypes -> szExtType[0] = '\0';
		BSParams.pValues[0] = (LPVOID)&vString;

	// eigentliche Ausführung
		if (SUCCEEDED(Run (_T("Description"), &BSParams, 0, &lpVoid, TYP_STRING))) {
			if (NULL == lpVoid)	
				hr = S_FALSE;
			else {
			int iToCopy = min (ulLen-1, (ULONG)strlen ((LPCSTR)lpVoid));

				strncpy (pBuffer, (LPCSTR)lpVoid, iToCopy);
				pBuffer[iToCopy] = '\0';
				hr = S_OK;
			} 
		} else {
		// 'Description' nicht gegeben
		CString strName;

			strName.Format (IDS_DEFAULTDESCRIPTION, (LPCSTR)m_strScriptName);

		int iToCopy = min(ulLen-1, (ULONG)strName.GetLength());

			strncpy (pBuffer, strName, iToCopy);
			pBuffer[iToCopy] = '\0';
			hr = S_OK;
		}
	}
	catch (bad_alloc)
	{
		hr = E_OUTOFMEMORY; 
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}	

	if (lpVoid) CoTaskMemFree(lpVoid);

	return hr;
}

HRESULT  CObjectFeatureScript2::RunCount (ULONG *pulCount)
{
HRESULT hr = S_OK;
BSPARAM BSParams;

	*pulCount = NULL;
	try	{
	// Anlegen der Parameterwerte
	ebPARAM Pars[1];
	LPVOID ParValues[1];

		BSParams.pTypes = Pars;
		BSParams.pValues = ParValues;

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_LONG;
		BSParams.pTypes -> szExtType[0] = '\0';
		BSParams.pValues[0] = (LPVOID)pulCount;	// Adresse des String-Pointers übergeben

	// EntryString laden
	CString strCount;
	
		if (!::LoadString(strCount, IDS_COUNT)) 
			_com_issue_error(E_OUTOFMEMORY);

	// eigentliche Ausführung
		hr = Run (strCount, &BSParams); // Params
	}
	catch (bad_alloc)
	{
		hr = E_OUTOFMEMORY; 
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}	
	return hr;
}

HRESULT CObjectFeatureScript2::RunPropertyFlags (DWORD *pulProps)
{
HRESULT hr = S_OK;
BSPARAM BSParams;

	*pulProps = 0L;
	try	{
	// Anlegen der Parameterwerte
	ebPARAM Pars[1];
	LPVOID ParValues[1];

		BSParams.pTypes = Pars;
		BSParams.pValues = ParValues;

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_LONG ;
		BSParams.pTypes -> szExtType[0] = '\0';
		BSParams.pValues[0] = (LPVOID)pulProps;

	// eigentliche Ausführung
		hr = Run (TEXT("PropertyFlags"), &BSParams); // Params
	}
	catch (bad_alloc)
	{
		hr = E_OUTOFMEMORY; 
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}	
	return hr;
}

HRESULT CObjectFeatureScript2::RunReset()
{
// Nur EntryString laden
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_RESET)) 
		return E_OUTOFMEMORY;

	return Run(strEntryName);		// keine Parameter
}

HRESULT CObjectFeatureScript2::RunInstall()
{
// Nur EntryString laden
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_INSTALL)) 
		return E_OUTOFMEMORY;

// ZugriffsCount Init.
	m_ulAccessCount = 0;
	return Run(strEntryName);		// keine Parameter
}

HRESULT CObjectFeatureScript2::RunUninstall()
{
// Nur EntryString laden
CString strEntryName;

	if (!::LoadString(strEntryName, IDS_UNINSTALL)) 
		return E_OUTOFMEMORY;

// ZugriffsCount zurücksetzen
	m_ulAccessCount = 0;

// keine Parameter
HRESULT hr = Run(strEntryName);

	DELETE_OBJ(m_pScript);		// Auf jeden Fall Script zerlegen
	return hr;
}

HRESULT CObjectFeatureScript2::RunCumulation(LPSTR pFeatureName, ULONG ulLen, ULONG *pulWritten)
{
	ASSERT(0<ulLen);
	ASSERT(pFeatureName);

HRESULT hr = S_OK;
BSPARAM BSParams;
LPVOID lpVoid = NULL;
ebVARIANT vString;

	if (pulWritten) *pulWritten = 0;
	try	{
	ebPARAM Pars[1];
	LPVOID ParValues[1];

		BSParams.pTypes = Pars;
		BSParams.pValues = ParValues;

	// Returnwert, Eigenschaftswert
		BSParams.pTypes -> wType = TYP_VARIANT;
		BSParams.pTypes -> szExtType[0] = '\0';
		BSParams.pValues[0] = (LPVOID)&vString;	

	// EntryString laden
	CString strEntryName;

		if (!::LoadString(strEntryName, IDS_CUMULATION)) 
			_com_issue_error(E_OUTOFMEMORY);
	
	// eigentliche Ausführung
		THROW_FAILED_HRESULT(Run (strEntryName, &BSParams, 0, &lpVoid, TYP_STRING)); // Params

		hr = S_FALSE;// erstmal fals setzen			
		if (lpVoid)
		{
			if (ulLen > strlen((LPSTR)lpVoid))
			{
				strcpy (pFeatureName, (LPSTR)lpVoid); 		
				if (pulWritten) *pulWritten = strlen((LPSTR)lpVoid);
			}
			hr = S_OK;
		}
	}
	catch (bad_alloc)
	{
		hr = E_OUTOFMEMORY; 
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}	

	if (lpVoid) CoTaskMemFree(lpVoid);
	return hr;
}


//
// *** konvertieren ObjNr -> Object***
//
HRESULT CObjectFeatureScript2::ConvertLongToObject (long lObjNr, _DDocument *pIDoc, _DGeoObject **ppIObj)
{
	ASSERT(pIDoc);
	ASSERT(lObjNr > 0);		// !! Objektnummer immer größer 0

	if (pIDoc == NULL) return E_POINTER;
	if (lObjNr <= 0) return E_INVALIDARG; 

HRESULT hr = S_OK;

	try {
	VARIANT vObj;
	VARIANT vMode;
			
		V_VT(&vObj)  = VT_I4;
		V_I4(&vObj)  = lObjNr;
		V_VT(&vMode) = VT_I2;
		V_I2(&vMode) = GEOOBJECTMODE_Get;

	// Übergebe Objektnummer, return IUnknown des Objekts als Variant
	W_DGeoObject IGO;

		THROW_FAILED_HRESULT(pIDoc -> GetObject(vObj, vMode, IGO.ppi()));
		*ppIObj = IGO.detach();
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}

	return hr;
}

HRESULT CObjectFeatureScript2::GetDocument (_DDocument **ppIDoc)
{
	HRESULT hr = S_OK;

	try
	{
	WGetTRiASApplication IGA;

	// von OLE_Erweiterung IGetAppl. geben lassen
		THROW_FAILED_HRESULT(g_pTE -> m_pXtnSite -> GetXtension (
										CLSID_OleAutoExtension, 
										IID_IGetTRiASApplication, 
										(LPVOID *)IGA.ppi()));

	// Applikationsobjekt-Dispatchinterface an sich geben lassen
	W_DApplication IA; 

		THROW_FAILED_HRESULT(IGA -> GetApplication(IID_DApplication, IA.ppv()));

	W_DDocument ID;

		THROW_FAILED_HRESULT(IA -> get_ActiveDocument(ID.ppi()));
		*ppIDoc = ID.detach();
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}

	return hr;
}

HRESULT CObjectFeatureScript2::SetRunTimeErrorInfo(CebThread  & Thread)
{
LPSTR lpstr = NULL;

	try
	{
		THROW_FAILED_HRESULT(g_pBSE -> CreateRunTimeErrorDebugger(m_strScriptName));

	// Wird gerufen, wenn Laufzeitfehler auftritt
		Thread.SetRuntimeErrorProc(&OnObjFeatRuntimeError, 0);		
	}
	catch (_com_error &e)
	{
		if (lpstr)	CoTaskMemFree(lpstr), lpstr = NULL;
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CObjectFeatureScript2::GetInstance(CebInstance **ppebInstance)
{
	*ppebInstance = NULL;

	CMacroScriptExtension *pExt = g_pBSE;
	ASSERT(NULL != pExt);

	CebInstance *pebInstance = &(pExt -> ebInst());
	ASSERT(NULL != pebInstance);

	if (NULL == pebInstance) return E_POINTER;

	*ppebInstance = pebInstance;

	return S_OK;
}

HRESULT CObjectFeatureScript2::GetCode(ebHCODE *phCode)
{
	HRESULT hr = S_OK;
	ebSaveStruct SS;

	memset(&SS, 0, sizeof(ebSaveStruct));

	*phCode = NULL;
	
	try
	{
	// ObjectFeatureScript kann ohne ScriptProperty nicht leben
	// Query nach IScriptProperty, um Code zu bekommen
	// Code muss vordem geladen worden sein
	WScriptProperty ISP((IObjectProperty *)this);

	/////////////////////////////////
	// Kopieren der Daten
		THROW_FAILED_HRESULT(ISP -> Get(&SS));  
		if (SS.hCode) *phCode = SS.hCode;
	}
	catch (_com_error &e)
	{
		if (SS.hCode) CoTaskMemFree(SS.hCode); SS.hCode = NULL;
		hr = _COM_ERROR(e);
	}	

// Brauche nur Code
	if (SS.pText) CoTaskMemFree(SS.pText); SS.pText = NULL;
	MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);

	return hr;
}

HRESULT CObjectFeatureScript2::GetText(LPSTR *pp)
{
HRESULT hr = S_OK;
ebSaveStruct SS;

	memset(&SS, 0, sizeof(ebSaveStruct));

	*pp = NULL;
	try
	{
	// ObjectFeatureScript kann ohne ScriptProperty nicht leben
	// Query nach IScriptProperty, um Code zu bekommen
	// Code muss vordem geladen worden sein
	WScriptProperty ISP((IObjectProperty *)this);

	/////////////////////////////////
	// Kopieren der Daten
		THROW_FAILED_HRESULT(ISP -> Get(&SS));
		if (SS.pText) *pp = SS.pText;
	}
	catch (_com_error &e)
	{
		if (SS.pText) CoTaskMemFree(SS.pText); SS.pText = NULL;
		hr = _COM_ERROR(e);
	}

// Brauche nur Text
	if (SS.hCode) CoTaskMemFree(SS.hCode); SS.hCode = NULL;
	MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);

	return hr;
}

HRESULT CObjectFeatureScript2::GetScript(LPCSTR lpcstrName)
{
	CebInstance *pebInstance = NULL;
	ebHCODE hCode = NULL;
	HRESULT hr = S_OK;

	if (NULL != m_pScript) return S_FALSE;

	try
	{
	// Instanz aus Extension geben lassen
		THROW_FAILED_HRESULT(GetInstance(&pebInstance));

		THROW_FAILED_HRESULT(GetCode(&hCode));
		ASSERT(NULL != hCode);

	char Buffer[MAXSTRLENGTH];
	
		m_pScript = new CebScript(pebInstance, hCode, Buffer, MAXSTRLENGTH);
		if (m_pScript -> Create()) 
			_com_issue_error(E_FAIL);
	
	// Brauch ich nicht mehr
		m_pScript -> SetErrorBuffer(NULL, 0);
		ASSERT(m_pScript -> GetHandle());			
		if (NULL == m_pScript -> GetHandle()) 
			_com_issue_error(E_HANDLE);

		CoTaskMemFree(hCode); hCode = NULL;
	
	// auch gleich Home setzen
		THROW_FAILED_HRESULT(SetHomeDir(pebInstance, lpcstrName));
	}
	catch (bad_alloc)
	{
		if (m_pScript) delete m_pScript, m_pScript = NULL;
		if (hCode) CoTaskMemFree(hCode); hCode = NULL;
		hr = E_OUTOFMEMORY;
	}
	catch (_com_error &e)
	{
		if (m_pScript) delete m_pScript, m_pScript = NULL;
		if (hCode) CoTaskMemFree(hCode); hCode = NULL;
		hr = _COM_ERROR(e);
	}

	return hr;
}

void CObjectFeatureScript2::UnLoadRelScripts()
{
	if (NULL != m_pRelScripts) delete m_pRelScripts;
	m_pRelScripts = NULL;
}

HRESULT CObjectFeatureScript2::LoadRelatedWhileRunning()
{
	return m_pRelScripts -> Add(m_strScriptName);
}
HRESULT CObjectFeatureScript2::UnLoadRelatedAfterRunning()
{
	return m_pRelScripts -> Delete(m_strScriptName);
}

HRESULT CObjectFeatureScript2::LoadRelScripts()
{
	HRESULT hr = S_OK;

	try 
	{
		if (NULL == m_pRelScripts)
		{	
			m_pRelScripts = new CRelScripts();

		WObjectManagement IObjManagement;

			THROW_FAILED_HRESULT(GetObjectFeatureScripts(IObjManagement.ppi()));

		WStreamInfo ISI;

			THROW_FAILED_HRESULT(GetInfoObjFeatureScripts(ISI.ppi()));
			m_pRelScripts -> SetStorageManagement(IObjManagement, ISI); 
		}

	// Diese Related-Scripts für RequestorProc setzen
	CebInstance *pInst = NULL;

		THROW_FAILED_HRESULT(GetInstance(&pInst));
		pInst -> SetRequestorProc(RequestorProc, (LPARAM)m_pRelScripts);
		pInst -> SetLinkOptions(LO_CALLREQUESTORBEFORE);
	} 
	catch (bad_alloc) 
	{
		UnLoadRelScripts();
		hr = E_OUTOFMEMORY;
	}		
	catch (_com_error &e)
	{
		UnLoadRelScripts();
		hr = _COM_ERROR(e);
	}		

	return hr;
}

HRESULT CObjectFeatureScript2::GetObjectFeatureScripts(IObjectManagement **ppIObj)
{
	IObjectManagement *pIObj = g_pBSE -> GetObjectFeatureScripts();
	ASSERT(pIObj);
	if (pIObj) 
	{
		*ppIObj = pIObj;
		(*ppIObj) -> AddRef();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CObjectFeatureScript2::GetInfoObjFeatureScripts(IStreamInfo **ppISI)
{
	IStreamInfo *pISI = g_pBSE -> GetInfoObjFeatureScripts();
	ASSERT(pISI);
	if (pISI) 
	{
		*ppISI = pISI;
		(*ppISI) -> AddRef();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT  CObjectFeatureScript2::SetLong (CebThread & Thread, BOOL fBreak, BOOL fAuto, LPCSTR lpcstr)
{
	ASSERT(lpcstr);

	if (NULL == lpcstr) return E_POINTER;

	long lName = (long)(LPSTR)lpcstr;
	
	Thread.SetLong (SETLONG_BREAK, fBreak);		// BreakFlag voreinstellen
	Thread.SetLong (SETLONG_AUTO, fAuto);		// Auto voreinstellen
	Thread.SetLong (SETLONG_NAME, lName);		// Name voreinstellen
	Thread.SetLong (SETLONG_HPROJECT, reinterpret_cast<LONG>(DEX_GetDataSourceHandle()));		// Datenquelle voreinstellen
	Thread.SetLong (SETLONG_HINSTANCE, reinterpret_cast<LONG>(_Module.GetResourceInstance()));	

	return S_OK;
}

HRESULT CObjectFeatureScript2::SetEntryInfo(CebEntryInfo & EntryInfo, LPCSTR lpcstrEntry, BSPARAM * pPars, int iCountPar)
{
	ASSERT(lpcstrEntry);

	memset(&EntryInfo, 0, sizeof(CebEntryInfo));
	// Typ der Parameter setzen: 
	// Featurename
	EntryInfo.SetEntryName (lpcstrEntry);			
	EntryInfo.SetParamsCount (iCountPar);
	
	if (pPars) 
	{	
		if (iCountPar > 0)// Params setzen 
			EntryInfo.SetParams (&pPars -> pTypes[1]);			
		if (pPars -> pTypes[0].wType != 0) 
		{// Return setzen
			EntryInfo.SetMethodType (true);	// Funktion
			EntryInfo.SetRetType (&pPars -> pTypes[0]);
		}
	}
	return S_OK;
}

HRESULT CObjectFeatureScript2::Run (
	LPCSTR lpcstrEntryName, BSPARAM *pBSParams, int iCountPar, LPVOID *lplpExtVariant, ebWORD wExtVariantType)
{
HRESULT hr = S_OK;
HRESULT hrNoPropertyValue = S_OK;

	if (lplpExtVariant) *lplpExtVariant = NULL;

	try	{	
		// Script zu dieser Instanz und zu diesem Objekt gehörigen Code geben lassen
		hr = GetScript(m_strScriptName);// erzeugen m_pSript
		if (FAILED(hr)) _com_issue_error(hr);
		// Related geben lassen
		hr = LoadRelScripts();
		if (FAILED(hr)) _com_issue_error(hr);
		// RelatedScripts von geladenem Macro in Liste eintragen
		hr = LoadRelatedWhileRunning();
		if (FAILED(hr)) _com_issue_error(hr);
		// DebuggerHelper erzeugen
		hr = OnDemandDebugger (m_strScriptName, &m_pSuspendDeb);
		if (FAILED(hr)) _com_issue_error(hr);
	
	// *** EntryInfo setzen ***
	CebEntryInfo EntryInfo;
	CBSParamCopy BSParam (iCountPar, pBSParams);

		BSParam.RemoveModsParam();
		hr = SetEntryInfo(EntryInfo, lpcstrEntryName, BSParam, iCountPar);
		if (FAILED(hr)) _com_issue_error(hr);

	// *** EntryPoint überprüfen ***
		int iErr = ebCheckEntry (m_pScript -> GetHandle(), EntryInfo.GetEntryInfo());
		if (0 != iErr) _com_issue_error(E_NOTIMPL);

	// Thread erzeugen
		CebThread Thread(m_pScript -> GetHandle(), EntryInfo.GetEntryInfo());		
		if (Thread.Create(CREATETHREAD_EXTRA)) _com_issue_error(E_OUTOFMEMORY);	

	// Auto, Break, Name voreinstellen
		hr = SetLong (Thread, true, 0, m_strScriptName);					
		if (FAILED(hr)) _com_issue_error(hr);

	// Text für Debugger geben lassen (Laufzeitfehler ?)
	// Neuen Laufzeitdebugger-Creator erzeugen, wenn Tetxt vorhanden 
	// Callbackfunktion wird gerufen, wenn Laufzeitfehler auftritt
		hr = SetRunTimeErrorInfo(Thread);		
		if (FAILED(hr)) _com_issue_error(hr);

	// Param setzen
		hr = SetAllParams(Thread, pBSParams, iCountPar);
		if (FAILED(hr)) _com_issue_error(hr);		

		try {	// Zweiter try/Catch, damit ResetApplicationObjects _IMMER_ ausgeführt wird
		// Returnwerte testen
		// Routine rufen, bis die CallbackFunktion erfolgreich abgeschlossen wurde	
			hr = RunThread(Thread);
			if (FAILED(hr)) _com_issue_error(hr);

			hrNoPropertyValue = GetReturnParams (Thread, pBSParams, lplpExtVariant, wExtVariantType);
			if (FAILED(hrNoPropertyValue)) _com_issue_error(hrNoPropertyValue);
			// Params geben lassen
			hr = GetAllParams (Thread, pBSParams, iCountPar);
		} 
		catch (_com_error& e) {
			hr = _COM_ERROR(e);		// hr auf FAILED, dann DELETE_OBJ(m_pScript) unten
		}
	
	// das folgende muß _IMMER_ ausgeführt werden!
		ResetApplicationObjects (Thread, pBSParams, iCountPar);
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);// hr auf FAILED, dann DELETE_OBJ(m_pScript) unten
	}
	if (FAILED(hr)) DELETE_OBJ(m_pScript); 

// Debugger  und Related freigeben:
// muß hier geschehen, um auch IObjMan und IStreamInfo
// freigeben zu können. Freigeben der CObjectFeatureScript-Objekte, 
// sonst nicht möglich !!!
	DELETE_OBJ(m_pSuspendDeb);
	UnLoadRelScripts();

	if (S_FALSE == hrNoPropertyValue) // Keine Eigenschaft generiert
		hr = E_NOTIMPL;

	return hr;
}
// Debuggen ermöglichen
HRESULT CObjectFeatureScript2::OnDemandDebugger (LPCSTR lpcstr, CRunBreakPoint **ppSuspendDeb)
{
	ASSERT(lpcstr);
	ASSERT(ppSuspendDeb);
	if (NULL == lpcstr || NULL == ppSuspendDeb) return E_POINTER;

	*ppSuspendDeb = NULL;
	try {
		CRunBreakPoint *pSuspendDeb = NULL;
		pSuspendDeb = new CRunBreakPoint (lpcstr);
		*ppSuspendDeb = pSuspendDeb;
	} catch (bad_alloc) {
		return E_OUTOFMEMORY;
	}
	return S_OK;
}
// Globale Funktion, wird überall gebraucht
HRESULT CObjectFeatureScript2::RunThread(CebThread & Thread)
{
CHandleMacroTrayIcons TrayIcons;		// evtl. TrayIcons anzeigen
LONG lThreadState = TS_IDLE;

	do {
		Thread.Start();
		
		lThreadState = Thread.GetState();
		if (lThreadState == TS_SUSPENDED) {
		// Breakpoint in CallBackfunktion ausgelöst
		WObjectManagement IObjManagement;
		HRESULT hr = GetObjectFeatureScripts (IObjManagement.ppi());
			
			if (FAILED(hr)) return hr;

		WStreamInfo ISI;
		
			hr = GetInfoObjFeatureScripts(ISI.ppi());
			if (FAILED(hr)) return hr;

			hr = m_pSuspendDeb -> OnDemandBreakpoint (m_pScript, &Thread, IObjManagement, ISI); //, &m_EI);
			if (FAILED(hr)) return hr;

		// RAUS !!!, Ansonsten wird immer gleicher Thread angeworfen, 
		// ist immer SUSPENDED ausserhalb des Debuggers 
			break; 
		}
	} while (lThreadState != TS_IDLE);

// Fehler aufgetreten
	if (Thread.GetErrorNumber()) 
		return E_ABORT;
	return S_OK;
}

HRESULT SetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar)
{
	for (int i = 1; i <= iCountPar; i++)
	{
		if (NULL != pBSParams && pBSParams -> pValues && pBSParams -> pTypes)
		{
			if (!SetParam(rThread, i, pBSParams -> pTypes[i], pBSParams -> pValues[i]))	return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT GetReturnParams (CebThread & rThread, BSPARAM *pBSParams, LPVOID *lplpExtVariant, ebWORD wExtVariantType)
{
	HRESULT hr = S_OK;

	if (NULL != pBSParams && 
		NULL != pBSParams -> pTypes && 
		pBSParams -> pValues && 
		pBSParams -> pTypes[0].wType != 0) 
	{
		if (!GetParam (rThread, 0, pBSParams -> pTypes[0], pBSParams -> pValues[0], true)) 
			return E_FAIL;			

		if (wExtVariantType) {
		// <<-- #HK: Objekteigenschaft existiert nicht für dieses Objekt
			hr = GetValueVariant (rThread, *((ebVARIANT *)pBSParams -> pValues[0]), lplpExtVariant, wExtVariantType);
			if (FAILED(hr)) return hr;
		}
	}

	return hr;
}

HRESULT GetAllParams (CebThread & rThread, BSPARAM *pBSParams, int iCountPar)
{
	for (int i = 1; i <= iCountPar;  i++) 
	{
		if (NULL != pBSParams && NULL != pBSParams -> pTypes && 
			NULL != pBSParams -> pValues && pBSParams -> pTypes[i].wType & TYP_MODSPARM) 
		{
			if (!GetParam (rThread, i, pBSParams -> pTypes[i], pBSParams -> pValues[i], true, true)) 
				return E_FAIL;
		}
	}

	return S_OK;
}

HRESULT ResetApplicationObjects (CebThread & rThread, BSPARAM *pBSParams, int iCountPar)
{
	// das folgende muß _immer_ ausgeführt werden!
	for (int i = 0; i <= iCountPar; i++) 
	{// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
		if (pBSParams && pBSParams -> pTypes && TYP_APPOBJECT == pBSParams -> pTypes[i].wType) 
		{
			DWORD dw = 0L;
			if (!SetParam (rThread, i, pBSParams -> pTypes[i], &dw)) return E_FAIL;
		}
	}

	return S_OK;
}

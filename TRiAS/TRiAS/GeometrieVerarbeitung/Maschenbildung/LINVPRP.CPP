// PropertyAction, welche Linienobjekte verbindet
// File: LINVPRP.CPP

#include "pheader.h"		// vorübers. Header
#include "resource.h"		// Resource-Konstanten

//	TRIAS-Header
#include <ospace/com/iterenum.h>
#include <IGeometr.hxx>		// IObjektGeometrie

//	STL-Header
#include <ospace/std/list>	// list

//	allgem. Header
#include <float.h>			// DBL_MIN, DBL_MAX
//#include <int64.h>			// LARGE

// GUID-Header
#include <xtsnguid.h>
#include <objgguid.h>		// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include <IPropSeq.hxx>

#include "rsltguid.h"		// CLSID_ResultPropAction
#include "doppguid.h"		// CLSID_FindDoubledObjects
#include "verguid.h"		// CLSID_VerschnittPropAct	
#include <triashelper.h>
#include <initguid.h>
//#define _TriasTLB_H_           
//#include <dirisole.h>		// CLSID_DataTransferObject
#include "linaguid.h"
#include "linvguid.h"

#include <hpp/propactb.hpp>	// Basisklasse			// fje
#include <hpp/datahelp.hpp>	// Get/SetEnumLongData

#include "objkante.hpp"		// CObjektKante
#include "ParamDlg.hpp"		// DialogPage

#include "objstatp.hpp"		// CResultPropAction
#define _NO_OBJECT_GEOMETRIE
#include "geoobjs.hpp"		// CGeometrieObject	
#include "doppgeop.hpp"		// CDoppGeoPropAction	
#include "verschnt.hpp"		// CVerschnittPropAct	
#include "imaschen.h"
#include "imaschen.hpp"
#include "linver.hpp"		// CLinVerExtension
	
#include "linvprp.hpp"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////
//	Konstanten
const short sParamCount = 5;
const UINT uiMaxStreamSize = sizeof (double) + (sParamCount * sizeof (LONG));	// max. Streamgröße

//  externe Variablen
extern const char ExtensionName[];		// Name der Erweiterung


///////////////////////////////////////////////////////////////////////////////
// ClassFactory/registry support
class CResultPropAction;
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_LinienVerfolgungsPropAct, CLinVerPropAct)
	OBJECT_ENTRY(CLSID_ResultPropAction, CResultPropAction)
	OBJECT_ENTRY(CLSID_FindDoubledObjects, CDoppGeoPropAction)
	OBJECT_ENTRY(CLSID_VerschnittPropAct, CVerschnittPropAct) 
	OBJECT_ENTRY(CLSID_LinienVerfolgung, CLinVerExtension)
	OBJECT_ENTRY(CLSID_ExtLinienVerfolgung, CMaschenBildungI)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;
}

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum


CLinVerPropAct :: CLinVerPropAct (void)
{
	m_pCfgDlg = NULL;
	m_bIsDirty = FALSE;
	m_bIsInitialized = FALSE;
	m_bHasInitData = FALSE;
	m_hDex = NULL;
	m_hResult = NOERROR;

	m_dFuzzy = 0.0;
	m_bOutputMerkmal = m_bUnionMaschen = m_bUnionLines = TRUE;
	m_bDeleteOldLines = FALSE;
	m_bMarkObjects = FALSE;		// #HK971218

	try 
	{
	//	Erweiterung laden
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		if (m_hDex = DEX_ExternalLoadExtensionEx (le))
			VERIFY (m_strDesc.LoadString(IDS_HELPDESC_LINVER));
	} 
	catch (CException *e)
	{
		m_hResult = E_OUTOFMEMORY;
		e -> ReportError ();
		e -> Delete ();
	}
}

CLinVerPropAct :: ~CLinVerPropAct (void)
{
//	Dialog löschen
	DELETE_OBJ (m_pCfgDlg);
}

void CLinVerPropAct :: FinalRelease (void)
{
	if (m_hDex)
	{
	//	Erweiterung entladen
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CLinVerPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
			ULONG ulLen= min (wLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return (m_hResult = E_FAIL);
	}

//	wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE;
	}

return NOERROR;
}

STDMETHODIMP CLinVerPropAct::HelpInfo (LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL == m_hDex)
			return E_FAIL;

		if (NULL != pBuffer && ulLen > 0) {
		// Beschreibung übergeben
		WORD wLen = min ((WORD) ulLen-1, m_strDesc.GetLength());

			strncpy (pBuffer, m_strDesc, wLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return (m_hResult = E_FAIL);
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CLinVerPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
	try 
	{
		if (NULL == m_hDex)
			return E_FAIL;

	//	zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		m_pCfgDlg = CParamDialog::CreateInstance (this);

		if (NULL == m_pCfgDlg) 
			_com_issue_error (E_OUTOFMEMORY);
		
		if (m_bHasInitData)
		{
			m_pCfgDlg -> SelectFuzzy (m_dFuzzy);
			m_pCfgDlg -> SelectUnionMaschen (m_bUnionMaschen);
			m_pCfgDlg -> SelectUnionLines (m_bUnionLines);
			m_pCfgDlg -> SelectDeleteOldLines (m_bDeleteOldLines);
			m_pCfgDlg -> SelectOutputMerkmal (m_bOutputMerkmal);
			m_pCfgDlg -> SelectMarkObjects (m_bMarkObjects);		// #HK971218
		}
	
		HPROPSHEETPAGE hPSP = NULL;
		PROPSHEETPAGE psp;

		memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		if (pcDesc && *pcDesc)
		{
			psp.dwFlags |= PSP_USETITLE;
			psp.pszTitle = pcDesc;
		}

		hPSP = CreatePropertySheetPage (&psp);
		
		if (NULL == hPSP)
			_com_issue_error (E_OUTOFMEMORY);
	
		if ( !IsNoShow() ) {	//fje
			if (!(*lpfnAddPage) (hPSP, lParam))  
				return E_FAIL;
		}
		if (NULL != puiCnt)		//fje
			*puiCnt = IsNoShow() ? 0 : 1;
	} 
	catch (_com_error& hr_result) 
	{
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) 
			*puiCnt = 0;
		return (m_hResult = _COM_ERROR (hr_result));
	}
	
	return NOERROR;
}

STDMETHODIMP CLinVerPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL == m_hDex)
		return E_FAIL;

	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CLinVerPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
	if (NULL == pIDataObj)
		return E_POINTER;
		
	if (NULL == m_hDex)
		return E_FAIL;

	COM_TRY {
	WEnumObjectsByNumber IEnumObj;
	HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

		if (FAILED(hr)) 
			_com_issue_error (hr);

		ASSERT (NULL != m_pCfgDlg);

	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED(GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED(vData.ChangeType (VT_I4))) 
		{
			m_pCfgDlg -> SetDataSource (reinterpret_cast<HPROJECT>(V_I4(&vData)));
		}

	//	Undo beginnen
	CString strText;

		VERIFY (strText.LoadString(IDS_UNDO_TEXT_UNION));
		DEX_BeginUndoLevel ((const char*)strText);

		m_hResult = m_pCfgDlg -> SetEnumLONG (IEnumObj);

	//	Undo auswerten
		if (SUCCEEDED (m_hResult))
			DEX_EndUndoLevel ();
		else
			DEX_CancelUndoLevel (TRUE);
	
	} COM_CATCH;
	return m_hResult;
}

STDMETHODIMP CLinVerPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	HRESULT hrr = S_OK;

	try 
	{
		if (NULL == ppDataObj)
			return E_POINTER;
		
		if (NULL == m_hDex)
			return E_FAIL;

		WEnumObjectsByNumber WEnumObj;
		hrr = m_pCfgDlg -> GetEnumLONG (WEnumObj);
	
		if (S_FALSE == hrr)		//#WM990624
			return hrr;

	//	DataObject generieren
		*ppDataObj = NULL;

		WDataObject IDO;
		HRESULT hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER,
									   IID_IDataObject, IDO.ppv()); 
		if (FAILED(hr)) 
			_com_issue_error (hr);

		hr = SetEnumLONGData (WEnumObj, IDO);
		if (FAILED(hr)) 
			_com_issue_error (hr);
	
		*ppDataObj = IDO.detach();

	}
	catch (_com_error& hr_result) 
	{
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return (m_hResult = _COM_ERROR (hr_result));
	}

	if (S_OK == hrr)
	{
	//	Parameter speichern
		m_dFuzzy = m_pCfgDlg -> GetFuzzy ();
		m_bUnionMaschen = m_pCfgDlg -> GetUnionMaschen ();
		m_bUnionLines = m_pCfgDlg -> GetUnionLines ();
		m_bDeleteOldLines = m_pCfgDlg -> GetDeleteOldLines ();
		m_bOutputMerkmal = m_pCfgDlg -> GetOutputMerkmal ();
		m_bMarkObjects = m_pCfgDlg -> GetMarkObjects();		// #HK971218

		DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben
	}

	return hrr;
}

///////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CLinVerPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_LinienVerfolgungsPropAct;
	return NOERROR;
}

//	IPersistStreamInit method
STDMETHODIMP CLinVerPropAct::InitNew (void)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;
	m_bHasInitData = FALSE;

	m_dFuzzy = 0.0;
	m_bOutputMerkmal = m_bUnionMaschen = m_bUnionLines = TRUE;
	m_bDeleteOldLines = FALSE;
	m_bMarkObjects = FALSE;		// #HK971218

	return NOERROR;
}

// IPersistStream methods
STDMETHODIMP CLinVerPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CLinVerPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = uiMaxStreamSize;
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CLinVerPropAct::Load (LPSTREAM pStm)
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (m_bIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) 
		return hr;

//	dann selektierte Info der letzten Auswahl
	double dFuzzy = 0.0;
	LONG lUnionMaschen = 1L;
	LONG lUnionLines = 1L;
	LONG lDeleteOldLines = 0L;
	LONG lOutputMerkmal = 1;
	LONG lMarkObjects = 0L;		// #HK971218
	
	hr = pStm -> Read (&dFuzzy, sizeof(double), NULL);
	if (FAILED(hr)) return hr;
	
	hr = pStm -> Read (&lUnionMaschen, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&lUnionLines, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&lDeleteOldLines, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	hr = pStm -> Read (&lOutputMerkmal, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

// #HK971218
ULONG lReadBytes = 0L;

	if (SUCCEEDED(pStm -> Read (&lMarkObjects, sizeof(LONG), &lReadBytes)) && lReadBytes == sizeof(LONG))
		m_bMarkObjects = lMarkObjects ? TRUE : FALSE;

	if (NULL == m_pCfgDlg) {
	//	Dialog ist noch nicht initialisiert
		m_dFuzzy = dFuzzy;
		m_bUnionMaschen = lUnionMaschen ? TRUE : FALSE;
		m_bUnionLines = lUnionLines ? TRUE : FALSE;
		m_bDeleteOldLines = lDeleteOldLines ? TRUE : FALSE;
		m_bOutputMerkmal = lOutputMerkmal ? TRUE : FALSE;
		m_bHasInitData = TRUE;
	} else {
		m_pCfgDlg -> SelectFuzzy (dFuzzy);
		m_pCfgDlg -> SelectUnionMaschen (lUnionMaschen ? TRUE : FALSE);
		m_pCfgDlg -> SelectUnionLines (lUnionLines ? TRUE : FALSE);
		m_pCfgDlg -> SelectDeleteOldLines (lDeleteOldLines ? TRUE : FALSE);
		m_pCfgDlg -> SelectOutputMerkmal (lOutputMerkmal ? TRUE : FALSE);
		m_pCfgDlg -> SelectMarkObjects (m_bMarkObjects);	// #HK971218
	}

	m_bIsInitialized = TRUE;
	m_bIsDirty = FALSE;
	return NOERROR;
}

STDMETHODIMP CLinVerPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
//	zuerst Bezeichner wegschreiben
	HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

//	dann selektierte Info der letzten Auswahl: Toleranz
	hr = pStm -> Write (&m_dFuzzy, sizeof(double), NULL);
	if (FAILED(hr)) return hr;

//	Maschen vereinigen
	LONG lTemp = m_bUnionMaschen ? TRUE : FALSE;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Linien vereinigen
	lTemp = m_bUnionLines ? TRUE : FALSE;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	alten Linien löschen
	lTemp = m_bDeleteOldLines ? TRUE : FALSE;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

//	Merkmal ausgeben
	lTemp = m_bOutputMerkmal ? TRUE : FALSE;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

// Objekte kennzeichnen (#HK971218)
	lTemp = m_bMarkObjects ? TRUE : FALSE;
	hr = pStm -> Write (&lTemp, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	if (fClearDirty) m_bIsDirty = FALSE;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CLinVerPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == m_hDex)
		return E_FAIL;

	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

//fje
/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CLinVerPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
 HRESULT hr;
//	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

// sonstige Werte Analysieren
CComVariant vOption;
	hr = pBag -> Read (CComBSTR("Fuzzy"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_R8)))
		m_dFuzzy = V_R8(&vOption) ? true : false;

	hr = pBag -> Read (CComBSTR("BuildA"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_BOOL)))
		m_bUnionMaschen = V_BOOL(&vOption) ? true : false;

	hr = pBag -> Read (CComBSTR("BuildL"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_BOOL)))
		m_bUnionLines = V_BOOL(&vOption) ? true : false;

	hr = pBag -> Read (CComBSTR("Delete"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_BOOL)))
		m_bDeleteOldLines = V_BOOL(&vOption) ? true : false;

	hr = pBag -> Read (CComBSTR("Inherit"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_BOOL)))
		m_bOutputMerkmal = V_BOOL(&vOption) ? true : false;

	hr = pBag -> Read (CComBSTR("Mark"), &vOption, pLog);
	if (S_OK == hr && SUCCEEDED(vOption.ChangeType (VT_BOOL)))
		m_bMarkObjects = V_BOOL(&vOption) ? true : false;
			
	m_bHasInitData = 1;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CLinVerPropAct::SetDirty (BOOL fDirty) 
{ 
	m_bIsDirty = fDirty; 
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen des Verweises auf die Optionenseite
HRESULT CLinVerPropAct::EnsureOptionsIF()
{
//	if (m_wOperOptions.IsValid())
//		return S_OK;
//
//	if (!m_mkOperOptions.IsValid())
//		return E_UNEXPECTED;
//
//	RETURN_FAILED_HRESULT(MkBindToObjectLocal(m_mkOperOptions, m_wOperOptions.ppi()));
	return S_OK;
}


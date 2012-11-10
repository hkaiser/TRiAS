// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.99 13:22:06 
//
// @doc
// @module PerfMonInstanceMapImpl.cpp | Declaration of the <c CPerfMonInstanceMapMgr> class

#include <Com/PerfMonInstanceMap.h>

namespace PerfMon {

///////////////////////////////////////////////////////////////////////////////
// keine Asserts bei THROW_FAILED_HRESULT
#if defined(_ASSERT_ON_THROW_FAILED_HRESULT)
#undef THROW_FAILED_HRESULT
#define THROW_FAILED_HRESULT(x)		{HRESULT __hr=(x);if(SUCCEEDED(__hr)){}else{_com_issue_error(__hr);}}	//lint --e(774)
#endif // defined(_ASSERT_ON_THROW_FAILED_HRESULT)

///////////////////////////////////////////////////////////////////////////////
// globaler PerfContext
__Interface<IPerfContext> g_PerfCtx;

///////////////////////////////////////////////////////////////////////////////
// Maintains a vector array of PERFINSTANCEDATA pointers. This can
// be used to generate a dynamic object map at run-time.

class CPerfMonInstanceMapMgr
{
private:
	typedef vector<const PERFINSTANCEDATA *> CPerfInstanceMapVector;

	CPerfInstanceMapVector m_vecPerfMonInstanceMap;
	PERFINSTANCEDATA *m_pPerfMonInstanceMap;

public:
	CPerfMonInstanceMapMgr();
	~CPerfMonInstanceMapMgr();

	void Add(const PERFINSTANCEDATA *pEntry);
	PERFINSTANCEDATA *GenerateMap();
};

///////////////////////////////////////////////////////////////////////////////
// local variable for terminating an object map.
static const PERFINSTANCEDATA __lastPerfMonInstanceEntry__[1] = { END_PERFINSTANCE_MAP() 

///////////////////////////////////////////////////////////////////////////////
// Initialise member variables
CPerfMonInstanceMapMgr::CPerfMonInstanceMapMgr()
{
	m_pPerfMonInstanceMap = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
CPerfMonInstanceMapMgr::~CPerfMonInstanceMapMgr()
{
	delete[] m_pPerfMonInstanceMap;
}

///////////////////////////////////////////////////////////////////////////////
// Adds an object map entry pointer to the vector array
void CPerfMonInstanceMapMgr::Add (const PERFINSTANCEDATA *pEntry)
{
	ATLTRY(m_vecPerfMonInstanceMap.push_back (pEntry));
}

///////////////////////////////////////////////////////////////////////////////
// Generates a contiguous map of all of the object map entries.
PERFINSTANCEDATA *CPerfMonInstanceMapMgr::GenerateMap()
{
	if (m_pPerfMonInstanceMap == NULL) {
		Add(__lastPerfMonInstanceEntry__);

	int iSize = m_vecPerfMonInstanceMap.size();

		ATLTRY(m_pPerfMonInstanceMap = new PERFINSTANCEDATA[iSize]);

		if (NULL != m_pPerfMonInstanceMap) {
			for (int iIndex = 0; iIndex < iSize; iIndex++)
				m_pPerfMonInstanceMap[iIndex] = *(m_vecPerfMonInstanceMap[iIndex]);
		}
	}
	return m_pPerfMonInstanceMap;
}

///////////////////////////////////////////////////////////////////////////////
// local pointer to a CPerfMonInstanceMapMgr
static CPerfMonInstanceMapMgr *pPerfMonInstanceMapMgr = NULL;

///////////////////////////////////////////////////////////////////////////////
// Creates (if necessary) the run-time instance manager, and adds the entry to it.
void RegisterPerfMonInstanceMapEntry (PERFINSTANCEDATA *pEntry)
{
	if(pPerfMonInstanceMapMgr == NULL) 
	{
		ATLTRY(pPerfMonInstanceMapMgr = new CPerfMonInstanceMapMgr);
	}

	if (NULL != pPerfMonInstanceMapMgr)
		pPerfMonInstanceMapMgr -> Add(pEntry);
}

///////////////////////////////////////////////////////////////////////////////
// delegates to the run-time object manager to get the object map.
const PERFINSTANCEDATA *GetPerfMonInstanceMap()
{
PERFINSTANCEDATA *pRunTimeMap = NULL;

	if (NULL != pPerfMonInstanceMapMgr)
		pRunTimeMap = pPerfMonInstanceMapMgr -> GenerateMap();

	if (NULL != pRunTimeMap)
		return pRunTimeMap;
	
	return __lastPerfMonInstanceEntry__;		// no entries at all
}

///////////////////////////////////////////////////////////////////////////////
// Cleans up an local CPerfMonInstanceMapMgr during shutdown
class CPerfMonInstanceMgrCaretaker
{
public:
	~CPerfMonInstanceMgrCaretaker()
	{
		DELETE_OBJ(pPerfMonInstanceMapMgr);
	}
};
static CPerfMonInstanceMgrCaretaker rtpmCaretaker;

///////////////////////////////////////////////////////////////////////////////
// Routinen für die Installation aller PerfCounter
static HRESULT InstallPerfCounters(HINSTANCE hInst, const PERFCOUNTERDATA *pPerfData, IPerfObject *pIObj)
{
	COM_TRY {
	// alle für dieses PerfObject zu installierenden Counter bearbeiten
		for (const PERFCOUNTERDATA *pActPerfData = pPerfData; NULL != pActPerfData -> pcoleName; pActPerfData++) 
		{
		CComBSTR bstrHelp, bstrDesc;

			_ASSERTE(0L != pActPerfData -> uiDesc && 0L != pActPerfData -> uiHelp);
			if (!bstrDesc.LoadString (hInst, pActPerfData -> uiDesc) || 
				!bstrHelp.LoadString (hInst, pActPerfData -> uiHelp)) 
			{
				_ASSERTE(FALSE);
				continue;
			}

		// counter im Kontext des PerfObjects neu erzeugen 
			THROW_FAILED_HRESULT(pIObj -> AddCounterDefinition (
				CComBSTR(pActPerfData -> pcoleName), bstrDesc, bstrHelp, 
				pActPerfData -> rgDetailLevel, pActPerfData -> lScale, 
				pActPerfData -> rgCounterType));
		}
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Instanzen für ein Counter-Objekt erzeugen
static HRESULT InstallPerfInstances(IPerfObject *pIObj, LPCOLESTR pcoleObjName)
{
	COM_TRY {
	// alle für dieses PerfObject zu installierenden Instanzen durchgehen
#if defined(_DEBUG)
	BOOL fFoundOne = FALSE;
#endif // defined(_DEBUG)

		for (const PERFINSTANCEDATA *pActPerfInst = GetPerfMonInstanceMap(); NULL != pActPerfInst -> pcoleName; pActPerfInst++) {
			if (!_wcsicmp (pcoleObjName, pActPerfInst -> pcoleObjectName)) {
			// nur für gesuchtes Objekt instantiieren
			__Interface<IPerfInstanceDefinition> InstanceDef;

				THROW_FAILED_HRESULT(pIObj -> AddInstanceDefinition (CComBSTR(pActPerfInst -> pcoleName), InstanceDef.ppi()));
#if defined(_DEBUG)
				fFoundOne = TRUE;
#endif // defined(_DEBUG)
			}
		}
		_ASSERTE(fFoundOne);	// wenigstens eine Instance dieses Typs muß existieren

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Installiert alle definierten PerfObjects, PerfInstances und PerfCounter
HRESULT InstallPerfCounters(HINSTANCE hInst)
{
	if (!g_PerfCtx.IsValid())
		return S_OK;

	COM_TRY {
	// alle zu installierenden PerfObjects durchgehen
		for (const PERFOBJECTDATA *pObjs = GetPerfObjectMap(); NULL != pObjs -> pcoleName; pObjs++) {
		__Interface<IPerfObject> Obj;
		CComBSTR bstrDesc;
		CComBSTR bstrHelp;

			_ASSERTE(0L != pObjs -> uiDesc && 0L != pObjs -> uiHelp);
			if (!bstrDesc.LoadString (hInst, pObjs -> uiDesc) || !bstrHelp.LoadString (hInst, pObjs -> uiHelp)) {
				_ASSERTE(FALSE);
				continue;
			}
			THROW_FAILED_HRESULT(g_PerfCtx -> AddPerformanceObject (CComBSTR(pObjs -> pcoleName), bstrDesc, bstrHelp, Obj.ppi()));
			THROW_FAILED_HRESULT(InstallPerfCounters (hInst, pObjs -> pPerfData, Obj));
			THROW_FAILED_HRESULT(InstallPerfInstances (Obj, pObjs -> pcoleName));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert einen instantiierten Counter einer gegebenen PerfInstanceDef
HRESULT GetPerfCounter (
	LPCOLESTR pcoleObjName, LPCOLESTR pcoleInstName, LPCOLESTR pcoleCounterName, 
	IPerfCounter **ppICount)
{
	if (!g_PerfCtx.IsValid())
		return S_OK;

	try {
	// PerfObject geben lassen
	__Interface<IPerfObjects> PerfObjs;
	__Interface<IPerfInstanceDefinitions> InstDefs;
	CComVariant vItemObj;

		THROW_FAILED_HRESULT(g_PerfCtx -> get_Objects (PerfObjs.ppi()));
		THROW_FAILED_HRESULT(PerfObjs -> get_Item (CComVariant(pcoleObjName), &vItemObj));
		_ASSERTE(VT_UNKNOWN == V_VT(&vItemObj) || VT_DISPATCH == V_VT(&vItemObj));

	// PerfInstance geben lassen
	__Interface<IPerfObject> PerfObj (V_UNKNOWN(&vItemObj));
	CComVariant vItemInst;

		THROW_FAILED_HRESULT(PerfObj -> get_InstanceDefs (InstDefs.ppi()));
		THROW_FAILED_HRESULT(InstDefs -> get_Item (CComVariant(pcoleInstName), &vItemInst));
		_ASSERTE(VT_UNKNOWN == V_VT(&vItemInst) || VT_DISPATCH == V_VT(&vItemInst));

	__Interface<IPerfInstanceDefinition> InstDef (V_UNKNOWN(&vItemInst));

		THROW_FAILED_HRESULT(InstDef -> get_Counter (CComBSTR(pcoleCounterName), ppICount));

	} catch (_com_error &e) {
		return _COM_ERROR(e);		// no assertion!
	} catch (...) {
		return E_UNEXPECTED;		// no assertion
	}
	return S_OK;
}

} // namespace PerfMon

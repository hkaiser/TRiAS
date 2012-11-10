// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/27/1998 09:47:02 PM
//
// @doc
// @module Main.cpp | Description goes here

#include "StdAfx.h"

#include "Main.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

//__Interface<PerfMon::IPerfObject>;
//__Interface<PerfMon::IPerfCounter>;
//__Interface<PerfMon::IPerfCounterDefinition>;
//__Interface<PerfMon::IPerfInstanceDefinition>;

DefineSmartInterface(BindCtx);
DefineSmartInterface(Moniker);

#define LOCALE_ENGLISH ((MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT)))

/////////////////////////////////////////////////////////////////////////////
// Initialisierung/Aufräumen
HRESULT CTestPerfMon::InitApplication(PERFMONSTARTMODE rgMode)
{
	COM_TRY {
		THROW_FAILED_HRESULT(PerfMonGetOrCreateContext (L"TestPerfMonitor", m_PerfContext.ppi()));

		THROW_FAILED_HRESULT(m_PerfContext -> Start (rgMode));
		THROW_FAILED_HRESULT(m_PerfContext -> put_Locale (LOCALE_ENGLISH));

		m_fInitialized = true;
	} COM_CATCH;
	return S_OK;
}

void CTestPerfMon::ExitApplication()
{
	if (m_fInitialized) 
		m_PerfContext -> Stop();
	m_PerfContext.Assign(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// hier passierts
struct PERFCOUNTERDATA {
	LPCOLESTR pcoleName;
	LPCOLESTR pcoleDesc;
	LPCOLESTR pcoleHelp;
	DETAILLEVEL rgDetailLevel;
	COUNTERTYPE rgCounterType;
	LONG lScale;
};

PERFCOUNTERDATA g_CounterData[] = {
	{	L"TESTPERFMONCOUNTER1", L"PerfMon TestCounter 1", 
		L"Test der allgemeinen PerfMonCounter Schnittstelle (Counter 1).",
		PERF_DETAIL_EXPERT, PERF_COUNTER_COUNTER, 0L,
	},
	{	L"TESTPERFMONCOUNTER2", L"PerfMon TestCounter 2", 
		L"Test der allgemeinen PerfMonCounter Schnittstelle (Counter 2).",
		PERF_DETAIL_NOVICE, PERF_COUNTER_TIMER, 2L,
	},
	{	NULL, NULL, NULL, 0L, 0L, 0L, },	// EndeKennung
};

struct PERFINSTANCEDATA {
	LPCOLESTR pcoleName;
};

PERFINSTANCEDATA g_InstanceData[] = {
	{	L"TESTPERFMONINSTANCE1", },
	{	L"TESTPERFMONINSTANCE2", },
	{	NULL, },	// EndeKennung
};

HRESULT CTestPerfMon::Start (void)
{
	COM_TRY {
	// ein Objekt hinzufügen
	CComBSTR bstrName ("TESTPERFMON");
	CComBSTR bstrDesc ("PerfMon Test");
	CComBSTR bstrHelp ("Test der allgemeinen PerfMon Schnittstelle.");
	__Interface<PerfMon::IPerfObject> Obj;

		THROW_FAILED_HRESULT(m_PerfContext -> AddPerformanceObject (bstrName, bstrDesc, bstrHelp, Obj.ppi()));

	// CounterDefinitions zu diesem Objekt hinzufügen
		for (PERFCOUNTERDATA *pCData = g_CounterData; NULL != pCData -> pcoleName; pCData++) {
			bstrName = pCData -> pcoleName;
			bstrDesc = pCData -> pcoleDesc;
			bstrHelp = pCData -> pcoleHelp;
			THROW_FAILED_HRESULT(Obj -> AddCounterDefinition (bstrName, bstrDesc, bstrHelp, pCData -> rgDetailLevel, pCData -> lScale, pCData -> rgCounterType));
		}

	// InstanceDefinitions zu diesem Objekt hinzufügen
	__Interface<PerfMon::IPerfInstanceDefinition> InstanceDef;

		for (PERFINSTANCEDATA *pIData = g_InstanceData; NULL != pIData -> pcoleName; pIData++) {
			bstrName = pIData -> pcoleName;
			THROW_FAILED_HRESULT(Obj -> AddInstanceDefinition (bstrName, InstanceDef.ppi()));
		}

	PERFMONSTARTMODE rgMode = PERFMONSTARTMODE_Unknown;

		THROW_FAILED_HRESULT(m_PerfContext -> get_Mode (&rgMode));
		switch (rgMode) {
		case PERFMONSTARTMODE_Register:
			THROW_FAILED_HRESULT(m_PerfContext -> Register());
			break;

		case PERFMONSTARTMODE_UnRegister:
			THROW_FAILED_HRESULT(m_PerfContext -> UnRegister());
			break;

		case PERFMONSTARTMODE_Normal:
			{
			// jetzt je einen Counter besorgen
			__Interface<PerfMon::IPerfCounter> Counter1;

				bstrName = g_CounterData[0].pcoleName;
				THROW_FAILED_HRESULT(InstanceDef -> get_Counter (bstrName, Counter1.ppi()));
				for (;;) 
				{
					if (FAILED(Counter1 -> Step()))
						break;

				MSG msg;
		
					while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) {
						if (::GetMessage(&msg, NULL, NULL, NULL))
							DispatchMessage(&msg);
					}

//				CComVariant vCnt;
//
//					THROW_FAILED_HRESULT(Counter1 -> get_Value (&vCnt));
//					if (V_I4(&vCnt) == 10000)
//						break;
				}
			}
			break;
		
		default:
			_ASSERTE(PERFMONSTARTMODE_Unknown != rgMode);
			break;
		}

	} COM_CATCH;
	return S_OK;
}



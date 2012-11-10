// @doc
// @module StatistApp.cpp | Implementation of exports for a TRiAS extension module.

#include "stdafx.h"

#include "resource.h"
#include "Statist.h"

#include <triastlb.h>
#include <registrx.hxx>

#include <initguid.h>
#include <objgguid.h>
#include <trelguid.h>

#include "StatistApp.h"
#include "StatistApp_i.c"

#include <dtoolbar.h>
#include <toolbar_i.c>

#include "Version.h"
#include "Strings.h"

#if !defined(_USE_RUNTIME_OBJECTMAP)
#include "TRiASSimpleStatistics.h"
#include "TRiASUnitsOfMeasure.h"
#include "TRiASUnitIDs.h"

#include "StatisticObjectProperty.h"
#include "CountLinePoints.h"
#include "PointRefCoord.h"
#include "PointCentreCoord.h"
#include "SelectStatistValue.h"
#include "LengthOfLine.h"
#include "CountAreaIsland.h"
#include "SimpleAreaFrame.h"
#include "FullAreaFrame.h"
#include "SuperficialContents.h"
#include "ObjektContainer.h"
#include "SimpleAreaRadius.h"

// PropertyPages/GeoComponenten
#include "MeshGeneration.h"
#include "UnitsOfMeasurePP.h"
//#include "MathOperationProperty.h"

// Controls
#include "ObjPropTree.h"

// statistische Kenngrößen
#include "StatistValue.h"
#include "ObjectClassStatistics.h"		// FüllHelper für Datenquellen
#include "ProjectValuePageCtrl.h"

// globale ValueProvider
#include "ObjectCountInClass.h"
#include "ObjectCountInDatasource.h"
#endif // !defined(_USE_RUNTIME_OBJECTMAP)

///////////////////////////////////////////////////////////////////////////////
// 
EXTERN_C const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
EXTERN_C const IID IID_ITRiASNotificationSink = {0x0796385A,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
EXTERN_C const CLSID CLSID_CatSimpleCache = {0xEA68A685,0x5166,0x4E55,{0x90,0x62,0x0B,0x13,0x06,0x81,0x33,0x93}};
EXTERN_C const CLSID CLSID_TRiASDataServerRegEntries = {0xF4B3F946,0x810E,0x11D1,{0x97,0x76,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

#if !defined(_USE_RUNTIME_OBJECTMAP)
///////////////////////////////////////////////////////////////////////////////
// Objectmap
BEGIN_OBJECT_MAP(ObjectMap)
// der Zusatzmodul selbst
	OBJECT_ENTRY(CLSID_Statist, CStatist)

// sonstige statistische Objekte
	OBJECT_ENTRY(CLSID_TRiASSimpleStatistics, CSimpleStatistics)
	OBJECT_ENTRY(CLSID_TRiASUnitsOfMeasure, CUnitsOfMeasure)
	OBJECT_ENTRY(CLSID_TRiASUnitIDs, CUnitIDs)

// Objekteigenschaften
	OBJECT_ENTRY(CLSID_SuperficialContents, CSuperficialContents)
	OBJECT_ENTRY(CLSID_CountAreaIsland, CCountAreaIsland)	// Anzahl der Inseln einer Fläche
	OBJECT_ENTRY(CLSID_SimpleAreaFrame, CSimpleAreaFrame)	// Länge der Außenkontur eines Flächenobjektes
	OBJECT_ENTRY(CLSID_FullAreaFrame, CFullAreaFrame)		// Länge der Kontur eines Flächenobjektes
	OBJECT_ENTRY(CLSID_CountLinePoints, CCountLinePoints)	// Anzahl der Stützpunkte eines Objektes
	OBJECT_ENTRY(CLSID_PointCoordX, CPointRefCoordX)		// Rechtswert der Punktkoordinate eines Punktobjektes
	OBJECT_ENTRY(CLSID_PointCoordY, CPointRefCoordY)		// Hochwert der Punktkoordinate eines Punktobjektes
	OBJECT_ENTRY(CLSID_PointCentreCoordX, CPointCentreCoordX)
	OBJECT_ENTRY(CLSID_PointCentreCoordY, CPointCentreCoordY)
	OBJECT_ENTRY(CLSID_LengthOfLine, CLengthOfLine)
	OBJECT_ENTRY(CLSID_ObjContainerXMin, CObjContainerXMin)
	OBJECT_ENTRY(CLSID_ObjContainerXMax, CObjContainerXMax)
	OBJECT_ENTRY(CLSID_ObjContainerYMin, CObjContainerYMin)
	OBJECT_ENTRY(CLSID_ObjContainerYMax, CObjContainerYMax)
	OBJECT_ENTRY(CLSID_SimpleAreaRadius, CSimpleAreaRadius)
	OBJECT_ENTRY(CLSID_StatisticObjectProperty, CStatisticObjectProperty)

// GeoKomponente
	OBJECT_ENTRY(CLSID_SelectStatistValue, CSelectStatistValue)
//	OBJECT_ENTRY(CLSID_MathOperationProperty, CMathOperationProperty)
	OBJECT_ENTRY(CLSID_MeshGeneration, CMeshGeneration)

// TRiAS-Propertypages 
	OBJECT_ENTRY(CLSID_UnitsOfMeasurePP, CUnitsOfMeasurePP)

// Controls
	OBJECT_ENTRY(CLSID_PopupTree, CPopupTree)

// statistische Kenngrößen
	OBJECT_ENTRY(CLSID_TRiASStatistCount, CStatistCount)
	OBJECT_ENTRY(CLSID_TRiASStatistCountNotNull, CStatistCountNotNull)
	OBJECT_ENTRY(CLSID_TRiASStatistSum, CStatistSum)
	OBJECT_ENTRY(CLSID_TRiASStatistArithmeticAverage, CStatistArithAverage)
	OBJECT_ENTRY(CLSID_TRiASStatistGeometricAverage, CStatistGeomAverage)
	OBJECT_ENTRY(CLSID_TRiASStatistMedian, CStatistMedian)
	OBJECT_ENTRY(CLSID_TRiASStatistMinValue, CStatistMinValue)
	OBJECT_ENTRY(CLSID_TRiASStatistMaxValue, CStatistMaxValue)
	OBJECT_ENTRY(CLSID_TRiASStatistRange, CStatistRange)
	OBJECT_ENTRY(CLSID_TRiASStatistStandardDeviation, CStatistStandardDeviation)
	OBJECT_ENTRY(CLSID_TRiASStatistVariance, CStatistVariance)

// Verwaltung ststistischer Kenngrößen
	OBJECT_ENTRY(CLSID_ProjectValuePageCtrl, CProjectValuePageCtrl)

// globale ValueProvider
	OBJECT_ENTRY(CLSID_ObjectCountInClass, CObjectCountInClass)
	OBJECT_ENTRY(CLSID_ObjectCountInDatasource, CObjectCountInDatasource)

END_OBJECT_MAP()
#endif // !defined(_USE_RUNTIME_OBJECTMAP)

/////////////////////////////////////////////////////////////////////////////
// ProgID dieses TRiAS-Zusatzmodules
extern "C" const TCHAR DECLSPEC_SELECTANY g_cbStatistProgID[] = _T("TRiAS.Statistics.1");

///////////////////////////////////////////////////////////////////////////////
// GuidString für statistische Kenngrößen (s. StatistValue.h)
OLECHAR s_cbGuid[37] = { '\0' };
OLECHAR s_cbStatName[128] = { '\0' };

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
#if !defined(_USE_RUNTIME_OBJECTMAP)
	return ObjectMap;				// liefert ObjectMap
#else
	return GetRunTimeObjectMap();
#endif // !defined(_USE_RUNTIME_OBJECTMAP)
}

BOOL GetTypeLibGUID (GUID &rGuid)
{
	rGuid = LIBID_TRiASStatistics;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// component categories verwalten
HRESULT CreateComponentCategory (CATID catid, LPCSTR pcCatDescription)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

// Make sure the HKCR\Component Categories\{..catid...}
// key is registered
CATEGORYINFO catinfo;

	catinfo.catid = catid;
	catinfo.lcid = GetUserDefaultLCID();

// Make sure the provided description is not too long.
// Only copy the first 127 characters if it is
	USES_CONVERSION;

WCHAR *catDescription = A2OLE(pcCatDescription);
int len = wcslen(catDescription);

	if (len > 127) len = 127;
    wcsncpy (catinfo.szDescription, catDescription, len);

// Make sure the description is null terminated
	catinfo.szDescription[len] = '\0';
    hr = pcr -> RegisterCategories (1, &catinfo);
	pcr -> Release();
	return hr;
}

HRESULT RemoveComponentCategory (REFCATID catid)
{
ICatRegister *pcr = NULL;
HRESULT hr = S_OK;

	hr = CoCreateInstance (CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (LPVOID *)&pcr);
	if (FAILED(hr))	return hr;

    hr = pcr -> UnRegisterCategories (1, (CATID *)&catid);
	pcr -> Release();
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// RegDB aktualisieren (initialisieren/löschen)

BOOL UpdateRegistry (BOOL fRegister)	
{
// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}

	if (fRegister) {	// RegDB initialisieren
	// Erweiterung selbst registrieren
		if (!ExtOleRegisterExtensionClass (_Module.GetModuleInstance(),
				CLSID_Statist, g_cbStatistProgID, IDS_LONGCLASSNAME,
				STATIST_MAJORVERSION, STATIST_MINORVERSION, EFPreLoad|EFUnLoadable))
			return FALSE;
	
	// registers component categories
	CString strCatId;

		strCatId.Format(IDS_CATIDDESC_STATVALUE, g_cbTRiAS);
		_ASSERTE(strCatId.GetLength() > 0);

		CreateComponentCategory (CATID_TRiASStatistValue, strCatId);

		strCatId.Format (IDS_CATIDDESC_STATVALUESCONTAINER, g_cbTRiAS);
		_ASSERTE(strCatId.GetLength() > 0);

		CreateComponentCategory (CATID_TRiASStatistValuesContainer, strCatId);
	} 
	else {
	// RegDB säubern
		RemoveComponentCategory (CATID_TRiASStatistValuesContainer);
		RemoveComponentCategory (CATID_TRiASStatistValue);

		if (!ExtOleUnregisterClass (CLSID_Statist, g_cbStatistProgID))
			return FALSE;
	}
	return TRUE;	// alles ok
}




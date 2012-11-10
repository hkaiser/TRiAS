// @doc
// @module Statist.cpp | Implementation of the <c CStatist> class

#include "stdafx.h"

#include <math.h>
#include <ctfxmfc.h>
#include <triastlb.h>

#include <errcodes.hxx>
#include <HdrEntrx.hxx>
#include <registrx.hxx>

#include <Com/ComBool.h>

#include "Strings.h"
#include "StatistApp.h"
#include "Statist.h"
#include "ConnectedCTF.h"
#include "UnitsOfMeasureDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(Statist)

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules Statist
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_Statist;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CStatist

CConnectedCtf *CStatist::GetCTF()
{
	_ASSERTE(NULL != m_pCT);
	return m_pCT;
}

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CStatist::InitExtension (short iMode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}

// Namen der Objekteigenschafts-Gruppe festlegen
CString strGroupName;

	strGroupName.LoadString(IDS_OBJPROP_GROUPNAME);
	_ASSERTE(strGroupName.GetLength() > 0);
	SetGroupName (strGroupName);

// Notifikationen anmelden
	RegisterNotification (DEX_HEADERREREAD);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

	if (DEX_TestActiveProject())
		OnOpenDocument();			// so tun als ob's jetzt erst passieren würde

#if defined(_USE_PROJECTVALUES)
// ProjectValues verwenden
	CProjectValueWindowImpl::RegisterTabWindow(this);
	InitToolbar();
#endif // defined(_USE_PROJECTVALUES)

	return TRUE;
}

// UnLoadExtension wird vor dem Entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CStatist::UnLoadExtension (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
	if (DEX_TestActiveProject())
		OnClosingProject();			// so tun als obs jetzt schon passieren würde

	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_HEADERREREAD);

#if defined(_USE_PROJECTVALUES)
	FreeToolbar();
#endif // defined(_USE_PROJECTVALUES)

	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
// Notifikationen behandeln
STDMETHODIMP_(LRESULT) CStatist::Notification (WPARAM wParam, LPARAM lParam)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
	switch (wParam) {
	case DEX_PROJECTOPEN:		// Projekt wurde geöffnet
		OnOpenDocument();
		break;

	case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
		OnClosingProject();
		break;

	case DEX_N_PROJECTTOCLOSE:
		OnProjectToClose();
		break;

	case DEX_HEADERREREAD:
		InitUnits();
		break;
	}
	return CTriasExtension::Notification (wParam, lParam);
}

HRESULT CStatist::OnOpenDocument()
{
	InitUnits();					// Maßeinheiten initialisieren
	InitCoordTrans();
	return InitObjectProperties();	// Objekteigenschaften initialisieren
}

HRESULT CStatist::OnClosingProject()
{
	return S_OK;
}

HRESULT CStatist::OnProjectToClose()
{
	FreeCoordTrans();
	FreeObjectProperties();			// Objekteigenschaften freigeben

#if defined(_USE_PROJECTVALUES)
	FreeProjectBar();
#endif // defined(_USE_PROJECTVALUES)
	return S_OK;
}

HRESULT CStatist::InitCoordTrans()
{
	COM_TRY {
	WTriasXtensionSite Site;

		if (SUCCEEDED(GetXtensionSite (Site.ppi()))) {
		HRESULT hr = CComObject<CConnectedCtf>::CreateInstance (&m_pCT);

			if (SUCCEEDED(hr)) {
				m_pCT -> AddRef();
				m_pCT -> SetXtsnSite (Site);
			}
			m_pCT -> EnsureLoaded();		// erstmaliges Laden
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CStatist::FreeCoordTrans()
{
	if (NULL != m_pCT) {
		m_pCT -> Release();
		m_pCT = NULL;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Funktionen, die gerufen werden, wenn die Objekteigenschaften für ein 
// bestimmtes Objekt bzw. alle Objekte einer bestimmten Objektklasse 
// registriert werden sollen

namespace {
// Listen der je Objekttyp verfügbaren Objekteigenschaften
	const CLSID *s_PointTempl[] = {		// Punkte
		&CLSID_CountLinePoints,		// Anzahl der Stützpunkte
		&CLSID_PointCoordX,			// Rechtswert der Punktkoordinate
		&CLSID_PointCoordY,			// Hochwert der Punktkoordinate
		&CLSID_ObjContainerXMin,
		&CLSID_ObjContainerXMax,
		&CLSID_ObjContainerYMin,
		&CLSID_ObjContainerYMax,
		NULL, 
	};
	const CLSID *s_LineTempl[] = {		// Linien
		&CLSID_CountLinePoints,		// Anzahl der Stützpunkte der Linie
		&CLSID_PointCoordX,			// Rechtswert der Linienkoordinate
		&CLSID_PointCoordY,			// Hochwert der Linienkoordinate
		&CLSID_LengthOfLine,			// Länge des Linienobjektes
		&CLSID_ObjContainerXMin,
		&CLSID_ObjContainerXMax,
		&CLSID_ObjContainerYMin,
		&CLSID_ObjContainerYMax,
		NULL, 
	};
	const CLSID *s_AreaTempl[] = {		// Flächen
		&CLSID_SuperficialContents,	// Flächeninhalt eines Flächenobjektes
		&CLSID_FullAreaFrame,		// Konturlänge eines Flächenobjektes
		&CLSID_SimpleAreaFrame,		// Außenkonturlänge eines Flächenobjektes
		&CLSID_CountAreaIsland,		// Anzahl der Inseln des Flächeobjektes
		&CLSID_CountLinePoints,		// Anzahl der Stützpunkte der Flächenumrandung
		&CLSID_PointCoordX,			// Rechtswert der Flächenkoordinate
		&CLSID_PointCoordY,			// Hochwert der Flächenkoordinate
		&CLSID_PointCentreCoordX,	// Rechtswert/Schwerpunkt der Flächenkoordinate
		&CLSID_PointCentreCoordY,	// Hochwert/Schwerpunkt der Flächenkoordinate
		&CLSID_ObjContainerXMin,
		&CLSID_ObjContainerXMax,
		&CLSID_ObjContainerYMin,
		&CLSID_ObjContainerYMax,
		&CLSID_SimpleAreaRadius,
		NULL, 
	};
	const CLSID *s_TextTempl[] = {		// Texte
		&CLSID_PointCoordX,			// Rechtswert der Textkoordinate
		&CLSID_PointCoordY,			// Hochwert der Textkoordinate
		&CLSID_ObjContainerXMin,
		&CLSID_ObjContainerXMax,
		&CLSID_ObjContainerYMin,
		&CLSID_ObjContainerYMax,
		NULL, 
	};
}

HRESULT CStatist::InitObjectProperties()
{
	COM_TRY {
	// Objekteigenschaften erzeugen und im jeweiligen cache zwischenspeichern
		m_PProps.InitObjectProperties (s_PointTempl);
		m_LProps.InitObjectProperties (s_LineTempl);
		m_FProps.InitObjectProperties (s_AreaTempl);
		m_TProps.InitObjectProperties (s_TextTempl);

	} COM_CATCH;
	return S_OK;
}

void CStatist::FreeObjectProperties()
{
	m_PProps.FreeObjectProperties();
	m_LProps.FreeObjectProperties();
	m_FProps.FreeObjectProperties();
	m_TProps.FreeObjectProperties();
}

// Umrechnen der verschiedenen Darstellungsformen der Objekttypen
int OTypToBits (int iOTyp)
{
	switch (iOTyp) {
	case OGPunkt:	return OTPunkt;
	case OGLinie:	return OTLinie;
	case OGFlaeche:
	case OGKreis:	return OTFlaeche;
	case OGLabel:
	case OGText:	return OTText;
	case OGKO:		return (OTPunkt|OTLinie|OTFlaeche|OTText);
	case OGUnknown:
	default:
		break;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// wird von TRiAS gerufen, wenn alle Objekteigenschaften für ein Objekt installiert
// werden sollen
STDMETHODIMP CStatist::OnNewReferenceObject (INT_PTR hRefONr)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
	if (-1L != hRefONr && m_lLastONr == hRefONr)
		return S_OK;				// warum alles mehrfach machen ?

	RemoveAllPropertyFunctions();	// alles bisherige vergessen
	m_lLastONr = hRefONr;
	m_lLastId = -1L;
	if (-1L == hRefONr)
		return S_OK;				// lediglich rücksetzen

int iOTyp = (OTPunkt|OTLinie|OTFlaeche|OTText);		// alle ObjektEigenschaften

	if (0L != hRefONr)				// neu initialisieren für ein konkretes Objekt
		iOTyp = OTypToBits(DEX_GetObjectType(hRefONr));
	
	return InstallPropertyFunctions(iOTyp);			// neue Funktionen installieren
}

///////////////////////////////////////////////////////////////////////////////
// Wird von TRiAS gerufen, wenn alle Objekteigenschaften für eine Objektklasse 
// installiert werden sollen. Unter Umständen ist zusätzlich ein Referenzobjekt
// gegeben, dann wird von dort der Objekttyp genommen.
STDMETHODIMP CStatist::OnNewReferenceObjects (INT_PTR hRefObjs, INT_PTR hRefONr)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState()); 		
	if (-1L != hRefObjs && m_lLastId == hRefObjs)
		return S_OK;				// warum alles mehrfach machen ?

	RemoveAllPropertyFunctions();	// alles bisherige vergessen
	m_lLastONr = -1L;
	m_lLastId = hRefObjs;
	if (-1L == hRefObjs)
		return S_OK;				// lediglich rücksetzen

int iOTyp = (OTPunkt|OTLinie|OTFlaeche|OTText);		// alle ObjektEigenschaften

// #HK001105: liefert jetzt nur noch sämtliche Objekteigenschaften für alle Objekte der 
// Objektklasse
//	if (0L != hRefONr)				// neu initialisieren für einen konkreten ObjektTyp
//		iOTyp = OTypToBits(DEX_GetObjectType(hRefONr));

	return InstallPropertyFunctions(iOTyp);			// neue Funktionen installieren
}

///////////////////////////////////////////////////////////////////////////////
// function-Objekt für for_each in 'CStatist::InstallPropertyFunctions'
class CAddPropertyFunction
{
public:
	CAddPropertyFunction (CStatist &rTarget) : 
		m_rTarget(rTarget) 
	{
	}
	HRESULT operator() (IObjectProperty *pIProp)
	{
	char cbBuffer[_MAX_PATH];
	WObjectProperty ObjProp;

		RETURN_FAILED_HRESULT(pIProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL));
		if (FAILED(m_rTarget.FindObjProp(cbBuffer, ObjProp.ppi())))
			return m_rTarget.AddPropertyFunction (pIProp);
		return S_OK;	// do not register twice
	}

private:
	CStatist &m_rTarget;
};

// Alle Objekteigenschaften für einen/mehrere Objekttypen installieren
HRESULT CStatist::InstallPropertyFunctions (int iOTypes)
{
	COM_TRY {
	CAddPropertyFunction Func(*this);

		if (iOTypes & OTPunkt)		// Objekteigenschaften für Punkte
			for_each (m_PProps.begin(), m_PProps.end(), Func);
		if (iOTypes & OTLinie) 		// Objekteigenschaften für Linien
			for_each (m_LProps.begin(), m_LProps.end(), Func);
		if (iOTypes & OTFlaeche) 	// Objekteigenschaften für Flächen
			for_each (m_FProps.begin(), m_FProps.end(), Func);
		if (iOTypes & OTText) 		// Objekteigenschaften für Texte
			for_each (m_TProps.begin(), m_TProps.end(), Func);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Maßeinheiten verwalten
si::Length CStatist::GetUoL (si::Length &rLength, os_string &rstrUnit)
{
	switch (m_iUnitOfLength) {
	case UoL_BestFit:
		break;

	case UoL_CentiMeter:
		if (m_fAppendUnits)
			rstrUnit = " [cm]";
		return si::centimeter;

	case UoL_DeciMeter:
		if (m_fAppendUnits)
			rstrUnit = " [dm]";
		return si::decimeter;

	case UoL_Meter:
		if (m_fAppendUnits)
			rstrUnit = " [m]";
		return si::meter;

	case UoL_KiloMeter:
		if (m_fAppendUnits)
			rstrUnit = " [km]";
		return si::kilometer;
	}

// best fit
	if (rLength >= si::kilometer) {
		rstrUnit = " [km]";
		return si::kilometer;
	}
	if (rLength < si::meter) {
		rstrUnit = " [cm]";
		return si::centimeter;
	}
	rstrUnit = " [m]";
	return si::meter;
}

si::Area CStatist::GetUoA(si::Area &rArea, os_string &rstrUnit)
{
	switch (m_iUnitOfArea) {
	case UoA_BestFit:
		break;

	case UoA_SquareCentiMeter:
		if (m_fAppendUnits)
			rstrUnit = " [cm²]";
		return si::squarecentimeter;

	case UoA_SquareDeciMeter:
		if (m_fAppendUnits)
			rstrUnit = " [dm²]";
		return si::squaredecimeter;

	case UoA_SquareMeter:
		if (m_fAppendUnits)
			rstrUnit = " [m²]";
		return si::squaremeter;

	case UoA_Hektar:
		if (m_fAppendUnits)
			rstrUnit = " [ha]";
		return si::hectare;

	case UoA_SquareKiloMeter:
		if (m_fAppendUnits)
			rstrUnit = " [km²]";
		return si::squarekilometer;
	}

// best fit ausrechnen
	if (rArea < si::squaredecimeter) {
		rstrUnit = " [cm²]";
		return si::squarecentimeter;
	}
	if (rArea < si::squaremeter) {
		rstrUnit = " [dm²]";
		return si::squaredecimeter;
	}
	if (rArea < si::hectare) {
		rstrUnit = " [m²]";
		return si::squaremeter;
	}
	if (rArea < si::squarekilometer) {
		rstrUnit = " [ha]";
		return si::hectare;
	}
	rstrUnit = " [km²]";
	return si::squarekilometer;
}

///////////////////////////////////////////////////////////////////////////////
// zu verwendende Maßeinheiten speichern/auslesen
void CStatist::InitUnits()
{
HeaderEntryX HdrLength (IDS_UNITOFLENGTH, HACTPROJECT);
HeaderEntryX HdrArea (IDS_UNITOFAREA, HACTPROJECT);
HeaderEntryX HdrAppend (IDS_APPENDUNITS, HACTPROJECT);

	m_iUnitOfLength = HdrLength.EntryLong(-1);		// default is fit best
	m_iUnitOfArea = HdrArea.EntryLong(-1);			// default is fit best
	m_fAppendUnits = HdrAppend.EntryLong(1) ? true : false;
}

void CStatist::SaveUnits()
{
HeaderEntryX HdrLength (IDS_UNITOFLENGTH, HACTPROJECT);
char cbBuffer[64];

	HdrLength.Flags() = HEADER_SYSTEM;
	HdrLength.SetEntryText(ltoa (m_iUnitOfLength, cbBuffer, 10));
	HdrLength.WriteBack();

HeaderEntryX HdrArea (IDS_UNITOFAREA, HACTPROJECT);

	HdrArea.Flags() = HEADER_SYSTEM;
	HdrArea.SetEntryText(ltoa (m_iUnitOfArea, cbBuffer, 10));
	HdrArea.WriteBack();

HeaderEntryX HdrAppend (IDS_APPENDUNITS, HACTPROJECT);

	HdrAppend.Flags() = HEADER_SYSTEM;
	HdrAppend.SetEntryText(m_fAppendUnits ? "1" : "0");
	HdrAppend.WriteBack();
}

#if defined(_USE_PROJECTVALUES)
bool CStatist::CreateProjectBar()
{
	_ASSERTE(NULL == m_pProjectBar);
	m_pProjectBar = CProjectValueWindowImpl::CreateInstance(this);
	return (NULL != m_pProjectBar) ? true : false;
}

bool CStatist::ShowProjectBar()
{
	_ASSERTE(NULL != m_pProjectBar);
	m_pProjectBar -> ReShow(this);
	return true;
}

bool CStatist::FreeProjectBar()
{
	if (NULL != m_pProjectBar) {
	// Rekursion verhindern
	CProjectValueWindowImpl *pProjBar = m_pProjectBar;

		m_pProjectBar = NULL;
		CProjectValueWindowImpl::DeleteInstance(this, pProjBar);
		_ASSERTE(NULL == pProjBar);
	}
	return true;
}
#endif // defined(_USE_PROJECTVALUES)

///////////////////////////////////////////////////////////////////////////////
// ITRiASUsedUnits

namespace {
// externe Repräsentation der Längenmaßeinheit in interne konvertieren und v.v.
	UNITCONSTANTS UnitConstantFromUoL(UNITOFLENGTH rgOoL)
	{
		switch (rgOoL) {
		case UoL_BestFit:
			return UNITCONSTANTS_BestFitSI;

		case UoL_CentiMeter:
			return UNITCONSTANTS_DistanceCentimeter;

		case UoL_DeciMeter:
			return UNITCONSTANTS_DistanceDecimeter;

		case UoL_Meter:
			return UNITCONSTANTS_DistanceMeter;

		case UoL_KiloMeter:
			return UNITCONSTANTS_DistanceKilometer;

		default:
			break;
		}
		return UNITCONSTANTS_Unknown;
	}
	UNITOFLENGTH UoLFromUnitConstant(UNITCONSTANTS rgVal)
	{
		switch (rgVal) {
		case UNITCONSTANTS_BestFitSI:
			return UoL_BestFit;

		case UNITCONSTANTS_DistanceCentimeter:
			return UoL_CentiMeter;

		case UNITCONSTANTS_DistanceDecimeter:
			return UoL_DeciMeter;

		case UNITCONSTANTS_DistanceMeter:
			return UoL_Meter;

		case UNITCONSTANTS_DistanceKilometer:
			return UoL_KiloMeter;

		default:
			break;
		}
		return UoL_Unknown;
	}

// externe Repräsentation der Flächenmaßeinheit in interne konvertieren und v.v.
	UNITCONSTANTS UnitConstantFromUoA(UNITOFAREA rgOoA)
	{
		switch (rgOoA) {
		case UoA_BestFit:
			return UNITCONSTANTS_BestFitSI;

		case UoA_SquareCentiMeter:
			return UNITCONSTANTS_AreaSquareCentimeter;

		case UoA_SquareDeciMeter:
			return UNITCONSTANTS_AreaSquareDecimeter;

		case UoA_SquareMeter:
			return UNITCONSTANTS_AreaSquareMeter;

		case UoA_Hektar:
			return UNITCONSTANTS_AreaHektar;

		case UoA_SquareKiloMeter:
			return UNITCONSTANTS_AreaSquareKilometer;

		default:
			break;
		}
		return UNITCONSTANTS_Unknown;
	}
	UNITOFAREA UoAFromUnitConstant(UNITCONSTANTS rgVal)
	{
		switch (rgVal) {
		case UNITCONSTANTS_BestFitSI:
			return UoA_BestFit;

		case UNITCONSTANTS_AreaSquareCentimeter:
			return UoA_SquareCentiMeter;

		case UNITCONSTANTS_AreaSquareDecimeter:
			return UoA_SquareDeciMeter;

		case UNITCONSTANTS_AreaSquareMeter:
			return UoA_SquareMeter;

		case UNITCONSTANTS_AreaHektar:
			return UoA_Hektar;

		case UNITCONSTANTS_AreaSquareKilometer:
			return UoA_SquareKiloMeter;

		default:
			break;
		}
		return UoA_Unknown;
	}
}

STDMETHODIMP CStatist::get_UnitOfLength(UNITCONSTANTS *pVal)
{
	if (NULL == pVal)
		return E_POINTER;

	*pVal = UnitConstantFromUoL((UNITOFLENGTH)m_iUnitOfLength);
	return S_OK;
}

STDMETHODIMP CStatist::put_UnitOfLength(UNITCONSTANTS newVal)
{
int iUnitOfLength = UoLFromUnitConstant(newVal);
	
	if (UoL_Unknown == iUnitOfLength)
		return E_INVALIDARG;
	m_iUnitOfLength = iUnitOfLength;
	return S_OK;
}

STDMETHODIMP CStatist::get_UnitOfArea(UNITCONSTANTS *pVal)
{
	if (NULL == pVal)
		return E_POINTER;

	*pVal = UnitConstantFromUoA((UNITOFAREA)m_iUnitOfArea);
	return S_OK;
}

STDMETHODIMP CStatist::put_UnitOfArea(UNITCONSTANTS newVal)
{
int iUnitOfArea = UoAFromUnitConstant(newVal);
	
	if (UoA_Unknown == iUnitOfArea)
		return E_INVALIDARG;
	m_iUnitOfArea = iUnitOfArea;
	return S_OK;
}

STDMETHODIMP CStatist::get_AppendUnits(VARIANT_BOOL *pVal)
{
	if (NULL == pVal)
		return E_POINTER;

CComBool fAppendUnits(m_fAppendUnits);

	*pVal = fAppendUnits;
	return S_OK;
}

STDMETHODIMP CStatist::put_AppendUnits(VARIANT_BOOL newVal)
{
	m_fAppendUnits = newVal ? true : false;
	return S_OK;
}

STDMETHODIMP CStatist::SaveUsedUnits()
{
	SaveUnits();
	return S_OK;
}

STDMETHODIMP CStatist::RestoreUsedUnits()
{
	InitUnits();
	return S_OK;
}

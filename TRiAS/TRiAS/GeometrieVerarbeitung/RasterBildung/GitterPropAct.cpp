// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.12.2002 12:55:37 
//
// @doc    PropertyAction für Gitterbildung
// @module GitterPropAct.cpp | Definition of the <c CGitterPropAct> class


#include "RasterP.hxx"

#include <resstrg.h>		// IDS_UIFORMAT
#include "clsfyprp.h"		// c_feORWndCaption

#include "GeoTrias.hxx"		// GeometrieAnTRIAS()
#include "Koord.hxx"		// UmrechnungsFaktor()
#include "DatBank.hxx"		// FehlerhaftesObjekt()

#include "RasterR.h"
#include "SmartInterfaces.h"
#include "GitterPropAct.h"
#include "Gitter.hxx"		// RasterExtension



///////////////////////////////////////////////////////////////////////////////////////////////
// CGitterPropAct
// IPropertyAction 

CGitterPropAct::CGitterPropAct (void)
			  : CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_GITTERPROPACT)
{
	// ggf. Erweiterung Gitter.ext laden
	m_hDex = NULL;
	if (NULL == g_pTE)
	{
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = 0;
		le.m_pName = "TRiAS.Raster.1";
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		m_hDex = DEX_ExternalLoadExtensionEx (le);
		
		_ASSERTE (0 != m_hDex);
	}

	// Member initialisieren
	m_pCfgDlg = NULL;
	m_bIsDirty = false;		// Parameter vom Dialog wurden (noch) nicht verändert
	m_bHasInitData = false;	// (noch) keine Initialisierungsdaten für den Dialog von Load()
							// bereitgestellt bzw. schon an diesen weitergereicht
}


// --------------------------------------------------------------------------------------------
CGitterPropAct::~CGitterPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}


// --------------------------------------------------------------------------------------------
void CGitterPropAct::FinalRelease (void)
{
	if (m_hDex)
	{
	//	Erweiterung Gitter.ext entladen
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = "TRiAS.Raster.1";
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = 0;
	}
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CGitterPropAct::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));

	COM_TRY
	{
	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence wSeq;
	WDataObject CtxDO;
	CComVariant vData;

		m_hPr = 0;	// Handle der Zieldatenquelle

		THROW_FAILED_HRESULT (GetSite (IID_IPropertyActionSequence, wSeq.ppv()));
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED (PropActBase::GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED (vData.ChangeType (VT_I4))) 
		{
			m_hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
	}
	COM_CATCH;

	// Zustand des Konfigurationsdialogs retten (für evtl. späteres Save())
	RETURN_FAILED_HRESULT(m_pCfgDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty));

	// Liste für Objekte, die an die PropertyPage übergeben werden, leeren
	m_InObjs.Clear();

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Hier werden alle Objekte angeboten.
STDMETHODIMP CGitterPropAct::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
	// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY
	{
	WEnumLONG EnumObjs;
	OutEnumLONG itObjs(&m_InObjs);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), itObjs);

	}
	COM_CATCH;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Hier werden 2 Aktionen durchgeführt:
// 1. Die eigentliche Verarbeitung einschließlich der Anwendung des ProgressIndikator und
// 2. das Weiterreichen des Ausgabestroms
STDMETHODIMP CGitterPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
double xb, yb;	// Gitterbreite (in DB-Verhältnissen), wird von BuildGrids() zurückgegeben

	COM_TRY
	{
		// Vorbereitung der Gitterbildung
		THROW_FAILED_HRESULT(m_pCfgDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty));

	// Gitter bilden: Parameter vom Konfigurationsdialog holen
//	EPunkt PRO = m_pCfgDlg->GetPRO();
//	EPunkt PLU = m_pCfgDlg->GetPLU();
	double dXWidth = m_pCfgDlg->GetXWidth();	// Gitterbreite in x-
	double dYWidth = m_pCfgDlg->GetYWidth();	//  bzw. y-Richtung

		_ASSERTE (dXWidth > 0.);
		_ASSERTE (dYWidth > 0.);

		m_PLO = m_pCfgDlg->GetPLO();
		m_PRU = m_pCfgDlg->GetPRU();
		m_bType = m_pCfgDlg->GetGridType();		// Gittertyp (Fläche: true, Linie: false)
		m_dTurnAngle = m_pCfgDlg->GetAngle();	// Drehwinkel
		
	InEnumLONG itEnd = InEnumLONG();	// Zeiger HINTER das letzte m_InObjs-Element

		for (InEnumLONG itObjs = InEnumLONG(&m_InObjs); itObjs != itEnd; ++itObjs)
		{
			BuildGrids (*itObjs, /*PRO, PLU, */dXWidth, dYWidth, xb, yb);

			// Gitterbildung ist (zur Zeit) nur für EIN Objekt möglich
			if (m_InObjs.Count() > 1)
			{
			ResourceFile RF (g_pDLLName);
			ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
			ResString resText (ResID (IDS_ONLYSINGLEOBJECT, &RF), 150);
			
				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
				break;
			}
		}

	// Ausgabeobjektmenge in Transfer-Objekt übertragen
	WEnumLONG wEnumOut (CLSID_EnumObjectsByNumber);	// Ausgabeobjektmenge

		BuildOutputObjects (wEnumOut);

	WDataObject wDO (CLSID_DataTransferObject);		// Transfer-Objekt

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (wEnumOut, wDO));
		*ppDataObj = wDO.detach();
	}
	COM_CATCH_NOASSERT_ON(E_ABORT);


	// die Ergebnisse an die Erweiterung übergeben
	((RasterExtension*)g_pTE)->ReturnResults (m_lObjInd, m_vlObjNr, m_PLO, m_PRU, xb, yb);

	DELETE_OBJ (m_pCfgDlg);	// Konfigurationsdialog freigeben, da nichts mehr kommt
	return S_OK;			// Es kommt keine weitere Objektmenge.

} // EndAction


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CGitterPropAct::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CGitterPropAct::Load (IStream *pStm)
{
	if (IsInitialized())		// IsInitialized() == true, wenn Page schon durch InitNew()
		return E_UNEXPECTED;	//  initialisiert wurde

	// Meine eigenen Daten vom stream holen
	// zuerst Bezeichner einlesen
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	

// meine Versionsnummer lesen und überprüfen
long lVersion = 0;

	RETURN_FAILED_HRESULT(pStm->Read (&lVersion, sizeof(long), NULL));
	if (lVersion > LAST_KNOWN_VERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

	// die zuletzt weggeschriebenen Parameter einlesen
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo, sizeof(GRIDDATA), NULL));

	// Initialisierungsdaten an den Konfigurationsdialog weiterreichen
	if (m_pCfgDlg)
	{
		RETURN_FAILED_HRESULT (m_pCfgDlg->SetSelectedInfo (&m_caSelInfo));
	}
	else
		// Initialisierungsdaten für den Konfigurationsdialog wurden zwar soeben von Load()
		// bereitgestellt, können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;

	SetInitialized();	// Page wurde jetzt durch Load() initialisiert
	m_bIsDirty = false;	// Dialogparameter wurden (noch) nicht verändert

	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CGitterPropAct::Save (IStream *pStm, BOOL bClearDirty)
{
	// Bezeichner wegschreiben
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, bClearDirty));

// Meine eigenen Daten im stream retten
// Version wegschreiben
long lVersion = LAST_KNOWN_VERSION;

	RETURN_FAILED_HRESULT (pStm->Write (&lVersion, sizeof(long), NULL));

	// die zuletzt gesetzten Parameter wegschreiben
	if (m_pCfgDlg)
		RETURN_FAILED_HRESULT (m_pCfgDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty));
	
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo, sizeof(GRIDDATA), NULL));

	if (bClearDirty)
		m_bIsDirty = false;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Bestimmen der benötigten Speichergröße für Save()
STDMETHODIMP CGitterPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	// die Größe meiner Daten zu pcbSize hinzuaddieren
	pcbSize  -> QuadPart += sizeof(GRIDDATA);

	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CGitterPropAct::InitNew()
{
	if (IsInitialized())		// IsInitialized() == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	//  initialisiert wurde

	// Initialisierung des Konfigurationsdialogs
	m_caSelInfo.bType = true;		// Flächengitter
	m_caSelInfo.bRound = false;		// nicht runden
	m_caSelInfo.iRoundListIndex = -1;	// Index in der Liste der Rundungswerte
	m_caSelInfo.lRoundValue = 0;	// Rundungswert
	m_caSelInfo.dTurnAngle = 0.;

	// Initialisierungsdaten an den Konfigurationsdialog weiterreichen
	if (m_pCfgDlg)
	{
		RETURN_FAILED_HRESULT (m_pCfgDlg->SetSelectedInfo (&m_caSelInfo));
	}
	else
		// Initialisierungsdaten für den Konfigurationsdialog wurden zwar soeben von InitNew()
		// bereitgestellt, können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;

	SetInitialized();	// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirty = false;	// Dialogparameter wurden (noch) nicht verändert
	
	return S_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// Einstellungen für Initialisierung des Dialoges aus der XML-Datei lesen
STDMETHODIMP CGitterPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));	// Load der Basisklasse

	// default-Einstellungen für Initialisierung des Konfigurationsdialogs
	m_caSelInfo.bType = true;		// Flächengitter
//	m_caSelInfo.dTRV = 0.;			// Rechtswert oben (in Real-Koordinaten)
//	m_caSelInfo.dTHV = 0.;			// Hochwert oben
//	m_caSelInfo.dBRV = 0.;			// Rechtswert unten
//	m_caSelInfo.dBHV = 0.;			// Hochwert unten
	m_caSelInfo.bRound = false;		// nicht runden
	m_caSelInfo.iRoundListIndex = -1;	// Index in der Liste der Rundungswerte
	m_caSelInfo.lRoundValue = 0;	// Rundungswert
	m_caSelInfo.lXWidth = 0;		// Gitterbreite in x- bzw.
	m_caSelInfo.lYWidth = 0;		//  y-Richtung
	m_caSelInfo.dTurnAngle = 0.;

// Parameter aus XML-Datei auswerten
// GridType
CComVariant vGridType;
HRESULT hr = pBag -> Read (CComBSTR(c_cbGridType), &vGridType, pLog);

	if (S_OK == hr && SUCCEEDED(vGridType.ChangeType(VT_BOOL))) 
		m_caSelInfo.bType = V_BOOL(&vGridType) ? true : false;
/*
// TopRightValue
CComVariant vTopRightValue;

	hr = pBag -> Read (CComBSTR(c_cbTopRightValue), &vTopRightValue, pLog);
	if (S_OK == hr && SUCCEEDED(vTopRightValue.ChangeType(VT_R8))) 
		m_caSelInfo.dTRV = V_R8(&vTopRightValue);

// TopHightValue
CComVariant vTopHightValue;

	hr = pBag -> Read (CComBSTR(c_cbTopHightValue), &vTopHightValue, pLog);
	if (S_OK == hr && SUCCEEDED(vTopHightValue.ChangeType(VT_R8))) 
		m_caSelInfo.dTHV = V_R8(&vTopHightValue);

// BottomRightValue
CComVariant vBottomRightValue;

	hr = pBag -> Read (CComBSTR(c_cbBottomRightValue), &vBottomRightValue, pLog);
	if (S_OK == hr && SUCCEEDED(vBottomRightValue.ChangeType(VT_R8))) 
		m_caSelInfo.dBRV = V_R8(&vBottomRightValue);

// BottomHighValue
CComVariant vBottomHighValue;

	hr = pBag -> Read (CComBSTR(c_cbBottomHighValue), &vBottomHighValue, pLog);
	if (S_OK == hr && SUCCEEDED(vBottomHighValue.ChangeType(VT_R8))) 
		m_caSelInfo.dBHV = V_R8(&vBottomHighValue);
*/
// Round
CComVariant vRound;

	hr = pBag -> Read (CComBSTR(c_cbRound), &vRound, pLog);
	if (S_OK == hr && SUCCEEDED(vRound.ChangeType(VT_BOOL))) 
		m_caSelInfo.bRound = V_BOOL(&vRound) ? true : false;

// RoundListIndex
CComVariant vRoundListIndex;

	hr = pBag -> Read (CComBSTR(c_cbRoundListIndex), &vRoundListIndex, pLog);
	if (S_OK == hr && SUCCEEDED(vRoundListIndex.ChangeType(VT_I2))) 
		m_caSelInfo.iRoundListIndex = V_I2(&vRoundListIndex);

	switch(m_caSelInfo.iRoundListIndex)
	{
		case 0:
			m_caSelInfo.lRoundValue = atol(sRound1);
			break;

		case 1:
			m_caSelInfo.lRoundValue = atol(sRound10);
			break;

		case 2:
			m_caSelInfo.lRoundValue = atol(sRound100);
			break;

		case 3:
			m_caSelInfo.lRoundValue = atol(sRound1000);
			break;

		case 4:
			m_caSelInfo.lRoundValue = atol(sRound10000);
	}

// XWidth
CComVariant vXWidth;

	hr = pBag -> Read (CComBSTR(c_cbXWidth), &vXWidth, pLog);
	if (S_OK == hr && SUCCEEDED(vXWidth.ChangeType(VT_I4))) 
		m_caSelInfo.lXWidth = V_I4(&vXWidth);
	
// YWidth
CComVariant vYWidth;

	hr = pBag -> Read (CComBSTR(c_cbYWidth), &vYWidth, pLog);
	if (S_OK == hr && SUCCEEDED(vYWidth.ChangeType(VT_I4))) 
		m_caSelInfo.lYWidth = V_I4(&vYWidth);
	
// TurnAngle
CComVariant vTurnAngle;

	hr = pBag -> Read (CComBSTR(c_cbTurnAngle), &vTurnAngle, pLog);
	if (S_OK == hr && SUCCEEDED(vTurnAngle.ChangeType(VT_R8))) 
		m_caSelInfo.dTurnAngle = V_R8(&vTurnAngle);


	// Initialisierungsdaten für den Dialog wurden zwar soeben von Load() bereitgestellt,
	// können hier aber noch nicht an diese weitergereicht werden
	m_bHasInitData = true;
	return S_OK;
	
} // Load



///////////////////////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CGitterPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam,
											 LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY
	{
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

		// zugehörigen Konfigurationsdialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);
		m_pCfgDlg = CGitterDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pCfgDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;	// es wurde 1 Page hinzugefügt
		} 

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData)
			// Initialisierungsdaten jetzt an den Dialog weiterreichen
			THROW_FAILED_HRESULT(m_pCfgDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow()));
	}
	COM_CATCH_OP(DELETE_OBJ(m_pCfgDlg));

	return S_OK;
}  


// --------------------------------------------------------------------------------------------
STDMETHODIMP CGitterPropAct::PreConfigPages (IDataObject *pIDataObj, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	// aus dem Kontext-Objekt das Handle m_hWnd des Fensters (Objektrecherchefenster bzw.
	// TRiAS-Hauptfenster) holen, aus dem die Gitterbildung aufgerufen wurde
	COM_TRY
	{
	WPropertyActionSequence wSeq;
	WDataObject wCtxDO;

		m_hWnd = 0x00;

		THROW_FAILED_HRESULT (GetSite (IID_IPropertyActionSequence, wSeq.ppv()));
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (wCtxDO.ppi()));
		THROW_FAILED_HRESULT (GetHWNDData (wCtxDO, &m_hWnd));
	}
	COM_CATCH;

	// Daten an den Dialog übergeben
	m_pCfgDlg->SetFlags (dwFlags);
	m_pCfgDlg->SetWinHandle (m_hWnd);

	return S_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////////

// Bilden eines Gitters
// lONr:             Objektnummer (bei Gitterbildung für ein konkretes Objekt)
// dXWidth, dYWidth: Breite in x/y-Richtung (in Meter)
// xb, yb:			 Breite in x/y-Richtung (DB-Verhältnissen)
void CGitterPropAct::BuildGrids (long lONr, /*EPunkt PRO, EPunkt PLU, */double dXWidth,
								 double dYWidth, double& xb, double& yb)
{
DoublePair dpUF = UmrechnungsFaktor (m_PLO.X(), m_PLO.Y(), m_PRU.X(), m_PRU.Y(), &m_CTX);
//DoublePair dpUF = UmrechnungsFaktor (PRO.X(), PRO.Y(), PLU.X(), PLU.Y(), &m_CTX);

	xb = dXWidth * dpUF.X();     // umgerechnete Gitterbreite in x-Richtung
	yb = dYWidth * dpUF.Y();     //  bzw. y-Richtung

/*	// "früher" wurde der Bereich für die Gitterbildung aus dem linken oberen und dem rechten
	// unteren Punkt gebildet; "heute" wird im Eingabedialog der rechte obere und der linke
	// untere Punkt angegeben; deshalb jetzt für den "alten" Algorithmus die Umrechnung
	m_PLO = PRO;
	m_PRU = PRO;	// nicht PLU !

	while (m_PLO.X() > PLU.X())
		m_PLO.X() -= xb;

	while (m_PRU.Y() > PLU.Y())
		m_PRU.Y() -= yb;
*/

	if (m_hWnd)   // Gitterbildung für ein konkretes Objekt
	{
		// bei Gitterbildung um einen Punkt oder eine absolut waagerechte bzw. senkrechte Linie hat
		// der Container mindestens eine Kante mit der Länge 0; deshalb die Kanten "etwas
		// aufspreizen"
		if (m_PLO.X() == m_PRU.X())
		{
			m_PLO.X() -= DtoL (xb/2.);
			m_PRU.X() += DtoL (xb/2.);
		}
		if (m_PLO.Y() == m_PRU.Y())
		{
			m_PLO.Y() += DtoL (yb/2.);
			m_PRU.Y() -= DtoL (yb/2.);
		}
	}

CEierUhr Wait (g_pTE->MVWind());

// Da an dieser Stelle die Objektklasse für die zu erzeugenden Gitterobjekte noch nicht
// bekannt ist, wird der Kurztext der "Unbekannten Objektklasse" als Objektname vorgesehen
PBDDATA pbdData;
char szKText[iKurzTextLen];

	INITSTRUCT (pbdData, PBDDATA);	// Initialisierung
	pbdData.pbdTyp = 'i';			// Typ: Identifikator
	pbdData.pbdCode = DEX_GetUnknownIdentEx (m_hPr);
	pbdData.pbdKText = szKText;
	pbdData.pbdKTextLen = sizeof(szKText) - 1;
	DEX_GetPBDData (pbdData);

// Anzahl der Gitterflächen bzw. -linien
long lGridCntX = DtoL (ceil (((double)m_PRU.X()-m_PLO.X())/xb));	// Anzahl der Gitter in x-
long lGridCntY = DtoL (ceil (((double)m_PLO.Y()-m_PRU.Y())/yb));	//  bzw. y-Richtung

	if (0 != lONr && -1 != lONr &&				// Gitterbildung für ein Punktobjekt
		OT_PUNKT == DEX_GetObjectType (lONr))
	{
		lGridCntX = 1;
		lGridCntY = 1;
	}

// eigentliche Gitterbildung
	if (m_bType)	// Flächengitter
		BuildAreaGrids (lGridCntX, lGridCntY, xb, yb, lONr, pbdData.pbdKText);
	else
		BuildLineGrids (lGridCntX, lGridCntY, xb, yb, lONr, pbdData.pbdKText);
} // BuildGrids


// --------------------------------------------------------------------------------------------
// Flächengitter bilden
bool CGitterPropAct::BuildAreaGrids (long lGridCntX, long lGridCntY, double xb, double yb,
									 long lONr, string sObjName)
{
ulong ulIdent = DEX_GetUnknownIdentEx (m_hPr);	// Ziel-Objektklasse an dieser Stelle noch unbekannt

	if (lGridCntX < 1) lGridCntX = 1;
	if (lGridCntY < 1) lGridCntY = 1;

	m_lGridCnt = lGridCntX * lGridCntY;	// Gesamtanzahl der Gitterobjekte

	SetMaxTicks (m_lGridCnt);			// ProgressIndikator initialisieren

	m_vlObjNr.resize (m_lGridCnt);		// Feld für die neuen Objektnummern
	m_lObjInd = 0;						// Laufindex für m_vlObjNr

EObjekt* pGridTerr = NULL;    // aktiviertes (blinkendes) Objekt bzw. allgemeiner Bereich

	GridTerritory (pGridTerr, lONr);

// Hilfswerte für TurnGrids()
double dFak = 1.;	// Hilfswerte für den Fall, daß x- und y-Achse nicht die gleiche
					// Maßeinteilung besitzen
double xm, ym;		// Drehpunkt
double dSin, dCos;

	if (m_dTurnAngle) // Drehwinkel ist vorgegeben
		TurnHelpParameters (xm, ym, dFak, dSin, dCos);

bool bInTest = true;	// es soll getestet werden, ob Gitter das lONr-Objekt überdeckt

	if (0 != lONr && -1 != lONr)	// Gitterbildung für ein konkretes Objekt
	{
		// Testen, ob Merkmal "Geometriefehler" belegt ist
		if (S_FALSE != FehlerhaftesObjekt (m_wGeoRein, lONr))
		{
		ResourceFile RF (g_pDLLName);
		ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
		ResString resText (ResID (IDS_GEOFEHL, &RF), 150);
			
			MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
			bInTest = false;	// kein EnthaltenIn-Test
		}
	}
	else			// Gitterbildung für einen allgemeinen Bereich
		bInTest = false;		// kein EnthaltenIn-Test

bool bRet = true;	// return-Wert für diese Routine
SpForm sfSForm;		// Speicherform

	// Zugriffsmode der Datenquelle ermitteln
	if (0 == DEX_GetROModeEx (m_hPr))	// Datenquelle nicht schreibgeschützt (R/W-Modus)
		sfSForm = SFORM_PERM;			// Speicherform: permanent
	else								// Datenquelle schreibgeschützt oder nicht geöffnet
	{
		DEX_Error (RC_Gitter, WC_DATASOURCE_ISRO);
		sfSForm = SFORM_TEMP;			// Speicherform: temporär
	}


	for (long i = 0; i < lGridCntY && bRet; ++i)
		for (long j = 0; j < lGridCntX; ++j)
		{
			Tick();				// ProgressIndikator weitersetzen

			if (FAILED(GoOn()))	// Abfrage, ob Gitterbildung abgebrochen werden soll
			{
			ResourceFile RF (g_pDLLName);
			ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
			ResString resText (ResID (IDS_CANCEL, &RF), 100);				

				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
				bRet = false;
				break;
			}


		KoOrd xr[5], yr[5];     // Koordinaten der Gitterfläche

			xr [0] = DtoL (xb*j + m_PLO.X());     yr [0] = DtoL (-yb*i + m_PLO.Y());
			xr [1] = xr [0];                      yr [1] = DtoL (-yb*(i+1) + m_PLO.Y());
			xr [2] = DtoL (xb*(j+1) + m_PLO.X()); yr [2] = yr [1];
			xr [3] = xr [2];                      yr [3] = yr [0];
			xr [4] = xr [0]; 			          yr [4] = yr [0];

			if (m_dTurnAngle)	// Drehwinkel ist vorgegeben
				TurnGrids (xr, yr, xm, ym, dSin, dCos, dFak);

		GeoFlaeche GridObj = GeoFlaeche (0, ulIdent, xr, yr, 5);  // Gitterfläche
				
			// Wenn das Objekt für die Gitterbildung einen Geometriefehler besitzt, dann
			// kann der Test, ob Gitter dieses Objekt überdeckt, nicht durchgeführt werden
			if (bInTest)
			{
			// Bei Gitterbildung mit Flächengitter wird getestet, ob das soeben erzeugte Gitter
			// GridObj das Objekt bzw. den allgemeinen Bereich GridTerr überdeckt (bLage == true)
			Posit posLage = pGridTerr->EnthaltenIn (&GridObj);
			bool bLage = INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
						 GLEICH == posLage || INNAUSS == posLage || UMSCHL == posLage ||
						 UMSCHLB == posLage;
			
				if (bLage)
					StoreGrids (GridObj, ulIdent, sfSForm, sObjName);
			}
			else
				StoreGrids (GridObj, ulIdent, sfSForm, sObjName);	// ohne EnthaltenIn-Test
	}

	DELETE_OBJ (pGridTerr);

	return bRet;

} // BuildAreaGrids


// --------------------------------------------------------------------------------------------
// Liniengitter bilden
bool CGitterPropAct::BuildLineGrids (long lGridCntX, long lGridCntY, double xb, double yb,
									 long lONr, string sObjName)

{
ulong ulIdent = DEX_GetUnknownIdentEx (m_hPr);	// Ziel-Objektklasse an dieser Stelle noch unbekannt

	lGridCntX++;	// bei Liniengitter wird senkrecht und
	lGridCntY++;	//  waagerecht noch eine Linie mehr benötigt
	if (lGridCntX < 2) lGridCntX = 2;
	if (lGridCntY < 2) lGridCntY = 2;

	m_lGridCnt = lGridCntX + lGridCntY;	// Gesamtanzahl der Gitterobjekte

	SetMaxTicks (m_lGridCnt);			// ProgressIndikator initialisieren

	m_vlObjNr.resize (m_lGridCnt);		// Feld für die neuen Objektnummern
	m_lObjInd = 0;						// Laufindex für m_vlObjNr

// Hilfswerte für TurnGrids()
double dFak = 1.;	// Hilfswerte für den Fall, daß x- und y-Achse nicht die gleiche
					// Maßeinteilung besitzen
double xm, ym;		// Drehpunkt
double dSin, dCos;

	if (m_dTurnAngle) 	// Drehwinkel ist vorgegeben
		TurnHelpParameters (xm, ym, dFak, dSin, dCos);

// Berechnung der rechten x-Koordinate der Gitterlinien, die größer als m_PRU.X() sein kann,
// wenn die Differenz m_PLO.X()-m_PRU.X() kein ganzzahliges Vielfaches von dXWidth ist bzw.
// der unteren y-Koordinate, die kleiner als m_PRU.Y() sein kann, wenn die Differenz
// m_PLO.Y()-m_PRU.Y() kein ganzzahliges Vielfaches von dYWidth ist
double dXRight = m_PLO.X() + (lGridCntX-1)*xb;
double dYDown = m_PLO.Y() - (lGridCntY-1)*yb;
KoOrd xr[2], yr[2];	// Koordinaten der Gitterlinien
bool bRet = true;	// return-Wert für diese Routine
SpForm sfSForm;		// Speicherform

	// Zugriffsmode der Datenquelle ermitteln
	if (0 == DEX_GetROModeEx (m_hPr))	// Datenquelle nicht schreibgeschützt (R/W-Modus)
		sfSForm = SFORM_PERM;			// Speicherform: permanent
	else								// Datenquelle schreibgeschützt oder nicht geöffnet
	{
		DEX_Error (RC_Gitter, WC_DATASOURCE_ISRO);
		sfSForm = SFORM_TEMP;			// Speicherform: temporär
	}


	for (long i = 0; i < lGridCntY; ++i)	// waagerechte Gitterlinien
	{
		Tick();				// ProgressIndikator weitersetzen

		if (FAILED(GoOn()))	// Abfrage, ob Gitterbildung abgebrochen werden soll
		{
		ResourceFile RF (g_pDLLName);
		ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
		ResString resText (ResID (IDS_CANCEL, &RF), 100);				

			MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
			bRet = false;
			break;
		}

		// xr[0] und xr[1] können nicht außerhalb der for-Schleife gesetzt werden, da sie 
		// für m_dTurnAngle != 0. in TurnGrids() verändert werden
		xr [0] = m_PLO.X();
		yr [0] = DtoL (-yb*i + m_PLO.Y());
		xr [1] = DtoL (dXRight);
		yr [1] = yr [0];

		if (m_dTurnAngle) 	// Drehwinkel ist vorgegeben
			TurnGrids (xr, yr, xm, ym, dSin, dCos, dFak);

	GeoKante GridObj = GeoKante (0, ulIdent, xr, yr, 2);	// Gitterlinie

		StoreGrids (GridObj, ulIdent, sfSForm, sObjName);
	} // for


	if (bRet)
		for (long j = 0; j < lGridCntX; ++j)	// senkrechte Gitterlinien
		{
			Tick();				// ProgressIndikator weitersetzen

			if (FAILED(GoOn()))	// Abfrage, ob Gitterbildung abgebrochen werden soll
			{
			ResourceFile RF (g_pDLLName);
			ResString resTitel (ResID (IDS_LONGCLASSNAME, &RF), 50);
			ResString resText (ResID (IDS_CANCEL, &RF), 100);				

				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
				bRet = false;
				break;
			}


			// yr[0] und yr[1] können nicht außerhalb der for-Schleife gesetzt werden, da sie 
			// für m_dTurnAngle != 0. in TurnGrids() verändert werden
			xr [0] = DtoL(xb*j + m_PLO.X());
			yr [0] = m_PLO.Y();
			xr [1] = xr [0];
			yr [1] = DtoL (dYDown);

			if (m_dTurnAngle) // Drehwinkel ist vorgegeben
				TurnGrids (xr, yr, xm, ym, dSin, dCos, dFak);

		GeoKante GridObj = GeoKante (0, ulIdent, xr, yr, 2);	// Gitterlinie

			StoreGrids (GridObj, ulIdent, sfSForm, sObjName);
		} // for

	return bRet;

} // BuildLineGrids


// --------------------------------------------------------------------------------------------
// GeoObjekt aus dem Objekt bzw. dem allgemeinen Bereich für die Gitterbildung erzeugen
void CGitterPropAct::GridTerritory (EObjekt*& pGridTerr, long lONr)
{
	// Gitterbildung für das aktivierte (blinkende) Objekt
	if (0 != lONr && -1 != lONr)
	{
	IObjektGeometrie* pIOG = NULL;

		if (FAILED(CreateInterfaceOG (&pIOG, lONr)))
			return;

	// Parameter des aktivierten Objektes
	short iOT;
	long lSPAnz;
	KoOrd* plXK; KoOrd* plYK;
	long* plK;

		pIOG->GetObjTyp (&iOT);
		pIOG->GetCnt (&lSPAnz);
		pIOG->GetX ((void**)&plXK);
		pIOG->GetY ((void**)&plYK);
		pIOG->GetLPCnt (&plK);

		switch (iOT)
		{
			case OT_PUNKT:
				pGridTerr = new EPunkt (plXK[0], plYK[0]);
				break;

			case OT_KANTE:
				pGridTerr = new EKante (plXK, plYK, lSPAnz);
				break;

			case OT_FLAECHE:
				pGridTerr = new EFlaeche (plXK, plYK, plK[0]);
				break;

			default:
				_ASSERTE (false);
				break;
		}

		pIOG->Release();
	}


	// Gitterbildung für einen allgemeinen Bereich
	else
	{
	KoOrd* plCO = m_pCfgDlg->GetCont();
	KoOrd plXK[5], plYK[5];

		plXK[0] = plCO[0];   plYK[0] = plCO[2];
		plXK[1] = plCO[1];   plYK[1] = plCO[2];
		plXK[2] = plCO[1];   plYK[2] = plCO[3];
		plXK[3] = plCO[0];   plYK[3] = plCO[3];
		plXK[4] = plXK[0];   plYK[4] = plYK[0];
		pGridTerr = new EFlaeche (plXK, plYK, 5);
	}

	if (! pGridTerr)
	{
		DEX_Error (RC_Gitter, EC_NOMEMORY);
		return;
	}

} // GridTerritory


// --------------------------------------------------------------------------------------------
// Gitter drehen
// dFak ist das Verhältnis der Maßeinteilung auf der y- bzw. x-Achse (für geodätische
// Koordinaten ist dFak != 1)
void CGitterPropAct::TurnGrids (KoOrd* xr, KoOrd* yr, double xm, double ym, double dSin,
								double dCos, double dFak)
{
	_ASSERTE (NULL != xr);
	_ASSERTE (NULL != yr);

	if (0. == dFak) return;

int iCnt = m_bType ? 5 : 2;	// Anzahl der Stützpunkte einer Gitterfläche bzw. -linie

	for (int i = 0; i < iCnt; ++i)
	{
	KoOrd temp_x = (KoOrd) (xm - (xm-xr[i])*dCos + (ym-yr[i])*dSin/dFak);

		yr [i] = (KoOrd) (ym - dFak*(xm-xr[i])*dSin - (ym-yr[i])*dCos);
		xr [i] = temp_x;
	}
} // TurnGrids


// --------------------------------------------------------------------------------------------
// Hilfswerte für TurnGrids()
void CGitterPropAct::TurnHelpParameters (double& xm, double& ym, double& dFak, double& dSin,
										 double& dCos)
{
KoOrd* plCO = m_pCfgDlg->GetCont();

	xm = ((double)plCO[0] + plCO[1]) / 2.; // Mittelpunkt des
	ym = ((double)plCO[2] + plCO[3]) / 2.; //  achsenparallelen Containers (in DB-Koordinaten)

	if (!m_CTX.isMetric())
	{
		if (plCO[0] != plCO[1] && plCO[2] != plCO[3])	// beide Containerseiten > 0
			dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (plCO[0], plCO[1], plCO[2], plCO[3]));
		else			// mindestens eine Containerseite == 0
		{
		KoOrd hw;	// Hilfswert

			if (plCO[0] == plCO[1] &&	// waagerechte Seite == 0,
				plCO[2] != plCO[3])		//  dh. total senkrechtes Linienobjekt
			{
				hw = plCO[0] + plCO[3] - plCO[2];
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (plCO[0], hw, plCO[2], plCO[3]));
			}
			if (plCO[2] == plCO[3] &&	// senkrechte Seite == 0,
				plCO[0] != plCO[1])		//  d.h. total waagerechtes Linienobjekt
			{
				hw = plCO[2] + plCO[1] - plCO[0];
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (plCO[0], plCO[1], plCO[2], hw));
			}
			else						// beide Seien == 0, d.h. Punktobjekt
			{
			KoOrd lCC[4];

				DEX_GetActiveSightContainer (lCC);
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (lCC[0], lCC[1], lCC[2], lCC[3]));
			}
		}
	}

	dSin = sin (m_dTurnAngle*Pi/180.);	// Pi ist in GeoKonst.hxx definiert
	dCos = cos (m_dTurnAngle*Pi/180.);

} // TurnHelpParameters


// --------------------------------------------------------------------------------------------
// Gitter nach TRiAS speichern
void CGitterPropAct::StoreGrids (GeoObjekt& GO, ulong ulIdent, SpForm sfSForm, string sObjName)
{
long lNewONr = -1;	// neue Objektnummer (von TRiAS bei Einspeicherung vergeben)
				
	GeometrieAnTRIASEx (m_hPr, &GO, sfSForm, lNewONr);

	if (0 == lNewONr || -1 == lNewONr)	// Einspeicherung in Datenbank ist nicht erfolgt
		return;
	
	WriteFeatureText (lNewONr, DEX_GetObjNameMCode(ulIdent), TT_Objekt, sObjName);

	_ASSERTE (m_lObjInd < m_lGridCnt);

	m_vlObjNr [m_lObjInd] = lNewONr;	// neue Objektnummer des Gitters abspeichern
	m_lObjInd++;

string sUIdent;
ResourceFile RF (g_pDLLName);
ResString resText (ResID (IDS_UIFORMAT, &RF), 20);

	Format (sUIdent, (char*)resText.Addr(), lNewONr);
	WriteFeatureText (lNewONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lNewONr)),
					  TT_Objekt, sUIdent);
} // StoreGrids


// --------------------------------------------------------------------------------------------
// Ausgabestrom zusammenstellen
void CGitterPropAct::BuildOutputObjects (IEnum<LONG>* pEnumOut)
{
	for (long l = 0; l < m_lObjInd; ++l)
		pEnumOut->AddItem (m_vlObjNr[l]);
}

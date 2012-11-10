// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:47:45
//
// @doc
// @module Strecken.cpp | Implementation of the <c CStrecken> class

#include "stdafx.h"


#include <TRiASHelper.h>

#include <xtsnguid.h>

#include "segguids.h"

#include "Segment.h"
#include "Strecken.h"

#include <KoOrd.h>

#include "worker.h"

#include <Errcodes.hxx>
#include <errinstx.hxx>
#include <Xtensnn.h>

/////////////////////////////////////////////////////////////////////////////
// CStrecken
// IPropertyAction 

STDMETHODIMP CStrecken::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CStrecken::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CStrecken::EndAction (DWORD, IDataObject **ppDataObj)
{


	// MerkmalskodeStruktur für Guid_Info anlegen/initialisieren

   	memset (&SG,'\0',sizeof(SEGMENTGUIDS));
	SG.dwSize = sizeof(SEGMENTGUIDS);


	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CStreckenWorker(iter_out, this, *this));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	// KnotenBaum freigeben
		if (NULL != m_pKnoten) {
			delete m_pKnoten;
			m_pKnoten = NULL;
		}

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CStrecken::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CStrecken::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CStrecken::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// TODO: Save your own data to the stream
	return S_OK;
}

STDMETHODIMP CStrecken::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CStrecken::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
bool CStrecken::AddConfigKnoten (const char *pKeyText)
{
	CTable t (*m_pKnoten);

	if (!t.Find((void *)pKeyText)) {
		CSegKnotenCreator OSCr (*m_pKnoten);
		CSegKnoten *pKnoten = ContCreate(OSCr, CSegKnoten)(pKeyText);

		if (NULL == pKnoten)
			return false;
	}
	return true;
}

long CStrecken::GetConfigKnoten (const char *pKeyText)
{
	CTable t (*m_pKnoten);

	if (t.Find((void *)pKeyText)) {

		CSegKnotenLock l(t);

		if (l) {
			return l -> GetObject();
		}
	}

	return -1L;
}

bool CStrecken::SetConfigKnoten (const char *pKeyText, long lONr)
{
	CTable t (*m_pKnoten);

	if (t.Find((void *)pKeyText)) {
		CSegKnotenLock l(t);

		if (l) {
			l -> SetObject(lONr);
			return true;
		}
	}

	return false;
}
///////////////////////////////////////////////////////////////////////////////
long CStrecken:: LoadGuidInfo(char * sText,SEGMENTGUIDS *pSG, bool iMode)
{
	pSG->iMode = 0;

	PBDMERKMALEX pbdData;
	memset (&pbdData, '\0', sizeof(PBDMERKMALEX));
	
	pbdData.dwSize = sizeof(PBDMERKMALEX);

	HPROJECT hPr = pSG->hPartPr;
	long lIdent = pSG->lPartIdent;

	if ( iMode ) {
		hPr = pSG->hPr;
		lIdent = pSG->lIdent;
	}

	ulong lMCode = DEX_GetMCodeFromFeatureNameEx (hPr, (LPCSTR)sText );

	if ( 0 != lMCode ) {
		pSG->iMode = true;
		return lMCode;
	}
		
	long lMHandle = DEX_GetUniqueSysMCode();
	lMCode = DEX_MapHandleToMCode(lMHandle);

	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKTextLen = strlen (sText) -1;
	pbdData.pbdLTextLen = 0;

	pbdData.pbdKText = sText;
	pbdData.ipbdMTyp = MPObjectFeature;	
	pbdData.ipbdMLen = 256;
	pbdData.lIdent = lIdent;

	{
	ErrInstall EI (WC_NOMERKMAL);
	if (DEX_ModPBDDataEx (hPr,pbdData) != EC_OKAY) {
		return -1;
	} else {
		DEXN_PBDMCodeChanged (lMCode);
		pSG->iMode = true;

	}
	}

	return lMCode;
}
///////////////////////////////////////////////////////////////////////////////
bool CStrecken :: CreatePBDData ( SEGMENTGUIDS *pSG)
{

	char KText[_MAX_PATH];


	PBDDATA pbdData;
	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = pSG->lIdent;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;

#if _MSC_VER < 1100
	DEX_GetPBDData (pbdData);
#else
	DEX_GetPBDDataEx (pSG->hPr,pbdData);
#endif


	if ( KText[0] == '\0')
		return false;


	pbdData.pbdCode = pSG->lPartIdent;
#if _MSC_VER < 1100
	DEX_ModPBDData (pbdData);
#else
	DEX_ModPBDDataEx (pSG->hPartPr,pbdData);
#endif


	return true;
}
///////////////////////////////////////////////////////////////////////////
bool CStrecken::SetConfigGuid ( long lIdent)
{
	if (0 == lIdent )
		return false;

   	memset (&SG,'\0',sizeof(SEGMENTGUIDS));
	SG.dwSize = sizeof(SEGMENTGUIDS);
	SG.lIdent = lIdent;
	SG.hPr = DEX_GetObjectsProject (lIdent);

	SG.hPartPr = m_pCfgDlg->bProjectHandle();
	if ( SG.hPartPr == SG.hPr)
		SG.lPartIdent = SG.lIdent;
	else {
		//	ID besorgen
		char NewIdent[MAX_OKS_LENX+1];
		ClassFromIdentX ( SG.hPr,SG.lIdent, NewIdent,strlen(NewIdent));
		ulong rIdent;
		HRESULT hr = IdentFromClassX ( SG.hPartPr,NewIdent,&rIdent,true);
		SG.lPartIdent = rIdent;
		CreatePBDData ( &SG);
	}

	CString strKante;
	VERIFY(strKante.LoadString(IDS_KANTENCODE));
	strcpy(SG.sGuid_Kante,(LPCTSTR)strKante);

	CString strKnoten;
	VERIFY(strKnoten.LoadString(IDS_KNOTENCODE));
	strcpy(SG.sGuid_Knoten,(LPCTSTR)strKnoten);

	CString strOriginal;
	VERIFY(strOriginal.LoadString(IDS_ORIGINALCODE));
	strcpy(SG.sGuid_Original, (LPCTSTR)strOriginal);

	CString strError;
	VERIFY(strError.LoadString(IDS_ERRORCODE));
	strcpy(SG.sErrorMode,(LPCTSTR)strError);

//	SG.lGuid_Kante = LoadGuidInfo(SG.sGuid_Kante,&SG);
	SG.lGuid_Knoten = LoadGuidInfo(SG.sGuid_Knoten,&SG);
	SG.lGuid_Original = LoadGuidInfo(SG.sGuid_Original,&SG);

	SG.lGuid_Knoten_Orig = LoadGuidInfo(SG.sGuid_Knoten,&SG,true);

	SG.lErrorMode = 0;

	return SG.iMode;
}
/////////////////////////////////////////////////////////////////////////////////
SEGMENTGUIDS *CStrecken::GetConfigGuid ( long lIdent)
{
	if ( SG.iMode)
		return &SG;

	SetConfigGuid(lIdent);

	return &SG;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CStrecken::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			ASSERT(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CStreckenDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);


	// zugehörigen KnotenBaum anlegen
		if (NULL != m_pKnoten) delete m_pKnoten;
		m_pKnoten = new CSegKnotenTree;
		if (NULL == m_pKnoten) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		PROPSHEETPAGE psp;

			memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		

		HPROPSHEETPAGE hPSP = ::CreatePropertySheetPage (&psp);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 
	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CStrecken::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

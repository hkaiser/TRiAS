// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.09.2000 15:48:18
//
// @doc
// @module MeshGeneration.cpp | Implementation of the <c CMeshGeneration> class

#include "stdafx.h"

#include <ospace/std/vector>
#include <ipropseq.hxx>
#include <clsfyprp.h>

#include "resource.h"

#include "GeoObj.h"
#include "MeshGeneration.h"
#include "ConvexHull.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(MeshGeneration)

/////////////////////////////////////////////////////////////////////////////
// CMeshGeneration

// IPropertyAction 

STDMETHODIMP CMeshGeneration::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CMeshGeneration::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// das Verhalten der Objekt-Sammlung ist bei den verschiedenen Operationen verschieden
// ConvexHull wird für jede Eingabe-Objektmenge separat durchgeführt, Voronoi und Delaynay
// für alle Objekte aller Eingabemengen gleichzeitig
	USES_CONVERSION;
	COM_TRY {
		m_rgOperation = m_pCfgDlg -> GetOperation();
		switch (m_rgOperation) {
		case CMeshGenerationDlg::MESH_CONVEXHULL:
			{
			// jede Objektmenge separat speichern
				m_listObjects.push_front(CListOfEnums::value_type(SEnumLONG(), os_string()));		// neues Element erzeugen

			// alle Objekte der Eingabemenge in neues Element reinkopieren
			CListOfEnums::iterator it = m_listObjects.begin();
			WEnumLONG EnumObjs;
			OutEnumLONG iter_out_if (&(*it).first);
			CComVariant vValue;

				THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
				if (SUCCEEDED(PropActBase::GetVariantData(pIDataObj, &c_feClassifyValue, &vValue))) {
					THROW_FAILED_HRESULT(vValue.ChangeType(VT_BSTR));
					(*it).second = OLE2A(V_BSTR(&vValue));
				}
				copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);
			}
			break;
		
		case CMeshGenerationDlg::MESH_VORONOI:
		case CMeshGenerationDlg::MESH_DELAUNAY:
			{
			// alle Objekte zusammenkopieren
			WEnumLONG EnumObjs;
			OutEnumLONG iter_out_if (&m_Objects);

				THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
				copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);
			}
			break;
		
		default:
			break;
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CMeshGeneration::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = E_FAIL;

	COM_TRY {
	// Zieldatenquelle bestimmen
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;
	HPROJECT hPr = 0;
	
		THROW_FAILED_HRESULT (GetSite (__uuidof(IPropertyActionSequence), Seq.ppv()));
		THROW_FAILED_HRESULT (Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED (PropActBase::GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED (vData.ChangeType (VT_I4))) 
		{
			hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
		if (HACTCONNECTION == hPr)
			hPr = DEX_GetDataSourceHandle();

		_ASSERTE(HACTCONNECTION != hPr);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		switch (m_rgOperation) {
		case CMeshGenerationDlg::MESH_CONVEXHULL:
			THROW_FAILED_HRESULT(hr = CalculateConvexHull(hPr, static_cast<IEnum<LONG> *>(EnumOut)));
			break;
		
		case CMeshGenerationDlg::MESH_VORONOI:
			THROW_FAILED_HRESULT(hr = CalculateVoronoiDiagram (hPr, static_cast<IEnum<LONG> *>(EnumOut)));
			break;

		case CMeshGenerationDlg::MESH_DELAUNAY:
			THROW_FAILED_HRESULT(hr = CalculateDelaunayTriangulation (hPr, static_cast<IEnum<LONG> *>(EnumOut)));
			break;
		
		default:
			break;
		}
		
	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (S_FALSE != hr) {
			if (NULL != m_pCfgDlg) {
				delete m_pCfgDlg;
				m_pCfgDlg = NULL;
			}
		}

	} COM_CATCH;
	return hr;
}

HRESULT CMeshGeneration::CalculateConvexHull(HPROJECT hPr, IEnum<LONG> *pEnumOut)
{
// ProgressIndikator initialisieren
	SetMaxTicks (m_listObjects.size());

double *pCoords = NULL;
double **pPoints = NULL;
double *pX = NULL;
double *pY = NULL;

	COM_TRY {
	OutEnumLONG iter_out (pEnumOut);

		for (CListOfEnums::iterator it = m_listObjects.begin(); it != m_listObjects.end(); ++it) {
		// Sinnfälligkeit testen
		long lPointCnt = (*it).first.Count();
		
			if (lPointCnt < 3)
				continue;		// es muß eine sinnvolle Fläche werden können

		// Felder initialisieren
			pCoords = new double[2 * lPointCnt];
			pPoints = new double * [lPointCnt + 1];	// ein Element mehr (Polygon wird geschlossen)

		// Koordinaten zusammensuchen
		long lCnt = 0;
		INT_PTR lONr = 0;
		vector<INT_PTR> vecObjs(lPointCnt);

			for ((*it).first.Reset(); S_OK == (*it).first.Next (1, &lONr, NULL); lCnt += 2) {
			CGObject Obj (lONr);
			
				if (!Obj.FInit() || OGPunkt != Obj.iObjTyp())	// nur Punkte behandeln
					continue;

				pCoords[lCnt] = *(Obj.X());
				pCoords[lCnt+1] = *(Obj.Y());
				pPoints[lCnt/2] = &pCoords[lCnt];
				vecObjs[lCnt/2] = lONr;
			}

		// Konvexe Hülle berechnen
		long lPoints = ConvexHull2D(pPoints, lCnt/2);

		// neues Objekt zusammenbauen
		CGObject NewObj(hPr);

		// Speicher (pX, pY, plCnt) wird von CGObject übernommen und freigegeben 
		double *pX = new double [lPoints];
		double *pY = new double [lPoints];
		long *plCnt = new long[1];			// immer nur eine Kontur

			for (long i = 0; i < lPoints; ++i) {
				pX[i] = pPoints[i][0];
				pY[i] = pPoints[i][1];
			}
			*plCnt = lPoints;
			
		// Merkmale erzeugen etc.
			if (NewObj.CreateNewObject(OGFlaeche, lPoints, pX, pY, 1, plCnt)) {
			// Unique Ident erzeugen
			CString strUIdent;

				strUIdent.Format (IDS_UNIQUEIDENT_CONVEXHULL, NewObj.lONr());
				NewObj.WriteUniqueIdent(strUIdent);

			// Objektnamen schreiben (kommt ggf. aus einer vorhergehenden Klassifikationsseite)
				if ((*it).second.size() > 0)
					NewObj.WriteObjectName((*it).second.c_str());

			// beteiligte Uniqueidents aufsammeln
			os_string strOldUniqueIdent;

				for (long i = 0; i < lPoints-1; ++i) {		// der Letzte ist identisch mit dem Ersten
				int iIndex = (pPoints[i] - pCoords)/2;		// Punktindex im Ausgangsfeld

					_ASSERTE(iIndex >= 0 && iIndex < lPointCnt);
					_ASSERTE(iIndex < vecObjs.size());

				CGObject OldObj (vecObjs[iIndex]);
				os_string strUIdent;
				
					if (OldObj.FInit() && OldObj.ReadUniqueIdent (strUIdent)) {
						if (strOldUniqueIdent.size() > 0) 
							strOldUniqueIdent += '/';		// nicht beim Ersten
						strOldUniqueIdent += strUIdent;
					}
				}
				if (strOldUniqueIdent.size() > 0)
					NewObj.WriteOldUniqueIdent(strOldUniqueIdent.c_str());

			// Objekt zur Ausgabemenge hinzufügen
				++iter_out = NewObj.lONr();
			}

		// Speicher wieder freigeben
			DELETE_OBJ(pCoords);
			DELETE_OBJ(pPoints);
		}

	} COM_CATCH_OP((delete pCoords, delete pPoints));
	return S_OK;	// das war der erste und letzte Schwung
}

HRESULT CMeshGeneration::CalculateVoronoiDiagram(HPROJECT hPr, IEnum<LONG> *pEnumOut)
{
// ProgressIndikator initialisieren
	SetMaxTicks (m_Objects.Count());

	return S_OK;	// das war der erste und letzte Schwung
}

HRESULT CMeshGeneration::CalculateDelaunayTriangulation(HPROJECT hPr, IEnum<LONG> *pEnumOut)
{
// ProgressIndikator initialisieren
	SetMaxTicks (m_Objects.Count());

	{
	OutEnumLONG iter_out (pEnumOut);

//		for_each(InEnumLONG(&m_Objects), InEnumLONG(), CMeshGenerationWorker(iter_out, this));
	} // iter_out goes out of scope

	return S_OK;	// das war der erste und letzte Schwung
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CMeshGeneration::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CMeshGeneration::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	_ASSERTE(sizeof(long) == sizeof(CMeshGenerationDlg::MESH_OPERATION));
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_rgOperation));
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CMeshGeneration::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_rgOperation));
	return S_OK;
}

STDMETHODIMP CMeshGeneration::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize  -> QuadPart += sizeof(CMeshGenerationDlg::MESH_OPERATION);
	return S_OK;
}

STDMETHODIMP CMeshGeneration::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_rgOperation = CMeshGenerationDlg::MESH_CONVEXHULL;
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CMeshGeneration::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CMeshGenerationDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

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

		if (CMeshGenerationDlg::MESH_UNKNOWN != m_rgOperation)
			m_pCfgDlg -> InitWithData (m_rgOperation);

	} COM_CATCH_OP(delete m_pCfgDlg);
	return S_OK;
}  

STDMETHODIMP CMeshGeneration::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CMeshGeneration::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

// sonstige Werte Analysieren

// MeshOp=
CComVariant vMeshOp;
HRESULT hr = pBag -> Read (L"MeshOp", &vMeshOp, pLog);

	if (S_OK == hr && SUCCEEDED(vMeshOp.ChangeType(VT_BSTR))) {
#if !defined(__ICL)
	using CMeshGenerationDlg::MESH_OPERATION;
#endif // !defined(__ICL)

		if (!_wcsicmp (V_BSTR(&vMeshOp), L"ConvexHull"))
			m_rgOperation = CMeshGenerationDlg::MESH_CONVEXHULL;	
		else if (!_wcsicmp (V_BSTR(&vMeshOp), L"Voronoi"))
			m_rgOperation = CMeshGenerationDlg::MESH_VORONOI;	
		else if (!_wcsicmp (V_BSTR(&vMeshOp), L"Delaunay"))
			m_rgOperation = CMeshGenerationDlg::MESH_DELAUNAY;
		else
			m_rgOperation = CMeshGenerationDlg::MESH_UNKNOWN;
	}
	return S_OK;
}


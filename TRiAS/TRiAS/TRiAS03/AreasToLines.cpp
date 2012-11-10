// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 11.11.2004 20:19:38
//
// @doc
// @module AreasToLines.cpp | Implementation of the <c CAreasToLines> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ipropseq.hxx>
#include <xtsnguid.h>
#include <funcs03.h>

#include "ObjGeomW.h"
#include "CloneObject.h"
#include "AreasToLines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);

/////////////////////////////////////////////////////////////////////////////
// CAreasToLines
// IPropertyAction 

STDMETHODIMP CAreasToLines::BeginAction (IProgressIndicator *pIProgInd)
{
	COM_TRY {
	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence Seq;
	WDataObject CtxDO;
	CComVariant vData;

	    m_hPr = HACTCONNECTION;

	    THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
	    THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));

	    if (SUCCEEDED(PropActBase::GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
		    SUCCEEDED(vData.ChangeType (VT_I4))) 
	    {
		    m_hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));	// Zieldatenquelle
	    }
	    if (HACTCONNECTION == m_hPr && m_bstrDataSource.Length() > 0) 
	    {
		    USES_CONVERSION;
		    m_hPr = DEX_GetDataSourceHandleFromShortName (OLE2A(m_bstrDataSource));
	    }

    // neue Datenquelle besorgen (für später)
	    if (HACTCONNECTION != m_hPr) {
		    if (!m_bstrDataSource) {
		    char cbBuffer[_MAX_PATH];

			    if (DEX_GetDataSourceShortName(m_hPr, cbBuffer))
				    m_bstrDataSource = cbBuffer;
		    }
	    } else
		    m_bstrDataSource = g_cbNil;

	    THROW_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	    m_Objects.clear();
		m_itlist = m_Objects.begin();
		m_lPacket = 0;

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CAreasToLines::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	// neues Paket speichern
		m_Objects.push_back(CListOfPackets::value_type());

	CListOfPackets::reference Enum (m_Objects.back());

	// Objekte kopieren
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&Enum);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

		m_itlist = m_Objects.begin();		// jedesmal machen
		m_lPacket = m_Objects.size();

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CAreasToLinesWorker 
	{
	public:
		CAreasToLinesWorker(OutEnumLONG &rOutIter, CAreasToLines *pThis) : 
			m_pThis(pThis), m_rOutIter(rOutIter)
		{
		}
		~CAreasToLinesWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pThis);
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);

            HOBJECT lNewONr = INVALID_HOBJECT;
		    if (S_OK == m_pThis->AreaToLine(HOBJECT(lONr), &lNewONr))
			    m_rOutIter++ = lNewONr;	// new object is added to the output collections
		}

	private:
		CAreasToLines *m_pThis;
		OutEnumLONG &m_rOutIter;
	};
} // namespace

STDMETHODIMP CAreasToLines::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	COM_TRY {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_AREASTOLINES_UNDO, &RF), 128);

		BeginUndoLevel (resUndo);

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	WDataObject DO (CLSID_DataTransferObject);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);		// Ausgabeobjektmenge

		if (m_itlist != m_Objects.end()) {
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

		// ProgressIndikator initialisieren
			SetMaxTicks ((*m_itlist).Count());
			for_each(InEnumLONG(&(*m_itlist)), InEnumLONG(), CAreasToLinesWorker(iter_out, this));

			++m_itlist;								// der nächste, Bitte
			hr = (m_itlist == m_Objects.end()) ? S_OK : S_FALSE;

			THROW_FAILED_HRESULT(PropActBase::SetPacketNumber(DO, m_lPacket--));
		}

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		EndUndoLevel();

	} COM_CATCH_OP_NOASSERT_ON(CancelUndoLevel(TRUE), E_ABORT);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CAreasToLines::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CAreasToLines::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

string strDataSource;

	RETURN_FAILED_HRESULT(LoadString(pStm, strDataSource));
	m_bstrDataSource = strDataSource.c_str();

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CAreasToLines::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

    USES_CONVERSION;

string strDataSource(!m_bstrDataSource ? "" : OLE2A(m_bstrDataSource));

	RETURN_FAILED_HRESULT(SaveString(pStm, strDataSource));
	return S_OK;
}

STDMETHODIMP CAreasToLines::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize -> QuadPart += m_bstrDataSource.Length();
	return S_OK;
}

STDMETHODIMP CAreasToLines::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_bstrDataSource.Empty();
    m_Objects.clear();
	m_itlist = m_Objects.begin();
	m_lPacket = 0;

	SetInitialized();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// mögliche SteuerParameter
//  DataSource=		Datenquelle, wo die Objekte erzeugt werden sollen

STDMETHODIMP CAreasToLines::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

CComVariant vParam;

// DataSource=
HRESULT hr = pBag -> Read (CComBSTR(g_cbDataSource), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BSTR)))
		m_bstrDataSource = V_BSTR(&vParam);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
// worker function
HRESULT CAreasToLines::AreaToLine(HOBJECT lONr, HOBJECT *plNewONr)
{
    if (NULL == plNewONr)
        return E_POINTER;

    HRESULT hr = S_FALSE;
    COM_TRY {
    CObjGeometrie ObjGeom;

        if (!ObjGeom.FillObjGeometrie(lONr))
            THROW_FAILED_HRESULT(E_UNEXPECTED);

        if (OGFlaeche == ObjGeom.iObjTyp && 1 == ObjGeom.iKCnt) {
        // nur für Flächen mit lediglich einer Außenkontur
        HPROJECT hPr = m_hPr;
        HOBJECTS lIdent = INVALID_HOBJECTS;

            if (HACTCONNECTION == m_hPr) {
                hPr = DEX_GetObjectProject(lONr);
                lIdent = DEX_GetObjIdentEx(lONr);
            }

        CCloneObject CloneObj (hPr, lONr, IDS_UNDOAREATOLINE);

            THROW_FAILED_HRESULT(ObjGeom.AreaToLine());
            THROW_FAILED_HRESULT(hr = CloneObj.Clone(ObjGeom, lIdent, plNewONr));
        
        // Originalobjekt löschen
            DEX_DeleteObjectEx(lONr);
        }

    } COM_CATCH;
    return hr;
}


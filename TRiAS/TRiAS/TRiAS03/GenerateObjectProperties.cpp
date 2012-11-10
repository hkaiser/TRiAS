// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 17:38:25
//
// @doc
// @module GenerateObjectProperties.cpp | Implementation of the <c CGenerateObjectProperties> class

#include "trias03p.hxx"
#include "trias03.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <TrCatIds.h>
#include <funcs03.h>
#include <IPropSeq.hxx>
#include <xtsnguid.h>

#include "Strings.h"
#include "DataHelp.h"

#include "PropSeqData.h"
#include "GenerateObjectProperties.h"
#include "GenObjPropDest.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineSmartInterface(ProgressIndicator2);

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectProperties
// IPropertyAction 

STDMETHODIMP CGenerateObjectProperties::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.clear();

// ausgewählte Objekteigenschaft im Kontext ablegen
	_ASSERTE(NULL != m_pCfgOptions);
	if (CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Property == m_pCfgOptions -> GetDestination()) {
	WPropertyActionSequence Seq;
	WDataObject CtxDO;

		if (SUCCEEDED(GetSite(IID_IPropertyActionSequence, Seq.ppv())) &&
			SUCCEEDED(Seq -> GetSequenceContext (CtxDO.ppi())))
		{
			SetObjectProperty(CtxDO, m_pCfgOptions -> GetPropName().c_str());
		}
	}
	return S_OK;
}

STDMETHODIMP CGenerateObjectProperties::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// EingabeObjektmengen in ihrer Strutur beibehalten
	COM_TRY {
	// neues Paket speichern
		m_Objects.push_back(CListOfPackets::value_type());

	CListOfPackets::reference Enum (m_Objects.back());

	// Objekte kopieren
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&Enum);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CGenerateObjectPropertiesWorker 
	{
	public:
		CGenerateObjectPropertiesWorker(
				OutEnumLONG &rOutIter, CGenerateObjectProperties *pThis, 
				list<WObjectProperty> &rLstProps, CGenObjPropDest *pDest, bool fOutputObjProp) : 
			m_pPA(pThis), m_rOutIter(rOutIter), m_rLstProps(rLstProps), m_pDest(pDest),
			m_fOutputObjProp(fOutputObjProp)
		{
		}
		~CGenerateObjectPropertiesWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);		// einfach abgebrochen

		char cbBuffer[2*_MAX_PATH];
		ULONG ul = 0;
		
			COM_TRY {
				THROW_FAILED_HRESULT(m_pDest -> BeginObject(lONr));
				for (list<WObjectProperty>::iterator it = m_rLstProps.begin(); it != m_rLstProps.end(); ++it, ++ul) 
				{
					if (FAILED((*it) -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL))) 
						cbBuffer[0] = '\0';
					if (m_fOutputObjProp) {
					// nur, wenn nicht nur kumulativer Index gewünscht wurde
						THROW_FAILED_HRESULT(m_pDest -> ObjectProperty (lONr, ul, cbBuffer));
					}
				}
				THROW_FAILED_HRESULT(m_pDest -> EndObject(lONr));
			} COM_CATCH_NORETURN;

			m_rOutIter++ = lONr;		// object is added to the output collections
		}

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
		list<WObjectProperty> &m_rLstProps;
		CGenObjPropDest *m_pDest;
		bool m_fOutputObjProp;
	};
} // namespace

///////////////////////////////////////////////////////////////////////////////
// Gesamtanzahl der zu bearbeitenden Objekte bestimmen
long CGenerateObjectProperties::GetObjectsCount()
{
long lCnt = 0;

	for (CListOfPackets::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it)
		lCnt += (*it).Count();
	return lCnt;
}

STDMETHODIMP CGenerateObjectProperties::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (GetObjectsCount());

	// Datenauswahl aus Dialogen holen
		m_lstProps = m_pCfgSequence -> GetObjProps();
		if (0 == m_lstProps.size())
			m_lstProps = m_pCfgSelect -> GetSelectedObjProps();		// die Sequence-Seite war ausgeblendet (nur eine OProp)
		_ASSERTE(m_lstProps.size() > 0);

		m_fHeadLine = m_pCfgOptions -> HasHeadline();
		m_fCumulate = m_pCfgOptions -> HasCumulate();
		m_fProps = m_pCfgOptions -> HasProps();
		m_fCounter = m_pCfgOptions -> HasCounter();

		m_rgDest = m_pCfgOptions -> GetDestination();
		m_cDelimiter = m_pCfgOptions -> GetDelimiter();

		if (CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_File <= m_rgDest)
			m_strFileName = m_pCfgOptions -> GetFileName();
		else
			m_strFileName = g_cbNil;

		if (CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Property == m_rgDest)
			m_strObjPropName = m_pCfgOptions -> GetPropName();
		else
			m_strObjPropName = g_cbNil;

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			switch (m_rgDest) {
			case CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Clipboard:
				OutputToClipboard (iter_out);
				break;

			case CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_FileCsv:
			case CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_FileOpr:
				OutputToFile(iter_out);
				break;

			case CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Property:
				OutputToObjProp(iter_out);
				break;

			case CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Window:
				OutputToWindow(iter_out);
				break;
				
			default:
				_ASSERTE(FALSE);
				break;
			}
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		DELETE_OBJ(m_pCfgSelect);
		DELETE_OBJ(m_pCfgSequence);
		DELETE_OBJ(m_pCfgOptions);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eigentliche Ausgabe
HRESULT CGenerateObjectProperties::OutputToClipboard(OutEnumLONG &rIterOut)
{
CGenObjPropClipboard Out(m_fProps);

	return GenericOutput (rIterOut, &Out);
}

HRESULT CGenerateObjectProperties::OutputToFile(OutEnumLONG &rIterOut)
{
CGenObjPropFile Out(m_strFileName.c_str(), m_cDelimiter, m_fProps);

	return GenericOutput (rIterOut, &Out);
}

HRESULT CGenerateObjectProperties::OutputToObjProp(OutEnumLONG &rIterOut)
{
WObjectProperty ObjProp;

	COM_TRY {
	WObjectProps Props (m_pCfgSelect -> GetObjectProps());
	WEnumObjProps Enum;

		THROW_FAILED_HRESULT(Props -> EnumObjectProps(Enum.ppi()));
		THROW_FAILED_HRESULT(Enum -> FindByName(m_strObjPropName.c_str(), ObjProp.ppi()));

	} COM_CATCH;

CGenWriteObjProp Out(ObjProp, m_cDelimiter, m_fCounter);

	return GenericOutput (rIterOut, &Out);
}

HRESULT CGenerateObjectProperties::OutputToWindow(OutEnumLONG &rIterOut)
{
HWND hParent = NULL;
WPropertyActionSequence PropSeq;
WDataObject CtxDO;

	RETURN_FAILED_HRESULT(GetSite (__uuidof(IPropertyActionSequence), PropSeq.ppv()));
	RETURN_FAILED_HRESULT(PropSeq -> GetSequenceContext (CtxDO.ppi()));
	RETURN_FAILED_HRESULT(GetHWND (CtxDO, &c_feMainWindow, &hParent))

char cbCaption[_MAX_PATH];

	m_pCfgOptions -> GetCaption(cbCaption, sizeof(cbCaption));

Point ptPos (m_pCfgOptions -> GetPosition());
CGenObjPropWindow Out(hParent, cbCaption, ptPos, m_fHeadLine, m_fProps);

	return GenericOutput (rIterOut, &Out, true);
}

///////////////////////////////////////////////////////////////////////////////
// generische Datenausgabe
HRESULT CGenerateObjectProperties::GenericOutput (
	OutEnumLONG &rIterOut, CGenObjPropDest *pDest, bool fHideStatus)
{
// Objekteigenschaften besorgen
list<WObjectProperty> lstProps;

	RETURN_FAILED_HRESULT(GetPropList (lstProps));

// hier gehts los
	RETURN_FAILED_HRESULT(pDest -> Begin(lstProps.size()));
	
	COM_TRY {
	list<WObjectProperty>::iterator it;
	char cbBuffer[2*_MAX_PATH];
	ULONG ul;

	// Überschrift ausgeben
		if (m_fHeadLine) {
			THROW_FAILED_HRESULT(pDest -> BeginHeadline());
			ul = 0;
			for (it = lstProps.begin(); it != lstProps.end(); ++it, ++ul) {
				if (FAILED((*it) -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL)))
					cbBuffer[0] = '\0';
				THROW_FAILED_HRESULT(pDest -> Headline(ul, cbBuffer));
			}
			THROW_FAILED_HRESULT(pDest -> EndHeadline());
		}

	// Objekteigenschaften für alle Objekte ausgeben
		if (m_fProps || m_fCumulate) {
		// alle Objekteigenschaften rücksetzen
			for (it = lstProps.begin(); it != lstProps.end(); ++it) 
				(*it) -> Reset();
				
		// alle Eingabeobjektmengen durchgehen
			for (CListOfPackets::iterator it = m_Objects.begin(); it != m_Objects.end(); ++it) {
			// alle Objekte der Eingabeobjektmenge bearbeiten
				for_each(InEnumLONG(&(*it)), InEnumLONG(), 
						CGenerateObjectPropertiesWorker(rIterOut, this, lstProps, pDest, m_fProps));
			}
		}

	// kumulativen Index Ausgeben
		if (m_fCumulate) {
			THROW_FAILED_HRESULT(pDest -> BeginCumulation());
			ul = 0;
			for (it = lstProps.begin(); it != lstProps.end(); ++it, ++ul) {
				if (FAILED((*it) -> Cumulation(cbBuffer, sizeof(cbBuffer), NULL)))
					cbBuffer[0] = '\0';
				THROW_FAILED_HRESULT(pDest -> Cumulation(ul, cbBuffer));
			}
			THROW_FAILED_HRESULT(pDest -> EndCumulation());
		}

	// Zähler ausgeben
		if (m_fCounter) {
			THROW_FAILED_HRESULT(pDest -> BeginCount());
			ul = 0;
			for (it = lstProps.begin(); it != lstProps.end(); ++it, ++ul) {
			DWORD dwCount = (*it) -> Count();

				ultoa(dwCount, cbBuffer, 10);
				THROW_FAILED_HRESULT(pDest -> Count(ul, cbBuffer));
			}
			THROW_FAILED_HRESULT(pDest -> EndCount());
		}

	// vor dem Ende evtl. Status ausblenden
		if (fHideStatus) {
		WProgressIndicator2 PI (m_pProgressIndicator);
					
			THROW_FAILED_HRESULT(PI -> Hide());
		}

	} COM_CATCH_OP_NOASSERT_ON(pDest -> Cancel(), E_ABORT);	// abbrechen

// ... und hier ist's zu Ende
	RETURN_FAILED_HRESULT(pDest -> End());

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// die Liste aller auszugebenden Objekteigenschaften bilden
HRESULT CGenerateObjectProperties::GetPropList(list<WObjectProperty> &rLstProps)
{
	COM_TRY {
	WObjectProps Props (m_pCfgSelect -> GetObjectProps());
	WEnumObjProps Enum;

		THROW_FAILED_HRESULT(Props -> EnumObjectProps(Enum.ppi()));

	// jetzt alle selektieretne Namen durchgehen und Objekteigenschaften besorgen
		for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) {
		WObjectProperty ObjProp;

			if (SUCCEEDED(Enum -> FindByName((*it).c_str(), ObjProp.ppi())))
			{
				rLstProps.push_back (ObjProp);
			}
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CGenerateObjectProperties::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CGenerateObjectProperties::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

list<os_string>::difference_type ulCnt = 0;

	RETURN_FAILED_HRESULT(LoadData(pStm, ulCnt));
	for (list<os_string>::difference_type ul = 0; ul < ulCnt; ++ul) 
	{
	os_string str;

		RETURN_FAILED_HRESULT(LoadString(pStm, str));
		m_lstProps.push_back(str);
	}

	RETURN_FAILED_HRESULT(LoadData(pStm, m_fHeadLine));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fCumulate));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fProps));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fCounter));

	RETURN_FAILED_HRESULT(LoadData(pStm, m_rgDest));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_cDelimiter));

	RETURN_FAILED_HRESULT(LoadString(pStm, m_strObjPropName));
	RETURN_FAILED_HRESULT(LoadString(pStm, m_strFileName));

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CGenerateObjectProperties::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

list<os_string>::difference_type ulCnt = m_lstProps.size();

	RETURN_FAILED_HRESULT(SaveData(pStm, ulCnt));
	for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) 
	{
		RETURN_FAILED_HRESULT(SaveString(pStm, *it));
	}

	RETURN_FAILED_HRESULT(SaveData(pStm, m_fHeadLine));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fCumulate));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fProps));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fCounter));

	RETURN_FAILED_HRESULT(SaveData(pStm, m_rgDest));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_cDelimiter));

	RETURN_FAILED_HRESULT(SaveString(pStm, m_strObjPropName));
	RETURN_FAILED_HRESULT(SaveString(pStm, m_strFileName));
	
	return S_OK;
}

STDMETHODIMP CGenerateObjectProperties::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize -> QuadPart += sizeof(list<os_string>::difference_type);
	for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) 
	{
		pcbSize -> QuadPart += ::GetSizeMax(*it);
	}

	pcbSize -> QuadPart += 4*sizeof(bool) + sizeof(CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST) +
		::GetSizeMax(m_strObjPropName) + ::GetSizeMax(m_strFileName) + sizeof(char);
	return S_OK;
}

STDMETHODIMP CGenerateObjectProperties::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_lstProps.clear();

	m_fHeadLine = false;
	m_fCumulate = false;
	m_fProps = true;
	m_fCounter = false;

	m_rgDest = CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Clipboard;
	m_strObjPropName = g_cbNil;
	m_strFileName = g_cbNil;
	m_cDelimiter = '\t';

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CGenerateObjectProperties::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialoge (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgSelect);
		DELETE_OBJ(m_pCfgSequence);
		DELETE_OBJ(m_pCfgOptions);

		m_pCfgSelect = CGenerateObjectPropertiesSelectDlg::CreateInstance(this, cbCaption);
		if (NULL == m_pCfgSelect) _com_issue_error(E_OUTOFMEMORY);

		m_pCfgSequence = CGenerateObjectPropertiesSequenceDlg::CreateInstance(this, cbCaption);
		if (NULL == m_pCfgSequence) _com_issue_error(E_OUTOFMEMORY);

		m_pCfgOptions = CGenerateObjectPropertiesOptionsDlg::CreateInstance(this, cbCaption);
		if (NULL == m_pCfgOptions) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seiten hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgSelect);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			hPSP = this -> CreatePage(m_pCfgSequence);
			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			hPSP = this -> CreatePage(m_pCfgOptions);
			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 3;		// wir haben drei Pages hinzugefügt
		} 

	// Vorinitialisierungen
		m_pCfgSelect -> SetInitialObjProps(m_lstProps);

		m_pCfgOptions -> SetHeadline(m_fHeadLine);
		m_pCfgOptions -> SetCumulate(m_fCumulate);
		m_pCfgOptions -> SetCounter(m_fCounter);
		m_pCfgOptions -> SetProps(m_fProps);
		m_pCfgOptions -> SetDestination(m_rgDest);
		if (CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_FileCsv == m_rgDest ||
			CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_FileOpr == m_rgDest)
		{
			m_pCfgOptions -> SetFileName(m_strFileName.c_str());
			m_pCfgOptions -> SetFileType(m_rgDest);
		}
		if (CGenerateObjectPropertiesOptionsDlg::OBJPROPDEST_Property == m_rgDest)
			m_pCfgOptions -> SetPropName(m_strObjPropName.c_str());
	
	} COM_CATCH_OP((delete m_pCfgSelect, delete m_pCfgSequence, delete m_pCfgOptions));
	return S_OK;
}  

STDMETHODIMP CGenerateObjectProperties::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgSelect || NULL == m_pCfgSequence || NULL == m_pCfgOptions) 
		return E_UNEXPECTED;

	m_pCfgSelect -> SetFlags(dwFlags & ~ADDPAGES_LASTPAGE);
	m_pCfgSequence -> SetFlags(dwFlags & ~(ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE));
	m_pCfgOptions -> SetFlags(dwFlags & ~ADDPAGES_FIRSTPAGE);
	return S_OK;
}

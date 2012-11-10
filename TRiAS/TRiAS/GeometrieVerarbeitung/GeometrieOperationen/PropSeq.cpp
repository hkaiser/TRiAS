// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PropSeq.cpp
// H. Kaiser


#include "ObjOperP.hxx"

#include "ObjOperR.h"		// IDS_LONGCLASSNAME

#include "SmartInterfaces.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variablen
extern ResourceFile* pRF;


///////////////////////////////////////////////////////////////////////////////////////////////
const TCHAR g_cbPropertySequences[] = TEXT("PropertySequences");


///////////////////////////////////////////////////////////////////////////////////////////////
// Konvertieren eines PropAct-Bezeichners in einen Stream-Namen
static string MakeStreamName (LPCSTR pcDesc)
{
char str[32];

	for (int i = 0; i < sizeof(str)-1; i++) {
	char c = pcDesc[i];

		switch (c) {
		case '.':
		case '\\':
		case '/':
		case ':':
		case '!':
			str[i] = '_';
			break;

		case '\0':		// Ende des Strings
			str[i] = '\0';
			return str;

		default:
			if (c > ' ')
				str[i] = c;
			else
				str[i] = '_';
			break;
		}
	}
	str[i] = '\0';
	return str;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Erzeugen und initialisieren einer PropertyActionSequence, welche die vorgegebenen
// PropertyActions enthält
HRESULT InitPropertyActionSequence (LPCSTR pcDesc, IStorage *pIStg,
									IPropertyActionSequence **ppISeq)
{
	if (NULL == ppISeq) return E_POINTER;

	*ppISeq = NULL;		// für alle Fälle

WPropertyActionSequence ISeq;

	USES_CONVERSION;

	if (NULL != pIStg)		// evtl. gespeicherten Status laden
	{
	WStream IStm;
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
	HRESULT hr = pIStg -> OpenStream (A2OLE(strName.c_str()), NULL,
									  STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());
		if (SUCCEEDED(hr))
		{
			hr = OleLoadFromStream (IStm, IID_IPropertyActionSequence, ISeq.ppv());
			if (SUCCEEDED(hr))
			{
				*ppISeq = ISeq.detach();
				return S_OK;
			}
		}
	}
	
// wenn Status nicht geladen werden kann, dann neu initialisieren
// dieser Abschnitt ist von mir zu modifizieren
	try
	{
	WPropertyActionSequence wSeq (CLSID_PropertyActionSequence);

		ISeq = wSeq;
		THROW_FAILED_HRESULT (WPersistStreamInit(ISeq)->InitNew());
		THROW_FAILED_HRESULT (ISeq->SetDescription(pcDesc));

	// 1. Seite einfach instantiieren 
	WPropertyAction wOrigObjs (CLSID_SelectFromObjectWindow);	// oder SelectIdentObjTyp

		THROW_FAILED_HRESULT (WPersistStreamInit(wOrigObjs)->InitNew());
		THROW_FAILED_HRESULT (ISeq->AddAction (wOrigObjs));	// 1. Seite zur Folge hinzufügen

	// 2. Seite wird von Hand zusammengebaut
	WPropertyActionSequence Choice (CLSID_PropertyChoice);	// 2. Seite enthält 2 PropertyPages

		THROW_FAILED_HRESULT (WPersistStreamInit(Choice)->InitNew());

	WPropertyAction wRegOperat (CLSID_RegOperatPropAct);	// Operationen mit Bezugsobjekten

		THROW_FAILED_HRESULT (WPersistStreamInit(wRegOperat)->InitNew());
		THROW_FAILED_HRESULT (Choice->AddAction (wRegOperat));

	WPropertyAction wSetsOperat (CLSID_SetsOperatPropAct);	// Mengenoperationen

		THROW_FAILED_HRESULT (WPersistStreamInit(wSetsOperat)->InitNew());
		THROW_FAILED_HRESULT (Choice->AddAction (wSetsOperat));

	WPropertyAction wLineSplit (CLSID_LineSplitPropAct);	// Splitten von Linienobjekten

		THROW_FAILED_HRESULT (WPersistStreamInit(wLineSplit)->InitNew());
		THROW_FAILED_HRESULT (Choice->AddAction (wLineSplit));

	WPropertyAction wAreaBuild (CLSID_AreaBuildPropAct);	// Bilden von Flächenobjekten

		THROW_FAILED_HRESULT (WPersistStreamInit(wAreaBuild)->InitNew());
		THROW_FAILED_HRESULT (Choice->AddAction (wAreaBuild));

		THROW_FAILED_HRESULT (ISeq->AddAction (WPropertyAction(Choice)));	// 2. Seite zur Folge hinzufügen

	// 3. Seite wieder einfach instantiieren 
	WPropertyAction wOptions (CLSID_OptionsPropAct);

		THROW_FAILED_HRESULT (WPersistStreamInit(wOptions)->InitNew());
		THROW_FAILED_HRESULT (ISeq->AddAction (wOptions));		// 3. Seite zur Folge hinzufügen

		WSetGeoOperatOptionsTarget(wRegOperat)->SetOperatOptionsSite(WGetGeoOperatOptions(wOptions));
		WSetGeoOperatOptionsTarget(wSetsOperat)->SetOperatOptionsSite(WGetGeoOperatOptions(wOptions));
		WSetGeoOperatOptionsTarget(wLineSplit)->SetOperatOptionsSite(WGetGeoOperatOptions(wOptions));
		WSetGeoOperatOptionsTarget(wAreaBuild)->SetOperatOptionsSite(WGetGeoOperatOptions(wOptions));

	// 4. Seite wieder einfach instantiieren 
	WPropertyAction wDestOClass (CLSID_ModifyIdent);

#if _TRiAS_VER < 0x0300
	WPropertyAction2 Init (wDestOClass);
	WDataObject Data (CLSID_DataTransferObject);	// throws hr
	CComVariant v ("CheckMode=1;Checked=0;");

		THROW_FAILED_HRESULT (SetVariantData (v, Data, &c_feInitPropAct));
		THROW_FAILED_HRESULT (Init -> InitFromData (Data, false, 0L));
#else
		THROW_FAILED_HRESULT (WPersistStreamInit(wDestOClass)->InitNew());
#endif // _TRiAS_VER < 0x0300
		THROW_FAILED_HRESULT (ISeq->AddAction (wDestOClass));	// 4. Seite zur Folge hinzufügen
	}
	catch (_com_error& e) 
	{
		if (REGDB_E_CLASSNOTREG == _COM_ERROR(e))
		{
		ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);

			MessageBox (__hWndM, "Es sind nicht alle Klassen registriert!", resTitel.Addr(),
						MB_ICONERROR | MB_OK);
		}

		return _COM_ERROR (e);
	}

	*ppISeq = ISeq.detach();
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Öffnen des PropertySequenceSubStorages
HRESULT GetSubPropSeqStorage (IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

WStorage IRootStg;

	if (!DEX_GetProjectStorage(*IRootStg.ppv()))
		return E_FAIL;

	USES_CONVERSION;

WStorage IStg;
HRESULT hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
	
	if (FAILED(hr)) {
	// mit Schreibschutz versuchen
		hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						NULL, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;
	}

CLSID clsId;

	hr = ReadClassStg (IStg, &clsId);
	if (FAILED(hr)) return hr;

	if (!IsEqualCLSID (clsId, CLSID_PropertyActionSequence))
		return E_FAIL;

	*ppIStg = IStg.detach();

	return hr;
}


// --------------------------------------------------------------------------------------------
HRESULT SavePropSeq (LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg)
{
HRESULT hr = E_FAIL;
WStorage IStg (pIStg);

	USES_CONVERSION;
	if (NULL == pIStg) {	// SubStorage sicher anlegen, da es noch nicht existiert
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> CreateStorage (A2OLE(g_cbPropertySequences),  
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
						0L, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;

		hr = WriteClassStg (IStg, CLSID_PropertyActionSequence);
		if (FAILED(hr)) return hr;
	}

	try {
	WStream IStm;
	WPersistStream IPersistStm (pISeq);		// throws hr
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
		hr = IStg -> CreateStream (A2OLE(strName.c_str()), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		hr = OleSaveToStream (IPersistStm, IStm);	// und wegschreiben
		if (FAILED(hr)) _com_issue_error(hr);

		hr = IStm -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	hr = IStg -> Commit (STGC_DEFAULT);
	if (SUCCEEDED(hr))
		DEX_SetDirtyGeoDB(true);

	return hr;
}

// VisInfo rücksetzen ---------------------------------------------------------
// File: RESETVIS.CXX

#include "visobjp.hxx"

#include <eieruhr.hxx>
#include <ipropseq.hxx>
#include <xtsnguid.h>
#include <selobwnd.h>
#include <dirisole.h>

#include <Com/PropertyActionBaseDataImpl.cpp>
#include <Atl/Ciid.h>

#include "visobj.h"
#include "visobj.hxx"		// Klasse für diese Erweiterung

#include "ResetVisAddEntryCB.h"
#include "ResetHideAddEntryCB.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumLONG **ppv);
short OTypToBits (short iOTyp);

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PropertyAction2);
DefineSmartInterface(AddEntryCallback);
DefineSmartInterface(InitAddEntryCallback);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(Stream);
DefineSmartInterface(DataObject);
DefineSmartInterface(EnumLONG);

///////////////////////////////////////////////////////////////////////////////
// VisInfo an einem Objekt rücksetzen
BOOL ObjResetVisInfoEx (long lONr, HWND hORWnd, UINT_PTR dwData, UINT_PTR dwLocalData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) {
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;
	HOBJECTS lIdent = DEX_GetObjIdent (lONr);
	map<HOBJECTS, DWORD> *pIdents = reinterpret_cast<map<HOBJECTS, DWORD> *>(dwLocalData);

		if (!DEX_GetROModeIdent(lIdent)) {
		DWORD dwType = OTypToBits(DEX_GetObjectType(lONr));

			pE -> ResetObjectVisInfo (lONr);	// Objekt bearbeiten
			if (NULL != pIdents) {
			map<HOBJECTS, DWORD>::iterator it = pIdents -> find(lIdent);

				if (it == pIdents -> end()) {
				pair<map<HOBJECTS, DWORD>::iterator, bool> p =
						pIdents -> insert(map<HOBJECTS, DWORD>::value_type(lIdent, 0));

					it = p.first;
				}
				(*it).second |= dwType;
			}
		}
	}
	return true;
}

BOOL ObjHideVisInfoEx (long lONr, HWND hORWnd, UINT_PTR dwData, UINT_PTR dwLocalData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) {
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
		if (!DEX_GetROModeIdent(DEX_GetObjIdent (lONr))) {
		bool fFirst = false;

			((CVisObjExtension *)g_pTE) -> HandleHiddenFlag (lONr, true, fFirst);	// Objekt bearbeiten
			if (NULL != hORWnd)
				DEX_RefreshEntry(lONr);	// Objekt wieder eingeblendet
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Anzeigen des Dialogfensters zum Rücksetzen der VisInfos
bool CVisObjExtension::RemoveVisInfo (void)
{
map<HOBJECTS, DWORD> Idents;

	if (HandleCustomVisCommands (CLSID_ResetVisAddEntryCB, IDS_RESETVISCAPTION, ObjResetVisInfoEx, 
			NULL, NULL, reinterpret_cast<UINT_PTR>(&Idents)))
	{
		for (map<HOBJECTS, DWORD>::iterator it = Idents.begin(); it != Idents.end(); ++it)
		{
			AdjustIdentifier ((*it).first, OVModVisInfo, (*it).second, false);	// Merkmal am Ident löschen/modifizieren
		}
		return true;
	}
	return false;
}

// aus ORWNd
bool CVisObjExtension::ResetVisInfo (HWND hORWnd)
{
map<HOBJECTS, DWORD> Idents;

	if (HandleCustomVisCommands (CLSID_NULL, IDS_RESETVISCAPTION, ObjResetVisInfoEx, hORWnd,
			NULL, reinterpret_cast<UINT_PTR>(&Idents)))
	{
		for (map<HOBJECTS, DWORD>::iterator it = Idents.begin(); it != Idents.end(); ++it)
		{
			AdjustIdentifier ((*it).first, OVModVisInfo, (*it).second, false);	// Merkmal am Ident löschen/modifizieren
		}
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Anzeigen des Dialogfensters zum 'Ausblenden rücksetzen'
bool CVisObjExtension::RemoveShowInfo (void)
{
	return HandleCustomVisCommands (CLSID_ResetHideAddEntryCB, IDS_RESETSHOWCAPTION, ObjHideVisInfoEx);
}

// aus ORWnd
bool CVisObjExtension::ShowObjects (HWND hORWnd)
{
	return HandleCustomVisCommands (CLSID_NULL, IDS_RESETSHOWCAPTION, ObjHideVisInfoEx, hORWnd);
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// FensterHandle in SequenceContext speichern
	HRESULT SetHWND (IPropertyActionSequence *pISeq, HWND hWnd)
	{
	STGMEDIUM stg;

		ZeroMemory(&stg, sizeof(STGMEDIUM));
		try {
		WDataObject CtxDO;

			THROW_FAILED_HRESULT(pISeq -> GetSequenceContext (CtxDO.ppi()));

		// hGlobal erzeugen
		HGLOBAL hGlobal = GlobalAlloc (GHND, sizeof(HWND));

			if (!hGlobal) _com_issue_error(E_OUTOFMEMORY);

		HWND *pHWnd = (HWND *)GlobalLock (hGlobal);

			if (NULL == pHWnd) _com_issue_error(E_OUTOFMEMORY);

			*pHWnd = hWnd;
			GlobalUnlock (hGlobal);

		// diesen hGlobal im DataObject setzen
			stg.tymed = TYMED_HGLOBAL;
			stg.hGlobal = hGlobal;
			stg.pUnkForRelease = NULL;

			THROW_FAILED_HRESULT(CtxDO -> SetData ((FORMATETC *)&c_feObjectWindow, &stg, true));

		} catch (_com_error &e) {
			if (NULL != stg.hGlobal)
				ReleaseStgMedium (&stg);
			return _COM_ERROR(e);
		}
		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////
// Schreiben/Lesen eines Variant
	HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe)
	{
	// Stream mit Variant generieren
	WStream IStream;
	HRESULT hr = CreateStreamOnHGlobal (NULL, true, IStream.ppi());

		if (FAILED(hr)) return hr;

	// Variant dort rein schreiben
		hr = rv.WriteToStream (IStream);
		if (FAILED(hr)) return hr;

	LARGE_INTEGER li;

		LISet32(li, 0L);
		hr = IStream -> Seek (li, SEEK_SET, NULL);
		if (FAILED(hr))	return hr;

	// diesen Stream im DataObject setzen
	STGMEDIUM stg;

		stg.tymed = TYMED_ISTREAM;
		stg.pstm = IStream.detach();
		stg.pUnkForRelease = NULL;

		hr = pIDO -> SetData ((FORMATETC *)pcfe, &stg, true);
		if (FAILED(hr)) {
			ReleaseStgMedium (&stg);
			return hr;
		}
		return S_OK;
	}
}

bool CVisObjExtension::HandleCustomVisCommands (
	REFCLSID rClsId, UINT uiResCap, HANDLEREMOVECASEPROC pFcn, HWND hORWnd, 
	UINT_PTR dwData, UINT_PTR dwLocalData)
{
ResString resCap (ResID (uiResCap, &RF()), 64);

	return HandleCustomVisCommands(rClsId, resCap, pFcn, hORWnd, dwData, dwLocalData);
}

bool CVisObjExtension::HandleCustomVisCommands (
	REFCLSID rClsId, LPCSTR pcCaption, HANDLEREMOVECASEPROC pFcn, HWND hORWnd, 
	UINT_PTR dwData, UINT_PTR dwLocalData)
{
// RecherchePages zu PropertyChoice zusammenfügen
bool fResult = true;

	COM_TRY {
	// Sequence und Aktion instantiieren
	WPropertyAction Action;
	WPropertyActionSequence Seq (CLSID_PropertyActionSequence);

		THROW_FAILED_HRESULT(WPersistStreamInit(Seq) -> InitNew());
		THROW_FAILED_HRESULT(Seq -> SetDescription(pcCaption));

	WAddEntryCallback AddEntryCB;		// callback object: entscheidet über angezeigte Objektklassen/Objekttypen

		if (NULL == hORWnd) {
		// aus Hauptmenu gerufen
			THROW_FAILED_HRESULT(Action.CreateInstance(CLSID_SelectIdentObjTyp));
			THROW_FAILED_HRESULT(AddEntryCB.CreateInstance(rClsId));
			THROW_FAILED_HRESULT(WInitAddEntryCallback(Action) -> putref_AddEntryCallback(AddEntryCB));
			THROW_FAILED_HRESULT(WPersistStreamInit(Action) -> InitNew());
		}
		else {
			_ASSERTE(IsEqualGUID(CLSID_NULL, rClsId));	// Param wird hier nicht verwendet

		// aus Recherchefenster gerufen
			THROW_FAILED_HRESULT(Action.CreateInstance(CLSID_SelectFromObjectWindow));

		// hORWnd in SequenceContext speichern
			THROW_FAILED_HRESULT(SetHWND(Seq, hORWnd));
			THROW_FAILED_HRESULT(WPersistStreamInit(Action) -> InitNew());

		// Initialisierungsdaten setzen (immer nur aktuelles ORWnd bearbeiten)
		WPropertyAction2 Init;

			if (SUCCEEDED(Action->QueryInterface(Init.ppi()))) {
			WDataObject DataObj;
			CIID Guid (CLSID_SelectFromObjectWindow);
			FORMATETC c_feProgID = {
					RegisterClipboardFormat (Guid.ProgID().c_str()),	// CLIPFORMAT cf
					NULL,											// DVTARGETDEVICE *ptd
					DVASPECT_CONTENT,								// DWORD dwAspect
					-1,												// LONG lindex	
					TYMED_ISTREAM,									// DWORD tymed
				};

			CComVariant v1 ("NoShow=1");

				THROW_FAILED_HRESULT(DataObj.CreateInstance(CLSID_DataTransferObject));
				THROW_FAILED_HRESULT(SetVariantData (v1, DataObj, &c_feProgID));
				THROW_FAILED_HRESULT(Init -> InitFromData (DataObj, false, 0L));
			}
		}

	// Aktion zu Sequence hinzufügen
		THROW_FAILED_HRESULT(Seq -> AddAction (Action));

	WDataObject OutData;
	HRESULT hr = Seq -> DoActions (MVWind() -> Handle(API_WINDOW_HWND), NULL, NULL, OutData.ppi());

		if (SUCCEEDED(hr)) {
		CEierUhr Wait(MWind());
		WEnumLONG EnumObjs;

			if (OutData.IsValid())
				hr = GetEnumLONGData (OutData, EnumObjs.ppi());

		// alle selektierten Objekte durchgehen und von Ihrer VisInfo befreien
			if (SUCCEEDED(hr)) {
			LONG lONr = 0L;

				for (EnumObjs -> Reset(); S_OK == EnumObjs -> Next (1, &lONr, NULL); /**/)
				{
					if (!pFcn (lONr, hORWnd, dwData, dwLocalData)) {
						fResult = false;
						break;
					}
				}
			}
		}

	} COM_CATCH_RETURN(false);
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// die folgende Funktion ist das konkrete äquivalent für 'OleLoadFromStream' 
HRESULT CreateEnumLONGFromStream (IStream *pIStream, REFIID riid, LPVOID *ppEnumOut)
{
	if (NULL == ppEnumOut) return E_POINTER;

	*ppEnumOut = NULL;

	COM_TRY {
	WStream StrClone;

		THROW_FAILED_HRESULT(pIStream -> Clone (StrClone.ppi()));
		THROW_FAILED_HRESULT(OleLoadFromStream (StrClone, riid, ppEnumOut));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Lesen eines EnumLONG aus einem DataObjekt 
HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnumLONG **ppv)
{
	if (NULL == pIDataObj) return E_POINTER;

HRESULT hr = E_FAIL;
STGMEDIUM stg;

	memset (&stg, 0, sizeof(STGMEDIUM));
	COM_TRY {
	// Testen, ob das gewünschte Format überhaupt da ist
		THROW_FAILED_HRESULT(pIDataObj -> QueryGetData ((FORMATETC *)&c_feSelectedObjects));
		if (NULL == ppv)	
			return S_OK;				// nur abfragen, ob Format vorhanden ist

	// Daten vom DataObject geben lassen
		THROW_FAILED_HRESULT(pIDataObj -> GetData ((FORMATETC *)&c_feSelectedObjects, &stg));

	// Einlesen des Enumerators aus den erhaltenen STGMEDIUM
		THROW_FAILED_HRESULT(CreateEnumLONGFromStream (stg.pstm, IID_IEnumLONG, (LPVOID *)ppv));
		ReleaseStgMedium (&stg);

	} COM_CATCH_OP (
		if (TYMED_NULL != stg.tymed)
			ReleaseStgMedium (&stg);
	);
	return S_OK;
}


//bool CVisObjExtension :: RemoveVisInfo (void)
//{
//CResetVisInfoDlg RVIDlg (MWind(), &RF(), GetIdentMCode (false, m_pActSight));
//
//	if (RVIDlg.Init ()) {
//		RVIDlg.Show (Centre);
//		return RVIDlg.Result();
//	}
//	return false;
//}

/////////////////////////////////////////////////////////////////////////////////
//// Einträge einfügen
//typedef struct tagRESETDATA {
//	long m_lMCode;
//	short m_iIdBase;
//	MultiSelListBox *m_lbIdents;
//} RESETDATA;
//
//inline
//bool AddEntry (RESETDATA *pRD, char cChar, LPCSTR pcOKS, LPCSTR pcKText, long lIdent)
//{
//char cbBuffer[_MAX_PATH];
//
//	wsprintf (cbBuffer, "%s:%c:%s", pcOKS, cChar, pcKText);
//
//// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
//// in Klammern hintendran hängen
//	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
//	char cbConnName[_MAX_PATH];
//	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
//
//		TX_ASSERT(NULL != hPr);
//		if (NULL != DEX_GetDataSourceShortName (hPr, cbConnName)) {
//			strcat (cbBuffer, " (");
//			strcat (cbBuffer, cbConnName);
//			strcat (cbBuffer, ")");
//		}
//	}
//	
//int iIndex = pRD -> m_lbIdents -> AddString (cbBuffer);
//
//	pRD -> m_lbIdents -> SetItemData (iIndex, lIdent);		// Ident wird diesem LB-Eintrag zugeordnet
//	return true;	// weitermachen
//}
//
//extern "C"
//BOOL PASCAL _XTENSN_EXPORT ResetVisInfoIdentEx (long lIdent, DWORD dwType, void *pPtr)
//{
//// Identifikator überprüfen, ob Objekte anders Visualisiert sind
//RESETDATA *pRD = (RESETDATA *)pPtr;
//char cbBuffer[_MAX_PATH];
//
//	if (!ReadTextMerkmal (TT_Identifikator, lIdent, pRD -> m_lMCode, cbBuffer))
//		return true;	// Ident ist nicht visualisiert
//
//// auf zu behandelnde Objekttypen beschränken
//	dwType &= GetObjectTypeBits(CVisObjExtension::StringToIdMode(cbBuffer), OVModVisInfo);
//
//	if (0 != dwType) {
//	// für diesen Identifikator KurzText besorgen
//	PBDDATA pbdData;
//	char KText[33];
//
//		KText[0] = '\0';		// für alle Fälle
//			
//		INITSTRUCT(pbdData, PBDDATA);
//		pbdData.pbdTyp = 'i';
//		pbdData.pbdCode = lIdent;
//		pbdData.pbdKText = KText;
//		pbdData.pbdKTextLen = sizeof(KText) -1;
//		pbdData.pbdLTextLen = 0;
//		DEX_GetPBDData (pbdData);
//		KText[32] = '\0';
//
//	char outBuff[64];
//
//		ClassFromIdentX (lIdent, outBuff);
//		if (dwType & OTPunkt) AddEntry (pRD, 'P', outBuff, pbdData.pbdKText, lIdent);
//		if (dwType & OTLinie) AddEntry (pRD, 'L', outBuff, pbdData.pbdKText, lIdent);
//		if (dwType & OTFlaeche) AddEntry (pRD, 'F', outBuff, pbdData.pbdKText, lIdent);
//		if (dwType & OTText) AddEntry (pRD, 'T', outBuff, pbdData.pbdKText, lIdent);
//	}
//	return true;
//}
//
//// Konstruktor/Destruktor -----------------------------------------------------
//#pragma warning (disable: 4355)
//
//CResetVisInfoDlg :: CResetVisInfoDlg (pWindow pW, ResourceFile *pRF, long lMCode)
//		  : DialogWindow (pW, ResID (RESETVISINFO, pRF)),
//		    m_pbOKButton (this, IDOK),
//		    m_lbIdents (this, IDL_RESETIDENTS),
//		    m_ftToDo (this, IDT_LISTBOXTEXT),
//		    m_lMCode (lMCode)
//{
//	SetCaption (ResString (ResID (IDS_RESETVISCAPTION, pRF), 50));
//	m_ftToDo.SetText (ResString (ResID (IDS_RESETVISTEXT, pRF), 50));	
//	
//	m_pInBuff = NULL;
//}
//
//#pragma warning (default: 4355)
//
//CResetVisInfoDlg :: ~CResetVisInfoDlg (void)
//{
//	DELETE_OBJ (m_pInBuff);
//}
//
//
//bool CResetVisInfoDlg :: Init (void)
//{
//	if (m_lMCode == -1) return false;
//	
//	m_pInBuff = new char [_MAX_PATH];
//	if (m_pInBuff == NULL) return false;
//	
//// ListBox füllen, dazu Identifikatoren dieser Sicht enumerieren lassen
//ENUMTEXTKEYEX ETK;
//RESETDATA RD;
//	
//	RD.m_lMCode = m_lMCode;
//	RD.m_iIdBase = DEX_GetIdBase();
//	RD.m_lbIdents = &m_lbIdents;
//	
//	ETK.eKey = DEX_GetActiveSight (m_pInBuff);
//	ETK.eFcn = (ENUMTEXTKEYEXPROC)ResetVisInfoIdentEx;
//	ETK.ePtr = &RD;
//	ETK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
//	DEX_EnumSightIdentsEx (ETK);	
//	return true;
//}
//
//void _XTENSN_EXPORT CResetVisInfoDlg :: ButtonClick (ControlEvt e)
//{
//	switch ((uint)e.GetControlID()) {
//	case IDOK:
//		EndDlg (RemoveIdentVisInfo());
//		break;
//		
//	case IDCANCEL:
//		EndDlg (0);
//		break;
//		
//	case IDB_RESETHELP:
//		break;
//	}
//}
//
//// Abschließendes bearbeiten der Eingaben -------------------------------------
//
//BOOL PASCAL _XTENSN_EXPORT ObjResetVisInfoEx (long lONr, DWORD, void *pData)
//{
//short Status = DEX_GetObjectStatus (lONr);
//
//	if (Status == OSNormal || Status == OSModified) 
//	{
//	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
//		((CVisObjExtension *)g_pTE) -> ResetObjectVisInfo (lONr);
//	}
//	return true;
//}
//
//DWORD BitsFromType (char *pType)
//{
//	if (NULL == pType)
//		return 0;
//
//// pType zeigt hier auf einen ':'
//	TX_ASSERT(':' == *pType);
//	switch (*(pType+1)) {
//	case 'P': 
//		return OTPunkt;
//	case 'L': 
//		return OTLinie;
//	case 'F': 
//		return OTFlaeche;
//	case 'T': 
//		return OTText;
//	default:
//		break;
//	}
//	return 0;
//}
//
//bool CResetVisInfoDlg :: RemoveIdentVisInfo (void)
//{
//CEierUhr Wait (GetParent());
//short iIndex = m_lbIdents.GetFirstSelected();
//bool fOne = false;
//
//	while (iIndex != -1) {
//	// Merkmale an Objekten löschen
//	long lIdent = m_lbIdents.GetItemData (iIndex);
//	
//		m_lbIdents.GetString (m_pInBuff, iIndex, _MAX_PATH);
//
//	ENUMLONGKEYEX ELK;
//	
//		ELK.eKey = lIdent;
//		ELK.eFcn = (ENUMLONGKEYEXPROC)ObjResetVisInfoEx;
//		ELK.ePtr = NULL;
//		ELK.eData = BitsFromType (strchr (m_pInBuff, ':'));
//		if (!DEX_EnumIdentObjectsEx (ELK))
//			break;		// Fehler o.ä.
//
//	// Merkmal am Ident löschen/modifizieren
//	CVisObjExtension *pE = (CVisObjExtension *)g_pTE;
//
//		if (!pE -> AdjustIdentifier (lIdent, OVModVisInfo, ELK.eData, false))
//			return false;
//
//	// nächster aktiver Eintrag
//		iIndex = m_lbIdents.GetNextSelected();
//		fOne = true;		// wenigstens einer
//	}
//	return fOne;
//}

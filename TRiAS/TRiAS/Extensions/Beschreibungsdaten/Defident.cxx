// Dialogfenster zur Definition einer IdentBeschreibung in einer PBD ----------
// File: DEFIDENT.CXX

#include "idntsdbp.hxx"

#include <Atl/Ciid.h>
#include <Com/ComBool.h>

#include <versions.h>
#include <errinstx.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <TRiASDB.h>
#include <TRiASDBDispIds.h>		// Dispatch Id
#include <eieruhr.hxx>

#include "Strings.h"
#include "identres.h"
#include "defident.h"
#include "defident.hxx"
#include "identsdb.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEXTLEN 		_MAX_PATH

#define TRIASTEXTLEN 		32			// KK991108

#define WM_RECALCOKS	WM_USER+1234

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASProject);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(Dispatch);
DefineSmartInterface(TRiASObjects);

EXTERN_C const CLSID CLSID_TRiASObjectsHandleMap = {0xCD579673,0xAA9D,0x11D1,{0x85,0x8C,0x00,0x60,0x08,0x75,0x13,0x8A}};
#if defined(_SUPPORT_QUERYDEFS)
EXTERN_C const CLSID CLSID_TRiASCollectObjects;
#endif // defined(_SUPPORT_QUERYDEFS)

///////////////////////////////////////////////////////////////////////////////
// wenn Connection der Objektklasse nicht schreibgeschützt ist, dann alle existierenden
// ansonsten alle Objektklassen aus beschreibbaren Datenquellen plus die zu editierende 
// Objektklasse
typedef struct tagEDITIDENTDATA {
	ComboBox *pIdentList;
	INT_PTR lIdent;
	BOOL fROMode;
} EDITIDENTDATA;

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillListBoxWithIdents (long Ident, BOOL, void *pData)
{
HPROJECT hPr = DEX_GetObjectsProject(Ident);

	TX_ASSERT(HACTCONNECTION != hPr);
	if (HACTPROJECT != hPr && !DEX_GetOpenedEx(hPr))
		return TRUE;		// nicht geöffnete Datenquelle

EDITIDENTDATA *pEID = reinterpret_cast<EDITIDENTDATA *>(pData);

	_ASSERTE(NULL != pEID -> pIdentList);
	if (!(!pEID -> fROMode || !DEX_GetROModeEx(hPr) || pEID -> lIdent == Ident))
		return TRUE;		// nicht anzeigen

PBDDATA pbdData;
char cbBuffer[_MAX_PATH] = { '\0' };

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);

char outBuff[_MAX_PATH] = { '\0' };

	ClassFromIdentX (Ident, outBuff);
	strcat (outBuff, ":");
	strcat (outBuff, cbBuffer);

// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
// in Klammern hintendran hängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
			strcat (outBuff, " (");
			strcat (outBuff, cbBuffer);
			strcat (outBuff, ")");
		}
	}

int iIndex = pEID -> pIdentList -> AddString (outBuff);

	pEID -> pIdentList -> AddExtentEntry (outBuff);
	pEID -> pIdentList -> SetItemData (iIndex, Ident);		// Ident wird diesem LB-Eintrag zugeordnet
	return true;	// weitermachen
}

// Kontextsensitive Hilfe -----------------------------------------------------
#include "dlghelp.h"

static DWORD s_dwHelp[] = {
	IDOK,			IDH_DEFIDENTDLG_OK,
	IDCANCEL,		IDH_DEFIDENTDLG_CANCEL,
	IDF_AUXINFO,		IDH_DEFIDENTDLG_AUXINFO,
	IDT_PBDDB,		IDH_DEFIDENTDLG_PBDNAME,
	IDT_DEFIDDBNAME,	IDH_DEFIDENTDLG_PBDNAME,
	IDT_IDENT,		IDH_DEFIDENTDLG_IDENT,
	IDT_DEFIDIDENT,		IDH_DEFIDENTDLG_IDENT,
	IDG_IDENTDESC,		IDH_DEFIDENTDLG_IDENTDESC,
	IDT_SHORTDESC,		IDH_DEFIDENTDLG_SHORTDESC,
	IDE_DEFIDSHORT,		IDH_DEFIDENTDLG_SHORTDESC,
	IDT_LONGDESC,		IDH_DEFIDENTDLG_LONGDESC,
	IDE_DEFIDLONG,		IDH_DEFIDENTDLG_LONGDESC,
	0,			0,		// EndeKennung
};

void DefineIdentDlg::HelpRequest (HelpRequestEvt e)
{
	if (HelpWmHelp == e.RequestType()) {
	const HELPINFO *pHI = e.GetHelpInfo();
	char cbHelpFile[_MAX_PATH];

		strcpy (cbHelpFile, g_cbHelpPath);
		strcat (cbHelpFile, DIALOG_HELP_FILE);

		WinHelp ((HWND)pHI -> hItemHandle, cbHelpFile, 
			 HELP_WM_HELP, (DWORD)s_dwHelp);
	}
}

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

DefineIdentDlg::DefineIdentDlg (pWindow pW, ResID res)
		: DialogWindow (pW, res),
		  OKButton (this, IDOK),
		  CancelButton (this, IDCANCEL),
		  EDKurzText (this, IDE_DEFIDSHORT),
		  EDLangText (this, IDE_DEFIDLONG),
		  m_Connections (this, IDC_CONNECTIONS),
		  m_SelectOKS(this, IDC_SELECTOKS),
#if defined(_DEBUG)
		  m_ROMode (this, IDC_READONLY),
#endif // defined(_DEBUG)
		  m_fIsValid (false), m_fEditExisting(false),
		  _actId(-1),
		  m_hPr(NULL),			// auf aktuelle connection voreinstellen
		  m_lConnCnt(0)
{
	OKButton.Disable();

// KK991108
// Notlösung : Nur für TRiAS-DB
	EDKurzText.SetTextLimit (TRIASTEXTLEN);
}

#pragma warning (default: 4355)

///////////////////////////////////////////////////////////////////////////////
// Initialisierung bei existierendem Identifikator/OKS
BOOL DefineIdentDlg::FInit (long lIdent)
{
CEierUhr Wait(this);
ResString resCap (ResID (IDS_EXISTINGCLASSDESC, &g_pTE -> RF()), 128);

	SetCaption (resCap);

	_actId = lIdent;
	m_fEditExisting = true;
	if (FAILED(InitConnectionControls(lIdent))) {
		m_fIsValid = false;
		return FALSE;
	}
	return InitRemainingControls();
}

// Initialisierung bei neuem Identifikator/OKS
BOOL DefineIdentDlg::FInit (LPCSTR pcOKS, HPROJECT hPr)
{
CEierUhr Wait(this);
ResString resCap (ResID (IDS_NEWCLASSDESC, &g_pTE -> RF()), 128);

	SetCaption (resCap);

	_actId = 0;
	m_fEditExisting = false;
	if (FAILED(InitConnectionControls(0, hPr))) {
		m_fIsValid = false;
		return FALSE;
	}
	return InitRemainingControlsOKS(pcOKS);
}

BOOL DefineIdentDlg::InitRemainingControls()
{
	TX_ASSERT(NULL != m_hPr && -1 != _actId);

// Variablen initialisieren
char Buffer[MAX_OKS_LENX];

	ClassFromIdentX (m_hPr, _actId, Buffer);
	if (InitOKSList(Buffer) && InitDescTexts()) {
		AdjustOK();
		return TRUE;
	}
	return FALSE;
}

BOOL DefineIdentDlg::InitOKSList(LPCSTR pcOKS)
{
	_ASSERTE(NULL == pcOKS || 0 != _actId);
	
// ListBox füllen:
// wenn Connection der Objektklasse nicht schreibgeschützt ist, dann alle exitierenden
// ansonsten alle Objektklassen aus beschreibbaren Datenquellen plus die zu editierende 
// Objektklasse
EDITIDENTDATA EID;

	EID.pIdentList = &m_SelectOKS;
	EID.lIdent = _actId;
	EID.fROMode = DEX_GetROModeEx(m_hPr);
	
ENUMLONGKEY ELK;

	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillListBoxWithIdents;
	ELK.ePtr = (void *)&EID;
	DEX_EnumPBDData (ELK);

	if (m_SelectOKS.GetCount() > 0) {
		if (NULL != pcOKS && '\0' != pcOKS[0]) 
			m_SelectOKS.SetText (pcOKS);
		else if (HACTPROJECT != m_hPr) {
		char cbBuffer[TEXTLEN];

			if (m_fEditExisting) {
				m_SelectOKS.ChangeCurrentIndex (0);
				m_SelectOKS.GetString (cbBuffer, 0, sizeof(cbBuffer));

			char *pT = strchr (cbBuffer, ':');

				TX_ASSERT(NULL != pT);
				*pT = '\0';
				m_SelectOKS.SetText (cbBuffer);
			}
			else {
			// beim Neuerfassen einen neuen OKS anbieten
				_actId = DEX_GetUniqueSysICodeEx(m_hPr);

				m_SelectOKS.ChangeCurrentIndex (-1);
				m_SelectOKS.SetText (ultoa(_actId, cbBuffer, DEX_GetIdBase()));
			}
		} 
		else 
			m_SelectOKS.ChangeCurrentIndex (-1);
	}
	return TRUE;
}

BOOL DefineIdentDlg::InitDescTexts()
{
// Einträge initialisieren
	{
	ErrInstall EI (WC_NOIDENT);
	PBDDATA pbdData;

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = _actId;
		pbdData.pbdKText = new char [TEXTLEN+2];	// gesucht
		pbdData.pbdLText = new char [1024];
		pbdData.pbdKTextLen = TEXTLEN+1;
		pbdData.pbdLTextLen = 1024;

	// PBD-Info holen
		if (pbdData.pbdKText) pbdData.pbdKText[0] = '\0';
		if (pbdData.pbdLText) pbdData.pbdLText[0] = '\0';
		DEX_GetPBDDataEx (m_hPr, pbdData);

		if (pbdData.pbdKTextLen > 0) {
			pbdData.pbdKText[TEXTLEN] = '\0';
			EDKurzText.SetText (pbdData.pbdKText);
		}
		if (pbdData.pbdLTextLen > 0) 
			EDLangText.SetText (pbdData.pbdLText);

	// Speicher wieder freigeben
		DELETE_OBJ(pbdData.pbdKText);
		DELETE_OBJ(pbdData.pbdLText);
	}

// KK991108
// Notlösung : Nur für InterTRiAS-DB
	EDKurzText.SetTextLimit (TRIASTEXTLEN);
	EDKurzText.SetFocus();
	return TRUE;
}

BOOL DefineIdentDlg::InitRemainingControlsOKS(LPCSTR pcOKS)
{
	TX_ASSERT(NULL != m_hPr && NULL != pcOKS);

// Variablen initialisieren
	if (FAILED(IdentFromClassX (m_hPr, pcOKS, (ULONG *)&_actId, false)))
		return InitOKSList();	// Ident ist neu

	if (InitOKSList() && InitDescTexts()) {
		AdjustOK();
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung bei neuem Identifikator/OKS
HRESULT DefineIdentDlg::InitConnectionControls (long lIdent, HPROJECT hPr)
{
// Anzahl der Connections feststellen
int iIndex = -1;
CComBSTR bstrActName;
bool fOKUpdatable = false;

	USES_CONVERSION;
	COM_TRY {
		TX_ASSERT(NULL == m_hPr);
	
		if (HACTCONNECTION == hPr) {
			if (0 == lIdent) {
				_ASSERTE(!m_fEditExisting);
				hPr = DEX_GetDataSourceHandle();
			}
			else 
				hPr = DEX_GetObjectsProject (lIdent);
		}

	// Objektklasse nicht schreibgeschützt heißt hier: 
	//	existierende Objektklasse nicht schreibgeschützt oder
	//	existierende Objektklasse schreibgeschützt, aber Texte editierbar oder
	//	neue Objektklasse
		fOKUpdatable = !DEX_GetROModeEx(hPr);
		
	// alle Connections durchgehen und feststellen:
	// aktuelle Connection, ob beschreibbare Connection existiert
	WTRiASProject Prj;

		if (!DEX_GetActiveProjectPtr (*Prj.ppi())) 
			_com_issue_error(E_UNEXPECTED);		// snh

	// Zuordnungsobjektklassen
	CComBSTR bstrName;
	int iNew = -1;
	int iCorr = 0;		// Korerektur für laufenden Index in ComboBox

		m_lConnCnt = 0;

#if defined(_SUPPORT_QUERYDEFS)
		if (((CIdentsDBExtension *)g_pTE) -> HasQueryDef()) {
			bstrName.LoadString (IDS_QUERYDEF_OBJECTS);
			iNew = m_Connections.AddString (OLE2A(bstrName));
			if (-1 != iNew)
				m_Connections.SetItemData (iNew, reinterpret_cast<INT_PTR>(HACTPROJECT));		// ProjectHandle zuordnen

			iCorr = 1;
			if (!DEX_GetROModeEx(HACTPROJECT))
				m_lConnCnt++;			// Zähler der beschreibbaren Connections

			if (hPr == HACTPROJECT) {
				iIndex = 0;			// aktuelles Projekt ist gefragt
				m_hPr = HACTPROJECT;
				bstrActName = bstrName;
			}
		}
#endif // defined(_SUPPORT_QUERYDEFS)

	// einzelne Datenquellen hinzufügen
	WTRiASConnections Conns;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			CComBool fUpdatable;

				THROW_FAILED_HRESULT(Conn -> get_Updatable (&fUpdatable));

			// nachsehen, ob die Objektklasse zu dieser Connection gehört
			WTRiASDatabase DBase;
			INT_PTR lHandle = 0; 

				THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> get_Handle (&lHandle));

			// die Connection wird nur angezeigt, wenn:
			//	die Objektklasse nicht schreibgeschützt ist oder
			//	die Connection nicht schreibgeschützt ist oder
			//	die zu editierende Objektklasse zu dieser Connection gehört
			// (in dieser Reihenfolge)
				if (fOKUpdatable || bool(fUpdatable) || hPr == reinterpret_cast<HPROJECT>(lHandle)) {
				// geöffnet und beschreibbar
					THROW_FAILED_HRESULT(Conn -> get_Name (CLEARED(&bstrName)));
					iNew = m_Connections.AddString (OLE2A(bstrName));

				// wenns die aktuelle ist, dann den Index speichern
					if (hPr == reinterpret_cast<HPROJECT>(lHandle) || -1 == iIndex) {
						iIndex = iNew;	// aktuelle oder irgend eine mit Schreibzugriff
						m_hPr = reinterpret_cast<HPROJECT>(lHandle);
						bstrActName = bstrName;
					}
					m_lConnCnt++;		// Zähler der beschreibbaren Connections

					if (-1 != iNew)
						m_Connections.SetItemData (iNew, lHandle);		// ProjectHandle zuordnen
				}
			}
		}
	} COM_CATCH;

// aktuelle Datenquelle aktivieren
	if (NULL == m_hPr) {
	// Ident/OKS bekannt, Schreibzugriff nicht möglich --> keine Neudefinition möglich
		TX_ASSERT(-1 == iIndex);
		m_fIsValid = false;
		return E_FAIL;
	} else {
	// Ident/OKS bekannt, nur aktuelle connection anzeigen
		TX_ASSERT(-1 != iIndex);
		m_fIsValid = true;
	}

	AdjustConnectionControls(m_lConnCnt, iIndex, OLE2A(bstrActName), lIdent);		// entsprechendes Control anzeigen
	return S_OK;
}

HRESULT DefineIdentDlg::AdjustConnectionControls(long lCnt, int iIndex, LPCSTR pcName, long lIdent)
{
// gibt es überhaupt eine geöffnete Connection
	TX_ASSERT(lCnt > 0);
	if (-1 != iIndex)
		m_Connections.ChangeCurrentIndex (iIndex);

// ist die gewählte Connection schreibgeschützt ?
	TX_ASSERT(NULL != m_hPr);
	if (DEX_GetROModeEx (m_hPr)) {
//		m_Connections.Disable();
#if defined(_DEBUG)
		m_ROMode.SetChecked (TRUE);
		m_ROMode.Disable();
#endif // defined(_DEBUG)

		if (!DEX_GetGDODataSourceEx(m_hPr)) {
		// DEX_GetGDODataSourceEx(m_hPr) steht für Editierbarkeit der Beschreibungsdaten von
		// Objektklassen trotz Schreibschutz
			m_SelectOKS.Disable();
			EDKurzText.ForwardEvent (EM_SETREADONLY, TRUE);
			EDLangText.ForwardEvent (EM_SETREADONLY, TRUE);
		}
	} 
#if defined(_DEBUG)
	else if (NULL != lIdent) {
		m_ROMode.Enable();
		m_ROMode.SetChecked (DEX_GetROModeIdent (lIdent));
	}
	else {
		m_ROMode.Enable();
		m_ROMode.SetChecked (FALSE);
	}
#endif // defined(_DEBUG)
	return S_OK;
}

BOOL DefineIdentDlg::IsIdentIdent (long lIdent, HPROJECT *phPr)
{
	if (NULL == phPr)
		return FALSE;

	*phPr = DEX_GetObjectsProject (lIdent);
	return *phPr ? TRUE : FALSE;
}

// EventHandler ----------------------------------------------------------------
void _XTENSN_EXPORT DefineIdentDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (OnOK());	// ok und raus
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;
	}
}

void DefineIdentDlg::ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_CONNECTIONS:
		{
			COM_TRY {
			// ProjectHandle der ausgewählten Connection finden
			int iIndex = m_Connections.GetCurrentIndex();

				TX_ASSERT(-1 != iIndex);
			
			HPROJECT hPr = reinterpret_cast<HPROJECT>(m_Connections.GetItemData (iIndex));

				TX_ASSERT(NULL != hPr);
				if (hPr != m_hPr) {
					m_fEditExisting = false;	// neu erzeugen
					EDKurzText.SetModified();	// Wegschreiben erzwingen
					EDLangText.SetModified();
				}
				m_hPr = hPr;

				if (DEX_GetROModeEx (m_hPr)) {
#if defined(_DEBUG)
					m_ROMode.SetChecked (TRUE);
					m_ROMode.Disable();
#endif defined(_DEBUG)

					if (!DEX_GetGDODataSourceEx(m_hPr)) {
					// DEX_GetGDODataSourceEx(m_hPr) steht für Editierbarkeit der Beschreibungsdaten von
					// Objektklassen trotz Schreibschutz
						m_SelectOKS.Disable();
						EDKurzText.ForwardEvent (EM_SETREADONLY, TRUE);
						EDLangText.ForwardEvent (EM_SETREADONLY, TRUE);
					}
				} else {
#if defined(_DEBUG)
					m_ROMode.SetChecked (FALSE);
					m_ROMode.Enable();
#endif // defined(_DEBUG)

					m_SelectOKS.Enable();
					EDKurzText.ForwardEvent (EM_SETREADONLY, FALSE);
					EDLangText.ForwardEvent (EM_SETREADONLY, FALSE);
				}

			} COM_CATCH_NORETURN_OP(m_hPr = NULL);
		}
		break;

	case IDC_SELECTOKS:
		m_SelectOKS.ForwardEvent (WM_SETREDRAW, FALSE);
		PostEvent (WM_RECALCOKS);
		break;
	}
}

void DefineIdentDlg::EditChange (ControlEvt e)
{
	if (IDE_DEFIDSHORT == (uint)e.GetControlID()) 
		AdjustOK();
}

void DefineIdentDlg::AdjustOK()
{
// OK-Button behandeln
	if (NULL != m_hPr) {
		if ((!DEX_GetROModeEx (m_hPr) || DEX_GetGDODataSourceEx(m_hPr)) && EDKurzText.GetTextLen() > 0) 
		{
		int iIndex = m_SelectOKS.GetCurrentIndex();
		char cbBuffer[TEXTLEN];

			if (-1 != iIndex) {
				m_SelectOKS.GetString (cbBuffer, iIndex, sizeof(cbBuffer));
				if ('\0' == cbBuffer[0])
					m_SelectOKS.GetText (cbBuffer, sizeof(cbBuffer));
			} else 
				m_SelectOKS.GetText (cbBuffer, sizeof(cbBuffer));

			if ('\0' != cbBuffer[0]) {
				OKButton.Enable();
				return;
			}
		}
	}

// ansonsten passivieren
	OKButton.Disable();
}

LRESULT DefineIdentDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_COMMAND:
	// nur hier behandeln, wenn CBN_CLOSEUP für m_SelectOKS
		if (m_SelectOKS.Handle() != reinterpret_cast<HWND>(e.LParam()) || 
			IDC_SELECTOKS != LOWORD(e.WParam()) || CBN_CLOSEUP != HIWORD(e.WParam())) 
			break;

		m_SelectOKS.ForwardEvent (WM_SETREDRAW, FALSE);
		PostEvent (WM_RECALCOKS);
		break;	

	// schneidet den Textteil im Editcontrol der Combobox ab, so daß lediglich
	// der OKS zu sehen bleibt
	case WM_RECALCOKS:
		{
		int iIndex = m_SelectOKS.GetCurrentIndex();

			if (-1 != iIndex) {
			char cbBuffer[TEXTLEN];

				m_SelectOKS.GetString (cbBuffer, iIndex, sizeof(cbBuffer));

			char *pT = strchr (cbBuffer, ':');

				TX_ASSERT(NULL != pT);
				if (NULL != pT) 
					*pT = '\0';
				m_SelectOKS.ForwardEvent (WM_SETREDRAW, TRUE);
				m_SelectOKS.SetText (cbBuffer);
			} else 
				m_SelectOKS.ForwardEvent (WM_SETREDRAW, TRUE);
		}
		return TRUE;

	default:
		break;
	}
	return DialogWindow::Dispatch(e);
}

int DefineIdentDlg::OnOK()
{
// evtl. Identifikator erzeugen
CEierUhr Wait(this);
char cbBuffer[MAX_OKS_LENX];

	m_SelectOKS.GetText (cbBuffer, sizeof(cbBuffer));
	if (!m_fEditExisting) {
		TX_ASSERT(NULL != m_hPr);

#if defined(_SUPPORT_QUERYDEFS)
		if (HACTPROJECT == m_hPr) {
		CIID Guid (CLSID_TRiASCollectObjects);
		os_string strGuid = Guid;

			strGuid += cbBuffer;
			if (FAILED(IdentFromClassX (m_hPr, strGuid.c_str(), (ULONG *)&_actId, true)))
				return ONOK_ERROR;
		} else 
#endif // defined(_SUPPORT_QUERYDEFS)
		{
			if (FAILED(IdentFromClassX (m_hPr, cbBuffer, (ULONG *)&_actId, true)))
				return ONOK_ERROR;
		}
	}

// zu bestimmtem Ident den OKS speichern
MODOBJCLASSCODE MOCC;

	INITSTRUCT(MOCC, MODOBJCLASSCODE);
	MOCC.ulIdent = _actId;
	MOCC.pcClass = cbBuffer;
	MOCC.fOverWrite = true;
	
HRESULT hr = DEX_ModObjectClassCodeEx(m_hPr, MOCC);
	
	if (FAILED(hr))	return ONOK_ERROR;		// Fehler

// aktuelle Texte holen und wegschreiben
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = _actId;
	pbdData.pbdTemp = false;

	if (EDKurzText.isModified() || EDLangText.isModified()) {
	char KT[TEXTLEN+1];
	int maxLen = 0;
	char *lT = new char [maxLen = EDLangText.GetTextLen()+1];
		
		EDKurzText.GetText (KT, TEXTLEN+1);
		pbdData.pbdKText = KT;
		pbdData.pbdKTextLen = strlen (KT);
		if (lT != NULL) {
			EDLangText.GetText (lT, maxLen);
			pbdData.pbdLText = lT;
			pbdData.pbdLTextLen = maxLen -1;
		}

	ITriasXtensionSite *pXtsnSite = NULL;
	HRESULT hr = g_pTE -> GetXtensionSite (&pXtsnSite);
	LPUNDOREDOPBDDATA pIUndo = NULL;

		if (SUCCEEDED(hr)) {
			hr = pXtsnSite -> CreateInstance (NULL, CLSID_UndoRedoObject, 
						IID_IUndoRedoPBDData, (LPVOID *)&pIUndo);
			pXtsnSite -> Release();
			if (SUCCEEDED(hr))
				hr = pIUndo -> InitModify ((const PBDDATA *)&pbdData, NULL);
			if (FAILED(hr)) {
				pIUndo -> Release();
				pIUndo = NULL;
			}
		}

	ErrCode RC = DEX_ModPBDDataEx (m_hPr, pbdData);

		_ASSERTE(EC_OKAY == RC);
		if (EC_OKAY == RC) {
			if (pIUndo) 
				DEX_AddUndoRedo (pIUndo);
		}

#if defined(_DEBUG)
	// ReadOnlyState schreiben
	MODIFYROMODE MRM;

		INITSTRUCT(MRM, MODIFYROMODE);
		MRM.lTarget = _actId;
		MRM.fROMode = m_ROMode.isChecked() ? TRUE : FALSE;
		DEX_SetROModeIdent (MRM);
#endif // defined(_DEBUG)

		if (pIUndo) pIUndo -> Release();

		DEXN_PBDIdentChanged (_actId);
		App::Exec (ExecWhileEvent);
		DELETE_OBJ(lT);
	}
	return m_fEditExisting ? ONOK_MODIFIED : ONOK_CREATED;
}

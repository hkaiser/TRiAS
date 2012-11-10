//	CONNECT.CPP:	Projektbezogene ODBC-Anbindung definieren.
//
//	Erarbeitet: J. Benkenstein					Stand vom: 29.06.95

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten

#include <odbcinst.h>		// SQLCreateDataSource u.a.

#include <xtsnaux.hxx>		// WideString
#include <errinstx.hxx> // ErrInstall
#include <xtensnn.h>

#include <hpp/getodbci.hpp>		// ODBC-Infos lesen
#include <hpp/tableset.hpp>		// CTables
#include <hpp/columnst.hpp>		// CColumnStatus
#include <hpp/waitcur.hpp>		// CWaitCursor
#include <hpp/helptext.hpp>		// CHelpText
#include "tablinfo.hpp"		// CTableInfoTree
#include <hpp/createwh.hpp>		// CCreateWhereKlDlg
#include <hpp/strdup.hxx>		// StringDup
#include <hpp/objinfo.hpp>		// ObjMerkmalInfo
#include <hpp/TabDlgs.hpp>		// CTabbedDialogs

#include "profile.hpp"		// Profile
#include "reldlg.hpp"		// CRelDialog
#include "UserDlg.h"		// CUserDlg
#include "FileDlg.h"		// CFileDsnPage
#include "connect.hpp"		// zugh. Header

#include "myhelper.h"		// InvalidIdent()
#include "fakename.h"		// AppNamen dynamisch anpassen

short const ConnectionLength = 256;			// Länge eines Wertes

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL __export FAR PASCAL FillObjFeatureList (ulong Ident, DWORD dw, void* pData);


// externe Funktionen
void CallMessageQueue (void);				// Steuerung an Windows zum Nachzeichnen

// externe Variablen
extern int g_sMkBase;						// und Merkmale

BEGIN_MESSAGE_MAP(CConnect, CDialog)
	//{{AFX_MSG_MAP(CConnect)
	ON_CBN_SELCHANGE(IDC_OBJKLASSEN, OnSelChangeObjKlasse) 
	ON_CBN_SELCHANGE(IDC_MERKMALSKODES, OnSelChangeMerkmal)	
	ON_CBN_SELCHANGE(IDC_TABLES, OnSelChangeTable)
	ON_CBN_SELCHANGE(IDC_KOPPELFELD, OnSelChangeKoppelField)
	ON_BN_CLICKED(IDB_RELATIONEN, CreateRelations)
	ON_EN_CHANGE(IDE_WHEREKLAUSEL, OnChangeWhereKlausel)
	ON_EN_CHANGE(IDE_ALIASNAME, OnChangeAliasName)
	ON_BN_CLICKED(IDB_MERKMALSKODE, WantMerkmalsKodes)
	ON_BN_CLICKED(IDB_SELECTWHERE, WantWhereKlausel)
	ON_BN_CLICKED(IDB_CREATEWHERE, CreateWhereKlausel)
	ON_BN_CLICKED(IDB_STORECONNECT, StoreConnection)
	ON_EN_SETFOCUS(IDE_WHEREKLAUSEL, OuputKlauselDescription)
	ON_EN_SETFOCUS(IDE_ALIASNAME, OutputAliasDescription)
	ON_BN_CLICKED(IDB_STANDARD_DSN, StandardDataSource)	
	ON_BN_CLICKED(IDB_BEENDEN, Beenden)
	ON_BN_CLICKED(IDB_LASTENTRY, OnLastentry)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// definition der Merkmalsauswahl
// Merkmalsnamen setzen
#define MERKMALE_SETTEXT(a)			m_cbMerkmalsKodes.SelectString(-1, a)
// Merkmalsnamen holen
#define MERKMALE_GETTEXT(a)			m_cbMerkmalsKodes.GetLBText(m_cbMerkmalsKodes.GetCurSel(), a)
// Merkmalscode holen
#define MERKMALE_GETITEMDATA()		m_cbMerkmalsKodes.GetItemData(m_cbMerkmalsKodes.GetCurSel())
// kein Merkmalsname setzen
#define MERKMALE_SETEMPTY()			m_cbMerkmalsKodes.SetCurSel(-1)
// ist was vorhanden
#define MERKMALE_TEST_AVAILABLE()	(m_cbMerkmalsKodes.GetCount() > 0)
// ist was selektiert
#define MERKMALE_TEST_PRESENT()		(m_cbMerkmalsKodes.GetCurSel() >= 0)

/////////////////////////////////////////////////////////////////////////////
// CConnect dialog
CConnect::CConnect (CWnd* pParent, long lActObjNr)
		  : CDialog (CConnect::IDD, pParent), m_tbDsn (3)
{
	//{{AFX_DATA_INIT(CConnect)
	m_bResult = TRUE;			// alles OK
	m_lObjNr = lActObjNr;		// aktuelle Objekt-Nr. speichern
	m_bInfosStored = TRUE;		// speichern jetzt nicht notwendig
	m_tDsn = NoDataSource;
	//}}AFX_DATA_INIT
}                           

void CConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnect)
	DDX_Control(pDX, IDC_TAB_DSN, m_tbDsn);
	DDX_Control(pDX, IDB_LASTENTRY, m_btLastEntry);
	DDX_Control(pDX, IDC_OBJKLASSEN, m_cbObjKlassen);		
	DDX_Control(pDX, IDC_MERKMALSKODES, m_cbMerkmalsKodes);			
	DDX_Control(pDX, IDC_TABLES, m_cbTables);
	DDX_Control(pDX, IDC_KOPPELFELD, m_cbKoppelFields);
	DDX_Control(pDX, IDB_MERKMALSKODE, m_btMermkalsKodes);
	DDX_Control(pDX, IDB_SELECTWHERE, m_btWhereKlausel);	            
	DDX_Control(pDX, IDB_RELATIONEN, m_btRelations);
	DDX_Control(pDX, IDB_BEENDEN, m_btBeenden);
	DDX_Control(pDX, IDB_STORECONNECT, m_btStoreConnection);
	DDX_Control(pDX, IDB_CREATEWHERE, m_btCreateWhereKlausel);
	DDX_Control(pDX, IDB_STANDARD_DSN, m_btStandard);	
	DDX_Control(pDX, IDE_ALIASNAME, m_edAliasName);
	DDX_Control(pDX, IDE_WHEREKLAUSEL, m_edWhereKlausel);
	DDX_Control(pDX, IDT_CONNECTDESCR, m_stDescription); 
	//}}AFX_DATA_MAP
}

BOOL CConnect::OnInitDialog(void)
{              
	CallMessageQueue ();
	CWaitCursor wc;
	
	CDialog::OnInitDialog();
	
	// den AppNmane faken
	FakeName(GetDlgItem(IDC_STATIC1));

	if (m_bResult == FALSE)
	{
		EndDialog (IDCANCEL);
		return FALSE;
	}		
	
//	Font für Beschreibungsfeld einstellen
	m_stDescription.InitFont ();
			        
	m_bResult = FALSE;		// noch nichts getan
	

//	KK000420 - ELK auf ENT, da ID der Sicht !!
//	Objektklassen ausgeben
//	ENUMLONGKEY ELK;
//	memset (&ELK, 0, sizeof (ELK));
//	ELK.eFcn = (ENUMLONGKEYPROC) FillObjMerkmalList;	// zu rufende Funktion
//	ELK.eKey = 'i';								// Suchschlüssel (Identifikator)

	ObjMerkmalInfo oi;
	oi.m_lType = 'i';
	oi.m_pCComboBox = &m_cbObjKlassen;

//	ELK.ePtr = (void*) &oi;								// durchgereichte Daten
	

// KK000411
//	BOOL iRet = DEX_EnumPBDData (ELK);

//	Nur Klassen der Sicht !!!
//	Alle O'Klassen der Sicht formal durchzählen

		ENUMTEXTKEY ENT;
		memset (&ENT, 0, sizeof (ENT));
		ENT.eKey = NULL;	// NULL = aktuelle Sicht

//	Bestimmen der Anzahl der Objektklassen
		ENT.eFcn = ( ENUMTEXTKEYPROC) FillObjMerkmalList;	// zu rufende Funktion

		ENT.ePtr = (void*) &oi;

		DEX_EnumSightIdents(ENT);


//	if (! DEX_EnumPBDData (ELK))
//		return FALSE;

//	wenn keine IDs in DB vorhanden --> beenden		
	if (m_cbObjKlassen.GetCount() <= 0) {                        
		EndDialog (IDCANCEL);
		DEX_Error (RC_OnInitDlgCConect, WC_NOIDENT);	// keine Objekt-Klassen gefunden
		return FALSE;
	}	
		
// KK000411
// Erst nach Selektieren einer Klasse sollten OE gezeigt werden !
/*----
	ELK.eKey = 'm';				
	oi.m_lType = 'm';
	oi.m_pCComboBox = &m_cbMerkmalsKodes;


	if (! DEX_EnumPBDData (ELK)) {
		EndDialog (IDCANCEL);
		DEX_Error (RC_OnInitDlgCConect, EC_ILLPARS);	// keine Merkmale gefunden
//		return FALSE;
	}

//	wenn keine Merkmale in DB vorhanden --> beenden		
	if (!MERKMALE_TEST_AVAILABLE()) {
//	if (m_cbMerkmalsKodes.GetCount() <= 0) {                        
		EndDialog (IDCANCEL);
		DEX_Error (RC_OnInitDlgCConect, WC_NOMERKMAL);	// keine Merkmale gefunden
		return FALSE;
	}	
------------------------------------*/
// KK000411

	
//	DataSource-Dialoge erzeugen
CString strCaption;

	VERIFY (strCaption.LoadString (IDS_USER_DSN_CAPT));
	m_dlgUserDsn.m_tType = UserDataSource;

	VERIFY (0 == m_tbDsn.AddDialog (&m_dlgUserDsn, IDD_USER_DSN, strCaption));
	VERIFY (strCaption.LoadString (IDS_SYSTEM_DSN_CAPT));
	m_dlgSystemDsn.m_tType = SystemDataSource;

	VERIFY (1 == m_tbDsn.AddDialog (&m_dlgSystemDsn, IDD_USER_DSN, strCaption));
	VERIFY (strCaption.LoadString (IDS_FILE_DSN_CAPT));
	m_dlgFileDsn.m_tType = FileDataSource;
	VERIFY (2 == m_tbDsn.AddDialog (&m_dlgFileDsn, IDD_FILE_DSN, strCaption));
	
//	Standard ist Ankopplung über Merkmal	                                  
	m_btMermkalsKodes.SetCheck (1);	                                  
	
//	wenn Objekt-Nummer übergeben wurde, die zugeh. Objektklassen-Anbindung lesen	
ulong lIdent = 0;

	if ((m_lObjNr > 0) &&                             			// gültige Objektnummer
		((lIdent = (ulong) DEX_GetObjIdent (m_lObjNr)) > 0)) 	// gültige Objektklasse
	{
	//	Info zusammen bauen		
	PBDDATA pbdData;            
	char KText [KurzTextLen] = "";

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = KText;
		pbdData.pbdKTextLen = sizeof(KText) - 1;

	//	wenn Info vorhanden		
		if (DEX_GetPBDData (pbdData) == EC_OKAY) {	
		char outBuff [sizeof(KText)+20] = "";
		
			if (SUCCEEDED(ClassFromIdentX (lIdent, outBuff, sizeof (outBuff))) && (*outBuff)) {
				strcat (outBuff, ":");
				if (*pbdData.pbdKText)
					strcat(outBuff, pbdData.pbdKText);

			// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
			// in Klammern hintendran hängen
				if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
				HPROJECT hPr = DEX_GetObjectsProject(lIdent);

					ASSERT(NULL != hPr);
					if (NULL != DEX_GetDataSourceShortName (hPr, KText)) {
						strcat (outBuff, " (");
						strcat (outBuff, KText);
						strcat (outBuff, ")");
					}
				}

				if (m_cbObjKlassen.SelectString (-1, outBuff) >= 0)	// diesen ID selektieren				
					ReadActConnections ();		// Anbindung lesen
			}
		}
	}

//	setze ggf. aktuelle Diaolgseite
	if (m_tbDsn.GetActiveIndex () < 0)
		m_tbDsn.SetActiveDialog (0);
	
	m_bResult = TRUE;		        
	return TRUE;	
}

// Infos der gew. Obj-Klasse lesen und ausgeben
BOOL CConnect::ReadActConnections (const char *pObjKlasse, ulong nObjIdent)
{                
	CallMessageQueue();

CWaitCursor wc;
	
//	alten Infos ggf. speichern 
	if (!QueryStore ())
		return FALSE;
	
	TRY {   
	//	Objekt-Klasse lesen
//		ulong ulObjKlasse = 0;

		if (NULL != pObjKlasse) {
			m_strActObjKlasse = pObjKlasse;
			m_nActObjIdent = nObjIdent;
		} 
		else {
		int iSel = m_cbObjKlassen.GetCurSel();
		
			if (iSel < 0)
				return FALSE;

			m_cbObjKlassen.GetLBText (iSel, m_strActObjKlasse);
			m_nActObjIdent = m_cbObjKlassen.GetItemData (iSel);
			ASSERT(!InvalidIdent(m_nActObjIdent));

		// KK000411
			if (0 == m_nActObjIdent)
				return FALSE;

		// Hier erst sollten die OE auftauchen !!!
		//	Objektklassen ausgeben
			m_cbMerkmalsKodes.ResetContent();

		ObjMerkmalInfo oi;

			oi.m_lIdent = m_nActObjIdent;
			oi.m_lType = 'm';
			oi.m_pCComboBox = &m_cbMerkmalsKodes;

		ENUMLONGKEYEX ELK;
		ErrInstall EI (WC_NOMERKMAL);

			ELK.eFcn = (ENUMLONGKEYEXPROC)FillObjFeatureList;
			ELK.ePtr =  (void*) &oi;
			ELK.eKey = m_nActObjIdent;
			ELK.eData = DWORD('a');

//			ELK.eData = DWORD('a')|PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY;

			if (!DEX_EnumObjektMerkmaleClassEx(ELK)) {
				EndDialog (IDCANCEL);
				DEX_Error (RC_OnInitDlgCConect, EC_ILLPARS);	// keine Merkmale gefunden
			}
		}

		if (m_strActObjKlasse.GetLength () == 0)
			return FALSE;
		         
	//	zuerst alles rücksetzen
		m_edAliasName.SetWindowText ("");		// AliasName	
		m_edWhereKlausel.SetWindowText ("");	// Klausel

		MERKMALE_SETEMPTY();
		m_cbTables.ResetContent ();				// Tabellen
		DELETE_OBJ (m_OdbcInfos.m_pTables);		         
		m_cbKoppelFields.ResetContent ();		// zugeh. Felder
		DELETE_OBJ (m_OdbcInfos.m_pColumns);
		m_btStandard.SetCheck (0); 				// keine Standard-Anbindng
		
	//	Information über Aktion ins Beschreibungsfeld ausgeben
	CString strInfo;
	
		strInfo.LoadString (IDS_READOBJCLASS);
		strInfo += m_strActObjKlasse;
		m_stDescription.SetWindowText (strInfo);

	StringDup strDSN;
	
		m_strDsn.Empty();
		m_tDsn = NoDataSource;
		
	//	vorhandenen Ankopplungs-Parameter lesen		
	long *pMKs = NULL;
	char **ppMStrs = NULL;
	short sCnt = 0;			// Anzahl der zum Eintrag gelesenen Werte

		if (!InvalidIdent(m_nActObjIdent)/*0 != ulObjKlasse*/) {
		HPROJECT hPr = DEX_GetObjectsProject(m_nActObjIdent);
		Profile ProFile(hPr);		// Name der Ini-Datei lesen

			sCnt = ProFile.ReadOdbcCodes (&pMKs, &ppMStrs, m_nActObjIdent);

		// 	AliasName vorhanden ?
			if ((sCnt > 0) &&			
				(pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0])) // und gültiger Wert
			{			
				m_edAliasName.SetWindowText (ppMStrs [0]);			
			
			//	ODBC-Infos lesen			                                   
				strDSN.Replace (ProFile.GetDataSourceName (ppMStrs [0], m_tDsn), FALSE);
				if (strDSN.Ptr() && DSNParamOk(strDSN, m_tDsn) && m_OdbcInfos.CreateDataBase(strDSN, m_tDsn))
				{                                                
				//	alle zum Data-Source-Objekt geh. Tabellen ausgeben
					BOOL bOk = m_OdbcInfos.OutputTableNames (&m_cbTables);
				
				// 	aktuelle Tabelle lesen						                        
					StringDup strTableName (ProFile.GetTableName (ppMStrs [0]), FALSE);
					if (bOk)
						bOk = strTableName ? TRUE : FALSE;
					
				//	Tabelle selektieren
					if (bOk && (m_cbTables.SelectString (-1, strTableName.Ptr ()) >= 0))  
				//	zur Tabelle alle möglichen Namen der Koppelfelder ausgeben						
						m_OdbcInfos.OutputColumnNames (strTableName, m_cbKoppelFields);

				//	DSN speichern
					if (bOk)
						m_strDsn = strDSN.Ptr ();
				}				
			}		        
			
		//	wenn kein Data-Source gewählt
		DataSourceType tType = NoDataSource;
		StringDup strStandardDSN (ProFile.GetDataSourceName ("", tType), FALSE);
		
			if (m_strDsn.IsEmpty ()) {
			//	Versuche Standard zu setzen
				if (NULL !=strStandardDSN.Ptr () && DSNParamOk (strDSN, tType) && 
					m_OdbcInfos.CreateDataBase (strStandardDSN.Ptr (), tType))
				{
					m_OdbcInfos.OutputTableNames (&m_cbTables); // Tabellen ausgeben	

				//	DataSource und Typ merken
					m_strDsn = strStandardDSN.Ptr ();
					m_tDsn = tType;
				}				
			}

		//	ist der selektierte DSN gleich dem Standard ?
			if (strDSN == strStandardDSN)
				m_btStandard.SetCheck (1);						
		}		// akt. Anbindung	!InvalidIdent
	//	akt. DataSourceDialog-Seite selektieren 
		if (!m_strDsn.IsEmpty ())
		{
			switch (m_tDsn)
			{
				case UserDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgUserDsn));
					VERIFY (m_dlgUserDsn.SelectDataSource (strDSN));
				}
				break;
				case FileDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgFileDsn));
					VERIFY (m_dlgFileDsn.SelectDataSource (strDSN));
				}
				break;
				case SystemDataSource:
				{
					VERIFY (m_tbDsn.SetActiveDialog (&m_dlgSystemDsn));
					VERIFY (m_dlgSystemDsn.SelectDataSource (strDSN));
				}
				break;
				default:
					ASSERT (FALSE);
			}								
		}
		else
		{
			m_tbDsn.SetActiveDialog (&m_dlgUserDsn);
			m_dlgUserDsn.SelectDataSource ("");
		}
		
	//	Where-Klausel vorhanden ?
		if ((sCnt > 1) && 			
			(pMKs [1] == -2) && (ppMStrs [1] != NULL) && (*ppMStrs [1])) // gültige SQL-Klausel
		{			                     
		//	doppelte durch einfache Anführungs-Zeichen ersetzen
			for (register char *pKlausel = ppMStrs [1]; *pKlausel; pKlausel++)
				if (*pKlausel == '\"')
					*pKlausel = '\'';
			
			m_edWhereKlausel.SetWindowText (ppMStrs [1]);
		}			
					
	//	Feldname vorhanden ?			                    
		if ((sCnt >= 1) && 			// mehr als 1 Attribut bei Anbindung
			(pMKs [1] == -1) && (ppMStrs [1]) && (*ppMStrs [1]))  			// gültiger Wert
			 m_cbKoppelFields.SelectString (-1, ppMStrs [1]); 		// selektiere Feld
			
	//	MerkmalsWert für Ankopplung gegeben ?
		if ((sCnt > 2) && (pMKs [2] > 0))
		{
		MAPMCODETOHANDLE mmh;
		HPROJECT hPr = DEX_GetObjectsProject(m_nActObjIdent);
		HFEATURE lMCode = INVALID_HFEATURE;

			INITSTRUCT(mmh, MAPMCODETOHANDLE);
			mmh.lIdent = m_nActObjIdent;
			mmh.lMCode = pMKs[2];
			mmh.fCreate = FALSE;
			mmh.plHandle = &lMCode;
			if (!DEX_MapOrCreateMCodeToHandle(hPr, mmh))
				lMCode = pMKs[2];
		
		char MBuffer [KurzTextLen + 20] = "";
		PBDMERKMALEX pbdData;            
		char KText [KurzTextLen];

			INITSTRUCT(pbdData, PBDMERKMALEX);
			KText[0] = '\0';
			pbdData.pbdTyp = 'm';
			pbdData.pbdCode = lMCode;
			pbdData.pbdKText = KText;
			pbdData.pbdKTextLen = sizeof(KText) - 1;
			pbdData.lIdent = m_nActObjIdent;
			DEX_GetPBDData(pbdData);

			MERKMALE_SETTEXT(pbdData.pbdKText);
		}			
			
	//	Information ins Beschreibungsfeld ausgeben         
		AfxFormatString1 (strInfo, IDS_SELECTOBJCLASS, m_strActObjKlasse);
		m_stDescription.SetWindowText (strInfo);
		
	//	MKodes und MStr-Speicher freigeben
		for (short i = 0; i < sCnt; i++)
				DELETE_VEC (ppMStrs [i]);
		DELETE_VEC (ppMStrs);
		DELETE_VEC (pMKs);		
	}
	CATCH (CMemoryException, me)
	{         
		DEX_Error (RC_ReadActConCConnect, EC_NOMEMORY);
		return FALSE;
	}                           
	END_CATCH        
	
//	Control-Status aktualisieren	   
	m_bInfosStored = TRUE;		// speichern jetzt nicht notwendig
	SetControlState ();
	
	return TRUE;                 
}	

//	Control-Status aktualisieren	   
void CConnect::SetControlState (void)
{               
//	Anbindung über Merkmal oder Where-Klausel ?
	if ((m_edWhereKlausel.GetWindowTextLength () > 0) ||	// Name vorhanden oder
		(!MERKMALE_TEST_AVAILABLE()))
//		(m_cbMerkmalsKodes.GetCount () == 0))				// keine Merkmale
	{		
		m_btWhereKlausel.SetCheck (1);	            		// Anbindung über Where-Klausel
		m_btMermkalsKodes.SetCheck (0);						// Merkmale deaktivieren
		m_cbMerkmalsKodes.EnableWindow (FALSE);		        // zugeh. Listbox	
		m_edWhereKlausel.EnableWindow (TRUE);				// Edit-Feld aktivieren
		m_cbKoppelFields.EnableWindow (FALSE);				// Koppelfeld nicht notwendig
		m_btRelations.EnableWindow (FALSE);			        // Relation nicht möglich
		SetCreateWhereKlausel ();							// Where-Klausel erzeugen
	}		
	else
	{                                           			// Merkmalskodes
		m_btMermkalsKodes.SetCheck (1);						// zugeh. Button aktivieren	
		m_cbMerkmalsKodes.EnableWindow (TRUE);				// zugeh. ComboBox
		m_btWhereKlausel.SetCheck (0);	            		// nicht über Where-Klausel
		m_edWhereKlausel.EnableWindow (FALSE);				// Edit-Feld eb. nicht notw.
		m_btCreateWhereKlausel.EnableWindow (FALSE);		// Where-Klausel nicht erzeugen
		
	//	ggf. Koppelfeld aktivieren
		SetKoppelFields ();									// KoppelFeld setzen
		
	//	ggf. Relation-Button aktvieren
		SetCreateRelations ();
	}		

//	Als Standard benutzen
	m_btStandard.EnableWindow (!m_strDsn.IsEmpty ());
	
//	Store-Button
	SetStoreButton ();										// Store-Button setzen
	
//	Table-Box
	SetTables ();
}		                                                                
                 
// Table-Box                 
void CConnect::SetTables (void)
{
	if ((!m_strDsn.IsEmpty ()) &&  				// Treiber OK
		  m_cbTables.GetCount () > 0)			// Tabellen vorhanden
		m_cbTables.EnableWindow (TRUE);
	else
		m_cbTables.EnableWindow (FALSE);
}								 			                             

//	Koppelfeld-ComboBox aktivieren/deaktivieren    
void CConnect::SetKoppelFields (void)
{                
	if ((m_btMermkalsKodes.GetCheck () == 1) &&			// wenn Merkmalsanbindung gewählt
	   (!m_strDsn.IsEmpty ()) &&							// Treiber OK
		(m_cbTables.GetCurSel () >= 0) &&				// Tabelle OK
		(m_cbKoppelFields.GetCount () > 0))				// Felder vorhanden
		m_cbKoppelFields.EnableWindow (TRUE);
	else
		m_cbKoppelFields.EnableWindow (FALSE);								
}			
                 
// erzeuge Where-Klausel-Button prüfen
void CConnect::SetCreateWhereKlausel (void)
{
	if ((!m_strDsn.IsEmpty ()) &&				// Treiber OK
		(m_cbTables.GetCurSel () >= 0))	        // Tabelle OK
		m_btCreateWhereKlausel.EnableWindow (TRUE);
	else
		m_btCreateWhereKlausel.EnableWindow (FALSE);					
}	
                 
// Store-Button setzen/rücksetzen                                    
void CConnect::SetStoreButton (void)
{       
	if ((m_bInfosStored == FALSE) &&						// wenn akt. Info noch nicht gespeichert
		(m_cbObjKlassen.GetCurSel () >= 0)	&&				// Objekt-Klasse ok
		(m_edAliasName.GetWindowTextLength () > 0) &&		// gültiger AliasName
		(m_cbTables.GetCurSel () >= 0) &&					// Tabelle ok		
		(!m_strDsn.IsEmpty ()))								// Data-Source ok
		
	{         
		if ((m_btMermkalsKodes.GetCheck () == 1) &&			// wenn Merkmalsanbindung gewählt
			MERKMALE_TEST_PRESENT() &&
//			(m_cbMerkmalsKodes.GetCurSel () >= 0) &&       	// Merkmalskode ok
			(m_cbKoppelFields.GetCurSel () >= 0))			// Koppelfeld ok
		{
		// bei Anbindung über Merkmal 
			m_btStoreConnection.EnableWindow (TRUE);
		} 
		else { 
		// Anbindung über Where-Klausel		
			if ((m_btWhereKlausel.GetCheck () == 1) && (m_edWhereKlausel.GetWindowTextLength () > 0))	// gültige Klausel
				m_btStoreConnection.EnableWindow (TRUE);          
			else
				m_btStoreConnection.EnableWindow (FALSE);	             			   
		}					
	} else
		m_btStoreConnection.EnableWindow (FALSE);
}		

// Relationen-Erzeugen-Button 		                                                                      
void CConnect::SetCreateRelations (void)	                  
{
	if ((m_cbObjKlassen.GetCurSel () >= 0)	&&				// Objekt-Klasse ok
		(m_edAliasName.GetWindowTextLength () > 0) &&		// gültiger AliasName
		(m_cbTables.GetCurSel () >= 0) &&					// Tabelle ok		
		(!m_strDsn.IsEmpty ()) &&							// Data-Source ok
		(m_btMermkalsKodes.GetCheck () == 1) &&		    	// Auswahl über MerkmalsKode
		MERKMALE_TEST_PRESENT()	&&
//		(m_cbMerkmalsKodes.GetCurSel () >= 0) &&       		// Merkmalskode ok
		(m_cbKoppelFields.GetCurSel () >= 0))				// Koppelfeld ok
	{
		m_btRelations.EnableWindow (TRUE);			 
	}
	else {
		m_btRelations.EnableWindow (FALSE);								
	}
}       
 
//	alle über ODBC gelesenen Infos löschen 
void CConnect::ResetODBCInfos (void)
{                              
	m_strDsn.Empty ();
	m_tDsn = NoDataSource;

//	alten Infos löschen
	m_OdbcInfos.DeleteAll ();
	
//	Tabellen-Namen löschen		
	m_cbTables.ResetContent ();
	m_cbTables.EnableWindow (FALSE);
		
//	Koppelfelder löschen		
	m_cbKoppelFields.ResetContent ();
	m_cbKoppelFields.EnableWindow (FALSE);				
		                                      
//	weitere Button rücksetzen
	m_btStoreConnection.EnableWindow (FALSE);	// speichern nicht möglich	                                      
	m_btRelations.EnableWindow (FALSE);			// Relationen ebenfalls unmöglich

//	Beschreibungsfeld löschen
	m_stDescription.SetWindowText (""); 	
	
//	Standard-Data-Source kann nicht gespeichert werden	
	m_btStandard.EnableWindow (FALSE);			
	
//	AliasNamen löschen
	m_edAliasName.SetWindowText ("");	
}   
 
//	aktuellen Anbindungen speichern 
BOOL CConnect::StoreActConnection (void)
{   
//	prüfe interne Parameter
	if (m_strActObjKlasse.IsEmpty ())
		return FALSE;	
    
	ErrCode EC = EC_OKAY;			// Operation-Flag
	
	TRY {
		CString strAliasName;
		m_edAliasName.GetWindowText (strAliasName);		

// JG 990309
	ulong ulIdent = m_nActObjIdent;
	HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
	Profile ProFile(hPr);

	//	Anbindungs-Art lesen                                        
		if (EC_OKAY == EC) {
			if (m_btMermkalsKodes.GetCheck () == 1)	{
			CString strFeldName, strMerkmal;
//			INT_PTR lMCode = MERKMALE_GETITEMDATA();
//
//				_ASSERTE(0 != lMCode);
				MERKMALE_GETTEXT(strMerkmal);

				m_cbKoppelFields.GetLBText (m_cbKoppelFields.GetCurSel(), strFeldName);
				if (! ProFile.WriteOdbcEntry (ulIdent, strAliasName, strFeldName, strMerkmal))
					EC = EC_NOWRITE;

			//	dBASE-AliasSection ausgeben			 
				if (EC == EC_OKAY && ProFile.WritedBaseAliasName (strAliasName)) 
					if (!ProFile.WriteDBaseEntry (ulIdent, strAliasName, strFeldName, strMerkmal))
						EC = EC_NOWRITE;

				if (1 == m_btStandard.GetCheck()) {
				// als Standardeinstellung mit wegschreiben
					if (!ProFile.WriteOdbcEntry (0L, strAliasName, strFeldName, strMerkmal))
						EC = EC_NOWRITE;

				}
			}			
			else {                     
			CString strKlausel;
			
				m_edWhereKlausel.GetWindowText (strKlausel);	// WHERE-Klausel
				if (!ProFile.WriteOdbcKlausel (ulIdent, strAliasName, strKlausel))
					EC = EC_NOWRITE;									
			}			
		}
			
	//	Tabellen-Name ausgeben            
		if (EC == EC_OKAY) {
		CString strTableName;
		
			m_cbTables.GetLBText (m_cbTables.GetCurSel (), strTableName);
			if (! ProFile.WriteTableName (strAliasName, strTableName))
				EC = EC_NOWRITE;			
		}					
	
	//	Data-Source-Name ausgeben
		if (EC == EC_OKAY) {
			ASSERT (!m_strDsn.IsEmpty ());
			if (!ProFile.WriteDataSourceName (strAliasName, m_strDsn, m_tDsn))
				EC = EC_NOWRITE;			
		}       
		
	//	Standard-DSN ausgeben
		if ((EC == EC_OKAY) && (m_btStandard.GetCheck () == 1)) {
			ASSERT (!m_strDsn.IsEmpty ());
			if (!ProFile.WriteStandardDataSourceName (m_strDsn, m_tDsn))
				EC = EC_NOWRITE;									
		}					

	// TRiAS von der veränderten Attributlage informieren
		if (EC_OKAY == EC)
			DEXN_FeatureSetModified(ulIdent);
	}
	CATCH (CMemoryException, me)
	{        
		DEX_Error (RC_StoreActConnCConnect, EC_NOMEMORY);
		return FALSE;
	}		
	END_CATCH
	
//	ggf. Fehlermeldung ausgeben
	if (EC != EC_OKAY) {   
		DEX_Error (RC_StoreActConnCConnect, EC);
		return FALSE;
	}		 	
	else {
		m_btLastEntry.EnableWindow (TRUE);			// diese Anbindung kann
													// wieder verwendet werden
		m_bInfosStored = TRUE;						// Info gespeichert
		m_btStoreConnection.EnableWindow (FALSE);   // nicht erneut speichern

		return TRUE;
	}		
}
                 
//	speichern über vorige Abfrage                 
BOOL CConnect::QueryStore (void)
{
//	muß akt. Anbindung noch gespeichert werden
	if ((m_bInfosStored == FALSE) &&
		 m_btStoreConnection.IsWindowEnabled () &&
		 ! m_strActObjKlasse.IsEmpty ())
	{           
		TRY
		{                 
		//	Caption laden                                          
			CString strCaption;
			strCaption.LoadString (IDS_CONNECTCAPTION);                     
		
		//	Format lasen
			CString strFormat;
			strFormat.LoadString (IDS_STORE_CONNECTQ);		
		
		//	Puffer anfordern	
			CString strBuffer;
			char *pBuffer = strBuffer.GetBuffer (m_strActObjKlasse.GetLength () +	
											 	 strFormat.GetLength ());
											 
		//	Textstring zusammenbauen												 
			wsprintf (pBuffer, strFormat, m_strActObjKlasse);
		
		//	Abfrage ausgeben		
			if (MessageBox (pBuffer, strCaption, MB_ICONQUESTION | MB_YESNO) == IDYES)
				return StoreActConnection ();	// speichern der Anbindungen
		}		
		CATCH (CMemoryException, me)			
		{                
			DEX_Error (RC_QueryStoreCConnect, EC_NOMEMORY);
			return FALSE;
		}
		END_CATCH
	}		        
	
	return TRUE;
}	

//	Event-Handler -------------------------------------------------------------------------    
//	neue Objektklasse gewählt
afx_msg void CConnect::OnSelChangeObjKlasse (void)
{   
	TRY
	{
		m_strOldObjKlasse = m_strActObjKlasse;
		m_nOldObjIdent = m_nActObjIdent;	// JG 990309
	}
	CATCH (CMemoryException, me)
	{
		m_strOldObjKlasse = m_strActObjKlasse;		
		m_nOldObjIdent = m_nActObjIdent;	// JG 990309
		return;
	}
	END_CATCH

	ReadActConnections ();		// deren Infos in Dialog übernehmen
}

//	Anbindung über Merkmal gewünscht
afx_msg void CConnect::WantMerkmalsKodes (void)
{      
	m_bInfosStored = FALSE;								// speichern wieder möglich                                       
	m_btWhereKlausel.SetCheck (0);               		// keine Where-Klausel
	m_cbMerkmalsKodes.EnableWindow (TRUE);				// Merkmale
	m_edWhereKlausel.EnableWindow (FALSE);				// und Liste aktivieren
	m_btCreateWhereKlausel.EnableWindow (FALSE);		// Where-Klausel nicht erzeugen
	
//	Koppelfeld aktvieren	
	if (m_cbKoppelFields.GetCount () > 0)
		m_cbKoppelFields.EnableWindow (TRUE);
	
//	ggf. Relation aktivieren	
	SetCreateRelations ();
}
                                      
//	Where-Klausel-Eingabe gewünscht                                      
afx_msg void CConnect::WantWhereKlausel (void)
{                       
//	wenn Editfeld für Where-Klausel leer oder Control-Taste gedrückt und Merkmal 
// 	und Feld gewählt, dann bilde eine mögliche Klausel                         
	m_bInfosStored = FALSE;										// speichern wieder möglich           
	if (((m_edWhereKlausel.GetWindowTextLength () == 0) ||   	// entweder keine Klausel vorh.
		(:: GetKeyState (VK_CONTROL) < 0)) &&     				// oder Control-Taste gedrückt
		MERKMALE_TEST_PRESENT()	&&
//		(m_cbMerkmalsKodes.GetCurSel () >= 0) &&
		(m_cbKoppelFields.GetCurSel () >= 0))
	{
		TRY {        
		CString strField, strFieldOnly;
		
			m_cbKoppelFields.GetLBText (m_cbKoppelFields.GetCurSel(), strFieldOnly);
			AfxFormatString1 (strField, IDS_FIELDNAME_FORMAT, strFieldOnly);
		
		CString strMerkmal;
		CString strFormat;                             
		
			MERKMALE_GETTEXT(strMerkmal);

		//	Feldtyp bestimmen
			switch (m_OdbcInfos.m_pColumns -> GetSqlType (this, strFieldOnly)) {
			case Text:
				strFormat.LoadString (IDS_DEFWHEREKLAUSELTEXT);		// = '{%s}'
				break;

			case Date:
				strFormat.LoadString (IDS_DEFWHEREKLAUSELDATE);		// = #{%s}#
				break;

			case Other:
			default:						           
				strFormat.LoadString (IDS_DEFWHEREKLAUSEL);			// = {%s}
				break;
			}

		CString strWhere;

			strWhere.Format(strFormat, (LPCSTR)strMerkmal);
			strField += strWhere;
			m_edWhereKlausel.SetWindowText (strField);
		}
		CATCH (CMemoryException, cme)
		{
			DEX_Error (RC_WantWhereKlauselCConnect, EC_NOMEMORY);
			return;
		}
		END_CATCH		
	}		 

	m_btMermkalsKodes.SetCheck (0);                  	// kein Merkmalskode für Anbindung                    
	m_cbMerkmalsKodes.EnableWindow (FALSE);				// Liste deaktivieren
	m_edWhereKlausel.EnableWindow (TRUE);				// Edit-Fenster für Eingabe aktivieren
	m_cbKoppelFields.EnableWindow (FALSE);				// Feldname nicht notwendig
	m_btRelations.EnableWindow (FALSE);			 		// mit 2 Parametern keine Relation möglich
	SetCreateWhereKlausel();							// Where-Klausel-Erzeugen-Button setzen
}

//	ein neues Merkmal wurde selektiert                           
afx_msg void CConnect::OnSelChangeMerkmal (void)
{      
//	int iSel = m_cbMerkmalsKodes.GetCurSel ();	// JG MERKMALSMAKROS
//	if (iSel < 0)								// JG MERKMALSMAKROS
//		return;									// JG MERKMALSMAKROS
	if (!MERKMALE_TEST_PRESENT())
		return;

	m_bInfosStored = FALSE;						// speichern wieder möglich                   
	SetStoreButton ();							// hier nur Store-Button akt.
	SetCreateRelations ();						// Relation aktivieren	

//	Beschreibung ausgeben	
CString strInfo;

	MERKMALE_GETTEXT(strInfo);
	
//	Merkmalskode lesen	
	if (!strInfo.IsEmpty ())       
		m_stDescription.OutputDescription (MERKMALE_GETITEMDATA(), 'm', IDS_SELMERKMAL);    // Info ausgeben
}	                            

//	WhereKlausel wurde modifiziert
afx_msg void CConnect::OnChangeWhereKlausel (void)
{                                               
	m_bInfosStored = FALSE;		// speichern wieder möglich           
	SetStoreButton ();         	// Store-Button setzen
	SetCreateWhereKlausel ();	// Create-Button setzen	
}	

//	Alias-Name geändert    
afx_msg void CConnect::OnChangeAliasName (void)
{                  
	m_bInfosStored = FALSE;		// speichern wieder möglich           
	SetStoreButton ();			// Store-Button
	SetCreateRelations ();		// Relationen-Erzeugen-Button 		                          
}	

//	neue Tabelle ausgewählt 
afx_msg void CConnect::OnSelChangeTable (void)
{                               
	if (m_cbTables.GetCurSel ()	< 0)
		return;

	m_bInfosStored = FALSE;		// speichern wieder möglich           
	CString strTableName;
	m_cbTables.GetLBText (m_cbTables.GetCurSel (), strTableName);
	if (strTableName.GetLength () &&												// Name OK
		m_OdbcInfos.OutputColumnNames (strTableName, m_cbKoppelFields) &&     // Felder ausgegeben
		m_OdbcInfos.OutputTableInfo (strTableName, m_stDescription))			// Tabellen-Kommentar
	{
		// SetKoppelFields ();		
		m_btStoreConnection.EnableWindow (FALSE);                // nicht mehr möglich
		m_btRelations.EnableWindow (FALSE);    					 // keine Relationen mehr möglich 
	
	//	ggf. AliasNamen setzen
	//	if (m_edAliasName.GetWindowTextLength () == 0)
		m_edAliasName.SetWindowText (strTableName);				 // immer neu setzen 
			
	//	ggf. Koppelfelder aktivieren                 
		if 	(m_btMermkalsKodes.GetCheck () == 1)
			m_cbKoppelFields.EnableWindow ();			
	}					
}	
	
//	Feld-Info ausgeben	                            
afx_msg void CConnect::OnSelChangeKoppelField (void)
{   
	if (m_cbKoppelFields.GetCurSel () < 0)
		return;

	m_bInfosStored = FALSE;		// speichern wieder möglich     
	CString strSel;                                                 
	m_cbKoppelFields.GetLBText (m_cbKoppelFields.GetCurSel (), strSel);                                 
	m_OdbcInfos.OutputColumnInfo (strSel, m_stDescription);                                          

	SetStoreButton ();			// Store-Button
	SetCreateRelations ();		// Relationen-Erzeugen-Button
}	

//	BeschreibungsText für Klausel ausgeben         
afx_msg void CConnect::OuputKlauselDescription (void)
{
	m_stDescription.Output (IDS_KLAUSEL_DESCR);
}
                                     
//	BeschreibungsText für AliasName ausgeben                                     
afx_msg void CConnect::OutputAliasDescription (void)
{
	m_stDescription.Output (IDS_ALIAS_DESCR);
}         

//	aktuelle Anbindung speichern
afx_msg void CConnect::StoreConnection (void)
{                                          
	StoreActConnection ();
}        
 
//	akt. DSN für alle Objekt-Klassen nehmen 
afx_msg void CConnect::StandardDataSource (void)
{   
	m_bInfosStored = FALSE;		// speichern wieder möglich                                      		                        
	SetStoreButton ();			// Store-Button akt.
	TRY
	{
		CString strInfo;
		strInfo.Format (1 == m_btStandard.GetCheck () ? IDS_ALL_OBJ_CLASSES : 
														IDS_ONLY_OBJ_CLASSES, 
						m_strDsn);
		m_stDescription.SetWindowText (strInfo);
	}
	CATCH (CMemoryException, me)
	{        
		DEX_Error (RC_StandardDSNCConnect, EC_NOMEMORY);
	}
	END_CATCH		
}

//	erzeuge mögliche Relationen zu anderen Tabellen                                    
//	hierbei wird davon ausgegangen, das die Anbindung bereits gespeichert wurde ???
afx_msg void CConnect::CreateRelations (void)
{              
//	Datenaustausch über INI-Datei
	if (QueryStore () == FALSE)
		return;

	CString strMaster, strKoppelField;
	int iSel = m_cbKoppelFields.GetCurSel ();
	if (iSel < 0)
		return;

	m_edAliasName.GetWindowText (strMaster);
	if (strMaster.IsEmpty ())
		return;

	m_cbKoppelFields.GetLBText (iSel, strKoppelField);

//  JG außerdem das Projekt der aktuellen Objektklasse mitgeben
	int iIndex = m_cbObjKlassen.GetCurSel();
	if (-1 == iIndex)
		return;

	m_nActObjIdent = m_cbObjKlassen.GetItemData (iIndex);
	HPROJECT hPr = DEX_GetObjectsProject(m_nActObjIdent);

	CRelDialog dlg (this, strMaster, strKoppelField, hPr);         
	if (dlg.Result () == EC_OKAY)
		dlg.DoModal ();
}	
	                             
//	Dialog beenden	                             
afx_msg void CConnect::Beenden (void)     
{
	QueryStore ();          // speichern über Abfrage
	EndDialog (IDOK);		// Dialog beenden
}
                     
//	WHERE-Klausel erzeugen	     
afx_msg void CConnect::CreateWhereKlausel (void)
{
//	aktuelle Klausel lesen	
	CString strKlausel;
	m_edWhereKlausel.GetWindowText (strKlausel);
	
//	Tabellen-Namen lesen	
	CString strTableName;
	m_cbTables.GetLBText (m_cbTables.GetCurSel (), strTableName);
	
//	Dialog erzeugen und aufrufen
	CCreateWhereKlDlg dlg (this, m_OdbcInfos.m_pDataBase,	    
						   strKlausel, m_nActObjIdent, strTableName);
	if ((dlg.Result () == EC_OKAY) &&	// Konstruktion OK
		(dlg.DoModal () == IDOK) &&		// Dialog anzeigen
 	    (dlg.Result () == EC_OKAY) &&	// wenn Dialog OK gelaufen
		(! strKlausel.IsEmpty ())) 		// gültige Klausel							   
	{
		m_edWhereKlausel.SetWindowText (strKlausel);		
		m_bInfosStored = FALSE;		// speichern wieder möglich
	}		
}
		 
void CConnect::OnLastentry() 
{
	if (m_strOldObjKlasse.IsEmpty () || m_strOldObjKlasse == m_strActObjKlasse)
		return;

	m_bInfosStored = TRUE;					// kein voriges speichern
	ReadActConnections (m_strOldObjKlasse, m_nOldObjIdent);

//	akt. Objektklasse neu lesen
int iIndex = m_cbObjKlassen.GetCurSel();

	if (-1 != iIndex)
	{
		m_cbObjKlassen.GetLBText (iIndex, m_strActObjKlasse);
		// JG 990309
		m_nActObjIdent = m_cbObjKlassen.GetItemData (iIndex);
	}
	m_bInfosStored = FALSE;					// speichern jetzt notwendig
	SetStoreButton ();						// Button akt.
}

BOOL CConnect::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IDM_CONFIG_DSN == wParam || IDM_SELECT_DSN == wParam) {
	//	lese und prüfe Parameter
	DataSourceInfo *pInfo = (DataSourceInfo *)lParam;
	
		ASSERT (NULL != pInfo);
		ASSERT (NULL != pInfo -> pName && AfxIsValidString (pInfo -> pName));
		ASSERT ((UserDataSource == pInfo->tType) || (SystemDataSource == pInfo-> tType) ||
				 (FileDataSource == pInfo->tType));

		m_bInfosStored = FALSE;		// speichern wieder möglich                                      		
		ResetODBCInfos ();        	// alten ODBC-Infos löschen

		if ((strlen (pInfo->pName) > 0) &&									// Name ok
			m_OdbcInfos.CreateDataBase (pInfo->pName, pInfo -> tType) &&	// neues Data-Source-Objekt erzeugen   
			m_OdbcInfos.OutputDataBaseInfo (m_stDescription) &&		// Kommentar zum DSN ausgeben
			m_OdbcInfos.OutputTableNames (&m_cbTables))				// mögliche Tabellen ausgeben
		{           
			m_cbTables.EnableWindow (TRUE);							// Tabellen-Selektion ermöglichen                              
			m_cbKoppelFields.ResetContent ();						// alten Feldnamen löschen
			m_cbKoppelFields.EnableWindow (FALSE);					// zuvor Tabelle auswählen
			m_btStandard.EnableWindow (TRUE);						// als Standard zu verwenden
			m_btRelations.EnableWindow (FALSE);						// keine Relationen mehr möglich

			m_strDsn = pInfo -> pName;
			m_tDsn = pInfo -> tType;
		}	

		SetStoreButton ();	// Store-Button setzen	
		return TRUE;
	}
	else
		return CDialog::OnCommand(wParam, lParam);
}


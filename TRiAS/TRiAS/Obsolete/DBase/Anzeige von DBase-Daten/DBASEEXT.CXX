// Erweiterung fuer die Anzeige von DBase-Informationen -------------------------
// File: DBASEEXT.CXX

#include "pheader.h"

extern "C" {
	#include <direct.h>
	#include <resstrg.h>
	#include "dbaseext.hr"   	// ResourceKonstanten
}

#include "dbaseext.htp"		 	// Klassen-Selektion
#include <commonvu.hxx>
#include <containr.hxx>

#include <ixtensn.hxx>			// ITriasXtension
#include <xtencunk.hxx>			// CTriasExtension			  
#include <xtsnprop.hxx>			// CObjectProperties
#include <xtsnaux.hxx>			// ExtOleRegisterClass () u.a.

#include <dbaserel.hxx>		 	// DBaseRel
#include <dbasprof.hxx>		 	// DBaseProfile
#include <dbtools.hxx>			// GetOemToAnsiiFlag ()

#include "dbase.hxx"
#include "dbaseext.hxx"		 	// Klasse für diese Erweiterung

//	GUID-Header
#include <xtsnguid.h>
#include <initguid.h>           
#include "dbasguid.h"
#include "version.h"

//  Konstanten
const short MinParCnt = 2;	  	// min. Anz. der Parameter in der INI-Datei
const int BeginExpr = '{';	  	// Separatoren in dBase-Expressions
const int EndExpr = '}';

// globale Variablen
DBaseExtension *pDBExt = NULL;

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)
{
	pDBExt = NULL;
	return new DBaseExtension ();
}


BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
    memcpy (&rClsID, &CLSID_DBaseExtension, sizeof (GUID));
	return TRUE;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
    char ExtName [] = "TRiAS.dBASEExtension.1";

	if (fRegister) 
	{// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
                                					  CLSID_DBaseExtension, 
                                					  TEXT(ExtName), IDS_LONGCLASSNAME,
                                					  DBASEEXT_MAJORVERSION, DBASEEXT_MINORVERSION, EFUnLoadable|EFVisible);
		if (!fSuccess) 
			return false;
	} 
	else 
	{// RegDB säubern
        return ExtOleUnregisterClass (CLSID_DBaseExtension, TEXT(ExtName));
	}

	return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
DBaseExtension :: DBaseExtension (void)
				: CTriasExtension ()
{
	_hWnd = 0;			  	// FensterHandle des aktiven ORFensters
	_lONr = -1;			 	// ObjektNummer
	_lIdent = -1;		   	// Identifikator
	_Type = FeldName;	   	// Parameter-Typ

	_pDBaseFile = NULL;	 	// aktuell zu verwendende DBaseDatei
	_pDBaseField = NULL;	// aktuelles DBaseSchlüssel für die Anbindung
	_pDBaseKey = NULL;	 	// aktueller Schlüssel
	m_pObjProp = NULL;		// ObjectEig.
	m_bOemToAnsi = True;	// DOS-Datei ist vorh.	

	_pDBaseDisp = new DBaseDispatchTree (); // Dispatcher der DBaseFenster 
	if (!_pDBaseDisp)
		return;
		
	pDBExt = this;
}

// Destruktor -----------------------------------------------------------------
DBaseExtension :: ~DBaseExtension (void) 
{
// 	Strings für die Anbindung der Dateien wieder freigeben
	DELETE_VEC (_pDBaseFile);		   
	DELETE_VEC (_pDBaseKey);
	DELETE_VEC (_pDBaseField);
		
// DBaseDispatcher wieder freigeben
	DELETE_OBJ (_pDBaseDisp);
	DELETE_OBJ (m_pObjProp);
}

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
HRESULT DBaseExtension :: QueryInterface (THIS_ REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IObjectProps)
		*ppvObj = m_pObjProp;	// ImportInterface liefern
	else
	// alles andere überlassen wir der BasisKlassse
		return CTriasExtension :: QueryInterface (riid, ppvObj);

// 	AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

	return NOERROR;
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
Bool DBaseExtension :: InitExtension (short iMode) 
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	m_pObjProp = CdBaseObjectProperties :: CreateInstance (m_pUnk ? m_pUnk : this);
	if (NULL == m_pObjProp) 
		return false;

//	anderen DLLs init.
	InitDBaseDLL (__hWndM, __DexCmd, __DexxCmd, __DexNotify);
//	InitDBTools (__hWndM, __DexCmd, __DexxCmd, __DexNotify);

// 	hier zusätzlichen MenuPunkt anhängen
	InstallMenuItem (IDM_SHOWDBASE, IDS_DBASEMENUITEM, TRUE, 0);

// 	Notifikationen anfordern
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);
	RegisterNotification (DEX_OBJECTUNSELECTED);
	RegisterNotification (DEX_OBJECTSELECTED);	  
#ifdef WIN32	      
	RegisterNotification (DEX_GOTOBJWNDFOCUS);
#else
	RegisterNotification (DEX_OBJWNDFOCUSCHANGED);
#endif
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);

	return TRUE;
}

Bool DBaseExtension :: UnLoadExtension (void)
{
//  Alle installierrten Funktionen hier wieder abmelden
	if (m_pObjProp)
		m_pObjProp -> RemoveAllPropertyFunctions ();

// 	MenuPunkt natürlich wieder ausbauen
	RemoveMenuItem (IDM_SHOWDBASE, TRUE, 0);

// 	Notifikationen wieder abmelden
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
#ifdef WIN32
	UnRegisterNotification (DEX_GOTOBJWNDFOCUS);
#else
	UnRegisterNotification (DEX_OBJWNDFOCUSCHANGED);
#endif
	UnRegisterNotification (DEX_OBJECTSELECTED);
	UnRegisterNotification (DEX_OBJECTUNSELECTED);
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);

	return CTriasExtension :: UnLoadExtension();
}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
Bool DBaseExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
	switch (MenuItemID) 
	{   
		case IDM_SHOWDBASE:
			if (hWnd != 0 && _pDBaseDisp)
			// 	Anzeige des zu diesem Objekt gehörenden DBaseSatzes
				return ShowDBaseInfo ();
		break;
	}
	return FALSE;
}

// Herausfinden, ob das aktive Objekt DBaseDaten hat, Menu --------------------
// entsprechend richten 
Bool DBaseExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd == 0) 
		return TRUE;			 // MenuInit aus HauptMenu

	_lONr = DEX_GetActiveObject (hWnd);	 // 1. ObjektNummer besorgen
	if (_lONr == -1L) 
	{
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		return TRUE;
	}

	short Status = DEX_GetObjectStatus (_lONr);

	if (Status != OSNormal && Status != OSModified) 
	{
	// 	Objekt existiert nicht
		_lONr = -1L;
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		return TRUE;
	}

	_lIdent = DEX_GetObjIdent (_lONr);	  // 2. Identifikator besorgen

// 	3. in INI-Datei des Projektes nach DBaseEinträgen (MCodes) suchen
	if (ReadDBaseCodes (_lONr, _lIdent) >= MinParCnt)
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	return TRUE;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
LRESULT DBaseExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) 
	{
		case DEX_CREATEOBJEKTINFO:
			_hWnd = (HWND)p;		// ORFensterHandle merken
		break;
		case DEX_OBJWNDCLOSED:
		{
			if (_pDBaseDisp == NULL) 
				break;
			_pDBaseDisp -> AllDelete ((HWND) p);	// DBaseFenster freigeben
		}
		break;
		case DEX_OBJECTSELECTED:							   
		{ 
			if (_pDBaseDisp == NULL) 
				break;
			long lLastObj = _pDBaseDisp -> ActObj (_hWnd);
			if (lLastObj != -1L && DEX_GetActiveObject (_hWnd) != lLastObj)
			// 	innerhalb eines ORFenster wurde Objekt gewechselt
				_pDBaseDisp -> AllDelete (_hWnd);	   // DBaseFenster freigeben
		}
		break;
		case DEX_OBJECTUNSELECTED:
			break;		  // andere wollen diese Meldungen auch noch haben
#ifdef WIN32
		case DEX_GOTOBJWNDFOCUS:		
#else
		case DEX_OBJWNDFOCUSCHANGED:
#endif
		{
		// wenn ein anderes ORFenster den Focus erhalten hat, Dispatcher
		// für dieses Fenster anlegen
#ifdef WIN32
			_hWnd = (HWND) p;			
#else
			if (LOWORD(p) && (_hWnd != (HWND) HIWORD(p))) 
				_hWnd = (HWND) HIWORD(p);	  // ORFensterHandle merken
#endif
		}
		break;
		case DEX_PROJECTOPEN:		   	// neues Projekt wurde eröffnet
		{					   			
		// DBaseFensterDispatcher initialisieren
			m_bOemToAnsi = GetOemToAnsiiFlag ();
			DELETE_OBJ (_pDBaseDisp);
			_pDBaseDisp = new DBaseDispatchTree ();
			_hWnd = NULL;
		}
		break;
		case DEX_PROJECTCLOSE:		  // project is to be closed
		{
			DELETE_OBJ (_pDBaseDisp);
			_hWnd = NULL;
		}
		break;
	}	//	end_switch

	return FALSE;   // alles andere ignorieren
}

// Testet, ob ein vorgegebener MerkmalsWert existiert -------------------------
Bool DBaseExtension :: ExistsMValue (long lONr, ulong lMCode)
{
	return GetMerkmalsValue (lONr, lMCode);
}
               
//	prüfe Wertebereich                                         
Bool DBaseExtension :: ValidMK (long MK)    
{                          
	return MK > 0 || MK < -3L ? True : False;
}	
               
// Liefert einen vorgegebenen MerkmalsWert ------------------------------------
Bool DBaseExtension :: GetMerkmalsValue (long lONr, ulong lMCode, 
								  char *pBuffer, short iLen)
{
	if (lMCode != 0) 
	{
		// MerkmalsWert holen
		TARGETMERKMAL tm;

		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = lONr;			  	// ObjektNummer
		tm.lMCode = lMCode;			 	// MerkmalsCode
		tm.imaxLen = iLen;
		tm.pMText = pBuffer;			// kein Buffer: nur Test
		tm.iTTyp = TT_Objekt;
		DEX_GetTextMerkmal (tm);

		return tm.imaxLen > 0;
	}

	return FALSE;
}

// Anzeigen der DBaseInfo für das aktive Objekt dieses ORFensters -------------
Bool DBaseExtension :: ShowDBaseInfo (void) {
//  prüfe Parameter
	switch (_Type) {
		case TagName:
		case FeldName:
			if (_pDBaseFile == NULL || _pDBaseField == NULL || _pDBaseKey == NULL)
				return FALSE;
		break;
		case dBaseExpr:
			if (_pDBaseFile == NULL || _pDBaseField == NULL)
				return FALSE;
		break;
		default:
			return FALSE;
	}

	Bool iResult = FALSE;

//  überprüfen, ob schon Dispatcher für dieses Fenster existiert
	CTable t (*_pDBaseDisp);

	if (_hWnd != 0) {
		if (!t.Find ((void *)&_hWnd)) {
		//  noch kein dBaseDispatch für dieses Fenster angelegt
			pWindow pORWindow = ORWind (_hWnd);
				
			if (pORWindow) {
				dBaseDispatchCreator DBCr (*_pDBaseDisp);
				long lActObj = DEX_GetActiveObject (_hWnd);
						
				Create (DBCr, dBaseDispatch) (pORWindow, lActObj);
			}   // einbauen
		}

	//  DBaseFenster zum Dispatcher hinzufügen und anzeigen
		_pDBaseDisp -> ShowDBaseWindowField (_hWnd, _pDBaseFile, _pDBaseField, _pDBaseKey, &RF(), _Type);
		iResult = TRUE;
	}

	return iResult;
}

// Lesen der INI-Datei für ein Objekt nach DBaseInformationen -----------------
short DBaseExtension :: ReadDBaseCodes (long lONr, long lIdent)
{
	DBaseProFile ProFile;		  // ProjektINI
	long *pMKs = NULL;
	char **ppMStrs = NULL;
	int iCnt = ProFile.ReadDBaseCodes (&pMKs, &ppMStrs, lIdent);
	short iMCnt = 0;

	DELETE_VEC (_pDBaseFile);		   // alte Info freigeben
	DELETE_VEC (_pDBaseKey);
	DELETE_VEC (_pDBaseField);

	_Type = FeldName;			   // Typ setzen

// 	wenn Merkmale existieren, dann hat Objekt DBaseDaten
	if (pMKs != NULL && ppMStrs != NULL && iCnt >= MinParCnt) 
	{
	// 	1. Parameter immer dBase-File-Name                   
		if (ValidMK (pMKs[0]) && ExistsMValue (lONr, pMKs[0])) 
		{
			_pDBaseFile = new char [_MAX_PATH];
			if (GetMerkmalsValue (lONr, pMKs[0], _pDBaseFile, _MAX_PATH))
				iMCnt++;
		} 
		else
			if (ppMStrs[0] != NULL) 
			{
				_pDBaseFile = ppMStrs[0];
				ppMStrs[0] = NULL;			 
				iMCnt++;
			}

	// 	2. Parameter Feld-, Tagname oder dBase-Expression
	 	if (ValidMK (pMKs[1]) && ExistsMValue (lONr, pMKs[1])) 
	 	{
			_pDBaseField = new char [_MAX_PATH];
			if (GetMerkmalsValue (lONr, pMKs[1], _pDBaseField, _MAX_PATH))
				iMCnt++;
		} 
		else 
		{
			if (pMKs[1] == -1L && ppMStrs[1] != NULL) 
			{
				_pDBaseField = ppMStrs[1];
				ppMStrs[1] = NULL;	  
				iMCnt++;
			} 
			else 
			{
				if (pMKs[1] == -3L && ppMStrs[1] != NULL) 
				{ 	
				// 	Tag gegeben
					_Type = TagName;
					if (ExistsMValue (lONr, strtoul (ppMStrs[1], NULL, DEX_GetMkBase ()))) 
					{
						_pDBaseField = new char [_MAX_PATH];
						if (GetMerkmalsValue (lONr, strtoul (ppMStrs[1], NULL, DEX_GetMkBase ()), _pDBaseField, _MAX_PATH))
							iMCnt++;
					} 
					else 
					{		
					// 	Tagname direkt gegeben
						_pDBaseField = ppMStrs[1];
						ppMStrs[1] = NULL;	  // dopp. löschen verh.
						iMCnt++;
					}
				} 
				else 
				{
					if (pMKs[1] == -2L && ppMStrs[1] != NULL) 
					{ 
					// 	dBase-Express.
						_Type = dBaseExpr;
						if (_pDBaseField = _ExpandDBaseExpression (lONr, ppMStrs[1]))
							iMCnt++;
					}
				}
			}
		}

	// 	optionaler 3. Parameter Feldinhalt oder Schlüssel
		if (iCnt > MinParCnt) 
		{
			if (ValidMK (pMKs[2]) && ExistsMValue (lONr, pMKs[2])) 
			{
				_pDBaseKey = new char [_MAX_PATH];
				if (GetMerkmalsValue (lONr, pMKs[2], _pDBaseKey, _MAX_PATH))
										iMCnt++;
			} 
			else
			 	if (ppMStrs[2] != NULL) 
			 	{
					_pDBaseKey = ppMStrs[2];
					ppMStrs[2] = NULL;	   
					iMCnt++;
				}
			}
		}
		
//	prüfe gelesene Parameter        
	switch (_Type)
	{
		case TagName:									// aus Kompatbilitätsgründen (Index)
		case FeldName:    								// Feldname	
		{
			if ((iMCnt < 3) ||		// Anbindung nur über wenigstens 3 Parameter				
				(!_pDBaseFile) || (!*_pDBaseFile) ||	// gültigen AliasNamen
				(!_pDBaseField) || (!*_pDBaseField)  ||	// gültigen Feld/Tagnamen
				(!_pDBaseKey) || (!*_pDBaseKey))			// und gültigen Schlüssel
				iMCnt = 0;					
		}			
		break;
		case dBaseExpr:									// WHERE-Klausel
		{
			if ((iMCnt < MinParCnt) ||		// Anbindung nur über wenigstens 2 Parameter				
				(!_pDBaseFile) || (!*_pDBaseFile) ||	// gültigen AliasNamen
				(!_pDBaseField) || (!*_pDBaseField)) 		// gültige Klausel
				iMCnt = 0;					
		}   
		break;                                                      
		default:
			iMCnt = 0;
	}
		
// 	Speicher wieder freigeben
	DELETE_VEC (pMKs);  
	if (ppMStrs != NULL) 
	{
		for (short iLoop = 0; iLoop < iCnt; iLoop++) 
		{
			DELETE_VEC (ppMStrs[iLoop]);
		}
		DELETE_VEC (ppMStrs);
	}

	return iMCnt;
}

// dBase-Expression expandieren
pchar DBaseExtension :: _ExpandDBaseExpression (long ONr, pchar pExpr) 
{
//  prüfe Parameter
	if (!pExpr || !*pExpr)
		return NULL;

//  Variablen init.
	pchar pAct = pExpr;		 // akt. Zeichen
	pchar pBegin = pExpr;	   // Beginn des öffnenden Separators
	pchar pResult = NULL;	   // Zeiger auf Ergebnis
	pchar pTemp = NULL;		 // Puffer-Zeiger
	char Merkmal [_MAX_PATH] = "";  // akt. Merkmalswert
	short ActLen = 0;		   // Textlängen
	short OldLen = 0;

//  Expression expandieren
	for (; ; ) {
	//  Beginn des 1./weiteren Parameters suchen
		pBegin = pAct;
		while (*pBegin && *pBegin != BeginExpr)
			pBegin++;
		if (!*pBegin)		   // Textende erreicht
			break;

	//  kopiere alle Zeichen bis zum Parameterbeginn
		ActLen = pBegin - pAct;
		pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + sizeof (Merkmal) + 1];
		if (!pTemp) {				   // wenn kein Speicher mehr
			DEX_Error (RC_ExpdBaseExpr, EC_NOMEMORY);   // Fehlermeldung ausgeben
			DELETE_VEC (pResult);		   // alten Wert ggf. löschen
			return NULL;				// zurück
		}
		*pTemp = '\0';
		if (pResult)
			lstrcpy (pTemp, pResult);	// alten Text kopieren
		DELETE_VEC (pResult);			   // und löschen
		pResult = pTemp;
		OldLen = pResult ? lstrlen (pResult) : 0;   // alte Länge merken
		memcpy (pResult + OldLen, pAct, ActLen); // neuen Text ans akt. Ende kop.
		* (pResult + OldLen + ActLen) = '\0';   // Textende setzen

	//  lese und speichere Merkmalswert
		long MKode = strtoul (++pBegin, NULL, DEX_GetMkBase ());
		if (MKode && GetMerkmalsValue (ONr, MKode, Merkmal, sizeof (Merkmal)))
			lstrcat (pResult, Merkmal);

	//  akt. Zeiger neu setzen
		while (*pAct && *pAct != EndExpr)
			pAct++;
		if (*pAct)			  // wenn noch kein Textende erreicht,
			pAct++;			 // auf 1. Zeichen nach Separator
		else {				  // Syntax-Fehler
			DEX_Error (RC_ExpdBaseExpr, EC_SYNTAX);
			DELETE_VEC (pResult);
			return NULL;
		}
	}   //  end of while

//  ggf. letzten Zeichen kopieren
	ActLen = pBegin - pAct;
	if (ActLen > 0) {
		pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + 1];
		if (!pTemp) {
			DELETE_VEC (pResult);
			DEX_Error (RC_ExpdBaseExpr, EC_NOMEMORY);
			return NULL;
		}
		*pTemp = '\0';
		if (pResult) 
			lstrcpy (pTemp, pResult);	  // alten Text kopieren
		DELETE_VEC (pResult);			   // und löschen
		pResult = pTemp;
		OldLen = pResult ? lstrlen (pResult) : 0;
		memcpy (pResult + OldLen, pAct, ActLen); // Rest kopieren
		* (pResult + OldLen + ActLen) = '\0';   // Ende-Kennung setzen
	}

	return pResult;
}




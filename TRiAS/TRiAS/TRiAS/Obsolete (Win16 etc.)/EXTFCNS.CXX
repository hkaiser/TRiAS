// Fuktionen, die bei externen Messages gerufen werden ------------------------
// File: EXTFCNS.CXX
// @doc

#include "triaspre.hxx"

#include <shellapi.h>
#include <tchar.h>
#include <registry.hxx>
#include <konsobj.hxx>

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "overview.hxx"
#include "legdinfo.hxx"
#include "legwind.hxx"

#include "triasres.h"
#include "strings.h"

#if defined(WIN32)
#include <funcs03.h>

#include <xtsnguid.h>		// GUID's
#include <undoguid.h>
#include <iunredo.hxx>

#include <undohelp.hxx>
#endif // WIN32

extern pApp CurrApp;		// aktuelle App
extern HINSTANCE hInstance;	// aktuelles InstanceHandle
extern HPALETTE hPalette;	// aktive Farbpalette

extern bool LegendeCFlag;	// Legende angezeigt
extern bool OverViewCFlag;
extern bool LegendToRepaint;
extern bool PrintEFlag;		// Drucken !aktiv
extern bool g_fMenu;		// Menu's anzeigen

extern short GCancelFlag;       // General Cancel Flag

#if defined(OLD_TOOLBOX)
extern class ToolWind *pToolBox;	// ToolBox
#else
extern int g_iActTool;		// aktives Tool
#endif // OLD_TOOLBOX

extern class COverView *pOverView;	// Gesamtübersicht
extern class CLegendeWindow *pLegende;	// Legende

extern char cbDefaultDir[_MAX_PATH+1];

bool g_fDiagnostics;		// DiagnosticNotifications ausgeben
extern bool g_fAutomation;	// durch OLE Automation gestartet
extern bool g_fStartByOle;	// mit /Embedding gestartet
extern bool g_fTip;			// mit -t gestartet

extern bool g_fSystemAdm;	// SystemAdministratorMode

#if defined(_DEBUG) && defined(WIN32)
extern short g_iKonsFlags;
#endif // _DEBUG

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// sonstige FunktionsPrototypen -----------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes);
short OTypToBits (ObjTyp iOTyp);
ErrCode MainInitPbd (GeoDB &DB, uint resID, Bool iEnterNewCode, long lNewCode);

#if !defined(WIN32)
bool IsWin32s (void);
#endif

#if 0
// Vergleicht GeoTyp mit VisTyp ------------------------------------------------
VisType OTypToVTyp (ObjTyp iOTyp) 
{
	switch (iOTyp) {
	case OT_PUNKT:	return VT_Punkt;
	case OT_KANTE:	return VT_Linie;
	case OT_FLAECHE:
	case OT_KREIS:	return VT_Flaeche;
	case OT_TEXT:	return VT_Text;
	case OT_UNKNOWN:
	case OT_KO:
	default:
		break;
	}

return VT_Default;
}
#endif

// ----------------------------------------------------------------------------
// Funktion, die für eine nicht definierte Message gerufen werden soll --------
LRESULT ExtDirisWindow :: OnNotDefinedMessage (LPARAM lParam)
{
DWORD dwSndSize = 0;
const char *pSnd = ReadResource (hInstance, IDSND_QUACK, dwSndSize);

	if (pSnd) {	// synchron abspielen
		sndPlaySound (pSnd, SND_MEMORY|SND_NODEFAULT|SND_SYNC);
		delete (char *)pSnd;
	} else
		MessageBeep ((UINT)-1);

return false;
}

// Abfrage eines Textmerkmales (Objekt, Identifikator oder Sicht) -------------
static LRESULT RetrieveMiText (long lMCode, long lTarget, short iTTyp,
			       char *pMText, short &imaxLen);

// @msg DEX_QUERYTEXTMERKMAL | Mit dieser Message an <tr> ist es möglich Merkmale
// eines Objektes, eines Identifikators oder einer Ansicht zu lesen.
// @parm TARGETMERKMAL * | pTargetFeature | lParam zeigt auf eine Struktur vom Typ
// <t TARGETMERKMAL>.
// @rdesc Diese Message liefert einen Zeiger auf den in der Datenstruktur übergebenen
// Zeichenkettenpuffer (<e TARGETMERKMAL.pMText>). Im Fehlerfall liefert diese Message 
// NULL.
// @comm Diese Message wird durch die Funktion <f DEX_GetTextMerkmal> ausgelöst.
// @xref <f DEX_GetTextMerkmal>, <t TARGETMERKMAL>, <t ErrCode>
LRESULT ExtDirisWindow :: OnQueryTextMerkmal (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

TARGETMERKMAL *pGM = (TARGETMERKMAL *)lParam;

#if defined(_DEBUG)
	if (pGM -> dwSize == sizeof(TARGETMERKMAL))
		TX_ASSERT_POINTER(pGM, TARGETMERKMAL);
	else {
		TX_ASSERT(sizeof(TARGETMERKMALEX) == pGM -> dwSize);
		TX_ASSERT_POINTER(pGM, TARGETMERKMALEX);
	}
#endif

	TX_ASSERT(IsValidMCode(pGM -> lMCode));
	TX_ASSERT(pGM -> imaxLen >= 0);
	TX_ASSERT(NULL == pGM -> pMText || TIsValidAddress (pGM -> pMText, pGM -> imaxLen, true));

long lTarget = GetTarget ((void *)pGM -> lTarget, pGM -> iTTyp);
ErrInstall EI (WC_NOTFOUND);

	if (lTarget == -1) return (LRESULT)NULL;
	
	switch (pGM -> iTTyp) {
	case TT_Objekt:
		{	// den ObjektMerkmalsCache befragen
			TX_ASSERT(IsValidONr(lTarget));

		CTable t(DBO().Shapes().ObjNumTree());
		
			if (t.Find (&lTarget)) {
			ExtShapeObjectLock l(t);
			CFeature* pF = l -> FFindFeature (pGM -> lMCode);
			
				if (pF) {
					if (pGM -> pMText) {
						strncpy (pGM -> pMText, pF -> FText(), pGM -> imaxLen-1);
						pGM -> pMText[pGM -> imaxLen -1] = '\0';
						return (LRESULT)pGM -> pMText;
					} else {
						pGM -> imaxLen = strlen (pF -> FText());
						return (LRESULT)true;
					}
				}
		// wenn Objekt nur temporär ist, dann hier aufhören
				if (l -> Status() == OS_Temp) 
					return (LRESULT)NULL;
		
		// Cache enthält dieses Merkmal noch nicht, also hinzufügen
			LRESULT lR = RetrieveMiText (
					pGM -> lMCode, lTarget, pGM ->  iTTyp,
					pGM -> pMText, pGM -> imaxLen);

				if (lR && 
				    (pGM -> dwSize == sizeof(TARGETMERKMAL) ||
				     !(((TARGETMERKMALEX *)pGM) -> iFlags & TMNoCaching)
				    )
				   )
				{
					l -> FAddFeature (pGM -> lMCode, pGM -> pMText);
				}
				return lR;
			} else {
			// Objekt ist nicht geladen
				return RetrieveMiText (pGM -> lMCode, lTarget, pGM ->  iTTyp,
						       pGM -> pMText, pGM -> imaxLen);
			}
		}
//		break;		// unreachable code
						
	case TT_Identifikator:
	case TT_Sicht:
		return RetrieveMiText (pGM -> lMCode, lTarget, pGM ->  iTTyp,
				       pGM -> pMText, pGM -> imaxLen);

	default:		// falscher MerkmalsTarget
		TX_ASSERT(false);
		break;
	}
		
return (LRESULT)NULL;
}

		
static LRESULT RetrieveMiText (long lMCode, long lTarget, short iTTyp,
			       char *pMText, short &imaxLen)
{
char *pT = NULL;
		
	GetMiText (lMCode, lTarget, iTTyp, &pT);
	if (pT) {
		if (pMText) {	// Merkmal extrahieren
			strncpy (pMText, pT, imaxLen-1);
			pMText[imaxLen -1] = '\0';
			imaxLen = strlen (pT);
			delete pT;
			return (LRESULT)pMText;
		} else {            	// nur Testen, ob Merkmal existiert
			imaxLen = strlen (pT);
			delete pT;
			return (LRESULT)true;
		}
	}
	imaxLen = -1;	// kein Merkmal
	
return (LPARAM)NULL;
}

// ----------------------------------------------------------------------------
// Objekt-/Sicht-/IdentifikatorMerkmal schreiben ------------------------------
// @msg DEX_MODIFYMERKMAL | Mit dieser Message an <tr> ist es möglich Merkmale
// eines Objektes, eines Identifikators oder einer Ansicht zu modifizieren oder zu 
// löschen.
// @parm TARGETMERKMAL * | pTargetFeature | lParam zeigt auf eine Struktur vom Typ
// <t TARGETMERKMAL>.
// @rdesc Diese Message liefert einen <t ErrCode>, der evtl. aufgetretene Fehler 
// verschlüsselt.
// @comm Diese Message wird durch die Funktion <f DEX_ModTextMerkmal> ausgelöst.
// @xref <f DEX_ModTextMerkmal>, <t TARGETMERKMAL>, <t ErrCode>
LRESULT ExtDirisWindow :: OnModTextMerkmal (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
TARGETMERKMAL *pMMK = (TARGETMERKMAL *)lParam;

#if defined(_DEBUG)
	if (sizeof(TARGETMERKMAL) == pMMK -> dwSize)
		TX_ASSERT_POINTER(pMMK, TARGETMERKMAL);
	else {
		TX_ASSERT(sizeof(TARGETMERKMALEX) == pMMK -> dwSize);
		TX_ASSERT_POINTER((TARGETMERKMALEX *)pMMK, TARGETMERKMALEX);
	}
#endif

	TX_ASSERT(IsValidMCode(pMMK -> lMCode));
	TX_ASSERT(pMMK -> imaxLen >= 0);
	TX_ASSERT(NULL == pMMK -> pMText || TIsValidAddress (pMMK -> pMText, pMMK -> imaxLen, false));

long lTarget = GetTarget ((void *)pMMK -> lTarget, pMMK -> iTTyp);
ErrInstall EI (WC_NOTFOUND);
ErrCode RC = EC_OKAY;
CActDB ActDB (DBO().DB());

	if (lTarget == -1) {
		if (pMMK -> iTTyp != TT_Sicht) 
			return (LRESULT)WC_NOTFOUND;	// Fehler, Bezug gibt es nicht
		else if (pMMK -> pMText && pMMK -> imaxLen >= 0) {
		// Sicht anlegen
			TX_ASSERT(TIsValidString ((char *)pMMK -> lTarget));

		Sicht S (DBO().DB(), (char *)pMMK -> lTarget);
		
			return (LRESULT)S.PutMiText (pMMK -> lMCode, pMMK -> pMText);
		} else
			return (LRESULT)WC_NOTFOUND;	// kann nichts löschen, wo es nichts zu löschen gibt
	}
	
	switch (pMMK -> iTTyp) {
	case TT_Objekt:
		{	// den ObjektMerkmalsCache befragen
			TX_ASSERT(IsValidONr(lTarget));

		CTable t(DBO().Shapes().ObjNumTree());
		
			if (t.Find (&lTarget)) {	// FeatureCache korrigieren
			ExtShapeObjectLock l(t);

			// Caching soll ggf. nicht erfolgen
				if (pMMK -> dwSize == sizeof(TARGETMERKMAL) ||
				    !(((TARGETMERKMALEX *)pMMK) -> iFlags & TMNoCaching) ||
				    OS_Temp == l -> Status()) 
				{
					l -> FDeleteFeature (pMMK -> lMCode);
					if ((pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) &&
					    (!l -> FAddFeature (pMMK -> lMCode, pMMK -> pMText)))
							return (LRESULT)EC_NOMEMORY;
				} else
					l -> FDeleteFeature (pMMK -> lMCode);

			// wenn Objekt nur temporär ist, dann hier aufhören
				if (OS_Temp == l -> Status()) 
					break;
			}
							
		// in der DB nachführen
			DBO().DB().SetDirty();
			delmi (pMMK -> lMCode, lTarget, pMMK -> iTTyp);
			if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) {
				AnsiToOem (pMMK -> pMText, pMMK -> pMText);
				DBASSERT (PutMiText (pMMK -> lMCode, lTarget, pMMK -> iTTyp, pMMK -> pMText));
			
			// Merkmals-Integrität testen
				TX_ASSERT(EC_OKAY == TestObjektMerkmal (DBO().DB(), lTarget, pMMK -> lMCode, g_iKonsFlags));
			} 
			else {	// alle Merkmale Testen, da eines gelöscht wurde
				TX_ASSERT(EC_OKAY == TestObjektMerkmalDeleted (DBO().DB(), lTarget, pMMK -> lMCode, g_iKonsFlags));
			}
		}
		break;
						
	case TT_Identifikator:
		TX_ASSERT(IsValidIdent (pMMK -> lTarget));

		DBO().DB().SetDirty();
		delmi (pMMK -> lMCode, lTarget, pMMK -> iTTyp);
		if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) {
			AnsiToOem (pMMK -> pMText, pMMK -> pMText);
			DBASSERT (PutMiText (pMMK -> lMCode, lTarget, TT_Identifikator, pMMK -> pMText));

		// Merkmals-Integrität testen
			TX_ASSERT(EC_OKAY == TestIdentMerkmal (DBO().DB(), pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
		}
		else {	// alle Merkmale Testen, da eines gelöscht wurde
			TX_ASSERT(EC_OKAY == TestIdentMerkmalDeleted (DBO().DB(), pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
		}
		break;
		
	case TT_Sicht:
		TX_ASSERT(TIsValidString ((char *)pMMK -> lTarget));

		DBO().DB().SetDirty();
		delmi (pMMK -> lMCode, lTarget, pMMK -> iTTyp);
		if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) {
			AnsiToOem (pMMK -> pMText, pMMK -> pMText);
			DBASSERT (PutMiText (pMMK -> lMCode, lTarget, TT_Sicht, pMMK -> pMText));

		// Merkmals-Integrität testen
			TX_ASSERT(EC_OKAY == TestSichtMerkmal (DBO().DB(), (LPCSTR)pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
		}
		else {	// alle Merkmale Testen, da eines gelöscht wurde
			TX_ASSERT(EC_OKAY == TestSichtMerkmalDeleted (DBO().DB(), (LPCSTR)pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
		}
		break;
		
	default:		// falscher MerkmalsTarget
		TX_ASSERT(false);
		break;
	}

return (LPARAM)EC_OKAY;
}


// Enumeration aller Identifikatoren einer Sicht ------------------------------
extern "C" 
static inline bool EnumIdentsCallback (bool (*pFcn)(long, bool, void *), 
				long lKey, bool fNotLast, void *pData)
{
	return ((ENUMLONGKEYCALLBACK) pFcn)(lKey, fNotLast, pData);
}

LRESULT ExtDirisWindow :: OnEnumSightIdents (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEY *pK = (ENUMTEXTKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	if (pK -> eKey == NULL || *(pK -> eKey) == '\0') {
	// aktuelle oder temporäre Sicht
	CTable t (DBO().Idents().IdentTree());
	bool fRet = true;
	bool fLast = false;
	GeoDB &rDB = DBO().DB();
		
		for (t.First(); t.Valid(); /* */) {
		CIdentifikatorLock lId (t);
		
			fLast = !t.Next();
			
			TX_ASSERT(NULL != (CIdentifikator *)lId);
			if (!lId) continue;

		// Info ggf. aus GeoDB lesen
		int iToPaint = (lId -> toPaint() & lId -> GetOTypes (rDB)) | (lId -> hasKO() ? OTKO : 0);

			if (!iToPaint) continue;
			if ((fRet = EnumIdentsCallback (pK -> eFcn, lId -> Id(), 
							!fLast, 
							pK -> ePtr)) == false) 
			{
				break;
			}
		}
		return fRet;
	} else {
	// aus Datenbank lesen
		TX_ASSERT(TIsValidString(pK -> eKey));

	Sicht locSicht (DBO().DB(), pK -> eKey);
	
		return (LRESULT)locSicht.EnumIdents (pK -> eFcn, pK -> ePtr);
	}
}


// Enumeration aller Identifikatoren einer Sicht unter Angabe der vorhandenen 
// Objekttypen
extern "C"
static inline bool EnumIdentsExCallback (bool (*pFcn)(long, DWORD, void *), 
				long lKey, DWORD dwData, void *pData)
{
	return ((ENUMLONGKEYEXCALLBACK) pFcn)(lKey, dwData, pData);
}

LRESULT ExtDirisWindow :: OnEnumSightIdentsEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEYEX *pK = (ENUMTEXTKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

	if (pK -> eKey == NULL || *(pK -> eKey) == '\0') {
	// aktuelle oder temporäre Sicht
	CTable t (DBO().Idents().IdentTree());
	bool fRet = true;
	short iToPaint = 0;
	GeoDB &rDB = DBO().DB();

		for (t.First(); t.Valid(); t.Next()) {
		CIdentifikatorLock lId (t);
		
			TX_ASSERT(NULL != (CIdentifikator *)lId);
			if (!lId) continue;

//			if ((iToPaint = lId -> toPaint()) == 0 ||
//			    !(iToPaint & pK -> eData)) 
//				continue;

		// ggf. aus GeoDB lesen
			iToPaint = (lId -> toPaint() & lId -> GetOTypes (rDB)) | (lId -> hasKO() ? OTKO : 0);
			if (!(iToPaint & pK -> eData))
				continue;
			if ((fRet = EnumIdentsExCallback (pK -> eFcn, lId -> Id(), 
							iToPaint & pK -> eData, 
							pK -> ePtr)) == false) 
			{
				break;
			}
		}
		return fRet;
	} else {
	// aus Datenbank lesen
		TX_ASSERT(TIsValidString(pK -> eKey));

	Sicht locSicht (DBO().DB(), pK -> eKey);
	
		return (LRESULT)locSicht.EnumIdentsEx (pK -> eFcn, pK -> ePtr, (short)pK -> eData);
	}
	
// return true;		// --> unreachable code
}


// Enumeration aller Identifikatoren ------------------------------------------
// @msg DEX_ENUMALLIDENTS | Mit dieser Message an <tr> ist es möglich alle 
// Identifikatoren des aktuellen Projektes zu enumerieren.
// @parm ENUMNOKEYLONG * | pEnumNoKey | lParam zeigt auf eine Struktur vom Typ
// <t ENUMNOKEYLONG>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumIdents> ausgelöst.<par>Um 
// zusätzlich den gewünschten Objekttyp vorgeben zu können, muß die 
// Message <m DEX_ENUMALLIDENTSEX> eingesetzt werden.
// werden.
// @xref <f DEX_EnumIdents>, <m DEX_ENUMALLIDENTSEX>, <t ENUMNOKEYLONG>
LRESULT ExtDirisWindow :: OnEnumIdents (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	return (LRESULT)DBO().DB().EnumIdents (
				(ENUMNOKEYLONGPROC)pK -> eFcn, pK -> ePtr);
}


// Enumeration aller Identifikatoren unter Berücksichtigung der gewünschten 
// Objektypen
// DEX_ENUMALLIDENTSEX
LRESULT ExtDirisWindow :: OnEnumIdentsEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEYEX *pK = (ENUMNOKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	return (LRESULT)DBO().DB().EnumIdentsEx (
				(ENUMNOKEYLONGEXPROC)pK -> eFcn, 
				pK -> ePtr, (short)pK -> eData);
}


// Enumeration aller Objekte mit einem Identifikator --------------------------
// @msg DEX_ENUMIDENTOBJS | Mit dieser Message an <tr> ist es möglich alle 
// Objekte eines vorgegebenen Identifikators zu enumerieren.
// @parm ENUMLONGKEY * | pEnumLongKey | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEY>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumIdentObjects> 
// ausgelöst.<par>Das Feld <e ENUMLONGKEY.eKey> muß vor dem Aufruf der Message 
// mit dem zu untersuchenden Identifikator belegt werden.<par>Bei dieser Enumeration
// wird der Objekttyp nicht berücksichtigt, d.h. es werden grundsätzlich alle Objekte,
// die den gegebenen Identifikator besitzen, enumeriert. Um zusätzlich den gewünschte
// Objekttyp vorgeben zu können, muß die Message <m DEX_ENUMIDENTOBJSEX> eingesetzt 
// werden.
// @xref <f DEX_EnumIdentObjects>, <m DEX_ENUMIDENTOBJS>, <m DEX_ENUMIDENTOBJSEX>, 
// <t ENUMLONGKEY>
LRESULT ExtDirisWindow :: OnEnumIdentObjects (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent((long)pK -> eKey));

CActDB ActDB (DBO().DB());

	return (LRESULT)DBO().DB().EnumIdentObjects (
			pK -> eKey, pK -> eFcn, pK -> ePtr);
}

// @msg DEX_ENUMIDENTOBJSEX | Mit dieser Message an <tr> ist es möglich alle 
// Objekte eines vorgegebenen Identifikators unter Berücksichtigung eines
// gewünschten Objekttypes (oder mehererer) zu enumerieren.
// @parm ENUMLONGKEYEX * | pEnumLongKeyEx | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEYEX>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumIdentObjectsEx> 
// ausgelöst.<par>Das Feld <e ENUMLONGKEYEX.eKey> muß vor dem Aufruf der Message 
// mit dem zu untersuchenden Identifikator belegt werden. Das 
// Feld <e ENUMLONGKEYEX.eData> muß mit den zu enumerierenden Objettypen belegt werden,
// wobei folgende Werte (oder deren Kombination) verwendet werden können:
// @flag OTPunkt | Es sollen alle Punktobjekte dieses Identifikators enumeriert werden.
// @flag OTLinie | Es sollen alle Linienobjekte dieses Identifikators enumeriert werden.
// @flag OTFlaeche | Es sollen alle Flächenobjekte dieses Identifikators enumeriert werden.
// @flag OTText | Es sollen alle Textobjekte dieses Identifikators enumeriert werden.
//<par>Bei dieser Enumeration wird der Objekttyp berücksichtigt. Sollen alle Objekte
// eines IDentifikators enumeriert werden, so ist es möglich die Message 
//<m DEX_ENUMIDENTOBJS> einzusetzen.
// @xref <f DEX_EnumIdentObjects>, <m DEX_ENUMIDENTOBJS>, <t ENUMLONGKEYEX>
LRESULT ExtDirisWindow :: OnEnumIdentObjectsEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEYEX *pK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent((long)pK -> eKey));

CActDB ActDB (DBO().DB());

	return (LRESULT)DBO().DB().EnumIdentObjectsEx (
			pK -> eKey, pK -> eFcn, pK -> ePtr, pK -> eData);
}


// Abfrage eines ObjektContainers ---------------------------------------------
LRESULT ExtDirisWindow :: OnQueryObjContainer (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
	TX_ASSERT(IsValidONr(*(long *)lParam));

// hier wird getrickst, die Objektnummer wird im ersten Feld der 
// übergebenen ObjContainerStruktur geliefert, und dann überschrieben
	return DBO().GetObjContainer (*(long *)lParam, *(ObjContainer *)lParam);
}


LRESULT ExtDirisWindow :: OnGetLastIdent (LPARAM)
{
	return (LRESULT)GetLastIdent();
}


LRESULT ExtDirisWindow :: OnSetLastIdent (LPARAM lParam)
{
	TX_ASSERT(IsValidIdent((long)lParam));

	SetLastIdent ((long)lParam);
	
return true;
}

LRESULT ExtDirisWindow :: OnDeleteObject (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);

	TX_ASSERT(IsValidONr((long)lParam));

	DBO().DB().SetDirty();
	return (LRESULT)DBO().DeleteObjekt ((long)lParam);
}

#if defined(WIN32)
LRESULT ExtDirisWindow :: OnDeleteObjectEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidONr((long)lParam));

	DBO().DB().SetDirty();
	DBO().DeleteFeatures (lParam);	// Merkmale mit Undo/Redo löschen
	DBO().DeleteRelations (lParam);	// Relationen mit Undo/Redo löschen

LPUNDOREDODELETEOBJECT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteObject, (LPVOID *)&pIUndo);
//HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//		CLSCTX_INPROC_SERVER, IID_IUndoRedoDeleteObject,
//		(LPVOID *)&pIUndo);
bool fResult = false;

	if (SUCCEEDED(hr)) hr = pIUndo -> Init (lParam, NULL/* (RECT *)rc */);
	if (DBO().DeleteObjekt (lParam)) {
		if (hr == NOERROR)
			DEX_AddUndoRedo (pIUndo);
		fResult = true;
	} 
	if (pIUndo) pIUndo -> Release();

return fResult;
}
#endif // WIN32

// LegendenBehandlung ---------------------------------------------------------
LRESULT ExtDirisWindow :: OnSaveLegend (LPARAM)
{
	if (pLegende) return (LRESULT)pLegende -> SaveLegend();
	return LRESULT(true);
}

LRESULT ExtDirisWindow :: OnResetLegend (LPARAM)
{
	if (pLegende) return (LRESULT)pLegende -> ResetLegend();
	return LRESULT(true);
}

LRESULT ExtDirisWindow :: OnRefreshLegend (LPARAM)
{
	if (pLegende) return (LRESULT)pLegende -> RefreshLegend();
	return LRESULT(true);
}

LRESULT ExtDirisWindow :: OnAddObjectToLegend (LPARAM lParam)
{
	if (pLegende) return (LRESULT)pLegende -> AddObject (lParam);
	return LRESULT(true);
}

LRESULT ExtDirisWindow :: OnRepaintLegend (LPARAM)
{
	if (pLegende) pLegende -> RePaint();
	return LRESULT(true);
}

// DEX_ENUMTEXTMERKMALRECH: Enumeration aller Objekte mit einem Merkmal -------
// @msg DEX_ENUMTEXTMERKMALRECH | Mit dieser Message an <tr> können alle Objekte
// enumeriert werden, die einem vorgebbaren Suchkriterium über die Objektmerkmale
// entsprechen.
// @parm ENUMRECHTEXTMERKMAL * | pEnumRechTextMerkmal | lParam enthält einem Pointer
// auf eine Struktur vom Typ <t ENUMRECHTEXTMERKMAL>
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumRechTextMerkmal> ausgelöst.
// @xref <f DEX_EnumRechTextMerkmal>, <t ENUMRECHTEXTMERKMAL>
LRESULT ExtDirisWindow :: OnEnumTextMerkmal (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
#if defined(_DEBUG)
ENUMRECHTEXTMERKMAL *pERT = (ENUMRECHTEXTMERKMAL *)lParam;

	TX_ASSERT_POINTER(pERT, ENUMRECHTEXTMERKMAL);
	TX_ASSERT(sizeof(ENUMRECHTEXTMERKMAL) == pERT -> dwSize);
	TX_ASSERT(pERT -> pView == NULL || TIsValidString(pERT -> pView));
	TX_ASSERT(IsValidMCode(pERT -> lMCode));
// wenn gleich NULL, dann alle, die diesen MCode besitzen
	TX_ASSERT(NULL == pERT -> pMWert || TIsValidString(pERT -> pMWert));
	TX_ASSERT(TIsValidAddress(pERT -> eFcn, 1, false));
// Mode testen
	if (NULL != pERT -> pMWert) {
	short iMode = pERT -> iMode & ~SMActViewOnly;

		TX_ASSERT(SMExactMatch == iMode || SMInexactMatch == iMode || 
			  SMSubstringMatch == iMode);
	}
#endif // _DEBUG

	return (LRESULT)DBO().EnumRechTextMerkmal ((ENUMRECHTEXTMERKMAL *)lParam);
}

LRESULT ExtDirisWindow :: OnGetTextObjectText (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
GETTEXTDATA *pGTD = (GETTEXTDATA *)lParam;

	TX_ASSERT_POINTER(pGTD, GETTEXTDATA);
	TX_ASSERT(sizeof(GETTEXTDATA) == pGTD -> m_dwSize);
	TX_ASSERT(IsValidONr(pGTD -> m_lONr));
	TX_ASSERT(pGTD -> m_iLen >= 0);
	TX_ASSERT(TIsValidAddress(pGTD -> m_pText, pGTD -> m_iLen, true));	// writeable !

GeoObjekt *pGO = DBO().GetGeoObj (pGTD -> m_lONr);

	if (pGO == NULL || pGO -> isA() != OT_TEXT) {
		DELETE (pGO);
		return false;
	}
	
char *pText = ((GeoText *)pGO) -> Text();

	TX_ASSERT(TIsValidString(pText));

	if (pText && pGTD -> m_pText) {
		strncpy (pGTD -> m_pText, pText, pGTD -> m_iLen);
		pGTD -> m_pText[pGTD -> m_iLen-1] = '\0';
		pGTD -> m_iLen = strlen (pGTD -> m_pText);
	} else 
		pGTD -> m_iLen = 0;
		
	delete pGO;
	
return true;
}

// Enumeration über Geometrie -------------------------------------------------
LRESULT ExtDirisWindow :: OnEnumGeometrie (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
#if defined(_DEBUG)
ENUMRECHGEOMETRIE *pERG = (ENUMRECHGEOMETRIE *)lParam;

	TX_ASSERT_POINTER(pERG, ENUMRECHGEOMETRIE);

	TX_ASSERT(sizeof(ENUMRECHGEOMETRIE) == pERG -> dwSize || 
			  sizeof(ENUMRECHGEOMETRIEEX) == pERG -> dwSize);
	TX_ASSERT(TIsValidAddress(pERG -> lCont, 
		(pERG -> iMode & ERGConverted) ? 4*sizeof(double) : sizeof(ObjContainer), 
		true));	// writeable!
	TX_ASSERT(TIsValidAddress(pERG -> eFcn, 1, false));
	if (sizeof(ENUMRECHGEOMETRIEEX) == pERG -> dwSize) {
	ENUMRECHGEOMETRIEEX *pERGEx = (ENUMRECHGEOMETRIEEX *)pERG;

		TX_ASSERT(pERGEx -> m_pView == NULL || TIsValidString(pERGEx -> m_pView));
	}
#endif // _DEBUG

	return (LRESULT)DBO().EnumRechGeometrie ((ENUMRECHGEOMETRIE *)lParam);
}

// Identifikator abfragen -----------------------------------------------------
LRESULT ExtDirisWindow :: OnRetrieveIdent (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidONr((LONG)lParam));

	return LRESULT(DBO().RetrieveIdent ((LONG)lParam));
}

// ObjektTyp festellen --------------------------------------------------------
LRESULT ExtDirisWindow :: OnRetrieveOTyp (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(IsValidONr((LONG)lParam));

	return (LRESULT)DBO().RetrieveObjTyp (lParam);
}

LRESULT ExtDirisWindow :: OnIsObjectVisible (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(IsValidONr((LONG)lParam));

	return (LRESULT)DBO().Shapes().isObjectVisible ((long)lParam);
}


LRESULT ExtDirisWindow :: OnEnumTopRelations (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTOPRELS *pETR = (ENUMTOPRELS *)lParam;

	TX_ASSERT_POINTER(pETR, ENUMTOPRELS);
	TX_ASSERT(sizeof(ENUMTOPRELS) == pETR -> m_dwSize);
	TX_ASSERT(IsValidONr(pETR -> m_lONr));
	TX_ASSERT(TIsValidAddress(pETR -> m_eFcn, 1, false));
	TX_ASSERT(NULL == pETR -> m_pView || TIsValidString(pETR -> m_pView));
	TX_ASSERT(0 == (pETR -> m_iMode & ~ETRAnalyzeView));

ObjFeld Objekte;                        // ArrayContainer
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();
CActDB ActDB (rDB);

	if (rDB.RigInfo (pETR -> m_lONr, Objekte) != EC_OKAY)
		return LRESULT(false);
		
	if (pETR -> m_iMode & ETRAnalyzeView) {
	// zusätzlich über gegebene Sicht filtern
		if (pETR -> m_pView == NULL) {
		// nach Identifikatoren (über aktuelle Sicht) filtern
			if (rDB.IdFilter (Objekte, rDBO.Idents()) != EC_OKAY)
				return LRESULT(false);
		} else {
		// nach Identifikatoren (über gegebebene Sicht) filtern
			if (rDB.IdFilter (Objekte, pETR -> m_pView) != EC_OKAY)
				return LRESULT(false);
		}
	}

return (LRESULT)Objekte.Enumerate (pETR -> m_eFcn, (void *)pETR -> m_dwData);
}


// Funktionen, die entsprechend der erhaltenen message gerufen werden müssen --
// DEX_MENUITEMINSTALL:	MenuItem installieren ---------------------------------
// @msg DEX_MENUITEMINSTALL | Diese Message wird an <tr> geschickt, wenn ein
// zusätzlicher Menupunkt installiert werden soll.
// @parm INSTALLMENUITEM * | pInstallMenuItem | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t INSTALLMENUITEM>.
// @rdesc <tr> liefert das Handle des Popupmenus, in dem der Menupunkt installiert 
// wurde, wenn kein Fehler aufgetreten ist. Ansonsten ist der Rückgabewert NULL.
// @comm Ein mit <m DEX_MENUITEMINSTALL> installierter Menupunkt muß durch die 
// Erweiterung mit der Message <m DEX_MENUITEMREMOVE> wieder entfernt werden, bevor
// diese entladen wird.<nl>Diese Message wird durch die Funktion 
// <f DEX_InstallMenuItem> ausgelöst.
// @xref <t INSTALLMENUITEM>, <m DEX_MENUITEMREMOVE>, <f DEX_InstallMenuItem>
LRESULT ExtDirisWindow :: OnDexInstallMenuItem (LPARAM lParam)
{
#if defined(_DEBUG)
INSTALLMENUITEM *pIMI = (INSTALLMENUITEM *)lParam;

	TX_ASSERT_POINTER(pIMI, INSTALLMENUITEM);
	TX_ASSERT(sizeof(INSTALLMENUITEM) == pIMI -> dwSize);
	TX_ASSERT(NULL != pIMI -> hDex);
	TX_ASSERT(0 <= pIMI -> iMenuNum);
	TX_ASSERT(0 <= pIMI -> iMenuID && 100 > pIMI -> iMenuID);
	TX_ASSERT(TIsValidString(pIMI -> pMenuText));
	TX_ASSERT(-1 <= pIMI -> iMenuPos);
#endif // _DEBUG

	return (LRESULT)(NULL != InstallMenuItem ((INSTALLMENUITEM *)lParam));
}

// DEX_MENUITEMREMOVE: MenuItem entfernen -------------------------------------
// @msg DEX_MENUITEMREMOVE | Diese Message wird an <tr> geschickt, wenn ein
// zusätzlich installierter Menupunkt entfernt werden soll.
// @parm REMOVEMENUITEM * | pRemoveMenuItem | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t REMOVEMENUITEM>.
// @rdesc <tr> liefert das Handle des Popupmenus, in dem der Menupunkt installiert 
// wurde, wenn kein Fehler aufgetreten ist. Ansonsten ist der Rückgabewert NULL.
// @comm Es sollten nur Menupunkte entfernt werden, die vorher mit 
// <m DEX_MENUITEMINSTALL> installiert wurden. Auf jeden Fall muß ein mit der
// Message <m DEX_MENUITEMINSTALL> installierter Menupunkt wieder entfernt werden, 
// bevor diese entladen wird.<nl>Diese Message wird durch die Funktion 
// <f DEX_RemoveMenuItem> ausgelöst.
// @xref <m DEX_MENUITEMINSTALL>, <f DEX_RemoveMenuItem>
LRESULT ExtDirisWindow :: OnDexRemoveMenuItem (LPARAM lParam)
{
#if defined(_DEBUG)
REMOVEMENUITEM *pRMI = (REMOVEMENUITEM *)lParam;

	TX_ASSERT_POINTER(pRMI, REMOVEMENUITEM);
	TX_ASSERT(sizeof(REMOVEMENUITEM) == pRMI -> dwSize);
	TX_ASSERT(NULL != pRMI -> hDex);
	TX_ASSERT(0 <= pRMI -> iMenuNum);
	TX_ASSERT(0 <= pRMI -> iMenuID && 100 > pRMI -> iMenuID);
#endif // _DEBUG

	return (LRESULT)RemoveMenuItem ((REMOVEMENUITEM *)lParam);
}

// DEX_TOOLINSTALL: Werkzeug installieren -------------------------------------
// @msg DEX_TOOLINSTALL | Diese Message wird an <tr> geschickt, wenn ein zusätzliches
// Werkzeug ducrh die Erweiterung installiert werden soll.
// @parm INSTALLTOOL | pInstallToolData | lParam enthält einen Pointer auf eine 
// Struktur vom Typ <t INSTALLDATA>.
// @rdesc Diese Message liefert den Werkzeug-ID des neu installierten Werkzeuges (0...)
// oder -1 im Fehlerfall.
// @comm Ein mit <m DEX_TOOLINSTALL> installiertes Werkzeug muß durch die 
// Erweiterung mit der Message <m DEX_TOOLREMOVE> wieder entfernt werden, bevor
// diese entladen wird.<nl>Diese Message wird durch die Funktion 
// <f DEX_InstallTool> ausgelöst.
// @xref <t INSTALLDATA>, <m DEX_TOOLREMOVE>, <f DEX_InstallTool>
LRESULT ExtDirisWindow :: OnDexInstallTool (LPARAM lParam)
{
#if defined(_DEBUG)
INSTALLTOOL *pIT = (INSTALLTOOL *)lParam;

	TX_ASSERT_POINTER(pIT, INSTALLTOOL);
	TX_ASSERT(sizeof(INSTALLTOOL) == pIT -> dwSize);
	TX_ASSERT(TIsValidString(pIT -> pDesc));
	TX_ASSERT(NULL != pIT -> hBmp);
#endif // _DEBUG

	return (LRESULT)InstallTool ((INSTALLTOOL *)lParam);
}

// DEX_TOOLREMOVE: Werkzeug entfernen -----------------------------------------
// @msg DEX_TOOLREMOVE | Diese Message wird an <tr> geschickt, um ein zusätzlich
// installiertes Werkzeug wieder zu entfernen.
// @parm short | iToolID | lParam enthält das Werkzeug-ID, welches das zu entfernende
// Werkzeug identifiziert.
// @rdesc Diese Message liefert keinen Rückgabewert.
// @comm Es sollten nur Werkzeuge entfernt werden, die vorher mit 
// <m DEX_TOOLINSTALL> installiert wurden. Auf jeden Fall muß ein durch die 
// Erweiterung mit der Message <m DEX_TOOLINSTALL> installiertes Werkzeug 
// wieder entfernt werden, bevor diese entladen wird.<nl>Diese Message wird 
// durch die Funktion <f DEX_RemoveTool> ausgelöst.
// @xref <m DEX_TOOLINSTALL>, <f DEX_RemoveTool>
LRESULT ExtDirisWindow :: OnDexRemoveTool (LPARAM lParam)
{
	return (LRESULT)RemoveTool ((short)lParam);
}

// DEX_QUERYACTIVEPROJECT: aktuelles Projekt abfragen -------------------------
// @msg DEX_QUERYACTIVEPROJECT | Diese Message wird an <tr> geschickt, um den 
// Namen des aktuellen Projektes abzufragen.
// @parm char * | pProjectName | lParam enthält einen Zeichenkettenpuffer, der 
// groß genug sein muß, um einen vollen Pfadnamen zu halten (_MAX_PATH). In diesem
// Puffer wird der Name des aktuellen Projektes abgelegt. 
// @rdesc Diese Message liefert den Wert von lParam, wenn kein Fehler aufgetreten 
// ist. Wenn kein aktives Projekt existiert oder im Fehlerfall liefert diese 
// Message NULL.
// @comm <tr> kann zur Zeit gleichzeitig lediglich ein Projekt geöffnet halten
// <m DEX_PROJECTOPEN>.<nl>Diese Message wird durch die Funktion 
// <f DEX_OpenProject> ausgelöst.
// Dieses Projekt ist somit auch das aktive Projekt. 
// @xref <m DEX_PROJECTOPEN>, <f DEX_OpenProject>
LRESULT ExtDirisWindow :: OnDexQueryActiveProject (LPARAM lParam)
{
	TX_ASSERT(TIsValidAddress((void *)lParam, _MAX_PATH, true));	// writeable!
	
	return (LRESULT)RetrieveActiveProject((char *)lParam);
}

// DEX_QUERYACTIVEUSER: aktuellen NutzerNamen abfragen ------------------------
// @msg DEX_QUERYACTIVEUSER | Diese Message wird an <tr> geschickt, um den 
// Namen des aktuellen Nutzers abzufragen.
// @parm char * | pUserName | lParam enthält einen Zeichenkettenpuffer, der 
// groß genug sein muß, um einen vollen Pfadnamen zu halten (_MAX_PATH). In diesem
// Puffer wird der Name des aktuellen Nutzers abgelegt. 
// @rdesc Diese Message liefert den Wert von lParam, wenn kein Fehler aufgetreten 
// ist. Wenn kein aktives Projekt existiert oder im Fehlerfall liefert diese 
// Message NULL.
// @comm Der aktuelle Nutzername ist die Zeichenkette, die beim Öffnen des aktuellen
// Projektes <m DEX_PROJECTOPEN> als Identifikation im Feld Nutzername 
// angegeben wurde.<nl>Diese Message wird durch die Funktion 
// <f DEX_GetActiveUser> ausgelöst.
// @xref <m DEX_PROJECTOPEN>, <f DEX_GetActiveUser>
LRESULT ExtDirisWindow :: OnDexQueryActiveUser (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, strlen(DBO().DB().GetUserName())+1, true));

	strcpy ((char *)lParam, DBO().DB().GetUserName());
	return (LRESULT)lParam;
}

// DEX_QUERYROMODE: aktiven Schreib/LeseMode der GeoDB abfragen -----------------
// @msg DEX_QUERYROMODE | Diese Message wird an <tr> geschickt, um die Zugriffsrechte
// für das aktuelle Projekt abzufragen.
// @rdesc Diese Message liefert -1, wenn kein aktuelles Projekt existiert, ansonsten
// <t true> wenn das aktuelle Projekt schreibgeschützt geöffnet wurde 
// (<m DEX_PROJECTOPEN>) und <t false>, wenn das aktuelle Projekt mit Schreibrechten
// eröffnet worden ist.
// @comm Diese Message benötigt keine Parameter.<nl>Diese Message wird durch die 
// Funktion <f DEX_GetROMode> ausgelöst.
// @xref <m DEX_PROJECTOPEN>, <f DEX_GetROMode>
LRESULT ExtDirisWindow :: OnDexQueryROMode (LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(-1);

#if defined(WIN32)
IStorage *pIStg = NULL;

	if (DBO().DB().GetProjectStorage (&pIStg)) {
		pIStg -> Release();
		return false;		// StorageProjekte sind NIE R/O
	}
#endif // WIN32

return (LRESULT)(DBO().DB().GetROMode());
}
		
// DEX_QUERYGEODBVERSION: Abfrage der GeoDBVersion ----------------------------
// @msg DEX_QUERYGEODBVERSION | Diese Message wird an <tr> geschickt, um die 
// Versionsnummer des aktuellen Projektes zu erfragen.
// @rdesc Der Rückgabewert enthält die Versionsnummer des aktuellen Projektes. Wenn
// kein aktuelles Projekt existiert, dann liefert diese Message 0;
// @comm Diese Message benötigt keine Parameter.<nl>Sie wird durch die 
// Funktion <f DEX_GetDBVersion> ausgelöst.
// @xref <f DEX_GetDBVersion>
LRESULT ExtDirisWindow :: OnDexQueryGeoDBVersion (LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(0);
		
	return (LRESULT)DBO().DB().GetDBVersion();
}


// DEX_QUERYACTIVEPBD: aktuelle PBD abfragen ----------------------------------
LRESULT ExtDirisWindow :: OnQueryActivePBD (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);
		
CActDB ActDB (DBO().PbdDB());

	if (!ActDB) return LRESULT(NULL);	// keine Pbd gegeben

	TX_ASSERT(TIsValidAddress((void *)lParam, strlen(DBO().PbdDB().GetDBName())+1, true));

	strcpy ((char *)lParam, DBO().PbdDB().GetDBName());
	return (LRESULT)lParam;
}

// DEX_MODIFYPBDNAME: neuen PBDNamen für aktuelle GeoDB setzen ----------------
LRESULT ExtDirisWindow :: OnModifyPBDName (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

	return DBO().InitPbd ((char *)lParam, true), true;
}

// DEX_QUERYMAINININAME: zentralen INI-DateiNamen liefern ---------------------
// @msg DEX_QUERYMAINININAME | Diese Message wird an <tr> geschickt, um den 
// Namen der zentralen Initialisierungsdatei abzufragen.
// @parm char * | pIniName | lParam enthält einen Zeichenkettenpuffer, der 
// groß genug sein muß, um einen vollen Dateinamen zu halten (_MAX_PATH Zeichen). 
// In diesem Puffer wird der Dateiname der Initialisierungsdatei abgelegt. 
// @rdesc Diese Message liefert den Wert von lParam, wenn kein Fehler aufgetreten 
// ist. Im Fehlerfall liefert diese Message NULL.
// @comm Diese Message wird durch die Funktion <f DEX_GetMainIniName> ausgelöst.
// @xref <f DEX_GetMainIniName>
LRESULT ExtDirisWindow :: OnQueryMainIniName (LPARAM lParam)
{
	TX_ASSERT(TIsValidAddress((void *)lParam, _MAX_PATH, true));

	return (LRESULT)RetrieveMainProFile ((char *)lParam);
}

// DEX_QUERYACTIVEOBJECT: das aktivierte Objekt eines ORFensters --------------
LRESULT ExtDirisWindow :: OnQueryActiveObject (LPARAM lParam)
{
	TX_ASSERT(NULL == (HWND)lParam ||
		  (IsWindow((HWND)lParam) && NULL != GetORWindow((HWND)lParam)));

	return GetSelectedObject((HWND)lParam);
}

// DEX_QUERYACTIVEORWINDOW: HWND des derzeit aktiven ORFensters liefern -------
LRESULT ExtDirisWindow :: OnQueryActiveORWindow (LPARAM)
{
HWND hWnd = GetActiveORWindow();
	
	TX_ASSERT(IsWindow(hWnd));
	return (LRESULT)(void *)hWnd;
}

// DEX_QUERYCNTACTIVEOBJECTS: Anzahl der offenen ORFenster liefern (obsolete) -
LRESULT ExtDirisWindow :: OnQueryCountORWindows (LPARAM lParam)
{
	return (LRESULT)GetORCount();
}

// DEX_QUERYCNTRECHERCHEDOBJECTS: Anzahl der Recherchierten Objket liefern (obsolete)
LRESULT ExtDirisWindow :: OnQueryCountORObjects (LPARAM lParam)
{
	return (LRESULT)GetORObjCount();
}

// DEX_QUERYALLACTIVEOBJECTS: Alle aktivierten Objekte liefern (obsolete) -----
LRESULT ExtDirisWindow :: OnQueryAllActiveObjects (LPARAM lParam)
{	
	return (LRESULT)GetAllSelectedObjects((long *)lParam);
}

// DEX_QUERYACTIVESIGHT: aktuelle Sicht liefern -------------------------------
// @msg DEX_QUERYACTIVESIGHT | Diese Message wird an <tr> geschickt, um den 
// Namen der aktuellen Ansicht des aktuellen Projektes abzufragen.
// @parm char * | pViewName | lParam enthält einen Zeichenkettenpuffer, der 
// groß genug sein muß, um einen Ansichtnamen zu halten (41 Zeichen). In diesem
// Puffer wird der Name der aktuellen Ansicht abgelegt. 
// @rdesc Diese Message liefert den Wert von lParam, wenn kein Fehler aufgetreten 
// ist. Wenn kein aktives Projekt existiert, keine aktuelle Ansicht ausgewählt ist
// oder im Fehlerfall liefert diese Message NULL.
// @comm Eine Ansicht kann mit Hilfe der Message <m DEX_SELNEWSIGHT> ausgewählt werden.
// <nl>Diese Message wird durch die Funktion <f DEX_GetActiveSight> ausgelöst.
// @xref <m DEX_SELNEWSIGHT>, <f DEX_GetActiveSight>
LRESULT ExtDirisWindow :: OnQueryActiveView (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(NULL);
	
	if (DBO().GetActiveSightName ((char *)lParam))
		return (LRESULT)lParam;

return NULL;
}
		
// DEX_QUERYOBJMERKMAL:	ein bestimmtes Objektmerkmal liefern ------------------
LRESULT ExtDirisWindow :: OnQueryObjectFeature (LPARAM lParam)
{
	return OnQueryTextMerkmal (lParam);
}

// DEX_QUERYIDENTVISINFO: VisualisierungsInfo für Ident liefern ---------------
LRESULT ExtDirisWindow :: OnQueryIdentVisInfo (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
HANDLEVISINFO *pHVI = (HANDLEVISINFO *)lParam;
		
	TX_ASSERT_POINTER(pHVI, HANDLEVISINFO);

	if (!IsValidIdent(pHVI -> m_lIdent)) {
	// Ident nicht gegeben
		TX_ASSERT(IsValidONr(pHVI -> m_lONr));
		pHVI -> m_lIdent = DBO().RetrieveIdent (pHVI -> m_lONr);
	}

	if (NULL == pHVI -> m_pView) {	// aktuelle Sicht
		return (LRESULT)DBO().Idents().RetrieveVisInfo (
				pHVI -> m_lIdent, 
				pHVI -> m_iVTyp, *pHVI -> m_pVI
			);
	} else {
		TX_ASSERT(TIsValidString(pHVI -> m_pView));

	ErrInstall EI (WC_NOTFOUND);
	Sicht locSicht (DBO().DB(), pHVI -> m_pView);
			
		return locSicht.RetrieveVisInfo (
				pHVI -> m_lIdent,
				pHVI -> m_iVTyp, *pHVI -> m_pVI
			);
	}
}

// DEX_QUERYOBJCOLOR: ObjektFarbe liefern -------------------------------------
LRESULT ExtDirisWindow :: OnQueryObjectColor (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1);

	TX_ASSERT(IsValidONr((LONG)lParam));

Color rC = DBO().GetObjectColor ((LONG)lParam);

	return LRESULT((COLORREF &)rC);
}

// DEX_QUERYOBJSTATUS: Liefern des ObjektStatus -------------------------------
LRESULT ExtDirisWindow :: OnQueryObjectStatus (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(OS_Invalid);
		
	TX_ASSERT(IsValidONr((LONG)lParam));

	return (LRESULT)DBO().Shapes().RetrieveObjStatus ((long)lParam);
}

// DEX_QUERYOBJSTATISTIK: Liefern Info über Geometrie eines Objektes ----------
LRESULT ExtDirisWindow :: OnQueryObjectStatistics (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
OBJSTATISTIK *pOS = (OBJSTATISTIK *)lParam;

	TX_ASSERT(TIsValidAddress(pOS, sizeof(OBJSTATISTIK), true));
	TX_ASSERT(sizeof(OBJSTATISTIK) <= pOS -> dwSize);
	TX_ASSERT(IsValidONr(pOS -> lONr));
#endif // _DEBUG

	return (LRESULT)DBO().QueryObjStatistik ((OBJSTATISTIK *)lParam);
}

// DEX_QUERYOBJGEOMETRIE: Geometrie eines Objektes liefern --------------------
LRESULT ExtDirisWindow :: OnQueryObjectGeometry (LPARAM lParam)
{		
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
OBJGEOMETRIE *pOG = (OBJGEOMETRIE *)lParam;

	TX_ASSERT_POINTER(pOG, OBJCREATE);	// erster Teil der Struktur ist für alle gleich

	if (sizeof(OBJGEOMETRIE) == pOG -> dwSize)
		TX_ASSERT(TIsValidAddress(pOG, sizeof(OBJGEOMETRIE), true));
	else if (sizeof(TEXTGEOMETRIE) == pOG -> dwSize) {
	TEXTGEOMETRIE *pTG = (TEXTGEOMETRIE *)pOG;

		TX_ASSERT(TIsValidAddress(pTG, sizeof(TEXTGEOMETRIE), true));
		TX_ASSERT(OT_TEXT == pTG -> iObjTyp);
		TX_ASSERT(1L == pTG -> lCnt);
		if (pTG -> pText) {
			TX_ASSERT(0 < pTG -> iKCnt);
			TX_ASSERT(TIsValidAddress(pTG -> pText, pTG -> iKCnt, true));
		}
	}
	TX_ASSERT(IsValidONr(pOG -> lONr));

// Geometriefelder prüfen
	if (pOG -> iFlags & OGConverted) {
		TX_ASSERT(TIsValidAddress(pOG -> pdblX, sizeof(double)*(pOG -> lCnt), true));
		TX_ASSERT(TIsValidAddress(pOG -> pdblY, sizeof(double)*(pOG -> lCnt), true));
	} else {
		TX_ASSERT(TIsValidAddress(pOG -> pdblX, sizeof(long)*(pOG -> lCnt), true));
		TX_ASSERT(TIsValidAddress(pOG -> pdblY, sizeof(long)*(pOG -> lCnt), true));
	}
#endif // _DEBUG

	return (LRESULT)DBO().QueryObjGeometrie ((OBJGEOMETRIE *)lParam);
}

// DEX_MODIFYOBJGEOMETRIE:	neue Geometrie für eine Objekt schreiben ------
// @msg DEX_MODIFYOBJGEOMETRIE | Mit dieser Message an <tr> ist es möglich, Objekte
// zu erzeugen oder Objektgeometrien zu modifizieren.
// @parm OBJGEOMETRIE * | pObjGeometrie | lParam zeigt auf eine Struktur vom Typ
// <t OBJGEOMETRIE> bzw. der verwandten Strukturen <t OBJCREATE>, <t COPYGEOMETRIE>
// oder <t TEXTGEOMETRIE>. Je nach auszuführender Funktion muß die entsprechende
// Datenstruktur übergeben werden. Unterschieden werden die einzelnen Strukturen über 
// den ersten Strukturmember <e OBJGEOMETRIE.dwSize>.
// @rdesc Diese Message liefert die Objektnummer des neu erzeugten bzw. modifizierten
// Objektes und im Fehlerfall -1L.
// @comm Die durchzuführende Funktion wird durch die Datenstruktur und den 
// Strukturmember <e OBJGEOMETRIE.iFlags> bestimmt.
// @xref <f DEX_ModObjGeometrie>, <t OBJGEOMETRIE>, <t OBJCREATE>, <t COPYGEOMETRIE>,
// <t TEXTGEOMETRIE>
LRESULT ExtDirisWindow :: OnModObjectGeometry (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
OBJGEOMETRIE *pOG = (OBJGEOMETRIE *)lParam;

	TX_ASSERT_POINTER(pOG, OBJCREATE);	// erster Teil der Struktur ist für alle gleich

	if (sizeof(OBJGEOMETRIE) == pOG -> dwSize) {
	// normales Objekt wegschreiben (Punkt, Linie oder Fläche)
		TX_ASSERT_POINTER(pOG, OBJGEOMETRIE);
		TX_ASSERT(0 == (pOG -> iFlags & OGOverlay));

	// bei Modifizieren muß Objekt existieren
		if (pOG -> iFlags & OGModObject) 
			TX_ASSERT(IsValidONr(pOG -> lONr));

	// GeometrieFelder prüfen
		if (pOG -> iFlags & OGConverted) {
			TX_ASSERT(TIsValidAddress(pOG -> pdblX, sizeof(double)*(pOG -> lCnt), false));
			TX_ASSERT(TIsValidAddress(pOG -> pdblY, sizeof(double)*(pOG -> lCnt), false));
		} else {
			TX_ASSERT(TIsValidAddress(pOG -> pdblX, sizeof(long)*(pOG -> lCnt), false));
			TX_ASSERT(TIsValidAddress(pOG -> pdblY, sizeof(long)*(pOG -> lCnt), false));
		}
		if (pOG -> iObjTyp == OT_FLAECHE)	// Konturfeld
			TX_ASSERT(TIsValidAddress(pOG -> plCnt, sizeof(long)*(pOG -> iKCnt), false));
	} else if (sizeof(TEXTGEOMETRIE) == pOG -> dwSize) {
	// Textobjekt neu schreiben
	TEXTGEOMETRIE *pTG = (TEXTGEOMETRIE *)pOG;

		TX_ASSERT_POINTER(pTG, TEXTGEOMETRIE);
		TX_ASSERT(OT_TEXT == pTG -> iObjTyp);
		TX_ASSERT(0 == (pTG -> iFlags & OGOverlay));

	// bei Modifizieren muß Objekt existieren
		if (pOG -> iFlags & OGModObject) 
			TX_ASSERT(IsValidONr(pOG -> lONr));

	// Geometrie des Textes prüfen
		if (pTG -> pText) {
			TX_ASSERT(0 < pTG -> iKCnt);
			TX_ASSERT(TIsValidString(pTG -> pText));
		}
		if (pTG -> iFlags & OGConverted) {
			TX_ASSERT_POINTER(pTG -> pdblX, double);
			TX_ASSERT_POINTER(pTG -> pdblY, double);
		} else {
			TX_ASSERT_POINTER(pTG -> pdblX, long);
			TX_ASSERT_POINTER(pTG -> pdblY, long);
		}
	} else if (sizeof(OBJCREATE) == pOG -> dwSize) {
	// neues Objekt erzeugen, evtl. bestehendes vorher löschen
		TX_ASSERT_POINTER(pOG, OBJCREATE);
		TX_ASSERT(0L == pOG -> lONr || IsValidONr(pOG -> lONr));
	} else if (sizeof(COPYGEOMETRIE) == pOG -> dwSize) {
	COPYGEOMETRIE *pCG = (COPYGEOMETRIE *)pOG;

		TX_ASSERT(pCG -> iFlags & OGOverlay);	// nur bei Overlay möglich
		TX_ASSERT(IsValidONr(pCG -> lTargetONr));
	}
#endif // _DEBUG

	DBO().DB().SetDirty();
	if (DBO().ModObjGeometrie ((OBJGEOMETRIE *)lParam)) {
		TX_ASSERT(IsValidONr(pOG -> lONr));
		TX_ASSERT(EC_OKAY == TestObjekt(DBO().DB(), pOG -> lONr, g_iKonsFlags));
		return LRESULT(true);
	}

return LRESULT(false);
}

// DEX_QUERYKOBJECTRCODE: für KObjekt: RCode liefern --------------------------
LRESULT ExtDirisWindow :: OnQueryKObjectRCode (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
	TX_ASSERT(IsValidONr((long)lParam));
	return (LRESULT)DBO().Shapes().GetRCode (lParam);		
}

// DEX_QUERYACTSIGHTCONTAINER:	aktuellen Bildschirmausschnitt liefern --------
LRESULT ExtDirisWindow :: OnQueryActViewContainer (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));

	*(ObjContainer *)lParam = DBO().GetExtend();
	return LRESULT(true);
}

// DEX_SETACTSIGHTCONTAINER: aktuellen Bildschirmausschnitt setzen ------------
LRESULT ExtDirisWindow :: OnSetActViewContainer (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), false));

return SetActViewContainer (*(ObjContainer *)lParam);
}

// DEX_QUERYACTIVESELECTION: aktuelle Selektion liefern -----------------------
LRESULT ExtDirisWindow :: OnQueryActSelection (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));

return GetActViewContainer (*(ObjContainer *)lParam);
}

// DEX_ADDNEWIDENT: neuen Ident in die Verwaltung aufnehmen (intern) ----------
LRESULT ExtDirisWindow :: OnAddNewIdent (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
ADDNEWIDENT *pA = (ADDNEWIDENT *)lParam;

	TX_ASSERT_POINTER(pA, ADDNEWIDENT);
	TX_ASSERT(IsValidIdent(pA -> newIdent));

	DBO().DB().SetDirty();

return (LRESULT)DBO().Idents().AddNewIdent (
			pA -> newIdent, pA -> iFlags, pA -> iTyp);
}

// DEX_USEDIDENT: Testen, ob Ident in dieser GeoDB verwendet ist --------------
LRESULT ExtDirisWindow :: OnQueryIdentUsage (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(IsValidIdent((LONG)lParam));
	return (LRESULT)DBO().Idents().isUsed ((long)lParam);
}

// DEX_USEDMCODE: Testen, ob in dieser GeoDB MCode verwendet ist --------------
LRESULT ExtDirisWindow :: OnQueryMCodeUsage (LPARAM lParam)
{
	return LRESULT(false);		// not implemented yet
}

// DEX_USEDRCODE: Testen, ob in dieser GeoDB RCode verwendet ist --------------
LRESULT ExtDirisWindow :: OnQueryRCodeUsage (LPARAM lParam)
{
	return LRESULT(false);		// not implemented yet
}

// DEX_MODOBJIDENT: Ident eines Objektes ändern -------------------------------
LRESULT ExtDirisWindow :: OnModObjectIdent (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
MODOBJIDENT *pMOI = (MODOBJIDENT *)lParam;

	TX_ASSERT_POINTER(pMOI, MODOBJIDENT);
	TX_ASSERT(3*sizeof(long) == pMOI -> dwSize || sizeof(MODOBJIDENT) == pMOI -> dwSize);
	TX_ASSERT(IsValidONr(pMOI -> lONr));
	TX_ASSERT(IsValidIdent(pMOI -> lNewIdent));

short iMode = pMOI -> dwSize > 3*sizeof(long) ? pMOI -> iMode : 0;

	DBO().DB().SetDirty();

return (LRESULT)DBO().ModIdent (pMOI -> lONr, pMOI -> lNewIdent, -1, iMode);
}

// DEX_MODIFYIDENTVISINFO: ObjektVisInfo modifizieren ----------------------------
LRESULT ExtDirisWindow :: OnModObjectVisInfo (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
HANDLEVISINFO *pHVI = (HANDLEVISINFO *)lParam;
		
	TX_ASSERT_POINTER(pHVI, HANDLEVISINFO);

	if (!IsValidIdent(pHVI -> m_lIdent)) {
	// Ident nicht gegeben
		TX_ASSERT(IsValidONr(pHVI -> m_lONr));
		pHVI -> m_lIdent = DBO().RetrieveIdent (pHVI -> m_lONr);
	}

	TX_ASSERT(IsValidIdent(pHVI -> m_lIdent));

	DBO().DB().SetDirty();
	if (VT_Default != pHVI -> m_iVTyp) {
		return (LRESULT)DBO().ChangeVisInfo (
				pHVI -> m_lIdent, pHVI -> m_iVTyp, 
				*pHVI -> m_pVI, pHVI -> m_pView, 0,
				pHVI -> m_fFlags & DF_ForceImport
			);
	} else {
		return (LRESULT)DBO().ChangeVisInfo (
				pHVI -> m_lIdent, pHVI -> m_iVTyp, 
				*pHVI -> m_pVI, pHVI -> m_pView,
				((DVISINFO &)pHVI -> m_pVI).m_iDefTypes,
				pHVI -> m_fFlags & DF_ForceImport
			);
	}
}
		
// DEX_MODIFYVISINFODIALOG: Dialoge zur VisInfoEinstellung -----------------------
LRESULT ExtDirisWindow :: OnVisInfoDialog (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
	return LRESULT(ChangeVisInfoExt ((HANDLEVISINFO *)lParam));
}
		
// DEX_MERGEKOBJECTS: KomplexObjekte zusammenfassen ---------------------------
LRESULT ExtDirisWindow :: OnMergeKObjects (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
MERGEKOBJECT *pM = (MERGEKOBJECT *)lParam;

	DBO().DB().SetDirty();

return (LRESULT)DBO().Shapes().MergeKObjects (
			pM -> mObj1, pM -> mObj2, 
			pM -> mIdent, pM -> mRCode, 
			pM -> mMerge
		);
}

// DEX_DELETEOBJFROMKOBJECT: Objekt aus KObjekt herauslöschen ------------------
LRESULT ExtDirisWindow :: OnDelObjectFromKObject (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
DELETEKOBJECT *pK = (DELETEKOBJECT *)lParam;

	DBO().DB().SetDirty();

return (LRESULT)DBO().Shapes().DeleteONFromKObject (
			pK -> doKObj, pK -> doObj);
}

// DEX_FLUSHALLMODIFICATIONS: aktuellen Zustand der GeoDB speichern --------------
LRESULT ExtDirisWindow :: OnFlushModifications (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	return SaveGeoDB();
}

// DEX_REBUILDVIEW: Sicht neu generieren -------------------------------------
LRESULT ExtDirisWindow :: OnRebuildView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
// Sicht nur neu generieren, wenn derzeit nicht gezeichnet wird
	if (DBO().isDrawing()) {
		GCancelFlag |= GCFAbort;	// Zeichnen abbrechen
//		DEX_PostRebuildSight();		// noch mal versuchen
		return LRESULT(false);
	}

ObjContainer OC = DBO().GetExtend();
LRESULT lResult = (LRESULT)DBO().ProcessMenuEvent (NULL, true);

	if (lResult) {
		LegendToRepaint = true;
		DEX_SetActiveSightContainer(OC);
		RePaint();
		if (OverViewCFlag && pOverView) pOverView -> RePaint();
	}

return lResult;
}

// DEX_REPAINTALL: gesamten Bildschirm neu zeichnen ---------------------------
LRESULT ExtDirisWindow :: OnRePaintAll (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	LegendToRepaint = true;
#if defined(WIN32)
	m_pView -> RePaint();
#else
	RePaint();
#endif // WIN32
	if (OverViewCFlag && pOverView) pOverView -> RePaint();

return true;
}

// DEX_REPAINTRECT: RechtEck neu zeichnen -------------------------------------
LRESULT ExtDirisWindow :: OnRePaintRect (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT_POINTER((void *)lParam, Rectangle);

	LegendToRepaint = true;
#if defined(WIN32)
	m_pView -> RePaintRect (*(Rectangle *)lParam);
#else
	RePaintRect (*(Rectangle *)lParam);
#endif // WIN32

return true;
}

// DEX_SELNEWSIGHT: neue Sicht auswählen --------------------------------------
LRESULT ExtDirisWindow :: OnSelectView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));
			
// Sicht soll umgeschaltet werden
	if (DEXN_SightToSelect ((char *)lParam))
		return false;	// jemand hat was dagegen

// Sicht umschalten
bool fResult = DBO().ActivateSight ((char *)lParam);

// Identifikatorbaum von nicht mehr benötigten temporären Idents bereinigen
	DBO().RemoveTempIdents();
	CIdentifikator :: ReleaseIgnoreTree();	// statische Funktion
	if (fResult)
		DEXN_SightSelected ((char *)lParam);

return fResult;
}

// DEX_DELETEVIEW: Sicht löschen ---------------------------------------------
LRESULT ExtDirisWindow :: OnDeleteView (LPARAM lParam)
{		
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
	TX_ASSERT(TIsValidString((char *)lParam));

	DBO().DB().SetDirty();

return LRESULT(DBO().DeleteView (MainMenu(), (char *)lParam));
}
		
// DEX_CREATEOBJEKTINFO: ObjektRechercheFenster erzeugen und anzeigen ---------
LRESULT ExtDirisWindow :: OnCreateORWindow (LPARAM lParam)
{	
#if defined(_DEBUG) && defined(WIN32)
CREATEOBJEKTINFO *pCOI = (CREATEOBJEKTINFO *)lParam;

	TX_ASSERT_POINTER(pCOI, DWORD);
	if (sizeof(CREATEOBJEKTINFO) == pCOI -> dwSize)
		TX_ASSERT_POINTER(pCOI, CREATEOBJEKTINFO);
	else if (sizeof(CREATEOBJEKTINFOEX) == pCOI -> dwSize) {
	CREATEOBJEKTINFOEX *pCOIEx = (CREATEOBJEKTINFOEX *)pCOI;

		TX_ASSERT_POINTER(pCOIEx, CREATEOBJEKTINFOEX);
		TX_ASSERT(NULL == pCOIEx -> m_hWnd || IsWindow(pCOIEx -> m_hWnd));
		TX_ASSERT(NULL == pCOIEx -> m_pCmpProc || TIsValidAddress(pCOIEx -> m_pCmpProc, 1, false));
	} else {
		TX_ASSERT(sizeof(CREATEOBJEKTINFOEX2) == pCOI -> dwSize);

	CREATEOBJEKTINFOEX2 *pCOIEx2 = (CREATEOBJEKTINFOEX2 *)pCOI;

	// entweder gleich NULL oder ein gültiges Interface
		TX_ASSERT(NULL == pCOIEx2 -> m_pIObjProp || 
			  TIsValidIUnknown(pCOIEx2 -> m_pIObjProp));
	}

	TX_ASSERT(TIsValidString(pCOI -> lpCaption));

// entweder keine Objekte oder gültiges Feld
//	if (NULL != pCOI -> plObjs && 0 != pCOI -> iNumObjs)
		TX_ASSERT(TIsValidAddress(pCOI -> plObjs, pCOI -> iNumObjs*sizeof(long), false));
#endif // _DEBUG

HWND hWnd = CreateObjektInfo ((CREATEOBJEKTINFO *)lParam);

	TX_ASSERT(IsWindow(hWnd));

	return (LRESULT)(void *)hWnd;
}

// DEX_READHEADER: GeoDB-HeaderEintrag lesen ----------------------------------
LRESULT ExtDirisWindow :: OnReadHeader (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
GEODBHDRENTRY *pHE = (GEODBHDRENTRY *)lParam;

#if defined(_DEBUG)
	TX_ASSERT(TIsValidAddress(pHE, sizeof(GEODBHDRENTRY), true));	// writeable!
	if (sizeof(GEODBHDRENTRY) != pHE -> dwSize) {
		TX_ASSERT(sizeof(GEODBHDRENTRYEX) == pHE -> dwSize);
		TX_ASSERT(0 == (((GEODBHDRENTRYEX *)pHE) -> dwFlags & ~HEADER_SYSTEMRO));
	}
	TX_ASSERT(TIsValidString(pHE -> hdrKey, sizeof(pHE -> hdrKey)));
	TX_ASSERT(TIsValidAddress(pHE -> lphdrText, pHE -> hdrTextLen, true));
#endif // _DEBUG

HeaderEntry HE (DBO().DB(), pHE -> hdrKey);

	if (HE.Status() == HE_UNMODIFIED) {
		strncpy (pHE -> lphdrText, HE.EntryText(), pHE -> hdrTextLen);
		pHE -> lphdrText[pHE -> hdrTextLen -1] = '\0';
		if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize) 
			((GEODBHDRENTRYEX *)pHE) -> dwFlags = HE.Flags();
		return (LRESULT)EC_OKAY;
	} else {
		*pHE -> lphdrText = '\0';
		return (LRESULT)WC_NOTFOUND;
	}
}

// DEX_MODIFYHEADER: GeoDB-HeaderEintrag modifizieren/anlegen -----------------
LRESULT ExtDirisWindow :: OnModifyHeader (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
GEODBHDRENTRY *pHE = (GEODBHDRENTRY *)lParam;

#if defined(WIN32)
	TX_ASSERT_POINTER(pHE, GEODBHDRENTRY);
	if (sizeof(GEODBHDRENTRY) != pHE -> dwSize) {
		TX_ASSERT(sizeof(GEODBHDRENTRYEX) == pHE -> dwSize);
		TX_ASSERT(0 == (((GEODBHDRENTRYEX *)pHE) -> dwFlags & ~HEADER_SYSTEMRO));
	}
	TX_ASSERT(TIsValidString(pHE -> hdrKey, sizeof(pHE -> hdrKey)));
	TX_ASSERT(TIsValidString(pHE -> lphdrText));
#endif // _DEBUG

HeaderEntry HE (DBO().DB(), pHE -> hdrKey, pHE -> lphdrText);

	if (sizeof(GEODBHDRENTRYEX) == pHE -> dwSize)
		HE.Flags() = ((GEODBHDRENTRYEX *)pHE) -> dwFlags;

return (LRESULT)HE.WriteBack();
}

// DEX_DELETEHEADER: GeoDB-HeaderEintrag löschen ------------------------------
LRESULT ExtDirisWindow :: OnDeleteHeader (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
GEODBHDRENTRY *pHE = (GEODBHDRENTRY *)lParam;

	TX_ASSERT_POINTER(pHE, GEODBHDRENTRY);
	TX_ASSERT(sizeof(GEODBHDRENTRY) == pHE -> dwSize);
	TX_ASSERT(TIsValidString(pHE -> hdrKey, sizeof(pHE -> hdrKey)));
#endif // _DEBUG

ErrInstall EI (WC_NOTFOUND);
CActDB ActDB (DBO().DB());
		
	DBO().DB().SetDirty();

// Key sauber mit Leerzeichen auffüllen
char cbKey[HDRKEYLENGTH+1];

	memset (cbKey, ' ', HDRKEYLENGTH+1);
	strncpy (cbKey, ((GEODBHDRENTRY *)lParam) -> hdrKey, HDRKEYLENGTH);

short iLen = min (strlen(((GEODBHDRENTRY *)lParam) -> hdrKey), HDRKEYLENGTH);

	memset (&cbKey[iLen], ' ', HDRKEYLENGTH-iLen);
	cbKey[HDRKEYLENGTH] = '\0';

	return (LRESULT)delhd_ ((long *)cbKey);
}

// DEX_ENUMHEADER: GeoDB-HeaderEinträge enumerieren ---------------------------
LRESULT ExtDirisWindow :: OnEnumHeader (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEY *pENK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pENK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pENK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());
		
	return LRESULT(EnumHdrData (pENK -> eFcn, pENK -> ePtr));
}

// DEX_GETUNIQUEICODE: Unique Identifikator generieren ------------------------
LRESULT ExtDirisWindow :: OnGetUniqueICode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1);
		
	return LRESULT(DBO().DB().GetUniqueICode());
}

// DEX_GETUNIQUEMCODE: Unique MCode generieren --------------------------------
LRESULT ExtDirisWindow :: OnGetUniqueMCode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1);
		
	return LRESULT(DBO().DB().GetUniqueMCode(lParam ? true : false));
}

// DEX_GETUNIQUERCODE: Unique RCode generieren --------------------------------
LRESULT ExtDirisWindow :: OnGetUniqueRCode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1);
		
	return LRESULT(DBO().DB().GetUniqueRCode());
}

// DEX_GETUNIQUETEMPON: Unique ObjektNummer (temporäres Objekt) generieren ----
LRESULT ExtDirisWindow :: OnGetUniqueTempONr (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(-1);
		
	return LRESULT(DBO().DB().GetUniqueTempONr());
}

// DEX_QUERYACTSCALING: aktuelle Bildschirmvergrößerung liefern ---------------
LRESULT ExtDirisWindow :: OnQueryActScaling (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(double), true));

	*(double *)lParam = DBO().M();

return true; 
}
		
// DEX_QUERYACTMASSTAB: aktuellen Maßstab liefern -----------------------------
LRESULT ExtDirisWindow :: OnQueryActMasstab (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(double), true));

double MF[2];

#if defined(WIN32)
	DBO().EvalMasstab (m_pView, MF);
#else
	DBO().EvalMasstab (this, MF);
#endif // WIN32

	*(double *)lParam = MF[0] == 1.0 ? MF[1] : MF[0];

return true;
}

// DEX_CHANGEACTIVECOLOR: MarkierungsFarbe ändern -----------------------------
LRESULT ExtDirisWindow :: OnModActiveColor (LPARAM lParam)
{	
#if defined(_DEBUG)
CHANGEACTIVECOLOR *pCAC = (CHANGEACTIVECOLOR *)lParam;

	TX_ASSERT_POINTER(pCAC, CHANGEACTIVECOLOR);
	TX_ASSERT(sizeof(CHANGEACTIVECOLOR) == pCAC -> dwSize);
	TX_ASSERT(IsWindow(pCAC -> hWnd) && NULL != GetORWindow(pCAC -> hWnd));
	TX_ASSERT(IsValidONr(pCAC -> lONr));
#endif // _DEBUG

	return LRESULT(ChangeActiveColor ((CHANGEACTIVECOLOR *)lParam));
}
		

// Enumerationsfunktionen -----------------------------------------------------
// DEX_ENUMALLSIGHTS: alle Sichten liefern ---------------------------------------
LRESULT ExtDirisWindow :: OnEnumViews (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

	return (LRESULT)DBO().EnumSights (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMSIGHTOBJECTS: alle (Einzel-)Objekte einer Sicht --------------------
LRESULT ExtDirisWindow :: OnEnumViewObjects (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEY *pK = (ENUMTEXTKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(TIsValidString(pK -> eKey));

Sicht locSicht (DBO().DB(), pK -> eKey);
		
	return (LRESULT)locSicht.EnumObjects (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALE: alle Merkmale eines Objektes enumerieren -----------------
// @msg DEX_ENUMMERKMALE | Mit dieser Message an <tr> ist es möglich alle 
// Objektmerkmale eines vorgegebenen Objektes zu enumerieren.
// @parm ENUMLONGKEY * | pEnumLongKey | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEY>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumObjektMerkmale> 
// ausgelöst.<nl>Durch diese Message werden lediglich die Merkmale enumeriert, 
// die in der Beschreibungs-Datenbasis als Objektmerkmale registriert sind und keine 
// Systemmerkmale sind. Werden alle Merkmale benötigt, so muß die Message
// <m DEX_ENUMMERKMALEEX> eingesetzt werden.<par>Das Feld <e ENUMLONGKEY.eKey> muß
// vor dem Aufruf der Message mit der Objektnummer des zu behandelnden Objektes 
// belegt werden.
// @xref <f DEX_EnumObjektMerkmale>, <m DEX_ENUMMERKMALEEX>, <t ENUMLONGKEY>
LRESULT ExtDirisWindow :: OnEnumObjectFeatures (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidONr(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey, OBL);

	return (LRESULT)ML.EnumMerkmale (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALEIDENT: alle Merkmale eines Identifikators enumerieren ------
// @msg DEX_ENUMMERKMALEIDENT | Mit dieser Message an <tr> ist es möglich alle 
// Identifikatormerkmale eines vorgegebenen Identifikators zu enumerieren.
// @parm ENUMLONGKEY * | pEnumLongKey | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEY>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumIdentMerkmale> 
// ausgelöst.<nl>Durch diese Message werden lediglich die Merkmale enumeriert, die in der 
// Beschreibungs-Datenbasis als Objektmerkmale registriert sind und keine 
// Systemmerkmale sind. Werden alle Merkmale benötigt, so muß die Message
// <m DEX_ENUMMERKMALEIDENTEX> eingesetzt werden.<par>Das Feld <e ENUMLONGKEY.eKey> muß
// vor dem Aufruf der Message mit dem Identifikator-Code des zu behandelnden 
// Identifikators belegt werden.
// @xref <f DEX_EnumIdentMerkmale>, <m DEX_ENUMMERKMALEIDENTEX>, <t ENUMLONGKEY>
LRESULT ExtDirisWindow :: OnEnumIdentFeatures (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey, IDL);

	return (LRESULT)ML.EnumMerkmale (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALESICHT: alle Merkmale einer Sicht enumerieren ---------------
// @msg DEX_ENUMMERKMALESICHT | Mit dieser Message an <tr> ist es möglich alle 
// Sichtmerkmale einer vorgegebenen Ansicht zu enumerieren.
// @parm ENUMTEXTKEY * | pEnumTextKey | lParam zeigt auf eine Struktur vom Typ
// <t ENUMTEXTKEY>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumSichtMerkmale> 
// ausgelöst.<nl>Durch diese Message werden lediglich die Merkmale enumeriert, 
// die in der Beschreibungs-Datenbasis als Objektmerkmale registriert sind und keine 
// Systemmerkmale sind. Werden alle Merkmale benötigt, so muß die Message
// <m DEX_ENUMMERKMALESICHTEX> eingesetzt werden.<par>Das Feld <e ENUMTEXTKEY.eKey> muß
// vor dem Aufruf der Message mit dem Namen der zu behandelnden Ansicht 
// belegt werden.
// @xref <f DEX_EnumSichtMerkmale>, <m DEX_ENUMMERKMALESICHTEX>, <t ENUMTEXTKEY>
LRESULT ExtDirisWindow :: OnEnumViewFeatures (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEY *pK = (ENUMTEXTKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(TIsValidString(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey);

	return (LRESULT)ML.EnumMerkmale (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALEEX: Alle Merkmale eines Objektes enumerieren -----------------
// @msg DEX_ENUMMERKMALEEX | Mit dieser Message an <tr> ist es möglich alle Merkmale
// eines Objektes zu enumerieren.
// @parm ENUMLONGKEYEX * | pEnumLongKeyEx | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEYEX>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumObjektMerkmaleEx> 
// ausgelöst.<nl>Im Unterschied zur Message <m DEX_ENUMMERKMALE> ist es möglich 
// alle Merkmale zu enumerieren, die das vorgegebene Objekt besitzt.<par>Das 
// Feld <e ENUMLONGKEYEX.eKey> muß vor dem Aufruf der Message mit der Objektnummer 
// des zu behandelnden Objektes belegt werden.<par>Das 
// Feld <e ENUMLONGKEYEX.eData> der Struktur <t ENUMLONGKEYEX> kann für diese Message einen 
// der folgenden Werte oder deren Kombination annehmen:
// @flag MPSystemFeatures | Es sollen zusätzliche alle Merkmale enumeriert werden,
// die in der Beschreibungs-Datenbasis als Systemmerkmale gekennzeichnet sind.
// @flag MPAllFeatures | Es sollen alle Merkmale des vorgegebenen Objektes enumeriert
// werden, selbst, unabhängig davon, ob diese in der Beschreibungs-Datenbasis 
// als Objektmerkmale definiert sind oder nicht.
// @comm Der an die zu rufende Funktion (<f ENUMLONGKEYEXPROC>) übergebene 2. Parameter
// <p dwData> kann folgende Werte oder eine Kombination dieser annehmen:
// @flag MPSystemFeatures | Dieser Merkmalscode ist als Systemmerkmal registriert.
// @flag MPObjectFeature | Dieser Merkmalscode ist als Objektmerkmalscode registriert.
// @flag MPViewFeature | Dieser Merkmalscode ist als Identifikatormerkmalscode registriert.
// @flag MPIdentFeature | Dieser Merkmalscode ist als Sichtmerkmalscode registriert.
// @xref <f DEX_EnumObjektMerkmaleEx>, <m DEX_ENUMMERKMALE>, <t ENUMLONGKEYEX>
LRESULT ExtDirisWindow :: OnEnumObjectFeaturesEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEYEX *pK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidONr(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey, OBL, 
		  bool(pK -> eData & MPSystemFeatures), 
		  bool(pK -> eData & MPAllFeatures));

	return (LRESULT)ML.EnumMerkmaleEx (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALEIDENTEX: alle Merkmale eines Identifikators enumerieren ------
// @msg DEX_ENUMMERKMALEIDENTEX | Mit dieser Message an <tr> ist es möglich alle Merkmale
// eines Identifikators zu enumerieren.
// @parm ENUMLONGKEYEX * | pEnumLongKeyEx | lParam zeigt auf eine Struktur vom Typ
// <t ENUMLONGKEYEX>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumIdentMerkmaleEx> 
// ausgelöst.<nl>Im Unterschied zur Message <m DEX_ENUMMERKMALEIDENT> ist es möglich 
// alle Merkmale zu enumerieren, die der vorgegebene Identifikator besitzt.<par>Das 
// Feld <e ENUMLONGKEYEX.eKey> muß vor dem Aufruf der Message mit dem 
// Identifikator-Code des zu behandelnden Objektes belegt werden.<par>Das 
// Feld <e ENUMLONGKEYEX.eData> der Struktur <t ENUMLONGKEYEX> kann für diese Message einen der 
// folgenden Werte oder deren Kombination annehmen:
// @flag MPSystemFeatures | Es sollen zusätzliche alle Merkmale enumeriert werden,
// die in der Beschreibungs-Datenbasis als Systemmerkmale gekennzeichnet sind.
// @flag MPAllFeatures | Es sollen alle Merkmale des vorgegebenen Identifikators
// enumeriert werden, selbst, unabhängig davon, ob diese in der 
// Beschreibungs-Datenbasis als Identifikatormerkmale definiert sind 
// oder nicht.
// @comm Der an die zu rufende Funktion (<f ENUMLONGKEYEXPROC>) übergebene 2. Parameter
// <p dwData> kann folgende Werte oder eine Kombination dieser annehmen:
// @flag MPSystemFeatures | Dieser Merkmalscode ist als Systemmerkmal registriert.
// @flag MPObjectFeature | Dieser Merkmalscode ist als Objektmerkmalscode registriert.
// @flag MPViewFeature | Dieser Merkmalscode ist als Identifikatormerkmalscode registriert.
// @flag MPIdentFeature | Dieser Merkmalscode ist als Sichtmerkmalscode registriert.
// @xref <f DEX_EnumIdentMerkmaleEx>, <m DEX_ENUMMERKMALEIDENT>, <t ENUMLONGKEYEX>
LRESULT ExtDirisWindow :: OnEnumIdentFeaturesEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEYEX *pK = (ENUMLONGKEYEX *)lParam;


	TX_ASSERT_POINTER(pK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey, IDL,
		  bool(pK -> eData & MPSystemFeatures), 
		  bool(pK -> eData & MPAllFeatures));

	return (LRESULT)ML.EnumMerkmaleEx (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMMERKMALESICHTEX: alle Merkmale einer Sicht enumerieren ---------------
// @msg DEX_ENUMMERKMALESICHTEX | Mit dieser Message an <tr> ist es möglich alle Merkmale
// einer Ansicht zu enumerieren.
// @parm ENUMTEXTKEYEX * | pEnumTextKeyEx | lParam zeigt auf eine Struktur vom Typ
// <t ENUMTEXTKEYEX>.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wird die Enumeration durch die Enumerationsfunktion 
// abgebrochen (indem diese Funktion <t false> an <tr> liefert, so ist der 
// Rückgabewert der Message ebenfalls <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_EnumSichtMerkmaleEx> 
// ausgelöst.<nl>Im Unterschied zur Message <m DEX_ENUMMERKMALESICHT> ist es möglich 
// alle Merkmale zu enumerieren, die der vorgegebene Identifikator besitzt.<par>Das 
// Feld <e ENUMTEXTKEYEX.eKey> muß vor dem Aufruf der Message mit dem Namen der 
// zu behandelnden Ansicht belegt werden.<par>Das 
// Feld <e ENUMTEXTKEYEX.eData> der Struktur <t ENUMTEXTKEYEX> kann für diese Message einen der 
// folgenden Werte oder deren Kombination annehmen:
// @flag MPSystemFeatures | Es sollen zusätzliche alle Merkmale enumeriert werden,
// die in der Beschreibungs-Datenbasis als Systemmerkmale gekennzeichnet sind.
// @flag MPAllFeatures | Es sollen alle Merkmale der vorgegebenen Sicht
// enumeriert werden, selbst, unabhängig davon, ob diese in der 
// Beschreibungs-Datenbasis als Sichtmerkmale definiert sind oder nicht.
// @comm Der an die zu rufende Funktion (<f ENUMTEXTKEYEXPROC>) übergebene 2. Parameter
// <p dwData> kann folgende Werte oder eine Kombination dieser annehmen:
// @flag MPSystemFeatures | Dieser Merkmalscode ist als Systemmerkmal registriert.
// @flag MPObjectFeature | Dieser Merkmalscode ist als Objektmerkmalscode registriert.
// @flag MPViewFeature | Dieser Merkmalscode ist als Identifikatormerkmalscode registriert.
// @flag MPIdentFeature | Dieser Merkmalscode ist als Sichtmerkmalscode registriert.
// @xref <f DEX_EnumSichtMerkmaleEx>, <m DEX_ENUMMERKMALESICHT>, <t ENUMTEXTKEYEX>
LRESULT ExtDirisWindow :: OnEnumViewFeaturesEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMTEXTKEYEX *pK = (ENUMTEXTKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMTEXTKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(TIsValidString(pK -> eKey));

MerkmalsListe ML (&DBO().PbdDB(), pK -> eKey,
		  bool(pK -> eData & MPSystemFeatures), 
		  bool(pK -> eData & MPAllFeatures));

	return (LRESULT)ML.EnumMerkmaleEx (pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMALLMCODES: alle MCodes der GeoDB enumerieren -----------------------
extern ErrCode FillMerkmale (MerkmalsListe &);

LRESULT ExtDirisWindow :: OnEnumFeatureCodes (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

MerkmalsListe ML;

	FillMerkmale (ML);

return (LRESULT)ML.EnumMerkmale ((ENUMNOKEYLONGPROC)pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMALLMCODESEX: alles MCodes der GeoDB enumerieren mit Optionen -------
LRESULT ExtDirisWindow :: OnEnumFeatureCodesEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEYEX *pK = (ENUMNOKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

MerkmalsListe ML (bool(pK -> eData & MPSystemFeatures), 
		  bool(pK -> eData & MPAllFeatures));

	FillMerkmale (ML);

return (LRESULT)ML.EnumMerkmaleEx ((ENUMNOKEYLONGEXPROC)pK -> eFcn, pK -> ePtr);
}

// DEX_ENUMSELECTEDOBJECTS: alle recherchierten Objekte enumerieren -----------
LRESULT ExtDirisWindow :: OnEnumSelObjects (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
// entweder alle ORFenster (eKey == NULL oder gültiges ORFenster
	TX_ASSERT(NULL == pK -> eKey || 
	         (IsWindow((HWND)pK -> eKey) && NULL != GetORWindow((HWND)pK -> eKey)));

	return (LRESULT)EnumSelectedObjects (
			(ENUMNOKEYLONGPROC)pK -> eFcn, pK -> ePtr, 
			(HWND)pK -> eKey
		);
}

// DEX_RECHERCHEDOBJECTS: alle Objekte in ORFenstern enumerieren --------------
LRESULT ExtDirisWindow :: OnEnumAllORObjects (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
// entweder alle ORFenster (eKey == NULL oder gültiges ORFenster
	TX_ASSERT(NULL != pK -> eKey || 
	         (IsWindow((HWND)pK -> eKey) && NULL != GetORWindow((HWND)pK -> eKey)));

	return (LRESULT)EnumAllObjects (
		(ENUMNOKEYLONGPROC)pK -> eFcn, pK -> ePtr,
		(HWND)pK -> eKey);
}

// DEX_ENUMKOMPLOBJECTS: alle Objekte eines KomplexObjektes enumerieren -------
LRESULT ExtDirisWindow :: OnEnumKObjectMember (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));
	TX_ASSERT(IsValidONr(pK -> eKey));

	return (LRESULT)DBO().Shapes().EnumKObjects (
			pK -> eKey, pK -> eFcn, pK -> ePtr);
}

// DEX_PROJECTOPEN: Neues Projekt eröffnen ------------------------------------
LRESULT ExtDirisWindow :: OnOpenProject (LPARAM lParam)
{
TRIAS_OPEN *pTO = (TRIAS_OPEN *)lParam;

	TX_ASSERT_POINTER(pTO, TRIAS_OPEN);
	TX_ASSERT(sizeof(TRIAS_OPEN) == pTO -> dwSize);
	TX_ASSERT(TIsValidString(pTO -> lpProject));
	TX_ASSERT(NULL == pTO -> lpUser || TIsValidString(pTO -> lpUser));
	TX_ASSERT(NULL == pTO -> lpPassWord || TIsValidString(pTO -> lpPassWord));

	if (IsValidActiveView()) {	// evtl. Projekt schließen
		if (!(pTO -> iMode & OM_NotCloseOpen)) {
#if defined(WIN32)
			if (!doCloseDocument())
				return LRESULT(WC_RETURN);
#else
	ErrCode RC;
	
			DBASSERT (CloseDB());
			DELETE (DRO);
			UnLoadLocalExtensions();
#endif
		}	
	}

#if defined(WIN32)
LRESULT iResult = EC_OKAY;

		if (!CreateView (pTO -> lpProject, 
						 pTO -> lpUser, 
						 pTO -> lpPassWord,
						 pTO -> iMode))
		{
			return EC_NOOPEN;
		}
#else
LRESULT iResult = (LRESULT)OpenDB (pTO -> lpProject, 
				   pTO -> lpUser, 
				   pTO -> lpPassWord, 
				   pTO -> iMode);
	if (iResult != EC_OKAY)
		return iResult;		// Fehler
	
	InitProjectMenu();
	ReReadCaption();
	LoadLocalExtensions();
#endif // WIN32

return LRESULT(EC_OKAY);
}

// DEX_PROJECTCLOSE: derzeit geöffnetes Projekt abschließen -------------------
LRESULT ExtDirisWindow :: OnCloseProject (LPARAM lParam)
{
#if defined(WIN32)
	return LRESULT(doCloseDocument());
#else
	if (CloseDB (true, HPROJECT(lParam)) != EC_OKAY)
		return LRESULT(false);

	DELETE (DRO);
	UnLoadLocalExtensions();

return LRESULT(true);
#endif // WIN32
}

// DEX_SETATTRIBUTES: Zeichenattribute setzen (intern) ------------------------
LRESULT ExtDirisWindow :: OnSetAttributes (LPARAM lParam)
{	
	TX_ASSERT(IsValidONr((LONG)lParam));

	return (LRESULT)DBO().PresetAttributes ((long)lParam);
}

// DEX_RESETATTRIBUTES:	Zeichenattribute rücksetzen (intern) ------------------
LRESULT ExtDirisWindow :: OnResetAttributes (LPARAM lParam)
{
RESETATTRDATA *pRAD = (RESETATTRDATA *)lParam;

	TX_ASSERT_POINTER(pRAD, RESETATTRDATA);
	TX_ASSERT(IsValidONr(pRAD -> lONr));
	TX_ASSERT(VI_NotChanged == pRAD -> pVI || VI_OtherType == pRAD -> pVI ||
		  NULL == pRAD -> pVI || TIsValidAddress(pRAD -> pVI, sizeof(VisInfo), false));

	return (LRESULT)DBO().ResetAttributes (pRAD -> lONr, (VisInfo *)pRAD -> pVI);
}

// PBDVerwaltung --------------------------------------------------------------
// DEX_BEGINPBDTRANSACTION: Transaction für PBD beginnen ----------------------
LRESULT ExtDirisWindow :: OnBeginPBDTransaction (LPARAM)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().BeginTransaction();
}

// DEX_BREAKPBDTRANSACTION: Transaction für PBD abbrechen ---------------------
LRESULT ExtDirisWindow :: OnBreakPBDTransaction (LPARAM)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().BreakTransaction();
}

// DEX_ENDPBDTRANSACTION: Transaction für PBD erfolgreich abschließen ---------
LRESULT ExtDirisWindow :: OnEndPBDTransaction (LPARAM)
{		
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().EndTransaction();
}

// DEX_QUERYPBDVERSION: Version de PBD abfragen -------------------------------
LRESULT ExtDirisWindow :: OnQueryPBDVersion (LPARAM lParam)
{		
	if (!IsValidActiveView())
		return 0L;
		
CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return 0L;
	return (LRESULT)DBO().PbdDB().GetDBVersion();
}

// DEX_QUERYPBDDATA: PBD-Eintrag lesen ----------------------------------------
LRESULT ExtDirisWindow :: OnQueryPBDData (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
PBDDATA *pPD = (PBDDATA *)lParam;

	TX_ASSERT_POINTER(pPD, DWORD);
	if (sizeof(PBDMERKMAL) == pPD -> dwSize) {
		TX_ASSERT(TIsValidAddress(pPD, sizeof(PBDMERKMAL), true));
		TX_ASSERT(IsValidMCode(pPD -> pbdCode));
	} else if (sizeof(PBDRELATION) == pPD -> dwSize) {
		TX_ASSERT(TIsValidAddress(pPD, sizeof(PBDRELATION), true));
		TX_ASSERT(IsValidRCode(pPD -> pbdCode));
	} else {
		TX_ASSERT(sizeof(PBDDATA) == pPD -> dwSize);
		TX_ASSERT_POINTER(pPD, PBDDATA);
	}
	TX_ASSERT(NULL == pPD -> pbdKText || TIsValidAddress(pPD -> pbdKText, pPD -> pbdKTextLen, true));
	TX_ASSERT(NULL == pPD -> pbdLText || TIsValidAddress(pPD -> pbdLText, pPD -> pbdLTextLen, true));
#endif // _DEBUG

CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().GetPBDData ((PBDDATA *)lParam);
}

// DEX_MODPBDDATA: PBD-Eintrag schreiben/anlegen ------------------------------
LRESULT ExtDirisWindow :: OnModPBDData (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
PBDDATA *pPD = (PBDDATA *)lParam;

	TX_ASSERT_POINTER(pPD, DWORD);
	if (sizeof(PBDMERKMAL) == pPD -> dwSize) {
		TX_ASSERT_POINTER(pPD, PBDMERKMAL);
		TX_ASSERT(IsValidMCode(pPD -> pbdCode));
	} else if (sizeof(PBDRELATION) == pPD -> dwSize) {
		TX_ASSERT_POINTER(pPD, PBDRELATION);
		TX_ASSERT(IsValidRCode(pPD -> pbdCode));
	} else {
		TX_ASSERT(sizeof(PBDDATA) == pPD -> dwSize);
		TX_ASSERT_POINTER(pPD, PBDDATA);
	}
	TX_ASSERT(NULL == pPD -> pbdKText || TIsValidString(pPD -> pbdKText));
	TX_ASSERT(NULL == pPD -> pbdLText || TIsValidString(pPD -> pbdLText));
#endif // _DEBUG

CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().ModPBDData ((PBDDATA *)lParam);
}

// DEX_DELPBDDATA: Löschen eines PBD-Eintrages --------------------------------
LRESULT ExtDirisWindow :: OnDelPBDData (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
PBDDATA *pPD = (PBDDATA *)lParam;

	TX_ASSERT_POINTER(pPD, DWORD);
	if (sizeof(PBDMERKMAL) == pPD -> dwSize) {
		TX_ASSERT_POINTER(pPD, PBDMERKMAL);
		TX_ASSERT(IsValidMCode(pPD -> pbdCode));
	} else if (sizeof(PBDRELATION) == pPD -> dwSize) {
		TX_ASSERT_POINTER(pPD, PBDRELATION);
		TX_ASSERT(IsValidRCode(pPD -> pbdCode));
	} else {
		TX_ASSERT(sizeof(PBDDATA) == pPD -> dwSize);
		TX_ASSERT_POINTER(pPD, PBDDATA);
	}
#endif // _DEBUG

CActDB ActPBD (DBO().PbdDB());
		
	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().DelPBDData ((PBDDATA *)lParam);
}

// DEX_ENUMPBDDATA: Enumeration eines PBD-EintragTypes ------------------------
LRESULT ExtDirisWindow :: OnEnumPBDData (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEY *pK = (ENUMLONGKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActPBD (DBO().PbdDB());

	if(!ActPBD) return LRESULT(EC_NOOPEN);
	return (LRESULT)DBO().PbdDB().EnumPBDData (
			pK -> eKey, pK -> eFcn, pK -> ePtr);
}

// DEX_QUERYDRAWINGSTATUS: Abfrage, ob derzeit gezeichnet wird ----------------
LRESULT ExtDirisWindow :: OnQueryDrawingStatus (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	return LRESULT(DBO().isDrawing());
}

// DEX_QUERYISPRINTING: Abfrage, ob derzeit gedruckt wird ---------------------
LRESULT ExtDirisWindow :: OnQueryPrintingStatus (LPARAM lParam)
{
	return !PrintEFlag; 
}

// DEX_OCTODCEX: Konvertierung von ObjektKoordinaten in BildschirmKoordinaten -
LRESULT ExtDirisWindow :: OnOCtoDCEx (LPARAM lParam)
{
#if defined(_DEBUG)
COORDCONVERT *pCC = (COORDCONVERT *)lParam;

	TX_ASSERT_POINTER(pCC, COORDCONVERT);
	TX_ASSERT_POINTER(pCC -> lpPkt, Punkt);
	TX_ASSERT(TIsValidAddress(pCC -> lpPt, sizeof(Point), true));
#endif // _DEBUG

Point Pt = OCtoDC ( *(Punkt *) ((COORDCONVERT *)lParam) -> lpPkt );

	memcpy (((COORDCONVERT *)lParam) -> lpPt, &Pt, sizeof (Point));

return LRESULT(true);
}

// DEX_OCTODC: wie oben, jedoch mit kippen der Y-Koordinate -------------------
LRESULT ExtDirisWindow :: OnOCtoDC (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(false);

#if defined(_DEBUG)
COORDCONVERT *pCC = (COORDCONVERT *)lParam;

	TX_ASSERT_POINTER(pCC, COORDCONVERT);
	TX_ASSERT_POINTER(pCC -> lpPkt, Punkt);
	TX_ASSERT(TIsValidAddress(pCC -> lpPt, sizeof(Point), true));
#endif // _DEBUG

Point Pt = OCtoDC ( *(Punkt *) ((COORDCONVERT *)lParam) -> lpPkt );
#if defined(WIN32)
CoOrd dY = m_pView -> GetOutputHeight();
#else
Rectangle Rc = CanvasRect();
CoOrd dY = Rc.Top() - Rc.Bottom();
#endif // WIN32

	Pt.Y() = dY - Pt.Y();
	memcpy (((COORDCONVERT *)lParam) -> lpPt, &Pt, sizeof (Point));

return LRESULT(true);
}
		
// DEX_DCTOOCEX: Konvertierung von Bildschirmkoordinaten in Objektkoordianten -
LRESULT ExtDirisWindow :: OnDCtoOCEx (LPARAM lParam)
{
#if defined(_DEBUG)
COORDCONVERT *pCC = (COORDCONVERT *)lParam;

	TX_ASSERT_POINTER(pCC, COORDCONVERT);
	TX_ASSERT_POINTER(pCC -> lpPt, Point);
	TX_ASSERT(TIsValidAddress(pCC -> lpPkt, sizeof(Punkt), true));
#endif // _DEBUG

Point Pt = *(Point *) ((COORDCONVERT *)lParam) -> lpPt;

	*(Punkt *)(((COORDCONVERT *)lParam) -> lpPkt) = DCtoOC (Pt);

return LRESULT(true);
}

// DEX_DCTOOC: wie oben, jedoch mit kippen der Y-Koordinate -------------------
LRESULT ExtDirisWindow :: OnDCtoOC (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LPARAM(false);

#if defined(_DEBUG)
COORDCONVERT *pCC = (COORDCONVERT *)lParam;

	TX_ASSERT_POINTER(pCC, COORDCONVERT);
	TX_ASSERT_POINTER(pCC -> lpPt, Point);
	TX_ASSERT(TIsValidAddress(pCC -> lpPkt, sizeof(Punkt), true));
#endif // _DEBUG

Point Pt = *(Point *)((COORDCONVERT *)lParam) -> lpPt;
#if defined(WIN32)
CoOrd dY = m_pView -> GetOutputHeight();
#else
Rectangle Rc = CanvasRect();
CoOrd dY = Rc.Top() - Rc.Bottom();
#endif // WIN32

	Pt.Y() = dY - Pt.Y();
	*(Punkt *)(((COORDCONVERT *)lParam) -> lpPkt) = DCtoOC (Pt);

return LRESULT(true);
}
		
// DEX_QUERYACTIVETOOL: aktives Werkzeug abfragen -----------------------------
LRESULT ExtDirisWindow :: OnQueryActTool (LPARAM lParam)
{	
#if defined(OLD_TOOLBOX)
	return (LRESULT)(pToolBox ? pToolBox -> iActTool() : -1);
#else
	return g_iActTool;
#endif // OLD_TOOLBOX
}

// DEX_SETACTIVETOOL: aktives Werkzeug setzen ---------------------------------
LRESULT ExtDirisWindow :: OnSetActTool (LPARAM lParam)
{
#if defined(OLD_TOOLBOX)
	if (pToolBox) {
	short iOldTool = pToolBox -> iActTool();

		pToolBox -> SetTool ((short)lParam);
		return LRESULT(iOldTool);
	} 
return LRESULT(-1);
#else
int iActTool = g_iActTool;

	g_iActTool = (int)lParam;
	DEXN_ActiveToolChanged (g_iActTool);
	return iActTool;
#endif // OLD_TOOLBOX
}

// DEX_FINDOBJECT: Objekte unter Mausklick enumerieren ------------------------
LRESULT ExtDirisWindow :: OnEnumFoundObjects (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
FINDOBJECT *pFO = (FINDOBJECT *)lParam;

	TX_ASSERT_POINTER(pFO, FINDOBJECT);
	TX_ASSERT(sizeof(FINDOBJECT) == pFO -> dwSize);
	TX_ASSERT(TIsValidAddress(pFO -> eFcn, 1, false));
#endif // _DEBUG

	return LRESULT(DBO().Shapes().FindObjectsFromPointEx ((FINDOBJECT *)lParam));
}

// Relationen -----------------------------------------------------------------
// DEX_MODRELATION: Relation modifizieren/erzeugen ----------------------------
LRESULT ExtDirisWindow :: OnModRelation (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
MODRELATION *pMR = (MODRELATION *)lParam;

	TX_ASSERT_POINTER(pMR, MODRELATION);
	TX_ASSERT(sizeof(MODRELATION) == pMR -> dwSize);
	TX_ASSERT(IsValidONr(pMR -> lPONr));
	TX_ASSERT(IsValidONr(pMR -> lSONr));
	TX_ASSERT((pMR -> iRTyp & (RTBegleitO|RTBegleitU)) || IsValidRCode(pMR -> lRCode));

CActDB ActDB (DBO().DB());
		
	DBO().DB().SetDirty();

return (LRESULT)PutRelation (pMR -> lPONr, pMR -> lSONr, 
			     pMR -> lRCode, pMR -> iRTyp);
}

// DEX_DELRELATION: Relation löschen ------------------------------------------
LRESULT ExtDirisWindow :: OnDelRelation (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
DELRELATION *pDR = (DELRELATION *)lParam;

	TX_ASSERT_POINTER(pDR, DELRELATION);
	TX_ASSERT(sizeof(DELRELATION) == pDR -> dwSize);
	TX_ASSERT(IsValidONr(pDR -> lPONr));
	TX_ASSERT(IsValidONr(pDR -> lSONr));
	TX_ASSERT((pDR -> iRTyp & (RTBegleitO|RTBegleitU)) || IsValidRCode(pDR -> lRCode));

CActDB ActDB (DBO().DB());
		
	DBO().DB().SetDirty();

return (LRESULT)DelRelation (pDR -> lPONr, pDR -> lSONr, 
			     pDR -> lRCode, pDR -> iRTyp);
}

// DEX_ENUMRELATIONS: alle Relationen (RCodes) der GeoDB enumerieren ----------
LRESULT ExtDirisWindow :: OnEnumRelations (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEYLONG);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	return (LRESULT)DBO().DB().EnumRCodes (pK -> eFcn, pK -> ePtr);
}


// DEX_ENUMRELATIONOBJS: alle Relationen (RCodes) eines Objektes enumerieren --
LRESULT ExtDirisWindow :: OnEnumObjectRelations (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
#if defined(_DEBUG)
ENUMRELATIONOBJS *pERO = (ENUMRELATIONOBJS *)lParam;

	TX_ASSERT_POINTER(pERO, ENUMRELATIONOBJS);
	TX_ASSERT(sizeof(ENUMRELATIONOBJS) == pERO -> dwSize);
	TX_ASSERT(IsValidONr(pERO -> lONr));
	TX_ASSERT(TIsValidAddress(pERO -> eFcn, 1, false));
//	TX_ASSERT(pERO -> iRTyp & (RTBegleitO|RTBegleitU) || IsValidRCode(pERO -> lRCode));
#endif // _DEBUG

CActDB ActDB (DBO().DB());
	
	return DBO().DB().EnumRelationObjs ((ENUMRELATIONOBJS *)lParam);
}

// DEX_QUERYIDENTBASE: IdentifikatorZahlenbasis liefern -----------------------
LRESULT ExtDirisWindow :: OnQueryIdentBase (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
CActDB ActDB (DBO().DB());
int iBase = DBO().GetIdBase();

	TX_ASSERT(iBase == 10 || iBase == 16);

	return (LRESULT)iBase;
}

// DEX_QUERYMCODEBASE: MCode-Zahlenbasis liefern ------------------------------
LRESULT ExtDirisWindow :: OnQueryMCodeBase (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
CActDB ActDB (DBO().DB());
int iBase = DBO().GetMkBase();

	TX_ASSERT(iBase == 10 || iBase == 16);

	return (LRESULT)iBase;
}

// DEX_QUERYIDENTOBJTYPES: ObjektTypen eines IDents liefern -------------------
LRESULT ExtDirisWindow :: OnQueryIdentObjectTypes (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);
		
	TX_ASSERT(IsValidIdent((LONG)lParam));

short iOTypes = 0;
CActDB ActDB (DBO().DB());

	if (DBO().DB().FindId (lParam, NULL, &iOTypes) != EC_OKAY)
		iOTypes = 0;		// Fehler

return LRESULT(iOTypes);
}

// Anlegen neuer Datenbanken --------------------------------------------------
// DEX_CREATENEWGEODB: GeoDB neu erzeugen -------------------------------------
LRESULT ExtDirisWindow :: OnCreateGeoDB (LPARAM lParam)
{	
#if defined(_DEBUG)
CREATEDB *pCD = (CREATEDB *)lParam;

	TX_ASSERT_POINTER(pCD, DWORD);
	if (sizeof(CREATEDBEX) == pCD -> dwSize)
		TX_ASSERT_POINTER(pCD, CREATEDBEX);
	else {
		TX_ASSERT(sizeof(CREATEDB) == pCD -> dwSize);
		TX_ASSERT_POINTER(pCD, CREATEDB);
	}
	TX_ASSERT(TIsValidString(pCD -> m_pName));
	TX_ASSERT(NULL == pCD -> m_pUser || TIsValidString(pCD -> m_pUser));
	TX_ASSERT(NULL == pCD -> m_pPassWd || TIsValidString(pCD -> m_pPassWd));
#endif // _DEBUG

	return (LRESULT)CreateNewDB ((CREATEDB *)lParam, 
		(((CREATEDB *)lParam) -> m_iMode & DBVFlags) == DBVNormal ? DBD050A : DBD050B);
}
		
// DEX_CREATENEWIDENTSDB: PBD neu erzeugen ------------------------------------
LRESULT ExtDirisWindow :: OnCreatePBD (LPARAM lParam)
{
#if defined(_DEBUG)
CREATEDB *pCD = (CREATEDB *)lParam;

	TX_ASSERT_POINTER(pCD, DWORD);
	if (sizeof(CREATEDBEX) == pCD -> dwSize)
		TX_ASSERT_POINTER(pCD, CREATEDBEX);
	else {
		TX_ASSERT(sizeof(CREATEDB) == pCD -> dwSize);
		TX_ASSERT_POINTER(pCD, CREATEDB);
	}
	TX_ASSERT(NULL == pCD -> m_pName || TIsValidString(pCD -> m_pName));
	TX_ASSERT(NULL == pCD -> m_pUser || TIsValidString(pCD -> m_pUser));
	TX_ASSERT(NULL == pCD -> m_pPassWd || TIsValidString(pCD -> m_pPassWd));
#endif // _DEBUG

	return (LRESULT)CreateNewDB ((CREATEDB *)lParam,
		(((CREATEDB *)lParam) -> m_iMode & DBVFlags) == DBVNormal ? PBD050A : PBD050B);
}

// SystemMeldungen ------------------------------------------------------------
// DEX_SETERROR: Fehlermeldung auslösen ---------------------------------------
LRESULT ExtDirisWindow :: OnSetError (LPARAM lParam)
{
ERRORMESSAGE *pEM = (ERRORMESSAGE *)lParam;

	TX_ASSERT_POINTER(pEM, ERRORMESSAGE);

	return (LRESULT)db_error (pEM -> emiErrCode,
				  pEM -> emiRoutine,
				  pEM -> empData);
}
		
// DEX_ERRINSTALL: Fehlerbehandlung festlegen ---------------------------------
LRESULT ExtDirisWindow :: OnErrInstall (LPARAM lParam)
{
ERRINSTALL *pEI = (ERRINSTALL *)lParam;

	TX_ASSERT_POINTER(pEI, ERRINSTALL);
	return (LRESULT)err_install (pEI -> eiRC, pEI -> eiEH, pEI -> eioEH);
}

// DEX_EXTERRINSTALL: Fehelerbehandlung festlegen (erweitert) -----------------
LRESULT ExtDirisWindow :: OnExtErrInstall (LPARAM lParam)
{
EXTERRINSTALL *pEI = (EXTERRINSTALL *)lParam;

	TX_ASSERT_POINTER(pEI, EXTERRINSTALL);
	return (LRESULT)ExtErrInstall (pEI -> eiRC, pEI -> eiEH, pEI -> eioEH, (void *)pEI -> dwData);
}
		
// Erweiterungen Laden/UnLaden ------------------------------------------------
// DEX_LOADEXTENSION: Erweiterung laden ---------------------------------------
LRESULT ExtDirisWindow :: OnLoadExtension (LPARAM lParam)
{	
	TX_ASSERT(TIsValidString((char *)lParam));

	return (LRESULT)(void *)LoadExtension (NULL, (char *)lParam, LEFullLoad);
}

// DEX_LOADEXTENSIONEX: Erweiterung mit Optionen laden ------------------------
LRESULT ExtDirisWindow :: OnExtLoadExtension (LPARAM lParam)
{
LOADEXTENSIONEX *pLE = (LOADEXTENSIONEX *)lParam;

	TX_ASSERT_POINTER(pLE, LOADEXTENSIONEX);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	return (LRESULT)(void *)LoadExtension (
				pLE -> m_pDesc, pLE -> m_pName, 
				pLE -> m_iMode, 
				pLE -> m_fGlobal ? EF_Global : (EXTENSIONFLAG)0
			);
}

// DEX_UNLOADEXTENSION: Erweiterung entladen ----------------------------------
LRESULT ExtDirisWindow :: OnUnLoadExtension (LPARAM lParam)
{
	TX_ASSERT(TIsValidString((char *)lParam));

char *pExtName = m_pEL -> RetrieveExtName ((char *)lParam);
bool iResult = ReUnLoadExtension (pExtName, (char *)lParam);

	DELETE (pExtName);

return (LRESULT)iResult;
}

// DEX_UNLOADEXTENSIONEX: Erweiterung mit Optionen entladen -------------------
LRESULT ExtDirisWindow :: OnExtUnLoadExtension (LPARAM lParam)
{
LOADEXTENSIONEX *pLE = (LOADEXTENSIONEX *)lParam;
bool iResult = false;

	TX_ASSERT_POINTER(pLE, LOADEXTENSIONEX);
	TX_ASSERT(NULL == pLE -> m_pDesc || TIsValidString(pLE -> m_pDesc));
	TX_ASSERT(TIsValidString(pLE -> m_pName));

	if (pLE -> m_iMode & LEFullLoad)	// hier FullUnload
		iResult = UnLoadExtension (pLE -> m_pName, true);
	else {		// nur entladen
		if (pLE -> m_pDesc == NULL) {
		char *pExtName = m_pEL -> RetrieveExtName (pLE -> m_pName);

			iResult = ReUnLoadExtension (pExtName, pLE -> m_pName);
			DELETE (pExtName);
		} else
			iResult = ReUnLoadExtension (pLE -> m_pDesc, pLE -> m_pName);
	}

return (LRESULT)iResult;
}

// DEX_RENDERGEODB: GeoDB in hDC abbilden -------------------------------------
LRESULT ExtDirisWindow :: OnRenderGeoDB (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
RENDERGEODB *pRG = (RENDERGEODB *)lParam;

	TX_ASSERT_POINTER(pRG, RENDERGEODB);
	TX_ASSERT(sizeof(RENDERGEODB) == pRG -> dwSize);
#endif // _DEBUG

	return LRESULT(RenderGeoDB ((RENDERGEODB *)lParam));
}

// DEX_QUERYEXPOSEDOC: neu zu zeichnenden GeoDB-Bereich liefern ---------------
LRESULT ExtDirisWindow :: OnQueryExposedOC (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
	return LRESULT(DBO().QueryExposedOC ((ObjContainer *)lParam));
}

// DEX_QUERYEXPOSEDAREA: neu zu zeichnenden Bildschirmbereich liefern ---------
LRESULT ExtDirisWindow :: OnQueryExposedArea (LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(Rectangle), true));
	return LRESULT(DBO().QueryExposedArea ((Rectangle *)lParam));
}

// DEX_QUERYPROJECTSTORAGE: LPSTORAGE für dieses Projekt liefern --------------
LRESULT ExtDirisWindow :: OnQueryIStorage (LPARAM lParam)
{		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(LPSTORAGE), true));

return LRESULT(DBO().DB().GetProjectStorage ((LPSTORAGE *)lParam));
}

// DEX_QUERYACTIVEPALETTE: aktuelle Palette abfragen --------------------------
LRESULT ExtDirisWindow :: OnQueryActPalette (LPARAM lParam)
{	
	return (LPARAM)(void *)hPalette;
}
		
// DEX_SHOWMAINWINDOW: Hauptfenster anzeigen ----------------------------------
LRESULT ExtDirisWindow :: OnShowMainWindow (LPARAM lParam)
{		
	Show ((ShowState)lParam);
	App :: Exec (ExecWhileEvent);

return LRESULT(true);
}

// DEX_HIDEMAINWINDOW: Hauptfenster ausblenden --------------------------------
LRESULT ExtDirisWindow :: OnHideMainWindow (LPARAM lParam)
{	
	Show (HideWindow);
	App :: Exec (ExecWhileEvent);

return LRESULT(true);
}

// DEX_QUERYMAINWINDOWVISIBLE: Hauptfenster sichtbar ? ------------------------
LRESULT ExtDirisWindow :: OnQueryMainWindowVisible (LPARAM lParam)
{		
	return (LPARAM)isVisible();
}
		
// DEX_QUITAPP: TRiAS beenden -------------------------------------------------
LRESULT ExtDirisWindow :: OnQuit (LPARAM lParam)
{
	if (myQueryClose ((bool)lParam)) {
		App :: Quit();				// Force Quit
		return LRESULT(true);		// schließen
	}

return LRESULT(false);	// nicht geschlossen
}
		
// DEX_QUERYDEFAULTDATAPATH: StandardDatenPfad liefern --------------------------
LRESULT ExtDirisWindow :: OnQueryDefaultDataPath (LPARAM lParam)
{	
	TX_ASSERT(TIsValidAddress((void *)lParam, _MAX_PATH, true));
	if (lParam) strcpy ((char *)lParam, cbDefaultDir);

return LRESULT(lParam);
}		

// DEX_MODDEFAULTDATAPATH: Standard-datenPfad modifizieren --------------------
LRESULT ExtDirisWindow :: OnModDefaultDataPath (LPARAM lParam)
{		
	TX_ASSERT(TIsValidString((char *)lParam));
	if (lParam) strcpy (cbDefaultDir, (char *)lParam);

return LRESULT(lParam);
}

// DEX_REMOVEORWND: ORFenster schließen ---------------------------------------
LRESULT ExtDirisWindow :: OnCloseORWindows (LPARAM lParam)
{
	if (NULL == lParam)
		CloseAllORWindows();	
	else {
		TX_ASSERT(IsWindow((HWND)lParam) && NULL != GetORWindow((HWND)lParam));

		CloseORWindow ((HWND)lParam);
	}

return LRESULT(true);
}

// DEX_ACTIVATEALLORWNDS: alle ORFenster schließen ----------------------------
LRESULT ExtDirisWindow :: OnActivateAllORWnds (LPARAM lParam)
{	
	TX_ASSERT(NULL == (HWND)lParam ||
		  (IsWindow((HWND)lParam) && NULL != GetORWindow((HWND)lParam)));
	
return LRESULT(ActivateAllObj ((HWND)lParam));
}

// DEX_QUERYOPENPROJECTS: Anzahl der geöffneten Projekte abfragen -------------
LRESULT ExtDirisWindow :: OnNumOfOpenProjects (LPARAM)
{
	return IsValidActiveView() ? 1 : 0;		// ehrlich aber wahr
}

// DEX_GETVIEWDESCRIPTION: BeschreibungsText für eine Sicht liefern -----------
LRESULT ExtDirisWindow :: OnQueryViewDescription (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

#if defined(_DEBUG)
VIEWDESC *pVD = (VIEWDESC *)lParam;

	TX_ASSERT(TIsValidAddress(pVD, sizeof(VIEWDESC), true));
	TX_ASSERT(sizeof(VIEWDESC) == pVD -> m_dwSize);
	TX_ASSERT(NULL == pVD -> m_pView || TIsValidString(pVD -> m_pView));
	TX_ASSERT(TIsValidAddress(pVD -> m_pDesc, pVD -> m_iLen, true));
#endif // _DEBUG

return LRESULT(DBO().QueryViewDesc ((VIEWDESC *)lParam));
}

// DEX_MODVIEWDESCRIPTION: BeschreibungsText einer Sicht setzen ---------------
LRESULT ExtDirisWindow :: OnSetViewDescription (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);
		
#if defined(_DEBUG)
VIEWDESC *pVD = (VIEWDESC *)lParam;

	TX_ASSERT_POINTER(pVD, VIEWDESC);
	TX_ASSERT(sizeof(VIEWDESC) == pVD -> m_dwSize);
	TX_ASSERT(NULL == pVD -> m_pView || TIsValidString(pVD -> m_pView));
	TX_ASSERT(NULL == pVD -> m_pDesc || TIsValidString(pVD -> m_pDesc));
#endif // _DEBUG

	DBO().DB().SetDirty();

return LRESULT(DBO().SetViewDesc ((VIEWDESC *)lParam));
}

// DEX_CANCELMODE: Blinken aller ORFenster beeinflussen -----------------------
LRESULT ExtDirisWindow :: OnCancelMode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
return LRESULT(HandleCancelMode ((lParam != 0) ? true : false));
}

// DEX_QUERYPROJECTCONT: liefert DB-Container ---------------------------------
LRESULT ExtDirisWindow :: OnQueryProjectCont (LPARAM lParam)
{
	if (!IsValidActiveView() || lParam == 0)
		return LRESULT(false);

	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
	*(ObjContainer *)lParam = DBO().DB().DBCont();
	
return LRESULT(true);
}

static long RetrieveObjNameMCodeIdent (DatenBasisObjekt &rDBO, long lIdent)
{
	TX_ASSERT(IsValidIdent(lIdent));

ProFile PF (rDBO.DB().GetDBName());
char outBuff[40];

	return PF.GetObjNameCode (ultoa (lIdent, outBuff, rDBO.GetIdBase()));
}

static long RetrieveObjNameMCode (DatenBasisObjekt &rDBO, long lONr)
{
	TX_ASSERT(IsValidONr(lONr));
	return RetrieveObjNameMCodeIdent (rDBO, rDBO.RetrieveIdent (lONr));
}

// DEX_QUERYOBJECTNAME: Lesen eines Objektnamens ------------------------------
// @msg DEX_QUERYOBJECTNAME | Diese Message wird an <tr> geschickt, um den Namen 
// eines Objektes abzufragen. In dem Fall, wenn kein Objektname für dieses Objekt 
// existiert, wird der Unique Ident geliefert.
// @parm OBJECTFEATURE * | pObjFeature | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc <tr> liefert den Pointer auf die Zeichenkette <e OBJECTFEATURE.m_pMText>
// wenn kein Fehler aufgetreten ist, ansonsten ist der Rückgabewert NULL.<nl>Diese Message
// kann außerdem dazu verwendet werden, abzufragen, ob das gegebene Objekt einen 
// Objektnamen besitzt. In diesem Fall ist der Rückgabewert <t true>, wenn ein Objektname 
// für dieses Objekt existiert, anderenfalls <t false>.
// @comm Der Objektname eines Objektes ist ein Merkmalswert, welcher für ein Objekt
// unter einem speziellen Merkmalscode abgelegt ist. Dieser Merkmalscode wird z.Zt.
// spezifisch für den Identifikator eines Objektes über die Initialisierungsdatei 
// des aktuellen Projektes festgelegt. Der Objektname eines Objektes kann mit der 
// Message <m DEX_SETOBJECTNAME> geschrieben bzw. gelöscht werden.<nl>Diese Message 
// wird durch die Funktion <f DEX_GetObjectName> ausgelöst.
// @xref <m DEX_SETOBJECTNAME>, <f DEX_GetObjectName>
LRESULT ExtDirisWindow :: OnQueryObjectFeatureSpec (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

// MerkmalsCode des Objektnamens besorgen und Merkmal schreiben
TARGETMERKMAL TM;
OBJECTFEATURE *pOF = (OBJECTFEATURE *)lParam;

	TX_ASSERT_POINTER(pOF, OBJECTFEATURE);

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = pOF -> m_lONr;
	TM.lMCode = RetrieveObjNameMCode (DBO(), pOF -> m_lONr);
	TM.imaxLen = pOF -> m_iLen;
	TM.pMText = pOF -> m_pMText;
	TM.iTTyp = TT_Objekt;

LRESULT lRes = 0L;

	if ((lRes = OnQueryTextMerkmal (LPARAM(&TM))) == 0L) {
	// dieses Objekt hat keinen Objektnamen, UniqueIdent verwenden
		TM.lMCode = DEX_GetUniqueIdentMCode();
		TM.imaxLen = pOF -> m_iLen;	// Länge neu setzen
		lRes = OnQueryTextMerkmal (LPARAM(&TM));
	} 

return lRes;	
}

// DEX_SETOBJECTNAME: Setzen/Löschen eines Objektnamens -----------------------
// @msg DEX_SETOBJECTNAME | Diese Message wird an <tr> geschickt, um den Namen 
// eines Objektes zu setzen oder zu löschen.
// @parm OBJECTFEATURE * | pObjFeature | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc <tr> liefert einen <t ErrCode>. D.h. EC_OKAY wenn kein Fehler 
// aufgetreten ist bzw. anderenfalls einen den Fehler beschreibendenden <t ErrCode>.
// @comm Der Objektname eines Objektes ist ein Merkmalswert, welcher für ein Objekt
// unter einem speziellen Merkmalscode abgelegt ist. Dieser Merkmalscode wird z.Zt.
// spezifisch für den Identifikator eines Objektes über die Initialisierungsdatei 
// des aktuellen Projektes festgelegt.<nl>Der Objektname wird gelöscht, wenn der Wert
// des Feldes <e OBJECTFEATURE.m_pMText> gleich NULL ist.<nl>Der Objektname eines 
// Objektes kann mit der Message <m DEX_QUERYOBJECTNAME> abgefragt werden.
// <nl>Diese Message wird durch die Funktion <f DEX_ModObjectName> ausgelöst.
// @xref <m DEX_QUERYOBJECTNAME>, <f DEX_ModObjectName>
LRESULT ExtDirisWindow :: OnSetObjectFeatureSpec (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);

// MerkmalsCode des Objektnamens besorgen und Merkmal schreiben
TARGETMERKMAL TM;
OBJECTFEATURE *pOF = (OBJECTFEATURE *)lParam;

	TX_ASSERT_POINTER(pOF, OBJECTFEATURE);

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = pOF -> m_lONr;
	TM.lMCode = RetrieveObjNameMCode (DBO(), pOF -> m_lONr);
	TM.imaxLen = pOF -> m_iLen;
	TM.pMText = pOF -> m_pMText;
	TM.iTTyp = TT_Objekt;

return OnModTextMerkmal (LPARAM(&TM));
}

// DEX_DIAGNOSTICSENABLE: Ein- und Ausschalten der DiagnoseNotifikationen ----
// @msg DEX_DIAGNOSTICSENABLE | Mit dieser Message an <tr> können die 
// Diagnose-Notifikationen ein- bzw. ausgeschaltet werden.
// @parm bool | fDiagnostics | lParam ist ein Wert vom Typ <t bool>, der angibt, ob
// im weiteren Diagnose-Notifikationen verschickt werden sollen.
// @rdesc Der Rückgabewert enthält den bisherigen DiagnoseMode, der dazu verwendet 
// werden kann den ursprünglichen wert wieder einzustellen.
// <nl>Diese Message wird durch die Funktionen <f DEX_EnableDiagnostics> und
// <f DEX_DisableDiagnostics> ausgelöst.
// @comm Um die Diagnose-Notifikation auch wirklich zu erhalten, genügt es nicht,
// diese mit dieser Message einzuschalten. Diese Message schaltet lediglich die
// Generierung der Diagnose-Notifikationen zu. Zusätzlich muß jede der gewünschten
// Notifikationen einzeln registriert werden <mf CTriasExtension::RegisterNotification>.
// Gleiches gilt für die Nutzung dieser Message zum Abschalten der Diagnose-Notifikationen.
// Es genügt nicht, lediglich diese Message abzuschicken, auf jeden Fall müssen alle
// vorher registrierten Notifikationen mit <mf CTriasExtension::UnRegisterNotification>
// wieder abgemeldet werden.
// @xref <f DEX_EnableDiagnostics>, <f DEX_DisableDiagnostics>, 
// <mf CTriasExtension::RegisterNotification>, 
// <mf CTriasExtension::UnRegisterNotification>
LRESULT ExtDirisWindow :: OnEnableDiagnostics (LPARAM lParam)
{
bool fOldDiag = g_fDiagnostics;

	g_fDiagnostics = (bool)lParam;

return LRESULT(fOldDiag);
}

// DEX_QUERYUNKNOWNIDENT: Ein- und Ausschalten der DiagnoseNotifikationen ----
// @msg DEX_QUERYUNKNOWNIDENT | Mit dieser Message an <tr> kann der Identifikator
// für nicht klassifizierte Objekte des aktuellen Projektes abgefragt werden.
// @rdesc Der Rückgabewert enthält den gewünschten Identifikator bzw. Null im 
// Fehlerfall.
// <nl>Diese Message wird durch die Funktion <f DEX_GetUnknownIdent> ausgelöst.
// @comm Der Identifikator für die Objektklasse der nicht klassifizierten Objekte ist
// eine projektbezogener Wert, der durch <tr> generiert wird. Dieser Wert wird im
// Datenbasis-Header unter dem Schlüssel 'UnknownIdent' eingetragen.
// @xref <f DEX_GetUnknownIdent>
LRESULT ExtDirisWindow :: OnQueryUnknownIdent (LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	return LRESULT(DBO().QueryUnknownIdent());
}

// DEX_FINDOBJFROMNAME: Auffinden eines Objektes über Objektnamen -------------
// @msg DEX_FINDOBJFROMNAME | Mit dieser Message an <tr> kann ein Objekt über seinen
// Objektnamen gesucht werden.
// @parm char * | pObjName | Der Objektname des gesuchten Objektes.
// @rdesc Der Rückgabewert enthält Objeknummer des gesuchten Objektes bzw. -1L im 
// Fehlerfall.<nl>Diese Message wird durch die Funktion <f DEX_GetONrFromObjName>
// ausgelöst.
// @comm Existieren mehrere Objekte mit diesem Objektnamen, so wird das erste gefundene 
// geliefert. Existiert kein Objekt mit diesem Objektnamen, so wird die übergebene
// Zeichenkette als Unique Ident interpretiert und das Objekt mit diesem Unique Ident
// gesucht. Auch hier wird das jeweils erste gefundene Objekte geliefert.
// @xref <f DEX_GetONrFromObjName>
LRESULT ExtDirisWindow :: OnFindObjFromName (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1L);

	TX_ASSERT(TIsValidString((char *)lParam));
	return LRESULT(DBO().FindObjFromName ((char *)lParam));
}

// DEX_QUERYOBJNAMEMCODE: Liefert MCode für Objektnamen für Objektes eines Idents
// @msg DEX_QUERYOBJNAMEMCODE | Mit dieser Message an <tr> kann der Merkmalscode 
// abgefragt werden, unter dem für alle Objekte des gegebenen Identifikators der
// Objektname abgelegt ist.
// @parm ULONG | lIdent | Identifikator, für dessen Objekte der Merkmalscode gesucht 
// wird.
// @rdesc Der Rückgabewert enthält den gesuchten Merkmalscode bzw. Null im 
// Fehlerfall.<nl>Diese Message wird durch die Funktion <f DEX_GetObjNameMCode>
// ausgelöst.
// @comm Der Objektname ist ein spezielles (Text-)Merkmal eines Objektes, welches ein Objekt 
// im allgemeinen eineindeutig beschreibt. Es kann zur nutzerfreundlichen Identifikation
// eines Objektes eingestzt werden. Dieses Merkmal wird für alle Objekte eines 
// Identifikators unter einem einheitlichen Merkmalscode abgelegt. Dieser Merkmalscode
// wird durch die Funktion <f DEX_GetObjNameMCode> geliefert.
// @xref <f DEX_GetObjNameMCode>
LRESULT ExtDirisWindow :: OnQueryObjNameMCode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(IsValidIdent(lParam));

return LRESULT (RetrieveObjNameMCodeIdent (DBO(), lParam));
}

// DEX_QUERYUNIQUEIDENTMCODE: Abfragen des MCodes der Unique Idents -----------
// @msg DEX_QUERYUNIQUEIDENTMCODE | Mit dieser Message an <tr> kann der Merkmalscode 
// abgefragt werden, unter dem für alle Objekte der Unique Ident abgelegt ist.
// @rdesc Der Rückgabewert enthält den gesuchten Merkmalscode bzw. Null im 
// Fehlerfall.
// @comm Der Unique Ident ist ein eineindeutiges (Text-)Merkmal, welches automatisiert für
// jedes Objekt bei dessen Erfassung generiert wird. Dieses Merkmal wird für alle 
// Objekte unter einem einheitlichen Merkmalscode abgelegt.<nl>Diese Message wird 
// durch die Funktion <f DEX_GetUniqueIdentMCode> ausgelöst.
// @xref <f DEX_GetUniqueIdentMCode>
LRESULT ExtDirisWindow :: OnQueryUniqueIdentMCode (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

long lMCode = HeaderEntry (DBO().DB(), IDS_UNIQUEIDENT).EntryLong(0L);

	if (0L == lMCode) {
		if (10 == DBO().GetMkBase())
			lMCode = 51200000L;
		else
			lMCode = 0x51200000L;
		MainInitPbd (DBO().DB(), IDS_UNIQUEIDENT, true, lMCode);
	}

return LRESULT(lMCode);
}


// Diverse HeaderEinträge neu einlesen ----------------------------------------
// @msg DEX_HEADERREREAD | Mit dieser Message an <tr> werden diverse Einträge des 
// aktuellen Projektes neu eingelesen. 
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message sollte gerufen werden, wenn ein Headereintrag verändert 
// wurde.<nl>Diese Message wird durch die Funktion <f DEX_ReReadHeader> ausgelöst.
// @xref <f DEX_ReReadHeader>
LRESULT ExtDirisWindow :: OnReReadHeader (LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	ReReadHeader();
	ReReadCaption();

return true;
}

// DEX_FINDIDENTFROMNAME: Ident über PBDNamen finden --------------------------
typedef struct tagFINDIDENTKTEXT {
	char *m_pText;
	ULONG m_lIdent;
	ExtDirisWindow *m_pW;
	bool m_fIgnoreCase;
} FINDIDENTKTEXT;

extern "C" bool EXPORTTRIAS PASCAL FindIdentKText (long lIdent, bool, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
FINDIDENTKTEXT *pFIT = (FINDIDENTKTEXT *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof (cbKText);
	if ((pFIT -> m_pW -> OnQueryPBDData ((DWORD)&pbdData) == EC_OKAY)) {
		if (pFIT -> m_fIgnoreCase) {
			if (!stricmp (cbKText, pFIT -> m_pText)) {
				pFIT -> m_lIdent = lIdent;
				return false;		// gefunden, also abbrechen
			}
		} else if (!strcmp (cbKText, pFIT -> m_pText)) {
			pFIT -> m_lIdent = lIdent;
			return false;		// gefunden, also abbrechen
		}
	}
			
return true;	// immer weiter suchen
}

LRESULT ExtDirisWindow :: OnFindIdentFromNameHelper (char *pName, bool fIgnoreCase)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(TIsValidString(pName));

// Pbd enumerieren und nach den gegeben KurzText suchen
CActDB ActPBD (DBO().PbdDB());

	if (!ActPBD) return 0L;		// keine PBD gegeben

FINDIDENTKTEXT FIT;

	FIT.m_pText = pName;
	FIT.m_lIdent = 0L;
	FIT.m_pW = this;
	FIT.m_fIgnoreCase = fIgnoreCase;
	DBO().PbdDB().EnumPBDData ('i', (ENUMLONGKEYPROC)FindIdentKText, 
				   (void *)&FIT);

return LRESULT(FIT.m_lIdent);
}

// @msg DEX_FINDIDENTFROMNAME | Mit dieser Message an <tr> ist es möglich über 
// einen Objektklassennamen (Kurztext) den zugehörigen Identifikator (Schlüssel)
// zu finden.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// (Kurztext) enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Identifikatoren der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Identifikator zu finden.
// @comm Diese Message wird durch die Funktion <f DEX_GetIdentFromClassName> ausgelöst.
// @xref <f DEX_GetIdentFromClassName>
LRESULT ExtDirisWindow :: OnFindIdentFromName (LPARAM lParam)
{
	return OnFindIdentFromNameHelper ((char *)lParam, false);
}

// @msg DEX_FINDIDENTFROMNAMECI | Mit dieser Message an <tr> ist es möglich über 
// einen Objektklassennamen (Kurztext) den zugehörigen Identifikator (Schlüssel)
// zu finden. Bei der Suche wird Groß-/Kleinschreibung ignoriert.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// (Kurztext) enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Identifikatoren der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Identifikator zu finden. Groß-/Kleinschreibung des Namens der Objektklasse
// wird dabei ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_GetIdentFromClassNameCI> ausgelöst.
// @xref <f DEX_GetIdentFromClassNameCI>, <f DEX_GetIdentFromClassName>
LRESULT ExtDirisWindow :: OnFindIdentFromNameCI (LPARAM lParam)
{
	return OnFindIdentFromNameHelper ((char *)lParam, true);
}

// DEX_FINDMCODEFROMNAME: MCode über PBDNamen finden --------------------------
typedef struct tagFINDMCODEKTEXT {
	char *m_pText;
	ULONG m_lMCode;
	ExtDirisWindow *m_pW;
	bool m_fIgnoreCase;
} FINDMCODEKTEXT;

extern "C" bool EXPORTTRIAS PASCAL FindMCodeKText (long lMCode, bool, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
FINDMCODEKTEXT *pFIT = (FINDMCODEKTEXT *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof (cbKText);
	if ((pFIT -> m_pW -> OnQueryPBDData ((DWORD)&pbdData) == EC_OKAY)) {
		if (pFIT -> m_fIgnoreCase) {
			if (!stricmp (cbKText, pFIT -> m_pText)) {
				pFIT -> m_lMCode = lMCode;
				return false;		// gefunden, also abbrechen
			}
		} else if (!strcmp (cbKText, pFIT -> m_pText)) {
			pFIT -> m_lMCode = lMCode;
			return false;		// gefunden, also abbrechen
		}
	}
		
return true;	// immer weiter suchen
}

LRESULT ExtDirisWindow :: OnFindMCodeFromNameHelper (char *pName, bool fIgnoreCase)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(TIsValidString(pName));

// Pbd enumerieren und nach den gegeben KurzText suchen
CActDB ActPBD (DBO().PbdDB());

	if (!ActPBD) return 0L;		// keine PBD gegeben

FINDMCODEKTEXT FIT;

	FIT.m_pText = pName;
	FIT.m_lMCode = 0L;
	FIT.m_pW = this;
	FIT.m_fIgnoreCase = fIgnoreCase;
	DBO().PbdDB().EnumPBDData ('m', (ENUMLONGKEYPROC)FindMCodeKText, 
				   (void *)&FIT);

return LRESULT(FIT.m_lMCode);
}

// @msg DEX_FINDMCODEFROMNAME | Mit dieser Message an <tr> ist es möglich über 
// einen Merkmalsnamen (Kurztext) den zugehörigen Merkmalscode (Schlüssel)
// zu finden.
// @parm char * | pFeatureName | Zeichenkette, die den Merkmalsnamen
// (Kurztext) enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Merkmalsbeschreibungen der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Merkmalscode zu finden.
// @comm Diese Message wird durch die Funktion <f DEX_GetMCodeFromFeatureName> ausgelöst.
// @xref <f DEX_GetMCodeFromFeatureName>
LRESULT ExtDirisWindow :: OnFindMCodeFromName (LPARAM lParam)
{
	return OnFindMCodeFromNameHelper ((char *)lParam, false);
}

// @msg DEX_FINDMCODEFROMNAMECI | Mit dieser Message an <tr> ist es möglich über 
// einen Merkmalsnamen (Kurztext) den zugehörigen Merkmalscode (Schlüssel)
// zu finden. Bei der Suche wird Groß-/Kleinschreibung ignoriert.
// @parm char * | pFeatureName | Zeichenkette, die den Merkmalsnamen
// (Kurztext) enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Merkmalsbeschreibungen der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Merkmalscode zu finden. Groß-/Kleinschreibung des Merkmalsnamens
// wird dabei ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_GetMCodeFromFeatureNameCI> ausgelöst.
// @xref <f DEX_GetMCodeFromFeatureNameCI>, <f DEX_GetMCodeFromFeatureName>
LRESULT ExtDirisWindow :: OnFindMCodeFromNameCI (LPARAM lParam)
{
	return OnFindMCodeFromNameHelper ((char *)lParam, true);
}

// DEX_DELETEIDENT: Alle Objekte eines Idents löschen -------------------------
// @msg DEX_DELETEIDENT | Mit dieser Message an <tr> werden alle Objekte mit
// einem gegebenen Identifikator physisch aus der Datenbasis gelöscht.
// @parm ULONG | lIdent | Identifikator, dessen Objekte aus der datenbasis gelöscht 
// werden sollen.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.<nl>Das Löschen der Objekte erfolgt vollständig und ist
// nicht rückgängig zu machen. Es erfolgt keine weitere Rückfrage über die
// Nutzeroberfläche.
// @comm Diese Message wird durch die Funktion <f DEX_DeleteAllIdentObjects> ausgelöst.
// @xref <f DEX_DeleteAllIdentObjects>

bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp);

LRESULT ExtDirisWindow :: OnDeleteIdent (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidIdent((LONG)lParam));

	if (DEXN_DeletingIdent (lParam)) return LRESULT(false);

CActDB ActDB (DBO().DB());
ObjFeld Objs;

	if (!AddObjects (Objs, lParam, OTPunkt|OTLinie|OTFlaeche|OTText))
		return LRESULT(false);

	if (Objs.Count()) {
	CRing r(Objs);
		
		for (r.First(); r.Valid(); r.Next()) {
		ObjNummerLock l(r);
			
			TX_ASSERT(NULL != (ObjNummer *)l);
			DEX_DeleteObject (l -> _ON);
		}
		DEX_RefreshLegend();
	}
	DEXN_IdentDeleted (lParam);

return LRESULT(true);
}

// DEX_VIEWCREATE: Leere Sicht erzeugen ---------------------------------------
// @msg DEX_VIEWCREATE | Mit dieser Message an <tr> kann eine Ansicht erzeugt 
// werden. 
// @parm char * | pViewName | Der Name der neu zu erzeugenden Sicht.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.Wenn die gegebene Ansicht bereits im aktuellen 
// Projekt existiert, dann wird diese Ansicht gelöscht und durch eine leere 
// neue Ansicht mit diesem Namen ersetzt.
// Diese Message wird durch die Funktion <f DEX_CreateView> ausgelöst.
// @xref <f DEX_CreateView>, <f DEX_CreateViewOpt>
LRESULT ExtDirisWindow :: OnViewCreate (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

CActDB ActDB (DBO().DB());
Sicht S (DBO().DB(), (char *)lParam);

	return LRESULT(S.CreateView (false) == EC_OKAY ? CVCreated : CVExists);
}

// DEX_VIEWCREATEOPT: Leere Sicht erzeugen ---------------------------------------
// @msg DEX_VIEWCREATEOPT | Mit dieser Message an <tr> kann eine Ansicht erzeugt 
// werden. 
// @parm char * | pViewName | Der Name der neu zu erzeugenden Sicht.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.Wenn die gegebene Ansicht bereits im aktuellen 
// Projekt existiert, dann macht diese Message garnichts.
// @comm Diese Message wird durch die Funktion <f DEX_CreateViewOpt> ausgelöst.
// @xref <f DEX_CreateViewOpt>, <f DEX_CreateView>
LRESULT ExtDirisWindow :: OnViewCreateOpt (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

CActDB ActDB (DBO().DB());
Sicht S (DBO().DB(), (char *)lParam);
ErrCode RC = S.CreateView();

	
	if (RC == WC_EXISTS) return LRESULT(CVExists);
	if (RC == EC_OKAY) return LRESULT(CVCreated);
	
return LRESULT(CVError);
}

// DEX_DELETEIDENTFROMVIEW: Ident aus der Sicht herauslösen -------------------
// @msg DEX_DELETEIDENTFROMVIEW | Mit dieser Message an <tr> können einzelne
// Identifikator/Objekttyp-Kombinationen aus einer Sicht herausgelöscht werden.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu löschenden 
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_RemoveIdentFromView> ausgelöst.
// @xref <f DEX_RemoveIdentFromView>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnRemoveIdentFromView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];

	if (pVIO -> m_pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pVIO -> m_pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pVIO -> m_pView);
bool fResult = S.SatzNr() > 0;		// Sicht existiert
ErrCode RC = EC_OKAY;

	if (fResult && pVIO -> m_iOTyp & OTPunkt) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTPunkt);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTLinie);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTFlaeche);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTText);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}

return LRESULT(fResult);
}

// DEX_VIEWRENAME: Sicht umbenennen -------------------------------------------
// @msg DEX_VIEWRENAME | Mit dieser Message an <tr> kann eine existierende
// Ansicht umbenannt werden.
// @parm RENAMEVIEW * | pRenameView | Ein Zeiger auf eine Struktur vom 
// Typ <t RENAMEVIEW>.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_RenameView> ausgelöst.
// @xref <f DEX_RenameView>, <t RENAMEVIEW>
LRESULT ExtDirisWindow :: OnViewRename (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

RENAMEVIEW *pRV = (RENAMEVIEW *)lParam;

	TX_ASSERT_POINTER(pRV, RENAMEVIEW);
	TX_ASSERT(sizeof(RENAMEVIEW) == pRV -> dwSize);
	TX_ASSERT(NULL == pRV -> m_pOldName || TIsValidString(pRV -> m_pOldName));
	TX_ASSERT(TIsValidString(pRV -> m_pNewName));

char cbView[64];
const char *pView = pRV -> m_pOldName;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);

	return LRESULT(S.SatzNr() > 0 && S.Rename (pRV -> m_pNewName) == EC_OKAY);
}

// DEX_HASVIEWIDENT: Testen, ob Ident zu dieser Sicht gehört ------------------
// @msg DEX_HASVIEWIDENT | Diese Message an <tr> wird dazu verwendet, um 
// abzufragen, ob eine bestimmte Identifikator/Objekttyp-Kombination zu einer 
// Ansicht gehört.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu untersuchenden
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn Objekte der gegebenen
// Objekttypen und des gegebenen Identifikators zur Sicht gehören <t true>, 
// anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ViewHasIdent> ausgelöst.
// @xref <f DEX_ViewHasIdent>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnHasViewIdent (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];
char *pView = pVIO -> m_pView;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);
bool fResult = S.SatzNr() > 0;		// Sicht existiert

	if (!fResult) return LPARAM(false);
	
ErrCode RC = EC_OKAY;
	
	if (pVIO -> m_iOTyp & OTPunkt) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTPunkt);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTLinie);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTFlaeche);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTText);
		fResult = (RC == EC_OKAY);
	}

return LRESULT(fResult);
}

// DEX_HASVIEWOBJECT: Testen, ob Objekt zu dieser Sicht gehört ----------------
// @msg DEX_HASVIEWOBJECT | Diese Message an <tr> wird dazu verwendet, um 
// abzufragen, ob ein bestimmtes Objekt zu einer Ansicht gehört.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lONr> die ObjektNummer
// des zu untersuchenden Objektes. Die Felder <e VIEWIDENTOBJECT.m_lIdent> und <e VIEWIDENTOBJECT.m_iOTyp> 
// werden ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn das gegebene Objekt 
// zur Sicht gehört <t true>, anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ViewHasObject> ausgelöst.
// @xref <f DEX_ViewHasObject>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnHasViewObject (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(0L == pVIO -> m_lIdent);	// not given
	TX_ASSERT(IsValidONr(pVIO -> m_lONr));

	pVIO -> m_lIdent = DBO().RetrieveIdent (pVIO -> m_lONr);
	pVIO -> m_iOTyp =  OTypToBits (DBO().RetrieveObjTyp (pVIO -> m_lONr));

return OnHasViewIdent(lParam);
}

// @msg DEX_HASPROJECTVIEW | Diese Message an <tr> wird dazu verwendet, zu testen, 
// ob eine gegebene Ansicht im aktuellen Projekt definiert ist.
// @parm char * | pViewName | Zeiger auf den Namen der Ansicht, deren Existenz im 
// aktuelle Projekt überprüft werden soll.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn das gegebene Objekt 
// zur Sicht gehört <t true>, anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ProjectHasView> ausgelöst.
// @xref <f DEX_ProjectHasView>
LRESULT ExtDirisWindow :: OnHasProjectView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), (char *)lParam);

	return LRESULT(S.SatzNr() > 0);		// Sicht existiert
}

// @msg DEX_IDENTADDTOVIEW | Diese Message an <tr> wird dazu verwendet, um einen 
// Identifikator zu einer Ansicht hinzuzufügen.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT * | pViewIdentOTyp | Pointer auf eine Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu untersuchenden
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_AddIdentToView> ausgelöst.
// @xref <f DEX_AddIdentToView>
LRESULT ExtDirisWindow :: OnAddIdentToView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];
char *pView = pVIO -> m_pView;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);
bool fResult = false;
ErrCode RC = EC_OKAY;

	if (pVIO -> m_iOTyp & OTPunkt) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTPunkt);
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTLinie);;
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTFlaeche);
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTText);
		fResult = (RC == EC_OKAY);
	}

return LRESULT(fResult);
}

// DEX_RCTOOC -----------------------------------------------------------------
LRESULT ExtDirisWindow :: OnRCtoOC (LPARAM)
{
return LRESULT(true);
}

// DEX_OCTORC -----------------------------------------------------------------
LRESULT ExtDirisWindow :: OnOCtoRC (LPARAM)
{
return LRESULT(true);
}

// DEX_ISOBJWINDOW ------------------------------------------------------------
// @msg DEX_ISOBJWINDOW | Diese Message an <tr> wird dazu verwendet, um 
// festzustellen, ob das Fenster, dessen Handle (HWND) übergeben wurde ein 
// gültiges Objektrecherche-Fenster ist.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm HWND | hORWnd | Zu untersuchendes Fensterhandle
// @comm Diese Message wird durch die Funktion <f DEX_IsORWindow> ausgelöst.
// @xref <f DEX_IsORWindow>
LRESULT ExtDirisWindow :: OnIsORWindow (LPARAM lParam)
{
	TX_ASSERT(IsWindow((HWND)lParam));

	return LRESULT(GetORWindow (HWND(lParam)) != NULL ? true : false);
}

// DEX_OBJECTREPAINT ----------------------------------------------------------
LRESULT ExtDirisWindow :: OnRePaintObject (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidONr((LONG)lParam));

CTable t(DBO().Shapes().ObjNumTree());
VisInfo *pVI = (VisInfo *)DEX_SetAttributes (lParam);
bool fResult = false;

	if (t.Find (&lParam)) {		// nur zeichnen, wenn geladen
	ExtShapeObjectLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);

	short iOldDCInit = l -> FullDCInit();

		l -> FullDCInit() = FDC_FullInit | FDC_ActivateOnly;
		DrawEx (l, (DWORD)&DBO());
		l -> FullDCInit() = iOldDCInit;
		fResult = true;		// Erfolg melden
	}

// Attribute wieder rücksetzen
RESETATTRDATA RAD;

	RAD.lONr = lParam;
	RAD.pVI = pVI;
	DEX_ResetAttributes (&RAD);

return LRESULT(fResult);
}

// DEX_ENUMIDENTVIEWSEX -------------------------------------------------------
LRESULT ExtDirisWindow :: OnEnumIdentViewsEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

#if defined(_DEBUG)
ENUMLONGKEYEX *pELK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pELK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pELK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent(pELK -> eKey));
#endif // _DEBUG

return LRESULT(DBO().EnumIdentViewsEx ((ENUMLONGKEYEX *)lParam));
}


// @msg DEX_QUERYADMINMODE | Diese Message an <tr> wird dazu verwendet, um die
// erweiterten Zugriffsrechte des aktuellen Nutzers abzufragen.
// @rdesc Liefert einen <t bool> -Wert, der angibt, ob der aktuelle Nutzer über 
// erweiterte Zugriffsrechte verfügt über nicht.
// @comm Diese Message wird durch die Funktion <f DEX_QueryMode> ausgelöst und
// ist nur unter WindowsNT und Windows 95 verfügbar.
// @xref <f DEX_QueryMode>, <m DEX_SETADMINMODE>
LRESULT ExtDirisWindow :: OnQueryAdminMode (LPARAM)
{
DWORD dwResult = g_fSystemAdm ? QMSysAdmin : 0;

	dwResult |= g_fAutomation ? QMAutomation : 0;
	dwResult |= g_fStartByOle ? QMEmbedding : 0;
	dwResult |= g_fTip ? QMTipOfTheDay : 0;

return dwResult;
}

// @msg DEX_SETADMINMODE | Diese Message an <tr> wird dazu verwendet, um die
// erweiterten Zugriffsrechte des aktuellen Nutzers zu setzen.
// @parm bool | fAdminFlag | Enthält den neuen Wert, der dem SystemAdminFlag des
// aktuellen Nutzers zugewiesen werden soll.
// @rdesc Liefert einen <t bool> -Wert, der angibt, ob der aktuelle Nutzer über 
// erweiterte Zugriffsrechte verfügt hatte über nicht.
// @comm Diese Message wird durch die Funktion <f DEX_SetMode> ausgelöst und
// ist nur unter WindowsNT und Windows 95 verfügbar.
// @comm Jetzt ist diese Funktion auch unter Win31 und Win32s verfügbar greift 
// jedoch nicht wie unter Windows95/WindowsNT auf die Registry, sondern 
// auf die TRIAS.INI (Section [Parameters], Key SystemAdministration=1).
// @xref <f DEX_SetMode>, <m DEX_QUERYADMINMODE>
LRESULT ExtDirisWindow :: OnSetAdminMode (LPARAM lParam)
{
bool fOldFlag = g_fSystemAdm;

	g_fSystemAdm = (lParam & QMSysAdmin) ? true : false;

#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegConfig);

		if (regCfg.isValid()) {
		DWORD dwData = g_fSystemAdm;

			regCfg.SetDWORD (g_cbSysAdmin, dwData);
		}
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
	{
	ResString Profile (IDS_PROFILE, 13);
	ResString IrisPars (IDS_IRISPARS, 13);

		if (g_fSystemAdm) {	// Eintrag setzen
			WritePrivateProfileString (IrisPars, 
				g_cbSysAdmin, "1", Profile);
		} else {		// Eintrag löschen
			WritePrivateProfileString (IrisPars, 
				g_cbSysAdmin, NULL, Profile);
		}
	}
#endif // ENABLE_WIN32S_CODE

return fOldFlag;
}

// DEX_ONSETGEODBDIRTY
LRESULT ExtDirisWindow :: OnSetDirtyGeoDB (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
	DBO().DB().SetDirty (lParam ? true : false);

return (LRESULT)true;	// makes no sense
}

// DEX_ENUMALLPROJECTS
LRESULT ExtDirisWindow :: OnEnumProjects  (LPARAM lParam)
{
	if (!IsValidActiveView()) 
		return LRESULT(false);

ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

return EnumProjects (pK);
}

// DEX_PROJECTHANDLEFROMNAME
LRESULT ExtDirisWindow :: OnGetProjectHandle  (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

	TX_ASSERT(TIsValidString((char *)lParam));

	return (LRESULT)(void *)GetProjectHandle ((LPCSTR)lParam);
}

// DEX_PROJECTMAKEACTIVE
LRESULT ExtDirisWindow :: OnMakeProjectActive  (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

	TX_ASSERT(NULL != (HPROJECT)lParam);

return (LRESULT)(void *)MakeProjectActive ((HPROJECT)lParam);
}

// DEX_ENUMOBJRECHWNDS
LRESULT ExtDirisWindow :: OnEnumORWindows (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEYLONG);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	return EnumORWindows (pK);
}

// DEX_ENUMSELECTEDOBJECTSEX: alle recherchierten Objekte enumerieren -----------
LRESULT ExtDirisWindow :: OnEnumSelObjectsEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEYEX *pK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

// entweder alle ORFenster (eKey == NULL oder gültiges ORFenster
	TX_ASSERT(NULL == pK -> eKey || 
	         (IsWindow((HWND)pK -> eKey) && NULL != GetORWindow((HWND)pK -> eKey)));

	return (LRESULT)EnumSelectedObjectsEx (
			(ENUMNOKEYLONGEXPROC)pK -> eFcn, pK -> ePtr, 
			pK -> eData, (HWND)pK -> eKey
		);
}

// DEX_QUERYIDENTOBJTYPESACTVIEW: liefert Objekttypen eines Idents in der aktuellen Ansicht
LRESULT ExtDirisWindow :: OnGetIdentObjTypesActView (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

return DBO().GetActIdentObjTypes (lParam);
}

// DEX_CAPTIONREREAD: Caption neu generieren ----------------------------------
LRESULT ExtDirisWindow :: OnReReadCaption (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

return ReReadCaption();
}

// DEX_GETGEODBDIRTY: Abfragen, ob gespeichert werden muß ---------------------
LRESULT ExtDirisWindow :: OnIsGeoDBDirty (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

return LRESULT(DBO().DB().isDirty());
}

// DEX_QUERYLEGENDACTIVE
LRESULT ExtDirisWindow :: OnIsLegendActive (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

return LRESULT(LegendeCFlag);
}

// DEX_MODACTVIEWCONTAINER
LRESULT ExtDirisWindow :: OnSetViewContainer (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	if (0L != lParam) {
		TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
		return (EC_OKAY == DBO().SetActSichtCont (*(ObjContainer *)lParam));
	}

return (EC_OKAY == DBO().DelActSichtCont());
}

// DEX_QUERYACTVIEWCONTAINER
LRESULT ExtDirisWindow :: OnGetViewContainer (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	if (0L != lParam) {
		TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), false));
		return (EC_OKAY == DBO().GetActSichtCont ((ObjContainer *)lParam));
	}

return (LRESULT)DBO().hasSichtCont();
}

#if defined(WIN32)

// DEX_ADDUNDOREDOITEM
LRESULT ExtDirisWindow :: OnAddUndoRedo (LPARAM lParam)
{
	TX_ASSERT(TIsValidIUnknown((LPUNKNOWN)lParam));
	return (LRESULT)m_pUndoRedo -> AddUndo ((LPUNKNOWN)lParam);
}

// DEX_UNDOLEVELBEGIN 
LRESULT ExtDirisWindow :: OnBeginUndoLevel (LPARAM lParam)
{
	TX_ASSERT(TIsValidString((char *)lParam));
	return (LRESULT)m_pUndoRedo -> BeginUndoLevel ((LPCTSTR)lParam);
}

// DEX_UNDOLEVELEND 
LRESULT ExtDirisWindow :: OnEndUndoLevel (LPARAM)
{
	return (LRESULT)m_pUndoRedo -> EndUndoLevel();
}

// DEX_UNDOLEVELCANCEL
LRESULT ExtDirisWindow :: OnCancelUndoLevel (LPARAM lParam)
{
	return (LRESULT)m_pUndoRedo -> CancelUndoLevel (lParam ? true : false);
}

// DEX_QUERYCANUNDO
LRESULT ExtDirisWindow :: OnQueryCanUndo (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(S_FALSE);

	TX_ASSERT(NULL != m_pUndoRedo);

LPSTR pDesc = NULL;
HRESULT hr = S_FALSE;

	if (m_pUndoRedo -> GetNextUndoDesc(&pDesc) & UNDOREDOCAPS_CANUNDO) {
		if (0L != lParam) {
		LPSTR pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

			TX_ASSERT(TIsValidAddress((LPSTR)lParam, strlen(pAnsi), false));
			if (pAnsi) strcpy ((LPSTR)lParam, pAnsi);
			else	   strcpy ((LPSTR)lParam, ResString (IDS_UNDOUNKNOWN, 30));
		}
		hr = NOERROR;
	}
	if (pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

return LRESULT(hr);
}

// DEX_QUERYCANREDO
LRESULT ExtDirisWindow :: OnQueryCanRedo (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(S_FALSE);

	TX_ASSERT(NULL != m_pUndoRedo);

LPSTR pDesc = NULL;
HRESULT hr = S_FALSE;

	if (m_pUndoRedo -> GetNextRedoDesc(&pDesc) & UNDOREDOCAPS_CANREDO) {
		if (0L != lParam) {
		LPSTR pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

			TX_ASSERT(TIsValidAddress((LPSTR)lParam, strlen(pAnsi), false));
			if (pAnsi) strcpy ((LPSTR)lParam, pAnsi);
			else	   strcpy ((LPSTR)lParam, ResString (IDS_UNDOUNKNOWN, 30));
		}
		hr = NOERROR;
	}
	if (pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

return LRESULT(hr);
}

// DEX_N_SAVESAMESTORAGE
LRESULT ExtDirisWindow :: OnSaveSameStorage (LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_SAVEOTHERSTORAGE
LRESULT ExtDirisWindow :: OnSaveOtherStorage (LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_HANDSOFFSTORAGE
LRESULT ExtDirisWindow :: OnHandsOffStorage (LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_SAVECOMPLETED
LRESULT ExtDirisWindow :: OnSaveCompleted (LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_ATTACHPRETRANSLATEMSGPROC
LRESULT ExtDirisWindow :: OnAttachPreTranslateMsgProc (LPARAM lParam)
{
	return (LRESULT)CurrApp -> AttachPreTranslateProc ((bool (*)(MSG *))lParam);
}

// DEX_ATTACHIDLEPROC
LRESULT ExtDirisWindow :: OnAttachIdleProc (LPARAM lParam)
{
	return (LRESULT)CurrApp -> AttachIdleProc ((bool (*)(LONG))lParam);
}

LRESULT ExtDirisWindow :: OnQueryActViewWindow (LPARAM)
{
	if (!IsValidActiveView())
		return LPARAM(NULL);

return LRESULT(m_pView -> Handle (API_WINDOW_HWND));
}

// DEX_MODOBJIDENTEX: Ident eines Objektes ändern (mit Undo) ------------------
LRESULT ExtDirisWindow :: OnModObjectIdentEx (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
MODOBJIDENT *pMOI = (MODOBJIDENT *)lParam;

	TX_ASSERT_POINTER(pMOI, MODOBJIDENT);
	TX_ASSERT(3*sizeof(long) == pMOI -> dwSize || sizeof(MODOBJIDENT) == pMOI -> dwSize);
	TX_ASSERT(IsValidONr(pMOI -> lONr));
	TX_ASSERT(IsValidIdent(pMOI -> lNewIdent));

short iMode = pMOI -> dwSize > 3*sizeof(long) ? pMOI -> iMode : 0;
LPUNDOREDOMODIDENT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoModIdent, (LPVOID *)&pIUndo);
bool fResult = false;

	if (SUCCEEDED(hr)) 
		hr = pIUndo -> Init (pMOI -> lONr, pMOI -> lNewIdent, 0L, iMode);

	DBO().DB().SetDirty();
	if (DBO().ModIdent (pMOI -> lONr, pMOI -> lNewIdent, -1, iMode)) {
		if (hr == NOERROR)
			DEX_AddUndoRedo (pIUndo);
		fResult = true;
	} 
	if (pIUndo) pIUndo -> Release();

return fResult;
}

// DEX_QUERYOBJECTPROPS
LRESULT ExtDirisWindow :: OnGetObjectProps (LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(E_UNEXPECTED);

	TX_ASSERT(TIsValidAddress ((void *)lParam, sizeof(IUnknown *), true));
	
	return (LPARAM)m_pEL -> QueryInterface (IID_IObjectProps, (LPVOID *)lParam);
}

// DEX_SETSTRINGMESSAGE
#define WM_SETMESSAGESTRING	0x362	// AFXPRIV.H

LRESULT ExtDirisWindow :: OnSetMessageString (LPARAM lParam)
{
// an MFC (FakeMFC) weiterleiten
	return ::SendMessage (Handle(API_WINDOW_HWND), WM_SETMESSAGESTRING, 0, lParam);
}

#endif // WIN32

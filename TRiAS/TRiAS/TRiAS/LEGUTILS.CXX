// Routinen für Verwaltung der LegendenMerkmale für LegendenStruktur ----------
// File: LEGUTILS.CXX

#include "triaspre.hxx"

#include "strings.h"

#include <FormatString.h>
#include <Com/PropertyHelper.h>
#include <Com/Mkhelper.h>

#include "ExtMain3.hxx"
#include "legdinfo.hxx"	// KlassenDeklarationen
#include "legdinfo.inl"	// Inline-Funktionen


#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperties);		// WTRiASProperties
DefineSmartInterface(TRiASProperty);		// WTRiASProperty
DefineSmartInterface(TRiASView);			// WTRiASView

/////////////////////////////////////////////////////////////////////////////
// Neuer Wrapper für GetHeaderMCode + ReadTextMerkmal(TT_View)
HRESULT DatenBasisObjekt::GetNamedViewProperty (NAMEDVIEWPROPERTY *pNVP)
{
// zu betrachtende Ansicht 
LPCSTR pcView = pNVP -> pcView;
string strView;

	if (NULL == pcView) {
	char cbBuffer[_MAX_PATH];
	
		if (NULL == DEX_GetActiveSight(cbBuffer))
			return -1L;
		strView = cbBuffer;
	} else
		strView = pcView;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// MerkmalsCode aus Header lesen
	long lMCode = GetHeaderMCode (false, pNVP -> pcName);

		if (!IsValidMCode(lMCode)) return NULL;

	// SichtMerkmal einlesen
		if (ReadTextMerkmal (TT_Sicht, (long)strView.c_str(), lMCode, pNVP -> pBuffer, pNVP -> iLen))
		{
			if (pNVP -> pBuffer) 
				pNVP -> iLen = strlen (pNVP -> pBuffer);
			else
				pNVP -> iLen = 0;
			return S_OK;
		}
		pNVP -> iLen = 0;
		return E_FAIL;	// nichts vorhanden
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen
	WTRiASView View;

		if (FAILED(m_Prj -> get_View (CComBSTR(strView.c_str()), VARIANT_FALSE, View.ppi())))
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	// alle Properties der Ansicht abfragen
	CComBSTR bstrText (g_cbNil);

		bstrText = GetPropertyFrom (View, pNVP -> pcName, bstrText);

	int iStrLen = bstrText.Length();			// grundsätzlich Textlänge liefern
	int iToCopy = min ((size_t)iStrLen, (size_t)(pNVP -> iLen-1));

		pNVP -> iLen = iToCopy;
		if (NULL != pNVP -> pBuffer && iToCopy > 0) {
			USES_CONVERSION;
			strncpy (pNVP -> pBuffer, OLE2A(bstrText), iToCopy);
			pNVP -> pBuffer[iToCopy] = '\0';
		} else 
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::SetNamedViewProperty (NAMEDVIEWPROPERTY *pNVP)
{
// zu betrachtende Ansicht 
LPCSTR pcView = pNVP -> pcView;
string strView;

	if (NULL == pcView) {
	char cbBuffer[_MAX_PATH];
	
		if (NULL == DEX_GetActiveSight(cbBuffer))
			return -1L;
		strView = cbBuffer;
	} else
		strView = pcView;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// MerkmalsCode aus Header lesen
	long lMCode = GetHeaderMCode ((NULL != pNVP -> pBuffer) ? TRUE : FALSE, 
			pNVP -> pcName, pcView, pNVP -> pcShort, pNVP -> pcDesc);

		if (!IsValidMCode(lMCode)) return NULL;

	// SichtMerkmal einlesen
		if (WriteTextMerkmal (TT_Sicht, (long)strView.c_str(), lMCode, pNVP -> pBuffer))
			return S_OK;
		return E_FAIL;	// irgendwie fehlgeschlagen
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen, evtl neu erzeugen (VisImport)
	WTRiASView View;

		RETURN_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(strView.c_str()), VARIANT_TRUE, View.ppi()));

	// alle Properties der Ansicht abfragen
	WTRiASProperties Props;

		RETURN_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

	// entweder Wert setzen/neu erzeugen oder löschen
		if (NULL != pNVP -> pBuffer) {
		WTRiASProperty Prop;
		CComVariant vKey (pNVP -> pcName);
		HRESULT hr = Props -> Item (vKey, Prop.ppi());
		bool fCreated = false;

			if (FAILED(hr))	{	// evtl. neu erzeugen
				hr = Props -> Add (vKey, Prop.ppi());
				fCreated = true;
			}
			if (SUCCEEDED(hr)) {			// Wert setzen
			CComVariantEx vVal(pNVP -> pBuffer, LOCALE_ENGLISH);

				if (!V_ISUNKNOWN(&vVal) && !V_ISDISPATCH(&vVal)) {
					hr = vVal.ChangeTypeEx(VT_BSTR);
					TX_ASSERT(SUCCEEDED(hr));
				}

			// versuchen, die Zeichenkette als Moniker zu binden
				{
				__Interface<IBindCtx> ctx;
				__Interface<IMoniker> mk;
				ULONG ulEaten = 0;

					RETURN_FAILED_HRESULT(::CreateBindCtx (0, ctx.ppi()));
					if (SUCCEEDED(MkParseDisplayName (ctx, V_BSTR(&vVal), &ulEaten, mk.ppi()))) {
#if defined(_DEBUG)
					// kleiner Test für den Monikercode
					CComBSTR bstrTst;

						RETURN_FAILED_HRESULT(MkGetDisplayName (mk, &bstrTst, ctx));
						_ASSERTE(!wcscmp (V_BSTR(&vVal), bstrTst));
#endif // defined(_DEBUG)
					__Interface<IDispatch> disp;

						if (SUCCEEDED(MkBindToObject (mk, disp.ppi(), NULL, ctx))) {
						CComVariant vDisp (disp);

							RETURN_FAILED_HRESULT(vDisp.Detach (CLEARED(&vVal)));
						}
					}
				}
							
			// Property jetzt schreiben
				RETURN_FAILED_HRESULT(Prop -> put_Value (vVal));
				if (fCreated) {
				LPCSTR pcDesc = pNVP -> pcDesc;

					if (NULL == pcDesc)
						pcDesc = pNVP -> pcShort;
					if (NULL != pcDesc)
						RETURN_FAILED_HRESULT(Prop -> put_Description (CComBSTR(pcDesc)));
				}
			}
			return hr;

		} else {
			RETURN_FAILED_HRESULT(DelProperty (Props, pNVP -> pcName));
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
//
#define MCODESIZE	20

long DatenBasisObjekt::GetHeaderMCode (
	bool fGenerate, UINT resID, LPCSTR pView, UINT uiResKT, UINT uiResLT)
{
	if (0 != uiResKT && 0 != uiResLT) {
	ResString resKT (uiResKT, 33);
	ResString resLT (uiResLT, _MAX_PATH);

		return GetHeaderMCode (fGenerate, ResString(resID, 17).Addr(), pView, resKT.Addr(), resLT.Addr()); 
	}

// evtl. kein Langtext gegeben
	if (0 != uiResKT) {
	ResString resKT (uiResKT, 33);

		_ASSERTE(0 == uiResLT);
		return GetHeaderMCode (fGenerate, ResString(resID, 17).Addr(), pView, resKT.Addr()); 
	}

// auch kein Kurztext gegeben
	return GetHeaderMCode (fGenerate, ResString(resID, 17).Addr(), pView); 
}

long DatenBasisObjekt::GetHeaderMCode (
	bool fGenerate, LPCSTR pcName, LPCSTR pView, LPCSTR pcShort, LPCSTR pcLong)
{
GEODBHDRENTRY hdrEntry;
long result = -1L;

	INITSTRUCT(hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, pcName, 16);
	hdrEntry.lphdrText = NULL; ATLTRY(hdrEntry.lphdrText = new char [MCODESIZE +1]);
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
		if (result == 0L) result = -1L;
	} else if (fGenerate) {
	// bei Bedarf neu generieren
	long lMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (lMCode != -1) {		// und wegschreiben
			hdrEntry.hdrTextLen = MCODESIZE;
			ltoa (lMCode, hdrEntry.lphdrText, 10);

			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY)
				result = lMCode;
		// in Pbd eintragen
			SaveViewMCodeInPbd (pView, lMCode, pcShort, pcLong);
		}
	}
	DELETE_OBJ (hdrEntry.lphdrText);
	return result;
}

INT_PTR DatenBasisObjekt::FindMCodeFromKText (LPCSTR pcView, UINT uiResID)
{
	_ASSERTE(NULL != pcView);

	if (0 == uiResID) 
		uiResID = IDS_LEGINFOKURZTEXT;		// Notanker

os_string strKText;
ResString resTmpl(uiResID, 128);

	Format (strKText, resTmpl, pcView);
	return DEX_GetMCodeFromFeatureName(strKText.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Für eine bestimmte Sicht MCode für Objekte besorgen 
long DatenBasisObjekt::GetObjMCodeView (
	bool fGenerate, LPCSTR pView, long lVMCode, uint uiResKT, uint uiResLT, INT_PTR lONr)
{
string strView;

	if (NULL == pView) {
	char cbBuffer[_MAX_PATH];
	
		if (NULL == DEX_GetActiveSight(cbBuffer))
			return -1L;
		strView = cbBuffer;
	} else
		strView = pView;

TARGETMERKMAL gm;
long result = -1L;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)strView.c_str();
	gm.lMCode = lVMCode;
	gm.imaxLen = MCODESIZE;
	gm.pMText = NULL; ATLTRY(gm.pMText = new char [MCODESIZE+1]);
	gm.iTTyp = TT_Sicht;

	if (DEX_GetTextMerkmal (gm) != NULL) {
		if (gm.pMText)
			result = atol (gm.pMText);
		_ASSERTE(0 != result);

		if (0 != lONr)		// Objekt hinzufügen muß Pbd schreiben
			SaveObjMCodeInPbd (strView.c_str(), result, uiResKT, uiResLT, lONr);

	} else if (fGenerate) {
	// Feststellen, ob bereits ein derartiger MCode vergeben wurde
	long lMCode = FindMCodeFromKText (pView, uiResKT);

	// neu generieren
		if (-1 == lMCode || 0 == lMCode)
			lMCode = DEX_GetUniqueSysMCode();
	
		if (lMCode != -1 && gm.pMText) {	// und wegschreiben
			ltoa (lMCode, gm.pMText, 10);
			gm.imaxLen = MCODESIZE;

			if (EC_OKAY == DEX_ModTextMerkmal(gm)) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
				SaveObjMCodeInPbd (strView.c_str(), result, uiResKT, uiResLT, lONr);
			}
		}
	}
	DELETE_OBJ (gm.pMText);
	return result;
}

///////////////////////////////////////////////////////////////////////////////
// Für eine bestimmte Sicht MCode für Idents besorgen 
long DatenBasisObjekt::GetIdentMCodeView (
	bool fGenerate, LPCSTR pcView, long lVMCode, uint uiResKT, uint uiResLT)
{
	return GetObjMCodeView (fGenerate, pcView, lVMCode, uiResKT, uiResLT);
}
///////////////////////////////////////////////////////////////////////////////
// Eintrag für ObjMCode in PBD generieren 
bool DatenBasisObjekt::SaveObjMCodeInPbd (LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2, INT_PTR lONr)
{
	if (0 == uiRes1) uiRes1 = IDS_LEGINFOKURZTEXT;		// Notanker
	if (0 == uiRes2) uiRes2 = IDS_LEGINFOLANGTEXT;

// an Ansicht wegspeichern
	return SaveViewMCodeInPbd (pView, lMCode, uiRes1, uiRes2, lONr);
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für IdentMCode in PBD generieren 
bool DatenBasisObjekt::SaveIdentMCodeInPbd (LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2)
{
	return SaveViewMCodeInPbd (pView, lMCode, uiRes1, uiRes2);
}

///////////////////////////////////////////////////////////////////////////////
// Eintrag für ViewLegMCode in PBD generieren 
bool DatenBasisObjekt::SaveViewMCodeInPbd (
	LPCSTR pView, long lMCode, uint uiRes1, uint uiRes2, INT_PTR lONr)
{
ResString KFormat (uiRes1, 32);
ResString LFormat (uiRes2, _MAX_PATH);

	return SaveViewMCodeInPbd (pView, lMCode, KFormat, LFormat, lONr);
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Eintrag in der Pbd existiert
bool IsNotInPbd (long lMCode, long lIdent)
{
PBDMERKMALEX TM;

	if (0 != lIdent) {
		INITSTRUCT(TM, PBDMERKMALEX);
	} else {
		INITSTRUCT(TM, PBDMERKMAL);
	}
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.lIdent = lIdent;
	return (EC_OKAY == DEX_GetPBDData(TM)) ? false : true;
}

bool DatenBasisObjekt::SaveViewMCodeInPbd (
	LPCSTR pView, long lMCode, LPCSTR pcShort, LPCSTR pcLong, INT_PTR lONr)
{
	_ASSERTE(NULL != pcShort);

bool iResult = true;

// PBDEintrag zusammenstellen
const char *pLocView = pView ? pView : g_cbNil;
os_string strLText;

	if (NULL != pcLong)
		Format (strLText, pcLong, pLocView);

#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	string strKText;
	PBDMERKMAL TM;

		Format (strKText, pcShort, pLocView);
		INITSTRUCT(TM, PBDMERKMAL);
		TM.pbdTyp = 'm';
		TM.pbdCode = lMCode;
		TM.pbdKText = (strKText.size()) > 0 ? (LPSTR)strKText.c_str() : NULL;
		TM.pbdLText = (strLText.size()) > 0 ? (LPSTR)strLText.c_str() : NULL;	
		TM.pbdKTextLen = strKText.size();
		TM.pbdLTextLen = strLText.size();
		TM.ipbdMTyp = 'b' | PBDMERKMAL_SYSTEMFLAG;
		TM.ipbdMLen = 256;
		{
		ErrInstall EI (WC_NOMERKMAL);

			if (DEX_ModPBDData (TM) != EC_OKAY)
				iResult = false;
			else
				DEXN_PBDMCodeChanged (lMCode);
		}
	} else
#endif // defined(_USE_LEGACY_CODE)
	{
		TX_ASSERT(IsTRiASDBBased());

	// evtl. als unsichtbares Merkmal in Pbd schreiben
		if (0 != lONr) {
		INT_PTR lIdent = DEX_GetObjIdent(lONr);
	
			if (IsNotInPbd(lMCode, lIdent)) {
			os_string strKText;
			PBDMERKMALEX TM;

				Format (strKText, pcShort, pLocView);
				INITSTRUCT(TM, PBDMERKMALEX);
				TM.pbdTyp = 'm';
				TM.pbdCode = lMCode;
				TM.pbdKText = (strKText.size()) > 0 ? (LPSTR)strKText.c_str() : NULL;
				TM.pbdLText = (strLText.size()) > 0 ? (LPSTR)strLText.c_str() : NULL;	
				TM.pbdKTextLen = strKText.size();
				TM.pbdLTextLen = strLText.size();
				TM.ipbdMTyp = 'a' | PBDMERKMAL_SYSTEMFLAG|PBDMERKMAL_READONLY;	// Sichtmerkmal und systemintern
				TM.ipbdMLen = 256;
				TM.lIdent = lIdent;
				{
				ErrInstall EI (WC_NOMERKMAL);

					if (EC_OKAY == DEX_ModPBDData (TM))
						DEXN_PBDMCodeChanged (lMCode);
				}
			}
		}

	// an Ansicht wegschreiben
		if (NULL != pView) {
		// Ansicht besorgen
		WTRiASView View;

			RETURN_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;
		char cbBuffer[_MAX_PATH];

			RETURN_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			wsprintf (cbBuffer, g_cbSysProperty, lMCode);

		// Setzen der Beschreibungsinfo für diese Property
		WTRiASProperty Prop;
		CComVariant vKey (cbBuffer);

			if (FAILED(Props -> Item (vKey, Prop.ppi()))) 
			{
				RETURN_FAILED_HRESULT(Props -> Add (vKey, Prop.ppi()));
				RETURN_FAILED_HRESULT(Prop -> put_Value (CComVariant(g_cbNil)));
			}
			if (strLText.size() > 0)
			{
				RETURN_FAILED_HRESULT(Prop -> put_Description(CComBSTR(strLText.c_str())));
			}
		}
	}
	return iResult;
}

///////////////////////////////////////////////////////////////////////////////
// Legende rücksetzen 
extern "C" 
BOOL EXPORTTRIAS WINAPI HandleIdentOnResetLegend (long lIdent, BOOL, void *pData)
{
// Idents selbst behandeln (Merkmal löschen)
	WriteTextMerkmal (TT_Identifikator, lIdent, *(long *)pData, NULL);
	return true;	// immer weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// LegInfo an Objekt löschen 
extern "C" 
BOOL EXPORTTRIAS WINAPI HandleObjectOnResetLegend (long lONr, BOOL, void *pData)
{
short Status = DEX_GetObjectStatus (lONr);

	if (Status == OSNormal || Status == OSModified) 
	// Objekt existiert und ist nicht temporär: VisInfoMerkmal löschen	
		WriteTextMerkmal (TT_Objekt, lONr, *(long *)pData, NULL);
	return true;
}

bool DatenBasisObjekt::ResetLegend (LPCSTR pcView, INT_PTR lVMCode)
{
	if (0 == lVMCode)
		lVMCode = GetHeaderMCode (false, IDS_LEGENDINFOMCODE); 

	if (-1 == lVMCode || 0 == lVMCode)
		return true;	// keine Zusatzinfos vorhanden

long lMCode = GetObjMCodeView (false, pcView, lVMCode);

	if (-1 == lMCode) 
		return true;	// in dieser Sicht nichts
	
// Alle Identifikatoren dieser Sicht enumerieren
ENUMTEXTKEY ETK;

	ETK.eKey = const_cast<char *>(pcView);
	ETK.eFcn = (ENUMTEXTKEYPROC)HandleIdentOnResetLegend;	
	ETK.ePtr = &lMCode;
	DEX_EnumSightIdents (ETK);

// Alle Objekte mit diesem MerkmalsCode enumerieren und Merkmal löschen
ENUMRECHTEXTMERKMAL ERTM;

	ERTM.dwSize = sizeof(ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;	// es können nur Objekte einer Sicht sein
	ERTM.lMCode = lMCode;
	ERTM.pMWert = NULL;	// alle Objekte
	ERTM.iMode = 0;
	ERTM.eFcn = HandleObjectOnResetLegend;
	ERTM.pData = &lMCode;
	DEX_EnumRechTextMerkmal (ERTM);

// an Sicht Merkmal löschen
	WriteTextMerkmal (TT_Sicht, HGENERIC(pcView), lVMCode, NULL);

// alle Zwischenüberschriften löschen
char *pBuffer = NULL;
int iLen = 0;

	if (GetTextMerkmalLen(TT_Sicht, HGENERIC(pcView), lMCode, iLen))
		pBuffer = new char [iLen+1];

	if (NULL != pBuffer && 
		ReadTextMerkmal (TT_Sicht, HGENERIC(pcView), lMCode, pBuffer, iLen)) 
	{
	CLegendInfo::CMCodes MCodes;

		CLegendInfo::ExtractMCodes (pBuffer, MCodes);
		for (CLegendInfo::CMCodes::iterator it = MCodes.begin(); it != MCodes.end(); ++it) 
			WriteTextMerkmal(TT_Sicht, HGENERIC(pcView), *it, NULL);
		WriteTextMerkmal(TT_Sicht, HGENERIC(pcView), lMCode, NULL);
	}
	DELETE_OBJ(pBuffer);

// da wir nicht mehr wissen, zu welchem Ident das Ganze gehört
// lassen wir den Eintrag einfach in der Pbd drin (:-))
#if defined(_FORCE_LEGACY_CODE)	
// in PBD Merkmal löschen
PBDDATA TM;

	memset (&TM, '\0', sizeof(PBDDATA));
	TM.dwSize = sizeof(PBDDATA);
	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	{
	ErrInstall EI (WC_NOMERKMAL);

		DEX_DelPBDData (TM);
		DEXN_PBDMCodeChanged (lMCode);
	}
#endif // _FORCE_LEGACY_CODE

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen der Länge eines Merkmales
bool GetTextMerkmalLen (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, int &riLen, LPCSTR pcView)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = 0;
	gm.pMText = NULL;
	gm.iTTyp = iTTyp;
	gm.iFlags = 0;
	gm.pcView = pcView;

	riLen = 0;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

	riLen = gm.imaxLen+1;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Lesen eines Merkmales
bool ReadTextMerkmal (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, char *pText, int iLen, LPCSTR pcView)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? iLen : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	gm.iFlags = 0;
	gm.pcView = pcView;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Schreiben eines Merkmales
bool WriteTextMerkmal (short iTTyp, HGENERIC lTarget, HFEATURE lMCode, const char *pText, int iFlags, LPCSTR pcView)
{
TARGETMERKMALEX gm;

	INITSTRUCT(gm, TARGETMERKMALEX);
	gm.lTarget = lTarget;
	gm.lMCode = lMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = const_cast<char *>(pText);
	gm.iTTyp = iTTyp;
	gm.iFlags = iFlags;
	gm.pcView = pcView;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;
	return true;
}


// BehandlungsRoutinen für HANDLEVISINFO --------------------------------------
HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp)
{
HANDLEVISINFO *pHVI = new HANDLEVISINFO;
VISINFO *pVI = NULL;

	if (pHVI == NULL) return NULL;
	
	switch (iVTyp) {
	case VTPunkt:
		pVI = (VISINFO *)new PVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(PVISINFO));
			pVI -> dwSize = sizeof(PVISINFO);
		}
		break;
		
	case VTLinie:
		pVI = (VISINFO *)new LVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(LVISINFO));
			pVI -> dwSize = sizeof(LVISINFO);
		}
		break;
		
	case VTFlaeche:
		pVI = (VISINFO *)new FVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(FVISINFO));
			pVI -> dwSize = sizeof(FVISINFO);
		}
		break;
		
	case VTText:
		pVI = (VISINFO *)new TVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(TVISINFO));
			pVI -> dwSize = sizeof(TVISINFO);
		}
		break;

	default:
	case VTDefault:
		pVI = (VISINFO *)new DVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(DVISINFO));
			pVI -> dwSize = sizeof(DVISINFO);
		}
		break;
	}
	if (pVI == NULL) {
		DELETE_OBJ (pHVI);
		return NULL;
	}

	pVI -> m_fVisible = true;
	pVI -> m_fLocatable = true;

	memset (pHVI, '\0', sizeof(HANDLEVISINFO));
	pHVI -> dwSize = sizeof (HANDLEVISINFO);
	pHVI -> m_iVTyp = iVTyp;
	pHVI -> m_pVI = pVI;
	return pHVI;
}

// Destruktor für HANDLEVISINFO -----------------------------------------------
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI)
{
	if (pHVI) {
		DELETE_OBJ (pHVI -> m_pVI);
		DELETE_OBJ (pHVI -> m_pView);
		DELETE_OBJ (pHVI -> m_pDesc);
		DELETE_OBJ (pHVI);
	}
}

// VisualisierungsInfo für einen Identifikator/Typ besoregn -------------------
HANDLEVISINFO *GetIdentVisInfo (long lIdent, short iVTyp, char *pView)
{
// typgerechte VISINFO-Struktur anfordern
HANDLEVISINFO *pHVI = ctHANDLEVISINFO (iVTyp);

	if (pHVI == NULL) return NULL;

// Strukturen füllen
	pHVI -> m_pView = pView;
	pHVI -> m_lIdent = lIdent;
	
	if (!DEX_GetIdentVisInfo (*pHVI)) 	// Fehler aufgetreten
		dtHANDLEVISINFO (pHVI);
	
return pHVI;
}


// Visinfo für einen Ident neu einstellen -------------------------------------
bool DefineNewIdentVisInfo (long lIdent, short iVTyp, bool fHSB)
{
	if (!IsValidIdent(lIdent) || iVTyp == VT_Default)
		return false;	// falsche Parameter
		
// aktuelle VisInfo für Ident/Typ besorgen (StandardVisualisierung)
HANDLEVISINFO *pHVI = GetIdentVisInfo (lIdent, iVTyp, NULL);

	if (pHVI == NULL) return false;	// Fehler

	if (fHSB) pHVI -> m_fFlags |= DF_HSBModel;

// DialogFenster zur VisInfoEinstellung anfordern
short iResult = false;

// IdentKurzText besorgen
PBDDATA pbdData;
char pKText[33];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;

ErrCode RC = DEX_GetPBDData (pbdData);

	if (EC_OKAY != RC && WC_RETURN != RC)
		ClassFromIdent (lIdent, pKText, sizeof(pKText));
		
	pKText[32] = '\0';
	pHVI -> m_pDesc = pKText;	// Überschrift der DialogBox setzen
	
	if (DEX_ModVisInfoDialog (*pHVI) == EC_OKAY && DEX_ModIdentVisInfo (*pHVI))
		iResult = true;
		
	pHVI -> m_pDesc = NULL;		// Verhindern, daß gelöscht wird
	dtHANDLEVISINFO (pHVI);		// Speicher freigeben
		
	return iResult;	// ok, error handled
}

// Besorgen des Kurz/Langtextes aus der PBD -----------------------------------
bool HasSpacesOnly (LPCSTR pcText)
{
	while (*pcText) {
		if (!isspace(*pcText))
			return false;
		pcText++;
	}
	return true;		// besteht nur aus spaces
}

char *GetPBDText (long lIdent, char *pText, int iLen)
{
	if (!IsValidIdent(lIdent)) return NULL;

PBDDATA pbdData;
char pKText[34];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;
	pbdData.pbdLText = pText;
	pbdData.pbdLTextLen = pText ? iLen-1 : 0;

ErrCode RC = DEX_GetPBDData (pbdData);

	if (EC_OKAY != RC && WC_RETURN != RC) 
		return NULL;

	pKText[32] = '\0';
	if (pbdData.pbdLTextLen <= 0 || HasSpacesOnly(pbdData.pbdLText))
		strcpy (pText, pKText);		// kein LangText (oder leer) --> Kurztext

	return pText;
}		


// @doc
// @module DBOMerkmal.cpp | Zugriff auf alles, was Merkmale betrift

#include "TriasPre.hxx"

#include <stdio.h>			// sscanf
#include "TRiASRes.h"
#include "Strings.h"

#if defined(_FORCE_LEGACY_CODE)
#include <konsobj.hxx>
#endif // defined(_FORCE_LEGACY_CODE)

#include <NativeObject.h>	// BRELA etc.

#include <Com/PropertyHelper.h>
#include <Com/VariantHelpers.h>
#include <Com/ComBool.h>

#include <iunredo.hxx>
#include <undoguid.h>

#include "TRiASUtil.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// globale Variablen et.al.
#if defined(_DEBUG) && !defined(WIN16) && _TRiAS_VER < 0x0400
extern short g_iKonsFlags;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperty);		// WTRiASProperty
DefineSmartInterface(TRiASProperties);		// WTRiASProperties
DefineSmartInterface(TRiASFeature);			// WTRiASFeature
DefineSmartInterface(TRiASView);			// WTRiASView
DefineSmartInterface(TRiASViewItem);		// WTRiASViewItem
DefineSmartInterface(TRiASFeatures);		// WTRiASFeatures
DefineSmartInterface(TRiASSimpleObject);
DefineSmartInterface(EnumVARIANT);			// WEnumVARIANT
DefineSmartInterface(Dispatch);				// WDispatch

DefineSmartInterface(UndoRedoCreateObjectRelation);
DefineSmartInterface(UndoRedoDeleteObjectRelation);

/////////////////////////////////////////////////////////////////////////////
// 
#if defined(_FORCE_LEGACY_CODE)
ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &rML);
#endif // defined(_FORCE_LEGACY_CODE)

/////////////////////////////////////////////////////////////////////////////
// 
FEATURETYPE BitsToFEATURETYPE (DWORD dwTypes)
{
FEATURETYPE rgType = FEATURETYPE(dwTypes & 0x7f);		// letzten 7 Bits sind 'a', 'b' oder 'c'

	if (dwTypes & MPSystemFeatures)
		rgType = FEATURETYPE(rgType | FEATURETYPE_System);
	if (dwTypes & MPReadOnlyFeatures)
		rgType = FEATURETYPE(rgType | FEATURETYPE_ReadOnly);
	if (dwTypes & MPAllFeatures)
		rgType = FEATURETYPE(rgType | FEATURETYPE_AllFeatures);
	if (dwTypes & MPPbdOnly)
		rgType = FEATURETYPE(rgType | FEATURETYPE_DefinitionOnly);

	return rgType;
}

/////////////////////////////////////////////////////////////////////////////
// 
#if defined(_USE_LEGACY_CODE)
LPCSTR RetrieveMiText (
	HPROJECT hPr, long lMCode, long lTarget, short iTTyp, 
	char *pMText, int &iMaxLen)
{
char *pT = NULL;
		
	GetMiText (hPr, lMCode, lTarget, iTTyp, &pT);
	if (pT) {
		if (pMText) {	// Merkmal extrahieren
			strncpy (pMText, pT, iMaxLen-1);
			pMText[iMaxLen -1] = '\0';
			iMaxLen = strlen (pT);
			delete pT;
			return pMText;
		} else {            	// nur Testen, ob Merkmal existiert
			iMaxLen = strlen (pT);
			delete pT;
			return (LPCSTR)TRUE;
		}
	}
	iMaxLen = -1;	// kein Merkmal
	return NULL;
}
#endif // defined(_USE_LEGACY_CODE)

LPCSTR DatenBasisObjekt::QueryTextMerkmal (HPROJECT hPr, TARGETMERKMAL *pTM)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
	long lTarget = GetTarget (DB().DBDesc(), (void *)pTM -> lTarget, pTM -> iTTyp);
	ErrInstall EI (WC_NOTFOUND);

		if (lTarget == -1) return NULL;
		
		switch (pTM -> iTTyp) {
		case TT_Objekt:
			{	// den ObjektMerkmalsCache befragen
				TX_ASSERT(IsValidONr(DB().DBDesc(), lTarget));

			CONrTable t(Shapes().ObjNumTree());

				if (NULL != pTM -> pMText && pTM -> imaxLen > 0)
					pTM -> pMText[0] = '\0';

				if (t.Find (&lTarget)) {
				ExtShapeObjectONrLock l(t);
				CFeature* pF = l -> FFindFeature (pTM -> lMCode);
				
					if (pF) {
						if (pTM -> pMText) {
							strncpy (pTM -> pMText, pF -> FText(), pTM -> imaxLen-1);
							pTM -> pMText[pTM -> imaxLen -1] = '\0';
							return pTM -> pMText;
						} else {
							pTM -> imaxLen = strlen (pF -> FText());
							return (LPCSTR)TRUE;
						}
					}
			// wenn Objekt nur temporär ist, dann hier aufhören
					if (l -> Status() == OS_Temp) 
						return (LPCSTR)TRUE;
			
			// Cache enthält dieses Merkmal noch nicht, also hinzufügen
				int iMaxLen = pTM -> imaxLen;
				LPCSTR lR = RetrieveMiText (DB().DBDesc(), 
						pTM -> lMCode, lTarget, pTM ->  iTTyp,
						pTM -> pMText, iMaxLen);

					pTM -> imaxLen = iMaxLen;
					if (lR && 
						(pTM -> dwSize == sizeof(TARGETMERKMAL) ||
						 !(((TARGETMERKMALEX *)pTM) -> iFlags & TMNoCaching)
						)
					   )
					{
						l -> FAddFeature (pTM -> lMCode, pTM -> pMText);
					}
					return lR;
				} else {
				// Objekt ist nicht geladen
				int iMaxLen = pTM -> imaxLen;
				LPCSTR pT = RetrieveMiText (DB().DBDesc(), pTM -> lMCode, lTarget, pTM ->  iTTyp, pTM -> pMText, iMaxLen);

					iMaxLen = pTM -> imaxLen;
					return pT;
				}
			}
	//		break;		// unreachable code
							
		case TT_Identifikator:
		case TT_Sicht:
			{
			int iMaxLen = pTM -> imaxLen;
			LPCSTR pT = RetrieveMiText (DB().DBDesc(), pTM -> lMCode, lTarget, pTM ->  iTTyp, pTM -> pMText, iMaxLen);

				iMaxLen = pTM -> imaxLen;
				return pT;
			}
		
		default:		// falscher MerkmalsTarget
			TX_ASSERT(false);
			break;
		}
		return FALSE;
	} else 
#endif // defined(_FORCE_LEGACY_CODE)
	{
	HRESULT hr = E_FAIL;

		TX_ASSERT(IsTRiASDBBased());
		switch (pTM -> iTTyp) {
		case TT_Objekt:
			hr = GetMiTextObject (pTM -> lTarget, pTM -> lMCode, pTM -> pMText, pTM -> imaxLen);
			if (SUCCEEDED(hr)) {
				if (NULL != pTM -> pMText)
					return pTM -> pMText;
				return (LPCSTR)TRUE;
			}
			break;
			
		case TT_Identifikator:
			{
			LPCSTR pcView = NULL;

				if (sizeof(TARGETMERKMALEX) == pTM -> dwSize)
					pcView = ((TARGETMERKMALEX *)pTM) -> pcView;
				hr = GetMiTextIdent (pcView, pTM -> lTarget, pTM -> lMCode, pTM -> pMText, pTM -> imaxLen);
				if (SUCCEEDED(hr)) {
					if (NULL != pTM -> pMText)
						return pTM -> pMText;
					return (LPCSTR)TRUE;
				}
			}
			break;
			
		case TT_Sicht:
			hr = GetMiTextSicht ((LPCSTR)pTM -> lTarget, pTM -> lMCode, pTM -> pMText, pTM -> imaxLen);
			if (SUCCEEDED(hr)) {
				if (NULL != pTM -> pMText)
					return pTM -> pMText;
				return (LPCSTR)TRUE;
			}
			break;

		default:		// falscher MerkmalsTarget
			TX_ASSERT(false);
			break;
		}
		::SetLastError(hr);
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Modifizieren eines Textmerkmales
ErrCode DatenBasisObjekt::ModTextMerkmal(HPROJECT hPr, TARGETMERKMAL *pMMK)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		if (HACTCONNECTION == hPr)
			hPr = DB().DBDesc();
	
	CActDB ActDB (DB());
	long lTarget = GetTarget (hPr, (void *)pMMK -> lTarget, pMMK -> iTTyp);
	ErrInstall EI (WC_NOTFOUND);
	ErrCode RC = EC_OKAY;
	
		if (lTarget == -1) {
			if (pMMK -> iTTyp != TT_Sicht) { 
				if (pMMK -> iTTyp != TT_Identifikator || 
					pMMK -> dwSize == sizeof(TARGETMERKMAL) ||
				    !(((TARGETMERKMALEX *)pMMK) -> iFlags & TMCreateNewTarget))
				{
					return WC_NOTFOUND;	// Fehler, Bezug gibt es nicht
				}
				DBASSERT(CreateTarget(hPr, pMMK -> iTTyp, pMMK -> lTarget, &lTarget));
			} else if (pMMK -> pMText && pMMK -> imaxLen >= 0) {
			// Sicht anlegen
				TX_ASSERT(TIsValidString ((char *)pMMK -> lTarget));
				return (S_OK == PutMiTextSicht ((LPCSTR)pMMK -> lTarget, pMMK -> lMCode, (LPSTR)pMMK -> pMText)) ? EC_OKAY : EC_FAIL;
			} else
				return WC_NOTFOUND;	// kann nichts löschen, wo es nichts zu löschen gibt
		}
		
		switch (pMMK -> iTTyp) {
		case TT_Objekt:
			{	// den ObjektMerkmalsCache befragen
				TX_ASSERT(IsValidONr(hPr, lTarget));
	
			CONrTable t(Shapes().ObjNumTree());
			
				if (t.Find (&lTarget)) {	// FeatureCache korrigieren
				ExtShapeObjectONrLock l(t);
	
				// Caching soll ggf. nicht erfolgen
					if (pMMK -> dwSize == sizeof(TARGETMERKMAL) ||
					    !(((TARGETMERKMALEX *)pMMK) -> iFlags & TMNoCaching) ||
					    OS_Temp == l -> Status()) 
					{
						l -> FDeleteFeature (pMMK -> lMCode);
						if ((pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) &&
						    (!l -> FAddFeature (pMMK -> lMCode, pMMK -> pMText)))
								return EC_NOMEMORY;
					} else
						l -> FDeleteFeature (pMMK -> lMCode);
	
				// wenn Objekt nur temporär ist, dann hier aufhören
					if (OS_Temp == l -> Status()) 
						break;
				}
								
			// in der DB nachführen
				DB().SetDirty();
				delmi (hPr, pMMK -> lMCode, lTarget, pMMK -> iTTyp);
				if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) {
					AnsiToOem (pMMK -> pMText, pMMK -> pMText);
					if (DB().TOMCode() == pMMK -> lMCode) {
						DBASSERT (PutMiText (hPr, pMMK -> lMCode, lTarget, pMMK -> iTTyp, pMMK -> pMText, TRUE));
					} else {
						DBASSERT (PutMiText (hPr, pMMK -> lMCode, lTarget, pMMK -> iTTyp, pMMK -> pMText, FALSE));
					}
				
				// Merkmals-Integrität testen
					TX_ASSERT(EC_OKAY == TestObjektMerkmal (DB(), lTarget, pMMK -> lMCode, g_iKonsFlags));
				} 
				else {	// alle Merkmale Testen, da eines gelöscht wurde
					TX_ASSERT(EC_OKAY == TestObjektMerkmalDeleted (DB(), lTarget, pMMK -> lMCode, g_iKonsFlags));
				}
	
				DEXN_FeatureModified (lTarget);		// Merkmal wurde modifiziert
			}
			break;
							
		case TT_Identifikator:
			TX_ASSERT(IsValidIdent (pMMK -> lTarget));
	
			DB().SetDirty();
			delmi (hPr, pMMK -> lMCode, lTarget, pMMK -> iTTyp);
			if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0) {
				AnsiToOem (pMMK -> pMText, pMMK -> pMText);
				DBASSERT (PutMiText (hPr, pMMK -> lMCode, lTarget, TT_Identifikator, pMMK -> pMText, FALSE));
	
			// Merkmals-Integrität testen
				TX_ASSERT(EC_OKAY == TestIdentMerkmal (DB(), pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
			}
			else {	// alle Merkmale Testen, da eines gelöscht wurde
				TX_ASSERT(EC_OKAY == TestIdentMerkmalDeleted (DB(), pMMK -> lTarget, pMMK -> lMCode, g_iKonsFlags));
			}
			break;
			
		case TT_Sicht:
			{
				TX_ASSERT(TIsValidString ((char *)pMMK -> lTarget));
				if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0)		// Merkmal schreiben
					return (S_OK == PutMiTextSicht ((LPCSTR)pMMK -> lTarget, pMMK -> lMCode, pMMK -> pMText)) ? EC_OKAY : EC_FAIL;
	
			// Merkmal löschen
				return (S_OK == DelMiTextSicht ((LPCSTR)pMMK -> lTarget, pMMK -> lMCode)) ? EC_OKAY : EC_FAIL;
			}
			break;
					
		default:		// falscher MerkmalsTarget
			TX_ASSERT(false);
			break;
		}
		return EC_OKAY;
	} else
#endif // defined(_FORCE_LEGACYCODE)
	{
	HRESULT hr = E_FAIL;

		TX_ASSERT(IsTRiASDBBased());
		switch (pMMK -> iTTyp) {
		case TT_Objekt:
			hr = PutMiTextObject (pMMK -> lTarget, pMMK -> lMCode, pMMK -> pMText);
			break;

		case TT_Identifikator:
			{
			LPCSTR pcView = NULL;

				if (sizeof(TARGETMERKMALEX) == pMMK -> dwSize)
					pcView = ((TARGETMERKMALEX *)pMMK) -> pcView;
				hr = PutMiTextIdent (pcView, pMMK -> lTarget, pMMK -> lMCode, pMMK -> pMText);
			}
			break;

		case TT_Sicht:
			{
				if (pMMK -> pMText != NULL && pMMK -> imaxLen >= 0)		// Merkmal schreiben
					hr = PutMiTextSicht ((LPCSTR)pMMK -> lTarget, pMMK -> lMCode, pMMK -> pMText);
				else 
					hr = DelMiTextSicht ((LPCSTR)pMMK -> lTarget, pMMK -> lMCode);
			}
			break;

		default:		// falscher MerkmalsTarget
			TX_ASSERT(false);
			break;
		}

		if (FAILED(hr)) {
			::SetLastError(hr);
			return EC_FAIL;
		}
		return EC_OKAY;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Merkmalsbehandlung für Objekte
HRESULT DatenBasisObjekt::PutMiTextObject (INT_PTR lONr, LONG lMCode, LPSTR pText)
{
HRESULT hr = S_OK;

	USES_CONVERSION;
	COM_TRY {
	// Feature von zugehöriger Objektklasse geben lassen
	WTRiASObject Obj;			// gesuchtes Objekt
	WTRiASFeature Feat;

		THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));
		if (FAILED(GetFeatureFromMap (lMCode, Feat))) {
		// Attribut neu erzeugen
		WTRiASObjects Objs;
		HOBJECTS hObjs = NULL;		// zugehörige Objektklasse

			THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
			THROW_FAILED_HRESULT(GetObjectsFromMap ((INT_PTR)hObjs, Objs));
			THROW_FAILED_HRESULT(Objs -> get_Feature (CComVariant(lMCode), VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));
		} 
		else {
		// Feststellen, ob das gefundene Feature wirklich der gewünschten Datenquelle entstammt
		HPROJECT hPrObj = NULL;
		HPROJECT hPrFeat = NULL;
		WDispatch Parent;

			THROW_FAILED_HRESULT(GetDatabaseHandle (Obj, &hPrObj, Parent.ppi()));
			THROW_FAILED_HRESULT(GetDatabaseHandle (Feat, &hPrFeat));
			if (hPrFeat != hPrObj) {
			// stimmt nicht überein, also in lokaler DatenBankMap suchen
			WTRiASObjectHandleMap locMap (GetPropertyFrom (Parent, g_cbFeatureMap, (IDispatch *)NULL), false);

				if (!locMap.IsValid() ||
					FAILED(locMap -> GetObjectEx (lMCode, OBJECTMAPMODE_GetObjectFromNativeHandle, Feat.ppu())))
				{
				// dieser MCode existiert nicht lokal in der GeoDB, muß neu erzeugt werden
				WTRiASObjects Objs;
				HOBJECTS hObjs = NULL;		// zugehörige Objektklasse

					THROW_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
					THROW_FAILED_HRESULT(GetObjectsFromMap ((INT_PTR)hObjs, Objs));
					THROW_FAILED_HRESULT(Objs -> get_Feature (CComVariant(lMCode), VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));

					DEXN_FeatureSetModified(hObjs);
				}
			}
		}

	// jetzt eigentliches Merkmal abfragen
	CComVariant vVal;
	
		V_VT(&vVal) = VT_NULL;
		if (NULL != pText)		// wenn Text gleich NULL, dann löschen
			vVal = pText;

		if (SUCCEEDED(hr = Feat -> Update (Obj, vVal))) {	// evtl. nicht beschreibbar
		// die Welt in Kenntnis setzen
		CComBSTR bstrName;
		FEATUREMODIFIED FM;

			THROW_FAILED_HRESULT(Feat -> get_Name(CLEARED(&bstrName)));

			INITSTRUCT(FM, FEATUREMODIFIED);
			FM.lONr = lONr;
			FM.pcName = OLE2A(bstrName);
			DEXN_FeatureModifiedEx (FM);		// Merkmal wurde modifiziert

		// Merkmal wurde modifiziert (alte Variante)
			DEXN_FeatureModified (lONr);
		}

	} COM_CATCH;
	return hr;
}

HRESULT DatenBasisObjekt::GetObjectFeatures (INT_PTR lONr, ITRiASFeatures **ppIFeats, ITRiASObject **ppIObj)
{
// Objekt besorgen
WTRiASObject Obj;			// gesuchtes Objekt
HOBJECTS hObjs = NULL;		// zugehörige Objektklasse
WTRiASObjects Objs;

	RETURN_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));
	RETURN_FAILED_HRESULT(Obj -> get_ObjectsHandle ((INT_PTR *)&hObjs));
	RETURN_FAILED_HRESULT(GetObjectsFromMap ((long)hObjs, Objs));

// Features evtl. vom Objekt selbst geben lassen
WTRiASFeatures Feats;

	if (SUCCEEDED(Obj -> get_Features (Feats.ppi()))) 
		*ppIFeats = Feats.detach();
	else {
	// ansonsten Features von zugehöriger Objektklasse geben lassen
		RETURN_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));
		*ppIFeats = Feats.detach();
	}
	if (NULL != ppIObj)
		*ppIObj = Obj.detach();
	return S_OK;
}

HRESULT DatenBasisObjekt::GetObjectsFeatures (INT_PTR hObjs, ITRiASFeatures **ppIFeats, ITRiASObjects **ppIObjs)
{
// Objekt besorgen
WTRiASObjects Objs;

	RETURN_FAILED_HRESULT(GetObjectsFromMap ((long)hObjs, Objs));

// Features von zugehöriger Objektklasse geben lassen
WTRiASFeatures Feats;

	RETURN_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));
	*ppIFeats = Feats.detach();

	if (NULL != ppIObjs)
		*ppIObjs = Objs.detach();

	return S_OK;
}

namespace {
	inline BOOL EnumMCodesCallback (
		BOOL (*pFcn)(long, BOOL, void *), long lMCode, BOOL fNotLast, void *pData) 
	{
		return ((ENUMLONGKEYCALLBACK)pFcn)(lMCode, fNotLast, pData);
	}

	inline BOOL EnumMCodesCallbackEx (
		BOOL (*pFcn)(long, DWORD, void *), long lMCode, DWORD dwData, void *pData) 
	{
		return ((ENUMLONGKEYEXCALLBACK)pFcn)(lMCode, dwData, pData);
	}
} // namespace

BOOL DatenBasisObjekt::EnumMiTextObject (
	INT_PTR lONr, ENUMLONGKEYPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (&DB(), &PbdDB(), lONr, OBL_OLD);

		return (LRESULT)ML.EnumMerkmale (pFcn, pData);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	BOOL iRC = FALSE;

		COM_TRY {
		// MerkmalsCollection besorgen
		WTRiASFeatures Feats;
		OBJECTTYPE rgType = OBJECTTYPE_Unknown;
		WTRiASObject Obj;
		INT_PTR lTOMCode = 0L;

			THROW_FAILED_HRESULT(GetObjectFeatures (lONr, Feats.ppi(), Obj.ppi()));
			THROW_FAILED_HRESULT(Obj -> get_Type (&rgType));
			if (OBJECTTYPE_Text == rgType) {
			HPROJECT hPr = DEX_GetObjectProject(lONr);

				lTOMCode = DB(hPr).TOMCode();
			}

		// ... und enumerieren
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Feats -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				if (FAILED(v.ChangeType (VT_DISPATCH)))
					continue;

			WTRiASFeature Feat (V_DISPATCH(&v));
			INT_PTR lMCode = 0L;
			FEATURETYPE rgType = FEATURETYPE_Unknown;

				if (SUCCEEDED(Feat -> get_Handle (&lMCode)) && (0 == lTOMCode || lMCode != lTOMCode)) {
					iRC = EnumMCodesCallback (pFcn, lMCode, TRUE, pData);
					if (!iRC) break;		// abgebrochen
				}
			}
		} COM_CATCH;
		return iRC;
	}
}

BOOL DatenBasisObjekt::EnumMiTextObjectEx (
	INT_PTR lONr, DWORD dwTypes, ENUMLONGKEYEXPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (&DB(), &PbdDB(), lONr, OBL_OLD,
		  bool(dwTypes & MPSystemFeatures), 
		  bool(dwTypes & MPAllFeatures));

		return (LRESULT)ML.EnumMerkmaleEx (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// MerkmalsCollection besorgen
	WTRiASFeatures Feats;
	WTRiASObject Obj;

		THROW_FAILED_HRESULT(GetObjectFeatures (lONr, Feats.ppi(), Obj.ppi()));
		return EnumMiTextFeatures (Feats, dwTypes, pFcn, pData, Obj);
	}
}

#if !defined(_FORCE_LEGACY_CODE)
// Alle Objekteigenschaften eines Objektes einer Objektklasse enumerieren
BOOL DatenBasisObjekt::EnumMiTextObjectClassEx (
	INT_PTR hObjs, DWORD dwTypes, ENUMLONGKEYEXPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());

// MerkmalsCollection besorgen
WTRiASFeatures Feats;

	RETURN_FAILED_HRESULT(GetObjectsFeatures (hObjs, Feats.ppi()));
	return EnumMiTextFeatures (Feats, dwTypes, pFcn, pData);
}
#endif // !defined(_FORCE_LEGACY_CODE)

BOOL DatenBasisObjekt::EnumMiTextFeatures (
	ITRiASFeatures *pIFeats, DWORD dwTypes, ENUMLONGKEYEXPROC pFcn, void *pData,
	ITRiASObject *pIObj)
{
// Fallunterscheidungen
FEATURETYPE rgTypeToEnum = BitsToFEATURETYPE(dwTypes);
bool fEnumSys = (rgTypeToEnum & FEATURETYPE_System) ? true : false;
bool fEnumDefinitionOnly = (rgTypeToEnum & FEATURETYPE_DefinitionOnly) ? true : false;
BOOL iRC = FALSE;

	COM_TRY {
	// evtl. Objecttyp feststellen und TOMCode setzen
	OBJECTTYPE rgType = OBJECTTYPE_Unknown;
	INT_PTR lTOMCode = 0L;

		if (NULL != pIObj) {
			THROW_FAILED_HRESULT(pIObj -> get_Type (&rgType));
			if (OBJECTTYPE_Text == rgType) {
			HPROJECT hPr = GetObjectProject (pIObj);

				lTOMCode = DB(hPr).TOMCode();
			}
		}

	// ... und enumerieren
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(pIFeats -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASFeature Feat (V_DISPATCH(&v));
		INT_PTR lMCode = 0L;
		FEATURETYPE rgType = FEATURETYPE_Unknown;

			if (SUCCEEDED(Feat -> get_Handle (&lMCode)) && SUCCEEDED(Feat -> get_Type (&rgType))) 
			{
				if (!fEnumSys && (rgType & FEATURETYPE_System))
					continue;
				if (!fEnumDefinitionOnly && (rgType & FEATURETYPE_DefinitionOnly))
					continue;
				if (0 != lTOMCode && lMCode == lTOMCode)
					continue;		// Text eines Textobjektes

				iRC = EnumMCodesCallbackEx (pFcn, lMCode, DWORD(rgType), pData);
				if (!iRC) break;		// abgebrochen
			}
		}

	} COM_CATCH_IGNORE;
	return iRC;
}

HRESULT DatenBasisObjekt::DelMiTextObject (INT_PTR lONr, LONG lMCode)
{
	return PutMiTextObject (lONr, lMCode, NULL);
}

HRESULT DatenBasisObjekt::GetMiTextObject (INT_PTR lONr, LONG lMCode, LPSTR pText, short &riLen)
{
HRESULT hr = HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	COM_TRY {
	// Feature von zugehöriger Objektklasse geben lassen
	WTRiASFeature Feat;

		if (SUCCEEDED(GetFeatureFromMap (lMCode, Feat))) {
		// Objekt besorgen
		WTRiASObject Obj;			// gesuchtes Objekt

			THROW_FAILED_HRESULT(GetObjectFromMap (lONr, Obj));

		// jetzt eigentliches Merkmal abfragen
		CComVariant vVal;
		
			hr = Feat -> Eval (Obj, &vVal);
			if (SUCCEEDED(hr)) {
				if (SUCCEEDED(hr = vVal.ChangeType (VT_BSTR))) {
				int iStrLen = SysStringLen(V_BSTR(&vVal));			// grundsätzlich Textlänge liefern
				int iToCopy = min ((size_t)iStrLen, (size_t)(riLen-1));

					riLen = iToCopy;
					if (NULL != pText && iToCopy > 0) {
						USES_CONVERSION;
						strncpy (pText, OLE2A(V_BSTR(&vVal)), iToCopy);
						pText[iToCopy] = '\0';
					} 
					else if (NULL == pText && iStrLen > 0)
						return S_OK;
					else
						return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
				} 
				else if (V_ISNULL(&vVal))
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
			}
		} 
	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Merkmalsbehandlung für Objektklassen (Idents)
HRESULT DatenBasisObjekt::PutMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode, LPSTR pText)
{
	TX_ASSERT(IsTRiASDBBased());

char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return EC_FAIL;		// keine aktive Sicht
		pcView = cbBuffer;
	}

// Ansicht besorgen
WTRiASView View;
WTRiASObjects Objs;
WTRiASViewItem ViewItem;
CComBSTR bstrText (g_cbNil);
HRESULT hr = m_Prj -> get_View (CComBSTR(pcView), VARIANT_TRUE, View.ppi());

	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

	hr = GetObjectsFromMap (lIdent, Objs);
	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

	hr = View -> get_ViewItem (CComVariant(Objs), VARIANT_TRUE, bstrText, ViewItem.ppi());
	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

// alle Properties der Ansicht abfragen
WTRiASProperties Props;

	RETURN_FAILED_HRESULT(WTRiASPropertyBase(ViewItem) -> get_Properties (Props.ppi()));
	wsprintf (cbBuffer, g_cbSysProperty, lMCode);

// entweder Wert setzen/neu erzeugen oder löschen
	if (NULL != pText) {
		RETURN_FAILED_HRESULT(SetProperty (Props, cbBuffer, CComBSTR(pText), true));
	} else {
		RETURN_FAILED_HRESULT(DelProperty (Props, cbBuffer));
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::DelMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode)
{
	return PutMiTextIdent (pcView, lIdent, lMCode, NULL);
}

HRESULT DatenBasisObjekt::GetMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode, LPSTR pText, short &riLen)
{
	TX_ASSERT(IsTRiASDBBased());

char cbBuffer[_MAX_PATH];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
			return EC_FAIL;		// keine aktive Sicht
		pcView = cbBuffer;
	}

WTRiASView View;
WTRiASObjects Objs;
WTRiASViewItem ViewItem;
CComBSTR bstrNil (g_cbNil);
HRESULT hr = m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi());

	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

	hr = GetObjectsFromMap (lIdent, Objs);
	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

	hr = View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, bstrNil, ViewItem.ppi());
	if (FAILED(hr)) { SetLastError(hr); return HRESULT_FROM_ERRCODE(WC_NOTFOUND); }

	wsprintf (cbBuffer, g_cbSysProperty, lMCode);

CComBSTR bstrText = GetPropertyFrom (ViewItem, cbBuffer, bstrNil);
int iStrLen = bstrText.Length();			// grundsätzlich Textlänge liefern
int iToCopy = min ((size_t)iStrLen, (size_t)(riLen-1));

	riLen = iToCopy;
	if (NULL != pText && iToCopy > 0) {
		USES_CONVERSION;
		strncpy (pText, OLE2A(bstrText), iToCopy);
		pText[iToCopy] = '\0';
	} else if (NULL == pText && iStrLen > 0)
		return S_OK;
	else
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	return S_OK;
}

BOOL DatenBasisObjekt::EnumMiTextIdent (LPCSTR pcView, INT_PTR lIdent, ENUMLONGKEYPROC pFcn, void *pData)
{
BOOL fReturn = TRUE;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (&DB(), &PbdDB(), lIdent, IDL);

		return (LRESULT)ML.EnumMerkmale (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		USES_CONVERSION;
		COM_TRY {

		char cbBuffer[_MAX_PATH];

			if (NULL == pcView) {
				if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
					return EC_FAIL;		// keine aktive Sicht
				pcView = cbBuffer;
			}

		WTRiASView View;
		WTRiASObjects Objs;
		WTRiASViewItem ViewItem;
		WTRiASProperties Props;
		CComBSTR bstrText (g_cbNil);

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));
			THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, bstrText, ViewItem.ppi()));
			THROW_FAILED_HRESULT(WTRiASPropertyBase(ViewItem) -> get_Properties (Props.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Props -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				TX_ASSERT(V_VT(&v) == VT_DISPATCH);

			WTRiASProperty Item (V_DISPATCH(&v));
			CComBSTR bstrName;
			INT_PTR lMCode = 0;

				THROW_FAILED_HRESULT(Item -> get_Name (CLEARED(&bstrName)));
				if (1 != sscanf (OLE2A(bstrName), g_cbSysProperty, &lMCode))
					continue;

				TX_ASSERT(0 != lMCode);
				if (!EnumMCodesCallback (pFcn, lMCode, TRUE, pData)) {
					fReturn = FALSE;
					break;
				}
			}
		} COM_CATCH_RETURN(FALSE);
	}
	return fReturn;
}

BOOL DatenBasisObjekt::EnumMiTextIdentEx (LPCSTR pcView, INT_PTR lIdent, DWORD dwTypes, ENUMLONGKEYEXPROC pFcn, void *pData)
{
BOOL fReturn = TRUE;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (&DB(), &PbdDB(), lIdent, IDL, bool(dwTypes & MPSystemFeatures), 
			  bool(dwTypes & MPAllFeatures));

		return (LRESULT)ML.EnumMerkmaleEx (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		USES_CONVERSION;
		COM_TRY {

		char cbBuffer[_MAX_PATH];

			if (NULL == pcView) {
				if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
					return EC_FAIL;		// keine aktive Sicht
				pcView = cbBuffer;
			}

		WTRiASView View;
		WTRiASObjects Objs;
		WTRiASViewItem ViewItem;
		WTRiASProperties Props;
		CComBSTR bstrText (g_cbNil);

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
			THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));
			THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, bstrText, ViewItem.ppi()));
			THROW_FAILED_HRESULT(WTRiASPropertyBase(ViewItem) -> get_Properties (Props.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(Props -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				TX_ASSERT(V_VT(&v) == VT_DISPATCH);

			WTRiASProperty Item (V_DISPATCH(&v));
			CComBSTR bstrName;
			INT_PTR lMCode = 0;

				THROW_FAILED_HRESULT(Item -> get_Name (CLEARED(&bstrName)));
				if (1 != sscanf (OLE2A(bstrName), g_cbSysProperty, &lMCode))
					continue;

				TX_ASSERT(0 != lMCode);
				if (!EnumMCodesCallbackEx (pFcn, lMCode, (FEATURETYPE_Ident | FEATURETYPE_System), pData)) {
					fReturn = FALSE;
					break;
				}
			}
		} COM_CATCH_RETURN(FALSE);
	}
	return fReturn;
}

///////////////////////////////////////////////////////////////////////////////
// Merkmalsbehandlung für Ansichten
HRESULT DatenBasisObjekt::PutMiTextSicht (LPCSTR pcView, LONG lMCode, LPSTR pText)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return S_OK;

		CharToOem (pText, pText);

	CActDB ActDB (DB());		// #ActDB
	Sicht S (DB(), pcView);
	ErrCode RC = S.PutMiText (lMCode, pText);

	// Merkmals-Integrität testen
		TX_ASSERT(EC_OKAY == TestSichtMerkmal (DB(), pcView, lMCode, g_iKonsFlags));
		if (EC_OKAY == RC)
			return S_OK;
		return HRESULT_FROM_ERRCODE(RC);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen/ggf. neu erzeugen
	WTRiASView View;

		RETURN_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_TRUE, View.ppi()));

	// alle Properties der Ansicht abfragen
	WTRiASProperties Props;
	char cbBuffer[_MAX_PATH];

		RETURN_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
		wsprintf (cbBuffer, g_cbSysProperty, lMCode);

	// entweder Wert setzen/neu erzeugen oder löschen
		if (NULL != pText) {
			RETURN_FAILED_HRESULT(SetProperty (Props, cbBuffer, CComBSTR(pText), true));
		} else {
			RETURN_FAILED_HRESULT(DelProperty (Props, cbBuffer));
		}
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::DelMiTextSicht (LPCSTR pcView, LONG lMCode)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return EC_OKAY;

	CActDB ActDB (DB());		// #ActDB
	Sicht S (DB(), pcView);
	ErrCode RC = S.DelMiText (lMCode);

		TX_ASSERT(EC_OKAY == TestSichtMerkmalDeleted (DB(), pcView, lMCode, g_iKonsFlags));
		if (EC_OKAY == RC)
			return S_OK;
		return HRESULT_FROM_ERRCODE(RC);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen
	WTRiASView View;

		if (FAILED(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi())))
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);		// keine Ansicht -> nichts zu löschen

	// alle Properties der Ansicht abfragen
	WTRiASProperties Props;
	char cbBuffer[_MAX_PATH];

		RETURN_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
		wsprintf (cbBuffer, g_cbSysProperty, lMCode);
		RETURN_FAILED_HRESULT(DelProperty (Props, cbBuffer));
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::GetMiTextSicht (LPCSTR pcView, LONG lMCode, LPSTR pText, short &riLen)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// VersionsKontrolle
		if (DB().GetDBVersion() < VERSION05000008) 
			return S_OK;

	CActDB ActDB (DB());		// #ActDB
	Sicht S (DB(), pcView);
	LPSTR pNewText = NULL;
	ErrCode RC = S.GetMiText (lMCode, &pNewText);

		if (EC_OKAY == RC) {
			OemToCharBuff (pNewText, pText, riLen-1);
			DELETE_OBJ(pNewText);
			return S_OK;
		}
		return HRESULT_FROM_ERRCODE(RC);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// Ansicht besorgen
	WTRiASView View;

		if (FAILED(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi())))
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	// alle Properties der Ansicht abfragen
	CComBSTR bstrNil (g_cbNil);
	char cbBuffer[_MAX_PATH];

		wsprintf (cbBuffer, g_cbSysProperty, lMCode);
	
	CComBSTR bstrText = GetPropertyFrom (View, cbBuffer, bstrNil);
	int iStrLen = bstrText.Length();			// grundsätzlich Textlänge liefern
	int iToCopy = min ((size_t)iStrLen, (size_t)(riLen-1));

		riLen = iToCopy;
		if (NULL != pText && iToCopy > 0) {
			USES_CONVERSION;
			strncpy (pText, OLE2A(bstrText), iToCopy);
			pText[iToCopy] = '\0';
		}  else if (NULL == pText && iStrLen > 0)
			return S_OK;
		else 
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}
	return S_OK;
}

namespace {
	inline BOOL EnumViewFeatsCallback (
		BOOL (*pFcn)(char *, BOOL, void *), char *pName, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYCALLBACK)pFcn)(pName, fNotLast, pData);
	}

	inline BOOL EnumViewFeatsCallbackEx (
		BOOL (*pFcn)(char *, DWORD, void *), char *pName, DWORD dwData, void *pData) 
	{
		return ((ENUMNOKEYEXCALLBACK)pFcn)(pName, dwData, pData);
	}
} // namespace

BOOL DatenBasisObjekt::EnumMiTextSicht (LPCSTR pcView, ENUMNOKEYPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	USES_CONVERSION;

BOOL fReturn = TRUE;

	COM_TRY {
	char cbBuffer[_MAX_PATH];

		if (NULL == pcView) {
			if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
				return EC_FAIL;		// keine aktive Sicht
			pcView = cbBuffer;
		}

	WTRiASView View;
	WTRiASObjects Objs;
	WTRiASViewItem ViewItem;
	WTRiASProperties Props;
	CComBSTR bstrText (g_cbNil);

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));
		THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(Props -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			TX_ASSERT(V_VT(&v) == VT_DISPATCH);

		WTRiASProperty Item (V_DISPATCH(&v));
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(Item -> get_Name (CLEARED(&bstrName)));
			if (!EnumViewFeatsCallback (pFcn, OLE2A(bstrName), TRUE, pData)) {
				fReturn = FALSE;
				break;
			}
		}
	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

BOOL DatenBasisObjekt::EnumMiTextSichtEx (LPCSTR pcView, DWORD dwTypes, ENUMNOKEYEXPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (&DB(), &PbdDB(), (LPSTR)pcView,
			  bool(dwTypes & MPSystemFeatures), 
			  bool(dwTypes & MPAllFeatures));

		return (LRESULT)ML.EnumMerkmaleEx (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	FEATURETYPE rgTypeToEnum = BitsToFEATURETYPE(dwTypes);

	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 
BOOL DatenBasisObjekt::EnumAllFeatures (ENUMNOKEYLONGPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML;

		FillMerkmale (*this, ML);
		return (LRESULT)ML.EnumMerkmale (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened() && !l -> EnumAllFeatures (pFcn, pData))
				return FALSE;
		}
	}
	return TRUE;
}

BOOL DatenBasisObjekt::EnumAllFeaturesEx (ENUMNOKEYLONGEXPROC pFcn, DWORD dwTypes, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	MerkmalsListe ML (bool(dwTypes & MPSystemFeatures), bool(dwTypes & MPAllFeatures));

		FillMerkmale (*this, ML);
		return (LRESULT)ML.EnumMerkmaleEx (pFcn, pData);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	FEATURETYPE rgTypeToEnum = BitsToFEATURETYPE(dwTypes);
	bool fListAllClasses = (dwTypes & MPListAllClasses) ? true : false;
	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened() && !l -> EnumAllFeaturesEx (pFcn, rgTypeToEnum, pData, fListAllClasses))
				return FALSE;
		}
	}
	return TRUE;
}

BOOL DatenBasisObjekt::EnumAllFeaturesObjsEx (ENUMNOKEYLONGEXPROC pFcn, DWORD dwIdent, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());

WTRiASObjects Objs;
HRESULT hr = GetObjectsFromMap ((long)dwIdent, Objs);

	if (FAILED(hr)) {
		SetLastError (hr);
		return FALSE;
	}

CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened() && !l -> EnumAllFeaturesObjsEx (Objs, pFcn, FEATURETYPE_AllFeatures, pData))
			return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Relationen
ErrCode DatenBasisObjekt::ModifyRelation (INT_PTR lPONr, INT_PTR lSONr, INT_PTR lRCode, int iRTyp, bool fUndo)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
			
		DB().SetDirty();
		return (ErrCode)PutRelation (DB().DBDesc(), lPONr, lSONr, lRCode, iRTyp);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// beide Objekte müssen aus ein und derselben TRiAS-Datenquelle kommen
	HPROJECT hPrP = DEX_GetObjectProject(lPONr);
	HPROJECT hPrS = DEX_GetObjectProject(lPONr);

		if (!DEX_GetTRiASDataSourceEx(hPrP) || !DEX_GetTRiASDataSourceEx(hPrS) || hPrP != hPrS)
			return ERRCODE_FROM_HRESULT(E_INVALIDARG);

	// derzeit werden nur Begleitrelationen bearbeitet
		if ((-1 != lRCode && 0 != lRCode) || !(iRTyp & BRELAP))
			return ERRCODE_FROM_HRESULT(E_INVALIDARG);

		COM_TRY {
		// Undo initialisieren
		WUndoRedoCreateObjectRelation Undo;
		HRESULT hr = S_FALSE;

			if (fUndo) {
				hr = UndoCreateInstance (IID_IUndoRedoCreateObjectRelation, Undo.ppv());
				if (SUCCEEDED(hr))
					hr = Undo -> Init (lPONr, lSONr, lRCode, iRTyp);
			}

		// Relation setzen
		WTRiASObject ObjP;
		WTRiASObject ObjS;

			THROW_FAILED_HRESULT(GetObjectFromMap (lPONr, ObjP));
			THROW_FAILED_HRESULT(GetObjectFromMap (lSONr, ObjS));

		WTRiASSimpleObject SimpleObj;

			THROW_FAILED_HRESULT(ObjP -> QueryInterface(SimpleObj.ppi()));
			THROW_FAILED_HRESULT(SimpleObj -> put_RelatedObject(ObjS));

		// bei Erfolg Undo einfügen
			if (S_OK == hr) 
				DEX_AddUndoRedo ((IUnknown *)Undo);

		} COM_CATCH_EX(e) {
			return ERRCODE_FROM_HRESULT(_COM_ERROR(e));
		}
	}
	return EC_OKAY;
}

ErrCode DatenBasisObjekt::DeleteRelation (INT_PTR lPONr, INT_PTR lSONr, INT_PTR lRCode, int iRTyp, bool fUndo)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());
			
		DB().SetDirty();
		return (ErrCode)DelRelation (DB().DBDesc(), lPONr, lSONr, lRCode, iRTyp);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// beide Objekte müssen aus ein und derselben TRiAS-Datenquelle kommen
	HPROJECT hPrP = DEX_GetObjectProject(lPONr);
	HPROJECT hPrS = DEX_GetObjectProject(lPONr);

		if (!DEX_GetTRiASDataSourceEx(hPrP) || !DEX_GetTRiASDataSourceEx(hPrS) || hPrP != hPrS)
			return ERRCODE_FROM_HRESULT(E_INVALIDARG);

	// derzeit werden nur Begleitrelationen bearbeitet
		if ((-1 != lRCode && 0 != lRCode) || !(iRTyp & BRELAP))
			return ERRCODE_FROM_HRESULT(E_INVALIDARG);

		COM_TRY {
		// Undo initialisieren
		WUndoRedoDeleteObjectRelation Undo;
		HRESULT hr = S_FALSE;

			if (fUndo) {
				hr = UndoCreateInstance (IID_IUndoRedoDeleteObjectRelation, Undo.ppv());
				if (SUCCEEDED(hr))
					hr = Undo -> Init (lPONr, lSONr, lRCode, iRTyp);
			}

		// Relation setzen
		WTRiASObject ObjP;
		WTRiASSimpleObject SimpleObj;

			THROW_FAILED_HRESULT(GetObjectFromMap (lPONr, ObjP));
			THROW_FAILED_HRESULT(ObjP -> QueryInterface(SimpleObj.ppi()));
			THROW_FAILED_HRESULT(SimpleObj -> put_RelatedObject(NULL));

		// bei Erfolg Undo einfügen
			if (S_OK == hr) 
				DEX_AddUndoRedo ((IUnknown *)Undo);

		} COM_CATCH_EX(e) {
			return ERRCODE_FROM_HRESULT(_COM_ERROR(e));
		}
	}
	return EC_OKAY;
}

namespace {
	inline BOOL EnumRelationCallback (
		BOOL (*pFcn)(long, BOOL, void *), INT_PTR lRCode, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYLONGCALLBACK)pFcn)(lRCode, fNotLast, pData);
	}
}

BOOL DatenBasisObjekt::EnumRelations (ENUMNOKEYLONGPROC pFcn, void *pData)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		return DB().EnumRCodes (pFcn, pData);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// derzeit werden nur Begleitrelationen bearbeitet
		return EnumRelationCallback(pFcn, 0, FALSE, pData);
	}
}

namespace {
	inline BOOL EnumRelatedObjsCallback (
		BOOL (*pFcn)(INT_PTR, INT_PTR, short, void *), INT_PTR lONr, INT_PTR lRCode, short iRTyp, void *pData) 
	{
		return ((ENUMRELOBJCALLBACK)pFcn)(lONr, lRCode, iRTyp, pData);
	}
}

BOOL DatenBasisObjekt::EnumRelatedObjects (ENUMRELATIONOBJS *pERO)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		return DB().EnumRelationObjs (pERO);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// derzeit werden nur Begleitrelationen bearbeitet
		if ((-1 != pERO -> lRCode && 0 != pERO -> lRCode) || !(pERO -> iRTyp & BRELAP)) {
			SetLastError(E_INVALIDARG);
			return FALSE;
		}

	// das Objekt muß einer TRiAS-Datenquelle entstammen
	HPROJECT hPr = DEX_GetObjectProject (pERO -> lONr);

		if (!DEX_GetTRiASDataSourceEx(hPr)) {
			SetLastError(E_INVALIDARG);
			return FALSE;
		}
	
	// alles ok, also jetzt die Enumeration starten	
		SetLastError(S_OK);

	// das Begleitobjekt geben lassen
	WTRiASObject ObjP, ObjS;
	WTRiASSimpleObject SimpleObjP, SimpleObjS;

		RETURN_FAILED_HRESULT(GetObjectFromMap (pERO -> lONr, ObjP));
		RETURN_FAILED_HRESULT(ObjP -> QueryInterface(SimpleObjP.ppi()));
		if (S_OK != SimpleObjP -> get_RelatedObject(ObjS.ppi()))
			return FALSE;	// nichts zu enumerieren

	INT_PTR lONr = 0;
	OBJECTTYPE rgType = OBJECTTYPE_Unknown;

		RETURN_FAILED_HRESULT(ObjS -> get_Handle(&lONr));
		RETURN_FAILED_HRESULT(ObjP -> get_Type(&rgType));
		return EnumRelatedObjsCallback(pERO -> eFcn, lONr, 0, (rgType != OBJECTTYPE_Text) ? BRELA : BRELP, pERO -> pData);
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die Objekteigenschaft beschreibbar (schreibgeschützt) ist
bool DatenBasisObjekt::GetROModeFeature (HPROJECT hPr, INT_PTR lMCode)
{
CComBool fCanUpdate;

	COM_TRY {
	// Feature von zugehöriger Objektklasse geben lassen
	WTRiASFeature Feat;

		if (SUCCEEDED(GetFeatureFromMap (lMCode, Feat))) {
		// Objekteigenschaft existiert
			THROW_FAILED_HRESULT(Feat -> get_Updatable (&fCanUpdate));
		}
		else {
		// Objekteigenschaft existiert (noch) nicht, also SchreibSchutzStatus der Datenquelle liefern
			fCanUpdate = CComBool(DEX_GetROModeEx(hPr));
		}

	} COM_CATCH_RETURN(true);	// bei Fehler so gut wie schreibgeschützt
	return bool(fCanUpdate);
}

HRESULT DatenBasisObjekt::SetROModeFeature (INT_PTR lMCode, bool fROMode)
{
	COM_TRY {
	// Feature von zugehöriger Objektklasse geben lassen
	WTRiASFeature Feat;

		if (SUCCEEDED(GetFeatureFromMap (lMCode, Feat))) 
		{
			THROW_FAILED_HRESULT(Feat -> put_Updatable (CComBool(!fROMode)));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// findet den zu einem MCode passenden Iddent
INT_PTR DatenBasisObjekt::GetFeatureIdent (INT_PTR lMCode)
{
HPROJECT hPr = DEX_GetFeatureProject(lMCode);

	if (DEX_GetTRiASDataSourceEx(hPr))
		return NULL;		// Feature gehört zu allen Objektklassen

// Die Objektklasse sollte ein Parent des Features sein
INT_PTR hObjs = NULL;

	COM_TRY {
	WTRiASFeature Feat;

		if (SUCCEEDED(GetFeatureFromMap(lMCode, Feat))) {
		// Objekteigenschaft existiert wirklich
		WTRiASObjects Objs;

			if (SUCCEEDED(FindSpecificParent(Feat, Objs.ppi()))) 
			{
				THROW_FAILED_HRESULT(Objs -> get_Handle(&hObjs));
			}
		}

	} COM_CATCH;
	return hObjs;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert das FeatureHandle in für Texte der Text gespeichert ist
HRESULT DatenBasisObjekt::GetTextFeature(INT_PTR lObjs, INT_PTR *plFeat)
{
HPROJECT hPr = DEX_GetObjectsProject(lObjs);

	if (DEX_GetTRiASDataSourceEx(hPr)) {
		*plFeat = DB(hPr).TOMCode();		// ist bereits gemappt
		return S_OK;
	}

	*plFeat = INVALID_HFEATURE;
	return S_OK;

//MAPMCODETOHANDLE MCH;
//
//	INITSTRUCT(MCH, MAPMCODETOHANDLE);
//	MCH.lIdent = lObjs;
//	MCH.lMCode = DB(hPr).TOMCode();
//	MCH.fCreate = FALSE;
//	MCH.plHandle = plFeat;
//	return DEX_MapOrCreateMCodeToHandle(hPr, MCH) ? S_OK : E_FAIL;
}


// @doc
// @module DBOMetaData.cpp | Zugriff auf alles, was MetaDaten betrift

#include "TriasPre.hxx"
#include "TRiASRes.h"

#include <Com/PropertyHelper.h>

#include "Strings.h"
#include "TRiASUtil.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen 
extern HPALETTE hPalette;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectsCollection);		// WTRiASObjectsCollection
DefineSmartInterface(EnumVARIANT);					// WEnumVARIANT
DefineSmartInterface(TRiASFeatures);				// WTRiASFeatures
DefineSmartInterface(TRiASDatabase);				// WTRiASDatabase

///////////////////////////////////////////////////////////////////////////////
// MetaDaten-TransactionHandling
ErrCode DatenBasisObjekt::BeginTransaction(HPROJECT hPr)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().BeginTransaction();

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
	}
	return EC_OKAY;
}

ErrCode DatenBasisObjekt::BreakTransaction(HPROJECT hPr)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().BreakTransaction();

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
	}
	return EC_OKAY;
}

ErrCode DatenBasisObjekt::EndTransaction(HPROJECT hPr)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().EndTransaction();

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Version der MetaDatenBank
long DatenBasisObjekt::GetPBDVersion(HPROJECT hPr)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().GetDBVersion();

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		return DB(hPr).GetDBVersion();		// hier wird die Version der GeoDB geliefert
	}
	return 0L;
}

///////////////////////////////////////////////////////////////////////////////
// Lesen von MetaDaten
ErrCode DatenBasisObjekt::GetPBDData (HPROJECT hPr, PBDDATA *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().GetPBDData (pData);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

#pragma TODO("Metadatenhandling für Relationen implementieren!")
		switch (pData -> pbdTyp) {
		case 'r':
			return EC_NOOPEN;

		case 'm':
			{
			HRESULT hr = GetPBDDataMerkmal (hPr, pData);

				if (S_OK == hr)
					return EC_OKAY;
				else if (S_FALSE == hr)
					return WC_RETURN;
				else if (FACILITY_ERRCODE == HRESULT_FACILITY(hr))
					return ERRCODE_FROM_HRESULT(hr);
				return EC_FAIL;
			}

		case 'i':
			{
			HRESULT hr = GetPBDDataIdent (hPr, pData);

				if (S_OK == hr)
					return EC_OKAY;
				else if (S_FALSE == hr)
					return WC_RETURN;
				else if (FACILITY_ERRCODE == HRESULT_FACILITY(hr))
					return ERRCODE_FROM_HRESULT(hr);
				return EC_FAIL;
			}
		}
	}
	return EC_OKAY;
}

// Lesen der Metadaten für eine Objektmenge
HRESULT DatenBasisObjekt::GetPBDDataIdent (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

VARIANT_BOOL fNameIsDefault = VARIANT_TRUE;

	USES_CONVERSION;
	{
	// Objektmenge aus globaler Tabelle lesen
	WTRiASObjects Objs;
	HRESULT hr = S_OK;

		if (FAILED(hr = GetObjectsFromMap (pData -> pbdCode, Objs)))
			return hr;

	// Testen, ob das gefundene Objektmenge zur geforderten Datenquelle paßt
		if (HACTCONNECTION != hPr) {
		HPROJECT hPrTarget = NULL;

			RETURN_FAILED_HRESULT(GetDatabaseOrProjectHandle (Objs, &hPrTarget));
			if (hPrTarget != hPr)			// Ident aus anderer Datenquelle
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}

	// Namen lesen und in Rückgabestruktur setzen
	CComBSTR bstr;

		RETURN_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstr)));
		fNameIsDefault = GetPropertyFrom (Objs, g_cbNameIsDefault, VARIANT_TRUE);

	char *pStr = OLE2A(bstr);

		if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText) {
			if (pStr) {
			int iLen = strlen (pStr);
			
				iLen = min(iLen, pData -> pbdKTextLen-1);
				strncpy (pData -> pbdKText, pStr, iLen);
				pData -> pbdKText[iLen] = '\0';
				pData -> pbdKTextLen = iLen;
			} else {
				*pData -> pbdKText = '\0';
				pData -> pbdKTextLen = 0;
			}
		} else 
			pData -> pbdKTextLen = (NULL != pStr) ? strlen(pStr)+1 : 0;	// benötigte Buffergröße liefern

	// BeschreibungsInfo lesen und in Rückgabestruktur setzen
	CComBSTR bstrLT;

		if (SUCCEEDED(Objs -> get_Description (CLEARED(&bstrLT)))) {
		// möglicherweise wird 'get_Description' nicht unterstützt
		char *pStr = OLE2A(bstrLT);

			if (pData -> pbdLTextLen > 0 && NULL != pData -> pbdLText) {
				if (pStr) {
				int iLen = strlen (pStr);

					iLen = min(iLen, pData -> pbdLTextLen-1);
					strncpy (pData -> pbdLText, pStr, iLen);
					pData -> pbdLText[iLen] = '\0';
					pData -> pbdLTextLen = iLen;
				} else {
					*pData -> pbdLText = '\0';
					pData -> pbdLTextLen = 0;
				}
			} else 
				pData -> pbdLTextLen = (NULL != pStr) ? strlen(pStr)+1 : 0;	// benötigte Buffergröße liefern
		} else
			pData -> pbdLTextLen = 0;

	}
	return fNameIsDefault ? S_FALSE : S_OK;
}

// Besorgen des Tabellennamens (sofern einer exitiert)
HRESULT DatenBasisObjekt::GetTableName (TABLENAME *pTableName)
{
// Rückgabewerte initialisieren
int iLen = pTableName -> iLen;

	pTableName -> pBuffer[0] = '\0';
	pTableName -> iLen = 0;

// Objektmenge aus globaler Tabelle lesen
WTRiASObjects Objs;
HRESULT hr = S_OK;

	if (FAILED(hr = GetObjectsFromMap (pTableName -> lIdent, Objs)))
		return hr;

CComBSTR bstrName;

	RETURN_FAILED_HRESULT(hr = Objs -> get_TableName (CLEARED(&bstrName)));

int iToCopy = min ((int)bstrName.Length(), iLen -1);

	USES_CONVERSION;
	strncpy (pTableName -> pBuffer, OLE2A(bstrName), iToCopy);
	pTableName -> pBuffer[iToCopy] = '\0';
	pTableName -> iLen = iToCopy;

	return hr;
}

// Lesen der Metadaten für eine Objektmenge
HRESULT DatenBasisObjekt::GetPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

VARIANT_BOOL fNameIsDefault = VARIANT_TRUE;

	USES_CONVERSION;
	{
	// wenns ein Ansichtsmerkmal sein soll, dann einfach wieder raus
		if ((sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) &&
			MPViewFeature == (((PBDMERKMAL *)pData) -> ipbdMTyp & 0x7F))
		{
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}

	// Objekteigenschaft aus globaler Tabelle lesen
	WTRiASFeature Feat;
	HRESULT hr = S_OK;

		if (FAILED(hr = GetFeatureFromMap (pData -> pbdCode, Feat)))
			return hr;

	// Testen, ob das gefundene Feature zur geforderten Datenquelle paßt
		if (HACTCONNECTION != hPr) {
		HPROJECT hPrTarget = NULL;

			RETURN_FAILED_HRESULT(GetDatabaseHandle (Feat, &hPrTarget));
			if (hPrTarget != hPr)		// MCode aus anderer Datenquelle
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}

	// Namen lesen und in Rückgabestruktur setzen
	CComBSTR bstr;

		RETURN_FAILED_HRESULT(Feat -> get_Name (CLEARED(&bstr)));
		fNameIsDefault = GetPropertyFrom (Feat, g_cbNameIsDefault, VARIANT_FALSE);

	char *pStr = OLE2A(bstr);

		if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText) {
			if (pStr) {
			int iLen = strlen (pStr);
			
				iLen = min(iLen, pData -> pbdKTextLen-1);
				strncpy (pData -> pbdKText, pStr, iLen);
				pData -> pbdKText[iLen] = '\0';
				pData -> pbdKTextLen = iLen;
			} else {
				*pData -> pbdKText = '\0';
				pData -> pbdKTextLen = 0;
			}
		} else 
			pData -> pbdKTextLen = (NULL != pStr) ? strlen(pStr)+1 : 0;	// benötigte Buffergröße liefern

	// BeschreibungsInfo lesen und in Rückgabestruktur setzen
	CComBSTR bstrLT;

		if (SUCCEEDED(Feat -> get_Description (CLEARED(&bstrLT)))) {
		// möglicherweise wird 'get_Description' nicht unterstützt
		char *pStr = OLE2A(bstrLT);

			if (pData -> pbdLTextLen > 0 && NULL != pData -> pbdLText) {
				if (pStr) {
				int iLen = strlen (pStr);

					iLen = min(iLen, pData -> pbdLTextLen-1);
					strncpy (pData -> pbdLText, pStr, iLen);
					pData -> pbdLText[iLen] = '\0';
					pData -> pbdLTextLen = iLen;
				} else {
					*pData -> pbdLText = '\0';
					pData -> pbdLTextLen = 0;
				}
			} else 
				pData -> pbdLTextLen = (NULL != pStr) ? strlen(pStr)+1 : 0;	// benötigte Buffergröße liefern
		} else
			pData -> pbdLTextLen = 0;

	// evtl. zusätzliche Infos liefern
		if (sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) {
		PBDMERKMAL *pPbdM = (PBDMERKMAL *)pData;
		FEATURETYPE rgType = FEATURETYPE_Unknown;

			pPbdM -> ipbdMTyp = 'a';	// Objektmerkmal
			if (SUCCEEDED(Feat -> get_Type (&rgType))) {
			// Typ der Objekteigenschaft festellen
				switch (VT_FROM_DATATYPE(rgType)) {
				case VT_I4:
				case VT_I2:
				case VT_I1:
				case VT_INT:
				case VT_UI4:
				case VT_UI2:
				case VT_UI1:
				case VT_UINT:
				case VT_BOOL:
				case VT_ERROR:
					pPbdM -> ipbdMTyp = 'i';
					break;

				case VT_R4:
				case VT_R8:
				case VT_DATE:
					pPbdM -> ipbdMTyp = 'f';
					break;

				default:
					break;		// VT_BSTR --> 'a'
				}

			// zusätzliche 
				if (rgType & FEATURETYPE_System)
					pPbdM -> ipbdMTyp |= PBDMERKMAL_SYSTEMFLAG;
				if (rgType & FEATURETYPE_ReadOnly)
					pPbdM -> ipbdMTyp |= PBDMERKMAL_READONLY;
			}

		// Platzbedarf der Objekteigenschaft feststellen
		long lLen = 0;

			if (SUCCEEDED(Feat -> get_Length (&lLen))) 
				pPbdM -> ipbdMLen = lLen;
			else
				pPbdM -> ipbdMLen = _MAX_PATH;	// doch recht willkürlich
		}

	} 
	return fNameIsDefault ? S_FALSE : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Schreiben von MetaDaten
ErrCode DatenBasisObjekt::ModPBDData (HPROJECT hPr, PBDDATA *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().ModPBDData (pData);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		switch (pData -> pbdTyp) {
		case 'r':
			return EC_NOOPEN;

		case 'm':
			return SUCCEEDED(ModPBDDataMerkmal (hPr, pData)) ? EC_OKAY : EC_FAIL;

		case 'i':
			{
			HRESULT hr = ModPBDDataIdent (hPr, pData);

				if (S_OK == hr)
					return EC_OKAY;
				else if (S_FALSE == hr)
					return WC_RETURN;
				else if (FACILITY_ERRCODE == HRESULT_FACILITY(hr))
					return ERRCODE_FROM_HRESULT(hr);
				return EC_FAIL;
			}
		}
	}
	return EC_OKAY;
}

HRESULT DatenBasisObjekt::ModPBDDataIdent (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

HRESULT hr = S_OK;

	USES_CONVERSION;
	{
	// wiederauffinden des Objects-Objektes
	WTRiASObjects Objs;

		if (FAILED(GetObjectsFromMap (pData -> pbdCode, Objs))) {
		// Objektklasse existiert nicht, also neu erzeugen
			TX_ASSERT(pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText);	// KurzText muß gegeben sein

		// Objektmenge (Tabelle) muß neu angelegt werden
			if (HACTPROJECT != hPr)	{	// neue Tabelle in einer Datenquelle anlegen
			ErrCode RC = DB(hPr).ModPBDDataIdent (pData);

				return (EC_OKAY == RC) ? S_OK : HRESULT_FROM_ERRCODE(RC);
			}

		// neue übergreifende Objektmenge ggf. erzeugen
			RETURN_FAILED_HRESULT(m_Prj -> get_ObjectsDef (CComVariant(pData -> pbdKText), VARIANT_TRUE, CComBSTR(g_cbNil), Objs.ppi()));

		// das neue Objekt wenigstens von seinem Handle informieren
			if (0 != pData -> pbdCode)
			{
				RETURN_FAILED_HRESULT(Objs -> put_Handle (pData -> pbdCode));
			} 

		// reales, vergebenes Handle zurückliefern
		INT_PTR lHandle = 0;

			RETURN_FAILED_HRESULT(Objs -> get_Handle (&lHandle));
			if (lHandle != pData -> pbdCode) {
				TX_TRACE2("TRiAS: ModPbdDataIdent: Changed IdentHandle %lx -> %lx !", pData -> pbdCode, lHandle);
				pData -> pbdCode = lHandle;

			// Notifikation rumschicken
				DEXN_FeatureSetModified(lHandle);
				return S_FALSE;
			}

		// Notifikation rumschicken
			DEXN_FeatureSetModified(pData -> pbdCode);
		} 
		else {
		// Testen, ob der gegebene Ident zur geforderten Datenquelle paßt
#if defined(_DEBUG)
			if (HACTCONNECTION != hPr) {
			HPROJECT hPrTarget = NULL;

				RETURN_FAILED_HRESULT(GetDatabaseOrProjectHandle (Objs, &hPrTarget));
				TX_ASSERT(hPrTarget == hPr);		// Ident aus anderer Datenquelle ?
			}
#endif // defined(_DEBUG)

		// hier nur neuen KurzText (Namen) einstellen
			if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText)
				RETURN_FAILED_HRESULT(Objs -> put_Name (CComBSTR(pData -> pbdKText)));
		}
	
	// LangText (BeschreibungsInfo) einstellen
		if (pData -> pbdLTextLen > 0 && NULL != pData -> pbdLText) {
			RETURN_FAILED_HRESULT(Objs -> put_Description (CComBSTR(pData -> pbdLText)));
		} else {
			RETURN_FAILED_HRESULT(Objs -> put_Description (CComBSTR(g_cbNil)));
		}
	}
	return hr;
}

HRESULT DatenBasisObjekt::ModPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

	USES_CONVERSION;
	{
	bool fForceTypeChange = (MPForceForTRiASDBs & ((PBDMERKMAL *)pData) -> ipbdMTyp) ? true : false;

	// wenns ein Ansichtsmerkmal sein soll, dann einfach wieder raus
		if ((sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) &&
			(MPViewFeature == (((PBDMERKMAL *)pData) -> ipbdMTyp & 0x7F)) &&
			!fForceTypeChange)
		{
			return S_FALSE;
		}

	// Objekteigenschaft aus globaler Tabelle lesen
	WTRiASFeature Feat;
	HRESULT hr = S_OK;

		if (FAILED(GetFeatureFromMap (pData -> pbdCode, Feat))) {
			TX_ASSERT(sizeof(PBDMERKMALEX) == pData -> dwSize);		// Ident muß gegeben sein

		// Objekteigenschaft existiert nicht, also neu erzeugen
			TX_ASSERT(pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText);	// KurzText muß gegeben sein

		// wiederauffinden des Objects-Objektes
		WTRiASObjects Objs;
		INT_PTR lIdent = ((PBDMERKMALEX *)pData) -> lIdent;

			if (-1 == lIdent) {
			// wenn Ident nicht gegeben ist dann muß DataSource eine GeoDB sein
				TX_ASSERT(DB(hPr).IsTRiASDataSource());
				lIdent = DEX_GetUnknownIdentEx(hPr);		// den erstbesten verwenden
			}

			RETURN_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));	// Objektmenge muß existieren
			RETURN_FAILED_HRESULT(Objs -> get_Feature (CComVariant(pData -> pbdCode), VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));

			if (!fForceTypeChange) {
				RETURN_FAILED_HRESULT(Feat -> put_Name (CComBSTR(pData -> pbdKText)));

			// reales, vergebenes Handle zurückliefern
			INT_PTR lHandle = 0;

				RETURN_FAILED_HRESULT(Feat -> get_Handle (&lHandle));
				if (lHandle != pData -> pbdCode) {
					TX_TRACE2("TRiAS: ModPbdDataMerkmal: Changed FeatureHandle %lx -> %lx !", pData -> pbdCode, lHandle);
					pData -> pbdCode = lHandle;
				}

			// Notifikation rumschicken
				DEXN_FeatureSetModified(lIdent);
			}
		} 
		else if (!fForceTypeChange || (MPObjectFeature == (((PBDMERKMAL *)pData) -> ipbdMTyp & 0x7F))) {
#if defined(_DEBUG)
		// Testen, ob der gegebene MCode zur geforderten Datenquelle paßt
			if (HACTCONNECTION != hPr) {
			HPROJECT hPrTarget = NULL;

				RETURN_FAILED_HRESULT(GetDatabaseOrProjectHandle (Feat, &hPrTarget));
				TX_ASSERT(hPrTarget == hPr);		// Ident aus anderer Datenquelle ?
			}
#endif // defined(_DEBUG)

		// hier nur neuen KurzText (Namen) einstellen
			if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText)
				RETURN_FAILED_HRESULT(Feat -> put_Name (CComBSTR(pData -> pbdKText)));

		// Notifikation rumschicken
		INT_PTR lIdent = -1L;

			if (sizeof(PBDMERKMALEX) == pData -> dwSize) {
				lIdent = ((PBDMERKMALEX *)pData) -> lIdent;

			// sicherstellen, daß dieser MCode schon zu dem Ident gehört (#HK030111)
				if (-1 != lIdent) {
				// schlimmstenfalls liefert _Add S_FALSE (wenns schon dazugehört)
				WTRiASObjects Objs;
				WTRiASFeatures Feats;
				WTRiASFeature TestFeat;

					RETURN_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));	// Objektmenge muß existieren
					RETURN_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));

					if (pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText) {
					// über den Namen gehts schneller
						if (S_OK != Feats -> Item (CComVariant(pData -> pbdKText), TestFeat.ppi()))
						{
							RETURN_FAILED_HRESULT(Feats -> _Add(Feat));
						}
					}
					else {
					// kein Name gegeben, also Handle verwenden
						if (S_OK != Feats -> Item (CComVariant(pData -> pbdCode), TestFeat.ppi()))
						{
							RETURN_FAILED_HRESULT(Feats -> _Add(Feat));
						}
					}
				}
			}
			DEXN_FeatureSetModified(lIdent);
		}
		
		if (!fForceTypeChange || (MPObjectFeature == (((PBDMERKMAL *)pData) -> ipbdMTyp & 0x7F))) {
		// LangText (BeschreibungsInfo) einstellen
			if (pData -> pbdLTextLen > 0 && NULL != pData -> pbdLText) {
				RETURN_FAILED_HRESULT(Feat -> put_Description (CComBSTR(pData -> pbdLText)));
			} else {
				RETURN_FAILED_HRESULT(Feat -> put_Description (CComBSTR(g_cbNil)));
			}
		}

	// evtl. zusätzliche Infos speichern
		if (sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) {
		PBDMERKMAL *pPbdM = (PBDMERKMAL *)pData;
		FEATURETYPE rgType = FEATURETYPE_Object;	// Objektmerkmal
		
			if (fForceTypeChange) 
				rgType = FEATURETYPE(pPbdM -> ipbdMTyp & 0x7f);	// ggf. neuer Typ

			if (pPbdM -> ipbdMTyp & PBDMERKMAL_SYSTEMFLAG) 
				rgType = FEATURETYPE(rgType | FEATURETYPE_System);
			if (pPbdM -> ipbdMTyp & PBDMERKMAL_READONLY) 
				rgType = FEATURETYPE(rgType | FEATURETYPE_ReadOnly);

			RETURN_FAILED_HRESULT(Feat -> put_Type (rgType));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Löschen von MetaDaten
ErrCode DatenBasisObjekt::DelPBDData (HPROJECT hPr, PBDDATA *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());
			
		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().DelPBDData (pData);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		switch (pData -> pbdTyp) {
		case 'r':
			return EC_NOOPEN;

		case 'm':
			return SUCCEEDED(DelPBDDataMerkmal (hPr, pData)) ? EC_OKAY : EC_FAIL;

		case 'i':
			return SUCCEEDED(DelPBDDataIdent (hPr, pData)) ? EC_OKAY : EC_FAIL;
		}
	}
	return EC_OKAY;
}

HRESULT DatenBasisObjekt::DelPBDDataIdent (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());

// Tabelle liegt in einer Datenquelle 
	if (HACTPROJECT != hPr) {
	ErrCode RC = DB(GetIdentDBHandle (pData -> pbdCode, hPr)).DelPBDDataIdent (pData);

		if (EC_OKAY != RC)
			return HRESULT_FROM_ERRCODE(RC);

	// Notifikation rumschicken
		DEXN_FeatureSetModified(pData -> pbdCode);
	} 
	else {
	// KurzText muß gegeben sein
		TX_ASSERT(pData -> pbdKTextLen > 0 && NULL != pData -> pbdKText);

	// übergreifende Objektmenge löschen
	WTRiASObjectsCollection ObjsDefs;

		RETURN_FAILED_HRESULT(m_Prj -> get_ObjectsDefs (ObjsDefs.ppi()));
		RETURN_FAILED_HRESULT(ObjsDefs -> Remove (CComVariant(pData -> pbdKText)));
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::DelPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData)
{
	TX_ASSERT(IsTRiASDBBased());
	TX_ASSERT(NULL == pData -> pbdKText || TIsValidString(pData -> pbdKText));	

// wenns ein Ansichtsmerkmal sein soll, dann einfach wieder raus
	if ((sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) &&
		MPViewFeature == (((PBDMERKMAL *)pData) -> ipbdMTyp & 0x7F))
	{
		return S_FALSE;
	}

	TX_ASSERT(sizeof(PBDMERKMALEX) == pData -> dwSize && 0 != ((PBDMERKMALEX *)pData) -> lIdent);							// Ident muß gegeben sein

// Feature entweder über Code oder Namen löschen
CComVariant v;

	if (NULL == pData -> pbdKText) 
		v = pData -> pbdCode;
	else 
		v = pData -> pbdKText;

// Wiederauffinden des Objects-Objektes
WTRiASFeatures Feats;
WTRiASObjects Objs;
INT_PTR lIdent = ((PBDMERKMALEX *)pData) -> lIdent;

	RETURN_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));	// Objektmenge muß existieren
	RETURN_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));

// erstmal nachsehen, ob das Merkmal existiert
bool fExists = false;

	{
	WTRiASFeature Feat;

		fExists = SUCCEEDED(Feats -> Item(v, Feat.ppi())) ? true : false;
	}
	if (fExists) {
	// nur löschen, wenns wirklich (noch) existiert)	
		RETURN_FAILED_HRESULT(Feats -> Remove (v));

	// Notifikation rumschicken
		DEXN_FeatureSetModified(lIdent);
	}
	return fExists ? S_OK : S_FALSE;	// S_FALSE heißt 'existiert nicht'
}

///////////////////////////////////////////////////////////////////////////////
// Enumerieren von MetaDaten
BOOL DatenBasisObjekt::EnumPBDData (HPROJECT hPr, long lKey, ENUMLONGKEYPROC pFcn, void *pData)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActPBD (PbdDB());

		if(!ActPBD) return EC_NOOPEN;
		return PbdDB().EnumPBDData (lKey, pFcn, pData);

	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		switch (lKey) {
		case 'r':
			return FALSE;

		case 'm':
			return EnumPBDDataMerkmal (hPr, pFcn, pData);

		case 'i':
			{
				if (HACTCONNECTION == hPr) {
				// alles enumerieren
					if (EnumPBDDataIdent (hPr, pFcn, pData))	// erst dies
						return EnumPBDDataIdent (HACTPROJECT, pFcn, pData);	// dann jenes
				} else
					return EnumPBDDataIdent (hPr, pFcn, pData);
			}
			break;
		}
	}
	return FALSE;
}

namespace {
	inline BOOL EnumIdentsCallback (
		BOOL (*pFcn)(long, BOOL, void *), long Id, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYLONGCALLBACK)pFcn)(Id, fNotLast, pData);
	}
}

BOOL DatenBasisObjekt::EnumPBDDataIdent (HPROJECT hPr, ENUMLONGKEYPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());

BOOL iRC = TRUE;

	COM_TRY {
	// Enumerieren aller Objektklassen einer Datenquelle
		if (HACTPROJECT != hPr) {
			if (HACTCONNECTION != hPr)	// eine bestimmte Datenquelle auswerten
				return DB(hPr).EnumPBDDataIdent (pFcn, pData);

		// _alle_ Datenquellen auswerten
		CRing r (*m_pGeoDBs);

			for (r.First(); r.Valid(); r.Next()) {
			GeoDBLock l(r);

				TX_ASSERT(NULL != (GeoDB *)l);
				if (l -> isOpened()) {
					if (!l -> EnumPBDDataIdent (pFcn, pData))
						return FALSE;
				}
			}
			return TRUE;
		}

	// Objektmengen (Tabellen) enumerieren
	WTRiASObjectsCollection ObjsDefs;

		THROW_FAILED_HRESULT(m_Prj -> get_ObjectsDefs (ObjsDefs.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(ObjsDefs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASObjects Item (V_DISPATCH(&v));
		INT_PTR lHandle = 0L;

			if (SUCCEEDED(Item -> get_Handle (&lHandle))) {
				iRC = EnumIdentsCallback (pFcn, lHandle, TRUE, pData);
				if (!iRC) break;	// Enumeration abgebrochen
			}
		}

	} COM_CATCH_RETURN(FALSE);
	return iRC;
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsCodes enumerieren
BOOL DatenBasisObjekt::EnumPBDDataMerkmal (HPROJECT hPr, ENUMLONGKEYPROC pFcn, void *pData)
{
	TX_ASSERT(IsTRiASDBBased());

// Enumerieren aller Objekteigenschaften einer bestimmten Datenquelle
	if (HACTCONNECTION != hPr) {	// eine bestimmte Datenquelle auswerten
//		return DB(hPr).EnumPBDDataMerkmal (pFcn, pData);
		TX_ASSERT(DB(hPr).isOpened());
		return DB(hPr).EnumAllFeatures ((ENUMNOKEYLONGPROC)pFcn, pData);
	}

// _alle_ Datenquellen auswerten
CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened()) {
//			if (!l -> EnumPBDDataMerkmal (pFcn, pData))
			if (!l -> EnumAllFeatures ((ENUMNOKEYLONGPROC)pFcn, pData))
				return FALSE;
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Objekt zu einer Zuordnungsobjektklasse einer Ansicht gehört
//bool DatenBasisObjekt::IsObjectInView (INT_PTR lONr, LPCSTR pcView)
//{
//	_ASSERTE(NULL == pcView);	// z.Zt lediglich für aktuelle Ansicht ausgeführt
//
//// zu untersuchende Ansicht 
//char cbBuffer[_MAX_PATH];
//
//	if (NULL == pcView) {
//		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer))) 
//			return FALSE;		// keine aktive Sicht
//		pcView = cbBuffer;
//	}
//
//// alle Zuordnungsobjektklassen durchgehen
//CTable t(Idents().IdentTree());
//
//	for (t.First(); t.Valid(); t.Next()) {
//	CIdentifikatorLock l(t);
//
//		if (!l || HACTPROJECT != l -> GetObjectsProject() || !l -> toPaint()) 
//			continue;	// keine Zuordnungsobjektklasse
//
//		if (l -> IsObjectInClass (lONr))
//			return TRUE;	// Objekt gehört zu dieser Objektklasse
//	}
//	return FALSE;			// nicht in Zuordnungsobjektklassen der Ansicht enthalten
//}


///////////////////////////////////////////////////////////////////////////////
// Zuordnungsobjektklassen (Notanker, wenn QueryDef nicht installiert ist)
namespace {
// Helper zum Auffruf der gewünschten callback-Funktion
	inline BOOL EnumObjectClassesCallback (
		BOOL (*pFcn)(long, DWORD, void *), long lIdent, DWORD dwData, void *pData) 
	{
		return ((ENUMLONGKEYEXCALLBACK)pFcn)(lIdent, dwData, pData);
	}
}

BOOL DatenBasisObjekt::EnumObjectClasses (INT_PTR lONr, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData)
{
long lIdent = RetrieveIdent (lONr, true);

	if (dwData & CFO_ActViewOnly) {
	// lediglich aktuelle´Ansicht untersuchen
	CTable t(Idents().IdentTree());

		if (t.Find (&lIdent)) {
		CIdentifikatorLock l(t);

			if (l && l -> toPaint())
				return EnumObjectClassesCallback (pFcn, lIdent, lONr, pData);
		}
		return TRUE;	// Ident gehört nicht zur Ansicht
	}

// unabhängig von aktueller Ansicht 
	return EnumObjectClassesCallback (pFcn, lIdent, lONr, pData);
}

// ebenfalls Notanker für evtl. fehlende QueryDef.dll
BOOL DatenBasisObjekt::IsObjectInClass (INT_PTR lIdent, INT_PTR lONr, INT_PTR *plONrMapped)
{
	if (lIdent != RetrieveIdent (lONr, true))
		return FALSE;

	if (NULL != plONrMapped)
		*plONrMapped = lONr;
	return TRUE;
}

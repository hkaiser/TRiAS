// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 04.07.2000 08:40:25
//
// @doc
// @module ArcViewLayer.cpp | Implementation of the <c CArcViewLayer> class

#include "StdAfx.h"

#include <ospace/file/path.h>

#include "Strings.h"
#include "ArcViewImpl.h"
#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "ArcView.hmc"
#include "ExportHelper.h"
#include "ArcViewDataSource.h"

///////////////////////////////////////////////////////////////////////////////
// Stellt fest, ob ein bestimmtes Feld bereits in der Datei enthalten ist
HRESULT CArcViewLayer::FieldExists (LPCSTR pcName, DBFFieldType rgType, int *piField)
{
CFieldNames::iterator it = m_Names.find (pcName);

	if (it != m_Names.end()) {
	int iCnt = DBFGetFieldCount(m_hDBF);
	int iWidth = 0;
	int iDecimals = 0;
	char cbBuffer[_MAX_PATH];

		for (int i = 0; i < iCnt; ++i) {
		DBFFieldType rgActType = DBFGetFieldInfo(m_hDBF, i, cbBuffer, &iWidth, &iDecimals);

			if ((*it).second == os_string(cbBuffer)) {
				if (NULL != piField)
					*piField = i;
				if (rgType == rgActType || rgActType == FTString)
					return S_OK;		// found Field
				else
					return S_FALSE;		// found, but type does not match
			}
		}
	}
	return E_FAIL;		// does not exist
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines eindeutigen Feldnames (max. 11 Zeichen lang)
#define MAX_DBASEFIELDNAME_LEN	10
#define MAX_DBASEFIELD_LEN		254

bool CArcViewLayer::IsUniqueName (os_string &rStr)
{
	for (CFieldNames::iterator it = m_Names.begin(); it != m_Names.end(); ++it) {
		if (rStr == (*it).second)
			return false;		// existiert bereits als Feldname
	}
	return true;	// existiert noch nicht als Feldname
}

os_string CArcViewLayer::GetUniqueFieldName (LPCSTR pcName)
{
// als erstes einfach auf 10 Zeichen verkürzen und Eindeutigkeit prüfen
os_string strName (pcName, min(MAX_DBASEFIELDNAME_LEN, strlen(pcName)));
int iCurrNumber = 0;

	while (!IsUniqueName (strName)) {
	// letzte Zeichen einfach durch hochgezählte Ziffern ersetzen
	char cbCnt[32];

		_ltoa (++iCurrNumber, cbCnt, 10);
		strName = strName.substr (0, min(MAX_DBASEFIELDNAME_LEN, strName.size()) - (strlen(cbCnt) + 1)) + "_" + cbCnt;
	}
	return strName;
}

///////////////////////////////////////////////////////////////////////////////
// anlegen eines neuen Feldes in der DBase-Datei
HRESULT CArcViewLayer::AddField(LPCSTR pcName, DBFFieldType rgTyp, int iLen, int iDecimal, int *piField)
{
	if (NULL == piField)
		return E_POINTER;
	*piField = -1;

CFieldNames::iterator it = m_Names.find (pcName);

	if (it == m_Names.end()) {
	// Namen zuordnen
	pair<CFieldNames::iterator, bool> p = m_Names.insert(CFieldNames::value_type(pcName, GetUniqueFieldName(pcName)));

		if (p.second)
			it = p.first;
	}

	if (it != m_Names.end()) {
	// DBasefeld anlegen
		if (FTString == rgTyp && iLen > MAX_DBASEFIELD_LEN)
			iLen = MAX_DBASEFIELD_LEN;
			
		*piField = DBFAddField(m_hDBF, (*it).second.c_str(), rgTyp, iLen, iDecimal);

	// ggf. existiert das Feld schon in der DBaseDatei (eine bereits exportierte
	// Datenquelle hat es hinterlassen)
		if (-1 != *piField) 
			return S_OK;		// found Field

	int iCnt = DBFGetFieldCount(m_hDBF);
	int iWidth = 0;
	int iDecimals = 0;
	char cbBuffer[_MAX_PATH];

		for (int i = 0; i < iCnt; ++i) {
		DBFFieldType rgActType = DBFGetFieldInfo(m_hDBF, i, cbBuffer, &iWidth, &iDecimals);

			if ((*it).second == os_string(cbBuffer) 
				&& (rgTyp == rgActType || rgActType == FTString))
			{
				*piField = i;
				return S_OK;		// found Field
			}
		}
		return E_FAIL;
	}
	return E_FAIL;		// could not create field
}

///////////////////////////////////////////////////////////////////////////////
// Export eines Objektes
HRESULT CArcViewLayer::ExportData (
	GSTRUCT *pGS, MFELD *pMF, LPCSTR pcUIdent, CArcViewLayerAttributes *pMap)
{
OBJECTTYPE rgType = GetType();
int iShapeId = -1;
int iObjTyp = pGS -> Typ;

	_ASSERTE(rgType == ObjType2OBJECTTYPE(pGS -> Typ, true));	// Objekttyp muß stimmen

// Geometrie erzeugen
	if (OBJECTTYPE_Area == rgType) {
	// Anzahl der Konturen feststellen und Konturfeld zusammenbauen
	int iKCnt = 1;
	vector<int> Cnts(1);
	int iCurr = 0;

		Cnts[0] = 0;
		for (int i = 0; 0 != pGS -> cnt[i]; ++i) {
			if (i > 0) 
				Cnts.push_back(iCurr);
			iCurr += pGS -> cnt[i];
		}
		iKCnt = i;

		_ASSERTE(iKCnt > 0 && iKCnt == Cnts.size());

	// Objekt erzeugen
	CArcViewObject Obj(SHPCreateObject(m_nShapeType, -1, iKCnt, Cnts.begin(), NULL,
						pGS -> GSize, pGS -> x, pGS -> y, NULL, NULL));

		iShapeId = SHPWriteObject(m_hSHP, -1, Obj);

	} else {
	// Objekt erzeugen
	CArcViewObject Obj(SHPCreateSimpleObject(m_nShapeType, pGS -> GSize, pGS -> x, pGS -> y, NULL));

		iShapeId = SHPWriteObject(m_hSHP, -1, Obj);
	}
	if (iShapeId == -1)
		return E_FAIL;

// Attribute sicherstellen (bei TRiAS-Datenquellen jedesmal)
	if (!HasFields() || DEX_GetTRiASDataSourceEx(DEX_GetObjectsProject(pGS -> Id))) {
	// sämtliche Attribute dieses Layers durchgehen und ggf. erzeugen
		for (CArcViewLayerAttributes::iterator it = pMap -> begin(); it != pMap -> end(); ++it) {
		// Feld in Datei erzeugen
		int iField = -1;
		CArcViewAttribute &rAttr = (*it).second;
		LPCSTR pcName = rAttr.GetName();

			if (OBJECTTYPE_Text != m_rgType && !strcmp (pcName, g_cbLabelText))
				continue;		// Labeltext nur für Textobjekte
				
			if (FAILED(FieldExists (pcName, rAttr.GetTyp(), &iField))) 
			{
				RETURN_FAILED_HRESULT(AddField(pcName, rAttr.GetTyp(), rAttr.GetLen(), rAttr.GetDecimals(), &iField));
			}
			_ASSERTE(-1 != iField);

		// mehrerer Objekttypen eines Idents haben identischen Satz von Attributen
			_ASSERTE(-1 == (*it).second.GetField(iObjTyp) || 
					 (*it).second.GetField(iObjTyp) == iField ||
					 DEX_GetTRiASDataSourceEx(DEX_GetObjectsProject(pGS -> Id)));

		// Feldnummer beim Attribut speichern
			(*it).second.SetField(iField, iObjTyp);
		}

	// Textlabel für Textobjekte
		if (OBJECTTYPE_Text == m_rgType) {
		pair<CArcViewLayerAttributes::iterator, bool> p = 
			pMap -> insert (CArcViewLayerAttributes::value_type (-1, CArcViewAttribute(g_cbLabelText, 'a', _MAX_PATH)));

			if (p.second) {
			int iField = -1;

				it = p.first;
				if (FAILED(FieldExists (g_cbLabelText, FTString, &iField))) 
				{
					RETURN_FAILED_HRESULT(AddField(g_cbLabelText, FTString, _MAX_PATH, 0, &iField));
				}
				
				_ASSERTE(-1 != iField);
				(*it).second.SetField(iField, iObjTyp);						
			}
		}
		SetHasFields();
	}
	
// Attributwerte schreiben
	if (NULL != pMF) {
	// nur, wenn mindestens ein Attribut ausgegeben werden soll
		for (MFELD *pMFT = pMF; 0 != pMFT -> MCode; ++pMFT) {
			if (NULL != pMap) {
			CArcViewLayerAttributes::iterator it = pMap -> find (pMFT -> MCode);

				_ASSERTE(it != pMap -> end());	// Attribut sollte (jetzt) existieren
				if (it != pMap -> end()) {
				// Feld muß bereits erzeugt worden sein und Typ muß mit DBF übereinstimmen
				int iField = (*it).second.GetField(iObjTyp);

					_ASSERTE(-1 != iField);
					_ASSERTE((*it).second.GetTyp() == DBFGetFieldInfo (m_hDBF, iField, NULL, NULL, NULL));

				// Wert je nach Typ in die Datenbank schreiben
					switch ((*it).second.GetTyp()) {
					case FTString:
						{
						char cbBuffer[_MAX_PATH] = { '\0' };

							if (NULL != pMFT -> MText)
								OemToCharBuff(pMFT -> MText, cbBuffer, min(MAX_DBASEFIELD_LEN, strlen(pMFT -> MText))+1);	// '\0' mit konvertieren
							DBFWriteStringAttribute(m_hDBF, iShapeId, iField, cbBuffer);
						}
						break;

					case FTInteger:
						DBFWriteIntegerAttribute(m_hDBF, iShapeId, iField, (NULL != pMFT -> MText) ? atol(pMFT -> MText) : 0);
						break;

					case FTDouble:
						DBFWriteDoubleAttribute(m_hDBF, iShapeId, iField, (NULL != pMFT -> MText) ? atof(pMFT -> MText) : 0.0);
						break;
					}
				}
			} else {
				_ASSERTE(NULL != pMap);		// eigentlich sollte eine Map da sein

			// keine Map, also erstmal leeren Datensatz schreiben
			int iCnt = DBFGetFieldCount(m_hDBF);

				for (int i = 0; i < iCnt; ++i) {
					switch (DBFGetFieldInfo(m_hDBF, i, NULL, NULL, NULL)) {
					case FTString:
						DBFWriteStringAttribute(m_hDBF, iShapeId, i, g_cbNil);
						break;

					case FTInteger:
						DBFWriteIntegerAttribute(m_hDBF, iShapeId, i, 0);
						break;

					case FTDouble:
						DBFWriteDoubleAttribute(m_hDBF, iShapeId, i, 0.0);
						break;
					}
				}
			}
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Objekttyp des Layers
OBJECTTYPE CArcViewLayer::GetType() 
{
OBJECTTYPE rgType = OBJECTTYPE_Unknown;

#if defined(_DEBUG)
int iCnt = 0;
int nShapeType = 0;

	SHPGetInfo (m_hSHP, &iCnt, &nShapeType, NULL, NULL);
	_ASSERTE(m_nShapeType == nShapeType);
#endif // defined(_DEBUG)

	switch (m_nShapeType) {
	case SHPT_POINT:
	case SHPT_POINTM:
	case SHPT_POINTZ:
		rgType = OBJECTTYPE_Point;
		break;

	case SHPT_MULTIPOINT:
	case SHPT_MULTIPOINTM:
	case SHPT_MULTIPOINTZ:
		break;

	case SHPT_ARC:
	case SHPT_ARCM:
	case SHPT_ARCZ:
		rgType = OBJECTTYPE_Line;
		break;

	case SHPT_POLYGON:
	case SHPT_POLYGONZ:
	case SHPT_POLYGONM:
		rgType = OBJECTTYPE_Area;
		break;
	}

	_ASSERTE(OBJECTTYPE_Unknown != rgType || iCnt == 0);
	return rgType;
}

///////////////////////////////////////////////////////////////////////////////
// alle Dateien schließen und löschen
HRESULT CArcViewLayer::CloseAndDeleteFiles()
{
	RETURN_FAILED_HRESULT(Close());

os_path pathRoot (m_strRoot);

	pathRoot.extension (g_cbShp);
	RETURN_EXPR_FALSE(DeleteFile(os_string(pathRoot).c_str()), HRESULT_FROM_WIN32(GetLastError()));

	pathRoot.extension (g_cbShx);
	RETURN_EXPR_FALSE(DeleteFile(os_string(pathRoot).c_str()), HRESULT_FROM_WIN32(GetLastError()));

	pathRoot.extension (g_cbDbf);
	RETURN_EXPR_FALSE(DeleteFile(os_string(pathRoot).c_str()), HRESULT_FROM_WIN32(GetLastError()));

	return S_OK;
}

// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.12.2000 12:15:48
//
// @doc
// @module ODBCProperty.cpp | Implementation of the <c CODBCProperty> class

#include "pheader.h"		//	vorübers. Header
#include "odbcext.hr"		//	Resource-Konstanten

#include <xtsnpropatl.h>			// CObjectProperties
#include <eonrguid.h>

#include <hpp/strdup.hxx>
#include <hpp/getodbci.hpp>
#include <hpp/collist.hpp>
#include <hpp/odbcerr.hpp>

#include "odbcguid.h"
#include "OdbcExt.hpp"
#include "Profile.hpp"
#include "RecSet.hpp"
#include "database.hpp"

#include "ODBCProperty.h"

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern CODBCObjectProperties *g_pCOdbcProperties;
extern COdbcExtension *g_pCOdbcExtension;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjectsByNumber);

/////////////////////////////////////////////////////////////////////////////
// CODBCProperty

// IObjectProperty specifics
STDMETHODIMP CODBCProperty::Reset (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	m_lCnt = 0L;
	m_lCntAll = 0L;
	m_lLastObjNr = 0L;
	if (!g_pCOdbcExtension -> GetOptEnable())
		g_pCOdbcExtension -> GetLastIdentInfo().RemoveAll();		// alten Ident-Infos löschen

	return CObjectPropertyBase::Reset();
}

STDMETHODIMP CODBCProperty::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
// erstmal Basisklasse arbeiten lassen	
HRESULT hr = CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData);

	if (FAILED(hr))
		return hr;

	if (pdwData) {
		switch (m_pFeldInfos -> m_iDataType) {
		case SQL_SMALLINT:
		case SQL_INTEGER: 		
			*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;	
			break;

		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:
			*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;	
			break;

		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:
			*pdwData |= PROPCAPS_OBJPROPTYPE_DATE;	
			break;

		case SQL_DECIMAL:
		case SQL_NUMERIC:
		case SQL_BIGINT:
		case SQL_CHAR:
		case SQL_VARCHAR:
			*pdwData |= PROPCAPS_OBJPROPTYPE_STRING;	
			break;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CODBCProperty::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (NULL == pBuffer) 
		return E_POINTER;

	_ASSERTE(0 != ulLen);
	if (pulWritten) 
		*pulWritten = 0;

	if (ulLen > 20) {
		ltoa (m_lCntAll, pBuffer, 10);
		if (pulWritten) 
			*pulWritten = strlen (pBuffer);
		return S_OK;
	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft

// Einlesen eines ODBC-Feldes über eine gegebene ObjektNummer 
STDMETHODIMP CODBCProperty::Eval (LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{                    
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (NULL == pBuffer)
		return E_POINTER;

//	ggf. RecordSet aufbauen                                     
BOOL bOpFlag = TRUE;
CLastIdentInfo &rLastIdentInfo = g_pCOdbcExtension -> GetLastIdentInfo();

	if (m_lLastObjNr != lONr) {
	INT_PTR ulIdent = DEX_GetObjIdent (lONr);

	//	aktuellen Merkmalswerte müssen für jedes neue Onjekt neu gelesen werden
		if (g_pCOdbcExtension -> ReadDBaseCodes (lONr, ulIdent) < 2) 	// INI lesen
			return E_FAIL;                    	// keine ODBC-Anbindung vorh.

	//	sind wir hier in der richtigen Tabelle ?
	HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
	Profile ProFile(hPr);
	StringDup strTableName (ProFile.GetTableName (g_pCOdbcExtension -> _pAliasName), FALSE);

		if (!strTableName)
			return E_FAIL;
		if (m_pFeldInfos -> m_strTableName.CompareNoCase (strTableName) != 0) 
			return E_FAIL;	

		if (!rLastIdentInfo.Refresh (strTableName, lONr, ulIdent))		// bei Init. ist Fehler aufgetreten
			return E_FAIL;

	//	neuen RecordSet aufbauen
	BOOL bHardError = FALSE;

		TRY	{                      
		//	zuerst Where-Klausel
		CString strWhere;                                       
		
			bOpFlag = rLastIdentInfo.m_pCA -> BuildWhereKlausel (
					strWhere, g_pCOdbcExtension -> _pFieldName, g_pCOdbcExtension -> _pKeyName, FALSE);
			if (bOpFlag) {
				rLastIdentInfo.m_pCRecSet -> m_strFilter = strWhere;	// neue Klausel speichern	
				if (rLastIdentInfo.m_pCRecSet -> IsOpen())
					bOpFlag = rLastIdentInfo.m_pCRecSet -> Requery();
				else
					bOpFlag = rLastIdentInfo.m_pCRecSet -> Open (
						CRecordset::snapshot, rLastIdentInfo.m_strSQL, CRecordset::readOnly);
			}           
		}                   
		CATCH (CDBException, dbe) {   
		OdbcError oe (dbe);

			bHardError = TRUE;
			oe.Show (RC_RetrieveFieldInfo);                                     
		}
		AND_CATCH (CMemoryException, mce)
		{                     
			bHardError = TRUE;      
			DEX_Error (RC_RetrieveFieldInfo, EC_NOMEMORY);
		}
		AND_CATCH (CFileException, fe)
		{
			bHardError = TRUE;
			// DEX_Error (RC_RetrieveFieldInfo, EC_SYSERROR);
			fe -> ReportError ();
		}
		END_CATCH          
		                        
	//	bei Fehler              
		if (bHardError)
			rLastIdentInfo.CleanUp (FALSE);		
		else
			m_lLastObjNr = lONr;		// neue Objekt-Nummer speichern
	}	// end_if // lese neue ODBC-Infos		
		
//	wenn Infos gefunden
ULONG sMinLen = 0;

	if (bOpFlag && rLastIdentInfo.HasInfo()) {
	//	FeldInhalt lesen
	CString strVal;
	
		if (rLastIdentInfo.m_pCA -> GetFieldInfo (
				rLastIdentInfo.m_pCRecSet, strVal, m_pFeldInfos -> m_sIndex))
		{           
		// Infos für Kumulation sammeln
			IncrementCount();			// Zähler der erfolgreichen Aufrufe

			sMinLen = min (ulLen -1, (ULONG)strVal.GetLength()); 		
			if (sMinLen) {
			// mehr als Ende-Zeichen
				memcpy (pBuffer, strVal, sMinLen);
				pBuffer[sMinLen] = '\0';
				m_lCntAll += atol (pBuffer);      // Versuch zu addieren

			// 	Zähler aktualisieren
				++m_lCnt;
			}				
		}			
	}
	return (0 < sMinLen) ? S_OK : E_FAIL;
}

STDMETHODIMP CODBCProperty::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	_ASSERTE(NULL != pBuffer);
	_ASSERTE(0 != ulLen);

CString strHelp;

	AfxFormatString2 (strHelp, IDS_OBJPROPFUNC_HELP, m_pFeldInfos -> m_strTableName, m_pFeldInfos -> m_strFeldName);							 								

ULONG ul = min(ulLen-1, ULONG(strHelp.GetLength()));

	strncpy (pBuffer, strHelp, ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// DSearchObjects specific functions
namespace {
	inline bool IsNumeric (int iType)
	{
		switch (iType) {
		case SQL_INTEGER:
		case SQL_FLOAT:
		case SQL_REAL:
		case SQL_DOUBLE:
		case SQL_SMALLINT:
		case SQL_NUMERIC:
			return true;	// numerisches Feld

		default:
			break;
		}
		return false;
	}
}

STDMETHODIMP CODBCProperty::ConsiderSearch (
	BSTR bstrToMatch, tagSEARCHMODE rgFlags, ULONG ulCnt)
{
// bei Zahlen bringt Groß-/Kleinschreibung sowieso keinen Sinn
	if (!IsNumeric(m_pFeldInfos -> m_iDataType) && !(rgFlags & SEARCHMODE_NOMATCHCASE))
		return E_NOTIMPL;	// ODBC kann Groß-/Kleinschreibung nicht berücksichtigen

	switch (rgFlags & ~SEARCHMODE_SEARCHMODIFIERS) {
	case SEARCHMODE_NORMAL:
	case SEARCHMODE_ONLYEXISTANCE:
		return S_OK;		// sollte schnell gehen

	case SEARCHMODE_LIKE:
	case SEARCHMODE_REGEXPR:
		break;

	default:
		_ASSERTE(FALSE);		// snh
	}
	return E_NOTIMPL;
}

namespace {
	typedef struct tagFINDOBJECTINFO {
		CObjClassMap_t *pMap;
		IEnumObjectsByNumber *pEnum;
	} FINDOBJECTINFO;

	BOOL CALLBACK FindObjekt (long lONr, BOOL iNotLast, void *pData)
	{
	//	prüfe Objektnummer
		if (0 != lONr && -1 != lONr) {
		ULONG ulIdent = DEX_GetObjIdent (lONr);
			
		//Nachsehen, ob der Ident bekannt (gesucht) ist
			ASSERT (NULL != pData);

		FINDOBJECTINFO *pInfo = reinterpret_cast<FINDOBJECTINFO *>(pData);

			ASSERT (NULL != pInfo -> pMap);
			ASSERT (NULL != pInfo -> pEnum);

		CObjClassMap_t_tit map_it = pInfo -> pMap -> find (ulIdent);

			if (map_it != pInfo -> pMap -> end())
				pInfo -> pEnum -> AddItem (lONr);
			else {
				map_it = pInfo -> pMap -> find(0);		// Standard= gegeben ?
				if (map_it != pInfo -> pMap -> end ())
					pInfo -> pEnum -> AddItem (lONr);
			}
		}
		return TRUE;		// immer weiter machen
	}
}

STDMETHODIMP CODBCProperty::SearchObjects (
	BSTR bstrToMatch, tagSEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj)
{
	if (NULL == ppvObj)
		return E_POINTER;
	
	*ppvObj = NULL;
	if (S_OK != ConsiderSearch (bstrToMatch, rgFlags, 1))
		return E_NOTIMPL;

	USES_CONVERSION;
	COM_TRY {
	WEnumObjectsByNumber Objs (CLSID_EnumObjectsByNumber); // Enumerator generieren

	// Recordset öffnen
	ULONG ulMCode = 0;
	CRecordset RecSet;
	CString strClasses;
	CString strKoppelFeld;
	LPCSTR pcToMatch = NULL;

		if (SEARCHMODE_NORMAL == (rgFlags & ~SEARCHMODE_SEARCHMODIFIERS))
			pcToMatch = OLE2A(bstrToMatch);
		else {
			_ASSERTE(SEARCHMODE_ONLYEXISTANCE == (rgFlags & ~SEARCHMODE_SEARCHMODIFIERS));
		}

		THROW_FAILED_HRESULT(ReadParams (rgFlags, pcToMatch, RecSet, ulMCode, strClasses, strKoppelFeld));
		
	//	Objklassen map füllen
	CObjClassMap_t mapCls;

		if (FillMapWithClasses (m_pFeldInfos -> m_hPr, mapCls, strClasses)) {
		// Objekte wiederfinden
		CWaitCursor wc;
		FINDOBJECTINFO FOI;

			FOI.pMap = &mapCls;
			FOI.pEnum = Objs;

		ENUMRECHTEXTMERKMAL tm;

			INITSTRUCT(tm, ENUMRECHTEXTMERKMAL);
			tm.lMCode = ulMCode;
			tm.pMWert = NULL;
			tm.iMode = SMExactMatch | SMActViewOnly;
			tm.pData = &FOI;
			tm.eFcn = FindObjekt;

			for (/**/; !RecSet.IsEOF(); RecSet.MoveNext()) {
			CString strSetVal;

			// Feldinhalt lesen
				RecSet.GetFieldValue (strKoppelFeld, strSetVal);
				if (strSetVal.IsEmpty())
					continue;

				tm.pMWert = (char *)(const char *)strSetVal;
				DEX_EnumRechTextMerkmal(tm);
			}
		}

	// Set schließen
		RecSet.Close();

	// Resultat liefern
		*ppvObj = Objs.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RecordSet bauen
HRESULT CODBCProperty::ReadParams (
	tagSEARCHMODE rgFlags, LPCSTR pcToMatch, CRecordset &rRecSet, ULONG &ulMerkmalsKode, 
	CString &rstrClasses, CString &rstrKoppelFeld)
{
	ASSERT(!rRecSet.IsOpen());

// Database erzeugen
CDataBaseEx *pCDataBase = NULL;

	TRY {
		pCDataBase = new CDataBaseEx;
		if (pCDataBase -> OpenAlias (m_pFeldInfos -> m_strAlias, m_pFeldInfos -> m_hPr)) {
		//	weitere Parameter lesen
		Profile ProFile(m_pFeldInfos -> m_hPr);

		//	lese Koppelfeld
			rstrKoppelFeld = ProFile.GetKoppelFeld (m_pFeldInfos -> m_strAlias);
			if (rstrKoppelFeld.IsEmpty ())
				return E_FAIL;

		//	lese Merkmalskode
			ulMerkmalsKode = ProFile.GetMerkmalsKode (m_pFeldInfos -> m_strAlias);
			if (ulMerkmalsKode <= 0)
				return E_FAIL;

		//	lese alle Objektklassen, die diese Anbindung haben
			rstrClasses = ProFile.GetObjClasses (m_pFeldInfos -> m_strAlias, rstrKoppelFeld, ulMerkmalsKode);
			if (rstrClasses.IsEmpty())
				return E_FAIL;
	
		// Recordset bauen
			rRecSet.m_pDatabase = pCDataBase;

		// Recordset öffnen
		CString strSelect;

			if (!GetSQLStmt(rgFlags, pcToMatch, rstrKoppelFeld, strSelect) ||
				!rRecSet.Open (CRecordset::forwardOnly, strSelect, CRecordset::readOnly))
			{
				return E_FAIL;
			}
		}
	}
	CATCH (CMemoryException, e)	
	{   
		return E_OUTOFMEMORY;
	}                
	AND_CATCH (CDBException, dbe)   
	{                   
	OdbcError oe (dbe);
	
		oe.Show (RC_InstPropFunction);
		return E_FAIL;
	}
	AND_CATCH (CFileException, fe)
	{
		fe -> ReportError ();
		return E_FAIL;
	}
	END_CATCH                                               
	return S_OK;
}

BOOL CODBCProperty::GetSQLStmt (
	tagSEARCHMODE rgFlags, LPCSTR pcToMatch, CString &rstrKoppelFeld, CString &rstrFilter)
{
CString strFilter;
tagSEARCHMODE rgModifier = tagSEARCHMODE(rgFlags & SEARCHMODE_SEARCHMODIFIERS);

	switch (rgFlags & ~SEARCHMODE_SEARCHMODIFIERS) {
	case SEARCHMODE_NORMAL:
		return GetSQLStmtNormal (rgModifier, pcToMatch, rstrKoppelFeld, rstrFilter);

	case SEARCHMODE_ONLYEXISTANCE:
		return GetSQLStmtExistance (rgModifier, rstrKoppelFeld, rstrFilter);

	case SEARCHMODE_LIKE:
	case SEARCHMODE_REGEXPR:
	default:
		_ASSERTE(FALSE);
		return FALSE;			// hier nicht unterstützt
	}

// Resultat liefern
	rstrFilter = strFilter;
	return TRUE;
}

BOOL CODBCProperty::GetSQLStmtNormal(
	tagSEARCHMODE rgModifier, LPCSTR pcToMatch, CString &rstrKoppelFeld, CString &rstrSelect)
{
// Groß-/Kleinschreibung kann ODBC nicht unterscheiden
	_ASSERTE(IsNumeric(m_pFeldInfos -> m_iDataType) || (SEARCHMODE_NOMATCHCASE & rgModifier));

CString strFilter;
CString strNot ((rgModifier & SEARCHMODE_NEGATERESULT) ? "NOT" : "");

	rgModifier = tagSEARCHMODE(rgModifier & ~SEARCHMODE_NEGATERESULT);

	if (SEARCHMODE_NOMATCHCASE == (rgModifier & SEARCHMODE_SEARCHMODIFIERS)) {
	// SELECT DISTINCT [Koppelfeld] from [Tabelle] WHERE NOT? [Name] = 'Suchstring'
		_ASSERTE(NULL != pcToMatch);

		if (SQL_CHAR == m_pFeldInfos -> m_iDataType || SQL_VARCHAR == m_pFeldInfos -> m_iDataType) {
		// Feld enthält Zeichenketten
			strFilter.Format ("(%s [%s] = '%s')", (LPCSTR)strNot, (LPCSTR)m_pFeldInfos -> m_strFeldName, pcToMatch);
			rstrSelect.Format (IDS_SELECT_PARSE_FORMAT, (LPCSTR)rstrKoppelFeld, (LPCSTR)m_pFeldInfos -> m_strTableName, (LPCSTR)strFilter);
		}
		else {
		// anderer Datentyp, erfordert spezielle Konvertierung
		// SELECT DISTINCT [Koppelfeld] from [Tabelle] 
		// WHERE (NOT? ( { fn LOCATE('ToSearch', `Feldname`) } = 1 AND { fn LENGTH(`Feldname`) } = strlen(ToSearch) ) )
			strFilter.Format ("(%s ({ fn LOCATE('%s', `%s`)} = 1 AND { fn LENGTH(`%s`)} = %d))", 
				(LPCSTR)strNot, pcToMatch, (LPCSTR)m_pFeldInfos -> m_strFeldName, 
				(LPCSTR)m_pFeldInfos -> m_strFeldName, strlen(pcToMatch));
			rstrSelect.Format (IDS_SELECT_PARSE_FORMAT, (LPCSTR)rstrKoppelFeld, (LPCSTR)m_pFeldInfos -> m_strTableName, (LPCSTR)strFilter);
		}
		return TRUE;
	}
	if (SEARCHMODE_PARTIALMATCHBOB & rgModifier) {
	// SELECT DISTINCT [Koppelfeld] from [Tabelle] WHERE [Name] = 'Suchstring%'
		_ASSERTE(NULL != pcToMatch);

		strFilter.Format ("(%s [%s] LIKE '%s%%')", (LPCSTR)strNot, (LPCSTR)m_pFeldInfos -> m_strFeldName, pcToMatch);
		rstrSelect.Format (IDS_SELECT_PARSE_FORMAT, (LPCSTR)rstrKoppelFeld, (LPCSTR)m_pFeldInfos -> m_strTableName, (LPCSTR)strFilter);
		return TRUE;
	}
	if (SEARCHMODE_PARTIALMATCH & rgModifier) {
	// SELECT DISTINCT [Koppelfeld] from [Tabelle] WHERE [Name] = '%Suchstring%'
		_ASSERTE(NULL != pcToMatch);

		strFilter.Format ("(%s [%s] LIKE '%%%s%%')", (LPCSTR)strNot, (LPCSTR)m_pFeldInfos -> m_strFeldName, pcToMatch);
		rstrSelect.Format (IDS_SELECT_PARSE_FORMAT, (LPCSTR)rstrKoppelFeld, (LPCSTR)m_pFeldInfos -> m_strTableName, (LPCSTR)strFilter);
		return TRUE;
	}
	return FALSE;
}

BOOL CODBCProperty::GetSQLStmtExistance(
	tagSEARCHMODE rgModifier, CString &rstrKoppelFeld, CString &rstrSelect)
{
CString strFilter;
CString strNot ((rgModifier & SEARCHMODE_NEGATERESULT) ? "NOT" : "");

// SELECT DISTINCT [Koppelfeld] from [Tabelle] WHERE [Name] IS NOT? NULL 
	strFilter.Format ("(%s [%s] IS NULL)", (LPCSTR)strNot, (LPCSTR)m_pFeldInfos -> m_strFeldName);
	rstrSelect.Format (IDS_SELECT_PARSE_FORMAT, (LPCSTR)rstrKoppelFeld, (LPCSTR)m_pFeldInfos -> m_strTableName, (LPCSTR)strFilter);
	return TRUE;
}


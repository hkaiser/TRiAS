// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 31.05.99 22:24:24
//
// @doc
// @module ExportAsXml.cpp | TXI/TXM-Export als XML-Datei

#include "idntsdbp.hxx"

#include <locale.h>
#include <ospace/time/timedate.h>
#include <ospace/file/path.h>

#include <eieruhr.hxx>
#include <statguid.h>
#include <registrx.hxx>

#include "identres.h"		// Resourcen
#include "Strings.h"

#include "identsdb.h"
#include "defiderr.hxx"
#include "defabout.hxx"
#include "identsdb.hxx"

#include "ExportAsXml.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// 
int CXMLElement::m_iIndent = 0;

// globale Funktionen
char *RemoveNewLines (char *pText);

///////////////////////////////////////////////////////////////////////////////
// Export eines Identifikatoreintrages 
typedef struct tagEXPORTDATA {
	int fh;
	LPUNKNOWN pIUnk;
	ULONG ulCnt;
	ULONG ulIdent;
} EXPORTDATA;

///////////////////////////////////////////////////////////////////////////////
// Export eines Merkmalseintrages 
extern "C" 
BOOL _XTENSN_EXPORT PASCAL ExportMCodeEntryAsXml (long MCode, DWORD, void *pData)
{
PBDMERKMAL pbdData;
char KText[34];
char pLText[1025];
                                          
	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKText = KText;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 1024;
	
ErrCode RC = DEX_GetPBDData (pbdData);

	KText[32] = '\0';

// Systemmerkmale nicht ausgeben
	if (pbdData.ipbdMTyp & MPSystemFeatures || !strncmp (KText, "__", 2))
		return true;

EXPORTDATA *pED = (EXPORTDATA *)pData;

	RemoveNewLines (pbdData.pbdLText);

CXMLAttribute Attr (g_cbMCode, (10 == DEX_GetMkBase()) ? "%08ld" : "0x%08lx", DEX_MapHandleToMCode(MCode));
CXMLNode Node (pED -> fh, g_cbFeature, Attr);

// nur OBJEKT-Eigenschaften ausgeben
	if (pbdData.ipbdMTyp & MPReadOnlyFeatures) {
	string strType = char (toupper(pbdData.ipbdMTyp & 0xff));

		strType += 'R';		// readonly
		CXMLText (pED -> fh, g_cbType, strType.c_str());
	}

// KurzText, Langtext ausgeben
	{
	CXMLAttribute IsDefault (g_cbIsDefault, "%d", EC_OKAY == RC ? 0 : 1);

		CXMLText (pED -> fh, g_cbName, pbdData.pbdKText, IsDefault);
	}
	if (pbdData.pbdLTextLen > 0 && pbdData.pbdLText[0] != '\0') {
		CXMLText (pED -> fh, g_cbDescription, pbdData.pbdLText);
	}
	if (_MAX_PATH != pbdData.ipbdMLen && 256 != pbdData.ipbdMLen) {
		CXMLTextEx (pED -> fh, g_cbLength, "%d", pbdData.ipbdMLen);
	}

//	if (pED -> pIUnk) {
//		LPPROGRESSINDICATOR(pED -> pIUnk) -> SetPosition (++(pED -> ulCnt));
//		if (LPPROGRESSINDICATOR(pED -> pIUnk) -> WasCanceled()) 
//			return false;		// abbrechen
//	}
	return true;	// weitermachen
}

extern "C" 
BOOL _XTENSN_EXPORT PASCAL ExportIdentEntryAsXml (long Ident, BOOL, void *pData)
{
PBDDATA pbdData;
char KText[34];
char pLText[1025];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdLText = pLText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 1024;

ErrCode RC = DEX_GetPBDData (pbdData);

	KText[32] = '\0';

EXPORTDATA *pED = (EXPORTDATA *)pData;

	RemoveNewLines (pbdData.pbdLText);

char cbBuffer[MAX_OKS_LENX];
HRESULT hr = ClassFromIdentX (Ident, cbBuffer);
CXMLAttribute Attr (g_cbIdent, (10 == DEX_GetIdBase()) ? "%ld" : "0x%lx", Ident);
CXMLNode Node (pED -> fh, g_cbObjectClass, Attr);

	if (EXPORTMODE_Normal == (s_rgExportMode & EXPORTMODE_TXI)) {
		if (S_OK == hr) {
			CXMLText (pED -> fh, g_cbOKS, cbBuffer);
		} 
	} else {
		if (SUCCEEDED(hr) && s_rgExportMode & EXPORTMODE_OKSOnly) {	// S_OK oder S_FALSE
			CXMLText (pED -> fh, g_cbOKS, cbBuffer);
		} 
	}

// evtl. Tabellennamen ausgeben
TABLENAME TN;

	INITSTRUCT(TN, TABLENAME);
	TN.lIdent = Ident;
	TN.pBuffer = cbBuffer;
	TN.iLen = sizeof(cbBuffer);

	hr = DEX_GetTableName (TN);
	if (S_OK == hr) 
		CXMLText (pED -> fh, g_cbTableName, cbBuffer);

// KurzText, Langtext ausgeben
	{
	CXMLAttribute IsDefault (g_cbIsDefault, "%d", EC_OKAY == RC ? 0 : 1);

		CXMLText (pED -> fh, g_cbName, pbdData.pbdKText, IsDefault);
	}
	if (pbdData.pbdLTextLen > 0 && pbdData.pbdLText[0] != '\0') {
	// Langtext (Beschreibungstext ausgeben
		CXMLText (pED -> fh, g_cbDescription, pbdData.pbdLText);
	} 

// Objekteigenschaften ausgeben
bool fRet = true;

// Identifikator übergeben
	pED -> ulIdent = (ULONG)Ident;

	{
	CXMLNode Feats (pED -> fh, g_cbObjectFeatures);
	ENUMLONGKEYEX ELK;

		ELK.eKey = Ident;
		ELK.eFcn = (ENUMLONGKEYEXPROC)ExportMCodeEntryAsXml;
		ELK.ePtr = pED;
		ELK.eData = MPObjectFeature|MPReadOnlyFeatures|FEATURETYPE_DefinitionOnly /*|MPSystemFeatures*/;
		fRet = DEX_EnumObjektMerkmaleClassEx (ELK);
	}

	if (pED -> pIUnk) {
		LPPROGRESSINDICATOR(pED -> pIUnk) -> SetPosition (++(pED -> ulCnt));
		if (LPPROGRESSINDICATOR(pED -> pIUnk) -> WasCanceled()) 
			return false;		// abbrechen
	}
	return fRet;	// weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// Exportieren aller PBD-IdentifikatorEinträge 
typedef struct tagENUMDATASOURCES {
	CIdentsDBExtension *pThis;
	LPUNKNOWN pUnk;
	LPCSTR pcFName;
	ULONG ulCnt;
} ENUMDATASOURCES;

extern "C"
BOOL _XTENSN_EXPORT PASCAL EnumDataSources (LPSTR pcPath, BOOL, void *pData)
{
ENUMDATASOURCES *pEDS = (ENUMDATASOURCES *)pData;
HPROJECT hPr = DEX_GetDataSourceHandleEx (pcPath);

	TX_ASSERT(NULL != hPr);
	if (!DEX_GetOpenedEx(hPr))
		return TRUE;		// diese Datenquelle ist nicht geöffnet

os_path path (pEDS -> pcFName);

	if (!path.has_extension())
		path.extension ("txc");

os_string strT;
char cbBuffer[_MAX_PATH];

	DEX_GetDataSourceShortName(hPr, cbBuffer);
	Format (strT, "%s (%s)", path.base().c_str(), cbBuffer);
	path.base (strT);
	return pEDS -> pThis -> ExportDataSourceAsXml (pEDS -> pUnk, hPr, os_string(path).c_str(), pEDS -> ulCnt);
}

bool CIdentsDBExtension::ExportAsXml (LPUNKNOWN pIUnk, LPCSTR pFName) 
{
ENUMNOKEY ENK;
ENUMDATASOURCES EDS;

	EDS.pThis = this;
	EDS.pUnk = pIUnk;
	EDS.pcFName = pFName;
	EDS.ulCnt = 0;

	ENK.eFcn = (ENUMNOKEYPROC)EnumDataSources;
	ENK.ePtr = &EDS;
	return DEX_EnumDataSources (ENK);
}

const char *s_cbDTD[] = {
	"<!DOCTYPE TRiAS_Metadata [\r\n",
	"\t<!ELEMENT TRiAS_Metadata (ObjectClass*)>\r\n",
	"\t<!ELEMENT ObjectClass (OKS?, TableName?, Name, Description?, ObjectFeatures)>\r\n",
	"\t<!ELEMENT OKS (#PCDATA)>\r\n",
	"\t<!ELEMENT Name (#PCDATA)>\r\n",
	"\t<!ELEMENT TableName (#PCDATA)>\r\n",
	"\t<!ELEMENT Description (#PCDATA)>\r\n",
	"\t<!ELEMENT ObjectFeatures (Feature*)>\r\n",
	"\t<!ELEMENT Feature (Type?, Name, Description?, Length?)>\r\n",
	"\t<!ELEMENT Length (#PCDATA)>\r\n",
	"\t<!ELEMENT Type (#PCDATA)>\r\n",
	"\t<!ATTLIST TRiAS_Metadata Version CDATA \"1.0\">\r\n",
	"\t<!ATTLIST ObjectClass Ident CDATA \"\">\r\n",
	"\t<!ATTLIST Name IsDefault CDATA \"\">\r\n",
	"\t<!ATTLIST Feature MCode CDATA \"\">\r\n",
	"]>\r\n",
	NULL,
};

bool CIdentsDBExtension::ExportDataSourceAsXml (LPUNKNOWN pIUnk, HPROJECT hPr, LPCSTR pFName, ULONG &rulCnt) 
{
	if (pIUnk) LPPROGRESSINDICATOR(pIUnk) -> ChangeText (PIFLAG_FILENAME, pFName);

// Datei bilden, wenn diese noch nicht existiert
int fh = _lcreat (pFName, 0);

	if (fh < 0) return false;

bool fRet = false;

	{
	// hier geht's los
	CXMLDocument Doc (fh);		// <?xml ...?>

	char cbBuffer[80];			// TRiAS Version, aktuelle Zeit 
	os_time_and_date now;
	string resVersion (g_cbTRiAS);
	ResString resTempl (IDS_SIGNONVERSION_MODAL, _MAX_PATH);
	
		resVersion += ": ";
		resVersion += resTempl;
	
		ATLTRY(now = os_time_and_date::now());
		strcpy (cbBuffer, resVersion.c_str());
		strcat (cbBuffer, now.to_string(" %e. %B %Y, %T").c_str());
	
		CXMLComment (fh, cbBuffer);
		CXMLComment (fh, ResString (IDS_COPYRIGHT, 100));	// allgemeines Copyright

	// DTD einfügen
		CXMLRawData (fh, s_cbDTD);

	// die eigentlichen Infos ausgeben
	CXMLAttribute Attr ("Version", "1.0");
	CXMLNode MainNode (fh, g_cbTRiASMetadata, Attr);

	ENUMLONGKEY ELK;
	EXPORTDATA ED;

		ED.fh = fh;
		ED.pIUnk = pIUnk;
		ED.ulCnt = rulCnt;

		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)ExportIdentEntryAsXml;
		ELK.ePtr = &ED;
		fRet = DEX_EnumPBDDataEx (hPr, ELK);
		rulCnt = ED.ulCnt;
	}

// Datei wieder schließen
	_lclose (fh);		// Datei schließen
	return fRet;
}


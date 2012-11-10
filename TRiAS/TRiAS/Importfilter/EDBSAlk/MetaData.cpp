// MetaData.cpp: implementation of the CMetaData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxtempl.h>

#include <errcodes.hxx>                 // Fehlermeldungen
#include <hdrentrx.hxx>                 // HeaderEntryX

extern "C"
{
#include <xtension.h>
#include <xtensnn.h>
#include <xtensnx.h>
}

#include <atlbase.h>
#include "trif.hpp"
#include <errinstx.hxx>					// ErrInstall
#include "cxstring.h"
#include "EDBS.hpp"
#include "Cfg.h"
#include "MetaData.h"
#include "ObjectAttributeTRiAS.h"

//#include <comip.h>

//typedef CMap<char*,,CObjectClassTRiAS*,CObjectClassTRiAS*> CMapObjectClassesTRiAS;

//CMapObjectClassesTRiAS* pMapObjectClassesTRiAS = new CMapObjectClassesTRiAS;
// Map on the heap with default blocksize

unsigned long ulObjectClassesTRiASIdent = 0;

bool				g_bKurzeIdents;
short				g_iKoordFormat;

bool IsHexDigit( char c )
{	bool	result = FALSE;

	if (( c >= '0' ) && ( c <= '9' )) result = TRUE;
	else if (( c >= 'A' ) && ( c <= 'F' )) result = TRUE;
	else if (( c >= 'a' ) && ( c <= 'f' )) result = TRUE;
	return result;
}

HRESULT IdFromClassX( const char* klasse, unsigned long *pid, BOOL flag )
{
	CString		cls;
	char		*x;

	cls = klasse;
	cls.TrimLeft();	cls.TrimRight();

	x = cls.GetBuffer( 0 );
	while ( '\0' != *x )
	{
		if ( !IsHexDigit( *x ))		*x = '0';
		x++;
	}
	cls.ReleaseBuffer();

	if ( g_bKurzeIdents )
		while( cls.GetLength() > 0 && ( cls.Right( 1 ) == "0"  || !IsHexDigit( *(const char*)cls.Right( 1 ))))
			cls = cls.Left( cls.GetLength() -1 );

	if ( cls.GetLength())
		return IdentFromClassX( DEX_GetDataSourceHandle(), cls, pid, flag );
	else
		return (HRESULT)-1L;
}	// IdFromClassX

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMetaData::CMetaData()
{
	m_lVerDatabase = 0;
	m_dKoeffEDBS = 0;
	m_bHexIdents = ( DEX_GetIdBase() == 16 );
	m_bHexMKodes = ( DEX_GetMkBase() == 16 );
	m_lOffsetX = -1;
	m_lOffsetY = -1;
	m_dKoeff11 = 0;
	m_dKoeff12 = 0;
	m_dKoeff21 = 0;
	m_dKoeff22 = 0;
	m_sRH = 0;
	m_sKoordinatensystem = 0;
	g_bKurzeIdents = TRUE;

	pConfiguration = &((CEDBSExtension*)g_pTE)->Configuration;
}

CMetaData::~CMetaData()
{

	POSITION	pos;
	CString		key;
	CObjectClassTRiAS	*pObjectClassTRiAS;
	CRule_Line	*pRule_Line;
	CRule_Layer	*pRule_Layer;
	CRule_Info	*pRule_Info;
	CRule_Geom	*pRule_Geom;
	CRule_Attr	*pRule_Attr;
	CRule_Text	*pRule_Text;
	CRegel		*rule;

//	IUnknown		*pEDBSXXinstance;

	for ( pos = m_Rules_Info.GetStartPosition(); pos != NULL; ) {
		m_Rules_Info.GetNextAssoc( pos, key, (CObject*&)pRule_Info );
		delete pRule_Info;
	}
	m_Rules_Info.RemoveAll();

	for ( pos = m_Rules_Line.GetStartPosition(); pos != NULL; ) {
		m_Rules_Line.GetNextAssoc( pos, key, (CObject*&)pRule_Line );
		delete pRule_Line;
	}
	m_Rules_Line.RemoveAll();

	for ( pos = m_Rules_Geom.GetStartPosition(); pos != NULL; ) {
		m_Rules_Geom.GetNextAssoc( pos, key, (CObject*&)pRule_Geom );
		delete pRule_Geom;
	}
	m_Rules_Geom.RemoveAll();

	for ( pos = m_Rules_Attr.GetStartPosition(); pos != NULL; ) {
		m_Rules_Attr.GetNextAssoc( pos, key, (CObject*&)pRule_Attr );
		delete pRule_Attr;
	}
	m_Rules_Attr.RemoveAll();

	for ( pos = m_Rules_Text.GetStartPosition(); pos != NULL; ) {
		m_Rules_Text.GetNextAssoc( pos, key, (CObject*&)pRule_Text );
		delete pRule_Text;
	}
	m_Rules_Text.RemoveAll();

	for ( pos = m_ObjectClassesTRiAS.GetStartPosition(); pos != NULL; ) {
		m_ObjectClassesTRiAS.GetNextAssoc( pos, key, (CObject*&)pObjectClassTRiAS );
		delete pObjectClassTRiAS;
	}
	m_ObjectClassesTRiAS.RemoveAll();

	for ( pos = m_Rules_Layer.GetStartPosition(); pos != NULL; ) {
		m_Rules_Layer.GetNextAssoc( pos, key, (CObject*&)pRule_Layer );
		delete pRule_Layer;
	}
	m_Rules_Layer.RemoveAll();

	
	for ( pos = m_B_Rules.GetStartPosition(); pos != NULL; )
	{	m_B_Rules.GetNextAssoc( pos, key, (void*&)rule );
		delete rule;
	}
	m_B_Rules.RemoveAll();

	ErrorLogAttributes.RemoveAll();

/*	for ( pos = m_EDBSXXinstances.GetStartPosition(); pos != NULL; )
	{	m_EDBSXXinstances.GetNextAssoc( pos, key, (void*&)pEDBSXXinstance );
		if( NULL != pEDBSXXinstance )
			pEDBSXXinstance->Release();
	}
	m_EDBSXXinstances.RemoveAll();
*/
}
void CMetaData::SetDefinition( const CString& strDef )
{
	strIniFileName = strDef;	
}

void CMetaData::Load()
{
	CRegKey regEDBS;
	char  straConfig[MAX_PATH];
	DWORD cbConfig;
	CxString strConfigPath;
	CxString strBuffer;
	CString strRegKey(TRiAS_REGKEY);

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\TRiAS.EDBSALK.1\\Config");

	
	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ObjectClassesTRiAS", &cbConfig ) )
		m_strObjectClassesTRiAS = straConfig;
	else
		m_strObjectClassesTRiAS = "D";

	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ObjectAttributesTRiAS", &cbConfig ) )
		m_strObjectAttributesTRiAS = straConfig;
	else
		m_strObjectAttributesTRiAS = "49";

	if( pConfiguration->m_strConfigFile != "Default" ) 
		pConfiguration->ConnectCfgDb();
	strBuffer = pConfiguration->GetCfgDbEntry("VERDATABASE");
	if( strBuffer.IsEmpty() )
		m_lVerDatabase = 0;
	else
		m_lVerDatabase = atol(strBuffer);

	strBuffer = pConfiguration->GetCfgDbEntry("CFGCODEPAGE");
	if( strBuffer.IsEmpty() ) {
		cbConfig = MAX_PATH;
		if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"Codepage", &cbConfig ) )
			strBuffer = straConfig;
		else
			strBuffer = "STANDARD";
	}
	strBuffer.MakeUpper();
	if( strBuffer == "STANDARD" )
		pConfiguration->m_sCodePage = 0;
	else if( strBuffer == "ASCII" )
		pConfiguration->m_sCodePage = 1;
	else if( strBuffer == "UNIX" )
		pConfiguration->m_sCodePage = 2;
	else
		pConfiguration->m_sCodePage = 0;

	strBuffer = pConfiguration->GetCfgDbEntry("CFGDEFAULT");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tDefaultObjectMapping = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tDefaultObjectMapping = false;
	else
		pConfiguration->m_tDefaultObjectMapping = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_DEFAULTOBJECTMAPPING));

	strBuffer = pConfiguration->GetCfgDbEntry("CFGOVERWRITERULES");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tOverwriteRules = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tOverwriteRules = false;
	else
		pConfiguration->m_tOverwriteRules = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_OVERWRITERULES));

//=== EDBS Allgemein =================================================

	strBuffer.GetPrivateProfileString( "EDBS Allgemein",
		"ArcPecision", "-4", 255, strIniFileName );
	dArcPrecision = atof( strBuffer );

	strBuffer.GetPrivateProfileString( "EDBS Allgemein",
		"KurzeIdents", "", 255, strIniFileName );
	if ( strBuffer == "nein" )
		g_bKurzeIdents = FALSE;

//=== Koordinatensystem =================================================

	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"§Koordinatensystem", "", 255, strIniFileName2 );
	strBuffer.MakeUpper();
	if ( strBuffer == "SOLDNER" )
		m_sKoordinatensystem = 3;
	else
		m_sKoordinatensystem = 0;

	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"§Koordinatentyp", "", 255, strIniFileName2 );
	strBuffer.MakeUpper();
	if( strBuffer == "RH" )
		m_sRH = 1;
	else if( strBuffer == "HR" )
		m_sRH = -1;
	else
		m_sRH = 0;

	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"§KoeffEDBS", "0",	255, strIniFileName2 );
	m_dKoeffEDBS = strBuffer.Double();
	
	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"Koeff11", "0",	255, strIniFileName2 );
	m_dKoeff11 = strBuffer.Double();
	
	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"Koeff12", "0",	255, strIniFileName2 );
	m_dKoeff12 = strBuffer.Double();
	
	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"Koeff21", "0",	255, strIniFileName2 );
	m_dKoeff21 = strBuffer.Double();

	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"Koeff22", "0",	255, strIniFileName2 );
	m_dKoeff22 = strBuffer.Double();
	
	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"OffsetX", "-1", 255, strIniFileName2 );
	m_lOffsetX = strBuffer.Long();

	strBuffer.GetPrivateProfileString( "Koordinatensystem",
		"OffsetY", "-1", 255, strIniFileName2 );
	m_lOffsetY = strBuffer.Long();

//=== Objekterzeugung ================================================================

	strBuffer = pConfiguration->GetCfgDbEntry("CFGIMPORTAREAS");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tImportAreas = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tImportAreas = false;
	else
		pConfiguration->m_tImportAreas = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_IMPORTAREAS));

	strBuffer = pConfiguration->GetCfgDbEntry("CFGIMPORTLINES");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tImportLines = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tImportLines = false;
	else
		pConfiguration->m_tImportLines = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_IMPORTLINES));
	
	strBuffer = pConfiguration->GetCfgDbEntry("CFGIMPORTPOINTS");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tImportPoints = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tImportPoints = false;
	else
		pConfiguration->m_tImportPoints = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_IMPORTPOINTS));
	
	strBuffer = pConfiguration->GetCfgDbEntry("CFGIMPORTTEXT");
	strBuffer.MakeUpper();
	if( strBuffer == "JA" )
		pConfiguration->m_tImportText = true;
	else if( strBuffer == "NEIN" )
		pConfiguration->m_tImportText = false;
	else
		pConfiguration->m_tImportText = 
		(0 != (pConfiguration->m_dwConfigBase & EDBSCFG_IMPORTTEXT));

	strBuffer.GetPrivateProfileString( "EDBS Allgemein",
		"Fehlerprotokoll erzeugen", "nein", 255, strIniFileName );
	m_bCreateErrorLog = ( strBuffer == "ja" );
	if( m_bCreateErrorLog ) {
		int i = 1;
		CxString strTemp;
		strTemp.printf( "M%d", i++ );
		while ( strBuffer.GetPrivateProfileString( "Fehlerprotokoll", strTemp, "",
						255, strIniFileName )) {
			ErrorLogAttributes.AddTail( strBuffer );			
			strTemp.printf( "M%d", i++ );
		}
	}

	Filter.GetPrivateProfileString( "EDBS Allgemein",
		"Filter", "", 255, strIniFileName );


//=== Standardattribute ============================================================================
	m_ObjectAttributesTRiAS.SetTyp( 'm' );

	LoadRules_Layer();
	LoadObjectClassesTRiAS();
	LoadObjectClassesEDBS();
	m_strKomplexobjekte = pConfiguration->GetCfgDbEntry("CFGX1");
	LoadRules_Line();
	LoadRules_Info();
//	LoadClassification();
	LoadRules_Geom();
	LoadRules_Text();
//	LoadRules_Attr();

	if( pConfiguration->m_dbCfg.IsOpen() )
		pConfiguration->m_dbCfg.Close();

	regEDBS.Close();
}

CRule_Line *CMetaData::GetRule_Line( CString &strKey )
{
	CRule_Line	*pRule_Line = NULL;
	CString		strTest;
	bool		tFound;

	tFound = m_Rules_Line.Lookup( strKey, (CObject*&)pRule_Line );
	if( !tFound ) {
		if( '9' < strKey.GetAt(3) ) {	// L,R,A,Z,N...
			strTest = strKey.Left(4) + "000";
			tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
			if( !tFound ) {
				strTest = "000" + strKey.Mid(4,1) + "000";
				tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
				if( !tFound ) {
					strTest = strKey.Left(3) + "0" + strKey.Mid(4);
					tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
					if( !tFound ) {
						strTest = "0000" + strKey.Mid(4);
						tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
					}
				}
			}
		}
		else {
			strTest = "000" + strKey.Mid(3);
			tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
			if( !tFound ) {
				strTest = strKey.Left(3) + "0000";
				tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
			}
		}
	}

	if( !tFound ) {
		strTest = "0000000";
		tFound = m_Rules_Line.Lookup( strTest, (CObject*&)pRule_Line );
	}

	if( !tFound && 	pConfiguration->m_tDefaultObjectMapping ) {
		pRule_Line = new CRule_Line( strKey );
		pRule_Line->Importmodus_Hauptgeometrie() = 1;
		pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() = false;
		pRule_Line->Importmodus_Zusatzgeometrie() = 0;
		pRule_Line->Objektklasse_Hauptgeometrie() = pConfiguration->m_strObjectClassesTRiAS + strKey;
		pRule_Line->Objektklasse_Zusatzgeometrie() = "";
		
		m_Rules_Line.SetAt( pRule_Line->Key(), pRule_Line );
		tFound = true;
	}
	return pRule_Line;
}

CRule_Layer * CMetaData::GetRule_Layer( CString &strKey, BOOL fDefault )
{
	CRule_Layer *pRule_Layer;
	if( m_Rules_Layer.Lookup( strKey, (CObject*&)pRule_Layer ) )
		return pRule_Layer;
	else if( m_Rules_Layer.Lookup( "000", (CObject*&)pRule_Layer ) )
		return pRule_Layer;
	else if( pConfiguration->m_tDefaultObjectMapping && fDefault) {
		pRule_Layer = new CRule_Layer( strKey );
		pRule_Layer->Kurztext() = "ALK-Objekte in Folie " + strKey;
		pRule_Layer->Langtext() = "";
		pRule_Layer->ObjectClassTRiAS() = pConfiguration->m_strObjectClassesTRiAS + strKey + "0000";
		pRule_Layer->ImportMode() = 1;
		pRule_Layer->Resolve(true);
		m_Rules_Layer.SetAt( strKey, pRule_Layer );
		return pRule_Layer;
	}
	else
		return NULL;
}

CRule_Attr *CMetaData::GetRule_Attr( CString &strKey )
{
	CRule_Attr *pRule_Attr;

	if( m_Rules_Attr.Lookup( strKey, (CObject*&)pRule_Attr ) )
		return pRule_Attr;
	else if( m_Rules_Attr.Lookup( strKey.Left(3) + "0000", (CObject*&)pRule_Attr ) )
		return pRule_Attr;
	else if( m_Rules_Attr.Lookup( "0000000", (CObject*&)pRule_Attr ) )
		return pRule_Attr;
	else if( pConfiguration->m_tDefaultObjectMapping && pConfiguration->m_tCreateBIattr) {
		pRule_Attr = new CRule_Attr( strKey );
		pRule_Attr->AttributeName() = "ALK-Merkmal "
									+ strKey.Mid( 7, 4 )
									+ "(" + strKey.Mid( 11, 2 ) + ")";
		m_Rules_Attr.SetAt( strKey, pRule_Attr );
		return pRule_Attr;
	}
	else
		return NULL;
}

CRule_Text *CMetaData::GetRule_Text( CString &strKey )
{
	CRule_Text *pRule_Text;

	if( m_Rules_Text.Lookup( strKey, (CObject*&)pRule_Text ) )
		return pRule_Text;
	else if( m_Rules_Text.Lookup( strKey.Left(3) + "0000" + strKey.Mid(7), (CObject*&)pRule_Text ) )
		return pRule_Text;
	else if( m_Rules_Text.Lookup( strKey.Left(3) + "00000000" + strKey.Mid(11), (CObject*&)pRule_Text ) )	// #HK000915
		return pRule_Text;
	else if( m_Rules_Text.Lookup( strKey.Left(3) + "0000000000", (CObject*&)pRule_Text ) )
		return pRule_Text;
	else if( m_Rules_Text.Lookup( "0000000000000", (CObject*&)pRule_Text ) )
		return pRule_Text;
	else if( pConfiguration->m_tDefaultObjectMapping && pConfiguration->m_tCreateBItext ) {
		pRule_Text = new CRule_Text( strKey );
		pRule_Text->ObjectClassTRiAS() = pConfiguration->m_strObjectClassesTRiAS
									   + strKey.Left( 3 )
									   + strKey.Mid( 8, 4 );
		m_Rules_Text.SetAt( pRule_Text->Key(), pRule_Text );
		return pRule_Text;
	}
	else
		return NULL;
}

CRule_Geom *CMetaData::GetRule_Geom( CString &strKey )
{
	CRule_Geom *pRule_Geom;

	if( m_Rules_Geom.Lookup( strKey, (CObject*&)pRule_Geom ) )
		return pRule_Geom;
	else if( m_Rules_Geom.Lookup( strKey.Left(3) + "0000", (CObject*&)pRule_Geom ) )
		return pRule_Geom;
	else if( m_Rules_Geom.Lookup( "0000000", (CObject*&)pRule_Geom ) )
		return pRule_Geom;
	else if( pConfiguration->m_tDefaultObjectMapping && pConfiguration->m_tCreateBIgeom) {
		pRule_Geom = new CRule_Geom( strKey );
		pRule_Geom->ObjectClassTRiAS() = pConfiguration->m_strObjectClassesTRiAS
									   + strKey.Left( 3 )
									   + strKey.Mid( 8, 4 );
		m_Rules_Geom.SetAt( strKey, pRule_Geom );
		return pRule_Geom;
	}
	else
		return NULL;
}

CRule_Info* CMetaData::GetRule_Info(CString &strKey)
{
	CRule_Info	*pRule_Info;

	if( m_Rules_Info.Lookup( strKey, (CObject*&)pRule_Info ) )
		return pRule_Info;
	else if( m_Rules_Info.Lookup( strKey.Left(3) + "0000" + strKey.Mid(7), (CObject*&)pRule_Info ) )
		return pRule_Info;
	else if( m_Rules_Info.Lookup( strKey.Left(3) + "00000000" + strKey.Mid(11), (CObject*&)pRule_Info ) )	// #HK000915
		return pRule_Info;
	else if( m_Rules_Info.Lookup( strKey.Left(3) + "0000000000", (CObject*&)pRule_Info ) )
		return pRule_Info;
	else if( m_Rules_Info.Lookup( "0000000000000", (CObject*&)pRule_Info ) )
		return pRule_Info;
	else if( pConfiguration->m_tDefaultObjectMapping ) {
		pRule_Info = new CRule_Info( strKey );
		pRule_Info->AutoRule() = true;

		pRule_Info->ObjektartBI_bestimmt_Objektklasse_Hauptgeometrie() = false;
		pRule_Info->ObjectClassTRiAS_Hauptgeometrie() = "";

		pRule_Info->Importmodus_Detailgeometrie() = 1;
		pRule_Info->Objektart_bestimmt_Objektklasse_Detailgeometrie() = false;
		pRule_Info->Objektklasse_Detailgeometrie() = "";

		pRule_Info->Importmodus_Text() = 1;
		pRule_Info->Konvertierung_Text() = "";
		pRule_Info->Objektklasse_Text() = "";

		pRule_Info->Importmodus_Attr() = 1;
		pRule_Info->Konvertierung_Attr() = "";
		pRule_Info->AttributeName() = "ALK-Merkmal "
									+ strKey.Mid( 7, 4 )
									+ "(" + strKey.Mid( 11, 2 ) + ")";

		m_Rules_Info.SetAt( strKey, pRule_Info );
		return pRule_Info;
	}
	else
		return NULL;


}

/**************************************************************************/
/*	CMapAliase  ***********************************************************/
/**************************************************************************/

/**************************************************************************/
/*	Format eines Eintrages: (veraltete Version)                           */
/*                                                                        */
/*	[EDBS]                                                                */
/*	...                                                                   */
/*	In=edbs-code,m,trias-id{,regel|alias{,regel|alias,...}}               */
/*	...                                                                   */
/*	                                                                      */
/*	In                          - nummerierter Eintrag                    */
/*	edbs-code                   - EDBS-Objektklasse (vierstellig)         */
/*	m                           - Anzahl der Regeln/Aliase                */
/*	trias-id                    - TRIAS-Objektklasse (ggf. mit x, y usw.  */
/*	                              für variable Codeteile. Treten vari-    */
/*	                              able Codeteile auf, so werden die x     */
/*	                              durch die erste Regel determiniert, y   */
/*	                              durch die zweite usw.)                  */
/*	regel                       - Name einer Regel                        */
/*	alias                       - Definition eines Alias der Form:        */
/*	                                 fkt:name                             */
/*	Dabei steht fkt für die Funktionsart und name für die Merkmalskurz-   */
/*	bezeichnung unter der der Text dieser Objektfunktion abgelegt wird.   */
/*	Weitere Besonderheit: Bei Funktionsart 44 werden automatisch und ohne */
/*	Definition eines Alias die ersten beiden Zeichen des Textes als Funk- */
/*	tionsart verwendet. Der eigentliche Text wird entsprechend gekürzt:   */
/*	Beispiel:                                                             */
/*	                       Funktionsart      Text                         */
/*	                           44            GNMagdeburg                  */
/*	                           44            ZNRothensee                  */
/*	wird umgewandelt in:                                                  */
/*	                           GN            Magdeburg                    */
/*	                           ZN            Rothensee                    */
/**************************************************************************/
/*	Format eines Eintrages: (aktuelle Version)                            */
/*                                                                        */
/*	[TYPEN]                                                               */
/*	...                                                                   */
/*	Tn=edbs-code,trias-id,text                                            */
/*	...                                                                   */
/*                                                                        */
/*	[edbs-code]                                                           */
/*	A1=attr:merkmal                                                       */
/*	...                                                                   */
/*	B1=attr,wert,trias-id                                                 */
/*	...                                                                   */
/*	                                                                      */
/**************************************************************************/
/*
void CMetaData :: LoadRules( const CxString &strKeyEDBS, const CxString &strRules )
{	CxString	strKey, strText, strTemp, strEintrag;
	CxString	strWert, strMerkName;
	CxString	strRulesTemp, strRule;
	CxString	strGen;
	int			i;

//=== laden der B-Regeln ============================================================	
	if ( strText.GetPrivateProfileString( strKeyEDBS, "B1", "",
					255, strIniFileName ))	// es muß mindestens eine B-Regel für den Schlüssel existieren
		m_B_Rules.SetAt( strKeyEDBS, new CRegel( strKeyEDBS, strIniFileName ));
//=== laden der C-Regeln ============================================================	
	strRulesTemp = strRules;
	if( 0 > strRules.Find(strKeyEDBS) ) {
		strRulesTemp += ";";
		strRulesTemp += strKeyEDBS;
	}
	strRulesTemp.Teilen( strRule,strRulesTemp, ';', true );
	while( !strRule.IsEmpty() ) {
		i = 1;
		strTemp.printf( "C%d", i++ );
		while ( strText.GetPrivateProfileString( strRule, strTemp, "",
					255, strIniFileName ))
		{	strText.Teilen( strKey, strText, ',' );
			strWert.Empty();
			strMerkName.Empty();
			if ( !strText.IsEmpty())
				strText.Teilen( strWert, strText, ',' );
			if ( !strText.IsEmpty())
				strText.Teilen( strMerkName, strText, ',' );
	
			if ( !strKey.IsEmpty() && !strWert.IsEmpty() && !strText.IsEmpty())
			{
				strTemp = strMerkName;
				strTemp += "#";
				strTemp += strText;
				strText = strTemp;
				strTemp = strKeyEDBS;
				strTemp += strKey;
				strTemp += ":";
				strTemp += strWert;
//				m_C_Rules.SetAt( strTemp, strText );
			}
			strTemp.printf( "C%d", i++ );
		}
		strRulesTemp.Teilen( strRule,strRulesTemp, ';', true );
	}
}	// AddEintrag
*/
/**************************************************************************/
/*	CMapRegeln  ***********************************************************/
/**************************************************************************/


/**************************************************************************/
/*	Format eines Eintrages: (aktuelle Version)                            */
/*                                                                        */
/*	[TYPEN]                                                               */
/*	...                                                                   */
/*	Tn=edbs-code,trias-id,text                                            */
/*	...                                                                   */
/*                                                                        */
/*	[edbs-code]                                                           */
/*	A1=attr:merkmal                                                       */
/*	...                                                                   */
/*	B1=attr,wert,trias-id                                                 */
/*	...                                                                   */
/*	                                                                      */
/**************************************************************************/
/*
void CMetaData :: AddRule( const char* strKey )
{	CxString	strK, strText, strTemp, strEintrag;
	CxString	strIniFileName;

}
*/
/*
void CMetaData :: GetClassX( const char* strK, CMapStringToString* pmm, CString &strClassX )
{	
	CRegel		*pR = NULL;
	CString		strKeyEDBS, strKey;
	POSITION	pos;

	strClassX.Empty();
	strKeyEDBS = strK;
	if ( !strKeyEDBS.IsEmpty() ) {
		for ( pos = m_B_Rules.GetStartPosition(); pos != NULL; )
		{	m_B_Rules.GetNextAssoc( pos, strKey, (void*&)pR );
			if ( strKeyEDBS == strKey.Left( strKeyEDBS.GetLength()))
				pR -> GetIdent( pmm, strClassX );
		}
	}
}
*/

bool CMetaData::ClassifyGeoObject( CGeoObj& GeoObject )
//unsigned long CTriasInterface::GetIdent( const char* objart, CMapStringToString* pmm )
{	
	unsigned long ulClassIdentTRiAS = 0;
	CObjectClassTRiAS*	pObjectClassTRiAS = NULL;
	CRule_Layer *pRule_Layer;
	PBDDATA*	pbdi;
	ErrInstall	*ErrInst;
	HRESULT	res;
	CxString strObjectClassEDBS;
	CxString strObjectClassTRiAS;
	CxString strClassName;
	CxString strClassDescription;

	if( NULL != GeoObject.ObjectClassTRiAS() ) {
		// TRiAS-Objektklasse wurde bereits festgelegt
	}
	else {
		pRule_Layer = GetRule_Layer( GeoObject.Folie() );
		if( pRule_Layer ) {
			if( 0 != pRule_Layer->ImportMode() ) {
				if( pRule_Layer->Resolve() ) {
						strObjectClassTRiAS = pConfiguration->m_strObjectClassesTRiAS
									   + GeoObject.Folie() + GeoObject.Objektart();

				}	// pRule_Layer->Resolve()
				else {
					if( pRule_Layer->ObjectClassTRiAS().IsEmpty() )
						strObjectClassTRiAS = pConfiguration->m_strObjectClassesTRiAS
									   + pRule_Layer->Folie() + "0000";
					else
						strObjectClassTRiAS = pRule_Layer->ObjectClassTRiAS();

				}	// pRule_Layer->Resolve()
			}	// ImportMode
		}	// pRule_Layer	
		GeoObject.ObjectClassTRiAS() = GetObjectClassTRiAS( strObjectClassTRiAS );
	}


	if( GeoObject.ObjectClassTRiAS() ) {
		// falls eine TRiAS-Objektklasse zugeordnet wurde, muß getestet werden,
		// ob diese Objektklasse in TRiAS schon existiert
		// res = IdFromClassX( GeoObject.ObjectClassTRiAS()->ClassX(), &ulClassIdentTRiAS, false );
		// if( res != 0 ) {
		if( NULL == GeoObject.ObjectClassTRiAS()->ClassIdentTRiAS() ) {
			// Objektklasse in TRiAS erzeugen
			pObjectClassTRiAS = GeoObject.ObjectClassTRiAS();
			res = IdFromClassX( pObjectClassTRiAS->ClassX(), &ulClassIdentTRiAS, true );
			pObjectClassTRiAS->ClassIdentTRiAS() = ulClassIdentTRiAS;
			strClassName = pObjectClassTRiAS->ClassName();
			strClassDescription = pObjectClassTRiAS->ClassDescription();

			pbdi = new PBDDATA;
			if ( pbdi ) {
				memset( pbdi, '\0', sizeof( PBDDATA ));
				ErrInst = new ErrInstall( WC_NOIDENT );

				pbdi -> dwSize = sizeof( PBDDATA );
				pbdi -> pbdTyp = 'i';
				pbdi -> pbdCode = ulClassIdentTRiAS;
				pbdi -> pbdKText = strClassName.GetBuffer( KURZTEXT_LEN );
				pbdi -> pbdLText = strClassDescription.GetBuffer( MAX_LANGTEXT_LEN );
				pbdi -> pbdTemp  = 0;
				pbdi -> pbdKTextLen = strClassName.GetLength();
				pbdi -> pbdLTextLen = strClassDescription.GetLength();
				
				DEX_ModPBDDataEx( DEX_GetDataSourceHandle(), *pbdi );
				DEXN_PBDIdentChanged( ulClassIdentTRiAS );
				if ( ErrInst )
					delete ErrInst;
				strClassName.ReleaseBuffer();
				strClassDescription.ReleaseBuffer();
				delete pbdi;
			}
//			LoadObjectAttributesTRiAS( ulClassIdentTRiAS );
		}
	}
	return (NULL != GeoObject.ObjectClassTRiAS());
}
/*
unsigned long CMetaData :: BildeIdent( const char *objart )
{
	unsigned long		result = 0L;
	CString		strK, strKey, strKode;
	CRegel		*pR = NULL;
	POSITION	pos;

	strK = objart;
//	strK += ':';
	if ( !strK.IsEmpty())
		for ( pos = m_Regeln.GetStartPosition(); pos != NULL; )
		{	m_Regeln.GetNextAssoc( pos, strKey, (void*&)pR );
			if ( strK == strKey.Left( strK.GetLength()))
				pR -> GetIdent( m_tabMMK, strKode );
		}

	if ( !strKode.IsEmpty())
	{	HRESULT	res;
//		res = IdentFromClassX( strKode, &result, true );
		res = IdFromClassX( strKode, &result, true );
	}

	return result;
}	// BildeIdent
*/
///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trif.h
//
//	Stand:			02.12.1994
//	Beschreibung:	TRIAS-Interface-Objekt
//					- Header-Update
//					- IdentsDB-Update
//					- GeoObjekt-Zugriff
//	Entwicklung:	02.12.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////



//extern int AllTrimm( CString& );


/**************************************************************************/
/*	CRegel  ***************************************************************/
/**************************************************************************/
CRegel :: CRegel( const char *eintrag, const CString& strIniFileName )
{	CxString	strK, strKey, strText, strTemp, strEintrag;
	CxString	strW, strI;
	int			i;

	strEintrag = eintrag;
	strEintrag.Teilen( strKey, strText, ',' );
	i = 1;
// B-Regeln Laden
	strTemp.printf( "B%d", i++ );
	while ( strText.GetPrivateProfileString( strKey, strTemp, "",
					255, strIniFileName ))
	{	strText.Teilen( strK, strText, ',' );
		strText.Teilen( strW, strI, ',' );
		if ( !strK.IsEmpty() && !strI.IsEmpty())
		{	strText  = strK;
			strText += "#";
			if ( !strW.IsEmpty()) strText += strW;
			m_mapWerte.SetAt( strText, strI );
			if ( !m_listMerkmale.Find( strK ))
				m_listMerkmale.AddHead( strK );
		}
		strTemp.printf( "B%d", i++ );
	}
}

void CRegel :: And( CString &id, const char *m )
{	char	*z, *q;
	CString	Q = m;
	BOOL	fertig = TRUE;

	for ( q = Q.GetBuffer( Q.GetLength()); *q; q++ )
		if ( !IsHexDigit( *q )) fertig = FALSE;
	Q.ReleaseBuffer();
	if ( fertig )
	{	id = m;		// Sonderfall 1: Neuer ID ist eindeutig und
		return;		//   dominiert bisherige Angaben!
	}

	fertig = TRUE;
	for ( z = id.GetBuffer( id.GetLength()); *z; z++ )
		if ( IsHexDigit( *z )) fertig = FALSE;
	id.ReleaseBuffer();
	if ( fertig )
	{				// Sonderfall 2: Alter ID ist eindeutig und
		return;		//   dominiert neue Angaben!
	}

	z = id.GetBuffer( id.GetLength());
	q = Q.GetBuffer( Q.GetLength());
	while ( *z && *q )
	{	if ( *z != *q )		// Nur wenn die Zeichen sich unterscheiden
			if ( IsHexDigit( *q )) *z = *q;
		z++;
		q++;
	}
	id.ReleaseBuffer();
	Q.ReleaseBuffer();
}

void CRegel :: LiesRegel( const char *name, char &c, const char *id )
{	CxString	strBuffer, strId1, strId2, strIdent;
	CxString	strE, strR, strK, strT;
	char		*temp;
	BOOL		neu;
	int			i = lstrlen( id );

	temp = strBuffer.GetBuffer( 256 );
	::GetPrivateProfileString( "Bedingungen", name, "", temp, 255, g_pMetaData->strIniFileName );
	strBuffer.ReleaseBuffer();

	strId1 = id;
	strId1.Teilen( strId1, strId2, c );
	while (( !strId2.IsEmpty()) && ( strId2.GetAt( 0 ) == c )) strId2 = strId2.Mid( 1 );

	strR = strBuffer;
	neu = TRUE;
	while ( !strR.IsEmpty())
	{	strR.Teilen( strE, strR );
		strE.Teilen( strK, strT, ':' );
		if ( strId1.GetLength() + strId2.GetLength() + strT.GetLength() == i )
		{	strIdent  = strId1;
			strIdent += strT;
			strIdent += strId2;
		}
		else
		{	strIdent = strT;
			c--;				// Bedingungen die nichts ersetzen zählen nicht!
		}

		m_mapWerte.SetAt( strK, strIdent );
		strK.Teilen( strK, strT, '#' );

		if ( !strK.IsEmpty() && neu )
		{	m_listMerkmale.AddHead( strK );
			neu = FALSE;
	}	}
}

BOOL CRegel :: GetIdent( CMapStringToString *mapMerkmale, CString &ident )
{	BOOL		result = FALSE;
	POSITION	pos;
	CString		strKey, strText, strTemp, strDefa;

	ident.Empty();
	for ( pos = m_listMerkmale.GetHeadPosition(); pos != NULL; )
	{	strKey = m_listMerkmale.GetNext( pos );
		strText.Empty();
		mapMerkmale -> Lookup( strKey, strText );
		strKey += '#';
		strDefa.Empty();
		m_mapWerte.Lookup( strKey, strDefa );
		strKey += strText;
		strTemp.Empty();
		m_mapWerte.Lookup( strKey, strTemp );
		if ( strTemp.IsEmpty()) strTemp = strDefa;

		if ( ident.IsEmpty())	ident = strTemp;
		else					And( ident, strTemp );

		if ( !ident.IsEmpty()) result = TRUE;
	}

	return result;
}

void CMetaData::LoadRules_Line()
{
	//=== laden der Regeln für die Erzeugung von Zusatzgeometrien 
	CRule_Line *pRule_Line;

	if( pConfiguration->m_dbCfg.IsOpen()  && !pConfiguration->m_tOverwriteRules ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strFolie;
		CxString strObjektart;
		CxString strFunktionDerLinie;
		CDBVariant vHauptgeometrie;
		CDBVariant vBestimmtObjektart;
		CDBVariant vZusatzgeometrie;
		CxString strHauptgeometrieOKS_TRiAS;
		CxString strZusatzgeometrieOKS_TRiAS;
		CxString strDatentyp_TRiAS;

		if( m_lVerDatabase >= 3 ) {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Funktion der Linie], [Importmodus_Hauptgeometrie], [Funktion der Linie bestimmt Objektklasse_Hauptgeometrie], [Objektklasse_TRiAS_Hauptgeometrie], [Importmodus_Zusatzgeometrie], [Objektklasse_TRiAS_Zusatzgeometrie] FROM [EDBS-Objekte, Linien]",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Funktion der Linie", strFunktionDerLinie );
					rsCfg.GetFieldValue( "Importmodus_Hauptgeometrie", vHauptgeometrie );
					rsCfg.GetFieldValue( "Funktion der Linie bestimmt Objektklasse_Hauptgeometrie", vBestimmtObjektart );
					rsCfg.GetFieldValue( "Objektklasse_TRiAS_Hauptgeometrie", strHauptgeometrieOKS_TRiAS );
					rsCfg.GetFieldValue( "Importmodus_Zusatzgeometrie", vZusatzgeometrie );
					rsCfg.GetFieldValue( "Objektklasse_TRiAS_Zusatzgeometrie", strZusatzgeometrieOKS_TRiAS );
					
					pRule_Line = new CRule_Line( strFolie + strFunktionDerLinie );
					pRule_Line->Importmodus_Hauptgeometrie() = vHauptgeometrie.m_lVal;
					pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() = ( 0 != (vBestimmtObjektart.m_boolVal & 0x1));
					pRule_Line->Importmodus_Zusatzgeometrie() = vZusatzgeometrie.m_lVal;
					pRule_Line->Objektklasse_Zusatzgeometrie() = strHauptgeometrieOKS_TRiAS;
					pRule_Line->Objektklasse_Zusatzgeometrie() = strZusatzgeometrieOKS_TRiAS;
/*					
					if( !pConfiguration->m_tImportKSIG && "Kartograf. Signatur" == strDatentyp_TRiAS )
						pRule_Line->Importmodus_Hauptgeometrie() = 0;
					if( !pConfiguration->m_tImportVPKT && "Punktdatei" == strDatentyp_TRiAS )
						pRule_Line->Importmodus_Hauptgeometrie() = 0;
*/
					m_Rules_Line.SetAt( pRule_Line->Key(), pRule_Line );

					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
		else {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Funktion der Linie], [Hauptgeometrie erzeugen], [Funktion der Linie bestimmt Objektart], [Hauptgeometrie OKS_TRiAS], [Dat-Typ TRiAS], [Zusatzgeometrie erzeugen], [Zusatzgeometrie OKS_TRiAS] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE [Hauptgeometrie erzeugen] = FALSE OR [Zusatzgeometrie erzeugen] = TRUE OR [Funktion der Linie bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Funktion der Linie", strFunktionDerLinie );
					rsCfg.GetFieldValue( "Hauptgeometrie erzeugen", vHauptgeometrie );
					rsCfg.GetFieldValue( "Funktion der Linie bestimmt Objektart", vBestimmtObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strHauptgeometrieOKS_TRiAS );
					rsCfg.GetFieldValue( "Dat-Typ TRiAS", strDatentyp_TRiAS );
					rsCfg.GetFieldValue( "Zusatzgeometrie erzeugen", vZusatzgeometrie );
					rsCfg.GetFieldValue( "Zusatzgeometrie OKS_TRiAS", strZusatzgeometrieOKS_TRiAS );
					
					pRule_Line = new CRule_Line( strFolie + strFunktionDerLinie );
					pRule_Line->Importmodus_Hauptgeometrie() = ( 0 != (vHauptgeometrie.m_boolVal & 0x1));
					pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() = ( 0 != (vBestimmtObjektart.m_boolVal & 0x1));
					pRule_Line->Importmodus_Zusatzgeometrie() = ( 0 != (vZusatzgeometrie.m_boolVal & 0x1));
					pRule_Line->Objektklasse_Hauptgeometrie() = strHauptgeometrieOKS_TRiAS;
					pRule_Line->Objektklasse_Zusatzgeometrie() = strZusatzgeometrieOKS_TRiAS;
					
					if( !pConfiguration->m_tImportKSIG && "Kartograf. Signatur" == strDatentyp_TRiAS )
						pRule_Line->Importmodus_Hauptgeometrie() = 0;
					if( !pConfiguration->m_tImportVPKT && "Punktdatei" == strDatentyp_TRiAS )
						pRule_Line->Importmodus_Hauptgeometrie() = 0;

					m_Rules_Line.SetAt( pRule_Line->Key(), pRule_Line );

					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
	}
	else if( pConfiguration->m_tDefaultObjectMapping ) {
		pRule_Line = new CRule_Line( "0000242" );
		pRule_Line->Importmodus_Hauptgeometrie() = 0;
		pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() = false;
		pRule_Line->Importmodus_Zusatzgeometrie() = 0;
		m_Rules_Line.SetAt( pRule_Line->Key(), pRule_Line );

		pRule_Line = new CRule_Line( "0000249" );
		pRule_Line->Importmodus_Hauptgeometrie() = 0;
		pRule_Line->FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie() = false;
		pRule_Line->Importmodus_Zusatzgeometrie() = 0;
		m_Rules_Line.SetAt( pRule_Line->Key(), pRule_Line );

	}
}

void CMetaData::LoadRules_Layer()
{
	CRule_Layer *pRule_Layer;
	CxString strTemp, strBuffer;
	CxString strID, strDef;

	if( pConfiguration->m_dbCfg.IsOpen() ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strFolie;
		CxString strKurztext;
		CxString strLangtext;
		CDBVariant vImportMode;
		CDBVariant vResolve;
		CxString strOKS_TRiAS;

		if( m_lVerDatabase >= 3 ) {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Kurztext], [Langtext], [Importmodus], [aufloesen], [Objektklasse_TRiAS] FROM [EDBS-Folien]",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Kurztext", strKurztext );
					rsCfg.GetFieldValue( "Langtext", strLangtext );
					rsCfg.GetFieldValue( "Importmodus", vImportMode );
					rsCfg.GetFieldValue( "aufloesen", vResolve );
					rsCfg.GetFieldValue( "Objektklasse_TRiAS", strOKS_TRiAS );
					
					pRule_Layer = new CRule_Layer( strFolie );
					pRule_Layer->Kurztext() = strKurztext;
					pRule_Layer->Langtext() = strLangtext;
					pRule_Layer->ImportMode() = vImportMode.m_lVal;
					pRule_Layer->Resolve( 0 != (vResolve.m_boolVal & 0x1));

					m_Rules_Layer.SetAt( pRule_Layer->Folie(), pRule_Layer );
			
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
		else {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Kurztext], [Langtext], [importieren], [aufloesen], [OKS_TRiAS] FROM [(1) Folienbezeichnung (ALK)]",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Kurztext", strKurztext );
					rsCfg.GetFieldValue( "Langtext", strLangtext );
					rsCfg.GetFieldValue( "importieren", vImportMode );
					rsCfg.GetFieldValue( "aufloesen", vResolve );
					rsCfg.GetFieldValue( "OKS_TRiAS", strOKS_TRiAS );
					
					pRule_Layer = new CRule_Layer( strFolie );
					pRule_Layer->Kurztext() = strKurztext;
					pRule_Layer->Langtext() = strLangtext;
					if( vImportMode.m_boolVal & 0x1 )
						pRule_Layer->ImportMode() = 255;
					else
						pRule_Layer->ImportMode() = 0;
					pRule_Layer->Resolve( 0 != (vResolve.m_boolVal & 0x1));

					m_Rules_Layer.SetAt( pRule_Layer->Folie(), pRule_Layer );
			
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
	}
}

void CMetaData::LoadObjectClassesTRiAS()
{
	CxString strTemp, strBuffer;
	CxString strID, strDef;

	if( pConfiguration->m_dbCfg.IsOpen() ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strObjectClassTRiAS;
		CxString strKurztext;
		CxString strLangtext;
		CDBVariant vImportMode;
		CObjectClassTRiAS	*pObjectClassTRiAS;

		if( m_lVerDatabase >= 3 ) {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Objektklasse_TRiAS], [Kurztext], [Langtext], [Importmodus] FROM [TRiAS-Objekte]",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Objektklasse_TRiAS", strObjectClassTRiAS );
					if( !m_ObjectClassesTRiAS.Lookup( strObjectClassTRiAS, (CObject*&)pObjectClassTRiAS ) ) {
						rsCfg.GetFieldValue( "Kurztext", strKurztext );
						rsCfg.GetFieldValue( "Langtext", strLangtext );
						rsCfg.GetFieldValue( "Importmodus", vImportMode );
						pObjectClassTRiAS = new CObjectClassTRiAS( strObjectClassTRiAS, 	m_bHexIdents );
						pObjectClassTRiAS->ClassX() = strObjectClassTRiAS;
						pObjectClassTRiAS->ClassName() = strKurztext;
						pObjectClassTRiAS->ClassDescription() = strLangtext;
						pObjectClassTRiAS->ImportMode() = vImportMode.m_lVal;
						m_ObjectClassesTRiAS.SetAt( strObjectClassTRiAS, pObjectClassTRiAS );
					}
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
		else {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [OKS_TRiAS], [Kurztext], [Langtext], [importieren] FROM [(III) Beschreibungsdaten für TRiAS]",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "OKS_TRiAS", strObjectClassTRiAS );
					if( !m_ObjectClassesTRiAS.Lookup( strObjectClassTRiAS, (CObject*&)pObjectClassTRiAS ) ) {
						rsCfg.GetFieldValue( "Kurztext", strKurztext );
						rsCfg.GetFieldValue( "Langtext", strLangtext );
						rsCfg.GetFieldValue( "importieren", vImportMode );
						pObjectClassTRiAS = new CObjectClassTRiAS( strObjectClassTRiAS, 	m_bHexIdents );
						pObjectClassTRiAS->ClassX() = strObjectClassTRiAS;
						pObjectClassTRiAS->ClassName() = strKurztext;
						pObjectClassTRiAS->ClassDescription() = strLangtext;
						if( 0 != (vImportMode.m_boolVal & 0x01) )
							pObjectClassTRiAS->ImportMode() = 255;
						else
							pObjectClassTRiAS->ImportMode() = 0;
						m_ObjectClassesTRiAS.SetAt( strObjectClassTRiAS, pObjectClassTRiAS );
					}
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
	}
}

void CMetaData::LoadObjectClassesEDBS()
{
/*
	if( pConfiguration->m_dbCfg.IsOpen() ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strFolie;
		CxString strFunktionDerLinie;

		m_strNichtDarzustellendeObjektarten.Empty();
		try {
			rsCfg.Open(CRecordset::forwardOnly,
				"SELECT [Folie], [Funktion der Linie] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE NOT [Funktion der Linie] IS NULL AND [Hauptgeometrie erzeugen] = FALSE",
				CRecordset::readOnly );
			while( !rsCfg.IsEOF() ) {
				rsCfg.GetFieldValue( "Folie", strFolie );
				rsCfg.GetFieldValue( "Funktion der Linie", strFunktionDerLinie );
		
				m_strNichtDarzustellendeObjektarten += strFolie + strFunktionDerLinie + ";";

				rsCfg.MoveNext();
			}
			rsCfg.Close();
		}
		catch( CDBException* e ) {
			e->ReportError(MB_ICONEXCLAMATION);
		}
	}
	else if( pConfiguration->m_tDefaultObjectMapping ) {
		m_strNichtDarzustellendeObjektarten = "0000242;";
	}
*/
/*
/	CxString strTemp, strBuffer;
	int	i;

//	E1=000;0242			Ex=Folie;Objektart
	i = 1;
	m_strNichtZuImportierendeObjektarten.Empty();
	strTemp.printf( "E%d", i++ );
	while ( strBuffer.GetPrivateProfileString( "Nicht importieren", strTemp, "",
					255, strIniFileName ))
	{
		strBuffer.TrimAll();
		m_strNichtZuImportierendeObjektarten += ";";
		m_strNichtZuImportierendeObjektarten += strBuffer.Left(3) + strBuffer.Right(4);
		
		strTemp.printf( "E%d", i++ );
	}


//	F1=011			Fx=Folie
	i = 1;
	m_strFunktionDerLinieBestimmtFunktionDesObjekts.Empty();
	strTemp.printf( "F%d", i++ );
	while ( strBuffer.GetPrivateProfileString( "Funktion der Linie bestimmt Objektart", strTemp, "",
					255, strIniFileName ))
	{
		strBuffer.TrimAll();
		m_strFunktionDerLinieBestimmtFunktionDesObjekts += ";";
		m_strFunktionDerLinieBestimmtFunktionDesObjekts += strBuffer;
		
		strTemp.printf( "F%d", i++ );
	}

	if( strIniFileName == "UngueltigeKonfigurationsdatei.ini" ) {
		m_strNichtDarzustellendeObjektarten = ";0000242";
	}
*/
}

void CMetaData::LoadObjectAttributesTRiAS( unsigned long ulObjectClassTRiAS )
{
	CxString strBuffer, strID, strDef;
	int	i;
	int nSize;

	char section[32767];

	nSize = ::GetPrivateProfileSection( "Merkmale", section, 32767, strIniFileName );
	if( nSize == 32765 )
		MessageBox(NULL, "Abschnitt [Merkmale] in INI-Datei grösser 32767","EDBS-Import",0);
	else {
		i = 0;
		while( i < nSize ) {
//			M1=49000001,EDBS-Dateiname
			strBuffer = &section[i];
			i += strBuffer.GetLength() + 1;
			strBuffer.Teilen(strID,strDef,"=",true);
			m_ObjectAttributesTRiAS.AddMMK( ulObjectClassTRiAS, strDef, m_bHexMKodes );
		}
	}
	if( pConfiguration->m_tDefaultObjectMapping ) {
		nSize = ::GetPrivateProfileSection( "EDBS-Attribute", section, 32767, m_strObjectClassesEDBS );
		if( nSize == 32765 )
			MessageBox(NULL, "Abschnitt [EDBS-Attribute] in INI-Datei grösser 32767","EDBS-Import",0);
		else {
			i = 0;
			while( i < nSize ) {
//				A1=15;/*Punktkennzeichen*/Objektname für Punkte der Punktdatei
				strBuffer = &section[i];
				i += strBuffer.GetLength() + 1;
				strBuffer.Teilen(strID,strDef,"=",true);
				strDef = m_strObjectAttributesTRiAS
						+ strDef.Left(2) + "0000"  
						+ strDef.Mid(2);
				m_ObjectAttributesTRiAS.AddMMK( ulObjectClassTRiAS, strDef, m_bHexMKodes );
			}
		}
	}
/*
	CxString strTemp, strBuffer;
	i = 1;
	strTemp.printf( "M%d", i++ );
	while ( strBuffer.GetPrivateProfileString( "MERKMALE", strTemp, "",
					255, strIniFileName ))
	{
		m_ObjectAttributesTRiAS.AddMMK( ulObjectClassTRiAS, strBuffer, m_bHexMKodes );
		strTemp.printf( "M%d", i++ );
	}
*/
	
}

long CMetaData::GetTriasAttributeIdent( const char* kurz )
{
//	return m_ObjectAttributesTRiAS.FindeKode( kurz );

	long lAttributeIdentTRiAS;
	lAttributeIdentTRiAS = m_ObjectAttributesTRiAS.FindeKode( kurz );
	if( 0 == lAttributeIdentTRiAS && pConfiguration->m_tDefaultObjectMapping ) {
		lAttributeIdentTRiAS = atol(kurz);
	}
	return lAttributeIdentTRiAS;
}

void CMetaData::LoadClassification( void )
{
	if( pConfiguration->m_dbCfg.IsOpen() ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strFolie;
		CxString strObjektart;
		CxString strObjectClassTRiAS;

		if( m_lVerDatabase >= 3 ) {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [Hauptgeometrie OKS_TRiAS] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE [Hauptgeometrie erzeugen] = TRUE AND [Funktion der Linie bestimmt Objektart] = FALSE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();

				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Funktion der Linie], [Hauptgeometrie OKS_TRiAS] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE [Hauptgeometrie erzeugen] = TRUE AND [Funktion der Linie bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Funktion der Linie", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();

				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [Hauptgeometrie OKS_TRiAS] FROM [(II) Besondere Informationen] WHERE [ObjektartBI bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
		else {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [Hauptgeometrie OKS_TRiAS] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE [Hauptgeometrie erzeugen] = TRUE AND [Funktion der Linie bestimmt Objektart] = FALSE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();

				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Funktion der Linie], [Hauptgeometrie OKS_TRiAS] FROM [(I) Hauptgeometrien mit Funktion der Linien] WHERE [Hauptgeometrie erzeugen] = TRUE AND [Funktion der Linie bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Funktion der Linie", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();

				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [Hauptgeometrie OKS_TRiAS] FROM [(II) Besondere Informationen] WHERE [ObjektartBI bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjectClassTRiAS );
			
					m_Classification.Add( strFolie + strObjektart, strObjectClassTRiAS, m_bHexIdents );
	//				LoadRules( strKeyEDBS, strRules );

					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
	}
/*
	CxString		strTemp, strBuffer;
	CxString strID, strDef;
	CxString		strKeyEDBS, strRules, strKeyTRiAS, str1, str2, str3;
	int				i;
	int				nSize;
	char			section[32767];

/ *
	i = 1;
	strTemp.printf( "T%d", i++ );
	while ( strBuffer.GetPrivateProfileString( "TYPEN", strTemp, "",
					255, strIniFileName ))
	{
		strBuffer.Teilen( strKeyEDBS, str2, ',', true );
		// sind allgemeine Regeln angegeben?
		// mehrere allgemeine Regeln sind durch Semikolon getrennt
		strKeyEDBS.Teilen( strKeyEDBS, strRules, '(', true );
		if( strRules.IsEmpty() ) {
			strRules = strKeyEDBS;
		}
		else {
			strRules.Teilen( strRules, str1, ')', true ); 
		}
		str2.Teilen( strKeyTRiAS, str3, ',', true );

		m_Classification.Add( strKeyEDBS, strKeyTRiAS, m_bHexIdents );
		LoadRules( strKeyEDBS, strRules );
		strTemp.printf( "T%d", i++ );
	}
* /
	nSize = ::GetPrivateProfileSection( "TYPEN", section, 32767, strIniFileName );
	if( nSize == 32765 )
		MessageBox(NULL, "Abschnitt [Typen] in INI-Datei grösser 32767","EDBS-Import",0);
	else {
		i = 0;
		while( i < nSize ) {
			strBuffer = &section[i];
			i += strBuffer.GetLength() + 1;
			strBuffer.Teilen(strID,strDef,"=",true);
			strDef.Teilen( strKeyEDBS, str2, ',', true );
			// sind allgemeine Regeln angegeben?
			// mehrere allgemeine Regeln sind durch Semikolon getrennt
			strKeyEDBS.Teilen( strKeyEDBS, strRules, '(', true );
			if( strRules.IsEmpty() ) {
				strRules = strKeyEDBS;
			}
			else {
				strRules.Teilen( strRules, str1, ')', true ); 
			}
			str2.Teilen( strKeyTRiAS, str3, ',', true );

			m_Classification.Add( strKeyEDBS, strKeyTRiAS, m_bHexIdents );
			LoadRules( strKeyEDBS, strRules );
		}
	}


/ *
	i = 1;
	strTemp.printf( "T%d", i++ );
	while ( strBuffer.GetPrivateProfileString( "Ignorieren", strTemp, "",
					255, strIniFileName ))
	{
		m_Classification.Ignore( strBuffer, TRUE );
		strTemp.printf( "T%d", i++ );
	}
* /
	nSize = ::GetPrivateProfileSection( "Ignorieren", section, 32767, strIniFileName );
	if( nSize == 32765 )
		MessageBox(NULL, "Abschnitt [Typen] in INI-Datei grösser 32767","EDBS-Import",0);
	else {
		i = 0;
		while( i < nSize ) {
			strBuffer = &section[i];
			i += strBuffer.GetLength() + 1;
			strBuffer.Teilen(strID,strDef,"=",true);
			m_Classification.Ignore( strDef, TRUE );
		}
	}
*/
}
//	-------------------------------------------------------------------
//	CObjectClassTRiAS
//	-------------------------------------------------------------------
CObjectClassTRiAS :: CObjectClassTRiAS( const char* def, bool hexbase )
{	CxString	strDef, strKurz, strLang;
	CxString	schl, rest;
//	int			i;

	m_lIdent = 0L;
	m_ulClassId = ++ulObjectClassesTRiASIdent;
	m_bUsed = false;
	m_lImportMode = 1;
	if ( def ) {
		schl = def;
		schl.Teilen( schl, rest, ';' );
		schl.TrimAll();

		m_strClassX = schl;

		strDef = rest;
//		HRESULT	res;
//		res = IdentFromClassX( schl, &m_lKode, true );	// ggf. neu anlegen

//		res = IdFromClassX( schl, &m_lIdent, true );	// ggf. neu anlegen

		
//		i = strDef.Find( ',' );
//		if ( i >= 0 ) strDef = strDef.Mid( i + 1 );
/*
		i = strDef.Find( '\t' );
		if ( i >= 0 )
		{	m_strKurz = strDef.Left( i );
			m_strLang = strDef.Mid( i + 1 );
		}
		else
			m_strKurz = strDef;
*/
		if ( "/*" == strDef.Left( 2 ))
			strDef = strDef.Mid( 2 );
		strDef.Teilen( strKurz, strLang, '\t' );
		if ( strLang.IsEmpty())
			strDef.Teilen( strKurz, strLang, "/*" );
		if ( strLang.IsEmpty()) {
			strDef.Teilen( strKurz, strLang, "*/" );
			if ( !strLang.IsEmpty())
				if ( "*/" == strLang.Right( 2 ))
					if ( strLang.GetLength() > 2 )
			{
				strLang = strLang.Left( strLang.GetLength() - 2 );
			}
			else
				strLang = "";
		}
		if ( strLang.IsEmpty())
			strLang = strKurz;
		m_strClassName = strKurz;
		m_strClassDescription = strLang;
	}
}

CObjectClassTRiAS::~CObjectClassTRiAS()
{
	POSITION	pos;
	CString		key;
	CObjectAttributeTRiAS	*pObjectAttributeTRiAS;

	for ( pos = m_Attributes.GetStartPosition(); pos != NULL; ) {
		m_Attributes.GetNextAssoc( pos, key, (CObject*&)pObjectAttributeTRiAS );
		delete pObjectAttributeTRiAS;
	}
	m_Attributes.RemoveAll();
}


/*
CObjectClassTRiAS *CTriasIdList :: GetId( const char* def )
{	unsigned long	id = atol( def );
	CObjectClassTRiAS		*result = NULL;

	ASSERT( FALSE );	// Fehlerquelle!!!

#ifdef _WIN32
	HRESULT res;
	res = IdentFromClassX( def, &id, true );
#else
	id = atol( def );
#endif

	for ( int i = 0; i < GetSize(); i++ )
		if (((CObjectClassTRiAS*)GetAt( i )) -> Kode() == id )
		{	result = (CObjectClassTRiAS*)GetAt( i );
			i = GetSize();
		}

	return result;
}
*/
//	-------------------------------------------------------------------
//	CLayerEDBS
//	-------------------------------------------------------------------
/*
CEDBSFolie::CEDBSFolie( const char* strDefinition )
{
	m_strFolie = strDefinition;
	m_tImport = true;
	m_tResolve = true;
}
*/
//	-------------------------------------------------------------------
//	CObjectClassEDBS
//	-------------------------------------------------------------------
CObjectClassEDBS::CObjectClassEDBS( const char* def )
{
	m_lClassId = 0L;
	m_bIgnored = false;
	if ( def ) {
		m_lClassId = atol(def);;
	}
}
//	-------------------------------------------------------------------
//	CObjectClassesEDBS
//	-------------------------------------------------------------------
CObjectClassesEDBS::~CObjectClassesEDBS()
{
	for( int i = 0; i < GetSize(); i++ )
		delete (CObjectClassEDBS*)GetAt( i );
	RemoveAll();
}

void CObjectClassesEDBS::Add( const char* def )
{
	unsigned long	id;
	bool			found = FALSE;
	CxString		strDef, strObjectClassEDBS, strRest;

	strDef = def;
	strDef.TrimAll();
	strDef.Teilen( strObjectClassEDBS, strRest, ";" );
	if( strObjectClassEDBS.IsEmpty() )
		strObjectClassEDBS = strDef;
	id = atol( def );

	for( int i = 0; i < GetSize(); i++ ) {
		if( ((CObjectClassEDBS*)GetAt( i ))->ClassId() == id )
			return;
	}
	CObArray::Add( new CObjectClassEDBS( def ) );
}

void CObjectClassesEDBS::Ignore( const char* strObjectClassEDBS, bool bIgnore )
{
	unsigned long	id;

	id = atol( strObjectClassEDBS );

	CObjectClassEDBS* tmp;
	for( int i = 0; i < GetSize(); i++ ) {
		tmp = (CObjectClassEDBS*)GetAt( i );
		if( tmp->ClassId() == id ) {
			tmp->Ignore( bIgnore );
			return;
		}
	}
}

bool CObjectClassesEDBS::Ignored( unsigned long ulObjectClassId )
{
	CObjectClassEDBS* tmp;
	for( int i = 0; i < GetSize(); i++ ) {
		tmp = (CObjectClassEDBS*)GetAt( i );
		if( tmp->ClassId() == ulObjectClassId )
			return tmp->Ignored();
	}
	return false;
}

bool CObjectClassesEDBS::Ignored( const char* strObjectClassEDBS )
{
	unsigned long	id;

	id = atol( strObjectClassEDBS );

	return Ignored( id );
}

CObjectClassEDBS* CObjectClassesEDBS::Get( unsigned long ulObjectClassId )
{
	CObjectClassEDBS* tmp;
	for ( int i = 0; i < GetSize(); i++ ) {
		tmp = (CObjectClassEDBS*)GetAt( i );
		if( tmp->ClassId() == ulObjectClassId )
			return tmp;
	}
	return NULL;
}

CObjectClassEDBS* CObjectClassesEDBS::Get( const char* strObjectClassEDBS )
{
	unsigned long	id;

	id = atol( strObjectClassEDBS );

	return Get( id );
}
//	-------------------------------------------------------------------
//	CClassificator
//	-------------------------------------------------------------------

CClassificator::CClassificator( const char* strKeyEDBS, 
							    const char* strKeyTRiAS, bool bHexbase)
{
	CxString	strNr;
	int			i;
	char		c;
	bool		eindeutig;

	m_lClassIdTRiAS = 0L;
	m_lClassIdEDBS  = 0L;
	eindeutig = TRUE;
	m_strObjectClassTRiAS = strKeyTRiAS;
	if( strKeyEDBS ) {
		m_lClassIdEDBS = atol( strKeyEDBS );
		if( strKeyTRiAS ) {
			strNr = strKeyTRiAS;
			for ( i = 0; i < strNr.GetLength(); i++ ) {
				c = strNr.GetAt( i );
				if ( !IsHexDigit( c )) {
					eindeutig = FALSE;
					i = strNr.GetLength() + 1;
				}	
			}

			if ( eindeutig ) {
				CObjectClassTRiAS* pObjectClassTRiAS;
				if( g_pMetaData->ObjectClassesTRiAS().Lookup( strKeyTRiAS, (CObject*&)pObjectClassTRiAS ) )
					m_lClassIdTRiAS = pObjectClassTRiAS->ClassId();
			}
		}
	}
}

//	-------------------------------------------------------------------
//	CClassification
//	-------------------------------------------------------------------
CClassification::~CClassification()
{
	POSITION		pos;
	CString			key;
	CClassificator	*pClassificator;


	for ( pos = GetStartPosition(); pos != NULL; ) {
		GetNextAssoc( pos, key, (CObject*&)pClassificator );
		delete pClassificator;
	}
	RemoveAll();
}

void CClassification::Add( const char* strKeyEDBS, const char* strKeyTRiAS, bool bHexbase )
{
	CClassificator *pClassificator;
	if( !Lookup( strKeyEDBS, (CObject*&)pClassificator ) )
		SetAt( strKeyEDBS, new CClassificator( strKeyEDBS, strKeyTRiAS, bHexbase ));
}

void CClassification::Importieren( const char* strKeyEDBS, bool tImportieren )
{	
	CClassificator *pClassificator;
	if( Lookup( strKeyEDBS, (CObject*&)pClassificator ) )
		pClassificator->Importieren( tImportieren );
}

unsigned long CClassification::Classify( const char* strKeyEDBS )
{
	CClassificator *pClassificator;
	if( Lookup( strKeyEDBS, (CObject*&)pClassificator ) )
		return pClassificator->ClassIdTRiAS();
	return 0;
}

bool CClassification::Importieren( const char* strKeyEDBS )
{
	CClassificator *pClassificator;
	if( Lookup( strKeyEDBS, (CObject*&)pClassificator ) )
		return pClassificator->Importieren();
	return false;
}

bool CMetaData::Komplexobjekt( CString strFolieObjektart )
{
	return 0 <= m_strKomplexobjekte.Find( strFolieObjektart );
}


CRule_Layer *CMetaData::MapObjectClassEDBStoObjectClassTRiAS( CGeoObj& GeoObject, CString &strObjectClassTRiAS)
{
	CRule_Layer	*pRule_Layer = NULL;
	CClassificator *pClassificator = NULL;
	CxString strObjectClassEDBS;

	pRule_Layer = GetRule_Layer( GeoObject.Folie() );
	if( pRule_Layer ) {
		if( 0 != pRule_Layer->ImportMode() ) {
			strObjectClassEDBS = pRule_Layer->Folie();
			if( pRule_Layer->Resolve() ) {
				strObjectClassEDBS  += GeoObject.Objektart();
				if( !m_Classification.Lookup( strObjectClassEDBS, (CObject*&)pClassificator ) ) {
					strObjectClassEDBS = pRule_Layer->Folie() + "0000";
					if( !m_Classification.Lookup( strObjectClassEDBS, (CObject*&)pClassificator ) && pRule_Layer->Folie() != "000") {
						strObjectClassEDBS = "000" + GeoObject.Objektart();
						if( !m_Classification.Lookup( strObjectClassEDBS, (CObject*&)pClassificator ) && pRule_Layer->Folie() != "000") {
							m_Classification.Lookup("0000000", (CObject*&)pClassificator );
						}
					}
				}
			}
			else {
				strObjectClassEDBS  += "0000";
				if( !m_Classification.Lookup( strObjectClassEDBS, (CObject*&)pClassificator ) && pRule_Layer->Folie() != "000") {
					m_Classification.Lookup("0000000", (CObject*&)pClassificator );
				}
			}
			if( NULL == pClassificator  && pConfiguration->m_tDefaultObjectMapping ) {
				strObjectClassEDBS = pRule_Layer->Folie();
				if( pRule_Layer->Resolve() )
					strObjectClassEDBS  += GeoObject.Objektart();
				strObjectClassTRiAS = pConfiguration->m_strObjectClassesTRiAS + strObjectClassEDBS;
				pClassificator = new CClassificator( strObjectClassEDBS, strObjectClassTRiAS, true );
				m_Classification.SetAt( strObjectClassEDBS, pClassificator );
			}
		}
		if( pClassificator ) {
//				if( pClassificator->Importieren() ) {
				strObjectClassTRiAS = pClassificator->ObjectClassTRiAS();
				return pRule_Layer;
//				}
		}
	}
	return NULL;
}

void CMetaData::LoadRules_Geom()
{
	//=== laden der Regeln für die Erzeugung von Geometrien aus besonderen Informationen 
	CRule_Geom	*pRule_Geom = NULL;

	if( pConfiguration->m_tCreateBIgeom ) {
		if( pConfiguration->m_dbCfg.IsOpen()  && !pConfiguration->m_tOverwriteRules ) {
			CRecordset rsCfg( &pConfiguration->m_dbCfg );
			CxString strFolie;
			CxString strObjektart;
			CxString strObjektartBI;
			CxString strInformationsart;
			CDBVariant vObjektartBestimmtObjektklasseDetailgeometrie;
			CDBVariant vObjektkategorie;
			CDBVariant vImportMode;
			CxString strObjektklasse;
			CxString strTmp1, strTmp2;
			CxString strDatentyp_TRiAS;

			if( m_lVerDatabase >= 3 ) {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Informationsart], [Importmodus_Detailgeometrie], [Objektart bestimmt Objektklasse_Detailgeometrie], [Objektklasse_Detailgeometrie], [Objektkategorie_Detailgeometrie] FROM [EDBS-Objekte, Besondere Informationen]",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Informationsart", strInformationsart );
						rsCfg.GetFieldValue( "Importmodus_Detailgeometrie", vImportMode );
						rsCfg.GetFieldValue( "Objektart bestimmt Objektklasse_Detailgeometrie", vObjektartBestimmtObjektklasseDetailgeometrie );
						rsCfg.GetFieldValue( "Objektklasse_Detailgeometrie", strObjektklasse );
						rsCfg.GetFieldValue( "Objektkategorie_Detailgeometrie", vObjektkategorie );

						pRule_Geom = new CRule_Geom( strFolie + strObjektart + strObjektartBI + strInformationsart );
						pRule_Geom->ObjektartBestimmtObjektartBI() = ( 0 != (vObjektartBestimmtObjektklasseDetailgeometrie.m_boolVal & 0x1));
						pRule_Geom->ObjectClassTRiAS() = strObjektklasse;
/*
						if( !pConfiguration->m_tImportKSIG && "Kartograf. Signatur" == strDatentyp_TRiAS )
							pRule_Geom->Import( false );
						if( !pConfiguration->m_tImportVPKT && "Punktdatei" == strDatentyp_TRiAS )
							pRule_Geom->Import( false );
*/
						m_Rules_Geom.SetAt( pRule_Geom->Key(), pRule_Geom );

						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
			else {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Art der Information], [Objektart bestimmt ObjektartBI], [Geometrie OKS_TRiAS], [Dat-Typ TRiAS] FROM [(II) Besondere Informationen] WHERE [Geometrie erzeugen] = TRUE",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Art der Information", strInformationsart );
						rsCfg.GetFieldValue( "Objektart bestimmt ObjektartBI", vObjektartBestimmtObjektklasseDetailgeometrie );
						rsCfg.GetFieldValue( "Geometrie OKS_TRiAS", strObjektklasse );
						rsCfg.GetFieldValue( "Dat-Typ TRiAS", strDatentyp_TRiAS );

						strTmp1 = strFolie + strObjektart + strObjektartBI;
						while( strInformationsart.GetLength() > 0 ) {
							strInformationsart.Teilen( strTmp2, strInformationsart, ';' );
							pRule_Geom = new CRule_Geom( strTmp1 + strTmp2 );
							pRule_Geom->ObjektartBestimmtObjektartBI() = ( 0 != (vObjektartBestimmtObjektklasseDetailgeometrie.m_boolVal & 0x1));
							pRule_Geom->ObjectClassTRiAS() = strObjektklasse;
							if( !pConfiguration->m_tImportKSIG && "Kartograf. Signatur" == strDatentyp_TRiAS )
								pRule_Geom->Import( false );
							if( !pConfiguration->m_tImportVPKT && "Punktdatei" == strDatentyp_TRiAS )
								pRule_Geom->Import( false );

							m_Rules_Geom.SetAt( pRule_Geom->Key(), pRule_Geom );
						}
						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
		}
	}
}

void CMetaData::LoadRules_Text()
{	
	//=== laden der Regeln für die Erzeugung von Textobjekten aus besonderen Informationen 
	CRule_Text *pRule_Text;

	if( pConfiguration->m_tCreateBItext ) {
		if( pConfiguration->m_dbCfg.IsOpen()  && !pConfiguration->m_tOverwriteRules ) {
			CRecordset rsCfg( &pConfiguration->m_dbCfg );
			CxString strFolie;
			CxString strObjektart;
			CxString strObjektartBI;
			CxString strInformationsart;
			CxString strKonvertierung;
			CDBVariant vImportMode_Text;
			CDBVariant vObjektkategorie;
			CxString strObjektklasse;
			CxString strTmp1, strTmp2;

			if( m_lVerDatabase >= 3 ) {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Informationsart], [Importmodus_Text], [Text konvertieren], [Objektkategorie_Text], [Objektklasse_Text] FROM [EDBS-Objekte, besondere Informationen]",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Informationsart", strInformationsart );
						rsCfg.GetFieldValue( "Importmodus_Text", vImportMode_Text );
						rsCfg.GetFieldValue( "Text konvertieren", strKonvertierung );
						rsCfg.GetFieldValue( "Objektkategorie_Text", vObjektkategorie );
						rsCfg.GetFieldValue( "Objektklasse_Text", strObjektklasse );
						
						pRule_Text = new CRule_Text( strFolie + strObjektart + strObjektartBI + strInformationsart );
						pRule_Text->Convert() = strKonvertierung;
						pRule_Text->ObjectClassTRiAS() = strObjektklasse;
						pRule_Text->ImportMode() = vImportMode_Text.m_lVal;
						m_Rules_Text.SetAt( pRule_Text->Key(), pRule_Text );

						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
			else {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Art der Information], [Text konvertieren], [Text OKS_TRiAS] FROM [(II) Besondere Informationen] WHERE [Text erzeugen] = TRUE",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Art der Information", strInformationsart );
						rsCfg.GetFieldValue( "Text konvertieren", strKonvertierung );
						rsCfg.GetFieldValue( "Text OKS_TRiAS", strObjektklasse );
						
						strTmp1 = strFolie + strObjektart + strObjektartBI;
						while( strInformationsart.GetLength() > 0 ) {
							strInformationsart.Teilen( strTmp2, strInformationsart, ';' );
							pRule_Text = new CRule_Text( strFolie + strObjektart + strObjektartBI + strTmp2 );
							pRule_Text->Convert() = strKonvertierung;
							pRule_Text->ObjectClassTRiAS() = strObjektklasse;
							m_Rules_Text.SetAt( pRule_Text->Key(), pRule_Text );
						}
						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
		}
	}
}

void CMetaData::LoadRules_Attr()
{
	//=== laden der Regeln für die Erzeugung von Geometrien aus besonderen Informationen 
	CRule_Attr *pRule_Attr;

	if( pConfiguration->m_tCreateBIattr ) {
		if( pConfiguration->m_dbCfg.IsOpen() && !pConfiguration->m_tOverwriteRules ) {
			CRecordset rsCfg( &pConfiguration->m_dbCfg );
			CxString strFolie;
			CxString strObjektart;
			CxString strObjektartBI;
			CxString strInformationsart;
			CDBVariant vImportMode;
			CxString strKonvertierung;
			CxString strAttributName;
			CxString strTmp1, strTmp2;

			if( m_lVerDatabase >= 3 ) {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Informationsart], [Importmodus_Attribut], [Attribut konvertieren], [Attribut] FROM [EDBS-Objekte, besondere Informationen]",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Informationsart", strInformationsart );
						rsCfg.GetFieldValue( "Importmodus_Attribut", vImportMode );
						rsCfg.GetFieldValue( "Attribut konvertieren", strKonvertierung );
						rsCfg.GetFieldValue( "Attribut", strAttributName );
						
						pRule_Attr = new CRule_Attr( strFolie + strObjektart + strObjektartBI + strInformationsart );
						pRule_Attr->ImportMode() = vImportMode.m_lVal;
						pRule_Attr->Convert() = strKonvertierung;
						pRule_Attr->AttributeName() = strAttributName;
						m_Rules_Attr.SetAt( pRule_Attr->Key(), pRule_Attr );

						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
			else {
				try {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Folie], [Objektart], [ObjektartBI], [Art der Information], [Attribut konvertieren], [Attribut Name] FROM [(II) Besondere Informationen] WHERE [Attribut erzeugen] = TRUE",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Folie", strFolie );
						rsCfg.GetFieldValue( "Objektart", strObjektart );
						rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
						rsCfg.GetFieldValue( "Art der Information", strInformationsart );
						rsCfg.GetFieldValue( "Attribut konvertieren", strKonvertierung );
						rsCfg.GetFieldValue( "Attribut Name", strAttributName );
						
						strTmp1 = strFolie + strObjektart + strObjektartBI;
						while( strInformationsart.GetLength() > 0 ) {
							strInformationsart.Teilen( strTmp2, strInformationsart, ';' );
							pRule_Attr = new CRule_Attr( strFolie + strObjektart + strObjektartBI + strTmp2 );
							pRule_Attr->Convert() = strKonvertierung;
							pRule_Attr->AttributeName() = strAttributName;
							m_Rules_Attr.SetAt( pRule_Attr->Key(), pRule_Attr );
						}
						rsCfg.MoveNext();
					}
					rsCfg.Close();
				}
				catch( CDBException* e ) {
					e->ReportError(MB_ICONEXCLAMATION);
				}
			}
		}
	}
}

void CMetaData::LoadRules_Info()
{
	//=== laden der allgemeinen Regeln für die Verarbeitung von besonderen Informationen 
	CRule_Info *pRule_Info;

	if( pConfiguration->m_dbCfg.IsOpen() && !pConfiguration->m_tOverwriteRules ) {
		CRecordset rsCfg( &pConfiguration->m_dbCfg );
		CxString strFolie;
		CxString strObjektart;
		CxString strObjektartBI;
		CxString strInformationsart;

		CDBVariant vObjektartBI_bestimmt_Objektklasse_Hauptgeometrie;
		CxString strObjektklasse_Hauptgeometrie;

		CDBVariant vImportmodus_Detailgeometrie;
		CDBVariant vObjektart_bestimmt_Objektklasse_Detailgeometrie;
		CDBVariant vObjektkategorie_Detailgeometrie;
		CxString strObjektklasse_Detailgeometrie;

		CDBVariant vImportmodus_Text;
		CxString strKonvertierung_Text;
		CDBVariant vObjektkategorie_Text;
		CxString strObjektklasse_Text;

		CDBVariant vImportmodus_Attr;
		CxString strKonvertierung_Attr;;
		CxString strAttributName;
		CxString strTmp1, strTmp2;

		if( m_lVerDatabase >= 3 ) {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [ObjektartBI], [Informationsart], " \
					"[ObjektartBI bestimmt Objektklasse_Hauptgeometrie], [Objektklasse_Hauptgeometrie], " \
					"[Importmodus_Detailgeometrie], [Objektart bestimmt Objektklasse_Detailgeometrie], [Objektklasse_Detailgeometrie], [Objektkategorie_Detailgeometrie], " \
					"[Importmodus_Text], [Text konvertieren], [Objektkategorie_Text], [Objektklasse_Text], " \
					"[Importmodus_Attribut], [Attribut konvertieren], [Attribut] " \
					"FROM [EDBS-Objekte, Besondere Informationen] ",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
					rsCfg.GetFieldValue( "Informationsart", strInformationsart );
					
					rsCfg.GetFieldValue( "ObjektartBI bestimmt Objektklasse_Hauptgeometrie", vObjektartBI_bestimmt_Objektklasse_Hauptgeometrie );
					rsCfg.GetFieldValue( "Objektklasse_Hauptgeometrie", strObjektklasse_Hauptgeometrie );
					
					rsCfg.GetFieldValue( "Importmodus_Detailgeometrie", vImportmodus_Detailgeometrie );
					rsCfg.GetFieldValue( "Objektart bestimmt Objektklasse_Detailgeometrie", vObjektart_bestimmt_Objektklasse_Detailgeometrie );
					rsCfg.GetFieldValue( "Objektklasse_Detailgeometrie", strObjektklasse_Detailgeometrie );
					rsCfg.GetFieldValue( "Objektkategorie_Detailgeometrie", vObjektkategorie_Detailgeometrie );

					rsCfg.GetFieldValue( "Importmodus_Text", vImportmodus_Text );
					rsCfg.GetFieldValue( "Text konvertieren", strKonvertierung_Text );
					rsCfg.GetFieldValue( "Objektkategorie_Text", vObjektkategorie_Text );
					rsCfg.GetFieldValue( "Objektklasse_Text", strObjektklasse_Text );

					rsCfg.GetFieldValue( "Importmodus_Attribut", vImportmodus_Attr );
					rsCfg.GetFieldValue( "Attribut konvertieren", strKonvertierung_Attr );
					rsCfg.GetFieldValue( "Attribut", strAttributName );

					pRule_Info = new CRule_Info( strFolie + strObjektart + strObjektartBI + strInformationsart );


					pRule_Info->ObjektartBI_bestimmt_Objektklasse_Hauptgeometrie() = ( 0 != (vObjektartBI_bestimmt_Objektklasse_Hauptgeometrie.m_boolVal & 0x1));
					pRule_Info->ObjectClassTRiAS_Hauptgeometrie() = strObjektklasse_Hauptgeometrie;

					pRule_Info->Importmodus_Detailgeometrie() = vImportmodus_Detailgeometrie.m_lVal;
					pRule_Info->Objektart_bestimmt_Objektklasse_Detailgeometrie() = ( 0 != (vObjektart_bestimmt_Objektklasse_Detailgeometrie.m_boolVal & 0x1));
					pRule_Info->Objektkategorie_Detailgeometrie() = vObjektkategorie_Detailgeometrie.m_lVal;
					pRule_Info->Objektklasse_Detailgeometrie() = strObjektklasse_Detailgeometrie;
					
					pRule_Info->Importmodus_Text() = vImportmodus_Text.m_lVal;
					pRule_Info->Konvertierung_Text() = strKonvertierung_Text;
					pRule_Info->Objektkategorie_Text() = vObjektkategorie_Text.m_lVal;
					pRule_Info->Objektklasse_Text() = strObjektklasse_Text;

					pRule_Info->Importmodus_Attr() = vImportmodus_Attr.m_lVal;
					pRule_Info->Konvertierung_Attr() = strKonvertierung_Attr;
					pRule_Info->AttributeName() = strAttributName;

					m_Rules_Info.SetAt( pRule_Info->Key(), pRule_Info );
					
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
		else {
			try {
				rsCfg.Open(CRecordset::forwardOnly,
					"SELECT [Folie], [Objektart], [ObjektartBI], [Hauptgeometrie OKS_TRiAS] FROM [(II) Besondere Informationen] WHERE [ObjektartBI bestimmt Objektart] = TRUE",
					CRecordset::readOnly );
				while( !rsCfg.IsEOF() ) {
					rsCfg.GetFieldValue( "Folie", strFolie );
					rsCfg.GetFieldValue( "Objektart", strObjektart );
					rsCfg.GetFieldValue( "ObjektartBI", strObjektartBI );
					rsCfg.GetFieldValue( "Hauptgeometrie OKS_TRiAS", strObjektklasse_Hauptgeometrie );

					pRule_Info = new CRule_Info( strFolie + strObjektart + strObjektartBI );
					pRule_Info->ObjectClassTRiAS_Hauptgeometrie() = strObjektklasse_Hauptgeometrie;
					m_Rules_Info.SetAt( pRule_Info->Key(), pRule_Info );
					
					rsCfg.MoveNext();
				}
				rsCfg.Close();
			}
			catch( CDBException* e ) {
				e->ReportError(MB_ICONEXCLAMATION);
			}
		}
	}
}


CObjectClassTRiAS * CMetaData::GetObjectClassTRiAS(CString &strObjectClassTRiAS)
{
	CObjectClassTRiAS *pObjectClassTRiAS = NULL;
	if( strObjectClassTRiAS.IsEmpty() )
		strObjectClassTRiAS = m_strObjectClassesTRiAS + "0000000";

	m_ObjectClassesTRiAS.Lookup( strObjectClassTRiAS, (CObject*&)pObjectClassTRiAS );
	if( NULL == pObjectClassTRiAS ) {
		CxString strFolie;
		CxString strObjektart;
		CxString strClassName;
		CxString strClassDescription;

		strFolie = strObjectClassTRiAS.Mid(strObjectClassTRiAS.GetLength()-7,3);
		strObjektart = strObjectClassTRiAS.Right(4);

		pObjectClassTRiAS = new CObjectClassTRiAS( strObjectClassTRiAS,	m_bHexIdents );
		if( "0000" != strObjektart ) {
			strClassName = "ALK ";
			strClassName += strFolie;
			strClassName += "-";
			strClassName += strObjektart;
			strClassDescription = "ALK-Objekt der Objektart ";
			strClassDescription += strObjektart;
			strClassDescription += " in Folie ";
			strClassDescription += strFolie;
		}
		else {
			if( "000" != strFolie ) {
				strClassName = "ALK ";
				strClassName += strFolie;
				strClassDescription = "ALK-Objekt in Folie ";
				strClassDescription += strFolie;
			}
			else {
				strClassName = "ALK";
				strClassDescription = "ALK-Objekt";
			}
		}
		pObjectClassTRiAS->ClassX() = strObjectClassTRiAS;
		pObjectClassTRiAS->ClassName() = strClassName;
		pObjectClassTRiAS->ClassDescription() = strClassDescription;
		pObjectClassTRiAS->ImportMode() = 255;
		m_ObjectClassesTRiAS.SetAt( strObjectClassTRiAS, pObjectClassTRiAS );
	}

	return pObjectClassTRiAS;
}

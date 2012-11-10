// Verwalten der Strassen
// File: relkey.cpp

#include "StdAfx.h"

#include "resource.h"		// ResourceKonstanten
#include "version.h"

#include "relkey.h"
#include "errorcode.h"
#include <Ristypes.hxx>

#pragma warning(disable: 4273)


///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4273)
int __cdecl lstrcmp (void *p1, void *p2)
{
	return strcmp((char *)p1, (char *)p2); 
}

///////////////////////////////////////////////////////////////////////////////

extern "C"  BOOL PASCAL _XTENSN_EXPORT  isShortCode( const char *pGCSCode) 
{

	if ( !pGCSCode || !*pGCSCode) 
		return FALSE;

	short ie = _countof ( GCS_USP);
	const short *iG = &GCS_USP[0];

	short i = 0;
	
	while ( i < ie) {
					
		if ( *(pGCSCode + *(iG+i)) != '_') {
			return FALSE;
		}
		i++;
	}

	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////////////
extern "C"  BOOL PASCAL _XTENSN_EXPORT CheckGCSPointCode ( const char * sCode)
{

	if ( !sCode || *sCode == '\0')
		return FALSE;		//Falscer Code - Weitersuchen

	short i = 0;

	short ie = _countof ( GCS_USP);
	const short *iG = &GCS_USP[0];

	while ( i < ie) {
					
		if ( *(sCode + *(iG+i)) != '_') {
			return FALSE;
		}
		i++;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////
extern "C"  BOOL PASCAL _XTENSN_EXPORT CheckGCSOtherCode ( const char * sCode)
{

	if ( !sCode || *sCode == '\0')
		return FALSE;		//Weitersuchen

	short i = 0;

	short ie = _countof ( GCS_US);
	const short *iG = &GCS_US[0];

	while ( i < ie) {
					
		if ( *(sCode + *(iG+i)) != '_') {
			return FALSE;
		}
		i++;
	}

	return TRUE;

}

/////////////////////////////////////////////////////////////////////////////////////

extern "C"  BOOL PASCAL _XTENSN_EXPORT FindGCSCode ( long lMCode, BOOL , void *pData)
{


	HPROJECT hPr = DEX_GetFeatureProject(lMCode);

	if ( 0 == hPr)
		return TRUE;

	long lONr = ((ObjFeat *) pData)->lONr;

	int iTyp =  ((ObjFeat *) pData)->iTyp;



	HPROJECT _hPr = DEX_GetObjectProject(lONr);

	if ( _hPr != hPr)
		return TRUE;

	if ( lMCode != 0 ) {

		TCHAR strGCS [_MAX_PATH];

		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = lONr;
		TM.lMCode = (long) lMCode;
		TM.imaxLen = _MAX_PATH-1;
		TM.iTTyp = TT_Objekt;
		TM.pMText = strGCS;

		if ( DEX_GetTextMerkmal ( TM )) {
			char *cptr = strchr(strGCS,'_');
			BOOL iFlag = FALSE;

			if ( cptr ) {

				if ( iTyp == OT_PUNKT) {

					iFlag = CheckGCSPointCode (strGCS);		//Verkürzter GCO-Code
					if ( !iFlag)		// nicht verkürzt
						iFlag = CheckGCSOtherCode (strGCS);

				} else
					iFlag = CheckGCSOtherCode (strGCS);

				if ( iFlag) {		// GCO-Code
				//GCS-Code  gefunden
					((ObjFeat *) pData)->lMCode = lMCode;
					strcpy((char *)((ObjFeat *) pData)->pCode,strGCS); 
					return FALSE;
				}
			}
		}

		
	}

	((ObjFeat *) pData)->lMCode = -1;

	return TRUE;

}
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_STREETS 
TR_STREETS::TR_STREETS (const char *pKey, const char *pWert,int iErrorCode,long lONr) :
//	m_strKey(pKey), m_strWert(pWert),m_lErrorCode(lErrorCode),m_pDuplObjects(NULL)
	m_strKey(pKey), m_strWert(pWert),m_iErrorCode(iErrorCode),m_pDupObj(NULL)
{
	if (lONr != -1 && lONr != 0)
		m_lONr = lONr;

}
////////////////////////////////////////////////////////////////////////////
TR_STREETS::~TR_STREETS (void) 
{
//	DELETE_OBJ(m_pDuplObjects);
	DELETE_OBJ(m_pDupObj);
}

//----------------------------------------------------------------
bool TR_STREETS::SetWert (const char *pWert) 
{
	if (NULL == pWert)
		return false;

	m_strWert = pWert;
	return true;
}
///////////////////////////////////////////////////////////////////////////////
bool TR_STREETS::AddObject(long lONr,int iErrorCode)
{
	if (lONr == -1 || lONr == 0)
		return false;

	if ( !m_pDupObj)
		m_pDupObj = new TR_ObjTree();

	CTable t (*m_pDupObj);

//	int iErrorCode = 0;

	if (!t.Find (&lONr)) {

		TR_OBJECTSCreator OSCr (*m_pDupObj);

		ContCreate(OSCr, TR_OBJECTS)(lONr,iErrorCode);
	}


	return true;

}
///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_STREETSTree 
TR_STREETSTree::TR_STREETSTree (void) 
	 : CTree (GetStreets, StrCmp)
{
}

/////////////////////////////////////////////////////////////////////////////

TR_STREETSTree::~TR_STREETSTree (void) 
{
	EveryDelete();	// alle Elemente des Baumes freigeben
}

/////////////////////////////////////////////////////////////////////////////

void _XTENSN_EXPORT TR_STREETSTree::UserDelete (void *pObj) 
{
	((TR_STREETS *)pObj) -> TR_STREETS::~TR_STREETS();
}

//////////////////////////////////////////////////////////////////////////////

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetStreets (void *pObj) 
{
	return (void *)(((TR_STREETS *)pObj) -> Key());
}

//////////////////////////////////////////////////////////////////////////////

// Member für Klasse TR_MESH 
TR_MESH::TR_MESH (const char *pKey,long lONr) :
	m_strKey(pKey), m_strGlobalKey(pKey),m_pObj(NULL)
{
	if (lONr != -1 && lONr != 0)
		m_lONr = lONr;

	AddObject ( lONr);

}

///////////////////////////////////////////////////////////////////////////////

TR_MESH::~TR_MESH (void) 
{
	DELETE_OBJ(m_pObj);
}

///////////////////////////////////////////////////////////////////////////////
bool TR_MESH::AddObject(long lONr)
{
	if (lONr == -1 || lONr == 0)
		return false;

	if ( !m_pObj)
		m_pObj = new TR_ObjTree();

	CTable t (*m_pObj);


	if (!t.Find (&lONr)) {

		TR_OBJECTSCreator OSCr (*m_pObj);

		int iErrorCode = 0;

		ContCreate(OSCr, TR_OBJECTS)(lONr,iErrorCode);
	}


	return true;

}
///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_STREETSTree 
TR_MESHTree::TR_MESHTree (void) 
	 : CTree (GetMesh, StrCmp)
{
}

///////////////////////////////////////////////////////////////////////////////

TR_MESHTree::~TR_MESHTree (void) 
{
	EveryDelete();	// alle Elemente des Baumes freigeben
}

///////////////////////////////////////////////////////////////////////////////

void _XTENSN_EXPORT TR_MESHTree::UserDelete (void *pObj) 
{
	((TR_MESH *)pObj) -> TR_MESH::~TR_MESH();
}

//////////////////////////////////////////////////////////////////////////////

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetMesh (void *pObj) 
{
	return (void *)(((TR_MESH *)pObj) -> Key());
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OBJECTS 
TR_OBJECTS::TR_OBJECTS (long lONr, int iError) 
	
{
	if (lONr != -1 && lONr != 0)
		m_lONr = lONr;
	m_iErrorCode = iError;
}

///////////////////////////////////////////////////////////////////////////////

TR_OBJECTS::~TR_OBJECTS (void) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_ObjTree 
TR_ObjTree::TR_ObjTree (void) 
	 : CTree (GetObjects, CmpObjects)
{
}

///////////////////////////////////////////////////////////////////////////////

TR_ObjTree::~TR_ObjTree (void) 
{
	EveryDelete();	// alle Elemente des Baumes freigeben
}

///////////////////////////////////////////////////////////////////////////////

void _XTENSN_EXPORT TR_ObjTree::UserDelete (void *pObj) 
{
	((TR_OBJECTS *)pObj) -> TR_OBJECTS::~TR_OBJECTS();
}

///////////////////////////////////////////////////////////////////////////////

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetObjects (void *pObj) 
{
	return (void *)& (((TR_OBJECTS *)pObj) -> Object());
}

////////////////////////////////////////////////////////////////////////////////

int _XTENSN_EXPORT CmpObjects (void *pObj1, void *pObj2) 
{
long l1 = ((TR_OBJECTS *)pObj1) -> Object();
long l2 = ((TR_OBJECTS *)pObj2) -> Object();

	if ((ulong)l1 < (ulong) l2) return -1;
	if ((ulong) l1 > (ulong) l2) return 1;
	return 0;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

CObjectPipe::CObjectPipe (long lONr,string strLink, int iVar, int iIndex) :
	m_lONr(lONr),m_isValid(0),m_strLinkFeature(strLink), m_iVar(iVar), m_iIndex(iIndex)
{

	if ( m_lONr != -1 && m_lONr != 0)
		FInit();
	
}

//////////////////////////////////////////////////////////////////////////////

CObjectPipe :: ~CObjectPipe (void) 
{
}

///////////////////////////////////////////////////////////////////////////////

void CObjectPipe :: FInit (void) 
{

	FInitTyp();

	if ( m_isValid)
		FInitGCS();

}

///////////////////////////////////////////////////////////////////////////////

void CObjectPipe :: FInitTyp (void) 
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  m_lONr;

	if ( DEX_GetObjStatistik (OS) ) 
		m_iTyp = OS.iObjTyp;

	switch (m_iIndex) {

		case 0: 
		{
			if ( m_iTyp == OT_PUNKT) 
				m_isValid = 1;

		}
		break;

		case 1: 
		{
			if ( m_iTyp == OT_KANTE) 
				m_isValid = 1;

		}
		break;

		case 2: 
		{
			if ( m_iTyp == OT_KANTE || m_iTyp == OT_PUNKT) 
				m_isValid = 1;

		}
		break;

		default:
		break;

	}


}

///////////////////////////////////////////////////////////////////////////////

void CObjectPipe :: FInitGCS (void) 
{

	HPROJECT m_hPr = DEX_GetObjectProject(m_lONr);

	CString strCode;

	if ( m_strLinkFeature != "")
		strCode = (char *) (m_strLinkFeature.c_str());
	else
		strCode.LoadString(IDS_GCOCODEKEY);


	ULONG lMCode = DEX_GetMCodeFromFeatureNameEx (m_hPr, (LPCSTR)strCode );

	TCHAR strGCS [_MAX_PATH];
	TCHAR strKey [5];

	if ( lMCode != 0 ) {

		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = m_lONr;
		TM.lMCode = (long) lMCode;
		TM.imaxLen = _MAX_PATH-1;
		TM.iTTyp = TT_Objekt;
		TM.pMText = strGCS;

		if ( DEX_GetTextMerkmal ( TM )) {				// Merkmal vorhanden
		// Key bestimmen
			if ( CheckGCSOtherCode (strGCS)) {

				if ( m_iVar ) {			// Ortsteilcode
					char *cptr = strGCS+GCS_PARTCODEPOS;
					strncpy (strKey,cptr,3);
					strKey[3] = '\0';
				} else {
					char *cptr = strGCS+GCS_STREETCODEPOS;
					strncpy (strKey,cptr,5);
					strKey[5] = '\0';
				}

				m_strKey =strKey;
				return;

			} else 
				m_isValid = 0;

			return;

		}
	}

	m_isValid = 0;

	return;
}


///////////////////////////////////////////////////////////////////////////////

CObjectDefine::CObjectDefine (long lONr,int iDlgCode,string strLink, string strOriginal) :
	m_lONr(lONr),m_iDlgCode(iDlgCode),m_isValid(0),m_iErrorCode(0),m_strLinkFeature(strLink),m_strOriginal(strOriginal)
{

	if ( m_lONr != -1 && m_lONr != 0)
		FInit();

	
}
//////////////////////////////////////////////////////////////////////////////
CObjectDefine :: ~CObjectDefine (void) 
{
}

///////////////////////////////////////////////////////////////////////////////

void CObjectDefine :: FInit (void) 
{

	FInitTyp();
	FInitGCS();
	FInitGuid();

	if ( m_iErrorCode & m_iDlgCode)
		m_isValid = 1;
}

///////////////////////////////////////////////////////////////////////////////

void CObjectDefine :: FInitTyp (void) 
{
	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  m_lONr;

	if ( DEX_GetObjStatistik (OS) ) 
		m_iTyp = OS.iObjTyp;

}

///////////////////////////////////////////////////////////////////////////////

void CObjectDefine :: FInitGCS (void) 
{

	m_hPr = DEX_GetObjectProject(m_lONr);

	CString strCode;
	if ( m_strLinkFeature != "")
		strCode = (char *) (m_strLinkFeature.c_str());
	else
		strCode.LoadString(IDS_GCOCODEKEY);


	ULONG lMCode = DEX_GetMCodeFromFeatureNameEx (m_hPr, (LPCSTR)strCode );

	TCHAR strGCS [_MAX_PATH];

	int iRefError = 0;
	int iOrgError = 0;

	if ( lMCode != 0 ) {

		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = m_lONr;
		TM.lMCode = (long) lMCode;
		TM.imaxLen = _MAX_PATH-1;
		TM.iTTyp = TT_Objekt;
		TM.pMText = strGCS;

		if ( DEX_GetTextMerkmal ( TM )) {				// Merkmal vorhanden
//			m_strGCS = strGCS;
			iRefError = SetGCSErrorCode(strGCS);		// Test GCO-Struktur

			if (iRefError) {				// Keine GCO-Struktur
			// Noch andere Attribute durchsuchen !!!
				if ( SetEnumGCSErrorCode(strGCS) ) {
			//		m_strGCS = strGCS;
					if ( !FindOriginalCode(&iOrgError)) {
						if (!iOrgError)
							m_iErrorCode = m_iErrorCode | GCS_OTHER;
					}
				}
				m_iErrorCode = m_iErrorCode | iRefError;

			} else {
				ControlIsAlpha(strGCS);
			}

			m_strGCS = strGCS;

			return;

		}

	// Fehlender Hauptcode . d.h.bei Code außer fehlender Polygis-Key: dort im Original suchen
		m_iErrorCode = m_iErrorCode | GCS_NOTHING;		// Kein GCO-Code

	}

	// Kein HauptMerkmal bzw. nicht definiert - Original abtesten

	bool bOrgExist = FindOriginalCode(&iOrgError);

	if ( !bOrgExist)
		m_iErrorCode = m_iErrorCode | iOrgError;		// Kein GCO-Struktur im Original
			
	// Noch andere Attribute durchsuchen !!!
	if ( SetEnumGCSErrorCode(strGCS) ) {
		m_strGCS = strGCS;

		if ( !bOrgExist) {		// GCO-Struktur in anderen Merkmal als Original gefunden
			if (!iOrgError)
				m_iErrorCode = m_iErrorCode | GCS_OTHER;
		}
	}

	return;
}
/////////////////////////////////////////////////////////////////////////////////////
bool CObjectDefine :: ControlIsAlpha(const char *pGCSCode)
{

	if ( !pGCSCode)
		return false;
	char *eptr = strchr(pGCSCode,'\0');
	if ( eptr)
		eptr--;
	else
		return false;

	char * aptr = (char *)pGCSCode;

	while (eptr != aptr) {
		if ( *eptr == '_')
			return true;

		if ( isalpha((int)*eptr)) {

			char inChar = *eptr;
			if ( islower(inChar) ) 
				*eptr = toupper(inChar);

		}

		eptr--;

	}

	return false;
}
//////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////
bool CObjectDefine :: FindOriginalCode (int *iOrg)
{

	m_hPr = DEX_GetObjectProject(m_lONr);

	CString strOriginal;

	if ( m_strOriginal != "")
		strOriginal = (char *) (m_strOriginal.c_str());
	else
		strOriginal.LoadString(IDS_GCORIGINALKEY);


	ULONG lMCode = DEX_GetMCodeFromFeatureNameEx (m_hPr, (LPCSTR)strOriginal );

	TCHAR strGCS [_MAX_PATH];

	*iOrg = GCS_NOTHING;

	if ( lMCode != 0 ) {

		TARGETMERKMAL TM;
		memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = m_lONr;
		TM.lMCode = (long) lMCode;
		TM.imaxLen = _MAX_PATH-1;
		TM.iTTyp = TT_Objekt;
		TM.pMText = strGCS;

		if ( DEX_GetTextMerkmal ( TM )) {				// Merkmal vorhanden
			*iOrg = SetGCSErrorCode(strGCS);
			if (*iOrg) {				// Keine GCO-Struktur
				return false;
			} else {
				ControlIsAlpha(strGCS);
			}
			m_strGCS = strGCS;
			*iOrg = 0;
			return true;
		}
		return false;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////
bool CObjectDefine :: SetEnumGCSErrorCode (const char *pGCSCode)
{

	if ( !pGCSCode || *pGCSCode == '\0')
		return false;

	ObjFeat OB;
	INITSTRUCT(OB, ObjFeat);
	OB.lONr = m_lONr;
	OB.lMCode = -1;
	OB.iTyp = m_iTyp;
	OB.pCode = pGCSCode;

	
	ENUMNOKEY ENK;

	ENK.eFcn = ( ENUMNOKEYPROC) FindGCSCode;
	ENK.ePtr = &OB;
	
	DEX_EnumMCodes(ENK);

	if ( OB.lMCode == -1 )
		return false;

	return true;
}
/////////////////////////////////////////////////////////////////////////////

short CObjectDefine :: SetGCSErrorCode (const char *pGCSCode)
{
	if ( !pGCSCode || !*pGCSCode) {
//		m_iErrorCode = m_iErrorCode | GCS_NOTHING;		// Kein GCS-Feld
		return GCS_NOTHING;
	}

	char *cptr = strchr ( pGCSCode,'_');
	if (!cptr) {
//		m_iErrorCode = m_iErrorCode | GCS_SYNTAX;		// Keine GCS-Struktur
		return GCS_SYNTAX;
	}

////////////////////////////////////////////////////////////////////////////////

	// Test, ob KurzCode getestet werden soll
//	if ( isShortCode(pGCSCode) ) {

	// Punkt abfangen

	if ( m_iTyp == OT_PUNKT) {

		BOOL iFlag = FALSE;

		iFlag = CheckGCSPointCode (pGCSCode);		//Verkürzter GCO-Code
		if ( !iFlag)
			iFlag = CheckGCSOtherCode (pGCSCode);

		if (!iFlag) {
//			m_iErrorCode = m_iErrorCode | GCS_SYNTAX;		//  GCS-Struktur falsch (Feldlänge)
			return GCS_SYNTAX;
		}
 
		return 0;

	}

	if ( strlen (pGCSCode) != GCS_LENGTH) {

//		m_iErrorCode = m_iErrorCode | GCS_SYNTAX;		//  GCS-Struktur falsch (Feldlänge)
		return GCS_SYNTAX;

	}
	
	if ( !CheckGCSOtherCode (pGCSCode) ){
//		m_iErrorCode = m_iErrorCode | GCS_SYNTAX;		//  GCS-Struktur falsch (Feldlänge)
		return GCS_SYNTAX;
	}

	return 0;
}



//////////////////////////////////////////////////////////////////////////

void CObjectDefine :: FInitGuid (void) 
{

	USES_CONVERSION;

	OBJECTGUID OGUID;
	INITSTRUCT(OGUID, OGUID);

	OGUID.lONr = m_lONr;
	if ( OGUID.lONr != -1) {
	
		if( SUCCEEDED(DEX_GetObjectGuid(OGUID)) ) {
			CComBSTR	strGUID(OGUID.guid);
			m_strGuid = W2A(strGUID);
		}
	}
}


////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CObjectStatus::CObjectStatus (long lONr, CComBSTR bstrError) :
	m_lONr(lONr),m_isValid(0),m_iErrorCode(0), m_bstrError(bstrError)
{

	if ( m_lONr != -1 && m_lONr != 0)
		FInit();

	
}

CObjectStatus :: ~CObjectStatus (void) 
{
}

///////////////////////////////////////////////////////////////////////////////

void CObjectStatus :: FInit (void) 
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  m_lONr;

	if ( DEX_GetObjStatistik (OS) ) 
		m_iTyp = OS.iObjTyp;


	CString ECode;

	USES_CONVERSION;

	if (m_bstrError.Length() > 0)
		ECode = W2A(m_bstrError);
	else
		ECode.LoadString (IDS_ERRORCODEFEATUREKEY);

	// Test, ob OE bereits definiert
	HPROJECT hPr = DEX_GetObjectProject(m_lONr);
	long m_lErrorCode = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)ECode);


	if ( m_lErrorCode == 0) 
		return;

	char buffer[_MAX_PATH];


	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = m_lONr;
	TM.lMCode = (long) m_lErrorCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = &buffer[0];

	if ( !DEX_GetTextMerkmal ( TM )) 
		return;

	m_iErrorCode = atoi(buffer);
	m_isValid = 1;

}

///////////////////////////////////////////////////////////////////////////////

CLineStatus::CLineStatus (long lONr, int iError, CComBSTR bstrErrorKey) :
	m_lONr(lONr),m_lIdent(0),m_isValid(0),m_iTyp(0),m_iErrorCode(iError), m_bstrErrorKey(bstrErrorKey)
{

	m_iError = 0;	// gefundener Fehler

	if ( m_lONr != -1 && m_lONr != 0)
		FInit();

	if ( m_iTyp == OT_KANTE || m_iTyp == OT_FLAECHE ) 
		SelectLineObject ();
	
}

CLineStatus :: ~CLineStatus (void) 
{
}

///////////////////////////////////////////////////////////////////////////////

void CLineStatus :: FInit (void) 
{

	OBJSTATISTIK OS;
   	memset (&OS,'\0',sizeof(OBJSTATISTIK));
	OS.dwSize = sizeof(OBJSTATISTIK);

	OS.lONr =  m_lONr;

	if ( DEX_GetObjStatistik (OS) ) 
		m_iTyp = OS.iObjTyp;


}

void CLineStatus :: SelectLineObject (void) 
{

	if ( m_iErrorCode & LINE_NOTCONTROL)
		GetNotControl();

	if ( m_iErrorCode & LINE_CTRLFEATURE)
		GetControlFeature();

	if ( m_iErrorCode & LINE_CTRLINTERN)
		GetControlIntern();


}
///////////////////////////////////////////////////////////////////////////////
void CLineStatus :: GetNotControl (void) 
{
	long lIdent = DEX_GetObjIdent(m_lONr);

	m_lIdent = lIdent;

	if ( lIdent != 0) {

		HPROJECT hPr = DEX_GetObjectsProject (lIdent);

		//	ID besorgen
		char NewIdent[MAX_OKS_LENX+1];

		ClassFromIdentX ( hPr,lIdent, NewIdent,strlen(NewIdent));

		char *cptr = strrchr(NewIdent,'\0');
		if ( cptr) {
			cptr--;
			if ( *cptr == '0' || *cptr == '2' || *cptr == '3' ) {	// nicht referenzierte Klassen
				m_isValid = 1;
				m_iError = m_iError | LINE_NOTCONTROL;
			}
		}

	}

}
///////////////////////////////////////////////////////////////////////////////
void CLineStatus :: GetControlFeature (void) 
{

	CComBSTR BemA;
	BemA.LoadString(IDS_LINEFEATBEMA);

	CComBSTR BemD;
	BemD.LoadString(IDS_LINEFEATBEMD);

	USES_CONVERSION;

	if ( GetFeature ( W2A(BemA)) || GetFeature (W2A(BemD))) {
		m_isValid = 1;
		m_iError = m_iError | LINE_CTRLFEATURE;
	}
}
///////////////////////////////////////////////////////////////////////////////
bool CLineStatus :: GetControlIntern (void) 
{

	USES_CONVERSION;

	if (m_bstrErrorKey.Length() > 0) {
		return GetInternFeature ( W2A(m_bstrErrorKey));
		
	}
	return false;

}
//////////////////////////////////////////////////////////////////////////////
bool CLineStatus :: GetFeature ( char *pText)
{
	if ( pText == NULL || *pText == '\0')
		return false;

	// Test, ob OE bereits definiert
	HPROJECT hPr = DEX_GetObjectProject(m_lONr);
	long lMCode = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)pText);

	if ( lMCode == 0) 
		return false;

	char buffer[_MAX_PATH];

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = m_lONr;
	TM.lMCode = (long) lMCode;
	TM.imaxLen = _MAX_PATH - 1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = &buffer[0];

	if ( !DEX_GetTextMerkmal ( TM )) 
		return false;

	if (buffer[0] == '\0')
		return false;

	long i = 0;

	while ( buffer[i] != '\0') {
		if ( buffer[i] != ' ')
			return true;
	}

	return false;
}

/////////////////////////////////////////////////////////////////////////////////////
bool CLineStatus :: GetInternFeature ( char *pText)
{
	if ( pText == NULL || *pText == '\0')
		return false;

	// Test, ob OE bereits definiert
	HPROJECT hPr = DEX_GetObjectProject(m_lONr);
	long lMCode = DEX_GetMCodeFromFeatureNameEx(hPr,(LPCSTR)pText);

	if ( lMCode == 0) 
		return false;

	TCHAR strGCS [_MAX_PATH];

	TARGETMERKMAL TM;
	memset ( &TM, '\0', sizeof ( TARGETMERKMAL) );	
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = m_lONr;
	TM.lMCode = (long) lMCode;
	TM.imaxLen = _MAX_PATH-1;
	TM.iTTyp = TT_Objekt;
	TM.pMText = strGCS;

	if ( DEX_GetTextMerkmal ( TM )) {

		char *cptr = strchr(strGCS,'_');
		if ( cptr ) {

			if ( m_iTyp == OT_KANTE) {

				if (CheckGCSOtherCode (strGCS)) 
					return LineInternFeature ( strGCS);

			}
		}
	}
	return false;

}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
bool CLineStatus :: LineInternFeature ( char *pText)
{
	if ( pText == NULL || *pText == '\0')
		return false;

	if ( strncmp(pText+GCS_STREETCODEPOS,"90",2) == 0 || strncmp(pText+GCS_STREETCODEPOS,"99",2) == 0 ) {
		m_isValid = 1;
		m_iError = m_iError | LINE_CTRLINTERN;

		return true;
	}

	return false;

}
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			trif.cpp
//
//	Stand:			02.12.1994
//	Beschreibung:	TRIAS-Interface-Objekt
//					- Header-Update
//					- IdentsDB-Update
//					- GeoObjekt-Zugriff
//	Entwicklung:	02.12.94	Beginn der Kodierung
///////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "edbs.hpp"

#include <errcodes.hxx>                 // Fehlermeldungen
#include <hdrentrx.hxx>                 // HeaderEntryX

extern "C"
{
	#include <xtension.h>
	#include <xtensnn.h>
	#include <xtensnx.h>
}

#include "trif.hpp"
#include <errinstx.hxx>					// ErrInstall
#include "cxstring.h"
#include "ObjPool.hpp"

#include "resource.h"

extern int AllTrimm(CString&);
extern CTriasInterface*	g_pTriasInterface;
extern BOOL g_bKurzeIdents;
extern CObjektPool *g_pObjektPool;

//	Konstruktor  ------------------------------------------------------

CTriasInterface::CTriasInterface()
{
	m_hPr = NULL;
	m_lOffsetX = m_lOffsetY = 0;
	m_dKoeff11 = m_dKoeff22 = 1.0;
	m_dKoeff12 = m_dKoeff21 = 0.0;
	m_lUniqueIdent = 0;
	m_bHexIdents = TRUE;
	m_bHexMKodes = FALSE;

	CString name;

    char *txt = name.GetBuffer( 1024 );
    UINT len = ::GetWindowsDirectory( txt, 1023 );
    txt[len] = '\0';
	name.ReleaseBuffer();
	if (( name[name.GetLength() - 1] != '/' ) &&
		( name[name.GetLength() - 1] != '\\' ))
		name += '/';
	name += "EDBS.INI";

    m_strIniFileName = name;
}

BOOL CTriasInterface::FInit()
{
	Tidy();		// erstmal alles freigeben

CxString		strTemp, strBuffer;
BOOL			bUpdateHeader = FALSE;
int				i;

// Header - Daten
//	1. vorhandene Einträge
	VERIFY(strTemp.LoadString(IDS_OFFSETX));
	m_lOffsetX = HeaderEntryX(strTemp).EntryLong(0);

	VERIFY(strTemp.LoadString(IDS_OFFSETY));
	m_lOffsetY = HeaderEntryX(strTemp).EntryLong(0);

	VERIFY(strTemp.LoadString(IDS_KOEFF11));
	m_dKoeff11 = HeaderEntryX(strTemp).EntryDouble(1.0);

	VERIFY(strTemp.LoadString(IDS_KOEFF12));
	m_dKoeff12 = HeaderEntryX(strTemp).EntryDouble(0.0);

	VERIFY(strTemp.LoadString(IDS_KOEFF21));
	m_dKoeff21 = HeaderEntryX(strTemp).EntryDouble(0.0);

	VERIFY(strTemp.LoadString(IDS_KOEFF22));
	m_dKoeff22 = HeaderEntryX(strTemp).EntryDouble(1.0);

	m_lUniqueIdent = DEX_GetUniqueIdentMCode();
	m_hPr = DEX_GetDataSourceHandle();

// 2. Einträge aus der EDBS.INI
	if (!m_lOffsetX && !m_lOffsetY)
	{
		strBuffer.GetPrivateProfileString("HEADER", "OffsetX", "", 255, m_strIniFileName);
		m_lOffsetX = strBuffer.Long();

		strBuffer.GetPrivateProfileString("HEADER", "OffsetY", "", 255, m_strIniFileName);
		m_lOffsetY = strBuffer.Long();

		bUpdateHeader = TRUE;
	}

	if (!m_dKoeff11 || !m_dKoeff22)
	{
		strBuffer.GetPrivateProfileString("HEADER", "Koeff11", "0.01", 255, m_strIniFileName);
		m_dKoeff11 = strBuffer.Double();

		strBuffer.GetPrivateProfileString("HEADER", "Koeff12", "0.00", 255, m_strIniFileName);
		m_dKoeff12 = strBuffer.Double();

		strBuffer.GetPrivateProfileString("HEADER", "Koeff21", "0.00", 255, m_strIniFileName);
		m_dKoeff21 = strBuffer.Double();

		strBuffer.GetPrivateProfileString("HEADER", "Koeff22", "0.01", 255, m_strIniFileName);
		m_dKoeff22 = strBuffer.Double();

		bUpdateHeader = TRUE;
	}

	if (bUpdateHeader)
		UpdateHeader();

	if (strBuffer.GetPrivateProfileString("EDBS Allgemein",	"nicht definierte Objekte ignorieren", "", 255, m_strIniFileName) > 0)
		m_bUndefinedObj = (strBuffer == "nein");
	else
		m_bUndefinedObj = TRUE;

	m_bHexIdents = (DEX_GetIdBase() == 16);
	m_bHexMKodes = (DEX_GetMkBase() == 16);

// IdentsDB
	m_tabIdent.SetTyp('i');
	m_tabMMK.SetTyp('m');

// erstmal funktionsfähig nur für TRiAS-Datenquellen (Merkmale werden alle am ersten gelieferten
// Ident gespeichert)
	_ASSERTE(DEX_GetTRiASDataSourceEx(m_hPr));

CString strIdent;

//	i = 1;
//	strTemp.printf("I%d", i++);
//	while (strBuffer.GetPrivateProfileString("IDENTS", strTemp, "",	255, m_strIniFileName))
//	{
//		m_listTriasId.AddID(strBuffer, m_bHexIdents);
//		if (2 == i)
//			strIdent = strBuffer;		// Objektklasse für Merkmale speichern
//		strTemp.printf("I%d", i++);
//	}

	i = 1;
	strTemp.printf("T%d", i++);
	while (strBuffer.GetPrivateProfileString("TYPEN", strTemp, "", 255, m_strIniFileName))
	{
	// #HK000929: was früher in 2 Einträgen war, ist jetzt in einem
	// I1=OKS,Description und T1=ObjArt,OKS ist jetzt 
	// T1=ObjArt,OKS,Description
	CxString strObjArt, strOKS, strDesc, strT;

		VERIFY(strBuffer.Teilen(strObjArt, strT, ','));
		VERIFY(strT.Teilen(strOKS, strDesc, ','));
	
	// Zuordnung Objektart --> Objektklassenschlüssel
		strBuffer = strObjArt + ',' + strOKS;
		m_listEdbsId.AddID(strBuffer, m_bHexIdents);
		m_Aliase.AddEintrag(strBuffer);
#if defined(_USE_B_REGELN)
		m_Regeln.AddEintrag(strBuffer);
#endif // defined(_USE_B_REGELN)

	// Zuordnung Objektklassenschlüssel --> Kurztext/Langtext
		strBuffer = strOKS + ',' + strDesc;
		m_listTriasId.AddID(strBuffer, m_bHexIdents);
		if (2 == i)
			strIdent = strBuffer;		// Objektklasse für Merkmale speichern
	
	// der Nächste bitte	
		strTemp.printf("T%d", i++);
	}
	if (strIdent.IsEmpty()) {
		strIdent = "C0000000,EDBS_Objekt";
		m_listTriasId.AddID(strIdent, m_bHexIdents);
	}

// allgemeine Merkmalsregeln
	m_Aliase.AddRegelnA("*");		// allgemeine A-Regeln hinzufügen
	m_Aliase.AddRegelnC("*");		// allgemeine C-Regeln hinzufügen

	i = 1;
	strTemp.printf("M%d", i++);
	while (strBuffer.GetPrivateProfileString("MERKMALE", strTemp, "", 255, m_strIniFileName))
	{
		m_tabMMK.AddMMK(strBuffer, m_bHexMKodes, strIdent);
		strTemp.printf("M%d", i++);
	}
	m_tabMMK.AddMMK("0,ATKIS-Folie", m_bHexMKodes, strIdent);
	m_tabMMK.AddMMK("0,ATKIS-Objektart", m_bHexMKodes, strIdent);
	m_tabMMK.AddMMK("0,ATKIS-Dateiname", m_bHexMKodes, strIdent);
	m_tabMMK.AddMMK("0,ATKIS-Objektnummer", m_bHexMKodes, strIdent);

	return TRUE;
}

CTriasInterface::~CTriasInterface()
{
	Tidy();
}

void CTriasInterface::Tidy()
{
	m_tabIdent.Tidy();
	m_tabMMK.Tidy();
	m_listEdbsId.Tidy();
	m_listTriasId.Tidy();
	m_Aliase.Tidy();
#if defined(_USE_B_REGELN)
	m_Regeln.Tidy();
#endif // defined(_USE_B_REGELN)
}

long CTriasInterface::TextMMK(const char* kurz)
{
	return m_tabMMK.FindeKode(kurz);
}

BOOL CTriasInterface::AddMMK(const char* kurz, LPCSTR pcOKS)
{
	return m_tabMMK.AddMMK(kurz, m_bHexIdents, pcOKS);
}

//	ProjectOpen  ------------------------------------------------------
BOOL CTriasInterface::ProjectOpen()
{
	BOOL result = TRUE;

	return result;
}	// ProjectOpen

//	UpdateHeader  -----------------------------------------------------
void CTriasInterface::UpdateHeader()
{
CxString	strTemp, strText;

	VERIFY(strTemp.LoadString(IDS_OFFSETX, TRUE));
	{
		strText.Empty();
		strText.printf("%ld", m_lOffsetX);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	VERIFY(strTemp.LoadString(IDS_OFFSETY, TRUE));
	{
		strText.Empty();
		strText.printf("%ld", m_lOffsetY);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	VERIFY(strTemp.LoadString(IDS_KOEFF11, TRUE));
	{
		strText.Empty();
		strText.printf("%lf", m_dKoeff11);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	VERIFY(strTemp.LoadString(IDS_KOEFF12, TRUE));
	{
		strText.Empty();
		strText.printf("%lf", m_dKoeff12);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	VERIFY(strTemp.LoadString(IDS_KOEFF21, TRUE));
	{
		strText.Empty();
		strText.printf("%lf", m_dKoeff21);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	VERIFY(strTemp.LoadString(IDS_KOEFF22, TRUE));
	{
		strText.Empty();
		strText.printf("%lf", m_dKoeff22);
		HeaderEntryX(strTemp, strText).WriteBack();
	}

	Flush();
}	// UpdateHeader


//	GetIdent  ---------------------------------------------------------
unsigned long CTriasInterface::GetIdent(const char *pcFolie, const char* objart, CMapStringToString* pmm)
{
	CxString	strObjArt, strKurz, strLang;
	CTriasIdent	*pTI;
	unsigned long		result = 0L;

	if (objart) {
		strObjArt = objart;
		strObjArt.Teilen(strKurz, strObjArt, ',');
		strKurz.AllTrimm();
		
		result = m_listEdbsId.GetKode(strKurz);
		while ((result == 0L) && (strObjArt.GetLength() > 0))
		{
			strObjArt.Teilen(strKurz, strObjArt, ',');
			strKurz.AllTrimm();
			result = m_listEdbsId.GetKode(strKurz);
		}
	}

#if defined(_USE_B_REGELN)
	if (!result) {
		strObjArt = objart;
		strObjArt.Teilen(strKurz, strObjArt, ',');
		strKurz.AllTrimm();
		
		result = BildeIdent(strKurz, pmm);
		while ((result == 0L) && (strObjArt.GetLength() > 0))
		{
			strObjArt.Teilen(strKurz, strObjArt, ',');
			strKurz.AllTrimm();
			result = BildeIdent(strKurz, pmm);
		}
	}
#endif // defined(_USE_B_REGELN)

	if (result) {
		if (!m_tabIdent.KodeExist(result))
		{
			pTI = m_listTriasId.GetId(result);
			if (pTI) {
				m_tabIdent.Add(pTI -> Kode(), pTI -> Kurz(), pTI -> Lang());
				m_tabIdent.FindeKode(pTI -> Kurz());	// WriteBack sicherstellen
			}
		}
	}
	if (!result) {
		if (m_bUndefinedObj) {
			ASSERT(NULL != pcFolie && NULL != objart && strlen(pcFolie) > 0 && strlen(objart) > 0);

		// Standardeintrag erzeugen
		CString strKText ("ATKIS ");

			strKText += pcFolie;
			strKText += "-";
			strKText += objart;
			result = m_tabIdent.FindeKode(strKText);
			if (!result) {
			CString strOKS ("C");

				strOKS += pcFolie;
				strOKS += objart;
				result = CTriasIdent::EnsureIdent(strOKS, true, m_bHexIdents);

			CString strLText ("ATKIS-Objekt der Objektart ");

				strLText += objart;
				strLText += " in Folie ";
				strLText += pcFolie;
				m_tabIdent.Add(result, strKText, strLText);
				m_tabIdent.FindeKode(strKText);		// WriteBack sicherstellen
			}

//			result = m_tabIdent.FindeKode("EDBS - Objekt");
//			if (!result)
//			{
//				result = CTriasIdent::EnsureIdent(CString("11111111"), true, m_bHexIdents);
//				m_tabIdent.Add(result, "EDBS - Objekt");
//			}
		}
	}

	return result;
}	// GetIdent


unsigned long CTriasInterface::BildeIdent(const char *objart, CMapStringToString *pmm)
{
unsigned long result = 0L;

#if defined(_USE_B_REGELN)
CString	strK, strKode;

	strK = objart;
//	strK += ':';

POSITION pos;
CRegel *pR = NULL;
CString strKey;

	if (!strK.IsEmpty()) {
		for (pos = m_Regeln.GetStartPosition(); pos != NULL; /**/)
		{
			m_Regeln.GetNextAssoc(pos, strKey, (void*&)pR);
			if (strK == strKey.Left(strK.GetLength()))
				pR -> GetIdent(pmm, strKode);
		}
	}

	if (!strKode.IsEmpty())
		result = CTriasIdent::EnsureIdent(strKode, true, m_bHexIdents);
#endif // defined(_USE_B_REGELN)

	return result;
}	// BildeIdent


BOOL CTriasInterface::NeuesMerkmal(const char *key)
{
	BOOL		res = FALSE;
	POSITION	pos = NULL;

	pos = MerkmalList().Find(key);
	if (pos == NULL)
	{
		MerkmalList().AddTail(key);
		res = TRUE;
	}
	return res;
}


void CTriasInterface::Flush()
{
	IStorage	*pIStorage = NULL;

	DEXN_ReScale();
	DEXN_ReReadIdents();

	if (DEX_GetProjectStorage(pIStorage))
		pIStorage -> Release();
	else
		DEX_FlushModifications();

	DEXN_ReReadContainer();
}	// Flush

void CTriasInterface::DeleteObjekt(long onr)
{
	DEX_DeleteObject(onr);
}

//	-------------------------------------------------------------------
//	CMerkmalsKode
//	-------------------------------------------------------------------
CMerkmalsKode::CMerkmalsKode(char typ, long mmk, const char* kurz, const char* lang, LPCSTR pcOKS)
{
	char*	txt;

	m_lMappedMCode = 0L;

	m_fWritten = false;
	m_Typ  = typ;
	m_MMK  = mmk;
	m_Kurz = kurz;
	m_Lang = lang;
	if (NULL != pcOKS) {
	CString strT;
	CxString strOKS (pcOKS);

		VERIFY(strOKS.Teilen(m_strOKS, strT));
		_ASSERTE(!m_strOKS.IsEmpty());
	}

	m_Gueltig = FALSE;
	if ((typ != 'i') &&(typ != 'm'))
		return;
	if (mmk == 0L)
		return;

	m_Gueltig = TRUE;		// wird bei MemError in Read() oder WriteBack() ggf. wieder gelöscht!!
//	if (!Read()) 
	{
		if (m_Kurz.IsEmpty())
		{
			txt = m_Kurz.GetBuffer(32);
			sprintf(txt, "ATKIS_%ld", mmk);
			m_Kurz.ReleaseBuffer();
		}

	// delay evaluation
//		WriteBack();
	}
}	// Konstruktor

void CMerkmalsKode::WriteBack()
{
	if (!Gueltig() || Written())
		return;		// Falschen Typ abfangen! bzw. bereits weggeschrieben

	if (m_Typ == 'i') {
	// beschreibungsinfos am Ident schreiben
	PBDDATA pbdi;

		INITSTRUCT(pbdi, PBDDATA);
		_ASSERTE(m_MMK);

	ErrInstall EI(WC_NOIDENT);

		pbdi.pbdTyp = m_Typ;
		pbdi.pbdCode = m_MMK;
		pbdi.pbdTemp = 0;

	// dazu evtl. existierenden Eintrag einlesen
	CString	strKurz, strLang;
		
		pbdi.pbdKText = strKurz.GetBuffer(KURZTEXT_LEN);
		pbdi.pbdLText = strLang.GetBuffer(MAX_LANGTEXT_LEN);
		pbdi.pbdKText[0] = '\0';
		pbdi.pbdLText[0] = '\0';
		pbdi.pbdKTextLen = KURZTEXT_LEN - 1;
		pbdi.pbdLTextLen = MAX_LANGTEXT_LEN - 1;
		if (EC_OKAY == DEX_GetPBDData(pbdi)) {
			m_Kurz = strKurz;
			m_Lang = strLang;
		}

	// und nun ggf. wieder wegschreiben
		pbdi.pbdKText = m_Kurz.GetBuffer(KURZTEXT_LEN);
		pbdi.pbdLText = m_Lang.GetBuffer(MAX_LANGTEXT_LEN);
		pbdi.pbdKTextLen = m_Kurz.GetLength();
		pbdi.pbdLTextLen = m_Lang.GetLength();

		DEX_ModPBDData(pbdi);
		DEXN_PBDIdentChanged(m_MMK);

		m_Kurz.ReleaseBuffer();
		m_Lang.ReleaseBuffer();
	}
	else if (m_Typ == 'm') {
	// Ident sicherstellen
	INT_PTR lIdent = CTriasIdent::EnsureIdent(m_strOKS, true, (16 == DEX_GetIdBase()) ? true : false);

		_ASSERTE(0 != lIdent);
		
	// Merkmalscode über aktuelle Datenquelle mappen
		if (0 == m_lMappedMCode) {
		long lMCode = m_MMK;

			if (0 != lMCode) {
			MAPMCODETOHANDLE MTH;
			INT_PTR lMappedMCode = 0L;
			BOOL fCreated = FALSE;

				INITSTRUCT(MTH, MAPMCODETOHANDLE);
				MTH.lIdent = lIdent;
				MTH.lMCode = m_MMK;
				MTH.plHandle = &lMappedMCode;
				MTH.fCreate = true;
				MTH.pfCreated = &fCreated;
				if (DEX_MapOrCreateMCodeToHandle(g_pTriasInterface->hPr(), MTH) && 0L != lMappedMCode)
					lMCode = lMappedMCode;
			}
			if (NULL == lMCode)
				lMCode = DEX_GetUniqueMCode();

			m_lMappedMCode = lMCode;
			_ASSERTE(0 != m_lMappedMCode);
		}

	// Beschreibungsinfos für Merkmal schreiben
	PBDMERKMALEX pbdm;

		INITSTRUCT(pbdm, PBDMERKMALEX);
		_ASSERTE(0 != m_lMappedMCode);

	ErrInstall EI (WC_NOMERKMAL);

		pbdm.ipbdMTyp = 'a';
		pbdm.ipbdMLen = 256;
		pbdm.pbdTyp = m_Typ;
		pbdm.pbdCode = m_lMappedMCode;
		pbdm.lIdent = lIdent;

	// dazu versuchen BeschreibungsInfos einzulesen
	CString	strKurz, strLang;
		
		pbdm.pbdKText = strKurz.GetBuffer(KURZTEXT_LEN);
		pbdm.pbdLText = strLang.GetBuffer(MAX_LANGTEXT_LEN);
		pbdm.pbdKText[0] = '\0';
		pbdm.pbdLText[0] = '\0';
		pbdm.pbdKTextLen = KURZTEXT_LEN - 1;
		pbdm.pbdLTextLen = MAX_LANGTEXT_LEN - 1;
		if (EC_OKAY == DEX_GetPBDData(pbdm)) {
			m_Kurz = strKurz;
			m_Lang = strLang;
		}

	// jetzt ggf. schreiben
		pbdm.pbdKText = (LPSTR)(LPCSTR)m_Kurz;
		pbdm.pbdLText = (LPSTR)(LPCSTR)m_Lang;
		pbdm.pbdKTextLen = m_Kurz.GetLength();
		pbdm.pbdLTextLen = m_Lang.GetLength();

		DEX_ModPBDData(pbdm);
		DEXN_PBDMCodeChanged(m_lMappedMCode);
	}
	m_Gueltig = true;
	m_fWritten = true;
}	// WriteBack

BOOL CMerkmalsKode::Read()
{
	_ASSERTE(FALSE);
	
BOOL result = FALSE;
CString		strKurz, strLang;

	if (!Gueltig())
		return FALSE;	// falschen Typ abfangen!

PBDDATA pbd;
ErrInstall EI ((m_Typ == 'i') ? WC_NOIDENT : WC_NOMERKMAL);

	INITSTRUCT(pbd, PBDDATA);
	pbd.pbdTyp = m_Typ;
	pbd.pbdCode = m_MMK;
	pbd.pbdKText = strKurz.GetBuffer(KURZTEXT_LEN);
	pbd.pbdLText = strLang.GetBuffer(MAX_LANGTEXT_LEN);
	pbd.pbdKText[0] = '\0';
	pbd.pbdLText[0] = '\0';

	pbd.pbdTemp = 0;
	pbd.pbdKTextLen = KURZTEXT_LEN - 1;
	pbd.pbdLTextLen = MAX_LANGTEXT_LEN - 1;
	result = (EC_OKAY == DEX_GetPBDData(pbd)) ? TRUE : FALSE;

	strKurz.ReleaseBuffer();
	strLang.ReleaseBuffer();

	if (result)	{
		m_Kurz = strKurz;
		m_Lang = strLang;
	}
	return result;
}	// Read

//	-------------------------------------------------------------------
//	CKodeTabelle
//	-------------------------------------------------------------------
CKodeTabelle::~CKodeTabelle()
{
	Tidy();
}

void CKodeTabelle::Tidy()
{
	for (int i = 0; i < GetSize(); i++) {
		if (GetAt(i))
			delete (CMerkmalsKode *)GetAt(i);
	}
	RemoveAll();
}

long CKodeTabelle::FindeKode(const char* kurz)
{
	long kode = 0L;

	for (int i = 0; i < GetSize(); i++) {
		if (((CMerkmalsKode *)GetAt(i)) -> KurzText() == kurz)
		{
			((CMerkmalsKode *)GetAt(i)) -> WriteBack();		// sicher wegschreiben
			kode = ((CMerkmalsKode *)GetAt(i)) -> Kode();
			break;
		}
	}
	return kode;
}	// FindeKode

BOOL CKodeTabelle::KodeExist(long k)
{
	BOOL result = FALSE;

	for (int i = 0; i < GetSize(); i++) {
		if (((CMerkmalsKode*)GetAt(i)) -> Kode() == k)
		{
			result = TRUE;
			break;
		}
	}
	return result;
}	// KodeExist

BOOL CKodeTabelle::Add(long kode, const char* kurz, const char* lang)
{
	BOOL			result = FALSE;
	CMerkmalsKode	*pMMK;

	if (m_Typ == '\0')
		return result;
	pMMK = new CMerkmalsKode(m_Typ, kode, kurz, lang);

	if (!pMMK)
		return result;
	if (!pMMK -> Gueltig())
	{
		delete pMMK;
		return result;
	}
	CObArray::Add(pMMK);
	result = TRUE;
	return result;
}	// Add

BOOL CKodeTabelle::AddMMK(const char* def, BOOL hexbase, LPCSTR pcOKS)
{
BOOL			result = FALSE;
CMerkmalsKode	*pMMK;
long			kode;
CString			kurz, lang;
int				i;
char			*stop;

	if (m_Typ != 'm')
		return result;
	if (!def)
		return result;

	if (hexbase)
		kode = strtol(def, &stop, 16);
	else
		kode = atol(def);

	lang = def;
	i = lang.Find(',');
	if (i <= 0)
		return result;
	lang = lang.Mid(i + 1);
	i = lang.Find('\t');
	if (i > 0)
	{
		kurz = lang.Left(i);
		lang = lang.Mid(i + 1);
	}
	else
	{
		kurz = lang;
		lang.Empty();
	}

// ggf. existierenden MCode verwenden oder neuen MCode anfordern
	if (0 == kode) {
		kode = DEX_GetMCodeFromFeatureNameCIEx(DEX_GetDataSourceHandle(), (LPCSTR)kurz);
		if (0 == kode)
			kode = DEX_GetUniqueMCode();
	}
	if (0 == kode)
		return result;

	pMMK = new CMerkmalsKode(m_Typ, kode, kurz, lang, pcOKS);
	if (!pMMK)
		return result;

	if (!pMMK -> Gueltig())
	{
		delete pMMK;
		return result;
	}
	CObArray::Add(pMMK);
	result = TRUE;
	return result;
}	// Add

BOOL CKodeTabelle::Mod(long kode, const char* kurz,	const char* lang)
{
	BOOL			result = FALSE;
	CMerkmalsKode	*pK;

	if (kode == 0L)
		return result;
	if (lstrlen(kurz) == 0)
		return result;

	for (int i = 0; i < GetSize(); i++) {
		if (((CMerkmalsKode*)GetAt(i)) -> Kode() == kode)
		{
			pK = (CMerkmalsKode*)GetAt(i);
			if (pK -> Gueltig()) {
				pK -> KurzText() = kurz;
				if (lstrlen(lang))
					pK -> LangText() = lang;
				else		
					pK -> LangText().Empty();
				pK -> WriteBack();
			}
			result = pK -> Gueltig();
			break;
		}
	}
	return result;
}	// Mod

//	-------------------------------------------------------------------
//	CTriasObjekt
//	-------------------------------------------------------------------
CTriasObjekt::CTriasObjekt()
{
	m_lONr		= 0L;
	m_lIdent	= 0L;
	m_iObjTyp   = OGUnknown;
	m_lCnt		= 0L;
	m_iKCnt		= 0;
	m_pdblX		= NULL;
	m_pdblY		= NULL;
	m_plCnt		= NULL;
	m_bNeu		= FALSE;
}	// Konstruktor

CTriasObjekt::~CTriasObjekt()
{
	if (m_pdblX)
		delete[] m_pdblX;
	if (m_pdblY)
		delete[] m_pdblY;
	if (m_plCnt)
		delete[] m_plCnt;
	m_lONr		= 0L;
	m_lIdent	= 0L;
	m_iObjTyp   = OGUnknown;
	m_lCnt		= 0L;
	m_iKCnt		= 0;
	m_pdblX		= NULL;
	m_pdblY		= NULL;
	m_plCnt		= NULL;
}	// Destruktor

BOOL CTriasObjekt::ReadyForRead()
{
	return (ONr() != 0L);
//	return ((( ONr() != 0L ) && ( Ident() != 0L ) && ( ObjTyp() != OGUnknown ))
//			|| ( !UniqueIdent().IsEmpty()));
}	// ReadyForRead

BOOL CTriasObjekt::ReadyForWrite()
{
	if (Neu())
		return (Ident() != 0L) && (ObjTyp() != OGUnknown);
	return 0 != ONr();

//	return	(( ONr() != 0L ) && ( Ident() != 0L ) && ( ObjTyp() != OGUnknown )
//			&& ( AnzahlPunkte() > 0 ) && ( XKoord() != NULL ) && ( YKoord() != NULL )
//			&& ( AnzahlKonturen() > 0 ) && ( KonturPunkte() != NULL ));
}	// ReadyForWrite

static BOOL LeseStatusZeigen = TRUE;

BOOL CTriasObjekt::Read()
{
	BOOL		result = FALSE;

	if (!ReadyForRead())
		return result;

	if (ONr() != 0L) {	// Objekt lesen
	OBJGEOMETRIE	og;
	CString			key, text;
	
		INITSTRUCT(og, OBJGEOMETRIE);

		og.lONr    = ONr();
		result = DEX_GetObjStatistik(og);
		if (!result)
			return result;	

		XKoord(new double[og.lCnt]);
		YKoord(new double[og.lCnt]);
		KonturPunkte(new long[og.iKCnt]);

		og.lONr    = ONr();
		og.iFlags  = (short)(OGConverted);
		og.pdblX   = XKoord();
		og.pdblY   = YKoord();
		og.plCnt   = KonturPunkte();

		result = DEX_GetObjGeometrie(og);

		Ident() = og.lIdent;
		ObjTyp() = og.iObjTyp;
		AnzahlPunkte() = og.lCnt;
		AnzahlKonturen() = og.iKCnt;
	}
	else {	// Objekt über UniqueIdent suchen!
	}
	return result;
}	// Read

void CTriasObjekt::AddTextMerkmal(const char *key, const char *text, BOOL add)
{
	CString		temp;

	temp = key;
	if (temp.IsEmpty())
		return;
	temp = text;
	if (temp.IsEmpty())
		return;

	if (TextMerkmal(key, temp))		// Schon vorhanden??
	{
		if (add)						// Ja! Neuen Text anfügen?
		{
			temp += '\n';				// Ja!
			temp += text;
			m_Merkmale.SetAt(key, temp);
		}
		else							// Nicht anfügen ==> Ersetzen!
			m_Merkmale.SetAt(key, text);
	}
	else								// Noch nicht vorhanden!
		m_Merkmale.SetAt(key, text);
}	// AddTextMerkmal

CString CTriasObjekt::GetOKS()
{
	return CTriasIdent::GetOKS(m_lIdent);
}

BOOL CTriasObjekt::WriteBack()
{
	BOOL			result = FALSE;
	long			mmk;
	CString			key, text;
	POSITION		pos;

	if (!ReadyForWrite())
		return result;

	if (OGText != ObjTyp()) {
		if (OGUnknown != ObjTyp()) {
			_ASSERTE(NULL != XKoord());		// Geometry muß da sein
			_ASSERTE(NULL != XKoord());

		// Punkt, Linie oder Fläche
		OBJGEOMETRIE og;

			INITSTRUCT(og, OBJGEOMETRIE);
			og.lONr    = ONr();
			og.lIdent  = Ident();
			og.iObjTyp = ObjTyp();
			if (Neu())
				og.iFlags  = (short)(OGNewObject|OGConverted|OGNoMemoryObject|OGForceGeometry);
			else
				og.iFlags  = (short)(OGModObject|OGConverted|OGNoMemoryObject|OGForceGeometry);

			og.lCnt    = AnzahlPunkte();
			og.iKCnt   = AnzahlKonturen();
			og.pdblX   = XKoord();
			og.pdblY   = YKoord();
			og.plCnt   = KonturPunkte();

		GEOMETRIEWITHCS GCS;

			INITSTRUCT(GCS, GEOMETRIEWITHCS);
			GCS.pOG = &og;
			GCS.pICS = ((CEDBSExtension *)g_pTE)->get_CS();

			result = DEX_ModObjGeometrie(GCS);
			if (0 == ONr())
				ONr() = og.lONr;

			XKoord(og.pdblX);
			YKoord(og.pdblY);
		}
	} 
	else {
	// Textobjekt gesondert behandeln
		_ASSERTE(NULL != XKoord());		// Geometry muß da sein
		_ASSERTE(NULL != XKoord());
		_ASSERTE(!m_strTextObjekt.IsEmpty());	// Text muß gegeben sein
		
	TEXTGEOMETRIE og;

		INITSTRUCT(og, TEXTGEOMETRIE);
		og.lONr    = ONr();
		og.lIdent  = Ident();
		og.iObjTyp = ObjTyp();
		if (Neu())
			og.iFlags  = short(OGNewObject|OGConverted|OGNoMemoryObject|OGForceGeometry);
		else
			og.iFlags  = short(OGModObject|OGConverted|OGNoMemoryObject|OGForceGeometry);

		og.lCnt    = AnzahlPunkte();
		og.pdblX   = XKoord();
		og.pdblY   = YKoord();
		og.iKCnt = m_strTextObjekt.GetLength();
		og.pText = (LPSTR)(LPCSTR)m_strTextObjekt;
		
	GEOMETRIEWITHCS GCS;

		INITSTRUCT(GCS, GEOMETRIEWITHCS);
		GCS.pOG = (OBJGEOMETRIE *)&og;
		GCS.pICS = ((CEDBSExtension *)g_pTE)->get_CS();

		result = DEX_ModObjGeometrie(GCS);
		if (0 == ONr())
			ONr() = og.lONr;

		XKoord(og.pdblX);
		YKoord(og.pdblY);
	}

	if (0 != ONr()) {
	// Merkmale schreiben
		if (TextMerkmalExist()) {
		CString strName, strMWert;
		TARGETMERKMALEX m;

			pos = FirstTextMerkmal();
			key = "start";
			while (pos != NULL)
			{
				NextTextMerkmal(pos, key, text);
				mmk = g_pTriasInterface -> TextMMK(key);

			// #HK000813: BEGIN
				if (0 == mmk) {
				// evtl. besonderes Merkmal
				CGeoObj *pGO = NULL;

					if (!g_pObjektPool -> Lookup (m_strUniqueIdent, &pGO)) 
						continue;

				CString strKey (pGO -> ObjektArt());
				CxString strWert;

					if (!g_pTriasInterface -> GetAlias(strKey, key, strWert)) {
					// evtl. C -Regel gefunden
					CString tmpkey (key);

						tmpkey += ':';
						tmpkey += text;

						if (!g_pTriasInterface -> GetAlias(strKey, tmpkey, strWert)) {
						// ggf. Merkmal mit Standardtexten erzeugen
							if (!g_pTriasInterface -> GetImportUnknownData())
								continue;

						// wenns ein interenes ATKIS-Merkmal ist, dann auch weiter
							if (isdigit(key[0]))	// "40", "41" ...
								continue;

						// Standardwerte berechnen
						CString strKText ("ATKIS-Merkmal [");
						
							strKText += key;
							strKText += "]";
							mmk = g_pTriasInterface -> TextMMK(strKText);
							if (0 == mmk) {
							CString strKTextTmp = "0," + strKText;
							CString strOKS = GetOKS() + ",Dummy";

								g_pTriasInterface -> AddMMK(strKTextTmp, strOKS);
								mmk = g_pTriasInterface -> TextMMK(strKText);
								ASSERT(0 != mmk);
								if (0 == mmk)
									continue;
							}

						// der Wert ist noch in 'text'
						// ...
						} 
						else if (strWert.Teilen(strName, strMWert, '#')) {
						// 'C' -Regel
							mmk = g_pTriasInterface -> TextMMK(strName);
							text = strMWert;
						} else
							continue;
					}

				// evtl. 'A' -Regel
					if (0 == mmk)
						mmk = g_pTriasInterface -> TextMMK(strWert);
				}
			// #HK000813: END
			
				if (mmk && !text.IsEmpty())
				{
					INITSTRUCT(m, TARGETMERKMALEX);

					_ASSERTE(mmk);

					m.lTarget = ONr();
					m.lMCode = mmk;
					m.imaxLen = text.GetLength();
					m.iTTyp = TT_Objekt;
					m.pMText = text.GetBuffer(256);
					m.iFlags = TMNoCaching;
					DEX_ModTextMerkmal(m);
					text.ReleaseBuffer();
				}
			}
		}

		if (!UniqueIdent().IsEmpty()) {
		// Unique Ident schreiben
		TARGETMERKMALEX m;

			INITSTRUCT(m, TARGETMERKMALEX);
			m.lTarget = ONr();

			_ASSERTE(g_pTriasInterface -> UniqueIdent());

			m.lMCode = g_pTriasInterface -> UniqueIdent();
			m.imaxLen = UniqueIdent().GetLength();
			m.iTTyp = TT_Objekt;
			m.pMText = UniqueIdent().GetBuffer(256);
			m.iFlags = TMNoCaching;
			DEX_ModTextMerkmal(m);

		// ATKIS-Objektnummer ist der Unique Ident (#HK011112)
			m.lMCode = g_pTriasInterface -> TextMMK("ATKIS-Objektnummer");
			_ASSERTE(0 != m.lMCode);
			DEX_ModTextMerkmal(m);

			UniqueIdent().ReleaseBuffer();
		}
	}
	return result;
}	// WriteBack

// Merkmal entfernen
BOOL CTriasObjekt::RemoveMerkmal (LPCSTR pcKey)
{
	return m_Merkmale.RemoveKey(pcKey);
}

BOOL IsHexDigit(char c)
{
	BOOL	result = FALSE;

	if ((c >= '0') &&(c <= '9'))
		result = TRUE;
	else if ((c >= 'A') &&(c <= 'F'))
		result = TRUE;
	else if ((c >= 'a') &&(c <= 'f'))
		result = TRUE;
	return result;
}

//	-------------------------------------------------------------------
//	CEDBSIdent
//	-------------------------------------------------------------------
CEDBSIdent::CEDBSIdent(const char *def, BOOL hexbase, BOOL fMakeText, LPCSTR pcTextAttr)
{
CxString	strDef, strNr;
int			i;
char		c;

	m_lEKode = 0L;
	m_lTKode = 0L;
	m_fEindeutig = true;

	m_fMakeText = fMakeText;
	if (fMakeText)
		m_strTextAttr = pcTextAttr;
	else
		m_strTextAttr = "";

	if (def) {
		m_lEKode = atol(def);
		strDef = def;
		VERIFY(strDef.Teilen(strNr, strDef, ','));
		
		if (!strDef.IsEmpty()) {
			strDef.Teilen(strNr, strDef, ',');
			for (i = 0; i < strNr.GetLength(); i++)
			{
				c = strNr.GetAt(i);
				if (!IsHexDigit(c))
				{
					m_fEindeutig = FALSE;
					i = strNr.GetLength() + 1;
				}
			}
			m_strOKS = strNr;
		}
	}
}

//	-------------------------------------------------------------------
//	CEDBSidList
//	-------------------------------------------------------------------
CEDBSidList::~CEDBSidList()
{
	Tidy();
}

void CEDBSidList::Tidy()
{
	for (int i = 0; i < GetSize(); i++)
		delete (CEDBSIdent *)GetAt(i);
	RemoveAll();
}


void CEDBSidList::AddID(const char* def, BOOL hexbase)
{
long	id;
BOOL	found = FALSE;

	id = atol(def);
	for (int i = 0; i < GetSize(); i++) {
		if (((CEDBSIdent *)GetAt(i)) -> EDBS_Kode() == id)
		{
			found = TRUE;
			break;
		}
	}

	if (!found) {
	CxString strEintrag (def);
	CxString strText, strKey, strAttr("");
	BOOL fMakeText = FALSE;

		VERIFY(strEintrag.Teilen(strKey, strText, ','));	// strKey enthält Objektart, strText den OKS
		if (strText.GetPrivateProfileString(strKey, "MakeText", "",	255, g_pTriasInterface->GetIniFileName())) {
		CxString strFlag, strTemp;

			VERIFY(strText.Teilen(strFlag, strAttr, ','));
			fMakeText = (strFlag == "1") ? TRUE : FALSE;
			if (fMakeText) {
				if (strTemp.GetPrivateProfileString(strKey, strAttr, "", 255, g_pTriasInterface->GetIniFileName())) {
				// Kurztext des als Text zu verwendenden Attributes herausfischen
				CxString strK;

					VERIFY(strTemp.Teilen (strK, strAttr, ':'));
				} else
					strAttr = "";
			} else
				strAttr = "";
		}

		Add(new CEDBSIdent(def, hexbase, fMakeText, strAttr));
	}
}

long CEDBSidList::GetKode(const char* def)
{
long		id = atol(def);
long		result = 0L;

	for (int i = 0; i < GetSize(); i++) {
		if (((CEDBSIdent *)GetAt(i)) -> EDBS_Kode() == id)
		{
			result = ((CEDBSIdent*)GetAt(i)) -> TRIAS_Kode();
			break;
		}
	}
	return result;
}

bool CEDBSidList::MakeText (LPCSTR def)
{
long id = atol(def);
bool result = false;

	for (int i = 0; i < GetSize(); i++) {
		if (((CEDBSIdent *)GetAt(i)) -> EDBS_Kode() == id)
		{
			result = ((CEDBSIdent*)GetAt(i)) -> MakeText();
			break;
		}
	}
	return result;
}

CString CEDBSidList::GetTextAttr(LPCSTR def)
{
long id = atol(def);
CString result;

	for (int i = 0; i < GetSize(); i++) {
		if (((CEDBSIdent *)GetAt(i)) -> EDBS_Kode() == id)
		{
			result = ((CEDBSIdent*)GetAt(i)) -> GetTextAttr();
			break;
		}
	}
	return result;
}

//	-------------------------------------------------------------------
//	CTriasIdent
//	-------------------------------------------------------------------
CTriasIdent::CTriasIdent(const char* def, BOOL hexbase)
{
CxString strDef, strKurz, strLang;
CxString schl, rest;

	m_lKode = 0L;
	if (def) {
	// lediglich alles bis zum ersten Komma ist OKS
		schl = def;
		schl.Teilen(schl, rest, ',');
		schl.AllTrimm();

		m_strSchl = schl;		// OKS speichern

	// delay evaluation
	//	m_lKode = EnsureIdent(m_strSchl, true, hexbase);		// ggf. Ident neu anlegen
		
	// Kurz- und Langtext isolieren
		strDef = rest;
		if ("/*" == strDef.Left(2))
			strDef = strDef.Mid(2);				// führende "/*" wegschneiden

		strDef.Teilen(strKurz, strLang, '\t');
		if (strLang.IsEmpty())
			strDef.Teilen(strKurz, strLang, "/*");
		if (strLang.IsEmpty())
		{
			strDef.Teilen(strKurz, strLang, "*/");
			if (!strLang.IsEmpty()) {
				if ("*/" == strLang.Right(2)) {
					if (strLang.GetLength() > 2)
						strLang = strLang.Left(strLang.GetLength() - 2);
					else
						strLang = "";
				}
			}
		}
		m_strKurz = strKurz;
		m_strLang = strLang;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Ident sicherstellen
/* static */
unsigned long CTriasIdent::EnsureIdent(CString &rstrOKS, bool fCreate, bool fHexBase)
{
	_ASSERTE(!rstrOKS.IsEmpty());		// OKS muß gesetzt sein

unsigned long ulIdent = 0;

#if !defined(WIN16)
HRESULT hr = IdFromClassX (rstrOKS, &ulIdent, fCreate);

	return ((S_OK == hr) || (S_FALSE == hr && fCreate)) ? ulIdent : 0;	// existent oder neu erzeugt
#else
char *stop = NULL;

	ulIdent = strtol(rstrOKS, &stop, fHexBase ? 16 : 10);
	return ulIdent;
#endif
}

/* static */
CString CTriasIdent::GetOKS (unsigned long lIdent)
{
CString strBuffer;
char *pBuffer = strBuffer.GetBufferSetLength(MAX_OKS_LENX+1);

	if (SUCCEEDED(ClassFromIdentX(g_pTriasInterface->hPr(), lIdent, pBuffer, MAX_OKS_LENX))) {
		strBuffer.ReleaseBuffer();
		return strBuffer;
	}
	return CString("");
}

//	-------------------------------------------------------------------
//	CTriasIdList
//	-------------------------------------------------------------------
CTriasIdList::~CTriasIdList()
{
	Tidy();
}

void CTriasIdList::Tidy()
{
	for (int i = 0; i < GetSize(); i++)
		delete(CTriasIdent *)GetAt(i);
	RemoveAll();
}

void CTriasIdList::AddID(const char* def, BOOL hexbase)
{
//unsigned long	id;
BOOL			found = FALSE;
CxString		strDef, strCls, strRest;

// ggf. nur alles bis zum ersten Komma verwenden
	strDef = def;
	strDef.AllTrimm();
	strDef.Teilen(strCls, strRest, ",");
	if (strCls.IsEmpty())
		strCls = strDef;

// delay evaluation
//#if !defined(WIN16)
//HRESULT	res = IdFromClassX(strCls, &id, true);	// Im Bedarfsfall neu anlegen
//#else
//	if (hexbase)
//		id = strtol(def, &stop, 16);
//	else
//		id = atol(def);
//#endif

	for (int i = 0; i < GetSize(); i++) {
		if (((CTriasIdent *)GetAt(i)) -> OKS() == strCls)
		{
			found = TRUE;
			break;
		}
	}

	if (!found)
		Add(new CTriasIdent(def, hexbase));
}

// Objektklassenbeschreibung über Ident wiederfinden
CTriasIdent *CTriasIdList::GetId(unsigned long id)
{
CTriasIdent	*result = NULL;

	for (int i = 0; i < GetSize(); i++) {
		if (((CTriasIdent *)GetAt(i)) -> Kode() == id)
		{
			result = (CTriasIdent *)GetAt(i);
			break;
		}
	}
	return result;
}

// Objektklassenbeschreibung über Kurztext wiederfinden
CTriasIdent *CTriasIdList::GetId(CString &rstrKurz)
{
	CTriasIdent	*result = NULL;

	for (int i = 0; i < GetSize(); i++) {
		if (((CTriasIdent*)GetAt(i)) -> Kurz() == rstrKurz)
		{
			result = (CTriasIdent *)GetAt(i);
			break;
		}
	}
	return result;
}

/**************************************************************************/
/*	CMapAliase  ***********************************************************/
/**************************************************************************/

CMapAliase::~CMapAliase()
{
	Tidy();
}

void CMapAliase::Tidy()
{
	RemoveAll();
}

/**************************************************************************/
/*	Format eines Eintrages:(veraltete Version)                           */
/*                                                                        */
/*[EDBS]                                                                */
/*	...                                                                   */
/*	In = edbs - code, m, trias - id{, regel | alias{, regel | alias,...}}               */
/*	...                                                                   */
/*	                                                                      */
/*	In                          - nummerierter Eintrag                    */
/*	edbs - code                   - EDBS - Objektklasse(vierstellig)         */
/*	m                           - Anzahl der Regeln/Aliase                */
/*	trias - id                    - TRIAS - Objektklasse(ggf. mit x, y usw.  */
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
/*	Format eines Eintrages:(aktuelle Version)                             */
/*                                                                        */
/*[TYPEN]                                                                 */
/*	...                                                                   */
/*	Tn = edbs - code, trias - id, text                                    */
/*	...                                                                   */
/*                                                                        */
/*[edbs - code]                                                           */
/*	A1 = attr:merkmal                                                     */
/*	...                                                                   */
/*	B1 = attr, wert, trias - id                                           */
/*	...                                                                   */
/*	                                                                      */
/**************************************************************************/

void CMapAliase::AddRegelnA (CString strKey)
{
CxString strTemp, strText;
int i = 1;

	strTemp.printf("A%d", i++);
	while (strText.GetPrivateProfileString(strKey, strTemp, "", 255, g_pTriasInterface->GetIniFileName()))
	{
	CxString strK;
	
		VERIFY(strText.Teilen(strK, strText, ':'));			// A1=GN:[GN] Geographischer Name

		_ASSERTE(!strK.IsEmpty() && !strText.IsEmpty());
		if (!strK.IsEmpty() && !strText.IsEmpty())
		{	
			strTemp = strKey + strK;
			SetAt(strTemp, strText);
		}
		strTemp.printf("A%d", i++);
	}
}

void CMapAliase::AddRegelnC(CString strKey)
{
CxString strTemp, strText;
int i = 1;

	strTemp.printf("C%d", i++);
	while (strText.GetPrivateProfileString(strKey, strTemp, "", 255, g_pTriasInterface->GetIniFileName()))
	{
	CString strK;
	
		VERIFY(strText.Teilen(strK, strText, ','));

	CString strWert;
	CString strMerkName;
	
		if (!strText.IsEmpty())
			strText.Teilen(strWert, strText, ',');
		if (!strText.IsEmpty())
			strText.Teilen(strMerkName, strText, ',');

		_ASSERTE(!strK.IsEmpty() && !strWert.IsEmpty() && !strText.IsEmpty());
		if (!strK.IsEmpty() && !strWert.IsEmpty() && !strText.IsEmpty())
		{
			strText = strMerkName + "#" + strText;
			strTemp = strKey + strK + ":" + strWert;
			SetAt(strTemp, strText);
		}
		strTemp.printf("C%d", i++);
	}
}

void CMapAliase::AddEintrag(const char *eintrag)
{	
CxString strEintrag(eintrag), strT, strKey;

	VERIFY(strEintrag.Teilen(strKey, strT, ','));	// strKey enthält Objektart, strText den OKS

	AddRegelnA (strKey);	// spezifische A-Regeln
	AddRegelnC (strKey);	// spezifische C-Regeln
}

HRESULT IdFromClassX(const char* klasse, unsigned long *pid, BOOL flag)
{
	CString		cls;
	char		*x;

	cls = klasse;
	cls.TrimLeft();
	cls.TrimRight();

	x = cls.GetBuffer(0);
	while ('\0' != *x)
	{
		if (!IsHexDigit(*x))
			*x = '0';
		x++;
	}
	cls.ReleaseBuffer();

	if (g_bKurzeIdents)
		while ((cls.Right(1) == "0") || !IsHexDigit(*(const char*)cls.Right(1)))
			cls = cls.Left(cls.GetLength() -1);

	if (cls.GetLength())
		return IdentFromClassX(g_pTriasInterface->hPr(), cls, pid, flag);
	else
		return (HRESULT) - 1L;
}	// IdFromClassX

#include "crtdbg.h"

void CTriasInterface::EnableCrtMemDbgFlag(BOOL flag)
{
/*
	DWORD	flg = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	if (flag)
	{
		_CrtSetDbgFlag(5);
		m_dwDbgFlag = flg;
	}
	else
		_CrtSetDbgFlag(m_dwDbgFlag);
*/
}

///////////////////////////////////////////////////////////////////////////////
// 
/*static*/
CString CTriasInterface::GetFileName(LPCSTR pcFullpath)
{
char cbFName[_MAX_FNAME];
char cbExt[_MAX_EXT];

	_splitpath (pcFullpath, NULL, NULL, cbFName, cbExt);
	return CString(cbFName) + cbExt;
}

///////////////////////////////////////////////////////////////////////////////
// Wiederfinden eines Objektes
typedef struct tagFINDOBJECTFROMATKIS {
	HOBJECT m_lONr;
	HFEATURE m_lMCode;
	const char *m_pObjNr;
} FINDOBJECTFROMATKIS;

extern "C"
BOOL CALLBACK FindObjectFromAtkisONr (long lONr, BOOL, void *pData)
{
FINDOBJECTFROMATKIS *pFO = reinterpret_cast<FINDOBJECTFROMATKIS *>(pData);
TARGETMERKMAL TM;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = lONr;
	TM.lMCode = pFO -> m_lMCode;
	TM.iTTyp = TT_Objekt;
	TM.pMText = cbBuffer;
	TM.imaxLen = sizeof(cbBuffer)-1;
	if (NULL == DEX_GetTextMerkmal(TM))
		return TRUE;

// Objektnummer nochmal nachprüfen
	if (7 == strlen(pFO -> m_pObjNr))	// keine Objektteilnummer gegeben, Fehler im EDBS ?
		return TRUE;					// eben mal weitermachen

	if (7 == strlen (cbBuffer) && '-' == pFO -> m_pObjNr[7]) 
	// Objekt wurde beim letzten Import vereinigt und liegt nur noch ohne Teilnummer vor
		*reinterpret_cast<HOBJECT *>(pData) = lONr;		// erstmal merken, vielleicht gibts noch was

	return TRUE;
}

extern "C"
BOOL CALLBACK FindObjectFromAtkisONrExact (long lONr, BOOL, void *pData)
{
	*reinterpret_cast<HOBJECT *>(pData) = lONr;
	return FALSE;		// nicht weitermachen, der ertse gewinnt
}

HOBJECT CTriasInterface::FindObject (const char *pObjNr)
{
HOBJECT lONr = INVALID_HOBJECT;
INT_PTR lMCode = DEX_GetMCodeFromFeatureNameCIEx(DEX_GetDataSourceHandle(), "ATKIS-Objektnummer");

	_ASSERTE(INVALID_HFEATURE != lMCode);

// zuerst versuchen vollständig zu matchen
ENUMRECHTEXTMERKMAL ERTM;
FINDOBJECTFROMATKIS FO;

	FO.m_lONr = INVALID_HOBJECT;
	FO.m_lMCode = lMCode;
	FO.m_pObjNr = pObjNr;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.pView = NULL;
	ERTM.lMCode = lMCode;
	ERTM.pMWert = const_cast<char *>(pObjNr);
	ERTM.iMode = SMExactMatch;
	ERTM.eFcn = FindObjectFromAtkisONrExact;
	ERTM.pData = &FO;
	if (!DEX_EnumRechTextMerkmal(ERTM))
		return FO.m_lONr;		// wir habens gefunden (oder auch nicht)

// jetzt Teilobjekt suchen
	if ('-' == pObjNr[7]) {
	char cbBuffer[8];

		strncpy (cbBuffer, pObjNr, 7);
		cbBuffer[7] = '\0';

		ERTM.iMode = SMSubStringStartMatch;
		ERTM.eFcn = FindObjectFromAtkisONr;
		ERTM.pMWert = const_cast<char *>(cbBuffer);
		DEX_EnumRechTextMerkmal(ERTM);
	}
	return FO.m_lONr;			// wir habens gefunden (oder auch nicht)
}


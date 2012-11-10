// Testen der Konsistenz eines Objektes ---------------------------------------
// File: KONSOBJ.CXX

#include "trias02p.hxx"

#include <dbaddr.hxx>
#include <objstat.hxx>

#include "trias02.h"

#include "konsobj.hxx"
#include "konssatz.hxx"
#include "kons.hxx"
#include "kroutins.hxx"

extern char g_pDLLName[260];

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

ERRHANDLERFUNC ERBadGeometrie;

// Gesamtes Objekt testen -----------------------------------------------------
ErrCode TestObjekt (GeoDB &rDB, long lONr, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

	if (DEX_GetObjectStatus(lONr) == OS_Temp)
		return EC_OKAY;

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

// Identifikator dieses Objektes testen
ErrCode RC = KTK.TestIdentifikator (OBLSatz);

// Geometrie testen
	{
	ErrInstall BG (EC_BadGeometrie, ERBadGeometrie);

		if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();
		RC = BadestRC (KTK.TestGeometrie (OBLSatz), RC);
	}

// MerkmaleTesten
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();
	RC = BadestRC (KTK.TestMerkmale (OBLSatz), RC);

return RC;
}

// nur Identifikator testen ---------------------------------------------------
ErrCode TestObjektIdent (GeoDB &rDB, long lONr, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

	if (DEX_GetObjectStatus(lONr) == OS_Temp)
		return EC_OKAY;

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

// Identifikator dieses Objektes testen
return KTK.TestIdentifikator (OBLSatz);
}

// lediglich Merkmale testen --------------------------------------------------
ErrCode TestObjektMerkmale (GeoDB &rDB, long lONr, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

	if (DEX_GetObjectStatus(lONr) == OS_Temp)
		return EC_OKAY;

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

return KTK.TestMerkmale(OBLSatz);
}

// lediglich ein Merkmal testen -----------------------------------------------
ErrCode TestObjektMerkmal (GeoDB &rDB, long lONr, long lMCode, short toDo,
			   CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

	if (DEX_GetObjectStatus(lONr) == OS_Temp)
		return EC_OKAY;

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

return KTK.TestMerkmale (OBLSatz, lMCode);
}

// ein Merkmal wurde gelöscht -------------------------------------------------
ErrCode TestObjektMerkmalDeleted (GeoDB &rDB, long lONr, long lMCode, short toDo,
				  CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

	if (DEX_GetObjectStatus(lONr) == OS_Temp)
		return EC_OKAY;

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

return KTK.TestDeletedMerkmal (OBLSatz, lMCode);
}

// lediglich Merkmale testen --------------------------------------------------
ErrCode TestSichtMerkmale (GeoDB &rDB, const char *pView, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

string strView = pView;

	AnsiToOem (strView.c_str(), (LPSTR)strView.c_str());

CKonsistenzTestKontext KTK(rDB, strView.c_str(), toDo, pPrt);

	if (!KTK) return WC_NOTFOUND;

CSICHTKontext SICHTSatz(KTK);

// SichtSatz lesen
	KTK.SetTStatus (KTSHandleView);
	if (SICHTSatz.KRead() != EC_OKAY) return SICHTSatz.RC();

return KTK.TestMerkmale(SICHTSatz);
}

ErrCode TestSichtMerkmal (GeoDB &rDB, const char *pView, long lMCode, short toDo, 
			  CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

string strView = pView;

	AnsiToOem (strView.c_str(), (LPSTR)strView.c_str());

CKonsistenzTestKontext KTK(rDB, strView.c_str(), toDo, pPrt);

	if (!KTK) return WC_NOTFOUND;

CSICHTKontext SICHTSatz(KTK);

// SichtSatz lesen
	KTK.SetTStatus (KTSHandleView);
	if (SICHTSatz.KRead() != EC_OKAY) return SICHTSatz.RC();

return KTK.TestMerkmale (SICHTSatz, lMCode);
}

// ein Merkmal wurde gelöscht -------------------------------------------------
ErrCode TestSichtMerkmalDeleted (GeoDB &rDB, const char *pView, long lMCode, 
				 short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

string strView = pView;

	AnsiToOem (strView.c_str(), (LPSTR)strView.c_str());

CKonsistenzTestKontext KTK (rDB, strView.c_str(), toDo, pPrt);
CSICHTKontext SICHTSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleView);
	if (SICHTSatz.KRead() != EC_OKAY) return SICHTSatz.RC();

return KTK.TestDeletedMerkmal (SICHTSatz, lMCode);
}

// lediglich Merkmale testen --------------------------------------------------
ErrCode TestIdentMerkmale (GeoDB &rDB, long lIdent, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

CKonsistenzTestKontext KTK (rDB, lIdent, IDL, toDo, pPrt);

	if (!KTK) return WC_NOTFOUND;

CIDLKontext IDLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleIdent);
	if (IDLSatz.KRead() != EC_OKAY) return IDLSatz.RC();

return KTK.TestMerkmale(IDLSatz);
}

// lediglich Merkmale testen --------------------------------------------------
ErrCode TestIdentMerkmal (GeoDB &rDB, long lIdent, long lMCode, short toDo,
			  CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

CKonsistenzTestKontext KTK (rDB, lIdent, IDL, toDo, pPrt);

	if (!KTK) return WC_NOTFOUND;

CIDLKontext IDLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleIdent);
	if (IDLSatz.KRead() != EC_OKAY) return IDLSatz.RC();

return KTK.TestMerkmale (IDLSatz, lMCode);
}

// ein Merkmal wurde gelöscht -------------------------------------------------
ErrCode TestIdentMerkmalDeleted (GeoDB &rDB, long lIdent, long lMCode, 
				 short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

CKonsistenzTestKontext KTK (rDB, lIdent, IDL, toDo, pPrt);
CIDLKontext IDLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleIdent);
	if (IDLSatz.KRead() != EC_OKAY) return IDLSatz.RC();

return KTK.TestDeletedMerkmal (IDLSatz, lMCode);
}

// lediglich Geometrie testen -------------------------------------------------
ErrCode TestObjektGeometrie (GeoDB &rDB, long lONr, short toDo, CProtocol *pPrt)
{
	if (KTDNothing == toDo) return EC_OKAY;		// nichts machen

CKonsistenzTestKontext KTK (rDB, lONr, VERSION0500000E <= rDB.GetDBVersion() ? OBL_NEW : OBL_OLD, toDo, pPrt);
COBLKontext OBLSatz (KTK);

// ObjektSatz lesen
	KTK.SetTStatus (KTSHandleObject);
	if (OBLSatz.KRead() != EC_OKAY) return OBLSatz.RC();

ErrInstall BG (EC_BadGeometrie, ERBadGeometrie);

	return KTK.TestGeometrie(OBLSatz);
}

// ----------------------------------------------------------------------------
// Identifikator eines Objektes Testen und ggf. Korrigieren -------------------
ErrCode CKonsistenzTestKontext :: TestIdentifikator (COBLKontext &OBLSatz)
{
	SetParent (&OBLSatz, NULL);		// BezugsSatz, no hot Point

CIDLKontext IDLSatz (((obl &)OBLSatz).zoid, *this);

	if (IDLSatz.KRead() != EC_OKAY)		// no correction possible
	// Hier kann die Empfehlung ausgesprochen werden, den EntityTest
	// für Identifikatoren durchzuführen, der diesem Objekt evtl. wieder
	// einen (seinen) Identifikator verpassen kann.
		return IDLSatz.RC();

	if (VERSION0500000E <= DB().GetDBVersion()) {
	idl &rIdl = (idl &)IDLSatz;
	bool fFound = false;

		if (EC_OKAY == TestIDL (rIdl.zvio, ObjNr()))
			fFound = true;
		if (EC_OKAY == TestIDL (rIdl.zpvio, ObjNr()))
			fFound = true;
		if (EC_OKAY == TestIDL (rIdl.zlvio, ObjNr()))
			fFound = true;
		if (EC_OKAY == TestIDL (rIdl.zfvio, ObjNr()))
			fFound = true;
		if (EC_OKAY == TestIDL (rIdl.ztvio, ObjNr()))
			fFound = true;
		if (EC_OKAY == TestIDL (rIdl.zkvio, ObjNr()))
			fFound = true;

		{	// jetzt normale Fehlerbehandlung
		ErrInstall BadZVIO (EC_BADLINK, ERBadZVIO, this);
			
			if (!fFound)
				return TestLink (VIO_OLD, rIdl.zvio, ObjNr());
		}
		return EC_OKAY;
	} else {
	// Rückverkettung IDL -> OBL testen, evtl. ObjektSatz neu einhängen
	ErrInstall BadZVIO (EC_BADLINK, ERBadZVIO, this);
	ErrInstall DupZVIO (EC_DUPLLINK, ERBadZVIO, this);
	long &lRef = ((idl &)IDLSatz).zvio;

		SetParent (&IDLSatz, &lRef);
		return TestLink (VIO_OLD, lRef, ObjNr());
	}
}

ErrCode CKonsistenzTestKontext::TestIDL (long &rlFirst, long lONr)
{
ErrInstall BadZVIO (EC_BADLINK);	// erstmal einfach ignorieren
ErrInstall DupZVIO (EC_DUPLLINK);
ErrCode RC = TestLink (VIO_OLD, rlFirst, lONr);

	if (EC_BADLINK == RC) {
	ErrInstall BadZVIO (EC_BADLINK, ERBadZVIO, this);

		return TestLink (VIO_OLD, rlFirst, lONr);
	}
	if (EC_DUPLLINK == RC) {
	ErrInstall DupZVIO (EC_DUPLLINK, ERBadZVIO, this);

		return TestLink (VIO_OLD, rlFirst, lONr);
	}
	return RC;
}

// ----------------------------------------------------------------------------
// Test der MerkmalsInformationen eines Objektes ------------------------------
ErrCode CKonsistenzTestKontext :: TestMerkmale (COBLKontext &OBLSatz, long lMCode)
{
long &lRef = ((obl &)OBLSatz).zovom;
short iStatus = ((obl &)OBLSatz).status;
ErrCode RC = EC_OKAY;
ULONG dwVersion = m_rDB.GetDBVersion();

	if (0 != lRef) {
		SetParent (&OBLSatz, NULL);		// BezugsSatz, no hot Point

		if (VERSION05000008 > dwVersion && (iStatus & SB_TEXTOBJ)) 
		{	// alte GeoDB und Textobjekt
		// MerkmalsKette hängt direkt am Objektsatz
			RC = TestTextMerkmal (lRef);
			if (RC != EC_OKAY && RC != EC_CORRECTED)
				return RC;

			if (lRef == 0 && DStatus() & KTDRepair) {
			// Verweis in DBT war fehlerhaft und es soll repariert werden
			ResourceFile RF (g_pDLLName);
			const char *pText = ResString (ResID (IDS_NOTEXT, &RF), 20);
			short iLen = (strlen (pText) + sizeof(long) -1) / sizeof(long);

				m_rDB.SetDirty();
				DBASSERT (PutText (m_rDB.DBDesc(), pText, iLen, &lRef));
				if (OBLSatz.KWrite() != EC_OKAY)
					return OBLSatz.RC();
				return BadestRC (RC, EC_CORRECTED);
			} 
			return RC;
		}

		if (VERSION05000008 > dwVersion && (iStatus & SB_TEXTOBJIND)) 
		{	// alte GeoDB und indirektes Textobjekt
			RC = TestIndTextMerkmal (lRef);
			if (RC != EC_OKAY && RC != EC_CORRECTED)
				return RC;

			if (lRef == 0 && DStatus() & KTDRepair) {
			// Verweis in DBT war fehlerhaft und es soll repariert werden
			ResourceFile RF (g_pDLLName);
			const char *pText = ResString (ResID (IDS_NOTEXT, &RF), 20);
			short iLen = (strlen (pText) + sizeof(long) -1) / sizeof(long);

				m_rDB.SetDirty();
				DBASSERT (PutText (m_rDB.DBDesc(), pText, iLen, &lRef));
				((obl &)OBLSatz).status &= ~SB_TEXTOBJIND;
				if (OBLSatz.KWrite() != EC_OKAY)
					return OBLSatz.RC();
				return BadestRC (RC, EC_CORRECTED);
			} 
			return RC;
		}

	// alte GeoDB und normale Objektmerkmale oder neue GeoDB
		{	// Finden des MerkmalsSatzes
		long lMKK = -1L;	// default: alle Merkmale testen

			if (IsValidMCode(lMCode)) {
			ErrInstall EI (WC_NOTFOUND);
			DB_ADDR dbaMKL(m_rDB.DBDesc());

				dbaMKL.file_no = MKL;
				RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
				if (EC_OKAY != RC) return RC;
				lMKK = dbaMKL.rec_no;
			} 

		// Testen der Verbindung OBL -> MKL -> OBL über Funktionsaufruf
		// für jeden VOMSatz
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);

			return TestLink (VOM, lRef, lMKK, DefGetWert, 
					 DefGetLink, ObjektMerkmalsTest);
		}
	}

return RC;
}

// ----------------------------------------------------------------------------
// Test der MerkmalsInformationen eines Objektes nach löschen eines Merkmales -
ErrCode CKonsistenzTestKontext :: TestDeletedMerkmal (COBLKontext &OBLSatz, long lMCode)
{
long &lRef = ((obl &)OBLSatz).zovom;
short iStatus = ((obl &)OBLSatz).status;
ErrCode RC = EC_OKAY;
ULONG dwVersion = m_rDB.GetDBVersion();

	if (0 != lRef) {
		SetParent (&OBLSatz, NULL);		// BezugsSatz, no hot Point

		if (VERSION05000008 > dwVersion && (iStatus & (SB_TEXTOBJ|SB_TEXTOBJIND))) 
			return EC_OKAY;	// alte Texte haben keine zusätzlichen Merkmale

	// alte GeoDB und normale Objektmerkmale oder neue GeoDB
	// Testen der Verbindung OBL -> MKL für alle verbleibenden 
		{	// Merkmale des Objektes
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);
		
			RC = TestLink (VOM, lRef, -1L, DefGetWert, DefGetLink);
			if (EC_OKAY != RC) return RC;
		}

	// Testen der Integrität der Rückverkettung für den gebenen MerkmalsCode
	// finden des MerkmalsSatzes
	long lMKK = -1L;	// default: alle Merkmale testen

		if (!IsValidMCode(lMCode)) return WC_NOTFOUND;

		{
		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaMKL(m_rDB.DBDesc());

			dbaMKL.file_no = MKL;
			RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
			if (WC_NOTFOUND == RC) 
				return EC_OKAY;	// war das letzte Merkmal
			
			if (EC_OKAY != RC) return RC;
			lMKK = dbaMKL.rec_no;
		} 
		TX_ASSERT(0L < lMKK);

	// Testen der Verbindung vom MerkmalsCode zurück zum Objekt
	// zuerst alle verbleibenden Rückverweise testen, dann nachsehen, ob
	// dieses Objekt wirklich raus ist.
	CKonsistenzTestKontext locKTK (*this);	// lokale Kopie anlegen
	CMKLKontext MKLSatz (lMKK, locKTK);

		if (MKLSatz.KRead() != EC_OKAY) return MKLSatz.RC();

	long &lMRef = ((mkl &)MKLSatz).zmkvmo;

		locKTK.SetParent (&MKLSatz, &lMRef);
		{
		ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
		ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Rückverkettung allgemein testen
			RC = TestLink (VMO_OLD, lMRef);
			if (EC_OKAY != RC) return RC;

		// Sicherstellen, daß MCode aus Rückverkettung raus ist
			locKTK.SetDStatus (KTDDiagnose);	// nicht fragen, nicht reparieren
			RC = TestLink (VMO_OLD, lMRef, OBLSatz.RecNo());
			if (EC_BADLINK == RC)
				RC = EC_OKAY;		// das ist so recht
			else if (EC_OKAY == RC)
				RC = EC_BADLINK;	// darf nicht passieren
		}
	}

return RC;
}

// ----------------------------------------------------------------------------
// Test der MerkmalsInformationen einer Sicht ---------------------------------
ErrCode CKonsistenzTestKontext :: TestMerkmale (CSICHTKontext &SICHTSatz, long lMCode)
{
long &lRef = ((sicht &)SICHTSatz).zmerkm;
ErrCode RC = EC_OKAY;

	if (VERSION05000008 > m_rDB.GetDBVersion())
		return EC_OKAY;

	if (0 != lRef) {	// hat Merkmale
		SetParent (&SICHTSatz, NULL);		// BezugsSatz, no hot Point

		{	// Finden des MerkmalsSatzes
		long lMKK = -1L;	// default: alle Merkmale testen

			if (IsValidMCode(lMCode)) {
			ErrInstall EI (WC_NOTFOUND);
			DB_ADDR dbaMKL(m_rDB.DBDesc());

				dbaMKL.file_no = MKL;
				RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
				if (EC_OKAY != RC) return RC;
				lMKK = dbaMKL.rec_no;
			} 

		// Testen der Verbindung SICHT -> MKL -> SICHT über Funktionsaufruf
		// für jeden VOMSatz
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);

			return TestLink (VOM, lRef, lMKK, DefGetWert, 
					 DefGetLink, SichtMerkmalsTest);
		}
	}

return RC;
}

// ----------------------------------------------------------------------------
// Test der MerkmalsInformationen einer Sicht nach löschen eines Merkmales ----
ErrCode CKonsistenzTestKontext :: TestDeletedMerkmal (CSICHTKontext &SICHTSatz, long lMCode)
{
long &lRef = ((sicht &)SICHTSatz).zmerkm;
ErrCode RC = EC_OKAY;

	if (VERSION05000008 > m_rDB.GetDBVersion())
		return EC_OKAY;


	if (0 != lRef) {
		SetParent (&SICHTSatz, NULL);		// BezugsSatz, no hot Point

	// Testen der Verbindung SICHT -> MKL für alle verbleibenden 
		{	// Merkmale der Sicht
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);
		ErrCode RC = TestLink (VOM, lRef);

			if (EC_OKAY != RC) return RC;
		}

	// Testen der Integrität der Rückverkettung für den gebenen MerkmalsCode
	long lMKK = -1L;	// default: alle Merkmale testen

		if (!IsValidMCode(lMCode)) return WC_NOTFOUND;

		{	// Finden des MerkmalsSatzes
		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaMKL(m_rDB.DBDesc());

			dbaMKL.file_no = MKL;
			RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
			if (WC_NOTFOUND == RC) 
				return EC_OKAY;	// war das letzte Merkmal
			
			if (EC_OKAY != RC) return RC;
			lMKK = dbaMKL.rec_no;
		} 
		TX_ASSERT(0L < lMKK);

	// Testen der Verbindung vom MerkmalsCode zurück zur Sicht
	CKonsistenzTestKontext locKTK (*this);	// lokale Kopie anlegen
	CMKLKontext MKLSatz (lMKK, locKTK);

		if (MKLSatz.KRead() != EC_OKAY) return MKLSatz.RC();

	long &lMRef = ((mkl &)MKLSatz).zmkvmo;

		locKTK.SetParent (&MKLSatz, &lMRef);
		{
		ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
		ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Rüclverkettung allgemein testen
			RC = TestLink (VMO_OLD, lMRef);
			if (EC_OKAY != RC) return RC;

		// Sicherstellen, daß MCode aus Rückverkettung raus ist
			locKTK.SetDStatus (KTDDiagnose);	// nicht fragen, nicht reparieren
			RC = TestLink (VMO_OLD, lMRef, SICHTSatz.RecNo() | SICHT_MERKMAL);
			if (EC_BADLINK == RC)
				RC = EC_OKAY;		// das ist so recht
			else if (EC_OKAY == RC)
				RC = EC_BADLINK;	// darf nicht passieren
		}
	}

return RC;
}


// Test der MerkmalsInformationen eines Identifikators ------------------------
ErrCode CKonsistenzTestKontext :: TestMerkmale (CIDLKontext &IDLSatz, long lMCode)
{
long &lRef = ((idl &)IDLSatz).zmerki;
ErrCode RC = EC_OKAY;
ULONG dwVersion = m_rDB.GetDBVersion();

	if (VERSION05000008 > m_rDB.GetDBVersion())
		return EC_OKAY;

	if (0 != lRef) {
		SetParent (&IDLSatz, NULL);		// BezugsSatz, no hot Point

		{	// Finden des MerkmalsSatzes
		long lMKK = -1L;	// default: alle Merkmale testen

			if (IsValidMCode(lMCode)) {
			ErrInstall EI (WC_NOTFOUND);
			DB_ADDR dbaMKL(m_rDB.DBDesc());

				dbaMKL.file_no = MKL;
				RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
				if (EC_OKAY != RC) return RC;
				lMKK = dbaMKL.rec_no;
			} 

		// Testen der Verbindung IDL -> MKL -> IDL über Funktionsaufruf
		// für jeden VOMSatz
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);

			return TestLink (VOM, lRef, lMKK, DefGetWert, 
					 DefGetLink, IdentMerkmalsTest);
		}
	}

return RC;
}


// ----------------------------------------------------------------------------
// Test der MerkmalsInformationen einer Sicht nach löschen eines Merkmales ----
ErrCode CKonsistenzTestKontext :: TestDeletedMerkmal (CIDLKontext &IDLSatz, long lMCode)
{
	return EC_OKAY;

long &lRef = ((idl &)IDLSatz).zmerki;
ErrCode RC = EC_OKAY;

	if (VERSION05000008 > m_rDB.GetDBVersion())
		return EC_OKAY;

	if (0 != lRef) {
		SetParent (&IDLSatz, NULL);		// BezugsSatz, no hot Point

	// Testen der Verbindung IDL -> MKL für alle verbleibenden 
		{	// Merkmale des Identifikators
		ErrInstall BadZVOM (EC_BADLINK, ERBadZVOM, this);
		ErrInstall DupZVOM (EC_DUPLLINK, ERBadZVOM, this);
		ErrCode RC = TestLink (VOM, lRef);

			if (EC_OKAY != RC) return RC;
		}

	// Testen der Integrität der Rückverkettung für den gebenen MerkmalsCode
	long lMKK = -1L;	// default: alle Merkmale testen

		if (!IsValidMCode(lMCode)) return WC_NOTFOUND;

		{	// Finden des MerkmalsSatzes
		ErrInstall EI (WC_NOTFOUND);
		DB_ADDR dbaMKL(m_rDB.DBDesc());

			dbaMKL.file_no = MKL;
			RC = (ErrCode)z_keyfind (&dbaMKL, MK, &lMCode);
			if (WC_NOTFOUND == RC) 
				return EC_OKAY;	// war das letzte Merkmal
			
			if (EC_OKAY != RC) return RC;
			lMKK = dbaMKL.rec_no;
		} 
		TX_ASSERT(0L < lMKK);

	// Testen der Verbindung vom MerkmalsCode zurück zum Identifikator
	CKonsistenzTestKontext locKTK (*this);	// lokale Kopie anlegen
	CMKLKontext MKLSatz (lMKK, locKTK);

		if (MKLSatz.KRead() != EC_OKAY) return MKLSatz.RC();

	long &lMRef = ((mkl &)MKLSatz).zmkvmo;

		locKTK.SetParent (&MKLSatz, &lMRef);
		{
		ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
		ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Rückverkettung allgemein testen
			RC = TestLink (VMO_OLD, lMRef);
			if (EC_OKAY != RC) return RC;

		// Testen, ob MCode aus Kette raus ist
			locKTK.SetDStatus (KTDDiagnose);	// nicht fragen, nicht reparieren
			RC = TestLink (VMO_OLD, lMRef, IDLSatz.RecNo() | IDL_MERKMAL);
			if (EC_BADLINK == RC)
				RC = EC_OKAY;		// das ist so recht
			else if (EC_OKAY == RC)
				RC = EC_BADLINK;	// darf nicht passieren
		}
	}

return RC;
}


// Test einer MerkmalsVerbindung VOM -> MKL -> OBL ----------------------------
// diese Routine wird für jeden erfolgreich gelesenen VOM-Satz gerufen --------
ErrCode ObjektMerkmalsTest (CKonsistenzTestKontext &rKTK, CSatzKontext *pSK)
{
// ParameterTest
	if (NULL == pSK || NULL == pSK -> GetData()) return EC_NOMEMORY;

long *pData = (long *)pSK -> GetData();	// Daten des Verbindungssatzes
ErrCode RC;
CKonsistenzTestKontext locKTK (rKTK);	// lokale Kopie anlegen

// 1. Testen der Verbindung vom MerkmalsCode zurück zum Objekt
CMKLKontext MKLSatz (pData[0], locKTK);

	if (EC_OKAY != MKLSatz.KRead())		// no correction possible
	// Hier kann die Empfehlung ausgesprochen werden, den EntityTest
	// für MerkmalsCodes durchzuführen, der diesem Objekt evtl. wieder
	// diesen (seinen) MerkmalsCode verpassen kann.
		return MKLSatz.RC();

long &lRef = ((mkl &)MKLSatz).zmkvmo;

	locKTK.SetParent (&MKLSatz, &lRef);
	{
	ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
	ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Testen der Verbindung mit Wiederfinden des Objektes
		RC = locKTK.TestLink (VMO_OLD, lRef, locKTK.ObjNr());
	}

// 2. Testen der konkreten Merkmalskette dieses MerkmalsCodes
	locKTK.SetParent (pSK);
	
return BadestRC (locKTK.TestMerkmalsInfo(pData[2], ((mkl &)MKLSatz).typ), RC);
}

// Test einer MerkmalsVerbindung SICHT -> MKL -> SICHT ------------------------
// diese Routine wird für jeden erfolgreich gelesenen VOM-Satz gerufen --------
ErrCode SichtMerkmalsTest (CKonsistenzTestKontext &rKTK, CSatzKontext *pSK)
{
// ParameterTest
	if (NULL == pSK || NULL == pSK -> GetData()) return EC_NOMEMORY;

long *pData = (long *)pSK -> GetData();	// Daten des Verbindungssatzes
ErrCode RC;
CKonsistenzTestKontext locKTK(rKTK);	// lokale Kopie anlegen

// 1. Testen der Verbindung vom MerkmalsCode zurück zur Sicht
CMKLKontext MKLSatz (pData[0], locKTK);

	if (EC_OKAY != MKLSatz.KRead())		// no correction possible
	// Hier kann die Empfehlung ausgesprochen werden, den EntityTest
	// für MerkmalsCodes durchzuführen, der diesem Objekt evtl. wieder
	// diesen (seinen) MerkmalsCode verpassen kann.
		return MKLSatz.RC();

long &lRef = ((mkl &)MKLSatz).zmkvmo;

	locKTK.SetParent (&MKLSatz, &lRef);
	{
	ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
	ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Testen der Verbindung mit Wiederfinden der Sicht
		RC = locKTK.TestLink (VMO_OLD, lRef, locKTK.RecNo() | SICHT_MERKMAL);
	}

// 2. Testen der konkreten Merkmalskette dieses MerkmalsCodes
	locKTK.SetParent (pSK);
	
return BadestRC (locKTK.TestMerkmalsInfo(pData[2], ((mkl &)MKLSatz).typ), RC);
}

// Test einer MerkmalsVerbindung IDL -> MKL -> IDL ----------------------------
// diese Routine wird für jeden erfolgreich gelesenen VOM-Satz gerufen --------
ErrCode IdentMerkmalsTest (CKonsistenzTestKontext &rKTK, CSatzKontext *pSK)
{
// ParameterTest
	if (NULL == pSK || NULL == pSK -> GetData()) return EC_NOMEMORY;

long *pData = (long *)pSK -> GetData();	// Daten des Verbindungssatzes
ErrCode RC;
CKonsistenzTestKontext locKTK(rKTK);	// lokale Kopie anlegen

// 1. Testen der Verbindung vom MerkmalsCode zurück zur Sicht
CMKLKontext MKLSatz (pData[0], locKTK);

	if (MKLSatz.KRead() != EC_OKAY)		// no correction possible
	// Hier kann die Empfehlung ausgesprochen werden, den EntityTest
	// für MerkmalsCodes durchzuführen, der diesem Objekt evtl. wieder
	// diesen (seinen) MerkmalsCode verpassen kann.
		return MKLSatz.RC();

long &lRef = ((mkl &)MKLSatz).zmkvmo;

	locKTK.SetParent (&MKLSatz, &lRef);
	{
	ErrInstall BadZVMO (EC_BADLINK, ERBadZVMO, &locKTK);
	ErrInstall DupZVMO (EC_DUPLLINK, ERBadZVMO, &locKTK);

		// Testen der Verbindung mit Wiederfinden der Sicht
		RC = locKTK.TestLink (VMO_OLD, lRef, locKTK.RecNo() | IDL_MERKMAL);
	}

// 2. Testen der konkreten Merkmalskette dieses MerkmalsCodes
	locKTK.SetParent (pSK);
	
return BadestRC (locKTK.TestMerkmalsInfo(pData[2], ((mkl &)MKLSatz).typ), RC);
}

// Testen einer konkreten MerkmalsKette ---------------------------------------
ErrCode CKonsistenzTestKontext :: TestMerkmalsInfo (long &lFirst, long lMTyp)
{
// Je nach MerkmalsTyp entsprechende Funktion rufen
	GetParent() -> SetField (&lFirst);

	switch (lMTyp) {
	case 0:		// TextMerkmal
		return TestTextMerkmal (lFirst);

	case 1:		// IntegerMerkmal
	case 3:		// DoubleMerkmal
		return TestNumericMerkmal (lFirst);

	case 10:	// Binärmerkmal
		return TestBinaryMerkmal (lFirst);

	default:
		return (ErrCode)db_error (WC_BADMKTYP, RC_TestMerkmalsInfo); 
	}

return EC_OKAY;
}

// Testen der Konsistenz eines Textmerkmales ----------------------------------
long DBTGetWert (long *pData) { return (long &)((fdbt *)pData) -> infof[0]; }
long & DBTGetLink (long *pData) { return ((fdbt *)pData) -> zndbtf; }

ErrCode CKonsistenzTestKontext :: TestTextMerkmal (long &lFirst)
{
ErrInstall BadZDBT (EC_BADLINK, ERBadZDBT, this);
ErrInstall DupZDBT (EC_DUPLLINK, ERBadZDBT, this);

	return TestLink (FDBT, lFirst, -1, DBTGetWert, DBTGetLink);
}

// Test der Konsistenz eines IndirektTextmerkmales ----------------------------
ErrCode CKonsistenzTestKontext :: TestIndTextMerkmal (long &)
{
	return EC_OKAY;
}

// Testen der Konsistenz einer Integer/Double- Merkmalskette ------------------
long MIGetWert (long *pData) { return *(((mi *)pData) -> mw); }
long & MIGetLink (long *pData) { return ((mi *)pData) -> znmi; }

ErrCode CKonsistenzTestKontext :: TestNumericMerkmal (long &lFirst)
{
ErrInstall BadZNMI (EC_BADLINK, ERBadZNMI, this);
ErrInstall DupZNMI (EC_DUPLLINK, ERBadZNMI, this);

	return TestLink (MI, lFirst, -1, MIGetWert, MIGetLink);
}

// Testen der Konsistenz eines Binärmerkmales ---------------------------------
ErrCode CKonsistenzTestKontext :: TestBinaryMerkmal (long &)
{
	return EC_OKAY;
}



// ----------------------------------------------------------------------------
// Geometrie eines Objektes Testen und ggf. Korrigieren -----------------------
ErrCode CKonsistenzTestKontext :: TestGeometrie (COBLKontext &OBLSatz)
{
// Geometrie testen 
	SetGStatus (KTKNoGeometrie);

// zuerst testen, ob Fläche
ErrCode RC = EC_OKAY;
ErrCode SumRC = EC_OKAY;

	{
	long &lRef = ((obl &)OBLSatz).zovoma;

		if (lRef) {
			SetParent (&OBLSatz, &lRef);
			if ((RC = TestGeometrieArea (lRef)) == EC_OKAY || 
			     RC == EC_CORRECTED) {
				if (lRef) SetGStatus (KTKisValidArea);
			} else
				SetGStatus (KTKisArea);
			SumRC = RC;
		}
	}

// dann testen, ob Linie 
	{
	long &lRef = ((obl &)OBLSatz).zovol;

		if (lRef) {
			SetParent (&OBLSatz, &lRef);
			if ((RC = TestGeometrieLine (lRef)) == EC_OKAY ||
			     RC == EC_CORRECTED) {
				if (lRef) SetGStatus (KTKisValidLine);
			} else
				SetGStatus (KTKisLine);
			SumRC = BadestRC (SumRC, RC);
		}
	}

// dann Testen, ob Punkt
	{
	long &lRef = ((obl &)OBLSatz).zokp;

		if (lRef) {
			SetParent (&OBLSatz, &lRef);
			if ((RC = TestGeometriePoint (lRef)) == EC_OKAY || 
			     RC == EC_CORRECTED) {
				if (lRef) SetGStatus (KTKisValidPoint);
			} else
				SetGStatus (KTKisPoint);
			SumRC = BadestRC (SumRC, RC);
		}
	}

// Geometriezustand auswerten
	switch (GStatus()) {
	case KTKNoGeometrie:		// keine Geometrie
	case KTKisValidPoint:		// gültiger Punkt
	case KTKisValidLine:		// gültige Linie
	case KTKisValidArea:		// gültige Fläche
		break;

	default:
		RC = (ErrCode)db_error (EC_BadGeometrie, RC_TestGeometrie, this);
		SumRC = BadestRC (SumRC, RC);
		break;
	}

return SumRC;
}

// GeometrieTest der EinzelObjektGeometrieKetten ------------------------------
ErrCode CKonsistenzTestKontext :: TestGeometriePoint (long &lzokp) 
{
CPOLKontext POLSatz (lzokp, *this);

// ObjektStatus merken
	SetTStatus (KTSHandlePoint);
	if (POLSatz.KRead() != EC_OKAY) return POLSatz.RC();

	SetParent (&POLSatz, NULL);

// Eigentlicher PunktTest
ErrCode RC = TestCoords (((pol &)POLSatz).kpkrd.px, ((pol &)POLSatz).kpkrd.py);

// Rückverweis zum Objekt testen
	{
	long &lRef = ((pol &)POLSatz).zpvgo;

		GetParent() -> SetField (&lRef);
		SetBrother (NULL);
		{
		ErrInstall BadZVGO (EC_BADLINK, ERBadZVGO, this);
		ErrInstall DupZVGO (EC_DUPLLINK, ERBadZVGO, this);

			RC = BadestRC (TestLink (VGO, lRef, ObjNr()), RC);
		}
	}
	
// Kantenfolge am Punkt überprüfen
	{
	long &lRef = (long &)((pol &)POLSatz).zpkfk;

		GetParent() -> SetField (&lRef);
		SetBrother (NULL);
		if (lRef != 0) {
//		ErrInstall BadZKFK (EC_BADLINK, ERBadZKFK, this);

			RC = BadestRC (TestLink(KFK, lRef), RC);
		}
	}

return RC; 
}


ErrCode CKonsistenzTestKontext :: TestGeometrieLine (long &lzovol) 
{ 
	return EC_OKAY; 
}


ErrCode CKonsistenzTestKontext :: TestGeometrieArea (long &) 
{ 
	return EC_OKAY; 
}


// Fehlerbehandlung für GeometrieTestAuswertung 1. Version --------------------
int ERBadGeometrie (int EC, int RC, ...)
{
va_list locList;
CKonsistenzTestKontext *pKTK;

	va_start (locList, RC);
	pKTK = va_arg (locList, CKonsistenzTestKontext *);
	va_end (locList);

char outBuff[128];
ResourceFile RF (g_pDLLName);

	wsprintf (outBuff, ResString (ResID (IDS_KONSBADGEOMETRIE, &RF), 120), 
		  pKTK -> ObjNr(), pKTK -> GStatus());

	if (pKTK -> DStatus() & KTDProtocol)
		pKTK -> Out (outBuff);

	if (pKTK -> DStatus() & KTDQueryCorrection) {
		if (!KonsErrorWindow (outBuff))
			return EC;
	}

return EC;
}



// Allgemeine FehlerRoutine für inhaltliche Korrektur einer Rückverkettung ----
int ERBadLink (int EC, int RC, short iFileNo, unsigned int resID, va_list locList)
{
long *plWert = va_arg (locList, long *);	// in der Verbindungsliste nicht wiedergefundener Wert	
CKonsistenzTestKontext *pKTK = va_arg (locList, CKonsistenzTestKontext *);

	if (pKTK == NULL || plWert == NULL) 
		return WC_RETURN;	// StandardFehlerBehandlung rufen

	if (!(~(KTDDiagnose|KTDDeepDiagnose) & pKTK -> DStatus()))
		return EC;			// lediglich diagnostizieren

CSatzKontext *pSK = pKTK -> GetMe();

	if (pSK == NULL)
		return WC_RETURN;	// StandardFehlerBehandlung rufen

char outBuff[128];
char cbBuffer[64];
ResourceFile RF (g_pDLLName);
char cbTarget[64];

	cbTarget[0] = '\0';
	switch (pKTK -> TStatus()) {
	case KTSHandleView:
		strcpy (cbTarget, pKTK -> View());
		break;

	case KTSHandleObject:
	case KTSHandlePoint:
	case KTSHandleLine:
	case KTSHandleArea:
		ltoa (pKTK -> ObjNr(), cbTarget, 10);
		break;

	case KTSHandleIdent:
		ultoa (pKTK -> ObjNr(), cbTarget, DEX_GetIdBase());
		break;

	default:
		TX_ASSERT(false);
		break;
	}

	wsprintf (outBuff, ResString (ResID (resID, &RF), 120), 
		  ResString (ResID (pKTK -> TStatus(), &RF), 15).Addr(),
		  cbTarget, pKTK -> ListName (pSK -> FileNo(), cbBuffer), 
		  pSK -> RecNo());

	if (pKTK -> DStatus() & KTDProtocol) 
		pKTK -> Out (outBuff);

// Wenn repariert werden soll
	if (pKTK -> DStatus() & KTDRepair) {
	// erstmal nachfragen
		if (pKTK -> DStatus() & KTDQueryCorrection) {
			if (!KonsErrorWindow (outBuff))
				return EC;
		}

		if (VMO_OLD == iFileNo || VIO_OLD == iFileNo) {
		// mit neuer VIO/VMO ist Korrektur not supported (yet)
			if (VERSION0500000F <= pKTK -> DB().GetDBVersion())
				return EC;
		}

	CSatzKontext *pParent = pKTK -> GetParent();

		if (pParent == NULL) return EC;

	long *pF = pParent -> GetField();

		if (EC_BADLINK == EC) {
		// EC_BADLINK: fehlender Verweis
			if (pF && *plWert != -1) {
			// wenn Wert gegeben ist, dann
			// neuen VerbindungsSatz anlegen und 
				pKTK -> DB().SetDirty();
				DBASSERT (PutLink (pKTK -> DB().DBDesc(), iFileNo, pF, *plWert));

			// Satz wegschreiben
				if (pParent -> KWrite() != EC_OKAY)
					return pParent -> RC();
				return EC_CORRECTED;
			}
		} else {
		// EC_DUPLLINK: doppelter Verweis
			if (pF && *plWert != -1) {
			// wenn Wert gegeben ist, dann
			// ersten VerbindungsSatz löschen und 
				pKTK -> DB().SetDirty();
				DBASSERT (DelLink (pKTK -> DB().DBDesc(), iFileNo, pF, *plWert));

			// Satz wegschreiben
				if (pParent -> KWrite() != EC_OKAY)
					return pParent -> RC();
				return EC_CORRECTED;
			}
		}
	}

return EC;
}


// FehlerRoutinen für die inhaltliche Korrektur einer Rückverkettung ----------
// Testen einer Rückverkettung zum ObjektSatz ---------------------------------
int ERBadZVGO (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZVGO : IDS_KONSDUPZVGO;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, VGO, resID, locList);
	va_end (locList);

return iResult;
}

int ERBadZVIO (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZVIO : IDS_KONSDUPZVIO;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, VIO_OLD, resID, locList);
	va_end (locList);

return iResult;
}

int ERBadZVOM (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZVOM : IDS_KONSDUPZVOM;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, VOM, resID, locList);
	va_end (locList);

return iResult;
}

int ERBadZVMO (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZVMO : IDS_KONSDUPZVMO;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, VMO_OLD, resID, locList);
	va_end (locList);

return iResult;
}

int ERBadZDBT (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZDBT : IDS_KONSDUPZDBT;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, FDBT, resID, locList);
	va_end (locList);

return iResult;
}

int ERBadZNMI (int EC, int RC, ...)
{
va_list locList;
int iResult;
UINT resID = (EC_BADLINK == EC) ? IDS_KONSBADZMI : IDS_KONSDUPZMI;

	va_start (locList, RC);
	iResult = ERBadLink (EC, RC, MI, resID, locList);
	va_end (locList);

return iResult;
}


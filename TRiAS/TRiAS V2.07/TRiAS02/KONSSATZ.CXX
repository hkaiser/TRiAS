// CSatzKontext, der einen gelesenen Satz mit aktivem Feld repraesentiert ------
// File: KONSSATZ.CXX

#include "trias02p.hxx"

#include <risrecs.h>
#include <risfiles.h>
#include <dbaddr.hxx>

//#include "dbd.h"
#include "trias02.h"

//#include "dbd.hxx"
#include "konssatz.hxx"
#include "kons.hxx"
#include "kroutins.hxx"

extern char g_pDLLName[260];

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CSatzKontext :: CSatzKontext (short iFileNo, long lRecNo, size_t iSize, 
			      CKonsistenzTestKontext &rKTK)
	      : m_rKTK (rKTK), m_rDBA (iFileNo, lRecNo, rKTK.DB().DBDesc())
{
	m_pFeld = NULL;
	m_pSatz = new char [iSize];
	if (m_pSatz == NULL)
		m_RC = (ErrCode)db_error (EC_NOMEMORY, RC_ctSatzKontext);
}

CSatzKontext :: ~CSatzKontext (void)
{
	DELETE (m_pSatz);
}

// Einlesen eines Satzes ------------------------------------------------------
ErrCode CSatzKontext :: KRead (void)
{
	TX_ASSERT(NULL != m_pSatz);

ErrInstall InvAddr (EC_INVADDR, ERInvAddr, &m_rKTK);
ErrInstall DelRecord (EC_DELRECORD, ERDelRecord, &m_rKTK);

	m_rKTK.SetMe (this);
	
return (m_RC = (ErrCode)z_readrec ((db_addr *)&m_rDBA, m_pSatz));
}

ErrCode CSatzKontext :: KWrite (void)
{
	TX_ASSERT(NULL != m_pSatz);
	m_rKTK.DB().SetDirty();

return (m_RC = (ErrCode)z_writerec ((db_addr *)&m_rDBA, m_pSatz));
}


COBLKontext :: COBLKontext (CKonsistenzTestKontext &rKTK)
	     : CSatzKontext (VERSION0500000E <= rKTK.DB().GetDBVersion() ? OBL_NEW : OBL_OLD, rKTK.ObjNr(), sizeof(obl), rKTK)
{
	// nothing to do
}

CSICHTKontext :: CSICHTKontext (CKonsistenzTestKontext &rKTK)
	       : CSatzKontext (SICHT, (DWORD)rKTK.RecNo(), sizeof(sicht), rKTK)
{
	// nothing to do
}

// POLSatz --------------------------------------------------------------------
CPOLKontext :: CPOLKontext (long lRecNo, CKonsistenzTestKontext &rKTK)
	     : CSatzKontext (POL, lRecNo, sizeof(pol), rKTK)
{
	// nothing to do
}


// IDLSatz --------------------------------------------------------------------
CIDLKontext :: CIDLKontext (long lRecNo, CKonsistenzTestKontext &rKTK)
	     : CSatzKontext (IDL, lRecNo, sizeof(idl), rKTK)
{
	// nothing to do
}

CIDLKontext :: CIDLKontext (CKonsistenzTestKontext &rKTK)
	     : CSatzKontext (IDL, (DWORD)rKTK.RecNo(), sizeof(idl), rKTK)
{
	// nothing to do
}

// MKLSatz --------------------------------------------------------------------
CMKLKontext :: CMKLKontext (long lRecNo, CKonsistenzTestKontext &rKTK)
	     : CSatzKontext (MKL, lRecNo, sizeof(mkl), rKTK)
{
	// nothing to do
}


// Allgemeine VerbindungsDatei ------------------------------------------------
CVerbKontext :: CVerbKontext (short iFileNo, long lRecNo, CKonsistenzTestKontext &rKTK)
	      : CSatzKontext (iFileNo, lRecNo, rKTK.RecSize(iFileNo)*sizeof(long), rKTK)
{
	// nothing to do
}


// Fehlerbehandlungsfunktionen für LeseFunktion -------------------------------
int ERInvAddr (int EC, int RC, ...)
{
va_list locList;
CKonsistenzTestKontext *pKTK;

	va_start (locList, RC);
	va_arg (locList, void *);	// dummy
	pKTK = va_arg (locList, CKonsistenzTestKontext *);
	va_end (locList);
	
	if (pKTK == NULL) 
		return WC_RETURN;	// StandardFehlerBehandlung rufen

	if (!(~(KTDDiagnose|KTDDeepDiagnose) & pKTK -> DStatus()))
		return EC;			// lediglich diagnostizieren

CSatzKontext *pMe = pKTK -> GetMe();

	if (pMe == NULL)
		return WC_RETURN;	// StandardFehlerBehandlung rufen

char outBuff[128];
char cbBuffer[64];
ResourceFile RF (g_pDLLName);

	wsprintf (outBuff, ResString (ResID (IDS_KONSINVADDR, &RF), 120).Addr(), 
		  ResString (ResID (pKTK -> TStatus(), &RF), 10).Addr(),
		  pKTK -> ObjNr(), pKTK -> ListName(pMe -> FileNo(), cbBuffer), 
		  pMe -> RecNo());

	if (pKTK -> DStatus() & KTDProtocol)
		pKTK -> Out (outBuff);

// evtl. reparieren
	if (pKTK -> DStatus() & KTDRepair) {
	// erstmal nochmal fragen
		if (pKTK -> DStatus() & KTDQueryCorrection) {
			if (!KonsErrorWindow (outBuff))
				return EC;
		}

	CSatzKontext *pParent = pKTK -> GetParent();

		if (pParent == NULL) return EC;

	CSatzKontext *pBrother = pKTK -> GetBrother();

		if (pBrother == NULL) {
		// erster Satz einer Kette spinnt
		long *pF = pParent -> GetField();

			if (pF) {
				*pF = 0;	// Feld ausnullen
				if (pParent -> KWrite() != EC_OKAY)
					return pParent -> RC();
				return EC_CORRECTED;
			}
		} else {
		// mitten in einer Kette
		long *pF = pBrother -> GetField();	// znext

			if (pF) {
				*pF = 0;	// znext ausnullen
				if (pBrother -> KWrite() != EC_OKAY)
					return pBrother -> RC();
				return EC_CORRECTED;
			}
		}
	}

return EC;
}


int ERDelRecord (int EC, int RC, ...)
{
va_list locList;
CKonsistenzTestKontext *pKTK;

	va_start (locList, RC);
	va_arg (locList, void *);	// dummy
	pKTK = va_arg (locList, CKonsistenzTestKontext *);
	va_end (locList);
	
	if (pKTK == NULL) 
		return WC_RETURN;	// StandardFehlerBehandlung rufen

	if (!(~(KTDDiagnose|KTDDeepDiagnose) & pKTK -> DStatus()))
		return EC;			// lediglich diagnostizieren

CSatzKontext *pMe = pKTK -> GetMe();

	if (pMe == NULL)
		return WC_RETURN;	// StandardFehlerBehandlung rufen

char outBuff[128];
char cbBuffer[64];
ResourceFile RF (g_pDLLName);

	wsprintf (outBuff, ResString (ResID (IDS_KONSDELRECORD, &RF), 120), 
		  ResString (ResID (pKTK -> TStatus(), &RF), 10).Addr(),
		  pKTK -> ObjNr(), pKTK -> ListName(pMe -> FileNo(), cbBuffer), 
		  pMe -> RecNo());

	if (pKTK -> DStatus() & KTDProtocol)
		pKTK -> Out (outBuff);

// evtl. reparieren
	if (pKTK -> DStatus() & KTDRepair) {
	// erstmal nochmal fragen
		if (pKTK -> DStatus() & KTDQueryCorrection) {
			if (!KonsErrorWindow (outBuff))
				return EC;
		}

	CSatzKontext *pParent = pKTK -> GetParent();

		if (pParent == NULL) return EC;

	CSatzKontext *pBrother = pKTK -> GetBrother();

		if (pBrother == NULL) {
		long *pF = pParent -> GetField();

			if (pF) {
				*pF = 0;	// Feld ausnullen
				if (pParent -> KWrite() != EC_OKAY)
					return pParent -> RC();
				return EC_CORRECTED;
			}
		} else {
		// mitten in einer Kette
		long *pF = pBrother -> GetField();	// znext

			if (pF) {
				*pF = 0;	// znext ausnullen
				if (pBrother -> KWrite() != EC_OKAY)
					return pBrother -> RC();
				return EC_CORRECTED;
			}
		}
	}

return EC;
}

// Routine, welche eine Dateibezeichnung aus der Dateinummer generiert --------
static long s_cbFileNo[] = {
	0,	// KAL -> KAL
	2,	// KPL -> KPL
	1, 	// SPL -> SPL
	3,	// MAL -> MAL
	4,	// KFK -> KFL
	4,	// KFM -> KFL
	6,	// OBL -> OBL
	12,	// REL -> REL
	13,	// IDL -> IDL
	9,	// MKL -> MKL
	8,	// MI  -> VOM
	17,	// DBT -> DBT
	5,	// VGO -> VGO
	5,	// VZO -> VGO
	7,	// VOL -> VOG
	7,	// VOL -> VOG
	8, 	// VOM -> VOM
	10,	// VMO -> VMO
	11,	// VOR -> VOR
	14,	// VIO -> VIO
	15,	// VRE -> VRE
	16, 	// RAL -> RAL
	2,	// POL -> KPL
	25,	// HEAD -> HDR
	25,	// FHEAD -> HDR
	27, 	// SICHT -> VIS
	28,	// PATTRIBS -> ATT
	28,	// LATTRIBS -> ATT
	28,	// FATTRIBS -> ATT
	30,	// RELTYP -> VAT
	28,	// TATTRIBS -> ATT
};
#define NUMFILES	(sizeof(s_cbFileNo)/sizeof(long))

char *FileName (long, char *);
char *RecordName (long, char *);

char *CKonsistenzTestKontext :: ListName (long iRecord, char *pBuffer)
{
	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 <= iRecord && NUMFILES > iRecord);

char cbFile[20];
char cbRecord[20];

	wsprintf (pBuffer, "%ld (%s[%s])", iRecord, 
//		  FileName (m_rDBD.FileNo(iRecord), cbFile),
		  FileName (s_cbFileNo[iRecord], cbFile),
		  RecordName (iRecord, cbRecord));

return pBuffer;
}

char *RecordName (long iRecord, char *pRecord)
{
	TX_ASSERT(TIsValidAddress(pRecord, 10, true));

unsigned int resID;

	switch (iRecord) {
	case RECORD_KAL:	resID = IDS_RECORDKAL; break;
	case RECORD_KPL:	resID = IDS_RECORDKPL; break;
	case RECORD_SPL:	resID = IDS_RECORDSPL; break;
	case RECORD_MAL:	resID = IDS_RECORDMAL; break;
	case RECORD_KFK:	resID = IDS_RECORDKFK; break;
	case RECORD_KFM:	resID = IDS_RECORDKFM; break;
	case RECORD_OBL:	resID = IDS_RECORDOBL; break;
	case RECORD_REL:	resID = IDS_RECORDREL; break;
	case RECORD_IDL:	resID = IDS_RECORDIDL; break;
	case RECORD_MKL:	resID = IDS_RECORDMKL; break;
	case RECORD_MI:		resID = IDS_RECORDMI; break;
	case RECORD_DBT:	resID = IDS_RECORDDBT; break;
	case RECORD_VGO:	resID = IDS_RECORDVGO; break;
	case RECORD_VZO:	resID = IDS_RECORDVZO; break;
	case RECORD_VOL:	resID = IDS_RECORDVOL; break;
	case RECORD_VOA:	resID = IDS_RECORDVOA; break;
	case RECORD_VOM:	resID = IDS_RECORDVOM; break;
	case RECORD_VMO:	resID = IDS_RECORDVMO; break;
	case RECORD_VOR:	resID = IDS_RECORDVOR; break;
	case RECORD_VIO:	resID = IDS_RECORDVIO; break;
	case RECORD_VRE:	resID = IDS_RECORDVRE; break;
	case RECORD_RAL:	resID = IDS_RECORDRAL; break;
	case RECORD_POL:	resID = IDS_RECORDPOL; break;
	case RECORD_HEAD:	resID = IDS_RECORDHEAD; break;
	case RECORD_FHEAD:	resID = IDS_RECORDFHEAD; break;
	case RECORD_SICHT:	resID = IDS_RECORDSICHT; break;
	case RECORD_PATTRIBS:	resID = IDS_RECORDPATTRIBS; break;
	case RECORD_LATTRIBS:	resID = IDS_RECORDLATTRIBS; break;
	case RECORD_FATTRIBS:	resID = IDS_RECORDFATTRIBS; break;
	case RECORD_RELTYP:	resID = IDS_RECORDRELTYP; break;
	case RECORD_TATTRIBS:	resID = IDS_RECORDTATTRIBS; break;
	case RECORD_KDBT:	resID = IDS_RECORDKDBT; break;
	case RECORD_OBLNEW: resID = IDS_RECORDOBLNEW; break;
	case RECORD_MCODEB: resID = IDS_RECORDMCODEB; break;
	case RECORD_IDENTB: resID = IDS_RECORDIDENTB; break;
	case RECORD_LONGSPL: resID = IDS_RECORDLONGSPL; break;
	default:		resID = IDS_KONSUNKNOWN; break;
	}

ResourceFile RF (g_pDLLName);

	strcpy (pRecord, ResString (ResID (resID, &RF), 10));

return pRecord;
}

char *FileName (long iFile, char *pFile) 
{
	TX_ASSERT(TIsValidAddress(pFile, 4, true));

unsigned int resID;

	switch (iFile) {
	case FILE_KAL:	resID = IDS_FILEKAL; break;
	case FILE_KPL:	resID = IDS_FILEKPL; break;
	case FILE_SPL:	resID = IDS_FILESPL; break;
	case FILE_MAL:	resID = IDS_FILEMAL; break;
	case FILE_KFL:	resID = IDS_FILEKFL; break;
	case FILE_OBL:	resID = IDS_FILEOBL; break;
	case FILE_REL:	resID = IDS_FILEREL; break;
	case FILE_IDL:	resID = IDS_FILEIDL; break;
	case FILE_MKL:	resID = IDS_FILEMKL; break;
	case FILE_VGO:	resID = IDS_FILEVGO; break;
	case FILE_VOG:	resID = IDS_FILEVOG; break;
	case FILE_VOM:	resID = IDS_FILEVOM; break;
	case FILE_VMO:	resID = IDS_FILEVMO; break;
	case FILE_VOR:	resID = IDS_FILEVOR; break;
	case FILE_VIO:	resID = IDS_FILEVIO; break;
	case FILE_VRE:	resID = IDS_FILEVRE; break;
	case FILE_RAL:	resID = IDS_FILERAL; break;
	case FILE_DBT:	resID = IDS_FILEDBT; break;
	case FILE_HKE:	resID = IDS_FILEHKE; break;
	case FILE_HTK:	resID = IDS_FILEHTK; break;
	case FILE_QKE:	resID = IDS_FILEQKE; break;
	case FILE_QTK:	resID = IDS_FILEQTK; break;
	case FILE_MKK:	resID = IDS_FILEMKK; break;
	case FILE_IDK:	resID = IDS_FILEIDK; break;
	case FILE_RLK:	resID = IDS_FILERLK; break;
	case FILE_HDR:	resID = IDS_FILEHDR; break;
	case FILE_HDK:	resID = IDS_FILEHDK; break;
	case FILE_VIS:	resID = IDS_FILEVIS; break;
	case FILE_ATT:	resID = IDS_FILEATT; break;
	case FILE_VSK:	resID = IDS_FILEVSK; break;
	case FILE_VAT:	resID = IDS_FILEVAT; break;
	default:	resID = IDS_KONSUNKNOWN; break;
	}
	
ResourceFile RF (g_pDLLName);

	strcpy (pFile, ResString (ResID (resID, &RF), 4));

return pFile;
}

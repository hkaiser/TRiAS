// KonsistenzTest einzelner Objekte -------------------------------------------
// File: KONS.CXX

#include "trias02p.hxx"

#include <dbaddr.hxx>

#include "trias02.h"

#include "konssatz.hxx"
#include "kons.hxx"
#include "protocol.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor -----------------------------------------------------
CKonsistenzTestKontext :: CKonsistenzTestKontext (GeoDB &rDB, long lTarget, 
				int iTyp, short toDo, CProtocol *pPrt)
		        : m_rDB(rDB), m_pPrt(pPrt)
{
	m_iDStatus = toDo;
	m_pParent = m_pBrother = m_pMe = NULL;
	m_lRecNo = 0L;
	m_iTyp = iTyp;

	switch (iTyp) {
	case IDL:
		{
			m_dwTarget = (DWORD)lTarget;	// IdentMerkmale untersuchen

		DB_ADDR dbaIDL(DB().DBDesc());
		ErrCode RC = EC_OKAY;
		ErrInstall EI (WC_NOTFOUND);

			dbaIDL.file_no = IDL;
			RC = (ErrCode)z_keyfind (&dbaIDL, IDN, &lTarget);
			if (EC_OKAY == RC) 
				m_lRecNo = dbaIDL.rec_no;
			else
				TX_ASSERT(false);
		}
		break;

	case OBL_OLD:
		m_dwTarget = (DWORD)lTarget;	// ObjektMerkmale untersuchen
		m_lRecNo = lTarget;
		break;

	default:
		TX_ASSERT(false);
		break;
	}
}

CKonsistenzTestKontext :: CKonsistenzTestKontext (GeoDB &rDB, const char *pView, 
				short toDo, CProtocol *pPrt)
		        : m_rDB(rDB), m_pPrt(pPrt)
{
	m_iDStatus = toDo;
	m_pParent = m_pBrother = m_pMe = NULL;

	m_dwTarget = (DWORD)pView;
	m_lRecNo = 0L;
	m_iTyp = SICHT;

	{
	DB_ADDR dbaSICHT(DB().DBDesc());
	ErrCode RC = EC_OKAY;
	ErrInstall EI (WC_NOTFOUND);

		dbaSICHT.file_no = SICHT;
		RC = (ErrCode)z_keyfind (&dbaSICHT, SICHTNAME, (LPVOID)pView);
		if (EC_OKAY == RC) 
			m_lRecNo = dbaSICHT.rec_no;
		else
			TX_ASSERT(false);
	}
}

CKonsistenzTestKontext :: CKonsistenzTestKontext (CKonsistenzTestKontext &rKTK)
		        : m_rDB(rKTK.m_rDB), m_pPrt(rKTK.m_pPrt)
{
	m_dwTarget = rKTK.Target();
	m_lRecNo = rKTK.RecNo();
	m_iTyp = rKTK.Typ();
	m_iDStatus = rKTK.DStatus();
	m_iTStatus = rKTK.TStatus();
	m_iGStatus = rKTK.GStatus();

	m_pParent = m_pBrother = m_pMe = NULL;
}

CKonsistenzTestKontext :: ~CKonsistenzTestKontext (void)
{
	// nothing to do
}

// StandardFunktionen für den Zugriff auf Teile eines Verbindungskettensatzes -
long DefGetWert (long *pData) { return pData[0]; }
long & DefGetLink (long *pData) { return pData[1]; }

long VIOGetWert (long *pData) { return LINKTOLINK(((identb *)pData) -> identbkey.zviook); }
long & VIOGetLink (long *pData) { return ((identb *)pData) -> zvionk; }

long VMOGetWert (long *pData) { return ((mcodeb *)pData) -> mcodebkey.zvmook; }
long & VMOGetLink (long *pData) { return ((mcodeb *)pData) -> zvmonk; }

// Liefert RecordGröße in long's ----------------------------------------------
static size_t s_cbRecSize[] = {
	sizeof(kal),		// RECORD_KAL
	sizeof(kpl),		// RECORD_KPL
	sizeof(spl),		// RECORD_SPL
	sizeof(mal),		// RECORD_MAL
	sizeof(kfk),		// RECORD_KFK
	sizeof(kfm),		// RECORD_KFM
	sizeof(obl),		// RECORD_OBL
	sizeof(rel),		// RECORD_REL
	sizeof(idl),		// RECORD_IDL
	sizeof(mkl),		// RECORD_MKL
	sizeof(mi),			// RECORD_MI 
	sizeof(fdbt),		// RECORD_DBT
	sizeof(vgo),		// RECORD_VGO
	sizeof(vzo),		// RECORD_VZO
	sizeof(vol),		// RECORD_VOL
	sizeof(voa),		// RECORD_VOA
	sizeof(vom),		// RECORD_VOM
	sizeof(vmo),		// RECORD_VMO
	sizeof(vor),		// RECORD_VOR
	sizeof(vio),		// RECORD_VIO
	sizeof(vre),		// RECORD_VRE
	sizeof(ral),		// RECORD_RAL
	sizeof(pol),		// RECORD_POL
	sizeof(head),		// RECORD_HEA
	sizeof(fhead),		// RECORD_FHEAD
	sizeof(sicht),		// RECORD_SICHT
	sizeof(pattribs),	// RECORD_PATTRIBS
	sizeof(lattribs),	// RECORD_LATTRIBS
	sizeof(fattribs),	// RECORD_FATTRIBS
	sizeof(reltyp),		// RECORD_RELTYP
	sizeof(tattribs),	// RECORD_TATTRIBS
	sizeof(kdbt),		// RECORD_KDBT
	sizeof(mcodeb),		// RECORD_MCODEB
	sizeof(identb),		// RECORD_IDENTB
	sizeof(longspl),	// RECORD_LONGSPL
};
#define NUMRECORDS	(sizeof(s_cbRecSize)/sizeof(size_t))

short CKonsistenzTestKontext :: RecSize (long iRecNo)
{
	TX_ASSERT(0 <= iRecNo && NUMRECORDS > iRecNo);

//	return m_rDBD.RecSize(iRecNo) / sizeof (long);
	return s_cbRecSize[iRecNo];
}

void CKonsistenzTestKontext :: Out (char *pOut)
{
	if (m_pPrt) 
		m_pPrt -> Out(pOut);
	else {
	// wenn keine Protokollsenke gegeben ist, dann Standard verwenden
		TX_TRACE1("KONS: %s\r\n", pOut);
	}
}

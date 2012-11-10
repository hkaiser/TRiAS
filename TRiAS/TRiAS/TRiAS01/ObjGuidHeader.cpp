// @doc 
// @module ObjGuidHeader.cpp | Eindeutige Handles aus Header besorgen

#include "trias01p.hxx"
#include "obj32/trias321.h"

#include <ObjGuidHeader.h>
#include <UniqueHeader.h>
#include <NativePbd.h>

using namespace trias_nativepbd;
using namespace trias_nativeheader;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern char pDLLName[];

/////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const TCHAR g_cbObjectGuid[] = TEXT("ObjectGuidMCode");

/////////////////////////////////////////////////////////////////////////////
// Konstruktor
CObjGuidHeader::CObjGuidHeader(HPROJECT hPr)
	: m_hPr(hPr)
{
}

long CObjGuidHeader::GetObjGuidCode()
{
long lMCode = 0L;

	if (FAILED(GetPredefinedMCode (m_hPr, &lMCode, PREDEFINEDMCODE_ObjGuid))) {
	// MCode für diese GeoDB nur einmal lesen
	CDBHeader Hdr (m_hPr, g_cbObjectGuid);
	long lFlags = HEADER_SYSTEMRO;
	
		lMCode = Hdr.GetHeaderLong (0L, &lFlags);
		if (0L == lMCode) {
		CUniqueHeader Unique (m_hPr);

			lMCode = Unique.GetNextUniqueCode (CUniqueHeader::UNIQUETYPE_SYSMCODE);
			if (-1L != lMCode) {
            BOOL fIsCompound = TRUE;

                GetIsCompoundDB(m_hPr, &fIsCompound);
                if (fIsCompound) {
                // neuen Wert wegschreiben
				    Hdr.PutHeaderLong (lMCode, lFlags);

			    // in Pbd eintragen
			    HPROJECT hPrPbd = NULL;

				if (!GetRelatedProject (m_hPr, &hPrPbd))
					return 0L;

			    CNativePbdMerkmal PbdMCode (hPrPbd, lMCode, NULL, FALSE);
			    ResourceFile RF (pDLLName);
			    ResString resKT(ResID(IDS_OBJECTGUIDMCODE, &RF), _MAX_PATH);

				    PbdMCode.SetTyp (PBD_MERKMAL);
				    PbdMCode.SetSystem (TRUE);
				    PbdMCode.SetReadOnly (TRUE);
				    PbdMCode.SetKurzText (resKT);
				    PbdMCode.SetLangText (resKT);
				    PbdMCode.SaveInPBD();
			    }
            }
		}
		SetPredefinedMCode (m_hPr, lMCode, PREDEFINEDMCODE_ObjGuid);
	}
	return lMCode;
}

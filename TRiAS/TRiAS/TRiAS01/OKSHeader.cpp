// @doc 
// @module OKSHeader.cpp | Klasse, die MCode für OKS aus Header liest.

#include "trias01p.hxx"
#include "obj32/trias321.h"

#include <OKSHeader.h>
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
const TCHAR g_cbObjClassDescript[] = TEXT("ObjClassDescript");

/////////////////////////////////////////////////////////////////////////////
// 
COKSHeader::COKSHeader (HPROJECT hPr)
	: m_hPr(hPr)
{
}

long COKSHeader::GetOKSMCode()
{
CDBHeader Hdr (m_hPr, g_cbObjClassDescript);
long lFlags = HEADER_SYSTEMRO;
long lMCode = Hdr.GetHeaderLong (0L, &lFlags);

	if (0L == lMCode) {
	CUniqueHeader Unique (m_hPr);

		lMCode = Unique.GetNextUniqueCode (CUniqueHeader::UNIQUETYPE_SYSMCODE);
		if (-1L != lMCode) {
        BOOL fIsCompound = TRUE;

            GetIsCompoundDB(m_hPr, &fIsCompound);
			if (fIsCompound) {
                Hdr.PutHeaderLong (lMCode, lFlags);		// neuen Wert wegschreiben

		    // in Pbd eintragen
		    HPROJECT hPrPbd = NULL;

			    if (!GetRelatedProject (m_hPr, &hPrPbd))
				    return 0L;

		    CNativePbdMerkmal PbdMCode (hPrPbd, lMCode, NULL, FALSE);
		    ResourceFile RF (pDLLName);
		    ResString resKT(ResID(IDS_OBJCLASSDESC_KT, &RF), _MAX_PATH);

			    PbdMCode.SetTyp (PBD_MERKMAL);
			    PbdMCode.SetSystem (TRUE);
			    PbdMCode.SetReadOnly (TRUE);
			    PbdMCode.SetKurzText (resKT);
			    PbdMCode.SetLangText (resKT);
			    PbdMCode.SaveInPBD();
            }
		}
	}
	return lMCode;
}


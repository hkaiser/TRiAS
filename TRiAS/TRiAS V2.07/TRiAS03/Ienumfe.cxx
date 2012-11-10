/*
 * IENUMFE.CXX
 * Data Tranfer Object for Chapter 7
 *
 * IEnumFORMATETC implementation specifically for the Data Tranfer
 * objects.  This enumerator copies the state of the data list in
 * the data object and uses that to maintain what FORMATETCs it
 * knows.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "trias03p.hxx"

#include <pdataobj.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
 * CEnumFormatEtc::CEnumFormatEtc
 * CEnumFormatEtc::~CEnumFormatEtc
 *
 * Parameters (Constructor):
 *  punkRef         LPUNKNOWN to use for reference counting.
 */

CEnumFormatEtc::CEnumFormatEtc (void)
{
}


CEnumFormatEtc::~CEnumFormatEtc (void)
{
}

CEnumFormatEtc *CEnumFormatEtc::CreateInstance (ULONG cFE, LPFORMATETC prgFE)
{
	try {
	CEnumFormatEtc *pEnum = new CEnumFormatEtc();

		if (NULL == pEnum || !pEnum -> FInit (cFE, prgFE)) {
			DELETE_OBJ (pEnum);
			return NULL;
		}
		pEnum -> AddRef();
		return pEnum;
	} catch (...) {
		return NULL;
	}
}

bool CEnumFormatEtc::FInit (ULONG cFE, LPFORMATETC prgFE)
{
	for (UINT i = 0; i < cFE; i++)
		AddItem(prgFE[i]);

return true;
}


CEnumFormatEtc *CEnumFormatEtc::CreateInstance (const CRenderData &rRD)
{
	try {
	CEnumFormatEtc *pEnum = new CEnumFormatEtc();

		if (NULL == pEnum || !pEnum -> FInit (rRD)) {
			DELETE_OBJ (pEnum);
			return NULL;
		}
		pEnum -> AddRef();
		return pEnum;
	} catch (...) {
		return NULL;
	}
}

bool CEnumFormatEtc::FInit (const CRenderData &rRD)
{
CRenderData::const_iterator it = rRD.begin();

	for (UINT i = 0; it != rRD.end(); it++, i++)
		AddItem ((*it).m_fe);

return true;
}



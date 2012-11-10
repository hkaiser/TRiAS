/// New RFX_LongBinary() code///////////////////////////////////////////
/*
        Das am 8.8.1995 aus dem MSN erhaltene Modul bereinigt den Fehler
        beim Lesen von CLongBinary-Feldern (Ursache: SQLGetData kann nicht 
        mit Länge 0 zur Bestimmung der Feldgröße gerufen werden).
*/

#include "pheader.h"                    // vorübersetzter Header        
#include <blobrfx.hpp>                  // zugeh. Header

// Helper
BYTE _huge* AllocateLongBinaryData(CLongBinary& value, DWORD dwLength);

void RFX_LongBinary2(CFieldExchange* pFX, const char *szName,
		      CLongBinary& value, DWORD dwFetchChunkSize)
{
	ASSERT(AfxIsValidAddress(pFX, sizeof(CFieldExchange)));
	ASSERT(AfxIsValidString(szName));
	ASSERT(dwFetchChunkSize <= 0x8FFFF); // must be less that segment size

	RETCODE nRetCode;
	UINT nField;
	if (!pFX->IsFieldType(&nField))
	return;

	LONG* plLength = pFX->m_prs->GetFieldLength(pFX);
	switch (pFX->m_nOperation)
	{
		case CFieldExchange::Name:
		case CFieldExchange::IsFieldNull:
		case CFieldExchange::IsFieldDirty:
		case CFieldExchange::SetFieldDirty:
		case CFieldExchange::IsFieldNullable:
		pFX->Default(szName, &value, plLength, SQL_C_DEFAULT, 0, 0);
		return;

#ifdef _DEBUG
		case CFieldExchange::BindParam:
	// CLongBinary parameters are not supported
	ASSERT(FALSE);

		case CFieldExchange::BindFieldToColumn:
	// We use SQLGetData upon Fixup instead of SQLBindCol
		case CFieldExchange::MarkForAddNew:
		case CFieldExchange::MarkForUpdate:
	// We do not archive LongBinary values
		case CFieldExchange::StoreField:
		case CFieldExchange::LoadField:
	// We do not archive LongBinary values
#endif // _DEBUG
	default:
	return;

		case CFieldExchange::Fixup:
	{
		// Give empty buffer to find size of entire LongBinary
		DWORD dwAllocationSize = 0;
	    
	    ASSERT(nRetCode == SQL_SUCCESS || 
		   SQL_SUCCESS_WITH_INFO);

	    const BYTE _huge* lpLongBinary;
     
	    DWORD dwDataLength = 0;
	    do
	    {
		// Grow buffer as required
		dwAllocationSize += dwFetchChunkSize;
		lpLongBinary = AllocateLongBinaryData(value, dwAllocationSize);// locks memory
     

		// Ignore expected data truncated warnings
		AFX_SQL_ASYNC(pFX->m_prs, ::SQLGetData(pFX->m_prs->m_hstmt,
		    (unsigned short int)nField, SQL_C_BINARY,
		    ((UCHAR _huge *)lpLongBinary + dwDataLength), 
		    dwFetchChunkSize, plLength));

		if (!pFX->m_prs->Check(nRetCode))
				pFX->m_prs->ThrowDBException(nRetCode);
		if (nRetCode == SQL_NO_DATA_FOUND || *plLength == SQL_NULL_DATA) 
			{
				pFX->m_prs->SetFieldFlags(nField,
						                  AFX_SQL_FIELD_FLAG_NULL,
					                      pFX->m_nFieldType);
			    *plLength = SQL_NULL_DATA;
			    value.m_dwDataLength=0;
			    ::GlobalUnlock(value.m_hData);
                ::GlobalFree(value.m_hData);
                value.m_hData=NULL;
			    return;
		    }
     
		// not null and successful retrieval of data            
		if (*plLength!=SQL_NO_TOTAL && ((DWORD)*plLength)<dwFetchChunkSize)
		    dwDataLength += *plLength;
		else
		    dwDataLength += dwFetchChunkSize;

		} while (nRetCode == SQL_SUCCESS_WITH_INFO); //Should be data truncated

	    //Realloc memory to exact size
			::GlobalUnlock(value.m_hData);
			value.m_hData = ::GlobalReAlloc(value.m_hData, dwDataLength, GMEM_MOVEABLE);
			value.m_dwDataLength = dwDataLength;
	  }
	  return;
	case CFieldExchange::NameValue:
	    if (pFX->m_prs->IsFieldFlagDirty(nField, pFX->m_nFieldType))
	    {
		
		#ifdef _WIN32
		 {
		   CString szTempName=szName;
		   pFX->m_prs->m_pDatabase->ReplaceBrackets(szTempName.GetBuffer(0));
		   szTempName.ReleaseBuffer();
		   *pFX->m_pstr +=szTempName;
		 }
		    
		#else
		  *pFX->m_pstr += pFX->m_prs->m_pDatabase->QuoteName(szName);
		#endif

		*pFX->m_pstr += "=";
	    }

	// Fall through
	case CFieldExchange::Value:
	if (pFX->m_prs->IsFieldFlagDirty(nField, pFX->m_nFieldType))
	    {
	    // If user marked column NULL, reflect this in length
	    if (pFX->m_prs->IsFieldFlagNull(nField,
		pFX->m_nFieldType))
	    *plLength = SQL_NULL_DATA;
	    else
	    {
		// Indicate data will be sent after SQLExecute
		*plLength = SQL_DATA_AT_EXEC;
	    }

	// If optimizing for bulk add, just set length.
	if(!(pFX->m_prs->m_dwOptions & CRecordset::optimizeBulkAdd))
	{
	    *pFX->m_pstr += "?";
	    *pFX->m_pstr += pFX->m_lpszSeparator;
	    pFX->m_nParamFields++;
	    AFX_SQL_SYNC(::SQLSetParam(pFX->m_hstmt,
		(unsigned short int)pFX->m_nParamFields, SQL_C_DEFAULT,
		// Get actual SQL type - may differ from CType (e.g. DECIMAL)
	(short int)pFX->GetColumnType(nField), value.m_dwDataLength, 0, 
		&value, plLength));
	if (nRetCode != SQL_SUCCESS)
	    pFX->m_prs->ThrowDBException(nRetCode, pFX->m_hstmt);
     }
    }
    return;

	case CFieldExchange::SetFieldNull:
	if ((pFX->m_pvField == NULL &&
	     pFX->m_nFieldType == CFieldExchange::outputColumn) ||
	    pFX->m_pvField == &value)
	{
	    if (pFX->m_bField)
	    {
	    // Mark fields null
	    pFX->m_prs->SetFieldFlags(nField,
		    AFX_SQL_FIELD_FLAG_NULL,
		    pFX->m_nFieldType);
	    value.m_dwDataLength = 0;
	    *plLength = SQL_NULL_DATA;
	}
	else
	{
	    pFX->m_prs->ClearFieldFlags(nField,
	    AFX_SQL_FIELD_FLAG_NULL,
	    pFX->m_nFieldType);
	    *plLength = SQL_DATA_AT_EXEC;
	}
#ifdef _DEBUG
	pFX->m_bFieldFound = TRUE;
#endif // _DEBUG
	}
	return;

	case CFieldExchange::GetFieldInfoValue:
	    if (pFX->m_pfi->pv == &value)
	    {
	    pFX->m_pfi->nField = nField-1;
	    goto LFieldFound;
	    }
	    return;

	case CFieldExchange::GetFieldInfoOrdinal:
	    if (nField-1 == pFX->m_pfi->nField)
	    {
	LFieldFound:
	    pFX->m_pfi->nDataType = AFX_RFX_LONGBINARY;
	    pFX->m_pfi->strName = szName;
	    pFX->m_pfi->pv = &value;
	    pFX->m_pfi->dwSize = sizeof(value);
	    // Make sure field found only once
	    ASSERT(pFX->m_bFieldFound == FALSE);
	    pFX->m_bFieldFound = TRUE;
	    }
	    return;
   }
}


BYTE _huge* AllocateLongBinaryData(CLongBinary& value, DWORD dwLength)
{
	// Allocate or ReAllocate memory as required
	if (value.m_hData == NULL)
	value.m_hData = ::GlobalAlloc(GMEM_MOVEABLE, dwLength);
	else if (::GlobalSize(value.m_hData) < dwLength)
	value.m_hData = ::GlobalReAlloc(value.m_hData, dwLength,
							GMEM_MOVEABLE);

	if (value.m_hData == NULL)
	AfxThrowMemoryException();

	value.m_dwDataLength = dwLength;

	// Lock down the memory
	BYTE _huge * lpLongBinary;
	lpLongBinary = (BYTE _huge *)::GlobalLock(value.m_hData);
	if (lpLongBinary == NULL)
	{
	::GlobalFree(value.m_hData);
	value.m_hData = NULL;
	AfxThrowMemoryException();
	}
 
 return lpLongBinary;
}





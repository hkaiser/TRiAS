// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.07.2002 14:56:14 
//
// @doc
// @module ConvertGuid.cpp | Definition of the <c CConvertGuid> class

#include "stdafx.h"

#include <Atl/Ciid.h>

#include "CvrtGuid.h"
#include "ConvertGuid.h"

/////////////////////////////////////////////////////////////////////////////
// CConvertGuid

STDMETHODIMP CConvertGuid::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IConvertGuid
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CConvertGuid::CreateGuid32String(BSTR *pbstrGuidStr)
{
	if (NULL == pbstrGuidStr)
		return E_POINTER;
	*pbstrGuidStr = NULL;

GUID Guid;

	RETURN_FAILED_HRESULT(CoCreateGuid(&Guid));
	RETURN_FAILED_HRESULT(GuidToGuid32String(Guid, pbstrGuidStr));
	return S_OK;
}

STDMETHODIMP CConvertGuid::GuidToGuid32String(BSTR bstrGuid, BSTR *pbstrGuidStr)
{
	if (NULL == pbstrGuidStr)
		return E_POINTER;
	*pbstrGuidStr = NULL;

CIID Guid(bstrGuid, CIID::INITCIID_InitFromGuid);

	return GuidToGuid32String(Guid, pbstrGuidStr);
}

STDMETHODIMP CConvertGuid::Guid32StringToGuid(BSTR bstrGuidStr, BSTR *pbstrGuid)
{
	if (NULL == pbstrGuid)
		return E_POINTER;
	*pbstrGuid = NULL;

CIID Guid;

	RETURN_FAILED_HRESULT(Guid32StringToGuid(bstrGuidStr, &Guid));
	*pbstrGuid = CComBSTR(Guid).Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Helperroutinen
HRESULT CConvertGuid::GuidToGuid32String(REFGUID rGuid, BSTR *pbstrGuidStr)
{
	_ASSERTE(NULL != pbstrGuidStr);

wchar_t wBuffer[40];
CComBSTR bstr;

	bstr = _ui64tow(((unsigned __int64 *)&rGuid)[0], wBuffer, 32);

int iLen = bstr.Length();

	if (iLen < 13) {
	CComBSTR bstrT;

		while (iLen++ < 13) 
			bstrT.Append(L"0");
		bstrT.AppendBSTR(bstr);
		bstr = bstrT;
	}

CComBSTR bstr2;

	bstr2 = _ui64tow(((unsigned __int64 *)&rGuid)[1], wBuffer, 32);
	iLen = bstr2.Length();

	if (iLen < 13) {
	CComBSTR bstrT;

		while (iLen++ < 13) 
			bstrT.Append(L"0");
		bstrT.AppendBSTR(bstr2);
		bstr.AppendBSTR(bstrT);
	}
	else
		bstr.AppendBSTR(bstr2);

	*pbstrGuidStr = bstr.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// String in Radix 32 --> unsigend __int64
#include <errno.h>

#define FL_UNSIGNED   1       /* strtoul called */
#define FL_NEG        2       /* negative sign found */
#define FL_OVERFLOW   4       /* overflow occured */
#define FL_READDIGIT  8       /* we've read at least one correct digit */

unsigned __int64 __cdecl wcstoxl32 (
        const wchar_t *nptr,
        const wchar_t **endptr
        )
{
        const wchar_t *p;
        wchar_t c;
        unsigned __int64 number;
        unsigned digval;
        unsigned __int64 maxval;
		int flags = FL_UNSIGNED;

        p = nptr;           /* p is our scanning pointer */
        number = 0;         /* start with zero */

        c = *p++;           /* read char */
        while (iswspace(c))
            c = *p++;       /* skip whitespace */

        if (c == '-') {
            flags |= FL_NEG;    /* remember minus sign */
            c = *p++;
        }
        else if (c == '+')
            c = *p++;       /* skip sign */

        /* if our number exceeds this, we will overflow on multiply */
        maxval = _UI64_MAX / 32;


        for (;;) {  /* exit in middle of loop */
            /* convert c to value */
            if (iswdigit(c))
                digval = c - L'0';
            else if (iswalpha(c))
                digval = towupper(c) - L'A' + 10;
            else
                break;
            if (digval >= (unsigned)32)
                break;      /* exit loop if bad digit found */

            /* record the fact we have read one digit */
            flags |= FL_READDIGIT;

            /* we now need to compute number = number * base + digval,
               but we need to know if overflow occured.  This requires
               a tricky pre-check. */

            if (number < maxval || (number == maxval &&
				(unsigned long)digval <= _UI64_MAX % 32)) {
                /* we won't overflow, go ahead and multiply */
                number = number * 32 + digval;
            }
            else {
                /* we would have overflowed -- set the overflow flag */
                flags |= FL_OVERFLOW;
            }

            c = *p++;       /* read next digit */
        }

        --p;                /* point to place that stopped scan */

        if (!(flags & FL_READDIGIT)) {
            /* no number there; return 0 and point to beginning of
               string */
            if (endptr)
                /* store beginning of string in endptr later on */
                p = nptr;
            number = 0;        /* return 0 */
        }
        else if ( (flags & FL_OVERFLOW) ||
              ( !(flags & FL_UNSIGNED) &&
                ( ( (flags & FL_NEG) && (number > -_I64_MIN) ) ||
                  ( !(flags & FL_NEG) && (number > _I64_MAX) ) ) ) )
        {
            /* overflow or signed overflow occurred */
            errno = ERANGE;
            if ( flags & FL_UNSIGNED )
                number = _UI64_MAX;
            else if (flags & FL_NEG )
                number = (unsigned __int64)(-_I64_MIN);
            else
                number = _I64_MAX;
        }

        if (endptr != NULL)
            /* store pointer to char that stopped the scan */
            *endptr = p;

        if (flags & FL_NEG)
            /* negate result if there was a neg sign */
            number = (unsigned __int64)(-(__int64)number);

        return number;          /* done. */
}

HRESULT CConvertGuid::Guid32StringToGuid(BSTR bstrGuidStr, GUID *pGuid)
{
	_ASSERTE(NULL != pGuid);

CComBSTR bstr (13, bstrGuidStr);

	((unsigned __int64 *)pGuid)[0] = wcstoxl32(bstr, NULL);
	((unsigned __int64 *)pGuid)[1] = wcstoxl32(&bstrGuidStr[13], NULL);
	return S_OK;
}

// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "StdAfx.h"
#include <Picture.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CPicture properties

long CPicture::GetHandle()
{
	long result;
	GetProperty(0x0, VT_I4, (void*)&result);
	return result;
}

long CPicture::GetHPal()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CPicture::SetHPal(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

short CPicture::GetType()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

long CPicture::GetWidth()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

long CPicture::GetHeight()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

/////////////////////////////////////////////////////////////////////////////
// CPicture operations

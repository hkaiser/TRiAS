// EDBS_Geometrie.cpp : Implementierung von CEDBS_Geometrie
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Geometrie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Geometrie

CEDBS_Geometrie::CEDBS_Geometrie( void )
{
	miDimension = 0;
	dblRA = 0;
	dblHA = 0;
	dblRE = 0;
	dblHE = 0;
	lTT = 0;
	padblR = NULL;
	padblH = NULL;
}

CEDBS_Geometrie::~CEDBS_Geometrie( void )
{
	if( padblR )
		delete padblR;
	if( padblH )
		delete padblH;
}

long CEDBS_Geometrie::Dim( int iDimension )
{
	miDimension = iDimension;
	padblR = new double[iDimension];
	memset(padblR,0,miDimension * sizeof(double));
	padblH = new double[iDimension];
	memset(padblH,0,miDimension * sizeof(double));
	return 0;
}

STDMETHODIMP CEDBS_Geometrie::get_Geometrieart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mbGeometrieart;

	return S_OK;
}

STDMETHODIMP CEDBS_Geometrie::get_HA(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = dblHA;

	return S_OK;
}

STDMETHODIMP CEDBS_Geometrie::get_HE(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = dblHE;

	return S_OK;
}

STDMETHODIMP CEDBS_Geometrie::get_RA(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = dblRA;

	return S_OK;
}

STDMETHODIMP CEDBS_Geometrie::get_RE(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = dblRE;

	return S_OK;
}

STDMETHODIMP CEDBS_Geometrie::get_AnzahlKoordinaten(int *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = miDimension + 2;

	return S_OK;
}

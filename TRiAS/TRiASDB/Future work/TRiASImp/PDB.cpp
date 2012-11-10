//	Declaration der PDB
//
//	Verwaltung der Klassenidentifikatoren und Merkmalsidentifikatoren.

#include "StdAfx.h"

#include "PDB.h"

CPDB::CPDB()
{	Reset();
}

CPDB::~CPDB()
{	Reset();
}

void CPDB::Reset()
{
	m_mapIdKurzText.RemoveAll();
	m_mapIdLangText.RemoveAll();
	m_mapMkKurzText.RemoveAll();
	m_mapMkLangText.RemoveAll();
	m_lIdBase = 16;
	m_lMkBase = 16;
}

BOOL CPDB::GetIdentTexte( const char* key, CString& kurz, CString& lang )
{
	BOOL	result = FALSE;

	ASSERT( NULL != key );

	try {

		if (( NULL != key ) && ( *key != '\0' ))
		{
			result = m_mapIdKurzText.Lookup( key, kurz );
			if ( result )
				m_mapIdLangText.Lookup( key, lang );
		}
	}
	catch ( CMemoryException* e )
	{
		AfxMessageBox( g_cbNoMemory );
		e;
//		e -> Delete();
	}

	return result;
}

BOOL CPDB::GetMerkmalTexte( const char* key, CString& kurz, CString& lang )
{
	BOOL	result = FALSE;

	ASSERT( NULL != key );

	try {

		if (( NULL != key ) && ( *key != '\0' ))
		{
			result = m_mapMkKurzText.Lookup( key, kurz );
			if ( result )
				m_mapMkLangText.Lookup( key, lang );
		}
	}
	catch ( CMemoryException* e )
	{
		AfxMessageBox( g_cbNoMemory );
		e;
//		e -> Delete();
	}

	return result;
}

BOOL CPDB::SetIdentTexte( const char* key, const char* kurz, const char* lang )
{
	BOOL	result = FALSE;

	ASSERT( NULL != key );
	ASSERT( NULL != kurz );
	ASSERT( NULL != lang );

	try {

		if (( NULL != key ) && ( *key != '\0' ) &&
			( NULL != kurz ) && ( *kurz != '\0' ))
		{
			m_mapIdKurzText.SetAt( key, kurz );

			if (( NULL != lang ) && ( *lang != '\0' ))
				m_mapIdLangText.SetAt( key, lang );

			result = TRUE;
		}
	}
	catch ( CMemoryException* e )
	{
		AfxMessageBox( g_cbNoMemory );
		e;
//		e -> Delete();
	}

	return result;
}

BOOL CPDB::SetMerkmalTexte( const char* key, const char* kurz, const char* lang )
{
	BOOL	result = FALSE;

	ASSERT( NULL != key );
	ASSERT( NULL != kurz );
	ASSERT( NULL != lang );

	try {

		if (( NULL != key ) && ( *key != '\0' ) &&
			( NULL != kurz ) && ( *kurz != '\0' ))
		{
			m_mapMkKurzText.SetAt( key, kurz );

			if (( NULL != lang ) && ( *lang != '\0' ))
				m_mapMkLangText.SetAt( key, lang );

			result = TRUE;
		}
	}
	catch ( CMemoryException* e )
	{
		AfxMessageBox( g_cbNoMemory );
		e;
//		e -> Delete();
	}

	return result;
}

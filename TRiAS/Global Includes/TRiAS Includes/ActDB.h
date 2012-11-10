// @doc
// @module ActDB.h | Declaration of the <c CActDB> and <c CAccessDB> classes

#if !defined(_ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_)
#define _ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Wrapperklasse zum aktivieren einer Datenbank

#if !defined(ASSERT)
#define ASSERT(x)	TX_ASSERT(x)
#endif // !ASSERT

class CActDB
{
protected:
	HPROJECT m_hPr;
	HPROJECT m_hThisPr;

public:
	CActDB (HPROJECT hPr)
	{
		m_hThisPr = hPr;
		m_hPr = z_activate (hPr);
	}
	~CActDB (void)
	{
		if (NULL != m_hPr) {	// nur wenn noch nicht explizit abgemeldet
		HPROJECT hPr = z_activate (m_hPr);

//			ASSERT(hPr == m_hThisPr);
			Reset();		// nur einmal machen
		}
	}
	void ReActivate() { z_activate (m_hThisPr); }	// wieder aktivieren (für alle Fälle)
	void Reset() { m_hPr = NULL; }				// Rücksetzen ohne Rückschaltung
	bool operator !() { return (NULL == m_hThisPr) ? true : false; }

	HPROJECT GetOldDB() { return m_hPr; }
};

/////////////////////////////////////////////////////////////////////////////
// DB aktiv schalten und zusätzlich die Zugriffsrechte auf voll schalten
class CAccessDB :
	public CActDB
{
public:
	CAccessDB (HPROJECT hPr) : CActDB(hPr)
	{
		z_access (hPr, Z_ALL|Z_RDWR);
	}
	~CAccessDB (void)
	{
		z_raccess (m_hThisPr, Z_ALL);
	}
};

#endif // !defined(_ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_)

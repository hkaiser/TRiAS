// @doc
// @module ActDB.h | Declaration of the <c CActDB> and <c CAccessDB> classes

#if !defined(_ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_)
#define _ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// Wrapperklasse zum aktivieren einer Datenbank

class CActDB
{
private:
	CActDB();		// do not use directly

protected:
	HPROJECT m_hThisPr;
	HPROJECT m_hPr;

public:
	explicit CActDB (HPROJECT hPr) :
		m_hThisPr(hPr), m_hPr(z_activate (hPr))
	{
	}
	~CActDB (void)
	{
		if (NULL != m_hThisPr) {	// nur wenn noch nicht explizit abgemeldet
		HPROJECT hPr = z_activate (m_hPr);

			_ASSERTE(hPr == m_hThisPr);
			m_hThisPr = NULL;		// nur einmal machen
		}
	}	//lint -esym(1740, m_hPr)
	void ReActivate() { z_activate (m_hThisPr); /*lint !e534*/ }	// wieder aktivieren (für alle Fälle)
	void Reset() { m_hThisPr = NULL; }				// Rücksetzen ohne Rückschaltung
	bool operator !() { return (NULL != m_hThisPr) ? true : false; }
};

/////////////////////////////////////////////////////////////////////////////
// DB aktiv schalten und zusätzlich die Zugriffsrechte auf voll schalten
class CAccessDB :
	public CActDB
{
private:
	CAccessDB();		// do not use directly

public:
	explicit CAccessDB (HPROJECT hPr) : CActDB(hPr)
	{
		z_access (hPr, Z_ALL|Z_RDWR);	//lint !e569, !e534
	}
	~CAccessDB (void)
	{
		z_raccess (m_hThisPr, Z_ALL);	//lint !e569, !e534
	}
};

#endif // !defined(_ACTDB_H__0F223934_491A_11d1_96D7_00A024D6F582__INCLUDED_)

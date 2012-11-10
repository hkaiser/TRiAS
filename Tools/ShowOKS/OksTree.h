// TRiAS Objektklassenschlüssel 
// File: OksTree.h

#if !defined(_OKSTREE_H)
#define _OKSTREE_H

#include <ospace/stlex/vtree.h>
#include <ospace/stlex/ternary_function.h>
#if !defined(OS_NO_STREAM_SUPPORT)
#include <ospace/uss/stlex/vtree.h>
#endif // OS_NO_STREAM_SUPPORT

extern const char OKS_ROOT_NAME[];

///////////////////////////////////////////////////////////////////////////////
// Ein Element, welches im oks_tree gespeichert wird
class COksElement
{
public:
	enum NODETYPE {
		NODETYPE_Normal = 0,	// normale Hierarchie
		NODETYPE_Special = 1,	// parallele Hierarchien
	};

	typedef COksElement self;

public:
	COksElement (os_string strDesc = OKS_ROOT_NAME, int iCode = 1, int iDigits = 0) :
		m_strText(strDesc), m_iCode (iCode), m_iDigits(iDigits),
		m_rgType(iDigits > 0 ? NODETYPE_Special : NODETYPE_Normal) {}

	COksElement (const COksElement &rOks)
		{
			m_iCode = rOks.GetCode();
			m_strText = rOks.GetText();
			m_rgType = rOks.GetType();
			m_iDigits = rOks.GetNumDigits();
		}

	COksElement & operator= (const COksElement &rhs)
		{
			if (this != &rhs) {
				m_iCode = rhs.GetCode();
				m_strText = rhs.GetText();
				m_rgType = rhs.GetType();
				m_iDigits = rhs.GetNumDigits();
			}
			return *this;
		}

	int GetCode() const { return m_iCode; }
	const os_string & GetText() const { return m_strText; }
	NODETYPE GetType() const { return m_rgType; }
	int GetNumDigits() const { return m_iDigits; }

private:
	int m_iCode;			// Laufender Code innerhal dieses Levels
	os_string m_strText;	// zugeordneter Beschreibungstext
	NODETYPE m_rgType;		// Typ der dranhängenden Nodes
	int m_iDigits;			// nur bei NODETYPE_Special: Anzahl der Digits dieser
							// parallelen Hierarchie
#if !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream& stream, const self& l);
	friend void os_read (os_bstream& stream, self& l);
#endif // OS_NO_STREAM_SUPPORT
};

#if !defined(OS_NO_STREAM_SUPPORT)
OS_CLASS(COksElement);
OS_STREAM_OPERATORS(COksElement);
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Die eigentliche OKS-Datenstruktur
class oks_tree :
	public vtree<COksElement>
{
public:
	typedef vtree<COksElement>::node oks_node;
	typedef vtree<COksElement>::ch_iter oks_ch_iter;
	typedef vtree<COksElement>::up_iter oks_up_iter;

	class oks_callback :
		public ternary_function<int, oks_ch_iter, const os_string, bool>
	{
	public:
		result_type operator() (first_argument_type, second_argument_type, third_argument_type);
	};

public:
	oks_tree() : vtree<COksElement> (COksElement()) {}

	oks_ch_iter insert (const char *pcOKS, const char *pcText, int iDigits = 0, int iLeading = 0)
		{ return insert (&root(), pcOKS, pcText, iDigits, iLeading); }
	bool erase (const char *pOKS);
	bool generate_text (const char *pcOKS, os_string &rResult)
		{ return generate_text (&root(), pcOKS, rResult); }

// Iteratoren des ersten bzw. letzten(+1) Knotens
	oks_ch_iter begin() { return root().ch_begin(); }
	oks_ch_iter end() { return root().ch_end(); }

	void erase (void) { vtree<COksElement>::erase(); }

protected:
	oks_ch_iter insert (oks_node *pNode, const char *pOKS, const char *pText, int iDigits, int iLeading);
	bool generate_text (oks_node *pNode, const char *pOKS, os_string &rResult);

friend int CountDigits (oks_ch_iter it);
friend int CountAllDigits (oks_ch_iter it);

///////////////////////////////////////////////////////////////////////////////
// Debug support
#if defined(_DEBUG)
public:
	void DumpAll (void);
#endif // _DEBUG
};

///////////////////////////////////////////////////////////////////////////////
// Traversion algorithms

// Konvertieren der übergebenen Zahl in eine Folge von HexDigits
inline os_string ToHex (long lCode)
{
char cbBuffer[10];

	ltoa (lCode, cbBuffer, 16);

os_string str (cbBuffer);

	return str;
}

template<class FwIt, class pred>
bool __oks_traverseNormalNode (FwIt, int, os_string, int, os_string, pred);
template<class FwIt, class pred>
bool __oks_traverseSpecialNode (FwIt, int, os_string, os_string, pred);

template<class FwIt, class pred>
bool __oks_traverse (FwIt it, int iLevel, os_string strPre, int iCode, os_string strPost, pred cb)
{
	if (COksElement::NODETYPE_Normal == it -> value.GetType()) 
		return __oks_traverseNormalNode (it, iLevel, strPre, iCode, strPost, cb);
	else
		return __oks_traverseSpecialNode (it, iLevel, strPre, strPost, cb);
}

template<class FwIt, class pred>
bool __oks_traverseNormalNode (FwIt it, int iLevel, os_string strPre, int iCode, os_string strPost, pred cb)
{
	{
	os_string strHex (ToHex(iCode));

		strPre += strHex;
		if (strPost.size() > 0)
			strPost = strPost.substr(strHex.size(), os_npos);

	os_string str (strPre + strPost + " " + it -> value.GetText());

		if (!cb (iLevel, it, str))
			return false;	// nicht weitermachen
	}

	for (FwIt chit = it -> ch_begin(); chit != it -> ch_end(); ++chit)
	{
		if (!__oks_traverse (chit, iLevel+1, strPre, chit -> value.GetCode(), strPost, cb))
			return false;
	}
	return true;
}

template<class FwIt, class pred>
bool __oks_traverseSpecialNode (FwIt it, int iLevel, os_string strPre, os_string strPost, pred cb)
{
	/*if (iLevel > 0)*/ {
	int iNumDigits = it -> value.GetNumDigits();
	int iCntDigits = CountDigits (it);
	int iAllDigits = CountAllDigits (it);

		strPre += os_string(iCntDigits, '.');

		strPost = os_string(iNumDigits, '0') +
				  os_string(iAllDigits-iNumDigits-iCntDigits, '.');

	os_string str (strPre + strPost + " " + it -> value.GetText());

		if (!cb (iLevel, it, str))
			return false;	// nicht weitermachen
	}

	for (FwIt chit = it -> ch_begin(); chit != it -> ch_end(); ++chit)
	{
		if (!__oks_traverse (chit, iLevel+1, strPre, chit -> value.GetCode(), strPost, cb))
			return false;
	}
	return true;
}

template<class FwIt, class pred>
bool oks_traverse (FwIt itbegin, FwIt itend, pred cb) 
{ 
	for (FwIt it = itbegin; it != itend; ++it) {
		if (!__oks_traverse (it, 0, "", it -> value.GetCode(), "", cb))
			return false;
	}
	return true;
}


#endif // _OKSTREE_H

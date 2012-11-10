// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 31.05.99 22:38:03 
//
// @doc
// @module ExportAsXml.h | TXI/TXM-Export als XML-Datei

#if !defined(_EXPORTASXML_H__B6576E30_1798_11D3_94DF_0080C786297B__INCLUDED_)
#define _EXPORTASXML_H__B6576E30_1798_11D3_94DF_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <FormatString.h>

///////////////////////////////////////////////////////////////////////////////
// XML Sonderzeichen ersetzen
inline
os_string EncodeXML (os_string str)
{
os_string::size_type iPos = 0;

	while ((iPos = str.find_first_of ('&', iPos)) != os_npos) {
		str.replace (iPos, 1, "&amp;");
		iPos += 3;
	}

	iPos = 0;
	while ((iPos = str.find_first_of ('<', iPos)) != os_npos) {
		str.replace (iPos, 1, "&lt;");
		iPos += 2;
	}

	iPos = 0;
	while ((iPos = str.find_first_of ('>', iPos)) != os_npos) {
		str.replace (iPos, 1, "&gt;");
		iPos += 2;
	}
	return str;
}

inline
os_string EncodeXML (LPCSTR pcText)
{
	return EncodeXML (os_string(pcText));
}

///////////////////////////////////////////////////////////////////////////////
// ein Attribut
class CXMLAttribute
{
public:
	CXMLAttribute (LPCSTR pcKey, LPCSTR pcVal, ...) 
		: m_strKey (pcKey)
	{
	va_list argList;

		va_start(argList, pcVal);
		FormatV(m_strVal, pcVal, argList);
		va_end(argList);
	}
	operator os_string()
	{
	os_string strT;

		Format (strT, " %s=\"%s\"", EncodeXML(m_strKey).c_str(), EncodeXML(m_strVal).c_str());
		return strT;
	}

private:
	os_string m_strKey;
	os_string m_strVal;
};

///////////////////////////////////////////////////////////////////////////////
// ein allgemeines Element
class CXMLElement
{
public:
	CXMLElement(int fh, bool fIncrIndent = true) 
		: m_fh(fh), m_fIncrIndent(fIncrIndent) 
	{ 
		if (m_fIncrIndent) m_iIndent++; 
	}
	~CXMLElement() 
	{ 
		if (m_fIncrIndent) m_iIndent--; 
	}

	void Output (LPCSTR pcFmt, ...)
	{
	char *pOut = (char *)_alloca(strlen(pcFmt)+_MAX_PATH);
	va_list argList;

		va_start(argList, pcFmt);
		wvsprintf (pOut, pcFmt, argList);
		for (int i = 0; i < m_iIndent; i++)
			_lwrite (m_fh, "\t", 1);
		_lwrite (m_fh, pOut, strlen(pOut)); 
	}

protected:
	static int m_iIndent;

private:
	int m_fh;
	bool m_fIncrIndent;
};

///////////////////////////////////////////////////////////////////////////////
// Ein XML-Node
class CXMLNode :
	public CXMLElement
{
public:
	CXMLNode (int fh, LPCSTR pcTag, CXMLAttribute &rAttr)
		: CXMLElement(fh), m_strTag(pcTag)
	{
		Output ("<%s%s>\r\n", m_strTag.c_str(), os_string(rAttr).c_str());
	}
	CXMLNode (int fh, LPCSTR pcTag)
		: CXMLElement(fh), m_strTag(pcTag)
	{
		Output ("<%s>\r\n", m_strTag.c_str());
	}
	~CXMLNode()
	{
		Output ("</%s>\r\n", m_strTag.c_str());
	}

private:
	os_string m_strTag;
};

///////////////////////////////////////////////////////////////////////////////
// Ein Textelement
class CXMLTextEx :
	public CXMLElement
{
public:
	CXMLTextEx (int fh, LPCSTR pcTag, LPCSTR pcText, ...)
		: CXMLElement(fh)
	{
	va_list argList;
	os_string strT;

		va_start(argList, pcText);
		FormatV(strT, pcText, argList);
		va_end(argList);
		Output ("<%s>%s</%s>\r\n", pcTag, EncodeXML(strT).c_str(), pcTag);
	}
};

class CXMLText :
	public CXMLElement
{
public:
	CXMLText (int fh, LPCSTR pcTag, LPCSTR pcText)
		: CXMLElement(fh)
	{
		Output ("<%s>%s</%s>\r\n", pcTag, EncodeXML(pcText).c_str(), pcTag);
	}
	CXMLText (int fh, LPCSTR pcTag, LPCSTR pcText, CXMLAttribute &rAttr)
		: CXMLElement(fh)
	{
		Output ("<%s%s>%s</%s>\r\n", pcTag, os_string(rAttr).c_str(), EncodeXML(pcText).c_str(), pcTag);
	}
};

///////////////////////////////////////////////////////////////////////////////
// ein Kommentar
class CXMLComment :
	public CXMLElement
{
public:
	CXMLComment (int fh, LPCSTR pcComment) :
		CXMLElement(fh, false)
	{
		Output ("<!-- %s -->\r\n", EncodeXML(pcComment).c_str());
	}
	~CXMLComment()
	{
	}
};

///////////////////////////////////////////////////////////////////////////////
// das auszugebende Dokument
class CXMLDocument :
	public CXMLElement
{
public:
	CXMLDocument (int fh)
		: CXMLElement(fh)
	{
		m_iIndent = -1;
		Output ("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n");
	}
	~CXMLDocument()
	{
		_ASSERTE(-1 == m_iIndent);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Einfach alles ausgeben
class CXMLRawData
{
public:
	CXMLRawData (int fh, LPCSTR pLines[])
	{
		for (LPCSTR *p = pLines; *p != NULL; p++)
			_lwrite (fh, *p, strlen(*p)); 
	}
};

#endif // !defined(_EXPORTASXML_H__B6576E30_1798_11D3_94DF_0080C786297B__INCLUDED_)

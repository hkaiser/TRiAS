// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/08/1998 12:34:46 PM
//
// @doc
// @module ResString.h | ResourceString aus CommonVu

#if !defined(_RESSTRING_H__7AEE4865_8E6C_11D2_9EFC_006008447800__INCLUDED_)
#define _RESSTRING_H__7AEE4865_8E6C_11D2_9EFC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
//
class ResourceFile
{
private:
	HINSTANCE hLib;

public:
	ResourceFile (const char *);
	~ResourceFile (void);

	HINSTANCE Handle() { return hLib; }
	friend class ResID;
};

class CvID {
private:
	unsigned int id;
	const char *str;

friend inline BOOL operator== (unsigned int n, CvID id) { return id.operator== (n); }
friend inline BOOL operator== (const char *s, CvID id) { return id.operator== (s); }

public:
	CvID (unsigned int i) { id = i; str = 0; }
	CvID (const char *);

	operator unsigned int (void) { return id; }
	operator const char * (void) { return str; }
	BOOL operator== (unsigned int i) { return id == i; }
	BOOL operator== (const char *s) { return id == CvID(s); }
	BOOL operator== (CvID &i) { return id == i.id; }
};

class ResID : 
	public CvID
{
private:
	HINSTANCE src;
	
public:
	ResID (unsigned int i) : CvID(i) { src = NULL; }
	ResID (unsigned int i, ResourceFile *source = NULL) : CvID(i) 
	{
		if (source)
			src = source -> Handle();
		else
			src = 0;
	}
	ResID (const char *s, ResourceFile *source = NULL) : CvID(s)
	{
		if (source)
			src = source -> Handle();
		else
			src = 0;
	}
	HINSTANCE Handle (void) { return src; }
};

///////////////////////////////////////////////////////////////////////////////
//
class ResString
{
private:
	int	length;
	char *string;

public:
	ResString (unsigned int, unsigned int len);
	ResString (ResID, unsigned int len);
	ResString (const ResString &);

	ResString &operator= (const ResString&);
	const char *Addr(void) { return string; }
	int	Len (void) { return length; }
	operator const char* (void) { return string; }

	~ResString (void);
};

#endif // !defined(_RESSTRING_H__7AEE4865_8E6C_11D2_9EFC_006008447800__INCLUDED_)

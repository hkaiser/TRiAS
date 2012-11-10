// Konvertierung ebHSUB<-->String ---------------------------------------------
// File: EBARGS.H

#if !defined(_EBARGS_H)
#define _EBARGS_H

///////////////////////////////////////////////////////////////////////////////
// Abfragen eines Strings -----------------------------------------------------
class CStrArg {
private:
	ebHSUB m_hStr;
	ebHTHREAD m_hThread;
	LPCSTR m_pcStr;

public:
	CStrArg (ebHTHREAD hThread, ebARGS lpArgs, int iArg) 
			: m_hThread(hThread), m_pcStr(NULL), m_hStr(ebGetString (lpArgs, iArg)) 
		{ if (m_hStr) m_pcStr = ebLockString (m_hThread, m_hStr); }
	CStrArg (ebHTHREAD hThread, ebARGS lpArgs, int iArg, int iNumArgs) 
			: m_hThread(hThread), m_hStr(NULL), m_pcStr(NULL) 
		{ if (iNumArgs >= iArg) Attach (lpArgs, iArg); }
	~CStrArg (void) 
		{ if (m_hStr) ebUnlockString (m_hThread, m_hStr); }

	operator LPCSTR () { return m_pcStr; }
	void Attach (ebARGS lpArgs, int iArg)
		{
			if (m_hStr) { ebUnlockString (m_hThread, m_hStr); m_pcStr = NULL; }
			m_hStr = ebGetString (lpArgs, iArg);
			if (m_hStr) m_pcStr = ebLockString (m_hThread, m_hStr);
		}
};

// Setzen eines ErgebnisStrings -----------------------------------------------
inline void SetString (ebHTHREAD hThread, ebARGS lpArgs, LPCSTR pcStr, int iArg = RETURNVAL)
{
	ebFreeString (hThread, ebGetString (lpArgs, iArg));
	ebSetString (lpArgs, iArg, ebCreateString (hThread, pcStr));
}

///////////////////////////////////////////////////////////////////////////////
// Abfrage optionaler Parameter -----------------------------------------------
inline int IntArg (ebARGS lpArgs, int iArg, int iDefault, int iNumArgs)
{
	return (iNumArgs >= iArg) ? ebGetInt (lpArgs, iArg) : iDefault;
}

inline long LongArg (ebARGS lpArgs, int iArg, long lDefault, int iNumArgs)
{
	return (iNumArgs >= iArg) ? ebGetLong (lpArgs, iArg) : lDefault;
}

inline ebBOOL BoolArg (ebARGS lpArgs, int iArg, ebBOOL fDefault, int iNumArgs)
{
	return (iNumArgs >= iArg) ? (ebGetBool(lpArgs, iArg) ? -1 : 0) : fDefault;
}

// Setzen und abfragen eines Bool/bool - Wertes -------------------------------
inline void SetBool (ebARGS lpArgs, int fToSet, int iArg = RETURNVAL)
{
	ebSetBool (lpArgs, iArg, (0 != fToSet)? -1 : 0);
}

inline bool GetBool (ebARGS lpArgs, int iArg)
{
	return ebGetBool(lpArgs, iArg) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen eines Objekt-(Interface-)Pointers ---------------------------------
inline IUnknown *GetDaoObject (ebARGS lpArgs, int iArg = OBJTARGET)
{
	return reinterpret_cast<IUnknown *>(ebGetObject (lpArgs, iArg));
}

template<class T>
inline T *GetDaoObject (ebARGS lpArgs, T *, int iArg = OBJTARGET)
{
	return reinterpret_cast<T *>(ebGetObject (lpArgs, iArg));
}

// Setzen eines Objekt-(Interface-)Pointers -----------------------------------
inline void SetDaoObject (ebARGS lpArgs, const CdbOleObject &rcObj, int iArg = RETURNVAL)
{
	ebSetObject (lpArgs, iArg, reinterpret_cast<DWORD>(rcObj.GetInterface(true)));
}


#endif // _EBARGS_H

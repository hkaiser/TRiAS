// Declarations for universal exception translator
// File: TransEx.h

#if !defined(_TRANSEX_H)
#define _TRANSEX_H

#include <exception>	// C++ exception-baseclass
#include <eh.h>			// User Defined Exception Handling

///////////////////////////////////////////////////////////////////////////////
// implementierte Exception-Hierarchie
class CWin32Exception;
	class CAccessViolation;
	class CBreakPoint;
	class CDatatypeMisalignment;
	class CSingleStep;
	class CArrayBoundsExceeded;
	class CMathException;
		class CFltException;
			class CFltDenormalOperand;
			class CFltDivideByZero;
			class CFltInexactResult;
			class CFltInvalidOperation;
			class CFltOverflow;
			class CFltStackCheck;
			class CFltUnderflow;
		class CIntException;
			class CIntDivideByZero;
			class CIntOverflow;
	class CPrivInstruction;
	class CNoncontinueableException;
	class CWin32UserException;

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für alle Win32Exceptions
class _CTR_ENTRY32 CWin32Exception : 
	public exception 
{
public:
	CWin32Exception(const char *_S) : exception (_S) {}
	virtual ~CWin32Exception();

	enum WIN32EXEPTION {
		W32EXP_None = 0x00000000,
		W32EXP_AccessViolation = 0x00000001,
		W32EXP_BreakPoint = 0x00000002,
		W32EXP_DatatypeMisalignment = 0x00000004,
		W32EXP_SingleStep = 0x00000008,
		W32EXP_ArrayBoundsExceeded = 0x00000010,
		W32EXP_FltDenormalOperand = 0x00000020,
		W32EXP_FltDivideByZero = 0x00000040,
		W32EXP_FltInexactResult = 0x00000080,
		W32EXP_FltInvalidOperation = 0x00000100,
		W32EXP_FltOverflow = 0x00000200,
		W32EXP_FltStackCheck = 0x00000400,
		W32EXP_FltUnderflow = 0x00000800,
		W32EXP_FltException = 
			W32EXP_FltDenormalOperand |
			W32EXP_FltDivideByZero |
			W32EXP_FltInexactResult |
			W32EXP_FltInvalidOperation |
			W32EXP_FltOverflow |
			W32EXP_FltStackCheck |
			W32EXP_FltUnderflow, 
		W32EXP_IntDivideByZero = 0x00001000,
		W32EXP_IntOverflow = 0x00002000,
		W32EXP_IntException = 
			W32EXP_IntDivideByZero |
			W32EXP_IntOverflow,
		W32EXP_MathException =
			W32EXP_FltException | 
			W32EXP_IntException,
		W32EXP_PrivInstruction = 0x00004000,
		W32EXP_NoncontinueableException = 0x00008000,
		W32EXP_UserException = 0x00010000,
		W32EXP_All = ~W32EXP_None,
	};

	static BOOL SetTranslator (void);
	static BOOL ResetTranslator (void);
	static UINT Translate (UINT uiExceptions, UINT uiMask = W32EXP_All);
	static void Translator (UINT uiCode, struct _EXCEPTION_POINTERS *p);

private:
	static UINT m_uiTranslated;
	static BOOL m_fInstalled;
	static _se_translator_function m_pNextProc;
};

///////////////////////////////////////////////////////////////////////////////
// Abgeleitete Exceptions
class _CTR_ENTRY32 CAccessViolation : 
	public CWin32Exception 
{
public:
	CAccessViolation (const char *_S = NULL);
	virtual ~CAccessViolation() _THROW0() {}
};

class _CTR_ENTRY32 CBreakPoint : 
	public CWin32Exception 
{
public:
	CBreakPoint (const char *_S = NULL);
	virtual ~CBreakPoint() _THROW0() {}
};

class _CTR_ENTRY32 CDatatypeMisalignment : 
	public CWin32Exception 
{
public:
	CDatatypeMisalignment (const char *_S = NULL);
	virtual ~CDatatypeMisalignment() _THROW0() {}
};

class _CTR_ENTRY32 CSingleStep : 
	public CWin32Exception 
{
public:
	CSingleStep (const char *_S = NULL); 
	virtual ~CSingleStep() _THROW0() {}
};

class _CTR_ENTRY32 CArrayBoundsExceeded : 
	public CWin32Exception 
{
public:
	CArrayBoundsExceeded (const char *_S = NULL);
	virtual ~CArrayBoundsExceeded() _THROW0() {}
};

class _CTR_ENTRY32 CMathException : 
	public CWin32Exception 
{
public:
	CMathException (const char *_S) _THROW0() : CWin32Exception(_S) {}
	virtual ~CMathException() _THROW0() {}
};
class _CTR_ENTRY32 CFltException : 
	public CMathException 
{
public:
	CFltException (const char *_S);
	virtual ~CFltException() _THROW0() {}
};

class _CTR_ENTRY32 CFltDenormalOperand : 
	public CFltException 
{
public:
	CFltDenormalOperand (const char *_S = NULL);
	virtual ~CFltDenormalOperand() _THROW0() {}
};

class _CTR_ENTRY32 CFltDivideByZero : 
	public CFltException 
{
public:
	CFltDivideByZero (const char *_S = NULL);
	virtual ~CFltDivideByZero() _THROW0() {}
};

class _CTR_ENTRY32 CFltInexactResult : 
	public CFltException 
{
public:
	CFltInexactResult (const char *_S = NULL);
	virtual ~CFltInexactResult() _THROW0() {}
};

class _CTR_ENTRY32 CFltInvalidOperation : 
	public CFltException 
{
public:
	CFltInvalidOperation (const char *_S = NULL);
	virtual ~CFltInvalidOperation() _THROW0() {}
};

class _CTR_ENTRY32 CFltOverflow : 
	public CFltException 
{
public:
	CFltOverflow (const char *_S = NULL);
	virtual ~CFltOverflow() _THROW0() {}
};

class _CTR_ENTRY32 CFltStackCheck : 
	public CFltException 
{
public:
	CFltStackCheck (const char *_S = NULL);
	virtual ~CFltStackCheck() _THROW0() {}
};

class _CTR_ENTRY32 CFltUnderflow : 
	public CFltException 
{
public:
	CFltUnderflow (const char *_S = NULL);
	virtual ~CFltUnderflow() _THROW0() {}
};

class _CTR_ENTRY32 CIntException : 
	public CMathException 
{
public:
	CIntException (const char *_S) _THROW0() : CMathException(_S) {} 
	virtual ~CIntException() _THROW0() {}
};

class _CTR_ENTRY32 CIntDivideByZero : 
	public CIntException 
{
public:
	CIntDivideByZero (const char *_S = NULL);
	virtual ~CIntDivideByZero() _THROW0() {}
};

class _CTR_ENTRY32 CIntOverflow : 
	public CIntException 
{
public:
	CIntOverflow (const char *_S = NULL);
	virtual ~CIntOverflow() _THROW0() {}
};

class _CTR_ENTRY32 CPrivInstruction : 
	public CWin32Exception 
{
public:
	CPrivInstruction (const char *_S = NULL);
	virtual ~CPrivInstruction() _THROW0() {}
};

class _CTR_ENTRY32 CNoncontinueableException : 
	public CWin32Exception 
{
public:
	CNoncontinueableException (const char *_S = NULL);
	virtual ~CNoncontinueableException() _THROW0() {}
};

class _CTR_ENTRY32 CWin32UserException : 
	public CWin32Exception 
{
public:
	CWin32UserException (UINT uiCode, const char *_S = NULL);
	CWin32UserException(const CWin32UserException &);
	CWin32UserException& operator= (const CWin32UserException &);
	virtual ~CWin32UserException() _THROW0() {}

	UINT GetExceptionCode (void) const { return m_uiCode; }

private:
	UINT m_uiCode;
};

#endif // _TRANSEX_H

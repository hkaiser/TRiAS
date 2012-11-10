// Universal exception translator
// File: TransEx.cpp

#include "contpre.hxx"

#include <float.h>
#include <TransEx.h>

#include "cont32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Verkettung zu nächstem Handler
_se_translator_function CWin32Exception::m_pNextProc = NULL;
BOOL CWin32Exception::m_fInstalled = false;
UINT CWin32Exception::m_uiTranslated = W32EXP_None;

BOOL CWin32Exception::SetTranslator (void)
{
	if (!m_fInstalled) {
		TX_ASSERT(NULL == m_pNextProc);

		m_pNextProc = _set_se_translator (Translator);
		m_fInstalled = true;
		return true;
	}

return false;
}

BOOL CWin32Exception::ResetTranslator (void)
{
	if (m_fInstalled) {
	_se_translator_function pNextProc = m_pNextProc;

		m_pNextProc = NULL;

	_se_translator_function pPrevProc = _set_se_translator (m_pNextProc);

		TX_ASSERT(Translator == pPrevProc);
		m_fInstalled = false;
		return true;
	}

return false;
}

UINT CWin32Exception::Translate (UINT uiExceptions, UINT uiMask)
{
UINT uiPrev = m_uiTranslated;

	m_uiTranslated = (uiPrev & ~uiMask) | (uiExceptions & uiMask);

// evtl. Floating Exceptions einschalten
	if ((uiExceptions & uiMask) & W32EXP_FltException) {
	UINT uiFltEx = uiExceptions & uiMask;
	UINT uiNewCW = 0;

		if (uiFltEx & W32EXP_FltDenormalOperand)
			uiNewCW |= _EM_DENORMAL;
		if (uiFltEx & W32EXP_FltDivideByZero)
			uiNewCW |= _EM_ZERODIVIDE;
		if (uiFltEx & W32EXP_FltInexactResult)
			uiNewCW |= _EM_INEXACT;
		if (uiFltEx & W32EXP_FltInvalidOperation)
			uiNewCW |= _EM_INVALID;
		if (uiFltEx & W32EXP_FltOverflow)
			uiNewCW |= _EM_OVERFLOW;
		if (uiFltEx & W32EXP_FltUnderflow)
			uiNewCW |= _EM_UNDERFLOW;

		if (uiNewCW != 0)
			_control87 (uiNewCW, uiNewCW);
	}
	return uiPrev;
}

CWin32Exception::~CWin32Exception (void)
{
	// placeholder only
}

void CWin32Exception::Translator (UINT uiCode, _EXCEPTION_POINTERS *p)
{
	switch (uiCode) {
	case EXCEPTION_ACCESS_VIOLATION:
		if (m_uiTranslated & W32EXP_AccessViolation)
			throw CAccessViolation();
		break;

	case EXCEPTION_BREAKPOINT:
		if (m_uiTranslated & W32EXP_BreakPoint)
			throw CBreakPoint();
		break;

	case EXCEPTION_DATATYPE_MISALIGNMENT:
		if (m_uiTranslated & W32EXP_DatatypeMisalignment)
			throw CDatatypeMisalignment();
		break;

	case EXCEPTION_SINGLE_STEP:
		if (m_uiTranslated & W32EXP_SingleStep)
			throw CSingleStep();
		break;

	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
		if (m_uiTranslated & W32EXP_ArrayBoundsExceeded)
			throw CArrayBoundsExceeded();
		break;

	case EXCEPTION_FLT_DENORMAL_OPERAND:
		if (m_uiTranslated & W32EXP_FltDenormalOperand)
			throw CFltDenormalOperand();
		break;

	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		if (m_uiTranslated & W32EXP_FltDivideByZero)
			throw CFltDivideByZero();
		break;

	case EXCEPTION_FLT_INEXACT_RESULT:
		if (m_uiTranslated & W32EXP_FltInexactResult)
			throw CFltInexactResult();
		break;

	case EXCEPTION_FLT_INVALID_OPERATION:
		if (m_uiTranslated & W32EXP_FltInvalidOperation)
			throw CFltInvalidOperation();
		break;

	case EXCEPTION_FLT_OVERFLOW:
		if (m_uiTranslated & W32EXP_FltOverflow)
			throw CFltOverflow();
		break;

	case EXCEPTION_FLT_STACK_CHECK:
		if (m_uiTranslated & W32EXP_FltStackCheck)
			throw CFltStackCheck();
		break;

	case EXCEPTION_FLT_UNDERFLOW:
		if (m_uiTranslated & W32EXP_FltUnderflow)
			throw CFltUnderflow();
		break;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		if (m_uiTranslated & W32EXP_IntDivideByZero)
			throw CIntDivideByZero();
		break;

	case EXCEPTION_INT_OVERFLOW:
		if (m_uiTranslated & W32EXP_IntOverflow)
			throw CIntOverflow();
		break;

	case EXCEPTION_PRIV_INSTRUCTION:
		if (m_uiTranslated & W32EXP_PrivInstruction)
			throw CPrivInstruction();
		break;

	case EXCEPTION_NONCONTINUABLE_EXCEPTION:
		if (m_uiTranslated & W32EXP_NoncontinueableException)
			throw CNoncontinueableException();
		break;

	default:
		if (m_uiTranslated & W32EXP_UserException)
			throw CWin32UserException (uiCode);
		break;
	}

// if not handled here, chain on to previous handler
	if (NULL != m_pNextProc) 
		m_pNextProc (uiCode, p);		// chain on
}

///////////////////////////////////////////////////////////////////////////////
// constructor of any FloatException has to clear exception
CFltException::CFltException (const char *_S)
	: CMathException(_S)
{
	_clearfp();		// turn off exception for _controlfp to succeed

UINT uiCW = _controlfp (0, 0);	// save current control word

	_fpreset();						// reset everything
	_controlfp (uiCW, (UINT)~0);	// restore control word
}

///////////////////////////////////////////////////////////////////////////////
// lokale ResourceStringKlasse
extern HINSTANCE g_hInst;

class ResString
{
private:
	char string[64];

public:
	ResString (UINT uiResID)
	{ 
		if (0 == ::LoadString (g_hInst, uiResID, string, sizeof(string)))
			string[0] = '\0';
			
	}
	operator const char* (void) { return string; };
};

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren der einzelnen Exceptions
CAccessViolation::CAccessViolation (const char *_S) _THROW0()
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_ACCESSVIOLATION))
{
}

CBreakPoint::CBreakPoint (const char *_S) _THROW0()
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_BREAKPOINT))
{
}

CDatatypeMisalignment::CDatatypeMisalignment (const char *_S) _THROW0()
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_DATATYPEMISALIGNMENT))
{
}

CSingleStep::CSingleStep (const char *_S) _THROW0()
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_SINGLESTEP))
{
}

CArrayBoundsExceeded::CArrayBoundsExceeded (const char *_S) _THROW0()
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_ARRAYBOUNDSEXCEEDED))
{
}

CFltDenormalOperand::CFltDenormalOperand (const char *_S) _THROW0()
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTDENORMALOPERAND))
{
}

CFltDivideByZero::CFltDivideByZero (const char *_S) _THROW0()
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTDIVIDEBYZERO))
{
}

CFltInexactResult::CFltInexactResult (const char *_S)
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTINEXACTRESULT))
{
}

CFltInvalidOperation::CFltInvalidOperation (const char *_S)
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTINVALIDOPERATION))
{
}

CFltOverflow::CFltOverflow (const char *_S)
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTOVERFLOW))
{
}

CFltStackCheck::CFltStackCheck (const char *_S)
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTSTACKCHECK))
{
}

CFltUnderflow::CFltUnderflow (const char *_S)
	: CFltException (NULL != _S ? _S : ResString(IDS_FLTUNDERFLOW))
{
}

CIntDivideByZero::CIntDivideByZero (const char *_S)
	: CIntException (NULL != _S ? _S : ResString(IDS_INTDIVIDEBYZERO))
{
}

CIntOverflow::CIntOverflow (const char *_S)
	: CIntException (NULL != _S ? _S : ResString(IDS_INTOVERFLOW))
{
}

CPrivInstruction::CPrivInstruction (const char *_S)
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_PRIVINSTRUCTION))
{
}

CNoncontinueableException::CNoncontinueableException (const char *_S)
	: CWin32Exception (NULL != _S ? _S : ResString(IDS_NONCONTINUEABLE))
{
}

CWin32UserException::CWin32UserException (UINT uiCode, const char *_S)
	: m_uiCode(uiCode), 
	  CWin32Exception (NULL != _S ? _S : ResString(IDS_USERDEFINED))
{
}

CWin32UserException::CWin32UserException (const CWin32UserException &rExc)
	: CWin32Exception(rExc), m_uiCode(rExc.GetExceptionCode())
{
}

CWin32UserException& CWin32UserException::operator= (const CWin32UserException &rExc)
{
	static_cast<CWin32Exception &>(*this) = rExc;
	m_uiCode = rExc.GetExceptionCode();	
	return *this;
}


// exceptio --exception members
#include <bool.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>

#include <exceptio.hpp>

xmsg :: raise_handler xmsg :: m_pHandler = 0;

// copy string to heap
static const char *hs (const char *s)		
{
const char *d;

	return (s == 0 || (d = (const char *)malloc(strlen(s) + 1)) == 0 
			   ? 0 : (const char *)strcpy((char *)d, s));
}

// set new raise handler
xmsg :: raise_handler xmsg :: set_raise_handler (raise_handler pnew)	
{
const raise_handler pold = m_pHandler;

	m_pHandler = pnew;

return (pold);
}

// construct an xmsg
xmsg :: xmsg (const char *what, const char *where, const char *why)
      : m_pWhat (hs(what)), 
	m_pWhere (hs(where)), 
	m_pWhy(hs(why)),
	m_fAlloced (1)
{
}

// copy an xmsg
xmsg :: xmsg (const xmsg &rhs)
      : m_pWhat (hs(rhs.what())),
	m_pWhere (hs(rhs.where())), 
	m_pWhy(hs(rhs.why())),
	m_fAlloced (1)
{
}

// assign an xmsg
xmsg &xmsg :: operator= (const xmsg &rhs)
{
	if (this != &rhs) {	// not the same, copy
		_Tidy();
		m_pWhat = hs(rhs.what());
		m_pWhere = hs(rhs.where());
		m_pWhy = hs(rhs.why());
		m_fAlloced = 1;
	}
	
return (*this);
}

// destruct an xmsg
xmsg :: ~xmsg (void)
{
	_Tidy();
}

// raise an xmsg
void xmsg :: raise (void)
{
	if (m_pHandler) (*m_pHandler) (*this);
	do_raise();
	_RAISE(*this);
}

// return non-null What pointer
const char *xmsg :: what (void) const 
{
	return m_pWhat != 0 ? m_pWhat : "";
}

// return non-null Where pointer
const char *xmsg :: where (void) const 
{
	return m_pWhere != 0 ? m_pWhere : "";
}

// return non-null Why pointer
const char *xmsg :: why (void) const 
{
	return m_pWhy != 0 ? m_pWhy : "";
}

// do no special raise action by default
void xmsg :: do_raise (void)
{
}

// construct an xmsg, optional copy
xmsg :: xmsg (const char *what, const char *where, const char *why, _Bool fCopy)
      : m_pWhat (fCopy ? hs(what) : what),
      	m_pWhere (fCopy ? hs(where) : where),
      	m_pWhy (fCopy ? hs(why) : why),
      	m_fAlloced (fCopy)
{
}

// handle unthrowable xmsg
void xmsg :: _Throw (xmsg *pex)
{
/*#if defined(MSWIND)
char cbBuffer[80];

	wsprintf (cbBuffer, "Exception: %s", pex ? pex->what() : "??");
	FatalAppExit (0, cbBuffer);
#else // MSWIND
*/
	cerr << "Exception: " << (pex ? pex->what() : "??") << endl;
	:: raise (SIGABRT);
//#endif
}

// free storage for an xmsg
void xmsg :: _Tidy (void)
{
	if (m_fAlloced) {
		free ((void *)m_pWhat);
		free ((void *)m_pWhere);
		free ((void *)m_pWhy);
		m_fAlloced = 0;
	}
}


// exception standard header
#ifndef _EXCEPTIO_
#define _EXCEPTIO_

#include <defines.hpp>

// class xmsg
class xmsg {
public:
typedef void(*raise_handler)(xmsg &);
static 	raise_handler set_raise_handler (raise_handler);
	
		xmsg (const char * = 0, const char * = 0, const char * = 0);
		xmsg (const xmsg &);
		xmsg & operator= (const xmsg &);
	virtual ~xmsg (void);
	
	void raise (void);
	const char *what (void) const;
	const char *where (void) const;
	const char *why (void) const;

static	void _Throw (xmsg *);

protected:
virtual	void do_raise (void);

		xmsg (const char *, const char *, const char *, bool);
private:
	void _Tidy (void);
static	raise_handler m_pHandler;
	const char *m_pWhat, *m_pWhere, *m_pWhy;
	bool m_fAlloced;
};

// class xlogic
class xlogic : public xmsg {
public:
		xlogic (const char * = 0, const char * = 0, const char * = 0);
	virtual ~xlogic (void);

protected:
virtual void do_raise (void);
};

// class xruntime
class xruntime : public xmsg {
public:
		xruntime (const char * = 0, const char * = 0, const char * = 0);
	virtual ~xruntime (void);

protected:
virtual void do_raise (void);
		xruntime (const char *, const char *, const char *, bool);
};

// class xbadcast
class badcast : public xlogic {
public:
		badcast (const char * = 0, const char * = 0, const char * = 0);
	virtual ~badcast (void);

protected:
virtual void do_raise (void);
};

// class invalidargument
class invalidargument : public xlogic {
public:
		invalidargument (const char * = 0, const char * = 0, const char * = 0);
	virtual ~invalidargument (void);

protected:
virtual void do_raise (void);
};

// class lengtherror
class lengtherror : public xlogic {
public:
		lengtherror (const char * = 0, const char * = 0, const char * = 0);
	virtual ~lengtherror (void);

protected:
virtual void do_raise (void);
};

// class outofrange
class outofrange : public xlogic {
public:
		outofrange (const char * = 0, const char * = 0, const char * = 0);
	virtual ~outofrange (void);

protected:
virtual void do_raise (void);
};

// class overflow
class overflow : public xruntime {
public:
		overflow (const char * = 0, const char * = 0, const char * = 0);
	virtual ~overflow (void);

protected:
virtual void do_raise (void);
};

// class xdomain
class xdomain : public xlogic {
public:
		xdomain (const char * = 0, const char * = 0, const char * = 0);
	virtual ~xdomain (void);

protected:
virtual void do_raise (void);
};

// class xrange
class xrange : public xruntime {
public:
		xrange (const char * = 0, const char * = 0, const char * = 0);
	virtual ~xrange (void);

protected:
virtual void do_raise (void);
};

// function declarations
// fvoid_t *set_terminate (fvoid_t *);
// fvoid_t *set_unexpected (fvoid_t *);
void std_terminate (void), std_unexpected (void);

#endif // _EXCEPTION_


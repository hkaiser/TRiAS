// test <exception>
#include <assert.h>
#include <setjmp.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream.h>

#include <exceptio.hpp>

static jmp_buf jbuf;

class myex : public xmsg {
public:
		myex (const char *what = 0) : xmsg (what) {}
		
protected:
virtual void do_raise (void);
};

void myex :: do_raise (void)
{
	longjmp (jbuf, 1);
}

void abort_hand (int)
{
	cout << "Exceptions are not implemented" << endl;
	cout << "SUCCESS testing <exception>" << endl;
	exit(0);
}

void jmpback (void)
{
	longjmp (jbuf, 1);
}

void raiseback (xmsg &)
{
	longjmp (jbuf, 1);
}

void try_myex_hand (void)
{
	if (setjmp(jbuf) == 0) {
		myex ("testing myex::do_raise").raise();
		assert("myex::raise() returned" == 0);
	}
}

void try_raise_hand (void)
{
xmsg :: raise_handler save_hand = xmsg::set_raise_handler(&raiseback);

	if (setjmp(jbuf) == 0) {
		xmsg("testing raise handler").raise();
		assert("xmsg::raise() returned" == 0);
	}
	assert (xmsg::set_raise_handler(save_hand) == &raiseback);
}

void try_terminate (void)
{
fvoid_t *save_hand = set_terminate (&jmpback);

	if (setjmp (jbuf) == 0) 
		std_terminate(), assert("terminate() returned" == 0);
	assert (set_terminate(save_hand) == &jmpback);
}

void try_unexpected (void)
{
fvoid_t *save_hand = set_unexpected (&jmpback);

	if (setjmp (jbuf) == 0) 
		std_unexpected(), assert("unexpected() returned" == 0);
	assert (set_unexpected(save_hand) == &jmpback);
}


int main()
{
xmsg x1("xmsg what", "where", "why");
xlogic x2 ("xlogic what", "where", "why");
xruntime x3 ("xruntime what", "where", "why");
badcast x4 ("badcast what", "where", "why");
invalidargument x5 ("invalidargument what", "where", "why");
lengtherror x6 ("lengtherror what", "where", "why");
outofrange x7 ("outofrange what", "where", "why");
overflow x8 ("overflow what", "where", "why");
xdomain x9 ("xdomain what", "where", "why");
xrange x10 ("xrange what", "where", "why");

	try_myex_hand();
	try_raise_hand();
	try_terminate();
	try_unexpected();
	
	cout << "About to throw an exception" << endl;
	signal (SIGABRT, &abort_hand);
	_TRY_BEGIN
		_RAISE(x1), assert ("throw returned" == 0);
	_CATCH_ALL
		cout << "Exceptions are implemented" << endl;
	_CATCH_END
	cout << "SUCCESS testing <exception>" << endl;

return (0);
}


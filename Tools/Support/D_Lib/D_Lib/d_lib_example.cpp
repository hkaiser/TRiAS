// ------ begin of program --------------
#include <stdio.h>
#include <iostream.h>

#include <d_lib.h>

class AAA_c
{
D_CLASS(AAA_c)
public:
	void func();
	virtual void virt_func();
	static void static_func();
friend ostream& operator <<( ostream& s, const AAA_c&)
	{ s << "AAA_c"; return( s); }
};

class BBB_c : public AAA_c
{
D_CLASS( BBB_c)
public:
	void func();
	virtual void virt_func();
	static void static_func();
};

template <class T>
class AAATmpl
{
D_CLASS(AAATmpl)
public:
	AAATmpl( const T val)
		: _val( val)
	{}
	void func()
	{ D_OUT(1) << "in AAATmpl::func() for [" << _val << "]\n" <<
					D_END; }
	static void static_func()
	{ D_OUT(1) << "in AAATmpl::static_func()\n" << D_END; }
private:
	const T _val;
};

struct AAAStr
{
D_CLASS( AAAStr)
public:
	void func();
};

void AAA_c::func()
{
	D_OUT(1) << "in AAA_c::func()\n" << D_END;
}

void AAA_c::virt_func()
{
	D_OUT(1) << "in AAA_c::virt_func()\n" << D_END;
	static_func();
}

void AAA_c::static_func()
{
	D_OUT(1) << "in AAA_c::static_func()\n" << D_END;
}

void BBB_c::func()
{
	D_OUT(1) << "in BBB_c::func()\n" << D_END;
}

void BBB_c::virt_func()
{
	D_OUT(1) << "in BBB_c::virt_func()\n" << D_END;
	static_func();
}

void BBB_c::static_func()
{
	D_OUT(1) << "in BBB_c::static_func()\n" << D_END;
}

void AAAStr::func()
{
	D_OUT(1) << "in AAAStr::func()\n" << D_END;
}

static void g( AAA_c* o)
{
	o->func();
	o->virt_func();
}

static void AAA_c_test()
{

	int a = 7;
	double b = 3.14159;

	D_OUT(1) << "sum of a and b = [" << a + b <<
		"] - I'm here 1!\n" << D_END;
	D_OUT(2) << "sum of a and b = [" << a + b <<
		"] - I'm here 2!\n" << D_END;
	D_OUT(3) << "sum of a and b = [" << a + b <<
		"] - I'm here 3!\n" << D_END;

	AAA_c aaa;
	aaa.func();
	aaa.virt_func();
	AAA_c::static_func();

	BBB_c bbb;
	bbb.func();
	bbb.virt_func();
	BBB_c::static_func();

	g( &aaa);
	g( &bbb);

	AAATmpl<double> a1( 3.14159);
	a1.func();
	AAATmpl<double>::static_func();

	AAAStr a2;
	a2.func();

	AAATmpl<AAA_c> a3( aaa);
	a3.func();
}

static void my_lovely_proc( int a)
{
     D_OUT(3) << "my_lovely_proc() a = [" << a << "]\n" << D_END;
}

void my_lovely_func()
{
D_STACK( my_lovely_func)

     D_OUT(1) << "my_lovely_func()\n" << D_END;
     for( int a = 15; a >=0; a--)
             my_lovely_proc( a);
}

static void recursive_func( int a)
{
D_STACK(recursive_func1)
	D_OUT(1) << "In recursive_func( " << a << ")\n" << D_END;
	if( a == 5)
		return;
D_STACK(recursive_func2)
	recursive_func( a + 1);
}

static void recursive_functest()
{
D_STACK(recursive_functest)
	int a = 0;
	recursive_func( a);
}

static void stack_scope_test()
{
D_STACK(stack_scope_test)

	int a = 3;
	double b = 16.56;

	D_OUT(1) << "sum of a and b = [" << a + b <<
		"] - I'm here 1!\n" << D_END;
	D_OUT(2) << "sum of a and b = [" << a + b <<
		"] - I'm here 2!\n" << D_END;
	D_OUT(3) << "sum of a and b = [" << a + b <<
		"] - I'm here 3!\n" << D_END;

	my_lovely_func();
	recursive_functest();
}

static void init_int_array( int* arr, int sz)
{
	for( int i = 0; i < sz; i ++)
		arr[i] = 0;
}

void try_dbg_macros()
{
	D_( cout << "This long message will be printed from the \n" <<
		"debug version but will not be included even in \n" <<
		"binary code of the production version\n"; )

	int a = 5, b = 6; D_( cout << "a=" << a << " b=" << b << endl;)

	D_P1( a * b);
	D_P( a + b);
	D_P2( a - b, a + b);

	D_PF( "%04d", a + b);

	D_S( "I'm here!");
	D_S2( "I'm here too:", a + b);

	D_SF( "I'm here again in hex: x%02X", a + b);

	a = 10;
	b = 15;
	D_Support_c::SetFileNameStrip( 1);
	D_PRINT( 2, a + b);
	D_PRINT2( 1, a + b, a - b);
	D_PRINTF( 1, "%d - in C++!", a + b);

	D_OUT(1) << "sum of a and b = [" << a + b <<
		"] - I'm here 1!\n" << D_END;
	D_OUT(2) << "sum of a and b = [" << a + b <<
		"] - I'm here 2!\n" << D_END;
	D_OUT(3) << "sum of a and b = [" << a + b <<
		"] - I'm here 3!\n" << D_END;

	D_OUTF2(1, "From D_OUTF(1): sum = [%d]", a + b,
			" diff = [%d]", a - b);

	cout << "Now you can change your debug " <<
		"config file...\n" <<
		"And then enter a symbol and press " <<
		"<enter>\n" << flush;
	char c;
	cin >> c;

	int zero_arr[3];		// array to be zeroed
	init_int_array( zero_arr, 3);	// right initialization
	D_SELFTEST(2) {
		for( int i = 0; i < 3; i ++)
		{
			D_OUT(2) << "D_SELFTEST(2) - checking [" <<
				i  << "]\n" << D_END;
			if( zero_arr[i] != 0)
				D_OUT(2) << "Internal error: " <<
				    "illegal array initialization\n" <<
				    D_END;
		}
	}

	int incr_arr[3];		// array to be incremental
	init_int_array( incr_arr, 3);	// wrong initialization -
					// will be warned if the
					// D_SELFTEST's part is tuned on
	D_SELFTEST(1) {
		for( int i = 0; i < 3; i ++)
		{
			D_OUT(1) << "D_SELFTEST(1) - checking [" << i
				<< "]\n" << D_END;
			if( incr_arr[i] != i)
				D_OUT(1) << "Internal error: " <<
				    "illegal array initialization\n" <<
				    D_END;
		}
	}

	AAA_c_test();
	stack_scope_test();
}

void main( int argc, char* argv[])
{
	cout << "main() began!\n" << flush;
	try_dbg_macros();
	exit( 0);
}
// ------ end of program --------------

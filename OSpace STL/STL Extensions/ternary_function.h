/*
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Moscow Center for SPARC Technology makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 */

#ifndef _TERNARY_FUNCTION_H_
# define _TERNARY_FUNCTION_H_

# include <ospace/stl/function.h>

// ternary function objects

# if defined (__STL_BASE_TYPEDEF_BUG)
// this workaround is needed for SunPro 4.0.1
// suggested by "Martin Abernethy" <gma@paston.co.uk>:

// We have to introduce the XXary_predicate_aux structures in order to
// access the argument and return types of predicate functions supplied
// as type parameters. SUN C++ 4.0.1 compiler gives errors for template type parameters
// of the form 'name1::name2', where name1 is itself a type parameter.

template <class Operation>
struct __ternary_fun_aux : private Operation
{
	typedef typename Operation::first_argument_type first_argument_type;
	typedef typename Operation::second_argument_type second_argument_type;
	typedef typename Operation::third_argument_type second_argument_type;
	typedef typename Operation::result_type result_type;
};

#  define __TERNARY_ARG(Operation,type)  __ternary_fun_aux<Operation>::type
# else

#if !defined(__UNARY_ARG)
#  define __UNARY_ARG(Operation,type)  Operation::type
#endif
#if !defined(__BINARY_ARG)
#  define __BINARY_ARG(Operation,type)  Operation::type
#endif

#  define __TERNARY_ARG(Operation,type) Operation::type
# endif

template <class Arg1, class Arg2, class Arg3, class Result>
struct ternary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Arg3 third_argument_type;
    typedef Result result_type;
};      

template <class Arg1, class Arg2, class Arg3, class Result>
class pointer_to_ternary_function : 
    public ternary_function<Arg1, Arg2, Arg3, Result> {
protected:
    Result (*ptr)(Arg1, Arg2, Arg3);
public:
    pointer_to_ternary_function() {}
    explicit pointer_to_ternary_function(Result (*x)(Arg1, Arg2,Arg3)) : 
        ptr(x) {}
    Result operator()(Arg1 x, Arg2 y, Arg3 z) const { return ptr(x, y, z); }
};

// adaptors

template <class Predicate> 
class ternary_negate 
    : public ternary_function<typename __TERNARY_ARG(Predicate,
                                                     first_argument_type),
      typename __TERNARY_ARG(Predicate,second_argument_type), 
      typename __TERNARY_ARG(Predicate,third_argument_type),
      bool> {
protected:
    Predicate pred;
public:
    explicit ternary_negate(const Predicate& x) : pred(x) {}
    bool operator()(const first_argument_type& x, 
		    const second_argument_type& y,
                    const third_argument_type& z) const {
	return !pred(x, y, z); 
    }
};

template <class Predicate>
ternary_negate<Predicate> not3(const Predicate& pred) {
    return ternary_negate<Predicate>(pred);
}

template <class Operation> 
class tbinder1st : 
    public binary_function<typename __TERNARY_ARG(Operation,
                                                  second_argument_type),
                   typename __TERNARY_ARG(Operation,third_argument_type),
                   typename __TERNARY_ARG(Operation,result_type)> {
protected:
    Operation op;
    typename __TERNARY_ARG(Operation,first_argument_type) value;
public:
    tbinder1st(const Operation& x, 
               const typename __TERNARY_ARG(Operation,first_argument_type)& y)
	: op(x), value(y) {}
    result_type operator()(const first_argument_type& x, 
                           const second_argument_type& y) const {
	return op(value, x, y); 
    }
};

template <class Operation, class T>
tbinder1st<Operation> 
tbind1st(const Operation& op, const T& x) {
    return tbinder1st<Operation>(op, 
                                 typename __TERNARY_ARG(Operation,
                                                        first_argument_type)(x));
}

template <class Operation> 
class tbinder2nd : 
    public binary_function<typename __TERNARY_ARG(Operation,
                                                  first_argument_type),
    typename __TERNARY_ARG(Operation,third_argument_type),
    typename __TERNARY_ARG(Operation,result_type)> {
protected:
    Operation op;
    typename __TERNARY_ARG(Operation,second_argument_type) value;
public:
    tbinder2nd(const Operation& x, 
               const typename __TERNARY_ARG(Operation,
                                            second_argument_type)& y) 
	: op(x), value(y) {}
    result_type operator()(const first_argument_type& x, 
                           const second_argument_type& y) const {
	return op(x, value, y); 
    }
};

template <class Operation, class T>
tbinder2nd<Operation> 
tbind2nd(const Operation& op, const T& x) {
    return tbinder2nd<Operation>(op, 
                                 typename __TERNARY_ARG(Operation,
                                                        second_argument_type)(x));
}

template <class Operation> 
class tbinder3rd : 
    public binary_function<typename __TERNARY_ARG(Operation,
                                                  first_argument_type),
    typename __TERNARY_ARG(Operation,second_argument_type),
    typename __TERNARY_ARG(Operation,result_type)> {
protected:
    Operation op;
    typename __TERNARY_ARG(Operation,third_argument_type) value;
public:
    tbinder3rd(const Operation& x, 
               const typename __TERNARY_ARG(Operation,third_argument_type)& y) 
	: op(x), value(y) {}
    result_type operator()(const first_argument_type& x, 
                           const second_argument_type& y) const {
	return op(x, y,value); 
    }
};

template <class Operation, class T>
tbinder3rd<Operation> 
tbind3rd(const Operation& op, const T& x) {
    return tbinder3rd<Operation>(op, 
                                 typename __TERNARY_ARG(Operation,
                                                        third_argument_type)(x));
}

template <class Operation1, class Operation2, class Operation3, class Operation4>
class ternary_compose : 
    public unary_function<typename __UNARY_ARG(Operation2,
                                               argument_type),
    typename __BINARY_ARG(Operation1,result_type)> {
protected:
    Operation1 op1;
    Operation2 op2;
    Operation3 op3;
    Operation4 op4;
public:
    ternary_compose(const Operation1& x, const Operation2& y, 
		   const Operation3& z, const Operation4& zz) : 
        op1(x), op2(y), op3(z), op4(zz) { }
    typename __BINARY_ARG(Operation1,result_type) 
        operator()(const typename __UNARY_ARG(Operation2,argument_type)& x) const 
        {return op1(op2(x), op3(x), op4(x)); }
};

template <class Operation1, class Operation2, class Operation3, class Operation4>
ternary_compose<Operation1, Operation2, Operation3, Operation4> 
compose3(const Operation1& op1, const Operation2& op2, 
         const Operation3& op3, const Operation4& op4) {
    return ternary_compose<Operation1, Operation2, 
        Operation3, Operation4>(op1, op2, op3);
}

// 20.3.8  Adaptors for pointers to members [lib.member.pointer.adaptors]       

//  2) Implementations that have multiple pointer to function  types  pro-
//  vide additional ptr_fun template functions.

//   mem_fun2_t  calls  the  member function it is initialized with given a
//   pointer argument and two additional arguments of appropriate types.
template <class Class, class Arg1, class Arg2, class Result>
class mem_fun2_t: public ternary_function<Class*, Arg1, Arg2, Result> {
public:
protected:
    typedef Result (Class::*proc_type)(Arg1, Arg2);
    const proc_type ptr;
public:
    mem_fun2_t() {}
    explicit mem_fun2_t(proc_type p) : ptr(p) {}
    Result operator()(Class* x, Arg1 a, Arg2 b) const 
    { return (x->*ptr)(a,b);}
};

//   mem_fun2_t  calls  the  member function it is initialized with given a
//   reference argument and two additional arguments of appropriate types.
template <class Class, class Arg1, class Arg2, class Result>
class mem_fun2_ref_t: public ternary_function<Class, Arg1, Arg2, Result> {
public:
protected:
    typedef Result (Class::*proc_type)(Arg1, Arg2);
    const proc_type ptr;
public:
    mem_fun2_ref_t() {}
    explicit mem_fun2_ref_t(proc_type p) : ptr(p) {}
    Result operator()(Class& x, Arg1 a, Arg2 b) const 
    { return (x.*ptr)(a,b);}
};

//  mem_fun2(&X::f) returns an object through  which  X::f  can  be  called
//  given  a  pointer  to an X followed by the arguments required for f (if
//  any).
template <class Class, class Arg1, class Arg2, class Result>
inline mem_fun2_t<Class, Arg1, Arg2, Result> 
mem_fun2(Result (Class::*ptr)(Arg1,Arg2)) {
    return mem_fun2_t<Class, Arg, Arg2,Result>(ptr);
}

//  mem_fun2_ref(&X::f) returns an object through  which  X::f  can  be  called
//  given  a  reference  to an X followed by the arguments required for f (if
//  any).
template <class Class, class Arg1, class Arg2, class Result>
inline mem_fun2_ref_t<Class, Arg1, Arg2, Result> 
mem_fun2_ref(Result (Class::*ptr)(Arg1,Arg2)) {
    return mem_fun2_ref_t<Class, Arg, Arg2,Result>(ptr);
}

#endif

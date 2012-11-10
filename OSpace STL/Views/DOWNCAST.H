//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// downcast.h - support for typesafe access to containers of base class pointers
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that this notice appears unmodified in all derivative
// works.
//
// The author makes no representations about the suitability of
// this software for any purpose.  It is provided "as is"
// without express or implied warranty.
//
// For more information about this software, refer to:
//
//   http://www.zeta.org.au/~jon/STL/views/doc/views.html
//
// Please send comments about this software to:
//
//   Jon Seymour (jon@zeta.org.au)
//

#ifndef _downcast_h
#define _downcast_h
#include <function.h>
#include <view.h>

//
// downcast_dereference
//
// Given a base class pointer, return a reference to the subclass.
//
template <class BaseType,
          class SubType>
   class downcast_dereference : public unary_function<BaseType *, SubType &>
{
public:
    typedef     SubType * (BaseType::* downcast)();

protected:
    downcast mf;

public:
    SubType &operator()(BaseType *b) const { return *(b->*mf)(); };
    downcast_dereference(downcast const & mf) : mf(mf) {};
};

//
// is_subtype
//
// true if the safe downcast on the argument yields a valid
// pointer to an instance of the subtype.
//
//
template <class BaseType,
          class SubType>
   class is_subtype : public unary_function<bool, BaseType const *>
{
public:
    typedef     SubType * (BaseType::* downcast)();

protected:
    downcast mf;

public:
    bool operator()(BaseType *b) const { return (b->*mf)() != 0; };
    is_subtype(downcast const & mf) : mf(mf) {};
};

//
// downcast_dereference_view
//
// makes a collection of pointers to instances of a base type
// look like a collection of instances of the subtype.
//
//
template <class Domain, class BaseType, class SubType>
   struct downcast_dereference_view :  view<
                                          SubType,
                                          Domain,
                                          is_subtype<BaseType, SubType>,
                                          downcast_dereference<BaseType, SubType> >
{
    typedef view<SubType,
         Domain,
         is_subtype<BaseType, SubType>,
         downcast_dereference<BaseType, SubType> > super;

    downcast_dereference_view(domain_t &domain, predicate_t::downcast const &downcast)
      : super(domain, predicate_t(downcast), transform_t(downcast)) {}
};
#endif

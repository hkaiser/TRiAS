//
// Copyright (c) 1995, 1996 - Jon Seymour
//
// examples.cpp - example program
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

#include <list.h>        // from STL
#include <map.h>         // from STL
#include <stdiostr.h>    // from C++ streams library
#include <ctype.h>       // from C library


#include <views.h>       // view templates

bool even(int i)
{
   return !(i%2);
}

bool islowercase(char c)
{
   return islower(c);
}

void main (void) 
{
//
// This example illustrates filtered iteration over 
// an STL container.
//
// In this case, only the even integers in the list
// are printed, e.g.:
//
// 32 52 58
//
   {

      typedef list<int> domain_t;
      typedef subdomain<domain_t, pointer_to_unary_function<int, bool> > subdomain_t;

      domain_t              domain;
      subdomain_t           subdomain(domain, ptr_fun(even));
      ostream_iterator<int> out(cout, " ");

      domain.push_back(1);
      domain.push_back(255);
      domain.push_back(32);
      domain.push_back(43);
      domain.push_back(52);
      domain.push_back(57);
      domain.push_back(58);
      domain.push_back(59);
   
      copy(subdomain.begin(), subdomain.end(), out);
      cout << endl;

   }
   
   //
   // This example illustrates filtered iteration over a
   // scalar domain.
   //
   // In this case, only the even integers between 1 and
   // 10 are printed, e.g:
   //
   // 2 4 6 8 10
   //
   {

      typedef int_domain domain_t;
      typedef subdomain<domain_t, pointer_to_unary_function<int, bool> > subdomain_t;

      domain_t              domain(1, 10);
      subdomain_t           subdomain(domain, ptr_fun(even));
      ostream_iterator<int> out(cout, " ");

      copy(subdomain.begin(), subdomain.end(), out);
      cout << endl;

   }

   //
   // This example illustrates filtered iteration over a 
   // normal character array.
   //
   // In this case, only the array elements containing
   // lower case characters are printed, e.g.:
   //
   // g r o o v y
   //

   {

      static char letters[] = "AgBrCoDoEvFy";
   
      typedef subrange_domain<char, char *> domain_t;
      typedef subdomain<domain_t, pointer_to_unary_function<char, bool> > subdomain_t;

      domain_t               domain(letters, &letters[sizeof(letters)-1]);
      subdomain_t            subdomain(domain, ptr_fun(islowercase));
      ostream_iterator<char> out(cout, " ");

      copy(subdomain.begin(), subdomain.end(), out);
      cout << endl;
   }

   //
   // This example illustrates the use of a view to
   // transform a container of one type into an abstract container
   // of another type.
   // 
   // In this case, an abstract container of chars is formed from
   // the keys of a map. The contents of the abstract container are 
   // printed, e.g.:
   //   a b c
   //

   {

      typedef map<char, int, less<char> >        map_t;
      typedef map_keys<char, int, less<char> >   keys_t;
	  typedef map_values<char, int, less<char> > values_t;

      map_t                  map;
      keys_t                 keys(map);
	  values_t				 values(map);
      ostream_iterator<char> out(cout, " ");
      ostream_iterator<int> out_int(cout, " ");

      map['a'] = 1;
      map['b'] = 2;
      map['c'] = 3;

      copy(keys.begin(), keys.end(), out);
      cout << endl;
      copy(values.begin(), values.end(), out_int);
      cout << endl;
   }

}

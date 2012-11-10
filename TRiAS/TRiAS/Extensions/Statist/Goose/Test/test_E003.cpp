// This is -*- C++ -*-
// $Id: test_E003.cpp,v 1.2 1999/03/16 18:29:39 alstrup Exp $

//
// Confidential Proprietary Material Exclusively Owned by EMC Capital
// Management.  (C) EMC Capital Management 1999.  All Rights Reserved.
//

#include <DateSet.h>

main()
{
  DateSet foo;
  foo.add_string(string("1/1/1980"));
  foo.add_string("6/5/1969");
  foo.add_string("12/31/1999");

  foo.spew(cout);
  
  foo.sort();
  foo.spew(cout);
}




// $Id: test_E003.cpp,v 1.2 1999/03/16 18:29:39 alstrup Exp $

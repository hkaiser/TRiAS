// This is -*- C++ -*-
// $Id: test_A002.cpp,v 1.1 1999/07/07 05:05:45 trow Exp $

#include <config.h>
#include <iostream>
#include <math.h>
#include <zdouble.h>

const char* encoded[] = {
  "???????????",
  "??????o~??B",
  "??????o~??J",
  "mEZox`H?HNS",
  "qR{eU[G?ENf",
  0
};
double decoded[] = {
  0,
  1,
  -1,
  3.14159,
  12345.6789012345,
  0
};

main()
{
  cout.precision(16);
  cout << "Checking fixed example set:" << endl;
  int i=0;
  while (encoded[i]) {
    cout << encoded[i] << " =?= " << decoded[i] << " ";
    double y = decode_double(string(encoded[i]));
    string s = encode_double(decoded[i]);
    if (decoded[i] == y && string(encoded[i]) == s)
      cout << "ok";
    else
      cout << "failed";
    cout << endl;
    ++i;
  }

  cout << endl << "Checking generated examples:" << endl;
  for(int i=-100; i<100; ++i) {
    double x = (sin(i) + 1e-4) * exp(i / 3.333);
    string s = encode_double(x);
    double xx = decode_double(s);
    cout << s << " =?= " << x << " ";
    if (x == xx)
      cout << "ok";
    else
      cout << "failed";
    cout << endl;
  }
   
}




// $Id: test_A002.cpp,v 1.1 1999/07/07 05:05:45 trow Exp $

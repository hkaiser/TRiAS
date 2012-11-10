// This is -*- C++ -*-
// $Id: test_ascii_import.cpp,v 1.10 1999/03/16 18:27:41 alstrup Exp $

/* 
 * test_ascii_import.cpp
 *
 * Copyright (C) 1998 Asger Alstrup Nielsen
 *
 * Developed by Asger Alstrup Nielsen <alstrup@diku.dk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <config.h>
#include <iostream>
#include <fstream>
#include "AsciiImport.h"
#include "WarningController.h"
#include "AsciiReader.h"

using namespace std;

int main() {
  StreamWarnings sw(cout);
  CachingAsciiReader<istream> ar(cin, sw);
  AsciiImport importer(ar, sw);
  importer.autosetup();
  importer.import();

  for (size_t i=0; i < importer.column_divider().columns(); ++i) {
    cout << "'" << importer.headings()[i].c_str() << "':\n";
    importer.datasets()[i]->spew(cout);
  }

  return 0;
}

// This is -*- C++ -*-
// $Id: AsciiImport_smob.cpp,v 1.1 1999/03/30 00:44:01 hp Exp $

/* 
 * AsciiImport_smob.cpp
 *
 * Copyright (C) 1999 EMC Capital Management
 *
 * Developed by Jon Trowbridge & Havoc Pennington
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

#include <AsciiImport.h>
#include "guilegoose.h"

////////////// This is not a smob for now, just a single function.
////////////// Eventually we'll want a real smob too for flexibility,
////////////// then this function can be written in scheme even

// Returns a list of imported realsets.
SCM
realset_simple_import(SCM filename)
{
  SCM_ASSERT(gh_string_p(filename), filename, SCM_ARG1, "realset-simple-import");

  gh_defer_ints();

  SCM retval = SCM_LIST0;

  char* fn = gh_scm2newstr(filename, NULL);

  FILE* f = fopen(fn, "r");

  free(fn);
  fn = 0;
  
  if (f == NULL) 
    {
      gh_allow_ints();
      // Important: destructors will probably not be run when we 
      //  throw a scheme error. (?)
      goose_scm_error("realset-simple-import", "Failed to open file.");
    }

  try 
    {
      StackWarningController wc;    

      wc.set_see_warnings(30); // at most 30 warnings are displayed.

      FILEAsciiReader car(f, wc);
      
      AsciiImport ai(car, wc);

      ai.autosetup();

      ai.import();

      const vector<string>& names = ai.headings();
      const vector<DataSet*>& sets = ai.datasets();
      
      vector<string>::const_iterator ni = names.begin();
      vector<DataSet*>::const_iterator i = sets.begin();
      while (i != sets.end())
        {
          RealSet* rs = 0; 
          
          if ((*i)->type() == RealSet::typecode)
            rs = static_cast<RealSet*>(*i);
          else 
            {
              wc.warn("Non-scalar column ignored in import file");
              // it will never be gc'd since we aren't creating a smob 
              //  from it, so nuke it.
              delete *i;
            }
              
          if (ni != names.end())
            {
              if (rs != 0)
                rs->set_label(*ni);
              ++ni;
            }

          if (rs != 0)
            retval = gh_cons(realset2scm(rs), retval);
          
          ++i;
        }

      // Clean up the AsciiImport
      AsciiImport::delete_dataconverters(ai.dataconverters());

      const vector<string>& warns = wc.get_warnings();
      vector<string>::const_iterator wi = warns.begin();
      while (wi != warns.end())
        {
          string warning = "Text import warning: " + *wi + "\n";
          gh_display(gh_str02scm(const_cast<char*>(warning.c_str())));
          ++wi;
        }
    }
  catch (Exception & e)
    {
      fclose(f); // check error?
      gh_allow_ints();
      goose_scm_error("realset-simple-import", e.what().c_str());
    }
  catch (...)
    {
      // What the fuck, over
      assert(0);

      fclose(f);

      gh_allow_ints();
      return retval; // why not
    }

  fclose(f);

  gh_allow_ints();

  return retval;
}

//////////////////////////////////////////////////////////////////////////////

#define RECAST(x) reinterpret_cast<long int(*)()>(x)

void
scm_init_asciiimport()
{
  fflush(stdout);
  static bool initialized = false;
  if (initialized) return;
  initialized = true;

  scm_make_gsubr("realset-simple-import", 1, 0, 0, RECAST(realset_simple_import));
}


// $Id: AsciiImport_smob.cpp,v 1.1 1999/03/30 00:44:01 hp Exp $


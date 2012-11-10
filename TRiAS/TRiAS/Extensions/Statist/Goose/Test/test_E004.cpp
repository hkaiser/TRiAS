// This is -*- C++ -*-
// $Id: test_E004.cpp,v 1.1 1999/04/22 19:53:01 hp Exp $

#include <vector>
#include <AsciiImport.h>
#include <RealSet.h>

const char* data [] = {
"1.00000",
"2.3465490867",
"3.423652345",
"4",
"5.00000", 
"3458923498",
"10.04353450", 
"33545.4350349",
"50948",  
"350298924.0"
};

static const unsigned int data_size = sizeof(data)/sizeof(data[0]);

int main (int argc, char** argv)
{
  string filename = "test.dat";

  unlink(filename.c_str());

  FILE* outfile = fopen(filename.c_str(), "w");

  if (!outfile)
    {
      perror("couldn't open output file");
      exit(1);
    }

  if (data_size % 2 != 0)
    {
      fprintf(stderr, "bug in test program");
      exit(1);
    }

  // write two per line
  unsigned int x = 0;
  while (x < data_size)
    {
      fputs(data[x], outfile);
      ++x;
      fputs("  ", outfile);
      fputs(data[x], outfile);
      ++x;
      fputs("\n", outfile);
    }
    
  if (fclose(outfile) != 0)
    {
      perror("couldn't close output file");
      exit(1);
    }

  FILE* f = fopen(filename.c_str(), "r");
  
  if (f == NULL) 
    {
      perror("couldn't open input file");
      exit(1);
    }

  try {
    vector<RealSet*> realsets;

    StackWarningController wc;    
    
    wc.set_see_warnings(10); // at most 10 warnings are displayed.
    
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
              {
                if ((*ni).empty())
                  rs->set_label("Imported Data");
                else
                  rs->set_label(*ni);
              }
            ++ni;
          }

        realsets.push_back(rs);
          
        ++i;
      }

    // Clean up the AsciiImport
    AsciiImport::delete_dataconverters(ai.dataconverters());

    string all_warnings;

    const vector<string>& warns = wc.get_warnings();
    vector<string>::const_iterator wi = warns.begin();
    while (wi != warns.end())
      {
        all_warnings += *wi;
        all_warnings += "\n";
        
        ++wi;
      }

    fputs(all_warnings.c_str(), stderr);

    if (realsets.size() != 2)
      {
        fprintf(stderr, "Didn't get two columns\n");
        exit(1);
      }

    realsets[0]->spew(cout);
    realsets[1]->spew(cout);

    if (realsets[0]->size() != data_size/2 || 
        realsets[1]->size() != data_size/2)
      {
        fprintf(stderr, "Wrong size data\n");
        exit(1);
      }

    // This is such a lame test, we don't even check the imported values...

  }
  catch (Exception & e)
    {
      fclose(f);
      fprintf(stderr, e.what().c_str());
      exit(1);
    }
  catch (...)
    {
      // What the fuck, over
      fprintf(stderr, "Should not happen, unknown exception in text import");

      fclose(f);

      exit(1);
    }

  fclose(f);

  return 0;
}

// Default application initialization/deinitialization ------------------------
// File: APPINIT.CXX

#include "tfrmlib.hxx"

class CFreeStore;	// declare only

CFreeStore *App :: InitApp (CFreeStore *pFS)
{
	return pFS;
}


void App :: DeInitApp (void)
{
	// nothing to do
}
	

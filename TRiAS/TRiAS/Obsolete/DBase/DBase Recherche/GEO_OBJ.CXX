/*
File Geo_Obj.cxx

Ersatzvariante für alte Version in DLL.

Erarbeitet: J. Benkenstein					  Begonnen am 20. Juli 1993
												Stand vom 13. Nov. 1995
*/

#include "pheader.h"

#include "geo_obj.htp"			  	// Klassenselektion
#include <commonvu.hxx>
#include <ristypes.hxx>			 	// Koord	
#include <geo_obj.hxx>			  	// zugeh. Header

// OjbContainer ------------------------------------------------------------
ObjContainer :: ObjContainer (long Xmin, long Xmax, long Ymin, long Ymax) {
	_XMin = Xmin;
	_YMin = Ymin;
	_XMax = Xmax;
	_YMax = Ymax;
}


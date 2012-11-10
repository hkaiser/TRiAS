#pragma	HDR_ON()

#include "resource.h"
#include <resstrg.h>            // TRiAS Resourcen-Defines
//#include "../ExportStdResrc.h"
#include "TRiASArc.h"

//#include <Errcodes.hxx>	
//#include <xtension.h>
//#include <xtensnx.h>

//#include <zprotos.h>
#include <ristypes.hxx>

typedef char* pchar;	// Wird in ImpExp.hxx verwendet...
#include <ImpExp.hxx>

#include "TRiASArc.hxx"

#include "../ExportInl.h"
#include "../ExportOEIface.h"

#include <fstream.h>

ErrCode OutputWarnungIdent (short ResourceId, long Ident);
extern HPROJECT	hDatasource;			// Handle der aktuellen Datenquelle

#pragma	HDR_OFF()

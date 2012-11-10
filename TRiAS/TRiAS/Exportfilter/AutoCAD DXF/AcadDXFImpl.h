#pragma HDR_ON()

#include "resource.h"
#include <resstrg.h>            // TRiAS Resourcen-Defines
#include "AcadDXF.h"


//#include <Errcodes.hxx>	
//#include <xtension.h>
//#include <xtensnx.h>

//#include <zprotos.h>
#include <ristypes.hxx>

typedef char* pchar;	// Wird in ImpExp.hxx verwendet...
#include <ImpExp.hxx>

#include "AcadDxf.hxx"

#include "../ExportInl.h"
#include "../ExportOEIface.h"

ErrCode OutputWarnungIdent (short ResourceId, long ID, long ObjNr = 0); // Warnung ausgeben

#pragma HDR_OFF()

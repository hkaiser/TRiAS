//  Hilfsfunktionen
#include "stdafx.h"
#include "Hilfsfunktionen.h"

BOOL AcceptVartype(VARTYPE test)
{
    switch (test)
    {
    case    VT_UI1:
    case 	VT_I2:
    case    VT_I4:
    case    VT_R4:
    case    VT_R8:
            return TRUE;
        default:
            return FALSE;
    }
};

void calculatecenter(CComVariant& objcenter,CComVariant& objmin,CComVariant& objmax)
{
    int vt=objmin.vt;

    // Typ anpassen
    objmax.ChangeType(vt);
    objcenter.ChangeType(vt);

    switch (vt)
    {
        case    VT_UI1  : objcenter.bVal=(objmin.bVal+objmin.bVal)/2;break;
        case 	VT_I2   : objcenter.iVal=(objmin.iVal+objmin.iVal)/2;break;
        case    VT_I4   : objcenter.lVal=(objmin.lVal+objmin.lVal)/2;break;
        case    VT_R4   : objcenter.fltVal=(objmin.fltVal+objmin.fltVal)/2;break;
        case    VT_R8   : objcenter.dblVal=(objmin.dblVal+objmin.dblVal)/2;break;
    }
}

BOOL groesser(CComVariant& x,CComVariant& y,VARTYPE vt)
{
    switch (vt)
    {
        case    VT_UI1  : return x.bVal>y.bVal; 
        case 	VT_I2   : return x.iVal>y.iVal;
        case    VT_I4   : return x.lVal>y.lVal;
        case    VT_R4   : return x.fltVal>y.fltVal;
        case    VT_R8   : return x.dblVal>y.dblVal;
        default:
            return FALSE;
    }
}



BOOL kleiner(CComVariant& x,CComVariant& y,VARTYPE vt)
{
    switch (vt)
    {
        case    VT_UI1  : return x.bVal<y.bVal; 
        case 	VT_I2   : return x.iVal<y.iVal;
        case    VT_I4   : return x.lVal<y.lVal;
        case    VT_R4   : return x.fltVal<y.fltVal;
        case    VT_R8   : return x.dblVal<y.dblVal;
        default:
            return FALSE;
    }
}

bool operator<(CComVariant& x,CComVariant& y)
{
    VARTYPE vt = x.vt;
    y.ChangeType(vt);
    return kleiner(x,y,vt);
}

bool operator==(CComVariant& x,CComVariant& y)
{
    VARTYPE vt = x.vt;
    y.ChangeType(vt);
    if (kleiner(x,y,vt)||groesser(x,y,vt))
        return FALSE;
    else 
        return TRUE;
}

bool operator>(CComVariant& x,CComVariant& y)
{
    VARTYPE vt = x.vt;
    y.ChangeType(vt);
    return groesser(x,y,vt);
}

bool operator<=(CComVariant& x,CComVariant& y)
{
    VARTYPE vt = x.vt;
    y.ChangeType(vt);
    if (groesser(x,y,vt))
        return FALSE;
    else 
        return TRUE;
}

bool operator>=(CComVariant& x,CComVariant& y)
{
    VARTYPE vt = x.vt;
    y.ChangeType(vt);
    if (kleiner(x,y,vt))
        return FALSE;
    else 
        return TRUE;
}

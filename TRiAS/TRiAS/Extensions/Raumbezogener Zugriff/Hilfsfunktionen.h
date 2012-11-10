
//  Hilfsfunktionen
BOOL AcceptVartype(VARTYPE test);
void calculatecenter(CComVariant& objcenter,CComVariant& objmin,CComVariant& objmax);
BOOL groesser(CComVariant& x,CComVariant& y,VARTYPE vt);
BOOL kleiner(CComVariant& x,CComVariant& y,VARTYPE vt);
bool operator<(CComVariant& x,CComVariant& y);
bool operator==(CComVariant& x,CComVariant& y); 
bool operator>(CComVariant& x,CComVariant& y); 
bool operator<=(CComVariant& x,CComVariant& y); 
bool operator>=(CComVariant& x,CComVariant& y); 

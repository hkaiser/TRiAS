#include "stdafx.h"

ostream& operator<<( ostream& os, const TAG& t ) {
	if( t.Space() > 0 )
		os << " (" << t.Space() << ") ";
	switch( t.Type() ) {
	case -1			: os << "<leer>"; break;
	case _BYTE		: os << t.ubVal(); break;
	case _SHORT		: os << t.usVal(); break;
	case _LONG		: os << t.ulVal(); break;
	case _RATIONAL	: os << t.urVal().num << "/" << t.urVal().denom; break;
	case  _ASCII	: os << t.strVal(); break;

	case _SBYTE		: os << t.sbVal(); break;
	case _SSHORT	: os << t.ssVal(); break;
	case _SLONG		: os << t.slVal(); break;
	case _SRATIONAL	: os << t.srVal().num << "/" << t.srVal().denom; break;
	case _FLOAT		: os << t.fVal(); break;
	case _DOUBLE	: os << t.dVal(); break;
	}
	return os;
}

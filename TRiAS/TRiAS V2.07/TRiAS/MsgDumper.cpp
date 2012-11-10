// MessageDumper Funktionen für DEX_...-Trace
// File: MsgDumper.cpp

#include "triaspre.hxx"

#include <dirisole.h>
#include "extmain3.hxx"

// DefaultFunktion, welche Parameter nicht analysiert
LPCSTR ExtDirisWindow::DefaultMsgDumper (HPROJECT hPr, LPARAM lParam)
{
	return g_cbNil;
}


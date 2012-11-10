///////////////////////////////////////////////////////////////////////////
// @doc 
// @module VERSIONS.H | Datenbankversionen

#if !defined(_VERSIONS_H__351219D3_BCF9_11D1_85C1_00600875138A__INCLUDED_)
#define _VERSIONS_H__351219D3_BCF9_11D1_85C1_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if !defined(NEWDBVERSION)

///////////////////////////////////////////////////////////////////////////////
// GeoDB-Versionen
#define BASICRELEASENUM 0x05000000L
#define NEWDBVERSION    0x05000003L
#define VERSION05000004 0x05000004L
#define VERSION05000005 0x05000005L
#define VERSION05000006 0x05000006L
#define VERSION05000007 0x05000007L
#define VERSION05000008 0x05000008L
#define VERSION05000009 0x05000009L
#define VERSION0500000A 0x0500000AL
#define VERSION0500000B 0x0500000BL
#define VERSION0500000C 0x0500000CL		// Indirekte Texte in VERSION0500000B
#define VERSION0500000E 0x0500000EL
#define VERSION0500000F 0x0500000FL
#define VERSION05000010 0x05000010L

#define LASTDBVERSION   VERSION05000010

///////////////////////////////////////////////////////////////////////////////
// PbdDB-Versionen
#define PBDVERSION03000001      0x03000001L
#define PBDVERSION03000002      0x03000002L
#define PBDVERSION03000003      0x03000003L
#define PBDVERSION0500000A      0x0500000AL
#define PBDVERSION0500000B      0x0500000BL

///////////////////////////////////////////////////////////////////////////////
// Projekt (workspace-) Versionen
#define VERSION06000001	0x06000001L

#define LASTPROJECTVERSION	VERSION06000001

#endif // NEWDBVERSION

#endif // !defined(_VERSIONS_H__351219D3_BCF9_11D1_85C1_00600875138A__INCLUDED_)

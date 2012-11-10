// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.07.2000 13:06:30
//
// @doc
// @module makecolors.cpp | Farben für automatische Farbzuweisung generieren

#include <stdio.h>
#import "tlb/colors.tlb" no_namespace no_implementation raw_interfaces_only

class CWrapCom
{
public:
	CWrapCom() { CoInitialize(NULL); }
	~CWrapCom() { CoUninitialize(); }
};

CWrapCom WrapCom;

const double HUE_STEP = 18.;

void main()
{
	printf ("// $Header: $\n");
	printf ("// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved\n");
	printf ("// Created: 10.07.2000 12:12:01 \n");
	printf ("//\n");
	printf ("// @doc\n");
	printf ("// @module AutoColors.def | Farben, die der Reihe nach zugewiesen werden\n\n");

	printf ("#if !defined(_AUTOCOLORS_DEF__426A3743_E1E6_4CC8_9E23_30BD4E2B777B__INCLUDED_)\n");
	printf ("#define _AUTOCOLORS_DEF__426A3743_E1E6_4CC8_9E23_30BD4E2B777B__INCLUDED_\n\n");

	printf ("#if _MSC_VER >= 1000\n");
	printf ("#pragma once\n");
	printf ("#endif // _MSC_VER >= 1000\n\n");

	printf ("// Header include diagnostics\n");
	printf ("#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)\n");
	printf ("#pragma message(__TIME__\": include \" __FILE__ )\n");
	printf ("#endif\n\n");

	printf ("///////////////////////////////////////////////////////////////////////////////\n");
	printf ("// Farben, die der Reihe nach zugewiesen werden, wenn automatisch die \n");
	printf ("// nichtdefinierten Darstellungsparameter generiert werden\n");
	printf ("typedef struct tagAUTOCOLOR {\n");
	printf ("\tCOLORREF crMain;\n");
	printf ("\tCOLORREF crFill;\n");
	printf ("} AUTOCOLOR;\n\n");

	printf ("// Saturation = 1.0, Brightness(Main) = 0.8, Brightness(Fill) = 0.65\n");
	printf ("const AUTOCOLOR g_Colors[] = {\n");

IDoubleColorPtr ColorMain, ColorFill;

	ColorMain.CreateInstance (__uuidof(DoubleColor));
	ColorMain -> put_Brightness (0.8);
	ColorMain -> put_Saturation (1.0);

	ColorFill.CreateInstance (__uuidof(DoubleColor));
	ColorFill -> put_Brightness (0.65);
	ColorFill -> put_Saturation (1.0);

	for (int i = 0; i < 20; ++i) {
		ColorMain -> put_Hue (i * HUE_STEP);
		ColorFill -> put_Hue (i * HUE_STEP);
	
	long lRGBMain = 0;
	long lRGBFill = 0;
		
		ColorMain -> get_RGB(&lRGBMain);
		ColorFill -> get_RGB(&lRGBFill);
		printf ("\t{ 0x%06X, 0x%06X },\t\t// Hue = %.0f\n", lRGBMain, lRGBFill, i * HUE_STEP);
	}
	printf("};\n\n");
	printf("#endif // !defined(_AUTOCOLORS_DEF__426A3743_E1E6_4CC8_9E23_30BD4E2B777B__INCLUDED_)\n");
}

BEGIN	{
			iLine = 0;
			print "// $Header: $";
			print "// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, All rights reserved";
			print "// Created: 19.02.2002 16:35:01 ";
			print "//";
			print "// DO NOT EDIT -- this file is ALWAYS GENERATED !";
			print "//";
			print "// @doc";
			print "// @module TDBGeo.hh | Declaration of the helpcontext constants for TDBGeo";
			print "";

			print "#if _MSC_VER >= 1000";
			print "#pragma once";
			print "#endif // _MSC_VER >= 1000";
			print "";

			print "// Header include diagnostics";
			print "#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)";
			print "#pragma message(__TIME__\": include \" __FILE__ )";
			print "#endif";
			print "";
		}
		{
			printf "%s%ld\n", $0, ++iLine;
		}

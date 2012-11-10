BEGIN	{
			iLine = 0;
			print "// $Header: $";
			print "// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved";
			print "// Created: 20.03.2002 12:30:27 ";
			print "//";
			print "// DO NOT EDIT -- this file is ALWAYS GENERATED !";
			print "//";
			print "// @doc";
			print "// @module OleAuto.hh | Declaration of the helpcontext constants for TRiAS";
			print "";

            print "#if !defined(_OLEAUTO_HH__INCLUDED_)";
            print "#define _OLEAUTO_HH__INCLUDED_";
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
			printf "%s %s %ld\n", $1, $2, ++iLine;
		}
END     {
			print "";
            print "#endif // !defined(_OLEAUTO_HH__INCLUDED_)";
        }

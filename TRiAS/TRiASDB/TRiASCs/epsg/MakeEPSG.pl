use WIN32::ODBC;
use Getopt::Std;
Getopt::Std::getopts('w:ih') || die "Usage: $0 -w What";
use vars qw~$opt_i $opt_h~;
use strict;

my %What = (
	AngularUnit => {
		input => {qw~table UOM_ANGLE code UOM_ANGLE_CODE name UNIT_OF_MEAS_EPSG_NAME~}
		, output => {qw~typedef TRIASCSUNITOFANGLE prefix tcsUOA~}
		, implant => {
			'Second' => {qw~ID 32769~}
			}
	}
	, GeodeticDatum => {
		input => {qw~table GEOD_DATUM code GEOD_DATUM_CODE name GEOD_DAT_EPSG_NAME~}
		, output => {qw~typedef TRIASCSGEODETICDATUM prefix tcsGD~}
		, implant => {
			'User Defined' => {qw~ID 32769~}
			}
	}
	, PrimeMeridian => {
		input => {qw~table P_MERIDIAN code PRIME_MERIDIAN_CODE name PRIME_MERID_EPSG_NAME~}
		, output => {qw~typedef TRIASCSPRIMEMERIDIAN prefix tcsPM~}
	}
	, LengthUnit => {
		input => {qw~table UOM_LENGTH code UOM_LENGTH_CODE name UNIT_OF_MEAS_EPSG_NAME~}
		, output => {qw~typedef TRIASCSUNITOFLENGTH prefix tcsUOL~}
		, implant => {
			'Kilometer' => {qw~ID 32768~}
			, 'Centimeter' => {qw~ID 32767~}
			, 'Millimeter' => {qw~ID 32766~}
			}
	}
	, Ellipsoid => {
		input => {qw~table ELLIPSOID code ELLIPSOID_CODE name ELLIPSOID_EPSG_NAME~}
		, output => {qw~typedef TRIASCSELLIPSOID prefix tcsEL~}
		, implant => {
			'User Defined' => {qw~ID 32769~}
			}
	}
	, DatumTransformationAlgorithm => {
		input => {qw~table TRF_ALG_DTRANSFORM code COORD_TRF_METHOD_CODE name CTRF_METHOD_EPSG_NAME~}
		, output => {qw~typedef TRIASCSDTRANSALGORITHM prefix tcsDTA~}
	}
	, ProjectionAlgorithm => {
		input => {qw~table TRF_ALG_PROJEKTION code COORD_TRF_METHOD_CODE name CTRF_METHOD_EPSG_NAME~}
		, output => {qw~typedef TRIASCSPROJECTIONALGORITHM prefix tcsPA~}
		, implant => {
			'Gauss Krüger' => {
				ID => 32769
				, PARAM => {
					'Latitude of natural origin' => { 
						ID => 'tcsPP_TransverseMercator_LatitudeOfNaturalOrigin'
						, NAME => 'Latitude of natural origin'
					}
					, 'Longitude of natural origin' => { 
						ID => 'tcsPP_TransverseMercator_LongitudeOfNaturalOrigin'
						, NAME => 'Longitude of natural origin'
					}
					, 'Scale factor at natural origin' => { 
						ID => 'tcsPP_TransverseMercator_ScaleFactorAtNaturalOrigin'
						, NAME => 'Scale factor at natural origin'
					}
					, 'False easting' => {
						ID => 'tcsPP_TransverseMercator_FalseEasting'
						, NAME => 'False easting'
					}
					, 'False northing' => {
						ID => 'tcsPP_TransverseMercator_FalseNorthing'
						, NAME => 'False northing'
					}
				}
			}
			, 'Affine Transformation' => {
				ID => 32770
				, PARAM => {
					'ScaleX' => { ID => 0, 'NAME' => 'Skalierung X' }
					, 'ScaleY' => { ID => 1, 'NAME' => 'Skalierung Y' }
#					, 'ScaleZ' => { ID => 2, 'NAME' => 'Skalierung Z' }
					, 'RotatePhi' => { ID => 3, 'NAME' => 'Rotation Phi' }
#					, 'RotatePsi' => { ID => 4, 'NAME' => 'Rotation Psi' }
#					, 'RotateChi' => { ID => 5, 'NAME' => 'Rotation Chi' }
#					, 'DistA11' => { ID => 6, 'NAME' => 'Verzerrung a11' }
#					, 'DistA12' => { ID => 7, 'NAME' => 'Verzerrung a12' }
#					, 'DistA13' => { ID => 8, 'NAME' => 'Verzerrung a13' }
#					, 'DistA21' => { ID => 9, 'NAME' => 'Verzerrung a21' }
#					, 'DistA22' => { ID => 10, 'NAME' => 'Verzerrung a22' }
#					, 'DistA23' => { ID => 11, 'NAME' => 'Verzerrung a23' }
#					, 'DistA31' => { ID => 12, 'NAME' => 'Verzerrung a31' }
#					, 'DistA32' => { ID => 13, 'NAME' => 'Verzerrung a32' }
#					, 'DistA33' => { ID => 14, 'NAME' => 'Verzerrung a33' }
					, 'OffsetX' => { ID => 15, 'NAME' => 'Offset X' }
					, 'OffsetY' => { ID => 16, 'NAME' => 'Offset Y' }
#					, 'OffsetZ' => { ID => 17, 'NAME' => 'Offset Z' }
					}
				}
			, 'Cylindric Equirectangular' => {
				ID => 32771
				, PARAM => {
					'Latitude of natural origin' => { 
						ID => 'tcsPP_TransverseMercator_LatitudeOfNaturalOrigin'
						, NAME => 'Latitude of natural origin'
					}
					, 'Longitude of natural origin' => { 
						ID => 'tcsPP_TransverseMercator_LongitudeOfNaturalOrigin'
						, NAME => 'Longitude of natural origin'
					}
					, 'False easting' => {
						ID => 'tcsPP_TransverseMercator_FalseEasting'
						, NAME => 'False easting'
					}
					, 'False northing' => {
						ID => 'tcsPP_TransverseMercator_FalseNorthing'
						, NAME => 'False northing'
					}
				}
			}
		}
	}
);

my $D = new ODBC( "DSN=epsg_v40" );
die "undefined Datasource" unless defined( $D );

if( $opt_i ) {
	print qq~#include "stdafx.h"\n#include "TRiASCs.h"\n~;
	foreach( sort keys %What ) {
		next unless defined( $What{$_} );
		print STDERR "Implementation for $_\n";
		make_implementation( $D, $_ );
	}
	make_ellips( $D, 1 );
	make_PA_Attrib( $D );
	make_DT_Attrib( $D );
} elsif( $opt_h ) {
	print qq~cpp_quote("typedef struct { long code; LPCTSTR name; } CODENAME;")\n~;
	print qq~cpp_quote("typedef const CODENAME const *LPCCODENAME;")\n~;
	print qq~cpp_quote("typedef struct { long code; long param; } CODEPARAM;")\n~;
	print qq~cpp_quote("typedef const CODEPARAM const *LPCCODEPARAM;")\n~;
	print qq~cpp_quote("const short tcsPP_SizeOfParameterSet = 35;")\n~;
	print qq~cpp_quote("typedef struct PARAMETERSET { double p[tcsPP_SizeOfParameterSet];} PARAMETERSET;")\n~;
	print qq~cpp_quote("typedef const PARAMETERSET const *LPCPARAMETERSET;")\n~;
	print qq~cpp_quote("typedef struct { long code; PARAMETERSET p; } CODEPARAMSET;")\n~;
	print qq~cpp_quote("typedef const CODEPARAMSET const *LPCCODEPARAMSET;")\n~;
	foreach( sort keys %What ) {
		next unless defined( $What{$_} );
		print STDERR "Header for $_\n";
		make_header( $D, $_ );
	}
	make_PA_header( $D );
	make_DT_header( $D );
	make_ellips( $D, 0 );
	print qq~cpp_quote("typedef struct PA_ATTRIBUTESET { TRIASCSPROJECTIONALGORITHM pa; TRIASCSPROJECTIONPARAMETER pp; LPCTSTR value; } PA_ATTRIBUTESET;")\n~;
	print qq~cpp_quote("typedef const PA_ATTRIBUTESET const *LPCPA_ATTRIBUTESET;")\n~;
	print qq~cpp_quote("typedef struct DT_ATTRIBUTESET { TRIASCSDTRANSALGORITHM ta; TRIASCSDTRANSPARAMETER tp; LPCTSTR value; } DT_ATTRIBUTESET;")\n~;
	print qq~cpp_quote("typedef const DT_ATTRIBUTESET const *LPCDT_ATTRIBUTESET;")\n~;
	print qq~cpp_quote("extern DT_ATTRIBUTESET _DT_ATTRIBUTES[];")\n~;
	print qq~cpp_quote("extern PA_ATTRIBUTESET _PA_ATTRIBUTES[];")\n~;
}

$D->Close();

##########################################################################
# aus einem Feldnamen einen symbolischen Namen erzeugen

sub make_symbolic_name {
	my($name,$prefix) = @_;
	my($delim) = ('_');

	$name =~ s/ä/ae/g;
	$name =~ s/ö/oe/g;
	$name =~ s/ü/ue/g;
	$name =~ s/Ä/Ae/g;
	$name =~ s/Ö/Oe/g;
	$name =~ s/Ü/Ue/g;
	$name =~ s/ß/sz/g;
	$name =~ s/([^a-zA-Z0-9_]+)([a-zA-Z0-9_])/uc($2)/eg;
	$name =~ s/^([a-zA-Z0-9_])/uc($1)/e;
	$name =~ s/[^a-zA-Z0-9_]+$//;
	$name = qq~$prefix$delim$name~;
	return $name;
}

##########################################################################
# Definitionen die mit dem Ellipsoid zusammenhängen

sub make_ellips {
	my($D,$impl) = @_;

	##########################################################################
	# Header wird erzeugt
	if( !$impl ) {
		print qq~cpp_quote("extern CODEPARAM _PT_ELLIPSFROMGD[];")\n~;
		print qq~cpp_quote("extern CODEPARAMSET _PT_ELLIPSPARAM[];")\n~;
		return;
	}
	##########################################################################
	# Implementation wird erzeugt

	my($S,$SymName,$SymName2,%D);
	############################################################################
	# Teil1 -> Zuordnung Ellipsoid zu geod. Datum
	$S = qq~SELECT G.GEOD_DAT_EPSG_NAME, G.ELLIPSOID_EPSG_NAME FROM G_DATUM G~;

	if( $D->Sql($S) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~CODEPARAM _PT_ELLIPSFROMGD[] = {\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		$SymName = make_symbolic_name( $D{GEOD_DAT_EPSG_NAME}, 'tcsGD' );
		$SymName2 = make_symbolic_name( $D{ELLIPSOID_EPSG_NAME}, 'tcsEL' );
		print qq~\t{ $SymName, $SymName2 },\n~;
	}
	print qq~\t{ tcsGD_Undefined, tcsEL_Undefined }\n};\n~;

	############################################################################
	# Teil2 -> Definition der Ellipsoide
	$S = qq~SELECT E.ELLIPSOID_EPSG_NAME, E.SEMI_MAJOR_AXIS, E.SEMI_MINOR_AXIS, E.INV_FLATTENING AS FLATTENING FROM ELLIPSOID E~;

	if( $D->Sql($S) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~CODEPARAMSET _PT_ELLIPSPARAM[] = {\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		if( $D{SEMI_MAJOR_AXIS} and $D{SEMI_MINOR_AXIS} ) {
			$D{FLATTENING} = ( $D{SEMI_MAJOR_AXIS} - $D{SEMI_MINOR_AXIS} ) / $D{SEMI_MAJOR_AXIS};
		} elsif( $D{SEMI_MAJOR_AXIS} and $D{FLATTENING} ) {
			$D{FLATTENING} = 1 / $D{FLATTENING};
			$D{SEMI_MINOR_AXIS} = $D{SEMI_MAJOR_AXIS} * ( 1 - $D{FLATTENING} );
		} else {
			next;
		}
		$SymName = make_symbolic_name( $D{ELLIPSOID_EPSG_NAME}, 'tcsEL' );
		print qq~\t$SymName, { $D{SEMI_MAJOR_AXIS}, $D{SEMI_MINOR_AXIS}, $D{FLATTENING} },\n~;
	}
	print qq~\ttcsEL_Undefined, {0}\n};\n~;
}

############################################################################
# Parameterindizies für Datumstransformationsalgorithmen

sub make_DT_header {
	my($D) = @_;
	my(%D,%P,$SymName,$SymName2);
	my $nParam;
	my $S = qq~SELECT * FROM TRF_ALG_DTRANSFORM~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~// \@doc ENUM TRIASCS\n~
		, qq~// \@enum TRIASCSDTRANSPARAMETER | TRIASCSDTRANSPARAMETER\n~
		, qq~typedef enum TRIASCSDTRANSPARAMETER {\n~
		, qq~\ttcsDTP_Undefined = -1, // \@emem Wert ist nicht definiert\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		%P = ();
		foreach( keys %D ) {
			if( /PARAM_([0-9]+)_NAME/ ) {
				next unless( $D{$_} );
				$P{param}{$1} = $D{$_};
			} elsif ( 'COORD_TRF_METHOD_CODE' eq $_ ) {
				$P{code} = $D{$_};
			} elsif( 'CTRF_METHOD_EPSG_NAME' eq $_ ) {
				$P{name} = $D{$_};
			}
		}
		$SymName = make_symbolic_name( $P{name}, 'tcsDTP' );
		$P{name} =~ s/\.//g;
		print qq~// \@xref <l $P{name}>\n~;
		foreach( keys %{$P{param}} ) {
			$nParam = $_ - 1;
			$SymName2 = make_symbolic_name( $P{param}{$_}, $SymName );
			print qq~\t$SymName2 = $nParam, // \@emem $P{param}{$_} <l $P{name}>\n~;
		}
	}
	print qq~} TRIASCSDTRANSPARAMETER;\n~;
}

##########################################################################
# Feldnamen für die Datumstransformationsalgorithmen

sub make_DT_Attrib {
	my($D) = @_;
	print STDERR "Implementation for Datumtransformation Attributes\n";
	my(%D,%P,$SymName,$SymName1,$SymName2);
	my($nParam, $i);
	my $S = qq~SELECT * FROM TRF_ALG_DTRANSFORM~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~DT_ATTRIBUTESET _DT_ATTRIBUTES[] = {\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		%P = ();
		foreach( keys %D ) {
			if( /PARAM_([0-9]+)_NAME/ ) {
				next unless( $D{$_} );
				$P{param}{$1} = $D{$_};
			} elsif ( 'COORD_TRF_METHOD_CODE' eq $_ ) {
				$P{code} = $D{$_};
			} elsif( 'CTRF_METHOD_EPSG_NAME' eq $_ ) {
				$P{name} = $D{$_};
			}
		}
		$SymName1 = make_symbolic_name( $P{name}, 'tcsDTA' );
		$SymName2 = make_symbolic_name( $P{name}, 'tcsDTP' );
		for( $i = 1; $i <= 34; $i++ ) {
			if( $P{param}{$i} ) {
				$SymName = make_symbolic_name( $P{param}{$i}, $SymName2 );
				print qq~{$SymName1, $SymName, _T("$P{param}{$i}")},\n~;
			}
		}
	}
	print qq~{tcsDTA_Undefined, tcsDTP_Undefined, NULL}\n};\n~;
}

############################################################################
# Parameterindizies für Projektionsalgorithmen

sub make_PA_header {
	my($D) = @_;
	my(%D,%P,$SymName,$SymName2);
	my $nParam;
	my $S = qq~SELECT * FROM TRF_ALG_PROJEKTION~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~// \@doc ENUM TRIASCS\n~
		, qq~// \@enum TRIASCSPROJECTIONPARAMETER | TRIASCSPROJECTIONPARAMETER\n~
		, qq~typedef enum TRIASCSPROJECTIONPARAMETER {\n~
		, qq~\ttcsPP_Undefined = -1, // \@emem Wert ist nicht definiert\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		%P = ();
		foreach( keys %D ) {
			if( /PARAM_([0-9]+)_NAME/ ) {
				next unless( $D{$_} );
				$P{param}{$1} = $D{$_};
			} elsif ( 'COORD_TRF_METHOD_CODE' eq $_ ) {
				$P{code} = $D{$_};
			} elsif( 'CTRF_METHOD_EPSG_NAME' eq $_ ) {
				$P{name} = $D{$_};
			}
		}
		$SymName = make_symbolic_name( $P{name}, 'tcsPP' );
		$P{name} =~ s/\.//g;
		print qq~// \@xref <l $P{name}>\n~;
		foreach( keys %{$P{param}} ) {
			$nParam = $_ - 1;
			$SymName2 = make_symbolic_name( $P{param}{$_}, $SymName );
			print qq~\t$SymName2 = $nParam, // \@emem $P{param}{$_} <l $P{name}>\n~;
		}
	}
	my $impl;
	foreach $impl ( keys %{$What{ProjectionAlgorithm}{implant}} ) {
		print qq~// \@xref <l $impl>\n~;
		$SymName = make_symbolic_name( $impl, 'tcsPP' );
		foreach( sort keys %{$What{ProjectionAlgorithm}{implant}{$impl}{PARAM}} ) {
			$SymName2 = make_symbolic_name( $_, $SymName );
			print qq~\t$SymName2 = $What{ProjectionAlgorithm}{implant}{$impl}{PARAM}{$_}{ID}, // \@emem $_ <l $impl>\n~;
		}
	}
	print qq~} TRIASCSPROJECTIONPARAMETER;\n~;
}

##########################################################################
# Feldnamen für die Projektionsalgorithmen

sub make_PA_Attrib {
	my($D) = @_;
	print STDERR "Implementation for Projectionalgorithm Attributes\n";
	my(%D,%P,$SymName,$SymName1,$SymName2);
	my($nParam, $i);
	my $S = qq~SELECT * FROM TRF_ALG_PROJEKTION~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}
	print qq~PA_ATTRIBUTESET _PA_ATTRIBUTES[] = {\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		%P = ();
		foreach( keys %D ) {
			if( /PARAM_([0-9]+)_NAME/ ) {
				next unless( $D{$_} );
				$P{param}{$1} = $D{$_};
			} elsif ( 'COORD_TRF_METHOD_CODE' eq $_ ) {
				$P{code} = $D{$_};
			} elsif( 'CTRF_METHOD_EPSG_NAME' eq $_ ) {
				$P{name} = $D{$_};
			}
		}
		$SymName1 = make_symbolic_name( $P{name}, 'tcsPA' );
		$SymName2 = make_symbolic_name( $P{name}, 'tcsPP' );
		for( $i = 1; $i <= 34; $i++ ) {
			if( $P{param}{$i} ) {
				$SymName = make_symbolic_name( $P{param}{$i}, $SymName2 );
				print qq~{$SymName1, $SymName, _T("$P{param}{$i}")},\n~;
			}
		}
	}
	my $impl;
	foreach $impl ( keys %{$What{ProjectionAlgorithm}{implant}} ) {
		$SymName1 = make_symbolic_name( $impl, 'tcsPA' );
		$SymName2 = make_symbolic_name( $impl, 'tcsPP' );
		foreach( sort keys %{$What{ProjectionAlgorithm}{implant}{$impl}{PARAM}} ) {
			$SymName = make_symbolic_name( $_, $SymName2 );
#			print qq~{$SymName1, $SymName, _T("$What{ProjectionAlgorithm}{implant}{$impl}{PARAM}{$_}{NAME}")},\n~;
			print qq~{$SymName1, $SymName, _T("$What{ProjectionAlgorithm}{implant}{$impl}{PARAM}{$_}{NAME}")},\n~;
		}
	}
	print qq~{tcsPA_Undefined, tcsPP_Undefined, NULL}\n};\n~;
	return;
print <<'EOF';
{tcsPA_GaussKrueger, tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, _T("Latitude of natural origin")},
{tcsPA_GaussKrueger, tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, _T("Longitude of natural origin")},
{tcsPA_GaussKrueger, tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, _T("Scale factor at natural origin")},
{tcsPA_GaussKrueger, tcsPP_GaussKrueger_FalseEasting, _T("False easting")},
{tcsPA_GaussKrueger, tcsPP_GaussKrueger_FalseNorthing, _T("False northing")},
EOF
}

############################################################################
# erzeugt aus einer Definition (siehe %What-Hash) die entsprechende Implementation

sub make_implementation {
	my($D,$what) = @_;
	my($SymName,%D);

	my $S = qq~SELECT $What{$what}{input}{code} as code, $What{$what}{input}{name} AS name \nFROM $What{$what}{input}{table} \nORDER BY $What{$what}{input}{code}~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}

	print qq~CODENAME _CT_$What{$what}{output}{typedef}\[\] = {\n~;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		$SymName = make_symbolic_name( $D{name}, $What{$what}{output}{prefix} );
		$D{name} = qq~_T("$D{name}")~;
		print qq~\t{ $SymName, $D{name} },\n~;
	}
	foreach( keys %{$What{$what}{implant}} ) {
		$SymName = make_symbolic_name( $_, $What{$what}{output}{prefix} );
		print qq~\t{ $SymName, _T("$_") },\n~;
	}
	print qq~\t{ $What{$what}{output}{prefix}_Undefined, NULL }\n};\n~;
}

############################################################################
# erzeugt aus einer Definition (siehe %What-Hash) den entsprechenden Header

sub make_header {
	my($D,$what) = @_;
	my($SymName,%D);

	my $S = qq~SELECT $What{$what}{input}{code} as code, $What{$what}{input}{name} AS name \nFROM $What{$what}{input}{table} \nORDER BY $What{$what}{input}{code}~;
	if( $D->Sql( $S ) ) {
		print STDERR $S, "\n";
		return undef;
	}

	print qq~cpp_quote("extern CODENAME _CT_$What{$what}{output}{typedef}\[\];")\n~
		, qq~// \@doc ENUM TRIASCS\n~
		, qq~// \@enum $What{$what}{output}{typedef} | $What{$what}{output}{typedef}\n~
		, qq~typedef enum $What{$what}{output}{typedef} {\n~
		, qq~\t$What{$what}{output}{prefix}_Undefined = -1, // \@emem Wert ist nicht definiert\n~
		;
	while( $D->FetchRow() ) {
		%D = $D->DataHash();
		$SymName = make_symbolic_name( $D{name}, $What{$what}{output}{prefix} );
		print ''
			#, qq~\t\t// \@doc ENUM TRIASCS $What{$what}{output}{prefix} $SymName\n~
			, qq~\t$SymName = $D{code}, // \@emem $D{name}\n~
		;
	}
	foreach( keys %{$What{$what}{implant}} ) {
		$SymName = make_symbolic_name( $_, $What{$what}{output}{prefix} );
		print qq~\t$SymName = $What{$what}{implant}{$_}{ID},  // \@emem $_\n~;
	}
print <<"END";
} $What{$what}{output}{typedef};
END
}

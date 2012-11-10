#!/usr/bin/perl -w

use strict;

use lib qw(./modules);

use MakeASC;
use MapOptions;

require "dumpvar.pl";

#@ARGV=(qw(-s Koethen -B SaAnh -T TKN));
####################################################################
# $makeASC ist das eigentliche Arbeitstier,
# $mapOptions bereitet die übergebenen Optionen auf

my($makeASC,$mapOptions);
my $param = {};

$makeASC = new MakeASC or die qq(MakeASC-Objekt kann nicht erstellt werden\n);
$mapOptions = new MapOptions or die qq(Objekt zur Optionsauswertung kann nicht erstellt werden\n);

####################################################################
# nur wenn Optionen auswerten *und* Aufgabe abarbeiten erfolgreich
# waren mit '0' zurück

$mapOptions->process_options( $param )
	and $makeASC->process_request( $param )
	and 0 == BaseObject::ERRORS()
	and exit(0)
	;

####################################################################
# anderenfalls gab es Fehler; diese ausgeben

print join( "\n", BaseObject::ERRORS() ), "\n";

__END__

#!/usr/bin/perl -w

use strict;

use lib qw(./modules);

use MakeCD;
use MapOptions;

require "dumpvar.pl";

####################################################################
# $makeCD ist das eigentliche Arbeitstier,
# $mapOptions bereitet die übergebenen Optionen auf

my($makeCD,$mapOptions);
my $param = {};

$makeCD = new MakeCD or die qq(MakeCD-Objekt kann nicht erstellt werden\n);
$mapOptions = new MapOptions or die qq(Objekt zur Optionsauswertung kann nicht erstellt werden\n);

####################################################################
# nur wenn Optionen auswerten *und* Aufgabe abarbeiten erfolgreich
# waren mit '0' zurück

$mapOptions->process_options( $param )
	and $makeCD->process_request( $param )
	and 0 == BaseObject::ERRORS()
	and exit(0)
	;

####################################################################
# anderenfalls gab es Fehler; diese ausgeben

print join( "\n", BaseObject::ERRORS() ), "\n";

__END__


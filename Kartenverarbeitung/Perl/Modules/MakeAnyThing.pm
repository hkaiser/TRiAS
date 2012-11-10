package MakeAnyThing;

use strict;
use vars qw(@ISA $VERSION);
use BaseObject;

@ISA=qw(BaseObject);
$VERSION="1.0";

use File::Basename;
use File::Find;
use Cwd;
use Config;

sub new {
	my($class,$param)=@_;
	my $self = {};
	bless $self, ref $class || $class || 'MakeAnyThing';
	return $self->init( $param );
}

sub init {
	my($self,$param)=@_;
	return $self;
}

=head1 NAME

MakeAnyThing.pm - Basismodul für die Aufbereitung von Rasterbildern

=head1 SYNTAX

 use strict;
 use MakeAnyThing;
 use vars(@ISA);
 @ISA=(MakeAnyThing);

 sub MakeAnyThing {
 	my($self,$Map)=@_;
	# ...
 }

=head1 BESCHREIBUNG

C<MakeAnyThing> ist Basismodul für die Aufbereitung von Rasterbildern.
Die eigentlichen Arbeitsmodule werden von C<MakeAnyThing> abgeleitet.
C<MakeAnyThing> traversiert das angegebene Quellverzeichnis, ermittelt
für gefundene B<Tiff>-Dateien die notwendigen Informationen (Bild-, und
Karteninformationen, Quelldatei, Zieldatei usw.) und ruft für jede
gefundene und einem Kartenschema entsprechende Datei die Funktion 
C<MakeAnyThing> im abgeleiteten Modul. Damit ist eine einheitliche
Bearbeitung der Rasterbilddateien gesichert.

=cut

####################################################################
# mfn - (m)ake (f)ile(n)ame - vollständigen Dateinamen aus
# Pfad / Name / Extension liefern
sub mfn { my $self=shift; return qq($_[0]->[0]$_[0]->[1]$_[0]->[2]); }

####################################################################
# die Aufgabe abarbeiten

sub process_request {
	my($self,$P) = @_;

	$P->{mapType} or return $self->ERROR( qw(ERR_MISSINGARG mapType) );
	$P->{mapLayer} or return $self->ERROR( qw(ERR_MISSINGARG mapLayer) );
	$P->{sourceDir} or return $self->ERROR( qw(ERR_MISSINGARG sourceDir) );
	$P->{mapInfo} or return $self->ERROR( qw(ERR_MISSINGARG mapInfo) );

	####################################################################
	# von hier aus wird gestartet
	$P->{cwd} = getcwd();

	####################################################################
	# benutzte Verzeichnisnamen verschönern
	foreach( qw(cwd sourceDir destDir) ) {
		next unless $P->{$_};
		$P->{$_} =~ tr@[\\]@/@;			# UN*X - Stil ist uns lieber ;-)
		$P->{$_} .= q(/) unless $P->{$_} =~ /.*\/$/;
	}

	####################################################################
	# wo können temporäre Dateien Angelegt werden?
	my $tmp = $ENV{TMP} ? $ENV{TMP} :
				$ENV{TEMP} ? $ENV{TEMP} :
				$P->{cwd}
				;
	$tmp =~ tr@[\\]@/@;			# wie gesagt ... i like UN*X ;-))
	for( 0..0 ) { push( @{$P->{tmpFiles}}, [$tmp, qq(/tmpTiff$_), '.tif'] ); }

	####################################################################
	# das abgeleitete Objekt kann vorverarbeiten
	$self->pre_process( $P ) or return $self->ERROR( q(ERR_CANNOTPREPROCESS) );

	####################################################################
	# Zähler für bearbeitete Objekte / Karten
	$P->{N} = 0;

	####################################################################
	# damit die Dateinamen auch richtig ausgewertet werden...
	fileparse_set_fstype($Config{osname});

	####################################################################
	# das Verzeichnis durchackern
	File::Find::finddepth(sub { $self->process_file( $P ); },$P->{sourceDir});

	####################################################################
	# das abgeleitete Objekt kann nachbearbeiten
	$self->post_process( $P );

	####################################################################
	# die Reste beseitigen
	foreach( @{$P->{tmpFiles}} ) {
		unlink( $self->mfn($_) ) if( -e $self->mfn($_) );
	}

	####################################################################
	# und raus
	return scalar $BaseObject::ERRORS ? undef : $self;
}

####################################################################
# eine einzelne Datei abarbeiten
sub process_file {
	my($self,$P) = @_;

	####################################################################
	# beim Traversieren steht die aktuell gefundene Datei in
	# '$File::Find::name'. Momentan werden nur Tiff-Dateien bearbeitet.
	return unless( $File::Find::name =~ /\.(tif)$/i );

	####################################################################
	# Kartenzähler erhöhen und Zeiger auf die aktuelle Karte besorgen
	my $M = $P->{++$P->{N}} = {};

	####################################################################
	# Pfad der aktuellen Datei nachbearbeiten
	# p,n,s -> (P)fad, (N)ame, (S)uffix
#	$M->{source} = $M->{inFile} = $File::Find::name;
	$M->{inFile} = $File::Find::name;
	$M->{inFile} =~ tr/A-Z/a-z/;
	$M->{source} = $M->{inFile};
	$M->{inFile} =~ tr@[\\]@/@;				# Backslash zu Slash
	$M->{outFile} = $M->{inFile};
	my($n,$p,$s) = fileparse( $M->{inFile},('.tif'));
	$M->{inFile} = [$p, $n, $s];
	$M->{outFile} = [$p, $n, $s];

	####################################################################
	# als Standard nehmen wir an:
	$M->{isa} = 'UNKNOWN';
	$M->{scale} = 'UNKNOWN';
	$M->{picture} = {};
	$M->{ident} = qq($n);
	$M->{layer}{name} = q(co);
	$M->{layer}{oks} = 0;
	$M->{layer}{description} = q(unbekannter Layer oder Farbkarte);

	####################################################################
	# Der Name der Quelldatei muß ein absoluter Pfadname sein
	if( $M->{inFile}[0] =~ /.:.*/ ) {
	}
	else {
		$M->{inFile}[0] = qq($P->{cwd}$M->{inFile}[0]);
	}

	####################################################################
	# dito der Name der Zieldatei; der muß aber auch noch von der Quelle
	# zum Ziel umgemapt werden
	if( $P->{destDir} ) {
		$M->{outFile}->[0] =~ s/^$P->{sourceDir}/$P->{destDir}/i;	
		if( $M->{outFile}[0] =~ /.:.*/ ) {
		}
		else {
			$M->{outFile}[0] = qq($P->{cwd}$M->{outFile}[0]);
		}
	}

	####################################################################
	# jetzt die einzelnen Module die Karte bearbeiten lassen und
	# versuchen soviel wie möglich an Informationen rauszuholen
	# !!!ACHTUNG!!! Die Module können den Ausgabedateinamen umbauen.
	if( $P->{mapLayer} ) {
		if( not $P->{mapLayer}->ident_from_path( $M, $M ) ) {
			$self->WARN( 'WARN_LAYER', $M->{source} );
			return $self;
		}
	}
	if( $P->{mapType} ) {
		if( not $P->{mapType}->ident_and_path( $M, $M ) ) {
			$self->WARN( 'WARN_MAPTYPE', $M->{source} );
			return $self;
		}
	}
	if( $P->{docType} ) {
		if( not $P->{docType}->read_info( {filename=>$M->{inFile}}, $M ) ) {
			$self->WARN( 'WARN_DOCTYPE', $M->{source} );
			return $self;
		}
	}
	($n,$p,$s) = fileparse( join('',@{$M->{outFile}} ), q(.tif) );
	$M->{outFile} = [$p, $n, $s];

	####################################################################
	# eindeutiger Identifikator
# fje	$M->{uniqueident} = qq($M->{isa}\@$M->{layer}{schema}:$M->{layer}{name}\@$M->{ident});
	if ( 'co' eq $M->{layer}{name} ) {
		$M->{uniqueident} = qq($M->{isa}\@$M->{layer}{schema}:$M->{layer}{name}\@$M->{ident});
	}
	else {
		$M->{uniqueident} = qq($M->{isa}\@$M->{layer}{schema}:$M->{layer}{name}\@$M->{ident}$M->{layer}{name});
	}
	####################################################################
	# Wenn's eine Layerkarte ist muß der Originaldateiname benutzt
	# werden, sonst überschreiben sich die Dateien gegenseitig.
	$M->{outFile}->[1] .= $M->{layer}{name} unless( 'co' eq $M->{layer}{name} );

	####################################################################
	# sonstige Karteninformationen holen
	$P->{mapInfo}->read( {filename=>$self->mfn($M->{inFile})}, $M->{picture} ) or return $self->ERROR( 'ERR_UNKNOWN', '' );
	$M->{picture}{269} = $M->{ident};
	$M->{picture}{270} = qq($M->{isa}\@$P->{mapLayerSchema}\@$M->{ident});

	####################################################################
	# 
	$M->{verbose} = $P->{verbose};
	$M->{DEBUG} = $P->{DEBUG};
	$M->{tmpFiles} = $P->{tmpFiles};
	$M->{CUSTOM} = $P->{CUSTOM} if( $P->{CUSTOM} );
	$M->{NUMBER} = $P->{N};
	$M->{quality} = $P->{quality};
	$M->{histFile} = $P->{histFile};
	$M->{ROTATION} = $P->{ROTATION};
	$M->{OMIT} = $P->{OMIT};

	####################################################################
	# das ist das eigentliche Arbeitstier
	$self->MakeAnyThing( $M ) or return $self->ERROR( ('ERR_PROCESSINGFAILED', $M->{inFile}[1] ) );

	####################################################################
	# Mr. Propper ranlassen
	foreach( qw(inFile outFile tmpFiles verbose DEBUG CUSTOM) ) { delete $M->{$_}; }
	foreach( qw(NAMES TAGS TYPES) ) { delete $P->{mapInfo}{$_}; }

	#::dumpValue(\$P);
	return $self;
}

####################################################################
# der Basismodul kann einfach mal nichts

sub MakeAnyThing { my $self=shift; return $self->ERROR( qw(ERR_PUREVIRT) ) };
sub pre_process { my $self=shift; return $self->ERROR( qw(ERR_PUREVIRT) ) };
sub post_process { my $self=shift; return $self->ERROR( qw(ERR_PUREVIRT) ) };

BEGIN {
$MakeAnyThing::ERRORS = q(
ERR_CANNOTPREPROCESS
	de	Vorverarbeitung gescheitert
WARN_DOCTYPE
	de	[%s]: Verarbeitung des Begleitdokumentes gescheitert.
WARN_LAYER
	de	[%s]: Verarbeitung des Layers gescheiter.
WARN_MAPTYPE
	de	[%s]: unbekannter Kartentyp.
);
	BaseObject::init_errmsg( $MakeAnyThing::ERRORS );
}

1;

__END__

package MapOptions;

use strict;
use vars qw(@ISA $VERSION);
use BaseObject;

@ISA=qw(BaseObject);
$VERSION="1.0";

use Cwd;			# (C)urrent (w)orking (d)irectory
use Getopt::Std;	# Auswertung v. Kommandozeilenoptionen 
use MapInfo;
use MapType;
use	MapLayer;
use DocType;

sub new {
	my($class,$param)=@_;
	my $self = {};
	bless $self, ref $class || $class || q(MapOtions);
	return $self->init( $param );
}

sub init {
	my($self,$param)=@_;
	return $self;
}

=head1 NAME MapOptions

Wertet Standardoptionen für Perl-Skripte zur Kartenbearbeitung aus.

=head1 SYNTAX

 use MapOptions;
 my($MapOptions,$param)=(undef,{});
 $mapOptions = new MapOptions or die q(kann MapOptions-Objekt nicht erstellen);
 $mapOptions->process_options( $param );

=head1 METHODEN

=item B<process_options( [in,out] $param )>

Liest die Kommandozeilenoptionen aus und setzt sie in 'programmiererlesbare'
Werte um. Diese werden im anonymen Hash C<$param> abgelegt.
Die Umsetzung der Optionen wird unter L<"OPTIONEN"> beschrieben.
Für die einzelnen Optionen ist jeweils beschrieben auf welchem Namen
sie im übergebenen Hash abgebildet werden; z.B. liest sich B<T =E<gt> mapType>
als: I<Die Option B<T> wird auf den Wert B<mapType> abgebildet>.

=head1 OPTIONEN

=cut

sub process_options {
	my($self,$P)=@_;

	my $O = {};
	Getopt::Std::getopts('s:d:q:Rv:O:B:L:T:H:X:Dv', $O );

	####################################################################
	# MapInfo wird immer gebraucht
	$P->{mapInfo} = new MapInfo or return $self->ERROR( qq(ERR_CANNOTCREATE MapInfo) );

	####################################################################
	# von hier aus wird gestartet
	$P->{cwd} = getcwd();

	####################################################################
	# Kartentyp

=item B<T =E<gt> mapType>

Kartentyp - L<MapType>

=cut

	if( $O->{T} ) {
		$P->{mapType} = MapTypeFactory::CreateInstance( $O->{T} ) or
			return $self->ERROR( qw(ERR_INVALIDOPT T), join( ",", sort @{&MapTypeFactory::EnumClasses()} ) );
	} else {
		$self->WARN( qw(WARN_MISSINGOPT T Kartentyp) );
		$P->{mapType} = MapTypeFactory::CreateInstance( q(UNKNOWN) )
			or return $self->ERROR( qw(ERR_CANNOTCREATEINSTANCE MapType::UNKNOWN) );
	}

	####################################################################
	# Layerschema; wird auf 'Color' gesetzt wenn nichts anderes gegeben

=item B<L =E<gt> mapLayer>

Layerschema - L<MapLayer>

=cut

	if( $O->{L} ) {
		$P->{mapLayerSchema} = $O->{L};
		$P->{mapLayer} = MapLayerFactory::CreateInstance( $O->{L} )
			or return $self->ERROR( qw(ERR_INVALIDOPT L), join( ",", sort @{&MapLayerFactory::EnumClasses()} ) );
	} else {
		$self->WARN( qw(WARN_MISSINGOPT L Layerschema) );
		$P->{mapLayerSchema} = q(Color);
		$P->{mapLayer} = MapLayerFactory::CreateInstance( q(Color) )
			or return $self->ERROR( qw(ERR_CANNOTCREATEINSTANCE MapLayer::Color) );
	}

	####################################################################
	# Typ der Begleitdatei

=item B<B =E<gt> docType>

Begleitdatei - L<DocType>

=cut

	if( $O->{B} ) {
		$P->{docType} = DocTypeFactory::CreateInstance( $O->{B} )
			or return $self->ERROR( qw(ERR_INVALIDOPT B), join(",", sort @{&DocTypeFactory::EnumClasses()} ) );
	} else {
		$self->WARN( qw(WARN_MISSINGOPT B Begleitdatei) );
	}

	####################################################################
	# Quell/Zielverzeichnis; Ziel muß nicht gegeben sein

=item B<s =E<gt> sourceDir>

Quellverzeichnis - dieses Verzeichnis wird rekursiv durchgegangen
und jede gefundene und entsprechend C<mapType> und C<mapLayer> passende
Datei bearbeitet.

=cut

	$O->{s} or return $self->ERROR( qw(ERR_MISSINGOPT s Quellverzeichnis) );
	$P->{sourceDir} = $O->{s};

=item B<d =E<gt> destDir>

Zielverzeichnis - hier werden die bearbeiteten Dateien abgelegt.
Die Verzeichnisstruktur muß B<nicht> zwangsläufig mit der des
Quellverzeichnisses übereinstimmen.

=cut

	$self->WARN( qw(WARN_MISSINGOPT d Zielverzeichnis) ) unless $O->{d};
	$P->{destDir} = $O->{d} if( $O->{d} );

	####################################################################
	# Histogrammdatei (muß nicht angegeben werden; Beschwerde kommt schon
	# wenn sie gebraucht wird)
	
=item B<H =E<gt> histFile>

Für die Farbreduktion von RGB-Dateien muß ein vorberechnetes
Farbmodell verwendet werden. Dieses kann hier angegeben werden;
als Standard wird F<resources/Standard.mif> verwendet.

=cut

	$P->{histFile} = $P->{cwd} . '/resources/Standard.mif';

croak (
<<"EOF"
Die Histogrammdatei 'Standard.mif' wird jetzt im Verzeichnis
'resources' erwartet. Sie müßte sich noch unter
\n\te:/Daten/CD_ROM/_Raw/Standard.mif\n
befinden. Bitte die Datei an den richtigen Platz verschieben!
EOF
) unless ( -e $P->{histFile} );

	$P->{histFile} = $O->{H} if( $O->{H} );

	####################################################################
	# Qualitätsparameter (Standard 4)

=item B<q =E<gt> quality>

Qualitätsparameter für die Größenreduktion. Dieser sollte bei
Farbkarten B<immer> auf B<4> gesetzt sein. Bei schwarz/weiß - Bildern
kann je nach Bild und Parameter ein besseres oder schlechteres
Ergebnis erzielt werden (hier wird die 'Ausdünnung' schwarzer Linien
bzw. Flächen gesteuert. Einfach mal probieren ;-))

=cut

	$P->{quality} = 4;
	$P->{quality} = $O->{q} if( $O->{q} );

	####################################################################
	# Rotation... die eigentliche Karte liegt gedreht in der Datei

=item B<R =E<gt> ROTATION>

Rotations-Modus - die eigentliche Karte liegt gedreht in der Datei und der Kartenrahmen wird anders berechnet.

=cut

	$P->{ROTATION} = 0;
	$P->{ROTATION} = 1 if( $O->{R} );

	####################################################################
	# DEBUG... na eben Debug-Ausgaben

=item B<D =E<gt> DEBUG>

Debug-Modus - es werden ausführliche Meldungen angezeigt,
es wird aber nicht real gearbeitet.

=cut

	$P->{DEBUG} = 0;
	$P->{DEBUG} = $O->{D} if( $O->{D} );


	####################################################################
	# Omitt... auszulassende Verarbeitungsschritte
=item B<O =E<gt> OMIT>

Verbose - ausführliche Meldungen über den Ablauf anzeigen.

=cut

	$P->{OMIT} = 0;
	$P->{OMIT} = 1 if( $O->{O}  and 'R' eq uc($O->{O}) );

=item B<X =E<gt> makeTXI, makeTXM>

TXI / TXM Datei erzeugen

=cut

	$P->{makeTXI} = 1 if( $O->{X} and 'I' eq uc($O->{X}) );
	$P->{makeTXM} = 1 if( $O->{X} and 'M' eq uc($O->{X}) );

=item B<v =E<gt> verbose>

Verbose - ausführliche Meldungen über den Ablauf anzeigen.

=cut

	$P->{verbose} = 0;
	$P->{verbose} = $O->{v} if( $O->{v} or $O->{D} );

=item B<X =E<gt> makeTXI, makeTXM>

TXI / TXM Datei erzeugen

=cut

	$P->{makeTXI} = 1 if( $O->{X} and 'I' eq uc($O->{X}) );
	$P->{makeTXM} = 1 if( $O->{X} and 'M' eq uc($O->{X}) );

	return $self;
}

BEGIN {
$MapOptions::ERRMSG = q(
ERR_CANNOTCREATE
	de	Objekt vom Typ [%s] kann nicht erstellt werden
ERR_MISSINGOPT
	de	Option [-%s] (%s) muß angegeben werden
ERR_INVALIDOPT
	de	Fehlerhafte Option [-%s]; möglich: [%s]
WARN_MISSINGOPT
	de	Option [-%s] (%s) wurde nicht angegeben; die Ergebnisse könnten unerwartet sein
);
}
	BaseObject::init_errmsg( $MapOptions::ERRMSG );
1;

__END__

package MapLayer;

use strict;
use Carp;
use vars qw(@ISA $VERSION);

use BaseObject;

@ISA=qw(BaseObject);
$VERSION="1.0";

BEGIN {
my $ERRMSGS = q(
ERR_INVALIDIDENT
	de	Fehlerhafte Nomenklatur %s
ERR_LAYERNOTFOUND
	de	[%s]: [%s] wurde als Layer erkannt, ist aber nicht definiert.
);
	BaseObject::init_errmsg( $ERRMSGS );

	sub read_layers {
		my($layers,$var)=@_;
		my @layers = split("\n", $layers );
		my($layer,$code,@param);
		foreach( @layers ) {
			next if( /^\s*$/ or /^\s*#.*$/ );
			s/^\s*//;
			@param = split( /\t/ );
			$code = shift(@param);
			next if( '--' eq $code );
			$var->{$code} = [@param];
		}
	}
}

sub new {
	my($class,@param)=@_;
	my $self = {};
    bless $self,ref $class || $class;
	return $self->init(@param);
}

sub DESTROY {
	1;
}

sub init {
	my($self,@param)=@_;
	return $self;
}

=head1 NAME

MapLayer.pm - Ermittlung von Nomenklatur und Layer aus einem Kartennamen

=head1 SYNTAX

 use MapLayer;

 my($mapLayer,$mapData);

 $mapLayer = MapLayerFactory::CreateInstance( 'SaAnh' ) or die $@;

 $mapData = {inFile=>['any/path/', 'c4334gg', '.tif']};

 $theMap->ident_from_path( $mapData, $mapData ) or die $@;

=head1 BESCHREIBUNG

Die 'MapLayer' - Module ermitteln für einen Kartennamen die Kartennomenklatur
und den zugehörigen Layer.

Bestimmte Karten werden in getrennten Layern geliefert
wobei meist aus dem Dateinamen selbst ersichtlich ist welchen Layer
die Datei repräsentiert. Z.B. entspricht die Datei C<C4335gg.tif>
im Layerschema B<SaAnh> dem Layer B<gg> =E<gt> B<Geodät. Grundl. / Freist. / Schrift>.

=head1 METHODEN

=over 16

=cut

sub ident_from_path { my $self = shift; return $self->PUREVIRT(); }

=head2 B<ident_from_path( $inParam, $outParam )>

Ermittelt für einen gegebenen Dateinamen die zugehörige Kartennomenklatur
und den (ggf. enthaltenen Layer). Diese Trennung ist notwendig um die
korrekte Arbeit der 'MapType'-Module zu ermöglichen. Z.B. beschreibt
I<path/to/the/file/c4334gg.tif> eine top. Karte N (I<c4334>) im Layer I<gg>
(geod. Grundlage, Freistellung, Schrift) entsprechend der Definitionen des
LVermA Sachsen-Anhalt.

=head2 I<In-Parameter>

=item C<$param->{inFile}>

Ein anonymes Array für den Dateinamen wobei die Arrayelemente in der Reihenfolge
den Pfad, den Dateinamen und die Dateierweiterung enthalten.

=head2 I<Out-Parameter>

=item C<$param->{ident}>

Die vollständige Nomenklatur.

=item C<$param->{layer}>

Der Layer.

=head1 INITIALISIERUNG

Die einzelnen Module initialisieren ihre Definitionen in einem 'BEGIN' - Block.
Dazu steht die Funktion C<read_layers( $layers, $var )> zur Verfügung:

	BEGIN {
		my $layers = q(
		gr	0	Grundriß
		sr	1	Schrift
		);
		MapLayer::read_layers( $Layers, $MapLayer::SaAnh = {} );
	}

Die Layerdefinition (liegt als Text in der Variablen $layers vor) wird mittels
C<MapLayer::read_layers> in die Variable C<$MapLayer::SaAnh> übernommen.
Eine Layerdefinition besteht pro Zeile aus drei mit Tabulator getrennten Spalten:

	1. Spalte: die Kurzbezeichnung des Layers
	2. Spalte: der zugehörige Teil des Objektklassenschlüssels
	3. Spalte: eine lange Beschreibung des Layers

=cut

1;

package MapLayerFactory;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(BaseObjectFactory);
$VERSION="1.0";

$MapLayerFactory::BASEDIR = 'MapLayer';

sub CreateInstance {
	return BaseObjectFactory::CreateInstance( $MapLayerFactory::BASEDIR, $_[0] );
}

sub EnumClasses {
	return BaseObjectFactory::EnumClasses( $MapLayerFactory::BASEDIR );
}

1;

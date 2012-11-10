package MapLayer::SaAnh2;

use strict;
use vars qw(@ISA $VERSION);

use MapLayer;

@ISA=qw(MapLayer);
$VERSION="1.0";

BEGIN {
my $Layers=q(
		###################################################################
		# Standard-Arc-Info-tfw's des LVermA Sachsen-Anhalt
		--	1	Grundriß
		--	13	Schrift
		hy	23	Gewässer / Freist. / Schrift
		--	21	Gewässerkontur
		hf	22	Gewässerfläche
		--	23	Gewässerschrift
		re	3	Höhenlinien
		wa	4	Wald
		--	c	Freist. Maske schwarz
		--	9	Geodätische Grundlage
		gr	1	Grundriß / Freistellung
		--	9	Geodät. Grundl. / Freist.
		gg	93	Geodät. Grundl. / Freist. / Schrift
		gb	5	Gebäudedecker
		gz	6	Grenze
		hs	f	Herstellerlayer
	);
	MapLayer::read_layers( $Layers, $MapLayer::SaAnh::Layers = {} );
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

sub ident_from_path {
	my($self,$I,$O) = @_;
	$I->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );
	$I->{inFile}[1] =~ /(.*[0-9])([a-z][a-z])$/;
	return undef unless $2;
	$MapLayer::SaAnh::Layers->{$2} or return $self->ERROR( ('ERR_LAYERNOTFOUND', $I->{inFile}[1], $2) );
	$O->{ident} = $1;
	$O->{layer}{name} = $2;
	$O->{layer}{oks} = $MapLayer::SaAnh::Layers->{$2}[0];
	$O->{layer}{schema} = q(SaAnh);
	$O->{layer}{description} = $MapLayer::SaAnh::Layers->{$2}[1];
	return $self;
}

1;


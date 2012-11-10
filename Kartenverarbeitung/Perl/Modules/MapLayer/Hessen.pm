package MapLayer::Hessen;

use strict;
use vars qw(@ISA $VERSION);

use MapLayer;

@ISA=qw(MapLayer);
$VERSION="1.0";

BEGIN {
my $Layers = q(
	##################################################################
	# top. Karten Hessen 
	co	0	Farbe
	gd	1	Gewässerdecker
	gk	2	Gewässerkontur
	hl	3	Höhenlinen
	si	4	Situation
	wf	5	Waldflächen
	vg	6	Verwaltungsgrenzen
);
	MapLayer::read_layers( $Layers, $MapLayer::Hessen::Layers = {} );
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
	$I->{inFile}[1] =~ /(.*[0-9]{4})([a-z][a-z])$/;
	return undef unless $2;
	$MapLayer::Hessen::Layers->{$2} or return $self->ERROR( ('ERR_LAYERNOTFOUND', $I->{inFile}[1], $2) );
	$O->{ident} = $1;
	$O->{layer}{name} = $2;
	$O->{layer}{oks} = $MapLayer::Hessen::Layers->{$2}[0];
	$O->{layer}{schema} = q(Hessen);
	$O->{layer}{description} = $MapLayer::Hessen::Layers->{$2}[1];
	return $self;
}

1;

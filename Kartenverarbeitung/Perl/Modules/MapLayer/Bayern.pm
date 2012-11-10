package MapLayer::Bayern;

use strict;
use vars qw(@ISA $VERSION);

use MapLayer;

@ISA=qw(MapLayer);
$VERSION="1.0";

BEGIN {
my $Layers = q(
	###################################################################
	# Bayerisches LVermA
	co	0	Farbkarte
	gr	1	Grundriß
	gk	4	Gewässerkontur
	gd	5	Gewässerfläche
	wa	7	Waldfläche
	hl	8	Höhenlinien
);
	MapLayer::read_layers( $Layers, $MapLayer::Bayern::Layers = {} );
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
	$MapLayer::Bayern::Layers->{$2} or return $self->ERROR( ('ERR_LAYERNOTFOUND', $I->{inFile}[1], $2) );
	$O->{ident} = $1; 
	$O->{layer}{name} = $2;
	$O->{layer}{oks} = $MapLayer::Bayern::Layers->{$2}[0];
	$O->{layer}{schema} = q(Bayern);
	$O->{layer}{description} = $MapLayer::Bayern::Layers->{$2}[1]; 
	return $self;
}

1;

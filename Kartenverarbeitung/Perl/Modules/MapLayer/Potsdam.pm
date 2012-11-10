package MapLayer::Potsdam;

use strict;
use vars qw(@ISA $VERSION);

use MapLayer;

@ISA=qw(MapLayer);
$VERSION="1.0";

BEGIN {
my $Layers = q(
	###################################################################
	# topogr. Stadtplan 1:10000 Potsdam (LVermA Brandenburg)
	gru	1	Grundriß
	kns	9	Kartennamen Schwarz
	sro	a	Strassendecker Rot
	gew	4	Gewässer
	rel	8	Relief
	wal	6	Waldflächen
);
	MapLayer::read_layers( $Layers, $MapLayer::Potsdam = {} );
}

sub new {
	my($class,@param)=@_;
	my $self = {};
	bless $self,ref $class || $class;
	return $self->init(@param);
}

sub init {
	my($self,@param)=@_;
	return $self;
}

sub ident_from_path {
	my($self,$I,$O) = @_;
	$I->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );
	$I->{inFile}[1] =~ /^pots([0-9])([a-z][a-z][a-z])$/i;
	return undef unless $2;
	return undef unless $MapLayer::Potsdam->{$2};
	$O->{ident} = $2;
	$O->{layer}{name} = $1;
	$O->{layer}{oks} = $MapLayer::Potsdam->{$2}[0];
	$O->{layer}{schema} = q(Potsdam);
	$O->{layer}{description} = $MapLayer::Potsdam->{$2}[1];
	return $self;
}

1;

package MapLayer::Color;

use strict;
use vars qw(@ISA $VERSION);

use MapLayer;

@ISA=qw(MapLayer);
$VERSION="1.0";

BEGIN {
my $Layers = q(
);
	MapLayer::read_layers( $Layers, $MapLayer::Color = {} );
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
	$O->{ident} = $I->{inFile}[1];
	$O->{layer}{name} = 'co';
	$O->{layer}{oks} = 0;
	$O->{layer}{schema} = q(Color);
	$O->{layer}{description} = q(Farbkarte);
	return $self;
}

1;

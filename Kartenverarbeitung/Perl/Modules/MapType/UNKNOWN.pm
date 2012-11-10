package MapType::UNKNOWN;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(MapType);
$VERSION="1.0";

use MapType;
use File::Basename;

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

sub TRiASCS {
	my($self,$CS)=@_; $CS->{COORDSYSTEM} = q(UNKNOWN); return $self;
}

#################################################################################
# ermittelt Pfadnamen und Nomenklatur

sub ident_and_path {
	my($self,$I,$O) = @_;
	$I->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );
	$O->{isa} = 'UNKNOWN';
	$O->{scale} = 'UNKNOWN';
	$O->{ident} = $O->{outFile}[1] = $I->{inFile}[1];
	return $self;
}

#################################################################################
# Ermittelt aus einem Pfadnamen die Nomenklatur

sub ident_from_path {
	my($self,$IP,$OP) = @_;
	$IP->{path} or return $self->ERROR( 'ERR_MISSINGARG', 'path' );
	my($n,$p,$s) = fileparse( $IP->{path}, qw(.tif .TIF) );
	$OP->{ident} = $n;
	return $self;
}

#################################################################################
# Ermittelt aus einer Koordinate die Nomenklatur

sub ident_from_coord {
	my($self,$IP,$OP)=@_;
	$IP->{scale} or return $self->ERROR( 'ERR_MISSINGARG', 'scale' );
	$IP->{lon} or return $self->ERROR( 'ERR_MISSINGARG', 'lon' );
	$IP->{lat} or return $self->ERROR( 'ERR_MISSINGARG', 'lat' );
	return undef;
}

#################################################################################
# Erzeugt aus Nomenklatur einen Pfadnamen

sub path_from_ident {
	my($self,$IP,$OP)=@_;
	$IP->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );
	$OP->{path} = $IP->{ident};
	return $self;
}

#################################################################################
# ermittelt Maßstab für eine bestimmte Nomenklatur

sub scale_from_ident {
	my($self,$IP,$OP)=@_;
	$IP->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );
	return undef;
}

#################################################################################
# ermittelt Koordinaten und Ausdehnung für eine bestimmte Nomenklatur

sub coord_from_ident {
	my($self,$IP,$OP)=@_;
	$IP->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );
	return undef;
}

1;

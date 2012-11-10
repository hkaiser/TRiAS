package MapType::ATKIS;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(MapType);
$VERSION="1.0";

use MapType;
use File::Basename;

sub new {
	my($class)=@_;
	my $self = {};
    bless $self,ref $class || $class;
    return $self->init();
}

sub DESTROY {
	1;
}

sub init {
	my($self)=@_;
	$self->{SCALES} = {
		order => [qw~10000~]
		,  10000 => '([1-4][0-9][0-9][0-9][0-9][0-9])'
	};
	return $self;
}

#################################################################################
# ermittelt Pfadnamen und Nomenklatur

sub ident_and_path {
	my($self,$IP,$OP) = @_;
	$IP->{path} or return $self->ERROR( 'ERR_MISSINGARG', 'path' );

	my($n,$p,$s) = fileparse( $IP->{path}, qw(.tif .TIF) );

	my($path,$ident,$scale);
	$path = qq~$p$n~;

	foreach $scale ( @{$self->{SCALES}{order}} ) {
		if( $path =~ /$self->{SCALES}{$scale}/ and $& ) {
			$ident=$&;
			last;
		}
	}
	return undef unless defined $ident;
	$OP->{path} = $path;
	$OP->{ident} = $ident;
	return $self;
}

#################################################################################
# Ermittelt aus einem Pfadnamen die Nomenklatur

sub ident_from_path {
	my($self,$IP,$OP)=@_;
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
	
	use integer;
	$OP->{ident} = sprintf( "%03d%03d", $IP->{lon} / 10000, $IP->{lat} / 10000 );
	return $self;
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
# ATKIS ist immer 1:25000

sub scale_from_ident {
	my($self,$IP,$OP)=@_;
	$IP->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );
	$OP->{scale} = 10000;
	return $self;
}

#################################################################################
# ermittelt Koordinaten und Ausdehnung für eine bestimmte Nomenklatur
# ATKIS-Blätter beginnen an einer vollen 10km-Grenze, d.h. von den vollen
# GK - 7-stellern werden nur drei Stellen benötigt; in der Nomenklatur geben
# die ersten drei Stellen den Rechtswert, die letzten drei Stellen den Hochwert
# an.

sub coord_from_ident {
	my($self,$IP,$OP)=@_;
	$IP->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );
	$IP->{ident} =~ /([0-9]{3,3})([0-9]{3,3})/;
	$1 and $2 or return $self->ERROR( 'ERR_INVALIDIDENT', $IP->{ident} );
	use integer;
	$OP->{LLR} = $1 * 10000;
	$OP->{LLH} = $2 * 10000;
	$OP->{DR} = 10000;
	$OP->{DL} = 10000;
	return $self;
}

1;

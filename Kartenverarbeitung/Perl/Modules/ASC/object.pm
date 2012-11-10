package ASC::object;

require Exporter;
use strict;
use Carp;

use vars qw(@ISA @EXPORT @EXPORT_OK $AUTOLOAD);
@ISA = qw(BaseObject);

use BaseObject;

BEGIN {
$ASC::object::TYPES = {
	qw(
		P Point
		F Area
		L Line
		B Text
		)
	};
}

sub new {
	my($class,$param)=@_;
	my $self = {};
	bless $self,ref $class || $class;
	return $self->init($param);
}

sub DESTROY {
	1;
}

sub init {
	my($self,$P)=@_;
	$P->{type} or return $self->ERROR(qw(ERR_MISSINGARG type));
	$P->{oks} or return $self->ERROR(qw(ERR_MISSINGARG oks));
	$P->{number} or return $self->ERROR(qw(ERR_MISSINGARG number));
	defined $ASC::object::TYPES->{$P->{type}} or return $self->ERROR(q(ERR_UNKNOWNTYPE), $P->{type} );
	$self->{TYPE} = $P->{type};
	$self->{CLASS} = $P->{oks};
	$self->{NUMBER} = $P->{number};
	return $self;
}

sub set_ident {
	my($self,$P)=@_;
	$P->{ident} or return $self->ERROR(qw(ERR_MISSINGARG ident));
	$self->{IDENT} = $P->{ident};
	return $self;
}

sub set_name {
	my($self,$P)=@_;
	$P->{name} or return $self->ERROR(qw(ERR_MISSINGARG name));
	$self->{NAME} = $P->{name};
	return $self;
}

sub set_coords {
	my($self,$P)=@_;
	$P->{coords} or return $self->ERROR(qw(ERR_MISSINGARG coords));
	$self->{COORDS} = [@{$P->{coords}}];
	return $self;
}

sub set_property {
	my($self,$P)=@_;
	$P->{name} or return $self->ERROR(qw(ERR_MISSINGARG name));
	$P->{value} or return $self->ERROR(qw(ERR_MISSINGARG value));
	$self->{MCODES}{$P->{name}} = $P->{value};
	return $self;
}

sub print_asc {
	my($self,$nObject,$H)=@_;
	my $nCoord = ( $#{$self->{COORDS}} + 1 ) / 2;
	if( 0 == $nCoord ) {
		print ";-----------------------------------------------------\n"
			, "; Undefined Object at $nObject (zero Coords)\n"
			, "; Class: $self->{CLASS}\n"
			, "; Type: $self->{TYPE}\n"
			, "; IDENT: $self->{IDENT}\n"
			;
		return;
	}
	#############################################################
	# P - Punkt
	# F - Fläche
	# L - Linie
	# B - Text
	if( 'P' eq $self->{TYPE} ) {
		print qq~P $nObject "$self->{CLASS}" 1\n~;
	}elsif( 'F' eq $self->{TYPE} ) {
		print qq~F $nObject "$self->{CLASS}" $nCoord\n~;
	}elsif( 'L' eq $self->{TYPE} ) {
		print qq~L $nObject "$self->{CLASS}" $nCoord\n~;
	}elsif( 'B' eq $self->{TYPE} ) {
		print qq~B $nObject "$self->{CLASS}" 1\n~;
		print qq~I "$self->{NAME}"\n~;
	}else{
		print ";-----------------------------------------------------\n"
			, "; Undefined Object at $nObject (unknown Type)\n"
			, "; Class: $self->{CLASS}\n"
			, "; Type: $self->{TYPE}\n"
			, "; IDENT: $self->{IDENT}\n"
			;
		return undef;
	}
	$self->print_asc_mcode( $H->{'Unique Ident'}, $self->{IDENT} );
	$self->print_asc_mcode( $H->{'ObjName'}, $self->{NAME} ) unless( 'B' eq $self->{TYPE} );
	foreach( sort { $a > $b ? 1 : $a < $b ? -1 : 0} keys %{$self->{MCODES}} ) {
		$self->print_asc_mcode( $_, $self->{MCODES}{$_} );
	}
	$nCoord = 0;
	foreach( @{$self->{COORDS}} ) {
		if( $nCoord % 2 == 0 ) {
			print "\n" if( $nCoord > 0 );
			print "G";
		}
		printf(" %.8lf", $_ );
		$nCoord++;
	}
	print "\n";
}

sub print_asc_mcode {
	my($self,$code,$val)=@_;
	my $len = length($val);

	print qq~M $code 1 A $len\n~;
	while( length( $val ) > 64 ) {
		print "W \"", substr($val,0,32), "\"\n";
		$val = substr( $val, 64 );
	}
	print qq~W "$val"\n~;
}

1;

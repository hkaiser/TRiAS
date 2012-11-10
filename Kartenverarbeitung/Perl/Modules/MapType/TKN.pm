package MapType::TKN;

use strict;
use vars qw(@ISA $VERSION);
use MapType;

@ISA=qw(MapType);
$VERSION="1.0";

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
	return $self;
}

sub TRiASCS {
	my($self,$P)=@_;
	$P->{COORDSYSTEM} = q(BESSELGK);
	return $self;
}

#################################################################################
# ermittelt Pfadnamen und Nomenklatur

sub ident_and_path {
	my($self,$I,$O) = @_;

	$I->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );

	my $path=qq~$I->{ident}~;
	my($scale,$ident);

	foreach ( @{$MapType::TKN::SCALES->{order}} ) {
		if( $path =~ /$MapType::TKN::SCALES->{$_}/ and $& ) {
			$O->{isa} = 'TKN';
			$O->{scale} = $_;
#			$O->{ident} = $O->{outFile}[1] = $2 ? qq($1\_$2) : qq($1);
			$O->{ident} = $O->{outFile}[1] = $2 ? qq($1$2) : qq($1);
			last;
		}
	}
	return undef unless defined $O->{ident};
	$self->coord_from_ident( $O, $O );
	return $self;
}

#################################################################################
# Ermittelt aus einer Koordinate die Nomenklatur

sub ident_from_coord {
	my($self,$I,$O)=@_;
	
	$I->{scale} or return $self->ERROR( 'ERR_MISSINGARG', 'scale' );
	$I->{X} or return $self->ERROR( 'ERR_MISSINGARG', 'X' );
	$I->{Y} or return $self->ERROR( 'ERR_MISSINGARG', 'Y' );

	my($scale,$Long,$Lat)=($I->{scale},$I->{X},$I->{Y});

	my(@S,@Q,@R,@N);
	use integer;
	@Q=($Lat,$Long);
	my(%quad,@zones);
	%quad = (
		  10000 => {qw~0 3 1 1 10 4 11 2~}
		, 25000 => {qw~0 c 1 a 10 d 11 b~}
		, 50000 => {qw~0 C 1 A 10 D 11 B~}
		);
	@zones=('A'..'Z');
#	@N=($Lat.'\\\\n'.$Long.'\\\\n');
	foreach( @{$MapType::TKN::NList} ) {
		@S=($MapType::TKN::MList->{$_}[0],$MapType::TKN::MList->{$_}[1]);
		@R=( $Q[0] % $S[0], $Q[1] % $S[1] );
		@Q=( $Q[0] / $S[0], $Q[1] / $S[1] );
		#print ";", join( ", ", @Q, @R ), "\n";
		if( 1000000 == $_ ) {
			@N = (@N, $zones[$Q[1]],$Q[0]+31 );
		} elsif( 100000 == $_ ) {
			@N = (@N, ( 12 - $Q[1] ) * 12 + $Q[0] - 11 );
		} elsif( 50000 == $_ ) {
			@N = (@N, $quad{50000}{10*$Q[0] + $Q[1]} );
		} elsif( 25000 == $_ ) {
			@N = (@N, $quad{25000}{10*$Q[0] + $Q[1]} );
		} elsif( 10000 == $_ ) {
			@N = (@N, $quad{10000}{10*$Q[0] + $Q[1]} );
		}
		last if( $scale eq $_ );
		@Q=@R;
	}
	$O->{ident} = join("-",@N);
	return $self;
}

#################################################################################
# ermittelt Koordinaten und Ausdehnung für eine bestimmte Nomenklatur
# 1:200000	CC-nnnn
# 1:100000	C-nnnn
# 1:50000	L-nnnn
# 1:25000	nnnn
# 1:10000	nnnn-qq
# wobei für *alle* Maßstäbe 1:25000 ausschlaggebend ist: Bei kleineren Maßstäben
# wird 'nnnn' durch das *links unten* liegende 1:25000'er Blatt festgelegt;
# 1:10000 wird durch das umschließende 1:25000'er Blatt festgelegt
#
# !!!WARNUNG!!!
# Momentan ist die Implementierung fürchterlich vereinfacht; es wird nicht
# abgetestet ob z.B. eine gegebene 1:100000'er Nomenklatur auch wirklich gültig ist

sub coord_from_ident {
	my($self,$I,$O)=@_;
	$I->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );

	#################################################################################
	# Nomenklatur normalisieren
	my $ident = $I->{ident};
	$ident =~ s/[^A-Za-z0-9]/_/g;
	$ident = lc($ident);

	my($scale,$M25000);

	foreach ( @{$MapType::TKN::SCALES->{order}} ) {
		if( $ident =~ /$MapType::TKN::SCALES->{$_}/ and $& ) {
			$scale =$_;
			$M25000 = 10000 == $scale || 25000 == $scale ? $1 : $2;
			last;
		}
	}
	return undef unless $scale;

	my($QR,$QH)=(0,0);

	$QR = $MapType::TKN::MList->{$scale}[0] / 2 if( 10000 == $scale and ( 'no' eq $2 or 'so' eq $2 ) );
	$QH = $MapType::TKN::MList->{$scale}[1] / 2 if( 10000 == $scale and ( 'nw' eq $2 or 'no' eq $2 ) );
	
	$O->{DR} = $MapType::TKN::MList->{$scale}[0];
	$O->{DH} = $MapType::TKN::MList->{$scale}[1];

	$M25000 =~ /([0-9][0-9])([0-9][0-9])/;

	$O->{M25000} = $M25000;
	$O->{LLR} = 201240 - $1 *360 + $QR;
	$O->{LLH} = 21400 + 600 * $2 + $QH;

	$O->{scale} = $scale;
	$O->{URR} = $O->{LLR} + $O->{DR};
	$O->{URH} = $O->{LLH} + $O->{DH};
	return $self;
}

BEGIN {
my $errMsgs = q(
);
	BaseObject::init_errmsg( $errMsgs );

	$MapType::TKN::SCALES = {
		order => [qw~10000 200000 100000 50000 25000~]
		,  10000 => '^([1-8][0-9][0-5][0-9])_*([ns][ow])'
		, 200000 => '^([c][c])*([1-8][0-9][0-5][0-9])'
		, 100000 => '^([c])*([1-8][0-9][0-5][0-9])'
		,  50000 => '^([l])*([1-8][0-9][0-5][0-9])'
		,  25000 => '^([1-8][0-9][0-5][0-9])'
	};
	$MapType::TKN::MList = {
			10000 => [qw~300 180~]
			, 25000 => [qw~600 360~]
			, 50000 => [qw~1200 720~]
			, 100000 => [qw~2400 1440~]
			, 200000 => [qw~4800 2880~]
	};
	$MapType::TKN::NList = [qw~200000 100000 50000 25000 10000~];
}

1;

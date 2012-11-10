package MapType::TKAS;

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
	return $self;
}

sub TRiASCS {
	my($self,$P)=@_;
	$P->{COORDSYSTEM} = q(KRGEOD);
	return $self;
}

#################################################################################
# Pfadnamen so formatieren daß kein Bestandteil länger als 8 Zeichen ist
# 1. wegen 8.3-Konvention
# 2. wegen logisch sinnvoller Verteilung der Karten (sind dann nicht alle auf
#    einem Haufen)

sub ident_and_path {
	my($self,$I,$O) = @_;

	$I->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );

	my $path = qq($I->{inFile}[0]$I->{inFile}[1]);
	$path =~ s/[^A-Za-z0-9]/_/g;	# Sonderzeichen zu '_'
	$path =~ tr/[A-Z]/[a-z]/;		# groß zu klein

	#################################################################################
	# versuchen eine passende Karte zu finden
	my($scale,$ident);

	foreach ( @{$MapType::TKAS::SCALES->{order}} ) {
		if( $path =~ /$MapType::TKAS::SCALES->{$_}/ and $& ) {
			$scale = $_;
			$ident = $1;
			last;
		}
	}
	return undef unless defined $ident;

	#################################################################################
	# Jetzt aus gefundener Nomenklatur Pfadnamen und korrekte Nomenklatur synthetisieren

	my %delims = (
		2 => ' _'
		, 3 => ' _ /'
		, 4 => ' _ / _ _'
		, 5 => ' _ _ / _ _'
		, 6 => ' _ _ / _ _'
		);

	my($Part, $nPart, $newPath, $delim );

	my @prefixParts = split( /[^a-zA-Z0-9]/, $ident );
	my @delims = split( / /, $delims{$#prefixParts} );
	# print "DELIMS $#prefixParts ", join( ":", @delims ), "\n";
	$newPath = "";
	$ident = '';
	$nPart = 0;
	my($D2) = '';
	while( @prefixParts ) {
		$Part = shift( @prefixParts );
		next if( "" eq $Part );
		$delim = shift( @delims );
		if( 0 == $nPart or 3 == $nPart ) {
			$Part = uc($Part);
		} elsif ( 4 == $nPart ) {
			$Part = lc($Part)
		} elsif( 1 == $nPart ) {
			$D2 = '-';
		}
		$newPath .= $delim . $Part;
		$ident .= $D2 . $Part;
		$nPart++;
	}
	$O->{isa} = 'TKAS';
	$O->{scale} = $scale;
	$O->{ident} = $ident;
	$O->{outFile}[1] = $newPath;
	$self->coord_from_ident( $O, $O );
	return $self;
}

#################################################################################
# Ermittelt aus einer Koordinate die Nomenklatur

sub ident_from_coord {
	my($self,$I,$O)=@_;
	$I->{scale} or return $self->ERROR( 'ERR_MISSINGARG', 'scale' );
	$I->{lon} or return $self->ERROR( 'ERR_MISSINGARG', 'lon' );
	$I->{lat} or return $self->ERROR( 'ERR_MISSINGARG', 'lat' );

	my($scale,$Lon,$Lat)=($I->{scale},$I->{lon},$I->{lat});

	my(@S,@Q,@R,@N);
	use integer;
	@Q=($Lon,$Lat);
	my(%quad,@zones);
	%quad = (
		  10000 => {qw~0 3 1 1 10 4 11 2~}
		, 25000 => {qw~0 c 1 a 10 d 11 b~}
		, 50000 => {qw~0 C 1 A 10 D 11 B~}
		);
	@zones=('A'..'Z');
#	@N=($Lon.'\\\\n'.$Lat.'\\\\n');
	foreach( @{$self->{NList}} ) {
		@S=($self->{MList}{$_}[0],$self->{MList}{$_}[1]);
		@R=( $Q[0] % $S[0], $Q[1] % $S[1] );
		@Q=( $Q[0] / $S[0], $Q[1] / $S[1] );
#		print ";", join( ", ", @Q, @R ), "\n";
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
#	return join("-",@N);
	$O->{ident} = join("-",@N);
}

#################################################################################
# ermittelt Koordinaten und Ausdehnung für eine bestimmte Nomenklatur

sub coord_from_ident {
	my($self,$I,$O)=@_;
	$I->{ident} or return $self->ERROR( 'ERR_MISSINGARG', 'ident' );

	#################################################################################
	# Nomenklatur normalisieren
	my $ident = $I->{ident};
	$ident =~ s/[^A-Za-z0-9]/_/g;
	$ident = lc($ident);

	my($scale);

	use integer;

	my(@ident)=split('_',$ident);
	my($x,$y,$dx,$dy)=(0,0,0,0);
	my($c,%c) = (0,());

	foreach( ('a'...'z') ) { $c{$_} = $c++; }
	my $idx = 0;

	while( $#ident > -1 ) {
		$c = splice(@ident,0,1);
		if( 0 == $idx ) {								# 1:1000000
			$y = ( 4 * $c{$c} ) * 3600;
			$dy = 14400;
		} elsif( 1 == $idx ) {							# 1:1000000
			$x = ( 6 * ( $c - 1 ) - 180 ) * 3600;
			$dx = 21600;
		} elsif(  2 == $idx ) {							# 1:100000
			$dx /= 12; $dy /= 12;
			$c -= 1;
			$x += $dx * ( $c % 12 );
			$y += 11 * $dy - ( $dy * ( $c / 12 ) );
		} elsif(  3 == $idx ) {							# 1:50000
			$dx /= 2; $dy /= 2;
			$x += $dx * ( $c{$c} % 2 );
			$y += $dy - ( $dy * ( $c{$c} / 2 ) );
		} elsif(  4 == $idx ) {							# 1:25000
			$dx /= 2; $dy /= 2;
			$x += $dx * ( $c{$c} % 2 );
			$y += $dy - ( $dy * ( $c{$c} / 2 ) );
		} elsif(  5 == $idx ) {							# 1:10000
			$dx /= 2; $dy /= 2;
			$c -= 1;
			$x += $dx * ( $c % 2 );
			$y += $dy - ( $dy * ( $c / 2 ) );
		}
		++$idx;
	}
	$O->{LLR} = $x;
	$O->{LLH} = $y;
	$O->{DR} = $dx;
	$O->{DH} = $dy;
	$O->{URR} = $O->{LLR} + $O->{DR};
	$O->{URH} = $O->{LLH} + $O->{DH};
	return $self;
}

BEGIN {
$MapType::TKAS::SCALES = {
		order => [qw~10000 25000 50000 100000 1000000~]
		,   10000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d]_[a-d]_[1-4])$'
		,   25000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d]_[a-d])$'
		,   50000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d])$'
		,  100000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3})[^1-9]$'
		, 1000000 => '([a-z]_[1-9]{1,2})[^1-9]$'
	};
	#########################################################
	# 0:03:45 0:02:30
	# 0:07:30 0:05:00
	# 0:15:00 0:10:00
	# 0:30:00 0:20:00
	# 1:00:00 0:40:00
	# 6:00:00 4:00:00
$MapType::TKAS::MList = {
			    10000 => [qw~225 150~]
			,   25000 => [qw~450 300~]
			,   50000 => [qw~900 600~]
			,  100000 => [qw~1800 1200~]
			,  200000 => [qw~3600 2400~]
			, 1000000 => [qw~21600 14400~]
	};
$MapType::TKAS::NList = [qw~1000000 100000 50000 25000 10000~];
}

1;

__END__

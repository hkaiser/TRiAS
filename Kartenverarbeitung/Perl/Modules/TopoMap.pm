package TopoMap;
use strict;
use Carp;

sub DMS2Dec {
	my( $dms ) = @_;
	my(@C);
	@C=split(/:/, $dms );
	$C[0] = 0 unless( $C[0] );
	$C[1] = 0 unless( $C[1] );
	$C[2] = 0 unless( $C[2] );
	return 3600 * $C[0] + 60 * $C[1] + $C[2];
}

sub new {
	my($class,$SCALE)=@_;
	my $self = {};
    bless $self;
    $self->init($SCALE);
    return $self;
}

sub DESTROY {
	1;
}

sub TopoMap::AUTOLOAD {
	my($self,@param)=@_;
    my($constname);
    ($constname = $TopoMap::AUTOLOAD) =~ s/.*:://;
	if( defined $self->{$constname} ) {
		return $self->{$constname};
	}
	croak 'undefined call : '.$constname;
	return undef;
}

sub init {
	my($self,$SCALE)=@_;
	$self->{SCALE} = defined $SCALE ? $SCALE : -1;
	$self->{IOffset} = {
		qw~200 11 250 12 400 13 500 14 750 15 1000 16 2000 17 4000 18 5000 19
			10000 21 25000 22 50000 23 100000 24
			200000 31 500000 32 750000 33 1000000 34
		~};
	$self->{MSchemes}{AS} = {
		order => [qw~10000 25000 50000 100000 1000000~]
		,   10000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d]_[a-d]_[1-4])'
		,   25000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d]_[a-d])'
		,   50000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3}_[a-d])'
		,  100000 => '([a-z]_[1-9]{1,2}_[0-9]{1,3})[^1-9]'
		, 1000000 => '([a-z]_[1-9]{1,2})[^1-9]'
	};
	$self->{MSchemes}{N} = {
		order => [qw~10000 200000 100000 50000 25000~]
		,  10000 => '([1-8][0-9][0-5][0-9]_[ns][ow])'
		, 200000 => '([c][c]_[1-8][0-9][0-5][0-9])'
		, 100000 => '([c]_[1-8][0-9][0-5][0-9])'
		,  50000 => '([l]_[1-8][0-9][0-5][0-9])'
		,  25000 => '([1-8][0-9][0-5][0-9])'
	};
	$self->{MSchemes}{ATKIS} = {
		order => [qw~10000~]
		,  10000 => '([1-4][0-9][0-9][0-9][0-9][0-9])'
	};
}

sub Parse {
	my($self,$mapname)=@_;
	my($scale,$schema,@mapinfo);
	$mapname =~ s/[^A-Za-z0-9]/_/g;
	$mapname =~ tr/[A-Z]/[a-z]/;
	foreach $schema ( keys %{$self->{MSchemes}} ) {
		foreach $scale ( @{$self->{MSchemes}{$schema}{order}} ) {
			if( $mapname =~ /$self->{MSchemes}{$schema}{$scale}/ and $& ) {
				return ($schema,$scale,$&);
			}
		}
	}
	return undef;
}

sub scale {
	my($self,$scale)=@_;
	my($oldscale) = defined $self->{SCALE} ? defined $self->{SCALE} : undef;
	if( defined $scale and defined $self->{MList}{$scale} ) {
		$self->{SCALE} = $scale;
	}
	return $oldscale;
}
	
sub Ident {
	my($self)=shift;
	return qq~$self->{IBase}$self->{IOffset}{ $self->{SCALE} }~;
}

sub Typ {
	my($self)=shift;
	return qq~$self->{MAPTYPE} Maástab 1:$self->{SCALE}~;
}

sub param {
	my($self)=shift;
	return( $self->{NAME}, $self->{SCALE}, $self->{X}, $self->{'Y'}, $self->{'DX'}, $self->{'DY'} );
}
1;

package TopoMapAS;
use Carp;
@TopoMapAS::ISA = qw( TopoMap );
sub new {
	my($class,$SCALE)=@_;
	my $self = $class->TopoMap::new($SCALE);
    bless $self;
    return $self->init();
}

sub init {
	my($self)=@_;
	$self->{MAPTYPE} = 'topogr. Karte AS';
	$self->{CoordTransform} = 'KRGEOD';
	$self->{CoordStrBreite} = 6;
	$self->{IBase} = '9110';
	#########################################################
	# 0:03:45 0:02:30
	# 0:07:30 0:05:00
	# 0:15:00 0:10:00
	# 0:30:00 0:20:00
	# 1:00:00 0:40:00
	# 6:00:00 4:00:00
	$self->{MList} = {
			    10000 => [qw~225 150~]
			,   25000 => [qw~450 300~]
			,   50000 => [qw~900 600~]
			,  100000 => [qw~1800 1200~]
			,  200000 => [qw~3600 2400~]
			, 1000000 => [qw~21600 14400~]
	};
	$self->{NList} = [qw~1000000 100000 50000 25000 10000~];
	if( defined $self->{SCALE} ) {
		if( not defined $self->{MList}{$self->{SCALE}} ) {
			print STDERR "Maßstab undefiniert für ".$self->{MAPTYPE}."\n" ;
			return undef;
		}
		$self->{DX} = $self->{MList}{$self->{SCALE}}[0];
		$self->{DY} = $self->{MList}{$self->{SCALE}}[1];
	}
	return $self;
}

sub Coord {
	my($self,$Lat,$Long)=@_;
	if( not defined $self->{SCALE} ) {
		return undef;
	}
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
	foreach( @{$self->{NList}} ) {
		@S=($self->{MList}{$_}[0],$self->{MList}{$_}[1]);
		@R=( $Q[0] % $S[0], $Q[1] % $S[1] );
		@Q=( $Q[0] / $S[0], $Q[1] / $S[1] );
		print ";", join( ", ", @Q, @R ), "\n";
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
		last if( $self->{SCALE} eq $_ );
		@Q=@R;
	}
	return join("-",@N);
}

sub Name {
	my($self,$name)=@_;
	my($schema,$scale);
	($schema,$scale,$name)=$self->Parse($name);
	return undef if( not defined $schema or not defined $scale );
	return undef if( $schema !~ /as/i );

	use integer;
	$self->{SCALE} = $scale;

	my(@name)=split('_',$name);
	my(@newName);
	my($x,$y,$dx,$dy)=(0,0,0,0);
	my($c,%c) = (0,());

	foreach( ('a'...'z') ) { $c{$_} = $c++; }
	my $idx = 0;

	while( $#name > -1 ) {
		$c = splice(@name,0,1);
		if( 0 == $idx ) {								# 1:1000000
			push(@newName,uc($c));
#			$$.pt.y = ( 4 * $1 ) * 3600;
			$y = ( 4 * $c{$c} ) * 3600;
			$dy = 14400;
		} elsif( 1 == $idx ) {							# 1:1000000
			push(@newName,$c);
#			$$.pt.x = ( 6 * ( $3 - 1 ) - 180 ) * 3600;
			$x = ( 6 * ( $c - 1 ) - 180 ) * 3600;
			$dx = 21600;
		} elsif(  2 == $idx ) {							# 1:100000
			push(@newName,$c);
#			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 12 );
#			$$.pt.y = $1.pt.y + 11 * $$.sz.cy - $$.sz.cy * ( $3 / 12 );
			$dx /= 12; $dy /= 12;
			$c -= 1;
			$x += $dx * ( $c % 12 );
			$y += 11 * $dy - ( $dy * ( $c / 12 ) );
		} elsif(  3 == $idx ) {							# 1:50000
			push(@newName,uc($c));
#			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
#			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$dx /= 2; $dy /= 2;
			$x += $dx * ( $c{$c} % 2 );
			$y += $dy - ( $dy * ( $c{$c} / 2 ) );
		} elsif(  4 == $idx ) {							# 1:25000
			push(@newName,lc($c));
#			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
#			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$dx /= 2; $dy /= 2;
			$x += $dx * ( $c{$c} % 2 );
			$y += $dy - ( $dy * ( $c{$c} / 2 ) );
		} elsif(  5 == $idx ) {							# 1:10000
			push(@newName,$c);
#			$$.pt.x = $1.pt.x + $$.sz.cx * ( $3 % 2 );
#			$$.pt.y = $1.pt.y + $$.sz.cy - ( $$.sz.cy * ( $3 / 2 ) );
			$dx /= 2; $dy /= 2;
			$c -= 1;
			$x += $dx * ( $c % 2 );
			$y += $dy - ( $dy * ( $c / 2 ) );
		}
		$idx++;
	}
	$self->{'X'} = $x;
	$self->{'Y'} = $y;
	$self->{'DX'} = $dx;
	$self->{'DY'} = $dy;
	$self->{'SCALE'} = $scale;
	$self->{'NAME'} = join('-',@newName);
	return $self->param();
}
1;

package TopoMapN;
use Carp;
@TopoMapN::ISA = qw( TopoMap );
sub new {
	my($class,$SCALE)=@_;
	my $self = $class->TopoMap::new($SCALE);
    bless $self;
    return $self->init();
}

sub init {
	my($self)=@_;
	$self->{MAPTYPE} = 'topogr. Karte N';
	$self->{CoordTransform} = 'BEGEOD';
	$self->{CoordStrBreite} = 3;
	$self->{IBase} = '9120';
	$self->{MList} = {
			10000 => [qw~300 180~]
			, 25000 => [qw~600 360~]
			, 50000 => [qw~1200 720~]
			, 100000 => [qw~2400 1440~]
			, 200000 => [qw~4800 2880~]
	};
	$self->{NList} = [qw~200000 100000 50000 25000 10000~];
	if( defined $self->{SCALE} ) {
		if( not defined $self->{MList}{$self->{SCALE}} ) {
			print STDERR "Maßstab undefiniert für ".$self->{MAPTYPE}."\n" ;
			return undef;
		}
		$self->{DX} = $self->{MList}{$self->{SCALE}}[0];
		$self->{DY} = $self->{MList}{$self->{SCALE}}[1];
	}
	return $self;
}

sub Coord {
	my($self,$Lat,$Long)=@_;
	if( not defined $self->{SCALE} ) {
		return undef;
	}
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
	foreach( @{$self->{NList}} ) {
		@S=($self->{MList}{$_}[0],$self->{MList}{$_}[1]);
		@R=( $Q[0] % $S[0], $Q[1] % $S[1] );
		@Q=( $Q[0] / $S[0], $Q[1] / $S[1] );
		print ";", join( ", ", @Q, @R ), "\n";
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
		last if( $self->{SCALE} eq $_ );
		@Q=@R;
	}
	return join("-",@N);
}
1;

package TopoMapATKIS;
use Carp;
@TopoMapATKIS::ISA = qw( TopoMap );
sub new {
	my($class,$SCALE)=@_;
	my $self = $class->TopoMap::new($SCALE);
    bless $self;
    $self->init();
    return $self;
}
sub init {
	my($self)=@_;
	$self->{MAPTYPE} = 'topogr. Karte ATKIS';
	$self->{CoordTransform} = 'BESSELGK';
	$self->{CoordStrBreite} = 3;
	$self->{IBase} = '9120';
}

sub Name {
	my($self,$name)=@_;
	my($schema,$scale);
	($schema,$scale,$name)=$self->Parse($name);
	return undef if( not defined $schema or $schema !~ /atkis/i );
	use integer;
	$self->{SCALE} = $scale;
	$name =~ /(...)(...)/;
	($self->{X},$self->{Y})=($1,$2);
	$self->{X} *= 10000;
	$self->{Y} *= 10000;
	$self->{DX} = 10000;
	$self->{DY} = 10000;
	$self->{NAME} = qq~AT$name~;
	return $self->param();
}
1;

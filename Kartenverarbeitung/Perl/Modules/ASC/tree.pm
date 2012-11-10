package ASC::tree;
require Exporter;
use Carp;
use ASC::object;
@ISA = qw(Exporter);
@EXPORT =
  qw(
);

sub new {
	my($class)=@_;
	my $self = {};
    bless $self,ref $class || $class;
    $self->init( );
    return $self;
}

sub DESTROY {
	1;
}

sub AUTOLOAD {
	my($self,@param)=@_;
    my($constname);
    ($constname = $AUTOLOAD) =~ s/.*:://;
	if( defined $self->{$constname} ) {
		return $self->{$constname};
	}
	croak 'undefined call : '.$constname;
	return undef;
}

sub init {
	my($self)=@_;
	undef $self->{O} if( defined $self->{O} );
	$self->header_value( 'Unique Ident', '51200000' );
	$self->header_value( 'ObjName', '51100000' );
	$self->header_value( 'TextObjMCode', '99999100' );
	$self->header_value( 'Scale', '1000 0 0 1000' );
	$self->{B}{XMIN} = 1.e+10;
	$self->{B}{YMIN} = 1.e+10;
	$self->{B}{XMAX} = -1.e+10;
	$self->{B}{YMAX} = -1.e+10;
}

sub accept_mcodes {
	my($self,@mcodes)=@_;
	if( -1 eq $#mcodes ) { return defined $self->{AMCODES} ? keys %{$self->{AMCODES}} : (); }
	undef $self->{AMCODES};
	foreach( @mcodes ) {
		$self->{AMCODES}{$_}='';
	}
}

sub accept_idents {
	my($self,@idents)=@_;
	if( -1 eq $#idents ) { return defined $self->{AIDENTS} ? keys %{$self->{AIDENTS}} : (); }
	undef $self->{AIDENTS};
	foreach( @idents ) {
		$self->{AIDENTS}{$_}='';
	}
}

sub accept_types {
	my($self,@types)=@_;
	if( -1 eq $#types ) { return defined $self->{ATYPES} ? keys %{$self->{ATYPES}} : (); }
	undef $self->{ATYPES};
	foreach( @types ) {
		$self->{ATYPES}{$_}='';
	}
}

sub header_value {
	my($self,$key,$val)=@_;
	my $old_val = defined $self->{H}{$key} ? $self->{H}{$key} : undef;
	$self->{H}{$key} = $val if( defined $val );
	return $old_val;
}

sub print_header {
	my($self)=@_;
	use integer;
	my($xMin,$yMin);
	$xMin = ($self->{B}{XMIN} / 10000); $xMin *= 10000;
	$yMin = ($self->{B}{YMIN} / 10000); $yMin *= 10000;
	print "H \n";
	$self->{H}{Offset} = qq~$xMin $yMin~;
	foreach( sort keys %{$self->{H}} ) {
		printf( "D Entry%-5s", defined $self->{DS}{$_} ? 'RoSys' : '' );
		printf( " \"%-16s\"", substr( $_, 0, 16 ) );
		printf( " \"%s\"", $self->{H}{$_} );
		print "\n";
	}
}

sub print_body {
	my($self)=@_;
	$self->traverse( \&ASC::object::print_asc );
}

sub print_trailer {
	print "E\n";
}

sub traverse {
	my($self,$function)=@_;
	$function = \&print_asc if( not defined $function );
	croak "no function defined" unless $function;
	foreach( sort { $a > $b ? 1 : $a < $b ? -1 : 0} keys %{$self->{O}} ) {
		&$function( $self->{O}{$_}, $_, $self->{H} );
	}
}

sub add_object {
	my($self,$o) = @_;
	croak "Not A TRiAS Object " unless( $o->{TYPE} );
	croak "Missing Coordinates " if( -1 == $#{$o->{COORDS}} );
	my($nObjects) =  $#[keys %{$self->{O}}];
	$nObject = defined $nObject ? $nObject + 1 : 1;
	while( defined $self->{O}{$nObject} ) {
		$nObject++;
	}
	my $i;
	for( $i = 0; $i < $#{$o->{COORDS}}; $i += 2 ) {
		$self->{B}{XMIN} = $o->{COORDS}[$i] if( $o->{COORDS}[$i] < $self->{B}{XMIN} );
		$self->{B}{YMIN} = $o->{COORDS}[$i+1] if( $o->{COORDS}[$i+1] < $self->{B}{YMIN} );
		$self->{B}{XMAX} = $o->{COORDS}[$i] if( $o->{COORDS}[$i] > $self->{B}{XMAX} );
		$self->{B}{YMAX} = $o->{COORDS}[$i+1] if( $o->{COORDS}[$i+1] > $self->{B}{YMAX} );
	}
	$self->{O}{$nObject} = $o;
}

sub read_asc {
	my($self,$fileptr)=@_;
	my($nObject,$id,$mc,@line);
	my($iaccept,$aaccept);
	my($X,$Y);

	$self->{B}{XMIN} = 1.e+10;
	$self->{B}{YMIN} = 1.e+10;
	$self->{B}{XMAX} = -1.e+10;
	$self->{B}{YMAX} = -1.e+10;

	while(<$fileptr>) {
		chop;
Line:
		if( /^D/ ) {
			s/^D\s*//;
			s/"\s*/"/g;
			s/\s*"/"/g;
			s/""/"/g;
			@line=split( /"/ );
#			print join( ":", @line ), "\n";
			$self->{H}{$line[1]} = $line[2];
#			$self->{H}{$line[1]} = 'Entry' eq $line[0] ? 0 : 1;
		} elsif( /^[FPLMGIB]/ ) {
			@line=split( /\s+/ );
			if( $line[0] =~ /[FLPB]/ ) {
				$iaccept = ( not defined $self->{ATYPES} or defined $self->{ATYPES}{$line[0]} ) ? 1 : 0;
				next unless( $iaccept );
				$line[2] =~ s/"//g;
				$iaccept = ( not defined $self->{AIDENTS} or defined $self->{AIDENTS}{$line[2]} ) ? 1 : 0;
				next unless( $iaccept );
				++$nObject;
				$self->{O}{$nObject}{TYPE} = $line[0];
				$self->{O}{$nObject}{IDENT} = $line[2];
			} elsif ( 'M' eq $line[0] or 'I' eq $line[0] ) {
				next unless( $iaccept );
				$aaccept = ( not defined $self->{AMCODES} or defined $self->{AMCODES}{$line[1]} ) ? 1 : 0;
				$mc=$line[1];
				while(<$fileptr>) {
					goto Line unless( /^W/ );
					$self->{O}{$nObject}{MCODES}{$mc} = '';
					chop;
					s/^W //;
					s/^"//; s/"$//;
					$self->{O}{$nObject}{MCODES}{$mc} .= $_;
				}
			} elsif ( 'G' eq $line[0] ) {
				next unless( $iaccept );
				undef @coord;
				shift( @line );
				while( -1 != $#line ) {
					($X,$Y)=splice(@line,0,2);
					$self->{B}{XMIN} = $X if( $X < $self->{B}{XMIN} );
					$self->{B}{YMIN} = $Y if( $Y < $self->{B}{YMIN} );
					$self->{B}{XMAX} = $X if( $X > $self->{B}{XMAX} );
					$self->{B}{YMAX} = $Y if( $Y > $self->{B}{YMAX} );
					@coord = (@coord,$X,$Y);
				}
				@{$self->{O}{$nObject}{COORDS}} = (@{$self->{O}{$nObject}{COORDS}},@coord);
			}
		}
	}
}

sub objects {
	my($self)=@_;
	return defined $self->{O} ? (sort { $a > $b ? 1 : $a < $b ? -1 : 0} keys %{$self->{O}} ) : ();
}

sub object {
	my($self,$obj)=@_;
	return defined $self->{O}{$obj} ? \%{$self->{O}{$obj}} : undef;
}

sub dump {
	my($self)=@_;
	foreach( sort keys %{$self->{O}} ) {
		print qq(\n$_ => $self->{O}{$_}->{TYPE} $self->{O}{$_}->{CLASS} )
			, qq(\n\t),  join( "\n\t", %{$self->{O}{$_}->{MCODES}} )
			, qq(\n\t\t), join( "\n\t\t", @{$self->{O}{$_}->{COORDS}} )
			;
	}	
}

1;

package DocType::TFW;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(DocType);
$VERSION="1.0";

use DocType;
use MapInfo;		# wir brauchen die Kartenbreite aus der TIFF-Datei...

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

#################################################################################
# Arc/Info - tfw-Dateien

sub read_info {
	my($self,$I,$O) = @_;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );
	my $filename = join('', $I->{filename}[0], $I->{filename}[1], '.tfw' );
	open( DATFILE, qq(<$filename) ) or return $self->ERROR( 'ERR_CANNOTOPENFILE', $filename );

	my(@T) = (<DATFILE>);
	close(DATFILE);

	my($idx);
	for( $idx = 0; $idx <= $#T; ++$idx ) {
		$T[$idx] =~ s/\s*//g;
	}
	########################################################
	# Tiff-Datei auslesen, wir brauchen Breite und Höhe
    my $mapInf = new MapInfo;
	my $pict = {}
	$mapInf->read( {filename=>join('', @{$I->{filename}})}, $pict ) 
		or return $self->ERROR(qw(ERR_UNKNOWN));
	my($W,$H) = ($pict->{256},$pict->{257});
	my($ULR,$ULH,$LRR,$LRH) = ( $T[4], $T[5], $T[4] + $W * $T[0], $T[5] + $H * $T[3]);

	$O->{layer} = undef;
	$O->{scale} = undef;
	$O->{LLR} = $ULR;
	$O->{URH} = $ULH;
	$O->{URR} = $LRR;
	$O->{LLH} = $LRH;
	return $self;
}

1;

__END__

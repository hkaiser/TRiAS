package DocType::GeoTiff;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(DocType);
$VERSION="1.0";

use DocType;

sub new {
	my($class)=@_;
	my $self = {};
    bless $self,ref $class || $class;
    return $self->init(@param);
}

sub DESTROY {
	1;
}

sub init {
	my($self)=@_;
	return $self;
}

#################################################################################
# geotiff-Informationsdatei; funktioniert nur, wenn Eckkoordinaten angeben sind:
#
#Corner Coordinates:
#Upper Left    (2524169.235,5688185.414)GTIFProj4ToLatLong() - PROJ.4 support not compiled in.
#
#Lower Left    (2524169.235,5679843.414)GTIFProj4ToLatLong() - PROJ.4 support not compiled in.
#
#Upper Right   (2530170.235,5688185.414)GTIFProj4ToLatLong() - PROJ.4 support not compiled in.
#
#Lower Right   (2530170.235,5679843.414)GTIFProj4ToLatLong() - PROJ.4 support not compiled in.

sub read_info {
	my($self,$I,$O) = @_;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );
	my $filename = join('', $I->{filename}[0], $I->{filename}[1], '.geo' );
	open( DATFILE, qq(<$filename) ) or return $self->ERROR( 'ERR_CANNOTOPENFILE', $filename );

	$O->{layer} = undef;
	$O->{scale} = undef;

	while(<DATFILE>) {
    	if( /Lower Left\s+\(([0-9\.]+),([0-9\.]+)\).*$/ ) {
			($O->{LLR},$O->{LLH}) = ($1,$2);
        }
    	if( /Upper Right\s+\(([0-9\.]+),([0-9\.]+)\).*$/ ) {
			($O->{URR},$O->{URH}) = ($1,$2);
        }
	}
	close DATFILE;
	return $self;
}

1;

__END__

package DocType::Hessen;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw(DocType);
$VERSION="1.0";

use DocType;
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

#################################################################################
# eine Tiff-Datei in einem Verzeichnis, daneben liegt immer eine Datei mit dem
# Namen 'Karte.dat' im Format:
# UL	4499218.75 5452093.80
# UR	4512950.00 5452093.80
# LR	4512950.00 5439412.55
# LL	4499218.75 5439412.55

sub read_info {
	my($self,$I,$O) = @_;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );
	my $filename = join('', $I->{filename}[0], 'Karte', '.dat' );
	open( DATFILE, qq(<$filename) ) or return $self->ERROR( 'ERR_CANNOTOPENFILE', $filename );

	$O->{layer} = undef;
	$O->{scale} = undef;

	while(<DATFILE>) {
		if( /^\s*LL\s*([0-9\.]+)\s*([0-9\.]+)\s*$/ ) {
			($O->{LLR},$O->{LLH}) = ($1,$2);
		} elsif( /^\s*UR\s*([0-9\.]+)\s*([0-9\.]+)\s*$/ ) {
			($O->{URR},$O->{URH}) = ($1,$2);
		}
	}
	close DATFILE;
	return $self;
}

1;

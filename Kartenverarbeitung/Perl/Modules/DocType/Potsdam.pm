package DocType::Potsdam;

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
# Stadtplan Potsdam (LVermA Brandenburg)
# Namensschema: potsXYYY.tif
# X => Blattnummer (1=>lo, 2=>ro, 3=>lu, 4=>ru)
# YYY => Layer; wird in MapLayer/Potsdam.pm ausgewertet

sub read_info {
	my($self,$I,$O) = @_;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );
	return undef unless $I->filename[1] =~ /^pots([0-9])([a-z]{3,3})$/i;
	my $filename = join('', $I->{filename}[0], qq(pots$1), '.dat' );
	open( DATFILE, qq(<$filename) ) or return $self->ERROR( 'ERR_CANNOTOPENFILE', $filename );


	$O->{layer} = $layer;
	$O->{scale} = undef;

	while(<DATFILE>) {
		if( /^\s*ULX\s*([0-9\.]+)\s*ULY\s*([0-9\.]+)\s*$/ ) {
			($O->{LLR},$O->{URH})=($1,$2);
#			($ULR,$ULH) = ($1,$2);
		} elsif( /^\s*LRX\s*([0-9\.]+)\s*LRY\s*([0-9\.]+)\s*$/ ) {
			($O->{URR},$O->{LLH})=($1,$2);
#			($LRR,$LRH) = ($1,$2);
		}
	}
	close DATFILE;
	return $self;
}

1;

__END__

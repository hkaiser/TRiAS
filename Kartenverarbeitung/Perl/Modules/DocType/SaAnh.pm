package DocType::SaAnh;

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
# doc-Dateien des LVermA Sachsen Anhalt

sub read_info {
	my($self,$I,$O) = @_;
	my $temp;
	my $LLMH;
	my $LRMH;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );
	my $filename = join('', $I->{filename}[0], $I->{filename}[1], '.doc' );
	open( DATFILE, qq(<$filename) ) or return $self->ERROR( 'ERR_CANNOTOPENFILE', $filename );
	while(<DATFILE>) {
		if( $_ =~ /^\s+[5]\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{LLR},$O->{LLH}) = ($1,$2);
			($O->{LLFR},$O->{LLFH}) = ($1,$2);
		} elsif( $_ =~ /^\s+[6]\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{URR},$O->{URH}) = ($1,$2);
			($O->{URFR},$O->{URFH}) = ($1,$2);
		} elsif( $_ =~ /^\s+[1]\s+([0-9\.]+)\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{LLMR},$O->{LLMH}) = ($1,$2);
			$LLMH = $3;
		} elsif( $_ =~ /^\s+[2]\s+([0-9\.]+)\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{LRMR},$O->{LRMH}) = ($1,$2);
			$LRMH = $3;
		} elsif( $_ =~ /^\s+[3]\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{URMR},$O->{URMH}) = ($1,$2);
		} elsif( $_ =~ /^\s+[4]\s+([0-9\.]+)\s+([0-9\.]+).*/ ) {
			($O->{ULMR},$O->{ULMH}) = ($1,$2);
		} elsif( $_ =~ /\s*(Ausgabe\s*[0-9]+).*/ ) {
			$O->{time} = $1;
		} elsif( $_ =~ /^\s*([^\s]+).*Topographische\s*Karte\s*1:([0-9]+)\s*$/ ) {
			($O->{ident},$O->{scale}) = ($1,$2);
		}
	}
	close(DATFILE);
	
# prüfen ob Koordinaten im Uhrzeigersinn angegeben wurden, dann vertauschen
#	if( $LLMH != $LRMH ) {
#		$temp = $O->{LRMH};
#		$O->{LRMH} = $O->{ULMH};
#		$O->{ULMH} = $temp;
#		$temp = $O->{LRMR};
#		$O->{LRMR} = $O->{ULMR};
#		$O->{ULMR} = $temp;
#	}
	return $self;
}

1;
__END__

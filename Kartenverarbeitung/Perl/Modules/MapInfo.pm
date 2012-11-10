package MapInfo;
use strict;
require Exporter;
use Carp;
use vars qw~$AUTOLOAD~;

sub new {
	my($class,$MapName)=@_;
	my $self = {};
	bless $self,ref $class || $class;
	$self->init( $MapName );
	return $self;
}

sub DESTROY {
	1;
}

sub AUTOLOAD {
	my($self,@param)=@_;
	my($constname);
	($constname = $AUTOLOAD) =~ s/.*:://;
	if( defined $self->{TAGS}{$constname} ) {
		return $self->{TAGS}{$constname};
	}
	return undef;
}

sub init {
	my($self,$MapName)=@_;
	$self->{TAGS}=();
	&read( $self, $MapName ) if( $MapName );
}

sub read {
	my($self,$I,$O) = @_;

	$I->{filename} or return $self->ERROR( 'ERR_MISSINGARG', 'filename' );

	my $opn = qq~MapInfo -r "$I->{filename}" |~;
	my($tag,$type,$name,@info);
	$self->{TAGS}=();
	open( MAPINFO, $opn ) or return $self->ERROR( 'ERR_CANNOTOPEN', $I->{filename} );
	while(<MAPINFO>) {
		#print "---> $_";
		chop;
		($tag,$type,$name,@info)=split(/\t/);
		$self->{TYPES}{'Tag'.$tag} = $type;
		$self->{TAGS}{'Tag'.$tag} = 1 == $info[0] ? $info[2] : [@info];
		$self->{NAMES}{'Tag'.$tag} = $name;
	}
	$O->{256} = $self->Width();
	$O->{257} = $self->Height();
	$O->{258} = $self->BPS();
	$O->{277} = $self->SPP();
	close(MAPINFO);
}

sub Width	{ my($self) = @_; $self->Tag256; }
sub Height	{ my($self) = @_; $self->Tag257; }
sub BPS		{ my($self) = @_; if( 0 == $self->Tag258 ) { 8; } else {$self->Tag258;}; }
sub SPP		{ my($self) = @_; if( 0 == $self->Tag277 ) { 1; } else {$self->Tag277;}; }

sub AllTags { my($self) = @_; return keys %{$self->{TAGS}}; }
sub TagName { my($self,$S) = @_; return (defined $self->{NAMES}{$S}) ? $self->{NAMES}{$S} : undef; }
sub TagType { my($self,$S) = @_; return (defined $self->{TYPES}{$S}) ? $self->{TYPES}{$S} : undef; }

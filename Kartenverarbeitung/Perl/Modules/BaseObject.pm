package BaseObject;

use strict;
use vars qw(@ISA $VERSION);

@ISA=qw();						# the root of all
$VERSION="1.0";

$BaseObject::__ERRORS = [];		# collect all errors
$BaseObject::__LANGUAGE = 'de';	# language for errormessages
$BaseObject::__DEBUG = $ENV{DEBUG_BASEOBJECT};		# für die Entwicklungsphase

sub ERROR {
	my($self,$e,@p)=@_;
	my($sc,$pc,$nc)=caller;
	my $err = $BaseObject::__ERRMSGS->{$e}{$BaseObject::__LANGUAGE} ? $e : 'ERR_UNKNOWN';
	my $S = qq(%s(%d): $e: $BaseObject::__ERRMSGS->{$err}{$BaseObject::__LANGUAGE});
	$S = sprintf( $S, $pc, $nc, @p );
	push( @{$BaseObject::__ERRORS}, $S );
	return undef;
}

sub WARN {
	my($self,$e,@p)=@_;
	my($sc,$pc,$nc)=caller;
	my $err = $BaseObject::__ERRMSGS->{$e}{$BaseObject::__LANGUAGE} ? $e : 'ERR_UNKNOWN';
	my $S = qq(%s(%d): $e: $BaseObject::__ERRMSGS->{$err}{$BaseObject::__LANGUAGE}\n);
	print STDERR sprintf( $S, $pc, $nc, @p );
	return $self;
}

sub ERRORS {
	if( wantarray ) {
		my @E = @$BaseObject::__ERRORS;
		$BaseObject::__ERRORS = [];
		return @E;
	} else {
		return $#{$BaseObject::__ERRORS} + 1;
	}
}

sub PUREVIRT {
	my($self)=@_;
	my($m,$p,$l,$n,$unk1,$unk2)=caller(1);
	return $self->ERROR( 'ERR_PUREVIRT', $n, $p, $l );
}

BEGIN { 
my $errMsgs = q(
ERR_UNKNOWN
	de	UNKNOWN ERROR
ERR_MISSINGARG
	de	Argument [%s] wurde nicht angegeben
ERR_PUREVIRT
	de	pure virtuelle Funktion [%s] in [%s(%d)] gerufen
ERR_CANNOTOPENFILE
	de	kann Datei [%s] nicht öffnen
ERR_CANNOTCREATEINSTANCE
	de	Kann Objekt vom Typ [%s] nicht erstellen.
);
	my $__ERRMSGS = {};
	sub init_errmsg {
		my @msgs = split(/\n/,$_[0]);
		my($classmsgs,$msgcode,$dummy,$lang,$msgstring) = ('');
		foreach( @msgs ) {
			next if( /^\s*$/ or /^\s*#/ );
			$msgcode = $_ and next if( /^[A-Za-z]/ );
			($dummy,$lang,$msgstring) = split( /\t/ );
#			print qq~>> $lang $msgcode\n~;
			$BaseObject::__ERRMSGS->{$msgcode}{$lang} = $msgstring;
		}
	}
	init_errmsg( $errMsgs );
}

1;

package BaseObjectFactory;

use strict;
use Carp;
use vars qw(@ISA $VERSION);

@ISA=qw(BaseObject);
$VERSION="1.0";

sub CreateInstance {
	my($BASEDIR,$what) = @_;
	eval("use $BASEDIR\::$what;");
	croak qq($@\n) if $@ and $BaseObject::__DEBUG;
	my $obj = eval("new $BASEDIR\::$what;" );
	croak qq($@\n) if $@ and $BaseObject::__DEBUG;
	return $obj;
}

sub EnumClasses {
	my($BASEDIR)=@_;
	my $objects = [];
	_EnumObjects( $_, $BASEDIR, $objects ) foreach(@INC);
	return $objects;
}

sub _EnumObjects {
	my($libdir,$BASEDIR,$objects)=@_;
	opendir(DIR,"$libdir/$BASEDIR") or return;
	push( @$objects, map /(.*)\.pm$/i, grep { /^[^\.]/ && -f "$libdir/$BASEDIR/$_" } readdir( DIR ) );
	closedir(DIR);
}

1;

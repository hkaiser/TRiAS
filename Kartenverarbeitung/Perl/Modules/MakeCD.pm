package MakeCD;

use strict;
use vars qw(@ISA $VERSION);
use MakeAnyThing;

@ISA=qw(MakeAnyThing);
$VERSION="1.0";

use File::Basename;
use File::Find;

sub new {
	my($class,$param)=@_;
	my $self = {};
	bless $self, ref $class || $class || 'MakeCD';
	return $self->init( $param );
}

sub init {
	my($self,$param)=@_;
	return $self;
}

sub pre_process {
	my($self,$P)=@_;
	$P->{destDir} or return $self->ERROR(qw(ERR_MISSINGARG destDir));
	return $self;
}
sub post_process { my $self = shift; return $self; }

sub MakeAnyThing {
	my($self,$M)=@_;

	####################################################################
	# ggf. Zielverzeichnis erstellen
	$self->check_path( {path=>$self->mfn($M->{outFile}),verbose=>$M->{verbose}} )
		or return $self->ERROR( 'ERR_INVALIDPATH', qq($M->{outFile}[1]) );

	####################################################################
	# ... und jetzt die richtige Arbeit ...
	my($inFile,$outFile) = ($M->{inFile},$M->{outFile});
	if( 0 == $M->{OMIT} and 3 == $M->{picture}{277} ) {		# 277 => Samples per Pixel => 3 => RGB
# fje		$M->{inFile} = $inFile;
		$M->{outFile} = $M->{tmpFiles}[0];
		$self->reduce_color( $M ) or return $self->ERROR( qw(ERR_UNKNOWN) );
		$M->{inFile} = $M->{tmpFiles}[0];
		$M->{outFile} = $outFile;
		$M->{picture}{277} = 1;
		$M->{picture}{258} = 8;
		$self->compress_file( $M ) or return $self->ERROR( qw(ERR_UNKNOWN) );
		$M->{inFile} = $inFile;
	} else {
# fje		$M->{inFile} = $inFile;
# fje		$M->{outFile} = $outFile;
		$self->compress_file( $M ) or return $self->ERROR( qw(ERR_UNKNOWN) );
	}

	####################################################################
	# Das Berechnen der Pyramiden erfolgt nur auf einer Datei
	$M->{filename} = $M->{outFile};
	####################################################################
	# jetzt reduzieren
	$M->{tmpFile} = $M->{tmpFiles}[0];
	$self->reduce_size( $M ) or return $self->ERROR( qw(ERR_UNKNOWN) );

	return $self;
}

####################################################################
# Farbreduktion

sub reduce_color {
	my($self,$P)=@_;
	$P->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );
	$P->{outFile} or return $self->ERROR( 'ERR_MISSINGARG', 'outFile' );
	my($if,$of);
	$if = $self->mfn($P->{inFile});
	$of = $self->mfn($P->{outFile});
	( -e $if ) or return $self->ERROR( 'ERR_NONEXISTENT', $P->{inFile} );
	print "RCOLOR: $if -> $of\n";
	$P->{picture}{271} = "Hell";
	$P->{picture}{272} = "DC 380";
	my $t = $self->make_tags($P->{picture});
# fje	my($cmd) = qq(MapRColor -p $P->{quality} -h "$P->{histFile}" -t "$t" "$if" "$of");
	my($cmd) = qq(MapRColor -p $P->{quality} -h "$P->{histFile}" "$if" "$of");
	print qq($cmd\n) if($P->{verbose});
	eval( qq(system('$cmd') ) ) unless $P->{DEBUG};
}

####################################################################
# komprimieren

sub compress_file {
	my($self,$P)=@_;
	$P->{inFile} or return $self->ERROR( 'ERR_MISSINGARG', 'inFile' );
	$P->{outFile} or return $self->ERROR( 'ERR_MISSINGARG', 'outFile' );
	my($compressor);
	# 277 => SPP, 258 => BPS
	if( 1 == $P->{picture}{277} and 8 == $P->{picture}{258} ) {
		$compressor = 'packbits';
	} elsif( 1 == $P->{picture}{277} and 1 == $P->{picture}{258} ) {
		$compressor = 'g4';
	} else {
		return $self->ERROR( 'ERR_INVALIDPICTFORMAT', $P->{inFile} );
	}

	my($inFile,$outFile) = ($self->mfn($P->{inFile}),$self->mfn($P->{outFile}));
	my($cmd) = qq(tiffcp -s -r 32 -c $compressor "$inFile" "$outFile");
	print "$cmd\n" if( $P->{verbose} );
	eval( qq(system('$cmd')) ) unless ( $P->{DEBUG} );
	return $self;
}

####################################################################
# Größenreduktion
# wir verzichten mal auf den Parametercheck und gehen davon aus, daß
# alles da ist; kein guter Stil aber streßmindernd (oder produzierend?)

sub reduce_size {
	my($self,$P)=@_;
	my($quality);
	if( 1 == $P->{picture}{277} and 8 == $P->{picture}{258} ) {
		$quality = 3;
	} elsif( 1 == $P->{picture}{277} and 1 == $P->{picture}{258} ) {
		$quality = 4;
	} else {
		return $self->ERROR( 'ERR_INVALIDPICTFORMAT', $P->{inFile} );
	} 
	my($tmpFile) = $self->mfn( $P->{tmpFile} );
	my($sP,$sN,$sS) = map { $_ } @{$P->{filename}};
	my($dP,$dN,$dS) = ($sP,$sN,$sS);
	my $sC = '';
	my($cmd);
	$P->{inFile} = $P->{tmpFile};
	foreach ( qw(a b c d e) ) {
		$cmd = qq(MapRSize -p $quality "$sP$sN$sC$sS" "$tmpFile");
		print "$cmd\n" if($P->{verbose});
		eval( qq~system('$cmd')~ ) unless $P->{DEBUG};
		$P->{outFile} = [$dP, qq($dN$_), $dS];
		$self->compress_file( $P ); 
		($sP,$sN,$sC,$sS) = ($dP,$dN,$_,$dS);
	}
	delete $P->{inFile};
	return $self;
}

####################################################################
# Überprüfen, ob der Pfad zu einer Datei vollständig ist; ggf.
# den Pfad aufbauen

sub check_path {
	my($self,$P) = @_;

	$P->{path} or return $self->ERROR( 'ERR_MISSINGARG', 'path' );

	my(@Parts,$dir);
	@Parts = split( /[\/\\]/, $P->{path} );
	$dir = shift( @Parts );
	while( @Parts ) {
		if( not -d $dir and not $dir =~ /:$/ ) {
			print STDERR "Creating Path: $dir\n" if( $P->{verbose} );
			mkdir( $dir, oct(755) );
		}
		$dir = $dir . "/" . shift( @Parts );
	}
	return $self;
}

####################################################################
# kleine Helferlein

sub make_tags {
	my($tags) = @_;
	my($t);
	foreach( keys %{$tags} ) { $t .= "$_,$tags->{$_}|"; }
	return $t;
}

1;
__END__


####################################################################
# einfach nur kopieren...

sub copy_file {
	my($srcFile,$dstFile,$tags,$mapInf) = @_;
#	print "COPY: $srcFile -> $dstFile\n";
#	my $t = make_tags($tags);
}

####################################################################
# Translationstabelle einlesen

sub read_translate_table {
	my($tabname) = @_;
	open(TABLE,$tabname) or return ();
	my(%table,$old,$new);
	while(<TABLE>) {
		chop;
		next if( /^\s*#/ );
		($old,$new) = split(/\s+/);
		$old =~ tr/[A-Z]/[a-z]/;
		$new = $old unless( $new );
		$table{lc($old)} = $new;
	}
	close(TABLE);
	$table{LOADED} = 'YES';
	return %table;
}

1;

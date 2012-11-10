sub format_DGK5 {
	my( $fullpath ) = @_;
	my($name,$path,$suffix) = fileparse( lc($fullpath), @SUFFIXES );
	$name =~ /[0-9]{6}/;
	if( $& ) {
		return( qq~$opt_d$&$suffix~, $name );
	} else {
		return undef;
	}
}


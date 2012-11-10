package ASC;

sub PutHeadBase {
	my($iB,$mB)=@_;
	PutHead( "IdentBase", 1, sprintf( "%ld", $iB ) );
	PutHead( "MCodeBase", 1, sprintf( "%ld", $mB ) );
}

sub PutHeadScale {
	my($scaleX, $scaleY)=@_;
	PutHead( "Scale", 1, sprintf( "%.5lf %.5lf", $scaleX, $scaleY ) );
}

sub PutHeadOffset {
	my($offX, $offY )=@_;
	PutHead( "Offset", 1, sprintf( "%.5lf %.5lf", $offX, $offY ) );
}

sub PutHead {
	my($entry,$bRO,$value)=@_;
	printf( "D Entry%s \"%-16s\" \"%s\"\n", 1==$bRO ? "RoSys" : "", $entry, $value );
}

sub PutCoord {
	my(@coords)=@_;
	my $nCoords=0;
	foreach( @coords ) {
		if( $nCoords % 6 == 0 ) {
			if( $nCoords > 0 ) {
				print "\n";
			}
			print "G";
		}
		printf( " %.8lf", $_ );
		$nCoord++;
	}
	print "\n";
}

sub PutMCode {
	my ($code,$val)=@_;
	$len = length($val);
	print "M $code 1 A $len\n";
	print "W \"$val\"\n";
}

sub PutPointIdent {
	my($ident,$num)=@_;
	print "P $num $ident 1\n";
}

sub PutRelation {
	my($num)=@_;
	print "R B $num\n";
}

sub PutBObjectIdent {
	my($ident,$value,$num)=@_;
	print "B $num $ident 1\n";
	print qq~I "$value"\n~;
}

sub PutLineIdent {
	my($ident,$num,$ncoords)=@_;
	print "L $num $ident $ncoords\n";
}

sub PutAreaIdent {
	my($ident,$num,$ncoords)=@_;
	print "F $num $ident $ncoords\n";
}

sub PutTrailer {
	print "E\n";
}

1;

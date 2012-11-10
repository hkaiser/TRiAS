package MakeASC;

use strict;
use vars qw(@ISA $VERSION);
use MakeAnyThing;

@ISA=qw(MakeAnyThing);
$VERSION="1.0";

use ASC::tree;
use MapOKS;

sub new {
	my($class,$param)=@_;
	my $self={};
	bless $self, ref $class || $class || 'MakeASC';
	return $self->init( $param );
}

sub init {
	my($self,$param)=@_;
	return $self;
}

sub pre_process {
	my($self,$P)=@_;

	$P->{mapType} or return $self->ERROR( qw(ERR_MISSINARG mapType) );
	$P->{mapLayer} or return $self->ERROR( qw(ERR_MISSINARG mapLayer) );
	$P->{mapInfo} or return $self->ERROR( qw(ERR_MISSINARG mapInfo) );
	$P->{sourceDir} or return $self->ERROR( qw(ERR_MISSINGARG sourceDir) );

	my $CUSTOM = {};

	####################################################################
	# der hier sammelt alles zusammen und gibt es am Ende fein hübsch aus
	$CUSTOM->{ASC} = new ASC::tree or return $self->ERROR( qw(ERR_CANNOTCREATEINSTANCE ASC::Tree) );

	####################################################################
	# einen Objektklassenverschlüsseler bauen; er erledigt schon mal einige
	# grundlegende Sachen
	$CUSTOM->{mapOKS} = new MapOKS or return $self->ERROR( qw(ERR_CANNOTCREATEINSTANCE MapOKS) );
	$CUSTOM->{mapOKS}->prepare_header( {mapType=>$P->{mapType},ASC=>$CUSTOM->{ASC}} ) or return $self->ERROR( qw(ERR_CANNOTPREPAREHEADER) );

	$P->{CUSTOM} = $CUSTOM;

	return $self;
}

sub post_process {
	my($self,$P)=@_;

	####################################################################
	# ASC-Datei ausgeben
	$P->{CUSTOM}{ASC}->print_header();
	$P->{CUSTOM}{ASC}->print_body();
	$P->{CUSTOM}{ASC}->print_trailer();

	return $self;
}

sub MakeAnyThing {
	my($self,$M)=@_;
	
	my($W,$H) = ($M->{picture}{256},$M->{picture}{257});

# die Nachfolgenden Berechnungen funktionieren nur für Deutschland
	my $WF = $M->{URFR} - $M->{LLFR};
	my $HF = $M->{URFH} - $M->{LLFH};
	my $WM = $M->{URMR} - $M->{LLMH};
	my $HM = $M->{URMH} - $M->{LLMH};

	my $MLLR = $M->{LLMR} - $M->{LLFR};
	my $MLLH = $M->{LLMH} - $M->{LLFH};
	my $MLRR = $M->{URFR} - $M->{LRMR};
	my $MLRH = $M->{LRMH} - $M->{LLFH};
	my $MURR = $M->{URFR} - $M->{URMR};
	my $MURH = $M->{URFH} - $M->{URMH};
	my $MULR = $M->{ULMR} - $M->{LLFR};
	my $MULH = $M->{URFH} - $M->{ULMH};

	my $PPW = $W / $WF;
	my $PPH = $H / $HF;

	my $MLLRP = int($MLLR * $PPW);
	my $MLLHP = int($MLLH * $PPW);
	my $MLRRP = int($MLRR * $PPH);
	my $MLRHP = int($MLRH * $PPH);
	my $MURRP = int($MURR * $PPW);
	my $MURHP = int($MURH * $PPW);
	my $MULRP = int($MULR * $PPH);
	my $MULHP = int($MULH * $PPH);

# Ausgabekoordinaten für Kartenviereck festlegen
	my $LLOR = $M->{LLMR};
	my $ULOR = $M->{ULMR};
	my $LROR = $M->{LRMR};
	my $UROR = $M->{URMR};
	my $LLOH = $M->{LLMH};
	my $LROH = $M->{LRMH};
	my $ULOH = $M->{URMH};
	my $UROH = $M->{URMH};

	if( $M->{ROTATION} ) {
		if( $LLOR > $ULOR ) {
			$LLOR = $ULOR;
		}
		else {		
			$ULOR = $LLOR;
		}
	
		if( $LROR < $UROR ) {
			$LROR = $UROR;
		}
		else {
			$UROR = $LROR;
		}
	
		if( $LLOH < $LROH ) {
			$LROH = $LLOH;
		}
		else{
			$LLOH = $LROH;
		}
	
		if( $ULOH < $UROH ) {
			$UROH = $ULOH;
		}
		else{
			$ULOH = $UROH;
		}
	}
	
	my($CU)=($M->{CUSTOM});
	my($ASC);
	$CU->{mapOKS}->OKS( {type=>$M->{isa}, layeroks=>$M->{layer}{oks}, scale=>$M->{scale}}, $M )
		or return $self->ERROR( qw(ERR_CANNOTBUILDOKS) );

	$ASC = new ASC::object( {type=>'F',oks=>$M->{OKS},number=>$M->{NUMBER}} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));
	$ASC->set_ident( {ident=>$M->{uniqueident}} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));
	$ASC->set_name( {name=>$M->{ident}} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));
# fje	$ASC->set_property( {name=>q(99999301),value=>qq($M->{outFile}[1]$M->{outFile}[2] $W $H 0 0 0 0 0 0 0 0)} )
	$ASC->set_property( {name=>q(99999301),value=>qq($M->{outFile}[1]$M->{outFile}[2] $W $H $MLLRP $MLLHP $MLRRP $MLRHP $MURRP $MURHP $MULRP $MULHP)} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));
	$ASC->set_property( {name=>q(99999304),value=>qq($M->{layer}{schema}:$M->{layer}{name}:$M->{layer}{description})} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));

# fje	$ASC->set_coords( {coords=>[map { $M->{$_} } qw(LLR LLH URR LLH URR URH LLR URH LLR LLH)]} )
#	$ASC->set_coords( {coords=>[map { $M->{$_} } qw($LLOR $LLOH $LROR $LROH $UROR $UROH $ULOR $ULOH $LLOR $LLOH)]} )
	$ASC->set_coords( {coords=>[$LLOR, $LLOH, $LROR, $LROH, $UROR, $UROH, $ULOR, $ULOH, $LLOR, $LLOH]} )
		or return $self->ERROR(qw(ERR_CANNOTBUILDOBJECT));

	$M->{CUSTOM}{ASC}->add_object( $ASC );
	return $self;
}

1;

__END__

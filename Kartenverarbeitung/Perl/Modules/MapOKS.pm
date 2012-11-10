package MapOKS;

use strict;
use vars qw(@ISA $VERSION);

$VERSION="1.0";
@ISA= qw(BaseObject);

use BaseObject;

sub new {
	my($class)=@_;
	my $self = {};
    bless $self,ref $class || $class;
	return $self->init( );
}

sub DESTROY {
	1;
}

BEGIN {
$MapOKS::OKSBASE = {
	qw(
		TKAS 91
		TKN 92
		TSK 94
		SK 95
		DLB 9c
	) };
$MapOKS::SCALES = {
	qw(
		200 9
		250 a
		400 b
		500 c
		750 d
		1000 5
		2000 6
		4000 7
		5000 8
		10000 1
		25000 2
		50000 3
		100000 4
	) };
$MapOKS::CSYSTEMS = {
		UNKNOWN		=> {qw~~}
		, BESSELGK	=> {qw~CoordTransform BESSELGK CoordMeridian Autoselect CoordStrBreite 3 CoordScaling 1.0 CoordPrecision 2~}
		, BEGEOD	=> {qw~CoordTransform BEGEOD~}
		, KRGEOD	=> {qw~CoordTransform KRGEOD~}
	};
}

sub init {
	my($self)=@_;
	return $self;
}

sub dump_txi {
	my($self,$B,$S,$M)=@_;
	my($s,$l,$OKS);
	print qq~"99999300" /*altes Hintergrundrasterbild*/\n~;
	foreach $s ( sort keys %{ $self->{SCHEMES}{$S} } ) {
		next if( '__PARAM__' eq $s );
		$OKS = $self->OKS($B,$S,$s,$M);
		print qq~"$OKS"~;
		print qq~ /*$B 1:$M Layer $s ($S)*/$self->{SCHEMES}{$S}{$s}[1]~;
		print qq~\n~;
	}
}

sub dump_txm {
print <<'EOF';
99999301 A 1 80 0 /*TK-Info*/Informationen zur Visualisierung topogr. Karten
99999302 B 1 80 0 /*TK-View*/Sichtmerkmal zur Speicherung des Farbschemas einer Sicht
99999303 A 1 80 0 /*TK-Zusatz1*/Zusäzliche beschreibende Informationen für Hintergrundrasterbilder
99999304 A 1 80 0 /*TK-Zusatz2*/Zusätzliche beschreibende Informationen für Hintergrundrasterbilder
99999305 A 1 80 0 /*TK-Zusatz3*/Zusätzliche beschreibende Informationen für Hintergrundrasterbilder
EOF
}

sub prepare_header {
	my($self,$P)=@_;
	$P->{mapType} or return $self->ERROR( qw(ERR_MISSINGARG mapType) );
	$P->{ASC} or return $self->ERROR( qw(ERR_MISSINGARG ASC) );
	my $CS = {};
	$P->{mapType}->TRiASCS( $CS ) or return $self->ERROR( q(ERR_CANNOTFINDCOORDSYSTEM), $P->{mapType} );
	$CS = $CS->{COORDSYSTEM};
	$MapOKS::CSYSTEMS->{ $CS } or return $self->ERROR( 'ERR_UNKNOWNSYSTEM', $CS );
	foreach( keys %{$MapOKS::CSYSTEMS->{$CS}} ) {
		$P->{ASC}->header_value( $_, $MapOKS::CSYSTEMS->{$CS}{$_} );
	}
	return $self;
}

sub OKS {
	my($self,$I,$O)=@_;
	$I->{type} or return $self->ERROR( qw(ERR_MISSINGARG type) );
	defined $I->{layeroks} or return $self->ERROR( qw(ERR_MISSINGARG layeroks) );
	defined $I->{scale} or return $self->ERROR( qw(ERR_MISSINGARG scale) );

	defined $MapOKS::OKSBASE->{$I->{type}} or return $self->ERROR( q(ERR_UNKNOWNTYPE), $I->{type} );
	defined $MapOKS::SCALES->{$I->{scale}} or return $self->ERROR( q(ERR_UNKNOWNSCALE), $I->{scale} );
	$O->{OKS} = qq($MapOKS::OKSBASE->{$I->{type}}$I->{layeroks}$MapOKS::SCALES->{$I->{scale}});
	return $self;
}

sub ident {
	my($self,$B,$F)=@_;
	qq~$B\@$B\@$F~;
}

sub layername {
	my($self,$B,$S,$s)=@_;
	$self->{SCHEMES}{$S}{$s}[1];
}

sub get_base {
	my($self,$S)=@_;
	$self->{SCHEMES}{$S}{__PARAM__}{TYPE};
}

sub get_scale {
	my($self,$S)=@_;
	$self->{SCHEMES}{$S}{__PARAM__}{SCALE};
}

BEGIN {
$MapOKS::ERRMSGS = q(
ERR_CANNOTFINDCOORDSYSTEM
	de	Kann Koordinatensystemdefinition in [%s] nicht finden
ERR_UNKNOWNSCALE
	de	Unbekannter Maßstab [%s]
ERR_UNKNOWNTYPE
	de	Unbekannter Kartentyp [%s]
);
	BaseObject::init_errmsg( $MapOKS::ERRMSGS );
}

1;

=pod

=head1 NAME

MapOKS.pm - Aufbereiten von Objektklassenschlüsseln für topographische Karten

=head1 SYNTAX

 use MapOKS;
 my $MP = new MapOKS;
 ########################################################################
 # Objektklassenschlüssel für eine 
 #   TKAS         ... topogr. Karte AS
 #   TKASCOLOR    ... im Ebenenschema 'TKASCOLOR'
 #   co           ... von dort die Ebene 'co' (Color) 
 #   25000        ... im Maßstab 1:25000
 # zurückliefern
 my $OKS = $MP->( 'TKAS', 'TKASCOLOR', 'co', '25000' );
 

=head1 BESCHREIBUNG

B<MapOKS.pm> bereitet Objektklassenschlüssel sowie eindeutige Identifikatoren 
für Hintergrundrasterbilder auf und enthält (hoffentlich) alle notwendigen Definitionen. 
Der Objektklassenschlüssel für Hintergrundrasterbilder setzt sich aus drei Teilen zusammen:

 BBBLMM

wobei die Teile wie folgt zu interpretieren sind:

=item B<BBB>

Die Basis für den Schlüssel; wird durch den Typ des Hintergrundrasterbildes an sich
festgelegt. So definiert B<911> eine topogr. Karte AS, B<916> eine UTM-Karte.

=item B<L>

Der Kartenlayer. Allgemein bekommt eine Farbkarte stets den Layer B<0>, alle anderen
Layer sind abhängig von den konkreten Verhältnissen. Der TRiAS-eigene Standard ist
wie folgt defdiniert:

	co	0	Farbkarte
	--	1	Grundriß
	--	2	Gebäude
	--	3	Grenzen
	--	4	Gewässer Umriß
	--	5	Gewässer Füllung
	--	6	Vegetation Umriß
	--	7	Vegetation Füllung
	--	8	Relief
	--	9	Beschriftung
	--	f	Herstellerlayer

Die Definitionen für andere Schemata sollten sich möglichst an dieses Schema
anlehnen und können in diesem Modul nachgetragen werden (siehe auch L<MapOKS.pm/LAYERDEFINITIONEN>).

=item B<MM>

Der Maßstab des Hintergrundrasterbildes.

=head1 LAYERDEFINITIONEN

Eine Layerdefinition beginnt stets mit einer Zeile *ohne* Tabulator am
Anfang die den Eintrag an sich definiert, gefolgt von Zeilen mit Tabulator
am Anfang die die einzelnen Layer beschreiben. Zeilen mit '#' am Anfang werden
ignoriert (Kommentar).

Am besten ist die Erläuterung anhand eines Beispiels:

 Bay<TAB>TYPE<TAB>TKN<TAB>SCALE<TAB>25000<TAB>COORDTRANSFORM<TAB>BESSELGK

 # Bay           Unter diesem Namen wird die folgende Definition geführt
 #               hier: Layerkarten des bayer. LVermA
 # TYPE TKN      Voreinstellung für den Basistyp
 # SCALE 25000   Voreinstellung für den Maßstab.
 # COORDTRANSFORM BESSELGK  Wird als Koordinatentransformator in die TRiAS-ASC
 #                          Datei übernommen

 <TAB>co<TAB>0<TAB>Farbkarte
 <TAB>gr<TAB>1<TAB>Grundriß
 <TAB>gk<TAB>4<TAB>Gewässerkontur

 # co          der Farblayer; dieser Layer sollte in jeder Definition vorhanden
 #             sein da alle unbekannten Layer hier eingeordnet werden
 # 0           Der Layer bekommt im OKS die Kennzahl '0'
 # Farbkarte   die ausführliche Bezeichnung für diesen Layer
 # gr 1 ...    Layer mit der Kennung 'gr' sind Grundriß und bekommen OKS '1'
 # ... usw. ...


Bedeutsam ist in der erste Eintrag in den Layerdefinitionen. I.A. wird aus
einem Kartennamen diese Kennung extrahiert und über diese Kennung dem entsprechenden
Layer zugeordnet (siehe hierzu L<DocType.pm>). 

=cut

__DATA__
###################################################################
# allgemeine Farbkarten
TKASCOLOR	TYPE	TKAS	SCALE	10000	COORDTRANSFORM	KRGEOD
	co	0	Top. Karte AS
TKNCOLOR	TYPE	TKN	SCALE	10000	COORDTRANSFORM	BESSELGK
	co	0	Top. Karte N

###################################################################
# Unsere Standardfestlegung für Farbebenendefinitionen
STDLAY	TYPE	TKN	SCALE	25000	COORDTRANSFORM	BESSELGK
	co	0	Farbkarte
	--	1	Grundriß
	--	2	Gebäude
	--	3	Grenzen
	--	4	Gewässer Umriß
	--	5	Gewässer Füllung
	--	6	Vegetation Umriß
	--	7	Vegetation Füllung
	--	8	Relief
	--	9	Beschriftung
	--	f	Herstellerlayer

###################################################################
# Luftbilder
LB50	TYPE	DLB	SCALE	50000	COORDTRANSFORM	BESSELGK
	co	0	Digitales Luftbild


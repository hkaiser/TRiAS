#!/usr/local/bin/perl
#
# runtests [-load] [-nodiff] [-noinsert] [<#test>]
# Copyright (c) 1997, 1998, Regents of the University of California
# $Id: runtests.pl,v 1.3 2000/03/23 02:31:02 mct Exp $
#

($ENV{LIBGISTHOME}) || die "runtests: must set LIBGISTHOME \n";

$ENV{PATH} = "$ENV{LIBGISTHOME}/src/cmdline:" . $ENV{PATH};

@names = ("B-tree_int", "B-tree_str", "R-tree_pt", "R-tree_rect", "R*-tree_pt", "R*-tree_rect", 
	  "RR-tree_point", "SS-tree_point", "SR-tree_point" );
@extns = ("bt_int_ext", "bt_str_ext", "rt_point_ext", "rt_rect_ext", "rstar_point_ext", "rstar_rect_ext", 
	  "rr_point_ext", "ss_point_ext", "sr_point_ext" );
@loads = ("1d_int_bulk", "1d_str_bulk", "2d_pt_bulk", "2d_rect_bulk", "2d_pt_bulk", "2d_rect_bulk", 
	  "2d_pt_bulk", "2d_pt_bulk", "2d_pt_bulk" );
@sorts = ("1d_int_bulk", "1d_str_bulk", "2d_pt_bulk", "2d_rect_bulk", "2d_pt_bulk", "2d_rect_bulk", 
	  "2d_pt_bulk", "2d_pt_bulk", "2d_pt_bulk" );

$loadonly = 0; # false
$bulkload = 1; # true
$nodiff = 0; #false
$noinsert = 0; #false

sub RunAndCheckQueries {

  my($table, $mystd) = @_;

  print "\t Running queries ... \n";

  open(GISTCMD, "| gistcmdline -s > $out ") 
    || die "\t Error in running gistcmdline.";

  print GISTCMD "open $table \n"
    || die "\t Error opening $table.";

  print GISTCMD "check $table \n" 
    || die "\t Error checking $table.";

  open(QRYFILE, $qry) 
    || die "\t Error opening $loads[$i].";

  while (<QRYFILE>) {
    s/_TBLNAME_/$table/;
    print GISTCMD $_
      || die "\t Error: $_.";
  }

  print GISTCMD "check $table \n"
    || die "\t Error checking $table.";
  
  print GISTCMD "quit \n"
    || die "\t Error quitting.";

  close(GISTCMD);
  close(QRYFILE);
   
  if (! $nodiff) {
    print "\t Checking answers ... \n";
      
    open(ANSWER, $out) || die "Couldn't open $out.";
    open(STANDARD, $mystd) || die "Couldn't open $mystd";
    @answers = <ANSWER>;
    @standard = <STANDARD>;
    @answers = sort(@answers);
    @standard = sort(@standard);
      
    $j = @answers; $k = @standard;
    ($j == $k) || die "\t Answers don't match lengths:: $j != $k. \n";
    for ($j = 0; $j < @answers; $j++) {
      ($answers[$j] eq $standard[$j]) 
	|| die "\t Answers don't match:: $answers[$j] :: $standard[$j]. \n";
    }

    close(ANSWER); close(STANDARD);
  }

  (unlink $out) || die "\t Couldn't delete output file.";

}

$i = 0;


foreach $arg (@ARGV) {

  if ($arg eq "-load") {
    $loadonly = 1; #true
  } elsif ($arg eq "-nodiff") {
    $nodiff = 1; #true
  } elsif ($arg eq "-noinsert") {
    $noinsert = 1; #true
  } elsif ($arg < @names) {
    $i = $arg;
  }
  
}


print "Loadonly: $loadonly \n";
print "Nodiff: $nodiff \n";
print "Noinsert: $noinsert \n";
print "Start test: $names[$i] \n";

while ($i < @names) {

  print "Running $names[$i] tests ... \n";

  $pref = $extns[$i];
  $pref =~ s/_ext//;

  # insertion loaded ...

  $tbl = $pref."tbl";
  $out = $pref.".out";
  $std = $pref.".std";

  # bulk loaded ...
  
  $btbl = $tbl.".bulk";
  $bout = $out.".bulk";
  $bstd = $std.".bulk";

  # query file
  
  $qry = $pref.".qry";

  if (! $noinsert) {
    print "\t Testing insertion loading ... \n";

    open(GISTCMD, "| gistcmdline -s > $out ") 
      || die "\t Error in running gistcmdline.";

    print GISTCMD "set echo 0 \n"
      || die "\t Error turning off echo.";

    print GISTCMD "create $tbl $extns[$i]\n" 
      || die "\t Error creating $tbl.";

    open(LOADFILE, $loads[$i]) 
      || die "\t Error opening $loads[$i].";

    while (<LOADFILE>) {
      s/^/insert $tbl /;
      print GISTCMD $_
	|| die "\t Error: $_.";
    }

    print GISTCMD "check $tbl \n"
      || die "\t Error checking $tbl.";
  
    print GISTCMD "quit \n"
      || die "\t Error quitting.";

    close(GISTCMD);
    close(LOADFILE);

    (unlink $out) || die "Couldn't delete output file.";

    if (! $loadonly) {
      RunAndCheckQueries($tbl,$std);
    }

    (unlink $tbl) || die "Couldn't delete table.";
  }

  # Test bulk loading for everything but btrees ...
  if ( ($i >= 2) && ($bulkload) ) {

    print "\t Testing bulk loading ... \n";

    open(GISTCMD, "| gistcmdline > $out ") 
      || die "\t Error in running gistcmdline.";

    print GISTCMD "create $btbl $extns[$i] $sorts[$i] 0.7 \n"
      || die "\t Error creating $btbl.";

    print GISTCMD "check $btbl \n" 
      || die "\t Error checking $tbl.";

    print GISTCMD "quit \n"
      || die "\t Error quitting.";

    close(GISTCMD);
    (unlink $out) || die "\t Couldn't delete output file.";

    if (! $loadonly) {
      RunAndCheckQueries($btbl,$bstd);
    }

    (unlink $btbl) || die "\t Couldn't delete table.";
  }

  $i = $i + 1;
}

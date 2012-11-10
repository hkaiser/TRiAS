#!/usr/bin/perl

($ENV{LIBGISTHOME}) || die "runtests: must set LIBGISTHOME \n";

$ENV{PATH} = "$LIBGISTHOME/src/cmdline:" . $ENV{PATH};

open(GISTCMD, "| gistcmdline ") 
  || die "\t Error in running gistcmdline.";

print GISTCMD "set echo 0 \n" 
  || die "Error turning off echo.";

print GISTCMD "create rt-2-uni rt_point_ext 2d-uni-40000 1.0 \n"
  || die "Error creating rt-2-uni.";

print GISTCMD "create rt-2-clust rt_point_ext 2d-clust-2500 1.0 \n"
  || die "Error creating rt-2-clust.";

print GISTCMD "create rs-2-clust rstar_point_ext 2d-clust-2500 1.0 \n"
  || die "Error creating rt-2-clust.";

print GISTCMD "quit \n"
  || die "Error quitting.";

close(GISTCMD);

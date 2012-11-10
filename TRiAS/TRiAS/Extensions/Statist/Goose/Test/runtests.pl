#!/usr/bin/perl -w

# We scan the README file and extract the mapping between letters and
# test types.
my %types = ();
if (open(IN, "README")) {
    while (<IN>) {
	chomp;
	if (/^([A-Z]) = (\S.+)$/) {
	    $types{$1} = $2;
	}
    }
    close(IN);
}

my @testprogs = sort { $a cmp $b } map { s/\.cpp//; $_ } <test*.cpp>;

my $t1 = time;
my ($tests, $success, $core) = (0,0,0);
$| = 1;
my $last_type = "";
foreach my $prog (@testprogs) {
    unlink "core";

    my ($this_type) = $prog =~ /test_([A-Z])/;
    if ($this_type ne $last_type) {
	print "\n";
	print $types{$this_type} || "Unknown Test Category '$this_type'";
	print ":\n";
    }
    $last_type = $this_type;

    printf("%s: ", $prog);
    ++$tests;

    if (-x "./$prog" && open(IN, "./$prog |")) {

	my $ok=1;
	my @buffer = ();
	while (<IN>) {
	    $ok = 0 if $ok && /failed/;
	    push(@buffer, $_);
	}

	if ($ok) {
	    print "ok";
	    ++$success;
	} else {
	    print "failed";
	}

	if (-e "core") {
	    ++$core;
	    print " (core dumped) ";
	    $ok = 0;
	}
	print "\n";

	unless ($ok) {
	    my $spacer = " " x (2+length($prog));
	    foreach (@buffer) {
		print $spacer, $_;
	    }
	}
    } else {
	print "could not run\n";
    }
}
my $t2 = time;

unlink("core");

print "\n";
printf("Elapsed Time: %3d seconds\n", $t2-$t1);
printf("  # of Tests: %3d\n", $tests);
printf("   Successes: %3d (%6.2f%%)\n", $success, 100*$success/$tests);
printf("    Failures: %3d (%6.2f%%)\n",
       ($tests-$success), 100*($tests-$success)/$tests);
printf("  Core dumps: %3d (%6.2f%%)\n", $core, 100*$core/$tests);

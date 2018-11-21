#! /usr/bin/perl
use strict;
use warnings;

# require './lab08.pl';

use lib '.';
use lab08;


# example function to run a test on addStatusFile
sub testBuildHash()
{
    # create a reference to store the hash table that is built
    my $tref;

    # call the function with file stat1, a non-existent file NoSuchFile,
    #    and file stat2 (example stat1 and stat2 files are in the
    #    repository)
    print "Running on stat1, NoSuchFile, and stat2:\n";
    $tref = buildStatusHash("stat1", "NoSuchFile", "stat2");

    # dereference and print the resulting hash table
    my %statTbl = %$tref;
    my $usr;
    my $stat;
    if (scalar %statTbl) {
       print "resulting pairs:\n";
       foreach $usr (keys %statTbl) {
          $stat = $statTbl{$usr};
          print "$usr: $stat\n";
       }
    } else {
       print "Resulting hash table is empty\n";
    }
}


# run the tests
testBuildHash();


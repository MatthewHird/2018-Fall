#! /usr/bin/perl
use strict;
use warnings;
use Scalar::Util qw(looks_like_number);

package lab08;

require Exporter;
use vars qw(@ISA @EXPORT @EXPORT_OK);
@ISA = qw(Exporter);
@EXPORT = qw(buildStatusHash addStatusFile);

sub buildStatusHash {
    my %statHash;
    foreach my $filename (@_) {
        addStatusFile($filename, \%statHash);
    }
    return \%statHash;
}

our %statusSet = (
    'active' => 1,
    'inactive' => 2,
    'locked' => 3,
    'deleted' => 4,
    'temporary' => 5
);

sub addStatusFile {
    if ((scalar @_) < 2) {
        print "Too few parameters\n";
        return;
    }
    my $filename = $_[0];
    if (Scalar::Util::looks_like_number($filename) || !(-r $filename)) {
        print "Invalid file: $filename\n";
        return;
    }
    my $hashRef = $_[1];
    if (ref($hashRef) ne "HASH"){
        print "Invalid table\n";
        return;
    }
    my $linenum = 0;

    open(FILE, $filename) or warn "oops";
    while (<FILE>) {
        ++$linenum;
        my $line = $_;
        my @word = split(/ /, $line);
        chomp @word;
        my $wordCount = scalar @word;

        if ($wordCount < 2) {
            print "Missing data: line $linenum\n";
            next;
        }
        
        my $username = $word[0];
        unless ($username =~ '^[A-Za-z]{3,8}$') {
            print "Invalid username $username on line $linenum\n";
            next;
        }

        my $userstatus = $word[1]; 
        # valid userstatus: lowercase-> active inactive locked deleted temporary
        unless ($statusSet{$userstatus}) {
            print "Invalid userstatus $userstatus on line $linenum\n";
            next;
        }

        if ($wordCount > 2) {
            print "Extra data ignored: line $linenum\n";
        }

        $$hashRef{$username} = $userstatus;
    }
    close(FILE);
}
1;
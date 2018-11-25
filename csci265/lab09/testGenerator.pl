use strict;
use warnings;

use lib '.';
use lab08;


sub main {
    my $testName = "";
    my @args = ();
    for (my $index = 0; $index < (scalar @args); ++$index) {
        $args[$index] = "Tests/dataFiles/" . $args[$index];
    }

    # genBshTest($testName, @args);
    # genAsfTest($testName, @args);
}


sub genBshTest {
    if ((scalar @_) < 1) {
        print "Error: No arguments provided\n";
        return;
    }
    my $testName = shift @_;
    my @args = @_;

    if (-f "Tests/expectedOutput/bsh/$testName") {
        system(`rm Tests/expectedOutput/bsh/$testName`);
    }
    open(my $expOutput, ">>Tests/expectedOutput/bsh/$testName") 
            or die "Error: Can't open Tests/expectedOutput/bsh/$testName";
    select($expOutput);

    my $expHashRef = buildStatusHash(@args);
    select(STDOUT);
    close($expOutput);
    
    open(my $testDataFile, ">>Tests/testData/bshTests") 
            or die "Error: Can't open Tests/testData/bshTests";
    open(my $expHashesFile, ">>Tests/testData/bshExpectedHashes") 
            or die "Error: Can't open Tests/testData/bshExpectedHashes";

    print $expHashesFile "\n" . $testName . "; ";
    while (my ($key, $value) = each %$expHashRef) {
        print $expHashesFile "$key $value ";
    }

    print $testDataFile "\n" . $testName . "; ";
    for my $argument (@args) {
        print $testDataFile $argument . "; ";
    }

    close($testDataFile);
    close($expHashesFile);
}


sub genAsfTest {
    if ((scalar @_) < 1) {
        print "Error: No arguments provided\n";
        return;
    }
    my $testName = shift @_;
    my @args = @_;

    if (-f "Tests/expectedOutput/asf/$testName") {
        system(`rm Tests/expectedOutput/asf/$testName`);
    }
    open(my $expOutput, ">>Tests/expectedOutput/asf/$testName") 
            or die "Error: Can't open Tests/expectedOutput/asf/$testName";
    select($expOutput);

    my %expHash = ();
    my $expHashRef = \%expHash;
    addStatusFile(@args, $expHashRef);
    
    select(STDOUT);
    close($expOutput);
    
    open(my $testDataFile, ">>Tests/testData/asfTests") 
            or die "Error: Can't open Tests/testData/asfTests";
    open(my $expHashesFile, ">>Tests/testData/asfExpectedHashes") 
            or die "Error: Can't open Tests/testData/asfExpectedHashes";

    print $expHashesFile "\n" . $testName . "; ";
    while (my ($key, $value) = each %$expHashRef) {
        print $expHashesFile "$key $value ";
    }

    print $testDataFile "\n" . $testName . "; ";
    for my $argument (@args) {
        print $testDataFile $argument . "; ";
    }

    close($testDataFile);
    close($expHashesFile);
}


main();
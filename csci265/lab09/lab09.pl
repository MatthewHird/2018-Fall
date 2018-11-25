#! /usr/bin/perl

use strict;
use warnings;

use lib '.';
use lab08;
# use brokenLab08;

use Test::More tests=>2;


sub main {
    runBshTests();
    runAsfTests();
}


sub runBshTests {
    subtest 'buildStatusHash()' => sub {
        open(my $testDataFile, "<Tests/testData/bshTests");
        my @testDataLines = <$testDataFile>;
        chomp @testDataLines;
        close($testDataFile);

        open(my $expHashFile, "<Tests/testData/bshExpectedHashes");
        my @expLines = <$expHashFile>;
        chomp @expLines;
        close($expHashFile);

        my %expHash = ();

        for my $line (@expLines) {
            my @tempArray = split(/; /, $line);
            if ((scalar @tempArray) < 2) {
                $tempArray[1] = "";
            }
            $expHash{$tempArray[0]} = $tempArray[1]; 
        }

        my $testDataCount = scalar @testDataLines;

        plan tests=>($testDataCount);

        BAIL_OUT("expectedHashFile and testDataFile have different numbers of lines") 
                if ($testDataCount != (scalar @expLines));


        for (my $index = 0; $index < $testDataCount; ++$index) {
            my @testData = split(/; /, $testDataLines[$index]);
            my $testName = shift @testData;
            my %expReturn = split(/ /, $expHash{$testName});

            if (-f "testOutput") {
                system(`rm testOutput`);
            }

            subtest "$testName" => sub {
                plan tests=>2;
                open(my $testOut, ">>testOutput") or die;
                select($testOut);

                is_deeply(buildStatusHash(@testData), \%expReturn, "Returned Hash");
                
                open(my $expOut, "<Tests/expectedOutput/bsh/" . $testName) or die;
                open($testOut, "<testOutput") or die;
                
                is(do { local $/; <$testOut> }, do { local $/; <$expOut> }, "Output");
                
                select(STDOUT);
                close($testOut) or die;
                system(`rm testOutput`);
                close($expOut) or die;
            };
        }
    };
}


sub runAsfTests {
    subtest 'addStatusFile()' => sub {
        open(my $testDataFile, "<Tests/testData/asfTests");
        my @testDataLines = <$testDataFile>;
        chomp @testDataLines;
        close($testDataFile);

        open(my $expHashFile, "<Tests/testData/asfExpectedHashes");
        my @expLines = <$expHashFile>;
        chomp @expLines;
        close($expHashFile);

        my %expHash = ();

        for my $line (@expLines) {
            my @tempArray = split(/; /, $line);
            if ((scalar @tempArray) < 2) {
                $tempArray[1] = "";
            }
            $expHash{$tempArray[0]} = $tempArray[1]; 
        }

        my $testDataCount = scalar @testDataLines;

        plan tests=>($testDataCount + 1);

        BAIL_OUT("expectedHashFile and testDataFile have different numbers of lines") 
                if ($testDataCount != (scalar @expLines));

        # Test for "invalid_hash"
        my @tempArray = ("Tests/dataFiles/blankFile");
        singleAsfTest("invalid_table", \@tempArray, "notAHash", "notAHash");

        # All tests from '/Tests/testData/asfTests'
        for (my $index = 0; $index < $testDataCount; ++$index) {
            my @testData = split(/; /, $testDataLines[$index]);
            my $testName = shift @testData;
            my %expReturn = split(/ /, $expHash{$testName});

            my %newHash = ();

            singleAsfTest($testName, \@testData, \%expReturn, \%newHash);
        }
    };
}


sub singleAsfTest {
    my $testName = shift @_;    # string
    my $testData = shift @_;    # array ref
    my $expReturn = shift @_;   # hash ref
    my $newHash = shift @_;     # hash ref

    subtest "$testName" => sub {
        if (-f "testOutput") {
            system(`rm testOutput`);
        }

        plan tests=>2;
        open(my $testOut, ">>testOutput") or die;
        select($testOut);

        addStatusFile(@$testData, $newHash);
        is_deeply($newHash, $expReturn, "Modified Hash");
        
        open(my $expOut, "<Tests/expectedOutput/asf/" . $testName) or die;
        open($testOut, "<testOutput") or die;
        
        is(do { local $/; <$testOut> }, do { local $/; <$expOut> }, "Output");
        
        select(STDOUT);
        close($testOut) or die;
        system(`rm testOutput`);
        close($expOut) or die;
    };
}


main();

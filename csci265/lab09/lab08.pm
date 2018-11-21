#! /usr/bin/perl
use strict;
use warnings;
use Scalar::Util qw(looks_like_number);

package lab08;

require Exporter;
use vars qw(@ISA @EXPORT @EXPORT_OK);
@ISA = qw(Exporter);
@EXPORT = qw(buildStatusHash addStatusFile);

# buildStatusHash
# ---------------
# This function takes zero or more parameters, each of which
#    is assumed to be the name of a readable file.
#
# Note the function must not display any output.
#
# The function declares an empty hash table, and for each of the
#    files passed as parameters it calls function addStatusFile,
#    passing the filename and a reference to the hash table as parameters.
#
# After all files have been processed, the function returns a reference
#    to the constructed hash table.
sub buildStatusHash
{
    my %statHash;

    foreach my $filename (@_) {
        addStatusFile($filename, \%statHash);
    }

    return \%statHash;
}


# addStatusFile
# -------------
# This function expects two parameters:
#    (first)  a filename
#    (second) a reference to a hash table
#
# Note the function must not display any output other than
#    the precise error/warning messages described below.
#
# Parameter error checking:
#    Errors are checked in the order specified below, so at most one
#        error message can be associated with parameter checking.
#    If too few parameters are supplied the function displays the
#       error message "Too few parameters\n" and returns.
#    If the first parameter is not a string, or if it does not
#       represent a readable file then the function displays the
#       error message "Invalid file: filename\n" and returns
#       (substituting the actual file name of course).
#    If the second parameter is not a reference to a hash table
#       the function displays the error message "Invalid table\n"
#       and returns.
#    Any extra parameters are simply ignored.
#
# Behaviour if given valid file/table:
#    The function reads each line of the file, treating the
#       first word of each line as a username, and the second
#       word of each line to describe a user status.  (Words
#       must be separated by spaces.)
#    (Note that a file may be empty, this is acceptable
#        and should not generate any error or warning.)
#    It checks that the line contains a valid username and status,
#       and, if so, adds or updates the hash table where the username
#       is treated as the key and the status as the associated value.
#    Valid usernames must be strictly alphabetic (uppercase, lowercase,
#       or a mix is acceptable) and must be at least 3 characters long
#       and at most 8 characters long.
#    Valid status values are as follows (all strictly lowercase):
#       active inactive locked deleted temporary
#
# File content error checking:
#     Errors are checked in the order specified below, so at most one
#        error message can be associated with any one line of the file.
#     N in each of the "line N" messages below should be replaced with
#        the line number, assuming the first line of the file is line 1.
#     Similarly, Name and Status should be replaced with the offending
#        username or status value.
#     If a line contains too few words the function displays the
#        error message "Missing data: line N\n" then proceeds immediately
#        to the next line.
#     If a line contains an invalid username the function displays the
#        error message "Invalid username Name on line N\n" then proceeds immediately
#        the next line.
#     If the username was valid but the status is not then the function
#        displays the error message "Invalid userstatus Status on line N\n" then
#        proceeds immediately to the next line.
#     If a line had a valid username and status but contains extra words afterward,
#        the function processes the first two words normally but then displays the
#        error message "Extra data ignored: line N\n".

our %statusSet = (
    'active' => 1,
    'inactive' => 2,
    'locked' => 3,
    'deleted' => 4,
    'temporary' => 5
);

sub addStatusFile
{
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
        $line =~ tr/\n//d;
        my @word = split(/ /, $line);
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

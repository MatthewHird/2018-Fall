#! /bin/bash

if [ $# -ne 1 ] ; then
    echo "Incorrect number of arguments"
    exit 1
elif [[ ! -e "$1" ]] ; then
    echo "$1 does not exist"
    exit 2
elif [[ ! -d $1 ]] ; then
    echo "$1 is not a directory"
    exit 3
fi

endInSlash='/$'
arg=$1

if ! [[ $arg =~ $endInSlash ]] ; then
    arg="$arg/"
fi

function dirAccess()
{
    if [[ -d $1 ]] ; then
        if [[ -r $1 ]] && [[ -x $1 ]] ; then
            echo "    Accessible directory: $1"
            for dir in "$1"*/ ; do
                dirAccess "$dir"
            done
        fi
    fi
}

echo -e "\n*** List of accessible directories within $arg: ***"
dirAccess "$arg"
echo -e "*** End of list ***\n"

exit 0
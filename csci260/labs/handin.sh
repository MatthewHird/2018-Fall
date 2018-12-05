#! /bin/bash

for dir in $(ls); do 
    if [[ -d $dir ]]; then
        x=$(
            labNum=$(
                rName=$dir
                rName=${rName##lab}
                rName=${rName%/}
                rName=${rName##0}
                echo $rName
            )
            cd "$dir"
            ~liuh/bin/submit 260 "Lab$labNum" .
        )
    fi
done

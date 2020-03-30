#!/bin/bash
if [[ $# -ne 1 ]]; then
    echo "Invalid Argument"
else 
    git add *
    git commit -m ${1}
    git push
fi

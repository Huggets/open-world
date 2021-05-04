#!/bin/bash
# Bash file that indicate if a file in src/ contains the word TODO

for i in $(find src/*); do
    if cat $i | grep TODO >> /dev/null; then
        echo "The file $i contains TODO"
    fi
done

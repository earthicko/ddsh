#!/bin/bash

candidates="
$HOME/.brew/opt/readline 
/usr/local/opt/readline"

echo "Creating symlink to readline library"

if [ -d $(pwd)/modules/readline ]
then
    echo "readline library already linked"
    exit 0
fi

for DIR in $candidates
do
    if [ -d $DIR ]
    then
        echo "Found directory $DIR"
        ln -s $DIR $(pwd)/modules/readline
        exit 0
    fi
done

echo "Couldn't find readline from: $candidates"
exit 1

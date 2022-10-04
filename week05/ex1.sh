#!/bin/bash

# Compile the programs
gcc ./publisher.c -o publisher
gcc ./subscriber.c -o subscriber

# Run publisher
gnome-terminal -- "$(pwd)/publisher" $1 &

# Run subscribers
for i in $(seq 1 $1)
do
    gnome-terminal -- "$(pwd)/subscriber" $i &
done

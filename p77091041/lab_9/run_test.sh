#!/bin/bash
TIMEFORMAT=%R
gcc -O2 -o pi pi.c

function repeat() {
    for ((i=0;i<$1;i++)); do
        printf "| trial $i | %s |\n" "$(eval time ${*:2} 2>&1 | tr -d '\n')"
    done
}

printf "clock rate:\n"
lscpu | grep MHz | head -n 1

# Print the configuration
head -n 6 pi.c
printf "| Trials | pi | Cycle/CPU rate (s) | Get time (s) | time command (s) |\n"
printf "|-:|-:|-:|-:|-:|\n"
repeat 10 ${*:1}
rm pi

unset TIMEFORMAT


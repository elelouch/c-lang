#!/bin/sh
[ $# -ne 1 ] && echo "Requires at least one argument" && exit 1
file=$1
count=0
total_lines=$(wc --l $file | awk '{print $1}')

while [ $count -le $total_lines ] ; do
    tail -n $count $file | head -n 1
    ((count++))
done

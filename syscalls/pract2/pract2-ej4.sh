#!/bin/sh
[ $# -ne 1 ] && echo "Requires at least one absolute path" && exit 1
[ ! -d $1 ] && echo "Path not valid" && exit 1
dir=$1
n_compr="file.tar.bz2" 
size_before=$(du $dir -h -b | tail -n 1 | awk '{print $1}')
tar -cvjSf $n_compr $dir
size_after=$(du file.tar.bz2 -h -b | tail -n 1 | awk '{print $1}')

echo "Before compression : $size_before. After compression : $size_after."


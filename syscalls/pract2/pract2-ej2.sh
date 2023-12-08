#!/bin/sh
echo "Ingrese fecha con el siguiente formato : dd-mm-aaaa"
read fecha
date -d "$(echo $fecha | tr '-' '\n' | tac | tr '\n' '-' | sed 's/.$/\n/')" "+%A"

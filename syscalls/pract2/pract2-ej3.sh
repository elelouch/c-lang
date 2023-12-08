#!/bin/sh
echo "Ingrese fecha con el siguiente formato : dd-mm-aaaa"
read fecha
fecha="$(echo $fecha | tr '-' '\n' | tac | tr '\n' '-' | sed 's/.$/\n/')" 

echo $fecha
birth_epoch=$(date -d $fecha "+%s")
now_epoch=$(date "+%s")
S_TO_D=$((60*60*24))
echo $(( ($now_epoch - $birth_epoch) / $S_TO_D ))

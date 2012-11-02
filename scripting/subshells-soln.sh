#! /bin/bash

if test -f out2; then
  echo "output file already exists"
  exit 1
fi

(
I=100
for J in $(seq 30); do 
  echo $I; ./some-timing $I
  I=$((I*110/100))
done
) > out

while read I; do
  read A B C D
  echo $I $C
done < out > out2

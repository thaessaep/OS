#!/bin/bash

read var
mkdir $var

for file in *.txt
 do
  dir_name="`pwd`/${var}/${file%.*}"
  mkdir $dir_name
  cp $file $dir_name
 done

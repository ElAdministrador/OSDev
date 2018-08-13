#!/bin/bash

set -e
. ./headers.sh
 
for PROJECT in $PROJECTS; do
  echo $PROJECT
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install)
done
#!/bin/bash

# Install all the system headers into the system root without relying on the compiler

set -e
. ./config.sh
 
mkdir -p "$SYSROOT"
 
for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done
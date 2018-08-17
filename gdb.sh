#!/bin/bash

set -e
. ./clean.sh
. ./build.sh

# for GDB on localhost:1234
qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/deros.bin -s -S &
gnome-terminal -e 'gdb --command=gdb_commands --nh' #--maximize 

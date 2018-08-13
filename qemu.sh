#!/bin/sh

set -e
. ./clean.sh
. ./build.sh
#. ./iso.sh
 
#qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom deros.iso
qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel sysroot/boot/deros.bin

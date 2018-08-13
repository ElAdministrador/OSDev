#!/bin/bash

set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/deros.kernel isodir/boot/deros.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "deros" {
	multiboot /boot/deros.kernel
}
EOF
#grub-mkrescue -o deros.iso isodir
grub-mkrescue -o deros.iso --xorriso=$HOME/src/xorriso-1.4.6/xorriso/xorriso sysroot
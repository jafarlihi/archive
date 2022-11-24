#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/hikmatos.kernel isodir/boot/hikmatos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "hikmatos" {
	multiboot /boot/hikmatos.kernel
}
EOF
grub-mkrescue -o hikmatos.iso isodir


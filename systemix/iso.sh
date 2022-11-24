#!/usr/bin/env bash

make

mkdir -p build/isodir
mkdir -p build/isodir/boot
mkdir -p build/isodir/boot/grub

cp systemix build/isodir/boot/systemix
cat > build/isodir/boot/grub/grub.cfg << EOF
menuentry "systemix" {
	multiboot /boot/systemix
}
EOF
grub-mkrescue -o systemix.iso build/isodir


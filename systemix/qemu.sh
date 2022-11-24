#!/usr/bin/env bash
set -e

. ./iso.sh

qemu-system-i386 -cdrom systemix.iso -D ./log -d guest_errors -d pcall -d int -no-shutdown -no-reboot -monitor stdio


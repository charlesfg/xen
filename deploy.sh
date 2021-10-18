#!/bin/bash -x
set -e

make dist-xen
make dist-tools
bash install.sh
/sbin/ldconfig 
sudo update-grub
reboot

#!/bin/bash -x
set -e

make dist-xen
bash install.sh
/sbin/ldconfig 
sudo update-grub
reboot

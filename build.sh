set -e
make dist-xen
cd dist
sh -x install.sh
cd ..
/sbin/ldconfig
sudo update-grub

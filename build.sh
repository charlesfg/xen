set -e
make dist-xen
make dist-tools
cd dist
sh -x install.sh
cd ..
/sbin/ldconfig
sudo update-grub

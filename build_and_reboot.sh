set -e
make dist-xen
cd dist
sh -x install.sh
cd ..
/sbin/ldconfig
sudo update-grub
set +e
xl shutdown guest01
xl shutdown guest02
sleep 10
reboot

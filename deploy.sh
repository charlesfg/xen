set -e
sh -x install.sh
/sbin/ldconfig
sudo update-grub
reboot

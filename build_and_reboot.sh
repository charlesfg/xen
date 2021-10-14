set -e
make dist-xen
if [ -e install.sh ];
then
    sh -x install.sh
else
    cd dist
    sh -x install.sh
fi
cd ..
/sbin/ldconfig
sudo update-grub
set +e
xl shutdown guest01
xl shutdown guest02
xl shutdown guest03
sleep 3
reboot

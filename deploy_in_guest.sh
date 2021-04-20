for i in guest01 guest02;
do
    scp xen/include/public/attack.h  ${i}:/usr/src/linux-headers-3.13.0-170/include/xen/interface/attack.h
one

for i in guest01 guest02;
do
    scp xen/include/public/effector.h  ${i}:/usr/src/linux-headers-3.13.0-170/include/xen/interface/effector.h
done

scp xen/include/public/effector.h guest03:/usr/src/linux-headers-4.4.0-040400/include/xen/interface/effector.h

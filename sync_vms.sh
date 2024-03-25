function help()
{
    echo "$0 Sync the guest01 and guest02 testing machines from oxum and xen-dev"
    echo -e "\t This should be runned in the Xen-Dev Host only\n\n"
    echo "usage: $0 [spec]"
    echo -e "ex. $0 [toOxum]\n"
    echo "Specs:"
    echo -e "\t toOxum : sync to oxum"
    echo -e "\t fromOxum : sync from oxum to update here!"

}
[ "$1" ] || { help; exit 1; }

if [[ ! "$1" =~ ^(to|from)Oxum$ ]];
then
    help;
    exit;
fi
if [ $(hostname) != 'xendev' ];
then
    echo "host should be the xendev machine"
    exit;
fi

if [ "$1" ==  "toOxum" ];
then
    echo "Copying to oxum"
    SRC=
    DST=root@150.164.203.68:
elif [ "$1" == "fromOxum" ];
then
    echo "Syncing from Oxum"
    SRC=root@150.164.203.68:
    DST=
else
    echo "Treta!"
    help;
    exit;
fi

set -x
for f in \
    /etc/xen/guest01.cfg \
    /etc/xen/guest02.cfg \
    /var/xen-images/domains/guest01 \
    /var/xen-images/domains/guest02;
do
    rsync -avz ${SRC}${f} ${DST}${f}
done



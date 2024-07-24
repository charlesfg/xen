make clean -j 

./configure \
	--enable-systemd \
	--enable-debug

/home/xen/.local/bin/compiledb make debug=y -j	2


sudo make install

sudo /sbin/ldconfig

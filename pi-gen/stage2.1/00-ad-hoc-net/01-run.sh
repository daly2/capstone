#!/bin/bash -e

#### Set up batman

on_chroot << EOF
mkdir /tmp/batctl-install

cd /tmp/batctl-install || exit 1
wget https://downloads.open-mesh.org/batman/stable/sources/batctl/batctl-2020.4.tar.gz
tar -xf batctl-2020.4.tar.gz
cd batctl-2020.4 || exit 1
make
make install
EOF

install -m 644 files/batman-start.service "${ROOTFS_DIR}/etc/systemd/system/batman-start.service"
install -m 700 files/mesh.sh "${ROOTFS_DIR}/usr/local/sbin/mesh.sh"

on_chroot << EOF
echo 'batman-adv' >> /etc/modules

systemctl enable batman-start.service
EOF

echo '172.27.1.2' > /boot/mesh-ip

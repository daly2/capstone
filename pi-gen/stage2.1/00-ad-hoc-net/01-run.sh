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
install -m 755 files/batman-start.sh "${ROOTFS_DIR}/usr/local/sbin/batman-start.sh"

on_chroot << EOF
echo 'batman-adv' >> /etc/modules

systemctl enable batman-start.service
EOF

install -m 644 files/bat0 "${ROOTFS_DIR}/etc/network/interfaces.d/bat0"
install -m 644 files/wlan0 "${ROOTFS_DIR}/etc/network/interfaces.d/wlan0"

cat << EOF >> "${ROOTFS_DIR}/etc/dhcpcd.conf"

denyinterfaces wlan0,bat0
EOF

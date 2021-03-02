#!/bin/bash

if [ $EUID -ne 0 ]
then
  echo "Please run as sudo"
  exit 1
fi

mkdir /tmp/batctl-install

(
  cd /tmp/batctl-install || exit 1
  wget https://downloads.open-mesh.org/batman/stable/sources/batctl/batctl-2020.4.tar.gz
  tar -xf batctl-2020.4.tar.gz
  cd batctl-2020.4 || exit 1
  make
  make install
)

if ! grep 'batman-adv' /etc/modules &> /dev/null
then
  echo 'batman-adv' >> /etc/modules
fi

sed -i 's/interface eth0/interface usb0/' /etc/dhcpcd.conf
sed -i 's/interface wlan0/denyinterfaces wlan0,bat0/' /etc/dhcpcd.conf
sed -i 's/metric 202//' /etc/dhcpcd.conf

cat << EOF > /usr/local/sbin/batman-start.sh
#!/bin/bash
sudo batctl if add wlan0

sudo ifconfig wlan0 up
sudo ifconfig bat0 up
EOF

chmod +x /usr/local/sbin/batman-start.sh

cat << EOF > /lib/systemd/system/batman-start.service
[Unit]
Description=Start batman interface
Before=multi-user.target

[Service]
Type=idle
ExecStart=/usr/local/sbin/batman-start.sh

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable batman-start.service

cat << EOF > /etc/network/interfaces.d/bat0
auto bat0
iface bat0 inet auto
    pre-up /usr/sbin/batctl if add wlan0
EOF

cat << EOF > /etc/network/interfaces.d/wlan0
auto wlan0
iface wlan0 inet manual
    mtu 1532
    wireless-channel 1
    wireless-essid cap-net
    wireless-mode ad-hoc
    wireless-ap 02:12:34:56:78:9A
EOF

echo "Rebooting in 5 seconds"
sleep 5
reboot

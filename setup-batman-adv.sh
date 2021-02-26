#!/bin/bash

apt install -y batctl

if ! grep 'batman-adv' /etc/modules &> /dev/null
then
  echo 'batman-adv' >> /etc/modules
fi

sed -i 's/^interface eth0/#interface eth0/' /etc/dhcpcd.conf
sed -i 's/^metric 302/#metric 302/' /etc/dhcpcd.conf
sed -i 's+^static ip-address=172.27.0.254/24+#static ip-address=172.27.0.254/24+' /etc/dhcpcd.conf
sed -i 's/^static routers=172.27.0.1/#static routers=172.27.0.1/' /etc/dhcpcd.conf
sed -i 's/^static domain_name_servers=172.27.0.1/#static domain_name_servers=172.27.0.1/' /etc/dhcpcd.conf
sed -i 's/^nolink/#nolink/' /etc/dhcpcd.conf
sed -i 's/interface wlan0/deny-interfaces wlan0/' /etc/dhcpcd.conf
sed -i 's/metric 202//' /etc/dhcpcd.conf

cat << EOF > /usr/bin/start-batman-adv.sh
sudo batctl if add wlan0

sudo ifconfig wlan0 up
sudo ifconfig bat0 up
EOF

chmod +x /usr/bin/start-batman-adv.sh

cat << EOF > /lib/systemd/system/batman-start.service
[Unit]
Description=Start batman interface
Before=multi-user.target

[Service]
Type=idle
ExecStart=/usr/bin/start-batman-adv.sh

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

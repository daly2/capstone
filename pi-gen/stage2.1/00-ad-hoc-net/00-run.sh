#!/bin/bash -e

# Set up SSH over USB

echo -n "Configure /boot/config.txt..."
echo 'dtoverlay=dwc2' >> "${ROOTFS_DIR}/boot/config.txt"
echo -e "\e[32mdone\3[0m"

echo -n "Configure /boot/cmdline.txt..."
sed -i 's/rootwait/rootwait modules-load=dwc2,g_ether/' "${ROOTFS_DIR}/boot/cmdline.txt"
echo -e "\e[32mdone\e[0m"


# Set static IP

echo -n "Configuring usb0..."
cat << EOF >> "${ROOTFS_DIR}/etc/dhcpcd.conf"

interface usb0
static ip_address=172.27.0.254/24
static routers=172.27.0.1
static domain_name_servers=172.27.0.1
nolink
EOF
echo -e "\e[32mdone\e[0m"


# Add usb0 to DHCP server

echo -n "Adding usb0 to DHCP server..."
sed -i 's/INTERFACESv4=""/INTERFACESv4="usb0"/g' "${ROOTFS_DIR}/etc/default/isc-dhcp-server" 
echo -e "\e[32mdone\e[0m"


# Configure DHCP server

echo -n "Removing DHCP server domain-name option..."
sed -i 's/option domain-name \"example.org\";//g' "${ROOTFS_DIR}/etc/dhcp/dhcpd.conf"
echo -e "\e[32mdone\e[0m"

echo -n "Removing DHCP server domain-name-servers option..."
sed -i 's/option domain-name-servers ns1.example.org, ns2.example.org;//g' "${ROOTFS_DIR}/etc/dhcp/dhcpd.conf"
echo -e "\e[32mdone\e[0m"

echo -n "Adding 172.27.0.* subnet to DHCP server..."
cat << EOF >> "${ROOTFS_DIR}/etc/dhcp/dhcpd.conf"

subnet 172.27.0.0 netmask 255.255.255.0 {
  range 172.27.0.2 172.27.0.253;
  option subnet-mask 255.255.255.0;
  option broadcast-address 172.27.0.255;
  option routers 172.27.0.254;
  option domain-name-servers 172.27.0.1;
  default-lease-time 600;
  max-lease-time 7200;
}
EOF
echo -e "\e[32mdone\e[0m"


# Configure DHCP server service

echo -n "Adding restart.conf to isc-dhcp-server.service.d..."
install -m 755 -d "${ROOTFS_DIR}/etc/systemd/system/isc-dhcp-server.service.d"
install -m 644 files/restart.conf "${ROOTFS_DIR}/etc/systemd/system/isc-dhcp-server.service.d/restart.conf"
echo -e "\e[32mdone\e[0m"


# Enable dhcp server

echo "Configuring isc-dhcp-server systemd service to run at startup..."
on_chroot << EOF
systemctl enable isc-dhcp-server
EOF
echo -e "\e[2mConfiguring isc-dhcp-server systemd service to run at startup...\e[22;32mdone\e[0m"


# Configure DHCP server service

echo -n "Adding restart.conf to dhcpcd.service.d..."
install -m 755 -d "${ROOTFS_DIR}/etc/systemd/system/dhcpcd.service.d"
install -m 644 files/restart.conf "${ROOTFS_DIR}/etc/systemd/system/dhcpcd.service.d/restart.conf"
echo -e "\e[32mdone\e[0m"

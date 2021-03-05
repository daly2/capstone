#!/bin/bash

sudo modprobe batman-adv

killall wpa_supplicant

sudo ip link set wlan0 down
sudo ifconfig wlan0 mtu 1500
sudo iwconfig wlan0 mode ad-hoc
sudo iwconfig wlan0 essid cap-net
sudo iwconfig wlan0 ap any
sudo iwconfig wlan0 channel 8
sleep 1s

sudo ip link set wlan0 up
sleep 1s

sudo batctl if add wlan0
sleep 1s

sudo ifconfig bat0 up
sleep 5s

sudo ifconfig bat0 "$(sudo cat /boot/mesh-ip)/16"

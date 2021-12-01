#!/bin/sh

xrandr --output HDMI-1-1 --mode 1360x768 --primary --output eDP-1-1 --auto --right-of HDMI-1-1
xset s off -dpms
nitrogen --restore &
picom &
dunst &
nm-applet &
volumeicon &
blueman-applet &
slstatus &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

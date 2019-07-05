#!/bin/bash

# Use to install appimage in linux

case "$1" in
    remove)
        echo "remove ..."
        rm -f /usr/share/applications/Tasks.desktop
        rm -f /etc/xdg/autostart/Tasks.desktop
        rm -f /usr/share/pixmaps/Tasks.png
    ;;

    install|*)
        echo "install ..."
        if [ -f /usr/share/applications/Tasks.desktop ]; then
            rm /usr/share/applications/Tasks.desktop
        fi
        ln -s `pwd`/share/applications/Tasks.desktop /usr/share/applications/Tasks.desktop

        if [ -f /etc/xdg/autostart/Tasks.desktop ]; then
            rm /etc/xdg/autostart/Tasks.desktop
        fi
        ln -s `pwd`/share/applications/Tasks.desktop /etc/xdg/autostart/Tasks.desktop

        sed -i "s/Exec=.*//g" `pwd`/share/applications/Tasks.desktop
        echo "Exec=`pwd`/Tasks-x86_64.AppImage" >> `pwd`/share/applications/Tasks.desktop

        if [ -f /usr/share/pixmaps/Tasks.png ]; then
            rm /usr/share/pixmaps/Tasks.png
        fi
        if [ ! -d /usr/share/pixmaps ]; then
            mkdir -p /usr/share/pixmaps
        fi
        ln -s `pwd`/share/pixmaps/Tasks.png /usr/share/pixmaps/Tasks.png
        ;;
esac

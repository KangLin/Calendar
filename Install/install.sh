#!/bin/bash

# Use to install appimage in linux
# $1: install or remove
# $2: run

case "$1" in
    remove)
        echo "remove ..."
        rm -f /usr/share/applications/Calendar.desktop
        rm -f ~/.config/autostart/Calendar.desktop
        rm -f /usr/share/pixmaps/Calendar.png
    ;;

    install|*)
        echo "install ..."
        # Install destop
        if [ -f /usr/share/applications/Calendar.desktop ]; then
            rm /usr/share/applications/Calendar.desktop
        fi
        ln -s `pwd`/share/applications/Calendar.desktop /usr/share/applications/Calendar.desktop

        # Install auto run on boot
        if [ ! -d ~/.config/autostart ]; then
            mkdir -p ~/.config/autostart
            chmod a+wr ~/.config/autostart
        fi
        if [ -f ~/.config/autostart/Calendar.desktop ]; then
            rm ~/.config/autostart/Calendar.desktop
        fi
        ln -s `pwd`/share/applications/Calendar.desktop ~/.config/autostart/Calendar.desktop

        # Reset exec to desktop
        sed -i "s/Exec=.*//g" `pwd`/share/applications/Calendar.desktop
        echo "Exec=`pwd`/Calendar-x86_64.AppImage" >> `pwd`/share/applications/Calendar.desktop

        # Install applications icon
        if [ -f /usr/share/pixmaps/Calendar.png ]; then
            rm /usr/share/pixmaps/Calendar.png
        fi
        if [ ! -d /usr/share/pixmaps ]; then
            mkdir -p /usr/share/pixmaps
        fi
        ln -s `pwd`/share/pixmaps/Calendar.png /usr/share/pixmaps/Calendar.png
        
        # Whether run after install
        if [ "$2" = "run" ]; then
            ./Calendar-x86_64.AppImage
        fi
        ;;
esac

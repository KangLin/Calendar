#!/bin/bash

# Use to install appimage in linux
# $1: install or remove
# $2: run

case "$1" in
    remove)
        echo "remove ..."
        rm -f /usr/share/applications/org.Rabbit.Calendar.desktop
        rm -f ~/.config/autostart/org.Rabbit.Calendar.desktop
        rm -f /usr/share/pixmaps/Calendar.png
    ;;

    install|*)
        echo "install ..."
        # Install desktop
        if [ -f /usr/share/applications/org.Rabbit.Calendar.desktop ]; then
            rm /usr/share/applications/org.Rabbit.Calendar.desktop
        fi
        ln -s `pwd`/share/applications/org.Rabbit.Calendar.desktop /usr/share/applications/org.Rabbit.Calendar.desktop

        # Install auto run on boot
        if [ ! -d ~/.config/autostart ]; then
            mkdir -p ~/.config/autostart
            chmod a+wr ~/.config/autostart
        fi
        if [ -f ~/.config/autostart/org.Rabbit.Calendar.desktop ]; then
            rm ~/.config/autostart/org.Rabbit.Calendar.desktop
        fi
        ln -s `pwd`/share/applications/org.Rabbit.Calendar.desktop ~/.config/autostart/org.Rabbit.Calendar.desktop

        # Reset exec to desktop
        sed -i "s/Exec=.*//g" `pwd`/share/applications/org.Rabbit.Calendar.desktop
        echo "Exec=`pwd`/Calendar-x86_64.AppImage" >> `pwd`/share/applications/org.Rabbit.Calendar.desktop

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

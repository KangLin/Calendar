#!/bin/bash

# Use to install appimage in linux
# $1: install or remove
# $2: run

case "$1" in
    remove)
        echo "remove ..."
        rm -f /usr/share/applications/Tasks.desktop
        rm -f ~/.config/autostart/Tasks.desktop
        rm -f /usr/share/pixmaps/Tasks.png
    ;;

    install|*)
        echo "install ..."
        # Install destop
        if [ -f /usr/share/applications/Tasks.desktop ]; then
            rm /usr/share/applications/Tasks.desktop
        fi
        ln -s `pwd`/share/applications/Tasks.desktop /usr/share/applications/Tasks.desktop

        # Install auto run on boot
        if [ ! -d ~/.config/autostart ]; then
            mkdir -p ~/.config/autostart
            chmod a+wr ~/.config/autostart
        fi
        if [ -f ~/.config/autostart/Tasks.desktop ]; then
            rm ~/.config/autostart/Tasks.desktop
        fi
        ln -s `pwd`/share/applications/Tasks.desktop ~/.config/autostart/Tasks.desktop

        # Reset exec to desktop
        sed -i "s/Exec=.*//g" `pwd`/share/applications/Tasks.desktop
        echo "Exec=`pwd`/Tasks-x86_64.AppImage" >> `pwd`/share/applications/Tasks.desktop

        # Install applications icon
        if [ -f /usr/share/pixmaps/Tasks.png ]; then
            rm /usr/share/pixmaps/Tasks.png
        fi
        if [ ! -d /usr/share/pixmaps ]; then
            mkdir -p /usr/share/pixmaps
        fi
        ln -s `pwd`/share/pixmaps/Tasks.png /usr/share/pixmaps/Tasks.png
        
        # Whether run after install
        if [ "$2" = "run" ]; then
            ./Tasks-x86_64.AppImage
        fi
        ;;
esac

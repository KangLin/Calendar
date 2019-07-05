#!/bin/bash

EXIT_CODE=0
PROJECT_NAME="Tasks"

if [ -n "$1" ]; then
    echo "$PROJECT_NAME"
	PROJECT_NAME=$1
fi

if [ ! ~/.config/autostart/${PROJECT_NAME}.desktop ]; then
    echo "There are not ~/.config/autostart/autostart/${PROJECT_NAME}.desktop"
    EXIT_CODE=$[EXIT_CODE+1]
fi

if [ ! -f /opt/${PROJECT_NAME}/share/applications/${PROJECT_NAME}.desktop ]; then
	echo "There are not /opt/share/applications/${PROJECT_NAME}.desktop"
	EXIT_CODE=$[EXIT_CODE+1]
fi

if [ ! -f /usr/share/applications/${PROJECT_NAME}.desktop ]; then
	echo "There are not /usr/share/applications/${PROJECT_NAME}.desktop"
	EXIT_CODE=$[EXIT_CODE+1]
fi

if [ ! -f /opt/${PROJECT_NAME}/share/pixmaps/Tasks.png ]; then
        echo "There are not /opt/share/pixmaps/Tasks.png"
	EXIT_CODE=$[EXIT_CODE+1]
fi

if [ ! -f /usr/share/pixmaps/Tasks.png ]; then
    echo "There are not /usr/share/pixmaps/Tasks.png"
    EXIT_CODE=$[EXIT_CODE+1]
fi

if [ ! -f /etc/ld.so.conf.d/Tasks.conf ]; then
	echo "There are not /etc/ld.so.conf.d/${PROJECT_NAME}.conf"
	EXIT_CODE=$[EXIT_CODE+1]
fi

exit $EXIT_CODE

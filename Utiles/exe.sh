#!/bin/bash

: '
If you run the script without any argument, you will be automatically connected to 4 account :
"1", "2", "3", "4"

How to use the script :

If you want to register the accounts "1", "2", "3", "4", run the program in this way :
    ./exe.sh REGISTER

If you want to directly launch a classic game run this command :
    ./exe.sh PLAY
'


if [ $(uname -r | grep -c fc) -ne 0 ] # Fedora
then
    xdotool key super+Up
else
    xdotool key ctrl+super+Up
fi
xdotool key ctrl+shift+o
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key super+g
xdotool key alt+g
xdotool type "cd /home/jepsiko/CLionProjects/Group4/cmake-build-debug/code/"
xdotool key "Return"
xdotool type "./client 127.0.0.1"
xdotool key "Return"

xdotool key ctrl+shift+t
xdotool type "./server"
xdotool key "Return"
xdotool key ctrl+Page_Down

if [ "$1" = "REGISTER" ]
then
	echo d1
    xdotool type "2"
    xdotool key "Return"
    xdotool key alt+o

    for i in `seq 1 4`;
    do
        for j in `seq 1 4`;
        do
            xdotool type ${i}
            xdotool key "Return"
        done
        xdotool key ctrl+shift+n
    done
else
	echo d2
    xdotool type "1"
    xdotool key "Return"
    xdotool key alt+o

    for i in `seq 1 4`;
    do
        for j in `seq 1 2`;
        do
            xdotool type ${i}
            xdotool key "Return"
        done
        xdotool key ctrl+shift+n
    done
fi

if [ "$1" = "PLAY" ]
then
    xdotool key alt+g
    xdotool type "1"
    xdotool key "Return"
    xdotool type "1"
    xdotool key "Return"
    xdotool key alt+o
fi
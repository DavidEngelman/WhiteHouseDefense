#!/bin/bash

xdotool key ctrl+super+Up #full sreen
xdotool key ctrl+shift+o
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key super+g
xdotool type "cd CLionProjects/Group4/cmake-build-debug/code/"
xdotool key "Return"
xdotool type "./client 127.0.0.1"
xdotool key "Return"
for i in `seq 1 10000`;
    do
    xdotool key ctrl+alt+t
    done
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
    xdotool key ctrl+o

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

xdotool key ctrl+g
xdotool type "1"
xdotool key "Return"
xdotool type "1"
xdotool key "Return"
xdotool key ctrl+o
#!/bin/bash

xdotool key ctrl+super+up #full sreen
xdotool key ctrl+shift+o
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key ctrl+shift+n
xdotool key ctrl+shift+e
xdotool key alt+a
xdotool type "cd CLionProjects/Group4/cmake-build-debug/code/"
xdotool key "Return"
xdotool type "./client 127.0.0.1"
xdotool key "Return"

for i in `seq 1 4`;
do

	xdotool type "1"
	xdotool key "Return"
	xdotool key ctrl+shift+n
done
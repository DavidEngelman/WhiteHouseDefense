#!/bin/bash

#xdotool key ctrl+alt+t
#WID=$(xdotool search --name "Terminator")
#xdotool windowfocus ${WID}
#xdotool key alt+F10
xdotool key ctrl+alt+agrave
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
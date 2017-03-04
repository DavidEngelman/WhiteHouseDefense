#!/bin/bash

: '
/!\ YOU MUST RUN THIS SCRIPT ON TERMINATOR /!\

If you run the script without any argument, you will be automatically connected to 4 account :
"1", "2", "3", "4"

Usage :
    ./exe.sh [SHOW] [REGISTER] [PLAY] [GAMEMODE]

How to use the script :

If you want to register the accounts "1", "2", "3", "4" :
    ./exe.sh REGISTER

If you want to launch a classic game :
    ./exe.sh PLAY

If you want to launch a timed game run this command :
    ./exe.sh PLAY TIMED

If you want to launch a team game run this command :
    ./exe.sh PLAY TEAM
'

function forAllClients {

    if [ show = "SHOW" ]
    then
        for i in `seq 1 4`;
        do
            xdotool type "$1"
            xdotool key "Return"
            xdotool key ctrl+Page_Down
        done
        xdotool key ctrl+Page_Down
    else
        xdotool key alt+g
        xdotool type "$1"
        xdotool key "Return"
        xdotool key alt+o
    fi
}

# Set the terminal on FullScreen
if [ $(uname -r | grep -c fc) -ne 0 ] # Fedora
then
    xdotool key super+Up
else
    xdotool key ctrl+super+Up
fi

show=""
if [ "$1" = "SHOW" ]
then
    show="SHOW"
    xdotool key ctrl+shift+t
    shift
else
    # Divide the terminal in 4
    xdotool key ctrl+shift+o
    sleep 1
    xdotool key ctrl+shift+n
    sleep 1
    xdotool key ctrl+shift+e
    sleep 1
    xdotool key ctrl+shift+n
    sleep 1
    xdotool key ctrl+shift+e
    sleep 1

    xdotool key super+g
fi

# Run all the clients
forAllClients "cd ~/CLionProjects/Group4/cmake-build-debug/code/"
forAllClients "./client 127.0.0.1"

# Create a new tab and run the server
xdotool key ctrl+shift+t
xdotool type "./server"
xdotool key "Return"
xdotool key ctrl+Page_Down


if [ "$1" = "REGISTER" ]
then
    forAllClients "2"

    # Register all the players
    for i in `seq 1 4`;
    do
        for j in `seq 1 2`;
        do
            forAllClients ${i}
        done
        xdotool key ctrl+shift+n
    done

    shift
else
    forAllClients "1"
fi

# Connect all the players
for i in `seq 1 4`;
do
    for j in `seq 1 2`;
    do
        forAllClients ${i}
    done
    xdotool key ctrl+shift+n
done

# Launch a game
if [ "$1" = "PLAY" ]
then
    forAllClients "1"

    shift

    if [ "$1" = "TEAM" ]
    then
        forAllClients "3"
    elif [ "$1" = "TIMED" ]
    then
        forAllClients "2"
    else
        forAllClients "1"
    fi
fi
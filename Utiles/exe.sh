#!/bin/bash

: '
/!\ YOU MUST RUN THIS SCRIPT ON TERMINATOR /!\

If you run the script without any argument, you will be automatically connected to 4 account :
"1", "2", "3", "4"

Usage :
    ./exe.sh [SHOW] [REGISTER] [PLAY] [GAMEMODE]

    /!\ The order is important so do not type in : ./exe.sh REGISTER SHOW /!\

How to use the script :

If you want to put all the clients in new tabs instead of dividing the screen by 4 :
    ./exe.sh SHOW

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
    if [ "${show}" = "SHOW" ]
    then
        for i in `seq 1 4`;
        do
            xdotool type --delay 100 "$1"
            xdotool key "Return"
            sleep 1
            xdotool key ctrl+Page_Down
        done
        xdotool key ctrl+Page_Down # Jump over the server tab
    else
        xdotool key alt+g
        xdotool type --delay 100 "$1"
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
sleep 1

show=""
if [ "$1" = "SHOW" ]
then
    # Open 3 tabs
    show="SHOW"
    xdotool key ctrl+shift+t
    sleep 1
    xdotool key ctrl+shift+t
    sleep 1
    xdotool key ctrl+shift+t
    sleep 1
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

# Create a new tab and run the server
xdotool key ctrl+shift+t
sleep 1
xdotool type --delay 100 "cd ~/CLionProjects/Group4/cmake-build-debug/code/"
xdotool key "Return"
xdotool type --delay 100 "./server"
xdotool key "Return"
sleep 1
xdotool key ctrl+Page_Down

# Run all the clients
forAllClients "cd ~/CLionProjects/Group4/cmake-build-debug/code/"
forAllClients "./client 127.0.0.1"


if [ "$1" = "REGISTER" ]
then
    echo REGISTER
    forAllClients "2"

    # Register all the players
    for i in `seq 1 4`;
    do
        for j in `seq 1 2`;
        do
            xdotool type ${i}
            xdotool key "Return"
        done

        if [ "${show}" = "SHOW" ]
        then
            xdotool key ctrl+Page_Down
        else
            xdotool key ctrl+shift+n
        fi
        sleep 1
    done
    if [ "${show}" = "SHOW" ]
    then
        xdotool key ctrl+Page_Down
    fi

    shift
else
    forAllClients "1"
fi

# Connect all the players
for i in `seq 1 4`;
do
    for j in `seq 1 2`;
    do
        xdotool type ${i}
        xdotool key "Return"
    done

    if [ "${show}" = "SHOW" ]
    then
        xdotool key ctrl+Page_Down
    else
        xdotool key ctrl+shift+n
    fi
    sleep 1
done
if [ "${show}" = "SHOW" ]
then
    xdotool key ctrl+Page_Down
fi

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
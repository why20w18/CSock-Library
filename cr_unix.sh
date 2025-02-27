#!/bin/bash

if [ $# -ne 1 ]; then
    echo "GECERSIZ ARGUMAN GIRDINIZ !"

elif [ "$1" == "release-compile" ] || [ "$1" == "c" ]; then
    clear
    echo "::::::::::Linux release compile started::::::::::"
    rm -rf build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    echo "::::::::::Linux release finished::::::::::"

elif [ "$1" == "debug-compile" ] || [ "$1" == "dc" ]; then 
    clear
    echo "::::::::::Linux debug compile started::::::::::"
    rm -rf build
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make
    echo "::::::::::Linux debug finished::::::::::"

elif [ "$1" == "run" ] || [ "$1" == "r" ]; then 
    ./build/CSOCK

fi
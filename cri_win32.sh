#!/bin/bash

if [ $# -ne 1 ]; then
    echo "GECERSIZ ARGUMAN GIRDINIZ !"
    echo "install : utils-win32 download"
    echo "compile or c : compiled for win32"
    echo "run or r : run for win32"
	
elif [ "$1" == "c" ] || [ "$1" == "compile" ]; then
    clear
    echo "::::::::::WIN32 release compile started::::::::::"
	rm -rf build-win32
	mkdir build-win32
    cp utils-WIN32/win32-dll/*.dll build-win32/
	cp utils-WIN32/win32-dll/toolchain-windows.cmake build-win32
	cd build-win32
	cmake -DCMAKE_TOOLCHAIN_FILE=toolchain-windows.cmake ..
	make
    echo "::::::::::WIN32 release compile finished::::::::::"

elif [ "$1" == "install" ]; then 
    wget https://github.com/why20w18/RCON-Protocol-Client/releases/download/utils-WIN32/utils-WIN32.zip
    unzip utils-WIN32.zip
    rm -rf utils-WIN32.zip

elif [ "$1" == "r" ] || [ "$1" == "run" ]; then
	wine ./build-win32/CSOCK.exe

fi

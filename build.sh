#!/bin/zsh

cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
cp ./build/client_1/client ./uTracker
cp ./build/server/server ./uTracker_server

#!/bin/sh

if [ -d "$HOME/work/MarlinTest/SimpleProcessor/build" ]; then
   rm -rf "$HOME/work/MarlinTest/SimpleProcessor/build"
fi

mkdir "$HOME/work/MarlinTest/SimpleProcessor/build"
cd "$HOME/work/MarlinTest/SimpleProcessor/build"
cmake -C $ILCSOFT/ILCSoft.cmake ..
make
make install


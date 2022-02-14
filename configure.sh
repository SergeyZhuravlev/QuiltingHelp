#!/bin/bash

mkdir .build
cd .build

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..

cd ..

read -p "Press enter to continue"
#!/bin/bash

g++ ./menu/CMenu.cpp ./menu/CMenuItem.cpp main.cpp -o program
echo "Скомпилировано: program"
echo "Today is $(date). Запускаю program..."
./program


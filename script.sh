#!/bin/bash

if g++ -I./models ./models/*.cpp ./menu/CMenu.cpp ./menu/CMenuItem.cpp main.cpp -o program; then

# echo "Скомпилировано: program"

# echo "Today is $(date). Запускаю program..."
    ./program

else
    echo "cringe"
fi
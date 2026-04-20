#!/bin/bash

if g++ -I./models -I./menu ./models/*.cpp ./menu/*.cpp main.cpp -o program; then

# echo "Скомпилировано: program"

# echo "Today is $(date). Запускаю program..."
    ./program

else
    echo "cringe"
fi
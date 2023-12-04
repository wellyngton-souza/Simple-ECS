#!/bin/bash

# Comando para compilar
g++ -Wall -Wextra -Werror ./src/main.cpp -o ./build/main.exe -lsfml-graphics -lsfml-window -lsfml-system

# Comando para executar
./build/main.exe

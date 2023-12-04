@echo off

g++ -Wall -Wextra -Werror .\src\main.cpp -o .\build\main.exe -lsfml-graphics -lsfml-window -lsfml-system

REM Comando para executar
.\build\main.exe

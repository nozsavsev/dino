#!/bin/bash
sudo apt install -y libsfml-dev
g++ main.cpp -o dino -lsfml-graphics -lsfml-window -lsfml-system
tar -xvf res.tar.gz
echo "to start game ./dino"

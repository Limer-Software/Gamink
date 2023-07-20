#!/bin/bash

# Remove the output directory if it exists.
if [ -d "bin" ]; then
  rm -r "bin";
fi

# Create the output directory and build the project.
mkdir "bin";
g++ src/main.cpp -o bin/main -Wall -g -Ofast `pkg-config --cflags --libs gtk4`;

# Heislab

## Authors
Paul Eirik Worre & Hans Tomren

## Introduction
This project contains source files for running a model elevator, such as taking orders and going to the correct destination.

## Installation
Requirements:
- Heis-setup (Elevator, engine-control-box, orderbox)
- PC

Instruction to compile the files to an executable program for running the elevator:
1. In terminal, navigatge to "./skeleton_project/"
2. Run following command: make
    - Now the program is compiled and there is an executable file.
    Before we can run the file, we need connection to the elevator.
3. Connect to elevator with following command: elevatorserver
3. Run the program with following command: ./elevator

Example of installation:
```
$ cd ./Heislabb/skeleton_project
$ make
$ elevatorserver
$ ./elevator
```

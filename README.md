# Sandbox file system emulator - C

### School project - Data structure - ENSMR (ex ENIM) - MSIP - 2020/2021

## Introduction

This project is a sandbox file system emulator. It is a school project for the data structure course. The goal is to
create a file system emulator with basic commands, such as:

- `ls`
- `cd`
- `mkdir`
- `touch`
- `rm`
- `rmdir`
- `cat`
- `pwd`
- `tree`

for more information/context, please refer to
the [project notes](https://github.com/Diettrich/sandbox-file-system/blob/master/note.md).

## TODO

### Features

#### Non-functional:

- [x] Modularity
- [ ] Command line arguments validation
    - [x] mkdir validation
    - [ ] ls validation
    - [ ] cd validation
    - [ ] pwd validation
    - [ ] touch validation
    - [ ] rm validation
    - [ ] rmdir validation
    - [ ] cat validation
    - [ ] tree validation
- [ ] Command line arguments options
    - [ ] mkdir options (e.g. -p)
    - [ ] ls options (e.g. -l)
    - [ ] cd options
    - [ ] pwd options
    - [ ] touch options
    - [ ] rm options
    - [ ] rmdir options
    - [ ] cat options
    - [ ] tree options
- [ ] Error handling
    - [ ] Basic error handling
        - [ ] mkdir error handling
        - [ ] ls error handling
        - [ ] cd error handling
        - [x] pwd error handling
        - [ ] touch error handling
        - [ ] rm error handling
        - [ ] rmdir error handling
        - [ ] cat error handling
        - [ ] tree error handling
    - [ ] Advanced error handling
- [ ] Documentation

#### Functional:

- [ ] Commands
    - [x] exit
    - [x] ls
    - [x] cd
    - [x] mkdir
    - [x] pwd
    - [ ] touch
    - [ ] rm
    - [ ] rmdir
    - [ ] cat
    - [ ] tree
- [ ] Shell true emulator
    - [ ] Command history
    - [ ] Command completion
    - [ ] Command line editing
- [ ] File system persistence (save/load)
- [ ] Very basic file editing

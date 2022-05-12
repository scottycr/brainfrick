# Brainfrick

## Info

Bestowed upon you is a fun unused project for CSCI 450: Compiler Structure, and repurposed for CSCI 375: Object Oriented Programming named Brainfrick.

Brainfrick is a compiler for Brainf\[REDACTED] with an institutionally friendly name that includes all the features of the original esoteric language. This project was brought to you by Bree Johnson and Theodore Corrello.

## Features

- Fully functioning Brainf interpreter
- Both console and file output
- Outputs what line and column number an error is on
- Variable memory table size

## What is Brainf

Brainf is an estoteric language designed in 1993. It has eight commands and is fully Turing complete. The goal of the language was never to be practically used, but as a interesting challenge for programmers.

Brainf uses a model of the program and instruction pointer, with a one-dimensional array of byte cells with various sizes, usually being 30,000 cells. These programs are made up of eight commands. To run a program, it needs two byte streams, input and ouput. 

The commands are executed sequentially and terminates at the last command, unless two specific commands are used. These two commands along with the other commands are listed below:

| Character | Use |
|:--|:--|
| `+` | Increment the byte at the data pointer |
| `-` | Decrement the byte at the data pointer |
| `>` | Move the data pointer to the right cell |
| `<` | Move the data pointer to the left cell |
| `.` | Output the byte at the data pointer |
| `,` | Accept a byte of input, storing the input into the byte at the data pointer |
| `[` | If the byte at the data pointer is 0, jump forward to the command after the matching `]`, instead of moving to the command |
| `]` | If the byte at the data pointer is not 0, jump backward to the command after the matching `[`, instead of moving to the next command |

## How to Use

To use brainfrick you need to build it first. Makes sure there is a bin folder in the main brainfrick directory and use the provided Makefile.

`make mains`

To run a program, run the executable and point it to a Brainf file. In this demonstration I use one of the example files provded.

`./bin/brainfrick ./examples/hello.bf`

To change the cell table size, use the -ts or --table-size flags.

`./bin/brainfrick ./examples/hello.bf -ts 30001`

To have Brainfrick move the output to a file, use the -o or --output-file flag.

`./bin/brainfrick ./examples/hello.bf -o hello.txt`

There are also tests included in this repository, which can be built with the provided Makefile.

`make tests`

All test binaries are prefixed with "test_", and can be run as a normal executable. However, test_interpreter uses the example Brainf files for testing, so it needs to be run from the main Brainfrick directory.

`./bin/test_interpreter`

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

Brainf is an esoteric language designed in 1993. It has eight commands and is fully Turing complete. The goal of the programming language was never to be practical. Instead, it aimed to be a challenge for programmers.

Brainf uses a machine model of the program and instruction pointer, with a one-dimensional array of byte cells of various sizes, usually 30,000 cells. These programs consist of eight commands, with all other characters ignored. To execute a Brainf program, it needs two-byte streams, input, and output. 

Brainf commands are executed sequentially and terminate at the end of the file. There are loops in Brainf which control the instruction pointer. Brainf's commands are listed below:

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

There also is a "comment loop" at the very beginning of the file used to describe the program. The interpreter ignores all characters in this loop, including the eight commands.

## Implementation

Brainfrick uses four key components to work. These are the tokenizer, parser, cell table, and interpreter. All of those components are in their respective .cpp and .h files. 

The tokenizer has one job, to change the characters from the file into tokens using its scan function. The Tokenizer class stores the code from an input file as a string, which the tokenizer then scans the symbols. Since Brainf only has eight commands, there are ten symbols that the tokenizer will return.

| Symbol | What it represents |
|:--|:--|
| `PLUS` | `+` |
| `MINUS` | `-` |
| `LESS` | `<` |
| `GREATER` | `>` |
| `DOT` | `.` |
| `COMMA` | `,` |
| `OPENBRACKET` | `[` |
| `CLOSEBRACKET` | `]` |
| `END` | End of file |
| `UNRECOGNIZED` | Should never be returned since Brainf ignores all other characters |

The parser uses the tokenizer to check if the code has valid syntax. Brainf only has one instance of invalid syntax, and that is if a loop does not have a matching bracket. The BNF for Brainf is in the `parse.cpp` file.

The parser has three functions. The function commandOperation checks if a character is a Brainf command. The function parse loops through the tokenizer sequentially and only calls the function command if it finds an `OPENBRACKET. If the function parse finds another`OPENBRACKET` while the function command is running, it will call itself recursively until it finds all matching `CLOSEBRACKET`s. If the function command does not match all brackets, it will return false.

If the parser does not find invalid syntax, it will append all the symbols into a vector passed into the parse function. The last step is the cell table and interpreter. The CellTable class is the machine model Brainf uses. 

CellTable has a vector of bytes with a default size of 30,000 (which can be changed by the user) and a character pointer which is the instruction pointer. It also has functions for all the Brainf commands. The interpreter uses the vector of symbols from the parser (the program), a CellTable, output stream, and input stream to run the program. 

The interpreter loops through the program provided with its eval function, which executes the code. The function eval calls the respective CellTable function for the corresponding Brainf command. When eval hits a loop, it calls itself recursively and passes in the current index of the program.

The main file ties all the parts together and controls the CellTable size and if the program outputs to the console or a file.

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

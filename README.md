# Introduction to Brainfuck

**Brainfuck** is a minimalist esoteric programming language created by Urban Müller in 1993. It is designed to be as minimal as possible, featuring only eight simple commands, yet it is Turing complete—meaning it can theoretically compute anything that is computable.

## Basic Concepts

- **Minimal Instruction Set:** Brainfuck has only 8 commands: `+ - > < . , [ ]`.
- **Memory Model:** The program uses an array of memory cells (the “tape”), each initially set to zero. A data pointer moves along this tape.
- **No Variables or Functions:** All logic is expressed through the manipulation of the tape and the data pointer.

## Commands Overview

| Command | Description                                              |
|---------|---------------------------------------------------------|
| `>`     | Move the pointer one cell to the right                  |
| `<`     | Move the pointer one cell to the left                   |
| `+`     | Increment the value at the current cell by one          |
| `-`     | Decrement the value at the current cell by one          |
| `.`     | Output the value at the current cell as a character     |
| `,`     | Input a character and store its value in the cell       |
| `[`     | Jump past the matching `]` if the current cell is zero  |
| `]`     | Jump back to the matching `[` if the current cell is nonzero |

## Implemention

I have provided implementations of the Brainfuck language in various programming languages. Each implementation is placed in a folder named after the language, and inside each folder, there are two versions: one that compiles Brainfuck code to the target language, and another that directly executes Brainfuck code and prints the result to the console.

Now, I have finished the implemention of C and C++.

To be continued...

## Examples

Each directory contains several examples of Brainfuck programs, which are named with the extension of ".bf".

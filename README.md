# ENC - Simple Encoder/Decoder Utility
**ENC** is a lightweight command-line utility for performing basic encoding and decoding operations. It currently supports `Base64` and `ROT13 (Caesar cipher variant)` transformations. You can provide input directly as a string or from a file, and output the result to the console.

# Features
**Flexible Input**: Read input data directly from the command line or from a specified file.

~~Not so~~ **Multiple Algorithms**:
*	Base64: Standard Base64 encoding/decoding.
*	ROT13: A simple Caesar cipher (symmetric, so the same operation encodes and decodes).
**Encode/Decode** Modes: Clearly specify whether you want to encode or decode.
Console or File Output: Display results directly in your terminal or save them to a file.
How to Build
To build enc, you'll need a C++ compiler (like `g++.exe`), go to the root directory and run:
``` bat
g++ source/entrypoint.cpp -o enc.exe -Wall -Wextra -std=c++20
```
> Adjust `g++` and `c++ flags` accordingly to your system

Or just using the `compile.bat` file in the root for `Windows`

# Usage
```
enc.exe [source] <flags> [destination]

Input Source:
  "<text>"     : Input text directly from command line (enclose in quotes)
  <filepath>   : Path to a file to read input from

Flags:
  -help        : Display help message
  -file_in     : Use file as input in <source>
  -base64      : Base64
  -rot13       : ROT13 (Caesar cipher variant)
  -encode      : Encode mode (default)
  -decode      : Decode mode

Output Destination (Optional):
  <filepath>    : Path to a file to write output to. If omitted, output goes to console.
```
Examples, run:
``` bat
enc.exe "this is a message" -encode -base64
```
will give
```
aGlzIGlzIGEgbWVzc2Fn
```
# Notes on Development
* Argument Parsing: The application uses a custom hashing function for command-line argument parsing.
* Symmetric Operations: ROT13 is a symmetric cipher, meaning the same Convert function is used for both encoding and decoding.
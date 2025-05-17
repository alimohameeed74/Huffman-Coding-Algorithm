# Huffman Coding Algorithm in C++

This project is an implementation of the Huffman Coding Algorithm in C++. Huffman Coding is a lossless data compression technique used to reduce the size of data by encoding more frequent characters with shorter codes. The program reads text from a file, compresses it using Huffman Coding, saves the encoded version to another file, and then decodes it back to its original form. This demonstrates the efficiency and correctness of the algorithm in handling compression and decompression.

---

## Table of Contents

1. [Project Overview](#project-overview)  
2. [How Huffman Coding Works](#how-huffman-coding-works)  
3. [Features](#features)  
4. [Project Structure](#project-structure)  
5. [Example](#example)  

---

## Project Overview

This is a C++ implementation of the Huffman Coding Algorithm, a well-known and widely used method for lossless data compression. The algorithm is based on the frequency of characters in the input text. By assigning shorter binary codes to more frequent characters and longer codes to less frequent ones, it effectively reduces the overall size of the data.

The project demonstrates:
- Frequency analysis of characters in a text
- Construction of a Huffman tree
- Generation of binary codes for each character
- Compression of input text
- Decompression of encoded data

---

## How Huffman Coding Works

1. Count the frequency of each character in the input.
2. Insert each character into a priority queue (min-heap) based on frequency.
3. Build a binary tree (Huffman Tree) where:
   - Each leaf node is a character.
   - The path from root to leaf represents the character’s binary code.
4. Encode the text using the generated codes.
5. To decode, traverse the tree using the binary codes to recover the original characters.

---

## Features

- Reads input text from `Original_Text.txt`
- Calculates frequencies of all characters
- Builds the Huffman Tree using a priority queue
- Generates and displays Huffman codes
- Compresses the text into a binary string
- Saves the encoded string into `Binary_Encoded_File.txt`
- Decodes the binary string back to the original text
- Calculates and displays the size before and after compression

---

## Project Structure

```plaintext
.
├── Huffman_Coding.cpp        # Main source code file
├── Original_Text.txt         # Input file containing the original text
├── Binary_Encoded_File.txt   # Output file with the encoded binary text
├── README.md                 # Project documentation

## Example

### Input Text:
```

ABBC

```

### Frequency of Characters:
```

A:1, B:2, C:1

```

### Generated Huffman Codes:
```

B: 0
A: 10
C: 11

```

### Encoded Output (Binary):
```

100011

```

### Decoded Output:
```

ABBC


```

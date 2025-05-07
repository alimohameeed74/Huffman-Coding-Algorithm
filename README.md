# Huffman-Coding-Algorithm


This is a C++ implementation of the **Huffman Coding Algorithm**, a well-known algorithm used for **lossless data compression**. The project demonstrates how to compress and decompress text efficiently using a binary tree structure. The goal of this project is to understand how Huffman Coding works and to implement it in C++.

## 📋 Table of Contents

1. [Project Overview](#-project-overview)
2. [Technologies Used](#-technologies-used)
3. [How Huffman Coding Works](#-how-huffman-coding-works)
4. [Features](#-features)
5. [Example](#-example)
6. [How to Compile and Run](#-how-to-compile-and-run)
7. [Compression Statistics](#-compression-statistics)
8. [Future Improvements](#-future-improvements)
9. [License](#-license)
10. [Contact](#-contact)


##  Project Overview

The **Huffman Coding Algorithm** minimizes the size of data by assigning shorter binary codes to more frequent characters and longer codes to less frequent ones. It uses a **binary tree** (Huffman Tree) to generate these codes. This project provides a detailed implementation of the algorithm from scratch, focusing on building the tree, generating the codes, and encoding/decoding the data.

---

##  Technologies Used

- **C++17** – For implementing the algorithm and handling the core logic.
- **Binary Tree** – The structure used to build the Huffman Tree.
- **STL (Standard Template Library)** – Utilizing `priority_queue` for efficient tree construction, `map` for character frequencies, and `vector` for managing the nodes.
- **File I/O** – For reading input data and writing compressed data (optional feature).

---

##  How Huffman Coding Works

1. **Frequency Calculation:**  
   - First, the algorithm counts the frequency of each character in the input text.

2. **Huffman Tree Construction:**  
   - Using a **priority queue**, the algorithm builds a binary tree where each node represents a character and its frequency. The two least frequent characters are combined to form a new node, and this process continues until a single tree is formed.

3. **Binary Code Generation:**  
   - The tree is then traversed, assigning binary codes to each character. Left edges represent `0`, and right edges represent `1`. The binary code for each character is determined by the path from the root of the tree to the character node.

4. **Encoding:**  
   - The input text is encoded using the generated binary codes for each character.

5. **Decoding:**  
   - The encoded binary data can be decoded back to its original text by traversing the Huffman Tree using the binary codes.

---

##  Features

- **Huffman Tree Construction:**  
  Builds a binary tree from the frequencies of the input characters using a **min-heap** (priority queue).
  
- **Text Compression:**  
  Compresses input text into a binary format using the generated Huffman codes.

- **Text Decompression:**  
  Decodes the compressed binary data back into the original text using the Huffman Tree.

- **File I/O Support:**  
  Optionally supports reading from and writing to text files for both compression and decompression.

---

##  Example

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


---








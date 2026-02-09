# 🧮 Matrix Manipulation Engine (CLI)

A robust, modular Command Line Interface (CLI) tool written in C for performing advanced linear algebra operations and computer vision kernel processing.

[Project Demo]<img width="1920" height="1080" alt="demo_screenshot" src="https://github.com/user-attachments/assets/35079bae-0086-492b-98dc-27fcc743f5df" />



## 🚀 Overview
This project is a high-performance matrix engine designed to handle 2D array manipulations safely and efficiently. Unlike standard calculator tools, this toolkit implements complex algorithms like **Spiral Traversal**, **Saddle Point Optimization**, and **2D Convolution** (Edge Detection) from scratch, with a focus on memory safety and input sanitization.

It features a modular architecture, separating the interface (`main.c`), logic (`matrix_toolkit.c`), and declarations (`matrix_toolkit.h`) to mimic professional embedded software standards.

## ✨ Features

### 🔧 Core Operations
* **Dynamic Memory Allocation**: No fixed size limits. Create matrices of any size supported by your system's RAM.
* **Scalar Multiplication**: Scale vectors and matrices efficiently.
* **Matrix Arithmetic**: Addition and Multiplication ($O(n^3)$) with internal memory management.
* **Transposition & Rotation**: 90° clockwise rotation (returns new dynamically allocated matrix).
* **Trace Calculation**: Diagonal summation for square matrices.

### 🧠 Advanced Algorithms
* **2D Convolution (Computer Vision)**: Implements a **Laplacian Kernel** with a sliding window to detect edges in a matrix, simulating robotic vision sensors.
* **Spiral Order Traversal**: A boundary-shrinking algorithm to parse 2D data into a 1D stream.
* **Saddle Point Detection**: Identifies critical points that are minimums in their row but maximums in their column (Minimax logic).

### 🛡️ Safety & Robustness
* **Memory Safety**: Full `malloc` and `free` implementation to prevent memory leaks.
* **Input Sanitization**: Custom `get_safe_int()` function prevents infinite loops and buffer overflows from invalid user input.
* **Boundary Protection**: Convolution logic automatically handles matrix borders to prevent segmentation faults.

## 🛠️ Installation & Usage

### Prerequisites
* GCC Compiler (MinGW for Windows, or standard GCC for Linux/macOS)

### Compilation
This project uses a multi-file compilation structure. Run the following command in your terminal:

```bash
gcc main.c matrix_toolkit.c -o matrix_toolkit

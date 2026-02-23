# 📚 Algorithms & Data Structures in C

A modular C project that implements fundamental **Abstract Data Types (ADTs)**, **Data Structures**, and **Algorithms**, along with dedicated runspaces for testing and a unified `main.c` project that integrates all components.

This repository is designed for learning, practicing, and experimenting with core computer science concepts in a structured and scalable way.

---

# 🗂 Project Structure

```
ADS Basics/
│
├── adt_&_ds/          # Abstract Data Types & Data Structures
│
├── algorithms/        # Algorithm implementations
│
├── runspaces/         # Independent test environments for each module
│
├── main.c             # Final integrated project entry point
│
├── CMakeLists.txt     # CMake build configuration
│
├── build/             # Generated build files
└── cmake-build-debug/ # IDE-generated debug build directory
```

---

# 📦 Folder Overview

## 1️⃣ `adt_&_ds/`

Contains implementations of core **Abstract Data Types and Data Structures**.

### Included Modules:

* `clist/` – Circular Linked List
* `dlist/` – Doubly Linked List
* `slist/` – Singly Linked List
* `stack/` – Stack implementation
* `queue/` – Queue implementation
* `heap/` – Heap data structure
* `pq/` – Priority Queue
* `hash/` – Hash table
* `tree/` – Tree structures
* `graph/` – Graph structure
* `adt.h` – Common interface / shared definitions

Each module is implemented in a modular way so it can be used independently or integrated into larger systems.

---

## 2️⃣ `algorithms/`

Contains algorithm implementations organized by topic.

### Subfolders:

* `sorting/` – Sorting algorithms (e.g., QuickSort, MergeSort, etc.)
* `graph/` – Graph algorithms (e.g., BFS, DFS, shortest paths)
* `dp/` – Dynamic Programming algorithms
* `recursion/` – Recursive problem implementations

These algorithms often utilize data structures defined in `adt_&_ds`.

---

## 3️⃣ `runspaces/`

This folder contains **dedicated testing environments** for each module.

Examples:

* `run_clist/`
* `run_stack/`
* `run_graph/`
* `run_sorting/`
* `run_dp/`
* etc.

Each runspace allows isolated testing of a specific data structure or algorithm without affecting the main project.

This makes debugging and experimentation much easier.

---

## 4️⃣ `main.c`

This is the **final integrated application entry point**.

It allows building a complete project that uses multiple data structures and algorithms together.

Think of it as:

> The “final project” that ties everything together.

---

# ⚙️ Build Instructions

This project uses **CMake** for building.

## 🔹 Option 1: Using an IDE (Recommended)

If you're using:

* CLion
* VSCode with CMake
* Any CMake-compatible IDE

Simply:

1. Open the root project folder.
2. Let the IDE detect `CMakeLists.txt`.
3. Build and Run.

The `cmake-build-debug/` folder will be generated automatically.

---

## 🔹 Option 2: Using Terminal (Manual Build)

From the root project directory:

```bash
mkdir build
cd build
cmake ..
make
```

To run:

```bash
./<executable_name>
```

(Executable name depends on how it's defined in `CMakeLists.txt`.)

---

# ▶️ How to Use

You have three main ways to use this project:

### 1️⃣ Test Individual Modules

Go to the appropriate `runspaces/run_*` folder and build/run that module independently.

### 2️⃣ Experiment with Algorithms

Modify and test specific algorithms in the `algorithms/` directory.

### 3️⃣ Build the Full Project

Use `main.c` to create a larger program that integrates multiple data structures and algorithms.

---

# 🧠 Learning Goals

This project demonstrates:

* Modular C programming
* Clean separation of ADTs and algorithms
* Memory management
* Reusable data structure design
* Testing via isolated runspaces
* CMake project organization

---

# 📌 Requirements

* C Compiler (GCC / Clang / MSVC)
* CMake 3.x+
* IDE (optional but recommended)

---

# 🚀 Future Improvements

* Add unit tests
* Add benchmarking tools
* Add documentation for each data structure API
* Add complexity analysis comments

# 📜 License

This project is for educational purposes.

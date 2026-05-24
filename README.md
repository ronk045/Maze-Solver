# Maze-Solver

A C implementation of a maze solver using **recursive Depth-First Search (DFS)**, developed for ECE 220. This project reads maze files, dynamically constructs maze structures, searches for a path from start to finish, and visualizes both the final solution and explored paths.

## Overview

The program solves text-based mazes by finding a path from:

- `S` → starting location
- `E` → ending location

Maze symbols:

- `%` → wall
- ` ` (space) → empty path
- `S` → start
- `E` → end
- `*` → cells on the final solution path
- `~` → visited cells that do not belong to the final solution

The maze is solved recursively using **Depth-First Search with backtracking**.

Example input:

```text
%%%%%%%%%%%
S %       %
% % %%%%% %
% % %   % %
% % % % %%%
% %   %   %
% %%%%%%% %
% % %     %
% % % % %%%
%     %   E
%%%%%%%%%%%
```

Example solved output:

```text
%%%%%%%%%%%
S*%       %
%*% %%%%% %
%*% %   % %
%*% % % %%%
%*%   %   %
%*%%%%%%% %
%*%~%***  %
%*%~%*%*%%%
%*****%***E
%%%%%%%%%%%
```

---

## Features

- Reads maze configurations from text files
- Dynamically allocates maze structures
- Solves mazes recursively using DFS
- Implements backtracking for dead-end recovery
- Tracks visited paths and final solution path
- Prints solved maze output
- Frees all dynamically allocated memory

---

## Implemented Functions

### `createMaze()`

Creates and initializes the maze structure.

Responsibilities:

- Reads maze dimensions
- Dynamically allocates memory
- Stores maze layout
- Identifies start and end positions

---

### `destroyMaze()`

Deallocates all memory associated with the maze.

Responsibilities:

- Frees row memory
- Frees cell arrays
- Frees maze structure

---

### `printMaze()`

Displays the maze in readable form.

Responsibilities:

- Prints each row
- Preserves maze formatting
- Outputs current board state

---

### `solveMazeDFS()`

Recursively searches for a path through the maze.

Responsibilities:

- Uses Depth-First Search
- Marks solution cells
- Tracks visited dead ends
- Uses backtracking to undo incorrect paths
- Returns success or failure

---

## DFS Algorithm

The recursive solver follows:

1. Check invalid positions
2. Check for goal state
3. Mark current position
4. Explore neighboring cells:
   - Left
   - Up
   - Right
   - Down
5. Backtrack if no path succeeds

Pseudo-process:

```text
Mark current position

Try left
Try right
Try up
Try down

If none work:
    mark as visited
    return false
```

---

## Concepts Used

- C programming
- Recursion
- Depth-First Search (DFS)
- Backtracking
- Dynamic memory allocation
- 2-D arrays
- File I/O
- Pointer manipulation
- Graph traversal concepts

---

## Project Structure

```text
maze.c         -> implemented functions
maze.h         -> structures and definitions
main.c         -> program driver
Makefile       -> build configuration
tests/         -> maze examples and outputs
```

---

## Build Instructions

Clean project:

```bash
make clean
```

Compile:

```bash
make
```

---

## Running the Program

Run with a maze file:

```bash
./mp9 maze1.txt
```

Example:

```bash
./mp9 tests/input/maze1.txt
```

---

## Memory Testing

Check for memory leaks:

```bash
valgrind ./mp9 tests/input/maze1.txt
```

---

## Skills Demonstrated

- Recursive algorithm design
- Depth-First Search implementation
- Backtracking techniques
- Dynamic memory management
- File parsing and processing
- Pointer usage in C
- Problem decomposition
- Debugging and memory analysis

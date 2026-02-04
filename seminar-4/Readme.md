# Seminar 4 – 2D Kadane (Maximum Sum Submatrix)

This project solves the problem of finding a submatrix with the maximum sum of elements in an integer matrix
using the two-dimensional Kadane algorithm (reduction to a one-dimensional problem).

## Task

For an integer matrix \(M \times N\), find the submatrix with the maximum sum of elements.

Required functions:

- `std::vector<std::vector<int>> readMatrix()` — reads a matrix of arbitrary size from standard input
- `int maxSubarraySum(const std::vector<int>& row)` — one-dimensional Kadane algorithm
- `std::tuple<int, int, int, int, int> maxSumSubmatrix(const std::vector<std::vector<int>>& m)` —
  returns coordinates of the submatrix and its sum `(r1, c1, r2, c2, sum)`
- `void printSubmatrix(const std::vector<std::vector<int>>& m, int r1, int c1, int r2, int c2)` —
  prints the found submatrix

The implementation correctly handles matrices containing negative numbers.

## Project Structure

```
seminar-4/
├── CMakeLists.txt
├── Readme.md
├── inc/
│   └── name_utils.h        # declarations of the required functions
├── src/
│   ├── main.cpp            # console interface
│   └── name_utils.cpp      # implementation of algorithms
└── tests/
    └── test_name_utils.cpp # (not used in this seminar)
```

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/max_sum_submatrix
```

Input format:

1. Two integers `rows` and `cols`
2. `rows * cols` integers — the elements of the matrix by rows

Example:

```text
3 4
1 2 -1 -4
-8 3 4 2
3 8 10 -8
```

The program prints the maximum sum, the coordinates of the submatrix and the submatrix itself.

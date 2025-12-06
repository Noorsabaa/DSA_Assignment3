# DSA Assignment 3 - Non-Comparison Sorting Algorithms

**Course:** CS250 - Data Structures and Algorithms  
**Program:** BSDS-2  
**Semester:** Fall 2025  
**Topic:** Non-Comparison Sorting Algorithms

## Overview

This project implements and analyzes four non-comparison sorting algorithms in C++. These algorithms sort data without directly comparing elements, instead using properties like digit positions, value ranges, and frequency counts.

## Implemented Algorithms

1. **Counting Sort** - Sorts by counting occurrences of each value
2. **Radix Sort (LSD)** - Sorts integers digit-by-digit from least to most significant
3. **Bucket Sort** - Distributes elements into buckets and sorts individually
4. **Pigeonhole Sort** - Uses pigeonhole principle to place elements in their positions

## Project Structure

```
DSA_Assignment3/
├── counting_sort.cpp           # Counting Sort implementation
├── radix_sort.cpp              # Radix Sort implementation
├── bucket_sort.cpp             # Bucket Sort implementation
├── pigeonhole_sort.cpp         # Pigeonhole Sort implementation
├── output_counting_sort.txt    # Test results for Counting Sort
├── output_radix_sort.txt       # Test results for Radix Sort
├── output_bucket_sort.txt      # Test results for Bucket Sort
├── output_pigeonhole_sort.txt  # Test results for Pigeonhole Sort
└── README.md                   # This file
```

## Requirements

- **Compiler:** g++ (GCC) 14.2.0 or later
- **Standard:** C++11 or higher
- **Operating System:** Windows/Linux/macOS

## Compilation Instructions

### For Windows (MinGW/g++)

```bash
# Counting Sort
g++ counting_sort.cpp -o counting_sort
counting_sort.exe

# Radix Sort
g++ radix_sort.cpp -o radix_sort
radix_sort.exe

# Bucket Sort
g++ bucket_sort.cpp -o bucket_sort
bucket_sort.exe

# Pigeonhole Sort
g++ pigeonhole_sort.cpp -o pigeonhole_sort
pigeonhole_sort.exe
```

### For Linux/macOS

```bash
# Counting Sort
g++ counting_sort.cpp -o counting_sort
./counting_sort

# Radix Sort
g++ radix_sort.cpp -o radix_sort
./radix_sort

# Bucket Sort
g++ bucket_sort.cpp -o bucket_sort
./bucket_sort

# Pigeonhole Sort
g++ pigeonhole_sort.cpp -o pigeonhole_sort
./pigeonhole_sort
```

### Save Output to File

```bash
# Windows
counting_sort.exe > output_counting_sort.txt

# Linux/macOS
./counting_sort > output_counting_sort.txt
```

## Algorithm Summaries

### 1. Counting Sort
- **Time Complexity:** O(n + k) where k is the range
- **Space Complexity:** O(n + k)
- **Stable:** Yes
- **Best For:** Small range of integer values
- **Limitation:** Inefficient when range >> array size

### 2. Radix Sort (LSD)
- **Time Complexity:** O(d × (n + k)) where d is number of digits
- **Space Complexity:** O(n + k)
- **Stable:** Yes
- **Best For:** Fixed-length integers with limited digits
- **Limitation:** Requires multiple passes based on digit count

### 3. Bucket Sort
- **Time Complexity:** Best/Average O(n + k), Worst O(n²)
- **Space Complexity:** O(n + k)
- **Stable:** Depends on internal sorting algorithm
- **Best For:** Uniformly distributed data
- **Limitation:** Poor performance with skewed data

### 4. Pigeonhole Sort
- **Time Complexity:** O(n + range)
- **Space Complexity:** O(range)
- **Stable:** No
- **Best For:** Small range with many duplicates
- **Limitation:** Memory wastage for large ranges

## Test Cases

Each implementation includes comprehensive test cases:

1. Small arrays for visual verification
2. Arrays with duplicates
3. Already sorted arrays
4. Reverse sorted arrays
5. Single element arrays
6. Arrays with all same elements
7. Performance tests with varying sizes (1K, 5K, 10K elements)
8. Edge cases (negative numbers, zeros, etc.)

## Performance Observations

### Counting Sort
- Excellent for small ranges (0-1000)
- Time increases linearly with range size
- Memory efficient for dense data

### Radix Sort
- Performance scales with number of digits
- Consistent O(n) behavior for fixed-digit numbers
- More stable than Bucket Sort

### Bucket Sort
- Best performance with uniform distribution
- Degrades significantly with clustered data
- Depends heavily on bucket count choice

### Pigeonhole Sort
- Fastest for very small ranges
- Nearly identical to Counting Sort in behavior
- Memory becomes limiting factor quickly

## Key Findings

1. **Counting Sort** and **Pigeonhole Sort** are nearly identical in implementation and performance
2. **Radix Sort** provides the most predictable performance across different data types
3. **Bucket Sort** requires careful tuning for optimal results
4. All algorithms significantly outperform comparison-based sorts (O(n log n)) for appropriate input types
5. Memory usage is the primary limitation for large value ranges

## Algorithms Comparison Table

| Algorithm | Best Case | Average Case | Worst Case | Space | Stable |
|-----------|-----------|--------------|------------|-------|--------|
| Counting Sort | O(n+k) | O(n+k) | O(n+k) | O(n+k) | Yes |
| Radix Sort | O(d(n+k)) | O(d(n+k)) | O(d(n+k)) | O(n+k) | Yes |
| Bucket Sort | O(n+k) | O(n+k) | O(n²) | O(n+k) | Depends |
| Pigeonhole Sort | O(n+range) | O(n+range) | O(n+range) | O(range) | No |


## Conclusions

Non-comparison sorting algorithms provide significant performance advantages over traditional comparison-based algorithms when working with specific data types and ranges. The choice of algorithm should be based on:

- **Data range:** Use Counting/Pigeonhole for small ranges
- **Data type:** Use Radix for fixed-digit integers
- **Distribution:** Use Bucket for uniform distributions
- **Stability requirements:** Use Counting or Radix for stable sorting

## References

- Introduction to Algorithms (CLRS) - Cormen, Leiserson, Rivest, Stein
- CS250 Course Materials - Data Structures and Algorithms
- GeeksforGeeks - Sorting Algorithms

## Author

**Noor ul Saba**  
BSDS-2, Fall 2025


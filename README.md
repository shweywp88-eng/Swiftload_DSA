# Swiftload_DSA
Data Structure and Algorithms

Overview

This repository contains the Data Structures & Algorithms assignment implementation for the SwiftLoad Logistics scenario. The system manages goods loaded onto delivery trucks, sorts cargo efficiently, and implements a warehouse inventory using advanced data structures.

Key Features Implemented:
FIFO Queue for truck loading.
Sorting comparison: Bubble Sort vs QuickSort vs STL sort with timing.
Stack for function calls and process control.
AVL Tree for warehouse inventory management with insert, delete, traversal.
Routing stub for shortest path analysis (Dijkstra / A* placeholder).
Error handling and input validation.
Learning Outcomes Mapping
LO	Implementation Highlights
LO1	Examined abstract data types (Goods, Stack, Queue, AVL Tree) and algorithms (sorting, insertion, deletion).
LO2	Specified ADTs formally and provided code documentation.
LO3	Implemented complex data structures (AVL Tree) with insert, delete, traversal, and error handling.
LO4	Assessed effectiveness of algorithms via timing metrics and Big O analysis.
Algorithms and Big O Analysis
FIFO Queue
Used to simulate truck loading.
Complexity: O(n) for processing all items.
Sorting Comparison
Bubble Sort: O(n²) worst-case.
QuickSort: O(n log n) average-case.
STL sort: Optimized C++ standard library sort, O(n log n).
AVL Tree
Insert/Delete/Search: O(log n)
Maintains balanced tree for fast retrieval.
Pre-order traversal and node deletion included.
Stack Operations
Simulates function calls using LIFO.
Complexity: O(1) for push/pop.

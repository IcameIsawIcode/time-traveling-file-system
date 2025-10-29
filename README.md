

A simple version-control system implemented in C++ using efficient data structures such as trees, hash maps, and heaps.
This project was built to explore efficient data versioning using trees, hash maps, and heaps, and to understand how complex state changes can be represented and stored efficiently.

---


- **Version Control Simulation:** 
  Each file version is stored as a node, linked to its parent version, forming a temporal dependency tree.

- **Efficient Data Structures:**  
  - **Tree:** Maintains file versions and their relationships.  
  - **HashMap:** Provides constant-time file access using unique identifiers.  
  - **Heap:** Tracks recent file edits for quick retrieval.


- **Time Travel:**  
  Restore any file to an older version using a single command.







## Technologies
- C++
- STL (maps, priority queues)
- File handling


## How to run
1. Compile using `g++ main.cpp -o build`
2. Run with `./build`

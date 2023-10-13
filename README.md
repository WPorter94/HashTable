# HashTable

Introduction

This repository contains C++ implementations written by Will Porter for a generic hash table using chaining, named WillHashTable. The project consists of several files: hash.h, hash_table_chain.h, Person.h, Test_Person.cpp, const_iterator.h, iterator.h, and a CMakeLists.txt file for building the project using CMake. These files collectively provide a hash table implementation with chaining, allowing for the storage and retrieval of key-value pairs.


Files Description

hash.h:
Defines a generic hash function template and provides specializations for std::string and int.
Hash functions are used to convert keys into hash values that determine the index in the hash table.

hash_table_chain.h:
Implements a hash map class using chaining, where collisions are resolved by storing multiple key-value pairs in the same bucket.
Includes functionalities for inserting, searching, updating, and deleting key-value pairs.
Utilizes the hash function from hash.h to calculate hash values.

Person.h:
Defines a Person class representing a human being with attributes such as given name, family name, ID number, and birth year.
Overloads operators for comparison and output.
Specializes the hash template for the Person class to create a custom hash function based on family name and given name.

Test_Person.cpp:
Contains a test program for the Person class and the hash map.
Reads data from a CSV file, creates Person objects, stores them in the hash map, and performs operations like searching and comparing.

const_iterator.h and iterator.h:
Define constant and mutable iterators, respectively, for traversing the hash map.
Provide functionality for iterating through the key-value pairs stored in the hash map.

CMakeLists.txt:
CMake configuration file specifying the project name, source files, and compilation requirements.


How to Build and Run

Build the Project:

Ensure CMake (version 3.19 or higher) is installed on your system.
Navigate to the project directory using the terminal.
Run the following commands:
mkdir build
cd build
cmake ..
make
Run the Test Program:

After building the project, the executable file should be generated in the build directory.
Run the executable to execute the test program:
./Test_Person

Sample Usage
The Test_Person program reads data from a CSV file, creates Person objects, stores them in the hash map, and performs various operations. The output displays the results of these operations, including comparisons and hash map entries.

Additional Notes
The code is tested for correctness and handles collisions using chaining.
Custom hash functions for the Person class ensure efficient storage and retrieval.
Feel free to explore and modify the code for your specific use case or extend the functionality further.

# POSD with C++ (and more)

#### FALL, 2023

#### Prof Y C Cheng

#### Dept of Computer Science and Information Engineering

#### Taipei Tech

### Important Links

* [Course Link](http://140.124.181.100/yccheng/posd2023f): http://140.124.181.100/yccheng/posd2023f

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 3

### Due: Nov 15 Wed 23:59

### Notice

* **DO NOT add any `.c` or `.cpp` file in your program that is not provided or required by the assignment**
* Please use the given makefile. You can modify the makefile if needed, but do not remove "all", "dirs", and "clean". Also, "all" must depends on "dirs". If you have any further questions about makefile, please search and learn it manually.
* Do not change the code structure, function prototype, or interface of the provided code, otherwise your code might not be compilable with TA's test.
* Do not commit the object files and executable files to git, otherwise your code might not be executable on the Jenkins server.
* Your program should not cause memory leak.
* The unit test you wrote will be also graded, please write the unit test comprehensively for the code you wrote.
* The design of your program will be also be graded, please follow the required patterns precisely while writing your program.
* If your code is not compilable on the Jenkins server, you'll get no point for the assignment.

### Description

In this assignment, you will keep working on the file system. You will know how to apply **Builder** and the combination of **Visitor**, **Iterator**, and **Factory Method** patterns to extend the operation for a **Composite** structure.

### Problem

In this assignment, you will extend the file system program from assignment 2, please do this assignment based on the [given code](./given_code), which is the suggested answer of assignment 2.

#### Revise `createIterator()`

In the previous assignments, you have written `Node::createIterator()` and implements `Folder::createIterator()` for creating an `FolderIterator`. In this assignment, you will need to revise `Node::createIterator()` to `Node::createIterator(OrderBy)`, which accepts an enum `OrderBy` that is located in `src/order_by.h`. The template method `Node::createIterator(OrderBy)` creates different iterators according to the receiving value. If a `OrderBy::Normal` is received, `createIterator(OrderBy)` creates a `FolderIterator`. For other `OrderBy` values, please implement three additional iterators `OrderByNameIterator`, `OrderByNameWithFolderFirstIterator`, and `OrderByKindIterator` for the enums `OrderBy::Name`, `OrderBy::NameWithFolderFirst`, and `OrderBy::Kind`, respectively. The three iterators should also become invalid if the structure of the target folder is changed. Please implement the three iterators as inner classes of `Folder`, the same way as `FolderIterator`. In addition, please make the method `createIterator` be compatible to the old programs, i.e., statement as `folder->createIterator();` should still work as usual.

##### Rules for iterating

- *Order by name*: The nodes under a folder are traversed alphabetically by their name.
- *Order by name with folder first*: The folders gets higher priority during the traversal and will be traversed first. Folders and files are traversed alphabetically by their names, respectively.
- *Order by kind*: The output nodes (files and folders) are sorted according to the kind of the node and the nodes with same kind are sorted alphabetically. The kind of node is defined as follows:

  - Folder: `"folder"`
  - File: The filename extension
  - File without filename extension: `"file"`

#### Tree Visitor

Please implement `TreeVisitor` in `src/tree_visitor.h`, which derives from `Visitor`, to simulate the cli tool [`tree`](https://www.javatpoint.com/linux-tree-command) in Unix system. A `TreeVisitor` accepts a enum `OrderBy` as the argument of the constructor to decide the output result.

##### Rules for order

*Order by name*: The output nodes (files and folders) are ordered alphabetically by their names.

```shell
.
├── Documents
│   ├── clean-architecture.pdf
│   ├── domain-driven-design.pub
│   ├── hello.txt
│   ├── note.txt
│   ├── object-oriented-analysis-and-design.pdf
│   └── programming
│       ├── cpp.pub
│       ├── oop.pdf
│       └── python.pub
├── Downloads
│   └── funny.png
├── hello.txt
└── my_profile
```

*Order by name with folder first*: The folders gets higher priority during the output and will be shown first. Folders and files are ordered alphabetically, respectively.

``` shell
.
├── Documents
│   ├── programming
│   │   ├── cpp.pub
│   │   ├── oop.pdf
│   │   └── python.pub
│   ├── clean-architecture.pdf
│   ├── domain-driven-design.pub
│   ├── hello.txt
│   ├── note.txt
│   └── object-oriented-analysis-and-design.pdf
├── Downloads
│   └── funny.png
├── hello.txt
└── my_profile
```

*Order by kind*: The output nodes (files and folders) are ordered according to the kind of the node and the nodes with same kind are sorted alphabetically.

``` shell
.
├── my_profile
├── Documents
│   ├── programming
│   │   ├── oop.pdf
│   │   ├── cpp.pub
│   │   └── python.pub
│   ├── clean-architecture.pdf
│   ├── object-oriented-analysis-and-design.pdf
│   ├── domain-driven-design.pub
│   ├── hello.txt
│   └── note.txt
├── Downloads
│   └── funny.png
└── hello.txt
```

##### Hint

1. Use the four iterators in the class `Folder` to distinguish and implement different ordering rules.

#### FileSystemParser

`FileSystemParser` is parser uses `FileSystemScanner` and `FileSystemBuilder` to parse a folder and the entire structure underneath it to build the entire composite structure of `Node` accordingly. `FileSystemParser::setPath(string)` sets the path to the folder that will be parsed. `FileSystemParser::parse()` reads the folders/files info with `FileSystemScanner` and build `Folder` and `File` with `FileSystemBuilder`.

`FileSystemScanner` scans the files and folders under the receiving path, non-recursively. `FileSystemScanner::setPath(string)` sets the path to the folder that will be scanned. `FileSystemScanner::nextNode()` read the info of next file or folder. `FileSystemScanner::currentNodeName()` returns the name most recently read node. `FileSystemScanner::isFile()` and `FileSystemScanner::isFolder()` tells the clients what type of the most recently read node is. `FileSystemScanner::isDone()` returns true if all the files and folders in the given path are read.


`FileSystemBuilder::buildFolder(String path)` starts to build a `Folder` for the receiving path accordingly. `FileSystemBuilder::buildFile(String path)` builds a `File` for the receiving path and add it to the currently building `Folder`. `FileSystemBuilder::endFolder()` ends the currently building folder and adds it to its parent `Folder`. `FileSystemBuilder::getRoot()` returns the pointer to the root folder.

##### Hint

1. For scanning the folders and files on the device, you can use [`<dirent.h>`](https://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html)

### Score

* Code written by students: 60%
* Passing Unit tests written by TA: 40%

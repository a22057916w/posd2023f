# POSD with C++ (and more)

#### FALL, 2023

#### Prof Y C Cheng

#### Dept of Computer Science and Information Engineering

#### Taipei Tech

### Important Links

* [Course Link](http://140.124.181.100/yccheng/posd2023f): http://140.124.181.100/yccheng/posd2023f

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 1

### Due: 2023/10/10 23:59

### Notice

* Do not change the code structure, function prototype, or interface of the provided sample code, otherwise your code might not be compilable with TA's test.
* Do not commit the object files and executable files to git, otherwise your code might not be executable on the Jenkins server.
* Your program should not cause memory leak.
* The unit test you wrote will be also graded, please write the unit test comprehensively for the code you wrote.
* The design of your program will be also be graded, please follow the required patterns precisely while writing your program.
* If your code is not compilable on the Jenkins server, you'll get no point for the assignment.

### Description

In this assignment, you will practice how to implement the **Composite** and **Iterator** patterns, and how these three patterns interacts to solve a complex problem.

In this assignment, you will build a simple file system. To start, you need to download the [template code](./template) and complete the provided class skeletons. You can add public member functions manually if needed, but do not change the prototype of the given functions. All the `virtual` are removed in the template, please add it manually if needed and decide whether it is a pure virtual or not.

You will write your makefile. Please generate an executable file `bin/ut_all` with the command `make`, otherwise, your project will not be executable on Jenkins. 

### Problem

First, you will implement two domain objects, `File` and `Folder`. Please implement the two objects in the manner of ***Composite*** pattern, where `File` is a leaf class and `Folder` is a composite class. In addition, a component abstract class `Node` is needed. Note that, a file can only be added to the folder of its path. For example, a file with the path "/Users/user/books/design-pattern.pdf" can only be added to the folder with path "/Users/user/books".

Next, please implement three iterators to traversal the file system. `FolderIterator` is a basic iterator that traverses the sub-folders and files in a folder, non-recursively. `DfsIterator` is an iterator that traverse a folder recursively in the manner of [DFS](https://en.wikipedia.org/wiki/Depth-first_search). `BfsIterator` is an iterator that traverse a folder recursively in the manner of [BFS](https://en.wikipedia.org/wiki/Breadth-first_search).

### Spec

Both `File` and `Folder` accepts a string of its path. A path is an absolute path to the file or folder including its own name. For example, a folder named "Documents" in the home directory of the system gets the path "/Users/user/home/Documents"; and a file named "hello.txt" in the "Documents" directory gets the path "/Users/user/home/Documents/hello.txt".

Each `Node` provides following member functions:

* `string name() const`: This function returns the name of the node without any path information.

* `string path() const`: This function returns the entire path of the node.

* `void add(Node * node)`: This function add a child node to the current node if the current node is a folder.

* `void remove(string path)`: This function removes the node under the given path from the composite hierarchy.
  * **HINT**: refer to *Explicit parent reference* in the Implementation section of the ***Composite*** pattern in the text book [GoF p.166]

* `Node * getChildByName(const char * name) const`: This function returns a child node according to the receiving name. `nullptr` is returned if no node matches the name.

* `Node * find(string path)`: This function returns the node under the composite structure with path matching the argument. If no matched node is found, a `nullptr` is returned. 

* `int numberOfFiles()`: This function calculates the total numbers of the files under the current node. For example, a folder "Books" gets a file "design-pattern.pdf" and a folder "SOLID". There are five files in the folder "SOLID" for the SOLID principles. The `numberOfFiles` for the folder "Books" is 6.

* `Iterator * createIterator()`: This function is a ***Factory Method*** for generating the corresponding iterators according to the concrete classes.
  * For `Folder`, it generates a `FolderIterator`.
  * Please place the implementation of `FolderIterator` in the path "src/iterator.cpp", as what we have done in the class. Otherwise, your code will not be compiled on Jenkins. 
  * For leaf classes, it generates a null iterator. 
    * **HINT**: refer to *Null Iterator* in the Implementation section of the ***Iterator*** pattern in the text book [GoF p.166]
  * **HINT**: refer to ***Factory Method*** pattern in the text book [GoF p.107-116]

The three iterators `FolderIterator`, `DfsIterator`, and `BfsIterator` should derive from the `Iterator` class.

### Score

* Code written by students: 60%
* Passing Unit tests written by TA: 40%

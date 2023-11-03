# POSD with C++ (and more)

#### FALL, 2023

#### Prof Y C Cheng

#### Dept of Computer Science and Information Engineering

#### Taipei Tech

### Important Links

* [Course Link](http://140.124.181.100/yccheng/posd2023f): http://140.124.181.100/yccheng/posd2023f

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 2

### Due: 10/24 23:59

### Notice

* Please use the given makefile. You can modify the makefile if needed, but do not remove "all", "dirs", and "clean". Also, "all" must depends on "dirs". If you have any further questions about makefile, please search and learn it manually.
* Do not change the code structure, function prototype, or interface of the provided code, otherwise your code might not be compilable with TA's test.
* Do not commit the object files and executable files to git, otherwise your code might not be executable on the Jenkins server.
* Your program should not cause memory leak.
* The unit test you wrote will be also graded, please write the unit test comprehensively for the code you wrote.
* The design of your program will be also be graded, please follow the required patterns precisely while writing your program.
* If your code is not compilable on the Jenkins server, you'll get no point for the assignment.

### Description

In this assignment, you will keep working on the file system. You will know how to apply **Visitor** pattern to a **Composite** structure. Further, you will learn improved design of the **Iterator** you wrote.

### Problem

In this assignment, you will extend the file system program from assignment 1, please do this assignment based on the [given code](./given_code), which is the suggested answer of assignment 1.

There are five questions for you to solve in this assignment:

1. Connect `Folder` and `File` to your OS. A `File` can be created only if there is an actual file under the given path with the same name on the device; same as `Folder`. To achieve this requirement, please refer to [lstate](https://linux.die.net/man/2/lstat) to get actual file/folder info from the devise file system. Note that, if a path to a folder is given to the constructor of `File`, an exception should be thrown; and vice versa.

2. Implement `FindByNameVisitor` which provides the same functionality as `list<string> findbyName(string name)` in `Node`, `File` and `Folder`.

3. Implement `StreamOutVisitor` to read files and folders. If the target is a file, return the path of the file and the entire content of the target file. If the target is a folder, return the contents of all the files under the folder, recursively. The output should follow the following example:

```shell
_____________________________________________
root/folder1/file1.txt
---------------------------------------------
hello, world
_____________________________________________

_____________________________________________
root/folder2/file2.txt
---------------------------------------------
This is file 2
This is second line
this is end of file
_____________________________________________
```

4. Refactor your code to make `FolderIterator` as an inner class of `Folder`. you need to remove the friend class relationship between `Folder` and `FolderIterator`. Using friend class is not a good approach since it causes dual dependency across the files.

5. Revise `Folder` and `FolderIterator` to make the created iterator unavailable if the structure of `Folder` is changed. For example, a client gets an iterator **it** from a folder **photo**, then the client add a new file **dog.jpg** to **photo**. In this case, **it** is no longer available as the structure of the folder is changed. An exception should be thrown if client invokes `it->next()` and `it->first()`.

### Further Specs

- Both `FindByNameVisitor` and `StreamOutVisitor` should implement the provided `Visitor` interface.

- The output format of `StreamOutVisitor`:
  - File:

    ```shell
    _____________________________________________
    root/folder1/file1.txt
    ---------------------------------------------
    hello, world
    _____________________________________________
    ```

  - Folder:
    
    ```shell
    _____________________________________________
    root/folder1/file1.txt
    ---------------------------------------------
    hello, world
    _____________________________________________

    _____________________________________________
    root/folder2/file2.txt
    ---------------------------------------------
    This is file 2
    This is second line
    this is end of file
    _____________________________________________
    ```

### Score

* Code written by students: 60%
* Passing Unit tests written by TA: 40%

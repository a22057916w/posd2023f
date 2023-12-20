# POSD with C++ (and more)

#### FALL, 2023

#### Prof Y C Cheng

#### Dept of Computer Science and Information Engineering

#### Taipei Tech

### Important Links

* [Course Link](http://140.124.181.100/yccheng/posd2023f): http://140.124.181.100/yccheng/posd2023f

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 5

### Due: Dec 13 Wed 23:59

### Notice

* **DO NOT add any .c or .cpp file in your program that is not provided or required by the assignment**
* Please use the given makefile. You can modify the makefile if needed, but do not remove "all", "dirs", and "clean". Also, "all" must depend on "dirs". If you have any further questions about makefile, please search and learn it manually.
* Do not change the code structure, function prototype, or interface of the provided code, otherwise, your code might not be compilable with TA's test.
* Do not commit the object files and executable files to git, otherwise, your code might not be executable on the Jenkins server.
* Your program should not cause memory leaks.
* The unit test you wrote will be also graded, please write the unit test comprehensively for the code you wrote.
* The design of your program will also be graded, please follow the required patterns precisely while writing your program.
* If your code is not compilable on the Jenkins server, you'll get no points for the assignment.

### Description

In this assignment, you will work on the problem we're solving in class. You will know how to apply **Singleton** and the combination of **Unit of Work**, and **Template Method** patterns to construct a database system.

### Problem

In this assignment, you will extend the database system we've modeled in class.
`Drawing` contains shapes and belongs to a Painter, and both `Drawing` and `Painter` should be saved in the database.
The shape is stored as a string in the database, so you might need `Scanner`, `Parser`, and `Builder` to rebuild a Drawing.

#### DomainObject

In class, we have written the class `Drawing`. In this assignment, you'll need to revise Drawing and implement a new class Painter and make them work with `UnitOfWork`.

##### Drawing
`Drawing` extends `DomainObject`, and has three data members:
- std::string id
- Painter * painter
- std::list<Shape *>

Different from the code we've written in class, In this assignment, you'll have to accept a `Painter` as a data member instead of a `std::string`.

##### Painter
`Painter` extends `DomainObject`, and has two data members:
- std::string id
- std::string name

#### UnitOfWork

Please implement UnitOfWork in `src/unit_of_work.h`. 

Keep track of the changes that may affect the database. When you create, update, or delete an object you should call the following methods to tell the `UnitOfWork`.

- registerNew(DomainObject *)
- registerDirty(DomainObject *)
- registerClean(DomainObject *)
- registerDeleted(DomainObject *)

For example, after you call the method below, the `Painter` object should be moved from clean to dirty.

``` c++
Painter::setName(std::string name) {
    _name = name;
    /*You should tell UnitOfWork here*/
}
```

A `DomainObject` is marked as **new** if:
- The `DomainObject` is just created.
- The `DomainObject` hasn't been saved in the database.

A `DomainObject` is marked as **clean** if:
- The `DomainObject` is the same as the database.

A `DomainObject` is marked as **dirty** if:
- The `DomainObject` is not the same as the database.

A `DomainObject` is marked as **deleted** if:
- The `DomainObject` should be deleted from the database.

You should access the db only when you **commit**. In other words, you should call Mapper only when you commit.
- void commit()

#### Mapper
##### AbstractMapper
We implemented **abstractFind** in class. In this assignment, you have to implement **abstractAdd**, **abstractDelete**, and **abstractUpdate**. 

You may need to use the **template method** to build different statements.
- updateStmt(DomainObject * domainObject)
- addStmt(DomainObject * domainObject)
- delStmt(std::string id)
- findStmt(std::string id)

##### DrawingMapper

We've done for the method **find(std::string id)** in class, you have to implement 3 methods:
- update(std::string id)
- add(DomainObject * domainObject)
- del(std::string id)

##### PainterMapper
You have to implement PainterMapper in this assignment. 
- find(std::string id)
- update(std::string id)
- add(DomainObject * Painter)
- del(std::string id)

#### SQL Statements

##### Create Table
Drawing:
``` SQL
CREATE TABLE drawing (
ID         char(6) PRIMARY KEY     not null,
painter    varchar(50)             not null,
shapes varchar(1028),
FOREIGN KEY(painter) REFERENCES painter(ID))
```

Painter:
``` SQL
CREATE TABLE painter (
ID         char(6) PRIMARY KEY     not null,
name    varchar(50)                not null);
```

### Score

* Design by students: 60%
* Passing Unit tests written by TA: 40%
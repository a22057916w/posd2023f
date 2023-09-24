## Pattern Oriented Software Design, Fall 2023
- Instructor: Prof. Y C Cheng
- Class meeting time: Mon 5-6-7
- Class meeting place:
  - CB2-207 (in person)
  - [Microsoft Teams](https://teams.microsoft.com/l/team/19%3arx_SzFvbX9zrlkaCgj-nhRG10GaY3kcyv86eZbP5IaE1%40thread.tacv2/conversations?groupId=ddb0ff79-028c-4dbc-bba3-1a7fa6eb1b3c&tenantId=dfb5e216-2b8a-4b32-b1cb-e786a1095218) (when distance learning is in effect 9/11~9/28)
- Office hours: Tue 1-2-3-4
- Course Repo: Course repository: http://140.124.181.100/yccheng/posd2023f
- TA: 
  - Patrick Hu \<nightlord851108@gmail.com\>, Richard Cheng \<t111598015@ntut.org.tw\> (Room 1624 S&T)
  - Office hours: 10-12 am and 14-17 pm, Wed
- TA's homework repository: [posd2023f_TA](http://140.124.181.100/course/posd2023f_ta)

### Synopsis 

This course aims to build a foundation for students to build software with _design patterns_ and mainstream _programming paradigms_ used in modern software development. We will also cover the SOLID principles of object-oriented design. These topics will be threaded in two to three long-running examples developed in the classroom with participation from students. 

Design patterns examine reusable solutions to object-oriented design problems (maintainability, extendability, etc.) in software developed in object-oriented languages like C++, Java, Python, Ruby, OCaml and so on.

  - design patterns
    - individual patterns by category as they are encountered in the running example
    - application of multiple patterns
    - real-world examples

The programming paradigms affect how design patterns are implemented. Although object orientation is the main paradigm, other paradigms that contribute to a cleaner implementation are examined in the context of design patterns implementation.

  - Programming paradigms
    - procedure (ad hoc polymorphism, c, python)
    - function (as in math functions, main abstraction in lisp, scheme, haskell, ...)
    - generics and templates (static polymorphism)
    - object orientation (dynamic polymorphism, in all object-oriented languages such as C++, Java, Ruby, Python, ...)
    - static typing vs dynamic typing

SOLID principles examine object-oriented design principles behind object-oriented software design, patterns and beyond, to achieve _separation of concerns_. We will look at source level principles and review of their use in the running example

The main part of lectures is threaded with a long-running example involving the creation, manipulation, and storage of geometric shapes. Development of the example is done mostly in class meetings; it is done iteratively and incrementally and with test-driven development, mob programming, and continuous integration. Source code is available to class participants through a repository.

  - Problem solving with _How To Solve It_ (HTSI):
    - _understanding the problem_, _devising a plan_, _carrying out the plan_, and _looking back_
  - Engineering practices
    - mob programming with strong style pair programming
      - class participants will take turn playing the roles of _driver_ and _navigator_
    - code proceeded by tests: _failing test-passing test-refactoring_ _TDD_
      - google test 
    - source control through git
    - program builds through builders and continuous integration

## Homework, exams, and grading policy
  - Homework*6: 40%
  - Midterm 1 (Lab test): 20%
  - Midterm 2 (Lab test): 20%
  - Final (Pen-and-paper test): 20%
## Textbook
  - Gamma, Erich, et al. Design patterns: elements of reusable object-oriented software. Pearson Education, 1994.
## Problems

**Problem 1 : sorting shapes**
A simple geometry application called _geo_ is needed to sort shapes such as triangles, circles, rectangles and others. As a command line application, _geo_ reads shapes from an input file, sorts the shapes by area or perimeter in increasing order or decreasing order, and write the result to an output file. For example,
```
geo input.txt output.txt area inc
```
sorts the shapes in file _input.txt_ in increasing order by area, and writes the result to the file _output.txt_. And
```
geo input.txt output.txt perimeter dec
```
sorts the shapes in file _input.txt_ in decreasing order by perimeter, and writes the result to the file _output.txt_.

**Problem 2: Shape manipulation**

A program for manipulating geometric shapes is needed. With the program, the user creates/deletes/modifies simple shapes such as square, circle, triangle, and convex polygons. Individual shapes will have properties such as area, perimeter, color and so on. Compound shapes can be formed from individual shapes. Area and perimeter properties are still needed on compound shapes. A compound shape can include other compound shapes. The following operations on shapes are needed.

- Add shapes to a compound shape;
- Delete shapes from a compound shape;
- Group and ungroup;
- Move shapes out of a compound shape;
- Move shapes from a compound shape to another compound shape;
- Select shapes by Boolean expression on the properties area, perimeter, color and type; and
- Load/store shapes from/into a file.

**Problem 3: Patient monitoring [adapted from Jackson 2001, pp, 21-29]**
A patient monitoring program is required for a hospital. Each patient is monitored by an analog device which measures factors such as pulse, temperature, blood pressure, and skin resistance. The program reads these factors on a periodic basis (specified for each patient) and stores the factors in a database. For each patient, safe ranges for each factor are also specified by medical staff. If a factor falls outside a patient's safe range, or if an analog device fails, the nurse's station is notified.

- initial setup for a patient
- discharging a patient
- movement inside hospital (For comfort and portability, allowing patients to move around while still being monitored)
- visualization 

**Lectures**

Week 1, 9/11/2023
- introduction 
- Review of OOP principles (1) by solving Problem 1

Week 2, 9/18/2023
- subtype polymorphism
- sorting: parametric polymorphism 
  - containers
  - algorithms
  - iterators
  
**Exercise: Complete the program for Problem 1** 

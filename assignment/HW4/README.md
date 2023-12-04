# POSD Assignment 4 (Lab 1)

#### FALL, 2023

#### Prof Y C Cheng

#### Dept of Computer Science and Information Engineering

#### Taipei Tech

## Lab 1

### Deadline : 2023/11/29 23:59

### Allowed materials

- Text book: Design Patterns Elements of Reusable Object-Oriented Software.
- Lab GitLab: http://140.124.181.100
- Dictionary: https://dictionary.cambridge.org/zht/
- CPlusPlus.com: https://cplusplus.com
- CppReference: https://cppreference.com
- GoogleTest User Guide: https://google.github.io/googletest/
- course link: http://140.124.181.100/yccheng/posd2023f
- jenkins link: http://140.124.181.97:8080

### Notice

* **DO NOT add any `.c` or `.cpp` file in your program that is not provided or required by the assignment**
* Please use the given makefile. You can modify the makefile if needed, but do not remove "all", "dirs", and "clean". Also, "all" must depends on "dirs". If you have any further questions about makefile, please search and learn it manually.
* Do not change the code structure, function prototype, or interface of the provided code, otherwise your code might not be compilable with TA's test.
* Do not commit the object files and executable files to git, otherwise your code might not be executable on the Jenkins server.
* Your program should not cause memory leak.
* The unit test you wrote will be also graded, please write the unit test comprehensively for the code you wrote.
* The design of your program will be also be graded, please follow the required patterns precisely while writing your program.
* If your code is not compilable on the Jenkins server, you'll get no point for the assignment.

### Problem

In this lab test, you are going to implement a simplified JSON format beautifier.
Enclosed by a pair of curly brackets `{` and `}`, a JSON object contains a set of comma-separated key-value pairs, where the key is a string and the value is either a string or a JSON object. Here is an example of a JSON object:

```json
{
    "books": {
        "design pattern": {
            "author": "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides",
            "name": "Design Patterns Elements of Reusable Object-Oriented Software"
        },
        "clean code": {
            "author": "Robert C. Martin",
            "name": "Clean Code"
        }
    }
}
```

This JSON object has only one key-value pair, where the key is the string "books" and the value is another JSON object having two key-value pairs. In the first pair, the key is "design pattern" and the value is yet another JSON object whose two keys are "name" and "author", respectively, and so on. Similarly, the second pair has the key "clean code" and yet another JSON object as its value.

In this program, a parser and a builder are needed to parse a JSON format string to build the `Value`, including `JsonObject` and `StringValue`. For example, a JSON string in C++ can be represented as:

```c++
string booksJson = 
    "{\"books\": {"
    "\"design patterns\": {"
    "\"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\","
    "\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\""
    "},"
    "\"clean code\": {"
    "\"name\": \"Clean Code\","
    "\"author\": \"Robert C. Martin\""
    "}"
    "}}"
```

As can be seen, the JSON string above is not easy to read. You need to build a beautifier visitor that generates a beautified JSON string of a `JsonObject`. The following shows an example of a beautified JSON string:

```c++
"{\n"
"    \"books\": {\n"
"        \"clean code\": {\n"
"            \"author\": \"Robert C. Martin\",\n"
"            \"name\": \"Clean Code\"\n"
"        },\n"
"        \"design patterns\": {\n"
"            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n"
"            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n"
"        }\n"
"    }\n"
"}";
```

### Specification for your program

Please copy the [given template code](./given_code) to your own assignment repository and complete the exam based on it.

#### Value

Refer to the textbook, you will implement a *Composite* structure to model JSON data as the class diagram shown below. In the diagram, `Value` is the **Component**, `StringValue` is the **Leaf**, and `JsonObject` is the **Composite**. 

![class diagram](img/json_class_diagram.png)

There are three tests in `test/json_test.h` in the given code. Please implement the code to make the three tests pass.

**HINT > use `std::map`**

In addition, the method `JsonObject::set(string key, Value * element)` is not only for adding a key-value pair with a new key to a `JsonObject`, but also for updating the key-value pair with an existing key.

#### JsonIterator

The method `Value::createIterator()` is a *Factory Method* for creating a `JsonIterator`; where a `JsonObject` creates a `JsonObjectIterator`, and a `StringValue` creates a `NullIterator`. Both `JsonObjectIterator` and `NullIterator` derive from the abstract class `JsonIterator`.

A `JsonObjectIterator` traverses the key-value pairs under the `JsonObject`. The iterator should traverse the pairs according to the key **alphabetically**. `JsonObjectIterator::currentKey()` returns the key of the current item, and `JsonObjectIterator::currentValue()` returns the value of the current item.

**HINT > use `std::map::iterator`**

A `NullIterator` is not traversable, and `NullIterator::isDone()` always returns true. If `NullIterator::currentKey()` or `NullIterator::currentValue()` is invoked, an exception should be thrown.

#### BeautifyVisitor

The method `Value::accept(Visitor * visitor)` accepts a visitor for extending the functionalities to `Value` with visitors. `BeautifyVisitor`, which derives from `Visitor`, is for generating a beautified Json string from a `Value`.

In `BeautifyVisitor`, the member function `visitJsonObject(JsonObject * obj)` visits a `JsonObject` to add the beautified key-value string to the resulting string. The member function `visitStringValue(StringValue * val)` visits a `StringValue` to add the value to the resulting string. The member function `getResult()` gets the resulting beautified Json string. A beautified Json string is defined with following requirements:

- Line breaks after a `'{'`,
- a `':'` is placed right after the key with no whitespace between them,
- a space exists after a `':'` before the value,
- a `','` exists right after the value if there is other key-value pairs left,
- line breaks after the end of each value, and
- the indent of each level is 4 spaces.

Beautified Json string example:

```json
{
    "books": {
        "clean code": {
            "author": "Robert C. Martin",
            "name": "Clean Code"
        },
        "design pattern": {
            "author": "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides",
            "name": "Design Patterns Elements of Reusable Object-Oriented Software"
        }
    }
}
```

### JsonParser

Finally, you will implement `JsonParser` to parse a Json string and build the `Value` accordingly. Part of the implementation for `JsonParser` is already provided in the given code, please fill in the missing code where we commented `// fill in the code`.

- `JsonParser::parse()` parses the string and builds the `Value` composite structure.
- `JsonParser::getJsonObject()` returns the root of the built `JsonObject`.

`JsonScanner` scans over the entire Json string, one character at a time. The implementation for `JsonScanner` is already provided and no need to change.

`JsonBuilder` supports building the composite structure of `Value`. `JsonBuilder` should follow the following specs:

- `JsonBuilder::buildObject(string key)` starts to build a `JsonObject` with a key.  
  **HINT > you might need to use `std::pair`**
- `JsonBuilder::buildValue(string key, string value)` builds a `StringValue` and add it to the currently building `JsonObject`.
- `JsonBuilder::endObject()` ends the currently building `JsonObject` and adds it to its parent `JsonObject`.
- `JsonBuilder::getJsonObject()` returns the built `JsonObject`.

### Scoring

* Code written by students: 60%
* Passing Unit tests written by TA: 40%

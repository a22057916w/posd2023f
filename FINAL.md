### 1. <br> This problem is about *composition* and *inheritance*.
  (a) *True or False*: a design pattern of the object scope uses composition but not inheritance. If true, why? If false, give a counter-example. <br>
  <p>
  *False*, the object scope pattern also applies inheritance, taking **Composite** pattern as an example. The following code shows a 
  simple **Composite** pattern where **Circle** and **Compound** inherit the method in **Shape**. <br>
  </p>
  ```
  class Shape {
    virtual void draw() = 0;
  };
  class Circle : public Shape {
    void draw() override {
      // draw circle
    }
  };
  class Compound : public Shape {
    void draw() override {
      // draw compound
    }
  };
  ```
  (b) *True or False*: of the two versions of  the Adapter (139) pattern, the class adapter is more flexible than the object adapter. Explain your answer. <br><br>
  
### 2. <br> This problem is about the *Liskov Substitution Principle*. Consider a base class **Base** with a data member **r** of the type **double** and a virtual method **sqrt()** for computing the square root of **r**. When called, **sqrt()** checks if **r** is greater than or equal to 0. If so, it performs computation on **r**; if not, it throws an exception. <br> In Johnny's application, his number **r** must be between 3 and 9. Since Johnny still needs the **sqrt()** member function, he writes a class **Derived** which publicly inherits **Base**. He overrides the method **sqrt()** with the following behavior: it checks if **r** is between 3 and 9. If so, it performs computation on **r**; if not, it throws an exception.
  (a) *True or False*: the class **Derived** is compliant with LSP. Explain your answer. <br><br>
  (b) Write a unit test for checking compliance of LSP for **Base** and **Derived**.

### 3. <br> In the *Open-Closed Principle*, it is said that "Since closure cannot be complete, it must be strategic".
  (a) Early in our course this semester, Composite (163) is applied for relating the classes **Shape**, **Circle**, **CompositeShape**, etc. With regard to these classes, what kind of change are they strategically closed against? Under what kind of change does the strategic closure fail? What is the consequence? <br><br>
  (b) Among the 23 patterns in the textbook, which pattern can be applied to fix the failure of the strategic closure in (a)? Briefly explain how this is done.

### 4. <br> In the **Shape** example in class, to read shape information stored on file and create corresponding shapes and their compositions in memory, we use three collaborating classes: **Parser**, **Scanner**, and **ShapeBuilder**. We wrote the constructor as in line 3 - line 8 shown below.
```
class Parser {
public:
  Parser(std::string input)" _input(input) {
    _builder = ShapeBuilder::instance();
    _scanner = new Scanner(_input);
  }
  void parse() { ... }
  std::vector<Shape*> getResult() { return _result; }
private:
  std::string _input;
  std::vector<Shape*> _result;
  ShapeBuilder * _builder;
  Scanner * _scannerl
};
```
  (a) Argue that the constructor in line 3 - line 6 is a bad design by identifying the SOLID principle it violates. <br><br>
  (b) Suggest a fix to improve it, You can change the signature of the constructor in your design. Argue that your fix is a better design.

### 5. <br> Your team is developing a new application for your company. The new application must use a completed existing system maintained by the other team. Luckily, you only need a service from the existing system, which involves several objects collaborating to achieve. The other team has been ordered to help your team by adding any object to the existing system for you. Suppose you were to ask the other team to help by adding a new object according to one of the 23 patterns of the textbook, what pattern would you pick? Explain why.
  <br><br>

### 6. <br> Use one of the **Shape** classes to give an example in which the Proxy (207) pattern is implemented exactly like the Decorator (175) pattern.
  <br><br>

#### 1. <br> This problem is about *composition* and *inheritance*.
  (a) *True or False*: a design pattern of the object scope uses composition but not inheritance. If true, why? If false, give a counter-example. <br><br>
  *False*, the object scope pattern also applies inheritance, taking **Composite** pattern as an example. The following code shows a 
  simple **Composite** pattern where **Circle** and **Compound** inherit the method in **Shape**. <br>
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
  *False*, the object adapter is more flexible than the class adapter. <br> 
  The class adapter uses **multiple inheritance** to adapt the adaptee(or interface), while the object adapter uses **object composition**(reference, pointer) to combine the adaptee. If there is a subclass of the adaptee, the object adapter will work well with that, while the class adapter will have no access to it. <br><br> 
  
#### 2. <br> This problem is about the *Liskov Substitution Principle*. Consider a base class **Base** with a data member **r** of the type **double** and a virtual method **sqrt()** for computing the square root of **r**. When called, **sqrt()** checks if **r** is greater than or equal to 0. If so, it performs computation on **r**; if not, it throws an exception. <br> In Johnny's application, his number **r** must be between 3 and 9. Since Johnny still needs the **sqrt()** member function, he writes a class **Derived** which publicly inherits **Base**. He overrides the method **sqrt()** with the following behavior: it checks if **r** is between 3 and 9. If so, it performs computation on **r**; if not, it throws an exception.
  (a) *True or False*: the class **Derived** is compliant with LSP. Explain your answer. <br><br>
  *False*, the class **Derived** is not compliant with LSP. <br>
  The derived precondition(if between 3 and 9) is **stronger** than that of **Base** class, which violates the "Design by Contract". If a Derived object is assigned to a Base pointer. The check    condition is changed from the Base to Derived, and the user might not know the condition of the Derived class, which might lead to an unexpected error. <br>
  
  (b) Write a unit test for checking compliance of LSP for **Base** and **Derived**. <br>
  ```
  TEST(DerivedSqrt, LSP) {
    for(double i = 0; i < DBL_MAX / 2; i++) {
      Base * od = new Derived(i);
      EXPECT_NO_THROW(od->sqrt());
      delete od;
  }
  ```
  <br><br>
  
#### 3. <br> In the *Open-Closed Principle*, it is said that "Since closure cannot be complete, it must be strategic".
  (a) Early in our course this semester, Composite (163) is applied for relating the classes **Shape**, **Circle**, **CompositeShape**, etc. With regard to these classes, what kind of change are they strategically closed against? Under what kind of change does the strategic closure fail? What is the consequence? <br>
  
  New types of shapes (e.g., new classes derived from Shape) can be added without affecting existing code. The pattern is closed against     
  **changes in the component classes**. <br>
  If we were to add a new module that is not related to the composite struct, which might involve changing the **Composite Structure**. It is   
  a failure against **changes in structure**. <br>
  
  (b) Among the 23 patterns in the textbook, which pattern can be applied to fix the failure of the strategic closure in (a)? Briefly explain how this is done. <br>
  We can isolate the unrelated module by **Visitor** pattern, the Shape composite needs only to accept the visitor by a single **accept()**
  method. Therefore, does not compromise the Shape composite structure. <br><br>

  
#### 4. <br> In the **Shape** example in class, to read shape information stored on file and create corresponding shapes and their compositions in memory, we use three collaborating classes: **Parser**, **Scanner**, and **ShapeBuilder**. We wrote the constructor as in line 3 - line 6 shown below.
```
class Parser {
public:
  Parser(std::string input): _input(input) {
    _builder = ShapeBuilder::instance();
    _scanner = new Scanner(_input);
  }
  void parse() { ... }
  std::vector<Shape*> getResult() { return _result; }
private:
  std::string _input;
  std::vector<Shape*> _result;
  ShapeBuilder * _builder;
  Scanner * _scanner;
};
```
  (a) Argue that the constructor in line 3 - line 6 is a bad design by identifying the SOLID principle it violates. <br><br>
  It violates the **Dependency Inversion Principle(DIP)**. The **Parser** class depends on the lower-level classes **ShapeBuilder** and 
  **Scanner**, if there is another build or scanner, the **Parser** policy cannot adopt it and thus, fails to reuse. <br>  
  
  (b) Suggest a fix to improve it, You can change the signature of the constructor in your design. Argue that your fix is a better design. <br>
  ```
  class Parser {
  public:
    Parser(std::string input): _input(input) {
      _builder = AbstractBuilder::instance();
      _scanner = new AbstrctScanner(_input);
    }
    void parse() { ... }
    std::vector<Shape*> getResult() { return _result; }
  private:
    std::string _input;
    std::vector<Shape*> _result;
    AbstrctBuilder * _builder;
    AbstrctScanner * _scanner;
  };
  ```
  <br>
  
  Let the **Parser** depend on the interface of the low-level classes, which are **AbstrctBuilder** and **AbstrctScanner**. With the dependency   inversion, the **Parser** can now take any kind of **Builder** and **Scanner** without changing its policy(code). <br><br>

#### 5. <br> Your team is developing a new application for your company. The new application must use a completed existing system maintained by the other team. Luckily, you only need a service from the existing system, which involves several objects collaborating to achieve. The other team has been ordered to help your team by adding any object to the existing system for you. Suppose you were to ask the other team to help by adding a new object according to one of the 23 patterns of the textbook, what pattern would you pick? Explain why.
  Apply the **Visitor** pattern. I would have the new object as a visitor class or subclass. Therefore, in my application, I only need to **accept** the new object as a visitor to get the service from the existing system. <br><br>

#### 6. <br> Use one of the **Shape** classes to give an example in which the Proxy (207) pattern is implemented exactly like the Decorator (175) pattern.
  ```
  class Circle : public Shape {
  public:
    void draw() override {
      // draw the circle
    }
  };
  class CircleProxy : public Shape {
  public:
    void draw() override {
      _circle->draw();
    }
  private:
    Circle * _circle;
  };
  class CircleDecorator : public Shape {
  public:
    void draw() override {
      _circle->draw();
      drawBorder();
    }
    void drawBorder() {
      // draw border for circle
    }
  private:
    Circle * _circle;
  };
  ```
The **CircleProxy** and **CircleDecorator** both hold a reference to **Circle** and forward the **draw()** operation to **Circle**. If **CircleDecorator** doesn't implement **drawBorder()**, the **CircleProxy** is exactly like the **CircleDecorator**. <br>

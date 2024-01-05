### 1. <br> This problem is about *composition* and *inheritance*.
  (a) *True or False*: a design pattern of the object scope uses composition but not inheritance. If true, why? If false, give a counter-example. <br><br>
  (b) *True or False*: of the two versions of  the Adapter (139) pattern, the class adapter is more flexible than the object adapter. Explain your answer. <br><br>
  
### 2. <br> This problem is about the *Liskov Substitution Principle*. Consider a base class **Base** with a data member **r** of the type **double** and a virtual method **sqrt()** for computing the square root of **r**. When called, **sqrt()** checks if **r** is greater than or equal to 0. If so, it performs computation on **r**; if not, it throws an exception. <br> In Johnny's application, his number **r** must be between 3 and 9. Since Johnny still needs the **sqrt()** member function, he writes a class **Derived** which publicly inherits **Base**. He overrides the method **sqrt()** with the following behavior: it checks if **r** is between 3 and 9. If so, it performs computation on **r**; if not, it throws an exception.
  (a) *True or False*: the class **Derived** is compliant with LSP. Explain your answer. <br><br>
  (b) Write a unit test for checking compliance of LSP for **Base** and **Derived**.

### 3. <br> In the *Open-Closed Principle*, it is said that "Since closure cannot be complete, it must be strategic".
  (a) Early in our course this semester, Composite (163) is applied for relating the classes **Shape**, **Circle**, **CompositeShape**, etc. With regard to these classes, what kind of change are they strategically closed against? Under what kind of change does the strategic closure fail? What is the consequence? <br><br>
  (b) Among the 23 patterns in the textbook, which pattern can be applied to fix the failure of the strategic closure in (a)? Briefly explain how this is done.

### 4.

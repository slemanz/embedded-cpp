# More about Class

### Class Inheritance

Is a fundamental concept of Object-Oriented Programming (OOP) that allows a new
class (the derived class or child class) to inherit properties and behaviors
(data members and member functions) from an existing class (the base class or
parent class). This mechanism promotes code reusability and establishes an
"is-a" relationship between classes. 

The general syntax for declaring a derived class is:

```cpp
class DerivedClass : access_specifier BaseClass
{
    // Members of DerivedClass
};
```

(access_specifier can be `public`, `protected`, or `private`, controlling the
visibility of inherited members in the derived class.)

[Inheritance Example](App/Src/inheritance.cpp)

### Access Specifiers

Are keywords that define the accessibility or visibility level of class members
(data members and member functions). They are fundamental to encapsulation, a
core principle of Object-Oriented Programming (OOP), as they control which parts
of a program can access the internal workings of a class.


There are three primary access specifiers in C++:

**public:**

- Members declared as public are accessible from anywhere in the program, both
inside and outside the class. 
- They define the public interface of the class, allowing other parts of the
program to interact with the class's functionality.
- Example: Member functions that provide services or retrieve data from the
class are often declared public

**private:** 

- Members declared as private are only accessible within the same class. 
- They cannot be accessed directly from outside the class, including by derived
classes or external functions
- private members are used to encapsulate the internal state and implementation
details of a class, hiding them from external access and preventing unauthorized
modification. 
- By convention, data members are typically declared private to ensure data
integrity and enforce controlled access through public member functions (e.g.,
getter and setter methods).

**protected:**

- Members declared as protected are accessible within the same class and by its
derived classes. 
- They are not directly accessible from outside the class by non-derived classes
or external functions.
- protected members facilitate inheritance, allowing derived classes to access
and potentially modify base class members while maintaining a level of
encapsulation from external code.

**[Access Specifiers - Example](App/Src/acessSpecifiers.cpp)**

### Class Pointers

A class pointer is a pointer variable specifically designed to store the memory
address of an object (an instance) of a particular class. This allows for
indirect access and manipulation of the object's members (data members and
member functions).

A class pointer is declared similarly to other pointers, using the class name
followed by an asterisk (*). It is then initialized with the address of an
existing object using the address-of operator (&).

```cpp
int main() {
    MyClass obj;
    MyClass* ptr;
    ptr = &obj;
}
```

The new operator is used to dynamically allocate memory for objects of a class
on the heap.

To create an object of ClassName on the heap and get a pointer to it, use the
new operator followed by the class name and any constructor arguments.

```cpp
ClassName* pointerName = new ClassName(constructor_arguments);
```

To access members (data members or member functions) of the object pointed to by
a class pointer, use the arrow operator (->)

```cpp
pointerName->memberVariable;
pointerName->memberFunction();
```

Memory allocated with new must be explicitly deallocated using the delete
operator to prevent memory leaks. This calls the object's destructor before
releasing the memory.

```cpp
delete pointerName;
```

### Function Overriding

Is a core concept of object-oriented programming that allows a derived class to
provide its own specific implementation of a function that is already defined
in its base class. This mechanism is essential for achieving runtime
polymorphism. 


```cpp
// Base class
class Animal
{
    public:
        // Function to be overridden
        void speak()
        {
            printf("Animal makes a sound\n");
        }
};

// Derived class
class Dog : public Animal
{
    public:
        // Overriding the speak() function
        void speak()
        {
            printf("Dog barks: Woof!");
        }
};
```

### Virtual Function

Is a member function in a base class that is overridden in a
derived class. It allows runtime polymorphism, meaning the correct function is
called based on the actual object type, not the pointer/reference type.

When a base class pointer or reference points to an object of a derived class,
and a virtual function is called through that pointer or reference, C++
determines which version of the function (base class or derived class) to
execute at runtime based on the actual type of the object being pointed to. 


```cpp
// Base class
class Animal
{
    public:
        // Function to be overridden
        virtual void speak()
        {
            printf("Animal makes a sound\n");
        }
};

// Derived class
class Dog : public Animal
{
    public:
        // Overriding the speak() function
        void speak()
        {
            printf("Dog barks: Woof!");
        }
};
```

**[Virtual Function - Example](App/Src/virtual_function.cpp)**

### Polymorphism

Is a core principle of Object-Oriented Programming (OOP) that allows objects to
Take on multiple forms or exhibit different behaviors based on their context.
The word "polymorphism" itself means "many forms."

Polymorphism is mainly achieved through:

1. Function Overriding (with virtual functions)

2. Pointers/References to Base Class

In C++, polymorphism is Broadly categorized into two main types:

**Compile-time Polymorphism (Static):**
This type of polymorphism is resolved during the compilation
Phase. 

- Function overloading
- Operator overloading
- Templates

**Runtime Polymorphism (Dynamic):**
This type of polymorphism is resolved during program execution.

- Virtual functions (as shown above)
- Function overriding

**[Polymorphism - Example](App/Src/polymorphism_1.cpp)**

### Pure Virtual Functions and Polymorphism

Is a virtual function that has no implementation in the base class and must be
overridden by derived classes. A class containing at least one pure virtual
function becomes an abstract class, which cannot be instantiated directly.

```Cpp
class Animal
{
    public:
        // Pure virtual function (must be overridden)
        virtual void speak() = 0;  // = 0 makes it pure virtual
        
        // Virtual destructor (still needed)
        virtual ~Animal() {}
};
```


**[Polymorphism Pure Virtual - Example](App/Src/polymorphism_2.cpp)**

### The Class Friend

Is a class that is granted special permission to access the private and protected
members of another class. This mechanism allows for controlled relaxation of
encapsulation in specific scenarios where two classes are closely related and
need direct access to each other's internal data or functionality. 

```cpp
class MyClass
{
    private:
        int privateData;
    public:
        // Declare AnotherClass as a friend
        friend class AnotherClass; 
    };

    class AnotherClass {
    public:
        void accessMyClassData(MyClass& obj) {
            obj.privateData = 10; // Allowed because AnotherClass is a friend
        }
    };
```

### Static Variable

In C++, the static keyword has different meanings depending on its context:

**Static Local Variables:**

- When declared inside a function, a static local variable retains its value
between successive calls to that function. 
- It is initialized only once, the first time the function is called, and exists
for the entire duration of the program.

**Static Global Variables (File Scope):**

- When declared at global scope (outside any function) with the static keyword,
the variable has internal linkage. 
- This means it is only visible and accessible within the compilation unit (the
.cpp file) where it is defined, and cannot be accessed from other files using
extern.

**Static Class Members (Data Members):**

- When a data member of a class is declared static, it belongs to the class
itself, not to any specific object of that class.
- There is only one copy of a static data member, shared by all instances of the
class.
- It must be defined outside the class definition (at file scope) to allocate
storage for it.

```cpp
class MyClass
{
    public:
    static int count; // Declaration
};

int MyClass::count = 0; // Definition and initialization
```

**[Static variable in class - Example](App/Src/static_variable.cpp)

### Static Functions

When applied to functions, it can refer to either static member functions within
a class or static non-member functions (global functions with internal linkage).

**Static Member Functions**

- Belong to the Class, Not Objects:
Static member functions are associated with the class itself, rather than with
any specific object (instance) of that class. This means they can be called
using the class name and the scope resolution operator (::), even without
creating an object of the class. 

- Access to Static Members: They can only directly access static data members
and other static member functions of the same class. 

Common Uses::
Often used for utility functions that operate on class-level data or perform
operations related to the class as a whole (e.g., managing a count of objects,
providing factory methods).

```cpp
class MyClass
{
    public:
        static int objectCount; // Static data member
        static void incrementCount() // Static member function
        { 
            objectCount++;
        }
};
int MyClass::objectCount = 0; // Definition of static data member

int main() {
    MyClass::incrementCount(); // Calling static member function
    return 0;
}
```

### Class Template

A class template in C++ enables the creation of a single class definition that
can operate with various data types without requiring the code to be rewritten
for each specific type. This promotes code reusability and type safety.

A class template is declared using the template keyword followed by template
parameters enclosed in angle brackets (<>). These parameters typically represent
type placeholders.

```cpp
template <class T>
class MyClass
{
    public:
        T data;
        MyClass(T val) : data(val) {}
        void printData()
        {
            // Code to print 'data'
        }
};
```

In C++ templates, there is no functional difference between using class and
typename in the template parameter declaration. They are completely
interchangeable in this context.

```cpp
template <class T>  // works
template <typename T> // also works exactly the same way
```

Modern Convention:

- Use typename when the template parameter can be any type (most common case)

- Use class when you specifically want to emphasize that the parameter should be a
class type (though the compiler won't enforce this)

**[Class template](App/Src/class_template.cpp)**

## Namespace

Are declarative regions that provide a scope to identifiers (names of types,
functions, variables, etc.) within them. Their primary purpose is to organize
code into logical groups and, crucially, to prevent naming collisions,
especially in large codebases or when incorporating multiple libraries.

**Declaration and Usage:**

Declaration

```cpp
namespace MyNamespace
{
    int myVariable;
    void myFunction();
}
```

Accessing Members

```cpp
MyNamespace::myVariable = 10;
MyNamespace::myFunction();
```

Using Directive

```cpp
using namespace MyNamespace; // Brings all identifiers from MyNamespace into scope
myVariable = 20; // Now directly accessible
```

Or, for specific identifiers

```cpp
using MyNamespace::myFunction; // Brings only myFunction into scope
myFunction();
```

### Destructor

Is a special member function of a class that is automatically invoked when an
object of that class is destroyed or goes out of scope. Its primary purpose is
to perform cleanup operations and release any resources acquired by the object
during its lifetime. 

A destructor has the same name as its class, preceded by a tilde (`~`). For
example, for a class `MyClass`, its destructor would be `~MyClass().`

**[Destructor - Example](App/Src/destructor.cpp)**

### Virtual Destructor

Is a destructor of a base class declared with the virtual keyword. Its primary
purpose is to ensure proper destruction of objects in an inheritance hierarchy,
especially when dealing with polymorphism. 

When a derived class object is deleted through a pointer to its base class, if
the base class destructor is not virtual, only the base class's destructor will
be called. This can lead to resource leaks or undefined behavior if the derived
class has its own resources that need to be deallocated by its specific
destructor. 

By making the base class destructor virtual, the C++ runtime ensures that the
correct destructor (i.e., the destructor of the most derived class) is called
first, followed by the destructors of its base classes in the correct order.
This guarantees that all resources acquired by the derived class are properly
released before the base class resources are deallocated.

**[Virtual Destructors - Example](App/Src/destructors_virtual.cpp)**
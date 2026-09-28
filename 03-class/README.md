# Class

a class is a user-defined data type that serves as a blueprint for creating
objects. It encapsulates data (member variables) and functions (member
functions) that operate on that data into a single unit.

### Class Property Functions 

Refers to member functions that provide controlled access to the private data
members (attributes) of a class. These are commonly known as getter and setter
methods, or more broadly, accessor and mutator methods.

- Getters (Accessor Methods)

```Cpp
class MyClass
{
    private:
        int myValue;

    public:
        int getMyValue() const
        { 
            return myValue;
        }
};
```

- Setters (Mutator Methods)

```cpp
class MyClass
{
    private:
        int myValue;

    public:
        void setMyValue(int value)
        { 
            if (value >= 0)
            {
                myValue = value;
            }
        }
};
```

**[Property function - Led example](App/Src/property_fn.cpp)**

### Class Constructors

A special member function of a class that is automatically invoked when an
object of that class is created. Its primary purpose is to initialize the
object's member variables and perform any necessary setup for the object's
proper functioning. 

```cpp
class MyClass
{
    public:
        int data1;
        double data2;

        // Default Constructor
        MyClass()
        {
            data1 = 0;
            data2 = 0.0;
        }

        // Parameterized Constructor
        MyClass(int d1, double d2)
        {
            data1 = d1;
            data2 = d2;
        }

        // Constructor with member initializer list (more efficient)
        MyClass(int d1) : data1(d1), data2(0.0) {}
};
```

### Scope Resolution

The process by which the compiler determines which declaration of an identifier
(like a variable, function, or class) is being referenced in a particular
context. This is crucial because C++ allows for identifiers with the same name
to exist in different scopes, potentially leading to ambiguity if not properly
managed.

The primary mechanism for explicit scope resolution in C++ is the scope
resolution operator (`::`).

- Accessing Global Variables When Local Variables Hide Them:

```cpp
int x = 10; // Global variable

int main()
{
    int x = 20; // Local variable
    printf("Local: %d\n", x);
    printf("Global: %d\n", ::x);
    return 0;
}
```

- Referring to Namespaces:

```cpp
namespace MyNamespace
{
    int value = 100;
}

int main()
{
    printf("%d\n", MyNamespace::value);
}
```

Also used for defining member functions outside the class:

- **[Scope Resolution - Led Hpp](App/Inc/led.hpp)**

- **[Scope Resolution - Led Cpp](App/Src/led.cpp)**

- **[Scope Resolution - Led Example](App/Src/scope.cpp)**

### this pointer

Is an implicit, constant pointer available within all non-static member
functions of a class. Its primary purpose is to point to the current object
instance on which the member function is being called. 

- Resolving Name Conflicts:

```cpp
class MyClass
{
    public:
        int value;

    void setValue(int value)
    {
        this->value = value; 
    }
};
```

- Chaining Member Functions:

```cpp
class MyClass
{
    public:
        int data;

    MyClass& setData(int d)
    {
        this->data = d;
        return *this;
    }
};
```

### Differences between Class and Struct

In C++, the fundamental difference between a class and a struct lies in their
default member access specifiers and default inheritance access.

- Default Member Access:
    - struct: Members (data and functions) declared within a struct are public by
    default. This means they can be accessed directly from outside the struct or by
    functions not part of the struct. 
    - class: Members declared within a class are
    private by default. This means they can only be accessed by other members of the
    same class or by friend functions/classes.

- Default Inheritance Access:
    - struct: When one struct inherits from another struct
    or class, the inheritance is public by default. 
    - class: When one class inherits from another class or struct, the
    inheritance is private by default.

### The function Friend

Is a non-member function that is granted special access to the private and
protected members of a class. While typically private and protected members are
only accessible by member functions of the class or its derived classes, a
friend function bypasses this restriction. 

```cpp
class MyClass
{
    private:
        int privateData;

    public:
        MyClass(int data) : privateData(data) {}

        // Declare a friend function
        friend void displayPrivateData(MyClass obj);
};

// Definition of the friend function
void displayPrivateData(MyClass obj)
{
    printf("%d\n", obj.privateData); // Accessing privateData
}

int main()
{
    MyClass obj(100);
    displayPrivateData(obj); // Call the friend function
    return 0;
}
```
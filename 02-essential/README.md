# Essential

In C++, classes and objects are fundamental concepts of Object-Oriented
Programming (OOP), enabling the creation of modular and reusable code.

### Class

A class serves as a blueprint or a template for creating objects. It defines the
structure and behavior that objects of that class will possess. 

```Cpp
class Car
{
    public: // Public members are accessible from outside the class
        std::string color;
        int speed;

        void accelerate(int amount)
        {
            speed += amount;
        }

        void displayInfo()
        {
            printf("Color: %s, Speed: %d km/h\n", color, speed);
        }
};
```

### Object

An object is an instance of a class. When a class is instantiated (an object is
created), memory is allocated for its data members, and it can then interact
with the member functions defined in its class.

- Each object has its own set of data members, distinct from other objects of the
same class.

```Cpp
int main() {
    Car myCar; // Creating an object named 'myCar' of the Car class

    // Accessing and modifying data members using the dot operator
    myCar.color = "Red";
    myCar.speed = 0;

    // Calling member functions
    myCar.accelerate(50);
    myCar.displayInfo(); 

    Car anotherCar; // Creating another object
    anotherCar.color = "Blue";
    anotherCar.speed = 20;
    anotherCar.displayInfo(); 

    while(1)
}
```

**[Car example](App/Src/car.cpp)**

### Dynamic Allocation

Dynamic memory allocation in C++ refers to the process of allocating memory
during the runtime of a program, rather than at compile time. This is in
contrast to static or stack-based memory allocation, where memory is reserved
when the program is compiled or when a function is called, respectively.

```Cpp
    int* p_int = new int; // Allocates memory for a single integer
    int* p_array = new int[10]; // Allocates memory for an array of 10 integers

    delete p_int; // Deallocates memory for a single integer
    delete[] p_array; // Deallocates memory for an array
```

**[Dynamic example](App/Src/dynamic.cpp)**

### Variable Reference

In programming, "aliasing" primarily refers to a situation where the same memory
location or data object can be accessed or referenced using different names or
expressions. This means that changes made through one name will be visible when
accessing the data through another name, as both names ultimately refer to the
same underlying entity.

A reference variable serves as an alias or an alternative name for an existing
variable. It provides a way to refer to the same memory location as another
variable, allowing modifications through either

References are declared using the ampersand (&) symbol during initialization. For example:

```cpp
    int originalVar = 10;
    int& referenceVar = originalVar; // referenceVar is now an alias for originalVar
```

Other example:

```cpp
    int num = 234;
    int &ref_alias = num;
    int norm_alias = num;

	printf("num is %d \n", num);                // 234
	printf("ref_alias is %d \n", ref_alias);    // 234
	printf("norm_alias is %d \n", norm_alias);  // 234
        
    ref_alias++;

	printf("num is %d \n", num);                // 235
	printf("ref_alias is %d \n", ref_alias);    // 235
	printf("norm_alias is %d \n", norm_alias);  // 234
```

### Function Template

A function template in C++ is a blueprint or a generic definition for a family
of functions that can operate on different data types without requiring the code
to be rewritten for each specific type. 

- A function template begins with the `template` keyword, followed by template
parameters enclosed in angle brackets `(<>)`, and then the function's signature
and body.

- typename T: This declares T as a template type parameter, which acts as a
placeholder for any data type (e.g., int, float, double, or custom classes).
class can be used interchangeably with typename in this context.

```cpp
template <typename T>
T add(T a, T b) 
{
    return a + b;
}
```

**[Template example](App/Src/template.cpp)**

### Default Arguments

Allow specifying pre-defined values for function parameters in the function
declaration. These values are automatically used if the caller of the function
does not provide an explicit argument for that parameter.

```cpp
int  add_tripple(int a, int b, int c=0)
{
    return a+b+c;
}
```

### Pass by Value

When an argument is passed by value, a copy of the actual argument's value is
made and passed to the function.  The function operates on this copy, meaning
any modifications made to the parameter within the function do not affect the
original variable in the calling scope.

This method ensures data integrity of the original variable, as it remains unchanged.

```cpp
void incrementByValue(int num)
{
    num = num + 1; // Modifies the copy of 'num'
}
```

### Pass by Reference

When an argument is passed by reference, an alias (or reference) to the original
variable is passed to the function.  The function's formal parameter directly
refers to the same memory location as the original variable.  Any modifications
made to the parameter within the function directly affect the original variable
in the calling scope.

This method allows functions to modify the original data,
avoiding the overhead of copying large objects.

```cpp
void incrementByReference(int& num)
{
    num = num + 1; // Modifies the original 'num'
}
```

### Pass by Address

When an argument is passed by address, the memory address of the original
variable is passed to the function.  The function's formal parameter is a
pointer that stores this memory address.  To access or modify the original
variable, the pointer must be dereferenced using the * operator.

Similar to pass by reference, this method allows functions to modify the
original data. It is often used when explicit pointer manipulation is required
or when dealing with dynamic memory

```cpp
void incrementByAddress(int* numPtr)
{
    *numPtr = *numPtr + 1; // Dereferences the pointer to modify the original value
}
```

### Return by Address

It refers to a function returning the memory address (pointer) of a variable or
dynamically allocated object. This allows the caller to access or modify the
data stored at that address.

```cpp
int* createAndReturnPointer()
{
    static int value = 100; // Using static storage duration to ensure the variable exists after the function returns
    return &value; // Return the address of 'value'
}
```

or

```cpp
int* createAndReturnPointer()
{
    int* value; // Declare a pointer to an integer
    value = new int; // Dynamically allocate memory for one integer
    *value = 25; // Assign a value to the dynamically allocated integer
    return value; // Return the address of 'value'
}
```

---

### Examples

1. **[Car example](App/Src/car.cpp)**
2. **[Dynamic example](App/Src/dynamic.cpp)**
3. **[Template example](App/Src/template.cpp)**
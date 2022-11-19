Basic C [1]_
===============

.. role:: cin(code)
   :language: c

P2M3 Requirements Clarification
-------------------------------

Some students are asking if they can use other methods to implement `players` and `stock, piles`.

Please follow the requirements listed on :file:`p2.pdf` (Selected):

    ...

    Use a **circular double linked list** for the players;

    Use a **dynamic array** to handle the stock and discard piles;

    ...

C Types
-------

Type Qualifier
^^^^^^^^^^^^^^

The most commonly-used qualifier in C is the `const type qualifier`.

`Constant type qualifier` can make one variable constant and it may help in some cases.

.. code-block:: c

    const int some_magic_number = 100;
    const char *const my_str[2] = {"List1", "List2"};

You can also use the `#define directive` to define a constant:

.. code-block:: c

    #define PI 3.1415926

Scope of Variables
^^^^^^^^^^^^^^^^^^

- Global variables: defined for all functions (outside the function or :cin:`static`)

  .. warning::
  
      Never use non-constant global variables in VG151!

  .. admonition:: Further Reading: Static storage duration [2]_      
      
      The storage duration is the entire execution of the program, and the value stored in the object is initialized only **once**, prior to main function. All objects declared static and all objects with either internal or external linkage that aren't declared :cin:`_Thread_local` (since C11) have this storage duration.

- Local variables: defined only in functions

Type Classification [3]_
^^^^^^^^^^^^^^^^^^^^^^^^

The C type system consists of the following types: (excluded some types that we don't need in VG151)

- the type :cin:`void`
- basic types

  - the type :cin:`char`
  - signed integer types

    - standard: :cin:`signed char`, :cin:`short`, :cin:`int`, :cin:`long`, :cin:`long long` (since C99)

  - unsigned integer types

    - standard: :cin:`unsigned char`, :cin:`unsigned short`, :cin:`unsigned int`, :cin:`unsigned long`, :cin:`unsigned long long` (since C99)

  - floating-point types

    - real floating-point types: :cin:`float`, :cin:`double`, :cin:`long double`

- enumerated types
- derived types

  - array types
  - structure types
  - union types
  - function types
  - pointer types

.. tip:: 
    
    There is no direct ``bool`` type support in C11 standard.

Arithmetic Types
^^^^^^^^^^^^^^^^

(See `arithmetic types <https://en.cppreference.com/w/c/language/arithmetic_types>`_ for more details)

- :cin:`int x = 3;`
- :cin:`float x = 1.0;` 7 digits of precision
- :cin:`double c = 5.5;` 13 digits of precision

.. tip::

    When comparing two :cin:`double` or :cin:`float`, it's safer to allow errors.

    .. code-block:: c
        :emphasize-lines: 2,6

        #include<math.h>
        #include<limits.h>

        float a,b;
        // ...
        if(abs(a - b) <= FLT_EPSILON){
            printf("a and b are equal");
        }
    
    :c:type:`FLT_EPSILON` defined in ``limits.h`` is helpful.

Characters
^^^^^^^^^^

- Characters are enclosed in single quotes: :cin:`char a = 'a'`;
- Character are encoded using the American Standard Codes for In-formation Interchange (ASCII)
- No :cin:`string` type. A string is viewed as an array of characters.
- Strings are enclosed in double quotes. Usually a string should ended up with a char :cin:`'\0'`.
- Here are examples about how to initialize strings:

.. code-block:: c

    char c[] = "abcd";
    char c[50] = "abcd";
    char c[] = {'a','b','c','d','\0'};
    char c[5] = {'a','b','c','d','\0'};

Displaying
^^^^^^^^^^

Comparing those two code snippets:

.. code-block:: c
    :emphasize-lines: 3

    #include <stdio.h>
    int main(){
        printf("%d %f\n",7/3,7/3);
    }

.. code-block:: c
    :emphasize-lines: 3

    #include <stdio.h>
    int main(){
        printf("%d %f\n",7/3,7.0/3);
    }

- :cin:`%d` means a signed integer here and :cin:`%f` means a floating-point number here.
- The compiler would take ``7/3`` as an integer, and take ``7.0/3`` as a floating-point number.

.. tip::

    You can use suffix, if present, is one of ``f``, ``l``, ``F``, ``L`` to define a "floating-point literal".

    - ``f``, ``F`` defines :cin:`float`
    - ``l``, ``L`` defines :cin:`long double`

    Example:

    .. code-block:: c

        printf("%f\n",7f/3);
    
Type Casting
^^^^^^^^^^^^

- Basic syntax: :cin:`(type) variable`
- :cin:`char a = (char) 100.111;` Then :cin:`a` becomes :cin:`'d'`
- Pay attention to the size and precision especially when dealing with mathematical operations.

Structures
----------

Basic :cin:`struct` usage:

.. code-block:: c

    #include <stdio.h> 

    typedef struct _person {
        char* name;
        int age;
    } person;

    int main() {
        person al={"albert",32};
        person gil;
        gil.name="gilbert";
        gil.age=23;
        struct _person so={"sophie",56};
        printf("%s %d\n",al.name, al.age);
        printf("%s %d\n",gil.name, gil.age);
        printf("%s %d\n",so.name, so.age);
    }

Combine with functions:

.. code-block:: c

    #include<stdio.h>
    typedef struct _person {
        char* name;
        int age;
    } person;

    person older(person p,int a);

    int main() {
        person al = {"albert",32};
        al = older(al,10);
        printf("%s %d\n", al.name, al.age);
    }

    person older(person p,int a) {
        printf("%s %d\n", p.name, p.age);
        p.age += a;
        return p;// A C function can only have one output.
    }

Control Statements
------------------

Basics on Conditional Statements
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- **No boolean type, 0 means False, anything else True**
- Boolean evaluation: :cin:`<, <=, >, >=, ==, !=`
- Not: :cin:`!`, short-circuit operators: and: :cin:`&&`, or: :cin:`||`
- Bit operations: :cin:`&, |, ^`

Conditional Ternary Operator
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

(Fewer lines, but not recommended in exams)

.. code-block:: c

    condition ? expression1 : expression2

Example:

.. code-block:: c

    #define MAX(a,b) a>=b ? a : b

``if`` and ``switch``
^^^^^^^^^^^^^^^^^^^^^

.. code-block:: c

    if(x == 0) printf("zero\n");
    else if(x == 1 || x == 2) printf("one or two\n");
    else printf("not zero or one\n");

    switch(x) {
        case 0:
            printf("zero\n");
            break; // Don't forget the break!!!
        case 1:
        case 2:
            printf("one or two\n");
            break;
        default:
            printf("not zero or one or two\n");
            break;
    }

Random numbers
^^^^^^^^^^^^^^

When generating random numbers, usually we should add these two lines:

.. code-block:: c

    #include <stdlib.h>
    #include <time.h>

To make the random number “random”, we could use :cin:`srand(time(NULL))`.

:cin:`srand()` seeds the pseudo-random number generator used by :cin:`rand()`.

If :cin:`rand()` is used before any calls to :cin:`srand()`, :cin:`rand()` behaves as if it was seeded with :cin:`srand(1)`.

Each time :cin:`rand()` is seeded with :cin:`srand()`, it must produce the same sequence of values.

Pseudo-random integer value between 0 and :cin:`RAND_MAX`, inclusive.

Loops
^^^^^

``while`` and ``do ... while`` loops
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: c

    int i = 0;
    do {printf("%d",i);} while(i++ < 1);
    i = 0;
    do {printf("%d",i);} while(++i < 1);
    i = 0;
    while (i++ < 1) {printf("%d",i);}
    i = 0;
    while (++i < 1) {printf("%d",i);}

``for`` loops
~~~~~~~~~~~~~

.. code-block:: c

    for(i = 0; i < n; i++)
        printf("%d ",i);
    i = 0;
    for(; i < n; i++)
        printf("%d ",i);
    for(i = 0; i < n;){
        printf("%d ",i);
        i++;
    }
    for(i = 0; i<n;)
        printf("%d ",i++);

``break`` and ``continue``
**************************

- Early exit of a loop: :cin:`break`
- Skip to the next loop iteration: :cin:`continue`

Initialization [4]_
-------------------

`(Removed some advanced usage)`

Initialization is quite complicated in C. (of course less complicated comparing to C++)

A declaration of an object may provide its initial value through the process known as initialization.

For each declarator, the initializer, if not omitted, may be one of the following:

- ``= expression``	
- ``= { initializer-list }``

where ``initializer-list`` is a `non-empty comma-separated list of initializers` (with an optional trailing comma), where each initializer has one of three possible forms:

- ``expression``
- ``{ initializer-list }``

Explicit Initialization
^^^^^^^^^^^^^^^^^^^^^^^
Examples:

.. code-block:: c

    int y[4][3] = { // array of 4 arrays of 3 ints each (4x3 matrix)
        { 1 },      // row 0 initialized to {1, 0, 0}
        { 0, 1 },   // row 1 initialized to {0, 1, 0}
        { [2]=1 },  // row 2 initialized to {0, 0, 1} (advanced usage)
    };              // row 3 initialized to {0, 0, 0}

    char str[3] = "abc"; // str has type char[3] and holds 'a', 'b', 'c'
    char str[] = "abc"; // str has type char[4] and holds 'a', 'b', 'c', '\0'

    int a[3] = {0}; // valid C and C++ way to zero-out a block-scope array
    int a[3] = {}; // valid C++ way to zero-out a block-scope array; valid in C since C23 (not valid in C11)

    const char *const my_str[] = {"List1", "List2"}; // my_str is a const array of string

    struct point {double x,y,z;} p = {1.2, 1.3}; // p.x=1.2, p.y=1.3, p.z=0.0
    struct point {double x,y,z;} p = {.y=1.3}; // p.x=0.0, p.y=1.3, p.z=0.0

Implicit Initialization
^^^^^^^^^^^^^^^^^^^^^^^

If an initializer is not provided:

- objects with :cin:`static` storage duration are empty-initialized
- other objects are initialized to `indeterminate values`

For example, consider the result of the following code:

.. code-block:: c

    #include <stdio.h>

    int glb_array2[10];

    int main(){
        int local_array[10];
        static int glb_array1[10];
        printf("%d\n", local_array[0]);
        printf("%d\n", glb_array1[0]);
        printf("%d\n", glb_array2[0]);
    }

The result would be:

.. code-block:: bash

    1826935528
    0
    0

Apparently the first result is undetermined.

It's a good habit to initialize variables when declaring them.

Dynamically allocate a 2D array [5]_
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Like this:

.. code-block:: c
    
    int (*arr)[M] = NULL;
    arr = malloc(sizeof(int[N][M]));

:cin:`arr` is pointer to :cin:`int[M]`.

Use like :cin:`arr[0][M-1];`.

And :cin:`free(arr);`.

Good Luck
---------

Hope you can do well!

.. [1] VG151 Mid2 Big RC Part 3, 2021. Jiache, Zhang.

.. [2] C Reference: Storage Duration. https://en.cppreference.com/w/c/language/storage_duration

.. [3] C Reference: Type. https://en.cppreference.com/w/c/language/type

.. [4] C Reference: Initialization. https://en.cppreference.com/w/c/language/initialization

.. [5] C Reference: Malloc a 2d array in c. https://stackoverflow.com/questions/36890624/malloc-a-2d-array-in-c

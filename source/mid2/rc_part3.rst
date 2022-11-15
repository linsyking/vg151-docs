Basic C [1]_
===============

.. role:: cin(code)
   :language: c

C Types
-------

Scope of Variables
^^^^^^^^^^^^^^^^^^

- Constant variables (make it easier to understand your code)

  .. code-block:: c
  
      const int some_magic_number = 100;
      const char *const my_str[2] = {"List1", "List2"};

- Global variables: defined for all functions (outside the function or :cin:`static`)

  .. warning::
  
      Never use non-constant global variables in VG151!

- Local variables: defined only in functions

Type Classification [2]_
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
        :linenos:
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
- Strings are enclosed in double quotes. Usually a string shouldended up with a char :cin:`'\0'`.
- Here are examples about how toinitialize strings:

.. code-block:: c
    :linenos:

    char c[] = "abcd";
    char c[50] = "abcd";
    char c[] = {'a','b','c','d','\0'};
    char c[5] = {'a','b','c','d','\0'};

Displaying
^^^^^^^^^^

Comparing those two code snippets:

.. code-block:: c
    :linenos:
    :emphasize-lines: 3

    #include <stdio.h>
    int main(){
        printf("%d %f\n",7/3,7/3);
    }

.. code-block:: c
    :linenos:
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
- Pay attention to the size and precision especialy when dealing with mathematical operations.

Structures
----------

Basic ``struct`` usage:

.. code-block:: c
    :linenos:

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
    :linenos:

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
- Not:!, short-circuit operators: and: :cin:`&&`, or: :cin:`||`
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
    :linenos:

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
***************************************

.. code-block:: c
    :linenos:

    int i = 0;
    do {printf("%d",i);} while(i++ < 1);
    i = 0;
    do {printf("%d",i);} while(++i < 1);
    i = 0;
    while (i++ < 1) {printf("%d",i);}
    i = 0;
    while (++i < 1) {printf("%d",i);}

``for`` loops
*************

.. code-block:: c
    :linenos:

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

Good Luck
---------

Hope you can do well!

References
----------

.. [1] VG151 Mid2 RC, 2021. Jiache, Zhang.

.. [2] C Refrence. https://en.cppreference.com/w/c/language/type


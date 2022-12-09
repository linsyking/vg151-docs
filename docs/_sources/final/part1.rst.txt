Review: Homework and Labs [1]_
==============================

.. role:: cpp(code)
  :language: cpp

Homework
--------

h7
^^^^

Ex3. File I/O in C++
********************

- File, string, standard input/output can all be converted into stream
- Similar to ``FILE*`` in C
- **DO NOT** forget to check whether the files are correctly opened

.. code-block:: cpp

    #include <fstream>

    ofstream output("result.txt");
    ifstream input("matrices.txt");
    if(!output.is_open() || !input.is_open()) return;

.. admonition:: Think

    **How to read a line that contains numbers separated by spaces?**

    One way is to take the advantages of:

    - :cpp:`std::getline`
    - :cpp:`std::istringstream`

    .. code-block:: cpp

        // Read a line from input. input can be a file or standard input.

        std::string line;
        std::getline(input, line);
        // Now line is one line
        std::istringstream iss(line);
        
        // Read numbers from iss
        while(iss >> num) {
            // Do something with num
        }

.. admonition:: Think

    How to detect input errors?

    For example, if we use :cpp:`cin>>a;` where ``a`` is an :cpp:`int`, but the real input is not an integer.

Ex4. Basic Programming
**********************

.. math:: 
    
    \begin{cases}
        u_0 = a\\
        u_{i+1} =
        \begin{cases}
            \frac{1}{2}u_i, \quad &\text{if $u_i$ is even}\\
            3_{u_i}+1, &\text{if $u_i$ is odd}
        \end{cases} 
    \end{cases}

- Basic logic questions
- Think about `Fibonacci` sequence. How to find the :math:`n`-th Fibonacci number?

.. hint::
    
    How to optimize the following recursion function?

    .. code-block:: cpp

        long findn(long a) {
            if (a == 1) return 0;
            if (a % 2) {
                return findn(3 * a + 1) + 1;
            } else {
                return findn(a >> 1) + 1;
            }
        }
    
    **Solution.** We can use `tail recursion` to optimize it.

    .. code-block:: cpp
            
        long findn(long a, long cnt) {
            if (a == 1) return cnt;
            if (a % 2) {
                return findn(3 * a + 1, cnt + 1);
            } else {
                return findn(a >> 1, cnt + 1);
            }
        }    

Ex5. From C to C++
******************

Here are some questions you should think:

- What is `class` in C++?
- What is `poly-morphism` in C++?
- What is `OOP`?
- What are the three characteristics of OOP?
- What is `abstract class` in C++?
- What is `virtual function` in C++? What is `virtual destructor` and when to use it?
  
    See `this answer <https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors>`_.

- What are the common containers in STL? How to use them?

**A Class is a user defined data-type which has data members and member functions.**

.. literalinclude:: ex5.cpp
    :caption: ex5.cpp
    :language: c++

h8
^^^^

Ex1. Containers
***************

- Basic C++ Containers library & Data structure
  
  Make full use of `cppreference <http://cppreference.com/>`_.

- Parameter ``T`` inside ``<>`` is called `template parameter`, deduced when compilation
- :cpp:`std::array<T, N>`: static contiguous array
- :cpp:`std::vector<T>`: dynamic contiguous array
- :cpp:`std::stack<T>`: adapts a container to provide stack (LIFO data structure)
- :cpp:`std::queue<T>`: adapts a container to provide queue (FIFO data structure)

You should know the basic operations of those containers.

.. literalinclude:: ex1.cpp
    :caption: ex1.cpp
    :language: c++

Ex2. Class Implementation
*************************

- Basic inheritance & polymorphism
- Basic drawing in OpenGL
- Draw hierarchy diagram

Ex3. Classes and OpenGL
***********************

- Basic animation in OpenGL
- Draw different figures in OpenGL

  - Rectangle
  - Triangle
  - Circle
  - Line
  - Polynomial

- Combination of classes

Lab
------

l9
^^^^

- What is `stack`?
- What is Postfix Expression?
- How to use `stack` and implement the Shunting Yard algorithm

  - :cpp:`stack.push()`
  - :cpp:`stack.pop()`
  - :cpp:`stack.top()`
  - :cpp:`stack.empty()`

l10
^^^^

- Basic class design (`mandatory`)
  
  - Methods
  - Attributes
  - Hierarchy (`public`, `protected`, `private`)
  - Abstract class (virtual functions)

- Some design patterns (`advanced`)
  
  - `Singleton`
  - `Factory Method`
  - `Observer`
  - `Adapter`

.. warning::

    Avoid diamond structure in class design

    (Solutions: See :ref:`diamond_sol`)

.. [1] Qinzhe, Yang. ENGR1510J Final RC

C Questions [1]_
================

.. role:: cin(code)
   :language: c

.. role:: bash(code)
   :language: bash

Guide for ``e2_r``
------------------

- I'm only choosing part of the questions to discuss.
- Those are NOT standard answers. As long as your own answer is correct and complete it's fine.
- It's NO USE reciting my sample answer and sample codes. You need to understand and remember the theory so that you can explain in your own words.
- If you haven't done ``e2_r`` on your own I suggest you do it before you look into my answer and codes in detail. 

Basic C Questions
-----------------

- What is a macro?

  Macros are defined by using :cin:`#define`. They are handled first when compiling.
  
  We usually use macros to define constant global variables and header guards.

- What are the five main data types?

  :cin:`int char float double void`

  (C does not have :cin:`bool`)

- What should upper-cases variable names reserved for?

  Constant variables (including macros)

- What is the length of a char?

  8 bits/1 byte.
  
  For some other data types(such as int), they depend on the computer and OS.

- Can you list and use all the shorthand operators?

  .. code-block:: c
  
      int a = 0;
      a += 1;
      a -= 1;
      a *= 1;
      a /= 1;
      a++;
      a--;
  
- Should :cin:`goto` be used and why?

  No. :cin:`goto` makes your code messy. Codes with :cin:`goto` are hard to read, understand and debug.

  What's more, using :cin:`goto` breaks code quality and means deduction!

 
- How to use the conditional ternary operator?

  .. code-block:: c

      condition ? expression1 : expression2
      int a = 1; int b = 2;
      int bigger_number = (a >= b ? a : b);
  
- What is the difference between switch in MATLAB and in C?

  :cin:`default` vs. ``otherwise``
  
  Effect of :cin:`break` at the end of each case. (usually necessary)
  
- Why should for loops be preferred over while loops?

  :cin:`for` loops are easier to write and read, especially when the loop needs a counter.

- Should global variables be used or not?

  No. Global variables are not safe since they can be accessed every where.
  
  They also makes debugging harder because it's difficult to locate where this variable is changed and go wrong.

  Also please think of code quality deductions.

- What is a pointer?

  Pointer is special type that points to the address of a memory, in which another variable is stored.

- Given a pointer on a structure, how to access the different fields of the structure?

  .. code-block:: c

      Card* c = ...   //Initialize
      c->rank = 1;    //Preferred
      (*c).rank = 1;  //OK

- What is dynamic memory allocation?

  It's asking computer for a block of memory, whose lifespan is controlled by us. (Not auto freed when leaving a block.)
  
  The size of that data structure (in dynamic memory) can be defined and changed in runtime. (while size of static data structures are defined when compiling and can not be changed.)
  
- For each ``malloc`` or ``calloc`` function in a program what function should also appear?

  :cin:`free();` (Code quality!)
  
  .. tip::
    
      According to the latest version of ``code_quality.pdf``, you should also check the return value of :c:func:`malloc` and :c:func:`calloc`.

- How to go through an array using pointers?

  .. code-block:: c
      :emphasize-lines: 2

      int a[] = {1, 2, 3};
      printf("%d %d %d", *a, *(a + 1), *(a + 2));
  
  .. tip::

      :cin:`a[b]` is equivalent to :cin:`*(a + b)` and :cin:`*(b + a)` and :cin:`b[a]` (never use this).

  .. admonition:: Think
  
      What is the equivalent representation for :cin:`a[b][c]`?

- Can you solve all the questions at the end of Chapter 11?

  - How to use external libraries?

    .. code-block:: c
        :caption: main.c

        #include <math.h>
        // other code

    Then, :bash:`gcc main.c -lm`.

  - How to write a ``Makefile/CMakeLists.txt``?

    Turn to the `materials repository <https://focs.ji.sjtu.edu.cn/git/ENGR151-22/materials/src/branch/master/templates>`_ to see a simple template!

    .. tip::

        Since we don't have strict rules on which one you should choose between `Makefile` or `CMakeLists.txt`, you only need to know how to write one of them.

A Simple Investigation Game
---------------------------

Ex2. Task 1
^^^^^^^^^^^

    Define a structure composed of the fields suspect, location, and weapon.

.. code-block:: c
    :linenos:

    typedef struct _scene{
        int suspect;
        int location;
        int weapon;
    } scene;
    
    const char *const sus_name = {"Butcher","Hairdresser","Salesman","Banker","Student"};
    const char *const loc_name = {"lounge","lobby","reception","restaurant","coffee shop"};
    const char *const weap_name = {"hammer","scissors","knife","poison","candlestick"};

Ex2. Task 2
^^^^^^^^^^^

    Write a function which selects a random suspect, a random location, and a random weapon.

The function does not have return value, so we need to give it a pointer.    

Also, when passing large variables (such as structures and arrays) to functions, using pointers saves time and memory to copy the variable.

.. code-block:: c
    :linenos:

    void generateScene(scene* answer){
        srand((unsigned)time(NULL));
        answer->suspect = rand()%5 + 1;
        answer->location = rand()%5 + 1;
        answer->weapon = rand()%5 + 1;
    }

Ex2. Task 3, 4
^^^^^^^^^^^^^^
    The game is then composed of rounds where the user constructs guesses, which are assessed by the program.

    Use dynamic memory allocation to save each step taken by the player and print the whole list of guesses.

.. code-block:: c
    :linenos:

    int compareGuess(scene *answer, scene *guess) {
        int correct = 0;
        if (answer->suspect == guess->suspect) correct++;
        if (answer->location == guess->location) correct++;
        if (answer->weapon == guess->weapon) correct++;
        return correct;
    }

    int    i;
    scene *guess, answer;
    int    flag = 0;
    guess       = malloc(0);
    generateScene(answer);

    for (i = 0; i < 10; i++) {
        guess = (scene*)realloc(guess,(i+1)*sizeof(scene)));
        int suspect, location, weapon;
        scanf("%d%d%d", &suspect, &location, &weapon);
        (guess + i)->suspect  = suspect;
        (guess + i)->location = location;
        (guess + i)->weapon   = weapon;
        int correct_num       = compareGuess(answer, guess + i);
        printf("You made %d correct guess(es)\n", correct_num);
        if (correct_num == 3) {
            flag = 1;
            break;
        }
    }

    if (flag) {
        printf("Congratulations...");
    } else {
        printf("Game over...");
    }
    for (int j = 0; j < i; j++) {
        printf("%d. You suspected the %s...", j + 1, sus_name[(guess + j)->suspect]);
    }
    printf("Conclusion: the %s...", sus_name[answer->suspect]);
    free(guess);



The Students' Grades
--------------------

Ex3. Task 1
^^^^^^^^^^^

    Write a structure composed of three fields: name, grades and mean.

Students have the same amount of scores, so we'd better use static arrays to save efforts...

.. code-block:: c
    :linenos:

    typedef struct _student{
        char  name[10];
        int   score[5];
        float mean;
    } student;

Ex3. Task 2
^^^^^^^^^^^

    Write a function called avg that computes the mean grade for each student.

.. code-block:: c
    :linenos:

    void avg(student* stu){
        float sum = 0;
        for(int i = 0; i < 5; i++){
            sum += stu->score[i];
        }
        stu->mean = sum/5;
    }

Ex3. Task 3
^^^^^^^^^^^

    Write a function which writes in a file called ``final_grades.txt`` the name, grades, and mean for each student.

Here I designed a function to write a single student into a arbitrary file. I will call this function in a loop.

.. code-block:: c
    :linenos:

    void writeFile(student* stu, FILE* fd){
        fprintf(fd,"%s;",stu->name);
        for(int i = 0; i < 5; i++){
            fprintf(fd," %d",stu->score[i]);
        }
        fprintf(fd,"; %.1f;\n",stu->mean); //One decimal
    }

Ex3. Task 4
^^^^^^^^^^^

    Write a function called best that returns the name of the student with the highest mean.

Dealing with arrays is always annoying. Why I use ``malloc`` here? Any alternatives?

.. code-block:: c
    :linenos:

    char* best(student* stu,int num){
        char* name = malloc(10*sizeof(char));
        float high = 0;
        for(int i = 0; i < num; i++){
            if ((stu+i)->mean > high){
                high = (stu+i)->mean;
                strcpy(name,(stu+i)->name);
            }
        }
        return name;
    }

.. warning::

    - Arrays can only pass in and out functions by pointers.
    - Returning the address of local variables can cause undefined behaviors.

    Wrong example:

    .. code-block:: c

        char* ArrayPtr(){
            char str[] = "This is a string";
            return str;
        }

    Alternatives:

    - Pass in a pointer and modify it.(:cin:`strcpy()` works the same way.)

      .. code-block:: c

          void ArrayPtr(char* str){
              char temp[] = "This is a string";
              strcpy(str,temp);
          }

    - Pass in a pointer and modify it. Then return it.(:cin:`realloc()` works the same way.)

      .. code-block:: c

          char* ArrayPtr(char* str){
              char temp[] = "This is a string";
              strcpy(str,temp);
              return str;
          }

Ex3. Task 5
^^^^^^^^^^^

    Read the file ``grades.txt`` and load the different fields for each student.

.. code-block:: c
    :linenos:

    int main() {
        FILE    *input  = fopen("grades.txt", "r");
        FILE    *output = fopen("final_grades.txt", "w");
        char     line[100];
        int      i   = 0;
        student *stu = malloc(0);

        while (fgets(line, 100, input) != NULL)  // Operate until EOF
        {
            stu        = (student *)realloc(stu, (i + 1) * sizeof(student));
            char *name = strtok(line, ";");  // Separate the name out
            strcpy((stu + i)->name, name);
            for (int j = 0; j < 5; j++) {
                int score           = atoi(strtok(NULL, " "));  // Separate each score
                (stu + i)->score[j] = score;
            }
            avg(stu + i);
            writeFile(stu + i, output);
            i++;
        }

        char *best_name = best(stu, i);
        printf("The student with best score is %s\n", best_name);
        // DO NOT forget the following part!!!
        free(best_name);  // This was allocated in function best()
        free(stu);
        fclose(input);
        fclose(output);
    }


Other Suggestions
-----------------

Mid 2 is very likely to be related to pointers and data structures that need it.

I recommend you to review how to use pointers and review related data structures, like :ref:`tree-structure` and :ref:`doubly-linked-list`.

If you have time, I also recommend you to implement some operations on doubly linked lists and trees, like `insert`, `delete`, `combine`.

For memory management, my Lab 7 :ref:`gc-easy` and :ref:`reference-counting` is a good material.

When you are lost with pointers, draw diagrams like :ref:`after-simulation`. It will help you understand what is happening.

.. tip::

    In the exam, please think of the exercise as a whole. Functions written in the first question can be helpful to the following ones.


.. tip::
    
    In the exam, please first read through all the exercises and make sure you start from the easiest one rather than from the start.

    This works for both Part 1 and Part 2.

.. tip::

    Review the homework carefullt. Part 1 will have a homework question.

Good Luck
---------

Hope you can do well!

.. [1] VG151 Mid2 Big RC Part 6, 2021. Jiache, Zhang.

ENGR151 Lab 7
=============

Trees

---------

.. note::

   I am still writing this page.

We will talk about trees in this lab.

Group Presentation
------------------

* What's the difference between ``Type **`` and ``Type *``? Why use ``Type **`` in homework?
* How to use valgrind to check memory leak?
* What is a dynamic array, and what are the similarities and differences compared to h6 ex5?
* What is a double linked list, and what are the similarities and differences compared to h6 ex7?

Homework Feedback
-----------------

Generally, you did a great job! However, remember the following things:

#. **Always** indent and format your code. You can use code formatters to do that easily.
#. Push to ``master`` branch for your final submission. Don't forget to release.
#. Follow the code quality rules (we'll talk about that in detail later)

.. warning::

   This lab is quite difficult. If I don't make something clear, please forgive me.

Tree Structure
--------------

What is tree?
^^^^^^^^^^^^^

   In computer science, a tree is a widely used abstract data type that represents a hierarchical tree structure with a set of connected nodes. Each node in the tree can be connected to many children (depending on the type of tree), but must be connected to exactly one parent, except for the root node, which has no parent.

   -- `Wikipedia <https://en.wikipedia.org/wiki/Tree_(data_structure)>`_

.. figure:: /_static/l7/tree.png
   :align: right
   :height: 230
   :width: 200

   A tree with *data* integers

Basic Concepts
~~~~~~~~~~~~~~

A **node** is a structure which may contain data and connections to other nodes. It forms the most basic elements in a tree.

The **root node** is the node that has no parent (the ancestor of all the other nodes in a tree).

The **leaf node** of a tree is the node that doesn't haven any child.

A **binary tree** is a special tree: every node have at most 2 children nodes.

.. figure:: /_static/l7/binary_tree.png
   :align: right
   :height: 220
   :width: 200

   A binary tree

.. note::

   Tree is an abstract data structure, which means that it is not necessarily related to a specific programming language. You can implement tree in any `Turing-Complete <https://en.wikipedia.org/wiki/Turing_completeness>`_ language.

Why trees?
^^^^^^^^^^

Trees are good because it can represent many data in our real life naturally. 

What does tree look like in C?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In this part, we will focus on the implementations in C.

Why pointers are involved?
~~~~~~~~~~~~~~~~~~~~~~~~~~

Pointers are helpful to writing "compound data structure with self-referring" (a self-made word).

**Examples**

* Linked list
* Tree
* Graph (more general than tree)
* Recursion

.. admonition:: Think

   Why can recursion also be related to pointers?

.. admonition:: Think

   What's the common things among those examples?

.. tip::

   Think about what their "nodes" are. Write out the concrete implementations.

Here I give two exmaples. Note that the data can be any data type, I use ``int`` only for demonstration.

**Linked list**

.. code-block:: c
    :linenos:
    :emphasize-lines: 4,6

    typedef struct _node{
        int data;
        // other staffs
        struct _node *next;
        // if double linked list
        struct _node *prev;
    } node;

**(Binary) Tree**

.. code-block:: c
    :linenos:
    :emphasize-lines: 4,5

    typedef struct _node{
        int data;
        // other staffs
        struct _node *left;
        struct _node *right;
    } node;


Review of the Game
------------------

In the last lab, we have a fun game which simulates a FIFA world cup.

However, the method we used last time is not very easy to understand (using array to represent the teams, etc..).

Now we have learned tree. Is it useful in this game?

Drone Setup Checking
--------------------

In the last lab we did this in a hurry. Let's check if everyone has done it!

.. warning::

   If you didn't set up :program:`drone` for your projects, you will not be able to see the compilation results, code quality feedback, etc.. As a result, you may get deductions on your projects.

Explanation of the checks
^^^^^^^^^^^^^^^^^^^^^^^^^

There are many checks we enabled on the server.

Code Check
~~~~~~~~~~

* :program:`clang-tidy` with custom checks. The checks could be found on the `materials repo <https://focs.ji.sjtu.edu.cn/git/ENGR151-22/materials/src/branch/drone>`_.
* Please follow :file:`code_quality.pdf` on canvas.
* Not following it will lead to deductions on exams/projects.

.. warning::

   Please read the code quality document now (download it from Canvas to get the latest version).

Runtime Check
~~~~~~~~~~~~~

This is the check mainly for your p2.

You have to learn how to manage memory by yourself in p2. (although in the real world it's **not recommended** to manage the memory by yourself)

We use :program:`msan, asan, lsan, ubsan` to perform the checks. The feedback is very clear. It shows the trackbacks and tell you where the problem is in your source files.

Alternative memory checking tools are :program:`valgrind` (not available on Windows). For Windows users, you can either try searching tools online or use WSL.

Attendence Quiz
---------------

Please do the attendence quiz on Canvas now.

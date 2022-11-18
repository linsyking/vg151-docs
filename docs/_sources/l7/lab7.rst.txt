ENGR151 Lab 7: Trees
====================

Group Presentation
------------------

* What's the difference between ``Type **`` and ``Type *``? Why use ``Type **`` in homework?
* How to use valgrind to check memory leak?
* What is a dynamic array, and what are the similarities and differences compared to h6 ex5?
* What is a doubly linked list, and what are the similarities and differences compared to h6 ex7?

Homework Feedback
-----------------

Generally, you did a great job! However, remember the following things:

#. **Always** indent and format your code. You can use code formatters to do that easily.
#. Push to ``master`` branch for your final submission. Don't forget to release.
#. Follow the code quality rules (we'll talk about that in detail later)

.. warning::

   This lab is quite difficult. If I don't make something clear, please forgive me.

.. _tree-structure:

Tree Structure
--------------

What is tree?
^^^^^^^^^^^^^

   In computer science, a tree is a widely used abstract data type that represents a hierarchical tree structure with a set of connected nodes. Each node in the tree can be connected to many children (depending on the type of tree), but must be connected to exactly one parent, except for the root node, which has no parent.

   -- `Wikipedia <https://en.wikipedia.org/wiki/Tree_(data_structure)>`_

.. figure:: /_static/l7/tree.png
   :height: 230
   :width: 200

   A tree with data integers

Basic Concepts
~~~~~~~~~~~~~~

A **node** is a structure which may contain data and connections to other nodes. It forms the most basic elements in a tree.

The **root node** is the node that has no parent (the ancestor of all the other nodes in a tree).

The **leaf node** of a tree is the node that doesn't haven any child.

A **binary tree** is a special tree: every node have at most 2 children nodes.

.. figure:: /_static/l7/binary_tree.png
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

Here I give two examples. Note that the data can be any data type, I use ``int`` only for demonstration.

.. _doubly-linked-list:

Doubly Linked list
**********************

.. code-block:: c
    :emphasize-lines: 4,5

    typedef struct _node{
        int data;
        // other staffs
        struct _node *next;
        struct _node *prev;
    } node;

Binary Tree
***********

.. code-block:: c
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

We use *Post Order* DFS to traverse all the nodes in the tree.

.. _gc-easy:

Garbage Collection: Easy Version
--------------------------------

After we simulate the whole game, we have to carefully collect all the "garbages" generated through the game. (Memory Management)

We will take a look at a simple example. In this example, we only have 2 countries and 3 nodes.

After we finish the game, all the nodes have set the ``country`` variable.

In the simple version, every data in the node is not a pointer. It is directly the ``Country`` data type. Hence, many countries are copied. (eg. Node 1 and Node 2 have the same country, but they don't share the same memory)

.. code-block:: c
   :emphasize-lines: 3

   struct Node_t {
        // data
        Country country;
        // children
        Node *left;
        Node *right;
    };

.. uml::
   :align: center
   :width: 12cm
   :caption: Simple Node

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R1c <<Rectangle>> #yellow {
        object "Country" as Country1c
        Country1c : name = "UFO"
        Country1c : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #yellow {
        object "Country" as Country2
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : data
    node1 : *left
    node1 : *right

    node1::data -> R1c

    object "Node 2" as node2
    node2 : data
    node2 : *left
    node2 : *right

    node2::data -> R1

    object "Node 3" as node3
    node3 : data
    node3 : *left
    node3 : *right

    node3::data -> R2

    node1::left --> node2
    node1::right --> node3

The :c:func:`Node_create` function is defined by:

.. code-block:: c
   
   Node *Node_create() {
        Node   *new_node = malloc(sizeof(Node));
        if (!new_code){
            exit(-1);
        }
        Country s;
        s.rank            = NON;
        new_node->country = s;
        new_node->left    = NULL;
        new_node->right   = NULL;
        return new_node;
    }

.. tip::

    Always check the return value of :c:func:`malloc`!

The destroy function should be:

.. code-block:: c

    void tree_destroy(Node *root) {
        // release memory
        if (root == NULL) {
            return;
        } else {
            tree_destroy(root->left);
            tree_destroy(root->right);
            free(root);
        }
    }

As you can see, we don't need to delete any other resources.

When we are destroying the tree, there are three steps:

Step 1
^^^^^^

We first delete the left child. When we delete Node 2, its country will be automatically destroyed. 

.. uml::
   :align: center
   :width: 12cm
   :caption: Step 1

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #grey {
        object "Country" as Country1 #grey
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R1c <<Rectangle>> #yellow {
        object "Country" as Country1c
        Country1c : name = "UFO"
        Country1c : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #yellow {
        object "Country" as Country2
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : data
    node1 : *left
    node1 : *right

    node1::data -> R1c

    object "Node 2" as node2 #grey
    node2 : data
    node2 : *left
    node2 : *right

    node2::data -> R1

    object "Node 3" as node3
    node3 : data
    node3 : *left
    node3 : *right

    node3::data -> R2

    node1::left --> node2
    node1::right --> node3


Step 2
^^^^^^

We then delete the right child. When we delete Node 3, its country will also be automatically destroyed. 

.. uml::
   :align: center
   :width: 12cm
   :caption: Step 2

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #grey {
        object "Country" as Country1 #grey
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R1c <<Rectangle>> #yellow {
        object "Country" as Country1c
        Country1c : name = "UFO"
        Country1c : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #grey {
        object "Country" as Country2 #grey
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : data
    node1 : *left
    node1 : *right

    node1::data -> R1c

    object "Node 2" as node2 #grey
    node2 : data
    node2 : *left
    node2 : *right

    node2::data -> R1

    object "Node 3" as node3 #grey
    node3 : data
    node3 : *left
    node3 : *right

    node3::data -> R2

    node1::left --> node2
    node1::right --> node3

Step 3
^^^^^^

Finally we destroy all the objects. 

.. uml::
   :align: center
   :width: 12cm
   :caption: Step 3

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #grey {
        object "Country" as Country1 #grey
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R1c <<Rectangle>> #grey {
        object "Country" as Country1c #grey
        Country1c : name = "UFO"
        Country1c : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #grey {
        object "Country" as Country2 #grey
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1 #grey
    node1 : data
    node1 : *left
    node1 : *right

    node1::data -> R1c

    object "Node 2" as node2 #grey
    node2 : data
    node2 : *left
    node2 : *right

    node2::data -> R1

    object "Node 3" as node3 #grey
    node3 : data
    node3 : *left
    node3 : *right

    node3::data -> R2

    node1::left --> node2
    node1::right --> node3

.. admonition:: Think

    What is the disadvantages of this simple method?

.. _reference-counting:

Reference counting
------------------

In the difficult version, we define a new ``Country_proxy`` type by:

.. code-block:: c

    typedef struct {
        Country *proxy;
        unsigned int counter;
    } Country_proxy;

And then define the ``Node`` by:

.. code-block:: c
    :emphasize-lines: 3

    struct Node_t {
        // data
        Country_proxy *country_proxy;
        // children
        Node *left;
        Node *right;
    };

Using pointers to store country is actually better when ``Country`` type is a large structure. It will cost less memory.

.. admonition:: Think

    Is it possible to use ``Country *country`` in the definition of ``Node`` to implement the simulation. And why?

    (Definitely `yes`! But some solutions may need the special property of this tree and cannot generalize)

Here I want to introduce a general solution to those kinds of problems.

The key trick is to use a `reference counter` to track the number of references to a resource.

Originally, we directly save country inside node:

.. uml::
   :align: center
   :width: 5cm
   :caption: Original Node

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    object "Node" as node1
    node1 : data
    node1 : *left
    node1 : *right

    node1::data -> R1

Now we add a "proxy" (or you can call it a counter) between them:

.. uml::
   :align: center
   :width: 7cm
   :caption: New Node

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    object "Proxy" as proxy1 #orange
    proxy1 : *country
    proxy1 : counter = 1

    object "Node" as node1
    node1 : *proxy
    node1 : *left
    node1 : *right

    node1::proxy -> proxy1
    proxy1::country -> R1

The ``counter`` in the proxy will remember the number of references. (In the above example, it's 1 because only one node want to point to the resource)

And, **one resource will only have one proxy**.

When the proxy found that its counter is 0, it will automatically delete **the resource it points to and also itself**. It is safe because there are no other references.

.. uml::
   :align: center
   :width: 7cm
   :caption: Proxy is deleted

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #grey {
        object "Country" as Country1 #grey
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    object "Proxy" as proxy1 #grey
    proxy1 : *country
    proxy1 : counter = 0

    object "Node" as node1
    node1 : *proxy
    node1 : *left
    node1 : *right

    node1::proxy .> proxy1
    proxy1::country -> R1

Now let's try to use this in the example we talked about in the simple version.

After simulation:

.. _after-simulation:

.. uml::
   :align: center
   :width: 10cm
   :caption: After Simulation

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #yellow {
        object "Country" as Country2
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : *proxy
    node1 : *left
    node1 : *right

    object "Node 2" as node2
    node2 : *proxy
    node2 : *left
    node2 : *right


    object "Node 3" as node3
    node3 : *proxy
    node3 : *left
    node3 : *right

    node1::left --> node2
    node1::right --> node3

    object "Proxy" as proxy1 #orange
    proxy1 : *country
    proxy1 : counter = 2

    object "Proxy" as proxy2 #orange
    proxy2 : *country
    proxy2 : counter = 1

    node2::proxy -> proxy1

    node3::proxy --> proxy2
    proxy2::country -> R2

    node1::proxy -> proxy1
    proxy1::country --> R1

Step 1
^^^^^^

.. uml::
   :align: center
   :width: 10cm
   :caption: Step 1

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #yellow {
        object "Country" as Country2
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : *proxy
    node1 : *left
    node1 : *right

    object "Node 2" as node2 #grey
    node2 : *proxy
    node2 : *left
    node2 : *right


    object "Node 3" as node3
    node3 : *proxy
    node3 : *left
    node3 : *right

    node1::left --> node2
    node1::right --> node3

    object "Proxy" as proxy1 #orange
    proxy1 : *country
    proxy1 : counter = 1

    object "Proxy" as proxy2 #orange
    proxy2 : *country
    proxy2 : counter = 1

    node2::proxy .> proxy1

    node3::proxy --> proxy2
    proxy2::country -> R2

    node1::proxy -> proxy1
    proxy1::country --> R1

Step 2
^^^^^^

.. uml::
   :align: center
   :width: 10cm
   :caption: Step 2

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #yellow {
        object "Country" as Country1
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #grey {
        object "Country" as Country2 #grey
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1
    node1 : *proxy
    node1 : *left
    node1 : *right

    object "Node 2" as node2 #grey
    node2 : *proxy
    node2 : *left
    node2 : *right


    object "Node 3" as node3 #grey
    node3 : *proxy
    node3 : *left
    node3 : *right

    node1::left --> node2
    node1::right --> node3

    object "Proxy" as proxy1 #orange
    proxy1 : *country
    proxy1 : counter = 1

    object "Proxy" as proxy2 #grey
    proxy2 : *country
    proxy2 : counter = 0

    node2::proxy .> proxy1

    node3::proxy ..> proxy2
    proxy2::country -> R2

    node1::proxy -> proxy1
    proxy1::country --> R1

Step 3
^^^^^^

.. uml::
   :align: center
   :width: 10cm
   :caption: Step 3

    skinparam classAttributeIconSize 0
    package "Resource" as R1 <<Rectangle>> #grey {
        object "Country" as Country1 #grey
        Country1 : name = "UFO"
        Country1 : id = 10
    }

    package "Resource" as R2 <<Rectangle>> #grey {
        object "Country" as Country2 #grey
        Country2 : name = "ABC"
        Country2 : id = 3
    }

    object "Node 1 (Root Node)" as node1 #grey
    node1 : *proxy
    node1 : *left
    node1 : *right

    object "Node 2" as node2 #grey
    node2 : *proxy
    node2 : *left
    node2 : *right


    object "Node 3" as node3 #grey
    node3 : *proxy
    node3 : *left
    node3 : *right

    node1::left --> node2
    node1::right --> node3

    object "Proxy" as proxy1 #grey
    proxy1 : *country
    proxy1 : counter = 0

    object "Proxy" as proxy2 #grey
    proxy2 : *country
    proxy2 : counter = 0

    node2::proxy .> proxy1

    node3::proxy ..> proxy2
    proxy2::country -> R2

    node1::proxy .> proxy1
    proxy1::country --> R1

Reference code to create the node:

.. code-block:: c

    Node *Node_create(Country *country) {
        // Create a Node with given country
        // return a new node
        Node *new_node = malloc(sizeof(Node));
        if (country) {
            new_node->country_proxy          = malloc(sizeof(Country_proxy));
            new_node->country_proxy->counter = 0;
            new_node->country_proxy->proxy   = country;
            new_node->country_proxy->counter++;
        } else {
            new_node->country_proxy = NULL;
        }
        new_node->left  = NULL;
        new_node->right = NULL;
        return new_node;
    }

Reference code for destroying:

.. code-block:: c

    void tree_destroy(Node *root) {
        // release memory
        if (root == NULL) {
            return;
        } else {
            // free all resources
            tree_destroy(root->left);
            tree_destroy(root->right);
            if (root->country_proxy && root->country_proxy->counter > 0) {
                // proxy still alive, decrease the counter by 1
                root->country_proxy->counter--;
                if (root->country_proxy->counter == 0) {
                    // counter is 0, free it!
                    free(root->country_proxy->proxy);
                    free(root->country_proxy);
                }
            }
            free(root);
        }
    }

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

We use :program:`msan, asan, lsan, ubsan` to perform the checks. The feedback is very clear. It shows the track-back and tell you where the problem is in your source files.

Alternative memory checking tools are :program:`valgrind` (not available on Windows). For Windows users, you can either try searching tools online or use WSL.

Attendance Quiz
---------------

Please do the attendance quiz on Canvas now.

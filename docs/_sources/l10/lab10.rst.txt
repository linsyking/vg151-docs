Zombies in JI
=============

.. role:: cpp(code)
  :language: cpp

More About Project 3
--------------------

- Please download the latest ``p3.pdf`` from canvas. We have updated some requirements in it.
- You can choose either CMake or Makefile to build p3. However, please use the templates in `materials repository <https://focs.ji.sjtu.edu.cn/git/ENGR151-22/materials/src/branch/master/templates/p3>`_. The default build system is CMake.
- In p3, you will pass drone even though you don't pass code quality and runtime checks. Only compile test is necessary to pass drone and merge into master branch.
- However, you might get some deductions if you cannot pass those "optional" checks. Hence, you should check the details of drone even if it is a green badge.
- The code check in p3 is less strict than p2 and you should at least read those errors from code check (some rules have been set to warnings rather than errors)
- You should add some code around all OpenGL-related code to pass test on drone. The detailed requirements are written in the part 2 of p3.pdf.
- ``include`` folder in your p3 repo is used to store all header files, ``pms`` is used to store cpp code for the first part of p3 while ``ipa`` is used for part 2.
- If you want to do bonus, please contact us first.

Background
----------

  Read the **fun** story in the lab manual. It's fun.

Objects
-------

In OOP(Object Oriented Programming), the first things we need to do is to define the objects we want to use in our program.

Recall the `Zombie` story. Where does it happen? In the `Long Bing building`. Therefore, we need to describe the building structure in our program.

What is necessary in the building to describe the game? One building, some floors, rooms and creatures.

The whole building contains several floors. Floor contains rooms. Room contains creatures. For simplicity, creatures can only be in the rooms (rather than in the corridors), and there is only one kind of floor and room.

Assume the structure of the building looks like:

.. code-block::

  Building
  |---------------------------------------------------|
  | Floor4 :| 401 | 402 | 403 | 404 |
  |----------+++++------------------------------------|
  | Floor3 :| 301 | 302 | 303 | 404 | 305 | 306 | 307 |
  |----------+++++------------------------------------|
  | Floor2 :| 201 | 202 | 203 | 204 | 205 | 206 | 207 |
  |----------+++++------------------------------------|
  | Floor1 :| 101 | 102 | 103 | 104 | 105 | 106 | 107 |
  |---------------------------------------------------|

  # +++++ means the stairs between floors

Now, we have to define the member functions and attributes of each class. Think from the bottom to the top!

`(A draft)`
  
Member functions of ``creature``:

- Get the position of the creature.
- Get the type of the creature.
- Get the (the pointer to) current room.
- Get the type of the creature (zombie or human).
- Move to a given direction.
- Move to a room. (?)
- (TBD)

Member functions of ``room``:

- `ctor`: create an empty room.
- Add a creature to this room.
- Get all the creatures (pointers) in this room.
- Get the room number.
- Get the neighbors of a room.
- Get (the pointer to) the floor
- Remove one creature in this room.

Member functions of ``floor``:

- `ctor`: create a floor with a given number of rooms. Each room is empty.
- Add a creature to this floor (need to specify the room number).
- Get the rooms of this floor.
- Get the neighbors of the floor.
- Get the floor number.
- Get the building.
- Get all the creatures in this floor. (?)

Member functions of ``building``:

- `ctor`: initialize the building with the given number of floors, rooms and creatures.
- Get all the floors.
- Get all the creatures in the building.

Member functions of ``game`` (implemented by a `singleton`):

- `ctor`: initialize the game (the building) with the given number of floors, rooms and creatures.
- Run the game by one step.

.. admonition:: Think

  Which member functions should be :cpp:`public`, which should be :cpp:`private` (no inheritance is involved in this case)?

After determining the member functions, you can define the attributes!

.. warning::

  **Always** use `setters` and `getters` to access the attributes of the classes. Do not access the attributes directly. The attributes should be only accessed by the member functions of the class (either :cpp:`private` or :cpp:`protected`, :cpp:`private` is preferred).

Creatures
---------

Creatures are more complicated. The relations we talked about above are all `"has-a"` relationship. Creatures can be described as below:

- Creature can be the type of `human` or `zombie`.
- Creatures can either be teachers, students or staffs.
- TAs are both students and teachers.

What's the difference between a zombie and a human? Well, zombies can bite humans and turn them into zombies (or simply kill them). Humans can only move to a given direction (different types of people will have different strategies).

First, design a hierarchy diagram. The basic requirements are: **no diamond problem**.

.. warning::

  No diamond problem should appear in the hierarchy diagram. If you have a diamond problem, you should think about the relationship between the classes again.

There are two ways to implement the hierarchy:

Solution 1
^^^^^^^^^^

OOP sucks, let's use `enum` to represent the type of creatures.

Here we use a special technique called `bitmask`.

.. code-block:: cpp

    enum CreatureIdentity {
        ZOMBIE  = 0,
        HUMAN   = 1,
        STAFF   = 2,
        TEACHER = 4,
        TA      = 8
    };  // enum CreatureIdentity
    // You can also use enum class/namespace to avoid name conflicts

    // Example usage:
    int student1 = Student | TA | Zombie;
    int teacher2 = Teacher | Human;

    if (student1 & Zombie) {
        // if student1 is a zombie
    }

However, to take advantage of inheritance, we can define ``creature`` as an abstract class and define ``human`` and ``zombie`` as derived classes. (of course this will not cause any diamond problem)

here is the hierarchy diagram:

.. figure:: /_static/l10/first_solution.png
  :scale: 100
  
  Simple Hierarchy Diagram

Solution 2
^^^^^^^^^^

I like design complicated hierarchy diagram! Multiple inheritance is the best!

However, you have to solve the basic problem: **diamond problem**. Since TA is both a student and a teacher, what should we do? We have to change our diagram based on the special characters we want to differentiate teachers/student and TAs.

For example, if TA is more like a student, we can remove the relationship between TA and teacher. If TA is more like a teacher, we can remove the relationship between TA and student. Then, we can use multiple inheritance to implement the hierarchy. To be more specific, say the main difference between a TA and a normal student is that TA can get money (which is the same as a teacher). Then we create a new class called "SalaryMan" and make TA and teacher inherit from it.

If in our game we want teachers and TAs protect their students, we can add a new class called "Protector" and make teacher and TA inherit from it. This can simply solve the diamond problem.

.. figure:: /_static/l10/second_solution.png
  :scale: 100
  
  Complicated Hierarchy Diagram

Note: The `Identity` should be a member attribute of a `Creature`.

-------

However, as the situation may become more complicated, it's **recommended** to use the first solution. The second solution is more complicated and may cause some problems. In reality, if your game has many characters and many special superpowers, the hierarchy diagram often becomes a mess and cannot describe the relationship well. In this case, we often use a `database` to store the information of each character and superpowers (which will be much faster and clearer).

What to Add for Each Class?
^^^^^^^^^^^^^^^^^^^^^^^^^^^

It depends on your needs. You can decide your game rules and write different implementations of the classes.

How to Code?
------------

Due to time limit, we won't show you how to code (in the lab manual, it also didn't ask you to code, only designing the game is necessary).

However, when you are implementing the inheritance, you should at least know the following concepts:

- `virtual` functions
- Constructors and destructors
- Different types of inheritance
- Memory management (especially :cpp:`new` and :cpp:`delete`, but if you know `smart pointers`, that's a better choice)
- Multiple inheritance (optional)
- Abstract class (pure virtual functions)
- Downcast and upcast (if you know how, it's better to use :cpp:`dynamic_cast`)
- Basic usage of :cpp:`std::vector` (should be mentioned in the course)

.. tip::

  If time permits, I can do some demonstrations in the lab.

Singleton
---------

In ``p3.pdf``, we provide you with a singleton template:

.. code-block:: cpp

    class Singleton {
    private:
        Singleton() {}
        // Add your member attributes

    public:
        static Singleton &getInstance() {
            static Singleton instance;
            return instance;
        }

        Singleton(Singleton const &)      = delete;
        void operator=(Singleton const &) = delete;
        // Add your member functions
    };

How to use it?

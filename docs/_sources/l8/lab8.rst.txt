Introduction to OpenGL
======================

.. role:: cpp(code)
   :language: c++

OpenGL
------

    OpenGL is a cross-language, cross-platform application programming interface (API) for rendering 2D and 3D vector graphics. The API is typically used to interact with a graphics processing unit (GPU), to achieve hardware-accelerated rendering.

    -- `Wikipedia: OpenGL <https://en.wikipedia.org/wiki/OpenGL>`_

GLUT and FreeGLUT
-----------------

    The OpenGL Utility Toolkit (GLUT) is a library of utilities for OpenGL programs, which primarily perform system-level I/O with the host operating system. Functions performed include window definition, window control, and monitoring of keyboard and mouse input. Routines for drawing a number of geometric primitives (both in solid and wireframe mode) are also provided, including cubes, spheres and the Utah teapot. GLUT also has some limited support for creating pop-up menus.

    -- `Wikipedia: GLUT <https://en.wikipedia.org/wiki/OpenGL_Utility_Toolkit>`_

    FreeGLUT is an open-source alternative to the OpenGL Utility Toolkit (GLUT) library. GLUT (and hence FreeGLUT) allows the user to create and manage windows containing OpenGL contexts on a wide range of platforms and also read the mouse, keyboard and joystick functions. FreeGLUT is intended to be a full replacement for GLUT, and has only a few differences.

    -- `Wikipedia: FreeGLUT <https://en.wikipedia.org/wiki/FreeGLUT>`_

Freeglut has some limitations comparing to GLFW [1]_. However, in this course, we only need to use freeglut to draw some simple animations. Therefore, we won't use more complicated libraries.

The freeglut project can be found on `this repository <https://github.com/FreeGLUTProject/freeglut>`_.

Getting Started
---------------

Linux
^^^^^

Install ``glu`` and ``freeglut`` library.

MacOS
^^^^^

Maybe you don't need to install.

Windows
^^^^^^^

If you are using ``MSYS2``, you can try:

.. code-block:: bash

    pacman -S mingw-w64-x86_64-freeglut

Hello Teapot
------------

In this part, we will try to figure out how to write a Hello world program for OpenGL.

Copy the following code and save it to ``main.cpp``.

.. code-block:: c++
    :caption: main.cpp

    /* macos */
    #include <GLUT/glut.h>
    /* windows */
    #include <GL/freeglut.h>
    #include <windows.h>
    /* linux */
    #include <GL/freeglut.h>
    void display() {
        /* clear window */
        glClear(GL_COLOR_BUFFER_BIT);
        /* draw scene */
        glutWireTeapot(.5);
        /* flush drawing routines to the window */
        glFlush();
    }
    int main(int argc, char *argv[]) {
        /* initialize GLUT, using any command line parameters passed to the program */
        glutInit(&argc, argv);
        /* setup the size, position, and display mode for new windows */
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0, 0);
        glutInitDisplayMode(GLUT_RGB);
        /* create and set up a window */
        glutCreateWindow("hello, teapot!");
        glutDisplayFunc(display);
        /* tell GLUT to wait for events */
        glutMainLoop();
    }

First, you have to change the code. You have to add some macros to check the OS.

After that, to compile it, run:

Linux
^^^^^

.. code-block:: bash

    g++ -Wall -Wextra -Wpedantic -Werror -std=c++17 -o teapot main.cpp -lglut -lGL -lGLU

MacOS
^^^^^

.. code-block:: bash

    g++ -Wall -Wextra -Wpedantic -Werror -std=c++17 -o teapot main.cpp -framework OpenGL -framework GLUT

Windows
^^^^^^^

.. code-block:: bash

    g++ -Wall -Wextra -Wpedantic -Werror -std=c++17 -o teapot main.cpp -lglu32 -lfreeglut -lopengl32

However, to make our life easier, we have to write a ``Makefile`` or ``CMakeLists.txt`` to help us compile.

``Makefile``
------------

Since we have to compile the program on different OS, we have to change the ``CFLAGS`` separately.

But, how to add different ``CFLAGS`` for different OS?

.. literalinclude:: Makefile
    :caption: Makefile
    :language: make

``CMakeLists.txt``
------------------

Things become easier in ``CMake``. We only need to find the libraries and add them. We don't have to add the flags by hand.

An example:

.. code-block:: cmake
    :caption: CMakeLists.txt

    cmake_minimum_required(VERSION 3.5)
    project(helloteapot)
    set(CMAKE_CXX_STANDARD 17)

    set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Wvla")

    set(OpenGL_GL_PREFERENCE "GLVND")

    # Find the OpenGL library
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})

    # Find the GLUT library
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIR})

    add_executable(teapot main.cpp)

    # Link OpenGL, GLUT
    target_link_libraries(teapot ${GLUT_LIBRARIES} ${OPENGL_LIBRARY})

Understanding the Code
----------------------

:cpp:`glutInit(&argc, argv);`

This function will initialize GLUT.

.. code-block:: c++

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB);

These two lines set the size, position and display mode. Generally, using ``GLUT_RGB`` is enough. But if you want to make your animation more fluent, you can use double buffer mode (``GLUT_DOUBLE``).

.. hint:: What is Double Buffer Mode?

    Double buffering provides two complete color buffers for use in drawing. One buffer is displayed while the other buffer is being drawn into. When the drawing is complete, the two buffers are swapped so that the one that was being viewed is now used for drawing. The swap is almost instantaneous, and thus provides a means of performing animation, like the way a sequence of still photographs, rapidly displayed, appear to depict a moving object. [2]_

    When using ``GLUT_DOUBLE``, your picture will have two buffers. One of them is always visible, the other one is not. You always render to the buffer that is not currently visible. When you're done rendering the frame, you swap the two buffers, making the one you just rendered visible. The one that was previously visible is now invisible, and you use it for rendering the next frame. So the role of the two buffers is reversed each frame. [3]_

    In short, you will need to add :cpp:`glutSwapBuffers();` after :cpp:`glFlush();`.

.. code-block:: c++

    glutCreateWindow("hello, teapot!");
    glutDisplayFunc(display);
    glutMainLoop();

:cpp:`glutDisplayFunc` will tell GLUT which function is used to display.

:cpp:`glutMainLoop` will tell GLUT wait for events.

Rendering a triangle
--------------------

After running hello teapot, we want to draw something new. The most basic element is triangle.

.. code-block:: c++

    glColor3f(1, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex2d(-0.5, 0.5);
    glVertex2d(-1, 0.5);
    glVertex2d(-0, -0.5);
    glEnd();

First, set the color. Then, we use :cpp:func:`gl_Begin` to draw a triangle.

Write your own triangle!

Animation
---------

I will introduce :cpp:func:`timer` and :cpp:func:`glutMainLoop`.

See the following example:

.. code-block:: c++
    :caption: main.cpp
    :emphasize-lines: 1-7,41-42

    void timer(int v) {
        if (v != 0) {
            return;
        }
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, timer, 0);
    }

    void display() {
        /* clear window */
        glClear(GL_COLOR_BUFFER_BIT);
        /* draw scene */
        int  &num   = test::get_instance().get_number();
        float num_f = static_cast<float>(num);

        glColor3f(0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex2d(-0.5, 0.5);
        glVertex2d(std::cos(num_f / 10) / 2, std::sin(num_f / 10) / 2);
        glVertex2d(-0.5, -0.5);
        glEnd();

        num++;
        glFlush();
        glutSwapBuffers();
    }

    int main(int argc, char *argv[]) {
        /* initialize GLUT, using any command line parameters passed to the program */
        glutInit(&argc, argv);
        /* setup the size, position, and display mode for new windows */
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(0, 0);
        glutInitDisplayMode(GLUT_DOUBLE);

        /* create and set up a window */
        glutCreateWindow("hello, teapot!");
        glutDisplayFunc(display);
        glClearColor(1, 1, 1, 1);
        /* tell GLUT to wait for events */
        timer(0);
        glutMainLoop();
    }

You can assume that variable ``num`` is somehow a global variable. (it's only for me to do the demonstration. do not use global variables!)

Singleton Template
------------------

You can see this part after you learn C++ Class.

Define your class:

.. code-block:: c++

    class test {
    private:
        test() {}
        // Define your methods and variables here

    public:
        static test &get_instance() {
            static test i;
            return i;
        }

        test(test const &)           = delete;
        void operator=(test const &) = delete;
    };

You can get this instance elsewhere by directly using :cpp:`test::get_instance()`.

.. [1] `What is the difference between FreeGLUT vs GLFW? <https://stackoverflow.com/questions/25708688/what-is-the-difference-between-freeglut-vs-glfw>`_

.. [2] `Double Buffering in GLUT <http://www2.cs.arizona.edu/classes/cs433/spring02/opengl/dblbuffer.html#:~:text=Double%20buffering%20provides%20two%20complete,is%20now%20used%20for%20drawing.>`_

.. [3] `Difference between single buffered(GLUT_SINGLE) and double buffered drawing(GLUT_DOUBLE) <https://stackoverflow.com/questions/28298540/difference-between-single-bufferedglut-single-and-double-buffered-drawingglut>`_

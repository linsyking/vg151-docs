Git Revisit
===========

In the first lab, you have learned how to use Git to manage your code.

You should have a basic understanding of the following commands:

.. code-block:: bash

    git init
    git add
    git commit
    git push
    git pull

However, you may have already noticed that there is "branches" in your Git repository. What is a branch and how can we take advantage of it?

In homework repository, you have one ``master`` branch and one ``group`` branch. Moreover, you have several individual branches.

Today, we will learn how to use branches in a more professional way to manage your code.

What is ``commit`` and ``branch``?
-----------------------------------

A ``commit`` is a snapshot of your code. It is a version of your code. You can think of it as a "checkpoint" in your code.

A ``branch`` is a pointer to a ``commit``. It is a `pointer` to a specific version of your code. You can think of it as a "branch" in your code.

Toy Git Playground
------------------

Goto this website `learn git branching <https://learngitbranching.js.org/>`_ and unlock all levels in `Introduction to Git Commits`, `Ramping Up` and `Moving Work Around`.

Have fun and play it!

You should at least know the following things after playing:

- ``git checkout``
- ``git merge``
- ``git rebase``
- ``git reset``
- ``HEAD^`` and ``HEAD~1``
- ``git cherry-pick``

Real Git
--------

In reality, Git is **much more complicated** than the toy playground. However, the basic idea is the same. You should remember those commonly-used commands and workflow.

Some Useful Commands
--------------------

- ``git log``: show the commit history
- ``git diff``: show the difference between two commits
- ``git clean -df``: remove untracked files
- ``git add -A``: add all files to the staging area

Solving Conflicts
-----------------

When you merge two branches, you may encounter conflicts. You can solve the conflicts by editing the files and then commit the changes. Or, if you use VS Code, it has a built-in Git GUI to help you solve the conflicts. Other IDE/Editors may have similar tools.

Good Bye
--------

This is the last lab in ENGR1510J.

My initial idea is to introduce the `beauty of programming and computer science` to you. Don't feel disappointed if you cannot understand the concepts in this course. There are many fields other than programming. You can still be successful in your life.

I hope that you all learned something useful in my lab. I wish you all the best in your future studies and career.

Thanks for your attention. Bye! (If you are interested in `software engineering`, please enroll in the manuel's section of VG100, one of the **greatest programming experience in JI**)

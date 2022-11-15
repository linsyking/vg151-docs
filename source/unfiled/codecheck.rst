Code Check
==========

Introduction to ``clang-tidy``
------------------------------

`clang-tidy <https://clang.llvm.org/extra/clang-tidy/index.html>`_ is a static analyzer for C and C++.

It has many checks and can help us find some potential bugs.

VG151 code quality checks
-------------------------

Originally, I wrote a :program:`python` script to perform the checks. It works quite good, but it fails for complicated cases.

Therefore, I spent some time writing a plugin for ``clang-tidy``, and it works very well. It enables me to get ``AST`` of the code and I can match some specific code and traverse the tree.

Run checks on your program
--------------------------

You can log into manuel's server and we have already installed :program:`clang-tidy` and my plugin for you.

Simply type:

.. code-block:: bash

    clang-tidy --load=/usr/local/lib/libcodequality.so # add your source code

Checks we enabled
-----------------

The ``.clang-tidy`` file we enabled is the following:

.. code-block::
    :linenos:
    
    ---
    Checks: 'clang-diagnostic-*,clang-analyzer-*,-*,misc-*,performance-*,readability-function-size,readability-identifier-naming,readability-named-parameter, readability-redundant-*,readability-simplify-boolean-expr,readability-mis*,-clang-analyzer-security*,-misc-no-recursion,bugprone-assignment-in-if-condition,bugprone-integer-division,bugprone-suspicious-string-compare,cppcoreguidelines-init-variables,llvm-header-guard,google-global-names-in-headers,codequality-*'
    WarningsAsErrors: '*'
    CheckOptions:
    - key:             readability-function-size.LineThreshold
        value:           '200'
    ...

Run ``clang-tidy`` with our checks locally
-------------------------------------------------

If you want to perform the checks locally, you can use the prebuilt plugin on the `Release page <https://github.com/linsyking/vg151-codequality/releases>`_.

Contribution
------------

Go to `Github repository <https://github.com/linsyking/vg151-codequality>`_, you can open PRs and issues.

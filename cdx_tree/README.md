tree_thing 
==========

Problem Statement/Requirements
------------------------------

create a small program that can consume a text file that describes an encoded tree structure.  The file may contain any number of lines, each line has one of the two following formats:

    <node_id> <left_child> <right_child> <node_description>

OR

    <node_id> <node_description>

node_id, left_child and right_child are all integer numbers, and may be arbitrary. The node_description is a string.  All fields are separated by arbitrary amounts of whitespace.  Assume every character from the first non-whitespace character of node_description to the end of the line is part of the node description.  The nodes in the tree may be described in the file in any order - the complete file describes the tree.

Please build up an in-memory data structure in one pass across the file. Once the data structure is built, print out the node_descriptions breadth-first, separated by spaces; then depth-first, separated by spaces (all left-to-right for peers).  Please try to be robust in handling any input lines that are malformed or have errors in syntax or structure that you can detect.

As an example, assume the input file looks like:

    15 2 25 first description
    2 1 3 another
    1 one
    3 three
    25 twenty-five

the first node is 15 ('first description'), it's left child is 2 ('another') and it's right child is 25 ('twenty-five').  In turn, 2's left child is 1 ('one') and right child is 3 ('three').


Building
--------

Prerequisites:

  * gcc
  * libtool
  * autoconf
  * automake
  * check (to build tests)

To build and install:

    $ sh autogen.sh
    $ ./configure
    $ make
    $ make test

    I have not tested the 'install' target (there is no point for this code) - use with caution (it's probably incorrect).
  

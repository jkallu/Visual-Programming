.. index::

************************
Expression parsing
************************

The mathematical expressions written on the visual blocks configuration environment has to be compiled into the C language. For this purpose, first we need to tokenize the expression string with a lexical analyzer, then parse it with Earley recognizer and parser and then translate into C code. We will go through these steps in the following sections.

Lexical analyzer
=================

A lexical analyzer is a program that separates the source code into a sequence of lexemes. It reads the input source code character by character, recognize the lexemes and outputs a sequence of tokens describing the lexemes. A good read on the lexical analyzer can be found on the link 
https://hackernoon.com/lexical-analysis-861b8bfe4cb0.

Regular expression
=====================

Context free grammar
====================


Earley recognizer and parsing
=================================

A good read on the Earley recognizer can be found on Wikipedia link https://en.wikipedia.org/wiki/Earley_parser

Set comprehension (list comprehension)
=========================================

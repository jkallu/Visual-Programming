.. index::

************************************************
Block diagram description of generated program
************************************************

Now that we know what the program does,  let’s better understand how the software do it with the help of Figure 1.1.

.. figure:: images/image10.png

   Figure 1.1: A block diagram representation of the workings of the program. Each block is a C function. Main in the entry        function which is defined in main.c. See text for more details.


The entry point to the program is the main block. Main block generates two source codes (main.c and eventLoop.c) and one header file (eventLoop.h). The main.c has the entry main() function defined.  From within the main() function, it calls exec() defined in the eventLoop.c and pass the name of the next block to be called. In this case, the name of the next block is Array_0.
The exec() function has two jobs, the first is to create a data pack with the name of the next function block to be called (the first block connected from main block output) and send it to the linked list. The second job is to call the eventloop thread which loops continuously till the end of the program life.

The event loop continuously scan the linked list for any available data and if it is available, it calls the block (function) to be executed with the name and pass the packed data.

In our example, each visual block are array block, duplicate block, expression block and graph block.

Data packing format
===================
.. figure:: images/image5.png

   Figure 1.2: Data packing format.
   
Linked list structure
===================
.. figure:: images/image8.png

   Figure 1.3: Linked list structure.

   



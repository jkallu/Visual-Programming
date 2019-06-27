.. index::
    
************
Introduction
************
Let’s examine the workings of the program with a simple example as shown in Gif 1.1. In the gif, we have five blocks, a Main block, Array block, Duplicate block, Expression block and Graph block. The number suffix is used to have a unique name for every block, in case of multiple blocks of the same type. The main block calls an array block which creates an array data. This array data is duplicated into two identical arrays by the duplicate block. One data is fed through an expression block which has a sin(x) expression in this example, produce the sine data.  Finally both data are fed to the graph block and plotted. Thus this program generate a sine(x) data and plot it. 

.. figure:: images/sine_graph_30fps.gif

   Gif 1.1: An animated program and data flow, a simple example of visual programming. The Main block is the entry block, which    calls an Array block. The Array block creates an array data and this data is sent to the Duplicate block. The Duplicate        block duplicates the data and the output is two identical arrays. One is fed through an Expression block, in this case a        sin(x) expression. Finally data are displayed in a Graph block. 


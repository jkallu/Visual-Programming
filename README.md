# Visual Programming and Simulation
[![Build Status](https://dev.azure.com/jineshkallunkathariyil/Visual%20programming%20and%20simulation/_apis/build/status/jkallu.Visual-Programming?branchName=master)](https://dev.azure.com/jineshkallunkathariyil/Visual%20programming%20and%20simulation/_build/latest?definitionId=5&branchName=master)  

* Visual programming uses a mix of visual blocks and traditional programming (coding) methods. 
* The program design uses node-graph editor.
* Each blocks has an additional capability of writing expressions (minimalist coding).
* For example, user can easily create an array, do math functions on it and then plot the outputs. 
* When the visual blocks are executed, it generates the optimised C/C++ codes for the blocks, and the corresponding Makefile.
* Then it do a compilation of the generated code and create a library Just in Time (JIT). 
* It then dynamically load the library and execute the the library. 
* Result of each block is brought back to the visual blocks ouput data and displayed. 
* This can be considered as the simulation of the program and data execution. 
* In this way one can easily see the outputs of each blocks just in time and can easily debug the program. 
* Once the program execution is simulated and tested one can generate a standalone Makefile and the main program which calls the already created library and execute this program and generate the binary. 
* This binary uses the same library that was used for the testing and simulation. 
* In this way the simulation and stand alone results will be the same. 
* More over the output binary is a compiled (non interpreted) binary.
* Also blocks supports mathematical expressions which are then compiled to C/C++.
* Set comprehension / List comprehension capability.
* Support for GSL library, for example ode solver in GSL has a visual block. User only need to write the ode function to be solved. All the internal wirings are done automatically.
* Support for 1D, 2D and 3D simulation. For example, one can connect a sine wave data (which is a solution to the spring mass system) to a 1D block, wher it accepts two data, time and one dimensional position data. The position data can be aligned in any of three axes (x, y or z). A sphere in the block will follow the dat, in this example sine data. 
* More is on the way... currently this program is under development. 


[Documentation (under development)](https://jkallu.github.io/Visual-Programming/)  
## Generate and plot sine function
![Alt text](https://github.com/jkallu/Visual-Programming/blob/master/docs/images/sine_graph_30fps.gif? "Title")  
## Generate and simulate sine function
![Alt text](https://github.com/jkallu/Visual-Programming/blob/master/docs/images/sine_sim_30fps.gif? "Title")

## Prerequisites
[Qt 5 or later](https://www.qt.io/download)  
[GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/) 
```
$ sudo apt-get install libgsl23 libgslcblas0 libgsl-dbg libgsl-dev
```

## Get it
```
$ git clone https://github.com/jkallu/Visual-Programming.git
$ cd Visual-Programming/Node/build
$ qmake ../Node.pro
$ make
$ ./Node
```

[Documentation (under development)](https://jkallu.github.io/Visual-Programming/)

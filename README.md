# Visual Programming and Simulation
[![Build Status](https://dev.azure.com/jineshkallunkathariyil/Visual%20programming%20and%20simulation/_apis/build/status/jkallu.Visual-Programming?branchName=master)](https://dev.azure.com/jineshkallunkathariyil/Visual%20programming%20and%20simulation/_build/latest?definitionId=5&branchName=master)
[![Documentation Status](https://readthedocs.org/projects/visual-programming/badge/?version=latest)](https://visual-programming.readthedocs.io/en/latest/?badge=latest)


* Visual programming uses a mix of visual blocks and functional programming (coding) methods. 
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
* The GUI is developed using Qt.
* More is on the way... currently this program is under development. 


[Documentation (under development)](https://visual-programming.readthedocs.io)  
## Demos
### Generate and plot sine function
![Alt text](https://github.com/jkallu/Visual-Programming/blob/master/docs/images/sine_graph_30fps.gif? "Title")  

### Generate and simulate sine function
![Alt text](https://github.com/jkallu/Visual-Programming/blob/master/docs/images/sine_sim_30fps.gif? "Title")

### Simulation with Gnuplot
![Alt text](https://github.com/jkallu/Visual-Programming/blob/master/docs/images/sine_gnuplot_sim.gif? "Title")

## Run with Docker image   
First, clone the repository from github.
```
git clone https://github.com/jkallu/Visual-Programming.git
cd Visual-Programming/Node
```
The following command downloads the docker file from 
[dockerhub](https://hub.docker.com/r/jinkallu/visual_programming)
(if not already exists) and build the source.
```
sudo docker run --rm -v `pwd`:/project/source -v `pwd`/build:/project/build jinkallu/visual_programming:latest
```
The binary will be saved in build directory.
To run the binar with X window
### Linux
```
xhost +local:docker   
sudo docker run --rm -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v `pwd`:/project/source -v `pwd`/build:/project/build jinkallu/visual_programming:latest ./Node
```
### Windows  
Install X server for windows. For example, [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/). Then launch Xlaunch from start and set it up with following,
1. Multipple windows
2. Start no client
3. Check disable access control and 
4. finish   
[More details on how to run docker image with gui apps...](https://dev.to/darksmile92/run-gui-app-in-linux-docker-container-on-windows-host-4kde) 

In Windows powershell
```
ipconfig
```
Find the ip of the system and then
```
set-variable -name DISPLAY -value 192.168.0.5:0.0   
sudo docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v `pwd`:/project/source -v `pwd`/build:/project/build jinkallu/visual_programming:latest ./Node
```
## Libraries used
[Qt 5 or later](https://www.qt.io/download)  
Necessary modules
```
gui widgets opengl script 3dcore 3drender 3dinput 3dlogic 3dextras 3danimation printsupport svg network
```
[GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/) 
```
$ sudo apt-get install libgsl23 libgslcblas0 libgsl-dbg libgsl-dev
```
[Gnuplot](http://www.gnuplot.info/)  


[Documentation (under development)](https://visual-programming.readthedocs.io)

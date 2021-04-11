PHAS0100Assignment2
------------------

[![Build Status](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2.svg?branch=master)](https://travis-ci.com/[USERNAME]/PHAS0100Assignment2)
[![Build Status](https://ci.appveyor.com/api/projects/status/[APPVEYOR_ID]/branch/master)](https://ci.appveyor.com/project/[USERNAME]/PHAS0100Assignment2)


Purpose
-------

This project serves as a starting point for the PHAS0100 Assignment 2 Gravitational N-body Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects,
that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.


Credits
-------

This project is maintained by [Dr. Jim Dobson](https://www.ucl.ac.uk/physics-astronomy/people/dr-jim-dobson). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](http://rits.github-pages.ucl.ac.uk/research-computing-with-cpp/)
course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james)
and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).


Build Instructions
------------------

Ensure that  a "out-of-source" build is made.

Detailed of "out-of-source" build is shown below:

<br/>(1): Make sure that you are in the PHAS0100ASSIGNMENT2 directory<br/>  
<br/>(2): **mkdir** build (or skip this step if you have created this directory before)<br/>
<br/>(3): **cd build**<br/>
<br/>(4): **cmake ..  -DCMAKE_BUILD_TYPE=Release** if you want to toggle off all std::cout, which is for the benchmarking<br/>
<br/>(5): Or **cmake ..  -DCMAKE_BUILD_TYPE=Debug** if you want to toggle on all std::cout, which is for outputing r_com and p_total to screen as the simulation evolves<br/>
<br/>(6): **make**<br/>


<br/>
Command line Instructions
------------------
After all these five steps, you can now run the command line app from the build directory and pass the step_size and the number of timesteps when invoking the command like this syntax:

<br/>a): **solarSystemSimulator [-s  step_size for the simulation] [-n  number of timesteps]**<br/>
<br/>b): **solarSystemSimulator [--stepsize  step_size for the simulation] [--number number of timesteps]**<br/>

Instruction may be like:
<br/>a): **./bin/solarSystemSimulator -s 0.000274 -n 3650**<br/>
<br/>b): **./bin/solarSystemSimulator -s 0.0000274 -n 36500**<br/>

<br/>
Unit test Instructions
------------------
Apart from command line app, you can also run the unit tests for this project. Instructions for unit test: **./bin/nbsimSolarSystemSimulationTest**. Or you could also simplely run **ctest** in the build directory.


<br/>
Benchmark
------------------
Benchmark the time that takes simulation to run for 1 year’s worth of simulated time and for
seven different timestep sizes. The detailed summary is listed below


|**step_size**|**p_total**|**r_com**|**p_total**|**r_com**|**Position of Earth**|**CPU time**|**Wall clock time**|
| :----: | :----: | :----: | :----: | :----: | :----: |:----: | :----: |
| 0.1second | (-4.63988e-05,2.58709e-05,-5.22848e-07) |  (-2.19114e-06,1.97059e-06,-7.94702e-09) | 5.31265e-05 | 2.94693e-06 | (-0.194365, 0.968603, 0.000108605) | 169498 ms | 169498 ms |
| 1second | (-4.63988e-05,2.58709e-05,-5.22848e-07) |  (-2.19114e-06,1.97059e-06,-7.94702e-09) | 5.31265e-05 | 2.94693e-06 | (-0.194355, 0.968607, 0.000108605) | 17242.9 ms | 17243ms |
| 1minute | (-4.63986e-05,2.58709e-05,-5.22848e-07) |  (-2.1914e-06,1.97073e-06,-7.9498e-09)   | 5.31263e-05 | 2.94721e-06 | (-0.195025, 0.968635, 0.0001086)   | 268.687 ms | 268.685 ms |
| 1hour   | (-4.63985e-05,2.58709e-05,-5.22848e-07) |  (-2.19161e-06,1.97085e-06,-7.95212e-09) | 5.31262e-05 | 2.94745e-06 | (-0.156951, 0.983257, 0.000108645) | 5.022 ms   | 5.0191 ms |
| 0.1day  | (-4.63987e-05,2.58709e-05,-5.22848e-07) |  (-2.19125e-06,1.97065e-06,-7.94825e-09) | 5.31264e-05 | 2.94706e-06 | (-0.099235, 1.0015, 0.000108855)   | 2.166 ms   | 2.1618 ms |
| 1day    | (-4.63987e-05,2.58709e-05,-5.22848e-07) |  (-2.19125e-06,1.97065e-06,-7.94825e-09) | 5.31264e-05 | 2.94706e-06 | (0.68553, 0.948918, 0.000126035)   | 0.2 ms     | 0.1966 ms |
| 3day    | (-4.64023e-05,2.58709e-05,-5.22848e-07) |  (-2.18455e-06,1.96707e-06,-7.87578e-09) | 5.31295e-05 | 2.93967e-06 | (1.54956, -0.0257923, 0.000199878) | 0.066 ms   | 0.0627 ms |

<br/>
From previous seven different step_sizes, comparing with known position of earth after one year simulation 𝒓𝐸𝑎𝑟𝑡ℎ = (−0.194, 0.969, 0.000109), it is clear that timestep greater than 1 minute would cause significant bias for position of earth after one year's simulation. Consideing the balance between simulation run time and accuracy, the timestep setting to 1s will be reasonable.
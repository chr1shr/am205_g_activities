# Introduction to multithreading
This git repository contains the Jupyter notebook and code presented at the "Introduction to multithreading" workshop. For slides please see the "[Group Activities](https://courses.seas.harvard.edu/courses/am205/g_act/index.html#multithreading)" tab on the main website. Materials are based on [Fall 2020 workshop](https://github.com/nderr/multithreading).

The workshop contains three exercises for learning multithreading in shared memory parallelization:
- Ex 1: (demo) check the thread number of a machine
- Ex 2: (demo) parallelize a matrix multiplication routine
- Ex 3: (homework) calculating π stochastically

It covers the basics of using ```OpenMP``` in C++, ```joblib``` in Python, and vectorized ```NumPy``` to parallelize a program.

### Monitoring core usage
[htop](https://htop.dev/) is a handy utility to visualize core usage. It can really help us understand multithreading and how to parallelize our code better. Highly recommend to install it if you are a Mac or Linux user. For Windows user, you can directly use the [Get-Process Cmdlet](https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-powershell-1.0/ee176855(v=technet.10)?redirectedfrom=MSDN) or try some [alternative](https://technet.microsoft.com/en-us/sysinternals/bb842062) tools.

### Repo organization
This repo contains two C++ examples and one exercise (C++ or Python). In order to run the example code, we need to first compile the executables. Run the following commands in your terminal:
```sh
git clone https://github.com/chr1shr/am205_g_activities.git
cd am205_g_activities/multithreading
make
```
>Note: ```Makefile``` automatically sets the compiler and flags based on the operating system. If you are running on Linux, the default GNU compiler will work out of the box. If you are running on a Mac, you will need to install a C++ compiler (preferably gcc) with ```OpenMP``` support from [MacPorts](https://www.macports.org/) or [Homebrew](https://brew.sh/). This is a [tutorial](http://www.mathcancer.org/blog/setting-up-gcc-openmp-on-osx-homebrew-edition/). If you are using a higher version of gcc, you can swap out the ```g++-mp7``` for Mac or ```g++-9``` for Linux with your gcc version.

1. ```hello_world.cc```: print out "Hello world" from each thread on your computer
   ```sh
   ./hello_world
   ```
2. ```race_condition.cc```: examine the different ways to prevent race condition in multithreaded code
   ```sh
   ./race_condition <keyword>
   ```
3. ```mat_mul.cc``` and ```mat_mul.py```: in-workshop exercise to use either ```OpenMP``` in C++ or ```joblib``` in Python to parallelize a matrix multiplication routine
   ```sh
   ./mat_mul N t
   python mat_mul.py [-v] N t
   ```
   >Note: Currently the ```Makefile``` does not compile this example. Full code will be posted once the workshop has ended. You also need to [install](https://joblib.readthedocs.io/en/latest/installing.html) ```joblib``` on your computer to run the Python script.
4. ```numpy_jax.ipynb```: Some simple ```NumPy``` and ```JAX``` examples on parallelized code
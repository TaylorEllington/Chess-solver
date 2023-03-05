# Setting up
All the listed commands below can be copy-pasted assuming your shells current working directory is the root of this repo. 

### Configure
Creates a build directory `_build` and creates a series of targets. These targets can be invoked in later steps to build the main project, the tests, and the static analysis tool.

> cmake -B_build -S.

### Build the Project
To build the chess solver project and the tests
> cmake --build _build 

### Run the tests
> ctest --test-dir _build

### Run Code Coverage
There are three necessary steps to take first. The code coverage utility requires compile and run time information in order to generate a report. 
1. Open `BuildOptions.cmake` and make sure the `GCC_CODE_COVERAGE` option is set to `On`
2. Configure and Build as listed above
3. Run the tests as listed above

Once these steps are done, the following command will run the code coverage utility, remove standard library calls from the results, and create a html report you can view in a directory called `code_coverage_report` in the root directory

> cmake --build _build --target code-cov-report


### Run Static Code Analysis
The static code analysis tool used here is cppcheck. It is an open source project, so we need to download it, build it, and run it. Ive automated all of that through CMake so you don't have to deal with it. 

> cmake --build _build --target run-scans

This will take some time. On tux, the download, build, and scan takes about 5 minutes. It will go faster the second time you run it because the tool is downloaded and built already. If it gets stuck on downloading the source(which happened several times in testing, you can ctrl-c out of the step and run it again)

The results of the scan gets printed in the root of the repo in a file that has the date and time in the format "YYYYMMDD-HHMM-report.txt"

### Running the app directly
If for some reason, you want to invoke the app itself, you need a properly formatted input file, some are furnished for you in the `input/` directory, with `input/example1.txt` being based on the example in the assignment. 

First, make the executable available
>  cmake --build _build --target install

This will create a `install` directory in the root of the project. inside you will find the exe, maybe a few layers down. 

to run the executable do this:
> ./install/bin/chess-solver.exe input/example1.txt  

The app should print the output to the terminal.

# Deliverables
The deliverables of the assignment can be found in these locations:
* Source code - src/
* Test cases - src/chess-lib-tests.cpp
* Instructions - This file
* Static Analysis report and discussion of fixes - deliverables/scan.txt
* Final code coverage report - deliverables/code_cov/index.html


# Assumptions/Limitations
* The application does not aggressively check input. Putting in illegal positions may still result in output. Putting in malformed input files may result in a crash.
* Code coverage only works with GCC compilers
* Build system has been tested on Tux environment, may not work in environments with heavy customization.
* Input files will be properly formulated.
* Moves calculated only take into account what moves that piece can take in that moment. Meaning that moves that discover check, move the king into check, or require past board states (en passant, castling) will not be listed.
* Pawn promotion and under-promotion options are not listed
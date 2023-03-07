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
1. Open `CMakeLists.txt` and make sure the `GCC_CODE_COVERAGE` option is set to `ON` (it should be by default)
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
If for some reason, you want to invoke the app itself, you need a properly formatted input file, one is furnished for you in the `input/` directory, with `input/example1.txt` being based on the example in the assignment. 

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
* Sample Static Analysis report  - deliverables/20230304-2243-Report.txt
* Final code coverage report - deliverables/code_cov/index.html

# Changes made after running static analysis
The code coverage report is in the `deliverables` directory and consists of individual lines of code, annotated with the scanner's recommendations about what to fix. The report in `deliverables` is much longer than what you might see running the static scanner now, as it is from an earlier version of the project and the following changes were made:

* all the move_generator functions now take the BoardState objects by const reference
* Fixed the erroneous use of std::remove
* board_utils moves to strings is now const correct

# Code Coverage Report

There is a directory in `deliverables` that contains an up to date version of the code coverage report, it should be identical to what you can generate with the `code-cov-report` command above. This coverage report shows line, function, and branch coverage for the assignment. Note that the coverage is only reported for code exercised by the unit tests, `src/main.cpp` contains some logic and a handful of branches that do not appear in this report. They largely handle file input and invoking the main corpus of code.  

The code coverage report is formatted as a series of HTML pages, open `index.html` and browse from there. If you are generating on tux, its recommended to ftp or otherwise download the entire report directory to your local machine from tux and open locally in a browser.

# Assumptions/Limitations
* The application does not aggressively check input. Putting in illegal positions may still result in output. 
* Malformed input files may result in a crash.
* Code coverage only works with GCC compilers
* Build system has been tested on Tux environment, may not work in environments with heavy customization.
* Input files will be properly formulated.
* Moves calculated only take into account what moves that piece can take in that moment. Meaning that moves that discover check, move the king into check, or require past board states (en passant, castling) will not be listed.
* Pawn promotion and under-promotion options are not listed
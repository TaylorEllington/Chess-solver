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

Once these steps are done, the following command will run the code coverage utility, remove standard library calls from the results, and create a html report you can view.

> cmake --build _build --target code-cov-report


### Run Static Code Analysis
The static code analysis tool used here is cppcheck. It is an open source project, so we need to download it, build it, and run it. Ive automated all of that through CMake so you don't have to deal with it. 

> cmake --build _build --target run-scans

This will take some time. On tux, the download, build, and scan takes about 5 minutes. It will go faster the second time you run it because the tool is downloaded and built already.

The results of the scan gets printed in the root of the repo in a file that has the date and time in the format "YYYYMMDD-HHMM-report.txt"
# Assumptions

* Input files will be properly formulated.
* Moves calculated only take into account what moves that peice can take in that moment. Meaning that moves that create a discover check, move the king into check, or require past board states (en passant, casteling) will not be listed.
* Pawn promotions are not listed
# Automated tests framework

_fconde-p && csilva-s_

## Description

This test framework intend to help you to keep your development process healty and stable. When we develop code we tend to break things. And, as mature programmers we know that the best way to do and mantain a good work is both by documenting our project and having a quick feedback when something goes wrong at the process of growing our systems.

So here we have a helper. Think about the time spent with testing as a bigger amount of time saved from infernal helter skelter debugging sessions. The tests you make should provide you a safety net. Think about their granularity, their modularity and the strategy you use with this approach.

_Read more about different types of tests like unity, regression, functional, non-functional, black/white box and many others._

## Main structure

The test framework is autocontained at the `tests` folder. There you will find the following files:

| File | Responsability |
|---|---|
| `makefile` | Runs the tests compiling them independently and sends a signal of _PASS_ or _FAIL_ at the very end |
| `test-{file_name}.c` | Contain a _main_ function that runs tests over the given _file_name_. You can -- and should -- have more than one test function for each tested file, running them on the _main_ function. |
| `tests.h` | Here is set the header files from the test project and from the tested project in order to run it. Is set also the resources for the testing project. |
| `{name}_report.log` | Report log file. It contains the results of the tests executed on a given run. |

## makefile

The main commands/recipes are:

- test: it's the core of this test system. It

  - creates the log file, 
  - compile and run each unit test file individually writting the results at the mentioned file.
  - When done, it counts the _PASS_ and _FAIL_ and also writes it at the log file. 
  - Sends a signal of _success_ or _failure_ according to the general result (passes only if all tests are successful). This final signal is sent in order to trigger any automated CI/CD process if we want so;

- run_test_bins: is responsible for run each unit test file independently. When each test runs it tries to compile. If so, it writes the result on the log file. If it doesn't, writes _ERROR_ at the log file to differ it from the test _FAIL_ (when it compiles and runs but the result is out of the expected).

*_Remember to set the directories folder for the project to be tested. Also, keep the good practice to keep the test and to-be-tested files explicitly written at their variable on the makefile [we should make it more intelligent soon]._

## Main commands

**make test** -> Run all unit tests registered.

**make clean** -> Simple clear of utilities like _LIBFT_ (if used).

**make fclean** -> Full clean included compiled files and logs.
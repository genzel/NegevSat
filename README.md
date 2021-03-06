NegevSat
========

NegevSat project by Ben Gurion University.

Environment Setup for windows:

Detailed instructions can be found here: http://gaisler.com/doc/gr_lide.pdf

1. Download GRTools from http://www.gaisler.com/index.php/products?task=view&id=272
2. Install the file
3. Assert that "Path" environment variable was updated correctly - it should contain the following paths:
    * mkprom2
    * tsim
    * grmon
    * rtems
    * sparc-elf
    * bin folder of the installation (default is c:\opt\bin)
if any of the paths are not correct fix it manually.
NOTE: if you wish to update any of these tools, you should also update the "Path" of your windows.

Quick hello-world c++ application:

1. Run Eclipse which was installed in the previous tutorial
2. Create a new C++ project:<br>
    2.1 File -> new -> C++ project<br>
    2.2 Choose a name and type it in the "Project name" field<br>
    2.3 Under Project type select "Hello World C++ Project"<br>
    2.4 Under Toolchains select SPARC RTEMS<br>
    2.5 Press finish<br>
3. Setting compiler flags:<br>
    3.1 Right click on the project in the project explorer and press on properties<br>
    3.2 Under C/C++ Build -> Settings -> SPARC RTEMS C++ Compiler -> Hardware mark the V8 Extension<br>
4. Setting Debug configuration:<br>
    4.1 Go to Run -> Debug Configurations -> LEON C/C++ application and add your project there.<br>
    4.2 Once your project appears under LEON C/C++ application click on it and go to Debugger window.<br>
    4.3 Add external target by clicking on "New..." near the External target field<br>
    4.4 Make sure the target's name is TSIM2 and Browse to the location of the TSIM simulator -<br>
        the default location is C:\opt\tsim-eval\tsim\win32\tsim-leon3.exe<br>
    4.5 Press on finish<br>
5.  Debug your project and see the output of TSIM in your console

/*

* ASSIGNMENT 3 : PGM IMAGE PROCESSING
*Read me file for CSC3022F ASSIGNMENT 3
* AUTHOR : MKXTSH013
* YEAR : 2022


*/



/*** INSTRUCTIONS TO COMPILE **/

1. make sure you're inside the package directory
2. Type make clean to remove any .o files
3. Type make in terminal for compiling
4. Type make Test for compiling the unix test

/*** INSTRUCTIONS TO RUN **/
1. make run // see makeFile for a example of run or use the command below
2. make test // running the unit test

./findcomp [options] <inputPGMfile>
#####[options]
-s int int (-s min max) ; set the minimum and maximum valid components size
[min default = 3, max = image width*img height i.e. unlimited]

-t int set the threshold for component detection (default=128, limit to [0. . . 255])

-p print out all the component data (entries do not have to be sorted) as well as the total
component number and the sizes of the smallest and largest components.

-w outPGMfile write out all retained components (as foreground/background pixels)
to a new PGM file, outPGMfile. (Example for -w : ./findcomp [options]  <outPGMfile> <inputPGMfile>)

-c outPGMfile write out all retained components (as coloured pixels -> each component with its own colour)
to a new PGM file, outPGMfile. (Example for -w : ./findcomp [options]  <outPGMfile> <inputPGMfile>)

####<inputPGMfile>
input file

/*** FILES **/

PGMImageProcessor.h  &PGMImageProcessor.cpp //Packages ConnectedComponents as a vector and provide functions to manipulate the components

ConnectedComponents.h & ConnectedComponents.cpp  //Helper class to encapsulate information about a connected component.

findcomp.cpp //executable

UnixTest.cpp //unit tests

The following is an example of how to run the code:
./findcomp -w new.pgm -c chess.pgm -s 2 5 -t 180 coins.pgm




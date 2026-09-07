//the first forward slash would be invalid code, but it is followed by another slash which tells the preprocessor not to pass this line to the compiler
#include <iostream>
/* <-- this tells the preprocessor not to pass text to the compiler until it reaches the */ //symbol
/*

the # symbol tells the pre-processor that the rest of the line is a direct instruction for it to execute, the pre-processor (as it sounds) reads the file before the compiler
and processes your code from human readable syntax to something that can be more easily processed by the compiler. It does things like removing whitespace, but the # symbol 
tells the preprocessor to execute the following command rather than pass the line to the compiler.

include tells the preprocessor to splice the following library into the code passed on to the compiler, for practical purposes it allows the programmer to use common tools
that may be outside the scope of this file.

< the less than operator lets the preprocessor know that it should save all following characters until it reaches the > symbol. iostream: I looked this up but I didn't 
understand what the preprocessor does here. in layman's terms it searches through its list of libraries for the name "iostream" and merges the contents of that library file  
to the begining of the code it passes on to the compiler.

*/
// include specific things from libraries
using std::cout, std::endl;
/*
the using keyword tells the compiler to search through the spliced library for the following objects and save them as "variables" to be more easily accessed later. 

std::cout and std::endl are objects within the iostream library. I'm not entirely sure what goes on here but for practical purposes this tells the compiler from now on, when it
sees cout and endl to treat them as std::cout and std::endl respectively.

the ; symbol tells the compiler that the statement is complete. This is the end of the "sentence."
*/

int main(){
/*
int tells the compiler that whatever object follows this keyword will be of an integer type AKA a whole number (positive or negative)

main is the binding of the object of int type

the ( symbol tells the compiler that the object is a function and that any characters following will be input parameters for the function until the closing parentheses symbol )
the { symbol tells the compiler that the following words preceding the } symbol will be instructions to carry out every time the function is called

these comments are of course not included in this and are removed by the preprocessor

*/

    cout << "Hello World!" << endl;
    return 0;
/*
cout tells the compiler to pull up the cout object, which is a copy of the std::cout object as explained earlier

<< tells the compiler to push the following object into the cout object so it can be printed. I don't know how this works, from what I can tell it takes objects, turns them into strings, and stores them into a buffer
    to be all printed at once, this lowers the number of times the program would have to print to the screen
the " symbol tells the compiler that the following text preceding the closing " is to be treated as a String, which is a collection of characters saved under one object
the << followed by endl pushes a newline character and 'flushes' the buffer of the std::cout object, meaning it prints everything in the buffer and clears it. Normally the buffer flushes(prints and clears) when the 
    program ends or when it becomes full (the size is compiler dependent), using the endl (operator?) forces it to flush immediately.

*/    
}//this } marks the end of the main function

//sources, I googled most of this
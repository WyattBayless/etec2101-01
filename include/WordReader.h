#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class WordReader
{
protected:

	/// <summary>
	/// This is the variable that will hold the file path input
	/// </summary>
	std::string file_path_input;

	/// <summary>
	/// This is the variable that will hold our randomly chosen word
	/// </summary>
	std::string random_word;

	/// <summary>
	/// This is a variable that will hold the file length in bytes
	/// </summary>
	size_t file_len;

	std::ifstream fp;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@ CONSTRUCTORS / OPERATORS        @
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
public:

	/// <summary>
	/// The default constructor
	/// </summary>
	WordReader();

	/// <summary>
	/// The Destructor
	/// </summary>
	~WordReader();

	/// <summary>
	/// This is a constuctor that takes a string for the file path
	/// </summary>
	WordReader(std::string file_path);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@ OTHER METHODS (alphabetical)            @
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
public:

	std::string getWord();


};
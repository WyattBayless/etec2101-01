// Examples of using cin/cout, also file input/output, stringstreams

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	int x = 42;
	float y;
	std::string s;
	std::cout << "x = " << x << "\n";   //CHEVRON goes to the left (<<) -- output
	std::cout << "Enter an integer value for x: ";
	std::cin >> x;
	if (std::cin.fail())
	{
		std::cout << "Invalid interger. Setting x to -1\n";
		x = -1;
		// Note2: cin is in an "error state" -- we've handled it. Telll cin all's good by 
		// Note3: Make sure to do clear before ignore
		std::cin.clear();
		// Note, the \n is still in the cin buffer. We don't want it there
		std::cin.ignore(1, '\n');		// Ignore up to 1 char until \n is seen
	}

	// If we just want a single word
	//std::cout << "Enter a string value for s (no whitespace): ";
	//std::cin >> s;
	//std::cin.ignore(100000, '\n');

	// If we want any type of text
	// Note4: Since we have some input already, there's likely a newline still
	// in the buffer
	std::cin.ignore(100000, '\n');
	std::cout << "Enter a string value for s: ";
	std::getline(std::cin, s);

	std::cout << "Enter a float value for y: ";
	std::cin >> y;
	
	std::cout << "You entered\n\tx=" << x << "\n\ty=" << y << "\n\ts='" << s << "'\n";

	return 0;
}
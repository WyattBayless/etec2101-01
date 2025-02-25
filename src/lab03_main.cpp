#include <array_list.h>

// This is pretty unfinished and unpolished. I tried to get everything working properly but some errors kept
// getting in my way, and obviously my test isn't very good. I'll be sure to manage my time better next time.



int main(int argc, char** argv)
{
	int x = 42;			// x holds 42 after this line
	int y = ++x;		// x holds 43 and y holds 43 after this line.
	int z = x++;		// x holds 44 and z holds 43


	// An example of an initializer-list constructor usage -- ONLY works when constructing
	ssuds::ArrayList<std::string> slist = { "abe", "bob", "carl", "diane" };
	//ssuds::ArrayList<std::string> slist {"abe", "bob", "carl", "diane"}; // alternate syntax -- same thing
	slist.append("erin");
	slist.append("frank");


	for (unsigned int i = 0; i < slist.size(); i++)
		std::cout << slist[i] << "\n";
	std::cout << slist << "\n";					// [abe, bob, carl, diane, erin, frank]

	std::cout << "iterator\n";
	ssuds::ArrayList<std::string>::ArrayListIterator slist_iterator;
	slist_iterator = slist.begin();
	while (slist_iterator != slist.end())
	{
		// User can do this
		(*slist_iterator) += "x";			// User can do this...that's why operator* needs
		// to return a reference
		std::string cur_string = *slist_iterator;
		std::cout << "\t" << cur_string << "\n";
		++slist_iterator;
	}

	slist_iterator = slist.begin();
	ssuds::ArrayList<std::string>::ArrayListIterator other_it = ++slist_iterator;
	other_it = slist.begin() + 2;

	// This comes for "free" if you get lines 11-18 to work
	std::cout << "for-each\n";
	for (std::string s : slist)
		std::cout << "\t" << s << "\n";
}
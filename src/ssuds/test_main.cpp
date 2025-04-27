// main.cpp
#include <linked_list.h>
#include <iostream>

int main()
{
	ssuds::LinkedList<std::string> llist;

	llist.append("Bob");
	llist.append("Carl");
	llist.append("Doug");
	llist.insert("Christine", 2);    // Takes Doug's spot, moves him "down"
	// [Bob, Carl, Christine, Doug]

	for (unsigned int i = 0; i < llist.size(); i++)
	{
		std::cout << i << "\t" << llist[i] << "\n";    // Much more expensive than ArrayList
	}													// ArrayList [] operator is O(1)
														// LinkedList [] operator is O(n)


	std::cout << llist.size() << "\n";		// 4

	ssuds::LinkedList<std::string>::LinkedListIterator it = llist.begin();
	while (it != llist.end())
	{
		std::string temp = *it;
		std::cout << temp << "\n";
		++it;
	}

	for (std::string s : llist)
		std::cout << s << "\n";

}
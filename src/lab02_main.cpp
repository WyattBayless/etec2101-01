
#include <iostream>
#include <fstream>
#include <array_list.h>

// Running short on time so, once again, I don't have doxygen. I'll be sure to add it, it may even be in github by the time you look
// Also, the test may be missing a few things like testing a few very specific cases within functions, different data types
// All those should work though I just don't have them explicitly added

int main()
{
	ssuds::ArrayList<int> ilist;
	// Test 1: checking capacity before adding items
	std::cout << "capacity before adding 5 items=" << ilist.capacity() << "\n" << std::endl;
	ilist.append(42);
	ilist.append(43);
	ilist.append(44);
	ilist.prepend(41);
	ilist.prepend(40);

	// Test 2: Check if append and prepend work properly
	std::cout << "Checking to see if prepend and append put items in correct places\n\n";
	for (int i = 0; i < ilist.size(); i++)
		std::cout << "ilist[" << i << "] = " << ilist.at(i) << "\n";

	// [40, 41, 42, 43, 44]
	ilist.append(40);
	ilist.append(43);
	ilist.append(99);
	ilist.append(43);
	ilist.append(98);
	// [40, 41, 42, 43, 44, 40, 43, 99, 43, 98]

	// Test 3: seeing if array size returns correctly
	// Outputting number of items in array to screen
	std::cout << "\nsize=" << ilist.size() << "\n" << std::endl;

	// Test 4: checking capacity after adding some items
	std::cout << "capacity after adding more than 5 items=" << ilist.capacity() << "\n" << std::endl;

	// Test 5: checking find function
	// Outputting first index where 43 is found after given start index. Return -1 if not found
	std::cout << "First index containing 43, starting at 0= " << ilist.find(43) << std::endl;					// Starts at 0. Should return 3
	std::cout << "First index containing 43, starting at 4= " << ilist.find(43, 4) << std::endl;					// Starts at 4. Should return 6
	std::cout << "First index containing 43, starting at 7= " << ilist.find(43, 7) << std::endl;					// Starts at 7. Should return 8
	std::cout << "First index containing 43, starting at 9= " << ilist.find(43, 9) << std::endl;					// Starts at 9. Should return -1
	std::cout << "First index containing 104, starting at 0= " << ilist.find(104) << "\n" << std::endl;			// Starts at 0, looks for 104. Should return -1

	// Test 6: checking output function by outputting to screen and as a bonus reassures second round of appending worked properly
	// Outputting full array to screen
	std::cout << "Output of ilist: ";
	ilist.output(std::cout);			// [40, 41, 42, 43, 44, 40, 43, 99, 43, 98]
	std::cout << "\n";

	// Test 7: checking insert function by changing an element in array
	// Should now be [40, 41, 42, 43, 44, 45, 40, 43, 99, 43, 98]
	ilist.insert(45,5);
	std::cout << "\n45 inserted\n";
	std::cout << "\nOutput of ilist: ";
	ilist.output(std::cout);

	// Test 8: testing output function by outputting to file
	std::ofstream fout("..\\..\\media\\test.txt");
	ilist.output(fout);

	// Test 9: testing remove function by removing newly added element
	// Should now be [40, 41, 42, 43, 44, 40, 43, 99, 43, 98]
	ilist.remove(5);
	std::cout << "\n\n45 removed\n";
	std::cout << "\nOutput of ilist: ";
	ilist.output(std::cout);

	// Test 10: testing remove all function by removing all occurrences of 43
	// Should now be [40, 41, 42, 44, 40, 99, 98]
	std::cout << "\n\nAll 43's removed\n";
	std::cout << "Amount removed:" << ilist.remove_all(43) << std::endl;
	std::cout << "\nOutput of ilist: ";
	ilist.output(std::cout);

	// Test 11: removing more items to test capacity shrink
	ilist.remove(6);
	ilist.remove(5);
	ilist.remove(4);
	ilist.remove(3);
	ilist.remove(2);
	ilist.remove(1);

	std::cout << "\n\nAll but 1 item removed\n";
	std::cout << "\nOutput of ilist: ";
	ilist.output(std::cout);
	std::cout << "\n\ncapacity after removing enough to shrink=" << ilist.capacity() << std::endl;

	// Test 12: testing at function and out_of_range. Uncomment lines below to trigger error
	//std::cout << "\nItem at index 1:" << ilist.at(1) << std::endl;			// Index 1 currently has nothing, should trigger out_of_range
	//std::cout << "\nItem at index -1:" << ilist.at(-1) << std::endl;			// Index cannot be negative, should trigger out_of_range
	std::cout << "\nItem at index 0: " << ilist.at(0) << std::endl;
}
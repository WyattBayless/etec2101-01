#include <array_list.h>
#include <iostream>



int main(int argc, char** argv)
{
	ssuds::ArrayList<float> flist = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };
	
	std::cout << "test1 (initializer-list):\n=====\n\t";	// test1 (initializer-list):
	flist.output(std::cout);	std::cout << "\n";			// =====
															//     [1.1, 2.2, 3.3, 4.4, 5.5, 6.6]




	std::cout << "\ntest2 (stream operator):\n=====\n";		// test2 (stream output)
	std::cout << "\t" << flist << "\n";						// =====
															//     [1.1, 2.2, 3.3, 4.4, 5.5, 6.6]




	std::cout << "\ntest3 ([] operator):\n=====\n";			// test3 ([] operator)
															// =====
	try														
	{
		std::cout << flist.at(100) << "\n";
		std::cout << "\tat exception NOT caught!\n";        // <- WE SHOULD NOT SEE THIS!!!
	}
	catch (std::out_of_range& e)
	{
		std::cout << "\tat exception caught properly\n";	//     at exception caught properly
		std::cout << "\t" << e.what() << "\n";				//     invalid index(100)
	}
	flist[0] = 1.11f;
	std::cout << "\tflist[0]=" << flist[0] << "\n";			//     flist[0] = 1.11
	std::cout << "\tflist[1]=" << flist[1] << "\n";			//     flist[1] = 2.2



	ssuds::ArrayList<float> flist2(flist);
	ssuds::ArrayList<float> flist3 = flist;
	std::cout << "\ntest4 (copy-constructor):\n=====\n";	// test4 (copy-constructor)
															// =====
	std::cout << "\tflist=" << flist << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6]
	std::cout << "\tflist2=" << flist2 << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6]
	std::cout << "\tflist3=" << flist3 << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6]
	flist.append(7.7f);
	flist2[1] = 999.99f;
	flist3.clear();
	std::cout << "\tflist=" << flist << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7]
	std::cout << "\tflist2=" << flist2 << "\n";				//     [1.11, 999.99, 3.3, 4.4, 5.5, 6.6]
	std::cout << "\tflist3=" << flist3 << "\n";				//     []




	std::cout << "\ntest5 (= operator):\n=====\n";			// test5 (= operator)
	ssuds::ArrayList<float> flist4;							// =====
	flist4 = flist2 = flist;
	flist.clear();
	flist3.append(8.8f);
	flist3.append(9.9f);
	std::cout << "\tflist=" << flist << "\n";				//     []
	std::cout << "\tflist2=" << flist2 << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7]
	std::cout << "\tflist3=" << flist3 << "\n";				//     [8.8, 9.9]
	std::cout << "\tflist4=" << flist4 << "\n";				//     [1.11, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7]
	flist3 = flist3;
	std::cout << "\tflist3=" << flist3 << "\n";				//     [8.8, 9.9]


	// I define "basic iterator" as supporting a for-each loop.  This requires 
	// begin and end methods in ArrayList, and *, !=, and ++(prefix) operators in the iterator class
	// The two loops here are functionally identical
	std::cout << "\ntest6 (basic iterator):\n=====\n\t";	// test6 (basic iterator):
	for (float f : flist2)									// =====
		std::cout << f << " ";								//     1.11 2.2 3.3 4.4 5.5 6.6 7.7
	std::cout << "\n\t";
	ssuds::ArrayList<float>::ArrayListIterator it = flist2.begin();
	while (it != flist2.end())								//     1.11 2.2 3.3 4.4 5.5 6.6 7.7
	{
		std::cout << *it << " ";
		++it;
	}

	std::cout << "\n\ntest7 (other iterator):\n=====\n";	// test7 (other iterator):
	it = flist2.begin();									// =====
	std::cout << "\t*it=" << *it << "\n";					//     *it=1.11
	ssuds::ArrayList<float>::ArrayListIterator it2, it3;
	it2 = ++it;
	it3 = it++;
	std::cout << "\t*it2=" << *it2 << "\n";					//     *it2=2.2
	std::cout << "\t*it3=" << *it3 << "\n";					//     *it3=2.2
	std::cout << "\t*it=" << *it << "\n";					//     *it=3.3
	it2 = it + 2;
	std::cout << "\t*it2=" << *it2 << "\n";					//     *it2=5.5
	it2 = it + (-1);
	std::cout << "\t*it2=" << *it2 << "\n";					//     *it2=2.2
	it2 = it - 1;
	std::cout << "\t*it2=" << *it2 << "\n";					//     *it2=2.2
	it2 = it + 20;
	std::cout << "\tit2 == flist2.end() is " << (it2 == flist2.end()) << "\n";	//     it2 == flist2.end() is 1
	it = flist.begin();
	std::cout << "\tit == flist.end() is " << (it == flist.end()) << "\n";	//     it == flist.end() is 1
	it = flist.begin();
	it2 = flist2.begin();
	std::cout << "\tit == it2 is " << (it == it2) << "\n";	//     it == it2 is 0



	std::cout << "\ntest8 (reverse-iteration):\n=====\n\t";	// test8 (reverse-iteration):
	it = flist2.rbegin();									// =====
	while (it != flist2.rend())								//      7.7 6.6 5.5 4.4 3.3 2.2 1.11
	{
		std::cout << *it << " ";
		it++;		// <- many people want to do a -- here, but this is the proper way
	}

	// This is one way to test the move-constructor
	std::cout << "\ntest9 (move semantics):\n=====\n";		// test9 (move semantics)
	std::cout << "\tflist2=" << flist2 << "\n";				//      flist2=[7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.11]
	ssuds::ArrayList<float> flist5(std::move(flist2));
	std::cout << "\tflist2=" << flist2 << "\n";				//      flist2=[]
	std::cout << "\tflist5=" << flist5 << "\n";				//      flist5=[7.7, 6.6, 5.5, 4.4, 3.3, 2.2, 1.11]


	// Testing the new find/remove variants (I kept the old versions for <Lab3 code)
	std::cout << "test10 (find/remove variants):\n=====\n";	// test10 (find/remove variants)
															// ======
	flist5 = ssuds::ArrayList<float>{ 4.0f, 3.0f, 3.0f, 4.0f, 5.0f, 3.0f, 4.0f, 3.0f, 4.0f };
	it = flist5.find(4.0f, flist5.begin());					//     removed an occurrence of 4.0
	while (it != flist5.end())								//     removed an occurrence of 4.0
	{														//     removed an occurrence of 4.0
		std::cout << "\tremoved an occurrence of 4.0\n";		//     removed an occurrence of 4.0
		it = flist5.remove(it);
		it = flist5.find(4.0f, it);
	}
	std::cout << "\tflist5=" << flist5 << "\n";				//     flist5=[3.0, 3.0, 5.0, 3.0, 3.0]
	it = flist5.find(3.0f, flist5.rbegin());				//     removed an occurrence of 3.0
	while (it != flist5.rend())								//     removed an occurrence of 3.0
	{														//     removed an occurrence of 3.0
		std::cout << "\t(backwards) removed an occurrence of 3.0\n";
		it = flist5.remove(it);								//     removed an occurrence of 3.0
		it = flist5.find(3.0f, it);
	}
	std::cout << "\tflist5=" << flist5 << "\n";				//     flist5=[5.0]
	return 0;
}
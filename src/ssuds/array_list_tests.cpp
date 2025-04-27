#include <gtest/gtest.h>
#include <array_list.h>

#define EXECUTE_ARRAY_LIST_TESTS 1
#if EXECUTE_ARRAY_LIST_TESTS

// Do you understand the difference betweeen a Fixture (a class derived from ::testing::Test),
// and a test-function?  They're almost identical -- the advantage of a fixture is you can put
// common code in there (like making an ArrayList with a few items in it) without having to put
// that code explicitly in each test case.
class ArrayListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.append("B");
		slist2.append("C");
		slist2.prepend("A");
		slist2.insert("D", 3);
	}

	void TearDown() override
	{

	}


	ssuds::ArrayList<std::string> slist1;
	ssuds::ArrayList<std::string> slist2;
	ssuds::ArrayList<int> ilist;
};

TEST_F(ArrayListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
	EXPECT_EQ(ilist.size(), 0);
}


TEST_F(ArrayListTestFixture, AddingItems)
{
	ASSERT_EQ(slist2.size(), 4);
	EXPECT_EQ(slist2[0], "A");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_EQ(slist2[2], "C");
	EXPECT_EQ(slist2[3], "D");
}


TEST_F(ArrayListTestFixture, MoreInsert)
{
	slist2.insert("pre_A", 0);			// [pre_A, A, B, C, D]
	slist2.insert("A2", 2);				// [pre_A, A, A2, B, C, D]
	slist2.insert("post_D", 6);			// [pre_A, A, A2, B, C, D, post_D]

	EXPECT_EQ(slist2.size(), 7);
	EXPECT_EQ(slist2.at(0), "pre_A");
	EXPECT_EQ(slist2.at(1), "A");
	EXPECT_EQ(slist2.at(2), "A2");
	EXPECT_EQ(slist2.at(3), "B");
	EXPECT_EQ(slist2.at(4), "C");
	EXPECT_EQ(slist2.at(5), "D");
	EXPECT_EQ(slist2.at(6), "post_D");
}


TEST_F(ArrayListTestFixture, Growing)
{
	EXPECT_EQ(ilist.size(), 0);
	unsigned int cap = ilist.capacity();
	for (unsigned int i = 0; i < cap + 1; i++)
		ilist.append(1);
	EXPECT_EQ(ilist.size(), cap + 1);
	EXPECT_GT(ilist.capacity(), cap);
	cap = ilist.capacity();
	ilist.clear();
	EXPECT_LT(ilist.capacity(), cap);
}


TEST_F(ArrayListTestFixture, Finding)
{
	for (int i : {10, 7, 10, 10, 9, 10, 5, 10})
		ilist.append(i);

	int index = ilist.find(7);
	EXPECT_EQ(index, 1);
	index = ilist.find(10, 0);
	for (int expected_index : {0, 2, 3, 5, 7})
	{
		EXPECT_EQ(index, expected_index);
		index = ilist.find(10, index + 1);
	}

	EXPECT_EQ(index, -1);
}


TEST_F(ArrayListTestFixture, Remove)
{
	unsigned int cap = slist2.capacity();
	unsigned int num_added = 0;
	while (slist2.capacity() == cap)
	{
		num_added++;
		slist2.append("X");
	}
	unsigned int s = slist2.size();
	std::string temp = slist2.remove(0);
	EXPECT_EQ(temp, "A");
	EXPECT_EQ(slist2.size(), s - 1);

	int num = slist2.remove_all("X", true);
	EXPECT_EQ(num, num_added);

	// Testing shrink
	// ...first, make sure we trigger two grows
	int grows = 0;
	cap = ilist.capacity();
	while (grows < 2)
	{
		ilist.append(99);
		if (ilist.capacity() > cap)
		{
			grows++;
			cap = ilist.capacity();
		}
	}
	// Remove the 99's, which should make the list empty
	ilist.remove_all(99);
	EXPECT_LT(ilist.capacity(), cap);
}


TEST_F(ArrayListTestFixture, Reserve)
{
	unsigned int cap = ilist.capacity();
	ilist.reserve(cap + 100);
	EXPECT_GE(ilist.capacity(), cap + 100);
}


TEST_F(ArrayListTestFixture, AtVsBrackets)
{
	EXPECT_EQ(slist2.at(1), "B");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_THROW(slist2.at(slist2.size()), std::out_of_range);

	slist2[0] = "Anew";
	EXPECT_EQ(slist2[0], "Anew");
	EXPECT_EQ(slist2.at(0), "Anew");
	slist2.at(0) = "Anew2";
	EXPECT_EQ(slist2[0], "Anew2");
	EXPECT_EQ(slist2.at(0), "Anew2");
}


TEST_F(ArrayListTestFixture, EmptyManualIteration)
{
	ssuds::ArrayList<std::string>::ArrayListIterator it = slist1.begin();
	ssuds::ArrayList<std::string>::ArrayListIterator it_end = slist1.end();
	ASSERT_EQ(it, it_end);
}


TEST_F(ArrayListTestFixture, ManualIteration)
{
	ssuds::ArrayList<std::string>::ArrayListIterator it = slist2.begin();
	ssuds::ArrayList<std::string>::ArrayListIterator it_end = slist2.end();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, "A");
	val2 = *it;
	++it;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val2, "B");
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4, "D");
	EXPECT_EQ(it, it_end);
}

TEST_F(ArrayListTestFixture, PrettyIteration)
{
	int i = 0;
	for (std::string s : slist2)
	{
		if (i == 0)
			EXPECT_EQ(s, "A");
		else if (i == 1)
			EXPECT_EQ(s, "B");
		else if (i == 2)
			EXPECT_EQ(s, "C");
		else
			EXPECT_EQ(s, "D");
		i++;
	}
}


TEST_F(ArrayListTestFixture, OS_Stream)
{
	std::stringstream ss;
	ss << slist1;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(std::string());
	ss << slist2;
	EXPECT_EQ(ss.str(), "[A, B, C, D]");
}


TEST_F(ArrayListTestFixture, CopyConstructor)
{
	ssuds::ArrayList<std::string> slist_copy1 = slist2;
	ssuds::ArrayList<std::string> slist_copy2(slist2);
	ASSERT_EQ(slist_copy1.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	slist2.remove(0);
	EXPECT_EQ(slist_copy1.size(), 4);

	// Same thing, really, but just to make sure...
	ASSERT_EQ(slist_copy2.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy2.size(), 4);
}


TEST_F(ArrayListTestFixture, Assignment)
{
	ssuds::ArrayList<std::string> slist3;
	slist3.append("X");
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], "X");
	slist3 = slist2;
	ASSERT_EQ(slist3.size(), 4);
	EXPECT_EQ(slist3[0], "A");
	EXPECT_EQ(slist3[1], "B");
	EXPECT_EQ(slist3[2], "C");
	EXPECT_EQ(slist3[3], "D");
	slist2.remove(0);
	EXPECT_EQ(slist3.size(), 4);

	// This one is kind of sneaky!
	// ... make a copy of slist2 manually
	slist3.clear();
	for (unsigned int i = 0; i < slist2.size(); i++)
		slist3.append(slist2[i]);
	// ... now do the thing
	slist2 = slist2;		// Could cause problems if not accounted for!
	// ...slist2 and slist3 should be the same
	ASSERT_EQ(slist2.size(), slist3.size());
	for (unsigned int i = 0; i < slist3.size(); i++)
		EXPECT_EQ(slist2[i], slist3[i]);

}


TEST_F(ArrayListTestFixture, InitializerListConstructor)
{
	ssuds::ArrayList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}


ssuds::ArrayList<float> move_func()
{
	ssuds::ArrayList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}

TEST_F(ArrayListTestFixture, MoveConstructor)
{
	ssuds::ArrayList<float> my_arr = move_func();
	ASSERT_EQ(my_arr.size(), 2);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
	my_arr.remove(0);
	EXPECT_EQ(my_arr.size(), 1);
}


// I'm not sure why this is such a troubling case.  Possibly something to
// do with the small-string optimizaiton (SSO)?
TEST_F(ArrayListTestFixture, CustomStrings)
{
	std::vector<std::string> vlist;
	ssuds::ArrayList<std::string> slist;
	char temp_cstr[4] = { '\0', '\0', '\0', '\0' };
	for (int i = 0; i < 26; i++)
	{
		temp_cstr[0] = temp_cstr[1] = temp_cstr[2] = i + 'a';
		std::string temp_cpp_str(temp_cstr);

		slist.append(temp_cpp_str);
		vlist.push_back(temp_cpp_str);

		temp_cstr[0] = temp_cstr[1] = temp_cstr[2] = i + 'A';

		slist.append(temp_cpp_str);
		vlist.push_back(temp_cpp_str);
	}

	ASSERT_EQ(vlist.size(), slist.size());

	for (int i = 0; i < vlist.size(); i++)
		ASSERT_EQ(vlist[i], slist[i]);
}

#endif
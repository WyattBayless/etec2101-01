#include <gtest/gtest.h>
#include <array_list_utility.h>

TEST(ArrayListUtilityTests, ShuffleTests)
{
	// We can't know where the elements will end up but we do
	// know each should be in a DIFFERENT spot than when we started if doing a derangement
	// I couldn't think of a good way to test the non-derangement case...
	ssuds::ArrayList<int> ilist;
	for (int i = 0; i < 1000; i++)
		ilist.append(i);
	ssuds::shuffle<int>(ilist, true);

	for (int i = 0; i < 1000; i++)
		ASSERT_NE(ilist[i], i);
}


TEST(ArrayListUtilityTests, QuickSort)
{
	ssuds::ArrayList<int> ilist;
	for (int i = 0; i < 500; i++)
		ilist.append(i);

	ssuds::shuffle<int>(ilist, false);

	ssuds::quicksort(ilist, ssuds::SortOrder::ASCENDING);
	for (int i = 0; i < 500; i++)
		ASSERT_EQ(ilist[i], i);

	ssuds::quicksort(ilist, ssuds::SortOrder::DESCENDING);
	for (int i = 0; i < 500; i++)
		ASSERT_EQ(ilist[i], 499 - i);

	// Shuffle again and make sure descending still works
	ssuds::shuffle(ilist, false);
	ssuds::quicksort(ilist, ssuds::SortOrder::DESCENDING);
	for (int i = 0; i < 500; i++)
		ASSERT_EQ(ilist[i], 499 - i);
}



TEST(ArrayListUtilityTests, BubbleSort)
{
	ssuds::ArrayList<int> ilist;
	for (int i = 0; i < 1000; i++)
		ilist.append(i);

	ssuds::shuffle<int>(ilist, false);

	ssuds::bubblesort(ilist, ssuds::SortOrder::ASCENDING);
	for (int i = 0; i < 1000; i++)
		ASSERT_EQ(ilist[i], i);

	ssuds::bubblesort(ilist, ssuds::SortOrder::DESCENDING);
	for (int i = 0; i < 1000; i++)
		ASSERT_EQ(ilist[i], 999 - i);

	// Shuffle again and make sure descending still works
	ssuds::shuffle(ilist, false);
	ssuds::bubblesort(ilist, ssuds::SortOrder::DESCENDING);
	for (int i = 0; i < 1000; i++)
		ASSERT_EQ(ilist[i], 999 - i);
}


TEST(ArrayListUtilityTests, BinarySearch)
{
	ssuds::ArrayList<float> flist;
	for (int i = 0; i < 1000; i++)
		flist.append(i + 0.5f);

	for (int i = 0; i < 1000; i++)
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, i + 0.5f);
		ASSERT_EQ(result, i);
	}

	// Give some values that should return -1
	for (int i = 0; i < 1000; i++)
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, i + 0.6f);
		ASSERT_EQ(result, -1);
		result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, i + 0.4f);
		ASSERT_EQ(result, -1);
	}
	for (float f : {-193.7f, 40000.0f})
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, f);
		ASSERT_EQ(result, -1);
	}


	// Reverse the list
	for (int i = 0; i < 1000; i++)
		flist[i] = (999 - i) + 0.5f;


	for (int i = 0; i < 1000; i++)
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::DESCENDING, i + 0.5f);
		ASSERT_EQ(result, 999 - i);
	}

	
	// Give some values that should return -1
	for (int i = 0; i < 1000; i++)
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, i + 0.6f);
		ASSERT_EQ(result, -1);
		result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, i + 0.4f);
		ASSERT_EQ(result, -1);
	}
	for (float f : {-193.7f, 40000.0f})
	{
		int result = ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, f);
		ASSERT_EQ(result, -1);
	}
}
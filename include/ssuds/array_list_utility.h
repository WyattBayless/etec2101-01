#pragma once

#pragma once
#include <array_list.h>
#include <random>
#include <functional>			// For lambda variables (see the long note below)

// Note: The way I described the structure of these functions in class was to recommend 
// a few functions for things like quicksort (one that the user calls, one for doing the recursion
// and one that does the partition).  The "problem" with this is those functions are visible to the user
// and they might inadvertently use them wrong.  What I'm doing here is to use a "lamda function"
// variable, which in C++ is the only way to write a nested function.  If you take python, it is completely 
// legal to do this:
// 
// def some_func(a):
//      x = 42
//      def nested_func():
//          # This function has access to x 
//          nonlocal x       # a bit like global statement, but less "strong"
//          x += a
//      nested_func()
//
// Why do this?  The outside user doesn't have access to nested_func, only some_func.  I want something like this
// in C++, but currently the only option is a "lambda function" variable.  It's a bit like a function pointer
// in C in some ways, but actually closer to what's going on in python above. What you'll see in my code is two 
// nested functions for quicksort (one to break up the portions recursively, and one to do the pivot operation)


namespace ssuds
{
	/// <summary>
	/// This is how the user tells us which type of sorting they want.  
	/// ASCENDING = small => big
	/// DESCENDING = big => small
	/// </summary>
	enum class SortOrder { ASCENDING, DESCENDING };

	
	/// <summary>
	/// Performs a recursive in-place sorting of the passed list using QuickSort
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're using</typeparam>
	/// <param name="alist">The ArrayList to be sorted</param>
	/// <param name="type">The desired sort-order</param>
	/// <returns></returns>
	template <class T>
	void quicksort(ArrayList<T>& alist, SortOrder type)
	{
		// Reference: https://www.geeksforgeeks.org/quick-sort/

		// This is making a function variable (a lot like a function pointer in C)
		std::function<int(int, int)> _quicksort_partition;

		// This is assigning to it a lambda function value.  The most confusing part of these (for me)
		// other than the fact that they're an unnamed function is the "capture" (in the square brackets),
		// This identifies what variables from the "outside world" this function will have.  By default it
		// has none, but I'm listing those that it will have access to (& in front means it will be mutable/
		// changeable)
		_quicksort_partition = [&alist, type](int low, int high) mutable -> int
			{
				int mid = (low + high) / 2;
				T& pivot_val = alist[high];
				int i = low - 1;
				for (int j = low; j <= high; j++)
				{
					if (out_of_order(alist, type, pivot_val, alist[j]))
					{
						i++;
						// Takes advantage of the move semantics, which would be faster than making a temp T value
						std::swap(alist[j], alist[i]);
					}
				}
				std::swap(alist[i + 1], alist[high]);
				return i + 1;
			};

		// A second lambda function variable
		std::function<void(int, int)> _quicksort_recursive;
		_quicksort_recursive = [&alist, type, &_quicksort_partition, &_quicksort_recursive](int low, int high) mutable -> void
			{
				if (low < high)
				{
					int part_index = _quicksort_partition(low, high);
					_quicksort_recursive(low, part_index - 1);
					_quicksort_recursive(part_index + 1, high);
				}
			};

		// This is where the process actually starts
		_quicksort_recursive(0, alist.size() - 1);
	}


	/// <summary>
	/// A handy utility function that determines if the items at two positions are in
	/// the correct order
	/// </summary>
	/// <typeparam name="T">The type of data we're storing in our array list</typeparam>
	/// <param name="alist">The ArrayList we're looking at</param>
	/// <param name="sort_type">This indicates the type of sort order we want</param>
	/// <param name="index1">The first index to look at</param>
	/// <param name="index2">The second index to look at</param>
	/// <returns>If the sort order is ASCENDING, we return true if the element
	/// at index1 is > the element at index2.  If the sort order is DESCENDING, we return
	/// true if the element at index1 is < the element at index2.</returns>
	template <class T>
	bool out_of_order_index(const ArrayList<T>& alist, SortOrder sort_type, int index1, int index2)
	{
		return ((sort_type == SortOrder::ASCENDING && alist[index1] > alist[index2]) ||
			(sort_type == SortOrder::DESCENDING && alist[index1] < alist[index2]));
	}

	

	/// <summary>
	/// A handy utility function that determines if the items at two positions are in
	/// the correct order (the difference between this and the last function is this one takes
	/// references to an actual value rather than an index -- useful for finding because the
	/// given item to search for isn't necessarily in the list)
	/// </summary>
	/// <typeparam name="T">The type of data we're storing in our array list</typeparam>
	/// <param name="alist">The ArrayList we're looking at</param>
	/// <param name="sort_type">This indicates the type of sort order we want</param>
	/// <param name="val1">The first value</param>
	/// <param name="val2">The second value</param>
	/// <returns>If the sort order is ASCENDING, we return true if the first element 
	/// is > the second element.  If the sort order is DESCENDING, we return
	/// true if the first element is < the second element</returns>
	template <class T>
	bool out_of_order(const ArrayList<T>& alist, SortOrder sort_type, const T& val1, const T& val2)
	{
		return ((sort_type == SortOrder::ASCENDING && val1 > val2) || (sort_type == SortOrder::DESCENDING && val1 < val2));
	}



	/// <summary>
	/// Performs a non-recursive binary search operation to find the position of an element
	/// in the list (or -1 if it's not found).  If there are multiple instances of the search
	/// value in the ArrayList, this function will return the index of an arbitrary one.  This
	/// method will only work properly if the ArrayList is already sorted! 
	/// </summary>
	/// <typeparam name="T">The type of data we're storing in the ArrayList</typeparam>
	/// <param name="alist">The ArrayList to search in</param>
	/// <param name="sort_order">The current sort-order of the ArrayList</param>
	/// <param name="search_value">The value we're searching for</param>
	/// <returns>The index of one occurrence of search_value in alist, or -1 if there
	/// are no occurrences of that value.</returns>
	template <class T>
	int find_binary_search(const ArrayList<T>& alist, SortOrder sort_order, const T& search_value)
	{
		int left = 0;
		int right = alist.size() - 1;
		while (left <= right)
		{
			int mid = (left + right) >> 1;			// divide by 2 (the average)
			if (alist[mid] == search_value)
				return mid;
			else if (out_of_order(alist, sort_order, search_value, alist[mid]))
				left = mid + 1;
			else
				right = mid - 1;
		}
		
		return -1;
	}

	

	/// <summary>
	/// Performs a bubble-sort of the ArrayList, transforming it in-place to be of the
	/// requested sorting order.
	/// </summary>
	/// <typeparam name="T">The type of data we're storing in the ArrayList</typeparam>
	/// <param name="alist">The ArrayList to be sorted</param>
	/// <param name="type">The desired sort-order</param>
	template <class T>
	void bubblesort(ArrayList<T>& alist, SortOrder type)
	{
		for (unsigned int z = 0; z < alist.size(); z++)
		{
			bool sorted = true;
			for (unsigned int i = 0; i < alist.size() - 1 - z; i++)
			{
				if (out_of_order_index(alist, type, i, i + 1))
				{
					sorted = false;
					std::swap(alist[i], alist[i + 1]);
				}
			}
			if (sorted)
				break;
		}
	}


	
	/// <summary>
	/// Performs a Fisher-Yates shuffle of the data.  The nice thing about Fischer-Yates
	/// is every value will be in a different spot than when we start.
	/// Reference1: https://www.cplusplus.com/reference/random/
	/// Reference2: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	/// </summary>
	/// <typeparam name="T">The type of data being stored in the ArrayList</typeparam>
	/// <param name="alist">The list to be shuffled</param>
	/// <param name="derangement">If true, we get a derangement instead of a permutation -- the former
	/// means each element will end up in a different spot than it started, where the latter will 
	/// give us some random arrangement but with some chance an element might end up in its original
	/// spot</param>
	template <class T>
	void shuffle(ArrayList<T>& alist, bool derangement)
	{
		int offset = 0;
		if (derangement)
			offset = -1;
		std::default_random_engine generator;
		for (int i = alist.size() - 1; i > 0; i--)
		{
			std::uniform_int_distribution<int> distribution(0, i + offset);
			int j = distribution(generator);  // generates number in the range 0...i (or 0...i-1 for derangement)

			std::swap(alist[i], alist[j]);
		}
	}
}


#pragma once
#include <string>
#include <stdexcept>
#include <ostream>

// Note: in C++, a general tempate (like this one) must be defined inline
// entirely in the .h file (no .cpp files).  

namespace ssuds
{
	/// An ArrayList is an array-based data structure. 
	template <class T>
	class ArrayList
	{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ ATTRIBUTES                              @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	protected:
		/// The default (and minimum) capacity of an ArrayList
		static const int msMinCapacity = 5;

		/// The current number of "slots" AVAILABLE in mData (i.e. the array size)
		unsigned int mCapacity;

		/// How many slots are we USING?  This will always be less than or equal to mCapacity
		unsigned int mSize;

		/// The array of data we're currently holding.  Note: an alternative would've been T* mData
		/// but I'm attempting to use raw bytes here so we don't have to have a default constructor
		/// for templated types.
		unsigned char* mData;
	


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ CONSTRUCTORS / DESTRUCTORS              @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// Default constructor
		ArrayList() : mSize(0), mCapacity(0), mData(nullptr)
		{
			// intentionally empty
		};



		/// Destructor
		~ArrayList() 
		{
			// Note that I used to worry about mData being null, but the delete operator
			// already has an internal check to avoid freeing a null pointer, so adding our own
			// would be redundance, so I'm commenting this line.
			// if (mData)
			delete[] mData;
		}


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ OTHER METHODS (alphabetical)            @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T& val)
		{
			// check to see if we need to increase our capacity
			grow();

			// Stick our new element in the last slot and (sneakily) increase our size in the process
			// ... This is what I had originally...
			//(T&)(mData[mSize * sizeof(T)]) = val;
			// ... but I switched to this.  Person seemed to be a problem (in particular the strings)
			//     Memcpy would side-step any = operators.  I'm not 100% sure why this fixed the problem
			memcpy(&mData[mSize * sizeof(T)], &val, sizeof(T));
			//T temp = (T&)(mData[mSize * sizeof(T)]);     // <- seeing if I could read out what i put in just now
			mSize++;
		}


		/// <summary>
		/// Returns a reference to the item at the given index.  Since it is a reference, this
		/// type of operation is allowed:
		///		my_float_array.at(5) = 17.3f;
		///		my_int_array.at(3)++;
		/// This method will raise a std::out_of_range exception if an invalid index is given.
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		T& at(const unsigned int index) const
		{
			if (index >= mSize)
				throw std::out_of_range("Invalid index (" + std::to_string(index) + ")");
			return (T&)(mData[index * sizeof(T)]);
		}


		/// <summary>
		/// Returns the current capacity of the ArrayList (this is always
		/// greater than or equal to the size)
		/// </summary>
		/// <returns>the capacity of the internal array in the ArrayList</returns>
		unsigned int capacity() const
		{
			return mCapacity;
		}

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear()
		{
			if (mData)
				delete[] mData;
			mData = nullptr;
			mSize = 0;
			mCapacity = 0;
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(const T& val, const unsigned int start_index = 0) const
		{
			if (start_index >= mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(start_index));

			for (unsigned int i = start_index; i < mSize; i++)
			{
				T temp = at(i);
				if (temp == val)
					return i;
			}

			// We didn't find it
			return -1;
		}

	

		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(const T& val, unsigned int index)
		{
			if (index > mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else if (index == mSize)
				append(val);
			else
			{
				// check to see if we need to increase capacity first
				grow();

				// Move all the elements that come *after* index up one spot
				memcpy(&mData[sizeof(T) * (index + 1)], &mData[index * sizeof(T)], (mSize - index) * sizeof(T));

				// Put our new elements in spot index and increase our size
				//(T&)(mData[index * sizeof(T)]) = val;
				memcpy(&mData[index * sizeof(T)], &val, sizeof(T));
				mSize++;
			}
		}


		/// <summary>
		/// Outputs the ArrayList to the given output stream
		/// </summary>
		/// <param name="os">an ostream object (ofstream, stringstream, cout, etc.) </param>
		void output(std::ostream& os) const
		{
			os << "[";
			for (unsigned int i = 0; i < size(); i++)
			{
				os << at(i);
				if (i < size() - 1)
					os << ", ";
			}
			os << "]";
		}

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the data item that was just removed</returns>
		T remove(unsigned int index, bool resize_if_necessary = true)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = (T&)(mData[index * sizeof(T)]);

			// Move all elements that come after index down one spot
			memcpy(&mData[index * sizeof(T)], &mData[(index + 1) * sizeof(T)], (mSize - index - 1) * sizeof(T));

			// Decrement our size
			mSize--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <param name="resize_if_necessary">if true, the array will be resized if it is now below half capacity</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(const T val, bool resize_if_necessary=true)
		{
			int cur_index = 0;
			unsigned int num_removed = 0;
			while (cur_index >= 0 && (unsigned int)cur_index < mSize)
			{
				// Find the next occurrence of val, starting at the current position
				cur_index = find(val, cur_index);
				if (cur_index >= 0)
				{
					// We found one!
					remove(cur_index, false);
					num_removed++;
				}
			}

			if (resize_if_necessary)
				shrink();

			return num_removed;
		}


		/// <summary>
		/// Ensures the internal array has at least this capacity.  This is useful if
		/// the user knows how many items they will add and don't want to take the performance
		/// penalty of the grow operation happening in-between.  If the capacity is already higher or
		/// equal to the given value, there will be no effect.
		/// </summary>
		/// <param name="desired_capacity">The capacity will be set to at least this value</param>
		void reserve(unsigned int desired_capacity)
		{
			if (desired_capacity > mCapacity)
			{
				// Make the larger array
				unsigned char* temp_array = new unsigned char[desired_capacity * sizeof(T)];
				memset(temp_array, 0, sizeof(T) * desired_capacity);

				// Copy data from the existing array
				memcpy(temp_array, mData, mSize * sizeof(T));

				// Free the old array
				delete[] mData;

				// Make mData point to the larger array
				mData = temp_array;
				mCapacity = desired_capacity;
			}
		}

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		unsigned int size() const
		{
			return mSize;
		}

		class ArrayListIterator        // iterator might be another name-choice.
		{
		private:
			// ATTRIBUTES?  ALL iterators should be very light-weight, throw-away.
			// Don't EVER make a copy of any data -- always refer to the contained
			// ArrayList.  It should be able to "point" to a current item.

			// Most important: a reference or pointer to the ArrayList.  A reference can't
			// be changed, a pointer is more flexible but also more dangerous
			ArrayList* my_list;

			int index;


		public:
			ArrayListIterator()
			{
				// Done
				my_list = nullptr;
				my_position = 0;
			}

			ArrayListIterator(ArrayList* owning_list, int starting_index)
			{
				// Done
				my_list = owning_list;
				my_position = starting_index;
			}


			T& operator*()
			{
				// Get the current value and return
				// ArrayList we're iterating through
				return my_array_list->at(index);
			}


			ArrayListIterator operator++()
			{
				// Advance ourself, making us look "null/end"-like if we just went
				// past the end of the attached ArrayList
				my_position++;

				// Now, if we went past the end of the ArrayList (my_list->size() is helpful!),
				// make myself look like a "null"-like iterator.
			}


			bool operator!=(const ArrayListIterator& other)
			{
				// We're the iterator on the left, the iterator on the right of the != is passed to us
			}
		};


		ArrayListIterator begin()
		{
			// Our job: construct an Iterator value and return it.
			// this is a pointer to the instance of ArrayList that called this method 
			//    (like self in Python)
			ArrayListIterator temp(this, 0);
			return temp;
		}


		ArrayListIterator end()
		{
			// Our job: construct an null-like Iterator value and return it.

			// Despite the name, this does NOT make an iterator that refers to the LAST value
			// -- it's a special "null-like" value that you decide on
			ArrayListIterator temp(? ? ? );
			return temp;

		}
		


	protected:
		/// <summary>
		/// An internal method to resize the array if we are currently at capacity (if we are not, nothing is done)
		/// </summary>
		void grow()
		{
			if (mSize == mCapacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = nullptr;
				if (mCapacity == 0)
				{
					new_array = new unsigned char[msMinCapacity * sizeof(T)];
					memset(new_array, 0, msMinCapacity * sizeof(T));
				}
				else
				{
					new_array = new unsigned char[(mCapacity * 2) * sizeof(T)];
					memset(new_array, 0, (mCapacity * 2) * sizeof(T));
				}

				// Copy over data from the old array (if any)
				if (mData != nullptr)
				{
					memcpy(new_array, mData, sizeof(T) * mSize);

					// Destroy the old array
					delete[] mData;
				}

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				if (mCapacity == 0)
					mCapacity = msMinCapacity;
				else
					mCapacity *= 2;
			}
		}


		/// <summary>
		/// An internal method to see if the array can be shrunk (capacity reduced by half, down to msMinCapacity)
		/// </summary>
		void shrink()
		{
			if (mSize < mCapacity / 4 && mCapacity > msMinCapacity)
			{
				// Allocate what will become the new array
				unsigned char* new_array = new unsigned char[(mCapacity / 2) * sizeof(T)];
				memset(new_array, 0, (mCapacity / 2) * sizeof(T));

				// Copy over data from the old array (if any)
				memcpy(new_array, mData, mSize * sizeof(T));
				
				// Destroy the old array
				delete[] mData;

				// Make the new array *the* array
				mData = new_array;

				// Note that our capacity is now double what it used to be
				mCapacity /= 2;
			}
		}
	};
}

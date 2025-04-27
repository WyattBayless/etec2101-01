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
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ ENUM CLASSES                           @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		enum class ArrayListIteratorType 
		{ 
			/// <summary>
			/// This ArrayList iterator visits items from beginning to end
			/// </summary>
			forward, 

			/// <summary>
			/// This ArrayList iterator visits items from end to beginning
			/// </summary>
			backwards 
		};

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// @ NESTED CLASSES                         @
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		/// The job of ArrayListIterator is to traverse the data in an ArrayList.  ArrayList
		/// wouldn't necessarily *need* an iterator since the internal array supports random access,
		/// but this is a chance to get used to the iterator pattern, which is much more useful
		/// for the user in other classes.  We might eventually use inheritance to derive this class
		/// from some common iterator class.
		/// </summary>
		class ArrayListIterator
		{
		protected:
			/// <summary>
			/// A pointer to the containing ArrayList
			/// </summary>
			const ArrayList* mArrayList;

			/// <summary>
			/// The current position within the array list.  Anything from 0...ArrayListSize-1 is considered
			/// "valid", all other values are invalid
			/// </summary>
			int mPosition;


			/// <summary>
			/// Which type of iterator are we?
			/// </summary>
			ArrayListIteratorType mType;

		public:
			/// <summary>
			/// The main constructor
			/// </summary>
			/// <param name="arr">The ArrayList we are to traverse</param>
			/// <param name="tp">What type of traversal to do</param>
			/// <param name="start_index">The index to start on</param>
			ArrayListIterator(const ArrayList* arr, ArrayListIteratorType tp, int start_index) : mArrayList(arr), mPosition(start_index), mType(tp)
			{
				// intentionally empty
			}


			/// <summary>
			/// This constructor only really has value if the user makes an iterator (BUT DOES NOT USE!)
			/// and then later assigns it a real value.  If the user does anything with an iterator
			/// created like this, bad things will happen...
			/// </summary>
			ArrayListIterator() : mArrayList(nullptr), mType(ArrayListIteratorType::forward), mPosition(0)
			{
				// intentionally empty
			}


			/// <summary>
			/// Copy-constructor
			/// </summary>
			/// <param name="other"></param>
			ArrayListIterator(const ArrayListIterator& other) : mArrayList(other.mArrayList), mPosition(other.mPosition),
				mType(other.mType)
			{
				// intentionally empty
			}


			/// <summary>
			/// Are we equal to the other iterator?  I'm currently not considering the ArrayListIterator type...
			/// I'm not sure if that's the right call or not.
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're equal</returns>
			bool operator==(const ArrayListIterator& other) const
			{
				return mArrayList == other.mArrayList && mPosition == other.mPosition;
			}

			/// <summary>
			/// Are we not equal to the other iterator?  This is computed by inverting the result of the
			/// == operator
			/// </summary>
			/// <param name="other">The iterator we're comparing ourself to</param>
			/// <returns>true if we're NOT equal</returns>
			bool operator!=(const ArrayListIterator& other) const
			{
				return !(*this == other);
			}


			/// <summary>
			/// Increments / advances the iterator (prefix ++x version).  This version of ++ returns
			/// a copy of the Iterator *after* the ++ is performed.  So if the user did this:
			/// y = ++x
			/// X is changed, and a copy is returned which can be assigned to y.
			/// It is the responsibility of the user to NOT call this if the iterator is 
			/// invalid (equal to end/rend) -- if they ignore this rule, the results are indeterminate.
			/// </summary>
			ArrayListIterator operator++()
			{
				if (mType == ArrayListIteratorType::forward)
					++mPosition;
				else
					--mPosition;

				return ArrayListIterator(mArrayList, mType, mPosition);
			}


			/// <summary>
			/// Increments / advances the iterator (postfix x++ version).  This version of ++ returns
			/// a copy of the Iterator *before* the ++ is performed.  So if the user did this:
			/// y = x++
			/// X is changed, but y will hold the iterator value before the change.  
			/// It is the responsibility of the user to NOT call this if the iterator is 
			/// invalid (equal to end/rend) -- if they ignore this rule, the results are indeterminate.
			/// <param name="not_used">This parameter is not used at all, but the compiler passes us
			/// a value so we can have both versions of ++</param>
			/// </summary>
			ArrayListIterator operator++(int not_used)
			{
				ArrayListIterator return_val(mArrayList, mType, mPosition);
				if (mType == ArrayListIteratorType::forward)
					++mPosition;
				else
					--mPosition;
				return return_val;
			}


			/// <summary>
			/// Returns a copy of this iterator that is some amount offset from the current position.
			/// The resulting index of that iterator is constratined to be within -1...mSize
			/// </summary>
			/// <param name="offset">The amount to offset this iterator (positive or negative)</param>
			/// <returns>A copy of this iterator with the given offset applied</returns>
			ArrayListIterator operator+(int offset) const
			{
				int new_index = mPosition + offset;
				if (new_index < -1)
					new_index = -1;
				if (new_index >= (int)mArrayList->size())
					new_index = (int)mArrayList->size();

				return ArrayListIterator(mArrayList, mType, new_index);
			}


			/// <summary>
			/// I don't think std::vector does this, but it is the inverse of the + operator and easy to add
			/// </summary>
			/// <param name="offset">The amount to offset this iterator by (inverted)</param>
			/// <returns>A copy of this iterator with the given offset</returns>
			ArrayListIterator operator-(int offset) const
			{
				return (*this) + (-offset);
			}


			/// <summary>
			/// Returns a reference to the current item in the ArrayList.  It is important that the
			/// user only call this method if the iterator is not in an invalid state (defined by being
			/// equal to end/rend)
			/// </summary>
			/// <returns>A reference to the current object</returns>
			T& operator*()
			{
				return (*mArrayList)[mPosition];
			}


			/// <summary>
			/// Used to copy one ArrayListIterator value to another
			/// </summary>
			/// <param name="other">The ArrayListIterator we're copying from</param>
			/// <returns>A reference to this changed ArrayListIterator</returns>
			ArrayListIterator& operator=(const ArrayListIterator& other)
			{
				mArrayList = other.mArrayList;
				mPosition = other.mPosition;
				mType = other.mType;
				return *this;
			}

			// I needed access in the remove method.
			friend class ArrayList;
		};

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

		// This is the "traditional" approach, but does require that we have a default constructor
		T* mData;


	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ OPERATOR OVERLOADS                      @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:

		/// <summary>
		/// Overloads the stream operator for ArrayLists.
		/// </summary>
		/// <param name="os">an ostream object (ofstream, stringstream, cout, etc.) </param>
		/// <param name="alist">the ArrayList</param>
		/// <returns>the (possibly modified) os that was given to us</returns>
		friend std::ostream& operator <<(std::ostream& os, const ArrayList& alist)
		{
			alist.output(os);
			return os;
		}


		/// <summary>
		/// Gets the data item at the given index.  This method (unlike at) does NOT
		/// do bounds-checking (and so is very slightly faster)
		/// </summary>
		/// <param name="index">the index of the thing to return</param>
		/// <returns>a reference to the value at the given index</returns>
		T& operator[](int index) const
		{
			return mData[index];
		}



		/// <summary>
		/// Allows the creation of a deep copy when the user assigns an existing
		/// ArrayList to another.  This method also handles the case where the user
		/// self-copies (a = a).
		/// </summary>
		/// <param name="other">The other ArrayList we are assigning to</param>
		/// <returns>a reference to this ArrayList</returns>
		ArrayList<T>& operator= (const ArrayList<T>& other)
		{
			// Save away all data we need from other
			T* other_data_copy = new T[other.mCapacity];
			for (unsigned int i = 0; i < other.mSize; i++)
				other_data_copy[i] = other[i];

			unsigned int other_size = other.size();
			unsigned int other_capacity = other.capacity();

			// Clear our data.  There is a chance that this and other are the same thing, which
			// was why it was important to save away the data above before doing this.
			clear();

			// Now just assign values from the temporaries we saved away
			mData = other_data_copy;
			mCapacity = other_capacity;
			mSize = other_size;

			// Finally return a reference to ourself to support chain-assignments like
			// b = this_array_list = a;
			return *this;
		}



	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// @ CONSTRUCTORS / DESTRUCTORS              @
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	public:
		/// <summary>
		/// The Default constructor
		/// </summary>
		ArrayList() : mSize(0), mCapacity(0), mData(nullptr)
		{
			// intentionally empty
		};


		/// <summary>
		/// The copy-constructor.  Used in these two cases
		/// ArrayList me(other_array_list);
		/// ArrayList me = other_array_list;    Note: this does NOT use the =operator
		/// ...
		/// me = other_array_list;				This WOULD use the =operator
		/// </summary>
		/// <param name="other"></param>
		ArrayList(const ArrayList& other) : mCapacity(other.mCapacity), mSize(other.mSize)
		{
			mData = new T[other.mCapacity];
			for (unsigned int i = 0; i < other.size(); i++)
				(*this)[i] = other[i];
		}

		/// <summary>
		/// The move-constructor.  This makes a shallow copy of other.  A better way to explain
		/// might be to say that this constructor "steals" the data from the other array.  The compiler
		/// calls this method when ArrayList other is about to go away, and it is being assigned
		/// to us.  Making a full copy would be much more expensive than this.
		/// </summary>
		/// <param name="other"></param>
		ArrayList(ArrayList&& other) : mCapacity(other.mCapacity), mSize(other.mSize), mData(other.mData)
		{
			other.mData = NULL;
			other.mCapacity = 0;
			other.mSize = 0;
		}

		/// Initializer-list constructor
		ArrayList(std::initializer_list<T> ilist) : mCapacity((int)ilist.size()), mSize((int)ilist.size())
		{
			mData = new T[mCapacity];
			int i = 0;
			for (T val : ilist)
				(*this)[i++] = val;
		}



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

			// Put the data in the last spot (and sneakily increase the size!)
			mData[mSize++] = val;
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
			return mData[index];
		}


		/// <summary>
		/// Returns an forward ArrayListIterator "pointing" at the first element (if it exists).  If the
		/// ArrayListIterator is empty, this iterator will be equal to end.
		/// </summary>
		/// <returns>A forward iterator referring to the first value value</returns>
		ArrayListIterator begin() const
		{
			return ArrayListIterator(this, ArrayListIteratorType::forward, 0);
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
		/// The name can be a bit mis-leading, but this iterator does NOT return an iterator referring
		/// to the LAST element.  Instead, it returns a special value that indicates this is an invalid
		/// iterator (or we're done forward-traversing)
		/// </summary>
		/// <returns>An "end" type iterator value</returns>
		ArrayListIterator end() const
		{
			return ArrayListIterator(this, ArrayListIteratorType::forward, mSize);
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
				return -1;

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
		/// Like the find method above, but using iterators (closer to std::vector)
		/// </summary>
		/// <param name="val">The value to search for</param>
		/// <param name="start">Either begin, rbegin, or some other iterator to initialize the search</param>
		/// <returns>And end iterator or rend/end iterator value if not found</returns>
		ArrayListIterator find(const T& val, const ArrayListIterator& start) const
		{
			if (start.mArrayList != this)
				throw std::runtime_error("iterator must be based on this ArrayList");

			// Make a copy of the ArrayListIterator we were given and one to hold the end iterator value
			ArrayListIterator temp = start;
			ArrayListIterator ender;

			// Properly assign the ender-man
			if (start.mType == ArrayListIteratorType::forward)
				ender = end();
			else
				ender = rend();

			// Now, continue until we reach the end or one of the values
			while (temp != ender)
			{
				if (*temp == val)
					return temp;
				else
					++temp;
			}

			return temp;
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

				// Move all elements at or after the given index down one spot
				for (unsigned int i = mSize; i > index; i--)
					mData[i] = mData[i - 1];
				// Put our new elements in spot index and increase our size
				mData[index] = val;
				mSize++;
			}
		}



		/// <summary>
		/// This basically does the same thing as the << operator (the syntax is a bit different).  I 
		/// chose to keep it to preserve backwards compatiability with <Lab3 code.
		/// </summary>
		/// <param name="os">The output stream (cout, fp, stringstring, etc.) to write to</param>
		void output(std::ostream& os) const
		{
			os << "[";
			for (unsigned int i = 0; i < mSize; i++)
			{
				os << (*this)[i];
				if (i < mSize - 1)
					os << ", ";
			}
			os << "]";
		}



		void prepend(const T& val)
		{
			// check to see if we need to increase our capacity
			grow();


			// Move the items "down" one index to make room
			for (unsigned int i = mSize; i > 0; i--)
				mData[i] = mData[i - 1];

			// Put the new item into the first spot
			mData[0] = val;
			mSize++;
		}



		/// <summary>
		/// Returns a backwards ArrayListIterator "pointing" at the last element (if it exists).  If the
		/// ArrayListIterator is empty, this iterator will be equal to rend.
		/// </summary>
		/// <returns>A backwards iterator referring to the last valid value</returns>
		ArrayListIterator rbegin() const
		{
			return ArrayListIterator(this, ArrayListIteratorType::backwards, mSize - 1);
		}


		/// <summary>
		/// Returns a special value indicating we're done iterating backwards or that this iterator is invalid
		/// </summary>
		/// <returns>A special end value for backwards iteration</returns>
		ArrayListIterator rend() const
		{
			return ArrayListIterator(this, ArrayListIteratorType::backwards, -1);
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
			T result = mData[index];

			// Move all elements that come after index down one spot
			for (unsigned int i = index; i < mSize - 1; i++)
				mData[i] = mData[i + 1];

			// Decrement our size
			mSize--;

			// Shrink, if applicable and requested
			if (resize_if_necessary)
				shrink();

			// Return the result
			return result;
		}


		/// <summary>
		/// Removes the value at the given position
		/// </summary>
		/// <param name="it">A valid iterator referring to the value that the user wants to remove</param>
		/// <returns>An iterator now referring to the value *after* the value removed (or end/rend if there's
		/// nothing after)</returns>
		ArrayListIterator remove(const ArrayListIterator& it)
		{
			if (it.mArrayList != this || it.mPosition < 0 || it.mPosition > (int)mSize)
				throw std::out_of_range("Invalid iterator state");
			
			remove(it.mPosition);
			if (it.mType == ArrayListIteratorType::forward)
				return it;
			else
			{
				return it - 1;
			}
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
				T* temp_array = new T[desired_capacity];

				// Copy data from the existing array
				for (unsigned int i = 0; i < mSize; i++)
					temp_array[i] = mData[i];

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


	protected:
		/// <summary>
		/// An internal method to resize the array if we are currently at capacity (if we are not, nothing is done)
		/// </summary>
		void grow()
		{
			if (mSize == mCapacity)
			{
				// Allocate what will become the new array
				T* new_array = nullptr;
				if (mCapacity == 0)
					new_array = new T[msMinCapacity];
				else
					new_array = new T[mCapacity * 2];

				// Copy over data from the old array (if any)
				if (mData != nullptr)
				{
					for (unsigned int i = 0; i < mSize; i++)
						new_array[i] = mData[i];

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
				T* new_array = new T[mCapacity / 2];

				// Copy over data from the old array (if any)
				for (unsigned int i = 0; i < mSize; i++)
					new_array[i] = mData[i];

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
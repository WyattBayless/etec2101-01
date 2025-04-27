// Wyatt Bayless
// ETEC2101 Lab06

#include <string>
#include <stdexcept>
#include <ostream>

/*
NOTE: I tried to implement as many of the lab specs as possible.
A few things may have problem, I don't really have the documentation,
and the tests may not be the best but I need to move on
*/

#pragma once
namespace ssuds
{
	template <class T>
	class LinkedList
	{
		// IMPORTANT DESIGN CONSIDERATION: User shouldn't be able to see any Nodes!!
	private:
		class Node			// Each instance corresponds to an orange "box" in the slides
		{
		public:
			T mData;
			Node* mNext;
			Node* mPrevious;
		};
		enum class LinkedListIteratorDirection
		{
			/// <summary>
			/// This ArrayList iterator visits items from beginning to end
			/// </summary>
			FORWARD,

			/// <summary>
			/// This ArrayList iterator visits items from end to beginning
			/// </summary>
			BACKWARDS
		};

	public:
		class LinkedListIterator
		{
		protected:
			// attributes???
			Node* mCurrentNode;
			LinkedListIteratorDirection mType;

		public:
			LinkedListIterator(Node* startNode, LinkedListIteratorDirection tp) : mCurrentNode(startNode), mType(tp)
			{
				// intentionally empty
			}

			bool operator==(const LinkedListIterator& other) const
			{
				return mCurrentNode == other.mCurrentNode && mType == other.mType;
			}

			bool operator!=(const LinkedListIterator& other) const
			{
				return !(*this == other);
			}

			T& operator*()
			{
				return mCurrentNode->mData;
			}

			LinkedListIterator& operator=(const LinkedListIterator& other)
			{
				mCurrentNode = other.mCurrentNode;
				mType = other.mType;
				return *this;
			}

			// Might return a LinkedListIterator?
			LinkedListIterator operator++()
			{
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mNext;
				else
					mCurrentNode = mCurrentNode->mPrevious;

				return LinkedListIterator(mCurrentNode, mType);
			}

			LinkedListIterator operator++(int not_used)
			{
				LinkedListIterator return_val(mCurrentNode, mType);
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mNext;
				else
					mCurrentNode = mCurrentNode->mPrevious;
				return return_val;
			}

			LinkedListIterator operator--()
			{
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mPrevious;
				else
					mCurrentNode = mCurrentNode->mNext;
				return LinkedListIterator(mCurrentNode, mType);
			}

			LinkedListIterator operator--(int not_used)
			{
				LinkedListIterator return_val(mCurrentNode, mType);
				if (mType == LinkedListIteratorDirection::FORWARD)
					mCurrentNode = mCurrentNode->mPrevious;
				else
					mCurrentNode = mCurrentNode->mNext;
				return return_val;
			}

			LinkedListIterator operator+(int offset) const
			{
				Node* cur = mCurrentNode;
				int new_index = offset;

				if (new_index > 0) 
				{
					while (new_index > 0 && cur)
					{
						cur = cur->mNext;
						--new_index;
					}
				}
				else
				{
					while (new_index < 0 && cur)
					{
						cur = cur->mPrevious;
						++new_index;
					}
				}
				return LinkedListIterator(cur, mType);
			}

			LinkedListIterator operator-(int offset) const
			{
				Node* cur = mCurrentNode;
				int new_index = offset;

				if (new_index > 0)
				{
					while (new_index > 0 && cur)
					{
						cur = cur->mPrevious;
						--new_index;
					}
				}
				else
				{
					while (new_index < 0 && cur)
					{
						cur = cur->mNext;
						++new_index;
					}
				}
				return LinkedListIterator(cur, mType);
			}

			// I needed access in the remove method.
			friend class LinkedList;
		};

		// Attributes
		Node* mStart;			// Sometimes called the "head"
		Node* mEnd;				// Sometimes called the "tail"
		unsigned int mSize;

	public:
		LinkedList()
		{
			mStart = nullptr;
			mEnd = nullptr;
			mSize = 0;
		}

		LinkedList(const LinkedList& other)
		{
			if (other.mStart == nullptr) 
			{ 
				mStart = nullptr;
				mEnd = nullptr;
				mSize = 0;
				return;
			}

			// Initialize the new list.
			mStart = new Node(other.mStart->mData);
			Node* cur_new = mStart;
			Node* cur_old = other.mStart->mNext;

			while (cur_old != nullptr) {
				Node* new_node = new Node(cur_old->mData); 
				cur_new->mNext = new_node; 
				new_node->mPrevious = cur_new; 
				cur_new = new_node; 
				cur_old = cur_old->mNext; 
			}

			mEnd = cur_new;
			mSize = other.mSize;
		}

		//Move constructor
		LinkedList(LinkedList&& other) : mStart(other.mStart), mEnd(other.mEnd), mSize(other.mSize)
		{
			other.mStart = nullptr;
			other.mEnd = nullptr;
			other.mSize = 0;
		}

		//Initializer-list constructor
		LinkedList(std::initializer_list<T> initList) : mStart(nullptr), mEnd(nullptr), mSize(0) 
		{
			Node* previous_node = nullptr;
			
			for (const T& value : initList) {
				Node* new_node = new Node(value);

				if (!mStart)
					mStart = new_node;
				else
				{
					previous_node->mNext = new_node;
				}
				previous_node = new_node;
				mEnd = new_node;

			}
		}


		/// Destructor
		~LinkedList()
		{
			// Can just call clear method here
			clear();
		}

		void append(const T& val)
		{

			if (mSize == 0)
			{
				// Case1: list is empty
				// a. Make a new Node
				// b. Make mStart and mEnd point to it.
				Node* new_node = new Node;
				mStart = mEnd = new_node;			// Maybe add a constructor to Node??
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
			}
			else
			{
				// Case2: list has data in it
				Node* new_node = new Node;
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
				// Make the current last node point to this new one
				mEnd->mNext = new_node;
				// Make the new node point to the *CURRENT* end node
				new_node->mPrevious = mEnd;
				// Make the new node THE last node
				mEnd = new_node;
			}
			// Increase size
			mSize++;
		}

		void prepend(const T& val)
		{

			if (mSize == 0)
			{
				// Case1: list is empty
				// a. Make a new Node
				// b. Make mStart and mEnd point to it.
				Node* new_node = new Node;
				mStart = mEnd = new_node;			// Maybe add a constructor to Node??
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
			}
			else
			{
				// Case2: list has data in it
				Node* new_node = new Node;
				new_node->mData = val;	            // Initializing the new node (could've
				new_node->mNext = nullptr;          //    referred to mEnd -- it's the same node!)
				new_node->mPrevious = nullptr;
				// Make the current first node point to this new one
				mStart->mPrevious = new_node;
				// Make the new node point to the *CURRENT* start node
				new_node->mNext = mStart;
				// Make the new node THE first node
				mStart = new_node;
			}
			// Increase size
			mSize++;
		}

		T& at(const unsigned int index) const
		{
			if (mSize >= index)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			Node* cur = mStart;
			unsigned int cur_index = 0;
			while (cur_index != index)
			{
				cur = cur->mNext;
				++cur_index;
			}
			return cur->mData;
		}

		unsigned int size() const
		{
			return mSize;
		}

		int find(const T& val, const unsigned int start_index = 0) const 
		{
			if (start_index >= mSize)
				return -1;

			Node* cur = mStart;
			for (unsigned int i = 0; i < start_index; i++)
				cur = cur->mNext;

			for (unsigned int i = start_index; i < mSize; i++)
			{
				if (cur->mData == val)
					return i;
				cur = cur->mNext;
			}

			// We didn't find it
			return -1;
		}

		LinkedListIterator find(const T& val, const LinkedListIterator& start) const
		{
			LinkedListIterator temp = start;
			LinkedListIterator ender;

			// Properly assign the ender-man
			if (start.mType == LinkedListIteratorDirection::FORWARD)
				ender = end();
			else
				ender = rend();

			while (temp != ender)
			{
				if (*temp == val)
					return temp;
				else
					++temp;
			}

			return temp;
		}

		void insert(const T& new_val, unsigned int index)    // O(n) b/c of step2
		{
			// 1. Check index to see if it's valid -- if not raise std::out_of_range exception
			//      I allowed index == mSize here and just did an append (and return)
			//      if index == 0, just call prepend (and return)
			// 2. Navigate to the current node at the given index (called cur_node)
			// 3. Create a new node.
			Node* cur_node = mStart;
			if (index > mSize)
				throw std::out_of_range("Invalid Index: " + std::to_string(index));
			else if (index == mSize) {
				append(new_val);
				return;
			}
			else if (index == 0) {
				prepend(new_val);
				return;
			}
			else
			{
				unsigned int cur_index = 0;

				while (cur_index != index)
					cur_node = cur_node->mNext;
					cur_index++;
			}

			Node* new_node = new Node;
			new_node->mData = new_val;
			new_node->mNext = nullptr;
			new_node->mPrevious = nullptr;
			// 4. Make changes to the links:
			new_node->mPrevious = cur_node->mPrevious;     // b.
			new_node->mPrevious->mNext = cur_node;		   // a. 
			new_node->mNext = cur_node;					   // d. 
			cur_node->mPrevious = new_node;				   // c. 
			// 5. Increase size
			mSize++;

		}

		T remove(unsigned int index) {
			if (index >= mSize) {
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			}

			Node* remove = mStart;

			if (index == 0) 
			{
				mStart = mStart->mNext; 
				if (mStart)
					mStart->mPrevious = nullptr;
				delete remove;
			}
			else 
			{
				for (unsigned int i = 0; i < index; i++)
					remove = remove->mNext;

				if (remove->mPrevious)
					remove->mPrevious->mNext = remove->mNext;
				if (remove->mNext)
					remove->mNext->mPrevious = remove->mPrevious;

				delete remove; 
			}
			if (index == mSize - 1) {
				mEnd = remove->mPrevious;
			}
			--mSize;
		}

		LinkedListIterator remove(LinkedListIterator it) {
			//if (it == LinkedListIterator(nullptr))
				//throw std::invalid_argument("Cannot remove a null iterator.");

			Node* remove = it.mCurrentNode;

			if (remove->mPrevious)
				remove->mPrevious->mNext = remove->mNext;
			else 
				mStart = remove->mNext;

			if (remove->mNext)
				remove->mNext->mPrevious = remove->mPrevious;
			else
				mEnd = remove->mPrevious;

			LinkedListIterator new_it(remove->mNext, it.mType);

			delete remove;
			--mSize;

			return new_it; 
		}

		int remove_all(const T val)
		{
			LinkedListIterator it = begin();
			int remove_count = 0;
			while (it != end())
			{
				if (*it == val)
				{
					it = remove(it);
					remove_count++;
				}
				else
					++it;
			}
			return remove_count;
		}

		void output(std::ostream& os) const
		{
			// Output in python-list style output: [A, B, C, D, E].  This pattern
			// is called ITERATING (not iterator) through all the nodes -- very
			// common pattern in the linked list.
			os << "[";
			Node* cur_node = mStart;		// Might be nullptr!!
			for (unsigned int i = 0; i < mSize; i++)
			{
				//os << mData[i];		// Not a thing here!!!
				os << cur_node->mData;
				cur_node = cur_node->mNext;
				if (i < mSize - 1)
					os << ", ";
			}
			os << "]";
		}

		void clear()
		{
			Node* cur = mStart;
			while (cur != nullptr)
			{
				Node* next = cur->mNext;
				delete cur;
				cur = next;
			}

			mStart = nullptr;
			mEnd = nullptr;

			mSize = 0;
		}

		T& operator[](unsigned int index)
		{
			// 1. Check index to see if it's valid -- if not raise std::out_of_range exception
			// 2. Loop to the proper spot (using the iteration pattern on slide 8)
			// 3. Return the data of that current node.
			// (maybe a few bonus points if you pick the "smart" side of the linked list to
			//     start from)
			if (index >= mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			Node* cur = mStart;
			unsigned int cur_index = 0;
			while (cur_index != index)
			{
				cur = cur->mNext;
				++cur_index;
			}
			return cur->mData;
		}

		friend std::ostream& operator <<(std::ostream& os, const LinkedList& llist)
		{
			llist.output(os);
			return os;
		}

		LinkedListIterator begin()
		{
			return LinkedListIterator(mStart, LinkedListIteratorDirection::FORWARD);
		}

		LinkedListIterator rbegin()
		{
			return LinkedListIterator(mEnd, LinkedListIteratorDirection::BACKWARDS);
		}

		LinkedListIterator end()
		{
			return LinkedListIterator(nullptr, LinkedListIteratorDirection::FORWARD);
		}

		LinkedListIterator rend()
		{
			return LinkedListIterator(nullptr, LinkedListIteratorDirection::BACKWARDS);
		}

	};

};

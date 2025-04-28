// Wyatt Bayless
// ETEC2101 Lab 07

#include <iostream>
#include <optional>
#include <string>
#include <stdexcept>
#include <ostream>
#include "array_list.h"

// Tried to do everything except google tests, iterator, and bonus
// (also documentation is not the best, sorry)

#pragma once
namespace ssuds
{
	template <class T>
	class OrderedSet
	{
		enum class TraversalType
		{
			PRE_ORDER,
			POST_ORDER,
			IN_ORDER
		};

	private:
		// Just like LinkedList, I don't want outside users to see this AT ALL!!!
		class Node
		{
		private:
			T mData;
			Node* mLeft;
			Node* mRight;
		public:
			Node(const T& data, Node* left, Node* right) : mData(data), mLeft(nullptr),
				mRight(nullptr)
			{
				// intentionally empty
			}

			~Node()
			{
				if (mLeft != nullptr)
					delete mLeft;
				if (mRight != nullptr)
					delete mRight;
			}

			// Other getters/setters

			bool insert_recursive(const T& new_val)
			{
				if (new_val == mData)
					return false;			// It's a duplicate -- stop!
				else if (new_val < mData)
				{
					// This should go to my left
					if (mLeft == nullptr)
					{
						// I don't have a left-child -- make a new node that BECOMES the left child.
						mLeft = new Node(new_val);
						return true;
					}
					else
					{
						// I DO have a left child
						mLeft->insert_recursive(new_val);
					}
				}
				else
				{
					// This should go to my right -- similar to left case
					if (mRight == nullptr)
					{
						mRight = new Node(new_val);
						return true;
					}
					else
					{
						mRight->insert_recursive(new_val);
					}
				}
			}


			bool contains_recursive(const T& val) const
			{
				// If I hold the value, return true.
				// If the value is less than my data it *WOULD* go to my left
				//     If I don't have a left child, return false
				//     If I do, ask the left child to compute the answer.
				if (val == mData)
					return true;
				else if (val < mData)
				{
					if (mLeft == nullptr)
						return false;
					else
						return mLeft->contains_recursive(val);
				}
				else
				{
					if (mRight == nullptr)
						return false;
					else
						return mRight->contains_recursive(val);
				}
			}

			void traversal_recursive(TraversalType order, ssuds::ArrayList<T>& result) const 
			{
				if (order == TraversalType::PRE_ORDER)
				{
					result.append(mData);
					if (mLeft)
						mLeft->traversal_recursive(order, result);
					if (mRight)
						mRight->traversal_recursive(order, result);
				}
				else if (order == TraversalType::POST_ORDER)
				{
					if (mLeft)
						mLeft->traversal_recursive(order, result);
					if (mRight)
						mRight->traversal_recursive(order, result);
					result.append(mData);
				}
				else if (order == TraversalType::IN_ORDER)
				{
					if (mLeft)
						mLeft->traversal_recursive(order, result);
					result.append(mData);
					if (mRight)
						mRight->traversal_recursive(order, result);
				}
			}

			void clear_recursive(Node<T>* node)
			{
				if (!node)
					return nullptr;		// null node
				clear_recursive(node->mLeft);
				clear_recursive(node->mRight);

				delete node;
			}

			unsigned int get_height_recursive(Node<T>* node)
			{
				if (node == nullptr)
					return;
				else
				{
					int leftHeight = get_height_recursive(node->mLeft);
					int rightHeight = get_height_recursive(node->mRight);
					if (leftHeight > rightHeight)
						return 1 + leftHeight;
					else
						return 1 + rightHeight;
				}
			}

			std::optional<Node*> get_parent_recursive(const T& val)
			{
				// left or right matches, so this is the parent
				if ((mLeft && mLeft->mData == val)) || (mRight && mRight->mData == val)
					return this;

				if (val < mData && mLeft)
					return mLeft->get_parent_recursive(val);
				else if (val > mData && mRight)
					return mRight->get_parent_recursive(val);

				// not found
				return std::nullopt;
			}

			Node* erase_recursive(const T& val)
			{
				if (val == mData)
				{
					// need to remove (and we now know we need to return true)
					if (!mLeft && !mRight)
					{
						delete this;
						return nullptr;
					}
				}
				else if (val < mData && mLeft != nullptr)
					mLeft = mLeft->erase_recursive(val);
				else if (val > mData && mRight != nullptr)
					mRight = mRight->erase_recursive(val);
				else if (mLeft && mRight)
				{
					Node* succ = get_successor();
					mData = succ->mData;
					mRight->erase_recursive(mData);
				}
				else if (!mLeft && mRight)
				{
					Node* temp = mRight;
					delete this;
					return temp;
				}
				else
				{
					Node* temp = mLeft;
					delete this;
					return temp;
				}
				// not there stop
				return this;
			}
		}; // end of Node class

		// Attributes for OrderedSet itself.
	private:
		unsigned int mSize;
		Node* mRoot;
	public:
		OrderedSet() : mSize(0), mRoot(nullptr)
		{
			// intentionally empty.
		}

		~OrderedSet()
		{
			if (mRoot != nullptr)
				delete mRoot;
		}

		unsigned int size() const
		{
			return mSize;
		}

		void clear()
		{
			if (mRoot)
			{
				clear_recursive(mRoot);
				mRoot = nullptr;
			}
		}

		friend std::ostream& operator <<(std::ostream& os, const OrderedSet<T>& set)
		{
			ssuds::ArrayList<T> result = set.traversal(TraversalType::IN_ORDER);
			for (const T& val : result)
				os << val << " ";
			return os;
		}

		bool insert(const T& val)
		{
			if (mSize == 0)
			{
				// Nothing here -- make the new node the root
				mRoot = new Node(val);
				mSize = 1;
				return true;
			}
			else
			{
				// We already have a root -- let it handle the rest
				bool result = mRoot->insert_recursive(val);
				if (result)
					mSize++;
			}
		}

		unsigned int get_height(Node<T>* node)
		{
			if (mRoot == nullptr)
				return 0;
			else
				return get_height(mRoot);
		}

		std::optional<Node<T>*> get_parent(const T& val)
		{
			if (!mRoot || mRoot->mData == val)
				return std::nullopt;
			return mRoot->get_parent_recursive(val);
		}

		bool contains(const T& val) const
		{
			if (!mRoot)
				return false
			else
				return mRoot->contains_recursive(val);
		}

		ssuds::ArrayList<T> traversal(TraversalType order) const
		{
			ssuds::ArrayList<T> result;
			if (mRoot)
				mRoot->traversal_recursive(order, result);
			return result;
		}

		bool erase(const T& val) const
		{
			if (mSize == 0)
				return false;
			else
				mRoot = mRoot->erase_recursive(val);
		}

		void rebalance()
		{
			ssuds::ArrayList<T> values = traversal(TraversalType::IN_ORDER);
			mRoot = create_balanced(values, 0, mSize - 1);
			
		}

		Node<T>* create_balanced(const ssuds::ArrayList<T>& values, int start, int end)
		{
			if (start > end)
				return nullptr;
			int mid = (start + end) / 2; // Middle becomes root
			Node<T>* new_node = new Node<T>(values[mid]);

			// Kinda like recursive methods in Node class, but you said they weren't needed there in lab specs
			new_node->mLeft = create_balanced(values, start, mid - 1);
			new_node->mRight = create_balanced(values, mid + 1, end);

			return new_node;
		}
	};
}
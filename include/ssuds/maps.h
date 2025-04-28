// Wyatt Bayless
// ETEC2101 Lab 08

#pragma once

#include <map>
#include <iostream>

// NOTE: I did a lot of this quickly. There are no google tests or bonus.
// I had to reference google a lot so half of this may not even work.
// I used std::pair and std::hash which I'm not sure I was allowed to do.
// I don't even know if I did what I was supposed to be doing for some of this.
// I was really just trying to get a decent amount done to hopefully recover some points.
// Also, I tried to add a little bit more documentation this time

namespace ssuds
{
	template <class K, class V>
	class Map
	{
		enum class MapIteratorType
		{
			FORWARD,
			BACKWARDS
		};
	protected:
		// attributes
		std::pair<K, V>* mTable;
		unsigned int mCapacity;
		unsigned int mMinCapacity = 5;
		unsigned int mSize;
		bool* occupied;

	public:
		class MapIterator
		{
		protected:
			Map<K,V>* mTable;
			unsigned int mPosition;
			MapIteratorType mType
		public:

			/// <summary>
			/// Main Constructor for MapIterator
			/// </summary>
			/// <param name="table"></param>
			/// <param name="i"></param>
			/// <param name="tp"></param>
			MapIterator(Map<K,V> * table, unsigned int i, MapIteratorType tp) : mtable(table), mPosition(i), mType(tp)
			{
				// Intentionally empty
			}

			/// <summary>
			/// Copy Constructor for MapIterator
			/// </summary>
			/// <param name="other"></param>
			MapIterator(const MapIterator& other) : mTable(other.mTable), mPosition(other.mPosition), mType(other.mType)
			{
				// intentionally empty
			}

			/// <summary>
			/// Checks if we are equal to other
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator==(const MapIterator& other) const
			{
				return mTable == other.mTable && mPosition == other.mPosition;
			}

			/// <summary>
			/// Checks if we are not equal to other
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			bool operator!=(const MapIterator& other) const
			{
				return !(*this == other);
			}

			/// <summary>
			/// Used to copy one MapIterator value to another
			/// </summary>
			/// <param name="other"></param>
			/// <returns></returns>
			MapIterator& operator=(const MapIterator& other)
			{
				mTable = other.mTable;
				mPosition = other.mPosition;
				return *this;
			}

			/// <summary>
			/// Returns a reference to current item in map. 
			/// </summary>
			/// <returns></returns>
			const Map<K,V>& operator*() const
			{
				return mTable[mPosition]; 
			}

			/// <summary>
			/// Increments / Advances the Iterator (pre-fix version)
			/// </summary>
			/// <returns></returns>
			MapIterator& operator++()
			{
				++mPosition;
				while (mPosition < mTable->mCapacity && !mTable[mPosition].occupied)
					++mPosition;
				return *this;
			}

			/// <summary>
			/// Increments / Advances the Iterator (post-fix version)
			/// </summary>
			/// <param name="not_used"></param>
			/// <returns></returns>
			MapIterator operator++(int not_used)
			{
				MapIterator return_val = *this;
				++(*this);
				return return_val;
			}

			/// <summary>
			/// Decrements the Iterator (pre-fix version). Did I even need this?
			/// </summary>
			/// <returns></returns>
			MapIterator& operator--()
			{
				--mPosition;
				while (mPosition > 0 && !mTable[mPosition].occupied)
					--mPosition;
				return *this;
			}
			
			/// <summary>
			/// Decrements the Iterator (post-fix version). Did I even need this?
			/// </summary>
			/// <param name="not_used"></param>
			/// <returns></returns>
			MapIterator& operator--(int not_used)
			{
				MapIterator return_val = *this;
				--(*this);
				return return_val;
			}

			/// <summary>
			/// Returns a copy of the Iterator some offset from current Position.
			/// </summary>
			/// <param name="offset"></param>
			/// <returns></returns>
			MapIterator operator+(int offset) const
			{
				MapIterator temp = *this;
				while (offset > 0 && temp.mPosition < temp.mTable->mCapacity)
				{
					++temp.mPosition;
					if (temp.mTable->mTable[temp.mPosition].occupied)
						--offset;
				}
				return temp;
			}

			/// <summary>
			/// Returns a copy of the Iterator some offset from current Position. Did I need this?
			/// </summary>
			/// <param name="offset"></param>
			/// <returns></returns>
			MapIterator operator-(int offset) const
			{
				MapIterator temp = *this;
				while (offset > 0 && temp.mPosition > 0)
				{
					--temp.mPosition;
					if (temp.mTable->mTable[temp.mPosition].occupied)
						--offset;
				}
				return temp;
			}

			friend class Map;
		};

	public:

		/// <summary>
		/// The Default Constructor
		/// </summary>
		Map() : mSize(0), mCapacity(mMinCapacity), mTable(std::pair<K, V>),
			occupied(new bool[mCapacity]())
		{
			// Intentionally empty
		}

		/// <summary>
		/// The Destructor
		/// </summary>
		~Map()
		{
			delete[] mTable;
			delete[] occupied;
		}

		/// <summary>
		/// The Copy Constructor
		/// </summary>
		/// <param name="other"></param>
		Map(const Map& other) : mCapacity(other.mCapacity), mSize(other.mSize)
		{
			mTable = new std::pair<K,V>[mCapacity];
			occupied = new bool[mCapacity];

			for (unsigned int i = 0; i < other.mSize; i++)
			{
				mTable[i] = other.mTable[i];
				occupied[i] = other.occupied[i];
			}
		}

		/// <summary>
		/// The Move Constructor
		/// </summary>
		/// <param name="other"></param>
		Map(Map&& other) : mCapacity(other.mCapacity), mSize(other.mSize), mTable(other.mTable), occupied(other.occupied)
		{
			other.mTable = nullptr;
			other.occupied = nullptr;
			other.mCapacity = 0;
			other.mSize = 0;
		}

		/// <summary>
		/// The Initializer List
		/// </summary>
		/// <param name="ilist"></param>
		Map(std::initializer_list <Map<K,V>> ilist) : mCapacity((int)ilist.size()), mSize((int)ilist.size())
		{
			mTable = new std::pair<K,V>[mCapacity];
			occupied = new bool[mCapacity]();
			int i = 0;
			for (const auto& kv : initList)
				insert(kv.first, kv.second);
			//for (T val : ilist)
				//(*this)[i++] = val;
		}

		/// <summary>
		/// Bracket operator overload. Can be used to add to or get from map
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		V& operator[](const K& key)
		{
			unsigned int index = std::hash(key);
			while (occupied[index])
			{
				if (mTable[index].first == key)
					return mTable[index].second;
				index = (index + 1) % mCapacity;
			}

			if ((float)mSize / mCapacity > 0.7)
			{
				grow();
				return (*this)[key];
			}

			mTable[index] = Map<K, V>(key, V());
			occupied[index] = true;
			mSize++;
			return mTable[index].second;
		}

		/// <summary>
		/// Output operator overload. Outputs in special format to show different pairs
		/// </summary>
		/// <param name="os"></param>
		/// <param name="map"></param>
		/// <returns></returns>
		friend std::ostream& operator <<(std::ostream& os, const Map<K,V>& map)
		{
			os << "{";
			bool first = true;
			for (unsigned int i = 0; i < map.capacity; i++)
			{
				if (map.occupied[i])
				{
					if (!first) // trick I found online, prevents comma from placing before first pair
						os << ", ";
					os << map.mTable[i].first << ":" << map.mTable[i].second;
					first = false;
				}
			}
			os << "}";
		}

		/// <summary>
		/// Grow method for when adding pairs
		/// </summary>
		void grow()
		{
			unsigned int newCapacity = mCapacity * 2;
			Map<K, V>* newTable = new Map<K, V>[newCapacity];
			bool* newOccupied = new bool[newCapacity]();

			for (unsigned int i = 0; i < mCapacity; ++i)
			{
				if (occupied[i])
				{
					unsigned int newIndex = std::hash(mTable[i].first) % newCapacity;
					while (newOccupied[newIndex])
						newIndex = (newIndex + 1) % newCapacity;
					newTable[newIndex] = mTable[i];
					newOccupied[newIndex] = true;
				}
			}

			delete[] mTable;
			delete[] occupied;

			mTable = newTable;
			occupied = newOccupied;
			mCapacity = newCapacity;
		}

		/// <summary>
		/// Returns capacity
		/// </summary>
		/// <returns></returns>
		unsigned int capacity() const
		{
			return mCapacity;
		}

		/// <summary>
		/// Returns size
		/// </summary>
		/// <returns></returns>
		unsigned int size() const
		{
			return mSize;
		}

		/// <summary>
		/// Method for removing from map
		/// </summary>
		/// <param name="key"></param>
		void remove(const K& key)
		{
			unsigned int index = std::hash(key);
			unsigned int originalIndex = index;

			while (occupied[index])
			{
				if (mTable[index].first == key)
				{
					occupied[index] = false;
					mSize--;
					rehash(index);
					return;
				}
				index = (index + 1) % mCapacity;
				if (index == originalIndex)
					break;		// completed cycle, key not found
			}
		}

		/// <summary>
		/// Rehash method for usage in remove
		/// </summary>
		/// <param name="startIndex"></param>
		void rehash(unsigned int startIndex)
		{
			unsigned int index = (startIndex + 1) % mCapacity;
			while (occupied[index])
			{
				std::pair<K,V> newTable = mTable[index];
				occupied[index] = false;
				mSize--;

				(*this)[newTable.first] = newTable.second;

				index = (index + 1) % mCapacity;
			}
		}
		/// <summary>
		/// Method for finding pairs using Iterator. Didn't do contains because I had the iterator
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		MapIterator find(const K& key) const
		{
			// We can use the for loop to loop through the iterator as opposed to using an int i index
			for (MapIterator it = begin(); it != end(); ++it)
			{
				if ((*it).first == key)
					return it;
			}
			return end();
		}

		/// <summary>
		/// Begin for MapIterator
		/// </summary>
		/// <returns></returns>
		MapIterator begin() const
		{
			return MapIterator(this, MapIteratorType::FORWARD, 0);
		}

		/// <summary>
		/// End for MapIterator
		/// </summary>
		/// <returns></returns>
		MapIterator end() const
		{
			return MapIterator(this, MapIteratorType::FORWARD, mSize);
		}

		/// <summary>
		/// Right Begin for MapIterator
		/// </summary>
		/// <returns></returns>
		MapIterator rbegin() const
		{
			return MapIterator(this, MapIteratorType::BACKWARDS, mSize - 1);
		}

		/// <summary>
		/// Right End for MapIterator
		/// </summary>
		/// <returns></returns>
		MapIterator rend() const
		{
			return MapIterator(this, MapIteratorType::BACKWARDS, -1);
		}
	};
}
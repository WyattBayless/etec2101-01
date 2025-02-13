#pragma once

#include <iostream>

namespace ssuds
{
	template <class T>
	class ArrayList
	{
	private:
		T* my_array;
		unsigned int my_array_size;
		unsigned int my_array_capacity;

		void grow()
		{
			T* temp_array = new T[my_array_capacity * 2];
			for (unsigned int i = 0; i < my_array_size; i++)
				temp_array[i] = my_array[i];
			delete[] my_array;
			my_array = temp_array;
			my_array_capacity *= 2;
		}

		void shrink()
		{
			T* temp_array = new T[my_array_capacity * 0.5];
			for (unsigned int i = 0; i < my_array_size; i++)
				temp_array[i] = my_array[i];
			delete[] my_array;
			my_array = temp_array;
			my_array_capacity *= 0.5;
		}

	public:
		ArrayList()
		{
			my_array_capacity = 5;
			my_array = new T[my_array_capacity];
			my_array_size = 0;
		}

		~ArrayList()
		{
			delete[] my_array;
		}

		int size()
		{
			return my_array_size;
		}
		
		int capacity()
		{
			return my_array_capacity;
		}

		void reserve(unsigned int amount)
		{
			my_array_capacity = amount;
		}

		void append(const T& new_value)
		{
			if (my_array_size == my_array_capacity)
				grow();
			my_array[my_array_size] = new_value;
			my_array_size++;
		}

		void prepend(const T& new_value)
		{
			if (my_array_size == my_array_capacity)
				grow();
			T* temp_array = new T[my_array_capacity];
			for (unsigned int i = 0; i < my_array_size; i++)
				temp_array[i + 1] = my_array[i];
			delete[] my_array;
			my_array = temp_array;
			my_array[0] = new_value;
			my_array_size++;
		}

		T at(unsigned int index) const
		{
			if (index < 0)
				throw std::out_of_range("The given index cannot be negative");
			if (index >= my_array_size)
				throw std::out_of_range("The given index cannot exceed the size of the array");
			return my_array[index];
		}

		int find(const T& search_value, unsigned int start_index=0)
		{
			for (unsigned int i = start_index; i < my_array_size; i++)
			{
				if (my_array[i] == search_value)
					return i;
			}
			return -1;
		}

		void insert(const T& new_value, unsigned int index)
		{
			if (my_array_size == my_array_capacity)
				grow();
			T* temp_array = new T[my_array_capacity];
			for (unsigned int i=0; i < my_array_size; i++)
			{
				if (i < index)
					temp_array[i] = my_array[i];
				if (i >= index)
					temp_array[i + 1] = my_array[i];
			}
			delete[] my_array;
			my_array = temp_array;
			my_array[index] = new_value;
			my_array_size++;
		}

		void output(std::ostream& os)
		{
			os << "[";
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				if (i == my_array_size - 1)
					os << my_array[i];
				else
					os << my_array[i] << ", ";
			}
			os << "]";
		}

		void remove(int index)
		{
			if (index < 0)
				throw std::out_of_range("The given index cannot be negative");
			if (index >= my_array_size)
				throw std::out_of_range("The given index cannot exceed the size of the array");
			if (my_array_size <= (my_array_capacity / 4))
				shrink();
			T* temp_array = new T[my_array_capacity];
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				if (i < index)
					temp_array[i] = my_array[i];
				if (i > index)
					temp_array[i - 1] = my_array[i];
			}
			delete[] my_array;
			my_array = temp_array;
			my_array_size--;
		}

		int remove_all(const T& value)
		{
			unsigned int remove_count = 0;
			for (unsigned int i = 0; i < my_array_size; i++)
			{
				if (my_array[i] == value)
				{
					remove(i);
					remove_count++;

				}
			}
			return remove_count;
		}

		//Doxygen stuff and main program
	};
}
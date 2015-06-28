#include "memory.h"

namespace EPITOME
{
	template <typename T>
	Room<T>::Room() {}

	template <typename T>
	Room<T>::~Room()
	{
		Empty();
	}

	template <typename T>
	Room<T>::Room(Room&& other)
	{
		items = other.items;
		other.items.clear();
	}

	template<typename T>
	void Room<T>::Add(T* item)
	{
		items.push_back(item);
	}

	template <typename T>
	void Room<T>::Empty()
	{
		for (T* a : items)
		{
			a->dispose();
			delete a;
		}
		items.clear();
	}
}
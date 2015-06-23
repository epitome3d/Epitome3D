#pragma once
#include <vector>

#include "utils.h"

namespace EPITOME
{

	template <typename T>
	class Room : public Disposable
	{
	public:
		Room();
		~Room();
		Room(Room&&);

		void Add(T* item);
		void Empty();

	private:
		Room(Room&);
		std::vector<T*> items;
	};
}
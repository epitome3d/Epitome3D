#pragma once
#include <vector>

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

	__interface Disposable
	{
	public:
		virtual void Dispose() = 0;
	};

	__interface Bin : public Disposable
	{
	public:
		virtual void Load() = 0;
		virtual void Unload() = 0;
	};
}
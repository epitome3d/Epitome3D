#include <vector>

namespace EPITOME
{
	template <typename T>
	class Room
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
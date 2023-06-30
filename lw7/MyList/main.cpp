#include <vector>
#include "MyList.h"
#include <iostream>

template <typename T>
void PrintList(CMyList<T>& list)
{
	std::cout << "Current state of list";

	if (list.IsEmpty())
	{
		std::cout << ": empty";
		return;
	}

	std::cout << std::endl << "  Size: " << list.Size();
	std::cout << std::endl << "  Data:";

	for (auto it = list.begin(); it != list.end(); ++it)
	{
		std::cout << std::endl << "    " << *it;
	}

	std::cout << std::endl;
}

template <typename T>
void DemoList(const std::vector<T>& data)
{
	if (data.size() != 3)
	{
		return;
	}

	CMyList<T> list;

	std::cout << "Check push front in list" << std::endl;
	list.PushFront(data[0]);
	PrintList(list);

	std::cout << "Check push back in list" << std::endl;
	list.PushBack(data[2]);
	PrintList(list);

	std::cout << "Check insert in list" << std::endl;
	auto it = list.begin();
	++it;
	it = list.Insert(it, data[1]);
	PrintList(list);

	std::cout << "Check erase in list" << std::endl;
	list.Erase(it);
	PrintList(list);

	std::cout << "Check clear list" << std::endl;
	list.Clear();
	PrintList(list);

	std::cout << std::endl;
}

int main()
{
	std::vector<std::string> stringData =
	{
		"first",
		"second",
		"third"
	};
	std::vector<int> intData = { 1, 2, 3 };

	DemoList(stringData);
	DemoList(intData);

	return 0;
}
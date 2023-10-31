#include "../../catch2/catch.hpp"
#include "../StringList/StringList.h"
#include "../StringList/StringListIterator.h"

TEST_CASE("Check the list has a size and is it empty or not")
{
	CStringList testList;

	REQUIRE(testList.IsEmpty());
	REQUIRE(testList.GetSize() == 0);

	testList.PushBack("first");
	REQUIRE(!testList.IsEmpty());
	REQUIRE(testList.GetSize() == 1);
}

TEST_CASE("Check the assignment and copying of the list")
{
	CStringList testList1;
	CStringList testList2;

	REQUIRE(testList1.IsEmpty());
	REQUIRE(testList1.GetSize() == 0);

	testList1.PushBack("first");
	testList2 = testList1;

	REQUIRE(!testList2.IsEmpty());
	REQUIRE(testList2.GetSize() == 1);

	CStringList copyList(testList2);

	REQUIRE(!copyList.IsEmpty());
	REQUIRE(copyList.GetSize() == 1);
}

TEST_CASE("Check the assignment and copying of the list with move semantic")
{
	CStringList testList1;

	REQUIRE(testList1.IsEmpty());
	REQUIRE(testList1.GetSize() == 0);

	testList1.PushBack("first");
	CStringList testList2(std::move(testList1));;

	REQUIRE(!testList2.IsEmpty());
	REQUIRE(testList2.GetSize() == 1);

	CStringList testList3;
	testList2 = std::move(testList3);

	REQUIRE(testList2.IsEmpty());
	REQUIRE(testList2.GetSize() == 0);
}

TEST_CASE("Check push back and front, insert and erase")
{
	CStringList testList;

	testList.PushBack("first");
	REQUIRE(testList.GetSize() == 1);

	testList.PushFront("zero");
	REQUIRE(testList.GetSize() == 2);

	testList.Insert(++testList.begin(), "third");
	REQUIRE(testList.GetSize() == 3);

	testList.Erase(--testList.end());
	REQUIRE(testList.GetSize() == 2);

	testList.Clear();
	REQUIRE(testList.GetSize() == 0);
}

TEST_CASE("Check work iterator")
{
	CStringList testList;
	testList.PushBack("first");
	testList.PushBack("second");
	testList.PushBack("third");

	CStringList::Iterator it = testList.begin();
	REQUIRE(*it == "first");
	REQUIRE("first" == *(it++));
	REQUIRE(*it == "second");
	REQUIRE("third" == *(++it));
	REQUIRE(*it == "third");

	CStringList::ReverseIterator reit = testList.rend();
	--reit;
	REQUIRE(*reit == "first");
	REQUIRE("first" == *(reit--));
	REQUIRE(*reit == "second");
	REQUIRE("first" == *(++reit));
	REQUIRE(*reit == "first");

	CStringList::ConstIterator cbit = testList.cbegin();
	REQUIRE(*cbit == "first");
	REQUIRE("first" == *(cbit++));
	REQUIRE(*cbit == "second");
	REQUIRE("third" == *(++cbit));
	REQUIRE(*cbit == "third");

	CStringList::ReverseIterator rbit = testList.rbegin();
	REQUIRE(*rbit == "third");
	REQUIRE("third" == *(rbit++));
	REQUIRE(*rbit == "second");
	REQUIRE("third" == *(--rbit));
	REQUIRE(*rbit == "third");

	CStringList::ConstIterator ceit = testList.cend();
	REQUIRE(ceit == testList.cend());
	ceit--;
	REQUIRE(*ceit == "third");
	REQUIRE("third" == *(ceit--));
	REQUIRE(*ceit == "second");
	REQUIRE("third" == *(++ceit));
	REQUIRE(*ceit == "third");

	CStringList::ConstReverseIterator rcbit = testList.rcbegin();
	REQUIRE(*rcbit == "third");
	REQUIRE("third" == *(rcbit++));
	REQUIRE(*rcbit == "second");
	REQUIRE("third" == *(--rcbit));
	REQUIRE(*rcbit == "third");

	CStringList::ConstReverseIterator rceit = testList.rcend();
	--rceit;
	REQUIRE(*rceit == "first");
	REQUIRE("first" == *(rceit--));
	REQUIRE(*rceit == "second");
	REQUIRE("first" == *(++rceit));
	REQUIRE(*rceit == "first");
}
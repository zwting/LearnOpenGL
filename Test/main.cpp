#include <iostream>
#include <vector>
using namespace std;

class Person
{
public:
	string name;
	int age;

	Person(const Person& other)
	{
		cout << "复制构造..." << endl;
		this->arr = other.arr;
	}

	Person()
	{
		cout << "构造..." << endl;
	}

	vector<int> arr;

	Person(const vector<int>& arr)
	{
		this->arr = arr;
	}

	void displayInfo()
	{
		cout << "name: " << name << ", arr.size=" << arr.size() << endl;
	}
};

Person func()
{
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);

	auto ret = Person(arr);
	ret.displayInfo();

	return ret;
}

int main()
{
	Person p;
	Person p2 = func();
	p2.displayInfo();
	return 0;
}

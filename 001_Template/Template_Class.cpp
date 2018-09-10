#include <iostream>
#include <string>
using namespace std;

template<typename T> class Character
{
public:
	void Set(T name)
	{
		this->name = name;
	}

	void PrintName()
	{
		cout << "캐릭터 : " << name << endl;
	}

private:
	T name;
};

class Player : public Character<string>
{

};

void main()
{
	Character<int> ob;
	ob.Set(20);
	ob.PrintName();

	Player player;
	player.Set("후비적");
	player.PrintName();
}

// inline
class A
{
public:
	void Add();
};

inline void A::Add() {
	cout << "z" << endl;
}

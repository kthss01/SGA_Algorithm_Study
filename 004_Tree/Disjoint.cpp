#include <iostream>
using namespace std;

template<typename T> class Disjoint
{
public:
	struct Set;

public:
	// 합집합으로 만드는거
	void UnionSet(Set* set1, Set* set2)
	{
		set2 = FindSet(set2);
		set2->Parent = set1;
	}

	// 최종부모 찾는 함수
	Set* FindSet(Set* set)
	{
		while (set->Parent != NULL)
			set = set->Parent;

		return set;
	}

	Set* MakeSet(T data)
	{
		Set* set = new Set();
		set->Data = data;
		set->Parent = NULL;

		return set;
	}

public:
	struct Set
	{
		// 자기 부모가 누군지만 알면 되서 부모만 가지고 있음
		Set* Parent;

		T Data;
		// 오리지날 부모를 가지고 있어야함
		// Union 할때 오리지날 부모를 남겨둬야 끉어졌을 때 다시 오리지날 부모를 가리킴
	};
};

void main() 
{
	int a = 1, b = 2, c = 3, d = 4;

	// a,b,c,d 가 구조체의 변수라고 생각
	Disjoint<int>* disjoint = new Disjoint<int>();
	Disjoint<int>::Set* set1 = disjoint->MakeSet(a);
	Disjoint<int>::Set* set2 = disjoint->MakeSet(b);
	Disjoint<int>::Set* set3 = disjoint->MakeSet(c);
	Disjoint<int>::Set* set4 = disjoint->MakeSet(d);

	bool temp = disjoint->FindSet(set1) == disjoint->FindSet(set2);
	cout << "set1 == set2 " << temp << endl;

	disjoint->UnionSet(set1, set3);
	temp = disjoint->FindSet(set1) == disjoint->FindSet(set3);
	cout << "set1 == set3 " << temp << endl;

	disjoint->UnionSet(set3, set4);
	temp = disjoint->FindSet(set3) == disjoint->FindSet(set4);
	cout << "set3 == set4 " << temp << endl;

	delete disjoint;
}


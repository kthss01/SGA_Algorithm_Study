#include <iostream>
using namespace std;

template<typename T> class Disjoint
{
public:
	struct Set;

public:
	// ���������� ����°�
	void UnionSet(Set* set1, Set* set2)
	{
		set2 = FindSet(set2);
		set2->Parent = set1;
	}

	// �����θ� ã�� �Լ�
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
		// �ڱ� �θ� �������� �˸� �Ǽ� �θ� ������ ����
		Set* Parent;

		T Data;
		// �������� �θ� ������ �־����
		// Union �Ҷ� �������� �θ� ���ܵ־� �������� �� �ٽ� �������� �θ� ����Ŵ
	};
};

void main() 
{
	int a = 1, b = 2, c = 3, d = 4;

	// a,b,c,d �� ����ü�� ������� ����
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


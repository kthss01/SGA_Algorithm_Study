#pragma once

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


#include "Priority.h"
#include <Windows.h>

PriorityQueue * CreateQueue(int size)
{
	PriorityQueue* q = new PriorityQueue();
	q->Capacity = size;
	q->UsedSize = 0;
	q->Nodes = new QueueNode[q->Capacity];

	return q;
}

void DestroyQueue(PriorityQueue * queue)
{
	delete[] queue->Nodes;
	delete queue;
}

void Enqueue(PriorityQueue * queue, QueueNode node)
{
	int currentPos = queue->UsedSize;
	int parentPos = GetParentQueueNode(currentPos);

	if (queue->UsedSize == queue->Capacity)
	{
		if (queue->Capacity == 0)
			queue->Capacity = 1;

		queue->Capacity *= 2;
		
		delete[] queue->Nodes;
		queue->Nodes = new QueueNode[queue->Capacity];
	}

	while (currentPos > 0 
		&& queue->Nodes[currentPos].Priority < queue->Nodes[parentPos].Priority)
	{
		SwapQueueNodes(queue, currentPos, parentPos);

		currentPos = parentPos;
		parentPos = GetParentQueueNode(currentPos);
	}

	queue->UsedSize++;
}

void Dequeue(PriorityQueue * queue, QueueNode * node)
{
	int parent = 0;
	int left = 0, right = 0;

	memcpy(node, &queue->Nodes[0], sizeof(QueueNode));
	ZeroMemory(&queue->Nodes[0], sizeof(QueueNode));
	
	queue->UsedSize--;

	SwapQueueNodes(queue, 0, queue->UsedSize);

	left = GetLeftChildQueue(0);
	right = left + 1;

	while (true)
	{
		int select = 0;

		if (left >= queue->UsedSize)
			break;

		if (right >= queue->UsedSize)
		{
			select = left;
		}
		else
		{
			if (queue->Nodes[left].Priority > queue->Nodes[right].Priority)
				select = right;
			else
				select = left;
		}

		if (queue->Nodes[select].Priority < queue->Nodes[parent].Priority)
		{
			SwapQueueNodes(queue, select, parent);
			parent = select;
		}
		else
			break;

		left = GetLeftChildQueue(parent);
		right = left + 1;
	}

	if (queue->UsedSize < (queue->Capacity / 2))
	{
		queue->Capacity /= 2;
		
		delete[] queue->Nodes;
		queue->Nodes = new QueueNode[queue->Capacity];
	}
}

int GetParentQueueNode(int index)
{
	return (int)((index - 1) / 2);
}

int GetLeftChildQueue(int index)
{
	return (2 * index) + 1;
}

void SwapQueueNodes(PriorityQueue * queue, int index1, int index2)
{
	size_t size = sizeof(QueueNode);
	QueueNode* temp = new QueueNode();

	memcpy(temp, &queue->Nodes[index1], size);
	memcpy(&queue->Nodes[index1], &queue->Nodes[index2], size);
	memcpy(&queue->Nodes[index2], temp, size);

	delete temp;
}

bool IsEmptyQueue(PriorityQueue * queue)
{
	return queue->UsedSize == 0;
}

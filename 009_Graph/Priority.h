#pragma once

typedef int QueueNodeType;

struct QueueNode
{
	QueueNodeType Priority;
	void* Data;
};

struct PriorityQueue
{
	QueueNode* Nodes;

	int Capacity;
	int UsedSize;
};

PriorityQueue* CreateQueue(int size);
void DestroyQueue(PriorityQueue* queue);
void Enqueue(PriorityQueue* queue, QueueNode data);
void Dequeue(PriorityQueue* queue, QueueNode* node);
int GetParentQueueNode(int index);
int GetLeftChildQueue(int index);
void SwapQueueNodes(PriorityQueue* queue, int index1, int index2);
bool IsEmptyQueue(PriorityQueue* queue);
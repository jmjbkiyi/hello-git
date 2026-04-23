// Simplified version_My linked list version queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
// this is a simplified version of a linked list implementation of a queue in C++.
// It includes basic operations such as adding an element to the back, removing an element from the front,
// retrieving the front element, clearing the queue, printing the queue, checking the size, and checking if it's empty.
#include <iostream>
#include <string>
// 已经移除 #include <utility>

using namespace std;

struct LinkNode
{
	friend class LinkedList;
private:
	LinkNode* next{ nullptr };
	string data;
	LinkNode() = default;
	LinkNode(const string& ss) : data(ss) {}
};

class LinkedList
{
private:
	LinkNode* front{ nullptr };
	LinkNode* rear{ nullptr };
	size_t size{ 0 };
	
	// 手工实现交换逻辑，替代 std::swap
	void swap(LinkedList& other) noexcept
	{
		// 交换 front 指针
		LinkNode* tempFront = front;
		front = other.front;
		other.front = tempFront;

		// 交换 rear 指针
		LinkNode* tempRear = rear;
		rear = other.rear;
		other.rear = tempRear;

		// 交换 size 大小
		size_t tempSize = size;
		size = other.size;
		other.size = tempSize;
	}
	
public:
	LinkedList() = default;
	~LinkedList()
	{
		clear();
	}
	
	// Copy constructor
	LinkedList(const LinkedList& other)
		: front(nullptr), rear(nullptr), size(0)
	{
		LinkNode* cur = other.front;
		while (cur)
		{
			push_back(cur->data);
			cur = cur->next;
		}
	}
	
	// Copy assignment (copy-and-swap)
	LinkedList& operator=(const LinkedList& other)
	{
		if (this == &other) return *this;
		LinkedList temp(other); // may throw
		swap(temp);
		return *this;
	}
	
	void push_back(const string& ss)
	{
		LinkNode* newNode = new LinkNode(ss);
		if (rear)
		{
			rear->next = newNode;
			rear = newNode;
		}
		else
		{
			front = rear = newNode;
		}
		++size;
	}
	
	string pop_front()
	{
		if (!front)
		{
			throw runtime_error("List is empty");
		}
		LinkNode* temp = front;
		string retData = front->data;
		front = front->next;
		if (!front)
		{
			rear = nullptr;
		}
		delete temp;
		--size;
		return retData;
	}
	
	string get_front() const
	{
		if (front == nullptr)
		{
			throw runtime_error("List is empty");
		}
		return front->data;
	}
	
	void clear()
	{
		while (front)
		{
			pop_front();
		}
	}
	
	void print() const
	{
		LinkNode* current = front;
		while (current)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
	
	size_t get_size() const
	{
		return size;
	}
	
	bool is_empty() const
	{
		return (size == 0);
	}
};

int main()
{
	typedef LinkedList Queue;
	Queue test_q;
	test_q.push_back("first");
	test_q.push_back("second");
	test_q.push_back("third");
	test_q.push_back("fourth");
	test_q.print();
	
	cout << "Front element: " << test_q.get_front() << endl;
	cout << "Popped element: " << test_q.pop_front() << endl;
	test_q.print();
	cout << "Queue size: " << test_q.get_size() << endl;
	test_q.clear();
	cout << "Queue cleared. Size: " << test_q.get_size() << endl;
	
	// Demonstrate copy assignment
	Queue q2;
	q2 = test_q;
	cout << "After assignment, q2 is empty: " << (q2.is_empty() ? "true" : "false") << endl;
	cout << "q2 size after assignment: " << q2.get_size() << endl;
	return 0;
}
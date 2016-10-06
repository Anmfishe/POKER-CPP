#pragma once
template<class T>
class LinkedList
{
public:

	LinkedList() {
		size = 0;
	};
	void push_back(T t) {
		node *temp = new node();
		temp->val = t;
		if (head == NULL) {
			head = tail = temp;
		}
		else {
			tail->next = temp;
			last = temp;
		}
		size++;
	};
	void push_front(T t) {
		node *temp = new node();
		temp->val = t;
		if (head == NULL) {
			head = tail = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
		size++;
	};
	T pop_front() {
		if (size > 0) {
			node *temp = new node();
			temp = head;
			T t2 = head->val;
		}
		return T();
	};
	T pop_back() {
		return T();
	};
	void find_and_delete(T t) {
	
	};
	T find_at_index(int index) {
		retun T();
	};
	void clear() {
	
	};
	int getSize() {
		return size;
	};
	~LinkedList() {};
private:
	struct node {
		T val;
		node *next = NULL;
	};
	int size;
	node *head = NULL;
	node *tail = NULL;
};


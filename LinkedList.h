#pragma once
#include <iostream>

using namespace std;

template<class T>
class LinkedList
{
public:

	LinkedList() {
		size = 0;
	};
	void push_back(const T &t) {
		node *temp = new node;
		temp->val = t;
		if (head == NULL) {
			head = tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
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
		if (head->next != NULL) {
			node *temp = head;
			T temp2 = head->val;
			head = head->next;
			size--;
			delete temp;
			return temp2;
		}
		else if (head != NULL && head->next == NULL) {
			T temp2 = head->val;
			node *temp = head;
			head = tail = NULL;
			size--;
			delete temp;
			return temp2;
		}
		else {
			return T();
		}
	};
	T pop_back() {
		if (head->next != NULL) {
			node *curr = head;
			while (curr->next != tail) {
				curr = curr->next;
			}
			T temp2 = tail->val;
			tail = curr;
			curr = curr->next;
			tail->next = NULL;
			size--;
			delete curr;
			return temp2;
		}
		else if (head != NULL && head->next == NULL) {
			T temp2 = head->val;
			node *temp = head;
			head = tail = NULL;
			size--;
			delete temp;
			return temp2;
		}
		else {
			return T();
		}
	};
	bool find_and_delete(const T &t) {
		node *curr = head;
		if (head == NULL) return false;
		else if (head == tail && head->next == NULL) {
			if (head->val == t) {
				delete head;
				head = tail = NULL;
				size--;
				return true;
			}
			else {
				return false;
			}
		}
		else if (head->val == t) {
			head = head->next;
			delete curr;
			size--;
			return true;
		}
		while (curr->next != tail) {
			if (curr->next->val == t) {
				node* temp = curr->next;
				curr->next = curr->next->next;
				size--;
				delete temp;
				return true;
			}
			curr = curr->next;
		}	
		if (tail->val == t) {
			tail = curr;
			curr = curr->next;
			tail->next = NULL;
			delete curr;
			size--;
			return true;
		}
		return false;
	};
	T find_at_index(int index) {
		if (index > size) {
			return T();
		}
		node *curr = head;
		for (int i = 0; i < index; i++) {
			curr = curr->next;
		}
		return curr->val;
	};
	void find_and_delete_at_index(int index) {
		find_and_delete(find_at_index(index));
	};
	bool clear() {
		node* curr = head;
		while (curr != NULL) {
			head = head->next;
			delete curr;
			curr = head;
		}
		head = tail = NULL;
		size = 0;
		return true;
	};
	int getSize() {
		return size;
	};
	void print() {
		node *curr = head;
		while (curr != NULL) {
			cout << curr->val << endl;
			curr = curr->next;
		}
		cout << endl;
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


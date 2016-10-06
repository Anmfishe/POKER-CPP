#include "LinkedList.h"


template<class T>
LinkedList<T>::LinkedList()
{
	size = 0;
}


template<class T>
void LinkedList<T>::push_back(T t)
{
	node *tmp = new node();
	tmp->val = t;

	if (head == NULL) {
		head = tmp;
		tail = tmp;
		size++;
	}
	else {
		last->next = tmp;
		last = tmp;
		size++;
	}
}
/*template<class T>
void LinkedList<T>::push_front(T t)
{
	node *tmp = new node();
	tmp->val = t;

	if (head == NULL) {
		head = tmp;
		tail = tmp;
		size++;
	}else{
		tmp->next = head;
		head = tmp;
		size++;
	}
}
template<class T>
T LinkedList<T>::pop_front()
{
	if (size == 0) {
		cout << "\nCan't pop_front the list is empty";
		return T();
	}
	if (size > 1) {
		node *tmp = head;
		T tmp2 = head->val;
		head = head->next;
		size--;
		delete tmp;
		return tmp2;
	}
	else if (size == 1) {
		node *tmp = head;
		T tmp2 = tmp->val;
		head = NULL;
		tail = NULL;
		size--;
		delete tmp;
		return tmp2;
	}
	return T();
}
template<class T>
T LinkedList<T>::pop_back()
{

	
	return T();
}
template<class T>
void LinkedList<T>::find_and_delete(T t)
{
}
template<class T>
T LinkedList<T>::find_at_index(int index)
{
	return T();
}
template<class T>
void LinkedList<T>::clear()
{
}*/
template<class T>
LinkedList<T>::~LinkedList()
{
}

#ifndef __QUEUE_OF_STRINGS_HPP
#define __QUEUE_OF_STRINGS_HPP

#include <string>
#include <stdexcept>

class QueueEmptyException : public std::runtime_error 
{
public:
	explicit QueueEmptyException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Object>
class GenericQueue
{
private:
	// fill in private member data here
	struct Node {
		Node(const Object&v)
		: value(v), nextNode(nullptr)
		{}

		Object value;
		Node* nextNode;
	};

	Node* frontNode;

public:
	GenericQueue();

	// Note:  copy constructors are required.
	// Be sure to do a "deep copy" -- if I 
	// make a copy and modify one, it should not affect the other. 
	GenericQueue(const GenericQueue & st);
	GenericQueue & operator=(const GenericQueue & st);
	~GenericQueue();

	size_t size() const noexcept;
	bool isEmpty() const noexcept;


	void enqueue(const Object & elem);


	// both versions of front(), as well as dequeue(), throw a QueueEmptyException if called when empty.
	Object & front();
	const Object & front() const;

	// does not return anything.  Just removes. 
	void dequeue();
};

template<typename Object>
GenericQueue<Object>::GenericQueue()
{
	frontNode = nullptr;
}



// Note:  copy constructors are required.
// Be sure to do a "deep copy" -- if I 
// make a copy and modify one, it should not affect the other. 
template<typename Object>
GenericQueue<Object>::GenericQueue(const GenericQueue & st)
{
	frontNode = nullptr;

	Node* currentNode{st.frontNode};

	while(currentNode != nullptr) {
		enqueue(currentNode->value);
		currentNode = currentNode->nextNode;
	}
}

template<typename Object>
GenericQueue<Object> & GenericQueue<Object>::operator=(const GenericQueue<Object> & st)
{
	if( this != &st )
	{
		// delete the current materials then finish the assignment operation.
		while(!isEmpty()) {
			dequeue();
		}

		Node* currentNode{st.frontNode};
		while(currentNode != nullptr) {
			enqueue(currentNode->value);
			currentNode = currentNode->nextNode;
		}
	}

	return *this;

}

template<typename Object>
GenericQueue<Object>::~GenericQueue() 
{
	while(!isEmpty()) {
		dequeue();
	}
}


template<typename Object>
size_t GenericQueue<Object>::size() const noexcept
{
	size_t queueCount{0};
	Node* current{frontNode};

	while (current != nullptr)
	{
		queueCount++;
		current = current->nextNode;
	}

	return queueCount;
}


template<typename Object>
bool GenericQueue<Object>::isEmpty() const noexcept
{
	return frontNode == nullptr;
}

template<typename Object>
void GenericQueue<Object>::enqueue(const Object & elem)
{
	Node* newNode{new Node(elem)};

	// If the queue is empty, it makes the frontNode point to the new QueueMode
	if (isEmpty())
		frontNode = newNode;
	else 
	{
		// Retrieve the frontNode
		Node* currentNode{frontNode};

		// Iterate through the nodes until reaching the final node, which the nextNode points to a nullptr (obiviously)
		while (currentNode->nextNode != nullptr) 
			currentNode = currentNode->nextNode;

		// Create a newNode after the last node previously 
		currentNode->nextNode = newNode;
	}
}


template<typename Object>
Object & GenericQueue<Object>::front()
{
	// If there is no string in the front node, then the queue is empty because there should be a string.
	if (isEmpty())
		throw QueueEmptyException{"Queue is Empty"};
	
	// Else, return the string object or value inside the front node or beginning of the linked list.
	return frontNode->value;
}

template<typename Object>
const Object & GenericQueue<Object>::front() const
{
	// If there is no string in the front node, then the queue is empty because there should be a string.
	if (isEmpty())
		throw QueueEmptyException{"Queue is Empty"};
	
	// Else, return the string object or value inside the front node or beginning of the linked list.
	return frontNode->value;
}


// does not return anything.  Just removes. 
template<typename Object>
void GenericQueue<Object>::dequeue()
{
	if (isEmpty())
		throw QueueEmptyException("Queue is Empty");
	
	Node* tmp{frontNode}; // Storing the frontNode into a temporary node.
	frontNode = frontNode->nextNode; // Pointing to the next node and storing it inside the frontNode.
	delete tmp; // Removing the frontNode.
}




#endif 


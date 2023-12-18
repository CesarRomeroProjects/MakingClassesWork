# Project 5: Making Classes Work

# Overview
This project consists of two parts. In the first part, you will implement a generic queue data structure using templates. Refer to the project four specification for information about a queue and the GenericQueue.hpp file for the expected interface. In the second part, you will develop an algorithm to match TAs to classes based on their preferences.

# Part One: Generic Queue Implementation
Implement a generic queue data structure using templates. The interface is specified in the GenericQueue.hpp file. You may refer to your queue implementation from the previous project but cannot use someone else's implementation. If you did not receive full credit for the queue part of project four, consider that when testing your queue for this assignment.

# Functions to Implement in GenericQueue
1. Constructor: Create an empty queue.
2. Destructor: Properly free memory.
3. void enqueue(const T &item): Add an item to the end of the queue.
4. T dequeue(): Remove and return the front item from the queue.
5. bool isEmpty() const: Check if the queue is empty.

# Part Two: Match TAs to Classes
Develop an algorithm to match TAs to classes based on their preferences. The matching process follows a specific set of rules outlined in the project description.

# Matching Criteria
A matching will be considered correct if it satisfies the following conditions:

- For each TA, there is no class X for which the TA prefers X over their assignment, and X prefers that TA to the one assigned to the class.
- For each class, there is no TA Y for which the professor prefers Y over the TA assigned to the class, and Y prefers that class to their own assignment.

# Restrictions
- No additional #include directives without written permission.
- When writing GenericQueue, do not use any container classes except for the GenericQueue itself.
- When writing matchTAs, only use GenericQueue and unordered_map.
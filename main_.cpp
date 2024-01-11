#include <iostream>

import Queue;

int main()
{
    Queue::QueueBasedOnBidirectionalCyclicLinkedList<double> queue1;
    Queue::QueueBasedOnBidirectionalCyclicLinkedList<int> queue2(10);
    Queue::QueueBasedOnBidirectionalCyclicLinkedList<int> queue3(queue2);

    queue1.Push(1.23);
    queue1.Push(3.22);
    queue1.Push(4.56);
    std::cout << std::endl << "Elements of queue1: ";
    for (auto i = 0; i < queue1.GetSize(); i++)
    {
        std::cout << queue1[i] << '\t';
    }
    std::cout << std::endl;

    double temp;
    queue1.Pop(temp);
    std::cout << std::endl << "PopBacked element: " << temp << std::endl;
    std::cout << std::endl << "Elements of queue1: ";
    for (auto i = 0; i < queue1.GetSize(); i++)
    {
        std::cout << queue1[i] << '\t';
    }
    std::cout << std::endl;
    Queue::QueueBasedOnBidirectionalCyclicLinkedList<char> queue4 = { 'K', 'o', 't', 'l', 'o', 'v', 'a'};
    std::cout << std::endl << "Elements of queue4: ";
    for (auto i = 0; i < queue4.GetSize(); i++)
    {
        std::cout << queue4[i] << ' ';
    }
    std::cout << std::endl;
    char ch;
    queue4.Peek(ch);
    std::cout << std::endl << "PeekFronted element: " << ch << std::endl;

    return 0;
}


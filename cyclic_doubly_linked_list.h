#ifndef CYCLIC_DOUBLY_LINKED_LIST_H
#define CYCLIC_DOUBLY_LINKED_LIST_H


#include <iostream>
#include <bits/stdc++.h>
#include <vector>

#include "nbnode.h"

class NBNode;


class CyclicDoublyLinkedList
{
    NBNode* m_head{ nullptr };

    public:
    CyclicDoublyLinkedList();

    ~CyclicDoublyLinkedList();

    NBNode* get_head();

    NBNode* get_tail();

    bool isEmpty();

    /*
    Insert at back of list.
    */
    int insertBack(NBNode* newNode);

    /*
    Inserts at front of list. New node takes the head's place
    */
    int insertFront(NBNode* newNode);

    NBNode* popFront();

    NBNode* popBack();

    int removeNode(NBNode* removed);

    int emptyList();

    NBNode* removeParent();

    friend std::ostream& operator<<(std::ostream& out, CyclicDoublyLinkedList& list);
    friend std::ostream& reversePrint(std::ostream& out, CyclicDoublyLinkedList& list);

    friend class FibonacciHeap;
    friend class NBNode;
};

#endif
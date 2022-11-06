#ifndef NBNODE_H
#define NBNODE_H

#include <iostream>
#include <bits/stdc++.h>
#include <vector>

#include "cyclic_doubly_linked_list.h"

class CyclicDoublyLinkedList;


class NBNode
{
    NBNode* m_parent{ nullptr };
    int m_key{ };
    int m_value{ };
    int m_degree{ };
    CyclicDoublyLinkedList* m_childList{ nullptr };
    NBNode* m_next{ nullptr };
    NBNode* m_prev{ nullptr };

    bool wasPruned{ false };

public:
    NBNode(int key, int degree, int value, NBNode* parent, NBNode* child, NBNode* next, NBNode* prev);
    NBNode(int key);
    NBNode(int key, int value);

    ~NBNode();

    void setParent(NBNode* parent);
    void setChild(NBNode* child);
    void setNextSibling(NBNode* next);
    void setPrevSibling(NBNode* prev);
    void setKey(int newKey);
    void setValue(int newVal);

    NBNode* getChild();
    CyclicDoublyLinkedList& getChildrenList();
    int insertChildFront(NBNode* newChild);
    int cutFromParent();

    NBNode* getNextSibling();
    NBNode* getPrevSibling();
    NBNode* getParent();

    int getKey();
    int getValue();
    int getDegree();

    int incrementDegree();
    int decrementDegree();

    bool hasChildren();
    bool isMarked();
    int mark();
    int unmark();

    friend std::ostream& operator<<(std::ostream& out, NBNode& node);

};

#endif